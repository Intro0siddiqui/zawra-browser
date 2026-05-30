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

#if USE(LIBWEBRTC) && PLATFORM(COCOA) && ENABLE(GPU_PROCESS)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "DataReference.h"
#include "IPCSemaphore.h"
#include "MessageNames.h"
#include "SharedMemory.h"
#include "SharedVideoFrame.h"
#include "VideoDecoderIdentifier.h"
#include "VideoEncoderIdentifier.h"
#include <optional>
#include <utility>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebKit {
enum class VideoCodecType : uint8_t;
}

namespace Messages {
namespace LibWebRTCCodecsProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::LibWebRTCCodecsProxy;
}

class CreateDecoder {
public:
    using Arguments = std::tuple<WebKit::VideoDecoderIdentifier, WebKit::VideoCodecType, bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_CreateDecoder; }
    static constexpr bool isSync = false;

    CreateDecoder(const WebKit::VideoDecoderIdentifier& id, WebKit::VideoCodecType codecType, bool useRemoteFrames, bool enableAdditionalLogging)
        : m_arguments(id, codecType, useRemoteFrames, enableAdditionalLogging)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoDecoderIdentifier&, WebKit::VideoCodecType, bool, bool> m_arguments;
};

class ReleaseDecoder {
public:
    using Arguments = std::tuple<WebKit::VideoDecoderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_ReleaseDecoder; }
    static constexpr bool isSync = false;

    explicit ReleaseDecoder(const WebKit::VideoDecoderIdentifier& id)
        : m_arguments(id)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoDecoderIdentifier&> m_arguments;
};

class FlushDecoder {
public:
    using Arguments = std::tuple<WebKit::VideoDecoderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_FlushDecoder; }
    static constexpr bool isSync = false;

    explicit FlushDecoder(const WebKit::VideoDecoderIdentifier& id)
        : m_arguments(id)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoDecoderIdentifier&> m_arguments;
};

class SetDecoderFormatDescription {
public:
    using Arguments = std::tuple<WebKit::VideoDecoderIdentifier, IPC::DataReference, uint16_t, uint16_t>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_SetDecoderFormatDescription; }
    static constexpr bool isSync = false;

    SetDecoderFormatDescription(const WebKit::VideoDecoderIdentifier& id, const IPC::DataReference& description, uint16_t width, uint16_t height)
        : m_arguments(id, description, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoDecoderIdentifier&, const IPC::DataReference&, uint16_t, uint16_t> m_arguments;
};

class DecodeFrame {
public:
    using Arguments = std::tuple<WebKit::VideoDecoderIdentifier, int64_t, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_DecodeFrame; }
    static constexpr bool isSync = false;

    DecodeFrame(const WebKit::VideoDecoderIdentifier& id, int64_t timeStamp, const IPC::DataReference& data)
        : m_arguments(id, timeStamp, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoDecoderIdentifier&, int64_t, const IPC::DataReference&> m_arguments;
};

class SetFrameSize {
public:
    using Arguments = std::tuple<WebKit::VideoDecoderIdentifier, uint16_t, uint16_t>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_SetFrameSize; }
    static constexpr bool isSync = false;

    SetFrameSize(const WebKit::VideoDecoderIdentifier& id, uint16_t width, uint16_t height)
        : m_arguments(id, width, height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoDecoderIdentifier&, uint16_t, uint16_t> m_arguments;
};

class CreateEncoder {
public:
    using Arguments = std::tuple<WebKit::VideoEncoderIdentifier, WebKit::VideoCodecType, Vector<std::pair<String, String>>, bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_CreateEncoder; }
    static constexpr bool isSync = false;

    CreateEncoder(const WebKit::VideoEncoderIdentifier& id, WebKit::VideoCodecType codecType, const Vector<std::pair<String, String>>& parameters, bool useLowLatency, bool useAnnexB)
        : m_arguments(id, codecType, parameters, useLowLatency, useAnnexB)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoEncoderIdentifier&, WebKit::VideoCodecType, const Vector<std::pair<String, String>>&, bool, bool> m_arguments;
};

