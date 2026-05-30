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
#if USE(LIBWEBRTC) && PLATFORM(COCOA) && ENABLE(GPU_PROCESS)
#include "LibWebRTCCodecsProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "DataReference.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "IPCSemaphore.h" // NOLINT
#include "LibWebRTCCodecsProxyMessages.h" // NOLINT
#include "SharedMemory.h" // NOLINT
#include "SharedVideoFrame.h" // NOLINT
#include "VideoCodecType.h" // NOLINT
#include "VideoDecoderIdentifier.h" // NOLINT
#include "VideoEncoderIdentifier.h" // NOLINT
#include <optional> // NOLINT
#include <utility> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void LibWebRTCCodecsProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::CreateDecoder::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::CreateDecoder>(connection, decoder, this, &LibWebRTCCodecsProxy::createDecoder);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::ReleaseDecoder::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::ReleaseDecoder>(connection, decoder, this, &LibWebRTCCodecsProxy::releaseDecoder);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::FlushDecoder::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::FlushDecoder>(connection, decoder, this, &LibWebRTCCodecsProxy::flushDecoder);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::SetDecoderFormatDescription::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::SetDecoderFormatDescription>(connection, decoder, this, &LibWebRTCCodecsProxy::setDecoderFormatDescription);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::DecodeFrame::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::DecodeFrame>(connection, decoder, this, &LibWebRTCCodecsProxy::decodeFrame);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::SetFrameSize::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::SetFrameSize>(connection, decoder, this, &LibWebRTCCodecsProxy::setFrameSize);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::CreateEncoder::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::CreateEncoder>(connection, decoder, this, &LibWebRTCCodecsProxy::createEncoder);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::ReleaseEncoder::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::ReleaseEncoder>(connection, decoder, this, &LibWebRTCCodecsProxy::releaseEncoder);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::InitializeEncoder::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::InitializeEncoder>(connection, decoder, this, &LibWebRTCCodecsProxy::initializeEncoder);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::EncodeFrame::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::EncodeFrame>(connection, decoder, this, &LibWebRTCCodecsProxy::encodeFrame);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::FlushEncoder::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::FlushEncoder>(connection, decoder, this, &LibWebRTCCodecsProxy::flushEncoder);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::SetEncodeRates::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::SetEncodeRates>(connection, decoder, this, &LibWebRTCCodecsProxy::setEncodeRates);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::SetSharedVideoFrameSemaphore::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::SetSharedVideoFrameSemaphore>(connection, decoder, this, &LibWebRTCCodecsProxy::setSharedVideoFrameSemaphore);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::SetSharedVideoFrameMemory::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::SetSharedVideoFrameMemory>(connection, decoder, this, &LibWebRTCCodecsProxy::setSharedVideoFrameMemory);
    if (decoder.messageName() == Messages::LibWebRTCCodecsProxy::SetRTCLoggingLevel::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecsProxy::SetRTCLoggingLevel>(connection, decoder, this, &LibWebRTCCodecsProxy::setRTCLoggingLevel);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_CreateDecoder>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::CreateDecoder::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_ReleaseDecoder>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::ReleaseDecoder::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_FlushDecoder>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::FlushDecoder::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_SetDecoderFormatDescription>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::SetDecoderFormatDescription::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_DecodeFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::DecodeFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_SetFrameSize>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::SetFrameSize::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_CreateEncoder>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::CreateEncoder::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_ReleaseEncoder>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::ReleaseEncoder::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_InitializeEncoder>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::InitializeEncoder::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_EncodeFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::EncodeFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_FlushEncoder>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::FlushEncoder::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_SetEncodeRates>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::SetEncodeRates::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_SetSharedVideoFrameSemaphore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::SetSharedVideoFrameSemaphore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_SetSharedVideoFrameMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::SetSharedVideoFrameMemory::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecsProxy_SetRTCLoggingLevel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecsProxy::SetRTCLoggingLevel::Arguments>(globalObject, decoder);
}

}

#endif


#endif // USE(LIBWEBRTC) && PLATFORM(COCOA) && ENABLE(GPU_PROCESS)
