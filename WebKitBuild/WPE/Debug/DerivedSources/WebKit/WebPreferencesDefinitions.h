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

#pragma once

#include "WebPreferencesDefaultValues.h"

#define DEFAULT_VALUE_FOR_AcceleratedCompositingEnabled true
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_AcceleratedCompositingForFixedPositionEnabled true
#else
#define DEFAULT_VALUE_FOR_AcceleratedCompositingForFixedPositionEnabled false
#endif
#define DEFAULT_VALUE_FOR_AggressiveTileRetentionEnabled false
#define DEFAULT_VALUE_FOR_AllowContentSecurityPolicySourceStarToMatchAnyProtocol false
#define DEFAULT_VALUE_FOR_AllowCrossOriginSubresourcesToAskForCredentials false
#define DEFAULT_VALUE_FOR_AllowDisplayOfInsecureContent false
#define DEFAULT_VALUE_FOR_AllowFileAccessFromFileURLs false
#define DEFAULT_VALUE_FOR_AllowMultiElementImplicitSubmission false
#define DEFAULT_VALUE_FOR_AllowRunningOfInsecureContent false
#define DEFAULT_VALUE_FOR_AllowSettingAnyXHRHeaderFromFileURLs false
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
#define DEFAULT_VALUE_FOR_AllowsAirPlayForMediaPlayback true
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_AllowsInlineMediaPlayback false
#else
#define DEFAULT_VALUE_FOR_AllowsInlineMediaPlayback true
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_AllowsInlineMediaPlaybackAfterFullscreen true
#else
#define DEFAULT_VALUE_FOR_AllowsInlineMediaPlaybackAfterFullscreen false
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_AllowsPictureInPictureMediaPlayback true
#else
#define DEFAULT_VALUE_FOR_AllowsPictureInPictureMediaPlayback false
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_AlternateFormControlDesignEnabled false
#endif
#if PLATFORM(IOS_FAMILY)
#if PLATFORM(VISION)
#define DEFAULT_VALUE_FOR_AlternateFullScreenControlDesignEnabled true
#else
#define DEFAULT_VALUE_FOR_AlternateFullScreenControlDesignEnabled false
#endif
#endif
#define DEFAULT_VALUE_FOR_AnimatedImageAsyncDecodingEnabled true
#if PLATFORM(MAC)
#define DEFAULT_VALUE_FOR_AppleMailPaginationQuirkEnabled WebKit::defaultAppleMailPaginationQuirkEnabled()
#else
#define DEFAULT_VALUE_FOR_AppleMailPaginationQuirkEnabled false
#endif
#if ENABLE(APPLE_PAY)
#define DEFAULT_VALUE_FOR_ApplePayCapabilityDisclosureAllowed true
#endif
#if ENABLE(APPLE_PAY)
#if ENABLE(APPLE_PAY_REMOTE_UI)
#define DEFAULT_VALUE_FOR_ApplePayEnabled true
#else
#define DEFAULT_VALUE_FOR_ApplePayEnabled false
#endif
#endif
#define DEFAULT_VALUE_FOR_AsynchronousSpellCheckingEnabled false
#if PLATFORM(VISION)
#define DEFAULT_VALUE_FOR_AudioControlsScaleWithPageZoom true
#elif PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_AudioControlsScaleWithPageZoom false
#else
#define DEFAULT_VALUE_FOR_AudioControlsScaleWithPageZoom true
#endif
#define DEFAULT_VALUE_FOR_AuthorAndUserStylesEnabled true
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_BackspaceKeyNavigationEnabled false
#else
#define DEFAULT_VALUE_FOR_BackspaceKeyNavigationEnabled true
#endif
#define DEFAULT_VALUE_FOR_CaretBrowsingEnabled false
#define DEFAULT_VALUE_FOR_ColorFilterEnabled false
#define DEFAULT_VALUE_FOR_ConstantPropertiesEnabled true
#if ENABLE(CONTENT_CHANGE_OBSERVER)
#define DEFAULT_VALUE_FOR_ContentChangeObserverEnabled true
#endif
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_ContentDispositionAttachmentSandboxEnabled true
#else
#define DEFAULT_VALUE_FOR_ContentDispositionAttachmentSandboxEnabled false
#endif
#if ENABLE(CONTEXT_MENU_QR_CODE_DETECTION)
#define DEFAULT_VALUE_FOR_ContextMenuQRCodeDetectionEnabled false
#endif
#if PLATFORM(COCOA) && PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_CursiveFontFamily "Snell Roundhand"
#elif PLATFORM(COCOA) && !PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_CursiveFontFamily "Apple Chancery"
#else
#define DEFAULT_VALUE_FOR_CursiveFontFamily "Comic Sans MS"
#endif
#define DEFAULT_VALUE_FOR_DNSPrefetchingEnabled false
#define DEFAULT_VALUE_FOR_DOMPasteAllowed false
#if ENABLE(DATA_DETECTION)
#define DEFAULT_VALUE_FOR_DataDetectorTypes static_cast<DataDetectorType>(0)
#endif
#define DEFAULT_VALUE_FOR_DatabasesEnabled true
#define DEFAULT_VALUE_FOR_DefaultFixedFontSize 13
#define DEFAULT_VALUE_FOR_DefaultFontSize 16
#define DEFAULT_VALUE_FOR_DefaultTextEncodingName PAL::defaultTextEncodingNameForSystemLanguage()
#define DEFAULT_VALUE_FOR_DeveloperExtrasEnabled false
#define DEFAULT_VALUE_FOR_DeviceHeight 0
#if ENABLE(DEVICE_ORIENTATION)
#define DEFAULT_VALUE_FOR_DeviceOrientationEventEnabled true
#endif
#if ENABLE(DEVICE_ORIENTATION)
#define DEFAULT_VALUE_FOR_DeviceOrientationPermissionAPIEnabled false
#endif
#define DEFAULT_VALUE_FOR_DeviceWidth 0
#if PLATFORM(WATCHOS)
#define DEFAULT_VALUE_FOR_DisabledAdaptationsMetaTagEnabled true
#else
#define DEFAULT_VALUE_FOR_DisabledAdaptationsMetaTagEnabled false
#endif
#if ENABLE(DOWNLOAD_ATTRIBUTE)
#define DEFAULT_VALUE_FOR_DownloadAttributeEnabled true
#endif
#define DEFAULT_VALUE_FOR_EditableLinkBehavior WebCore::EditableLinkBehavior::NeverLive
#define DEFAULT_VALUE_FOR_EnableInheritURIQueryComponent false
#if ENABLE(ENCRYPTED_MEDIA)
#define DEFAULT_VALUE_FOR_EncryptedMediaAPIEnabled true
#endif
#if HAVE(APP_SSO)
#define DEFAULT_VALUE_FOR_ExtensibleSSOEnabled true
#endif
#define DEFAULT_VALUE_FOR_FTPDirectoryTemplatePath ""
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_FantasyFontFamily "Papyrus"
#else
#define DEFAULT_VALUE_FOR_FantasyFontFamily "Impact"
#endif
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_FixedFontFamily "Courier"
#else
#define DEFAULT_VALUE_FOR_FixedFontFamily "Courier New"
#endif
#define DEFAULT_VALUE_FOR_ForceCompositingMode false
#define DEFAULT_VALUE_FOR_ForceFTPDirectoryListings false
#define DEFAULT_VALUE_FOR_ForceWebGLUsesLowPower false
#if USE(GSTREAMER)
#define DEFAULT_VALUE_FOR_GStreamerEnabled true
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK)
#define DEFAULT_VALUE_FOR_HiddenPageCSSAnimationSuspensionEnabled true
#else
#define DEFAULT_VALUE_FOR_HiddenPageCSSAnimationSuspensionEnabled false
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_InactiveMediaCaptureSteamRepromptIntervalInMinutes 1
#else
#define DEFAULT_VALUE_FOR_InactiveMediaCaptureSteamRepromptIntervalInMinutes 10
#endif
#define DEFAULT_VALUE_FOR_IncompleteImageBorderEnabled false
#if HAVE(INCREMENTAL_PDF_APIS)
#if PLATFORM(MAC)
#define DEFAULT_VALUE_FOR_IncrementalPDFLoadingEnabled true
#else
#define DEFAULT_VALUE_FOR_IncrementalPDFLoadingEnabled false
#endif
#endif
#define DEFAULT_VALUE_FOR_IncrementalRenderingSuppressionTimeout 5
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_InlineMediaPlaybackRequiresPlaysInlineAttribute true
#else
#define DEFAULT_VALUE_FOR_InlineMediaPlaybackRequiresPlaysInlineAttribute false
#endif
#define DEFAULT_VALUE_FOR_InspectorAttachedHeight 500
#define DEFAULT_VALUE_FOR_InspectorAttachedWidth 750
#define DEFAULT_VALUE_FOR_InspectorAttachmentSide 0
#define DEFAULT_VALUE_FOR_InspectorStartsAttached true
#define DEFAULT_VALUE_FOR_InspectorWindowFrame ""
#define DEFAULT_VALUE_FOR_InteractionRegionInlinePadding 4
#define DEFAULT_VALUE_FOR_InteractionRegionMinimumCornerRadius 8
#if ENABLE(MEDIA_STREAM)
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_InterruptAudioOnPageVisibilityChangeEnabled true
#else
#define DEFAULT_VALUE_FOR_InterruptAudioOnPageVisibilityChangeEnabled false
#endif
#endif
#if ENABLE(MEDIA_STREAM)
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_InterruptVideoOnPageVisibilityChangeEnabled true
#else
#define DEFAULT_VALUE_FOR_InterruptVideoOnPageVisibilityChangeEnabled false
#endif
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_InvisibleAutoplayNotPermitted true
#else
#define DEFAULT_VALUE_FOR_InvisibleAutoplayNotPermitted false
#endif
#define DEFAULT_VALUE_FOR_JavaScriptCanAccessClipboard false
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_JavaScriptCanOpenWindowsAutomatically false
#else
#define DEFAULT_VALUE_FOR_JavaScriptCanOpenWindowsAutomatically true
#endif
#define DEFAULT_VALUE_FOR_JavaScriptMarkupEnabled true
#define DEFAULT_VALUE_FOR_JavaScriptRuntimeFlags 0
#define DEFAULT_VALUE_FOR_LargeImageAsyncDecodingEnabled true
#define DEFAULT_VALUE_FOR_LayoutFallbackWidth 980
#if PLATFORM(WATCHOS)
#define DEFAULT_VALUE_FOR_LayoutViewportHeightExpansionFactor 1
#else
#define DEFAULT_VALUE_FOR_LayoutViewportHeightExpansionFactor 0
#endif
#if ENABLE(SERVER_PRECONNECT)
#define DEFAULT_VALUE_FOR_LinkPreconnect true
#else
#define DEFAULT_VALUE_FOR_LinkPreconnect false
#endif
#define DEFAULT_VALUE_FOR_LinkPreloadEnabled true
#define DEFAULT_VALUE_FOR_LoadDeferringEnabled true
#define DEFAULT_VALUE_FOR_LoadsImagesAutomatically true
#define DEFAULT_VALUE_FOR_LongRunningMediaCaptureStreamRepromptIntervalInHours 24
#define DEFAULT_VALUE_FOR_LowPowerVideoAudioBufferSizeEnabled true
#if ENABLE(MANAGED_MEDIA_SOURCE)
#define DEFAULT_VALUE_FOR_ManagedMediaSourceHighThreshold 30
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
#define DEFAULT_VALUE_FOR_ManagedMediaSourceLowThreshold 10
#endif
#if ENABLE(MATHML)
#define DEFAULT_VALUE_FOR_MathMLEnabled true
#endif
#define DEFAULT_VALUE_FOR_MaxParseDuration -1
#define DEFAULT_VALUE_FOR_MediaAudioCodecIDsAllowedInLockdownMode "aac ,zaac,qaac,caac,.mp3,mp4a"
#define DEFAULT_VALUE_FOR_MediaCapabilitiesEnabled true
#define DEFAULT_VALUE_FOR_MediaCaptionFormatTypesAllowedInLockdownMode "c608,wvtt"
#define DEFAULT_VALUE_FOR_MediaCodecTypesAllowedInLockdownMode "mp4a.40,avc1"
#define DEFAULT_VALUE_FOR_MediaContainerTypesAllowedInLockdownMode "video/mp4,audio/mp4,video/x-m4v,audio/x-m4a,audio/mp3,application/x-mpegURL,application/vnd.apple.mpegURL,video/mp2t,video/iso.segment,audio/aac,audio/mpeg,audio/ac3,audio/eac3,video/mpeg2,text/vtt"
#define DEFAULT_VALUE_FOR_MediaContentTypesRequiringHardwareSupport ""
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS)
#define DEFAULT_VALUE_FOR_MediaControlsContextMenusEnabled true
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_MediaControlsScaleWithPageZoom false
#else
#define DEFAULT_VALUE_FOR_MediaControlsScaleWithPageZoom true
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_MediaDataLoadsAutomatically false
#else
#define DEFAULT_VALUE_FOR_MediaDataLoadsAutomatically true
#endif
#if ENABLE(VIDEO)
#define DEFAULT_VALUE_FOR_MediaEnabled true
#endif
#define DEFAULT_VALUE_FOR_MediaPreferredFullscreenWidth 960
#define DEFAULT_VALUE_FOR_MediaPreloadingEnabled false
#if ENABLE(MEDIA_STREAM)
#define DEFAULT_VALUE_FOR_MediaStreamEnabled true
#endif
#define DEFAULT_VALUE_FOR_MediaUserGestureInheritsFromDocument false
#define DEFAULT_VALUE_FOR_MediaVideoCodecIDsAllowedInLockdownMode "avc1,zavc,qavc,cavc"
#define DEFAULT_VALUE_FOR_MenuItemElementEnabled false
#define DEFAULT_VALUE_FOR_MinimumFontSize 0
#define DEFAULT_VALUE_FOR_MinimumLogicalFontSize 9
#if ENABLE(TEXT_AUTOSIZING)
#if PLATFORM(WATCHOS)
#define DEFAULT_VALUE_FOR_MinimumZoomFontSize 30
#else
#define DEFAULT_VALUE_FOR_MinimumZoomFontSize 15
#endif
#endif
#define DEFAULT_VALUE_FOR_MockCaptureDevicesPromptEnabled true
#define DEFAULT_VALUE_FOR_MockScrollbarsControllerEnabled false
#define DEFAULT_VALUE_FOR_MockScrollbarsEnabled false
#define DEFAULT_VALUE_FOR_NeedsAdobeFrameReloadingQuirk false
#define DEFAULT_VALUE_FOR_NeedsFrameNameFallbackToIdQuirk false
#define DEFAULT_VALUE_FOR_NeedsKeyboardEventDisambiguationQuirks false
#define DEFAULT_VALUE_FOR_OfflineWebApplicationCacheEnabled WebKit::defaultOfflineWebApplicationCacheEnabled()
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_PDFPluginEnabled true
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_PassiveTouchListenersAsDefaultOnDocument WebKit::defaultPassiveTouchListenersAsDefaultOnDocument()
#else
#define DEFAULT_VALUE_FOR_PassiveTouchListenersAsDefaultOnDocument true
#endif
#define DEFAULT_VALUE_FOR_PasswordEchoDuration 2
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
#define DEFAULT_VALUE_FOR_PasswordEchoEnabled true
#else
#define DEFAULT_VALUE_FOR_PasswordEchoEnabled false
#endif
#if PLATFORM(COCOA) && PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_PictographFontFamily "AppleColorEmoji"
#elif PLATFORM(COCOA) && !PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_PictographFontFamily "Apple Color Emoji"
#else
#define DEFAULT_VALUE_FOR_PictographFontFamily "Times"
#endif
#if ENABLE(PICTURE_IN_PICTURE_API)
#define DEFAULT_VALUE_FOR_PictureInPictureAPIEnabled true
#endif
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_PitchCorrectionAlgorithm static_cast<uint32_t>(WebCore::MediaPlayerEnums::PitchCorrectionAlgorithm::BestForSpeech)
#else
#define DEFAULT_VALUE_FOR_PitchCorrectionAlgorithm static_cast<uint32_t>(WebCore::MediaPlayerEnums::PitchCorrectionAlgorithm::BestAllAround)
#endif
#define DEFAULT_VALUE_FOR_PluginsEnabled false
#define DEFAULT_VALUE_FOR_PunchOutWhiteBackgroundsInDarkMode false
#define DEFAULT_VALUE_FOR_RequiresPageVisibilityToPlayAudio false
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_RequiresUserGestureForAudioPlayback true
#else
#define DEFAULT_VALUE_FOR_RequiresUserGestureForAudioPlayback false
#endif
#define DEFAULT_VALUE_FOR_RequiresUserGestureForMediaPlayback false
#define DEFAULT_VALUE_FOR_RequiresUserGestureForVideoPlayback false
#define DEFAULT_VALUE_FOR_RequiresUserGestureToLoadVideo false
#if HAVE(RUBBER_BANDING)
#define DEFAULT_VALUE_FOR_RubberBandingForSubScrollableRegionsEnabled true
#endif
#define DEFAULT_VALUE_FOR_SampledPageTopColorMaxDifference 0
#define DEFAULT_VALUE_FOR_SampledPageTopColorMinHeight 0
#define DEFAULT_VALUE_FOR_SansSerifFontFamily "Helvetica"
#define DEFAULT_VALUE_FOR_SelectTrailingWhitespaceEnabled false
#define DEFAULT_VALUE_FOR_SerifFontFamily "Times"
#if ENABLE(SERVICE_CONTROLS)
#define DEFAULT_VALUE_FOR_ServiceControlsEnabled false
#endif
#if ENABLE(SERVICE_WORKER)
#define DEFAULT_VALUE_FOR_ServiceWorkerEntitlementDisabledForTesting false
#endif
#define DEFAULT_VALUE_FOR_ShouldAllowUserInstalledFonts true
#define DEFAULT_VALUE_FOR_ShouldConvertInvalidURLsToBlank true
#define DEFAULT_VALUE_FOR_ShouldConvertPositionStyleOnCopy false
#define DEFAULT_VALUE_FOR_ShouldDecidePolicyBeforeLoadingQuickLookPreview false
#if ENABLE(VIDEO)
#define DEFAULT_VALUE_FOR_ShouldDisplayCaptions false
#endif
#if ENABLE(VIDEO)
#define DEFAULT_VALUE_FOR_ShouldDisplaySubtitles false
#endif
#if ENABLE(VIDEO)
#define DEFAULT_VALUE_FOR_ShouldDisplayTextDescriptions false
#endif
#if ENABLE(TEXT_AUTOSIZING)
#define DEFAULT_VALUE_FOR_ShouldEnableTextAutosizingBoost false
#endif
#define DEFAULT_VALUE_FOR_ShouldIgnoreMetaViewport false
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_ShouldPrintBackgrounds WebKit::defaultShouldPrintBackgrounds()
#else
#define DEFAULT_VALUE_FOR_ShouldPrintBackgrounds false
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_ShouldRespectImageOrientation true
#else
#define DEFAULT_VALUE_FOR_ShouldRespectImageOrientation false
#endif
#define DEFAULT_VALUE_FOR_ShouldRestrictBaseURLSchemes false
#define DEFAULT_VALUE_FOR_ShouldSuppressTextInputFromEditingDuringProvisionalNavigation false
#define DEFAULT_VALUE_FOR_ShouldUseServiceWorkerShortTimeout false
#define DEFAULT_VALUE_FOR_ShowsToolTipOverTruncatedText false
#define DEFAULT_VALUE_FOR_ShowsURLsInToolTipsEnabled false
#define DEFAULT_VALUE_FOR_ShrinksStandaloneImagesToFit true
#define DEFAULT_VALUE_FOR_SmartInsertDeleteEnabled true
#if ENABLE(MEDIA_SOURCE)
#if USE(GSTREAMER)
#define DEFAULT_VALUE_FOR_SourceBufferChangeTypeEnabled false
#else
#define DEFAULT_VALUE_FOR_SourceBufferChangeTypeEnabled true
#endif
#endif
#define DEFAULT_VALUE_FOR_SpatialNavigationEnabled false
#define DEFAULT_VALUE_FOR_Standalone false
#if PLATFORM(WATCHOS)
#define DEFAULT_VALUE_FOR_StandardFontFamily "system-ui"
#else
#define DEFAULT_VALUE_FOR_StandardFontFamily "Times"
#endif
#define DEFAULT_VALUE_FOR_SuppressesIncrementalRendering false
#define DEFAULT_VALUE_FOR_SystemLayoutDirection TextDirection::LTR
#if USE(SYSTEM_PREVIEW)
#define DEFAULT_VALUE_FOR_SystemPreviewEnabled false
#endif
#if PLATFORM(GTK)
#define DEFAULT_VALUE_FOR_TabsToLinks true
#else
#define DEFAULT_VALUE_FOR_TabsToLinks false
#endif
#define DEFAULT_VALUE_FOR_TelephoneNumberParsingEnabled false
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_TemporaryTileCohortRetentionEnabled false
#else
#define DEFAULT_VALUE_FOR_TemporaryTileCohortRetentionEnabled true
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_TextAreasAreResizable false
#else
#define DEFAULT_VALUE_FOR_TextAreasAreResizable true
#endif
#if ENABLE(TEXT_AUTOSIZING)
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_TextAutosizingEnabled true
#else
#define DEFAULT_VALUE_FOR_TextAutosizingEnabled false
#endif
#endif
#if PLATFORM(WATCHOS)
#define DEFAULT_VALUE_FOR_TextInteractionEnabled false
#else
#define DEFAULT_VALUE_FOR_TextInteractionEnabled true
#endif
#define DEFAULT_VALUE_FOR_ThreadedScrollingEnabled true
#define DEFAULT_VALUE_FOR_TreatsAnyTextCSSLinkAsStylesheet false
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_UseImageDocumentForSubframePDF true
#else
#define DEFAULT_VALUE_FOR_UseImageDocumentForSubframePDF false
#endif
#define DEFAULT_VALUE_FOR_UseLegacyBackgroundSizeShorthandBehavior false
#define DEFAULT_VALUE_FOR_UsePreHTML5ParserQuirks false
#define DEFAULT_VALUE_FOR_UserInterfaceDirectionPolicy UserInterfaceDirectionPolicy::Content
#define DEFAULT_VALUE_FOR_UsesBackForwardCache true
#define DEFAULT_VALUE_FOR_UsesEncodingDetector false
#if ENABLE(VP9)
#define DEFAULT_VALUE_FOR_VP8DecoderEnabled true
#endif
#if ENABLE(VP9)
#define DEFAULT_VALUE_FOR_VP9DecoderEnabled true
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_VideoFullscreenRequiresElementFullscreen false
#endif
#if PLATFORM(VISION)
#define DEFAULT_VALUE_FOR_VideoPresentationModeAPIEnabled false
#else
#define DEFAULT_VALUE_FOR_VideoPresentationModeAPIEnabled true
#endif
#if ENABLE(VIDEO)
#define DEFAULT_VALUE_FOR_VideoQualityIncludesDisplayCompositingEnabled false
#endif
#define DEFAULT_VALUE_FOR_VisibleDebugOverlayRegions 0
#define DEFAULT_VALUE_FOR_VisualViewportEnabled true
#define DEFAULT_VALUE_FOR_WantsBalancedSetDefersLoadingBehavior false
#if ENABLE(WEB_AUDIO)
#define DEFAULT_VALUE_FOR_WebAudioEnabled true
#endif
#if ENABLE(WEBM_FORMAT_READER)
#define DEFAULT_VALUE_FOR_WebMFormatReaderEnabled true
#endif
#if ENABLE(MEDIA_SOURCE)
#define DEFAULT_VALUE_FOR_WebMParserEnabled true
#endif
#define DEFAULT_VALUE_FOR_WebSecurityEnabled true
#if PLATFORM(WATCHOS)
#define DEFAULT_VALUE_FOR_WebSocketEnabled false
#else
#define DEFAULT_VALUE_FOR_WebSocketEnabled true
#endif
#define DEFAULT_VALUE_FOR_WindowFocusRestricted true
#if PLATFORM(VISION)
#define DEFAULT_VALUE_FOR_WirelessPlaybackTargetAPIEnabled false
#else
#define DEFAULT_VALUE_FOR_WirelessPlaybackTargetAPIEnabled true
#endif
#define DEFAULT_VALUE_FOR_DirPseudoEnabled true
#define DEFAULT_VALUE_FOR_FocusVisibleEnabled true
#define DEFAULT_VALUE_FOR_HasPseudoClassEnabled true
#define DEFAULT_VALUE_FOR_PageAtRuleSupportEnabled false
#define DEFAULT_VALUE_FOR_AriaReflectionForElementReferencesEnabled true
#if USE(AVFOUNDATION)
#if PLATFORM(WATCHOS)
#define DEFAULT_VALUE_FOR_AVFoundationEnabled false
#else
#define DEFAULT_VALUE_FOR_AVFoundationEnabled true
#endif
#endif
#define DEFAULT_VALUE_FOR_AbortSignalAnyOperationEnabled false
#if USE(CORE_IMAGE)
#define DEFAULT_VALUE_FOR_AcceleratedFiltersEnabled false
#endif
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_AccessHandleEnabled true
#else
#define DEFAULT_VALUE_FOR_AccessHandleEnabled false
#endif
#define DEFAULT_VALUE_FOR_DOMTestingAPIsEnabled false
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_AllowMediaContentTypesRequiringHardwareSupportAsFallback true
#else
#define DEFAULT_VALUE_FOR_AllowMediaContentTypesRequiringHardwareSupportAsFallback false
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_AllowViewportShrinkToFitContent true
#endif
#if ENABLE(WEBGL)
#if ENABLE(WEBGL_IN_WORKERS)
#define DEFAULT_VALUE_FOR_AllowWebGLInWorkers true
#else
#define DEFAULT_VALUE_FOR_AllowWebGLInWorkers false
#endif
#endif
#if ENABLE(MEDIA_STREAM)
#define DEFAULT_VALUE_FOR_PerElementSpeakerSelectionEnabled false
#endif
#if ENABLE(MEDIA_STREAM)
#define DEFAULT_VALUE_FOR_ExposeSpeakersEnabled false
#endif
#define DEFAULT_VALUE_FOR_AllowTopNavigationToDataURLs false
#define DEFAULT_VALUE_FOR_AllowUniversalAccessFromFileURLs false
#if ENABLE(ALTERNATE_WEBM_PLAYER)
#define DEFAULT_VALUE_FOR_AlternateWebMPlayerEnabled false
#endif
#if ENABLE(BADGING)
#define DEFAULT_VALUE_FOR_AppBadgeEnabled false
#endif
#if ENABLE(APP_HIGHLIGHTS)
#define DEFAULT_VALUE_FOR_AppHighlightsEnabled false
#endif
#define DEFAULT_VALUE_FOR_AspectRatioOfImgFromWidthAndHeightEnabled true
#if USE(NICOSIA)
#define DEFAULT_VALUE_FOR_AsyncFrameScrollingEnabled true
#elif PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_AsyncFrameScrollingEnabled true
#else
#define DEFAULT_VALUE_FOR_AsyncFrameScrollingEnabled false
#endif
#if USE(NICOSIA)
#define DEFAULT_VALUE_FOR_AsyncOverflowScrollingEnabled true
#elif PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_AsyncOverflowScrollingEnabled true
#else
#define DEFAULT_VALUE_FOR_AsyncOverflowScrollingEnabled false
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK)
#define DEFAULT_VALUE_FOR_AsyncClipboardAPIEnabled true
#else
#define DEFAULT_VALUE_FOR_AsyncClipboardAPIEnabled false
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
#define DEFAULT_VALUE_FOR_AttachmentElementEnabled false
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
#define DEFAULT_VALUE_FOR_AttachmentWideLayoutEnabled false
#endif
#if ENABLE(VIDEO)
#define DEFAULT_VALUE_FOR_ExtendedAudioDescriptionsEnabled false
#endif
#if ENABLE(VIDEO)
#define DEFAULT_VALUE_FOR_AudioDescriptionsEnabled false
#endif
#if ENABLE(DOM_AUDIO_SESSION)
#define DEFAULT_VALUE_FOR_DOMAudioSessionEnabled true
#endif
#if ENABLE(DOM_AUDIO_SESSION)
#define DEFAULT_VALUE_FOR_DOMAudioSessionFullEnabled false
#endif
#define DEFAULT_VALUE_FOR_BeaconAPIEnabled true
#define DEFAULT_VALUE_FOR_ThirdPartyIframeRedirectBlockingEnabled true
#define DEFAULT_VALUE_FOR_BroadcastChannelEnabled true
#define DEFAULT_VALUE_FOR_BroadcastChannelOriginPartitioningEnabled true
#if ENABLE(BUILT_IN_NOTIFICATIONS)
#define DEFAULT_VALUE_FOR_BuiltInNotificationsEnabled false
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
#define DEFAULT_VALUE_FOR_UseCGDisplayListsForDOMRendering true
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
#define DEFAULT_VALUE_FOR_UseCGDisplayListImageCache true
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
#define DEFAULT_VALUE_FOR_ReplayCGDisplayListsIntoBackingStore false
#endif
#define DEFAULT_VALUE_FOR_CSS3DTransformInteroperabilityEnabled true
#define DEFAULT_VALUE_FOR_CSSCounterStyleAtRuleImageSymbolsEnabled false
#define DEFAULT_VALUE_FOR_CSSCounterStyleAtRulesEnabled true
#define DEFAULT_VALUE_FOR_CSSFontFaceSizeAdjustEnabled true
#if PLATFORM(COCOA) || PLATFORM(GTK) || PLATFORM(WPE)
#define DEFAULT_VALUE_FOR_AccentColorEnabled true
#else
#define DEFAULT_VALUE_FOR_AccentColorEnabled false
#endif
#define DEFAULT_VALUE_FOR_AspectRatioEnabled true
#define DEFAULT_VALUE_FOR_CSSCascadeLayersEnabled true
#define DEFAULT_VALUE_FOR_CSSColor4 true
#define DEFAULT_VALUE_FOR_CSSContainIntrinsicSizeEnabled true
#define DEFAULT_VALUE_FOR_CSSContainerQueriesEnabled true
#define DEFAULT_VALUE_FOR_CSSContainmentEnabled true
#define DEFAULT_VALUE_FOR_CSSContentVisibilityEnabled false
#define DEFAULT_VALUE_FOR_CSSCustomPropertiesAndValuesEnabled true
#define DEFAULT_VALUE_FOR_CSSGradientInterpolationColorSpacesEnabled true
#define DEFAULT_VALUE_FOR_CSSGradientPremultipliedAlphaInterpolationEnabled true
#define DEFAULT_VALUE_FOR_CSSIndividualTransformPropertiesEnabled true
#define DEFAULT_VALUE_FOR_CSSInputSecurityEnabled false
#define DEFAULT_VALUE_FOR_MasonryEnabled false
#define DEFAULT_VALUE_FOR_CSSMotionPathEnabled true
#define DEFAULT_VALUE_FOR_CSSNestingEnabled true
#if PLATFORM(WIN) || PLATFORM(GTK) || PLATFORM(WPE)
#define DEFAULT_VALUE_FOR_OverscrollBehaviorEnabled false
#else
#define DEFAULT_VALUE_FOR_OverscrollBehaviorEnabled true
#endif
#if ENABLE(CSS_PAINTING_API)
#if ENABLE(EXPERIMENTAL_FEATURES)
#define DEFAULT_VALUE_FOR_CSSPaintingAPIEnabled true
#else
#define DEFAULT_VALUE_FOR_CSSPaintingAPIEnabled false
#endif
#endif
#define DEFAULT_VALUE_FOR_CSSRelativeColorSyntaxEnabled true
#define DEFAULT_VALUE_FOR_CSSRhythmicSizingEnabled false
#define DEFAULT_VALUE_FOR_CSSScrollAnchoringEnabled false
#if ENABLE(EXPERIMENTAL_FEATURES)
#define DEFAULT_VALUE_FOR_SpringTimingFunctionEnabled true
#else
#define DEFAULT_VALUE_FOR_SpringTimingFunctionEnabled false
#endif
#define DEFAULT_VALUE_FOR_CSSTypedOMEnabled true
#define DEFAULT_VALUE_FOR_CSSTypedOMColorEnabled false
#define DEFAULT_VALUE_FOR_MasonryTrackAlignmentEnabled false
#define DEFAULT_VALUE_FOR_CSSColorContrastEnabled false
#define DEFAULT_VALUE_FOR_CSSColorMixEnabled true
#define DEFAULT_VALUE_FOR_CSSMarginTrimEnabled true
#define DEFAULT_VALUE_FOR_OverflowClipEnabled true
#define DEFAULT_VALUE_FOR_CSSScrollbarColorEnabled false
#define DEFAULT_VALUE_FOR_CSSScrollbarGutterEnabled false
#define DEFAULT_VALUE_FOR_CSSScrollbarWidthEnabled false
#define DEFAULT_VALUE_FOR_SubgridEnabled true
#define DEFAULT_VALUE_FOR_CSSTextAlignLastEnabled true
#define DEFAULT_VALUE_FOR_CSSTextBoxTrimEnabled false
#define DEFAULT_VALUE_FOR_CSSTextGroupAlignEnabled false
#define DEFAULT_VALUE_FOR_CSSTextJustifyEnabled false
#define DEFAULT_VALUE_FOR_CSSTextSpacingEnabled false
#define DEFAULT_VALUE_FOR_CSSTextUnderlinePositionLeftRightEnabled false
#define DEFAULT_VALUE_FOR_CSSWhiteSpaceLonghandsEnabled false
#define DEFAULT_VALUE_FOR_CSSTextWrapNewValuesEnabled false
#if ENABLE(CSS_TRANSFORM_STYLE_OPTIMIZED_3D)
#define DEFAULT_VALUE_FOR_CSSTransformStyleOptimized3DEnabled false
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_CSSOMViewScrollingAPIEnabled WebKit::defaultCSSOMViewScrollingAPIEnabled()
#else
#define DEFAULT_VALUE_FOR_CSSOMViewScrollingAPIEnabled true
#endif
#define DEFAULT_VALUE_FOR_CSSOMViewSmoothScrollingEnabled true
#define DEFAULT_VALUE_FOR_CacheAPIEnabled true
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_CanvasColorSpaceEnabled true
#else
#define DEFAULT_VALUE_FOR_CanvasColorSpaceEnabled false
#endif
#define DEFAULT_VALUE_FOR_CanvasFiltersEnabled false
#define DEFAULT_VALUE_FOR_CanvasUsesAcceleratedDrawing true
#if ENABLE(MEDIA_STREAM)
#define DEFAULT_VALUE_FOR_CaptureAudioInUIProcessEnabled WebKit::defaultCaptureAudioInUIProcessEnabled()
#endif
#if ENABLE(MEDIA_STREAM)
#define DEFAULT_VALUE_FOR_CaptureVideoInUIProcessEnabled false
#endif
#define DEFAULT_VALUE_FOR_ClearSiteDataHTTPHeaderEnabled true
#if ENABLE(BADGING)
#define DEFAULT_VALUE_FOR_ClientBadgeEnabled false
#endif
#if ENABLE(INPUT_TYPE_COLOR)
#if PLATFORM(WATCHOS)
#define DEFAULT_VALUE_FOR_InputTypeColorEnabled false
#else
#define DEFAULT_VALUE_FOR_InputTypeColorEnabled true
#endif
#endif
#define DEFAULT_VALUE_FOR_CompositingBordersVisible false
#define DEFAULT_VALUE_FOR_CompositingRepaintCountersVisible false
#define DEFAULT_VALUE_FOR_CompressionStreamEnabled true
#define DEFAULT_VALUE_FOR_ConstructableStylesheetsEnabled true
#define DEFAULT_VALUE_FOR_ContactPickerAPIEnabled false
#if HAVE(AVCONTENTKEYSPECIFIER)
#define DEFAULT_VALUE_FOR_SampleBufferContentKeySessionSupportEnabled false
#endif
#define DEFAULT_VALUE_FOR_CookieConsentAPIEnabled false
#define DEFAULT_VALUE_FOR_CookieStoreAPIExtendedAttributesEnabled false
#define DEFAULT_VALUE_FOR_CookieStoreAPIEnabled false
#define DEFAULT_VALUE_FOR_CookieEnabled true
#define DEFAULT_VALUE_FOR_CrossOriginEmbedderPolicyEnabled true
#define DEFAULT_VALUE_FOR_CrossOriginOpenerPolicyEnabled true
#if PLATFORM(COCOA) || PLATFORM(GTK) || PLATFORM(WIN)
#define DEFAULT_VALUE_FOR_CustomPasteboardDataEnabled true
#else
#define DEFAULT_VALUE_FOR_CustomPasteboardDataEnabled false
#endif
#if PLATFORM(IOS) || PLATFORM(MAC) || PLATFORM(GTK) || PLATFORM(VISION)
#define DEFAULT_VALUE_FOR_DOMPasteAccessRequestsEnabled true
#else
#define DEFAULT_VALUE_FOR_DOMPasteAccessRequestsEnabled false
#endif
#define DEFAULT_VALUE_FOR_DOMTimersThrottlingEnabled true
#define DEFAULT_VALUE_FOR_DeclarativeShadowDOMInDOMParserEnabled false
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_ZoomOnDoubleTapWhenRoot false
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_AlwaysZoomOnDoubleTap false
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK) || PLATFORM(WPE)
#define DEFAULT_VALUE_FOR_DataTransferItemsEnabled true
#else
#define DEFAULT_VALUE_FOR_DataTransferItemsEnabled false
#endif
#if ENABLE(DATALIST_ELEMENT)
#if PLATFORM(WATCHOS)
#define DEFAULT_VALUE_FOR_DataListElementEnabled false
#else
#define DEFAULT_VALUE_FOR_DataListElementEnabled true
#endif
#endif
#if ENABLE(INPUT_TYPE_DATE)
#if PLATFORM(APPLETV)
#define DEFAULT_VALUE_FOR_InputTypeDateEnabled false
#else
#define DEFAULT_VALUE_FOR_InputTypeDateEnabled true
#endif
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
#if PLATFORM(MAC) || PLATFORM(GTK)
#define DEFAULT_VALUE_FOR_DateTimeInputsEditableComponentsEnabled true
#else
#define DEFAULT_VALUE_FOR_DateTimeInputsEditableComponentsEnabled false
#endif
#endif
#define DEFAULT_VALUE_FOR_DeclarativeShadowDOMEnabled true
#define DEFAULT_VALUE_FOR_DefaultARIAForCustomElementsEnabled true
#define DEFAULT_VALUE_FOR_ShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint true
#define DEFAULT_VALUE_FOR_DeprecateRSAESPKCSWebCryptoEnabled true
#define DEFAULT_VALUE_FOR_DeprecationReportingEnabled false
#define DEFAULT_VALUE_FOR_DiagnosticLoggingEnabled false
#if PLATFORM(COCOA) || PLATFORM(GTK) || PLATFORM(WPE)
#define DEFAULT_VALUE_FOR_DirectoryUploadEnabled true
#else
#define DEFAULT_VALUE_FOR_DirectoryUploadEnabled false
#endif
#define DEFAULT_VALUE_FOR_IsThirdPartyCookieBlockingDisabled false
#define DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalDisabled false
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_DisableScreenSizeOverride false
#endif
#if PLATFORM(MAC) || PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_DisallowSyncXHRDuringPageDismissalEnabled WebKit::defaultDisallowSyncXHRDuringPageDismissalEnabled()
#else
#define DEFAULT_VALUE_FOR_DisallowSyncXHRDuringPageDismissalEnabled true
#endif
#define DEFAULT_VALUE_FOR_DisplayListDrawingEnabled false
#define DEFAULT_VALUE_FOR_ShouldDropNearSuspendedAssertionAfterDelay WebKit::defaultShouldDropNearSuspendedAssertionAfterDelay()
#define DEFAULT_VALUE_FOR_EmbedElementEnabled true
#if PLATFORM(VISION)
#define DEFAULT_VALUE_FOR_AutomaticLiveResizeEnabled true
#else
#define DEFAULT_VALUE_FOR_AutomaticLiveResizeEnabled false
#endif
#define DEFAULT_VALUE_FOR_CanvasFingerprintingQuirkEnabled true
#define DEFAULT_VALUE_FOR_EnumeratingAllNetworkInterfacesEnabled false
#define DEFAULT_VALUE_FOR_EnumeratingVisibleNetworkInterfacesEnabled false
#define DEFAULT_VALUE_FOR_ICECandidateFilteringEnabled true
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
#define DEFAULT_VALUE_FOR_LegacyEncryptedMediaAPIEnabled true
#endif
#if ENABLE(MEDIA_STREAM)
#if PLATFORM(IOS_FAMILY_SIMULATOR)
#define DEFAULT_VALUE_FOR_MockCaptureDevicesEnabled true
#else
#define DEFAULT_VALUE_FOR_MockCaptureDevicesEnabled false
#endif
#endif
#if ENABLE(PDFJS)
#if PLATFORM(GTK) || PLATFORM(WPE)
#define DEFAULT_VALUE_FOR_PdfJSViewerEnabled true
#else
#define DEFAULT_VALUE_FOR_PdfJSViewerEnabled false
#endif
#endif
#if PLATFORM(MAC) && USE(RUNNINGBOARD)
#define DEFAULT_VALUE_FOR_BackgroundWebContentRunningBoardThrottlingEnabled WebKit::defaultRunningBoardThrottlingEnabled()
#endif
#if ENABLE(SERVICE_WORKER)
#define DEFAULT_VALUE_FOR_BackgroundFetchAPIEnabled false
#endif
#if HAVE(MACH_BOOTSTRAP_EXTENSION) || HAVE(SANDBOX_STATE_FLAGS)
#define DEFAULT_VALUE_FOR_ExperimentalSandboxEnabled false
#endif
#define DEFAULT_VALUE_FOR_StrictSecureDecodingForAllObjC true
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_EnterKeyHintEnabled true
#else
#define DEFAULT_VALUE_FOR_EnterKeyHintEnabled false
#endif
#if PLATFORM(MAC)
#define DEFAULT_VALUE_FOR_EventHandlerDrivenSmoothKeyboardScrollingEnabled WebKit::defaultScrollAnimatorEnabled()
#else
#define DEFAULT_VALUE_FOR_EventHandlerDrivenSmoothKeyboardScrollingEnabled false
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
#define DEFAULT_VALUE_FOR_MediaSessionCoordinatorEnabled WebKit::defaultMediaSessionCoordinatorEnabled()
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR) && ENABLE(MEDIA_SESSION_PLAYLIST)
#define DEFAULT_VALUE_FOR_MediaSessionPlaylistEnabled WebKit::defaultMediaSessionCoordinatorEnabled()
#endif
#if ENABLE(MEDIA_SOURCE) && (HAVE(AVSAMPLEBUFFERVIDEOOUTPUT) || USE(GSTREAMER))
#if HAVE(AVSAMPLEBUFFERDISPLAYLAYER_COPYDISPLAYEDPIXELBUFFER)
#define DEFAULT_VALUE_FOR_MediaSourceInlinePaintingEnabled true
#else
#define DEFAULT_VALUE_FOR_MediaSourceInlinePaintingEnabled false
#endif
#endif
#if HAVE(NETWORK_LOADER)
#define DEFAULT_VALUE_FOR_CFNetworkNetworkLoaderEnabled false
#endif
#define DEFAULT_VALUE_FOR_FTPEnabled false
#if PLATFORM(IOS_FAMILY)
#if PLATFORM(IOS_FAMILY) && !PLATFORM(WATCHOS)
#define DEFAULT_VALUE_FOR_PreferFasterClickOverDoubleTap true
#else
#define DEFAULT_VALUE_FOR_PreferFasterClickOverDoubleTap false
#endif
#endif
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_FasterClicksEnabled true
#endif
#define DEFAULT_VALUE_FOR_FetchAPIKeepAliveEnabled true
#define DEFAULT_VALUE_FOR_FetchAPIEnabled true
#define DEFAULT_VALUE_FOR_FetchMetadataEnabled true
#define DEFAULT_VALUE_FOR_FetchPriorityEnabled false
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_FileSystemAccessEnabled true
#else
#define DEFAULT_VALUE_FOR_FileSystemAccessEnabled false
#endif
#define DEFAULT_VALUE_FOR_FileReaderAPIEnabled true
#define DEFAULT_VALUE_FOR_RestrictedHTTPResponseAccess true
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_ForceAlwaysUserScalable false
#endif
#define DEFAULT_VALUE_FOR_RequestSubmitEnabled true
#define DEFAULT_VALUE_FOR_FormAssociatedCustomElementsEnabled true
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_FrameFlatteningEnabled true
#else
#define DEFAULT_VALUE_FOR_FrameFlatteningEnabled false
#endif
#define DEFAULT_VALUE_FOR_LayoutFormattingContextEnabled false
#if ENABLE(FULLSCREEN_API)
#define DEFAULT_VALUE_FOR_FullScreenEnabled false
#endif
#if PLATFORM(VISION)
#define DEFAULT_VALUE_FOR_FullscreenSceneAspectRatioLockingEnabled true
#endif
#if PLATFORM(VISION)
#define DEFAULT_VALUE_FOR_FullscreenSceneDimmingEnabled false
#endif
#if ENABLE(MEDIA_STREAM)
#define DEFAULT_VALUE_FOR_CaptureAudioInGPUProcessEnabled WebKit::defaultCaptureAudioInGPUProcessEnabled()
#endif
#if ENABLE(GPU_PROCESS)
#define DEFAULT_VALUE_FOR_BlockMediaLayerRehostingInWebContentProcess true
#endif
#if ENABLE(GPU_PROCESS) && !(PLATFORM(GTK) || PLATFORM(WPE))
#if ENABLE(GPU_PROCESS_BY_DEFAULT)
#define DEFAULT_VALUE_FOR_UseGPUProcessForCanvasRenderingEnabled true
#elif USE(GRAPHICS_LAYER_WC)
#define DEFAULT_VALUE_FOR_UseGPUProcessForCanvasRenderingEnabled true
#else
#define DEFAULT_VALUE_FOR_UseGPUProcessForCanvasRenderingEnabled false
#endif
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_ManageCaptureStatusBarInGPUProcessEnabled WebKit::defaultManageCaptureStatusBarInGPUProcessEnabled()
#endif
#if ENABLE(GPU_PROCESS)
#define DEFAULT_VALUE_FOR_UseGPUProcessForDOMRenderingEnabled defaultUseGPUProcessForDOMRenderingEnabled()
#endif
#if ENABLE(GPU_PROCESS) && !USE(GSTREAMER)
#if ENABLE(GPU_PROCESS_BY_DEFAULT)
#define DEFAULT_VALUE_FOR_UseGPUProcessForMediaEnabled true
#else
#define DEFAULT_VALUE_FOR_UseGPUProcessForMediaEnabled false
#endif
#endif
#if HAVE(SCREEN_CAPTURE_KIT)
#define DEFAULT_VALUE_FOR_UseGPUProcessForDisplayCapture true
#endif
#if ENABLE(MEDIA_STREAM)
#if ENABLE(GPU_PROCESS_BY_DEFAULT)
#define DEFAULT_VALUE_FOR_CaptureVideoInGPUProcessEnabled true
#else
#define DEFAULT_VALUE_FOR_CaptureVideoInGPUProcessEnabled false
#endif
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
#if ENABLE(GPU_PROCESS_BY_DEFAULT) && ENABLE(GPU_PROCESS_WEBGL_BY_DEFAULT)
#define DEFAULT_VALUE_FOR_UseGPUProcessForWebGLEnabled true
#elif USE(GRAPHICS_LAYER_WC)
#define DEFAULT_VALUE_FOR_UseGPUProcessForWebGLEnabled true
#else
#define DEFAULT_VALUE_FOR_UseGPUProcessForWebGLEnabled false
#endif
#endif
#if ENABLE(WEB_RTC)
#if ENABLE(GPU_PROCESS_BY_DEFAULT)
#define DEFAULT_VALUE_FOR_WebRTCPlatformCodecsInGPUProcessEnabled true
#else
#define DEFAULT_VALUE_FOR_WebRTCPlatformCodecsInGPUProcessEnabled false
#endif
#endif
#if ENABLE(GAMEPAD)
#define DEFAULT_VALUE_FOR_GamepadTriggerRumbleEnabled false
#endif
#if ENABLE(GAMEPAD)
#define DEFAULT_VALUE_FOR_GamepadVibrationActuatorEnabled defaultGamepadVibrationActuatorEnabled()
#endif
#if ENABLE(GAMEPAD)
#define DEFAULT_VALUE_FOR_GamepadsEnabled true
#endif
#if ENABLE(VIDEO)
#define DEFAULT_VALUE_FOR_GenericCueAPIEnabled true
#endif
#if USE(GRAPHICS_CONTEXT_FILTERS)
#define DEFAULT_VALUE_FOR_GraphicsContextFiltersEnabled false
#endif
#define DEFAULT_VALUE_FOR_AcceleratedDrawingEnabled true
#define DEFAULT_VALUE_FOR_DialogElementEnabled true
#if ENABLE(MODEL_ELEMENT)
#define DEFAULT_VALUE_FOR_ModelElementEnabled false
#endif
#if ENABLE(MODEL_ELEMENT)
#define DEFAULT_VALUE_FOR_ModelDocumentEnabled false
#endif
#define DEFAULT_VALUE_FOR_InteractiveFormValidationEnabled true
#define DEFAULT_VALUE_FOR_InertAttributeEnabled true
#define DEFAULT_VALUE_FOR_PopoverAttributeEnabled WebKit::defaultPopoverAttributeEnabled()
#define DEFAULT_VALUE_FOR_HiddenPageDOMTimerThrottlingAutoIncreases false
#if PLATFORM(COCOA) || PLATFORM(GTK)
#define DEFAULT_VALUE_FOR_HiddenPageDOMTimerThrottlingEnabled true
#else
#define DEFAULT_VALUE_FOR_HiddenPageDOMTimerThrottlingEnabled false
#endif
#define DEFAULT_VALUE_FOR_HighlightAPIEnabled false
#define DEFAULT_VALUE_FOR_HyperlinkAuditingEnabled true
#if HAVE(SANDBOX_STATE_FLAGS)
#define DEFAULT_VALUE_FOR_BlockIOKitInWebContentSandbox true
#endif
#if ENABLE(IPC_TESTING_API)
#define DEFAULT_VALUE_FOR_IPCTestingAPIEnabled false
#endif
#define DEFAULT_VALUE_FOR_ItpDebugModeEnabled false
#if ENABLE(TEXT_AUTOSIZING)
#if PLATFORM(IOS_FAMILY) && !PLATFORM(VISION)
#define DEFAULT_VALUE_FOR_TextAutosizingUsesIdempotentMode defaultTextAutosizingUsesIdempotentMode()
#else
#define DEFAULT_VALUE_FOR_TextAutosizingUsesIdempotentMode false
#endif
#endif
#if ENABLE(IMAGE_ANALYSIS)
#define DEFAULT_VALUE_FOR_ImageAnalysisDuringFindInPageEnabled false
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
#define DEFAULT_VALUE_FOR_ImageAnimationControlEnabled true
#endif
#if ENABLE(SERVICE_CONTROLS)
#define DEFAULT_VALUE_FOR_ImageControlsEnabled false
#endif
#define DEFAULT_VALUE_FOR_ImperativeSlotAPIEnabled true
#define DEFAULT_VALUE_FOR_IndexedDBAPIEnabled true
#define DEFAULT_VALUE_FOR_InlinePredictionsInAllEditableElementsEnabled false
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
#define DEFAULT_VALUE_FOR_InteractionRegionsEnabled true
#endif
#define DEFAULT_VALUE_FOR_IntersectionObserverEnabled true
#define DEFAULT_VALUE_FOR_IsLoggedInAPIEnabled false
#if ENABLE(ACCESSIBILITY_ISOLATED_TREE)
#if USE(ATSPI)
#define DEFAULT_VALUE_FOR_IsAccessibilityIsolatedTreeEnabled true
#else
#define DEFAULT_VALUE_FOR_IsAccessibilityIsolatedTreeEnabled false
#endif
#endif
#define DEFAULT_VALUE_FOR_JavaScriptEnabled true
#if ENABLE(LAYER_BASED_SVG_ENGINE)
#define DEFAULT_VALUE_FOR_LayerBasedSVGEngineEnabled false
#endif
#define DEFAULT_VALUE_FOR_LazyIframeLoadingEnabled true
#define DEFAULT_VALUE_FOR_LazyImageLoadingEnabled true
#if ENABLE(OVERFLOW_SCROLLING_TOUCH)
#define DEFAULT_VALUE_FOR_LegacyOverflowScrollingTouchEnabled true
#endif
#define DEFAULT_VALUE_FOR_LegacyLineLayoutVisualCoverageEnabled false
#define DEFAULT_VALUE_FOR_ShowModalDialogEnabled WebKit::defaultShowModalDialogEnabled()
#if ENABLE(MEDIA_STREAM)
#define DEFAULT_VALUE_FOR_MediaCaptureRequiresSecureConnection true
#endif
#define DEFAULT_VALUE_FOR_LinkSanitizerEnabled false
#define DEFAULT_VALUE_FOR_LinkPreloadResponsiveImagesEnabled false
#define DEFAULT_VALUE_FOR_LinkModulePreloadEnabled true
#if ENABLE(SERVER_PRECONNECT)
#define DEFAULT_VALUE_FOR_LinkPreconnectEarlyHintsEnabled true
#else
#define DEFAULT_VALUE_FOR_LinkPreconnectEarlyHintsEnabled false
#endif
#define DEFAULT_VALUE_FOR_LinkPrefetchEnabled false
#define DEFAULT_VALUE_FOR_LiveRangeSelectionEnabled WebKit::defaultLiveRangeSelectionEnabled()
#define DEFAULT_VALUE_FOR_LocalFileContentSniffingEnabled false
#define DEFAULT_VALUE_FOR_LocalStorageEnabled true
#define DEFAULT_VALUE_FOR_LogsPageMessagesToSystemConsoleEnabled false
#define DEFAULT_VALUE_FOR_MainContentUserGestureOverrideEnabled false
#if ENABLE(MANAGED_MEDIA_SOURCE)
#define DEFAULT_VALUE_FOR_ManagedMediaSourceEnabled WebKit::defaultManagedMediaSourceEnabled()
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE) && ENABLE(WIRELESS_PLAYBACK_TARGET)
#define DEFAULT_VALUE_FOR_ManagedMediaSourceNeedsAirPlay WebKit::defaultManagedMediaSourceNeedsAirPlay()
#endif
#if ENABLE(WEBGL)
#define DEFAULT_VALUE_FOR_MaskWebGLStringsEnabled true
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
#define DEFAULT_VALUE_FOR_CoreMathMLEnabled true
#else
#define DEFAULT_VALUE_FOR_CoreMathMLEnabled false
#endif
#define DEFAULT_VALUE_FOR_MediaCapabilitiesExtensionsEnabled true
#if ENABLE(MEDIA_SESSION)
#define DEFAULT_VALUE_FOR_MediaSessionEnabled true
#endif
#if ENABLE(MEDIA_SOURCE) && PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_MediaSourceEnabled WebKit::defaultMediaSourceEnabled()
#elif ENABLE(MEDIA_SOURCE) && !PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_MediaSourceEnabled true
#else
#define DEFAULT_VALUE_FOR_MediaSourceEnabled false
#endif
#if ENABLE(MEDIA_STREAM)
#define DEFAULT_VALUE_FOR_MediaDevicesEnabled false
#endif
#if ENABLE(MEDIA_RECORDER)
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_MediaRecorderEnabled true
#elif USE(GSTREAMER_TRANSCODER)
#define DEFAULT_VALUE_FOR_MediaRecorderEnabled true
#else
#define DEFAULT_VALUE_FOR_MediaRecorderEnabled false
#endif
#endif
#define DEFAULT_VALUE_FOR_MomentumScrollingAnimatorEnabled true
#if ENABLE(INPUT_TYPE_MONTH)
#if !PLATFORM(MAC) && !PLATFORM(APPLETV)
#define DEFAULT_VALUE_FOR_InputTypeMonthEnabled true
#else
#define DEFAULT_VALUE_FOR_InputTypeMonthEnabled false
#endif
#endif
#if ENABLE(TOUCH_EVENTS)
#define DEFAULT_VALUE_FOR_MouseEventsSimulationEnabled false
#endif
#if ENABLE(MEDIA_STREAM)
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_MuteCameraOnMicrophoneInterruptionEnabled true
#else
#define DEFAULT_VALUE_FOR_MuteCameraOnMicrophoneInterruptionEnabled false
#endif
#endif
#if ENABLE(APP_BOUND_DOMAINS)
#define DEFAULT_VALUE_FOR_NeedsInAppBrowserPrivacyQuirks false
#endif
#define DEFAULT_VALUE_FOR_NeedsSiteSpecificQuirks true
#define DEFAULT_VALUE_FOR_NeedsStorageAccessFromFileURLsQuirk true
#define DEFAULT_VALUE_FOR_FlexFormattingContextIntegrationEnabled false
#define DEFAULT_VALUE_FOR_InlineFormattingContextIntegrationEnabled true
#if ENABLE(NOTIFICATION_EVENT)
#if ENABLE(NOTIFICATION_EVENT) && !PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_NotificationEventEnabled true
#else
#define DEFAULT_VALUE_FOR_NotificationEventEnabled false
#endif
#endif
#if ENABLE(NOTIFICATIONS)
#if PLATFORM(IOS_FAMILY)
#define DEFAULT_VALUE_FOR_NotificationsEnabled false
#else
#define DEFAULT_VALUE_FOR_NotificationsEnabled true
#endif
#endif
#if ENABLE(OFFSCREEN_CANVAS_IN_WORKERS)
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_OffscreenCanvasInWorkersEnabled true
#else
#define DEFAULT_VALUE_FOR_OffscreenCanvasInWorkersEnabled false
#endif
#endif
#if ENABLE(OFFSCREEN_CANVAS)
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_OffscreenCanvasEnabled true
#else
#define DEFAULT_VALUE_FOR_OffscreenCanvasEnabled false
#endif
#endif
#if ENABLE(OPUS)
#define DEFAULT_VALUE_FOR_OpusDecoderEnabled true
#endif
#define DEFAULT_VALUE_FOR_PageVisibilityBasedProcessSuppressionEnabled true
#define DEFAULT_VALUE_FOR_PaintTimingEnabled true
#define DEFAULT_VALUE_FOR_BlobRegistryTopOriginPartitioningEnabled false
#define DEFAULT_VALUE_FOR_PerformanceNavigationTimingAPIEnabled true
#define DEFAULT_VALUE_FOR_PerformanceResourceTimingSensitivePropertiesEnabled true
#if PLATFORM(COCOA) || PLATFORM(GTK) || PLATFORM(WPE)
#define DEFAULT_VALUE_FOR_PermissionsAPIEnabled true
#else
#define DEFAULT_VALUE_FOR_PermissionsAPIEnabled false
#endif
#if ENABLE(FULL_SPEED_ANIMATION_LOOP)
#define DEFAULT_VALUE_FOR_PreferPageRenderingUpdatesNear60FPSEnabled false
#else
#define DEFAULT_VALUE_FOR_PreferPageRenderingUpdatesNear60FPSEnabled true
#endif
#if ENABLE(VIDEO)
#define DEFAULT_VALUE_FOR_PreferSandboxedMediaParsing true
#endif
#define DEFAULT_VALUE_FOR_PrivateClickMeasurementDebugModeEnabled false
#if HAVE(RSA_BSSA)
#define DEFAULT_VALUE_FOR_PrivateClickMeasurementFraudPreventionEnabled true
#else
#define DEFAULT_VALUE_FOR_PrivateClickMeasurementFraudPreventionEnabled false
#endif
#define DEFAULT_VALUE_FOR_PrivateClickMeasurementEnabled true
#if ENABLE(SERVICE_WORKER)
#define DEFAULT_VALUE_FOR_PushAPIEnabled false
#endif
#define DEFAULT_VALUE_FOR_GoogleAntiFlickerOptimizationQuirkEnabled true
#define DEFAULT_VALUE_FOR_ReadableByteStreamAPIEnabled false
#define DEFAULT_VALUE_FOR_ReferrerPolicyAttributeEnabled true
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
#if PLATFORM(VISION)
#define DEFAULT_VALUE_FOR_RemotePlaybackEnabled false
#else
#define DEFAULT_VALUE_FOR_RemotePlaybackEnabled true
#endif
#endif
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
#define DEFAULT_VALUE_FOR_RemoveBackgroundEnabled defaultRemoveBackgroundEnabled()
#endif
#define DEFAULT_VALUE_FOR_ReportingEnabled true
#if PLATFORM(COCOA) && HAVE(AVSAMPLEBUFFERVIDEOOUTPUT)
#define DEFAULT_VALUE_FOR_RequestVideoFrameCallbackEnabled true
#elif USE(GSTREAMER)
#define DEFAULT_VALUE_FOR_RequestVideoFrameCallbackEnabled true
#else
#define DEFAULT_VALUE_FOR_RequestVideoFrameCallbackEnabled false
#endif
#if HAVE(SC_CONTENT_SHARING_PICKER)
#define DEFAULT_VALUE_FOR_RequireUAGetDisplayMediaPrompt true
#endif
#if ENABLE(MEDIA_STREAM)
#define DEFAULT_VALUE_FOR_SpeakerSelectionRequiresUserGesture true
#endif
#define DEFAULT_VALUE_FOR_FullscreenRequirementForScreenOrientationLockingEnabled true
#if ENABLE(MEDIA_STREAM)
#define DEFAULT_VALUE_FOR_GetUserMediaRequiresFocus true
#endif
#define DEFAULT_VALUE_FOR_ResizeObserverEnabled true
#define DEFAULT_VALUE_FOR_ResourceLoadSchedulingEnabled true
#if ENABLE(RESOURCE_USAGE)
#define DEFAULT_VALUE_FOR_ResourceUsageOverlayVisible false
#endif
#define DEFAULT_VALUE_FOR_SKAttributionEnabled true
#define DEFAULT_VALUE_FOR_SafeBrowsingEnabled true
#define DEFAULT_VALUE_FOR_IsSameSiteStrictEnforcementEnabled false
#define DEFAULT_VALUE_FOR_ScreenOrientationLockingAPIEnabled false
#define DEFAULT_VALUE_FOR_ScreenOrientationAPIEnabled WebKit::defaultShouldEnableScreenOrientationAPI()
#define DEFAULT_VALUE_FOR_ScreenWakeLockAPIEnabled true
#if ENABLE(MEDIA_STREAM)
#if PLATFORM(MAC) || USE(GSTREAMER)
#define DEFAULT_VALUE_FOR_ScreenCaptureEnabled true
#else
#define DEFAULT_VALUE_FOR_ScreenCaptureEnabled false
#endif
#endif
#define DEFAULT_VALUE_FOR_ScrollingPerformanceTestingEnabled false
#define DEFAULT_VALUE_FOR_ScrollToTextFragmentIndicatorEnabled true
#define DEFAULT_VALUE_FOR_ScrollToTextFragmentEnabled true
#if PLATFORM(MAC)
#define DEFAULT_VALUE_FOR_ScrollAnimatorEnabled WebKit::defaultScrollAnimatorEnabled()
#elif PLATFORM(GTK) || PLATFORM(WPE)
#define DEFAULT_VALUE_FOR_ScrollAnimatorEnabled true
#else
#define DEFAULT_VALUE_FOR_ScrollAnimatorEnabled false
#endif
#define DEFAULT_VALUE_FOR_SearchInputIncrementalAttributeAndSearchEventEnabled WebKit::defaultSearchInputIncrementalAttributeAndSearchEventEnabled()
#define DEFAULT_VALUE_FOR_SecureContextChecksEnabled true
#define DEFAULT_VALUE_FOR_SelectionAPIForShadowDOMEnabled true
#if PLATFORM(VISION)
#define DEFAULT_VALUE_FOR_SelectionFlippingEnabled false
#else
#define DEFAULT_VALUE_FOR_SelectionFlippingEnabled true
#endif
#define DEFAULT_VALUE_FOR_SendMouseEventsToDisabledFormControlsEnabled true
#define DEFAULT_VALUE_FOR_ServerTimingEnabled true
#if ENABLE(SERVICE_WORKER)
#define DEFAULT_VALUE_FOR_ServiceWorkerNavigationPreloadEnabled true
#endif
#if ENABLE(SERVICE_WORKER)
#define DEFAULT_VALUE_FOR_ServiceWorkersEnabled true
#endif
#define DEFAULT_VALUE_FOR_ShapeDetection false
#define DEFAULT_VALUE_FOR_SharedWorkerEnabled true
#define DEFAULT_VALUE_FOR_ShowMediaStatsContextMenuItemEnabled false
#define DEFAULT_VALUE_FOR_SiteIsolationEnabled false
#if HAVE(SPEECHRECOGNIZER) && ENABLE(MEDIA_STREAM)
#define DEFAULT_VALUE_FOR_SpeechRecognitionEnabled true
#else
#define DEFAULT_VALUE_FOR_SpeechRecognitionEnabled false
#endif
#define DEFAULT_VALUE_FOR_SpeechSynthesisAPIEnabled true
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_StorageAPIEstimateEnabled true
#else
#define DEFAULT_VALUE_FOR_StorageAPIEstimateEnabled false
#endif
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_StorageAPIEnabled true
#else
#define DEFAULT_VALUE_FOR_StorageAPIEnabled false
#endif
#define DEFAULT_VALUE_FOR_StorageAccessAPIEnabled true
#define DEFAULT_VALUE_FOR_StorageBlockingPolicy WebCore::StorageBlockingPolicy::BlockThirdParty
#if PLATFORM(PLAYSTATION)
#define DEFAULT_VALUE_FOR_ProcessSwapOnCrossSiteNavigationEnabled false
#else
#define DEFAULT_VALUE_FOR_ProcessSwapOnCrossSiteNavigationEnabled true
#endif
#define DEFAULT_VALUE_FOR_ProcessSwapOnCrossSiteWindowOpenEnabled false
#define DEFAULT_VALUE_FOR_SyntheticEditingCommandsEnabled true
#define DEFAULT_VALUE_FOR_ShouldTakeNearSuspendedAssertions true
#if ENABLE(IMAGE_ANALYSIS)
#define DEFAULT_VALUE_FOR_TextRecognitionInVideosEnabled defaultTextRecognitionInVideosEnabled()
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
#define DEFAULT_VALUE_FOR_ThreadedAnimationResolutionEnabled false
#endif
#define DEFAULT_VALUE_FOR_TiledScrollingIndicatorVisible false
#if ENABLE(INPUT_TYPE_TIME)
#if PLATFORM(APPLETV)
#define DEFAULT_VALUE_FOR_InputTypeTimeEnabled false
#else
#define DEFAULT_VALUE_FOR_InputTypeTimeEnabled true
#endif
#endif
#define DEFAULT_VALUE_FOR_TrackConfigurationEnabled false
#define DEFAULT_VALUE_FOR_TransformStreamAPIEnabled true
#define DEFAULT_VALUE_FOR_UndoManagerAPIEnabled false
#define DEFAULT_VALUE_FOR_UnprefixedFullscreenAPIEnabled true
#define DEFAULT_VALUE_FOR_UpgradeKnownHostsToHTTPSEnabled true
#if ENABLE(ARKIT_INLINE_PREVIEW)
#define DEFAULT_VALUE_FOR_UseARKitForModel true
#endif
#define DEFAULT_VALUE_FOR_UseGeneralDirectoryForStorage true
#if HAVE(SC_CONTENT_SHARING_PICKER)
#define DEFAULT_VALUE_FOR_UseSCContentSharingPicker WebKit::defaultUseSCContentSharingPicker()
#endif
#if HAVE(SCENEKIT)
#define DEFAULT_VALUE_FOR_UseSceneKitForModel false
#endif
#define DEFAULT_VALUE_FOR_UseGiantTiles false
#define DEFAULT_VALUE_FOR_UserActivationAPIEnabled true
#define DEFAULT_VALUE_FOR_UserGesturePromisePropagationEnabled true
#if ENABLE(VP9)
#define DEFAULT_VALUE_FOR_VP9SWDecoderEnabledOnBattery false
#endif
#if ENABLE(SERVICE_WORKER)
#define DEFAULT_VALUE_FOR_ServiceWorkersUserGestureEnabled true
#endif
#define DEFAULT_VALUE_FOR_VerifyWindowOpenUserGestureFromUIProcess false
#define DEFAULT_VALUE_FOR_VerticalFormControlsEnabled false
#define DEFAULT_VALUE_FOR_ViewGestureDebuggingEnabled false
#if ENABLE(IMAGE_ANALYSIS)
#define DEFAULT_VALUE_FOR_VisualTranslationEnabled defaultVisualTranslationEnabled()
#endif
#define DEFAULT_VALUE_FOR_VisualViewportAPIEnabled true
#if ENABLE(VORBIS)
#define DEFAULT_VALUE_FOR_VorbisDecoderEnabled true
#endif
#define DEFAULT_VALUE_FOR_WebAPIStatisticsEnabled false
#define DEFAULT_VALUE_FOR_WebAPIsInShadowRealmEnabled false
#define DEFAULT_VALUE_FOR_WebAnimationsCompositeOperationsEnabled true
#define DEFAULT_VALUE_FOR_WebAnimationsCustomEffectsEnabled false
#define DEFAULT_VALUE_FOR_WebAnimationsCustomFrameRateEnabled false
#define DEFAULT_VALUE_FOR_WebAnimationsIterationCompositeEnabled true
#define DEFAULT_VALUE_FOR_WebAnimationsMutableTimelinesEnabled true
#if ENABLE(WEB_ARCHIVE)
#define DEFAULT_VALUE_FOR_WebArchiveDebugModeEnabled false
#endif
#if ENABLE(WEB_ARCHIVE)
#define DEFAULT_VALUE_FOR_WebArchiveTestingModeEnabled false
#endif
#if ENABLE(WEB_AUTHN)
#define DEFAULT_VALUE_FOR_WebAuthenticationEnabled true
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK) || PLATFORM(WPE)
#define DEFAULT_VALUE_FOR_WebCryptoSafeCurvesEnabled true
#else
#define DEFAULT_VALUE_FOR_WebCryptoSafeCurvesEnabled false
#endif
#define DEFAULT_VALUE_FOR_WebLocksAPIEnabled true
#if PLATFORM(COCOA) && !PLATFORM(WATCHOS) && !PLATFORM(APPLETV)
#define DEFAULT_VALUE_FOR_WebShareFileAPIEnabled true
#else
#define DEFAULT_VALUE_FOR_WebShareFileAPIEnabled false
#endif
#if PLATFORM(COCOA) && !PLATFORM(WATCHOS) && !PLATFORM(APPLETV)
#define DEFAULT_VALUE_FOR_WebShareEnabled true
#else
#define DEFAULT_VALUE_FOR_WebShareEnabled false
#endif
#if ENABLE(WEBASSEMBLY)
#define DEFAULT_VALUE_FOR_WebAssemblyESMIntegrationEnabled false
#endif
#if ENABLE(WEB_CODECS)
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_WebCodecsEnabled true
#elif USE(GSTREAMER)
#define DEFAULT_VALUE_FOR_WebCodecsEnabled true
#else
#define DEFAULT_VALUE_FOR_WebCodecsEnabled false
#endif
#endif
#if ENABLE(WEB_CODECS)
#if USE(GSTREAMER)
#define DEFAULT_VALUE_FOR_WebCodecsAV1Enabled true
#else
#define DEFAULT_VALUE_FOR_WebCodecsAV1Enabled false
#endif
#endif
#if ENABLE(WEB_CODECS)
#if USE(GSTREAMER)
#define DEFAULT_VALUE_FOR_WebCodecsHEVCEnabled true
#else
#define DEFAULT_VALUE_FOR_WebCodecsHEVCEnabled false
#endif
#endif
#define DEFAULT_VALUE_FOR_WebGLDraftExtensionsEnabled false
#define DEFAULT_VALUE_FOR_WebGLTimerQueriesEnabled false
#if ENABLE(WEBGL) && PLATFORM(COCOA)
#if HAVE(WEBGL_COMPATIBLE_METAL)
#define DEFAULT_VALUE_FOR_WebGLUsingMetal true
#else
#define DEFAULT_VALUE_FOR_WebGLUsingMetal false
#endif
#endif
#define DEFAULT_VALUE_FOR_WebGLEnabled true
#if ENABLE(WEBGPU_BY_DEFAULT)
#define DEFAULT_VALUE_FOR_WebGPUEnabled true
#else
#define DEFAULT_VALUE_FOR_WebGPUEnabled false
#endif
#define DEFAULT_VALUE_FOR_WebInspectorEngineeringSettingsAllowed false
#if ENABLE(WEB_RTC)
#if USE(GSTREAMER)
#define DEFAULT_VALUE_FOR_WebRTCAV1CodecEnabled true
#else
#define DEFAULT_VALUE_FOR_WebRTCAV1CodecEnabled false
#endif
#endif
#define DEFAULT_VALUE_FOR_WebRTCAudioLatencyAdaptationEnabled true
#if ENABLE(WEB_RTC)
#define DEFAULT_VALUE_FOR_WebRTCDTMFEnabled true
#endif
#if ENABLE(WEB_RTC)
#if USE(LIBWEBRTC)
#define DEFAULT_VALUE_FOR_WebRTCEncodedTransformEnabled true
#else
#define DEFAULT_VALUE_FOR_WebRTCEncodedTransformEnabled false
#endif
#endif
#if ENABLE(WEB_RTC)
#define DEFAULT_VALUE_FOR_WebRTCH264HardwareEncoderEnabled true
#endif
#if ENABLE(WEB_RTC)
#define DEFAULT_VALUE_FOR_WebRTCH264LowLatencyEncoderEnabled true
#endif
#if ENABLE(WEB_RTC)
#define DEFAULT_VALUE_FOR_WebRTCH264SimulcastEnabled true
#endif
#if ENABLE(WEB_RTC)
#define DEFAULT_VALUE_FOR_WebRTCH265CodecEnabled false
#endif
#if USE(LIBWEBRTC)
#define DEFAULT_VALUE_FOR_WebRTCMediaPipelineAdditionalLoggingEnabled true
#endif
#if ENABLE(WEB_RTC)
#if USE(LIBWEBRTC)
#define DEFAULT_VALUE_FOR_PeerConnectionEnabled WebKit::defaultPeerConnectionEnabledAvailable()
#elif USE(GSTREAMER_WEBRTC)
#define DEFAULT_VALUE_FOR_PeerConnectionEnabled true
#else
#define DEFAULT_VALUE_FOR_PeerConnectionEnabled false
#endif
#endif
#if ENABLE(WEB_RTC)
#define DEFAULT_VALUE_FOR_WebRTCPlatformTCPSocketsEnabled true
#endif
#if ENABLE(WEB_RTC)
#define DEFAULT_VALUE_FOR_WebRTCPlatformUDPSocketsEnabled true
#endif
#if ENABLE(WEB_RTC)
#if PLATFORM(COCOA)
#define DEFAULT_VALUE_FOR_WebRTCRemoteVideoFrameEnabled true
#else
#define DEFAULT_VALUE_FOR_WebRTCRemoteVideoFrameEnabled false
#endif
#endif
#if ENABLE(WEB_RTC)
#define DEFAULT_VALUE_FOR_WebRTCSFrameTransformEnabled false
#endif
#if ENABLE(WEB_RTC)
#define DEFAULT_VALUE_FOR_WebRTCSocketsProxyingEnabled true
#endif
#if ENABLE(WEB_RTC)
#define DEFAULT_VALUE_FOR_WebRTCVP9Profile0CodecEnabled true
#endif
#if ENABLE(WEB_RTC)
#define DEFAULT_VALUE_FOR_WebRTCVP9Profile2CodecEnabled false
#endif
#if ENABLE(WEBXR)
#define DEFAULT_VALUE_FOR_WebXRAugmentedRealityModuleEnabled false
#endif
#if ENABLE(WEBXR)
#define DEFAULT_VALUE_FOR_WebXREnabled false
#endif
#if ENABLE(WEBXR)
#define DEFAULT_VALUE_FOR_WebXRGamepadsModuleEnabled false
#endif
#if ENABLE(WEBXR_HANDS)
#define DEFAULT_VALUE_FOR_WebXRHandInputModuleEnabled false
#endif
#if ENABLE(INPUT_TYPE_WEEK)
#if !PLATFORM(MAC) && !PLATFORM(APPLETV)
#define DEFAULT_VALUE_FOR_InputTypeWeekEnabled true
#else
#define DEFAULT_VALUE_FOR_InputTypeWeekEnabled false
#endif
#endif
#if PLATFORM(MAC)
#define DEFAULT_VALUE_FOR_WheelEventGesturesBecomeNonBlocking WebKit::defaultWheelEventGesturesBecomeNonBlocking()
#else
#define DEFAULT_VALUE_FOR_WheelEventGesturesBecomeNonBlocking true
#endif
#if PLATFORM(MAC)
#define DEFAULT_VALUE_FOR_PassiveWheelListenersAsDefaultOnDocument WebKit::defaultPassiveWheelListenersAsDefaultOnDocument()
#else
#define DEFAULT_VALUE_FOR_PassiveWheelListenersAsDefaultOnDocument true
#endif
#define DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled false
#define DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalReproTestingEnabled false
#if ENABLE(INPUT_TYPE_DATETIMELOCAL)
#if PLATFORM(APPLETV)
#define DEFAULT_VALUE_FOR_InputTypeDateTimeLocalEnabled false
#else
#define DEFAULT_VALUE_FOR_InputTypeDateTimeLocalEnabled true
#endif
#endif
#define DEFAULT_VALUE_FOR_HTTPEquivEnabled true
#if ENABLE(IOS_FORM_CONTROL_REFRESH)
#define DEFAULT_VALUE_FOR_IOSFormControlRefreshEnabled true
#endif
#define DEFAULT_VALUE_FOR_LineHeightUnitsEnabled true
#define DEFAULT_VALUE_FOR_RequestIdleCallbackEnabled false
#define DEFAULT_VALUE_FOR_CSSWordBreakAutoEnabled false

