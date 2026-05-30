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
#include "WebPage.h"

#include "WebPreferencesDefinitions.h"
#include "WebPreferencesKeys.h"
#include "WebPreferencesStore.h"
#include <WebCore/DeprecatedGlobalSettings.h>
#include <WebCore/Page.h>
#include <WebCore/Settings.h>

namespace WebKit {

void WebPage::updateSettingsGenerated(const WebPreferencesStore& store, WebCore::Settings& settings)
{
    settings.setAcceleratedCompositingEnabled(store.getBoolValueForKey(WebPreferencesKey::acceleratedCompositingEnabledKey()));
    settings.setAcceleratedCompositingForFixedPositionEnabled(store.getBoolValueForKey(WebPreferencesKey::acceleratedCompositingForFixedPositionEnabledKey()));
    settings.setAggressiveTileRetentionEnabled(store.getBoolValueForKey(WebPreferencesKey::aggressiveTileRetentionEnabledKey()));
    settings.setAllowContentSecurityPolicySourceStarToMatchAnyProtocol(store.getBoolValueForKey(WebPreferencesKey::allowContentSecurityPolicySourceStarToMatchAnyProtocolKey()));
    settings.setAllowCrossOriginSubresourcesToAskForCredentials(store.getBoolValueForKey(WebPreferencesKey::allowCrossOriginSubresourcesToAskForCredentialsKey()));
    settings.setAllowDisplayOfInsecureContent(store.getBoolValueForKey(WebPreferencesKey::allowDisplayOfInsecureContentKey()));
    settings.setAllowFileAccessFromFileURLs(store.getBoolValueForKey(WebPreferencesKey::allowFileAccessFromFileURLsKey()));
    settings.setAllowMultiElementImplicitSubmission(store.getBoolValueForKey(WebPreferencesKey::allowMultiElementImplicitSubmissionKey()));
    settings.setAllowRunningOfInsecureContent(store.getBoolValueForKey(WebPreferencesKey::allowRunningOfInsecureContentKey()));
    settings.setAllowSettingAnyXHRHeaderFromFileURLs(store.getBoolValueForKey(WebPreferencesKey::allowSettingAnyXHRHeaderFromFileURLsKey()));
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    settings.setAllowsAirPlayForMediaPlayback(store.getBoolValueForKey(WebPreferencesKey::allowsAirPlayForMediaPlaybackKey()));
#endif
    settings.setAllowsInlineMediaPlayback(store.getBoolValueForKey(WebPreferencesKey::allowsInlineMediaPlaybackKey()));
    settings.setAllowsInlineMediaPlaybackAfterFullscreen(store.getBoolValueForKey(WebPreferencesKey::allowsInlineMediaPlaybackAfterFullscreenKey()));
    settings.setAllowsPictureInPictureMediaPlayback(store.getBoolValueForKey(WebPreferencesKey::allowsPictureInPictureMediaPlaybackKey()));
#if PLATFORM(IOS_FAMILY)
    settings.setAlternateFormControlDesignEnabled(store.getBoolValueForKey(WebPreferencesKey::alternateFormControlDesignEnabledKey()));
#endif
#if PLATFORM(IOS_FAMILY)
    settings.setAlternateFullScreenControlDesignEnabled(store.getBoolValueForKey(WebPreferencesKey::alternateFullScreenControlDesignEnabledKey()));
#endif
    settings.setAnimatedImageAsyncDecodingEnabled(store.getBoolValueForKey(WebPreferencesKey::animatedImageAsyncDecodingEnabledKey()));
    settings.setAppleMailPaginationQuirkEnabled(store.getBoolValueForKey(WebPreferencesKey::appleMailPaginationQuirkEnabledKey()));
#if ENABLE(APPLE_PAY)
    settings.setApplePayCapabilityDisclosureAllowed(store.getBoolValueForKey(WebPreferencesKey::applePayCapabilityDisclosureAllowedKey()));
#endif
#if ENABLE(APPLE_PAY)
    settings.setApplePayEnabled(store.getBoolValueForKey(WebPreferencesKey::applePayEnabledKey()));
#endif
    settings.setAsynchronousSpellCheckingEnabled(store.getBoolValueForKey(WebPreferencesKey::asynchronousSpellCheckingEnabledKey()));
    settings.setAudioControlsScaleWithPageZoom(store.getBoolValueForKey(WebPreferencesKey::audioControlsScaleWithPageZoomKey()));
    settings.setAuthorAndUserStylesEnabled(store.getBoolValueForKey(WebPreferencesKey::authorAndUserStylesEnabledKey()));
    settings.setBackspaceKeyNavigationEnabled(store.getBoolValueForKey(WebPreferencesKey::backspaceKeyNavigationEnabledKey()));
    settings.setCaretBrowsingEnabled(store.getBoolValueForKey(WebPreferencesKey::caretBrowsingEnabledKey()));
    settings.setColorFilterEnabled(store.getBoolValueForKey(WebPreferencesKey::colorFilterEnabledKey()));
    settings.setConstantPropertiesEnabled(store.getBoolValueForKey(WebPreferencesKey::constantPropertiesEnabledKey()));
#if ENABLE(CONTENT_CHANGE_OBSERVER)
    settings.setContentChangeObserverEnabled(store.getBoolValueForKey(WebPreferencesKey::contentChangeObserverEnabledKey()));
#endif
    settings.setContentDispositionAttachmentSandboxEnabled(store.getBoolValueForKey(WebPreferencesKey::contentDispositionAttachmentSandboxEnabledKey()));
#if ENABLE(CONTEXT_MENU_QR_CODE_DETECTION)
    settings.setContextMenuQRCodeDetectionEnabled(store.getBoolValueForKey(WebPreferencesKey::contextMenuQRCodeDetectionEnabledKey()));
#endif
    settings.setCursiveFontFamily(store.getStringValueForKey(WebPreferencesKey::cursiveFontFamilyKey()));
    settings.setDNSPrefetchingEnabled(store.getBoolValueForKey(WebPreferencesKey::dnsPrefetchingEnabledKey()));
    settings.setDOMPasteAllowed(store.getBoolValueForKey(WebPreferencesKey::domPasteAllowedKey()));
#if ENABLE(DATA_DETECTION)
    settings.setDataDetectorTypes(static_cast<WebCore::DataDetectorType>(store.getUInt32ValueForKey(WebPreferencesKey::dataDetectorTypesKey())));
#endif
    settings.setDefaultFixedFontSize(store.getDoubleValueForKey(WebPreferencesKey::defaultFixedFontSizeKey()));
    settings.setDefaultFontSize(store.getDoubleValueForKey(WebPreferencesKey::defaultFontSizeKey()));
    settings.setDefaultTextEncodingName(store.getStringValueForKey(WebPreferencesKey::defaultTextEncodingNameKey()));
    settings.setDeveloperExtrasEnabled(store.getBoolValueForKey(WebPreferencesKey::developerExtrasEnabledKey()));
    settings.setDeviceHeight(store.getUInt32ValueForKey(WebPreferencesKey::deviceHeightKey()));
#if ENABLE(DEVICE_ORIENTATION)
    settings.setDeviceOrientationEventEnabled(store.getBoolValueForKey(WebPreferencesKey::deviceOrientationEventEnabledKey()));
#endif
#if ENABLE(DEVICE_ORIENTATION)
    settings.setDeviceOrientationPermissionAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::deviceOrientationPermissionAPIEnabledKey()));
#endif
    settings.setDeviceWidth(store.getUInt32ValueForKey(WebPreferencesKey::deviceWidthKey()));
    settings.setDisabledAdaptationsMetaTagEnabled(store.getBoolValueForKey(WebPreferencesKey::disabledAdaptationsMetaTagEnabledKey()));
#if ENABLE(DOWNLOAD_ATTRIBUTE)
    settings.setDownloadAttributeEnabled(store.getBoolValueForKey(WebPreferencesKey::downloadAttributeEnabledKey()));
#endif
    settings.setEditableLinkBehavior(static_cast<WebCore::EditableLinkBehavior>(store.getUInt32ValueForKey(WebPreferencesKey::editableLinkBehaviorKey())));
    settings.setEnableInheritURIQueryComponent(store.getBoolValueForKey(WebPreferencesKey::enableInheritURIQueryComponentKey()));
#if ENABLE(ENCRYPTED_MEDIA)
    settings.setEncryptedMediaAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::encryptedMediaAPIEnabledKey()));
#endif
    settings.setFTPDirectoryTemplatePath(store.getStringValueForKey(WebPreferencesKey::ftpDirectoryTemplatePathKey()));
    settings.setFantasyFontFamily(store.getStringValueForKey(WebPreferencesKey::fantasyFontFamilyKey()));
    settings.setFixedFontFamily(store.getStringValueForKey(WebPreferencesKey::fixedFontFamilyKey()));
    settings.setForceFTPDirectoryListings(store.getBoolValueForKey(WebPreferencesKey::forceFTPDirectoryListingsKey()));
    settings.setForceWebGLUsesLowPower(store.getBoolValueForKey(WebPreferencesKey::forceWebGLUsesLowPowerKey()));
    settings.setHiddenPageCSSAnimationSuspensionEnabled(store.getBoolValueForKey(WebPreferencesKey::hiddenPageCSSAnimationSuspensionEnabledKey()));
    settings.setIncompleteImageBorderEnabled(store.getBoolValueForKey(WebPreferencesKey::incompleteImageBorderEnabledKey()));
#if HAVE(INCREMENTAL_PDF_APIS)
    settings.setIncrementalPDFLoadingEnabled(store.getBoolValueForKey(WebPreferencesKey::incrementalPDFLoadingEnabledKey()));
#endif
    settings.setIncrementalRenderingSuppressionTimeoutInSeconds(store.getDoubleValueForKey(WebPreferencesKey::incrementalRenderingSuppressionTimeoutKey()));
    settings.setInlineMediaPlaybackRequiresPlaysInlineAttribute(store.getBoolValueForKey(WebPreferencesKey::inlineMediaPlaybackRequiresPlaysInlineAttributeKey()));
    settings.setInteractionRegionInlinePadding(store.getDoubleValueForKey(WebPreferencesKey::interactionRegionInlinePaddingKey()));
    settings.setInteractionRegionMinimumCornerRadius(store.getDoubleValueForKey(WebPreferencesKey::interactionRegionMinimumCornerRadiusKey()));
#if ENABLE(MEDIA_STREAM)
    settings.setInterruptAudioOnPageVisibilityChangeEnabled(store.getBoolValueForKey(WebPreferencesKey::interruptAudioOnPageVisibilityChangeEnabledKey()));
