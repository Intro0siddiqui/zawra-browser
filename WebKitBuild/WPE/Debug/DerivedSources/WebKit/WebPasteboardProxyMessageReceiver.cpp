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
#include "WebPasteboardProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#if PLATFORM(COCOA)
#include "SandboxExtension.h" // NOLINT
#endif
#if (PLATFORM(COCOA) && ENABLE(IPC_TESTING_API))
#include "SharedMemory.h" // NOLINT
#endif
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebPasteboardProxyMessages.h" // NOLINT
#if PLATFORM(COCOA)
#include <WebCore/Color.h> // NOLINT
#endif
#include <WebCore/PageIdentifier.h> // NOLINT
#include <WebCore/Pasteboard.h> // NOLINT
#include <WebCore/PasteboardItemInfo.h> // NOLINT
#if PLATFORM(GTK)
#include <WebCore/SelectionData.h> // NOLINT
#endif
#include <WebCore/SharedBuffer.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/RefCounted.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebPasteboardProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
#if PLATFORM(IOS_FAMILY)
    if (decoder.messageName() == Messages::WebPasteboardProxy::WriteURLToPasteboard::name())
        return IPC::handleMessage<Messages::WebPasteboardProxy::WriteURLToPasteboard>(connection, decoder, this, &WebPasteboardProxy::writeURLToPasteboard);
    if (decoder.messageName() == Messages::WebPasteboardProxy::WriteWebContentToPasteboard::name())
        return IPC::handleMessage<Messages::WebPasteboardProxy::WriteWebContentToPasteboard>(connection, decoder, this, &WebPasteboardProxy::writeWebContentToPasteboard);
    if (decoder.messageName() == Messages::WebPasteboardProxy::WriteImageToPasteboard::name())
        return IPC::handleMessage<Messages::WebPasteboardProxy::WriteImageToPasteboard>(connection, decoder, this, &WebPasteboardProxy::writeImageToPasteboard);
    if (decoder.messageName() == Messages::WebPasteboardProxy::WriteStringToPasteboard::name())
        return IPC::handleMessage<Messages::WebPasteboardProxy::WriteStringToPasteboard>(connection, decoder, this, &WebPasteboardProxy::writeStringToPasteboard);
    if (decoder.messageName() == Messages::WebPasteboardProxy::UpdateSupportedTypeIdentifiers::name())
        return IPC::handleMessage<Messages::WebPasteboardProxy::UpdateSupportedTypeIdentifiers>(connection, decoder, this, &WebPasteboardProxy::updateSupportedTypeIdentifiers);
#endif
#if PLATFORM(GTK)
    if (decoder.messageName() == Messages::WebPasteboardProxy::WriteToClipboard::name())
        return IPC::handleMessage<Messages::WebPasteboardProxy::WriteToClipboard>(connection, decoder, this, &WebPasteboardProxy::writeToClipboard);
    if (decoder.messageName() == Messages::WebPasteboardProxy::ClearClipboard::name())
        return IPC::handleMessage<Messages::WebPasteboardProxy::ClearClipboard>(connection, decoder, this, &WebPasteboardProxy::clearClipboard);
#endif
#if USE(LIBWPE)
    if (decoder.messageName() == Messages::WebPasteboardProxy::WriteWebContentToPasteboard::name())
        return IPC::handleMessage<Messages::WebPasteboardProxy::WriteWebContentToPasteboard>(connection, decoder, this, &WebPasteboardProxy::writeWebContentToPasteboard);
    if (decoder.messageName() == Messages::WebPasteboardProxy::WriteStringToPasteboard::name())
        return IPC::handleMessage<Messages::WebPasteboardProxy::WriteStringToPasteboard>(connection, decoder, this, &WebPasteboardProxy::writeStringToPasteboard);