class ReleaseEncoder {
public:
    using Arguments = std::tuple<WebKit::VideoEncoderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_ReleaseEncoder; }
    static constexpr bool isSync = false;

    explicit ReleaseEncoder(const WebKit::VideoEncoderIdentifier& id)
        : m_arguments(id)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoEncoderIdentifier&> m_arguments;
};

class InitializeEncoder {
public:
    using Arguments = std::tuple<WebKit::VideoEncoderIdentifier, uint16_t, uint16_t, unsigned, unsigned, unsigned, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_InitializeEncoder; }
    static constexpr bool isSync = false;

    InitializeEncoder(const WebKit::VideoEncoderIdentifier& id, uint16_t width, uint16_t height, const unsigned& startBitrate, const unsigned& maxBitrate, const unsigned& minBitrate, uint32_t maxFramerate)
        : m_arguments(id, width, height, startBitrate, maxBitrate, minBitrate, maxFramerate)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoEncoderIdentifier&, uint16_t, uint16_t, const unsigned&, const unsigned&, const unsigned&, uint32_t> m_arguments;
};

class EncodeFrame {
public:
    using Arguments = std::tuple<WebKit::VideoEncoderIdentifier, WebKit::SharedVideoFrame, int64_t, std::optional<uint64_t>, bool>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_EncodeFrame; }
    static constexpr bool isSync = false;

    EncodeFrame(const WebKit::VideoEncoderIdentifier& id, WebKit::SharedVideoFrame&& buffer, int64_t timeStamp, const std::optional<uint64_t>& duration, bool shouldEncodeAsKeyFrame)
        : m_arguments(id, WTFMove(buffer), timeStamp, duration, shouldEncodeAsKeyFrame)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoEncoderIdentifier&, WebKit::SharedVideoFrame&&, int64_t, const std::optional<uint64_t>&, bool> m_arguments;
};

class FlushEncoder {
public:
    using Arguments = std::tuple<WebKit::VideoEncoderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_FlushEncoder; }
    static constexpr bool isSync = false;

    explicit FlushEncoder(const WebKit::VideoEncoderIdentifier& id)
        : m_arguments(id)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoEncoderIdentifier&> m_arguments;
};

class SetEncodeRates {
public:
    using Arguments = std::tuple<WebKit::VideoEncoderIdentifier, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_SetEncodeRates; }
    static constexpr bool isSync = false;

    SetEncodeRates(const WebKit::VideoEncoderIdentifier& id, uint32_t bitRate, uint32_t frameRate)
        : m_arguments(id, bitRate, frameRate)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoEncoderIdentifier&, uint32_t, uint32_t> m_arguments;
};

class SetSharedVideoFrameSemaphore {
public:
    using Arguments = std::tuple<WebKit::VideoEncoderIdentifier, IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_SetSharedVideoFrameSemaphore; }
    static constexpr bool isSync = false;

    SetSharedVideoFrameSemaphore(const WebKit::VideoEncoderIdentifier& id, const IPC::Semaphore& semaphore)
        : m_arguments(id, semaphore)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoEncoderIdentifier&, const IPC::Semaphore&> m_arguments;
};

class SetSharedVideoFrameMemory {
public:
    using Arguments = std::tuple<WebKit::VideoEncoderIdentifier, WebKit::SharedMemory::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_SetSharedVideoFrameMemory; }
    static constexpr bool isSync = false;

    SetSharedVideoFrameMemory(const WebKit::VideoEncoderIdentifier& id, WebKit::SharedMemory::Handle&& storageHandle)
        : m_arguments(id, WTFMove(storageHandle))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoEncoderIdentifier&, WebKit::SharedMemory::Handle&&> m_arguments;
};

class SetRTCLoggingLevel {
public:
    using Arguments = std::tuple<WTFLogLevel>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecsProxy_SetRTCLoggingLevel; }
    static constexpr bool isSync = false;

    explicit SetRTCLoggingLevel(const WTFLogLevel& level)
        : m_arguments(level)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WTFLogLevel&> m_arguments;
};

} // namespace LibWebRTCCodecsProxy
} // namespace Messages

#endif // USE(LIBWEBRTC) && PLATFORM(COCOA) && ENABLE(GPU_PROCESS)