#endif
#if ENABLE(MEDIA_STREAM)
    settings.setInterruptVideoOnPageVisibilityChangeEnabled(store.getBoolValueForKey(WebPreferencesKey::interruptVideoOnPageVisibilityChangeEnabledKey()));
#endif
    settings.setInvisibleAutoplayNotPermitted(store.getBoolValueForKey(WebPreferencesKey::invisibleAutoplayNotPermittedKey()));
    settings.setJavaScriptCanAccessClipboard(store.getBoolValueForKey(WebPreferencesKey::javaScriptCanAccessClipboardKey()));
    settings.setJavaScriptCanOpenWindowsAutomatically(store.getBoolValueForKey(WebPreferencesKey::javaScriptCanOpenWindowsAutomaticallyKey()));
    settings.setScriptMarkupEnabled(store.getBoolValueForKey(WebPreferencesKey::javaScriptMarkupEnabledKey()));
    settings.setJavaScriptRuntimeFlags(static_cast<JSC::RuntimeFlags>(store.getUInt32ValueForKey(WebPreferencesKey::javaScriptRuntimeFlagsKey())));
    settings.setLargeImageAsyncDecodingEnabled(store.getBoolValueForKey(WebPreferencesKey::largeImageAsyncDecodingEnabledKey()));
    settings.setLayoutFallbackWidth(store.getUInt32ValueForKey(WebPreferencesKey::layoutFallbackWidthKey()));
    settings.setLayoutViewportHeightExpansionFactor(store.getDoubleValueForKey(WebPreferencesKey::layoutViewportHeightExpansionFactorKey()));
    settings.setLinkPreconnectEnabled(store.getBoolValueForKey(WebPreferencesKey::linkPreconnectKey()));
    settings.setLinkPreloadEnabled(store.getBoolValueForKey(WebPreferencesKey::linkPreloadEnabledKey()));
    settings.setLoadDeferringEnabled(store.getBoolValueForKey(WebPreferencesKey::loadDeferringEnabledKey()));
    settings.setLoadsImagesAutomatically(store.getBoolValueForKey(WebPreferencesKey::loadsImagesAutomaticallyKey()));
#if ENABLE(MANAGED_MEDIA_SOURCE)
    settings.setManagedMediaSourceHighThreshold(store.getDoubleValueForKey(WebPreferencesKey::managedMediaSourceHighThresholdKey()));
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    settings.setManagedMediaSourceLowThreshold(store.getDoubleValueForKey(WebPreferencesKey::managedMediaSourceLowThresholdKey()));
#endif
#if ENABLE(MATHML)
    settings.setMathMLEnabled(store.getBoolValueForKey(WebPreferencesKey::mathMLEnabledKey()));
#endif
    settings.setMaxParseDuration(store.getDoubleValueForKey(WebPreferencesKey::maxParseDurationKey()));
    settings.setMediaCapabilitiesEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaCapabilitiesEnabledKey()));
    settings.setMediaContentTypesRequiringHardwareSupport(store.getStringValueForKey(WebPreferencesKey::mediaContentTypesRequiringHardwareSupportKey()));
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS)
    settings.setMediaControlsContextMenusEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaControlsContextMenusEnabledKey()));
#endif
    settings.setMediaControlsScaleWithPageZoom(store.getBoolValueForKey(WebPreferencesKey::mediaControlsScaleWithPageZoomKey()));
    settings.setMediaDataLoadsAutomatically(store.getBoolValueForKey(WebPreferencesKey::mediaDataLoadsAutomaticallyKey()));
#if ENABLE(VIDEO)
    settings.setMediaEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaEnabledKey()));
#endif
    settings.setMediaPreferredFullscreenWidth(store.getDoubleValueForKey(WebPreferencesKey::mediaPreferredFullscreenWidthKey()));
    settings.setMediaPreloadingEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaPreloadingEnabledKey()));
#if ENABLE(MEDIA_STREAM)
    settings.setMediaStreamEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaStreamEnabledKey()));
#endif
    settings.setMediaUserGestureInheritsFromDocument(store.getBoolValueForKey(WebPreferencesKey::mediaUserGestureInheritsFromDocumentKey()));
    settings.setMenuItemElementEnabled(store.getBoolValueForKey(WebPreferencesKey::menuItemElementEnabledKey()));
    settings.setMinimumFontSize(store.getDoubleValueForKey(WebPreferencesKey::minimumFontSizeKey()));
    settings.setMinimumLogicalFontSize(store.getDoubleValueForKey(WebPreferencesKey::minimumLogicalFontSizeKey()));
#if ENABLE(TEXT_AUTOSIZING)
    settings.setMinimumZoomFontSize(store.getDoubleValueForKey(WebPreferencesKey::minimumZoomFontSizeKey()));
#endif
    settings.setMockScrollbarsControllerEnabled(store.getBoolValueForKey(WebPreferencesKey::mockScrollbarsControllerEnabledKey()));
    settings.setNeedsAdobeFrameReloadingQuirk(store.getBoolValueForKey(WebPreferencesKey::needsAdobeFrameReloadingQuirkKey()));
    settings.setNeedsFrameNameFallbackToIdQuirk(store.getBoolValueForKey(WebPreferencesKey::needsFrameNameFallbackToIdQuirkKey()));
    settings.setNeedsKeyboardEventDisambiguationQuirks(store.getBoolValueForKey(WebPreferencesKey::needsKeyboardEventDisambiguationQuirksKey()));
    settings.setOfflineWebApplicationCacheEnabled(store.getBoolValueForKey(WebPreferencesKey::offlineWebApplicationCacheEnabledKey()));
    settings.setPassiveTouchListenersAsDefaultOnDocument(store.getBoolValueForKey(WebPreferencesKey::passiveTouchListenersAsDefaultOnDocumentKey()));
    settings.setPasswordEchoDurationInSeconds(store.getDoubleValueForKey(WebPreferencesKey::passwordEchoDurationKey()));
    settings.setPasswordEchoEnabled(store.getBoolValueForKey(WebPreferencesKey::passwordEchoEnabledKey()));
    settings.setPictographFontFamily(store.getStringValueForKey(WebPreferencesKey::pictographFontFamilyKey()));
#if ENABLE(PICTURE_IN_PICTURE_API)
    settings.setPictureInPictureAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::pictureInPictureAPIEnabledKey()));
#endif
    settings.setPitchCorrectionAlgorithm(static_cast<WebCore::MediaPlayerEnums::PitchCorrectionAlgorithm>(store.getUInt32ValueForKey(WebPreferencesKey::pitchCorrectionAlgorithmKey())));
    settings.setPluginsEnabled(store.getBoolValueForKey(WebPreferencesKey::pluginsEnabledKey()));
    settings.setPunchOutWhiteBackgroundsInDarkMode(store.getBoolValueForKey(WebPreferencesKey::punchOutWhiteBackgroundsInDarkModeKey()));
    settings.setRequiresPageVisibilityToPlayAudio(store.getBoolValueForKey(WebPreferencesKey::requiresPageVisibilityToPlayAudioKey()));
    settings.setRequiresUserGestureForAudioPlayback(store.getBoolValueForKey(WebPreferencesKey::requiresUserGestureForAudioPlaybackKey()));
    settings.setRequiresUserGestureForVideoPlayback(store.getBoolValueForKey(WebPreferencesKey::requiresUserGestureForVideoPlaybackKey()));
    settings.setRequiresUserGestureToLoadVideo(store.getBoolValueForKey(WebPreferencesKey::requiresUserGestureToLoadVideoKey()));
#if HAVE(RUBBER_BANDING)
    settings.setRubberBandingForSubScrollableRegionsEnabled(store.getBoolValueForKey(WebPreferencesKey::rubberBandingForSubScrollableRegionsEnabledKey()));
#endif
    settings.setSampledPageTopColorMaxDifference(store.getDoubleValueForKey(WebPreferencesKey::sampledPageTopColorMaxDifferenceKey()));
    settings.setSampledPageTopColorMinHeight(store.getDoubleValueForKey(WebPreferencesKey::sampledPageTopColorMinHeightKey()));
    settings.setSansSerifFontFamily(store.getStringValueForKey(WebPreferencesKey::sansSerifFontFamilyKey()));
    settings.setSelectTrailingWhitespaceEnabled(store.getBoolValueForKey(WebPreferencesKey::selectTrailingWhitespaceEnabledKey()));
    settings.setSerifFontFamily(store.getStringValueForKey(WebPreferencesKey::serifFontFamilyKey()));
#if ENABLE(SERVICE_CONTROLS)
    settings.setServiceControlsEnabled(store.getBoolValueForKey(WebPreferencesKey::serviceControlsEnabledKey()));
#endif
    settings.setShouldAllowUserInstalledFonts(store.getBoolValueForKey(WebPreferencesKey::shouldAllowUserInstalledFontsKey()));
    settings.setShouldConvertInvalidURLsToBlank(store.getBoolValueForKey(WebPreferencesKey::shouldConvertInvalidURLsToBlankKey()));
    settings.setShouldConvertPositionStyleOnCopy(store.getBoolValueForKey(WebPreferencesKey::shouldConvertPositionStyleOnCopyKey()));
    settings.setShouldDecidePolicyBeforeLoadingQuickLookPreview(store.getBoolValueForKey(WebPreferencesKey::shouldDecidePolicyBeforeLoadingQuickLookPreviewKey()));
#if ENABLE(VIDEO)
    settings.setShouldDisplayCaptions(store.getBoolValueForKey(WebPreferencesKey::shouldDisplayCaptionsKey()));
#endif
#if ENABLE(VIDEO)
    settings.setShouldDisplaySubtitles(store.getBoolValueForKey(WebPreferencesKey::shouldDisplaySubtitlesKey()));
#endif
#if ENABLE(VIDEO)
    settings.setShouldDisplayTextDescriptions(store.getBoolValueForKey(WebPreferencesKey::shouldDisplayTextDescriptionsKey()));
#endif
#if ENABLE(TEXT_AUTOSIZING)
    settings.setShouldEnableTextAutosizingBoost(store.getBoolValueForKey(WebPreferencesKey::shouldEnableTextAutosizingBoostKey()));
