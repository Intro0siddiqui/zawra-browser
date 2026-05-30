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

#if ENABLE(GPU_PROCESS) && ENABLE(WEB_AUDIO)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "IPCSemaphore.h"
#include "MessageNames.h"
#include "RemoteAudioDestinationIdentifier.h"
#if PLATFORM(COCOA)
#include "SharedCARingBuffer.h"
#endif
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace RemoteAudioDestinationManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteAudioDestinationManager;
}

class CreateAudioDestination {
public:
    using Arguments = std::tuple<WebKit::RemoteAudioDestinationIdentifier, String, uint32_t, uint32_t, float, float, IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioDestinationManager_CreateAudioDestination; }
    static constexpr bool isSync = false;

    CreateAudioDestination(const WebKit::RemoteAudioDestinationIdentifier& identifier, const String& inputDeviceId, uint32_t numberOfInputChannels, uint32_t numberOfOutputChannels, float sampleRate, float hardwareSampleRate, const IPC::Semaphore& renderSemaphore)
        : m_arguments(identifier, inputDeviceId, numberOfInputChannels, numberOfOutputChannels, sampleRate, hardwareSampleRate, renderSemaphore)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteAudioDestinationIdentifier&, const String&, uint32_t, uint32_t, float, float, const IPC::Semaphore&> m_arguments;
};

class DeleteAudioDestination {
public:
    using Arguments = std::tuple<WebKit::RemoteAudioDestinationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioDestinationManager_DeleteAudioDestination; }
    static constexpr bool isSync = false;

    explicit DeleteAudioDestination(const WebKit::RemoteAudioDestinationIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteAudioDestinationIdentifier&> m_arguments;
};

class StartAudioDestination {
public:
    using Arguments = std::tuple<WebKit::RemoteAudioDestinationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioDestinationManager_StartAudioDestination; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteAudioDestinationManager_StartAudioDestinationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit StartAudioDestination(const WebKit::RemoteAudioDestinationIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteAudioDestinationIdentifier&> m_arguments;
};

class StopAudioDestination {
public:
    using Arguments = std::tuple<WebKit::RemoteAudioDestinationIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioDestinationManager_StopAudioDestination; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteAudioDestinationManager_StopAudioDestinationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit StopAudioDestination(const WebKit::RemoteAudioDestinationIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteAudioDestinationIdentifier&> m_arguments;
};

#if PLATFORM(COCOA)
class AudioSamplesStorageChanged {
public:
    using Arguments = std::tuple<WebKit::RemoteAudioDestinationIdentifier, WebKit::ConsumerSharedCARingBuffer::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioDestinationManager_AudioSamplesStorageChanged; }
    static constexpr bool isSync = false;

    AudioSamplesStorageChanged(const WebKit::RemoteAudioDestinationIdentifier& identifier, WebKit::ConsumerSharedCARingBuffer::Handle&& storageHandle)
        : m_arguments(identifier, WTFMove(storageHandle))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteAudioDestinationIdentifier&, WebKit::ConsumerSharedCARingBuffer::Handle&&> m_arguments;
};
#endif

} // namespace RemoteAudioDestinationManager
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(WEB_AUDIO)