// macro(KeyUpper, KeyLower, TypeNameUpper, TypeName, DefaultValue, HumanReadableName, HumanReadableDescription)

#define FOR_EACH_WEBKIT_PREFERENCE(macro) \
    macro(AcceleratedCompositingEnabled, acceleratedCompositingEnabled, Bool, bool, DEFAULT_VALUE_FOR_AcceleratedCompositingEnabled, "", "") \
    macro(AcceleratedCompositingForFixedPositionEnabled, acceleratedCompositingForFixedPositionEnabled, Bool, bool, DEFAULT_VALUE_FOR_AcceleratedCompositingForFixedPositionEnabled, "", "") \
    macro(AggressiveTileRetentionEnabled, aggressiveTileRetentionEnabled, Bool, bool, DEFAULT_VALUE_FOR_AggressiveTileRetentionEnabled, "", "") \
    macro(AllowContentSecurityPolicySourceStarToMatchAnyProtocol, allowContentSecurityPolicySourceStarToMatchAnyProtocol, Bool, bool, DEFAULT_VALUE_FOR_AllowContentSecurityPolicySourceStarToMatchAnyProtocol, "", "") \
    macro(AllowCrossOriginSubresourcesToAskForCredentials, allowCrossOriginSubresourcesToAskForCredentials, Bool, bool, DEFAULT_VALUE_FOR_AllowCrossOriginSubresourcesToAskForCredentials, "", "") \
    macro(AllowDisplayOfInsecureContent, allowDisplayOfInsecureContent, Bool, bool, DEFAULT_VALUE_FOR_AllowDisplayOfInsecureContent, "", "") \
    macro(AllowFileAccessFromFileURLs, allowFileAccessFromFileURLs, Bool, bool, DEFAULT_VALUE_FOR_AllowFileAccessFromFileURLs, "", "") \
    macro(AllowMultiElementImplicitSubmission, allowMultiElementImplicitSubmission, Bool, bool, DEFAULT_VALUE_FOR_AllowMultiElementImplicitSubmission, "", "") \
    macro(AllowRunningOfInsecureContent, allowRunningOfInsecureContent, Bool, bool, DEFAULT_VALUE_FOR_AllowRunningOfInsecureContent, "", "") \
    macro(AllowSettingAnyXHRHeaderFromFileURLs, allowSettingAnyXHRHeaderFromFileURLs, Bool, bool, DEFAULT_VALUE_FOR_AllowSettingAnyXHRHeaderFromFileURLs, "", "") \
    macro(AllowsAirPlayForMediaPlayback, allowsAirPlayForMediaPlayback, Bool, bool, DEFAULT_VALUE_FOR_AllowsAirPlayForMediaPlayback, "", "") \
    macro(AllowsInlineMediaPlayback, allowsInlineMediaPlayback, Bool, bool, DEFAULT_VALUE_FOR_AllowsInlineMediaPlayback, "", "") \
    macro(AllowsInlineMediaPlaybackAfterFullscreen, allowsInlineMediaPlaybackAfterFullscreen, Bool, bool, DEFAULT_VALUE_FOR_AllowsInlineMediaPlaybackAfterFullscreen, "", "") \
    macro(AllowsPictureInPictureMediaPlayback, allowsPictureInPictureMediaPlayback, Bool, bool, DEFAULT_VALUE_FOR_AllowsPictureInPictureMediaPlayback, "", "") \
    macro(AlternateFormControlDesignEnabled, alternateFormControlDesignEnabled, Bool, bool, DEFAULT_VALUE_FOR_AlternateFormControlDesignEnabled, "", "") \
    macro(AlternateFullScreenControlDesignEnabled, alternateFullScreenControlDesignEnabled, Bool, bool, DEFAULT_VALUE_FOR_AlternateFullScreenControlDesignEnabled, "", "") \
    macro(AnimatedImageAsyncDecodingEnabled, animatedImageAsyncDecodingEnabled, Bool, bool, DEFAULT_VALUE_FOR_AnimatedImageAsyncDecodingEnabled, "", "") \
    macro(AppleMailPaginationQuirkEnabled, appleMailPaginationQuirkEnabled, Bool, bool, DEFAULT_VALUE_FOR_AppleMailPaginationQuirkEnabled, "", "") \
    macro(ApplePayCapabilityDisclosureAllowed, applePayCapabilityDisclosureAllowed, Bool, bool, DEFAULT_VALUE_FOR_ApplePayCapabilityDisclosureAllowed, "", "") \
    macro(ApplePayEnabled, applePayEnabled, Bool, bool, DEFAULT_VALUE_FOR_ApplePayEnabled, "", "") \
    macro(AsynchronousSpellCheckingEnabled, asynchronousSpellCheckingEnabled, Bool, bool, DEFAULT_VALUE_FOR_AsynchronousSpellCheckingEnabled, "", "") \
    macro(AudioControlsScaleWithPageZoom, audioControlsScaleWithPageZoom, Bool, bool, DEFAULT_VALUE_FOR_AudioControlsScaleWithPageZoom, "", "") \
    macro(AuthorAndUserStylesEnabled, authorAndUserStylesEnabled, Bool, bool, DEFAULT_VALUE_FOR_AuthorAndUserStylesEnabled, "", "") \
    macro(BackspaceKeyNavigationEnabled, backspaceKeyNavigationEnabled, Bool, bool, DEFAULT_VALUE_FOR_BackspaceKeyNavigationEnabled, "", "") \
    macro(CaretBrowsingEnabled, caretBrowsingEnabled, Bool, bool, DEFAULT_VALUE_FOR_CaretBrowsingEnabled, "", "") \
    macro(ColorFilterEnabled, colorFilterEnabled, Bool, bool, DEFAULT_VALUE_FOR_ColorFilterEnabled, "", "") \
    macro(ConstantPropertiesEnabled, constantPropertiesEnabled, Bool, bool, DEFAULT_VALUE_FOR_ConstantPropertiesEnabled, "", "") \
    macro(ContentChangeObserverEnabled, contentChangeObserverEnabled, Bool, bool, DEFAULT_VALUE_FOR_ContentChangeObserverEnabled, "", "") \
    macro(ContentDispositionAttachmentSandboxEnabled, contentDispositionAttachmentSandboxEnabled, Bool, bool, DEFAULT_VALUE_FOR_ContentDispositionAttachmentSandboxEnabled, "", "") \
    macro(ContextMenuQRCodeDetectionEnabled, contextMenuQRCodeDetectionEnabled, Bool, bool, DEFAULT_VALUE_FOR_ContextMenuQRCodeDetectionEnabled, "", "") \
    macro(CursiveFontFamily, cursiveFontFamily, String, String, DEFAULT_VALUE_FOR_CursiveFontFamily, "", "") \
    macro(DNSPrefetchingEnabled, dnsPrefetchingEnabled, Bool, bool, DEFAULT_VALUE_FOR_DNSPrefetchingEnabled, "", "") \
    macro(DOMPasteAllowed, domPasteAllowed, Bool, bool, DEFAULT_VALUE_FOR_DOMPasteAllowed, "", "") \
    macro(DataDetectorTypes, dataDetectorTypes, UInt32, uint32_t, DEFAULT_VALUE_FOR_DataDetectorTypes, "", "") \
    macro(DatabasesEnabled, databasesEnabled, Bool, bool, DEFAULT_VALUE_FOR_DatabasesEnabled, "", "") \
    macro(DefaultFixedFontSize, defaultFixedFontSize, Double, double, DEFAULT_VALUE_FOR_DefaultFixedFontSize, "", "") \
    macro(DefaultFontSize, defaultFontSize, Double, double, DEFAULT_VALUE_FOR_DefaultFontSize, "", "") \
    macro(DefaultTextEncodingName, defaultTextEncodingName, String, String, DEFAULT_VALUE_FOR_DefaultTextEncodingName, "", "") \
    macro(DeveloperExtrasEnabled, developerExtrasEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeveloperExtrasEnabled, "", "") \
    macro(DeviceHeight, deviceHeight, UInt32, uint32_t, DEFAULT_VALUE_FOR_DeviceHeight, "", "") \
    macro(DeviceOrientationEventEnabled, deviceOrientationEventEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeviceOrientationEventEnabled, "", "") \
    macro(DeviceOrientationPermissionAPIEnabled, deviceOrientationPermissionAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeviceOrientationPermissionAPIEnabled, "", "") \
    macro(DeviceWidth, deviceWidth, UInt32, uint32_t, DEFAULT_VALUE_FOR_DeviceWidth, "", "") \
    macro(DisabledAdaptationsMetaTagEnabled, disabledAdaptationsMetaTagEnabled, Bool, bool, DEFAULT_VALUE_FOR_DisabledAdaptationsMetaTagEnabled, "", "") \
    macro(DownloadAttributeEnabled, downloadAttributeEnabled, Bool, bool, DEFAULT_VALUE_FOR_DownloadAttributeEnabled, "", "") \
    macro(EditableLinkBehavior, editableLinkBehavior, UInt32, uint32_t, DEFAULT_VALUE_FOR_EditableLinkBehavior, "", "") \
    macro(EnableInheritURIQueryComponent, enableInheritURIQueryComponent, Bool, bool, DEFAULT_VALUE_FOR_EnableInheritURIQueryComponent, "", "") \
    macro(EncryptedMediaAPIEnabled, encryptedMediaAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_EncryptedMediaAPIEnabled, "", "") \
    macro(ExtensibleSSOEnabled, isExtensibleSSOEnabled, Bool, bool, DEFAULT_VALUE_FOR_ExtensibleSSOEnabled, "", "") \
    macro(FTPDirectoryTemplatePath, ftpDirectoryTemplatePath, String, String, DEFAULT_VALUE_FOR_FTPDirectoryTemplatePath, "", "") \
    macro(FantasyFontFamily, fantasyFontFamily, String, String, DEFAULT_VALUE_FOR_FantasyFontFamily, "", "") \
    macro(FixedFontFamily, fixedFontFamily, String, String, DEFAULT_VALUE_FOR_FixedFontFamily, "", "") \
    macro(ForceCompositingMode, forceCompositingMode, Bool, bool, DEFAULT_VALUE_FOR_ForceCompositingMode, "", "") \
    macro(ForceFTPDirectoryListings, forceFTPDirectoryListings, Bool, bool, DEFAULT_VALUE_FOR_ForceFTPDirectoryListings, "", "") \
    macro(ForceWebGLUsesLowPower, forceWebGLUsesLowPower, Bool, bool, DEFAULT_VALUE_FOR_ForceWebGLUsesLowPower, "", "") \
    macro(GStreamerEnabled, isGStreamerEnabled, Bool, bool, DEFAULT_VALUE_FOR_GStreamerEnabled, "", "") \
    macro(HiddenPageCSSAnimationSuspensionEnabled, hiddenPageCSSAnimationSuspensionEnabled, Bool, bool, DEFAULT_VALUE_FOR_HiddenPageCSSAnimationSuspensionEnabled, "", "") \
    macro(InactiveMediaCaptureSteamRepromptIntervalInMinutes, inactiveMediaCaptureSteamRepromptIntervalInMinutes, Double, double, DEFAULT_VALUE_FOR_InactiveMediaCaptureSteamRepromptIntervalInMinutes, "", "") \
    macro(IncompleteImageBorderEnabled, incompleteImageBorderEnabled, Bool, bool, DEFAULT_VALUE_FOR_IncompleteImageBorderEnabled, "", "") \
    macro(IncrementalPDFLoadingEnabled, incrementalPDFLoadingEnabled, Bool, bool, DEFAULT_VALUE_FOR_IncrementalPDFLoadingEnabled, "", "") \
    macro(IncrementalRenderingSuppressionTimeout, incrementalRenderingSuppressionTimeout, Double, double, DEFAULT_VALUE_FOR_IncrementalRenderingSuppressionTimeout, "", "") \
    macro(InlineMediaPlaybackRequiresPlaysInlineAttribute, inlineMediaPlaybackRequiresPlaysInlineAttribute, Bool, bool, DEFAULT_VALUE_FOR_InlineMediaPlaybackRequiresPlaysInlineAttribute, "", "") \
    macro(InspectorAttachedHeight, inspectorAttachedHeight, UInt32, uint32_t, DEFAULT_VALUE_FOR_InspectorAttachedHeight, "", "") \
    macro(InspectorAttachedWidth, inspectorAttachedWidth, UInt32, uint32_t, DEFAULT_VALUE_FOR_InspectorAttachedWidth, "", "") \
    macro(InspectorAttachmentSide, inspectorAttachmentSide, UInt32, uint32_t, DEFAULT_VALUE_FOR_InspectorAttachmentSide, "", "") \
    macro(InspectorStartsAttached, inspectorStartsAttached, Bool, bool, DEFAULT_VALUE_FOR_InspectorStartsAttached, "", "") \
    macro(InspectorWindowFrame, inspectorWindowFrame, String, String, DEFAULT_VALUE_FOR_InspectorWindowFrame, "", "") \
    macro(InteractionRegionInlinePadding, interactionRegionInlinePadding, Double, double, DEFAULT_VALUE_FOR_InteractionRegionInlinePadding, "", "") \
    macro(InteractionRegionMinimumCornerRadius, interactionRegionMinimumCornerRadius, Double, double, DEFAULT_VALUE_FOR_InteractionRegionMinimumCornerRadius, "", "") \
    macro(InterruptAudioOnPageVisibilityChangeEnabled, interruptAudioOnPageVisibilityChangeEnabled, Bool, bool, DEFAULT_VALUE_FOR_InterruptAudioOnPageVisibilityChangeEnabled, "", "") \
    macro(InterruptVideoOnPageVisibilityChangeEnabled, interruptVideoOnPageVisibilityChangeEnabled, Bool, bool, DEFAULT_VALUE_FOR_InterruptVideoOnPageVisibilityChangeEnabled, "", "") \
    macro(InvisibleAutoplayNotPermitted, invisibleAutoplayNotPermitted, Bool, bool, DEFAULT_VALUE_FOR_InvisibleAutoplayNotPermitted, "", "") \
    macro(JavaScriptCanAccessClipboard, javaScriptCanAccessClipboard, Bool, bool, DEFAULT_VALUE_FOR_JavaScriptCanAccessClipboard, "", "") \
    macro(JavaScriptCanOpenWindowsAutomatically, javaScriptCanOpenWindowsAutomatically, Bool, bool, DEFAULT_VALUE_FOR_JavaScriptCanOpenWindowsAutomatically, "", "") \
    macro(JavaScriptMarkupEnabled, javaScriptMarkupEnabled, Bool, bool, DEFAULT_VALUE_FOR_JavaScriptMarkupEnabled, "", "") \
    macro(JavaScriptRuntimeFlags, javaScriptRuntimeFlags, UInt32, uint32_t, DEFAULT_VALUE_FOR_JavaScriptRuntimeFlags, "", "") \
    macro(LargeImageAsyncDecodingEnabled, largeImageAsyncDecodingEnabled, Bool, bool, DEFAULT_VALUE_FOR_LargeImageAsyncDecodingEnabled, "", "") \
    macro(LayoutFallbackWidth, layoutFallbackWidth, UInt32, uint32_t, DEFAULT_VALUE_FOR_LayoutFallbackWidth, "", "") \
    macro(LayoutViewportHeightExpansionFactor, layoutViewportHeightExpansionFactor, Double, double, DEFAULT_VALUE_FOR_LayoutViewportHeightExpansionFactor, "", "") \
    macro(LinkPreconnect, linkPreconnect, Bool, bool, DEFAULT_VALUE_FOR_LinkPreconnect, "", "") \
    macro(LinkPreloadEnabled, linkPreloadEnabled, Bool, bool, DEFAULT_VALUE_FOR_LinkPreloadEnabled, "", "") \
    macro(LoadDeferringEnabled, loadDeferringEnabled, Bool, bool, DEFAULT_VALUE_FOR_LoadDeferringEnabled, "", "") \
    macro(LoadsImagesAutomatically, loadsImagesAutomatically, Bool, bool, DEFAULT_VALUE_FOR_LoadsImagesAutomatically, "", "") \
    macro(LongRunningMediaCaptureStreamRepromptIntervalInHours, longRunningMediaCaptureStreamRepromptIntervalInHours, Double, double, DEFAULT_VALUE_FOR_LongRunningMediaCaptureStreamRepromptIntervalInHours, "", "") \
    macro(LowPowerVideoAudioBufferSizeEnabled, lowPowerVideoAudioBufferSizeEnabled, Bool, bool, DEFAULT_VALUE_FOR_LowPowerVideoAudioBufferSizeEnabled, "", "") \
    macro(ManagedMediaSourceHighThreshold, managedMediaSourceHighThreshold, Double, double, DEFAULT_VALUE_FOR_ManagedMediaSourceHighThreshold, "", "") \
    macro(ManagedMediaSourceLowThreshold, managedMediaSourceLowThreshold, Double, double, DEFAULT_VALUE_FOR_ManagedMediaSourceLowThreshold, "", "") \
    macro(MathMLEnabled, mathMLEnabled, Bool, bool, DEFAULT_VALUE_FOR_MathMLEnabled, "", "") \
    macro(MaxParseDuration, maxParseDuration, Double, double, DEFAULT_VALUE_FOR_MaxParseDuration, "", "") \
    macro(MediaAudioCodecIDsAllowedInLockdownMode, mediaAudioCodecIDsAllowedInLockdownMode, String, String, DEFAULT_VALUE_FOR_MediaAudioCodecIDsAllowedInLockdownMode, "", "") \
    macro(MediaCapabilitiesEnabled, mediaCapabilitiesEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaCapabilitiesEnabled, "", "") \
    macro(MediaCaptionFormatTypesAllowedInLockdownMode, mediaCaptionFormatTypesAllowedInLockdownMode, String, String, DEFAULT_VALUE_FOR_MediaCaptionFormatTypesAllowedInLockdownMode, "", "") \
    macro(MediaCodecTypesAllowedInLockdownMode, mediaCodecTypesAllowedInLockdownMode, String, String, DEFAULT_VALUE_FOR_MediaCodecTypesAllowedInLockdownMode, "", "") \
    macro(MediaContainerTypesAllowedInLockdownMode, mediaContainerTypesAllowedInLockdownMode, String, String, DEFAULT_VALUE_FOR_MediaContainerTypesAllowedInLockdownMode, "", "") \
    macro(MediaContentTypesRequiringHardwareSupport, mediaContentTypesRequiringHardwareSupport, String, String, DEFAULT_VALUE_FOR_MediaContentTypesRequiringHardwareSupport, "", "") \
    macro(MediaControlsContextMenusEnabled, mediaControlsContextMenusEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaControlsContextMenusEnabled, "", "") \
    macro(MediaControlsScaleWithPageZoom, mediaControlsScaleWithPageZoom, Bool, bool, DEFAULT_VALUE_FOR_MediaControlsScaleWithPageZoom, "", "") \
    macro(MediaDataLoadsAutomatically, mediaDataLoadsAutomatically, Bool, bool, DEFAULT_VALUE_FOR_MediaDataLoadsAutomatically, "", "") \
    macro(MediaEnabled, mediaEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaEnabled, "", "") \
    macro(MediaPreferredFullscreenWidth, mediaPreferredFullscreenWidth, Double, double, DEFAULT_VALUE_FOR_MediaPreferredFullscreenWidth, "", "") \
    macro(MediaPreloadingEnabled, mediaPreloadingEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaPreloadingEnabled, "", "") \
    macro(MediaStreamEnabled, mediaStreamEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaStreamEnabled, "", "") \
    macro(MediaUserGestureInheritsFromDocument, mediaUserGestureInheritsFromDocument, Bool, bool, DEFAULT_VALUE_FOR_MediaUserGestureInheritsFromDocument, "", "") \
    macro(MediaVideoCodecIDsAllowedInLockdownMode, mediaVideoCodecIDsAllowedInLockdownMode, String, String, DEFAULT_VALUE_FOR_MediaVideoCodecIDsAllowedInLockdownMode, "", "") \
    macro(MenuItemElementEnabled, menuItemElementEnabled, Bool, bool, DEFAULT_VALUE_FOR_MenuItemElementEnabled, "", "") \
    macro(MinimumFontSize, minimumFontSize, Double, double, DEFAULT_VALUE_FOR_MinimumFontSize, "", "") \
    macro(MinimumLogicalFontSize, minimumLogicalFontSize, Double, double, DEFAULT_VALUE_FOR_MinimumLogicalFontSize, "", "") \
    macro(MinimumZoomFontSize, minimumZoomFontSize, Double, double, DEFAULT_VALUE_FOR_MinimumZoomFontSize, "", "") \
    macro(MockCaptureDevicesPromptEnabled, mockCaptureDevicesPromptEnabled, Bool, bool, DEFAULT_VALUE_FOR_MockCaptureDevicesPromptEnabled, "", "") \
    macro(MockScrollbarsControllerEnabled, mockScrollbarsControllerEnabled, Bool, bool, DEFAULT_VALUE_FOR_MockScrollbarsControllerEnabled, "", "") \
    macro(MockScrollbarsEnabled, mockScrollbarsEnabled, Bool, bool, DEFAULT_VALUE_FOR_MockScrollbarsEnabled, "", "") \
    macro(NeedsAdobeFrameReloadingQuirk, needsAdobeFrameReloadingQuirk, Bool, bool, DEFAULT_VALUE_FOR_NeedsAdobeFrameReloadingQuirk, "", "") \
    macro(NeedsFrameNameFallbackToIdQuirk, needsFrameNameFallbackToIdQuirk, Bool, bool, DEFAULT_VALUE_FOR_NeedsFrameNameFallbackToIdQuirk, "", "") \
    macro(NeedsKeyboardEventDisambiguationQuirks, needsKeyboardEventDisambiguationQuirks, Bool, bool, DEFAULT_VALUE_FOR_NeedsKeyboardEventDisambiguationQuirks, "", "") \
    macro(OfflineWebApplicationCacheEnabled, offlineWebApplicationCacheEnabled, Bool, bool, DEFAULT_VALUE_FOR_OfflineWebApplicationCacheEnabled, "", "") \
    macro(PDFPluginEnabled, pdfPluginEnabled, Bool, bool, DEFAULT_VALUE_FOR_PDFPluginEnabled, "", "") \
    macro(PassiveTouchListenersAsDefaultOnDocument, passiveTouchListenersAsDefaultOnDocument, Bool, bool, DEFAULT_VALUE_FOR_PassiveTouchListenersAsDefaultOnDocument, "", "") \
    macro(PasswordEchoDuration, passwordEchoDuration, Double, double, DEFAULT_VALUE_FOR_PasswordEchoDuration, "", "") \
    macro(PasswordEchoEnabled, passwordEchoEnabled, Bool, bool, DEFAULT_VALUE_FOR_PasswordEchoEnabled, "", "") \
    macro(PictographFontFamily, pictographFontFamily, String, String, DEFAULT_VALUE_FOR_PictographFontFamily, "", "") \
    macro(PictureInPictureAPIEnabled, pictureInPictureAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_PictureInPictureAPIEnabled, "", "") \
    macro(PitchCorrectionAlgorithm, pitchCorrectionAlgorithm, UInt32, uint32_t, DEFAULT_VALUE_FOR_PitchCorrectionAlgorithm, "", "") \
    macro(PluginsEnabled, pluginsEnabled, Bool, bool, DEFAULT_VALUE_FOR_PluginsEnabled, "", "") \
    macro(PunchOutWhiteBackgroundsInDarkMode, punchOutWhiteBackgroundsInDarkMode, Bool, bool, DEFAULT_VALUE_FOR_PunchOutWhiteBackgroundsInDarkMode, "", "") \
    macro(RequiresPageVisibilityToPlayAudio, requiresPageVisibilityToPlayAudio, Bool, bool, DEFAULT_VALUE_FOR_RequiresPageVisibilityToPlayAudio, "", "") \
    macro(RequiresUserGestureForAudioPlayback, requiresUserGestureForAudioPlayback, Bool, bool, DEFAULT_VALUE_FOR_RequiresUserGestureForAudioPlayback, "", "") \
    macro(RequiresUserGestureForMediaPlayback, requiresUserGestureForMediaPlayback, Bool, bool, DEFAULT_VALUE_FOR_RequiresUserGestureForMediaPlayback, "", "") \
    macro(RequiresUserGestureForVideoPlayback, requiresUserGestureForVideoPlayback, Bool, bool, DEFAULT_VALUE_FOR_RequiresUserGestureForVideoPlayback, "", "") \
    macro(RequiresUserGestureToLoadVideo, requiresUserGestureToLoadVideo, Bool, bool, DEFAULT_VALUE_FOR_RequiresUserGestureToLoadVideo, "", "") \
    macro(RubberBandingForSubScrollableRegionsEnabled, rubberBandingForSubScrollableRegionsEnabled, Bool, bool, DEFAULT_VALUE_FOR_RubberBandingForSubScrollableRegionsEnabled, "", "") \
    macro(SampledPageTopColorMaxDifference, sampledPageTopColorMaxDifference, Double, double, DEFAULT_VALUE_FOR_SampledPageTopColorMaxDifference, "", "") \
    macro(SampledPageTopColorMinHeight, sampledPageTopColorMinHeight, Double, double, DEFAULT_VALUE_FOR_SampledPageTopColorMinHeight, "", "") \
    macro(SansSerifFontFamily, sansSerifFontFamily, String, String, DEFAULT_VALUE_FOR_SansSerifFontFamily, "", "") \
    macro(SelectTrailingWhitespaceEnabled, selectTrailingWhitespaceEnabled, Bool, bool, DEFAULT_VALUE_FOR_SelectTrailingWhitespaceEnabled, "", "") \
    macro(SerifFontFamily, serifFontFamily, String, String, DEFAULT_VALUE_FOR_SerifFontFamily, "", "") \
    macro(ServiceControlsEnabled, serviceControlsEnabled, Bool, bool, DEFAULT_VALUE_FOR_ServiceControlsEnabled, "", "") \
    macro(ServiceWorkerEntitlementDisabledForTesting, serviceWorkerEntitlementDisabledForTesting, Bool, bool, DEFAULT_VALUE_FOR_ServiceWorkerEntitlementDisabledForTesting, "", "") \
    macro(ShouldAllowUserInstalledFonts, shouldAllowUserInstalledFonts, Bool, bool, DEFAULT_VALUE_FOR_ShouldAllowUserInstalledFonts, "", "") \
    macro(ShouldConvertInvalidURLsToBlank, shouldConvertInvalidURLsToBlank, Bool, bool, DEFAULT_VALUE_FOR_ShouldConvertInvalidURLsToBlank, "", "") \
    macro(ShouldConvertPositionStyleOnCopy, shouldConvertPositionStyleOnCopy, Bool, bool, DEFAULT_VALUE_FOR_ShouldConvertPositionStyleOnCopy, "", "") \
    macro(ShouldDecidePolicyBeforeLoadingQuickLookPreview, shouldDecidePolicyBeforeLoadingQuickLookPreview, Bool, bool, DEFAULT_VALUE_FOR_ShouldDecidePolicyBeforeLoadingQuickLookPreview, "", "") \
    macro(ShouldDisplayCaptions, shouldDisplayCaptions, Bool, bool, DEFAULT_VALUE_FOR_ShouldDisplayCaptions, "", "") \
    macro(ShouldDisplaySubtitles, shouldDisplaySubtitles, Bool, bool, DEFAULT_VALUE_FOR_ShouldDisplaySubtitles, "", "") \
    macro(ShouldDisplayTextDescriptions, shouldDisplayTextDescriptions, Bool, bool, DEFAULT_VALUE_FOR_ShouldDisplayTextDescriptions, "", "") \
    macro(ShouldEnableTextAutosizingBoost, shouldEnableTextAutosizingBoost, Bool, bool, DEFAULT_VALUE_FOR_ShouldEnableTextAutosizingBoost, "", "") \
    macro(ShouldIgnoreMetaViewport, shouldIgnoreMetaViewport, Bool, bool, DEFAULT_VALUE_FOR_ShouldIgnoreMetaViewport, "", "") \
    macro(ShouldPrintBackgrounds, shouldPrintBackgrounds, Bool, bool, DEFAULT_VALUE_FOR_ShouldPrintBackgrounds, "", "") \
    macro(ShouldRespectImageOrientation, shouldRespectImageOrientation, Bool, bool, DEFAULT_VALUE_FOR_ShouldRespectImageOrientation, "", "") \
    macro(ShouldRestrictBaseURLSchemes, shouldRestrictBaseURLSchemes, Bool, bool, DEFAULT_VALUE_FOR_ShouldRestrictBaseURLSchemes, "", "") \
    macro(ShouldSuppressTextInputFromEditingDuringProvisionalNavigation, shouldSuppressTextInputFromEditingDuringProvisionalNavigation, Bool, bool, DEFAULT_VALUE_FOR_ShouldSuppressTextInputFromEditingDuringProvisionalNavigation, "", "") \
    macro(ShouldUseServiceWorkerShortTimeout, shouldUseServiceWorkerShortTimeout, Bool, bool, DEFAULT_VALUE_FOR_ShouldUseServiceWorkerShortTimeout, "", "") \
    macro(ShowsToolTipOverTruncatedText, showsToolTipOverTruncatedText, Bool, bool, DEFAULT_VALUE_FOR_ShowsToolTipOverTruncatedText, "", "") \
    macro(ShowsURLsInToolTipsEnabled, showsURLsInToolTipsEnabled, Bool, bool, DEFAULT_VALUE_FOR_ShowsURLsInToolTipsEnabled, "", "") \
    macro(ShrinksStandaloneImagesToFit, shrinksStandaloneImagesToFit, Bool, bool, DEFAULT_VALUE_FOR_ShrinksStandaloneImagesToFit, "", "") \
    macro(SmartInsertDeleteEnabled, smartInsertDeleteEnabled, Bool, bool, DEFAULT_VALUE_FOR_SmartInsertDeleteEnabled, "", "") \
    macro(SourceBufferChangeTypeEnabled, sourceBufferChangeTypeEnabled, Bool, bool, DEFAULT_VALUE_FOR_SourceBufferChangeTypeEnabled, "", "") \
    macro(SpatialNavigationEnabled, spatialNavigationEnabled, Bool, bool, DEFAULT_VALUE_FOR_SpatialNavigationEnabled, "", "") \
    macro(Standalone, standalone, Bool, bool, DEFAULT_VALUE_FOR_Standalone, "", "") \
    macro(StandardFontFamily, standardFontFamily, String, String, DEFAULT_VALUE_FOR_StandardFontFamily, "", "") \
    macro(SuppressesIncrementalRendering, suppressesIncrementalRendering, Bool, bool, DEFAULT_VALUE_FOR_SuppressesIncrementalRendering, "", "") \
    macro(SystemLayoutDirection, systemLayoutDirection, UInt32, uint32_t, DEFAULT_VALUE_FOR_SystemLayoutDirection, "", "") \
    macro(SystemPreviewEnabled, systemPreviewEnabled, Bool, bool, DEFAULT_VALUE_FOR_SystemPreviewEnabled, "", "") \
    macro(TabsToLinks, tabsToLinks, Bool, bool, DEFAULT_VALUE_FOR_TabsToLinks, "", "") \
    macro(TelephoneNumberParsingEnabled, telephoneNumberParsingEnabled, Bool, bool, DEFAULT_VALUE_FOR_TelephoneNumberParsingEnabled, "", "") \
    macro(TemporaryTileCohortRetentionEnabled, temporaryTileCohortRetentionEnabled, Bool, bool, DEFAULT_VALUE_FOR_TemporaryTileCohortRetentionEnabled, "", "") \
    macro(TextAreasAreResizable, textAreasAreResizable, Bool, bool, DEFAULT_VALUE_FOR_TextAreasAreResizable, "", "") \
    macro(TextAutosizingEnabled, textAutosizingEnabled, Bool, bool, DEFAULT_VALUE_FOR_TextAutosizingEnabled, "", "") \
    macro(TextInteractionEnabled, textInteractionEnabled, Bool, bool, DEFAULT_VALUE_FOR_TextInteractionEnabled, "", "") \
    macro(ThreadedScrollingEnabled, threadedScrollingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ThreadedScrollingEnabled, "", "") \
    macro(TreatsAnyTextCSSLinkAsStylesheet, treatsAnyTextCSSLinkAsStylesheet, Bool, bool, DEFAULT_VALUE_FOR_TreatsAnyTextCSSLinkAsStylesheet, "", "") \
    macro(UseImageDocumentForSubframePDF, useImageDocumentForSubframePDF, Bool, bool, DEFAULT_VALUE_FOR_UseImageDocumentForSubframePDF, "", "") \
    macro(UseLegacyBackgroundSizeShorthandBehavior, useLegacyBackgroundSizeShorthandBehavior, Bool, bool, DEFAULT_VALUE_FOR_UseLegacyBackgroundSizeShorthandBehavior, "", "") \
    macro(UsePreHTML5ParserQuirks, usePreHTML5ParserQuirks, Bool, bool, DEFAULT_VALUE_FOR_UsePreHTML5ParserQuirks, "", "") \
    macro(UserInterfaceDirectionPolicy, userInterfaceDirectionPolicy, UInt32, uint32_t, DEFAULT_VALUE_FOR_UserInterfaceDirectionPolicy, "", "") \
    macro(UsesBackForwardCache, usesBackForwardCache, Bool, bool, DEFAULT_VALUE_FOR_UsesBackForwardCache, "", "") \
    macro(UsesEncodingDetector, usesEncodingDetector, Bool, bool, DEFAULT_VALUE_FOR_UsesEncodingDetector, "", "") \
    macro(VP8DecoderEnabled, vp8DecoderEnabled, Bool, bool, DEFAULT_VALUE_FOR_VP8DecoderEnabled, "", "") \
    macro(VP9DecoderEnabled, vp9DecoderEnabled, Bool, bool, DEFAULT_VALUE_FOR_VP9DecoderEnabled, "", "") \
    macro(VideoFullscreenRequiresElementFullscreen, videoFullscreenRequiresElementFullscreen, Bool, bool, DEFAULT_VALUE_FOR_VideoFullscreenRequiresElementFullscreen, "", "") \
    macro(VideoPresentationModeAPIEnabled, videoPresentationModeAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_VideoPresentationModeAPIEnabled, "", "") \
    macro(VideoQualityIncludesDisplayCompositingEnabled, videoQualityIncludesDisplayCompositingEnabled, Bool, bool, DEFAULT_VALUE_FOR_VideoQualityIncludesDisplayCompositingEnabled, "", "") \
    macro(VisibleDebugOverlayRegions, visibleDebugOverlayRegions, UInt32, uint32_t, DEFAULT_VALUE_FOR_VisibleDebugOverlayRegions, "", "") \
    macro(VisualViewportEnabled, visualViewportEnabled, Bool, bool, DEFAULT_VALUE_FOR_VisualViewportEnabled, "", "") \
    macro(WantsBalancedSetDefersLoadingBehavior, wantsBalancedSetDefersLoadingBehavior, Bool, bool, DEFAULT_VALUE_FOR_WantsBalancedSetDefersLoadingBehavior, "", "") \
    macro(WebAudioEnabled, webAudioEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAudioEnabled, "", "") \
    macro(WebMFormatReaderEnabled, webMFormatReaderEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebMFormatReaderEnabled, "", "") \
    macro(WebMParserEnabled, webMParserEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebMParserEnabled, "", "") \
    macro(WebSecurityEnabled, webSecurityEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebSecurityEnabled, "", "") \
    macro(WebSocketEnabled, webSocketEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebSocketEnabled, "", "") \
    macro(WindowFocusRestricted, windowFocusRestricted, Bool, bool, DEFAULT_VALUE_FOR_WindowFocusRestricted, "", "") \
    macro(WirelessPlaybackTargetAPIEnabled, wirelessPlaybackTargetAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_WirelessPlaybackTargetAPIEnabled, "", "") \
    macro(DirPseudoEnabled, dirPseudoEnabled, Bool, bool, DEFAULT_VALUE_FOR_DirPseudoEnabled, ":dir pseudo-class", "Enable the directionality pseudo-class :dir") \
    macro(FocusVisibleEnabled, focusVisibleEnabled, Bool, bool, DEFAULT_VALUE_FOR_FocusVisibleEnabled, ":focus-visible pseudo-class", "Enable the focus-indicated pseudo-class :focus-visible") \
    macro(HasPseudoClassEnabled, hasPseudoClassEnabled, Bool, bool, DEFAULT_VALUE_FOR_HasPseudoClassEnabled, ":has() pseudo-class", "Enable :has() pseudo-class") \
    macro(PageAtRuleSupportEnabled, pageAtRuleSupportEnabled, Bool, bool, DEFAULT_VALUE_FOR_PageAtRuleSupportEnabled, "@page CSS at-rule support", "Enable @page support") \
    macro(AriaReflectionForElementReferencesEnabled, ariaReflectionForElementReferencesEnabled, Bool, bool, DEFAULT_VALUE_FOR_AriaReflectionForElementReferencesEnabled, "ARIA Reflection for Element References", "Enable ARIA reflection for attributes that refer to elements") \
    macro(AVFoundationEnabled, isAVFoundationEnabled, Bool, bool, DEFAULT_VALUE_FOR_AVFoundationEnabled, "AVFoundation", "Enable AVFoundation") \
    macro(AbortSignalAnyOperationEnabled, abortSignalAnyOperationEnabled, Bool, bool, DEFAULT_VALUE_FOR_AbortSignalAnyOperationEnabled, "AbortSignal.any() API", "Enable AbortSignal.any() API") \
    macro(AcceleratedFiltersEnabled, acceleratedFiltersEnabled, Bool, bool, DEFAULT_VALUE_FOR_AcceleratedFiltersEnabled, "Accelerated Filter Rendering", "Accelerated CSS and SVG filter rendering") \
    macro(AccessHandleEnabled, accessHandleEnabled, Bool, bool, DEFAULT_VALUE_FOR_AccessHandleEnabled, "AccessHandle API", "Enable AccessHandle API") \
    macro(DOMTestingAPIsEnabled, domTestingAPIsEnabled, Bool, bool, DEFAULT_VALUE_FOR_DOMTestingAPIsEnabled, "Additional Testing APIs for DOM Objects", "Enable additional testing APIs for DOM objects") \
    macro(AllowMediaContentTypesRequiringHardwareSupportAsFallback, allowMediaContentTypesRequiringHardwareSupportAsFallback, Bool, bool, DEFAULT_VALUE_FOR_AllowMediaContentTypesRequiringHardwareSupportAsFallback, "Allow Media Content Types Requirining Hardware As Fallback", "Allow Media Content Types Requirining Hardware As Fallback") \
    macro(AllowViewportShrinkToFitContent, allowViewportShrinkToFitContent, Bool, bool, DEFAULT_VALUE_FOR_AllowViewportShrinkToFitContent, "Allow Viewport Shrink to Fit Content", "Allow the viewport shrink to fit content heuristic when appropriate") \
    macro(AllowWebGLInWorkers, allowWebGLInWorkers, Bool, bool, DEFAULT_VALUE_FOR_AllowWebGLInWorkers, "Allow WebGL in Web Workers", "") \
    macro(PerElementSpeakerSelectionEnabled, perElementSpeakerSelectionEnabled, Bool, bool, DEFAULT_VALUE_FOR_PerElementSpeakerSelectionEnabled, "Allow per media element speaker device selection", "Allow per media element speaker device selection") \
    macro(ExposeSpeakersEnabled, exposeSpeakersEnabled, Bool, bool, DEFAULT_VALUE_FOR_ExposeSpeakersEnabled, "Allow speaker device selection", "Allow speaker device selection") \
    macro(AllowTopNavigationToDataURLs, allowTopNavigationToDataURLs, Bool, bool, DEFAULT_VALUE_FOR_AllowTopNavigationToDataURLs, "Allow top navigation to data: URLs", "") \
    macro(AllowUniversalAccessFromFileURLs, allowUniversalAccessFromFileURLs, Bool, bool, DEFAULT_VALUE_FOR_AllowUniversalAccessFromFileURLs, "Allow universal access from file: URLs", "") \
    macro(AlternateWebMPlayerEnabled, alternateWebMPlayerEnabled, Bool, bool, DEFAULT_VALUE_FOR_AlternateWebMPlayerEnabled, "Alternate WebM Player", "Enable Alternate WebM Player") \
    macro(AppBadgeEnabled, appBadgeEnabled, Bool, bool, DEFAULT_VALUE_FOR_AppBadgeEnabled, "App Badge", "Enable App Badge") \
    macro(AppHighlightsEnabled, appHighlightsEnabled, Bool, bool, DEFAULT_VALUE_FOR_AppHighlightsEnabled, "App Highlights", "Enable App Highlights") \
    macro(AspectRatioOfImgFromWidthAndHeightEnabled, aspectRatioOfImgFromWidthAndHeightEnabled, Bool, bool, DEFAULT_VALUE_FOR_AspectRatioOfImgFromWidthAndHeightEnabled, "Aspect ratio of <img> from width and height", "Map HTML attributes width/height to the default aspect ratio of <img>") \
    macro(AsyncFrameScrollingEnabled, asyncFrameScrollingEnabled, Bool, bool, DEFAULT_VALUE_FOR_AsyncFrameScrollingEnabled, "Async Frame Scrolling", "Perform frame scrolling off the main thread") \
    macro(AsyncOverflowScrollingEnabled, asyncOverflowScrollingEnabled, Bool, bool, DEFAULT_VALUE_FOR_AsyncOverflowScrollingEnabled, "Async Overflow Scrolling", "Perform overflow scrolling off the main thread") \
    macro(AsyncClipboardAPIEnabled, asyncClipboardAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_AsyncClipboardAPIEnabled, "Async clipboard API", "Enable the async clipboard API") \
    macro(AttachmentElementEnabled, attachmentElementEnabled, Bool, bool, DEFAULT_VALUE_FOR_AttachmentElementEnabled, "Attachment Element", "Allow the insertion of attachment elements") \
    macro(AttachmentWideLayoutEnabled, attachmentWideLayoutEnabled, Bool, bool, DEFAULT_VALUE_FOR_AttachmentWideLayoutEnabled, "Attachment wide-layout styling", "Use horizontal wide-layout attachment style, requires Attachment Element") \
    macro(ExtendedAudioDescriptionsEnabled, extendedAudioDescriptionsEnabled, Bool, bool, DEFAULT_VALUE_FOR_ExtendedAudioDescriptionsEnabled, "Audio descriptions for video - Extended", "Enable extended audio descriptions for video") \
    macro(AudioDescriptionsEnabled, audioDescriptionsEnabled, Bool, bool, DEFAULT_VALUE_FOR_AudioDescriptionsEnabled, "Audio descriptions for video - Standard", "Enable standard audio descriptions for video") \
    macro(DOMAudioSessionEnabled, domAudioSessionEnabled, Bool, bool, DEFAULT_VALUE_FOR_DOMAudioSessionEnabled, "AudioSession API", "Enable AudioSession API") \
    macro(DOMAudioSessionFullEnabled, domAudioSessionFullEnabled, Bool, bool, DEFAULT_VALUE_FOR_DOMAudioSessionFullEnabled, "AudioSession full API", "Enable AudioSession full API") \
    macro(BeaconAPIEnabled, beaconAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_BeaconAPIEnabled, "Beacon API", "Beacon API") \
    macro(ThirdPartyIframeRedirectBlockingEnabled, thirdPartyIframeRedirectBlockingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ThirdPartyIframeRedirectBlockingEnabled, "Block top-level redirects by third-party iframes", "Block top-level redirects by third-party iframes") \
    macro(BroadcastChannelEnabled, broadcastChannelEnabled, Bool, bool, DEFAULT_VALUE_FOR_BroadcastChannelEnabled, "BroadcastChannel API", "BroadcastChannel API") \
    macro(BroadcastChannelOriginPartitioningEnabled, broadcastChannelOriginPartitioningEnabled, Bool, bool, DEFAULT_VALUE_FOR_BroadcastChannelOriginPartitioningEnabled, "BroadcastChannel Origin Partitioning", "BroadcastChannel Origin Partitioning") \
    macro(BuiltInNotificationsEnabled, builtInNotificationsEnabled, Bool, bool, DEFAULT_VALUE_FOR_BuiltInNotificationsEnabled, "Built-In Web Notifications", "Enable built-in WebKit managed notifications") \
    macro(UseCGDisplayListsForDOMRendering, useCGDisplayListsForDOMRendering, Bool, bool, DEFAULT_VALUE_FOR_UseCGDisplayListsForDOMRendering, "CG Display Lists: DOM Rendering", "Use CG Display Lists for DOM rendering") \
    macro(UseCGDisplayListImageCache, useCGDisplayListImageCache, Bool, bool, DEFAULT_VALUE_FOR_UseCGDisplayListImageCache, "CG Display Lists: Image Cache", "Cache and transmit surfaces out-of-line for CG Display List image buffers.") \
    macro(ReplayCGDisplayListsIntoBackingStore, replayCGDisplayListsIntoBackingStore, Bool, bool, DEFAULT_VALUE_FOR_ReplayCGDisplayListsIntoBackingStore, "CG Display Lists: Replay for Testing", "Replay CG Display Lists into layer contents for testing") \
    macro(CSS3DTransformInteroperabilityEnabled, css3DTransformInteroperabilityEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSS3DTransformInteroperabilityEnabled, "CSS 3D Transform Interoperability", "Enable 3D transform behavior that is specification-compliant but backwards incompatible") \
    macro(CSSCounterStyleAtRuleImageSymbolsEnabled, cssCounterStyleAtRuleImageSymbolsEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSCounterStyleAtRuleImageSymbolsEnabled, "CSS @counter-style <image> symbols", "Enable support for <image> symbols in CSS @counter-style rules") \
    macro(CSSCounterStyleAtRulesEnabled, cssCounterStyleAtRulesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSCounterStyleAtRulesEnabled, "CSS @counter-style", "Enable support for CSS @counter-style rules") \
    macro(CSSFontFaceSizeAdjustEnabled, cssFontFaceSizeAdjustEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSFontFaceSizeAdjustEnabled, "CSS @font-face size-adjust", "Enable size-adjust descriptor in @font-face") \
    macro(AccentColorEnabled, accentColorEnabled, Bool, bool, DEFAULT_VALUE_FOR_AccentColorEnabled, "CSS Accent Color", "Enable accent-color CSS property") \
    macro(AspectRatioEnabled, aspectRatioEnabled, Bool, bool, DEFAULT_VALUE_FOR_AspectRatioEnabled, "CSS Aspect Ratio", "Enable aspect-ratio CSS property") \
    macro(CSSCascadeLayersEnabled, cssCascadeLayersEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSCascadeLayersEnabled, "CSS Cascade Layers", "Enable CSS Cascade Layers") \
    macro(CSSColor4, cssColor4, Bool, bool, DEFAULT_VALUE_FOR_CSSColor4, "CSS Color 4 Color Types", "Enable support for CSS Color 4 Color Types") \
    macro(CSSContainIntrinsicSizeEnabled, cssContainIntrinsicSizeEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSContainIntrinsicSizeEnabled, "CSS Contain Intrinsic Size", "Enable contain-intrinsic-size CSS property") \
    macro(CSSContainerQueriesEnabled, cssContainerQueriesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSContainerQueriesEnabled, "CSS Container Queries", "Enable CSS Container Queries") \
    macro(CSSContainmentEnabled, cssContainmentEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSContainmentEnabled, "CSS Containment", "Enable contain CSS property") \
    macro(CSSContentVisibilityEnabled, cssContentVisibilityEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSContentVisibilityEnabled, "CSS Content Visibility", "Enable CSS content-visibility") \
    macro(CSSCustomPropertiesAndValuesEnabled, cssCustomPropertiesAndValuesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSCustomPropertiesAndValuesEnabled, "CSS Custom Properties and Values API", "Enable CSS Custom Properties and Values API") \
    macro(CSSGradientInterpolationColorSpacesEnabled, cssGradientInterpolationColorSpacesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSGradientInterpolationColorSpacesEnabled, "CSS Gradient Interpolation Color Spaces", "Enable custom interpolation in CSS gradients") \
    macro(CSSGradientPremultipliedAlphaInterpolationEnabled, cssGradientPremultipliedAlphaInterpolationEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSGradientPremultipliedAlphaInterpolationEnabled, "CSS Gradient Premultiplied Alpha Interpolation", "Enable premultiplied alpha interpolated CSS gradients") \
    macro(CSSIndividualTransformPropertiesEnabled, cssIndividualTransformPropertiesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSIndividualTransformPropertiesEnabled, "CSS Individual Transform Properties", "Support for the translate, scale and rotate CSS properties") \
    macro(CSSInputSecurityEnabled, cssInputSecurityEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSInputSecurityEnabled, "CSS Input Security", "Enable input-security CSS property") \
    macro(MasonryEnabled, masonryEnabled, Bool, bool, DEFAULT_VALUE_FOR_MasonryEnabled, "CSS Masonry Layout", "Enable Masonry Layout for CSS Grid") \
    macro(CSSMotionPathEnabled, cssMotionPathEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSMotionPathEnabled, "CSS Motion Path", "Enable CSS Motion Path support") \
    macro(CSSNestingEnabled, cssNestingEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSNestingEnabled, "CSS Nesting", "Enable support for CSS nesting https://www.w3.org/TR/css-nesting-1/") \
    macro(OverscrollBehaviorEnabled, overscrollBehaviorEnabled, Bool, bool, DEFAULT_VALUE_FOR_OverscrollBehaviorEnabled, "CSS Overscroll Behavior", "Enable CSS overscroll-behavior") \
    macro(CSSPaintingAPIEnabled, cssPaintingAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSPaintingAPIEnabled, "CSS Painting API", "Enable the CSS Painting API") \
    macro(CSSRelativeColorSyntaxEnabled, cssRelativeColorSyntaxEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSRelativeColorSyntaxEnabled, "CSS Relative Color Syntax", "Enable support for CSS Relative Color Syntax defined in CSS Color 5") \
    macro(CSSRhythmicSizingEnabled, cssRhythmicSizingEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSRhythmicSizingEnabled, "CSS Rhythmic Sizing", "Enable CSS Rhythmic Sizing properties") \
    macro(CSSScrollAnchoringEnabled, cssScrollAnchoringEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSScrollAnchoringEnabled, "CSS Scroll Anchoring", "Enable CSS Scroll Anchoring") \
    macro(SpringTimingFunctionEnabled, springTimingFunctionEnabled, Bool, bool, DEFAULT_VALUE_FOR_SpringTimingFunctionEnabled, "CSS Spring Animations", "CSS Spring Animation prototype") \
    macro(CSSTypedOMEnabled, cssTypedOMEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTypedOMEnabled, "CSS Typed OM", "Enable the CSS Typed OM") \
    macro(CSSTypedOMColorEnabled, cssTypedOMColorEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTypedOMColorEnabled, "CSS Typed OM: Color Support", "Enable the CSS Typed OM Color support") \
    macro(MasonryTrackAlignmentEnabled, masonryTrackAlignmentEnabled, Bool, bool, DEFAULT_VALUE_FOR_MasonryTrackAlignmentEnabled, "CSS align-tracks & justify-tracks properties for masonry layout", "Enable CSS align-tracks & justify-tracks properties for masonry layout") \
    macro(CSSColorContrastEnabled, cssColorContrastEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSColorContrastEnabled, "CSS color-contrast()", "Enable support for CSS color-contrast() defined in CSS Color 5") \
    macro(CSSColorMixEnabled, cssColorMixEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSColorMixEnabled, "CSS color-mix()", "Enable support for CSS color-mix() defined in CSS Color 5") \
    macro(CSSMarginTrimEnabled, cssMarginTrimEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSMarginTrimEnabled, "CSS margin-trim property", "Enable margin-trim CSS property") \
    macro(OverflowClipEnabled, overflowClipEnabled, Bool, bool, DEFAULT_VALUE_FOR_OverflowClipEnabled, "CSS overflow: clip support", "Enable CSS overflow: clip support") \
    macro(CSSScrollbarColorEnabled, cssScrollbarColorEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSScrollbarColorEnabled, "CSS scrollbar-color property", "Enable scrollbar-color CSS property") \
    macro(CSSScrollbarGutterEnabled, cssScrollbarGutterEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSScrollbarGutterEnabled, "CSS scrollbar-gutter property", "Enable scrollbar-gutter CSS property") \
    macro(CSSScrollbarWidthEnabled, cssScrollbarWidthEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSScrollbarWidthEnabled, "CSS scrollbar-width property", "Enable scrollbar-width CSS property") \
    macro(SubgridEnabled, subgridEnabled, Bool, bool, DEFAULT_VALUE_FOR_SubgridEnabled, "CSS subgrid support", "Enable CSS subgrid support") \
    macro(CSSTextAlignLastEnabled, cssTextAlignLastEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTextAlignLastEnabled, "CSS text-align-last property", "Enable the property text-align-last, defined in CSS Text 3") \
    macro(CSSTextBoxTrimEnabled, cssTextBoxTrimEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTextBoxTrimEnabled, "CSS text-box-trim property", "Enable text-box-trim") \
    macro(CSSTextGroupAlignEnabled, cssTextGroupAlignEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTextGroupAlignEnabled, "CSS text-group-align property", "Enable text-group-align CSS property") \
    macro(CSSTextJustifyEnabled, cssTextJustifyEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTextJustifyEnabled, "CSS text-justify property", "Enable the property text-justify, defined in CSS Text 3") \
    macro(CSSTextSpacingEnabled, cssTextSpacingEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTextSpacingEnabled, "CSS text-spacing property", "Enable the property text-spacing, defined in CSS Text 4") \
    macro(CSSTextUnderlinePositionLeftRightEnabled, cssTextUnderlinePositionLeftRightEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTextUnderlinePositionLeftRightEnabled, "CSS text-underline-position: left right", "Enable the property text-underline-position left and right value support") \
    macro(CSSWhiteSpaceLonghandsEnabled, cssWhiteSpaceLonghandsEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSWhiteSpaceLonghandsEnabled, "CSS text-wrap & white-space-collapse properties", "Enable text-wrap & white-space-collapse CSS properties") \
    macro(CSSTextWrapNewValuesEnabled, cssTextWrapNewValuesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTextWrapNewValuesEnabled, "CSS text-wrap: balance stable pretty", "Enable text-wrap: balance/stable/pretty CSS support") \
    macro(CSSTransformStyleOptimized3DEnabled, cssTransformStyleOptimized3DEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTransformStyleOptimized3DEnabled, "CSS transform-style: optimized-3d", "Enable transform-style: optimized-3d property to access the separated graphics layer") \
    macro(CSSOMViewScrollingAPIEnabled, cssOMViewScrollingAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSOMViewScrollingAPIEnabled, "CSSOM View Scrolling API", "Implement standard behavior for scrollLeft, scrollTop, scrollWidth, scrollHeight, scrollTo, scrollBy and scrollingElement.") \
    macro(CSSOMViewSmoothScrollingEnabled, cssOMViewSmoothScrollingEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSOMViewSmoothScrollingEnabled, "CSSOM View Smooth Scrolling", "Enable DOM API and CSS property for 'smooth' scroll behavior") \
    macro(CacheAPIEnabled, cacheAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_CacheAPIEnabled, "Cache API", "Cache API") \
    macro(CanvasColorSpaceEnabled, canvasColorSpaceEnabled, Bool, bool, DEFAULT_VALUE_FOR_CanvasColorSpaceEnabled, "Canvas Color Spaces", "Enable use of predefined canvas color spaces") \
    macro(CanvasFiltersEnabled, canvasFiltersEnabled, Bool, bool, DEFAULT_VALUE_FOR_CanvasFiltersEnabled, "Canvas Filters", "Canvas Filters") \
    macro(CanvasUsesAcceleratedDrawing, canvasUsesAcceleratedDrawing, Bool, bool, DEFAULT_VALUE_FOR_CanvasUsesAcceleratedDrawing, "Canvas uses accelerated drawing", "") \
    macro(CaptureAudioInUIProcessEnabled, captureAudioInUIProcessEnabled, Bool, bool, DEFAULT_VALUE_FOR_CaptureAudioInUIProcessEnabled, "Capture audio in UI Process", "Enable audio capture in UI Process") \
    macro(CaptureVideoInUIProcessEnabled, captureVideoInUIProcessEnabled, Bool, bool, DEFAULT_VALUE_FOR_CaptureVideoInUIProcessEnabled, "Capture video in UI Process", "Enable video capture in UI Process") \
    macro(ClearSiteDataHTTPHeaderEnabled, clearSiteDataHTTPHeaderEnabled, Bool, bool, DEFAULT_VALUE_FOR_ClearSiteDataHTTPHeaderEnabled, "Clear-Site-Data HTTP Header", "Enable Clear-Site-Data HTTP Header support") \
    macro(ClientBadgeEnabled, clientBadgeEnabled, Bool, bool, DEFAULT_VALUE_FOR_ClientBadgeEnabled, "Client Badge", "Enable Client Badge") \
    macro(InputTypeColorEnabled, inputTypeColorEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeColorEnabled, "Color Inputs", "Enable input elements of type color") \
    macro(CompositingBordersVisible, compositingBordersVisible, Bool, bool, DEFAULT_VALUE_FOR_CompositingBordersVisible, "Compositing borders visible", "") \
    macro(CompositingRepaintCountersVisible, compositingRepaintCountersVisible, Bool, bool, DEFAULT_VALUE_FOR_CompositingRepaintCountersVisible, "Compositing repaint counters visible", "") \
    macro(CompressionStreamEnabled, compressionStreamEnabled, Bool, bool, DEFAULT_VALUE_FOR_CompressionStreamEnabled, "Compression Stream API", "Enable Compression Stream API") \
    macro(ConstructableStylesheetsEnabled, constructableStylesheetsEnabled, Bool, bool, DEFAULT_VALUE_FOR_ConstructableStylesheetsEnabled, "Constructable Stylesheets", "Enable Constructable Stylesheets") \
    macro(ContactPickerAPIEnabled, contactPickerAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_ContactPickerAPIEnabled, "Contact Picker API", "Enable the Contact Picker API") \
    macro(SampleBufferContentKeySessionSupportEnabled, sampleBufferContentKeySessionSupportEnabled, Bool, bool, DEFAULT_VALUE_FOR_SampleBufferContentKeySessionSupportEnabled, "ContentKeySession support for SampleBuffer Renderers", "ContentKeySession support for SampleBuffer Renderers Enabled") \
    macro(CookieConsentAPIEnabled, cookieConsentAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_CookieConsentAPIEnabled, "Cookie Consent API", "Enable cookie consent API") \
    macro(CookieStoreAPIExtendedAttributesEnabled, cookieStoreAPIExtendedAttributesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CookieStoreAPIExtendedAttributesEnabled, "Cookie Store API Extended Attributes", "Enable Extended Attributes of the Cookie Store API") \
    macro(CookieStoreAPIEnabled, cookieStoreAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_CookieStoreAPIEnabled, "Cookie Store API", "Enable Cookie Store API") \
    macro(CookieEnabled, cookieEnabled, Bool, bool, DEFAULT_VALUE_FOR_CookieEnabled, "Cookies Enabled", "") \
    macro(CrossOriginEmbedderPolicyEnabled, crossOriginEmbedderPolicyEnabled, Bool, bool, DEFAULT_VALUE_FOR_CrossOriginEmbedderPolicyEnabled, "Cross-Origin-Embedder-Policy (COEP) header", "Support for Cross-Origin-Embedder-Policy (COEP) header") \
    macro(CrossOriginOpenerPolicyEnabled, crossOriginOpenerPolicyEnabled, Bool, bool, DEFAULT_VALUE_FOR_CrossOriginOpenerPolicyEnabled, "Cross-Origin-Opener-Policy (COOP) header", "Support for Cross-Origin-Opener-Policy (COOP) header") \
    macro(CustomPasteboardDataEnabled, customPasteboardDataEnabled, Bool, bool, DEFAULT_VALUE_FOR_CustomPasteboardDataEnabled, "Custom pasteboard data", "Enable custom clipboard types and better security model for clipboard API.") \
    macro(DOMPasteAccessRequestsEnabled, domPasteAccessRequestsEnabled, Bool, bool, DEFAULT_VALUE_FOR_DOMPasteAccessRequestsEnabled, "DOM Paste Access Requests", "Enable DOM Paste Access Requests") \
    macro(DOMTimersThrottlingEnabled, domTimersThrottlingEnabled, Bool, bool, DEFAULT_VALUE_FOR_DOMTimersThrottlingEnabled, "DOM timer throttling enabled", "") \
    macro(DeclarativeShadowDOMInDOMParserEnabled, declarativeShadowDOMInDOMParserEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeclarativeShadowDOMInDOMParserEnabled, "DOMParser support for Declarative Shadow DOM", "Enable Declarative Shadow DOM in DOMParser") \
    macro(ZoomOnDoubleTapWhenRoot, zoomOnDoubleTapWhenRoot, Bool, bool, DEFAULT_VALUE_FOR_ZoomOnDoubleTapWhenRoot, "DTTZ also when root", "Double taps zoom, even if we dispatched a click on the root nodes") \
    macro(AlwaysZoomOnDoubleTap, alwaysZoomOnDoubleTap, Bool, bool, DEFAULT_VALUE_FOR_AlwaysZoomOnDoubleTap, "DTTZ always", "Double taps zoom, even if we dispatched a click anywhere") \
    macro(DataTransferItemsEnabled, dataTransferItemsEnabled, Bool, bool, DEFAULT_VALUE_FOR_DataTransferItemsEnabled, "Data Transfer Items", "Enables DataTransferItem in the clipboard API") \
    macro(DataListElementEnabled, dataListElementEnabled, Bool, bool, DEFAULT_VALUE_FOR_DataListElementEnabled, "DataList Element", "Enable datalist elements") \
    macro(InputTypeDateEnabled, inputTypeDateEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeDateEnabled, "Date Input", "Enable input elements of type date") \
    macro(DateTimeInputsEditableComponentsEnabled, dateTimeInputsEditableComponentsEnabled, Bool, bool, DEFAULT_VALUE_FOR_DateTimeInputsEditableComponentsEnabled, "Date/Time inputs have editable components", "Enable multiple editable components in date/time inputs") \
    macro(DeclarativeShadowDOMEnabled, declarativeShadowDOMEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeclarativeShadowDOMEnabled, "Declarative Shadow DOM", "Enable Declarative Shadow DOM") \
    macro(DefaultARIAForCustomElementsEnabled, defaultARIAForCustomElementsEnabled, Bool, bool, DEFAULT_VALUE_FOR_DefaultARIAForCustomElementsEnabled, "Default ARIA for Custom Elements", "Enable Default ARIA for Custom Elements") \
    macro(ShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint, shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint, Bool, bool, DEFAULT_VALUE_FOR_ShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint, "Defer async scripts until DOMContentLoaded or first-paint", "Defer async scripts until DOMContentLoaded or first-paint") \
    macro(DeprecateRSAESPKCSWebCryptoEnabled, deprecateRSAESPKCSWebCryptoEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeprecateRSAESPKCSWebCryptoEnabled, "Deprecate RSAES-PKCS1-v1_5 Web Crypto", "Enable Deprecation of RSAES-PKCS1-v1_5 Web Crypto") \
    macro(DeprecationReportingEnabled, deprecationReportingEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeprecationReportingEnabled, "Deprecation Reporting", "Enable Deprecation Reporting") \
    macro(DiagnosticLoggingEnabled, diagnosticLoggingEnabled, Bool, bool, DEFAULT_VALUE_FOR_DiagnosticLoggingEnabled, "Diagnostic logging enabled", "") \
    macro(DirectoryUploadEnabled, directoryUploadEnabled, Bool, bool, DEFAULT_VALUE_FOR_DirectoryUploadEnabled, "Directory Upload", "input.webkitdirectory / dataTransferItem.webkitGetAsEntry()") \
    macro(IsThirdPartyCookieBlockingDisabled, isThirdPartyCookieBlockingDisabled, Bool, bool, DEFAULT_VALUE_FOR_IsThirdPartyCookieBlockingDisabled, "Disable Full 3rd-Party Cookie Blocking (ITP)", "Disable full third-party cookie blocking when Intelligent Tracking Prevention is enabled") \
    macro(IsFirstPartyWebsiteDataRemovalDisabled, isFirstPartyWebsiteDataRemovalDisabled, Bool, bool, DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalDisabled, "Disable Removal of Non-Cookie Data After 7 Days of No User Interaction (ITP)", "Disable removal of all non-cookie website data after seven days of no user interaction when Intelligent Tracking Prevention is enabled") \
    macro(DisableScreenSizeOverride, disableScreenSizeOverride, Bool, bool, DEFAULT_VALUE_FOR_DisableScreenSizeOverride, "Disable screen size override", "") \
    macro(DisallowSyncXHRDuringPageDismissalEnabled, disallowSyncXHRDuringPageDismissalEnabled, Bool, bool, DEFAULT_VALUE_FOR_DisallowSyncXHRDuringPageDismissalEnabled, "Disallow sync XHR during page dismissal", "Disallow synchronous XMLHttpRequest during page dismissal") \
    macro(DisplayListDrawingEnabled, displayListDrawingEnabled, Bool, bool, DEFAULT_VALUE_FOR_DisplayListDrawingEnabled, "DisplayList Drawing", "Enable display-list drawing") \
    macro(ShouldDropNearSuspendedAssertionAfterDelay, shouldDropNearSuspendedAssertionAfterDelay, Bool, bool, DEFAULT_VALUE_FOR_ShouldDropNearSuspendedAssertionAfterDelay, "Drop Near-Suspended Assertion After Delay", "Causes processes to fully suspend after a delay") \
    macro(EmbedElementEnabled, embedElementEnabled, Bool, bool, DEFAULT_VALUE_FOR_EmbedElementEnabled, "Embed Element", "Embed Element") \
    macro(AutomaticLiveResizeEnabled, automaticLiveResizeEnabled, Bool, bool, DEFAULT_VALUE_FOR_AutomaticLiveResizeEnabled, "Enable Automatic Live Resize", "Automatically synchronize web view resize with painting") \
    macro(CanvasFingerprintingQuirkEnabled, canvasFingerprintingQuirkEnabled, Bool, bool, DEFAULT_VALUE_FOR_CanvasFingerprintingQuirkEnabled, "Enable Canvas fingerprinting-related quirk", "") \
    macro(EnumeratingAllNetworkInterfacesEnabled, enumeratingAllNetworkInterfacesEnabled, Bool, bool, DEFAULT_VALUE_FOR_EnumeratingAllNetworkInterfacesEnabled, "Enable Enumerating All Network Interfaces", "") \
    macro(EnumeratingVisibleNetworkInterfacesEnabled, enumeratingVisibleNetworkInterfacesEnabled, Bool, bool, DEFAULT_VALUE_FOR_EnumeratingVisibleNetworkInterfacesEnabled, "Enable Enumerating Visible Network Interfaces", "") \
    macro(ICECandidateFilteringEnabled, iceCandidateFilteringEnabled, Bool, bool, DEFAULT_VALUE_FOR_ICECandidateFilteringEnabled, "Enable ICE Candidate Filtering", "Enable ICE Candidate Filtering") \
    macro(LegacyEncryptedMediaAPIEnabled, legacyEncryptedMediaAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_LegacyEncryptedMediaAPIEnabled, "Enable Legacy EME API", "Enable legacy EME API") \
    macro(MockCaptureDevicesEnabled, mockCaptureDevicesEnabled, Bool, bool, DEFAULT_VALUE_FOR_MockCaptureDevicesEnabled, "Enable Mock Capture Devices", "Enable Mock Capture Devices") \
    macro(PdfJSViewerEnabled, pdfJSViewerEnabled, Bool, bool, DEFAULT_VALUE_FOR_PdfJSViewerEnabled, "Enable PDF.js viewer", "Enable PDF.js viewer") \
    macro(BackgroundWebContentRunningBoardThrottlingEnabled, backgroundWebContentRunningBoardThrottlingEnabled, Bool, bool, DEFAULT_VALUE_FOR_BackgroundWebContentRunningBoardThrottlingEnabled, "Enable background web content throttling via RunningBoard", "Enable background web content throttling via RunningBoard") \
    macro(BackgroundFetchAPIEnabled, backgroundFetchAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_BackgroundFetchAPIEnabled, "Enable background-fetch API", "Enable background-fetch API") \
    macro(ExperimentalSandboxEnabled, experimentalSandboxEnabled, Bool, bool, DEFAULT_VALUE_FOR_ExperimentalSandboxEnabled, "Enable experimental sandbox features", "Enable experimental sandbox features") \
    macro(StrictSecureDecodingForAllObjC, strictSecureDecodingForAllObjC, Bool, bool, DEFAULT_VALUE_FOR_StrictSecureDecodingForAllObjC, "Enable strict decoding of all ObjC classes", "") \
    macro(EnterKeyHintEnabled, enterKeyHintEnabled, Bool, bool, DEFAULT_VALUE_FOR_EnterKeyHintEnabled, "Enter Key Hint", "Enable the enterKeyHint HTML attribute") \
    macro(EventHandlerDrivenSmoothKeyboardScrollingEnabled, eventHandlerDrivenSmoothKeyboardScrollingEnabled, Bool, bool, DEFAULT_VALUE_FOR_EventHandlerDrivenSmoothKeyboardScrollingEnabled, "EventHandler driven smooth keyboard scrolling", "Enable EventHandler driven smooth keyboard scrolling") \
    macro(MediaSessionCoordinatorEnabled, mediaSessionCoordinatorEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaSessionCoordinatorEnabled, "Experimental MediaSession coordinator API", "Enable experimental MediaSession coordinator API") \
    macro(MediaSessionPlaylistEnabled, mediaSessionPlaylistEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaSessionPlaylistEnabled, "Experimental MediaSession playlist API", "Enable experimental MediaSession playlist API") \
    macro(MediaSourceInlinePaintingEnabled, mediaSourceInlinePaintingEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaSourceInlinePaintingEnabled, "Experimental MediaSource Inline Painting", "Experimental MediaSource Inline Painting") \
    macro(CFNetworkNetworkLoaderEnabled, cFNetworkNetworkLoaderEnabled, Bool, bool, DEFAULT_VALUE_FOR_CFNetworkNetworkLoaderEnabled, "Experimental network loader", "Enable experimental network loader") \
    macro(FTPEnabled, ftpEnabled, Bool, bool, DEFAULT_VALUE_FOR_FTPEnabled, "FTP support enabled", "FTP support enabled") \
    macro(PreferFasterClickOverDoubleTap, preferFasterClickOverDoubleTap, Bool, bool, DEFAULT_VALUE_FOR_PreferFasterClickOverDoubleTap, "Fast clicks beat DTTZ", "Prefer a faster click over a double tap") \
    macro(FasterClicksEnabled, fasterClicksEnabled, Bool, bool, DEFAULT_VALUE_FOR_FasterClicksEnabled, "Fast clicks", "Support faster clicks on zoomable pages") \
    macro(FetchAPIKeepAliveEnabled, fetchAPIKeepAliveEnabled, Bool, bool, DEFAULT_VALUE_FOR_FetchAPIKeepAliveEnabled, "Fetch API Request KeepAlive", "Enable Fetch API Request KeepAlive") \
    macro(FetchAPIEnabled, fetchAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_FetchAPIEnabled, "Fetch API", "Fetch API") \
    macro(FetchMetadataEnabled, fetchMetadataEnabled, Bool, bool, DEFAULT_VALUE_FOR_FetchMetadataEnabled, "Fetch Metadata", "Enable Fetch Metadata headers") \
    macro(FetchPriorityEnabled, fetchPriorityEnabled, Bool, bool, DEFAULT_VALUE_FOR_FetchPriorityEnabled, "Fetch Priority", "Enable Fetch Priority support") \
    macro(FileSystemAccessEnabled, fileSystemAccessEnabled, Bool, bool, DEFAULT_VALUE_FOR_FileSystemAccessEnabled, "File System Access API", "Enable File System Access API") \
    macro(FileReaderAPIEnabled, fileReaderAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_FileReaderAPIEnabled, "FileReader API", "FileReader API") \
    macro(RestrictedHTTPResponseAccess, restrictedHTTPResponseAccess, Bool, bool, DEFAULT_VALUE_FOR_RestrictedHTTPResponseAccess, "Filter HTTP Response for Web Processes", "Enable HTTP Response filtering for Web Processes") \
    macro(ForceAlwaysUserScalable, forceAlwaysUserScalable, Bool, bool, DEFAULT_VALUE_FOR_ForceAlwaysUserScalable, "Force always user-scalable", "") \
    macro(RequestSubmitEnabled, requestSubmitEnabled, Bool, bool, DEFAULT_VALUE_FOR_RequestSubmitEnabled, "Form requestSubmit", "Form requestSubmit method") \
    macro(FormAssociatedCustomElementsEnabled, formAssociatedCustomElementsEnabled, Bool, bool, DEFAULT_VALUE_FOR_FormAssociatedCustomElementsEnabled, "Form-associated custom elements", "Support for form-associated custom elements") \
    macro(FrameFlatteningEnabled, frameFlatteningEnabled, Bool, bool, DEFAULT_VALUE_FOR_FrameFlatteningEnabled, "Frame flattening", "Enable frame flattening, which adjusts the height of an iframe to fit its contents") \
    macro(LayoutFormattingContextEnabled, layoutFormattingContextEnabled, Bool, bool, DEFAULT_VALUE_FOR_LayoutFormattingContextEnabled, "Full next-generation layout (LFC)", "Enable full next-generation layout (LFC)") \
    macro(FullScreenEnabled, fullScreenEnabled, Bool, bool, DEFAULT_VALUE_FOR_FullScreenEnabled, "Fullscreen API", "Fullscreen API") \
    macro(FullscreenSceneAspectRatioLockingEnabled, fullscreenSceneAspectRatioLockingEnabled, Bool, bool, DEFAULT_VALUE_FOR_FullscreenSceneAspectRatioLockingEnabled, "Fullscreen scene aspect ratio locking", "Enable scene aspect ratio locking in Fullscreen") \
    macro(FullscreenSceneDimmingEnabled, fullscreenSceneDimmingEnabled, Bool, bool, DEFAULT_VALUE_FOR_FullscreenSceneDimmingEnabled, "Fullscreen scene dimming", "Enable scene dimming in Fullscreen") \
    macro(CaptureAudioInGPUProcessEnabled, captureAudioInGPUProcessEnabled, Bool, bool, DEFAULT_VALUE_FOR_CaptureAudioInGPUProcessEnabled, "GPU Process: Audio Capture", "Enable audio capture in GPU Process") \
    macro(BlockMediaLayerRehostingInWebContentProcess, blockMediaLayerRehostingInWebContentProcess, Bool, bool, DEFAULT_VALUE_FOR_BlockMediaLayerRehostingInWebContentProcess, "GPU Process: Block Media Layer Re-hosting", "GPU Process: Block Media Layer Re-hosting in WebContent process") \
    macro(UseGPUProcessForCanvasRenderingEnabled, useGPUProcessForCanvasRenderingEnabled, Bool, bool, DEFAULT_VALUE_FOR_UseGPUProcessForCanvasRenderingEnabled, "GPU Process: Canvas Rendering", "Enable canvas rendering in GPU Process") \
    macro(ManageCaptureStatusBarInGPUProcessEnabled, manageCaptureStatusBarInGPUProcessEnabled, Bool, bool, DEFAULT_VALUE_FOR_ManageCaptureStatusBarInGPUProcessEnabled, "GPU Process: Capture Status Bar management", "Enable Capture Status Bar management in GPU Process") \
    macro(UseGPUProcessForDOMRenderingEnabled, useGPUProcessForDOMRenderingEnabled, Bool, bool, DEFAULT_VALUE_FOR_UseGPUProcessForDOMRenderingEnabled, "GPU Process: DOM Rendering", "Enable DOM rendering in GPU Process") \
    macro(UseGPUProcessForMediaEnabled, useGPUProcessForMediaEnabled, Bool, bool, DEFAULT_VALUE_FOR_UseGPUProcessForMediaEnabled, "GPU Process: Media", "Do all media loading and playback in the GPU Process") \
    macro(UseGPUProcessForDisplayCapture, useGPUProcessForDisplayCapture, Bool, bool, DEFAULT_VALUE_FOR_UseGPUProcessForDisplayCapture, "GPU Process: Screen and Window capture", "Display capture in GPU Process") \
    macro(CaptureVideoInGPUProcessEnabled, captureVideoInGPUProcessEnabled, Bool, bool, DEFAULT_VALUE_FOR_CaptureVideoInGPUProcessEnabled, "GPU Process: Video Capture", "Enable video capture in GPU Process") \
    macro(UseGPUProcessForWebGLEnabled, useGPUProcessForWebGLEnabled, Bool, bool, DEFAULT_VALUE_FOR_UseGPUProcessForWebGLEnabled, "GPU Process: WebGL", "Process all WebGL operations in GPU Process") \
    macro(WebRTCPlatformCodecsInGPUProcessEnabled, webRTCPlatformCodecsInGPUProcessEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCPlatformCodecsInGPUProcessEnabled, "GPU Process: WebRTC Platform Codecs", "Enable WebRTC Platform Codecs in GPU Process") \
    macro(GamepadTriggerRumbleEnabled, gamepadTriggerRumbleEnabled, Bool, bool, DEFAULT_VALUE_FOR_GamepadTriggerRumbleEnabled, "Gamepad trigger vibration support", "Support for Gamepad trigger vibration") \
    macro(GamepadVibrationActuatorEnabled, gamepadVibrationActuatorEnabled, Bool, bool, DEFAULT_VALUE_FOR_GamepadVibrationActuatorEnabled, "Gamepad.vibrationActuator support", "Support for Gamepad.vibrationActuator") \
    macro(GamepadsEnabled, gamepadsEnabled, Bool, bool, DEFAULT_VALUE_FOR_GamepadsEnabled, "Gamepads", "Web Gamepad API support") \
    macro(GenericCueAPIEnabled, genericCueAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_GenericCueAPIEnabled, "Generic Text Track Cue API", "Enable Generic Text Track Cue API") \
    macro(GraphicsContextFiltersEnabled, graphicsContextFiltersEnabled, Bool, bool, DEFAULT_VALUE_FOR_GraphicsContextFiltersEnabled, "GraphicsContext Filter Rendering", "GraphicsContext Filter Rendering") \
    macro(AcceleratedDrawingEnabled, acceleratedDrawingEnabled, Bool, bool, DEFAULT_VALUE_FOR_AcceleratedDrawingEnabled, "GraphicsLayer accelerated drawing", "Enable GraphicsLayer accelerated drawing") \
    macro(DialogElementEnabled, dialogElementEnabled, Bool, bool, DEFAULT_VALUE_FOR_DialogElementEnabled, "HTML <dialog> element", "Enable HTML <dialog> element") \
    macro(ModelElementEnabled, modelElementEnabled, Bool, bool, DEFAULT_VALUE_FOR_ModelElementEnabled, "HTML <model> element", "Enable HTML <model> element") \
    macro(ModelDocumentEnabled, modelDocumentEnabled, Bool, bool, DEFAULT_VALUE_FOR_ModelDocumentEnabled, "HTML <model> elements for stand-alone document", "Enable HTML <model> element for model documents") \
    macro(InteractiveFormValidationEnabled, interactiveFormValidationEnabled, Bool, bool, DEFAULT_VALUE_FOR_InteractiveFormValidationEnabled, "HTML Interactive Form Validation", "HTML interactive form validation") \
    macro(InertAttributeEnabled, inertAttributeEnabled, Bool, bool, DEFAULT_VALUE_FOR_InertAttributeEnabled, "HTML inert attribute", "Enable inert attribute support") \
    macro(PopoverAttributeEnabled, popoverAttributeEnabled, Bool, bool, DEFAULT_VALUE_FOR_PopoverAttributeEnabled, "HTML popover attribute", "Enable HTML popover attribute support") \
    macro(HiddenPageDOMTimerThrottlingAutoIncreases, hiddenPageDOMTimerThrottlingAutoIncreases, Bool, bool, DEFAULT_VALUE_FOR_HiddenPageDOMTimerThrottlingAutoIncreases, "Hidden page DOM timer throttling auto-increases", "") \
    macro(HiddenPageDOMTimerThrottlingEnabled, hiddenPageDOMTimerThrottlingEnabled, Bool, bool, DEFAULT_VALUE_FOR_HiddenPageDOMTimerThrottlingEnabled, "Hidden page DOM timer throttling", "Enable hidden page DOM timer throttling") \
    macro(HighlightAPIEnabled, highlightAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_HighlightAPIEnabled, "Highlight API", "Highlight API support") \
    macro(HyperlinkAuditingEnabled, hyperlinkAuditingEnabled, Bool, bool, DEFAULT_VALUE_FOR_HyperlinkAuditingEnabled, "Hyperlink Auditing", "Enable Hyperlink Auditing") \
    macro(BlockIOKitInWebContentSandbox, blockIOKitInWebContentSandbox, Bool, bool, DEFAULT_VALUE_FOR_BlockIOKitInWebContentSandbox, "IOKit blocking in the WebContent sandbox", "Block IOKit access in the WebContent sandbox") \
    macro(IPCTestingAPIEnabled, ipcTestingAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_IPCTestingAPIEnabled, "IPC Testing API", "Enable IPC Testing API for JavaScript") \
    macro(ItpDebugModeEnabled, itpDebugModeEnabled, Bool, bool, DEFAULT_VALUE_FOR_ItpDebugModeEnabled, "ITP Debug Mode", "Intelligent Tracking Prevention Debug Mode") \
    macro(TextAutosizingUsesIdempotentMode, textAutosizingUsesIdempotentMode, Bool, bool, DEFAULT_VALUE_FOR_TextAutosizingUsesIdempotentMode, "Idempotent Text Autosizing", "Use idempotent text autosizing mode") \
    macro(ImageAnalysisDuringFindInPageEnabled, imageAnalysisDuringFindInPageEnabled, Bool, bool, DEFAULT_VALUE_FOR_ImageAnalysisDuringFindInPageEnabled, "Image Analysis for Find-in-Page", "Trigger image analysis when performing Find-in-Page") \
    macro(ImageAnimationControlEnabled, imageAnimationControlEnabled, Bool, bool, DEFAULT_VALUE_FOR_ImageAnimationControlEnabled, "Image Animation Control", "Enable controls for image animations") \
    macro(ImageControlsEnabled, imageControlsEnabled, Bool, bool, DEFAULT_VALUE_FOR_ImageControlsEnabled, "Image Controls", "Enable image controls") \
    macro(ImperativeSlotAPIEnabled, imperativeSlotAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_ImperativeSlotAPIEnabled, "Imperative Slot API", "Imperative Shadow DOM Distribution API") \
    macro(IndexedDBAPIEnabled, indexedDBAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_IndexedDBAPIEnabled, "IndexedDB API", "IndexedDB API") \
    macro(InlinePredictionsInAllEditableElementsEnabled, inlinePredictionsInAllEditableElementsEnabled, Bool, bool, DEFAULT_VALUE_FOR_InlinePredictionsInAllEditableElementsEnabled, "Inline Text Predictions", "Enable Inline Text Predictions in all editable elements") \
    macro(InteractionRegionsEnabled, interactionRegionsEnabled, Bool, bool, DEFAULT_VALUE_FOR_InteractionRegionsEnabled, "Interaction Regions", "Generate and visualize interaction regions") \
    macro(IntersectionObserverEnabled, intersectionObserverEnabled, Bool, bool, DEFAULT_VALUE_FOR_IntersectionObserverEnabled, "Intersection Observer", "Enable Intersection Observer support") \
    macro(IsLoggedInAPIEnabled, isLoggedInAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_IsLoggedInAPIEnabled, "IsLoggedIn web API", "Enable the proposed IsLoggedIn web API") \
    macro(IsAccessibilityIsolatedTreeEnabled, isAccessibilityIsolatedTreeEnabled, Bool, bool, DEFAULT_VALUE_FOR_IsAccessibilityIsolatedTreeEnabled, "Isolated Accessibility Tree Mode", "Enable an accessibility hierarchy for VoiceOver that can be accessed on a secondary thread for improved performance") \
    macro(JavaScriptEnabled, javaScriptEnabled, Bool, bool, DEFAULT_VALUE_FOR_JavaScriptEnabled, "JavaScript", "Enable JavaScript") \
    macro(LayerBasedSVGEngineEnabled, layerBasedSVGEngineEnabled, Bool, bool, DEFAULT_VALUE_FOR_LayerBasedSVGEngineEnabled, "Layer-based SVG Engine (LBSE)", "Enable next-generation layer-based SVG Engine (LBSE)") \
    macro(LazyIframeLoadingEnabled, lazyIframeLoadingEnabled, Bool, bool, DEFAULT_VALUE_FOR_LazyIframeLoadingEnabled, "Lazy iframe loading", "Enable lazy iframe loading support") \
    macro(LazyImageLoadingEnabled, lazyImageLoadingEnabled, Bool, bool, DEFAULT_VALUE_FOR_LazyImageLoadingEnabled, "Lazy image loading", "Enable lazy image loading support") \
    macro(LegacyOverflowScrollingTouchEnabled, legacyOverflowScrollingTouchEnabled, Bool, bool, DEFAULT_VALUE_FOR_LegacyOverflowScrollingTouchEnabled, "Legacy -webkit-overflow-scrolling property", "Support the legacy -webkit-overflow-scrolling CSS property") \
    macro(LegacyLineLayoutVisualCoverageEnabled, legacyLineLayoutVisualCoverageEnabled, Bool, bool, DEFAULT_VALUE_FOR_LegacyLineLayoutVisualCoverageEnabled, "Legacy line layout visual coverage", "Enable legacy line layout visual coverage") \
    macro(ShowModalDialogEnabled, showModalDialogEnabled, Bool, bool, DEFAULT_VALUE_FOR_ShowModalDialogEnabled, "Legacy showModalDialog() API", "Legacy showModalDialog() API") \
    macro(MediaCaptureRequiresSecureConnection, mediaCaptureRequiresSecureConnection, Bool, bool, DEFAULT_VALUE_FOR_MediaCaptureRequiresSecureConnection, "Limit Media Capture to Secure Sites", "Limit Media Capture to Secure Sites") \
    macro(LinkSanitizerEnabled, linkSanitizerEnabled, Bool, bool, DEFAULT_VALUE_FOR_LinkSanitizerEnabled, "Link Sanitizer", "Enable link sanitizer") \
    macro(LinkPreloadResponsiveImagesEnabled, linkPreloadResponsiveImagesEnabled, Bool, bool, DEFAULT_VALUE_FOR_LinkPreloadResponsiveImagesEnabled, "Link preload responsive images", "Enable link preload responsive images") \
    macro(LinkModulePreloadEnabled, linkModulePreloadEnabled, Bool, bool, DEFAULT_VALUE_FOR_LinkModulePreloadEnabled, "Link rel=modulepreload", "Enable Link rel=modulepreload") \
    macro(LinkPreconnectEarlyHintsEnabled, linkPreconnectEarlyHintsEnabled, Bool, bool, DEFAULT_VALUE_FOR_LinkPreconnectEarlyHintsEnabled, "Link rel=preconnect via HTTP early hints", "Enable link rel=preconnect via early hints") \
    macro(LinkPrefetchEnabled, linkPrefetchEnabled, Bool, bool, DEFAULT_VALUE_FOR_LinkPrefetchEnabled, "LinkPrefetch", "Enable LinkedPrefetch") \
    macro(LiveRangeSelectionEnabled, liveRangeSelectionEnabled, Bool, bool, DEFAULT_VALUE_FOR_LiveRangeSelectionEnabled, "Live Ranges in Selection", "Live range behavior for ranges in the Selection object") \
    macro(LocalFileContentSniffingEnabled, localFileContentSniffingEnabled, Bool, bool, DEFAULT_VALUE_FOR_LocalFileContentSniffingEnabled, "Local File Content Sniffing", "Enable Local File Content Sniffing") \
    macro(LocalStorageEnabled, localStorageEnabled, Bool, bool, DEFAULT_VALUE_FOR_LocalStorageEnabled, "Local Storage", "Enable Local Storage") \
    macro(LogsPageMessagesToSystemConsoleEnabled, logsPageMessagesToSystemConsoleEnabled, Bool, bool, DEFAULT_VALUE_FOR_LogsPageMessagesToSystemConsoleEnabled, "Log page messages to system console", "Enable logging page messages to system console") \
    macro(MainContentUserGestureOverrideEnabled, mainContentUserGestureOverrideEnabled, Bool, bool, DEFAULT_VALUE_FOR_MainContentUserGestureOverrideEnabled, "Main content user gesture override", "Enable main content user gesture override") \
    macro(ManagedMediaSourceEnabled, managedMediaSourceEnabled, Bool, bool, DEFAULT_VALUE_FOR_ManagedMediaSourceEnabled, "Managed Media Source API", "Managed Media Source API") \
    macro(ManagedMediaSourceNeedsAirPlay, managedMediaSourceNeedsAirPlay, Bool, bool, DEFAULT_VALUE_FOR_ManagedMediaSourceNeedsAirPlay, "Managed Media Source Requires AirPlay source", "Managed Media Source Requires AirPlay source") \
    macro(MaskWebGLStringsEnabled, maskWebGLStringsEnabled, Bool, bool, DEFAULT_VALUE_FOR_MaskWebGLStringsEnabled, "Mask WebGL Strings", "Mask WebGL Vendor, Renderer, Shader Language Strings") \
    macro(CoreMathMLEnabled, coreMathMLEnabled, Bool, bool, DEFAULT_VALUE_FOR_CoreMathMLEnabled, "MathML Core", "Disable features removed from the MathML Core spec.") \
    macro(MediaCapabilitiesExtensionsEnabled, mediaCapabilitiesExtensionsEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaCapabilitiesExtensionsEnabled, "Media Capabilities Extensions", "Media Capabilities Extensions") \
    macro(MediaSessionEnabled, mediaSessionEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaSessionEnabled, "Media Session API", "Media Session API") \
    macro(MediaSourceEnabled, mediaSourceEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaSourceEnabled, "Media Source API", "Media Source API") \
    macro(MediaDevicesEnabled, mediaDevicesEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaDevicesEnabled, "Media devices", "Enable media devices") \
    macro(MediaRecorderEnabled, mediaRecorderEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaRecorderEnabled, "MediaRecorder", "MediaRecorder") \
    macro(MomentumScrollingAnimatorEnabled, momentumScrollingAnimatorEnabled, Bool, bool, DEFAULT_VALUE_FOR_MomentumScrollingAnimatorEnabled, "Momentum Scrolling Animator", "Generate momentum events in WebKit instead of using those delivered by the system") \
    macro(InputTypeMonthEnabled, inputTypeMonthEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeMonthEnabled, "Month Input", "Enable input elements of type month") \
    macro(MouseEventsSimulationEnabled, mouseEventsSimulationEnabled, Bool, bool, DEFAULT_VALUE_FOR_MouseEventsSimulationEnabled, "Mouse events simulation", "Enable mouse events dispatch along with touch events on iOS") \
    macro(MuteCameraOnMicrophoneInterruptionEnabled, muteCameraOnMicrophoneInterruptionEnabled, Bool, bool, DEFAULT_VALUE_FOR_MuteCameraOnMicrophoneInterruptionEnabled, "Mute Camera on Microphone Interruption", "Mute Camera on Microphone Interruption") \
    macro(NeedsInAppBrowserPrivacyQuirks, needsInAppBrowserPrivacyQuirks, Bool, bool, DEFAULT_VALUE_FOR_NeedsInAppBrowserPrivacyQuirks, "Needs In-App Browser Privacy Quirks", "Enable quirks needed to support In-App Browser privacy") \
    macro(NeedsSiteSpecificQuirks, needsSiteSpecificQuirks, Bool, bool, DEFAULT_VALUE_FOR_NeedsSiteSpecificQuirks, "Needs Site-Specific Quirks", "Enable site-specific quirks") \
    macro(NeedsStorageAccessFromFileURLsQuirk, needsStorageAccessFromFileURLsQuirk, Bool, bool, DEFAULT_VALUE_FOR_NeedsStorageAccessFromFileURLsQuirk, "Needs storage access from file URLs quirk", "") \
    macro(FlexFormattingContextIntegrationEnabled, flexFormattingContextIntegrationEnabled, Bool, bool, DEFAULT_VALUE_FOR_FlexFormattingContextIntegrationEnabled, "Next-generation flex layout integration (FFC)", "Enable next-generation flex layout integration (FFC)") \
    macro(InlineFormattingContextIntegrationEnabled, inlineFormattingContextIntegrationEnabled, Bool, bool, DEFAULT_VALUE_FOR_InlineFormattingContextIntegrationEnabled, "Next-generation inline layout (IFC)", "Enable next-generation inline layout (IFC)") \
    macro(NotificationEventEnabled, notificationEventEnabled, Bool, bool, DEFAULT_VALUE_FOR_NotificationEventEnabled, "NotificationEvent support", "NotificationEvent and ServiceWorkerRegistration.showNotification() support") \
    macro(NotificationsEnabled, notificationsEnabled, Bool, bool, DEFAULT_VALUE_FOR_NotificationsEnabled, "Notifications", "Enable the Notifications API") \
    macro(OffscreenCanvasInWorkersEnabled, offscreenCanvasInWorkersEnabled, Bool, bool, DEFAULT_VALUE_FOR_OffscreenCanvasInWorkersEnabled, "OffscreenCanvas in Workers", "Support for the OffscreenCanvas APIs in Workers") \
    macro(OffscreenCanvasEnabled, offscreenCanvasEnabled, Bool, bool, DEFAULT_VALUE_FOR_OffscreenCanvasEnabled, "OffscreenCanvas", "Support for the OffscreenCanvas APIs") \
    macro(OpusDecoderEnabled, opusDecoderEnabled, Bool, bool, DEFAULT_VALUE_FOR_OpusDecoderEnabled, "Opus audio decoder", "Enable Opus audio decoder") \
    macro(PageVisibilityBasedProcessSuppressionEnabled, pageVisibilityBasedProcessSuppressionEnabled, Bool, bool, DEFAULT_VALUE_FOR_PageVisibilityBasedProcessSuppressionEnabled, "Page visibility-based process suppression", "Enable page visibility-based process suppression") \
    macro(PaintTimingEnabled, paintTimingEnabled, Bool, bool, DEFAULT_VALUE_FOR_PaintTimingEnabled, "Paint Timing", "Enable PaintTiming API") \
    macro(BlobRegistryTopOriginPartitioningEnabled, blobRegistryTopOriginPartitioningEnabled, Bool, bool, DEFAULT_VALUE_FOR_BlobRegistryTopOriginPartitioningEnabled, "Partition Blob URL Registry", "Partition Blob URL Registry by Top-Level Origin") \
    macro(PerformanceNavigationTimingAPIEnabled, performanceNavigationTimingAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_PerformanceNavigationTimingAPIEnabled, "PerformanceNavigationTiming", "Enable PerformanceNavigationTiming API") \
    macro(PerformanceResourceTimingSensitivePropertiesEnabled, performanceResourceTimingSensitivePropertiesEnabled, Bool, bool, DEFAULT_VALUE_FOR_PerformanceResourceTimingSensitivePropertiesEnabled, "PerformanceResourceTiming.transferSize, encodedBodySize, and decodedBodySize", "Enable all properties of PerformanceResourceTiming API") \
    macro(PermissionsAPIEnabled, permissionsAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_PermissionsAPIEnabled, "Permissions API", "Enable Permissions API") \
    macro(PreferPageRenderingUpdatesNear60FPSEnabled, preferPageRenderingUpdatesNear60FPSEnabled, Bool, bool, DEFAULT_VALUE_FOR_PreferPageRenderingUpdatesNear60FPSEnabled, "Prefer Page Rendering Updates near 60fps", "Prefer page rendering updates near 60 frames per second rather than using the display's refresh rate") \
    macro(PreferSandboxedMediaParsing, preferSandboxedMediaParsing, Bool, bool, DEFAULT_VALUE_FOR_PreferSandboxedMediaParsing, "Prefer Sandboxed Parsing of Media", "Prefer parsing media out-of-process in a sandboxed service") \
    macro(PrivateClickMeasurementDebugModeEnabled, privateClickMeasurementDebugModeEnabled, Bool, bool, DEFAULT_VALUE_FOR_PrivateClickMeasurementDebugModeEnabled, "Private Click Measurement Debug Mode", "Enable Private Click Measurement Debug Mode") \
    macro(PrivateClickMeasurementFraudPreventionEnabled, privateClickMeasurementFraudPreventionEnabled, Bool, bool, DEFAULT_VALUE_FOR_PrivateClickMeasurementFraudPreventionEnabled, "Private Click Measurement Fraud Prevention", "Enable Private Click Measurement Fraud Prevention") \
    macro(PrivateClickMeasurementEnabled, privateClickMeasurementEnabled, Bool, bool, DEFAULT_VALUE_FOR_PrivateClickMeasurementEnabled, "Private Click Measurement", "Enable Private Click Measurement for Cross-Site Link Navigations") \
    macro(PushAPIEnabled, pushAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_PushAPIEnabled, "Push API", "Enable Push API") \
    macro(GoogleAntiFlickerOptimizationQuirkEnabled, googleAntiFlickerOptimizationQuirkEnabled, Bool, bool, DEFAULT_VALUE_FOR_GoogleAntiFlickerOptimizationQuirkEnabled, "Quirk to prevent delayed initial painting on sites using Google's Anti-Flicker optimization", "Quirk to prevent delayed initial painting on sites using Google's Anti-Flicker optimization") \
    macro(ReadableByteStreamAPIEnabled, readableByteStreamAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_ReadableByteStreamAPIEnabled, "ReadableByteStream", "Enable Readable Byte Streams") \
    macro(ReferrerPolicyAttributeEnabled, referrerPolicyAttributeEnabled, Bool, bool, DEFAULT_VALUE_FOR_ReferrerPolicyAttributeEnabled, "Referrer Policy attribute", "Enable Referrer Policy attribute") \
    macro(RemotePlaybackEnabled, remotePlaybackEnabled, Bool, bool, DEFAULT_VALUE_FOR_RemotePlaybackEnabled, "Remote Playback API", "Enable Remote Playback API") \
    macro(RemoveBackgroundEnabled, removeBackgroundEnabled, Bool, bool, DEFAULT_VALUE_FOR_RemoveBackgroundEnabled, "Remove Background", "Enable Remove Background") \
    macro(ReportingEnabled, reportingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ReportingEnabled, "Reporting API", "Enable Reporting API") \
    macro(RequestVideoFrameCallbackEnabled, requestVideoFrameCallbackEnabled, Bool, bool, DEFAULT_VALUE_FOR_RequestVideoFrameCallbackEnabled, "RequestVideoFrameCallback", "Enable RequestVideoFrameCallback API") \
    macro(RequireUAGetDisplayMediaPrompt, requireUAGetDisplayMediaPrompt, Bool, bool, DEFAULT_VALUE_FOR_RequireUAGetDisplayMediaPrompt, "Require User Agent getDisplayMedia prompt", "Require and use User Agent getDisplayMedia prompt") \
    macro(SpeakerSelectionRequiresUserGesture, speakerSelectionRequiresUserGesture, Bool, bool, DEFAULT_VALUE_FOR_SpeakerSelectionRequiresUserGesture, "Require a user gesture for speaker selection", "Require a user gesture for speaker selection") \
    macro(FullscreenRequirementForScreenOrientationLockingEnabled, fullscreenRequirementForScreenOrientationLockingEnabled, Bool, bool, DEFAULT_VALUE_FOR_FullscreenRequirementForScreenOrientationLockingEnabled, "Require being in Fullscreen to lock screen orientation", "Require being in Fullscreen to lock screen orientation") \
    macro(GetUserMediaRequiresFocus, getUserMediaRequiresFocus, Bool, bool, DEFAULT_VALUE_FOR_GetUserMediaRequiresFocus, "Require focus to start getUserMedia", "Require focus to start getUserMedia") \
    macro(ResizeObserverEnabled, resizeObserverEnabled, Bool, bool, DEFAULT_VALUE_FOR_ResizeObserverEnabled, "Resize Observer", "Enable Resize Observer support") \
    macro(ResourceLoadSchedulingEnabled, resourceLoadSchedulingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ResourceLoadSchedulingEnabled, "Resource Load Scheduling", "Network process side priority and visibility based resource load scheduling") \
    macro(ResourceUsageOverlayVisible, resourceUsageOverlayVisible, Bool, bool, DEFAULT_VALUE_FOR_ResourceUsageOverlayVisible, "Resource usage overlay", "Make resource usage overlay visible") \
    macro(SKAttributionEnabled, sKAttributionEnabled, Bool, bool, DEFAULT_VALUE_FOR_SKAttributionEnabled, "SKAttribution", "SKAttribution") \
    macro(SafeBrowsingEnabled, safeBrowsingEnabled, Bool, bool, DEFAULT_VALUE_FOR_SafeBrowsingEnabled, "Safe Browsing", "Enable Safe Browsing") \
    macro(IsSameSiteStrictEnforcementEnabled, isSameSiteStrictEnforcementEnabled, Bool, bool, DEFAULT_VALUE_FOR_IsSameSiteStrictEnforcementEnabled, "SameSite strict enforcement (ITP)", "Enable SameSite strict enforcement to mitigate bounce tracking") \
    macro(ScreenOrientationLockingAPIEnabled, screenOrientationLockingAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScreenOrientationLockingAPIEnabled, "Screen Orientation API (Locking / Unlocking)", "Enable Screen Orientation API (Locking / Unlocking)") \
    macro(ScreenOrientationAPIEnabled, screenOrientationAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScreenOrientationAPIEnabled, "Screen Orientation API", "Enable Screen Orientation API") \
    macro(ScreenWakeLockAPIEnabled, screenWakeLockAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScreenWakeLockAPIEnabled, "Screen Wake Lock API", "Enable Screen Wake Lock API") \
    macro(ScreenCaptureEnabled, screenCaptureEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScreenCaptureEnabled, "ScreenCapture", "Enable ScreenCapture") \
    macro(ScrollingPerformanceTestingEnabled, scrollingPerformanceTestingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScrollingPerformanceTestingEnabled, "Scroll Performance Testing Enabled", "Enable behaviors used by scrolling performance tests") \
    macro(ScrollToTextFragmentIndicatorEnabled, scrollToTextFragmentIndicatorEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScrollToTextFragmentIndicatorEnabled, "Scroll To Text Fragment Indicator", "Enable Scroll To Text Fragment Indicator") \
    macro(ScrollToTextFragmentEnabled, scrollToTextFragmentEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScrollToTextFragmentEnabled, "Scroll To Text Fragment", "Enable Scroll To Text Fragment") \
    macro(ScrollAnimatorEnabled, scrollAnimatorEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScrollAnimatorEnabled, "Scroll animator", "Enable scroll animator") \
    macro(SearchInputIncrementalAttributeAndSearchEventEnabled, searchInputIncrementalAttributeAndSearchEventEnabled, Bool, bool, DEFAULT_VALUE_FOR_SearchInputIncrementalAttributeAndSearchEventEnabled, "Search control incremental attribute and search event", "Enable search control incremental attribute and search event support") \
    macro(SecureContextChecksEnabled, secureContextChecksEnabled, Bool, bool, DEFAULT_VALUE_FOR_SecureContextChecksEnabled, "Secure Context Checks", "Allow access to HTTPS-only Web APIs over HTTP") \
    macro(SelectionAPIForShadowDOMEnabled, selectionAPIForShadowDOMEnabled, Bool, bool, DEFAULT_VALUE_FOR_SelectionAPIForShadowDOMEnabled, "Selection API for shadow DOM", "Enable selection API for shadow DOM") \
    macro(SelectionFlippingEnabled, selectionFlippingEnabled, Bool, bool, DEFAULT_VALUE_FOR_SelectionFlippingEnabled, "Selection Flipping", "Enable Selection Flipping") \
    macro(SendMouseEventsToDisabledFormControlsEnabled, sendMouseEventsToDisabledFormControlsEnabled, Bool, bool, DEFAULT_VALUE_FOR_SendMouseEventsToDisabledFormControlsEnabled, "Send mouse events to disabled form controls", "Send mouse events to disabled form controls") \
    macro(ServerTimingEnabled, serverTimingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ServerTimingEnabled, "Server Timing", "Enable Server Timing API") \
    macro(ServiceWorkerNavigationPreloadEnabled, serviceWorkerNavigationPreloadEnabled, Bool, bool, DEFAULT_VALUE_FOR_ServiceWorkerNavigationPreloadEnabled, "Service Worker Navigation Preload", "Enable Service Worker Navigation Preload API") \
    macro(ServiceWorkersEnabled, serviceWorkersEnabled, Bool, bool, DEFAULT_VALUE_FOR_ServiceWorkersEnabled, "Service Workers", "Enable Service Workers") \
    macro(ShapeDetection, shapeDetection, Bool, bool, DEFAULT_VALUE_FOR_ShapeDetection, "Shape Detection API", "Enable the Shape Detection API") \
    macro(SharedWorkerEnabled, sharedWorkerEnabled, Bool, bool, DEFAULT_VALUE_FOR_SharedWorkerEnabled, "SharedWorker", "Enabled SharedWorker API") \
    macro(ShowMediaStatsContextMenuItemEnabled, showMediaStatsContextMenuItemEnabled, Bool, bool, DEFAULT_VALUE_FOR_ShowMediaStatsContextMenuItemEnabled, "Show Media Stats", "Adds a 'Media Stats' context menu item to <video> when the Develop menu is enabled") \
    macro(SiteIsolationEnabled, siteIsolationEnabled, Bool, bool, DEFAULT_VALUE_FOR_SiteIsolationEnabled, "Site Isolation", "Put cross-origin iframes in a different process") \
    macro(SpeechRecognitionEnabled, speechRecognitionEnabled, Bool, bool, DEFAULT_VALUE_FOR_SpeechRecognitionEnabled, "SpeechRecognition API", "Enable SpeechRecognition of WebSpeech API") \
    macro(SpeechSynthesisAPIEnabled, speechSynthesisAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_SpeechSynthesisAPIEnabled, "SpeechSynthesis API", "SpeechSynthesis API") \
    macro(StorageAPIEstimateEnabled, storageAPIEstimateEnabled, Bool, bool, DEFAULT_VALUE_FOR_StorageAPIEstimateEnabled, "Storage API Estimate", "Enable Storage API Estimate") \
    macro(StorageAPIEnabled, storageAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_StorageAPIEnabled, "Storage API", "Enable Storage API") \
    macro(StorageAccessAPIEnabled, storageAccessAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_StorageAccessAPIEnabled, "Storage Access API", "Enable Storage Access API") \
    macro(StorageBlockingPolicy, storageBlockingPolicy, UInt32, uint32_t, DEFAULT_VALUE_FOR_StorageBlockingPolicy, "Storage Blocking Policy", "") \
    macro(ProcessSwapOnCrossSiteNavigationEnabled, processSwapOnCrossSiteNavigationEnabled, Bool, bool, DEFAULT_VALUE_FOR_ProcessSwapOnCrossSiteNavigationEnabled, "Swap Processes on Cross-Site Navigation", "Swap WebContent Processes on cross-site navigations") \
    macro(ProcessSwapOnCrossSiteWindowOpenEnabled, processSwapOnCrossSiteWindowOpenEnabled, Bool, bool, DEFAULT_VALUE_FOR_ProcessSwapOnCrossSiteWindowOpenEnabled, "Swap Processes on Cross-Site Window Open", "Swap WebContent Processes on cross-site window.open") \
    macro(SyntheticEditingCommandsEnabled, syntheticEditingCommandsEnabled, Bool, bool, DEFAULT_VALUE_FOR_SyntheticEditingCommandsEnabled, "Synthetic Editing Commands", "Enable Synthetic Editing Commands") \
    macro(ShouldTakeNearSuspendedAssertions, shouldTakeNearSuspendedAssertions, Bool, bool, DEFAULT_VALUE_FOR_ShouldTakeNearSuspendedAssertions, "Take WebKit:NearSuspended assertions on background web content processes", "Take WebKit:NearSuspended assertions on background web content processes") \
    macro(TextRecognitionInVideosEnabled, textRecognitionInVideosEnabled, Bool, bool, DEFAULT_VALUE_FOR_TextRecognitionInVideosEnabled, "Text Recognition in Videos", "Enable Text Recognition in Videos") \
    macro(ThreadedAnimationResolutionEnabled, threadedAnimationResolutionEnabled, Bool, bool, DEFAULT_VALUE_FOR_ThreadedAnimationResolutionEnabled, "Threaded animation resolution", "Run accelerated animations on a separate thread") \
    macro(TiledScrollingIndicatorVisible, tiledScrollingIndicatorVisible, Bool, bool, DEFAULT_VALUE_FOR_TiledScrollingIndicatorVisible, "Tiled scrolling indicator", "Make tiled scrolling indicator visible") \
    macro(InputTypeTimeEnabled, inputTypeTimeEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeTimeEnabled, "Time Input", "Enable input elements of type time") \
    macro(TrackConfigurationEnabled, trackConfigurationEnabled, Bool, bool, DEFAULT_VALUE_FOR_TrackConfigurationEnabled, "Track Configuration API", "Track Configuration API") \
    macro(TransformStreamAPIEnabled, transformStreamAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_TransformStreamAPIEnabled, "TransformStream API", "Enable Transform Stream API") \
    macro(UndoManagerAPIEnabled, undoManagerAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_UndoManagerAPIEnabled, "UndoManager DOM API", "Enable the UndoManager DOM API") \
    macro(UnprefixedFullscreenAPIEnabled, unprefixedFullscreenAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_UnprefixedFullscreenAPIEnabled, "Unprefixed Fullscreen API", "Enable Unprefixed Fullscreen API") \
    macro(UpgradeKnownHostsToHTTPSEnabled, upgradeKnownHostsToHTTPSEnabled, Bool, bool, DEFAULT_VALUE_FOR_UpgradeKnownHostsToHTTPSEnabled, "Upgrade known hosts to HTTPS", "Upgrade known hosts to HTTPS") \
    macro(UseARKitForModel, useARKitForModel, Bool, bool, DEFAULT_VALUE_FOR_UseARKitForModel, "Use ARKit for <model>", "Use ARKit for <model>") \
    macro(UseGeneralDirectoryForStorage, useGeneralDirectoryForStorage, Bool, bool, DEFAULT_VALUE_FOR_UseGeneralDirectoryForStorage, "Use General Directory For Storage", "Use general storage directory for IndexedDB and LocalStorage") \
    macro(UseSCContentSharingPicker, useSCContentSharingPicker, Bool, bool, DEFAULT_VALUE_FOR_UseSCContentSharingPicker, "Use SCContentSharingPicker", "Use SCContentSharingPicker when available") \
    macro(UseSceneKitForModel, useSceneKitForModel, Bool, bool, DEFAULT_VALUE_FOR_UseSceneKitForModel, "Use SceneKit for <model>", "Use SceneKit for <model>") \
    macro(UseGiantTiles, useGiantTiles, Bool, bool, DEFAULT_VALUE_FOR_UseGiantTiles, "Use giant tiles", "") \
    macro(UserActivationAPIEnabled, userActivationAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_UserActivationAPIEnabled, "User Activation API", "Enable User Activation API") \
    macro(UserGesturePromisePropagationEnabled, userGesturePromisePropagationEnabled, Bool, bool, DEFAULT_VALUE_FOR_UserGesturePromisePropagationEnabled, "UserGesture Promise Propagation", "UserGesture Promise Propagation") \
    macro(VP9SWDecoderEnabledOnBattery, vp9SWDecoderEnabledOnBattery, Bool, bool, DEFAULT_VALUE_FOR_VP9SWDecoderEnabledOnBattery, "VP9 SW decoder on battery", "Enable VP9 SW decoder on battery") \
    macro(ServiceWorkersUserGestureEnabled, serviceWorkersUserGestureEnabled, Bool, bool, DEFAULT_VALUE_FOR_ServiceWorkersUserGestureEnabled, "Validate UserGesture requirements in Service Workers", "Validate UserGesture requirements in Service Workers") \
    macro(VerifyWindowOpenUserGestureFromUIProcess, verifyWindowOpenUserGestureFromUIProcess, Bool, bool, DEFAULT_VALUE_FOR_VerifyWindowOpenUserGestureFromUIProcess, "Verify window.open user gesture", "Verifies that the user gesture for window.open came from the UI process") \
    macro(VerticalFormControlsEnabled, verticalFormControlsEnabled, Bool, bool, DEFAULT_VALUE_FOR_VerticalFormControlsEnabled, "Vertical form control support", "Enable support for form controls in vertical writing mode") \
    macro(ViewGestureDebuggingEnabled, viewGestureDebuggingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ViewGestureDebuggingEnabled, "View gesture debugging", "Enable view gesture debugging") \
    macro(VisualTranslationEnabled, visualTranslationEnabled, Bool, bool, DEFAULT_VALUE_FOR_VisualTranslationEnabled, "Visual Translation", "Enable Visual Translation") \
    macro(VisualViewportAPIEnabled, visualViewportAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_VisualViewportAPIEnabled, "Visual Viewport API", "Enable Visual Viewport API") \
    macro(VorbisDecoderEnabled, vorbisDecoderEnabled, Bool, bool, DEFAULT_VALUE_FOR_VorbisDecoderEnabled, "Vorbis audio decoder", "Enable Vorbis audio decoder") \
    macro(WebAPIStatisticsEnabled, webAPIStatisticsEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAPIStatisticsEnabled, "Web API Statistics", "Enable Web API Statistics") \
    macro(WebAPIsInShadowRealmEnabled, webAPIsInShadowRealmEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAPIsInShadowRealmEnabled, "Web APIs in ShadowRealm", "Enable Web APIs to be exposed in ShadowRealm") \
    macro(WebAnimationsCompositeOperationsEnabled, webAnimationsCompositeOperationsEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAnimationsCompositeOperationsEnabled, "Web Animations composite operations", "Support for the CompositeOperation enum and properties consuming it") \
    macro(WebAnimationsCustomEffectsEnabled, webAnimationsCustomEffectsEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAnimationsCustomEffectsEnabled, "Web Animations custom effects", "Support for the CustomEffect interface") \
    macro(WebAnimationsCustomFrameRateEnabled, webAnimationsCustomFrameRateEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAnimationsCustomFrameRateEnabled, "Web Animations custom frame rate", "Support for specifying a custom frame rate for Web Animations") \
    macro(WebAnimationsIterationCompositeEnabled, webAnimationsIterationCompositeEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAnimationsIterationCompositeEnabled, "Web Animations iteration composite", "Support for the KeyframeEffect.iterationComposite property") \
    macro(WebAnimationsMutableTimelinesEnabled, webAnimationsMutableTimelinesEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAnimationsMutableTimelinesEnabled, "Web Animations mutable timelines", "Support for setting the timeline property of an Animation object") \
    macro(WebArchiveDebugModeEnabled, webArchiveDebugModeEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebArchiveDebugModeEnabled, "Web Archive debug mode", "Enable web archive debug mode") \
    macro(WebArchiveTestingModeEnabled, webArchiveTestingModeEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebArchiveTestingModeEnabled, "Web Archive testing mode", "Enable web archive testing mode") \
    macro(WebAuthenticationEnabled, webAuthenticationEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAuthenticationEnabled, "Web Authentication", "Enable Web Authentication support") \
    macro(WebCryptoSafeCurvesEnabled, webCryptoSafeCurvesEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebCryptoSafeCurvesEnabled, "Web Crypto Safe Curves", "Enable Web Crypto Safe Curves") \
    macro(WebLocksAPIEnabled, webLocksAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebLocksAPIEnabled, "Web Locks API", "Web Locks API") \
    macro(WebShareFileAPIEnabled, webShareFileAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebShareFileAPIEnabled, "Web Share API Level 2", "Enable level 2 of Web Share API") \
    macro(WebShareEnabled, webShareEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebShareEnabled, "Web Share", "Enable support for share sheet via Web Share API") \
    macro(WebAssemblyESMIntegrationEnabled, webAssemblyESMIntegrationEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAssemblyESMIntegrationEnabled, "WebAssembly ES module integration support", "Support for allowing WebAssembly modules to integrate as ES modules") \
    macro(WebCodecsEnabled, webCodecsEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebCodecsEnabled, "WebCodecs API", "Enable WebCodecs API") \
    macro(WebCodecsAV1Enabled, webCodecsAV1Enabled, Bool, bool, DEFAULT_VALUE_FOR_WebCodecsAV1Enabled, "WebCodecs AV1 codec", "Enable WebCodecs AV1 codec") \
    macro(WebCodecsHEVCEnabled, webCodecsHEVCEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebCodecsHEVCEnabled, "WebCodecs HEVC codec", "Enable WebCodecs HEVC codec") \
    macro(WebGLDraftExtensionsEnabled, webGLDraftExtensionsEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebGLDraftExtensionsEnabled, "WebGL Draft Extensions", "Enable WebGL extensions that are still in draft status") \
    macro(WebGLTimerQueriesEnabled, webGLTimerQueriesEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebGLTimerQueriesEnabled, "WebGL Timer Queries", "Enable WebGL extensions that provide GPU timer queries") \
    macro(WebGLUsingMetal, webGLUsingMetal, Bool, bool, DEFAULT_VALUE_FOR_WebGLUsingMetal, "WebGL via Metal", "Use the Metal backend for ANGLE") \
    macro(WebGLEnabled, webGLEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebGLEnabled, "WebGL", "Enable WebGL") \
    macro(WebGPUEnabled, webGPUEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebGPUEnabled, "WebGPU", "Enable WebGPU") \
    macro(WebInspectorEngineeringSettingsAllowed, webInspectorEngineeringSettingsAllowed, Bool, bool, DEFAULT_VALUE_FOR_WebInspectorEngineeringSettingsAllowed, "WebInspector engineering settings allowed", "") \
    macro(WebRTCAV1CodecEnabled, webRTCAV1CodecEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCAV1CodecEnabled, "WebRTC AV1 codec", "Enable WebRTC AV1 codec") \
    macro(WebRTCAudioLatencyAdaptationEnabled, webRTCAudioLatencyAdaptationEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCAudioLatencyAdaptationEnabled, "WebRTC Audio Latency Adaptation", "Enable WebRTC Audio Latency Adaptation") \
    macro(WebRTCDTMFEnabled, webRTCDTMFEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCDTMFEnabled, "WebRTC DTMF", "Enable WebRTC DTMF") \
    macro(WebRTCEncodedTransformEnabled, webRTCEncodedTransformEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCEncodedTransformEnabled, "WebRTC Encoded Transform API", "Enable WebRTC Encoded Transform API") \
    macro(WebRTCH264HardwareEncoderEnabled, webRTCH264HardwareEncoderEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCH264HardwareEncoderEnabled, "WebRTC H264 Hardware encoder", "Enable H264 Hardware encoder") \
    macro(WebRTCH264LowLatencyEncoderEnabled, webRTCH264LowLatencyEncoderEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCH264LowLatencyEncoderEnabled, "WebRTC H264 LowLatency encoder", "Enable H264 LowLatency encoder") \
    macro(WebRTCH264SimulcastEnabled, webRTCH264SimulcastEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCH264SimulcastEnabled, "WebRTC H264 Simulcast", "Enable WebRTC H264 Simulcast") \
    macro(WebRTCH265CodecEnabled, webRTCH265CodecEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCH265CodecEnabled, "WebRTC H265 codec", "Enable WebRTC H265 codec") \
    macro(WebRTCMediaPipelineAdditionalLoggingEnabled, webRTCMediaPipelineAdditionalLoggingEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCMediaPipelineAdditionalLoggingEnabled, "WebRTC Media Pipeline Additional Logging", "Enable WebRTC Media Pipeline Additional Logging") \
    macro(PeerConnectionEnabled, peerConnectionEnabled, Bool, bool, DEFAULT_VALUE_FOR_PeerConnectionEnabled, "WebRTC Peer Connection", "Enable RTCPeerConnection") \
    macro(WebRTCPlatformTCPSocketsEnabled, webRTCPlatformTCPSocketsEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCPlatformTCPSocketsEnabled, "WebRTC Platform TCP Sockets", "Enable WebRTC Platform TCP Sockets") \
    macro(WebRTCPlatformUDPSocketsEnabled, webRTCPlatformUDPSocketsEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCPlatformUDPSocketsEnabled, "WebRTC Platform UDP Sockets", "Enable WebRTC Platform UDP Sockets") \
    macro(WebRTCRemoteVideoFrameEnabled, webRTCRemoteVideoFrameEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCRemoteVideoFrameEnabled, "WebRTC Remote Video Frame", "Enable WebRTC Remote Video Frame") \
    macro(WebRTCSFrameTransformEnabled, webRTCSFrameTransformEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCSFrameTransformEnabled, "WebRTC SFrame Transform API", "Enable WebRTC SFrame Transform API") \
    macro(WebRTCSocketsProxyingEnabled, webRTCSocketsProxyingEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCSocketsProxyingEnabled, "WebRTC Sockets Proxying", "Enable WebRTC Sockets Proxying") \
    macro(WebRTCVP9Profile0CodecEnabled, webRTCVP9Profile0CodecEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCVP9Profile0CodecEnabled, "WebRTC VP9 profile 0 codec", "Enable WebRTC VP9 profile 0 codec") \
    macro(WebRTCVP9Profile2CodecEnabled, webRTCVP9Profile2CodecEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCVP9Profile2CodecEnabled, "WebRTC VP9 profile 2 codec", "Enable WebRTC VP9 profile 2 codec") \
    macro(WebXRAugmentedRealityModuleEnabled, webXRAugmentedRealityModuleEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebXRAugmentedRealityModuleEnabled, "WebXR Augmented Reality Module", "Adds support for the WebXR Augmented Reality Module") \
    macro(WebXREnabled, webXREnabled, Bool, bool, DEFAULT_VALUE_FOR_WebXREnabled, "WebXR Device API", "Adds support for accessing virtual reality (VR) and augmented reality (AR) devices, including sensors and head-mounted displays, on the Web") \
    macro(WebXRGamepadsModuleEnabled, webXRGamepadsModuleEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebXRGamepadsModuleEnabled, "WebXR Gamepads Module", "Adds support for the WebXR Gamepads Module") \
    macro(WebXRHandInputModuleEnabled, webXRHandInputModuleEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebXRHandInputModuleEnabled, "WebXR Hand Input Module", "Adds support for the Hands Input Module for WebXR") \
    macro(InputTypeWeekEnabled, inputTypeWeekEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeWeekEnabled, "Week Input", "Enable input elements of type week") \
    macro(WheelEventGesturesBecomeNonBlocking, wheelEventGesturesBecomeNonBlocking, Bool, bool, DEFAULT_VALUE_FOR_WheelEventGesturesBecomeNonBlocking, "Wheel Event gestures become non-blocking", "preventDefault() is only allowed on the first wheel event in a gesture") \
    macro(PassiveWheelListenersAsDefaultOnDocument, passiveWheelListenersAsDefaultOnDocument, Bool, bool, DEFAULT_VALUE_FOR_PassiveWheelListenersAsDefaultOnDocument, "Wheel Event listeners on the root made passive", "Force wheel event listeners registered on the window, document or body to be passive") \
    macro(IsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled, isFirstPartyWebsiteDataRemovalLiveOnTestingEnabled, Bool, bool, DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled, "[ITP Live-On] 1 Hour Timeout For Non-Cookie Data Removal", "Remove all non-cookie website data after just one hour of no user interaction when Intelligent Tracking Prevention is enabled") \
    macro(IsFirstPartyWebsiteDataRemovalReproTestingEnabled, isFirstPartyWebsiteDataRemovalReproTestingEnabled, Bool, bool, DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalReproTestingEnabled, "[ITP Repro] 30 Second Timeout For Non-Cookie Data Removal", "Remove all non-cookie website data after just 30 seconds of no user interaction when Intelligent Tracking Prevention is enabled") \
    macro(InputTypeDateTimeLocalEnabled, inputTypeDateTimeLocalEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeDateTimeLocalEnabled, "datetime-local Inputs", "Enable input elements of type datetime-local") \
    macro(HTTPEquivEnabled, httpEquivEnabled, Bool, bool, DEFAULT_VALUE_FOR_HTTPEquivEnabled, "http-equiv", "Enable http-equiv attribute") \
    macro(IOSFormControlRefreshEnabled, iOSFormControlRefreshEnabled, Bool, bool, DEFAULT_VALUE_FOR_IOSFormControlRefreshEnabled, "iOS Form Control Refresh", "Enable the new appearance for form controls on iOS") \
    macro(LineHeightUnitsEnabled, lineHeightUnitsEnabled, Bool, bool, DEFAULT_VALUE_FOR_LineHeightUnitsEnabled, "lh / rlh units", "Enable the lh and rlh units") \
    macro(RequestIdleCallbackEnabled, requestIdleCallbackEnabled, Bool, bool, DEFAULT_VALUE_FOR_RequestIdleCallbackEnabled, "requestIdleCallback", "Enable requestIdleCallback support") \
    macro(CSSWordBreakAutoEnabled, cssWordBreakAutoEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSWordBreakAutoEnabled, "word-break: auto enabled", "Enables the auto value of the word-break CSS property") \
    \


