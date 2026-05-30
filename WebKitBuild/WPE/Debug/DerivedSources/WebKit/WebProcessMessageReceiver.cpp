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
#include "WebProcess.h"

#if PLATFORM(COCOA)
#include "AccessibilityPreferences.h" // NOLINT
#endif
#include "ArgumentCoders.h" // NOLINT
#include "CacheModel.h" // NOLINT
#include "DataReference.h" // NOLINT
#include "Decoder.h" // NOLINT
#if ENABLE(GAMEPAD)
#include "GamepadData.h" // NOLINT
#endif
#include "HandleMessage.h" // NOLINT
#include "IdentifierTypes.h" // NOLINT
#if (ENABLE(MEDIA_STREAM) && ENABLE(SANDBOX_EXTENSIONS))
#include "MediaDeviceSandboxExtensions.h" // NOLINT
#endif
#include "RemoteWorkerInitializationData.h" // NOLINT
#include "RemoteWorkerType.h" // NOLINT
#include "SandboxExtension.h" // NOLINT
#if HAVE(AUDIO_COMPONENT_SERVER_REGISTRATIONS)
#include "SharedBufferReference.h" // NOLINT
#endif
#include "TextCheckerState.h" // NOLINT
#include "UserData.h" // NOLINT
#if PLATFORM(GTK) || PLATFORM(WPE)
#include "UserMessage.h" // NOLINT
#endif
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebPageCreationParameters.h" // NOLINT
#include "WebPageProxyIdentifier.h" // NOLINT
#include "WebPreferencesStore.h" // NOLINT
#include "WebProcessCreationParameters.h" // NOLINT
#include "WebProcessDataStoreParameters.h" // NOLINT
#include "WebProcessMessages.h" // NOLINT
#include "WebsiteData.h" // NOLINT
#include "WebsiteDataType.h" // NOLINT
#include <WebCore/BackForwardItemIdentifier.h> // NOLINT
#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
#include <WebCore/CaptionUserPreferences.h> // NOLINT
#endif
#include <WebCore/ClientOrigin.h> // NOLINT
#if HAVE(CVDISPLAYLINK)
#include <WebCore/DisplayUpdate.h> // NOLINT
#endif
#include <WebCore/FrameIdentifier.h> // NOLINT
#if ENABLE(GAMEPAD)
#include <WebCore/GamepadProviderClient.h> // NOLINT
#endif
#include <WebCore/MessageWithMessagePorts.h> // NOLINT
#if ENABLE(MEDIA_STREAM)
#include <WebCore/MockMediaDevice.h> // NOLINT
#endif
#if ENABLE(TRACKING_PREVENTION)
#include <WebCore/NetworkStorageSession.h> // NOLINT
#endif
#include <WebCore/PageIdentifier.h> // NOLINT
#include <WebCore/PrewarmInformation.h> // NOLINT
#include <WebCore/ProcessQualified.h> // NOLINT
#include <WebCore/RegistrableDomain.h> // NOLINT
#include <WebCore/RenderTreeAsText.h> // NOLINT
#if PLATFORM(COCOA)
#include <WebCore/ScreenProperties.h> // NOLINT
#endif
#include <WebCore/ScriptExecutionContextIdentifier.h> // NOLINT
#include <WebCore/SecurityOriginData.h> // NOLINT
#include <optional> // NOLINT
#if PLATFORM(IOS_FAMILY)
#include <pal/system/ios/UserInterfaceIdiom.h> // NOLINT
#endif
#if ENABLE(TRACKING_PREVENTION)
#include <wtf/HashMap.h> // NOLINT
#endif
#if ENABLE(TRACKING_PREVENTION)
#include <wtf/HashSet.h> // NOLINT
#endif
#include <wtf/MonotonicTime.h> // NOLINT
#include <wtf/ObjectIdentifier.h> // NOLINT
#include <wtf/OptionSet.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/WallTime.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebProcess::didReceiveWebProcessMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::WebProcess::InitializeWebProcess::name())
        return IPC::handleMessage<Messages::WebProcess::InitializeWebProcess>(connection, decoder, this, &WebProcess::initializeWebProcess);
    if (decoder.messageName() == Messages::WebProcess::SetWebsiteDataStoreParameters::name())
        return IPC::handleMessage<Messages::WebProcess::SetWebsiteDataStoreParameters>(connection, decoder, this, &WebProcess::setWebsiteDataStoreParameters);
    if (decoder.messageName() == Messages::WebProcess::CreateWebPage::name())
        return IPC::handleMessage<Messages::WebProcess::CreateWebPage>(connection, decoder, this, &WebProcess::createWebPage);
    if (decoder.messageName() == Messages::WebProcess::PrewarmWithDomainInformation::name())
        return IPC::handleMessage<Messages::WebProcess::PrewarmWithDomainInformation>(connection, decoder, this, &WebProcess::prewarmWithDomainInformation);
    if (decoder.messageName() == Messages::WebProcess::SetCacheModel::name())
        return IPC::handleMessage<Messages::WebProcess::SetCacheModel>(connection, decoder, this, &WebProcess::setCacheModel);
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsEmptyDocument::name())
        return IPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsEmptyDocument>(connection, decoder, this, &WebProcess::registerURLSchemeAsEmptyDocument);
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsSecure::name())
        return IPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsSecure>(connection, decoder, this, &WebProcess::registerURLSchemeAsSecure);
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsBypassingContentSecurityPolicy::name())
        return IPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsBypassingContentSecurityPolicy>(connection, decoder, this, &WebProcess::registerURLSchemeAsBypassingContentSecurityPolicy);
    if (decoder.messageName() == Messages::WebProcess::SetDomainRelaxationForbiddenForURLScheme::name())
        return IPC::handleMessage<Messages::WebProcess::SetDomainRelaxationForbiddenForURLScheme>(connection, decoder, this, &WebProcess::setDomainRelaxationForbiddenForURLScheme);
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsLocal::name())
        return IPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsLocal>(connection, decoder, this, &WebProcess::registerURLSchemeAsLocal);
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsNoAccess::name())
        return IPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsNoAccess>(connection, decoder, this, &WebProcess::registerURLSchemeAsNoAccess);
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsDisplayIsolated::name())
        return IPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsDisplayIsolated>(connection, decoder, this, &WebProcess::registerURLSchemeAsDisplayIsolated);
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsCORSEnabled::name())
        return IPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsCORSEnabled>(connection, decoder, this, &WebProcess::registerURLSchemeAsCORSEnabled);
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsCachePartitioned::name())
        return IPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsCachePartitioned>(connection, decoder, this, &WebProcess::registerURLSchemeAsCachePartitioned);
    if (decoder.messageName() == Messages::WebProcess::RegisterURLSchemeAsCanDisplayOnlyIfCanRequest::name())
        return IPC::handleMessage<Messages::WebProcess::RegisterURLSchemeAsCanDisplayOnlyIfCanRequest>(connection, decoder, this, &WebProcess::registerURLSchemeAsCanDisplayOnlyIfCanRequest);
    if (decoder.messageName() == Messages::WebProcess::SetDefaultRequestTimeoutInterval::name())
        return IPC::handleMessage<Messages::WebProcess::SetDefaultRequestTimeoutInterval>(connection, decoder, this, &WebProcess::setDefaultRequestTimeoutInterval);
    if (decoder.messageName() == Messages::WebProcess::SetAlwaysUsesComplexTextCodePath::name())
        return IPC::handleMessage<Messages::WebProcess::SetAlwaysUsesComplexTextCodePath>(connection, decoder, this, &WebProcess::setAlwaysUsesComplexTextCodePath);
    if (decoder.messageName() == Messages::WebProcess::SetDisableFontSubpixelAntialiasingForTesting::name())
        return IPC::handleMessage<Messages::WebProcess::SetDisableFontSubpixelAntialiasingForTesting>(connection, decoder, this, &WebProcess::setDisableFontSubpixelAntialiasingForTesting);
    if (decoder.messageName() == Messages::WebProcess::SetTrackingPreventionEnabled::name())
        return IPC::handleMessage<Messages::WebProcess::SetTrackingPreventionEnabled>(connection, decoder, this, &WebProcess::setTrackingPreventionEnabled);
    if (decoder.messageName() == Messages::WebProcess::ClearResourceLoadStatistics::name())
        return IPC::handleMessage<Messages::WebProcess::ClearResourceLoadStatistics>(connection, decoder, this, &WebProcess::clearResourceLoadStatistics);
    if (decoder.messageName() == Messages::WebProcess::UserPreferredLanguagesChanged::name())
        return IPC::handleMessage<Messages::WebProcess::UserPreferredLanguagesChanged>(connection, decoder, this, &WebProcess::userPreferredLanguagesChanged);
    if (decoder.messageName() == Messages::WebProcess::FullKeyboardAccessModeChanged::name())
        return IPC::handleMessage<Messages::WebProcess::FullKeyboardAccessModeChanged>(connection, decoder, this, &WebProcess::fullKeyboardAccessModeChanged);
