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

#if ENABLE(MEDIA_STREAM)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include "SandboxExtension.h"
#include <WebCore/PageIdentifier.h>
#include <WebCore/RealtimeMediaSourceIdentifier.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace WebCore {
class CaptureDevice;
}

namespace Messages {
namespace SpeechRecognitionRealtimeMediaSourceManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::SpeechRecognitionRealtimeMediaSourceManager;
}

class CreateSource {
public:
    using Arguments = std::tuple<WebCore::RealtimeMediaSourceIdentifier, WebCore::CaptureDevice, WebCore::PageIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionRealtimeMediaSourceManager_CreateSource; }
    static constexpr bool isSync = false;

    CreateSource(const WebCore::RealtimeMediaSourceIdentifier& identifier, const WebCore::CaptureDevice& device, const WebCore::PageIdentifier& pageIdentifier)
        : m_arguments(identifier, device, pageIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RealtimeMediaSourceIdentifier&, const WebCore::CaptureDevice&, const WebCore::PageIdentifier&> m_arguments;
};

class DeleteSource {
public:
    using Arguments = std::tuple<WebCore::RealtimeMediaSourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionRealtimeMediaSourceManager_DeleteSource; }
    static constexpr bool isSync = false;

    explicit DeleteSource(const WebCore::RealtimeMediaSourceIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RealtimeMediaSourceIdentifier&> m_arguments;
};

class Start {
public:
    using Arguments = std::tuple<WebCore::RealtimeMediaSourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionRealtimeMediaSourceManager_Start; }
    static constexpr bool isSync = false;

    explicit Start(const WebCore::RealtimeMediaSourceIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RealtimeMediaSourceIdentifier&> m_arguments;
};

class Stop {
public:
    using Arguments = std::tuple<WebCore::RealtimeMediaSourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionRealtimeMediaSourceManager_Stop; }
    static constexpr bool isSync = false;

    explicit Stop(const WebCore::RealtimeMediaSourceIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RealtimeMediaSourceIdentifier&> m_arguments;
};

#if ENABLE(SANDBOX_EXTENSIONS)
class GrantSandboxExtensions {
public:
    using Arguments = std::tuple<WebKit::SandboxExtension::Handle, WebKit::SandboxExtension::Handle, WebKit::SandboxExtension::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionRealtimeMediaSourceManager_GrantSandboxExtensions; }
    static constexpr bool isSync = false;

    GrantSandboxExtensions(const WebKit::SandboxExtension::Handle& bootstrapHandle, const WebKit::SandboxExtension::Handle& sandboxExtensionHandleForTCCD, const WebKit::SandboxExtension::Handle& sandboxExtensionHandleForMicrophone)
        : m_arguments(bootstrapHandle, sandboxExtensionHandleForTCCD, sandboxExtensionHandleForMicrophone)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::SandboxExtension::Handle&, const WebKit::SandboxExtension::Handle&, const WebKit::SandboxExtension::Handle&> m_arguments;
};
#endif

#if ENABLE(SANDBOX_EXTENSIONS)
class RevokeSandboxExtensions {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionRealtimeMediaSourceManager_RevokeSandboxExtensions; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

} // namespace SpeechRecognitionRealtimeMediaSourceManager
} // namespace Messages

#endif // ENABLE(MEDIA_STREAM)
