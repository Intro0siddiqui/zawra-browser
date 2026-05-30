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
#include "WebInspectorUI.h"

#include "ArgumentCoders.h" // NOLINT
#include "DebuggableInfoData.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "WebInspectorUIMessages.h" // NOLINT
#include "WebPageProxyIdentifier.h" // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebInspectorUI::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::WebInspectorUI::EstablishConnection::name())
        return IPC::handleMessage<Messages::WebInspectorUI::EstablishConnection>(connection, decoder, this, &WebInspectorUI::establishConnection);
    if (decoder.messageName() == Messages::WebInspectorUI::UpdateConnection::name())
        return IPC::handleMessage<Messages::WebInspectorUI::UpdateConnection>(connection, decoder, this, &WebInspectorUI::updateConnection);
    if (decoder.messageName() == Messages::WebInspectorUI::AttachedBottom::name())
        return IPC::handleMessage<Messages::WebInspectorUI::AttachedBottom>(connection, decoder, this, &WebInspectorUI::attachedBottom);
    if (decoder.messageName() == Messages::WebInspectorUI::AttachedRight::name())
        return IPC::handleMessage<Messages::WebInspectorUI::AttachedRight>(connection, decoder, this, &WebInspectorUI::attachedRight);
    if (decoder.messageName() == Messages::WebInspectorUI::AttachedLeft::name())
        return IPC::handleMessage<Messages::WebInspectorUI::AttachedLeft>(connection, decoder, this, &WebInspectorUI::attachedLeft);
    if (decoder.messageName() == Messages::WebInspectorUI::Detached::name())
        return IPC::handleMessage<Messages::WebInspectorUI::Detached>(connection, decoder, this, &WebInspectorUI::detached);
    if (decoder.messageName() == Messages::WebInspectorUI::SetDockingUnavailable::name())
        return IPC::handleMessage<Messages::WebInspectorUI::SetDockingUnavailable>(connection, decoder, this, &WebInspectorUI::setDockingUnavailable);
    if (decoder.messageName() == Messages::WebInspectorUI::SetIsVisible::name())
        return IPC::handleMessage<Messages::WebInspectorUI::SetIsVisible>(connection, decoder, this, &WebInspectorUI::setIsVisible);
    if (decoder.messageName() == Messages::WebInspectorUI::UpdateFindString::name())
        return IPC::handleMessage<Messages::WebInspectorUI::UpdateFindString>(connection, decoder, this, &WebInspectorUI::updateFindString);
#if ENABLE(INSPECTOR_TELEMETRY)
    if (decoder.messageName() == Messages::WebInspectorUI::SetDiagnosticLoggingAvailable::name())
        return IPC::handleMessage<Messages::WebInspectorUI::SetDiagnosticLoggingAvailable>(connection, decoder, this, &WebInspectorUI::setDiagnosticLoggingAvailable);
#endif
    if (decoder.messageName() == Messages::WebInspectorUI::ShowConsole::name())
        return IPC::handleMessage<Messages::WebInspectorUI::ShowConsole>(connection, decoder, this, &WebInspectorUI::showConsole);
    if (decoder.messageName() == Messages::WebInspectorUI::ShowResources::name())
        return IPC::handleMessage<Messages::WebInspectorUI::ShowResources>(connection, decoder, this, &WebInspectorUI::showResources);
    if (decoder.messageName() == Messages::WebInspectorUI::ShowMainResourceForFrame::name())
        return IPC::handleMessage<Messages::WebInspectorUI::ShowMainResourceForFrame>(connection, decoder, this, &WebInspectorUI::showMainResourceForFrame);
    if (decoder.messageName() == Messages::WebInspectorUI::StartPageProfiling::name())
        return IPC::handleMessage<Messages::WebInspectorUI::StartPageProfiling>(connection, decoder, this, &WebInspectorUI::startPageProfiling);
    if (decoder.messageName() == Messages::WebInspectorUI::StopPageProfiling::name())
        return IPC::handleMessage<Messages::WebInspectorUI::StopPageProfiling>(connection, decoder, this, &WebInspectorUI::stopPageProfiling);
    if (decoder.messageName() == Messages::WebInspectorUI::StartElementSelection::name())
        return IPC::handleMessage<Messages::WebInspectorUI::StartElementSelection>(connection, decoder, this, &WebInspectorUI::startElementSelection);
    if (decoder.messageName() == Messages::WebInspectorUI::StopElementSelection::name())
        return IPC::handleMessage<Messages::WebInspectorUI::StopElementSelection>(connection, decoder, this, &WebInspectorUI::stopElementSelection);
    if (decoder.messageName() == Messages::WebInspectorUI::SendMessageToFrontend::name())
        return IPC::handleMessage<Messages::WebInspectorUI::SendMessageToFrontend>(connection, decoder, this, &WebInspectorUI::sendMessageToFrontend);
    if (decoder.messageName() == Messages::WebInspectorUI::EvaluateInFrontendForTesting::name())
        return IPC::handleMessage<Messages::WebInspectorUI::EvaluateInFrontendForTesting>(connection, decoder, this, &WebInspectorUI::evaluateInFrontendForTesting);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_EstablishConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::EstablishConnection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_UpdateConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::UpdateConnection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_AttachedBottom>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::AttachedBottom::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_AttachedRight>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::AttachedRight::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_AttachedLeft>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::AttachedLeft::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_Detached>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::Detached::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_SetDockingUnavailable>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::SetDockingUnavailable::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_SetIsVisible>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::SetIsVisible::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_UpdateFindString>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::UpdateFindString::Arguments>(globalObject, decoder);
}
#if ENABLE(INSPECTOR_TELEMETRY)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_SetDiagnosticLoggingAvailable>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::SetDiagnosticLoggingAvailable::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_ShowConsole>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::ShowConsole::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_ShowResources>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::ShowResources::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_ShowMainResourceForFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::ShowMainResourceForFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_StartPageProfiling>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::StartPageProfiling::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_StopPageProfiling>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::StopPageProfiling::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_StartElementSelection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::StartElementSelection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_StopElementSelection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::StopElementSelection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_SendMessageToFrontend>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::SendMessageToFrontend::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspectorUI_EvaluateInFrontendForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspectorUI::EvaluateInFrontendForTesting::Arguments>(globalObject, decoder);
}

}

#endif

