#pragma once

#include "NetworkDataTask.h"
#include "NetworkLoadParameters.h"
#include <atomic>
#include <memory>
#include <mutex>
#include <wtf/RunLoop.h>
#include <wtf/Threading.h>

namespace WebKit {

struct StreamContext;

class NetworkDataTaskZNet final : public NetworkDataTask {
public:
    static Ref<NetworkDataTask> create(NetworkSession& session, NetworkDataTaskClient& client, const NetworkLoadParameters& parameters)
    {
        return adoptRef(*new NetworkDataTaskZNet(session, client, parameters));
    }

    ~NetworkDataTaskZNet();

    bool isCancelled() const { return m_isCancelled.load(); }
    void setCompleted() { m_state.store(State::Completed); }

private:
    NetworkDataTaskZNet(NetworkSession&, NetworkDataTaskClient&, const NetworkLoadParameters&);

    void cancel() override;
    void resume() override;
    void invalidateAndCancel() override;
    NetworkDataTask::State state() const override;

    void startFetch();

    std::atomic<State> m_state { State::Suspended };
    RefPtr<Thread> m_thread;
    std::atomic<bool> m_isCancelled { false };
    PreconnectOnly m_shouldPreconnectOnly { PreconnectOnly::No };
    std::mutex m_streamContextMutex;
    std::shared_ptr<StreamContext> m_streamContext;
};

} // namespace WebKit
