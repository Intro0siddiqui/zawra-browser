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
#include "CacheStorageEngineConnection.h"

#include "ArgumentCoders.h" // NOLINT
#include "CacheStorageEngineConnectionMessages.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include <WebCore/CacheQueryOptions.h> // NOLINT
#include <WebCore/ClientOrigin.h> // NOLINT
#include <WebCore/DOMCacheEngine.h> // NOLINT
#include <WebCore/DOMCacheIdentifier.h> // NOLINT
#include <WebCore/ResourceRequest.h> // NOLINT
#include <WebCore/RetrieveRecordsOptions.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void CacheStorageEngineConnection::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::CacheStorageEngineConnection::Reference::name())
        return IPC::handleMessage<Messages::CacheStorageEngineConnection::Reference>(connection, decoder, this, &CacheStorageEngineConnection::reference);
    if (decoder.messageName() == Messages::CacheStorageEngineConnection::Dereference::name())
        return IPC::handleMessage<Messages::CacheStorageEngineConnection::Dereference>(connection, decoder, this, &CacheStorageEngineConnection::dereference);
    if (decoder.messageName() == Messages::CacheStorageEngineConnection::Open::name())
        return IPC::handleMessageAsync<Messages::CacheStorageEngineConnection::Open>(connection, decoder, this, &CacheStorageEngineConnection::open);
    if (decoder.messageName() == Messages::CacheStorageEngineConnection::Remove::name())
        return IPC::handleMessageAsync<Messages::CacheStorageEngineConnection::Remove>(connection, decoder, this, &CacheStorageEngineConnection::remove);
    if (decoder.messageName() == Messages::CacheStorageEngineConnection::Caches::name())
        return IPC::handleMessageAsync<Messages::CacheStorageEngineConnection::Caches>(connection, decoder, this, &CacheStorageEngineConnection::caches);
    if (decoder.messageName() == Messages::CacheStorageEngineConnection::RetrieveRecords::name())
        return IPC::handleMessageAsync<Messages::CacheStorageEngineConnection::RetrieveRecords>(connection, decoder, this, &CacheStorageEngineConnection::retrieveRecords);
    if (decoder.messageName() == Messages::CacheStorageEngineConnection::DeleteMatchingRecords::name())
        return IPC::handleMessageAsync<Messages::CacheStorageEngineConnection::DeleteMatchingRecords>(connection, decoder, this, &CacheStorageEngineConnection::deleteMatchingRecords);
    if (decoder.messageName() == Messages::CacheStorageEngineConnection::PutRecords::name())
        return IPC::handleMessageAsync<Messages::CacheStorageEngineConnection::PutRecords>(connection, decoder, this, &CacheStorageEngineConnection::putRecords);
    if (decoder.messageName() == Messages::CacheStorageEngineConnection::ClearMemoryRepresentation::name())
        return IPC::handleMessageAsync<Messages::CacheStorageEngineConnection::ClearMemoryRepresentation>(connection, decoder, this, &CacheStorageEngineConnection::clearMemoryRepresentation);
    if (decoder.messageName() == Messages::CacheStorageEngineConnection::EngineRepresentation::name())
        return IPC::handleMessageAsync<Messages::CacheStorageEngineConnection::EngineRepresentation>(connection, decoder, this, &CacheStorageEngineConnection::engineRepresentation);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::CacheStorageEngineConnection_Reference>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::Reference::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::CacheStorageEngineConnection_Dereference>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::Dereference::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::CacheStorageEngineConnection_Open>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::Open::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::CacheStorageEngineConnection_Open>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::Open::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::CacheStorageEngineConnection_Remove>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::Remove::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::CacheStorageEngineConnection_Remove>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::Remove::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::CacheStorageEngineConnection_Caches>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::Caches::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::CacheStorageEngineConnection_Caches>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::Caches::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::CacheStorageEngineConnection_RetrieveRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::RetrieveRecords::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::CacheStorageEngineConnection_RetrieveRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::RetrieveRecords::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::CacheStorageEngineConnection_DeleteMatchingRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::DeleteMatchingRecords::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::CacheStorageEngineConnection_DeleteMatchingRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::DeleteMatchingRecords::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::CacheStorageEngineConnection_PutRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::PutRecords::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::CacheStorageEngineConnection_PutRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::PutRecords::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::CacheStorageEngineConnection_ClearMemoryRepresentation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::ClearMemoryRepresentation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::CacheStorageEngineConnection_ClearMemoryRepresentation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::ClearMemoryRepresentation::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::CacheStorageEngineConnection_EngineRepresentation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::EngineRepresentation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::CacheStorageEngineConnection_EngineRepresentation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::CacheStorageEngineConnection::EngineRepresentation::ReplyArguments>(globalObject, decoder);
}

}

#endif

