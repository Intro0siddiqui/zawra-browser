#include "config.h"
#include "NetworkDataTaskZNet.h"

#include "AuthenticationManager.h"
#include "NetworkLoadParameters.h"
#include "NetworkSession.h"
#include <WebCore/ResourceError.h>
#include <WebCore/ResourceRequest.h>
#include <WebCore/ResourceResponse.h>
#include <WebCore/SharedBuffer.h>
#include <wtf/ASCIICType.h>
#include <wtf/URL.h>
#include <wtf/text/AtomString.h>
#include <wtf/text/StringBuilder.h>
#include <wtf/text/StringToIntegerConversion.h>

extern "C" {
typedef void* NetEngineHandle;
typedef void* ConnectionHandle;
NetEngineHandle net_engine_create();
void net_engine_destroy(NetEngineHandle handle);
ConnectionHandle net_connect(NetEngineHandle engine_handle, const char* host, uint16_t port);
int32_t net_close(NetEngineHandle engine_handle, ConnectionHandle conn_handle);
int32_t net_read(NetEngineHandle engine_handle, ConnectionHandle conn_handle, uint8_t* buffer, size_t buffer_len, size_t* bytes_read);
int32_t net_write(NetEngineHandle engine_handle, ConnectionHandle conn_handle, const uint8_t* data, size_t data_len, size_t* bytes_written);
int32_t net_poll(NetEngineHandle engine_handle, int32_t timeout_ms);
}