#endif
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool WebPasteboardProxy::didReceiveSyncMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    if (decoder.messageName() == Messages::WebPasteboardProxy::WriteCustomData::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::WriteCustomData>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::writeCustomData);
    if (decoder.messageName() == Messages::WebPasteboardProxy::TypesSafeForDOMToReadAndWrite::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::TypesSafeForDOMToReadAndWrite>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::typesSafeForDOMToReadAndWrite);
    if (decoder.messageName() == Messages::WebPasteboardProxy::AllPasteboardItemInfo::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::AllPasteboardItemInfo>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::allPasteboardItemInfo);
    if (decoder.messageName() == Messages::WebPasteboardProxy::InformationForItemAtIndex::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::InformationForItemAtIndex>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::informationForItemAtIndex);
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetPasteboardItemsCount::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetPasteboardItemsCount>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getPasteboardItemsCount);
    if (decoder.messageName() == Messages::WebPasteboardProxy::ReadStringFromPasteboard::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::ReadStringFromPasteboard>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::readStringFromPasteboard);
    if (decoder.messageName() == Messages::WebPasteboardProxy::ReadURLFromPasteboard::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::ReadURLFromPasteboard>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::readURLFromPasteboard);
    if (decoder.messageName() == Messages::WebPasteboardProxy::ReadBufferFromPasteboard::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::ReadBufferFromPasteboard>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::readBufferFromPasteboard);
    if (decoder.messageName() == Messages::WebPasteboardProxy::ContainsStringSafeForDOMToReadForType::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::ContainsStringSafeForDOMToReadForType>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::containsStringSafeForDOMToReadForType);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetNumberOfFiles::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetNumberOfFiles>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getNumberOfFiles);
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetPasteboardTypes::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetPasteboardTypes>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getPasteboardTypes);
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetPasteboardPathnamesForType::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetPasteboardPathnamesForType>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getPasteboardPathnamesForType);
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetPasteboardStringForType::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetPasteboardStringForType>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getPasteboardStringForType);
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetPasteboardStringsForType::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetPasteboardStringsForType>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getPasteboardStringsForType);
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetPasteboardBufferForType::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetPasteboardBufferForType>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getPasteboardBufferForType);
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetPasteboardChangeCount::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetPasteboardChangeCount>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getPasteboardChangeCount);
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetPasteboardColor::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetPasteboardColor>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getPasteboardColor);
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetPasteboardURL::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetPasteboardURL>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getPasteboardURL);
    if (decoder.messageName() == Messages::WebPasteboardProxy::AddPasteboardTypes::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::AddPasteboardTypes>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::addPasteboardTypes);
    if (decoder.messageName() == Messages::WebPasteboardProxy::SetPasteboardTypes::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::SetPasteboardTypes>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::setPasteboardTypes);
    if (decoder.messageName() == Messages::WebPasteboardProxy::SetPasteboardURL::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::SetPasteboardURL>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::setPasteboardURL);
    if (decoder.messageName() == Messages::WebPasteboardProxy::SetPasteboardColor::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::SetPasteboardColor>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::setPasteboardColor);
    if (decoder.messageName() == Messages::WebPasteboardProxy::SetPasteboardStringForType::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::SetPasteboardStringForType>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::setPasteboardStringForType);
    if (decoder.messageName() == Messages::WebPasteboardProxy::SetPasteboardBufferForType::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::SetPasteboardBufferForType>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::setPasteboardBufferForType);
    if (decoder.messageName() == Messages::WebPasteboardProxy::ContainsURLStringSuitableForLoading::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::ContainsURLStringSuitableForLoading>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::containsURLStringSuitableForLoading);
    if (decoder.messageName() == Messages::WebPasteboardProxy::URLStringSuitableForLoading::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::URLStringSuitableForLoading>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::urlStringSuitableForLoading);
#endif
#if (PLATFORM(COCOA) && ENABLE(IPC_TESTING_API))
    if (decoder.messageName() == Messages::WebPasteboardProxy::TestIPCSharedMemory::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::TestIPCSharedMemory>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::testIPCSharedMemory);
#endif
#if PLATFORM(GTK)
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetTypes::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetTypes>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getTypes);
    if (decoder.messageName() == Messages::WebPasteboardProxy::ReadText::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::ReadText>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::readText);
    if (decoder.messageName() == Messages::WebPasteboardProxy::ReadFilePaths::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::ReadFilePaths>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::readFilePaths);
    if (decoder.messageName() == Messages::WebPasteboardProxy::ReadBuffer::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::ReadBuffer>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::readBuffer);
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetPasteboardChangeCount::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetPasteboardChangeCount>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getPasteboardChangeCount);
#endif
#if USE(LIBWPE)
    if (decoder.messageName() == Messages::WebPasteboardProxy::GetPasteboardTypes::name())
        return IPC::handleMessageSynchronous<Messages::WebPasteboardProxy::GetPasteboardTypes>(connection, decoder, replyEncoder, this, &WebPasteboardProxy::getPasteboardTypes);
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