#define FOR_EACH_PERSISTENT_WEBKIT_PREFERENCE(macro) \
    macro(AcceleratedCompositingEnabled, acceleratedCompositingEnabled, Bool, bool, DEFAULT_VALUE_FOR_AcceleratedCompositingEnabled, "", "") \
    macro(AcceleratedCompositingForFixedPositionEnabled, acceleratedCompositingForFixedPositionEnabled, Bool, bool, DEFAULT_VALUE_FOR_AcceleratedCompositingForFixedPositionEnabled, "", "") \
    macro(AggressiveTileRetentionEnabled, aggressiveTileRetentionEnabled, Bool, bool, DEFAULT_VALUE_FOR_AggressiveTileRetentionEnabled, "", "") \
    macro(AllowContentSecurityPolicySourceStarToMatchAnyProtocol, allowContentSecurityPolicySourceStarToMatchAnyProtocol, Bool, bool, DEFAULT_VALUE_FOR_AllowContentSecurityPolicySourceStarToMatchAnyProtocol, "", "") \
    macro(AllowCrossOriginSubresourcesToAskForCredentials, allowCrossOriginSubresourcesToAskForCredentials, Bool, bool, DEFAULT_VALUE_FOR_AllowCrossOriginSubresourcesToAskForCredentials, "", "") \
    macro(AllowDisplayOfInsecureContent, allowDisplayOfInsecureContent, Bool, bool, DEFAULT_VALUE_FOR_AllowDisplayOfInsecureContent, "", "") \
    macro(AllowFileAccessFromFileURLs, allowFileAccessFromFileURLs, Bool, bool, DEFAULT_VALUE_FOR_AllowFileAccessFromFileURLs, "", "") \
    macro(AllowMultiElementImplicitSubmission, allowMultiElementImplicitSubmission, Bool, bool, DEFAULT_VALUE_FOR_AllowMultiElementImplicitSubmission, "", "") \
    macro(AllowRunningOfInsecureContent, allowRunningOfInsecureContent, Bool, bool, DEFAULT_VALUE_FOR_AllowRunningOfInsecureContent, "", "") \
    macro(AllowSettingAnyXHRHeaderFromFileURLs, allowSettingAnyXHRHeaderFromFileURLs, Bool, bool, DEFAULT_VALUE_FOR_AllowSettingAnyXHRHeaderFromFileURLs, "", "") \
    macro(AllowsAirPlayForMediaPlayback, allowsAirPlayForMediaPlayback, Bool, bool, DEFAULT_VALUE_FOR_AllowsAirPlayForMediaPlayback, "", "") \
    macro(AllowsInlineMediaPlayback, allowsInlineMediaPlayback, Bool, bool, DEFAULT_VALUE_FOR_AllowsInlineMediaPlayback, "", "") \
    macro(AllowsInlineMediaPlaybackAfterFullscreen, allowsInlineMediaPlaybackAfterFullscreen, Bool, bool, DEFAULT_VALUE_FOR_AllowsInlineMediaPlaybackAfterFullscreen, "", "") \
    macro(AllowsPictureInPictureMediaPlayback, allowsPictureInPictureMediaPlayback, Bool, bool, DEFAULT_VALUE_FOR_AllowsPictureInPictureMediaPlayback, "", "") \
    macro(AlternateFormControlDesignEnabled, alternateFormControlDesignEnabled, Bool, bool, DEFAULT_VALUE_FOR_AlternateFormControlDesignEnabled, "", "") \
    macro(AlternateFullScreenControlDesignEnabled, alternateFullScreenControlDesignEnabled, Bool, bool, DEFAULT_VALUE_FOR_AlternateFullScreenControlDesignEnabled, "", "") \
    macro(AnimatedImageAsyncDecodingEnabled, animatedImageAsyncDecodingEnabled, Bool, bool, DEFAULT_VALUE_FOR_AnimatedImageAsyncDecodingEnabled, "", "") \
    macro(AppleMailPaginationQuirkEnabled, appleMailPaginationQuirkEnabled, Bool, bool, DEFAULT_VALUE_FOR_AppleMailPaginationQuirkEnabled, "", "") \
    macro(ApplePayCapabilityDisclosureAllowed, applePayCapabilityDisclosureAllowed, Bool, bool, DEFAULT_VALUE_FOR_ApplePayCapabilityDisclosureAllowed, "", "") \
    macro(ApplePayEnabled, applePayEnabled, Bool, bool, DEFAULT_VALUE_FOR_ApplePayEnabled, "", "") \
    macro(AsynchronousSpellCheckingEnabled, asynchronousSpellCheckingEnabled, Bool, bool, DEFAULT_VALUE_FOR_AsynchronousSpellCheckingEnabled, "", "") \
    macro(AudioControlsScaleWithPageZoom, audioControlsScaleWithPageZoom, Bool, bool, DEFAULT_VALUE_FOR_AudioControlsScaleWithPageZoom, "", "") \
    macro(AuthorAndUserStylesEnabled, authorAndUserStylesEnabled, Bool, bool, DEFAULT_VALUE_FOR_AuthorAndUserStylesEnabled, "", "") \
    macro(BackspaceKeyNavigationEnabled, backspaceKeyNavigationEnabled, Bool, bool, DEFAULT_VALUE_FOR_BackspaceKeyNavigationEnabled, "", "") \
    macro(CaretBrowsingEnabled, caretBrowsingEnabled, Bool, bool, DEFAULT_VALUE_FOR_CaretBrowsingEnabled, "", "") \
    macro(ColorFilterEnabled, colorFilterEnabled, Bool, bool, DEFAULT_VALUE_FOR_ColorFilterEnabled, "", "") \
    macro(ConstantPropertiesEnabled, constantPropertiesEnabled, Bool, bool, DEFAULT_VALUE_FOR_ConstantPropertiesEnabled, "", "") \
    macro(ContentChangeObserverEnabled, contentChangeObserverEnabled, Bool, bool, DEFAULT_VALUE_FOR_ContentChangeObserverEnabled, "", "") \
    macro(ContentDispositionAttachmentSandboxEnabled, contentDispositionAttachmentSandboxEnabled, Bool, bool, DEFAULT_VALUE_FOR_ContentDispositionAttachmentSandboxEnabled, "", "") \
    macro(ContextMenuQRCodeDetectionEnabled, contextMenuQRCodeDetectionEnabled, Bool, bool, DEFAULT_VALUE_FOR_ContextMenuQRCodeDetectionEnabled, "", "") \
    macro(CursiveFontFamily, cursiveFontFamily, String, String, DEFAULT_VALUE_FOR_CursiveFontFamily, "", "") \
    macro(DNSPrefetchingEnabled, dnsPrefetchingEnabled, Bool, bool, DEFAULT_VALUE_FOR_DNSPrefetchingEnabled, "", "") \
    macro(DOMPasteAllowed, domPasteAllowed, Bool, bool, DEFAULT_VALUE_FOR_DOMPasteAllowed, "", "") \
    macro(DataDetectorTypes, dataDetectorTypes, UInt32, uint32_t, DEFAULT_VALUE_FOR_DataDetectorTypes, "", "") \
    macro(DatabasesEnabled, databasesEnabled, Bool, bool, DEFAULT_VALUE_FOR_DatabasesEnabled, "", "") \
    macro(DefaultFixedFontSize, defaultFixedFontSize, Double, double, DEFAULT_VALUE_FOR_DefaultFixedFontSize, "", "") \
    macro(DefaultFontSize, defaultFontSize, Double, double, DEFAULT_VALUE_FOR_DefaultFontSize, "", "") \
    macro(DefaultTextEncodingName, defaultTextEncodingName, String, String, DEFAULT_VALUE_FOR_DefaultTextEncodingName, "", "") \
    macro(DeveloperExtrasEnabled, developerExtrasEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeveloperExtrasEnabled, "", "") \
    macro(DeviceHeight, deviceHeight, UInt32, uint32_t, DEFAULT_VALUE_FOR_DeviceHeight, "", "") \
    macro(DeviceOrientationEventEnabled, deviceOrientationEventEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeviceOrientationEventEnabled, "", "") \
    macro(DeviceOrientationPermissionAPIEnabled, deviceOrientationPermissionAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeviceOrientationPermissionAPIEnabled, "", "") \
    macro(DeviceWidth, deviceWidth, UInt32, uint32_t, DEFAULT_VALUE_FOR_DeviceWidth, "", "") \
    macro(DisabledAdaptationsMetaTagEnabled, disabledAdaptationsMetaTagEnabled, Bool, bool, DEFAULT_VALUE_FOR_DisabledAdaptationsMetaTagEnabled, "", "") \
    macro(DownloadAttributeEnabled, downloadAttributeEnabled, Bool, bool, DEFAULT_VALUE_FOR_DownloadAttributeEnabled, "", "") \
    macro(EditableLinkBehavior, editableLinkBehavior, UInt32, uint32_t, DEFAULT_VALUE_FOR_EditableLinkBehavior, "", "") \
    macro(EnableInheritURIQueryComponent, enableInheritURIQueryComponent, Bool, bool, DEFAULT_VALUE_FOR_EnableInheritURIQueryComponent, "", "") \
    macro(EncryptedMediaAPIEnabled, encryptedMediaAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_EncryptedMediaAPIEnabled, "", "") \
    macro(ExtensibleSSOEnabled, isExtensibleSSOEnabled, Bool, bool, DEFAULT_VALUE_FOR_ExtensibleSSOEnabled, "", "") \
    macro(FTPDirectoryTemplatePath, ftpDirectoryTemplatePath, String, String, DEFAULT_VALUE_FOR_FTPDirectoryTemplatePath, "", "") \
    macro(FantasyFontFamily, fantasyFontFamily, String, String, DEFAULT_VALUE_FOR_FantasyFontFamily, "", "") \
    macro(FixedFontFamily, fixedFontFamily, String, String, DEFAULT_VALUE_FOR_FixedFontFamily, "", "") \
    macro(ForceCompositingMode, forceCompositingMode, Bool, bool, DEFAULT_VALUE_FOR_ForceCompositingMode, "", "") \
    macro(ForceFTPDirectoryListings, forceFTPDirectoryListings, Bool, bool, DEFAULT_VALUE_FOR_ForceFTPDirectoryListings, "", "") \
    macro(ForceWebGLUsesLowPower, forceWebGLUsesLowPower, Bool, bool, DEFAULT_VALUE_FOR_ForceWebGLUsesLowPower, "", "") \
    macro(GStreamerEnabled, isGStreamerEnabled, Bool, bool, DEFAULT_VALUE_FOR_GStreamerEnabled, "", "") \
    macro(HiddenPageCSSAnimationSuspensionEnabled, hiddenPageCSSAnimationSuspensionEnabled, Bool, bool, DEFAULT_VALUE_FOR_HiddenPageCSSAnimationSuspensionEnabled, "", "") \
    macro(InactiveMediaCaptureSteamRepromptIntervalInMinutes, inactiveMediaCaptureSteamRepromptIntervalInMinutes, Double, double, DEFAULT_VALUE_FOR_InactiveMediaCaptureSteamRepromptIntervalInMinutes, "", "") \
    macro(IncompleteImageBorderEnabled, incompleteImageBorderEnabled, Bool, bool, DEFAULT_VALUE_FOR_IncompleteImageBorderEnabled, "", "") \
    macro(IncrementalPDFLoadingEnabled, incrementalPDFLoadingEnabled, Bool, bool, DEFAULT_VALUE_FOR_IncrementalPDFLoadingEnabled, "", "") \
    macro(IncrementalRenderingSuppressionTimeout, incrementalRenderingSuppressionTimeout, Double, double, DEFAULT_VALUE_FOR_IncrementalRenderingSuppressionTimeout, "", "") \
    macro(InlineMediaPlaybackRequiresPlaysInlineAttribute, inlineMediaPlaybackRequiresPlaysInlineAttribute, Bool, bool, DEFAULT_VALUE_FOR_InlineMediaPlaybackRequiresPlaysInlineAttribute, "", "") \
    macro(InspectorAttachedHeight, inspectorAttachedHeight, UInt32, uint32_t, DEFAULT_VALUE_FOR_InspectorAttachedHeight, "", "") \
    macro(InspectorAttachedWidth, inspectorAttachedWidth, UInt32, uint32_t, DEFAULT_VALUE_FOR_InspectorAttachedWidth, "", "") \
    macro(InspectorAttachmentSide, inspectorAttachmentSide, UInt32, uint32_t, DEFAULT_VALUE_FOR_InspectorAttachmentSide, "", "") \
    macro(InspectorStartsAttached, inspectorStartsAttached, Bool, bool, DEFAULT_VALUE_FOR_InspectorStartsAttached, "", "") \
    macro(InspectorWindowFrame, inspectorWindowFrame, String, String, DEFAULT_VALUE_FOR_InspectorWindowFrame, "", "") \
    macro(InteractionRegionInlinePadding, interactionRegionInlinePadding, Double, double, DEFAULT_VALUE_FOR_InteractionRegionInlinePadding, "", "") \
    macro(InteractionRegionMinimumCornerRadius, interactionRegionMinimumCornerRadius, Double, double, DEFAULT_VALUE_FOR_InteractionRegionMinimumCornerRadius, "", "") \
    macro(InterruptAudioOnPageVisibilityChangeEnabled, interruptAudioOnPageVisibilityChangeEnabled, Bool, bool, DEFAULT_VALUE_FOR_InterruptAudioOnPageVisibilityChangeEnabled, "", "") \
    macro(InterruptVideoOnPageVisibilityChangeEnabled, interruptVideoOnPageVisibilityChangeEnabled, Bool, bool, DEFAULT_VALUE_FOR_InterruptVideoOnPageVisibilityChangeEnabled, "", "") \
    macro(InvisibleAutoplayNotPermitted, invisibleAutoplayNotPermitted, Bool, bool, DEFAULT_VALUE_FOR_InvisibleAutoplayNotPermitted, "", "") \
    macro(JavaScriptCanAccessClipboard, javaScriptCanAccessClipboard, Bool, bool, DEFAULT_VALUE_FOR_JavaScriptCanAccessClipboard, "", "") \
    macro(JavaScriptCanOpenWindowsAutomatically, javaScriptCanOpenWindowsAutomatically, Bool, bool, DEFAULT_VALUE_FOR_JavaScriptCanOpenWindowsAutomatically, "", "") \
    macro(JavaScriptMarkupEnabled, javaScriptMarkupEnabled, Bool, bool, DEFAULT_VALUE_FOR_JavaScriptMarkupEnabled, "", "") \
    macro(JavaScriptRuntimeFlags, javaScriptRuntimeFlags, UInt32, uint32_t, DEFAULT_VALUE_FOR_JavaScriptRuntimeFlags, "", "") \
    macro(LargeImageAsyncDecodingEnabled, largeImageAsyncDecodingEnabled, Bool, bool, DEFAULT_VALUE_FOR_LargeImageAsyncDecodingEnabled, "", "") \
    macro(LayoutFallbackWidth, layoutFallbackWidth, UInt32, uint32_t, DEFAULT_VALUE_FOR_LayoutFallbackWidth, "", "") \
    macro(LayoutViewportHeightExpansionFactor, layoutViewportHeightExpansionFactor, Double, double, DEFAULT_VALUE_FOR_LayoutViewportHeightExpansionFactor, "", "") \
    macro(LinkPreconnect, linkPreconnect, Bool, bool, DEFAULT_VALUE_FOR_LinkPreconnect, "", "") \
    macro(LinkPreloadEnabled, linkPreloadEnabled, Bool, bool, DEFAULT_VALUE_FOR_LinkPreloadEnabled, "", "") \
    macro(LoadDeferringEnabled, loadDeferringEnabled, Bool, bool, DEFAULT_VALUE_FOR_LoadDeferringEnabled, "", "") \
    macro(LoadsImagesAutomatically, loadsImagesAutomatically, Bool, bool, DEFAULT_VALUE_FOR_LoadsImagesAutomatically, "", "") \
    macro(LongRunningMediaCaptureStreamRepromptIntervalInHours, longRunningMediaCaptureStreamRepromptIntervalInHours, Double, double, DEFAULT_VALUE_FOR_LongRunningMediaCaptureStreamRepromptIntervalInHours, "", "") \
    macro(LowPowerVideoAudioBufferSizeEnabled, lowPowerVideoAudioBufferSizeEnabled, Bool, bool, DEFAULT_VALUE_FOR_LowPowerVideoAudioBufferSizeEnabled, "", "") \
    macro(ManagedMediaSourceHighThreshold, managedMediaSourceHighThreshold, Double, double, DEFAULT_VALUE_FOR_ManagedMediaSourceHighThreshold, "", "") \
    macro(ManagedMediaSourceLowThreshold, managedMediaSourceLowThreshold, Double, double, DEFAULT_VALUE_FOR_ManagedMediaSourceLowThreshold, "", "") \
    macro(MathMLEnabled, mathMLEnabled, Bool, bool, DEFAULT_VALUE_FOR_MathMLEnabled, "", "") \
    macro(MaxParseDuration, maxParseDuration, Double, double, DEFAULT_VALUE_FOR_MaxParseDuration, "", "") \
    macro(MediaAudioCodecIDsAllowedInLockdownMode, mediaAudioCodecIDsAllowedInLockdownMode, String, String, DEFAULT_VALUE_FOR_MediaAudioCodecIDsAllowedInLockdownMode, "", "") \
    macro(MediaCapabilitiesEnabled, mediaCapabilitiesEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaCapabilitiesEnabled, "", "") \
    macro(MediaCaptionFormatTypesAllowedInLockdownMode, mediaCaptionFormatTypesAllowedInLockdownMode, String, String, DEFAULT_VALUE_FOR_MediaCaptionFormatTypesAllowedInLockdownMode, "", "") \
    macro(MediaCodecTypesAllowedInLockdownMode, mediaCodecTypesAllowedInLockdownMode, String, String, DEFAULT_VALUE_FOR_MediaCodecTypesAllowedInLockdownMode, "", "") \
    macro(MediaContainerTypesAllowedInLockdownMode, mediaContainerTypesAllowedInLockdownMode, String, String, DEFAULT_VALUE_FOR_MediaContainerTypesAllowedInLockdownMode, "", "") \
    macro(MediaContentTypesRequiringHardwareSupport, mediaContentTypesRequiringHardwareSupport, String, String, DEFAULT_VALUE_FOR_MediaContentTypesRequiringHardwareSupport, "", "") \
    macro(MediaControlsContextMenusEnabled, mediaControlsContextMenusEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaControlsContextMenusEnabled, "", "") \
    macro(MediaControlsScaleWithPageZoom, mediaControlsScaleWithPageZoom, Bool, bool, DEFAULT_VALUE_FOR_MediaControlsScaleWithPageZoom, "", "") \
    macro(MediaDataLoadsAutomatically, mediaDataLoadsAutomatically, Bool, bool, DEFAULT_VALUE_FOR_MediaDataLoadsAutomatically, "", "") \
    macro(MediaEnabled, mediaEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaEnabled, "", "") \
    macro(MediaPreferredFullscreenWidth, mediaPreferredFullscreenWidth, Double, double, DEFAULT_VALUE_FOR_MediaPreferredFullscreenWidth, "", "") \
    macro(MediaPreloadingEnabled, mediaPreloadingEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaPreloadingEnabled, "", "") \
    macro(MediaStreamEnabled, mediaStreamEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaStreamEnabled, "", "") \
    macro(MediaUserGestureInheritsFromDocument, mediaUserGestureInheritsFromDocument, Bool, bool, DEFAULT_VALUE_FOR_MediaUserGestureInheritsFromDocument, "", "") \
    macro(MediaVideoCodecIDsAllowedInLockdownMode, mediaVideoCodecIDsAllowedInLockdownMode, String, String, DEFAULT_VALUE_FOR_MediaVideoCodecIDsAllowedInLockdownMode, "", "") \
    macro(MenuItemElementEnabled, menuItemElementEnabled, Bool, bool, DEFAULT_VALUE_FOR_MenuItemElementEnabled, "", "") \
    macro(MinimumFontSize, minimumFontSize, Double, double, DEFAULT_VALUE_FOR_MinimumFontSize, "", "") \
    macro(MinimumLogicalFontSize, minimumLogicalFontSize, Double, double, DEFAULT_VALUE_FOR_MinimumLogicalFontSize, "", "") \
    macro(MinimumZoomFontSize, minimumZoomFontSize, Double, double, DEFAULT_VALUE_FOR_MinimumZoomFontSize, "", "") \
    macro(MockCaptureDevicesPromptEnabled, mockCaptureDevicesPromptEnabled, Bool, bool, DEFAULT_VALUE_FOR_MockCaptureDevicesPromptEnabled, "", "") \
    macro(MockScrollbarsControllerEnabled, mockScrollbarsControllerEnabled, Bool, bool, DEFAULT_VALUE_FOR_MockScrollbarsControllerEnabled, "", "") \
    macro(MockScrollbarsEnabled, mockScrollbarsEnabled, Bool, bool, DEFAULT_VALUE_FOR_MockScrollbarsEnabled, "", "") \
    macro(NeedsAdobeFrameReloadingQuirk, needsAdobeFrameReloadingQuirk, Bool, bool, DEFAULT_VALUE_FOR_NeedsAdobeFrameReloadingQuirk, "", "") \
    macro(NeedsFrameNameFallbackToIdQuirk, needsFrameNameFallbackToIdQuirk, Bool, bool, DEFAULT_VALUE_FOR_NeedsFrameNameFallbackToIdQuirk, "", "") \
    macro(NeedsKeyboardEventDisambiguationQuirks, needsKeyboardEventDisambiguationQuirks, Bool, bool, DEFAULT_VALUE_FOR_NeedsKeyboardEventDisambiguationQuirks, "", "") \
    macro(OfflineWebApplicationCacheEnabled, offlineWebApplicationCacheEnabled, Bool, bool, DEFAULT_VALUE_FOR_OfflineWebApplicationCacheEnabled, "", "") \
    macro(PDFPluginEnabled, pdfPluginEnabled, Bool, bool, DEFAULT_VALUE_FOR_PDFPluginEnabled, "", "") \
    macro(PassiveTouchListenersAsDefaultOnDocument, passiveTouchListenersAsDefaultOnDocument, Bool, bool, DEFAULT_VALUE_FOR_PassiveTouchListenersAsDefaultOnDocument, "", "") \
    macro(PasswordEchoDuration, passwordEchoDuration, Double, double, DEFAULT_VALUE_FOR_PasswordEchoDuration, "", "") \
    macro(PasswordEchoEnabled, passwordEchoEnabled, Bool, bool, DEFAULT_VALUE_FOR_PasswordEchoEnabled, "", "") \
    macro(PictographFontFamily, pictographFontFamily, String, String, DEFAULT_VALUE_FOR_PictographFontFamily, "", "") \
    macro(PictureInPictureAPIEnabled, pictureInPictureAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_PictureInPictureAPIEnabled, "", "") \
    macro(PitchCorrectionAlgorithm, pitchCorrectionAlgorithm, UInt32, uint32_t, DEFAULT_VALUE_FOR_PitchCorrectionAlgorithm, "", "") \
    macro(PluginsEnabled, pluginsEnabled, Bool, bool, DEFAULT_VALUE_FOR_PluginsEnabled, "", "") \
    macro(PunchOutWhiteBackgroundsInDarkMode, punchOutWhiteBackgroundsInDarkMode, Bool, bool, DEFAULT_VALUE_FOR_PunchOutWhiteBackgroundsInDarkMode, "", "") \
    macro(RequiresPageVisibilityToPlayAudio, requiresPageVisibilityToPlayAudio, Bool, bool, DEFAULT_VALUE_FOR_RequiresPageVisibilityToPlayAudio, "", "") \
    macro(RequiresUserGestureForAudioPlayback, requiresUserGestureForAudioPlayback, Bool, bool, DEFAULT_VALUE_FOR_RequiresUserGestureForAudioPlayback, "", "") \
    macro(RequiresUserGestureForMediaPlayback, requiresUserGestureForMediaPlayback, Bool, bool, DEFAULT_VALUE_FOR_RequiresUserGestureForMediaPlayback, "", "") \
    macro(RequiresUserGestureForVideoPlayback, requiresUserGestureForVideoPlayback, Bool, bool, DEFAULT_VALUE_FOR_RequiresUserGestureForVideoPlayback, "", "") \
    macro(RequiresUserGestureToLoadVideo, requiresUserGestureToLoadVideo, Bool, bool, DEFAULT_VALUE_FOR_RequiresUserGestureToLoadVideo, "", "") \
    macro(RubberBandingForSubScrollableRegionsEnabled, rubberBandingForSubScrollableRegionsEnabled, Bool, bool, DEFAULT_VALUE_FOR_RubberBandingForSubScrollableRegionsEnabled, "", "") \
    macro(SampledPageTopColorMaxDifference, sampledPageTopColorMaxDifference, Double, double, DEFAULT_VALUE_FOR_SampledPageTopColorMaxDifference, "", "") \
    macro(SampledPageTopColorMinHeight, sampledPageTopColorMinHeight, Double, double, DEFAULT_VALUE_FOR_SampledPageTopColorMinHeight, "", "") \
    macro(SansSerifFontFamily, sansSerifFontFamily, String, String, DEFAULT_VALUE_FOR_SansSerifFontFamily, "", "") \
    macro(SelectTrailingWhitespaceEnabled, selectTrailingWhitespaceEnabled, Bool, bool, DEFAULT_VALUE_FOR_SelectTrailingWhitespaceEnabled, "", "") \
    macro(SerifFontFamily, serifFontFamily, String, String, DEFAULT_VALUE_FOR_SerifFontFamily, "", "") \
    macro(ServiceControlsEnabled, serviceControlsEnabled, Bool, bool, DEFAULT_VALUE_FOR_ServiceControlsEnabled, "", "") \
    macro(ServiceWorkerEntitlementDisabledForTesting, serviceWorkerEntitlementDisabledForTesting, Bool, bool, DEFAULT_VALUE_FOR_ServiceWorkerEntitlementDisabledForTesting, "", "") \
    macro(ShouldAllowUserInstalledFonts, shouldAllowUserInstalledFonts, Bool, bool, DEFAULT_VALUE_FOR_ShouldAllowUserInstalledFonts, "", "") \
    macro(ShouldConvertInvalidURLsToBlank, shouldConvertInvalidURLsToBlank, Bool, bool, DEFAULT_VALUE_FOR_ShouldConvertInvalidURLsToBlank, "", "") \
    macro(ShouldConvertPositionStyleOnCopy, shouldConvertPositionStyleOnCopy, Bool, bool, DEFAULT_VALUE_FOR_ShouldConvertPositionStyleOnCopy, "", "") \
    macro(ShouldDecidePolicyBeforeLoadingQuickLookPreview, shouldDecidePolicyBeforeLoadingQuickLookPreview, Bool, bool, DEFAULT_VALUE_FOR_ShouldDecidePolicyBeforeLoadingQuickLookPreview, "", "") \
    macro(ShouldDisplayCaptions, shouldDisplayCaptions, Bool, bool, DEFAULT_VALUE_FOR_ShouldDisplayCaptions, "", "") \
    macro(ShouldDisplaySubtitles, shouldDisplaySubtitles, Bool, bool, DEFAULT_VALUE_FOR_ShouldDisplaySubtitles, "", "") \
    macro(ShouldDisplayTextDescriptions, shouldDisplayTextDescriptions, Bool, bool, DEFAULT_VALUE_FOR_ShouldDisplayTextDescriptions, "", "") \
    macro(ShouldEnableTextAutosizingBoost, shouldEnableTextAutosizingBoost, Bool, bool, DEFAULT_VALUE_FOR_ShouldEnableTextAutosizingBoost, "", "") \
    macro(ShouldIgnoreMetaViewport, shouldIgnoreMetaViewport, Bool, bool, DEFAULT_VALUE_FOR_ShouldIgnoreMetaViewport, "", "") \
    macro(ShouldPrintBackgrounds, shouldPrintBackgrounds, Bool, bool, DEFAULT_VALUE_FOR_ShouldPrintBackgrounds, "", "") \
    macro(ShouldRespectImageOrientation, shouldRespectImageOrientation, Bool, bool, DEFAULT_VALUE_FOR_ShouldRespectImageOrientation, "", "") \
    macro(ShouldRestrictBaseURLSchemes, shouldRestrictBaseURLSchemes, Bool, bool, DEFAULT_VALUE_FOR_ShouldRestrictBaseURLSchemes, "", "") \
    macro(ShouldSuppressTextInputFromEditingDuringProvisionalNavigation, shouldSuppressTextInputFromEditingDuringProvisionalNavigation, Bool, bool, DEFAULT_VALUE_FOR_ShouldSuppressTextInputFromEditingDuringProvisionalNavigation, "", "") \
    macro(ShouldUseServiceWorkerShortTimeout, shouldUseServiceWorkerShortTimeout, Bool, bool, DEFAULT_VALUE_FOR_ShouldUseServiceWorkerShortTimeout, "", "") \
    macro(ShowsToolTipOverTruncatedText, showsToolTipOverTruncatedText, Bool, bool, DEFAULT_VALUE_FOR_ShowsToolTipOverTruncatedText, "", "") \
    macro(ShowsURLsInToolTipsEnabled, showsURLsInToolTipsEnabled, Bool, bool, DEFAULT_VALUE_FOR_ShowsURLsInToolTipsEnabled, "", "") \
    macro(ShrinksStandaloneImagesToFit, shrinksStandaloneImagesToFit, Bool, bool, DEFAULT_VALUE_FOR_ShrinksStandaloneImagesToFit, "", "") \
    macro(SmartInsertDeleteEnabled, smartInsertDeleteEnabled, Bool, bool, DEFAULT_VALUE_FOR_SmartInsertDeleteEnabled, "", "") \
    macro(SourceBufferChangeTypeEnabled, sourceBufferChangeTypeEnabled, Bool, bool, DEFAULT_VALUE_FOR_SourceBufferChangeTypeEnabled, "", "") \
    macro(SpatialNavigationEnabled, spatialNavigationEnabled, Bool, bool, DEFAULT_VALUE_FOR_SpatialNavigationEnabled, "", "") \
    macro(Standalone, standalone, Bool, bool, DEFAULT_VALUE_FOR_Standalone, "", "") \
    macro(StandardFontFamily, standardFontFamily, String, String, DEFAULT_VALUE_FOR_StandardFontFamily, "", "") \
    macro(SuppressesIncrementalRendering, suppressesIncrementalRendering, Bool, bool, DEFAULT_VALUE_FOR_SuppressesIncrementalRendering, "", "") \
    macro(SystemLayoutDirection, systemLayoutDirection, UInt32, uint32_t, DEFAULT_VALUE_FOR_SystemLayoutDirection, "", "") \
    macro(SystemPreviewEnabled, systemPreviewEnabled, Bool, bool, DEFAULT_VALUE_FOR_SystemPreviewEnabled, "", "") \
    macro(TabsToLinks, tabsToLinks, Bool, bool, DEFAULT_VALUE_FOR_TabsToLinks, "", "") \
    macro(TelephoneNumberParsingEnabled, telephoneNumberParsingEnabled, Bool, bool, DEFAULT_VALUE_FOR_TelephoneNumberParsingEnabled, "", "") \
    macro(TemporaryTileCohortRetentionEnabled, temporaryTileCohortRetentionEnabled, Bool, bool, DEFAULT_VALUE_FOR_TemporaryTileCohortRetentionEnabled, "", "") \
    macro(TextAreasAreResizable, textAreasAreResizable, Bool, bool, DEFAULT_VALUE_FOR_TextAreasAreResizable, "", "") \
    macro(TextAutosizingEnabled, textAutosizingEnabled, Bool, bool, DEFAULT_VALUE_FOR_TextAutosizingEnabled, "", "") \
    macro(TextInteractionEnabled, textInteractionEnabled, Bool, bool, DEFAULT_VALUE_FOR_TextInteractionEnabled, "", "") \
    macro(ThreadedScrollingEnabled, threadedScrollingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ThreadedScrollingEnabled, "", "") \
    macro(TreatsAnyTextCSSLinkAsStylesheet, treatsAnyTextCSSLinkAsStylesheet, Bool, bool, DEFAULT_VALUE_FOR_TreatsAnyTextCSSLinkAsStylesheet, "", "") \
    macro(UseImageDocumentForSubframePDF, useImageDocumentForSubframePDF, Bool, bool, DEFAULT_VALUE_FOR_UseImageDocumentForSubframePDF, "", "") \
    macro(UseLegacyBackgroundSizeShorthandBehavior, useLegacyBackgroundSizeShorthandBehavior, Bool, bool, DEFAULT_VALUE_FOR_UseLegacyBackgroundSizeShorthandBehavior, "", "") \
    macro(UsePreHTML5ParserQuirks, usePreHTML5ParserQuirks, Bool, bool, DEFAULT_VALUE_FOR_UsePreHTML5ParserQuirks, "", "") \
    macro(UserInterfaceDirectionPolicy, userInterfaceDirectionPolicy, UInt32, uint32_t, DEFAULT_VALUE_FOR_UserInterfaceDirectionPolicy, "", "") \
    macro(UsesBackForwardCache, usesBackForwardCache, Bool, bool, DEFAULT_VALUE_FOR_UsesBackForwardCache, "", "") \
    macro(UsesEncodingDetector, usesEncodingDetector, Bool, bool, DEFAULT_VALUE_FOR_UsesEncodingDetector, "", "") \
    macro(VP8DecoderEnabled, vp8DecoderEnabled, Bool, bool, DEFAULT_VALUE_FOR_VP8DecoderEnabled, "", "") \
    macro(VP9DecoderEnabled, vp9DecoderEnabled, Bool, bool, DEFAULT_VALUE_FOR_VP9DecoderEnabled, "", "") \
    macro(VideoFullscreenRequiresElementFullscreen, videoFullscreenRequiresElementFullscreen, Bool, bool, DEFAULT_VALUE_FOR_VideoFullscreenRequiresElementFullscreen, "", "") \
    macro(VideoPresentationModeAPIEnabled, videoPresentationModeAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_VideoPresentationModeAPIEnabled, "", "") \
    macro(VideoQualityIncludesDisplayCompositingEnabled, videoQualityIncludesDisplayCompositingEnabled, Bool, bool, DEFAULT_VALUE_FOR_VideoQualityIncludesDisplayCompositingEnabled, "", "") \
    macro(VisibleDebugOverlayRegions, visibleDebugOverlayRegions, UInt32, uint32_t, DEFAULT_VALUE_FOR_VisibleDebugOverlayRegions, "", "") \
    macro(VisualViewportEnabled, visualViewportEnabled, Bool, bool, DEFAULT_VALUE_FOR_VisualViewportEnabled, "", "") \
    macro(WantsBalancedSetDefersLoadingBehavior, wantsBalancedSetDefersLoadingBehavior, Bool, bool, DEFAULT_VALUE_FOR_WantsBalancedSetDefersLoadingBehavior, "", "") \
    macro(WebAudioEnabled, webAudioEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAudioEnabled, "", "") \
    macro(WebMFormatReaderEnabled, webMFormatReaderEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebMFormatReaderEnabled, "", "") \
    macro(WebMParserEnabled, webMParserEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebMParserEnabled, "", "") \
    macro(WebSecurityEnabled, webSecurityEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebSecurityEnabled, "", "") \
    macro(WebSocketEnabled, webSocketEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebSocketEnabled, "", "") \
    macro(WindowFocusRestricted, windowFocusRestricted, Bool, bool, DEFAULT_VALUE_FOR_WindowFocusRestricted, "", "") \
    macro(WirelessPlaybackTargetAPIEnabled, wirelessPlaybackTargetAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_WirelessPlaybackTargetAPIEnabled, "", "") \
    macro(DirPseudoEnabled, dirPseudoEnabled, Bool, bool, DEFAULT_VALUE_FOR_DirPseudoEnabled, ":dir pseudo-class", "Enable the directionality pseudo-class :dir") \
    macro(FocusVisibleEnabled, focusVisibleEnabled, Bool, bool, DEFAULT_VALUE_FOR_FocusVisibleEnabled, ":focus-visible pseudo-class", "Enable the focus-indicated pseudo-class :focus-visible") \
    macro(HasPseudoClassEnabled, hasPseudoClassEnabled, Bool, bool, DEFAULT_VALUE_FOR_HasPseudoClassEnabled, ":has() pseudo-class", "Enable :has() pseudo-class") \
    macro(AriaReflectionForElementReferencesEnabled, ariaReflectionForElementReferencesEnabled, Bool, bool, DEFAULT_VALUE_FOR_AriaReflectionForElementReferencesEnabled, "ARIA Reflection for Element References", "Enable ARIA reflection for attributes that refer to elements") \
    macro(AVFoundationEnabled, isAVFoundationEnabled, Bool, bool, DEFAULT_VALUE_FOR_AVFoundationEnabled, "AVFoundation", "Enable AVFoundation") \
    macro(AbortSignalAnyOperationEnabled, abortSignalAnyOperationEnabled, Bool, bool, DEFAULT_VALUE_FOR_AbortSignalAnyOperationEnabled, "AbortSignal.any() API", "Enable AbortSignal.any() API") \
    macro(AccessHandleEnabled, accessHandleEnabled, Bool, bool, DEFAULT_VALUE_FOR_AccessHandleEnabled, "AccessHandle API", "Enable AccessHandle API") \
    macro(AllowMediaContentTypesRequiringHardwareSupportAsFallback, allowMediaContentTypesRequiringHardwareSupportAsFallback, Bool, bool, DEFAULT_VALUE_FOR_AllowMediaContentTypesRequiringHardwareSupportAsFallback, "Allow Media Content Types Requirining Hardware As Fallback", "Allow Media Content Types Requirining Hardware As Fallback") \
    macro(AllowWebGLInWorkers, allowWebGLInWorkers, Bool, bool, DEFAULT_VALUE_FOR_AllowWebGLInWorkers, "Allow WebGL in Web Workers", "") \
    macro(AllowTopNavigationToDataURLs, allowTopNavigationToDataURLs, Bool, bool, DEFAULT_VALUE_FOR_AllowTopNavigationToDataURLs, "Allow top navigation to data: URLs", "") \
    macro(AllowUniversalAccessFromFileURLs, allowUniversalAccessFromFileURLs, Bool, bool, DEFAULT_VALUE_FOR_AllowUniversalAccessFromFileURLs, "Allow universal access from file: URLs", "") \
    macro(AspectRatioOfImgFromWidthAndHeightEnabled, aspectRatioOfImgFromWidthAndHeightEnabled, Bool, bool, DEFAULT_VALUE_FOR_AspectRatioOfImgFromWidthAndHeightEnabled, "Aspect ratio of <img> from width and height", "Map HTML attributes width/height to the default aspect ratio of <img>") \
    macro(AsyncClipboardAPIEnabled, asyncClipboardAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_AsyncClipboardAPIEnabled, "Async clipboard API", "Enable the async clipboard API") \
    macro(AttachmentElementEnabled, attachmentElementEnabled, Bool, bool, DEFAULT_VALUE_FOR_AttachmentElementEnabled, "Attachment Element", "Allow the insertion of attachment elements") \
    macro(AttachmentWideLayoutEnabled, attachmentWideLayoutEnabled, Bool, bool, DEFAULT_VALUE_FOR_AttachmentWideLayoutEnabled, "Attachment wide-layout styling", "Use horizontal wide-layout attachment style, requires Attachment Element") \
    macro(ExtendedAudioDescriptionsEnabled, extendedAudioDescriptionsEnabled, Bool, bool, DEFAULT_VALUE_FOR_ExtendedAudioDescriptionsEnabled, "Audio descriptions for video - Extended", "Enable extended audio descriptions for video") \
    macro(AudioDescriptionsEnabled, audioDescriptionsEnabled, Bool, bool, DEFAULT_VALUE_FOR_AudioDescriptionsEnabled, "Audio descriptions for video - Standard", "Enable standard audio descriptions for video") \
    macro(DOMAudioSessionEnabled, domAudioSessionEnabled, Bool, bool, DEFAULT_VALUE_FOR_DOMAudioSessionEnabled, "AudioSession API", "Enable AudioSession API") \
    macro(BeaconAPIEnabled, beaconAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_BeaconAPIEnabled, "Beacon API", "Beacon API") \
    macro(ThirdPartyIframeRedirectBlockingEnabled, thirdPartyIframeRedirectBlockingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ThirdPartyIframeRedirectBlockingEnabled, "Block top-level redirects by third-party iframes", "Block top-level redirects by third-party iframes") \
    macro(BroadcastChannelEnabled, broadcastChannelEnabled, Bool, bool, DEFAULT_VALUE_FOR_BroadcastChannelEnabled, "BroadcastChannel API", "BroadcastChannel API") \
    macro(BroadcastChannelOriginPartitioningEnabled, broadcastChannelOriginPartitioningEnabled, Bool, bool, DEFAULT_VALUE_FOR_BroadcastChannelOriginPartitioningEnabled, "BroadcastChannel Origin Partitioning", "BroadcastChannel Origin Partitioning") \
    macro(CSS3DTransformInteroperabilityEnabled, css3DTransformInteroperabilityEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSS3DTransformInteroperabilityEnabled, "CSS 3D Transform Interoperability", "Enable 3D transform behavior that is specification-compliant but backwards incompatible") \
    macro(CSSCounterStyleAtRulesEnabled, cssCounterStyleAtRulesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSCounterStyleAtRulesEnabled, "CSS @counter-style", "Enable support for CSS @counter-style rules") \
    macro(CSSFontFaceSizeAdjustEnabled, cssFontFaceSizeAdjustEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSFontFaceSizeAdjustEnabled, "CSS @font-face size-adjust", "Enable size-adjust descriptor in @font-face") \
    macro(AccentColorEnabled, accentColorEnabled, Bool, bool, DEFAULT_VALUE_FOR_AccentColorEnabled, "CSS Accent Color", "Enable accent-color CSS property") \
    macro(AspectRatioEnabled, aspectRatioEnabled, Bool, bool, DEFAULT_VALUE_FOR_AspectRatioEnabled, "CSS Aspect Ratio", "Enable aspect-ratio CSS property") \
    macro(CSSCascadeLayersEnabled, cssCascadeLayersEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSCascadeLayersEnabled, "CSS Cascade Layers", "Enable CSS Cascade Layers") \
    macro(CSSColor4, cssColor4, Bool, bool, DEFAULT_VALUE_FOR_CSSColor4, "CSS Color 4 Color Types", "Enable support for CSS Color 4 Color Types") \
    macro(CSSContainIntrinsicSizeEnabled, cssContainIntrinsicSizeEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSContainIntrinsicSizeEnabled, "CSS Contain Intrinsic Size", "Enable contain-intrinsic-size CSS property") \
    macro(CSSContainerQueriesEnabled, cssContainerQueriesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSContainerQueriesEnabled, "CSS Container Queries", "Enable CSS Container Queries") \
    macro(CSSContainmentEnabled, cssContainmentEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSContainmentEnabled, "CSS Containment", "Enable contain CSS property") \
    macro(CSSCustomPropertiesAndValuesEnabled, cssCustomPropertiesAndValuesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSCustomPropertiesAndValuesEnabled, "CSS Custom Properties and Values API", "Enable CSS Custom Properties and Values API") \
    macro(CSSGradientInterpolationColorSpacesEnabled, cssGradientInterpolationColorSpacesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSGradientInterpolationColorSpacesEnabled, "CSS Gradient Interpolation Color Spaces", "Enable custom interpolation in CSS gradients") \
    macro(CSSGradientPremultipliedAlphaInterpolationEnabled, cssGradientPremultipliedAlphaInterpolationEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSGradientPremultipliedAlphaInterpolationEnabled, "CSS Gradient Premultiplied Alpha Interpolation", "Enable premultiplied alpha interpolated CSS gradients") \
    macro(CSSIndividualTransformPropertiesEnabled, cssIndividualTransformPropertiesEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSIndividualTransformPropertiesEnabled, "CSS Individual Transform Properties", "Support for the translate, scale and rotate CSS properties") \
    macro(MasonryEnabled, masonryEnabled, Bool, bool, DEFAULT_VALUE_FOR_MasonryEnabled, "CSS Masonry Layout", "Enable Masonry Layout for CSS Grid") \
    macro(CSSMotionPathEnabled, cssMotionPathEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSMotionPathEnabled, "CSS Motion Path", "Enable CSS Motion Path support") \
    macro(CSSNestingEnabled, cssNestingEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSNestingEnabled, "CSS Nesting", "Enable support for CSS nesting https://www.w3.org/TR/css-nesting-1/") \
    macro(OverscrollBehaviorEnabled, overscrollBehaviorEnabled, Bool, bool, DEFAULT_VALUE_FOR_OverscrollBehaviorEnabled, "CSS Overscroll Behavior", "Enable CSS overscroll-behavior") \
    macro(CSSRelativeColorSyntaxEnabled, cssRelativeColorSyntaxEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSRelativeColorSyntaxEnabled, "CSS Relative Color Syntax", "Enable support for CSS Relative Color Syntax defined in CSS Color 5") \
    macro(CSSTypedOMEnabled, cssTypedOMEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTypedOMEnabled, "CSS Typed OM", "Enable the CSS Typed OM") \
    macro(CSSColorMixEnabled, cssColorMixEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSColorMixEnabled, "CSS color-mix()", "Enable support for CSS color-mix() defined in CSS Color 5") \
    macro(CSSMarginTrimEnabled, cssMarginTrimEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSMarginTrimEnabled, "CSS margin-trim property", "Enable margin-trim CSS property") \
    macro(OverflowClipEnabled, overflowClipEnabled, Bool, bool, DEFAULT_VALUE_FOR_OverflowClipEnabled, "CSS overflow: clip support", "Enable CSS overflow: clip support") \
    macro(SubgridEnabled, subgridEnabled, Bool, bool, DEFAULT_VALUE_FOR_SubgridEnabled, "CSS subgrid support", "Enable CSS subgrid support") \
    macro(CSSTextAlignLastEnabled, cssTextAlignLastEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTextAlignLastEnabled, "CSS text-align-last property", "Enable the property text-align-last, defined in CSS Text 3") \
    macro(CSSTextBoxTrimEnabled, cssTextBoxTrimEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSTextBoxTrimEnabled, "CSS text-box-trim property", "Enable text-box-trim") \
    macro(CSSOMViewScrollingAPIEnabled, cssOMViewScrollingAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSOMViewScrollingAPIEnabled, "CSSOM View Scrolling API", "Implement standard behavior for scrollLeft, scrollTop, scrollWidth, scrollHeight, scrollTo, scrollBy and scrollingElement.") \
    macro(CSSOMViewSmoothScrollingEnabled, cssOMViewSmoothScrollingEnabled, Bool, bool, DEFAULT_VALUE_FOR_CSSOMViewSmoothScrollingEnabled, "CSSOM View Smooth Scrolling", "Enable DOM API and CSS property for 'smooth' scroll behavior") \
    macro(CacheAPIEnabled, cacheAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_CacheAPIEnabled, "Cache API", "Cache API") \
    macro(CanvasColorSpaceEnabled, canvasColorSpaceEnabled, Bool, bool, DEFAULT_VALUE_FOR_CanvasColorSpaceEnabled, "Canvas Color Spaces", "Enable use of predefined canvas color spaces") \
    macro(CanvasUsesAcceleratedDrawing, canvasUsesAcceleratedDrawing, Bool, bool, DEFAULT_VALUE_FOR_CanvasUsesAcceleratedDrawing, "Canvas uses accelerated drawing", "") \
    macro(ClearSiteDataHTTPHeaderEnabled, clearSiteDataHTTPHeaderEnabled, Bool, bool, DEFAULT_VALUE_FOR_ClearSiteDataHTTPHeaderEnabled, "Clear-Site-Data HTTP Header", "Enable Clear-Site-Data HTTP Header support") \
    macro(InputTypeColorEnabled, inputTypeColorEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeColorEnabled, "Color Inputs", "Enable input elements of type color") \
    macro(CompressionStreamEnabled, compressionStreamEnabled, Bool, bool, DEFAULT_VALUE_FOR_CompressionStreamEnabled, "Compression Stream API", "Enable Compression Stream API") \
    macro(ConstructableStylesheetsEnabled, constructableStylesheetsEnabled, Bool, bool, DEFAULT_VALUE_FOR_ConstructableStylesheetsEnabled, "Constructable Stylesheets", "Enable Constructable Stylesheets") \
    macro(CookieEnabled, cookieEnabled, Bool, bool, DEFAULT_VALUE_FOR_CookieEnabled, "Cookies Enabled", "") \
    macro(CrossOriginEmbedderPolicyEnabled, crossOriginEmbedderPolicyEnabled, Bool, bool, DEFAULT_VALUE_FOR_CrossOriginEmbedderPolicyEnabled, "Cross-Origin-Embedder-Policy (COEP) header", "Support for Cross-Origin-Embedder-Policy (COEP) header") \
    macro(CrossOriginOpenerPolicyEnabled, crossOriginOpenerPolicyEnabled, Bool, bool, DEFAULT_VALUE_FOR_CrossOriginOpenerPolicyEnabled, "Cross-Origin-Opener-Policy (COOP) header", "Support for Cross-Origin-Opener-Policy (COOP) header") \
    macro(CustomPasteboardDataEnabled, customPasteboardDataEnabled, Bool, bool, DEFAULT_VALUE_FOR_CustomPasteboardDataEnabled, "Custom pasteboard data", "Enable custom clipboard types and better security model for clipboard API.") \
    macro(DOMTimersThrottlingEnabled, domTimersThrottlingEnabled, Bool, bool, DEFAULT_VALUE_FOR_DOMTimersThrottlingEnabled, "DOM timer throttling enabled", "") \
    macro(DataTransferItemsEnabled, dataTransferItemsEnabled, Bool, bool, DEFAULT_VALUE_FOR_DataTransferItemsEnabled, "Data Transfer Items", "Enables DataTransferItem in the clipboard API") \
    macro(DataListElementEnabled, dataListElementEnabled, Bool, bool, DEFAULT_VALUE_FOR_DataListElementEnabled, "DataList Element", "Enable datalist elements") \
    macro(InputTypeDateEnabled, inputTypeDateEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeDateEnabled, "Date Input", "Enable input elements of type date") \
    macro(DateTimeInputsEditableComponentsEnabled, dateTimeInputsEditableComponentsEnabled, Bool, bool, DEFAULT_VALUE_FOR_DateTimeInputsEditableComponentsEnabled, "Date/Time inputs have editable components", "Enable multiple editable components in date/time inputs") \
    macro(DeclarativeShadowDOMEnabled, declarativeShadowDOMEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeclarativeShadowDOMEnabled, "Declarative Shadow DOM", "Enable Declarative Shadow DOM") \
    macro(DefaultARIAForCustomElementsEnabled, defaultARIAForCustomElementsEnabled, Bool, bool, DEFAULT_VALUE_FOR_DefaultARIAForCustomElementsEnabled, "Default ARIA for Custom Elements", "Enable Default ARIA for Custom Elements") \
    macro(ShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint, shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint, Bool, bool, DEFAULT_VALUE_FOR_ShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint, "Defer async scripts until DOMContentLoaded or first-paint", "Defer async scripts until DOMContentLoaded or first-paint") \
    macro(DeprecateRSAESPKCSWebCryptoEnabled, deprecateRSAESPKCSWebCryptoEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeprecateRSAESPKCSWebCryptoEnabled, "Deprecate RSAES-PKCS1-v1_5 Web Crypto", "Enable Deprecation of RSAES-PKCS1-v1_5 Web Crypto") \
    macro(DiagnosticLoggingEnabled, diagnosticLoggingEnabled, Bool, bool, DEFAULT_VALUE_FOR_DiagnosticLoggingEnabled, "Diagnostic logging enabled", "") \
    macro(DirectoryUploadEnabled, directoryUploadEnabled, Bool, bool, DEFAULT_VALUE_FOR_DirectoryUploadEnabled, "Directory Upload", "input.webkitdirectory / dataTransferItem.webkitGetAsEntry()") \
    macro(IsThirdPartyCookieBlockingDisabled, isThirdPartyCookieBlockingDisabled, Bool, bool, DEFAULT_VALUE_FOR_IsThirdPartyCookieBlockingDisabled, "Disable Full 3rd-Party Cookie Blocking (ITP)", "Disable full third-party cookie blocking when Intelligent Tracking Prevention is enabled") \
    macro(IsFirstPartyWebsiteDataRemovalDisabled, isFirstPartyWebsiteDataRemovalDisabled, Bool, bool, DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalDisabled, "Disable Removal of Non-Cookie Data After 7 Days of No User Interaction (ITP)", "Disable removal of all non-cookie website data after seven days of no user interaction when Intelligent Tracking Prevention is enabled") \
    macro(DisallowSyncXHRDuringPageDismissalEnabled, disallowSyncXHRDuringPageDismissalEnabled, Bool, bool, DEFAULT_VALUE_FOR_DisallowSyncXHRDuringPageDismissalEnabled, "Disallow sync XHR during page dismissal", "Disallow synchronous XMLHttpRequest during page dismissal") \
    macro(EmbedElementEnabled, embedElementEnabled, Bool, bool, DEFAULT_VALUE_FOR_EmbedElementEnabled, "Embed Element", "Embed Element") \
    macro(CanvasFingerprintingQuirkEnabled, canvasFingerprintingQuirkEnabled, Bool, bool, DEFAULT_VALUE_FOR_CanvasFingerprintingQuirkEnabled, "Enable Canvas fingerprinting-related quirk", "") \
    macro(LegacyEncryptedMediaAPIEnabled, legacyEncryptedMediaAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_LegacyEncryptedMediaAPIEnabled, "Enable Legacy EME API", "Enable legacy EME API") \
    macro(MediaSessionCoordinatorEnabled, mediaSessionCoordinatorEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaSessionCoordinatorEnabled, "Experimental MediaSession coordinator API", "Enable experimental MediaSession coordinator API") \
    macro(MediaSessionPlaylistEnabled, mediaSessionPlaylistEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaSessionPlaylistEnabled, "Experimental MediaSession playlist API", "Enable experimental MediaSession playlist API") \
    macro(FTPEnabled, ftpEnabled, Bool, bool, DEFAULT_VALUE_FOR_FTPEnabled, "FTP support enabled", "FTP support enabled") \
    macro(FetchAPIKeepAliveEnabled, fetchAPIKeepAliveEnabled, Bool, bool, DEFAULT_VALUE_FOR_FetchAPIKeepAliveEnabled, "Fetch API Request KeepAlive", "Enable Fetch API Request KeepAlive") \
    macro(FetchAPIEnabled, fetchAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_FetchAPIEnabled, "Fetch API", "Fetch API") \
    macro(FetchMetadataEnabled, fetchMetadataEnabled, Bool, bool, DEFAULT_VALUE_FOR_FetchMetadataEnabled, "Fetch Metadata", "Enable Fetch Metadata headers") \
    macro(FileSystemAccessEnabled, fileSystemAccessEnabled, Bool, bool, DEFAULT_VALUE_FOR_FileSystemAccessEnabled, "File System Access API", "Enable File System Access API") \
    macro(FileReaderAPIEnabled, fileReaderAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_FileReaderAPIEnabled, "FileReader API", "FileReader API") \
    macro(RequestSubmitEnabled, requestSubmitEnabled, Bool, bool, DEFAULT_VALUE_FOR_RequestSubmitEnabled, "Form requestSubmit", "Form requestSubmit method") \
    macro(FormAssociatedCustomElementsEnabled, formAssociatedCustomElementsEnabled, Bool, bool, DEFAULT_VALUE_FOR_FormAssociatedCustomElementsEnabled, "Form-associated custom elements", "Support for form-associated custom elements") \
    macro(FrameFlatteningEnabled, frameFlatteningEnabled, Bool, bool, DEFAULT_VALUE_FOR_FrameFlatteningEnabled, "Frame flattening", "Enable frame flattening, which adjusts the height of an iframe to fit its contents") \
    macro(FullScreenEnabled, fullScreenEnabled, Bool, bool, DEFAULT_VALUE_FOR_FullScreenEnabled, "Fullscreen API", "Fullscreen API") \
    macro(UseGPUProcessForCanvasRenderingEnabled, useGPUProcessForCanvasRenderingEnabled, Bool, bool, DEFAULT_VALUE_FOR_UseGPUProcessForCanvasRenderingEnabled, "GPU Process: Canvas Rendering", "Enable canvas rendering in GPU Process") \
    macro(UseGPUProcessForDOMRenderingEnabled, useGPUProcessForDOMRenderingEnabled, Bool, bool, DEFAULT_VALUE_FOR_UseGPUProcessForDOMRenderingEnabled, "GPU Process: DOM Rendering", "Enable DOM rendering in GPU Process") \
    macro(UseGPUProcessForMediaEnabled, useGPUProcessForMediaEnabled, Bool, bool, DEFAULT_VALUE_FOR_UseGPUProcessForMediaEnabled, "GPU Process: Media", "Do all media loading and playback in the GPU Process") \
    macro(UseGPUProcessForDisplayCapture, useGPUProcessForDisplayCapture, Bool, bool, DEFAULT_VALUE_FOR_UseGPUProcessForDisplayCapture, "GPU Process: Screen and Window capture", "Display capture in GPU Process") \
    macro(WebRTCPlatformCodecsInGPUProcessEnabled, webRTCPlatformCodecsInGPUProcessEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCPlatformCodecsInGPUProcessEnabled, "GPU Process: WebRTC Platform Codecs", "Enable WebRTC Platform Codecs in GPU Process") \
    macro(GamepadVibrationActuatorEnabled, gamepadVibrationActuatorEnabled, Bool, bool, DEFAULT_VALUE_FOR_GamepadVibrationActuatorEnabled, "Gamepad.vibrationActuator support", "Support for Gamepad.vibrationActuator") \
    macro(GamepadsEnabled, gamepadsEnabled, Bool, bool, DEFAULT_VALUE_FOR_GamepadsEnabled, "Gamepads", "Web Gamepad API support") \
    macro(GenericCueAPIEnabled, genericCueAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_GenericCueAPIEnabled, "Generic Text Track Cue API", "Enable Generic Text Track Cue API") \
    macro(DialogElementEnabled, dialogElementEnabled, Bool, bool, DEFAULT_VALUE_FOR_DialogElementEnabled, "HTML <dialog> element", "Enable HTML <dialog> element") \
    macro(InteractiveFormValidationEnabled, interactiveFormValidationEnabled, Bool, bool, DEFAULT_VALUE_FOR_InteractiveFormValidationEnabled, "HTML Interactive Form Validation", "HTML interactive form validation") \
    macro(InertAttributeEnabled, inertAttributeEnabled, Bool, bool, DEFAULT_VALUE_FOR_InertAttributeEnabled, "HTML inert attribute", "Enable inert attribute support") \
    macro(PopoverAttributeEnabled, popoverAttributeEnabled, Bool, bool, DEFAULT_VALUE_FOR_PopoverAttributeEnabled, "HTML popover attribute", "Enable HTML popover attribute support") \
    macro(HiddenPageDOMTimerThrottlingAutoIncreases, hiddenPageDOMTimerThrottlingAutoIncreases, Bool, bool, DEFAULT_VALUE_FOR_HiddenPageDOMTimerThrottlingAutoIncreases, "Hidden page DOM timer throttling auto-increases", "") \
    macro(HiddenPageDOMTimerThrottlingEnabled, hiddenPageDOMTimerThrottlingEnabled, Bool, bool, DEFAULT_VALUE_FOR_HiddenPageDOMTimerThrottlingEnabled, "Hidden page DOM timer throttling", "Enable hidden page DOM timer throttling") \
    macro(HyperlinkAuditingEnabled, hyperlinkAuditingEnabled, Bool, bool, DEFAULT_VALUE_FOR_HyperlinkAuditingEnabled, "Hyperlink Auditing", "Enable Hyperlink Auditing") \
    macro(ItpDebugModeEnabled, itpDebugModeEnabled, Bool, bool, DEFAULT_VALUE_FOR_ItpDebugModeEnabled, "ITP Debug Mode", "Intelligent Tracking Prevention Debug Mode") \
    macro(TextAutosizingUsesIdempotentMode, textAutosizingUsesIdempotentMode, Bool, bool, DEFAULT_VALUE_FOR_TextAutosizingUsesIdempotentMode, "Idempotent Text Autosizing", "Use idempotent text autosizing mode") \
    macro(ImageAnimationControlEnabled, imageAnimationControlEnabled, Bool, bool, DEFAULT_VALUE_FOR_ImageAnimationControlEnabled, "Image Animation Control", "Enable controls for image animations") \
    macro(ImperativeSlotAPIEnabled, imperativeSlotAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_ImperativeSlotAPIEnabled, "Imperative Slot API", "Imperative Shadow DOM Distribution API") \
    macro(IndexedDBAPIEnabled, indexedDBAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_IndexedDBAPIEnabled, "IndexedDB API", "IndexedDB API") \
    macro(IntersectionObserverEnabled, intersectionObserverEnabled, Bool, bool, DEFAULT_VALUE_FOR_IntersectionObserverEnabled, "Intersection Observer", "Enable Intersection Observer support") \
    macro(IsAccessibilityIsolatedTreeEnabled, isAccessibilityIsolatedTreeEnabled, Bool, bool, DEFAULT_VALUE_FOR_IsAccessibilityIsolatedTreeEnabled, "Isolated Accessibility Tree Mode", "Enable an accessibility hierarchy for VoiceOver that can be accessed on a secondary thread for improved performance") \
    macro(JavaScriptEnabled, javaScriptEnabled, Bool, bool, DEFAULT_VALUE_FOR_JavaScriptEnabled, "JavaScript", "Enable JavaScript") \
    macro(LazyIframeLoadingEnabled, lazyIframeLoadingEnabled, Bool, bool, DEFAULT_VALUE_FOR_LazyIframeLoadingEnabled, "Lazy iframe loading", "Enable lazy iframe loading support") \
    macro(LazyImageLoadingEnabled, lazyImageLoadingEnabled, Bool, bool, DEFAULT_VALUE_FOR_LazyImageLoadingEnabled, "Lazy image loading", "Enable lazy image loading support") \
    macro(ShowModalDialogEnabled, showModalDialogEnabled, Bool, bool, DEFAULT_VALUE_FOR_ShowModalDialogEnabled, "Legacy showModalDialog() API", "Legacy showModalDialog() API") \
    macro(LinkModulePreloadEnabled, linkModulePreloadEnabled, Bool, bool, DEFAULT_VALUE_FOR_LinkModulePreloadEnabled, "Link rel=modulepreload", "Enable Link rel=modulepreload") \
    macro(LinkPreconnectEarlyHintsEnabled, linkPreconnectEarlyHintsEnabled, Bool, bool, DEFAULT_VALUE_FOR_LinkPreconnectEarlyHintsEnabled, "Link rel=preconnect via HTTP early hints", "Enable link rel=preconnect via early hints") \
    macro(LiveRangeSelectionEnabled, liveRangeSelectionEnabled, Bool, bool, DEFAULT_VALUE_FOR_LiveRangeSelectionEnabled, "Live Ranges in Selection", "Live range behavior for ranges in the Selection object") \
    macro(LocalStorageEnabled, localStorageEnabled, Bool, bool, DEFAULT_VALUE_FOR_LocalStorageEnabled, "Local Storage", "Enable Local Storage") \
    macro(MainContentUserGestureOverrideEnabled, mainContentUserGestureOverrideEnabled, Bool, bool, DEFAULT_VALUE_FOR_MainContentUserGestureOverrideEnabled, "Main content user gesture override", "Enable main content user gesture override") \
    macro(ManagedMediaSourceEnabled, managedMediaSourceEnabled, Bool, bool, DEFAULT_VALUE_FOR_ManagedMediaSourceEnabled, "Managed Media Source API", "Managed Media Source API") \
    macro(ManagedMediaSourceNeedsAirPlay, managedMediaSourceNeedsAirPlay, Bool, bool, DEFAULT_VALUE_FOR_ManagedMediaSourceNeedsAirPlay, "Managed Media Source Requires AirPlay source", "Managed Media Source Requires AirPlay source") \
    macro(MaskWebGLStringsEnabled, maskWebGLStringsEnabled, Bool, bool, DEFAULT_VALUE_FOR_MaskWebGLStringsEnabled, "Mask WebGL Strings", "Mask WebGL Vendor, Renderer, Shader Language Strings") \
    macro(MediaCapabilitiesExtensionsEnabled, mediaCapabilitiesExtensionsEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaCapabilitiesExtensionsEnabled, "Media Capabilities Extensions", "Media Capabilities Extensions") \
    macro(MediaSessionEnabled, mediaSessionEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaSessionEnabled, "Media Session API", "Media Session API") \
    macro(MediaSourceEnabled, mediaSourceEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaSourceEnabled, "Media Source API", "Media Source API") \
    macro(MediaDevicesEnabled, mediaDevicesEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaDevicesEnabled, "Media devices", "Enable media devices") \
    macro(MediaRecorderEnabled, mediaRecorderEnabled, Bool, bool, DEFAULT_VALUE_FOR_MediaRecorderEnabled, "MediaRecorder", "MediaRecorder") \
    macro(InputTypeMonthEnabled, inputTypeMonthEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeMonthEnabled, "Month Input", "Enable input elements of type month") \
    macro(NeedsSiteSpecificQuirks, needsSiteSpecificQuirks, Bool, bool, DEFAULT_VALUE_FOR_NeedsSiteSpecificQuirks, "Needs Site-Specific Quirks", "Enable site-specific quirks") \
    macro(NeedsStorageAccessFromFileURLsQuirk, needsStorageAccessFromFileURLsQuirk, Bool, bool, DEFAULT_VALUE_FOR_NeedsStorageAccessFromFileURLsQuirk, "Needs storage access from file URLs quirk", "") \
    macro(InlineFormattingContextIntegrationEnabled, inlineFormattingContextIntegrationEnabled, Bool, bool, DEFAULT_VALUE_FOR_InlineFormattingContextIntegrationEnabled, "Next-generation inline layout (IFC)", "Enable next-generation inline layout (IFC)") \
    macro(NotificationsEnabled, notificationsEnabled, Bool, bool, DEFAULT_VALUE_FOR_NotificationsEnabled, "Notifications", "Enable the Notifications API") \
    macro(OffscreenCanvasInWorkersEnabled, offscreenCanvasInWorkersEnabled, Bool, bool, DEFAULT_VALUE_FOR_OffscreenCanvasInWorkersEnabled, "OffscreenCanvas in Workers", "Support for the OffscreenCanvas APIs in Workers") \
    macro(OffscreenCanvasEnabled, offscreenCanvasEnabled, Bool, bool, DEFAULT_VALUE_FOR_OffscreenCanvasEnabled, "OffscreenCanvas", "Support for the OffscreenCanvas APIs") \
    macro(OpusDecoderEnabled, opusDecoderEnabled, Bool, bool, DEFAULT_VALUE_FOR_OpusDecoderEnabled, "Opus audio decoder", "Enable Opus audio decoder") \
    macro(PaintTimingEnabled, paintTimingEnabled, Bool, bool, DEFAULT_VALUE_FOR_PaintTimingEnabled, "Paint Timing", "Enable PaintTiming API") \
    macro(PerformanceNavigationTimingAPIEnabled, performanceNavigationTimingAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_PerformanceNavigationTimingAPIEnabled, "PerformanceNavigationTiming", "Enable PerformanceNavigationTiming API") \
    macro(PerformanceResourceTimingSensitivePropertiesEnabled, performanceResourceTimingSensitivePropertiesEnabled, Bool, bool, DEFAULT_VALUE_FOR_PerformanceResourceTimingSensitivePropertiesEnabled, "PerformanceResourceTiming.transferSize, encodedBodySize, and decodedBodySize", "Enable all properties of PerformanceResourceTiming API") \
    macro(PermissionsAPIEnabled, permissionsAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_PermissionsAPIEnabled, "Permissions API", "Enable Permissions API") \
    macro(PreferPageRenderingUpdatesNear60FPSEnabled, preferPageRenderingUpdatesNear60FPSEnabled, Bool, bool, DEFAULT_VALUE_FOR_PreferPageRenderingUpdatesNear60FPSEnabled, "Prefer Page Rendering Updates near 60fps", "Prefer page rendering updates near 60 frames per second rather than using the display's refresh rate") \
    macro(PrivateClickMeasurementDebugModeEnabled, privateClickMeasurementDebugModeEnabled, Bool, bool, DEFAULT_VALUE_FOR_PrivateClickMeasurementDebugModeEnabled, "Private Click Measurement Debug Mode", "Enable Private Click Measurement Debug Mode") \
    macro(PrivateClickMeasurementFraudPreventionEnabled, privateClickMeasurementFraudPreventionEnabled, Bool, bool, DEFAULT_VALUE_FOR_PrivateClickMeasurementFraudPreventionEnabled, "Private Click Measurement Fraud Prevention", "Enable Private Click Measurement Fraud Prevention") \
    macro(PrivateClickMeasurementEnabled, privateClickMeasurementEnabled, Bool, bool, DEFAULT_VALUE_FOR_PrivateClickMeasurementEnabled, "Private Click Measurement", "Enable Private Click Measurement for Cross-Site Link Navigations") \
    macro(PushAPIEnabled, pushAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_PushAPIEnabled, "Push API", "Enable Push API") \
    macro(GoogleAntiFlickerOptimizationQuirkEnabled, googleAntiFlickerOptimizationQuirkEnabled, Bool, bool, DEFAULT_VALUE_FOR_GoogleAntiFlickerOptimizationQuirkEnabled, "Quirk to prevent delayed initial painting on sites using Google's Anti-Flicker optimization", "Quirk to prevent delayed initial painting on sites using Google's Anti-Flicker optimization") \
    macro(ReferrerPolicyAttributeEnabled, referrerPolicyAttributeEnabled, Bool, bool, DEFAULT_VALUE_FOR_ReferrerPolicyAttributeEnabled, "Referrer Policy attribute", "Enable Referrer Policy attribute") \
    macro(RemotePlaybackEnabled, remotePlaybackEnabled, Bool, bool, DEFAULT_VALUE_FOR_RemotePlaybackEnabled, "Remote Playback API", "Enable Remote Playback API") \
    macro(ReportingEnabled, reportingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ReportingEnabled, "Reporting API", "Enable Reporting API") \
    macro(RequestVideoFrameCallbackEnabled, requestVideoFrameCallbackEnabled, Bool, bool, DEFAULT_VALUE_FOR_RequestVideoFrameCallbackEnabled, "RequestVideoFrameCallback", "Enable RequestVideoFrameCallback API") \
    macro(FullscreenRequirementForScreenOrientationLockingEnabled, fullscreenRequirementForScreenOrientationLockingEnabled, Bool, bool, DEFAULT_VALUE_FOR_FullscreenRequirementForScreenOrientationLockingEnabled, "Require being in Fullscreen to lock screen orientation", "Require being in Fullscreen to lock screen orientation") \
    macro(ResizeObserverEnabled, resizeObserverEnabled, Bool, bool, DEFAULT_VALUE_FOR_ResizeObserverEnabled, "Resize Observer", "Enable Resize Observer support") \
    macro(SKAttributionEnabled, sKAttributionEnabled, Bool, bool, DEFAULT_VALUE_FOR_SKAttributionEnabled, "SKAttribution", "SKAttribution") \
    macro(SafeBrowsingEnabled, safeBrowsingEnabled, Bool, bool, DEFAULT_VALUE_FOR_SafeBrowsingEnabled, "Safe Browsing", "Enable Safe Browsing") \
    macro(ScreenOrientationAPIEnabled, screenOrientationAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScreenOrientationAPIEnabled, "Screen Orientation API", "Enable Screen Orientation API") \
    macro(ScreenWakeLockAPIEnabled, screenWakeLockAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScreenWakeLockAPIEnabled, "Screen Wake Lock API", "Enable Screen Wake Lock API") \
    macro(ScreenCaptureEnabled, screenCaptureEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScreenCaptureEnabled, "ScreenCapture", "Enable ScreenCapture") \
    macro(ScrollToTextFragmentIndicatorEnabled, scrollToTextFragmentIndicatorEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScrollToTextFragmentIndicatorEnabled, "Scroll To Text Fragment Indicator", "Enable Scroll To Text Fragment Indicator") \
    macro(ScrollToTextFragmentEnabled, scrollToTextFragmentEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScrollToTextFragmentEnabled, "Scroll To Text Fragment", "Enable Scroll To Text Fragment") \
    macro(ScrollAnimatorEnabled, scrollAnimatorEnabled, Bool, bool, DEFAULT_VALUE_FOR_ScrollAnimatorEnabled, "Scroll animator", "Enable scroll animator") \
    macro(SearchInputIncrementalAttributeAndSearchEventEnabled, searchInputIncrementalAttributeAndSearchEventEnabled, Bool, bool, DEFAULT_VALUE_FOR_SearchInputIncrementalAttributeAndSearchEventEnabled, "Search control incremental attribute and search event", "Enable search control incremental attribute and search event support") \
    macro(SelectionAPIForShadowDOMEnabled, selectionAPIForShadowDOMEnabled, Bool, bool, DEFAULT_VALUE_FOR_SelectionAPIForShadowDOMEnabled, "Selection API for shadow DOM", "Enable selection API for shadow DOM") \
    macro(SelectionFlippingEnabled, selectionFlippingEnabled, Bool, bool, DEFAULT_VALUE_FOR_SelectionFlippingEnabled, "Selection Flipping", "Enable Selection Flipping") \
    macro(SendMouseEventsToDisabledFormControlsEnabled, sendMouseEventsToDisabledFormControlsEnabled, Bool, bool, DEFAULT_VALUE_FOR_SendMouseEventsToDisabledFormControlsEnabled, "Send mouse events to disabled form controls", "Send mouse events to disabled form controls") \
    macro(ServerTimingEnabled, serverTimingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ServerTimingEnabled, "Server Timing", "Enable Server Timing API") \
    macro(ServiceWorkerNavigationPreloadEnabled, serviceWorkerNavigationPreloadEnabled, Bool, bool, DEFAULT_VALUE_FOR_ServiceWorkerNavigationPreloadEnabled, "Service Worker Navigation Preload", "Enable Service Worker Navigation Preload API") \
    macro(ServiceWorkersEnabled, serviceWorkersEnabled, Bool, bool, DEFAULT_VALUE_FOR_ServiceWorkersEnabled, "Service Workers", "Enable Service Workers") \
    macro(SharedWorkerEnabled, sharedWorkerEnabled, Bool, bool, DEFAULT_VALUE_FOR_SharedWorkerEnabled, "SharedWorker", "Enabled SharedWorker API") \
    macro(ShowMediaStatsContextMenuItemEnabled, showMediaStatsContextMenuItemEnabled, Bool, bool, DEFAULT_VALUE_FOR_ShowMediaStatsContextMenuItemEnabled, "Show Media Stats", "Adds a 'Media Stats' context menu item to <video> when the Develop menu is enabled") \
    macro(SpeechRecognitionEnabled, speechRecognitionEnabled, Bool, bool, DEFAULT_VALUE_FOR_SpeechRecognitionEnabled, "SpeechRecognition API", "Enable SpeechRecognition of WebSpeech API") \
    macro(SpeechSynthesisAPIEnabled, speechSynthesisAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_SpeechSynthesisAPIEnabled, "SpeechSynthesis API", "SpeechSynthesis API") \
    macro(StorageAPIEstimateEnabled, storageAPIEstimateEnabled, Bool, bool, DEFAULT_VALUE_FOR_StorageAPIEstimateEnabled, "Storage API Estimate", "Enable Storage API Estimate") \
    macro(StorageAPIEnabled, storageAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_StorageAPIEnabled, "Storage API", "Enable Storage API") \
    macro(StorageAccessAPIEnabled, storageAccessAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_StorageAccessAPIEnabled, "Storage Access API", "Enable Storage Access API") \
    macro(StorageBlockingPolicy, storageBlockingPolicy, UInt32, uint32_t, DEFAULT_VALUE_FOR_StorageBlockingPolicy, "Storage Blocking Policy", "") \
    macro(ProcessSwapOnCrossSiteNavigationEnabled, processSwapOnCrossSiteNavigationEnabled, Bool, bool, DEFAULT_VALUE_FOR_ProcessSwapOnCrossSiteNavigationEnabled, "Swap Processes on Cross-Site Navigation", "Swap WebContent Processes on cross-site navigations") \
    macro(SyntheticEditingCommandsEnabled, syntheticEditingCommandsEnabled, Bool, bool, DEFAULT_VALUE_FOR_SyntheticEditingCommandsEnabled, "Synthetic Editing Commands", "Enable Synthetic Editing Commands") \
    macro(InputTypeTimeEnabled, inputTypeTimeEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeTimeEnabled, "Time Input", "Enable input elements of type time") \
    macro(TransformStreamAPIEnabled, transformStreamAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_TransformStreamAPIEnabled, "TransformStream API", "Enable Transform Stream API") \
    macro(UnprefixedFullscreenAPIEnabled, unprefixedFullscreenAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_UnprefixedFullscreenAPIEnabled, "Unprefixed Fullscreen API", "Enable Unprefixed Fullscreen API") \
    macro(UseGiantTiles, useGiantTiles, Bool, bool, DEFAULT_VALUE_FOR_UseGiantTiles, "Use giant tiles", "") \
    macro(UserActivationAPIEnabled, userActivationAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_UserActivationAPIEnabled, "User Activation API", "Enable User Activation API") \
    macro(ViewGestureDebuggingEnabled, viewGestureDebuggingEnabled, Bool, bool, DEFAULT_VALUE_FOR_ViewGestureDebuggingEnabled, "View gesture debugging", "Enable view gesture debugging") \
    macro(VisualViewportAPIEnabled, visualViewportAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_VisualViewportAPIEnabled, "Visual Viewport API", "Enable Visual Viewport API") \
    macro(VorbisDecoderEnabled, vorbisDecoderEnabled, Bool, bool, DEFAULT_VALUE_FOR_VorbisDecoderEnabled, "Vorbis audio decoder", "Enable Vorbis audio decoder") \
    macro(WebAnimationsCompositeOperationsEnabled, webAnimationsCompositeOperationsEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAnimationsCompositeOperationsEnabled, "Web Animations composite operations", "Support for the CompositeOperation enum and properties consuming it") \
    macro(WebAnimationsIterationCompositeEnabled, webAnimationsIterationCompositeEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAnimationsIterationCompositeEnabled, "Web Animations iteration composite", "Support for the KeyframeEffect.iterationComposite property") \
    macro(WebAnimationsMutableTimelinesEnabled, webAnimationsMutableTimelinesEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAnimationsMutableTimelinesEnabled, "Web Animations mutable timelines", "Support for setting the timeline property of an Animation object") \
    macro(WebArchiveDebugModeEnabled, webArchiveDebugModeEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebArchiveDebugModeEnabled, "Web Archive debug mode", "Enable web archive debug mode") \
    macro(WebAuthenticationEnabled, webAuthenticationEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebAuthenticationEnabled, "Web Authentication", "Enable Web Authentication support") \
    macro(WebCryptoSafeCurvesEnabled, webCryptoSafeCurvesEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebCryptoSafeCurvesEnabled, "Web Crypto Safe Curves", "Enable Web Crypto Safe Curves") \
    macro(WebLocksAPIEnabled, webLocksAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebLocksAPIEnabled, "Web Locks API", "Web Locks API") \
    macro(WebShareFileAPIEnabled, webShareFileAPIEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebShareFileAPIEnabled, "Web Share API Level 2", "Enable level 2 of Web Share API") \
    macro(WebShareEnabled, webShareEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebShareEnabled, "Web Share", "Enable support for share sheet via Web Share API") \
    macro(WebCodecsEnabled, webCodecsEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebCodecsEnabled, "WebCodecs API", "Enable WebCodecs API") \
    macro(WebCodecsAV1Enabled, webCodecsAV1Enabled, Bool, bool, DEFAULT_VALUE_FOR_WebCodecsAV1Enabled, "WebCodecs AV1 codec", "Enable WebCodecs AV1 codec") \
    macro(WebCodecsHEVCEnabled, webCodecsHEVCEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebCodecsHEVCEnabled, "WebCodecs HEVC codec", "Enable WebCodecs HEVC codec") \
    macro(WebGLTimerQueriesEnabled, webGLTimerQueriesEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebGLTimerQueriesEnabled, "WebGL Timer Queries", "Enable WebGL extensions that provide GPU timer queries") \
    macro(WebGLEnabled, webGLEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebGLEnabled, "WebGL", "Enable WebGL") \
    macro(WebRTCAV1CodecEnabled, webRTCAV1CodecEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCAV1CodecEnabled, "WebRTC AV1 codec", "Enable WebRTC AV1 codec") \
    macro(WebRTCEncodedTransformEnabled, webRTCEncodedTransformEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCEncodedTransformEnabled, "WebRTC Encoded Transform API", "Enable WebRTC Encoded Transform API") \
    macro(WebRTCH265CodecEnabled, webRTCH265CodecEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCH265CodecEnabled, "WebRTC H265 codec", "Enable WebRTC H265 codec") \
    macro(PeerConnectionEnabled, peerConnectionEnabled, Bool, bool, DEFAULT_VALUE_FOR_PeerConnectionEnabled, "WebRTC Peer Connection", "Enable RTCPeerConnection") \
    macro(WebRTCVP9Profile2CodecEnabled, webRTCVP9Profile2CodecEnabled, Bool, bool, DEFAULT_VALUE_FOR_WebRTCVP9Profile2CodecEnabled, "WebRTC VP9 profile 2 codec", "Enable WebRTC VP9 profile 2 codec") \
    macro(InputTypeWeekEnabled, inputTypeWeekEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeWeekEnabled, "Week Input", "Enable input elements of type week") \
    macro(WheelEventGesturesBecomeNonBlocking, wheelEventGesturesBecomeNonBlocking, Bool, bool, DEFAULT_VALUE_FOR_WheelEventGesturesBecomeNonBlocking, "Wheel Event gestures become non-blocking", "preventDefault() is only allowed on the first wheel event in a gesture") \
    macro(PassiveWheelListenersAsDefaultOnDocument, passiveWheelListenersAsDefaultOnDocument, Bool, bool, DEFAULT_VALUE_FOR_PassiveWheelListenersAsDefaultOnDocument, "Wheel Event listeners on the root made passive", "Force wheel event listeners registered on the window, document or body to be passive") \
    macro(IsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled, isFirstPartyWebsiteDataRemovalLiveOnTestingEnabled, Bool, bool, DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled, "[ITP Live-On] 1 Hour Timeout For Non-Cookie Data Removal", "Remove all non-cookie website data after just one hour of no user interaction when Intelligent Tracking Prevention is enabled") \
    macro(IsFirstPartyWebsiteDataRemovalReproTestingEnabled, isFirstPartyWebsiteDataRemovalReproTestingEnabled, Bool, bool, DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalReproTestingEnabled, "[ITP Repro] 30 Second Timeout For Non-Cookie Data Removal", "Remove all non-cookie website data after just 30 seconds of no user interaction when Intelligent Tracking Prevention is enabled") \
    macro(InputTypeDateTimeLocalEnabled, inputTypeDateTimeLocalEnabled, Bool, bool, DEFAULT_VALUE_FOR_InputTypeDateTimeLocalEnabled, "datetime-local Inputs", "Enable input elements of type datetime-local") \
    macro(HTTPEquivEnabled, httpEquivEnabled, Bool, bool, DEFAULT_VALUE_FOR_HTTPEquivEnabled, "http-equiv", "Enable http-equiv attribute") \
    macro(LineHeightUnitsEnabled, lineHeightUnitsEnabled, Bool, bool, DEFAULT_VALUE_FOR_LineHeightUnitsEnabled, "lh / rlh units", "Enable the lh and rlh units") \
    \


