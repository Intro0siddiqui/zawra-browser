#include "config.h"
#include "ZPCMBridge.h"
#include <wtf/text/CString.h>

extern "C" {
    int32_t Z_PCM_StoreUnattributed(const uint8_t* data, uint32_t data_len);
    int32_t Z_PCM_GetUnattributed(uint8_t* result_buf, uint32_t result_buf_len, uint32_t* result_written);
    int32_t Z_PCM_StoreAttributed(const uint8_t* data, uint32_t data_len);
    int32_t Z_PCM_GetAttributed(uint8_t* result_buf, uint32_t result_buf_len, uint32_t* result_written);
    int32_t Z_PCM_DeleteMeasurement(uint64_t id_hi, uint64_t id_lo);
}

int ZPCMBridge::storeUnattributed(const char* data, uint32_t dataLen)
{
    return Z_PCM_StoreUnattributed(reinterpret_cast<const uint8_t*>(data), dataLen);
}

int ZPCMBridge::getUnattributed(char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten)
{
    return Z_PCM_GetUnattributed(reinterpret_cast<uint8_t*>(resultBuf), resultBufLen, resultWritten);
}

int ZPCMBridge::storeAttributed(const char* data, uint32_t dataLen)
{
    return Z_PCM_StoreAttributed(reinterpret_cast<const uint8_t*>(data), dataLen);
}

int ZPCMBridge::getAttributed(char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten)
{
    return Z_PCM_GetAttributed(reinterpret_cast<uint8_t*>(resultBuf), resultBufLen, resultWritten);
}

int ZPCMBridge::deleteMeasurement(uint64_t idHi, uint64_t idLo)
{
    return Z_PCM_DeleteMeasurement(idHi, idLo);
}
