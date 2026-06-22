#pragma once

#include <cstdint>
#include <wtf/text/WTFString.h>

// ZPushBridge - BrowserDB-backed Push API replacement.
// Routes Push subscription storage operations through BrowserDB via Rust FFI.
class ZPushBridge {
public:
    static int storeSubscription(uint64_t originHi, uint64_t originLo,
                                 const uint8_t* endpoint, uint32_t endpointLen,
                                 const uint8_t* p256dh, uint32_t p256dhLen,
                                 const uint8_t* auth, uint32_t authLen);
    static int getSubscription(uint64_t originHi, uint64_t originLo,
                               char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten);
    static int deleteSubscription(uint64_t originHi, uint64_t originLo);
    static int deleteAll();
};