#define FOR_EACH_DEFAULT_OVERRIDABLE_WEBKIT_PREFERENCE(macro) \
    macro(DeveloperExtrasEnabled, developerExtrasEnabled, Bool, bool, DEFAULT_VALUE_FOR_DeveloperExtrasEnabled, "", "") \
    macro(VisibleDebugOverlayRegions, visibleDebugOverlayRegions, UInt32, uint32_t, DEFAULT_VALUE_FOR_VisibleDebugOverlayRegions, "", "") \
    macro(CompositingBordersVisible, compositingBordersVisible, Bool, bool, DEFAULT_VALUE_FOR_CompositingBordersVisible, "Compositing borders visible", "") \
    macro(CompositingRepaintCountersVisible, compositingRepaintCountersVisible, Bool, bool, DEFAULT_VALUE_FOR_CompositingRepaintCountersVisible, "Compositing repaint counters visible", "") \
    macro(DisableScreenSizeOverride, disableScreenSizeOverride, Bool, bool, DEFAULT_VALUE_FOR_DisableScreenSizeOverride, "Disable screen size override", "") \
    macro(DisplayListDrawingEnabled, displayListDrawingEnabled, Bool, bool, DEFAULT_VALUE_FOR_DisplayListDrawingEnabled, "DisplayList Drawing", "Enable display-list drawing") \
    macro(ForceAlwaysUserScalable, forceAlwaysUserScalable, Bool, bool, DEFAULT_VALUE_FOR_ForceAlwaysUserScalable, "Force always user-scalable", "") \
    macro(AcceleratedDrawingEnabled, acceleratedDrawingEnabled, Bool, bool, DEFAULT_VALUE_FOR_AcceleratedDrawingEnabled, "GraphicsLayer accelerated drawing", "Enable GraphicsLayer accelerated drawing") \
    macro(LegacyLineLayoutVisualCoverageEnabled, legacyLineLayoutVisualCoverageEnabled, Bool, bool, DEFAULT_VALUE_FOR_LegacyLineLayoutVisualCoverageEnabled, "Legacy line layout visual coverage", "Enable legacy line layout visual coverage") \
    macro(LogsPageMessagesToSystemConsoleEnabled, logsPageMessagesToSystemConsoleEnabled, Bool, bool, DEFAULT_VALUE_FOR_LogsPageMessagesToSystemConsoleEnabled, "Log page messages to system console", "Enable logging page messages to system console") \
    macro(NeedsInAppBrowserPrivacyQuirks, needsInAppBrowserPrivacyQuirks, Bool, bool, DEFAULT_VALUE_FOR_NeedsInAppBrowserPrivacyQuirks, "Needs In-App Browser Privacy Quirks", "Enable quirks needed to support In-App Browser privacy") \
    macro(ResourceUsageOverlayVisible, resourceUsageOverlayVisible, Bool, bool, DEFAULT_VALUE_FOR_ResourceUsageOverlayVisible, "Resource usage overlay", "Make resource usage overlay visible") \
    macro(TiledScrollingIndicatorVisible, tiledScrollingIndicatorVisible, Bool, bool, DEFAULT_VALUE_FOR_TiledScrollingIndicatorVisible, "Tiled scrolling indicator", "Make tiled scrolling indicator visible") \
    macro(WebInspectorEngineeringSettingsAllowed, webInspectorEngineeringSettingsAllowed, Bool, bool, DEFAULT_VALUE_FOR_WebInspectorEngineeringSettingsAllowed, "WebInspector engineering settings allowed", "") \
    \

