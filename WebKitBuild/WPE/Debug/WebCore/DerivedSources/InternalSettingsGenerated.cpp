/*
 * THIS FILE WAS AUTOMATICALLY GENERATED, DO NOT EDIT.
 *
 * Copyright (C) 2017-2020 Apple Inc. All rights reserved.
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
#include "InternalSettingsGenerated.h"

#include "Page.h"
#include "Settings.h"

namespace WebCore {

InternalSettingsGenerated::InternalSettingsGenerated(Page* page)
    : m_page(page)
    , m_CSSOMViewScrollingAPIEnabled(page->settings().CSSOMViewScrollingAPIEnabled())
    , m_CSSOMViewSmoothScrollingEnabled(page->settings().CSSOMViewSmoothScrollingEnabled())
    , m_abortSignalAnyOperationEnabled(page->settings().abortSignalAnyOperationEnabled())
    , m_acceleratedCompositedAnimationsEnabled(page->settings().acceleratedCompositedAnimationsEnabled())
    , m_acceleratedCompositingEnabled(page->settings().acceleratedCompositingEnabled())
    , m_acceleratedCompositingForFixedPositionEnabled(page->settings().acceleratedCompositingForFixedPositionEnabled())
    , m_acceleratedDrawingEnabled(page->settings().acceleratedDrawingEnabled())
#if USE(CORE_IMAGE)
    , m_acceleratedFiltersEnabled(page->settings().acceleratedFiltersEnabled())
#endif
    , m_accentColorEnabled(page->settings().accentColorEnabled())
    , m_accessHandleEnabled(page->settings().accessHandleEnabled())
    , m_aggressiveTileRetentionEnabled(page->settings().aggressiveTileRetentionEnabled())
    , m_allowAnimationControlsOverride(page->settings().allowAnimationControlsOverride())
    , m_allowContentSecurityPolicySourceStarToMatchAnyProtocol(page->settings().allowContentSecurityPolicySourceStarToMatchAnyProtocol())
    , m_allowCrossOriginSubresourcesToAskForCredentials(page->settings().allowCrossOriginSubresourcesToAskForCredentials())
    , m_allowDisplayOfInsecureContent(page->settings().allowDisplayOfInsecureContent())
    , m_allowFileAccessFromFileURLs(page->settings().allowFileAccessFromFileURLs())
    , m_allowMediaContentTypesRequiringHardwareSupportAsFallback(page->settings().allowMediaContentTypesRequiringHardwareSupportAsFallback())
    , m_allowMultiElementImplicitSubmission(page->settings().allowMultiElementImplicitSubmission())
    , m_allowRunningOfInsecureContent(page->settings().allowRunningOfInsecureContent())
    , m_allowSettingAnyXHRHeaderFromFileURLs(page->settings().allowSettingAnyXHRHeaderFromFileURLs())
    , m_allowTopNavigationToDataURLs(page->settings().allowTopNavigationToDataURLs())
    , m_allowUniversalAccessFromFileURLs(page->settings().allowUniversalAccessFromFileURLs())
#if PLATFORM(IOS_FAMILY)
    , m_allowViewportShrinkToFitContent(page->settings().allowViewportShrinkToFitContent())
#endif
#if ENABLE(WEBGL)
    , m_allowWebGLInWorkers(page->settings().allowWebGLInWorkers())
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    , m_allowsAirPlayForMediaPlayback(page->settings().allowsAirPlayForMediaPlayback())
#endif
    , m_allowsInlineMediaPlayback(page->settings().allowsInlineMediaPlayback())
    , m_allowsInlineMediaPlaybackAfterFullscreen(page->settings().allowsInlineMediaPlaybackAfterFullscreen())
    , m_allowsPictureInPictureMediaPlayback(page->settings().allowsPictureInPictureMediaPlayback())
#if PLATFORM(IOS_FAMILY)
    , m_alternateFormControlDesignEnabled(page->settings().alternateFormControlDesignEnabled())
#endif
#if PLATFORM(IOS_FAMILY)
    , m_alternateFullScreenControlDesignEnabled(page->settings().alternateFullScreenControlDesignEnabled())
#endif
#if ENABLE(ALTERNATE_WEBM_PLAYER)
    , m_alternateWebMPlayerEnabled(page->settings().alternateWebMPlayerEnabled())
#endif
    , m_animatedImageAsyncDecodingEnabled(page->settings().animatedImageAsyncDecodingEnabled())
    , m_animatedImageDebugCanvasDrawingEnabled(page->settings().animatedImageDebugCanvasDrawingEnabled())
#if ENABLE(BADGING)
    , m_appBadgeEnabled(page->settings().appBadgeEnabled())
#endif
#if ENABLE(APP_HIGHLIGHTS)
    , m_appHighlightsEnabled(page->settings().appHighlightsEnabled())
#endif
    , m_appleMailPaginationQuirkEnabled(page->settings().appleMailPaginationQuirkEnabled())
#if ENABLE(APPLE_PAY)
    , m_applePayCapabilityDisclosureAllowed(page->settings().applePayCapabilityDisclosureAllowed())
#endif
#if ENABLE(APPLE_PAY)
    , m_applePayEnabled(page->settings().applePayEnabled())
#endif
    , m_ariaReflectionForElementReferencesEnabled(page->settings().ariaReflectionForElementReferencesEnabled())
    , m_aspectRatioEnabled(page->settings().aspectRatioEnabled())
    , m_aspectRatioOfImgFromWidthAndHeightEnabled(page->settings().aspectRatioOfImgFromWidthAndHeightEnabled())
    , m_asyncClipboardAPIEnabled(page->settings().asyncClipboardAPIEnabled())
    , m_asyncFrameScrollingEnabled(page->settings().asyncFrameScrollingEnabled())
    , m_asyncOverflowScrollingEnabled(page->settings().asyncOverflowScrollingEnabled())
    , m_asynchronousSpellCheckingEnabled(page->settings().asynchronousSpellCheckingEnabled())
#if ENABLE(ATTACHMENT_ELEMENT)
    , m_attachmentWideLayoutEnabled(page->settings().attachmentWideLayoutEnabled())
#endif
    , m_audioControlsScaleWithPageZoom(page->settings().audioControlsScaleWithPageZoom())
#if ENABLE(VIDEO)
    , m_audioDescriptionsEnabled(page->settings().audioDescriptionsEnabled())
#endif
    , m_authorAndUserStylesEnabled(page->settings().authorAndUserStylesEnabled())
    , m_autoscrollForDragAndDropEnabled(page->settings().autoscrollForDragAndDropEnabled())
#if ENABLE(SERVICE_WORKER)
    , m_backgroundFetchAPIEnabled(page->settings().backgroundFetchAPIEnabled())
#endif
    , m_backgroundShouldExtendBeyondPage(page->settings().backgroundShouldExtendBeyondPage())
#if PLATFORM(MAC) && USE(RUNNINGBOARD)
    , m_backgroundWebContentRunningBoardThrottlingEnabled(page->settings().backgroundWebContentRunningBoardThrottlingEnabled())
#endif
    , m_backspaceKeyNavigationEnabled(page->settings().backspaceKeyNavigationEnabled())
    , m_beaconAPIEnabled(page->settings().beaconAPIEnabled())
#if ENABLE(GPU_PROCESS)
    , m_blockMediaLayerRehostingInWebContentProcess(page->settings().blockMediaLayerRehostingInWebContentProcess())
#endif
    , m_broadcastChannelEnabled(page->settings().broadcastChannelEnabled())
    , m_broadcastChannelOriginPartitioningEnabled(page->settings().broadcastChannelOriginPartitioningEnabled())
    , m_cacheAPIEnabled(page->settings().cacheAPIEnabled())
    , m_canvasColorSpaceEnabled(page->settings().canvasColorSpaceEnabled())
    , m_canvasFiltersEnabled(page->settings().canvasFiltersEnabled())
    , m_canvasFingerprintingQuirkEnabled(page->settings().canvasFingerprintingQuirkEnabled())
    , m_canvasUsesAcceleratedDrawing(page->settings().canvasUsesAcceleratedDrawing())
    , m_caretBrowsingEnabled(page->settings().caretBrowsingEnabled())
    , m_clearSiteDataHTTPHeaderEnabled(page->settings().clearSiteDataHTTPHeaderEnabled())
#if ENABLE(BADGING)
    , m_clientBadgeEnabled(page->settings().clientBadgeEnabled())
#endif
    , m_clientCoordinatesRelativeToLayoutViewport(page->settings().clientCoordinatesRelativeToLayoutViewport())
    , m_colorFilterEnabled(page->settings().colorFilterEnabled())
    , m_compressionStreamEnabled(page->settings().compressionStreamEnabled())
    , m_constantPropertiesEnabled(page->settings().constantPropertiesEnabled())
    , m_constructableStylesheetsEnabled(page->settings().constructableStylesheetsEnabled())
    , m_contactPickerAPIEnabled(page->settings().contactPickerAPIEnabled())
#if ENABLE(CONTENT_CHANGE_OBSERVER)
    , m_contentChangeObserverEnabled(page->settings().contentChangeObserverEnabled())
#endif
    , m_contentDispositionAttachmentSandboxEnabled(page->settings().contentDispositionAttachmentSandboxEnabled())
#if ENABLE(CONTEXT_MENU_QR_CODE_DETECTION)
    , m_contextMenuQRCodeDetectionEnabled(page->settings().contextMenuQRCodeDetectionEnabled())
#endif
    , m_cookieConsentAPIEnabled(page->settings().cookieConsentAPIEnabled())
    , m_cookieEnabled(page->settings().cookieEnabled())
    , m_cookieStoreAPIEnabled(page->settings().cookieStoreAPIEnabled())
    , m_cookieStoreAPIExtendedAttributesEnabled(page->settings().cookieStoreAPIExtendedAttributesEnabled())
    , m_coreMathMLEnabled(page->settings().coreMathMLEnabled())
    , m_crossOriginCheckInGetMatchedCSSRulesDisabled(page->settings().crossOriginCheckInGetMatchedCSSRulesDisabled())
    , m_crossOriginEmbedderPolicyEnabled(page->settings().crossOriginEmbedderPolicyEnabled())
    , m_crossOriginOpenerPolicyEnabled(page->settings().crossOriginOpenerPolicyEnabled())
    , m_css3DTransformInteroperabilityEnabled(page->settings().css3DTransformInteroperabilityEnabled())
    , m_cssCascadeLayersEnabled(page->settings().cssCascadeLayersEnabled())
    , m_cssColor4(page->settings().cssColor4())
    , m_cssColorContrastEnabled(page->settings().cssColorContrastEnabled())
    , m_cssColorMixEnabled(page->settings().cssColorMixEnabled())
    , m_cssContainIntrinsicSizeEnabled(page->settings().cssContainIntrinsicSizeEnabled())
    , m_cssContainerQueriesEnabled(page->settings().cssContainerQueriesEnabled())
    , m_cssContainmentEnabled(page->settings().cssContainmentEnabled())
    , m_cssContentVisibilityEnabled(page->settings().cssContentVisibilityEnabled())
    , m_cssCounterStyleAtRuleImageSymbolsEnabled(page->settings().cssCounterStyleAtRuleImageSymbolsEnabled())
    , m_cssCounterStyleAtRulesEnabled(page->settings().cssCounterStyleAtRulesEnabled())
    , m_cssCustomPropertiesAndValuesEnabled(page->settings().cssCustomPropertiesAndValuesEnabled())
    , m_cssFontFaceSizeAdjustEnabled(page->settings().cssFontFaceSizeAdjustEnabled())
    , m_cssGradientInterpolationColorSpacesEnabled(page->settings().cssGradientInterpolationColorSpacesEnabled())
    , m_cssGradientPremultipliedAlphaInterpolationEnabled(page->settings().cssGradientPremultipliedAlphaInterpolationEnabled())
    , m_cssIndividualTransformPropertiesEnabled(page->settings().cssIndividualTransformPropertiesEnabled())
    , m_cssInputSecurityEnabled(page->settings().cssInputSecurityEnabled())
    , m_cssMarginTrimEnabled(page->settings().cssMarginTrimEnabled())
    , m_cssMotionPathEnabled(page->settings().cssMotionPathEnabled())
    , m_cssNestingEnabled(page->settings().cssNestingEnabled())
#if ENABLE(CSS_PAINTING_API)
    , m_cssPaintingAPIEnabled(page->settings().cssPaintingAPIEnabled())
#endif
    , m_cssRelativeColorSyntaxEnabled(page->settings().cssRelativeColorSyntaxEnabled())
    , m_cssRhythmicSizingEnabled(page->settings().cssRhythmicSizingEnabled())
    , m_cssScrollAnchoringEnabled(page->settings().cssScrollAnchoringEnabled())
    , m_cssScrollbarColorEnabled(page->settings().cssScrollbarColorEnabled())
    , m_cssScrollbarGutterEnabled(page->settings().cssScrollbarGutterEnabled())
    , m_cssScrollbarWidthEnabled(page->settings().cssScrollbarWidthEnabled())
    , m_cssTextAlignLastEnabled(page->settings().cssTextAlignLastEnabled())
    , m_cssTextBoxTrimEnabled(page->settings().cssTextBoxTrimEnabled())
    , m_cssTextGroupAlignEnabled(page->settings().cssTextGroupAlignEnabled())
    , m_cssTextJustifyEnabled(page->settings().cssTextJustifyEnabled())
    , m_cssTextSpacingEnabled(page->settings().cssTextSpacingEnabled())
    , m_cssTextUnderlinePositionLeftRightEnabled(page->settings().cssTextUnderlinePositionLeftRightEnabled())
    , m_cssTextWrapNewValuesEnabled(page->settings().cssTextWrapNewValuesEnabled())
#if ENABLE(CSS_TRANSFORM_STYLE_OPTIMIZED_3D)
    , m_cssTransformStyleOptimized3DEnabled(page->settings().cssTransformStyleOptimized3DEnabled())
#endif
    , m_cssTypedOMColorEnabled(page->settings().cssTypedOMColorEnabled())
    , m_cssTypedOMEnabled(page->settings().cssTypedOMEnabled())
    , m_cssWhiteSpaceLonghandsEnabled(page->settings().cssWhiteSpaceLonghandsEnabled())
    , m_cssWordBreakAutoEnabled(page->settings().cssWordBreakAutoEnabled())
    , m_cursiveFontFamily(page->settings().cursiveFontFamily())
#if ENABLE(DATALIST_ELEMENT)
    , m_dataListElementEnabled(page->settings().dataListElementEnabled())
#endif
    , m_dataTransferItemsEnabled(page->settings().dataTransferItemsEnabled())
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    , m_dateTimeInputsEditableComponentsEnabled(page->settings().dateTimeInputsEditableComponentsEnabled())
#endif
    , m_declarativeShadowDOMEnabled(page->settings().declarativeShadowDOMEnabled())
    , m_declarativeShadowDOMInDOMParserEnabled(page->settings().declarativeShadowDOMInDOMParserEnabled())
    , m_defaultARIAForCustomElementsEnabled(page->settings().defaultARIAForCustomElementsEnabled())
    , m_defaultFixedFontSize(page->settings().defaultFixedFontSize())
    , m_defaultFontSize(page->settings().defaultFontSize())
    , m_defaultTextEncodingName(page->settings().defaultTextEncodingName())
    , m_defaultVideoPosterURL(page->settings().defaultVideoPosterURL())
    , m_deprecateRSAESPKCSWebCryptoEnabled(page->settings().deprecateRSAESPKCSWebCryptoEnabled())
    , m_deprecationReportingEnabled(page->settings().deprecationReportingEnabled())
    , m_developerExtrasEnabled(page->settings().developerExtrasEnabled())
    , m_deviceHeight(page->settings().deviceHeight())
#if ENABLE(DEVICE_ORIENTATION)
    , m_deviceOrientationEventEnabled(page->settings().deviceOrientationEventEnabled())
#endif
#if ENABLE(DEVICE_ORIENTATION)
    , m_deviceOrientationPermissionAPIEnabled(page->settings().deviceOrientationPermissionAPIEnabled())
#endif
    , m_deviceWidth(page->settings().deviceWidth())
    , m_diagnosticLoggingEnabled(page->settings().diagnosticLoggingEnabled())
    , m_dialogElementEnabled(page->settings().dialogElementEnabled())
    , m_dirPseudoEnabled(page->settings().dirPseudoEnabled())
    , m_directoryUploadEnabled(page->settings().directoryUploadEnabled())
    , m_disabledAdaptationsMetaTagEnabled(page->settings().disabledAdaptationsMetaTagEnabled())
    , m_disallowSyncXHRDuringPageDismissalEnabled(page->settings().disallowSyncXHRDuringPageDismissalEnabled())
    , m_displayListDrawingEnabled(page->settings().displayListDrawingEnabled())
    , m_dnsPrefetchingEnabled(page->settings().dnsPrefetchingEnabled())
#if ENABLE(DOM_AUDIO_SESSION)
    , m_domAudioSessionEnabled(page->settings().domAudioSessionEnabled())
#endif
#if ENABLE(DOM_AUDIO_SESSION)
    , m_domAudioSessionFullEnabled(page->settings().domAudioSessionFullEnabled())
#endif
    , m_domPasteAccessRequestsEnabled(page->settings().domPasteAccessRequestsEnabled())
    , m_domPasteAllowed(page->settings().domPasteAllowed())
    , m_domTestingAPIsEnabled(page->settings().domTestingAPIsEnabled())
    , m_domTimersThrottlingEnabled(page->settings().domTimersThrottlingEnabled())
#if ENABLE(DOWNLOAD_ATTRIBUTE)
    , m_downloadAttributeEnabled(page->settings().downloadAttributeEnabled())
#endif
    , m_embedElementEnabled(page->settings().embedElementEnabled())
    , m_enableInheritURIQueryComponent(page->settings().enableInheritURIQueryComponent())
#if ENABLE(ENCRYPTED_MEDIA)
    , m_encryptedMediaAPIEnabled(page->settings().encryptedMediaAPIEnabled())
#endif
    , m_enterKeyHintEnabled(page->settings().enterKeyHintEnabled())
    , m_eventHandlerDrivenSmoothKeyboardScrollingEnabled(page->settings().eventHandlerDrivenSmoothKeyboardScrollingEnabled())
#if ENABLE(MEDIA_STREAM)
    , m_exposeSpeakersEnabled(page->settings().exposeSpeakersEnabled())
#endif
#if ENABLE(VIDEO)
    , m_extendedAudioDescriptionsEnabled(page->settings().extendedAudioDescriptionsEnabled())
#endif
    , m_fantasyFontFamily(page->settings().fantasyFontFamily())
    , m_fetchAPIEnabled(page->settings().fetchAPIEnabled())
    , m_fetchMetadataEnabled(page->settings().fetchMetadataEnabled())
    , m_fetchPriorityEnabled(page->settings().fetchPriorityEnabled())
    , m_fileReaderAPIEnabled(page->settings().fileReaderAPIEnabled())
    , m_fileSystemAccessEnabled(page->settings().fileSystemAccessEnabled())
    , m_fixedBackgroundsPaintRelativeToDocument(page->settings().fixedBackgroundsPaintRelativeToDocument())
    , m_fixedElementsLayoutRelativeToFrame(page->settings().fixedElementsLayoutRelativeToFrame())
    , m_fixedFontFamily(page->settings().fixedFontFamily())
    , m_flexFormattingContextIntegrationEnabled(page->settings().flexFormattingContextIntegrationEnabled())
    , m_focusVisibleEnabled(page->settings().focusVisibleEnabled())
    , m_fontFallbackPrefersPictographs(page->settings().fontFallbackPrefersPictographs())
    , m_forceCompositingMode(page->settings().forceCompositingMode())
    , m_forceFTPDirectoryListings(page->settings().forceFTPDirectoryListings())
    , m_forceWebGLUsesLowPower(page->settings().forceWebGLUsesLowPower())
    , m_formAssociatedCustomElementsEnabled(page->settings().formAssociatedCustomElementsEnabled())
    , m_ftpDirectoryTemplatePath(page->settings().ftpDirectoryTemplatePath())
    , m_ftpEnabled(page->settings().ftpEnabled())
#if ENABLE(FULLSCREEN_API)
    , m_fullScreenEnabled(page->settings().fullScreenEnabled())
#endif
    , m_fullscreenRequirementForScreenOrientationLockingEnabled(page->settings().fullscreenRequirementForScreenOrientationLockingEnabled())
#if PLATFORM(VISION)
    , m_fullscreenSceneAspectRatioLockingEnabled(page->settings().fullscreenSceneAspectRatioLockingEnabled())
#endif
#if PLATFORM(VISION)
    , m_fullscreenSceneDimmingEnabled(page->settings().fullscreenSceneDimmingEnabled())
#endif
#if ENABLE(GAMEPAD)
    , m_gamepadTriggerRumbleEnabled(page->settings().gamepadTriggerRumbleEnabled())
#endif
#if ENABLE(GAMEPAD)
    , m_gamepadVibrationActuatorEnabled(page->settings().gamepadVibrationActuatorEnabled())
#endif
#if ENABLE(GAMEPAD)
    , m_gamepadsEnabled(page->settings().gamepadsEnabled())
#endif
#if ENABLE(VIDEO)
    , m_genericCueAPIEnabled(page->settings().genericCueAPIEnabled())
#endif
    , m_geolocationFloorLevelEnabled(page->settings().geolocationFloorLevelEnabled())
#if ENABLE(MEDIA_STREAM)
    , m_getUserMediaRequiresFocus(page->settings().getUserMediaRequiresFocus())
#endif
    , m_googleAntiFlickerOptimizationQuirkEnabled(page->settings().googleAntiFlickerOptimizationQuirkEnabled())
#if USE(GRAPHICS_CONTEXT_FILTERS)
    , m_graphicsContextFiltersEnabled(page->settings().graphicsContextFiltersEnabled())
#endif
    , m_hasPseudoClassEnabled(page->settings().hasPseudoClassEnabled())
    , m_hiddenPageCSSAnimationSuspensionEnabled(page->settings().hiddenPageCSSAnimationSuspensionEnabled())
    , m_hiddenPageDOMTimerThrottlingAutoIncreases(page->settings().hiddenPageDOMTimerThrottlingAutoIncreases())
    , m_hiddenPageDOMTimerThrottlingEnabled(page->settings().hiddenPageDOMTimerThrottlingEnabled())
    , m_httpEquivEnabled(page->settings().httpEquivEnabled())
    , m_hyperlinkAuditingEnabled(page->settings().hyperlinkAuditingEnabled())
#if ENABLE(IOS_FORM_CONTROL_REFRESH)
    , m_iOSFormControlRefreshEnabled(page->settings().iOSFormControlRefreshEnabled())
#endif
    , m_iceCandidateFilteringEnabled(page->settings().iceCandidateFilteringEnabled())
#if ENABLE(TEXT_AUTOSIZING)
    , m_idempotentModeAutosizingOnlyHonorsPercentages(page->settings().idempotentModeAutosizingOnlyHonorsPercentages())
#endif
#if ENABLE(IMAGE_ANALYSIS)
    , m_imageAnalysisDuringFindInPageEnabled(page->settings().imageAnalysisDuringFindInPageEnabled())
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    , m_imageAnimationControlEnabled(page->settings().imageAnimationControlEnabled())
#endif
#if ENABLE(SERVICE_CONTROLS)
    , m_imageControlsEnabled(page->settings().imageControlsEnabled())
#endif
    , m_imageSubsamplingEnabled(page->settings().imageSubsamplingEnabled())
    , m_imagesEnabled(page->settings().areImagesEnabled())
    , m_imperativeSlotAPIEnabled(page->settings().imperativeSlotAPIEnabled())
    , m_incompleteImageBorderEnabled(page->settings().incompleteImageBorderEnabled())
#if HAVE(INCREMENTAL_PDF_APIS)
    , m_incrementalPDFLoadingEnabled(page->settings().incrementalPDFLoadingEnabled())
#endif
    , m_incrementalRenderingSuppressionTimeoutInSeconds(page->settings().incrementalRenderingSuppressionTimeoutInSeconds())
    , m_indexedDBAPIEnabled(page->settings().indexedDBAPIEnabled())
    , m_inertAttributeEnabled(page->settings().inertAttributeEnabled())
    , m_inlineMediaPlaybackRequiresPlaysInlineAttribute(page->settings().inlineMediaPlaybackRequiresPlaysInlineAttribute())
    , m_inlinePredictionsInAllEditableElementsEnabled(page->settings().inlinePredictionsInAllEditableElementsEnabled())
#if ENABLE(INPUT_TYPE_COLOR)
    , m_inputTypeColorEnabled(page->settings().inputTypeColorEnabled())
#endif
#if ENABLE(INPUT_TYPE_DATE)
    , m_inputTypeDateEnabled(page->settings().inputTypeDateEnabled())
#endif
#if ENABLE(INPUT_TYPE_DATETIMELOCAL)
    , m_inputTypeDateTimeLocalEnabled(page->settings().inputTypeDateTimeLocalEnabled())
#endif
#if ENABLE(INPUT_TYPE_MONTH)
    , m_inputTypeMonthEnabled(page->settings().inputTypeMonthEnabled())
#endif
#if ENABLE(INPUT_TYPE_TIME)
    , m_inputTypeTimeEnabled(page->settings().inputTypeTimeEnabled())
#endif
#if ENABLE(INPUT_TYPE_WEEK)
    , m_inputTypeWeekEnabled(page->settings().inputTypeWeekEnabled())
#endif
    , m_interactionRegionInlinePadding(page->settings().interactionRegionInlinePadding())
    , m_interactionRegionMinimumCornerRadius(page->settings().interactionRegionMinimumCornerRadius())
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
    , m_interactionRegionsEnabled(page->settings().interactionRegionsEnabled())
#endif
    , m_interactiveFormValidationEnabled(page->settings().interactiveFormValidationEnabled())
#if ENABLE(MEDIA_STREAM)
    , m_interruptAudioOnPageVisibilityChangeEnabled(page->settings().interruptAudioOnPageVisibilityChangeEnabled())
#endif
#if ENABLE(MEDIA_STREAM)
    , m_interruptVideoOnPageVisibilityChangeEnabled(page->settings().interruptVideoOnPageVisibilityChangeEnabled())
#endif
    , m_intersectionObserverEnabled(page->settings().intersectionObserverEnabled())
    , m_invisibleAutoplayNotPermitted(page->settings().invisibleAutoplayNotPermitted())
    , m_isFirstPartyWebsiteDataRemovalDisabled(page->settings().isFirstPartyWebsiteDataRemovalDisabled())
    , m_isFirstPartyWebsiteDataRemovalLiveOnTestingEnabled(page->settings().isFirstPartyWebsiteDataRemovalLiveOnTestingEnabled())
    , m_isFirstPartyWebsiteDataRemovalReproTestingEnabled(page->settings().isFirstPartyWebsiteDataRemovalReproTestingEnabled())
    , m_isLoggedInAPIEnabled(page->settings().isLoggedInAPIEnabled())
    , m_isPerActivityStateCPUUsageMeasurementEnabled(page->settings().isPerActivityStateCPUUsageMeasurementEnabled())
    , m_isPostBackgroundingCPUUsageMeasurementEnabled(page->settings().isPostBackgroundingCPUUsageMeasurementEnabled())
    , m_isPostBackgroundingMemoryUsageMeasurementEnabled(page->settings().isPostBackgroundingMemoryUsageMeasurementEnabled())
    , m_isPostLoadCPUUsageMeasurementEnabled(page->settings().isPostLoadCPUUsageMeasurementEnabled())
    , m_isPostLoadMemoryUsageMeasurementEnabled(page->settings().isPostLoadMemoryUsageMeasurementEnabled())
    , m_isSameSiteStrictEnforcementEnabled(page->settings().isSameSiteStrictEnforcementEnabled())
    , m_isThirdPartyCookieBlockingDisabled(page->settings().isThirdPartyCookieBlockingDisabled())
    , m_itpDebugModeEnabled(page->settings().itpDebugModeEnabled())
    , m_javaScriptCanAccessClipboard(page->settings().javaScriptCanAccessClipboard())
    , m_javaScriptCanOpenWindowsAutomatically(page->settings().javaScriptCanOpenWindowsAutomatically())
    , m_langAttributeAwareFormControlUIEnabled(page->settings().langAttributeAwareFormControlUIEnabled())
    , m_largeImageAsyncDecodingEnabled(page->settings().largeImageAsyncDecodingEnabled())
#if ENABLE(LAYER_BASED_SVG_ENGINE)
    , m_layerBasedSVGEngineEnabled(page->settings().layerBasedSVGEngineEnabled())
#endif
    , m_layoutFallbackWidth(page->settings().layoutFallbackWidth())
    , m_layoutFormattingContextEnabled(page->settings().layoutFormattingContextEnabled())
    , m_layoutViewportHeightExpansionFactor(page->settings().layoutViewportHeightExpansionFactor())
    , m_lazyIframeLoadingEnabled(page->settings().lazyIframeLoadingEnabled())
    , m_lazyImageLoadingEnabled(page->settings().lazyImageLoadingEnabled())
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    , m_legacyEncryptedMediaAPIEnabled(page->settings().legacyEncryptedMediaAPIEnabled())
#endif
    , m_legacyLineLayoutVisualCoverageEnabled(page->settings().legacyLineLayoutVisualCoverageEnabled())
#if ENABLE(OVERFLOW_SCROLLING_TOUCH)
    , m_legacyOverflowScrollingTouchEnabled(page->settings().legacyOverflowScrollingTouchEnabled())
#endif
    , m_linkModulePreloadEnabled(page->settings().linkModulePreloadEnabled())
    , m_linkPreconnectEarlyHintsEnabled(page->settings().linkPreconnectEarlyHintsEnabled())
    , m_linkPreconnectEnabled(page->settings().linkPreconnectEnabled())
    , m_linkPrefetchEnabled(page->settings().linkPrefetchEnabled())
    , m_linkPreloadEnabled(page->settings().linkPreloadEnabled())
    , m_linkPreloadResponsiveImagesEnabled(page->settings().linkPreloadResponsiveImagesEnabled())
    , m_linkSanitizerEnabled(page->settings().linkSanitizerEnabled())
    , m_liveRangeSelectionEnabled(page->settings().liveRangeSelectionEnabled())
    , m_loadDeferringEnabled(page->settings().loadDeferringEnabled())
    , m_loadsImagesAutomatically(page->settings().loadsImagesAutomatically())
    , m_localFileContentSniffingEnabled(page->settings().localFileContentSniffingEnabled())
    , m_localStorageDatabasePath(page->settings().localStorageDatabasePath())
    , m_localStorageEnabled(page->settings().localStorageEnabled())
    , m_logsPageMessagesToSystemConsoleEnabled(page->settings().logsPageMessagesToSystemConsoleEnabled())
    , m_mainContentUserGestureOverrideEnabled(page->settings().mainContentUserGestureOverrideEnabled())
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
    , m_manageCaptureStatusBarInGPUProcessEnabled(page->settings().manageCaptureStatusBarInGPUProcessEnabled())
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    , m_managedMediaSourceEnabled(page->settings().managedMediaSourceEnabled())
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    , m_managedMediaSourceHighThreshold(page->settings().managedMediaSourceHighThreshold())
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    , m_managedMediaSourceLowThreshold(page->settings().managedMediaSourceLowThreshold())
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE) && ENABLE(WIRELESS_PLAYBACK_TARGET)
    , m_managedMediaSourceNeedsAirPlay(page->settings().managedMediaSourceNeedsAirPlay())
#endif
#if ENABLE(WEBGL)
    , m_maskWebGLStringsEnabled(page->settings().maskWebGLStringsEnabled())
#endif
    , m_masonryEnabled(page->settings().masonryEnabled())
    , m_masonryTrackAlignmentEnabled(page->settings().masonryTrackAlignmentEnabled())
#if ENABLE(MATHML)
    , m_mathMLEnabled(page->settings().mathMLEnabled())
#endif
    , m_maxParseDuration(page->settings().maxParseDuration())
    , m_maximumAccelerated2dCanvasSize(page->settings().maximumAccelerated2dCanvasSize())
    , m_maximumHTMLParserDOMTreeDepth(page->settings().maximumHTMLParserDOMTreeDepth())
#if ENABLE(MEDIA_SOURCE)
    , m_maximumSourceBufferSize(page->settings().maximumSourceBufferSize())
#endif
    , m_mediaCapabilitiesEnabled(page->settings().mediaCapabilitiesEnabled())
    , m_mediaCapabilitiesExtensionsEnabled(page->settings().mediaCapabilitiesExtensionsEnabled())
#if ENABLE(MEDIA_STREAM)
    , m_mediaCaptureRequiresSecureConnection(page->settings().mediaCaptureRequiresSecureConnection())
#endif
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS)
    , m_mediaControlsContextMenusEnabled(page->settings().mediaControlsContextMenusEnabled())
#endif
    , m_mediaControlsScaleWithPageZoom(page->settings().mediaControlsScaleWithPageZoom())
    , m_mediaDataLoadsAutomatically(page->settings().mediaDataLoadsAutomatically())
#if ENABLE(MEDIA_STREAM)
    , m_mediaDevicesEnabled(page->settings().mediaDevicesEnabled())
#endif
#if ENABLE(VIDEO)
    , m_mediaEnabled(page->settings().mediaEnabled())
#endif
    , m_mediaKeysStorageDirectory(page->settings().mediaKeysStorageDirectory())
    , m_mediaPreferredFullscreenWidth(page->settings().mediaPreferredFullscreenWidth())
    , m_mediaPreloadingEnabled(page->settings().mediaPreloadingEnabled())
#if ENABLE(MEDIA_RECORDER)
    , m_mediaRecorderEnabled(page->settings().mediaRecorderEnabled())
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
    , m_mediaSessionCoordinatorEnabled(page->settings().mediaSessionCoordinatorEnabled())
#endif
#if ENABLE(MEDIA_SESSION)
    , m_mediaSessionEnabled(page->settings().mediaSessionEnabled())
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR) && ENABLE(MEDIA_SESSION_PLAYLIST)
    , m_mediaSessionPlaylistEnabled(page->settings().mediaSessionPlaylistEnabled())
#endif
    , m_mediaSourceEnabled(page->settings().mediaSourceEnabled())
#if ENABLE(MEDIA_STREAM)
    , m_mediaStreamEnabled(page->settings().mediaStreamEnabled())
#endif
    , m_mediaTypeOverride(page->settings().mediaTypeOverride())
    , m_mediaUserGestureInheritsFromDocument(page->settings().mediaUserGestureInheritsFromDocument())
    , m_menuItemElementEnabled(page->settings().menuItemElementEnabled())
    , m_minimumAccelerated2dCanvasSize(page->settings().minimumAccelerated2dCanvasSize())
    , m_minimumFontSize(page->settings().minimumFontSize())
    , m_minimumLogicalFontSize(page->settings().minimumLogicalFontSize())
#if ENABLE(TEXT_AUTOSIZING)
    , m_minimumZoomFontSize(page->settings().minimumZoomFontSize())
#endif
#if ENABLE(MEDIA_STREAM)
    , m_mockCaptureDevicesEnabled(page->settings().mockCaptureDevicesEnabled())
#endif
    , m_mockScrollbarsControllerEnabled(page->settings().mockScrollbarsControllerEnabled())
#if ENABLE(MODEL_ELEMENT)
    , m_modelElementEnabled(page->settings().modelElementEnabled())
#endif
    , m_momentumScrollingAnimatorEnabled(page->settings().momentumScrollingAnimatorEnabled())
#if ENABLE(TOUCH_EVENTS)
    , m_mouseEventsSimulationEnabled(page->settings().mouseEventsSimulationEnabled())
#endif
#if ENABLE(MEDIA_STREAM)
    , m_muteCameraOnMicrophoneInterruptionEnabled(page->settings().muteCameraOnMicrophoneInterruptionEnabled())
#endif
    , m_needsAdobeFrameReloadingQuirk(page->settings().needsAcrobatFrameReloadingQuirk())
    , m_needsDeferKeyDownAndKeyPressTimersUntilNextEditingCommandQuirk(page->settings().needsDeferKeyDownAndKeyPressTimersUntilNextEditingCommandQuirk())
    , m_needsFrameNameFallbackToIdQuirk(page->settings().needsFrameNameFallbackToIdQuirk())
    , m_needsKeyboardEventDisambiguationQuirks(page->settings().needsKeyboardEventDisambiguationQuirks())
    , m_needsSiteSpecificQuirks(page->settings().needsSiteSpecificQuirks())
    , m_needsStorageAccessFromFileURLsQuirk(page->settings().needsStorageAccessFromFileURLsQuirk())
#if ENABLE(NOTIFICATION_EVENT)
    , m_notificationEventEnabled(page->settings().notificationEventEnabled())
#endif
#if ENABLE(NOTIFICATIONS)
    , m_notificationsEnabled(page->settings().notificationsEnabled())
#endif
    , m_offlineWebApplicationCacheEnabled(page->settings().offlineWebApplicationCacheEnabled())
#if ENABLE(OFFSCREEN_CANVAS)
    , m_offscreenCanvasEnabled(page->settings().offscreenCanvasEnabled())
#endif
#if ENABLE(OFFSCREEN_CANVAS_IN_WORKERS)
    , m_offscreenCanvasInWorkersEnabled(page->settings().offscreenCanvasInWorkersEnabled())
#endif
    , m_overflowClipEnabled(page->settings().overflowClipEnabled())
    , m_overscrollBehaviorEnabled(page->settings().overscrollBehaviorEnabled())
    , m_pageAtRuleSupportEnabled(page->settings().pageAtRuleSupportEnabled())
    , m_passiveTouchListenersAsDefaultOnDocument(page->settings().passiveTouchListenersAsDefaultOnDocument())
    , m_passiveWheelListenersAsDefaultOnDocument(page->settings().passiveWheelListenersAsDefaultOnDocument())
    , m_passwordEchoDurationInSeconds(page->settings().passwordEchoDurationInSeconds())
    , m_passwordEchoEnabled(page->settings().passwordEchoEnabled())
#if ENABLE(PAYMENT_REQUEST)
    , m_paymentRequestEnabled(page->settings().paymentRequestEnabled())
#endif
#if ENABLE(PDFJS)
    , m_pdfJSViewerEnabled(page->settings().pdfJSViewerEnabled())
#endif
#if ENABLE(WEB_RTC)
    , m_peerConnectionEnabled(page->settings().peerConnectionEnabled())
#endif
#if ENABLE(MEDIA_STREAM)
    , m_perElementSpeakerSelectionEnabled(page->settings().perElementSpeakerSelectionEnabled())
#endif
    , m_performanceNavigationTimingAPIEnabled(page->settings().performanceNavigationTimingAPIEnabled())
    , m_performanceResourceTimingSensitivePropertiesEnabled(page->settings().performanceResourceTimingSensitivePropertiesEnabled())
    , m_permissionsAPIEnabled(page->settings().permissionsAPIEnabled())
    , m_pictographFontFamily(page->settings().pictographFontFamily())
#if ENABLE(PICTURE_IN_PICTURE_API)
    , m_pictureInPictureAPIEnabled(page->settings().pictureInPictureAPIEnabled())
#endif
    , m_pluginsEnabled(page->settings().arePluginsEnabled())
    , m_popoverAttributeEnabled(page->settings().popoverAttributeEnabled())
    , m_preferMIMETypeForImages(page->settings().preferMIMETypeForImages())
    , m_preferPageRenderingUpdatesNear60FPSEnabled(page->settings().preferPageRenderingUpdatesNear60FPSEnabled())
#if ENABLE(VIDEO)
    , m_preferSandboxedMediaParsing(page->settings().preferSandboxedMediaParsing())
#endif
    , m_preventKeyboardDOMEventDispatch(page->settings().preventKeyboardDOMEventDispatch())
    , m_privateClickMeasurementDebugModeEnabled(page->settings().privateClickMeasurementDebugModeEnabled())
    , m_privateClickMeasurementEnabled(page->settings().privateClickMeasurementEnabled())
    , m_privateClickMeasurementFraudPreventionEnabled(page->settings().privateClickMeasurementFraudPreventionEnabled())
    , m_punchOutWhiteBackgroundsInDarkMode(page->settings().punchOutWhiteBackgroundsInDarkMode())
#if ENABLE(SERVICE_WORKER)
    , m_pushAPIEnabled(page->settings().pushAPIEnabled())
#endif
    , m_referrerPolicyAttributeEnabled(page->settings().referrerPolicyAttributeEnabled())
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    , m_remotePlaybackEnabled(page->settings().remotePlaybackEnabled())
#endif
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    , m_removeBackgroundEnabled(page->settings().removeBackgroundEnabled())
#endif
    , m_reportingEnabled(page->settings().reportingEnabled())
    , m_requestIdleCallbackEnabled(page->settings().requestIdleCallbackEnabled())
    , m_requestSubmitEnabled(page->settings().requestSubmitEnabled())
    , m_requestVideoFrameCallbackEnabled(page->settings().requestVideoFrameCallbackEnabled())
#if HAVE(SC_CONTENT_SHARING_PICKER)
    , m_requireUAGetDisplayMediaPrompt(page->settings().requireUAGetDisplayMediaPrompt())
#endif
    , m_requiresPageVisibilityToPlayAudio(page->settings().requiresPageVisibilityToPlayAudio())
    , m_requiresUserGestureForAudioPlayback(page->settings().requiresUserGestureForAudioPlayback())
    , m_requiresUserGestureForVideoPlayback(page->settings().requiresUserGestureForVideoPlayback())
    , m_requiresUserGestureToLoadVideo(page->settings().requiresUserGestureToLoadVideo())
    , m_resizeObserverEnabled(page->settings().resizeObserverEnabled())
    , m_resourceLoadSchedulingEnabled(page->settings().resourceLoadSchedulingEnabled())
#if ENABLE(RESOURCE_USAGE)
    , m_resourceUsageOverlayVisible(page->settings().resourceUsageOverlayVisible())
#endif
#if HAVE(RUBBER_BANDING)
    , m_rubberBandingForSubScrollableRegionsEnabled(page->settings().rubberBandingForSubScrollableRegionsEnabled())
#endif
    , m_sKAttributionEnabled(page->settings().sKAttributionEnabled())
#if HAVE(AVCONTENTKEYSPECIFIER)
    , m_sampleBufferContentKeySessionSupportEnabled(page->settings().sampleBufferContentKeySessionSupportEnabled())
#endif
    , m_sampledPageTopColorMaxDifference(page->settings().sampledPageTopColorMaxDifference())
    , m_sampledPageTopColorMinHeight(page->settings().sampledPageTopColorMinHeight())
    , m_sansSerifFontFamily(page->settings().sansSerifFontFamily())
#if ENABLE(MEDIA_STREAM)
    , m_screenCaptureEnabled(page->settings().screenCaptureEnabled())
#endif
    , m_screenOrientationAPIEnabled(page->settings().screenOrientationAPIEnabled())
    , m_screenOrientationLockingAPIEnabled(page->settings().screenOrientationLockingAPIEnabled())
    , m_screenWakeLockAPIEnabled(page->settings().screenWakeLockAPIEnabled())
    , m_scriptEnabled(page->settings().isScriptEnabled())
    , m_scriptMarkupEnabled(page->settings().scriptMarkupEnabled())
    , m_scrollAnimatorEnabled(page->settings().scrollAnimatorEnabled())
    , m_scrollToTextFragmentEnabled(page->settings().scrollToTextFragmentEnabled())
    , m_scrollToTextFragmentIndicatorEnabled(page->settings().scrollToTextFragmentIndicatorEnabled())
    , m_scrollingCoordinatorEnabled(page->settings().scrollingCoordinatorEnabled())
    , m_scrollingPerformanceTestingEnabled(page->settings().scrollingPerformanceTestingEnabled())
    , m_scrollingTreeIncludesFrames(page->settings().scrollingTreeIncludesFrames())
    , m_searchInputIncrementalAttributeAndSearchEventEnabled(page->settings().searchInputIncrementalAttributeAndSearchEventEnabled())
    , m_secureContextChecksEnabled(page->settings().secureContextChecksEnabled())
    , m_selectTrailingWhitespaceEnabled(page->settings().selectTrailingWhitespaceEnabled())
    , m_selectionAPIForShadowDOMEnabled(page->settings().selectionAPIForShadowDOMEnabled())
    , m_sendMouseEventsToDisabledFormControlsEnabled(page->settings().sendMouseEventsToDisabledFormControlsEnabled())
    , m_serifFontFamily(page->settings().serifFontFamily())
#if ENABLE(SERVICE_CONTROLS)
    , m_serviceControlsEnabled(page->settings().serviceControlsEnabled())
#endif
#if ENABLE(SERVICE_WORKER)
    , m_serviceWorkerNavigationPreloadEnabled(page->settings().serviceWorkerNavigationPreloadEnabled())
#endif
#if ENABLE(SERVICE_WORKER)
    , m_serviceWorkersEnabled(page->settings().serviceWorkersEnabled())
#endif
#if ENABLE(SERVICE_WORKER)
    , m_serviceWorkersUserGestureEnabled(page->settings().serviceWorkersUserGestureEnabled())
#endif
    , m_sessionStorageQuota(page->settings().sessionStorageQuota())
    , m_shapeDetection(page->settings().shapeDetection())
    , m_sharedWorkerEnabled(page->settings().sharedWorkerEnabled())
    , m_shouldAllowUserInstalledFonts(page->settings().shouldAllowUserInstalledFonts())
    , m_shouldConvertInvalidURLsToBlank(page->settings().shouldConvertInvalidURLsToBlank())
    , m_shouldConvertPositionStyleOnCopy(page->settings().shouldConvertPositionStyleOnCopy())
    , m_shouldDecidePolicyBeforeLoadingQuickLookPreview(page->settings().shouldDecidePolicyBeforeLoadingQuickLookPreview())
    , m_shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint(page->settings().shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint())
    , m_shouldDispatchSyntheticMouseEventsWhenModifyingSelection(page->settings().shouldDispatchSyntheticMouseEventsWhenModifyingSelection())
    , m_shouldDispatchSyntheticMouseOutAfterSyntheticClick(page->settings().shouldDispatchSyntheticMouseOutAfterSyntheticClick())
#if ENABLE(VIDEO)
    , m_shouldDisplayCaptions(page->settings().shouldDisplayCaptions())
#endif
#if ENABLE(VIDEO)
    , m_shouldDisplaySubtitles(page->settings().shouldDisplaySubtitles())
#endif
#if ENABLE(VIDEO)
    , m_shouldDisplayTextDescriptions(page->settings().shouldDisplayTextDescriptions())
#endif
    , m_shouldDropNearSuspendedAssertionAfterDelay(page->settings().shouldDropNearSuspendedAssertionAfterDelay())
#if ENABLE(TEXT_AUTOSIZING)
    , m_shouldEnableTextAutosizingBoost(page->settings().shouldEnableTextAutosizingBoost())
#endif
    , m_shouldIgnoreFontLoadCompletions(page->settings().shouldIgnoreFontLoadCompletions())
    , m_shouldIgnoreMetaViewport(page->settings().shouldIgnoreMetaViewport())
    , m_shouldInjectUserScriptsInInitialEmptyDocument(page->settings().shouldInjectUserScriptsInInitialEmptyDocument())
    , m_shouldPrintBackgrounds(page->settings().shouldPrintBackgrounds())
    , m_shouldRespectImageOrientation(page->settings().shouldRespectImageOrientation())
    , m_shouldRestrictBaseURLSchemes(page->settings().shouldRestrictBaseURLSchemes())
    , m_shouldSuppressTextInputFromEditingDuringProvisionalNavigation(page->settings().shouldSuppressTextInputFromEditingDuringProvisionalNavigation())
    , m_shouldTakeNearSuspendedAssertions(page->settings().shouldTakeNearSuspendedAssertions())
    , m_shouldUseServiceWorkerShortTimeout(page->settings().shouldUseServiceWorkerShortTimeout())
    , m_showDebugBorders(page->settings().showDebugBorders())
    , m_showMediaStatsContextMenuItemEnabled(page->settings().showMediaStatsContextMenuItemEnabled())
    , m_showModalDialogEnabled(page->settings().showModalDialogEnabled())
    , m_showRepaintCounter(page->settings().showRepaintCounter())
    , m_showTiledScrollingIndicator(page->settings().showTiledScrollingIndicator())
    , m_showsToolTipOverTruncatedText(page->settings().showsToolTipOverTruncatedText())
    , m_showsURLsInToolTips(page->settings().showsURLsInToolTips())
    , m_shrinksStandaloneImagesToFit(page->settings().shrinksStandaloneImagesToFit())
    , m_siteIsolationEnabled(page->settings().siteIsolationEnabled())
    , m_smartInsertDeleteEnabled(page->settings().smartInsertDeleteEnabled())
#if ENABLE(MEDIA_SOURCE)
    , m_sourceBufferChangeTypeEnabled(page->settings().sourceBufferChangeTypeEnabled())
#endif
    , m_spatialNavigationEnabled(page->settings().spatialNavigationEnabled())
#if ENABLE(MEDIA_STREAM)
    , m_speakerSelectionRequiresUserGesture(page->settings().speakerSelectionRequiresUserGesture())
#endif
    , m_speechRecognitionEnabled(page->settings().speechRecognitionEnabled())
    , m_speechSynthesisAPIEnabled(page->settings().speechSynthesisAPIEnabled())
    , m_springTimingFunctionEnabled(page->settings().springTimingFunctionEnabled())
    , m_standalone(page->settings().standalone())
    , m_standardFontFamily(page->settings().standardFontFamily())
    , m_storageAPIEnabled(page->settings().storageAPIEnabled())
    , m_storageAPIEstimateEnabled(page->settings().storageAPIEstimateEnabled())
    , m_storageAccessAPIEnabled(page->settings().storageAccessAPIEnabled())
    , m_storageAccessAPIPerPageScopeEnabled(page->settings().storageAccessAPIPerPageScopeEnabled())
    , m_subgridEnabled(page->settings().subgridEnabled())
    , m_suppressesIncrementalRendering(page->settings().suppressesIncrementalRendering())
    , m_syntheticEditingCommandsEnabled(page->settings().syntheticEditingCommandsEnabled())
#if USE(SYSTEM_PREVIEW)
    , m_systemPreviewEnabled(page->settings().systemPreviewEnabled())
#endif
    , m_telephoneNumberParsingEnabled(page->settings().telephoneNumberParsingEnabled())
    , m_temporaryTileCohortRetentionEnabled(page->settings().temporaryTileCohortRetentionEnabled())
    , m_textAreasAreResizable(page->settings().textAreasAreResizable())
#if ENABLE(TEXT_AUTOSIZING)
    , m_textAutosizingEnabled(page->settings().textAutosizingEnabled())
#endif
#if ENABLE(TEXT_AUTOSIZING)
    , m_textAutosizingUsesIdempotentMode(page->settings().textAutosizingUsesIdempotentMode())
#endif
#if ENABLE(TEXT_AUTOSIZING)
    , m_textAutosizingWindowSizeOverrideHeight(page->settings().textAutosizingWindowSizeOverrideHeight())
#endif
#if ENABLE(TEXT_AUTOSIZING)
    , m_textAutosizingWindowSizeOverrideWidth(page->settings().textAutosizingWindowSizeOverrideWidth())
#endif
    , m_textInteractionEnabled(page->settings().textInteractionEnabled())
#if ENABLE(IMAGE_ANALYSIS)
    , m_textRecognitionInVideosEnabled(page->settings().textRecognitionInVideosEnabled())
#endif
    , m_thirdPartyIframeRedirectBlockingEnabled(page->settings().thirdPartyIframeRedirectBlockingEnabled())
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
    , m_threadedAnimationResolutionEnabled(page->settings().threadedAnimationResolutionEnabled())
#endif
#if ENABLE(TOUCH_EVENTS)
    , m_touchEventEmulationEnabled(page->settings().isTouchEventEmulationEnabled())
#endif
#if ENABLE(TOUCH_EVENTS)
    , m_touchEventsEnabled(page->settings().touchEventsEnabled())
#endif
    , m_trackConfigurationEnabled(page->settings().trackConfigurationEnabled())
    , m_transformStreamAPIEnabled(page->settings().transformStreamAPIEnabled())
    , m_treatIPAddressAsDomain(page->settings().treatIPAddressAsDomain())
    , m_treatsAnyTextCSSLinkAsStylesheet(page->settings().treatsAnyTextCSSLinkAsStylesheet())
    , m_undoManagerAPIEnabled(page->settings().undoManagerAPIEnabled())
    , m_unhandledPromiseRejectionToConsoleEnabled(page->settings().unhandledPromiseRejectionToConsoleEnabled())
    , m_unifiedTextCheckerEnabled(page->settings().unifiedTextCheckerEnabled())
    , m_unprefixedFullscreenAPIEnabled(page->settings().unprefixedFullscreenAPIEnabled())
    , m_useAnonymousModeWhenFetchingMaskImages(page->settings().useAnonymousModeWhenFetchingMaskImages())
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
    , m_useGPUProcessForWebGLEnabled(page->settings().useGPUProcessForWebGLEnabled())
#endif
    , m_useGiantTiles(page->settings().useGiantTiles())
    , m_useImageDocumentForSubframePDF(page->settings().useImageDocumentForSubframePDF())
    , m_useLegacyBackgroundSizeShorthandBehavior(page->settings().useLegacyBackgroundSizeShorthandBehavior())
    , m_usePreHTML5ParserQuirks(page->settings().usePreHTML5ParserQuirks())
#if HAVE(SC_CONTENT_SHARING_PICKER)
    , m_useSCContentSharingPicker(page->settings().useSCContentSharingPicker())
#endif
    , m_userActivationAPIEnabled(page->settings().userActivationAPIEnabled())
    , m_userGesturePromisePropagationEnabled(page->settings().userGesturePromisePropagationEnabled())
    , m_usesEncodingDetector(page->settings().usesEncodingDetector())
    , m_validationMessageTimerMagnification(page->settings().validationMessageTimerMagnification())
    , m_verifyWindowOpenUserGestureFromUIProcess(page->settings().verifyWindowOpenUserGestureFromUIProcess())
    , m_verticalFormControlsEnabled(page->settings().verticalFormControlsEnabled())
#if PLATFORM(IOS_FAMILY)
    , m_videoFullscreenRequiresElementFullscreen(page->settings().videoFullscreenRequiresElementFullscreen())
#endif
    , m_videoPresentationModeAPIEnabled(page->settings().videoPresentationModeAPIEnabled())
#if ENABLE(VIDEO)
    , m_videoQualityIncludesDisplayCompositingEnabled(page->settings().videoQualityIncludesDisplayCompositingEnabled())
#endif
    , m_visibleDebugOverlayRegions(page->settings().visibleDebugOverlayRegions())
#if ENABLE(IMAGE_ANALYSIS)
    , m_visualTranslationEnabled(page->settings().visualTranslationEnabled())
#endif
    , m_visualViewportAPIEnabled(page->settings().visualViewportAPIEnabled())
    , m_visualViewportEnabled(page->settings().visualViewportEnabled())
#if ENABLE(VP9)
    , m_vp9DecoderEnabled(page->settings().vp9DecoderEnabled())
#endif
    , m_wantsBalancedSetDefersLoadingBehavior(page->settings().wantsBalancedSetDefersLoadingBehavior())
    , m_webAPIStatisticsEnabled(page->settings().webAPIStatisticsEnabled())
    , m_webAPIsInShadowRealmEnabled(page->settings().webAPIsInShadowRealmEnabled())
    , m_webAnimationsCompositeOperationsEnabled(page->settings().webAnimationsCompositeOperationsEnabled())
    , m_webAnimationsCustomEffectsEnabled(page->settings().webAnimationsCustomEffectsEnabled())
    , m_webAnimationsCustomFrameRateEnabled(page->settings().webAnimationsCustomFrameRateEnabled())
    , m_webAnimationsIterationCompositeEnabled(page->settings().webAnimationsIterationCompositeEnabled())
    , m_webAnimationsMutableTimelinesEnabled(page->settings().webAnimationsMutableTimelinesEnabled())
#if ENABLE(WEB_ARCHIVE)
    , m_webArchiveDebugModeEnabled(page->settings().webArchiveDebugModeEnabled())
#endif
#if ENABLE(WEB_ARCHIVE)
    , m_webArchiveTestingModeEnabled(page->settings().webArchiveTestingModeEnabled())
#endif
#if ENABLE(WEBASSEMBLY)
    , m_webAssemblyESMIntegrationEnabled(page->settings().webAssemblyESMIntegrationEnabled())
#endif
#if ENABLE(WEB_AUDIO)
    , m_webAudioEnabled(page->settings().webAudioEnabled())
#endif
#if ENABLE(WEB_AUTHN)
    , m_webAuthenticationEnabled(page->settings().webAuthenticationEnabled())
#endif
#if ENABLE(WEB_CODECS)
    , m_webCodecsAV1Enabled(page->settings().webCodecsAV1Enabled())
#endif
#if ENABLE(WEB_CODECS)
    , m_webCodecsEnabled(page->settings().webCodecsEnabled())
#endif
#if ENABLE(WEB_CODECS)
    , m_webCodecsHEVCEnabled(page->settings().webCodecsHEVCEnabled())
#endif
    , m_webCryptoSafeCurvesEnabled(page->settings().webCryptoSafeCurvesEnabled())
    , m_webGLDraftExtensionsEnabled(page->settings().webGLDraftExtensionsEnabled())
    , m_webGLEnabled(page->settings().webGLEnabled())
    , m_webGLErrorsToConsoleEnabled(page->settings().webGLErrorsToConsoleEnabled())
    , m_webGLTimerQueriesEnabled(page->settings().webGLTimerQueriesEnabled())
#if ENABLE(WEBGL) && PLATFORM(COCOA)
    , m_webGLUsingMetal(page->settings().webGLUsingMetal())
#endif
    , m_webGPUEnabled(page->settings().webGPUEnabled())
    , m_webInspectorEngineeringSettingsAllowed(page->settings().webInspectorEngineeringSettingsAllowed())
    , m_webLocksAPIEnabled(page->settings().webLocksAPIEnabled())
#if ENABLE(WEB_RTC)
    , m_webRTCAV1CodecEnabled(page->settings().webRTCAV1CodecEnabled())
#endif
#if ENABLE(WEB_RTC)
    , m_webRTCDTMFEnabled(page->settings().webRTCDTMFEnabled())
#endif
#if ENABLE(WEB_RTC)
    , m_webRTCEncodedTransformEnabled(page->settings().webRTCEncodedTransformEnabled())
#endif
    , m_webRTCEncryptionEnabled(page->settings().webRTCEncryptionEnabled())
#if ENABLE(WEB_RTC)
    , m_webRTCH265CodecEnabled(page->settings().webRTCH265CodecEnabled())
#endif
#if USE(LIBWEBRTC)
    , m_webRTCMediaPipelineAdditionalLoggingEnabled(page->settings().webRTCMediaPipelineAdditionalLoggingEnabled())
#endif
#if ENABLE(WEB_RTC)
    , m_webRTCPlatformCodecsInGPUProcessEnabled(page->settings().webRTCPlatformCodecsInGPUProcessEnabled())
#endif
#if ENABLE(WEB_RTC)
    , m_webRTCRemoteVideoFrameEnabled(page->settings().webRTCRemoteVideoFrameEnabled())
#endif
#if ENABLE(WEB_RTC)
    , m_webRTCSFrameTransformEnabled(page->settings().webRTCSFrameTransformEnabled())
#endif
#if ENABLE(WEB_RTC)
    , m_webRTCSocketsProxyingEnabled(page->settings().webRTCSocketsProxyingEnabled())
#endif
#if ENABLE(WEB_RTC)
    , m_webRTCVP9Profile0CodecEnabled(page->settings().webRTCVP9Profile0CodecEnabled())
#endif
#if ENABLE(WEB_RTC)
    , m_webRTCVP9Profile2CodecEnabled(page->settings().webRTCVP9Profile2CodecEnabled())
#endif
    , m_webSecurityEnabled(page->settings().webSecurityEnabled())
    , m_webShareEnabled(page->settings().webShareEnabled())
    , m_webShareFileAPIEnabled(page->settings().webShareFileAPIEnabled())
    , m_webSocketEnabled(page->settings().webSocketEnabled())
#if ENABLE(WEBXR)
    , m_webXRAugmentedRealityModuleEnabled(page->settings().webXRAugmentedRealityModuleEnabled())
#endif
#if ENABLE(WEBXR)
    , m_webXREnabled(page->settings().webXREnabled())
#endif
#if ENABLE(WEBXR)
    , m_webXRGamepadsModuleEnabled(page->settings().webXRGamepadsModuleEnabled())
#endif
#if ENABLE(WEBXR_HANDS)
    , m_webXRHandInputModuleEnabled(page->settings().webXRHandInputModuleEnabled())
#endif
    , m_webkitImageReadyEventEnabled(page->settings().webkitImageReadyEventEnabled())
    , m_wheelEventGesturesBecomeNonBlocking(page->settings().wheelEventGesturesBecomeNonBlocking())
    , m_windowFocusRestricted(page->settings().windowFocusRestricted())
    , m_wirelessPlaybackTargetAPIEnabled(page->settings().wirelessPlaybackTargetAPIEnabled())
    , m_youTubeFlashPluginReplacementEnabled(page->settings().youTubeFlashPluginReplacementEnabled())
{
}

InternalSettingsGenerated::~InternalSettingsGenerated()
{
}

void InternalSettingsGenerated::resetToConsistentState()
{
    m_page->settings().setCSSOMViewScrollingAPIEnabled(m_CSSOMViewScrollingAPIEnabled);
    m_page->settings().setCSSOMViewSmoothScrollingEnabled(m_CSSOMViewSmoothScrollingEnabled);
    m_page->settings().setAbortSignalAnyOperationEnabled(m_abortSignalAnyOperationEnabled);
    m_page->settings().setAcceleratedCompositedAnimationsEnabled(m_acceleratedCompositedAnimationsEnabled);
    m_page->settings().setAcceleratedCompositingEnabled(m_acceleratedCompositingEnabled);
    m_page->settings().setAcceleratedCompositingForFixedPositionEnabled(m_acceleratedCompositingForFixedPositionEnabled);
    m_page->settings().setAcceleratedDrawingEnabled(m_acceleratedDrawingEnabled);
#if USE(CORE_IMAGE)
    m_page->settings().setAcceleratedFiltersEnabled(m_acceleratedFiltersEnabled);
#endif
    m_page->settings().setAccentColorEnabled(m_accentColorEnabled);
    m_page->settings().setAccessHandleEnabled(m_accessHandleEnabled);
    m_page->settings().setAggressiveTileRetentionEnabled(m_aggressiveTileRetentionEnabled);
    m_page->settings().setAllowAnimationControlsOverride(m_allowAnimationControlsOverride);
    m_page->settings().setAllowContentSecurityPolicySourceStarToMatchAnyProtocol(m_allowContentSecurityPolicySourceStarToMatchAnyProtocol);
    m_page->settings().setAllowCrossOriginSubresourcesToAskForCredentials(m_allowCrossOriginSubresourcesToAskForCredentials);
    m_page->settings().setAllowDisplayOfInsecureContent(m_allowDisplayOfInsecureContent);
    m_page->settings().setAllowFileAccessFromFileURLs(m_allowFileAccessFromFileURLs);
    m_page->settings().setAllowMediaContentTypesRequiringHardwareSupportAsFallback(m_allowMediaContentTypesRequiringHardwareSupportAsFallback);
    m_page->settings().setAllowMultiElementImplicitSubmission(m_allowMultiElementImplicitSubmission);
    m_page->settings().setAllowRunningOfInsecureContent(m_allowRunningOfInsecureContent);
    m_page->settings().setAllowSettingAnyXHRHeaderFromFileURLs(m_allowSettingAnyXHRHeaderFromFileURLs);
    m_page->settings().setAllowTopNavigationToDataURLs(m_allowTopNavigationToDataURLs);
    m_page->settings().setAllowUniversalAccessFromFileURLs(m_allowUniversalAccessFromFileURLs);
#if PLATFORM(IOS_FAMILY)
    m_page->settings().setAllowViewportShrinkToFitContent(m_allowViewportShrinkToFitContent);
#endif
#if ENABLE(WEBGL)
    m_page->settings().setAllowWebGLInWorkers(m_allowWebGLInWorkers);
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    m_page->settings().setAllowsAirPlayForMediaPlayback(m_allowsAirPlayForMediaPlayback);
#endif
    m_page->settings().setAllowsInlineMediaPlayback(m_allowsInlineMediaPlayback);
    m_page->settings().setAllowsInlineMediaPlaybackAfterFullscreen(m_allowsInlineMediaPlaybackAfterFullscreen);
    m_page->settings().setAllowsPictureInPictureMediaPlayback(m_allowsPictureInPictureMediaPlayback);
#if PLATFORM(IOS_FAMILY)
    m_page->settings().setAlternateFormControlDesignEnabled(m_alternateFormControlDesignEnabled);
#endif
#if PLATFORM(IOS_FAMILY)
    m_page->settings().setAlternateFullScreenControlDesignEnabled(m_alternateFullScreenControlDesignEnabled);
#endif
#if ENABLE(ALTERNATE_WEBM_PLAYER)
    m_page->settings().setAlternateWebMPlayerEnabled(m_alternateWebMPlayerEnabled);
#endif
    m_page->settings().setAnimatedImageAsyncDecodingEnabled(m_animatedImageAsyncDecodingEnabled);
    m_page->settings().setAnimatedImageDebugCanvasDrawingEnabled(m_animatedImageDebugCanvasDrawingEnabled);
#if ENABLE(BADGING)
    m_page->settings().setAppBadgeEnabled(m_appBadgeEnabled);
#endif
#if ENABLE(APP_HIGHLIGHTS)
    m_page->settings().setAppHighlightsEnabled(m_appHighlightsEnabled);
#endif
    m_page->settings().setAppleMailPaginationQuirkEnabled(m_appleMailPaginationQuirkEnabled);
#if ENABLE(APPLE_PAY)
    m_page->settings().setApplePayCapabilityDisclosureAllowed(m_applePayCapabilityDisclosureAllowed);
#endif
#if ENABLE(APPLE_PAY)
    m_page->settings().setApplePayEnabled(m_applePayEnabled);
#endif
    m_page->settings().setAriaReflectionForElementReferencesEnabled(m_ariaReflectionForElementReferencesEnabled);
    m_page->settings().setAspectRatioEnabled(m_aspectRatioEnabled);
    m_page->settings().setAspectRatioOfImgFromWidthAndHeightEnabled(m_aspectRatioOfImgFromWidthAndHeightEnabled);
    m_page->settings().setAsyncClipboardAPIEnabled(m_asyncClipboardAPIEnabled);
    m_page->settings().setAsyncFrameScrollingEnabled(m_asyncFrameScrollingEnabled);
    m_page->settings().setAsyncOverflowScrollingEnabled(m_asyncOverflowScrollingEnabled);
    m_page->settings().setAsynchronousSpellCheckingEnabled(m_asynchronousSpellCheckingEnabled);
#if ENABLE(ATTACHMENT_ELEMENT)
    m_page->settings().setAttachmentWideLayoutEnabled(m_attachmentWideLayoutEnabled);
#endif
    m_page->settings().setAudioControlsScaleWithPageZoom(m_audioControlsScaleWithPageZoom);
#if ENABLE(VIDEO)
    m_page->settings().setAudioDescriptionsEnabled(m_audioDescriptionsEnabled);
#endif
    m_page->settings().setAuthorAndUserStylesEnabled(m_authorAndUserStylesEnabled);
    m_page->settings().setAutoscrollForDragAndDropEnabled(m_autoscrollForDragAndDropEnabled);
#if ENABLE(SERVICE_WORKER)
    m_page->settings().setBackgroundFetchAPIEnabled(m_backgroundFetchAPIEnabled);
#endif
    m_page->settings().setBackgroundShouldExtendBeyondPage(m_backgroundShouldExtendBeyondPage);
#if PLATFORM(MAC) && USE(RUNNINGBOARD)
    m_page->settings().setBackgroundWebContentRunningBoardThrottlingEnabled(m_backgroundWebContentRunningBoardThrottlingEnabled);
#endif
    m_page->settings().setBackspaceKeyNavigationEnabled(m_backspaceKeyNavigationEnabled);
    m_page->settings().setBeaconAPIEnabled(m_beaconAPIEnabled);
#if ENABLE(GPU_PROCESS)
    m_page->settings().setBlockMediaLayerRehostingInWebContentProcess(m_blockMediaLayerRehostingInWebContentProcess);
#endif
    m_page->settings().setBroadcastChannelEnabled(m_broadcastChannelEnabled);
    m_page->settings().setBroadcastChannelOriginPartitioningEnabled(m_broadcastChannelOriginPartitioningEnabled);
    m_page->settings().setCacheAPIEnabled(m_cacheAPIEnabled);
    m_page->settings().setCanvasColorSpaceEnabled(m_canvasColorSpaceEnabled);
    m_page->settings().setCanvasFiltersEnabled(m_canvasFiltersEnabled);
    m_page->settings().setCanvasFingerprintingQuirkEnabled(m_canvasFingerprintingQuirkEnabled);
    m_page->settings().setCanvasUsesAcceleratedDrawing(m_canvasUsesAcceleratedDrawing);
    m_page->settings().setCaretBrowsingEnabled(m_caretBrowsingEnabled);
    m_page->settings().setClearSiteDataHTTPHeaderEnabled(m_clearSiteDataHTTPHeaderEnabled);
#if ENABLE(BADGING)
    m_page->settings().setClientBadgeEnabled(m_clientBadgeEnabled);
#endif
    m_page->settings().setClientCoordinatesRelativeToLayoutViewport(m_clientCoordinatesRelativeToLayoutViewport);
    m_page->settings().setColorFilterEnabled(m_colorFilterEnabled);
    m_page->settings().setCompressionStreamEnabled(m_compressionStreamEnabled);
    m_page->settings().setConstantPropertiesEnabled(m_constantPropertiesEnabled);
    m_page->settings().setConstructableStylesheetsEnabled(m_constructableStylesheetsEnabled);
    m_page->settings().setContactPickerAPIEnabled(m_contactPickerAPIEnabled);
#if ENABLE(CONTENT_CHANGE_OBSERVER)
    m_page->settings().setContentChangeObserverEnabled(m_contentChangeObserverEnabled);
#endif
    m_page->settings().setContentDispositionAttachmentSandboxEnabled(m_contentDispositionAttachmentSandboxEnabled);
#if ENABLE(CONTEXT_MENU_QR_CODE_DETECTION)
    m_page->settings().setContextMenuQRCodeDetectionEnabled(m_contextMenuQRCodeDetectionEnabled);
#endif
    m_page->settings().setCookieConsentAPIEnabled(m_cookieConsentAPIEnabled);
    m_page->settings().setCookieEnabled(m_cookieEnabled);
    m_page->settings().setCookieStoreAPIEnabled(m_cookieStoreAPIEnabled);
    m_page->settings().setCookieStoreAPIExtendedAttributesEnabled(m_cookieStoreAPIExtendedAttributesEnabled);
    m_page->settings().setCoreMathMLEnabled(m_coreMathMLEnabled);
    m_page->settings().setCrossOriginCheckInGetMatchedCSSRulesDisabled(m_crossOriginCheckInGetMatchedCSSRulesDisabled);
    m_page->settings().setCrossOriginEmbedderPolicyEnabled(m_crossOriginEmbedderPolicyEnabled);
    m_page->settings().setCrossOriginOpenerPolicyEnabled(m_crossOriginOpenerPolicyEnabled);
    m_page->settings().setCSS3DTransformInteroperabilityEnabled(m_css3DTransformInteroperabilityEnabled);
    m_page->settings().setCSSCascadeLayersEnabled(m_cssCascadeLayersEnabled);
    m_page->settings().setCSSColor4(m_cssColor4);
    m_page->settings().setCSSColorContrastEnabled(m_cssColorContrastEnabled);
    m_page->settings().setCSSColorMixEnabled(m_cssColorMixEnabled);
    m_page->settings().setCSSContainIntrinsicSizeEnabled(m_cssContainIntrinsicSizeEnabled);
    m_page->settings().setCSSContainerQueriesEnabled(m_cssContainerQueriesEnabled);
    m_page->settings().setCSSContainmentEnabled(m_cssContainmentEnabled);
    m_page->settings().setCSSContentVisibilityEnabled(m_cssContentVisibilityEnabled);
    m_page->settings().setCSSCounterStyleAtRuleImageSymbolsEnabled(m_cssCounterStyleAtRuleImageSymbolsEnabled);
    m_page->settings().setCSSCounterStyleAtRulesEnabled(m_cssCounterStyleAtRulesEnabled);
    m_page->settings().setCSSCustomPropertiesAndValuesEnabled(m_cssCustomPropertiesAndValuesEnabled);
    m_page->settings().setCSSFontFaceSizeAdjustEnabled(m_cssFontFaceSizeAdjustEnabled);
    m_page->settings().setCSSGradientInterpolationColorSpacesEnabled(m_cssGradientInterpolationColorSpacesEnabled);
    m_page->settings().setCSSGradientPremultipliedAlphaInterpolationEnabled(m_cssGradientPremultipliedAlphaInterpolationEnabled);
    m_page->settings().setCSSIndividualTransformPropertiesEnabled(m_cssIndividualTransformPropertiesEnabled);
    m_page->settings().setCSSInputSecurityEnabled(m_cssInputSecurityEnabled);
    m_page->settings().setCSSMarginTrimEnabled(m_cssMarginTrimEnabled);
    m_page->settings().setCSSMotionPathEnabled(m_cssMotionPathEnabled);
    m_page->settings().setCSSNestingEnabled(m_cssNestingEnabled);
#if ENABLE(CSS_PAINTING_API)
    m_page->settings().setCSSPaintingAPIEnabled(m_cssPaintingAPIEnabled);
#endif
    m_page->settings().setCSSRelativeColorSyntaxEnabled(m_cssRelativeColorSyntaxEnabled);
    m_page->settings().setCSSRhythmicSizingEnabled(m_cssRhythmicSizingEnabled);
    m_page->settings().setCSSScrollAnchoringEnabled(m_cssScrollAnchoringEnabled);
    m_page->settings().setCSSScrollbarColorEnabled(m_cssScrollbarColorEnabled);
    m_page->settings().setCSSScrollbarGutterEnabled(m_cssScrollbarGutterEnabled);
    m_page->settings().setCSSScrollbarWidthEnabled(m_cssScrollbarWidthEnabled);
    m_page->settings().setCSSTextAlignLastEnabled(m_cssTextAlignLastEnabled);
    m_page->settings().setCSSTextBoxTrimEnabled(m_cssTextBoxTrimEnabled);
    m_page->settings().setCSSTextGroupAlignEnabled(m_cssTextGroupAlignEnabled);
    m_page->settings().setCSSTextJustifyEnabled(m_cssTextJustifyEnabled);
    m_page->settings().setCSSTextSpacingEnabled(m_cssTextSpacingEnabled);
    m_page->settings().setCSSTextUnderlinePositionLeftRightEnabled(m_cssTextUnderlinePositionLeftRightEnabled);
    m_page->settings().setCSSTextWrapNewValuesEnabled(m_cssTextWrapNewValuesEnabled);
#if ENABLE(CSS_TRANSFORM_STYLE_OPTIMIZED_3D)
    m_page->settings().setCSSTransformStyleOptimized3DEnabled(m_cssTransformStyleOptimized3DEnabled);
#endif
    m_page->settings().setCSSTypedOMColorEnabled(m_cssTypedOMColorEnabled);
    m_page->settings().setCSSTypedOMEnabled(m_cssTypedOMEnabled);
    m_page->settings().setCSSWhiteSpaceLonghandsEnabled(m_cssWhiteSpaceLonghandsEnabled);
    m_page->settings().setCSSWordBreakAutoEnabled(m_cssWordBreakAutoEnabled);
    m_page->settings().setCursiveFontFamily(m_cursiveFontFamily);
#if ENABLE(DATALIST_ELEMENT)
    m_page->settings().setDataListElementEnabled(m_dataListElementEnabled);
#endif
    m_page->settings().setDataTransferItemsEnabled(m_dataTransferItemsEnabled);
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    m_page->settings().setDateTimeInputsEditableComponentsEnabled(m_dateTimeInputsEditableComponentsEnabled);
#endif
    m_page->settings().setDeclarativeShadowDOMEnabled(m_declarativeShadowDOMEnabled);
    m_page->settings().setDeclarativeShadowDOMInDOMParserEnabled(m_declarativeShadowDOMInDOMParserEnabled);
    m_page->settings().setDefaultARIAForCustomElementsEnabled(m_defaultARIAForCustomElementsEnabled);
    m_page->settings().setDefaultFixedFontSize(m_defaultFixedFontSize);
    m_page->settings().setDefaultFontSize(m_defaultFontSize);
    m_page->settings().setDefaultTextEncodingName(m_defaultTextEncodingName);
    m_page->settings().setDefaultVideoPosterURL(m_defaultVideoPosterURL);
    m_page->settings().setDeprecateRSAESPKCSWebCryptoEnabled(m_deprecateRSAESPKCSWebCryptoEnabled);
    m_page->settings().setDeprecationReportingEnabled(m_deprecationReportingEnabled);
    m_page->settings().setDeveloperExtrasEnabled(m_developerExtrasEnabled);
    m_page->settings().setDeviceHeight(m_deviceHeight);
#if ENABLE(DEVICE_ORIENTATION)
    m_page->settings().setDeviceOrientationEventEnabled(m_deviceOrientationEventEnabled);
#endif
#if ENABLE(DEVICE_ORIENTATION)
    m_page->settings().setDeviceOrientationPermissionAPIEnabled(m_deviceOrientationPermissionAPIEnabled);
#endif
    m_page->settings().setDeviceWidth(m_deviceWidth);
    m_page->settings().setDiagnosticLoggingEnabled(m_diagnosticLoggingEnabled);
    m_page->settings().setDialogElementEnabled(m_dialogElementEnabled);
    m_page->settings().setDirPseudoEnabled(m_dirPseudoEnabled);
    m_page->settings().setDirectoryUploadEnabled(m_directoryUploadEnabled);
    m_page->settings().setDisabledAdaptationsMetaTagEnabled(m_disabledAdaptationsMetaTagEnabled);
    m_page->settings().setDisallowSyncXHRDuringPageDismissalEnabled(m_disallowSyncXHRDuringPageDismissalEnabled);
    m_page->settings().setDisplayListDrawingEnabled(m_displayListDrawingEnabled);
    m_page->settings().setDNSPrefetchingEnabled(m_dnsPrefetchingEnabled);
#if ENABLE(DOM_AUDIO_SESSION)
    m_page->settings().setDOMAudioSessionEnabled(m_domAudioSessionEnabled);
#endif
#if ENABLE(DOM_AUDIO_SESSION)
    m_page->settings().setDOMAudioSessionFullEnabled(m_domAudioSessionFullEnabled);
#endif
    m_page->settings().setDOMPasteAccessRequestsEnabled(m_domPasteAccessRequestsEnabled);
    m_page->settings().setDOMPasteAllowed(m_domPasteAllowed);
    m_page->settings().setDOMTestingAPIsEnabled(m_domTestingAPIsEnabled);
    m_page->settings().setDOMTimersThrottlingEnabled(m_domTimersThrottlingEnabled);
#if ENABLE(DOWNLOAD_ATTRIBUTE)
    m_page->settings().setDownloadAttributeEnabled(m_downloadAttributeEnabled);
#endif
    m_page->settings().setEmbedElementEnabled(m_embedElementEnabled);
    m_page->settings().setEnableInheritURIQueryComponent(m_enableInheritURIQueryComponent);
#if ENABLE(ENCRYPTED_MEDIA)
    m_page->settings().setEncryptedMediaAPIEnabled(m_encryptedMediaAPIEnabled);
#endif
    m_page->settings().setEnterKeyHintEnabled(m_enterKeyHintEnabled);
    m_page->settings().setEventHandlerDrivenSmoothKeyboardScrollingEnabled(m_eventHandlerDrivenSmoothKeyboardScrollingEnabled);
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setExposeSpeakersEnabled(m_exposeSpeakersEnabled);
#endif
#if ENABLE(VIDEO)
    m_page->settings().setExtendedAudioDescriptionsEnabled(m_extendedAudioDescriptionsEnabled);
#endif
    m_page->settings().setFantasyFontFamily(m_fantasyFontFamily);
    m_page->settings().setFetchAPIEnabled(m_fetchAPIEnabled);
    m_page->settings().setFetchMetadataEnabled(m_fetchMetadataEnabled);
    m_page->settings().setFetchPriorityEnabled(m_fetchPriorityEnabled);
    m_page->settings().setFileReaderAPIEnabled(m_fileReaderAPIEnabled);
    m_page->settings().setFileSystemAccessEnabled(m_fileSystemAccessEnabled);
    m_page->settings().setFixedBackgroundsPaintRelativeToDocument(m_fixedBackgroundsPaintRelativeToDocument);
    m_page->settings().setFixedElementsLayoutRelativeToFrame(m_fixedElementsLayoutRelativeToFrame);
    m_page->settings().setFixedFontFamily(m_fixedFontFamily);
    m_page->settings().setFlexFormattingContextIntegrationEnabled(m_flexFormattingContextIntegrationEnabled);
    m_page->settings().setFocusVisibleEnabled(m_focusVisibleEnabled);
    m_page->settings().setFontFallbackPrefersPictographs(m_fontFallbackPrefersPictographs);
    m_page->settings().setForceCompositingMode(m_forceCompositingMode);
    m_page->settings().setForceFTPDirectoryListings(m_forceFTPDirectoryListings);
    m_page->settings().setForceWebGLUsesLowPower(m_forceWebGLUsesLowPower);
    m_page->settings().setFormAssociatedCustomElementsEnabled(m_formAssociatedCustomElementsEnabled);
    m_page->settings().setFTPDirectoryTemplatePath(m_ftpDirectoryTemplatePath);
    m_page->settings().setFTPEnabled(m_ftpEnabled);
#if ENABLE(FULLSCREEN_API)
    m_page->settings().setFullScreenEnabled(m_fullScreenEnabled);
#endif
    m_page->settings().setFullscreenRequirementForScreenOrientationLockingEnabled(m_fullscreenRequirementForScreenOrientationLockingEnabled);
#if PLATFORM(VISION)
    m_page->settings().setFullscreenSceneAspectRatioLockingEnabled(m_fullscreenSceneAspectRatioLockingEnabled);
#endif
#if PLATFORM(VISION)
    m_page->settings().setFullscreenSceneDimmingEnabled(m_fullscreenSceneDimmingEnabled);
#endif
#if ENABLE(GAMEPAD)
    m_page->settings().setGamepadTriggerRumbleEnabled(m_gamepadTriggerRumbleEnabled);
#endif
#if ENABLE(GAMEPAD)
    m_page->settings().setGamepadVibrationActuatorEnabled(m_gamepadVibrationActuatorEnabled);
#endif
#if ENABLE(GAMEPAD)
    m_page->settings().setGamepadsEnabled(m_gamepadsEnabled);
#endif
#if ENABLE(VIDEO)
    m_page->settings().setGenericCueAPIEnabled(m_genericCueAPIEnabled);
#endif
    m_page->settings().setGeolocationFloorLevelEnabled(m_geolocationFloorLevelEnabled);
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setGetUserMediaRequiresFocus(m_getUserMediaRequiresFocus);
#endif
    m_page->settings().setGoogleAntiFlickerOptimizationQuirkEnabled(m_googleAntiFlickerOptimizationQuirkEnabled);
#if USE(GRAPHICS_CONTEXT_FILTERS)
    m_page->settings().setGraphicsContextFiltersEnabled(m_graphicsContextFiltersEnabled);
#endif
    m_page->settings().setHasPseudoClassEnabled(m_hasPseudoClassEnabled);
    m_page->settings().setHiddenPageCSSAnimationSuspensionEnabled(m_hiddenPageCSSAnimationSuspensionEnabled);
    m_page->settings().setHiddenPageDOMTimerThrottlingAutoIncreases(m_hiddenPageDOMTimerThrottlingAutoIncreases);
    m_page->settings().setHiddenPageDOMTimerThrottlingEnabled(m_hiddenPageDOMTimerThrottlingEnabled);
    m_page->settings().setHttpEquivEnabled(m_httpEquivEnabled);
    m_page->settings().setHyperlinkAuditingEnabled(m_hyperlinkAuditingEnabled);
#if ENABLE(IOS_FORM_CONTROL_REFRESH)
    m_page->settings().setIOSFormControlRefreshEnabled(m_iOSFormControlRefreshEnabled);
#endif
    m_page->settings().setICECandidateFilteringEnabled(m_iceCandidateFilteringEnabled);
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setIdempotentModeAutosizingOnlyHonorsPercentages(m_idempotentModeAutosizingOnlyHonorsPercentages);
#endif
#if ENABLE(IMAGE_ANALYSIS)
    m_page->settings().setImageAnalysisDuringFindInPageEnabled(m_imageAnalysisDuringFindInPageEnabled);
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    m_page->settings().setImageAnimationControlEnabled(m_imageAnimationControlEnabled);
#endif
#if ENABLE(SERVICE_CONTROLS)
    m_page->settings().setImageControlsEnabled(m_imageControlsEnabled);
#endif
    m_page->settings().setImageSubsamplingEnabled(m_imageSubsamplingEnabled);
    m_page->settings().setImagesEnabled(m_imagesEnabled);
    m_page->settings().setImperativeSlotAPIEnabled(m_imperativeSlotAPIEnabled);
    m_page->settings().setIncompleteImageBorderEnabled(m_incompleteImageBorderEnabled);
#if HAVE(INCREMENTAL_PDF_APIS)
    m_page->settings().setIncrementalPDFLoadingEnabled(m_incrementalPDFLoadingEnabled);
#endif
    m_page->settings().setIncrementalRenderingSuppressionTimeoutInSeconds(m_incrementalRenderingSuppressionTimeoutInSeconds);
    m_page->settings().setIndexedDBAPIEnabled(m_indexedDBAPIEnabled);
    m_page->settings().setInertAttributeEnabled(m_inertAttributeEnabled);
    m_page->settings().setInlineMediaPlaybackRequiresPlaysInlineAttribute(m_inlineMediaPlaybackRequiresPlaysInlineAttribute);
    m_page->settings().setInlinePredictionsInAllEditableElementsEnabled(m_inlinePredictionsInAllEditableElementsEnabled);
#if ENABLE(INPUT_TYPE_COLOR)
    m_page->settings().setInputTypeColorEnabled(m_inputTypeColorEnabled);
#endif
#if ENABLE(INPUT_TYPE_DATE)
    m_page->settings().setInputTypeDateEnabled(m_inputTypeDateEnabled);
#endif
#if ENABLE(INPUT_TYPE_DATETIMELOCAL)
    m_page->settings().setInputTypeDateTimeLocalEnabled(m_inputTypeDateTimeLocalEnabled);
#endif
#if ENABLE(INPUT_TYPE_MONTH)
    m_page->settings().setInputTypeMonthEnabled(m_inputTypeMonthEnabled);
#endif
#if ENABLE(INPUT_TYPE_TIME)
    m_page->settings().setInputTypeTimeEnabled(m_inputTypeTimeEnabled);
#endif
#if ENABLE(INPUT_TYPE_WEEK)
    m_page->settings().setInputTypeWeekEnabled(m_inputTypeWeekEnabled);
#endif
    m_page->settings().setInteractionRegionInlinePadding(m_interactionRegionInlinePadding);
    m_page->settings().setInteractionRegionMinimumCornerRadius(m_interactionRegionMinimumCornerRadius);
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
    m_page->settings().setInteractionRegionsEnabled(m_interactionRegionsEnabled);
#endif
    m_page->settings().setInteractiveFormValidationEnabled(m_interactiveFormValidationEnabled);
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setInterruptAudioOnPageVisibilityChangeEnabled(m_interruptAudioOnPageVisibilityChangeEnabled);
#endif
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setInterruptVideoOnPageVisibilityChangeEnabled(m_interruptVideoOnPageVisibilityChangeEnabled);
#endif
    m_page->settings().setIntersectionObserverEnabled(m_intersectionObserverEnabled);
    m_page->settings().setInvisibleAutoplayNotPermitted(m_invisibleAutoplayNotPermitted);
    m_page->settings().setIsFirstPartyWebsiteDataRemovalDisabled(m_isFirstPartyWebsiteDataRemovalDisabled);
    m_page->settings().setIsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled(m_isFirstPartyWebsiteDataRemovalLiveOnTestingEnabled);
    m_page->settings().setIsFirstPartyWebsiteDataRemovalReproTestingEnabled(m_isFirstPartyWebsiteDataRemovalReproTestingEnabled);
    m_page->settings().setIsLoggedInAPIEnabled(m_isLoggedInAPIEnabled);
    m_page->settings().setIsPerActivityStateCPUUsageMeasurementEnabled(m_isPerActivityStateCPUUsageMeasurementEnabled);
    m_page->settings().setIsPostBackgroundingCPUUsageMeasurementEnabled(m_isPostBackgroundingCPUUsageMeasurementEnabled);
    m_page->settings().setIsPostBackgroundingMemoryUsageMeasurementEnabled(m_isPostBackgroundingMemoryUsageMeasurementEnabled);
    m_page->settings().setIsPostLoadCPUUsageMeasurementEnabled(m_isPostLoadCPUUsageMeasurementEnabled);
    m_page->settings().setIsPostLoadMemoryUsageMeasurementEnabled(m_isPostLoadMemoryUsageMeasurementEnabled);
    m_page->settings().setIsSameSiteStrictEnforcementEnabled(m_isSameSiteStrictEnforcementEnabled);
    m_page->settings().setIsThirdPartyCookieBlockingDisabled(m_isThirdPartyCookieBlockingDisabled);
    m_page->settings().setItpDebugModeEnabled(m_itpDebugModeEnabled);
    m_page->settings().setJavaScriptCanAccessClipboard(m_javaScriptCanAccessClipboard);
    m_page->settings().setJavaScriptCanOpenWindowsAutomatically(m_javaScriptCanOpenWindowsAutomatically);
    m_page->settings().setLangAttributeAwareFormControlUIEnabled(m_langAttributeAwareFormControlUIEnabled);
    m_page->settings().setLargeImageAsyncDecodingEnabled(m_largeImageAsyncDecodingEnabled);
#if ENABLE(LAYER_BASED_SVG_ENGINE)
    m_page->settings().setLayerBasedSVGEngineEnabled(m_layerBasedSVGEngineEnabled);
#endif
    m_page->settings().setLayoutFallbackWidth(m_layoutFallbackWidth);
    m_page->settings().setLayoutFormattingContextEnabled(m_layoutFormattingContextEnabled);
    m_page->settings().setLayoutViewportHeightExpansionFactor(m_layoutViewportHeightExpansionFactor);
    m_page->settings().setLazyIframeLoadingEnabled(m_lazyIframeLoadingEnabled);
    m_page->settings().setLazyImageLoadingEnabled(m_lazyImageLoadingEnabled);
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    m_page->settings().setLegacyEncryptedMediaAPIEnabled(m_legacyEncryptedMediaAPIEnabled);
#endif
    m_page->settings().setLegacyLineLayoutVisualCoverageEnabled(m_legacyLineLayoutVisualCoverageEnabled);
#if ENABLE(OVERFLOW_SCROLLING_TOUCH)
    m_page->settings().setLegacyOverflowScrollingTouchEnabled(m_legacyOverflowScrollingTouchEnabled);
#endif
    m_page->settings().setLinkModulePreloadEnabled(m_linkModulePreloadEnabled);
    m_page->settings().setLinkPreconnectEarlyHintsEnabled(m_linkPreconnectEarlyHintsEnabled);
    m_page->settings().setLinkPreconnectEnabled(m_linkPreconnectEnabled);
    m_page->settings().setLinkPrefetchEnabled(m_linkPrefetchEnabled);
    m_page->settings().setLinkPreloadEnabled(m_linkPreloadEnabled);
    m_page->settings().setLinkPreloadResponsiveImagesEnabled(m_linkPreloadResponsiveImagesEnabled);
    m_page->settings().setLinkSanitizerEnabled(m_linkSanitizerEnabled);
    m_page->settings().setLiveRangeSelectionEnabled(m_liveRangeSelectionEnabled);
    m_page->settings().setLoadDeferringEnabled(m_loadDeferringEnabled);
    m_page->settings().setLoadsImagesAutomatically(m_loadsImagesAutomatically);
    m_page->settings().setLocalFileContentSniffingEnabled(m_localFileContentSniffingEnabled);
    m_page->settings().setLocalStorageDatabasePath(m_localStorageDatabasePath);
    m_page->settings().setLocalStorageEnabled(m_localStorageEnabled);
    m_page->settings().setLogsPageMessagesToSystemConsoleEnabled(m_logsPageMessagesToSystemConsoleEnabled);
    m_page->settings().setMainContentUserGestureOverrideEnabled(m_mainContentUserGestureOverrideEnabled);
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
    m_page->settings().setManageCaptureStatusBarInGPUProcessEnabled(m_manageCaptureStatusBarInGPUProcessEnabled);
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    m_page->settings().setManagedMediaSourceEnabled(m_managedMediaSourceEnabled);
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    m_page->settings().setManagedMediaSourceHighThreshold(m_managedMediaSourceHighThreshold);
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    m_page->settings().setManagedMediaSourceLowThreshold(m_managedMediaSourceLowThreshold);
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE) && ENABLE(WIRELESS_PLAYBACK_TARGET)
    m_page->settings().setManagedMediaSourceNeedsAirPlay(m_managedMediaSourceNeedsAirPlay);
#endif
#if ENABLE(WEBGL)
    m_page->settings().setMaskWebGLStringsEnabled(m_maskWebGLStringsEnabled);
#endif
    m_page->settings().setMasonryEnabled(m_masonryEnabled);
    m_page->settings().setMasonryTrackAlignmentEnabled(m_masonryTrackAlignmentEnabled);
#if ENABLE(MATHML)
    m_page->settings().setMathMLEnabled(m_mathMLEnabled);
#endif
    m_page->settings().setMaxParseDuration(m_maxParseDuration);
    m_page->settings().setMaximumAccelerated2dCanvasSize(m_maximumAccelerated2dCanvasSize);
    m_page->settings().setMaximumHTMLParserDOMTreeDepth(m_maximumHTMLParserDOMTreeDepth);
#if ENABLE(MEDIA_SOURCE)
    m_page->settings().setMaximumSourceBufferSize(m_maximumSourceBufferSize);
#endif
    m_page->settings().setMediaCapabilitiesEnabled(m_mediaCapabilitiesEnabled);
    m_page->settings().setMediaCapabilitiesExtensionsEnabled(m_mediaCapabilitiesExtensionsEnabled);
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setMediaCaptureRequiresSecureConnection(m_mediaCaptureRequiresSecureConnection);
#endif
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS)
    m_page->settings().setMediaControlsContextMenusEnabled(m_mediaControlsContextMenusEnabled);
#endif
    m_page->settings().setMediaControlsScaleWithPageZoom(m_mediaControlsScaleWithPageZoom);
    m_page->settings().setMediaDataLoadsAutomatically(m_mediaDataLoadsAutomatically);
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setMediaDevicesEnabled(m_mediaDevicesEnabled);
#endif
#if ENABLE(VIDEO)
    m_page->settings().setMediaEnabled(m_mediaEnabled);
#endif
    m_page->settings().setMediaKeysStorageDirectory(m_mediaKeysStorageDirectory);
    m_page->settings().setMediaPreferredFullscreenWidth(m_mediaPreferredFullscreenWidth);
    m_page->settings().setMediaPreloadingEnabled(m_mediaPreloadingEnabled);
#if ENABLE(MEDIA_RECORDER)
    m_page->settings().setMediaRecorderEnabled(m_mediaRecorderEnabled);
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
    m_page->settings().setMediaSessionCoordinatorEnabled(m_mediaSessionCoordinatorEnabled);
#endif
#if ENABLE(MEDIA_SESSION)
    m_page->settings().setMediaSessionEnabled(m_mediaSessionEnabled);
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR) && ENABLE(MEDIA_SESSION_PLAYLIST)
    m_page->settings().setMediaSessionPlaylistEnabled(m_mediaSessionPlaylistEnabled);
#endif
    m_page->settings().setMediaSourceEnabled(m_mediaSourceEnabled);
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setMediaStreamEnabled(m_mediaStreamEnabled);
#endif
    m_page->settings().setMediaTypeOverride(m_mediaTypeOverride);
    m_page->settings().setMediaUserGestureInheritsFromDocument(m_mediaUserGestureInheritsFromDocument);
    m_page->settings().setMenuItemElementEnabled(m_menuItemElementEnabled);
    m_page->settings().setMinimumAccelerated2dCanvasSize(m_minimumAccelerated2dCanvasSize);
    m_page->settings().setMinimumFontSize(m_minimumFontSize);
    m_page->settings().setMinimumLogicalFontSize(m_minimumLogicalFontSize);
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setMinimumZoomFontSize(m_minimumZoomFontSize);
#endif
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setMockCaptureDevicesEnabled(m_mockCaptureDevicesEnabled);
#endif
    m_page->settings().setMockScrollbarsControllerEnabled(m_mockScrollbarsControllerEnabled);
#if ENABLE(MODEL_ELEMENT)
    m_page->settings().setModelElementEnabled(m_modelElementEnabled);
#endif
    m_page->settings().setMomentumScrollingAnimatorEnabled(m_momentumScrollingAnimatorEnabled);
#if ENABLE(TOUCH_EVENTS)
    m_page->settings().setMouseEventsSimulationEnabled(m_mouseEventsSimulationEnabled);
#endif
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setMuteCameraOnMicrophoneInterruptionEnabled(m_muteCameraOnMicrophoneInterruptionEnabled);
#endif
    m_page->settings().setNeedsAdobeFrameReloadingQuirk(m_needsAdobeFrameReloadingQuirk);
    m_page->settings().setNeedsDeferKeyDownAndKeyPressTimersUntilNextEditingCommandQuirk(m_needsDeferKeyDownAndKeyPressTimersUntilNextEditingCommandQuirk);
    m_page->settings().setNeedsFrameNameFallbackToIdQuirk(m_needsFrameNameFallbackToIdQuirk);
    m_page->settings().setNeedsKeyboardEventDisambiguationQuirks(m_needsKeyboardEventDisambiguationQuirks);
    m_page->settings().setNeedsSiteSpecificQuirks(m_needsSiteSpecificQuirks);
    m_page->settings().setNeedsStorageAccessFromFileURLsQuirk(m_needsStorageAccessFromFileURLsQuirk);
#if ENABLE(NOTIFICATION_EVENT)
    m_page->settings().setNotificationEventEnabled(m_notificationEventEnabled);
#endif
#if ENABLE(NOTIFICATIONS)
    m_page->settings().setNotificationsEnabled(m_notificationsEnabled);
#endif
    m_page->settings().setOfflineWebApplicationCacheEnabled(m_offlineWebApplicationCacheEnabled);
#if ENABLE(OFFSCREEN_CANVAS)
    m_page->settings().setOffscreenCanvasEnabled(m_offscreenCanvasEnabled);
#endif
#if ENABLE(OFFSCREEN_CANVAS_IN_WORKERS)
    m_page->settings().setOffscreenCanvasInWorkersEnabled(m_offscreenCanvasInWorkersEnabled);
#endif
    m_page->settings().setOverflowClipEnabled(m_overflowClipEnabled);
    m_page->settings().setOverscrollBehaviorEnabled(m_overscrollBehaviorEnabled);
    m_page->settings().setPageAtRuleSupportEnabled(m_pageAtRuleSupportEnabled);
    m_page->settings().setPassiveTouchListenersAsDefaultOnDocument(m_passiveTouchListenersAsDefaultOnDocument);
    m_page->settings().setPassiveWheelListenersAsDefaultOnDocument(m_passiveWheelListenersAsDefaultOnDocument);
    m_page->settings().setPasswordEchoDurationInSeconds(m_passwordEchoDurationInSeconds);
    m_page->settings().setPasswordEchoEnabled(m_passwordEchoEnabled);
#if ENABLE(PAYMENT_REQUEST)
    m_page->settings().setPaymentRequestEnabled(m_paymentRequestEnabled);
#endif
#if ENABLE(PDFJS)
    m_page->settings().setPdfJSViewerEnabled(m_pdfJSViewerEnabled);
#endif
#if ENABLE(WEB_RTC)
    m_page->settings().setPeerConnectionEnabled(m_peerConnectionEnabled);
#endif
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setPerElementSpeakerSelectionEnabled(m_perElementSpeakerSelectionEnabled);
#endif
    m_page->settings().setPerformanceNavigationTimingAPIEnabled(m_performanceNavigationTimingAPIEnabled);
    m_page->settings().setPerformanceResourceTimingSensitivePropertiesEnabled(m_performanceResourceTimingSensitivePropertiesEnabled);
    m_page->settings().setPermissionsAPIEnabled(m_permissionsAPIEnabled);
    m_page->settings().setPictographFontFamily(m_pictographFontFamily);
#if ENABLE(PICTURE_IN_PICTURE_API)
    m_page->settings().setPictureInPictureAPIEnabled(m_pictureInPictureAPIEnabled);
#endif
    m_page->settings().setPluginsEnabled(m_pluginsEnabled);
    m_page->settings().setPopoverAttributeEnabled(m_popoverAttributeEnabled);
    m_page->settings().setPreferMIMETypeForImages(m_preferMIMETypeForImages);
    m_page->settings().setPreferPageRenderingUpdatesNear60FPSEnabled(m_preferPageRenderingUpdatesNear60FPSEnabled);
#if ENABLE(VIDEO)
    m_page->settings().setPreferSandboxedMediaParsing(m_preferSandboxedMediaParsing);
#endif
    m_page->settings().setPreventKeyboardDOMEventDispatch(m_preventKeyboardDOMEventDispatch);
    m_page->settings().setPrivateClickMeasurementDebugModeEnabled(m_privateClickMeasurementDebugModeEnabled);
    m_page->settings().setPrivateClickMeasurementEnabled(m_privateClickMeasurementEnabled);
    m_page->settings().setPrivateClickMeasurementFraudPreventionEnabled(m_privateClickMeasurementFraudPreventionEnabled);
    m_page->settings().setPunchOutWhiteBackgroundsInDarkMode(m_punchOutWhiteBackgroundsInDarkMode);
#if ENABLE(SERVICE_WORKER)
    m_page->settings().setPushAPIEnabled(m_pushAPIEnabled);
#endif
    m_page->settings().setReferrerPolicyAttributeEnabled(m_referrerPolicyAttributeEnabled);
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    m_page->settings().setRemotePlaybackEnabled(m_remotePlaybackEnabled);
#endif
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    m_page->settings().setRemoveBackgroundEnabled(m_removeBackgroundEnabled);
#endif
    m_page->settings().setReportingEnabled(m_reportingEnabled);
    m_page->settings().setRequestIdleCallbackEnabled(m_requestIdleCallbackEnabled);
    m_page->settings().setRequestSubmitEnabled(m_requestSubmitEnabled);
    m_page->settings().setRequestVideoFrameCallbackEnabled(m_requestVideoFrameCallbackEnabled);
#if HAVE(SC_CONTENT_SHARING_PICKER)
    m_page->settings().setRequireUAGetDisplayMediaPrompt(m_requireUAGetDisplayMediaPrompt);
#endif
    m_page->settings().setRequiresPageVisibilityToPlayAudio(m_requiresPageVisibilityToPlayAudio);
    m_page->settings().setRequiresUserGestureForAudioPlayback(m_requiresUserGestureForAudioPlayback);
    m_page->settings().setRequiresUserGestureForVideoPlayback(m_requiresUserGestureForVideoPlayback);
    m_page->settings().setRequiresUserGestureToLoadVideo(m_requiresUserGestureToLoadVideo);
    m_page->settings().setResizeObserverEnabled(m_resizeObserverEnabled);
    m_page->settings().setResourceLoadSchedulingEnabled(m_resourceLoadSchedulingEnabled);
#if ENABLE(RESOURCE_USAGE)
    m_page->settings().setResourceUsageOverlayVisible(m_resourceUsageOverlayVisible);
#endif
#if HAVE(RUBBER_BANDING)
    m_page->settings().setRubberBandingForSubScrollableRegionsEnabled(m_rubberBandingForSubScrollableRegionsEnabled);
#endif
    m_page->settings().setSKAttributionEnabled(m_sKAttributionEnabled);
#if HAVE(AVCONTENTKEYSPECIFIER)
    m_page->settings().setSampleBufferContentKeySessionSupportEnabled(m_sampleBufferContentKeySessionSupportEnabled);
#endif
    m_page->settings().setSampledPageTopColorMaxDifference(m_sampledPageTopColorMaxDifference);
    m_page->settings().setSampledPageTopColorMinHeight(m_sampledPageTopColorMinHeight);
    m_page->settings().setSansSerifFontFamily(m_sansSerifFontFamily);
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setScreenCaptureEnabled(m_screenCaptureEnabled);
#endif
    m_page->settings().setScreenOrientationAPIEnabled(m_screenOrientationAPIEnabled);
    m_page->settings().setScreenOrientationLockingAPIEnabled(m_screenOrientationLockingAPIEnabled);
    m_page->settings().setScreenWakeLockAPIEnabled(m_screenWakeLockAPIEnabled);
    m_page->settings().setScriptEnabled(m_scriptEnabled);
    m_page->settings().setScriptMarkupEnabled(m_scriptMarkupEnabled);
    m_page->settings().setScrollAnimatorEnabled(m_scrollAnimatorEnabled);
    m_page->settings().setScrollToTextFragmentEnabled(m_scrollToTextFragmentEnabled);
    m_page->settings().setScrollToTextFragmentIndicatorEnabled(m_scrollToTextFragmentIndicatorEnabled);
    m_page->settings().setScrollingCoordinatorEnabled(m_scrollingCoordinatorEnabled);
    m_page->settings().setScrollingPerformanceTestingEnabled(m_scrollingPerformanceTestingEnabled);
    m_page->settings().setScrollingTreeIncludesFrames(m_scrollingTreeIncludesFrames);
    m_page->settings().setSearchInputIncrementalAttributeAndSearchEventEnabled(m_searchInputIncrementalAttributeAndSearchEventEnabled);
    m_page->settings().setSecureContextChecksEnabled(m_secureContextChecksEnabled);
    m_page->settings().setSelectTrailingWhitespaceEnabled(m_selectTrailingWhitespaceEnabled);
    m_page->settings().setSelectionAPIForShadowDOMEnabled(m_selectionAPIForShadowDOMEnabled);
    m_page->settings().setSendMouseEventsToDisabledFormControlsEnabled(m_sendMouseEventsToDisabledFormControlsEnabled);
    m_page->settings().setSerifFontFamily(m_serifFontFamily);
#if ENABLE(SERVICE_CONTROLS)
    m_page->settings().setServiceControlsEnabled(m_serviceControlsEnabled);
#endif
#if ENABLE(SERVICE_WORKER)
    m_page->settings().setServiceWorkerNavigationPreloadEnabled(m_serviceWorkerNavigationPreloadEnabled);
#endif
#if ENABLE(SERVICE_WORKER)
    m_page->settings().setServiceWorkersEnabled(m_serviceWorkersEnabled);
#endif
#if ENABLE(SERVICE_WORKER)
    m_page->settings().setServiceWorkersUserGestureEnabled(m_serviceWorkersUserGestureEnabled);
#endif
    m_page->settings().setSessionStorageQuota(m_sessionStorageQuota);
    m_page->settings().setShapeDetection(m_shapeDetection);
    m_page->settings().setSharedWorkerEnabled(m_sharedWorkerEnabled);
    m_page->settings().setShouldAllowUserInstalledFonts(m_shouldAllowUserInstalledFonts);
    m_page->settings().setShouldConvertInvalidURLsToBlank(m_shouldConvertInvalidURLsToBlank);
    m_page->settings().setShouldConvertPositionStyleOnCopy(m_shouldConvertPositionStyleOnCopy);
    m_page->settings().setShouldDecidePolicyBeforeLoadingQuickLookPreview(m_shouldDecidePolicyBeforeLoadingQuickLookPreview);
    m_page->settings().setShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint(m_shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint);
    m_page->settings().setShouldDispatchSyntheticMouseEventsWhenModifyingSelection(m_shouldDispatchSyntheticMouseEventsWhenModifyingSelection);
    m_page->settings().setShouldDispatchSyntheticMouseOutAfterSyntheticClick(m_shouldDispatchSyntheticMouseOutAfterSyntheticClick);
#if ENABLE(VIDEO)
    m_page->settings().setShouldDisplayCaptions(m_shouldDisplayCaptions);
#endif
#if ENABLE(VIDEO)
    m_page->settings().setShouldDisplaySubtitles(m_shouldDisplaySubtitles);
#endif
#if ENABLE(VIDEO)
    m_page->settings().setShouldDisplayTextDescriptions(m_shouldDisplayTextDescriptions);
#endif
    m_page->settings().setShouldDropNearSuspendedAssertionAfterDelay(m_shouldDropNearSuspendedAssertionAfterDelay);
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setShouldEnableTextAutosizingBoost(m_shouldEnableTextAutosizingBoost);
#endif
    m_page->settings().setShouldIgnoreFontLoadCompletions(m_shouldIgnoreFontLoadCompletions);
    m_page->settings().setShouldIgnoreMetaViewport(m_shouldIgnoreMetaViewport);
    m_page->settings().setShouldInjectUserScriptsInInitialEmptyDocument(m_shouldInjectUserScriptsInInitialEmptyDocument);
    m_page->settings().setShouldPrintBackgrounds(m_shouldPrintBackgrounds);
    m_page->settings().setShouldRespectImageOrientation(m_shouldRespectImageOrientation);
    m_page->settings().setShouldRestrictBaseURLSchemes(m_shouldRestrictBaseURLSchemes);
    m_page->settings().setShouldSuppressTextInputFromEditingDuringProvisionalNavigation(m_shouldSuppressTextInputFromEditingDuringProvisionalNavigation);
    m_page->settings().setShouldTakeNearSuspendedAssertions(m_shouldTakeNearSuspendedAssertions);
    m_page->settings().setShouldUseServiceWorkerShortTimeout(m_shouldUseServiceWorkerShortTimeout);
    m_page->settings().setShowDebugBorders(m_showDebugBorders);
    m_page->settings().setShowMediaStatsContextMenuItemEnabled(m_showMediaStatsContextMenuItemEnabled);
    m_page->settings().setShowModalDialogEnabled(m_showModalDialogEnabled);
    m_page->settings().setShowRepaintCounter(m_showRepaintCounter);
    m_page->settings().setShowTiledScrollingIndicator(m_showTiledScrollingIndicator);
    m_page->settings().setShowsToolTipOverTruncatedText(m_showsToolTipOverTruncatedText);
    m_page->settings().setShowsURLsInToolTips(m_showsURLsInToolTips);
    m_page->settings().setShrinksStandaloneImagesToFit(m_shrinksStandaloneImagesToFit);
    m_page->settings().setSiteIsolationEnabled(m_siteIsolationEnabled);
    m_page->settings().setSmartInsertDeleteEnabled(m_smartInsertDeleteEnabled);
#if ENABLE(MEDIA_SOURCE)
    m_page->settings().setSourceBufferChangeTypeEnabled(m_sourceBufferChangeTypeEnabled);
#endif
    m_page->settings().setSpatialNavigationEnabled(m_spatialNavigationEnabled);
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setSpeakerSelectionRequiresUserGesture(m_speakerSelectionRequiresUserGesture);
#endif
    m_page->settings().setSpeechRecognitionEnabled(m_speechRecognitionEnabled);
    m_page->settings().setSpeechSynthesisAPIEnabled(m_speechSynthesisAPIEnabled);
    m_page->settings().setSpringTimingFunctionEnabled(m_springTimingFunctionEnabled);
    m_page->settings().setStandalone(m_standalone);
    m_page->settings().setStandardFontFamily(m_standardFontFamily);
    m_page->settings().setStorageAPIEnabled(m_storageAPIEnabled);
    m_page->settings().setStorageAPIEstimateEnabled(m_storageAPIEstimateEnabled);
    m_page->settings().setStorageAccessAPIEnabled(m_storageAccessAPIEnabled);
    m_page->settings().setStorageAccessAPIPerPageScopeEnabled(m_storageAccessAPIPerPageScopeEnabled);
    m_page->settings().setSubgridEnabled(m_subgridEnabled);
    m_page->settings().setSuppressesIncrementalRendering(m_suppressesIncrementalRendering);
    m_page->settings().setSyntheticEditingCommandsEnabled(m_syntheticEditingCommandsEnabled);
#if USE(SYSTEM_PREVIEW)
    m_page->settings().setSystemPreviewEnabled(m_systemPreviewEnabled);
#endif
    m_page->settings().setTelephoneNumberParsingEnabled(m_telephoneNumberParsingEnabled);
    m_page->settings().setTemporaryTileCohortRetentionEnabled(m_temporaryTileCohortRetentionEnabled);
    m_page->settings().setTextAreasAreResizable(m_textAreasAreResizable);
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setTextAutosizingEnabled(m_textAutosizingEnabled);
#endif
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setTextAutosizingUsesIdempotentMode(m_textAutosizingUsesIdempotentMode);
#endif
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setTextAutosizingWindowSizeOverrideHeight(m_textAutosizingWindowSizeOverrideHeight);
#endif
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setTextAutosizingWindowSizeOverrideWidth(m_textAutosizingWindowSizeOverrideWidth);
#endif
    m_page->settings().setTextInteractionEnabled(m_textInteractionEnabled);
#if ENABLE(IMAGE_ANALYSIS)
    m_page->settings().setTextRecognitionInVideosEnabled(m_textRecognitionInVideosEnabled);
#endif
    m_page->settings().setThirdPartyIframeRedirectBlockingEnabled(m_thirdPartyIframeRedirectBlockingEnabled);
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
    m_page->settings().setThreadedAnimationResolutionEnabled(m_threadedAnimationResolutionEnabled);
#endif
#if ENABLE(TOUCH_EVENTS)
    m_page->settings().setTouchEventEmulationEnabled(m_touchEventEmulationEnabled);
#endif
#if ENABLE(TOUCH_EVENTS)
    m_page->settings().setTouchEventsEnabled(m_touchEventsEnabled);
#endif
    m_page->settings().setTrackConfigurationEnabled(m_trackConfigurationEnabled);
    m_page->settings().setTransformStreamAPIEnabled(m_transformStreamAPIEnabled);
    m_page->settings().setTreatIPAddressAsDomain(m_treatIPAddressAsDomain);
    m_page->settings().setTreatsAnyTextCSSLinkAsStylesheet(m_treatsAnyTextCSSLinkAsStylesheet);
    m_page->settings().setUndoManagerAPIEnabled(m_undoManagerAPIEnabled);
    m_page->settings().setUnhandledPromiseRejectionToConsoleEnabled(m_unhandledPromiseRejectionToConsoleEnabled);
    m_page->settings().setUnifiedTextCheckerEnabled(m_unifiedTextCheckerEnabled);
    m_page->settings().setUnprefixedFullscreenAPIEnabled(m_unprefixedFullscreenAPIEnabled);
    m_page->settings().setUseAnonymousModeWhenFetchingMaskImages(m_useAnonymousModeWhenFetchingMaskImages);
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
    m_page->settings().setUseGPUProcessForWebGLEnabled(m_useGPUProcessForWebGLEnabled);
#endif
    m_page->settings().setUseGiantTiles(m_useGiantTiles);
    m_page->settings().setUseImageDocumentForSubframePDF(m_useImageDocumentForSubframePDF);
    m_page->settings().setUseLegacyBackgroundSizeShorthandBehavior(m_useLegacyBackgroundSizeShorthandBehavior);
    m_page->settings().setUsePreHTML5ParserQuirks(m_usePreHTML5ParserQuirks);
#if HAVE(SC_CONTENT_SHARING_PICKER)
    m_page->settings().setUseSCContentSharingPicker(m_useSCContentSharingPicker);
#endif
    m_page->settings().setUserActivationAPIEnabled(m_userActivationAPIEnabled);
    m_page->settings().setUserGesturePromisePropagationEnabled(m_userGesturePromisePropagationEnabled);
    m_page->settings().setUsesEncodingDetector(m_usesEncodingDetector);
    m_page->settings().setValidationMessageTimerMagnification(m_validationMessageTimerMagnification);
    m_page->settings().setVerifyWindowOpenUserGestureFromUIProcess(m_verifyWindowOpenUserGestureFromUIProcess);
    m_page->settings().setVerticalFormControlsEnabled(m_verticalFormControlsEnabled);
#if PLATFORM(IOS_FAMILY)
    m_page->settings().setVideoFullscreenRequiresElementFullscreen(m_videoFullscreenRequiresElementFullscreen);
#endif
    m_page->settings().setVideoPresentationModeAPIEnabled(m_videoPresentationModeAPIEnabled);
#if ENABLE(VIDEO)
    m_page->settings().setVideoQualityIncludesDisplayCompositingEnabled(m_videoQualityIncludesDisplayCompositingEnabled);
#endif
    m_page->settings().setVisibleDebugOverlayRegions(m_visibleDebugOverlayRegions);
#if ENABLE(IMAGE_ANALYSIS)
    m_page->settings().setVisualTranslationEnabled(m_visualTranslationEnabled);
#endif
    m_page->settings().setVisualViewportAPIEnabled(m_visualViewportAPIEnabled);
    m_page->settings().setVisualViewportEnabled(m_visualViewportEnabled);
#if ENABLE(VP9)
    m_page->settings().setVP9DecoderEnabled(m_vp9DecoderEnabled);
#endif
    m_page->settings().setWantsBalancedSetDefersLoadingBehavior(m_wantsBalancedSetDefersLoadingBehavior);
    m_page->settings().setWebAPIStatisticsEnabled(m_webAPIStatisticsEnabled);
    m_page->settings().setWebAPIsInShadowRealmEnabled(m_webAPIsInShadowRealmEnabled);
    m_page->settings().setWebAnimationsCompositeOperationsEnabled(m_webAnimationsCompositeOperationsEnabled);
    m_page->settings().setWebAnimationsCustomEffectsEnabled(m_webAnimationsCustomEffectsEnabled);
    m_page->settings().setWebAnimationsCustomFrameRateEnabled(m_webAnimationsCustomFrameRateEnabled);
    m_page->settings().setWebAnimationsIterationCompositeEnabled(m_webAnimationsIterationCompositeEnabled);
    m_page->settings().setWebAnimationsMutableTimelinesEnabled(m_webAnimationsMutableTimelinesEnabled);
#if ENABLE(WEB_ARCHIVE)
    m_page->settings().setWebArchiveDebugModeEnabled(m_webArchiveDebugModeEnabled);
#endif
#if ENABLE(WEB_ARCHIVE)
    m_page->settings().setWebArchiveTestingModeEnabled(m_webArchiveTestingModeEnabled);
#endif
#if ENABLE(WEBASSEMBLY)
    m_page->settings().setWebAssemblyESMIntegrationEnabled(m_webAssemblyESMIntegrationEnabled);
#endif
#if ENABLE(WEB_AUDIO)
    m_page->settings().setWebAudioEnabled(m_webAudioEnabled);
#endif
#if ENABLE(WEB_AUTHN)
    m_page->settings().setWebAuthenticationEnabled(m_webAuthenticationEnabled);
#endif
#if ENABLE(WEB_CODECS)
    m_page->settings().setWebCodecsAV1Enabled(m_webCodecsAV1Enabled);
#endif
#if ENABLE(WEB_CODECS)
    m_page->settings().setWebCodecsEnabled(m_webCodecsEnabled);
#endif
#if ENABLE(WEB_CODECS)
    m_page->settings().setWebCodecsHEVCEnabled(m_webCodecsHEVCEnabled);
#endif
    m_page->settings().setWebCryptoSafeCurvesEnabled(m_webCryptoSafeCurvesEnabled);
    m_page->settings().setWebGLDraftExtensionsEnabled(m_webGLDraftExtensionsEnabled);
    m_page->settings().setWebGLEnabled(m_webGLEnabled);
    m_page->settings().setWebGLErrorsToConsoleEnabled(m_webGLErrorsToConsoleEnabled);
    m_page->settings().setWebGLTimerQueriesEnabled(m_webGLTimerQueriesEnabled);
#if ENABLE(WEBGL) && PLATFORM(COCOA)
    m_page->settings().setWebGLUsingMetal(m_webGLUsingMetal);
#endif
    m_page->settings().setWebGPUEnabled(m_webGPUEnabled);
    m_page->settings().setWebInspectorEngineeringSettingsAllowed(m_webInspectorEngineeringSettingsAllowed);
    m_page->settings().setWebLocksAPIEnabled(m_webLocksAPIEnabled);
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCAV1CodecEnabled(m_webRTCAV1CodecEnabled);
#endif
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCDTMFEnabled(m_webRTCDTMFEnabled);
#endif
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCEncodedTransformEnabled(m_webRTCEncodedTransformEnabled);
#endif
    m_page->settings().setWebRTCEncryptionEnabled(m_webRTCEncryptionEnabled);
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCH265CodecEnabled(m_webRTCH265CodecEnabled);
#endif
#if USE(LIBWEBRTC)
    m_page->settings().setWebRTCMediaPipelineAdditionalLoggingEnabled(m_webRTCMediaPipelineAdditionalLoggingEnabled);
#endif
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCPlatformCodecsInGPUProcessEnabled(m_webRTCPlatformCodecsInGPUProcessEnabled);
#endif
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCRemoteVideoFrameEnabled(m_webRTCRemoteVideoFrameEnabled);
#endif
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCSFrameTransformEnabled(m_webRTCSFrameTransformEnabled);
#endif
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCSocketsProxyingEnabled(m_webRTCSocketsProxyingEnabled);
#endif
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCVP9Profile0CodecEnabled(m_webRTCVP9Profile0CodecEnabled);
#endif
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCVP9Profile2CodecEnabled(m_webRTCVP9Profile2CodecEnabled);
#endif
    m_page->settings().setWebSecurityEnabled(m_webSecurityEnabled);
    m_page->settings().setWebShareEnabled(m_webShareEnabled);
    m_page->settings().setWebShareFileAPIEnabled(m_webShareFileAPIEnabled);
    m_page->settings().setWebSocketEnabled(m_webSocketEnabled);
#if ENABLE(WEBXR)
    m_page->settings().setWebXRAugmentedRealityModuleEnabled(m_webXRAugmentedRealityModuleEnabled);
#endif
#if ENABLE(WEBXR)
    m_page->settings().setWebXREnabled(m_webXREnabled);
#endif
#if ENABLE(WEBXR)
    m_page->settings().setWebXRGamepadsModuleEnabled(m_webXRGamepadsModuleEnabled);
#endif
#if ENABLE(WEBXR_HANDS)
    m_page->settings().setWebXRHandInputModuleEnabled(m_webXRHandInputModuleEnabled);
#endif
    m_page->settings().setWebkitImageReadyEventEnabled(m_webkitImageReadyEventEnabled);
    m_page->settings().setWheelEventGesturesBecomeNonBlocking(m_wheelEventGesturesBecomeNonBlocking);
    m_page->settings().setWindowFocusRestricted(m_windowFocusRestricted);
    m_page->settings().setWirelessPlaybackTargetAPIEnabled(m_wirelessPlaybackTargetAPIEnabled);
    m_page->settings().setYouTubeFlashPluginReplacementEnabled(m_youTubeFlashPluginReplacementEnabled);
}

void InternalSettingsGenerated::setCSSOMViewScrollingAPIEnabled(bool CSSOMViewScrollingAPIEnabled)
{
    m_page->settings().setCSSOMViewScrollingAPIEnabled(CSSOMViewScrollingAPIEnabled);
}

void InternalSettingsGenerated::setCSSOMViewSmoothScrollingEnabled(bool CSSOMViewSmoothScrollingEnabled)
{
    m_page->settings().setCSSOMViewSmoothScrollingEnabled(CSSOMViewSmoothScrollingEnabled);
}

void InternalSettingsGenerated::setAbortSignalAnyOperationEnabled(bool abortSignalAnyOperationEnabled)
{
    m_page->settings().setAbortSignalAnyOperationEnabled(abortSignalAnyOperationEnabled);
}

void InternalSettingsGenerated::setAcceleratedCompositedAnimationsEnabled(bool acceleratedCompositedAnimationsEnabled)
{
    m_page->settings().setAcceleratedCompositedAnimationsEnabled(acceleratedCompositedAnimationsEnabled);
}

void InternalSettingsGenerated::setAcceleratedCompositingEnabled(bool acceleratedCompositingEnabled)
{
    m_page->settings().setAcceleratedCompositingEnabled(acceleratedCompositingEnabled);
}

void InternalSettingsGenerated::setAcceleratedCompositingForFixedPositionEnabled(bool acceleratedCompositingForFixedPositionEnabled)
{
    m_page->settings().setAcceleratedCompositingForFixedPositionEnabled(acceleratedCompositingForFixedPositionEnabled);
}

void InternalSettingsGenerated::setAcceleratedDrawingEnabled(bool acceleratedDrawingEnabled)
{
    m_page->settings().setAcceleratedDrawingEnabled(acceleratedDrawingEnabled);
}

void InternalSettingsGenerated::setAcceleratedFiltersEnabled(bool acceleratedFiltersEnabled)
{
#if USE(CORE_IMAGE)
    m_page->settings().setAcceleratedFiltersEnabled(acceleratedFiltersEnabled);
#else
    UNUSED_PARAM(acceleratedFiltersEnabled);
#endif
}

void InternalSettingsGenerated::setAccentColorEnabled(bool accentColorEnabled)
{
    m_page->settings().setAccentColorEnabled(accentColorEnabled);
}

void InternalSettingsGenerated::setAccessHandleEnabled(bool accessHandleEnabled)
{
    m_page->settings().setAccessHandleEnabled(accessHandleEnabled);
}

void InternalSettingsGenerated::setAggressiveTileRetentionEnabled(bool aggressiveTileRetentionEnabled)
{
    m_page->settings().setAggressiveTileRetentionEnabled(aggressiveTileRetentionEnabled);
}

void InternalSettingsGenerated::setAllowAnimationControlsOverride(bool allowAnimationControlsOverride)
{
    m_page->settings().setAllowAnimationControlsOverride(allowAnimationControlsOverride);
}

void InternalSettingsGenerated::setAllowContentSecurityPolicySourceStarToMatchAnyProtocol(bool allowContentSecurityPolicySourceStarToMatchAnyProtocol)
{
    m_page->settings().setAllowContentSecurityPolicySourceStarToMatchAnyProtocol(allowContentSecurityPolicySourceStarToMatchAnyProtocol);
}

void InternalSettingsGenerated::setAllowCrossOriginSubresourcesToAskForCredentials(bool allowCrossOriginSubresourcesToAskForCredentials)
{
    m_page->settings().setAllowCrossOriginSubresourcesToAskForCredentials(allowCrossOriginSubresourcesToAskForCredentials);
}

void InternalSettingsGenerated::setAllowDisplayOfInsecureContent(bool allowDisplayOfInsecureContent)
{
    m_page->settings().setAllowDisplayOfInsecureContent(allowDisplayOfInsecureContent);
}

void InternalSettingsGenerated::setAllowFileAccessFromFileURLs(bool allowFileAccessFromFileURLs)
{
    m_page->settings().setAllowFileAccessFromFileURLs(allowFileAccessFromFileURLs);
}

void InternalSettingsGenerated::setAllowMediaContentTypesRequiringHardwareSupportAsFallback(bool allowMediaContentTypesRequiringHardwareSupportAsFallback)
{
    m_page->settings().setAllowMediaContentTypesRequiringHardwareSupportAsFallback(allowMediaContentTypesRequiringHardwareSupportAsFallback);
}

void InternalSettingsGenerated::setAllowMultiElementImplicitSubmission(bool allowMultiElementImplicitSubmission)
{
    m_page->settings().setAllowMultiElementImplicitSubmission(allowMultiElementImplicitSubmission);
}

void InternalSettingsGenerated::setAllowRunningOfInsecureContent(bool allowRunningOfInsecureContent)
{
    m_page->settings().setAllowRunningOfInsecureContent(allowRunningOfInsecureContent);
}

void InternalSettingsGenerated::setAllowSettingAnyXHRHeaderFromFileURLs(bool allowSettingAnyXHRHeaderFromFileURLs)
{
    m_page->settings().setAllowSettingAnyXHRHeaderFromFileURLs(allowSettingAnyXHRHeaderFromFileURLs);
}

void InternalSettingsGenerated::setAllowTopNavigationToDataURLs(bool allowTopNavigationToDataURLs)
{
    m_page->settings().setAllowTopNavigationToDataURLs(allowTopNavigationToDataURLs);
}

void InternalSettingsGenerated::setAllowUniversalAccessFromFileURLs(bool allowUniversalAccessFromFileURLs)
{
    m_page->settings().setAllowUniversalAccessFromFileURLs(allowUniversalAccessFromFileURLs);
}

void InternalSettingsGenerated::setAllowViewportShrinkToFitContent(bool allowViewportShrinkToFitContent)
{
#if PLATFORM(IOS_FAMILY)
    m_page->settings().setAllowViewportShrinkToFitContent(allowViewportShrinkToFitContent);
#else
    UNUSED_PARAM(allowViewportShrinkToFitContent);
#endif
}

void InternalSettingsGenerated::setAllowWebGLInWorkers(bool allowWebGLInWorkers)
{
#if ENABLE(WEBGL)
    m_page->settings().setAllowWebGLInWorkers(allowWebGLInWorkers);
#else
    UNUSED_PARAM(allowWebGLInWorkers);
#endif
}

void InternalSettingsGenerated::setAllowsAirPlayForMediaPlayback(bool allowsAirPlayForMediaPlayback)
{
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    m_page->settings().setAllowsAirPlayForMediaPlayback(allowsAirPlayForMediaPlayback);
#else
    UNUSED_PARAM(allowsAirPlayForMediaPlayback);
#endif
}

void InternalSettingsGenerated::setAllowsInlineMediaPlayback(bool allowsInlineMediaPlayback)
{
    m_page->settings().setAllowsInlineMediaPlayback(allowsInlineMediaPlayback);
}

void InternalSettingsGenerated::setAllowsInlineMediaPlaybackAfterFullscreen(bool allowsInlineMediaPlaybackAfterFullscreen)
{
    m_page->settings().setAllowsInlineMediaPlaybackAfterFullscreen(allowsInlineMediaPlaybackAfterFullscreen);
}

void InternalSettingsGenerated::setAllowsPictureInPictureMediaPlayback(bool allowsPictureInPictureMediaPlayback)
{
    m_page->settings().setAllowsPictureInPictureMediaPlayback(allowsPictureInPictureMediaPlayback);
}

void InternalSettingsGenerated::setAlternateFormControlDesignEnabled(bool alternateFormControlDesignEnabled)
{
#if PLATFORM(IOS_FAMILY)
    m_page->settings().setAlternateFormControlDesignEnabled(alternateFormControlDesignEnabled);
#else
    UNUSED_PARAM(alternateFormControlDesignEnabled);
#endif
}

void InternalSettingsGenerated::setAlternateFullScreenControlDesignEnabled(bool alternateFullScreenControlDesignEnabled)
{
#if PLATFORM(IOS_FAMILY)
    m_page->settings().setAlternateFullScreenControlDesignEnabled(alternateFullScreenControlDesignEnabled);
#else
    UNUSED_PARAM(alternateFullScreenControlDesignEnabled);
#endif
}

void InternalSettingsGenerated::setAlternateWebMPlayerEnabled(bool alternateWebMPlayerEnabled)
{
#if ENABLE(ALTERNATE_WEBM_PLAYER)
    m_page->settings().setAlternateWebMPlayerEnabled(alternateWebMPlayerEnabled);
#else
    UNUSED_PARAM(alternateWebMPlayerEnabled);
#endif
}

void InternalSettingsGenerated::setAnimatedImageAsyncDecodingEnabled(bool animatedImageAsyncDecodingEnabled)
{
    m_page->settings().setAnimatedImageAsyncDecodingEnabled(animatedImageAsyncDecodingEnabled);
}

void InternalSettingsGenerated::setAnimatedImageDebugCanvasDrawingEnabled(bool animatedImageDebugCanvasDrawingEnabled)
{
    m_page->settings().setAnimatedImageDebugCanvasDrawingEnabled(animatedImageDebugCanvasDrawingEnabled);
}

void InternalSettingsGenerated::setAppBadgeEnabled(bool appBadgeEnabled)
{
#if ENABLE(BADGING)
    m_page->settings().setAppBadgeEnabled(appBadgeEnabled);
#else
    UNUSED_PARAM(appBadgeEnabled);
#endif
}

void InternalSettingsGenerated::setAppHighlightsEnabled(bool appHighlightsEnabled)
{
#if ENABLE(APP_HIGHLIGHTS)
    m_page->settings().setAppHighlightsEnabled(appHighlightsEnabled);
#else
    UNUSED_PARAM(appHighlightsEnabled);
#endif
}

void InternalSettingsGenerated::setAppleMailPaginationQuirkEnabled(bool appleMailPaginationQuirkEnabled)
{
    m_page->settings().setAppleMailPaginationQuirkEnabled(appleMailPaginationQuirkEnabled);
}

void InternalSettingsGenerated::setApplePayCapabilityDisclosureAllowed(bool applePayCapabilityDisclosureAllowed)
{
#if ENABLE(APPLE_PAY)
    m_page->settings().setApplePayCapabilityDisclosureAllowed(applePayCapabilityDisclosureAllowed);
#else
    UNUSED_PARAM(applePayCapabilityDisclosureAllowed);
#endif
}

void InternalSettingsGenerated::setApplePayEnabled(bool applePayEnabled)
{
#if ENABLE(APPLE_PAY)
    m_page->settings().setApplePayEnabled(applePayEnabled);
#else
    UNUSED_PARAM(applePayEnabled);
#endif
}

void InternalSettingsGenerated::setAriaReflectionForElementReferencesEnabled(bool ariaReflectionForElementReferencesEnabled)
{
    m_page->settings().setAriaReflectionForElementReferencesEnabled(ariaReflectionForElementReferencesEnabled);
}

void InternalSettingsGenerated::setAspectRatioEnabled(bool aspectRatioEnabled)
{
    m_page->settings().setAspectRatioEnabled(aspectRatioEnabled);
}

void InternalSettingsGenerated::setAspectRatioOfImgFromWidthAndHeightEnabled(bool aspectRatioOfImgFromWidthAndHeightEnabled)
{
    m_page->settings().setAspectRatioOfImgFromWidthAndHeightEnabled(aspectRatioOfImgFromWidthAndHeightEnabled);
}

void InternalSettingsGenerated::setAsyncClipboardAPIEnabled(bool asyncClipboardAPIEnabled)
{
    m_page->settings().setAsyncClipboardAPIEnabled(asyncClipboardAPIEnabled);
}

void InternalSettingsGenerated::setAsyncFrameScrollingEnabled(bool asyncFrameScrollingEnabled)
{
    m_page->settings().setAsyncFrameScrollingEnabled(asyncFrameScrollingEnabled);
}

void InternalSettingsGenerated::setAsyncOverflowScrollingEnabled(bool asyncOverflowScrollingEnabled)
{
    m_page->settings().setAsyncOverflowScrollingEnabled(asyncOverflowScrollingEnabled);
}

void InternalSettingsGenerated::setAsynchronousSpellCheckingEnabled(bool asynchronousSpellCheckingEnabled)
{
    m_page->settings().setAsynchronousSpellCheckingEnabled(asynchronousSpellCheckingEnabled);
}

void InternalSettingsGenerated::setAttachmentWideLayoutEnabled(bool attachmentWideLayoutEnabled)
{
#if ENABLE(ATTACHMENT_ELEMENT)
    m_page->settings().setAttachmentWideLayoutEnabled(attachmentWideLayoutEnabled);
#else
    UNUSED_PARAM(attachmentWideLayoutEnabled);
#endif
}

void InternalSettingsGenerated::setAudioControlsScaleWithPageZoom(bool audioControlsScaleWithPageZoom)
{
    m_page->settings().setAudioControlsScaleWithPageZoom(audioControlsScaleWithPageZoom);
}

void InternalSettingsGenerated::setAudioDescriptionsEnabled(bool audioDescriptionsEnabled)
{
#if ENABLE(VIDEO)
    m_page->settings().setAudioDescriptionsEnabled(audioDescriptionsEnabled);
#else
    UNUSED_PARAM(audioDescriptionsEnabled);
#endif
}

void InternalSettingsGenerated::setAuthorAndUserStylesEnabled(bool authorAndUserStylesEnabled)
{
    m_page->settings().setAuthorAndUserStylesEnabled(authorAndUserStylesEnabled);
}

void InternalSettingsGenerated::setAutoscrollForDragAndDropEnabled(bool autoscrollForDragAndDropEnabled)
{
    m_page->settings().setAutoscrollForDragAndDropEnabled(autoscrollForDragAndDropEnabled);
}

void InternalSettingsGenerated::setBackgroundFetchAPIEnabled(bool backgroundFetchAPIEnabled)
{
#if ENABLE(SERVICE_WORKER)
    m_page->settings().setBackgroundFetchAPIEnabled(backgroundFetchAPIEnabled);
#else
    UNUSED_PARAM(backgroundFetchAPIEnabled);
#endif
}

void InternalSettingsGenerated::setBackgroundShouldExtendBeyondPage(bool backgroundShouldExtendBeyondPage)
{
    m_page->settings().setBackgroundShouldExtendBeyondPage(backgroundShouldExtendBeyondPage);
}

void InternalSettingsGenerated::setBackgroundWebContentRunningBoardThrottlingEnabled(bool backgroundWebContentRunningBoardThrottlingEnabled)
{
#if PLATFORM(MAC) && USE(RUNNINGBOARD)
    m_page->settings().setBackgroundWebContentRunningBoardThrottlingEnabled(backgroundWebContentRunningBoardThrottlingEnabled);
#else
    UNUSED_PARAM(backgroundWebContentRunningBoardThrottlingEnabled);
#endif
}

void InternalSettingsGenerated::setBackspaceKeyNavigationEnabled(bool backspaceKeyNavigationEnabled)
{
    m_page->settings().setBackspaceKeyNavigationEnabled(backspaceKeyNavigationEnabled);
}

void InternalSettingsGenerated::setBeaconAPIEnabled(bool beaconAPIEnabled)
{
    m_page->settings().setBeaconAPIEnabled(beaconAPIEnabled);
}

void InternalSettingsGenerated::setBlockMediaLayerRehostingInWebContentProcess(bool blockMediaLayerRehostingInWebContentProcess)
{
#if ENABLE(GPU_PROCESS)
    m_page->settings().setBlockMediaLayerRehostingInWebContentProcess(blockMediaLayerRehostingInWebContentProcess);
#else
    UNUSED_PARAM(blockMediaLayerRehostingInWebContentProcess);
#endif
}

void InternalSettingsGenerated::setBroadcastChannelEnabled(bool broadcastChannelEnabled)
{
    m_page->settings().setBroadcastChannelEnabled(broadcastChannelEnabled);
}

void InternalSettingsGenerated::setBroadcastChannelOriginPartitioningEnabled(bool broadcastChannelOriginPartitioningEnabled)
{
    m_page->settings().setBroadcastChannelOriginPartitioningEnabled(broadcastChannelOriginPartitioningEnabled);
}

void InternalSettingsGenerated::setCacheAPIEnabled(bool cacheAPIEnabled)
{
    m_page->settings().setCacheAPIEnabled(cacheAPIEnabled);
}

void InternalSettingsGenerated::setCanvasColorSpaceEnabled(bool canvasColorSpaceEnabled)
{
    m_page->settings().setCanvasColorSpaceEnabled(canvasColorSpaceEnabled);
}

void InternalSettingsGenerated::setCanvasFiltersEnabled(bool canvasFiltersEnabled)
{
    m_page->settings().setCanvasFiltersEnabled(canvasFiltersEnabled);
}

void InternalSettingsGenerated::setCanvasFingerprintingQuirkEnabled(bool canvasFingerprintingQuirkEnabled)
{
    m_page->settings().setCanvasFingerprintingQuirkEnabled(canvasFingerprintingQuirkEnabled);
}

void InternalSettingsGenerated::setCanvasUsesAcceleratedDrawing(bool canvasUsesAcceleratedDrawing)
{
    m_page->settings().setCanvasUsesAcceleratedDrawing(canvasUsesAcceleratedDrawing);
}

void InternalSettingsGenerated::setCaretBrowsingEnabled(bool caretBrowsingEnabled)
{
    m_page->settings().setCaretBrowsingEnabled(caretBrowsingEnabled);
}

void InternalSettingsGenerated::setClearSiteDataHTTPHeaderEnabled(bool clearSiteDataHTTPHeaderEnabled)
{
    m_page->settings().setClearSiteDataHTTPHeaderEnabled(clearSiteDataHTTPHeaderEnabled);
}

void InternalSettingsGenerated::setClientBadgeEnabled(bool clientBadgeEnabled)
{
#if ENABLE(BADGING)
    m_page->settings().setClientBadgeEnabled(clientBadgeEnabled);
#else
    UNUSED_PARAM(clientBadgeEnabled);
#endif
}

void InternalSettingsGenerated::setClientCoordinatesRelativeToLayoutViewport(bool clientCoordinatesRelativeToLayoutViewport)
{
    m_page->settings().setClientCoordinatesRelativeToLayoutViewport(clientCoordinatesRelativeToLayoutViewport);
}

void InternalSettingsGenerated::setColorFilterEnabled(bool colorFilterEnabled)
{
    m_page->settings().setColorFilterEnabled(colorFilterEnabled);
}

void InternalSettingsGenerated::setCompressionStreamEnabled(bool compressionStreamEnabled)
{
    m_page->settings().setCompressionStreamEnabled(compressionStreamEnabled);
}

void InternalSettingsGenerated::setConstantPropertiesEnabled(bool constantPropertiesEnabled)
{
    m_page->settings().setConstantPropertiesEnabled(constantPropertiesEnabled);
}

void InternalSettingsGenerated::setConstructableStylesheetsEnabled(bool constructableStylesheetsEnabled)
{
    m_page->settings().setConstructableStylesheetsEnabled(constructableStylesheetsEnabled);
}

void InternalSettingsGenerated::setContactPickerAPIEnabled(bool contactPickerAPIEnabled)
{
    m_page->settings().setContactPickerAPIEnabled(contactPickerAPIEnabled);
}

void InternalSettingsGenerated::setContentChangeObserverEnabled(bool contentChangeObserverEnabled)
{
#if ENABLE(CONTENT_CHANGE_OBSERVER)
    m_page->settings().setContentChangeObserverEnabled(contentChangeObserverEnabled);
#else
    UNUSED_PARAM(contentChangeObserverEnabled);
#endif
}

void InternalSettingsGenerated::setContentDispositionAttachmentSandboxEnabled(bool contentDispositionAttachmentSandboxEnabled)
{
    m_page->settings().setContentDispositionAttachmentSandboxEnabled(contentDispositionAttachmentSandboxEnabled);
}

void InternalSettingsGenerated::setContextMenuQRCodeDetectionEnabled(bool contextMenuQRCodeDetectionEnabled)
{
#if ENABLE(CONTEXT_MENU_QR_CODE_DETECTION)
    m_page->settings().setContextMenuQRCodeDetectionEnabled(contextMenuQRCodeDetectionEnabled);
#else
    UNUSED_PARAM(contextMenuQRCodeDetectionEnabled);
#endif
}

void InternalSettingsGenerated::setCookieConsentAPIEnabled(bool cookieConsentAPIEnabled)
{
    m_page->settings().setCookieConsentAPIEnabled(cookieConsentAPIEnabled);
}

void InternalSettingsGenerated::setCookieEnabled(bool cookieEnabled)
{
    m_page->settings().setCookieEnabled(cookieEnabled);
}

void InternalSettingsGenerated::setCookieStoreAPIEnabled(bool cookieStoreAPIEnabled)
{
    m_page->settings().setCookieStoreAPIEnabled(cookieStoreAPIEnabled);
}

void InternalSettingsGenerated::setCookieStoreAPIExtendedAttributesEnabled(bool cookieStoreAPIExtendedAttributesEnabled)
{
    m_page->settings().setCookieStoreAPIExtendedAttributesEnabled(cookieStoreAPIExtendedAttributesEnabled);
}

void InternalSettingsGenerated::setCoreMathMLEnabled(bool coreMathMLEnabled)
{
    m_page->settings().setCoreMathMLEnabled(coreMathMLEnabled);
}

void InternalSettingsGenerated::setCrossOriginCheckInGetMatchedCSSRulesDisabled(bool crossOriginCheckInGetMatchedCSSRulesDisabled)
{
    m_page->settings().setCrossOriginCheckInGetMatchedCSSRulesDisabled(crossOriginCheckInGetMatchedCSSRulesDisabled);
}

void InternalSettingsGenerated::setCrossOriginEmbedderPolicyEnabled(bool crossOriginEmbedderPolicyEnabled)
{
    m_page->settings().setCrossOriginEmbedderPolicyEnabled(crossOriginEmbedderPolicyEnabled);
}

void InternalSettingsGenerated::setCrossOriginOpenerPolicyEnabled(bool crossOriginOpenerPolicyEnabled)
{
    m_page->settings().setCrossOriginOpenerPolicyEnabled(crossOriginOpenerPolicyEnabled);
}

void InternalSettingsGenerated::setCSS3DTransformInteroperabilityEnabled(bool css3DTransformInteroperabilityEnabled)
{
    m_page->settings().setCSS3DTransformInteroperabilityEnabled(css3DTransformInteroperabilityEnabled);
}

void InternalSettingsGenerated::setCSSCascadeLayersEnabled(bool cssCascadeLayersEnabled)
{
    m_page->settings().setCSSCascadeLayersEnabled(cssCascadeLayersEnabled);
}

void InternalSettingsGenerated::setCSSColor4(bool cssColor4)
{
    m_page->settings().setCSSColor4(cssColor4);
}

void InternalSettingsGenerated::setCSSColorContrastEnabled(bool cssColorContrastEnabled)
{
    m_page->settings().setCSSColorContrastEnabled(cssColorContrastEnabled);
}

void InternalSettingsGenerated::setCSSColorMixEnabled(bool cssColorMixEnabled)
{
    m_page->settings().setCSSColorMixEnabled(cssColorMixEnabled);
}

void InternalSettingsGenerated::setCSSContainIntrinsicSizeEnabled(bool cssContainIntrinsicSizeEnabled)
{
    m_page->settings().setCSSContainIntrinsicSizeEnabled(cssContainIntrinsicSizeEnabled);
}

void InternalSettingsGenerated::setCSSContainerQueriesEnabled(bool cssContainerQueriesEnabled)
{
    m_page->settings().setCSSContainerQueriesEnabled(cssContainerQueriesEnabled);
}

void InternalSettingsGenerated::setCSSContainmentEnabled(bool cssContainmentEnabled)
{
    m_page->settings().setCSSContainmentEnabled(cssContainmentEnabled);
}

void InternalSettingsGenerated::setCSSContentVisibilityEnabled(bool cssContentVisibilityEnabled)
{
    m_page->settings().setCSSContentVisibilityEnabled(cssContentVisibilityEnabled);
}

void InternalSettingsGenerated::setCSSCounterStyleAtRuleImageSymbolsEnabled(bool cssCounterStyleAtRuleImageSymbolsEnabled)
{
    m_page->settings().setCSSCounterStyleAtRuleImageSymbolsEnabled(cssCounterStyleAtRuleImageSymbolsEnabled);
}

void InternalSettingsGenerated::setCSSCounterStyleAtRulesEnabled(bool cssCounterStyleAtRulesEnabled)
{
    m_page->settings().setCSSCounterStyleAtRulesEnabled(cssCounterStyleAtRulesEnabled);
}

void InternalSettingsGenerated::setCSSCustomPropertiesAndValuesEnabled(bool cssCustomPropertiesAndValuesEnabled)
{
    m_page->settings().setCSSCustomPropertiesAndValuesEnabled(cssCustomPropertiesAndValuesEnabled);
}

void InternalSettingsGenerated::setCSSFontFaceSizeAdjustEnabled(bool cssFontFaceSizeAdjustEnabled)
{
    m_page->settings().setCSSFontFaceSizeAdjustEnabled(cssFontFaceSizeAdjustEnabled);
}

void InternalSettingsGenerated::setCSSGradientInterpolationColorSpacesEnabled(bool cssGradientInterpolationColorSpacesEnabled)
{
    m_page->settings().setCSSGradientInterpolationColorSpacesEnabled(cssGradientInterpolationColorSpacesEnabled);
}

void InternalSettingsGenerated::setCSSGradientPremultipliedAlphaInterpolationEnabled(bool cssGradientPremultipliedAlphaInterpolationEnabled)
{
    m_page->settings().setCSSGradientPremultipliedAlphaInterpolationEnabled(cssGradientPremultipliedAlphaInterpolationEnabled);
}

void InternalSettingsGenerated::setCSSIndividualTransformPropertiesEnabled(bool cssIndividualTransformPropertiesEnabled)
{
    m_page->settings().setCSSIndividualTransformPropertiesEnabled(cssIndividualTransformPropertiesEnabled);
}

void InternalSettingsGenerated::setCSSInputSecurityEnabled(bool cssInputSecurityEnabled)
{
    m_page->settings().setCSSInputSecurityEnabled(cssInputSecurityEnabled);
}

void InternalSettingsGenerated::setCSSMarginTrimEnabled(bool cssMarginTrimEnabled)
{
    m_page->settings().setCSSMarginTrimEnabled(cssMarginTrimEnabled);
}

void InternalSettingsGenerated::setCSSMotionPathEnabled(bool cssMotionPathEnabled)
{
    m_page->settings().setCSSMotionPathEnabled(cssMotionPathEnabled);
}

void InternalSettingsGenerated::setCSSNestingEnabled(bool cssNestingEnabled)
{
    m_page->settings().setCSSNestingEnabled(cssNestingEnabled);
}

void InternalSettingsGenerated::setCSSPaintingAPIEnabled(bool cssPaintingAPIEnabled)
{
#if ENABLE(CSS_PAINTING_API)
    m_page->settings().setCSSPaintingAPIEnabled(cssPaintingAPIEnabled);
#else
    UNUSED_PARAM(cssPaintingAPIEnabled);
#endif
}

void InternalSettingsGenerated::setCSSRelativeColorSyntaxEnabled(bool cssRelativeColorSyntaxEnabled)
{
    m_page->settings().setCSSRelativeColorSyntaxEnabled(cssRelativeColorSyntaxEnabled);
}

void InternalSettingsGenerated::setCSSRhythmicSizingEnabled(bool cssRhythmicSizingEnabled)
{
    m_page->settings().setCSSRhythmicSizingEnabled(cssRhythmicSizingEnabled);
}

void InternalSettingsGenerated::setCSSScrollAnchoringEnabled(bool cssScrollAnchoringEnabled)
{
    m_page->settings().setCSSScrollAnchoringEnabled(cssScrollAnchoringEnabled);
}

void InternalSettingsGenerated::setCSSScrollbarColorEnabled(bool cssScrollbarColorEnabled)
{
    m_page->settings().setCSSScrollbarColorEnabled(cssScrollbarColorEnabled);
}

void InternalSettingsGenerated::setCSSScrollbarGutterEnabled(bool cssScrollbarGutterEnabled)
{
    m_page->settings().setCSSScrollbarGutterEnabled(cssScrollbarGutterEnabled);
}

void InternalSettingsGenerated::setCSSScrollbarWidthEnabled(bool cssScrollbarWidthEnabled)
{
    m_page->settings().setCSSScrollbarWidthEnabled(cssScrollbarWidthEnabled);
}

void InternalSettingsGenerated::setCSSTextAlignLastEnabled(bool cssTextAlignLastEnabled)
{
    m_page->settings().setCSSTextAlignLastEnabled(cssTextAlignLastEnabled);
}

void InternalSettingsGenerated::setCSSTextBoxTrimEnabled(bool cssTextBoxTrimEnabled)
{
    m_page->settings().setCSSTextBoxTrimEnabled(cssTextBoxTrimEnabled);
}

void InternalSettingsGenerated::setCSSTextGroupAlignEnabled(bool cssTextGroupAlignEnabled)
{
    m_page->settings().setCSSTextGroupAlignEnabled(cssTextGroupAlignEnabled);
}

void InternalSettingsGenerated::setCSSTextJustifyEnabled(bool cssTextJustifyEnabled)
{
    m_page->settings().setCSSTextJustifyEnabled(cssTextJustifyEnabled);
}

void InternalSettingsGenerated::setCSSTextSpacingEnabled(bool cssTextSpacingEnabled)
{
    m_page->settings().setCSSTextSpacingEnabled(cssTextSpacingEnabled);
}

void InternalSettingsGenerated::setCSSTextUnderlinePositionLeftRightEnabled(bool cssTextUnderlinePositionLeftRightEnabled)
{
    m_page->settings().setCSSTextUnderlinePositionLeftRightEnabled(cssTextUnderlinePositionLeftRightEnabled);
}

void InternalSettingsGenerated::setCSSTextWrapNewValuesEnabled(bool cssTextWrapNewValuesEnabled)
{
    m_page->settings().setCSSTextWrapNewValuesEnabled(cssTextWrapNewValuesEnabled);
}

void InternalSettingsGenerated::setCSSTransformStyleOptimized3DEnabled(bool cssTransformStyleOptimized3DEnabled)
{
#if ENABLE(CSS_TRANSFORM_STYLE_OPTIMIZED_3D)
    m_page->settings().setCSSTransformStyleOptimized3DEnabled(cssTransformStyleOptimized3DEnabled);
#else
    UNUSED_PARAM(cssTransformStyleOptimized3DEnabled);
#endif
}

void InternalSettingsGenerated::setCSSTypedOMColorEnabled(bool cssTypedOMColorEnabled)
{
    m_page->settings().setCSSTypedOMColorEnabled(cssTypedOMColorEnabled);
}

void InternalSettingsGenerated::setCSSTypedOMEnabled(bool cssTypedOMEnabled)
{
    m_page->settings().setCSSTypedOMEnabled(cssTypedOMEnabled);
}

void InternalSettingsGenerated::setCSSWhiteSpaceLonghandsEnabled(bool cssWhiteSpaceLonghandsEnabled)
{
    m_page->settings().setCSSWhiteSpaceLonghandsEnabled(cssWhiteSpaceLonghandsEnabled);
}

void InternalSettingsGenerated::setCSSWordBreakAutoEnabled(bool cssWordBreakAutoEnabled)
{
    m_page->settings().setCSSWordBreakAutoEnabled(cssWordBreakAutoEnabled);
}

void InternalSettingsGenerated::setCursiveFontFamily(const String& cursiveFontFamily)
{
    m_page->settings().setCursiveFontFamily(cursiveFontFamily);
}

void InternalSettingsGenerated::setDataListElementEnabled(bool dataListElementEnabled)
{
#if ENABLE(DATALIST_ELEMENT)
    m_page->settings().setDataListElementEnabled(dataListElementEnabled);
#else
    UNUSED_PARAM(dataListElementEnabled);
#endif
}

void InternalSettingsGenerated::setDataTransferItemsEnabled(bool dataTransferItemsEnabled)
{
    m_page->settings().setDataTransferItemsEnabled(dataTransferItemsEnabled);
}

void InternalSettingsGenerated::setDateTimeInputsEditableComponentsEnabled(bool dateTimeInputsEditableComponentsEnabled)
{
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    m_page->settings().setDateTimeInputsEditableComponentsEnabled(dateTimeInputsEditableComponentsEnabled);
#else
    UNUSED_PARAM(dateTimeInputsEditableComponentsEnabled);
#endif
}

void InternalSettingsGenerated::setDeclarativeShadowDOMEnabled(bool declarativeShadowDOMEnabled)
{
    m_page->settings().setDeclarativeShadowDOMEnabled(declarativeShadowDOMEnabled);
}

void InternalSettingsGenerated::setDeclarativeShadowDOMInDOMParserEnabled(bool declarativeShadowDOMInDOMParserEnabled)
{
    m_page->settings().setDeclarativeShadowDOMInDOMParserEnabled(declarativeShadowDOMInDOMParserEnabled);
}

void InternalSettingsGenerated::setDefaultARIAForCustomElementsEnabled(bool defaultARIAForCustomElementsEnabled)
{
    m_page->settings().setDefaultARIAForCustomElementsEnabled(defaultARIAForCustomElementsEnabled);
}

void InternalSettingsGenerated::setDefaultFixedFontSize(double defaultFixedFontSize)
{
    m_page->settings().setDefaultFixedFontSize(defaultFixedFontSize);
}

void InternalSettingsGenerated::setDefaultFontSize(double defaultFontSize)
{
    m_page->settings().setDefaultFontSize(defaultFontSize);
}

void InternalSettingsGenerated::setDefaultTextEncodingName(const String& defaultTextEncodingName)
{
    m_page->settings().setDefaultTextEncodingName(defaultTextEncodingName);
}

void InternalSettingsGenerated::setDefaultVideoPosterURL(const String& defaultVideoPosterURL)
{
    m_page->settings().setDefaultVideoPosterURL(defaultVideoPosterURL);
}

void InternalSettingsGenerated::setDeprecateRSAESPKCSWebCryptoEnabled(bool deprecateRSAESPKCSWebCryptoEnabled)
{
    m_page->settings().setDeprecateRSAESPKCSWebCryptoEnabled(deprecateRSAESPKCSWebCryptoEnabled);
}

void InternalSettingsGenerated::setDeprecationReportingEnabled(bool deprecationReportingEnabled)
{
    m_page->settings().setDeprecationReportingEnabled(deprecationReportingEnabled);
}

void InternalSettingsGenerated::setDeveloperExtrasEnabled(bool developerExtrasEnabled)
{
    m_page->settings().setDeveloperExtrasEnabled(developerExtrasEnabled);
}

void InternalSettingsGenerated::setDeviceHeight(uint32_t deviceHeight)
{
    m_page->settings().setDeviceHeight(deviceHeight);
}

void InternalSettingsGenerated::setDeviceOrientationEventEnabled(bool deviceOrientationEventEnabled)
{
#if ENABLE(DEVICE_ORIENTATION)
    m_page->settings().setDeviceOrientationEventEnabled(deviceOrientationEventEnabled);
#else
    UNUSED_PARAM(deviceOrientationEventEnabled);
#endif
}

void InternalSettingsGenerated::setDeviceOrientationPermissionAPIEnabled(bool deviceOrientationPermissionAPIEnabled)
{
#if ENABLE(DEVICE_ORIENTATION)
    m_page->settings().setDeviceOrientationPermissionAPIEnabled(deviceOrientationPermissionAPIEnabled);
#else
    UNUSED_PARAM(deviceOrientationPermissionAPIEnabled);
#endif
}

void InternalSettingsGenerated::setDeviceWidth(uint32_t deviceWidth)
{
    m_page->settings().setDeviceWidth(deviceWidth);
}

void InternalSettingsGenerated::setDiagnosticLoggingEnabled(bool diagnosticLoggingEnabled)
{
    m_page->settings().setDiagnosticLoggingEnabled(diagnosticLoggingEnabled);
}

void InternalSettingsGenerated::setDialogElementEnabled(bool dialogElementEnabled)
{
    m_page->settings().setDialogElementEnabled(dialogElementEnabled);
}

void InternalSettingsGenerated::setDirPseudoEnabled(bool dirPseudoEnabled)
{
    m_page->settings().setDirPseudoEnabled(dirPseudoEnabled);
}

void InternalSettingsGenerated::setDirectoryUploadEnabled(bool directoryUploadEnabled)
{
    m_page->settings().setDirectoryUploadEnabled(directoryUploadEnabled);
}

void InternalSettingsGenerated::setDisabledAdaptationsMetaTagEnabled(bool disabledAdaptationsMetaTagEnabled)
{
    m_page->settings().setDisabledAdaptationsMetaTagEnabled(disabledAdaptationsMetaTagEnabled);
}

void InternalSettingsGenerated::setDisallowSyncXHRDuringPageDismissalEnabled(bool disallowSyncXHRDuringPageDismissalEnabled)
{
    m_page->settings().setDisallowSyncXHRDuringPageDismissalEnabled(disallowSyncXHRDuringPageDismissalEnabled);
}

void InternalSettingsGenerated::setDisplayListDrawingEnabled(bool displayListDrawingEnabled)
{
    m_page->settings().setDisplayListDrawingEnabled(displayListDrawingEnabled);
}

void InternalSettingsGenerated::setDNSPrefetchingEnabled(bool dnsPrefetchingEnabled)
{
    m_page->settings().setDNSPrefetchingEnabled(dnsPrefetchingEnabled);
}

void InternalSettingsGenerated::setDOMAudioSessionEnabled(bool domAudioSessionEnabled)
{
#if ENABLE(DOM_AUDIO_SESSION)
    m_page->settings().setDOMAudioSessionEnabled(domAudioSessionEnabled);
#else
    UNUSED_PARAM(domAudioSessionEnabled);
#endif
}

void InternalSettingsGenerated::setDOMAudioSessionFullEnabled(bool domAudioSessionFullEnabled)
{
#if ENABLE(DOM_AUDIO_SESSION)
    m_page->settings().setDOMAudioSessionFullEnabled(domAudioSessionFullEnabled);
#else
    UNUSED_PARAM(domAudioSessionFullEnabled);
#endif
}

void InternalSettingsGenerated::setDOMPasteAccessRequestsEnabled(bool domPasteAccessRequestsEnabled)
{
    m_page->settings().setDOMPasteAccessRequestsEnabled(domPasteAccessRequestsEnabled);
}

void InternalSettingsGenerated::setDOMPasteAllowed(bool domPasteAllowed)
{
    m_page->settings().setDOMPasteAllowed(domPasteAllowed);
}

void InternalSettingsGenerated::setDOMTestingAPIsEnabled(bool domTestingAPIsEnabled)
{
    m_page->settings().setDOMTestingAPIsEnabled(domTestingAPIsEnabled);
}

void InternalSettingsGenerated::setDOMTimersThrottlingEnabled(bool domTimersThrottlingEnabled)
{
    m_page->settings().setDOMTimersThrottlingEnabled(domTimersThrottlingEnabled);
}

void InternalSettingsGenerated::setDownloadAttributeEnabled(bool downloadAttributeEnabled)
{
#if ENABLE(DOWNLOAD_ATTRIBUTE)
    m_page->settings().setDownloadAttributeEnabled(downloadAttributeEnabled);
#else
    UNUSED_PARAM(downloadAttributeEnabled);
#endif
}

void InternalSettingsGenerated::setEmbedElementEnabled(bool embedElementEnabled)
{
    m_page->settings().setEmbedElementEnabled(embedElementEnabled);
}

void InternalSettingsGenerated::setEnableInheritURIQueryComponent(bool enableInheritURIQueryComponent)
{
    m_page->settings().setEnableInheritURIQueryComponent(enableInheritURIQueryComponent);
}

void InternalSettingsGenerated::setEncryptedMediaAPIEnabled(bool encryptedMediaAPIEnabled)
{
#if ENABLE(ENCRYPTED_MEDIA)
    m_page->settings().setEncryptedMediaAPIEnabled(encryptedMediaAPIEnabled);
#else
    UNUSED_PARAM(encryptedMediaAPIEnabled);
#endif
}

void InternalSettingsGenerated::setEnterKeyHintEnabled(bool enterKeyHintEnabled)
{
    m_page->settings().setEnterKeyHintEnabled(enterKeyHintEnabled);
}

void InternalSettingsGenerated::setEventHandlerDrivenSmoothKeyboardScrollingEnabled(bool eventHandlerDrivenSmoothKeyboardScrollingEnabled)
{
    m_page->settings().setEventHandlerDrivenSmoothKeyboardScrollingEnabled(eventHandlerDrivenSmoothKeyboardScrollingEnabled);
}

void InternalSettingsGenerated::setExposeSpeakersEnabled(bool exposeSpeakersEnabled)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setExposeSpeakersEnabled(exposeSpeakersEnabled);
#else
    UNUSED_PARAM(exposeSpeakersEnabled);
#endif
}

void InternalSettingsGenerated::setExtendedAudioDescriptionsEnabled(bool extendedAudioDescriptionsEnabled)
{
#if ENABLE(VIDEO)
    m_page->settings().setExtendedAudioDescriptionsEnabled(extendedAudioDescriptionsEnabled);
#else
    UNUSED_PARAM(extendedAudioDescriptionsEnabled);
#endif
}

void InternalSettingsGenerated::setFantasyFontFamily(const String& fantasyFontFamily)
{
    m_page->settings().setFantasyFontFamily(fantasyFontFamily);
}

void InternalSettingsGenerated::setFetchAPIEnabled(bool fetchAPIEnabled)
{
    m_page->settings().setFetchAPIEnabled(fetchAPIEnabled);
}

void InternalSettingsGenerated::setFetchMetadataEnabled(bool fetchMetadataEnabled)
{
    m_page->settings().setFetchMetadataEnabled(fetchMetadataEnabled);
}

void InternalSettingsGenerated::setFetchPriorityEnabled(bool fetchPriorityEnabled)
{
    m_page->settings().setFetchPriorityEnabled(fetchPriorityEnabled);
}

void InternalSettingsGenerated::setFileReaderAPIEnabled(bool fileReaderAPIEnabled)
{
    m_page->settings().setFileReaderAPIEnabled(fileReaderAPIEnabled);
}

void InternalSettingsGenerated::setFileSystemAccessEnabled(bool fileSystemAccessEnabled)
{
    m_page->settings().setFileSystemAccessEnabled(fileSystemAccessEnabled);
}

void InternalSettingsGenerated::setFixedBackgroundsPaintRelativeToDocument(bool fixedBackgroundsPaintRelativeToDocument)
{
    m_page->settings().setFixedBackgroundsPaintRelativeToDocument(fixedBackgroundsPaintRelativeToDocument);
}

void InternalSettingsGenerated::setFixedElementsLayoutRelativeToFrame(bool fixedElementsLayoutRelativeToFrame)
{
    m_page->settings().setFixedElementsLayoutRelativeToFrame(fixedElementsLayoutRelativeToFrame);
}

void InternalSettingsGenerated::setFixedFontFamily(const String& fixedFontFamily)
{
    m_page->settings().setFixedFontFamily(fixedFontFamily);
}

void InternalSettingsGenerated::setFlexFormattingContextIntegrationEnabled(bool flexFormattingContextIntegrationEnabled)
{
    m_page->settings().setFlexFormattingContextIntegrationEnabled(flexFormattingContextIntegrationEnabled);
}

void InternalSettingsGenerated::setFocusVisibleEnabled(bool focusVisibleEnabled)
{
    m_page->settings().setFocusVisibleEnabled(focusVisibleEnabled);
}

void InternalSettingsGenerated::setFontFallbackPrefersPictographs(bool fontFallbackPrefersPictographs)
{
    m_page->settings().setFontFallbackPrefersPictographs(fontFallbackPrefersPictographs);
}

void InternalSettingsGenerated::setForceCompositingMode(bool forceCompositingMode)
{
    m_page->settings().setForceCompositingMode(forceCompositingMode);
}

void InternalSettingsGenerated::setForceFTPDirectoryListings(bool forceFTPDirectoryListings)
{
    m_page->settings().setForceFTPDirectoryListings(forceFTPDirectoryListings);
}

void InternalSettingsGenerated::setForceWebGLUsesLowPower(bool forceWebGLUsesLowPower)
{
    m_page->settings().setForceWebGLUsesLowPower(forceWebGLUsesLowPower);
}

void InternalSettingsGenerated::setFormAssociatedCustomElementsEnabled(bool formAssociatedCustomElementsEnabled)
{
    m_page->settings().setFormAssociatedCustomElementsEnabled(formAssociatedCustomElementsEnabled);
}

void InternalSettingsGenerated::setFTPDirectoryTemplatePath(const String& ftpDirectoryTemplatePath)
{
    m_page->settings().setFTPDirectoryTemplatePath(ftpDirectoryTemplatePath);
}

void InternalSettingsGenerated::setFTPEnabled(bool ftpEnabled)
{
    m_page->settings().setFTPEnabled(ftpEnabled);
}

void InternalSettingsGenerated::setFullScreenEnabled(bool fullScreenEnabled)
{
#if ENABLE(FULLSCREEN_API)
    m_page->settings().setFullScreenEnabled(fullScreenEnabled);
#else
    UNUSED_PARAM(fullScreenEnabled);
#endif
}

void InternalSettingsGenerated::setFullscreenRequirementForScreenOrientationLockingEnabled(bool fullscreenRequirementForScreenOrientationLockingEnabled)
{
    m_page->settings().setFullscreenRequirementForScreenOrientationLockingEnabled(fullscreenRequirementForScreenOrientationLockingEnabled);
}

void InternalSettingsGenerated::setFullscreenSceneAspectRatioLockingEnabled(bool fullscreenSceneAspectRatioLockingEnabled)
{
#if PLATFORM(VISION)
    m_page->settings().setFullscreenSceneAspectRatioLockingEnabled(fullscreenSceneAspectRatioLockingEnabled);
#else
    UNUSED_PARAM(fullscreenSceneAspectRatioLockingEnabled);
#endif
}

void InternalSettingsGenerated::setFullscreenSceneDimmingEnabled(bool fullscreenSceneDimmingEnabled)
{
#if PLATFORM(VISION)
    m_page->settings().setFullscreenSceneDimmingEnabled(fullscreenSceneDimmingEnabled);
#else
    UNUSED_PARAM(fullscreenSceneDimmingEnabled);
#endif
}

void InternalSettingsGenerated::setGamepadTriggerRumbleEnabled(bool gamepadTriggerRumbleEnabled)
{
#if ENABLE(GAMEPAD)
    m_page->settings().setGamepadTriggerRumbleEnabled(gamepadTriggerRumbleEnabled);
#else
    UNUSED_PARAM(gamepadTriggerRumbleEnabled);
#endif
}

void InternalSettingsGenerated::setGamepadVibrationActuatorEnabled(bool gamepadVibrationActuatorEnabled)
{
#if ENABLE(GAMEPAD)
    m_page->settings().setGamepadVibrationActuatorEnabled(gamepadVibrationActuatorEnabled);
#else
    UNUSED_PARAM(gamepadVibrationActuatorEnabled);
#endif
}

void InternalSettingsGenerated::setGamepadsEnabled(bool gamepadsEnabled)
{
#if ENABLE(GAMEPAD)
    m_page->settings().setGamepadsEnabled(gamepadsEnabled);
#else
    UNUSED_PARAM(gamepadsEnabled);
#endif
}

void InternalSettingsGenerated::setGenericCueAPIEnabled(bool genericCueAPIEnabled)
{
#if ENABLE(VIDEO)
    m_page->settings().setGenericCueAPIEnabled(genericCueAPIEnabled);
#else
    UNUSED_PARAM(genericCueAPIEnabled);
#endif
}

void InternalSettingsGenerated::setGeolocationFloorLevelEnabled(bool geolocationFloorLevelEnabled)
{
    m_page->settings().setGeolocationFloorLevelEnabled(geolocationFloorLevelEnabled);
}

void InternalSettingsGenerated::setGetUserMediaRequiresFocus(bool getUserMediaRequiresFocus)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setGetUserMediaRequiresFocus(getUserMediaRequiresFocus);
#else
    UNUSED_PARAM(getUserMediaRequiresFocus);
#endif
}

void InternalSettingsGenerated::setGoogleAntiFlickerOptimizationQuirkEnabled(bool googleAntiFlickerOptimizationQuirkEnabled)
{
    m_page->settings().setGoogleAntiFlickerOptimizationQuirkEnabled(googleAntiFlickerOptimizationQuirkEnabled);
}

void InternalSettingsGenerated::setGraphicsContextFiltersEnabled(bool graphicsContextFiltersEnabled)
{
#if USE(GRAPHICS_CONTEXT_FILTERS)
    m_page->settings().setGraphicsContextFiltersEnabled(graphicsContextFiltersEnabled);
#else
    UNUSED_PARAM(graphicsContextFiltersEnabled);
#endif
}

void InternalSettingsGenerated::setHasPseudoClassEnabled(bool hasPseudoClassEnabled)
{
    m_page->settings().setHasPseudoClassEnabled(hasPseudoClassEnabled);
}

void InternalSettingsGenerated::setHiddenPageCSSAnimationSuspensionEnabled(bool hiddenPageCSSAnimationSuspensionEnabled)
{
    m_page->settings().setHiddenPageCSSAnimationSuspensionEnabled(hiddenPageCSSAnimationSuspensionEnabled);
}

void InternalSettingsGenerated::setHiddenPageDOMTimerThrottlingAutoIncreases(bool hiddenPageDOMTimerThrottlingAutoIncreases)
{
    m_page->settings().setHiddenPageDOMTimerThrottlingAutoIncreases(hiddenPageDOMTimerThrottlingAutoIncreases);
}

void InternalSettingsGenerated::setHiddenPageDOMTimerThrottlingEnabled(bool hiddenPageDOMTimerThrottlingEnabled)
{
    m_page->settings().setHiddenPageDOMTimerThrottlingEnabled(hiddenPageDOMTimerThrottlingEnabled);
}

void InternalSettingsGenerated::setHttpEquivEnabled(bool httpEquivEnabled)
{
    m_page->settings().setHttpEquivEnabled(httpEquivEnabled);
}

void InternalSettingsGenerated::setHyperlinkAuditingEnabled(bool hyperlinkAuditingEnabled)
{
    m_page->settings().setHyperlinkAuditingEnabled(hyperlinkAuditingEnabled);
}

void InternalSettingsGenerated::setIOSFormControlRefreshEnabled(bool iOSFormControlRefreshEnabled)
{
#if ENABLE(IOS_FORM_CONTROL_REFRESH)
    m_page->settings().setIOSFormControlRefreshEnabled(iOSFormControlRefreshEnabled);
#else
    UNUSED_PARAM(iOSFormControlRefreshEnabled);
#endif
}

void InternalSettingsGenerated::setICECandidateFilteringEnabled(bool iceCandidateFilteringEnabled)
{
    m_page->settings().setICECandidateFilteringEnabled(iceCandidateFilteringEnabled);
}

void InternalSettingsGenerated::setIdempotentModeAutosizingOnlyHonorsPercentages(bool idempotentModeAutosizingOnlyHonorsPercentages)
{
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setIdempotentModeAutosizingOnlyHonorsPercentages(idempotentModeAutosizingOnlyHonorsPercentages);
#else
    UNUSED_PARAM(idempotentModeAutosizingOnlyHonorsPercentages);
#endif
}

void InternalSettingsGenerated::setImageAnalysisDuringFindInPageEnabled(bool imageAnalysisDuringFindInPageEnabled)
{
#if ENABLE(IMAGE_ANALYSIS)
    m_page->settings().setImageAnalysisDuringFindInPageEnabled(imageAnalysisDuringFindInPageEnabled);
#else
    UNUSED_PARAM(imageAnalysisDuringFindInPageEnabled);
#endif
}

void InternalSettingsGenerated::setImageAnimationControlEnabled(bool imageAnimationControlEnabled)
{
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    m_page->settings().setImageAnimationControlEnabled(imageAnimationControlEnabled);
#else
    UNUSED_PARAM(imageAnimationControlEnabled);
#endif
}

void InternalSettingsGenerated::setImageControlsEnabled(bool imageControlsEnabled)
{
#if ENABLE(SERVICE_CONTROLS)
    m_page->settings().setImageControlsEnabled(imageControlsEnabled);
#else
    UNUSED_PARAM(imageControlsEnabled);
#endif
}

void InternalSettingsGenerated::setImageSubsamplingEnabled(bool imageSubsamplingEnabled)
{
    m_page->settings().setImageSubsamplingEnabled(imageSubsamplingEnabled);
}

void InternalSettingsGenerated::setImagesEnabled(bool imagesEnabled)
{
    m_page->settings().setImagesEnabled(imagesEnabled);
}

void InternalSettingsGenerated::setImperativeSlotAPIEnabled(bool imperativeSlotAPIEnabled)
{
    m_page->settings().setImperativeSlotAPIEnabled(imperativeSlotAPIEnabled);
}

void InternalSettingsGenerated::setIncompleteImageBorderEnabled(bool incompleteImageBorderEnabled)
{
    m_page->settings().setIncompleteImageBorderEnabled(incompleteImageBorderEnabled);
}

void InternalSettingsGenerated::setIncrementalPDFLoadingEnabled(bool incrementalPDFLoadingEnabled)
{
#if HAVE(INCREMENTAL_PDF_APIS)
    m_page->settings().setIncrementalPDFLoadingEnabled(incrementalPDFLoadingEnabled);
#else
    UNUSED_PARAM(incrementalPDFLoadingEnabled);
#endif
}

void InternalSettingsGenerated::setIncrementalRenderingSuppressionTimeoutInSeconds(double incrementalRenderingSuppressionTimeoutInSeconds)
{
    m_page->settings().setIncrementalRenderingSuppressionTimeoutInSeconds(incrementalRenderingSuppressionTimeoutInSeconds);
}

void InternalSettingsGenerated::setIndexedDBAPIEnabled(bool indexedDBAPIEnabled)
{
    m_page->settings().setIndexedDBAPIEnabled(indexedDBAPIEnabled);
}

void InternalSettingsGenerated::setInertAttributeEnabled(bool inertAttributeEnabled)
{
    m_page->settings().setInertAttributeEnabled(inertAttributeEnabled);
}

void InternalSettingsGenerated::setInlineMediaPlaybackRequiresPlaysInlineAttribute(bool inlineMediaPlaybackRequiresPlaysInlineAttribute)
{
    m_page->settings().setInlineMediaPlaybackRequiresPlaysInlineAttribute(inlineMediaPlaybackRequiresPlaysInlineAttribute);
}

void InternalSettingsGenerated::setInlinePredictionsInAllEditableElementsEnabled(bool inlinePredictionsInAllEditableElementsEnabled)
{
    m_page->settings().setInlinePredictionsInAllEditableElementsEnabled(inlinePredictionsInAllEditableElementsEnabled);
}

void InternalSettingsGenerated::setInputTypeColorEnabled(bool inputTypeColorEnabled)
{
#if ENABLE(INPUT_TYPE_COLOR)
    m_page->settings().setInputTypeColorEnabled(inputTypeColorEnabled);
#else
    UNUSED_PARAM(inputTypeColorEnabled);
#endif
}

void InternalSettingsGenerated::setInputTypeDateEnabled(bool inputTypeDateEnabled)
{
#if ENABLE(INPUT_TYPE_DATE)
    m_page->settings().setInputTypeDateEnabled(inputTypeDateEnabled);
#else
    UNUSED_PARAM(inputTypeDateEnabled);
#endif
}

void InternalSettingsGenerated::setInputTypeDateTimeLocalEnabled(bool inputTypeDateTimeLocalEnabled)
{
#if ENABLE(INPUT_TYPE_DATETIMELOCAL)
    m_page->settings().setInputTypeDateTimeLocalEnabled(inputTypeDateTimeLocalEnabled);
#else
    UNUSED_PARAM(inputTypeDateTimeLocalEnabled);
#endif
}

void InternalSettingsGenerated::setInputTypeMonthEnabled(bool inputTypeMonthEnabled)
{
#if ENABLE(INPUT_TYPE_MONTH)
    m_page->settings().setInputTypeMonthEnabled(inputTypeMonthEnabled);
#else
    UNUSED_PARAM(inputTypeMonthEnabled);
#endif
}

void InternalSettingsGenerated::setInputTypeTimeEnabled(bool inputTypeTimeEnabled)
{
#if ENABLE(INPUT_TYPE_TIME)
    m_page->settings().setInputTypeTimeEnabled(inputTypeTimeEnabled);
#else
    UNUSED_PARAM(inputTypeTimeEnabled);
#endif
}

void InternalSettingsGenerated::setInputTypeWeekEnabled(bool inputTypeWeekEnabled)
{
#if ENABLE(INPUT_TYPE_WEEK)
    m_page->settings().setInputTypeWeekEnabled(inputTypeWeekEnabled);
#else
    UNUSED_PARAM(inputTypeWeekEnabled);
#endif
}

void InternalSettingsGenerated::setInteractionRegionInlinePadding(double interactionRegionInlinePadding)
{
    m_page->settings().setInteractionRegionInlinePadding(interactionRegionInlinePadding);
}

void InternalSettingsGenerated::setInteractionRegionMinimumCornerRadius(double interactionRegionMinimumCornerRadius)
{
    m_page->settings().setInteractionRegionMinimumCornerRadius(interactionRegionMinimumCornerRadius);
}

void InternalSettingsGenerated::setInteractionRegionsEnabled(bool interactionRegionsEnabled)
{
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
    m_page->settings().setInteractionRegionsEnabled(interactionRegionsEnabled);
#else
    UNUSED_PARAM(interactionRegionsEnabled);
#endif
}

void InternalSettingsGenerated::setInteractiveFormValidationEnabled(bool interactiveFormValidationEnabled)
{
    m_page->settings().setInteractiveFormValidationEnabled(interactiveFormValidationEnabled);
}

void InternalSettingsGenerated::setInterruptAudioOnPageVisibilityChangeEnabled(bool interruptAudioOnPageVisibilityChangeEnabled)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setInterruptAudioOnPageVisibilityChangeEnabled(interruptAudioOnPageVisibilityChangeEnabled);
#else
    UNUSED_PARAM(interruptAudioOnPageVisibilityChangeEnabled);
#endif
}

void InternalSettingsGenerated::setInterruptVideoOnPageVisibilityChangeEnabled(bool interruptVideoOnPageVisibilityChangeEnabled)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setInterruptVideoOnPageVisibilityChangeEnabled(interruptVideoOnPageVisibilityChangeEnabled);
#else
    UNUSED_PARAM(interruptVideoOnPageVisibilityChangeEnabled);
#endif
}

void InternalSettingsGenerated::setIntersectionObserverEnabled(bool intersectionObserverEnabled)
{
    m_page->settings().setIntersectionObserverEnabled(intersectionObserverEnabled);
}

void InternalSettingsGenerated::setInvisibleAutoplayNotPermitted(bool invisibleAutoplayNotPermitted)
{
    m_page->settings().setInvisibleAutoplayNotPermitted(invisibleAutoplayNotPermitted);
}

void InternalSettingsGenerated::setIsFirstPartyWebsiteDataRemovalDisabled(bool isFirstPartyWebsiteDataRemovalDisabled)
{
    m_page->settings().setIsFirstPartyWebsiteDataRemovalDisabled(isFirstPartyWebsiteDataRemovalDisabled);
}

void InternalSettingsGenerated::setIsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled(bool isFirstPartyWebsiteDataRemovalLiveOnTestingEnabled)
{
    m_page->settings().setIsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled(isFirstPartyWebsiteDataRemovalLiveOnTestingEnabled);
}

void InternalSettingsGenerated::setIsFirstPartyWebsiteDataRemovalReproTestingEnabled(bool isFirstPartyWebsiteDataRemovalReproTestingEnabled)
{
    m_page->settings().setIsFirstPartyWebsiteDataRemovalReproTestingEnabled(isFirstPartyWebsiteDataRemovalReproTestingEnabled);
}

void InternalSettingsGenerated::setIsLoggedInAPIEnabled(bool isLoggedInAPIEnabled)
{
    m_page->settings().setIsLoggedInAPIEnabled(isLoggedInAPIEnabled);
}

void InternalSettingsGenerated::setIsPerActivityStateCPUUsageMeasurementEnabled(bool isPerActivityStateCPUUsageMeasurementEnabled)
{
    m_page->settings().setIsPerActivityStateCPUUsageMeasurementEnabled(isPerActivityStateCPUUsageMeasurementEnabled);
}

void InternalSettingsGenerated::setIsPostBackgroundingCPUUsageMeasurementEnabled(bool isPostBackgroundingCPUUsageMeasurementEnabled)
{
    m_page->settings().setIsPostBackgroundingCPUUsageMeasurementEnabled(isPostBackgroundingCPUUsageMeasurementEnabled);
}

void InternalSettingsGenerated::setIsPostBackgroundingMemoryUsageMeasurementEnabled(bool isPostBackgroundingMemoryUsageMeasurementEnabled)
{
    m_page->settings().setIsPostBackgroundingMemoryUsageMeasurementEnabled(isPostBackgroundingMemoryUsageMeasurementEnabled);
}

void InternalSettingsGenerated::setIsPostLoadCPUUsageMeasurementEnabled(bool isPostLoadCPUUsageMeasurementEnabled)
{
    m_page->settings().setIsPostLoadCPUUsageMeasurementEnabled(isPostLoadCPUUsageMeasurementEnabled);
}

void InternalSettingsGenerated::setIsPostLoadMemoryUsageMeasurementEnabled(bool isPostLoadMemoryUsageMeasurementEnabled)
{
    m_page->settings().setIsPostLoadMemoryUsageMeasurementEnabled(isPostLoadMemoryUsageMeasurementEnabled);
}

void InternalSettingsGenerated::setIsSameSiteStrictEnforcementEnabled(bool isSameSiteStrictEnforcementEnabled)
{
    m_page->settings().setIsSameSiteStrictEnforcementEnabled(isSameSiteStrictEnforcementEnabled);
}

void InternalSettingsGenerated::setIsThirdPartyCookieBlockingDisabled(bool isThirdPartyCookieBlockingDisabled)
{
    m_page->settings().setIsThirdPartyCookieBlockingDisabled(isThirdPartyCookieBlockingDisabled);
}

void InternalSettingsGenerated::setItpDebugModeEnabled(bool itpDebugModeEnabled)
{
    m_page->settings().setItpDebugModeEnabled(itpDebugModeEnabled);
}

void InternalSettingsGenerated::setJavaScriptCanAccessClipboard(bool javaScriptCanAccessClipboard)
{
    m_page->settings().setJavaScriptCanAccessClipboard(javaScriptCanAccessClipboard);
}

void InternalSettingsGenerated::setJavaScriptCanOpenWindowsAutomatically(bool javaScriptCanOpenWindowsAutomatically)
{
    m_page->settings().setJavaScriptCanOpenWindowsAutomatically(javaScriptCanOpenWindowsAutomatically);
}

void InternalSettingsGenerated::setLangAttributeAwareFormControlUIEnabled(bool langAttributeAwareFormControlUIEnabled)
{
    m_page->settings().setLangAttributeAwareFormControlUIEnabled(langAttributeAwareFormControlUIEnabled);
}

void InternalSettingsGenerated::setLargeImageAsyncDecodingEnabled(bool largeImageAsyncDecodingEnabled)
{
    m_page->settings().setLargeImageAsyncDecodingEnabled(largeImageAsyncDecodingEnabled);
}

void InternalSettingsGenerated::setLayerBasedSVGEngineEnabled(bool layerBasedSVGEngineEnabled)
{
#if ENABLE(LAYER_BASED_SVG_ENGINE)
    m_page->settings().setLayerBasedSVGEngineEnabled(layerBasedSVGEngineEnabled);
#else
    UNUSED_PARAM(layerBasedSVGEngineEnabled);
#endif
}

void InternalSettingsGenerated::setLayoutFallbackWidth(uint32_t layoutFallbackWidth)
{
    m_page->settings().setLayoutFallbackWidth(layoutFallbackWidth);
}

void InternalSettingsGenerated::setLayoutFormattingContextEnabled(bool layoutFormattingContextEnabled)
{
    m_page->settings().setLayoutFormattingContextEnabled(layoutFormattingContextEnabled);
}

void InternalSettingsGenerated::setLayoutViewportHeightExpansionFactor(double layoutViewportHeightExpansionFactor)
{
    m_page->settings().setLayoutViewportHeightExpansionFactor(layoutViewportHeightExpansionFactor);
}

void InternalSettingsGenerated::setLazyIframeLoadingEnabled(bool lazyIframeLoadingEnabled)
{
    m_page->settings().setLazyIframeLoadingEnabled(lazyIframeLoadingEnabled);
}

void InternalSettingsGenerated::setLazyImageLoadingEnabled(bool lazyImageLoadingEnabled)
{
    m_page->settings().setLazyImageLoadingEnabled(lazyImageLoadingEnabled);
}

void InternalSettingsGenerated::setLegacyEncryptedMediaAPIEnabled(bool legacyEncryptedMediaAPIEnabled)
{
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    m_page->settings().setLegacyEncryptedMediaAPIEnabled(legacyEncryptedMediaAPIEnabled);
#else
    UNUSED_PARAM(legacyEncryptedMediaAPIEnabled);
#endif
}

void InternalSettingsGenerated::setLegacyLineLayoutVisualCoverageEnabled(bool legacyLineLayoutVisualCoverageEnabled)
{
    m_page->settings().setLegacyLineLayoutVisualCoverageEnabled(legacyLineLayoutVisualCoverageEnabled);
}

void InternalSettingsGenerated::setLegacyOverflowScrollingTouchEnabled(bool legacyOverflowScrollingTouchEnabled)
{
#if ENABLE(OVERFLOW_SCROLLING_TOUCH)
    m_page->settings().setLegacyOverflowScrollingTouchEnabled(legacyOverflowScrollingTouchEnabled);
#else
    UNUSED_PARAM(legacyOverflowScrollingTouchEnabled);
#endif
}

void InternalSettingsGenerated::setLinkModulePreloadEnabled(bool linkModulePreloadEnabled)
{
    m_page->settings().setLinkModulePreloadEnabled(linkModulePreloadEnabled);
}

void InternalSettingsGenerated::setLinkPreconnectEarlyHintsEnabled(bool linkPreconnectEarlyHintsEnabled)
{
    m_page->settings().setLinkPreconnectEarlyHintsEnabled(linkPreconnectEarlyHintsEnabled);
}

void InternalSettingsGenerated::setLinkPreconnectEnabled(bool linkPreconnectEnabled)
{
    m_page->settings().setLinkPreconnectEnabled(linkPreconnectEnabled);
}

void InternalSettingsGenerated::setLinkPrefetchEnabled(bool linkPrefetchEnabled)
{
    m_page->settings().setLinkPrefetchEnabled(linkPrefetchEnabled);
}

void InternalSettingsGenerated::setLinkPreloadEnabled(bool linkPreloadEnabled)
{
    m_page->settings().setLinkPreloadEnabled(linkPreloadEnabled);
}

void InternalSettingsGenerated::setLinkPreloadResponsiveImagesEnabled(bool linkPreloadResponsiveImagesEnabled)
{
    m_page->settings().setLinkPreloadResponsiveImagesEnabled(linkPreloadResponsiveImagesEnabled);
}

void InternalSettingsGenerated::setLinkSanitizerEnabled(bool linkSanitizerEnabled)
{
    m_page->settings().setLinkSanitizerEnabled(linkSanitizerEnabled);
}

void InternalSettingsGenerated::setLiveRangeSelectionEnabled(bool liveRangeSelectionEnabled)
{
    m_page->settings().setLiveRangeSelectionEnabled(liveRangeSelectionEnabled);
}

void InternalSettingsGenerated::setLoadDeferringEnabled(bool loadDeferringEnabled)
{
    m_page->settings().setLoadDeferringEnabled(loadDeferringEnabled);
}

void InternalSettingsGenerated::setLoadsImagesAutomatically(bool loadsImagesAutomatically)
{
    m_page->settings().setLoadsImagesAutomatically(loadsImagesAutomatically);
}

void InternalSettingsGenerated::setLocalFileContentSniffingEnabled(bool localFileContentSniffingEnabled)
{
    m_page->settings().setLocalFileContentSniffingEnabled(localFileContentSniffingEnabled);
}

void InternalSettingsGenerated::setLocalStorageDatabasePath(const String& localStorageDatabasePath)
{
    m_page->settings().setLocalStorageDatabasePath(localStorageDatabasePath);
}

void InternalSettingsGenerated::setLocalStorageEnabled(bool localStorageEnabled)
{
    m_page->settings().setLocalStorageEnabled(localStorageEnabled);
}

void InternalSettingsGenerated::setLogsPageMessagesToSystemConsoleEnabled(bool logsPageMessagesToSystemConsoleEnabled)
{
    m_page->settings().setLogsPageMessagesToSystemConsoleEnabled(logsPageMessagesToSystemConsoleEnabled);
}

void InternalSettingsGenerated::setMainContentUserGestureOverrideEnabled(bool mainContentUserGestureOverrideEnabled)
{
    m_page->settings().setMainContentUserGestureOverrideEnabled(mainContentUserGestureOverrideEnabled);
}

void InternalSettingsGenerated::setManageCaptureStatusBarInGPUProcessEnabled(bool manageCaptureStatusBarInGPUProcessEnabled)
{
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
    m_page->settings().setManageCaptureStatusBarInGPUProcessEnabled(manageCaptureStatusBarInGPUProcessEnabled);
#else
    UNUSED_PARAM(manageCaptureStatusBarInGPUProcessEnabled);
#endif
}

void InternalSettingsGenerated::setManagedMediaSourceEnabled(bool managedMediaSourceEnabled)
{
#if ENABLE(MANAGED_MEDIA_SOURCE)
    m_page->settings().setManagedMediaSourceEnabled(managedMediaSourceEnabled);
#else
    UNUSED_PARAM(managedMediaSourceEnabled);
#endif
}

void InternalSettingsGenerated::setManagedMediaSourceHighThreshold(double managedMediaSourceHighThreshold)
{
#if ENABLE(MANAGED_MEDIA_SOURCE)
    m_page->settings().setManagedMediaSourceHighThreshold(managedMediaSourceHighThreshold);
#else
    UNUSED_PARAM(managedMediaSourceHighThreshold);
#endif
}

void InternalSettingsGenerated::setManagedMediaSourceLowThreshold(double managedMediaSourceLowThreshold)
{
#if ENABLE(MANAGED_MEDIA_SOURCE)
    m_page->settings().setManagedMediaSourceLowThreshold(managedMediaSourceLowThreshold);
#else
    UNUSED_PARAM(managedMediaSourceLowThreshold);
#endif
}

void InternalSettingsGenerated::setManagedMediaSourceNeedsAirPlay(bool managedMediaSourceNeedsAirPlay)
{
#if ENABLE(MANAGED_MEDIA_SOURCE) && ENABLE(WIRELESS_PLAYBACK_TARGET)
    m_page->settings().setManagedMediaSourceNeedsAirPlay(managedMediaSourceNeedsAirPlay);
#else
    UNUSED_PARAM(managedMediaSourceNeedsAirPlay);
#endif
}

void InternalSettingsGenerated::setMaskWebGLStringsEnabled(bool maskWebGLStringsEnabled)
{
#if ENABLE(WEBGL)
    m_page->settings().setMaskWebGLStringsEnabled(maskWebGLStringsEnabled);
#else
    UNUSED_PARAM(maskWebGLStringsEnabled);
#endif
}

void InternalSettingsGenerated::setMasonryEnabled(bool masonryEnabled)
{
    m_page->settings().setMasonryEnabled(masonryEnabled);
}

void InternalSettingsGenerated::setMasonryTrackAlignmentEnabled(bool masonryTrackAlignmentEnabled)
{
    m_page->settings().setMasonryTrackAlignmentEnabled(masonryTrackAlignmentEnabled);
}

void InternalSettingsGenerated::setMathMLEnabled(bool mathMLEnabled)
{
#if ENABLE(MATHML)
    m_page->settings().setMathMLEnabled(mathMLEnabled);
#else
    UNUSED_PARAM(mathMLEnabled);
#endif
}

void InternalSettingsGenerated::setMaxParseDuration(double maxParseDuration)
{
    m_page->settings().setMaxParseDuration(maxParseDuration);
}

void InternalSettingsGenerated::setMaximumAccelerated2dCanvasSize(uint32_t maximumAccelerated2dCanvasSize)
{
    m_page->settings().setMaximumAccelerated2dCanvasSize(maximumAccelerated2dCanvasSize);
}

void InternalSettingsGenerated::setMaximumHTMLParserDOMTreeDepth(uint32_t maximumHTMLParserDOMTreeDepth)
{
    m_page->settings().setMaximumHTMLParserDOMTreeDepth(maximumHTMLParserDOMTreeDepth);
}

void InternalSettingsGenerated::setMaximumSourceBufferSize(uint32_t maximumSourceBufferSize)
{
#if ENABLE(MEDIA_SOURCE)
    m_page->settings().setMaximumSourceBufferSize(maximumSourceBufferSize);
#else
    UNUSED_PARAM(maximumSourceBufferSize);
#endif
}

void InternalSettingsGenerated::setMediaCapabilitiesEnabled(bool mediaCapabilitiesEnabled)
{
    m_page->settings().setMediaCapabilitiesEnabled(mediaCapabilitiesEnabled);
}

void InternalSettingsGenerated::setMediaCapabilitiesExtensionsEnabled(bool mediaCapabilitiesExtensionsEnabled)
{
    m_page->settings().setMediaCapabilitiesExtensionsEnabled(mediaCapabilitiesExtensionsEnabled);
}

void InternalSettingsGenerated::setMediaCaptureRequiresSecureConnection(bool mediaCaptureRequiresSecureConnection)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setMediaCaptureRequiresSecureConnection(mediaCaptureRequiresSecureConnection);
#else
    UNUSED_PARAM(mediaCaptureRequiresSecureConnection);
#endif
}

void InternalSettingsGenerated::setMediaControlsContextMenusEnabled(bool mediaControlsContextMenusEnabled)
{
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS)
    m_page->settings().setMediaControlsContextMenusEnabled(mediaControlsContextMenusEnabled);
#else
    UNUSED_PARAM(mediaControlsContextMenusEnabled);
#endif
}

void InternalSettingsGenerated::setMediaControlsScaleWithPageZoom(bool mediaControlsScaleWithPageZoom)
{
    m_page->settings().setMediaControlsScaleWithPageZoom(mediaControlsScaleWithPageZoom);
}

void InternalSettingsGenerated::setMediaDataLoadsAutomatically(bool mediaDataLoadsAutomatically)
{
    m_page->settings().setMediaDataLoadsAutomatically(mediaDataLoadsAutomatically);
}

void InternalSettingsGenerated::setMediaDevicesEnabled(bool mediaDevicesEnabled)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setMediaDevicesEnabled(mediaDevicesEnabled);
#else
    UNUSED_PARAM(mediaDevicesEnabled);
#endif
}

void InternalSettingsGenerated::setMediaEnabled(bool mediaEnabled)
{
#if ENABLE(VIDEO)
    m_page->settings().setMediaEnabled(mediaEnabled);
#else
    UNUSED_PARAM(mediaEnabled);
#endif
}

void InternalSettingsGenerated::setMediaKeysStorageDirectory(const String& mediaKeysStorageDirectory)
{
    m_page->settings().setMediaKeysStorageDirectory(mediaKeysStorageDirectory);
}

void InternalSettingsGenerated::setMediaPreferredFullscreenWidth(double mediaPreferredFullscreenWidth)
{
    m_page->settings().setMediaPreferredFullscreenWidth(mediaPreferredFullscreenWidth);
}

void InternalSettingsGenerated::setMediaPreloadingEnabled(bool mediaPreloadingEnabled)
{
    m_page->settings().setMediaPreloadingEnabled(mediaPreloadingEnabled);
}

void InternalSettingsGenerated::setMediaRecorderEnabled(bool mediaRecorderEnabled)
{
#if ENABLE(MEDIA_RECORDER)
    m_page->settings().setMediaRecorderEnabled(mediaRecorderEnabled);
#else
    UNUSED_PARAM(mediaRecorderEnabled);
#endif
}

void InternalSettingsGenerated::setMediaSessionCoordinatorEnabled(bool mediaSessionCoordinatorEnabled)
{
#if ENABLE(MEDIA_SESSION_COORDINATOR)
    m_page->settings().setMediaSessionCoordinatorEnabled(mediaSessionCoordinatorEnabled);
#else
    UNUSED_PARAM(mediaSessionCoordinatorEnabled);
#endif
}

void InternalSettingsGenerated::setMediaSessionEnabled(bool mediaSessionEnabled)
{
#if ENABLE(MEDIA_SESSION)
    m_page->settings().setMediaSessionEnabled(mediaSessionEnabled);
#else
    UNUSED_PARAM(mediaSessionEnabled);
#endif
}

void InternalSettingsGenerated::setMediaSessionPlaylistEnabled(bool mediaSessionPlaylistEnabled)
{
#if ENABLE(MEDIA_SESSION_COORDINATOR) && ENABLE(MEDIA_SESSION_PLAYLIST)
    m_page->settings().setMediaSessionPlaylistEnabled(mediaSessionPlaylistEnabled);
#else
    UNUSED_PARAM(mediaSessionPlaylistEnabled);
#endif
}

void InternalSettingsGenerated::setMediaSourceEnabled(bool mediaSourceEnabled)
{
    m_page->settings().setMediaSourceEnabled(mediaSourceEnabled);
}

void InternalSettingsGenerated::setMediaStreamEnabled(bool mediaStreamEnabled)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setMediaStreamEnabled(mediaStreamEnabled);
#else
    UNUSED_PARAM(mediaStreamEnabled);
#endif
}

void InternalSettingsGenerated::setMediaTypeOverride(const String& mediaTypeOverride)
{
    m_page->settings().setMediaTypeOverride(mediaTypeOverride);
}

void InternalSettingsGenerated::setMediaUserGestureInheritsFromDocument(bool mediaUserGestureInheritsFromDocument)
{
    m_page->settings().setMediaUserGestureInheritsFromDocument(mediaUserGestureInheritsFromDocument);
}

void InternalSettingsGenerated::setMenuItemElementEnabled(bool menuItemElementEnabled)
{
    m_page->settings().setMenuItemElementEnabled(menuItemElementEnabled);
}

void InternalSettingsGenerated::setMinimumAccelerated2dCanvasSize(uint32_t minimumAccelerated2dCanvasSize)
{
    m_page->settings().setMinimumAccelerated2dCanvasSize(minimumAccelerated2dCanvasSize);
}

void InternalSettingsGenerated::setMinimumFontSize(double minimumFontSize)
{
    m_page->settings().setMinimumFontSize(minimumFontSize);
}

void InternalSettingsGenerated::setMinimumLogicalFontSize(double minimumLogicalFontSize)
{
    m_page->settings().setMinimumLogicalFontSize(minimumLogicalFontSize);
}

void InternalSettingsGenerated::setMinimumZoomFontSize(double minimumZoomFontSize)
{
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setMinimumZoomFontSize(minimumZoomFontSize);
#else
    UNUSED_PARAM(minimumZoomFontSize);
#endif
}

void InternalSettingsGenerated::setMockCaptureDevicesEnabled(bool mockCaptureDevicesEnabled)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setMockCaptureDevicesEnabled(mockCaptureDevicesEnabled);
#else
    UNUSED_PARAM(mockCaptureDevicesEnabled);
#endif
}

void InternalSettingsGenerated::setMockScrollbarsControllerEnabled(bool mockScrollbarsControllerEnabled)
{
    m_page->settings().setMockScrollbarsControllerEnabled(mockScrollbarsControllerEnabled);
}

void InternalSettingsGenerated::setModelElementEnabled(bool modelElementEnabled)
{
#if ENABLE(MODEL_ELEMENT)
    m_page->settings().setModelElementEnabled(modelElementEnabled);
#else
    UNUSED_PARAM(modelElementEnabled);
#endif
}

void InternalSettingsGenerated::setMomentumScrollingAnimatorEnabled(bool momentumScrollingAnimatorEnabled)
{
    m_page->settings().setMomentumScrollingAnimatorEnabled(momentumScrollingAnimatorEnabled);
}

void InternalSettingsGenerated::setMouseEventsSimulationEnabled(bool mouseEventsSimulationEnabled)
{
#if ENABLE(TOUCH_EVENTS)
    m_page->settings().setMouseEventsSimulationEnabled(mouseEventsSimulationEnabled);
#else
    UNUSED_PARAM(mouseEventsSimulationEnabled);
#endif
}

void InternalSettingsGenerated::setMuteCameraOnMicrophoneInterruptionEnabled(bool muteCameraOnMicrophoneInterruptionEnabled)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setMuteCameraOnMicrophoneInterruptionEnabled(muteCameraOnMicrophoneInterruptionEnabled);
#else
    UNUSED_PARAM(muteCameraOnMicrophoneInterruptionEnabled);
#endif
}

void InternalSettingsGenerated::setNeedsAdobeFrameReloadingQuirk(bool needsAdobeFrameReloadingQuirk)
{
    m_page->settings().setNeedsAdobeFrameReloadingQuirk(needsAdobeFrameReloadingQuirk);
}

void InternalSettingsGenerated::setNeedsDeferKeyDownAndKeyPressTimersUntilNextEditingCommandQuirk(bool needsDeferKeyDownAndKeyPressTimersUntilNextEditingCommandQuirk)
{
    m_page->settings().setNeedsDeferKeyDownAndKeyPressTimersUntilNextEditingCommandQuirk(needsDeferKeyDownAndKeyPressTimersUntilNextEditingCommandQuirk);
}

void InternalSettingsGenerated::setNeedsFrameNameFallbackToIdQuirk(bool needsFrameNameFallbackToIdQuirk)
{
    m_page->settings().setNeedsFrameNameFallbackToIdQuirk(needsFrameNameFallbackToIdQuirk);
}

void InternalSettingsGenerated::setNeedsKeyboardEventDisambiguationQuirks(bool needsKeyboardEventDisambiguationQuirks)
{
    m_page->settings().setNeedsKeyboardEventDisambiguationQuirks(needsKeyboardEventDisambiguationQuirks);
}

void InternalSettingsGenerated::setNeedsSiteSpecificQuirks(bool needsSiteSpecificQuirks)
{
    m_page->settings().setNeedsSiteSpecificQuirks(needsSiteSpecificQuirks);
}

void InternalSettingsGenerated::setNeedsStorageAccessFromFileURLsQuirk(bool needsStorageAccessFromFileURLsQuirk)
{
    m_page->settings().setNeedsStorageAccessFromFileURLsQuirk(needsStorageAccessFromFileURLsQuirk);
}

void InternalSettingsGenerated::setNotificationEventEnabled(bool notificationEventEnabled)
{
#if ENABLE(NOTIFICATION_EVENT)
    m_page->settings().setNotificationEventEnabled(notificationEventEnabled);
#else
    UNUSED_PARAM(notificationEventEnabled);
#endif
}

void InternalSettingsGenerated::setNotificationsEnabled(bool notificationsEnabled)
{
#if ENABLE(NOTIFICATIONS)
    m_page->settings().setNotificationsEnabled(notificationsEnabled);
#else
    UNUSED_PARAM(notificationsEnabled);
#endif
}

void InternalSettingsGenerated::setOfflineWebApplicationCacheEnabled(bool offlineWebApplicationCacheEnabled)
{
    m_page->settings().setOfflineWebApplicationCacheEnabled(offlineWebApplicationCacheEnabled);
}

void InternalSettingsGenerated::setOffscreenCanvasEnabled(bool offscreenCanvasEnabled)
{
#if ENABLE(OFFSCREEN_CANVAS)
    m_page->settings().setOffscreenCanvasEnabled(offscreenCanvasEnabled);
#else
    UNUSED_PARAM(offscreenCanvasEnabled);
#endif
}

void InternalSettingsGenerated::setOffscreenCanvasInWorkersEnabled(bool offscreenCanvasInWorkersEnabled)
{
#if ENABLE(OFFSCREEN_CANVAS_IN_WORKERS)
    m_page->settings().setOffscreenCanvasInWorkersEnabled(offscreenCanvasInWorkersEnabled);
#else
    UNUSED_PARAM(offscreenCanvasInWorkersEnabled);
#endif
}

void InternalSettingsGenerated::setOverflowClipEnabled(bool overflowClipEnabled)
{
    m_page->settings().setOverflowClipEnabled(overflowClipEnabled);
}

void InternalSettingsGenerated::setOverscrollBehaviorEnabled(bool overscrollBehaviorEnabled)
{
    m_page->settings().setOverscrollBehaviorEnabled(overscrollBehaviorEnabled);
}

void InternalSettingsGenerated::setPageAtRuleSupportEnabled(bool pageAtRuleSupportEnabled)
{
    m_page->settings().setPageAtRuleSupportEnabled(pageAtRuleSupportEnabled);
}

void InternalSettingsGenerated::setPassiveTouchListenersAsDefaultOnDocument(bool passiveTouchListenersAsDefaultOnDocument)
{
    m_page->settings().setPassiveTouchListenersAsDefaultOnDocument(passiveTouchListenersAsDefaultOnDocument);
}

void InternalSettingsGenerated::setPassiveWheelListenersAsDefaultOnDocument(bool passiveWheelListenersAsDefaultOnDocument)
{
    m_page->settings().setPassiveWheelListenersAsDefaultOnDocument(passiveWheelListenersAsDefaultOnDocument);
}

void InternalSettingsGenerated::setPasswordEchoDurationInSeconds(double passwordEchoDurationInSeconds)
{
    m_page->settings().setPasswordEchoDurationInSeconds(passwordEchoDurationInSeconds);
}

void InternalSettingsGenerated::setPasswordEchoEnabled(bool passwordEchoEnabled)
{
    m_page->settings().setPasswordEchoEnabled(passwordEchoEnabled);
}

void InternalSettingsGenerated::setPaymentRequestEnabled(bool paymentRequestEnabled)
{
#if ENABLE(PAYMENT_REQUEST)
    m_page->settings().setPaymentRequestEnabled(paymentRequestEnabled);
#else
    UNUSED_PARAM(paymentRequestEnabled);
#endif
}

void InternalSettingsGenerated::setPdfJSViewerEnabled(bool pdfJSViewerEnabled)
{
#if ENABLE(PDFJS)
    m_page->settings().setPdfJSViewerEnabled(pdfJSViewerEnabled);
#else
    UNUSED_PARAM(pdfJSViewerEnabled);
#endif
}

void InternalSettingsGenerated::setPeerConnectionEnabled(bool peerConnectionEnabled)
{
#if ENABLE(WEB_RTC)
    m_page->settings().setPeerConnectionEnabled(peerConnectionEnabled);
#else
    UNUSED_PARAM(peerConnectionEnabled);
#endif
}

void InternalSettingsGenerated::setPerElementSpeakerSelectionEnabled(bool perElementSpeakerSelectionEnabled)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setPerElementSpeakerSelectionEnabled(perElementSpeakerSelectionEnabled);
#else
    UNUSED_PARAM(perElementSpeakerSelectionEnabled);
#endif
}

void InternalSettingsGenerated::setPerformanceNavigationTimingAPIEnabled(bool performanceNavigationTimingAPIEnabled)
{
    m_page->settings().setPerformanceNavigationTimingAPIEnabled(performanceNavigationTimingAPIEnabled);
}

void InternalSettingsGenerated::setPerformanceResourceTimingSensitivePropertiesEnabled(bool performanceResourceTimingSensitivePropertiesEnabled)
{
    m_page->settings().setPerformanceResourceTimingSensitivePropertiesEnabled(performanceResourceTimingSensitivePropertiesEnabled);
}

void InternalSettingsGenerated::setPermissionsAPIEnabled(bool permissionsAPIEnabled)
{
    m_page->settings().setPermissionsAPIEnabled(permissionsAPIEnabled);
}

void InternalSettingsGenerated::setPictographFontFamily(const String& pictographFontFamily)
{
    m_page->settings().setPictographFontFamily(pictographFontFamily);
}

void InternalSettingsGenerated::setPictureInPictureAPIEnabled(bool pictureInPictureAPIEnabled)
{
#if ENABLE(PICTURE_IN_PICTURE_API)
    m_page->settings().setPictureInPictureAPIEnabled(pictureInPictureAPIEnabled);
#else
    UNUSED_PARAM(pictureInPictureAPIEnabled);
#endif
}

void InternalSettingsGenerated::setPluginsEnabled(bool pluginsEnabled)
{
    m_page->settings().setPluginsEnabled(pluginsEnabled);
}

void InternalSettingsGenerated::setPopoverAttributeEnabled(bool popoverAttributeEnabled)
{
    m_page->settings().setPopoverAttributeEnabled(popoverAttributeEnabled);
}

void InternalSettingsGenerated::setPreferMIMETypeForImages(bool preferMIMETypeForImages)
{
    m_page->settings().setPreferMIMETypeForImages(preferMIMETypeForImages);
}

void InternalSettingsGenerated::setPreferPageRenderingUpdatesNear60FPSEnabled(bool preferPageRenderingUpdatesNear60FPSEnabled)
{
    m_page->settings().setPreferPageRenderingUpdatesNear60FPSEnabled(preferPageRenderingUpdatesNear60FPSEnabled);
}

void InternalSettingsGenerated::setPreferSandboxedMediaParsing(bool preferSandboxedMediaParsing)
{
#if ENABLE(VIDEO)
    m_page->settings().setPreferSandboxedMediaParsing(preferSandboxedMediaParsing);
#else
    UNUSED_PARAM(preferSandboxedMediaParsing);
#endif
}

void InternalSettingsGenerated::setPreventKeyboardDOMEventDispatch(bool preventKeyboardDOMEventDispatch)
{
    m_page->settings().setPreventKeyboardDOMEventDispatch(preventKeyboardDOMEventDispatch);
}

void InternalSettingsGenerated::setPrivateClickMeasurementDebugModeEnabled(bool privateClickMeasurementDebugModeEnabled)
{
    m_page->settings().setPrivateClickMeasurementDebugModeEnabled(privateClickMeasurementDebugModeEnabled);
}

void InternalSettingsGenerated::setPrivateClickMeasurementEnabled(bool privateClickMeasurementEnabled)
{
    m_page->settings().setPrivateClickMeasurementEnabled(privateClickMeasurementEnabled);
}

void InternalSettingsGenerated::setPrivateClickMeasurementFraudPreventionEnabled(bool privateClickMeasurementFraudPreventionEnabled)
{
    m_page->settings().setPrivateClickMeasurementFraudPreventionEnabled(privateClickMeasurementFraudPreventionEnabled);
}

void InternalSettingsGenerated::setPunchOutWhiteBackgroundsInDarkMode(bool punchOutWhiteBackgroundsInDarkMode)
{
    m_page->settings().setPunchOutWhiteBackgroundsInDarkMode(punchOutWhiteBackgroundsInDarkMode);
}

void InternalSettingsGenerated::setPushAPIEnabled(bool pushAPIEnabled)
{
#if ENABLE(SERVICE_WORKER)
    m_page->settings().setPushAPIEnabled(pushAPIEnabled);
#else
    UNUSED_PARAM(pushAPIEnabled);
#endif
}

void InternalSettingsGenerated::setReferrerPolicyAttributeEnabled(bool referrerPolicyAttributeEnabled)
{
    m_page->settings().setReferrerPolicyAttributeEnabled(referrerPolicyAttributeEnabled);
}

void InternalSettingsGenerated::setRemotePlaybackEnabled(bool remotePlaybackEnabled)
{
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    m_page->settings().setRemotePlaybackEnabled(remotePlaybackEnabled);
#else
    UNUSED_PARAM(remotePlaybackEnabled);
#endif
}

void InternalSettingsGenerated::setRemoveBackgroundEnabled(bool removeBackgroundEnabled)
{
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    m_page->settings().setRemoveBackgroundEnabled(removeBackgroundEnabled);
#else
    UNUSED_PARAM(removeBackgroundEnabled);
#endif
}

void InternalSettingsGenerated::setReportingEnabled(bool reportingEnabled)
{
    m_page->settings().setReportingEnabled(reportingEnabled);
}

void InternalSettingsGenerated::setRequestIdleCallbackEnabled(bool requestIdleCallbackEnabled)
{
    m_page->settings().setRequestIdleCallbackEnabled(requestIdleCallbackEnabled);
}

void InternalSettingsGenerated::setRequestSubmitEnabled(bool requestSubmitEnabled)
{
    m_page->settings().setRequestSubmitEnabled(requestSubmitEnabled);
}

void InternalSettingsGenerated::setRequestVideoFrameCallbackEnabled(bool requestVideoFrameCallbackEnabled)
{
    m_page->settings().setRequestVideoFrameCallbackEnabled(requestVideoFrameCallbackEnabled);
}

void InternalSettingsGenerated::setRequireUAGetDisplayMediaPrompt(bool requireUAGetDisplayMediaPrompt)
{
#if HAVE(SC_CONTENT_SHARING_PICKER)
    m_page->settings().setRequireUAGetDisplayMediaPrompt(requireUAGetDisplayMediaPrompt);
#else
    UNUSED_PARAM(requireUAGetDisplayMediaPrompt);
#endif
}

void InternalSettingsGenerated::setRequiresPageVisibilityToPlayAudio(bool requiresPageVisibilityToPlayAudio)
{
    m_page->settings().setRequiresPageVisibilityToPlayAudio(requiresPageVisibilityToPlayAudio);
}

void InternalSettingsGenerated::setRequiresUserGestureForAudioPlayback(bool requiresUserGestureForAudioPlayback)
{
    m_page->settings().setRequiresUserGestureForAudioPlayback(requiresUserGestureForAudioPlayback);
}

void InternalSettingsGenerated::setRequiresUserGestureForVideoPlayback(bool requiresUserGestureForVideoPlayback)
{
    m_page->settings().setRequiresUserGestureForVideoPlayback(requiresUserGestureForVideoPlayback);
}

void InternalSettingsGenerated::setRequiresUserGestureToLoadVideo(bool requiresUserGestureToLoadVideo)
{
    m_page->settings().setRequiresUserGestureToLoadVideo(requiresUserGestureToLoadVideo);
}

void InternalSettingsGenerated::setResizeObserverEnabled(bool resizeObserverEnabled)
{
    m_page->settings().setResizeObserverEnabled(resizeObserverEnabled);
}

void InternalSettingsGenerated::setResourceLoadSchedulingEnabled(bool resourceLoadSchedulingEnabled)
{
    m_page->settings().setResourceLoadSchedulingEnabled(resourceLoadSchedulingEnabled);
}

void InternalSettingsGenerated::setResourceUsageOverlayVisible(bool resourceUsageOverlayVisible)
{
#if ENABLE(RESOURCE_USAGE)
    m_page->settings().setResourceUsageOverlayVisible(resourceUsageOverlayVisible);
#else
    UNUSED_PARAM(resourceUsageOverlayVisible);
#endif
}

void InternalSettingsGenerated::setRubberBandingForSubScrollableRegionsEnabled(bool rubberBandingForSubScrollableRegionsEnabled)
{
#if HAVE(RUBBER_BANDING)
    m_page->settings().setRubberBandingForSubScrollableRegionsEnabled(rubberBandingForSubScrollableRegionsEnabled);
#else
    UNUSED_PARAM(rubberBandingForSubScrollableRegionsEnabled);
#endif
}

void InternalSettingsGenerated::setSKAttributionEnabled(bool sKAttributionEnabled)
{
    m_page->settings().setSKAttributionEnabled(sKAttributionEnabled);
}

void InternalSettingsGenerated::setSampleBufferContentKeySessionSupportEnabled(bool sampleBufferContentKeySessionSupportEnabled)
{
#if HAVE(AVCONTENTKEYSPECIFIER)
    m_page->settings().setSampleBufferContentKeySessionSupportEnabled(sampleBufferContentKeySessionSupportEnabled);
#else
    UNUSED_PARAM(sampleBufferContentKeySessionSupportEnabled);
#endif
}

void InternalSettingsGenerated::setSampledPageTopColorMaxDifference(double sampledPageTopColorMaxDifference)
{
    m_page->settings().setSampledPageTopColorMaxDifference(sampledPageTopColorMaxDifference);
}

void InternalSettingsGenerated::setSampledPageTopColorMinHeight(double sampledPageTopColorMinHeight)
{
    m_page->settings().setSampledPageTopColorMinHeight(sampledPageTopColorMinHeight);
}

void InternalSettingsGenerated::setSansSerifFontFamily(const String& sansSerifFontFamily)
{
    m_page->settings().setSansSerifFontFamily(sansSerifFontFamily);
}

void InternalSettingsGenerated::setScreenCaptureEnabled(bool screenCaptureEnabled)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setScreenCaptureEnabled(screenCaptureEnabled);
#else
    UNUSED_PARAM(screenCaptureEnabled);
#endif
}

void InternalSettingsGenerated::setScreenOrientationAPIEnabled(bool screenOrientationAPIEnabled)
{
    m_page->settings().setScreenOrientationAPIEnabled(screenOrientationAPIEnabled);
}

void InternalSettingsGenerated::setScreenOrientationLockingAPIEnabled(bool screenOrientationLockingAPIEnabled)
{
    m_page->settings().setScreenOrientationLockingAPIEnabled(screenOrientationLockingAPIEnabled);
}

void InternalSettingsGenerated::setScreenWakeLockAPIEnabled(bool screenWakeLockAPIEnabled)
{
    m_page->settings().setScreenWakeLockAPIEnabled(screenWakeLockAPIEnabled);
}

void InternalSettingsGenerated::setScriptEnabled(bool scriptEnabled)
{
    m_page->settings().setScriptEnabled(scriptEnabled);
}

void InternalSettingsGenerated::setScriptMarkupEnabled(bool scriptMarkupEnabled)
{
    m_page->settings().setScriptMarkupEnabled(scriptMarkupEnabled);
}

void InternalSettingsGenerated::setScrollAnimatorEnabled(bool scrollAnimatorEnabled)
{
    m_page->settings().setScrollAnimatorEnabled(scrollAnimatorEnabled);
}

void InternalSettingsGenerated::setScrollToTextFragmentEnabled(bool scrollToTextFragmentEnabled)
{
    m_page->settings().setScrollToTextFragmentEnabled(scrollToTextFragmentEnabled);
}

void InternalSettingsGenerated::setScrollToTextFragmentIndicatorEnabled(bool scrollToTextFragmentIndicatorEnabled)
{
    m_page->settings().setScrollToTextFragmentIndicatorEnabled(scrollToTextFragmentIndicatorEnabled);
}

void InternalSettingsGenerated::setScrollingCoordinatorEnabled(bool scrollingCoordinatorEnabled)
{
    m_page->settings().setScrollingCoordinatorEnabled(scrollingCoordinatorEnabled);
}

void InternalSettingsGenerated::setScrollingPerformanceTestingEnabled(bool scrollingPerformanceTestingEnabled)
{
    m_page->settings().setScrollingPerformanceTestingEnabled(scrollingPerformanceTestingEnabled);
}

void InternalSettingsGenerated::setScrollingTreeIncludesFrames(bool scrollingTreeIncludesFrames)
{
    m_page->settings().setScrollingTreeIncludesFrames(scrollingTreeIncludesFrames);
}

void InternalSettingsGenerated::setSearchInputIncrementalAttributeAndSearchEventEnabled(bool searchInputIncrementalAttributeAndSearchEventEnabled)
{
    m_page->settings().setSearchInputIncrementalAttributeAndSearchEventEnabled(searchInputIncrementalAttributeAndSearchEventEnabled);
}

void InternalSettingsGenerated::setSecureContextChecksEnabled(bool secureContextChecksEnabled)
{
    m_page->settings().setSecureContextChecksEnabled(secureContextChecksEnabled);
}

void InternalSettingsGenerated::setSelectTrailingWhitespaceEnabled(bool selectTrailingWhitespaceEnabled)
{
    m_page->settings().setSelectTrailingWhitespaceEnabled(selectTrailingWhitespaceEnabled);
}

void InternalSettingsGenerated::setSelectionAPIForShadowDOMEnabled(bool selectionAPIForShadowDOMEnabled)
{
    m_page->settings().setSelectionAPIForShadowDOMEnabled(selectionAPIForShadowDOMEnabled);
}

void InternalSettingsGenerated::setSendMouseEventsToDisabledFormControlsEnabled(bool sendMouseEventsToDisabledFormControlsEnabled)
{
    m_page->settings().setSendMouseEventsToDisabledFormControlsEnabled(sendMouseEventsToDisabledFormControlsEnabled);
}

void InternalSettingsGenerated::setSerifFontFamily(const String& serifFontFamily)
{
    m_page->settings().setSerifFontFamily(serifFontFamily);
}

void InternalSettingsGenerated::setServiceControlsEnabled(bool serviceControlsEnabled)
{
#if ENABLE(SERVICE_CONTROLS)
    m_page->settings().setServiceControlsEnabled(serviceControlsEnabled);
#else
    UNUSED_PARAM(serviceControlsEnabled);
#endif
}

void InternalSettingsGenerated::setServiceWorkerNavigationPreloadEnabled(bool serviceWorkerNavigationPreloadEnabled)
{
#if ENABLE(SERVICE_WORKER)
    m_page->settings().setServiceWorkerNavigationPreloadEnabled(serviceWorkerNavigationPreloadEnabled);
#else
    UNUSED_PARAM(serviceWorkerNavigationPreloadEnabled);
#endif
}

void InternalSettingsGenerated::setServiceWorkersEnabled(bool serviceWorkersEnabled)
{
#if ENABLE(SERVICE_WORKER)
    m_page->settings().setServiceWorkersEnabled(serviceWorkersEnabled);
#else
    UNUSED_PARAM(serviceWorkersEnabled);
#endif
}

void InternalSettingsGenerated::setServiceWorkersUserGestureEnabled(bool serviceWorkersUserGestureEnabled)
{
#if ENABLE(SERVICE_WORKER)
    m_page->settings().setServiceWorkersUserGestureEnabled(serviceWorkersUserGestureEnabled);
#else
    UNUSED_PARAM(serviceWorkersUserGestureEnabled);
#endif
}

void InternalSettingsGenerated::setSessionStorageQuota(uint32_t sessionStorageQuota)
{
    m_page->settings().setSessionStorageQuota(sessionStorageQuota);
}

void InternalSettingsGenerated::setShapeDetection(bool shapeDetection)
{
    m_page->settings().setShapeDetection(shapeDetection);
}

void InternalSettingsGenerated::setSharedWorkerEnabled(bool sharedWorkerEnabled)
{
    m_page->settings().setSharedWorkerEnabled(sharedWorkerEnabled);
}

void InternalSettingsGenerated::setShouldAllowUserInstalledFonts(bool shouldAllowUserInstalledFonts)
{
    m_page->settings().setShouldAllowUserInstalledFonts(shouldAllowUserInstalledFonts);
}

void InternalSettingsGenerated::setShouldConvertInvalidURLsToBlank(bool shouldConvertInvalidURLsToBlank)
{
    m_page->settings().setShouldConvertInvalidURLsToBlank(shouldConvertInvalidURLsToBlank);
}

void InternalSettingsGenerated::setShouldConvertPositionStyleOnCopy(bool shouldConvertPositionStyleOnCopy)
{
    m_page->settings().setShouldConvertPositionStyleOnCopy(shouldConvertPositionStyleOnCopy);
}

void InternalSettingsGenerated::setShouldDecidePolicyBeforeLoadingQuickLookPreview(bool shouldDecidePolicyBeforeLoadingQuickLookPreview)
{
    m_page->settings().setShouldDecidePolicyBeforeLoadingQuickLookPreview(shouldDecidePolicyBeforeLoadingQuickLookPreview);
}

void InternalSettingsGenerated::setShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint(bool shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint)
{
    m_page->settings().setShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint(shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint);
}

void InternalSettingsGenerated::setShouldDispatchSyntheticMouseEventsWhenModifyingSelection(bool shouldDispatchSyntheticMouseEventsWhenModifyingSelection)
{
    m_page->settings().setShouldDispatchSyntheticMouseEventsWhenModifyingSelection(shouldDispatchSyntheticMouseEventsWhenModifyingSelection);
}

void InternalSettingsGenerated::setShouldDispatchSyntheticMouseOutAfterSyntheticClick(bool shouldDispatchSyntheticMouseOutAfterSyntheticClick)
{
    m_page->settings().setShouldDispatchSyntheticMouseOutAfterSyntheticClick(shouldDispatchSyntheticMouseOutAfterSyntheticClick);
}

void InternalSettingsGenerated::setShouldDisplayCaptions(bool shouldDisplayCaptions)
{
#if ENABLE(VIDEO)
    m_page->settings().setShouldDisplayCaptions(shouldDisplayCaptions);
#else
    UNUSED_PARAM(shouldDisplayCaptions);
#endif
}

void InternalSettingsGenerated::setShouldDisplaySubtitles(bool shouldDisplaySubtitles)
{
#if ENABLE(VIDEO)
    m_page->settings().setShouldDisplaySubtitles(shouldDisplaySubtitles);
#else
    UNUSED_PARAM(shouldDisplaySubtitles);
#endif
}

void InternalSettingsGenerated::setShouldDisplayTextDescriptions(bool shouldDisplayTextDescriptions)
{
#if ENABLE(VIDEO)
    m_page->settings().setShouldDisplayTextDescriptions(shouldDisplayTextDescriptions);
#else
    UNUSED_PARAM(shouldDisplayTextDescriptions);
#endif
}

void InternalSettingsGenerated::setShouldDropNearSuspendedAssertionAfterDelay(bool shouldDropNearSuspendedAssertionAfterDelay)
{
    m_page->settings().setShouldDropNearSuspendedAssertionAfterDelay(shouldDropNearSuspendedAssertionAfterDelay);
}

void InternalSettingsGenerated::setShouldEnableTextAutosizingBoost(bool shouldEnableTextAutosizingBoost)
{
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setShouldEnableTextAutosizingBoost(shouldEnableTextAutosizingBoost);
#else
    UNUSED_PARAM(shouldEnableTextAutosizingBoost);
#endif
}

void InternalSettingsGenerated::setShouldIgnoreFontLoadCompletions(bool shouldIgnoreFontLoadCompletions)
{
    m_page->settings().setShouldIgnoreFontLoadCompletions(shouldIgnoreFontLoadCompletions);
}

void InternalSettingsGenerated::setShouldIgnoreMetaViewport(bool shouldIgnoreMetaViewport)
{
    m_page->settings().setShouldIgnoreMetaViewport(shouldIgnoreMetaViewport);
}

void InternalSettingsGenerated::setShouldInjectUserScriptsInInitialEmptyDocument(bool shouldInjectUserScriptsInInitialEmptyDocument)
{
    m_page->settings().setShouldInjectUserScriptsInInitialEmptyDocument(shouldInjectUserScriptsInInitialEmptyDocument);
}

void InternalSettingsGenerated::setShouldPrintBackgrounds(bool shouldPrintBackgrounds)
{
    m_page->settings().setShouldPrintBackgrounds(shouldPrintBackgrounds);
}

void InternalSettingsGenerated::setShouldRespectImageOrientation(bool shouldRespectImageOrientation)
{
    m_page->settings().setShouldRespectImageOrientation(shouldRespectImageOrientation);
}

void InternalSettingsGenerated::setShouldRestrictBaseURLSchemes(bool shouldRestrictBaseURLSchemes)
{
    m_page->settings().setShouldRestrictBaseURLSchemes(shouldRestrictBaseURLSchemes);
}

void InternalSettingsGenerated::setShouldSuppressTextInputFromEditingDuringProvisionalNavigation(bool shouldSuppressTextInputFromEditingDuringProvisionalNavigation)
{
    m_page->settings().setShouldSuppressTextInputFromEditingDuringProvisionalNavigation(shouldSuppressTextInputFromEditingDuringProvisionalNavigation);
}

void InternalSettingsGenerated::setShouldTakeNearSuspendedAssertions(bool shouldTakeNearSuspendedAssertions)
{
    m_page->settings().setShouldTakeNearSuspendedAssertions(shouldTakeNearSuspendedAssertions);
}

void InternalSettingsGenerated::setShouldUseServiceWorkerShortTimeout(bool shouldUseServiceWorkerShortTimeout)
{
    m_page->settings().setShouldUseServiceWorkerShortTimeout(shouldUseServiceWorkerShortTimeout);
}

void InternalSettingsGenerated::setShowDebugBorders(bool showDebugBorders)
{
    m_page->settings().setShowDebugBorders(showDebugBorders);
}

void InternalSettingsGenerated::setShowMediaStatsContextMenuItemEnabled(bool showMediaStatsContextMenuItemEnabled)
{
    m_page->settings().setShowMediaStatsContextMenuItemEnabled(showMediaStatsContextMenuItemEnabled);
}

void InternalSettingsGenerated::setShowModalDialogEnabled(bool showModalDialogEnabled)
{
    m_page->settings().setShowModalDialogEnabled(showModalDialogEnabled);
}

void InternalSettingsGenerated::setShowRepaintCounter(bool showRepaintCounter)
{
    m_page->settings().setShowRepaintCounter(showRepaintCounter);
}

void InternalSettingsGenerated::setShowTiledScrollingIndicator(bool showTiledScrollingIndicator)
{
    m_page->settings().setShowTiledScrollingIndicator(showTiledScrollingIndicator);
}

void InternalSettingsGenerated::setShowsToolTipOverTruncatedText(bool showsToolTipOverTruncatedText)
{
    m_page->settings().setShowsToolTipOverTruncatedText(showsToolTipOverTruncatedText);
}

void InternalSettingsGenerated::setShowsURLsInToolTips(bool showsURLsInToolTips)
{
    m_page->settings().setShowsURLsInToolTips(showsURLsInToolTips);
}

void InternalSettingsGenerated::setShrinksStandaloneImagesToFit(bool shrinksStandaloneImagesToFit)
{
    m_page->settings().setShrinksStandaloneImagesToFit(shrinksStandaloneImagesToFit);
}

void InternalSettingsGenerated::setSiteIsolationEnabled(bool siteIsolationEnabled)
{
    m_page->settings().setSiteIsolationEnabled(siteIsolationEnabled);
}

void InternalSettingsGenerated::setSmartInsertDeleteEnabled(bool smartInsertDeleteEnabled)
{
    m_page->settings().setSmartInsertDeleteEnabled(smartInsertDeleteEnabled);
}

void InternalSettingsGenerated::setSourceBufferChangeTypeEnabled(bool sourceBufferChangeTypeEnabled)
{
#if ENABLE(MEDIA_SOURCE)
    m_page->settings().setSourceBufferChangeTypeEnabled(sourceBufferChangeTypeEnabled);
#else
    UNUSED_PARAM(sourceBufferChangeTypeEnabled);
#endif
}

void InternalSettingsGenerated::setSpatialNavigationEnabled(bool spatialNavigationEnabled)
{
    m_page->settings().setSpatialNavigationEnabled(spatialNavigationEnabled);
}

void InternalSettingsGenerated::setSpeakerSelectionRequiresUserGesture(bool speakerSelectionRequiresUserGesture)
{
#if ENABLE(MEDIA_STREAM)
    m_page->settings().setSpeakerSelectionRequiresUserGesture(speakerSelectionRequiresUserGesture);
#else
    UNUSED_PARAM(speakerSelectionRequiresUserGesture);
#endif
}

void InternalSettingsGenerated::setSpeechRecognitionEnabled(bool speechRecognitionEnabled)
{
    m_page->settings().setSpeechRecognitionEnabled(speechRecognitionEnabled);
}

void InternalSettingsGenerated::setSpeechSynthesisAPIEnabled(bool speechSynthesisAPIEnabled)
{
    m_page->settings().setSpeechSynthesisAPIEnabled(speechSynthesisAPIEnabled);
}

void InternalSettingsGenerated::setSpringTimingFunctionEnabled(bool springTimingFunctionEnabled)
{
    m_page->settings().setSpringTimingFunctionEnabled(springTimingFunctionEnabled);
}

void InternalSettingsGenerated::setStandalone(bool standalone)
{
    m_page->settings().setStandalone(standalone);
}

void InternalSettingsGenerated::setStandardFontFamily(const String& standardFontFamily)
{
    m_page->settings().setStandardFontFamily(standardFontFamily);
}

void InternalSettingsGenerated::setStorageAPIEnabled(bool storageAPIEnabled)
{
    m_page->settings().setStorageAPIEnabled(storageAPIEnabled);
}

void InternalSettingsGenerated::setStorageAPIEstimateEnabled(bool storageAPIEstimateEnabled)
{
    m_page->settings().setStorageAPIEstimateEnabled(storageAPIEstimateEnabled);
}

void InternalSettingsGenerated::setStorageAccessAPIEnabled(bool storageAccessAPIEnabled)
{
    m_page->settings().setStorageAccessAPIEnabled(storageAccessAPIEnabled);
}

void InternalSettingsGenerated::setStorageAccessAPIPerPageScopeEnabled(bool storageAccessAPIPerPageScopeEnabled)
{
    m_page->settings().setStorageAccessAPIPerPageScopeEnabled(storageAccessAPIPerPageScopeEnabled);
}

void InternalSettingsGenerated::setSubgridEnabled(bool subgridEnabled)
{
    m_page->settings().setSubgridEnabled(subgridEnabled);
}

void InternalSettingsGenerated::setSuppressesIncrementalRendering(bool suppressesIncrementalRendering)
{
    m_page->settings().setSuppressesIncrementalRendering(suppressesIncrementalRendering);
}

void InternalSettingsGenerated::setSyntheticEditingCommandsEnabled(bool syntheticEditingCommandsEnabled)
{
    m_page->settings().setSyntheticEditingCommandsEnabled(syntheticEditingCommandsEnabled);
}

void InternalSettingsGenerated::setSystemPreviewEnabled(bool systemPreviewEnabled)
{
#if USE(SYSTEM_PREVIEW)
    m_page->settings().setSystemPreviewEnabled(systemPreviewEnabled);
#else
    UNUSED_PARAM(systemPreviewEnabled);
#endif
}

void InternalSettingsGenerated::setTelephoneNumberParsingEnabled(bool telephoneNumberParsingEnabled)
{
    m_page->settings().setTelephoneNumberParsingEnabled(telephoneNumberParsingEnabled);
}

void InternalSettingsGenerated::setTemporaryTileCohortRetentionEnabled(bool temporaryTileCohortRetentionEnabled)
{
    m_page->settings().setTemporaryTileCohortRetentionEnabled(temporaryTileCohortRetentionEnabled);
}

void InternalSettingsGenerated::setTextAreasAreResizable(bool textAreasAreResizable)
{
    m_page->settings().setTextAreasAreResizable(textAreasAreResizable);
}

void InternalSettingsGenerated::setTextAutosizingEnabled(bool textAutosizingEnabled)
{
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setTextAutosizingEnabled(textAutosizingEnabled);
#else
    UNUSED_PARAM(textAutosizingEnabled);
#endif
}

void InternalSettingsGenerated::setTextAutosizingUsesIdempotentMode(bool textAutosizingUsesIdempotentMode)
{
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setTextAutosizingUsesIdempotentMode(textAutosizingUsesIdempotentMode);
#else
    UNUSED_PARAM(textAutosizingUsesIdempotentMode);
#endif
}

void InternalSettingsGenerated::setTextAutosizingWindowSizeOverrideHeight(uint32_t textAutosizingWindowSizeOverrideHeight)
{
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setTextAutosizingWindowSizeOverrideHeight(textAutosizingWindowSizeOverrideHeight);
#else
    UNUSED_PARAM(textAutosizingWindowSizeOverrideHeight);
#endif
}

void InternalSettingsGenerated::setTextAutosizingWindowSizeOverrideWidth(uint32_t textAutosizingWindowSizeOverrideWidth)
{
#if ENABLE(TEXT_AUTOSIZING)
    m_page->settings().setTextAutosizingWindowSizeOverrideWidth(textAutosizingWindowSizeOverrideWidth);
#else
    UNUSED_PARAM(textAutosizingWindowSizeOverrideWidth);
#endif
}

void InternalSettingsGenerated::setTextInteractionEnabled(bool textInteractionEnabled)
{
    m_page->settings().setTextInteractionEnabled(textInteractionEnabled);
}

void InternalSettingsGenerated::setTextRecognitionInVideosEnabled(bool textRecognitionInVideosEnabled)
{
#if ENABLE(IMAGE_ANALYSIS)
    m_page->settings().setTextRecognitionInVideosEnabled(textRecognitionInVideosEnabled);
#else
    UNUSED_PARAM(textRecognitionInVideosEnabled);
#endif
}

void InternalSettingsGenerated::setThirdPartyIframeRedirectBlockingEnabled(bool thirdPartyIframeRedirectBlockingEnabled)
{
    m_page->settings().setThirdPartyIframeRedirectBlockingEnabled(thirdPartyIframeRedirectBlockingEnabled);
}

void InternalSettingsGenerated::setThreadedAnimationResolutionEnabled(bool threadedAnimationResolutionEnabled)
{
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
    m_page->settings().setThreadedAnimationResolutionEnabled(threadedAnimationResolutionEnabled);
#else
    UNUSED_PARAM(threadedAnimationResolutionEnabled);
#endif
}

void InternalSettingsGenerated::setTouchEventEmulationEnabled(bool touchEventEmulationEnabled)
{
#if ENABLE(TOUCH_EVENTS)
    m_page->settings().setTouchEventEmulationEnabled(touchEventEmulationEnabled);
#else
    UNUSED_PARAM(touchEventEmulationEnabled);
#endif
}

void InternalSettingsGenerated::setTouchEventsEnabled(bool touchEventsEnabled)
{
#if ENABLE(TOUCH_EVENTS)
    m_page->settings().setTouchEventsEnabled(touchEventsEnabled);
#else
    UNUSED_PARAM(touchEventsEnabled);
#endif
}

void InternalSettingsGenerated::setTrackConfigurationEnabled(bool trackConfigurationEnabled)
{
    m_page->settings().setTrackConfigurationEnabled(trackConfigurationEnabled);
}

void InternalSettingsGenerated::setTransformStreamAPIEnabled(bool transformStreamAPIEnabled)
{
    m_page->settings().setTransformStreamAPIEnabled(transformStreamAPIEnabled);
}

void InternalSettingsGenerated::setTreatIPAddressAsDomain(bool treatIPAddressAsDomain)
{
    m_page->settings().setTreatIPAddressAsDomain(treatIPAddressAsDomain);
}

void InternalSettingsGenerated::setTreatsAnyTextCSSLinkAsStylesheet(bool treatsAnyTextCSSLinkAsStylesheet)
{
    m_page->settings().setTreatsAnyTextCSSLinkAsStylesheet(treatsAnyTextCSSLinkAsStylesheet);
}

void InternalSettingsGenerated::setUndoManagerAPIEnabled(bool undoManagerAPIEnabled)
{
    m_page->settings().setUndoManagerAPIEnabled(undoManagerAPIEnabled);
}

void InternalSettingsGenerated::setUnhandledPromiseRejectionToConsoleEnabled(bool unhandledPromiseRejectionToConsoleEnabled)
{
    m_page->settings().setUnhandledPromiseRejectionToConsoleEnabled(unhandledPromiseRejectionToConsoleEnabled);
}

void InternalSettingsGenerated::setUnifiedTextCheckerEnabled(bool unifiedTextCheckerEnabled)
{
    m_page->settings().setUnifiedTextCheckerEnabled(unifiedTextCheckerEnabled);
}

void InternalSettingsGenerated::setUnprefixedFullscreenAPIEnabled(bool unprefixedFullscreenAPIEnabled)
{
    m_page->settings().setUnprefixedFullscreenAPIEnabled(unprefixedFullscreenAPIEnabled);
}

void InternalSettingsGenerated::setUseAnonymousModeWhenFetchingMaskImages(bool useAnonymousModeWhenFetchingMaskImages)
{
    m_page->settings().setUseAnonymousModeWhenFetchingMaskImages(useAnonymousModeWhenFetchingMaskImages);
}

void InternalSettingsGenerated::setUseGPUProcessForWebGLEnabled(bool useGPUProcessForWebGLEnabled)
{
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
    m_page->settings().setUseGPUProcessForWebGLEnabled(useGPUProcessForWebGLEnabled);
#else
    UNUSED_PARAM(useGPUProcessForWebGLEnabled);
#endif
}

void InternalSettingsGenerated::setUseGiantTiles(bool useGiantTiles)
{
    m_page->settings().setUseGiantTiles(useGiantTiles);
}

void InternalSettingsGenerated::setUseImageDocumentForSubframePDF(bool useImageDocumentForSubframePDF)
{
    m_page->settings().setUseImageDocumentForSubframePDF(useImageDocumentForSubframePDF);
}

void InternalSettingsGenerated::setUseLegacyBackgroundSizeShorthandBehavior(bool useLegacyBackgroundSizeShorthandBehavior)
{
    m_page->settings().setUseLegacyBackgroundSizeShorthandBehavior(useLegacyBackgroundSizeShorthandBehavior);
}

void InternalSettingsGenerated::setUsePreHTML5ParserQuirks(bool usePreHTML5ParserQuirks)
{
    m_page->settings().setUsePreHTML5ParserQuirks(usePreHTML5ParserQuirks);
}

void InternalSettingsGenerated::setUseSCContentSharingPicker(bool useSCContentSharingPicker)
{
#if HAVE(SC_CONTENT_SHARING_PICKER)
    m_page->settings().setUseSCContentSharingPicker(useSCContentSharingPicker);
#else
    UNUSED_PARAM(useSCContentSharingPicker);
#endif
}

void InternalSettingsGenerated::setUserActivationAPIEnabled(bool userActivationAPIEnabled)
{
    m_page->settings().setUserActivationAPIEnabled(userActivationAPIEnabled);
}

void InternalSettingsGenerated::setUserGesturePromisePropagationEnabled(bool userGesturePromisePropagationEnabled)
{
    m_page->settings().setUserGesturePromisePropagationEnabled(userGesturePromisePropagationEnabled);
}

void InternalSettingsGenerated::setUsesEncodingDetector(bool usesEncodingDetector)
{
    m_page->settings().setUsesEncodingDetector(usesEncodingDetector);
}

void InternalSettingsGenerated::setValidationMessageTimerMagnification(uint32_t validationMessageTimerMagnification)
{
    m_page->settings().setValidationMessageTimerMagnification(validationMessageTimerMagnification);
}

void InternalSettingsGenerated::setVerifyWindowOpenUserGestureFromUIProcess(bool verifyWindowOpenUserGestureFromUIProcess)
{
    m_page->settings().setVerifyWindowOpenUserGestureFromUIProcess(verifyWindowOpenUserGestureFromUIProcess);
}

void InternalSettingsGenerated::setVerticalFormControlsEnabled(bool verticalFormControlsEnabled)
{
    m_page->settings().setVerticalFormControlsEnabled(verticalFormControlsEnabled);
}

void InternalSettingsGenerated::setVideoFullscreenRequiresElementFullscreen(bool videoFullscreenRequiresElementFullscreen)
{
#if PLATFORM(IOS_FAMILY)
    m_page->settings().setVideoFullscreenRequiresElementFullscreen(videoFullscreenRequiresElementFullscreen);
#else
    UNUSED_PARAM(videoFullscreenRequiresElementFullscreen);
#endif
}

void InternalSettingsGenerated::setVideoPresentationModeAPIEnabled(bool videoPresentationModeAPIEnabled)
{
    m_page->settings().setVideoPresentationModeAPIEnabled(videoPresentationModeAPIEnabled);
}

void InternalSettingsGenerated::setVideoQualityIncludesDisplayCompositingEnabled(bool videoQualityIncludesDisplayCompositingEnabled)
{
#if ENABLE(VIDEO)
    m_page->settings().setVideoQualityIncludesDisplayCompositingEnabled(videoQualityIncludesDisplayCompositingEnabled);
#else
    UNUSED_PARAM(videoQualityIncludesDisplayCompositingEnabled);
#endif
}

void InternalSettingsGenerated::setVisibleDebugOverlayRegions(uint32_t visibleDebugOverlayRegions)
{
    m_page->settings().setVisibleDebugOverlayRegions(visibleDebugOverlayRegions);
}

void InternalSettingsGenerated::setVisualTranslationEnabled(bool visualTranslationEnabled)
{
#if ENABLE(IMAGE_ANALYSIS)
    m_page->settings().setVisualTranslationEnabled(visualTranslationEnabled);
#else
    UNUSED_PARAM(visualTranslationEnabled);
#endif
}

void InternalSettingsGenerated::setVisualViewportAPIEnabled(bool visualViewportAPIEnabled)
{
    m_page->settings().setVisualViewportAPIEnabled(visualViewportAPIEnabled);
}

void InternalSettingsGenerated::setVisualViewportEnabled(bool visualViewportEnabled)
{
    m_page->settings().setVisualViewportEnabled(visualViewportEnabled);
}

void InternalSettingsGenerated::setVP9DecoderEnabled(bool vp9DecoderEnabled)
{
#if ENABLE(VP9)
    m_page->settings().setVP9DecoderEnabled(vp9DecoderEnabled);
#else
    UNUSED_PARAM(vp9DecoderEnabled);
#endif
}

void InternalSettingsGenerated::setWantsBalancedSetDefersLoadingBehavior(bool wantsBalancedSetDefersLoadingBehavior)
{
    m_page->settings().setWantsBalancedSetDefersLoadingBehavior(wantsBalancedSetDefersLoadingBehavior);
}

void InternalSettingsGenerated::setWebAPIStatisticsEnabled(bool webAPIStatisticsEnabled)
{
    m_page->settings().setWebAPIStatisticsEnabled(webAPIStatisticsEnabled);
}

void InternalSettingsGenerated::setWebAPIsInShadowRealmEnabled(bool webAPIsInShadowRealmEnabled)
{
    m_page->settings().setWebAPIsInShadowRealmEnabled(webAPIsInShadowRealmEnabled);
}

void InternalSettingsGenerated::setWebAnimationsCompositeOperationsEnabled(bool webAnimationsCompositeOperationsEnabled)
{
    m_page->settings().setWebAnimationsCompositeOperationsEnabled(webAnimationsCompositeOperationsEnabled);
}

void InternalSettingsGenerated::setWebAnimationsCustomEffectsEnabled(bool webAnimationsCustomEffectsEnabled)
{
    m_page->settings().setWebAnimationsCustomEffectsEnabled(webAnimationsCustomEffectsEnabled);
}

void InternalSettingsGenerated::setWebAnimationsCustomFrameRateEnabled(bool webAnimationsCustomFrameRateEnabled)
{
    m_page->settings().setWebAnimationsCustomFrameRateEnabled(webAnimationsCustomFrameRateEnabled);
}

void InternalSettingsGenerated::setWebAnimationsIterationCompositeEnabled(bool webAnimationsIterationCompositeEnabled)
{
    m_page->settings().setWebAnimationsIterationCompositeEnabled(webAnimationsIterationCompositeEnabled);
}

void InternalSettingsGenerated::setWebAnimationsMutableTimelinesEnabled(bool webAnimationsMutableTimelinesEnabled)
{
    m_page->settings().setWebAnimationsMutableTimelinesEnabled(webAnimationsMutableTimelinesEnabled);
}

void InternalSettingsGenerated::setWebArchiveDebugModeEnabled(bool webArchiveDebugModeEnabled)
{
#if ENABLE(WEB_ARCHIVE)
    m_page->settings().setWebArchiveDebugModeEnabled(webArchiveDebugModeEnabled);
#else
    UNUSED_PARAM(webArchiveDebugModeEnabled);
#endif
}

void InternalSettingsGenerated::setWebArchiveTestingModeEnabled(bool webArchiveTestingModeEnabled)
{
#if ENABLE(WEB_ARCHIVE)
    m_page->settings().setWebArchiveTestingModeEnabled(webArchiveTestingModeEnabled);
#else
    UNUSED_PARAM(webArchiveTestingModeEnabled);
#endif
}

void InternalSettingsGenerated::setWebAssemblyESMIntegrationEnabled(bool webAssemblyESMIntegrationEnabled)
{
#if ENABLE(WEBASSEMBLY)
    m_page->settings().setWebAssemblyESMIntegrationEnabled(webAssemblyESMIntegrationEnabled);
#else
    UNUSED_PARAM(webAssemblyESMIntegrationEnabled);
#endif
}

void InternalSettingsGenerated::setWebAudioEnabled(bool webAudioEnabled)
{
#if ENABLE(WEB_AUDIO)
    m_page->settings().setWebAudioEnabled(webAudioEnabled);
#else
    UNUSED_PARAM(webAudioEnabled);
#endif
}

void InternalSettingsGenerated::setWebAuthenticationEnabled(bool webAuthenticationEnabled)
{
#if ENABLE(WEB_AUTHN)
    m_page->settings().setWebAuthenticationEnabled(webAuthenticationEnabled);
#else
    UNUSED_PARAM(webAuthenticationEnabled);
#endif
}

void InternalSettingsGenerated::setWebCodecsAV1Enabled(bool webCodecsAV1Enabled)
{
#if ENABLE(WEB_CODECS)
    m_page->settings().setWebCodecsAV1Enabled(webCodecsAV1Enabled);
#else
    UNUSED_PARAM(webCodecsAV1Enabled);
#endif
}

void InternalSettingsGenerated::setWebCodecsEnabled(bool webCodecsEnabled)
{
#if ENABLE(WEB_CODECS)
    m_page->settings().setWebCodecsEnabled(webCodecsEnabled);
#else
    UNUSED_PARAM(webCodecsEnabled);
#endif
}

void InternalSettingsGenerated::setWebCodecsHEVCEnabled(bool webCodecsHEVCEnabled)
{
#if ENABLE(WEB_CODECS)
    m_page->settings().setWebCodecsHEVCEnabled(webCodecsHEVCEnabled);
#else
    UNUSED_PARAM(webCodecsHEVCEnabled);
#endif
}

void InternalSettingsGenerated::setWebCryptoSafeCurvesEnabled(bool webCryptoSafeCurvesEnabled)
{
    m_page->settings().setWebCryptoSafeCurvesEnabled(webCryptoSafeCurvesEnabled);
}

void InternalSettingsGenerated::setWebGLDraftExtensionsEnabled(bool webGLDraftExtensionsEnabled)
{
    m_page->settings().setWebGLDraftExtensionsEnabled(webGLDraftExtensionsEnabled);
}

void InternalSettingsGenerated::setWebGLEnabled(bool webGLEnabled)
{
    m_page->settings().setWebGLEnabled(webGLEnabled);
}

void InternalSettingsGenerated::setWebGLErrorsToConsoleEnabled(bool webGLErrorsToConsoleEnabled)
{
    m_page->settings().setWebGLErrorsToConsoleEnabled(webGLErrorsToConsoleEnabled);
}

void InternalSettingsGenerated::setWebGLTimerQueriesEnabled(bool webGLTimerQueriesEnabled)
{
    m_page->settings().setWebGLTimerQueriesEnabled(webGLTimerQueriesEnabled);
}

void InternalSettingsGenerated::setWebGLUsingMetal(bool webGLUsingMetal)
{
#if ENABLE(WEBGL) && PLATFORM(COCOA)
    m_page->settings().setWebGLUsingMetal(webGLUsingMetal);
#else
    UNUSED_PARAM(webGLUsingMetal);
#endif
}

void InternalSettingsGenerated::setWebGPUEnabled(bool webGPUEnabled)
{
    m_page->settings().setWebGPUEnabled(webGPUEnabled);
}

void InternalSettingsGenerated::setWebInspectorEngineeringSettingsAllowed(bool webInspectorEngineeringSettingsAllowed)
{
    m_page->settings().setWebInspectorEngineeringSettingsAllowed(webInspectorEngineeringSettingsAllowed);
}

void InternalSettingsGenerated::setWebLocksAPIEnabled(bool webLocksAPIEnabled)
{
    m_page->settings().setWebLocksAPIEnabled(webLocksAPIEnabled);
}

void InternalSettingsGenerated::setWebRTCAV1CodecEnabled(bool webRTCAV1CodecEnabled)
{
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCAV1CodecEnabled(webRTCAV1CodecEnabled);
#else
    UNUSED_PARAM(webRTCAV1CodecEnabled);
#endif
}

void InternalSettingsGenerated::setWebRTCDTMFEnabled(bool webRTCDTMFEnabled)
{
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCDTMFEnabled(webRTCDTMFEnabled);
#else
    UNUSED_PARAM(webRTCDTMFEnabled);
#endif
}

void InternalSettingsGenerated::setWebRTCEncodedTransformEnabled(bool webRTCEncodedTransformEnabled)
{
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCEncodedTransformEnabled(webRTCEncodedTransformEnabled);
#else
    UNUSED_PARAM(webRTCEncodedTransformEnabled);
#endif
}

void InternalSettingsGenerated::setWebRTCEncryptionEnabled(bool webRTCEncryptionEnabled)
{
    m_page->settings().setWebRTCEncryptionEnabled(webRTCEncryptionEnabled);
}

void InternalSettingsGenerated::setWebRTCH265CodecEnabled(bool webRTCH265CodecEnabled)
{
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCH265CodecEnabled(webRTCH265CodecEnabled);
#else
    UNUSED_PARAM(webRTCH265CodecEnabled);
#endif
}

void InternalSettingsGenerated::setWebRTCMediaPipelineAdditionalLoggingEnabled(bool webRTCMediaPipelineAdditionalLoggingEnabled)
{
#if USE(LIBWEBRTC)
    m_page->settings().setWebRTCMediaPipelineAdditionalLoggingEnabled(webRTCMediaPipelineAdditionalLoggingEnabled);
#else
    UNUSED_PARAM(webRTCMediaPipelineAdditionalLoggingEnabled);
#endif
}

void InternalSettingsGenerated::setWebRTCPlatformCodecsInGPUProcessEnabled(bool webRTCPlatformCodecsInGPUProcessEnabled)
{
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCPlatformCodecsInGPUProcessEnabled(webRTCPlatformCodecsInGPUProcessEnabled);
#else
    UNUSED_PARAM(webRTCPlatformCodecsInGPUProcessEnabled);
#endif
}

void InternalSettingsGenerated::setWebRTCRemoteVideoFrameEnabled(bool webRTCRemoteVideoFrameEnabled)
{
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCRemoteVideoFrameEnabled(webRTCRemoteVideoFrameEnabled);
#else
    UNUSED_PARAM(webRTCRemoteVideoFrameEnabled);
#endif
}

void InternalSettingsGenerated::setWebRTCSFrameTransformEnabled(bool webRTCSFrameTransformEnabled)
{
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCSFrameTransformEnabled(webRTCSFrameTransformEnabled);
#else
    UNUSED_PARAM(webRTCSFrameTransformEnabled);
#endif
}

void InternalSettingsGenerated::setWebRTCSocketsProxyingEnabled(bool webRTCSocketsProxyingEnabled)
{
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCSocketsProxyingEnabled(webRTCSocketsProxyingEnabled);
#else
    UNUSED_PARAM(webRTCSocketsProxyingEnabled);
#endif
}

void InternalSettingsGenerated::setWebRTCVP9Profile0CodecEnabled(bool webRTCVP9Profile0CodecEnabled)
{
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCVP9Profile0CodecEnabled(webRTCVP9Profile0CodecEnabled);
#else
    UNUSED_PARAM(webRTCVP9Profile0CodecEnabled);
#endif
}

void InternalSettingsGenerated::setWebRTCVP9Profile2CodecEnabled(bool webRTCVP9Profile2CodecEnabled)
{
#if ENABLE(WEB_RTC)
    m_page->settings().setWebRTCVP9Profile2CodecEnabled(webRTCVP9Profile2CodecEnabled);
#else
    UNUSED_PARAM(webRTCVP9Profile2CodecEnabled);
#endif
}

void InternalSettingsGenerated::setWebSecurityEnabled(bool webSecurityEnabled)
{
    m_page->settings().setWebSecurityEnabled(webSecurityEnabled);
}

void InternalSettingsGenerated::setWebShareEnabled(bool webShareEnabled)
{
    m_page->settings().setWebShareEnabled(webShareEnabled);
}

void InternalSettingsGenerated::setWebShareFileAPIEnabled(bool webShareFileAPIEnabled)
{
    m_page->settings().setWebShareFileAPIEnabled(webShareFileAPIEnabled);
}

void InternalSettingsGenerated::setWebSocketEnabled(bool webSocketEnabled)
{
    m_page->settings().setWebSocketEnabled(webSocketEnabled);
}

void InternalSettingsGenerated::setWebXRAugmentedRealityModuleEnabled(bool webXRAugmentedRealityModuleEnabled)
{
#if ENABLE(WEBXR)
    m_page->settings().setWebXRAugmentedRealityModuleEnabled(webXRAugmentedRealityModuleEnabled);
#else
    UNUSED_PARAM(webXRAugmentedRealityModuleEnabled);
#endif
}

void InternalSettingsGenerated::setWebXREnabled(bool webXREnabled)
{
#if ENABLE(WEBXR)
    m_page->settings().setWebXREnabled(webXREnabled);
#else
    UNUSED_PARAM(webXREnabled);
#endif
}

void InternalSettingsGenerated::setWebXRGamepadsModuleEnabled(bool webXRGamepadsModuleEnabled)
{
#if ENABLE(WEBXR)
    m_page->settings().setWebXRGamepadsModuleEnabled(webXRGamepadsModuleEnabled);
#else
    UNUSED_PARAM(webXRGamepadsModuleEnabled);
#endif
}

void InternalSettingsGenerated::setWebXRHandInputModuleEnabled(bool webXRHandInputModuleEnabled)
{
#if ENABLE(WEBXR_HANDS)
    m_page->settings().setWebXRHandInputModuleEnabled(webXRHandInputModuleEnabled);
#else
    UNUSED_PARAM(webXRHandInputModuleEnabled);
#endif
}

void InternalSettingsGenerated::setWebkitImageReadyEventEnabled(bool webkitImageReadyEventEnabled)
{
    m_page->settings().setWebkitImageReadyEventEnabled(webkitImageReadyEventEnabled);
}

void InternalSettingsGenerated::setWheelEventGesturesBecomeNonBlocking(bool wheelEventGesturesBecomeNonBlocking)
{
    m_page->settings().setWheelEventGesturesBecomeNonBlocking(wheelEventGesturesBecomeNonBlocking);
}

void InternalSettingsGenerated::setWindowFocusRestricted(bool windowFocusRestricted)
{
    m_page->settings().setWindowFocusRestricted(windowFocusRestricted);
}

void InternalSettingsGenerated::setWirelessPlaybackTargetAPIEnabled(bool wirelessPlaybackTargetAPIEnabled)
{
    m_page->settings().setWirelessPlaybackTargetAPIEnabled(wirelessPlaybackTargetAPIEnabled);
}

void InternalSettingsGenerated::setYouTubeFlashPluginReplacementEnabled(bool youTubeFlashPluginReplacementEnabled)
{
    m_page->settings().setYouTubeFlashPluginReplacementEnabled(youTubeFlashPluginReplacementEnabled);
}

} // namespace WebCore
