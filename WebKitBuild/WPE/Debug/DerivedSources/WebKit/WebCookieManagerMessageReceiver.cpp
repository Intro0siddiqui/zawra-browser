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
#include "WebCookieManager.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#if USE(SOUP)
#include "SoupCookiePersistentStorageType.h" // NOLINT
#endif
#include "WebCookieManagerMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/Cookie.h> // NOLINT
#include <WebCore/HTTPCookieAcceptPolicy.h> // NOLINT
#include <pal/SessionID.h> // NOLINT
#include <wtf/URLHash.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/WallTime.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebCookieManager::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::WebCookieManager::GetHostnamesWithCookies::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::GetHostnamesWithCookies>(connection, decoder, this, &WebCookieManager::getHostnamesWithCookies);
    if (decoder.messageName() == Messages::WebCookieManager::DeleteCookiesForHostnames::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::DeleteCookiesForHostnames>(connection, decoder, this, &WebCookieManager::deleteCookiesForHostnames);
    if (decoder.messageName() == Messages::WebCookieManager::DeleteAllCookies::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::DeleteAllCookies>(connection, decoder, this, &WebCookieManager::deleteAllCookies);
    if (decoder.messageName() == Messages::WebCookieManager::SetCookie::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::SetCookie>(connection, decoder, this, &WebCookieManager::setCookie);
    if (decoder.messageName() == Messages::WebCookieManager::SetCookies::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::SetCookies>(connection, decoder, this, &WebCookieManager::setCookies);
    if (decoder.messageName() == Messages::WebCookieManager::GetAllCookies::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::GetAllCookies>(connection, decoder, this, &WebCookieManager::getAllCookies);
    if (decoder.messageName() == Messages::WebCookieManager::GetCookies::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::GetCookies>(connection, decoder, this, &WebCookieManager::getCookies);
    if (decoder.messageName() == Messages::WebCookieManager::DeleteCookie::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::DeleteCookie>(connection, decoder, this, &WebCookieManager::deleteCookie);
    if (decoder.messageName() == Messages::WebCookieManager::DeleteAllCookiesModifiedSince::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::DeleteAllCookiesModifiedSince>(connection, decoder, this, &WebCookieManager::deleteAllCookiesModifiedSince);
    if (decoder.messageName() == Messages::WebCookieManager::SetHTTPCookieAcceptPolicy::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::SetHTTPCookieAcceptPolicy>(connection, decoder, this, &WebCookieManager::setHTTPCookieAcceptPolicy);
    if (decoder.messageName() == Messages::WebCookieManager::GetHTTPCookieAcceptPolicy::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::GetHTTPCookieAcceptPolicy>(connection, decoder, this, &WebCookieManager::getHTTPCookieAcceptPolicy);
    if (decoder.messageName() == Messages::WebCookieManager::StartObservingCookieChanges::name())
        return IPC::handleMessage<Messages::WebCookieManager::StartObservingCookieChanges>(connection, decoder, this, &WebCookieManager::startObservingCookieChanges);
    if (decoder.messageName() == Messages::WebCookieManager::StopObservingCookieChanges::name())
        return IPC::handleMessage<Messages::WebCookieManager::StopObservingCookieChanges>(connection, decoder, this, &WebCookieManager::stopObservingCookieChanges);
#if USE(SOUP)
    if (decoder.messageName() == Messages::WebCookieManager::ReplaceCookies::name())
        return IPC::handleMessageAsync<Messages::WebCookieManager::ReplaceCookies>(connection, decoder, this, &WebCookieManager::replaceCookies);
    if (decoder.messageName() == Messages::WebCookieManager::SetCookiePersistentStorage::name())
        return IPC::handleMessage<Messages::WebCookieManager::SetCookiePersistentStorage>(connection, decoder, this, &WebCookieManager::setCookiePersistentStorage);
#endif
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_GetHostnamesWithCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::GetHostnamesWithCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_GetHostnamesWithCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::GetHostnamesWithCookies::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_DeleteCookiesForHostnames>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::DeleteCookiesForHostnames::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_DeleteCookiesForHostnames>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::DeleteCookiesForHostnames::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_DeleteAllCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::DeleteAllCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_DeleteAllCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::DeleteAllCookies::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_SetCookie>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::SetCookie::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_SetCookie>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::SetCookie::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_SetCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::SetCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_SetCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::SetCookies::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_GetAllCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::GetAllCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_GetAllCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::GetAllCookies::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_GetCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::GetCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_GetCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::GetCookies::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_DeleteCookie>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::DeleteCookie::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_DeleteCookie>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::DeleteCookie::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_DeleteAllCookiesModifiedSince>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::DeleteAllCookiesModifiedSince::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_DeleteAllCookiesModifiedSince>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::DeleteAllCookiesModifiedSince::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_SetHTTPCookieAcceptPolicy>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::SetHTTPCookieAcceptPolicy::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_SetHTTPCookieAcceptPolicy>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::SetHTTPCookieAcceptPolicy::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_GetHTTPCookieAcceptPolicy>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::GetHTTPCookieAcceptPolicy::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_GetHTTPCookieAcceptPolicy>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::GetHTTPCookieAcceptPolicy::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_StartObservingCookieChanges>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::StartObservingCookieChanges::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_StopObservingCookieChanges>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::StopObservingCookieChanges::Arguments>(globalObject, decoder);
}
#if USE(SOUP)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_ReplaceCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::ReplaceCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebCookieManager_ReplaceCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::ReplaceCookies::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebCookieManager_SetCookiePersistentStorage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebCookieManager::SetCookiePersistentStorage::Arguments>(globalObject, decoder);
}
#endif

}

#endif

