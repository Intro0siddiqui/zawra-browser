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
#include "ScrollingAccelerationCurve.h"
#include <WebCore/PageIdentifier.h>
#include <WebCore/RectEdges.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace WebCore {
struct DisplayUpdate;
}

namespace WebKit {
class WebGestureEvent;
class WebTouchEvent;
class WebWheelEvent;
}

namespace Messages {
namespace EventDispatcher {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::EventDispatcher;
}

class WheelEvent {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, WebKit::WebWheelEvent, WebCore::RectEdges<bool>>;

    static IPC::MessageName name() { return IPC::MessageName::EventDispatcher_WheelEvent; }
    static constexpr bool isSync = false;

    WheelEvent(const WebCore::PageIdentifier& pageID, const WebKit::WebWheelEvent& event, const WebCore::RectEdges<bool>& rubberBandableEdges)
        : m_arguments(pageID, event, rubberBandableEdges)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const WebKit::WebWheelEvent&, const WebCore::RectEdges<bool>&> m_arguments;
};

#if ENABLE(IOS_TOUCH_EVENTS)
class TouchEvent {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, WebKit::WebTouchEvent>;

    static IPC::MessageName name() { return IPC::MessageName::EventDispatcher_TouchEvent; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::EventDispatcher_TouchEventReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::MainThread;
    using ReplyArguments = std::tuple<bool>;
    TouchEvent(const WebCore::PageIdentifier& pageID, const WebKit::WebTouchEvent& event)
        : m_arguments(pageID, event)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const WebKit::WebTouchEvent&> m_arguments;
};
#endif

#if ENABLE(IOS_TOUCH_EVENTS)
class TouchEventWithoutCallback {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, WebKit::WebTouchEvent>;

    static IPC::MessageName name() { return IPC::MessageName::EventDispatcher_TouchEventWithoutCallback; }
    static constexpr bool isSync = false;

    TouchEventWithoutCallback(const WebCore::PageIdentifier& pageID, const WebKit::WebTouchEvent& event)
        : m_arguments(pageID, event)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const WebKit::WebTouchEvent&> m_arguments;
};
#endif

#if ENABLE(MAC_GESTURE_EVENTS)
class GestureEvent {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, WebKit::WebGestureEvent>;

    static IPC::MessageName name() { return IPC::MessageName::EventDispatcher_GestureEvent; }
    static constexpr bool isSync = false;

    GestureEvent(const WebCore::PageIdentifier& pageID, const WebKit::WebGestureEvent& event)
        : m_arguments(pageID, event)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const WebKit::WebGestureEvent&> m_arguments;
};
#endif

#if HAVE(CVDISPLAYLINK)
class DisplayDidRefresh {
public:
    using Arguments = std::tuple<uint32_t, WebCore::DisplayUpdate, bool>;

    static IPC::MessageName name() { return IPC::MessageName::EventDispatcher_DisplayDidRefresh; }
    static constexpr bool isSync = false;

    DisplayDidRefresh(uint32_t displayID, const WebCore::DisplayUpdate& update, bool sendToMainThread)
        : m_arguments(displayID, update, sendToMainThread)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const WebCore::DisplayUpdate&, bool> m_arguments;
};
#endif

#if ENABLE(MOMENTUM_EVENT_DISPATCHER)
class SetScrollingAccelerationCurve {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebKit::ScrollingAccelerationCurve>>;

    static IPC::MessageName name() { return IPC::MessageName::EventDispatcher_SetScrollingAccelerationCurve; }
    static constexpr bool isSync = false;

    SetScrollingAccelerationCurve(const WebCore::PageIdentifier& pageID, const std::optional<WebKit::ScrollingAccelerationCurve>& curve)
        : m_arguments(pageID, curve)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebKit::ScrollingAccelerationCurve>&> m_arguments;
};
#endif

class PageScreenDidChange {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, uint32_t, std::optional<unsigned>>;

    static IPC::MessageName name() { return IPC::MessageName::EventDispatcher_PageScreenDidChange; }
    static constexpr bool isSync = false;

    PageScreenDidChange(const WebCore::PageIdentifier& pageID, uint32_t displayID, const std::optional<unsigned>& nominalFramesPerSecond)
        : m_arguments(pageID, displayID, nominalFramesPerSecond)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, uint32_t, const std::optional<unsigned>&> m_arguments;
};

} // namespace EventDispatcher
} // namespace Messages