#if PLATFORM(IOS_FAMILY)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_WriteURLToPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::WriteURLToPasteboard::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_WriteWebContentToPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::WriteWebContentToPasteboard::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_WriteImageToPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::WriteImageToPasteboard::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_WriteStringToPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::WriteStringToPasteboard::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_UpdateSupportedTypeIdentifiers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::UpdateSupportedTypeIdentifiers::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_WriteCustomData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::WriteCustomData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_WriteCustomData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::WriteCustomData::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_TypesSafeForDOMToReadAndWrite>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::TypesSafeForDOMToReadAndWrite::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_TypesSafeForDOMToReadAndWrite>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::TypesSafeForDOMToReadAndWrite::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_AllPasteboardItemInfo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::AllPasteboardItemInfo::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_AllPasteboardItemInfo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::AllPasteboardItemInfo::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_InformationForItemAtIndex>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::InformationForItemAtIndex::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_InformationForItemAtIndex>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::InformationForItemAtIndex::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetPasteboardItemsCount>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardItemsCount::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetPasteboardItemsCount>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardItemsCount::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_ReadStringFromPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadStringFromPasteboard::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_ReadStringFromPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadStringFromPasteboard::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_ReadURLFromPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadURLFromPasteboard::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_ReadURLFromPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadURLFromPasteboard::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_ReadBufferFromPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadBufferFromPasteboard::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_ReadBufferFromPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadBufferFromPasteboard::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_ContainsStringSafeForDOMToReadForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ContainsStringSafeForDOMToReadForType::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_ContainsStringSafeForDOMToReadForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ContainsStringSafeForDOMToReadForType::ReplyArguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetNumberOfFiles>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetNumberOfFiles::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetNumberOfFiles>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetNumberOfFiles::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetPasteboardTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardTypes::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetPasteboardTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardTypes::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetPasteboardPathnamesForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardPathnamesForType::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetPasteboardPathnamesForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardPathnamesForType::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetPasteboardStringForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardStringForType::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetPasteboardStringForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardStringForType::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetPasteboardStringsForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardStringsForType::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetPasteboardStringsForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardStringsForType::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetPasteboardBufferForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardBufferForType::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetPasteboardBufferForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardBufferForType::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetPasteboardChangeCount>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardChangeCount::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetPasteboardChangeCount>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardChangeCount::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetPasteboardColor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardColor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetPasteboardColor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardColor::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetPasteboardURL>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardURL::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetPasteboardURL>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardURL::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_AddPasteboardTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::AddPasteboardTypes::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_AddPasteboardTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::AddPasteboardTypes::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_SetPasteboardTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::SetPasteboardTypes::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_SetPasteboardTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::SetPasteboardTypes::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_SetPasteboardURL>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::SetPasteboardURL::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_SetPasteboardURL>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::SetPasteboardURL::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_SetPasteboardColor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::SetPasteboardColor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_SetPasteboardColor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::SetPasteboardColor::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_SetPasteboardStringForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::SetPasteboardStringForType::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_SetPasteboardStringForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::SetPasteboardStringForType::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_SetPasteboardBufferForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::SetPasteboardBufferForType::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_SetPasteboardBufferForType>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::SetPasteboardBufferForType::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_ContainsURLStringSuitableForLoading>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ContainsURLStringSuitableForLoading::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_ContainsURLStringSuitableForLoading>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ContainsURLStringSuitableForLoading::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_URLStringSuitableForLoading>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::URLStringSuitableForLoading::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_URLStringSuitableForLoading>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::URLStringSuitableForLoading::ReplyArguments>(globalObject, decoder);
}
#endif
#if (PLATFORM(COCOA) && ENABLE(IPC_TESTING_API))
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_TestIPCSharedMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::TestIPCSharedMemory::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_TestIPCSharedMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::TestIPCSharedMemory::ReplyArguments>(globalObject, decoder);
}
#endif
#if PLATFORM(GTK)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetTypes::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetTypes::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_ReadText>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadText::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_ReadText>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadText::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_ReadFilePaths>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadFilePaths::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_ReadFilePaths>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadFilePaths::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_ReadBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadBuffer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_ReadBuffer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ReadBuffer::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_WriteToClipboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::WriteToClipboard::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_ClearClipboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::ClearClipboard::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetPasteboardChangeCount>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardChangeCount::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetPasteboardChangeCount>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardChangeCount::ReplyArguments>(globalObject, decoder);
}
#endif
#if USE(LIBWPE)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_GetPasteboardTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardTypes::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebPasteboardProxy_GetPasteboardTypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::GetPasteboardTypes::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_WriteWebContentToPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::WriteWebContentToPasteboard::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebPasteboardProxy_WriteStringToPasteboard>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebPasteboardProxy::WriteStringToPasteboard::Arguments>(globalObject, decoder);
}
#endif

}

#endif

