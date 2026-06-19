#include "config.h"
#include "Z_IDBStore.h"

#include "IDBCursorInfo.h"
#include "IDBGetAllRecordsData.h"
#include "IDBGetAllResult.h"
#include "IDBGetRecordData.h"
#include "IDBGetResult.h"
#include "IDBIterateCursorData.h"
#include "IDBKeyData.h"
#include "IDBSerialization.h"
#include "IDBValue.h"
#include "IndexKey.h"
#include "IndexedDB.h"
#include "Logging.h"
#include "ThreadSafeDataBuffer.h"
#include <algorithm>
#include <tuple>

extern "C" {
    int32_t Z_IDBStore_Put(const uint8_t* key, size_t key_len, const uint8_t* value, size_t value_len);
    int32_t Z_IDBStore_Get(const uint8_t* key, size_t key_len, uint8_t** out_ptr, size_t* out_len);
    int32_t Z_IDBStore_Delete(const uint8_t* key, size_t key_len);
    int32_t Z_IDBStore_ScanPrefix(const uint8_t* prefix, size_t prefix_len, uint8_t* out_buf, size_t out_buf_len);
    int32_t Z_IDBStore_Clear();
    void Z_Free_Buffer(uint8_t* ptr, size_t len);
}

namespace WebCore {
namespace IDBServer {

static const uint64_t maxGeneratorValue = 0x20000000000000;

static uint64_t hashIdentifier(const IDBDatabaseIdentifier& identifier)
{
    auto name = identifier.databaseName();
    auto nameUTF8 = name.utf8();
    uint64_t hash = 5381;
    for (size_t i = 0; i < nameUTF8.length(); ++i)
        hash = ((hash << 5) + hash) + static_cast<uint8_t>(nameUTF8.data()[i]);
    return hash;
}

void Z_IDBStore::writeU64(Vector<uint8_t>& buf, uint64_t val)
{
    for (int i = 0; i < 8; ++i) {
        buf.append(static_cast<uint8_t>(val & 0xFF));
        val >>= 8;
    }
}

void Z_IDBStore::writeU32(Vector<uint8_t>& buf, uint32_t val)
{
    for (int i = 0; i < 4; ++i) {
        buf.append(static_cast<uint8_t>(val & 0xFF));
        val >>= 8;
    }
}

Vector<uint8_t> Z_IDBStore::packU64(uint64_t val)
{
    Vector<uint8_t> buf;
    writeU64(buf, val);
    return buf;
}

Vector<uint8_t> Z_IDBStore::packU32(uint32_t val)
{
    Vector<uint8_t> buf;
    writeU32(buf, val);
    return buf;
}

uint64_t Z_IDBStore::readU64(const uint8_t*& data, const uint8_t* end)
{
    if (data + 8 > end)
        return 0;
    uint64_t val = 0;
    for (int i = 0; i < 8; ++i)
        val |= static_cast<uint64_t>(data[i]) << (i * 8);
    data += 8;
    return val;
}

uint32_t Z_IDBStore::readU32(const uint8_t*& data, const uint8_t* end)
{
    if (data + 4 > end)
        return 0;
    uint32_t val = 0;
    for (int i = 0; i < 4; ++i)
        val |= static_cast<uint32_t>(data[i]) << (i * 8);
    data += 4;
    return val;
}

Vector<uint8_t> Z_IDBStore::makeKey(uint8_t type) const
{
    Vector<uint8_t> key;
    writeU64(key, m_databaseID);
    key.append(type);
    return key;
}

Vector<uint8_t> Z_IDBStore::makeKeyWithOS(uint8_t type, uint64_t osID) const
{
    Vector<uint8_t> key;
    writeU64(key, m_databaseID);
    key.append(type);
    writeU64(key, osID);
    return key;
}

Vector<uint8_t> Z_IDBStore::makeKeyWithOSAndIndex(uint8_t type, uint64_t osID, uint64_t indexID) const
{
    Vector<uint8_t> key;
    writeU64(key, m_databaseID);
    key.append(type);
    writeU64(key, osID);
    writeU64(key, indexID);
    return key;
}

Z_IDBStore::Z_IDBStore(const IDBDatabaseIdentifier& identifier)
    : m_identifier(identifier)
    , m_databaseID(hashIdentifier(identifier))
{
}

Z_IDBStore::~Z_IDBStore() = default;

IDBError Z_IDBStore::getOrEstablishDatabaseInfo(IDBDatabaseInfo& info)
{
    LOG(IndexedDB, "Z_IDBStore::getOrEstablishDatabaseInfo");

    if (m_databaseInfo) {
        info = *m_databaseInfo;
        return IDBError { };
    }

    auto metaKey = makeKey(0x01);
    uint8_t* outPtr = nullptr;
    size_t outLen = 0;

    if (Z_IDBStore_Get(metaKey.data(), metaKey.size(), &outPtr, &outLen) == 0 && outPtr && outLen > 0) {
        const uint8_t* data = outPtr;
        const uint8_t* end = outPtr + outLen;

        uint64_t version = readU64(data, end);
        uint64_t maxIndexID = readU64(data, end);
        uint64_t maxObjectStoreID = readU64(data, end);

        m_databaseInfo = makeUnique<IDBDatabaseInfo>(m_identifier.databaseName(), version, maxIndexID, maxObjectStoreID);

        Z_Free_Buffer(outPtr, outLen);
    } else {
        if (outPtr)
            Z_Free_Buffer(outPtr, outLen);
        m_databaseInfo = makeUnique<IDBDatabaseInfo>(m_identifier.databaseName(), 0, 0);

        auto metaKey = makeKey(0x01);
        Vector<uint8_t> val;
        writeU64(val, 0ULL);
        writeU64(val, 0ULL);
        writeU64(val, 0ULL);
        Z_IDBStore_Put(metaKey.data(), metaKey.size(), val.data(), val.size());
    }

    auto osPrefix = makeKey(0x02);
    uint8_t scanBuf[65536];
    int32_t scanResult = Z_IDBStore_ScanPrefix(osPrefix.data(), osPrefix.size(), scanBuf, sizeof(scanBuf));
    if (scanResult == 0) {
        const uint8_t* sdata = scanBuf;
        const uint8_t* send = scanBuf + sizeof(scanBuf);
        while (sdata + 4 <= send) {
            uint32_t klen = readU32(sdata, send);
            if (!klen || sdata + klen > send)
                break;
            const uint8_t* keyStart = sdata;
            sdata += klen;
            if (sdata + 4 > send)
                break;
            uint32_t vlen = readU32(sdata, send);
            if (!vlen || sdata + vlen > send)
                break;
            const uint8_t* vdata = sdata;
            sdata += vlen;

            const uint8_t* vptr = vdata;
            const uint8_t* vend = vdata + vlen;

            uint64_t osID = readU64(vptr, vend);
            uint32_t nameLen = readU32(vptr, vend);
            String osName;
            if (nameLen && vptr + nameLen <= vend) {
                osName = String::fromUTF8(reinterpret_cast<const char*>(vptr), nameLen);
                vptr += nameLen;
            }
            std::optional<IDBKeyPath> keyPath;
            if (vptr + 4 <= vend) {
                uint32_t kpLen = readU32(vptr, vend);
                if (kpLen && vptr + kpLen <= vend) {
                    deserializeIDBKeyPath(vptr, kpLen, keyPath);
                    vptr += kpLen;
                }
            }
            bool autoInc = (vptr < vend) ? (*vptr++ != 0) : false;

            IDBObjectStoreInfo osInfo(osID, osName, keyPath ? std::optional<IDBKeyPath>(WTFMove(*keyPath)) : std::nullopt, autoInc);
            m_databaseInfo->addExistingObjectStore(osInfo);
            m_objectStoreInfoCache.set(osID, WTFMove(osInfo));
        }
    }

    info = *m_databaseInfo;
    return IDBError { };
}

uint64_t Z_IDBStore::databaseVersion()
{
    return m_databaseInfo ? m_databaseInfo->version() : 0;
}

IDBError Z_IDBStore::beginTransaction(const IDBTransactionInfo&)
{
    LOG(IndexedDB, "Z_IDBStore::beginTransaction");
    return IDBError { };
}

IDBError Z_IDBStore::abortTransaction(const IDBResourceIdentifier&)
{
    LOG(IndexedDB, "Z_IDBStore::abortTransaction");
    return IDBError { };
}

IDBError Z_IDBStore::commitTransaction(const IDBResourceIdentifier&)
{
    LOG(IndexedDB, "Z_IDBStore::commitTransaction");
    return IDBError { };
}

IDBError Z_IDBStore::createObjectStore(const IDBResourceIdentifier& transactionIdentifier, const IDBObjectStoreInfo& info)
{
    LOG(IndexedDB, "Z_IDBStore::createObjectStore - %s", info.name().utf8().data());

    ASSERT(m_databaseInfo);
    if (m_databaseInfo->hasObjectStore(info.name()))
        return IDBError { ConstraintError };

    auto keyPathBuffer = serializeIDBKeyPath(info.keyPath());

    Vector<uint8_t> val;
    writeU64(val, info.identifier());
    auto nameUTF8 = info.name().utf8();
    writeU32(val, nameUTF8.length());
    val.append(nameUTF8.data(), nameUTF8.length());
    if (keyPathBuffer) {
        auto span = keyPathBuffer->dataAsSpanForContiguousData();
        writeU32(val, span.size());
        val.append(span.data(), span.size());
    } else {
        writeU32(val, 0);
    }
    val.append(static_cast<uint8_t>(info.autoIncrement() ? 1 : 0));

    auto key = makeKeyWithOS(0x02, info.identifier());
    Z_IDBStore_Put(key.data(), key.size(), val.data(), val.size());

    auto genKey = makeKeyWithOS(0x07, info.identifier());
    auto genVal = packU64(0ULL);
    Z_IDBStore_Put(genKey.data(), genKey.size(), genVal.data(), genVal.size());

    m_databaseInfo->addExistingObjectStore(info);
    m_objectStoreInfoCache.set(info.identifier(), info);

    return IDBError { };
}

IDBError Z_IDBStore::deleteObjectStore(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier)
{
    LOG(IndexedDB, "Z_IDBStore::deleteObjectStore - %" PRIu64, objectStoreIdentifier);

    ASSERT(m_databaseInfo);
    auto* osInfo = m_databaseInfo->infoForExistingObjectStore(objectStoreIdentifier);
    if (!osInfo)
        return IDBError { ConstraintError };

    auto metaKey = makeKeyWithOS(0x02, objectStoreIdentifier);
    Z_IDBStore_Delete(metaKey.data(), metaKey.size());

    auto genKey = makeKeyWithOS(0x07, objectStoreIdentifier);
    Z_IDBStore_Delete(genKey.data(), genKey.size());

    uint8_t scanBuf[65536];
    auto recPrefix = makeKeyWithOS(0x03, objectStoreIdentifier);
    if (Z_IDBStore_ScanPrefix(recPrefix.data(), recPrefix.size(), scanBuf, sizeof(scanBuf)) == 0) {
        const uint8_t* sdata = scanBuf;
        const uint8_t* send = scanBuf + sizeof(scanBuf);
        while (sdata + 4 <= send) {
            uint32_t klen = readU32(sdata, send);
            if (!klen || sdata + klen > send)
                break;
            Z_IDBStore_Delete(sdata, klen);
            sdata += klen;
            if (sdata + 4 > send)
                break;
            uint32_t vlen = readU32(sdata, send);
            sdata += vlen;
        }
    }

    auto idxPrefix = makeKeyWithOS(0x04, objectStoreIdentifier);
    if (Z_IDBStore_ScanPrefix(idxPrefix.data(), idxPrefix.size(), scanBuf, sizeof(scanBuf)) == 0) {
        const uint8_t* sdata = scanBuf;
        const uint8_t* send = scanBuf + sizeof(scanBuf);
        while (sdata + 4 <= send) {
            uint32_t klen = readU32(sdata, send);
            if (!klen || sdata + klen > send)
                break;
            Z_IDBStore_Delete(sdata, klen);
            sdata += klen;
            if (sdata + 4 > send)
                break;
            uint32_t vlen = readU32(sdata, send);
            sdata += vlen;
        }
    }

    auto idxRecPrefix = makeKeyWithOS(0x05, objectStoreIdentifier);
    if (Z_IDBStore_ScanPrefix(idxRecPrefix.data(), idxRecPrefix.size(), scanBuf, sizeof(scanBuf)) == 0) {
        const uint8_t* sdata = scanBuf;
        const uint8_t* send = scanBuf + sizeof(scanBuf);
        while (sdata + 4 <= send) {
            uint32_t klen = readU32(sdata, send);
            if (!klen || sdata + klen > send)
                break;
            Z_IDBStore_Delete(sdata, klen);
            sdata += klen;
            if (sdata + 4 > send)
                break;
            uint32_t vlen = readU32(sdata, send);
            sdata += vlen;
        }
    }

    m_databaseInfo->deleteObjectStore(osInfo->name());
    m_objectStoreInfoCache.remove(objectStoreIdentifier);

    return IDBError { };
}

IDBError Z_IDBStore::renameObjectStore(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, const String& newName)
{
    LOG(IndexedDB, "Z_IDBStore::renameObjectStore - %" PRIu64, objectStoreIdentifier);

    ASSERT(m_databaseInfo);
    auto* info = m_databaseInfo->infoForExistingObjectStore(objectStoreIdentifier);
    if (!info)
        return IDBError { ConstraintError };

    m_databaseInfo->renameObjectStore(objectStoreIdentifier, newName);

    auto metaKey = makeKeyWithOS(0x02, objectStoreIdentifier);
    auto* updatedInfo = m_databaseInfo->infoForExistingObjectStore(objectStoreIdentifier);
    if (!updatedInfo)
        return IDBError { UnknownError };

    auto keyPathBuffer = serializeIDBKeyPath(updatedInfo->keyPath());
    Vector<uint8_t> val;
    writeU64(val, updatedInfo->identifier());
    auto nameUTF8 = newName.utf8();
    writeU32(val, nameUTF8.length());
    val.append(nameUTF8.data(), nameUTF8.length());
    if (keyPathBuffer) {
        auto span = keyPathBuffer->dataAsSpanForContiguousData();
        writeU32(val, span.size());
        val.append(span.data(), span.size());
    } else {
        writeU32(val, 0);
    }
    val.append(static_cast<uint8_t>(updatedInfo->autoIncrement() ? 1 : 0));

    Z_IDBStore_Put(metaKey.data(), metaKey.size(), val.data(), val.size());

    auto it = m_objectStoreInfoCache.find(objectStoreIdentifier);
    if (it != m_objectStoreInfoCache.end()) {
        it->value.rename(newName);
    }

    return IDBError { };
}

IDBError Z_IDBStore::clearObjectStore(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier)
{
    LOG(IndexedDB, "Z_IDBStore::clearObjectStore - %" PRIu64, objectStoreIdentifier);

    uint8_t scanBuf[65536];
    auto recPrefix = makeKeyWithOS(0x03, objectStoreIdentifier);
    if (Z_IDBStore_ScanPrefix(recPrefix.data(), recPrefix.size(), scanBuf, sizeof(scanBuf)) == 0) {
        const uint8_t* sdata = scanBuf;
        const uint8_t* send = scanBuf + sizeof(scanBuf);
        while (sdata + 4 <= send) {
            uint32_t klen = readU32(sdata, send);
            if (!klen || sdata + klen > send)
                break;
            Z_IDBStore_Delete(sdata, klen);
            sdata += klen;
            if (sdata + 4 > send)
                break;
            uint32_t vlen = readU32(sdata, send);
            sdata += vlen;
        }
    }

    auto idxRecPrefix = makeKeyWithOS(0x05, objectStoreIdentifier);
    if (Z_IDBStore_ScanPrefix(idxRecPrefix.data(), idxRecPrefix.size(), scanBuf, sizeof(scanBuf)) == 0) {
        const uint8_t* sdata = scanBuf;
        const uint8_t* send = scanBuf + sizeof(scanBuf);
        while (sdata + 4 <= send) {
            uint32_t klen = readU32(sdata, send);
            if (!klen || sdata + klen > send)
                break;
            Z_IDBStore_Delete(sdata, klen);
            sdata += klen;
            if (sdata + 4 > send)
                break;
            uint32_t vlen = readU32(sdata, send);
            sdata += vlen;
        }
    }

    return IDBError { };
}

IDBError Z_IDBStore::createIndex(const IDBResourceIdentifier& transactionIdentifier, const IDBIndexInfo& info)
{
    LOG(IndexedDB, "Z_IDBStore::createIndex");

    ASSERT(m_databaseInfo);
    auto* osInfo = m_databaseInfo->infoForExistingObjectStore(info.objectStoreIdentifier());
    if (!osInfo)
        return IDBError { ConstraintError };

    auto keyPathBuffer = serializeIDBKeyPath(info.keyPath());

    Vector<uint8_t> val;
    writeU64(val, info.identifier());
    writeU64(val, info.objectStoreIdentifier());
    auto nameUTF8 = info.name().utf8();
    writeU32(val, nameUTF8.length());
    val.append(nameUTF8.data(), nameUTF8.length());
    if (keyPathBuffer) {
        auto span = keyPathBuffer->dataAsSpanForContiguousData();
        writeU32(val, span.size());
        val.append(span.data(), span.size());
    } else {
        writeU32(val, 0);
    }
    val.append(static_cast<uint8_t>(info.unique() ? 1 : 0));
    val.append(static_cast<uint8_t>(info.multiEntry() ? 1 : 0));

    auto key = makeKeyWithOSAndIndex(0x04, info.objectStoreIdentifier(), info.identifier());
    Z_IDBStore_Put(key.data(), key.size(), val.data(), val.size());

    osInfo->addExistingIndex(info);
    m_databaseInfo->setMaxIndexID(info.identifier());

    return IDBError { };
}

IDBError Z_IDBStore::deleteIndex(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t indexIdentifier)
{
    LOG(IndexedDB, "Z_IDBStore::deleteIndex");

    ASSERT(m_databaseInfo);
    auto* osInfo = m_databaseInfo->infoForExistingObjectStore(objectStoreIdentifier);
    if (!osInfo)
        return IDBError { ConstraintError };

    auto* idxInfo = osInfo->infoForExistingIndex(indexIdentifier);
    if (!idxInfo)
        return IDBError { ConstraintError };

    auto metaKey = makeKeyWithOSAndIndex(0x04, objectStoreIdentifier, indexIdentifier);
    Z_IDBStore_Delete(metaKey.data(), metaKey.size());

    uint8_t scanBuf[65536];
    auto idxRecPrefix = makeKeyWithOSAndIndex(0x05, objectStoreIdentifier, indexIdentifier);
    if (Z_IDBStore_ScanPrefix(idxRecPrefix.data(), idxRecPrefix.size(), scanBuf, sizeof(scanBuf)) == 0) {
        const uint8_t* sdata = scanBuf;
        const uint8_t* send = scanBuf + sizeof(scanBuf);
        while (sdata + 4 <= send) {
            uint32_t klen = readU32(sdata, send);
            if (!klen || sdata + klen > send)
                break;
            Z_IDBStore_Delete(sdata, klen);
            sdata += klen;
            if (sdata + 4 > send)
                break;
            uint32_t vlen = readU32(sdata, send);
            sdata += vlen;
        }
    }

    osInfo->deleteIndex(indexIdentifier);

    return IDBError { };
}

IDBError Z_IDBStore::renameIndex(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t indexIdentifier, const String& newName)
{
    LOG(IndexedDB, "Z_IDBStore::renameIndex");

    ASSERT(m_databaseInfo);
    auto* osInfo = m_databaseInfo->infoForExistingObjectStore(objectStoreIdentifier);
    if (!osInfo)
        return IDBError { ConstraintError };

    auto* idxInfo = osInfo->infoForExistingIndex(indexIdentifier);
    if (!idxInfo)
        return IDBError { ConstraintError };

    idxInfo->rename(newName);

    auto keyPathBuffer = serializeIDBKeyPath(idxInfo->keyPath());
    Vector<uint8_t> val;
    writeU64(val, idxInfo->identifier());
    writeU64(val, idxInfo->objectStoreIdentifier());
    auto nameUTF8 = newName.utf8();
    writeU32(val, nameUTF8.length());
    val.append(nameUTF8.data(), nameUTF8.length());
    if (keyPathBuffer) {
        auto span = keyPathBuffer->dataAsSpanForContiguousData();
        writeU32(val, span.size());
        val.append(span.data(), span.size());
    } else {
        writeU32(val, 0);
    }
    val.append(static_cast<uint8_t>(idxInfo->unique() ? 1 : 0));
    val.append(static_cast<uint8_t>(idxInfo->multiEntry() ? 1 : 0));

    auto key = makeKeyWithOSAndIndex(0x04, objectStoreIdentifier, indexIdentifier);
    Z_IDBStore_Put(key.data(), key.size(), val.data(), val.size());

    return IDBError { };
}

IDBError Z_IDBStore::keyExistsInObjectStore(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, const IDBKeyData& keyData, bool& keyExists)
{
    LOG(IndexedDB, "Z_IDBStore::keyExistsInObjectStore");

    auto keyBuffer = serializeIDBKeyData(keyData);
    if (!keyBuffer)
        return IDBError { UnknownError, "Unable to serialize key"_s };

    auto span = keyBuffer->dataAsSpanForContiguousData();
    Vector<uint8_t> fullKey;
    writeU64(fullKey, m_databaseID);
    fullKey.append(0x03);
    writeU64(fullKey, objectStoreIdentifier);
    fullKey.append(span.data(), span.size());

    uint8_t* outPtr = nullptr;
    size_t outLen = 0;
    if (Z_IDBStore_Get(fullKey.data(), fullKey.size(), &outPtr, &outLen) == 0 && outPtr && outLen > 0) {
        keyExists = true;
        Z_Free_Buffer(outPtr, outLen);
    } else {
        keyExists = false;
        if (outPtr)
            Z_Free_Buffer(outPtr, outLen);
    }

    return IDBError { };
}

IDBError Z_IDBStore::deleteRange(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, const IDBKeyRangeData& range)
{
    LOG(IndexedDB, "Z_IDBStore::deleteRange");

    uint8_t scanBuf[65536];
    auto recPrefix = makeKeyWithOS(0x03, objectStoreIdentifier);
    if (Z_IDBStore_ScanPrefix(recPrefix.data(), recPrefix.size(), scanBuf, sizeof(scanBuf)) != 0)
        return IDBError { };

    const uint8_t* sdata = scanBuf;
    const uint8_t* send = scanBuf + sizeof(scanBuf);
    while (sdata + 4 <= send) {
        uint32_t klen = readU32(sdata, send);
        if (!klen || sdata + klen > send)
            break;

        const uint8_t* keyStart = sdata;
        sdata += klen;

        if (sdata + 4 > send)
            break;
        uint32_t vlen = readU32(sdata, send);
        sdata += vlen;

        size_t keyDataOffset = 1 + 8;
        size_t keyDataLen = klen > keyDataOffset ? klen - keyDataOffset : 0;
        if (keyDataLen > 0) {
            IDBKeyData storedKey;
            if (deserializeIDBKeyData(keyStart + keyDataOffset, keyDataLen, storedKey)) {
                if (range.isExactlyOneKey()) {
                    if (storedKey.compare(range.lowerKey) == 0)
                        Z_IDBStore_Delete(keyStart, klen);
                } else if (range.containsKey(storedKey)) {
                    Z_IDBStore_Delete(keyStart, klen);
                }
            }
        }
    }

    return IDBError { };
}

IDBError Z_IDBStore::addRecord(const IDBResourceIdentifier&, const IDBObjectStoreInfo& objectStoreInfo, const IDBKeyData& keyData, const IndexIDToIndexKeyMap& indexKeys, const IDBValue& value)
{
    LOG(IndexedDB, "Z_IDBStore::addRecord");

    auto keyBuffer = serializeIDBKeyData(keyData);
    if (!keyBuffer)
        return IDBError { UnknownError, "Unable to serialize key"_s };

    auto keySpan = keyBuffer->dataAsSpanForContiguousData();
    Vector<uint8_t> fullKey;
    writeU64(fullKey, m_databaseID);
    fullKey.append(0x03);
    writeU64(fullKey, objectStoreInfo.identifier());
    fullKey.append(keySpan.data(), keySpan.size());

    Vector<uint8_t> val;
    auto* dataPtr = value.data().data();
    if (dataPtr) {
        writeU32(val, dataPtr->size());
        val.append(dataPtr->data(), dataPtr->size());
    } else {
        writeU32(val, 0);
    }

    Z_IDBStore_Put(fullKey.data(), fullKey.size(), val.data(), val.size());

    for (auto& entry : indexKeys) {
        uint64_t indexID = entry.key;
        const IndexKey& idxKey = entry.value;

        auto keys = idxKey.multiEntry();
        if (keys.isEmpty()) {
            auto oneKey = idxKey.asOneKey();
            if (!oneKey.isNull())
                keys.append(oneKey);
        }

        for (auto& ik : keys) {
            auto idxKeyBuf = serializeIDBKeyData(ik);
            if (!idxKeyBuf)
                continue;
            auto idxKeySpan = idxKeyBuf->dataAsSpanForContiguousData();

            Vector<uint8_t> idxFullKey;
            writeU64(idxFullKey, m_databaseID);
            idxFullKey.append(0x05);
            writeU64(idxFullKey, objectStoreInfo.identifier());
            writeU64(idxFullKey, indexID);
            idxFullKey.append(idxKeySpan.data(), idxKeySpan.size());

            auto pkBuffer = serializeIDBKeyData(keyData);
            if (!pkBuffer)
                continue;
            auto pkSpan = pkBuffer->dataAsSpanForContiguousData();
            Vector<uint8_t> idxVal;
            writeU32(idxVal, pkSpan.size());
            idxVal.append(pkSpan.data(), pkSpan.size());

            Z_IDBStore_Put(idxFullKey.data(), idxFullKey.size(), idxVal.data(), idxVal.size());
        }
    }

    return IDBError { };
}

IDBError Z_IDBStore::getRecord(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, const IDBKeyRangeData& keyRange, IDBGetRecordDataType type, IDBGetResult& outValue)
{
    LOG(IndexedDB, "Z_IDBStore::getRecord");

    auto* objectStoreInfo = m_databaseInfo ? m_databaseInfo->infoForExistingObjectStore(objectStoreIdentifier) : nullptr;

    uint8_t scanBuf[65536];
    auto recPrefix = makeKeyWithOS(0x03, objectStoreIdentifier);
    if (Z_IDBStore_ScanPrefix(recPrefix.data(), recPrefix.size(), scanBuf, sizeof(scanBuf)) != 0)
        return IDBError { };

    const uint8_t* sdata = scanBuf;
    const uint8_t* send = scanBuf + sizeof(scanBuf);
    while (sdata + 4 <= send) {
        uint32_t klen = readU32(sdata, send);
        if (!klen || sdata + klen > send)
            break;

        const uint8_t* storedFullKey = sdata;
        size_t storedFullKeyLen = klen;
        sdata += klen;

        if (sdata + 4 > send)
            break;
        uint32_t vlen = readU32(sdata, send);
        const uint8_t* vdata = sdata;
        sdata += vlen;

        const uint8_t* keyDataStart = storedFullKey + 1 + 8 + 8;
        size_t keyDataLen = storedFullKeyLen > (1 + 8 + 8) ? storedFullKeyLen - (1 + 8 + 8) : 0;

        if (!keyDataLen)
            continue;

        IDBKeyData storedKey;
        if (!deserializeIDBKeyData(keyDataStart, keyDataLen, storedKey))
            continue;

        bool keyMatches;
        if (keyRange.isExactlyOneKey())
            keyMatches = storedKey.compare(keyRange.lowerKey) == 0;
        else
            keyMatches = keyRange.containsKey(storedKey);

        if (!keyMatches)
            continue;

        if (type == IDBGetRecordDataType::KeyOnly) {
            outValue = IDBGetResult(storedKey);
            return IDBError { };
        }

        const uint8_t* valData = vdata;
        const uint8_t* valEnd = vdata + vlen;
        uint32_t dataSize = readU32(valData, valEnd);
        if (dataSize && valData + dataSize <= valEnd) {
            Vector<uint8_t> dataCopy(valData, dataSize);
            auto buffer = ThreadSafeDataBuffer::create(WTFMove(dataCopy));
            outValue = IDBGetResult(storedKey, buffer, objectStoreInfo ? objectStoreInfo->keyPath() : std::nullopt);
        } else {
            outValue = IDBGetResult(storedKey, ThreadSafeDataBuffer(), objectStoreInfo ? objectStoreInfo->keyPath() : std::nullopt);
        }
        return IDBError { };
    }

    outValue = IDBGetResult();
    return IDBError { };
}

static bool keyMatchesRange(const IDBKeyData& key, const IDBKeyRangeData& range)
{
    if (range.isExactlyOneKey())
        return key.compare(range.lowerKey) == 0;
    return range.containsKey(key);
}

IDBError Z_IDBStore::getAllRecords(const IDBResourceIdentifier&, const IDBGetAllRecordsData& data, IDBGetAllResult& outValue)
{
    LOG(IndexedDB, "Z_IDBStore::getAllRecords");

    auto* objectStoreInfo = m_databaseInfo ? m_databaseInfo->infoForExistingObjectStore(data.objectStoreIdentifier) : nullptr;
    outValue = IDBGetAllResult(data.getAllType, objectStoreInfo ? objectStoreInfo->keyPath() : std::nullopt);

    if (data.indexIdentifier)
        return getAllRecordsForIndex(data, outValue);
    return getAllRecordsForObjectStore(data, outValue);
}

IDBError Z_IDBStore::getAllRecordsForObjectStore(const IDBGetAllRecordsData& data, IDBGetAllResult& outValue)
{
    uint8_t scanBuf[65536];
    auto recPrefix = makeKeyWithOS(0x03, data.objectStoreIdentifier);
    if (Z_IDBStore_ScanPrefix(recPrefix.data(), recPrefix.size(), scanBuf, sizeof(scanBuf)) != 0)
        return IDBError { };

    const uint8_t* sdata = scanBuf;
    const uint8_t* send = scanBuf + sizeof(scanBuf);

    while (sdata + 4 <= send) {
        uint32_t klen = readU32(sdata, send);
        if (!klen || sdata + klen > send)
            break;

        const uint8_t* storedFullKey = sdata;
        size_t storedFullKeyLen = klen;
        sdata += klen;

        if (sdata + 4 > send)
            break;
        uint32_t vlen = readU32(sdata, send);
        const uint8_t* vdata = sdata;
        sdata += vlen;

        size_t keyDataOffset = recPrefix.size();
        size_t keyDataLen = storedFullKeyLen > keyDataOffset ? storedFullKeyLen - keyDataOffset : 0;
        if (!keyDataLen)
            continue;

        IDBKeyData storedKey;
        if (!deserializeIDBKeyData(storedFullKey + keyDataOffset, keyDataLen, storedKey))
            continue;

        if (!keyMatchesRange(storedKey, data.keyRangeData))
            continue;

        if (data.getAllType == IndexedDB::GetAllType::Keys) {
            outValue.addKey(IDBKeyData(storedKey));
        } else {
            const uint8_t* valEnd = vdata + vlen;
            const uint8_t* valData = vdata;
            uint32_t dataSize = readU32(valData, valEnd);
            if (dataSize && valData + dataSize <= valEnd) {
                Vector<uint8_t> dataCopy(valData, dataSize);
                auto buffer = ThreadSafeDataBuffer::create(WTFMove(dataCopy));
                outValue.addValue(IDBValue(buffer));
            }
        }

        if (data.count && ((data.getAllType == IndexedDB::GetAllType::Keys) ? outValue.keys().size() : outValue.values().size()) >= *data.count)
            break;
    }

    return IDBError { };
}

IDBError Z_IDBStore::getAllRecordsForIndex(const IDBGetAllRecordsData& data, IDBGetAllResult& outValue)
{
    uint8_t scanBuf[65536];
    auto idxRecPrefix = makeKeyWithOSAndIndex(0x05, data.objectStoreIdentifier, data.indexIdentifier);
    if (Z_IDBStore_ScanPrefix(idxRecPrefix.data(), idxRecPrefix.size(), scanBuf, sizeof(scanBuf)) != 0)
        return IDBError { };

    const uint8_t* sdata = scanBuf;
    const uint8_t* send = scanBuf + sizeof(scanBuf);

    while (sdata + 4 <= send) {
        uint32_t klen = readU32(sdata, send);
        if (!klen || sdata + klen > send)
            break;

        const uint8_t* storedFullKey = sdata;
        size_t storedFullKeyLen = klen;
        sdata += klen;

        if (sdata + 4 > send)
            break;
        uint32_t vlen = readU32(sdata, send);
        const uint8_t* vdata = sdata;
        sdata += vlen;

        size_t keyDataOffset = idxRecPrefix.size();
        size_t keyDataLen = storedFullKeyLen > keyDataOffset ? storedFullKeyLen - keyDataOffset : 0;
        if (!keyDataLen)
            continue;

        IDBKeyData indexKey;
        if (!deserializeIDBKeyData(storedFullKey + keyDataOffset, keyDataLen, indexKey))
            continue;

        if (!keyMatchesRange(indexKey, data.keyRangeData))
            continue;

        const uint8_t* valEnd = vdata + vlen;
        const uint8_t* valData = vdata;
        uint32_t pkSize = readU32(valData, valEnd);
        IDBKeyData primaryKey;
        if (!pkSize || !deserializeIDBKeyData(valData, pkSize, primaryKey))
            continue;

        if (data.getAllType == IndexedDB::GetAllType::Keys) {
            outValue.addKey(WTFMove(primaryKey));
        } else {
            ThreadSafeDataBuffer valueBuffer;
            getObjectStoreValue(data.objectStoreIdentifier, primaryKey, valueBuffer);
            outValue.addValue(IDBValue(valueBuffer));
        }

        if (data.count && ((data.getAllType == IndexedDB::GetAllType::Keys) ? outValue.keys().size() : outValue.values().size()) >= *data.count)
            break;
    }

    return IDBError { };
}

IDBError Z_IDBStore::getIndexRecord(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t indexIdentifier, IndexedDB::IndexRecordType recordType, const IDBKeyRangeData& range, IDBGetResult& outValue)
{
    LOG(IndexedDB, "Z_IDBStore::getIndexRecord");

    auto* objectStoreInfo = m_databaseInfo ? m_databaseInfo->infoForExistingObjectStore(objectStoreIdentifier) : nullptr;

    uint8_t scanBuf[65536];
    auto idxRecPrefix = makeKeyWithOSAndIndex(0x05, objectStoreIdentifier, indexIdentifier);
    if (Z_IDBStore_ScanPrefix(idxRecPrefix.data(), idxRecPrefix.size(), scanBuf, sizeof(scanBuf)) != 0)
        return IDBError { };

    const uint8_t* sdata = scanBuf;
    const uint8_t* send = scanBuf + sizeof(scanBuf);

    while (sdata + 4 <= send) {
        uint32_t klen = readU32(sdata, send);
        if (!klen || sdata + klen > send)
            break;

        const uint8_t* storedFullKey = sdata;
        size_t storedFullKeyLen = klen;
        sdata += klen;

        if (sdata + 4 > send)
            break;
        uint32_t vlen = readU32(sdata, send);
        const uint8_t* vdata = sdata;
        sdata += vlen;

        size_t keyDataOffset = idxRecPrefix.size();
        size_t keyDataLen = storedFullKeyLen > keyDataOffset ? storedFullKeyLen - keyDataOffset : 0;
        if (!keyDataLen)
            continue;

        IDBKeyData indexKey;
        if (!deserializeIDBKeyData(storedFullKey + keyDataOffset, keyDataLen, indexKey))
            continue;

        if (!keyMatchesRange(indexKey, range))
            continue;

        const uint8_t* valEnd = vdata + vlen;
        const uint8_t* valData = vdata;
        uint32_t pkSize = readU32(valData, valEnd);
        IDBKeyData primaryKey;
        if (!pkSize || !deserializeIDBKeyData(valData, pkSize, primaryKey))
            continue;

        if (recordType == IndexedDB::IndexRecordType::Key) {
            outValue = IDBGetResult(primaryKey);
            return IDBError { };
        }

        ThreadSafeDataBuffer valueBuffer;
        getObjectStoreValue(objectStoreIdentifier, primaryKey, valueBuffer);
        outValue = IDBGetResult(indexKey, primaryKey, IDBValue(valueBuffer), objectStoreInfo ? objectStoreInfo->keyPath() : std::nullopt);
        return IDBError { };
    }

    outValue = IDBGetResult();
    return IDBError { };
}

IDBError Z_IDBStore::getCount(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t indexIdentifier, const IDBKeyRangeData& range, uint64_t& outCount)
{
    LOG(IndexedDB, "Z_IDBStore::getCount");

    outCount = 0;

    if (indexIdentifier) {
        uint8_t scanBuf[65536];
        auto idxRecPrefix = makeKeyWithOSAndIndex(0x05, objectStoreIdentifier, indexIdentifier);
        if (Z_IDBStore_ScanPrefix(idxRecPrefix.data(), idxRecPrefix.size(), scanBuf, sizeof(scanBuf)) != 0)
            return IDBError { };

        const uint8_t* sdata = scanBuf;
        const uint8_t* send = scanBuf + sizeof(scanBuf);
        while (sdata + 4 <= send) {
            uint32_t klen = readU32(sdata, send);
            if (!klen || sdata + klen > send)
                break;

            const uint8_t* storedFullKey = sdata;
            size_t storedFullKeyLen = klen;
            sdata += klen;

            if (sdata + 4 > send)
                break;
            uint32_t vlen = readU32(sdata, send);
            sdata += vlen;

            size_t keyDataOffset = idxRecPrefix.size();
            size_t keyDataLen = storedFullKeyLen > keyDataOffset ? storedFullKeyLen - keyDataOffset : 0;
            if (!keyDataLen)
                continue;

            IDBKeyData storedKey;
            if (!deserializeIDBKeyData(storedFullKey + keyDataOffset, keyDataLen, storedKey))
                continue;

            if (!keyMatchesRange(storedKey, range))
                continue;

            outCount++;
        }
        return IDBError { };
    }

    if (!range.isExactlyOneKey()) {
        uint8_t scanBuf[65536];
        auto recPrefix = makeKeyWithOS(0x03, objectStoreIdentifier);
        if (Z_IDBStore_ScanPrefix(recPrefix.data(), recPrefix.size(), scanBuf, sizeof(scanBuf)) != 0)
            return IDBError { };

        const uint8_t* sdata = scanBuf;
        const uint8_t* send = scanBuf + sizeof(scanBuf);
        while (sdata + 4 <= send) {
            uint32_t klen = readU32(sdata, send);
            if (!klen || sdata + klen > send)
                break;
            sdata += klen;
            if (sdata + 4 > send)
                break;
            uint32_t vlen = readU32(sdata, send);
            sdata += vlen;
            outCount++;
        }
        return IDBError { };
    }

    auto keyBuffer = serializeIDBKeyData(range.lowerKey);
    if (!keyBuffer)
        return IDBError { UnknownError };

    auto span = keyBuffer->dataAsSpanForContiguousData();
    Vector<uint8_t> fullKey;
    writeU64(fullKey, m_databaseID);
    fullKey.append(0x03);
    writeU64(fullKey, objectStoreIdentifier);
    fullKey.append(span.data(), span.size());

    uint8_t* outPtr = nullptr;
    size_t outLen = 0;
    if (Z_IDBStore_Get(fullKey.data(), fullKey.size(), &outPtr, &outLen) == 0 && outPtr && outLen > 0) {
        outCount = 1;
        Z_Free_Buffer(outPtr, outLen);
    } else if (outPtr) {
        Z_Free_Buffer(outPtr, outLen);
    }

    return IDBError { };
}

IDBError Z_IDBStore::generateKeyNumber(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t& keyNumber)
{
    LOG(IndexedDB, "Z_IDBStore::generateKeyNumber");

    auto genKey = makeKeyWithOS(0x07, objectStoreIdentifier);

    uint8_t* outPtr = nullptr;
    size_t outLen = 0;
    if (Z_IDBStore_Get(genKey.data(), genKey.size(), &outPtr, &outLen) == 0 && outPtr && outLen >= 8) {
        const uint8_t* data = outPtr;
        const uint8_t* end = outPtr + outLen;
        uint64_t currentValue = readU64(data, end);
        if (currentValue + 1 > maxGeneratorValue) {
            Z_Free_Buffer(outPtr, outLen);
            return IDBError { ConstraintError, "Cannot generate new key value over 2^53 for object store operation"_s };
        }
        keyNumber = currentValue + 1;
        Z_Free_Buffer(outPtr, outLen);
    } else {
        if (outPtr)
            Z_Free_Buffer(outPtr, outLen);
        keyNumber = 1;
    }

    auto newVal = packU64(keyNumber);
    Z_IDBStore_Put(genKey.data(), genKey.size(), newVal.data(), newVal.size());

    return IDBError { };
}

IDBError Z_IDBStore::revertGeneratedKeyNumber(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, uint64_t keyNumber)
{
    LOG(IndexedDB, "Z_IDBStore::revertGeneratedKeyNumber");

    if (!keyNumber)
        return IDBError { };

    auto genKey = makeKeyWithOS(0x07, objectStoreIdentifier);
    auto newVal = packU64(keyNumber - 1);
    Z_IDBStore_Put(genKey.data(), genKey.size(), newVal.data(), newVal.size());

    return IDBError { };
}

IDBError Z_IDBStore::maybeUpdateKeyGeneratorNumber(const IDBResourceIdentifier&, uint64_t objectStoreIdentifier, double newKeyNumber)
{
    LOG(IndexedDB, "Z_IDBStore::maybeUpdateKeyGeneratorNumber");

    auto genKey = makeKeyWithOS(0x07, objectStoreIdentifier);

    uint8_t* outPtr = nullptr;
    size_t outLen = 0;
    uint64_t currentValue = 0;
    if (Z_IDBStore_Get(genKey.data(), genKey.size(), &outPtr, &outLen) == 0 && outPtr && outLen >= 8) {
        const uint8_t* data = outPtr;
        const uint8_t* end = outPtr + outLen;
        currentValue = readU64(data, end);
        Z_Free_Buffer(outPtr, outLen);
    } else if (outPtr) {
        Z_Free_Buffer(outPtr, outLen);
    }

    if (newKeyNumber <= currentValue)
        return IDBError { };

    uint64_t newVal = std::min(static_cast<uint64_t>(newKeyNumber), maxGeneratorValue);
    auto val = packU64(newVal);
    Z_IDBStore_Put(genKey.data(), genKey.size(), val.data(), val.size());

    return IDBError { };
}

struct ZCursorState {
    IDBCursorInfo info;
    Vector<IDBKeyData> keys;
    Vector<IDBKeyData> primaryKeys;
    Vector<ThreadSafeDataBuffer> values;
    int64_t currentIndex { -1 };
    bool done { false };
};

IDBError Z_IDBStore::getObjectStoreValue(uint64_t objectStoreIdentifier, const IDBKeyData& primaryKey, ThreadSafeDataBuffer& outBuffer)
{
    auto pkBuffer = serializeIDBKeyData(primaryKey);
    if (!pkBuffer)
        return IDBError { UnknownError };

    auto pkSpan = pkBuffer->dataAsSpanForContiguousData();
    Vector<uint8_t> recFullKey;
    writeU64(recFullKey, m_databaseID);
    recFullKey.append(0x03);
    writeU64(recFullKey, objectStoreIdentifier);
    recFullKey.append(pkSpan.data(), pkSpan.size());

    uint8_t* recOutPtr = nullptr;
    size_t recOutLen = 0;
    IDBError error;
    if (Z_IDBStore_Get(recFullKey.data(), recFullKey.size(), &recOutPtr, &recOutLen) == 0 && recOutPtr && recOutLen > 0) {
        const uint8_t* rdata = recOutPtr;
        const uint8_t* rend = recOutPtr + recOutLen;
        uint32_t recDataSize = readU32(rdata, rend);
        if (recDataSize && rdata + recDataSize <= rend) {
            Vector<uint8_t> dataCopy(rdata, recDataSize);
            outBuffer = ThreadSafeDataBuffer::create(WTFMove(dataCopy));
        }
        Z_Free_Buffer(recOutPtr, recOutLen);
    } else if (recOutPtr) {
        Z_Free_Buffer(recOutPtr, recOutLen);
    }

    return IDBError { };
}

static void buildCursorRecords(Vector<std::tuple<IDBKeyData, IDBKeyData, ThreadSafeDataBuffer>>& records, Vector<IDBKeyData>& keys, Vector<IDBKeyData>& primaryKeys, Vector<ThreadSafeDataBuffer>& values)
{
    for (auto& rec : records) {
        keys.append(WTFMove(std::get<0>(rec)));
        primaryKeys.append(WTFMove(std::get<1>(rec)));
        values.append(WTFMove(std::get<2>(rec)));
    }
}

IDBError Z_IDBStore::scanObjectStoreRecords(uint64_t objectStoreIdentifier, const IDBKeyRangeData& range, Vector<std::tuple<IDBKeyData, IDBKeyData, ThreadSafeDataBuffer>>& outRecords)
{
    uint8_t scanBuf[65536];
    auto recPrefix = makeKeyWithOS(0x03, objectStoreIdentifier);
    if (Z_IDBStore_ScanPrefix(recPrefix.data(), recPrefix.size(), scanBuf, sizeof(scanBuf)) != 0)
        return IDBError { };

    const uint8_t* sdata = scanBuf;
    const uint8_t* send = scanBuf + sizeof(scanBuf);

    while (sdata + 4 <= send) {
        uint32_t klen = readU32(sdata, send);
        if (!klen || sdata + klen > send)
            break;

        const uint8_t* storedFullKey = sdata;
        size_t storedFullKeyLen = klen;
        sdata += klen;

        if (sdata + 4 > send)
            break;
        uint32_t vlen = readU32(sdata, send);
        const uint8_t* vdata = sdata;
        sdata += vlen;

        size_t keyDataOffset = recPrefix.size();
        size_t keyDataLen = storedFullKeyLen > keyDataOffset ? storedFullKeyLen - keyDataOffset : 0;
        if (!keyDataLen)
            continue;

        IDBKeyData storedKey;
        if (!deserializeIDBKeyData(storedFullKey + keyDataOffset, keyDataLen, storedKey))
            continue;

        if (!keyMatchesRange(storedKey, range))
            continue;

        const uint8_t* valEnd = vdata + vlen;
        const uint8_t* valData = vdata;
        uint32_t dataSize = readU32(valData, valEnd);
        ThreadSafeDataBuffer valueBuffer;
        if (dataSize && valData + dataSize <= valEnd) {
            Vector<uint8_t> dataCopy(valData, dataSize);
            valueBuffer = ThreadSafeDataBuffer::create(WTFMove(dataCopy));
        }

        outRecords.append({ IDBKeyData(storedKey), IDBKeyData(storedKey), valueBuffer });
    }

    return IDBError { };
}

IDBError Z_IDBStore::scanIndexRecords(uint64_t objectStoreIdentifier, uint64_t indexIdentifier, const IDBKeyRangeData& range, Vector<std::tuple<IDBKeyData, IDBKeyData, ThreadSafeDataBuffer>>& outRecords)
{
    uint8_t scanBuf[65536];
    auto idxRecPrefix = makeKeyWithOSAndIndex(0x05, objectStoreIdentifier, indexIdentifier);
    if (Z_IDBStore_ScanPrefix(idxRecPrefix.data(), idxRecPrefix.size(), scanBuf, sizeof(scanBuf)) != 0)
        return IDBError { };

    const uint8_t* sdata = scanBuf;
    const uint8_t* send = scanBuf + sizeof(scanBuf);

    while (sdata + 4 <= send) {
        uint32_t klen = readU32(sdata, send);
        if (!klen || sdata + klen > send)
            break;

        const uint8_t* storedFullKey = sdata;
        size_t storedFullKeyLen = klen;
        sdata += klen;

        if (sdata + 4 > send)
            break;
        uint32_t vlen = readU32(sdata, send);
        const uint8_t* vdata = sdata;
        sdata += vlen;

        size_t keyDataOffset = idxRecPrefix.size();
        size_t keyDataLen = storedFullKeyLen > keyDataOffset ? storedFullKeyLen - keyDataOffset : 0;
        if (!keyDataLen)
            continue;

        IDBKeyData indexKey;
        if (!deserializeIDBKeyData(storedFullKey + keyDataOffset, keyDataLen, indexKey))
            continue;

        if (!keyMatchesRange(indexKey, range))
            continue;

        const uint8_t* valEnd = vdata + vlen;
        const uint8_t* valData = vdata;
        uint32_t pkSize = readU32(valData, valEnd);
        IDBKeyData primaryKey;
        if (!pkSize || !deserializeIDBKeyData(valData, pkSize, primaryKey))
            continue;

        ThreadSafeDataBuffer valueBuffer;
        outRecords.append({ WTFMove(indexKey), WTFMove(primaryKey), valueBuffer });
    }

    return IDBError { };
}

IDBError Z_IDBStore::openCursor(const IDBResourceIdentifier&, const IDBCursorInfo& info, IDBGetResult& outResult)
{
    LOG(IndexedDB, "Z_IDBStore::openCursor");

    auto* objectStoreInfo = m_databaseInfo ? m_databaseInfo->infoForExistingObjectStore(info.objectStoreIdentifier()) : nullptr;

    auto cursorState = std::make_unique<ZCursorState>();
    cursorState->info = info;

    Vector<std::tuple<IDBKeyData, IDBKeyData, ThreadSafeDataBuffer>> records;
    IDBError error;
    if (info.cursorSource() == IndexedDB::CursorSource::Index) {
        error = scanIndexRecords(info.objectStoreIdentifier(), info.sourceIdentifier(), info.range(), records);
        if (!error.isNull())
            return error;
    } else {
        error = scanObjectStoreRecords(info.sourceIdentifier(), info.range(), records);
        if (!error.isNull())
            return error;
    }

    bool isForward = info.cursorDirection() == IndexedDB::CursorDirection::Next || info.cursorDirection() == IndexedDB::CursorDirection::Nextunique;

    std::sort(records.begin(), records.end(), [](const auto& a, const auto& b) {
        return std::get<0>(a).compare(std::get<0>(b)) < 0;
    });

    if (!isForward)
        std::reverse(records.begin(), records.end());

    buildCursorRecords(records, cursorState->keys, cursorState->primaryKeys, cursorState->values);

    if (cursorState->keys.isEmpty()) {
        cursorState->done = true;
        m_cursors.set(info.identifier(), WTFMove(cursorState));
        outResult = IDBGetResult();
        return IDBError { };
    }

    cursorState->currentIndex = isForward ? 0 : static_cast<int64_t>(cursorState->keys.size()) - 1;

    if (info.cursorType() == IndexedDB::CursorType::KeyOnly) {
        outResult = IDBGetResult(cursorState->keys[cursorState->currentIndex], cursorState->primaryKeys[cursorState->currentIndex]);
    } else {
        if (cursorState->values[cursorState->currentIndex].data()) {
            outResult = IDBGetResult(cursorState->keys[cursorState->currentIndex], cursorState->primaryKeys[cursorState->currentIndex], IDBValue(cursorState->values[cursorState->currentIndex]), objectStoreInfo ? objectStoreInfo->keyPath() : std::nullopt);
        } else if (info.cursorSource() == IndexedDB::CursorSource::Index) {
            ThreadSafeDataBuffer valueBuffer;
            getObjectStoreValue(info.objectStoreIdentifier(), cursorState->primaryKeys[cursorState->currentIndex], valueBuffer);
            cursorState->values[cursorState->currentIndex] = valueBuffer;
            outResult = IDBGetResult(cursorState->keys[cursorState->currentIndex], cursorState->primaryKeys[cursorState->currentIndex], IDBValue(valueBuffer), objectStoreInfo ? objectStoreInfo->keyPath() : std::nullopt);
        } else {
            outResult = IDBGetResult(cursorState->keys[cursorState->currentIndex], cursorState->primaryKeys[cursorState->currentIndex], IDBValue(ThreadSafeDataBuffer()), objectStoreInfo ? objectStoreInfo->keyPath() : std::nullopt);
        }
    }

    m_cursors.set(info.identifier(), WTFMove(cursorState));
    return IDBError { };
}

IDBError Z_IDBStore::iterateCursor(const IDBResourceIdentifier&, const IDBResourceIdentifier& cursorIdentifier, const IDBIterateCursorData& data, IDBGetResult& outResult)
{
    LOG(IndexedDB, "Z_IDBStore::iterateCursor");

    auto cursorIt = m_cursors.find(cursorIdentifier);
    if (cursorIt == m_cursors.end())
        return IDBError { UnknownError, "Cursor not found"_s };

    auto& cursor = *cursorIt->value;
    auto* objectStoreInfo = m_databaseInfo ? m_databaseInfo->infoForExistingObjectStore(cursor.info.objectStoreIdentifier()) : nullptr;

    if (cursor.done) {
        outResult = IDBGetResult();
        return IDBError { };
    }

    bool isForward = cursor.info.cursorDirection() == IndexedDB::CursorDirection::Next || cursor.info.cursorDirection() == IndexedDB::CursorDirection::Nextunique;
    bool isUnique = cursor.info.cursorDirection() == IndexedDB::CursorDirection::Nextunique || cursor.info.cursorDirection() == IndexedDB::CursorDirection::Prevunique;

    uint64_t advanceCount = data.count ? data.count : 1;

    auto advanceOne = [&]() -> bool {
        for (uint64_t step = 0; step < advanceCount; ++step) {
            if (isForward)
                ++cursor.currentIndex;
            else
                --cursor.currentIndex;

            if (cursor.currentIndex < 0 || cursor.currentIndex >= static_cast<int64_t>(cursor.keys.size())) {
                cursor.done = true;
                return false;
            }

            if (isUnique) {
                while (cursor.currentIndex >= 0 && cursor.currentIndex < static_cast<int64_t>(cursor.keys.size())) {
                    bool duplicate = false;
                    if (isForward && cursor.currentIndex > 0)
                        duplicate = cursor.keys[cursor.currentIndex].compare(cursor.keys[cursor.currentIndex - 1]) == 0;
                    else if (!isForward && cursor.currentIndex + 1 < static_cast<int64_t>(cursor.keys.size()))
                        duplicate = cursor.keys[cursor.currentIndex].compare(cursor.keys[cursor.currentIndex + 1]) == 0;

                    if (!duplicate)
                        break;

                    if (isForward)
                        ++cursor.currentIndex;
                    else
                        --cursor.currentIndex;
                }

                if (cursor.currentIndex < 0 || cursor.currentIndex >= static_cast<int64_t>(cursor.keys.size())) {
                    cursor.done = true;
                    return false;
                }
            }
        }
        return true;
    };

    if (!advanceOne())
        return IDBError { };

    if (!data.keyData.isNull()) {
        while (!cursor.done) {
            int cmp = cursor.keys[cursor.currentIndex].compare(data.keyData);
            if ((isForward && cmp >= 0) || (!isForward && cmp <= 0))
                break;

            if (!advanceOne())
                break;
        }
    }

    if (data.primaryKeyData.isValid() && !cursor.done) {
        while (!cursor.done) {
            auto& currentKey = cursor.keys[cursor.currentIndex];
            if (currentKey.compare(data.keyData) != 0)
                break;
            int cmp = cursor.primaryKeys[cursor.currentIndex].compare(data.primaryKeyData);
            if ((isForward && cmp >= 0) || (!isForward && cmp <= 0))
                break;

            if (!advanceOne())
                break;
        }
    }

    if (cursor.done) {
        outResult = IDBGetResult();
        return IDBError { };
    }

    if (cursor.info.cursorType() == IndexedDB::CursorType::KeyOnly) {
        outResult = IDBGetResult(cursor.keys[cursor.currentIndex], cursor.primaryKeys[cursor.currentIndex]);
    } else {
        auto& valBuffer = cursor.values[cursor.currentIndex];
        if (valBuffer.data()) {
            outResult = IDBGetResult(cursor.keys[cursor.currentIndex], cursor.primaryKeys[cursor.currentIndex], IDBValue(valBuffer), objectStoreInfo ? objectStoreInfo->keyPath() : std::nullopt);
        } else if (cursor.info.cursorSource() == IndexedDB::CursorSource::Index) {
            ThreadSafeDataBuffer valueBuffer;
            getObjectStoreValue(cursor.info.objectStoreIdentifier(), cursor.primaryKeys[cursor.currentIndex], valueBuffer);
            cursor.values[cursor.currentIndex] = valueBuffer;
            outResult = IDBGetResult(cursor.keys[cursor.currentIndex], cursor.primaryKeys[cursor.currentIndex], IDBValue(valueBuffer), objectStoreInfo ? objectStoreInfo->keyPath() : std::nullopt);
        } else {
            outResult = IDBGetResult(cursor.keys[cursor.currentIndex], cursor.primaryKeys[cursor.currentIndex], IDBValue(ThreadSafeDataBuffer()), objectStoreInfo ? objectStoreInfo->keyPath() : std::nullopt);
        }
    }

    return IDBError { };
}

IDBObjectStoreInfo* Z_IDBStore::infoForObjectStore(uint64_t objectStoreIdentifier)
{
    ASSERT(m_databaseInfo);
    return m_databaseInfo->infoForExistingObjectStore(objectStoreIdentifier);
}

void Z_IDBStore::deleteBackingStore()
{
    LOG(IndexedDB, "Z_IDBStore::deleteBackingStore");
    Z_IDBStore_Clear();
    m_databaseInfo = nullptr;
    m_objectStoreInfoCache.clear();
}

void Z_IDBStore::close()
{
    LOG(IndexedDB, "Z_IDBStore::close");
    m_objectStoreInfoCache.clear();
}

} // namespace IDBServer
} // namespace WebCore
