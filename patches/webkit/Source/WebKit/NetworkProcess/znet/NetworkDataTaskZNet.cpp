#include "config.h"
#include "NetworkDataTaskZNet.h"

#include "AuthenticationManager.h"
#include "NetworkLoadParameters.h"
#include "NetworkSession.h"
#include <WebCore/FormData.h>
#include <WebCore/ResourceError.h>
#include <WebCore/ResourceRequest.h>
#include <WebCore/ResourceResponse.h>
#include <WebCore/SharedBuffer.h>
#include <atomic>
#include <memory>
#include <mutex>
#include <span>
#include <wtf/ASCIICType.h>
#include <wtf/URL.h>
#include <wtf/text/ASCIILiteral.h>
#include <wtf/text/AtomString.h>
#include <wtf/text/MakeString.h>
#include <wtf/text/StringBuilder.h>
#include <wtf/text/StringToIntegerConversion.h>
#include <wtf/threads/BinarySemaphore.h>

extern "C" {
typedef void* NetEngineHandle;
typedef void* ConnectionHandle;

NetEngineHandle net_engine_create();
void net_engine_destroy(NetEngineHandle handle);

struct ZNetHttpStreamCallbacks {
    void* user_data;
    void (*on_headers)(uint16_t status, const char* reason, size_t header_count, const char* const* header_names, const char* const* header_values, void* user_data);
    void (*on_data)(const uint8_t* chunk, size_t chunk_len, void* user_data);
    void (*on_complete)(bool keep_alive, void* user_data);
    bool (*is_cancelled)(void* user_data);
};

int32_t net_http_execute_streaming(
    NetEngineHandle engine_handle,
    uint64_t session_id,
    const char* method,
    const char* url,
    const char* const* header_names,
    const char* const* header_values,
    size_t header_count,
    const uint8_t* body,
    size_t body_len,
    uint64_t body_ring_id,
    const ZNetHttpStreamCallbacks* callbacks
);

int32_t net_cookie_jar_store(NetEngineHandle engine, uint64_t session_id, const char* url, const char* set_cookie_str);
int32_t net_cookie_jar_get_header(NetEngineHandle engine, uint64_t session_id, const char* url, char* out_buf, size_t max_len);
void net_cookie_jar_clear(NetEngineHandle engine, uint64_t session_id);
}

