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

#pragma once

#include <wtf/RefCounted.h>
#include <wtf/WeakPtr.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

class Page;

class InternalSettingsGenerated : public RefCounted<InternalSettingsGenerated> {
public:
    explicit InternalSettingsGenerated(Page*);
    virtual ~InternalSettingsGenerated();

    void resetToConsistentState();

    void setCSSOMViewScrollingAPIEnabled(bool CSSOMViewScrollingAPIEnabled);
    void setCSSOMViewSmoothScrollingEnabled(bool CSSOMViewSmoothScrollingEnabled);
    void setAbortSignalAnyOperationEnabled(bool abortSignalAnyOperationEnabled);
    void setAcceleratedCompositedAnimationsEnabled(bool acceleratedCompositedAnimationsEnabled);
    void setAcceleratedCompositingEnabled(bool acceleratedCompositingEnabled);
    void setAcceleratedCompositingForFixedPositionEnabled(bool acceleratedCompositingForFixedPositionEnabled);
    void setAcceleratedDrawingEnabled(bool acceleratedDrawingEnabled);
    void setAcceleratedFiltersEnabled(bool acceleratedFiltersEnabled);
    void setAccentColorEnabled(bool accentColorEnabled);
    void setAccessHandleEnabled(bool accessHandleEnabled);
    void setAggressiveTileRetentionEnabled(bool aggressiveTileRetentionEnabled);
    void setAllowAnimationControlsOverride(bool allowAnimationControlsOverride);
    void setAllowContentSecurityPolicySourceStarToMatchAnyProtocol(bool allowContentSecurityPolicySourceStarToMatchAnyProtocol);
    void setAllowCrossOriginSubresourcesToAskForCredentials(bool allowCrossOriginSubresourcesToAskForCredentials);
    void setAllowDisplayOfInsecureContent(bool allowDisplayOfInsecureContent);
    void setAllowFileAccessFromFileURLs(bool allowFileAccessFromFileURLs);
    void setAllowMediaContentTypesRequiringHardwareSupportAsFallback(bool allowMediaContentTypesRequiringHardwareSupportAsFallback);
    void setAllowMultiElementImplicitSubmission(bool allowMultiElementImplicitSubmission);
    void setAllowRunningOfInsecureContent(bool allowRunningOfInsecureContent);
    void setAllowSettingAnyXHRHeaderFromFileURLs(bool allowSettingAnyXHRHeaderFromFileURLs);
    void setAllowTopNavigationToDataURLs(bool allowTopNavigationToDataURLs);
    void setAllowUniversalAccessFromFileURLs(bool allowUniversalAccessFromFileURLs);
    void setAllowViewportShrinkToFitContent(bool allowViewportShrinkToFitContent);
    void setAllowWebGLInWorkers(bool allowWebGLInWorkers);
    void setAllowsAirPlayForMediaPlayback(bool allowsAirPlayForMediaPlayback);
    void setAllowsInlineMediaPlayback(bool allowsInlineMediaPlayback);
    void setAllowsInlineMediaPlaybackAfterFullscreen(bool allowsInlineMediaPlaybackAfterFullscreen);
    void setAllowsPictureInPictureMediaPlayback(bool allowsPictureInPictureMediaPlayback);
    void setAlternateFormControlDesignEnabled(bool alternateFormControlDesignEnabled);
    void setAlternateFullScreenControlDesignEnabled(bool alternateFullScreenControlDesignEnabled);
    void setAlternateWebMPlayerEnabled(bool alternateWebMPlayerEnabled);
    void setAnimatedImageAsyncDecodingEnabled(bool animatedImageAsyncDecodingEnabled);
    void setAnimatedImageDebugCanvasDrawingEnabled(bool animatedImageDebugCanvasDrawingEnabled);
    void setAppBadgeEnabled(bool appBadgeEnabled);
    void setAppHighlightsEnabled(bool appHighlightsEnabled);
    void setAppleMailPaginationQuirkEnabled(bool appleMailPaginationQuirkEnabled);
    void setApplePayCapabilityDisclosureAllowed(bool applePayCapabilityDisclosureAllowed);
    void setApplePayEnabled(bool applePayEnabled);
    void setAriaReflectionForElementReferencesEnabled(bool ariaReflectionForElementReferencesEnabled);
    void setAspectRatioEnabled(bool aspectRatioEnabled);
    void setAspectRatioOfImgFromWidthAndHeightEnabled(bool aspectRatioOfImgFromWidthAndHeightEnabled);
    void setAsyncClipboardAPIEnabled(bool asyncClipboardAPIEnabled);
    void setAsyncFrameScrollingEnabled(bool asyncFrameScrollingEnabled);
    void setAsyncOverflowScrollingEnabled(bool asyncOverflowScrollingEnabled);
    void setAsynchronousSpellCheckingEnabled(bool asynchronousSpellCheckingEnabled);
    void setAttachmentWideLayoutEnabled(bool attachmentWideLayoutEnabled);
    void setAudioControlsScaleWithPageZoom(bool audioControlsScaleWithPageZoom);
    void setAudioDescriptionsEnabled(bool audioDescriptionsEnabled);
    void setAuthorAndUserStylesEnabled(bool authorAndUserStylesEnabled);
    void setAutoscrollForDragAndDropEnabled(bool autoscrollForDragAndDropEnabled);
    void setBackgroundFetchAPIEnabled(bool backgroundFetchAPIEnabled);
    void setBackgroundShouldExtendBeyondPage(bool backgroundShouldExtendBeyondPage);
    void setBackgroundWebContentRunningBoardThrottlingEnabled(bool backgroundWebContentRunningBoardThrottlingEnabled);
    void setBackspaceKeyNavigationEnabled(bool backspaceKeyNavigationEnabled);
    void setBeaconAPIEnabled(bool beaconAPIEnabled);
    void setBlockMediaLayerRehostingInWebContentProcess(bool blockMediaLayerRehostingInWebContentProcess);
    void setBroadcastChannelEnabled(bool broadcastChannelEnabled);
    void setBroadcastChannelOriginPartitioningEnabled(bool broadcastChannelOriginPartitioningEnabled);
    void setCacheAPIEnabled(bool cacheAPIEnabled);
    void setCanvasColorSpaceEnabled(bool canvasColorSpaceEnabled);
    void setCanvasFiltersEnabled(bool canvasFiltersEnabled);
    void setCanvasFingerprintingQuirkEnabled(bool canvasFingerprintingQuirkEnabled);
    void setCanvasUsesAcceleratedDrawing(bool canvasUsesAcceleratedDrawing);
    void setCaretBrowsingEnabled(bool caretBrowsingEnabled);
    void setClearSiteDataHTTPHeaderEnabled(bool clearSiteDataHTTPHeaderEnabled);
    void setClientBadgeEnabled(bool clientBadgeEnabled);
    void setClientCoordinatesRelativeToLayoutViewport(bool clientCoordinatesRelativeToLayoutViewport);
    void setColorFilterEnabled(bool colorFilterEnabled);
    void setCompressionStreamEnabled(bool compressionStreamEnabled);
    void setConstantPropertiesEnabled(bool constantPropertiesEnabled);
    void setConstructableStylesheetsEnabled(bool constructableStylesheetsEnabled);
    void setContactPickerAPIEnabled(bool contactPickerAPIEnabled);
    void setContentChangeObserverEnabled(bool contentChangeObserverEnabled);
    void setContentDispositionAttachmentSandboxEnabled(bool contentDispositionAttachmentSandboxEnabled);
    void setContextMenuQRCodeDetectionEnabled(bool contextMenuQRCodeDetectionEnabled);
    void setCookieConsentAPIEnabled(bool cookieConsentAPIEnabled);
    void setCookieEnabled(bool cookieEnabled);
    void setCookieStoreAPIEnabled(bool cookieStoreAPIEnabled);
    void setCookieStoreAPIExtendedAttributesEnabled(bool cookieStoreAPIExtendedAttributesEnabled);
    void setCoreMathMLEnabled(bool coreMathMLEnabled);
    void setCrossOriginCheckInGetMatchedCSSRulesDisabled(bool crossOriginCheckInGetMatchedCSSRulesDisabled);
    void setCrossOriginEmbedderPolicyEnabled(bool crossOriginEmbedderPolicyEnabled);
    void setCrossOriginOpenerPolicyEnabled(bool crossOriginOpenerPolicyEnabled);
    void setCSS3DTransformInteroperabilityEnabled(bool css3DTransformInteroperabilityEnabled);
    void setCSSCascadeLayersEnabled(bool cssCascadeLayersEnabled);
    void setCSSColor4(bool cssColor4);
    void setCSSColorContrastEnabled(bool cssColorContrastEnabled);
    void setCSSColorMixEnabled(bool cssColorMixEnabled);
    void setCSSContainIntrinsicSizeEnabled(bool cssContainIntrinsicSizeEnabled);
    void setCSSContainerQueriesEnabled(bool cssContainerQueriesEnabled);
    void setCSSContainmentEnabled(bool cssContainmentEnabled);
    void setCSSContentVisibilityEnabled(bool cssContentVisibilityEnabled);
    void setCSSCounterStyleAtRuleImageSymbolsEnabled(bool cssCounterStyleAtRuleImageSymbolsEnabled);
    void setCSSCounterStyleAtRulesEnabled(bool cssCounterStyleAtRulesEnabled);
    void setCSSCustomPropertiesAndValuesEnabled(bool cssCustomPropertiesAndValuesEnabled);
    void setCSSFontFaceSizeAdjustEnabled(bool cssFontFaceSizeAdjustEnabled);
    void setCSSGradientInterpolationColorSpacesEnabled(bool cssGradientInterpolationColorSpacesEnabled);
    void setCSSGradientPremultipliedAlphaInterpolationEnabled(bool cssGradientPremultipliedAlphaInterpolationEnabled);
    void setCSSIndividualTransformPropertiesEnabled(bool cssIndividualTransformPropertiesEnabled);
    void setCSSInputSecurityEnabled(bool cssInputSecurityEnabled);
    void setCSSMarginTrimEnabled(bool cssMarginTrimEnabled);
    void setCSSMotionPathEnabled(bool cssMotionPathEnabled);
    void setCSSNestingEnabled(bool cssNestingEnabled);
    void setCSSPaintingAPIEnabled(bool cssPaintingAPIEnabled);
    void setCSSRelativeColorSyntaxEnabled(bool cssRelativeColorSyntaxEnabled);
    void setCSSRhythmicSizingEnabled(bool cssRhythmicSizingEnabled);
    void setCSSScrollAnchoringEnabled(bool cssScrollAnchoringEnabled);
    void setCSSScrollbarColorEnabled(bool cssScrollbarColorEnabled);
    void setCSSScrollbarGutterEnabled(bool cssScrollbarGutterEnabled);
    void setCSSScrollbarWidthEnabled(bool cssScrollbarWidthEnabled);
    void setCSSTextAlignLastEnabled(bool cssTextAlignLastEnabled);
    void setCSSTextBoxTrimEnabled(bool cssTextBoxTrimEnabled);
    void setCSSTextGroupAlignEnabled(bool cssTextGroupAlignEnabled);
    void setCSSTextJustifyEnabled(bool cssTextJustifyEnabled);
    void setCSSTextSpacingEnabled(bool cssTextSpacingEnabled);
    void setCSSTextUnderlinePositionLeftRightEnabled(bool cssTextUnderlinePositionLeftRightEnabled);
    void setCSSTextWrapNewValuesEnabled(bool cssTextWrapNewValuesEnabled);
    void setCSSTransformStyleOptimized3DEnabled(bool cssTransformStyleOptimized3DEnabled);
    void setCSSTypedOMColorEnabled(bool cssTypedOMColorEnabled);
    void setCSSTypedOMEnabled(bool cssTypedOMEnabled);
    void setCSSWhiteSpaceLonghandsEnabled(bool cssWhiteSpaceLonghandsEnabled);
    void setCSSWordBreakAutoEnabled(bool cssWordBreakAutoEnabled);
    void setCursiveFontFamily(const String& cursiveFontFamily);
    void setDataListElementEnabled(bool dataListElementEnabled);
    void setDataTransferItemsEnabled(bool dataTransferItemsEnabled);
    void setDateTimeInputsEditableComponentsEnabled(bool dateTimeInputsEditableComponentsEnabled);
    void setDeclarativeShadowDOMEnabled(bool declarativeShadowDOMEnabled);
    void setDeclarativeShadowDOMInDOMParserEnabled(bool declarativeShadowDOMInDOMParserEnabled);
    void setDefaultARIAForCustomElementsEnabled(bool defaultARIAForCustomElementsEnabled);
    void setDefaultFixedFontSize(double defaultFixedFontSize);
    void setDefaultFontSize(double defaultFontSize);
    void setDefaultTextEncodingName(const String& defaultTextEncodingName);
    void setDefaultVideoPosterURL(const String& defaultVideoPosterURL);
    void setDeprecateRSAESPKCSWebCryptoEnabled(bool deprecateRSAESPKCSWebCryptoEnabled);
    void setDeprecationReportingEnabled(bool deprecationReportingEnabled);
    void setDeveloperExtrasEnabled(bool developerExtrasEnabled);
    void setDeviceHeight(uint32_t deviceHeight);
    void setDeviceOrientationEventEnabled(bool deviceOrientationEventEnabled);
    void setDeviceOrientationPermissionAPIEnabled(bool deviceOrientationPermissionAPIEnabled);
    void setDeviceWidth(uint32_t deviceWidth);
    void setDiagnosticLoggingEnabled(bool diagnosticLoggingEnabled);
    void setDialogElementEnabled(bool dialogElementEnabled);
    void setDirPseudoEnabled(bool dirPseudoEnabled);
    void setDirectoryUploadEnabled(bool directoryUploadEnabled);
    void setDisabledAdaptationsMetaTagEnabled(bool disabledAdaptationsMetaTagEnabled);
    void setDisallowSyncXHRDuringPageDismissalEnabled(bool disallowSyncXHRDuringPageDismissalEnabled);
    void setDisplayListDrawingEnabled(bool displayListDrawingEnabled);
    void setDNSPrefetchingEnabled(bool dnsPrefetchingEnabled);
    void setDOMAudioSessionEnabled(bool domAudioSessionEnabled);
    void setDOMAudioSessionFullEnabled(bool domAudioSessionFullEnabled);
    void setDOMPasteAccessRequestsEnabled(bool domPasteAccessRequestsEnabled);
    void setDOMPasteAllowed(bool domPasteAllowed);
    void setDOMTestingAPIsEnabled(bool domTestingAPIsEnabled);
    void setDOMTimersThrottlingEnabled(bool domTimersThrottlingEnabled);
    void setDownloadAttributeEnabled(bool downloadAttributeEnabled);
    void setEmbedElementEnabled(bool embedElementEnabled);
    void setEnableInheritURIQueryComponent(bool enableInheritURIQueryComponent);
    void setEncryptedMediaAPIEnabled(bool encryptedMediaAPIEnabled);
    void setEnterKeyHintEnabled(bool enterKeyHintEnabled);
    void setEventHandlerDrivenSmoothKeyboardScrollingEnabled(bool eventHandlerDrivenSmoothKeyboardScrollingEnabled);
    void setExposeSpeakersEnabled(bool exposeSpeakersEnabled);
    void setExtendedAudioDescriptionsEnabled(bool extendedAudioDescriptionsEnabled);
    void setFantasyFontFamily(const String& fantasyFontFamily);
    void setFetchAPIEnabled(bool fetchAPIEnabled);
    void setFetchMetadataEnabled(bool fetchMetadataEnabled);
    void setFetchPriorityEnabled(bool fetchPriorityEnabled);
    void setFileReaderAPIEnabled(bool fileReaderAPIEnabled);
    void setFileSystemAccessEnabled(bool fileSystemAccessEnabled);
    void setFixedBackgroundsPaintRelativeToDocument(bool fixedBackgroundsPaintRelativeToDocument);
    void setFixedElementsLayoutRelativeToFrame(bool fixedElementsLayoutRelativeToFrame);
    void setFixedFontFamily(const String& fixedFontFamily);
    void setFlexFormattingContextIntegrationEnabled(bool flexFormattingContextIntegrationEnabled);
    void setFocusVisibleEnabled(bool focusVisibleEnabled);
    void setFontFallbackPrefersPictographs(bool fontFallbackPrefersPictographs);
    void setForceCompositingMode(bool forceCompositingMode);
    void setForceFTPDirectoryListings(bool forceFTPDirectoryListings);
    void setForceWebGLUsesLowPower(bool forceWebGLUsesLowPower);
    void setFormAssociatedCustomElementsEnabled(bool formAssociatedCustomElementsEnabled);
    void setFTPDirectoryTemplatePath(const String& ftpDirectoryTemplatePath);
    void setFTPEnabled(bool ftpEnabled);
    void setFullScreenEnabled(bool fullScreenEnabled);
    void setFullscreenRequirementForScreenOrientationLockingEnabled(bool fullscreenRequirementForScreenOrientationLockingEnabled);
    void setFullscreenSceneAspectRatioLockingEnabled(bool fullscreenSceneAspectRatioLockingEnabled);
    void setFullscreenSceneDimmingEnabled(bool fullscreenSceneDimmingEnabled);
    void setGamepadTriggerRumbleEnabled(bool gamepadTriggerRumbleEnabled);
    void setGamepadVibrationActuatorEnabled(bool gamepadVibrationActuatorEnabled);
    void setGamepadsEnabled(bool gamepadsEnabled);
    void setGenericCueAPIEnabled(bool genericCueAPIEnabled);
    void setGeolocationFloorLevelEnabled(bool geolocationFloorLevelEnabled);
    void setGetUserMediaRequiresFocus(bool getUserMediaRequiresFocus);
    void setGoogleAntiFlickerOptimizationQuirkEnabled(bool googleAntiFlickerOptimizationQuirkEnabled);
    void setGraphicsContextFiltersEnabled(bool graphicsContextFiltersEnabled);
    void setHasPseudoClassEnabled(bool hasPseudoClassEnabled);
    void setHiddenPageCSSAnimationSuspensionEnabled(bool hiddenPageCSSAnimationSuspensionEnabled);
    void setHiddenPageDOMTimerThrottlingAutoIncreases(bool hiddenPageDOMTimerThrottlingAutoIncreases);
    void setHiddenPageDOMTimerThrottlingEnabled(bool hiddenPageDOMTimerThrottlingEnabled);
    void setHttpEquivEnabled(bool httpEquivEnabled);
    void setHyperlinkAuditingEnabled(bool hyperlinkAuditingEnabled);
    void setIOSFormControlRefreshEnabled(bool iOSFormControlRefreshEnabled);
    void setICECandidateFilteringEnabled(bool iceCandidateFilteringEnabled);
    void setIdempotentModeAutosizingOnlyHonorsPercentages(bool idempotentModeAutosizingOnlyHonorsPercentages);
    void setImageAnalysisDuringFindInPageEnabled(bool imageAnalysisDuringFindInPageEnabled);
    void setImageAnimationControlEnabled(bool imageAnimationControlEnabled);
    void setImageControlsEnabled(bool imageControlsEnabled);
    void setImageSubsamplingEnabled(bool imageSubsamplingEnabled);
    void setImagesEnabled(bool imagesEnabled);
    void setImperativeSlotAPIEnabled(bool imperativeSlotAPIEnabled);
    void setIncompleteImageBorderEnabled(bool incompleteImageBorderEnabled);
    void setIncrementalPDFLoadingEnabled(bool incrementalPDFLoadingEnabled);
    void setIncrementalRenderingSuppressionTimeoutInSeconds(double incrementalRenderingSuppressionTimeoutInSeconds);
    void setIndexedDBAPIEnabled(bool indexedDBAPIEnabled);
    void setInertAttributeEnabled(bool inertAttributeEnabled);
    void setInlineMediaPlaybackRequiresPlaysInlineAttribute(bool inlineMediaPlaybackRequiresPlaysInlineAttribute);
    void setInlinePredictionsInAllEditableElementsEnabled(bool inlinePredictionsInAllEditableElementsEnabled);
    void setInputTypeColorEnabled(bool inputTypeColorEnabled);
    void setInputTypeDateEnabled(bool inputTypeDateEnabled);
    void setInputTypeDateTimeLocalEnabled(bool inputTypeDateTimeLocalEnabled);
    void setInputTypeMonthEnabled(bool inputTypeMonthEnabled);
    void setInputTypeTimeEnabled(bool inputTypeTimeEnabled);
    void setInputTypeWeekEnabled(bool inputTypeWeekEnabled);
    void setInteractionRegionInlinePadding(double interactionRegionInlinePadding);
    void setInteractionRegionMinimumCornerRadius(double interactionRegionMinimumCornerRadius);
    void setInteractionRegionsEnabled(bool interactionRegionsEnabled);
    void setInteractiveFormValidationEnabled(bool interactiveFormValidationEnabled);
    void setInterruptAudioOnPageVisibilityChangeEnabled(bool interruptAudioOnPageVisibilityChangeEnabled);
    void setInterruptVideoOnPageVisibilityChangeEnabled(bool interruptVideoOnPageVisibilityChangeEnabled);
    void setIntersectionObserverEnabled(bool intersectionObserverEnabled);
    void setInvisibleAutoplayNotPermitted(bool invisibleAutoplayNotPermitted);
    void setIsFirstPartyWebsiteDataRemovalDisabled(bool isFirstPartyWebsiteDataRemovalDisabled);
    void setIsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled(bool isFirstPartyWebsiteDataRemovalLiveOnTestingEnabled);
    void setIsFirstPartyWebsiteDataRemovalReproTestingEnabled(bool isFirstPartyWebsiteDataRemovalReproTestingEnabled);
    void setIsLoggedInAPIEnabled(bool isLoggedInAPIEnabled);
    void setIsPerActivityStateCPUUsageMeasurementEnabled(bool isPerActivityStateCPUUsageMeasurementEnabled);
    void setIsPostBackgroundingCPUUsageMeasurementEnabled(bool isPostBackgroundingCPUUsageMeasurementEnabled);
    void setIsPostBackgroundingMemoryUsageMeasurementEnabled(bool isPostBackgroundingMemoryUsageMeasurementEnabled);
    void setIsPostLoadCPUUsageMeasurementEnabled(bool isPostLoadCPUUsageMeasurementEnabled);
    void setIsPostLoadMemoryUsageMeasurementEnabled(bool isPostLoadMemoryUsageMeasurementEnabled);
    void setIsSameSiteStrictEnforcementEnabled(bool isSameSiteStrictEnforcementEnabled);
    void setIsThirdPartyCookieBlockingDisabled(bool isThirdPartyCookieBlockingDisabled);
    void setItpDebugModeEnabled(bool itpDebugModeEnabled);
    void setJavaScriptCanAccessClipboard(bool javaScriptCanAccessClipboard);
    void setJavaScriptCanOpenWindowsAutomatically(bool javaScriptCanOpenWindowsAutomatically);
    void setLangAttributeAwareFormControlUIEnabled(bool langAttributeAwareFormControlUIEnabled);
    void setLargeImageAsyncDecodingEnabled(bool largeImageAsyncDecodingEnabled);
    void setLayerBasedSVGEngineEnabled(bool layerBasedSVGEngineEnabled);
    void setLayoutFallbackWidth(uint32_t layoutFallbackWidth);
    void setLayoutFormattingContextEnabled(bool layoutFormattingContextEnabled);
    void setLayoutViewportHeightExpansionFactor(double layoutViewportHeightExpansionFactor);
    void setLazyIframeLoadingEnabled(bool lazyIframeLoadingEnabled);
    void setLazyImageLoadingEnabled(bool lazyImageLoadingEnabled);
    void setLegacyEncryptedMediaAPIEnabled(bool legacyEncryptedMediaAPIEnabled);
    void setLegacyLineLayoutVisualCoverageEnabled(bool legacyLineLayoutVisualCoverageEnabled);
    void setLegacyOverflowScrollingTouchEnabled(bool legacyOverflowScrollingTouchEnabled);
    void setLinkModulePreloadEnabled(bool linkModulePreloadEnabled);
    void setLinkPreconnectEarlyHintsEnabled(bool linkPreconnectEarlyHintsEnabled);
    void setLinkPreconnectEnabled(bool linkPreconnectEnabled);
    void setLinkPrefetchEnabled(bool linkPrefetchEnabled);
    void setLinkPreloadEnabled(bool linkPreloadEnabled);
    void setLinkPreloadResponsiveImagesEnabled(bool linkPreloadResponsiveImagesEnabled);
    void setLinkSanitizerEnabled(bool linkSanitizerEnabled);
    void setLiveRangeSelectionEnabled(bool liveRangeSelectionEnabled);
    void setLoadDeferringEnabled(bool loadDeferringEnabled);
    void setLoadsImagesAutomatically(bool loadsImagesAutomatically);
    void setLocalFileContentSniffingEnabled(bool localFileContentSniffingEnabled);
    void setLocalStorageDatabasePath(const String& localStorageDatabasePath);
    void setLocalStorageEnabled(bool localStorageEnabled);
    void setLogsPageMessagesToSystemConsoleEnabled(bool logsPageMessagesToSystemConsoleEnabled);
    void setMainContentUserGestureOverrideEnabled(bool mainContentUserGestureOverrideEnabled);
    void setManageCaptureStatusBarInGPUProcessEnabled(bool manageCaptureStatusBarInGPUProcessEnabled);
    void setManagedMediaSourceEnabled(bool managedMediaSourceEnabled);
    void setManagedMediaSourceHighThreshold(double managedMediaSourceHighThreshold);
    void setManagedMediaSourceLowThreshold(double managedMediaSourceLowThreshold);
    void setManagedMediaSourceNeedsAirPlay(bool managedMediaSourceNeedsAirPlay);
    void setMaskWebGLStringsEnabled(bool maskWebGLStringsEnabled);
    void setMasonryEnabled(bool masonryEnabled);
    void setMasonryTrackAlignmentEnabled(bool masonryTrackAlignmentEnabled);
    void setMathMLEnabled(bool mathMLEnabled);
    void setMaxParseDuration(double maxParseDuration);
    void setMaximumAccelerated2dCanvasSize(uint32_t maximumAccelerated2dCanvasSize);
    void setMaximumHTMLParserDOMTreeDepth(uint32_t maximumHTMLParserDOMTreeDepth);
    void setMaximumSourceBufferSize(uint32_t maximumSourceBufferSize);
    void setMediaCapabilitiesEnabled(bool mediaCapabilitiesEnabled);
    void setMediaCapabilitiesExtensionsEnabled(bool mediaCapabilitiesExtensionsEnabled);
    void setMediaCaptureRequiresSecureConnection(bool mediaCaptureRequiresSecureConnection);
    void setMediaControlsContextMenusEnabled(bool mediaControlsContextMenusEnabled);
    void setMediaControlsScaleWithPageZoom(bool mediaControlsScaleWithPageZoom);
    void setMediaDataLoadsAutomatically(bool mediaDataLoadsAutomatically);
    void setMediaDevicesEnabled(bool mediaDevicesEnabled);
    void setMediaEnabled(bool mediaEnabled);
    void setMediaKeysStorageDirectory(const String& mediaKeysStorageDirectory);
    void setMediaPreferredFullscreenWidth(double mediaPreferredFullscreenWidth);
    void setMediaPreloadingEnabled(bool mediaPreloadingEnabled);
    void setMediaRecorderEnabled(bool mediaRecorderEnabled);
    void setMediaSessionCoordinatorEnabled(bool mediaSessionCoordinatorEnabled);
    void setMediaSessionEnabled(bool mediaSessionEnabled);
    void setMediaSessionPlaylistEnabled(bool mediaSessionPlaylistEnabled);
    void setMediaSourceEnabled(bool mediaSourceEnabled);
    void setMediaStreamEnabled(bool mediaStreamEnabled);
    void setMediaTypeOverride(const String& mediaTypeOverride);
    void setMediaUserGestureInheritsFromDocument(bool mediaUserGestureInheritsFromDocument);
    void setMenuItemElementEnabled(bool menuItemElementEnabled);
    void setMinimumAccelerated2dCanvasSize(uint32_t minimumAccelerated2dCanvasSize);
    void setMinimumFontSize(double minimumFontSize);
    void setMinimumLogicalFontSize(double minimumLogicalFontSize);
    void setMinimumZoomFontSize(double minimumZoomFontSize);
    void setMockCaptureDevicesEnabled(bool mockCaptureDevicesEnabled);
    void setMockScrollbarsControllerEnabled(bool mockScrollbarsControllerEnabled);
    void setModelElementEnabled(bool modelElementEnabled);
    void setMomentumScrollingAnimatorEnabled(bool momentumScrollingAnimatorEnabled);
    void setMouseEventsSimulationEnabled(bool mouseEventsSimulationEnabled);
    void setMuteCameraOnMicrophoneInterruptionEnabled(bool muteCameraOnMicrophoneInterruptionEnabled);
    void setNeedsAdobeFrameReloadingQuirk(bool needsAdobeFrameReloadingQuirk);
    void setNeedsDeferKeyDownAndKeyPressTimersUntilNextEditingCommandQuirk(bool needsDeferKeyDownAndKeyPressTimersUntilNextEditingCommandQuirk);
    void setNeedsFrameNameFallbackToIdQuirk(bool needsFrameNameFallbackToIdQuirk);
    void setNeedsKeyboardEventDisambiguationQuirks(bool needsKeyboardEventDisambiguationQuirks);
    void setNeedsSiteSpecificQuirks(bool needsSiteSpecificQuirks);
    void setNeedsStorageAccessFromFileURLsQuirk(bool needsStorageAccessFromFileURLsQuirk);
    void setNotificationEventEnabled(bool notificationEventEnabled);
    void setNotificationsEnabled(bool notificationsEnabled);
    void setOfflineWebApplicationCacheEnabled(bool offlineWebApplicationCacheEnabled);
    void setOffscreenCanvasEnabled(bool offscreenCanvasEnabled);
    void setOffscreenCanvasInWorkersEnabled(bool offscreenCanvasInWorkersEnabled);
    void setOverflowClipEnabled(bool overflowClipEnabled);
    void setOverscrollBehaviorEnabled(bool overscrollBehaviorEnabled);
    void setPageAtRuleSupportEnabled(bool pageAtRuleSupportEnabled);
    void setPassiveTouchListenersAsDefaultOnDocument(bool passiveTouchListenersAsDefaultOnDocument);
    void setPassiveWheelListenersAsDefaultOnDocument(bool passiveWheelListenersAsDefaultOnDocument);
    void setPasswordEchoDurationInSeconds(double passwordEchoDurationInSeconds);
    void setPasswordEchoEnabled(bool passwordEchoEnabled);
    void setPaymentRequestEnabled(bool paymentRequestEnabled);
    void setPdfJSViewerEnabled(bool pdfJSViewerEnabled);
    void setPeerConnectionEnabled(bool peerConnectionEnabled);
    void setPerElementSpeakerSelectionEnabled(bool perElementSpeakerSelectionEnabled);
    void setPerformanceNavigationTimingAPIEnabled(bool performanceNavigationTimingAPIEnabled);
    void setPerformanceResourceTimingSensitivePropertiesEnabled(bool performanceResourceTimingSensitivePropertiesEnabled);
    void setPermissionsAPIEnabled(bool permissionsAPIEnabled);
    void setPictographFontFamily(const String& pictographFontFamily);
    void setPictureInPictureAPIEnabled(bool pictureInPictureAPIEnabled);
    void setPluginsEnabled(bool pluginsEnabled);
    void setPopoverAttributeEnabled(bool popoverAttributeEnabled);
    void setPreferMIMETypeForImages(bool preferMIMETypeForImages);
    void setPreferPageRenderingUpdatesNear60FPSEnabled(bool preferPageRenderingUpdatesNear60FPSEnabled);
    void setPreferSandboxedMediaParsing(bool preferSandboxedMediaParsing);
    void setPreventKeyboardDOMEventDispatch(bool preventKeyboardDOMEventDispatch);
    void setPrivateClickMeasurementDebugModeEnabled(bool privateClickMeasurementDebugModeEnabled);
    void setPrivateClickMeasurementEnabled(bool privateClickMeasurementEnabled);
    void setPrivateClickMeasurementFraudPreventionEnabled(bool privateClickMeasurementFraudPreventionEnabled);
    void setPunchOutWhiteBackgroundsInDarkMode(bool punchOutWhiteBackgroundsInDarkMode);
    void setPushAPIEnabled(bool pushAPIEnabled);
    void setReferrerPolicyAttributeEnabled(bool referrerPolicyAttributeEnabled);
    void setRemotePlaybackEnabled(bool remotePlaybackEnabled);
    void setRemoveBackgroundEnabled(bool removeBackgroundEnabled);
    void setReportingEnabled(bool reportingEnabled);
    void setRequestIdleCallbackEnabled(bool requestIdleCallbackEnabled);
    void setRequestSubmitEnabled(bool requestSubmitEnabled);
    void setRequestVideoFrameCallbackEnabled(bool requestVideoFrameCallbackEnabled);
    void setRequireUAGetDisplayMediaPrompt(bool requireUAGetDisplayMediaPrompt);
    void setRequiresPageVisibilityToPlayAudio(bool requiresPageVisibilityToPlayAudio);
    void setRequiresUserGestureForAudioPlayback(bool requiresUserGestureForAudioPlayback);
    void setRequiresUserGestureForVideoPlayback(bool requiresUserGestureForVideoPlayback);
    void setRequiresUserGestureToLoadVideo(bool requiresUserGestureToLoadVideo);
    void setResizeObserverEnabled(bool resizeObserverEnabled);
    void setResourceLoadSchedulingEnabled(bool resourceLoadSchedulingEnabled);
    void setResourceUsageOverlayVisible(bool resourceUsageOverlayVisible);
    void setRubberBandingForSubScrollableRegionsEnabled(bool rubberBandingForSubScrollableRegionsEnabled);
    void setSKAttributionEnabled(bool sKAttributionEnabled);
    void setSampleBufferContentKeySessionSupportEnabled(bool sampleBufferContentKeySessionSupportEnabled);
    void setSampledPageTopColorMaxDifference(double sampledPageTopColorMaxDifference);
    void setSampledPageTopColorMinHeight(double sampledPageTopColorMinHeight);
    void setSansSerifFontFamily(const String& sansSerifFontFamily);
    void setScreenCaptureEnabled(bool screenCaptureEnabled);
    void setScreenOrientationAPIEnabled(bool screenOrientationAPIEnabled);
    void setScreenOrientationLockingAPIEnabled(bool screenOrientationLockingAPIEnabled);
    void setScreenWakeLockAPIEnabled(bool screenWakeLockAPIEnabled);
    void setScriptEnabled(bool scriptEnabled);
    void setScriptMarkupEnabled(bool scriptMarkupEnabled);
    void setScrollAnimatorEnabled(bool scrollAnimatorEnabled);
    void setScrollToTextFragmentEnabled(bool scrollToTextFragmentEnabled);
    void setScrollToTextFragmentIndicatorEnabled(bool scrollToTextFragmentIndicatorEnabled);
    void setScrollingCoordinatorEnabled(bool scrollingCoordinatorEnabled);
    void setScrollingPerformanceTestingEnabled(bool scrollingPerformanceTestingEnabled);
    void setScrollingTreeIncludesFrames(bool scrollingTreeIncludesFrames);
    void setSearchInputIncrementalAttributeAndSearchEventEnabled(bool searchInputIncrementalAttributeAndSearchEventEnabled);
    void setSecureContextChecksEnabled(bool secureContextChecksEnabled);
    void setSelectTrailingWhitespaceEnabled(bool selectTrailingWhitespaceEnabled);
    void setSelectionAPIForShadowDOMEnabled(bool selectionAPIForShadowDOMEnabled);
    void setSendMouseEventsToDisabledFormControlsEnabled(bool sendMouseEventsToDisabledFormControlsEnabled);
    void setSerifFontFamily(const String& serifFontFamily);
    void setServiceControlsEnabled(bool serviceControlsEnabled);
    void setServiceWorkerNavigationPreloadEnabled(bool serviceWorkerNavigationPreloadEnabled);
    void setServiceWorkersEnabled(bool serviceWorkersEnabled);
    void setServiceWorkersUserGestureEnabled(bool serviceWorkersUserGestureEnabled);
    void setSessionStorageQuota(uint32_t sessionStorageQuota);
    void setShapeDetection(bool shapeDetection);
    void setSharedWorkerEnabled(bool sharedWorkerEnabled);
    void setShouldAllowUserInstalledFonts(bool shouldAllowUserInstalledFonts);
    void setShouldConvertInvalidURLsToBlank(bool shouldConvertInvalidURLsToBlank);
    void setShouldConvertPositionStyleOnCopy(bool shouldConvertPositionStyleOnCopy);
    void setShouldDecidePolicyBeforeLoadingQuickLookPreview(bool shouldDecidePolicyBeforeLoadingQuickLookPreview);
    void setShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint(bool shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint);
    void setShouldDispatchSyntheticMouseEventsWhenModifyingSelection(bool shouldDispatchSyntheticMouseEventsWhenModifyingSelection);
    void setShouldDispatchSyntheticMouseOutAfterSyntheticClick(bool shouldDispatchSyntheticMouseOutAfterSyntheticClick);
    void setShouldDisplayCaptions(bool shouldDisplayCaptions);
    void setShouldDisplaySubtitles(bool shouldDisplaySubtitles);
    void setShouldDisplayTextDescriptions(bool shouldDisplayTextDescriptions);
    void setShouldDropNearSuspendedAssertionAfterDelay(bool shouldDropNearSuspendedAssertionAfterDelay);
    void setShouldEnableTextAutosizingBoost(bool shouldEnableTextAutosizingBoost);
    void setShouldIgnoreFontLoadCompletions(bool shouldIgnoreFontLoadCompletions);
    void setShouldIgnoreMetaViewport(bool shouldIgnoreMetaViewport);
    void setShouldInjectUserScriptsInInitialEmptyDocument(bool shouldInjectUserScriptsInInitialEmptyDocument);
    void setShouldPrintBackgrounds(bool shouldPrintBackgrounds);
    void setShouldRespectImageOrientation(bool shouldRespectImageOrientation);
    void setShouldRestrictBaseURLSchemes(bool shouldRestrictBaseURLSchemes);
    void setShouldSuppressTextInputFromEditingDuringProvisionalNavigation(bool shouldSuppressTextInputFromEditingDuringProvisionalNavigation);
    void setShouldTakeNearSuspendedAssertions(bool shouldTakeNearSuspendedAssertions);
    void setShouldUseServiceWorkerShortTimeout(bool shouldUseServiceWorkerShortTimeout);
    void setShowDebugBorders(bool showDebugBorders);
    void setShowMediaStatsContextMenuItemEnabled(bool showMediaStatsContextMenuItemEnabled);
    void setShowModalDialogEnabled(bool showModalDialogEnabled);
    void setShowRepaintCounter(bool showRepaintCounter);
    void setShowTiledScrollingIndicator(bool showTiledScrollingIndicator);
    void setShowsToolTipOverTruncatedText(bool showsToolTipOverTruncatedText);
    void setShowsURLsInToolTips(bool showsURLsInToolTips);
    void setShrinksStandaloneImagesToFit(bool shrinksStandaloneImagesToFit);
    void setSiteIsolationEnabled(bool siteIsolationEnabled);
    void setSmartInsertDeleteEnabled(bool smartInsertDeleteEnabled);
    void setSourceBufferChangeTypeEnabled(bool sourceBufferChangeTypeEnabled);
    void setSpatialNavigationEnabled(bool spatialNavigationEnabled);
    void setSpeakerSelectionRequiresUserGesture(bool speakerSelectionRequiresUserGesture);
    void setSpeechRecognitionEnabled(bool speechRecognitionEnabled);
    void setSpeechSynthesisAPIEnabled(bool speechSynthesisAPIEnabled);
    void setSpringTimingFunctionEnabled(bool springTimingFunctionEnabled);
    void setStandalone(bool standalone);
    void setStandardFontFamily(const String& standardFontFamily);
    void setStorageAPIEnabled(bool storageAPIEnabled);
    void setStorageAPIEstimateEnabled(bool storageAPIEstimateEnabled);
    void setStorageAccessAPIEnabled(bool storageAccessAPIEnabled);
    void setStorageAccessAPIPerPageScopeEnabled(bool storageAccessAPIPerPageScopeEnabled);
    void setSubgridEnabled(bool subgridEnabled);
    void setSuppressesIncrementalRendering(bool suppressesIncrementalRendering);
    void setSyntheticEditingCommandsEnabled(bool syntheticEditingCommandsEnabled);
    void setSystemPreviewEnabled(bool systemPreviewEnabled);
    void setTelephoneNumberParsingEnabled(bool telephoneNumberParsingEnabled);
    void setTemporaryTileCohortRetentionEnabled(bool temporaryTileCohortRetentionEnabled);
    void setTextAreasAreResizable(bool textAreasAreResizable);
    void setTextAutosizingEnabled(bool textAutosizingEnabled);
    void setTextAutosizingUsesIdempotentMode(bool textAutosizingUsesIdempotentMode);
    void setTextAutosizingWindowSizeOverrideHeight(uint32_t textAutosizingWindowSizeOverrideHeight);
    void setTextAutosizingWindowSizeOverrideWidth(uint32_t textAutosizingWindowSizeOverrideWidth);
    void setTextInteractionEnabled(bool textInteractionEnabled);
    void setTextRecognitionInVideosEnabled(bool textRecognitionInVideosEnabled);
    void setThirdPartyIframeRedirectBlockingEnabled(bool thirdPartyIframeRedirectBlockingEnabled);
    void setThreadedAnimationResolutionEnabled(bool threadedAnimationResolutionEnabled);
    void setTouchEventEmulationEnabled(bool touchEventEmulationEnabled);
    void setTouchEventsEnabled(bool touchEventsEnabled);
    void setTrackConfigurationEnabled(bool trackConfigurationEnabled);
    void setTransformStreamAPIEnabled(bool transformStreamAPIEnabled);
    void setTreatIPAddressAsDomain(bool treatIPAddressAsDomain);
    void setTreatsAnyTextCSSLinkAsStylesheet(bool treatsAnyTextCSSLinkAsStylesheet);
    void setUndoManagerAPIEnabled(bool undoManagerAPIEnabled);
    void setUnhandledPromiseRejectionToConsoleEnabled(bool unhandledPromiseRejectionToConsoleEnabled);
    void setUnifiedTextCheckerEnabled(bool unifiedTextCheckerEnabled);
    void setUnprefixedFullscreenAPIEnabled(bool unprefixedFullscreenAPIEnabled);
    void setUseAnonymousModeWhenFetchingMaskImages(bool useAnonymousModeWhenFetchingMaskImages);
    void setUseGPUProcessForWebGLEnabled(bool useGPUProcessForWebGLEnabled);
    void setUseGiantTiles(bool useGiantTiles);
    void setUseImageDocumentForSubframePDF(bool useImageDocumentForSubframePDF);
    void setUseLegacyBackgroundSizeShorthandBehavior(bool useLegacyBackgroundSizeShorthandBehavior);
    void setUsePreHTML5ParserQuirks(bool usePreHTML5ParserQuirks);
    void setUseSCContentSharingPicker(bool useSCContentSharingPicker);
    void setUserActivationAPIEnabled(bool userActivationAPIEnabled);
    void setUserGesturePromisePropagationEnabled(bool userGesturePromisePropagationEnabled);
    void setUsesEncodingDetector(bool usesEncodingDetector);
    void setValidationMessageTimerMagnification(uint32_t validationMessageTimerMagnification);
    void setVerifyWindowOpenUserGestureFromUIProcess(bool verifyWindowOpenUserGestureFromUIProcess);
    void setVerticalFormControlsEnabled(bool verticalFormControlsEnabled);
    void setVideoFullscreenRequiresElementFullscreen(bool videoFullscreenRequiresElementFullscreen);
    void setVideoPresentationModeAPIEnabled(bool videoPresentationModeAPIEnabled);
    void setVideoQualityIncludesDisplayCompositingEnabled(bool videoQualityIncludesDisplayCompositingEnabled);
    void setVisibleDebugOverlayRegions(uint32_t visibleDebugOverlayRegions);
    void setVisualTranslationEnabled(bool visualTranslationEnabled);
    void setVisualViewportAPIEnabled(bool visualViewportAPIEnabled);
    void setVisualViewportEnabled(bool visualViewportEnabled);
    void setVP9DecoderEnabled(bool vp9DecoderEnabled);
    void setWantsBalancedSetDefersLoadingBehavior(bool wantsBalancedSetDefersLoadingBehavior);
    void setWebAPIStatisticsEnabled(bool webAPIStatisticsEnabled);
    void setWebAPIsInShadowRealmEnabled(bool webAPIsInShadowRealmEnabled);
    void setWebAnimationsCompositeOperationsEnabled(bool webAnimationsCompositeOperationsEnabled);
    void setWebAnimationsCustomEffectsEnabled(bool webAnimationsCustomEffectsEnabled);
    void setWebAnimationsCustomFrameRateEnabled(bool webAnimationsCustomFrameRateEnabled);
    void setWebAnimationsIterationCompositeEnabled(bool webAnimationsIterationCompositeEnabled);
    void setWebAnimationsMutableTimelinesEnabled(bool webAnimationsMutableTimelinesEnabled);
    void setWebArchiveDebugModeEnabled(bool webArchiveDebugModeEnabled);
    void setWebArchiveTestingModeEnabled(bool webArchiveTestingModeEnabled);
    void setWebAssemblyESMIntegrationEnabled(bool webAssemblyESMIntegrationEnabled);
    void setWebAudioEnabled(bool webAudioEnabled);
    void setWebAuthenticationEnabled(bool webAuthenticationEnabled);
    void setWebCodecsAV1Enabled(bool webCodecsAV1Enabled);
    void setWebCodecsEnabled(bool webCodecsEnabled);
    void setWebCodecsHEVCEnabled(bool webCodecsHEVCEnabled);
    void setWebCryptoSafeCurvesEnabled(bool webCryptoSafeCurvesEnabled);
    void setWebGLDraftExtensionsEnabled(bool webGLDraftExtensionsEnabled);
    void setWebGLEnabled(bool webGLEnabled);
    void setWebGLErrorsToConsoleEnabled(bool webGLErrorsToConsoleEnabled);
    void setWebGLTimerQueriesEnabled(bool webGLTimerQueriesEnabled);
    void setWebGLUsingMetal(bool webGLUsingMetal);
    void setWebGPUEnabled(bool webGPUEnabled);
    void setWebInspectorEngineeringSettingsAllowed(bool webInspectorEngineeringSettingsAllowed);
    void setWebLocksAPIEnabled(bool webLocksAPIEnabled);
    void setWebRTCAV1CodecEnabled(bool webRTCAV1CodecEnabled);
    void setWebRTCDTMFEnabled(bool webRTCDTMFEnabled);
    void setWebRTCEncodedTransformEnabled(bool webRTCEncodedTransformEnabled);
    void setWebRTCEncryptionEnabled(bool webRTCEncryptionEnabled);
    void setWebRTCH265CodecEnabled(bool webRTCH265CodecEnabled);
    void setWebRTCMediaPipelineAdditionalLoggingEnabled(bool webRTCMediaPipelineAdditionalLoggingEnabled);
    void setWebRTCPlatformCodecsInGPUProcessEnabled(bool webRTCPlatformCodecsInGPUProcessEnabled);
    void setWebRTCRemoteVideoFrameEnabled(bool webRTCRemoteVideoFrameEnabled);
    void setWebRTCSFrameTransformEnabled(bool webRTCSFrameTransformEnabled);
    void setWebRTCSocketsProxyingEnabled(bool webRTCSocketsProxyingEnabled);
    void setWebRTCVP9Profile0CodecEnabled(bool webRTCVP9Profile0CodecEnabled);
    void setWebRTCVP9Profile2CodecEnabled(bool webRTCVP9Profile2CodecEnabled);
    void setWebSecurityEnabled(bool webSecurityEnabled);
    void setWebShareEnabled(bool webShareEnabled);
    void setWebShareFileAPIEnabled(bool webShareFileAPIEnabled);
    void setWebSocketEnabled(bool webSocketEnabled);
    void setWebXRAugmentedRealityModuleEnabled(bool webXRAugmentedRealityModuleEnabled);
    void setWebXREnabled(bool webXREnabled);
    void setWebXRGamepadsModuleEnabled(bool webXRGamepadsModuleEnabled);
    void setWebXRHandInputModuleEnabled(bool webXRHandInputModuleEnabled);
    void setWebkitImageReadyEventEnabled(bool webkitImageReadyEventEnabled);
    void setWheelEventGesturesBecomeNonBlocking(bool wheelEventGesturesBecomeNonBlocking);
    void setWindowFocusRestricted(bool windowFocusRestricted);
    void setWirelessPlaybackTargetAPIEnabled(bool wirelessPlaybackTargetAPIEnabled);
    void setYouTubeFlashPluginReplacementEnabled(bool youTubeFlashPluginReplacementEnabled);

private:
    WeakPtr<Page> m_page;