#endif
    settings.setShouldIgnoreMetaViewport(store.getBoolValueForKey(WebPreferencesKey::shouldIgnoreMetaViewportKey()));
    settings.setShouldPrintBackgrounds(store.getBoolValueForKey(WebPreferencesKey::shouldPrintBackgroundsKey()));
    settings.setShouldRespectImageOrientation(store.getBoolValueForKey(WebPreferencesKey::shouldRespectImageOrientationKey()));
    settings.setShouldRestrictBaseURLSchemes(store.getBoolValueForKey(WebPreferencesKey::shouldRestrictBaseURLSchemesKey()));
    settings.setShouldSuppressTextInputFromEditingDuringProvisionalNavigation(store.getBoolValueForKey(WebPreferencesKey::shouldSuppressTextInputFromEditingDuringProvisionalNavigationKey()));
    settings.setShouldUseServiceWorkerShortTimeout(store.getBoolValueForKey(WebPreferencesKey::shouldUseServiceWorkerShortTimeoutKey()));
    settings.setShowsToolTipOverTruncatedText(store.getBoolValueForKey(WebPreferencesKey::showsToolTipOverTruncatedTextKey()));
    settings.setShowsURLsInToolTips(store.getBoolValueForKey(WebPreferencesKey::showsURLsInToolTipsEnabledKey()));
    settings.setShrinksStandaloneImagesToFit(store.getBoolValueForKey(WebPreferencesKey::shrinksStandaloneImagesToFitKey()));
    settings.setSmartInsertDeleteEnabled(store.getBoolValueForKey(WebPreferencesKey::smartInsertDeleteEnabledKey()));
#if ENABLE(MEDIA_SOURCE)
    settings.setSourceBufferChangeTypeEnabled(store.getBoolValueForKey(WebPreferencesKey::sourceBufferChangeTypeEnabledKey()));
#endif
    settings.setSpatialNavigationEnabled(store.getBoolValueForKey(WebPreferencesKey::spatialNavigationEnabledKey()));
    settings.setStandalone(store.getBoolValueForKey(WebPreferencesKey::standaloneKey()));
    settings.setStandardFontFamily(store.getStringValueForKey(WebPreferencesKey::standardFontFamilyKey()));
    settings.setSuppressesIncrementalRendering(store.getBoolValueForKey(WebPreferencesKey::suppressesIncrementalRenderingKey()));
    settings.setSystemLayoutDirection(static_cast<WebCore::TextDirection>(store.getUInt32ValueForKey(WebPreferencesKey::systemLayoutDirectionKey())));
#if USE(SYSTEM_PREVIEW)
    settings.setSystemPreviewEnabled(store.getBoolValueForKey(WebPreferencesKey::systemPreviewEnabledKey()));
#endif
    settings.setTelephoneNumberParsingEnabled(store.getBoolValueForKey(WebPreferencesKey::telephoneNumberParsingEnabledKey()));
    settings.setTemporaryTileCohortRetentionEnabled(store.getBoolValueForKey(WebPreferencesKey::temporaryTileCohortRetentionEnabledKey()));
    settings.setTextAreasAreResizable(store.getBoolValueForKey(WebPreferencesKey::textAreasAreResizableKey()));
#if ENABLE(TEXT_AUTOSIZING)
    settings.setTextAutosizingEnabled(store.getBoolValueForKey(WebPreferencesKey::textAutosizingEnabledKey()));
#endif
    settings.setTextInteractionEnabled(store.getBoolValueForKey(WebPreferencesKey::textInteractionEnabledKey()));
    settings.setTreatsAnyTextCSSLinkAsStylesheet(store.getBoolValueForKey(WebPreferencesKey::treatsAnyTextCSSLinkAsStylesheetKey()));
    settings.setUseImageDocumentForSubframePDF(store.getBoolValueForKey(WebPreferencesKey::useImageDocumentForSubframePDFKey()));
    settings.setUseLegacyBackgroundSizeShorthandBehavior(store.getBoolValueForKey(WebPreferencesKey::useLegacyBackgroundSizeShorthandBehaviorKey()));
    settings.setUsePreHTML5ParserQuirks(store.getBoolValueForKey(WebPreferencesKey::usePreHTML5ParserQuirksKey()));
    settings.setUserInterfaceDirectionPolicy(static_cast<WebCore::UserInterfaceDirectionPolicy>(store.getUInt32ValueForKey(WebPreferencesKey::userInterfaceDirectionPolicyKey())));
    settings.setUsesBackForwardCache(store.getBoolValueForKey(WebPreferencesKey::usesBackForwardCacheKey()));
    settings.setUsesEncodingDetector(store.getBoolValueForKey(WebPreferencesKey::usesEncodingDetectorKey()));
#if ENABLE(VP9)
    settings.setVP9DecoderEnabled(store.getBoolValueForKey(WebPreferencesKey::vp9DecoderEnabledKey()));
#endif
#if PLATFORM(IOS_FAMILY)
    settings.setVideoFullscreenRequiresElementFullscreen(store.getBoolValueForKey(WebPreferencesKey::videoFullscreenRequiresElementFullscreenKey()));
#endif
    settings.setVideoPresentationModeAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::videoPresentationModeAPIEnabledKey()));
#if ENABLE(VIDEO)
    settings.setVideoQualityIncludesDisplayCompositingEnabled(store.getBoolValueForKey(WebPreferencesKey::videoQualityIncludesDisplayCompositingEnabledKey()));
#endif
    settings.setVisibleDebugOverlayRegions(store.getUInt32ValueForKey(WebPreferencesKey::visibleDebugOverlayRegionsKey()));
    settings.setVisualViewportEnabled(store.getBoolValueForKey(WebPreferencesKey::visualViewportEnabledKey()));
    settings.setWantsBalancedSetDefersLoadingBehavior(store.getBoolValueForKey(WebPreferencesKey::wantsBalancedSetDefersLoadingBehaviorKey()));
#if ENABLE(WEB_AUDIO)
    settings.setWebAudioEnabled(store.getBoolValueForKey(WebPreferencesKey::webAudioEnabledKey()));
#endif
    settings.setWebSecurityEnabled(store.getBoolValueForKey(WebPreferencesKey::webSecurityEnabledKey()));
    settings.setWebSocketEnabled(store.getBoolValueForKey(WebPreferencesKey::webSocketEnabledKey()));
    settings.setWindowFocusRestricted(store.getBoolValueForKey(WebPreferencesKey::windowFocusRestrictedKey()));
    settings.setWirelessPlaybackTargetAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::wirelessPlaybackTargetAPIEnabledKey()));
    settings.setDirPseudoEnabled(store.getBoolValueForKey(WebPreferencesKey::dirPseudoEnabledKey()));
    settings.setFocusVisibleEnabled(store.getBoolValueForKey(WebPreferencesKey::focusVisibleEnabledKey()));
    settings.setHasPseudoClassEnabled(store.getBoolValueForKey(WebPreferencesKey::hasPseudoClassEnabledKey()));
    settings.setPageAtRuleSupportEnabled(store.getBoolValueForKey(WebPreferencesKey::pageAtRuleSupportEnabledKey()));
    settings.setAriaReflectionForElementReferencesEnabled(store.getBoolValueForKey(WebPreferencesKey::ariaReflectionForElementReferencesEnabledKey()));
    settings.setAbortSignalAnyOperationEnabled(store.getBoolValueForKey(WebPreferencesKey::abortSignalAnyOperationEnabledKey()));
#if USE(CORE_IMAGE)
    settings.setAcceleratedFiltersEnabled(store.getBoolValueForKey(WebPreferencesKey::acceleratedFiltersEnabledKey()));
#endif
    settings.setAccessHandleEnabled(store.getBoolValueForKey(WebPreferencesKey::accessHandleEnabledKey()));
    settings.setDOMTestingAPIsEnabled(store.getBoolValueForKey(WebPreferencesKey::domTestingAPIsEnabledKey()));
    settings.setAllowMediaContentTypesRequiringHardwareSupportAsFallback(store.getBoolValueForKey(WebPreferencesKey::allowMediaContentTypesRequiringHardwareSupportAsFallbackKey()));
#if PLATFORM(IOS_FAMILY)
    settings.setAllowViewportShrinkToFitContent(store.getBoolValueForKey(WebPreferencesKey::allowViewportShrinkToFitContentKey()));
#endif
#if ENABLE(WEBGL)
    settings.setAllowWebGLInWorkers(store.getBoolValueForKey(WebPreferencesKey::allowWebGLInWorkersKey()));
#endif
#if ENABLE(MEDIA_STREAM)
    settings.setPerElementSpeakerSelectionEnabled(store.getBoolValueForKey(WebPreferencesKey::perElementSpeakerSelectionEnabledKey()));
#endif
#if ENABLE(MEDIA_STREAM)
    settings.setExposeSpeakersEnabled(store.getBoolValueForKey(WebPreferencesKey::exposeSpeakersEnabledKey()));
#endif
    settings.setAllowTopNavigationToDataURLs(store.getBoolValueForKey(WebPreferencesKey::allowTopNavigationToDataURLsKey()));
    settings.setAllowUniversalAccessFromFileURLs(store.getBoolValueForKey(WebPreferencesKey::allowUniversalAccessFromFileURLsKey()));
#if ENABLE(ALTERNATE_WEBM_PLAYER)
    settings.setAlternateWebMPlayerEnabled(store.getBoolValueForKey(WebPreferencesKey::alternateWebMPlayerEnabledKey()));
#endif
#if ENABLE(BADGING)
    settings.setAppBadgeEnabled(store.getBoolValueForKey(WebPreferencesKey::appBadgeEnabledKey()));
#endif
#if ENABLE(APP_HIGHLIGHTS)
    settings.setAppHighlightsEnabled(store.getBoolValueForKey(WebPreferencesKey::appHighlightsEnabledKey()));
#endif
    settings.setAspectRatioOfImgFromWidthAndHeightEnabled(store.getBoolValueForKey(WebPreferencesKey::aspectRatioOfImgFromWidthAndHeightEnabledKey()));
    settings.setAsyncFrameScrollingEnabled(store.getBoolValueForKey(WebPreferencesKey::asyncFrameScrollingEnabledKey()));
    settings.setAsyncOverflowScrollingEnabled(store.getBoolValueForKey(WebPreferencesKey::asyncOverflowScrollingEnabledKey()));
    settings.setAsyncClipboardAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::asyncClipboardAPIEnabledKey()));
#if ENABLE(ATTACHMENT_ELEMENT)
    settings.setAttachmentWideLayoutEnabled(store.getBoolValueForKey(WebPreferencesKey::attachmentWideLayoutEnabledKey()));
#endif
#if ENABLE(VIDEO)
    settings.setExtendedAudioDescriptionsEnabled(store.getBoolValueForKey(WebPreferencesKey::extendedAudioDescriptionsEnabledKey()));
#endif
#if ENABLE(VIDEO)
    settings.setAudioDescriptionsEnabled(store.getBoolValueForKey(WebPreferencesKey::audioDescriptionsEnabledKey()));
