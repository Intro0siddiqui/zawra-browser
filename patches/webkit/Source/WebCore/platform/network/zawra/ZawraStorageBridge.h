#pragma once
// ZSB = ZawraStorageBridge

#include <wtf/text/WTFString.h>
#include <wtf/URL.h>
#include <wtf/HashMap.h>
#include <wtf/text/StringHash.h>

namespace WebCore {

class ZSB {
public:
    static void hashString(const String& input, uint64_t& hi, uint64_t& lo);
    static void storeCookie(const URL& url, const String& cookieStr);
    static String getCookies(const URL& url);
    static void recordHistory(const URL& url, const String& title);
    static void incrementHistoryVisit(const URL& url);
    static void storeDataWithTTL(uint64_t originHashHi, uint64_t originHashLo, const String& key, const String& value, uint64_t ttl);
    static String getData(uint64_t originHashHi, uint64_t originHashLo, const String& key);
    static HashMap<String, String> getAllData(uint64_t originHashHi, uint64_t originHashLo);
    static void removeData(uint64_t originHashHi, uint64_t originHashLo, const String& key);
    static void clearData(uint64_t originHashHi, uint64_t originHashLo);
    static void addBookmark(const URL& url, const String& title, const String& folder = String());
    static void removeBookmark(const URL& url);
    static String getBookmarks();
    static void deleteCookiesForDomain(const String& domain);
    static void deleteCookie(const URL& url, const String& name);
    static void deleteAllCookies();
};

}