    bool m_CSSOMViewScrollingAPIEnabled;
    bool m_CSSOMViewSmoothScrollingEnabled;
    bool m_abortSignalAnyOperationEnabled;
    bool m_acceleratedCompositedAnimationsEnabled;
    bool m_acceleratedCompositingEnabled;
    bool m_acceleratedCompositingForFixedPositionEnabled;
    bool m_acceleratedDrawingEnabled;
#if USE(CORE_IMAGE)
    bool m_acceleratedFiltersEnabled;
#endif
    bool m_accentColorEnabled;
    bool m_accessHandleEnabled;
    bool m_aggressiveTileRetentionEnabled;
    bool m_allowAnimationControlsOverride;
    bool m_allowContentSecurityPolicySourceStarToMatchAnyProtocol;
    bool m_allowCrossOriginSubresourcesToAskForCredentials;
    bool m_allowDisplayOfInsecureContent;
    bool m_allowFileAccessFromFileURLs;
    bool m_allowMediaContentTypesRequiringHardwareSupportAsFallback;
    bool m_allowMultiElementImplicitSubmission;
    bool m_allowRunningOfInsecureContent;
    bool m_allowSettingAnyXHRHeaderFromFileURLs;
    bool m_allowTopNavigationToDataURLs;
    bool m_allowUniversalAccessFromFileURLs;
#if PLATFORM(IOS_FAMILY)
    bool m_allowViewportShrinkToFitContent;
#endif
#if ENABLE(WEBGL)
    bool m_allowWebGLInWorkers;
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    bool m_allowsAirPlayForMediaPlayback;
#endif
    bool m_allowsInlineMediaPlayback;
    bool m_allowsInlineMediaPlaybackAfterFullscreen;
    bool m_allowsPictureInPictureMediaPlayback;
#if PLATFORM(IOS_FAMILY)
    bool m_alternateFormControlDesignEnabled;
#endif
#if PLATFORM(IOS_FAMILY)
    bool m_alternateFullScreenControlDesignEnabled;
#endif
#if ENABLE(ALTERNATE_WEBM_PLAYER)
    bool m_alternateWebMPlayerEnabled;
#endif
    bool m_animatedImageAsyncDecodingEnabled;
    bool m_animatedImageDebugCanvasDrawingEnabled;
#if ENABLE(BADGING)
    bool m_appBadgeEnabled;
#endif
#if ENABLE(APP_HIGHLIGHTS)
    bool m_appHighlightsEnabled;
#endif
    bool m_appleMailPaginationQuirkEnabled;
#if ENABLE(APPLE_PAY)
    bool m_applePayCapabilityDisclosureAllowed;
#endif
#if ENABLE(APPLE_PAY)
    bool m_applePayEnabled;
#endif
    bool m_ariaReflectionForElementReferencesEnabled;
    bool m_aspectRatioEnabled;
    bool m_aspectRatioOfImgFromWidthAndHeightEnabled;
    bool m_asyncClipboardAPIEnabled;
    bool m_asyncFrameScrollingEnabled;
    bool m_asyncOverflowScrollingEnabled;
    bool m_asynchronousSpellCheckingEnabled;
#if ENABLE(ATTACHMENT_ELEMENT)
    bool m_attachmentWideLayoutEnabled;
#endif
    bool m_audioControlsScaleWithPageZoom;
#if ENABLE(VIDEO)
    bool m_audioDescriptionsEnabled;
#endif
    bool m_authorAndUserStylesEnabled;
    bool m_autoscrollForDragAndDropEnabled;
#if ENABLE(SERVICE_WORKER)
    bool m_backgroundFetchAPIEnabled;
#endif
    bool m_backgroundShouldExtendBeyondPage;
#if PLATFORM(MAC) && USE(RUNNINGBOARD)
    bool m_backgroundWebContentRunningBoardThrottlingEnabled;
#endif
    bool m_backspaceKeyNavigationEnabled;
    bool m_beaconAPIEnabled;
#if ENABLE(GPU_PROCESS)
    bool m_blockMediaLayerRehostingInWebContentProcess;
#endif
    bool m_broadcastChannelEnabled;
    bool m_broadcastChannelOriginPartitioningEnabled;
    bool m_cacheAPIEnabled;
    bool m_canvasColorSpaceEnabled;
    bool m_canvasFiltersEnabled;
    bool m_canvasFingerprintingQuirkEnabled;
    bool m_canvasUsesAcceleratedDrawing;
    bool m_caretBrowsingEnabled;
    bool m_clearSiteDataHTTPHeaderEnabled;
#if ENABLE(BADGING)
    bool m_clientBadgeEnabled;
#endif
    bool m_clientCoordinatesRelativeToLayoutViewport;
    bool m_colorFilterEnabled;
    bool m_compressionStreamEnabled;
    bool m_constantPropertiesEnabled;
    bool m_constructableStylesheetsEnabled;
    bool m_contactPickerAPIEnabled;
#if ENABLE(CONTENT_CHANGE_OBSERVER)
    bool m_contentChangeObserverEnabled;
#endif
    bool m_contentDispositionAttachmentSandboxEnabled;
#if ENABLE(CONTEXT_MENU_QR_CODE_DETECTION)
    bool m_contextMenuQRCodeDetectionEnabled;
#endif
    bool m_cookieConsentAPIEnabled;
    bool m_cookieEnabled;
    bool m_cookieStoreAPIEnabled;
    bool m_cookieStoreAPIExtendedAttributesEnabled;
    bool m_coreMathMLEnabled;
    bool m_crossOriginCheckInGetMatchedCSSRulesDisabled;
    bool m_crossOriginEmbedderPolicyEnabled;
    bool m_crossOriginOpenerPolicyEnabled;
    bool m_css3DTransformInteroperabilityEnabled;
    bool m_cssCascadeLayersEnabled;
    bool m_cssColor4;
    bool m_cssColorContrastEnabled;
    bool m_cssColorMixEnabled;
    bool m_cssContainIntrinsicSizeEnabled;
    bool m_cssContainerQueriesEnabled;
    bool m_cssContainmentEnabled;
    bool m_cssContentVisibilityEnabled;
    bool m_cssCounterStyleAtRuleImageSymbolsEnabled;
    bool m_cssCounterStyleAtRulesEnabled;
    bool m_cssCustomPropertiesAndValuesEnabled;
    bool m_cssFontFaceSizeAdjustEnabled;
    bool m_cssGradientInterpolationColorSpacesEnabled;
    bool m_cssGradientPremultipliedAlphaInterpolationEnabled;
    bool m_cssIndividualTransformPropertiesEnabled;
    bool m_cssInputSecurityEnabled;
    bool m_cssMarginTrimEnabled;
    bool m_cssMotionPathEnabled;
    bool m_cssNestingEnabled;
#if ENABLE(CSS_PAINTING_API)
    bool m_cssPaintingAPIEnabled;
#endif
    bool m_cssRelativeColorSyntaxEnabled;
    bool m_cssRhythmicSizingEnabled;
    bool m_cssScrollAnchoringEnabled;
    bool m_cssScrollbarColorEnabled;
    bool m_cssScrollbarGutterEnabled;
    bool m_cssScrollbarWidthEnabled;
    bool m_cssTextAlignLastEnabled;
    bool m_cssTextBoxTrimEnabled;
    bool m_cssTextGroupAlignEnabled;
    bool m_cssTextJustifyEnabled;
    bool m_cssTextSpacingEnabled;
    bool m_cssTextUnderlinePositionLeftRightEnabled;
    bool m_cssTextWrapNewValuesEnabled;
#if ENABLE(CSS_TRANSFORM_STYLE_OPTIMIZED_3D)
    bool m_cssTransformStyleOptimized3DEnabled;
#endif
    bool m_cssTypedOMColorEnabled;
    bool m_cssTypedOMEnabled;
    bool m_cssWhiteSpaceLonghandsEnabled;
    bool m_cssWordBreakAutoEnabled;
    String m_cursiveFontFamily;
#if ENABLE(DATALIST_ELEMENT)
    bool m_dataListElementEnabled;
#endif
    bool m_dataTransferItemsEnabled;
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    bool m_dateTimeInputsEditableComponentsEnabled;
#endif
    bool m_declarativeShadowDOMEnabled;
    bool m_declarativeShadowDOMInDOMParserEnabled;
    bool m_defaultARIAForCustomElementsEnabled;
    double m_defaultFixedFontSize;
    double m_defaultFontSize;
    String m_defaultTextEncodingName;
    String m_defaultVideoPosterURL;
    bool m_deprecateRSAESPKCSWebCryptoEnabled;
    bool m_deprecationReportingEnabled;
    bool m_developerExtrasEnabled;
    uint32_t m_deviceHeight;
#if ENABLE(DEVICE_ORIENTATION)
    bool m_deviceOrientationEventEnabled;
#endif
#if ENABLE(DEVICE_ORIENTATION)
    bool m_deviceOrientationPermissionAPIEnabled;
#endif
    uint32_t m_deviceWidth;
    bool m_diagnosticLoggingEnabled;
    bool m_dialogElementEnabled;
    bool m_dirPseudoEnabled;
    bool m_directoryUploadEnabled;
    bool m_disabledAdaptationsMetaTagEnabled;
    bool m_disallowSyncXHRDuringPageDismissalEnabled;
    bool m_displayListDrawingEnabled;
    bool m_dnsPrefetchingEnabled;
#if ENABLE(DOM_AUDIO_SESSION)
    bool m_domAudioSessionEnabled;
#endif
#if ENABLE(DOM_AUDIO_SESSION)
    bool m_domAudioSessionFullEnabled;
#endif
    bool m_domPasteAccessRequestsEnabled;
    bool m_domPasteAllowed;
    bool m_domTestingAPIsEnabled;
    bool m_domTimersThrottlingEnabled;
#if ENABLE(DOWNLOAD_ATTRIBUTE)
    bool m_downloadAttributeEnabled;
#endif
    bool m_embedElementEnabled;
    bool m_enableInheritURIQueryComponent;
#if ENABLE(ENCRYPTED_MEDIA)
    bool m_encryptedMediaAPIEnabled;
#endif
    bool m_enterKeyHintEnabled;
    bool m_eventHandlerDrivenSmoothKeyboardScrollingEnabled;
#if ENABLE(MEDIA_STREAM)
    bool m_exposeSpeakersEnabled;
#endif
#if ENABLE(VIDEO)
    bool m_extendedAudioDescriptionsEnabled;
#endif
    String m_fantasyFontFamily;
    bool m_fetchAPIEnabled;
    bool m_fetchMetadataEnabled;
    bool m_fetchPriorityEnabled;
    bool m_fileReaderAPIEnabled;
    bool m_fileSystemAccessEnabled;
    bool m_fixedBackgroundsPaintRelativeToDocument;
    bool m_fixedElementsLayoutRelativeToFrame;
    String m_fixedFontFamily;
    bool m_flexFormattingContextIntegrationEnabled;
    bool m_focusVisibleEnabled;
    bool m_fontFallbackPrefersPictographs;
    bool m_forceCompositingMode;
    bool m_forceFTPDirectoryListings;
    bool m_forceWebGLUsesLowPower;
    bool m_formAssociatedCustomElementsEnabled;
    String m_ftpDirectoryTemplatePath;
    bool m_ftpEnabled;
#if ENABLE(FULLSCREEN_API)
    bool m_fullScreenEnabled;
#endif
    bool m_fullscreenRequirementForScreenOrientationLockingEnabled;
#if PLATFORM(VISION)
    bool m_fullscreenSceneAspectRatioLockingEnabled;
#endif
#if PLATFORM(VISION)
    bool m_fullscreenSceneDimmingEnabled;
#endif
#if ENABLE(GAMEPAD)
    bool m_gamepadTriggerRumbleEnabled;
#endif
#if ENABLE(GAMEPAD)
    bool m_gamepadVibrationActuatorEnabled;
#endif
#if ENABLE(GAMEPAD)
    bool m_gamepadsEnabled;
#endif
#if ENABLE(VIDEO)
    bool m_genericCueAPIEnabled;
#endif
    bool m_geolocationFloorLevelEnabled;
#if ENABLE(MEDIA_STREAM)
    bool m_getUserMediaRequiresFocus;
#endif
    bool m_googleAntiFlickerOptimizationQuirkEnabled;
#if USE(GRAPHICS_CONTEXT_FILTERS)
    bool m_graphicsContextFiltersEnabled;
#endif
    bool m_hasPseudoClassEnabled;
    bool m_hiddenPageCSSAnimationSuspensionEnabled;
    bool m_hiddenPageDOMTimerThrottlingAutoIncreases;
    bool m_hiddenPageDOMTimerThrottlingEnabled;
    bool m_httpEquivEnabled;
    bool m_hyperlinkAuditingEnabled;
#if ENABLE(IOS_FORM_CONTROL_REFRESH)
    bool m_iOSFormControlRefreshEnabled;
#endif
    bool m_iceCandidateFilteringEnabled;
#if ENABLE(TEXT_AUTOSIZING)
    bool m_idempotentModeAutosizingOnlyHonorsPercentages;
#endif
#if ENABLE(IMAGE_ANALYSIS)
    bool m_imageAnalysisDuringFindInPageEnabled;
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    bool m_imageAnimationControlEnabled;
#endif
#if ENABLE(SERVICE_CONTROLS)
    bool m_imageControlsEnabled;
#endif
    bool m_imageSubsamplingEnabled;
    bool m_imagesEnabled;
    bool m_imperativeSlotAPIEnabled;
    bool m_incompleteImageBorderEnabled;
#if HAVE(INCREMENTAL_PDF_APIS)
    bool m_incrementalPDFLoadingEnabled;
#endif
    double m_incrementalRenderingSuppressionTimeoutInSeconds;
    bool m_indexedDBAPIEnabled;
    bool m_inertAttributeEnabled;
    bool m_inlineMediaPlaybackRequiresPlaysInlineAttribute;
    bool m_inlinePredictionsInAllEditableElementsEnabled;
#if ENABLE(INPUT_TYPE_COLOR)
    bool m_inputTypeColorEnabled;
#endif
#if ENABLE(INPUT_TYPE_DATE)
    bool m_inputTypeDateEnabled;
#endif
#if ENABLE(INPUT_TYPE_DATETIMELOCAL)
    bool m_inputTypeDateTimeLocalEnabled;
#endif
#if ENABLE(INPUT_TYPE_MONTH)
    bool m_inputTypeMonthEnabled;
#endif
#if ENABLE(INPUT_TYPE_TIME)
    bool m_inputTypeTimeEnabled;
#endif
#if ENABLE(INPUT_TYPE_WEEK)
    bool m_inputTypeWeekEnabled;
#endif
    double m_interactionRegionInlinePadding;
    double m_interactionRegionMinimumCornerRadius;
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
    bool m_interactionRegionsEnabled;
#endif
    bool m_interactiveFormValidationEnabled;
#if ENABLE(MEDIA_STREAM)
    bool m_interruptAudioOnPageVisibilityChangeEnabled;
#endif
#if ENABLE(MEDIA_STREAM)
    bool m_interruptVideoOnPageVisibilityChangeEnabled;
#endif
    bool m_intersectionObserverEnabled;
    bool m_invisibleAutoplayNotPermitted;
    bool m_isFirstPartyWebsiteDataRemovalDisabled;
    bool m_isFirstPartyWebsiteDataRemovalLiveOnTestingEnabled;
    bool m_isFirstPartyWebsiteDataRemovalReproTestingEnabled;
    bool m_isLoggedInAPIEnabled;
    bool m_isPerActivityStateCPUUsageMeasurementEnabled;
    bool m_isPostBackgroundingCPUUsageMeasurementEnabled;
    bool m_isPostBackgroundingMemoryUsageMeasurementEnabled;
    bool m_isPostLoadCPUUsageMeasurementEnabled;
    bool m_isPostLoadMemoryUsageMeasurementEnabled;
    bool m_isSameSiteStrictEnforcementEnabled;
    bool m_isThirdPartyCookieBlockingDisabled;
    bool m_itpDebugModeEnabled;
    bool m_javaScriptCanAccessClipboard;
    bool m_javaScriptCanOpenWindowsAutomatically;
    bool m_langAttributeAwareFormControlUIEnabled;
    bool m_largeImageAsyncDecodingEnabled;
#if ENABLE(LAYER_BASED_SVG_ENGINE)
    bool m_layerBasedSVGEngineEnabled;
#endif
    uint32_t m_layoutFallbackWidth;
    bool m_layoutFormattingContextEnabled;
    double m_layoutViewportHeightExpansionFactor;
    bool m_lazyIframeLoadingEnabled;
    bool m_lazyImageLoadingEnabled;
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    bool m_legacyEncryptedMediaAPIEnabled;
#endif
    bool m_legacyLineLayoutVisualCoverageEnabled;
#if ENABLE(OVERFLOW_SCROLLING_TOUCH)
    bool m_legacyOverflowScrollingTouchEnabled;
#endif
    bool m_linkModulePreloadEnabled;
    bool m_linkPreconnectEarlyHintsEnabled;
    bool m_linkPreconnectEnabled;
    bool m_linkPrefetchEnabled;
    bool m_linkPreloadEnabled;
    bool m_linkPreloadResponsiveImagesEnabled;
    bool m_linkSanitizerEnabled;
    bool m_liveRangeSelectionEnabled;
    bool m_loadDeferringEnabled;
    bool m_loadsImagesAutomatically;
    bool m_localFileContentSniffingEnabled;
    String m_localStorageDatabasePath;
    bool m_localStorageEnabled;
    bool m_logsPageMessagesToSystemConsoleEnabled;
    bool m_mainContentUserGestureOverrideEnabled;
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
    bool m_manageCaptureStatusBarInGPUProcessEnabled;
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    bool m_managedMediaSourceEnabled;
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    double m_managedMediaSourceHighThreshold;
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    double m_managedMediaSourceLowThreshold;
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE) && ENABLE(WIRELESS_PLAYBACK_TARGET)
    bool m_managedMediaSourceNeedsAirPlay;
