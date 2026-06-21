#pragma once

#include <cstdint>
#include <wtf/text/WTFString.h>

// ZPCMBridge - BrowserDB-backed PCM (Private Click Measurement) replacement.
// Routes PCM storage operations through BrowserDB via Rust FFI.
class ZPCMBridge {
public:
    static int storeUnattributed(const char* data, uint32_t dataLen);
    static int getUnattributed(char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten);
    static int storeAttributed(const char* data, uint32_t dataLen);
    static int getAttributed(char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten);
    static int deleteMeasurement(uint64_t idHi, uint64_t idLo);
};
