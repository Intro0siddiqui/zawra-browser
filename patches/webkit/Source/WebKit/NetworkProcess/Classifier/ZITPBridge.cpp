#include "config.h"
#include "ZITPBridge.h"
#include <wtf/text/CString.h>

extern "C" {
    int32_t Z_ITP_StoreStatistics(uint64_t origin_hi, uint64_t origin_lo, const uint8_t* data, uint32_t data_len);
    int32_t Z_ITP_GetStatistics(uint64_t origin_hi, uint64_t origin_lo,
        uint8_t* result_buf, uint32_t result_buf_len, uint32_t* result_written);
    int32_t Z_ITP_DeleteStatistics(uint64_t origin_hi, uint64_t origin_lo);
    int32_t Z_ITP_DeleteAll();
    int32_t Z_ITP_GetAllOrigins(uint8_t* result_buf, uint32_t result_buf_len, uint32_t* result_written);
    void Z_Hash_String(const char* input, uint64_t* out_hi, uint64_t* out_lo);
}

void ZITPBridge::hashDomain(const WTF::String& domain, uint64_t& hi, uint64_t& lo)
{
    auto utf8 = domain.utf8();
    Z_Hash_String(utf8.data(), &hi, &lo);
}

int ZITPBridge::storeStatistics(uint64_t originHashHi, uint64_t originHashLo, const char* data, uint32_t dataLen)
{
    return Z_ITP_StoreStatistics(originHashHi, originHashLo, reinterpret_cast<const uint8_t*>(data), dataLen);
}

int ZITPBridge::getStatistics(uint64_t originHashHi, uint64_t originHashLo,
    char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten)
{
    return Z_ITP_GetStatistics(originHashHi, originHashLo,
        reinterpret_cast<uint8_t*>(resultBuf), resultBufLen, resultWritten);
}

int ZITPBridge::deleteStatistics(uint64_t originHashHi, uint64_t originHashLo)
{
    return Z_ITP_DeleteStatistics(originHashHi, originHashLo);
}

int ZITPBridge::deleteAll()
{
    return Z_ITP_DeleteAll();
}

int ZITPBridge::getAllOrigins(char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten)
{
    return Z_ITP_GetAllOrigins(reinterpret_cast<uint8_t*>(resultBuf), resultBufLen, resultWritten);
}
