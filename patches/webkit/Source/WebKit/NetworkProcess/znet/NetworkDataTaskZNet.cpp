#include "config.h"
#include "NetworkDataTaskZNet.h"

#include "AuthenticationManager.h"
#include "NetworkLoadParameters.h"
#include "NetworkSession.h"
#include <WebCore/CookieJar.h>
#include <WebCore/FormData.h>
#include <WebCore/HTTPHeaderNames.h>
#include <WebCore/HTTPParsers.h>
#include <WebCore/MIMETypeRegistry.h>
#include <WebCore/NetworkStorageSession.h>
#include <WebCore/ResourceError.h>
#include <WebCore/ResourceRequest.h>
#include <WebCore/ResourceResponse.h>
#include <WebCore/SameSiteInfo.h>
#include <WebCore/SecurityOrigin.h>
#include <WebCore/SharedBuffer.h>
#include <WebCore/ShouldRelaxThirdPartyCookieBlocking.h>
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
void net_engine_set_manage_cookies(NetEngineHandle handle, bool enable);

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

struct StreamContext : std::enable_shared_from_this<StreamContext> {
    explicit StreamContext(Ref<NetworkDataTaskZNet>&& task)
        : task(WTF::move(task))
    {
    }

    Ref<NetworkDataTaskZNet> task;
    std::atomic<bool> cancelled { false };
    bool responseDispatched { false };
    bool completedDispatched { false };
    WTF::BinarySemaphore policySemaphore;
    std::atomic<WebCore::PolicyAction> policyAction { WebCore::PolicyAction::Ignore };
    std::atomic<bool> policyDispatched { false };

    // Redirection tracking
    bool isRedirected { false };
    ResourceRequest redirectRequest;
    bool redirectRejected { false };
};

static NetEngineHandle sharedNetEngine()
{
    static NetEngineHandle s_engine = nullptr;
    static std::once_flag s_once;
    std::call_once(s_once, [] {
        s_engine = net_engine_create();
        if (s_engine)
            net_engine_set_manage_cookies(s_engine, false);
    });
    return s_engine;
}

static void applyStoredCookiesToRequest(NetworkSession* session, ResourceRequest& request)
{
    if (!session)
        return;
    auto* storageSession = session->networkStorageSession();
    if (!storageSession)
        return;
    auto [cookieHeader, secure] = storageSession->cookieRequestHeaderFieldValue(
        request.firstPartyForCookies(),
        SameSiteInfo::create(request),
        request.url(),
        std::nullopt,
        std::nullopt,
        request.url().protocolIs("https"_s) ? IncludeSecureCookies::Yes : IncludeSecureCookies::No,
        ApplyTrackingPrevention::Yes,
        ShouldRelaxThirdPartyCookieBlocking::No,
        IsKnownCrossSiteTracker::No
    );
    UNUSED_PARAM(secure);
    if (!cookieHeader.isEmpty())
        request.setHTTPHeaderField(HTTPHeaderName::Cookie, cookieHeader);
    else
        request.removeHTTPHeaderField(HTTPHeaderName::Cookie);
}

NetworkDataTaskZNet::NetworkDataTaskZNet(NetworkSession& session, NetworkDataTaskClient& client, const NetworkLoadParameters& parameters)
    : NetworkDataTask(session, client, parameters.request, parameters.storedCredentialsPolicy, parameters.shouldClearReferrerOnHTTPSToHTTPRedirect, parameters.isMainFrameNavigation, parameters.isInitiatedByDedicatedWorker)
    , m_shouldPreconnectOnly(parameters.shouldPreconnectOnly)
{
}

NetworkDataTaskZNet::~NetworkDataTaskZNet()
{
    cancel();
}

void NetworkDataTaskZNet::cancel()
{
    WTFLogAlways("NetworkDataTaskZNet::cancel() called for %s", m_firstRequest.url().string().utf8().data());
    m_isCancelled.store(true);
    m_state.store(State::Canceling);
    std::shared_ptr<StreamContext> ctx;
    {
        std::lock_guard<std::mutex> lock(m_streamContextMutex);
        ctx = m_streamContext;
    }
    if (ctx) {
        ctx->cancelled.store(true);
        ctx->policySemaphore.signal();
    }
    if (m_thread) {
        if (m_thread.get() != &Thread::currentSingleton())
            m_thread->waitForCompletion();
        m_thread = nullptr;
    }
    m_state.store(State::Completed);
}

