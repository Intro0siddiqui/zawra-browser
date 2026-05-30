#pragma once

#include <wtf/text/WTFString.h>
#include <wtf/Vector.h>

namespace WebCore {

class ZawraCryptoBridge {
public:
    enum class Algorithm {
        AES_CBC,
        AES_CTR,
        AES_GCM,
        SHA256,
        SHA512
    };

    static std::optional<Vector<uint8_t>> encrypt(Algorithm, const Vector<uint8_t>& key, const Vector<uint8_t>& iv, const Vector<uint8_t>& plainText);
    static std::optional<Vector<uint8_t>> decrypt(Algorithm, const Vector<uint8_t>& key, const Vector<uint8_t>& iv, const Vector<uint8_t>& cipherText);
    static std::optional<Vector<uint8_t>> digest(Algorithm, const Vector<uint8_t>& data);
};

}
