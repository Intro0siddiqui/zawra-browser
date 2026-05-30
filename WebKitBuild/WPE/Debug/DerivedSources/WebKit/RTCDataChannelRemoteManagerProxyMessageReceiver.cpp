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
#if ENABLE(WEB_RTC)
#include "RTCDataChannelRemoteManagerProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "DataReference.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RTCDataChannelRemoteManagerProxyMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/RTCDataChannelIdentifier.h> // NOLINT
#include <WebCore/RTCDataChannelState.h> // NOLINT
#include <WebCore/RTCErrorDetailType.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RTCDataChannelRemoteManagerProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RTCDataChannelRemoteManagerProxy::SendData::name())
        return IPC::handleMessage<Messages::RTCDataChannelRemoteManagerProxy::SendData>(connection, decoder, this, &RTCDataChannelRemoteManagerProxy::sendData);
    if (decoder.messageName() == Messages::RTCDataChannelRemoteManagerProxy::Close::name())
        return IPC::handleMessage<Messages::RTCDataChannelRemoteManagerProxy::Close>(connection, decoder, this, &RTCDataChannelRemoteManagerProxy::close);
    if (decoder.messageName() == Messages::RTCDataChannelRemoteManagerProxy::ChangeReadyState::name())
        return IPC::handleMessage<Messages::RTCDataChannelRemoteManagerProxy::ChangeReadyState>(connection, decoder, this, &RTCDataChannelRemoteManagerProxy::changeReadyState);
    if (decoder.messageName() == Messages::RTCDataChannelRemoteManagerProxy::ReceiveData::name())
        return IPC::handleMessage<Messages::RTCDataChannelRemoteManagerProxy::ReceiveData>(connection, decoder, this, &RTCDataChannelRemoteManagerProxy::receiveData);
    if (decoder.messageName() == Messages::RTCDataChannelRemoteManagerProxy::DetectError::name())
        return IPC::handleMessage<Messages::RTCDataChannelRemoteManagerProxy::DetectError>(connection, decoder, this, &RTCDataChannelRemoteManagerProxy::detectError);
    if (decoder.messageName() == Messages::RTCDataChannelRemoteManagerProxy::BufferedAmountIsDecreasing::name())
        return IPC::handleMessage<Messages::RTCDataChannelRemoteManagerProxy::BufferedAmountIsDecreasing>(connection, decoder, this, &RTCDataChannelRemoteManagerProxy::bufferedAmountIsDecreasing);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RTCDataChannelRemoteManagerProxy_SendData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RTCDataChannelRemoteManagerProxy::SendData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RTCDataChannelRemoteManagerProxy_Close>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RTCDataChannelRemoteManagerProxy::Close::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RTCDataChannelRemoteManagerProxy_ChangeReadyState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RTCDataChannelRemoteManagerProxy::ChangeReadyState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RTCDataChannelRemoteManagerProxy_ReceiveData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RTCDataChannelRemoteManagerProxy::ReceiveData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RTCDataChannelRemoteManagerProxy_DetectError>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RTCDataChannelRemoteManagerProxy::DetectError::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RTCDataChannelRemoteManagerProxy_BufferedAmountIsDecreasing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RTCDataChannelRemoteManagerProxy::BufferedAmountIsDecreasing::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(WEB_RTC)
