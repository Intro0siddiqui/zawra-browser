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
#include "NetworkConnectionToWebProcess.h"

#include "ArgumentCoders.h" // NOLINT
#if ENABLE(LOGD_BLOCKING_IN_WEBCONTENT)
#include "DataReference.h" // NOLINT
#endif
#include "Decoder.h" // NOLINT
#include "DownloadID.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "NavigatingToAppBoundDomain.h" // NOLINT
#include "NetworkConnectionToWebProcessMessages.h" // NOLINT
#include "NetworkResourceLoadIdentifier.h" // NOLINT
#include "NetworkResourceLoadParameters.h" // NOLINT
#include "SandboxExtension.h" // NOLINT
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebPageProxyIdentifier.h" // NOLINT
#include <WebCore/AdvancedPrivacyProtections.h> // NOLINT
#include <WebCore/BlobPart.h> // NOLINT
#include <WebCore/ClientOrigin.h> // NOLINT
#include <WebCore/Cookie.h> // NOLINT
#include <WebCore/CookieJar.h> // NOLINT
#include <WebCore/CookieStoreGetOptions.h> // NOLINT
#if ENABLE(TRACKING_PREVENTION)
#include <WebCore/DocumentStorageAccess.h> // NOLINT
#endif
#include <WebCore/FrameIdentifier.h> // NOLINT
#include <WebCore/LoadSchedulingMode.h> // NOLINT
#include <WebCore/MessagePortIdentifier.h> // NOLINT
#include <WebCore/MessageWithMessagePorts.h> // NOLINT
#if ENABLE(CONTENT_FILTERING)
#include <WebCore/MockContentFilterSettings.h> // NOLINT
#endif
#include <WebCore/NetworkLoadInformation.h> // NOLINT
#include <WebCore/NetworkLoadMetrics.h> // NOLINT
#include <WebCore/NetworkStorageSession.h> // NOLINT
#include <WebCore/PageIdentifier.h> // NOLINT
#include <WebCore/PolicyContainer.h> // NOLINT
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ProcessQualified.h> // NOLINT
#endif
#if ENABLE(WEB_RTC)
#include <WebCore/RTCDataChannelIdentifier.h> // NOLINT
#endif
#include <WebCore/RegistrableDomain.h> // NOLINT
#include <WebCore/ResourceError.h> // NOLINT
#if ENABLE(TRACKING_PREVENTION)
#include <WebCore/ResourceLoadStatistics.h> // NOLINT
#endif
#include <WebCore/ResourceLoaderIdentifier.h> // NOLINT
#include <WebCore/ResourceRequest.h> // NOLINT
#include <WebCore/ResourceResponse.h> // NOLINT
#include <WebCore/SameSiteInfo.h> // NOLINT
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ScriptExecutionContextIdentifier.h> // NOLINT
#endif
#include <WebCore/SecurityOriginData.h> // NOLINT
#include <WebCore/ShouldRelaxThirdPartyCookieBlocking.h> // NOLINT
#include <WebCore/StoredCredentialsPolicy.h> // NOLINT
#include <WebCore/WebSocketIdentifier.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/Expected.h> // NOLINT
#if ENABLE(SERVICE_WORKER)
#include <wtf/ObjectIdentifier.h> // NOLINT
#endif
#include <wtf/OptionSet.h> // NOLINT
#include <wtf/Seconds.h> // NOLINT
#include <wtf/URLHash.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void NetworkConnectionToWebProcess::didReceiveNetworkConnectionToWebProcessMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::ScheduleResourceLoad::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::ScheduleResourceLoad>(connection, decoder, this, &NetworkConnectionToWebProcess::scheduleResourceLoad);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::LoadPing::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::LoadPing>(connection, decoder, this, &NetworkConnectionToWebProcess::loadPing);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RemoveLoadIdentifier::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::RemoveLoadIdentifier>(connection, decoder, this, &NetworkConnectionToWebProcess::removeLoadIdentifier);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::PageLoadCompleted::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::PageLoadCompleted>(connection, decoder, this, &NetworkConnectionToWebProcess::pageLoadCompleted);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::BrowsingContextRemoved::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::BrowsingContextRemoved>(connection, decoder, this, &NetworkConnectionToWebProcess::browsingContextRemoved);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::PrefetchDNS::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::PrefetchDNS>(connection, decoder, this, &NetworkConnectionToWebProcess::prefetchDNS);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::SendH2Ping::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::SendH2Ping>(connection, decoder, this, &NetworkConnectionToWebProcess::sendH2Ping);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::PreconnectTo::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::PreconnectTo>(connection, decoder, this, &NetworkConnectionToWebProcess::preconnectTo);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::IsResourceLoadFinished::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::IsResourceLoadFinished>(connection, decoder, this, &NetworkConnectionToWebProcess::isResourceLoadFinished);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::StartDownload::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::StartDownload>(connection, decoder, this, &NetworkConnectionToWebProcess::startDownload);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::ConvertMainResourceLoadToDownload::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::ConvertMainResourceLoadToDownload>(connection, decoder, this, &NetworkConnectionToWebProcess::convertMainResourceLoadToDownload);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::SetCookiesFromDOM::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::SetCookiesFromDOM>(connection, decoder, this, &NetworkConnectionToWebProcess::setCookiesFromDOM);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::SetRawCookie::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::SetRawCookie>(connection, decoder, this, &NetworkConnectionToWebProcess::setRawCookie);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::DeleteCookie::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::DeleteCookie>(connection, decoder, this, &NetworkConnectionToWebProcess::deleteCookie);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::CookiesForDOMAsync::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::CookiesForDOMAsync>(connection, decoder, this, &NetworkConnectionToWebProcess::cookiesForDOMAsync);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::SetCookieFromDOMAsync::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::SetCookieFromDOMAsync>(connection, decoder, this, &NetworkConnectionToWebProcess::setCookieFromDOMAsync);
#if HAVE(COOKIE_CHANGE_LISTENER_API)
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::SubscribeToCookieChangeNotifications::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::SubscribeToCookieChangeNotifications>(connection, decoder, this, &NetworkConnectionToWebProcess::subscribeToCookieChangeNotifications);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::UnsubscribeFromCookieChangeNotifications::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::UnsubscribeFromCookieChangeNotifications>(connection, decoder, this, &NetworkConnectionToWebProcess::unsubscribeFromCookieChangeNotifications);
#endif
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RegisterInternalFileBlobURL::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::RegisterInternalFileBlobURL>(connection, decoder, this, &NetworkConnectionToWebProcess::registerInternalFileBlobURL);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RegisterInternalBlobURL::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::RegisterInternalBlobURL>(connection, decoder, this, &NetworkConnectionToWebProcess::registerInternalBlobURL);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RegisterBlobURL::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::RegisterBlobURL>(connection, decoder, this, &NetworkConnectionToWebProcess::registerBlobURL);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RegisterInternalBlobURLOptionallyFileBacked::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::RegisterInternalBlobURLOptionallyFileBacked>(connection, decoder, this, &NetworkConnectionToWebProcess::registerInternalBlobURLOptionallyFileBacked);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RegisterInternalBlobURLForSlice::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::RegisterInternalBlobURLForSlice>(connection, decoder, this, &NetworkConnectionToWebProcess::registerInternalBlobURLForSlice);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::UnregisterBlobURL::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::UnregisterBlobURL>(connection, decoder, this, &NetworkConnectionToWebProcess::unregisterBlobURL);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::WriteBlobsToTemporaryFilesForIndexedDB::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::WriteBlobsToTemporaryFilesForIndexedDB>(connection, decoder, this, &NetworkConnectionToWebProcess::writeBlobsToTemporaryFilesForIndexedDB);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RegisterBlobURLHandle::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::RegisterBlobURLHandle>(connection, decoder, this, &NetworkConnectionToWebProcess::registerBlobURLHandle);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::UnregisterBlobURLHandle::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::UnregisterBlobURLHandle>(connection, decoder, this, &NetworkConnectionToWebProcess::unregisterBlobURLHandle);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::SetCaptureExtraNetworkLoadMetricsEnabled::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::SetCaptureExtraNetworkLoadMetricsEnabled>(connection, decoder, this, &NetworkConnectionToWebProcess::setCaptureExtraNetworkLoadMetricsEnabled);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::CreateSocketChannel::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::CreateSocketChannel>(connection, decoder, this, &NetworkConnectionToWebProcess::createSocketChannel);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::ClearPageSpecificData::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::ClearPageSpecificData>(connection, decoder, this, &NetworkConnectionToWebProcess::clearPageSpecificData);
#if ENABLE(TRACKING_PREVENTION)
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RemoveStorageAccessForFrame::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::RemoveStorageAccessForFrame>(connection, decoder, this, &NetworkConnectionToWebProcess::removeStorageAccessForFrame);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::LogUserInteraction::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::LogUserInteraction>(connection, decoder, this, &NetworkConnectionToWebProcess::logUserInteraction);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::ResourceLoadStatisticsUpdated::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::ResourceLoadStatisticsUpdated>(connection, decoder, this, &NetworkConnectionToWebProcess::resourceLoadStatisticsUpdated);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::HasStorageAccess::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::HasStorageAccess>(connection, decoder, this, &NetworkConnectionToWebProcess::hasStorageAccess);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RequestStorageAccess::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::RequestStorageAccess>(connection, decoder, this, &NetworkConnectionToWebProcess::requestStorageAccess);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RequestStorageAccessUnderOpener::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::RequestStorageAccessUnderOpener>(connection, decoder, this, &NetworkConnectionToWebProcess::requestStorageAccessUnderOpener);
#endif
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::AddOriginAccessAllowListEntry::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::AddOriginAccessAllowListEntry>(connection, decoder, this, &NetworkConnectionToWebProcess::addOriginAccessAllowListEntry);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RemoveOriginAccessAllowListEntry::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::RemoveOriginAccessAllowListEntry>(connection, decoder, this, &NetworkConnectionToWebProcess::removeOriginAccessAllowListEntry);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::ResetOriginAccessAllowLists::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::ResetOriginAccessAllowLists>(connection, decoder, this, &NetworkConnectionToWebProcess::resetOriginAccessAllowLists);
#if ENABLE(SERVICE_WORKER)
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::EstablishSWContextConnection::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::EstablishSWContextConnection>(connection, decoder, this, &NetworkConnectionToWebProcess::establishSWContextConnection);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::CloseSWContextConnection::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::CloseSWContextConnection>(connection, decoder, this, &NetworkConnectionToWebProcess::closeSWContextConnection);
#endif
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::EstablishSharedWorkerContextConnection::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::EstablishSharedWorkerContextConnection>(connection, decoder, this, &NetworkConnectionToWebProcess::establishSharedWorkerContextConnection);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::CloseSharedWorkerContextConnection::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::CloseSharedWorkerContextConnection>(connection, decoder, this, &NetworkConnectionToWebProcess::closeSharedWorkerContextConnection);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::CreateRTCProvider::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::CreateRTCProvider>(connection, decoder, this, &NetworkConnectionToWebProcess::createRTCProvider);
#if ENABLE(WEB_RTC)
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::ConnectToRTCDataChannelRemoteSource::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::ConnectToRTCDataChannelRemoteSource>(connection, decoder, this, &NetworkConnectionToWebProcess::connectToRTCDataChannelRemoteSource);
#endif
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::UpdateQuotaBasedOnSpaceUsageForTesting::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::UpdateQuotaBasedOnSpaceUsageForTesting>(connection, decoder, this, &NetworkConnectionToWebProcess::updateQuotaBasedOnSpaceUsageForTesting);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::CreateNewMessagePortChannel::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::CreateNewMessagePortChannel>(connection, decoder, this, &NetworkConnectionToWebProcess::createNewMessagePortChannel);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::EntangleLocalPortInThisProcessToRemote::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::EntangleLocalPortInThisProcessToRemote>(connection, decoder, this, &NetworkConnectionToWebProcess::entangleLocalPortInThisProcessToRemote);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::MessagePortDisentangled::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::MessagePortDisentangled>(connection, decoder, this, &NetworkConnectionToWebProcess::messagePortDisentangled);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::MessagePortClosed::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::MessagePortClosed>(connection, decoder, this, &NetworkConnectionToWebProcess::messagePortClosed);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::TakeAllMessagesForPort::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::TakeAllMessagesForPort>(connection, decoder, this, &NetworkConnectionToWebProcess::takeAllMessagesForPort);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::PostMessageToRemote::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::PostMessageToRemote>(connection, decoder, this, &NetworkConnectionToWebProcess::postMessageToRemote);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::DidDeliverMessagePortMessages::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::DidDeliverMessagePortMessages>(connection, decoder, this, &NetworkConnectionToWebProcess::didDeliverMessagePortMessages);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::RegisterURLSchemesAsCORSEnabled::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::RegisterURLSchemesAsCORSEnabled>(connection, decoder, this, &NetworkConnectionToWebProcess::registerURLSchemesAsCORSEnabled);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::SetCORSDisablingPatterns::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::SetCORSDisablingPatterns>(connection, decoder, this, &NetworkConnectionToWebProcess::setCORSDisablingPatterns);
#if PLATFORM(MAC)
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::GetProcessDisplayName::name())
        return IPC::handleMessageAsync<Messages::NetworkConnectionToWebProcess::GetProcessDisplayName>(connection, decoder, this, &NetworkConnectionToWebProcess::getProcessDisplayName);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::UpdateActivePages::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::UpdateActivePages>(connection, decoder, this, &NetworkConnectionToWebProcess::updateActivePages);
