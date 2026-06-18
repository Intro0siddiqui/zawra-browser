#pragma once

#include <wtf/WallTime.h>
#include <wtf/SHA1.h>
#include <wtf/Vector.h>

namespace WebKit {
namespace NetworkCache {

class ZawraCacheBridge {
public:
    static void storeRecord(const SHA1::Digest& keyHash, WallTime timestamp, const uint8_t* headerData, size_t headerSize, const uint8_t* bodyData, size_t bodySize);
    static bool retrieveRecord(const SHA1::Digest& keyHash, WallTime& timestamp, Vector<uint8_t>& header, Vector<uint8_t>& body);
    static void removeRecord(const SHA1::Digest& keyHash);
    static void clearAll();
};

}
}
