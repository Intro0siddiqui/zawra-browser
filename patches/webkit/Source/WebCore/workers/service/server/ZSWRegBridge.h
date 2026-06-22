#pragma once

#include <cstdint>

// ZSWRegBridge - BrowserDB-backed Service Worker Registration replacement.
// Routes SW registration storage operations through BrowserDB via Rust FFI.
class ZSWRegBridge {
public:
    static int storeRegistration(const uint8_t* scope, uint32_t scopeLen,
                                 const uint8_t* data, uint32_t dataLen);
    static int getRegistration(const uint8_t* scope, uint32_t scopeLen,
                               uint8_t* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten);
    static int deleteRegistration(const uint8_t* scope, uint32_t scopeLen);
    static int getAll(uint8_t* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten);
    static int deleteAll();
};
