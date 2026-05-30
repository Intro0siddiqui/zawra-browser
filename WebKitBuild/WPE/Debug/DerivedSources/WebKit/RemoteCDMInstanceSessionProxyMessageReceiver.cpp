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
#if ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)
#include "RemoteCDMInstanceSessionProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteCDMInstanceSessionProxyMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/CDMInstanceSession.h> // NOLINT
#include <WebCore/SharedBuffer.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/RefCounted.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteCDMInstanceSessionProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteCDMInstanceSessionProxy::SetLogIdentifier::name())
        return IPC::handleMessage<Messages::RemoteCDMInstanceSessionProxy::SetLogIdentifier>(connection, decoder, this, &RemoteCDMInstanceSessionProxy::setLogIdentifier);
    if (decoder.messageName() == Messages::RemoteCDMInstanceSessionProxy::RequestLicense::name())
        return IPC::handleMessageAsync<Messages::RemoteCDMInstanceSessionProxy::RequestLicense>(connection, decoder, this, &RemoteCDMInstanceSessionProxy::requestLicense);
    if (decoder.messageName() == Messages::RemoteCDMInstanceSessionProxy::UpdateLicense::name())
        return IPC::handleMessageAsync<Messages::RemoteCDMInstanceSessionProxy::UpdateLicense>(connection, decoder, this, &RemoteCDMInstanceSessionProxy::updateLicense);
    if (decoder.messageName() == Messages::RemoteCDMInstanceSessionProxy::LoadSession::name())
        return IPC::handleMessageAsync<Messages::RemoteCDMInstanceSessionProxy::LoadSession>(connection, decoder, this, &RemoteCDMInstanceSessionProxy::loadSession);
    if (decoder.messageName() == Messages::RemoteCDMInstanceSessionProxy::CloseSession::name())
        return IPC::handleMessageAsync<Messages::RemoteCDMInstanceSessionProxy::CloseSession>(connection, decoder, this, &RemoteCDMInstanceSessionProxy::closeSession);
    if (decoder.messageName() == Messages::RemoteCDMInstanceSessionProxy::RemoveSessionData::name())
        return IPC::handleMessageAsync<Messages::RemoteCDMInstanceSessionProxy::RemoveSessionData>(connection, decoder, this, &RemoteCDMInstanceSessionProxy::removeSessionData);
    if (decoder.messageName() == Messages::RemoteCDMInstanceSessionProxy::StoreRecordOfKeyUsage::name())
        return IPC::handleMessage<Messages::RemoteCDMInstanceSessionProxy::StoreRecordOfKeyUsage>(connection, decoder, this, &RemoteCDMInstanceSessionProxy::storeRecordOfKeyUsage);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCDMInstanceSessionProxy_SetLogIdentifier>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::SetLogIdentifier::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCDMInstanceSessionProxy_RequestLicense>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::RequestLicense::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteCDMInstanceSessionProxy_RequestLicense>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::RequestLicense::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCDMInstanceSessionProxy_UpdateLicense>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::UpdateLicense::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteCDMInstanceSessionProxy_UpdateLicense>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::UpdateLicense::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCDMInstanceSessionProxy_LoadSession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::LoadSession::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteCDMInstanceSessionProxy_LoadSession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::LoadSession::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCDMInstanceSessionProxy_CloseSession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::CloseSession::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteCDMInstanceSessionProxy_CloseSession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::CloseSession::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCDMInstanceSessionProxy_RemoveSessionData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::RemoveSessionData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteCDMInstanceSessionProxy_RemoveSessionData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::RemoveSessionData::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteCDMInstanceSessionProxy_StoreRecordOfKeyUsage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteCDMInstanceSessionProxy::StoreRecordOfKeyUsage::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)
