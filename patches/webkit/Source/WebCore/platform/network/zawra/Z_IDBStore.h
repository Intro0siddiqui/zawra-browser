#pragma once

#include "IDBBackingStore.h"
#include "IDBDatabaseIdentifier.h"
#include "IDBDatabaseInfo.h"
#include "IDBResourceIdentifier.h"
#include <wtf/HashMap.h>

namespace WebCore {
namespace IDBServer {

class Z_IDBStore final : public IDBBackingStore {
    WTF_MAKE_FAST_ALLOCATED;
public:
    WEBCORE_EXPORT explicit Z_IDBStore(const IDBDatabaseIdentifier&);
    WEBCORE_EXPORT ~Z_IDBStore();

    IDBError getOrEstablishDatabaseInfo(IDBDatabaseInfo&) final;
    uint64_t databaseVersion() final;

    IDBError beginTransaction(const IDBTransactionInfo&) final;
    IDBError abortTransaction(const IDBResourceIdentifier&) final;
    IDBError commitTransaction(const IDBResourceIdentifier&) final;

    IDBError createObjectStore(const IDBResourceIdentifier&, const IDBObjectStoreInfo&) final;
    IDBError deleteObjectStore(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier) final;
    IDBError renameObjectStore(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, const String& newName) final;
    IDBError clearObjectStore(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier) final;
    IDBError createIndex(const IDBResourceIdentifier&, const IDBIndexInfo&) final;
    IDBError deleteIndex(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t indexIdentifier) final;
    IDBError renameIndex(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t indexIdentifier, const String& newName) final;
    IDBError keyExistsInObjectStore(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, const IDBKeyData&, bool& keyExists) final;
    IDBError deleteRange(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, const IDBKeyRangeData&) final;
    IDBError addRecord(const IDBResourceIdentifier&, const IDBObjectStoreInfo&, const IDBKeyData&, const IndexIDToIndexKeyMap&, const IDBValue&) final;
    IDBError getRecord(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, const IDBKeyRangeData&, IDBGetRecordDataType, IDBGetResult& outValue) final;
    IDBError getAllRecords(const IDBResourceIdentifier&, const IDBGetAllRecordsData&, IDBGetAllResult& outValue) final;
    IDBError getIndexRecord(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t indexIdentifier, IndexedDB::IndexRecordType, const IDBKeyRangeData&, IDBGetResult& outValue) final;
    IDBError getCount(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t indexIdentifier, const IDBKeyRangeData&, uint64_t& outCount) final;
    IDBError generateKeyNumber(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t& keyNumber) final;
    IDBError revertGeneratedKeyNumber(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t keyNumber) final;
    IDBError maybeUpdateKeyGeneratorNumber(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, double newKeyNumber) final;
    IDBError openCursor(const IDBResourceIdentifier&, const IDBCursorInfo&, IDBGetResult& outResult) final;
    IDBError iterateCursor(const IDBResourceIdentifier&, const IDBResourceIdentifier& cursorIdentifier, const IDBIterateCursorData&, IDBGetResult& outResult) final;

    IDBObjectStoreInfo* infoForObjectStore(uint64_t objectStoreIdentifier) final;
    void deleteBackingStore() final;

    bool supportsSimultaneousTransactions() final { return false; }
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

    IDBDatabaseIdentifier m_identifier;
    uint64_t m_databaseID { 0 };
    std::unique_ptr<IDBDatabaseInfo> m_databaseInfo;
    HashMap<uint64_t, IDBObjectStoreInfo> m_objectStoreInfoCache;
};

} // namespace IDBServer
} // namespace WebCore
