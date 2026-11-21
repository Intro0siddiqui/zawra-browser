/*
 * Copyright (C) 2025 Apple Inc. All rights reserved.
 * Zawra BrowserDB stub: SQLiteMemoryIDBBackingStore replaced by MemoryIDBBackingStore / BrowserDB.
 */

#pragma once

#include "SQLiteIDBBackingStore.h"

namespace WebCore {
namespace IDBServer {

class SQLiteMemoryIDBBackingStore final : public SQLiteIDBBackingStore {
    WTF_MAKE_TZONE_ALLOCATED_EXPORT(SQLiteMemoryIDBBackingStore, WEBCORE_EXPORT);
    WTF_OVERRIDE_DELETE_FOR_CHECKED_PTR(SQLiteMemoryIDBBackingStore);
public:
    WEBCORE_EXPORT explicit SQLiteMemoryIDBBackingStore(const IDBDatabaseIdentifier&);
    WEBCORE_EXPORT ~SQLiteMemoryIDBBackingStore() final;

    IDBError getOrEstablishDatabaseInfo(IDBDatabaseInfo&) final { return IDBError(); }
    bool isEphemeral() final { return true; }
    bool supportsSimultaneousReadWriteTransactions() final { return false; }
    String fullDatabasePath() const final { return nullString(); }
    void deleteBackingStore() final { }
};

} // namespace IDBServer
} // namespace WebCore
