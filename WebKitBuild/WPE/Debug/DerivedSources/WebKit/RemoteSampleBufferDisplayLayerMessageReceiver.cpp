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
#include "RemoteSampleBufferDisplayLayer.h"

#include "ArgumentCoders.h" // NOLINT
#include "ArgumentCodersDarwin.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "IPCSemaphore.h" // NOLINT
#include "RemoteSampleBufferDisplayLayerMessages.h" // NOLINT
#include "SharedMemory.h" // NOLINT
#include "SharedVideoFrame.h" // NOLINT
#include <optional> // NOLINT
#include <wtf/MachSendRight.h> // NOLINT
#if !RELEASE_LOG_DISABLED
#include <wtf/text/WTFString.h> // NOLINT
#endif

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteSampleBufferDisplayLayer::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
#if !RELEASE_LOG_DISABLED
    if (decoder.messageName() == Messages::RemoteSampleBufferDisplayLayer::SetLogIdentifier::name())
        return IPC::handleMessage<Messages::RemoteSampleBufferDisplayLayer::SetLogIdentifier>(connection, decoder, this, &RemoteSampleBufferDisplayLayer::setLogIdentifier);
#endif
    if (decoder.messageName() == Messages::RemoteSampleBufferDisplayLayer::UpdateDisplayMode::name())
        return IPC::handleMessage<Messages::RemoteSampleBufferDisplayLayer::UpdateDisplayMode>(connection, decoder, this, &RemoteSampleBufferDisplayLayer::updateDisplayMode);
    if (decoder.messageName() == Messages::RemoteSampleBufferDisplayLayer::UpdateBoundsAndPosition::name())
        return IPC::handleMessage<Messages::RemoteSampleBufferDisplayLayer::UpdateBoundsAndPosition>(connection, decoder, this, &RemoteSampleBufferDisplayLayer::updateBoundsAndPosition);
    if (decoder.messageName() == Messages::RemoteSampleBufferDisplayLayer::Flush::name())
        return IPC::handleMessage<Messages::RemoteSampleBufferDisplayLayer::Flush>(connection, decoder, this, &RemoteSampleBufferDisplayLayer::flush);
    if (decoder.messageName() == Messages::RemoteSampleBufferDisplayLayer::FlushAndRemoveImage::name())
        return IPC::handleMessage<Messages::RemoteSampleBufferDisplayLayer::FlushAndRemoveImage>(connection, decoder, this, &RemoteSampleBufferDisplayLayer::flushAndRemoveImage);
    if (decoder.messageName() == Messages::RemoteSampleBufferDisplayLayer::EnqueueVideoFrame::name())
        return IPC::handleMessage<Messages::RemoteSampleBufferDisplayLayer::EnqueueVideoFrame>(connection, decoder, this, &RemoteSampleBufferDisplayLayer::enqueueVideoFrame);
    if (decoder.messageName() == Messages::RemoteSampleBufferDisplayLayer::ClearVideoFrames::name())
        return IPC::handleMessage<Messages::RemoteSampleBufferDisplayLayer::ClearVideoFrames>(connection, decoder, this, &RemoteSampleBufferDisplayLayer::clearVideoFrames);
    if (decoder.messageName() == Messages::RemoteSampleBufferDisplayLayer::Play::name())
        return IPC::handleMessage<Messages::RemoteSampleBufferDisplayLayer::Play>(connection, decoder, this, &RemoteSampleBufferDisplayLayer::play);
    if (decoder.messageName() == Messages::RemoteSampleBufferDisplayLayer::Pause::name())
        return IPC::handleMessage<Messages::RemoteSampleBufferDisplayLayer::Pause>(connection, decoder, this, &RemoteSampleBufferDisplayLayer::pause);
    if (decoder.messageName() == Messages::RemoteSampleBufferDisplayLayer::SetSharedVideoFrameSemaphore::name())
        return IPC::handleMessage<Messages::RemoteSampleBufferDisplayLayer::SetSharedVideoFrameSemaphore>(connection, decoder, this, &RemoteSampleBufferDisplayLayer::setSharedVideoFrameSemaphore);
    if (decoder.messageName() == Messages::RemoteSampleBufferDisplayLayer::SetSharedVideoFrameMemory::name())
        return IPC::handleMessage<Messages::RemoteSampleBufferDisplayLayer::SetSharedVideoFrameMemory>(connection, decoder, this, &RemoteSampleBufferDisplayLayer::setSharedVideoFrameMemory);
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

#if !RELEASE_LOG_DISABLED
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSampleBufferDisplayLayer_SetLogIdentifier>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSampleBufferDisplayLayer::SetLogIdentifier::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSampleBufferDisplayLayer_UpdateDisplayMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSampleBufferDisplayLayer::UpdateDisplayMode::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSampleBufferDisplayLayer_UpdateBoundsAndPosition>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSampleBufferDisplayLayer::UpdateBoundsAndPosition::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSampleBufferDisplayLayer_Flush>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSampleBufferDisplayLayer::Flush::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSampleBufferDisplayLayer_FlushAndRemoveImage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSampleBufferDisplayLayer::FlushAndRemoveImage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSampleBufferDisplayLayer_EnqueueVideoFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSampleBufferDisplayLayer::EnqueueVideoFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSampleBufferDisplayLayer_ClearVideoFrames>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSampleBufferDisplayLayer::ClearVideoFrames::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSampleBufferDisplayLayer_Play>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSampleBufferDisplayLayer::Play::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSampleBufferDisplayLayer_Pause>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSampleBufferDisplayLayer::Pause::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSampleBufferDisplayLayer_SetSharedVideoFrameSemaphore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSampleBufferDisplayLayer::SetSharedVideoFrameSemaphore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteSampleBufferDisplayLayer_SetSharedVideoFrameMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteSampleBufferDisplayLayer::SetSharedVideoFrameMemory::Arguments>(globalObject, decoder);
}

}

#endif


#endif // PLATFORM(COCOA) && ENABLE(GPU_PROCESS) && ENABLE(MEDIA_STREAM)