#if HAVE(MOUSE_DEVICE_OBSERVATION)
    if (decoder.messageName() == Messages::WebProcess::SetHasMouseDevice::name())
        return IPC::handleMessage<Messages::WebProcess::SetHasMouseDevice>(connection, decoder, this, &WebProcess::setHasMouseDevice);
#endif
#if HAVE(STYLUS_DEVICE_OBSERVATION)
    if (decoder.messageName() == Messages::WebProcess::SetHasStylusDevice::name())
        return IPC::handleMessage<Messages::WebProcess::SetHasStylusDevice>(connection, decoder, this, &WebProcess::setHasStylusDevice);
#endif
    if (decoder.messageName() == Messages::WebProcess::StartMemorySampler::name())
        return IPC::handleMessage<Messages::WebProcess::StartMemorySampler>(connection, decoder, this, &WebProcess::startMemorySampler);
    if (decoder.messageName() == Messages::WebProcess::StopMemorySampler::name())
        return IPC::handleMessage<Messages::WebProcess::StopMemorySampler>(connection, decoder, this, &WebProcess::stopMemorySampler);
    if (decoder.messageName() == Messages::WebProcess::SetTextCheckerState::name())
        return IPC::handleMessage<Messages::WebProcess::SetTextCheckerState>(connection, decoder, this, &WebProcess::setTextCheckerState);
    if (decoder.messageName() == Messages::WebProcess::SetEnhancedAccessibility::name())
        return IPC::handleMessage<Messages::WebProcess::SetEnhancedAccessibility>(connection, decoder, this, &WebProcess::setEnhancedAccessibility);
    if (decoder.messageName() == Messages::WebProcess::GarbageCollectJavaScriptObjects::name())
        return IPC::handleMessage<Messages::WebProcess::GarbageCollectJavaScriptObjects>(connection, decoder, this, &WebProcess::garbageCollectJavaScriptObjects);
    if (decoder.messageName() == Messages::WebProcess::SetJavaScriptGarbageCollectorTimerEnabled::name())
        return IPC::handleMessage<Messages::WebProcess::SetJavaScriptGarbageCollectorTimerEnabled>(connection, decoder, this, &WebProcess::setJavaScriptGarbageCollectorTimerEnabled);
    if (decoder.messageName() == Messages::WebProcess::SetInjectedBundleParameter::name())
        return IPC::handleMessage<Messages::WebProcess::SetInjectedBundleParameter>(connection, decoder, this, &WebProcess::setInjectedBundleParameter);
    if (decoder.messageName() == Messages::WebProcess::SetInjectedBundleParameters::name())
        return IPC::handleMessage<Messages::WebProcess::SetInjectedBundleParameters>(connection, decoder, this, &WebProcess::setInjectedBundleParameters);
    if (decoder.messageName() == Messages::WebProcess::HandleInjectedBundleMessage::name())
        return IPC::handleMessage<Messages::WebProcess::HandleInjectedBundleMessage>(connection, decoder, this, &WebProcess::handleInjectedBundleMessage);
    if (decoder.messageName() == Messages::WebProcess::FetchWebsiteData::name())
        return IPC::handleMessageAsync<Messages::WebProcess::FetchWebsiteData>(connection, decoder, this, &WebProcess::fetchWebsiteData);
    if (decoder.messageName() == Messages::WebProcess::DeleteWebsiteData::name())
        return IPC::handleMessageAsync<Messages::WebProcess::DeleteWebsiteData>(connection, decoder, this, &WebProcess::deleteWebsiteData);
    if (decoder.messageName() == Messages::WebProcess::DeleteWebsiteDataForOrigins::name())
        return IPC::handleMessageAsync<Messages::WebProcess::DeleteWebsiteDataForOrigins>(connection, decoder, this, &WebProcess::deleteWebsiteDataForOrigins);
    if (decoder.messageName() == Messages::WebProcess::DeleteWebsiteDataForOrigin::name())
        return IPC::handleMessageAsync<Messages::WebProcess::DeleteWebsiteDataForOrigin>(connection, decoder, this, &WebProcess::deleteWebsiteDataForOrigin);
    if (decoder.messageName() == Messages::WebProcess::ReloadExecutionContextsForOrigin::name())
        return IPC::handleMessageAsync<Messages::WebProcess::ReloadExecutionContextsForOrigin>(connection, decoder, this, &WebProcess::reloadExecutionContextsForOrigin);
    if (decoder.messageName() == Messages::WebProcess::DeleteAllCookies::name())
        return IPC::handleMessageAsync<Messages::WebProcess::DeleteAllCookies>(connection, decoder, this, &WebProcess::deleteAllCookies);
    if (decoder.messageName() == Messages::WebProcess::SetHiddenPageDOMTimerThrottlingIncreaseLimit::name())
        return IPC::handleMessage<Messages::WebProcess::SetHiddenPageDOMTimerThrottlingIncreaseLimit>(connection, decoder, this, &WebProcess::setHiddenPageDOMTimerThrottlingIncreaseLimit);
    if (decoder.messageName() == Messages::WebProcess::SetMemoryCacheDisabled::name())
        return IPC::handleMessage<Messages::WebProcess::SetMemoryCacheDisabled>(connection, decoder, this, &WebProcess::setMemoryCacheDisabled);
