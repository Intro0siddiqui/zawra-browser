/*
 * Copyright (C) 2016-2024 Apple Inc. All rights reserved.
 * Zawra BrowserDB stub: SQLiteIDBBackingStore replaced by BrowserDB (Z_IDBStore).
 */

#include "config.h"
#include "SQLiteIDBBackingStore.h"
#include <wtf/TZoneMallocInlines.h>

namespace WebCore {
namespace IDBServer {

WTF_MAKE_TZONE_ALLOCATED_IMPL(SQLiteIDBBackingStore);

SQLiteIDBBackingStore::SQLiteIDBBackingStore(const IDBDatabaseIdentifier& identifier, const String&)
    : IDBBackingStore()
{
}

SQLiteIDBBackingStore::~SQLiteIDBBackingStore() = default;

} // namespace IDBServer
} // namespace WebCore