#endif
#if ENABLE(DOM_AUDIO_SESSION)
    settings.setDOMAudioSessionEnabled(store.getBoolValueForKey(WebPreferencesKey::domAudioSessionEnabledKey()));
#endif
#if ENABLE(DOM_AUDIO_SESSION)
    settings.setDOMAudioSessionFullEnabled(store.getBoolValueForKey(WebPreferencesKey::domAudioSessionFullEnabledKey()));
#endif
    settings.setBeaconAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::beaconAPIEnabledKey()));
    settings.setThirdPartyIframeRedirectBlockingEnabled(store.getBoolValueForKey(WebPreferencesKey::thirdPartyIframeRedirectBlockingEnabledKey()));
    settings.setBroadcastChannelEnabled(store.getBoolValueForKey(WebPreferencesKey::broadcastChannelEnabledKey()));
    settings.setBroadcastChannelOriginPartitioningEnabled(store.getBoolValueForKey(WebPreferencesKey::broadcastChannelOriginPartitioningEnabledKey()));
    settings.setCSS3DTransformInteroperabilityEnabled(store.getBoolValueForKey(WebPreferencesKey::css3DTransformInteroperabilityEnabledKey()));
    settings.setCSSCounterStyleAtRuleImageSymbolsEnabled(store.getBoolValueForKey(WebPreferencesKey::cssCounterStyleAtRuleImageSymbolsEnabledKey()));
    settings.setCSSCounterStyleAtRulesEnabled(store.getBoolValueForKey(WebPreferencesKey::cssCounterStyleAtRulesEnabledKey()));
    settings.setCSSFontFaceSizeAdjustEnabled(store.getBoolValueForKey(WebPreferencesKey::cssFontFaceSizeAdjustEnabledKey()));
    settings.setAccentColorEnabled(store.getBoolValueForKey(WebPreferencesKey::accentColorEnabledKey()));
    settings.setAspectRatioEnabled(store.getBoolValueForKey(WebPreferencesKey::aspectRatioEnabledKey()));
    settings.setCSSCascadeLayersEnabled(store.getBoolValueForKey(WebPreferencesKey::cssCascadeLayersEnabledKey()));
    settings.setCSSColor4(store.getBoolValueForKey(WebPreferencesKey::cssColor4Key()));
    settings.setCSSContainIntrinsicSizeEnabled(store.getBoolValueForKey(WebPreferencesKey::cssContainIntrinsicSizeEnabledKey()));
    settings.setCSSContainerQueriesEnabled(store.getBoolValueForKey(WebPreferencesKey::cssContainerQueriesEnabledKey()));
    settings.setCSSContainmentEnabled(store.getBoolValueForKey(WebPreferencesKey::cssContainmentEnabledKey()));
    settings.setCSSContentVisibilityEnabled(store.getBoolValueForKey(WebPreferencesKey::cssContentVisibilityEnabledKey()));
    settings.setCSSCustomPropertiesAndValuesEnabled(store.getBoolValueForKey(WebPreferencesKey::cssCustomPropertiesAndValuesEnabledKey()));
    settings.setCSSGradientInterpolationColorSpacesEnabled(store.getBoolValueForKey(WebPreferencesKey::cssGradientInterpolationColorSpacesEnabledKey()));
    settings.setCSSGradientPremultipliedAlphaInterpolationEnabled(store.getBoolValueForKey(WebPreferencesKey::cssGradientPremultipliedAlphaInterpolationEnabledKey()));
    settings.setCSSIndividualTransformPropertiesEnabled(store.getBoolValueForKey(WebPreferencesKey::cssIndividualTransformPropertiesEnabledKey()));
    settings.setCSSInputSecurityEnabled(store.getBoolValueForKey(WebPreferencesKey::cssInputSecurityEnabledKey()));
    settings.setMasonryEnabled(store.getBoolValueForKey(WebPreferencesKey::masonryEnabledKey()));
    settings.setCSSMotionPathEnabled(store.getBoolValueForKey(WebPreferencesKey::cssMotionPathEnabledKey()));
    settings.setCSSNestingEnabled(store.getBoolValueForKey(WebPreferencesKey::cssNestingEnabledKey()));
    settings.setOverscrollBehaviorEnabled(store.getBoolValueForKey(WebPreferencesKey::overscrollBehaviorEnabledKey()));
#if ENABLE(CSS_PAINTING_API)
    settings.setCSSPaintingAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::cssPaintingAPIEnabledKey()));
#endif
    settings.setCSSRelativeColorSyntaxEnabled(store.getBoolValueForKey(WebPreferencesKey::cssRelativeColorSyntaxEnabledKey()));
    settings.setCSSRhythmicSizingEnabled(store.getBoolValueForKey(WebPreferencesKey::cssRhythmicSizingEnabledKey()));
    settings.setCSSScrollAnchoringEnabled(store.getBoolValueForKey(WebPreferencesKey::cssScrollAnchoringEnabledKey()));
    settings.setSpringTimingFunctionEnabled(store.getBoolValueForKey(WebPreferencesKey::springTimingFunctionEnabledKey()));
    settings.setCSSTypedOMEnabled(store.getBoolValueForKey(WebPreferencesKey::cssTypedOMEnabledKey()));
    settings.setCSSTypedOMColorEnabled(store.getBoolValueForKey(WebPreferencesKey::cssTypedOMColorEnabledKey()));
    settings.setMasonryTrackAlignmentEnabled(store.getBoolValueForKey(WebPreferencesKey::masonryTrackAlignmentEnabledKey()));
    settings.setCSSColorContrastEnabled(store.getBoolValueForKey(WebPreferencesKey::cssColorContrastEnabledKey()));
    settings.setCSSColorMixEnabled(store.getBoolValueForKey(WebPreferencesKey::cssColorMixEnabledKey()));
    settings.setCSSMarginTrimEnabled(store.getBoolValueForKey(WebPreferencesKey::cssMarginTrimEnabledKey()));
    settings.setOverflowClipEnabled(store.getBoolValueForKey(WebPreferencesKey::overflowClipEnabledKey()));
    settings.setCSSScrollbarColorEnabled(store.getBoolValueForKey(WebPreferencesKey::cssScrollbarColorEnabledKey()));
    settings.setCSSScrollbarGutterEnabled(store.getBoolValueForKey(WebPreferencesKey::cssScrollbarGutterEnabledKey()));
    settings.setCSSScrollbarWidthEnabled(store.getBoolValueForKey(WebPreferencesKey::cssScrollbarWidthEnabledKey()));
    settings.setSubgridEnabled(store.getBoolValueForKey(WebPreferencesKey::subgridEnabledKey()));
    settings.setCSSTextAlignLastEnabled(store.getBoolValueForKey(WebPreferencesKey::cssTextAlignLastEnabledKey()));
    settings.setCSSTextBoxTrimEnabled(store.getBoolValueForKey(WebPreferencesKey::cssTextBoxTrimEnabledKey()));
    settings.setCSSTextGroupAlignEnabled(store.getBoolValueForKey(WebPreferencesKey::cssTextGroupAlignEnabledKey()));
    settings.setCSSTextJustifyEnabled(store.getBoolValueForKey(WebPreferencesKey::cssTextJustifyEnabledKey()));
    settings.setCSSTextSpacingEnabled(store.getBoolValueForKey(WebPreferencesKey::cssTextSpacingEnabledKey()));
    settings.setCSSTextUnderlinePositionLeftRightEnabled(store.getBoolValueForKey(WebPreferencesKey::cssTextUnderlinePositionLeftRightEnabledKey()));
    settings.setCSSWhiteSpaceLonghandsEnabled(store.getBoolValueForKey(WebPreferencesKey::cssWhiteSpaceLonghandsEnabledKey()));
    settings.setCSSTextWrapNewValuesEnabled(store.getBoolValueForKey(WebPreferencesKey::cssTextWrapNewValuesEnabledKey()));
#if ENABLE(CSS_TRANSFORM_STYLE_OPTIMIZED_3D)
    settings.setCSSTransformStyleOptimized3DEnabled(store.getBoolValueForKey(WebPreferencesKey::cssTransformStyleOptimized3DEnabledKey()));
#endif
    settings.setCSSOMViewScrollingAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::cssOMViewScrollingAPIEnabledKey()));
    settings.setCSSOMViewSmoothScrollingEnabled(store.getBoolValueForKey(WebPreferencesKey::cssOMViewSmoothScrollingEnabledKey()));
    settings.setCacheAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::cacheAPIEnabledKey()));
    settings.setCanvasColorSpaceEnabled(store.getBoolValueForKey(WebPreferencesKey::canvasColorSpaceEnabledKey()));
    settings.setCanvasFiltersEnabled(store.getBoolValueForKey(WebPreferencesKey::canvasFiltersEnabledKey()));
    settings.setCanvasUsesAcceleratedDrawing(store.getBoolValueForKey(WebPreferencesKey::canvasUsesAcceleratedDrawingKey()));
    settings.setClearSiteDataHTTPHeaderEnabled(store.getBoolValueForKey(WebPreferencesKey::clearSiteDataHTTPHeaderEnabledKey()));
#if ENABLE(BADGING)
    settings.setClientBadgeEnabled(store.getBoolValueForKey(WebPreferencesKey::clientBadgeEnabledKey()));
#endif
#if ENABLE(INPUT_TYPE_COLOR)
    settings.setInputTypeColorEnabled(store.getBoolValueForKey(WebPreferencesKey::inputTypeColorEnabledKey()));
#endif
    settings.setShowDebugBorders(store.getBoolValueForKey(WebPreferencesKey::compositingBordersVisibleKey()));
    settings.setShowRepaintCounter(store.getBoolValueForKey(WebPreferencesKey::compositingRepaintCountersVisibleKey()));
    settings.setCompressionStreamEnabled(store.getBoolValueForKey(WebPreferencesKey::compressionStreamEnabledKey()));
    settings.setConstructableStylesheetsEnabled(store.getBoolValueForKey(WebPreferencesKey::constructableStylesheetsEnabledKey()));
    settings.setContactPickerAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::contactPickerAPIEnabledKey()));
#if HAVE(AVCONTENTKEYSPECIFIER)
    settings.setSampleBufferContentKeySessionSupportEnabled(store.getBoolValueForKey(WebPreferencesKey::sampleBufferContentKeySessionSupportEnabledKey()));
