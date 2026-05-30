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

#include "config.h"
#include "EventDispatcher.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "EventDispatcherMessages.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#if ENABLE(MOMENTUM_EVENT_DISPATCHER)
#include "ScrollingAccelerationCurve.h" // NOLINT
#endif
#include "WebCoreArgumentCoders.h" // NOLINT
#if ENABLE(MAC_GESTURE_EVENTS)
#include "WebGestureEvent.h" // NOLINT
#endif
#if ENABLE(IOS_TOUCH_EVENTS)
#include "WebTouchEvent.h" // NOLINT
#endif
#include "WebWheelEvent.h" // NOLINT
#if HAVE(CVDISPLAYLINK)
#include <WebCore/DisplayUpdate.h> // NOLINT
#endif
#include <WebCore/PageIdentifier.h> // NOLINT
#include <WebCore/RectEdges.h> // NOLINT
#include <optional> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void EventDispatcher::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::EventDispatcher::WheelEvent::name())
        return IPC::handleMessage<Messages::EventDispatcher::WheelEvent>(connection, decoder, this, &EventDispatcher::wheelEvent);
#if ENABLE(IOS_TOUCH_EVENTS)
    if (decoder.messageName() == Messages::EventDispatcher::TouchEvent::name())
        return IPC::handleMessageAsync<Messages::EventDispatcher::TouchEvent>(connection, decoder, this, &EventDispatcher::touchEvent);
    if (decoder.messageName() == Messages::EventDispatcher::TouchEventWithoutCallback::name())
        return IPC::handleMessage<Messages::EventDispatcher::TouchEventWithoutCallback>(connection, decoder, this, &EventDispatcher::touchEventWithoutCallback);
#endif
#if ENABLE(MAC_GESTURE_EVENTS)
    if (decoder.messageName() == Messages::EventDispatcher::GestureEvent::name())
        return IPC::handleMessage<Messages::EventDispatcher::GestureEvent>(connection, decoder, this, &EventDispatcher::gestureEvent);
#endif
#if HAVE(CVDISPLAYLINK)
    if (decoder.messageName() == Messages::EventDispatcher::DisplayDidRefresh::name())
        return IPC::handleMessage<Messages::EventDispatcher::DisplayDidRefresh>(connection, decoder, this, &EventDispatcher::displayDidRefresh);
#endif
#if ENABLE(MOMENTUM_EVENT_DISPATCHER)
    if (decoder.messageName() == Messages::EventDispatcher::SetScrollingAccelerationCurve::name())
        return IPC::handleMessage<Messages::EventDispatcher::SetScrollingAccelerationCurve>(connection, decoder, this, &EventDispatcher::setScrollingAccelerationCurve);
#endif
    if (decoder.messageName() == Messages::EventDispatcher::PageScreenDidChange::name())
        return IPC::handleMessage<Messages::EventDispatcher::PageScreenDidChange>(connection, decoder, this, &EventDispatcher::pageScreenDidChange);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

} // namespace WebKit

#if ENABLE(IPC_TESTING_API)

namespace IPC {

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::EventDispatcher_WheelEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::EventDispatcher::WheelEvent::Arguments>(globalObject, decoder);
}
#if ENABLE(IOS_TOUCH_EVENTS)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::EventDispatcher_TouchEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::EventDispatcher::TouchEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::EventDispatcher_TouchEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::EventDispatcher::TouchEvent::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::EventDispatcher_TouchEventWithoutCallback>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::EventDispatcher::TouchEventWithoutCallback::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(MAC_GESTURE_EVENTS)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::EventDispatcher_GestureEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::EventDispatcher::GestureEvent::Arguments>(globalObject, decoder);
}
#endif
#if HAVE(CVDISPLAYLINK)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::EventDispatcher_DisplayDidRefresh>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::EventDispatcher::DisplayDidRefresh::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(MOMENTUM_EVENT_DISPATCHER)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::EventDispatcher_SetScrollingAccelerationCurve>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::EventDispatcher::SetScrollingAccelerationCurve::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::EventDispatcher_PageScreenDidChange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::EventDispatcher::PageScreenDidChange::Arguments>(globalObject, decoder);
}

}

#endif

