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
#if ENABLE(GPU_PROCESS) && USE(AUDIO_SESSION)
#include "RemoteAudioSessionProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteAudioSessionProxyMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/AudioSession.h> // NOLINT
#include <optional> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteAudioSessionProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteAudioSessionProxy::SetCategory::name())
        return IPC::handleMessage<Messages::RemoteAudioSessionProxy::SetCategory>(connection, decoder, this, &RemoteAudioSessionProxy::setCategory);
    if (decoder.messageName() == Messages::RemoteAudioSessionProxy::SetPreferredBufferSize::name())
        return IPC::handleMessage<Messages::RemoteAudioSessionProxy::SetPreferredBufferSize>(connection, decoder, this, &RemoteAudioSessionProxy::setPreferredBufferSize);
    if (decoder.messageName() == Messages::RemoteAudioSessionProxy::SetIsPlayingToBluetoothOverride::name())
        return IPC::handleMessage<Messages::RemoteAudioSessionProxy::SetIsPlayingToBluetoothOverride>(connection, decoder, this, &RemoteAudioSessionProxy::setIsPlayingToBluetoothOverride);
    if (decoder.messageName() == Messages::RemoteAudioSessionProxy::TriggerBeginInterruptionForTesting::name())
        return IPC::handleMessage<Messages::RemoteAudioSessionProxy::TriggerBeginInterruptionForTesting>(connection, decoder, this, &RemoteAudioSessionProxy::triggerBeginInterruptionForTesting);
    if (decoder.messageName() == Messages::RemoteAudioSessionProxy::TriggerEndInterruptionForTesting::name())
        return IPC::handleMessage<Messages::RemoteAudioSessionProxy::TriggerEndInterruptionForTesting>(connection, decoder, this, &RemoteAudioSessionProxy::triggerEndInterruptionForTesting);
    if (decoder.messageName() == Messages::RemoteAudioSessionProxy::BeginInterruptionRemote::name())
        return IPC::handleMessage<Messages::RemoteAudioSessionProxy::BeginInterruptionRemote>(connection, decoder, this, &RemoteAudioSessionProxy::beginInterruptionRemote);
    if (decoder.messageName() == Messages::RemoteAudioSessionProxy::EndInterruptionRemote::name())
        return IPC::handleMessage<Messages::RemoteAudioSessionProxy::EndInterruptionRemote>(connection, decoder, this, &RemoteAudioSessionProxy::endInterruptionRemote);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool RemoteAudioSessionProxy::didReceiveSyncMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    if (decoder.messageName() == Messages::RemoteAudioSessionProxy::TryToSetActive::name())
        return IPC::handleMessageSynchronous<Messages::RemoteAudioSessionProxy::TryToSetActive>(connection, decoder, replyEncoder, this, &RemoteAudioSessionProxy::tryToSetActive);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
    UNUSED_PARAM(replyEncoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return false;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled synchronous message %s to %" PRIu64, description(decoder.messageName()), decoder.destinationID());
    return false;
}

} // namespace WebKit

#if ENABLE(IPC_TESTING_API)

namespace IPC {

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioSessionProxy_SetCategory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioSessionProxy::SetCategory::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioSessionProxy_SetPreferredBufferSize>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioSessionProxy::SetPreferredBufferSize::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioSessionProxy_TryToSetActive>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioSessionProxy::TryToSetActive::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteAudioSessionProxy_TryToSetActive>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioSessionProxy::TryToSetActive::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioSessionProxy_SetIsPlayingToBluetoothOverride>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioSessionProxy::SetIsPlayingToBluetoothOverride::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioSessionProxy_TriggerBeginInterruptionForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioSessionProxy::TriggerBeginInterruptionForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioSessionProxy_TriggerEndInterruptionForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioSessionProxy::TriggerEndInterruptionForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioSessionProxy_BeginInterruptionRemote>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioSessionProxy::BeginInterruptionRemote::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioSessionProxy_EndInterruptionRemote>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioSessionProxy::EndInterruptionRemote::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS) && USE(AUDIO_SESSION)