#if ENABLE(SERVICE_CONTROLS)
    if (decoder.messageName() == Messages::WebProcess::SetEnabledServices::name())
        return IPC::handleMessage<Messages::WebProcess::SetEnabledServices>(connection, decoder, this, &WebProcess::setEnabledServices);
#endif
    if (decoder.messageName() == Messages::WebProcess::EnsureAutomationSessionProxy::name())
        return IPC::handleMessage<Messages::WebProcess::EnsureAutomationSessionProxy>(connection, decoder, this, &WebProcess::ensureAutomationSessionProxy);
    if (decoder.messageName() == Messages::WebProcess::DestroyAutomationSessionProxy::name())
        return IPC::handleMessage<Messages::WebProcess::DestroyAutomationSessionProxy>(connection, decoder, this, &WebProcess::destroyAutomationSessionProxy);
    if (decoder.messageName() == Messages::WebProcess::PrepareToSuspend::name())
        return IPC::handleMessageAsync<Messages::WebProcess::PrepareToSuspend>(connection, decoder, this, &WebProcess::prepareToSuspend);
    if (decoder.messageName() == Messages::WebProcess::ProcessDidResume::name())
        return IPC::handleMessage<Messages::WebProcess::ProcessDidResume>(connection, decoder, this, &WebProcess::processDidResume);
    if (decoder.messageName() == Messages::WebProcess::BackgroundResponsivenessPing::name())
        return IPC::handleMessage<Messages::WebProcess::BackgroundResponsivenessPing>(connection, decoder, this, &WebProcess::backgroundResponsivenessPing);
