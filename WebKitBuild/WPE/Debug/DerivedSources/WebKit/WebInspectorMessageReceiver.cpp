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
#include "WebInspector.h"

#include "Connection.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebInspectorMessages.h" // NOLINT
#include <WebCore/FrameIdentifier.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebInspector::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::WebInspector::Show::name())
        return IPC::handleMessage<Messages::WebInspector::Show>(connection, decoder, this, &WebInspector::show);
    if (decoder.messageName() == Messages::WebInspector::Close::name())
        return IPC::handleMessage<Messages::WebInspector::Close>(connection, decoder, this, &WebInspector::close);
    if (decoder.messageName() == Messages::WebInspector::SetAttached::name())
        return IPC::handleMessage<Messages::WebInspector::SetAttached>(connection, decoder, this, &WebInspector::setAttached);
    if (decoder.messageName() == Messages::WebInspector::ShowConsole::name())
        return IPC::handleMessage<Messages::WebInspector::ShowConsole>(connection, decoder, this, &WebInspector::showConsole);
    if (decoder.messageName() == Messages::WebInspector::ShowResources::name())
        return IPC::handleMessage<Messages::WebInspector::ShowResources>(connection, decoder, this, &WebInspector::showResources);
    if (decoder.messageName() == Messages::WebInspector::ShowMainResourceForFrame::name())
        return IPC::handleMessage<Messages::WebInspector::ShowMainResourceForFrame>(connection, decoder, this, &WebInspector::showMainResourceForFrame);
    if (decoder.messageName() == Messages::WebInspector::StartPageProfiling::name())
        return IPC::handleMessage<Messages::WebInspector::StartPageProfiling>(connection, decoder, this, &WebInspector::startPageProfiling);
    if (decoder.messageName() == Messages::WebInspector::StopPageProfiling::name())
        return IPC::handleMessage<Messages::WebInspector::StopPageProfiling>(connection, decoder, this, &WebInspector::stopPageProfiling);
    if (decoder.messageName() == Messages::WebInspector::StartElementSelection::name())
        return IPC::handleMessage<Messages::WebInspector::StartElementSelection>(connection, decoder, this, &WebInspector::startElementSelection);
    if (decoder.messageName() == Messages::WebInspector::StopElementSelection::name())
        return IPC::handleMessage<Messages::WebInspector::StopElementSelection>(connection, decoder, this, &WebInspector::stopElementSelection);
    if (decoder.messageName() == Messages::WebInspector::SetFrontendConnection::name())
        return IPC::handleMessage<Messages::WebInspector::SetFrontendConnection>(connection, decoder, this, &WebInspector::setFrontendConnection);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspector_Show>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspector::Show::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspector_Close>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspector::Close::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspector_SetAttached>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspector::SetAttached::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspector_ShowConsole>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspector::ShowConsole::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspector_ShowResources>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspector::ShowResources::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspector_ShowMainResourceForFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspector::ShowMainResourceForFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspector_StartPageProfiling>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspector::StartPageProfiling::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspector_StopPageProfiling>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspector::StopPageProfiling::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspector_StartElementSelection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspector::StartElementSelection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspector_StopElementSelection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspector::StopElementSelection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebInspector_SetFrontendConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebInspector::SetFrontendConnection::Arguments>(globalObject, decoder);
}

}

#endif

