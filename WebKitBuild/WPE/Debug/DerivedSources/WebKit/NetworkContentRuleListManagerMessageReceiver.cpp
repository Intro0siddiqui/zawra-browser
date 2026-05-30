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
#if ENABLE(CONTENT_EXTENSIONS)
#include "NetworkContentRuleListManager.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "NetworkContentRuleListManagerMessages.h" // NOLINT
#include "UserContentControllerIdentifier.h" // NOLINT
#include "WebCompiledContentRuleListData.h" // NOLINT
#include <utility> // NOLINT
#include <wtf/URLHash.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void NetworkContentRuleListManager::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::NetworkContentRuleListManager::Remove::name())
        return IPC::handleMessage<Messages::NetworkContentRuleListManager::Remove>(connection, decoder, this, &NetworkContentRuleListManager::remove);
    if (decoder.messageName() == Messages::NetworkContentRuleListManager::AddContentRuleLists::name())
        return IPC::handleMessage<Messages::NetworkContentRuleListManager::AddContentRuleLists>(connection, decoder, this, &NetworkContentRuleListManager::addContentRuleLists);
    if (decoder.messageName() == Messages::NetworkContentRuleListManager::RemoveContentRuleList::name())
        return IPC::handleMessage<Messages::NetworkContentRuleListManager::RemoveContentRuleList>(connection, decoder, this, &NetworkContentRuleListManager::removeContentRuleList);
    if (decoder.messageName() == Messages::NetworkContentRuleListManager::RemoveAllContentRuleLists::name())
        return IPC::handleMessage<Messages::NetworkContentRuleListManager::RemoveAllContentRuleLists>(connection, decoder, this, &NetworkContentRuleListManager::removeAllContentRuleLists);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkContentRuleListManager_Remove>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkContentRuleListManager::Remove::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkContentRuleListManager_AddContentRuleLists>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkContentRuleListManager::AddContentRuleLists::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkContentRuleListManager_RemoveContentRuleList>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkContentRuleListManager::RemoveContentRuleList::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkContentRuleListManager_RemoveAllContentRuleLists>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkContentRuleListManager::RemoveAllContentRuleLists::Arguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(CONTENT_EXTENSIONS)
