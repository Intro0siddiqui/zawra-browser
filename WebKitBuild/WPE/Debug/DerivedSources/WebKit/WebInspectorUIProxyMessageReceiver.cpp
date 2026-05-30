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
#include "WebInspectorUIProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "Connection.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebInspectorUIProxyMessages.h" // NOLINT
#include <WebCore/CertificateInfo.h> // NOLINT
#include <WebCore/Color.h> // NOLINT
#include <WebCore/FloatRect.h> // NOLINT
#include <WebCore/InspectorClient.h> // NOLINT
#include <WebCore/InspectorFrontendClient.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebInspectorUIProxy::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::WebInspectorUIProxy::OpenLocalInspectorFrontend::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::OpenLocalInspectorFrontend>(connection, decoder, this, &WebInspectorUIProxy::openLocalInspectorFrontend);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::SetFrontendConnection::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::SetFrontendConnection>(connection, decoder, this, &WebInspectorUIProxy::setFrontendConnection);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::SendMessageToBackend::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::SendMessageToBackend>(connection, decoder, this, &WebInspectorUIProxy::sendMessageToBackend);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::FrontendLoaded::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::FrontendLoaded>(connection, decoder, this, &WebInspectorUIProxy::frontendLoaded);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::DidClose::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::DidClose>(connection, decoder, this, &WebInspectorUIProxy::didClose);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::BringToFront::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::BringToFront>(connection, decoder, this, &WebInspectorUIProxy::bringToFront);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::Reopen::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::Reopen>(connection, decoder, this, &WebInspectorUIProxy::reopen);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::ResetState::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::ResetState>(connection, decoder, this, &WebInspectorUIProxy::resetState);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::SetForcedAppearance::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::SetForcedAppearance>(connection, decoder, this, &WebInspectorUIProxy::setForcedAppearance);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::OpenURLExternally::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::OpenURLExternally>(connection, decoder, this, &WebInspectorUIProxy::openURLExternally);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::RevealFileExternally::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::RevealFileExternally>(connection, decoder, this, &WebInspectorUIProxy::revealFileExternally);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::InspectedURLChanged::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::InspectedURLChanged>(connection, decoder, this, &WebInspectorUIProxy::inspectedURLChanged);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::ShowCertificate::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::ShowCertificate>(connection, decoder, this, &WebInspectorUIProxy::showCertificate);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::ElementSelectionChanged::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::ElementSelectionChanged>(connection, decoder, this, &WebInspectorUIProxy::elementSelectionChanged);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::TimelineRecordingChanged::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::TimelineRecordingChanged>(connection, decoder, this, &WebInspectorUIProxy::timelineRecordingChanged);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::SetDeveloperPreferenceOverride::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::SetDeveloperPreferenceOverride>(connection, decoder, this, &WebInspectorUIProxy::setDeveloperPreferenceOverride);
#if ENABLE(INSPECTOR_NETWORK_THROTTLING)
    if (decoder.messageName() == Messages::WebInspectorUIProxy::SetEmulatedConditions::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::SetEmulatedConditions>(connection, decoder, this, &WebInspectorUIProxy::setEmulatedConditions);
#endif
    if (decoder.messageName() == Messages::WebInspectorUIProxy::Save::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::Save>(connection, decoder, this, &WebInspectorUIProxy::save);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::Load::name())
        return IPC::handleMessageAsync<Messages::WebInspectorUIProxy::Load>(connection, decoder, this, &WebInspectorUIProxy::load);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::PickColorFromScreen::name())
        return IPC::handleMessageAsync<Messages::WebInspectorUIProxy::PickColorFromScreen>(connection, decoder, this, &WebInspectorUIProxy::pickColorFromScreen);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::AttachBottom::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::AttachBottom>(connection, decoder, this, &WebInspectorUIProxy::attachBottom);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::AttachRight::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::AttachRight>(connection, decoder, this, &WebInspectorUIProxy::attachRight);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::AttachLeft::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::AttachLeft>(connection, decoder, this, &WebInspectorUIProxy::attachLeft);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::Detach::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::Detach>(connection, decoder, this, &WebInspectorUIProxy::detach);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::AttachAvailabilityChanged::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::AttachAvailabilityChanged>(connection, decoder, this, &WebInspectorUIProxy::attachAvailabilityChanged);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::SetAttachedWindowHeight::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::SetAttachedWindowHeight>(connection, decoder, this, &WebInspectorUIProxy::setAttachedWindowHeight);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::SetAttachedWindowWidth::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::SetAttachedWindowWidth>(connection, decoder, this, &WebInspectorUIProxy::setAttachedWindowWidth);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::SetSheetRect::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::SetSheetRect>(connection, decoder, this, &WebInspectorUIProxy::setSheetRect);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::StartWindowDrag::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::StartWindowDrag>(connection, decoder, this, &WebInspectorUIProxy::startWindowDrag);
    if (decoder.messageName() == Messages::WebInspectorUIProxy::SetInspectorPageDeveloperExtrasEnabled::name())
        return IPC::handleMessage<Messages::WebInspectorUIProxy::SetInspectorPageDeveloperExtrasEnabled>(connection, decoder, this, &WebInspectorUIProxy::setInspectorPageDeveloperExtrasEnabled);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_OpenLocalInspectorFrontend>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::OpenLocalInspectorFrontend::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_SetFrontendConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::SetFrontendConnection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_SendMessageToBackend>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::SendMessageToBackend::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_FrontendLoaded>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::FrontendLoaded::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_DidClose>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::DidClose::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_BringToFront>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::BringToFront::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_Reopen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::Reopen::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_ResetState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::ResetState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_SetForcedAppearance>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::SetForcedAppearance::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_OpenURLExternally>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::OpenURLExternally::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_RevealFileExternally>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::RevealFileExternally::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_InspectedURLChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::InspectedURLChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_ShowCertificate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::ShowCertificate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_ElementSelectionChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::ElementSelectionChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_TimelineRecordingChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::TimelineRecordingChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_SetDeveloperPreferenceOverride>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::SetDeveloperPreferenceOverride::Arguments>(globalObject, decoder);
}
#if ENABLE(INSPECTOR_NETWORK_THROTTLING)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_SetEmulatedConditions>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::SetEmulatedConditions::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_Save>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::Save::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_Load>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::Load::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebInspectorUIProxy_Load>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::Load::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_PickColorFromScreen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::PickColorFromScreen::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebInspectorUIProxy_PickColorFromScreen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::PickColorFromScreen::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_AttachBottom>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::AttachBottom::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_AttachRight>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::AttachRight::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_AttachLeft>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::AttachLeft::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_Detach>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::Detach::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_AttachAvailabilityChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::AttachAvailabilityChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_SetAttachedWindowHeight>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::SetAttachedWindowHeight::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_SetAttachedWindowWidth>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::SetAttachedWindowWidth::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_SetSheetRect>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::SetSheetRect::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_StartWindowDrag>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::StartWindowDrag::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUIProxy_SetInspectorPageDeveloperExtrasEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUIProxy::SetInspectorPageDeveloperExtrasEnabled::Arguments>(globalObject, decoder);
}

}

#endif