#endif
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::SetResourceLoadSchedulingMode::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::SetResourceLoadSchedulingMode>(connection, decoder, this, &NetworkConnectionToWebProcess::setResourceLoadSchedulingMode);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::PrioritizeResourceLoads::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::PrioritizeResourceLoads>(connection, decoder, this, &NetworkConnectionToWebProcess::prioritizeResourceLoads);
#if ENABLE(CONTENT_FILTERING)
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::InstallMockContentFilter::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::InstallMockContentFilter>(connection, decoder, this, &NetworkConnectionToWebProcess::installMockContentFilter);
#endif
#if ENABLE(LOGD_BLOCKING_IN_WEBCONTENT)
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::LogOnBehalfOfWebContent::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::LogOnBehalfOfWebContent>(connection, decoder, this, &NetworkConnectionToWebProcess::logOnBehalfOfWebContent);
#endif
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::AddAllowedFirstPartyForCookies::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::AddAllowedFirstPartyForCookies>(connection, decoder, this, &NetworkConnectionToWebProcess::addAllowedFirstPartyForCookies);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::UseRedirectionForCurrentNavigation::name())
        return IPC::handleMessage<Messages::NetworkConnectionToWebProcess::UseRedirectionForCurrentNavigation>(connection, decoder, this, &NetworkConnectionToWebProcess::useRedirectionForCurrentNavigation);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool NetworkConnectionToWebProcess::didReceiveSyncNetworkConnectionToWebProcessMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::PerformSynchronousLoad::name())
        return IPC::handleMessageSynchronous<Messages::NetworkConnectionToWebProcess::PerformSynchronousLoad>(connection, decoder, replyEncoder, this, &NetworkConnectionToWebProcess::performSynchronousLoad);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::TestProcessIncomingSyncMessagesWhenWaitingForSyncReply::name())
        return IPC::handleMessageSynchronous<Messages::NetworkConnectionToWebProcess::TestProcessIncomingSyncMessagesWhenWaitingForSyncReply>(connection, decoder, replyEncoder, this, &NetworkConnectionToWebProcess::testProcessIncomingSyncMessagesWhenWaitingForSyncReply);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::CookiesForDOM::name())
        return IPC::handleMessageSynchronous<Messages::NetworkConnectionToWebProcess::CookiesForDOM>(connection, decoder, replyEncoder, this, &NetworkConnectionToWebProcess::cookiesForDOM);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::CookieRequestHeaderFieldValue::name())
        return IPC::handleMessageSynchronous<Messages::NetworkConnectionToWebProcess::CookieRequestHeaderFieldValue>(connection, decoder, replyEncoder, this, &NetworkConnectionToWebProcess::cookieRequestHeaderFieldValue);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::GetRawCookies::name())
        return IPC::handleMessageSynchronous<Messages::NetworkConnectionToWebProcess::GetRawCookies>(connection, decoder, replyEncoder, this, &NetworkConnectionToWebProcess::getRawCookies);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::DomCookiesForHost::name())
        return IPC::handleMessageSynchronous<Messages::NetworkConnectionToWebProcess::DomCookiesForHost>(connection, decoder, replyEncoder, this, &NetworkConnectionToWebProcess::domCookiesForHost);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::BlobSize::name())
        return IPC::handleMessageSynchronous<Messages::NetworkConnectionToWebProcess::BlobSize>(connection, decoder, replyEncoder, this, &NetworkConnectionToWebProcess::blobSize);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::GetNetworkLoadInformationResponse::name())
        return IPC::handleMessageSynchronous<Messages::NetworkConnectionToWebProcess::GetNetworkLoadInformationResponse>(connection, decoder, replyEncoder, this, &NetworkConnectionToWebProcess::getNetworkLoadInformationResponse);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::GetNetworkLoadIntermediateInformation::name())
        return IPC::handleMessageSynchronous<Messages::NetworkConnectionToWebProcess::GetNetworkLoadIntermediateInformation>(connection, decoder, replyEncoder, this, &NetworkConnectionToWebProcess::getNetworkLoadIntermediateInformation);
    if (decoder.messageName() == Messages::NetworkConnectionToWebProcess::TakeNetworkLoadInformationMetrics::name())
        return IPC::handleMessageSynchronous<Messages::NetworkConnectionToWebProcess::TakeNetworkLoadInformationMetrics>(connection, decoder, replyEncoder, this, &NetworkConnectionToWebProcess::takeNetworkLoadInformationMetrics);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_ScheduleResourceLoad>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::ScheduleResourceLoad::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_PerformSynchronousLoad>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::PerformSynchronousLoad::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_PerformSynchronousLoad>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::PerformSynchronousLoad::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::TestProcessIncomingSyncMessagesWhenWaitingForSyncReply::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::TestProcessIncomingSyncMessagesWhenWaitingForSyncReply::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_LoadPing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::LoadPing::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RemoveLoadIdentifier>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RemoveLoadIdentifier::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_PageLoadCompleted>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::PageLoadCompleted::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_BrowsingContextRemoved>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::BrowsingContextRemoved::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_PrefetchDNS>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::PrefetchDNS::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_SendH2Ping>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::SendH2Ping::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_SendH2Ping>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::SendH2Ping::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_PreconnectTo>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::PreconnectTo::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_IsResourceLoadFinished>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::IsResourceLoadFinished::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_IsResourceLoadFinished>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::IsResourceLoadFinished::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_StartDownload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::StartDownload::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_ConvertMainResourceLoadToDownload>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::ConvertMainResourceLoadToDownload::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_CookiesForDOM>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CookiesForDOM::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_CookiesForDOM>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CookiesForDOM::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_SetCookiesFromDOM>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::SetCookiesFromDOM::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_CookieRequestHeaderFieldValue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CookieRequestHeaderFieldValue::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_CookieRequestHeaderFieldValue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CookieRequestHeaderFieldValue::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_GetRawCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::GetRawCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_GetRawCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::GetRawCookies::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_SetRawCookie>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::SetRawCookie::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_DeleteCookie>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::DeleteCookie::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_DeleteCookie>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::DeleteCookie::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_DomCookiesForHost>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::DomCookiesForHost::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_DomCookiesForHost>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::DomCookiesForHost::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_CookiesForDOMAsync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CookiesForDOMAsync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_CookiesForDOMAsync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CookiesForDOMAsync::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_SetCookieFromDOMAsync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::SetCookieFromDOMAsync::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_SetCookieFromDOMAsync>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::SetCookieFromDOMAsync::ReplyArguments>(globalObject, decoder);
}
#if HAVE(COOKIE_CHANGE_LISTENER_API)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_SubscribeToCookieChangeNotifications>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::SubscribeToCookieChangeNotifications::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_UnsubscribeFromCookieChangeNotifications>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::UnsubscribeFromCookieChangeNotifications::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RegisterInternalFileBlobURL>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RegisterInternalFileBlobURL::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RegisterInternalBlobURL>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RegisterInternalBlobURL::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RegisterBlobURL>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RegisterBlobURL::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RegisterInternalBlobURLOptionallyFileBacked>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RegisterInternalBlobURLOptionallyFileBacked::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RegisterInternalBlobURLForSlice>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RegisterInternalBlobURLForSlice::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_UnregisterBlobURL>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::UnregisterBlobURL::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_BlobSize>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::BlobSize::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_BlobSize>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::BlobSize::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_WriteBlobsToTemporaryFilesForIndexedDB>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::WriteBlobsToTemporaryFilesForIndexedDB::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_WriteBlobsToTemporaryFilesForIndexedDB>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::WriteBlobsToTemporaryFilesForIndexedDB::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RegisterBlobURLHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RegisterBlobURLHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_UnregisterBlobURLHandle>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::UnregisterBlobURLHandle::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_SetCaptureExtraNetworkLoadMetricsEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::SetCaptureExtraNetworkLoadMetricsEnabled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_CreateSocketChannel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CreateSocketChannel::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_ClearPageSpecificData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::ClearPageSpecificData::Arguments>(globalObject, decoder);
}
#if ENABLE(TRACKING_PREVENTION)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RemoveStorageAccessForFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RemoveStorageAccessForFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_LogUserInteraction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::LogUserInteraction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_ResourceLoadStatisticsUpdated>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::ResourceLoadStatisticsUpdated::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_ResourceLoadStatisticsUpdated>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::ResourceLoadStatisticsUpdated::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_HasStorageAccess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::HasStorageAccess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_HasStorageAccess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::HasStorageAccess::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RequestStorageAccess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RequestStorageAccess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_RequestStorageAccess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RequestStorageAccess::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RequestStorageAccessUnderOpener>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RequestStorageAccessUnderOpener::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_AddOriginAccessAllowListEntry>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::AddOriginAccessAllowListEntry::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RemoveOriginAccessAllowListEntry>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RemoveOriginAccessAllowListEntry::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_ResetOriginAccessAllowLists>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::ResetOriginAccessAllowLists::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_GetNetworkLoadInformationResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::GetNetworkLoadInformationResponse::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_GetNetworkLoadInformationResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::GetNetworkLoadInformationResponse::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_GetNetworkLoadIntermediateInformation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::GetNetworkLoadIntermediateInformation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_GetNetworkLoadIntermediateInformation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::GetNetworkLoadIntermediateInformation::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_TakeNetworkLoadInformationMetrics>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::TakeNetworkLoadInformationMetrics::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_TakeNetworkLoadInformationMetrics>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::TakeNetworkLoadInformationMetrics::ReplyArguments>(globalObject, decoder);
}
#if ENABLE(SERVICE_WORKER)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_EstablishSWContextConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::EstablishSWContextConnection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_EstablishSWContextConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::EstablishSWContextConnection::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_CloseSWContextConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CloseSWContextConnection::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_EstablishSharedWorkerContextConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::EstablishSharedWorkerContextConnection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_EstablishSharedWorkerContextConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::EstablishSharedWorkerContextConnection::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_CloseSharedWorkerContextConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CloseSharedWorkerContextConnection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_CreateRTCProvider>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CreateRTCProvider::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_CreateRTCProvider>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CreateRTCProvider::ReplyArguments>(globalObject, decoder);
}
#if ENABLE(WEB_RTC)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_ConnectToRTCDataChannelRemoteSource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::ConnectToRTCDataChannelRemoteSource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_ConnectToRTCDataChannelRemoteSource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::ConnectToRTCDataChannelRemoteSource::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_UpdateQuotaBasedOnSpaceUsageForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::UpdateQuotaBasedOnSpaceUsageForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_CreateNewMessagePortChannel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::CreateNewMessagePortChannel::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_EntangleLocalPortInThisProcessToRemote>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::EntangleLocalPortInThisProcessToRemote::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_MessagePortDisentangled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::MessagePortDisentangled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_MessagePortClosed>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::MessagePortClosed::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_TakeAllMessagesForPort>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::TakeAllMessagesForPort::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_TakeAllMessagesForPort>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::TakeAllMessagesForPort::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_PostMessageToRemote>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::PostMessageToRemote::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_DidDeliverMessagePortMessages>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::DidDeliverMessagePortMessages::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_RegisterURLSchemesAsCORSEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::RegisterURLSchemesAsCORSEnabled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_SetCORSDisablingPatterns>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::SetCORSDisablingPatterns::Arguments>(globalObject, decoder);
}
#if PLATFORM(MAC)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_GetProcessDisplayName>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::GetProcessDisplayName::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkConnectionToWebProcess_GetProcessDisplayName>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::GetProcessDisplayName::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_UpdateActivePages>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::UpdateActivePages::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_SetResourceLoadSchedulingMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::SetResourceLoadSchedulingMode::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_PrioritizeResourceLoads>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::PrioritizeResourceLoads::Arguments>(globalObject, decoder);
}
#if ENABLE(CONTENT_FILTERING)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_InstallMockContentFilter>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::InstallMockContentFilter::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(LOGD_BLOCKING_IN_WEBCONTENT)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_LogOnBehalfOfWebContent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::LogOnBehalfOfWebContent::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_AddAllowedFirstPartyForCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::AddAllowedFirstPartyForCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkConnectionToWebProcess_UseRedirectionForCurrentNavigation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkConnectionToWebProcess::UseRedirectionForCurrentNavigation::Arguments>(globalObject, decoder);
}

}

#endif

