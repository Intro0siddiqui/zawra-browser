#include "config.h"
#include "ZawraCacheBridge.h"

#include <wtf/SHA1.h>
#include <wtf/WallTime.h>
#include <wtf/Vector.h>

extern "C" {
    int32_t Z_CacheStore_Store(const uint8_t* hash_ptr, size_t hash_len, const uint8_t* data_ptr, size_t data_len);
    int32_t Z_CacheStore_Retrieve(const uint8_t* hash_ptr, size_t hash_len, uint8_t** out_ptr, size_t* out_len);
    int32_t Z_CacheStore_Delete(const uint8_t* hash_ptr, size_t hash_len);
    int32_t Z_CacheStore_Clear();
    void Z_Free_Buffer(uint8_t* ptr, size_t len);
}

namespace WebKit {
namespace NetworkCache {

void ZawraCacheBridge::storeRecord(const SHA1::Digest& keyHash, WallTime timestamp, const uint8_t* headerData, size_t headerSize, const uint8_t* bodyData, size_t bodySize)
{
    double ts = timestamp.secondsSinceEpoch().value();
    size_t totalSize = sizeof(ts) + sizeof(uint32_t) + headerSize + sizeof(uint32_t) + bodySize;
    Vector<uint8_t> buf;
    buf.reserveInitialCapacity(totalSize);

    buf.append(reinterpret_cast<const uint8_t*>(&ts), sizeof(ts));
    uint32_t hdrSz = static_cast<uint32_t>(headerSize);
    buf.append(reinterpret_cast<const uint8_t*>(&hdrSz), sizeof(hdrSz));
    if (headerSize)
        buf.append(headerData, headerSize);
    uint32_t bdySz = static_cast<uint32_t>(bodySize);
    buf.append(reinterpret_cast<const uint8_t*>(&bdySz), sizeof(bdySz));
    if (bodySize)
        buf.append(bodyData, bodySize);

    Z_CacheStore_Store(keyHash.data(), keyHash.size(), buf.data(), buf.size());
}

bool ZawraCacheBridge::retrieveRecord(const SHA1::Digest& keyHash, WallTime& timestamp, Vector<uint8_t>& header, Vector<uint8_t>& body)
{
    uint8_t* outPtr = nullptr;
    size_t outLen = 0;
    if (Z_CacheStore_Retrieve(keyHash.data(), keyHash.size(), &outPtr, &outLen) != 0 || !outPtr || !outLen) {
        if (outPtr)
            Z_Free_Buffer(outPtr, outLen);
        return false;
    }

    const uint8_t* data = outPtr;
    const uint8_t* end = outPtr + outLen;

    if (data + sizeof(double) > end) {
        Z_Free_Buffer(outPtr, outLen);
        return false;
    }
    double ts;
    memcpy(&ts, data, sizeof(double));
    data += sizeof(double);
    timestamp = WallTime::fromRawSeconds(Seconds { ts });

    if (data + sizeof(uint32_t) > end) {
        Z_Free_Buffer(outPtr, outLen);
        return false;
    }
    uint32_t hdrSz;
    memcpy(&hdrSz, data, sizeof(uint32_t));
    data += sizeof(uint32_t);
    if (data + hdrSz > end) {
        Z_Free_Buffer(outPtr, outLen);
        return false;
    }
    header.append(data, hdrSz);
    data += hdrSz;

    if (data + sizeof(uint32_t) > end) {
        Z_Free_Buffer(outPtr, outLen);
        return false;
    }
    uint32_t bdySz;
    memcpy(&bdySz, data, sizeof(uint32_t));
    data += sizeof(uint32_t);
    if (data + bdySz > end) {
        Z_Free_Buffer(outPtr, outLen);
        return false;
    }
    body.append(data, bdySz);

    Z_Free_Buffer(outPtr, outLen);
    return true;
}

void ZawraCacheBridge::removeRecord(const SHA1::Digest& keyHash)
{
    Z_CacheStore_Delete(keyHash.data(), keyHash.size());
}

void ZawraCacheBridge::clearAll()
{
    Z_CacheStore_Clear();
}

}
}
