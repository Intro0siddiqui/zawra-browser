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

#if PLATFORM(COCOA) && ENABLE(GPU_PROCESS) && ENABLE(MEDIA_STREAM)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MediaRecorderIdentifier.h"
#include "MessageNames.h"
#include <WebCore/ExceptionData.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
struct MediaRecorderPrivateOptions;
}

namespace Messages {
namespace RemoteMediaRecorderManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteMediaRecorderManager;
}

class CreateRecorder {
public:
    using Arguments = std::tuple<WebKit::MediaRecorderIdentifier, bool, bool, WebCore::MediaRecorderPrivateOptions>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaRecorderManager_CreateRecorder; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteMediaRecorderManager_CreateRecorderReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ExceptionData>, String, unsigned, unsigned>;
    CreateRecorder(const WebKit::MediaRecorderIdentifier& id, bool hasAudio, bool hasVideo, const WebCore::MediaRecorderPrivateOptions& options)
        : m_arguments(id, hasAudio, hasVideo, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::MediaRecorderIdentifier&, bool, bool, const WebCore::MediaRecorderPrivateOptions&> m_arguments;
};

class ReleaseRecorder {
public:
    using Arguments = std::tuple<WebKit::MediaRecorderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaRecorderManager_ReleaseRecorder; }
    static constexpr bool isSync = false;

    explicit ReleaseRecorder(const WebKit::MediaRecorderIdentifier& id)
        : m_arguments(id)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::MediaRecorderIdentifier&> m_arguments;
};

} // namespace RemoteMediaRecorderManager
} // namespace Messages

#endif // PLATFORM(COCOA) && ENABLE(GPU_PROCESS) && ENABLE(MEDIA_STREAM)
