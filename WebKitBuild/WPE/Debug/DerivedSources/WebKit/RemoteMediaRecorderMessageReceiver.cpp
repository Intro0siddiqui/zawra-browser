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
#if PLATFORM(COCOA) && ENABLE(GPU_PROCESS) && ENABLE(MEDIA_STREAM)
#include "RemoteMediaRecorder.h"

#include "DataReference.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "IPCSemaphore.h" // NOLINT
#include "RemoteMediaRecorderMessages.h" // NOLINT
#include "SharedCARingBuffer.h" // NOLINT
#include "SharedMemory.h" // NOLINT
#include "SharedVideoFrame.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/CAAudioStreamDescription.h> // NOLINT
#include <wtf/MediaTime.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteMediaRecorder::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::RemoteMediaRecorder::AudioSamplesStorageChanged::name())
        return IPC::handleMessage<Messages::RemoteMediaRecorder::AudioSamplesStorageChanged>(connection, decoder, this, &RemoteMediaRecorder::audioSamplesStorageChanged);
    if (decoder.messageName() == Messages::RemoteMediaRecorder::AudioSamplesAvailable::name())
        return IPC::handleMessage<Messages::RemoteMediaRecorder::AudioSamplesAvailable>(connection, decoder, this, &RemoteMediaRecorder::audioSamplesAvailable);
    if (decoder.messageName() == Messages::RemoteMediaRecorder::VideoFrameAvailable::name())
        return IPC::handleMessage<Messages::RemoteMediaRecorder::VideoFrameAvailable>(connection, decoder, this, &RemoteMediaRecorder::videoFrameAvailable);
    if (decoder.messageName() == Messages::RemoteMediaRecorder::FetchData::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaRecorder::FetchData>(connection, decoder, this, &RemoteMediaRecorder::fetchData);
    if (decoder.messageName() == Messages::RemoteMediaRecorder::StopRecording::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaRecorder::StopRecording>(connection, decoder, this, &RemoteMediaRecorder::stopRecording);
    if (decoder.messageName() == Messages::RemoteMediaRecorder::Pause::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaRecorder::Pause>(connection, decoder, this, &RemoteMediaRecorder::pause);
    if (decoder.messageName() == Messages::RemoteMediaRecorder::Resume::name())
        return IPC::handleMessageAsync<Messages::RemoteMediaRecorder::Resume>(connection, decoder, this, &RemoteMediaRecorder::resume);
    if (decoder.messageName() == Messages::RemoteMediaRecorder::SetSharedVideoFrameSemaphore::name())
        return IPC::handleMessage<Messages::RemoteMediaRecorder::SetSharedVideoFrameSemaphore>(connection, decoder, this, &RemoteMediaRecorder::setSharedVideoFrameSemaphore);
    if (decoder.messageName() == Messages::RemoteMediaRecorder::SetSharedVideoFrameMemory::name())
        return IPC::handleMessage<Messages::RemoteMediaRecorder::SetSharedVideoFrameMemory>(connection, decoder, this, &RemoteMediaRecorder::setSharedVideoFrameMemory);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaRecorder_AudioSamplesStorageChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::AudioSamplesStorageChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaRecorder_AudioSamplesAvailable>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::AudioSamplesAvailable::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaRecorder_VideoFrameAvailable>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::VideoFrameAvailable::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaRecorder_FetchData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::FetchData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaRecorder_FetchData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::FetchData::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaRecorder_StopRecording>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::StopRecording::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaRecorder_StopRecording>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::StopRecording::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaRecorder_Pause>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::Pause::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaRecorder_Pause>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::Pause::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaRecorder_Resume>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::Resume::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteMediaRecorder_Resume>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::Resume::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaRecorder_SetSharedVideoFrameSemaphore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::SetSharedVideoFrameSemaphore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteMediaRecorder_SetSharedVideoFrameMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteMediaRecorder::SetSharedVideoFrameMemory::Arguments>(globalObject, decoder);
}

}

#endif


#endif // PLATFORM(COCOA) && ENABLE(GPU_PROCESS) && ENABLE(MEDIA_STREAM)
