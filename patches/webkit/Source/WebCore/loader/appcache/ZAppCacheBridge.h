#pragma once

#include <cstdint>
#include <wtf/text/WTFString.h>

// ZAppCacheBridge - BrowserDB-backed ApplicationCache replacement.
// Routes ApplicationCache operations through BrowserDB via Rust FFI.
class ZAppCacheBridge {
public:
    static int storeManifest(uint64_t originHi, uint64_t originLo, const WTF::String& manifestUrl, const char* data, uint32_t dataLen);
    static int getManifest(uint64_t originHi, uint64_t originLo, const WTF::String& manifestUrl, char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten);
    static int storeResource(uint64_t originHi, uint64_t originLo, const WTF::String& resourceUrl, const char* data, uint32_t dataLen);
    static int getResource(uint64_t originHi, uint64_t originLo, const WTF::String& resourceUrl, char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten);
    static int deleteOrigin(uint64_t originHi, uint64_t originLo);
};
