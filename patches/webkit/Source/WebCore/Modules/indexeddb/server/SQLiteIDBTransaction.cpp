/*
 * Copyright (C) 2013, 2016 Apple Inc. All rights reserved.
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

// Zawra no-op: SQLiteIDBBackingStore is replaced by Z_IDBStore (BrowserDB).
// This file is compiled to satisfy the linker but all methods are stubs.

#include "config.h"
#include "SQLiteIDBTransaction.h"

#include "IDBCursorInfo.h"
#include "IDBKeyRangeData.h"
#include "SQLiteIDBBackingStore.h"
#include "SQLiteIDBCursor.h"
#include "platform/sql/SQLiteTransaction.h"
#include "platform/sql/SQLiteDatabase.h"

namespace WebCore::IDBServer {

SQLiteIDBTransaction::SQLiteIDBTransaction(SQLiteIDBBackingStore& backingStore, const IDBTransactionInfo& info)
    : m_info(info)
    , m_backingStore(backingStore)
{
}

SQLiteIDBTransaction::~SQLiteIDBTransaction()
{
}

IDBError SQLiteIDBTransaction::begin(SQLiteDatabase&)
{
    return IDBError();
}

IDBError SQLiteIDBTransaction::commit()
{
    return IDBError();
}

IDBError SQLiteIDBTransaction::abort()
{
    return IDBError();
}

std::unique_ptr<SQLiteIDBCursor> SQLiteIDBTransaction::maybeOpenBackingStoreCursor(uint64_t, uint64_t, const IDBKeyRangeData&)
{
    return nullptr;
}

SQLiteIDBCursor* SQLiteIDBTransaction::maybeOpenCursor(const IDBCursorInfo&)
{
    return nullptr;
}

void SQLiteIDBTransaction::closeCursor(SQLiteIDBCursor&)
{
}

void SQLiteIDBTransaction::notifyCursorsOfChanges(int64_t)
{
}

bool SQLiteIDBTransaction::inProgress() const
{
    return false;
}

void SQLiteIDBTransaction::addBlobFile(const String&, const String&)
{
}

void SQLiteIDBTransaction::addRemovedBlobFile(const String&)
{
}

void SQLiteIDBTransaction::clearCursors()
{
}

void SQLiteIDBTransaction::reset()
{
}

void SQLiteIDBTransaction::moveBlobFilesIfNecessary()
{
}

void SQLiteIDBTransaction::deleteBlobFilesIfNecessary()
{
}

} // namespace WebCore::IDBServer
