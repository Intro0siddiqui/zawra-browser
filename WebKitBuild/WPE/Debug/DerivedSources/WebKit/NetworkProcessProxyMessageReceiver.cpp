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
#include "NetworkProcessProxy.h"

#include "ArgumentCoders.h" // NOLINT
#include "AuthenticationChallengeDisposition.h" // NOLINT
#if ENABLE(SERVICE_WORKER)
#include "BackgroundFetchChange.h" // NOLINT
#endif
#include "DataReference.h" // NOLINT
#include "DataTaskIdentifier.h" // NOLINT
#include "Decoder.h" // NOLINT
#include "FormDataReference.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "IdentifierTypes.h" // NOLINT
#include "NetworkProcessProxyMessages.h" // NOLINT
#include "NetworkResourceLoadIdentifier.h" // NOLINT
#include "QuotaIncreaseRequestIdentifier.h" // NOLINT
#include "RemoteWorkerType.h" // NOLINT
#include "ResourceLoadInfo.h" // NOLINT
#if ENABLE(CONTENT_EXTENSIONS)
#include "UserContentControllerIdentifier.h" // NOLINT
#endif
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebPageProxyIdentifier.h" // NOLINT
#if ENABLE(TRACKING_PREVENTION)
#include "WebsiteDataFetchOption.h" // NOLINT
#endif
#include "WebsiteDataType.h" // NOLINT
#include <JavaScriptCore/ConsoleTypes.h> // NOLINT
#include <WebCore/AuthenticationChallenge.h> // NOLINT
#include <WebCore/ClientOrigin.h> // NOLINT
#include <WebCore/Credential.h> // NOLINT
#include <WebCore/DiagnosticLoggingClient.h> // NOLINT
#include <WebCore/FrameIdentifier.h> // NOLINT
#include <WebCore/FrameLoaderTypes.h> // NOLINT
#include <WebCore/PageIdentifier.h> // NOLINT
#include <WebCore/ProcessIdentifier.h> // NOLINT
#include <WebCore/ProcessQualified.h> // NOLINT
#include <WebCore/RegistrableDomain.h> // NOLINT
#include <WebCore/ResourceError.h> // NOLINT
#include <WebCore/ResourceRequest.h> // NOLINT
#include <WebCore/ResourceResponse.h> // NOLINT
#include <WebCore/ScriptExecutionContextIdentifier.h> // NOLINT
#include <WebCore/SecurityOriginData.h> // NOLINT
#include <optional> // NOLINT
#include <pal/SessionID.h> // NOLINT
#if ENABLE(TRACKING_PREVENTION)
#include <wtf/HashMap.h> // NOLINT
#endif
#if ENABLE(APP_BOUND_DOMAINS) || ENABLE(TRACKING_PREVENTION)
#include <wtf/HashSet.h> // NOLINT
#endif
#include <wtf/ObjectIdentifier.h> // NOLINT
#include <wtf/OptionSet.h> // NOLINT
#include <wtf/URLHash.h> // NOLINT
#if ENABLE(TRACKING_PREVENTION)
#include <wtf/Vector.h> // NOLINT
#endif
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void NetworkProcessProxy::didReceiveNetworkProcessProxyMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::NetworkProcessProxy::DidReceiveAuthenticationChallenge::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::DidReceiveAuthenticationChallenge>(connection, decoder, this, &NetworkProcessProxy::didReceiveAuthenticationChallenge);
    if (decoder.messageName() == Messages::NetworkProcessProxy::NegotiatedLegacyTLS::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::NegotiatedLegacyTLS>(connection, decoder, this, &NetworkProcessProxy::negotiatedLegacyTLS);
    if (decoder.messageName() == Messages::NetworkProcessProxy::DidNegotiateModernTLS::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::DidNegotiateModernTLS>(connection, decoder, this, &NetworkProcessProxy::didNegotiateModernTLS);
    if (decoder.messageName() == Messages::NetworkProcessProxy::DidBlockLoadToKnownTracker::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::DidBlockLoadToKnownTracker>(connection, decoder, this, &NetworkProcessProxy::didBlockLoadToKnownTracker);
    if (decoder.messageName() == Messages::NetworkProcessProxy::TerminateUnresponsiveServiceWorkerProcesses::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::TerminateUnresponsiveServiceWorkerProcesses>(connection, decoder, this, &NetworkProcessProxy::terminateUnresponsiveServiceWorkerProcesses);
    if (decoder.messageName() == Messages::NetworkProcessProxy::LogDiagnosticMessage::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::LogDiagnosticMessage>(connection, decoder, this, &NetworkProcessProxy::logDiagnosticMessage);
    if (decoder.messageName() == Messages::NetworkProcessProxy::LogDiagnosticMessageWithResult::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::LogDiagnosticMessageWithResult>(connection, decoder, this, &NetworkProcessProxy::logDiagnosticMessageWithResult);
    if (decoder.messageName() == Messages::NetworkProcessProxy::LogDiagnosticMessageWithValue::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::LogDiagnosticMessageWithValue>(connection, decoder, this, &NetworkProcessProxy::logDiagnosticMessageWithValue);
#if ENABLE(TRACKING_PREVENTION)
    if (decoder.messageName() == Messages::NetworkProcessProxy::LogTestingEvent::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::LogTestingEvent>(connection, decoder, this, &NetworkProcessProxy::logTestingEvent);
    if (decoder.messageName() == Messages::NetworkProcessProxy::NotifyResourceLoadStatisticsProcessed::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::NotifyResourceLoadStatisticsProcessed>(connection, decoder, this, &NetworkProcessProxy::notifyResourceLoadStatisticsProcessed);
    if (decoder.messageName() == Messages::NetworkProcessProxy::NotifyWebsiteDataDeletionForRegistrableDomainsFinished::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::NotifyWebsiteDataDeletionForRegistrableDomainsFinished>(connection, decoder, this, &NetworkProcessProxy::notifyWebsiteDataDeletionForRegistrableDomainsFinished);
    if (decoder.messageName() == Messages::NetworkProcessProxy::NotifyWebsiteDataScanForRegistrableDomainsFinished::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::NotifyWebsiteDataScanForRegistrableDomainsFinished>(connection, decoder, this, &NetworkProcessProxy::notifyWebsiteDataScanForRegistrableDomainsFinished);
    if (decoder.messageName() == Messages::NetworkProcessProxy::RequestStorageAccessConfirm::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::RequestStorageAccessConfirm>(connection, decoder, this, &NetworkProcessProxy::requestStorageAccessConfirm);
    if (decoder.messageName() == Messages::NetworkProcessProxy::DeleteWebsiteDataInUIProcessForRegistrableDomains::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::DeleteWebsiteDataInUIProcessForRegistrableDomains>(connection, decoder, this, &NetworkProcessProxy::deleteWebsiteDataInUIProcessForRegistrableDomains);
    if (decoder.messageName() == Messages::NetworkProcessProxy::DidCommitCrossSiteLoadWithDataTransferFromPrevalentResource::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::DidCommitCrossSiteLoadWithDataTransferFromPrevalentResource>(connection, decoder, this, &NetworkProcessProxy::didCommitCrossSiteLoadWithDataTransferFromPrevalentResource);
    if (decoder.messageName() == Messages::NetworkProcessProxy::SetDomainsWithUserInteraction::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::SetDomainsWithUserInteraction>(connection, decoder, this, &NetworkProcessProxy::setDomainsWithUserInteraction);
    if (decoder.messageName() == Messages::NetworkProcessProxy::SetDomainsWithCrossPageStorageAccess::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::SetDomainsWithCrossPageStorageAccess>(connection, decoder, this, &NetworkProcessProxy::setDomainsWithCrossPageStorageAccess);
#endif
#if ENABLE(CONTENT_EXTENSIONS)
    if (decoder.messageName() == Messages::NetworkProcessProxy::ContentExtensionRules::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::ContentExtensionRules>(connection, decoder, this, &NetworkProcessProxy::contentExtensionRules);
#endif
    if (decoder.messageName() == Messages::NetworkProcessProxy::TerminateWebProcess::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::TerminateWebProcess>(connection, decoder, this, &NetworkProcessProxy::terminateWebProcess);
#if ENABLE(SERVICE_WORKER)
    if (decoder.messageName() == Messages::NetworkProcessProxy::StartServiceWorkerBackgroundProcessing::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::StartServiceWorkerBackgroundProcessing>(connection, decoder, this, &NetworkProcessProxy::startServiceWorkerBackgroundProcessing);
    if (decoder.messageName() == Messages::NetworkProcessProxy::EndServiceWorkerBackgroundProcessing::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::EndServiceWorkerBackgroundProcessing>(connection, decoder, this, &NetworkProcessProxy::endServiceWorkerBackgroundProcessing);
    if (decoder.messageName() == Messages::NetworkProcessProxy::RequestBackgroundFetchPermission::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::RequestBackgroundFetchPermission>(connection, decoder, this, &NetworkProcessProxy::requestBackgroundFetchPermission);
    if (decoder.messageName() == Messages::NetworkProcessProxy::NotifyBackgroundFetchChange::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::NotifyBackgroundFetchChange>(connection, decoder, this, &NetworkProcessProxy::notifyBackgroundFetchChange);
#endif
    if (decoder.messageName() == Messages::NetworkProcessProxy::EstablishRemoteWorkerContextConnectionToNetworkProcess::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::EstablishRemoteWorkerContextConnectionToNetworkProcess>(connection, decoder, this, &NetworkProcessProxy::establishRemoteWorkerContextConnectionToNetworkProcess);
    if (decoder.messageName() == Messages::NetworkProcessProxy::RemoteWorkerContextConnectionNoLongerNeeded::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::RemoteWorkerContextConnectionNoLongerNeeded>(connection, decoder, this, &NetworkProcessProxy::remoteWorkerContextConnectionNoLongerNeeded);
    if (decoder.messageName() == Messages::NetworkProcessProxy::RegisterRemoteWorkerClientProcess::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::RegisterRemoteWorkerClientProcess>(connection, decoder, this, &NetworkProcessProxy::registerRemoteWorkerClientProcess);
    if (decoder.messageName() == Messages::NetworkProcessProxy::UnregisterRemoteWorkerClientProcess::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::UnregisterRemoteWorkerClientProcess>(connection, decoder, this, &NetworkProcessProxy::unregisterRemoteWorkerClientProcess);
    if (decoder.messageName() == Messages::NetworkProcessProxy::SetWebProcessHasUploads::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::SetWebProcessHasUploads>(connection, decoder, this, &NetworkProcessProxy::setWebProcessHasUploads);
#if ENABLE(APP_BOUND_DOMAINS)
    if (decoder.messageName() == Messages::NetworkProcessProxy::GetAppBoundDomains::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::GetAppBoundDomains>(connection, decoder, this, &NetworkProcessProxy::getAppBoundDomains);
#endif
    if (decoder.messageName() == Messages::NetworkProcessProxy::RequestStorageSpace::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::RequestStorageSpace>(connection, decoder, this, &NetworkProcessProxy::requestStorageSpace);
    if (decoder.messageName() == Messages::NetworkProcessProxy::IncreaseQuota::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::IncreaseQuota>(connection, decoder, this, &NetworkProcessProxy::increaseQuota);
    if (decoder.messageName() == Messages::NetworkProcessProxy::ResourceLoadDidSendRequest::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::ResourceLoadDidSendRequest>(connection, decoder, this, &NetworkProcessProxy::resourceLoadDidSendRequest);
    if (decoder.messageName() == Messages::NetworkProcessProxy::ResourceLoadDidPerformHTTPRedirection::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::ResourceLoadDidPerformHTTPRedirection>(connection, decoder, this, &NetworkProcessProxy::resourceLoadDidPerformHTTPRedirection);
    if (decoder.messageName() == Messages::NetworkProcessProxy::ResourceLoadDidReceiveChallenge::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::ResourceLoadDidReceiveChallenge>(connection, decoder, this, &NetworkProcessProxy::resourceLoadDidReceiveChallenge);
    if (decoder.messageName() == Messages::NetworkProcessProxy::ResourceLoadDidReceiveResponse::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::ResourceLoadDidReceiveResponse>(connection, decoder, this, &NetworkProcessProxy::resourceLoadDidReceiveResponse);
    if (decoder.messageName() == Messages::NetworkProcessProxy::ResourceLoadDidCompleteWithError::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::ResourceLoadDidCompleteWithError>(connection, decoder, this, &NetworkProcessProxy::resourceLoadDidCompleteWithError);
    if (decoder.messageName() == Messages::NetworkProcessProxy::TriggerBrowsingContextGroupSwitchForNavigation::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::TriggerBrowsingContextGroupSwitchForNavigation>(connection, decoder, this, &NetworkProcessProxy::triggerBrowsingContextGroupSwitchForNavigation);
#if USE(SOUP)
    if (decoder.messageName() == Messages::NetworkProcessProxy::DidExceedMemoryLimit::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::DidExceedMemoryLimit>(connection, decoder, this, &NetworkProcessProxy::didExceedMemoryLimit);
#endif
#if ENABLE(APPLE_PAY_REMOTE_UI_USES_SCENE)
    if (decoder.messageName() == Messages::NetworkProcessProxy::GetWindowSceneIdentifierForPaymentPresentation::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::GetWindowSceneIdentifierForPaymentPresentation>(connection, decoder, this, &NetworkProcessProxy::getWindowSceneIdentifierForPaymentPresentation);
#endif
    if (decoder.messageName() == Messages::NetworkProcessProxy::DataTaskReceivedChallenge::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::DataTaskReceivedChallenge>(connection, decoder, this, &NetworkProcessProxy::dataTaskReceivedChallenge);
    if (decoder.messageName() == Messages::NetworkProcessProxy::DataTaskWillPerformHTTPRedirection::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::DataTaskWillPerformHTTPRedirection>(connection, decoder, this, &NetworkProcessProxy::dataTaskWillPerformHTTPRedirection);
    if (decoder.messageName() == Messages::NetworkProcessProxy::DataTaskDidReceiveResponse::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::DataTaskDidReceiveResponse>(connection, decoder, this, &NetworkProcessProxy::dataTaskDidReceiveResponse);
    if (decoder.messageName() == Messages::NetworkProcessProxy::DataTaskDidReceiveData::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::DataTaskDidReceiveData>(connection, decoder, this, &NetworkProcessProxy::dataTaskDidReceiveData);
    if (decoder.messageName() == Messages::NetworkProcessProxy::DataTaskDidCompleteWithError::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::DataTaskDidCompleteWithError>(connection, decoder, this, &NetworkProcessProxy::dataTaskDidCompleteWithError);
    if (decoder.messageName() == Messages::NetworkProcessProxy::OpenWindowFromServiceWorker::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::OpenWindowFromServiceWorker>(connection, decoder, this, &NetworkProcessProxy::openWindowFromServiceWorker);
    if (decoder.messageName() == Messages::NetworkProcessProxy::NavigateServiceWorkerClient::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::NavigateServiceWorkerClient>(connection, decoder, this, &NetworkProcessProxy::navigateServiceWorkerClient);
    if (decoder.messageName() == Messages::NetworkProcessProxy::ReportConsoleMessage::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::ReportConsoleMessage>(connection, decoder, this, &NetworkProcessProxy::reportConsoleMessage);
    if (decoder.messageName() == Messages::NetworkProcessProxy::CookiesDidChange::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::CookiesDidChange>(connection, decoder, this, &NetworkProcessProxy::cookiesDidChange);
    if (decoder.messageName() == Messages::NetworkProcessProxy::DeleteWebsiteDataInWebProcessesForOrigin::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::DeleteWebsiteDataInWebProcessesForOrigin>(connection, decoder, this, &NetworkProcessProxy::deleteWebsiteDataInWebProcessesForOrigin);
    if (decoder.messageName() == Messages::NetworkProcessProxy::ReloadExecutionContextsForOrigin::name())
        return IPC::handleMessageAsync<Messages::NetworkProcessProxy::ReloadExecutionContextsForOrigin>(connection, decoder, this, &NetworkProcessProxy::reloadExecutionContextsForOrigin);
#if USE(RUNNINGBOARD)
    if (decoder.messageName() == Messages::NetworkProcessProxy::WakeUpWebProcessForIPC::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::WakeUpWebProcessForIPC>(connection, decoder, this, &NetworkProcessProxy::wakeUpWebProcessForIPC);
#endif
#if ENABLE(NETWORK_ISSUE_REPORTING)
    if (decoder.messageName() == Messages::NetworkProcessProxy::ReportNetworkIssue::name())
        return IPC::handleMessage<Messages::NetworkProcessProxy::ReportNetworkIssue>(connection, decoder, this, &NetworkProcessProxy::reportNetworkIssue);
#endif
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool NetworkProcessProxy::didReceiveSyncNetworkProcessProxyMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::NetworkProcessProxy::TestProcessIncomingSyncMessagesWhenWaitingForSyncReply::name())
        return IPC::handleMessageSynchronous<Messages::NetworkProcessProxy::TestProcessIncomingSyncMessagesWhenWaitingForSyncReply>(connection, decoder, replyEncoder, this, &NetworkProcessProxy::testProcessIncomingSyncMessagesWhenWaitingForSyncReply);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DidReceiveAuthenticationChallenge>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DidReceiveAuthenticationChallenge::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_NegotiatedLegacyTLS>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::NegotiatedLegacyTLS::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DidNegotiateModernTLS>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DidNegotiateModernTLS::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DidBlockLoadToKnownTracker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DidBlockLoadToKnownTracker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::TestProcessIncomingSyncMessagesWhenWaitingForSyncReply::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::TestProcessIncomingSyncMessagesWhenWaitingForSyncReply::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_TerminateUnresponsiveServiceWorkerProcesses>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::TerminateUnresponsiveServiceWorkerProcesses::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_LogDiagnosticMessage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::LogDiagnosticMessage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_LogDiagnosticMessageWithResult>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::LogDiagnosticMessageWithResult::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_LogDiagnosticMessageWithValue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::LogDiagnosticMessageWithValue::Arguments>(globalObject, decoder);
}
#if ENABLE(TRACKING_PREVENTION)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_LogTestingEvent>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::LogTestingEvent::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_NotifyResourceLoadStatisticsProcessed>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::NotifyResourceLoadStatisticsProcessed::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_NotifyWebsiteDataDeletionForRegistrableDomainsFinished>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::NotifyWebsiteDataDeletionForRegistrableDomainsFinished::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_NotifyWebsiteDataScanForRegistrableDomainsFinished>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::NotifyWebsiteDataScanForRegistrableDomainsFinished::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_RequestStorageAccessConfirm>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::RequestStorageAccessConfirm::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_RequestStorageAccessConfirm>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::RequestStorageAccessConfirm::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DeleteWebsiteDataInUIProcessForRegistrableDomains>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DeleteWebsiteDataInUIProcessForRegistrableDomains::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_DeleteWebsiteDataInUIProcessForRegistrableDomains>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DeleteWebsiteDataInUIProcessForRegistrableDomains::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DidCommitCrossSiteLoadWithDataTransferFromPrevalentResource>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DidCommitCrossSiteLoadWithDataTransferFromPrevalentResource::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_SetDomainsWithUserInteraction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::SetDomainsWithUserInteraction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_SetDomainsWithCrossPageStorageAccess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::SetDomainsWithCrossPageStorageAccess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_SetDomainsWithCrossPageStorageAccess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::SetDomainsWithCrossPageStorageAccess::ReplyArguments>(globalObject, decoder);
}
#endif
#if ENABLE(CONTENT_EXTENSIONS)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_ContentExtensionRules>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::ContentExtensionRules::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_TerminateWebProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::TerminateWebProcess::Arguments>(globalObject, decoder);
}
#if ENABLE(SERVICE_WORKER)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_StartServiceWorkerBackgroundProcessing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::StartServiceWorkerBackgroundProcessing::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_EndServiceWorkerBackgroundProcessing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::EndServiceWorkerBackgroundProcessing::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_RequestBackgroundFetchPermission>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::RequestBackgroundFetchPermission::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_RequestBackgroundFetchPermission>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::RequestBackgroundFetchPermission::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_NotifyBackgroundFetchChange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::NotifyBackgroundFetchChange::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_EstablishRemoteWorkerContextConnectionToNetworkProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::EstablishRemoteWorkerContextConnectionToNetworkProcess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_EstablishRemoteWorkerContextConnectionToNetworkProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::EstablishRemoteWorkerContextConnectionToNetworkProcess::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_RemoteWorkerContextConnectionNoLongerNeeded>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::RemoteWorkerContextConnectionNoLongerNeeded::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_RegisterRemoteWorkerClientProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::RegisterRemoteWorkerClientProcess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_UnregisterRemoteWorkerClientProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::UnregisterRemoteWorkerClientProcess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_SetWebProcessHasUploads>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::SetWebProcessHasUploads::Arguments>(globalObject, decoder);
}
#if ENABLE(APP_BOUND_DOMAINS)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_GetAppBoundDomains>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::GetAppBoundDomains::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_GetAppBoundDomains>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::GetAppBoundDomains::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_RequestStorageSpace>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::RequestStorageSpace::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_RequestStorageSpace>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::RequestStorageSpace::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_IncreaseQuota>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::IncreaseQuota::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_ResourceLoadDidSendRequest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::ResourceLoadDidSendRequest::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_ResourceLoadDidPerformHTTPRedirection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::ResourceLoadDidPerformHTTPRedirection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_ResourceLoadDidReceiveChallenge>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::ResourceLoadDidReceiveChallenge::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_ResourceLoadDidReceiveResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::ResourceLoadDidReceiveResponse::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_ResourceLoadDidCompleteWithError>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::ResourceLoadDidCompleteWithError::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_TriggerBrowsingContextGroupSwitchForNavigation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::TriggerBrowsingContextGroupSwitchForNavigation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_TriggerBrowsingContextGroupSwitchForNavigation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::TriggerBrowsingContextGroupSwitchForNavigation::ReplyArguments>(globalObject, decoder);
}
#if USE(SOUP)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DidExceedMemoryLimit>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DidExceedMemoryLimit::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(APPLE_PAY_REMOTE_UI_USES_SCENE)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_GetWindowSceneIdentifierForPaymentPresentation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::GetWindowSceneIdentifierForPaymentPresentation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_GetWindowSceneIdentifierForPaymentPresentation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::GetWindowSceneIdentifierForPaymentPresentation::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DataTaskReceivedChallenge>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DataTaskReceivedChallenge::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_DataTaskReceivedChallenge>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DataTaskReceivedChallenge::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DataTaskWillPerformHTTPRedirection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DataTaskWillPerformHTTPRedirection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_DataTaskWillPerformHTTPRedirection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DataTaskWillPerformHTTPRedirection::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DataTaskDidReceiveResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DataTaskDidReceiveResponse::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_DataTaskDidReceiveResponse>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DataTaskDidReceiveResponse::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DataTaskDidReceiveData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DataTaskDidReceiveData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DataTaskDidCompleteWithError>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DataTaskDidCompleteWithError::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_OpenWindowFromServiceWorker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::OpenWindowFromServiceWorker::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_OpenWindowFromServiceWorker>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::OpenWindowFromServiceWorker::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_NavigateServiceWorkerClient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::NavigateServiceWorkerClient::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_NavigateServiceWorkerClient>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::NavigateServiceWorkerClient::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_ReportConsoleMessage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::ReportConsoleMessage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_CookiesDidChange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::CookiesDidChange::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_DeleteWebsiteDataInWebProcessesForOrigin>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DeleteWebsiteDataInWebProcessesForOrigin::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_DeleteWebsiteDataInWebProcessesForOrigin>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::DeleteWebsiteDataInWebProcessesForOrigin::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_ReloadExecutionContextsForOrigin>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::ReloadExecutionContextsForOrigin::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::NetworkProcessProxy_ReloadExecutionContextsForOrigin>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::ReloadExecutionContextsForOrigin::ReplyArguments>(globalObject, decoder);
}
#if USE(RUNNINGBOARD)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_WakeUpWebProcessForIPC>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::WakeUpWebProcessForIPC::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(NETWORK_ISSUE_REPORTING)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::NetworkProcessProxy_ReportNetworkIssue>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::NetworkProcessProxy::ReportNetworkIssue::Arguments>(globalObject, decoder);
}
#endif

}

#endif

