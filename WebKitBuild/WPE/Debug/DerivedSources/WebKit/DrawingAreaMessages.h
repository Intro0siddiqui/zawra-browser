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
#include <WebCore/DestinationColorSpace.h>
#include <WebCore/FloatRect.h>
#include <WebCore/PlatformLayerIdentifier.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/MachSendRight.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class FloatPoint;
class IntSize;
}

namespace Messages {
namespace DrawingArea {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::DrawingArea;
}

#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
class UpdateGeometry {
public:
    using Arguments = std::tuple<WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_UpdateGeometry; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::DrawingArea_UpdateGeometryReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit UpdateGeometry(const WebCore::IntSize& size)
        : m_arguments(size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntSize&> m_arguments;
};
#endif

#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
class TargetRefreshRateDidChange {
public:
    using Arguments = std::tuple<unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_TargetRefreshRateDidChange; }
    static constexpr bool isSync = false;

    explicit TargetRefreshRateDidChange(const unsigned& rate)
        : m_arguments(rate)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const unsigned&> m_arguments;
};
#endif

#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
class SetDeviceScaleFactor {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_SetDeviceScaleFactor; }
    static constexpr bool isSync = false;

    explicit SetDeviceScaleFactor(float deviceScaleFactor)
        : m_arguments(deviceScaleFactor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};
#endif

#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
class ForceUpdate {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_ForceUpdate; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
class DidDiscardBackingStore {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_DidDiscardBackingStore; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class DisplayDidRefresh {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_DisplayDidRefresh; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if PLATFORM(COCOA)
class UpdateGeometry {
public:
    using Arguments = std::tuple<WebCore::IntSize, bool, MachSendRight>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_UpdateGeometry; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::DrawingArea_UpdateGeometryReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    UpdateGeometry(const WebCore::IntSize& viewSize, bool flushSynchronously, MachSendRight&& fencePort)
        : m_arguments(viewSize, flushSynchronously, WTFMove(fencePort))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntSize&, bool, MachSendRight&&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetDeviceScaleFactor {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_SetDeviceScaleFactor; }
    static constexpr bool isSync = false;

    explicit SetDeviceScaleFactor(float deviceScaleFactor)
        : m_arguments(deviceScaleFactor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetColorSpace {
public:
    using Arguments = std::tuple<std::optional<WebCore::DestinationColorSpace>>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_SetColorSpace; }
    static constexpr bool isSync = false;

    explicit SetColorSpace(const std::optional<WebCore::DestinationColorSpace>& colorSpace)
        : m_arguments(colorSpace)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::DestinationColorSpace>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetViewExposedRect {
public:
    using Arguments = std::tuple<std::optional<WebCore::FloatRect>>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_SetViewExposedRect; }
    static constexpr bool isSync = false;

    explicit SetViewExposedRect(const std::optional<WebCore::FloatRect>& viewExposedRect)
        : m_arguments(viewExposedRect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::FloatRect>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class AcceleratedAnimationDidStart {
public:
    using Arguments = std::tuple<WebCore::PlatformLayerIdentifier, String, MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_AcceleratedAnimationDidStart; }
    static constexpr bool isSync = false;

    AcceleratedAnimationDidStart(const WebCore::PlatformLayerIdentifier& layerID, const String& key, const MonotonicTime& startTime)
        : m_arguments(layerID, key, startTime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlatformLayerIdentifier&, const String&, const MonotonicTime&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class AcceleratedAnimationDidEnd {
public:
    using Arguments = std::tuple<WebCore::PlatformLayerIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_AcceleratedAnimationDidEnd; }
    static constexpr bool isSync = false;

    AcceleratedAnimationDidEnd(const WebCore::PlatformLayerIdentifier& layerID, const String& key)
        : m_arguments(layerID, key)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlatformLayerIdentifier&, const String&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class DispatchAfterEnsuringDrawing {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_DispatchAfterEnsuringDrawing; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::DrawingArea_DispatchAfterEnsuringDrawingReply; }
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

#if USE(GRAPHICS_LAYER_WC)
class UpdateGeometryWC {
public:
    using Arguments = std::tuple<uint64_t, WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_UpdateGeometryWC; }
    static constexpr bool isSync = false;

    UpdateGeometryWC(uint64_t backingStoreStateID, const WebCore::IntSize& viewSize)
        : m_arguments(backingStoreStateID, viewSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const WebCore::IntSize&> m_arguments;
};
#endif

#if PLATFORM(COCOA) || PLATFORM(GTK)
class AdjustTransientZoom {
public:
    using Arguments = std::tuple<double, WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_AdjustTransientZoom; }
    static constexpr bool isSync = false;

    AdjustTransientZoom(double scale, const WebCore::FloatPoint& origin)
        : m_arguments(scale, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double, const WebCore::FloatPoint&> m_arguments;
};
#endif

#if PLATFORM(COCOA) || PLATFORM(GTK)
class CommitTransientZoom {
public:
    using Arguments = std::tuple<double, WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::DrawingArea_CommitTransientZoom; }
    static constexpr bool isSync = false;

    CommitTransientZoom(double scale, const WebCore::FloatPoint& origin)
        : m_arguments(scale, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double, const WebCore::FloatPoint&> m_arguments;
};
#endif

} // namespace DrawingArea
} // namespace Messages
