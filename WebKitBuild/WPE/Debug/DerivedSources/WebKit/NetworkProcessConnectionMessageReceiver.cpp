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
#include "NetworkProcessConnection.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "NetworkProcessConnectionMessages.h" // NOLINT
#if ENABLE(SHAREABLE_RESOURCE)
#include "ShareableResource.h" // NOLINT
#endif
#include "WebCoreArgumentCoders.h" // NOLINT
#include <JavaScriptCore/ConsoleTypes.h> // NOLINT
#if HAVE(COOKIE_CHANGE_LISTENER_API)
#include <WebCore/Cookie.h> // NOLINT
#endif
#include <WebCore/HTTPCookieAcceptPolicy.h> // NOLINT
#include <WebCore/MessagePortIdentifier.h> // NOLINT
#if ENABLE(WEB_RTC)
#include <WebCore/RTCDataChannelIdentifier.h> // NOLINT
#endif
#include <WebCore/RegistrableDomain.h> // NOLINT
#include <WebCore/ResourceError.h> // NOLINT
#include <WebCore/ResourceLoaderIdentifier.h> // NOLINT
#if ENABLE(SHAREABLE_RESOURCE)
#include <WebCore/ResourceRequest.h> // NOLINT
#endif
#include <WebCore/ResourceResponse.h> // NOLINT
#if ENABLE(WEB_RTC)
#include <optional> // NOLINT
#endif
#if HAVE(COOKIE_CHANGE_LISTENER_API)
#include <wtf/Vector.h> // NOLINT
#endif
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void NetworkProcessConnection::didReceiveNetworkProcessConnectionMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
#if ENABLE(SHAREABLE_RESOURCE)
    if (decoder.messageName() == Messages::NetworkProcessConnection::DidCacheResource::name())
        return IPC::handleMessage<Messages::NetworkProcessConnection::DidCacheResource>(connection, decoder, this, &NetworkProcessConnection::didCacheResource);
#endif
    if (decoder.messageName() == Messages::NetworkProcessConnection::DidFinishPingLoad::name())
        return IPC::handleMessage<Messages::NetworkProcessConnection::DidFinishPingLoad>(connection, decoder, this, &NetworkProcessConnection::didFinishPingLoad);
    if (decoder.messageName() == Messages::NetworkProcessConnection::DidFinishPreconnection::name())
        return IPC::handleMessage<Messages::NetworkProcessConnection::DidFinishPreconnection>(connection, decoder, this, &NetworkProcessConnection::didFinishPreconnection);
    if (decoder.messageName() == Messages::NetworkProcessConnection::SetOnLineState::name())
        return IPC::handleMessage<Messages::NetworkProcessConnection::SetOnLineState>(connection, decoder, this, &NetworkProcessConnection::setOnLineState);
    if (decoder.messageName() == Messages::NetworkProcessConnection::CookieAcceptPolicyChanged::name())
        return IPC::handleMessage<Messages::NetworkProcessConnection::CookieAcceptPolicyChanged>(connection, decoder, this, &NetworkProcessConnection::cookieAcceptPolicyChanged);
#if HAVE(COOKIE_CHANGE_LISTENER_API)
    if (decoder.messageName() == Messages::NetworkProcessConnection::CookiesAdded::name())
        return IPC::handleMessage<Messages::NetworkProcessConnection::CookiesAdded>(connection, decoder, this, &NetworkProcessConnection::cookiesAdded);
    if (decoder.messageName() == Messages::NetworkProcessConnection::CookiesDeleted::name())
        return IPC::handleMessage<Messages::NetworkProcessConnection::CookiesDeleted>(connection, decoder, this, &NetworkProcessConnection::cookiesDeleted);
    if (decoder.messageName() == Messages::NetworkProcessConnection::AllCookiesDeleted::name())
        return IPC::handleMessage<Messages::NetworkProcessConnection::AllCookiesDeleted>(connection, decoder, this, &NetworkProcessConnection::allCookiesDeleted);
#endif
#if ENABLE(WEB_RTC)
    if (decoder.messageName() == Messages::NetworkProcessConnection::ConnectToRTCDataChannelRemoteSource::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessConnection::ConnectToRTCDataChannelRemoteSource>(connection, decoder, this, &NetworkProcessConnection::connectToRTCDataChannelRemoteSource);
#endif
    if (decoder.messageName() == Messages::NetworkProcessConnection::MessagesAvailableForPort::name())
        return IPC::handleMessage<Messages::NetworkProcessConnection::MessagesAvailableForPort>(connection, decoder, this, &NetworkProcessConnection::messagesAvailableForPort);
    if (decoder.messageName() == Messages::NetworkProcessConnection::BroadcastConsoleMessage::name())
        return IPC::handleMessage<Messages::NetworkProcessConnection::BroadcastConsoleMessage>(connection, decoder, this, &NetworkProcessConnection::broadcastConsoleMessage);
    if (decoder.messageName() == Messages::NetworkProcessConnection::AddAllowedFirstPartyForCookies::name())
        return IPC::handleMessage<Messages::NetworkProcessConnection::AddAllowedFirstPartyForCookies>(connection, decoder, this, &NetworkProcessConnection::addAllowedFirstPartyForCookies);
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

#if ENABLE(SHAREABLE_RESOURCE)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_DidCacheResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::DidCacheResource::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_DidFinishPingLoad>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::DidFinishPingLoad::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_DidFinishPreconnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::DidFinishPreconnection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_SetOnLineState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::SetOnLineState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_CookieAcceptPolicyChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::CookieAcceptPolicyChanged::Arguments>(globalObject, decoder);
}
#if HAVE(COOKIE_CHANGE_LISTENER_API)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_CookiesAdded>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::CookiesAdded::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_CookiesDeleted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::CookiesDeleted::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_AllCookiesDeleted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::AllCookiesDeleted::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(WEB_RTC)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_ConnectToRTCDataChannelRemoteSource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::ConnectToRTCDataChannelRemoteSource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessConnection_ConnectToRTCDataChannelRemoteSource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::ConnectToRTCDataChannelRemoteSource::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_MessagesAvailableForPort>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::MessagesAvailableForPort::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_BroadcastConsoleMessage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::BroadcastConsoleMessage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessConnection_AddAllowedFirstPartyForCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessConnection::AddAllowedFirstPartyForCookies::Arguments>(globalObject, decoder);
}

}

#endif

