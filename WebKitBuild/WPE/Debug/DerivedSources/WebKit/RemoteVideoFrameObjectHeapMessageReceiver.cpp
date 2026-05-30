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
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
#include "RemoteVideoFrameObjectHeap.h"

#if PLATFORM(COCOA)
#include "ArgumentCodersCF.h" // NOLINT
#endif
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#if PLATFORM(COCOA)
#include "IPCSemaphore.h" // NOLINT
#endif
#include "RemoteVideoFrameIdentifier.h" // NOLINT
#include "RemoteVideoFrameObjectHeapMessages.h" // NOLINT
#if PLATFORM(COCOA)
#include "SharedMemory.h" // NOLINT
#endif
#if PLATFORM(COCOA)
#include "SharedVideoFrame.h" // NOLINT
#endif
#if PLATFORM(COCOA)
#include "WebCoreArgumentCoders.h" // NOLINT
#endif
#if PLATFORM(COCOA)
#include <WebCore/CVUtilities.h> // NOLINT
#endif
#if PLATFORM(COCOA)
#include <WebCore/DestinationColorSpace.h> // NOLINT
#endif
#if PLATFORM(COCOA)
#include <wtf/RetainPtr.h> // NOLINT
#endif

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteVideoFrameObjectHeap::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::RemoteVideoFrameObjectHeap::GetVideoFrameBuffer::name())
        return IPC::handleMessage<Messages::RemoteVideoFrameObjectHeap::GetVideoFrameBuffer>(connection, decoder, this, &RemoteVideoFrameObjectHeap::getVideoFrameBuffer);
    if (decoder.messageName() == Messages::RemoteVideoFrameObjectHeap::SetSharedVideoFrameSemaphore::name())
        return IPC::handleMessage<Messages::RemoteVideoFrameObjectHeap::SetSharedVideoFrameSemaphore>(connection, decoder, this, &RemoteVideoFrameObjectHeap::setSharedVideoFrameSemaphore);
    if (decoder.messageName() == Messages::RemoteVideoFrameObjectHeap::SetSharedVideoFrameMemory::name())
        return IPC::handleMessage<Messages::RemoteVideoFrameObjectHeap::SetSharedVideoFrameMemory>(connection, decoder, this, &RemoteVideoFrameObjectHeap::setSharedVideoFrameMemory);
#endif
    if (decoder.messageName() == Messages::RemoteVideoFrameObjectHeap::ReleaseVideoFrame::name())
        return IPC::handleMessage<Messages::RemoteVideoFrameObjectHeap::ReleaseVideoFrame>(connection, decoder, this, &RemoteVideoFrameObjectHeap::releaseVideoFrame);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool RemoteVideoFrameObjectHeap::didReceiveSyncMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::RemoteVideoFrameObjectHeap::PixelBuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteVideoFrameObjectHeap::PixelBuffer>(connection, decoder, replyEncoder, this, &RemoteVideoFrameObjectHeap::pixelBuffer);
    if (decoder.messageName() == Messages::RemoteVideoFrameObjectHeap::ConvertFrameBuffer::name())
        return IPC::handleMessageSynchronous<Messages::RemoteVideoFrameObjectHeap::ConvertFrameBuffer>(connection, decoder, replyEncoder, this, &RemoteVideoFrameObjectHeap::convertFrameBuffer);
#endif
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

#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteVideoFrameObjectHeap_GetVideoFrameBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteVideoFrameObjectHeap::GetVideoFrameBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteVideoFrameObjectHeap_PixelBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteVideoFrameObjectHeap::PixelBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteVideoFrameObjectHeap_PixelBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteVideoFrameObjectHeap::PixelBuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteVideoFrameObjectHeap_SetSharedVideoFrameSemaphore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteVideoFrameObjectHeap::SetSharedVideoFrameSemaphore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteVideoFrameObjectHeap_SetSharedVideoFrameMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteVideoFrameObjectHeap::SetSharedVideoFrameMemory::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteVideoFrameObjectHeap_ConvertFrameBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteVideoFrameObjectHeap::ConvertFrameBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteVideoFrameObjectHeap_ConvertFrameBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteVideoFrameObjectHeap::ConvertFrameBuffer::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteVideoFrameObjectHeap_ReleaseVideoFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteVideoFrameObjectHeap::ReleaseVideoFrame::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
