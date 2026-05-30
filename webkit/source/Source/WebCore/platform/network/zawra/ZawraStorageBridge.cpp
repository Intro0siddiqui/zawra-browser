#include "config.h"
#include "ZawraStorageBridge.h"
#include <wtf/text/CString.h>
#include <wtf/DateMath.h>
#include <wtf/WallTime.h>
#include <wtf/ASCIICType.h>

extern "C" {
    void Zawra_Hash_String(const char* input, uint64_t* out_hi, uint64_t* out_lo);
    int32_t Zawra_Cookie_Put(uint64_t hi, uint64_t lo, const char* name, const char* value, uint64_t expiry, uint8_t flags);
    int32_t Zawra_Cookie_GetForDomain(uint64_t hi, uint64_t lo, char* out_buf, size_t out_buf_len);
    int32_t Zawra_History_Put(uint64_t hi, uint64_t lo, const char* url, const char* title, uint64_t timestamp);
    int32_t Zawra_Bookmark_Put(uint64_t hi, uint64_t lo, const char* url, const char* title, const char* folder);
    int32_t Zawra_Bookmark_Delete(uint64_t hi, uint64_t lo);
    int32_t Zawra_Bookmark_GetAll(char* out_buf, size_t out_buf_len);
    int32_t Zawra_Cookie_DeleteForDomain(uint64_t hi, uint64_t lo);
    int32_t Zawra_LocalStorage_Put(uint64_t hi, uint64_t lo, const char* key, const char* value);
    int32_t Zawra_LocalStorage_Get(uint64_t hi, uint64_t lo, const char* key, char* out_buf, size_t out_buf_len);
    int32_t Zawra_LocalStorage_Remove(uint64_t hi, uint64_t lo, const char* key);
    int32_t Zawra_LocalStorage_Clear(uint64_t hi, uint64_t lo);
}

namespace WebCore {

void ZawraStorageBridge::hashString(const String& input, uint64_t& hi, uint64_t& lo)
{
    Zawra_Hash_String(input.utf8().data(), &hi, &lo);
}

void ZawraStorageBridge::storeCookie(const URL& url, const String& cookieStr)
{
    uint64_t hi, lo;
    hashString(url.host().toString(), hi, lo);

    auto parts = cookieStr.split(';');
    if (parts.isEmpty()) return;
    
    auto kv = parts[0].split('=');
    if (kv.size() < 2) return;
    
    String name = kv[0].trim(isASCIIWhitespace);
    String value = kv[1].trim(isASCIIWhitespace);

    Zawra_Cookie_Put(hi, lo, name.utf8().data(), value.utf8().data(), 0, 0);
}

String ZawraStorageBridge::getCookies(const URL& url)
{
    uint64_t hi, lo;
    hashString(url.host().toString(), hi, lo);

    char buf[4096];
    if (Zawra_Cookie_GetForDomain(hi, lo, buf, sizeof(buf)) == 0)
        return String::fromUTF8(buf);
    
    return String();
}

void ZawraStorageBridge::recordHistory(const URL& url, const String& title)
{
    uint64_t hi, lo;
    hashString(url.string(), hi, lo);
    
    uint64_t ts = static_cast<uint64_t>(WallTime::now().secondsSinceEpoch().value());
    Zawra_History_Put(hi, lo, url.string().utf8().data(), title.utf8().data(), ts);
}

void ZawraStorageBridge::addBookmark(const URL& url, const String& title, const String& folder)
{
    uint64_t hi, lo;
    hashString(url.string(), hi, lo);
    Zawra_Bookmark_Put(hi, lo, url.string().utf8().data(), title.utf8().data(), folder.utf8().data());
}

void ZawraStorageBridge::removeBookmark(const URL& url)
{
    uint64_t hi, lo;
    hashString(url.string(), hi, lo);
    Zawra_Bookmark_Delete(hi, lo);
}

String ZawraStorageBridge::getBookmarks()
{
    char buf[16384];
    if (Zawra_Bookmark_GetAll(buf, sizeof(buf)) == 0)
        return String::fromUTF8(buf);
    return String();
}

void ZawraStorageBridge::deleteCookiesForDomain(const String& domain)
{
    uint64_t hi, lo;
    hashString(domain, hi, lo);
    Zawra_Cookie_DeleteForDomain(hi, lo);
}

int32_t ZawraStorageBridge::localStoragePut(const String& origin, const String& key, const String& value)
{
    uint64_t hi, lo;
    hashString(origin, hi, lo);
    return Zawra_LocalStorage_Put(hi, lo, key.utf8().data(), value.utf8().data());
}

String ZawraStorageBridge::localStorageGet(const String& origin, const String& key)
{
    uint64_t hi, lo;
    hashString(origin, hi, lo);
    char buf[16384]; // 16KB max for now
    if (Zawra_LocalStorage_Get(hi, lo, key.utf8().data(), buf, sizeof(buf)) == 0)
        return String::fromUTF8(buf);
    return String();
}

int32_t ZawraStorageBridge::localStorageRemove(const String& origin, const String& key)
{
    uint64_t hi, lo;
    hashString(origin, hi, lo);
    return Zawra_LocalStorage_Remove(hi, lo, key.utf8().data());
}

int32_t ZawraStorageBridge::localStorageClear(const String& origin)
{
    uint64_t hi, lo;
    hashString(origin, hi, lo);
    return Zawra_LocalStorage_Clear(hi, lo);
}

}
