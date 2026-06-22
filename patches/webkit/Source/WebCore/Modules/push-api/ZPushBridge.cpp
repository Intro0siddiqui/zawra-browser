#include "config.h"
#include "ZPushBridge.h"
#include <wtf/text/CString.h>

extern "C" {
    int32_t Z_Push_StoreSubscription(uint64_t origin_hi, uint64_t origin_lo,
                                     const uint8_t* endpoint, uint32_t endpoint_len,
                                     const uint8_t* p256dh, uint32_t p256dh_len,
                                     const uint8_t* auth, uint32_t auth_len);
    int32_t Z_Push_GetSubscription(uint64_t origin_hi, uint64_t origin_lo,
                                   uint8_t* result_buf, uint32_t result_buf_len, uint32_t* result_written);
    int32_t Z_Push_DeleteSubscription(uint64_t origin_hi, uint64_t origin_lo);
    int32_t Z_Push_DeleteAll();
}

int ZPushBridge::storeSubscription(uint64_t originHi, uint64_t originLo,
                                    const uint8_t* endpoint, uint32_t endpointLen,
                                    const uint8_t* p256dh, uint32_t p256dhLen,
                                    const uint8_t* auth, uint32_t authLen)
{
    return Z_Push_StoreSubscription(originHi, originLo, endpoint, endpointLen, p256dh, p256dhLen, auth, authLen);
}

int ZPushBridge::getSubscription(uint64_t originHi, uint64_t originLo,
                                  char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten)
{
    return Z_Push_GetSubscription(originHi, originLo, reinterpret_cast<uint8_t*>(resultBuf), resultBufLen, resultWritten);
}

int ZPushBridge::deleteSubscription(uint64_t originHi, uint64_t originLo)
{
    return Z_Push_DeleteSubscription(originHi, originLo);
}

int ZPushBridge::deleteAll()
{
    return Z_Push_DeleteAll();
}