#endif
#if ENABLE(WEBGL)
    bool m_maskWebGLStringsEnabled;
#endif
    bool m_masonryEnabled;
    bool m_masonryTrackAlignmentEnabled;
#if ENABLE(MATHML)
    bool m_mathMLEnabled;
#endif
    double m_maxParseDuration;
    uint32_t m_maximumAccelerated2dCanvasSize;
    uint32_t m_maximumHTMLParserDOMTreeDepth;
#if ENABLE(MEDIA_SOURCE)
    uint32_t m_maximumSourceBufferSize;
#endif
    bool m_mediaCapabilitiesEnabled;
    bool m_mediaCapabilitiesExtensionsEnabled;
#if ENABLE(MEDIA_STREAM)
    bool m_mediaCaptureRequiresSecureConnection;
#endif
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS)
    bool m_mediaControlsContextMenusEnabled;
#endif
    bool m_mediaControlsScaleWithPageZoom;
    bool m_mediaDataLoadsAutomatically;
#if ENABLE(MEDIA_STREAM)
    bool m_mediaDevicesEnabled;
#endif
#if ENABLE(VIDEO)
    bool m_mediaEnabled;
#endif
    String m_mediaKeysStorageDirectory;
    double m_mediaPreferredFullscreenWidth;
    bool m_mediaPreloadingEnabled;
