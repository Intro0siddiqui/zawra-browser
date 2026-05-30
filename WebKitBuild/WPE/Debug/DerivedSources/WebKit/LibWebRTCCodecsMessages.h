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
#include "MessageNames.h"
#include "RemoteVideoFrameProxy.h"
#include "VideoDecoderIdentifier.h"
#include "VideoEncoderIdentifier.h"
#if PLATFORM(COCOA)
#include <WebCore/CVUtilities.h>
#endif
#include <WebCore/PlatformVideoColorSpace.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/RetainPtr.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace webrtc {
struct WebKitEncodedFrameInfo;
}

namespace Messages {
namespace LibWebRTCCodecs {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::LibWebRTCCodecs;
}

class FailedDecoding {
public:
    using Arguments = std::tuple<WebKit::VideoDecoderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecs_FailedDecoding; }
    static constexpr bool isSync = false;

    explicit FailedDecoding(const WebKit::VideoDecoderIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoDecoderIdentifier&> m_arguments;
};

class FlushDecoderCompleted {
public:
    using Arguments = std::tuple<WebKit::VideoDecoderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecs_FlushDecoderCompleted; }
    static constexpr bool isSync = false;

    explicit FlushDecoderCompleted(const WebKit::VideoDecoderIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoDecoderIdentifier&> m_arguments;
};

class CompletedDecoding {
public:
    using Arguments = std::tuple<WebKit::VideoDecoderIdentifier, int64_t, int64_t, WebKit::RemoteVideoFrameProxy::Properties>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecs_CompletedDecoding; }
    static constexpr bool isSync = false;

    CompletedDecoding(const WebKit::VideoDecoderIdentifier& identifier, int64_t timeStamp, int64_t timeStampNs, const WebKit::RemoteVideoFrameProxy::Properties& frame)
        : m_arguments(identifier, timeStamp, timeStampNs, frame)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoDecoderIdentifier&, int64_t, int64_t, const WebKit::RemoteVideoFrameProxy::Properties&> m_arguments;
};

class CompletedDecodingCV {
public:
    using Arguments = std::tuple<WebKit::VideoDecoderIdentifier, int64_t, int64_t, RetainPtr<CVPixelBufferRef>>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecs_CompletedDecodingCV; }
    static constexpr bool isSync = false;

    CompletedDecodingCV(const WebKit::VideoDecoderIdentifier& identifier, int64_t timeStamp, int64_t timeStampNs, const RetainPtr<CVPixelBufferRef>& pixelBuffer)
        : m_arguments(identifier, timeStamp, timeStampNs, pixelBuffer)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoDecoderIdentifier&, int64_t, int64_t, const RetainPtr<CVPixelBufferRef>&> m_arguments;
};

class CompletedEncoding {
public:
    using Arguments = std::tuple<WebKit::VideoEncoderIdentifier, IPC::DataReference, webrtc::WebKitEncodedFrameInfo>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecs_CompletedEncoding; }
    static constexpr bool isSync = false;

    CompletedEncoding(const WebKit::VideoEncoderIdentifier& identifier, const IPC::DataReference& data, const webrtc::WebKitEncodedFrameInfo& info)
        : m_arguments(identifier, data, info)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoEncoderIdentifier&, const IPC::DataReference&, const webrtc::WebKitEncodedFrameInfo&> m_arguments;
};

class FlushEncoderCompleted {
public:
    using Arguments = std::tuple<WebKit::VideoEncoderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecs_FlushEncoderCompleted; }
    static constexpr bool isSync = false;

    explicit FlushEncoderCompleted(const WebKit::VideoEncoderIdentifier& id)
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

class SetEncodingConfiguration {
public:
    using Arguments = std::tuple<WebKit::VideoEncoderIdentifier, IPC::DataReference, std::optional<WebCore::PlatformVideoColorSpace>>;

    static IPC::MessageName name() { return IPC::MessageName::LibWebRTCCodecs_SetEncodingConfiguration; }
    static constexpr bool isSync = false;

    SetEncodingConfiguration(const WebKit::VideoEncoderIdentifier& identifier, const IPC::DataReference& description, const std::optional<WebCore::PlatformVideoColorSpace>& colorSpace)
        : m_arguments(identifier, description, colorSpace)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::VideoEncoderIdentifier&, const IPC::DataReference&, const std::optional<WebCore::PlatformVideoColorSpace>&> m_arguments;
};

} // namespace LibWebRTCCodecs
} // namespace Messages

#endif // USE(LIBWEBRTC) && PLATFORM(COCOA) && ENABLE(GPU_PROCESS)
