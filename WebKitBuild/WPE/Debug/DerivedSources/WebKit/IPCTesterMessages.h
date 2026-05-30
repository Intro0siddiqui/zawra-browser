/*
 * Copyright (C) 2021-2023 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(IPC_TESTING_API)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "IPCConnectionTesterIdentifier.h"
#include "IPCSemaphore.h"
#include "IPCStreamTesterIdentifier.h"
#include "MessageNames.h"
#include "StreamServerConnection.h"
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace IPCTester {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::IPCTester;
}

class StartMessageTesting {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::IPCTester_StartMessageTesting; }
    static constexpr bool isSync = false;

    explicit StartMessageTesting(const String& driverName)
        : m_arguments(driverName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class StopMessageTesting {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::IPCTester_StopMessageTesting; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class CreateStreamTester {
public:
    using Arguments = std::tuple<WebKit::IPCStreamTesterIdentifier, IPC::StreamServerConnection::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::IPCTester_CreateStreamTester; }
    static constexpr bool isSync = false;

    CreateStreamTester(const WebKit::IPCStreamTesterIdentifier& identifier, IPC::StreamServerConnection::Handle&& serverConnection)
        : m_arguments(identifier, WTFMove(serverConnection))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::IPCStreamTesterIdentifier&, IPC::StreamServerConnection::Handle&&> m_arguments;
};

class ReleaseStreamTester {
public:
    using Arguments = std::tuple<WebKit::IPCStreamTesterIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::IPCTester_ReleaseStreamTester; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ReleaseStreamTester(const WebKit::IPCStreamTesterIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::IPCStreamTesterIdentifier&> m_arguments;
};

class CreateConnectionTester {
public:
    using Arguments = std::tuple<WebKit::IPCConnectionTesterIdentifier, IPC::Connection::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::IPCTester_CreateConnectionTester; }
    static constexpr bool isSync = false;

    CreateConnectionTester(const WebKit::IPCConnectionTesterIdentifier& identifier, IPC::Connection::Handle&& connection)
        : m_arguments(identifier, WTFMove(connection))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::IPCConnectionTesterIdentifier&, IPC::Connection::Handle&&> m_arguments;
};

class CreateConnectionTesterAndSendAsyncMessages {
public:
    using Arguments = std::tuple<WebKit::IPCConnectionTesterIdentifier, IPC::Connection::Handle, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::IPCTester_CreateConnectionTesterAndSendAsyncMessages; }
    static constexpr bool isSync = false;

    CreateConnectionTesterAndSendAsyncMessages(const WebKit::IPCConnectionTesterIdentifier& identifier, IPC::Connection::Handle&& connection, uint32_t messageCount)
        : m_arguments(identifier, WTFMove(connection), messageCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::IPCConnectionTesterIdentifier&, IPC::Connection::Handle&&, uint32_t> m_arguments;
};

class ReleaseConnectionTester {
public:
    using Arguments = std::tuple<WebKit::IPCConnectionTesterIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::IPCTester_ReleaseConnectionTester; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ReleaseConnectionTester(const WebKit::IPCConnectionTesterIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::IPCConnectionTesterIdentifier&> m_arguments;
};

class SendSameSemaphoreBack {
public:
    using Arguments = std::tuple<IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::IPCTester_SendSameSemaphoreBack; }
    static constexpr bool isSync = false;

    explicit SendSameSemaphoreBack(const IPC::Semaphore& semaphore)
        : m_arguments(semaphore)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::Semaphore&> m_arguments;
};

class SendSemaphoreBackAndSignalProtocol {
public:
    using Arguments = std::tuple<IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::IPCTester_SendSemaphoreBackAndSignalProtocol; }
    static constexpr bool isSync = false;

    explicit SendSemaphoreBackAndSignalProtocol(const IPC::Semaphore& semaphore)
        : m_arguments(semaphore)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::Semaphore&> m_arguments;
};

class SendAsyncMessageToReceiver {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::IPCTester_SendAsyncMessageToReceiver; }
    static constexpr bool isSync = false;

    explicit SendAsyncMessageToReceiver(uint32_t arg0)
        : m_arguments(arg0)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

} // namespace IPCTester
} // namespace Messages

#endif // ENABLE(IPC_TESTING_API)
