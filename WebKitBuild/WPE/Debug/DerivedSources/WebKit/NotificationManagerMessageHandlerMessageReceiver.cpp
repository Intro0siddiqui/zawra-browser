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
#include "NotificationManagerMessageHandler.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "NotificationManagerMessageHandlerMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/NotificationData.h> // NOLINT
#include <WebCore/NotificationResources.h> // NOLINT
#include <wtf/RefCounted.h> // NOLINT
#include <wtf/UUID.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void NotificationManagerMessageHandler::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::NotificationManagerMessageHandler::RequestSystemNotificationPermission::name())
        return IPC::handleMessageAsync<Messages::NotificationManagerMessageHandler::RequestSystemNotificationPermission>(connection, decoder, this, &NotificationManagerMessageHandler::requestSystemNotificationPermission);
    if (decoder.messageName() == Messages::NotificationManagerMessageHandler::ShowNotification::name())
        return IPC::handleMessageAsync<Messages::NotificationManagerMessageHandler::ShowNotification>(connection, decoder, this, &NotificationManagerMessageHandler::showNotification);
    if (decoder.messageName() == Messages::NotificationManagerMessageHandler::CancelNotification::name())
        return IPC::handleMessage<Messages::NotificationManagerMessageHandler::CancelNotification>(connection, decoder, this, &NotificationManagerMessageHandler::cancelNotification);
    if (decoder.messageName() == Messages::NotificationManagerMessageHandler::ClearNotifications::name())
        return IPC::handleMessage<Messages::NotificationManagerMessageHandler::ClearNotifications>(connection, decoder, this, &NotificationManagerMessageHandler::clearNotifications);
    if (decoder.messageName() == Messages::NotificationManagerMessageHandler::DidDestroyNotification::name())
        return IPC::handleMessage<Messages::NotificationManagerMessageHandler::DidDestroyNotification>(connection, decoder, this, &NotificationManagerMessageHandler::didDestroyNotification);
    if (decoder.messageName() == Messages::NotificationManagerMessageHandler::PageWasNotifiedOfNotificationPermission::name())
        return IPC::handleMessage<Messages::NotificationManagerMessageHandler::PageWasNotifiedOfNotificationPermission>(connection, decoder, this, &NotificationManagerMessageHandler::pageWasNotifiedOfNotificationPermission);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NotificationManagerMessageHandler_RequestSystemNotificationPermission>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NotificationManagerMessageHandler::RequestSystemNotificationPermission::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NotificationManagerMessageHandler_RequestSystemNotificationPermission>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NotificationManagerMessageHandler::RequestSystemNotificationPermission::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NotificationManagerMessageHandler_ShowNotification>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NotificationManagerMessageHandler::ShowNotification::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NotificationManagerMessageHandler_ShowNotification>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NotificationManagerMessageHandler::ShowNotification::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NotificationManagerMessageHandler_CancelNotification>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NotificationManagerMessageHandler::CancelNotification::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NotificationManagerMessageHandler_ClearNotifications>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NotificationManagerMessageHandler::ClearNotifications::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NotificationManagerMessageHandler_DidDestroyNotification>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NotificationManagerMessageHandler::DidDestroyNotification::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NotificationManagerMessageHandler_PageWasNotifiedOfNotificationPermission>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NotificationManagerMessageHandler::PageWasNotifiedOfNotificationPermission::Arguments>(globalObject, decoder);
}

}

#endif

