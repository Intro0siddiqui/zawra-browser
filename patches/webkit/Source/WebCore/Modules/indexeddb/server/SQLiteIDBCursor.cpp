/*
 * Copyright (C) 2016-2021 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

// Zawra no-op: SQLiteIDBCursor is replaced by Z_IDBStore (BrowserDB).
// This file is compiled to satisfy the linker but all methods are stubs.

#include "config.h"
#include "SQLiteIDBCursor.h"

#include "IDBCursorInfo.h"
#include "IDBGetResult.h"
#include "SQLiteIDBTransaction.h"

namespace WebCore::IDBServer {

std::unique_ptr<SQLiteIDBCursor> SQLiteIDBCursor::maybeCreate(SQLiteIDBTransaction&, const IDBCursorInfo&)
{
    return nullptr;
}

std::unique_ptr<SQLiteIDBCursor> SQLiteIDBCursor::maybeCreateBackingStoreCursor(SQLiteIDBTransaction&, const uint64_t, const uint64_t, const IDBKeyRangeData&)
{
    return nullptr;
}

SQLiteIDBCursor::SQLiteIDBCursor(SQLiteIDBTransaction& transaction, const IDBCursorInfo&)
    : m_transaction(&transaction)
    , m_cursorIdentifier(IDBResourceIdentifier::emptyValue())
    , m_objectStoreID(0)
{
}

SQLiteIDBCursor::SQLiteIDBCursor(SQLiteIDBTransaction& transaction, uint64_t objectStoreID, uint64_t, const IDBKeyRangeData&)
    : m_transaction(&transaction)
    , m_cursorIdentifier(IDBResourceIdentifier::emptyValue())
    , m_objectStoreID(objectStoreID)
{
}

SQLiteIDBCursor::~SQLiteIDBCursor() = default;

int64_t SQLiteIDBCursor::currentRecordRowID() const
{
    return 0;
}

const IDBKeyData& SQLiteIDBCursor::currentKey() const
{
    static const IDBKeyData emptyKey;
    return emptyKey;
}

const IDBKeyData& SQLiteIDBCursor::currentPrimaryKey() const
{
    static const IDBKeyData emptyKey;
    return emptyKey;
}

const IDBValue& SQLiteIDBCursor::currentValue() const
{
    static const IDBValue emptyValue;
    return emptyValue;
}

bool SQLiteIDBCursor::advance(uint64_t)
{
    return false;
}

bool SQLiteIDBCursor::iterate(const IDBKeyData&, const IDBKeyData&)
{
    return false;
}

bool SQLiteIDBCursor::prefetchOneRecord()
{
    return false;
}

bool SQLiteIDBCursor::prefetch()
{
    return false;
}

bool SQLiteIDBCursor::didComplete() const
{
    return true;
}

bool SQLiteIDBCursor::didError() const
{
    return false;
}

void SQLiteIDBCursor::objectStoreRecordsChanged()
{
}

void SQLiteIDBCursor::currentData(IDBGetResult& result, const std::optional<IDBKeyPath>&, ShouldIncludePrefetchedRecords)
{
    result = IDBGetResult();
}

bool SQLiteIDBCursor::establishStatement()
{
    return false;
}

bool SQLiteIDBCursor::createSQLiteStatement(StringView)
{
    return false;
}

bool SQLiteIDBCursor::bindArguments()
{
    return false;
}

bool SQLiteIDBCursor::resetAndRebindPreIndexStatementIfNecessary()
{
    return false;
}

void SQLiteIDBCursor::resetAndRebindStatement()
{
}

bool SQLiteIDBCursor::fetch()
{
    return false;
}

bool SQLiteIDBCursor::fetchNextRecord(SQLiteCursorRecord&)
{
    return false;
}

SQLiteIDBCursor::FetchResult SQLiteIDBCursor::internalFetchNextRecord(SQLiteCursorRecord&)
{
    return FetchResult::Failure;
}

void SQLiteIDBCursor::markAsErrored(SQLiteCursorRecord& record)
{
    record.errored = true;
}

void SQLiteIDBCursor::increaseCountToPrefetch()
{
}

} // namespace WebCore::IDBServer