#endif
    settings.setCookieConsentAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::cookieConsentAPIEnabledKey()));
    settings.setCookieStoreAPIExtendedAttributesEnabled(store.getBoolValueForKey(WebPreferencesKey::cookieStoreAPIExtendedAttributesEnabledKey()));
    settings.setCookieStoreAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::cookieStoreAPIEnabledKey()));
    settings.setCookieEnabled(store.getBoolValueForKey(WebPreferencesKey::cookieEnabledKey()));
    settings.setCrossOriginEmbedderPolicyEnabled(store.getBoolValueForKey(WebPreferencesKey::crossOriginEmbedderPolicyEnabledKey()));
    settings.setCrossOriginOpenerPolicyEnabled(store.getBoolValueForKey(WebPreferencesKey::crossOriginOpenerPolicyEnabledKey()));
    settings.setDOMPasteAccessRequestsEnabled(store.getBoolValueForKey(WebPreferencesKey::domPasteAccessRequestsEnabledKey()));
    settings.setDOMTimersThrottlingEnabled(store.getBoolValueForKey(WebPreferencesKey::domTimersThrottlingEnabledKey()));
    settings.setDeclarativeShadowDOMInDOMParserEnabled(store.getBoolValueForKey(WebPreferencesKey::declarativeShadowDOMInDOMParserEnabledKey()));
    settings.setDataTransferItemsEnabled(store.getBoolValueForKey(WebPreferencesKey::dataTransferItemsEnabledKey()));
#if ENABLE(DATALIST_ELEMENT)
    settings.setDataListElementEnabled(store.getBoolValueForKey(WebPreferencesKey::dataListElementEnabledKey()));
#endif
#if ENABLE(INPUT_TYPE_DATE)
    settings.setInputTypeDateEnabled(store.getBoolValueForKey(WebPreferencesKey::inputTypeDateEnabledKey()));
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    settings.setDateTimeInputsEditableComponentsEnabled(store.getBoolValueForKey(WebPreferencesKey::dateTimeInputsEditableComponentsEnabledKey()));
#endif
    settings.setDeclarativeShadowDOMEnabled(store.getBoolValueForKey(WebPreferencesKey::declarativeShadowDOMEnabledKey()));
    settings.setDefaultARIAForCustomElementsEnabled(store.getBoolValueForKey(WebPreferencesKey::defaultARIAForCustomElementsEnabledKey()));
    settings.setShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint(store.getBoolValueForKey(WebPreferencesKey::shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaintKey()));
    settings.setDeprecateRSAESPKCSWebCryptoEnabled(store.getBoolValueForKey(WebPreferencesKey::deprecateRSAESPKCSWebCryptoEnabledKey()));
    settings.setDeprecationReportingEnabled(store.getBoolValueForKey(WebPreferencesKey::deprecationReportingEnabledKey()));
    settings.setDiagnosticLoggingEnabled(store.getBoolValueForKey(WebPreferencesKey::diagnosticLoggingEnabledKey()));
    settings.setDirectoryUploadEnabled(store.getBoolValueForKey(WebPreferencesKey::directoryUploadEnabledKey()));
    settings.setIsThirdPartyCookieBlockingDisabled(store.getBoolValueForKey(WebPreferencesKey::isThirdPartyCookieBlockingDisabledKey()));
    settings.setIsFirstPartyWebsiteDataRemovalDisabled(store.getBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalDisabledKey()));
    settings.setDisallowSyncXHRDuringPageDismissalEnabled(store.getBoolValueForKey(WebPreferencesKey::disallowSyncXHRDuringPageDismissalEnabledKey()));
    settings.setDisplayListDrawingEnabled(store.getBoolValueForKey(WebPreferencesKey::displayListDrawingEnabledKey()));
    settings.setShouldDropNearSuspendedAssertionAfterDelay(store.getBoolValueForKey(WebPreferencesKey::shouldDropNearSuspendedAssertionAfterDelayKey()));
    settings.setEmbedElementEnabled(store.getBoolValueForKey(WebPreferencesKey::embedElementEnabledKey()));
    settings.setCanvasFingerprintingQuirkEnabled(store.getBoolValueForKey(WebPreferencesKey::canvasFingerprintingQuirkEnabledKey()));
    settings.setICECandidateFilteringEnabled(store.getBoolValueForKey(WebPreferencesKey::iceCandidateFilteringEnabledKey()));
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    settings.setLegacyEncryptedMediaAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::legacyEncryptedMediaAPIEnabledKey()));
#endif
#if ENABLE(MEDIA_STREAM)
    settings.setMockCaptureDevicesEnabled(store.getBoolValueForKey(WebPreferencesKey::mockCaptureDevicesEnabledKey()));
#endif
#if ENABLE(PDFJS)
    settings.setPdfJSViewerEnabled(store.getBoolValueForKey(WebPreferencesKey::pdfJSViewerEnabledKey()));
#endif
#if PLATFORM(MAC) && USE(RUNNINGBOARD)
    settings.setBackgroundWebContentRunningBoardThrottlingEnabled(store.getBoolValueForKey(WebPreferencesKey::backgroundWebContentRunningBoardThrottlingEnabledKey()));
#endif
#if ENABLE(SERVICE_WORKER)
    settings.setBackgroundFetchAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::backgroundFetchAPIEnabledKey()));
#endif
    settings.setEnterKeyHintEnabled(store.getBoolValueForKey(WebPreferencesKey::enterKeyHintEnabledKey()));
    settings.setEventHandlerDrivenSmoothKeyboardScrollingEnabled(store.getBoolValueForKey(WebPreferencesKey::eventHandlerDrivenSmoothKeyboardScrollingEnabledKey()));
#if ENABLE(MEDIA_SESSION_COORDINATOR)
    settings.setMediaSessionCoordinatorEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaSessionCoordinatorEnabledKey()));
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR) && ENABLE(MEDIA_SESSION_PLAYLIST)
    settings.setMediaSessionPlaylistEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaSessionPlaylistEnabledKey()));
#endif
    settings.setFTPEnabled(store.getBoolValueForKey(WebPreferencesKey::ftpEnabledKey()));
    settings.setFetchAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::fetchAPIEnabledKey()));
    settings.setFetchMetadataEnabled(store.getBoolValueForKey(WebPreferencesKey::fetchMetadataEnabledKey()));
    settings.setFetchPriorityEnabled(store.getBoolValueForKey(WebPreferencesKey::fetchPriorityEnabledKey()));
    settings.setFileSystemAccessEnabled(store.getBoolValueForKey(WebPreferencesKey::fileSystemAccessEnabledKey()));
    settings.setFileReaderAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::fileReaderAPIEnabledKey()));
    settings.setRequestSubmitEnabled(store.getBoolValueForKey(WebPreferencesKey::requestSubmitEnabledKey()));
    settings.setFormAssociatedCustomElementsEnabled(store.getBoolValueForKey(WebPreferencesKey::formAssociatedCustomElementsEnabledKey()));
    settings.setLayoutFormattingContextEnabled(store.getBoolValueForKey(WebPreferencesKey::layoutFormattingContextEnabledKey()));
#if ENABLE(FULLSCREEN_API)
    settings.setFullScreenEnabled(store.getBoolValueForKey(WebPreferencesKey::fullScreenEnabledKey()));
#endif
#if PLATFORM(VISION)
    settings.setFullscreenSceneAspectRatioLockingEnabled(store.getBoolValueForKey(WebPreferencesKey::fullscreenSceneAspectRatioLockingEnabledKey()));
#endif
#if PLATFORM(VISION)
    settings.setFullscreenSceneDimmingEnabled(store.getBoolValueForKey(WebPreferencesKey::fullscreenSceneDimmingEnabledKey()));
#endif
#if ENABLE(GPU_PROCESS)
    settings.setBlockMediaLayerRehostingInWebContentProcess(store.getBoolValueForKey(WebPreferencesKey::blockMediaLayerRehostingInWebContentProcessKey()));
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
    settings.setManageCaptureStatusBarInGPUProcessEnabled(store.getBoolValueForKey(WebPreferencesKey::manageCaptureStatusBarInGPUProcessEnabledKey()));
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
    settings.setUseGPUProcessForWebGLEnabled(store.getBoolValueForKey(WebPreferencesKey::useGPUProcessForWebGLEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    settings.setWebRTCPlatformCodecsInGPUProcessEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCPlatformCodecsInGPUProcessEnabledKey()));
#endif
#if ENABLE(GAMEPAD)
    settings.setGamepadTriggerRumbleEnabled(store.getBoolValueForKey(WebPreferencesKey::gamepadTriggerRumbleEnabledKey()));
#endif
#if ENABLE(GAMEPAD)
    settings.setGamepadVibrationActuatorEnabled(store.getBoolValueForKey(WebPreferencesKey::gamepadVibrationActuatorEnabledKey()));
#endif
#if ENABLE(GAMEPAD)
    settings.setGamepadsEnabled(store.getBoolValueForKey(WebPreferencesKey::gamepadsEnabledKey()));
#endif
#if ENABLE(VIDEO)
    settings.setGenericCueAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::genericCueAPIEnabledKey()));
#endif
#if USE(GRAPHICS_CONTEXT_FILTERS)
    settings.setGraphicsContextFiltersEnabled(store.getBoolValueForKey(WebPreferencesKey::graphicsContextFiltersEnabledKey()));
#endif
    settings.setAcceleratedDrawingEnabled(store.getBoolValueForKey(WebPreferencesKey::acceleratedDrawingEnabledKey()));
    settings.setDialogElementEnabled(store.getBoolValueForKey(WebPreferencesKey::dialogElementEnabledKey()));
#if ENABLE(MODEL_ELEMENT)
    settings.setModelElementEnabled(store.getBoolValueForKey(WebPreferencesKey::modelElementEnabledKey()));
#endif
    settings.setInteractiveFormValidationEnabled(store.getBoolValueForKey(WebPreferencesKey::interactiveFormValidationEnabledKey()));
    settings.setInertAttributeEnabled(store.getBoolValueForKey(WebPreferencesKey::inertAttributeEnabledKey()));
    settings.setPopoverAttributeEnabled(store.getBoolValueForKey(WebPreferencesKey::popoverAttributeEnabledKey()));
    settings.setHiddenPageDOMTimerThrottlingAutoIncreases(store.getBoolValueForKey(WebPreferencesKey::hiddenPageDOMTimerThrottlingAutoIncreasesKey()));
    settings.setHiddenPageDOMTimerThrottlingEnabled(store.getBoolValueForKey(WebPreferencesKey::hiddenPageDOMTimerThrottlingEnabledKey()));
    settings.setHyperlinkAuditingEnabled(store.getBoolValueForKey(WebPreferencesKey::hyperlinkAuditingEnabledKey()));
    settings.setItpDebugModeEnabled(store.getBoolValueForKey(WebPreferencesKey::itpDebugModeEnabledKey()));