namespace WebKit {
using namespace WebCore;

NetworkDataTaskZNet::NetworkDataTaskZNet(NetworkSession& session, NetworkDataTaskClient& client, const NetworkLoadParameters& parameters)
    : NetworkDataTask(session, client, parameters.request, parameters.storedCredentialsPolicy, parameters.shouldClearReferrerOnHTTPSToHTTPRedirect, parameters.isMainFrameNavigation)
{
}

NetworkDataTaskZNet::~NetworkDataTaskZNet()
{
    cancel();
}

void NetworkDataTaskZNet::cancel()
{
    m_isCancelled.store(true, std::memory_order_release);
    m_state.store(State::Canceling, std::memory_order_release);
    if (m_thread) {
        m_thread->waitForCompletion();
        m_thread = nullptr;
    }
    m_state.store(State::Completed, std::memory_order_release);
}

void NetworkDataTaskZNet::resume()
{
    WTFLogAlways("NetworkDataTaskZNet::resume() called for %s", m_firstRequest.url().string().utf8().data());
    if (m_state.load(std::memory_order_acquire) != State::Suspended)
        return;

    m_state.store(State::Running, std::memory_order_release);
    m_thread = Thread::create("ZNetFetcher", [this, protectedThis = Ref { *this }] {
        startFetch();
    });
}

void NetworkDataTaskZNet::invalidateAndCancel()
{
    cancel();
}

NetworkDataTask::State NetworkDataTaskZNet::state() const
{
    return m_state.load(std::memory_order_acquire);
}

void NetworkDataTaskZNet::startFetch()
{
    URL url = m_firstRequest.url();
    WTFLogAlways("NetworkDataTaskZNet::startFetch() started for %s", url.string().utf8().data());
    String host = url.host().toString();
    uint16_t port = url.port().value_or(url.protocolIs("https"_s) ? 443 : 80);
    String path = url.path().toString();
    if (path.isEmpty())
        path = "/"_s;
    if (url.hasQuery())
        path = path + "?"_s + url.query().toString();

    NetEngineHandle engine = net_engine_create();
    if (!engine) {
        RunLoop::main().dispatch([this, protectedThis = Ref { *this }] {
            if (m_isCancelled.load(std::memory_order_acquire)) return;
            if (client())
                client()->didCompleteWithError(ResourceError(String(), 0, m_firstRequest.url(), "Failed to create net engine"_s));
        });
        m_state.store(State::Completed, std::memory_order_release);
        return;
    }

    ConnectionHandle conn = net_connect(engine, host.utf8().data(), port);
    if (!conn) {
        net_engine_destroy(engine);
        RunLoop::main().dispatch([this, protectedThis = Ref { *this }] {
            if (m_isCancelled.load(std::memory_order_acquire)) return;
            if (client())
                client()->didCompleteWithError(ResourceError(String(), 0, m_firstRequest.url(), "Failed to connect to host"_s));
        });
        m_state.store(State::Completed, std::memory_order_release);
        return;
    }

    // 2. Format Request
    StringBuilder requestBuilder;
    requestBuilder.append(m_firstRequest.httpMethod(), " ", path, " HTTP/1.1\r\n");
    requestBuilder.append("Host: ", host, "\r\n");
    for (auto& header : m_firstRequest.httpHeaderFields()) {
        requestBuilder.append(header.key, ": ", header.value, "\r\n");
    }
    if (!m_firstRequest.httpHeaderFields().contains("Connection"_s)) {
        requestBuilder.append("Connection: close\r\n");
    }
    requestBuilder.append("\r\n");

    CString requestStr = requestBuilder.toString().utf8();
    size_t totalWritten = 0;
    while (totalWritten < requestStr.length() && !m_isCancelled.load(std::memory_order_acquire)) {
        size_t written = 0;
        int32_t res = net_write(engine, conn,
            reinterpret_cast<const uint8_t*>(requestStr.data()) + totalWritten,
            requestStr.length() - totalWritten, &written);
        if (res != 0)
            break;
        totalWritten += written;
    }

    // 3. Read loop
    Vector<uint8_t> responseData;
    uint8_t buffer[8192];
    size_t headerEnd = WTF::notFound;

    while (!m_isCancelled.load(std::memory_order_acquire)) {
        size_t bytesRead = 0;
        int32_t res = net_read(engine, conn, buffer, sizeof(buffer), &bytesRead);
        if (res != 0 || bytesRead == 0) {
            break; // EOF or error
        }

        responseData.append(buffer, bytesRead);

        if (headerEnd == WTF::notFound) {
            for (size_t i = 0; i + 3 < responseData.size(); ++i) {
                if (responseData[i] == '\r' && responseData[i+1] == '\n' && responseData[i+2] == '\r' && responseData[i+3] == '\n') {
                    headerEnd = i + 4;
                    break;
                }
            }

            if (headerEnd != WTF::notFound) {
                // Parse headers
                String headerStr = String::fromUTF8(responseData.data(), headerEnd);
                auto lines = headerStr.split("\r\n"_s);
                if (!lines.isEmpty()) {
                    auto statusLine = lines[0];
                    auto statusParts = statusLine.split(" "_s);
                    int status = 200;
                    String statusText = "OK"_s;
                    if (statusParts.size() >= 2) {
                        status = parseIntegerAllowingTrailingJunk<int>(statusParts[1]).value_or(200);
                    }
                    if (statusParts.size() >= 3) {
                        statusText = statusParts[2];
                    }

                    auto response = makeUnique<ResourceResponse>(url, "text/html"_s, 0, "utf-8"_s);
                    response->setHTTPStatusCode(status);
                    response->setHTTPStatusText(AtomString(statusText));

                    for (size_t i = 1; i < lines.size(); ++i) {
                        auto line = lines[i];
                        if (line.isEmpty()) continue;
                        size_t colon = line.find(':');
                        if (colon == WTF::notFound) continue;
                        auto name = line.left(colon).simplifyWhiteSpace(isASCIIWhitespace<UChar>);
                        auto value = line.substring(colon + 1).simplifyWhiteSpace(isASCIIWhitespace<UChar>);
                        response->setHTTPHeaderField(name, value);
                    }

                    RunLoop::main().dispatch([this, protectedThis = Ref { *this }, rawResponse = response.release()] {
                        std::unique_ptr<ResourceResponse> response(rawResponse);
                        if (m_isCancelled.load(std::memory_order_acquire)) return;
                        didReceiveResponse(WTFMove(*response), NegotiatedLegacyTLS::No, PrivateRelayed::No, [](WebCore::PolicyAction) {});
                    });
                }

                // If there's initial body data read, dispatch it
                if (responseData.size() > headerEnd) {
                    auto bodyData = SharedBuffer::create(responseData.data() + headerEnd, responseData.size() - headerEnd);
                    RunLoop::main().dispatch([this, protectedThis = Ref { *this }, bodyData = WTFMove(bodyData)] {
                        if (m_isCancelled.load(std::memory_order_acquire)) return;
                        if (client())
                            client()->didReceiveData(bodyData);
                    });
                }
            }
        } else {
            // Streaming body data
            auto bodyData = SharedBuffer::create(buffer, bytesRead);
            RunLoop::main().dispatch([this, protectedThis = Ref { *this }, bodyData = WTFMove(bodyData)] {
                if (m_isCancelled.load(std::memory_order_acquire)) return;
                if (client())
                    client()->didReceiveData(bodyData);
            });
        }
    }

    net_close(engine, conn);
    net_engine_destroy(engine);

    RunLoop::main().dispatch([this, protectedThis = Ref { *this }] {
        if (m_isCancelled.load(std::memory_order_acquire)) return;
        m_state.store(State::Completed, std::memory_order_release);
        if (client())
            client()->didCompleteWithError(ResourceError());
    });
}

} // namespace WebKit