#if ENABLE(GAMEPAD)
    if (decoder.messageName() == Messages::WebProcess::SetInitialGamepads::name())
        return IPC::handleMessage<Messages::WebProcess::SetInitialGamepads>(connection, decoder, this, &WebProcess::setInitialGamepads);
    if (decoder.messageName() == Messages::WebProcess::GamepadConnected::name())
        return IPC::handleMessage<Messages::WebProcess::GamepadConnected>(connection, decoder, this, &WebProcess::gamepadConnected);
    if (decoder.messageName() == Messages::WebProcess::GamepadDisconnected::name())
        return IPC::handleMessage<Messages::WebProcess::GamepadDisconnected>(connection, decoder, this, &WebProcess::gamepadDisconnected);
#endif
    if (decoder.messageName() == Messages::WebProcess::EstablishRemoteWorkerContextConnectionToNetworkProcess::name())
        return IPC::handleMessageAsync<Messages::WebProcess::EstablishRemoteWorkerContextConnectionToNetworkProcess>(connection, decoder, this, &WebProcess::establishRemoteWorkerContextConnectionToNetworkProcess);
    if (decoder.messageName() == Messages::WebProcess::SetHasSuspendedPageProxy::name())
        return IPC::handleMessage<Messages::WebProcess::SetHasSuspendedPageProxy>(connection, decoder, this, &WebProcess::setHasSuspendedPageProxy);
    if (decoder.messageName() == Messages::WebProcess::SetIsInProcessCache::name())
        return IPC::handleMessage<Messages::WebProcess::SetIsInProcessCache>(connection, decoder, this, &WebProcess::setIsInProcessCache);
    if (decoder.messageName() == Messages::WebProcess::MarkIsNoLongerPrewarmed::name())
        return IPC::handleMessage<Messages::WebProcess::MarkIsNoLongerPrewarmed>(connection, decoder, this, &WebProcess::markIsNoLongerPrewarmed);
    if (decoder.messageName() == Messages::WebProcess::GetActivePagesOriginsForTesting::name())
        return IPC::handleMessageAsync<Messages::WebProcess::GetActivePagesOriginsForTesting>(connection, decoder, this, &WebProcess::getActivePagesOriginsForTesting);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::WebProcess::SetScreenProperties::name())
        return IPC::handleMessage<Messages::WebProcess::SetScreenProperties>(connection, decoder, this, &WebProcess::setScreenProperties);
#endif
#if PLATFORM(MAC)
    if (decoder.messageName() == Messages::WebProcess::ScrollerStylePreferenceChanged::name())
        return IPC::handleMessage<Messages::WebProcess::ScrollerStylePreferenceChanged>(connection, decoder, this, &WebProcess::scrollerStylePreferenceChanged);
    if (decoder.messageName() == Messages::WebProcess::DisplayConfigurationChanged::name())
        return IPC::handleMessage<Messages::WebProcess::DisplayConfigurationChanged>(connection, decoder, this, &WebProcess::displayConfigurationChanged);
#endif
#if PLATFORM(IOS_FAMILY)
    if (decoder.messageName() == Messages::WebProcess::UserInterfaceIdiomDidChange::name())
        return IPC::handleMessage<Messages::WebProcess::UserInterfaceIdiomDidChange>(connection, decoder, this, &WebProcess::userInterfaceIdiomDidChange);
#endif
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
    if (decoder.messageName() == Messages::WebProcess::BacklightLevelDidChange::name())
        return IPC::handleMessage<Messages::WebProcess::BacklightLevelDidChange>(connection, decoder, this, &WebProcess::backlightLevelDidChange);
#endif
#if PLATFORM(MAC) || PLATFORM(MACCATALYST)
    if (decoder.messageName() == Messages::WebProcess::ColorPreferencesDidChange::name())
        return IPC::handleMessage<Messages::WebProcess::ColorPreferencesDidChange>(connection, decoder, this, &WebProcess::colorPreferencesDidChange);
#endif
    if (decoder.messageName() == Messages::WebProcess::IsJITEnabled::name())
        return IPC::handleMessageAsync<Messages::WebProcess::IsJITEnabled>(connection, decoder, this, &WebProcess::isJITEnabled);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::WebProcess::SetMediaMIMETypes::name())
        return IPC::handleMessage<Messages::WebProcess::SetMediaMIMETypes>(connection, decoder, this, &WebProcess::setMediaMIMETypes);
#endif
#if (PLATFORM(COCOA) && ENABLE(REMOTE_INSPECTOR))
    if (decoder.messageName() == Messages::WebProcess::EnableRemoteWebInspector::name())
        return IPC::handleMessage<Messages::WebProcess::EnableRemoteWebInspector>(connection, decoder, this, &WebProcess::enableRemoteWebInspector);