namespace WebKit {
using namespace WebCore;

struct StreamContext {
    Ref<NetworkDataTaskZNet> task;
    bool responseDispatched { false };
    bool completedDispatched { false };
    WTF::BinarySemaphore policySemaphore;
    std::atomic<WebCore::PolicyAction> policyAction { WebCore::PolicyAction::Ignore };
    std::atomic<bool> policyDispatched { false };
};

static NetEngineHandle sharedNetEngine()
{
    static NetEngineHandle s_engine = nullptr;
    static std::once_flag s_once;
    std::call_once(s_once, [] {
        s_engine = net_engine_create();
    });
    return s_engine;
}

NetworkDataTaskZNet::NetworkDataTaskZNet(NetworkSession& session, NetworkDataTaskClient& client, const NetworkLoadParameters& parameters)
    : NetworkDataTask(session, client, parameters.request, parameters.storedCredentialsPolicy, parameters.shouldClearReferrerOnHTTPSToHTTPRedirect, parameters.isMainFrameNavigation, parameters.isInitiatedByDedicatedWorker)
{
}

NetworkDataTaskZNet::~NetworkDataTaskZNet()
{
    cancel();
}

void NetworkDataTaskZNet::cancel()
{
    m_isCancelled = true;
    m_state = State::Canceling;
    if (auto* ctx = m_streamContext.load()) {
        ctx->policySemaphore.signal();
    }
    if (m_thread) {
        m_thread->waitForCompletion();
        m_thread = nullptr;
    }
    m_state = State::Completed;
}

void NetworkDataTaskZNet::resume()
{
    WTFLogAlways("NetworkDataTaskZNet::resume() called for %s", m_firstRequest.url().string().utf8().data());
    if (m_state != State::Suspended)
        return;

    m_state = State::Running;
    m_thread = Thread::create("ZNetFetcher"_s, [this, protectedThis = Ref { *this }] {
        startFetch();
    });
}

void NetworkDataTaskZNet::invalidateAndCancel()
{
    cancel();
}

NetworkDataTask::State NetworkDataTaskZNet::state() const
{
    return m_state;
}

void NetworkDataTaskZNet::startFetch()
{
    URL url = m_firstRequest.url();
    WTFLogAlways("NetworkDataTaskZNet::startFetch() started for %s", url.string().utf8().data());

    NetEngineHandle engine = sharedNetEngine();
    if (!engine) {
        RunLoop::mainSingleton().dispatch([this, protectedThis = Ref { *this }] {
            if (m_isCancelled) return;
            if (RefPtr client = this->client())
                client->didCompleteWithError(ResourceError(String(), 0, m_firstRequest.url(), "Failed to initialize z-net engine"_s));
        });
        m_state = State::Completed;
        return;
    }

    uint64_t sessionId = 0;
    if (auto* session = m_session.get())
        sessionId = session->sessionID().toUInt64();

    // 1. Prepare Request Headers
    Vector<CString> headerNames;
    Vector<CString> headerValues;
    Vector<const char*> headerNamePtrs;
    Vector<const char*> headerValPtrs;

    for (auto& header : m_firstRequest.httpHeaderFields()) {
        headerNames.append(header.key.utf8());
        headerValues.append(header.value.utf8());
    }

    headerNamePtrs.reserveInitialCapacity(headerNames.size());
    headerValPtrs.reserveInitialCapacity(headerValues.size());
    for (size_t i = 0; i < headerNames.size(); ++i) {
        headerNamePtrs.append(headerNames[i].data());
        headerValPtrs.append(headerValues[i].data());
    }

    // 2. Prepare Request Body (POST/PUT/FormData)
    Vector<uint8_t> bodyBytes;
    if (RefPtr body = m_firstRequest.httpBody()) {
        if (!body->isEmpty())
            bodyBytes = body->flatten();
    }

    // 3. Setup Streaming Callbacks & Flow Control Context
    auto context = WTF::makeUnique<StreamContext>(StreamContext { Ref { *this }, false, false, WTF::BinarySemaphore(), WebCore::PolicyAction::Ignore, false });
    m_streamContext.store(context.get());

    auto onHeadersCallback = [](uint16_t status, const char* reason, size_t headerCount, const char* const* names, const char* const* values, void* userData) {
        auto* ctx = static_cast<StreamContext*>(userData);
        if (!ctx || ctx->task->isCancelled())
            return;

        auto response = WTF::makeUnique<ResourceResponse>(URL { ctx->task->firstRequest().url() }, "text/html"_s, 0, "utf-8"_s);
        response->setHTTPStatusCode(status);
        if (reason)
            response->setHTTPStatusText(String::fromUTF8(reason));

        for (size_t i = 0; i < headerCount; ++i) {
            if (names && values && names[i] && values[i]) {
                response->setHTTPHeaderField(String::fromUTF8(names[i]), String::fromUTF8(values[i]));
            }
        }

        RunLoop::mainSingleton().dispatch([ctx, response = WTF::move(response)]() mutable {
            if (ctx->task->isCancelled()) {
                ctx->policyAction.store(WebCore::PolicyAction::Ignore);
                ctx->policyDispatched.store(true);
                ctx->policySemaphore.signal();
                return;
            }

            ctx->task->didReceiveResponse(WTF::move(*response), NegotiatedLegacyTLS::No, PrivateRelayed::No, std::nullopt, [ctx](WebCore::PolicyAction action) {
                ctx->policyAction.store(action);
                ctx->policyDispatched.store(true);
                ctx->policySemaphore.signal();
            });
        });

        // Block ZNetFetcher thread until WebKit's main thread completes PolicyAction evaluation
        ctx->policySemaphore.wait();
        ctx->responseDispatched = true;
    };

    auto onDataCallback = [](const uint8_t* chunk, size_t chunkLen, void* userData) {
        auto* ctx = static_cast<StreamContext*>(userData);
        if (!ctx || ctx->task->isCancelled() || !chunk || chunkLen == 0)
            return;
        if (ctx->policyAction.load() != WebCore::PolicyAction::Use)
            return;

        auto bodyData = SharedBuffer::create(std::span<const uint8_t>(chunk, chunkLen));
        RunLoop::mainSingleton().dispatch([protectedTask = ctx->task, bodyData = WTF::move(bodyData)]() mutable {
            if (protectedTask->isCancelled())
                return;
            if (RefPtr client = protectedTask->client())
                client->didReceiveData(bodyData.get());
        });
    };

    auto onCompleteCallback = [](bool /*keepAlive*/, void* userData) {
        auto* ctx = static_cast<StreamContext*>(userData);
        if (!ctx || ctx->completedDispatched)
            return;
        ctx->completedDispatched = true;

        RunLoop::mainSingleton().dispatch([protectedTask = ctx->task]() mutable {
            if (protectedTask->isCancelled())
                return;
            protectedTask->setCompleted();
            if (RefPtr client = protectedTask->client())
                client->didCompleteWithError(ResourceError());
        });
    };

    auto isCancelledCallback = [](void* userData) -> bool {
        auto* ctx = static_cast<StreamContext*>(userData);
        if (!ctx)
            return true;
        if (ctx->task->isCancelled())
            return true;
        if (ctx->policyDispatched.load() && ctx->policyAction.load() != WebCore::PolicyAction::Use)
            return true;
        return false;
    };

    ZNetHttpStreamCallbacks callbacks;
    callbacks.user_data = context.get();
    callbacks.on_headers = onHeadersCallback;
    callbacks.on_data = onDataCallback;
    callbacks.on_complete = onCompleteCallback;
    callbacks.is_cancelled = isCancelledCallback;

    CString methodStr = m_firstRequest.httpMethod().utf8();
    CString urlStr = m_firstRequest.url().string().utf8();

    int32_t res = net_http_execute_streaming(
        engine,
        sessionId,
        methodStr.data(),
        urlStr.data(),
        headerNamePtrs.isEmpty() ? nullptr : headerNamePtrs.span().data(),
        headerValPtrs.isEmpty() ? nullptr : headerValPtrs.span().data(),
        headerNamePtrs.size(),
        bodyBytes.isEmpty() ? nullptr : bodyBytes.span().data(),
        bodyBytes.size(),
        0, // body_ring_id
        &callbacks
    );

    m_streamContext.store(nullptr);

    if (res != 0 && !context->completedDispatched) {
        RunLoop::mainSingleton().dispatch([protectedTask = context->task]() mutable {
            if (protectedTask->isCancelled())
                return;
            protectedTask->setCompleted();
            if (RefPtr client = protectedTask->client())
                client->didCompleteWithError(ResourceError(String(), 0, protectedTask->firstRequest().url(), "Network request failed in z-net"_s));
        });
    }
}

} // namespace WebKit