#if ENABLE(MEDIA_RECORDER)
    bool m_mediaRecorderEnabled;
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
    bool m_mediaSessionCoordinatorEnabled;
#endif
#if ENABLE(MEDIA_SESSION)
    bool m_mediaSessionEnabled;
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR) && ENABLE(MEDIA_SESSION_PLAYLIST)
    bool m_mediaSessionPlaylistEnabled;
#endif
    bool m_mediaSourceEnabled;
#if ENABLE(MEDIA_STREAM)
    bool m_mediaStreamEnabled;
#endif
    String m_mediaTypeOverride;
    bool m_mediaUserGestureInheritsFromDocument;
    bool m_menuItemElementEnabled;
    uint32_t m_minimumAccelerated2dCanvasSize;
    double m_minimumFontSize;
    double m_minimumLogicalFontSize;
#if ENABLE(TEXT_AUTOSIZING)
    double m_minimumZoomFontSize;
#endif
#if ENABLE(MEDIA_STREAM)
    bool m_mockCaptureDevicesEnabled;
#endif
    bool m_mockScrollbarsControllerEnabled;
#if ENABLE(MODEL_ELEMENT)
    bool m_modelElementEnabled;
#endif
    bool m_momentumScrollingAnimatorEnabled;
#if ENABLE(TOUCH_EVENTS)
    bool m_mouseEventsSimulationEnabled;
