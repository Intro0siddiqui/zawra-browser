/*
 * Copyright (C) 2021-2023 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "NetworkProcess.h"

#if PLATFORM(COCOA)
#include "AppPrivacyReport.h" // NOLINT
#endif
#include "ArgumentCoders.h" // NOLINT
#if ENABLE(SERVICE_WORKER)
#include "BackgroundFetchState.h" // NOLINT
#endif
#include "CacheModel.h" // NOLINT
#include "Connection.h" // NOLINT
#include "DataReference.h" // NOLINT
#include "DataTaskIdentifier.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "DownloadID.h" // NOLINT
#include "DownloadManager.h" // NOLINT
#include "FormDataReference.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "LoadedWebArchive.h" // NOLINT
#include "NavigatingToAppBoundDomain.h" // NOLINT
#include "NetworkProcessConnectionParameters.h" // NOLINT
#include "NetworkProcessCreationParameters.h" // NOLINT
#include "NetworkProcessMessages.h" // NOLINT
#include "QuotaIncreaseRequestIdentifier.h" // NOLINT
#include "RemoteWorkerType.h" // NOLINT
#include "SandboxExtension.h" // NOLINT
#if ENABLE(TRACKING_PREVENTION)
#include "ShouldGrandfatherStatistics.h" // NOLINT
#endif
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebPageNetworkParameters.h" // NOLINT
#include "WebPageProxyIdentifier.h" // NOLINT
#if ENABLE(SERVICE_WORKER)
#include "WebPushMessage.h" // NOLINT
#endif
#if ENABLE(TRACKING_PREVENTION)
#include "WebResourceLoadStatisticsStore.h" // NOLINT
#endif
#include "WebsiteData.h" // NOLINT
#include "WebsiteDataFetchOption.h" // NOLINT
#include "WebsiteDataStoreParameters.h" // NOLINT
#include "WebsiteDataType.h" // NOLINT
#include <WebCore/CertificateInfo.h> // NOLINT
#include <WebCore/ClientOrigin.h> // NOLINT
#if ENABLE(TRACKING_PREVENTION)
#include <WebCore/CrossSiteNavigationDataTransfer.h> // NOLINT
#endif
#if USE(CURL)
#include <WebCore/CurlProxySettings.h> // NOLINT
#endif
#include <WebCore/HTTPCookieAcceptPolicy.h> // NOLINT
#if ENABLE(TRACKING_PREVENTION)
#include <WebCore/NetworkStorageSession.h> // NOLINT
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/NotificationData.h> // NOLINT
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/NotificationEventType.h> // NOLINT
#endif
#include <WebCore/PageIdentifier.h> // NOLINT
#include <WebCore/PrivateClickMeasurement.h> // NOLINT
#include <WebCore/ProcessIdentifier.h> // NOLINT
#if ENABLE(SERVICE_WORKER)
#include <WebCore/PushPermissionState.h> // NOLINT
#endif
#include <WebCore/RegistrableDomain.h> // NOLINT
#include <WebCore/ResourceRequest.h> // NOLINT
#include <WebCore/SecurityOriginData.h> // NOLINT
#if USE(SOUP)
#include <WebCore/SoupNetworkProxySettings.h> // NOLINT
#endif
#include <WebCore/StoredCredentialsPolicy.h> // NOLINT
#include <optional> // NOLINT
#include <pal/SessionID.h> // NOLINT
#if HAVE(NW_PROXY_CONFIG)
#include <utility> // NOLINT
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(APP_BOUND_DOMAINS)) || (ENABLE(TRACKING_PREVENTION) && ENABLE(MANAGED_DOMAINS))
#include <wtf/HashSet.h> // NOLINT
#endif
#include <wtf/MonotonicTime.h> // NOLINT
#include <wtf/OptionSet.h> // NOLINT
#include <wtf/Seconds.h> // NOLINT
#include <wtf/URLHash.h> // NOLINT
#if HAVE(NW_PROXY_CONFIG)
#include <wtf/UUID.h> // NOLINT
#endif
#include <wtf/Vector.h> // NOLINT
#include <wtf/WallTime.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void NetworkProcess::didReceiveNetworkProcessMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::NetworkProcess::InitializeNetworkProcess::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::InitializeNetworkProcess>(connection, decoder, this, &NetworkProcess::initializeNetworkProcess);
    if (decoder.messageName() == Messages::NetworkProcess::CreateNetworkConnectionToWebProcess::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::CreateNetworkConnectionToWebProcess>(connection, decoder, this, &NetworkProcess::createNetworkConnectionToWebProcess);
    if (decoder.messageName() == Messages::NetworkProcess::AddAllowedFirstPartyForCookies::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::AddAllowedFirstPartyForCookies>(connection, decoder, this, &NetworkProcess::addAllowedFirstPartyForCookies);
#if USE(SOUP)
    if (decoder.messageName() == Messages::NetworkProcess::SetIgnoreTLSErrors::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetIgnoreTLSErrors>(connection, decoder, this, &NetworkProcess::setIgnoreTLSErrors);
    if (decoder.messageName() == Messages::NetworkProcess::UserPreferredLanguagesChanged::name())
        return IPC::handleMessage<Messages::NetworkProcess::UserPreferredLanguagesChanged>(connection, decoder, this, &NetworkProcess::userPreferredLanguagesChanged);
    if (decoder.messageName() == Messages::NetworkProcess::SetNetworkProxySettings::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetNetworkProxySettings>(connection, decoder, this, &NetworkProcess::setNetworkProxySettings);
    if (decoder.messageName() == Messages::NetworkProcess::PrefetchDNS::name())
        return IPC::handleMessage<Messages::NetworkProcess::PrefetchDNS>(connection, decoder, this, &NetworkProcess::prefetchDNS);
    if (decoder.messageName() == Messages::NetworkProcess::SetPersistentCredentialStorageEnabled::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetPersistentCredentialStorageEnabled>(connection, decoder, this, &NetworkProcess::setPersistentCredentialStorageEnabled);
#endif
#if USE(CURL)
    if (decoder.messageName() == Messages::NetworkProcess::SetNetworkProxySettings::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetNetworkProxySettings>(connection, decoder, this, &NetworkProcess::setNetworkProxySettings);
#endif
    if (decoder.messageName() == Messages::NetworkProcess::AddWebsiteDataStore::name())
        return IPC::handleMessage<Messages::NetworkProcess::AddWebsiteDataStore>(connection, decoder, this, &NetworkProcess::addWebsiteDataStore);
    if (decoder.messageName() == Messages::NetworkProcess::DestroySession::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::DestroySession>(connection, decoder, this, &NetworkProcess::destroySession);
    if (decoder.messageName() == Messages::NetworkProcess::FetchWebsiteData::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::FetchWebsiteData>(connection, decoder, this, &NetworkProcess::fetchWebsiteData);
    if (decoder.messageName() == Messages::NetworkProcess::DeleteWebsiteData::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::DeleteWebsiteData>(connection, decoder, this, &NetworkProcess::deleteWebsiteData);
    if (decoder.messageName() == Messages::NetworkProcess::DeleteWebsiteDataForOrigins::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::DeleteWebsiteDataForOrigins>(connection, decoder, this, &NetworkProcess::deleteWebsiteDataForOrigins);
    if (decoder.messageName() == Messages::NetworkProcess::RenameOriginInWebsiteData::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::RenameOriginInWebsiteData>(connection, decoder, this, &NetworkProcess::renameOriginInWebsiteData);
    if (decoder.messageName() == Messages::NetworkProcess::WebsiteDataOriginDirectoryForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::WebsiteDataOriginDirectoryForTesting>(connection, decoder, this, &NetworkProcess::websiteDataOriginDirectoryForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::DownloadRequest::name())
        return IPC::handleMessage<Messages::NetworkProcess::DownloadRequest>(connection, decoder, this, &NetworkProcess::downloadRequest);
    if (decoder.messageName() == Messages::NetworkProcess::ResumeDownload::name())
        return IPC::handleMessage<Messages::NetworkProcess::ResumeDownload>(connection, decoder, this, &NetworkProcess::resumeDownload);
    if (decoder.messageName() == Messages::NetworkProcess::CancelDownload::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::CancelDownload>(connection, decoder, this, &NetworkProcess::cancelDownload);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::NetworkProcess::PublishDownloadProgress::name())
        return IPC::handleMessage<Messages::NetworkProcess::PublishDownloadProgress>(connection, decoder, this, &NetworkProcess::publishDownloadProgress);
#endif
    if (decoder.messageName() == Messages::NetworkProcess::DataTaskWithRequest::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::DataTaskWithRequest>(connection, decoder, this, &NetworkProcess::dataTaskWithRequest);
    if (decoder.messageName() == Messages::NetworkProcess::CancelDataTask::name())
        return IPC::handleMessage<Messages::NetworkProcess::CancelDataTask>(connection, decoder, this, &NetworkProcess::cancelDataTask);
    if (decoder.messageName() == Messages::NetworkProcess::ApplicationDidEnterBackground::name())
        return IPC::handleMessage<Messages::NetworkProcess::ApplicationDidEnterBackground>(connection, decoder, this, &NetworkProcess::applicationDidEnterBackground);
    if (decoder.messageName() == Messages::NetworkProcess::ApplicationWillEnterForeground::name())
        return IPC::handleMessage<Messages::NetworkProcess::ApplicationWillEnterForeground>(connection, decoder, this, &NetworkProcess::applicationWillEnterForeground);
    if (decoder.messageName() == Messages::NetworkProcess::FlushCookies::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::FlushCookies>(connection, decoder, this, &NetworkProcess::flushCookies);
    if (decoder.messageName() == Messages::NetworkProcess::AllowSpecificHTTPSCertificateForHost::name())
        return IPC::handleMessage<Messages::NetworkProcess::AllowSpecificHTTPSCertificateForHost>(connection, decoder, this, &NetworkProcess::allowSpecificHTTPSCertificateForHost);
    if (decoder.messageName() == Messages::NetworkProcess::AllowTLSCertificateChainForLocalPCMTesting::name())
        return IPC::handleMessage<Messages::NetworkProcess::AllowTLSCertificateChainForLocalPCMTesting>(connection, decoder, this, &NetworkProcess::allowTLSCertificateChainForLocalPCMTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetCacheModel::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetCacheModel>(connection, decoder, this, &NetworkProcess::setCacheModel);
    if (decoder.messageName() == Messages::NetworkProcess::PrepareToSuspend::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::PrepareToSuspend>(connection, decoder, this, &NetworkProcess::prepareToSuspend);
    if (decoder.messageName() == Messages::NetworkProcess::ProcessDidResume::name())
        return IPC::handleMessage<Messages::NetworkProcess::ProcessDidResume>(connection, decoder, this, &NetworkProcess::processDidResume);
    if (decoder.messageName() == Messages::NetworkProcess::NotifyMediaStreamingActivity::name())
        return IPC::handleMessage<Messages::NetworkProcess::NotifyMediaStreamingActivity>(connection, decoder, this, &NetworkProcess::notifyMediaStreamingActivity);
    if (decoder.messageName() == Messages::NetworkProcess::PreconnectTo::name())
        return IPC::handleMessage<Messages::NetworkProcess::PreconnectTo>(connection, decoder, this, &NetworkProcess::preconnectTo);
#if ENABLE(TRACKING_PREVENTION)
    if (decoder.messageName() == Messages::NetworkProcess::ClearPrevalentResource::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ClearPrevalentResource>(connection, decoder, this, &NetworkProcess::clearPrevalentResource);
    if (decoder.messageName() == Messages::NetworkProcess::ClearUserInteraction::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ClearUserInteraction>(connection, decoder, this, &NetworkProcess::clearUserInteraction);
    if (decoder.messageName() == Messages::NetworkProcess::DumpResourceLoadStatistics::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::DumpResourceLoadStatistics>(connection, decoder, this, &NetworkProcess::dumpResourceLoadStatistics);
    if (decoder.messageName() == Messages::NetworkProcess::SetTrackingPreventionEnabled::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetTrackingPreventionEnabled>(connection, decoder, this, &NetworkProcess::setTrackingPreventionEnabled);
    if (decoder.messageName() == Messages::NetworkProcess::SetResourceLoadStatisticsLogTestingEvent::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetResourceLoadStatisticsLogTestingEvent>(connection, decoder, this, &NetworkProcess::setResourceLoadStatisticsLogTestingEvent);
    if (decoder.messageName() == Messages::NetworkProcess::UpdatePrevalentDomainsToBlockCookiesFor::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::UpdatePrevalentDomainsToBlockCookiesFor>(connection, decoder, this, &NetworkProcess::updatePrevalentDomainsToBlockCookiesFor);
    if (decoder.messageName() == Messages::NetworkProcess::IsGrandfathered::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::IsGrandfathered>(connection, decoder, this, &NetworkProcess::isGrandfathered);
    if (decoder.messageName() == Messages::NetworkProcess::IsPrevalentResource::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::IsPrevalentResource>(connection, decoder, this, &NetworkProcess::isPrevalentResource);
    if (decoder.messageName() == Messages::NetworkProcess::IsVeryPrevalentResource::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::IsVeryPrevalentResource>(connection, decoder, this, &NetworkProcess::isVeryPrevalentResource);
    if (decoder.messageName() == Messages::NetworkProcess::SetLastSeen::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetLastSeen>(connection, decoder, this, &NetworkProcess::setLastSeen);
    if (decoder.messageName() == Messages::NetworkProcess::MergeStatisticForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::MergeStatisticForTesting>(connection, decoder, this, &NetworkProcess::mergeStatisticForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::InsertExpiredStatisticForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::InsertExpiredStatisticForTesting>(connection, decoder, this, &NetworkProcess::insertExpiredStatisticForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetPrevalentResource::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetPrevalentResource>(connection, decoder, this, &NetworkProcess::setPrevalentResource);
    if (decoder.messageName() == Messages::NetworkProcess::SetPrevalentResourceForDebugMode::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetPrevalentResourceForDebugMode>(connection, decoder, this, &NetworkProcess::setPrevalentResourceForDebugMode);
    if (decoder.messageName() == Messages::NetworkProcess::IsResourceLoadStatisticsEphemeral::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::IsResourceLoadStatisticsEphemeral>(connection, decoder, this, &NetworkProcess::isResourceLoadStatisticsEphemeral);
    if (decoder.messageName() == Messages::NetworkProcess::HadUserInteraction::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::HadUserInteraction>(connection, decoder, this, &NetworkProcess::hadUserInteraction);
    if (decoder.messageName() == Messages::NetworkProcess::IsRelationshipOnlyInDatabaseOnce::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::IsRelationshipOnlyInDatabaseOnce>(connection, decoder, this, &NetworkProcess::isRelationshipOnlyInDatabaseOnce);
    if (decoder.messageName() == Messages::NetworkProcess::HasLocalStorage::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::HasLocalStorage>(connection, decoder, this, &NetworkProcess::hasLocalStorage);
    if (decoder.messageName() == Messages::NetworkProcess::GetAllStorageAccessEntries::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::GetAllStorageAccessEntries>(connection, decoder, this, &NetworkProcess::getAllStorageAccessEntries);
    if (decoder.messageName() == Messages::NetworkProcess::IsRegisteredAsRedirectingTo::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::IsRegisteredAsRedirectingTo>(connection, decoder, this, &NetworkProcess::isRegisteredAsRedirectingTo);
    if (decoder.messageName() == Messages::NetworkProcess::IsRegisteredAsSubFrameUnder::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::IsRegisteredAsSubFrameUnder>(connection, decoder, this, &NetworkProcess::isRegisteredAsSubFrameUnder);
    if (decoder.messageName() == Messages::NetworkProcess::IsRegisteredAsSubresourceUnder::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::IsRegisteredAsSubresourceUnder>(connection, decoder, this, &NetworkProcess::isRegisteredAsSubresourceUnder);
    if (decoder.messageName() == Messages::NetworkProcess::DomainIDExistsInDatabase::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::DomainIDExistsInDatabase>(connection, decoder, this, &NetworkProcess::domainIDExistsInDatabase);
    if (decoder.messageName() == Messages::NetworkProcess::LogFrameNavigation::name())
        return IPC::handleMessage<Messages::NetworkProcess::LogFrameNavigation>(connection, decoder, this, &NetworkProcess::logFrameNavigation);
    if (decoder.messageName() == Messages::NetworkProcess::LogUserInteraction::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::LogUserInteraction>(connection, decoder, this, &NetworkProcess::logUserInteraction);
    if (decoder.messageName() == Messages::NetworkProcess::ResetParametersToDefaultValues::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ResetParametersToDefaultValues>(connection, decoder, this, &NetworkProcess::resetParametersToDefaultValues);
    if (decoder.messageName() == Messages::NetworkProcess::ScheduleClearInMemoryAndPersistent::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ScheduleClearInMemoryAndPersistent>(connection, decoder, this, &NetworkProcess::scheduleClearInMemoryAndPersistent);
    if (decoder.messageName() == Messages::NetworkProcess::ScheduleCookieBlockingUpdate::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ScheduleCookieBlockingUpdate>(connection, decoder, this, &NetworkProcess::scheduleCookieBlockingUpdate);
    if (decoder.messageName() == Messages::NetworkProcess::ScheduleStatisticsAndDataRecordsProcessing::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ScheduleStatisticsAndDataRecordsProcessing>(connection, decoder, this, &NetworkProcess::scheduleStatisticsAndDataRecordsProcessing);
    if (decoder.messageName() == Messages::NetworkProcess::StatisticsDatabaseHasAllTables::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::StatisticsDatabaseHasAllTables>(connection, decoder, this, &NetworkProcess::statisticsDatabaseHasAllTables);
    if (decoder.messageName() == Messages::NetworkProcess::SetCacheMaxAgeCapForPrevalentResources::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetCacheMaxAgeCapForPrevalentResources>(connection, decoder, this, &NetworkProcess::setCacheMaxAgeCapForPrevalentResources);
    if (decoder.messageName() == Messages::NetworkProcess::SetGrandfathered::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetGrandfathered>(connection, decoder, this, &NetworkProcess::setGrandfathered);
    if (decoder.messageName() == Messages::NetworkProcess::GetResourceLoadStatisticsDataSummary::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::GetResourceLoadStatisticsDataSummary>(connection, decoder, this, &NetworkProcess::getResourceLoadStatisticsDataSummary);
    if (decoder.messageName() == Messages::NetworkProcess::SetGrandfatheringTime::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetGrandfatheringTime>(connection, decoder, this, &NetworkProcess::setGrandfatheringTime);
    if (decoder.messageName() == Messages::NetworkProcess::SetMaxStatisticsEntries::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetMaxStatisticsEntries>(connection, decoder, this, &NetworkProcess::setMaxStatisticsEntries);
    if (decoder.messageName() == Messages::NetworkProcess::SetMinimumTimeBetweenDataRecordsRemoval::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetMinimumTimeBetweenDataRecordsRemoval>(connection, decoder, this, &NetworkProcess::setMinimumTimeBetweenDataRecordsRemoval);
    if (decoder.messageName() == Messages::NetworkProcess::SetPruneEntriesDownTo::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetPruneEntriesDownTo>(connection, decoder, this, &NetworkProcess::setPruneEntriesDownTo);
    if (decoder.messageName() == Messages::NetworkProcess::SetShouldClassifyResourcesBeforeDataRecordsRemoval::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetShouldClassifyResourcesBeforeDataRecordsRemoval>(connection, decoder, this, &NetworkProcess::setShouldClassifyResourcesBeforeDataRecordsRemoval);
    if (decoder.messageName() == Messages::NetworkProcess::SetNotifyPagesWhenDataRecordsWereScanned::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetNotifyPagesWhenDataRecordsWereScanned>(connection, decoder, this, &NetworkProcess::setNotifyPagesWhenDataRecordsWereScanned);
    if (decoder.messageName() == Messages::NetworkProcess::SetResourceLoadStatisticsTimeAdvanceForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetResourceLoadStatisticsTimeAdvanceForTesting>(connection, decoder, this, &NetworkProcess::setResourceLoadStatisticsTimeAdvanceForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetIsRunningResourceLoadStatisticsTest::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetIsRunningResourceLoadStatisticsTest>(connection, decoder, this, &NetworkProcess::setIsRunningResourceLoadStatisticsTest);
    if (decoder.messageName() == Messages::NetworkProcess::SetResourceLoadStatisticsDebugMode::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetResourceLoadStatisticsDebugMode>(connection, decoder, this, &NetworkProcess::setResourceLoadStatisticsDebugMode);
    if (decoder.messageName() == Messages::NetworkProcess::SetVeryPrevalentResource::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetVeryPrevalentResource>(connection, decoder, this, &NetworkProcess::setVeryPrevalentResource);
    if (decoder.messageName() == Messages::NetworkProcess::SetSubframeUnderTopFrameDomain::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetSubframeUnderTopFrameDomain>(connection, decoder, this, &NetworkProcess::setSubframeUnderTopFrameDomain);
    if (decoder.messageName() == Messages::NetworkProcess::SetSubresourceUnderTopFrameDomain::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetSubresourceUnderTopFrameDomain>(connection, decoder, this, &NetworkProcess::setSubresourceUnderTopFrameDomain);
    if (decoder.messageName() == Messages::NetworkProcess::SetSubresourceUniqueRedirectTo::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetSubresourceUniqueRedirectTo>(connection, decoder, this, &NetworkProcess::setSubresourceUniqueRedirectTo);
    if (decoder.messageName() == Messages::NetworkProcess::SetSubresourceUniqueRedirectFrom::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetSubresourceUniqueRedirectFrom>(connection, decoder, this, &NetworkProcess::setSubresourceUniqueRedirectFrom);
    if (decoder.messageName() == Messages::NetworkProcess::SetTimeToLiveUserInteraction::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetTimeToLiveUserInteraction>(connection, decoder, this, &NetworkProcess::setTimeToLiveUserInteraction);
    if (decoder.messageName() == Messages::NetworkProcess::SetTopFrameUniqueRedirectTo::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetTopFrameUniqueRedirectTo>(connection, decoder, this, &NetworkProcess::setTopFrameUniqueRedirectTo);
    if (decoder.messageName() == Messages::NetworkProcess::SetTopFrameUniqueRedirectFrom::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetTopFrameUniqueRedirectFrom>(connection, decoder, this, &NetworkProcess::setTopFrameUniqueRedirectFrom);
    if (decoder.messageName() == Messages::NetworkProcess::ResetCacheMaxAgeCapForPrevalentResources::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ResetCacheMaxAgeCapForPrevalentResources>(connection, decoder, this, &NetworkProcess::resetCacheMaxAgeCapForPrevalentResources);
    if (decoder.messageName() == Messages::NetworkProcess::DidCommitCrossSiteLoadWithDataTransfer::name())
        return IPC::handleMessage<Messages::NetworkProcess::DidCommitCrossSiteLoadWithDataTransfer>(connection, decoder, this, &NetworkProcess::didCommitCrossSiteLoadWithDataTransfer);
    if (decoder.messageName() == Messages::NetworkProcess::SetCrossSiteLoadWithLinkDecorationForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetCrossSiteLoadWithLinkDecorationForTesting>(connection, decoder, this, &NetworkProcess::setCrossSiteLoadWithLinkDecorationForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::ResetCrossSiteLoadsWithLinkDecorationForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ResetCrossSiteLoadsWithLinkDecorationForTesting>(connection, decoder, this, &NetworkProcess::resetCrossSiteLoadsWithLinkDecorationForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::DeleteCookiesForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::DeleteCookiesForTesting>(connection, decoder, this, &NetworkProcess::deleteCookiesForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::HasIsolatedSession::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::HasIsolatedSession>(connection, decoder, this, &NetworkProcess::hasIsolatedSession);
    if (decoder.messageName() == Messages::NetworkProcess::CloseITPDatabase::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::CloseITPDatabase>(connection, decoder, this, &NetworkProcess::closeITPDatabase);
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(APP_BOUND_DOMAINS))
    if (decoder.messageName() == Messages::NetworkProcess::SetAppBoundDomainsForResourceLoadStatistics::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetAppBoundDomainsForResourceLoadStatistics>(connection, decoder, this, &NetworkProcess::setAppBoundDomainsForResourceLoadStatistics);
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(MANAGED_DOMAINS))
    if (decoder.messageName() == Messages::NetworkProcess::SetManagedDomainsForResourceLoadStatistics::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetManagedDomainsForResourceLoadStatistics>(connection, decoder, this, &NetworkProcess::setManagedDomainsForResourceLoadStatistics);
#endif
#if ENABLE(TRACKING_PREVENTION)
    if (decoder.messageName() == Messages::NetworkProcess::SetShouldDowngradeReferrerForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetShouldDowngradeReferrerForTesting>(connection, decoder, this, &NetworkProcess::setShouldDowngradeReferrerForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetThirdPartyCookieBlockingMode::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetThirdPartyCookieBlockingMode>(connection, decoder, this, &NetworkProcess::setThirdPartyCookieBlockingMode);
    if (decoder.messageName() == Messages::NetworkProcess::SetShouldEnbleSameSiteStrictEnforcementForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetShouldEnbleSameSiteStrictEnforcementForTesting>(connection, decoder, this, &NetworkProcess::setShouldEnbleSameSiteStrictEnforcementForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetFirstPartyWebsiteDataRemovalModeForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetFirstPartyWebsiteDataRemovalModeForTesting>(connection, decoder, this, &NetworkProcess::setFirstPartyWebsiteDataRemovalModeForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetToSameSiteStrictCookiesForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetToSameSiteStrictCookiesForTesting>(connection, decoder, this, &NetworkProcess::setToSameSiteStrictCookiesForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetFirstPartyHostCNAMEDomainForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetFirstPartyHostCNAMEDomainForTesting>(connection, decoder, this, &NetworkProcess::setFirstPartyHostCNAMEDomainForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetThirdPartyCNAMEDomainForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetThirdPartyCNAMEDomainForTesting>(connection, decoder, this, &NetworkProcess::setThirdPartyCNAMEDomainForTesting);
#endif
    if (decoder.messageName() == Messages::NetworkProcess::SetPrivateClickMeasurementDebugMode::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetPrivateClickMeasurementDebugMode>(connection, decoder, this, &NetworkProcess::setPrivateClickMeasurementDebugMode);
    if (decoder.messageName() == Messages::NetworkProcess::SetBlobRegistryTopOriginPartitioningEnabled::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetBlobRegistryTopOriginPartitioningEnabled>(connection, decoder, this, &NetworkProcess::setBlobRegistryTopOriginPartitioningEnabled);
    if (decoder.messageName() == Messages::NetworkProcess::SetSessionIsControlledByAutomation::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetSessionIsControlledByAutomation>(connection, decoder, this, &NetworkProcess::setSessionIsControlledByAutomation);
    if (decoder.messageName() == Messages::NetworkProcess::RegisterURLSchemeAsSecure::name())
        return IPC::handleMessage<Messages::NetworkProcess::RegisterURLSchemeAsSecure>(connection, decoder, this, &NetworkProcess::registerURLSchemeAsSecure);
    if (decoder.messageName() == Messages::NetworkProcess::RegisterURLSchemeAsBypassingContentSecurityPolicy::name())
        return IPC::handleMessage<Messages::NetworkProcess::RegisterURLSchemeAsBypassingContentSecurityPolicy>(connection, decoder, this, &NetworkProcess::registerURLSchemeAsBypassingContentSecurityPolicy);
    if (decoder.messageName() == Messages::NetworkProcess::RegisterURLSchemeAsLocal::name())
        return IPC::handleMessage<Messages::NetworkProcess::RegisterURLSchemeAsLocal>(connection, decoder, this, &NetworkProcess::registerURLSchemeAsLocal);
    if (decoder.messageName() == Messages::NetworkProcess::RegisterURLSchemeAsNoAccess::name())
        return IPC::handleMessage<Messages::NetworkProcess::RegisterURLSchemeAsNoAccess>(connection, decoder, this, &NetworkProcess::registerURLSchemeAsNoAccess);
    if (decoder.messageName() == Messages::NetworkProcess::SyncLocalStorage::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SyncLocalStorage>(connection, decoder, this, &NetworkProcess::syncLocalStorage);
    if (decoder.messageName() == Messages::NetworkProcess::StoreServiceWorkerRegistrations::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::StoreServiceWorkerRegistrations>(connection, decoder, this, &NetworkProcess::storeServiceWorkerRegistrations);
    if (decoder.messageName() == Messages::NetworkProcess::StorePrivateClickMeasurement::name())
        return IPC::handleMessage<Messages::NetworkProcess::StorePrivateClickMeasurement>(connection, decoder, this, &NetworkProcess::storePrivateClickMeasurement);
    if (decoder.messageName() == Messages::NetworkProcess::DumpPrivateClickMeasurement::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::DumpPrivateClickMeasurement>(connection, decoder, this, &NetworkProcess::dumpPrivateClickMeasurement);
    if (decoder.messageName() == Messages::NetworkProcess::ClearPrivateClickMeasurement::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ClearPrivateClickMeasurement>(connection, decoder, this, &NetworkProcess::clearPrivateClickMeasurement);
    if (decoder.messageName() == Messages::NetworkProcess::SetPrivateClickMeasurementOverrideTimerForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetPrivateClickMeasurementOverrideTimerForTesting>(connection, decoder, this, &NetworkProcess::setPrivateClickMeasurementOverrideTimerForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::MarkAttributedPrivateClickMeasurementsAsExpiredForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::MarkAttributedPrivateClickMeasurementsAsExpiredForTesting>(connection, decoder, this, &NetworkProcess::markAttributedPrivateClickMeasurementsAsExpiredForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetPrivateClickMeasurementEphemeralMeasurementForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetPrivateClickMeasurementEphemeralMeasurementForTesting>(connection, decoder, this, &NetworkProcess::setPrivateClickMeasurementEphemeralMeasurementForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SimulatePrivateClickMeasurementSessionRestart::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SimulatePrivateClickMeasurementSessionRestart>(connection, decoder, this, &NetworkProcess::simulatePrivateClickMeasurementSessionRestart);
    if (decoder.messageName() == Messages::NetworkProcess::SetPrivateClickMeasurementTokenPublicKeyURLForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetPrivateClickMeasurementTokenPublicKeyURLForTesting>(connection, decoder, this, &NetworkProcess::setPrivateClickMeasurementTokenPublicKeyURLForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetPrivateClickMeasurementTokenSignatureURLForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetPrivateClickMeasurementTokenSignatureURLForTesting>(connection, decoder, this, &NetworkProcess::setPrivateClickMeasurementTokenSignatureURLForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetPrivateClickMeasurementAttributionReportURLsForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetPrivateClickMeasurementAttributionReportURLsForTesting>(connection, decoder, this, &NetworkProcess::setPrivateClickMeasurementAttributionReportURLsForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::MarkPrivateClickMeasurementsAsExpiredForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::MarkPrivateClickMeasurementsAsExpiredForTesting>(connection, decoder, this, &NetworkProcess::markPrivateClickMeasurementsAsExpiredForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetPCMFraudPreventionValuesForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetPCMFraudPreventionValuesForTesting>(connection, decoder, this, &NetworkProcess::setPCMFraudPreventionValuesForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::SetPrivateClickMeasurementAppBundleIDForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetPrivateClickMeasurementAppBundleIDForTesting>(connection, decoder, this, &NetworkProcess::setPrivateClickMeasurementAppBundleIDForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::ClosePCMDatabase::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ClosePCMDatabase>(connection, decoder, this, &NetworkProcess::closePCMDatabase);
    if (decoder.messageName() == Messages::NetworkProcess::ResetQuota::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ResetQuota>(connection, decoder, this, &NetworkProcess::resetQuota);
#if PLATFORM(IOS_FAMILY)
    if (decoder.messageName() == Messages::NetworkProcess::SetBackupExclusionPeriodForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetBackupExclusionPeriodForTesting>(connection, decoder, this, &NetworkProcess::setBackupExclusionPeriodForTesting);
#endif
    if (decoder.messageName() == Messages::NetworkProcess::ResetStoragePersistedState::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ResetStoragePersistedState>(connection, decoder, this, &NetworkProcess::resetStoragePersistedState);
    if (decoder.messageName() == Messages::NetworkProcess::CloneSessionStorageForWebPage::name())
        return IPC::handleMessage<Messages::NetworkProcess::CloneSessionStorageForWebPage>(connection, decoder, this, &NetworkProcess::cloneSessionStorageForWebPage);
    if (decoder.messageName() == Messages::NetworkProcess::DidIncreaseQuota::name())
        return IPC::handleMessage<Messages::NetworkProcess::DidIncreaseQuota>(connection, decoder, this, &NetworkProcess::didIncreaseQuota);
#if ENABLE(APP_BOUND_DOMAINS)
    if (decoder.messageName() == Messages::NetworkProcess::HasAppBoundSession::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::HasAppBoundSession>(connection, decoder, this, &NetworkProcess::hasAppBoundSession);
    if (decoder.messageName() == Messages::NetworkProcess::ClearAppBoundSession::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ClearAppBoundSession>(connection, decoder, this, &NetworkProcess::clearAppBoundSession);
#endif
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
    if (decoder.messageName() == Messages::NetworkProcess::DisableServiceWorkerEntitlement::name())
        return IPC::handleMessage<Messages::NetworkProcess::DisableServiceWorkerEntitlement>(connection, decoder, this, &NetworkProcess::disableServiceWorkerEntitlement);
    if (decoder.messageName() == Messages::NetworkProcess::ClearServiceWorkerEntitlementOverride::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ClearServiceWorkerEntitlementOverride>(connection, decoder, this, &NetworkProcess::clearServiceWorkerEntitlementOverride);
#endif
    if (decoder.messageName() == Messages::NetworkProcess::UpdateBundleIdentifier::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::UpdateBundleIdentifier>(connection, decoder, this, &NetworkProcess::updateBundleIdentifier);
    if (decoder.messageName() == Messages::NetworkProcess::ClearBundleIdentifier::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ClearBundleIdentifier>(connection, decoder, this, &NetworkProcess::clearBundleIdentifier);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::NetworkProcess::AppPrivacyReportTestingData::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::AppPrivacyReportTestingData>(connection, decoder, this, &NetworkProcess::appPrivacyReportTestingData);
    if (decoder.messageName() == Messages::NetworkProcess::ClearAppPrivacyReportTestingData::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ClearAppPrivacyReportTestingData>(connection, decoder, this, &NetworkProcess::clearAppPrivacyReportTestingData);
#endif
    if (decoder.messageName() == Messages::NetworkProcess::AddWebPageNetworkParameters::name())
        return IPC::handleMessage<Messages::NetworkProcess::AddWebPageNetworkParameters>(connection, decoder, this, &NetworkProcess::addWebPageNetworkParameters);
    if (decoder.messageName() == Messages::NetworkProcess::RemoveWebPageNetworkParameters::name())
        return IPC::handleMessage<Messages::NetworkProcess::RemoveWebPageNetworkParameters>(connection, decoder, this, &NetworkProcess::removeWebPageNetworkParameters);
    if (decoder.messageName() == Messages::NetworkProcess::CountNonDefaultSessionSets::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::CountNonDefaultSessionSets>(connection, decoder, this, &NetworkProcess::countNonDefaultSessionSets);
#if ENABLE(CFPREFS_DIRECT_MODE)
    if (decoder.messageName() == Messages::NetworkProcess::NotifyPreferencesChanged::name())
        return IPC::handleMessage<Messages::NetworkProcess::NotifyPreferencesChanged>(connection, decoder, this, &NetworkProcess::notifyPreferencesChanged);
#endif
    if (decoder.messageName() == Messages::NetworkProcess::TerminateRemoteWorkerContextConnectionWhenPossible::name())
        return IPC::handleMessage<Messages::NetworkProcess::TerminateRemoteWorkerContextConnectionWhenPossible>(connection, decoder, this, &NetworkProcess::terminateRemoteWorkerContextConnectionWhenPossible);
#if ENABLE(SERVICE_WORKER)
    if (decoder.messageName() == Messages::NetworkProcess::GetPendingPushMessages::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::GetPendingPushMessages>(connection, decoder, this, &NetworkProcess::getPendingPushMessages);
    if (decoder.messageName() == Messages::NetworkProcess::ProcessPushMessage::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ProcessPushMessage>(connection, decoder, this, &NetworkProcess::processPushMessage);
    if (decoder.messageName() == Messages::NetworkProcess::ProcessNotificationEvent::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ProcessNotificationEvent>(connection, decoder, this, &NetworkProcess::processNotificationEvent);
    if (decoder.messageName() == Messages::NetworkProcess::GetAllBackgroundFetchIdentifiers::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::GetAllBackgroundFetchIdentifiers>(connection, decoder, this, &NetworkProcess::getAllBackgroundFetchIdentifiers);
    if (decoder.messageName() == Messages::NetworkProcess::GetBackgroundFetchState::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::GetBackgroundFetchState>(connection, decoder, this, &NetworkProcess::getBackgroundFetchState);
    if (decoder.messageName() == Messages::NetworkProcess::AbortBackgroundFetch::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::AbortBackgroundFetch>(connection, decoder, this, &NetworkProcess::abortBackgroundFetch);
    if (decoder.messageName() == Messages::NetworkProcess::PauseBackgroundFetch::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::PauseBackgroundFetch>(connection, decoder, this, &NetworkProcess::pauseBackgroundFetch);
    if (decoder.messageName() == Messages::NetworkProcess::ResumeBackgroundFetch::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ResumeBackgroundFetch>(connection, decoder, this, &NetworkProcess::resumeBackgroundFetch);
    if (decoder.messageName() == Messages::NetworkProcess::ClickBackgroundFetch::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::ClickBackgroundFetch>(connection, decoder, this, &NetworkProcess::clickBackgroundFetch);
#endif
    if (decoder.messageName() == Messages::NetworkProcess::SetPushAndNotificationsEnabledForOrigin::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::SetPushAndNotificationsEnabledForOrigin>(connection, decoder, this, &NetworkProcess::setPushAndNotificationsEnabledForOrigin);
    if (decoder.messageName() == Messages::NetworkProcess::DeletePushAndNotificationRegistration::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::DeletePushAndNotificationRegistration>(connection, decoder, this, &NetworkProcess::deletePushAndNotificationRegistration);
    if (decoder.messageName() == Messages::NetworkProcess::GetOriginsWithPushAndNotificationPermissions::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::GetOriginsWithPushAndNotificationPermissions>(connection, decoder, this, &NetworkProcess::getOriginsWithPushAndNotificationPermissions);
    if (decoder.messageName() == Messages::NetworkProcess::HasPushSubscriptionForTesting::name())
        return IPC::handleMessageAsync<Messages::NetworkProcess::HasPushSubscriptionForTesting>(connection, decoder, this, &NetworkProcess::hasPushSubscriptionForTesting);
#if ENABLE(INSPECTOR_NETWORK_THROTTLING)
    if (decoder.messageName() == Messages::NetworkProcess::SetEmulatedConditions::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetEmulatedConditions>(connection, decoder, this, &NetworkProcess::setEmulatedConditions);
#endif
#if HAVE(NW_PROXY_CONFIG)
    if (decoder.messageName() == Messages::NetworkProcess::ClearProxyConfigData::name())
        return IPC::handleMessage<Messages::NetworkProcess::ClearProxyConfigData>(connection, decoder, this, &NetworkProcess::clearProxyConfigData);
    if (decoder.messageName() == Messages::NetworkProcess::SetProxyConfigData::name())
        return IPC::handleMessage<Messages::NetworkProcess::SetProxyConfigData>(connection, decoder, this, &NetworkProcess::setProxyConfigData);
#endif
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool NetworkProcess::didReceiveSyncNetworkProcessMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::NetworkProcess::SetAllowsAnySSLCertificateForWebSocket::name())
        return IPC::handleMessageSynchronous<Messages::NetworkProcess::SetAllowsAnySSLCertificateForWebSocket>(connection, decoder, replyEncoder, this, &NetworkProcess::setAllowsAnySSLCertificateForWebSocket);
    if (decoder.messageName() == Messages::NetworkProcess::SetCacheModelSynchronouslyForTesting::name())
        return IPC::handleMessageSynchronous<Messages::NetworkProcess::SetCacheModelSynchronouslyForTesting>(connection, decoder, replyEncoder, this, &NetworkProcess::setCacheModelSynchronouslyForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::ProcessWillSuspendImminentlyForTestingSync::name())
        return IPC::handleMessageSynchronous<Messages::NetworkProcess::ProcessWillSuspendImminentlyForTestingSync>(connection, decoder, replyEncoder, this, &NetworkProcess::processWillSuspendImminentlyForTestingSync);
    if (decoder.messageName() == Messages::NetworkProcess::SetServiceWorkerFetchTimeoutForTesting::name())
        return IPC::handleMessageSynchronous<Messages::NetworkProcess::SetServiceWorkerFetchTimeoutForTesting>(connection, decoder, replyEncoder, this, &NetworkProcess::setServiceWorkerFetchTimeoutForTesting);
    if (decoder.messageName() == Messages::NetworkProcess::ResetServiceWorkerFetchTimeoutForTesting::name())
        return IPC::handleMessageSynchronous<Messages::NetworkProcess::ResetServiceWorkerFetchTimeoutForTesting>(connection, decoder, replyEncoder, this, &NetworkProcess::resetServiceWorkerFetchTimeoutForTesting);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
    UNUSED_PARAM(replyEncoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return false;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled synchronous message %s to %" PRIu64, description(decoder.messageName()), decoder.destinationID());
    return false;
}

} // namespace WebKit

#if ENABLE(IPC_TESTING_API)

namespace IPC {

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_InitializeNetworkProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::InitializeNetworkProcess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_InitializeNetworkProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::InitializeNetworkProcess::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_CreateNetworkConnectionToWebProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::CreateNetworkConnectionToWebProcess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_CreateNetworkConnectionToWebProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::CreateNetworkConnectionToWebProcess::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_AddAllowedFirstPartyForCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::AddAllowedFirstPartyForCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_AddAllowedFirstPartyForCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::AddAllowedFirstPartyForCookies::ReplyArguments>(globalObject, decoder);
}
#if USE(SOUP)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetIgnoreTLSErrors>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetIgnoreTLSErrors::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_UserPreferredLanguagesChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::UserPreferredLanguagesChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetNetworkProxySettings>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetNetworkProxySettings::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_PrefetchDNS>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::PrefetchDNS::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPersistentCredentialStorageEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPersistentCredentialStorageEnabled::Arguments>(globalObject, decoder);
}
#endif
#if USE(CURL)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetNetworkProxySettings>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetNetworkProxySettings::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_AddWebsiteDataStore>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::AddWebsiteDataStore::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DestroySession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DestroySession::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_DestroySession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DestroySession::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_FetchWebsiteData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::FetchWebsiteData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_FetchWebsiteData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::FetchWebsiteData::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DeleteWebsiteData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DeleteWebsiteData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_DeleteWebsiteData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DeleteWebsiteData::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DeleteWebsiteDataForOrigins>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DeleteWebsiteDataForOrigins::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_DeleteWebsiteDataForOrigins>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DeleteWebsiteDataForOrigins::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_RenameOriginInWebsiteData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::RenameOriginInWebsiteData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_RenameOriginInWebsiteData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::RenameOriginInWebsiteData::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_WebsiteDataOriginDirectoryForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::WebsiteDataOriginDirectoryForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_WebsiteDataOriginDirectoryForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::WebsiteDataOriginDirectoryForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DownloadRequest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DownloadRequest::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ResumeDownload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResumeDownload::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_CancelDownload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::CancelDownload::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_CancelDownload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::CancelDownload::ReplyArguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_PublishDownloadProgress>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::PublishDownloadProgress::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DataTaskWithRequest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DataTaskWithRequest::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_DataTaskWithRequest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DataTaskWithRequest::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_CancelDataTask>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::CancelDataTask::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ApplicationDidEnterBackground>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ApplicationDidEnterBackground::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ApplicationWillEnterForeground>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ApplicationWillEnterForeground::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetAllowsAnySSLCertificateForWebSocket>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetAllowsAnySSLCertificateForWebSocket::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetAllowsAnySSLCertificateForWebSocket>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetAllowsAnySSLCertificateForWebSocket::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_FlushCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::FlushCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_FlushCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::FlushCookies::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_AllowSpecificHTTPSCertificateForHost>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::AllowSpecificHTTPSCertificateForHost::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_AllowTLSCertificateChainForLocalPCMTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::AllowTLSCertificateChainForLocalPCMTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetCacheModel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetCacheModel::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetCacheModelSynchronouslyForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetCacheModelSynchronouslyForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetCacheModelSynchronouslyForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetCacheModelSynchronouslyForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ProcessWillSuspendImminentlyForTestingSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ProcessWillSuspendImminentlyForTestingSync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ProcessWillSuspendImminentlyForTestingSync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ProcessWillSuspendImminentlyForTestingSync::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_PrepareToSuspend>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::PrepareToSuspend::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_PrepareToSuspend>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::PrepareToSuspend::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ProcessDidResume>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ProcessDidResume::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_NotifyMediaStreamingActivity>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::NotifyMediaStreamingActivity::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_PreconnectTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::PreconnectTo::Arguments>(globalObject, decoder);
}
#if ENABLE(TRACKING_PREVENTION)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ClearPrevalentResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearPrevalentResource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ClearPrevalentResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearPrevalentResource::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ClearUserInteraction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearUserInteraction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ClearUserInteraction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearUserInteraction::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DumpResourceLoadStatistics>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DumpResourceLoadStatistics::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_DumpResourceLoadStatistics>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DumpResourceLoadStatistics::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetTrackingPreventionEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetTrackingPreventionEnabled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetResourceLoadStatisticsLogTestingEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetResourceLoadStatisticsLogTestingEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_UpdatePrevalentDomainsToBlockCookiesFor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::UpdatePrevalentDomainsToBlockCookiesFor::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_UpdatePrevalentDomainsToBlockCookiesFor>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::UpdatePrevalentDomainsToBlockCookiesFor::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_IsGrandfathered>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsGrandfathered::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_IsGrandfathered>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsGrandfathered::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_IsPrevalentResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsPrevalentResource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_IsPrevalentResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsPrevalentResource::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_IsVeryPrevalentResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsVeryPrevalentResource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_IsVeryPrevalentResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsVeryPrevalentResource::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetLastSeen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetLastSeen::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetLastSeen>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetLastSeen::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_MergeStatisticForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::MergeStatisticForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_MergeStatisticForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::MergeStatisticForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_InsertExpiredStatisticForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::InsertExpiredStatisticForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_InsertExpiredStatisticForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::InsertExpiredStatisticForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPrevalentResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrevalentResource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetPrevalentResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrevalentResource::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPrevalentResourceForDebugMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrevalentResourceForDebugMode::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetPrevalentResourceForDebugMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrevalentResourceForDebugMode::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_IsResourceLoadStatisticsEphemeral>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsResourceLoadStatisticsEphemeral::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_IsResourceLoadStatisticsEphemeral>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsResourceLoadStatisticsEphemeral::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_HadUserInteraction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::HadUserInteraction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_HadUserInteraction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::HadUserInteraction::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_IsRelationshipOnlyInDatabaseOnce>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsRelationshipOnlyInDatabaseOnce::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_IsRelationshipOnlyInDatabaseOnce>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsRelationshipOnlyInDatabaseOnce::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_HasLocalStorage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::HasLocalStorage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_HasLocalStorage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::HasLocalStorage::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_GetAllStorageAccessEntries>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetAllStorageAccessEntries::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_GetAllStorageAccessEntries>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetAllStorageAccessEntries::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_IsRegisteredAsRedirectingTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsRegisteredAsRedirectingTo::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_IsRegisteredAsRedirectingTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsRegisteredAsRedirectingTo::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_IsRegisteredAsSubFrameUnder>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsRegisteredAsSubFrameUnder::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_IsRegisteredAsSubFrameUnder>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsRegisteredAsSubFrameUnder::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_IsRegisteredAsSubresourceUnder>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsRegisteredAsSubresourceUnder::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_IsRegisteredAsSubresourceUnder>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::IsRegisteredAsSubresourceUnder::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DomainIDExistsInDatabase>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DomainIDExistsInDatabase::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_DomainIDExistsInDatabase>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DomainIDExistsInDatabase::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_LogFrameNavigation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::LogFrameNavigation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_LogUserInteraction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::LogUserInteraction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_LogUserInteraction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::LogUserInteraction::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ResetParametersToDefaultValues>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetParametersToDefaultValues::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ResetParametersToDefaultValues>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetParametersToDefaultValues::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ScheduleClearInMemoryAndPersistent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ScheduleClearInMemoryAndPersistent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ScheduleClearInMemoryAndPersistent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ScheduleClearInMemoryAndPersistent::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ScheduleCookieBlockingUpdate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ScheduleCookieBlockingUpdate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ScheduleCookieBlockingUpdate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ScheduleCookieBlockingUpdate::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ScheduleStatisticsAndDataRecordsProcessing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ScheduleStatisticsAndDataRecordsProcessing::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ScheduleStatisticsAndDataRecordsProcessing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ScheduleStatisticsAndDataRecordsProcessing::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_StatisticsDatabaseHasAllTables>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::StatisticsDatabaseHasAllTables::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_StatisticsDatabaseHasAllTables>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::StatisticsDatabaseHasAllTables::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetCacheMaxAgeCapForPrevalentResources>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetCacheMaxAgeCapForPrevalentResources::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetCacheMaxAgeCapForPrevalentResources>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetCacheMaxAgeCapForPrevalentResources::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetGrandfathered>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetGrandfathered::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetGrandfathered>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetGrandfathered::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_GetResourceLoadStatisticsDataSummary>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetResourceLoadStatisticsDataSummary::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_GetResourceLoadStatisticsDataSummary>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetResourceLoadStatisticsDataSummary::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetGrandfatheringTime>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetGrandfatheringTime::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetGrandfatheringTime>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetGrandfatheringTime::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetMaxStatisticsEntries>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetMaxStatisticsEntries::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetMaxStatisticsEntries>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetMaxStatisticsEntries::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetMinimumTimeBetweenDataRecordsRemoval>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetMinimumTimeBetweenDataRecordsRemoval::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetMinimumTimeBetweenDataRecordsRemoval>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetMinimumTimeBetweenDataRecordsRemoval::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPruneEntriesDownTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPruneEntriesDownTo::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetPruneEntriesDownTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPruneEntriesDownTo::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetShouldClassifyResourcesBeforeDataRecordsRemoval>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetShouldClassifyResourcesBeforeDataRecordsRemoval::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetShouldClassifyResourcesBeforeDataRecordsRemoval>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetShouldClassifyResourcesBeforeDataRecordsRemoval::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetNotifyPagesWhenDataRecordsWereScanned>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetNotifyPagesWhenDataRecordsWereScanned::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetNotifyPagesWhenDataRecordsWereScanned>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetNotifyPagesWhenDataRecordsWereScanned::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetResourceLoadStatisticsTimeAdvanceForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetResourceLoadStatisticsTimeAdvanceForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetResourceLoadStatisticsTimeAdvanceForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetResourceLoadStatisticsTimeAdvanceForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetIsRunningResourceLoadStatisticsTest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetIsRunningResourceLoadStatisticsTest::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetIsRunningResourceLoadStatisticsTest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetIsRunningResourceLoadStatisticsTest::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetResourceLoadStatisticsDebugMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetResourceLoadStatisticsDebugMode::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetResourceLoadStatisticsDebugMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetResourceLoadStatisticsDebugMode::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetVeryPrevalentResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetVeryPrevalentResource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetVeryPrevalentResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetVeryPrevalentResource::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetSubframeUnderTopFrameDomain>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetSubframeUnderTopFrameDomain::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetSubframeUnderTopFrameDomain>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetSubframeUnderTopFrameDomain::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetSubresourceUnderTopFrameDomain>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetSubresourceUnderTopFrameDomain::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetSubresourceUnderTopFrameDomain>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetSubresourceUnderTopFrameDomain::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetSubresourceUniqueRedirectTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetSubresourceUniqueRedirectTo::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetSubresourceUniqueRedirectTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetSubresourceUniqueRedirectTo::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetSubresourceUniqueRedirectFrom>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetSubresourceUniqueRedirectFrom::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetSubresourceUniqueRedirectFrom>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetSubresourceUniqueRedirectFrom::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetTimeToLiveUserInteraction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetTimeToLiveUserInteraction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetTimeToLiveUserInteraction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetTimeToLiveUserInteraction::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetTopFrameUniqueRedirectTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetTopFrameUniqueRedirectTo::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetTopFrameUniqueRedirectTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetTopFrameUniqueRedirectTo::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetTopFrameUniqueRedirectFrom>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetTopFrameUniqueRedirectFrom::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetTopFrameUniqueRedirectFrom>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetTopFrameUniqueRedirectFrom::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ResetCacheMaxAgeCapForPrevalentResources>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetCacheMaxAgeCapForPrevalentResources::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ResetCacheMaxAgeCapForPrevalentResources>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetCacheMaxAgeCapForPrevalentResources::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DidCommitCrossSiteLoadWithDataTransfer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DidCommitCrossSiteLoadWithDataTransfer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetCrossSiteLoadWithLinkDecorationForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetCrossSiteLoadWithLinkDecorationForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetCrossSiteLoadWithLinkDecorationForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetCrossSiteLoadWithLinkDecorationForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ResetCrossSiteLoadsWithLinkDecorationForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetCrossSiteLoadsWithLinkDecorationForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ResetCrossSiteLoadsWithLinkDecorationForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetCrossSiteLoadsWithLinkDecorationForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DeleteCookiesForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DeleteCookiesForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_DeleteCookiesForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DeleteCookiesForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_HasIsolatedSession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::HasIsolatedSession::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_HasIsolatedSession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::HasIsolatedSession::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_CloseITPDatabase>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::CloseITPDatabase::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_CloseITPDatabase>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::CloseITPDatabase::ReplyArguments>(globalObject, decoder);
}
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(APP_BOUND_DOMAINS))
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetAppBoundDomainsForResourceLoadStatistics>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetAppBoundDomainsForResourceLoadStatistics::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetAppBoundDomainsForResourceLoadStatistics>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetAppBoundDomainsForResourceLoadStatistics::ReplyArguments>(globalObject, decoder);
}
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(MANAGED_DOMAINS))
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetManagedDomainsForResourceLoadStatistics>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetManagedDomainsForResourceLoadStatistics::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetManagedDomainsForResourceLoadStatistics>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetManagedDomainsForResourceLoadStatistics::ReplyArguments>(globalObject, decoder);
}
#endif
#if ENABLE(TRACKING_PREVENTION)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetShouldDowngradeReferrerForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetShouldDowngradeReferrerForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetShouldDowngradeReferrerForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetShouldDowngradeReferrerForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetThirdPartyCookieBlockingMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetThirdPartyCookieBlockingMode::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetThirdPartyCookieBlockingMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetThirdPartyCookieBlockingMode::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetShouldEnbleSameSiteStrictEnforcementForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetShouldEnbleSameSiteStrictEnforcementForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetShouldEnbleSameSiteStrictEnforcementForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetShouldEnbleSameSiteStrictEnforcementForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetFirstPartyWebsiteDataRemovalModeForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetFirstPartyWebsiteDataRemovalModeForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetFirstPartyWebsiteDataRemovalModeForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetFirstPartyWebsiteDataRemovalModeForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetToSameSiteStrictCookiesForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetToSameSiteStrictCookiesForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetToSameSiteStrictCookiesForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetToSameSiteStrictCookiesForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetFirstPartyHostCNAMEDomainForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetFirstPartyHostCNAMEDomainForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetFirstPartyHostCNAMEDomainForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetFirstPartyHostCNAMEDomainForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetThirdPartyCNAMEDomainForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetThirdPartyCNAMEDomainForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetThirdPartyCNAMEDomainForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetThirdPartyCNAMEDomainForTesting::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPrivateClickMeasurementDebugMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementDebugMode::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetBlobRegistryTopOriginPartitioningEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetBlobRegistryTopOriginPartitioningEnabled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetSessionIsControlledByAutomation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetSessionIsControlledByAutomation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_RegisterURLSchemeAsSecure>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::RegisterURLSchemeAsSecure::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_RegisterURLSchemeAsBypassingContentSecurityPolicy>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::RegisterURLSchemeAsBypassingContentSecurityPolicy::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_RegisterURLSchemeAsLocal>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::RegisterURLSchemeAsLocal::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_RegisterURLSchemeAsNoAccess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::RegisterURLSchemeAsNoAccess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SyncLocalStorage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SyncLocalStorage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SyncLocalStorage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SyncLocalStorage::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_StoreServiceWorkerRegistrations>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::StoreServiceWorkerRegistrations::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_StoreServiceWorkerRegistrations>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::StoreServiceWorkerRegistrations::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_StorePrivateClickMeasurement>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::StorePrivateClickMeasurement::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DumpPrivateClickMeasurement>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DumpPrivateClickMeasurement::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_DumpPrivateClickMeasurement>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DumpPrivateClickMeasurement::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ClearPrivateClickMeasurement>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearPrivateClickMeasurement::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ClearPrivateClickMeasurement>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearPrivateClickMeasurement::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPrivateClickMeasurementOverrideTimerForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementOverrideTimerForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetPrivateClickMeasurementOverrideTimerForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementOverrideTimerForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_MarkAttributedPrivateClickMeasurementsAsExpiredForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::MarkAttributedPrivateClickMeasurementsAsExpiredForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_MarkAttributedPrivateClickMeasurementsAsExpiredForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::MarkAttributedPrivateClickMeasurementsAsExpiredForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPrivateClickMeasurementEphemeralMeasurementForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementEphemeralMeasurementForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetPrivateClickMeasurementEphemeralMeasurementForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementEphemeralMeasurementForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SimulatePrivateClickMeasurementSessionRestart>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SimulatePrivateClickMeasurementSessionRestart::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SimulatePrivateClickMeasurementSessionRestart>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SimulatePrivateClickMeasurementSessionRestart::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPrivateClickMeasurementTokenPublicKeyURLForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementTokenPublicKeyURLForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetPrivateClickMeasurementTokenPublicKeyURLForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementTokenPublicKeyURLForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPrivateClickMeasurementTokenSignatureURLForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementTokenSignatureURLForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetPrivateClickMeasurementTokenSignatureURLForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementTokenSignatureURLForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPrivateClickMeasurementAttributionReportURLsForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementAttributionReportURLsForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetPrivateClickMeasurementAttributionReportURLsForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementAttributionReportURLsForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_MarkPrivateClickMeasurementsAsExpiredForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::MarkPrivateClickMeasurementsAsExpiredForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_MarkPrivateClickMeasurementsAsExpiredForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::MarkPrivateClickMeasurementsAsExpiredForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPCMFraudPreventionValuesForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPCMFraudPreventionValuesForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetPCMFraudPreventionValuesForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPCMFraudPreventionValuesForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPrivateClickMeasurementAppBundleIDForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementAppBundleIDForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetPrivateClickMeasurementAppBundleIDForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPrivateClickMeasurementAppBundleIDForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ClosePCMDatabase>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClosePCMDatabase::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ClosePCMDatabase>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClosePCMDatabase::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetServiceWorkerFetchTimeoutForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetServiceWorkerFetchTimeoutForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetServiceWorkerFetchTimeoutForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetServiceWorkerFetchTimeoutForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ResetServiceWorkerFetchTimeoutForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetServiceWorkerFetchTimeoutForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ResetServiceWorkerFetchTimeoutForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetServiceWorkerFetchTimeoutForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ResetQuota>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetQuota::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ResetQuota>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetQuota::ReplyArguments>(globalObject, decoder);
}
#if PLATFORM(IOS_FAMILY)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetBackupExclusionPeriodForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetBackupExclusionPeriodForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetBackupExclusionPeriodForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetBackupExclusionPeriodForTesting::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ResetStoragePersistedState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetStoragePersistedState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ResetStoragePersistedState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResetStoragePersistedState::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_CloneSessionStorageForWebPage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::CloneSessionStorageForWebPage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DidIncreaseQuota>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DidIncreaseQuota::Arguments>(globalObject, decoder);
}
#if ENABLE(APP_BOUND_DOMAINS)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_HasAppBoundSession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::HasAppBoundSession::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_HasAppBoundSession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::HasAppBoundSession::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ClearAppBoundSession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearAppBoundSession::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ClearAppBoundSession>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearAppBoundSession::ReplyArguments>(globalObject, decoder);
}
#endif
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DisableServiceWorkerEntitlement>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DisableServiceWorkerEntitlement::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ClearServiceWorkerEntitlementOverride>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearServiceWorkerEntitlementOverride::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ClearServiceWorkerEntitlementOverride>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearServiceWorkerEntitlementOverride::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_UpdateBundleIdentifier>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::UpdateBundleIdentifier::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_UpdateBundleIdentifier>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::UpdateBundleIdentifier::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ClearBundleIdentifier>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearBundleIdentifier::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ClearBundleIdentifier>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearBundleIdentifier::ReplyArguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_AppPrivacyReportTestingData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::AppPrivacyReportTestingData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_AppPrivacyReportTestingData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::AppPrivacyReportTestingData::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ClearAppPrivacyReportTestingData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearAppPrivacyReportTestingData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ClearAppPrivacyReportTestingData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearAppPrivacyReportTestingData::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_AddWebPageNetworkParameters>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::AddWebPageNetworkParameters::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_RemoveWebPageNetworkParameters>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::RemoveWebPageNetworkParameters::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_CountNonDefaultSessionSets>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::CountNonDefaultSessionSets::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_CountNonDefaultSessionSets>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::CountNonDefaultSessionSets::ReplyArguments>(globalObject, decoder);
}
#if ENABLE(CFPREFS_DIRECT_MODE)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_NotifyPreferencesChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::NotifyPreferencesChanged::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_TerminateRemoteWorkerContextConnectionWhenPossible>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::TerminateRemoteWorkerContextConnectionWhenPossible::Arguments>(globalObject, decoder);
}
#if ENABLE(SERVICE_WORKER)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_GetPendingPushMessages>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetPendingPushMessages::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_GetPendingPushMessages>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetPendingPushMessages::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ProcessPushMessage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ProcessPushMessage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ProcessPushMessage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ProcessPushMessage::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ProcessNotificationEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ProcessNotificationEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ProcessNotificationEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ProcessNotificationEvent::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_GetAllBackgroundFetchIdentifiers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetAllBackgroundFetchIdentifiers::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_GetAllBackgroundFetchIdentifiers>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetAllBackgroundFetchIdentifiers::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_GetBackgroundFetchState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetBackgroundFetchState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_GetBackgroundFetchState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetBackgroundFetchState::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_AbortBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::AbortBackgroundFetch::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_AbortBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::AbortBackgroundFetch::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_PauseBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::PauseBackgroundFetch::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_PauseBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::PauseBackgroundFetch::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ResumeBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResumeBackgroundFetch::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ResumeBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ResumeBackgroundFetch::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ClickBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClickBackgroundFetch::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_ClickBackgroundFetch>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClickBackgroundFetch::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetPushAndNotificationsEnabledForOrigin>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPushAndNotificationsEnabledForOrigin::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_SetPushAndNotificationsEnabledForOrigin>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetPushAndNotificationsEnabledForOrigin::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_DeletePushAndNotificationRegistration>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DeletePushAndNotificationRegistration::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_DeletePushAndNotificationRegistration>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::DeletePushAndNotificationRegistration::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_GetOriginsWithPushAndNotificationPermissions>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetOriginsWithPushAndNotificationPermissions::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_GetOriginsWithPushAndNotificationPermissions>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::GetOriginsWithPushAndNotificationPermissions::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_HasPushSubscriptionForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::HasPushSubscriptionForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcess_HasPushSubscriptionForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::HasPushSubscriptionForTesting::ReplyArguments>(globalObject, decoder);
}
#if ENABLE(INSPECTOR_NETWORK_THROTTLING)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetEmulatedConditions>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetEmulatedConditions::Arguments>(globalObject, decoder);
}
#endif
#if HAVE(NW_PROXY_CONFIG)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_ClearProxyConfigData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::ClearProxyConfigData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcess_SetProxyConfigData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcess::SetProxyConfigData::Arguments>(globalObject, decoder);
}
#endif

}

#endif

