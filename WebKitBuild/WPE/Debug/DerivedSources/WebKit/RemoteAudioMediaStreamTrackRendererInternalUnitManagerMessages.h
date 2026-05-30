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

#if ENABLE(GPU_PROCESS) && ENABLE(MEDIA_STREAM) && PLATFORM(COCOA)

#include "ArgumentCoders.h"
#include "AudioMediaStreamTrackRendererInternalUnitIdentifier.h"
#include "Connection.h"
#include "IPCSemaphore.h"
#include "MessageNames.h"
#if PLATFORM(COCOA)
#include "SharedCARingBuffer.h"
#endif
#include <WebCore/CAAudioStreamDescription.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace RemoteAudioMediaStreamTrackRendererInternalUnitManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteAudioMediaStreamTrackRendererInternalUnitManager;
}

class CreateUnit {
public:
    using Arguments = std::tuple<WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioMediaStreamTrackRendererInternalUnitManager_CreateUnit; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteAudioMediaStreamTrackRendererInternalUnitManager_CreateUnitReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::CAAudioStreamDescription>, size_t>;
    explicit CreateUnit(const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier&> m_arguments;
};

class DeleteUnit {
public:
    using Arguments = std::tuple<WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioMediaStreamTrackRendererInternalUnitManager_DeleteUnit; }
    static constexpr bool isSync = false;

    explicit DeleteUnit(const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier&> m_arguments;
};

class StartUnit {
public:
    using Arguments = std::tuple<WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier, WebKit::ConsumerSharedCARingBuffer::Handle, IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioMediaStreamTrackRendererInternalUnitManager_StartUnit; }
    static constexpr bool isSync = false;

    StartUnit(const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier& identifier, WebKit::ConsumerSharedCARingBuffer::Handle&& storageHandle, const IPC::Semaphore& renderSemaphore)
        : m_arguments(identifier, WTFMove(storageHandle), renderSemaphore)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier&, WebKit::ConsumerSharedCARingBuffer::Handle&&, const IPC::Semaphore&> m_arguments;
};

class StopUnit {
public:
    using Arguments = std::tuple<WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioMediaStreamTrackRendererInternalUnitManager_StopUnit; }
    static constexpr bool isSync = false;

    explicit StopUnit(const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier&> m_arguments;
};

class SetAudioOutputDevice {
public:
    using Arguments = std::tuple<WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteAudioMediaStreamTrackRendererInternalUnitManager_SetAudioOutputDevice; }
    static constexpr bool isSync = false;

    SetAudioOutputDevice(const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier& identifier, const String& deviceId)
        : m_arguments(identifier, deviceId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::AudioMediaStreamTrackRendererInternalUnitIdentifier&, const String&> m_arguments;
};

} // namespace RemoteAudioMediaStreamTrackRendererInternalUnitManager
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(MEDIA_STREAM) && PLATFORM(COCOA)