#endif
#if ENABLE(MEDIA_STREAM)
    bool m_muteCameraOnMicrophoneInterruptionEnabled;
#endif
    bool m_needsAdobeFrameReloadingQuirk;
    bool m_needsDeferKeyDownAndKeyPressTimersUntilNextEditingCommandQuirk;
    bool m_needsFrameNameFallbackToIdQuirk;
    bool m_needsKeyboardEventDisambiguationQuirks;
    bool m_needsSiteSpecificQuirks;
    bool m_needsStorageAccessFromFileURLsQuirk;
#if ENABLE(NOTIFICATION_EVENT)
    bool m_notificationEventEnabled;
#endif
#if ENABLE(NOTIFICATIONS)
    bool m_notificationsEnabled;
#endif
    bool m_offlineWebApplicationCacheEnabled;
#if ENABLE(OFFSCREEN_CANVAS)
    bool m_offscreenCanvasEnabled;
#endif
#if ENABLE(OFFSCREEN_CANVAS_IN_WORKERS)
    bool m_offscreenCanvasInWorkersEnabled;
#endif
    bool m_overflowClipEnabled;
    bool m_overscrollBehaviorEnabled;
    bool m_pageAtRuleSupportEnabled;
    bool m_passiveTouchListenersAsDefaultOnDocument;
    bool m_passiveWheelListenersAsDefaultOnDocument;
    double m_passwordEchoDurationInSeconds;
    bool m_passwordEchoEnabled;