void NetworkDataTaskZNet::resume()
{
    WTFLogAlways("NetworkDataTaskZNet::resume() called for %s, preconnectOnly=%d",
        m_firstRequest.url().string().utf8().data(), m_shouldPreconnectOnly == PreconnectOnly::Yes);
    if (m_state.load() != State::Suspended)
        return;

    if (m_shouldPreconnectOnly == PreconnectOnly::Yes) {
        WTFLogAlways("NetworkDataTaskZNet: Handling PreconnectOnly task for %s", m_firstRequest.url().string().utf8().data());
        m_state.store(State::Completed);
        RunLoop::mainSingleton().dispatch([this, protectedThis = Ref { *this }] {
            if (m_isCancelled.load())
                return;
            if (RefPtr client = this->client())
                client->didCompleteWithError(ResourceError());
        });
        return;
    }

    // Cookie synchronization: query WebKit's NetworkStorageSession before launch
    applyStoredCookiesToRequest(networkSession(), m_firstRequest);

    m_state.store(State::Running);
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
    return m_state.load();
}

void NetworkDataTaskZNet::startFetch()
{
    NetEngineHandle engine = sharedNetEngine();
    if (!engine) {
        RunLoop::mainSingleton().dispatch([this, protectedThis = Ref { *this }] {
            if (m_isCancelled.load()) return;
            if (RefPtr client = this->client())
                client->didCompleteWithError(ResourceError(String(), 0, m_firstRequest.url(), "Failed to initialize z-net engine"_s));
        });
        m_state.store(State::Completed);
        return;
    }

    uint64_t sessionId = 0;
    if (auto* session = networkSession())
        sessionId = session->sessionID().toUInt64();

    unsigned redirectCount = 0;
    const unsigned maxRedirects = 20;

    while (!m_isCancelled.load() && m_state.load() != State::Canceling) {
        URL url = m_firstRequest.url();
        WTFLogAlways("NetworkDataTaskZNet::startFetch() fetching %s", url.string().utf8().data());

        // 1. Prepare Request Headers
        Vector<CString> headerNames;
        Vector<CString> headerValues;
        Vector<const char*> headerNamePtrs;
        Vector<const char*> headerValPtrs;

        bool isChrome134UA = false;
        bool hasSecChUa = false;
        bool hasSecChUaMobile = false;
        bool hasSecChUaPlatform = false;

        for (auto& header : m_firstRequest.httpHeaderFields()) {
            if (equalLettersIgnoringASCIICase(header.key, "user-agent"_s) && header.value.contains("Chrome/134."_s))
                isChrome134UA = true;
            else if (equalLettersIgnoringASCIICase(header.key, "sec-ch-ua"_s))
                hasSecChUa = true;
            else if (equalLettersIgnoringASCIICase(header.key, "sec-ch-ua-mobile"_s))
                hasSecChUaMobile = true;
            else if (equalLettersIgnoringASCIICase(header.key, "sec-ch-ua-platform"_s))
                hasSecChUaPlatform = true;

            headerNames.append(header.key.utf8());
            headerValues.append(header.value.utf8());
        }

        if (url.protocolIs("https"_s) && isChrome134UA) {
            if (!hasSecChUa) {
                headerNames.append(String("sec-ch-ua"_s).utf8());
                headerValues.append(String("\"Chromium\";v=\"134\", \"Not:A-Brand\";v=\"24\", \"Google Chrome\";v=\"134\""_s).utf8());
            }
            if (!hasSecChUaMobile) {
                headerNames.append(String("sec-ch-ua-mobile"_s).utf8());
                headerValues.append(String("?0"_s).utf8());
            }
            if (!hasSecChUaPlatform) {
                headerNames.append(String("sec-ch-ua-platform"_s).utf8());
                headerValues.append(String("\"Linux\""_s).utf8());
            }
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
        auto context = std::make_shared<StreamContext>(Ref { *this });
        {
            std::lock_guard<std::mutex> lock(m_streamContextMutex);
            m_streamContext = context;
        }

        auto onHeadersCallback = [](uint16_t status, const char* reason, size_t headerCount, const char* const* names, const char* const* values, void* userData) {
            WTFLogAlways("NetworkDataTaskZNet: onHeadersCallback status=%u, count=%zu", status, headerCount);
            auto* rawCtx = static_cast<StreamContext*>(userData);
            if (!rawCtx || rawCtx->cancelled.load() || rawCtx->task->isCancelled())
                return;
            auto ctx = rawCtx->shared_from_this();

            auto response = WTF::makeUnique<ResourceResponse>();
            response->setURL(URL { ctx->task->firstRequest().url() });
            response->setHTTPStatusCode(status);
            if (reason)
                response->setHTTPStatusText(String::fromLatin1(reason));
            response->setHTTPVersion("HTTP/1.1"_s);

            long long expectedLength = -1;
            String contentType;

            for (size_t i = 0; i < headerCount; ++i) {
                if (names && values && names[i] && values[i]) {
                    String key = String::fromLatin1(names[i]);
                    String val = String::fromLatin1(values[i]);
                    if (equalLettersIgnoringASCIICase(key, "content-type"_s))
                        contentType = val;
                    else if (equalLettersIgnoringASCIICase(key, "content-length"_s)) {
                        if (auto len = parseContentLength(val))
                            expectedLength = static_cast<long long>(*len);
                    }
                    response->addHTTPHeaderField(WTF::move(key), WTF::move(val));
                }
            }

            if (!contentType.isEmpty()) {
                response->setMimeType(extractMIMETypeFromMediaType(contentType));
                response->setTextEncodingName(extractCharsetFromMediaType(contentType).toString());
            }
            if (response->mimeType().isEmpty()) {
                response->setMimeType(MIMETypeRegistry::mimeTypeForPath(response->url().path()));
                if (response->mimeType().isEmpty())
                    response->setMimeType("text/html"_s);
            }
            response->setExpectedContentLength(expectedLength);
            WTFLogAlways("NetworkDataTaskZNet: onHeadersCallback url=%s mimeType=%s textEncoding=%s expectedLength=%lld httpVersion=%s",
                response->url().string().utf8().data(), response->mimeType().utf8().data(), response->textEncodingName().utf8().data(),
                response->expectedContentLength(), response->httpVersion().utf8().data());

            String location = response->httpHeaderField(HTTPHeaderName::Location);
            bool isRedirect = (status >= 300 && status < 400 && !location.isEmpty());

            RunLoop::mainSingleton().dispatch([ctx, response = WTF::move(response), isRedirect, location = WTF::move(location)]() mutable {
                if (ctx->cancelled.load() || ctx->task->isCancelled()) {
                    if (isRedirect)
                        ctx->redirectRejected = true;
                    ctx->policyAction.store(WebCore::PolicyAction::Ignore);
                    ctx->policyDispatched.store(true);
                    ctx->policySemaphore.signal();
                    return;
                }

                // Two-way cookie sync: synchronize any Set-Cookie headers into WebKit's NetworkStorageSession
                if (auto* session = ctx->task->networkSession()) {
                    if (auto* storageSession = session->networkStorageSession()) {
                        for (auto& header : response->httpHeaderFields()) {
                            if (equalLettersIgnoringASCIICase(header.key, "set-cookie"_s)) {
                                storageSession->setCookiesFromDOM(
                                    ctx->task->firstRequest().firstPartyForCookies(),
                                    SameSiteInfo(),
                                    response->url(),
                                    std::nullopt,
                                    std::nullopt,
                                    ApplyTrackingPrevention::No,
                                    RequiresScriptTrackingPrivacy::No,
                                    header.value,
                                    ShouldRelaxThirdPartyCookieBlocking::No,
                                    IsKnownCrossSiteTracker::No
                                );
                            }
                        }
                    }
                }

                if (isRedirect) {
                    URL redirectURL = URL(ctx->task->firstRequest().url(), location);
                    if (!redirectURL.hasFragmentIdentifier() && ctx->task->firstRequest().url().hasFragmentIdentifier())
                        redirectURL.setFragmentIdentifier(ctx->task->firstRequest().url().fragmentIdentifier());

                    ResourceRequest redirectRequest = ctx->task->firstRequest();
                    redirectRequest.setURL(WTF::move(redirectURL));

                    // RFC 7231 method rewriting:
                    // 303 See Other: Always switch to GET and drop payload
                    // 301 Moved Permanently / 302 Found: If POST, switch to GET and drop payload
                    if (response->httpStatusCode() == 303 || 
                        ((response->httpStatusCode() == 301 || response->httpStatusCode() == 302) && 
                         equalLettersIgnoringASCIICase(redirectRequest.httpMethod(), "post"_s))) {
                        redirectRequest.setHTTPMethod("GET"_s);
                        redirectRequest.setHTTPBody(nullptr);
                        redirectRequest.clearHTTPContentType();
                    }

                    // Cross-origin redirect protection: strip sensitive authorization & origin headers
                    bool isCrossOrigin = !protocolHostAndPortAreEqual(ctx->task->firstRequest().url(), redirectRequest.url());
                    if (isCrossOrigin) {
                        redirectRequest.clearHTTPAuthorization();
                        redirectRequest.clearHTTPOrigin();
                    }

                    // HTTPS to HTTP downgrade: strip referer
                    if (!redirectRequest.url().protocolIs("https"_s) && protocolIs(redirectRequest.httpReferrer(), "https"_s))
                        redirectRequest.clearHTTPReferrer();

                    if (RefPtr client = ctx->task->client()) {
                        client->willPerformHTTPRedirection(WTF::move(*response), WTF::move(redirectRequest), [ctx](ResourceRequest&& newRequest) {
                            if (!ctx->cancelled.load() && !ctx->task->isCancelled()) {
                                if (newRequest.isNull()) {
                                    ctx->redirectRejected = true;
                                } else {
                                    // Re-query WebKit's NetworkStorageSession for the redirect target URL on the main thread
                                    // after Set-Cookie headers from the 3xx response have been synchronized.
                                    bool shouldIncludeCookies = ctx->task->m_storedCredentialsPolicy == StoredCredentialsPolicy::Use
                                        && newRequest.allowCookies();
                                    String cookieHeader;
                                    if (shouldIncludeCookies) {
                                        if (auto* session = ctx->task->networkSession()) {
                                            if (auto* storageSession = session->networkStorageSession()) {
                                                auto [headerValue, secure] = storageSession->cookieRequestHeaderFieldValue(
                                                    newRequest.firstPartyForCookies(),
                                                    SameSiteInfo::create(newRequest),
                                                    newRequest.url(),
                                                    std::nullopt,
                                                    std::nullopt,
                                                    newRequest.url().protocolIs("https"_s) ? IncludeSecureCookies::Yes : IncludeSecureCookies::No,
                                                    ApplyTrackingPrevention::Yes,
                                                    ShouldRelaxThirdPartyCookieBlocking::No,
                                                    IsKnownCrossSiteTracker::No
                                                );
                                                cookieHeader = WTF::move(headerValue);
                                            }
                                        }
                                    }
                                    if (!cookieHeader.isEmpty())
                                        newRequest.setHTTPHeaderField(HTTPHeaderName::Cookie, cookieHeader);
                                    else
                                        newRequest.removeHTTPHeaderField(HTTPHeaderName::Cookie);

                                    ctx->isRedirected = true;
                                    ctx->redirectRequest = WTF::move(newRequest);
                                }
                            } else {
                                ctx->redirectRejected = true;
                            }
                            ctx->policyAction.store(WebCore::PolicyAction::Ignore);
                            ctx->policyDispatched.store(true);
                            ctx->policySemaphore.signal();
                        });
                    } else {
                        ctx->redirectRejected = true;
                        ctx->policyAction.store(WebCore::PolicyAction::Ignore);
                        ctx->policyDispatched.store(true);
                        ctx->policySemaphore.signal();
                    }
                    return;
                }

                // Normal (non-redirect) response: dispatch to WebKit's didReceiveResponse
                ctx->task->didReceiveResponse(WTF::move(*response), NegotiatedLegacyTLS::No, PrivateRelayed::No, std::nullopt, [ctx](WebCore::PolicyAction action) {
                    WTFLogAlways("NetworkDataTaskZNet: didReceiveResponse callback action=%u", static_cast<unsigned>(action));
                    ctx->policyAction.store(action);
                    ctx->policyDispatched.store(true);
                    ctx->policySemaphore.signal();
                });
            });

            // Block ZNetFetcher thread until WebKit's main thread completes evaluation
            ctx->policySemaphore.wait();
            ctx->responseDispatched = true;
        };

        auto onDataCallback = [](const uint8_t* chunk, size_t chunkLen, void* userData) {
            auto* ctx = static_cast<StreamContext*>(userData);
            if (!ctx || ctx->cancelled.load() || ctx->task->isCancelled() || !chunk || chunkLen == 0)
                return;
            if (ctx->policyAction.load() != WebCore::PolicyAction::Use)
                return;

            auto bodyData = SharedBuffer::create(std::span<const uint8_t>(chunk, chunkLen));
            RunLoop::mainSingleton().dispatch([protectedTask = Ref { ctx->task.get() }, bodyData = WTF::move(bodyData)]() mutable {
                if (protectedTask->isCancelled())
                    return;
                if (RefPtr client = protectedTask->client())
                    client->didReceiveData(bodyData.get());
            });
        };

        auto onCompleteCallback = [](bool /*keepAlive*/, void* userData) {
            WTFLogAlways("NetworkDataTaskZNet: onCompleteCallback");
            auto* ctx = static_cast<StreamContext*>(userData);
            if (!ctx || ctx->completedDispatched)
                return;
            ctx->completedDispatched = true;

            if (ctx->isRedirected) {
                // Intermediate redirect complete; do not dispatch didCompleteWithError to client
                return;
            }

            RunLoop::mainSingleton().dispatch([protectedTask = Ref { ctx->task.get() }]() mutable {
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
            if (ctx->cancelled.load() || ctx->task->isCancelled()) {
                WTFLogAlways("NetworkDataTaskZNet: isCancelled true: task->isCancelled()");
                return true;
            }
            if (ctx->isRedirected)
                return true; // Stop reading 3xx body early and proceed to fetch the redirect target
            if (ctx->policyDispatched.load() && ctx->policyAction.load() != WebCore::PolicyAction::Use) {
                WTFLogAlways("NetworkDataTaskZNet: isCancelled true: policyAction=%u", static_cast<unsigned>(ctx->policyAction.load()));
                return true;
            }
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

        WTFLogAlways("NetworkDataTaskZNet: calling net_http_execute_streaming for %s", urlStr.data());
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
        WTFLogAlways("NetworkDataTaskZNet: net_http_execute_streaming returned %d", res);

        {
            std::lock_guard<std::mutex> lock(m_streamContextMutex);
            m_streamContext.reset();
        }

        if (m_isCancelled.load() || m_state.load() == State::Canceling) {
            context->cancelled.store(true);
            break;
        }

        if (context->isRedirected) {
            if (context->redirectRejected) {
                m_state.store(State::Completed);
                break;
            }
            if (++redirectCount > maxRedirects) {
                RunLoop::mainSingleton().dispatch([protectedTask = Ref { *this }] {
                    if (protectedTask->isCancelled())
                        return;
                    protectedTask->setCompleted();
                    if (RefPtr client = protectedTask->client())
                        client->didCompleteWithError(ResourceError(String(), 0, protectedTask->firstRequest().url(), "Too many redirects"_s));
                });
                m_state.store(State::Completed);
                break;
            }

            m_firstRequest = WTF::move(context->redirectRequest);
            WTFLogAlways("NetworkDataTaskZNet: Following redirect #%u to %s", redirectCount, m_firstRequest.url().string().utf8().data());
            continue; // Loop to fetch redirected URL!
        }

        if (!context->completedDispatched) {
            context->completedDispatched = true;
            RunLoop::mainSingleton().dispatch([protectedTask = Ref { context->task.get() }, res]() mutable {
                if (protectedTask->isCancelled())
                    return;
                protectedTask->setCompleted();
                if (RefPtr client = protectedTask->client()) {
                    if (res == 0) {
                        WTFLogAlways("NetworkDataTaskZNet: dispatching didCompleteWithError(success)");
                        client->didCompleteWithError(ResourceError());
                    } else {
                        client->didCompleteWithError(ResourceError(String(), 0, protectedTask->firstRequest().url(), "Network request failed in z-net"_s));
                    }
                }
            });
        }

        break; // Request done, exit loop
    }
}

} // namespace WebKit
