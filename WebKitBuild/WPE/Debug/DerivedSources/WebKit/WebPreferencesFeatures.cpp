/*
 * THIS FILE WAS AUTOMATICALLY GENERATED, DO NOT EDIT.
 *
 * Copyright (C) 2017-2023 Apple Inc. All rights reserved.
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
#include "WebPreferences.h"

#include "WebPreferencesDefinitions.h"
#include "WebPreferencesKeys.h"
#include <wtf/ExperimentalFeatureNames.h>
#include <wtf/NeverDestroyed.h>

namespace WebKit {

const Vector<RefPtr<API::Object>>& WebPreferences::features()
{
    static NeverDestroyed<Vector<RefPtr<API::Object>>> features(std::initializer_list<RefPtr<API::Object>> {
        API::Feature::create(""""_s, "AcceleratedCompositingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AcceleratedCompositingEnabled, false),
        API::Feature::create(""""_s, "AcceleratedCompositingForFixedPositionEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AcceleratedCompositingForFixedPositionEnabled, false),
        API::Feature::create(""""_s, "AggressiveTileRetentionEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AggressiveTileRetentionEnabled, false),
        API::Feature::create(""""_s, "AllowContentSecurityPolicySourceStarToMatchAnyProtocol"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowContentSecurityPolicySourceStarToMatchAnyProtocol, false),
        API::Feature::create(""""_s, "AllowCrossOriginSubresourcesToAskForCredentials"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowCrossOriginSubresourcesToAskForCredentials, false),
        API::Feature::create(""""_s, "AllowDisplayOfInsecureContent"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowDisplayOfInsecureContent, false),
        API::Feature::create(""""_s, "AllowFileAccessFromFileURLs"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowFileAccessFromFileURLs, false),
        API::Feature::create(""""_s, "AllowMultiElementImplicitSubmission"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowMultiElementImplicitSubmission, false),
        API::Feature::create(""""_s, "AllowRunningOfInsecureContent"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowRunningOfInsecureContent, false),
        API::Feature::create(""""_s, "AllowSettingAnyXHRHeaderFromFileURLs"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowSettingAnyXHRHeaderFromFileURLs, false),
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
        API::Feature::create(""""_s, "AllowsAirPlayForMediaPlayback"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowsAirPlayForMediaPlayback, false),
#endif
        API::Feature::create(""""_s, "AllowsInlineMediaPlayback"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowsInlineMediaPlayback, false),
        API::Feature::create(""""_s, "AllowsInlineMediaPlaybackAfterFullscreen"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowsInlineMediaPlaybackAfterFullscreen, false),
        API::Feature::create(""""_s, "AllowsPictureInPictureMediaPlayback"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowsPictureInPictureMediaPlayback, false),
#if PLATFORM(IOS_FAMILY)
        API::Feature::create(""""_s, "AlternateFormControlDesignEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AlternateFormControlDesignEnabled, false),
#endif
#if PLATFORM(IOS_FAMILY)
        API::Feature::create(""""_s, "AlternateFullScreenControlDesignEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AlternateFullScreenControlDesignEnabled, false),
#endif
        API::Feature::create(""""_s, "AnimatedImageAsyncDecodingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AnimatedImageAsyncDecodingEnabled, false),
        API::Feature::create(""""_s, "AppleMailPaginationQuirkEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AppleMailPaginationQuirkEnabled, false),
#if ENABLE(APPLE_PAY)
        API::Feature::create(""""_s, "ApplePayCapabilityDisclosureAllowed"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ApplePayCapabilityDisclosureAllowed, false),
#endif
#if ENABLE(APPLE_PAY)
        API::Feature::create(""""_s, "ApplePayEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ApplePayEnabled, false),
#endif
        API::Feature::create(""""_s, "AsynchronousSpellCheckingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AsynchronousSpellCheckingEnabled, false),
        API::Feature::create(""""_s, "AudioControlsScaleWithPageZoom"_s, API::FeatureStatus::Embedder, API::FeatureCategory::Media, """"_s, DEFAULT_VALUE_FOR_AudioControlsScaleWithPageZoom, false),
        API::Feature::create(""""_s, "AuthorAndUserStylesEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AuthorAndUserStylesEnabled, false),
        API::Feature::create(""""_s, "BackspaceKeyNavigationEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_BackspaceKeyNavigationEnabled, false),
        API::Feature::create(""""_s, "CaretBrowsingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_CaretBrowsingEnabled, false),
        API::Feature::create(""""_s, "ColorFilterEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ColorFilterEnabled, false),
        API::Feature::create(""""_s, "ConstantPropertiesEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ConstantPropertiesEnabled, false),
#if ENABLE(CONTENT_CHANGE_OBSERVER)
        API::Feature::create(""""_s, "ContentChangeObserverEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ContentChangeObserverEnabled, false),
#endif
        API::Feature::create(""""_s, "ContentDispositionAttachmentSandboxEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ContentDispositionAttachmentSandboxEnabled, false),
#if ENABLE(CONTEXT_MENU_QR_CODE_DETECTION)
        API::Feature::create(""""_s, "ContextMenuQRCodeDetectionEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ContextMenuQRCodeDetectionEnabled, false),
#endif
        API::Feature::create(""""_s, "DNSPrefetchingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_DNSPrefetchingEnabled, false),
        API::Feature::create(""""_s, "DOMPasteAllowed"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_DOMPasteAllowed, false),
        API::Feature::create(""""_s, "DatabasesEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_DatabasesEnabled, false),
        API::Feature::create(""""_s, "DeveloperExtrasEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_DeveloperExtrasEnabled, false),
#if ENABLE(DEVICE_ORIENTATION)
        API::Feature::create(""""_s, "DeviceOrientationEventEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_DeviceOrientationEventEnabled, false),
#endif
#if ENABLE(DEVICE_ORIENTATION)
        API::Feature::create(""""_s, "DeviceOrientationPermissionAPIEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_DeviceOrientationPermissionAPIEnabled, false),
#endif
        API::Feature::create(""""_s, "DisabledAdaptationsMetaTagEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_DisabledAdaptationsMetaTagEnabled, false),
#if ENABLE(DOWNLOAD_ATTRIBUTE)
        API::Feature::create(""""_s, "DownloadAttributeEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_DownloadAttributeEnabled, false),
#endif
        API::Feature::create(""""_s, "EnableInheritURIQueryComponent"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_EnableInheritURIQueryComponent, false),
#if ENABLE(ENCRYPTED_MEDIA)
        API::Feature::create(""""_s, "EncryptedMediaAPIEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_EncryptedMediaAPIEnabled, false),
#endif
#if HAVE(APP_SSO)
        API::Feature::create(""""_s, "ExtensibleSSOEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ExtensibleSSOEnabled, false),
#endif
        API::Feature::create(""""_s, "ForceCompositingMode"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ForceCompositingMode, false),
        API::Feature::create(""""_s, "ForceFTPDirectoryListings"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ForceFTPDirectoryListings, false),
        API::Feature::create(""""_s, "ForceWebGLUsesLowPower"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ForceWebGLUsesLowPower, false),
#if USE(GSTREAMER)
        API::Feature::create(""""_s, "GStreamerEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_GStreamerEnabled, false),
#endif
        API::Feature::create(""""_s, "HiddenPageCSSAnimationSuspensionEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_HiddenPageCSSAnimationSuspensionEnabled, false),
        API::Feature::create(""""_s, "IncompleteImageBorderEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_IncompleteImageBorderEnabled, false),
#if HAVE(INCREMENTAL_PDF_APIS)
        API::Feature::create(""""_s, "IncrementalPDFLoadingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_IncrementalPDFLoadingEnabled, false),
#endif
        API::Feature::create(""""_s, "InlineMediaPlaybackRequiresPlaysInlineAttribute"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_InlineMediaPlaybackRequiresPlaysInlineAttribute, false),
        API::Feature::create(""""_s, "InspectorStartsAttached"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_InspectorStartsAttached, false),
#if ENABLE(MEDIA_STREAM)
        API::Feature::create(""""_s, "InterruptAudioOnPageVisibilityChangeEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_InterruptAudioOnPageVisibilityChangeEnabled, false),
#endif
#if ENABLE(MEDIA_STREAM)
        API::Feature::create(""""_s, "InterruptVideoOnPageVisibilityChangeEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_InterruptVideoOnPageVisibilityChangeEnabled, false),
#endif
        API::Feature::create(""""_s, "InvisibleAutoplayNotPermitted"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_InvisibleAutoplayNotPermitted, false),
        API::Feature::create(""""_s, "JavaScriptCanAccessClipboard"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_JavaScriptCanAccessClipboard, false),
        API::Feature::create(""""_s, "JavaScriptCanOpenWindowsAutomatically"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_JavaScriptCanOpenWindowsAutomatically, false),
        API::Feature::create(""""_s, "JavaScriptMarkupEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_JavaScriptMarkupEnabled, false),
        API::Feature::create(""""_s, "LargeImageAsyncDecodingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_LargeImageAsyncDecodingEnabled, false),
        API::Feature::create(""""_s, "LinkPreconnect"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_LinkPreconnect, false),
        API::Feature::create(""""_s, "LinkPreloadEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_LinkPreloadEnabled, false),
        API::Feature::create(""""_s, "LoadDeferringEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_LoadDeferringEnabled, false),
        API::Feature::create(""""_s, "LoadsImagesAutomatically"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_LoadsImagesAutomatically, false),
        API::Feature::create(""""_s, "LowPowerVideoAudioBufferSizeEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_LowPowerVideoAudioBufferSizeEnabled, false),
#if ENABLE(MATHML)
        API::Feature::create(""""_s, "MathMLEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MathMLEnabled, false),
#endif
        API::Feature::create(""""_s, "MediaCapabilitiesEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MediaCapabilitiesEnabled, false),
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS)
        API::Feature::create(""""_s, "MediaControlsContextMenusEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MediaControlsContextMenusEnabled, false),
#endif
        API::Feature::create(""""_s, "MediaControlsScaleWithPageZoom"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MediaControlsScaleWithPageZoom, false),
        API::Feature::create(""""_s, "MediaDataLoadsAutomatically"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MediaDataLoadsAutomatically, false),
#if ENABLE(VIDEO)
        API::Feature::create(""""_s, "MediaEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MediaEnabled, false),
#endif
        API::Feature::create(""""_s, "MediaPreloadingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MediaPreloadingEnabled, false),
#if ENABLE(MEDIA_STREAM)
        API::Feature::create(""""_s, "MediaStreamEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MediaStreamEnabled, false),
#endif
        API::Feature::create(""""_s, "MediaUserGestureInheritsFromDocument"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MediaUserGestureInheritsFromDocument, false),
        API::Feature::create(""""_s, "MenuItemElementEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MenuItemElementEnabled, false),
        API::Feature::create(""""_s, "MockCaptureDevicesPromptEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MockCaptureDevicesPromptEnabled, false),
        API::Feature::create(""""_s, "MockScrollbarsControllerEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MockScrollbarsControllerEnabled, false),
        API::Feature::create(""""_s, "MockScrollbarsEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_MockScrollbarsEnabled, false),
        API::Feature::create(""""_s, "NeedsAdobeFrameReloadingQuirk"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_NeedsAdobeFrameReloadingQuirk, false),
        API::Feature::create(""""_s, "NeedsFrameNameFallbackToIdQuirk"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_NeedsFrameNameFallbackToIdQuirk, false),
        API::Feature::create(""""_s, "NeedsKeyboardEventDisambiguationQuirks"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_NeedsKeyboardEventDisambiguationQuirks, false),
        API::Feature::create(""""_s, "OfflineWebApplicationCacheEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_OfflineWebApplicationCacheEnabled, false),
#if PLATFORM(COCOA)
        API::Feature::create(""""_s, "PDFPluginEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_PDFPluginEnabled, false),
#endif
        API::Feature::create(""""_s, "PassiveTouchListenersAsDefaultOnDocument"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_PassiveTouchListenersAsDefaultOnDocument, false),
        API::Feature::create(""""_s, "PasswordEchoEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_PasswordEchoEnabled, false),
#if ENABLE(PICTURE_IN_PICTURE_API)
        API::Feature::create(""""_s, "PictureInPictureAPIEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_PictureInPictureAPIEnabled, false),
#endif
        API::Feature::create(""""_s, "PluginsEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_PluginsEnabled, false),
        API::Feature::create(""""_s, "PunchOutWhiteBackgroundsInDarkMode"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_PunchOutWhiteBackgroundsInDarkMode, false),
        API::Feature::create(""""_s, "RequiresPageVisibilityToPlayAudio"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_RequiresPageVisibilityToPlayAudio, false),
        API::Feature::create(""""_s, "RequiresUserGestureForAudioPlayback"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_RequiresUserGestureForAudioPlayback, false),
        API::Feature::create(""""_s, "RequiresUserGestureForMediaPlayback"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_RequiresUserGestureForMediaPlayback, false),
        API::Feature::create(""""_s, "RequiresUserGestureForVideoPlayback"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_RequiresUserGestureForVideoPlayback, false),
        API::Feature::create(""""_s, "RequiresUserGestureToLoadVideo"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_RequiresUserGestureToLoadVideo, false),
#if HAVE(RUBBER_BANDING)
        API::Feature::create(""""_s, "RubberBandingForSubScrollableRegionsEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_RubberBandingForSubScrollableRegionsEnabled, false),
#endif
        API::Feature::create(""""_s, "SelectTrailingWhitespaceEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_SelectTrailingWhitespaceEnabled, false),
#if ENABLE(SERVICE_CONTROLS)
        API::Feature::create(""""_s, "ServiceControlsEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ServiceControlsEnabled, false),
#endif
#if ENABLE(SERVICE_WORKER)
        API::Feature::create(""""_s, "ServiceWorkerEntitlementDisabledForTesting"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ServiceWorkerEntitlementDisabledForTesting, false),
#endif
        API::Feature::create(""""_s, "ShouldAllowUserInstalledFonts"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldAllowUserInstalledFonts, false),
        API::Feature::create(""""_s, "ShouldConvertInvalidURLsToBlank"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldConvertInvalidURLsToBlank, false),
        API::Feature::create(""""_s, "ShouldConvertPositionStyleOnCopy"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldConvertPositionStyleOnCopy, false),
        API::Feature::create(""""_s, "ShouldDecidePolicyBeforeLoadingQuickLookPreview"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldDecidePolicyBeforeLoadingQuickLookPreview, false),
#if ENABLE(VIDEO)
        API::Feature::create(""""_s, "ShouldDisplayCaptions"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldDisplayCaptions, false),
#endif
#if ENABLE(VIDEO)
        API::Feature::create(""""_s, "ShouldDisplaySubtitles"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldDisplaySubtitles, false),
#endif
#if ENABLE(VIDEO)
        API::Feature::create(""""_s, "ShouldDisplayTextDescriptions"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldDisplayTextDescriptions, false),
#endif
#if ENABLE(TEXT_AUTOSIZING)
        API::Feature::create(""""_s, "ShouldEnableTextAutosizingBoost"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldEnableTextAutosizingBoost, false),
#endif
        API::Feature::create(""""_s, "ShouldIgnoreMetaViewport"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldIgnoreMetaViewport, false),
        API::Feature::create(""""_s, "ShouldPrintBackgrounds"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldPrintBackgrounds, false),
        API::Feature::create(""""_s, "ShouldRespectImageOrientation"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldRespectImageOrientation, false),
        API::Feature::create(""""_s, "ShouldRestrictBaseURLSchemes"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldRestrictBaseURLSchemes, false),
        API::Feature::create(""""_s, "ShouldSuppressTextInputFromEditingDuringProvisionalNavigation"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldSuppressTextInputFromEditingDuringProvisionalNavigation, false),
        API::Feature::create(""""_s, "ShouldUseServiceWorkerShortTimeout"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShouldUseServiceWorkerShortTimeout, false),
        API::Feature::create(""""_s, "ShowsToolTipOverTruncatedText"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShowsToolTipOverTruncatedText, false),
        API::Feature::create(""""_s, "ShowsURLsInToolTipsEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShowsURLsInToolTipsEnabled, false),
        API::Feature::create(""""_s, "ShrinksStandaloneImagesToFit"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ShrinksStandaloneImagesToFit, false),
        API::Feature::create(""""_s, "SmartInsertDeleteEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_SmartInsertDeleteEnabled, false),
#if ENABLE(MEDIA_SOURCE)
        API::Feature::create(""""_s, "SourceBufferChangeTypeEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_SourceBufferChangeTypeEnabled, false),
#endif
        API::Feature::create(""""_s, "SpatialNavigationEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_SpatialNavigationEnabled, false),
        API::Feature::create(""""_s, "Standalone"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_Standalone, false),
        API::Feature::create(""""_s, "SuppressesIncrementalRendering"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_SuppressesIncrementalRendering, false),
#if USE(SYSTEM_PREVIEW)
        API::Feature::create(""""_s, "SystemPreviewEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_SystemPreviewEnabled, false),
#endif
        API::Feature::create(""""_s, "TabsToLinks"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_TabsToLinks, false),
        API::Feature::create(""""_s, "TelephoneNumberParsingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_TelephoneNumberParsingEnabled, false),
        API::Feature::create(""""_s, "TemporaryTileCohortRetentionEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_TemporaryTileCohortRetentionEnabled, false),
        API::Feature::create(""""_s, "TextAreasAreResizable"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_TextAreasAreResizable, false),
#if ENABLE(TEXT_AUTOSIZING)
        API::Feature::create(""""_s, "TextAutosizingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_TextAutosizingEnabled, false),
#endif
        API::Feature::create(""""_s, "TextInteractionEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_TextInteractionEnabled, false),
        API::Feature::create(""""_s, "ThreadedScrollingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ThreadedScrollingEnabled, false),
        API::Feature::create(""""_s, "TreatsAnyTextCSSLinkAsStylesheet"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_TreatsAnyTextCSSLinkAsStylesheet, false),
        API::Feature::create(""""_s, "UseImageDocumentForSubframePDF"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_UseImageDocumentForSubframePDF, false),
        API::Feature::create(""""_s, "UseLegacyBackgroundSizeShorthandBehavior"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_UseLegacyBackgroundSizeShorthandBehavior, false),
        API::Feature::create(""""_s, "UsePreHTML5ParserQuirks"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_UsePreHTML5ParserQuirks, false),
        API::Feature::create(""""_s, "UsesBackForwardCache"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_UsesBackForwardCache, false),
        API::Feature::create(""""_s, "UsesEncodingDetector"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_UsesEncodingDetector, false),
#if ENABLE(VP9)
        API::Feature::create(""""_s, "VP8DecoderEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_VP8DecoderEnabled, false),
#endif
#if ENABLE(VP9)
        API::Feature::create(""""_s, "VP9DecoderEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_VP9DecoderEnabled, false),
#endif
#if PLATFORM(IOS_FAMILY)
        API::Feature::create(""""_s, "VideoFullscreenRequiresElementFullscreen"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_VideoFullscreenRequiresElementFullscreen, false),
#endif
        API::Feature::create(""""_s, "VideoPresentationModeAPIEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_VideoPresentationModeAPIEnabled, false),
#if ENABLE(VIDEO)
        API::Feature::create(""""_s, "VideoQualityIncludesDisplayCompositingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_VideoQualityIncludesDisplayCompositingEnabled, false),
#endif
        API::Feature::create(""""_s, "VisualViewportEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_VisualViewportEnabled, false),
        API::Feature::create(""""_s, "WantsBalancedSetDefersLoadingBehavior"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_WantsBalancedSetDefersLoadingBehavior, false),
#if ENABLE(WEB_AUDIO)
        API::Feature::create(""""_s, "WebAudioEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_WebAudioEnabled, false),
#endif
#if ENABLE(WEBM_FORMAT_READER)
        API::Feature::create(""""_s, "WebMFormatReaderEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_WebMFormatReaderEnabled, false),
#endif
#if ENABLE(MEDIA_SOURCE)
        API::Feature::create(""""_s, "WebMParserEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_WebMParserEnabled, false),
#endif
        API::Feature::create(""""_s, "WebSecurityEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_WebSecurityEnabled, false),
        API::Feature::create(""""_s, "WebSocketEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_WebSocketEnabled, false),
        API::Feature::create(""""_s, "WindowFocusRestricted"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_WindowFocusRestricted, false),
        API::Feature::create(""""_s, "WirelessPlaybackTargetAPIEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_WirelessPlaybackTargetAPIEnabled, false),
        API::Feature::create(":dir pseudo-class"""_s, "DirPseudoEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable the directionality pseudo-class :dir"""_s, DEFAULT_VALUE_FOR_DirPseudoEnabled, false),
        API::Feature::create(":focus-visible pseudo-class"""_s, "FocusVisibleEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable the focus-indicated pseudo-class :focus-visible"""_s, DEFAULT_VALUE_FOR_FocusVisibleEnabled, false),
        API::Feature::create(":has() pseudo-class"""_s, "HasPseudoClassEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable :has() pseudo-class"""_s, DEFAULT_VALUE_FOR_HasPseudoClassEnabled, false),
        API::Feature::create("@page CSS at-rule support"""_s, "PageAtRuleSupportEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::CSS, "Enable @page support"""_s, DEFAULT_VALUE_FOR_PageAtRuleSupportEnabled, false),
        API::Feature::create("ARIA Reflection for Element References"""_s, "AriaReflectionForElementReferencesEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable ARIA reflection for attributes that refer to elements"""_s, DEFAULT_VALUE_FOR_AriaReflectionForElementReferencesEnabled, false),
#if USE(AVFOUNDATION)
        API::Feature::create("AVFoundation"""_s, "AVFoundationEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable AVFoundation"""_s, DEFAULT_VALUE_FOR_AVFoundationEnabled, false),
#endif
        API::Feature::create("AbortSignal.any() API"""_s, "AbortSignalAnyOperationEnabled"_s, API::FeatureStatus::Preview, API::FeatureCategory::DOM, "Enable AbortSignal.any() API"""_s, DEFAULT_VALUE_FOR_AbortSignalAnyOperationEnabled, false),
#if USE(CORE_IMAGE)
        API::Feature::create("Accelerated Filter Rendering"""_s, "AcceleratedFiltersEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::None, "Accelerated CSS and SVG filter rendering"""_s, DEFAULT_VALUE_FOR_AcceleratedFiltersEnabled, false),
#endif
        API::Feature::create("AccessHandle API"""_s, "AccessHandleEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable AccessHandle API"""_s, DEFAULT_VALUE_FOR_AccessHandleEnabled, false),
        API::Feature::create("Additional Testing APIs for DOM Objects"""_s, "DOMTestingAPIsEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable additional testing APIs for DOM objects"""_s, DEFAULT_VALUE_FOR_DOMTestingAPIsEnabled, false),
        API::Feature::create("Allow Media Content Types Requirining Hardware As Fallback"""_s, "AllowMediaContentTypesRequiringHardwareSupportAsFallback"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Allow Media Content Types Requirining Hardware As Fallback"""_s, DEFAULT_VALUE_FOR_AllowMediaContentTypesRequiringHardwareSupportAsFallback, false),
#if PLATFORM(IOS_FAMILY)
        API::Feature::create("Allow Viewport Shrink to Fit Content"""_s, "AllowViewportShrinkToFitContent"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Allow the viewport shrink to fit content heuristic when appropriate"""_s, DEFAULT_VALUE_FOR_AllowViewportShrinkToFitContent, false),
#endif
#if ENABLE(WEBGL)
        API::Feature::create("Allow WebGL in Web Workers"""_s, "AllowWebGLInWorkers"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, """"_s, DEFAULT_VALUE_FOR_AllowWebGLInWorkers, false),
#endif
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("Allow per media element speaker device selection"""_s, "PerElementSpeakerSelectionEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Media, "Allow per media element speaker device selection"""_s, DEFAULT_VALUE_FOR_PerElementSpeakerSelectionEnabled, false),
#endif
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("Allow speaker device selection"""_s, "ExposeSpeakersEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Media, "Allow speaker device selection"""_s, DEFAULT_VALUE_FOR_ExposeSpeakersEnabled, false),
#endif
        API::Feature::create("Allow top navigation to data: URLs"""_s, "AllowTopNavigationToDataURLs"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_AllowTopNavigationToDataURLs, false),
        API::Feature::create("Allow universal access from file: URLs"""_s, "AllowUniversalAccessFromFileURLs"_s, API::FeatureStatus::Developer, API::FeatureCategory::Security, """"_s, DEFAULT_VALUE_FOR_AllowUniversalAccessFromFileURLs, false),
#if ENABLE(ALTERNATE_WEBM_PLAYER)
        API::Feature::create("Alternate WebM Player"""_s, "AlternateWebMPlayerEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::Media, "Enable Alternate WebM Player"""_s, DEFAULT_VALUE_FOR_AlternateWebMPlayerEnabled, false),
#endif
#if ENABLE(BADGING)
        API::Feature::create("App Badge"""_s, "AppBadgeEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Enable App Badge"""_s, DEFAULT_VALUE_FOR_AppBadgeEnabled, false),
#endif
#if ENABLE(APP_HIGHLIGHTS)
        API::Feature::create("App Highlights"""_s, "AppHighlightsEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::CSS, "Enable App Highlights"""_s, DEFAULT_VALUE_FOR_AppHighlightsEnabled, false),
#endif
        API::Feature::create("Aspect ratio of <img> from width and height"""_s, "AspectRatioOfImgFromWidthAndHeightEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Map HTML attributes width/height to the default aspect ratio of <img>"""_s, DEFAULT_VALUE_FOR_AspectRatioOfImgFromWidthAndHeightEnabled, false),
        API::Feature::create("Async Frame Scrolling"""_s, "AsyncFrameScrollingEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Perform frame scrolling off the main thread"""_s, DEFAULT_VALUE_FOR_AsyncFrameScrollingEnabled, false),
        API::Feature::create("Async Overflow Scrolling"""_s, "AsyncOverflowScrollingEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Perform overflow scrolling off the main thread"""_s, DEFAULT_VALUE_FOR_AsyncOverflowScrollingEnabled, false),
        API::Feature::create("Async clipboard API"""_s, "AsyncClipboardAPIEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable the async clipboard API"""_s, DEFAULT_VALUE_FOR_AsyncClipboardAPIEnabled, false),
#if ENABLE(ATTACHMENT_ELEMENT)
        API::Feature::create("Attachment Element"""_s, "AttachmentElementEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Allow the insertion of attachment elements"""_s, DEFAULT_VALUE_FOR_AttachmentElementEnabled, false),
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
        API::Feature::create("Attachment wide-layout styling"""_s, "AttachmentWideLayoutEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Use horizontal wide-layout attachment style, requires Attachment Element"""_s, DEFAULT_VALUE_FOR_AttachmentWideLayoutEnabled, false),
#endif
#if ENABLE(VIDEO)
        API::Feature::create("Audio descriptions for video - Extended"""_s, "ExtendedAudioDescriptionsEnabled"_s, API::FeatureStatus::Preview, API::FeatureCategory::Media, "Enable extended audio descriptions for video"""_s, DEFAULT_VALUE_FOR_ExtendedAudioDescriptionsEnabled, false),
#endif
#if ENABLE(VIDEO)
        API::Feature::create("Audio descriptions for video - Standard"""_s, "AudioDescriptionsEnabled"_s, API::FeatureStatus::Preview, API::FeatureCategory::Media, "Enable standard audio descriptions for video"""_s, DEFAULT_VALUE_FOR_AudioDescriptionsEnabled, false),
#endif
#if ENABLE(DOM_AUDIO_SESSION)
        API::Feature::create("AudioSession API"""_s, "DOMAudioSessionEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "Enable AudioSession API"""_s, DEFAULT_VALUE_FOR_DOMAudioSessionEnabled, false),
#endif
#if ENABLE(DOM_AUDIO_SESSION)
        API::Feature::create("AudioSession full API"""_s, "DOMAudioSessionFullEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Media, "Enable AudioSession full API"""_s, DEFAULT_VALUE_FOR_DOMAudioSessionFullEnabled, false),
#endif
        API::Feature::create("Beacon API"""_s, "BeaconAPIEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Beacon API"""_s, DEFAULT_VALUE_FOR_BeaconAPIEnabled, false),
        API::Feature::create("Block top-level redirects by third-party iframes"""_s, "ThirdPartyIframeRedirectBlockingEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Block top-level redirects by third-party iframes"""_s, DEFAULT_VALUE_FOR_ThirdPartyIframeRedirectBlockingEnabled, false),
        API::Feature::create("BroadcastChannel API"""_s, "BroadcastChannelEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "BroadcastChannel API"""_s, DEFAULT_VALUE_FOR_BroadcastChannelEnabled, false),
        API::Feature::create("BroadcastChannel Origin Partitioning"""_s, "BroadcastChannelOriginPartitioningEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "BroadcastChannel Origin Partitioning"""_s, DEFAULT_VALUE_FOR_BroadcastChannelOriginPartitioningEnabled, false),
#if ENABLE(BUILT_IN_NOTIFICATIONS)
        API::Feature::create("Built-In Web Notifications"""_s, "BuiltInNotificationsEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Enable built-in WebKit managed notifications"""_s, DEFAULT_VALUE_FOR_BuiltInNotificationsEnabled, false),
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        API::Feature::create("CG Display Lists: DOM Rendering"""_s, "UseCGDisplayListsForDOMRendering"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Use CG Display Lists for DOM rendering"""_s, DEFAULT_VALUE_FOR_UseCGDisplayListsForDOMRendering, false),
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        API::Feature::create("CG Display Lists: Image Cache"""_s, "UseCGDisplayListImageCache"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Cache and transmit surfaces out-of-line for CG Display List image buffers."""_s, DEFAULT_VALUE_FOR_UseCGDisplayListImageCache, false),
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        API::Feature::create("CG Display Lists: Replay for Testing"""_s, "ReplayCGDisplayListsIntoBackingStore"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Replay CG Display Lists into layer contents for testing"""_s, DEFAULT_VALUE_FOR_ReplayCGDisplayListsIntoBackingStore, false),
#endif
        API::Feature::create("CSS 3D Transform Interoperability"""_s, "CSS3DTransformInteroperabilityEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable 3D transform behavior that is specification-compliant but backwards incompatible"""_s, DEFAULT_VALUE_FOR_CSS3DTransformInteroperabilityEnabled, false),
        API::Feature::create("CSS @counter-style <image> symbols"""_s, "CSSCounterStyleAtRuleImageSymbolsEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable support for <image> symbols in CSS @counter-style rules"""_s, DEFAULT_VALUE_FOR_CSSCounterStyleAtRuleImageSymbolsEnabled, false),
        API::Feature::create("CSS @counter-style"""_s, "CSSCounterStyleAtRulesEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable support for CSS @counter-style rules"""_s, DEFAULT_VALUE_FOR_CSSCounterStyleAtRulesEnabled, false),
        API::Feature::create("CSS @font-face size-adjust"""_s, "CSSFontFaceSizeAdjustEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable size-adjust descriptor in @font-face"""_s, DEFAULT_VALUE_FOR_CSSFontFaceSizeAdjustEnabled, false),
        API::Feature::create("CSS Accent Color"""_s, "AccentColorEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable accent-color CSS property"""_s, DEFAULT_VALUE_FOR_AccentColorEnabled, false),
        API::Feature::create("CSS Aspect Ratio"""_s, "AspectRatioEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable aspect-ratio CSS property"""_s, DEFAULT_VALUE_FOR_AspectRatioEnabled, false),
        API::Feature::create("CSS Cascade Layers"""_s, "CSSCascadeLayersEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable CSS Cascade Layers"""_s, DEFAULT_VALUE_FOR_CSSCascadeLayersEnabled, false),
        API::Feature::create("CSS Color 4 Color Types"""_s, "CSSColor4"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable support for CSS Color 4 Color Types"""_s, DEFAULT_VALUE_FOR_CSSColor4, false),
        API::Feature::create("CSS Contain Intrinsic Size"""_s, "CSSContainIntrinsicSizeEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable contain-intrinsic-size CSS property"""_s, DEFAULT_VALUE_FOR_CSSContainIntrinsicSizeEnabled, false),
        API::Feature::create("CSS Container Queries"""_s, "CSSContainerQueriesEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable CSS Container Queries"""_s, DEFAULT_VALUE_FOR_CSSContainerQueriesEnabled, false),
        API::Feature::create("CSS Containment"""_s, "CSSContainmentEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable contain CSS property"""_s, DEFAULT_VALUE_FOR_CSSContainmentEnabled, false),
        API::Feature::create("CSS Content Visibility"""_s, "CSSContentVisibilityEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable CSS content-visibility"""_s, DEFAULT_VALUE_FOR_CSSContentVisibilityEnabled, false),
        API::Feature::create("CSS Custom Properties and Values API"""_s, "CSSCustomPropertiesAndValuesEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable CSS Custom Properties and Values API"""_s, DEFAULT_VALUE_FOR_CSSCustomPropertiesAndValuesEnabled, false),
        API::Feature::create("CSS Gradient Interpolation Color Spaces"""_s, "CSSGradientInterpolationColorSpacesEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable custom interpolation in CSS gradients"""_s, DEFAULT_VALUE_FOR_CSSGradientInterpolationColorSpacesEnabled, false),
        API::Feature::create("CSS Gradient Premultiplied Alpha Interpolation"""_s, "CSSGradientPremultipliedAlphaInterpolationEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable premultiplied alpha interpolated CSS gradients"""_s, DEFAULT_VALUE_FOR_CSSGradientPremultipliedAlphaInterpolationEnabled, false),
        API::Feature::create("CSS Individual Transform Properties"""_s, "CSSIndividualTransformPropertiesEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Support for the translate, scale and rotate CSS properties"""_s, DEFAULT_VALUE_FOR_CSSIndividualTransformPropertiesEnabled, false),
        API::Feature::create("CSS Input Security"""_s, "CSSInputSecurityEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable input-security CSS property"""_s, DEFAULT_VALUE_FOR_CSSInputSecurityEnabled, false),
        API::Feature::create("CSS Masonry Layout"""_s, "MasonryEnabled"_s, API::FeatureStatus::Preview, API::FeatureCategory::CSS, "Enable Masonry Layout for CSS Grid"""_s, DEFAULT_VALUE_FOR_MasonryEnabled, false),
        API::Feature::create("CSS Motion Path"""_s, "CSSMotionPathEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable CSS Motion Path support"""_s, DEFAULT_VALUE_FOR_CSSMotionPathEnabled, false),
        API::Feature::create("CSS Nesting"""_s, "CSSNestingEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable support for CSS nesting https://www.w3.org/TR/css-nesting-1/"""_s, DEFAULT_VALUE_FOR_CSSNestingEnabled, false),
        API::Feature::create("CSS Overscroll Behavior"""_s, "OverscrollBehaviorEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable CSS overscroll-behavior"""_s, DEFAULT_VALUE_FOR_OverscrollBehaviorEnabled, false),
#if ENABLE(CSS_PAINTING_API)
        API::Feature::create("CSS Painting API"""_s, "CSSPaintingAPIEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable the CSS Painting API"""_s, DEFAULT_VALUE_FOR_CSSPaintingAPIEnabled, false),
#endif
        API::Feature::create("CSS Relative Color Syntax"""_s, "CSSRelativeColorSyntaxEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable support for CSS Relative Color Syntax defined in CSS Color 5"""_s, DEFAULT_VALUE_FOR_CSSRelativeColorSyntaxEnabled, false),
        API::Feature::create("CSS Rhythmic Sizing"""_s, "CSSRhythmicSizingEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable CSS Rhythmic Sizing properties"""_s, DEFAULT_VALUE_FOR_CSSRhythmicSizingEnabled, false),
        API::Feature::create("CSS Scroll Anchoring"""_s, "CSSScrollAnchoringEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable CSS Scroll Anchoring"""_s, DEFAULT_VALUE_FOR_CSSScrollAnchoringEnabled, false),
        API::Feature::create("CSS Spring Animations"""_s, "SpringTimingFunctionEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::CSS, "CSS Spring Animation prototype"""_s, DEFAULT_VALUE_FOR_SpringTimingFunctionEnabled, false),
        API::Feature::create("CSS Typed OM"""_s, "CSSTypedOMEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable the CSS Typed OM"""_s, DEFAULT_VALUE_FOR_CSSTypedOMEnabled, false),
        API::Feature::create("CSS Typed OM: Color Support"""_s, "CSSTypedOMColorEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable the CSS Typed OM Color support"""_s, DEFAULT_VALUE_FOR_CSSTypedOMColorEnabled, false),
        API::Feature::create("CSS align-tracks & justify-tracks properties for masonry layout"""_s, "MasonryTrackAlignmentEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable CSS align-tracks & justify-tracks properties for masonry layout"""_s, DEFAULT_VALUE_FOR_MasonryTrackAlignmentEnabled, false),
        API::Feature::create("CSS color-contrast()"""_s, "CSSColorContrastEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable support for CSS color-contrast() defined in CSS Color 5"""_s, DEFAULT_VALUE_FOR_CSSColorContrastEnabled, false),
        API::Feature::create("CSS color-mix()"""_s, "CSSColorMixEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable support for CSS color-mix() defined in CSS Color 5"""_s, DEFAULT_VALUE_FOR_CSSColorMixEnabled, false),
        API::Feature::create("CSS margin-trim property"""_s, "CSSMarginTrimEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable margin-trim CSS property"""_s, DEFAULT_VALUE_FOR_CSSMarginTrimEnabled, false),
        API::Feature::create("CSS overflow: clip support"""_s, "OverflowClipEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable CSS overflow: clip support"""_s, DEFAULT_VALUE_FOR_OverflowClipEnabled, false),
        API::Feature::create("CSS scrollbar-color property"""_s, "CSSScrollbarColorEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable scrollbar-color CSS property"""_s, DEFAULT_VALUE_FOR_CSSScrollbarColorEnabled, false),
        API::Feature::create("CSS scrollbar-gutter property"""_s, "CSSScrollbarGutterEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable scrollbar-gutter CSS property"""_s, DEFAULT_VALUE_FOR_CSSScrollbarGutterEnabled, false),
        API::Feature::create("CSS scrollbar-width property"""_s, "CSSScrollbarWidthEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable scrollbar-width CSS property"""_s, DEFAULT_VALUE_FOR_CSSScrollbarWidthEnabled, false),
        API::Feature::create("CSS subgrid support"""_s, "SubgridEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable CSS subgrid support"""_s, DEFAULT_VALUE_FOR_SubgridEnabled, false),
        API::Feature::create("CSS text-align-last property"""_s, "CSSTextAlignLastEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable the property text-align-last, defined in CSS Text 3"""_s, DEFAULT_VALUE_FOR_CSSTextAlignLastEnabled, false),
        API::Feature::create("CSS text-box-trim property"""_s, "CSSTextBoxTrimEnabled"_s, API::FeatureStatus::Preview, API::FeatureCategory::CSS, "Enable text-box-trim"""_s, DEFAULT_VALUE_FOR_CSSTextBoxTrimEnabled, false),
        API::Feature::create("CSS text-group-align property"""_s, "CSSTextGroupAlignEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable text-group-align CSS property"""_s, DEFAULT_VALUE_FOR_CSSTextGroupAlignEnabled, false),
        API::Feature::create("CSS text-justify property"""_s, "CSSTextJustifyEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable the property text-justify, defined in CSS Text 3"""_s, DEFAULT_VALUE_FOR_CSSTextJustifyEnabled, false),
        API::Feature::create("CSS text-spacing property"""_s, "CSSTextSpacingEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable the property text-spacing, defined in CSS Text 4"""_s, DEFAULT_VALUE_FOR_CSSTextSpacingEnabled, false),
        API::Feature::create("CSS text-underline-position: left right"""_s, "CSSTextUnderlinePositionLeftRightEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::CSS, "Enable the property text-underline-position left and right value support"""_s, DEFAULT_VALUE_FOR_CSSTextUnderlinePositionLeftRightEnabled, false),
        API::Feature::create("CSS text-wrap & white-space-collapse properties"""_s, "CSSWhiteSpaceLonghandsEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable text-wrap & white-space-collapse CSS properties"""_s, DEFAULT_VALUE_FOR_CSSWhiteSpaceLonghandsEnabled, false),
        API::Feature::create("CSS text-wrap: balance stable pretty"""_s, "CSSTextWrapNewValuesEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enable text-wrap: balance/stable/pretty CSS support"""_s, DEFAULT_VALUE_FOR_CSSTextWrapNewValuesEnabled, false),
#if ENABLE(CSS_TRANSFORM_STYLE_OPTIMIZED_3D)
        API::Feature::create("CSS transform-style: optimized-3d"""_s, "CSSTransformStyleOptimized3DEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::CSS, "Enable transform-style: optimized-3d property to access the separated graphics layer"""_s, DEFAULT_VALUE_FOR_CSSTransformStyleOptimized3DEnabled, false),
#endif
        API::Feature::create("CSSOM View Scrolling API"""_s, "CSSOMViewScrollingAPIEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Implement standard behavior for scrollLeft, scrollTop, scrollWidth, scrollHeight, scrollTo, scrollBy and scrollingElement."""_s, DEFAULT_VALUE_FOR_CSSOMViewScrollingAPIEnabled, false),
        API::Feature::create("CSSOM View Smooth Scrolling"""_s, "CSSOMViewSmoothScrollingEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable DOM API and CSS property for 'smooth' scroll behavior"""_s, DEFAULT_VALUE_FOR_CSSOMViewSmoothScrollingEnabled, false),
        API::Feature::create("Cache API"""_s, "CacheAPIEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Cache API"""_s, DEFAULT_VALUE_FOR_CacheAPIEnabled, false),
        API::Feature::create("Canvas Color Spaces"""_s, "CanvasColorSpaceEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable use of predefined canvas color spaces"""_s, DEFAULT_VALUE_FOR_CanvasColorSpaceEnabled, false),
        API::Feature::create("Canvas Filters"""_s, "CanvasFiltersEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Canvas Filters"""_s, DEFAULT_VALUE_FOR_CanvasFiltersEnabled, false),
        API::Feature::create("Canvas uses accelerated drawing"""_s, "CanvasUsesAcceleratedDrawing"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_CanvasUsesAcceleratedDrawing, false),
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("Capture audio in UI Process"""_s, "CaptureAudioInUIProcessEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable audio capture in UI Process"""_s, DEFAULT_VALUE_FOR_CaptureAudioInUIProcessEnabled, false),
#endif
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("Capture video in UI Process"""_s, "CaptureVideoInUIProcessEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable video capture in UI Process"""_s, DEFAULT_VALUE_FOR_CaptureVideoInUIProcessEnabled, false),
#endif
        API::Feature::create("Clear-Site-Data HTTP Header"""_s, "ClearSiteDataHTTPHeaderEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Networking, "Enable Clear-Site-Data HTTP Header support"""_s, DEFAULT_VALUE_FOR_ClearSiteDataHTTPHeaderEnabled, false),
#if ENABLE(BADGING)
        API::Feature::create("Client Badge"""_s, "ClientBadgeEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Enable Client Badge"""_s, DEFAULT_VALUE_FOR_ClientBadgeEnabled, false),
#endif
#if ENABLE(INPUT_TYPE_COLOR)
        API::Feature::create("Color Inputs"""_s, "InputTypeColorEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable input elements of type color"""_s, DEFAULT_VALUE_FOR_InputTypeColorEnabled, false),
#endif
        API::Feature::create("Compositing borders visible"""_s, "CompositingBordersVisible"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_CompositingBordersVisible, false),
        API::Feature::create("Compositing repaint counters visible"""_s, "CompositingRepaintCountersVisible"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_CompositingRepaintCountersVisible, false),
        API::Feature::create("Compression Stream API"""_s, "CompressionStreamEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Compression Stream API"""_s, DEFAULT_VALUE_FOR_CompressionStreamEnabled, false),
        API::Feature::create("Constructable Stylesheets"""_s, "ConstructableStylesheetsEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable Constructable Stylesheets"""_s, DEFAULT_VALUE_FOR_ConstructableStylesheetsEnabled, false),
        API::Feature::create("Contact Picker API"""_s, "ContactPickerAPIEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Enable the Contact Picker API"""_s, DEFAULT_VALUE_FOR_ContactPickerAPIEnabled, false),
#if HAVE(AVCONTENTKEYSPECIFIER)
        API::Feature::create("ContentKeySession support for SampleBuffer Renderers"""_s, "SampleBufferContentKeySessionSupportEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::Media, "ContentKeySession support for SampleBuffer Renderers Enabled"""_s, DEFAULT_VALUE_FOR_SampleBufferContentKeySessionSupportEnabled, false),
#endif
        API::Feature::create("Cookie Consent API"""_s, "CookieConsentAPIEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Enable cookie consent API"""_s, DEFAULT_VALUE_FOR_CookieConsentAPIEnabled, false),
        API::Feature::create("Cookie Store API Extended Attributes"""_s, "CookieStoreAPIExtendedAttributesEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Enable Extended Attributes of the Cookie Store API"""_s, DEFAULT_VALUE_FOR_CookieStoreAPIExtendedAttributesEnabled, false),
        API::Feature::create("Cookie Store API"""_s, "CookieStoreAPIEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Enable Cookie Store API"""_s, DEFAULT_VALUE_FOR_CookieStoreAPIEnabled, false),
        API::Feature::create("Cookies Enabled"""_s, "CookieEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_CookieEnabled, false),
        API::Feature::create("Cross-Origin-Embedder-Policy (COEP) header"""_s, "CrossOriginEmbedderPolicyEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Security, "Support for Cross-Origin-Embedder-Policy (COEP) header"""_s, DEFAULT_VALUE_FOR_CrossOriginEmbedderPolicyEnabled, false),
        API::Feature::create("Cross-Origin-Opener-Policy (COOP) header"""_s, "CrossOriginOpenerPolicyEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Security, "Support for Cross-Origin-Opener-Policy (COOP) header"""_s, DEFAULT_VALUE_FOR_CrossOriginOpenerPolicyEnabled, false),
        API::Feature::create("Custom pasteboard data"""_s, "CustomPasteboardDataEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable custom clipboard types and better security model for clipboard API."""_s, DEFAULT_VALUE_FOR_CustomPasteboardDataEnabled, false),
        API::Feature::create("DOM Paste Access Requests"""_s, "DOMPasteAccessRequestsEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable DOM Paste Access Requests"""_s, DEFAULT_VALUE_FOR_DOMPasteAccessRequestsEnabled, false),
        API::Feature::create("DOM timer throttling enabled"""_s, "DOMTimersThrottlingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_DOMTimersThrottlingEnabled, false),
        API::Feature::create("DOMParser support for Declarative Shadow DOM"""_s, "DeclarativeShadowDOMInDOMParserEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Enable Declarative Shadow DOM in DOMParser"""_s, DEFAULT_VALUE_FOR_DeclarativeShadowDOMInDOMParserEnabled, false),
#if PLATFORM(IOS_FAMILY)
        API::Feature::create("DTTZ also when root"""_s, "ZoomOnDoubleTapWhenRoot"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Double taps zoom, even if we dispatched a click on the root nodes"""_s, DEFAULT_VALUE_FOR_ZoomOnDoubleTapWhenRoot, false),
#endif
#if PLATFORM(IOS_FAMILY)
        API::Feature::create("DTTZ always"""_s, "AlwaysZoomOnDoubleTap"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Double taps zoom, even if we dispatched a click anywhere"""_s, DEFAULT_VALUE_FOR_AlwaysZoomOnDoubleTap, false),
#endif
        API::Feature::create("Data Transfer Items"""_s, "DataTransferItemsEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enables DataTransferItem in the clipboard API"""_s, DEFAULT_VALUE_FOR_DataTransferItemsEnabled, false),
#if ENABLE(DATALIST_ELEMENT)
        API::Feature::create("DataList Element"""_s, "DataListElementEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable datalist elements"""_s, DEFAULT_VALUE_FOR_DataListElementEnabled, false),
#endif
#if ENABLE(INPUT_TYPE_DATE)
        API::Feature::create("Date Input"""_s, "InputTypeDateEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable input elements of type date"""_s, DEFAULT_VALUE_FOR_InputTypeDateEnabled, false),
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
        API::Feature::create("Date/Time inputs have editable components"""_s, "DateTimeInputsEditableComponentsEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable multiple editable components in date/time inputs"""_s, DEFAULT_VALUE_FOR_DateTimeInputsEditableComponentsEnabled, false),
#endif
        API::Feature::create("Declarative Shadow DOM"""_s, "DeclarativeShadowDOMEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Declarative Shadow DOM"""_s, DEFAULT_VALUE_FOR_DeclarativeShadowDOMEnabled, false),
        API::Feature::create("Default ARIA for Custom Elements"""_s, "DefaultARIAForCustomElementsEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Default ARIA for Custom Elements"""_s, DEFAULT_VALUE_FOR_DefaultARIAForCustomElementsEnabled, false),
        API::Feature::create("Defer async scripts until DOMContentLoaded or first-paint"""_s, "ShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Defer async scripts until DOMContentLoaded or first-paint"""_s, DEFAULT_VALUE_FOR_ShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint, false),
        API::Feature::create("Deprecate RSAES-PKCS1-v1_5 Web Crypto"""_s, "DeprecateRSAESPKCSWebCryptoEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Deprecation of RSAES-PKCS1-v1_5 Web Crypto"""_s, DEFAULT_VALUE_FOR_DeprecateRSAESPKCSWebCryptoEnabled, false),
        API::Feature::create("Deprecation Reporting"""_s, "DeprecationReportingEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Enable Deprecation Reporting"""_s, DEFAULT_VALUE_FOR_DeprecationReportingEnabled, false),
        API::Feature::create("Diagnostic logging enabled"""_s, "DiagnosticLoggingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_DiagnosticLoggingEnabled, false),
        API::Feature::create("Directory Upload"""_s, "DirectoryUploadEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "input.webkitdirectory / dataTransferItem.webkitGetAsEntry()"""_s, DEFAULT_VALUE_FOR_DirectoryUploadEnabled, false),
        API::Feature::create("Disable Full 3rd-Party Cookie Blocking (ITP)"""_s, "IsThirdPartyCookieBlockingDisabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::Privacy, "Disable full third-party cookie blocking when Intelligent Tracking Prevention is enabled"""_s, DEFAULT_VALUE_FOR_IsThirdPartyCookieBlockingDisabled, false),
        API::Feature::create("Disable Removal of Non-Cookie Data After 7 Days of No User Interaction (ITP)"""_s, "IsFirstPartyWebsiteDataRemovalDisabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::Privacy, "Disable removal of all non-cookie website data after seven days of no user interaction when Intelligent Tracking Prevention is enabled"""_s, DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalDisabled, false),
#if PLATFORM(IOS_FAMILY)
        API::Feature::create("Disable screen size override"""_s, "DisableScreenSizeOverride"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_DisableScreenSizeOverride, false),
#endif
        API::Feature::create("Disallow sync XHR during page dismissal"""_s, "DisallowSyncXHRDuringPageDismissalEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Security, "Disallow synchronous XMLHttpRequest during page dismissal"""_s, DEFAULT_VALUE_FOR_DisallowSyncXHRDuringPageDismissalEnabled, false),
        API::Feature::create("DisplayList Drawing"""_s, "DisplayListDrawingEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::None, "Enable display-list drawing"""_s, DEFAULT_VALUE_FOR_DisplayListDrawingEnabled, false),
        API::Feature::create("Drop Near-Suspended Assertion After Delay"""_s, "ShouldDropNearSuspendedAssertionAfterDelay"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Causes processes to fully suspend after a delay"""_s, DEFAULT_VALUE_FOR_ShouldDropNearSuspendedAssertionAfterDelay, false),
        API::Feature::create("Embed Element"""_s, "EmbedElementEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Embed Element"""_s, DEFAULT_VALUE_FOR_EmbedElementEnabled, false),
        API::Feature::create("Enable Automatic Live Resize"""_s, "AutomaticLiveResizeEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Automatically synchronize web view resize with painting"""_s, DEFAULT_VALUE_FOR_AutomaticLiveResizeEnabled, false),
        API::Feature::create("Enable Canvas fingerprinting-related quirk"""_s, "CanvasFingerprintingQuirkEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, """"_s, DEFAULT_VALUE_FOR_CanvasFingerprintingQuirkEnabled, false),
        API::Feature::create("Enable Enumerating All Network Interfaces"""_s, "EnumeratingAllNetworkInterfacesEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_EnumeratingAllNetworkInterfacesEnabled, false),
        API::Feature::create("Enable Enumerating Visible Network Interfaces"""_s, "EnumeratingVisibleNetworkInterfacesEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_EnumeratingVisibleNetworkInterfacesEnabled, false),
        API::Feature::create("Enable ICE Candidate Filtering"""_s, "ICECandidateFilteringEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable ICE Candidate Filtering"""_s, DEFAULT_VALUE_FOR_ICECandidateFilteringEnabled, false),
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
        API::Feature::create("Enable Legacy EME API"""_s, "LegacyEncryptedMediaAPIEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable legacy EME API"""_s, DEFAULT_VALUE_FOR_LegacyEncryptedMediaAPIEnabled, false),
#endif
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("Enable Mock Capture Devices"""_s, "MockCaptureDevicesEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable Mock Capture Devices"""_s, DEFAULT_VALUE_FOR_MockCaptureDevicesEnabled, false),
#endif
#if ENABLE(PDFJS)
        API::Feature::create("Enable PDF.js viewer"""_s, "PdfJSViewerEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::HTML, "Enable PDF.js viewer"""_s, DEFAULT_VALUE_FOR_PdfJSViewerEnabled, false),
#endif
#if PLATFORM(MAC) && USE(RUNNINGBOARD)
        API::Feature::create("Enable background web content throttling via RunningBoard"""_s, "BackgroundWebContentRunningBoardThrottlingEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::Networking, "Enable background web content throttling via RunningBoard"""_s, DEFAULT_VALUE_FOR_BackgroundWebContentRunningBoardThrottlingEnabled, false),
#endif
#if ENABLE(SERVICE_WORKER)
        API::Feature::create("Enable background-fetch API"""_s, "BackgroundFetchAPIEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Networking, "Enable background-fetch API"""_s, DEFAULT_VALUE_FOR_BackgroundFetchAPIEnabled, false),
#endif
#if HAVE(MACH_BOOTSTRAP_EXTENSION) || HAVE(SANDBOX_STATE_FLAGS)
        API::Feature::create("Enable experimental sandbox features"""_s, "ExperimentalSandboxEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Security, "Enable experimental sandbox features"""_s, DEFAULT_VALUE_FOR_ExperimentalSandboxEnabled, false),
#endif
        API::Feature::create("Enable strict decoding of all ObjC classes"""_s, "StrictSecureDecodingForAllObjC"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_StrictSecureDecodingForAllObjC, false),
        API::Feature::create("Enter Key Hint"""_s, "EnterKeyHintEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable the enterKeyHint HTML attribute"""_s, DEFAULT_VALUE_FOR_EnterKeyHintEnabled, false),
        API::Feature::create("EventHandler driven smooth keyboard scrolling"""_s, "EventHandlerDrivenSmoothKeyboardScrollingEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable EventHandler driven smooth keyboard scrolling"""_s, DEFAULT_VALUE_FOR_EventHandlerDrivenSmoothKeyboardScrollingEnabled, false),
#if ENABLE(MEDIA_SESSION_COORDINATOR)
        API::Feature::create("Experimental MediaSession coordinator API"""_s, "MediaSessionCoordinatorEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "Enable experimental MediaSession coordinator API"""_s, DEFAULT_VALUE_FOR_MediaSessionCoordinatorEnabled, false),
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR) && ENABLE(MEDIA_SESSION_PLAYLIST)
        API::Feature::create("Experimental MediaSession playlist API"""_s, "MediaSessionPlaylistEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "Enable experimental MediaSession playlist API"""_s, DEFAULT_VALUE_FOR_MediaSessionPlaylistEnabled, false),
#endif
#if ENABLE(MEDIA_SOURCE) && (HAVE(AVSAMPLEBUFFERVIDEOOUTPUT) || USE(GSTREAMER))
        API::Feature::create("Experimental MediaSource Inline Painting"""_s, "MediaSourceInlinePaintingEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::Media, "Experimental MediaSource Inline Painting"""_s, DEFAULT_VALUE_FOR_MediaSourceInlinePaintingEnabled, false),
#endif
#if HAVE(NETWORK_LOADER)
        API::Feature::create("Experimental network loader"""_s, "CFNetworkNetworkLoaderEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::Networking, "Enable experimental network loader"""_s, DEFAULT_VALUE_FOR_CFNetworkNetworkLoaderEnabled, false),
#endif
        API::Feature::create("FTP support enabled"""_s, "FTPEnabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::Networking, "FTP support enabled"""_s, DEFAULT_VALUE_FOR_FTPEnabled, false),
#if PLATFORM(IOS_FAMILY)
        API::Feature::create("Fast clicks beat DTTZ"""_s, "PreferFasterClickOverDoubleTap"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Prefer a faster click over a double tap"""_s, DEFAULT_VALUE_FOR_PreferFasterClickOverDoubleTap, false),
#endif
#if PLATFORM(IOS_FAMILY)
        API::Feature::create("Fast clicks"""_s, "FasterClicksEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Support faster clicks on zoomable pages"""_s, DEFAULT_VALUE_FOR_FasterClicksEnabled, false),
#endif
        API::Feature::create("Fetch API Request KeepAlive"""_s, "FetchAPIKeepAliveEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Fetch API Request KeepAlive"""_s, DEFAULT_VALUE_FOR_FetchAPIKeepAliveEnabled, false),
        API::Feature::create("Fetch API"""_s, "FetchAPIEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Fetch API"""_s, DEFAULT_VALUE_FOR_FetchAPIEnabled, false),
        API::Feature::create("Fetch Metadata"""_s, "FetchMetadataEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Fetch Metadata headers"""_s, DEFAULT_VALUE_FOR_FetchMetadataEnabled, false),
        API::Feature::create("Fetch Priority"""_s, "FetchPriorityEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Networking, "Enable Fetch Priority support"""_s, DEFAULT_VALUE_FOR_FetchPriorityEnabled, false),
        API::Feature::create("File System Access API"""_s, "FileSystemAccessEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable File System Access API"""_s, DEFAULT_VALUE_FOR_FileSystemAccessEnabled, false),
        API::Feature::create("FileReader API"""_s, "FileReaderAPIEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "FileReader API"""_s, DEFAULT_VALUE_FOR_FileReaderAPIEnabled, false),
        API::Feature::create("Filter HTTP Response for Web Processes"""_s, "RestrictedHTTPResponseAccess"_s, API::FeatureStatus::Internal, API::FeatureCategory::Networking, "Enable HTTP Response filtering for Web Processes"""_s, DEFAULT_VALUE_FOR_RestrictedHTTPResponseAccess, false),
#if PLATFORM(IOS_FAMILY)
        API::Feature::create("Force always user-scalable"""_s, "ForceAlwaysUserScalable"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_ForceAlwaysUserScalable, false),
#endif
        API::Feature::create("Form requestSubmit"""_s, "RequestSubmitEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Form requestSubmit method"""_s, DEFAULT_VALUE_FOR_RequestSubmitEnabled, false),
        API::Feature::create("Form-associated custom elements"""_s, "FormAssociatedCustomElementsEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Support for form-associated custom elements"""_s, DEFAULT_VALUE_FOR_FormAssociatedCustomElementsEnabled, false),
        API::Feature::create("Frame flattening"""_s, "FrameFlatteningEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable frame flattening, which adjusts the height of an iframe to fit its contents"""_s, DEFAULT_VALUE_FOR_FrameFlatteningEnabled, false),
        API::Feature::create("Full next-generation layout (LFC)"""_s, "LayoutFormattingContextEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Enable full next-generation layout (LFC)"""_s, DEFAULT_VALUE_FOR_LayoutFormattingContextEnabled, false),
#if ENABLE(FULLSCREEN_API)
        API::Feature::create("Fullscreen API"""_s, "FullScreenEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Fullscreen API"""_s, DEFAULT_VALUE_FOR_FullScreenEnabled, EXPERIMENTAL_FULLSCREEN_API_HIDDEN),
#endif
#if PLATFORM(VISION)
        API::Feature::create("Fullscreen scene aspect ratio locking"""_s, "FullscreenSceneAspectRatioLockingEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Enable scene aspect ratio locking in Fullscreen"""_s, DEFAULT_VALUE_FOR_FullscreenSceneAspectRatioLockingEnabled, false),
#endif
#if PLATFORM(VISION)
        API::Feature::create("Fullscreen scene dimming"""_s, "FullscreenSceneDimmingEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Enable scene dimming in Fullscreen"""_s, DEFAULT_VALUE_FOR_FullscreenSceneDimmingEnabled, false),
#endif
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("GPU Process: Audio Capture"""_s, "CaptureAudioInGPUProcessEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable audio capture in GPU Process"""_s, DEFAULT_VALUE_FOR_CaptureAudioInGPUProcessEnabled, false),
#endif
#if ENABLE(GPU_PROCESS)
        API::Feature::create("GPU Process: Block Media Layer Re-hosting"""_s, "BlockMediaLayerRehostingInWebContentProcess"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "GPU Process: Block Media Layer Re-hosting in WebContent process"""_s, DEFAULT_VALUE_FOR_BlockMediaLayerRehostingInWebContentProcess, false),
#endif
#if ENABLE(GPU_PROCESS) && !(PLATFORM(GTK) || PLATFORM(WPE))
        API::Feature::create("GPU Process: Canvas Rendering"""_s, "UseGPUProcessForCanvasRenderingEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable canvas rendering in GPU Process"""_s, DEFAULT_VALUE_FOR_UseGPUProcessForCanvasRenderingEnabled, false),
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
        API::Feature::create("GPU Process: Capture Status Bar management"""_s, "ManageCaptureStatusBarInGPUProcessEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable Capture Status Bar management in GPU Process"""_s, DEFAULT_VALUE_FOR_ManageCaptureStatusBarInGPUProcessEnabled, false),
#endif
#if ENABLE(GPU_PROCESS)
        API::Feature::create("GPU Process: DOM Rendering"""_s, "UseGPUProcessForDOMRenderingEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable DOM rendering in GPU Process"""_s, DEFAULT_VALUE_FOR_UseGPUProcessForDOMRenderingEnabled, false),
#endif
#if ENABLE(GPU_PROCESS) && !USE(GSTREAMER)
        API::Feature::create("GPU Process: Media"""_s, "UseGPUProcessForMediaEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Do all media loading and playback in the GPU Process"""_s, DEFAULT_VALUE_FOR_UseGPUProcessForMediaEnabled, false),
#endif
#if HAVE(SCREEN_CAPTURE_KIT)
        API::Feature::create("GPU Process: Screen and Window capture"""_s, "UseGPUProcessForDisplayCapture"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "Display capture in GPU Process"""_s, DEFAULT_VALUE_FOR_UseGPUProcessForDisplayCapture, false),
#endif
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("GPU Process: Video Capture"""_s, "CaptureVideoInGPUProcessEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable video capture in GPU Process"""_s, DEFAULT_VALUE_FOR_CaptureVideoInGPUProcessEnabled, false),
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
        API::Feature::create("GPU Process: WebGL"""_s, "UseGPUProcessForWebGLEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Process all WebGL operations in GPU Process"""_s, DEFAULT_VALUE_FOR_UseGPUProcessForWebGLEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("GPU Process: WebRTC Platform Codecs"""_s, "WebRTCPlatformCodecsInGPUProcessEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable WebRTC Platform Codecs in GPU Process"""_s, DEFAULT_VALUE_FOR_WebRTCPlatformCodecsInGPUProcessEnabled, false),
#endif
#if ENABLE(GAMEPAD)
        API::Feature::create("Gamepad trigger vibration support"""_s, "GamepadTriggerRumbleEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Support for Gamepad trigger vibration"""_s, DEFAULT_VALUE_FOR_GamepadTriggerRumbleEnabled, false),
#endif
#if ENABLE(GAMEPAD)
        API::Feature::create("Gamepad.vibrationActuator support"""_s, "GamepadVibrationActuatorEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Support for Gamepad.vibrationActuator"""_s, DEFAULT_VALUE_FOR_GamepadVibrationActuatorEnabled, false),
#endif
#if ENABLE(GAMEPAD)
        API::Feature::create("Gamepads"""_s, "GamepadsEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Web Gamepad API support"""_s, DEFAULT_VALUE_FOR_GamepadsEnabled, false),
#endif
#if ENABLE(VIDEO)
        API::Feature::create("Generic Text Track Cue API"""_s, "GenericCueAPIEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Generic Text Track Cue API"""_s, DEFAULT_VALUE_FOR_GenericCueAPIEnabled, false),
#endif
#if USE(GRAPHICS_CONTEXT_FILTERS)
        API::Feature::create("GraphicsContext Filter Rendering"""_s, "GraphicsContextFiltersEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::None, "GraphicsContext Filter Rendering"""_s, DEFAULT_VALUE_FOR_GraphicsContextFiltersEnabled, false),
#endif
        API::Feature::create("GraphicsLayer accelerated drawing"""_s, "AcceleratedDrawingEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Enable GraphicsLayer accelerated drawing"""_s, DEFAULT_VALUE_FOR_AcceleratedDrawingEnabled, false),
        API::Feature::create("HTML <dialog> element"""_s, "DialogElementEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::HTML, "Enable HTML <dialog> element"""_s, DEFAULT_VALUE_FOR_DialogElementEnabled, false),
#if ENABLE(MODEL_ELEMENT)
        API::Feature::create("HTML <model> element"""_s, "ModelElementEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::HTML, "Enable HTML <model> element"""_s, DEFAULT_VALUE_FOR_ModelElementEnabled, false),
#endif
#if ENABLE(MODEL_ELEMENT)
        API::Feature::create("HTML <model> elements for stand-alone document"""_s, "ModelDocumentEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::HTML, "Enable HTML <model> element for model documents"""_s, DEFAULT_VALUE_FOR_ModelDocumentEnabled, false),
#endif
        API::Feature::create("HTML Interactive Form Validation"""_s, "InteractiveFormValidationEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "HTML interactive form validation"""_s, DEFAULT_VALUE_FOR_InteractiveFormValidationEnabled, false),
        API::Feature::create("HTML inert attribute"""_s, "InertAttributeEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::HTML, "Enable inert attribute support"""_s, DEFAULT_VALUE_FOR_InertAttributeEnabled, false),
        API::Feature::create("HTML popover attribute"""_s, "PopoverAttributeEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::HTML, "Enable HTML popover attribute support"""_s, DEFAULT_VALUE_FOR_PopoverAttributeEnabled, false),
        API::Feature::create("Hidden page DOM timer throttling auto-increases"""_s, "HiddenPageDOMTimerThrottlingAutoIncreases"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_HiddenPageDOMTimerThrottlingAutoIncreases, false),
        API::Feature::create("Hidden page DOM timer throttling"""_s, "HiddenPageDOMTimerThrottlingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable hidden page DOM timer throttling"""_s, DEFAULT_VALUE_FOR_HiddenPageDOMTimerThrottlingEnabled, false),
        API::Feature::create("Highlight API"""_s, "HighlightAPIEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Highlight API support"""_s, DEFAULT_VALUE_FOR_HighlightAPIEnabled, false),
        API::Feature::create("Hyperlink Auditing"""_s, "HyperlinkAuditingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable Hyperlink Auditing"""_s, DEFAULT_VALUE_FOR_HyperlinkAuditingEnabled, false),
#if HAVE(SANDBOX_STATE_FLAGS)
        API::Feature::create("IOKit blocking in the WebContent sandbox"""_s, "BlockIOKitInWebContentSandbox"_s, API::FeatureStatus::Internal, API::FeatureCategory::Networking, "Block IOKit access in the WebContent sandbox"""_s, DEFAULT_VALUE_FOR_BlockIOKitInWebContentSandbox, false),
#endif
#if ENABLE(IPC_TESTING_API)
        API::Feature::create("IPC Testing API"""_s, "IPCTestingAPIEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Security, "Enable IPC Testing API for JavaScript"""_s, DEFAULT_VALUE_FOR_IPCTestingAPIEnabled, false),
#endif
        API::Feature::create("ITP Debug Mode"""_s, "ItpDebugModeEnabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::Privacy, "Intelligent Tracking Prevention Debug Mode"""_s, DEFAULT_VALUE_FOR_ItpDebugModeEnabled, false),
#if ENABLE(TEXT_AUTOSIZING)
        API::Feature::create("Idempotent Text Autosizing"""_s, "TextAutosizingUsesIdempotentMode"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Use idempotent text autosizing mode"""_s, DEFAULT_VALUE_FOR_TextAutosizingUsesIdempotentMode, false),
#endif
#if ENABLE(IMAGE_ANALYSIS)
        API::Feature::create("Image Analysis for Find-in-Page"""_s, "ImageAnalysisDuringFindInPageEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::None, "Trigger image analysis when performing Find-in-Page"""_s, DEFAULT_VALUE_FOR_ImageAnalysisDuringFindInPageEnabled, false),
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
        API::Feature::create("Image Animation Control"""_s, "ImageAnimationControlEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Animation, "Enable controls for image animations"""_s, DEFAULT_VALUE_FOR_ImageAnimationControlEnabled, false),
#endif
#if ENABLE(SERVICE_CONTROLS)
        API::Feature::create("Image Controls"""_s, "ImageControlsEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Enable image controls"""_s, DEFAULT_VALUE_FOR_ImageControlsEnabled, false),
#endif
        API::Feature::create("Imperative Slot API"""_s, "ImperativeSlotAPIEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Imperative Shadow DOM Distribution API"""_s, DEFAULT_VALUE_FOR_ImperativeSlotAPIEnabled, false),
        API::Feature::create("IndexedDB API"""_s, "IndexedDBAPIEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "IndexedDB API"""_s, DEFAULT_VALUE_FOR_IndexedDBAPIEnabled, false),
        API::Feature::create("Inline Text Predictions"""_s, "InlinePredictionsInAllEditableElementsEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Enable Inline Text Predictions in all editable elements"""_s, DEFAULT_VALUE_FOR_InlinePredictionsInAllEditableElementsEnabled, false),
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
        API::Feature::create("Interaction Regions"""_s, "InteractionRegionsEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Generate and visualize interaction regions"""_s, DEFAULT_VALUE_FOR_InteractionRegionsEnabled, false),
#endif
        API::Feature::create("Intersection Observer"""_s, "IntersectionObserverEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Intersection Observer support"""_s, DEFAULT_VALUE_FOR_IntersectionObserverEnabled, false),
        API::Feature::create("IsLoggedIn web API"""_s, "IsLoggedInAPIEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Enable the proposed IsLoggedIn web API"""_s, DEFAULT_VALUE_FOR_IsLoggedInAPIEnabled, false),
#if ENABLE(ACCESSIBILITY_ISOLATED_TREE)
        API::Feature::create("Isolated Accessibility Tree Mode"""_s, "IsAccessibilityIsolatedTreeEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable an accessibility hierarchy for VoiceOver that can be accessed on a secondary thread for improved performance"""_s, DEFAULT_VALUE_FOR_IsAccessibilityIsolatedTreeEnabled, false),
#endif
        API::Feature::create("JavaScript"""_s, "JavaScriptEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable JavaScript"""_s, DEFAULT_VALUE_FOR_JavaScriptEnabled, false),
#if ENABLE(LAYER_BASED_SVG_ENGINE)
        API::Feature::create("Layer-based SVG Engine (LBSE)"""_s, "LayerBasedSVGEngineEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::None, "Enable next-generation layer-based SVG Engine (LBSE)"""_s, DEFAULT_VALUE_FOR_LayerBasedSVGEngineEnabled, false),
#endif
        API::Feature::create("Lazy iframe loading"""_s, "LazyIframeLoadingEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::HTML, "Enable lazy iframe loading support"""_s, DEFAULT_VALUE_FOR_LazyIframeLoadingEnabled, false),
        API::Feature::create("Lazy image loading"""_s, "LazyImageLoadingEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::HTML, "Enable lazy image loading support"""_s, DEFAULT_VALUE_FOR_LazyImageLoadingEnabled, false),
#if ENABLE(OVERFLOW_SCROLLING_TOUCH)
        API::Feature::create("Legacy -webkit-overflow-scrolling property"""_s, "LegacyOverflowScrollingTouchEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Support the legacy -webkit-overflow-scrolling CSS property"""_s, DEFAULT_VALUE_FOR_LegacyOverflowScrollingTouchEnabled, false),
#endif
        API::Feature::create("Legacy line layout visual coverage"""_s, "LegacyLineLayoutVisualCoverageEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable legacy line layout visual coverage"""_s, DEFAULT_VALUE_FOR_LegacyLineLayoutVisualCoverageEnabled, false),
        API::Feature::create("Legacy showModalDialog() API"""_s, "ShowModalDialogEnabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::DOM, "Legacy showModalDialog() API"""_s, DEFAULT_VALUE_FOR_ShowModalDialogEnabled, false),
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("Limit Media Capture to Secure Sites"""_s, "MediaCaptureRequiresSecureConnection"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Limit Media Capture to Secure Sites"""_s, DEFAULT_VALUE_FOR_MediaCaptureRequiresSecureConnection, false),
#endif
        API::Feature::create("Link Sanitizer"""_s, "LinkSanitizerEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::Networking, "Enable link sanitizer"""_s, DEFAULT_VALUE_FOR_LinkSanitizerEnabled, false),
        API::Feature::create("Link preload responsive images"""_s, "LinkPreloadResponsiveImagesEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Networking, "Enable link preload responsive images"""_s, DEFAULT_VALUE_FOR_LinkPreloadResponsiveImagesEnabled, false),
        API::Feature::create("Link rel=modulepreload"""_s, "LinkModulePreloadEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Networking, "Enable Link rel=modulepreload"""_s, DEFAULT_VALUE_FOR_LinkModulePreloadEnabled, false),
        API::Feature::create("Link rel=preconnect via HTTP early hints"""_s, "LinkPreconnectEarlyHintsEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Networking, "Enable link rel=preconnect via early hints"""_s, DEFAULT_VALUE_FOR_LinkPreconnectEarlyHintsEnabled, false),
        API::Feature::create("LinkPrefetch"""_s, "LinkPrefetchEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Networking, "Enable LinkedPrefetch"""_s, DEFAULT_VALUE_FOR_LinkPrefetchEnabled, false),
        API::Feature::create("Live Ranges in Selection"""_s, "LiveRangeSelectionEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Live range behavior for ranges in the Selection object"""_s, DEFAULT_VALUE_FOR_LiveRangeSelectionEnabled, false),
        API::Feature::create("Local File Content Sniffing"""_s, "LocalFileContentSniffingEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Networking, "Enable Local File Content Sniffing"""_s, DEFAULT_VALUE_FOR_LocalFileContentSniffingEnabled, false),
        API::Feature::create("Local Storage"""_s, "LocalStorageEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Local Storage"""_s, DEFAULT_VALUE_FOR_LocalStorageEnabled, false),
        API::Feature::create("Log page messages to system console"""_s, "LogsPageMessagesToSystemConsoleEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable logging page messages to system console"""_s, DEFAULT_VALUE_FOR_LogsPageMessagesToSystemConsoleEnabled, false),
        API::Feature::create("Main content user gesture override"""_s, "MainContentUserGestureOverrideEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable main content user gesture override"""_s, DEFAULT_VALUE_FOR_MainContentUserGestureOverrideEnabled, false),
#if ENABLE(MANAGED_MEDIA_SOURCE)
        API::Feature::create("Managed Media Source API"""_s, "ManagedMediaSourceEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "Managed Media Source API"""_s, DEFAULT_VALUE_FOR_ManagedMediaSourceEnabled, false),
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE) && ENABLE(WIRELESS_PLAYBACK_TARGET)
        API::Feature::create("Managed Media Source Requires AirPlay source"""_s, "ManagedMediaSourceNeedsAirPlay"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "Managed Media Source Requires AirPlay source"""_s, DEFAULT_VALUE_FOR_ManagedMediaSourceNeedsAirPlay, false),
#endif
#if ENABLE(WEBGL)
        API::Feature::create("Mask WebGL Strings"""_s, "MaskWebGLStringsEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Privacy, "Mask WebGL Vendor, Renderer, Shader Language Strings"""_s, DEFAULT_VALUE_FOR_MaskWebGLStringsEnabled, false),
#endif
        API::Feature::create("MathML Core"""_s, "CoreMathMLEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Disable features removed from the MathML Core spec."""_s, DEFAULT_VALUE_FOR_CoreMathMLEnabled, false),
        API::Feature::create("Media Capabilities Extensions"""_s, "MediaCapabilitiesExtensionsEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "Media Capabilities Extensions"""_s, DEFAULT_VALUE_FOR_MediaCapabilitiesExtensionsEnabled, false),
#if ENABLE(MEDIA_SESSION)
        API::Feature::create("Media Session API"""_s, "MediaSessionEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Media Session API"""_s, DEFAULT_VALUE_FOR_MediaSessionEnabled, false),
#endif
        API::Feature::create("Media Source API"""_s, "MediaSourceEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::Media, "Media Source API"""_s, DEFAULT_VALUE_FOR_MediaSourceEnabled, false),
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("Media devices"""_s, "MediaDevicesEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable media devices"""_s, DEFAULT_VALUE_FOR_MediaDevicesEnabled, false),
#endif
#if ENABLE(MEDIA_RECORDER)
        API::Feature::create("MediaRecorder"""_s, "MediaRecorderEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "MediaRecorder"""_s, DEFAULT_VALUE_FOR_MediaRecorderEnabled, false),
#endif
        API::Feature::create("Momentum Scrolling Animator"""_s, "MomentumScrollingAnimatorEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Generate momentum events in WebKit instead of using those delivered by the system"""_s, DEFAULT_VALUE_FOR_MomentumScrollingAnimatorEnabled, false),
#if ENABLE(INPUT_TYPE_MONTH)
        API::Feature::create("Month Input"""_s, "InputTypeMonthEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable input elements of type month"""_s, DEFAULT_VALUE_FOR_InputTypeMonthEnabled, false),
#endif
#if ENABLE(TOUCH_EVENTS)
        API::Feature::create("Mouse events simulation"""_s, "MouseEventsSimulationEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable mouse events dispatch along with touch events on iOS"""_s, DEFAULT_VALUE_FOR_MouseEventsSimulationEnabled, false),
#endif
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("Mute Camera on Microphone Interruption"""_s, "MuteCameraOnMicrophoneInterruptionEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Mute Camera on Microphone Interruption"""_s, DEFAULT_VALUE_FOR_MuteCameraOnMicrophoneInterruptionEnabled, false),
#endif
#if ENABLE(APP_BOUND_DOMAINS)
        API::Feature::create("Needs In-App Browser Privacy Quirks"""_s, "NeedsInAppBrowserPrivacyQuirks"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable quirks needed to support In-App Browser privacy"""_s, DEFAULT_VALUE_FOR_NeedsInAppBrowserPrivacyQuirks, false),
#endif
        API::Feature::create("Needs Site-Specific Quirks"""_s, "NeedsSiteSpecificQuirks"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable site-specific quirks"""_s, DEFAULT_VALUE_FOR_NeedsSiteSpecificQuirks, false),
        API::Feature::create("Needs storage access from file URLs quirk"""_s, "NeedsStorageAccessFromFileURLsQuirk"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_NeedsStorageAccessFromFileURLsQuirk, false),
        API::Feature::create("Next-generation flex layout integration (FFC)"""_s, "FlexFormattingContextIntegrationEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Enable next-generation flex layout integration (FFC)"""_s, DEFAULT_VALUE_FOR_FlexFormattingContextIntegrationEnabled, false),
        API::Feature::create("Next-generation inline layout (IFC)"""_s, "InlineFormattingContextIntegrationEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable next-generation inline layout (IFC)"""_s, DEFAULT_VALUE_FOR_InlineFormattingContextIntegrationEnabled, false),
#if ENABLE(NOTIFICATION_EVENT)
        API::Feature::create("NotificationEvent support"""_s, "NotificationEventEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "NotificationEvent and ServiceWorkerRegistration.showNotification() support"""_s, DEFAULT_VALUE_FOR_NotificationEventEnabled, false),
#endif
#if ENABLE(NOTIFICATIONS)
        API::Feature::create("Notifications"""_s, "NotificationsEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable the Notifications API"""_s, DEFAULT_VALUE_FOR_NotificationsEnabled, false),
#endif
#if ENABLE(OFFSCREEN_CANVAS_IN_WORKERS)
        API::Feature::create("OffscreenCanvas in Workers"""_s, "OffscreenCanvasInWorkersEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Support for the OffscreenCanvas APIs in Workers"""_s, DEFAULT_VALUE_FOR_OffscreenCanvasInWorkersEnabled, false),
#endif
#if ENABLE(OFFSCREEN_CANVAS)
        API::Feature::create("OffscreenCanvas"""_s, "OffscreenCanvasEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Support for the OffscreenCanvas APIs"""_s, DEFAULT_VALUE_FOR_OffscreenCanvasEnabled, false),
#endif
#if ENABLE(OPUS)
        API::Feature::create("Opus audio decoder"""_s, "OpusDecoderEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Opus audio decoder"""_s, DEFAULT_VALUE_FOR_OpusDecoderEnabled, false),
#endif
        API::Feature::create("Page visibility-based process suppression"""_s, "PageVisibilityBasedProcessSuppressionEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable page visibility-based process suppression"""_s, DEFAULT_VALUE_FOR_PageVisibilityBasedProcessSuppressionEnabled, false),
        API::Feature::create("Paint Timing"""_s, "PaintTimingEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable PaintTiming API"""_s, DEFAULT_VALUE_FOR_PaintTimingEnabled, false),
        API::Feature::create("Partition Blob URL Registry"""_s, "BlobRegistryTopOriginPartitioningEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::None, "Partition Blob URL Registry by Top-Level Origin"""_s, DEFAULT_VALUE_FOR_BlobRegistryTopOriginPartitioningEnabled, false),
        API::Feature::create("PerformanceNavigationTiming"""_s, "PerformanceNavigationTimingAPIEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable PerformanceNavigationTiming API"""_s, DEFAULT_VALUE_FOR_PerformanceNavigationTimingAPIEnabled, false),
        API::Feature::create("PerformanceResourceTiming.transferSize, encodedBodySize, and decodedBodySize"""_s, "PerformanceResourceTimingSensitivePropertiesEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable all properties of PerformanceResourceTiming API"""_s, DEFAULT_VALUE_FOR_PerformanceResourceTimingSensitivePropertiesEnabled, false),
        API::Feature::create("Permissions API"""_s, "PermissionsAPIEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Permissions API"""_s, DEFAULT_VALUE_FOR_PermissionsAPIEnabled, false),
        API::Feature::create("Prefer Page Rendering Updates near 60fps"""_s, "PreferPageRenderingUpdatesNear60FPSEnabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::DOM, "Prefer page rendering updates near 60 frames per second rather than using the display's refresh rate"""_s, DEFAULT_VALUE_FOR_PreferPageRenderingUpdatesNear60FPSEnabled, false),
#if ENABLE(VIDEO)
        API::Feature::create("Prefer Sandboxed Parsing of Media"""_s, "PreferSandboxedMediaParsing"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Prefer parsing media out-of-process in a sandboxed service"""_s, DEFAULT_VALUE_FOR_PreferSandboxedMediaParsing, false),
#endif
        API::Feature::create("Private Click Measurement Debug Mode"""_s, "PrivateClickMeasurementDebugModeEnabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::Privacy, "Enable Private Click Measurement Debug Mode"""_s, DEFAULT_VALUE_FOR_PrivateClickMeasurementDebugModeEnabled, false),
        API::Feature::create("Private Click Measurement Fraud Prevention"""_s, "PrivateClickMeasurementFraudPreventionEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Privacy, "Enable Private Click Measurement Fraud Prevention"""_s, DEFAULT_VALUE_FOR_PrivateClickMeasurementFraudPreventionEnabled, false),
        API::Feature::create("Private Click Measurement"""_s, "PrivateClickMeasurementEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable Private Click Measurement for Cross-Site Link Navigations"""_s, DEFAULT_VALUE_FOR_PrivateClickMeasurementEnabled, false),
#if ENABLE(SERVICE_WORKER)
        API::Feature::create("Push API"""_s, "PushAPIEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::DOM, "Enable Push API"""_s, DEFAULT_VALUE_FOR_PushAPIEnabled, false),
#endif
        API::Feature::create("Quirk to prevent delayed initial painting on sites using Google's Anti-Flicker optimization"""_s, "GoogleAntiFlickerOptimizationQuirkEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Quirk to prevent delayed initial painting on sites using Google's Anti-Flicker optimization"""_s, DEFAULT_VALUE_FOR_GoogleAntiFlickerOptimizationQuirkEnabled, false),
        API::Feature::create("ReadableByteStream"""_s, "ReadableByteStreamAPIEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Enable Readable Byte Streams"""_s, DEFAULT_VALUE_FOR_ReadableByteStreamAPIEnabled, false),
        API::Feature::create("Referrer Policy attribute"""_s, "ReferrerPolicyAttributeEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Referrer Policy attribute"""_s, DEFAULT_VALUE_FOR_ReferrerPolicyAttributeEnabled, false),
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
        API::Feature::create("Remote Playback API"""_s, "RemotePlaybackEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Remote Playback API"""_s, DEFAULT_VALUE_FOR_RemotePlaybackEnabled, false),
#endif
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
        API::Feature::create("Remove Background"""_s, "RemoveBackgroundEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable Remove Background"""_s, DEFAULT_VALUE_FOR_RemoveBackgroundEnabled, false),
#endif
        API::Feature::create("Reporting API"""_s, "ReportingEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Reporting API"""_s, DEFAULT_VALUE_FOR_ReportingEnabled, false),
        API::Feature::create("RequestVideoFrameCallback"""_s, "RequestVideoFrameCallbackEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "Enable RequestVideoFrameCallback API"""_s, DEFAULT_VALUE_FOR_RequestVideoFrameCallbackEnabled, false),
#if HAVE(SC_CONTENT_SHARING_PICKER)
        API::Feature::create("Require User Agent getDisplayMedia prompt"""_s, "RequireUAGetDisplayMediaPrompt"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Require and use User Agent getDisplayMedia prompt"""_s, DEFAULT_VALUE_FOR_RequireUAGetDisplayMediaPrompt, false),
#endif
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("Require a user gesture for speaker selection"""_s, "SpeakerSelectionRequiresUserGesture"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Require a user gesture for speaker selection"""_s, DEFAULT_VALUE_FOR_SpeakerSelectionRequiresUserGesture, false),
#endif
        API::Feature::create("Require being in Fullscreen to lock screen orientation"""_s, "FullscreenRequirementForScreenOrientationLockingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Require being in Fullscreen to lock screen orientation"""_s, DEFAULT_VALUE_FOR_FullscreenRequirementForScreenOrientationLockingEnabled, false),
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("Require focus to start getUserMedia"""_s, "GetUserMediaRequiresFocus"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Require focus to start getUserMedia"""_s, DEFAULT_VALUE_FOR_GetUserMediaRequiresFocus, false),
#endif
        API::Feature::create("Resize Observer"""_s, "ResizeObserverEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Resize Observer support"""_s, DEFAULT_VALUE_FOR_ResizeObserverEnabled, false),
        API::Feature::create("Resource Load Scheduling"""_s, "ResourceLoadSchedulingEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Networking, "Network process side priority and visibility based resource load scheduling"""_s, DEFAULT_VALUE_FOR_ResourceLoadSchedulingEnabled, false),
#if ENABLE(RESOURCE_USAGE)
        API::Feature::create("Resource usage overlay"""_s, "ResourceUsageOverlayVisible"_s, API::FeatureStatus::Internal, API::FeatureCategory::Networking, "Make resource usage overlay visible"""_s, DEFAULT_VALUE_FOR_ResourceUsageOverlayVisible, false),
#endif
        API::Feature::create("SKAttribution"""_s, "SKAttributionEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "SKAttribution"""_s, DEFAULT_VALUE_FOR_SKAttributionEnabled, false),
        API::Feature::create("Safe Browsing"""_s, "SafeBrowsingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable Safe Browsing"""_s, DEFAULT_VALUE_FOR_SafeBrowsingEnabled, false),
        API::Feature::create("SameSite strict enforcement (ITP)"""_s, "IsSameSiteStrictEnforcementEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::Privacy, "Enable SameSite strict enforcement to mitigate bounce tracking"""_s, DEFAULT_VALUE_FOR_IsSameSiteStrictEnforcementEnabled, false),
        API::Feature::create("Screen Orientation API (Locking / Unlocking)"""_s, "ScreenOrientationLockingAPIEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Enable Screen Orientation API (Locking / Unlocking)"""_s, DEFAULT_VALUE_FOR_ScreenOrientationLockingAPIEnabled, false),
        API::Feature::create("Screen Orientation API"""_s, "ScreenOrientationAPIEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Screen Orientation API"""_s, DEFAULT_VALUE_FOR_ScreenOrientationAPIEnabled, false),
        API::Feature::create("Screen Wake Lock API"""_s, "ScreenWakeLockAPIEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Screen Wake Lock API"""_s, DEFAULT_VALUE_FOR_ScreenWakeLockAPIEnabled, false),
#if ENABLE(MEDIA_STREAM)
        API::Feature::create("ScreenCapture"""_s, "ScreenCaptureEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "Enable ScreenCapture"""_s, DEFAULT_VALUE_FOR_ScreenCaptureEnabled, false),
#endif
        API::Feature::create("Scroll Performance Testing Enabled"""_s, "ScrollingPerformanceTestingEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Enable behaviors used by scrolling performance tests"""_s, DEFAULT_VALUE_FOR_ScrollingPerformanceTestingEnabled, false),
        API::Feature::create("Scroll To Text Fragment Indicator"""_s, "ScrollToTextFragmentIndicatorEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable Scroll To Text Fragment Indicator"""_s, DEFAULT_VALUE_FOR_ScrollToTextFragmentIndicatorEnabled, false),
        API::Feature::create("Scroll To Text Fragment"""_s, "ScrollToTextFragmentEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Scroll To Text Fragment"""_s, DEFAULT_VALUE_FOR_ScrollToTextFragmentEnabled, false),
        API::Feature::create("Scroll animator"""_s, "ScrollAnimatorEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable scroll animator"""_s, DEFAULT_VALUE_FOR_ScrollAnimatorEnabled, false),
        API::Feature::create("Search control incremental attribute and search event"""_s, "SearchInputIncrementalAttributeAndSearchEventEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::HTML, "Enable search control incremental attribute and search event support"""_s, DEFAULT_VALUE_FOR_SearchInputIncrementalAttributeAndSearchEventEnabled, false),
        API::Feature::create("Secure Context Checks"""_s, "SecureContextChecksEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Security, "Allow access to HTTPS-only Web APIs over HTTP"""_s, DEFAULT_VALUE_FOR_SecureContextChecksEnabled, false),
        API::Feature::create("Selection API for shadow DOM"""_s, "SelectionAPIForShadowDOMEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable selection API for shadow DOM"""_s, DEFAULT_VALUE_FOR_SelectionAPIForShadowDOMEnabled, false),
        API::Feature::create("Selection Flipping"""_s, "SelectionFlippingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable Selection Flipping"""_s, DEFAULT_VALUE_FOR_SelectionFlippingEnabled, false),
        API::Feature::create("Send mouse events to disabled form controls"""_s, "SendMouseEventsToDisabledFormControlsEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::HTML, "Send mouse events to disabled form controls"""_s, DEFAULT_VALUE_FOR_SendMouseEventsToDisabledFormControlsEnabled, false),
        API::Feature::create("Server Timing"""_s, "ServerTimingEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Networking, "Enable Server Timing API"""_s, DEFAULT_VALUE_FOR_ServerTimingEnabled, false),
#if ENABLE(SERVICE_WORKER)
        API::Feature::create("Service Worker Navigation Preload"""_s, "ServiceWorkerNavigationPreloadEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Networking, "Enable Service Worker Navigation Preload API"""_s, DEFAULT_VALUE_FOR_ServiceWorkerNavigationPreloadEnabled, false),
#endif
#if ENABLE(SERVICE_WORKER)
        API::Feature::create("Service Workers"""_s, "ServiceWorkersEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Service Workers"""_s, DEFAULT_VALUE_FOR_ServiceWorkersEnabled, false),
#endif
        API::Feature::create("Shape Detection API"""_s, "ShapeDetection"_s, API::FeatureStatus::Testable, API::FeatureCategory::Media, "Enable the Shape Detection API"""_s, DEFAULT_VALUE_FOR_ShapeDetection, false),
        API::Feature::create("SharedWorker"""_s, "SharedWorkerEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enabled SharedWorker API"""_s, DEFAULT_VALUE_FOR_SharedWorkerEnabled, false),
        API::Feature::create("Show Media Stats"""_s, "ShowMediaStatsContextMenuItemEnabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::Media, "Adds a 'Media Stats' context menu item to <video> when the Develop menu is enabled"""_s, DEFAULT_VALUE_FOR_ShowMediaStatsContextMenuItemEnabled, false),
        API::Feature::create("Site Isolation"""_s, "SiteIsolationEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::Security, "Put cross-origin iframes in a different process"""_s, DEFAULT_VALUE_FOR_SiteIsolationEnabled, false),
        API::Feature::create("SpeechRecognition API"""_s, "SpeechRecognitionEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable SpeechRecognition of WebSpeech API"""_s, DEFAULT_VALUE_FOR_SpeechRecognitionEnabled, false),
        API::Feature::create("SpeechSynthesis API"""_s, "SpeechSynthesisAPIEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "SpeechSynthesis API"""_s, DEFAULT_VALUE_FOR_SpeechSynthesisAPIEnabled, false),
        API::Feature::create("Storage API Estimate"""_s, "StorageAPIEstimateEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Storage API Estimate"""_s, DEFAULT_VALUE_FOR_StorageAPIEstimateEnabled, false),
        API::Feature::create("Storage API"""_s, "StorageAPIEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Storage API"""_s, DEFAULT_VALUE_FOR_StorageAPIEnabled, false),
        API::Feature::create("Storage Access API"""_s, "StorageAccessAPIEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Storage Access API"""_s, DEFAULT_VALUE_FOR_StorageAccessAPIEnabled, false),
        API::Feature::create("Swap Processes on Cross-Site Navigation"""_s, "ProcessSwapOnCrossSiteNavigationEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Networking, "Swap WebContent Processes on cross-site navigations"""_s, DEFAULT_VALUE_FOR_ProcessSwapOnCrossSiteNavigationEnabled, false),
        API::Feature::create("Swap Processes on Cross-Site Window Open"""_s, "ProcessSwapOnCrossSiteWindowOpenEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::Networking, "Swap WebContent Processes on cross-site window.open"""_s, DEFAULT_VALUE_FOR_ProcessSwapOnCrossSiteWindowOpenEnabled, false),
        API::Feature::create("Synthetic Editing Commands"""_s, "SyntheticEditingCommandsEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Synthetic Editing Commands"""_s, DEFAULT_VALUE_FOR_SyntheticEditingCommandsEnabled, false),
        API::Feature::create("Take WebKit:NearSuspended assertions on background web content processes"""_s, "ShouldTakeNearSuspendedAssertions"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Take WebKit:NearSuspended assertions on background web content processes"""_s, DEFAULT_VALUE_FOR_ShouldTakeNearSuspendedAssertions, false),
#if ENABLE(IMAGE_ANALYSIS)
        API::Feature::create("Text Recognition in Videos"""_s, "TextRecognitionInVideosEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable Text Recognition in Videos"""_s, DEFAULT_VALUE_FOR_TextRecognitionInVideosEnabled, false),
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
        API::Feature::create("Threaded animation resolution"""_s, "ThreadedAnimationResolutionEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::Animation, "Run accelerated animations on a separate thread"""_s, DEFAULT_VALUE_FOR_ThreadedAnimationResolutionEnabled, false),
#endif
        API::Feature::create("Tiled scrolling indicator"""_s, "TiledScrollingIndicatorVisible"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Make tiled scrolling indicator visible"""_s, DEFAULT_VALUE_FOR_TiledScrollingIndicatorVisible, false),
#if ENABLE(INPUT_TYPE_TIME)
        API::Feature::create("Time Input"""_s, "InputTypeTimeEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable input elements of type time"""_s, DEFAULT_VALUE_FOR_InputTypeTimeEnabled, false),
#endif
        API::Feature::create("Track Configuration API"""_s, "TrackConfigurationEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Media, "Track Configuration API"""_s, DEFAULT_VALUE_FOR_TrackConfigurationEnabled, false),
        API::Feature::create("TransformStream API"""_s, "TransformStreamAPIEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Transform Stream API"""_s, DEFAULT_VALUE_FOR_TransformStreamAPIEnabled, false),
        API::Feature::create("UndoManager DOM API"""_s, "UndoManagerAPIEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Enable the UndoManager DOM API"""_s, DEFAULT_VALUE_FOR_UndoManagerAPIEnabled, false),
        API::Feature::create("Unprefixed Fullscreen API"""_s, "UnprefixedFullscreenAPIEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Unprefixed Fullscreen API"""_s, DEFAULT_VALUE_FOR_UnprefixedFullscreenAPIEnabled, false),
        API::Feature::create("Upgrade known hosts to HTTPS"""_s, "UpgradeKnownHostsToHTTPSEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Networking, "Upgrade known hosts to HTTPS"""_s, DEFAULT_VALUE_FOR_UpgradeKnownHostsToHTTPSEnabled, false),
#if ENABLE(ARKIT_INLINE_PREVIEW)
        API::Feature::create("Use ARKit for <model>"""_s, "UseARKitForModel"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Use ARKit for <model>"""_s, DEFAULT_VALUE_FOR_UseARKitForModel, false),
#endif
        API::Feature::create("Use General Directory For Storage"""_s, "UseGeneralDirectoryForStorage"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Use general storage directory for IndexedDB and LocalStorage"""_s, DEFAULT_VALUE_FOR_UseGeneralDirectoryForStorage, false),
#if HAVE(SC_CONTENT_SHARING_PICKER)
        API::Feature::create("Use SCContentSharingPicker"""_s, "UseSCContentSharingPicker"_s, API::FeatureStatus::Internal, API::FeatureCategory::None, "Use SCContentSharingPicker when available"""_s, DEFAULT_VALUE_FOR_UseSCContentSharingPicker, false),
#endif
#if HAVE(SCENEKIT)
        API::Feature::create("Use SceneKit for <model>"""_s, "UseSceneKitForModel"_s, API::FeatureStatus::Unstable, API::FeatureCategory::None, "Use SceneKit for <model>"""_s, DEFAULT_VALUE_FOR_UseSceneKitForModel, false),
#endif
        API::Feature::create("Use giant tiles"""_s, "UseGiantTiles"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, """"_s, DEFAULT_VALUE_FOR_UseGiantTiles, false),
        API::Feature::create("User Activation API"""_s, "UserActivationAPIEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable User Activation API"""_s, DEFAULT_VALUE_FOR_UserActivationAPIEnabled, false),
        API::Feature::create("UserGesture Promise Propagation"""_s, "UserGesturePromisePropagationEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "UserGesture Promise Propagation"""_s, DEFAULT_VALUE_FOR_UserGesturePromisePropagationEnabled, false),
#if ENABLE(VP9)
        API::Feature::create("VP9 SW decoder on battery"""_s, "VP9SWDecoderEnabledOnBattery"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable VP9 SW decoder on battery"""_s, DEFAULT_VALUE_FOR_VP9SWDecoderEnabledOnBattery, false),
#endif
#if ENABLE(SERVICE_WORKER)
        API::Feature::create("Validate UserGesture requirements in Service Workers"""_s, "ServiceWorkersUserGestureEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Validate UserGesture requirements in Service Workers"""_s, DEFAULT_VALUE_FOR_ServiceWorkersUserGestureEnabled, false),
#endif
        API::Feature::create("Verify window.open user gesture"""_s, "VerifyWindowOpenUserGestureFromUIProcess"_s, API::FeatureStatus::Testable, API::FeatureCategory::Security, "Verifies that the user gesture for window.open came from the UI process"""_s, DEFAULT_VALUE_FOR_VerifyWindowOpenUserGestureFromUIProcess, false),
        API::Feature::create("Vertical form control support"""_s, "VerticalFormControlsEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::HTML, "Enable support for form controls in vertical writing mode"""_s, DEFAULT_VALUE_FOR_VerticalFormControlsEnabled, false),
        API::Feature::create("View gesture debugging"""_s, "ViewGestureDebuggingEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable view gesture debugging"""_s, DEFAULT_VALUE_FOR_ViewGestureDebuggingEnabled, false),
#if ENABLE(IMAGE_ANALYSIS)
        API::Feature::create("Visual Translation"""_s, "VisualTranslationEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable Visual Translation"""_s, DEFAULT_VALUE_FOR_VisualTranslationEnabled, false),
#endif
        API::Feature::create("Visual Viewport API"""_s, "VisualViewportAPIEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Visual Viewport API"""_s, DEFAULT_VALUE_FOR_VisualViewportAPIEnabled, false),
#if ENABLE(VORBIS)
        API::Feature::create("Vorbis audio decoder"""_s, "VorbisDecoderEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable Vorbis audio decoder"""_s, DEFAULT_VALUE_FOR_VorbisDecoderEnabled, false),
#endif
        API::Feature::create("Web API Statistics"""_s, "WebAPIStatisticsEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Enable Web API Statistics"""_s, DEFAULT_VALUE_FOR_WebAPIStatisticsEnabled, false),
        API::Feature::create("Web APIs in ShadowRealm"""_s, "WebAPIsInShadowRealmEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Enable Web APIs to be exposed in ShadowRealm"""_s, DEFAULT_VALUE_FOR_WebAPIsInShadowRealmEnabled, false),
        API::Feature::create("Web Animations composite operations"""_s, "WebAnimationsCompositeOperationsEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Animation, "Support for the CompositeOperation enum and properties consuming it"""_s, DEFAULT_VALUE_FOR_WebAnimationsCompositeOperationsEnabled, false),
        API::Feature::create("Web Animations custom effects"""_s, "WebAnimationsCustomEffectsEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Animation, "Support for the CustomEffect interface"""_s, DEFAULT_VALUE_FOR_WebAnimationsCustomEffectsEnabled, false),
        API::Feature::create("Web Animations custom frame rate"""_s, "WebAnimationsCustomFrameRateEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Animation, "Support for specifying a custom frame rate for Web Animations"""_s, DEFAULT_VALUE_FOR_WebAnimationsCustomFrameRateEnabled, false),
        API::Feature::create("Web Animations iteration composite"""_s, "WebAnimationsIterationCompositeEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Animation, "Support for the KeyframeEffect.iterationComposite property"""_s, DEFAULT_VALUE_FOR_WebAnimationsIterationCompositeEnabled, false),
        API::Feature::create("Web Animations mutable timelines"""_s, "WebAnimationsMutableTimelinesEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Animation, "Support for setting the timeline property of an Animation object"""_s, DEFAULT_VALUE_FOR_WebAnimationsMutableTimelinesEnabled, false),
#if ENABLE(WEB_ARCHIVE)
        API::Feature::create("Web Archive debug mode"""_s, "WebArchiveDebugModeEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable web archive debug mode"""_s, DEFAULT_VALUE_FOR_WebArchiveDebugModeEnabled, false),
#endif
#if ENABLE(WEB_ARCHIVE)
        API::Feature::create("Web Archive testing mode"""_s, "WebArchiveTestingModeEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable web archive testing mode"""_s, DEFAULT_VALUE_FOR_WebArchiveTestingModeEnabled, false),
#endif
#if ENABLE(WEB_AUTHN)
        API::Feature::create("Web Authentication"""_s, "WebAuthenticationEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable Web Authentication support"""_s, DEFAULT_VALUE_FOR_WebAuthenticationEnabled, false),
#endif
        API::Feature::create("Web Crypto Safe Curves"""_s, "WebCryptoSafeCurvesEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable Web Crypto Safe Curves"""_s, DEFAULT_VALUE_FOR_WebCryptoSafeCurvesEnabled, false),
        API::Feature::create("Web Locks API"""_s, "WebLocksAPIEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Web Locks API"""_s, DEFAULT_VALUE_FOR_WebLocksAPIEnabled, false),
        API::Feature::create("Web Share API Level 2"""_s, "WebShareFileAPIEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::DOM, "Enable level 2 of Web Share API"""_s, DEFAULT_VALUE_FOR_WebShareFileAPIEnabled, false),
        API::Feature::create("Web Share"""_s, "WebShareEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable support for share sheet via Web Share API"""_s, DEFAULT_VALUE_FOR_WebShareEnabled, false),
#if ENABLE(WEBASSEMBLY)
        API::Feature::create("WebAssembly ES module integration support"""_s, "WebAssemblyESMIntegrationEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Javascript, "Support for allowing WebAssembly modules to integrate as ES modules"""_s, DEFAULT_VALUE_FOR_WebAssemblyESMIntegrationEnabled, false),
#endif
#if ENABLE(WEB_CODECS)
        API::Feature::create("WebCodecs API"""_s, "WebCodecsEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "Enable WebCodecs API"""_s, DEFAULT_VALUE_FOR_WebCodecsEnabled, false),
#endif
#if ENABLE(WEB_CODECS)
        API::Feature::create("WebCodecs AV1 codec"""_s, "WebCodecsAV1Enabled"_s, API::FeatureStatus::Preview, API::FeatureCategory::Media, "Enable WebCodecs AV1 codec"""_s, DEFAULT_VALUE_FOR_WebCodecsAV1Enabled, false),
#endif
#if ENABLE(WEB_CODECS)
        API::Feature::create("WebCodecs HEVC codec"""_s, "WebCodecsHEVCEnabled"_s, API::FeatureStatus::Preview, API::FeatureCategory::Media, "Enable WebCodecs HEVC codec"""_s, DEFAULT_VALUE_FOR_WebCodecsHEVCEnabled, false),
#endif
        API::Feature::create("WebGL Draft Extensions"""_s, "WebGLDraftExtensionsEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::None, "Enable WebGL extensions that are still in draft status"""_s, DEFAULT_VALUE_FOR_WebGLDraftExtensionsEnabled, false),
        API::Feature::create("WebGL Timer Queries"""_s, "WebGLTimerQueriesEnabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::DOM, "Enable WebGL extensions that provide GPU timer queries"""_s, DEFAULT_VALUE_FOR_WebGLTimerQueriesEnabled, false),
#if ENABLE(WEBGL) && PLATFORM(COCOA)
        API::Feature::create("WebGL via Metal"""_s, "WebGLUsingMetal"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Use the Metal backend for ANGLE"""_s, DEFAULT_VALUE_FOR_WebGLUsingMetal, false),
#endif
        API::Feature::create("WebGL"""_s, "WebGLEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable WebGL"""_s, DEFAULT_VALUE_FOR_WebGLEnabled, false),
        API::Feature::create("WebGPU"""_s, "WebGPUEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::None, "Enable WebGPU"""_s, DEFAULT_VALUE_FOR_WebGPUEnabled, false),
        API::Feature::create("WebInspector engineering settings allowed"""_s, "WebInspectorEngineeringSettingsAllowed"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, """"_s, DEFAULT_VALUE_FOR_WebInspectorEngineeringSettingsAllowed, false),
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC AV1 codec"""_s, "WebRTCAV1CodecEnabled"_s, API::FeatureStatus::Preview, API::FeatureCategory::Media, "Enable WebRTC AV1 codec"""_s, DEFAULT_VALUE_FOR_WebRTCAV1CodecEnabled, false),
#endif
        API::Feature::create("WebRTC Audio Latency Adaptation"""_s, "WebRTCAudioLatencyAdaptationEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable WebRTC Audio Latency Adaptation"""_s, DEFAULT_VALUE_FOR_WebRTCAudioLatencyAdaptationEnabled, false),
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC DTMF"""_s, "WebRTCDTMFEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable WebRTC DTMF"""_s, DEFAULT_VALUE_FOR_WebRTCDTMFEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC Encoded Transform API"""_s, "WebRTCEncodedTransformEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::Media, "Enable WebRTC Encoded Transform API"""_s, DEFAULT_VALUE_FOR_WebRTCEncodedTransformEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC H264 Hardware encoder"""_s, "WebRTCH264HardwareEncoderEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable H264 Hardware encoder"""_s, DEFAULT_VALUE_FOR_WebRTCH264HardwareEncoderEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC H264 LowLatency encoder"""_s, "WebRTCH264LowLatencyEncoderEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable H264 LowLatency encoder"""_s, DEFAULT_VALUE_FOR_WebRTCH264LowLatencyEncoderEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC H264 Simulcast"""_s, "WebRTCH264SimulcastEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable WebRTC H264 Simulcast"""_s, DEFAULT_VALUE_FOR_WebRTCH264SimulcastEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC H265 codec"""_s, "WebRTCH265CodecEnabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::Media, "Enable WebRTC H265 codec"""_s, DEFAULT_VALUE_FOR_WebRTCH265CodecEnabled, false),
#endif
#if USE(LIBWEBRTC)
        API::Feature::create("WebRTC Media Pipeline Additional Logging"""_s, "WebRTCMediaPipelineAdditionalLoggingEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable WebRTC Media Pipeline Additional Logging"""_s, DEFAULT_VALUE_FOR_WebRTCMediaPipelineAdditionalLoggingEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC Peer Connection"""_s, "PeerConnectionEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable RTCPeerConnection"""_s, DEFAULT_VALUE_FOR_PeerConnectionEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC Platform TCP Sockets"""_s, "WebRTCPlatformTCPSocketsEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable WebRTC Platform TCP Sockets"""_s, DEFAULT_VALUE_FOR_WebRTCPlatformTCPSocketsEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC Platform UDP Sockets"""_s, "WebRTCPlatformUDPSocketsEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable WebRTC Platform UDP Sockets"""_s, DEFAULT_VALUE_FOR_WebRTCPlatformUDPSocketsEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC Remote Video Frame"""_s, "WebRTCRemoteVideoFrameEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable WebRTC Remote Video Frame"""_s, DEFAULT_VALUE_FOR_WebRTCRemoteVideoFrameEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC SFrame Transform API"""_s, "WebRTCSFrameTransformEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::Media, "Enable WebRTC SFrame Transform API"""_s, DEFAULT_VALUE_FOR_WebRTCSFrameTransformEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC Sockets Proxying"""_s, "WebRTCSocketsProxyingEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable WebRTC Sockets Proxying"""_s, DEFAULT_VALUE_FOR_WebRTCSocketsProxyingEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC VP9 profile 0 codec"""_s, "WebRTCVP9Profile0CodecEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::Media, "Enable WebRTC VP9 profile 0 codec"""_s, DEFAULT_VALUE_FOR_WebRTCVP9Profile0CodecEnabled, false),
#endif
#if ENABLE(WEB_RTC)
        API::Feature::create("WebRTC VP9 profile 2 codec"""_s, "WebRTCVP9Profile2CodecEnabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::Media, "Enable WebRTC VP9 profile 2 codec"""_s, DEFAULT_VALUE_FOR_WebRTCVP9Profile2CodecEnabled, false),
#endif
#if ENABLE(WEBXR)
        API::Feature::create("WebXR Augmented Reality Module"""_s, "WebXRAugmentedRealityModuleEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Adds support for the WebXR Augmented Reality Module"""_s, DEFAULT_VALUE_FOR_WebXRAugmentedRealityModuleEnabled, false),
#endif
#if ENABLE(WEBXR)
        API::Feature::create("WebXR Device API"""_s, "WebXREnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Adds support for accessing virtual reality (VR) and augmented reality (AR) devices, including sensors and head-mounted displays, on the Web"""_s, DEFAULT_VALUE_FOR_WebXREnabled, false),
#endif
#if ENABLE(WEBXR)
        API::Feature::create("WebXR Gamepads Module"""_s, "WebXRGamepadsModuleEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Adds support for the WebXR Gamepads Module"""_s, DEFAULT_VALUE_FOR_WebXRGamepadsModuleEnabled, false),
#endif
#if ENABLE(WEBXR_HANDS)
        API::Feature::create("WebXR Hand Input Module"""_s, "WebXRHandInputModuleEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::DOM, "Adds support for the Hands Input Module for WebXR"""_s, DEFAULT_VALUE_FOR_WebXRHandInputModuleEnabled, false),
#endif
#if ENABLE(INPUT_TYPE_WEEK)
        API::Feature::create("Week Input"""_s, "InputTypeWeekEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable input elements of type week"""_s, DEFAULT_VALUE_FOR_InputTypeWeekEnabled, false),
#endif
        API::Feature::create("Wheel Event gestures become non-blocking"""_s, "WheelEventGesturesBecomeNonBlocking"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "preventDefault() is only allowed on the first wheel event in a gesture"""_s, DEFAULT_VALUE_FOR_WheelEventGesturesBecomeNonBlocking, false),
        API::Feature::create("Wheel Event listeners on the root made passive"""_s, "PassiveWheelListenersAsDefaultOnDocument"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Force wheel event listeners registered on the window, document or body to be passive"""_s, DEFAULT_VALUE_FOR_PassiveWheelListenersAsDefaultOnDocument, false),
        API::Feature::create("[ITP Live-On] 1 Hour Timeout For Non-Cookie Data Removal"""_s, "IsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::Privacy, "Remove all non-cookie website data after just one hour of no user interaction when Intelligent Tracking Prevention is enabled"""_s, DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled, false),
        API::Feature::create("[ITP Repro] 30 Second Timeout For Non-Cookie Data Removal"""_s, "IsFirstPartyWebsiteDataRemovalReproTestingEnabled"_s, API::FeatureStatus::Developer, API::FeatureCategory::Privacy, "Remove all non-cookie website data after just 30 seconds of no user interaction when Intelligent Tracking Prevention is enabled"""_s, DEFAULT_VALUE_FOR_IsFirstPartyWebsiteDataRemovalReproTestingEnabled, false),
#if ENABLE(INPUT_TYPE_DATETIMELOCAL)
        API::Feature::create("datetime-local Inputs"""_s, "InputTypeDateTimeLocalEnabled"_s, API::FeatureStatus::Embedder, API::FeatureCategory::None, "Enable input elements of type datetime-local"""_s, DEFAULT_VALUE_FOR_InputTypeDateTimeLocalEnabled, false),
#endif
        API::Feature::create("http-equiv"""_s, "HTTPEquivEnabled"_s, API::FeatureStatus::Mature, API::FeatureCategory::None, "Enable http-equiv attribute"""_s, DEFAULT_VALUE_FOR_HTTPEquivEnabled, false),
#if ENABLE(IOS_FORM_CONTROL_REFRESH)
        API::Feature::create("iOS Form Control Refresh"""_s, "IOSFormControlRefreshEnabled"_s, API::FeatureStatus::Internal, API::FeatureCategory::DOM, "Enable the new appearance for form controls on iOS"""_s, DEFAULT_VALUE_FOR_IOSFormControlRefreshEnabled, false),
#endif
        API::Feature::create("lh / rlh units"""_s, "LineHeightUnitsEnabled"_s, API::FeatureStatus::Stable, API::FeatureCategory::CSS, "Enable the lh and rlh units"""_s, DEFAULT_VALUE_FOR_LineHeightUnitsEnabled, false),
        API::Feature::create("requestIdleCallback"""_s, "RequestIdleCallbackEnabled"_s, API::FeatureStatus::Unstable, API::FeatureCategory::DOM, "Enable requestIdleCallback support"""_s, DEFAULT_VALUE_FOR_RequestIdleCallbackEnabled, false),
        API::Feature::create("word-break: auto enabled"""_s, "CSSWordBreakAutoEnabled"_s, API::FeatureStatus::Testable, API::FeatureCategory::CSS, "Enables the auto value of the word-break CSS property"""_s, DEFAULT_VALUE_FOR_CSSWordBreakAutoEnabled, false),
    });

    return features;
}

bool WebPreferences::isFeatureEnabled(const API::Feature& feature) const
{
    struct FeatureGetterMapping {
        ASCIILiteral name;
        bool (WebPreferences::*function) () const;
    };

    static FeatureGetterMapping getters[] = {
        { "AcceleratedCompositingEnabled"_s, &WebPreferences::acceleratedCompositingEnabled },
        { "AcceleratedCompositingForFixedPositionEnabled"_s, &WebPreferences::acceleratedCompositingForFixedPositionEnabled },
        { "AggressiveTileRetentionEnabled"_s, &WebPreferences::aggressiveTileRetentionEnabled },
        { "AllowContentSecurityPolicySourceStarToMatchAnyProtocol"_s, &WebPreferences::allowContentSecurityPolicySourceStarToMatchAnyProtocol },
        { "AllowCrossOriginSubresourcesToAskForCredentials"_s, &WebPreferences::allowCrossOriginSubresourcesToAskForCredentials },
        { "AllowDisplayOfInsecureContent"_s, &WebPreferences::allowDisplayOfInsecureContent },
        { "AllowFileAccessFromFileURLs"_s, &WebPreferences::allowFileAccessFromFileURLs },
        { "AllowMultiElementImplicitSubmission"_s, &WebPreferences::allowMultiElementImplicitSubmission },
        { "AllowRunningOfInsecureContent"_s, &WebPreferences::allowRunningOfInsecureContent },
        { "AllowSettingAnyXHRHeaderFromFileURLs"_s, &WebPreferences::allowSettingAnyXHRHeaderFromFileURLs },
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
        { "AllowsAirPlayForMediaPlayback"_s, &WebPreferences::allowsAirPlayForMediaPlayback },
#endif
        { "AllowsInlineMediaPlayback"_s, &WebPreferences::allowsInlineMediaPlayback },
        { "AllowsInlineMediaPlaybackAfterFullscreen"_s, &WebPreferences::allowsInlineMediaPlaybackAfterFullscreen },
        { "AllowsPictureInPictureMediaPlayback"_s, &WebPreferences::allowsPictureInPictureMediaPlayback },
#if PLATFORM(IOS_FAMILY)
        { "AlternateFormControlDesignEnabled"_s, &WebPreferences::alternateFormControlDesignEnabled },
#endif
#if PLATFORM(IOS_FAMILY)
        { "AlternateFullScreenControlDesignEnabled"_s, &WebPreferences::alternateFullScreenControlDesignEnabled },
#endif
        { "AnimatedImageAsyncDecodingEnabled"_s, &WebPreferences::animatedImageAsyncDecodingEnabled },
        { "AppleMailPaginationQuirkEnabled"_s, &WebPreferences::appleMailPaginationQuirkEnabled },
#if ENABLE(APPLE_PAY)
        { "ApplePayCapabilityDisclosureAllowed"_s, &WebPreferences::applePayCapabilityDisclosureAllowed },
#endif
#if ENABLE(APPLE_PAY)
        { "ApplePayEnabled"_s, &WebPreferences::applePayEnabled },
#endif
        { "AsynchronousSpellCheckingEnabled"_s, &WebPreferences::asynchronousSpellCheckingEnabled },
        { "AudioControlsScaleWithPageZoom"_s, &WebPreferences::audioControlsScaleWithPageZoom },
        { "AuthorAndUserStylesEnabled"_s, &WebPreferences::authorAndUserStylesEnabled },
        { "BackspaceKeyNavigationEnabled"_s, &WebPreferences::backspaceKeyNavigationEnabled },
        { "CaretBrowsingEnabled"_s, &WebPreferences::caretBrowsingEnabled },
        { "ColorFilterEnabled"_s, &WebPreferences::colorFilterEnabled },
        { "ConstantPropertiesEnabled"_s, &WebPreferences::constantPropertiesEnabled },
#if ENABLE(CONTENT_CHANGE_OBSERVER)
        { "ContentChangeObserverEnabled"_s, &WebPreferences::contentChangeObserverEnabled },
#endif
        { "ContentDispositionAttachmentSandboxEnabled"_s, &WebPreferences::contentDispositionAttachmentSandboxEnabled },
#if ENABLE(CONTEXT_MENU_QR_CODE_DETECTION)
        { "ContextMenuQRCodeDetectionEnabled"_s, &WebPreferences::contextMenuQRCodeDetectionEnabled },
#endif
        { "DNSPrefetchingEnabled"_s, &WebPreferences::dnsPrefetchingEnabled },
        { "DOMPasteAllowed"_s, &WebPreferences::domPasteAllowed },
        { "DatabasesEnabled"_s, &WebPreferences::databasesEnabled },
        { "DeveloperExtrasEnabled"_s, &WebPreferences::developerExtrasEnabled },
#if ENABLE(DEVICE_ORIENTATION)
        { "DeviceOrientationEventEnabled"_s, &WebPreferences::deviceOrientationEventEnabled },
#endif
#if ENABLE(DEVICE_ORIENTATION)
        { "DeviceOrientationPermissionAPIEnabled"_s, &WebPreferences::deviceOrientationPermissionAPIEnabled },
#endif
        { "DisabledAdaptationsMetaTagEnabled"_s, &WebPreferences::disabledAdaptationsMetaTagEnabled },
#if ENABLE(DOWNLOAD_ATTRIBUTE)
        { "DownloadAttributeEnabled"_s, &WebPreferences::downloadAttributeEnabled },
#endif
        { "EnableInheritURIQueryComponent"_s, &WebPreferences::enableInheritURIQueryComponent },
#if ENABLE(ENCRYPTED_MEDIA)
        { "EncryptedMediaAPIEnabled"_s, &WebPreferences::encryptedMediaAPIEnabled },
#endif
#if HAVE(APP_SSO)
        { "ExtensibleSSOEnabled"_s, &WebPreferences::isExtensibleSSOEnabled },
#endif
        { "ForceCompositingMode"_s, &WebPreferences::forceCompositingMode },
        { "ForceFTPDirectoryListings"_s, &WebPreferences::forceFTPDirectoryListings },
        { "ForceWebGLUsesLowPower"_s, &WebPreferences::forceWebGLUsesLowPower },
#if USE(GSTREAMER)
        { "GStreamerEnabled"_s, &WebPreferences::isGStreamerEnabled },
#endif
        { "HiddenPageCSSAnimationSuspensionEnabled"_s, &WebPreferences::hiddenPageCSSAnimationSuspensionEnabled },
        { "IncompleteImageBorderEnabled"_s, &WebPreferences::incompleteImageBorderEnabled },
#if HAVE(INCREMENTAL_PDF_APIS)
        { "IncrementalPDFLoadingEnabled"_s, &WebPreferences::incrementalPDFLoadingEnabled },
#endif
        { "InlineMediaPlaybackRequiresPlaysInlineAttribute"_s, &WebPreferences::inlineMediaPlaybackRequiresPlaysInlineAttribute },
        { "InspectorStartsAttached"_s, &WebPreferences::inspectorStartsAttached },
#if ENABLE(MEDIA_STREAM)
        { "InterruptAudioOnPageVisibilityChangeEnabled"_s, &WebPreferences::interruptAudioOnPageVisibilityChangeEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "InterruptVideoOnPageVisibilityChangeEnabled"_s, &WebPreferences::interruptVideoOnPageVisibilityChangeEnabled },
#endif
        { "InvisibleAutoplayNotPermitted"_s, &WebPreferences::invisibleAutoplayNotPermitted },
        { "JavaScriptCanAccessClipboard"_s, &WebPreferences::javaScriptCanAccessClipboard },
        { "JavaScriptCanOpenWindowsAutomatically"_s, &WebPreferences::javaScriptCanOpenWindowsAutomatically },
        { "JavaScriptMarkupEnabled"_s, &WebPreferences::javaScriptMarkupEnabled },
        { "LargeImageAsyncDecodingEnabled"_s, &WebPreferences::largeImageAsyncDecodingEnabled },
        { "LinkPreconnect"_s, &WebPreferences::linkPreconnect },
        { "LinkPreloadEnabled"_s, &WebPreferences::linkPreloadEnabled },
        { "LoadDeferringEnabled"_s, &WebPreferences::loadDeferringEnabled },
        { "LoadsImagesAutomatically"_s, &WebPreferences::loadsImagesAutomatically },
        { "LowPowerVideoAudioBufferSizeEnabled"_s, &WebPreferences::lowPowerVideoAudioBufferSizeEnabled },
#if ENABLE(MATHML)
        { "MathMLEnabled"_s, &WebPreferences::mathMLEnabled },
#endif
        { "MediaCapabilitiesEnabled"_s, &WebPreferences::mediaCapabilitiesEnabled },
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS)
        { "MediaControlsContextMenusEnabled"_s, &WebPreferences::mediaControlsContextMenusEnabled },
#endif
        { "MediaControlsScaleWithPageZoom"_s, &WebPreferences::mediaControlsScaleWithPageZoom },
        { "MediaDataLoadsAutomatically"_s, &WebPreferences::mediaDataLoadsAutomatically },
#if ENABLE(VIDEO)
        { "MediaEnabled"_s, &WebPreferences::mediaEnabled },
#endif
        { "MediaPreloadingEnabled"_s, &WebPreferences::mediaPreloadingEnabled },
#if ENABLE(MEDIA_STREAM)
        { "MediaStreamEnabled"_s, &WebPreferences::mediaStreamEnabled },
#endif
        { "MediaUserGestureInheritsFromDocument"_s, &WebPreferences::mediaUserGestureInheritsFromDocument },
        { "MenuItemElementEnabled"_s, &WebPreferences::menuItemElementEnabled },
        { "MockCaptureDevicesPromptEnabled"_s, &WebPreferences::mockCaptureDevicesPromptEnabled },
        { "MockScrollbarsControllerEnabled"_s, &WebPreferences::mockScrollbarsControllerEnabled },
        { "MockScrollbarsEnabled"_s, &WebPreferences::mockScrollbarsEnabled },
        { "NeedsAdobeFrameReloadingQuirk"_s, &WebPreferences::needsAdobeFrameReloadingQuirk },
        { "NeedsFrameNameFallbackToIdQuirk"_s, &WebPreferences::needsFrameNameFallbackToIdQuirk },
        { "NeedsKeyboardEventDisambiguationQuirks"_s, &WebPreferences::needsKeyboardEventDisambiguationQuirks },
        { "OfflineWebApplicationCacheEnabled"_s, &WebPreferences::offlineWebApplicationCacheEnabled },
#if PLATFORM(COCOA)
        { "PDFPluginEnabled"_s, &WebPreferences::pdfPluginEnabled },
#endif
        { "PassiveTouchListenersAsDefaultOnDocument"_s, &WebPreferences::passiveTouchListenersAsDefaultOnDocument },
        { "PasswordEchoEnabled"_s, &WebPreferences::passwordEchoEnabled },
#if ENABLE(PICTURE_IN_PICTURE_API)
        { "PictureInPictureAPIEnabled"_s, &WebPreferences::pictureInPictureAPIEnabled },
#endif
        { "PluginsEnabled"_s, &WebPreferences::pluginsEnabled },
        { "PunchOutWhiteBackgroundsInDarkMode"_s, &WebPreferences::punchOutWhiteBackgroundsInDarkMode },
        { "RequiresPageVisibilityToPlayAudio"_s, &WebPreferences::requiresPageVisibilityToPlayAudio },
        { "RequiresUserGestureForAudioPlayback"_s, &WebPreferences::requiresUserGestureForAudioPlayback },
        { "RequiresUserGestureForMediaPlayback"_s, &WebPreferences::requiresUserGestureForMediaPlayback },
        { "RequiresUserGestureForVideoPlayback"_s, &WebPreferences::requiresUserGestureForVideoPlayback },
        { "RequiresUserGestureToLoadVideo"_s, &WebPreferences::requiresUserGestureToLoadVideo },
#if HAVE(RUBBER_BANDING)
        { "RubberBandingForSubScrollableRegionsEnabled"_s, &WebPreferences::rubberBandingForSubScrollableRegionsEnabled },
#endif
        { "SelectTrailingWhitespaceEnabled"_s, &WebPreferences::selectTrailingWhitespaceEnabled },
#if ENABLE(SERVICE_CONTROLS)
        { "ServiceControlsEnabled"_s, &WebPreferences::serviceControlsEnabled },
#endif
#if ENABLE(SERVICE_WORKER)
        { "ServiceWorkerEntitlementDisabledForTesting"_s, &WebPreferences::serviceWorkerEntitlementDisabledForTesting },
#endif
        { "ShouldAllowUserInstalledFonts"_s, &WebPreferences::shouldAllowUserInstalledFonts },
        { "ShouldConvertInvalidURLsToBlank"_s, &WebPreferences::shouldConvertInvalidURLsToBlank },
        { "ShouldConvertPositionStyleOnCopy"_s, &WebPreferences::shouldConvertPositionStyleOnCopy },
        { "ShouldDecidePolicyBeforeLoadingQuickLookPreview"_s, &WebPreferences::shouldDecidePolicyBeforeLoadingQuickLookPreview },
#if ENABLE(VIDEO)
        { "ShouldDisplayCaptions"_s, &WebPreferences::shouldDisplayCaptions },
#endif
#if ENABLE(VIDEO)
        { "ShouldDisplaySubtitles"_s, &WebPreferences::shouldDisplaySubtitles },
#endif
#if ENABLE(VIDEO)
        { "ShouldDisplayTextDescriptions"_s, &WebPreferences::shouldDisplayTextDescriptions },
#endif
#if ENABLE(TEXT_AUTOSIZING)
        { "ShouldEnableTextAutosizingBoost"_s, &WebPreferences::shouldEnableTextAutosizingBoost },
#endif
        { "ShouldIgnoreMetaViewport"_s, &WebPreferences::shouldIgnoreMetaViewport },
        { "ShouldPrintBackgrounds"_s, &WebPreferences::shouldPrintBackgrounds },
        { "ShouldRespectImageOrientation"_s, &WebPreferences::shouldRespectImageOrientation },
        { "ShouldRestrictBaseURLSchemes"_s, &WebPreferences::shouldRestrictBaseURLSchemes },
        { "ShouldSuppressTextInputFromEditingDuringProvisionalNavigation"_s, &WebPreferences::shouldSuppressTextInputFromEditingDuringProvisionalNavigation },
        { "ShouldUseServiceWorkerShortTimeout"_s, &WebPreferences::shouldUseServiceWorkerShortTimeout },
        { "ShowsToolTipOverTruncatedText"_s, &WebPreferences::showsToolTipOverTruncatedText },
        { "ShowsURLsInToolTipsEnabled"_s, &WebPreferences::showsURLsInToolTipsEnabled },
        { "ShrinksStandaloneImagesToFit"_s, &WebPreferences::shrinksStandaloneImagesToFit },
        { "SmartInsertDeleteEnabled"_s, &WebPreferences::smartInsertDeleteEnabled },
#if ENABLE(MEDIA_SOURCE)
        { "SourceBufferChangeTypeEnabled"_s, &WebPreferences::sourceBufferChangeTypeEnabled },
#endif
        { "SpatialNavigationEnabled"_s, &WebPreferences::spatialNavigationEnabled },
        { "Standalone"_s, &WebPreferences::standalone },
        { "SuppressesIncrementalRendering"_s, &WebPreferences::suppressesIncrementalRendering },
#if USE(SYSTEM_PREVIEW)
        { "SystemPreviewEnabled"_s, &WebPreferences::systemPreviewEnabled },
#endif
        { "TabsToLinks"_s, &WebPreferences::tabsToLinks },
        { "TelephoneNumberParsingEnabled"_s, &WebPreferences::telephoneNumberParsingEnabled },
        { "TemporaryTileCohortRetentionEnabled"_s, &WebPreferences::temporaryTileCohortRetentionEnabled },
        { "TextAreasAreResizable"_s, &WebPreferences::textAreasAreResizable },
#if ENABLE(TEXT_AUTOSIZING)
        { "TextAutosizingEnabled"_s, &WebPreferences::textAutosizingEnabled },
#endif
        { "TextInteractionEnabled"_s, &WebPreferences::textInteractionEnabled },
        { "ThreadedScrollingEnabled"_s, &WebPreferences::threadedScrollingEnabled },
        { "TreatsAnyTextCSSLinkAsStylesheet"_s, &WebPreferences::treatsAnyTextCSSLinkAsStylesheet },
        { "UseImageDocumentForSubframePDF"_s, &WebPreferences::useImageDocumentForSubframePDF },
        { "UseLegacyBackgroundSizeShorthandBehavior"_s, &WebPreferences::useLegacyBackgroundSizeShorthandBehavior },
        { "UsePreHTML5ParserQuirks"_s, &WebPreferences::usePreHTML5ParserQuirks },
        { "UsesBackForwardCache"_s, &WebPreferences::usesBackForwardCache },
        { "UsesEncodingDetector"_s, &WebPreferences::usesEncodingDetector },
#if ENABLE(VP9)
        { "VP8DecoderEnabled"_s, &WebPreferences::vp8DecoderEnabled },
#endif
#if ENABLE(VP9)
        { "VP9DecoderEnabled"_s, &WebPreferences::vp9DecoderEnabled },
#endif
#if PLATFORM(IOS_FAMILY)
        { "VideoFullscreenRequiresElementFullscreen"_s, &WebPreferences::videoFullscreenRequiresElementFullscreen },
#endif
        { "VideoPresentationModeAPIEnabled"_s, &WebPreferences::videoPresentationModeAPIEnabled },
#if ENABLE(VIDEO)
        { "VideoQualityIncludesDisplayCompositingEnabled"_s, &WebPreferences::videoQualityIncludesDisplayCompositingEnabled },
#endif
        { "VisualViewportEnabled"_s, &WebPreferences::visualViewportEnabled },
        { "WantsBalancedSetDefersLoadingBehavior"_s, &WebPreferences::wantsBalancedSetDefersLoadingBehavior },
#if ENABLE(WEB_AUDIO)
        { "WebAudioEnabled"_s, &WebPreferences::webAudioEnabled },
#endif
#if ENABLE(WEBM_FORMAT_READER)
        { "WebMFormatReaderEnabled"_s, &WebPreferences::webMFormatReaderEnabled },
#endif
#if ENABLE(MEDIA_SOURCE)
        { "WebMParserEnabled"_s, &WebPreferences::webMParserEnabled },
#endif
        { "WebSecurityEnabled"_s, &WebPreferences::webSecurityEnabled },
        { "WebSocketEnabled"_s, &WebPreferences::webSocketEnabled },
        { "WindowFocusRestricted"_s, &WebPreferences::windowFocusRestricted },
        { "WirelessPlaybackTargetAPIEnabled"_s, &WebPreferences::wirelessPlaybackTargetAPIEnabled },
        { "DirPseudoEnabled"_s, &WebPreferences::dirPseudoEnabled },
        { "FocusVisibleEnabled"_s, &WebPreferences::focusVisibleEnabled },
        { "HasPseudoClassEnabled"_s, &WebPreferences::hasPseudoClassEnabled },
        { "PageAtRuleSupportEnabled"_s, &WebPreferences::pageAtRuleSupportEnabled },
        { "AriaReflectionForElementReferencesEnabled"_s, &WebPreferences::ariaReflectionForElementReferencesEnabled },
#if USE(AVFOUNDATION)
        { "AVFoundationEnabled"_s, &WebPreferences::isAVFoundationEnabled },
#endif
        { "AbortSignalAnyOperationEnabled"_s, &WebPreferences::abortSignalAnyOperationEnabled },
#if USE(CORE_IMAGE)
        { "AcceleratedFiltersEnabled"_s, &WebPreferences::acceleratedFiltersEnabled },
#endif
        { "AccessHandleEnabled"_s, &WebPreferences::accessHandleEnabled },
        { "DOMTestingAPIsEnabled"_s, &WebPreferences::domTestingAPIsEnabled },
        { "AllowMediaContentTypesRequiringHardwareSupportAsFallback"_s, &WebPreferences::allowMediaContentTypesRequiringHardwareSupportAsFallback },
#if PLATFORM(IOS_FAMILY)
        { "AllowViewportShrinkToFitContent"_s, &WebPreferences::allowViewportShrinkToFitContent },
#endif
#if ENABLE(WEBGL)
        { "AllowWebGLInWorkers"_s, &WebPreferences::allowWebGLInWorkers },
#endif
#if ENABLE(MEDIA_STREAM)
        { "PerElementSpeakerSelectionEnabled"_s, &WebPreferences::perElementSpeakerSelectionEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "ExposeSpeakersEnabled"_s, &WebPreferences::exposeSpeakersEnabled },
#endif
        { "AllowTopNavigationToDataURLs"_s, &WebPreferences::allowTopNavigationToDataURLs },
        { "AllowUniversalAccessFromFileURLs"_s, &WebPreferences::allowUniversalAccessFromFileURLs },
#if ENABLE(ALTERNATE_WEBM_PLAYER)
        { "AlternateWebMPlayerEnabled"_s, &WebPreferences::alternateWebMPlayerEnabled },
#endif
#if ENABLE(BADGING)
        { "AppBadgeEnabled"_s, &WebPreferences::appBadgeEnabled },
#endif
#if ENABLE(APP_HIGHLIGHTS)
        { "AppHighlightsEnabled"_s, &WebPreferences::appHighlightsEnabled },
#endif
        { "AspectRatioOfImgFromWidthAndHeightEnabled"_s, &WebPreferences::aspectRatioOfImgFromWidthAndHeightEnabled },
        { "AsyncFrameScrollingEnabled"_s, &WebPreferences::asyncFrameScrollingEnabled },
        { "AsyncOverflowScrollingEnabled"_s, &WebPreferences::asyncOverflowScrollingEnabled },
        { "AsyncClipboardAPIEnabled"_s, &WebPreferences::asyncClipboardAPIEnabled },
#if ENABLE(ATTACHMENT_ELEMENT)
        { "AttachmentElementEnabled"_s, &WebPreferences::attachmentElementEnabled },
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
        { "AttachmentWideLayoutEnabled"_s, &WebPreferences::attachmentWideLayoutEnabled },
#endif
#if ENABLE(VIDEO)
        { "ExtendedAudioDescriptionsEnabled"_s, &WebPreferences::extendedAudioDescriptionsEnabled },
#endif
#if ENABLE(VIDEO)
        { "AudioDescriptionsEnabled"_s, &WebPreferences::audioDescriptionsEnabled },
#endif
#if ENABLE(DOM_AUDIO_SESSION)
        { "DOMAudioSessionEnabled"_s, &WebPreferences::domAudioSessionEnabled },
#endif
#if ENABLE(DOM_AUDIO_SESSION)
        { "DOMAudioSessionFullEnabled"_s, &WebPreferences::domAudioSessionFullEnabled },
#endif
        { "BeaconAPIEnabled"_s, &WebPreferences::beaconAPIEnabled },
        { "ThirdPartyIframeRedirectBlockingEnabled"_s, &WebPreferences::thirdPartyIframeRedirectBlockingEnabled },
        { "BroadcastChannelEnabled"_s, &WebPreferences::broadcastChannelEnabled },
        { "BroadcastChannelOriginPartitioningEnabled"_s, &WebPreferences::broadcastChannelOriginPartitioningEnabled },
#if ENABLE(BUILT_IN_NOTIFICATIONS)
        { "BuiltInNotificationsEnabled"_s, &WebPreferences::builtInNotificationsEnabled },
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        { "UseCGDisplayListsForDOMRendering"_s, &WebPreferences::useCGDisplayListsForDOMRendering },
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        { "UseCGDisplayListImageCache"_s, &WebPreferences::useCGDisplayListImageCache },
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        { "ReplayCGDisplayListsIntoBackingStore"_s, &WebPreferences::replayCGDisplayListsIntoBackingStore },
#endif
        { "CSS3DTransformInteroperabilityEnabled"_s, &WebPreferences::css3DTransformInteroperabilityEnabled },
        { "CSSCounterStyleAtRuleImageSymbolsEnabled"_s, &WebPreferences::cssCounterStyleAtRuleImageSymbolsEnabled },
        { "CSSCounterStyleAtRulesEnabled"_s, &WebPreferences::cssCounterStyleAtRulesEnabled },
        { "CSSFontFaceSizeAdjustEnabled"_s, &WebPreferences::cssFontFaceSizeAdjustEnabled },
        { "AccentColorEnabled"_s, &WebPreferences::accentColorEnabled },
        { "AspectRatioEnabled"_s, &WebPreferences::aspectRatioEnabled },
        { "CSSCascadeLayersEnabled"_s, &WebPreferences::cssCascadeLayersEnabled },
        { "CSSColor4"_s, &WebPreferences::cssColor4 },
        { "CSSContainIntrinsicSizeEnabled"_s, &WebPreferences::cssContainIntrinsicSizeEnabled },
        { "CSSContainerQueriesEnabled"_s, &WebPreferences::cssContainerQueriesEnabled },
        { "CSSContainmentEnabled"_s, &WebPreferences::cssContainmentEnabled },
        { "CSSContentVisibilityEnabled"_s, &WebPreferences::cssContentVisibilityEnabled },
        { "CSSCustomPropertiesAndValuesEnabled"_s, &WebPreferences::cssCustomPropertiesAndValuesEnabled },
        { "CSSGradientInterpolationColorSpacesEnabled"_s, &WebPreferences::cssGradientInterpolationColorSpacesEnabled },
        { "CSSGradientPremultipliedAlphaInterpolationEnabled"_s, &WebPreferences::cssGradientPremultipliedAlphaInterpolationEnabled },
        { "CSSIndividualTransformPropertiesEnabled"_s, &WebPreferences::cssIndividualTransformPropertiesEnabled },
        { "CSSInputSecurityEnabled"_s, &WebPreferences::cssInputSecurityEnabled },
        { "MasonryEnabled"_s, &WebPreferences::masonryEnabled },
        { "CSSMotionPathEnabled"_s, &WebPreferences::cssMotionPathEnabled },
        { "CSSNestingEnabled"_s, &WebPreferences::cssNestingEnabled },
        { "OverscrollBehaviorEnabled"_s, &WebPreferences::overscrollBehaviorEnabled },
#if ENABLE(CSS_PAINTING_API)
        { "CSSPaintingAPIEnabled"_s, &WebPreferences::cssPaintingAPIEnabled },
#endif
        { "CSSRelativeColorSyntaxEnabled"_s, &WebPreferences::cssRelativeColorSyntaxEnabled },
        { "CSSRhythmicSizingEnabled"_s, &WebPreferences::cssRhythmicSizingEnabled },
        { "CSSScrollAnchoringEnabled"_s, &WebPreferences::cssScrollAnchoringEnabled },
        { "SpringTimingFunctionEnabled"_s, &WebPreferences::springTimingFunctionEnabled },
        { "CSSTypedOMEnabled"_s, &WebPreferences::cssTypedOMEnabled },
        { "CSSTypedOMColorEnabled"_s, &WebPreferences::cssTypedOMColorEnabled },
        { "MasonryTrackAlignmentEnabled"_s, &WebPreferences::masonryTrackAlignmentEnabled },
        { "CSSColorContrastEnabled"_s, &WebPreferences::cssColorContrastEnabled },
        { "CSSColorMixEnabled"_s, &WebPreferences::cssColorMixEnabled },
        { "CSSMarginTrimEnabled"_s, &WebPreferences::cssMarginTrimEnabled },
        { "OverflowClipEnabled"_s, &WebPreferences::overflowClipEnabled },
        { "CSSScrollbarColorEnabled"_s, &WebPreferences::cssScrollbarColorEnabled },
        { "CSSScrollbarGutterEnabled"_s, &WebPreferences::cssScrollbarGutterEnabled },
        { "CSSScrollbarWidthEnabled"_s, &WebPreferences::cssScrollbarWidthEnabled },
        { "SubgridEnabled"_s, &WebPreferences::subgridEnabled },
        { "CSSTextAlignLastEnabled"_s, &WebPreferences::cssTextAlignLastEnabled },
        { "CSSTextBoxTrimEnabled"_s, &WebPreferences::cssTextBoxTrimEnabled },
        { "CSSTextGroupAlignEnabled"_s, &WebPreferences::cssTextGroupAlignEnabled },
        { "CSSTextJustifyEnabled"_s, &WebPreferences::cssTextJustifyEnabled },
        { "CSSTextSpacingEnabled"_s, &WebPreferences::cssTextSpacingEnabled },
        { "CSSTextUnderlinePositionLeftRightEnabled"_s, &WebPreferences::cssTextUnderlinePositionLeftRightEnabled },
        { "CSSWhiteSpaceLonghandsEnabled"_s, &WebPreferences::cssWhiteSpaceLonghandsEnabled },
        { "CSSTextWrapNewValuesEnabled"_s, &WebPreferences::cssTextWrapNewValuesEnabled },
#if ENABLE(CSS_TRANSFORM_STYLE_OPTIMIZED_3D)
        { "CSSTransformStyleOptimized3DEnabled"_s, &WebPreferences::cssTransformStyleOptimized3DEnabled },
#endif
        { "CSSOMViewScrollingAPIEnabled"_s, &WebPreferences::cssOMViewScrollingAPIEnabled },
        { "CSSOMViewSmoothScrollingEnabled"_s, &WebPreferences::cssOMViewSmoothScrollingEnabled },
        { "CacheAPIEnabled"_s, &WebPreferences::cacheAPIEnabled },
        { "CanvasColorSpaceEnabled"_s, &WebPreferences::canvasColorSpaceEnabled },
        { "CanvasFiltersEnabled"_s, &WebPreferences::canvasFiltersEnabled },
        { "CanvasUsesAcceleratedDrawing"_s, &WebPreferences::canvasUsesAcceleratedDrawing },
#if ENABLE(MEDIA_STREAM)
        { "CaptureAudioInUIProcessEnabled"_s, &WebPreferences::captureAudioInUIProcessEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "CaptureVideoInUIProcessEnabled"_s, &WebPreferences::captureVideoInUIProcessEnabled },
#endif
        { "ClearSiteDataHTTPHeaderEnabled"_s, &WebPreferences::clearSiteDataHTTPHeaderEnabled },
#if ENABLE(BADGING)
        { "ClientBadgeEnabled"_s, &WebPreferences::clientBadgeEnabled },
#endif
#if ENABLE(INPUT_TYPE_COLOR)
        { "InputTypeColorEnabled"_s, &WebPreferences::inputTypeColorEnabled },
#endif
        { "CompositingBordersVisible"_s, &WebPreferences::compositingBordersVisible },
        { "CompositingRepaintCountersVisible"_s, &WebPreferences::compositingRepaintCountersVisible },
        { "CompressionStreamEnabled"_s, &WebPreferences::compressionStreamEnabled },
        { "ConstructableStylesheetsEnabled"_s, &WebPreferences::constructableStylesheetsEnabled },
        { "ContactPickerAPIEnabled"_s, &WebPreferences::contactPickerAPIEnabled },
#if HAVE(AVCONTENTKEYSPECIFIER)
        { "SampleBufferContentKeySessionSupportEnabled"_s, &WebPreferences::sampleBufferContentKeySessionSupportEnabled },
#endif
        { "CookieConsentAPIEnabled"_s, &WebPreferences::cookieConsentAPIEnabled },
        { "CookieStoreAPIExtendedAttributesEnabled"_s, &WebPreferences::cookieStoreAPIExtendedAttributesEnabled },
        { "CookieStoreAPIEnabled"_s, &WebPreferences::cookieStoreAPIEnabled },
        { "CookieEnabled"_s, &WebPreferences::cookieEnabled },
        { "CrossOriginEmbedderPolicyEnabled"_s, &WebPreferences::crossOriginEmbedderPolicyEnabled },
        { "CrossOriginOpenerPolicyEnabled"_s, &WebPreferences::crossOriginOpenerPolicyEnabled },
        { "CustomPasteboardDataEnabled"_s, &WebPreferences::customPasteboardDataEnabled },
        { "DOMPasteAccessRequestsEnabled"_s, &WebPreferences::domPasteAccessRequestsEnabled },
        { "DOMTimersThrottlingEnabled"_s, &WebPreferences::domTimersThrottlingEnabled },
        { "DeclarativeShadowDOMInDOMParserEnabled"_s, &WebPreferences::declarativeShadowDOMInDOMParserEnabled },
#if PLATFORM(IOS_FAMILY)
        { "ZoomOnDoubleTapWhenRoot"_s, &WebPreferences::zoomOnDoubleTapWhenRoot },
#endif
#if PLATFORM(IOS_FAMILY)
        { "AlwaysZoomOnDoubleTap"_s, &WebPreferences::alwaysZoomOnDoubleTap },
#endif
        { "DataTransferItemsEnabled"_s, &WebPreferences::dataTransferItemsEnabled },
#if ENABLE(DATALIST_ELEMENT)
        { "DataListElementEnabled"_s, &WebPreferences::dataListElementEnabled },
#endif
#if ENABLE(INPUT_TYPE_DATE)
        { "InputTypeDateEnabled"_s, &WebPreferences::inputTypeDateEnabled },
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
        { "DateTimeInputsEditableComponentsEnabled"_s, &WebPreferences::dateTimeInputsEditableComponentsEnabled },
#endif
        { "DeclarativeShadowDOMEnabled"_s, &WebPreferences::declarativeShadowDOMEnabled },
        { "DefaultARIAForCustomElementsEnabled"_s, &WebPreferences::defaultARIAForCustomElementsEnabled },
        { "ShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint"_s, &WebPreferences::shouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint },
        { "DeprecateRSAESPKCSWebCryptoEnabled"_s, &WebPreferences::deprecateRSAESPKCSWebCryptoEnabled },
        { "DeprecationReportingEnabled"_s, &WebPreferences::deprecationReportingEnabled },
        { "DiagnosticLoggingEnabled"_s, &WebPreferences::diagnosticLoggingEnabled },
        { "DirectoryUploadEnabled"_s, &WebPreferences::directoryUploadEnabled },
        { "IsThirdPartyCookieBlockingDisabled"_s, &WebPreferences::isThirdPartyCookieBlockingDisabled },
        { "IsFirstPartyWebsiteDataRemovalDisabled"_s, &WebPreferences::isFirstPartyWebsiteDataRemovalDisabled },
#if PLATFORM(IOS_FAMILY)
        { "DisableScreenSizeOverride"_s, &WebPreferences::disableScreenSizeOverride },
#endif
        { "DisallowSyncXHRDuringPageDismissalEnabled"_s, &WebPreferences::disallowSyncXHRDuringPageDismissalEnabled },
        { "DisplayListDrawingEnabled"_s, &WebPreferences::displayListDrawingEnabled },
        { "ShouldDropNearSuspendedAssertionAfterDelay"_s, &WebPreferences::shouldDropNearSuspendedAssertionAfterDelay },
        { "EmbedElementEnabled"_s, &WebPreferences::embedElementEnabled },
        { "AutomaticLiveResizeEnabled"_s, &WebPreferences::automaticLiveResizeEnabled },
        { "CanvasFingerprintingQuirkEnabled"_s, &WebPreferences::canvasFingerprintingQuirkEnabled },
        { "EnumeratingAllNetworkInterfacesEnabled"_s, &WebPreferences::enumeratingAllNetworkInterfacesEnabled },
        { "EnumeratingVisibleNetworkInterfacesEnabled"_s, &WebPreferences::enumeratingVisibleNetworkInterfacesEnabled },
        { "ICECandidateFilteringEnabled"_s, &WebPreferences::iceCandidateFilteringEnabled },
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
        { "LegacyEncryptedMediaAPIEnabled"_s, &WebPreferences::legacyEncryptedMediaAPIEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "MockCaptureDevicesEnabled"_s, &WebPreferences::mockCaptureDevicesEnabled },
#endif
#if ENABLE(PDFJS)
        { "PdfJSViewerEnabled"_s, &WebPreferences::pdfJSViewerEnabled },
#endif
#if PLATFORM(MAC) && USE(RUNNINGBOARD)
        { "BackgroundWebContentRunningBoardThrottlingEnabled"_s, &WebPreferences::backgroundWebContentRunningBoardThrottlingEnabled },
#endif
#if ENABLE(SERVICE_WORKER)
        { "BackgroundFetchAPIEnabled"_s, &WebPreferences::backgroundFetchAPIEnabled },
#endif
#if HAVE(MACH_BOOTSTRAP_EXTENSION) || HAVE(SANDBOX_STATE_FLAGS)
        { "ExperimentalSandboxEnabled"_s, &WebPreferences::experimentalSandboxEnabled },
#endif
        { "StrictSecureDecodingForAllObjC"_s, &WebPreferences::strictSecureDecodingForAllObjC },
        { "EnterKeyHintEnabled"_s, &WebPreferences::enterKeyHintEnabled },
        { "EventHandlerDrivenSmoothKeyboardScrollingEnabled"_s, &WebPreferences::eventHandlerDrivenSmoothKeyboardScrollingEnabled },
#if ENABLE(MEDIA_SESSION_COORDINATOR)
        { "MediaSessionCoordinatorEnabled"_s, &WebPreferences::mediaSessionCoordinatorEnabled },
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR) && ENABLE(MEDIA_SESSION_PLAYLIST)
        { "MediaSessionPlaylistEnabled"_s, &WebPreferences::mediaSessionPlaylistEnabled },
#endif
#if ENABLE(MEDIA_SOURCE) && (HAVE(AVSAMPLEBUFFERVIDEOOUTPUT) || USE(GSTREAMER))
        { "MediaSourceInlinePaintingEnabled"_s, &WebPreferences::mediaSourceInlinePaintingEnabled },
#endif
#if HAVE(NETWORK_LOADER)
        { "CFNetworkNetworkLoaderEnabled"_s, &WebPreferences::cFNetworkNetworkLoaderEnabled },
#endif
        { "FTPEnabled"_s, &WebPreferences::ftpEnabled },
#if PLATFORM(IOS_FAMILY)
        { "PreferFasterClickOverDoubleTap"_s, &WebPreferences::preferFasterClickOverDoubleTap },
#endif
#if PLATFORM(IOS_FAMILY)
        { "FasterClicksEnabled"_s, &WebPreferences::fasterClicksEnabled },
#endif
        { "FetchAPIKeepAliveEnabled"_s, &WebPreferences::fetchAPIKeepAliveEnabled },
        { "FetchAPIEnabled"_s, &WebPreferences::fetchAPIEnabled },
        { "FetchMetadataEnabled"_s, &WebPreferences::fetchMetadataEnabled },
        { "FetchPriorityEnabled"_s, &WebPreferences::fetchPriorityEnabled },
        { "FileSystemAccessEnabled"_s, &WebPreferences::fileSystemAccessEnabled },
        { "FileReaderAPIEnabled"_s, &WebPreferences::fileReaderAPIEnabled },
        { "RestrictedHTTPResponseAccess"_s, &WebPreferences::restrictedHTTPResponseAccess },
#if PLATFORM(IOS_FAMILY)
        { "ForceAlwaysUserScalable"_s, &WebPreferences::forceAlwaysUserScalable },
#endif
        { "RequestSubmitEnabled"_s, &WebPreferences::requestSubmitEnabled },
        { "FormAssociatedCustomElementsEnabled"_s, &WebPreferences::formAssociatedCustomElementsEnabled },
        { "FrameFlatteningEnabled"_s, &WebPreferences::frameFlatteningEnabled },
        { "LayoutFormattingContextEnabled"_s, &WebPreferences::layoutFormattingContextEnabled },
#if ENABLE(FULLSCREEN_API)
        { "FullScreenEnabled"_s, &WebPreferences::fullScreenEnabled },
#endif
#if PLATFORM(VISION)
        { "FullscreenSceneAspectRatioLockingEnabled"_s, &WebPreferences::fullscreenSceneAspectRatioLockingEnabled },
#endif
#if PLATFORM(VISION)
        { "FullscreenSceneDimmingEnabled"_s, &WebPreferences::fullscreenSceneDimmingEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "CaptureAudioInGPUProcessEnabled"_s, &WebPreferences::captureAudioInGPUProcessEnabled },
#endif
#if ENABLE(GPU_PROCESS)
        { "BlockMediaLayerRehostingInWebContentProcess"_s, &WebPreferences::blockMediaLayerRehostingInWebContentProcess },
#endif
#if ENABLE(GPU_PROCESS) && !(PLATFORM(GTK) || PLATFORM(WPE))
        { "UseGPUProcessForCanvasRenderingEnabled"_s, &WebPreferences::useGPUProcessForCanvasRenderingEnabled },
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
        { "ManageCaptureStatusBarInGPUProcessEnabled"_s, &WebPreferences::manageCaptureStatusBarInGPUProcessEnabled },
#endif
#if ENABLE(GPU_PROCESS)
        { "UseGPUProcessForDOMRenderingEnabled"_s, &WebPreferences::useGPUProcessForDOMRenderingEnabled },
#endif
#if ENABLE(GPU_PROCESS) && !USE(GSTREAMER)
        { "UseGPUProcessForMediaEnabled"_s, &WebPreferences::useGPUProcessForMediaEnabled },
#endif
#if HAVE(SCREEN_CAPTURE_KIT)
        { "UseGPUProcessForDisplayCapture"_s, &WebPreferences::useGPUProcessForDisplayCapture },
#endif
#if ENABLE(MEDIA_STREAM)
        { "CaptureVideoInGPUProcessEnabled"_s, &WebPreferences::captureVideoInGPUProcessEnabled },
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
        { "UseGPUProcessForWebGLEnabled"_s, &WebPreferences::useGPUProcessForWebGLEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCPlatformCodecsInGPUProcessEnabled"_s, &WebPreferences::webRTCPlatformCodecsInGPUProcessEnabled },
#endif
#if ENABLE(GAMEPAD)
        { "GamepadTriggerRumbleEnabled"_s, &WebPreferences::gamepadTriggerRumbleEnabled },
#endif
#if ENABLE(GAMEPAD)
        { "GamepadVibrationActuatorEnabled"_s, &WebPreferences::gamepadVibrationActuatorEnabled },
#endif
#if ENABLE(GAMEPAD)
        { "GamepadsEnabled"_s, &WebPreferences::gamepadsEnabled },
#endif
#if ENABLE(VIDEO)
        { "GenericCueAPIEnabled"_s, &WebPreferences::genericCueAPIEnabled },
#endif
#if USE(GRAPHICS_CONTEXT_FILTERS)
        { "GraphicsContextFiltersEnabled"_s, &WebPreferences::graphicsContextFiltersEnabled },
#endif
        { "AcceleratedDrawingEnabled"_s, &WebPreferences::acceleratedDrawingEnabled },
        { "DialogElementEnabled"_s, &WebPreferences::dialogElementEnabled },
#if ENABLE(MODEL_ELEMENT)
        { "ModelElementEnabled"_s, &WebPreferences::modelElementEnabled },
#endif
#if ENABLE(MODEL_ELEMENT)
        { "ModelDocumentEnabled"_s, &WebPreferences::modelDocumentEnabled },
#endif
        { "InteractiveFormValidationEnabled"_s, &WebPreferences::interactiveFormValidationEnabled },
        { "InertAttributeEnabled"_s, &WebPreferences::inertAttributeEnabled },
        { "PopoverAttributeEnabled"_s, &WebPreferences::popoverAttributeEnabled },
        { "HiddenPageDOMTimerThrottlingAutoIncreases"_s, &WebPreferences::hiddenPageDOMTimerThrottlingAutoIncreases },
        { "HiddenPageDOMTimerThrottlingEnabled"_s, &WebPreferences::hiddenPageDOMTimerThrottlingEnabled },
        { "HighlightAPIEnabled"_s, &WebPreferences::highlightAPIEnabled },
        { "HyperlinkAuditingEnabled"_s, &WebPreferences::hyperlinkAuditingEnabled },
#if HAVE(SANDBOX_STATE_FLAGS)
        { "BlockIOKitInWebContentSandbox"_s, &WebPreferences::blockIOKitInWebContentSandbox },
#endif
#if ENABLE(IPC_TESTING_API)
        { "IPCTestingAPIEnabled"_s, &WebPreferences::ipcTestingAPIEnabled },
#endif
        { "ItpDebugModeEnabled"_s, &WebPreferences::itpDebugModeEnabled },
#if ENABLE(TEXT_AUTOSIZING)
        { "TextAutosizingUsesIdempotentMode"_s, &WebPreferences::textAutosizingUsesIdempotentMode },
#endif
#if ENABLE(IMAGE_ANALYSIS)
        { "ImageAnalysisDuringFindInPageEnabled"_s, &WebPreferences::imageAnalysisDuringFindInPageEnabled },
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
        { "ImageAnimationControlEnabled"_s, &WebPreferences::imageAnimationControlEnabled },
#endif
#if ENABLE(SERVICE_CONTROLS)
        { "ImageControlsEnabled"_s, &WebPreferences::imageControlsEnabled },
#endif
        { "ImperativeSlotAPIEnabled"_s, &WebPreferences::imperativeSlotAPIEnabled },
        { "IndexedDBAPIEnabled"_s, &WebPreferences::indexedDBAPIEnabled },
        { "InlinePredictionsInAllEditableElementsEnabled"_s, &WebPreferences::inlinePredictionsInAllEditableElementsEnabled },
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
        { "InteractionRegionsEnabled"_s, &WebPreferences::interactionRegionsEnabled },
#endif
        { "IntersectionObserverEnabled"_s, &WebPreferences::intersectionObserverEnabled },
        { "IsLoggedInAPIEnabled"_s, &WebPreferences::isLoggedInAPIEnabled },
#if ENABLE(ACCESSIBILITY_ISOLATED_TREE)
        { "IsAccessibilityIsolatedTreeEnabled"_s, &WebPreferences::isAccessibilityIsolatedTreeEnabled },
#endif
        { "JavaScriptEnabled"_s, &WebPreferences::javaScriptEnabled },
#if ENABLE(LAYER_BASED_SVG_ENGINE)
        { "LayerBasedSVGEngineEnabled"_s, &WebPreferences::layerBasedSVGEngineEnabled },
#endif
        { "LazyIframeLoadingEnabled"_s, &WebPreferences::lazyIframeLoadingEnabled },
        { "LazyImageLoadingEnabled"_s, &WebPreferences::lazyImageLoadingEnabled },
#if ENABLE(OVERFLOW_SCROLLING_TOUCH)
        { "LegacyOverflowScrollingTouchEnabled"_s, &WebPreferences::legacyOverflowScrollingTouchEnabled },
#endif
        { "LegacyLineLayoutVisualCoverageEnabled"_s, &WebPreferences::legacyLineLayoutVisualCoverageEnabled },
        { "ShowModalDialogEnabled"_s, &WebPreferences::showModalDialogEnabled },
#if ENABLE(MEDIA_STREAM)
        { "MediaCaptureRequiresSecureConnection"_s, &WebPreferences::mediaCaptureRequiresSecureConnection },
#endif
        { "LinkSanitizerEnabled"_s, &WebPreferences::linkSanitizerEnabled },
        { "LinkPreloadResponsiveImagesEnabled"_s, &WebPreferences::linkPreloadResponsiveImagesEnabled },
        { "LinkModulePreloadEnabled"_s, &WebPreferences::linkModulePreloadEnabled },
        { "LinkPreconnectEarlyHintsEnabled"_s, &WebPreferences::linkPreconnectEarlyHintsEnabled },
        { "LinkPrefetchEnabled"_s, &WebPreferences::linkPrefetchEnabled },
        { "LiveRangeSelectionEnabled"_s, &WebPreferences::liveRangeSelectionEnabled },
        { "LocalFileContentSniffingEnabled"_s, &WebPreferences::localFileContentSniffingEnabled },
        { "LocalStorageEnabled"_s, &WebPreferences::localStorageEnabled },
        { "LogsPageMessagesToSystemConsoleEnabled"_s, &WebPreferences::logsPageMessagesToSystemConsoleEnabled },
        { "MainContentUserGestureOverrideEnabled"_s, &WebPreferences::mainContentUserGestureOverrideEnabled },
#if ENABLE(MANAGED_MEDIA_SOURCE)
        { "ManagedMediaSourceEnabled"_s, &WebPreferences::managedMediaSourceEnabled },
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE) && ENABLE(WIRELESS_PLAYBACK_TARGET)
        { "ManagedMediaSourceNeedsAirPlay"_s, &WebPreferences::managedMediaSourceNeedsAirPlay },
#endif
#if ENABLE(WEBGL)
        { "MaskWebGLStringsEnabled"_s, &WebPreferences::maskWebGLStringsEnabled },
#endif
        { "CoreMathMLEnabled"_s, &WebPreferences::coreMathMLEnabled },
        { "MediaCapabilitiesExtensionsEnabled"_s, &WebPreferences::mediaCapabilitiesExtensionsEnabled },
#if ENABLE(MEDIA_SESSION)
        { "MediaSessionEnabled"_s, &WebPreferences::mediaSessionEnabled },
#endif
        { "MediaSourceEnabled"_s, &WebPreferences::mediaSourceEnabled },
#if ENABLE(MEDIA_STREAM)
        { "MediaDevicesEnabled"_s, &WebPreferences::mediaDevicesEnabled },
#endif
#if ENABLE(MEDIA_RECORDER)
        { "MediaRecorderEnabled"_s, &WebPreferences::mediaRecorderEnabled },
#endif
        { "MomentumScrollingAnimatorEnabled"_s, &WebPreferences::momentumScrollingAnimatorEnabled },
#if ENABLE(INPUT_TYPE_MONTH)
        { "InputTypeMonthEnabled"_s, &WebPreferences::inputTypeMonthEnabled },
#endif
#if ENABLE(TOUCH_EVENTS)
        { "MouseEventsSimulationEnabled"_s, &WebPreferences::mouseEventsSimulationEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "MuteCameraOnMicrophoneInterruptionEnabled"_s, &WebPreferences::muteCameraOnMicrophoneInterruptionEnabled },
#endif
#if ENABLE(APP_BOUND_DOMAINS)
        { "NeedsInAppBrowserPrivacyQuirks"_s, &WebPreferences::needsInAppBrowserPrivacyQuirks },
#endif
        { "NeedsSiteSpecificQuirks"_s, &WebPreferences::needsSiteSpecificQuirks },
        { "NeedsStorageAccessFromFileURLsQuirk"_s, &WebPreferences::needsStorageAccessFromFileURLsQuirk },
        { "FlexFormattingContextIntegrationEnabled"_s, &WebPreferences::flexFormattingContextIntegrationEnabled },
        { "InlineFormattingContextIntegrationEnabled"_s, &WebPreferences::inlineFormattingContextIntegrationEnabled },
#if ENABLE(NOTIFICATION_EVENT)
        { "NotificationEventEnabled"_s, &WebPreferences::notificationEventEnabled },
#endif
#if ENABLE(NOTIFICATIONS)
        { "NotificationsEnabled"_s, &WebPreferences::notificationsEnabled },
#endif
#if ENABLE(OFFSCREEN_CANVAS_IN_WORKERS)
        { "OffscreenCanvasInWorkersEnabled"_s, &WebPreferences::offscreenCanvasInWorkersEnabled },
#endif
#if ENABLE(OFFSCREEN_CANVAS)
        { "OffscreenCanvasEnabled"_s, &WebPreferences::offscreenCanvasEnabled },
#endif
#if ENABLE(OPUS)
        { "OpusDecoderEnabled"_s, &WebPreferences::opusDecoderEnabled },
#endif
        { "PageVisibilityBasedProcessSuppressionEnabled"_s, &WebPreferences::pageVisibilityBasedProcessSuppressionEnabled },
        { "PaintTimingEnabled"_s, &WebPreferences::paintTimingEnabled },
        { "BlobRegistryTopOriginPartitioningEnabled"_s, &WebPreferences::blobRegistryTopOriginPartitioningEnabled },
        { "PerformanceNavigationTimingAPIEnabled"_s, &WebPreferences::performanceNavigationTimingAPIEnabled },
        { "PerformanceResourceTimingSensitivePropertiesEnabled"_s, &WebPreferences::performanceResourceTimingSensitivePropertiesEnabled },
        { "PermissionsAPIEnabled"_s, &WebPreferences::permissionsAPIEnabled },
        { "PreferPageRenderingUpdatesNear60FPSEnabled"_s, &WebPreferences::preferPageRenderingUpdatesNear60FPSEnabled },
#if ENABLE(VIDEO)
        { "PreferSandboxedMediaParsing"_s, &WebPreferences::preferSandboxedMediaParsing },
#endif
        { "PrivateClickMeasurementDebugModeEnabled"_s, &WebPreferences::privateClickMeasurementDebugModeEnabled },
        { "PrivateClickMeasurementFraudPreventionEnabled"_s, &WebPreferences::privateClickMeasurementFraudPreventionEnabled },
        { "PrivateClickMeasurementEnabled"_s, &WebPreferences::privateClickMeasurementEnabled },
#if ENABLE(SERVICE_WORKER)
        { "PushAPIEnabled"_s, &WebPreferences::pushAPIEnabled },
#endif
        { "GoogleAntiFlickerOptimizationQuirkEnabled"_s, &WebPreferences::googleAntiFlickerOptimizationQuirkEnabled },
        { "ReadableByteStreamAPIEnabled"_s, &WebPreferences::readableByteStreamAPIEnabled },
        { "ReferrerPolicyAttributeEnabled"_s, &WebPreferences::referrerPolicyAttributeEnabled },
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
        { "RemotePlaybackEnabled"_s, &WebPreferences::remotePlaybackEnabled },
#endif
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
        { "RemoveBackgroundEnabled"_s, &WebPreferences::removeBackgroundEnabled },
#endif
        { "ReportingEnabled"_s, &WebPreferences::reportingEnabled },
        { "RequestVideoFrameCallbackEnabled"_s, &WebPreferences::requestVideoFrameCallbackEnabled },
#if HAVE(SC_CONTENT_SHARING_PICKER)
        { "RequireUAGetDisplayMediaPrompt"_s, &WebPreferences::requireUAGetDisplayMediaPrompt },
#endif
#if ENABLE(MEDIA_STREAM)
        { "SpeakerSelectionRequiresUserGesture"_s, &WebPreferences::speakerSelectionRequiresUserGesture },
#endif
        { "FullscreenRequirementForScreenOrientationLockingEnabled"_s, &WebPreferences::fullscreenRequirementForScreenOrientationLockingEnabled },
#if ENABLE(MEDIA_STREAM)
        { "GetUserMediaRequiresFocus"_s, &WebPreferences::getUserMediaRequiresFocus },
#endif
        { "ResizeObserverEnabled"_s, &WebPreferences::resizeObserverEnabled },
        { "ResourceLoadSchedulingEnabled"_s, &WebPreferences::resourceLoadSchedulingEnabled },
#if ENABLE(RESOURCE_USAGE)
        { "ResourceUsageOverlayVisible"_s, &WebPreferences::resourceUsageOverlayVisible },
#endif
        { "SKAttributionEnabled"_s, &WebPreferences::sKAttributionEnabled },
        { "SafeBrowsingEnabled"_s, &WebPreferences::safeBrowsingEnabled },
        { "IsSameSiteStrictEnforcementEnabled"_s, &WebPreferences::isSameSiteStrictEnforcementEnabled },
        { "ScreenOrientationLockingAPIEnabled"_s, &WebPreferences::screenOrientationLockingAPIEnabled },
        { "ScreenOrientationAPIEnabled"_s, &WebPreferences::screenOrientationAPIEnabled },
        { "ScreenWakeLockAPIEnabled"_s, &WebPreferences::screenWakeLockAPIEnabled },
#if ENABLE(MEDIA_STREAM)
        { "ScreenCaptureEnabled"_s, &WebPreferences::screenCaptureEnabled },
#endif
        { "ScrollingPerformanceTestingEnabled"_s, &WebPreferences::scrollingPerformanceTestingEnabled },
        { "ScrollToTextFragmentIndicatorEnabled"_s, &WebPreferences::scrollToTextFragmentIndicatorEnabled },
        { "ScrollToTextFragmentEnabled"_s, &WebPreferences::scrollToTextFragmentEnabled },
        { "ScrollAnimatorEnabled"_s, &WebPreferences::scrollAnimatorEnabled },
        { "SearchInputIncrementalAttributeAndSearchEventEnabled"_s, &WebPreferences::searchInputIncrementalAttributeAndSearchEventEnabled },
        { "SecureContextChecksEnabled"_s, &WebPreferences::secureContextChecksEnabled },
        { "SelectionAPIForShadowDOMEnabled"_s, &WebPreferences::selectionAPIForShadowDOMEnabled },
        { "SelectionFlippingEnabled"_s, &WebPreferences::selectionFlippingEnabled },
        { "SendMouseEventsToDisabledFormControlsEnabled"_s, &WebPreferences::sendMouseEventsToDisabledFormControlsEnabled },
        { "ServerTimingEnabled"_s, &WebPreferences::serverTimingEnabled },
#if ENABLE(SERVICE_WORKER)
        { "ServiceWorkerNavigationPreloadEnabled"_s, &WebPreferences::serviceWorkerNavigationPreloadEnabled },
#endif
#if ENABLE(SERVICE_WORKER)
        { "ServiceWorkersEnabled"_s, &WebPreferences::serviceWorkersEnabled },
#endif
        { "ShapeDetection"_s, &WebPreferences::shapeDetection },
        { "SharedWorkerEnabled"_s, &WebPreferences::sharedWorkerEnabled },
        { "ShowMediaStatsContextMenuItemEnabled"_s, &WebPreferences::showMediaStatsContextMenuItemEnabled },
        { "SiteIsolationEnabled"_s, &WebPreferences::siteIsolationEnabled },
        { "SpeechRecognitionEnabled"_s, &WebPreferences::speechRecognitionEnabled },
        { "SpeechSynthesisAPIEnabled"_s, &WebPreferences::speechSynthesisAPIEnabled },
        { "StorageAPIEstimateEnabled"_s, &WebPreferences::storageAPIEstimateEnabled },
        { "StorageAPIEnabled"_s, &WebPreferences::storageAPIEnabled },
        { "StorageAccessAPIEnabled"_s, &WebPreferences::storageAccessAPIEnabled },
        { "ProcessSwapOnCrossSiteNavigationEnabled"_s, &WebPreferences::processSwapOnCrossSiteNavigationEnabled },
        { "ProcessSwapOnCrossSiteWindowOpenEnabled"_s, &WebPreferences::processSwapOnCrossSiteWindowOpenEnabled },
        { "SyntheticEditingCommandsEnabled"_s, &WebPreferences::syntheticEditingCommandsEnabled },
        { "ShouldTakeNearSuspendedAssertions"_s, &WebPreferences::shouldTakeNearSuspendedAssertions },
#if ENABLE(IMAGE_ANALYSIS)
        { "TextRecognitionInVideosEnabled"_s, &WebPreferences::textRecognitionInVideosEnabled },
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
        { "ThreadedAnimationResolutionEnabled"_s, &WebPreferences::threadedAnimationResolutionEnabled },
#endif
        { "TiledScrollingIndicatorVisible"_s, &WebPreferences::tiledScrollingIndicatorVisible },
#if ENABLE(INPUT_TYPE_TIME)
        { "InputTypeTimeEnabled"_s, &WebPreferences::inputTypeTimeEnabled },
#endif
        { "TrackConfigurationEnabled"_s, &WebPreferences::trackConfigurationEnabled },
        { "TransformStreamAPIEnabled"_s, &WebPreferences::transformStreamAPIEnabled },
        { "UndoManagerAPIEnabled"_s, &WebPreferences::undoManagerAPIEnabled },
        { "UnprefixedFullscreenAPIEnabled"_s, &WebPreferences::unprefixedFullscreenAPIEnabled },
        { "UpgradeKnownHostsToHTTPSEnabled"_s, &WebPreferences::upgradeKnownHostsToHTTPSEnabled },
#if ENABLE(ARKIT_INLINE_PREVIEW)
        { "UseARKitForModel"_s, &WebPreferences::useARKitForModel },
#endif
        { "UseGeneralDirectoryForStorage"_s, &WebPreferences::useGeneralDirectoryForStorage },
#if HAVE(SC_CONTENT_SHARING_PICKER)
        { "UseSCContentSharingPicker"_s, &WebPreferences::useSCContentSharingPicker },
#endif
#if HAVE(SCENEKIT)
        { "UseSceneKitForModel"_s, &WebPreferences::useSceneKitForModel },
#endif
        { "UseGiantTiles"_s, &WebPreferences::useGiantTiles },
        { "UserActivationAPIEnabled"_s, &WebPreferences::userActivationAPIEnabled },
        { "UserGesturePromisePropagationEnabled"_s, &WebPreferences::userGesturePromisePropagationEnabled },
#if ENABLE(VP9)
        { "VP9SWDecoderEnabledOnBattery"_s, &WebPreferences::vp9SWDecoderEnabledOnBattery },
#endif
#if ENABLE(SERVICE_WORKER)
        { "ServiceWorkersUserGestureEnabled"_s, &WebPreferences::serviceWorkersUserGestureEnabled },
#endif
        { "VerifyWindowOpenUserGestureFromUIProcess"_s, &WebPreferences::verifyWindowOpenUserGestureFromUIProcess },
        { "VerticalFormControlsEnabled"_s, &WebPreferences::verticalFormControlsEnabled },
        { "ViewGestureDebuggingEnabled"_s, &WebPreferences::viewGestureDebuggingEnabled },
#if ENABLE(IMAGE_ANALYSIS)
        { "VisualTranslationEnabled"_s, &WebPreferences::visualTranslationEnabled },
#endif
        { "VisualViewportAPIEnabled"_s, &WebPreferences::visualViewportAPIEnabled },
#if ENABLE(VORBIS)
        { "VorbisDecoderEnabled"_s, &WebPreferences::vorbisDecoderEnabled },
#endif
        { "WebAPIStatisticsEnabled"_s, &WebPreferences::webAPIStatisticsEnabled },
        { "WebAPIsInShadowRealmEnabled"_s, &WebPreferences::webAPIsInShadowRealmEnabled },
        { "WebAnimationsCompositeOperationsEnabled"_s, &WebPreferences::webAnimationsCompositeOperationsEnabled },
        { "WebAnimationsCustomEffectsEnabled"_s, &WebPreferences::webAnimationsCustomEffectsEnabled },
        { "WebAnimationsCustomFrameRateEnabled"_s, &WebPreferences::webAnimationsCustomFrameRateEnabled },
        { "WebAnimationsIterationCompositeEnabled"_s, &WebPreferences::webAnimationsIterationCompositeEnabled },
        { "WebAnimationsMutableTimelinesEnabled"_s, &WebPreferences::webAnimationsMutableTimelinesEnabled },
#if ENABLE(WEB_ARCHIVE)
        { "WebArchiveDebugModeEnabled"_s, &WebPreferences::webArchiveDebugModeEnabled },
#endif
#if ENABLE(WEB_ARCHIVE)
        { "WebArchiveTestingModeEnabled"_s, &WebPreferences::webArchiveTestingModeEnabled },
#endif
#if ENABLE(WEB_AUTHN)
        { "WebAuthenticationEnabled"_s, &WebPreferences::webAuthenticationEnabled },
#endif
        { "WebCryptoSafeCurvesEnabled"_s, &WebPreferences::webCryptoSafeCurvesEnabled },
        { "WebLocksAPIEnabled"_s, &WebPreferences::webLocksAPIEnabled },
        { "WebShareFileAPIEnabled"_s, &WebPreferences::webShareFileAPIEnabled },
        { "WebShareEnabled"_s, &WebPreferences::webShareEnabled },
#if ENABLE(WEBASSEMBLY)
        { "WebAssemblyESMIntegrationEnabled"_s, &WebPreferences::webAssemblyESMIntegrationEnabled },
#endif
#if ENABLE(WEB_CODECS)
        { "WebCodecsEnabled"_s, &WebPreferences::webCodecsEnabled },
#endif
#if ENABLE(WEB_CODECS)
        { "WebCodecsAV1Enabled"_s, &WebPreferences::webCodecsAV1Enabled },
#endif
#if ENABLE(WEB_CODECS)
        { "WebCodecsHEVCEnabled"_s, &WebPreferences::webCodecsHEVCEnabled },
#endif
        { "WebGLDraftExtensionsEnabled"_s, &WebPreferences::webGLDraftExtensionsEnabled },
        { "WebGLTimerQueriesEnabled"_s, &WebPreferences::webGLTimerQueriesEnabled },
#if ENABLE(WEBGL) && PLATFORM(COCOA)
        { "WebGLUsingMetal"_s, &WebPreferences::webGLUsingMetal },
#endif
        { "WebGLEnabled"_s, &WebPreferences::webGLEnabled },
        { "WebGPUEnabled"_s, &WebPreferences::webGPUEnabled },
        { "WebInspectorEngineeringSettingsAllowed"_s, &WebPreferences::webInspectorEngineeringSettingsAllowed },
#if ENABLE(WEB_RTC)
        { "WebRTCAV1CodecEnabled"_s, &WebPreferences::webRTCAV1CodecEnabled },
#endif
        { "WebRTCAudioLatencyAdaptationEnabled"_s, &WebPreferences::webRTCAudioLatencyAdaptationEnabled },
#if ENABLE(WEB_RTC)
        { "WebRTCDTMFEnabled"_s, &WebPreferences::webRTCDTMFEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCEncodedTransformEnabled"_s, &WebPreferences::webRTCEncodedTransformEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCH264HardwareEncoderEnabled"_s, &WebPreferences::webRTCH264HardwareEncoderEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCH264LowLatencyEncoderEnabled"_s, &WebPreferences::webRTCH264LowLatencyEncoderEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCH264SimulcastEnabled"_s, &WebPreferences::webRTCH264SimulcastEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCH265CodecEnabled"_s, &WebPreferences::webRTCH265CodecEnabled },
#endif
#if USE(LIBWEBRTC)
        { "WebRTCMediaPipelineAdditionalLoggingEnabled"_s, &WebPreferences::webRTCMediaPipelineAdditionalLoggingEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "PeerConnectionEnabled"_s, &WebPreferences::peerConnectionEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCPlatformTCPSocketsEnabled"_s, &WebPreferences::webRTCPlatformTCPSocketsEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCPlatformUDPSocketsEnabled"_s, &WebPreferences::webRTCPlatformUDPSocketsEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCRemoteVideoFrameEnabled"_s, &WebPreferences::webRTCRemoteVideoFrameEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCSFrameTransformEnabled"_s, &WebPreferences::webRTCSFrameTransformEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCSocketsProxyingEnabled"_s, &WebPreferences::webRTCSocketsProxyingEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCVP9Profile0CodecEnabled"_s, &WebPreferences::webRTCVP9Profile0CodecEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCVP9Profile2CodecEnabled"_s, &WebPreferences::webRTCVP9Profile2CodecEnabled },
#endif
#if ENABLE(WEBXR)
        { "WebXRAugmentedRealityModuleEnabled"_s, &WebPreferences::webXRAugmentedRealityModuleEnabled },
#endif
#if ENABLE(WEBXR)
        { "WebXREnabled"_s, &WebPreferences::webXREnabled },
#endif
#if ENABLE(WEBXR)
        { "WebXRGamepadsModuleEnabled"_s, &WebPreferences::webXRGamepadsModuleEnabled },
#endif
#if ENABLE(WEBXR_HANDS)
        { "WebXRHandInputModuleEnabled"_s, &WebPreferences::webXRHandInputModuleEnabled },
#endif
#if ENABLE(INPUT_TYPE_WEEK)
        { "InputTypeWeekEnabled"_s, &WebPreferences::inputTypeWeekEnabled },
#endif
        { "WheelEventGesturesBecomeNonBlocking"_s, &WebPreferences::wheelEventGesturesBecomeNonBlocking },
        { "PassiveWheelListenersAsDefaultOnDocument"_s, &WebPreferences::passiveWheelListenersAsDefaultOnDocument },
        { "IsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled"_s, &WebPreferences::isFirstPartyWebsiteDataRemovalLiveOnTestingEnabled },
        { "IsFirstPartyWebsiteDataRemovalReproTestingEnabled"_s, &WebPreferences::isFirstPartyWebsiteDataRemovalReproTestingEnabled },
#if ENABLE(INPUT_TYPE_DATETIMELOCAL)
        { "InputTypeDateTimeLocalEnabled"_s, &WebPreferences::inputTypeDateTimeLocalEnabled },
#endif
        { "HTTPEquivEnabled"_s, &WebPreferences::httpEquivEnabled },
#if ENABLE(IOS_FORM_CONTROL_REFRESH)
        { "IOSFormControlRefreshEnabled"_s, &WebPreferences::iOSFormControlRefreshEnabled },
#endif
        { "LineHeightUnitsEnabled"_s, &WebPreferences::lineHeightUnitsEnabled },
        { "RequestIdleCallbackEnabled"_s, &WebPreferences::requestIdleCallbackEnabled },
        { "CSSWordBreakAutoEnabled"_s, &WebPreferences::cssWordBreakAutoEnabled },
    };

    const String& key = feature.key();

    for (auto& getter : getters) {
        if (key == getter.name)
            return (this->*getter.function)();
    }

    return false;
}

void WebPreferences::setFeatureEnabled(const API::Feature& feature, bool value)
{
    setFeatureEnabledForKey(feature.key(), value);
}

void WebPreferences::setFeatureEnabledForKey(const String& key, bool value)
{
    struct FeatureSetterMapping {
        ASCIILiteral name;
        void (WebPreferences::*function) (const bool&);
    };

    static FeatureSetterMapping setters[] = {
        { "AcceleratedCompositingEnabled"_s, &WebPreferences::setAcceleratedCompositingEnabled },
        { "AcceleratedCompositingForFixedPositionEnabled"_s, &WebPreferences::setAcceleratedCompositingForFixedPositionEnabled },
        { "AggressiveTileRetentionEnabled"_s, &WebPreferences::setAggressiveTileRetentionEnabled },
        { "AllowContentSecurityPolicySourceStarToMatchAnyProtocol"_s, &WebPreferences::setAllowContentSecurityPolicySourceStarToMatchAnyProtocol },
        { "AllowCrossOriginSubresourcesToAskForCredentials"_s, &WebPreferences::setAllowCrossOriginSubresourcesToAskForCredentials },
        { "AllowDisplayOfInsecureContent"_s, &WebPreferences::setAllowDisplayOfInsecureContent },
        { "AllowFileAccessFromFileURLs"_s, &WebPreferences::setAllowFileAccessFromFileURLs },
        { "AllowMultiElementImplicitSubmission"_s, &WebPreferences::setAllowMultiElementImplicitSubmission },
        { "AllowRunningOfInsecureContent"_s, &WebPreferences::setAllowRunningOfInsecureContent },
        { "AllowSettingAnyXHRHeaderFromFileURLs"_s, &WebPreferences::setAllowSettingAnyXHRHeaderFromFileURLs },
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
        { "AllowsAirPlayForMediaPlayback"_s, &WebPreferences::setAllowsAirPlayForMediaPlayback },
#endif
        { "AllowsInlineMediaPlayback"_s, &WebPreferences::setAllowsInlineMediaPlayback },
        { "AllowsInlineMediaPlaybackAfterFullscreen"_s, &WebPreferences::setAllowsInlineMediaPlaybackAfterFullscreen },
        { "AllowsPictureInPictureMediaPlayback"_s, &WebPreferences::setAllowsPictureInPictureMediaPlayback },
#if PLATFORM(IOS_FAMILY)
        { "AlternateFormControlDesignEnabled"_s, &WebPreferences::setAlternateFormControlDesignEnabled },
#endif
#if PLATFORM(IOS_FAMILY)
        { "AlternateFullScreenControlDesignEnabled"_s, &WebPreferences::setAlternateFullScreenControlDesignEnabled },
#endif
        { "AnimatedImageAsyncDecodingEnabled"_s, &WebPreferences::setAnimatedImageAsyncDecodingEnabled },
        { "AppleMailPaginationQuirkEnabled"_s, &WebPreferences::setAppleMailPaginationQuirkEnabled },
#if ENABLE(APPLE_PAY)
        { "ApplePayCapabilityDisclosureAllowed"_s, &WebPreferences::setApplePayCapabilityDisclosureAllowed },
#endif
#if ENABLE(APPLE_PAY)
        { "ApplePayEnabled"_s, &WebPreferences::setApplePayEnabled },
#endif
        { "AsynchronousSpellCheckingEnabled"_s, &WebPreferences::setAsynchronousSpellCheckingEnabled },
        { "AudioControlsScaleWithPageZoom"_s, &WebPreferences::setAudioControlsScaleWithPageZoom },
        { "AuthorAndUserStylesEnabled"_s, &WebPreferences::setAuthorAndUserStylesEnabled },
        { "BackspaceKeyNavigationEnabled"_s, &WebPreferences::setBackspaceKeyNavigationEnabled },
        { "CaretBrowsingEnabled"_s, &WebPreferences::setCaretBrowsingEnabled },
        { "ColorFilterEnabled"_s, &WebPreferences::setColorFilterEnabled },
        { "ConstantPropertiesEnabled"_s, &WebPreferences::setConstantPropertiesEnabled },
#if ENABLE(CONTENT_CHANGE_OBSERVER)
        { "ContentChangeObserverEnabled"_s, &WebPreferences::setContentChangeObserverEnabled },
#endif
        { "ContentDispositionAttachmentSandboxEnabled"_s, &WebPreferences::setContentDispositionAttachmentSandboxEnabled },
#if ENABLE(CONTEXT_MENU_QR_CODE_DETECTION)
        { "ContextMenuQRCodeDetectionEnabled"_s, &WebPreferences::setContextMenuQRCodeDetectionEnabled },
#endif
        { "DNSPrefetchingEnabled"_s, &WebPreferences::setDNSPrefetchingEnabled },
        { "DOMPasteAllowed"_s, &WebPreferences::setDOMPasteAllowed },
        { "DatabasesEnabled"_s, &WebPreferences::setDatabasesEnabled },
        { "DeveloperExtrasEnabled"_s, &WebPreferences::setDeveloperExtrasEnabled },
#if ENABLE(DEVICE_ORIENTATION)
        { "DeviceOrientationEventEnabled"_s, &WebPreferences::setDeviceOrientationEventEnabled },
#endif
#if ENABLE(DEVICE_ORIENTATION)
        { "DeviceOrientationPermissionAPIEnabled"_s, &WebPreferences::setDeviceOrientationPermissionAPIEnabled },
#endif
        { "DisabledAdaptationsMetaTagEnabled"_s, &WebPreferences::setDisabledAdaptationsMetaTagEnabled },
#if ENABLE(DOWNLOAD_ATTRIBUTE)
        { "DownloadAttributeEnabled"_s, &WebPreferences::setDownloadAttributeEnabled },
#endif
        { "EnableInheritURIQueryComponent"_s, &WebPreferences::setEnableInheritURIQueryComponent },
#if ENABLE(ENCRYPTED_MEDIA)
        { "EncryptedMediaAPIEnabled"_s, &WebPreferences::setEncryptedMediaAPIEnabled },
#endif
#if HAVE(APP_SSO)
        { "ExtensibleSSOEnabled"_s, &WebPreferences::setExtensibleSSOEnabled },
#endif
        { "ForceCompositingMode"_s, &WebPreferences::setForceCompositingMode },
        { "ForceFTPDirectoryListings"_s, &WebPreferences::setForceFTPDirectoryListings },
        { "ForceWebGLUsesLowPower"_s, &WebPreferences::setForceWebGLUsesLowPower },
#if USE(GSTREAMER)
        { "GStreamerEnabled"_s, &WebPreferences::setGStreamerEnabled },
#endif
        { "HiddenPageCSSAnimationSuspensionEnabled"_s, &WebPreferences::setHiddenPageCSSAnimationSuspensionEnabled },
        { "IncompleteImageBorderEnabled"_s, &WebPreferences::setIncompleteImageBorderEnabled },
#if HAVE(INCREMENTAL_PDF_APIS)
        { "IncrementalPDFLoadingEnabled"_s, &WebPreferences::setIncrementalPDFLoadingEnabled },
#endif
        { "InlineMediaPlaybackRequiresPlaysInlineAttribute"_s, &WebPreferences::setInlineMediaPlaybackRequiresPlaysInlineAttribute },
        { "InspectorStartsAttached"_s, &WebPreferences::setInspectorStartsAttached },
#if ENABLE(MEDIA_STREAM)
        { "InterruptAudioOnPageVisibilityChangeEnabled"_s, &WebPreferences::setInterruptAudioOnPageVisibilityChangeEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "InterruptVideoOnPageVisibilityChangeEnabled"_s, &WebPreferences::setInterruptVideoOnPageVisibilityChangeEnabled },
#endif
        { "InvisibleAutoplayNotPermitted"_s, &WebPreferences::setInvisibleAutoplayNotPermitted },
        { "JavaScriptCanAccessClipboard"_s, &WebPreferences::setJavaScriptCanAccessClipboard },
        { "JavaScriptCanOpenWindowsAutomatically"_s, &WebPreferences::setJavaScriptCanOpenWindowsAutomatically },
        { "JavaScriptMarkupEnabled"_s, &WebPreferences::setJavaScriptMarkupEnabled },
        { "LargeImageAsyncDecodingEnabled"_s, &WebPreferences::setLargeImageAsyncDecodingEnabled },
        { "LinkPreconnect"_s, &WebPreferences::setLinkPreconnect },
        { "LinkPreloadEnabled"_s, &WebPreferences::setLinkPreloadEnabled },
        { "LoadDeferringEnabled"_s, &WebPreferences::setLoadDeferringEnabled },
        { "LoadsImagesAutomatically"_s, &WebPreferences::setLoadsImagesAutomatically },
        { "LowPowerVideoAudioBufferSizeEnabled"_s, &WebPreferences::setLowPowerVideoAudioBufferSizeEnabled },
#if ENABLE(MATHML)
        { "MathMLEnabled"_s, &WebPreferences::setMathMLEnabled },
#endif
        { "MediaCapabilitiesEnabled"_s, &WebPreferences::setMediaCapabilitiesEnabled },
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS)
        { "MediaControlsContextMenusEnabled"_s, &WebPreferences::setMediaControlsContextMenusEnabled },
#endif
        { "MediaControlsScaleWithPageZoom"_s, &WebPreferences::setMediaControlsScaleWithPageZoom },
        { "MediaDataLoadsAutomatically"_s, &WebPreferences::setMediaDataLoadsAutomatically },
#if ENABLE(VIDEO)
        { "MediaEnabled"_s, &WebPreferences::setMediaEnabled },
#endif
        { "MediaPreloadingEnabled"_s, &WebPreferences::setMediaPreloadingEnabled },
#if ENABLE(MEDIA_STREAM)
        { "MediaStreamEnabled"_s, &WebPreferences::setMediaStreamEnabled },
#endif
        { "MediaUserGestureInheritsFromDocument"_s, &WebPreferences::setMediaUserGestureInheritsFromDocument },
        { "MenuItemElementEnabled"_s, &WebPreferences::setMenuItemElementEnabled },
        { "MockCaptureDevicesPromptEnabled"_s, &WebPreferences::setMockCaptureDevicesPromptEnabled },
        { "MockScrollbarsControllerEnabled"_s, &WebPreferences::setMockScrollbarsControllerEnabled },
        { "MockScrollbarsEnabled"_s, &WebPreferences::setMockScrollbarsEnabled },
        { "NeedsAdobeFrameReloadingQuirk"_s, &WebPreferences::setNeedsAdobeFrameReloadingQuirk },
        { "NeedsFrameNameFallbackToIdQuirk"_s, &WebPreferences::setNeedsFrameNameFallbackToIdQuirk },
        { "NeedsKeyboardEventDisambiguationQuirks"_s, &WebPreferences::setNeedsKeyboardEventDisambiguationQuirks },
        { "OfflineWebApplicationCacheEnabled"_s, &WebPreferences::setOfflineWebApplicationCacheEnabled },
#if PLATFORM(COCOA)
        { "PDFPluginEnabled"_s, &WebPreferences::setPDFPluginEnabled },
#endif
        { "PassiveTouchListenersAsDefaultOnDocument"_s, &WebPreferences::setPassiveTouchListenersAsDefaultOnDocument },
        { "PasswordEchoEnabled"_s, &WebPreferences::setPasswordEchoEnabled },
#if ENABLE(PICTURE_IN_PICTURE_API)
        { "PictureInPictureAPIEnabled"_s, &WebPreferences::setPictureInPictureAPIEnabled },
#endif
        { "PluginsEnabled"_s, &WebPreferences::setPluginsEnabled },
        { "PunchOutWhiteBackgroundsInDarkMode"_s, &WebPreferences::setPunchOutWhiteBackgroundsInDarkMode },
        { "RequiresPageVisibilityToPlayAudio"_s, &WebPreferences::setRequiresPageVisibilityToPlayAudio },
        { "RequiresUserGestureForAudioPlayback"_s, &WebPreferences::setRequiresUserGestureForAudioPlayback },
        { "RequiresUserGestureForMediaPlayback"_s, &WebPreferences::setRequiresUserGestureForMediaPlayback },
        { "RequiresUserGestureForVideoPlayback"_s, &WebPreferences::setRequiresUserGestureForVideoPlayback },
        { "RequiresUserGestureToLoadVideo"_s, &WebPreferences::setRequiresUserGestureToLoadVideo },
#if HAVE(RUBBER_BANDING)
        { "RubberBandingForSubScrollableRegionsEnabled"_s, &WebPreferences::setRubberBandingForSubScrollableRegionsEnabled },
#endif
        { "SelectTrailingWhitespaceEnabled"_s, &WebPreferences::setSelectTrailingWhitespaceEnabled },
#if ENABLE(SERVICE_CONTROLS)
        { "ServiceControlsEnabled"_s, &WebPreferences::setServiceControlsEnabled },
#endif
#if ENABLE(SERVICE_WORKER)
        { "ServiceWorkerEntitlementDisabledForTesting"_s, &WebPreferences::setServiceWorkerEntitlementDisabledForTesting },
#endif
        { "ShouldAllowUserInstalledFonts"_s, &WebPreferences::setShouldAllowUserInstalledFonts },
        { "ShouldConvertInvalidURLsToBlank"_s, &WebPreferences::setShouldConvertInvalidURLsToBlank },
        { "ShouldConvertPositionStyleOnCopy"_s, &WebPreferences::setShouldConvertPositionStyleOnCopy },
        { "ShouldDecidePolicyBeforeLoadingQuickLookPreview"_s, &WebPreferences::setShouldDecidePolicyBeforeLoadingQuickLookPreview },
#if ENABLE(VIDEO)
        { "ShouldDisplayCaptions"_s, &WebPreferences::setShouldDisplayCaptions },
#endif
#if ENABLE(VIDEO)
        { "ShouldDisplaySubtitles"_s, &WebPreferences::setShouldDisplaySubtitles },
#endif
#if ENABLE(VIDEO)
        { "ShouldDisplayTextDescriptions"_s, &WebPreferences::setShouldDisplayTextDescriptions },
#endif
#if ENABLE(TEXT_AUTOSIZING)
        { "ShouldEnableTextAutosizingBoost"_s, &WebPreferences::setShouldEnableTextAutosizingBoost },
#endif
        { "ShouldIgnoreMetaViewport"_s, &WebPreferences::setShouldIgnoreMetaViewport },
        { "ShouldPrintBackgrounds"_s, &WebPreferences::setShouldPrintBackgrounds },
        { "ShouldRespectImageOrientation"_s, &WebPreferences::setShouldRespectImageOrientation },
        { "ShouldRestrictBaseURLSchemes"_s, &WebPreferences::setShouldRestrictBaseURLSchemes },
        { "ShouldSuppressTextInputFromEditingDuringProvisionalNavigation"_s, &WebPreferences::setShouldSuppressTextInputFromEditingDuringProvisionalNavigation },
        { "ShouldUseServiceWorkerShortTimeout"_s, &WebPreferences::setShouldUseServiceWorkerShortTimeout },
        { "ShowsToolTipOverTruncatedText"_s, &WebPreferences::setShowsToolTipOverTruncatedText },
        { "ShowsURLsInToolTipsEnabled"_s, &WebPreferences::setShowsURLsInToolTipsEnabled },
        { "ShrinksStandaloneImagesToFit"_s, &WebPreferences::setShrinksStandaloneImagesToFit },
        { "SmartInsertDeleteEnabled"_s, &WebPreferences::setSmartInsertDeleteEnabled },
#if ENABLE(MEDIA_SOURCE)
        { "SourceBufferChangeTypeEnabled"_s, &WebPreferences::setSourceBufferChangeTypeEnabled },
#endif
        { "SpatialNavigationEnabled"_s, &WebPreferences::setSpatialNavigationEnabled },
        { "Standalone"_s, &WebPreferences::setStandalone },
        { "SuppressesIncrementalRendering"_s, &WebPreferences::setSuppressesIncrementalRendering },
#if USE(SYSTEM_PREVIEW)
        { "SystemPreviewEnabled"_s, &WebPreferences::setSystemPreviewEnabled },
#endif
        { "TabsToLinks"_s, &WebPreferences::setTabsToLinks },
        { "TelephoneNumberParsingEnabled"_s, &WebPreferences::setTelephoneNumberParsingEnabled },
        { "TemporaryTileCohortRetentionEnabled"_s, &WebPreferences::setTemporaryTileCohortRetentionEnabled },
        { "TextAreasAreResizable"_s, &WebPreferences::setTextAreasAreResizable },
#if ENABLE(TEXT_AUTOSIZING)
        { "TextAutosizingEnabled"_s, &WebPreferences::setTextAutosizingEnabled },
#endif
        { "TextInteractionEnabled"_s, &WebPreferences::setTextInteractionEnabled },
        { "ThreadedScrollingEnabled"_s, &WebPreferences::setThreadedScrollingEnabled },
        { "TreatsAnyTextCSSLinkAsStylesheet"_s, &WebPreferences::setTreatsAnyTextCSSLinkAsStylesheet },
        { "UseImageDocumentForSubframePDF"_s, &WebPreferences::setUseImageDocumentForSubframePDF },
        { "UseLegacyBackgroundSizeShorthandBehavior"_s, &WebPreferences::setUseLegacyBackgroundSizeShorthandBehavior },
        { "UsePreHTML5ParserQuirks"_s, &WebPreferences::setUsePreHTML5ParserQuirks },
        { "UsesBackForwardCache"_s, &WebPreferences::setUsesBackForwardCache },
        { "UsesEncodingDetector"_s, &WebPreferences::setUsesEncodingDetector },
#if ENABLE(VP9)
        { "VP8DecoderEnabled"_s, &WebPreferences::setVP8DecoderEnabled },
#endif
#if ENABLE(VP9)
        { "VP9DecoderEnabled"_s, &WebPreferences::setVP9DecoderEnabled },
#endif
#if PLATFORM(IOS_FAMILY)
        { "VideoFullscreenRequiresElementFullscreen"_s, &WebPreferences::setVideoFullscreenRequiresElementFullscreen },
#endif
        { "VideoPresentationModeAPIEnabled"_s, &WebPreferences::setVideoPresentationModeAPIEnabled },
#if ENABLE(VIDEO)
        { "VideoQualityIncludesDisplayCompositingEnabled"_s, &WebPreferences::setVideoQualityIncludesDisplayCompositingEnabled },
#endif
        { "VisualViewportEnabled"_s, &WebPreferences::setVisualViewportEnabled },
        { "WantsBalancedSetDefersLoadingBehavior"_s, &WebPreferences::setWantsBalancedSetDefersLoadingBehavior },
#if ENABLE(WEB_AUDIO)
        { "WebAudioEnabled"_s, &WebPreferences::setWebAudioEnabled },
#endif
#if ENABLE(WEBM_FORMAT_READER)
        { "WebMFormatReaderEnabled"_s, &WebPreferences::setWebMFormatReaderEnabled },
#endif
#if ENABLE(MEDIA_SOURCE)
        { "WebMParserEnabled"_s, &WebPreferences::setWebMParserEnabled },
#endif
        { "WebSecurityEnabled"_s, &WebPreferences::setWebSecurityEnabled },
        { "WebSocketEnabled"_s, &WebPreferences::setWebSocketEnabled },
        { "WindowFocusRestricted"_s, &WebPreferences::setWindowFocusRestricted },
        { "WirelessPlaybackTargetAPIEnabled"_s, &WebPreferences::setWirelessPlaybackTargetAPIEnabled },
        { "DirPseudoEnabled"_s, &WebPreferences::setDirPseudoEnabled },
        { "FocusVisibleEnabled"_s, &WebPreferences::setFocusVisibleEnabled },
        { "HasPseudoClassEnabled"_s, &WebPreferences::setHasPseudoClassEnabled },
        { "PageAtRuleSupportEnabled"_s, &WebPreferences::setPageAtRuleSupportEnabled },
        { "AriaReflectionForElementReferencesEnabled"_s, &WebPreferences::setAriaReflectionForElementReferencesEnabled },
#if USE(AVFOUNDATION)
        { "AVFoundationEnabled"_s, &WebPreferences::setAVFoundationEnabled },
#endif
        { "AbortSignalAnyOperationEnabled"_s, &WebPreferences::setAbortSignalAnyOperationEnabled },
#if USE(CORE_IMAGE)
        { "AcceleratedFiltersEnabled"_s, &WebPreferences::setAcceleratedFiltersEnabled },
#endif
        { "AccessHandleEnabled"_s, &WebPreferences::setAccessHandleEnabled },
        { "DOMTestingAPIsEnabled"_s, &WebPreferences::setDOMTestingAPIsEnabled },
        { "AllowMediaContentTypesRequiringHardwareSupportAsFallback"_s, &WebPreferences::setAllowMediaContentTypesRequiringHardwareSupportAsFallback },
#if PLATFORM(IOS_FAMILY)
        { "AllowViewportShrinkToFitContent"_s, &WebPreferences::setAllowViewportShrinkToFitContent },
#endif
#if ENABLE(WEBGL)
        { "AllowWebGLInWorkers"_s, &WebPreferences::setAllowWebGLInWorkers },
#endif
#if ENABLE(MEDIA_STREAM)
        { "PerElementSpeakerSelectionEnabled"_s, &WebPreferences::setPerElementSpeakerSelectionEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "ExposeSpeakersEnabled"_s, &WebPreferences::setExposeSpeakersEnabled },
#endif
        { "AllowTopNavigationToDataURLs"_s, &WebPreferences::setAllowTopNavigationToDataURLs },
        { "AllowUniversalAccessFromFileURLs"_s, &WebPreferences::setAllowUniversalAccessFromFileURLs },
#if ENABLE(ALTERNATE_WEBM_PLAYER)
        { "AlternateWebMPlayerEnabled"_s, &WebPreferences::setAlternateWebMPlayerEnabled },
#endif
#if ENABLE(BADGING)
        { "AppBadgeEnabled"_s, &WebPreferences::setAppBadgeEnabled },
#endif
#if ENABLE(APP_HIGHLIGHTS)
        { "AppHighlightsEnabled"_s, &WebPreferences::setAppHighlightsEnabled },
#endif
        { "AspectRatioOfImgFromWidthAndHeightEnabled"_s, &WebPreferences::setAspectRatioOfImgFromWidthAndHeightEnabled },
        { "AsyncFrameScrollingEnabled"_s, &WebPreferences::setAsyncFrameScrollingEnabled },
        { "AsyncOverflowScrollingEnabled"_s, &WebPreferences::setAsyncOverflowScrollingEnabled },
        { "AsyncClipboardAPIEnabled"_s, &WebPreferences::setAsyncClipboardAPIEnabled },
#if ENABLE(ATTACHMENT_ELEMENT)
        { "AttachmentElementEnabled"_s, &WebPreferences::setAttachmentElementEnabled },
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
        { "AttachmentWideLayoutEnabled"_s, &WebPreferences::setAttachmentWideLayoutEnabled },
#endif
#if ENABLE(VIDEO)
        { "ExtendedAudioDescriptionsEnabled"_s, &WebPreferences::setExtendedAudioDescriptionsEnabled },
#endif
#if ENABLE(VIDEO)
        { "AudioDescriptionsEnabled"_s, &WebPreferences::setAudioDescriptionsEnabled },
#endif
#if ENABLE(DOM_AUDIO_SESSION)
        { "DOMAudioSessionEnabled"_s, &WebPreferences::setDOMAudioSessionEnabled },
#endif
#if ENABLE(DOM_AUDIO_SESSION)
        { "DOMAudioSessionFullEnabled"_s, &WebPreferences::setDOMAudioSessionFullEnabled },
#endif
        { "BeaconAPIEnabled"_s, &WebPreferences::setBeaconAPIEnabled },
        { "ThirdPartyIframeRedirectBlockingEnabled"_s, &WebPreferences::setThirdPartyIframeRedirectBlockingEnabled },
        { "BroadcastChannelEnabled"_s, &WebPreferences::setBroadcastChannelEnabled },
        { "BroadcastChannelOriginPartitioningEnabled"_s, &WebPreferences::setBroadcastChannelOriginPartitioningEnabled },
#if ENABLE(BUILT_IN_NOTIFICATIONS)
        { "BuiltInNotificationsEnabled"_s, &WebPreferences::setBuiltInNotificationsEnabled },
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        { "UseCGDisplayListsForDOMRendering"_s, &WebPreferences::setUseCGDisplayListsForDOMRendering },
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        { "UseCGDisplayListImageCache"_s, &WebPreferences::setUseCGDisplayListImageCache },
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
        { "ReplayCGDisplayListsIntoBackingStore"_s, &WebPreferences::setReplayCGDisplayListsIntoBackingStore },
#endif
        { "CSS3DTransformInteroperabilityEnabled"_s, &WebPreferences::setCSS3DTransformInteroperabilityEnabled },
        { "CSSCounterStyleAtRuleImageSymbolsEnabled"_s, &WebPreferences::setCSSCounterStyleAtRuleImageSymbolsEnabled },
        { "CSSCounterStyleAtRulesEnabled"_s, &WebPreferences::setCSSCounterStyleAtRulesEnabled },
        { "CSSFontFaceSizeAdjustEnabled"_s, &WebPreferences::setCSSFontFaceSizeAdjustEnabled },
        { "AccentColorEnabled"_s, &WebPreferences::setAccentColorEnabled },
        { "AspectRatioEnabled"_s, &WebPreferences::setAspectRatioEnabled },
        { "CSSCascadeLayersEnabled"_s, &WebPreferences::setCSSCascadeLayersEnabled },
        { "CSSColor4"_s, &WebPreferences::setCSSColor4 },
        { "CSSContainIntrinsicSizeEnabled"_s, &WebPreferences::setCSSContainIntrinsicSizeEnabled },
        { "CSSContainerQueriesEnabled"_s, &WebPreferences::setCSSContainerQueriesEnabled },
        { "CSSContainmentEnabled"_s, &WebPreferences::setCSSContainmentEnabled },
        { "CSSContentVisibilityEnabled"_s, &WebPreferences::setCSSContentVisibilityEnabled },
        { "CSSCustomPropertiesAndValuesEnabled"_s, &WebPreferences::setCSSCustomPropertiesAndValuesEnabled },
        { "CSSGradientInterpolationColorSpacesEnabled"_s, &WebPreferences::setCSSGradientInterpolationColorSpacesEnabled },
        { "CSSGradientPremultipliedAlphaInterpolationEnabled"_s, &WebPreferences::setCSSGradientPremultipliedAlphaInterpolationEnabled },
        { "CSSIndividualTransformPropertiesEnabled"_s, &WebPreferences::setCSSIndividualTransformPropertiesEnabled },
        { "CSSInputSecurityEnabled"_s, &WebPreferences::setCSSInputSecurityEnabled },
        { "MasonryEnabled"_s, &WebPreferences::setMasonryEnabled },
        { "CSSMotionPathEnabled"_s, &WebPreferences::setCSSMotionPathEnabled },
        { "CSSNestingEnabled"_s, &WebPreferences::setCSSNestingEnabled },
        { "OverscrollBehaviorEnabled"_s, &WebPreferences::setOverscrollBehaviorEnabled },
#if ENABLE(CSS_PAINTING_API)
        { "CSSPaintingAPIEnabled"_s, &WebPreferences::setCSSPaintingAPIEnabled },
#endif
        { "CSSRelativeColorSyntaxEnabled"_s, &WebPreferences::setCSSRelativeColorSyntaxEnabled },
        { "CSSRhythmicSizingEnabled"_s, &WebPreferences::setCSSRhythmicSizingEnabled },
        { "CSSScrollAnchoringEnabled"_s, &WebPreferences::setCSSScrollAnchoringEnabled },
        { "SpringTimingFunctionEnabled"_s, &WebPreferences::setSpringTimingFunctionEnabled },
        { "CSSTypedOMEnabled"_s, &WebPreferences::setCSSTypedOMEnabled },
        { "CSSTypedOMColorEnabled"_s, &WebPreferences::setCSSTypedOMColorEnabled },
        { "MasonryTrackAlignmentEnabled"_s, &WebPreferences::setMasonryTrackAlignmentEnabled },
        { "CSSColorContrastEnabled"_s, &WebPreferences::setCSSColorContrastEnabled },
        { "CSSColorMixEnabled"_s, &WebPreferences::setCSSColorMixEnabled },
        { "CSSMarginTrimEnabled"_s, &WebPreferences::setCSSMarginTrimEnabled },
        { "OverflowClipEnabled"_s, &WebPreferences::setOverflowClipEnabled },
        { "CSSScrollbarColorEnabled"_s, &WebPreferences::setCSSScrollbarColorEnabled },
        { "CSSScrollbarGutterEnabled"_s, &WebPreferences::setCSSScrollbarGutterEnabled },
        { "CSSScrollbarWidthEnabled"_s, &WebPreferences::setCSSScrollbarWidthEnabled },
        { "SubgridEnabled"_s, &WebPreferences::setSubgridEnabled },
        { "CSSTextAlignLastEnabled"_s, &WebPreferences::setCSSTextAlignLastEnabled },
        { "CSSTextBoxTrimEnabled"_s, &WebPreferences::setCSSTextBoxTrimEnabled },
        { "CSSTextGroupAlignEnabled"_s, &WebPreferences::setCSSTextGroupAlignEnabled },
        { "CSSTextJustifyEnabled"_s, &WebPreferences::setCSSTextJustifyEnabled },
        { "CSSTextSpacingEnabled"_s, &WebPreferences::setCSSTextSpacingEnabled },
        { "CSSTextUnderlinePositionLeftRightEnabled"_s, &WebPreferences::setCSSTextUnderlinePositionLeftRightEnabled },
        { "CSSWhiteSpaceLonghandsEnabled"_s, &WebPreferences::setCSSWhiteSpaceLonghandsEnabled },
        { "CSSTextWrapNewValuesEnabled"_s, &WebPreferences::setCSSTextWrapNewValuesEnabled },
#if ENABLE(CSS_TRANSFORM_STYLE_OPTIMIZED_3D)
        { "CSSTransformStyleOptimized3DEnabled"_s, &WebPreferences::setCSSTransformStyleOptimized3DEnabled },
#endif
        { "CSSOMViewScrollingAPIEnabled"_s, &WebPreferences::setCSSOMViewScrollingAPIEnabled },
        { "CSSOMViewSmoothScrollingEnabled"_s, &WebPreferences::setCSSOMViewSmoothScrollingEnabled },
        { "CacheAPIEnabled"_s, &WebPreferences::setCacheAPIEnabled },
        { "CanvasColorSpaceEnabled"_s, &WebPreferences::setCanvasColorSpaceEnabled },
        { "CanvasFiltersEnabled"_s, &WebPreferences::setCanvasFiltersEnabled },
        { "CanvasUsesAcceleratedDrawing"_s, &WebPreferences::setCanvasUsesAcceleratedDrawing },
#if ENABLE(MEDIA_STREAM)
        { "CaptureAudioInUIProcessEnabled"_s, &WebPreferences::setCaptureAudioInUIProcessEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "CaptureVideoInUIProcessEnabled"_s, &WebPreferences::setCaptureVideoInUIProcessEnabled },
#endif
        { "ClearSiteDataHTTPHeaderEnabled"_s, &WebPreferences::setClearSiteDataHTTPHeaderEnabled },
#if ENABLE(BADGING)
        { "ClientBadgeEnabled"_s, &WebPreferences::setClientBadgeEnabled },
#endif
#if ENABLE(INPUT_TYPE_COLOR)
        { "InputTypeColorEnabled"_s, &WebPreferences::setInputTypeColorEnabled },
#endif
        { "CompositingBordersVisible"_s, &WebPreferences::setCompositingBordersVisible },
        { "CompositingRepaintCountersVisible"_s, &WebPreferences::setCompositingRepaintCountersVisible },
        { "CompressionStreamEnabled"_s, &WebPreferences::setCompressionStreamEnabled },
        { "ConstructableStylesheetsEnabled"_s, &WebPreferences::setConstructableStylesheetsEnabled },
        { "ContactPickerAPIEnabled"_s, &WebPreferences::setContactPickerAPIEnabled },
#if HAVE(AVCONTENTKEYSPECIFIER)
        { "SampleBufferContentKeySessionSupportEnabled"_s, &WebPreferences::setSampleBufferContentKeySessionSupportEnabled },
#endif
        { "CookieConsentAPIEnabled"_s, &WebPreferences::setCookieConsentAPIEnabled },
        { "CookieStoreAPIExtendedAttributesEnabled"_s, &WebPreferences::setCookieStoreAPIExtendedAttributesEnabled },
        { "CookieStoreAPIEnabled"_s, &WebPreferences::setCookieStoreAPIEnabled },
        { "CookieEnabled"_s, &WebPreferences::setCookieEnabled },
        { "CrossOriginEmbedderPolicyEnabled"_s, &WebPreferences::setCrossOriginEmbedderPolicyEnabled },
        { "CrossOriginOpenerPolicyEnabled"_s, &WebPreferences::setCrossOriginOpenerPolicyEnabled },
        { "CustomPasteboardDataEnabled"_s, &WebPreferences::setCustomPasteboardDataEnabled },
        { "DOMPasteAccessRequestsEnabled"_s, &WebPreferences::setDOMPasteAccessRequestsEnabled },
        { "DOMTimersThrottlingEnabled"_s, &WebPreferences::setDOMTimersThrottlingEnabled },
        { "DeclarativeShadowDOMInDOMParserEnabled"_s, &WebPreferences::setDeclarativeShadowDOMInDOMParserEnabled },
#if PLATFORM(IOS_FAMILY)
        { "ZoomOnDoubleTapWhenRoot"_s, &WebPreferences::setZoomOnDoubleTapWhenRoot },
#endif
#if PLATFORM(IOS_FAMILY)
        { "AlwaysZoomOnDoubleTap"_s, &WebPreferences::setAlwaysZoomOnDoubleTap },
#endif
        { "DataTransferItemsEnabled"_s, &WebPreferences::setDataTransferItemsEnabled },
#if ENABLE(DATALIST_ELEMENT)
        { "DataListElementEnabled"_s, &WebPreferences::setDataListElementEnabled },
#endif
#if ENABLE(INPUT_TYPE_DATE)
        { "InputTypeDateEnabled"_s, &WebPreferences::setInputTypeDateEnabled },
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
        { "DateTimeInputsEditableComponentsEnabled"_s, &WebPreferences::setDateTimeInputsEditableComponentsEnabled },
#endif
        { "DeclarativeShadowDOMEnabled"_s, &WebPreferences::setDeclarativeShadowDOMEnabled },
        { "DefaultARIAForCustomElementsEnabled"_s, &WebPreferences::setDefaultARIAForCustomElementsEnabled },
        { "ShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint"_s, &WebPreferences::setShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint },
        { "DeprecateRSAESPKCSWebCryptoEnabled"_s, &WebPreferences::setDeprecateRSAESPKCSWebCryptoEnabled },
        { "DeprecationReportingEnabled"_s, &WebPreferences::setDeprecationReportingEnabled },
        { "DiagnosticLoggingEnabled"_s, &WebPreferences::setDiagnosticLoggingEnabled },
        { "DirectoryUploadEnabled"_s, &WebPreferences::setDirectoryUploadEnabled },
        { "IsThirdPartyCookieBlockingDisabled"_s, &WebPreferences::setIsThirdPartyCookieBlockingDisabled },
        { "IsFirstPartyWebsiteDataRemovalDisabled"_s, &WebPreferences::setIsFirstPartyWebsiteDataRemovalDisabled },
#if PLATFORM(IOS_FAMILY)
        { "DisableScreenSizeOverride"_s, &WebPreferences::setDisableScreenSizeOverride },
#endif
        { "DisallowSyncXHRDuringPageDismissalEnabled"_s, &WebPreferences::setDisallowSyncXHRDuringPageDismissalEnabled },
        { "DisplayListDrawingEnabled"_s, &WebPreferences::setDisplayListDrawingEnabled },
        { "ShouldDropNearSuspendedAssertionAfterDelay"_s, &WebPreferences::setShouldDropNearSuspendedAssertionAfterDelay },
        { "EmbedElementEnabled"_s, &WebPreferences::setEmbedElementEnabled },
        { "AutomaticLiveResizeEnabled"_s, &WebPreferences::setAutomaticLiveResizeEnabled },
        { "CanvasFingerprintingQuirkEnabled"_s, &WebPreferences::setCanvasFingerprintingQuirkEnabled },
        { "EnumeratingAllNetworkInterfacesEnabled"_s, &WebPreferences::setEnumeratingAllNetworkInterfacesEnabled },
        { "EnumeratingVisibleNetworkInterfacesEnabled"_s, &WebPreferences::setEnumeratingVisibleNetworkInterfacesEnabled },
        { "ICECandidateFilteringEnabled"_s, &WebPreferences::setICECandidateFilteringEnabled },
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
        { "LegacyEncryptedMediaAPIEnabled"_s, &WebPreferences::setLegacyEncryptedMediaAPIEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "MockCaptureDevicesEnabled"_s, &WebPreferences::setMockCaptureDevicesEnabled },
#endif
#if ENABLE(PDFJS)
        { "PdfJSViewerEnabled"_s, &WebPreferences::setPdfJSViewerEnabled },
#endif
#if PLATFORM(MAC) && USE(RUNNINGBOARD)
        { "BackgroundWebContentRunningBoardThrottlingEnabled"_s, &WebPreferences::setBackgroundWebContentRunningBoardThrottlingEnabled },
#endif
#if ENABLE(SERVICE_WORKER)
        { "BackgroundFetchAPIEnabled"_s, &WebPreferences::setBackgroundFetchAPIEnabled },
#endif
#if HAVE(MACH_BOOTSTRAP_EXTENSION) || HAVE(SANDBOX_STATE_FLAGS)
        { "ExperimentalSandboxEnabled"_s, &WebPreferences::setExperimentalSandboxEnabled },
#endif
        { "StrictSecureDecodingForAllObjC"_s, &WebPreferences::setStrictSecureDecodingForAllObjC },
        { "EnterKeyHintEnabled"_s, &WebPreferences::setEnterKeyHintEnabled },
        { "EventHandlerDrivenSmoothKeyboardScrollingEnabled"_s, &WebPreferences::setEventHandlerDrivenSmoothKeyboardScrollingEnabled },
#if ENABLE(MEDIA_SESSION_COORDINATOR)
        { "MediaSessionCoordinatorEnabled"_s, &WebPreferences::setMediaSessionCoordinatorEnabled },
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR) && ENABLE(MEDIA_SESSION_PLAYLIST)
        { "MediaSessionPlaylistEnabled"_s, &WebPreferences::setMediaSessionPlaylistEnabled },
#endif
#if ENABLE(MEDIA_SOURCE) && (HAVE(AVSAMPLEBUFFERVIDEOOUTPUT) || USE(GSTREAMER))
        { "MediaSourceInlinePaintingEnabled"_s, &WebPreferences::setMediaSourceInlinePaintingEnabled },
#endif
#if HAVE(NETWORK_LOADER)
        { "CFNetworkNetworkLoaderEnabled"_s, &WebPreferences::setCFNetworkNetworkLoaderEnabled },
#endif
        { "FTPEnabled"_s, &WebPreferences::setFTPEnabled },
#if PLATFORM(IOS_FAMILY)
        { "PreferFasterClickOverDoubleTap"_s, &WebPreferences::setPreferFasterClickOverDoubleTap },
#endif
#if PLATFORM(IOS_FAMILY)
        { "FasterClicksEnabled"_s, &WebPreferences::setFasterClicksEnabled },
#endif
        { "FetchAPIKeepAliveEnabled"_s, &WebPreferences::setFetchAPIKeepAliveEnabled },
        { "FetchAPIEnabled"_s, &WebPreferences::setFetchAPIEnabled },
        { "FetchMetadataEnabled"_s, &WebPreferences::setFetchMetadataEnabled },
        { "FetchPriorityEnabled"_s, &WebPreferences::setFetchPriorityEnabled },
        { "FileSystemAccessEnabled"_s, &WebPreferences::setFileSystemAccessEnabled },
        { "FileReaderAPIEnabled"_s, &WebPreferences::setFileReaderAPIEnabled },
        { "RestrictedHTTPResponseAccess"_s, &WebPreferences::setRestrictedHTTPResponseAccess },
#if PLATFORM(IOS_FAMILY)
        { "ForceAlwaysUserScalable"_s, &WebPreferences::setForceAlwaysUserScalable },
#endif
        { "RequestSubmitEnabled"_s, &WebPreferences::setRequestSubmitEnabled },
        { "FormAssociatedCustomElementsEnabled"_s, &WebPreferences::setFormAssociatedCustomElementsEnabled },
        { "FrameFlatteningEnabled"_s, &WebPreferences::setFrameFlatteningEnabled },
        { "LayoutFormattingContextEnabled"_s, &WebPreferences::setLayoutFormattingContextEnabled },
#if ENABLE(FULLSCREEN_API)
        { "FullScreenEnabled"_s, &WebPreferences::setFullScreenEnabled },
#endif
#if PLATFORM(VISION)
        { "FullscreenSceneAspectRatioLockingEnabled"_s, &WebPreferences::setFullscreenSceneAspectRatioLockingEnabled },
#endif
#if PLATFORM(VISION)
        { "FullscreenSceneDimmingEnabled"_s, &WebPreferences::setFullscreenSceneDimmingEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "CaptureAudioInGPUProcessEnabled"_s, &WebPreferences::setCaptureAudioInGPUProcessEnabled },
#endif
#if ENABLE(GPU_PROCESS)
        { "BlockMediaLayerRehostingInWebContentProcess"_s, &WebPreferences::setBlockMediaLayerRehostingInWebContentProcess },
#endif
#if ENABLE(GPU_PROCESS) && !(PLATFORM(GTK) || PLATFORM(WPE))
        { "UseGPUProcessForCanvasRenderingEnabled"_s, &WebPreferences::setUseGPUProcessForCanvasRenderingEnabled },
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
        { "ManageCaptureStatusBarInGPUProcessEnabled"_s, &WebPreferences::setManageCaptureStatusBarInGPUProcessEnabled },
#endif
#if ENABLE(GPU_PROCESS)
        { "UseGPUProcessForDOMRenderingEnabled"_s, &WebPreferences::setUseGPUProcessForDOMRenderingEnabled },
#endif
#if ENABLE(GPU_PROCESS) && !USE(GSTREAMER)
        { "UseGPUProcessForMediaEnabled"_s, &WebPreferences::setUseGPUProcessForMediaEnabled },
#endif
#if HAVE(SCREEN_CAPTURE_KIT)
        { "UseGPUProcessForDisplayCapture"_s, &WebPreferences::setUseGPUProcessForDisplayCapture },
#endif
#if ENABLE(MEDIA_STREAM)
        { "CaptureVideoInGPUProcessEnabled"_s, &WebPreferences::setCaptureVideoInGPUProcessEnabled },
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
        { "UseGPUProcessForWebGLEnabled"_s, &WebPreferences::setUseGPUProcessForWebGLEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCPlatformCodecsInGPUProcessEnabled"_s, &WebPreferences::setWebRTCPlatformCodecsInGPUProcessEnabled },
#endif
#if ENABLE(GAMEPAD)
        { "GamepadTriggerRumbleEnabled"_s, &WebPreferences::setGamepadTriggerRumbleEnabled },
#endif
#if ENABLE(GAMEPAD)
        { "GamepadVibrationActuatorEnabled"_s, &WebPreferences::setGamepadVibrationActuatorEnabled },
#endif
#if ENABLE(GAMEPAD)
        { "GamepadsEnabled"_s, &WebPreferences::setGamepadsEnabled },
#endif
#if ENABLE(VIDEO)
        { "GenericCueAPIEnabled"_s, &WebPreferences::setGenericCueAPIEnabled },
#endif
#if USE(GRAPHICS_CONTEXT_FILTERS)
        { "GraphicsContextFiltersEnabled"_s, &WebPreferences::setGraphicsContextFiltersEnabled },
#endif
        { "AcceleratedDrawingEnabled"_s, &WebPreferences::setAcceleratedDrawingEnabled },
        { "DialogElementEnabled"_s, &WebPreferences::setDialogElementEnabled },
#if ENABLE(MODEL_ELEMENT)
        { "ModelElementEnabled"_s, &WebPreferences::setModelElementEnabled },
#endif
#if ENABLE(MODEL_ELEMENT)
        { "ModelDocumentEnabled"_s, &WebPreferences::setModelDocumentEnabled },
#endif
        { "InteractiveFormValidationEnabled"_s, &WebPreferences::setInteractiveFormValidationEnabled },
        { "InertAttributeEnabled"_s, &WebPreferences::setInertAttributeEnabled },
        { "PopoverAttributeEnabled"_s, &WebPreferences::setPopoverAttributeEnabled },
        { "HiddenPageDOMTimerThrottlingAutoIncreases"_s, &WebPreferences::setHiddenPageDOMTimerThrottlingAutoIncreases },
        { "HiddenPageDOMTimerThrottlingEnabled"_s, &WebPreferences::setHiddenPageDOMTimerThrottlingEnabled },
        { "HighlightAPIEnabled"_s, &WebPreferences::setHighlightAPIEnabled },
        { "HyperlinkAuditingEnabled"_s, &WebPreferences::setHyperlinkAuditingEnabled },
#if HAVE(SANDBOX_STATE_FLAGS)
        { "BlockIOKitInWebContentSandbox"_s, &WebPreferences::setBlockIOKitInWebContentSandbox },
#endif
#if ENABLE(IPC_TESTING_API)
        { "IPCTestingAPIEnabled"_s, &WebPreferences::setIPCTestingAPIEnabled },
#endif
        { "ItpDebugModeEnabled"_s, &WebPreferences::setItpDebugModeEnabled },
#if ENABLE(TEXT_AUTOSIZING)
        { "TextAutosizingUsesIdempotentMode"_s, &WebPreferences::setTextAutosizingUsesIdempotentMode },
#endif
#if ENABLE(IMAGE_ANALYSIS)
        { "ImageAnalysisDuringFindInPageEnabled"_s, &WebPreferences::setImageAnalysisDuringFindInPageEnabled },
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
        { "ImageAnimationControlEnabled"_s, &WebPreferences::setImageAnimationControlEnabled },
#endif
#if ENABLE(SERVICE_CONTROLS)
        { "ImageControlsEnabled"_s, &WebPreferences::setImageControlsEnabled },
#endif
        { "ImperativeSlotAPIEnabled"_s, &WebPreferences::setImperativeSlotAPIEnabled },
        { "IndexedDBAPIEnabled"_s, &WebPreferences::setIndexedDBAPIEnabled },
        { "InlinePredictionsInAllEditableElementsEnabled"_s, &WebPreferences::setInlinePredictionsInAllEditableElementsEnabled },
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
        { "InteractionRegionsEnabled"_s, &WebPreferences::setInteractionRegionsEnabled },
#endif
        { "IntersectionObserverEnabled"_s, &WebPreferences::setIntersectionObserverEnabled },
        { "IsLoggedInAPIEnabled"_s, &WebPreferences::setIsLoggedInAPIEnabled },
#if ENABLE(ACCESSIBILITY_ISOLATED_TREE)
        { "IsAccessibilityIsolatedTreeEnabled"_s, &WebPreferences::setIsAccessibilityIsolatedTreeEnabled },
#endif
        { "JavaScriptEnabled"_s, &WebPreferences::setJavaScriptEnabled },
#if ENABLE(LAYER_BASED_SVG_ENGINE)
        { "LayerBasedSVGEngineEnabled"_s, &WebPreferences::setLayerBasedSVGEngineEnabled },
#endif
        { "LazyIframeLoadingEnabled"_s, &WebPreferences::setLazyIframeLoadingEnabled },
        { "LazyImageLoadingEnabled"_s, &WebPreferences::setLazyImageLoadingEnabled },
#if ENABLE(OVERFLOW_SCROLLING_TOUCH)
        { "LegacyOverflowScrollingTouchEnabled"_s, &WebPreferences::setLegacyOverflowScrollingTouchEnabled },
#endif
        { "LegacyLineLayoutVisualCoverageEnabled"_s, &WebPreferences::setLegacyLineLayoutVisualCoverageEnabled },
        { "ShowModalDialogEnabled"_s, &WebPreferences::setShowModalDialogEnabled },
#if ENABLE(MEDIA_STREAM)
        { "MediaCaptureRequiresSecureConnection"_s, &WebPreferences::setMediaCaptureRequiresSecureConnection },
#endif
        { "LinkSanitizerEnabled"_s, &WebPreferences::setLinkSanitizerEnabled },
        { "LinkPreloadResponsiveImagesEnabled"_s, &WebPreferences::setLinkPreloadResponsiveImagesEnabled },
        { "LinkModulePreloadEnabled"_s, &WebPreferences::setLinkModulePreloadEnabled },
        { "LinkPreconnectEarlyHintsEnabled"_s, &WebPreferences::setLinkPreconnectEarlyHintsEnabled },
        { "LinkPrefetchEnabled"_s, &WebPreferences::setLinkPrefetchEnabled },
        { "LiveRangeSelectionEnabled"_s, &WebPreferences::setLiveRangeSelectionEnabled },
        { "LocalFileContentSniffingEnabled"_s, &WebPreferences::setLocalFileContentSniffingEnabled },
        { "LocalStorageEnabled"_s, &WebPreferences::setLocalStorageEnabled },
        { "LogsPageMessagesToSystemConsoleEnabled"_s, &WebPreferences::setLogsPageMessagesToSystemConsoleEnabled },
        { "MainContentUserGestureOverrideEnabled"_s, &WebPreferences::setMainContentUserGestureOverrideEnabled },
#if ENABLE(MANAGED_MEDIA_SOURCE)
        { "ManagedMediaSourceEnabled"_s, &WebPreferences::setManagedMediaSourceEnabled },
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE) && ENABLE(WIRELESS_PLAYBACK_TARGET)
        { "ManagedMediaSourceNeedsAirPlay"_s, &WebPreferences::setManagedMediaSourceNeedsAirPlay },
#endif
#if ENABLE(WEBGL)
        { "MaskWebGLStringsEnabled"_s, &WebPreferences::setMaskWebGLStringsEnabled },
#endif
        { "CoreMathMLEnabled"_s, &WebPreferences::setCoreMathMLEnabled },
        { "MediaCapabilitiesExtensionsEnabled"_s, &WebPreferences::setMediaCapabilitiesExtensionsEnabled },
#if ENABLE(MEDIA_SESSION)
        { "MediaSessionEnabled"_s, &WebPreferences::setMediaSessionEnabled },
#endif
        { "MediaSourceEnabled"_s, &WebPreferences::setMediaSourceEnabled },
#if ENABLE(MEDIA_STREAM)
        { "MediaDevicesEnabled"_s, &WebPreferences::setMediaDevicesEnabled },
#endif
#if ENABLE(MEDIA_RECORDER)
        { "MediaRecorderEnabled"_s, &WebPreferences::setMediaRecorderEnabled },
#endif
        { "MomentumScrollingAnimatorEnabled"_s, &WebPreferences::setMomentumScrollingAnimatorEnabled },
#if ENABLE(INPUT_TYPE_MONTH)
        { "InputTypeMonthEnabled"_s, &WebPreferences::setInputTypeMonthEnabled },
#endif
#if ENABLE(TOUCH_EVENTS)
        { "MouseEventsSimulationEnabled"_s, &WebPreferences::setMouseEventsSimulationEnabled },
#endif
#if ENABLE(MEDIA_STREAM)
        { "MuteCameraOnMicrophoneInterruptionEnabled"_s, &WebPreferences::setMuteCameraOnMicrophoneInterruptionEnabled },
#endif
#if ENABLE(APP_BOUND_DOMAINS)
        { "NeedsInAppBrowserPrivacyQuirks"_s, &WebPreferences::setNeedsInAppBrowserPrivacyQuirks },
#endif
        { "NeedsSiteSpecificQuirks"_s, &WebPreferences::setNeedsSiteSpecificQuirks },
        { "NeedsStorageAccessFromFileURLsQuirk"_s, &WebPreferences::setNeedsStorageAccessFromFileURLsQuirk },
        { "FlexFormattingContextIntegrationEnabled"_s, &WebPreferences::setFlexFormattingContextIntegrationEnabled },
        { "InlineFormattingContextIntegrationEnabled"_s, &WebPreferences::setInlineFormattingContextIntegrationEnabled },
#if ENABLE(NOTIFICATION_EVENT)
        { "NotificationEventEnabled"_s, &WebPreferences::setNotificationEventEnabled },
#endif
#if ENABLE(NOTIFICATIONS)
        { "NotificationsEnabled"_s, &WebPreferences::setNotificationsEnabled },
#endif
#if ENABLE(OFFSCREEN_CANVAS_IN_WORKERS)
        { "OffscreenCanvasInWorkersEnabled"_s, &WebPreferences::setOffscreenCanvasInWorkersEnabled },
#endif
#if ENABLE(OFFSCREEN_CANVAS)
        { "OffscreenCanvasEnabled"_s, &WebPreferences::setOffscreenCanvasEnabled },
#endif
#if ENABLE(OPUS)
        { "OpusDecoderEnabled"_s, &WebPreferences::setOpusDecoderEnabled },
#endif
        { "PageVisibilityBasedProcessSuppressionEnabled"_s, &WebPreferences::setPageVisibilityBasedProcessSuppressionEnabled },
        { "PaintTimingEnabled"_s, &WebPreferences::setPaintTimingEnabled },
        { "BlobRegistryTopOriginPartitioningEnabled"_s, &WebPreferences::setBlobRegistryTopOriginPartitioningEnabled },
        { "PerformanceNavigationTimingAPIEnabled"_s, &WebPreferences::setPerformanceNavigationTimingAPIEnabled },
        { "PerformanceResourceTimingSensitivePropertiesEnabled"_s, &WebPreferences::setPerformanceResourceTimingSensitivePropertiesEnabled },
        { "PermissionsAPIEnabled"_s, &WebPreferences::setPermissionsAPIEnabled },
        { "PreferPageRenderingUpdatesNear60FPSEnabled"_s, &WebPreferences::setPreferPageRenderingUpdatesNear60FPSEnabled },
#if ENABLE(VIDEO)
        { "PreferSandboxedMediaParsing"_s, &WebPreferences::setPreferSandboxedMediaParsing },
#endif
        { "PrivateClickMeasurementDebugModeEnabled"_s, &WebPreferences::setPrivateClickMeasurementDebugModeEnabled },
        { "PrivateClickMeasurementFraudPreventionEnabled"_s, &WebPreferences::setPrivateClickMeasurementFraudPreventionEnabled },
        { "PrivateClickMeasurementEnabled"_s, &WebPreferences::setPrivateClickMeasurementEnabled },
#if ENABLE(SERVICE_WORKER)
        { "PushAPIEnabled"_s, &WebPreferences::setPushAPIEnabled },
#endif
        { "GoogleAntiFlickerOptimizationQuirkEnabled"_s, &WebPreferences::setGoogleAntiFlickerOptimizationQuirkEnabled },
        { "ReadableByteStreamAPIEnabled"_s, &WebPreferences::setReadableByteStreamAPIEnabled },
        { "ReferrerPolicyAttributeEnabled"_s, &WebPreferences::setReferrerPolicyAttributeEnabled },
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
        { "RemotePlaybackEnabled"_s, &WebPreferences::setRemotePlaybackEnabled },
#endif
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
        { "RemoveBackgroundEnabled"_s, &WebPreferences::setRemoveBackgroundEnabled },
#endif
        { "ReportingEnabled"_s, &WebPreferences::setReportingEnabled },
        { "RequestVideoFrameCallbackEnabled"_s, &WebPreferences::setRequestVideoFrameCallbackEnabled },
#if HAVE(SC_CONTENT_SHARING_PICKER)
        { "RequireUAGetDisplayMediaPrompt"_s, &WebPreferences::setRequireUAGetDisplayMediaPrompt },
#endif
#if ENABLE(MEDIA_STREAM)
        { "SpeakerSelectionRequiresUserGesture"_s, &WebPreferences::setSpeakerSelectionRequiresUserGesture },
#endif
        { "FullscreenRequirementForScreenOrientationLockingEnabled"_s, &WebPreferences::setFullscreenRequirementForScreenOrientationLockingEnabled },
#if ENABLE(MEDIA_STREAM)
        { "GetUserMediaRequiresFocus"_s, &WebPreferences::setGetUserMediaRequiresFocus },
#endif
        { "ResizeObserverEnabled"_s, &WebPreferences::setResizeObserverEnabled },
        { "ResourceLoadSchedulingEnabled"_s, &WebPreferences::setResourceLoadSchedulingEnabled },
#if ENABLE(RESOURCE_USAGE)
        { "ResourceUsageOverlayVisible"_s, &WebPreferences::setResourceUsageOverlayVisible },
#endif
        { "SKAttributionEnabled"_s, &WebPreferences::setSKAttributionEnabled },
        { "SafeBrowsingEnabled"_s, &WebPreferences::setSafeBrowsingEnabled },
        { "IsSameSiteStrictEnforcementEnabled"_s, &WebPreferences::setIsSameSiteStrictEnforcementEnabled },
        { "ScreenOrientationLockingAPIEnabled"_s, &WebPreferences::setScreenOrientationLockingAPIEnabled },
        { "ScreenOrientationAPIEnabled"_s, &WebPreferences::setScreenOrientationAPIEnabled },
        { "ScreenWakeLockAPIEnabled"_s, &WebPreferences::setScreenWakeLockAPIEnabled },
#if ENABLE(MEDIA_STREAM)
        { "ScreenCaptureEnabled"_s, &WebPreferences::setScreenCaptureEnabled },
#endif
        { "ScrollingPerformanceTestingEnabled"_s, &WebPreferences::setScrollingPerformanceTestingEnabled },
        { "ScrollToTextFragmentIndicatorEnabled"_s, &WebPreferences::setScrollToTextFragmentIndicatorEnabled },
        { "ScrollToTextFragmentEnabled"_s, &WebPreferences::setScrollToTextFragmentEnabled },
        { "ScrollAnimatorEnabled"_s, &WebPreferences::setScrollAnimatorEnabled },
        { "SearchInputIncrementalAttributeAndSearchEventEnabled"_s, &WebPreferences::setSearchInputIncrementalAttributeAndSearchEventEnabled },
        { "SecureContextChecksEnabled"_s, &WebPreferences::setSecureContextChecksEnabled },
        { "SelectionAPIForShadowDOMEnabled"_s, &WebPreferences::setSelectionAPIForShadowDOMEnabled },
        { "SelectionFlippingEnabled"_s, &WebPreferences::setSelectionFlippingEnabled },
        { "SendMouseEventsToDisabledFormControlsEnabled"_s, &WebPreferences::setSendMouseEventsToDisabledFormControlsEnabled },
        { "ServerTimingEnabled"_s, &WebPreferences::setServerTimingEnabled },
#if ENABLE(SERVICE_WORKER)
        { "ServiceWorkerNavigationPreloadEnabled"_s, &WebPreferences::setServiceWorkerNavigationPreloadEnabled },
#endif
#if ENABLE(SERVICE_WORKER)
        { "ServiceWorkersEnabled"_s, &WebPreferences::setServiceWorkersEnabled },
#endif
        { "ShapeDetection"_s, &WebPreferences::setShapeDetection },
        { "SharedWorkerEnabled"_s, &WebPreferences::setSharedWorkerEnabled },
        { "ShowMediaStatsContextMenuItemEnabled"_s, &WebPreferences::setShowMediaStatsContextMenuItemEnabled },
        { "SiteIsolationEnabled"_s, &WebPreferences::setSiteIsolationEnabled },
        { "SpeechRecognitionEnabled"_s, &WebPreferences::setSpeechRecognitionEnabled },
        { "SpeechSynthesisAPIEnabled"_s, &WebPreferences::setSpeechSynthesisAPIEnabled },
        { "StorageAPIEstimateEnabled"_s, &WebPreferences::setStorageAPIEstimateEnabled },
        { "StorageAPIEnabled"_s, &WebPreferences::setStorageAPIEnabled },
        { "StorageAccessAPIEnabled"_s, &WebPreferences::setStorageAccessAPIEnabled },
        { "ProcessSwapOnCrossSiteNavigationEnabled"_s, &WebPreferences::setProcessSwapOnCrossSiteNavigationEnabled },
        { "ProcessSwapOnCrossSiteWindowOpenEnabled"_s, &WebPreferences::setProcessSwapOnCrossSiteWindowOpenEnabled },
        { "SyntheticEditingCommandsEnabled"_s, &WebPreferences::setSyntheticEditingCommandsEnabled },
        { "ShouldTakeNearSuspendedAssertions"_s, &WebPreferences::setShouldTakeNearSuspendedAssertions },
#if ENABLE(IMAGE_ANALYSIS)
        { "TextRecognitionInVideosEnabled"_s, &WebPreferences::setTextRecognitionInVideosEnabled },
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
        { "ThreadedAnimationResolutionEnabled"_s, &WebPreferences::setThreadedAnimationResolutionEnabled },
#endif
        { "TiledScrollingIndicatorVisible"_s, &WebPreferences::setTiledScrollingIndicatorVisible },
#if ENABLE(INPUT_TYPE_TIME)
        { "InputTypeTimeEnabled"_s, &WebPreferences::setInputTypeTimeEnabled },
#endif
        { "TrackConfigurationEnabled"_s, &WebPreferences::setTrackConfigurationEnabled },
        { "TransformStreamAPIEnabled"_s, &WebPreferences::setTransformStreamAPIEnabled },
        { "UndoManagerAPIEnabled"_s, &WebPreferences::setUndoManagerAPIEnabled },
        { "UnprefixedFullscreenAPIEnabled"_s, &WebPreferences::setUnprefixedFullscreenAPIEnabled },
        { "UpgradeKnownHostsToHTTPSEnabled"_s, &WebPreferences::setUpgradeKnownHostsToHTTPSEnabled },
#if ENABLE(ARKIT_INLINE_PREVIEW)
        { "UseARKitForModel"_s, &WebPreferences::setUseARKitForModel },
#endif
        { "UseGeneralDirectoryForStorage"_s, &WebPreferences::setUseGeneralDirectoryForStorage },
#if HAVE(SC_CONTENT_SHARING_PICKER)
        { "UseSCContentSharingPicker"_s, &WebPreferences::setUseSCContentSharingPicker },
#endif
#if HAVE(SCENEKIT)
        { "UseSceneKitForModel"_s, &WebPreferences::setUseSceneKitForModel },
#endif
        { "UseGiantTiles"_s, &WebPreferences::setUseGiantTiles },
        { "UserActivationAPIEnabled"_s, &WebPreferences::setUserActivationAPIEnabled },
        { "UserGesturePromisePropagationEnabled"_s, &WebPreferences::setUserGesturePromisePropagationEnabled },
#if ENABLE(VP9)
        { "VP9SWDecoderEnabledOnBattery"_s, &WebPreferences::setVP9SWDecoderEnabledOnBattery },
#endif
#if ENABLE(SERVICE_WORKER)
        { "ServiceWorkersUserGestureEnabled"_s, &WebPreferences::setServiceWorkersUserGestureEnabled },
#endif
        { "VerifyWindowOpenUserGestureFromUIProcess"_s, &WebPreferences::setVerifyWindowOpenUserGestureFromUIProcess },
        { "VerticalFormControlsEnabled"_s, &WebPreferences::setVerticalFormControlsEnabled },
        { "ViewGestureDebuggingEnabled"_s, &WebPreferences::setViewGestureDebuggingEnabled },
#if ENABLE(IMAGE_ANALYSIS)
        { "VisualTranslationEnabled"_s, &WebPreferences::setVisualTranslationEnabled },
#endif
        { "VisualViewportAPIEnabled"_s, &WebPreferences::setVisualViewportAPIEnabled },
#if ENABLE(VORBIS)
        { "VorbisDecoderEnabled"_s, &WebPreferences::setVorbisDecoderEnabled },
#endif
        { "WebAPIStatisticsEnabled"_s, &WebPreferences::setWebAPIStatisticsEnabled },
        { "WebAPIsInShadowRealmEnabled"_s, &WebPreferences::setWebAPIsInShadowRealmEnabled },
        { "WebAnimationsCompositeOperationsEnabled"_s, &WebPreferences::setWebAnimationsCompositeOperationsEnabled },
        { "WebAnimationsCustomEffectsEnabled"_s, &WebPreferences::setWebAnimationsCustomEffectsEnabled },
        { "WebAnimationsCustomFrameRateEnabled"_s, &WebPreferences::setWebAnimationsCustomFrameRateEnabled },
        { "WebAnimationsIterationCompositeEnabled"_s, &WebPreferences::setWebAnimationsIterationCompositeEnabled },
        { "WebAnimationsMutableTimelinesEnabled"_s, &WebPreferences::setWebAnimationsMutableTimelinesEnabled },
#if ENABLE(WEB_ARCHIVE)
        { "WebArchiveDebugModeEnabled"_s, &WebPreferences::setWebArchiveDebugModeEnabled },
#endif
#if ENABLE(WEB_ARCHIVE)
        { "WebArchiveTestingModeEnabled"_s, &WebPreferences::setWebArchiveTestingModeEnabled },
#endif
#if ENABLE(WEB_AUTHN)
        { "WebAuthenticationEnabled"_s, &WebPreferences::setWebAuthenticationEnabled },
#endif
        { "WebCryptoSafeCurvesEnabled"_s, &WebPreferences::setWebCryptoSafeCurvesEnabled },
        { "WebLocksAPIEnabled"_s, &WebPreferences::setWebLocksAPIEnabled },
        { "WebShareFileAPIEnabled"_s, &WebPreferences::setWebShareFileAPIEnabled },
        { "WebShareEnabled"_s, &WebPreferences::setWebShareEnabled },
#if ENABLE(WEBASSEMBLY)
        { "WebAssemblyESMIntegrationEnabled"_s, &WebPreferences::setWebAssemblyESMIntegrationEnabled },
#endif
#if ENABLE(WEB_CODECS)
        { "WebCodecsEnabled"_s, &WebPreferences::setWebCodecsEnabled },
#endif
#if ENABLE(WEB_CODECS)
        { "WebCodecsAV1Enabled"_s, &WebPreferences::setWebCodecsAV1Enabled },
#endif
#if ENABLE(WEB_CODECS)
        { "WebCodecsHEVCEnabled"_s, &WebPreferences::setWebCodecsHEVCEnabled },
#endif
        { "WebGLDraftExtensionsEnabled"_s, &WebPreferences::setWebGLDraftExtensionsEnabled },
        { "WebGLTimerQueriesEnabled"_s, &WebPreferences::setWebGLTimerQueriesEnabled },
#if ENABLE(WEBGL) && PLATFORM(COCOA)
        { "WebGLUsingMetal"_s, &WebPreferences::setWebGLUsingMetal },
#endif
        { "WebGLEnabled"_s, &WebPreferences::setWebGLEnabled },
        { "WebGPUEnabled"_s, &WebPreferences::setWebGPUEnabled },
        { "WebInspectorEngineeringSettingsAllowed"_s, &WebPreferences::setWebInspectorEngineeringSettingsAllowed },
#if ENABLE(WEB_RTC)
        { "WebRTCAV1CodecEnabled"_s, &WebPreferences::setWebRTCAV1CodecEnabled },
#endif
        { "WebRTCAudioLatencyAdaptationEnabled"_s, &WebPreferences::setWebRTCAudioLatencyAdaptationEnabled },
#if ENABLE(WEB_RTC)
        { "WebRTCDTMFEnabled"_s, &WebPreferences::setWebRTCDTMFEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCEncodedTransformEnabled"_s, &WebPreferences::setWebRTCEncodedTransformEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCH264HardwareEncoderEnabled"_s, &WebPreferences::setWebRTCH264HardwareEncoderEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCH264LowLatencyEncoderEnabled"_s, &WebPreferences::setWebRTCH264LowLatencyEncoderEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCH264SimulcastEnabled"_s, &WebPreferences::setWebRTCH264SimulcastEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCH265CodecEnabled"_s, &WebPreferences::setWebRTCH265CodecEnabled },
#endif
#if USE(LIBWEBRTC)
        { "WebRTCMediaPipelineAdditionalLoggingEnabled"_s, &WebPreferences::setWebRTCMediaPipelineAdditionalLoggingEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "PeerConnectionEnabled"_s, &WebPreferences::setPeerConnectionEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCPlatformTCPSocketsEnabled"_s, &WebPreferences::setWebRTCPlatformTCPSocketsEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCPlatformUDPSocketsEnabled"_s, &WebPreferences::setWebRTCPlatformUDPSocketsEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCRemoteVideoFrameEnabled"_s, &WebPreferences::setWebRTCRemoteVideoFrameEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCSFrameTransformEnabled"_s, &WebPreferences::setWebRTCSFrameTransformEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCSocketsProxyingEnabled"_s, &WebPreferences::setWebRTCSocketsProxyingEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCVP9Profile0CodecEnabled"_s, &WebPreferences::setWebRTCVP9Profile0CodecEnabled },
#endif
#if ENABLE(WEB_RTC)
        { "WebRTCVP9Profile2CodecEnabled"_s, &WebPreferences::setWebRTCVP9Profile2CodecEnabled },
#endif
#if ENABLE(WEBXR)
        { "WebXRAugmentedRealityModuleEnabled"_s, &WebPreferences::setWebXRAugmentedRealityModuleEnabled },
#endif
#if ENABLE(WEBXR)
        { "WebXREnabled"_s, &WebPreferences::setWebXREnabled },
#endif
#if ENABLE(WEBXR)
        { "WebXRGamepadsModuleEnabled"_s, &WebPreferences::setWebXRGamepadsModuleEnabled },
#endif
#if ENABLE(WEBXR_HANDS)
        { "WebXRHandInputModuleEnabled"_s, &WebPreferences::setWebXRHandInputModuleEnabled },
#endif
#if ENABLE(INPUT_TYPE_WEEK)
        { "InputTypeWeekEnabled"_s, &WebPreferences::setInputTypeWeekEnabled },
#endif
        { "WheelEventGesturesBecomeNonBlocking"_s, &WebPreferences::setWheelEventGesturesBecomeNonBlocking },
        { "PassiveWheelListenersAsDefaultOnDocument"_s, &WebPreferences::setPassiveWheelListenersAsDefaultOnDocument },
        { "IsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled"_s, &WebPreferences::setIsFirstPartyWebsiteDataRemovalLiveOnTestingEnabled },
        { "IsFirstPartyWebsiteDataRemovalReproTestingEnabled"_s, &WebPreferences::setIsFirstPartyWebsiteDataRemovalReproTestingEnabled },
#if ENABLE(INPUT_TYPE_DATETIMELOCAL)
        { "InputTypeDateTimeLocalEnabled"_s, &WebPreferences::setInputTypeDateTimeLocalEnabled },
#endif
        { "HTTPEquivEnabled"_s, &WebPreferences::setHTTPEquivEnabled },
#if ENABLE(IOS_FORM_CONTROL_REFRESH)
        { "IOSFormControlRefreshEnabled"_s, &WebPreferences::setIOSFormControlRefreshEnabled },
#endif
        { "LineHeightUnitsEnabled"_s, &WebPreferences::setLineHeightUnitsEnabled },
        { "RequestIdleCallbackEnabled"_s, &WebPreferences::setRequestIdleCallbackEnabled },
        { "CSSWordBreakAutoEnabled"_s, &WebPreferences::setCSSWordBreakAutoEnabled },
    };

    for (auto& setter : setters) {
        if (key == setter.name) {
            (this->*setter.function)(value);
            return;
        }
    }
}

void WebPreferences::enableAllExperimentalFeatures()
{
    UpdateBatch batch(*this);
    setDirPseudoEnabled(true);
    setFocusVisibleEnabled(true);
    setHasPseudoClassEnabled(true);
    setAriaReflectionForElementReferencesEnabled(true);
    setAbortSignalAnyOperationEnabled(true);
    setAccessHandleEnabled(true);
#if ENABLE(WEBGL)
    setAllowWebGLInWorkers(true);
#endif
#if ENABLE(MEDIA_STREAM)
    setPerElementSpeakerSelectionEnabled(true);
#endif
#if ENABLE(MEDIA_STREAM)
    setExposeSpeakersEnabled(true);
#endif
    setAspectRatioOfImgFromWidthAndHeightEnabled(true);
    setAsyncClipboardAPIEnabled(true);
#if ENABLE(VIDEO)
    setExtendedAudioDescriptionsEnabled(true);
#endif
#if ENABLE(VIDEO)
    setAudioDescriptionsEnabled(true);
#endif
#if ENABLE(DOM_AUDIO_SESSION)
    setDOMAudioSessionEnabled(true);
#endif
#if ENABLE(DOM_AUDIO_SESSION)
    setDOMAudioSessionFullEnabled(true);
#endif
    setBeaconAPIEnabled(true);
    setThirdPartyIframeRedirectBlockingEnabled(true);
    setBroadcastChannelEnabled(true);
    setBroadcastChannelOriginPartitioningEnabled(true);
    setCSS3DTransformInteroperabilityEnabled(true);
    setCSSCounterStyleAtRuleImageSymbolsEnabled(true);
    setCSSCounterStyleAtRulesEnabled(true);
    setCSSFontFaceSizeAdjustEnabled(true);
    setAccentColorEnabled(true);
    setAspectRatioEnabled(true);
    setCSSCascadeLayersEnabled(true);
    setCSSColor4(true);
    setCSSContainIntrinsicSizeEnabled(true);
    setCSSContainerQueriesEnabled(true);
    setCSSContainmentEnabled(true);
    setCSSContentVisibilityEnabled(true);
    setCSSCustomPropertiesAndValuesEnabled(true);
    setCSSGradientInterpolationColorSpacesEnabled(true);
    setCSSGradientPremultipliedAlphaInterpolationEnabled(true);
    setCSSIndividualTransformPropertiesEnabled(true);
    setCSSInputSecurityEnabled(true);
    setMasonryEnabled(true);
    setCSSMotionPathEnabled(true);
    setCSSNestingEnabled(true);
    setOverscrollBehaviorEnabled(true);
#if ENABLE(CSS_PAINTING_API)
    setCSSPaintingAPIEnabled(true);
#endif
    setCSSRelativeColorSyntaxEnabled(true);
    setCSSRhythmicSizingEnabled(true);
    setCSSScrollAnchoringEnabled(true);
    setCSSTypedOMEnabled(true);
    setCSSTypedOMColorEnabled(true);
    setMasonryTrackAlignmentEnabled(true);
    setCSSColorContrastEnabled(true);
    setCSSColorMixEnabled(true);
    setCSSMarginTrimEnabled(true);
    setOverflowClipEnabled(true);
    setCSSScrollbarColorEnabled(true);
    setCSSScrollbarGutterEnabled(true);
    setCSSScrollbarWidthEnabled(true);
    setSubgridEnabled(true);
    setCSSTextAlignLastEnabled(true);
    setCSSTextBoxTrimEnabled(true);
    setCSSTextGroupAlignEnabled(true);
    setCSSTextJustifyEnabled(true);
    setCSSTextSpacingEnabled(true);
    setCSSWhiteSpaceLonghandsEnabled(true);
    setCSSTextWrapNewValuesEnabled(true);
    setCSSOMViewScrollingAPIEnabled(true);
    setCSSOMViewSmoothScrollingEnabled(true);
    setCanvasColorSpaceEnabled(true);
    setClearSiteDataHTTPHeaderEnabled(true);
    setCompressionStreamEnabled(true);
    setConstructableStylesheetsEnabled(true);
    setContactPickerAPIEnabled(true);
    setCookieStoreAPIExtendedAttributesEnabled(true);
    setCookieStoreAPIEnabled(true);
    setCrossOriginEmbedderPolicyEnabled(true);
    setCrossOriginOpenerPolicyEnabled(true);
    setDeclarativeShadowDOMInDOMParserEnabled(true);
    setDeclarativeShadowDOMEnabled(true);
    setDefaultARIAForCustomElementsEnabled(true);
    setShouldDeferAsynchronousScriptsUntilAfterDocumentLoadOrFirstPaint(true);
    setDeprecateRSAESPKCSWebCryptoEnabled(true);
    setDeprecationReportingEnabled(true);
    setDisallowSyncXHRDuringPageDismissalEnabled(true);
    setEmbedElementEnabled(true);
    setCanvasFingerprintingQuirkEnabled(true);
#if ENABLE(PDFJS)
    setPdfJSViewerEnabled(true);
#endif
#if ENABLE(SERVICE_WORKER)
    setBackgroundFetchAPIEnabled(true);
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
    setMediaSessionCoordinatorEnabled(true);
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR) && ENABLE(MEDIA_SESSION_PLAYLIST)
    setMediaSessionPlaylistEnabled(true);
#endif
    setFetchAPIKeepAliveEnabled(true);
    setFetchAPIEnabled(true);
    setFetchMetadataEnabled(true);
    setFetchPriorityEnabled(true);
    setFileSystemAccessEnabled(true);
    setRequestSubmitEnabled(true);
    setFormAssociatedCustomElementsEnabled(true);
#if ENABLE(GPU_PROCESS) && !(PLATFORM(GTK) || PLATFORM(WPE))
    setUseGPUProcessForCanvasRenderingEnabled(true);
#endif
#if ENABLE(GPU_PROCESS)
    setUseGPUProcessForDOMRenderingEnabled(true);
#endif
#if HAVE(SCREEN_CAPTURE_KIT)
    setUseGPUProcessForDisplayCapture(true);
#endif
#if ENABLE(GAMEPAD)
    setGamepadTriggerRumbleEnabled(true);
#endif
#if ENABLE(GAMEPAD)
    setGamepadVibrationActuatorEnabled(true);
#endif
#if ENABLE(VIDEO)
    setGenericCueAPIEnabled(true);
#endif
    setDialogElementEnabled(true);
#if ENABLE(MODEL_ELEMENT)
    setModelElementEnabled(true);
#endif
#if ENABLE(MODEL_ELEMENT)
    setModelDocumentEnabled(true);
#endif
    setInertAttributeEnabled(true);
    setPopoverAttributeEnabled(true);
    setHighlightAPIEnabled(true);
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    setImageAnimationControlEnabled(true);
#endif
    setImperativeSlotAPIEnabled(true);
    setIntersectionObserverEnabled(true);
    setIsLoggedInAPIEnabled(true);
    setJavaScriptEnabled(true);
    setLazyIframeLoadingEnabled(true);
    setLazyImageLoadingEnabled(true);
    setLinkPreloadResponsiveImagesEnabled(true);
    setLinkModulePreloadEnabled(true);
    setLinkPreconnectEarlyHintsEnabled(true);
    setLinkPrefetchEnabled(true);
    setLiveRangeSelectionEnabled(true);
    setLocalStorageEnabled(true);
#if ENABLE(MANAGED_MEDIA_SOURCE)
    setManagedMediaSourceEnabled(true);
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE) && ENABLE(WIRELESS_PLAYBACK_TARGET)
    setManagedMediaSourceNeedsAirPlay(true);
#endif
#if ENABLE(WEBGL)
    setMaskWebGLStringsEnabled(true);
#endif
    setMediaCapabilitiesExtensionsEnabled(true);
#if ENABLE(MEDIA_SESSION)
    setMediaSessionEnabled(true);
#endif
#if ENABLE(MEDIA_RECORDER)
    setMediaRecorderEnabled(true);
#endif
    setInlineFormattingContextIntegrationEnabled(true);
#if ENABLE(NOTIFICATIONS)
    setNotificationsEnabled(true);
#endif
#if ENABLE(OFFSCREEN_CANVAS_IN_WORKERS)
    setOffscreenCanvasInWorkersEnabled(true);
#endif
#if ENABLE(OFFSCREEN_CANVAS)
    setOffscreenCanvasEnabled(true);
#endif
#if ENABLE(OPUS)
    setOpusDecoderEnabled(true);
#endif
    setPaintTimingEnabled(true);
    setPerformanceNavigationTimingAPIEnabled(true);
    setPerformanceResourceTimingSensitivePropertiesEnabled(true);
    setPermissionsAPIEnabled(true);
    setPrivateClickMeasurementFraudPreventionEnabled(true);
    setGoogleAntiFlickerOptimizationQuirkEnabled(true);
    setReadableByteStreamAPIEnabled(true);
    setReferrerPolicyAttributeEnabled(true);
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    setRemotePlaybackEnabled(true);
#endif
    setReportingEnabled(true);
    setRequestVideoFrameCallbackEnabled(true);
    setResizeObserverEnabled(true);
    setScreenOrientationLockingAPIEnabled(true);
    setScreenOrientationAPIEnabled(true);
    setScreenWakeLockAPIEnabled(true);
#if ENABLE(MEDIA_STREAM)
    setScreenCaptureEnabled(true);
#endif
    setScrollToTextFragmentEnabled(true);
    setSelectionAPIForShadowDOMEnabled(true);
    setSendMouseEventsToDisabledFormControlsEnabled(true);
    setServerTimingEnabled(true);
#if ENABLE(SERVICE_WORKER)
    setServiceWorkerNavigationPreloadEnabled(true);
#endif
#if ENABLE(SERVICE_WORKER)
    setServiceWorkersEnabled(true);
#endif
    setShapeDetection(true);
    setSharedWorkerEnabled(true);
    setSpeechRecognitionEnabled(true);
    setStorageAPIEstimateEnabled(true);
    setStorageAPIEnabled(true);
    setStorageAccessAPIEnabled(true);
    setProcessSwapOnCrossSiteNavigationEnabled(true);
    setSyntheticEditingCommandsEnabled(true);
    setTrackConfigurationEnabled(true);
    setTransformStreamAPIEnabled(true);
    setUnprefixedFullscreenAPIEnabled(true);
    setUserActivationAPIEnabled(true);
    setVerifyWindowOpenUserGestureFromUIProcess(true);
    setVerticalFormControlsEnabled(true);
    setVisualViewportAPIEnabled(true);
#if ENABLE(VORBIS)
    setVorbisDecoderEnabled(true);
#endif
    setWebAnimationsCompositeOperationsEnabled(true);
    setWebAnimationsCustomEffectsEnabled(true);
    setWebAnimationsCustomFrameRateEnabled(true);
    setWebAnimationsIterationCompositeEnabled(true);
    setWebAnimationsMutableTimelinesEnabled(true);
    setWebCryptoSafeCurvesEnabled(true);
    setWebLocksAPIEnabled(true);
    setWebShareFileAPIEnabled(true);
#if ENABLE(WEBASSEMBLY)
    setWebAssemblyESMIntegrationEnabled(true);
#endif
#if ENABLE(WEB_CODECS)
    setWebCodecsEnabled(true);
#endif
#if ENABLE(WEB_CODECS)
    setWebCodecsAV1Enabled(true);
#endif
#if ENABLE(WEB_CODECS)
    setWebCodecsHEVCEnabled(true);
#endif
    setWebGLEnabled(true);
#if ENABLE(WEB_RTC)
    setWebRTCAV1CodecEnabled(true);
#endif
#if ENABLE(WEB_RTC)
    setWebRTCEncodedTransformEnabled(true);
#endif
#if ENABLE(WEB_RTC)
    setWebRTCSFrameTransformEnabled(true);
#endif
#if ENABLE(WEBXR)
    setWebXRAugmentedRealityModuleEnabled(true);
#endif
#if ENABLE(WEBXR)
    setWebXREnabled(true);
#endif
#if ENABLE(WEBXR)
    setWebXRGamepadsModuleEnabled(true);
#endif
#if ENABLE(WEBXR_HANDS)
    setWebXRHandInputModuleEnabled(true);
#endif
    setWheelEventGesturesBecomeNonBlocking(true);
    setHTTPEquivEnabled(true);
    setLineHeightUnitsEnabled(true);
    setCSSWordBreakAutoEnabled(true);
}

void WebPreferences::resetAllInternalDebugFeatures()
{
    UpdateBatch batch(*this);
    setPageAtRuleSupportEnabled(DEFAULT_VALUE_FOR_PageAtRuleSupportEnabled);
#if USE(CORE_IMAGE)
    setAcceleratedFiltersEnabled(DEFAULT_VALUE_FOR_AcceleratedFiltersEnabled);
#endif
    setDOMTestingAPIsEnabled(DEFAULT_VALUE_FOR_DOMTestingAPIsEnabled);
#if PLATFORM(IOS_FAMILY)
    setAllowViewportShrinkToFitContent(DEFAULT_VALUE_FOR_AllowViewportShrinkToFitContent);
#endif
#if ENABLE(ALTERNATE_WEBM_PLAYER)
    setAlternateWebMPlayerEnabled(DEFAULT_VALUE_FOR_AlternateWebMPlayerEnabled);
#endif
#if ENABLE(BADGING)
    setAppBadgeEnabled(DEFAULT_VALUE_FOR_AppBadgeEnabled);
#endif
#if ENABLE(APP_HIGHLIGHTS)
    setAppHighlightsEnabled(DEFAULT_VALUE_FOR_AppHighlightsEnabled);
#endif
    setAsyncFrameScrollingEnabled(DEFAULT_VALUE_FOR_AsyncFrameScrollingEnabled);
    setAsyncOverflowScrollingEnabled(DEFAULT_VALUE_FOR_AsyncOverflowScrollingEnabled);
#if ENABLE(BUILT_IN_NOTIFICATIONS)
    setBuiltInNotificationsEnabled(DEFAULT_VALUE_FOR_BuiltInNotificationsEnabled);
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
    setUseCGDisplayListsForDOMRendering(DEFAULT_VALUE_FOR_UseCGDisplayListsForDOMRendering);
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
    setUseCGDisplayListImageCache(DEFAULT_VALUE_FOR_UseCGDisplayListImageCache);
#endif
#if ENABLE(CG_DISPLAY_LIST_BACKED_IMAGE_BUFFER)
    setReplayCGDisplayListsIntoBackingStore(DEFAULT_VALUE_FOR_ReplayCGDisplayListsIntoBackingStore);
#endif
    setSpringTimingFunctionEnabled(DEFAULT_VALUE_FOR_SpringTimingFunctionEnabled);
    setCSSTextUnderlinePositionLeftRightEnabled(DEFAULT_VALUE_FOR_CSSTextUnderlinePositionLeftRightEnabled);
#if ENABLE(CSS_TRANSFORM_STYLE_OPTIMIZED_3D)
    setCSSTransformStyleOptimized3DEnabled(DEFAULT_VALUE_FOR_CSSTransformStyleOptimized3DEnabled);
#endif
    setCanvasFiltersEnabled(DEFAULT_VALUE_FOR_CanvasFiltersEnabled);
#if ENABLE(MEDIA_STREAM)
    setCaptureAudioInUIProcessEnabled(DEFAULT_VALUE_FOR_CaptureAudioInUIProcessEnabled);
#endif
#if ENABLE(MEDIA_STREAM)
    setCaptureVideoInUIProcessEnabled(DEFAULT_VALUE_FOR_CaptureVideoInUIProcessEnabled);
#endif
#if ENABLE(BADGING)
    setClientBadgeEnabled(DEFAULT_VALUE_FOR_ClientBadgeEnabled);
#endif
    setCompositingBordersVisible(DEFAULT_VALUE_FOR_CompositingBordersVisible);
    setCompositingRepaintCountersVisible(DEFAULT_VALUE_FOR_CompositingRepaintCountersVisible);
#if HAVE(AVCONTENTKEYSPECIFIER)
    setSampleBufferContentKeySessionSupportEnabled(DEFAULT_VALUE_FOR_SampleBufferContentKeySessionSupportEnabled);
#endif
    setCookieConsentAPIEnabled(DEFAULT_VALUE_FOR_CookieConsentAPIEnabled);
    setDOMPasteAccessRequestsEnabled(DEFAULT_VALUE_FOR_DOMPasteAccessRequestsEnabled);
#if PLATFORM(IOS_FAMILY)
    setZoomOnDoubleTapWhenRoot(DEFAULT_VALUE_FOR_ZoomOnDoubleTapWhenRoot);
#endif
#if PLATFORM(IOS_FAMILY)
    setAlwaysZoomOnDoubleTap(DEFAULT_VALUE_FOR_AlwaysZoomOnDoubleTap);
#endif
#if PLATFORM(IOS_FAMILY)
    setDisableScreenSizeOverride(DEFAULT_VALUE_FOR_DisableScreenSizeOverride);
#endif
    setDisplayListDrawingEnabled(DEFAULT_VALUE_FOR_DisplayListDrawingEnabled);
    setShouldDropNearSuspendedAssertionAfterDelay(DEFAULT_VALUE_FOR_ShouldDropNearSuspendedAssertionAfterDelay);
    setAutomaticLiveResizeEnabled(DEFAULT_VALUE_FOR_AutomaticLiveResizeEnabled);
    setEnumeratingAllNetworkInterfacesEnabled(DEFAULT_VALUE_FOR_EnumeratingAllNetworkInterfacesEnabled);
    setEnumeratingVisibleNetworkInterfacesEnabled(DEFAULT_VALUE_FOR_EnumeratingVisibleNetworkInterfacesEnabled);
    setICECandidateFilteringEnabled(DEFAULT_VALUE_FOR_ICECandidateFilteringEnabled);
#if ENABLE(MEDIA_STREAM)
    setMockCaptureDevicesEnabled(DEFAULT_VALUE_FOR_MockCaptureDevicesEnabled);
#endif
#if PLATFORM(MAC) && USE(RUNNINGBOARD)
    setBackgroundWebContentRunningBoardThrottlingEnabled(DEFAULT_VALUE_FOR_BackgroundWebContentRunningBoardThrottlingEnabled);
#endif
#if HAVE(MACH_BOOTSTRAP_EXTENSION) || HAVE(SANDBOX_STATE_FLAGS)
    setExperimentalSandboxEnabled(DEFAULT_VALUE_FOR_ExperimentalSandboxEnabled);
#endif
    setStrictSecureDecodingForAllObjC(DEFAULT_VALUE_FOR_StrictSecureDecodingForAllObjC);
    setEnterKeyHintEnabled(DEFAULT_VALUE_FOR_EnterKeyHintEnabled);
    setEventHandlerDrivenSmoothKeyboardScrollingEnabled(DEFAULT_VALUE_FOR_EventHandlerDrivenSmoothKeyboardScrollingEnabled);
#if ENABLE(MEDIA_SOURCE) && (HAVE(AVSAMPLEBUFFERVIDEOOUTPUT) || USE(GSTREAMER))
    setMediaSourceInlinePaintingEnabled(DEFAULT_VALUE_FOR_MediaSourceInlinePaintingEnabled);
#endif
#if HAVE(NETWORK_LOADER)
    setCFNetworkNetworkLoaderEnabled(DEFAULT_VALUE_FOR_CFNetworkNetworkLoaderEnabled);
#endif
#if PLATFORM(IOS_FAMILY)
    setPreferFasterClickOverDoubleTap(DEFAULT_VALUE_FOR_PreferFasterClickOverDoubleTap);
#endif
#if PLATFORM(IOS_FAMILY)
    setFasterClicksEnabled(DEFAULT_VALUE_FOR_FasterClicksEnabled);
#endif
    setRestrictedHTTPResponseAccess(DEFAULT_VALUE_FOR_RestrictedHTTPResponseAccess);
#if PLATFORM(IOS_FAMILY)
    setForceAlwaysUserScalable(DEFAULT_VALUE_FOR_ForceAlwaysUserScalable);
#endif
    setLayoutFormattingContextEnabled(DEFAULT_VALUE_FOR_LayoutFormattingContextEnabled);
#if PLATFORM(VISION)
    setFullscreenSceneAspectRatioLockingEnabled(DEFAULT_VALUE_FOR_FullscreenSceneAspectRatioLockingEnabled);
#endif
#if PLATFORM(VISION)
    setFullscreenSceneDimmingEnabled(DEFAULT_VALUE_FOR_FullscreenSceneDimmingEnabled);
#endif
#if ENABLE(MEDIA_STREAM)
    setCaptureAudioInGPUProcessEnabled(DEFAULT_VALUE_FOR_CaptureAudioInGPUProcessEnabled);
#endif
#if ENABLE(GPU_PROCESS)
    setBlockMediaLayerRehostingInWebContentProcess(DEFAULT_VALUE_FOR_BlockMediaLayerRehostingInWebContentProcess);
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
    setManageCaptureStatusBarInGPUProcessEnabled(DEFAULT_VALUE_FOR_ManageCaptureStatusBarInGPUProcessEnabled);
#endif
#if ENABLE(MEDIA_STREAM)
    setCaptureVideoInGPUProcessEnabled(DEFAULT_VALUE_FOR_CaptureVideoInGPUProcessEnabled);
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
    setUseGPUProcessForWebGLEnabled(DEFAULT_VALUE_FOR_UseGPUProcessForWebGLEnabled);
#endif
#if USE(GRAPHICS_CONTEXT_FILTERS)
    setGraphicsContextFiltersEnabled(DEFAULT_VALUE_FOR_GraphicsContextFiltersEnabled);
#endif
    setAcceleratedDrawingEnabled(DEFAULT_VALUE_FOR_AcceleratedDrawingEnabled);
#if HAVE(SANDBOX_STATE_FLAGS)
    setBlockIOKitInWebContentSandbox(DEFAULT_VALUE_FOR_BlockIOKitInWebContentSandbox);
#endif
#if ENABLE(IPC_TESTING_API)
    setIPCTestingAPIEnabled(DEFAULT_VALUE_FOR_IPCTestingAPIEnabled);
#endif
#if ENABLE(IMAGE_ANALYSIS)
    setImageAnalysisDuringFindInPageEnabled(DEFAULT_VALUE_FOR_ImageAnalysisDuringFindInPageEnabled);
#endif
#if ENABLE(SERVICE_CONTROLS)
    setImageControlsEnabled(DEFAULT_VALUE_FOR_ImageControlsEnabled);
#endif
    setInlinePredictionsInAllEditableElementsEnabled(DEFAULT_VALUE_FOR_InlinePredictionsInAllEditableElementsEnabled);
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
    setInteractionRegionsEnabled(DEFAULT_VALUE_FOR_InteractionRegionsEnabled);
#endif
#if ENABLE(LAYER_BASED_SVG_ENGINE)
    setLayerBasedSVGEngineEnabled(DEFAULT_VALUE_FOR_LayerBasedSVGEngineEnabled);
#endif
#if ENABLE(OVERFLOW_SCROLLING_TOUCH)
    setLegacyOverflowScrollingTouchEnabled(DEFAULT_VALUE_FOR_LegacyOverflowScrollingTouchEnabled);
#endif
    setLegacyLineLayoutVisualCoverageEnabled(DEFAULT_VALUE_FOR_LegacyLineLayoutVisualCoverageEnabled);
#if ENABLE(MEDIA_STREAM)
    setMediaCaptureRequiresSecureConnection(DEFAULT_VALUE_FOR_MediaCaptureRequiresSecureConnection);
#endif
    setLinkSanitizerEnabled(DEFAULT_VALUE_FOR_LinkSanitizerEnabled);
    setLocalFileContentSniffingEnabled(DEFAULT_VALUE_FOR_LocalFileContentSniffingEnabled);
    setLogsPageMessagesToSystemConsoleEnabled(DEFAULT_VALUE_FOR_LogsPageMessagesToSystemConsoleEnabled);
    setCoreMathMLEnabled(DEFAULT_VALUE_FOR_CoreMathMLEnabled);
    setMomentumScrollingAnimatorEnabled(DEFAULT_VALUE_FOR_MomentumScrollingAnimatorEnabled);
#if ENABLE(TOUCH_EVENTS)
    setMouseEventsSimulationEnabled(DEFAULT_VALUE_FOR_MouseEventsSimulationEnabled);
#endif
#if ENABLE(MEDIA_STREAM)
    setMuteCameraOnMicrophoneInterruptionEnabled(DEFAULT_VALUE_FOR_MuteCameraOnMicrophoneInterruptionEnabled);
#endif
#if ENABLE(APP_BOUND_DOMAINS)
    setNeedsInAppBrowserPrivacyQuirks(DEFAULT_VALUE_FOR_NeedsInAppBrowserPrivacyQuirks);
#endif
    setFlexFormattingContextIntegrationEnabled(DEFAULT_VALUE_FOR_FlexFormattingContextIntegrationEnabled);
#if ENABLE(NOTIFICATION_EVENT)
    setNotificationEventEnabled(DEFAULT_VALUE_FOR_NotificationEventEnabled);
#endif
    setPageVisibilityBasedProcessSuppressionEnabled(DEFAULT_VALUE_FOR_PageVisibilityBasedProcessSuppressionEnabled);
    setBlobRegistryTopOriginPartitioningEnabled(DEFAULT_VALUE_FOR_BlobRegistryTopOriginPartitioningEnabled);
#if ENABLE(VIDEO)
    setPreferSandboxedMediaParsing(DEFAULT_VALUE_FOR_PreferSandboxedMediaParsing);
#endif
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    setRemoveBackgroundEnabled(DEFAULT_VALUE_FOR_RemoveBackgroundEnabled);
#endif
#if HAVE(SC_CONTENT_SHARING_PICKER)
    setRequireUAGetDisplayMediaPrompt(DEFAULT_VALUE_FOR_RequireUAGetDisplayMediaPrompt);
#endif
#if ENABLE(MEDIA_STREAM)
    setSpeakerSelectionRequiresUserGesture(DEFAULT_VALUE_FOR_SpeakerSelectionRequiresUserGesture);
#endif
#if ENABLE(MEDIA_STREAM)
    setGetUserMediaRequiresFocus(DEFAULT_VALUE_FOR_GetUserMediaRequiresFocus);
#endif
    setResourceLoadSchedulingEnabled(DEFAULT_VALUE_FOR_ResourceLoadSchedulingEnabled);
#if ENABLE(RESOURCE_USAGE)
    setResourceUsageOverlayVisible(DEFAULT_VALUE_FOR_ResourceUsageOverlayVisible);
#endif
    setIsSameSiteStrictEnforcementEnabled(DEFAULT_VALUE_FOR_IsSameSiteStrictEnforcementEnabled);
    setScrollingPerformanceTestingEnabled(DEFAULT_VALUE_FOR_ScrollingPerformanceTestingEnabled);
    setSecureContextChecksEnabled(DEFAULT_VALUE_FOR_SecureContextChecksEnabled);
    setSiteIsolationEnabled(DEFAULT_VALUE_FOR_SiteIsolationEnabled);
    setProcessSwapOnCrossSiteWindowOpenEnabled(DEFAULT_VALUE_FOR_ProcessSwapOnCrossSiteWindowOpenEnabled);
    setShouldTakeNearSuspendedAssertions(DEFAULT_VALUE_FOR_ShouldTakeNearSuspendedAssertions);
#if ENABLE(IMAGE_ANALYSIS)
    setTextRecognitionInVideosEnabled(DEFAULT_VALUE_FOR_TextRecognitionInVideosEnabled);
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
    setThreadedAnimationResolutionEnabled(DEFAULT_VALUE_FOR_ThreadedAnimationResolutionEnabled);
#endif
    setTiledScrollingIndicatorVisible(DEFAULT_VALUE_FOR_TiledScrollingIndicatorVisible);
    setUndoManagerAPIEnabled(DEFAULT_VALUE_FOR_UndoManagerAPIEnabled);
    setUpgradeKnownHostsToHTTPSEnabled(DEFAULT_VALUE_FOR_UpgradeKnownHostsToHTTPSEnabled);
#if ENABLE(ARKIT_INLINE_PREVIEW)
    setUseARKitForModel(DEFAULT_VALUE_FOR_UseARKitForModel);
#endif
    setUseGeneralDirectoryForStorage(DEFAULT_VALUE_FOR_UseGeneralDirectoryForStorage);
#if HAVE(SC_CONTENT_SHARING_PICKER)
    setUseSCContentSharingPicker(DEFAULT_VALUE_FOR_UseSCContentSharingPicker);
#endif
#if HAVE(SCENEKIT)
    setUseSceneKitForModel(DEFAULT_VALUE_FOR_UseSceneKitForModel);
#endif
    setUserGesturePromisePropagationEnabled(DEFAULT_VALUE_FOR_UserGesturePromisePropagationEnabled);
#if ENABLE(VP9)
    setVP9SWDecoderEnabledOnBattery(DEFAULT_VALUE_FOR_VP9SWDecoderEnabledOnBattery);
#endif
#if ENABLE(SERVICE_WORKER)
    setServiceWorkersUserGestureEnabled(DEFAULT_VALUE_FOR_ServiceWorkersUserGestureEnabled);
#endif
#if ENABLE(IMAGE_ANALYSIS)
    setVisualTranslationEnabled(DEFAULT_VALUE_FOR_VisualTranslationEnabled);
#endif
    setWebAPIStatisticsEnabled(DEFAULT_VALUE_FOR_WebAPIStatisticsEnabled);
    setWebAPIsInShadowRealmEnabled(DEFAULT_VALUE_FOR_WebAPIsInShadowRealmEnabled);
#if ENABLE(WEB_ARCHIVE)
    setWebArchiveTestingModeEnabled(DEFAULT_VALUE_FOR_WebArchiveTestingModeEnabled);
#endif
    setWebGLDraftExtensionsEnabled(DEFAULT_VALUE_FOR_WebGLDraftExtensionsEnabled);
#if ENABLE(WEBGL) && PLATFORM(COCOA)
    setWebGLUsingMetal(DEFAULT_VALUE_FOR_WebGLUsingMetal);
#endif
    setWebGPUEnabled(DEFAULT_VALUE_FOR_WebGPUEnabled);
    setWebInspectorEngineeringSettingsAllowed(DEFAULT_VALUE_FOR_WebInspectorEngineeringSettingsAllowed);
    setWebRTCAudioLatencyAdaptationEnabled(DEFAULT_VALUE_FOR_WebRTCAudioLatencyAdaptationEnabled);
#if ENABLE(WEB_RTC)
    setWebRTCDTMFEnabled(DEFAULT_VALUE_FOR_WebRTCDTMFEnabled);
#endif
#if ENABLE(WEB_RTC)
    setWebRTCH264HardwareEncoderEnabled(DEFAULT_VALUE_FOR_WebRTCH264HardwareEncoderEnabled);
#endif
#if ENABLE(WEB_RTC)
    setWebRTCH264LowLatencyEncoderEnabled(DEFAULT_VALUE_FOR_WebRTCH264LowLatencyEncoderEnabled);
#endif
#if ENABLE(WEB_RTC)
    setWebRTCH264SimulcastEnabled(DEFAULT_VALUE_FOR_WebRTCH264SimulcastEnabled);
#endif
#if USE(LIBWEBRTC)
    setWebRTCMediaPipelineAdditionalLoggingEnabled(DEFAULT_VALUE_FOR_WebRTCMediaPipelineAdditionalLoggingEnabled);
#endif
#if ENABLE(WEB_RTC)
    setWebRTCPlatformTCPSocketsEnabled(DEFAULT_VALUE_FOR_WebRTCPlatformTCPSocketsEnabled);
#endif
#if ENABLE(WEB_RTC)
    setWebRTCPlatformUDPSocketsEnabled(DEFAULT_VALUE_FOR_WebRTCPlatformUDPSocketsEnabled);
#endif
#if ENABLE(WEB_RTC)
    setWebRTCRemoteVideoFrameEnabled(DEFAULT_VALUE_FOR_WebRTCRemoteVideoFrameEnabled);
#endif
#if ENABLE(WEB_RTC)
    setWebRTCSocketsProxyingEnabled(DEFAULT_VALUE_FOR_WebRTCSocketsProxyingEnabled);
#endif
#if ENABLE(WEB_RTC)
    setWebRTCVP9Profile0CodecEnabled(DEFAULT_VALUE_FOR_WebRTCVP9Profile0CodecEnabled);
#endif
#if ENABLE(IOS_FORM_CONTROL_REFRESH)
    setIOSFormControlRefreshEnabled(DEFAULT_VALUE_FOR_IOSFormControlRefreshEnabled);
#endif
    setRequestIdleCallbackEnabled(DEFAULT_VALUE_FOR_RequestIdleCallbackEnabled);
}

}