#endif
#if ENABLE(MEDIA_STREAM)
    if (decoder.messageName() == Messages::WebProcess::AddMockMediaDevice::name())
        return IPC::handleMessage<Messages::WebProcess::AddMockMediaDevice>(connection, decoder, this, &WebProcess::addMockMediaDevice);
    if (decoder.messageName() == Messages::WebProcess::ClearMockMediaDevices::name())
        return IPC::handleMessage<Messages::WebProcess::ClearMockMediaDevices>(connection, decoder, this, &WebProcess::clearMockMediaDevices);
    if (decoder.messageName() == Messages::WebProcess::RemoveMockMediaDevice::name())
        return IPC::handleMessage<Messages::WebProcess::RemoveMockMediaDevice>(connection, decoder, this, &WebProcess::removeMockMediaDevice);
    if (decoder.messageName() == Messages::WebProcess::SetMockMediaDeviceIsEphemeral::name())
        return IPC::handleMessage<Messages::WebProcess::SetMockMediaDeviceIsEphemeral>(connection, decoder, this, &WebProcess::setMockMediaDeviceIsEphemeral);
    if (decoder.messageName() == Messages::WebProcess::ResetMockMediaDevices::name())
        return IPC::handleMessage<Messages::WebProcess::ResetMockMediaDevices>(connection, decoder, this, &WebProcess::resetMockMediaDevices);
#endif
#if (ENABLE(MEDIA_STREAM) && ENABLE(SANDBOX_EXTENSIONS))
    if (decoder.messageName() == Messages::WebProcess::GrantUserMediaDeviceSandboxExtensions::name())
        return IPC::handleMessage<Messages::WebProcess::GrantUserMediaDeviceSandboxExtensions>(connection, decoder, this, &WebProcess::grantUserMediaDeviceSandboxExtensions);
    if (decoder.messageName() == Messages::WebProcess::RevokeUserMediaDeviceSandboxExtensions::name())
        return IPC::handleMessage<Messages::WebProcess::RevokeUserMediaDeviceSandboxExtensions>(connection, decoder, this, &WebProcess::revokeUserMediaDeviceSandboxExtensions);
#endif
    if (decoder.messageName() == Messages::WebProcess::ClearCurrentModifierStateForTesting::name())
        return IPC::handleMessage<Messages::WebProcess::ClearCurrentModifierStateForTesting>(connection, decoder, this, &WebProcess::clearCurrentModifierStateForTesting);
    if (decoder.messageName() == Messages::WebProcess::SetBackForwardCacheCapacity::name())
        return IPC::handleMessage<Messages::WebProcess::SetBackForwardCacheCapacity>(connection, decoder, this, &WebProcess::setBackForwardCacheCapacity);
    if (decoder.messageName() == Messages::WebProcess::ClearCachedPage::name())
        return IPC::handleMessageAsync<Messages::WebProcess::ClearCachedPage>(connection, decoder, this, &WebProcess::clearCachedPage);
#if PLATFORM(GTK) || PLATFORM(WPE)
    if (decoder.messageName() == Messages::WebProcess::SendMessageToWebProcessExtension::name())
        return IPC::handleMessage<Messages::WebProcess::SendMessageToWebProcessExtension>(connection, decoder, this, &WebProcess::sendMessageToWebProcessExtension);
#endif
#if ENABLE(TRACKING_PREVENTION)
    if (decoder.messageName() == Messages::WebProcess::SeedResourceLoadStatisticsForTesting::name())
        return IPC::handleMessageAsync<Messages::WebProcess::SeedResourceLoadStatisticsForTesting>(connection, decoder, this, &WebProcess::seedResourceLoadStatisticsForTesting);
    if (decoder.messageName() == Messages::WebProcess::SetThirdPartyCookieBlockingMode::name())
        return IPC::handleMessageAsync<Messages::WebProcess::SetThirdPartyCookieBlockingMode>(connection, decoder, this, &WebProcess::setThirdPartyCookieBlockingMode);
    if (decoder.messageName() == Messages::WebProcess::SetDomainsWithUserInteraction::name())
        return IPC::handleMessage<Messages::WebProcess::SetDomainsWithUserInteraction>(connection, decoder, this, &WebProcess::setDomainsWithUserInteraction);
    if (decoder.messageName() == Messages::WebProcess::SetDomainsWithCrossPageStorageAccess::name())
        return IPC::handleMessageAsync<Messages::WebProcess::SetDomainsWithCrossPageStorageAccess>(connection, decoder, this, &WebProcess::setDomainsWithCrossPageStorageAccess);
    if (decoder.messageName() == Messages::WebProcess::SendResourceLoadStatisticsDataImmediately::name())
        return IPC::handleMessageAsync<Messages::WebProcess::SendResourceLoadStatisticsDataImmediately>(connection, decoder, this, &WebProcess::sendResourceLoadStatisticsDataImmediately);
#endif
    if (decoder.messageName() == Messages::WebProcess::GrantAccessToAssetServices::name())
        return IPC::handleMessage<Messages::WebProcess::GrantAccessToAssetServices>(connection, decoder, this, &WebProcess::grantAccessToAssetServices);
    if (decoder.messageName() == Messages::WebProcess::RevokeAccessToAssetServices::name())
        return IPC::handleMessage<Messages::WebProcess::RevokeAccessToAssetServices>(connection, decoder, this, &WebProcess::revokeAccessToAssetServices);
    if (decoder.messageName() == Messages::WebProcess::SwitchFromStaticFontRegistryToUserFontRegistry::name())
        return IPC::handleMessage<Messages::WebProcess::SwitchFromStaticFontRegistryToUserFontRegistry>(connection, decoder, this, &WebProcess::switchFromStaticFontRegistryToUserFontRegistry);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::WebProcess::DisableURLSchemeCheckInDataDetectors::name())
        return IPC::handleMessage<Messages::WebProcess::DisableURLSchemeCheckInDataDetectors>(connection, decoder, this, &WebProcess::disableURLSchemeCheckInDataDetectors);
    if (decoder.messageName() == Messages::WebProcess::UnblockServicesRequiredByAccessibility::name())
        return IPC::handleMessage<Messages::WebProcess::UnblockServicesRequiredByAccessibility>(connection, decoder, this, &WebProcess::unblockServicesRequiredByAccessibility);
