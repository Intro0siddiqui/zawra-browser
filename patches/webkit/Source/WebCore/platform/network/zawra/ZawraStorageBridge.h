#pragma once

#include <wtf/text/WTFString.h>
#include <wtf/URL.h>

namespace WebCore {

class ZawraStorageBridge {
public:
    static void hashString(const String& input, uint64_t& hi, uint64_t& lo);
    static void storeCookie(const URL& url, const String& cookieStr);
    static String getCookies(const URL& url);
    static void recordHistory(const URL& url, const String& title);
    static void incrementHistoryVisit(const URL& url);
    static void storeDataWithTTL(const String& key, const String& value, uint64_t ttl);
    static String getData(const String& key);
    static void removeData(const String& key);
    static void clearData();
    static void addBookmark(const URL& url, const String& title, const String& folder = String());
    static void removeBookmark(const URL& url);
    static String getBookmarks();
    static void deleteCookiesForDomain(const String& domain);
};

}
