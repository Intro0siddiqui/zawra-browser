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
#include "LibWebRTCCodecs.h"

#include "ArgumentCoders.h" // NOLINT
#include "ArgumentCodersCF.h" // NOLINT
#include "DataReference.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "LibWebRTCCodecsMessages.h" // NOLINT
#include "RTCWebKitEncodedFrameInfo.h" // NOLINT
#include "RemoteVideoFrameProxy.h" // NOLINT
#include "VideoDecoderIdentifier.h" // NOLINT
#include "VideoEncoderIdentifier.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/CVUtilities.h> // NOLINT
#include <WebCore/LibWebRTCEnumTraits.h> // NOLINT
#include <WebCore/PlatformVideoColorSpace.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/RetainPtr.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void LibWebRTCCodecs::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::LibWebRTCCodecs::FailedDecoding::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecs::FailedDecoding>(connection, decoder, this, &LibWebRTCCodecs::failedDecoding);
    if (decoder.messageName() == Messages::LibWebRTCCodecs::FlushDecoderCompleted::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecs::FlushDecoderCompleted>(connection, decoder, this, &LibWebRTCCodecs::flushDecoderCompleted);
    if (decoder.messageName() == Messages::LibWebRTCCodecs::CompletedDecoding::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecs::CompletedDecoding>(connection, decoder, this, &LibWebRTCCodecs::completedDecoding);
    if (decoder.messageName() == Messages::LibWebRTCCodecs::CompletedDecodingCV::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecs::CompletedDecodingCV>(connection, decoder, this, &LibWebRTCCodecs::completedDecodingCV);
    if (decoder.messageName() == Messages::LibWebRTCCodecs::CompletedEncoding::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecs::CompletedEncoding>(connection, decoder, this, &LibWebRTCCodecs::completedEncoding);
    if (decoder.messageName() == Messages::LibWebRTCCodecs::FlushEncoderCompleted::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecs::FlushEncoderCompleted>(connection, decoder, this, &LibWebRTCCodecs::flushEncoderCompleted);
    if (decoder.messageName() == Messages::LibWebRTCCodecs::SetEncodingConfiguration::name())
        return IPC::handleMessage<Messages::LibWebRTCCodecs::SetEncodingConfiguration>(connection, decoder, this, &LibWebRTCCodecs::setEncodingConfiguration);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecs_FailedDecoding>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecs::FailedDecoding::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecs_FlushDecoderCompleted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecs::FlushDecoderCompleted::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecs_CompletedDecoding>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecs::CompletedDecoding::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecs_CompletedDecodingCV>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecs::CompletedDecodingCV::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecs_CompletedEncoding>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecs::CompletedEncoding::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecs_FlushEncoderCompleted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecs::FlushEncoderCompleted::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::LibWebRTCCodecs_SetEncodingConfiguration>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::LibWebRTCCodecs::SetEncodingConfiguration::Arguments>(globalObject, decoder);
}

}

#endif


#endif // USE(LIBWEBRTC) && PLATFORM(COCOA) && ENABLE(GPU_PROCESS)