#endif
#if (PLATFORM(COCOA) && ENABLE(CFPREFS_DIRECT_MODE))
    if (decoder.messageName() == Messages::WebProcess::NotifyPreferencesChanged::name())
        return IPC::handleMessage<Messages::WebProcess::NotifyPreferencesChanged>(connection, decoder, this, &WebProcess::notifyPreferencesChanged);
#endif
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::WebProcess::PowerSourceDidChange::name())
        return IPC::handleMessage<Messages::WebProcess::PowerSourceDidChange>(connection, decoder, this, &WebProcess::powerSourceDidChange);
#endif
#if PLATFORM(GTK) && !USE(GTK4)
    if (decoder.messageName() == Messages::WebProcess::SetUseSystemAppearanceForScrollbars::name())
        return IPC::handleMessage<Messages::WebProcess::SetUseSystemAppearanceForScrollbars>(connection, decoder, this, &WebProcess::setUseSystemAppearanceForScrollbars);
#endif
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::WebProcess::DidWriteToPasteboardAsynchronously::name())
        return IPC::handleMessage<Messages::WebProcess::DidWriteToPasteboardAsynchronously>(connection, decoder, this, &WebProcess::didWriteToPasteboardAsynchronously);
#endif
#if HAVE(CVDISPLAYLINK)
    if (decoder.messageName() == Messages::WebProcess::DisplayDidRefresh::name())
        return IPC::handleMessage<Messages::WebProcess::DisplayDidRefresh>(connection, decoder, this, &WebProcess::displayDidRefresh);
#endif
#if PLATFORM(MAC)
    if (decoder.messageName() == Messages::WebProcess::SystemWillPowerOn::name())
        return IPC::handleMessage<Messages::WebProcess::SystemWillPowerOn>(connection, decoder, this, &WebProcess::systemWillPowerOn);
    if (decoder.messageName() == Messages::WebProcess::SystemWillSleep::name())
        return IPC::handleMessage<Messages::WebProcess::SystemWillSleep>(connection, decoder, this, &WebProcess::systemWillSleep);
    if (decoder.messageName() == Messages::WebProcess::SystemDidWake::name())
        return IPC::handleMessage<Messages::WebProcess::SystemDidWake>(connection, decoder, this, &WebProcess::systemDidWake);
#endif
#if HAVE(AUDIO_COMPONENT_SERVER_REGISTRATIONS)
    if (decoder.messageName() == Messages::WebProcess::ConsumeAudioComponentRegistrations::name())
        return IPC::handleMessage<Messages::WebProcess::ConsumeAudioComponentRegistrations>(connection, decoder, this, &WebProcess::consumeAudioComponentRegistrations);
#endif
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::WebProcess::AccessibilityPreferencesDidChange::name())
        return IPC::handleMessage<Messages::WebProcess::AccessibilityPreferencesDidChange>(connection, decoder, this, &WebProcess::accessibilityPreferencesDidChange);
#endif
#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
    if (decoder.messageName() == Messages::WebProcess::SetMediaAccessibilityPreferences::name())
        return IPC::handleMessage<Messages::WebProcess::SetMediaAccessibilityPreferences>(connection, decoder, this, &WebProcess::setMediaAccessibilityPreferences);
#endif
#if PLATFORM(MAC)
    if (decoder.messageName() == Messages::WebProcess::OpenDirectoryCacheInvalidated::name())
        return IPC::handleMessage<Messages::WebProcess::OpenDirectoryCacheInvalidated>(connection, decoder, this, &WebProcess::openDirectoryCacheInvalidated);
