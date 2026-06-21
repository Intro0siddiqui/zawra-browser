#pragma once

#include <cstdint>
#include <wtf/text/WTFString.h>

// ZWebSQLBridge - BrowserDB-backed WebSQL replacement.
// Routes WebSQL operations through BrowserDB via Rust FFI.
class ZWebSQLBridge {
public:
    static int openDatabase(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName, int version);
    static int closeDatabase(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName);
    static int execSQL(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName, const WTF::String& sql,
                      char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten);
    static int getVersion(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName);
    static int setVersion(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName, int version);
    static int deleteDatabase(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName);
};