#if ENABLE(PAYMENT_REQUEST)
    bool m_paymentRequestEnabled;
#endif
#if ENABLE(PDFJS)
    bool m_pdfJSViewerEnabled;
#endif
#if ENABLE(WEB_RTC)
    bool m_peerConnectionEnabled;
#endif
#if ENABLE(MEDIA_STREAM)
    bool m_perElementSpeakerSelectionEnabled;
#endif
    bool m_performanceNavigationTimingAPIEnabled;
    bool m_performanceResourceTimingSensitivePropertiesEnabled;
    bool m_permissionsAPIEnabled;
    String m_pictographFontFamily;
#if ENABLE(PICTURE_IN_PICTURE_API)
    bool m_pictureInPictureAPIEnabled;
#endif
    bool m_pluginsEnabled;
    bool m_popoverAttributeEnabled;
    bool m_preferMIMETypeForImages;
    bool m_preferPageRenderingUpdatesNear60FPSEnabled;
#if ENABLE(VIDEO)
    bool m_preferSandboxedMediaParsing;
#endif
    bool m_preventKeyboardDOMEventDispatch;
    bool m_privateClickMeasurementDebugModeEnabled;
    bool m_privateClickMeasurementEnabled;
    bool m_privateClickMeasurementFraudPreventionEnabled;
    bool m_punchOutWhiteBackgroundsInDarkMode;
