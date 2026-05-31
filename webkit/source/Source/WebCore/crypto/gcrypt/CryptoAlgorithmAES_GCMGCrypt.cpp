/*
 * Copyright (C) 2017 Apple Inc. All rights reserved.
 * Copyright (C) 2017 Metrological Group B.V.
 * Copyright (C) 2017 Igalia S.L.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "CryptoAlgorithmAES_GCM.h"

#if ENABLE(WEB_CRYPTO)

#include "CryptoAlgorithmAesGcmParams.h"
#include "CryptoKeyAES.h"
#include "NotImplemented.h"
#include <wtf/CryptographicUtilities.h>

extern "C" int Zawra_Crypto_Encrypt_GCM(
    const uint8_t* key_ptr, size_t key_len,
    const uint8_t* iv_ptr, size_t iv_len,
    const uint8_t* aad_ptr, size_t aad_len,
    const uint8_t* plain_ptr, size_t plain_len,
    uint8_t* out_ptr, size_t tag_len);

extern "C" int Zawra_Crypto_Decrypt_GCM(
    const uint8_t* key_ptr, size_t key_len,
    const uint8_t* iv_ptr, size_t iv_len,
    const uint8_t* aad_ptr, size_t aad_len,
    const uint8_t* cipher_ptr, size_t cipher_len,
    uint8_t* out_ptr, size_t tag_len);

namespace WebCore {

static std::optional<Vector<uint8_t>> gcryptEncrypt(const Vector<uint8_t>& key, const Vector<uint8_t>& iv, const Vector<uint8_t>& plainText, const Vector<uint8_t>& additionalData, uint8_t tagLength)
{
    Vector<uint8_t> output(plainText.size() + tagLength);
    int result = Zawra_Crypto_Encrypt_GCM(
        key.data(), key.size(),
        iv.data(), iv.size(),
        additionalData.data(), additionalData.size(),
        plainText.data(), plainText.size(),
        output.data(), tagLength);

    if (result != 0)
        return std::nullopt;

    return output;
}

static std::optional<Vector<uint8_t>> gcryptDecrypt(const Vector<uint8_t>& key, const Vector<uint8_t>& iv, const Vector<uint8_t>& cipherText, const Vector<uint8_t>& additionalData, uint8_t tagLength)
{
    if (cipherText.size() < tagLength)
        return std::nullopt;

    Vector<uint8_t> output(cipherText.size() - tagLength);
    int result = Zawra_Crypto_Decrypt_GCM(
        key.data(), key.size(),
        iv.data(), iv.size(),
        additionalData.data(), additionalData.size(),
        cipherText.data(), cipherText.size(),
        output.data(), tagLength);

    if (result != 0)
        return std::nullopt;

    return output;
}

ExceptionOr<Vector<uint8_t>> CryptoAlgorithmAES_GCM::platformEncrypt(const CryptoAlgorithmAesGcmParams& parameters, const CryptoKeyAES& key, const Vector<uint8_t>& plainText)
{
    auto output = gcryptEncrypt(key.key(), parameters.ivVector(), plainText, parameters.additionalDataVector(), parameters.tagLength.value_or(0) / 8);
    if (!output)
        return Exception { OperationError };
    return WTFMove(*output);
}

ExceptionOr<Vector<uint8_t>> CryptoAlgorithmAES_GCM::platformDecrypt(const CryptoAlgorithmAesGcmParams& parameters, const CryptoKeyAES& key, const Vector<uint8_t>& cipherText)
{
    auto output = gcryptDecrypt(key.key(), parameters.ivVector(), cipherText, parameters.additionalDataVector(), parameters.tagLength.value_or(0) / 8);
    if (!output)
        return Exception { OperationError };
    return WTFMove(*output);
}

} // namespace WebCore

#endif // ENABLE(WEB_CRYPTO)
