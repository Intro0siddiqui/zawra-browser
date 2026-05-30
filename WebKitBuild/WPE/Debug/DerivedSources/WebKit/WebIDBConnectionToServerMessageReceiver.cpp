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
#include "WebIDBConnectionToServer.h"

#include "ArgumentCoders.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebIDBConnectionToServerMessages.h" // NOLINT
#include "WebIDBResult.h" // NOLINT
#include <WebCore/IDBDatabaseNameAndVersion.h> // NOLINT
#include <WebCore/IDBError.h> // NOLINT
#include <WebCore/IDBResourceIdentifier.h> // NOLINT
#include <WebCore/IDBResultData.h> // NOLINT
#include <wtf/Vector.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebIDBConnectionToServer::didReceiveMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidDeleteDatabase::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidDeleteDatabase>(connection, decoder, this, &WebIDBConnectionToServer::didDeleteDatabase);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidOpenDatabase::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidOpenDatabase>(connection, decoder, this, &WebIDBConnectionToServer::didOpenDatabase);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidAbortTransaction::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidAbortTransaction>(connection, decoder, this, &WebIDBConnectionToServer::didAbortTransaction);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidCommitTransaction::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidCommitTransaction>(connection, decoder, this, &WebIDBConnectionToServer::didCommitTransaction);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidCreateObjectStore::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidCreateObjectStore>(connection, decoder, this, &WebIDBConnectionToServer::didCreateObjectStore);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidDeleteObjectStore::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidDeleteObjectStore>(connection, decoder, this, &WebIDBConnectionToServer::didDeleteObjectStore);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidRenameObjectStore::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidRenameObjectStore>(connection, decoder, this, &WebIDBConnectionToServer::didRenameObjectStore);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidClearObjectStore::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidClearObjectStore>(connection, decoder, this, &WebIDBConnectionToServer::didClearObjectStore);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidCreateIndex::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidCreateIndex>(connection, decoder, this, &WebIDBConnectionToServer::didCreateIndex);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidDeleteIndex::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidDeleteIndex>(connection, decoder, this, &WebIDBConnectionToServer::didDeleteIndex);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidRenameIndex::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidRenameIndex>(connection, decoder, this, &WebIDBConnectionToServer::didRenameIndex);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidPutOrAdd::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidPutOrAdd>(connection, decoder, this, &WebIDBConnectionToServer::didPutOrAdd);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidGetRecord::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidGetRecord>(connection, decoder, this, &WebIDBConnectionToServer::didGetRecord);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidGetAllRecords::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidGetAllRecords>(connection, decoder, this, &WebIDBConnectionToServer::didGetAllRecords);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidGetCount::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidGetCount>(connection, decoder, this, &WebIDBConnectionToServer::didGetCount);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidDeleteRecord::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidDeleteRecord>(connection, decoder, this, &WebIDBConnectionToServer::didDeleteRecord);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidOpenCursor::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidOpenCursor>(connection, decoder, this, &WebIDBConnectionToServer::didOpenCursor);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidIterateCursor::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidIterateCursor>(connection, decoder, this, &WebIDBConnectionToServer::didIterateCursor);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::FireVersionChangeEvent::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::FireVersionChangeEvent>(connection, decoder, this, &WebIDBConnectionToServer::fireVersionChangeEvent);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidStartTransaction::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidStartTransaction>(connection, decoder, this, &WebIDBConnectionToServer::didStartTransaction);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidCloseFromServer::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidCloseFromServer>(connection, decoder, this, &WebIDBConnectionToServer::didCloseFromServer);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::NotifyOpenDBRequestBlocked::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::NotifyOpenDBRequestBlocked>(connection, decoder, this, &WebIDBConnectionToServer::notifyOpenDBRequestBlocked);
    if (decoder.messageName() == Messages::WebIDBConnectionToServer::DidGetAllDatabaseNamesAndVersions::name())
        return IPC::handleMessage<Messages::WebIDBConnectionToServer::DidGetAllDatabaseNamesAndVersions>(connection, decoder, this, &WebIDBConnectionToServer::didGetAllDatabaseNamesAndVersions);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidDeleteDatabase>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidDeleteDatabase::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidOpenDatabase>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidOpenDatabase::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidAbortTransaction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidAbortTransaction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidCommitTransaction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidCommitTransaction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidCreateObjectStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidCreateObjectStore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidDeleteObjectStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidDeleteObjectStore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidRenameObjectStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidRenameObjectStore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidClearObjectStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidClearObjectStore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidCreateIndex>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidCreateIndex::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidDeleteIndex>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidDeleteIndex::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidRenameIndex>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidRenameIndex::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidPutOrAdd>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidPutOrAdd::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidGetRecord>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidGetRecord::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidGetAllRecords>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidGetAllRecords::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidGetCount>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidGetCount::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidDeleteRecord>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidDeleteRecord::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidOpenCursor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidOpenCursor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidIterateCursor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidIterateCursor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_FireVersionChangeEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::FireVersionChangeEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidStartTransaction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidStartTransaction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidCloseFromServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidCloseFromServer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_NotifyOpenDBRequestBlocked>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::NotifyOpenDBRequestBlocked::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebIDBConnectionToServer_DidGetAllDatabaseNamesAndVersions>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebIDBConnectionToServer::DidGetAllDatabaseNamesAndVersions::Arguments>(globalObject, decoder);
}

}

#endif