#if ENABLE(SERVICE_WORKER)
    bool m_pushAPIEnabled;
#endif
    bool m_referrerPolicyAttributeEnabled;
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    bool m_remotePlaybackEnabled;
#endif
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    bool m_removeBackgroundEnabled;
#endif
    bool m_reportingEnabled;
    bool m_requestIdleCallbackEnabled;
    bool m_requestSubmitEnabled;
    bool m_requestVideoFrameCallbackEnabled;
#if HAVE(SC_CONTENT_SHARING_PICKER)
    bool m_requireUAGetDisplayMediaPrompt;
#endif
    bool m_requiresPageVisibilityToPlayAudio;
    bool m_requiresUserGestureForAudioPlayback;
    bool m_requiresUserGestureForVideoPlayback;
    bool m_requiresUserGestureToLoadVideo;
    bool m_resizeObserverEnabled;
    bool m_resourceLoadSchedulingEnabled;
#if ENABLE(RESOURCE_USAGE)
    bool m_resourceUsageOverlayVisible;
#endif
#if HAVE(RUBBER_BANDING)
    bool m_rubberBandingForSubScrollableRegionsEnabled;
#endif
    bool m_sKAttributionEnabled;
#if HAVE(AVCONTENTKEYSPECIFIER)
    bool m_sampleBufferContentKeySessionSupportEnabled;
#endif
    double m_sampledPageTopColorMaxDifference;
    double m_sampledPageTopColorMinHeight;
    String m_sansSerifFontFamily;
#if ENABLE(MEDIA_STREAM)
    bool m_screenCaptureEnabled;
#endif
    bool m_screenOrientationAPIEnabled;
    bool m_screenOrientationLockingAPIEnabled;
    bool m_screenWakeLockAPIEnabled;
    bool m_scriptEnabled;
    bool m_scriptMarkupEnabled;
    bool m_scrollAnimatorEnabled;
    bool m_scrollToTextFragmentEnabled;
    bool m_scrollToTextFragmentIndicatorEnabled;
    bool m_scrollingCoordinatorEnabled;
    bool m_scrollingPerformanceTestingEnabled;
    bool m_scrollingTreeIncludesFrames;
    bool m_searchInputIncrementalAttributeAndSearchEventEnabled;
    bool m_secureContextChecksEnabled;
    bool m_selectTrailingWhitespaceEnabled;
    bool m_selectionAPIForShadowDOMEnabled;
    bool m_sendMouseEventsToDisabledFormControlsEnabled;
    String m_serifFontFamily;
