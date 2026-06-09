#pragma once

#include "NetworkDataTask.h"
#include <atomic>
#include <wtf/RunLoop.h>
#include <wtf/Threading.h>

namespace WebKit {

class NetworkDataTaskZNet final : public NetworkDataTask {
public:
    static Ref<NetworkDataTask> create(NetworkSession& session, NetworkDataTaskClient& client, const NetworkLoadParameters& parameters)
    {
        return adoptRef(*new NetworkDataTaskZNet(session, client, parameters));
    }

    ~NetworkDataTaskZNet();

private:
    NetworkDataTaskZNet(NetworkSession&, NetworkDataTaskClient&, const NetworkLoadParameters&);

    void cancel() override;
    void resume() override;
    void invalidateAndCancel() override;
    NetworkDataTask::State state() const override;

    void startFetch();

    // m_state and m_isCancelled are touched concurrently from the main thread
    // (cancel / resume / state()) and from the worker thread spawned in
    // resume() (startFetch). They must be std::atomic to avoid a C++ data
    // race / undefined behavior. NetworkDataTask::State is a trivially
    // copyable enum class, so std::atomic<State> is well-defined.
    std::atomic<State> m_state { State::Suspended };
    RefPtr<Thread> m_thread;
    std::atomic<bool> m_isCancelled { false };
};

} // namespace WebKit
