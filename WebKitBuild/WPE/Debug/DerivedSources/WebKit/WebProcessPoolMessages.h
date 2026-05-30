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

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
enum class GamepadHapticEffectType : uint8_t;
struct GamepadEffectParameters;
}

namespace WebKit {
class UserData;
}

namespace Messages {
namespace WebProcessPool {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebProcessPool;
}

class HandleMessage {
public:
    using Arguments = std::tuple<String, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessPool_HandleMessage; }
    static constexpr bool isSync = false;

    HandleMessage(const String& messageName, const WebKit::UserData& messageBody)
        : m_arguments(messageName, messageBody)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebKit::UserData&> m_arguments;
};

class HandleSynchronousMessage {
public:
    using Arguments = std::tuple<String, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessPool_HandleSynchronousMessage; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::UserData>;
    HandleSynchronousMessage(const String& messageName, const WebKit::UserData& messageBody)
        : m_arguments(messageName, messageBody)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebKit::UserData&> m_arguments;
};

#if ENABLE(GAMEPAD)
class StartedUsingGamepads {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessPool_StartedUsingGamepads; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(GAMEPAD)
class StoppedUsingGamepads {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessPool_StoppedUsingGamepads; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcessPool_StoppedUsingGamepadsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(GAMEPAD)
class PlayGamepadEffect {
public:
    using Arguments = std::tuple<unsigned, String, WebCore::GamepadHapticEffectType, WebCore::GamepadEffectParameters>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessPool_PlayGamepadEffect; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcessPool_PlayGamepadEffectReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    PlayGamepadEffect(const unsigned& gamepadIndex, const String& gamepadID, WebCore::GamepadHapticEffectType type, const WebCore::GamepadEffectParameters& parameters)
        : m_arguments(gamepadIndex, gamepadID, type, parameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const unsigned&, const String&, WebCore::GamepadHapticEffectType, const WebCore::GamepadEffectParameters&> m_arguments;
};
#endif

#if ENABLE(GAMEPAD)
class StopGamepadEffects {
public:
    using Arguments = std::tuple<unsigned, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessPool_StopGamepadEffects; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcessPool_StopGamepadEffectsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    StopGamepadEffects(const unsigned& gamepadIndex, const String& gamepadID)
        : m_arguments(gamepadIndex, gamepadID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const unsigned&, const String&> m_arguments;
};
#endif

class ReportWebContentCPUTime {
public:
    using Arguments = std::tuple<Seconds, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessPool_ReportWebContentCPUTime; }
    static constexpr bool isSync = false;

    ReportWebContentCPUTime(const Seconds& cpuTime, uint64_t activityState)
        : m_arguments(cpuTime, activityState)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Seconds&, uint64_t> m_arguments;
};

} // namespace WebProcessPool
} // namespace Messages
