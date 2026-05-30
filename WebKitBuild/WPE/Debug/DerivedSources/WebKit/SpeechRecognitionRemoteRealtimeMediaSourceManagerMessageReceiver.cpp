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
#if ENABLE(MEDIA_STREAM)
#include "SpeechRecognitionRemoteRealtimeMediaSourceManager.h"

#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#if PLATFORM(COCOA)
#include "SharedCARingBuffer.h" // NOLINT
#endif
#include "SpeechRecognitionRemoteRealtimeMediaSourceManagerMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#if PLATFORM(COCOA)
#include <WebCore/CAAudioStreamDescription.h> // NOLINT
#endif
#include <WebCore/RealtimeMediaSourceIdentifier.h> // NOLINT
#include <wtf/MediaTime.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void SpeechRecognitionRemoteRealtimeMediaSourceManager::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::RemoteAudioSamplesAvailable::name())
        return IPC::handleMessage<Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::RemoteAudioSamplesAvailable>(connection, decoder, this, &SpeechRecognitionRemoteRealtimeMediaSourceManager::remoteAudioSamplesAvailable);
    if (decoder.messageName() == Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::RemoteCaptureFailed::name())
        return IPC::handleMessage<Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::RemoteCaptureFailed>(connection, decoder, this, &SpeechRecognitionRemoteRealtimeMediaSourceManager::remoteCaptureFailed);
    if (decoder.messageName() == Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::RemoteSourceStopped::name())
        return IPC::handleMessage<Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::RemoteSourceStopped>(connection, decoder, this, &SpeechRecognitionRemoteRealtimeMediaSourceManager::remoteSourceStopped);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::SetStorage::name())
        return IPC::handleMessage<Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::SetStorage>(connection, decoder, this, &SpeechRecognitionRemoteRealtimeMediaSourceManager::setStorage);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteAudioSamplesAvailable>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::RemoteAudioSamplesAvailable::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteCaptureFailed>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::RemoteCaptureFailed::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteSourceStopped>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::RemoteSourceStopped::Arguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::SpeechRecognitionRemoteRealtimeMediaSourceManager_SetStorage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::SpeechRecognitionRemoteRealtimeMediaSourceManager::SetStorage::Arguments>(globalObject, decoder);
}
#endif

}

#endif


#endif // ENABLE(MEDIA_STREAM)
