/*
 * Copyright (C) 2019 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

// Zawra: SQLite replaced by ZITPBridge (BrowserDB).

#include "config.h"
#include "ResourceLoadStatisticsStore.h"

#include "ITPThirdPartyData.h"
#include "ITPThirdPartyDataForSpecificFirstParty.h"
#include "Logging.h"
#include "PrivateClickMeasurementManager.h"
#include "PrivateClickMeasurementManagerProxy.h"
#include "StorageAccessStatus.h"
#include "WebProcessProxy.h"
#include "WebResourceLoadStatisticsStore.h"
#include "WebsiteDataStore.h"
#include "ZITPBridge.h"
#include <JavaScriptCore/ConsoleTypes.h>
#include <WebCore/CookieJar.h>
#include <WebCore/DocumentStorageAccess.h>
#include <WebCore/KeyedCoding.h>
#include <WebCore/NetworkStorageSession.h>
#include <WebCore/OrganizationStorageAccessPromptQuirk.h>
#include <WebCore/PermissionState.h>
#include <WebCore/ResourceLoadStatistics.h>
#include <WebCore/UserGestureIndicator.h>
#include <wtf/CallbackAggregator.h>
#include <wtf/CompletionHandler.h>
#include <wtf/CrossThreadCopier.h>
#include <wtf/NeverDestroyed.h>
#include <wtf/Scope.h>
#include <wtf/SuspendableWorkQueue.h>
#include <wtf/TZoneMallocInlines.h>
#include <wtf/WeakHashSet.h>
#include <wtf/text/MakeString.h>
#include <wtf/text/StringBuilder.h>

namespace WebKit {
using namespace WebCore;

#define ITP_RELEASE_LOG(fmt, ...) RELEASE_LOG(ResourceLoadStatistics, "%p - [sessionID=%" PRIu64 "] - ResourceLoadStatisticsStore::" fmt, this, m_sessionID.toUInt64(), ##__VA_ARGS__)
#define ITP_RELEASE_LOG_ERROR(fmt, ...) RELEASE_LOG_ERROR(ResourceLoadStatistics, "%p - [sessionID=%" PRIu64 "] - ResourceLoadStatisticsStore::" fmt, this, m_sessionID.toUInt64(), ##__VA_ARGS__)

static WeakHashSet<ResourceLoadStatisticsStore>& NODELETE allStores()
{
    ASSERT(!RunLoop::isMain());
    static NeverDestroyed<WeakHashSet<ResourceLoadStatisticsStore>> set;
    return set;
}

WTF_MAKE_TZONE_ALLOCATED_IMPL(ResourceLoadStatisticsStore);

ResourceLoadStatisticsStore::ResourceLoadStatisticsStore(WebResourceLoadStatisticsStore& store, SuspendableWorkQueue& workQueue, ShouldIncludeLocalhost shouldIncludeLocalhost, const String& storageDirectoryPath, PAL::SessionID sessionID)
    : DatabaseUtilities(FileSystem::pathByAppendingComponent(storageDirectoryPath, "observations.db"_s))
    , m_store(store)
    , m_workQueue(workQueue)
    , m_sessionID(sessionID)
    , m_shouldIncludeLocalhost(shouldIncludeLocalhost)
{
    ASSERT(!RunLoop::isMain());
    allStores().add(*this);
}

ResourceLoadStatisticsStore::~ResourceLoadStatisticsStore()
{
    ASSERT(!RunLoop::isMain());
    allStores().remove(*this);
}

void ResourceLoadStatisticsStore::interruptAllDatabases()
{
    ASSERT(!RunLoop::isMain());
    for (auto& store : allStores())
        store.interrupt();
}

void ResourceLoadStatisticsStore::clear(CompletionHandler<void()>&& completionHandler)
{
    ASSERT(!RunLoop::isMain());
    clearDatabaseContents();
    RunLoop::mainSingleton().dispatch(WTF::move(completionHandler));
}

bool ResourceLoadStatisticsStore::isEmpty() const
{
    ASSERT(!RunLoop::isMain());
    return true;
}

Vector<ITPThirdPartyData> ResourceLoadStatisticsStore::aggregatedThirdPartyData() const
{
    ASSERT(!RunLoop::isMain());
    return { };
}

void ResourceLoadStatisticsStore::updateCookieBlocking(CompletionHandler<void()>&& completionHandler)
{
    ASSERT(!RunLoop::isMain());
    RunLoop::mainSingleton().dispatch(WTF::move(completionHandler));
}

void ResourceLoadStatisticsStore::processStatisticsAndDataRecords(CompletionHandler<void()>&& completionHandler)
{
    ASSERT(!RunLoop::isMain());
    RunLoop::mainSingleton().dispatch(WTF::move(completionHandler));
}

void ResourceLoadStatisticsStore::cancelPendingStatisticsProcessingRequest()
{
}

void ResourceLoadStatisticsStore::mergeStatistics(Vector<ResourceLoadStatistics>&& statistics)
{
    ASSERT(!RunLoop::isMain());
    if (statistics.isEmpty())
        return;

    for (auto& statistic : statistics) {
        uint64_t hi, lo;
        ZITPBridge::hashDomain(statistic.registrableDomain.string(), hi, lo);
        StringBuilder json;
        json.append('{');
        json.append("\"domain\":\""_s, statistic.registrableDomain.string(), "\","_s);
        json.append("\"lastSeen\":"_s, statistic.lastSeen.secondsSinceEpoch().value(), ',' );
        json.append("\"hadUserInteraction\":"_s, statistic.hadUserInteraction ? "true"_s : "false"_s, ',' );
        json.append("\"grandfathered\":"_s, statistic.grandfathered ? "true"_s : "false"_s, ',' );
        json.append("\"isPrevalent\":"_s, statistic.isPrevalentResource ? "true"_s : "false"_s, ',' );
        json.append("\"isVeryPrevalent\":"_s, statistic.isVeryPrevalentResource ? "true"_s : "false"_s, ',' );
        json.append("\"dataRecordsRemoved\":"_s, statistic.dataRecordsRemoved);
        json.append('}');
        auto utf8 = json.toString().utf8();
        ZITPBridge::storeStatistics(hi, lo, utf8.data(), utf8.length());
    }
}

void ResourceLoadStatisticsStore::runIncrementalVacuumCommand()
{
}

void ResourceLoadStatisticsStore::dumpResourceLoadStatistics(CompletionHandler<void(const String&)>&& completionHandler)
{
    ASSERT(!RunLoop::isMain());
    RunLoop::mainSingleton().dispatch([completionHandler = WTF::move(completionHandler)]() mutable {
        completionHandler("\nNo stored Resource Load Statistics data.\n"_s);
    });
}

void ResourceLoadStatisticsStore::requestStorageAccessUnderOpener(DomainInNeedOfStorageAccess&&, WebCore::PageIdentifier, OpenerDomain&&, CanRequestStorageAccessWithoutUserInteraction)
{
}

void ResourceLoadStatisticsStore::removeAllStorageAccess(CompletionHandler<void()>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch(WTF::move(completionHandler));
}

HashSet<WebCore::RegistrableDomain> ResourceLoadStatisticsStore::loadWebsitesWithUserInteraction()
{
    return { };
}

void ResourceLoadStatisticsStore::grandfatherExistingWebsiteData(CompletionHandler<void()>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch(WTF::move(completionHandler));
}

void ResourceLoadStatisticsStore::setGrandfathered(const RegistrableDomain&, bool)
{
}

bool ResourceLoadStatisticsStore::isGrandfathered(const RegistrableDomain&) const
{
    return false;
}

void ResourceLoadStatisticsStore::setGrandfatheringTime(Seconds)
{
}

bool ResourceLoadStatisticsStore::isRegisteredAsSubresourceUnder(const SubResourceDomain&, const TopFrameDomain&) const
{
    return false;
}

bool ResourceLoadStatisticsStore::isRegisteredAsSubFrameUnder(const SubFrameDomain&, const TopFrameDomain&) const
{
    return false;
}

bool ResourceLoadStatisticsStore::isRegisteredAsRedirectingTo(const RedirectedFromDomain&, const RedirectedToDomain&) const
{
    return false;
}

void ResourceLoadStatisticsStore::clearPrevalentResource(const RegistrableDomain&)
{
}

bool ResourceLoadStatisticsStore::isPrevalentResource(const RegistrableDomain&) const
{
    return false;
}

bool ResourceLoadStatisticsStore::isVeryPrevalentResource(const RegistrableDomain&) const
{
    return false;
}

void ResourceLoadStatisticsStore::setPrevalentResource(const RegistrableDomain&)
{
}

void ResourceLoadStatisticsStore::setVeryPrevalentResource(const RegistrableDomain&)
{
}

void ResourceLoadStatisticsStore::setMostRecentWebPushInteractionTime(const RegistrableDomain&)
{
}

void ResourceLoadStatisticsStore::setSubframeUnderTopFrameDomain(const SubFrameDomain&, const TopFrameDomain&)
{
}

void ResourceLoadStatisticsStore::setSubresourceUnderTopFrameDomain(const SubResourceDomain&, const TopFrameDomain&)
{
}

void ResourceLoadStatisticsStore::setSubresourceUniqueRedirectTo(const SubResourceDomain&, const RedirectDomain&)
{
}

void ResourceLoadStatisticsStore::setSubresourceUniqueRedirectFrom(const SubResourceDomain&, const RedirectDomain&)
{
}

void ResourceLoadStatisticsStore::setTopFrameUniqueRedirectTo(const TopFrameDomain&, const RedirectDomain&)
{
}

void ResourceLoadStatisticsStore::setTopFrameUniqueRedirectFrom(const TopFrameDomain&, const RedirectDomain&)
{
}

void ResourceLoadStatisticsStore::setIsRunningTest(bool)
{
}

void ResourceLoadStatisticsStore::logTestingEvent(String&&)
{
}

void ResourceLoadStatisticsStore::setTimeAdvanceForTesting(Seconds)
{
}

void ResourceLoadStatisticsStore::setMaxStatisticsEntries(size_t)
{
}

void ResourceLoadStatisticsStore::setPruneEntriesDownTo(size_t)
{
}

void ResourceLoadStatisticsStore::resetParametersToDefaultValues()
{
}

bool ResourceLoadStatisticsStore::shouldSkip(const RegistrableDomain& domain) const
{
    return !(parameters().isRunningTest)
        && m_shouldIncludeLocalhost == ShouldIncludeLocalhost::No && domain.string() == "localhost"_s;
}

void ResourceLoadStatisticsStore::setShouldClassifyResourcesBeforeDataRecordsRemoval(bool)
{
}

void ResourceLoadStatisticsStore::setTimeToLiveUserInteraction(Seconds)
{
}

void ResourceLoadStatisticsStore::setMinimumTimeBetweenDataRecordsRemoval(Seconds)
{
}

void ResourceLoadStatisticsStore::setResourceLoadStatisticsDebugMode(bool enabled)
{
    m_debugModeEnabled = enabled;
}

void ResourceLoadStatisticsStore::setPrevalentResourceForDebugMode(const RegistrableDomain&)
{
}

#if ENABLE(APP_BOUND_DOMAINS)
void ResourceLoadStatisticsStore::setAppBoundDomains(HashSet<RegistrableDomain>&& domains)
{
    m_appBoundDomains = WTF::move(domains);
}
#endif

#if ENABLE(MANAGED_DOMAINS)
void ResourceLoadStatisticsStore::setManagedDomains(HashSet<RegistrableDomain>&& domains)
{
    m_managedDomains = WTF::move(domains);
}
#endif

void ResourceLoadStatisticsStore::hasStorageAccess(SubFrameDomain&&, TopFrameDomain&&, std::optional<WebCore::FrameIdentifier>, WebCore::PageIdentifier, CanRequestStorageAccessWithoutUserInteraction, CompletionHandler<void(bool)>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch([completionHandler = WTF::move(completionHandler)]() mutable {
        completionHandler(false);
    });
}

void ResourceLoadStatisticsStore::requestStorageAccess(SubFrameDomain&&, TopFrameDomain&&, WebCore::FrameIdentifier, WebCore::PageIdentifier, WebCore::StorageAccessScope, CanRequestStorageAccessWithoutUserInteraction, CompletionHandler<void(StorageAccessStatus)>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch([completionHandler = WTF::move(completionHandler)]() mutable {
        completionHandler(StorageAccessStatus::CannotRequestAccess);
    });
}

void ResourceLoadStatisticsStore::queryStorageAccessPermission(const SubFrameDomain&, const TopFrameDomain&, CompletionHandler<void(WebCore::PermissionState)>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch([completionHandler = WTF::move(completionHandler)]() mutable {
        completionHandler(WebCore::PermissionState::Denied);
    });
}

std::pair<ResourceLoadStatisticsStore::AddedRecord, std::optional<unsigned>> ResourceLoadStatisticsStore::grantStorageAccessPermission(const RegistrableDomain&, const RegistrableDomain&)
{
    return { AddedRecord::No, std::nullopt };
}

void ResourceLoadStatisticsStore::revokeStorageAccessPermission(const RegistrableDomain&)
{
}

void ResourceLoadStatisticsStore::grantStorageAccess(SubFrameDomain&&, TopFrameDomain&&, WebCore::FrameIdentifier, WebCore::PageIdentifier, WebCore::StorageAccessPromptWasShown, WebCore::StorageAccessScope, CompletionHandler<void(WebCore::StorageAccessWasGranted)>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch([completionHandler = WTF::move(completionHandler)]() mutable {
        completionHandler(WebCore::StorageAccessWasGranted::No);
    });
}

void ResourceLoadStatisticsStore::logFrameNavigation(const NavigatedToDomain&, const TopFrameDomain&, const NavigatedFromDomain&, bool, bool, Seconds, bool)
{
}

void ResourceLoadStatisticsStore::logCrossSiteLoadWithLinkDecoration(const NavigatedFromDomain&, const NavigatedToDomain&, DidFilterKnownLinkDecoration)
{
}

void ResourceLoadStatisticsStore::logUserInteraction(const TopFrameDomain&, CompletionHandler<void()>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch(WTF::move(completionHandler));
}

void ResourceLoadStatisticsStore::clearUserInteraction(const RegistrableDomain&, CompletionHandler<void()>&& completionHandler)
{
    RunLoop::mainSingleton().dispatch(WTF::move(completionHandler));
}

bool ResourceLoadStatisticsStore::hasHadUserInteraction(const RegistrableDomain&, OperatingDatesWindow)
{
    return false;
}

void ResourceLoadStatisticsStore::setLastSeen(const RegistrableDomain&, Seconds)
{
}

bool ResourceLoadStatisticsStore::isCorrectSubStatisticsCount(const RegistrableDomain&, const TopFrameDomain&)
{
    return true;
}

void ResourceLoadStatisticsStore::removeDataForDomain(const RegistrableDomain& domain)
{
    ASSERT(!RunLoop::isMain());
    uint64_t hi, lo;
    ZITPBridge::hashDomain(domain.string(), hi, lo);
    ZITPBridge::deleteStatistics(hi, lo);
}

Vector<WebCore::RegistrableDomain> ResourceLoadStatisticsStore::allDomains() const
{
    ASSERT(!RunLoop::isMain());
    return { };
}

HashMap<WebCore::RegistrableDomain, WallTime> ResourceLoadStatisticsStore::allDomainsWithLastAccessedTime() const
{
    return { };
}

HashSet<WebCore::RegistrableDomain> ResourceLoadStatisticsStore::domainsExemptFromWebsiteDataDeletion() const
{
    return { };
}

void ResourceLoadStatisticsStore::didCreateNetworkProcess()
{
}

bool ResourceLoadStatisticsStore::domainIDExistsInDatabase(int)
{
    return false;
}

bool ResourceLoadStatisticsStore::observedDomainNavigationWithLinkDecoration(int)
{
    return false;
}

std::optional<Vector<String>> ResourceLoadStatisticsStore::checkForMissingTablesInSchema()
{
    return std::nullopt;
}

void ResourceLoadStatisticsStore::includeTodayAsOperatingDateIfNecessary()
{
}

void ResourceLoadStatisticsStore::insertExpiredStatisticForTesting(const RegistrableDomain&, unsigned, bool, bool, bool)
{
}

const MemoryCompactLookupOnlyRobinHoodHashMap<String, TableAndIndexPair>& ResourceLoadStatisticsStore::expectedTableAndIndexQueries()
{
    static NeverDestroyed<MemoryCompactLookupOnlyRobinHoodHashMap<String, TableAndIndexPair>> emptyMap;
    return emptyMap;
}

std::span<const ASCIILiteral> ResourceLoadStatisticsStore::sortedTables()
{
    return { };
}

bool ResourceLoadStatisticsStore::createSchema()
{
    return true;
}

bool ResourceLoadStatisticsStore::createUniqueIndices()
{
    return true;
}

void ResourceLoadStatisticsStore::destroyStatements()
{
}

String ResourceLoadStatisticsStore::getDomainStringFromDomainID(unsigned) const
{
    return emptyString();
}

bool ResourceLoadStatisticsStore::needsUpdatedSchema()
{
    return false;
}

void ResourceLoadStatisticsStore::clearDatabaseContents()
{
    ZITPBridge::deleteAll();
}

} // namespace WebKit