#if ENABLE(TEXT_AUTOSIZING)
    settings.setTextAutosizingUsesIdempotentMode(store.getBoolValueForKey(WebPreferencesKey::textAutosizingUsesIdempotentModeKey()));
#endif
#if ENABLE(IMAGE_ANALYSIS)
    settings.setImageAnalysisDuringFindInPageEnabled(store.getBoolValueForKey(WebPreferencesKey::imageAnalysisDuringFindInPageEnabledKey()));
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    settings.setImageAnimationControlEnabled(store.getBoolValueForKey(WebPreferencesKey::imageAnimationControlEnabledKey()));
#endif
#if ENABLE(SERVICE_CONTROLS)
    settings.setImageControlsEnabled(store.getBoolValueForKey(WebPreferencesKey::imageControlsEnabledKey()));
#endif
    settings.setImperativeSlotAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::imperativeSlotAPIEnabledKey()));
    settings.setIndexedDBAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::indexedDBAPIEnabledKey()));
    settings.setInlinePredictionsInAllEditableElementsEnabled(store.getBoolValueForKey(WebPreferencesKey::inlinePredictionsInAllEditableElementsEnabledKey()));
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
    settings.setInteractionRegionsEnabled(store.getBoolValueForKey(WebPreferencesKey::interactionRegionsEnabledKey()));
#endif
    settings.setIntersectionObserverEnabled(store.getBoolValueForKey(WebPreferencesKey::intersectionObserverEnabledKey()));
    settings.setIsLoggedInAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::isLoggedInAPIEnabledKey()));
    settings.setScriptEnabled(store.getBoolValueForKey(WebPreferencesKey::javaScriptEnabledKey()));
#if ENABLE(LAYER_BASED_SVG_ENGINE)
    settings.setLayerBasedSVGEngineEnabled(store.getBoolValueForKey(WebPreferencesKey::layerBasedSVGEngineEnabledKey()));
#endif
    settings.setLazyIframeLoadingEnabled(store.getBoolValueForKey(WebPreferencesKey::lazyIframeLoadingEnabledKey()));
    settings.setLazyImageLoadingEnabled(store.getBoolValueForKey(WebPreferencesKey::lazyImageLoadingEnabledKey()));
#if ENABLE(OVERFLOW_SCROLLING_TOUCH)
    settings.setLegacyOverflowScrollingTouchEnabled(store.getBoolValueForKey(WebPreferencesKey::legacyOverflowScrollingTouchEnabledKey()));
#endif
    settings.setLegacyLineLayoutVisualCoverageEnabled(store.getBoolValueForKey(WebPreferencesKey::legacyLineLayoutVisualCoverageEnabledKey()));
    settings.setShowModalDialogEnabled(store.getBoolValueForKey(WebPreferencesKey::showModalDialogEnabledKey()));
#if ENABLE(MEDIA_STREAM)
    settings.setMediaCaptureRequiresSecureConnection(store.getBoolValueForKey(WebPreferencesKey::mediaCaptureRequiresSecureConnectionKey()));
#endif
    settings.setLinkSanitizerEnabled(store.getBoolValueForKey(WebPreferencesKey::linkSanitizerEnabledKey()));
    settings.setLinkPreloadResponsiveImagesEnabled(store.getBoolValueForKey(WebPreferencesKey::linkPreloadResponsiveImagesEnabledKey()));
    settings.setLinkModulePreloadEnabled(store.getBoolValueForKey(WebPreferencesKey::linkModulePreloadEnabledKey()));
    settings.setLinkPreconnectEarlyHintsEnabled(store.getBoolValueForKey(WebPreferencesKey::linkPreconnectEarlyHintsEnabledKey()));
    settings.setLinkPrefetchEnabled(store.getBoolValueForKey(WebPreferencesKey::linkPrefetchEnabledKey()));
    settings.setLiveRangeSelectionEnabled(store.getBoolValueForKey(WebPreferencesKey::liveRangeSelectionEnabledKey()));
    settings.setLocalFileContentSniffingEnabled(store.getBoolValueForKey(WebPreferencesKey::localFileContentSniffingEnabledKey()));
    settings.setLocalStorageEnabled(store.getBoolValueForKey(WebPreferencesKey::localStorageEnabledKey()));
    settings.setLogsPageMessagesToSystemConsoleEnabled(store.getBoolValueForKey(WebPreferencesKey::logsPageMessagesToSystemConsoleEnabledKey()));
    settings.setMainContentUserGestureOverrideEnabled(store.getBoolValueForKey(WebPreferencesKey::mainContentUserGestureOverrideEnabledKey()));
#if ENABLE(MANAGED_MEDIA_SOURCE)
    settings.setManagedMediaSourceEnabled(store.getBoolValueForKey(WebPreferencesKey::managedMediaSourceEnabledKey()));
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE) && ENABLE(WIRELESS_PLAYBACK_TARGET)
    settings.setManagedMediaSourceNeedsAirPlay(store.getBoolValueForKey(WebPreferencesKey::managedMediaSourceNeedsAirPlayKey()));
#endif
#if ENABLE(WEBGL)
    settings.setMaskWebGLStringsEnabled(store.getBoolValueForKey(WebPreferencesKey::maskWebGLStringsEnabledKey()));
#endif
    settings.setCoreMathMLEnabled(store.getBoolValueForKey(WebPreferencesKey::coreMathMLEnabledKey()));
    settings.setMediaCapabilitiesExtensionsEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaCapabilitiesExtensionsEnabledKey()));
#if ENABLE(MEDIA_SESSION)
    settings.setMediaSessionEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaSessionEnabledKey()));
#endif
    settings.setMediaSourceEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaSourceEnabledKey()));
#if ENABLE(MEDIA_STREAM)
    settings.setMediaDevicesEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaDevicesEnabledKey()));
#endif
#if ENABLE(MEDIA_RECORDER)
    settings.setMediaRecorderEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaRecorderEnabledKey()));
#endif
    settings.setMomentumScrollingAnimatorEnabled(store.getBoolValueForKey(WebPreferencesKey::momentumScrollingAnimatorEnabledKey()));
#if ENABLE(INPUT_TYPE_MONTH)
    settings.setInputTypeMonthEnabled(store.getBoolValueForKey(WebPreferencesKey::inputTypeMonthEnabledKey()));
#endif
#if ENABLE(TOUCH_EVENTS)
    settings.setMouseEventsSimulationEnabled(store.getBoolValueForKey(WebPreferencesKey::mouseEventsSimulationEnabledKey()));
#endif
#if ENABLE(MEDIA_STREAM)
    settings.setMuteCameraOnMicrophoneInterruptionEnabled(store.getBoolValueForKey(WebPreferencesKey::muteCameraOnMicrophoneInterruptionEnabledKey()));
#endif
    settings.setNeedsSiteSpecificQuirks(store.getBoolValueForKey(WebPreferencesKey::needsSiteSpecificQuirksKey()));
    settings.setNeedsStorageAccessFromFileURLsQuirk(store.getBoolValueForKey(WebPreferencesKey::needsStorageAccessFromFileURLsQuirkKey()));
    settings.setFlexFormattingContextIntegrationEnabled(store.getBoolValueForKey(WebPreferencesKey::flexFormattingContextIntegrationEnabledKey()));
#if ENABLE(NOTIFICATION_EVENT)
    settings.setNotificationEventEnabled(store.getBoolValueForKey(WebPreferencesKey::notificationEventEnabledKey()));
#endif
#if ENABLE(NOTIFICATIONS)
    settings.setNotificationsEnabled(store.getBoolValueForKey(WebPreferencesKey::notificationsEnabledKey()));
#endif
#if ENABLE(OFFSCREEN_CANVAS_IN_WORKERS)
    settings.setOffscreenCanvasInWorkersEnabled(store.getBoolValueForKey(WebPreferencesKey::offscreenCanvasInWorkersEnabledKey()));
#endif
#if ENABLE(OFFSCREEN_CANVAS)
    settings.setOffscreenCanvasEnabled(store.getBoolValueForKey(WebPreferencesKey::offscreenCanvasEnabledKey()));
#endif
    settings.setPerformanceNavigationTimingAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::performanceNavigationTimingAPIEnabledKey()));
    settings.setPerformanceResourceTimingSensitivePropertiesEnabled(store.getBoolValueForKey(WebPreferencesKey::performanceResourceTimingSensitivePropertiesEnabledKey()));
    settings.setPermissionsAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::permissionsAPIEnabledKey()));
    settings.setPreferPageRenderingUpdatesNear60FPSEnabled(store.getBoolValueForKey(WebPreferencesKey::preferPageRenderingUpdatesNear60FPSEnabledKey()));
#if ENABLE(VIDEO)
    settings.setPreferSandboxedMediaParsing(store.getBoolValueForKey(WebPreferencesKey::preferSandboxedMediaParsingKey()));
#endif
    settings.setPrivateClickMeasurementDebugModeEnabled(store.getBoolValueForKey(WebPreferencesKey::privateClickMeasurementDebugModeEnabledKey()));
    settings.setPrivateClickMeasurementFraudPreventionEnabled(store.getBoolValueForKey(WebPreferencesKey::privateClickMeasurementFraudPreventionEnabledKey()));
    settings.setPrivateClickMeasurementEnabled(store.getBoolValueForKey(WebPreferencesKey::privateClickMeasurementEnabledKey()));
#if ENABLE(SERVICE_WORKER)
    settings.setPushAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::pushAPIEnabledKey()));
#endif
    settings.setGoogleAntiFlickerOptimizationQuirkEnabled(store.getBoolValueForKey(WebPreferencesKey::googleAntiFlickerOptimizationQuirkEnabledKey()));
    settings.setReferrerPolicyAttributeEnabled(store.getBoolValueForKey(WebPreferencesKey::referrerPolicyAttributeEnabledKey()));
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    settings.setRemotePlaybackEnabled(store.getBoolValueForKey(WebPreferencesKey::remotePlaybackEnabledKey()));
#endif
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    settings.setRemoveBackgroundEnabled(store.getBoolValueForKey(WebPreferencesKey::removeBackgroundEnabledKey()));
#endif
    settings.setReportingEnabled(store.getBoolValueForKey(WebPreferencesKey::reportingEnabledKey()));
    settings.setRequestVideoFrameCallbackEnabled(store.getBoolValueForKey(WebPreferencesKey::requestVideoFrameCallbackEnabledKey()));
#if HAVE(SC_CONTENT_SHARING_PICKER)
    settings.setRequireUAGetDisplayMediaPrompt(store.getBoolValueForKey(WebPreferencesKey::requireUAGetDisplayMediaPromptKey()));
