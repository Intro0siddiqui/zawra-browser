/*
 * THIS FILE WAS AUTOMATICALLY GENERATED, DO NOT EDIT.
 *
 * Copyright (C) 2017 Apple Inc. All rights reserved.
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

#include "config.h"
#include "WebPreferencesStore.h"

#include "WebPreferencesDefinitions.h"
#include "WebPreferencesKeys.h"
#include <variant>
#include <wtf/NeverDestroyed.h>

// FIXME: These should added via options in WebPreferences.yaml, rather than hardcoded.
#include <WebCore/DeprecatedGlobalSettings.h>
#include <WebCore/LibWebRTCProvider.h>
#include <WebCore/SecurityOrigin.h>
#include <WebCore/Settings.h>
#include <pal/text/TextEncodingRegistry.h>

namespace WebKit {
using namespace WebCore;

WebPreferencesStore::ValueMap& WebPreferencesStore::defaults()
{
    static NeverDestroyed<ValueMap> defaults;
    if (defaults.get().isEmpty()) {
        defaults.get().set(WebPreferencesKey::acceleratedCompositingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AcceleratedCompositingEnabled)));
        defaults.get().set(WebPreferencesKey::acceleratedCompositingForFixedPositionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AcceleratedCompositingForFixedPositionEnabled)));
        defaults.get().set(WebPreferencesKey::aggressiveTileRetentionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AggressiveTileRetentionEnabled)));
        defaults.get().set(WebPreferencesKey::allowContentSecurityPolicySourceStarToMatchAnyProtocolKey(), Value(bool(DEFAULT_VALUE_FOR_AllowContentSecurityPolicySourceStarToMatchAnyProtocol)));
        defaults.get().set(WebPreferencesKey::allowCrossOriginSubresourcesToAskForCredentialsKey(), Value(bool(DEFAULT_VALUE_FOR_AllowCrossOriginSubresourcesToAskForCredentials)));
        defaults.get().set(WebPreferencesKey::allowDisplayOfInsecureContentKey(), Value(bool(DEFAULT_VALUE_FOR_AllowDisplayOfInsecureContent)));
        defaults.get().set(WebPreferencesKey::allowFileAccessFromFileURLsKey(), Value(bool(DEFAULT_VALUE_FOR_AllowFileAccessFromFileURLs)));
        defaults.get().set(WebPreferencesKey::allowMultiElementImplicitSubmissionKey(), Value(bool(DEFAULT_VALUE_FOR_AllowMultiElementImplicitSubmission)));
        defaults.get().set(WebPreferencesKey::allowRunningOfInsecureContentKey(), Value(bool(DEFAULT_VALUE_FOR_AllowRunningOfInsecureContent)));
        defaults.get().set(WebPreferencesKey::allowSettingAnyXHRHeaderFromFileURLsKey(), Value(bool(DEFAULT_VALUE_FOR_AllowSettingAnyXHRHeaderFromFileURLs)));
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
        defaults.get().set(WebPreferencesKey::allowsAirPlayForMediaPlaybackKey(), Value(bool(DEFAULT_VALUE_FOR_AllowsAirPlayForMediaPlayback)));
#endif
        defaults.get().set(WebPreferencesKey::allowsInlineMediaPlaybackKey(), Value(bool(DEFAULT_VALUE_FOR_AllowsInlineMediaPlayback)));
        defaults.get().set(WebPreferencesKey::allowsInlineMediaPlaybackAfterFullscreenKey(), Value(bool(DEFAULT_VALUE_FOR_AllowsInlineMediaPlaybackAfterFullscreen)));
        defaults.get().set(WebPreferencesKey::allowsPictureInPictureMediaPlaybackKey(), Value(bool(DEFAULT_VALUE_FOR_AllowsPictureInPictureMediaPlayback)));
#if PLATFORM(IOS_FAMILY)
        defaults.get().set(WebPreferencesKey::alternateFormControlDesignEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AlternateFormControlDesignEnabled)));
#endif
#if PLATFORM(IOS_FAMILY)
        defaults.get().set(WebPreferencesKey::alternateFullScreenControlDesignEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AlternateFullScreenControlDesignEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::animatedImageAsyncDecodingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AnimatedImageAsyncDecodingEnabled)));
        defaults.get().set(WebPreferencesKey::appleMailPaginationQuirkEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AppleMailPaginationQuirkEnabled)));
#if ENABLE(APPLE_PAY)
        defaults.get().set(WebPreferencesKey::applePayCapabilityDisclosureAllowedKey(), Value(bool(DEFAULT_VALUE_FOR_ApplePayCapabilityDisclosureAllowed)));
#endif
#if ENABLE(APPLE_PAY)
        defaults.get().set(WebPreferencesKey::applePayEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ApplePayEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::asynchronousSpellCheckingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AsynchronousSpellCheckingEnabled)));
        defaults.get().set(WebPreferencesKey::audioControlsScaleWithPageZoomKey(), Value(bool(DEFAULT_VALUE_FOR_AudioControlsScaleWithPageZoom)));
        defaults.get().set(WebPreferencesKey::authorAndUserStylesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AuthorAndUserStylesEnabled)));
        defaults.get().set(WebPreferencesKey::backspaceKeyNavigationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_BackspaceKeyNavigationEnabled)));
        defaults.get().set(WebPreferencesKey::caretBrowsingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CaretBrowsingEnabled)));
        defaults.get().set(WebPreferencesKey::colorFilterEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ColorFilterEnabled)));
        defaults.get().set(WebPreferencesKey::constantPropertiesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ConstantPropertiesEnabled)));
#if ENABLE(CONTENT_CHANGE_OBSERVER)
        defaults.get().set(WebPreferencesKey::contentChangeObserverEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ContentChangeObserverEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::contentDispositionAttachmentSandboxEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ContentDispositionAttachmentSandboxEnabled)));
#if ENABLE(CONTEXT_MENU_QR_CODE_DETECTION)
        defaults.get().set(WebPreferencesKey::contextMenuQRCodeDetectionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ContextMenuQRCodeDetectionEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::cursiveFontFamilyKey(), Value(makeString(DEFAULT_VALUE_FOR_CursiveFontFamily)));
        defaults.get().set(WebPreferencesKey::dnsPrefetchingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DNSPrefetchingEnabled)));
        defaults.get().set(WebPreferencesKey::domPasteAllowedKey(), Value(bool(DEFAULT_VALUE_FOR_DOMPasteAllowed)));
#if ENABLE(DATA_DETECTION)
        defaults.get().set(WebPreferencesKey::dataDetectorTypesKey(), Value(uint32_t(DEFAULT_VALUE_FOR_DataDetectorTypes)));
#endif
        defaults.get().set(WebPreferencesKey::databasesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DatabasesEnabled)));
        defaults.get().set(WebPreferencesKey::defaultFixedFontSizeKey(), Value(double(DEFAULT_VALUE_FOR_DefaultFixedFontSize)));
        defaults.get().set(WebPreferencesKey::defaultFontSizeKey(), Value(double(DEFAULT_VALUE_FOR_DefaultFontSize)));
        defaults.get().set(WebPreferencesKey::defaultTextEncodingNameKey(), Value(makeString(DEFAULT_VALUE_FOR_DefaultTextEncodingName)));
        defaults.get().set(WebPreferencesKey::developerExtrasEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DeveloperExtrasEnabled)));
        defaults.get().set(WebPreferencesKey::deviceHeightKey(), Value(uint32_t(DEFAULT_VALUE_FOR_DeviceHeight)));
#if ENABLE(DEVICE_ORIENTATION)
        defaults.get().set(WebPreferencesKey::deviceOrientationEventEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DeviceOrientationEventEnabled)));
#endif
#if ENABLE(DEVICE_ORIENTATION)
        defaults.get().set(WebPreferencesKey::deviceOrientationPermissionAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DeviceOrientationPermissionAPIEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::deviceWidthKey(), Value(uint32_t(DEFAULT_VALUE_FOR_DeviceWidth)));
        defaults.get().set(WebPreferencesKey::disabledAdaptationsMetaTagEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DisabledAdaptationsMetaTagEnabled)));
#if ENABLE(DOWNLOAD_ATTRIBUTE)
        defaults.get().set(WebPreferencesKey::downloadAttributeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DownloadAttributeEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::editableLinkBehaviorKey(), Value(uint32_t(DEFAULT_VALUE_FOR_EditableLinkBehavior)));
        defaults.get().set(WebPreferencesKey::enableInheritURIQueryComponentKey(), Value(bool(DEFAULT_VALUE_FOR_EnableInheritURIQueryComponent)));
#if ENABLE(ENCRYPTED_MEDIA)
        defaults.get().set(WebPreferencesKey::encryptedMediaAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_EncryptedMediaAPIEnabled)));
#endif
#if HAVE(APP_SSO)
        defaults.get().set(WebPreferencesKey::isExtensibleSSOEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ExtensibleSSOEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::ftpDirectoryTemplatePathKey(), Value(makeString(DEFAULT_VALUE_FOR_FTPDirectoryTemplatePath)));
        defaults.get().set(WebPreferencesKey::fantasyFontFamilyKey(), Value(makeString(DEFAULT_VALUE_FOR_FantasyFontFamily)));
        defaults.get().set(WebPreferencesKey::fixedFontFamilyKey(), Value(makeString(DEFAULT_VALUE_FOR_FixedFontFamily)));
        defaults.get().set(WebPreferencesKey::forceCompositingModeKey(), Value(bool(DEFAULT_VALUE_FOR_ForceCompositingMode)));
        defaults.get().set(WebPreferencesKey::forceFTPDirectoryListingsKey(), Value(bool(DEFAULT_VALUE_FOR_ForceFTPDirectoryListings)));
        defaults.get().set(WebPreferencesKey::forceWebGLUsesLowPowerKey(), Value(bool(DEFAULT_VALUE_FOR_ForceWebGLUsesLowPower)));
#if USE(GSTREAMER)
        defaults.get().set(WebPreferencesKey::isGStreamerEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_GStreamerEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::hiddenPageCSSAnimationSuspensionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_HiddenPageCSSAnimationSuspensionEnabled)));
        defaults.get().set(WebPreferencesKey::inactiveMediaCaptureSteamRepromptIntervalInMinutesKey(), Value(double(DEFAULT_VALUE_FOR_InactiveMediaCaptureSteamRepromptIntervalInMinutes)));
        defaults.get().set(WebPreferencesKey::incompleteImageBorderEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_IncompleteImageBorderEnabled)));
#if HAVE(INCREMENTAL_PDF_APIS)
        defaults.get().set(WebPreferencesKey::incrementalPDFLoadingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_IncrementalPDFLoadingEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::incrementalRenderingSuppressionTimeoutKey(), Value(double(DEFAULT_VALUE_FOR_IncrementalRenderingSuppressionTimeout)));
        defaults.get().set(WebPreferencesKey::inlineMediaPlaybackRequiresPlaysInlineAttributeKey(), Value(bool(DEFAULT_VALUE_FOR_InlineMediaPlaybackRequiresPlaysInlineAttribute)));
        defaults.get().set(WebPreferencesKey::inspectorAttachedHeightKey(), Value(uint32_t(DEFAULT_VALUE_FOR_InspectorAttachedHeight)));
        defaults.get().set(WebPreferencesKey::inspectorAttachedWidthKey(), Value(uint32_t(DEFAULT_VALUE_FOR_InspectorAttachedWidth)));
        defaults.get().set(WebPreferencesKey::inspectorAttachmentSideKey(), Value(uint32_t(DEFAULT_VALUE_FOR_InspectorAttachmentSide)));
        defaults.get().set(WebPreferencesKey::inspectorStartsAttachedKey(), Value(bool(DEFAULT_VALUE_FOR_InspectorStartsAttached)));
        defaults.get().set(WebPreferencesKey::inspectorWindowFrameKey(), Value(makeString(DEFAULT_VALUE_FOR_InspectorWindowFrame)));
        defaults.get().set(WebPreferencesKey::interactionRegionInlinePaddingKey(), Value(double(DEFAULT_VALUE_FOR_InteractionRegionInlinePadding)));
        defaults.get().set(WebPreferencesKey::interactionRegionMinimumCornerRadiusKey(), Value(double(DEFAULT_VALUE_FOR_InteractionRegionMinimumCornerRadius)));
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::interruptAudioOnPageVisibilityChangeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InterruptAudioOnPageVisibilityChangeEnabled)));
#endif
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::interruptVideoOnPageVisibilityChangeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InterruptVideoOnPageVisibilityChangeEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::invisibleAutoplayNotPermittedKey(), Value(bool(DEFAULT_VALUE_FOR_InvisibleAutoplayNotPermitted)));
        defaults.get().set(WebPreferencesKey::javaScriptCanAccessClipboardKey(), Value(bool(DEFAULT_VALUE_FOR_JavaScriptCanAccessClipboard)));
        defaults.get().set(WebPreferencesKey::javaScriptCanOpenWindowsAutomaticallyKey(), Value(bool(DEFAULT_VALUE_FOR_JavaScriptCanOpenWindowsAutomatically)));
        defaults.get().set(WebPreferencesKey::javaScriptMarkupEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_JavaScriptMarkupEnabled)));
        defaults.get().set(WebPreferencesKey::javaScriptRuntimeFlagsKey(), Value(uint32_t(DEFAULT_VALUE_FOR_JavaScriptRuntimeFlags)));
        defaults.get().set(WebPreferencesKey::largeImageAsyncDecodingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LargeImageAsyncDecodingEnabled)));
        defaults.get().set(WebPreferencesKey::layoutFallbackWidthKey(), Value(uint32_t(DEFAULT_VALUE_FOR_LayoutFallbackWidth)));
        defaults.get().set(WebPreferencesKey::layoutViewportHeightExpansionFactorKey(), Value(double(DEFAULT_VALUE_FOR_LayoutViewportHeightExpansionFactor)));
        defaults.get().set(WebPreferencesKey::linkPreconnectKey(), Value(bool(DEFAULT_VALUE_FOR_LinkPreconnect)));
        defaults.get().set(WebPreferencesKey::linkPreloadEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LinkPreloadEnabled)));
        defaults.get().set(WebPreferencesKey::loadDeferringEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LoadDeferringEnabled)));
        defaults.get().set(WebPreferencesKey::loadsImagesAutomaticallyKey(), Value(bool(DEFAULT_VALUE_FOR_LoadsImagesAutomatically)));
        defaults.get().set(WebPreferencesKey::longRunningMediaCaptureStreamRepromptIntervalInHoursKey(), Value(double(DEFAULT_VALUE_FOR_LongRunningMediaCaptureStreamRepromptIntervalInHours)));
        defaults.get().set(WebPreferencesKey::lowPowerVideoAudioBufferSizeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LowPowerVideoAudioBufferSizeEnabled)));
#if ENABLE(MANAGED_MEDIA_SOURCE)
        defaults.get().set(WebPreferencesKey::managedMediaSourceHighThresholdKey(), Value(double(DEFAULT_VALUE_FOR_ManagedMediaSourceHighThreshold)));
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
        defaults.get().set(WebPreferencesKey::managedMediaSourceLowThresholdKey(), Value(double(DEFAULT_VALUE_FOR_ManagedMediaSourceLowThreshold)));
#endif
#if ENABLE(MATHML)
        defaults.get().set(WebPreferencesKey::mathMLEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MathMLEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::maxParseDurationKey(), Value(double(DEFAULT_VALUE_FOR_MaxParseDuration)));
        defaults.get().set(WebPreferencesKey::mediaAudioCodecIDsAllowedInLockdownModeKey(), Value(makeString(DEFAULT_VALUE_FOR_MediaAudioCodecIDsAllowedInLockdownMode)));
        defaults.get().set(WebPreferencesKey::mediaCapabilitiesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaCapabilitiesEnabled)));
        defaults.get().set(WebPreferencesKey::mediaCaptionFormatTypesAllowedInLockdownModeKey(), Value(makeString(DEFAULT_VALUE_FOR_MediaCaptionFormatTypesAllowedInLockdownMode)));
        defaults.get().set(WebPreferencesKey::mediaCodecTypesAllowedInLockdownModeKey(), Value(makeString(DEFAULT_VALUE_FOR_MediaCodecTypesAllowedInLockdownMode)));
        defaults.get().set(WebPreferencesKey::mediaContainerTypesAllowedInLockdownModeKey(), Value(makeString(DEFAULT_VALUE_FOR_MediaContainerTypesAllowedInLockdownMode)));
        defaults.get().set(WebPreferencesKey::mediaContentTypesRequiringHardwareSupportKey(), Value(makeString(DEFAULT_VALUE_FOR_MediaContentTypesRequiringHardwareSupport)));
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS)
        defaults.get().set(WebPreferencesKey::mediaControlsContextMenusEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaControlsContextMenusEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::mediaControlsScaleWithPageZoomKey(), Value(bool(DEFAULT_VALUE_FOR_MediaControlsScaleWithPageZoom)));
        defaults.get().set(WebPreferencesKey::mediaDataLoadsAutomaticallyKey(), Value(bool(DEFAULT_VALUE_FOR_MediaDataLoadsAutomatically)));
#if ENABLE(VIDEO)
        defaults.get().set(WebPreferencesKey::mediaEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::mediaPreferredFullscreenWidthKey(), Value(double(DEFAULT_VALUE_FOR_MediaPreferredFullscreenWidth)));
        defaults.get().set(WebPreferencesKey::mediaPreloadingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaPreloadingEnabled)));
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::mediaStreamEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaStreamEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::mediaUserGestureInheritsFromDocumentKey(), Value(bool(DEFAULT_VALUE_FOR_MediaUserGestureInheritsFromDocument)));
        defaults.get().set(WebPreferencesKey::mediaVideoCodecIDsAllowedInLockdownModeKey(), Value(makeString(DEFAULT_VALUE_FOR_MediaVideoCodecIDsAllowedInLockdownMode)));
        defaults.get().set(WebPreferencesKey::menuItemElementEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MenuItemElementEnabled)));
        defaults.get().set(WebPreferencesKey::minimumFontSizeKey(), Value(double(DEFAULT_VALUE_FOR_MinimumFontSize)));
        defaults.get().set(WebPreferencesKey::minimumLogicalFontSizeKey(), Value(double(DEFAULT_VALUE_FOR_MinimumLogicalFontSize)));
#if ENABLE(TEXT_AUTOSIZING)
        defaults.get().set(WebPreferencesKey::minimumZoomFontSizeKey(), Value(double(DEFAULT_VALUE_FOR_MinimumZoomFontSize)));
#endif
        defaults.get().set(WebPreferencesKey::mockCaptureDevicesPromptEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MockCaptureDevicesPromptEnabled)));
        defaults.get().set(WebPreferencesKey::mockScrollbarsControllerEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MockScrollbarsControllerEnabled)));
        defaults.get().set(WebPreferencesKey::mockScrollbarsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MockScrollbarsEnabled)));
        defaults.get().set(WebPreferencesKey::needsAdobeFrameReloadingQuirkKey(), Value(bool(DEFAULT_VALUE_FOR_NeedsAdobeFrameReloadingQuirk)));
        defaults.get().set(WebPreferencesKey::needsFrameNameFallbackToIdQuirkKey(), Value(bool(DEFAULT_VALUE_FOR_NeedsFrameNameFallbackToIdQuirk)));
        defaults.get().set(WebPreferencesKey::needsKeyboardEventDisambiguationQuirksKey(), Value(bool(DEFAULT_VALUE_FOR_NeedsKeyboardEventDisambiguationQuirks)));
        defaults.get().set(WebPreferencesKey::offlineWebApplicationCacheEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_OfflineWebApplicationCacheEnabled)));
#if PLATFORM(COCOA)
        defaults.get().set(WebPreferencesKey::pdfPluginEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PDFPluginEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::passiveTouchListenersAsDefaultOnDocumentKey(), Value(bool(DEFAULT_VALUE_FOR_PassiveTouchListenersAsDefaultOnDocument)));
        defaults.get().set(WebPreferencesKey::passwordEchoDurationKey(), Value(double(DEFAULT_VALUE_FOR_PasswordEchoDuration)));
        defaults.get().set(WebPreferencesKey::passwordEchoEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PasswordEchoEnabled)));
        defaults.get().set(WebPreferencesKey::pictographFontFamilyKey(), Value(makeString(DEFAULT_VALUE_FOR_PictographFontFamily)));
#if ENABLE(PICTURE_IN_PICTURE_API)
        defaults.get().set(WebPreferencesKey::pictureInPictureAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PictureInPictureAPIEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::pitchCorrectionAlgorithmKey(), Value(uint32_t(DEFAULT_VALUE_FOR_PitchCorrectionAlgorithm)));
        defaults.get().set(WebPreferencesKey::pluginsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PluginsEnabled)));
        defaults.get().set(WebPreferencesKey::punchOutWhiteBackgroundsInDarkModeKey(), Value(bool(DEFAULT_VALUE_FOR_PunchOutWhiteBackgroundsInDarkMode)));
        defaults.get().set(WebPreferencesKey::requiresPageVisibilityToPlayAudioKey(), Value(bool(DEFAULT_VALUE_FOR_RequiresPageVisibilityToPlayAudio)));
        defaults.get().set(WebPreferencesKey::requiresUserGestureForAudioPlaybackKey(), Value(bool(DEFAULT_VALUE_FOR_RequiresUserGestureForAudioPlayback)));
        defaults.get().set(WebPreferencesKey::requiresUserGestureForMediaPlaybackKey(), Value(bool(DEFAULT_VALUE_FOR_RequiresUserGestureForMediaPlayback)));
        defaults.get().set(WebPreferencesKey::requiresUserGestureForVideoPlaybackKey(), Value(bool(DEFAULT_VALUE_FOR_RequiresUserGestureForVideoPlayback)));
        defaults.get().set(WebPreferencesKey::requiresUserGestureToLoadVideoKey(), Value(bool(DEFAULT_VALUE_FOR_RequiresUserGestureToLoadVideo)));
#if HAVE(RUBBER_BANDING)
        defaults.get().set(WebPreferencesKey::rubberBandingForSubScrollableRegionsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_RubberBandingForSubScrollableRegionsEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::sampledPageTopColorMaxDifferenceKey(), Value(double(DEFAULT_VALUE_FOR_SampledPageTopColorMaxDifference)));
        defaults.get().set(WebPreferencesKey::sampledPageTopColorMinHeightKey(), Value(double(DEFAULT_VALUE_FOR_SampledPageTopColorMinHeight)));
        defaults.get().set(WebPreferencesKey::sansSerifFontFamilyKey(), Value(makeString(DEFAULT_VALUE_FOR_SansSerifFontFamily)));
        defaults.get().set(WebPreferencesKey::selectTrailingWhitespaceEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SelectTrailingWhitespaceEnabled)));
        defaults.get().set(WebPreferencesKey::serifFontFamilyKey(), Value(makeString(DEFAULT_VALUE_FOR_SerifFontFamily)));
#if ENABLE(SERVICE_CONTROLS)
        defaults.get().set(WebPreferencesKey::serviceControlsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ServiceControlsEnabled)));
#endif
#if ENABLE(SERVICE_WORKER)
        defaults.get().set(WebPreferencesKey::serviceWorkerEntitlementDisabledForTestingKey(), Value(bool(DEFAULT_VALUE_FOR_ServiceWorkerEntitlementDisabledForTesting)));
#endif
        defaults.get().set(WebPreferencesKey::shouldAllowUserInstalledFontsKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldAllowUserInstalledFonts)));
        defaults.get().set(WebPreferencesKey::shouldConvertInvalidURLsToBlankKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldConvertInvalidURLsToBlank)));
        defaults.get().set(WebPreferencesKey::shouldConvertPositionStyleOnCopyKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldConvertPositionStyleOnCopy)));
        defaults.get().set(WebPreferencesKey::shouldDecidePolicyBeforeLoadingQuickLookPreviewKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldDecidePolicyBeforeLoadingQuickLookPreview)));
#if ENABLE(VIDEO)
        defaults.get().set(WebPreferencesKey::shouldDisplayCaptionsKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldDisplayCaptions)));
#endif
#if ENABLE(VIDEO)
        defaults.get().set(WebPreferencesKey::shouldDisplaySubtitlesKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldDisplaySubtitles)));
#endif
#if ENABLE(VIDEO)
        defaults.get().set(WebPreferencesKey::shouldDisplayTextDescriptionsKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldDisplayTextDescriptions)));
#endif
#if ENABLE(TEXT_AUTOSIZING)
        defaults.get().set(WebPreferencesKey::shouldEnableTextAutosizingBoostKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldEnableTextAutosizingBoost)));
#endif
        defaults.get().set(WebPreferencesKey::shouldIgnoreMetaViewportKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldIgnoreMetaViewport)));
        defaults.get().set(WebPreferencesKey::shouldPrintBackgroundsKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldPrintBackgrounds)));
        defaults.get().set(WebPreferencesKey::shouldRespectImageOrientationKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldRespectImageOrientation)));
        defaults.get().set(WebPreferencesKey::shouldRestrictBaseURLSchemesKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldRestrictBaseURLSchemes)));
        defaults.get().set(WebPreferencesKey::shouldSuppressTextInputFromEditingDuringProvisionalNavigationKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldSuppressTextInputFromEditingDuringProvisionalNavigation)));
        defaults.get().set(WebPreferencesKey::shouldUseServiceWorkerShortTimeoutKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldUseServiceWorkerShortTimeout)));
        defaults.get().set(WebPreferencesKey::showsToolTipOverTruncatedTextKey(), Value(bool(DEFAULT_VALUE_FOR_ShowsToolTipOverTruncatedText)));
        defaults.get().set(WebPreferencesKey::showsURLsInToolTipsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ShowsURLsInToolTipsEnabled)));
        defaults.get().set(WebPreferencesKey::shrinksStandaloneImagesToFitKey(), Value(bool(DEFAULT_VALUE_FOR_ShrinksStandaloneImagesToFit)));
        defaults.get().set(WebPreferencesKey::smartInsertDeleteEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SmartInsertDeleteEnabled)));
#if ENABLE(MEDIA_SOURCE)
        defaults.get().set(WebPreferencesKey::sourceBufferChangeTypeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SourceBufferChangeTypeEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::spatialNavigationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SpatialNavigationEnabled)));
        defaults.get().set(WebPreferencesKey::standaloneKey(), Value(bool(DEFAULT_VALUE_FOR_Standalone)));
        defaults.get().set(WebPreferencesKey::standardFontFamilyKey(), Value(makeString(DEFAULT_VALUE_FOR_StandardFontFamily)));
        defaults.get().set(WebPreferencesKey::suppressesIncrementalRenderingKey(), Value(bool(DEFAULT_VALUE_FOR_SuppressesIncrementalRendering)));
        defaults.get().set(WebPreferencesKey::systemLayoutDirectionKey(), Value(uint32_t(DEFAULT_VALUE_FOR_SystemLayoutDirection)));
#if USE(SYSTEM_PREVIEW)
        defaults.get().set(WebPreferencesKey::systemPreviewEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SystemPreviewEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::tabsToLinksKey(), Value(bool(DEFAULT_VALUE_FOR_TabsToLinks)));
        defaults.get().set(WebPreferencesKey::telephoneNumberParsingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_TelephoneNumberParsingEnabled)));
        defaults.get().set(WebPreferencesKey::temporaryTileCohortRetentionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_TemporaryTileCohortRetentionEnabled)));
        defaults.get().set(WebPreferencesKey::textAreasAreResizableKey(), Value(bool(DEFAULT_VALUE_FOR_TextAreasAreResizable)));
#if ENABLE(TEXT_AUTOSIZING)
        defaults.get().set(WebPreferencesKey::textAutosizingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_TextAutosizingEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::textInteractionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_TextInteractionEnabled)));
        defaults.get().set(WebPreferencesKey::threadedScrollingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ThreadedScrollingEnabled)));
        defaults.get().set(WebPreferencesKey::treatsAnyTextCSSLinkAsStylesheetKey(), Value(bool(DEFAULT_VALUE_FOR_TreatsAnyTextCSSLinkAsStylesheet)));
        defaults.get().set(WebPreferencesKey::useImageDocumentForSubframePDFKey(), Value(bool(DEFAULT_VALUE_FOR_UseImageDocumentForSubframePDF)));
        defaults.get().set(WebPreferencesKey::useLegacyBackgroundSizeShorthandBehaviorKey(), Value(bool(DEFAULT_VALUE_FOR_UseLegacyBackgroundSizeShorthandBehavior)));
        defaults.get().set(WebPreferencesKey::usePreHTML5ParserQuirksKey(), Value(bool(DEFAULT_VALUE_FOR_UsePreHTML5ParserQuirks)));
        defaults.get().set(WebPreferencesKey::userInterfaceDirectionPolicyKey(), Value(uint32_t(DEFAULT_VALUE_FOR_UserInterfaceDirectionPolicy)));
        defaults.get().set(WebPreferencesKey::usesBackForwardCacheKey(), Value(bool(DEFAULT_VALUE_FOR_UsesBackForwardCache)));
        defaults.get().set(WebPreferencesKey::usesEncodingDetectorKey(), Value(bool(DEFAULT_VALUE_FOR_UsesEncodingDetector)));
#if ENABLE(VP9)
        defaults.get().set(WebPreferencesKey::vp8DecoderEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_VP8DecoderEnabled)));
#endif
#if ENABLE(VP9)
        defaults.get().set(WebPreferencesKey::vp9DecoderEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_VP9DecoderEnabled)));
#endif
#if PLATFORM(IOS_FAMILY)
        defaults.get().set(WebPreferencesKey::videoFullscreenRequiresElementFullscreenKey(), Value(bool(DEFAULT_VALUE_FOR_VideoFullscreenRequiresElementFullscreen)));
#endif
        defaults.get().set(WebPreferencesKey::videoPresentationModeAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_VideoPresentationModeAPIEnabled)));
#if ENABLE(VIDEO)
        defaults.get().set(WebPreferencesKey::videoQualityIncludesDisplayCompositingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_VideoQualityIncludesDisplayCompositingEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::visibleDebugOverlayRegionsKey(), Value(uint32_t(DEFAULT_VALUE_FOR_VisibleDebugOverlayRegions)));
        defaults.get().set(WebPreferencesKey::visualViewportEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_VisualViewportEnabled)));
        defaults.get().set(WebPreferencesKey::wantsBalancedSetDefersLoadingBehaviorKey(), Value(bool(DEFAULT_VALUE_FOR_WantsBalancedSetDefersLoadingBehavior)));
#if ENABLE(WEB_AUDIO)
        defaults.get().set(WebPreferencesKey::webAudioEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebAudioEnabled)));
#endif
#if ENABLE(WEBM_FORMAT_READER)
        defaults.get().set(WebPreferencesKey::webMFormatReaderEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebMFormatReaderEnabled)));
#endif
#if ENABLE(MEDIA_SOURCE)
        defaults.get().set(WebPreferencesKey::webMParserEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebMParserEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::webSecurityEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebSecurityEnabled)));
        defaults.get().set(WebPreferencesKey::webSocketEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebSocketEnabled)));
        defaults.get().set(WebPreferencesKey::windowFocusRestrictedKey(), Value(bool(DEFAULT_VALUE_FOR_WindowFocusRestricted)));
        defaults.get().set(WebPreferencesKey::wirelessPlaybackTargetAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WirelessPlaybackTargetAPIEnabled)));
        defaults.get().set(WebPreferencesKey::dirPseudoEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DirPseudoEnabled)));
        defaults.get().set(WebPreferencesKey::focusVisibleEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FocusVisibleEnabled)));
        defaults.get().set(WebPreferencesKey::hasPseudoClassEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_HasPseudoClassEnabled)));
        defaults.get().set(WebPreferencesKey::pageAtRuleSupportEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PageAtRuleSupportEnabled)));
        defaults.get().set(WebPreferencesKey::ariaReflectionForElementReferencesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AriaReflectionForElementReferencesEnabled)));
#if USE(AVFOUNDATION)
        defaults.get().set(WebPreferencesKey::isAVFoundationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AVFoundationEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::abortSignalAnyOperationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AbortSignalAnyOperationEnabled)));
#if USE(CORE_IMAGE)
        defaults.get().set(WebPreferencesKey::acceleratedFiltersEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AcceleratedFiltersEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::accessHandleEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AccessHandleEnabled)));
        defaults.get().set(WebPreferencesKey::domTestingAPIsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DOMTestingAPIsEnabled)));
        defaults.get().set(WebPreferencesKey::allowMediaContentTypesRequiringHardwareSupportAsFallbackKey(), Value(bool(DEFAULT_VALUE_FOR_AllowMediaContentTypesRequiringHardwareSupportAsFallback)));
#if PLATFORM(IOS_FAMILY)
        defaults.get().set(WebPreferencesKey::allowViewportShrinkToFitContentKey(), Value(bool(DEFAULT_VALUE_FOR_AllowViewportShrinkToFitContent)));
#endif
#if ENABLE(WEBGL)
        defaults.get().set(WebPreferencesKey::allowWebGLInWorkersKey(), Value(bool(DEFAULT_VALUE_FOR_AllowWebGLInWorkers)));
#endif
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::perElementSpeakerSelectionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PerElementSpeakerSelectionEnabled)));
#endif
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::exposeSpeakersEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ExposeSpeakersEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::allowTopNavigationToDataURLsKey(), Value(bool(DEFAULT_VALUE_FOR_AllowTopNavigationToDataURLs)));
        defaults.get().set(WebPreferencesKey::allowUniversalAccessFromFileURLsKey(), Value(bool(DEFAULT_VALUE_FOR_AllowUniversalAccessFromFileURLs)));
#if ENABLE(ALTERNATE_WEBM_PLAYER)
        defaults.get().set(WebPreferencesKey::alternateWebMPlayerEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AlternateWebMPlayerEnabled)));
#endif
#if ENABLE(BADGING)
        defaults.get().set(WebPreferencesKey::appBadgeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AppBadgeEnabled)));
#endif
#if ENABLE(APP_HIGHLIGHTS)
        defaults.get().set(WebPreferencesKey::appHighlightsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AppHighlightsEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::aspectRatioOfImgFromWidthAndHeightEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AspectRatioOfImgFromWidthAndHeightEnabled)));
        defaults.get().set(WebPreferencesKey::asyncFrameScrollingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AsyncFrameScrollingEnabled)));
        defaults.get().set(WebPreferencesKey::asyncOverflowScrollingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AsyncOverflowScrollingEnabled)));
        defaults.get().set(WebPreferencesKey::asyncClipboardAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AsyncClipboardAPIEnabled)));
#if ENABLE(ATTACHMENT_ELEMENT)
        defaults.get().set(WebPreferencesKey::attachmentElementEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AttachmentElementEnabled)));
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
        defaults.get().set(WebPreferencesKey::attachmentWideLayoutEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AttachmentWideLayoutEnabled)));
#endif
#if ENABLE(VIDEO)
        defaults.get().set(WebPreferencesKey::extendedAudioDescriptionsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ExtendedAudioDescriptionsEnabled)));
#endif
#if ENABLE(VIDEO)
        defaults.get().set(WebPreferencesKey::audioDescriptionsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AudioDescriptionsEnabled)));
#endif
#if ENABLE(DOM_AUDIO_SESSION)
        defaults.get().set(WebPreferencesKey::domAudioSessionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DOMAudioSessionEnabled)));
#endif
#if ENABLE(DOM_AUDIO_SESSION)
        defaults.get().set(WebPreferencesKey::domAudioSessionFullEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DOMAudioSessionFullEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::beaconAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_BeaconAPIEnabled)));
        defaults.get().set(WebPreferencesKey::thirdPartyIframeRedirectBlockingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ThirdPartyIframeRedirectBlockingEnabled)));
        defaults.get().set(WebPreferencesKey::broadcastChannelEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_BroadcastChannelEnabled)));
        defaults.get().set(WebPreferencesKey::broadcastChannelOriginPartitioningEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_BroadcastChannelOriginPartitioningEnabled)));
#if ENABLE(BUILT_IN_NOTIFICATIONS)
        defaults.get().set(WebPreferencesKey::builtInNotificationsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_BuiltInNotificationsEnabled)));
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        defaults.get().set(WebPreferencesKey::useCGDisplayListsForDOMRenderingKey(), Value(bool(DEFAULT_VALUE_FOR_UseCGDisplayListsForDOMRendering)));
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        defaults.get().set(WebPreferencesKey::useCGDisplayListImageCacheKey(), Value(bool(DEFAULT_VALUE_FOR_UseCGDisplayListImageCache)));
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        defaults.get().set(WebPreferencesKey::replayCGDisplayListsIntoBackingStoreKey(), Value(bool(DEFAULT_VALUE_FOR_ReplayCGDisplayListsIntoBackingStore)));
#endif
        defaults.get().set(WebPreferencesKey::css3DTransformInteroperabilityEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSS3DTransformInteroperabilityEnabled)));
        defaults.get().set(WebPreferencesKey::cssCounterStyleAtRuleImageSymbolsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSCounterStyleAtRuleImageSymbolsEnabled)));
        defaults.get().set(WebPreferencesKey::cssCounterStyleAtRulesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSCounterStyleAtRulesEnabled)));
        defaults.get().set(WebPreferencesKey::cssFontFaceSizeAdjustEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSFontFaceSizeAdjustEnabled)));
        defaults.get().set(WebPreferencesKey::accentColorEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AccentColorEnabled)));
        defaults.get().set(WebPreferencesKey::aspectRatioEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AspectRatioEnabled)));
        defaults.get().set(WebPreferencesKey::cssCascadeLayersEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSCascadeLayersEnabled)));
        defaults.get().set(WebPreferencesKey::cssColor4Key(), Value(bool(DEFAULT_VALUE_FOR_CSSColor4)));
        defaults.get().set(WebPreferencesKey::cssContainIntrinsicSizeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSContainIntrinsicSizeEnabled)));
        defaults.get().set(WebPreferencesKey::cssContainerQueriesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSContainerQueriesEnabled)));
        defaults.get().set(WebPreferencesKey::cssContainmentEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSContainmentEnabled)));
        defaults.get().set(WebPreferencesKey::cssContentVisibilityEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSContentVisibilityEnabled)));
        defaults.get().set(WebPreferencesKey::cssCustomPropertiesAndValuesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSCustomPropertiesAndValuesEnabled)));
        defaults.get().set(WebPreferencesKey::cssGradientInterpolationColorSpacesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSGradientInterpolationColorSpacesEnabled)));
        defaults.get().set(WebPreferencesKey::cssGradientPremultipliedAlphaInterpolationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSGradientPremultipliedAlphaInterpolationEnabled)));
        defaults.get().set(WebPreferencesKey::cssIndividualTransformPropertiesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSIndividualTransformPropertiesEnabled)));
        defaults.get().set(WebPreferencesKey::cssInputSecurityEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSInputSecurityEnabled)));
        defaults.get().set(WebPreferencesKey::masonryEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MasonryEnabled)));
        defaults.get().set(WebPreferencesKey::cssMotionPathEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSMotionPathEnabled)));
        defaults.get().set(WebPreferencesKey::cssNestingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSNestingEnabled)));
        defaults.get().set(WebPreferencesKey::overscrollBehaviorEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_OverscrollBehaviorEnabled)));
#if ENABLE(CSS_PAINTING_API)
        defaults.get().set(WebPreferencesKey::cssPaintingAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSPaintingAPIEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::cssRelativeColorSyntaxEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSRelativeColorSyntaxEnabled)));
        defaults.get().set(WebPreferencesKey::cssRhythmicSizingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSRhythmicSizingEnabled)));
        defaults.get().set(WebPreferencesKey::cssScrollAnchoringEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSScrollAnchoringEnabled)));
        defaults.get().set(WebPreferencesKey::springTimingFunctionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SpringTimingFunctionEnabled)));
        defaults.get().set(WebPreferencesKey::cssTypedOMEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSTypedOMEnabled)));
        defaults.get().set(WebPreferencesKey::cssTypedOMColorEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSTypedOMColorEnabled)));
        defaults.get().set(WebPreferencesKey::masonryTrackAlignmentEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MasonryTrackAlignmentEnabled)));
        defaults.get().set(WebPreferencesKey::cssColorContrastEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSColorContrastEnabled)));
        defaults.get().set(WebPreferencesKey::cssColorMixEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSColorMixEnabled)));
        defaults.get().set(WebPreferencesKey::cssMarginTrimEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSMarginTrimEnabled)));
        defaults.get().set(WebPreferencesKey::overflowClipEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_OverflowClipEnabled)));
        defaults.get().set(WebPreferencesKey::cssScrollbarColorEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSScrollbarColorEnabled)));
        defaults.get().set(WebPreferencesKey::cssScrollbarGutterEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSScrollbarGutterEnabled)));
        defaults.get().set(WebPreferencesKey::cssScrollbarWidthEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSScrollbarWidthEnabled)));
        defaults.get().set(WebPreferencesKey::subgridEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SubgridEnabled)));
        defaults.get().set(WebPreferencesKey::cssTextAlignLastEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSTextAlignLastEnabled)));
        defaults.get().set(WebPreferencesKey::cssTextBoxTrimEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSTextBoxTrimEnabled)));
        defaults.get().set(WebPreferencesKey::cssTextGroupAlignEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSTextGroupAlignEnabled)));
        defaults.get().set(WebPreferencesKey::cssTextJustifyEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSTextJustifyEnabled)));
        defaults.get().set(WebPreferencesKey::cssTextSpacingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSTextSpacingEnabled)));
        defaults.get().set(WebPreferencesKey::cssTextUnderlinePositionLeftRightEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSTextUnderlinePositionLeftRightEnabled)));
        defaults.get().set(WebPreferencesKey::cssWhiteSpaceLonghandsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSWhiteSpaceLonghandsEnabled)));
        defaults.get().set(WebPreferencesKey::cssTextWrapNewValuesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSTextWrapNewValuesEnabled)));
#if ENABLE(CSS_TRANSFORM_STYLE_OPTIMIZED_3D)
        defaults.get().set(WebPreferencesKey::cssTransformStyleOptimized3DEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSTransformStyleOptimized3DEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::cssOMViewScrollingAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSOMViewScrollingAPIEnabled)));
        defaults.get().set(WebPreferencesKey::cssOMViewSmoothScrollingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSOMViewSmoothScrollingEnabled)));
        defaults.get().set(WebPreferencesKey::cacheAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CacheAPIEnabled)));
        defaults.get().set(WebPreferencesKey::canvasColorSpaceEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CanvasColorSpaceEnabled)));
        defaults.get().set(WebPreferencesKey::canvasFiltersEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CanvasFiltersEnabled)));
        defaults.get().set(WebPreferencesKey::canvasUsesAcceleratedDrawingKey(), Value(bool(DEFAULT_VALUE_FOR_CanvasUsesAcceleratedDrawing)));
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::captureAudioInUIProcessEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CaptureAudioInUIProcessEnabled)));
#endif
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::captureVideoInUIProcessEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CaptureVideoInUIProcessEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::clearSiteDataHTTPHeaderEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ClearSiteDataHTTPHeaderEnabled)));
#if ENABLE(BADGING)
        defaults.get().set(WebPreferencesKey::clientBadgeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ClientBadgeEnabled)));
#endif
#if ENABLE(INPUT_TYPE_COLOR)
        defaults.get().set(WebPreferencesKey::inputTypeColorEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InputTypeColorEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::compositingBordersVisibleKey(), Value(bool(DEFAULT_VALUE_FOR_CompositingBordersVisible)));
        defaults.get().set(WebPreferencesKey::compositingRepaintCountersVisibleKey(), Value(bool(DEFAULT_VALUE_FOR_CompositingRepaintCountersVisible)));
        defaults.get().set(WebPreferencesKey::compressionStreamEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CompressionStreamEnabled)));
        defaults.get().set(WebPreferencesKey::constructableStylesheetsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ConstructableStylesheetsEnabled)));
        defaults.get().set(WebPreferencesKey::contactPickerAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ContactPickerAPIEnabled)));
#if HAVE(AVCONTENTKEYSPECIFIER)
        defaults.get().set(WebPreferencesKey::sampleBufferContentKeySessionSupportEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SampleBufferContentKeySessionSupportEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::cookieConsentAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CookieConsentAPIEnabled)));
        defaults.get().set(WebPreferencesKey::cookieStoreAPIExtendedAttributesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CookieStoreAPIExtendedAttributesEnabled)));
        defaults.get().set(WebPreferencesKey::cookieStoreAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CookieStoreAPIEnabled)));
        defaults.get().set(WebPreferencesKey::cookieEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CookieEnabled)));
        defaults.get().set(WebPreferencesKey::crossOriginEmbedderPolicyEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CrossOriginEmbedderPolicyEnabled)));
        defaults.get().set(WebPreferencesKey::crossOriginOpenerPolicyEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CrossOriginOpenerPolicyEnabled)));
        defaults.get().set(WebPreferencesKey::customPasteboardDataEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CustomPasteboardDataEnabled)));
        defaults.get().set(WebPreferencesKey::domPasteAccessRequestsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DOMPasteAccessRequestsEnabled)));
        defaults.get().set(WebPreferencesKey::domTimersThrottlingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DOMTimersThrottlingEnabled)));
        defaults.get().set(WebPreferencesKey::declarativeShadowDOMInDOMParserEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DeclarativeShadowDOMInDOMParserEnabled)));
#if PLATFORM(IOS_FAMILY)
        defaults.get().set(WebPreferencesKey::zoomOnDoubleTapWhenRootKey(), Value(bool(DEFAULT_VALUE_FOR_ZoomOnDoubleTapWhenRoot)));
#endif
#if PLATFORM(IOS_FAMILY)
        defaults.get().set(WebPreferencesKey::alwaysZoomOnDoubleTapKey(), Value(bool(DEFAULT_VALUE_FOR_AlwaysZoomOnDoubleTap)));
#endif
        defaults.get().set(WebPreferencesKey::dataTransferItemsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DataTransferItemsEnabled)));
#if ENABLE(DATALIST_ELEMENT)
        defaults.get().set(WebPreferencesKey::dataListElementEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DataListElementEnabled)));
#endif
#if ENABLE(INPUT_TYPE_DATE)
        defaults.get().set(WebPreferencesKey::inputTypeDateEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InputTypeDateEnabled)));
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
        defaults.get().set(WebPreferencesKey::dateTimeInputsEditableComponentsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DateTimeInputsEditableComponentsEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::declarativeShadowDOMEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DeclarativeShadowDOMEnabled)));
        defaults.get().set(WebPreferencesKey::defaultARIAForCustomElementsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DefaultARIAForCustomElementsEnabled)));
        defaults.get().set(WebPreferencesKey::shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaintKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint)));
        defaults.get().set(WebPreferencesKey::deprecateRSAESPKCSWebCryptoEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DeprecateRSAESPKCSWebCryptoEnabled)));
        defaults.get().set(WebPreferencesKey::deprecationReportingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DeprecationReportingEnabled)));
        defaults.get().set(WebPreferencesKey::diagnosticLoggingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DiagnosticLoggingEnabled)));
        defaults.get().set(WebPreferencesKey::directoryUploadEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DirectoryUploadEnabled)));
        defaults.get().set(WebPreferencesKey::isThirdPartyCookieBlockingDisabledKey(), Value(bool(DEFAULT_VALUE_FOR_IsThirdPartyCookieBlockingDisabled)));
        defaults.get().set(WebPreferencesKey::isFirstPartyWebsiteDataRemovalDisabledKey(), Value(bool(DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalDisabled)));
#if PLATFORM(IOS_FAMILY)
        defaults.get().set(WebPreferencesKey::disableScreenSizeOverrideKey(), Value(bool(DEFAULT_VALUE_FOR_DisableScreenSizeOverride)));
#endif
        defaults.get().set(WebPreferencesKey::disallowSyncXHRDuringPageDismissalEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DisallowSyncXHRDuringPageDismissalEnabled)));
        defaults.get().set(WebPreferencesKey::displayListDrawingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DisplayListDrawingEnabled)));
        defaults.get().set(WebPreferencesKey::shouldDropNearSuspendedAssertionAfterDelayKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldDropNearSuspendedAssertionAfterDelay)));
        defaults.get().set(WebPreferencesKey::embedElementEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_EmbedElementEnabled)));
        defaults.get().set(WebPreferencesKey::automaticLiveResizeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AutomaticLiveResizeEnabled)));
        defaults.get().set(WebPreferencesKey::canvasFingerprintingQuirkEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CanvasFingerprintingQuirkEnabled)));
        defaults.get().set(WebPreferencesKey::enumeratingAllNetworkInterfacesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_EnumeratingAllNetworkInterfacesEnabled)));
        defaults.get().set(WebPreferencesKey::enumeratingVisibleNetworkInterfacesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_EnumeratingVisibleNetworkInterfacesEnabled)));
        defaults.get().set(WebPreferencesKey::iceCandidateFilteringEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ICECandidateFilteringEnabled)));
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
        defaults.get().set(WebPreferencesKey::legacyEncryptedMediaAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LegacyEncryptedMediaAPIEnabled)));
#endif
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::mockCaptureDevicesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MockCaptureDevicesEnabled)));
#endif
#if ENABLE(PDFJS)
        defaults.get().set(WebPreferencesKey::pdfJSViewerEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PdfJSViewerEnabled)));
#endif
#if PLATFORM(MAC) && USE(RUNNINGBOARD)
        defaults.get().set(WebPreferencesKey::backgroundWebContentRunningBoardThrottlingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_BackgroundWebContentRunningBoardThrottlingEnabled)));
#endif
#if ENABLE(SERVICE_WORKER)
        defaults.get().set(WebPreferencesKey::backgroundFetchAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_BackgroundFetchAPIEnabled)));
#endif
#if HAVE(MACH_BOOTSTRAP_EXTENSION) || HAVE(SANDBOX_STATE_FLAGS)
        defaults.get().set(WebPreferencesKey::experimentalSandboxEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ExperimentalSandboxEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::strictSecureDecodingForAllObjCKey(), Value(bool(DEFAULT_VALUE_FOR_StrictSecureDecodingForAllObjC)));
        defaults.get().set(WebPreferencesKey::enterKeyHintEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_EnterKeyHintEnabled)));
        defaults.get().set(WebPreferencesKey::eventHandlerDrivenSmoothKeyboardScrollingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_EventHandlerDrivenSmoothKeyboardScrollingEnabled)));
#if ENABLE(MEDIA_SESSION_COORDINATOR)
        defaults.get().set(WebPreferencesKey::mediaSessionCoordinatorEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaSessionCoordinatorEnabled)));
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR) && ENABLE(MEDIA_SESSION_PLAYLIST)
        defaults.get().set(WebPreferencesKey::mediaSessionPlaylistEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaSessionPlaylistEnabled)));
#endif
#if ENABLE(MEDIA_SOURCE) && (HAVE(AVSAMPLEBUFFERVIDEOOUTPUT) || USE(GSTREAMER))
        defaults.get().set(WebPreferencesKey::mediaSourceInlinePaintingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaSourceInlinePaintingEnabled)));
#endif
#if HAVE(NETWORK_LOADER)
        defaults.get().set(WebPreferencesKey::cFNetworkNetworkLoaderEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CFNetworkNetworkLoaderEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::ftpEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FTPEnabled)));
#if PLATFORM(IOS_FAMILY)
        defaults.get().set(WebPreferencesKey::preferFasterClickOverDoubleTapKey(), Value(bool(DEFAULT_VALUE_FOR_PreferFasterClickOverDoubleTap)));
#endif
#if PLATFORM(IOS_FAMILY)
        defaults.get().set(WebPreferencesKey::fasterClicksEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FasterClicksEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::fetchAPIKeepAliveEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FetchAPIKeepAliveEnabled)));
        defaults.get().set(WebPreferencesKey::fetchAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FetchAPIEnabled)));
        defaults.get().set(WebPreferencesKey::fetchMetadataEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FetchMetadataEnabled)));
        defaults.get().set(WebPreferencesKey::fetchPriorityEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FetchPriorityEnabled)));
        defaults.get().set(WebPreferencesKey::fileSystemAccessEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FileSystemAccessEnabled)));
        defaults.get().set(WebPreferencesKey::fileReaderAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FileReaderAPIEnabled)));
        defaults.get().set(WebPreferencesKey::restrictedHTTPResponseAccessKey(), Value(bool(DEFAULT_VALUE_FOR_RestrictedHTTPResponseAccess)));
#if PLATFORM(IOS_FAMILY)
        defaults.get().set(WebPreferencesKey::forceAlwaysUserScalableKey(), Value(bool(DEFAULT_VALUE_FOR_ForceAlwaysUserScalable)));
#endif
        defaults.get().set(WebPreferencesKey::requestSubmitEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_RequestSubmitEnabled)));
        defaults.get().set(WebPreferencesKey::formAssociatedCustomElementsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FormAssociatedCustomElementsEnabled)));
        defaults.get().set(WebPreferencesKey::frameFlatteningEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FrameFlatteningEnabled)));
        defaults.get().set(WebPreferencesKey::layoutFormattingContextEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LayoutFormattingContextEnabled)));
#if ENABLE(FULLSCREEN_API)
        defaults.get().set(WebPreferencesKey::fullScreenEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FullScreenEnabled)));
#endif
#if PLATFORM(VISION)
        defaults.get().set(WebPreferencesKey::fullscreenSceneAspectRatioLockingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FullscreenSceneAspectRatioLockingEnabled)));
#endif
#if PLATFORM(VISION)
        defaults.get().set(WebPreferencesKey::fullscreenSceneDimmingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FullscreenSceneDimmingEnabled)));
#endif
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::captureAudioInGPUProcessEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CaptureAudioInGPUProcessEnabled)));
#endif
#if ENABLE(GPU_PROCESS)
        defaults.get().set(WebPreferencesKey::blockMediaLayerRehostingInWebContentProcessKey(), Value(bool(DEFAULT_VALUE_FOR_BlockMediaLayerRehostingInWebContentProcess)));
#endif
#if ENABLE(GPU_PROCESS) && !(PLATFORM(GTK) || PLATFORM(WPE))
        defaults.get().set(WebPreferencesKey::useGPUProcessForCanvasRenderingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_UseGPUProcessForCanvasRenderingEnabled)));
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
        defaults.get().set(WebPreferencesKey::manageCaptureStatusBarInGPUProcessEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ManageCaptureStatusBarInGPUProcessEnabled)));
#endif
#if ENABLE(GPU_PROCESS)
        defaults.get().set(WebPreferencesKey::useGPUProcessForDOMRenderingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_UseGPUProcessForDOMRenderingEnabled)));
#endif
#if ENABLE(GPU_PROCESS) && !USE(GSTREAMER)
        defaults.get().set(WebPreferencesKey::useGPUProcessForMediaEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_UseGPUProcessForMediaEnabled)));
#endif
#if HAVE(SCREEN_CAPTURE_KIT)
        defaults.get().set(WebPreferencesKey::useGPUProcessForDisplayCaptureKey(), Value(bool(DEFAULT_VALUE_FOR_UseGPUProcessForDisplayCapture)));
#endif
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::captureVideoInGPUProcessEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CaptureVideoInGPUProcessEnabled)));
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
        defaults.get().set(WebPreferencesKey::useGPUProcessForWebGLEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_UseGPUProcessForWebGLEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCPlatformCodecsInGPUProcessEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCPlatformCodecsInGPUProcessEnabled)));
#endif
#if ENABLE(GAMEPAD)
        defaults.get().set(WebPreferencesKey::gamepadTriggerRumbleEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_GamepadTriggerRumbleEnabled)));
#endif
#if ENABLE(GAMEPAD)
        defaults.get().set(WebPreferencesKey::gamepadVibrationActuatorEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_GamepadVibrationActuatorEnabled)));
#endif
#if ENABLE(GAMEPAD)
        defaults.get().set(WebPreferencesKey::gamepadsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_GamepadsEnabled)));
#endif
#if ENABLE(VIDEO)
        defaults.get().set(WebPreferencesKey::genericCueAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_GenericCueAPIEnabled)));
#endif
#if USE(GRAPHICS_CONTEXT_FILTERS)
        defaults.get().set(WebPreferencesKey::graphicsContextFiltersEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_GraphicsContextFiltersEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::acceleratedDrawingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_AcceleratedDrawingEnabled)));
        defaults.get().set(WebPreferencesKey::dialogElementEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_DialogElementEnabled)));
#if ENABLE(MODEL_ELEMENT)
        defaults.get().set(WebPreferencesKey::modelElementEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ModelElementEnabled)));
#endif
#if ENABLE(MODEL_ELEMENT)
        defaults.get().set(WebPreferencesKey::modelDocumentEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ModelDocumentEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::interactiveFormValidationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InteractiveFormValidationEnabled)));
        defaults.get().set(WebPreferencesKey::inertAttributeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InertAttributeEnabled)));
        defaults.get().set(WebPreferencesKey::popoverAttributeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PopoverAttributeEnabled)));
        defaults.get().set(WebPreferencesKey::hiddenPageDOMTimerThrottlingAutoIncreasesKey(), Value(bool(DEFAULT_VALUE_FOR_HiddenPageDOMTimerThrottlingAutoIncreases)));
        defaults.get().set(WebPreferencesKey::hiddenPageDOMTimerThrottlingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_HiddenPageDOMTimerThrottlingEnabled)));
        defaults.get().set(WebPreferencesKey::highlightAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_HighlightAPIEnabled)));
        defaults.get().set(WebPreferencesKey::hyperlinkAuditingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_HyperlinkAuditingEnabled)));
#if HAVE(SANDBOX_STATE_FLAGS)
        defaults.get().set(WebPreferencesKey::blockIOKitInWebContentSandboxKey(), Value(bool(DEFAULT_VALUE_FOR_BlockIOKitInWebContentSandbox)));
#endif
#if ENABLE(IPC_TESTING_API)
        defaults.get().set(WebPreferencesKey::ipcTestingAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_IPCTestingAPIEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::itpDebugModeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ItpDebugModeEnabled)));
#if ENABLE(TEXT_AUTOSIZING)
        defaults.get().set(WebPreferencesKey::textAutosizingUsesIdempotentModeKey(), Value(bool(DEFAULT_VALUE_FOR_TextAutosizingUsesIdempotentMode)));
#endif
#if ENABLE(IMAGE_ANALYSIS)
        defaults.get().set(WebPreferencesKey::imageAnalysisDuringFindInPageEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ImageAnalysisDuringFindInPageEnabled)));
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
        defaults.get().set(WebPreferencesKey::imageAnimationControlEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ImageAnimationControlEnabled)));
#endif
#if ENABLE(SERVICE_CONTROLS)
        defaults.get().set(WebPreferencesKey::imageControlsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ImageControlsEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::imperativeSlotAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ImperativeSlotAPIEnabled)));
        defaults.get().set(WebPreferencesKey::indexedDBAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_IndexedDBAPIEnabled)));
        defaults.get().set(WebPreferencesKey::inlinePredictionsInAllEditableElementsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InlinePredictionsInAllEditableElementsEnabled)));
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
        defaults.get().set(WebPreferencesKey::interactionRegionsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InteractionRegionsEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::intersectionObserverEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_IntersectionObserverEnabled)));
        defaults.get().set(WebPreferencesKey::isLoggedInAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_IsLoggedInAPIEnabled)));
#if ENABLE(ACCESSIBILITY_ISOLATED_TREE)
        defaults.get().set(WebPreferencesKey::isAccessibilityIsolatedTreeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_IsAccessibilityIsolatedTreeEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::javaScriptEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_JavaScriptEnabled)));
#if ENABLE(LAYER_BASED_SVG_ENGINE)
        defaults.get().set(WebPreferencesKey::layerBasedSVGEngineEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LayerBasedSVGEngineEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::lazyIframeLoadingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LazyIframeLoadingEnabled)));
        defaults.get().set(WebPreferencesKey::lazyImageLoadingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LazyImageLoadingEnabled)));
#if ENABLE(OVERFLOW_SCROLLING_TOUCH)
        defaults.get().set(WebPreferencesKey::legacyOverflowScrollingTouchEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LegacyOverflowScrollingTouchEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::legacyLineLayoutVisualCoverageEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LegacyLineLayoutVisualCoverageEnabled)));
        defaults.get().set(WebPreferencesKey::showModalDialogEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ShowModalDialogEnabled)));
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::mediaCaptureRequiresSecureConnectionKey(), Value(bool(DEFAULT_VALUE_FOR_MediaCaptureRequiresSecureConnection)));
#endif
        defaults.get().set(WebPreferencesKey::linkSanitizerEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LinkSanitizerEnabled)));
        defaults.get().set(WebPreferencesKey::linkPreloadResponsiveImagesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LinkPreloadResponsiveImagesEnabled)));
        defaults.get().set(WebPreferencesKey::linkModulePreloadEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LinkModulePreloadEnabled)));
        defaults.get().set(WebPreferencesKey::linkPreconnectEarlyHintsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LinkPreconnectEarlyHintsEnabled)));
        defaults.get().set(WebPreferencesKey::linkPrefetchEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LinkPrefetchEnabled)));
        defaults.get().set(WebPreferencesKey::liveRangeSelectionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LiveRangeSelectionEnabled)));
        defaults.get().set(WebPreferencesKey::localFileContentSniffingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LocalFileContentSniffingEnabled)));
        defaults.get().set(WebPreferencesKey::localStorageEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LocalStorageEnabled)));
        defaults.get().set(WebPreferencesKey::logsPageMessagesToSystemConsoleEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LogsPageMessagesToSystemConsoleEnabled)));
        defaults.get().set(WebPreferencesKey::mainContentUserGestureOverrideEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MainContentUserGestureOverrideEnabled)));
#if ENABLE(MANAGED_MEDIA_SOURCE)
        defaults.get().set(WebPreferencesKey::managedMediaSourceEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ManagedMediaSourceEnabled)));
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE) && ENABLE(WIRELESS_PLAYBACK_TARGET)
        defaults.get().set(WebPreferencesKey::managedMediaSourceNeedsAirPlayKey(), Value(bool(DEFAULT_VALUE_FOR_ManagedMediaSourceNeedsAirPlay)));
#endif
#if ENABLE(WEBGL)
        defaults.get().set(WebPreferencesKey::maskWebGLStringsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MaskWebGLStringsEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::coreMathMLEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CoreMathMLEnabled)));
        defaults.get().set(WebPreferencesKey::mediaCapabilitiesExtensionsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaCapabilitiesExtensionsEnabled)));
#if ENABLE(MEDIA_SESSION)
        defaults.get().set(WebPreferencesKey::mediaSessionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaSessionEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::mediaSourceEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaSourceEnabled)));
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::mediaDevicesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaDevicesEnabled)));
#endif
#if ENABLE(MEDIA_RECORDER)
        defaults.get().set(WebPreferencesKey::mediaRecorderEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MediaRecorderEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::momentumScrollingAnimatorEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MomentumScrollingAnimatorEnabled)));
#if ENABLE(INPUT_TYPE_MONTH)
        defaults.get().set(WebPreferencesKey::inputTypeMonthEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InputTypeMonthEnabled)));
#endif
#if ENABLE(TOUCH_EVENTS)
        defaults.get().set(WebPreferencesKey::mouseEventsSimulationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MouseEventsSimulationEnabled)));
#endif
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::muteCameraOnMicrophoneInterruptionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_MuteCameraOnMicrophoneInterruptionEnabled)));
#endif
#if ENABLE(APP_BOUND_DOMAINS)
        defaults.get().set(WebPreferencesKey::needsInAppBrowserPrivacyQuirksKey(), Value(bool(DEFAULT_VALUE_FOR_NeedsInAppBrowserPrivacyQuirks)));
#endif
        defaults.get().set(WebPreferencesKey::needsSiteSpecificQuirksKey(), Value(bool(DEFAULT_VALUE_FOR_NeedsSiteSpecificQuirks)));
        defaults.get().set(WebPreferencesKey::needsStorageAccessFromFileURLsQuirkKey(), Value(bool(DEFAULT_VALUE_FOR_NeedsStorageAccessFromFileURLsQuirk)));
        defaults.get().set(WebPreferencesKey::flexFormattingContextIntegrationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FlexFormattingContextIntegrationEnabled)));
        defaults.get().set(WebPreferencesKey::inlineFormattingContextIntegrationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InlineFormattingContextIntegrationEnabled)));
#if ENABLE(NOTIFICATION_EVENT)
        defaults.get().set(WebPreferencesKey::notificationEventEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_NotificationEventEnabled)));
#endif
#if ENABLE(NOTIFICATIONS)
        defaults.get().set(WebPreferencesKey::notificationsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_NotificationsEnabled)));
#endif
#if ENABLE(OFFSCREEN_CANVAS_IN_WORKERS)
        defaults.get().set(WebPreferencesKey::offscreenCanvasInWorkersEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_OffscreenCanvasInWorkersEnabled)));
#endif
#if ENABLE(OFFSCREEN_CANVAS)
        defaults.get().set(WebPreferencesKey::offscreenCanvasEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_OffscreenCanvasEnabled)));
#endif
#if ENABLE(OPUS)
        defaults.get().set(WebPreferencesKey::opusDecoderEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_OpusDecoderEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::pageVisibilityBasedProcessSuppressionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PageVisibilityBasedProcessSuppressionEnabled)));
        defaults.get().set(WebPreferencesKey::paintTimingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PaintTimingEnabled)));
        defaults.get().set(WebPreferencesKey::blobRegistryTopOriginPartitioningEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_BlobRegistryTopOriginPartitioningEnabled)));
        defaults.get().set(WebPreferencesKey::performanceNavigationTimingAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PerformanceNavigationTimingAPIEnabled)));
        defaults.get().set(WebPreferencesKey::performanceResourceTimingSensitivePropertiesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PerformanceResourceTimingSensitivePropertiesEnabled)));
        defaults.get().set(WebPreferencesKey::permissionsAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PermissionsAPIEnabled)));
        defaults.get().set(WebPreferencesKey::preferPageRenderingUpdatesNear60FPSEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PreferPageRenderingUpdatesNear60FPSEnabled)));
#if ENABLE(VIDEO)
        defaults.get().set(WebPreferencesKey::preferSandboxedMediaParsingKey(), Value(bool(DEFAULT_VALUE_FOR_PreferSandboxedMediaParsing)));
#endif
        defaults.get().set(WebPreferencesKey::privateClickMeasurementDebugModeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PrivateClickMeasurementDebugModeEnabled)));
        defaults.get().set(WebPreferencesKey::privateClickMeasurementFraudPreventionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PrivateClickMeasurementFraudPreventionEnabled)));
        defaults.get().set(WebPreferencesKey::privateClickMeasurementEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PrivateClickMeasurementEnabled)));
#if ENABLE(SERVICE_WORKER)
        defaults.get().set(WebPreferencesKey::pushAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PushAPIEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::googleAntiFlickerOptimizationQuirkEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_GoogleAntiFlickerOptimizationQuirkEnabled)));
        defaults.get().set(WebPreferencesKey::readableByteStreamAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ReadableByteStreamAPIEnabled)));
        defaults.get().set(WebPreferencesKey::referrerPolicyAttributeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ReferrerPolicyAttributeEnabled)));
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
        defaults.get().set(WebPreferencesKey::remotePlaybackEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_RemotePlaybackEnabled)));
#endif
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
        defaults.get().set(WebPreferencesKey::removeBackgroundEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_RemoveBackgroundEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::reportingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ReportingEnabled)));
        defaults.get().set(WebPreferencesKey::requestVideoFrameCallbackEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_RequestVideoFrameCallbackEnabled)));
#if HAVE(SC_CONTENT_SHARING_PICKER)
        defaults.get().set(WebPreferencesKey::requireUAGetDisplayMediaPromptKey(), Value(bool(DEFAULT_VALUE_FOR_RequireUAGetDisplayMediaPrompt)));
#endif
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::speakerSelectionRequiresUserGestureKey(), Value(bool(DEFAULT_VALUE_FOR_SpeakerSelectionRequiresUserGesture)));
#endif
        defaults.get().set(WebPreferencesKey::fullscreenRequirementForScreenOrientationLockingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_FullscreenRequirementForScreenOrientationLockingEnabled)));
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::getUserMediaRequiresFocusKey(), Value(bool(DEFAULT_VALUE_FOR_GetUserMediaRequiresFocus)));
#endif
        defaults.get().set(WebPreferencesKey::resizeObserverEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ResizeObserverEnabled)));
        defaults.get().set(WebPreferencesKey::resourceLoadSchedulingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ResourceLoadSchedulingEnabled)));
#if ENABLE(RESOURCE_USAGE)
        defaults.get().set(WebPreferencesKey::resourceUsageOverlayVisibleKey(), Value(bool(DEFAULT_VALUE_FOR_ResourceUsageOverlayVisible)));
#endif
        defaults.get().set(WebPreferencesKey::sKAttributionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SKAttributionEnabled)));
        defaults.get().set(WebPreferencesKey::safeBrowsingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SafeBrowsingEnabled)));
        defaults.get().set(WebPreferencesKey::isSameSiteStrictEnforcementEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_IsSameSiteStrictEnforcementEnabled)));
        defaults.get().set(WebPreferencesKey::screenOrientationLockingAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ScreenOrientationLockingAPIEnabled)));
        defaults.get().set(WebPreferencesKey::screenOrientationAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ScreenOrientationAPIEnabled)));
        defaults.get().set(WebPreferencesKey::screenWakeLockAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ScreenWakeLockAPIEnabled)));
#if ENABLE(MEDIA_STREAM)
        defaults.get().set(WebPreferencesKey::screenCaptureEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ScreenCaptureEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::scrollingPerformanceTestingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ScrollingPerformanceTestingEnabled)));
        defaults.get().set(WebPreferencesKey::scrollToTextFragmentIndicatorEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ScrollToTextFragmentIndicatorEnabled)));
        defaults.get().set(WebPreferencesKey::scrollToTextFragmentEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ScrollToTextFragmentEnabled)));
        defaults.get().set(WebPreferencesKey::scrollAnimatorEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ScrollAnimatorEnabled)));
        defaults.get().set(WebPreferencesKey::searchInputIncrementalAttributeAndSearchEventEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SearchInputIncrementalAttributeAndSearchEventEnabled)));
        defaults.get().set(WebPreferencesKey::secureContextChecksEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SecureContextChecksEnabled)));
        defaults.get().set(WebPreferencesKey::selectionAPIForShadowDOMEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SelectionAPIForShadowDOMEnabled)));
        defaults.get().set(WebPreferencesKey::selectionFlippingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SelectionFlippingEnabled)));
        defaults.get().set(WebPreferencesKey::sendMouseEventsToDisabledFormControlsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SendMouseEventsToDisabledFormControlsEnabled)));
        defaults.get().set(WebPreferencesKey::serverTimingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ServerTimingEnabled)));
#if ENABLE(SERVICE_WORKER)
        defaults.get().set(WebPreferencesKey::serviceWorkerNavigationPreloadEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ServiceWorkerNavigationPreloadEnabled)));
#endif
#if ENABLE(SERVICE_WORKER)
        defaults.get().set(WebPreferencesKey::serviceWorkersEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ServiceWorkersEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::shapeDetectionKey(), Value(bool(DEFAULT_VALUE_FOR_ShapeDetection)));
        defaults.get().set(WebPreferencesKey::sharedWorkerEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SharedWorkerEnabled)));
        defaults.get().set(WebPreferencesKey::showMediaStatsContextMenuItemEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ShowMediaStatsContextMenuItemEnabled)));
        defaults.get().set(WebPreferencesKey::siteIsolationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SiteIsolationEnabled)));
        defaults.get().set(WebPreferencesKey::speechRecognitionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SpeechRecognitionEnabled)));
        defaults.get().set(WebPreferencesKey::speechSynthesisAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SpeechSynthesisAPIEnabled)));
        defaults.get().set(WebPreferencesKey::storageAPIEstimateEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_StorageAPIEstimateEnabled)));
        defaults.get().set(WebPreferencesKey::storageAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_StorageAPIEnabled)));
        defaults.get().set(WebPreferencesKey::storageAccessAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_StorageAccessAPIEnabled)));
        defaults.get().set(WebPreferencesKey::storageBlockingPolicyKey(), Value(uint32_t(DEFAULT_VALUE_FOR_StorageBlockingPolicy)));
        defaults.get().set(WebPreferencesKey::processSwapOnCrossSiteNavigationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ProcessSwapOnCrossSiteNavigationEnabled)));
        defaults.get().set(WebPreferencesKey::processSwapOnCrossSiteWindowOpenEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ProcessSwapOnCrossSiteWindowOpenEnabled)));
        defaults.get().set(WebPreferencesKey::syntheticEditingCommandsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_SyntheticEditingCommandsEnabled)));
        defaults.get().set(WebPreferencesKey::shouldTakeNearSuspendedAssertionsKey(), Value(bool(DEFAULT_VALUE_FOR_ShouldTakeNearSuspendedAssertions)));
#if ENABLE(IMAGE_ANALYSIS)
        defaults.get().set(WebPreferencesKey::textRecognitionInVideosEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_TextRecognitionInVideosEnabled)));
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
        defaults.get().set(WebPreferencesKey::threadedAnimationResolutionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ThreadedAnimationResolutionEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::tiledScrollingIndicatorVisibleKey(), Value(bool(DEFAULT_VALUE_FOR_TiledScrollingIndicatorVisible)));
#if ENABLE(INPUT_TYPE_TIME)
        defaults.get().set(WebPreferencesKey::inputTypeTimeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InputTypeTimeEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::trackConfigurationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_TrackConfigurationEnabled)));
        defaults.get().set(WebPreferencesKey::transformStreamAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_TransformStreamAPIEnabled)));
        defaults.get().set(WebPreferencesKey::undoManagerAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_UndoManagerAPIEnabled)));
        defaults.get().set(WebPreferencesKey::unprefixedFullscreenAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_UnprefixedFullscreenAPIEnabled)));
        defaults.get().set(WebPreferencesKey::upgradeKnownHostsToHTTPSEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_UpgradeKnownHostsToHTTPSEnabled)));
#if ENABLE(ARKIT_INLINE_PREVIEW)
        defaults.get().set(WebPreferencesKey::useARKitForModelKey(), Value(bool(DEFAULT_VALUE_FOR_UseARKitForModel)));
#endif
        defaults.get().set(WebPreferencesKey::useGeneralDirectoryForStorageKey(), Value(bool(DEFAULT_VALUE_FOR_UseGeneralDirectoryForStorage)));
#if HAVE(SC_CONTENT_SHARING_PICKER)
        defaults.get().set(WebPreferencesKey::useSCContentSharingPickerKey(), Value(bool(DEFAULT_VALUE_FOR_UseSCContentSharingPicker)));
#endif
#if HAVE(SCENEKIT)
        defaults.get().set(WebPreferencesKey::useSceneKitForModelKey(), Value(bool(DEFAULT_VALUE_FOR_UseSceneKitForModel)));
#endif
        defaults.get().set(WebPreferencesKey::useGiantTilesKey(), Value(bool(DEFAULT_VALUE_FOR_UseGiantTiles)));
        defaults.get().set(WebPreferencesKey::userActivationAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_UserActivationAPIEnabled)));
        defaults.get().set(WebPreferencesKey::userGesturePromisePropagationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_UserGesturePromisePropagationEnabled)));
#if ENABLE(VP9)
        defaults.get().set(WebPreferencesKey::vp9SWDecoderEnabledOnBatteryKey(), Value(bool(DEFAULT_VALUE_FOR_VP9SWDecoderEnabledOnBattery)));
#endif
#if ENABLE(SERVICE_WORKER)
        defaults.get().set(WebPreferencesKey::serviceWorkersUserGestureEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ServiceWorkersUserGestureEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::verifyWindowOpenUserGestureFromUIProcessKey(), Value(bool(DEFAULT_VALUE_FOR_VerifyWindowOpenUserGestureFromUIProcess)));
        defaults.get().set(WebPreferencesKey::verticalFormControlsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_VerticalFormControlsEnabled)));
        defaults.get().set(WebPreferencesKey::viewGestureDebuggingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_ViewGestureDebuggingEnabled)));
#if ENABLE(IMAGE_ANALYSIS)
        defaults.get().set(WebPreferencesKey::visualTranslationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_VisualTranslationEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::visualViewportAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_VisualViewportAPIEnabled)));
#if ENABLE(VORBIS)
        defaults.get().set(WebPreferencesKey::vorbisDecoderEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_VorbisDecoderEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::webAPIStatisticsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebAPIStatisticsEnabled)));
        defaults.get().set(WebPreferencesKey::webAPIsInShadowRealmEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebAPIsInShadowRealmEnabled)));
        defaults.get().set(WebPreferencesKey::webAnimationsCompositeOperationsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebAnimationsCompositeOperationsEnabled)));
        defaults.get().set(WebPreferencesKey::webAnimationsCustomEffectsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebAnimationsCustomEffectsEnabled)));
        defaults.get().set(WebPreferencesKey::webAnimationsCustomFrameRateEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebAnimationsCustomFrameRateEnabled)));
        defaults.get().set(WebPreferencesKey::webAnimationsIterationCompositeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebAnimationsIterationCompositeEnabled)));
        defaults.get().set(WebPreferencesKey::webAnimationsMutableTimelinesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebAnimationsMutableTimelinesEnabled)));
#if ENABLE(WEB_ARCHIVE)
        defaults.get().set(WebPreferencesKey::webArchiveDebugModeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebArchiveDebugModeEnabled)));
#endif
#if ENABLE(WEB_ARCHIVE)
        defaults.get().set(WebPreferencesKey::webArchiveTestingModeEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebArchiveTestingModeEnabled)));
#endif
#if ENABLE(WEB_AUTHN)
        defaults.get().set(WebPreferencesKey::webAuthenticationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebAuthenticationEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::webCryptoSafeCurvesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebCryptoSafeCurvesEnabled)));
        defaults.get().set(WebPreferencesKey::webLocksAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebLocksAPIEnabled)));
        defaults.get().set(WebPreferencesKey::webShareFileAPIEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebShareFileAPIEnabled)));
        defaults.get().set(WebPreferencesKey::webShareEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebShareEnabled)));
#if ENABLE(WEBASSEMBLY)
        defaults.get().set(WebPreferencesKey::webAssemblyESMIntegrationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebAssemblyESMIntegrationEnabled)));
#endif
#if ENABLE(WEB_CODECS)
        defaults.get().set(WebPreferencesKey::webCodecsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebCodecsEnabled)));
#endif
#if ENABLE(WEB_CODECS)
        defaults.get().set(WebPreferencesKey::webCodecsAV1EnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebCodecsAV1Enabled)));
#endif
#if ENABLE(WEB_CODECS)
        defaults.get().set(WebPreferencesKey::webCodecsHEVCEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebCodecsHEVCEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::webGLDraftExtensionsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebGLDraftExtensionsEnabled)));
        defaults.get().set(WebPreferencesKey::webGLTimerQueriesEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebGLTimerQueriesEnabled)));
#if ENABLE(WEBGL) && PLATFORM(COCOA)
        defaults.get().set(WebPreferencesKey::webGLUsingMetalKey(), Value(bool(DEFAULT_VALUE_FOR_WebGLUsingMetal)));
#endif
        defaults.get().set(WebPreferencesKey::webGLEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebGLEnabled)));
        defaults.get().set(WebPreferencesKey::webGPUEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebGPUEnabled)));
        defaults.get().set(WebPreferencesKey::webInspectorEngineeringSettingsAllowedKey(), Value(bool(DEFAULT_VALUE_FOR_WebInspectorEngineeringSettingsAllowed)));
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCAV1CodecEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCAV1CodecEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::webRTCAudioLatencyAdaptationEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCAudioLatencyAdaptationEnabled)));
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCDTMFEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCDTMFEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCEncodedTransformEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCEncodedTransformEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCH264HardwareEncoderEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCH264HardwareEncoderEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCH264LowLatencyEncoderEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCH264LowLatencyEncoderEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCH264SimulcastEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCH264SimulcastEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCH265CodecEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCH265CodecEnabled)));
#endif
#if USE(LIBWEBRTC)
        defaults.get().set(WebPreferencesKey::webRTCMediaPipelineAdditionalLoggingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCMediaPipelineAdditionalLoggingEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::peerConnectionEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_PeerConnectionEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCPlatformTCPSocketsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCPlatformTCPSocketsEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCPlatformUDPSocketsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCPlatformUDPSocketsEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCRemoteVideoFrameEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCRemoteVideoFrameEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCSFrameTransformEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCSFrameTransformEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCSocketsProxyingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCSocketsProxyingEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCVP9Profile0CodecEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCVP9Profile0CodecEnabled)));
#endif
#if ENABLE(WEB_RTC)
        defaults.get().set(WebPreferencesKey::webRTCVP9Profile2CodecEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebRTCVP9Profile2CodecEnabled)));
#endif
#if ENABLE(WEBXR)
        defaults.get().set(WebPreferencesKey::webXRAugmentedRealityModuleEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebXRAugmentedRealityModuleEnabled)));
#endif
#if ENABLE(WEBXR)
        defaults.get().set(WebPreferencesKey::webXREnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebXREnabled)));
#endif
#if ENABLE(WEBXR)
        defaults.get().set(WebPreferencesKey::webXRGamepadsModuleEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebXRGamepadsModuleEnabled)));
#endif
#if ENABLE(WEBXR_HANDS)
        defaults.get().set(WebPreferencesKey::webXRHandInputModuleEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_WebXRHandInputModuleEnabled)));
#endif
#if ENABLE(INPUT_TYPE_WEEK)
        defaults.get().set(WebPreferencesKey::inputTypeWeekEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InputTypeWeekEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::wheelEventGesturesBecomeNonBlockingKey(), Value(bool(DEFAULT_VALUE_FOR_WheelEventGesturesBecomeNonBlocking)));
        defaults.get().set(WebPreferencesKey::passiveWheelListenersAsDefaultOnDocumentKey(), Value(bool(DEFAULT_VALUE_FOR_PassiveWheelListenersAsDefaultOnDocument)));
        defaults.get().set(WebPreferencesKey::isFirstPartyWebsiteDataRemovalLiveOnTestingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled)));
        defaults.get().set(WebPreferencesKey::isFirstPartyWebsiteDataRemovalReproTestingEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalReproTestingEnabled)));
#if ENABLE(INPUT_TYPE_DATETIMELOCAL)
        defaults.get().set(WebPreferencesKey::inputTypeDateTimeLocalEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_InputTypeDateTimeLocalEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::httpEquivEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_HTTPEquivEnabled)));
#if ENABLE(IOS_FORM_CONTROL_REFRESH)
        defaults.get().set(WebPreferencesKey::iOSFormControlRefreshEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_IOSFormControlRefreshEnabled)));
#endif
        defaults.get().set(WebPreferencesKey::lineHeightUnitsEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_LineHeightUnitsEnabled)));
        defaults.get().set(WebPreferencesKey::requestIdleCallbackEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_RequestIdleCallbackEnabled)));
        defaults.get().set(WebPreferencesKey::cssWordBreakAutoEnabledKey(), Value(bool(DEFAULT_VALUE_FOR_CSSWordBreakAutoEnabled)));
    }

    return defaults;
}

} // namespace WebKit
