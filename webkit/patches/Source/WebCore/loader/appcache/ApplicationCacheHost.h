#pragma once

#include <wtf/CheckedRef.h>
#include <wtf/Deque.h>
#include <wtf/URL.h>
#include <wtf/Vector.h>
#include <wtf/WeakPtr.h>

namespace WebCore {

class ApplicationCache;
class ApplicationCacheGroup;
class ApplicationCacheResource;
class ApplicationCacheStorage;
class SharedBuffer;
class DOMApplicationCache;
class DocumentLoader;
class LocalFrame;
class ResourceError;
class ResourceLoader;
class ResourceRequest;
class ResourceResponse;
class SubstituteData;
class WeakPtrImplWithEventTargetData;

class ApplicationCacheHost {
    WTF_MAKE_NONCOPYABLE(ApplicationCacheHost); WTF_MAKE_FAST_ALLOCATED;
public:
    enum Status {
        UNCACHED = 0,
        IDLE = 1,
        CHECKING = 2,
        DOWNLOADING = 3,
        UPDATEREADY = 4,
        OBSOLETE = 5
    };

    struct CacheInfo {
        URL manifest;
        double creationTime;
        double updateTime;
        long long size;
    };

    struct ResourceInfo {
        URL resource;
        bool isMaster;
        bool isManifest;
        bool isFallback;
        bool isForeign;
        bool isExplicit;
        long long size;
    };

    explicit ApplicationCacheHost(DocumentLoader&) {}
    ~ApplicationCacheHost() {}

    static URL createFileURL(const String&) { return URL(); }

    void selectCacheWithoutManifest() {}
    void selectCacheWithManifest(const URL&) {}

    bool canLoadMainResource(const ResourceRequest&) { return false; }

    void maybeLoadMainResource(const ResourceRequest&, SubstituteData&) {}
    void maybeLoadMainResourceForRedirect(const ResourceRequest&, SubstituteData&) {}
    bool maybeLoadFallbackForMainResponse(const ResourceRequest&, const ResourceResponse&) { return false; }
    void mainResourceDataReceived(const SharedBuffer&, long long, bool) {}
    void finishedLoadingMainResource() {}
    void failedLoadingMainResource() {}

    WEBCORE_EXPORT bool maybeLoadResource(ResourceLoader&, const ResourceRequest&, const URL&) { return false; }
    WEBCORE_EXPORT bool maybeLoadFallbackForRedirect(ResourceLoader*, ResourceRequest&, const ResourceResponse&) { return false; }
    WEBCORE_EXPORT bool maybeLoadFallbackForResponse(ResourceLoader*, const ResourceResponse&) { return false; }
    WEBCORE_EXPORT bool maybeLoadFallbackForError(ResourceLoader*, const ResourceError&) { return false; }

    bool maybeLoadSynchronously(ResourceRequest&, ResourceError&, ResourceResponse&, RefPtr<SharedBuffer>&) { return false; }
    void maybeLoadFallbackSynchronously(const ResourceRequest&, ResourceError&, ResourceResponse&, RefPtr<SharedBuffer>&) {}

    bool canCacheInBackForwardCache() { return true; }

    Status status() const { return UNCACHED; }
    bool update() { return false; }
    bool swapCache() { return false; }
    void abort() {}

    void setDOMApplicationCache(DOMApplicationCache*) {}
    void notifyDOMApplicationCache(const AtomString&, int, int) {}

    void stopLoadingInFrame(LocalFrame&) {}

    void stopDeferringEvents() {}

    Vector<ResourceInfo> resourceList() { return { }; }
    CacheInfo applicationCacheInfo() { return { }; }

    bool shouldLoadResourceFromApplicationCache(const ResourceRequest&, ApplicationCacheResource*&) { return false; }
    bool getApplicationCacheFallbackResource(const ResourceRequest&, ApplicationCacheResource*&, ApplicationCache* = nullptr) { return false; }
};

} // namespace WebCore