#endif
#if ENABLE(MEDIA_STREAM)
    settings.setSpeakerSelectionRequiresUserGesture(store.getBoolValueForKey(WebPreferencesKey::speakerSelectionRequiresUserGestureKey()));
#endif
    settings.setFullscreenRequirementForScreenOrientationLockingEnabled(store.getBoolValueForKey(WebPreferencesKey::fullscreenRequirementForScreenOrientationLockingEnabledKey()));
#if ENABLE(MEDIA_STREAM)
    settings.setGetUserMediaRequiresFocus(store.getBoolValueForKey(WebPreferencesKey::getUserMediaRequiresFocusKey()));
#endif
    settings.setResizeObserverEnabled(store.getBoolValueForKey(WebPreferencesKey::resizeObserverEnabledKey()));
    settings.setResourceLoadSchedulingEnabled(store.getBoolValueForKey(WebPreferencesKey::resourceLoadSchedulingEnabledKey()));
#if ENABLE(RESOURCE_USAGE)
    settings.setResourceUsageOverlayVisible(store.getBoolValueForKey(WebPreferencesKey::resourceUsageOverlayVisibleKey()));
#endif
    settings.setSKAttributionEnabled(store.getBoolValueForKey(WebPreferencesKey::sKAttributionEnabledKey()));
    settings.setIsSameSiteStrictEnforcementEnabled(store.getBoolValueForKey(WebPreferencesKey::isSameSiteStrictEnforcementEnabledKey()));
    settings.setScreenOrientationLockingAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::screenOrientationLockingAPIEnabledKey()));
    settings.setScreenOrientationAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::screenOrientationAPIEnabledKey()));
    settings.setScreenWakeLockAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::screenWakeLockAPIEnabledKey()));
#if ENABLE(MEDIA_STREAM)
    settings.setScreenCaptureEnabled(store.getBoolValueForKey(WebPreferencesKey::screenCaptureEnabledKey()));
#endif
    settings.setScrollingPerformanceTestingEnabled(store.getBoolValueForKey(WebPreferencesKey::scrollingPerformanceTestingEnabledKey()));
    settings.setScrollToTextFragmentIndicatorEnabled(store.getBoolValueForKey(WebPreferencesKey::scrollToTextFragmentIndicatorEnabledKey()));
    settings.setScrollToTextFragmentEnabled(store.getBoolValueForKey(WebPreferencesKey::scrollToTextFragmentEnabledKey()));
    settings.setScrollAnimatorEnabled(store.getBoolValueForKey(WebPreferencesKey::scrollAnimatorEnabledKey()));
    settings.setSearchInputIncrementalAttributeAndSearchEventEnabled(store.getBoolValueForKey(WebPreferencesKey::searchInputIncrementalAttributeAndSearchEventEnabledKey()));
    settings.setSecureContextChecksEnabled(store.getBoolValueForKey(WebPreferencesKey::secureContextChecksEnabledKey()));
    settings.setSelectionAPIForShadowDOMEnabled(store.getBoolValueForKey(WebPreferencesKey::selectionAPIForShadowDOMEnabledKey()));
    settings.setSendMouseEventsToDisabledFormControlsEnabled(store.getBoolValueForKey(WebPreferencesKey::sendMouseEventsToDisabledFormControlsEnabledKey()));
#if ENABLE(SERVICE_WORKER)
    settings.setServiceWorkerNavigationPreloadEnabled(store.getBoolValueForKey(WebPreferencesKey::serviceWorkerNavigationPreloadEnabledKey()));
#endif
#if ENABLE(SERVICE_WORKER)
    settings.setServiceWorkersEnabled(store.getBoolValueForKey(WebPreferencesKey::serviceWorkersEnabledKey()));
#endif
    settings.setShapeDetection(store.getBoolValueForKey(WebPreferencesKey::shapeDetectionKey()));
    settings.setSharedWorkerEnabled(store.getBoolValueForKey(WebPreferencesKey::sharedWorkerEnabledKey()));
    settings.setShowMediaStatsContextMenuItemEnabled(store.getBoolValueForKey(WebPreferencesKey::showMediaStatsContextMenuItemEnabledKey()));
    settings.setSiteIsolationEnabled(store.getBoolValueForKey(WebPreferencesKey::siteIsolationEnabledKey()));
    settings.setSpeechRecognitionEnabled(store.getBoolValueForKey(WebPreferencesKey::speechRecognitionEnabledKey()));
    settings.setSpeechSynthesisAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::speechSynthesisAPIEnabledKey()));
    settings.setStorageAPIEstimateEnabled(store.getBoolValueForKey(WebPreferencesKey::storageAPIEstimateEnabledKey()));
    settings.setStorageAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::storageAPIEnabledKey()));
    settings.setStorageAccessAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::storageAccessAPIEnabledKey()));
    settings.setStorageBlockingPolicy(static_cast<WebCore::StorageBlockingPolicy>(store.getUInt32ValueForKey(WebPreferencesKey::storageBlockingPolicyKey())));
    settings.setSyntheticEditingCommandsEnabled(store.getBoolValueForKey(WebPreferencesKey::syntheticEditingCommandsEnabledKey()));
    settings.setShouldTakeNearSuspendedAssertions(store.getBoolValueForKey(WebPreferencesKey::shouldTakeNearSuspendedAssertionsKey()));
#if ENABLE(IMAGE_ANALYSIS)
    settings.setTextRecognitionInVideosEnabled(store.getBoolValueForKey(WebPreferencesKey::textRecognitionInVideosEnabledKey()));
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
    settings.setThreadedAnimationResolutionEnabled(store.getBoolValueForKey(WebPreferencesKey::threadedAnimationResolutionEnabledKey()));
#endif
    settings.setShowTiledScrollingIndicator(store.getBoolValueForKey(WebPreferencesKey::tiledScrollingIndicatorVisibleKey()));
#if ENABLE(INPUT_TYPE_TIME)
    settings.setInputTypeTimeEnabled(store.getBoolValueForKey(WebPreferencesKey::inputTypeTimeEnabledKey()));
#endif
    settings.setTrackConfigurationEnabled(store.getBoolValueForKey(WebPreferencesKey::trackConfigurationEnabledKey()));
    settings.setTransformStreamAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::transformStreamAPIEnabledKey()));
    settings.setUndoManagerAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::undoManagerAPIEnabledKey()));
    settings.setUnprefixedFullscreenAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::unprefixedFullscreenAPIEnabledKey()));
#if HAVE(SC_CONTENT_SHARING_PICKER)
    settings.setUseSCContentSharingPicker(store.getBoolValueForKey(WebPreferencesKey::useSCContentSharingPickerKey()));
#endif
    settings.setUseGiantTiles(store.getBoolValueForKey(WebPreferencesKey::useGiantTilesKey()));
    settings.setUserActivationAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::userActivationAPIEnabledKey()));
    settings.setUserGesturePromisePropagationEnabled(store.getBoolValueForKey(WebPreferencesKey::userGesturePromisePropagationEnabledKey()));
#if ENABLE(SERVICE_WORKER)
    settings.setServiceWorkersUserGestureEnabled(store.getBoolValueForKey(WebPreferencesKey::serviceWorkersUserGestureEnabledKey()));
#endif
    settings.setVerifyWindowOpenUserGestureFromUIProcess(store.getBoolValueForKey(WebPreferencesKey::verifyWindowOpenUserGestureFromUIProcessKey()));
    settings.setVerticalFormControlsEnabled(store.getBoolValueForKey(WebPreferencesKey::verticalFormControlsEnabledKey()));
#if ENABLE(IMAGE_ANALYSIS)
    settings.setVisualTranslationEnabled(store.getBoolValueForKey(WebPreferencesKey::visualTranslationEnabledKey()));
#endif
    settings.setVisualViewportAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::visualViewportAPIEnabledKey()));
    settings.setWebAPIStatisticsEnabled(store.getBoolValueForKey(WebPreferencesKey::webAPIStatisticsEnabledKey()));
    settings.setWebAPIsInShadowRealmEnabled(store.getBoolValueForKey(WebPreferencesKey::webAPIsInShadowRealmEnabledKey()));
    settings.setWebAnimationsCompositeOperationsEnabled(store.getBoolValueForKey(WebPreferencesKey::webAnimationsCompositeOperationsEnabledKey()));
    settings.setWebAnimationsCustomEffectsEnabled(store.getBoolValueForKey(WebPreferencesKey::webAnimationsCustomEffectsEnabledKey()));
    settings.setWebAnimationsCustomFrameRateEnabled(store.getBoolValueForKey(WebPreferencesKey::webAnimationsCustomFrameRateEnabledKey()));
    settings.setWebAnimationsIterationCompositeEnabled(store.getBoolValueForKey(WebPreferencesKey::webAnimationsIterationCompositeEnabledKey()));
    settings.setWebAnimationsMutableTimelinesEnabled(store.getBoolValueForKey(WebPreferencesKey::webAnimationsMutableTimelinesEnabledKey()));
#if ENABLE(WEB_ARCHIVE)
    settings.setWebArchiveDebugModeEnabled(store.getBoolValueForKey(WebPreferencesKey::webArchiveDebugModeEnabledKey()));
#endif
#if ENABLE(WEB_ARCHIVE)
    settings.setWebArchiveTestingModeEnabled(store.getBoolValueForKey(WebPreferencesKey::webArchiveTestingModeEnabledKey()));
#endif
#if ENABLE(WEB_AUTHN)
    settings.setWebAuthenticationEnabled(store.getBoolValueForKey(WebPreferencesKey::webAuthenticationEnabledKey()));
#endif
    settings.setWebCryptoSafeCurvesEnabled(store.getBoolValueForKey(WebPreferencesKey::webCryptoSafeCurvesEnabledKey()));
    settings.setWebLocksAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::webLocksAPIEnabledKey()));
    settings.setWebShareFileAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::webShareFileAPIEnabledKey()));
    settings.setWebShareEnabled(store.getBoolValueForKey(WebPreferencesKey::webShareEnabledKey()));
#if ENABLE(WEBASSEMBLY)
    settings.setWebAssemblyESMIntegrationEnabled(store.getBoolValueForKey(WebPreferencesKey::webAssemblyESMIntegrationEnabledKey()));
#endif
#if ENABLE(WEB_CODECS)
    settings.setWebCodecsEnabled(store.getBoolValueForKey(WebPreferencesKey::webCodecsEnabledKey()));
#endif
#if ENABLE(WEB_CODECS)
    settings.setWebCodecsAV1Enabled(store.getBoolValueForKey(WebPreferencesKey::webCodecsAV1EnabledKey()));
