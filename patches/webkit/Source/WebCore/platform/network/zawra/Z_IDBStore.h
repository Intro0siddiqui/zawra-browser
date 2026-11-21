#pragma once

#include "IDBBackingStore.h"
#include "IDBDatabaseIdentifier.h"
#include "IDBDatabaseInfo.h"
#include "IDBIndexIdentifier.h"
#include "IDBObjectStoreIdentifier.h"
#include "IDBResourceIdentifier.h"
#include <wtf/CheckedPtr.h>
#include <wtf/HashMap.h>
#include <wtf/TZoneMalloc.h>

namespace WebCore {
namespace IDBServer {

struct ZCursorState;

class Z_IDBStore final : public IDBBackingStore {
    WTF_MAKE_TZONE_ALLOCATED(Z_IDBStore);
    WTF_OVERRIDE_DELETE_FOR_CHECKED_PTR(Z_IDBStore);
public:
    WEBCORE_EXPORT explicit Z_IDBStore(const IDBDatabaseIdentifier&);
    WEBCORE_EXPORT ~Z_IDBStore();

    IDBError getOrEstablishDatabaseInfo(IDBDatabaseInfo&) final;
    uint64_t databaseVersion() final;

    IDBError beginTransaction(const IDBTransactionInfo&) final;
    IDBError abortTransaction(const IDBResourceIdentifier&) final;
    IDBError commitTransaction(const IDBResourceIdentifier&) final;

    IDBError createObjectStore(const IDBResourceIdentifier&, const IDBObjectStoreInfo&) final;
    IDBError deleteObjectStore(const IDBResourceIdentifier&, IDBObjectStoreIdentifier) final;
    IDBError renameObjectStore(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, const String& newName) final;
    IDBError clearObjectStore(const IDBResourceIdentifier&, IDBObjectStoreIdentifier) final;
    IDBError deleteIndex(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, IDBIndexIdentifier) final;
    IDBError renameIndex(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, IDBIndexIdentifier, const String& newName) final;
    IDBError keyExistsInObjectStore(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, const IDBKeyData&, bool& keyExists) final;
    IDBError deleteRange(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, const IDBKeyRangeData&) final;
    IDBError overwriteRecord(const IDBResourceIdentifier&, const IDBObjectStoreInfo&, const IDBKeyData&, const IndexIDToIndexKeyMap&, const IDBValue&) final;
    IDBError getRecord(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, const IDBKeyRangeData&, IDBGetRecordDataType, IDBGetResult& outValue) final;
    IDBError getAllRecords(const IDBResourceIdentifier&, const IDBGetAllRecordsData&, IDBGetAllResult& outValue) final;
    IDBError getIndexRecord(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, IDBIndexIdentifier, IndexedDB::IndexRecordType, const IDBKeyRangeData&, IDBGetResult& outValue) final;
    IDBError getCount(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, std::optional<IDBIndexIdentifier>, const IDBKeyRangeData&, uint64_t& outCount) final;
    IDBError generateKeyNumber(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, uint64_t& keyNumber) final;
    IDBError revertGeneratedKeyNumber(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, uint64_t keyNumber) final;
    IDBError maybeUpdateKeyGeneratorNumber(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, double newKeyNumber) final;
    IDBError openCursor(const IDBResourceIdentifier&, const IDBCursorInfo&, IDBGetResult& outResult) final;
    IDBError iterateCursor(const IDBResourceIdentifier&, const IDBResourceIdentifier& cursorIdentifier, const IDBIterateCursorData&, IDBGetResult& outResult) final;

    IDBError addIndex(const IDBResourceIdentifier&, const IDBIndexInfo&) final;
    void revertAddIndex(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, IDBIndexIdentifier) final;
    IDBError updateIndexRecordsWithIndexKey(const IDBResourceIdentifier&, const IDBIndexInfo&, const IDBKeyData&, const IndexKey&, std::optional<int64_t> recordID) final;
    void forEachObjectStoreRecord(const IDBResourceIdentifier&, IDBObjectStoreIdentifier, Function<void(RecordOrError&&)>&&) final;

    IDBObjectStoreInfo* infoForObjectStore(IDBObjectStoreIdentifier) final;
    void deleteBackingStore() final;

    bool supportsSimultaneousReadWriteTransactions() final { return false; }
    bool isEphemeral() final { return false; }
    String fullDatabasePath() const final { return nullString(); }

    bool hasTransaction(const IDBResourceIdentifier&) const final { return false; }
    void handleLowMemoryWarning() final { }

    void close() final;

private:
    Vector<uint8_t> makeKey(uint8_t type) const;
    Vector<uint8_t> makeKeyWithOS(uint8_t type, uint64_t osID) const;
    Vector<uint8_t> makeKeyWithOSAndIndex(uint8_t type, uint64_t osID, uint64_t indexID) const;

    static Vector<uint8_t> packU64(uint64_t val);
    static Vector<uint8_t> packU32(uint32_t val);
    static void writeU64(Vector<uint8_t>& buf, uint64_t val);
    static void writeU32(Vector<uint8_t>& buf, uint32_t val);
    static uint64_t readU64(const uint8_t*& data, const uint8_t* end);
    static uint32_t readU32(const uint8_t*& data, const uint8_t* end);

    IDBError getAllRecordsForObjectStore(const IDBGetAllRecordsData&, IDBGetAllResult&);
    IDBError getAllRecordsForIndex(const IDBGetAllRecordsData&, IDBGetAllResult&);
    IDBError scanObjectStoreRecords(uint64_t objectStoreIdentifier, const IDBKeyRangeData&, Vector<std::tuple<IDBKeyData, IDBKeyData, ThreadSafeDataBuffer>>&);
    IDBError scanIndexRecords(uint64_t objectStoreIdentifier, uint64_t indexIdentifier, const IDBKeyRangeData&, Vector<std::tuple<IDBKeyData, IDBKeyData, ThreadSafeDataBuffer>>&);
    IDBError getObjectStoreValue(uint64_t objectStoreIdentifier, const IDBKeyData& primaryKey, ThreadSafeDataBuffer& outBuffer);

    IDBDatabaseIdentifier m_identifier;
    uint64_t m_databaseID { 0 };
    std::unique_ptr<IDBDatabaseInfo> m_databaseInfo;
    HashMap<IDBObjectStoreIdentifier, IDBObjectStoreInfo> m_objectStoreInfoCache;
    HashMap<IDBResourceIdentifier, std::unique_ptr<ZCursorState>> m_cursors;
};

} // namespace IDBServer
} // namespace WebCore
