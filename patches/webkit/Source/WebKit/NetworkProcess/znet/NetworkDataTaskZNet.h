#pragma once

#include "NetworkDataTask.h"
#include <atomic>
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

    bool isCancelled() const { return m_isCancelled; }
    void setCompleted() { m_state = State::Completed; }

private:
    NetworkDataTaskZNet(NetworkSession&, NetworkDataTaskClient&, const NetworkLoadParameters&);

    void cancel() override;
    void resume() override;
    void invalidateAndCancel() override;
    NetworkDataTask::State state() const override;

    void startFetch();

    State m_state { State::Suspended };
    RefPtr<Thread> m_thread;
    bool m_isCancelled { false };
    std::atomic<StreamContext*> m_streamContext { nullptr };
};

} // namespace WebKit