#endif
#if ENABLE(WEB_CODECS)
    settings.setWebCodecsHEVCEnabled(store.getBoolValueForKey(WebPreferencesKey::webCodecsHEVCEnabledKey()));
#endif
    settings.setWebGLDraftExtensionsEnabled(store.getBoolValueForKey(WebPreferencesKey::webGLDraftExtensionsEnabledKey()));
    settings.setWebGLTimerQueriesEnabled(store.getBoolValueForKey(WebPreferencesKey::webGLTimerQueriesEnabledKey()));
#if ENABLE(WEBGL) && PLATFORM(COCOA)
    settings.setWebGLUsingMetal(store.getBoolValueForKey(WebPreferencesKey::webGLUsingMetalKey()));
#endif
    settings.setWebGLEnabled(store.getBoolValueForKey(WebPreferencesKey::webGLEnabledKey()));
    settings.setWebGPUEnabled(store.getBoolValueForKey(WebPreferencesKey::webGPUEnabledKey()));
    settings.setWebInspectorEngineeringSettingsAllowed(store.getBoolValueForKey(WebPreferencesKey::webInspectorEngineeringSettingsAllowedKey()));
#if ENABLE(WEB_RTC)
    settings.setWebRTCAV1CodecEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCAV1CodecEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    settings.setWebRTCDTMFEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCDTMFEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    settings.setWebRTCEncodedTransformEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCEncodedTransformEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    settings.setWebRTCH265CodecEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCH265CodecEnabledKey()));
#endif
#if USE(LIBWEBRTC)
    settings.setWebRTCMediaPipelineAdditionalLoggingEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCMediaPipelineAdditionalLoggingEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    settings.setPeerConnectionEnabled(store.getBoolValueForKey(WebPreferencesKey::peerConnectionEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    settings.setWebRTCRemoteVideoFrameEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCRemoteVideoFrameEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    settings.setWebRTCSFrameTransformEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCSFrameTransformEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    settings.setWebRTCSocketsProxyingEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCSocketsProxyingEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    settings.setWebRTCVP9Profile0CodecEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCVP9Profile0CodecEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    settings.setWebRTCVP9Profile2CodecEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCVP9Profile2CodecEnabledKey()));
#endif
#if ENABLE(WEBXR)
    settings.setWebXRAugmentedRealityModuleEnabled(store.getBoolValueForKey(WebPreferencesKey::webXRAugmentedRealityModuleEnabledKey()));
#endif
#if ENABLE(WEBXR)
    settings.setWebXREnabled(store.getBoolValueForKey(WebPreferencesKey::webXREnabledKey()));
#endif
#if ENABLE(WEBXR)
    settings.setWebXRGamepadsModuleEnabled(store.getBoolValueForKey(WebPreferencesKey::webXRGamepadsModuleEnabledKey()));
#endif
#if ENABLE(WEBXR_HANDS)
    settings.setWebXRHandInputModuleEnabled(store.getBoolValueForKey(WebPreferencesKey::webXRHandInputModuleEnabledKey()));
#endif
#if ENABLE(INPUT_TYPE_WEEK)
    settings.setInputTypeWeekEnabled(store.getBoolValueForKey(WebPreferencesKey::inputTypeWeekEnabledKey()));
#endif
    settings.setWheelEventGesturesBecomeNonBlocking(store.getBoolValueForKey(WebPreferencesKey::wheelEventGesturesBecomeNonBlockingKey()));
    settings.setPassiveWheelListenersAsDefaultOnDocument(store.getBoolValueForKey(WebPreferencesKey::passiveWheelListenersAsDefaultOnDocumentKey()));
    settings.setIsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled(store.getBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalLiveOnTestingEnabledKey()));
    settings.setIsFirstPartyWebsiteDataRemovalReproTestingEnabled(store.getBoolValueForKey(WebPreferencesKey::isFirstPartyWebsiteDataRemovalReproTestingEnabledKey()));
#if ENABLE(INPUT_TYPE_DATETIMELOCAL)
    settings.setInputTypeDateTimeLocalEnabled(store.getBoolValueForKey(WebPreferencesKey::inputTypeDateTimeLocalEnabledKey()));
#endif
    settings.setHttpEquivEnabled(store.getBoolValueForKey(WebPreferencesKey::httpEquivEnabledKey()));
#if ENABLE(IOS_FORM_CONTROL_REFRESH)
    settings.setIOSFormControlRefreshEnabled(store.getBoolValueForKey(WebPreferencesKey::iOSFormControlRefreshEnabledKey()));
#endif
    settings.setRequestIdleCallbackEnabled(store.getBoolValueForKey(WebPreferencesKey::requestIdleCallbackEnabledKey()));
    settings.setCSSWordBreakAutoEnabled(store.getBoolValueForKey(WebPreferencesKey::cssWordBreakAutoEnabledKey()));
}

void WebPage::updatePreferencesGenerated(const WebPreferencesStore& store)
{
#if USE(GSTREAMER)
    WebCore::DeprecatedGlobalSettings::setGStreamerEnabled(store.getBoolValueForKey(WebPreferencesKey::isGStreamerEnabledKey()));
#endif
    WebCore::DeprecatedGlobalSettings::setLowPowerVideoAudioBufferSizeEnabled(store.getBoolValueForKey(WebPreferencesKey::lowPowerVideoAudioBufferSizeEnabledKey()));
    WebCore::DeprecatedGlobalSettings::setMockScrollbarsEnabled(store.getBoolValueForKey(WebPreferencesKey::mockScrollbarsEnabledKey()));
#if ENABLE(WEBM_FORMAT_READER)
    WebCore::DeprecatedGlobalSettings::setWebMFormatReaderEnabled(store.getBoolValueForKey(WebPreferencesKey::webMFormatReaderEnabledKey()));
#endif
#if ENABLE(MEDIA_SOURCE)
    WebCore::DeprecatedGlobalSettings::setWebMParserEnabled(store.getBoolValueForKey(WebPreferencesKey::webMParserEnabledKey()));
#endif
#if USE(AVFOUNDATION)
    WebCore::DeprecatedGlobalSettings::setAVFoundationEnabled(store.getBoolValueForKey(WebPreferencesKey::isAVFoundationEnabledKey()));
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
    WebCore::DeprecatedGlobalSettings::setAttachmentElementEnabled(store.getBoolValueForKey(WebPreferencesKey::attachmentElementEnabledKey()));
#endif
#if ENABLE(BUILT_IN_NOTIFICATIONS)
    WebCore::DeprecatedGlobalSettings::setBuiltInNotificationsEnabled(store.getBoolValueForKey(WebPreferencesKey::builtInNotificationsEnabledKey()));
#endif
    WebCore::DeprecatedGlobalSettings::setCustomPasteboardDataEnabled(store.getBoolValueForKey(WebPreferencesKey::customPasteboardDataEnabledKey()));
#if PLATFORM(IOS_FAMILY)
    WebCore::DeprecatedGlobalSettings::setDisableScreenSizeOverride(store.getBoolValueForKey(WebPreferencesKey::disableScreenSizeOverrideKey()));
#endif
#if ENABLE(MEDIA_SOURCE) && (HAVE(AVSAMPLEBUFFERVIDEOOUTPUT) || USE(GSTREAMER))
    WebCore::DeprecatedGlobalSettings::setMediaSourceInlinePaintingEnabled(store.getBoolValueForKey(WebPreferencesKey::mediaSourceInlinePaintingEnabledKey()));
#endif
    WebCore::DeprecatedGlobalSettings::setFetchAPIKeepAliveEnabled(store.getBoolValueForKey(WebPreferencesKey::fetchAPIKeepAliveEnabledKey()));
    WebCore::DeprecatedGlobalSettings::setRestrictedHTTPResponseAccess(store.getBoolValueForKey(WebPreferencesKey::restrictedHTTPResponseAccessKey()));
#if ENABLE(MODEL_ELEMENT)
    WebCore::DeprecatedGlobalSettings::setModelDocumentEnabled(store.getBoolValueForKey(WebPreferencesKey::modelDocumentEnabledKey()));
#endif
    WebCore::DeprecatedGlobalSettings::setHighlightAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::highlightAPIEnabledKey()));
#if ENABLE(ACCESSIBILITY_ISOLATED_TREE)
    WebCore::DeprecatedGlobalSettings::setIsAccessibilityIsolatedTreeEnabled(store.getBoolValueForKey(WebPreferencesKey::isAccessibilityIsolatedTreeEnabledKey()));
#endif
    WebCore::DeprecatedGlobalSettings::setInlineFormattingContextIntegrationEnabled(store.getBoolValueForKey(WebPreferencesKey::inlineFormattingContextIntegrationEnabledKey()));
#if ENABLE(OPUS)
    WebCore::DeprecatedGlobalSettings::setOpusDecoderEnabled(store.getBoolValueForKey(WebPreferencesKey::opusDecoderEnabledKey()));
#endif
    WebCore::DeprecatedGlobalSettings::setPaintTimingEnabled(store.getBoolValueForKey(WebPreferencesKey::paintTimingEnabledKey()));
    WebCore::DeprecatedGlobalSettings::setReadableByteStreamAPIEnabled(store.getBoolValueForKey(WebPreferencesKey::readableByteStreamAPIEnabledKey()));
    WebCore::DeprecatedGlobalSettings::setServerTimingEnabled(store.getBoolValueForKey(WebPreferencesKey::serverTimingEnabledKey()));
#if ENABLE(VORBIS)
    WebCore::DeprecatedGlobalSettings::setVorbisDecoderEnabled(store.getBoolValueForKey(WebPreferencesKey::vorbisDecoderEnabledKey()));
#endif
    WebCore::DeprecatedGlobalSettings::setWebRTCAudioLatencyAdaptationEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCAudioLatencyAdaptationEnabledKey()));
#if ENABLE(WEB_RTC)
    WebCore::DeprecatedGlobalSettings::setWebRTCH264LowLatencyEncoderEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCH264LowLatencyEncoderEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    WebCore::DeprecatedGlobalSettings::setWebRTCH264SimulcastEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCH264SimulcastEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    WebCore::DeprecatedGlobalSettings::setWebRTCPlatformTCPSocketsEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCPlatformTCPSocketsEnabledKey()));
#endif
#if ENABLE(WEB_RTC)
    WebCore::DeprecatedGlobalSettings::setWebRTCPlatformUDPSocketsEnabled(store.getBoolValueForKey(WebPreferencesKey::webRTCPlatformUDPSocketsEnabledKey()));
#endif
    WebCore::DeprecatedGlobalSettings::setLineHeightUnitsEnabled(store.getBoolValueForKey(WebPreferencesKey::lineHeightUnitsEnabledKey()));
}

}
