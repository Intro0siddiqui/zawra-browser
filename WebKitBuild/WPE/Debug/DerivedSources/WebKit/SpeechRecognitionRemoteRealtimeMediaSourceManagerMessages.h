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
#if PLATFORM(COCOA)
#include "SharedCARingBuffer.h"
#endif
#include <WebCore/RealtimeMediaSourceIdentifier.h>
#include <wtf/Forward.h>
#include <wtf/MediaTime.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace WebCore {
class CAAudioStreamDescription;
}

namespace Messages {
namespace SpeechRecognitionRemoteRealtimeMediaSourceManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::SpeechRecognitionRemoteRealtimeMediaSourceManager;
}

class RemoteAudioSamplesAvailable {
public:
    using Arguments = std::tuple<WebCore::RealtimeMediaSourceIdentifier, MediaTime, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteAudioSamplesAvailable; }
    static constexpr bool isSync = false;

    RemoteAudioSamplesAvailable(const WebCore::RealtimeMediaSourceIdentifier& identifier, const MediaTime& time, uint64_t numberOfFrames)
        : m_arguments(identifier, time, numberOfFrames)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RealtimeMediaSourceIdentifier&, const MediaTime&, uint64_t> m_arguments;
};

class RemoteCaptureFailed {
public:
    using Arguments = std::tuple<WebCore::RealtimeMediaSourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteCaptureFailed; }
    static constexpr bool isSync = false;

    explicit RemoteCaptureFailed(const WebCore::RealtimeMediaSourceIdentifier& identifier)
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

class RemoteSourceStopped {
public:
    using Arguments = std::tuple<WebCore::RealtimeMediaSourceIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteSourceStopped; }
    static constexpr bool isSync = false;

    explicit RemoteSourceStopped(const WebCore::RealtimeMediaSourceIdentifier& identifier)
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

#if PLATFORM(COCOA)
class SetStorage {
public:
    using Arguments = std::tuple<WebCore::RealtimeMediaSourceIdentifier, WebKit::ConsumerSharedCARingBuffer::Handle, WebCore::CAAudioStreamDescription>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionRemoteRealtimeMediaSourceManager_SetStorage; }
    static constexpr bool isSync = false;

    SetStorage(const WebCore::RealtimeMediaSourceIdentifier& identifier, WebKit::ConsumerSharedCARingBuffer::Handle&& storageHandle, const WebCore::CAAudioStreamDescription& description)
        : m_arguments(identifier, WTFMove(storageHandle), description)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RealtimeMediaSourceIdentifier&, WebKit::ConsumerSharedCARingBuffer::Handle&&, const WebCore::CAAudioStreamDescription&> m_arguments;
};
#endif

} // namespace SpeechRecognitionRemoteRealtimeMediaSourceManager
} // namespace Messages

#endif // ENABLE(MEDIA_STREAM)
