/*
 * Zawra no-op stub: SQLiteIDBBackingStore replaced by BrowserDB (Z_IDBStore).
 * All methods return failure/default values — IndexedDB will fail gracefully.
 */

#include "config.h"
#include "SQLiteIDBBackingStore.h"

namespace WebCore {
namespace IDBServer {

SQLiteIDBBackingStore::SQLiteIDBBackingStore(const IDBDatabaseIdentifier&, const String&)
{
}

SQLiteIDBBackingStore::~SQLiteIDBBackingStore()
{
}

IDBError SQLiteIDBBackingStore::getOrEstablishDatabaseInfo(IDBDatabaseInfo&)
{
    return IDBError();
}

uint64_t SQLiteIDBBackingStore::databaseVersion()
{
    return 0;
}

IDBError SQLiteIDBBackingStore::beginTransaction(const IDBTransactionInfo&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::abortTransaction(const IDBResourceIdentifier&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::commitTransaction(const IDBResourceIdentifier&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::createObjectStore(const IDBResourceIdentifier&, const IDBObjectStoreInfo&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::deleteObjectStore(const IDBResourceIdentifier&, uint64_t)
{
    return { };
}

IDBError SQLiteIDBBackingStore::renameObjectStore(const IDBResourceIdentifier&, uint64_t, const String&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::clearObjectStore(const IDBResourceIdentifier&, uint64_t)
{
    return { };
}

IDBError SQLiteIDBBackingStore::createIndex(const IDBResourceIdentifier&, const IDBIndexInfo&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::deleteIndex(const IDBResourceIdentifier&, uint64_t, uint64_t)
{
    return { };
}

IDBError SQLiteIDBBackingStore::renameIndex(const IDBResourceIdentifier&, uint64_t, uint64_t, const String&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::keyExistsInObjectStore(const IDBResourceIdentifier&, uint64_t, const IDBKeyData&, bool& keyExists)
{
    keyExists = false;
    return { };
}

IDBError SQLiteIDBBackingStore::deleteRange(const IDBResourceIdentifier&, uint64_t, const IDBKeyRangeData&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::addRecord(const IDBResourceIdentifier&, const IDBObjectStoreInfo&, const IDBKeyData&, const IndexIDToIndexKeyMap&, const IDBValue&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::getRecord(const IDBResourceIdentifier&, uint64_t, const IDBKeyRangeData&, IDBGetRecordDataType, IDBGetResult&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::getAllRecords(const IDBResourceIdentifier&, const IDBGetAllRecordsData&, IDBGetAllResult&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::getIndexRecord(const IDBResourceIdentifier&, uint64_t, uint64_t, IndexedDB::IndexRecordType, const IDBKeyRangeData&, IDBGetResult&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::getCount(const IDBResourceIdentifier&, uint64_t, uint64_t, const IDBKeyRangeData&, uint64_t& outCount)
{
    outCount = 0;
    return { };
}

IDBError SQLiteIDBBackingStore::generateKeyNumber(const IDBResourceIdentifier&, uint64_t, uint64_t& keyNumber)
{
    keyNumber = 0;
    return { };
}

IDBError SQLiteIDBBackingStore::revertGeneratedKeyNumber(const IDBResourceIdentifier&, uint64_t, uint64_t)
{
    return { };
}

IDBError SQLiteIDBBackingStore::maybeUpdateKeyGeneratorNumber(const IDBResourceIdentifier&, uint64_t, double)
{
    return { };
}

IDBError SQLiteIDBBackingStore::openCursor(const IDBResourceIdentifier&, const IDBCursorInfo&, IDBGetResult&)
{
    return { };
}

IDBError SQLiteIDBBackingStore::iterateCursor(const IDBResourceIdentifier&, const IDBResourceIdentifier&, const IDBIterateCursorData&, IDBGetResult&)
{
    return { };
}

IDBObjectStoreInfo* SQLiteIDBBackingStore::infoForObjectStore(uint64_t)
{
    return nullptr;
}

void SQLiteIDBBackingStore::deleteBackingStore()
{
}

String SQLiteIDBBackingStore::fullDatabasePath() const
{
    return emptyString();
}

void SQLiteIDBBackingStore::close()
{
}

bool SQLiteIDBBackingStore::hasTransaction(const IDBResourceIdentifier&) const
{
    return false;
}

void SQLiteIDBBackingStore::handleLowMemoryWarning()
{
}

String SQLiteIDBBackingStore::fullDatabasePathForDirectory(const String&)
{
    return emptyString();
}

std::optional<IDBDatabaseNameAndVersion> SQLiteIDBBackingStore::databaseNameAndVersionFromFile(const String&)
{
    return std::nullopt;
}

String SQLiteIDBBackingStore::encodeDatabaseName(const String& databaseName)
{
    return databaseName;
}

String SQLiteIDBBackingStore::decodeDatabaseName(const String& originalName)
{
    return originalName;
}

uint64_t SQLiteIDBBackingStore::databasesSizeForDirectory(const String&)
{
    return 0;
}

} // namespace IDBServer
} // namespace WebCore
