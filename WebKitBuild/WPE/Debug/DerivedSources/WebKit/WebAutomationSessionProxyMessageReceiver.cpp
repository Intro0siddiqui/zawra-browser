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
#include "WebAutomationSessionProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "CoordinateSystem.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "WebAutomationSessionProxyMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/Cookie.h> // NOLINT
#include <WebCore/FloatRect.h> // NOLINT
#include <WebCore/FrameIdentifier.h> // NOLINT
#include <WebCore/IntPoint.h> // NOLINT
#include <WebCore/IntRect.h> // NOLINT
#include <WebCore/PageIdentifier.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebAutomationSessionProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::EvaluateJavaScriptFunction::name())
        return IPC::handleMessage<Messages::WebAutomationSessionProxy::EvaluateJavaScriptFunction>(connection, decoder, this, &WebAutomationSessionProxy::evaluateJavaScriptFunction);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::ResolveChildFrameWithOrdinal::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::ResolveChildFrameWithOrdinal>(connection, decoder, this, &WebAutomationSessionProxy::resolveChildFrameWithOrdinal);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::ResolveChildFrameWithNodeHandle::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::ResolveChildFrameWithNodeHandle>(connection, decoder, this, &WebAutomationSessionProxy::resolveChildFrameWithNodeHandle);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::ResolveChildFrameWithName::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::ResolveChildFrameWithName>(connection, decoder, this, &WebAutomationSessionProxy::resolveChildFrameWithName);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::ResolveParentFrame::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::ResolveParentFrame>(connection, decoder, this, &WebAutomationSessionProxy::resolveParentFrame);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::ComputeElementLayout::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::ComputeElementLayout>(connection, decoder, this, &WebAutomationSessionProxy::computeElementLayout);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::GetComputedRole::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::GetComputedRole>(connection, decoder, this, &WebAutomationSessionProxy::getComputedRole);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::GetComputedLabel::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::GetComputedLabel>(connection, decoder, this, &WebAutomationSessionProxy::getComputedLabel);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::SelectOptionElement::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::SelectOptionElement>(connection, decoder, this, &WebAutomationSessionProxy::selectOptionElement);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::SetFilesForInputFileUpload::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::SetFilesForInputFileUpload>(connection, decoder, this, &WebAutomationSessionProxy::setFilesForInputFileUpload);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::TakeScreenshot::name())
        return IPC::handleMessage<Messages::WebAutomationSessionProxy::TakeScreenshot>(connection, decoder, this, &WebAutomationSessionProxy::takeScreenshot);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::SnapshotRectForScreenshot::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::SnapshotRectForScreenshot>(connection, decoder, this, &WebAutomationSessionProxy::snapshotRectForScreenshot);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::GetCookiesForFrame::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::GetCookiesForFrame>(connection, decoder, this, &WebAutomationSessionProxy::getCookiesForFrame);
    if (decoder.messageName() == Messages::WebAutomationSessionProxy::DeleteCookie::name())
        return IPC::handleMessageAsync<Messages::WebAutomationSessionProxy::DeleteCookie>(connection, decoder, this, &WebAutomationSessionProxy::deleteCookie);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_EvaluateJavaScriptFunction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::EvaluateJavaScriptFunction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_ResolveChildFrameWithOrdinal>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::ResolveChildFrameWithOrdinal::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_ResolveChildFrameWithOrdinal>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::ResolveChildFrameWithOrdinal::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_ResolveChildFrameWithNodeHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::ResolveChildFrameWithNodeHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_ResolveChildFrameWithNodeHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::ResolveChildFrameWithNodeHandle::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_ResolveChildFrameWithName>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::ResolveChildFrameWithName::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_ResolveChildFrameWithName>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::ResolveChildFrameWithName::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_ResolveParentFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::ResolveParentFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_ResolveParentFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::ResolveParentFrame::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_ComputeElementLayout>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::ComputeElementLayout::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_ComputeElementLayout>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::ComputeElementLayout::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_GetComputedRole>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::GetComputedRole::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_GetComputedRole>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::GetComputedRole::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_GetComputedLabel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::GetComputedLabel::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_GetComputedLabel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::GetComputedLabel::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_SelectOptionElement>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::SelectOptionElement::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_SelectOptionElement>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::SelectOptionElement::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_SetFilesForInputFileUpload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::SetFilesForInputFileUpload::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_SetFilesForInputFileUpload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::SetFilesForInputFileUpload::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_TakeScreenshot>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::TakeScreenshot::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_SnapshotRectForScreenshot>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::SnapshotRectForScreenshot::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_SnapshotRectForScreenshot>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::SnapshotRectForScreenshot::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_GetCookiesForFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::GetCookiesForFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_GetCookiesForFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::GetCookiesForFrame::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebAutomationSessionProxy_DeleteCookie>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::DeleteCookie::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebAutomationSessionProxy_DeleteCookie>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebAutomationSessionProxy::DeleteCookie::ReplyArguments>(globalObject, decoder);
}

}

#endif

