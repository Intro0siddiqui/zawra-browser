/*
 * Copyright (C) 2025 Apple Inc. All rights reserved.
 * Zawra BrowserDB stub: SQLiteMemoryIDBBackingStore replaced by MemoryIDBBackingStore / BrowserDB.
 */

#include "config.h"
#include "SQLiteMemoryIDBBackingStore.h"
#include <wtf/TZoneMallocInlines.h>

namespace WebCore {
namespace IDBServer {

WTF_MAKE_TZONE_ALLOCATED_IMPL(SQLiteMemoryIDBBackingStore);

SQLiteMemoryIDBBackingStore::SQLiteMemoryIDBBackingStore(const IDBDatabaseIdentifier& identifier)
    : SQLiteIDBBackingStore(identifier, emptyString())
{
}

SQLiteMemoryIDBBackingStore::~SQLiteMemoryIDBBackingStore() = default;

} // namespace IDBServer
} // namespace WebCore
