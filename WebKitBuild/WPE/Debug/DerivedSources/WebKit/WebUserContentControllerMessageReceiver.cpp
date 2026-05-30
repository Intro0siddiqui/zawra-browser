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
#include "WebUserContentController.h"

#include "ArgumentCoders.h" // NOLINT
#include "ContentWorldShared.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "InjectUserScriptImmediately.h" // NOLINT
#if ENABLE(CONTENT_EXTENSIONS)
#include "WebCompiledContentRuleListData.h" // NOLINT
#endif
#include "WebUserContentControllerDataTypes.h" // NOLINT
#include "WebUserContentControllerMessages.h" // NOLINT
#include <utility> // NOLINT
#if ENABLE(CONTENT_EXTENSIONS)
#include <wtf/URLHash.h> // NOLINT
#endif
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebUserContentController::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::WebUserContentController::AddContentWorlds::name())
        return IPC::handleMessage<Messages::WebUserContentController::AddContentWorlds>(connection, decoder, this, &WebUserContentController::addContentWorlds);
    if (decoder.messageName() == Messages::WebUserContentController::RemoveContentWorlds::name())
        return IPC::handleMessage<Messages::WebUserContentController::RemoveContentWorlds>(connection, decoder, this, &WebUserContentController::removeContentWorlds);
    if (decoder.messageName() == Messages::WebUserContentController::AddUserScripts::name())
        return IPC::handleMessage<Messages::WebUserContentController::AddUserScripts>(connection, decoder, this, &WebUserContentController::addUserScripts);
    if (decoder.messageName() == Messages::WebUserContentController::RemoveUserScript::name())
        return IPC::handleMessage<Messages::WebUserContentController::RemoveUserScript>(connection, decoder, this, &WebUserContentController::removeUserScript);
    if (decoder.messageName() == Messages::WebUserContentController::RemoveAllUserScripts::name())
        return IPC::handleMessage<Messages::WebUserContentController::RemoveAllUserScripts>(connection, decoder, this, &WebUserContentController::removeAllUserScripts);
    if (decoder.messageName() == Messages::WebUserContentController::AddUserStyleSheets::name())
        return IPC::handleMessage<Messages::WebUserContentController::AddUserStyleSheets>(connection, decoder, this, &WebUserContentController::addUserStyleSheets);
    if (decoder.messageName() == Messages::WebUserContentController::RemoveUserStyleSheet::name())
        return IPC::handleMessage<Messages::WebUserContentController::RemoveUserStyleSheet>(connection, decoder, this, &WebUserContentController::removeUserStyleSheet);
    if (decoder.messageName() == Messages::WebUserContentController::RemoveAllUserStyleSheets::name())
        return IPC::handleMessage<Messages::WebUserContentController::RemoveAllUserStyleSheets>(connection, decoder, this, &WebUserContentController::removeAllUserStyleSheets);
    if (decoder.messageName() == Messages::WebUserContentController::AddUserScriptMessageHandlers::name())
        return IPC::handleMessage<Messages::WebUserContentController::AddUserScriptMessageHandlers>(connection, decoder, this, &WebUserContentController::addUserScriptMessageHandlers);
    if (decoder.messageName() == Messages::WebUserContentController::RemoveUserScriptMessageHandler::name())
        return IPC::handleMessage<Messages::WebUserContentController::RemoveUserScriptMessageHandler>(connection, decoder, this, &WebUserContentController::removeUserScriptMessageHandler);
    if (decoder.messageName() == Messages::WebUserContentController::RemoveAllUserScriptMessageHandlersForWorlds::name())
        return IPC::handleMessage<Messages::WebUserContentController::RemoveAllUserScriptMessageHandlersForWorlds>(connection, decoder, this, &WebUserContentController::removeAllUserScriptMessageHandlersForWorlds);
    if (decoder.messageName() == Messages::WebUserContentController::RemoveAllUserScriptMessageHandlers::name())
        return IPC::handleMessage<Messages::WebUserContentController::RemoveAllUserScriptMessageHandlers>(connection, decoder, this, &WebUserContentController::removeAllUserScriptMessageHandlers);
#if ENABLE(CONTENT_EXTENSIONS)
    if (decoder.messageName() == Messages::WebUserContentController::AddContentRuleLists::name())
        return IPC::handleMessage<Messages::WebUserContentController::AddContentRuleLists>(connection, decoder, this, &WebUserContentController::addContentRuleLists);
    if (decoder.messageName() == Messages::WebUserContentController::RemoveContentRuleList::name())
        return IPC::handleMessage<Messages::WebUserContentController::RemoveContentRuleList>(connection, decoder, this, &WebUserContentController::removeContentRuleList);
    if (decoder.messageName() == Messages::WebUserContentController::RemoveAllContentRuleLists::name())
        return IPC::handleMessage<Messages::WebUserContentController::RemoveAllContentRuleLists>(connection, decoder, this, &WebUserContentController::removeAllContentRuleLists);
#endif
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_AddContentWorlds>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::AddContentWorlds::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_RemoveContentWorlds>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::RemoveContentWorlds::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_AddUserScripts>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::AddUserScripts::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_RemoveUserScript>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::RemoveUserScript::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_RemoveAllUserScripts>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::RemoveAllUserScripts::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_AddUserStyleSheets>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::AddUserStyleSheets::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_RemoveUserStyleSheet>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::RemoveUserStyleSheet::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_RemoveAllUserStyleSheets>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::RemoveAllUserStyleSheets::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_AddUserScriptMessageHandlers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::AddUserScriptMessageHandlers::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_RemoveUserScriptMessageHandler>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::RemoveUserScriptMessageHandler::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_RemoveAllUserScriptMessageHandlersForWorlds>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::RemoveAllUserScriptMessageHandlersForWorlds::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_RemoveAllUserScriptMessageHandlers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::RemoveAllUserScriptMessageHandlers::Arguments>(globalObject, decoder);
}
#if ENABLE(CONTENT_EXTENSIONS)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_AddContentRuleLists>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::AddContentRuleLists::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_RemoveContentRuleList>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::RemoveContentRuleList::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebUserContentController_RemoveAllContentRuleLists>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebUserContentController::RemoveAllContentRuleLists::Arguments>(globalObject, decoder);
}
#endif

}

#endif

