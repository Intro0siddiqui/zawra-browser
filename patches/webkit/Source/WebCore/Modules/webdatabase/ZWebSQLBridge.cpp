#include "config.h"
#include "ZWebSQLBridge.h"
#include <wtf/text/CString.h>

extern "C" {
    int32_t Z_WebSQL_Open(uint64_t hi, uint64_t lo, const char* db_name, uint32_t db_name_len, int32_t version);
    int32_t Z_WebSQL_Close(uint64_t hi, uint64_t lo, const char* db_name, uint32_t db_name_len);
    int32_t Z_WebSQL_ExecSQL(uint64_t hi, uint64_t lo, const char* db_name, uint32_t db_name_len,
        const char* sql, uint32_t sql_len, char* result_buf, uint32_t result_buf_len, uint32_t* result_written);
    int32_t Z_WebSQL_GetVersion(uint64_t hi, uint64_t lo, const char* db_name, uint32_t db_name_len);
    int32_t Z_WebSQL_SetVersion(uint64_t hi, uint64_t lo, const char* db_name, uint32_t db_name_len, int32_t version);
    int32_t Z_WebSQL_DeleteDatabase(uint64_t hi, uint64_t lo, const char* db_name, uint32_t db_name_len);
}

int ZWebSQLBridge::openDatabase(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName, int version)
{
    auto utf8 = dbName.utf8();
    return Z_WebSQL_Open(originHashHi, originHashLo, utf8.data(), utf8.length(), version);
}

int ZWebSQLBridge::closeDatabase(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName)
{
    auto utf8 = dbName.utf8();
    return Z_WebSQL_Close(originHashHi, originHashLo, utf8.data(), utf8.length());
}

int ZWebSQLBridge::execSQL(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName, const WTF::String& sql,
    char* resultBuf, uint32_t resultBufLen, uint32_t* resultWritten)
{
    auto dbUtf8 = dbName.utf8();
    auto sqlUtf8 = sql.utf8();
    return Z_WebSQL_ExecSQL(originHashHi, originHashLo, dbUtf8.data(), dbUtf8.length(),
        sqlUtf8.data(), sqlUtf8.length(), resultBuf, resultBufLen, resultWritten);
}

int ZWebSQLBridge::getVersion(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName)
{
    auto utf8 = dbName.utf8();
    return Z_WebSQL_GetVersion(originHashHi, originHashLo, utf8.data(), utf8.length());
}

int ZWebSQLBridge::setVersion(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName, int version)
{
    auto utf8 = dbName.utf8();
    return Z_WebSQL_SetVersion(originHashHi, originHashLo, utf8.data(), utf8.length(), version);
}

int ZWebSQLBridge::deleteDatabase(uint64_t originHashHi, uint64_t originHashLo, const WTF::String& dbName)
{
    auto utf8 = dbName.utf8();
    return Z_WebSQL_DeleteDatabase(originHashHi, originHashLo, utf8.data(), utf8.length());
}
