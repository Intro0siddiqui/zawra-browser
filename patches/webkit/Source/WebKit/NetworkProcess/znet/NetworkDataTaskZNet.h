#pragma once

#include "NetworkDataTask.h"
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

    State m_state { State::Suspended };
    RefPtr<Thread> m_thread;
    bool m_isCancelled { false };
};

} // namespace WebKit
