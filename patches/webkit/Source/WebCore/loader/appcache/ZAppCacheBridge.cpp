#include "config.h"
#include "ZAppCacheBridge.h"
#include <wtf/text/CString.h>

extern "C" {
    int32_t Z_AppCache_StoreManifest(uint64_t hi, uint64_t lo, const char* manifest_url, uint32_t manifest_url_len,
        const char* manifest_data, uint32_t manifest_data_len);
    int32_t Z_AppCache_GetManifest(uint64_t hi, uint64_t lo, const char* manifest_url, uint32_t manifest_url_len,
        char* result_buf, uint32_t result_buf_len, uint32_t* result_written);
    int32_t Z_AppCache_StoreResource(uint64_t hi, uint64_t lo, const char* resource_url, uint32_t resource_url_len,
        const char* resource_data, uint32_t resource_data_len);
    int32_t Z_AppCache_GetResource(uint64_t hi, uint64_t lo, const char* resource_url, uint32_t resource_url_len,
        char* result_buf, uint32_t result_buf_len, uint32_t* result_written);
    int32_t Z_AppCache_DeleteOrigin(uint64_t hi, uint64_t lo);
}

int ZAppCacheBridge::storeManifest(uint64_t originHi, uint64_t originLo, const WTF::String& manifestUrl, const char* data, uint32_t dataLen)
{
    auto utf8 = manifestUrl.utf8();
    return Z_AppCache_StoreManifest(originHi, originLo, utf8.data(), utf8.length(), data, dataLen);
}

int ZAppCacheBridge::getManifest(uint64_t originHi, uint64_t originLo, const WTF::String& manifestUrl, char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten)
{
    auto utf8 = manifestUrl.utf8();
    return Z_AppCache_GetManifest(originHi, originLo, utf8.data(), utf8.length(), resultBuf, resultBufLen, resultWritten);
}

int ZAppCacheBridge::storeResource(uint64_t originHi, uint64_t originLo, const WTF::String& resourceUrl, const char* data, uint32_t dataLen)
{
    auto utf8 = resourceUrl.utf8();
    return Z_AppCache_StoreResource(originHi, originLo, utf8.data(), utf8.length(), data, dataLen);
}

int ZAppCacheBridge::getResource(uint64_t originHi, uint64_t originLo, const WTF::String& resourceUrl, char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten)
{
    auto utf8 = resourceUrl.utf8();
    return Z_AppCache_GetResource(originHi, originLo, utf8.data(), utf8.length(), resultBuf, resultBufLen, resultWritten);
}

int ZAppCacheBridge::deleteOrigin(uint64_t originHi, uint64_t originLo)
{
    return Z_AppCache_DeleteOrigin(originHi, originLo);
}
