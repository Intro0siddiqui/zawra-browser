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
#include "RemoteWebInspectorUI.h"

#include "ArgumentCoders.h" // NOLINT
#include "DebuggableInfoData.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "RemoteWebInspectorUIMessages.h" // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void RemoteWebInspectorUI::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::RemoteWebInspectorUI::Initialize::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUI::Initialize>(connection, decoder, this, &RemoteWebInspectorUI::initialize);
    if (decoder.messageName() == Messages::RemoteWebInspectorUI::UpdateFindString::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUI::UpdateFindString>(connection, decoder, this, &RemoteWebInspectorUI::updateFindString);
#if ENABLE(INSPECTOR_TELEMETRY)
    if (decoder.messageName() == Messages::RemoteWebInspectorUI::SetDiagnosticLoggingAvailable::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUI::SetDiagnosticLoggingAvailable>(connection, decoder, this, &RemoteWebInspectorUI::setDiagnosticLoggingAvailable);
#endif
    if (decoder.messageName() == Messages::RemoteWebInspectorUI::ShowConsole::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUI::ShowConsole>(connection, decoder, this, &RemoteWebInspectorUI::showConsole);
    if (decoder.messageName() == Messages::RemoteWebInspectorUI::ShowResources::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUI::ShowResources>(connection, decoder, this, &RemoteWebInspectorUI::showResources);
    if (decoder.messageName() == Messages::RemoteWebInspectorUI::SendMessageToFrontend::name())
        return IPC::handleMessage<Messages::RemoteWebInspectorUI::SendMessageToFrontend>(connection, decoder, this, &RemoteWebInspectorUI::sendMessageToFrontend);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUI_Initialize>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUI::Initialize::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUI_UpdateFindString>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUI::UpdateFindString::Arguments>(globalObject, decoder);
}
#if ENABLE(INSPECTOR_TELEMETRY)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUI_SetDiagnosticLoggingAvailable>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUI::SetDiagnosticLoggingAvailable::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUI_ShowConsole>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUI::ShowConsole::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUI_ShowResources>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUI::ShowResources::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::RemoteWebInspectorUI_SendMessageToFrontend>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::RemoteWebInspectorUI::SendMessageToFrontend::Arguments>(globalObject, decoder);
}

}

#endif