#if ENABLE(SERVICE_CONTROLS)
    bool m_serviceControlsEnabled;
#endif
#if ENABLE(SERVICE_WORKER)
    bool m_serviceWorkerNavigationPreloadEnabled;
#endif
#if ENABLE(SERVICE_WORKER)
    bool m_serviceWorkersEnabled;
#endif
#if ENABLE(SERVICE_WORKER)
    bool m_serviceWorkersUserGestureEnabled;
#endif
    uint32_t m_sessionStorageQuota;
    bool m_shapeDetection;
    bool m_sharedWorkerEnabled;
    bool m_shouldAllowUserInstalledFonts;
    bool m_shouldConvertInvalidURLsToBlank;
    bool m_shouldConvertPositionStyleOnCopy;
    bool m_shouldDecidePolicyBeforeLoadingQuickLookPreview;
    bool m_shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint;
    bool m_shouldDispatchSyntheticMouseEventsWhenModifyingSelection;
    bool m_shouldDispatchSyntheticMouseOutAfterSyntheticClick;
#if ENABLE(VIDEO)
    bool m_shouldDisplayCaptions;
#endif
#if ENABLE(VIDEO)
    bool m_shouldDisplaySubtitles;
#endif
#if ENABLE(VIDEO)
    bool m_shouldDisplayTextDescriptions;
#endif
    bool m_shouldDropNearSuspendedAssertionAfterDelay;
#if ENABLE(TEXT_AUTOSIZING)
    bool m_shouldEnableTextAutosizingBoost;
#endif
    bool m_shouldIgnoreFontLoadCompletions;
    bool m_shouldIgnoreMetaViewport;
    bool m_shouldInjectUserScriptsInInitialEmptyDocument;
    bool m_shouldPrintBackgrounds;
    bool m_shouldRespectImageOrientation;
    bool m_shouldRestrictBaseURLSchemes;
    bool m_shouldSuppressTextInputFromEditingDuringProvisionalNavigation;
    bool m_shouldTakeNearSuspendedAssertions;
    bool m_shouldUseServiceWorkerShortTimeout;
    bool m_showDebugBorders;
    bool m_showMediaStatsContextMenuItemEnabled;
    bool m_showModalDialogEnabled;
    bool m_showRepaintCounter;
    bool m_showTiledScrollingIndicator;
    bool m_showsToolTipOverTruncatedText;
    bool m_showsURLsInToolTips;
    bool m_shrinksStandaloneImagesToFit;
    bool m_siteIsolationEnabled;
    bool m_smartInsertDeleteEnabled;
#if ENABLE(MEDIA_SOURCE)
    bool m_sourceBufferChangeTypeEnabled;
#endif
    bool m_spatialNavigationEnabled;
#if ENABLE(MEDIA_STREAM)
    bool m_speakerSelectionRequiresUserGesture;
#endif
    bool m_speechRecognitionEnabled;
    bool m_speechSynthesisAPIEnabled;
    bool m_springTimingFunctionEnabled;
    bool m_standalone;
    String m_standardFontFamily;
    bool m_storageAPIEnabled;
    bool m_storageAPIEstimateEnabled;
    bool m_storageAccessAPIEnabled;
    bool m_storageAccessAPIPerPageScopeEnabled;
    bool m_subgridEnabled;
    bool m_suppressesIncrementalRendering;
    bool m_syntheticEditingCommandsEnabled;
#if USE(SYSTEM_PREVIEW)
    bool m_systemPreviewEnabled;
#endif
    bool m_telephoneNumberParsingEnabled;
    bool m_temporaryTileCohortRetentionEnabled;
    bool m_textAreasAreResizable;
#if ENABLE(TEXT_AUTOSIZING)
    bool m_textAutosizingEnabled;
#endif
#if ENABLE(TEXT_AUTOSIZING)
    bool m_textAutosizingUsesIdempotentMode;
#endif
#if ENABLE(TEXT_AUTOSIZING)
    uint32_t m_textAutosizingWindowSizeOverrideHeight;
#endif
#if ENABLE(TEXT_AUTOSIZING)
    uint32_t m_textAutosizingWindowSizeOverrideWidth;
#endif
    bool m_textInteractionEnabled;
#if ENABLE(IMAGE_ANALYSIS)
    bool m_textRecognitionInVideosEnabled;
#endif
    bool m_thirdPartyIframeRedirectBlockingEnabled;
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
    bool m_threadedAnimationResolutionEnabled;
#endif
#if ENABLE(TOUCH_EVENTS)
    bool m_touchEventEmulationEnabled;
#endif
#if ENABLE(TOUCH_EVENTS)
    bool m_touchEventsEnabled;
#endif
    bool m_trackConfigurationEnabled;
    bool m_transformStreamAPIEnabled;
    bool m_treatIPAddressAsDomain;
    bool m_treatsAnyTextCSSLinkAsStylesheet;
    bool m_undoManagerAPIEnabled;
    bool m_unhandledPromiseRejectionToConsoleEnabled;
    bool m_unifiedTextCheckerEnabled;
    bool m_unprefixedFullscreenAPIEnabled;
    bool m_useAnonymousModeWhenFetchingMaskImages;
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
    bool m_useGPUProcessForWebGLEnabled;
#endif
    bool m_useGiantTiles;
    bool m_useImageDocumentForSubframePDF;
    bool m_useLegacyBackgroundSizeShorthandBehavior;
    bool m_usePreHTML5ParserQuirks;
#if HAVE(SC_CONTENT_SHARING_PICKER)
    bool m_useSCContentSharingPicker;
#endif
    bool m_userActivationAPIEnabled;
    bool m_userGesturePromisePropagationEnabled;
    bool m_usesEncodingDetector;
    uint32_t m_validationMessageTimerMagnification;
    bool m_verifyWindowOpenUserGestureFromUIProcess;
    bool m_verticalFormControlsEnabled;
#if PLATFORM(IOS_FAMILY)
    bool m_videoFullscreenRequiresElementFullscreen;
#endif
    bool m_videoPresentationModeAPIEnabled;
#if ENABLE(VIDEO)
    bool m_videoQualityIncludesDisplayCompositingEnabled;
#endif
    uint32_t m_visibleDebugOverlayRegions;
#if ENABLE(IMAGE_ANALYSIS)
    bool m_visualTranslationEnabled;
#endif
    bool m_visualViewportAPIEnabled;
    bool m_visualViewportEnabled;
#if ENABLE(VP9)
    bool m_vp9DecoderEnabled;
#endif
    bool m_wantsBalancedSetDefersLoadingBehavior;
    bool m_webAPIStatisticsEnabled;
    bool m_webAPIsInShadowRealmEnabled;
    bool m_webAnimationsCompositeOperationsEnabled;
    bool m_webAnimationsCustomEffectsEnabled;
    bool m_webAnimationsCustomFrameRateEnabled;
    bool m_webAnimationsIterationCompositeEnabled;
    bool m_webAnimationsMutableTimelinesEnabled;
#if ENABLE(WEB_ARCHIVE)
    bool m_webArchiveDebugModeEnabled;
#endif
#if ENABLE(WEB_ARCHIVE)
    bool m_webArchiveTestingModeEnabled;
#endif
#if ENABLE(WEBASSEMBLY)
    bool m_webAssemblyESMIntegrationEnabled;
#endif
#if ENABLE(WEB_AUDIO)
    bool m_webAudioEnabled;
#endif
#if ENABLE(WEB_AUTHN)
    bool m_webAuthenticationEnabled;
#endif
#if ENABLE(WEB_CODECS)
    bool m_webCodecsAV1Enabled;
#endif
#if ENABLE(WEB_CODECS)
    bool m_webCodecsEnabled;
#endif
#if ENABLE(WEB_CODECS)
    bool m_webCodecsHEVCEnabled;
#endif
    bool m_webCryptoSafeCurvesEnabled;
    bool m_webGLDraftExtensionsEnabled;
    bool m_webGLEnabled;
    bool m_webGLErrorsToConsoleEnabled;
    bool m_webGLTimerQueriesEnabled;
#if ENABLE(WEBGL) && PLATFORM(COCOA)
    bool m_webGLUsingMetal;
#endif
    bool m_webGPUEnabled;
    bool m_webInspectorEngineeringSettingsAllowed;
    bool m_webLocksAPIEnabled;
#if ENABLE(WEB_RTC)
    bool m_webRTCAV1CodecEnabled;
#endif
#if ENABLE(WEB_RTC)
    bool m_webRTCDTMFEnabled;
#endif
#if ENABLE(WEB_RTC)
    bool m_webRTCEncodedTransformEnabled;
#endif
    bool m_webRTCEncryptionEnabled;
#if ENABLE(WEB_RTC)
    bool m_webRTCH265CodecEnabled;
#endif
#if USE(LIBWEBRTC)
    bool m_webRTCMediaPipelineAdditionalLoggingEnabled;
#endif
#if ENABLE(WEB_RTC)
    bool m_webRTCPlatformCodecsInGPUProcessEnabled;
#endif
#if ENABLE(WEB_RTC)
    bool m_webRTCRemoteVideoFrameEnabled;
#endif
#if ENABLE(WEB_RTC)
    bool m_webRTCSFrameTransformEnabled;
#endif
#if ENABLE(WEB_RTC)
    bool m_webRTCSocketsProxyingEnabled;
#endif
#if ENABLE(WEB_RTC)
    bool m_webRTCVP9Profile0CodecEnabled;
#endif
#if ENABLE(WEB_RTC)
    bool m_webRTCVP9Profile2CodecEnabled;
#endif
    bool m_webSecurityEnabled;
    bool m_webShareEnabled;
    bool m_webShareFileAPIEnabled;
    bool m_webSocketEnabled;
#if ENABLE(WEBXR)
    bool m_webXRAugmentedRealityModuleEnabled;
#endif
#if ENABLE(WEBXR)
    bool m_webXREnabled;
#endif
#if ENABLE(WEBXR)
    bool m_webXRGamepadsModuleEnabled;
#endif
#if ENABLE(WEBXR_HANDS)
    bool m_webXRHandInputModuleEnabled;
#endif
    bool m_webkitImageReadyEventEnabled;
    bool m_wheelEventGesturesBecomeNonBlocking;
    bool m_windowFocusRestricted;
    bool m_wirelessPlaybackTargetAPIEnabled;
    bool m_youTubeFlashPluginReplacementEnabled;
};

} // namespace WebCore
