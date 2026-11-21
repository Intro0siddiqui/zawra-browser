/*
 * Copyright (C) 2016-2024 Apple Inc. All rights reserved.
 * Zawra BrowserDB stub: SQLiteIDBBackingStore replaced by BrowserDB (Z_IDBStore).
 * All methods return default values — persistence is handled via BrowserDB.
 */

#pragma once

#include "IDBBackingStore.h"
#include "IDBDatabaseIdentifier.h"
#include "IDBDatabaseInfo.h"
#include "IDBDatabaseNameAndVersion.h"
#include "IDBResourceIdentifier.h"
#include <wtf/TZoneMalloc.h>

namespace WebCore {
namespace IDBServer {

class SQLiteIDBBackingStore : public IDBBackingStore {
    WTF_MAKE_TZONE_ALLOCATED_EXPORT(SQLiteIDBBackingStore, WEBCORE_EXPORT);
    WTF_OVERRIDE_DELETE_FOR_CHECKED_PTR(SQLiteIDBBackingStore);
public:
    WEBCORE_EXPORT SQLiteIDBBackingStore(const IDBDatabaseIdentifier&, const String&);
    WEBCORE_EXPORT ~SQLiteIDBBackingStore() override;

    IDBError getOrEstablishDatabaseInfo(IDBDatabaseInfo&) override { return IDBError(); }
    uint64_t databaseVersion() override { return 0; }

    IDBError beginTransaction(const IDBTransactionInfo&) override { return IDBError(); }
    IDBError abortTransaction(const IDBResourceIdentifier&) override { return IDBError(); }
    IDBError commitTransaction(const IDBResourceIdentifier&) override { return IDBError(); }

    IDBError createObjectStore(const IDBResourceIdentifier&, const IDBObjectStoreInfo&) override { return IDBError(); }
    IDBError deleteObjectStore(const IDBResourceIdentifier&, IDBObjectStoreIdentifier) override { return IDBError(); }
    IDBError renameObjectStore(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, const String&) override { return IDBError(); }
    IDBError clearObjectStore(const IDBResourceIdentifier&, IDBObjectStoreIdentifier) override { return IDBError(); }
    IDBError deleteIndex(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, IDBIndexIdentifier) override { return IDBError(); }
    IDBError renameIndex(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, IDBIndexIdentifier, const String&) override { return IDBError(); }
    IDBError keyExistsInObjectStore(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, const IDBKeyData&, bool& keyExists) override { keyExists = false; return IDBError(); }
    IDBError deleteRange(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, const IDBKeyRangeData&) override { return IDBError(); }
    IDBError overwriteRecord(const IDBResourceIdentifier&, const IDBObjectStoreInfo&, const IDBKeyData&, const IndexIDToIndexKeyMap&, const IDBValue&) override { return IDBError(); }
    IDBError getRecord(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, const IDBKeyRangeData&, IDBGetRecordDataType, IDBGetResult&) override { return IDBError(); }
    IDBError getAllRecords(const IDBResourceIdentifier&, const IDBGetAllRecordsData&, IDBGetAllResult&) override { return IDBError(); }
    IDBError getIndexRecord(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, IDBIndexIdentifier, IndexedDB::IndexRecordType, const IDBKeyRangeData&, IDBGetResult&) override { return IDBError(); }
    IDBError getCount(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, std::optional<IDBIndexIdentifier>, const IDBKeyRangeData&, uint64_t& outCount) override { outCount = 0; return IDBError(); }
    IDBError generateKeyNumber(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, uint64_t& keyNumber) override { keyNumber = 0; return IDBError(); }
    IDBError revertGeneratedKeyNumber(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, uint64_t) override { return IDBError(); }
    IDBError maybeUpdateKeyGeneratorNumber(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, double) override { return IDBError(); }
    IDBError openCursor(const IDBResourceIdentifier&, const IDBCursorInfo&, IDBGetResult&) override { return IDBError(); }
    IDBError iterateCursor(const IDBResourceIdentifier&, const IDBResourceIdentifier&, const IDBIterateCursorData&, IDBGetResult&) override { return IDBError(); }

    IDBError addIndex(const IDBResourceIdentifier&, const IDBIndexInfo&) override { return IDBError(); }
    void revertAddIndex(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, IDBIndexIdentifier) override { }
    IDBError updateIndexRecordsWithIndexKey(const IDBResourceIdentifier&, const IDBIndexInfo&, const IDBKeyData&, const IndexKey&, std::optional<int64_t>) override { return IDBError(); }
    void forEachObjectStoreRecord(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, Function<void(RecordOrError&&)>&&) override { }

    IDBObjectStoreInfo* infoForObjectStore(IDBObjectStoreIdentifier) override { return nullptr; }
    void deleteBackingStore() override { }

    bool supportsSimultaneousReadWriteTransactions() override { return false; }
    bool isEphemeral() override { return false; }
    String fullDatabasePath() const override { return emptyString(); }

    void close() override { }

    bool hasTransaction(const IDBResourceIdentifier&) const final { return false; }
    void handleLowMemoryWarning() override { }

    // Static helpers called from IDBServer
    static uint64_t databasesSizeForDirectory(const String&) { return 0; }
    static String fullDatabasePathForDirectory(const String& dir) { return dir; }
    static String encodeDatabaseName(const String& name) { return name; }
    static String decodeDatabaseName(const String& name) { return name; }
    static std::optional<IDBDatabaseNameAndVersion> databaseNameAndVersionFromFile(const String&) { return std::nullopt; }
};

} // namespace IDBServer
} // namespace WebCore
