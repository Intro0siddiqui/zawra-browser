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

#if ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include <WebCore/CDMInstanceSession.h>
#include <WebCore/SharedBuffer.h>
#include <wtf/Forward.h>
#include <wtf/RefCounted.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
enum class CDMMessageType : uint8_t;
}

namespace Messages {
namespace RemoteCDMInstanceSession {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteCDMInstanceSession;
}

class UpdateKeyStatuses {
public:
    using Arguments = std::tuple<WebCore::CDMInstanceSession::KeyStatusVector>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceSession_UpdateKeyStatuses; }
    static constexpr bool isSync = false;

    explicit UpdateKeyStatuses(const WebCore::CDMInstanceSession::KeyStatusVector& keyStatuses)
        : m_arguments(keyStatuses)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::CDMInstanceSession::KeyStatusVector&> m_arguments;
};

class SendMessage {
public:
    using Arguments = std::tuple<WebCore::CDMMessageType, RefPtr<WebCore::SharedBuffer>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceSession_SendMessage; }
    static constexpr bool isSync = false;

    SendMessage(WebCore::CDMMessageType type, const RefPtr<WebCore::SharedBuffer>& message)
        : m_arguments(type, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::CDMMessageType, const RefPtr<WebCore::SharedBuffer>&> m_arguments;
};

class SessionIdChanged {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceSession_SessionIdChanged; }
    static constexpr bool isSync = false;

    explicit SessionIdChanged(const String& sessionId)
        : m_arguments(sessionId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

} // namespace RemoteCDMInstanceSession
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)
