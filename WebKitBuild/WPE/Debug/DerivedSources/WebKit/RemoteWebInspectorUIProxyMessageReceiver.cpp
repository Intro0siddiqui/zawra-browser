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
#include "RemoteWebInspectorUIProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteWebInspectorUIProxyMessages.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/CertificateInfo.h> // NOLINT
#include <WebCore/Color.h> // NOLINT
#include <WebCore/FloatRect.h> // NOLINT
#include <WebCore/InspectorFrontendClient.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteWebInspectorUIProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::FrontendLoaded::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::FrontendLoaded>(connection, decoder, this, &RemoteWebInspectorUIProxy::frontendLoaded);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::FrontendDidClose::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::FrontendDidClose>(connection, decoder, this, &RemoteWebInspectorUIProxy::frontendDidClose);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::Reopen::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::Reopen>(connection, decoder, this, &RemoteWebInspectorUIProxy::reopen);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::ResetState::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::ResetState>(connection, decoder, this, &RemoteWebInspectorUIProxy::resetState);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::BringToFront::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::BringToFront>(connection, decoder, this, &RemoteWebInspectorUIProxy::bringToFront);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::Save::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::Save>(connection, decoder, this, &RemoteWebInspectorUIProxy::save);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::Load::name())
        return IPC::handleMessageAsync<Messages::RemoteWebInspectorUIProxy::Load>(connection, decoder, this, &RemoteWebInspectorUIProxy::load);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::PickColorFromScreen::name())
        return IPC::handleMessageAsync<Messages::RemoteWebInspectorUIProxy::PickColorFromScreen>(connection, decoder, this, &RemoteWebInspectorUIProxy::pickColorFromScreen);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::SetForcedAppearance::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::SetForcedAppearance>(connection, decoder, this, &RemoteWebInspectorUIProxy::setForcedAppearance);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::SetSheetRect::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::SetSheetRect>(connection, decoder, this, &RemoteWebInspectorUIProxy::setSheetRect);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::StartWindowDrag::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::StartWindowDrag>(connection, decoder, this, &RemoteWebInspectorUIProxy::startWindowDrag);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::OpenURLExternally::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::OpenURLExternally>(connection, decoder, this, &RemoteWebInspectorUIProxy::openURLExternally);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::RevealFileExternally::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::RevealFileExternally>(connection, decoder, this, &RemoteWebInspectorUIProxy::revealFileExternally);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::ShowCertificate::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::ShowCertificate>(connection, decoder, this, &RemoteWebInspectorUIProxy::showCertificate);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::SendMessageToBackend::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::SendMessageToBackend>(connection, decoder, this, &RemoteWebInspectorUIProxy::sendMessageToBackend);
    if (decoder.messageName() == Messages::RemoteWebInspectorUIProxy::SetInspectorPageDeveloperExtrasEnabled::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUIProxy::SetInspectorPageDeveloperExtrasEnabled>(connection, decoder, this, &RemoteWebInspectorUIProxy::setInspectorPageDeveloperExtrasEnabled);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_FrontendLoaded>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::FrontendLoaded::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_FrontendDidClose>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::FrontendDidClose::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_Reopen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::Reopen::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_ResetState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::ResetState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_BringToFront>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::BringToFront::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_Save>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::Save::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_Load>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::Load::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteWebInspectorUIProxy_Load>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::Load::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_PickColorFromScreen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::PickColorFromScreen::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::RemoteWebInspectorUIProxy_PickColorFromScreen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::PickColorFromScreen::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_SetForcedAppearance>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::SetForcedAppearance::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_SetSheetRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::SetSheetRect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_StartWindowDrag>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::StartWindowDrag::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_OpenURLExternally>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::OpenURLExternally::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_RevealFileExternally>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::RevealFileExternally::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_ShowCertificate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::ShowCertificate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_SendMessageToBackend>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::SendMessageToBackend::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUIProxy_SetInspectorPageDeveloperExtrasEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUIProxy::SetInspectorPageDeveloperExtrasEnabled::Arguments>(globalObject, decoder);
}

}

#endif