#endif
    if (decoder.messageName() == Messages::WebProcess::ReleaseMemory::name())
        return IPC::handleMessageAsync<Messages::WebProcess::ReleaseMemory>(connection, decoder, this, &WebProcess::releaseMemory);
    if (decoder.messageName() == Messages::WebProcess::RemotePostMessage::name())
        return IPC::handleMessage<Messages::WebProcess::RemotePostMessage>(connection, decoder, this, &WebProcess::remotePostMessage);
    if (decoder.messageName() == Messages::WebProcess::AddAllowedFirstPartyForCookies::name())
        return IPC::handleMessage<Messages::WebProcess::AddAllowedFirstPartyForCookies>(connection, decoder, this, &WebProcess::addAllowedFirstPartyForCookies);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool WebProcess::didReceiveSyncWebProcessMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    if (decoder.messageName() == Messages::WebProcess::RenderTreeAsText::name())
        return IPC::handleMessageSynchronous<Messages::WebProcess::RenderTreeAsText>(connection, decoder, replyEncoder, this, &WebProcess::renderTreeAsText);
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

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_InitializeWebProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::InitializeWebProcess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetWebsiteDataStoreParameters>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetWebsiteDataStoreParameters::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_CreateWebPage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::CreateWebPage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_PrewarmWithDomainInformation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::PrewarmWithDomainInformation::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetCacheModel>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetCacheModel::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RegisterURLSchemeAsEmptyDocument>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RegisterURLSchemeAsEmptyDocument::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RegisterURLSchemeAsSecure>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RegisterURLSchemeAsSecure::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RegisterURLSchemeAsBypassingContentSecurityPolicy>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RegisterURLSchemeAsBypassingContentSecurityPolicy::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetDomainRelaxationForbiddenForURLScheme>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetDomainRelaxationForbiddenForURLScheme::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RegisterURLSchemeAsLocal>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RegisterURLSchemeAsLocal::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RegisterURLSchemeAsNoAccess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RegisterURLSchemeAsNoAccess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RegisterURLSchemeAsDisplayIsolated>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RegisterURLSchemeAsDisplayIsolated::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RegisterURLSchemeAsCORSEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RegisterURLSchemeAsCORSEnabled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RegisterURLSchemeAsCachePartitioned>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RegisterURLSchemeAsCachePartitioned::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RegisterURLSchemeAsCanDisplayOnlyIfCanRequest>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RegisterURLSchemeAsCanDisplayOnlyIfCanRequest::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetDefaultRequestTimeoutInterval>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetDefaultRequestTimeoutInterval::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetAlwaysUsesComplexTextCodePath>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetAlwaysUsesComplexTextCodePath::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetDisableFontSubpixelAntialiasingForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetDisableFontSubpixelAntialiasingForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetTrackingPreventionEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetTrackingPreventionEnabled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_ClearResourceLoadStatistics>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ClearResourceLoadStatistics::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_UserPreferredLanguagesChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::UserPreferredLanguagesChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_FullKeyboardAccessModeChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::FullKeyboardAccessModeChanged::Arguments>(globalObject, decoder);
}
#if HAVE(MOUSE_DEVICE_OBSERVATION)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetHasMouseDevice>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetHasMouseDevice::Arguments>(globalObject, decoder);
}
#endif
#if HAVE(STYLUS_DEVICE_OBSERVATION)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetHasStylusDevice>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetHasStylusDevice::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_StartMemorySampler>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::StartMemorySampler::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_StopMemorySampler>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::StopMemorySampler::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetTextCheckerState>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetTextCheckerState::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetEnhancedAccessibility>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetEnhancedAccessibility::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_GarbageCollectJavaScriptObjects>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::GarbageCollectJavaScriptObjects::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetJavaScriptGarbageCollectorTimerEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetJavaScriptGarbageCollectorTimerEnabled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetInjectedBundleParameter>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetInjectedBundleParameter::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetInjectedBundleParameters>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetInjectedBundleParameters::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_HandleInjectedBundleMessage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::HandleInjectedBundleMessage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_FetchWebsiteData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::FetchWebsiteData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_FetchWebsiteData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::FetchWebsiteData::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_DeleteWebsiteData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DeleteWebsiteData::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_DeleteWebsiteData>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DeleteWebsiteData::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_DeleteWebsiteDataForOrigins>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DeleteWebsiteDataForOrigins::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_DeleteWebsiteDataForOrigins>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DeleteWebsiteDataForOrigins::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_DeleteWebsiteDataForOrigin>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DeleteWebsiteDataForOrigin::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_DeleteWebsiteDataForOrigin>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DeleteWebsiteDataForOrigin::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_ReloadExecutionContextsForOrigin>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ReloadExecutionContextsForOrigin::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_ReloadExecutionContextsForOrigin>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ReloadExecutionContextsForOrigin::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_DeleteAllCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DeleteAllCookies::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_DeleteAllCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DeleteAllCookies::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetHiddenPageDOMTimerThrottlingIncreaseLimit>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetHiddenPageDOMTimerThrottlingIncreaseLimit::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetMemoryCacheDisabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetMemoryCacheDisabled::Arguments>(globalObject, decoder);
}
#if ENABLE(SERVICE_CONTROLS)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetEnabledServices>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetEnabledServices::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_EnsureAutomationSessionProxy>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::EnsureAutomationSessionProxy::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_DestroyAutomationSessionProxy>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DestroyAutomationSessionProxy::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_PrepareToSuspend>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::PrepareToSuspend::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_PrepareToSuspend>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::PrepareToSuspend::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_ProcessDidResume>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ProcessDidResume::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_BackgroundResponsivenessPing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::BackgroundResponsivenessPing::Arguments>(globalObject, decoder);
}
#if ENABLE(GAMEPAD)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetInitialGamepads>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetInitialGamepads::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_GamepadConnected>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::GamepadConnected::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_GamepadDisconnected>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::GamepadDisconnected::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_EstablishRemoteWorkerContextConnectionToNetworkProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::EstablishRemoteWorkerContextConnectionToNetworkProcess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_EstablishRemoteWorkerContextConnectionToNetworkProcess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::EstablishRemoteWorkerContextConnectionToNetworkProcess::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetHasSuspendedPageProxy>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetHasSuspendedPageProxy::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetIsInProcessCache>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetIsInProcessCache::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_MarkIsNoLongerPrewarmed>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::MarkIsNoLongerPrewarmed::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_GetActivePagesOriginsForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::GetActivePagesOriginsForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_GetActivePagesOriginsForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::GetActivePagesOriginsForTesting::ReplyArguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetScreenProperties>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetScreenProperties::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(MAC)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_ScrollerStylePreferenceChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ScrollerStylePreferenceChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_DisplayConfigurationChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DisplayConfigurationChanged::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(IOS_FAMILY)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_UserInterfaceIdiomDidChange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::UserInterfaceIdiomDidChange::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_BacklightLevelDidChange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::BacklightLevelDidChange::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(MAC) || PLATFORM(MACCATALYST)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_ColorPreferencesDidChange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ColorPreferencesDidChange::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_IsJITEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::IsJITEnabled::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_IsJITEnabled>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::IsJITEnabled::ReplyArguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetMediaMIMETypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetMediaMIMETypes::Arguments>(globalObject, decoder);
}
#endif
#if (PLATFORM(COCOA) && ENABLE(REMOTE_INSPECTOR))
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_EnableRemoteWebInspector>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::EnableRemoteWebInspector::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(MEDIA_STREAM)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_AddMockMediaDevice>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::AddMockMediaDevice::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_ClearMockMediaDevices>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ClearMockMediaDevices::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RemoveMockMediaDevice>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RemoveMockMediaDevice::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetMockMediaDeviceIsEphemeral>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetMockMediaDeviceIsEphemeral::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_ResetMockMediaDevices>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ResetMockMediaDevices::Arguments>(globalObject, decoder);
}
#endif
#if (ENABLE(MEDIA_STREAM) && ENABLE(SANDBOX_EXTENSIONS))
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_GrantUserMediaDeviceSandboxExtensions>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::GrantUserMediaDeviceSandboxExtensions::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RevokeUserMediaDeviceSandboxExtensions>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RevokeUserMediaDeviceSandboxExtensions::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_ClearCurrentModifierStateForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ClearCurrentModifierStateForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetBackForwardCacheCapacity>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetBackForwardCacheCapacity::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_ClearCachedPage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ClearCachedPage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_ClearCachedPage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ClearCachedPage::ReplyArguments>(globalObject, decoder);
}
#if PLATFORM(GTK) || PLATFORM(WPE)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SendMessageToWebProcessExtension>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SendMessageToWebProcessExtension::Arguments>(globalObject, decoder);
}
#endif
#if ENABLE(TRACKING_PREVENTION)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SeedResourceLoadStatisticsForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SeedResourceLoadStatisticsForTesting::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_SeedResourceLoadStatisticsForTesting>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SeedResourceLoadStatisticsForTesting::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetThirdPartyCookieBlockingMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetThirdPartyCookieBlockingMode::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_SetThirdPartyCookieBlockingMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetThirdPartyCookieBlockingMode::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetDomainsWithUserInteraction>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetDomainsWithUserInteraction::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetDomainsWithCrossPageStorageAccess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetDomainsWithCrossPageStorageAccess::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_SetDomainsWithCrossPageStorageAccess>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetDomainsWithCrossPageStorageAccess::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SendResourceLoadStatisticsDataImmediately>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SendResourceLoadStatisticsDataImmediately::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_SendResourceLoadStatisticsDataImmediately>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SendResourceLoadStatisticsDataImmediately::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_GrantAccessToAssetServices>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::GrantAccessToAssetServices::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RevokeAccessToAssetServices>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RevokeAccessToAssetServices::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SwitchFromStaticFontRegistryToUserFontRegistry>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SwitchFromStaticFontRegistryToUserFontRegistry::Arguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_DisableURLSchemeCheckInDataDetectors>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DisableURLSchemeCheckInDataDetectors::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_UnblockServicesRequiredByAccessibility>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::UnblockServicesRequiredByAccessibility::Arguments>(globalObject, decoder);
}
#endif
#if (PLATFORM(COCOA) && ENABLE(CFPREFS_DIRECT_MODE))
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_NotifyPreferencesChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::NotifyPreferencesChanged::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_PowerSourceDidChange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::PowerSourceDidChange::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(GTK) && !USE(GTK4)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetUseSystemAppearanceForScrollbars>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetUseSystemAppearanceForScrollbars::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_DidWriteToPasteboardAsynchronously>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DidWriteToPasteboardAsynchronously::Arguments>(globalObject, decoder);
}
#endif
#if HAVE(CVDISPLAYLINK)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_DisplayDidRefresh>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::DisplayDidRefresh::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(MAC)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SystemWillPowerOn>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SystemWillPowerOn::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SystemWillSleep>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SystemWillSleep::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SystemDidWake>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SystemDidWake::Arguments>(globalObject, decoder);
}
#endif
#if HAVE(AUDIO_COMPONENT_SERVER_REGISTRATIONS)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_ConsumeAudioComponentRegistrations>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ConsumeAudioComponentRegistrations::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_AccessibilityPreferencesDidChange>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::AccessibilityPreferencesDidChange::Arguments>(globalObject, decoder);
}
#endif
#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_SetMediaAccessibilityPreferences>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::SetMediaAccessibilityPreferences::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(MAC)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_OpenDirectoryCacheInvalidated>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::OpenDirectoryCacheInvalidated::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_ReleaseMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ReleaseMemory::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_ReleaseMemory>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::ReleaseMemory::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RemotePostMessage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RemotePostMessage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_RenderTreeAsText>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RenderTreeAsText::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcess_RenderTreeAsText>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::RenderTreeAsText::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcess_AddAllowedFirstPartyForCookies>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcess::AddAllowedFirstPartyForCookies::Arguments>(globalObject, decoder);
}

}

#endif

