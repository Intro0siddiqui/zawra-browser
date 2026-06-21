#pragma once

#include <cstdint>
#include <wtf/text/WTFString.h>

// ZITPBridge - BrowserDB-backed ITP (Intelligent Tracking Prevention) replacement.
// Routes ITP storage operations through BrowserDB via Rust FFI.
class ZITPBridge {
public:
    static int storeStatistics(uint64_t originHashHi, uint64_t originHashLo, const char* data, uint32_t dataLen);
    static int getStatistics(uint64_t originHashHi, uint64_t originHashLo,
                             char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten);
    static int deleteStatistics(uint64_t originHashHi, uint64_t originHashLo);
    static int deleteAll();
    static int getAllOrigins(char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten);

    static void hashDomain(const WTF::String& domain, uint64_t& hi, uint64_t& lo);
};
