/*
 * Copyright (C) 2022 Apple Inc. All rights reserved.
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

#pragma once

#include <wtf/ArgumentCoder.h>
#include <wtf/OptionSet.h>
#include <wtf/Ref.h>

namespace WebKit { enum class PreconnectOnly : bool; }
namespace WebKit { enum class ListType : uint8_t; }
namespace WebKit { enum class TextAlignment : uint8_t; }
namespace WebKit { enum class TypingAttribute : uint8_t; }
namespace WebKit { enum class FrameType : bool; }
namespace WebKit { enum class RemoteWorkerType : uint8_t; }
namespace WebKit { enum class SameDocumentNavigationType : uint8_t; }
namespace WebCore { enum class FontWidthVariant : uint8_t; }
namespace WebCore { enum class Kerning : uint8_t; }
namespace WebCore { enum class FontOpticalSizing : uint8_t; }
namespace WebCore { enum class FontStyleAxis : uint8_t; }
namespace WebCore { enum class AllowUserInstalledFonts : bool; }
namespace WebCore { enum class FontVariantEastAsianVariant : uint8_t; }
namespace WebCore { enum class FontVariantEastAsianWidth : uint8_t; }
namespace WebCore { enum class FontVariantEastAsianRuby : uint8_t; }
namespace WebCore { enum class FontVariantLigatures : uint8_t; }
namespace WebCore { enum class FontVariantPosition : uint8_t; }
namespace WebCore { enum class FontVariantCaps : uint8_t; }
namespace WebCore { enum class FontVariantNumericFigure : uint8_t; }
namespace WebCore { enum class FontVariantNumericSpacing : uint8_t; }
namespace WebCore { enum class FontVariantNumericFraction : uint8_t; }
namespace WebCore { enum class TextRenderingMode : uint8_t; }
namespace WebCore { enum class FontSmoothingMode : uint8_t; }
namespace WebCore { enum class FontOrientation : bool; }
namespace WebCore { enum class NonCJKGlyphOrientation : bool; }
namespace WebCore { enum class FontSynthesisLonghandValue : bool; }
namespace WebCore { enum class FontSmallCaps : bool; }
#if ENABLE(APPLE_PAY)
namespace WebCore { enum class ApplePayFeature : uint8_t; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { enum class ApplePayPaymentTiming : uint8_t; }
#endif
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
namespace WebCore { enum class ApplePayRecurringPaymentDateUnit : uint8_t; }
#endif
namespace WebCore { enum class ContactProperty : uint8_t; }
namespace WebCore { enum class CookieConsentDecisionResult : uint8_t; }
namespace WebCore { enum class IDBResultType : uint8_t; }
namespace WebCore { enum class IDBTransactionDurability : uint8_t; }
namespace WebCore { enum class IDBTransactionMode : uint8_t; }
#if ENABLE(MEDIA_SESSION)
namespace WebCore { enum class MediaSessionAction : uint8_t; }
#endif
#if ENABLE(MEDIA_SESSION)
namespace WebCore { enum class MediaSessionPlaybackState : uint8_t; }
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
namespace WebCore { enum class MediaSessionCoordinatorState : uint8_t; }
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
namespace WebCore { enum class MediaSessionReadyState : uint8_t; }
#endif
namespace WebCore { enum class RTCErrorDetailType : uint8_t; }
namespace WebCore { enum class NotificationEventType : bool; }
namespace WebCore { enum class PermissionName : uint8_t; }
namespace WebCore { enum class PermissionQuerySource : uint8_t; }
namespace WebCore { enum class PermissionState : uint8_t; }
#if ENABLE(SERVICE_WORKER)
namespace WebCore { enum class PushPermissionState : uint8_t; }
#endif
namespace WebCore { enum class AutofillFieldName : uint8_t; }
namespace WebCore { enum class NonAutofillCredentialType : bool; }
namespace WebCore { enum class EnterKeyHint : uint8_t; }
namespace WebCore { enum class DownloadableBinaryFontAllowedTypes : uint8_t; }
namespace WebCore { enum class LoadSchedulingMode : uint8_t; }
namespace WebCore { enum class ServiceWorkersMode : uint8_t; }
namespace WebCore { enum class ShouldTreatAsContinuingLoad : uint8_t; }
namespace WebCore { enum class ContentSecurityPolicyModeForExtension : uint8_t; }
namespace WebCore { enum class MediaProducerMediaCaptureKind : uint8_t; }
namespace WebCore { enum class ScreenOrientationType : uint8_t; }
namespace WebCore { enum class StorageBlockingPolicy : uint8_t; }
#if HAVE(TRANSLATION_UI_SERVICES) && ENABLE(CONTEXT_MENUS)
namespace WebCore { enum class TranslationContextMenuMode : bool; }
#endif
#if HAVE(TRANSLATION_UI_SERVICES) && ENABLE(CONTEXT_MENUS)
namespace WebCore { enum class TranslationContextMenuSource : bool; }
#endif
#if USE(APPKIT)
namespace WebCore { enum class AppKitControlSystemImageType : uint8_t; }
#endif
namespace WebCore { enum class ScrollIsAnimated : bool; }
namespace WebCore { enum class ScrollGranularity : uint8_t; }
namespace WebCore::IndexedDB { enum class KeyType : int8_t; }
namespace WebCore::IndexedDB { enum class CursorDirection : uint8_t; }
namespace WebCore::IndexedDB { enum class ObjectStoreOverwriteMode : uint8_t; }
namespace WebCore::IndexedDB { enum class RequestType : uint8_t; }
namespace WebCore { enum class NavigatorAPIsAccessed : uint64_t; }
namespace WebCore { enum class ScreenAPIsAccessed : uint64_t; }
namespace WebCore { enum class ViewportFit : uint8_t; }
namespace WebCore { enum class ShareDataOriginator : bool; }
namespace WebCore::PCM { enum class AttributionEphemeral : bool; }
namespace WebCore::PCM { enum class WasSent : bool; }
#if ENABLE(APPLE_PAY)
namespace WebCore { enum class ApplePayLogoStyle : bool; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { enum class ApplePayErrorContactField : uint8_t; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { enum class ApplePayErrorCode : uint8_t; }
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
namespace WebCore { enum class ApplePaySetupFeatureType : bool; }
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
namespace WebCore { enum class ApplePayInstallmentItemType : uint8_t; }
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
namespace WebCore { enum class ApplePayInstallmentRetailChannel : uint8_t; }
#endif
namespace WebCore { enum class ScreenOrientationLockType : uint8_t; }
namespace WebCore::DOMCacheEngine { enum class Error : uint8_t; }
#if ENABLE(WEB_CODECS)
namespace WebCore { enum class WebCodecsEncodedVideoChunkType : bool; }
#endif
namespace WebCore { enum class SpeechRecognitionErrorType : uint8_t; }
#if ENABLE(WEB_AUTHN)
namespace WebCore { enum class AttestationConveyancePreference : uint8_t; }
#endif
namespace WebCore { enum class RenderingMode : bool; }
namespace WebCore { enum class RenderingPurpose : uint8_t; }
namespace WebCore { enum class RotationDirection : bool; }
namespace WebCore { enum class AutoplayEvent : uint8_t; }
namespace WebCore { enum class InputMode : uint8_t; }
namespace WebCore { enum class NotificationDirection : uint8_t; }
namespace WebCore::IndexedDB { enum class GetAllType : bool; }
namespace WebCore { enum class WorkerType : bool; }
namespace WebCore { enum class StoredCredentialsPolicy : uint8_t; }
namespace WebCore { enum class ContentSniffingPolicy : bool; }
namespace WebCore { enum class ContentEncodingSniffingPolicy : bool; }
namespace WebCore { enum class ClientCredentialPolicy : bool; }
namespace WebCore { enum class ShouldRelaxThirdPartyCookieBlocking : bool; }
namespace WebCore { enum class PreflightPolicy : uint8_t; }
enum class WTFLogChannelState : uint8_t;
namespace WebCore { enum class ScrollSnapStrictness : uint8_t; }
namespace WebCore { enum class LengthType : uint8_t; }
namespace WebCore { enum class OverscrollBehavior : uint8_t; }
namespace WebCore { enum class ScrollPinningBehavior : uint8_t; }
namespace WebCore { enum class WheelScrollGestureState : uint8_t; }
namespace WebCore { enum class DiagnosticLoggingDomain : uint8_t; }
namespace WebCore { enum class MediaCaptureType : uint8_t; }
namespace WebCore { enum class TextCheckingProcessType : bool; }
#if ENABLE(WEB_AUTHN)
namespace WebCore { enum class AuthenticatorTransport : uint8_t; }
#endif
#if ENABLE(WEB_AUTHN)
namespace WebCore { enum class PublicKeyCredentialType : bool; }
#endif
#if ENABLE(DATALIST_ELEMENT)
namespace WebCore { enum class DataListSuggestionActivationType : uint8_t; }
#endif
namespace WebCore { enum class AlphaPremultiplication : uint8_t; }
namespace WebCore { enum class PixelFormat : uint8_t; }
namespace WebCore { enum class HasInsecureContent : bool; }
namespace WebCore { enum class ScrollElasticity : uint8_t; }
namespace WebCore { enum class ScrollbarMode : uint8_t; }
namespace WebCore { enum class NativeScrollbarVisibility : uint8_t; }
namespace WebCore { enum class ScrollbarWidth : uint8_t; }
namespace WebCore { enum class WheelEventProcessingSteps : uint8_t; }
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
namespace WebCore { enum class GraphicsContextGLPowerPreference : uint8_t; }
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
namespace WebCore { enum class GraphicsContextGLWebGLVersion : uint8_t; }
#endif
namespace WebCore { enum class CSSBoxType : uint8_t; }
#if PLATFORM(IOS_FAMILY)
namespace WebCore { enum class SelectionRenderingBehavior : bool; }
#endif
#if ENABLE(WEB_AUTHN)
namespace WebCore { enum class UserVerificationRequirement : uint8_t; }
#endif
#if ENABLE(WEB_AUTHN)
namespace WebCore { enum class ResidentKeyRequirement : uint8_t; }
#endif
#if ENABLE(WEB_AUTHN)
namespace WebCore { enum class AuthenticatorAttachment : uint8_t; }
#endif
namespace WebCore { enum class ResourceRequestCachePolicy : uint8_t; }
namespace WebCore { enum class ResourceLoadPriority : uint8_t; }
namespace WebCore { enum class ReferrerPolicy : uint8_t; }
namespace WebCore { enum class FetchOptionsDestination : uint8_t; }
namespace WebCore { enum class FetchOptionsMode : uint8_t; }
namespace WebCore { enum class FetchOptionsCredentials : uint8_t; }
namespace WebCore { enum class FetchOptionsCache : uint8_t; }
namespace WebCore { enum class FetchOptionsRedirect : uint8_t; }
namespace WebCore { enum class FetchHeadersGuard : uint8_t; }
namespace WebCore { enum class StyleAppearance : uint8_t; }
#if ENABLE(APPLE_PAY)
namespace WebCore { enum class ApplePayButtonType : uint8_t; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { enum class ApplePayButtonStyle : uint8_t; }
#endif
namespace WebCore { enum class HasInsecureContent : bool; }
namespace WebCore { enum class ModalContainerDecision : uint8_t; }
namespace WebCore { enum class AutoplayEventFlags : uint8_t; }
namespace WebCore { enum class FocusDirection : uint8_t; }
#if ENABLE(GAMEPAD)
namespace WebCore { enum class GamepadHapticEffectType : uint8_t; }
#endif
namespace WebCore { enum class DOMPasteAccessCategory : uint8_t; }
namespace WebCore { enum class DOMPasteAccessPolicy : uint8_t; }
namespace WebCore { enum class DOMPasteAccessResponse : uint8_t; }
namespace WebCore { enum class DeviceOrientationOrMotionPermissionState : uint8_t; }
namespace WebCore { enum class SecurityPolicyViolationEventDisposition : bool; }
namespace WebCore { enum class VerticalAlignChange : uint8_t; }
namespace WebCore { enum class TextGranularity : uint8_t; }
namespace WebCore { enum class WritingDirection : uint8_t; }
namespace WebCore { enum class SelectionDirection : uint8_t; }
#if ENABLE(DATA_DETECTION)
namespace WebCore { enum class DataDetectorType : uint8_t; }
#endif
namespace WebCore { enum class AutocapitalizeType : uint8_t; }
namespace WebCore { enum class CrossOriginEmbedderPolicyValue : bool; }
namespace WebCore { enum class IncludeSecureCookies : bool; }
#if ENABLE(ASYNC_SCROLLING)
namespace WebCore { enum class ScrollingStateNodeProperty : uint64_t; }
#endif
#if ENABLE(ENCRYPTED_MEDIA)
namespace WebCore { enum class CDMEncryptionScheme : bool; }
#endif
#if ENABLE(ENCRYPTED_MEDIA)
namespace WebCore { enum class CDMSessionType : uint8_t; }
#endif
namespace WebCore { enum class MediaDecodingType : uint8_t; }
namespace WebCore { enum class MediaEncodingType : bool; }
namespace WebCore { enum class MediaPlayerNetworkState : uint8_t; }
namespace WebCore { enum class MediaPlayerReadyState : uint8_t; }
namespace WebCore { enum class MediaPlayerMovieLoadType : uint8_t; }
namespace WebCore { enum class MediaPlayerPreload : uint8_t; }
namespace WebCore { enum class MediaPlayerVideoGravity : uint8_t; }
namespace WebCore { enum class MediaPlayerSupportsType : uint8_t; }
namespace WebCore { enum class MediaPlayerBufferingPolicy : uint8_t; }
namespace WebCore { enum class MediaPlayerMediaEngineIdentifier : uint8_t; }
namespace WebCore { enum class MediaPlayerWirelessPlaybackTargetType : uint8_t; }
namespace WebCore { enum class MediaPlayerPitchCorrectionAlgorithm : uint8_t; }
#if ENABLE(APP_HIGHLIGHTS)
namespace WebCore { enum class CreateNewGroupForHighlight : bool; }
#endif
#if ENABLE(APP_HIGHLIGHTS)
namespace WebCore { enum class HighlightRequestOriginatedInApp : bool; }
#endif
namespace WebCore { enum class SpeechRecognitionUpdateType : uint8_t; }
namespace WebCore { enum class CompositeOperator : uint8_t; }
namespace WebCore { enum class BlendMode : uint8_t; }
namespace WebCore { enum class GradientSpreadMethod : uint8_t; }
namespace WebCore { enum class InterpolationQuality : uint8_t; }
#if ENABLE(VIDEO)
namespace WebCore { enum class VideoFrameRotation : uint16_t; }
#endif
namespace WebCore { enum class PreserveResolution : bool; }
namespace WebCore { enum class ColorInterpolationColorSpace : uint8_t; }
namespace WebCore { enum class HueInterpolationMethod : uint8_t; }
#if USE(AUDIO_SESSION)
namespace WebCore { enum class RouteSharingPolicy : uint8_t; }
#endif
#if USE(AUDIO_SESSION)
namespace WebCore { enum class AudioSessionCategory : uint8_t; }
#endif
#if USE(AUDIO_SESSION)
namespace WebCore { enum class AudioSessionMode : uint8_t; }
#endif
#if USE(AUDIO_SESSION)
namespace WebCore { enum class AudioSessionRoutingArbitrationError : uint8_t; }
#endif
#if ENABLE(ENCRYPTED_MEDIA)
namespace WebCore { enum class CDMKeyStatus : uint8_t; }
#endif
#if ENABLE(ENCRYPTED_MEDIA)
namespace WebCore { enum class CDMMessageType : uint8_t; }
#endif
#if ENABLE(ENCRYPTED_MEDIA)
namespace WebCore { enum class CDMRequirement : uint8_t; }
#endif
#if ENABLE(WEB_RTC)
namespace WebCore { enum class RTCDataChannelState : uint8_t; }
#endif
#if ENABLE(WEB_RTC)
namespace WebCore { enum class RTCPriorityType : uint8_t; }
#endif
namespace WebCore { enum class LineCap : uint8_t; }
namespace WebCore { enum class LineJoin : uint8_t; }
namespace WebCore { enum class StrokeStyle : uint8_t; }
namespace WebCore { enum class TextDrawingMode : uint8_t; }
namespace WebCore { enum class DecodingMode : uint8_t; }
namespace WebCore { enum class DocumentMarkerLineStyleMode : uint8_t; }
namespace WebCore { enum class CrossOriginOpenerPolicyValue : uint8_t; }
namespace WebCore { enum class HTTPCookieAcceptPolicy : uint8_t; }
namespace WebCore { enum class NetworkLoadPriority : uint8_t; }
namespace WebCore { enum class PrivacyStance : uint8_t; }
namespace WebCore { enum class ThirdPartyCookieBlockingMode : uint8_t; }
namespace WebCore { enum class FirstPartyWebsiteDataRemovalMode : uint8_t; }
namespace WebCore { enum class DragApplicationFlags : uint8_t; }
namespace WebCore { enum class TextCheckingType : uint8_t; }
#if ENABLE(SERVICE_WORKER)
namespace WebCore { enum class ServiceWorkerClientType : uint8_t; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { enum class ServiceWorkerJobType : uint8_t; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { enum class ServiceWorkerRegistrationState : uint8_t; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { enum class ServiceWorkerState : uint8_t; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { enum class ServiceWorkerClientFrameType : uint8_t; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { enum class ShouldNotifyWhenResolved : bool; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { enum class ServiceWorkerUpdateViaCache : uint8_t; }
#endif
#if ENABLE(TRACKING_PREVENTION)
namespace WebCore { enum class StorageAccessWasGranted : bool; }
#endif
#if ENABLE(TRACKING_PREVENTION)
namespace WebCore { enum class StorageAccessPromptWasShown : bool; }
#endif
#if ENABLE(TRACKING_PREVENTION)
namespace WebCore { enum class StorageAccessScope : bool; }
#endif
#if ENABLE(TRACKING_PREVENTION)
namespace WebCore { enum class StorageAccessQuickResult : bool; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { enum class MediaConstraintType : uint8_t; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { enum class VideoFacingMode : uint8_t; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { enum class DisplaySurfaceType : uint8_t; }
#endif
namespace WebCore { enum class PlatformVideoColorPrimaries : uint8_t; }
namespace WebCore { enum class PlatformVideoTransferCharacteristics : uint8_t; }
namespace WebCore { enum class PlatformVideoMatrixCoefficients : uint8_t; }
namespace WebCore { enum class PolicyAction : uint8_t; }
namespace WebCore { enum class ReloadOption : uint8_t; }
namespace WebCore { enum class FrameLoadType : uint8_t; }
namespace WebCore { enum class NavigationType : uint8_t; }
namespace WebCore { enum class BrowsingContextGroupSwitchDecision : uint8_t; }
namespace WebCore { enum class ShouldOpenExternalURLsPolicy : uint8_t; }
namespace WebCore { enum class MouseEventPolicy : uint8_t; }
namespace WebCore { enum class ColorSchemePreference : uint8_t; }
namespace WebCore { enum class ModalContainerObservationPolicy : bool; }
namespace WebCore { enum class AllowsContentJavaScript : bool; }
namespace WebCore { enum class AdvancedPrivacyProtections : uint16_t; }
namespace WebCore { enum class ViolationReportType : uint8_t; }
namespace WebCore { enum class COEPDisposition : bool; }
namespace WebCore { enum class LinkIconType : uint8_t; }
namespace WebCore { enum class PluginLoadClientPolicy : uint8_t; }
namespace WebCore { enum class PasteboardItemPresentationStyle : uint8_t; }
#if HAVE(SCREEN_CAPTURE_KIT)
namespace WebCore { enum class DisplayCapturePromptType : uint8_t; }
#endif
namespace WebCore { enum class TextIndicatorPresentationTransition : uint8_t; }
namespace WebCore { enum class TextIndicatorOption : uint16_t; }
namespace WebCore { enum class StorageType : uint8_t; }
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
namespace WebCore { enum class AcceleratedEffectProperty : uint16_t; }
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
namespace WebCore { enum class WebAnimationType : uint8_t; }
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
namespace WebCore { enum class FillMode : uint8_t; }
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
namespace WebCore { enum class PlaybackDirection : uint8_t; }
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
namespace WebCore { enum class CompositeOperation : uint8_t; }
#endif
#if PLATFORM(MAC)
namespace WebCore { enum class CaretAnimatorType : uint8_t; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebCore::ShapeDetection { enum class BarcodeFormat : uint8_t; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebCore::ShapeDetection { enum class LandmarkType : uint8_t; }
#endif
namespace WebCore { enum class RenderAsTextFlag : uint16_t; }
namespace WebCore::WebGPU { enum class TextureFormat : uint8_t; }
#if ENABLE(MEDIA_STREAM)
namespace WebCore { enum class MediaAccessDenialReason : uint8_t; }
#endif
namespace WebCore::WebGPU { enum class TextureAspect : uint8_t; }
namespace WebCore::WebGPU { enum class PowerPreference : bool; }
namespace WebCore::WebGPU { enum class PredefinedColorSpace : uint8_t; }
namespace WebKit { enum class WebEventModifier : uint8_t; }
namespace WebKit { enum class WebEventType : int8_t; }
namespace WebKit { enum class WebMouseEventButton : int32_t; }
namespace WebKit { enum class WebMouseEventSyntheticClickType : uint8_t; }
namespace WebKit { enum class WebsiteMetaViewportPolicy : uint8_t; }
namespace WebKit { enum class WebsiteMediaSourcePolicy : uint8_t; }
namespace WebKit { enum class WebsiteSimulatedMouseEventsDispatchPolicy : uint8_t; }
namespace WebKit { enum class WebsiteLegacyOverflowScrollingTouchPolicy : uint8_t; }
#if ENABLE(WK_WEB_EXTENSIONS)
namespace WebKit { enum class WebExtensionEventListenerType : uint8_t; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebCore::WebGPU { enum class FeatureName : uint8_t; }
#endif
namespace WebKit { enum class WebsiteDataFetchOption : uint8_t; }
namespace WebKit { enum class WebsiteDataType : uint32_t; }
#if ENABLE(WEBXR)
namespace PlatformXR { enum class SessionFeature : uint8_t; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit { struct GPUProcessSessionParameters; }
#endif
namespace WebCore { struct PathMoveTo; }
namespace WebCore { struct PathLineTo; }
namespace WebCore { struct PathQuadCurveTo; }
namespace WebCore { struct PathBezierCurveTo; }
namespace WebCore { struct PathArcTo; }
namespace WebCore { struct PathArc; }
namespace WebCore { struct PathEllipse; }
namespace WebCore { struct PathEllipseInRect; }
namespace WebCore { struct PathRect; }
namespace WebCore { struct PathRoundedRect; }
namespace WebCore { struct PathDataLine; }
namespace WebCore { struct PathDataQuadCurve; }
namespace WebCore { struct PathDataBezierCurve; }
namespace WebCore { struct PathDataArc; }
namespace WebCore { struct PathCloseSubpath; }
namespace WebCore { class PathSegment; }
#if ENABLE(GPU_PROCESS)
namespace WebKit { struct RemoteRenderingBackendCreationParameters; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit { struct RemoteGPURequestAdapterResponse; }
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
namespace WebKit { struct AudioTrackPrivateRemoteConfiguration; }
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
namespace WebKit { struct InitializationSegmentInfo; }
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
namespace WebKit { struct MediaDescriptionInfo; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit { struct RemoteMediaPlayerProxyConfiguration; }
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
namespace WebKit { struct TextTrackPrivateRemoteConfiguration; }
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
namespace WebKit { struct TrackPrivateRemoteConfiguration; }
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
namespace WebKit { struct VideoTrackPrivateRemoteConfiguration; }
#endif
namespace WebKit { struct NetworkProcessCreationParameters; }
namespace WebKit { class NetworkLoadParameters; }
namespace WebKit { class NetworkResourceLoadParameters; }
namespace WebKit { class SharedMemoryHandle; }
#if ENABLE(SERVICE_WORKER)
namespace WebKit { struct BackgroundFetchState; }
#endif
namespace WebKit { class CallbackID; }
namespace WebCore::DisplayList { class SetState; }
namespace WebCore::DisplayList { class SetLineDash; }
namespace WebCore::DisplayList { class ClipOutToPath; }
namespace WebCore::DisplayList { class ClipPath; }
namespace WebCore::DisplayList { class DrawGlyphs; }
namespace WebCore::DisplayList { class DrawSystemImage; }
namespace WebCore::DisplayList { class DrawLinesForText; }
namespace WebCore::DisplayList { class DrawPath; }
namespace WebCore::DisplayList { class DrawFocusRingPath; }
namespace WebCore::DisplayList { class DrawFocusRingRects; }
namespace WebCore::DisplayList { class FillRectWithColor; }
namespace WebCore::DisplayList { class FillRectWithGradient; }
namespace WebCore::DisplayList { class FillCompositedRect; }
namespace WebCore::DisplayList { class FillRoundedRect; }
namespace WebCore::DisplayList { class FillRectWithRoundedHole; }
namespace WebCore::DisplayList { class FillPath; }
namespace WebCore::DisplayList { class StrokePath; }
namespace WebKit { struct EditorState; }
namespace WebKit { struct FileSystemSyncAccessHandleInfo; }
#if PLATFORM(IOS_FAMILY)
namespace WebKit { struct OptionItem; }
#endif
#if PLATFORM(IOS_FAMILY)
namespace WebKit { struct FocusedElementInformation; }
#endif
namespace WebKit { struct FrameInfoData; }
namespace WebKit { struct FrameTreeCreationParameters; }
namespace WebKit { struct FrameTreeNodeData; }
#if ENABLE(GPU_PROCESS)
namespace WebKit { struct GPUProcessConnectionParameters; }
#endif
namespace WebKit { class LayerTreeContext; }
namespace WebKit { struct LocalFrameCreationParameters; }
#if ENABLE(ARKIT_INLINE_PREVIEW)
namespace WebKit { struct ModelIdentifier; }
#endif
namespace WebKit { struct NavigationActionData; }
namespace WebKit { struct NetworkProcessConnectionParameters; }
namespace WebCore { struct PasteboardImage; }
namespace WebCore { struct PasteboardWebContent; }
namespace WebCore { struct PasteboardURL; }
namespace WebCore { struct PasteboardBuffer; }
namespace WebKit { struct PlatformPopupMenuData; }
namespace WebKit { struct PolicyDecision; }
namespace WebKit { struct HTTPBody; }
namespace WebKit { class FrameState; }
namespace WebKit { struct PageState; }
namespace WebKit { struct BackForwardListItemState; }
namespace WebKit { struct BackForwardListState; }
namespace WebKit { class ShareableBitmapConfiguration; }
namespace WebKit { class ShareableBitmapHandle; }
namespace WebKit { class ShareableBitmap; }
#if ENABLE(IMAGE_ANALYSIS)
namespace WebCore { struct TextRecognitionWordData; }
#endif
#if ENABLE(IMAGE_ANALYSIS)
namespace WebCore { struct TextRecognitionLineData; }
#endif
#if ENABLE(IMAGE_ANALYSIS)
namespace WebCore { struct TextRecognitionBlockData; }
#endif
#if ENABLE(IMAGE_ANALYSIS)
namespace WebCore { struct TextRecognitionResult; }
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
namespace WebKit { struct UpdateInfo; }
#endif
namespace WTF { class URL; }
namespace WTF { class MediaTime; }
namespace WTF { class Seconds; }
namespace WTF { class MonotonicTime; }
namespace WTF { class WallTime; }
namespace WTF { class AtomString; }
namespace WebCore::DOMCacheEngine { struct CacheInfo; }
namespace WebCore::DOMCacheEngine { struct CacheInfos; }
namespace WebCore::DOMCacheEngine { struct CacheIdentifierOperationResult; }
#if HAVE(TRANSLATION_UI_SERVICES) && ENABLE(CONTEXT_MENUS)
namespace WebCore { struct TranslationContextMenuInfo; }
#endif
namespace WebCore::DOMCacheEngine { struct CrossThreadRecord; }
namespace WebCore { class TransformationMatrix; }
namespace WebCore { struct CacheQueryOptions; }
namespace WebCore { struct CharacterRange; }
namespace WebCore { class AffineTransform; }
namespace WebCore { class FloatPoint; }
namespace WebCore { class FloatPoint3D; }
namespace WebCore { class FloatQuad; }
namespace WebCore { struct IDBCursorRecord; }
namespace WebCore { class IDBCursorInfo; }
namespace WebCore { class IDBError; }
namespace WebCore { struct IDBGetAllRecordsData; }
namespace WebCore { class IDBGetResult; }
namespace WebCore { class IDBGetAllResult; }
namespace WebCore { class IDBDatabaseInfo; }
namespace WebCore { struct IDBKeyRangeData; }
namespace WebCore { class IDBTransactionInfo; }
namespace WebCore { struct IDBGetRecordData; }
namespace WebCore { class IDBIndexInfo; }
namespace WebCore { class IDBObjectStoreInfo; }
namespace WebCore { struct IDBIterateCursorData; }
namespace WebCore { class IDBResourceIdentifier; }
namespace WebCore { class IDBValue; }
namespace WebCore { class IDBRequestData; }
namespace WebCore { class IDBDatabaseIdentifier; }
namespace WebCore { struct IDBDatabaseNameAndVersion; }
namespace WebCore { class IDBResultData; }
namespace WebCore { class IDBKeyData; }
#if USE(CG)
struct CGSize;
#endif
#if USE(CG)
struct CGPoint;
#endif
#if USE(CG)
struct CGRect;
#endif
#if USE(CG)
struct CGAffineTransform;
#endif
namespace WebCore { class FloatRect; }
namespace WebCore { class LinearTimingFunction; }
namespace WebCore { class CubicBezierTimingFunction; }
namespace WebCore { class StepsTimingFunction; }
namespace WebCore { class SpringTimingFunction; }
namespace WebCore { struct ResourceLoadStatistics; }
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
namespace WebCore { struct GraphicsContextGLActiveInfo; }
#endif
namespace WebCore { struct ViewportAttributes; }
namespace WebCore { struct ShareDataWithParsedURL; }
namespace WebCore { struct ShareData; }
namespace WebCore { struct RawFile; }
namespace WebCore { class FloatRoundedRect; }
namespace WebCore { class IntRect; }
namespace WebCore { class IntPoint; }
namespace WebCore { class IntSize; }
namespace WebCore { class FloatSize; }
namespace WebCore { class LayoutUnit; }
namespace WebCore { class LayoutPoint; }
namespace WebCore { class LayoutSize; }
namespace WebCore { struct DictionaryPopupInfo; }
namespace WebCore { class PrivateClickMeasurement; }
namespace WebCore::PCM { struct SourceSite; }
namespace WebCore::PCM { struct AttributionDestinationSite; }
namespace WebCore::PCM { struct EphemeralNonce; }
namespace WebCore::PCM { struct AttributionTriggerData; }
namespace WebCore::PCM { struct AttributionTimeToSendData; }
#if ENABLE(APPLE_PAY_RECURRING_PAYMENTS)
namespace WebCore { struct ApplePayRecurringPaymentRequest; }
#endif
#if ENABLE(APPLE_PAY_MULTI_MERCHANT_PAYMENTS)
namespace WebCore { struct ApplePayPaymentTokenContext; }
#endif
#if ENABLE(APPLE_PAY_DEFERRED_PAYMENTS)
namespace WebCore { struct ApplePayDeferredPaymentRequest; }
#endif
#if ENABLE(APPLE_PAY_PAYMENT_ORDER_DETAILS)
namespace WebCore { struct ApplePayPaymentOrderDetails; }
#endif
#if ENABLE(APPLE_PAY_AMS_UI) && ENABLE(PAYMENT_REQUEST)
namespace WebCore { struct ApplePayAMSUIRequest; }
#endif
#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_PAYMENTS)
namespace WebCore { struct ApplePayAutomaticReloadPaymentRequest; }
#endif
#if ENABLE(APPLE_PAY_SHIPPING_METHOD_DATE_COMPONENTS_RANGE)
namespace WebCore { struct ApplePayDateComponents; }
#endif
#if ENABLE(APPLE_PAY_SHIPPING_METHOD_DATE_COMPONENTS_RANGE)
namespace WebCore { struct ApplePayDateComponentsRange; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { struct ApplePaySetupConfiguration; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { struct ApplePayLineItem; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { struct ApplePayShippingMethod; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { class ApplePayError; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { class ApplePayLogoSystemImage; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { struct ApplePayDetailsUpdateBase; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { struct ApplePayPaymentMethodUpdate; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { struct ApplePayShippingContactUpdate; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { struct ApplePayShippingMethodUpdate; }
#endif
#if ENABLE(APPLE_PAY)
namespace WebCore { struct ApplePayPaymentAuthorizationResult; }
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
namespace WebCore { struct ApplePayInstallmentConfiguration; }
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
namespace WebCore { class PaymentInstallmentConfiguration; }
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
namespace WebCore { struct ApplePayInstallmentItem; }
#endif
#if ENABLE(APPLE_PAY_COUPON_CODE)
namespace WebCore { struct ApplePayCouponCodeUpdate; }
#endif
#if ENABLE(APPLICATION_MANIFEST)
namespace WebCore { struct ApplicationManifest; }
#endif
namespace WebCore { struct RetrieveRecordsOptions; }
namespace WebCore { struct ContactInfo; }
namespace WebCore { struct ContactsRequestData; }
#if ENABLE(MEDIA_SESSION)
namespace WebCore { struct MediaPositionState; }
#endif
#if ENABLE(WEB_RTC)
namespace WebCore { struct DetachedRTCDataChannel; }
#endif
#if ENABLE(WEB_CODECS)
namespace WebCore { struct WebCodecsEncodedVideoChunkData; }
#endif
namespace WebCore { struct HTMLModelElementCamera; }
namespace WebCore { struct NotificationData; }
namespace WebCore { struct PermissionDescriptor; }
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct PushSubscriptionData; }
#endif
namespace WebCore { class DeprecationReportBody; }
namespace WebCore { class Report; }
namespace WebCore { class TestReportBody; }
namespace WebCore { struct SpeechRecognitionError; }
namespace WebCore { struct SpeechRecognitionRequestInfo; }
namespace WebCore { struct SpeechRecognitionAlternativeData; }
namespace WebCore { struct SpeechRecognitionResultData; }
namespace WebCore { struct WebLockManagerSnapshot; }
#if ENABLE(WEB_AUTHN)
namespace WebCore { struct AuthenticationExtensionsClientInputs; }
#endif
#if ENABLE(WEB_AUTHN)
namespace WebCore { struct AuthenticationExtensionsClientOutputs; }
#endif
#if ENABLE(WEB_AUTHN)
namespace WebCore { struct PublicKeyCredentialDescriptor; }
#endif
namespace WebCore { struct PublicKeyCredentialCreationOptions; }
namespace WebCore { struct PublicKeyCredentialRequestOptions; }
namespace WebCore { class RegistrableDomain; }
namespace WebCore { struct AudioConfiguration; }
namespace WebCore { struct Cookie; }
#if ENABLE(VIDEO)
namespace WebCore { struct VideoFrameMetadata; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct NavigationPreloadState; }
#endif
#if ENABLE(CONTENT_FILTERING)
namespace WebCore { class MockContentFilterSettings; }
#endif
namespace WebCore { struct ExceptionDetails; }
namespace WebCore {
template<typename> class RectEdges;
using FloatBoxExtent = RectEdges<float>;
}
namespace WebCore::DisplayList { class SetInlineFillColor; }
namespace WebCore::DisplayList { class SetInlineStrokeColor; }
namespace WebCore { class HTTPHeaderMap; }
namespace WebCore { struct ElementContext; }
namespace WebCore { struct ElementAnimationContext; }
namespace WebCore { struct SystemPreviewInfo; }
#if USE(SOUP)
namespace WebCore { struct ResourceRequestPlatformData; }
#endif
#if PLATFORM(COCOA)
namespace WebCore { class ResourceRequest; }
#endif
#if USE(CURL)
namespace WebCore { class ResourceRequest; }
#endif
#if !USE(CURL) && !PLATFORM(COCOA)
namespace WebCore { class ResourceRequest; }
#endif
#if !USE(CG)
namespace WebCore { class PlatformColorSpace; }
#endif
namespace WebCore { class DestinationColorSpace; }
namespace WebCore { struct WindowFeatures; }
namespace WebCore { struct CompositionUnderline; }
namespace WebCore { struct FileChooserSettings; }
namespace WebCore { struct GrammarDetail; }
namespace WebCore { struct TextCheckingResult; }
namespace WebCore { class TextCheckingRequestData; }
namespace WebCore { class LayoutRect; }
namespace WebCore { struct ScreenDataOverrides; }
namespace WebCore { struct MediaCapabilitiesInfo; }
#if ENABLE(MEDIA_STREAM)
namespace WebCore { struct MediaStreamRequest; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { class MediaTrackConstraintSetMap; }
#endif
#if ! ENABLE(MEDIA_STREAM)
namespace WebCore { struct MediaStreamRequest; }
#endif
namespace WebCore { struct MediaCapabilitiesDecodingInfo; }
namespace WebCore { struct MediaCapabilitiesEncodingInfo; }
namespace WebCore { struct FormDataElement; }
namespace WebCore { struct NetworkTransactionInformation; }
namespace WebCore { class ContentType; }
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
namespace WebCore { struct DateTimeChooserParameters; }
#endif
namespace WebCore { struct ScreenData; }
namespace WebCore { struct ScreenProperties; }
namespace WebCore { class PlatformTimeRanges; }
#if ENABLE(VIDEO)
namespace WebCore { struct VideoPlaybackQualityMetrics; }
#endif
#if PLATFORM(IOS_FAMILY)
namespace WebCore { class SelectionGeometry; }
#endif
#if ENABLE(DATALIST_ELEMENT)
namespace WebCore { struct DataListSuggestion; }
#endif
#if ENABLE(DATALIST_ELEMENT)
namespace WebCore { struct DataListSuggestionInformation; }
#endif
namespace WebCore { struct ClientOrigin; }
namespace WebCore { struct PixelBufferFormat; }
namespace WebCore { class TextIndicator; }
namespace WebCore { class CertificateInfo; }
namespace WebCore { class PasteboardCustomData; }
namespace WebCore { class DatabaseDetails; }
namespace WebCore { class DecomposedGlyphs; }
namespace WebCore { struct TextIndicatorData; }
#if ENABLE(MEDIA_STREAM)
namespace WebCore { struct MediaConstraints; }
#endif
namespace WebCore { struct PromisedAttachmentInfo; }
namespace WebCore { struct RecentSearch; }
namespace WebCore { struct EventTrackingRegions; }
namespace WebCore { struct TextManipulationItem; }
namespace WebCore { struct TextManipulationToken; }
namespace WebCore { struct TextManipulationTokenInfo; }
namespace WebCore { struct VelocityData; }
namespace WebCore { struct MimeClassInfo; }
namespace WebCore { class AuthenticationChallenge; }
#if ENABLE(DRAG_SUPPORT)
namespace WebCore { class DragData; }
#endif
namespace WebCore { struct DictationAlternative; }
namespace WebCore { class UserStyleSheet; }
namespace WebCore { struct ScrollableAreaParameters; }
namespace WebCore { struct RequestedKeyboardScrollData; }
namespace WebCore { class AbsolutePositionConstraints; }
namespace WebCore { struct KeyboardScroll; }
namespace WebCore { class NotificationResources; }
namespace WebCore { class IdentityTransformOperation; }
namespace WebCore { class TranslateTransformOperation; }
namespace WebCore { class RotateTransformOperation; }
namespace WebCore { class ScaleTransformOperation; }
namespace WebCore { class SkewTransformOperation; }
namespace WebCore { class PerspectiveTransformOperation; }
namespace WebCore { class MatrixTransformOperation; }
namespace WebCore { class Matrix3DTransformOperation; }
namespace WebCore { class TransformOperations; }
namespace WebCore { class Gradient; }
namespace WebCore { class Pattern; }
namespace WebCore { class SourceBrush; }
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
namespace WebCore { struct GraphicsContextGLAttributes; }
#endif
namespace WebCore { class TimingFunction; }
namespace WebCore { class TransformOperation; }
namespace WebCore { struct LengthSize; }
namespace WebCore { class SVGPathByteStream; }
namespace WebCore { class BasicShapeCenterCoordinate; }
namespace WebCore { class BasicShapeRadius; }
namespace WebCore { class BasicShapeCircle; }
namespace WebCore { class BasicShapeEllipse; }
namespace WebCore { class BasicShapePolygon; }
namespace WebCore { class BasicShapePath; }
namespace WebCore { class BasicShapeInset; }
namespace WebCore { class BasicShape; }
namespace WebCore { class ReferencePathOperation; }
namespace WebCore { class ShapePathOperation; }
namespace WebCore { class BoxPathOperation; }
namespace WebCore { class RayPathOperation; }
namespace WebCore { class PathOperation; }
#if ENABLE(ENCRYPTED_MEDIA)
namespace WebCore { struct CDMKeySystemConfiguration; }
#endif
namespace WebCore { struct MediaConfiguration; }
namespace WebCore { struct MediaEncodingConfiguration; }
namespace WebCore { struct MediaDecodingConfiguration; }
namespace WebCore { class ResourceResponseBase; }
namespace WebCore { class ResourceResponse; }
namespace WebCore { struct FetchOptions; }
namespace WebCore { struct ControlStyle; }
#if ENABLE(APPLE_PAY)
namespace WebCore { class ApplePayButtonPart; }
#endif
namespace WebCore { class MeterPart; }
namespace WebCore { class ProgressBarPart; }
namespace WebCore { class SliderTrackPart; }
namespace WebCore { class DistantLightSource; }
namespace WebCore { class PointLightSource; }
namespace WebCore { class SpotLightSource; }
namespace WebCore { class FEBlend; }
namespace WebCore { class FEColorMatrix; }
namespace WebCore { struct ComponentTransferFunction; }
namespace WebCore { class FEComponentTransfer; }
namespace WebCore { class FEComposite; }
namespace WebCore { class FEConvolveMatrix; }
namespace WebCore { class FEDiffuseLighting; }
namespace WebCore { class FEDisplacementMap; }
namespace WebCore { class FEDropShadow; }
namespace WebCore { class FEFlood; }
namespace WebCore { class FEGaussianBlur; }
namespace WebCore { class FEImage; }
namespace WebCore { class FEMerge; }
namespace WebCore { class FEMorphology; }
namespace WebCore { class FEOffset; }
namespace WebCore { class FESpecularLighting; }
namespace WebCore { class FETurbulence; }
namespace WebCore { class FilterEffectGeometry; }
namespace WebCore { struct SVGFilterExpressionTerm; }
namespace WebCore { class SVGPreserveAspectRatioValue; }
#if ENABLE(GAMEPAD)
namespace WebCore { struct GamepadEffectParameters; }
#endif
namespace WebCore { struct StorageEstimate; }
namespace WebCore { struct ListStyleType; }
namespace WebCore { struct TextList; }
namespace WebCore { struct FontAttributes; }
namespace WebCore { struct CrossOriginEmbedderPolicy; }
namespace WebCore { struct SameSiteInfo; }
namespace WebCore { class SecurityOrigin; }
namespace WebCore { struct CookieRequestHeaderFieldProxy; }
namespace WebCore { class FormData; }
namespace WebCore { struct RequestedScrollData; }
namespace WebCore {
template<typename, typename> struct ScrollSnapOffsetsInfo;
using FloatScrollSnapOffsetsInfo = ScrollSnapOffsetsInfo<float, WebCore::FloatRect>;
}
namespace WebCore {
template<typename> struct SnapOffset;
using FloatSnapOffset = SnapOffset<float>;
}
#if ENABLE(ENCRYPTED_MEDIA)
namespace WebCore { struct CDMMediaCapability; }
#endif
#if ENABLE(ENCRYPTED_MEDIA)
namespace WebCore { struct CDMRestrictions; }
#endif
namespace WebCore { struct MediaSelectionOption; }
namespace WebCore { class BufferSource; }
namespace WebCore { struct FontShadow; }
namespace WebCore { struct CompositionHighlight; }
namespace WebCore { class FontChanges; }
namespace WebCore { class FontAttributeChanges; }
namespace WebCore { struct TextManipulationControllerExclusionRule; }
namespace WebCore { struct TextManipulationControllerManipulationFailure; }
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct BackgroundFetchInformation; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct BackgroundFetchRequest; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct BackgroundFetchRecordInformation; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct BackgroundFetchOptions; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct ImageResource; }
#endif
namespace WebCore { struct FourCC; }
#if ENABLE(VIDEO)
namespace WebCore { struct MediaEngineSupportParameters; }
#endif
namespace WebCore { class GeolocationPositionData; }
#if ENABLE(APP_HIGHLIGHTS)
namespace WebCore { struct AppHighlight; }
#endif
namespace WebCore { struct MediaDeviceHashSalts; }
namespace WebCore { class SpeechRecognitionUpdate; }
#if USE(SYSTEM_PREVIEW)
namespace WebCore { class ARKitBadgeSystemImage; }
#endif
namespace WebCore { struct AudioIOPosition; }
#if ENABLE(VIDEO) && USE(AVFOUNDATION)
namespace WebCore { class VideoFrameCV; }
#endif
namespace WebCore { struct GradientColorStop; }
namespace WebCore { class GradientColorStops; }
namespace WebCore { struct ImageBufferBackendParameters; }
namespace WebCore { class ProcessIdentity; }
namespace WebCore { struct ColorInterpolationMethod; }
namespace WebCore { struct CompositeMode; }
namespace WebCore { struct DocumentMarkerLineStyle; }
namespace WebCore { struct GraphicsDropShadow; }
#if ENABLE(VIDEO)
namespace WebCore { struct GenericCueData; }
#endif
namespace WebCore { struct ImageDecoderFrameInfo; }
namespace WebCore::DisplayList { class DrawDotsForDocumentMarker; }
namespace WebCore { struct ImageOrientation; }
namespace WebCore { struct ImagePaintingOptions; }
namespace WebCore { struct CanvasActivityRecord; }
namespace WebCore::PCM { struct AttributionSecondsUntilSendData; }
namespace WebCore { struct CrossOriginOpenerPolicy; }
namespace WebCore { struct CustomHeaderFields; }
namespace WebCore { class HTTPHeaderField; }
namespace WebCore { struct NavigationRequester; }
namespace WebCore { struct PolicyContainer; }
namespace WebCore { class SubstituteData; }
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct ServiceWorkerClientData; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct ServiceWorkerClientPendingMessage; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct ServiceWorkerClientQueryOptions; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct ServiceWorkerData; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct ServiceWorkerJobData; }
#endif
namespace WebCore { struct EventInit; }
namespace WebCore { struct MessageWithMessagePorts; }
#if ENABLE(TRACKING_PREVENTION)
namespace WebCore { struct RequestStorageAccessResult; }
#endif
namespace WebCore { class Exception; }
namespace WebCore { struct ExceptionData; }
namespace WebCore { struct MessagePortIdentifier; }
namespace WebCore { struct SecurityPolicyViolationEventInit; }
namespace WebCore { class CSPViolationReportBody; }
namespace WebCore { class SecurityOriginData; }
#if ENABLE(MEDIA_STREAM)
namespace WebCore { class MediaConstraint; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { class IntConstraint; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { class DoubleConstraint; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { class BooleanConstraint; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { class StringConstraint; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { struct FrameRateRange; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { struct VideoPresetData; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { class RealtimeMediaSourceSupportedConstraints; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { class RealtimeMediaSourceSettings; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { class CaptureDevice; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { struct CaptureDeviceWithCapabilities; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { class RealtimeMediaSourceCapabilities; }
#endif
namespace WebCore { struct PlatformVideoColorSpace; }
#if ENABLE(VIDEO)
namespace WebCore { struct PlatformTrackConfiguration; }
#endif
#if ENABLE(VIDEO)
namespace WebCore { struct PlatformAudioTrackConfiguration; }
#endif
#if ENABLE(VIDEO)
namespace WebCore { struct PlatformVideoTrackConfiguration; }
#endif
#if ENABLE(WEB_RTC)
namespace WebCore { struct RTCDataChannelInit; }
#endif
#if ENABLE(WEB_RTC)
namespace WebCore { struct RTCDataChannelIdentifier; }
#endif
#if ENABLE(CONTENT_EXTENSIONS)
namespace WebCore { struct ContentRuleListResults; }
#endif
namespace WebCore { class COEPInheritenceViolationReportBody; }
namespace WebCore { class CORPViolationReportBody; }
namespace WebCore { class ReportBody; }
namespace WebCore { class SourceImage; }
namespace WebCore { struct LinkIcon; }
namespace WebCore { struct SupportedPluginIdentifier; }
namespace WebCore { struct CSSValueKey; }
namespace WebCore { struct VideoFrameTimeMetadata; }
namespace WebCore { struct PositionedGlyphs; }
namespace WebCore { class EventRegion; }
namespace WebCore { struct PresentationSize; }
namespace WebCore { struct PasteboardItemInfo; }
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS) && USE(UICONTEXTMENU)
namespace WebCore { struct MediaControlsContextMenuItem; }
#endif
namespace WebCore { struct WorkerOptions; }
namespace WebCore { struct WorkerInitializationData; }
namespace WebCore { struct WorkerFetchResult; }
namespace WebCore { struct SharedWorkerKey; }
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct ServiceWorkerRegistrationOptions; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { class ServiceWorkerRegistrationKey; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct ServiceWorkerRegistrationData; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct ServiceWorkerJobDataIdentifier; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct ServiceWorkerImportedScript; }
#endif
#if ENABLE(SERVICE_WORKER)
namespace WebCore { struct ServiceWorkerContextData; }
#endif
namespace JSC { class ArrayBuffer; }
namespace WebCore { struct GlobalFrameIdentifier; }
namespace WebCore { struct GlobalWindowIdentifier; }
namespace WebCore { struct InteractionRegion; }
namespace WebCore { class Region; }
namespace WebCore { class ISOWebVTTCue; }
#if ENABLE(WEB_AUTHN)
namespace WebCore { struct MockWebAuthenticationConfiguration; }
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
namespace WebCore { struct LengthPoint; }
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
namespace WebCore { class OffsetRotation; }
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
namespace WebCore { struct AcceleratedEffectValues; }
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
namespace WebCore { struct AcceleratedEffectKeyframe; }
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
namespace WebCore { class AcceleratedEffect; }
#endif
namespace WebCore { class ProtectionSpace; }
#if ENABLE(GPU_PROCESS)
namespace WebCore::ShapeDetection { struct BarcodeDetectorOptions; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebCore::ShapeDetection { struct DetectedBarcode; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebCore::ShapeDetection { struct DetectedFace; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebCore::ShapeDetection { struct DetectedText; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebCore::ShapeDetection { struct FaceDetectorOptions; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebCore::ShapeDetection { struct Landmark; }
#endif
#if ENABLE(MEDIA_STREAM)
namespace WebCore { struct CaptureSourceError; }
#endif
namespace WebCore { struct CookieStoreGetOptions; }
namespace WebCore { class Model; }
namespace WebKit { class WebEvent; }
namespace WebKit { class WebKeyboardEvent; }
#if ENABLE(TOUCH_EVENTS)
namespace WebKit { class WebTouchEvent; }
#endif
#if ENABLE(TOUCH_EVENTS)
namespace WebKit { class WebPlatformTouchPoint; }
#endif
namespace WebKit { class WebMouseEvent; }
#if ENABLE(MAC_GESTURE_EVENTS)
namespace WebKit { class WebGestureEvent; }
#endif
namespace WebKit { class WebWheelEvent; }
namespace WebKit { struct WebHitTestResultData; }
namespace WebKit { struct WebPageCreationParameters; }
namespace WebKit { struct WebPopupItem; }
namespace WebKit { struct WebProcessCreationParameters; }
namespace WebKit { struct WebProcessDataStoreParameters; }
namespace WebKit::WebPushD { struct WebPushDaemonConnectionConfiguration; }
namespace WebKit { struct WebPushMessage; }
namespace WebKit { struct WebsiteDataStoreParameters; }
namespace WebKit { struct WebsitePoliciesData; }
namespace API { class Data; }
namespace API { class Error; }
namespace API { class FrameHandle; }
namespace API { class Size; }
namespace API { class Point; }
namespace API { class Rect; }
namespace API { class PageHandle; }
namespace API { class URL; }
namespace API { class URLRequest; }
namespace API { class URLResponse; }
namespace WebKit { class WebIDBResult; }
#if ENABLE(GAMEPAD)
namespace WebKit { class GamepadData; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct BindGroupDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct BindGroupEntry; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct BindGroupLayoutDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct BindGroupLayoutEntry; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct BlendComponent; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct BlendState; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct BufferBinding; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct BufferBindingLayout; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct BufferDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct CanvasConfiguration; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ColorDict; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ColorTargetState; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct CommandBufferDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct CommandEncoderDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct CompilationMessage; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ComputePassDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ComputePassTimestampWrite; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ComputePipelineDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct DepthStencilState; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct DeviceDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct Extent3DDict; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ExternalTextureBindingLayout; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebCore::WebGPU { struct HTMLVideoElementIdentifier; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebCore::WebGPU { struct WebCodecsVideoFrameIdentifier; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ExternalTextureDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct FragmentState; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ImageCopyBuffer; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ImageCopyExternalImage; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ImageCopyTexture; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ImageCopyTextureTagged; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ImageDataLayout; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct MultisampleState; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ObjectDescriptorBase; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct Origin2DDict; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct Origin3DDict; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct OutOfMemoryError; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct PipelineDescriptorBase; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct PipelineLayoutDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct PresentationContextDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct PrimitiveState; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ProgrammableStage; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct QuerySetDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct RenderBundleDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct RenderBundleEncoderDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct RenderPassColorAttachment; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct RenderPassDepthStencilAttachment; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct RenderPassDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct RenderPassLayout; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct RenderPassTimestampWrite; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct RenderPipelineDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct RequestAdapterOptions; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct SamplerBindingLayout; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct SamplerDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ShaderModuleCompilationHint; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ShaderModuleDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct StencilFaceState; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct StorageTextureBindingLayout; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct SupportedFeatures; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct SupportedLimits; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct TextureBindingLayout; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct TextureDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct TextureViewDescriptor; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct ValidationError; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct VertexAttribute; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct VertexBufferLayout; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit::WebGPU { struct VertexState; }
#endif
namespace WebKit { struct WebsiteData; }
#if ENABLE(GPU_PROCESS)
namespace WebKit { struct BufferIdentifierSet; }
#endif
#if ENABLE(GPU_PROCESS) && PLATFORM(COCOA)
namespace WebKit { struct PrepareBackingStoreBuffersInputData; }
#endif
#if ENABLE(GPU_PROCESS) && PLATFORM(COCOA)
namespace WebKit { struct PrepareBackingStoreBuffersOutputData; }
#endif
#if ENABLE(GPU_PROCESS) && USE(AUDIO_SESSION)
namespace WebKit { struct RemoteAudioSessionConfiguration; }
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)
namespace WebKit { struct RemoteCDMConfiguration; }
#endif
#if ENABLE(GPU_PROCESS)
namespace WebKit { struct RemoteMediaPlayerConfiguration; }
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
namespace WebKit { struct RemoteMediaPlayerState; }
#endif
#if ENABLE(SPEECH_SYNTHESIS)
namespace WebKit { struct WebSpeechSynthesisVoice; }
#endif

namespace IPC {

class Decoder;
class Encoder;
class StreamConnectionEncoder;

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::GPUProcessSessionParameters> {
    static void encode(Encoder&, const WebKit::GPUProcessSessionParameters&);
    static std::optional<WebKit::GPUProcessSessionParameters> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::PathMoveTo> {
    static void encode(Encoder&, const WebCore::PathMoveTo&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathMoveTo&);
    static std::optional<WebCore::PathMoveTo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathLineTo> {
    static void encode(Encoder&, const WebCore::PathLineTo&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathLineTo&);
    static std::optional<WebCore::PathLineTo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathQuadCurveTo> {
    static void encode(Encoder&, const WebCore::PathQuadCurveTo&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathQuadCurveTo&);
    static std::optional<WebCore::PathQuadCurveTo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathBezierCurveTo> {
    static void encode(Encoder&, const WebCore::PathBezierCurveTo&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathBezierCurveTo&);
    static std::optional<WebCore::PathBezierCurveTo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathArcTo> {
    static void encode(Encoder&, const WebCore::PathArcTo&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathArcTo&);
    static std::optional<WebCore::PathArcTo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathArc> {
    static void encode(Encoder&, const WebCore::PathArc&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathArc&);
    static std::optional<WebCore::PathArc> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathEllipse> {
    static void encode(Encoder&, const WebCore::PathEllipse&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathEllipse&);
    static std::optional<WebCore::PathEllipse> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathEllipseInRect> {
    static void encode(Encoder&, const WebCore::PathEllipseInRect&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathEllipseInRect&);
    static std::optional<WebCore::PathEllipseInRect> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathRect> {
    static void encode(Encoder&, const WebCore::PathRect&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathRect&);
    static std::optional<WebCore::PathRect> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathRoundedRect> {
    static void encode(Encoder&, const WebCore::PathRoundedRect&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathRoundedRect&);
    static std::optional<WebCore::PathRoundedRect> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathDataLine> {
    static void encode(Encoder&, const WebCore::PathDataLine&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathDataLine&);
    static std::optional<WebCore::PathDataLine> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathDataQuadCurve> {
    static void encode(Encoder&, const WebCore::PathDataQuadCurve&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathDataQuadCurve&);
    static std::optional<WebCore::PathDataQuadCurve> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathDataBezierCurve> {
    static void encode(Encoder&, const WebCore::PathDataBezierCurve&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathDataBezierCurve&);
    static std::optional<WebCore::PathDataBezierCurve> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathDataArc> {
    static void encode(Encoder&, const WebCore::PathDataArc&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathDataArc&);
    static std::optional<WebCore::PathDataArc> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathCloseSubpath> {
    static void encode(Encoder&, const WebCore::PathCloseSubpath&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathCloseSubpath&);
    static std::optional<WebCore::PathCloseSubpath> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathSegment> {
    static void encode(Encoder&, const WebCore::PathSegment&);
    static void encode(StreamConnectionEncoder&, const WebCore::PathSegment&);
    static std::optional<WebCore::PathSegment> decode(Decoder&);
};

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::RemoteRenderingBackendCreationParameters> {
    static void encode(Encoder&, const WebKit::RemoteRenderingBackendCreationParameters&);
    static std::optional<WebKit::RemoteRenderingBackendCreationParameters> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::RemoteGPURequestAdapterResponse> {
    static void encode(Encoder&, const WebKit::RemoteGPURequestAdapterResponse&);
    static void encode(StreamConnectionEncoder&, const WebKit::RemoteGPURequestAdapterResponse&);
    static std::optional<WebKit::RemoteGPURequestAdapterResponse> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
template<> struct ArgumentCoder<WebKit::AudioTrackPrivateRemoteConfiguration> {
    static void encode(Encoder&, const WebKit::AudioTrackPrivateRemoteConfiguration&);
    static std::optional<WebKit::AudioTrackPrivateRemoteConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
template<> struct ArgumentCoder<WebKit::InitializationSegmentInfo> {
    static void encode(Encoder&, const WebKit::InitializationSegmentInfo&);
    static std::optional<WebKit::InitializationSegmentInfo> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
template<> struct ArgumentCoder<WebKit::MediaDescriptionInfo> {
    static void encode(Encoder&, const WebKit::MediaDescriptionInfo&);
    static std::optional<WebKit::MediaDescriptionInfo> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::RemoteMediaPlayerProxyConfiguration> {
    static void encode(Encoder&, const WebKit::RemoteMediaPlayerProxyConfiguration&);
    static std::optional<WebKit::RemoteMediaPlayerProxyConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
template<> struct ArgumentCoder<WebKit::TextTrackPrivateRemoteConfiguration> {
    static void encode(Encoder&, const WebKit::TextTrackPrivateRemoteConfiguration&);
    static std::optional<WebKit::TextTrackPrivateRemoteConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
template<> struct ArgumentCoder<WebKit::TrackPrivateRemoteConfiguration> {
    static void encode(Encoder&, const WebKit::TrackPrivateRemoteConfiguration&);
    static std::optional<WebKit::TrackPrivateRemoteConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
template<> struct ArgumentCoder<WebKit::VideoTrackPrivateRemoteConfiguration> {
    static void encode(Encoder&, const WebKit::VideoTrackPrivateRemoteConfiguration&);
    static std::optional<WebKit::VideoTrackPrivateRemoteConfiguration> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebKit::NetworkProcessCreationParameters> {
    static void encode(Encoder&, const WebKit::NetworkProcessCreationParameters&);
    static std::optional<WebKit::NetworkProcessCreationParameters> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::NetworkLoadParameters> {
    static void encode(Encoder&, const WebKit::NetworkLoadParameters&);
    static std::optional<WebKit::NetworkLoadParameters> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::NetworkResourceLoadParameters> {
    static void encode(Encoder&, const WebKit::NetworkResourceLoadParameters&);
    static std::optional<WebKit::NetworkResourceLoadParameters> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::SharedMemoryHandle> {
    static void encode(Encoder&, WebKit::SharedMemoryHandle&&);
    static std::optional<WebKit::SharedMemoryHandle> decode(Decoder&);
};

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebKit::BackgroundFetchState> {
    static void encode(Encoder&, const WebKit::BackgroundFetchState&);
    static std::optional<WebKit::BackgroundFetchState> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebKit::CallbackID> {
    static void encode(Encoder&, const WebKit::CallbackID&);
    static std::optional<WebKit::CallbackID> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::SetState> {
    static void encode(Encoder&, const WebCore::DisplayList::SetState&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::SetState&);
    static std::optional<WebCore::DisplayList::SetState> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::SetLineDash> {
    static void encode(Encoder&, const WebCore::DisplayList::SetLineDash&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::SetLineDash&);
    static std::optional<WebCore::DisplayList::SetLineDash> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::ClipOutToPath> {
    static void encode(Encoder&, const WebCore::DisplayList::ClipOutToPath&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::ClipOutToPath&);
    static std::optional<WebCore::DisplayList::ClipOutToPath> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::ClipPath> {
    static void encode(Encoder&, const WebCore::DisplayList::ClipPath&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::ClipPath&);
    static std::optional<WebCore::DisplayList::ClipPath> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::DrawGlyphs> {
    static void encode(Encoder&, const WebCore::DisplayList::DrawGlyphs&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::DrawGlyphs&);
    static std::optional<WebCore::DisplayList::DrawGlyphs> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::DrawSystemImage> {
    static void encode(Encoder&, const WebCore::DisplayList::DrawSystemImage&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::DrawSystemImage&);
    static std::optional<WebCore::DisplayList::DrawSystemImage> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::DrawLinesForText> {
    static void encode(Encoder&, const WebCore::DisplayList::DrawLinesForText&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::DrawLinesForText&);
    static std::optional<WebCore::DisplayList::DrawLinesForText> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::DrawPath> {
    static void encode(Encoder&, const WebCore::DisplayList::DrawPath&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::DrawPath&);
    static std::optional<WebCore::DisplayList::DrawPath> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::DrawFocusRingPath> {
    static void encode(Encoder&, const WebCore::DisplayList::DrawFocusRingPath&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::DrawFocusRingPath&);
    static std::optional<WebCore::DisplayList::DrawFocusRingPath> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::DrawFocusRingRects> {
    static void encode(Encoder&, const WebCore::DisplayList::DrawFocusRingRects&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::DrawFocusRingRects&);
    static std::optional<WebCore::DisplayList::DrawFocusRingRects> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::FillRectWithColor> {
    static void encode(Encoder&, const WebCore::DisplayList::FillRectWithColor&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::FillRectWithColor&);
    static std::optional<WebCore::DisplayList::FillRectWithColor> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::FillRectWithGradient> {
    static void encode(Encoder&, const WebCore::DisplayList::FillRectWithGradient&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::FillRectWithGradient&);
    static std::optional<WebCore::DisplayList::FillRectWithGradient> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::FillCompositedRect> {
    static void encode(Encoder&, const WebCore::DisplayList::FillCompositedRect&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::FillCompositedRect&);
    static std::optional<WebCore::DisplayList::FillCompositedRect> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::FillRoundedRect> {
    static void encode(Encoder&, const WebCore::DisplayList::FillRoundedRect&);
    static std::optional<WebCore::DisplayList::FillRoundedRect> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::FillRectWithRoundedHole> {
    static void encode(Encoder&, const WebCore::DisplayList::FillRectWithRoundedHole&);
    static std::optional<WebCore::DisplayList::FillRectWithRoundedHole> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::FillPath> {
    static void encode(Encoder&, const WebCore::DisplayList::FillPath&);
    static std::optional<WebCore::DisplayList::FillPath> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::StrokePath> {
    static void encode(Encoder&, const WebCore::DisplayList::StrokePath&);
    static std::optional<WebCore::DisplayList::StrokePath> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::EditorState> {
    static void encode(Encoder&, const WebKit::EditorState&);
    static std::optional<WebKit::EditorState> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::FileSystemSyncAccessHandleInfo> {
    static void encode(Encoder&, const WebKit::FileSystemSyncAccessHandleInfo&);
    static std::optional<WebKit::FileSystemSyncAccessHandleInfo> decode(Decoder&);
};

#if PLATFORM(IOS_FAMILY)
template<> struct ArgumentCoder<WebKit::OptionItem> {
    static void encode(Encoder&, const WebKit::OptionItem&);
    static std::optional<WebKit::OptionItem> decode(Decoder&);
};
#endif

#if PLATFORM(IOS_FAMILY)
template<> struct ArgumentCoder<WebKit::FocusedElementInformation> {
    static void encode(Encoder&, const WebKit::FocusedElementInformation&);
    static std::optional<WebKit::FocusedElementInformation> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebKit::FrameInfoData> {
    static void encode(Encoder&, const WebKit::FrameInfoData&);
    static std::optional<WebKit::FrameInfoData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::FrameTreeCreationParameters> {
    static void encode(Encoder&, const WebKit::FrameTreeCreationParameters&);
    static std::optional<WebKit::FrameTreeCreationParameters> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::FrameTreeNodeData> {
    static void encode(Encoder&, const WebKit::FrameTreeNodeData&);
    static std::optional<WebKit::FrameTreeNodeData> decode(Decoder&);
};

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::GPUProcessConnectionParameters> {
    static void encode(Encoder&, WebKit::GPUProcessConnectionParameters&&);
    static std::optional<WebKit::GPUProcessConnectionParameters> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebKit::LayerTreeContext> {
    static void encode(Encoder&, const WebKit::LayerTreeContext&);
    static std::optional<WebKit::LayerTreeContext> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::LocalFrameCreationParameters> {
    static void encode(Encoder&, const WebKit::LocalFrameCreationParameters&);
    static std::optional<WebKit::LocalFrameCreationParameters> decode(Decoder&);
};

#if ENABLE(ARKIT_INLINE_PREVIEW)
template<> struct ArgumentCoder<WebKit::ModelIdentifier> {
    static void encode(Encoder&, const WebKit::ModelIdentifier&);
    static std::optional<WebKit::ModelIdentifier> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebKit::NavigationActionData> {
    static void encode(Encoder&, const WebKit::NavigationActionData&);
    static std::optional<WebKit::NavigationActionData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::NetworkProcessConnectionParameters> {
    static void encode(Encoder&, const WebKit::NetworkProcessConnectionParameters&);
    static std::optional<WebKit::NetworkProcessConnectionParameters> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PasteboardImage> {
    static void encode(Encoder&, const WebCore::PasteboardImage&);
    static std::optional<WebCore::PasteboardImage> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PasteboardWebContent> {
    static void encode(Encoder&, const WebCore::PasteboardWebContent&);
    static std::optional<WebCore::PasteboardWebContent> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PasteboardURL> {
    static void encode(Encoder&, const WebCore::PasteboardURL&);
    static std::optional<WebCore::PasteboardURL> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PasteboardBuffer> {
    static void encode(Encoder&, const WebCore::PasteboardBuffer&);
    static std::optional<WebCore::PasteboardBuffer> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::PlatformPopupMenuData> {
    static void encode(Encoder&, const WebKit::PlatformPopupMenuData&);
    static std::optional<WebKit::PlatformPopupMenuData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::PolicyDecision> {
    static void encode(Encoder&, const WebKit::PolicyDecision&);
    static std::optional<WebKit::PolicyDecision> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::HTTPBody> {
    static void encode(Encoder&, const WebKit::HTTPBody&);
    static std::optional<WebKit::HTTPBody> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::FrameState> {
    static void encode(Encoder&, const WebKit::FrameState&);
    static std::optional<WebKit::FrameState> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::PageState> {
    static void encode(Encoder&, const WebKit::PageState&);
    static std::optional<WebKit::PageState> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::BackForwardListItemState> {
    static void encode(Encoder&, const WebKit::BackForwardListItemState&);
    static std::optional<WebKit::BackForwardListItemState> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::BackForwardListState> {
    static void encode(Encoder&, const WebKit::BackForwardListState&);
    static std::optional<WebKit::BackForwardListState> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::ShareableBitmapConfiguration> {
    static void encode(Encoder&, const WebKit::ShareableBitmapConfiguration&);
    static std::optional<WebKit::ShareableBitmapConfiguration> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::ShareableBitmapHandle> {
    static void encode(Encoder&, WebKit::ShareableBitmapHandle&&);
    static std::optional<WebKit::ShareableBitmapHandle> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::ShareableBitmap> {
    static void encode(Encoder&, const WebKit::ShareableBitmap&);
    static std::optional<Ref<WebKit::ShareableBitmap>> decode(Decoder&);
};

#if ENABLE(IMAGE_ANALYSIS)
template<> struct ArgumentCoder<WebCore::TextRecognitionWordData> {
    static void encode(Encoder&, const WebCore::TextRecognitionWordData&);
    static std::optional<WebCore::TextRecognitionWordData> decode(Decoder&);
};
#endif

#if ENABLE(IMAGE_ANALYSIS)
template<> struct ArgumentCoder<WebCore::TextRecognitionLineData> {
    static void encode(Encoder&, const WebCore::TextRecognitionLineData&);
    static std::optional<WebCore::TextRecognitionLineData> decode(Decoder&);
};
#endif

#if ENABLE(IMAGE_ANALYSIS)
template<> struct ArgumentCoder<WebCore::TextRecognitionBlockData> {
    static void encode(Encoder&, const WebCore::TextRecognitionBlockData&);
    static std::optional<WebCore::TextRecognitionBlockData> decode(Decoder&);
};
#endif

#if ENABLE(IMAGE_ANALYSIS)
template<> struct ArgumentCoder<WebCore::TextRecognitionResult> {
    static void encode(Encoder&, const WebCore::TextRecognitionResult&);
    static std::optional<WebCore::TextRecognitionResult> decode(Decoder&);
};
#endif

#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
template<> struct ArgumentCoder<WebKit::UpdateInfo> {
    static void encode(Encoder&, WebKit::UpdateInfo&&);
    static std::optional<WebKit::UpdateInfo> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WTF::URL> {
    static void encode(Encoder&, const WTF::URL&);
    static std::optional<WTF::URL> decode(Decoder&);
};

template<> struct ArgumentCoder<WTF::MediaTime> {
    static void encode(Encoder&, const WTF::MediaTime&);
    static void encode(StreamConnectionEncoder&, const WTF::MediaTime&);
    static std::optional<WTF::MediaTime> decode(Decoder&);
};

template<> struct ArgumentCoder<WTF::Seconds> {
    static void encode(Encoder&, const WTF::Seconds&);
    static void encode(StreamConnectionEncoder&, const WTF::Seconds&);
    static std::optional<WTF::Seconds> decode(Decoder&);
};

template<> struct ArgumentCoder<WTF::MonotonicTime> {
    static void encode(Encoder&, const WTF::MonotonicTime&);
    static std::optional<WTF::MonotonicTime> decode(Decoder&);
};

template<> struct ArgumentCoder<WTF::WallTime> {
    static void encode(Encoder&, const WTF::WallTime&);
    static std::optional<WTF::WallTime> decode(Decoder&);
};

template<> struct ArgumentCoder<WTF::AtomString> {
    static void encode(Encoder&, const WTF::AtomString&);
    static void encode(StreamConnectionEncoder&, const WTF::AtomString&);
    static std::optional<WTF::AtomString> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DOMCacheEngine::CacheInfo> {
    static void encode(Encoder&, const WebCore::DOMCacheEngine::CacheInfo&);
    static std::optional<WebCore::DOMCacheEngine::CacheInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DOMCacheEngine::CacheInfos> {
    static void encode(Encoder&, const WebCore::DOMCacheEngine::CacheInfos&);
    static std::optional<WebCore::DOMCacheEngine::CacheInfos> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DOMCacheEngine::CacheIdentifierOperationResult> {
    static void encode(Encoder&, const WebCore::DOMCacheEngine::CacheIdentifierOperationResult&);
    static std::optional<WebCore::DOMCacheEngine::CacheIdentifierOperationResult> decode(Decoder&);
};

#if HAVE(TRANSLATION_UI_SERVICES) && ENABLE(CONTEXT_MENUS)
template<> struct ArgumentCoder<WebCore::TranslationContextMenuInfo> {
    static void encode(Encoder&, const WebCore::TranslationContextMenuInfo&);
    static std::optional<WebCore::TranslationContextMenuInfo> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::DOMCacheEngine::CrossThreadRecord> {
    static void encode(Encoder&, const WebCore::DOMCacheEngine::CrossThreadRecord&);
    static std::optional<WebCore::DOMCacheEngine::CrossThreadRecord> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TransformationMatrix> {
    static void encode(Encoder&, const WebCore::TransformationMatrix&);
    static void encode(StreamConnectionEncoder&, const WebCore::TransformationMatrix&);
    static std::optional<WebCore::TransformationMatrix> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CacheQueryOptions> {
    static void encode(Encoder&, const WebCore::CacheQueryOptions&);
    static std::optional<WebCore::CacheQueryOptions> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CharacterRange> {
    static void encode(Encoder&, const WebCore::CharacterRange&);
    static std::optional<WebCore::CharacterRange> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::AffineTransform> {
    static void encode(Encoder&, const WebCore::AffineTransform&);
    static void encode(StreamConnectionEncoder&, const WebCore::AffineTransform&);
    static std::optional<WebCore::AffineTransform> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FloatPoint> {
    static void encode(Encoder&, const WebCore::FloatPoint&);
    static void encode(StreamConnectionEncoder&, const WebCore::FloatPoint&);
    static std::optional<WebCore::FloatPoint> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FloatPoint3D> {
    static void encode(Encoder&, const WebCore::FloatPoint3D&);
    static void encode(StreamConnectionEncoder&, const WebCore::FloatPoint3D&);
    static std::optional<WebCore::FloatPoint3D> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FloatQuad> {
    static void encode(Encoder&, const WebCore::FloatQuad&);
    static std::optional<WebCore::FloatQuad> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBCursorRecord> {
    static void encode(Encoder&, const WebCore::IDBCursorRecord&);
    static std::optional<WebCore::IDBCursorRecord> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBCursorInfo> {
    static void encode(Encoder&, const WebCore::IDBCursorInfo&);
    static std::optional<WebCore::IDBCursorInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBError> {
    static void encode(Encoder&, const WebCore::IDBError&);
    static std::optional<WebCore::IDBError> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBGetAllRecordsData> {
    static void encode(Encoder&, const WebCore::IDBGetAllRecordsData&);
    static std::optional<WebCore::IDBGetAllRecordsData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBGetResult> {
    static void encode(Encoder&, const WebCore::IDBGetResult&);
    static std::optional<WebCore::IDBGetResult> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBGetAllResult> {
    static void encode(Encoder&, const WebCore::IDBGetAllResult&);
    static std::optional<WebCore::IDBGetAllResult> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBDatabaseInfo> {
    static void encode(Encoder&, const WebCore::IDBDatabaseInfo&);
    static std::optional<WebCore::IDBDatabaseInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBKeyRangeData> {
    static void encode(Encoder&, const WebCore::IDBKeyRangeData&);
    static std::optional<WebCore::IDBKeyRangeData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBTransactionInfo> {
    static void encode(Encoder&, const WebCore::IDBTransactionInfo&);
    static std::optional<WebCore::IDBTransactionInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBGetRecordData> {
    static void encode(Encoder&, const WebCore::IDBGetRecordData&);
    static std::optional<WebCore::IDBGetRecordData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBIndexInfo> {
    static void encode(Encoder&, const WebCore::IDBIndexInfo&);
    static std::optional<WebCore::IDBIndexInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBObjectStoreInfo> {
    static void encode(Encoder&, const WebCore::IDBObjectStoreInfo&);
    static std::optional<WebCore::IDBObjectStoreInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBIterateCursorData> {
    static void encode(Encoder&, const WebCore::IDBIterateCursorData&);
    static std::optional<WebCore::IDBIterateCursorData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBResourceIdentifier> {
    static void encode(Encoder&, const WebCore::IDBResourceIdentifier&);
    static std::optional<WebCore::IDBResourceIdentifier> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBValue> {
    static void encode(Encoder&, const WebCore::IDBValue&);
    static std::optional<WebCore::IDBValue> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBRequestData> {
    static void encode(Encoder&, const WebCore::IDBRequestData&);
    static std::optional<WebCore::IDBRequestData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBDatabaseIdentifier> {
    static void encode(Encoder&, const WebCore::IDBDatabaseIdentifier&);
    static std::optional<WebCore::IDBDatabaseIdentifier> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBDatabaseNameAndVersion> {
    static void encode(Encoder&, const WebCore::IDBDatabaseNameAndVersion&);
    static std::optional<WebCore::IDBDatabaseNameAndVersion> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBResultData> {
    static void encode(Encoder&, const WebCore::IDBResultData&);
    static std::optional<WebCore::IDBResultData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IDBKeyData> {
    static void encode(Encoder&, const WebCore::IDBKeyData&);
    static std::optional<WebCore::IDBKeyData> decode(Decoder&);
};

#if USE(CG)
template<> struct ArgumentCoder<CGSize> {
    static void encode(Encoder&, const CGSize&);
    static void encode(StreamConnectionEncoder&, const CGSize&);
    static std::optional<CGSize> decode(Decoder&);
};
#endif

#if USE(CG)
template<> struct ArgumentCoder<CGPoint> {
    static void encode(Encoder&, const CGPoint&);
    static std::optional<CGPoint> decode(Decoder&);
};
#endif

#if USE(CG)
template<> struct ArgumentCoder<CGRect> {
    static void encode(Encoder&, const CGRect&);
    static std::optional<CGRect> decode(Decoder&);
};
#endif

#if USE(CG)
template<> struct ArgumentCoder<CGAffineTransform> {
    static void encode(Encoder&, const CGAffineTransform&);
    static std::optional<CGAffineTransform> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::FloatRect> {
    static void encode(Encoder&, const WebCore::FloatRect&);
    static void encode(StreamConnectionEncoder&, const WebCore::FloatRect&);
    static std::optional<WebCore::FloatRect> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::LinearTimingFunction> {
    static void encode(Encoder&, const WebCore::LinearTimingFunction&);
    static std::optional<Ref<WebCore::LinearTimingFunction>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CubicBezierTimingFunction> {
    static void encode(Encoder&, const WebCore::CubicBezierTimingFunction&);
    static std::optional<Ref<WebCore::CubicBezierTimingFunction>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::StepsTimingFunction> {
    static void encode(Encoder&, const WebCore::StepsTimingFunction&);
    static std::optional<Ref<WebCore::StepsTimingFunction>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SpringTimingFunction> {
    static void encode(Encoder&, const WebCore::SpringTimingFunction&);
    static std::optional<Ref<WebCore::SpringTimingFunction>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ResourceLoadStatistics> {
    static void encode(Encoder&, const WebCore::ResourceLoadStatistics&);
    static std::optional<WebCore::ResourceLoadStatistics> decode(Decoder&);
};

#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
template<> struct ArgumentCoder<WebCore::GraphicsContextGLActiveInfo> {
    static void encode(Encoder&, const WebCore::GraphicsContextGLActiveInfo&);
    static void encode(StreamConnectionEncoder&, const WebCore::GraphicsContextGLActiveInfo&);
    static std::optional<WebCore::GraphicsContextGLActiveInfo> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::ViewportAttributes> {
    static void encode(Encoder&, const WebCore::ViewportAttributes&);
    static std::optional<WebCore::ViewportAttributes> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ShareDataWithParsedURL> {
    static void encode(Encoder&, const WebCore::ShareDataWithParsedURL&);
    static std::optional<WebCore::ShareDataWithParsedURL> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ShareData> {
    static void encode(Encoder&, const WebCore::ShareData&);
    static std::optional<WebCore::ShareData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::RawFile> {
    static void encode(Encoder&, const WebCore::RawFile&);
    static std::optional<WebCore::RawFile> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FloatRoundedRect> {
    static void encode(Encoder&, const WebCore::FloatRoundedRect&);
    static void encode(StreamConnectionEncoder&, const WebCore::FloatRoundedRect&);
    static std::optional<WebCore::FloatRoundedRect> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IntRect> {
    static void encode(Encoder&, const WebCore::IntRect&);
    static void encode(StreamConnectionEncoder&, const WebCore::IntRect&);
    static std::optional<WebCore::IntRect> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IntPoint> {
    static void encode(Encoder&, const WebCore::IntPoint&);
    static void encode(StreamConnectionEncoder&, const WebCore::IntPoint&);
    static std::optional<WebCore::IntPoint> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IntSize> {
    static void encode(Encoder&, const WebCore::IntSize&);
    static void encode(StreamConnectionEncoder&, const WebCore::IntSize&);
    static std::optional<WebCore::IntSize> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FloatSize> {
    static void encode(Encoder&, const WebCore::FloatSize&);
    static void encode(StreamConnectionEncoder&, const WebCore::FloatSize&);
    static std::optional<WebCore::FloatSize> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::LayoutUnit> {
    static void encode(Encoder&, const WebCore::LayoutUnit&);
    static void encode(StreamConnectionEncoder&, const WebCore::LayoutUnit&);
    static std::optional<WebCore::LayoutUnit> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::LayoutPoint> {
    static void encode(Encoder&, const WebCore::LayoutPoint&);
    static void encode(StreamConnectionEncoder&, const WebCore::LayoutPoint&);
    static std::optional<WebCore::LayoutPoint> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::LayoutSize> {
    static void encode(Encoder&, const WebCore::LayoutSize&);
    static void encode(StreamConnectionEncoder&, const WebCore::LayoutSize&);
    static std::optional<WebCore::LayoutSize> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DictionaryPopupInfo> {
    static void encode(Encoder&, const WebCore::DictionaryPopupInfo&);
    static std::optional<WebCore::DictionaryPopupInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PrivateClickMeasurement> {
    static void encode(Encoder&, const WebCore::PrivateClickMeasurement&);
    static std::optional<WebCore::PrivateClickMeasurement> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PCM::SourceSite> {
    static void encode(Encoder&, const WebCore::PCM::SourceSite&);
    static std::optional<WebCore::PCM::SourceSite> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PCM::AttributionDestinationSite> {
    static void encode(Encoder&, const WebCore::PCM::AttributionDestinationSite&);
    static std::optional<WebCore::PCM::AttributionDestinationSite> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PCM::EphemeralNonce> {
    static void encode(Encoder&, const WebCore::PCM::EphemeralNonce&);
    static std::optional<WebCore::PCM::EphemeralNonce> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PCM::AttributionTriggerData> {
    static void encode(Encoder&, const WebCore::PCM::AttributionTriggerData&);
    static std::optional<WebCore::PCM::AttributionTriggerData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PCM::AttributionTimeToSendData> {
    static void encode(Encoder&, const WebCore::PCM::AttributionTimeToSendData&);
    static std::optional<WebCore::PCM::AttributionTimeToSendData> decode(Decoder&);
};

#if ENABLE(APPLE_PAY_RECURRING_PAYMENTS)
template<> struct ArgumentCoder<WebCore::ApplePayRecurringPaymentRequest> {
    static void encode(Encoder&, const WebCore::ApplePayRecurringPaymentRequest&);
    static std::optional<WebCore::ApplePayRecurringPaymentRequest> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY_MULTI_MERCHANT_PAYMENTS)
template<> struct ArgumentCoder<WebCore::ApplePayPaymentTokenContext> {
    static void encode(Encoder&, const WebCore::ApplePayPaymentTokenContext&);
    static std::optional<WebCore::ApplePayPaymentTokenContext> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY_DEFERRED_PAYMENTS)
template<> struct ArgumentCoder<WebCore::ApplePayDeferredPaymentRequest> {
    static void encode(Encoder&, const WebCore::ApplePayDeferredPaymentRequest&);
    static std::optional<WebCore::ApplePayDeferredPaymentRequest> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY_PAYMENT_ORDER_DETAILS)
template<> struct ArgumentCoder<WebCore::ApplePayPaymentOrderDetails> {
    static void encode(Encoder&, const WebCore::ApplePayPaymentOrderDetails&);
    static std::optional<WebCore::ApplePayPaymentOrderDetails> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY_AMS_UI) && ENABLE(PAYMENT_REQUEST)
template<> struct ArgumentCoder<WebCore::ApplePayAMSUIRequest> {
    static void encode(Encoder&, const WebCore::ApplePayAMSUIRequest&);
    static std::optional<WebCore::ApplePayAMSUIRequest> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_PAYMENTS)
template<> struct ArgumentCoder<WebCore::ApplePayAutomaticReloadPaymentRequest> {
    static void encode(Encoder&, const WebCore::ApplePayAutomaticReloadPaymentRequest&);
    static std::optional<WebCore::ApplePayAutomaticReloadPaymentRequest> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY_SHIPPING_METHOD_DATE_COMPONENTS_RANGE)
template<> struct ArgumentCoder<WebCore::ApplePayDateComponents> {
    static void encode(Encoder&, const WebCore::ApplePayDateComponents&);
    static std::optional<WebCore::ApplePayDateComponents> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY_SHIPPING_METHOD_DATE_COMPONENTS_RANGE)
template<> struct ArgumentCoder<WebCore::ApplePayDateComponentsRange> {
    static void encode(Encoder&, const WebCore::ApplePayDateComponentsRange&);
    static std::optional<WebCore::ApplePayDateComponentsRange> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY)
template<> struct ArgumentCoder<WebCore::ApplePaySetupConfiguration> {
    static void encode(Encoder&, const WebCore::ApplePaySetupConfiguration&);
    static std::optional<WebCore::ApplePaySetupConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY)
template<> struct ArgumentCoder<WebCore::ApplePayLineItem> {
    static void encode(Encoder&, const WebCore::ApplePayLineItem&);
    static std::optional<WebCore::ApplePayLineItem> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY)
template<> struct ArgumentCoder<WebCore::ApplePayShippingMethod> {
    static void encode(Encoder&, const WebCore::ApplePayShippingMethod&);
    static std::optional<WebCore::ApplePayShippingMethod> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY)
template<> struct ArgumentCoder<WebCore::ApplePayError> {
    static void encode(Encoder&, const WebCore::ApplePayError&);
    static std::optional<Ref<WebCore::ApplePayError>> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY)
template<> struct ArgumentCoder<WebCore::ApplePayLogoSystemImage> {
    static void encode(Encoder&, const WebCore::ApplePayLogoSystemImage&);
    static void encode(StreamConnectionEncoder&, const WebCore::ApplePayLogoSystemImage&);
    static std::optional<Ref<WebCore::ApplePayLogoSystemImage>> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY)
template<> struct ArgumentCoder<WebCore::ApplePayDetailsUpdateBase> {
    static void encode(Encoder&, const WebCore::ApplePayDetailsUpdateBase&);
    static std::optional<WebCore::ApplePayDetailsUpdateBase> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY)
template<> struct ArgumentCoder<WebCore::ApplePayPaymentMethodUpdate> {
    static void encode(Encoder&, const WebCore::ApplePayPaymentMethodUpdate&);
    static std::optional<WebCore::ApplePayPaymentMethodUpdate> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY)
template<> struct ArgumentCoder<WebCore::ApplePayShippingContactUpdate> {
    static void encode(Encoder&, const WebCore::ApplePayShippingContactUpdate&);
    static std::optional<WebCore::ApplePayShippingContactUpdate> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY)
template<> struct ArgumentCoder<WebCore::ApplePayShippingMethodUpdate> {
    static void encode(Encoder&, const WebCore::ApplePayShippingMethodUpdate&);
    static std::optional<WebCore::ApplePayShippingMethodUpdate> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY)
template<> struct ArgumentCoder<WebCore::ApplePayPaymentAuthorizationResult> {
    static void encode(Encoder&, const WebCore::ApplePayPaymentAuthorizationResult&);
    static std::optional<WebCore::ApplePayPaymentAuthorizationResult> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY_INSTALLMENTS)
template<> struct ArgumentCoder<WebCore::ApplePayInstallmentConfiguration> {
    static void encode(Encoder&, const WebCore::ApplePayInstallmentConfiguration&);
    static std::optional<WebCore::ApplePayInstallmentConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY_INSTALLMENTS)
template<> struct ArgumentCoder<WebCore::PaymentInstallmentConfiguration> {
    static void encode(Encoder&, const WebCore::PaymentInstallmentConfiguration&);
    static std::optional<WebCore::PaymentInstallmentConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY_INSTALLMENTS)
template<> struct ArgumentCoder<WebCore::ApplePayInstallmentItem> {
    static void encode(Encoder&, const WebCore::ApplePayInstallmentItem&);
    static std::optional<WebCore::ApplePayInstallmentItem> decode(Decoder&);
};
#endif

#if ENABLE(APPLE_PAY_COUPON_CODE)
template<> struct ArgumentCoder<WebCore::ApplePayCouponCodeUpdate> {
    static void encode(Encoder&, const WebCore::ApplePayCouponCodeUpdate&);
    static std::optional<WebCore::ApplePayCouponCodeUpdate> decode(Decoder&);
};
#endif

#if ENABLE(APPLICATION_MANIFEST)
template<> struct ArgumentCoder<WebCore::ApplicationManifest> {
    static void encode(Encoder&, const WebCore::ApplicationManifest&);
    static std::optional<WebCore::ApplicationManifest> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::RetrieveRecordsOptions> {
    static void encode(Encoder&, const WebCore::RetrieveRecordsOptions&);
    static std::optional<WebCore::RetrieveRecordsOptions> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ContactInfo> {
    static void encode(Encoder&, const WebCore::ContactInfo&);
    static std::optional<WebCore::ContactInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ContactsRequestData> {
    static void encode(Encoder&, const WebCore::ContactsRequestData&);
    static std::optional<WebCore::ContactsRequestData> decode(Decoder&);
};

#if ENABLE(MEDIA_SESSION)
template<> struct ArgumentCoder<WebCore::MediaPositionState> {
    static void encode(Encoder&, const WebCore::MediaPositionState&);
    static std::optional<WebCore::MediaPositionState> decode(Decoder&);
};
#endif

#if ENABLE(WEB_RTC)
template<> struct ArgumentCoder<WebCore::DetachedRTCDataChannel> {
    static void encode(Encoder&, const WebCore::DetachedRTCDataChannel&);
    static std::optional<WebCore::DetachedRTCDataChannel> decode(Decoder&);
};
#endif

#if ENABLE(WEB_CODECS)
template<> struct ArgumentCoder<WebCore::WebCodecsEncodedVideoChunkData> {
    static void encode(Encoder&, const WebCore::WebCodecsEncodedVideoChunkData&);
    static std::optional<WebCore::WebCodecsEncodedVideoChunkData> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::HTMLModelElementCamera> {
    static void encode(Encoder&, const WebCore::HTMLModelElementCamera&);
    static std::optional<WebCore::HTMLModelElementCamera> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::NotificationData> {
    static void encode(Encoder&, const WebCore::NotificationData&);
    static std::optional<WebCore::NotificationData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PermissionDescriptor> {
    static void encode(Encoder&, const WebCore::PermissionDescriptor&);
    static std::optional<WebCore::PermissionDescriptor> decode(Decoder&);
};

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::PushSubscriptionData> {
    static void encode(Encoder&, const WebCore::PushSubscriptionData&);
    static std::optional<WebCore::PushSubscriptionData> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::DeprecationReportBody> {
    static void encode(Encoder&, const WebCore::DeprecationReportBody&);
    static std::optional<Ref<WebCore::DeprecationReportBody>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::Report> {
    static void encode(Encoder&, const WebCore::Report&);
    static std::optional<Ref<WebCore::Report>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TestReportBody> {
    static void encode(Encoder&, const WebCore::TestReportBody&);
    static std::optional<Ref<WebCore::TestReportBody>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SpeechRecognitionError> {
    static void encode(Encoder&, const WebCore::SpeechRecognitionError&);
    static std::optional<WebCore::SpeechRecognitionError> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SpeechRecognitionRequestInfo> {
    static void encode(Encoder&, const WebCore::SpeechRecognitionRequestInfo&);
    static std::optional<WebCore::SpeechRecognitionRequestInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SpeechRecognitionAlternativeData> {
    static void encode(Encoder&, const WebCore::SpeechRecognitionAlternativeData&);
    static std::optional<WebCore::SpeechRecognitionAlternativeData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SpeechRecognitionResultData> {
    static void encode(Encoder&, const WebCore::SpeechRecognitionResultData&);
    static std::optional<WebCore::SpeechRecognitionResultData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::WebLockManagerSnapshot> {
    static void encode(Encoder&, const WebCore::WebLockManagerSnapshot&);
    static std::optional<WebCore::WebLockManagerSnapshot> decode(Decoder&);
};

#if ENABLE(WEB_AUTHN)
template<> struct ArgumentCoder<WebCore::AuthenticationExtensionsClientInputs> {
    static void encode(Encoder&, const WebCore::AuthenticationExtensionsClientInputs&);
    static std::optional<WebCore::AuthenticationExtensionsClientInputs> decode(Decoder&);
};
#endif

#if ENABLE(WEB_AUTHN)
template<> struct ArgumentCoder<WebCore::AuthenticationExtensionsClientOutputs> {
    static void encode(Encoder&, const WebCore::AuthenticationExtensionsClientOutputs&);
    static std::optional<WebCore::AuthenticationExtensionsClientOutputs> decode(Decoder&);
};
#endif

#if ENABLE(WEB_AUTHN)
template<> struct ArgumentCoder<WebCore::PublicKeyCredentialDescriptor> {
    static void encode(Encoder&, const WebCore::PublicKeyCredentialDescriptor&);
    static std::optional<WebCore::PublicKeyCredentialDescriptor> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::PublicKeyCredentialCreationOptions> {
    static void encode(Encoder&, const WebCore::PublicKeyCredentialCreationOptions&);
    static std::optional<WebCore::PublicKeyCredentialCreationOptions> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PublicKeyCredentialRequestOptions> {
    static void encode(Encoder&, const WebCore::PublicKeyCredentialRequestOptions&);
    static std::optional<WebCore::PublicKeyCredentialRequestOptions> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::RegistrableDomain> {
    static void encode(Encoder&, const WebCore::RegistrableDomain&);
    static std::optional<WebCore::RegistrableDomain> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::AudioConfiguration> {
    static void encode(Encoder&, const WebCore::AudioConfiguration&);
    static std::optional<WebCore::AudioConfiguration> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::Cookie> {
    static void encode(Encoder&, const WebCore::Cookie&);
    static std::optional<WebCore::Cookie> decode(Decoder&);
};

#if ENABLE(VIDEO)
template<> struct ArgumentCoder<WebCore::VideoFrameMetadata> {
    static void encode(Encoder&, const WebCore::VideoFrameMetadata&);
    static std::optional<WebCore::VideoFrameMetadata> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::NavigationPreloadState> {
    static void encode(Encoder&, const WebCore::NavigationPreloadState&);
    static std::optional<WebCore::NavigationPreloadState> decode(Decoder&);
};
#endif

#if ENABLE(CONTENT_FILTERING)
template<> struct ArgumentCoder<WebCore::MockContentFilterSettings> {
    static void encode(Encoder&, const WebCore::MockContentFilterSettings&);
    static std::optional<WebCore::MockContentFilterSettings> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::ExceptionDetails> {
    static void encode(Encoder&, const WebCore::ExceptionDetails&);
    static std::optional<WebCore::ExceptionDetails> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FloatBoxExtent> {
    static void encode(Encoder&, const WebCore::FloatBoxExtent&);
    static void encode(StreamConnectionEncoder&, const WebCore::FloatBoxExtent&);
    static std::optional<WebCore::FloatBoxExtent> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::SetInlineFillColor> {
    static void encode(Encoder&, const WebCore::DisplayList::SetInlineFillColor&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::SetInlineFillColor&);
    static std::optional<WebCore::DisplayList::SetInlineFillColor> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::SetInlineStrokeColor> {
    static void encode(Encoder&, const WebCore::DisplayList::SetInlineStrokeColor&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::SetInlineStrokeColor&);
    static std::optional<WebCore::DisplayList::SetInlineStrokeColor> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::HTTPHeaderMap> {
    static void encode(Encoder&, const WebCore::HTTPHeaderMap&);
    static std::optional<WebCore::HTTPHeaderMap> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ElementContext> {
    static void encode(Encoder&, const WebCore::ElementContext&);
    static std::optional<WebCore::ElementContext> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ElementAnimationContext> {
    static void encode(Encoder&, const WebCore::ElementAnimationContext&);
    static std::optional<WebCore::ElementAnimationContext> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SystemPreviewInfo> {
    static void encode(Encoder&, const WebCore::SystemPreviewInfo&);
    static std::optional<WebCore::SystemPreviewInfo> decode(Decoder&);
};

#if USE(SOUP)
template<> struct ArgumentCoder<WebCore::ResourceRequestPlatformData> {
    static void encode(Encoder&, const WebCore::ResourceRequestPlatformData&);
    static std::optional<WebCore::ResourceRequestPlatformData> decode(Decoder&);
};
#endif

#if PLATFORM(COCOA)
template<> struct ArgumentCoder<WebCore::ResourceRequest> {
    static void encode(Encoder&, const WebCore::ResourceRequest&);
    static std::optional<WebCore::ResourceRequest> decode(Decoder&);
};
#endif

#if USE(CURL)
template<> struct ArgumentCoder<WebCore::ResourceRequest> {
    static void encode(Encoder&, const WebCore::ResourceRequest&);
    static std::optional<WebCore::ResourceRequest> decode(Decoder&);
};
#endif

#if !USE(CURL) && !PLATFORM(COCOA)
template<> struct ArgumentCoder<WebCore::ResourceRequest> {
    static void encode(Encoder&, const WebCore::ResourceRequest&);
    static std::optional<WebCore::ResourceRequest> decode(Decoder&);
};
#endif

#if !USE(CG)
template<> struct ArgumentCoder<WebCore::PlatformColorSpace> {
    static void encode(Encoder&, const WebCore::PlatformColorSpace&);
    static void encode(StreamConnectionEncoder&, const WebCore::PlatformColorSpace&);
    static std::optional<WebCore::PlatformColorSpace> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::DestinationColorSpace> {
    static void encode(Encoder&, const WebCore::DestinationColorSpace&);
    static void encode(StreamConnectionEncoder&, const WebCore::DestinationColorSpace&);
    static std::optional<WebCore::DestinationColorSpace> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::WindowFeatures> {
    static void encode(Encoder&, const WebCore::WindowFeatures&);
    static std::optional<WebCore::WindowFeatures> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CompositionUnderline> {
    static void encode(Encoder&, const WebCore::CompositionUnderline&);
    static std::optional<WebCore::CompositionUnderline> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FileChooserSettings> {
    static void encode(Encoder&, const WebCore::FileChooserSettings&);
    static std::optional<WebCore::FileChooserSettings> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::GrammarDetail> {
    static void encode(Encoder&, const WebCore::GrammarDetail&);
    static std::optional<WebCore::GrammarDetail> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TextCheckingResult> {
    static void encode(Encoder&, const WebCore::TextCheckingResult&);
    static std::optional<WebCore::TextCheckingResult> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TextCheckingRequestData> {
    static void encode(Encoder&, const WebCore::TextCheckingRequestData&);
    static std::optional<WebCore::TextCheckingRequestData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::LayoutRect> {
    static void encode(Encoder&, const WebCore::LayoutRect&);
    static std::optional<WebCore::LayoutRect> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ScreenDataOverrides> {
    static void encode(Encoder&, const WebCore::ScreenDataOverrides&);
    static std::optional<WebCore::ScreenDataOverrides> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::MediaCapabilitiesInfo> {
    static void encode(Encoder&, const WebCore::MediaCapabilitiesInfo&);
    static std::optional<WebCore::MediaCapabilitiesInfo> decode(Decoder&);
};

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::MediaStreamRequest> {
    static void encode(Encoder&, const WebCore::MediaStreamRequest&);
    static std::optional<WebCore::MediaStreamRequest> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::MediaTrackConstraintSetMap> {
    static void encode(Encoder&, const WebCore::MediaTrackConstraintSetMap&);
    static std::optional<WebCore::MediaTrackConstraintSetMap> decode(Decoder&);
};
#endif

#if ! ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::MediaStreamRequest> {
    static void encode(Encoder&, const WebCore::MediaStreamRequest&);
    static std::optional<WebCore::MediaStreamRequest> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::MediaCapabilitiesDecodingInfo> {
    static void encode(Encoder&, const WebCore::MediaCapabilitiesDecodingInfo&);
    static std::optional<WebCore::MediaCapabilitiesDecodingInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::MediaCapabilitiesEncodingInfo> {
    static void encode(Encoder&, const WebCore::MediaCapabilitiesEncodingInfo&);
    static std::optional<WebCore::MediaCapabilitiesEncodingInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FormDataElement> {
    static void encode(Encoder&, const WebCore::FormDataElement&);
    static std::optional<WebCore::FormDataElement> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::NetworkTransactionInformation> {
    static void encode(Encoder&, const WebCore::NetworkTransactionInformation&);
    static std::optional<WebCore::NetworkTransactionInformation> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ContentType> {
    static void encode(Encoder&, const WebCore::ContentType&);
    static std::optional<WebCore::ContentType> decode(Decoder&);
};

#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
template<> struct ArgumentCoder<WebCore::DateTimeChooserParameters> {
    static void encode(Encoder&, const WebCore::DateTimeChooserParameters&);
    static std::optional<WebCore::DateTimeChooserParameters> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::ScreenData> {
    static void encode(Encoder&, const WebCore::ScreenData&);
    static std::optional<WebCore::ScreenData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ScreenProperties> {
    static void encode(Encoder&, const WebCore::ScreenProperties&);
    static std::optional<WebCore::ScreenProperties> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PlatformTimeRanges> {
    static void encode(Encoder&, const WebCore::PlatformTimeRanges&);
    static std::optional<WebCore::PlatformTimeRanges> decode(Decoder&);
};

#if ENABLE(VIDEO)
template<> struct ArgumentCoder<WebCore::VideoPlaybackQualityMetrics> {
    static void encode(Encoder&, const WebCore::VideoPlaybackQualityMetrics&);
    static std::optional<WebCore::VideoPlaybackQualityMetrics> decode(Decoder&);
};
#endif

#if PLATFORM(IOS_FAMILY)
template<> struct ArgumentCoder<WebCore::SelectionGeometry> {
    static void encode(Encoder&, const WebCore::SelectionGeometry&);
    static std::optional<WebCore::SelectionGeometry> decode(Decoder&);
};
#endif

#if ENABLE(DATALIST_ELEMENT)
template<> struct ArgumentCoder<WebCore::DataListSuggestion> {
    static void encode(Encoder&, const WebCore::DataListSuggestion&);
    static std::optional<WebCore::DataListSuggestion> decode(Decoder&);
};
#endif

#if ENABLE(DATALIST_ELEMENT)
template<> struct ArgumentCoder<WebCore::DataListSuggestionInformation> {
    static void encode(Encoder&, const WebCore::DataListSuggestionInformation&);
    static std::optional<WebCore::DataListSuggestionInformation> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::ClientOrigin> {
    static void encode(Encoder&, const WebCore::ClientOrigin&);
    static std::optional<WebCore::ClientOrigin> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PixelBufferFormat> {
    static void encode(Encoder&, const WebCore::PixelBufferFormat&);
    static void encode(StreamConnectionEncoder&, const WebCore::PixelBufferFormat&);
    static std::optional<WebCore::PixelBufferFormat> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TextIndicator> {
    static void encode(Encoder&, const WebCore::TextIndicator&);
    static std::optional<Ref<WebCore::TextIndicator>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CertificateInfo> {
    static void encode(Encoder&, const WebCore::CertificateInfo&);
    static std::optional<WebCore::CertificateInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PasteboardCustomData> {
    static void encode(Encoder&, const WebCore::PasteboardCustomData&);
    static std::optional<WebCore::PasteboardCustomData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DatabaseDetails> {
    static void encode(Encoder&, const WebCore::DatabaseDetails&);
    static std::optional<WebCore::DatabaseDetails> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DecomposedGlyphs> {
    static void encode(Encoder&, const WebCore::DecomposedGlyphs&);
    static std::optional<Ref<WebCore::DecomposedGlyphs>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TextIndicatorData> {
    static void encode(Encoder&, const WebCore::TextIndicatorData&);
    static std::optional<WebCore::TextIndicatorData> decode(Decoder&);
};

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::MediaConstraints> {
    static void encode(Encoder&, const WebCore::MediaConstraints&);
    static std::optional<WebCore::MediaConstraints> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::PromisedAttachmentInfo> {
    static void encode(Encoder&, const WebCore::PromisedAttachmentInfo&);
    static std::optional<WebCore::PromisedAttachmentInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::RecentSearch> {
    static void encode(Encoder&, const WebCore::RecentSearch&);
    static std::optional<WebCore::RecentSearch> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::EventTrackingRegions> {
    static void encode(Encoder&, const WebCore::EventTrackingRegions&);
    static std::optional<WebCore::EventTrackingRegions> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TextManipulationItem> {
    static void encode(Encoder&, const WebCore::TextManipulationItem&);
    static std::optional<WebCore::TextManipulationItem> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TextManipulationToken> {
    static void encode(Encoder&, const WebCore::TextManipulationToken&);
    static std::optional<WebCore::TextManipulationToken> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TextManipulationTokenInfo> {
    static void encode(Encoder&, const WebCore::TextManipulationTokenInfo&);
    static std::optional<WebCore::TextManipulationTokenInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::VelocityData> {
    static void encode(Encoder&, const WebCore::VelocityData&);
    static std::optional<WebCore::VelocityData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::MimeClassInfo> {
    static void encode(Encoder&, const WebCore::MimeClassInfo&);
    static std::optional<WebCore::MimeClassInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::AuthenticationChallenge> {
    static void encode(Encoder&, const WebCore::AuthenticationChallenge&);
    static std::optional<WebCore::AuthenticationChallenge> decode(Decoder&);
};

#if ENABLE(DRAG_SUPPORT)
template<> struct ArgumentCoder<WebCore::DragData> {
    static void encode(Encoder&, const WebCore::DragData&);
    static std::optional<WebCore::DragData> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::DictationAlternative> {
    static void encode(Encoder&, const WebCore::DictationAlternative&);
    static std::optional<WebCore::DictationAlternative> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::UserStyleSheet> {
    static void encode(Encoder&, const WebCore::UserStyleSheet&);
    static std::optional<WebCore::UserStyleSheet> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ScrollableAreaParameters> {
    static void encode(Encoder&, const WebCore::ScrollableAreaParameters&);
    static std::optional<WebCore::ScrollableAreaParameters> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::RequestedKeyboardScrollData> {
    static void encode(Encoder&, const WebCore::RequestedKeyboardScrollData&);
    static std::optional<WebCore::RequestedKeyboardScrollData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::AbsolutePositionConstraints> {
    static void encode(Encoder&, const WebCore::AbsolutePositionConstraints&);
    static std::optional<WebCore::AbsolutePositionConstraints> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::KeyboardScroll> {
    static void encode(Encoder&, const WebCore::KeyboardScroll&);
    static std::optional<WebCore::KeyboardScroll> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::NotificationResources> {
    static void encode(Encoder&, const WebCore::NotificationResources&);
    static std::optional<Ref<WebCore::NotificationResources>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::IdentityTransformOperation> {
    static void encode(Encoder&, const WebCore::IdentityTransformOperation&);
    static std::optional<Ref<WebCore::IdentityTransformOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TranslateTransformOperation> {
    static void encode(Encoder&, const WebCore::TranslateTransformOperation&);
    static std::optional<Ref<WebCore::TranslateTransformOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::RotateTransformOperation> {
    static void encode(Encoder&, const WebCore::RotateTransformOperation&);
    static std::optional<Ref<WebCore::RotateTransformOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ScaleTransformOperation> {
    static void encode(Encoder&, const WebCore::ScaleTransformOperation&);
    static std::optional<Ref<WebCore::ScaleTransformOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SkewTransformOperation> {
    static void encode(Encoder&, const WebCore::SkewTransformOperation&);
    static std::optional<Ref<WebCore::SkewTransformOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PerspectiveTransformOperation> {
    static void encode(Encoder&, const WebCore::PerspectiveTransformOperation&);
    static std::optional<Ref<WebCore::PerspectiveTransformOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::MatrixTransformOperation> {
    static void encode(Encoder&, const WebCore::MatrixTransformOperation&);
    static std::optional<Ref<WebCore::MatrixTransformOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::Matrix3DTransformOperation> {
    static void encode(Encoder&, const WebCore::Matrix3DTransformOperation&);
    static std::optional<Ref<WebCore::Matrix3DTransformOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TransformOperations> {
    static void encode(Encoder&, const WebCore::TransformOperations&);
    static std::optional<WebCore::TransformOperations> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::Gradient> {
    static void encode(Encoder&, const WebCore::Gradient&);
    static void encode(StreamConnectionEncoder&, const WebCore::Gradient&);
    static std::optional<Ref<WebCore::Gradient>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::Pattern> {
    static void encode(Encoder&, const WebCore::Pattern&);
    static void encode(StreamConnectionEncoder&, const WebCore::Pattern&);
    static std::optional<Ref<WebCore::Pattern>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SourceBrush> {
    static void encode(Encoder&, const WebCore::SourceBrush&);
    static void encode(StreamConnectionEncoder&, const WebCore::SourceBrush&);
    static std::optional<WebCore::SourceBrush> decode(Decoder&);
};

#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
template<> struct ArgumentCoder<WebCore::GraphicsContextGLAttributes> {
    static void encode(Encoder&, const WebCore::GraphicsContextGLAttributes&);
    static std::optional<WebCore::GraphicsContextGLAttributes> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::TimingFunction> {
    static void encode(Encoder&, const WebCore::TimingFunction&);
    static std::optional<Ref<WebCore::TimingFunction>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TransformOperation> {
    static void encode(Encoder&, const WebCore::TransformOperation&);
    static std::optional<Ref<WebCore::TransformOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::LengthSize> {
    static void encode(Encoder&, const WebCore::LengthSize&);
    static std::optional<WebCore::LengthSize> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SVGPathByteStream> {
    static void encode(Encoder&, const WebCore::SVGPathByteStream&);
    static std::optional<WebCore::SVGPathByteStream> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::BasicShapeCenterCoordinate> {
    static void encode(Encoder&, const WebCore::BasicShapeCenterCoordinate&);
    static std::optional<WebCore::BasicShapeCenterCoordinate> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::BasicShapeRadius> {
    static void encode(Encoder&, const WebCore::BasicShapeRadius&);
    static std::optional<WebCore::BasicShapeRadius> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::BasicShapeCircle> {
    static void encode(Encoder&, const WebCore::BasicShapeCircle&);
    static std::optional<Ref<WebCore::BasicShapeCircle>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::BasicShapeEllipse> {
    static void encode(Encoder&, const WebCore::BasicShapeEllipse&);
    static std::optional<Ref<WebCore::BasicShapeEllipse>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::BasicShapePolygon> {
    static void encode(Encoder&, const WebCore::BasicShapePolygon&);
    static std::optional<Ref<WebCore::BasicShapePolygon>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::BasicShapePath> {
    static void encode(Encoder&, const WebCore::BasicShapePath&);
    static std::optional<Ref<WebCore::BasicShapePath>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::BasicShapeInset> {
    static void encode(Encoder&, const WebCore::BasicShapeInset&);
    static std::optional<Ref<WebCore::BasicShapeInset>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::BasicShape> {
    static void encode(Encoder&, const WebCore::BasicShape&);
    static std::optional<Ref<WebCore::BasicShape>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ReferencePathOperation> {
    static void encode(Encoder&, const WebCore::ReferencePathOperation&);
    static std::optional<Ref<WebCore::ReferencePathOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ShapePathOperation> {
    static void encode(Encoder&, const WebCore::ShapePathOperation&);
    static std::optional<Ref<WebCore::ShapePathOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::BoxPathOperation> {
    static void encode(Encoder&, const WebCore::BoxPathOperation&);
    static std::optional<Ref<WebCore::BoxPathOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::RayPathOperation> {
    static void encode(Encoder&, const WebCore::RayPathOperation&);
    static std::optional<Ref<WebCore::RayPathOperation>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PathOperation> {
    static void encode(Encoder&, const WebCore::PathOperation&);
    static std::optional<Ref<WebCore::PathOperation>> decode(Decoder&);
};

#if ENABLE(ENCRYPTED_MEDIA)
template<> struct ArgumentCoder<WebCore::CDMKeySystemConfiguration> {
    static void encode(Encoder&, const WebCore::CDMKeySystemConfiguration&);
    static std::optional<WebCore::CDMKeySystemConfiguration> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::MediaConfiguration> {
    static void encode(Encoder&, const WebCore::MediaConfiguration&);
    static std::optional<WebCore::MediaConfiguration> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::MediaEncodingConfiguration> {
    static void encode(Encoder&, const WebCore::MediaEncodingConfiguration&);
    static std::optional<WebCore::MediaEncodingConfiguration> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::MediaDecodingConfiguration> {
    static void encode(Encoder&, const WebCore::MediaDecodingConfiguration&);
    static std::optional<WebCore::MediaDecodingConfiguration> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ResourceResponseBase> {
    static void encode(Encoder&, const WebCore::ResourceResponseBase&);
    static std::optional<WebCore::ResourceResponseBase> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ResourceResponse> {
    static void encode(Encoder&, const WebCore::ResourceResponse&);
    static std::optional<WebCore::ResourceResponse> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FetchOptions> {
    static void encode(Encoder&, const WebCore::FetchOptions&);
    static std::optional<WebCore::FetchOptions> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ControlStyle> {
    static void encode(Encoder&, const WebCore::ControlStyle&);
    static void encode(StreamConnectionEncoder&, const WebCore::ControlStyle&);
    static std::optional<WebCore::ControlStyle> decode(Decoder&);
};

#if ENABLE(APPLE_PAY)
template<> struct ArgumentCoder<WebCore::ApplePayButtonPart> {
    static void encode(Encoder&, const WebCore::ApplePayButtonPart&);
    static void encode(StreamConnectionEncoder&, const WebCore::ApplePayButtonPart&);
    static std::optional<Ref<WebCore::ApplePayButtonPart>> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::MeterPart> {
    static void encode(Encoder&, const WebCore::MeterPart&);
    static void encode(StreamConnectionEncoder&, const WebCore::MeterPart&);
    static std::optional<Ref<WebCore::MeterPart>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ProgressBarPart> {
    static void encode(Encoder&, const WebCore::ProgressBarPart&);
    static void encode(StreamConnectionEncoder&, const WebCore::ProgressBarPart&);
    static std::optional<Ref<WebCore::ProgressBarPart>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SliderTrackPart> {
    static void encode(Encoder&, const WebCore::SliderTrackPart&);
    static void encode(StreamConnectionEncoder&, const WebCore::SliderTrackPart&);
    static std::optional<Ref<WebCore::SliderTrackPart>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DistantLightSource> {
    static void encode(Encoder&, const WebCore::DistantLightSource&);
    static void encode(StreamConnectionEncoder&, const WebCore::DistantLightSource&);
    static std::optional<Ref<WebCore::DistantLightSource>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PointLightSource> {
    static void encode(Encoder&, const WebCore::PointLightSource&);
    static void encode(StreamConnectionEncoder&, const WebCore::PointLightSource&);
    static std::optional<Ref<WebCore::PointLightSource>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SpotLightSource> {
    static void encode(Encoder&, const WebCore::SpotLightSource&);
    static void encode(StreamConnectionEncoder&, const WebCore::SpotLightSource&);
    static std::optional<Ref<WebCore::SpotLightSource>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEBlend> {
    static void encode(Encoder&, const WebCore::FEBlend&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEBlend&);
    static std::optional<Ref<WebCore::FEBlend>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEColorMatrix> {
    static void encode(Encoder&, const WebCore::FEColorMatrix&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEColorMatrix&);
    static std::optional<Ref<WebCore::FEColorMatrix>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ComponentTransferFunction> {
    static void encode(Encoder&, const WebCore::ComponentTransferFunction&);
    static void encode(StreamConnectionEncoder&, const WebCore::ComponentTransferFunction&);
    static std::optional<WebCore::ComponentTransferFunction> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEComponentTransfer> {
    static void encode(Encoder&, const WebCore::FEComponentTransfer&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEComponentTransfer&);
    static std::optional<Ref<WebCore::FEComponentTransfer>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEComposite> {
    static void encode(Encoder&, const WebCore::FEComposite&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEComposite&);
    static std::optional<Ref<WebCore::FEComposite>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEConvolveMatrix> {
    static void encode(Encoder&, const WebCore::FEConvolveMatrix&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEConvolveMatrix&);
    static std::optional<Ref<WebCore::FEConvolveMatrix>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEDiffuseLighting> {
    static void encode(Encoder&, const WebCore::FEDiffuseLighting&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEDiffuseLighting&);
    static std::optional<Ref<WebCore::FEDiffuseLighting>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEDisplacementMap> {
    static void encode(Encoder&, const WebCore::FEDisplacementMap&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEDisplacementMap&);
    static std::optional<Ref<WebCore::FEDisplacementMap>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEDropShadow> {
    static void encode(Encoder&, const WebCore::FEDropShadow&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEDropShadow&);
    static std::optional<Ref<WebCore::FEDropShadow>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEFlood> {
    static void encode(Encoder&, const WebCore::FEFlood&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEFlood&);
    static std::optional<Ref<WebCore::FEFlood>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEGaussianBlur> {
    static void encode(Encoder&, const WebCore::FEGaussianBlur&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEGaussianBlur&);
    static std::optional<Ref<WebCore::FEGaussianBlur>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEImage> {
    static void encode(Encoder&, const WebCore::FEImage&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEImage&);
    static std::optional<Ref<WebCore::FEImage>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEMerge> {
    static void encode(Encoder&, const WebCore::FEMerge&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEMerge&);
    static std::optional<Ref<WebCore::FEMerge>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEMorphology> {
    static void encode(Encoder&, const WebCore::FEMorphology&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEMorphology&);
    static std::optional<Ref<WebCore::FEMorphology>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FEOffset> {
    static void encode(Encoder&, const WebCore::FEOffset&);
    static void encode(StreamConnectionEncoder&, const WebCore::FEOffset&);
    static std::optional<Ref<WebCore::FEOffset>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FESpecularLighting> {
    static void encode(Encoder&, const WebCore::FESpecularLighting&);
    static void encode(StreamConnectionEncoder&, const WebCore::FESpecularLighting&);
    static std::optional<Ref<WebCore::FESpecularLighting>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FETurbulence> {
    static void encode(Encoder&, const WebCore::FETurbulence&);
    static void encode(StreamConnectionEncoder&, const WebCore::FETurbulence&);
    static std::optional<Ref<WebCore::FETurbulence>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FilterEffectGeometry> {
    static void encode(Encoder&, const WebCore::FilterEffectGeometry&);
    static void encode(StreamConnectionEncoder&, const WebCore::FilterEffectGeometry&);
    static std::optional<WebCore::FilterEffectGeometry> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SVGFilterExpressionTerm> {
    static void encode(Encoder&, const WebCore::SVGFilterExpressionTerm&);
    static void encode(StreamConnectionEncoder&, const WebCore::SVGFilterExpressionTerm&);
    static std::optional<WebCore::SVGFilterExpressionTerm> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SVGPreserveAspectRatioValue> {
    static void encode(Encoder&, const WebCore::SVGPreserveAspectRatioValue&);
    static void encode(StreamConnectionEncoder&, const WebCore::SVGPreserveAspectRatioValue&);
    static std::optional<WebCore::SVGPreserveAspectRatioValue> decode(Decoder&);
};

#if ENABLE(GAMEPAD)
template<> struct ArgumentCoder<WebCore::GamepadEffectParameters> {
    static void encode(Encoder&, const WebCore::GamepadEffectParameters&);
    static std::optional<WebCore::GamepadEffectParameters> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::StorageEstimate> {
    static void encode(Encoder&, const WebCore::StorageEstimate&);
    static std::optional<WebCore::StorageEstimate> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ListStyleType> {
    static void encode(Encoder&, const WebCore::ListStyleType&);
    static std::optional<WebCore::ListStyleType> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TextList> {
    static void encode(Encoder&, const WebCore::TextList&);
    static std::optional<WebCore::TextList> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FontAttributes> {
    static void encode(Encoder&, const WebCore::FontAttributes&);
    static std::optional<WebCore::FontAttributes> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CrossOriginEmbedderPolicy> {
    static void encode(Encoder&, const WebCore::CrossOriginEmbedderPolicy&);
    static std::optional<WebCore::CrossOriginEmbedderPolicy> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SameSiteInfo> {
    static void encode(Encoder&, const WebCore::SameSiteInfo&);
    static std::optional<WebCore::SameSiteInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SecurityOrigin> {
    static void encode(Encoder&, const WebCore::SecurityOrigin&);
    static std::optional<Ref<WebCore::SecurityOrigin>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CookieRequestHeaderFieldProxy> {
    static void encode(Encoder&, const WebCore::CookieRequestHeaderFieldProxy&);
    static std::optional<WebCore::CookieRequestHeaderFieldProxy> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FormData> {
    static void encode(Encoder&, const WebCore::FormData&);
    static std::optional<Ref<WebCore::FormData>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::RequestedScrollData> {
    static void encode(Encoder&, const WebCore::RequestedScrollData&);
    static std::optional<WebCore::RequestedScrollData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FloatScrollSnapOffsetsInfo> {
    static void encode(Encoder&, const WebCore::FloatScrollSnapOffsetsInfo&);
    static std::optional<WebCore::FloatScrollSnapOffsetsInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FloatSnapOffset> {
    static void encode(Encoder&, const WebCore::FloatSnapOffset&);
    static std::optional<WebCore::FloatSnapOffset> decode(Decoder&);
};

#if ENABLE(ENCRYPTED_MEDIA)
template<> struct ArgumentCoder<WebCore::CDMMediaCapability> {
    static void encode(Encoder&, const WebCore::CDMMediaCapability&);
    static std::optional<WebCore::CDMMediaCapability> decode(Decoder&);
};
#endif

#if ENABLE(ENCRYPTED_MEDIA)
template<> struct ArgumentCoder<WebCore::CDMRestrictions> {
    static void encode(Encoder&, const WebCore::CDMRestrictions&);
    static std::optional<WebCore::CDMRestrictions> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::MediaSelectionOption> {
    static void encode(Encoder&, const WebCore::MediaSelectionOption&);
    static std::optional<WebCore::MediaSelectionOption> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::BufferSource> {
    static void encode(Encoder&, const WebCore::BufferSource&);
    static std::optional<WebCore::BufferSource> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FontShadow> {
    static void encode(Encoder&, const WebCore::FontShadow&);
    static std::optional<WebCore::FontShadow> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CompositionHighlight> {
    static void encode(Encoder&, const WebCore::CompositionHighlight&);
    static std::optional<WebCore::CompositionHighlight> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FontChanges> {
    static void encode(Encoder&, const WebCore::FontChanges&);
    static std::optional<WebCore::FontChanges> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::FontAttributeChanges> {
    static void encode(Encoder&, const WebCore::FontAttributeChanges&);
    static std::optional<WebCore::FontAttributeChanges> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TextManipulationControllerExclusionRule> {
    static void encode(Encoder&, const WebCore::TextManipulationControllerExclusionRule&);
    static std::optional<WebCore::TextManipulationControllerExclusionRule> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::TextManipulationControllerManipulationFailure> {
    static void encode(Encoder&, const WebCore::TextManipulationControllerManipulationFailure&);
    static std::optional<WebCore::TextManipulationControllerManipulationFailure> decode(Decoder&);
};

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::BackgroundFetchInformation> {
    static void encode(Encoder&, const WebCore::BackgroundFetchInformation&);
    static std::optional<WebCore::BackgroundFetchInformation> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::BackgroundFetchRequest> {
    static void encode(Encoder&, const WebCore::BackgroundFetchRequest&);
    static std::optional<WebCore::BackgroundFetchRequest> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::BackgroundFetchRecordInformation> {
    static void encode(Encoder&, const WebCore::BackgroundFetchRecordInformation&);
    static std::optional<WebCore::BackgroundFetchRecordInformation> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::BackgroundFetchOptions> {
    static void encode(Encoder&, const WebCore::BackgroundFetchOptions&);
    static std::optional<WebCore::BackgroundFetchOptions> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ImageResource> {
    static void encode(Encoder&, const WebCore::ImageResource&);
    static std::optional<WebCore::ImageResource> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::FourCC> {
    static void encode(Encoder&, const WebCore::FourCC&);
    static std::optional<WebCore::FourCC> decode(Decoder&);
};

#if ENABLE(VIDEO)
template<> struct ArgumentCoder<WebCore::MediaEngineSupportParameters> {
    static void encode(Encoder&, const WebCore::MediaEngineSupportParameters&);
    static std::optional<WebCore::MediaEngineSupportParameters> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::GeolocationPositionData> {
    static void encode(Encoder&, const WebCore::GeolocationPositionData&);
    static std::optional<WebCore::GeolocationPositionData> decode(Decoder&);
};

#if ENABLE(APP_HIGHLIGHTS)
template<> struct ArgumentCoder<WebCore::AppHighlight> {
    static void encode(Encoder&, const WebCore::AppHighlight&);
    static std::optional<WebCore::AppHighlight> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::MediaDeviceHashSalts> {
    static void encode(Encoder&, const WebCore::MediaDeviceHashSalts&);
    static std::optional<WebCore::MediaDeviceHashSalts> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SpeechRecognitionUpdate> {
    static void encode(Encoder&, const WebCore::SpeechRecognitionUpdate&);
    static std::optional<WebCore::SpeechRecognitionUpdate> decode(Decoder&);
};

#if USE(SYSTEM_PREVIEW)
template<> struct ArgumentCoder<WebCore::ARKitBadgeSystemImage> {
    static void encode(Encoder&, const WebCore::ARKitBadgeSystemImage&);
    static void encode(StreamConnectionEncoder&, const WebCore::ARKitBadgeSystemImage&);
    static std::optional<Ref<WebCore::ARKitBadgeSystemImage>> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::AudioIOPosition> {
    static void encode(Encoder&, const WebCore::AudioIOPosition&);
    static std::optional<WebCore::AudioIOPosition> decode(Decoder&);
};

#if ENABLE(VIDEO) && USE(AVFOUNDATION)
template<> struct ArgumentCoder<WebCore::VideoFrameCV> {
    static void encode(Encoder&, const WebCore::VideoFrameCV&);
    static std::optional<Ref<WebCore::VideoFrameCV>> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::GradientColorStop> {
    static void encode(Encoder&, const WebCore::GradientColorStop&);
    static void encode(StreamConnectionEncoder&, const WebCore::GradientColorStop&);
    static std::optional<WebCore::GradientColorStop> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::GradientColorStops> {
    static void encode(Encoder&, const WebCore::GradientColorStops&);
    static void encode(StreamConnectionEncoder&, const WebCore::GradientColorStops&);
    static std::optional<WebCore::GradientColorStops> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ImageBufferBackendParameters> {
    static void encode(Encoder&, const WebCore::ImageBufferBackendParameters&);
    static std::optional<WebCore::ImageBufferBackendParameters> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ProcessIdentity> {
    static void encode(Encoder&, WebCore::ProcessIdentity&&);
    static std::optional<WebCore::ProcessIdentity> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ColorInterpolationMethod> {
    static void encode(Encoder&, const WebCore::ColorInterpolationMethod&);
    static void encode(StreamConnectionEncoder&, const WebCore::ColorInterpolationMethod&);
    static std::optional<WebCore::ColorInterpolationMethod> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CompositeMode> {
    static void encode(Encoder&, const WebCore::CompositeMode&);
    static void encode(StreamConnectionEncoder&, const WebCore::CompositeMode&);
    static std::optional<WebCore::CompositeMode> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DocumentMarkerLineStyle> {
    static void encode(Encoder&, const WebCore::DocumentMarkerLineStyle&);
    static void encode(StreamConnectionEncoder&, const WebCore::DocumentMarkerLineStyle&);
    static std::optional<WebCore::DocumentMarkerLineStyle> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::GraphicsDropShadow> {
    static void encode(Encoder&, const WebCore::GraphicsDropShadow&);
    static void encode(StreamConnectionEncoder&, const WebCore::GraphicsDropShadow&);
    static std::optional<WebCore::GraphicsDropShadow> decode(Decoder&);
};

#if ENABLE(VIDEO)
template<> struct ArgumentCoder<WebCore::GenericCueData> {
    static void encode(Encoder&, const WebCore::GenericCueData&);
    static void encode(StreamConnectionEncoder&, const WebCore::GenericCueData&);
    static std::optional<WebCore::GenericCueData> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::ImageDecoderFrameInfo> {
    static void encode(Encoder&, const WebCore::ImageDecoderFrameInfo&);
    static void encode(StreamConnectionEncoder&, const WebCore::ImageDecoderFrameInfo&);
    static std::optional<WebCore::ImageDecoderFrameInfo> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::DisplayList::DrawDotsForDocumentMarker> {
    static void encode(Encoder&, const WebCore::DisplayList::DrawDotsForDocumentMarker&);
    static void encode(StreamConnectionEncoder&, const WebCore::DisplayList::DrawDotsForDocumentMarker&);
    static std::optional<WebCore::DisplayList::DrawDotsForDocumentMarker> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ImageOrientation> {
    static void encode(Encoder&, const WebCore::ImageOrientation&);
    static void encode(StreamConnectionEncoder&, const WebCore::ImageOrientation&);
    static std::optional<WebCore::ImageOrientation> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ImagePaintingOptions> {
    static void encode(Encoder&, const WebCore::ImagePaintingOptions&);
    static void encode(StreamConnectionEncoder&, const WebCore::ImagePaintingOptions&);
    static std::optional<WebCore::ImagePaintingOptions> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CanvasActivityRecord> {
    static void encode(Encoder&, const WebCore::CanvasActivityRecord&);
    static std::optional<WebCore::CanvasActivityRecord> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PCM::AttributionSecondsUntilSendData> {
    static void encode(Encoder&, const WebCore::PCM::AttributionSecondsUntilSendData&);
    static std::optional<WebCore::PCM::AttributionSecondsUntilSendData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CrossOriginOpenerPolicy> {
    static void encode(Encoder&, const WebCore::CrossOriginOpenerPolicy&);
    static std::optional<WebCore::CrossOriginOpenerPolicy> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CustomHeaderFields> {
    static void encode(Encoder&, const WebCore::CustomHeaderFields&);
    static std::optional<WebCore::CustomHeaderFields> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::HTTPHeaderField> {
    static void encode(Encoder&, const WebCore::HTTPHeaderField&);
    static std::optional<WebCore::HTTPHeaderField> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::NavigationRequester> {
    static void encode(Encoder&, const WebCore::NavigationRequester&);
    static std::optional<WebCore::NavigationRequester> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PolicyContainer> {
    static void encode(Encoder&, const WebCore::PolicyContainer&);
    static std::optional<WebCore::PolicyContainer> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SubstituteData> {
    static void encode(Encoder&, const WebCore::SubstituteData&);
    static std::optional<WebCore::SubstituteData> decode(Decoder&);
};

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ServiceWorkerClientData> {
    static void encode(Encoder&, const WebCore::ServiceWorkerClientData&);
    static std::optional<WebCore::ServiceWorkerClientData> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ServiceWorkerClientPendingMessage> {
    static void encode(Encoder&, const WebCore::ServiceWorkerClientPendingMessage&);
    static std::optional<WebCore::ServiceWorkerClientPendingMessage> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ServiceWorkerClientQueryOptions> {
    static void encode(Encoder&, const WebCore::ServiceWorkerClientQueryOptions&);
    static std::optional<WebCore::ServiceWorkerClientQueryOptions> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ServiceWorkerData> {
    static void encode(Encoder&, const WebCore::ServiceWorkerData&);
    static std::optional<WebCore::ServiceWorkerData> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ServiceWorkerJobData> {
    static void encode(Encoder&, const WebCore::ServiceWorkerJobData&);
    static std::optional<WebCore::ServiceWorkerJobData> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::EventInit> {
    static void encode(Encoder&, const WebCore::EventInit&);
    static std::optional<WebCore::EventInit> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::MessageWithMessagePorts> {
    static void encode(Encoder&, const WebCore::MessageWithMessagePorts&);
    static std::optional<WebCore::MessageWithMessagePorts> decode(Decoder&);
};

#if ENABLE(TRACKING_PREVENTION)
template<> struct ArgumentCoder<WebCore::RequestStorageAccessResult> {
    static void encode(Encoder&, const WebCore::RequestStorageAccessResult&);
    static std::optional<WebCore::RequestStorageAccessResult> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::Exception> {
    static void encode(Encoder&, const WebCore::Exception&);
    static std::optional<WebCore::Exception> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ExceptionData> {
    static void encode(Encoder&, const WebCore::ExceptionData&);
    static std::optional<WebCore::ExceptionData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::MessagePortIdentifier> {
    static void encode(Encoder&, const WebCore::MessagePortIdentifier&);
    static std::optional<WebCore::MessagePortIdentifier> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SecurityPolicyViolationEventInit> {
    static void encode(Encoder&, const WebCore::SecurityPolicyViolationEventInit&);
    static std::optional<WebCore::SecurityPolicyViolationEventInit> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CSPViolationReportBody> {
    static void encode(Encoder&, const WebCore::CSPViolationReportBody&);
    static std::optional<Ref<WebCore::CSPViolationReportBody>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SecurityOriginData> {
    static void encode(Encoder&, const WebCore::SecurityOriginData&);
    static std::optional<WebCore::SecurityOriginData> decode(Decoder&);
};

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::MediaConstraint> {
    static void encode(Encoder&, const WebCore::MediaConstraint&);
    static std::optional<WebCore::MediaConstraint> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::IntConstraint> {
    static void encode(Encoder&, const WebCore::IntConstraint&);
    static std::optional<WebCore::IntConstraint> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::DoubleConstraint> {
    static void encode(Encoder&, const WebCore::DoubleConstraint&);
    static std::optional<WebCore::DoubleConstraint> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::BooleanConstraint> {
    static void encode(Encoder&, const WebCore::BooleanConstraint&);
    static std::optional<WebCore::BooleanConstraint> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::StringConstraint> {
    static void encode(Encoder&, const WebCore::StringConstraint&);
    static std::optional<WebCore::StringConstraint> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::FrameRateRange> {
    static void encode(Encoder&, const WebCore::FrameRateRange&);
    static std::optional<WebCore::FrameRateRange> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::VideoPresetData> {
    static void encode(Encoder&, const WebCore::VideoPresetData&);
    static std::optional<WebCore::VideoPresetData> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::RealtimeMediaSourceSupportedConstraints> {
    static void encode(Encoder&, const WebCore::RealtimeMediaSourceSupportedConstraints&);
    static std::optional<WebCore::RealtimeMediaSourceSupportedConstraints> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::RealtimeMediaSourceSettings> {
    static void encode(Encoder&, const WebCore::RealtimeMediaSourceSettings&);
    static std::optional<WebCore::RealtimeMediaSourceSettings> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::CaptureDevice> {
    static void encode(Encoder&, const WebCore::CaptureDevice&);
    static std::optional<WebCore::CaptureDevice> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::CaptureDeviceWithCapabilities> {
    static void encode(Encoder&, const WebCore::CaptureDeviceWithCapabilities&);
    static std::optional<WebCore::CaptureDeviceWithCapabilities> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::RealtimeMediaSourceCapabilities> {
    static void encode(Encoder&, const WebCore::RealtimeMediaSourceCapabilities&);
    static std::optional<WebCore::RealtimeMediaSourceCapabilities> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::PlatformVideoColorSpace> {
    static void encode(Encoder&, const WebCore::PlatformVideoColorSpace&);
    static void encode(StreamConnectionEncoder&, const WebCore::PlatformVideoColorSpace&);
    static std::optional<WebCore::PlatformVideoColorSpace> decode(Decoder&);
};

#if ENABLE(VIDEO)
template<> struct ArgumentCoder<WebCore::PlatformTrackConfiguration> {
    static void encode(Encoder&, const WebCore::PlatformTrackConfiguration&);
    static std::optional<WebCore::PlatformTrackConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(VIDEO)
template<> struct ArgumentCoder<WebCore::PlatformAudioTrackConfiguration> {
    static void encode(Encoder&, const WebCore::PlatformAudioTrackConfiguration&);
    static std::optional<WebCore::PlatformAudioTrackConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(VIDEO)
template<> struct ArgumentCoder<WebCore::PlatformVideoTrackConfiguration> {
    static void encode(Encoder&, const WebCore::PlatformVideoTrackConfiguration&);
    static std::optional<WebCore::PlatformVideoTrackConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(WEB_RTC)
template<> struct ArgumentCoder<WebCore::RTCDataChannelInit> {
    static void encode(Encoder&, const WebCore::RTCDataChannelInit&);
    static std::optional<WebCore::RTCDataChannelInit> decode(Decoder&);
};
#endif

#if ENABLE(WEB_RTC)
template<> struct ArgumentCoder<WebCore::RTCDataChannelIdentifier> {
    static void encode(Encoder&, const WebCore::RTCDataChannelIdentifier&);
    static std::optional<WebCore::RTCDataChannelIdentifier> decode(Decoder&);
};
#endif

#if ENABLE(CONTENT_EXTENSIONS)
template<> struct ArgumentCoder<WebCore::ContentRuleListResults> {
    static void encode(Encoder&, const WebCore::ContentRuleListResults&);
    static std::optional<WebCore::ContentRuleListResults> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::COEPInheritenceViolationReportBody> {
    static void encode(Encoder&, const WebCore::COEPInheritenceViolationReportBody&);
    static std::optional<Ref<WebCore::COEPInheritenceViolationReportBody>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CORPViolationReportBody> {
    static void encode(Encoder&, const WebCore::CORPViolationReportBody&);
    static std::optional<Ref<WebCore::CORPViolationReportBody>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ReportBody> {
    static void encode(Encoder&, const WebCore::ReportBody&);
    static std::optional<Ref<WebCore::ReportBody>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SourceImage> {
    static void encode(Encoder&, const WebCore::SourceImage&);
    static void encode(StreamConnectionEncoder&, const WebCore::SourceImage&);
    static std::optional<WebCore::SourceImage> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::LinkIcon> {
    static void encode(Encoder&, const WebCore::LinkIcon&);
    static std::optional<WebCore::LinkIcon> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SupportedPluginIdentifier> {
    static void encode(Encoder&, const WebCore::SupportedPluginIdentifier&);
    static std::optional<WebCore::SupportedPluginIdentifier> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::CSSValueKey> {
    static void encode(Encoder&, const WebCore::CSSValueKey&);
    static std::optional<WebCore::CSSValueKey> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::VideoFrameTimeMetadata> {
    static void encode(Encoder&, const WebCore::VideoFrameTimeMetadata&);
    static std::optional<WebCore::VideoFrameTimeMetadata> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PositionedGlyphs> {
    static void encode(Encoder&, const WebCore::PositionedGlyphs&);
    static void encode(StreamConnectionEncoder&, const WebCore::PositionedGlyphs&);
    static std::optional<WebCore::PositionedGlyphs> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::EventRegion> {
    static void encode(Encoder&, const WebCore::EventRegion&);
    static std::optional<WebCore::EventRegion> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PresentationSize> {
    static void encode(Encoder&, const WebCore::PresentationSize&);
    static std::optional<WebCore::PresentationSize> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::PasteboardItemInfo> {
    static void encode(Encoder&, const WebCore::PasteboardItemInfo&);
    static std::optional<WebCore::PasteboardItemInfo> decode(Decoder&);
};

#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS) && USE(UICONTEXTMENU)
template<> struct ArgumentCoder<WebCore::MediaControlsContextMenuItem> {
    static void encode(Encoder&, const WebCore::MediaControlsContextMenuItem&);
    static std::optional<WebCore::MediaControlsContextMenuItem> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::WorkerOptions> {
    static void encode(Encoder&, const WebCore::WorkerOptions&);
    static std::optional<WebCore::WorkerOptions> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::WorkerInitializationData> {
    static void encode(Encoder&, const WebCore::WorkerInitializationData&);
    static std::optional<WebCore::WorkerInitializationData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::WorkerFetchResult> {
    static void encode(Encoder&, const WebCore::WorkerFetchResult&);
    static std::optional<WebCore::WorkerFetchResult> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::SharedWorkerKey> {
    static void encode(Encoder&, const WebCore::SharedWorkerKey&);
    static std::optional<WebCore::SharedWorkerKey> decode(Decoder&);
};

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ServiceWorkerRegistrationOptions> {
    static void encode(Encoder&, const WebCore::ServiceWorkerRegistrationOptions&);
    static std::optional<WebCore::ServiceWorkerRegistrationOptions> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ServiceWorkerRegistrationKey> {
    static void encode(Encoder&, const WebCore::ServiceWorkerRegistrationKey&);
    static std::optional<WebCore::ServiceWorkerRegistrationKey> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ServiceWorkerRegistrationData> {
    static void encode(Encoder&, const WebCore::ServiceWorkerRegistrationData&);
    static std::optional<WebCore::ServiceWorkerRegistrationData> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ServiceWorkerJobDataIdentifier> {
    static void encode(Encoder&, const WebCore::ServiceWorkerJobDataIdentifier&);
    static std::optional<WebCore::ServiceWorkerJobDataIdentifier> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ServiceWorkerImportedScript> {
    static void encode(Encoder&, const WebCore::ServiceWorkerImportedScript&);
    static std::optional<WebCore::ServiceWorkerImportedScript> decode(Decoder&);
};
#endif

#if ENABLE(SERVICE_WORKER)
template<> struct ArgumentCoder<WebCore::ServiceWorkerContextData> {
    static void encode(Encoder&, const WebCore::ServiceWorkerContextData&);
    static std::optional<WebCore::ServiceWorkerContextData> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<JSC::ArrayBuffer> {
    static void encode(Encoder&, const JSC::ArrayBuffer&);
    static std::optional<Ref<JSC::ArrayBuffer>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::GlobalFrameIdentifier> {
    static void encode(Encoder&, const WebCore::GlobalFrameIdentifier&);
    static std::optional<WebCore::GlobalFrameIdentifier> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::GlobalWindowIdentifier> {
    static void encode(Encoder&, const WebCore::GlobalWindowIdentifier&);
    static std::optional<WebCore::GlobalWindowIdentifier> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::InteractionRegion> {
    static void encode(Encoder&, const WebCore::InteractionRegion&);
    static std::optional<WebCore::InteractionRegion> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::Region> {
    static void encode(Encoder&, const WebCore::Region&);
    static std::optional<WebCore::Region> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::ISOWebVTTCue> {
    static void encode(Encoder&, const WebCore::ISOWebVTTCue&);
    static std::optional<WebCore::ISOWebVTTCue> decode(Decoder&);
};

#if ENABLE(WEB_AUTHN)
template<> struct ArgumentCoder<WebCore::MockWebAuthenticationConfiguration> {
    static void encode(Encoder&, const WebCore::MockWebAuthenticationConfiguration&);
    static std::optional<WebCore::MockWebAuthenticationConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(THREADED_ANIMATION_RESOLUTION)
template<> struct ArgumentCoder<WebCore::LengthPoint> {
    static void encode(Encoder&, const WebCore::LengthPoint&);
    static std::optional<WebCore::LengthPoint> decode(Decoder&);
};
#endif

#if ENABLE(THREADED_ANIMATION_RESOLUTION)
template<> struct ArgumentCoder<WebCore::OffsetRotation> {
    static void encode(Encoder&, const WebCore::OffsetRotation&);
    static std::optional<WebCore::OffsetRotation> decode(Decoder&);
};
#endif

#if ENABLE(THREADED_ANIMATION_RESOLUTION)
template<> struct ArgumentCoder<WebCore::AcceleratedEffectValues> {
    static void encode(Encoder&, const WebCore::AcceleratedEffectValues&);
    static std::optional<WebCore::AcceleratedEffectValues> decode(Decoder&);
};
#endif

#if ENABLE(THREADED_ANIMATION_RESOLUTION)
template<> struct ArgumentCoder<WebCore::AcceleratedEffectKeyframe> {
    static void encode(Encoder&, const WebCore::AcceleratedEffectKeyframe&);
    static std::optional<WebCore::AcceleratedEffectKeyframe> decode(Decoder&);
};
#endif

#if ENABLE(THREADED_ANIMATION_RESOLUTION)
template<> struct ArgumentCoder<WebCore::AcceleratedEffect> {
    static void encode(Encoder&, const WebCore::AcceleratedEffect&);
    static std::optional<Ref<WebCore::AcceleratedEffect>> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::ProtectionSpace> {
    static void encode(Encoder&, const WebCore::ProtectionSpace&);
    static std::optional<WebCore::ProtectionSpace> decode(Decoder&);
};

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebCore::ShapeDetection::BarcodeDetectorOptions> {
    static void encode(Encoder&, const WebCore::ShapeDetection::BarcodeDetectorOptions&);
    static void encode(StreamConnectionEncoder&, const WebCore::ShapeDetection::BarcodeDetectorOptions&);
    static std::optional<WebCore::ShapeDetection::BarcodeDetectorOptions> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebCore::ShapeDetection::DetectedBarcode> {
    static void encode(Encoder&, const WebCore::ShapeDetection::DetectedBarcode&);
    static void encode(StreamConnectionEncoder&, const WebCore::ShapeDetection::DetectedBarcode&);
    static std::optional<WebCore::ShapeDetection::DetectedBarcode> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebCore::ShapeDetection::DetectedFace> {
    static void encode(Encoder&, const WebCore::ShapeDetection::DetectedFace&);
    static void encode(StreamConnectionEncoder&, const WebCore::ShapeDetection::DetectedFace&);
    static std::optional<WebCore::ShapeDetection::DetectedFace> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebCore::ShapeDetection::DetectedText> {
    static void encode(Encoder&, const WebCore::ShapeDetection::DetectedText&);
    static void encode(StreamConnectionEncoder&, const WebCore::ShapeDetection::DetectedText&);
    static std::optional<WebCore::ShapeDetection::DetectedText> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebCore::ShapeDetection::FaceDetectorOptions> {
    static void encode(Encoder&, const WebCore::ShapeDetection::FaceDetectorOptions&);
    static void encode(StreamConnectionEncoder&, const WebCore::ShapeDetection::FaceDetectorOptions&);
    static std::optional<WebCore::ShapeDetection::FaceDetectorOptions> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebCore::ShapeDetection::Landmark> {
    static void encode(Encoder&, const WebCore::ShapeDetection::Landmark&);
    static void encode(StreamConnectionEncoder&, const WebCore::ShapeDetection::Landmark&);
    static std::optional<WebCore::ShapeDetection::Landmark> decode(Decoder&);
};
#endif

#if ENABLE(MEDIA_STREAM)
template<> struct ArgumentCoder<WebCore::CaptureSourceError> {
    static void encode(Encoder&, const WebCore::CaptureSourceError&);
    static std::optional<WebCore::CaptureSourceError> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebCore::CookieStoreGetOptions> {
    static void encode(Encoder&, const WebCore::CookieStoreGetOptions&);
    static std::optional<WebCore::CookieStoreGetOptions> decode(Decoder&);
};

template<> struct ArgumentCoder<WebCore::Model> {
    static void encode(Encoder&, const WebCore::Model&);
    static std::optional<Ref<WebCore::Model>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebEvent> {
    static void encode(Encoder&, const WebKit::WebEvent&);
    static std::optional<WebKit::WebEvent> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebKeyboardEvent> {
    static void encode(Encoder&, const WebKit::WebKeyboardEvent&);
    static std::optional<WebKit::WebKeyboardEvent> decode(Decoder&);
};

#if ENABLE(TOUCH_EVENTS)
template<> struct ArgumentCoder<WebKit::WebTouchEvent> {
    static void encode(Encoder&, const WebKit::WebTouchEvent&);
    static std::optional<WebKit::WebTouchEvent> decode(Decoder&);
};
#endif

#if ENABLE(TOUCH_EVENTS)
template<> struct ArgumentCoder<WebKit::WebPlatformTouchPoint> {
    static void encode(Encoder&, const WebKit::WebPlatformTouchPoint&);
    static std::optional<WebKit::WebPlatformTouchPoint> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebKit::WebMouseEvent> {
    static void encode(Encoder&, const WebKit::WebMouseEvent&);
    static std::optional<WebKit::WebMouseEvent> decode(Decoder&);
};

#if ENABLE(MAC_GESTURE_EVENTS)
template<> struct ArgumentCoder<WebKit::WebGestureEvent> {
    static void encode(Encoder&, const WebKit::WebGestureEvent&);
    static std::optional<WebKit::WebGestureEvent> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebKit::WebWheelEvent> {
    static void encode(Encoder&, const WebKit::WebWheelEvent&);
    static std::optional<WebKit::WebWheelEvent> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebHitTestResultData> {
    static void encode(Encoder&, const WebKit::WebHitTestResultData&);
    static std::optional<WebKit::WebHitTestResultData> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebPageCreationParameters> {
    static void encode(Encoder&, const WebKit::WebPageCreationParameters&);
    static std::optional<WebKit::WebPageCreationParameters> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebPopupItem> {
    static void encode(Encoder&, const WebKit::WebPopupItem&);
    static std::optional<WebKit::WebPopupItem> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebProcessCreationParameters> {
    static void encode(Encoder&, WebKit::WebProcessCreationParameters&&);
    static std::optional<WebKit::WebProcessCreationParameters> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebProcessDataStoreParameters> {
    static void encode(Encoder&, const WebKit::WebProcessDataStoreParameters&);
    static std::optional<WebKit::WebProcessDataStoreParameters> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebPushD::WebPushDaemonConnectionConfiguration> {
    static void encode(Encoder&, const WebKit::WebPushD::WebPushDaemonConnectionConfiguration&);
    static std::optional<WebKit::WebPushD::WebPushDaemonConnectionConfiguration> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebPushMessage> {
    static void encode(Encoder&, const WebKit::WebPushMessage&);
    static std::optional<WebKit::WebPushMessage> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebsiteDataStoreParameters> {
    static void encode(Encoder&, const WebKit::WebsiteDataStoreParameters&);
    static std::optional<WebKit::WebsiteDataStoreParameters> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebsitePoliciesData> {
    static void encode(Encoder&, const WebKit::WebsitePoliciesData&);
    static std::optional<WebKit::WebsitePoliciesData> decode(Decoder&);
};

template<> struct ArgumentCoder<API::Data> {
    static void encode(Encoder&, const API::Data&);
    static std::optional<Ref<API::Data>> decode(Decoder&);
};

template<> struct ArgumentCoder<API::Error> {
    static void encode(Encoder&, const API::Error&);
    static std::optional<Ref<API::Error>> decode(Decoder&);
};

template<> struct ArgumentCoder<API::FrameHandle> {
    static void encode(Encoder&, const API::FrameHandle&);
    static std::optional<Ref<API::FrameHandle>> decode(Decoder&);
};

template<> struct ArgumentCoder<API::Size> {
    static void encode(Encoder&, const API::Size&);
    static std::optional<Ref<API::Size>> decode(Decoder&);
};

template<> struct ArgumentCoder<API::Point> {
    static void encode(Encoder&, const API::Point&);
    static std::optional<Ref<API::Point>> decode(Decoder&);
};

template<> struct ArgumentCoder<API::Rect> {
    static void encode(Encoder&, const API::Rect&);
    static std::optional<Ref<API::Rect>> decode(Decoder&);
};

template<> struct ArgumentCoder<API::PageHandle> {
    static void encode(Encoder&, const API::PageHandle&);
    static std::optional<Ref<API::PageHandle>> decode(Decoder&);
};

template<> struct ArgumentCoder<API::URL> {
    static void encode(Encoder&, const API::URL&);
    static std::optional<Ref<API::URL>> decode(Decoder&);
};

template<> struct ArgumentCoder<API::URLRequest> {
    static void encode(Encoder&, const API::URLRequest&);
    static std::optional<Ref<API::URLRequest>> decode(Decoder&);
};

template<> struct ArgumentCoder<API::URLResponse> {
    static void encode(Encoder&, const API::URLResponse&);
    static std::optional<Ref<API::URLResponse>> decode(Decoder&);
};

template<> struct ArgumentCoder<WebKit::WebIDBResult> {
    static void encode(Encoder&, const WebKit::WebIDBResult&);
    static std::optional<WebKit::WebIDBResult> decode(Decoder&);
};

#if ENABLE(GAMEPAD)
template<> struct ArgumentCoder<WebKit::GamepadData> {
    static void encode(Encoder&, const WebKit::GamepadData&);
    static std::optional<WebKit::GamepadData> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::BindGroupDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::BindGroupDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::BindGroupDescriptor&);
    static std::optional<WebKit::WebGPU::BindGroupDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::BindGroupEntry> {
    static void encode(Encoder&, const WebKit::WebGPU::BindGroupEntry&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::BindGroupEntry&);
    static std::optional<WebKit::WebGPU::BindGroupEntry> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::BindGroupLayoutDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::BindGroupLayoutDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::BindGroupLayoutDescriptor&);
    static std::optional<WebKit::WebGPU::BindGroupLayoutDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::BindGroupLayoutEntry> {
    static void encode(Encoder&, const WebKit::WebGPU::BindGroupLayoutEntry&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::BindGroupLayoutEntry&);
    static std::optional<WebKit::WebGPU::BindGroupLayoutEntry> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::BlendComponent> {
    static void encode(Encoder&, const WebKit::WebGPU::BlendComponent&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::BlendComponent&);
    static std::optional<WebKit::WebGPU::BlendComponent> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::BlendState> {
    static void encode(Encoder&, const WebKit::WebGPU::BlendState&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::BlendState&);
    static std::optional<WebKit::WebGPU::BlendState> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::BufferBinding> {
    static void encode(Encoder&, const WebKit::WebGPU::BufferBinding&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::BufferBinding&);
    static std::optional<WebKit::WebGPU::BufferBinding> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::BufferBindingLayout> {
    static void encode(Encoder&, const WebKit::WebGPU::BufferBindingLayout&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::BufferBindingLayout&);
    static std::optional<WebKit::WebGPU::BufferBindingLayout> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::BufferDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::BufferDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::BufferDescriptor&);
    static std::optional<WebKit::WebGPU::BufferDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::CanvasConfiguration> {
    static void encode(Encoder&, const WebKit::WebGPU::CanvasConfiguration&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::CanvasConfiguration&);
    static std::optional<WebKit::WebGPU::CanvasConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ColorDict> {
    static void encode(Encoder&, const WebKit::WebGPU::ColorDict&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ColorDict&);
    static std::optional<WebKit::WebGPU::ColorDict> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ColorTargetState> {
    static void encode(Encoder&, const WebKit::WebGPU::ColorTargetState&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ColorTargetState&);
    static std::optional<WebKit::WebGPU::ColorTargetState> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::CommandBufferDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::CommandBufferDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::CommandBufferDescriptor&);
    static std::optional<WebKit::WebGPU::CommandBufferDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::CommandEncoderDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::CommandEncoderDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::CommandEncoderDescriptor&);
    static std::optional<WebKit::WebGPU::CommandEncoderDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::CompilationMessage> {
    static void encode(Encoder&, const WebKit::WebGPU::CompilationMessage&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::CompilationMessage&);
    static std::optional<WebKit::WebGPU::CompilationMessage> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ComputePassDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::ComputePassDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ComputePassDescriptor&);
    static std::optional<WebKit::WebGPU::ComputePassDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ComputePassTimestampWrite> {
    static void encode(Encoder&, const WebKit::WebGPU::ComputePassTimestampWrite&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ComputePassTimestampWrite&);
    static std::optional<WebKit::WebGPU::ComputePassTimestampWrite> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ComputePipelineDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::ComputePipelineDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ComputePipelineDescriptor&);
    static std::optional<WebKit::WebGPU::ComputePipelineDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::DepthStencilState> {
    static void encode(Encoder&, const WebKit::WebGPU::DepthStencilState&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::DepthStencilState&);
    static std::optional<WebKit::WebGPU::DepthStencilState> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::DeviceDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::DeviceDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::DeviceDescriptor&);
    static std::optional<WebKit::WebGPU::DeviceDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::Extent3DDict> {
    static void encode(Encoder&, const WebKit::WebGPU::Extent3DDict&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::Extent3DDict&);
    static std::optional<WebKit::WebGPU::Extent3DDict> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ExternalTextureBindingLayout> {
    static void encode(Encoder&, const WebKit::WebGPU::ExternalTextureBindingLayout&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ExternalTextureBindingLayout&);
    static std::optional<WebKit::WebGPU::ExternalTextureBindingLayout> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebCore::WebGPU::HTMLVideoElementIdentifier> {
    static void encode(Encoder&, const WebCore::WebGPU::HTMLVideoElementIdentifier&);
    static void encode(StreamConnectionEncoder&, const WebCore::WebGPU::HTMLVideoElementIdentifier&);
    static std::optional<WebCore::WebGPU::HTMLVideoElementIdentifier> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebCore::WebGPU::WebCodecsVideoFrameIdentifier> {
    static void encode(Encoder&, const WebCore::WebGPU::WebCodecsVideoFrameIdentifier&);
    static void encode(StreamConnectionEncoder&, const WebCore::WebGPU::WebCodecsVideoFrameIdentifier&);
    static std::optional<WebCore::WebGPU::WebCodecsVideoFrameIdentifier> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ExternalTextureDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::ExternalTextureDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ExternalTextureDescriptor&);
    static std::optional<WebKit::WebGPU::ExternalTextureDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::FragmentState> {
    static void encode(Encoder&, const WebKit::WebGPU::FragmentState&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::FragmentState&);
    static std::optional<WebKit::WebGPU::FragmentState> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ImageCopyBuffer> {
    static void encode(Encoder&, const WebKit::WebGPU::ImageCopyBuffer&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ImageCopyBuffer&);
    static std::optional<WebKit::WebGPU::ImageCopyBuffer> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ImageCopyExternalImage> {
    static void encode(Encoder&, const WebKit::WebGPU::ImageCopyExternalImage&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ImageCopyExternalImage&);
    static std::optional<WebKit::WebGPU::ImageCopyExternalImage> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ImageCopyTexture> {
    static void encode(Encoder&, const WebKit::WebGPU::ImageCopyTexture&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ImageCopyTexture&);
    static std::optional<WebKit::WebGPU::ImageCopyTexture> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ImageCopyTextureTagged> {
    static void encode(Encoder&, const WebKit::WebGPU::ImageCopyTextureTagged&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ImageCopyTextureTagged&);
    static std::optional<WebKit::WebGPU::ImageCopyTextureTagged> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ImageDataLayout> {
    static void encode(Encoder&, const WebKit::WebGPU::ImageDataLayout&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ImageDataLayout&);
    static std::optional<WebKit::WebGPU::ImageDataLayout> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::MultisampleState> {
    static void encode(Encoder&, const WebKit::WebGPU::MultisampleState&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::MultisampleState&);
    static std::optional<WebKit::WebGPU::MultisampleState> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ObjectDescriptorBase> {
    static void encode(Encoder&, const WebKit::WebGPU::ObjectDescriptorBase&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ObjectDescriptorBase&);
    static std::optional<WebKit::WebGPU::ObjectDescriptorBase> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::Origin2DDict> {
    static void encode(Encoder&, const WebKit::WebGPU::Origin2DDict&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::Origin2DDict&);
    static std::optional<WebKit::WebGPU::Origin2DDict> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::Origin3DDict> {
    static void encode(Encoder&, const WebKit::WebGPU::Origin3DDict&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::Origin3DDict&);
    static std::optional<WebKit::WebGPU::Origin3DDict> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::OutOfMemoryError> {
    static void encode(Encoder&, const WebKit::WebGPU::OutOfMemoryError&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::OutOfMemoryError&);
    static std::optional<WebKit::WebGPU::OutOfMemoryError> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::PipelineDescriptorBase> {
    static void encode(Encoder&, const WebKit::WebGPU::PipelineDescriptorBase&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::PipelineDescriptorBase&);
    static std::optional<WebKit::WebGPU::PipelineDescriptorBase> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::PipelineLayoutDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::PipelineLayoutDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::PipelineLayoutDescriptor&);
    static std::optional<WebKit::WebGPU::PipelineLayoutDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::PresentationContextDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::PresentationContextDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::PresentationContextDescriptor&);
    static std::optional<WebKit::WebGPU::PresentationContextDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::PrimitiveState> {
    static void encode(Encoder&, const WebKit::WebGPU::PrimitiveState&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::PrimitiveState&);
    static std::optional<WebKit::WebGPU::PrimitiveState> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ProgrammableStage> {
    static void encode(Encoder&, const WebKit::WebGPU::ProgrammableStage&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ProgrammableStage&);
    static std::optional<WebKit::WebGPU::ProgrammableStage> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::QuerySetDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::QuerySetDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::QuerySetDescriptor&);
    static std::optional<WebKit::WebGPU::QuerySetDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::RenderBundleDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::RenderBundleDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::RenderBundleDescriptor&);
    static std::optional<WebKit::WebGPU::RenderBundleDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::RenderBundleEncoderDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::RenderBundleEncoderDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::RenderBundleEncoderDescriptor&);
    static std::optional<WebKit::WebGPU::RenderBundleEncoderDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::RenderPassColorAttachment> {
    static void encode(Encoder&, const WebKit::WebGPU::RenderPassColorAttachment&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::RenderPassColorAttachment&);
    static std::optional<WebKit::WebGPU::RenderPassColorAttachment> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::RenderPassDepthStencilAttachment> {
    static void encode(Encoder&, const WebKit::WebGPU::RenderPassDepthStencilAttachment&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::RenderPassDepthStencilAttachment&);
    static std::optional<WebKit::WebGPU::RenderPassDepthStencilAttachment> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::RenderPassDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::RenderPassDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::RenderPassDescriptor&);
    static std::optional<WebKit::WebGPU::RenderPassDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::RenderPassLayout> {
    static void encode(Encoder&, const WebKit::WebGPU::RenderPassLayout&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::RenderPassLayout&);
    static std::optional<WebKit::WebGPU::RenderPassLayout> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::RenderPassTimestampWrite> {
    static void encode(Encoder&, const WebKit::WebGPU::RenderPassTimestampWrite&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::RenderPassTimestampWrite&);
    static std::optional<WebKit::WebGPU::RenderPassTimestampWrite> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::RenderPipelineDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::RenderPipelineDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::RenderPipelineDescriptor&);
    static std::optional<WebKit::WebGPU::RenderPipelineDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::RequestAdapterOptions> {
    static void encode(Encoder&, const WebKit::WebGPU::RequestAdapterOptions&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::RequestAdapterOptions&);
    static std::optional<WebKit::WebGPU::RequestAdapterOptions> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::SamplerBindingLayout> {
    static void encode(Encoder&, const WebKit::WebGPU::SamplerBindingLayout&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::SamplerBindingLayout&);
    static std::optional<WebKit::WebGPU::SamplerBindingLayout> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::SamplerDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::SamplerDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::SamplerDescriptor&);
    static std::optional<WebKit::WebGPU::SamplerDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ShaderModuleCompilationHint> {
    static void encode(Encoder&, const WebKit::WebGPU::ShaderModuleCompilationHint&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ShaderModuleCompilationHint&);
    static std::optional<WebKit::WebGPU::ShaderModuleCompilationHint> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ShaderModuleDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::ShaderModuleDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ShaderModuleDescriptor&);
    static std::optional<WebKit::WebGPU::ShaderModuleDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::StencilFaceState> {
    static void encode(Encoder&, const WebKit::WebGPU::StencilFaceState&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::StencilFaceState&);
    static std::optional<WebKit::WebGPU::StencilFaceState> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::StorageTextureBindingLayout> {
    static void encode(Encoder&, const WebKit::WebGPU::StorageTextureBindingLayout&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::StorageTextureBindingLayout&);
    static std::optional<WebKit::WebGPU::StorageTextureBindingLayout> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::SupportedFeatures> {
    static void encode(Encoder&, const WebKit::WebGPU::SupportedFeatures&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::SupportedFeatures&);
    static std::optional<WebKit::WebGPU::SupportedFeatures> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::SupportedLimits> {
    static void encode(Encoder&, const WebKit::WebGPU::SupportedLimits&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::SupportedLimits&);
    static std::optional<WebKit::WebGPU::SupportedLimits> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::TextureBindingLayout> {
    static void encode(Encoder&, const WebKit::WebGPU::TextureBindingLayout&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::TextureBindingLayout&);
    static std::optional<WebKit::WebGPU::TextureBindingLayout> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::TextureDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::TextureDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::TextureDescriptor&);
    static std::optional<WebKit::WebGPU::TextureDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::TextureViewDescriptor> {
    static void encode(Encoder&, const WebKit::WebGPU::TextureViewDescriptor&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::TextureViewDescriptor&);
    static std::optional<WebKit::WebGPU::TextureViewDescriptor> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::ValidationError> {
    static void encode(Encoder&, const WebKit::WebGPU::ValidationError&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::ValidationError&);
    static std::optional<WebKit::WebGPU::ValidationError> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::VertexAttribute> {
    static void encode(Encoder&, const WebKit::WebGPU::VertexAttribute&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::VertexAttribute&);
    static std::optional<WebKit::WebGPU::VertexAttribute> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::VertexBufferLayout> {
    static void encode(Encoder&, const WebKit::WebGPU::VertexBufferLayout&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::VertexBufferLayout&);
    static std::optional<WebKit::WebGPU::VertexBufferLayout> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::WebGPU::VertexState> {
    static void encode(Encoder&, const WebKit::WebGPU::VertexState&);
    static void encode(StreamConnectionEncoder&, const WebKit::WebGPU::VertexState&);
    static std::optional<WebKit::WebGPU::VertexState> decode(Decoder&);
};
#endif

template<> struct ArgumentCoder<WebKit::WebsiteData> {
    static void encode(Encoder&, const WebKit::WebsiteData&);
    static std::optional<WebKit::WebsiteData> decode(Decoder&);
};

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::BufferIdentifierSet> {
    static void encode(Encoder&, const WebKit::BufferIdentifierSet&);
    static void encode(StreamConnectionEncoder&, const WebKit::BufferIdentifierSet&);
    static std::optional<WebKit::BufferIdentifierSet> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS) && PLATFORM(COCOA)
template<> struct ArgumentCoder<WebKit::PrepareBackingStoreBuffersInputData> {
    static void encode(Encoder&, const WebKit::PrepareBackingStoreBuffersInputData&);
    static void encode(StreamConnectionEncoder&, const WebKit::PrepareBackingStoreBuffersInputData&);
    static std::optional<WebKit::PrepareBackingStoreBuffersInputData> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS) && PLATFORM(COCOA)
template<> struct ArgumentCoder<WebKit::PrepareBackingStoreBuffersOutputData> {
    static void encode(Encoder&, WebKit::PrepareBackingStoreBuffersOutputData&&);
    static std::optional<WebKit::PrepareBackingStoreBuffersOutputData> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS) && USE(AUDIO_SESSION)
template<> struct ArgumentCoder<WebKit::RemoteAudioSessionConfiguration> {
    static void encode(Encoder&, const WebKit::RemoteAudioSessionConfiguration&);
    static std::optional<WebKit::RemoteAudioSessionConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)
template<> struct ArgumentCoder<WebKit::RemoteCDMConfiguration> {
    static void encode(Encoder&, const WebKit::RemoteCDMConfiguration&);
    static std::optional<WebKit::RemoteCDMConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS)
template<> struct ArgumentCoder<WebKit::RemoteMediaPlayerConfiguration> {
    static void encode(Encoder&, const WebKit::RemoteMediaPlayerConfiguration&);
    static std::optional<WebKit::RemoteMediaPlayerConfiguration> decode(Decoder&);
};
#endif

#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
template<> struct ArgumentCoder<WebKit::RemoteMediaPlayerState> {
    static void encode(Encoder&, const WebKit::RemoteMediaPlayerState&);
    static std::optional<WebKit::RemoteMediaPlayerState> decode(Decoder&);
};
#endif

#if ENABLE(SPEECH_SYNTHESIS)
template<> struct ArgumentCoder<WebKit::WebSpeechSynthesisVoice> {
    static void encode(Encoder&, const WebKit::WebSpeechSynthesisVoice&);
    static std::optional<WebKit::WebSpeechSynthesisVoice> decode(Decoder&);
};
#endif

} // namespace IPC


namespace WTF {

template<> bool isValidEnum<WebKit::ListType, void>(uint8_t);
template<> bool isValidEnum<WebKit::TextAlignment, void>(uint8_t);
template<> bool isValidOptionSet<WebKit::TypingAttribute>(OptionSet<WebKit::TypingAttribute>);
template<> bool isValidEnum<WebKit::RemoteWorkerType, void>(uint8_t);
template<> bool isValidEnum<WebKit::SameDocumentNavigationType, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontWidthVariant, void>(uint8_t);
template<> bool isValidEnum<WebCore::Kerning, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontOpticalSizing, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontStyleAxis, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontVariantEastAsianVariant, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontVariantEastAsianWidth, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontVariantEastAsianRuby, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontVariantLigatures, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontVariantPosition, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontVariantCaps, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontVariantNumericFigure, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontVariantNumericSpacing, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontVariantNumericFraction, void>(uint8_t);
template<> bool isValidEnum<WebCore::TextRenderingMode, void>(uint8_t);
template<> bool isValidEnum<WebCore::FontSmoothingMode, void>(uint8_t);
#if ENABLE(APPLE_PAY)
template<> bool isValidEnum<WebCore::ApplePayFeature, void>(uint8_t);
#endif
#if ENABLE(APPLE_PAY)
template<> bool isValidEnum<WebCore::ApplePayPaymentTiming, void>(uint8_t);
#endif
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
template<> bool isValidEnum<WebCore::ApplePayRecurringPaymentDateUnit, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::ContactProperty, void>(uint8_t);
template<> bool isValidEnum<WebCore::CookieConsentDecisionResult, void>(uint8_t);
template<> bool isValidEnum<WebCore::IDBResultType, void>(uint8_t);
template<> bool isValidEnum<WebCore::IDBTransactionDurability, void>(uint8_t);
template<> bool isValidEnum<WebCore::IDBTransactionMode, void>(uint8_t);
#if ENABLE(MEDIA_SESSION)
template<> bool isValidEnum<WebCore::MediaSessionAction, void>(uint8_t);
#endif
#if ENABLE(MEDIA_SESSION)
template<> bool isValidEnum<WebCore::MediaSessionPlaybackState, void>(uint8_t);
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
template<> bool isValidEnum<WebCore::MediaSessionCoordinatorState, void>(uint8_t);
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
template<> bool isValidEnum<WebCore::MediaSessionReadyState, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::RTCErrorDetailType, void>(uint8_t);
template<> bool isValidEnum<WebCore::PermissionName, void>(uint8_t);
template<> bool isValidEnum<WebCore::PermissionQuerySource, void>(uint8_t);
template<> bool isValidEnum<WebCore::PermissionState, void>(uint8_t);
#if ENABLE(SERVICE_WORKER)
template<> bool isValidEnum<WebCore::PushPermissionState, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::AutofillFieldName, void>(uint8_t);
template<> bool isValidEnum<WebCore::EnterKeyHint, void>(uint8_t);
template<> bool isValidEnum<WebCore::DownloadableBinaryFontAllowedTypes, void>(uint8_t);
template<> bool isValidEnum<WebCore::LoadSchedulingMode, void>(uint8_t);
template<> bool isValidEnum<WebCore::ServiceWorkersMode, void>(uint8_t);
template<> bool isValidEnum<WebCore::ShouldTreatAsContinuingLoad, void>(uint8_t);
template<> bool isValidEnum<WebCore::ContentSecurityPolicyModeForExtension, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaProducerMediaCaptureKind, void>(uint8_t);
template<> bool isValidEnum<WebCore::ScreenOrientationType, void>(uint8_t);
template<> bool isValidEnum<WebCore::StorageBlockingPolicy, void>(uint8_t);
#if USE(APPKIT)
template<> bool isValidEnum<WebCore::AppKitControlSystemImageType, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::ScrollGranularity, void>(uint8_t);
template<> bool isValidEnum<WebCore::IndexedDB::KeyType, void>(int8_t);
template<> bool isValidEnum<WebCore::IndexedDB::CursorDirection, void>(uint8_t);
template<> bool isValidEnum<WebCore::IndexedDB::ObjectStoreOverwriteMode, void>(uint8_t);
template<> bool isValidEnum<WebCore::IndexedDB::RequestType, void>(uint8_t);
template<> bool isValidOptionSet<WebCore::NavigatorAPIsAccessed>(OptionSet<WebCore::NavigatorAPIsAccessed>);
template<> bool isValidOptionSet<WebCore::ScreenAPIsAccessed>(OptionSet<WebCore::ScreenAPIsAccessed>);
template<> bool isValidEnum<WebCore::ViewportFit, void>(uint8_t);
#if ENABLE(APPLE_PAY)
template<> bool isValidEnum<WebCore::ApplePayErrorContactField, void>(uint8_t);
#endif
#if ENABLE(APPLE_PAY)
template<> bool isValidEnum<WebCore::ApplePayErrorCode, void>(uint8_t);
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
template<> bool isValidEnum<WebCore::ApplePayInstallmentItemType, void>(uint8_t);
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
template<> bool isValidEnum<WebCore::ApplePayInstallmentRetailChannel, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::ScreenOrientationLockType, void>(uint8_t);
template<> bool isValidEnum<WebCore::DOMCacheEngine::Error, void>(uint8_t);
template<> bool isValidEnum<WebCore::SpeechRecognitionErrorType, void>(uint8_t);
#if ENABLE(WEB_AUTHN)
template<> bool isValidEnum<WebCore::AttestationConveyancePreference, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::RenderingPurpose, void>(uint8_t);
template<> bool isValidEnum<WebCore::AutoplayEvent, void>(uint8_t);
template<> bool isValidEnum<WebCore::InputMode, void>(uint8_t);
template<> bool isValidEnum<WebCore::NotificationDirection, void>(uint8_t);
template<> bool isValidEnum<WebCore::StoredCredentialsPolicy, void>(uint8_t);
template<> bool isValidEnum<WebCore::PreflightPolicy, void>(uint8_t);
template<> bool isValidEnum<WTFLogChannelState, void>(uint8_t);
template<> bool isValidEnum<WebCore::ScrollSnapStrictness, void>(uint8_t);
template<> bool isValidEnum<WebCore::LengthType, void>(uint8_t);
template<> bool isValidEnum<WebCore::OverscrollBehavior, void>(uint8_t);
template<> bool isValidEnum<WebCore::ScrollPinningBehavior, void>(uint8_t);
template<> bool isValidEnum<WebCore::WheelScrollGestureState, void>(uint8_t);
template<> bool isValidEnum<WebCore::DiagnosticLoggingDomain, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaCaptureType, void>(uint8_t);
#if ENABLE(WEB_AUTHN)
template<> bool isValidEnum<WebCore::AuthenticatorTransport, void>(uint8_t);
#endif
#if ENABLE(DATALIST_ELEMENT)
template<> bool isValidEnum<WebCore::DataListSuggestionActivationType, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::AlphaPremultiplication, void>(uint8_t);
template<> bool isValidEnum<WebCore::PixelFormat, void>(uint8_t);
template<> bool isValidEnum<WebCore::ScrollElasticity, void>(uint8_t);
template<> bool isValidEnum<WebCore::ScrollbarMode, void>(uint8_t);
template<> bool isValidEnum<WebCore::NativeScrollbarVisibility, void>(uint8_t);
template<> bool isValidEnum<WebCore::ScrollbarWidth, void>(uint8_t);
template<> bool isValidOptionSet<WebCore::WheelEventProcessingSteps>(OptionSet<WebCore::WheelEventProcessingSteps>);
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
template<> bool isValidEnum<WebCore::GraphicsContextGLPowerPreference, void>(uint8_t);
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
template<> bool isValidEnum<WebCore::GraphicsContextGLWebGLVersion, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::CSSBoxType, void>(uint8_t);
#if ENABLE(WEB_AUTHN)
template<> bool isValidEnum<WebCore::UserVerificationRequirement, void>(uint8_t);
#endif
#if ENABLE(WEB_AUTHN)
template<> bool isValidEnum<WebCore::ResidentKeyRequirement, void>(uint8_t);
#endif
#if ENABLE(WEB_AUTHN)
template<> bool isValidEnum<WebCore::AuthenticatorAttachment, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::ResourceRequestCachePolicy, void>(uint8_t);
template<> bool isValidEnum<WebCore::ResourceLoadPriority, void>(uint8_t);
template<> bool isValidEnum<WebCore::ReferrerPolicy, void>(uint8_t);
template<> bool isValidEnum<WebCore::FetchOptionsDestination, void>(uint8_t);
template<> bool isValidEnum<WebCore::FetchOptionsMode, void>(uint8_t);
template<> bool isValidEnum<WebCore::FetchOptionsCredentials, void>(uint8_t);
template<> bool isValidEnum<WebCore::FetchOptionsCache, void>(uint8_t);
template<> bool isValidEnum<WebCore::FetchOptionsRedirect, void>(uint8_t);
template<> bool isValidEnum<WebCore::FetchHeadersGuard, void>(uint8_t);
template<> bool isValidEnum<WebCore::StyleAppearance, void>(uint8_t);
#if ENABLE(APPLE_PAY)
template<> bool isValidEnum<WebCore::ApplePayButtonType, void>(uint8_t);
#endif
#if ENABLE(APPLE_PAY)
template<> bool isValidEnum<WebCore::ApplePayButtonStyle, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::ModalContainerDecision, void>(uint8_t);
template<> bool isValidOptionSet<WebCore::AutoplayEventFlags>(OptionSet<WebCore::AutoplayEventFlags>);
template<> bool isValidEnum<WebCore::FocusDirection, void>(uint8_t);
#if ENABLE(GAMEPAD)
template<> bool isValidEnum<WebCore::GamepadHapticEffectType, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::DOMPasteAccessCategory, void>(uint8_t);
template<> bool isValidEnum<WebCore::DOMPasteAccessPolicy, void>(uint8_t);
template<> bool isValidEnum<WebCore::DOMPasteAccessResponse, void>(uint8_t);
template<> bool isValidEnum<WebCore::DeviceOrientationOrMotionPermissionState, void>(uint8_t);
template<> bool isValidEnum<WebCore::VerticalAlignChange, void>(uint8_t);
template<> bool isValidEnum<WebCore::TextGranularity, void>(uint8_t);
template<> bool isValidEnum<WebCore::WritingDirection, void>(uint8_t);
template<> bool isValidEnum<WebCore::SelectionDirection, void>(uint8_t);
#if ENABLE(DATA_DETECTION)
template<> bool isValidOptionSet<WebCore::DataDetectorType>(OptionSet<WebCore::DataDetectorType>);
#endif
template<> bool isValidEnum<WebCore::AutocapitalizeType, void>(uint8_t);
#if ENABLE(ASYNC_SCROLLING)
template<> bool isValidOptionSet<WebCore::ScrollingStateNodeProperty>(OptionSet<WebCore::ScrollingStateNodeProperty>);
#endif
#if ENABLE(ENCRYPTED_MEDIA)
template<> bool isValidEnum<WebCore::CDMSessionType, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::MediaDecodingType, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaPlayerNetworkState, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaPlayerReadyState, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaPlayerMovieLoadType, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaPlayerPreload, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaPlayerVideoGravity, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaPlayerSupportsType, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaPlayerBufferingPolicy, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaPlayerMediaEngineIdentifier, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaPlayerWirelessPlaybackTargetType, void>(uint8_t);
template<> bool isValidEnum<WebCore::MediaPlayerPitchCorrectionAlgorithm, void>(uint8_t);
template<> bool isValidEnum<WebCore::SpeechRecognitionUpdateType, void>(uint8_t);
template<> bool isValidEnum<WebCore::CompositeOperator, void>(uint8_t);
template<> bool isValidEnum<WebCore::BlendMode, void>(uint8_t);
template<> bool isValidEnum<WebCore::GradientSpreadMethod, void>(uint8_t);
template<> bool isValidEnum<WebCore::InterpolationQuality, void>(uint8_t);
#if ENABLE(VIDEO)
template<> bool isValidEnum<WebCore::VideoFrameRotation, void>(uint16_t);
#endif
template<> bool isValidEnum<WebCore::ColorInterpolationColorSpace, void>(uint8_t);
template<> bool isValidEnum<WebCore::HueInterpolationMethod, void>(uint8_t);
#if USE(AUDIO_SESSION)
template<> bool isValidEnum<WebCore::RouteSharingPolicy, void>(uint8_t);
#endif
#if USE(AUDIO_SESSION)
template<> bool isValidEnum<WebCore::AudioSessionCategory, void>(uint8_t);
#endif
#if USE(AUDIO_SESSION)
template<> bool isValidEnum<WebCore::AudioSessionMode, void>(uint8_t);
#endif
#if USE(AUDIO_SESSION)
template<> bool isValidEnum<WebCore::AudioSessionRoutingArbitrationError, void>(uint8_t);
#endif
#if ENABLE(ENCRYPTED_MEDIA)
template<> bool isValidEnum<WebCore::CDMKeyStatus, void>(uint8_t);
#endif
#if ENABLE(ENCRYPTED_MEDIA)
template<> bool isValidEnum<WebCore::CDMMessageType, void>(uint8_t);
#endif
#if ENABLE(ENCRYPTED_MEDIA)
template<> bool isValidEnum<WebCore::CDMRequirement, void>(uint8_t);
#endif
#if ENABLE(WEB_RTC)
template<> bool isValidEnum<WebCore::RTCDataChannelState, void>(uint8_t);
#endif
#if ENABLE(WEB_RTC)
template<> bool isValidEnum<WebCore::RTCPriorityType, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::LineCap, void>(uint8_t);
template<> bool isValidEnum<WebCore::LineJoin, void>(uint8_t);
template<> bool isValidEnum<WebCore::StrokeStyle, void>(uint8_t);
template<> bool isValidOptionSet<WebCore::TextDrawingMode>(OptionSet<WebCore::TextDrawingMode>);
template<> bool isValidEnum<WebCore::DecodingMode, void>(uint8_t);
template<> bool isValidEnum<WebCore::DocumentMarkerLineStyleMode, void>(uint8_t);
template<> bool isValidEnum<WebCore::CrossOriginOpenerPolicyValue, void>(uint8_t);
template<> bool isValidEnum<WebCore::HTTPCookieAcceptPolicy, void>(uint8_t);
template<> bool isValidEnum<WebCore::NetworkLoadPriority, void>(uint8_t);
template<> bool isValidEnum<WebCore::PrivacyStance, void>(uint8_t);
template<> bool isValidEnum<WebCore::ThirdPartyCookieBlockingMode, void>(uint8_t);
template<> bool isValidEnum<WebCore::FirstPartyWebsiteDataRemovalMode, void>(uint8_t);
template<> bool isValidOptionSet<WebCore::DragApplicationFlags>(OptionSet<WebCore::DragApplicationFlags>);
template<> bool isValidOptionSet<WebCore::TextCheckingType>(OptionSet<WebCore::TextCheckingType>);
#if ENABLE(SERVICE_WORKER)
template<> bool isValidEnum<WebCore::ServiceWorkerClientType, void>(uint8_t);
#endif
#if ENABLE(SERVICE_WORKER)
template<> bool isValidEnum<WebCore::ServiceWorkerJobType, void>(uint8_t);
#endif
#if ENABLE(SERVICE_WORKER)
template<> bool isValidEnum<WebCore::ServiceWorkerRegistrationState, void>(uint8_t);
#endif
#if ENABLE(SERVICE_WORKER)
template<> bool isValidEnum<WebCore::ServiceWorkerState, void>(uint8_t);
#endif
#if ENABLE(SERVICE_WORKER)
template<> bool isValidEnum<WebCore::ServiceWorkerClientFrameType, void>(uint8_t);
#endif
#if ENABLE(SERVICE_WORKER)
template<> bool isValidEnum<WebCore::ServiceWorkerUpdateViaCache, void>(uint8_t);
#endif
#if ENABLE(MEDIA_STREAM)
template<> bool isValidEnum<WebCore::MediaConstraintType, void>(uint8_t);
#endif
#if ENABLE(MEDIA_STREAM)
template<> bool isValidEnum<WebCore::VideoFacingMode, void>(uint8_t);
#endif
#if ENABLE(MEDIA_STREAM)
template<> bool isValidEnum<WebCore::DisplaySurfaceType, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::PlatformVideoColorPrimaries, void>(uint8_t);
template<> bool isValidEnum<WebCore::PlatformVideoTransferCharacteristics, void>(uint8_t);
template<> bool isValidEnum<WebCore::PlatformVideoMatrixCoefficients, void>(uint8_t);
template<> bool isValidEnum<WebCore::PolicyAction, void>(uint8_t);
template<> bool isValidOptionSet<WebCore::ReloadOption>(OptionSet<WebCore::ReloadOption>);
template<> bool isValidEnum<WebCore::FrameLoadType, void>(uint8_t);
template<> bool isValidEnum<WebCore::NavigationType, void>(uint8_t);
template<> bool isValidEnum<WebCore::BrowsingContextGroupSwitchDecision, void>(uint8_t);
template<> bool isValidEnum<WebCore::ShouldOpenExternalURLsPolicy, void>(uint8_t);
template<> bool isValidEnum<WebCore::MouseEventPolicy, void>(uint8_t);
template<> bool isValidEnum<WebCore::ColorSchemePreference, void>(uint8_t);
template<> bool isValidOptionSet<WebCore::AdvancedPrivacyProtections>(OptionSet<WebCore::AdvancedPrivacyProtections>);
template<> bool isValidEnum<WebCore::ViolationReportType, void>(uint8_t);
template<> bool isValidEnum<WebCore::LinkIconType, void>(uint8_t);
template<> bool isValidEnum<WebCore::PluginLoadClientPolicy, void>(uint8_t);
template<> bool isValidEnum<WebCore::PasteboardItemPresentationStyle, void>(uint8_t);
#if HAVE(SCREEN_CAPTURE_KIT)
template<> bool isValidEnum<WebCore::DisplayCapturePromptType, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::TextIndicatorPresentationTransition, void>(uint8_t);
template<> bool isValidOptionSet<WebCore::TextIndicatorOption>(OptionSet<WebCore::TextIndicatorOption>);
template<> bool isValidEnum<WebCore::StorageType, void>(uint8_t);
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
template<> bool isValidOptionSet<WebCore::AcceleratedEffectProperty>(OptionSet<WebCore::AcceleratedEffectProperty>);
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
template<> bool isValidEnum<WebCore::WebAnimationType, void>(uint8_t);
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
template<> bool isValidEnum<WebCore::FillMode, void>(uint8_t);
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
template<> bool isValidEnum<WebCore::PlaybackDirection, void>(uint8_t);
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
template<> bool isValidEnum<WebCore::CompositeOperation, void>(uint8_t);
#endif
#if PLATFORM(MAC)
template<> bool isValidEnum<WebCore::CaretAnimatorType, void>(uint8_t);
#endif
#if ENABLE(GPU_PROCESS)
template<> bool isValidEnum<WebCore::ShapeDetection::BarcodeFormat, void>(uint8_t);
#endif
#if ENABLE(GPU_PROCESS)
template<> bool isValidEnum<WebCore::ShapeDetection::LandmarkType, void>(uint8_t);
#endif
template<> bool isValidOptionSet<WebCore::RenderAsTextFlag>(OptionSet<WebCore::RenderAsTextFlag>);
template<> bool isValidEnum<WebCore::WebGPU::TextureFormat, void>(uint8_t);
#if ENABLE(MEDIA_STREAM)
template<> bool isValidEnum<WebCore::MediaAccessDenialReason, void>(uint8_t);
#endif
template<> bool isValidEnum<WebCore::WebGPU::TextureAspect, void>(uint8_t);
template<> bool isValidEnum<WebCore::WebGPU::PredefinedColorSpace, void>(uint8_t);
template<> bool isValidOptionSet<WebKit::WebEventModifier>(OptionSet<WebKit::WebEventModifier>);
template<> bool isValidEnum<WebKit::WebEventType, void>(int8_t);
template<> bool isValidEnum<WebKit::WebMouseEventButton, void>(int32_t);
template<> bool isValidEnum<WebKit::WebMouseEventSyntheticClickType, void>(uint8_t);
template<> bool isValidEnum<WebKit::WebsiteMetaViewportPolicy, void>(uint8_t);
template<> bool isValidEnum<WebKit::WebsiteMediaSourcePolicy, void>(uint8_t);
template<> bool isValidEnum<WebKit::WebsiteSimulatedMouseEventsDispatchPolicy, void>(uint8_t);
template<> bool isValidEnum<WebKit::WebsiteLegacyOverflowScrollingTouchPolicy, void>(uint8_t);
#if ENABLE(WK_WEB_EXTENSIONS)
template<> bool isValidEnum<WebKit::WebExtensionEventListenerType, void>(uint8_t);
#endif
#if ENABLE(GPU_PROCESS)
template<> bool isValidEnum<WebCore::WebGPU::FeatureName, void>(uint8_t);
#endif
template<> bool isValidOptionSet<WebKit::WebsiteDataFetchOption>(OptionSet<WebKit::WebsiteDataFetchOption>);
template<> bool isValidOptionSet<WebKit::WebsiteDataType>(OptionSet<WebKit::WebsiteDataType>);
#if ENABLE(WEBXR)
template<> bool isValidEnum<PlatformXR::SessionFeature, void>(uint8_t);
#endif

} // namespace WTF
