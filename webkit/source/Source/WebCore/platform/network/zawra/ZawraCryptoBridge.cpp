#include "config.h"
#include "ZawraCryptoBridge.h"

extern "C" {
    int32_t Zawra_Crypto_Encrypt(uint32_t algo, const uint8_t* key, size_t key_len, const uint8_t* iv, size_t iv_len, const uint8_t* in, size_t in_len, uint8_t* out, size_t* out_len);
    int32_t Zawra_Crypto_Decrypt(uint32_t algo, const uint8_t* key, size_t key_len, const uint8_t* iv, size_t iv_len, const uint8_t* in, size_t in_len, uint8_t* out, size_t* out_len);
}

namespace WebCore {

std::optional<Vector<uint8_t>> ZawraCryptoBridge::encrypt(Algorithm algo, const Vector<uint8_t>& key, const Vector<uint8_t>& iv, const Vector<uint8_t>& plainText)
{
    Vector<uint8_t> output(plainText.size() + 64); // Padding room
    size_t outLen = output.size();
    if (Zawra_Crypto_Encrypt(static_cast<uint32_t>(algo), key.data(), key.size(), iv.data(), iv.size(), plainText.data(), plainText.size(), output.data(), &outLen) == 0) {
        output.shrink(outLen);
        return output;
    }
    return std::nullopt;
}

std::optional<Vector<uint8_t>> ZawraCryptoBridge::decrypt(Algorithm algo, const Vector<uint8_t>& key, const Vector<uint8_t>& iv, const Vector<uint8_t>& cipherText)
{
    Vector<uint8_t> output(cipherText.size());
    size_t outLen = output.size();
    if (Zawra_Crypto_Decrypt(static_cast<uint32_t>(algo), key.data(), key.size(), iv.data(), iv.size(), cipherText.data(), cipherText.size(), output.data(), &outLen) == 0) {
        output.shrink(outLen);
        return output;
    }
    return std::nullopt;
}

}
