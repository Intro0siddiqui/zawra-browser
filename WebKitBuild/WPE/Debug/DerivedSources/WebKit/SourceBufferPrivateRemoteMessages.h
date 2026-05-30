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

#if ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include <WebCore/PlatformTimeRanges.h>
#include <WebCore/SourceBufferPrivateClient.h>
#include <wtf/Forward.h>
#include <wtf/MediaTime.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>

namespace WebCore {
class PlatformTimeRanges;
}

namespace WebKit {
struct InitializationSegmentInfo;
}

namespace Messages {
namespace SourceBufferPrivateRemote {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::SourceBufferPrivateRemote;
}

class SourceBufferPrivateDidReceiveInitializationSegment {
public:
    using Arguments = std::tuple<WebKit::InitializationSegmentInfo>;

    static IPC::MessageName name() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveInitializationSegment; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveInitializationSegmentReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::SourceBufferPrivateClient::ReceiveResult>;
    explicit SourceBufferPrivateDidReceiveInitializationSegment(const WebKit::InitializationSegmentInfo& segmentConfiguration)
        : m_arguments(segmentConfiguration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::InitializationSegmentInfo&> m_arguments;
};

class SourceBufferPrivateStreamEndedWithDecodeError {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateStreamEndedWithDecodeError; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SourceBufferPrivateAppendComplete {
public:
    using Arguments = std::tuple<WebCore::SourceBufferPrivateClient::AppendResult, uint64_t, MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateAppendComplete; }
    static constexpr bool isSync = false;

    SourceBufferPrivateAppendComplete(const WebCore::SourceBufferPrivateClient::AppendResult& appendResult, uint64_t totalTrackBufferSizeInBytes, const MediaTime& timeStampOffset)
        : m_arguments(appendResult, totalTrackBufferSizeInBytes, timeStampOffset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SourceBufferPrivateClient::AppendResult&, uint64_t, const MediaTime&> m_arguments;
};

class SourceBufferPrivateHighestPresentationTimestampChanged {
public:
    using Arguments = std::tuple<MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateHighestPresentationTimestampChanged; }
    static constexpr bool isSync = false;

    explicit SourceBufferPrivateHighestPresentationTimestampChanged(const MediaTime& timestamp)
        : m_arguments(timestamp)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&> m_arguments;
};

class SourceBufferPrivateBufferedChanged {
public:
    using Arguments = std::tuple<WebCore::PlatformTimeRanges>;

    static IPC::MessageName name() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateBufferedChanged; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateBufferedChangedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit SourceBufferPrivateBufferedChanged(const WebCore::PlatformTimeRanges& buffered)
        : m_arguments(buffered)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlatformTimeRanges&> m_arguments;
};

class SourceBufferPrivateTrackBuffersChanged {
public:
    using Arguments = std::tuple<Vector<WebCore::PlatformTimeRanges>>;

    static IPC::MessageName name() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateTrackBuffersChanged; }
    static constexpr bool isSync = false;

    explicit SourceBufferPrivateTrackBuffersChanged(const Vector<WebCore::PlatformTimeRanges>& trackBuffers)
        : m_arguments(trackBuffers)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::PlatformTimeRanges>&> m_arguments;
};

class SourceBufferPrivateDurationChanged {
public:
    using Arguments = std::tuple<MediaTime>;

    static IPC::MessageName name() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDurationChanged; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDurationChangedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit SourceBufferPrivateDurationChanged(const MediaTime& duration)
        : m_arguments(duration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const MediaTime&> m_arguments;
};

class SourceBufferPrivateDidParseSample {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDidParseSample; }
    static constexpr bool isSync = false;

    explicit SourceBufferPrivateDidParseSample(double sampleDuration)
        : m_arguments(sampleDuration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class SourceBufferPrivateDidDropSample {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDidDropSample; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SourceBufferPrivateDidReceiveRenderingError {
public:
    using Arguments = std::tuple<int64_t>;

    static IPC::MessageName name() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveRenderingError; }
    static constexpr bool isSync = false;

    explicit SourceBufferPrivateDidReceiveRenderingError(int64_t errorCode)
        : m_arguments(errorCode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int64_t> m_arguments;
};

class SourceBufferPrivateReportExtraMemoryCost {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::SourceBufferPrivateRemote_SourceBufferPrivateReportExtraMemoryCost; }
    static constexpr bool isSync = false;

    explicit SourceBufferPrivateReportExtraMemoryCost(uint64_t extraMemory)
        : m_arguments(extraMemory)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

} // namespace SourceBufferPrivateRemote
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
