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
#if ENABLE(GPU_PROCESS) && ENABLE(WEB_AUDIO)
#include "RemoteAudioDestinationManager.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "IPCSemaphore.h" // NOLINT
#include "RemoteAudioDestinationIdentifier.h" // NOLINT
#include "RemoteAudioDestinationManagerMessages.h" // NOLINT
#if PLATFORM(COCOA)
#include "SharedCARingBuffer.h" // NOLINT
#endif
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteAudioDestinationManager::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteAudioDestinationManager::CreateAudioDestination::name())
        return IPC::handleMessage<Messages::RemoteAudioDestinationManager::CreateAudioDestination>(connection, decoder, this, &RemoteAudioDestinationManager::createAudioDestination);
    if (decoder.messageName() == Messages::RemoteAudioDestinationManager::DeleteAudioDestination::name())
        return IPC::handleMessage<Messages::RemoteAudioDestinationManager::DeleteAudioDestination>(connection, decoder, this, &RemoteAudioDestinationManager::deleteAudioDestination);
    if (decoder.messageName() == Messages::RemoteAudioDestinationManager::StartAudioDestination::name())
        return IPC::handleMessageAsync<Messages::RemoteAudioDestinationManager::StartAudioDestination>(connection, decoder, this, &RemoteAudioDestinationManager::startAudioDestination);
    if (decoder.messageName() == Messages::RemoteAudioDestinationManager::StopAudioDestination::name())
        return IPC::handleMessageAsync<Messages::RemoteAudioDestinationManager::StopAudioDestination>(connection, decoder, this, &RemoteAudioDestinationManager::stopAudioDestination);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::RemoteAudioDestinationManager::AudioSamplesStorageChanged::name())
        return IPC::handleMessage<Messages::RemoteAudioDestinationManager::AudioSamplesStorageChanged>(connection, decoder, this, &RemoteAudioDestinationManager::audioSamplesStorageChanged);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioDestinationManager_CreateAudioDestination>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioDestinationManager::CreateAudioDestination::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioDestinationManager_DeleteAudioDestination>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioDestinationManager::DeleteAudioDestination::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioDestinationManager_StartAudioDestination>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioDestinationManager::StartAudioDestination::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteAudioDestinationManager_StartAudioDestination>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioDestinationManager::StartAudioDestination::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioDestinationManager_StopAudioDestination>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioDestinationManager::StopAudioDestination::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteAudioDestinationManager_StopAudioDestination>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioDestinationManager::StopAudioDestination::ReplyArguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteAudioDestinationManager_AudioSamplesStorageChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteAudioDestinationManager::AudioSamplesStorageChanged::Arguments>(globalObject, decoder);
}
#endif

}

#endif


#endif // ENABLE(GPU_PROCESS) && ENABLE(WEB_AUDIO)
