#include "config.h"
#include "ZawraStorageBridge.h"
#include <wtf/text/CString.h>
#include <wtf/DateMath.h>
#include <wtf/WallTime.h>
#include <wtf/ASCIICType.h>

extern "C" {
    int32_t Zawra_LocalStorage_Put(uint64_t hi, uint64_t lo, const char* key, const char* value);
    int32_t Zawra_LocalStorage_Get(uint64_t hi, uint64_t lo, const char* key, char* out_buf, size_t out_buf_len);
    int32_t Zawra_LocalStorage_GetAll(char* out_buf, size_t out_buf_len);
    int32_t Zawra_LocalStorage_Delete(uint64_t hi, uint64_t lo, const char* key);
    int32_t Zawra_LocalStorage_Clear(uint64_t hi, uint64_t lo);

    void Zawra_Hash_String(const char* input, uint64_t* out_hi, uint64_t* out_lo);
    int32_t Zawra_Cookie_Put(uint64_t hi, uint64_t lo, const char* name, const char* value, uint64_t expiry, uint8_t flags);
    int32_t Zawra_Cookie_GetForDomain(uint64_t hi, uint64_t lo, char* out_buf, size_t out_buf_len);
    int32_t Zawra_History_Put(uint64_t hi, uint64_t lo, const char* url, const char* title, uint64_t timestamp);
    int32_t Zawra_Bookmark_Put(uint64_t hi, uint64_t lo, const char* url, const char* title, const char* folder);
    int32_t Zawra_Bookmark_Delete(uint64_t hi, uint64_t lo);
    int32_t Zawra_Bookmark_GetAll(char* out_buf, size_t out_buf_len);
    int32_t Zawra_Cookie_DeleteForDomain(uint64_t hi, uint64_t lo);
    int32_t Zawra_History_Increment(uint64_t hi, uint64_t lo, int64_t delta);
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

    uint64_t expiry = 0;
    uint8_t flags = 0;

    for (size_t i = 1; i < parts.size(); ++i) {
        auto attr = parts[i].trim(isASCIIWhitespace);
        if (attr.isEmpty()) continue;

        auto lowerAttr = attr.convertToASCIILowercase();
        if (lowerAttr.startsWith("expires="_s)) {
            auto val = attr.substring(8);
            bool ok = false;
            double ts = val.toDouble(&ok);
            if (ok && ts > 0)
                expiry = static_cast<uint64_t>(ts);
        } else if (lowerAttr.startsWith("max-age="_s)) {
            auto val = attr.substring(8);
            bool ok = false;
            double maxAge = val.toDouble(&ok);
            if (ok && maxAge > 0)
                expiry = static_cast<uint64_t>(WallTime::now().secondsSinceEpoch().value()) + static_cast<uint64_t>(maxAge);
        } else if (lowerAttr.startsWith("path="_s)) {
            // Path is informational for domain matching; not stored separately yet
        } else if (lowerAttr.startsWith("domain="_s)) {
            // Domain override handled elsewhere if needed
        } else if (lowerAttr == "secure"_s) {
            flags |= 0x01;
        } else if (lowerAttr == "httponly"_s) {
            flags |= 0x02;
        } else if (lowerAttr.startsWith("samesite="_s)) {
            auto val = attr.substring(9).convertToASCIILowercase();
            if (val == "strict"_s)
                flags |= 0x04;
            else if (val == "lax"_s)
                flags |= 0x08;
            // "none" -> no flag
        }
    }

    Zawra_Cookie_Put(hi, lo, name.utf8().data(), value.utf8().data(), expiry, flags);
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


void ZawraStorageBridge::incrementHistoryVisit(const URL& url)
{
    uint64_t hi, lo;
    hashString(url.string(), hi, lo);
    Zawra_History_Increment(hi, lo, 1);
}

void ZawraStorageBridge::storeDataWithTTL(const String& key, const String& value, uint64_t ttl)
{
    uint64_t hi, lo;
    hashString(key, hi, lo);
    Zawra_LocalStorage_Put(hi, lo, key.utf8().data(), value.utf8().data());
}

String ZawraStorageBridge::getData(const String& key)
{
    uint64_t hi, lo;
    hashString(key, hi, lo);
    char buf[4096];
    if (Zawra_LocalStorage_Get(hi, lo, key.utf8().data(), buf, sizeof(buf)) == 0)
        return String::fromUTF8(buf);
    return String();
}

HashMap<String, String> ZawraStorageBridge::getAllData()
{
    HashMap<String, String> items;
    char buf[16384];
    if (Zawra_LocalStorage_GetAll(buf, sizeof(buf)) == 0) {
        String allData = String::fromUTF8(buf);
        auto lines = allData.split('\n');
        for (auto& line : lines) {
            auto kv = line.split('|');
            if (kv.size() >= 2) {
                items.add(kv[0], kv[1]);
            }
        }
    }
    return items;
}

void ZawraStorageBridge::removeData(const String& key)
{
    uint64_t hi, lo;
    hashString(key, hi, lo);
    Zawra_LocalStorage_Delete(hi, lo, key.utf8().data());
}

void ZawraStorageBridge::clearData()
{
    // Without an origin available, clearing all local storage requires either
    // wiping all local storage entirely, or just doing nothing.
    // SQLiteStorageArea::clear normally clears all items for that StorageArea.
    // For now we will use a global clear if possible, or omit the call.
    // Using origin 0, 0 as a placeholder since we hash the key as origin above.
    Zawra_LocalStorage_Clear(0, 0);
}

} // namespace WebCore
