#include "config.h"
#include "ZSWRegBridge.h"

extern "C" {
    int32_t Z_SWReg_StoreRegistration(const uint8_t* scope, uint32_t scope_len,
                                      const uint8_t* data, uint32_t data_len);
    int32_t Z_SWReg_GetRegistration(const uint8_t* scope, uint32_t scope_len,
                                    uint8_t* result_buf, uint32_t result_buf_len, uint32_t* result_written);
    int32_t Z_SWReg_DeleteRegistration(const uint8_t* scope, uint32_t scope_len);
    int32_t Z_SWReg_GetAll(uint8_t* result_buf, uint32_t result_buf_len, uint32_t* result_written);
    int32_t Z_SWReg_DeleteAll();
}

int ZSWRegBridge::storeRegistration(const uint8_t* scope, uint32_t scopeLen,
                                     const uint8_t* data, uint32_t dataLen)
{
    return Z_SWReg_StoreRegistration(scope, scopeLen, data, dataLen);
}

int ZSWRegBridge::getRegistration(const uint8_t* scope, uint32_t scopeLen,
                                   uint8_t* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten)
{
    return Z_SWReg_GetRegistration(scope, scopeLen, resultBuf, resultBufLen, resultWritten);
}

int ZSWRegBridge::deleteRegistration(const uint8_t* scope, uint32_t scopeLen)
{
    return Z_SWReg_DeleteRegistration(scope, scopeLen);
}

int ZSWRegBridge::getAll(uint8_t* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten)
{
    return Z_SWReg_GetAll(resultBuf, resultBufLen, resultWritten);
}

int ZSWRegBridge::deleteAll()
{
    return Z_SWReg_DeleteAll();
}
