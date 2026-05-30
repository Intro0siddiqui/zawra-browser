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

#if ENABLE(WEB_RTC)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "DataReference.h"
#include "MessageNames.h"
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
enum class RTCDataChannelState : uint8_t;
enum class RTCErrorDetailType : uint8_t;
struct RTCDataChannelIdentifier;
}

namespace Messages {
namespace RTCDataChannelRemoteManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RTCDataChannelRemoteManager;
}

class SendData {
public:
    using Arguments = std::tuple<WebCore::RTCDataChannelIdentifier, bool, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::RTCDataChannelRemoteManager_SendData; }
    static constexpr bool isSync = false;

    SendData(const WebCore::RTCDataChannelIdentifier& source, bool isRaw, const IPC::DataReference& text)
        : m_arguments(source, isRaw, text)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RTCDataChannelIdentifier&, bool, const IPC::DataReference&> m_arguments;
};

class Close {
public:
    using Arguments = std::tuple<WebCore::RTCDataChannelIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RTCDataChannelRemoteManager_Close; }
    static constexpr bool isSync = false;

    explicit Close(const WebCore::RTCDataChannelIdentifier& source)
        : m_arguments(source)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RTCDataChannelIdentifier&> m_arguments;
};

class ChangeReadyState {
public:
    using Arguments = std::tuple<WebCore::RTCDataChannelIdentifier, WebCore::RTCDataChannelState>;

    static IPC::MessageName name() { return IPC::MessageName::RTCDataChannelRemoteManager_ChangeReadyState; }
    static constexpr bool isSync = false;

    ChangeReadyState(const WebCore::RTCDataChannelIdentifier& handler, WebCore::RTCDataChannelState state)
        : m_arguments(handler, state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RTCDataChannelIdentifier&, WebCore::RTCDataChannelState> m_arguments;
};

class ReceiveData {
public:
    using Arguments = std::tuple<WebCore::RTCDataChannelIdentifier, bool, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::RTCDataChannelRemoteManager_ReceiveData; }
    static constexpr bool isSync = false;

    ReceiveData(const WebCore::RTCDataChannelIdentifier& handler, bool isRaw, const IPC::DataReference& data)
        : m_arguments(handler, isRaw, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RTCDataChannelIdentifier&, bool, const IPC::DataReference&> m_arguments;
};

class DetectError {
public:
    using Arguments = std::tuple<WebCore::RTCDataChannelIdentifier, WebCore::RTCErrorDetailType, String>;

    static IPC::MessageName name() { return IPC::MessageName::RTCDataChannelRemoteManager_DetectError; }
    static constexpr bool isSync = false;

    DetectError(const WebCore::RTCDataChannelIdentifier& handler, WebCore::RTCErrorDetailType type, const String& message)
        : m_arguments(handler, type, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RTCDataChannelIdentifier&, WebCore::RTCErrorDetailType, const String&> m_arguments;
};

class BufferedAmountIsDecreasing {
public:
    using Arguments = std::tuple<WebCore::RTCDataChannelIdentifier, size_t>;

    static IPC::MessageName name() { return IPC::MessageName::RTCDataChannelRemoteManager_BufferedAmountIsDecreasing; }
    static constexpr bool isSync = false;

    BufferedAmountIsDecreasing(const WebCore::RTCDataChannelIdentifier& handler, size_t amount)
        : m_arguments(handler, amount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RTCDataChannelIdentifier&, size_t> m_arguments;
};

} // namespace RTCDataChannelRemoteManager
} // namespace Messages

#endif // ENABLE(WEB_RTC)
