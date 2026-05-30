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

#include "config.h"
#include "SerializedTypeInfo.h"

#include "APIError.h"
#include "APIFrameHandle.h"
#include "APIGeometry.h"
#include "APIPageHandle.h"
#include "APIURL.h"
#include "APIURLRequest.h"
#include "APIURLResponse.h"
#include "ArgumentCoders.h"
#if OS(DARWIN)
#include "ArgumentCodersDarwin.h"
#endif
#if USE(SOUP)
#include "ArgumentCodersGLib.h"
#endif
#if USE(UNIX_DOMAIN_SOCKETS)
#include "ArgumentCodersUnix.h"
#endif
#if OS(WINDOWS)
#include "ArgumentCodersWin.h"
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
#include "AudioTrackPrivateRemoteConfiguration.h"
#endif
#include "AuxiliaryProcessCreationParameters.h"
#include "BackgroundFetchState.h"
#if ENABLE(SERVICE_WORKER)
#include "BackgroundFetchState.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "BufferIdentifierSet.h"
#endif
#include "CacheModel.h"
#include "CallbackID.h"
#include "Decoder.h"
#include "EditorState.h"
#include "Encoder.h"
#include "FileSystemSyncAccessHandleInfo.h"
#include "FocusedElementInformation.h"
#include "FrameInfoData.h"
#include "FrameTreeCreationParameters.h"
#include "FrameTreeNodeData.h"
#if ENABLE(GPU_PROCESS)
#include "GPUProcessConnectionParameters.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "GPUProcessSessionParameters.h"
#endif
#if ENABLE(GAMEPAD)
#include "GamepadData.h"
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
#include "InitializationSegmentInfo.h"
#endif
#include "LayerTreeContext.h"
#include "LocalFrameCreationParameters.h"
#if ENABLE(GPU_PROCESS) && ENABLE(MEDIA_SOURCE)
#include "MediaDescriptionInfo.h"
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
#include "ModelIdentifier.h"
#endif
#include "NavigationActionData.h"
#include "NetworkLoadParameters.h"
#include "NetworkProcessConnectionParameters.h"
#include "NetworkProcessCreationParameters.h"
#include "NetworkResourceLoadParameters.h"
#include "PlatformPopupMenuData.h"
#include "PolicyDecision.h"
#if ENABLE(GPU_PROCESS) && PLATFORM(COCOA)
#include "PrepareBackingStoreBuffersData.h"
#endif
#if ENABLE(GPU_PROCESS) && USE(AUDIO_SESSION)
#include "RemoteAudioSessionConfiguration.h"
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)
#include "RemoteCDMConfiguration.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "RemoteGPURequestAdapterResponse.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "RemoteMediaPlayerConfiguration.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "RemoteMediaPlayerProxyConfiguration.h"
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
#include "RemoteMediaPlayerState.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "RemoteRenderingBackendCreationParameters.h"
#endif
#include "RemoteWorkerType.h"
#include "SameDocumentNavigationType.h"
#include "SessionState.h"
#include "ShareableBitmap.h"
#include "SharedMemory.h"
#include "StreamConnectionEncoder.h"
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
#include "TextTrackPrivateRemoteConfiguration.h"
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
#include "TrackPrivateRemoteConfiguration.h"
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
#include "UpdateInfo.h"
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
#include "VideoTrackPrivateRemoteConfiguration.h"
#endif
#include "WebCoreArgumentCoders.h"
#include "WebEvent.h"
#if ENABLE(GPU_PROCESS)
#include "WebGPUBindGroupDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUBindGroupEntry.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUBindGroupLayoutDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUBindGroupLayoutEntry.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUBlendComponent.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUBlendState.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUBufferBinding.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUBufferBindingLayout.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUBufferDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUCanvasConfiguration.h"
#endif
#include "WebGPUColor.h"
#if ENABLE(GPU_PROCESS)
#include "WebGPUColorTargetState.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUCommandBufferDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUCommandEncoderDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUCompilationMessage.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUComputePassDescriptor.h"
#endif
#include "WebGPUComputePassTimestampWrites.h"
#if ENABLE(GPU_PROCESS)
#include "WebGPUComputePipelineDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUDepthStencilState.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUDeviceDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUExtent3D.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUExternalTextureBindingLayout.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUExternalTextureDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUFragmentState.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUImageCopyBuffer.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUImageCopyExternalImage.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUImageCopyTexture.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUImageCopyTextureTagged.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUImageDataLayout.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUMultisampleState.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUObjectDescriptorBase.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUOrigin2D.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUOrigin3D.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUOutOfMemoryError.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUPipelineDescriptorBase.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUPipelineLayoutDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUPresentationContextDescriptor.h"
#endif
#include "WebGPUPrimitiveState.h"
#if ENABLE(GPU_PROCESS)
#include "WebGPUPrimitiveState.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUProgrammableStage.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUQuerySetDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPURenderBundleDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPURenderBundleEncoderDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPURenderPassColorAttachment.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPURenderPassDepthStencilAttachment.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPURenderPassDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPURenderPassLayout.h"
#endif
#include "WebGPURenderPassTimestampWrites.h"
#if ENABLE(GPU_PROCESS)
#include "WebGPURenderPipelineDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPURequestAdapterOptions.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUSamplerBindingLayout.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUSamplerDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUShaderModuleCompilationHint.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUShaderModuleDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUStencilFaceState.h"
#endif
#include "WebGPUStorageTextureBindingLayout.h"
#if ENABLE(GPU_PROCESS)
#include "WebGPUStorageTextureBindingLayout.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUSupportedFeatures.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUSupportedLimits.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUTextureBindingLayout.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUTextureDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUTextureViewDescriptor.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUValidationError.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUVertexAttribute.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUVertexBufferLayout.h"
#endif
#if ENABLE(GPU_PROCESS)
#include "WebGPUVertexState.h"
#endif
#if ENABLE(MAC_GESTURE_EVENTS)
#include "WebGestureEvent.h"
#endif
#include "WebHitTestResultData.h"
#include "WebIDBResult.h"
#include "WebKeyboardEvent.h"
#include "WebMouseEvent.h"
#include "WebPageCreationParameters.h"
#include "WebPopupItem.h"
#include "WebProcessCreationParameters.h"
#include "WebProcessDataStoreParameters.h"
#include "WebPushDaemonConnectionConfiguration.h"
#include "WebPushMessage.h"
#if ENABLE(SPEECH_SYNTHESIS)
#include "WebSpeechSynthesisVoice.h"
#endif
#if ENABLE(TOUCH_EVENTS)
#include "WebTouchEvent.h"
#endif
#include "WebWheelEvent.h"
#include "WebsiteData.h"
#include "WebsiteDataFetchOption.h"
#include "WebsiteDataStoreParameters.h"
#include "WebsiteDataType.h"
#include "WebsitePoliciesData.h"
#if USE(CG)
#include <CoreGraphics/CGAffineTransform.h>
#endif
#if USE(CG)
#include <CoreGraphics/CGGeometry.h>
#endif
#include <JavaScriptCore/ArrayBuffer.h>
#if USE(SYSTEM_PREVIEW)
#include <WebCore/ARKitBadgeSystemImage.h>
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
#include <WebCore/AcceleratedEffect.h>
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
#include <WebCore/AcceleratedEffectValues.h>
#endif
#include <WebCore/AffineTransform.h>
#if ENABLE(APP_HIGHLIGHTS)
#include <WebCore/AppHighlight.h>
#endif
#if USE(APPKIT)
#include <WebCore/AppKitControlSystemImage.h>
#endif
#if ENABLE(APPLE_PAY_AMS_UI) && ENABLE(PAYMENT_REQUEST)
#include <WebCore/ApplePayAMSUIRequest.h>
#endif
#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_PAYMENTS)
#include <WebCore/ApplePayAutomaticReloadPaymentRequest.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePayButtonPart.h>
#endif
#if ENABLE(APPLE_PAY_COUPON_CODE)
#include <WebCore/ApplePayCouponCodeUpdate.h>
#endif
#if ENABLE(APPLE_PAY_SHIPPING_METHOD_DATE_COMPONENTS_RANGE)
#include <WebCore/ApplePayDateComponents.h>
#endif
#if ENABLE(APPLE_PAY_SHIPPING_METHOD_DATE_COMPONENTS_RANGE)
#include <WebCore/ApplePayDateComponentsRange.h>
#endif
#if ENABLE(APPLE_PAY_DEFERRED_PAYMENTS)
#include <WebCore/ApplePayDeferredPaymentRequest.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePayDetailsUpdateBase.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePayError.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePayFeature.h>
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
#include <WebCore/ApplePayInstallmentConfigurationWebCore.h>
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
#include <WebCore/ApplePayInstallmentItem.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePayLineItem.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePayLogoSystemImage.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePayPaymentAuthorizationResult.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePayPaymentMethodUpdate.h>
#endif
#if ENABLE(APPLE_PAY_PAYMENT_ORDER_DETAILS)
#include <WebCore/ApplePayPaymentOrderDetails.h>
#endif
#if ENABLE(APPLE_PAY_MULTI_MERCHANT_PAYMENTS)
#include <WebCore/ApplePayPaymentTokenContext.h>
#endif
#if ENABLE(APPLE_PAY_RECURRING_PAYMENTS)
#include <WebCore/ApplePayRecurringPaymentRequest.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePaySetupConfiguration.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePayShippingContactUpdate.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePayShippingMethod.h>
#endif
#if ENABLE(APPLE_PAY)
#include <WebCore/ApplePayShippingMethodUpdate.h>
#endif
#if ENABLE(APPLICATION_MANIFEST)
#include <WebCore/ApplicationManifest.h>
#endif
#include <WebCore/AttributionSecondsUntilSendData.h>
#include <WebCore/AudioConfiguration.h>
#include <WebCore/AudioIOCallback.h>
#if USE(AUDIO_SESSION)
#include <WebCore/AudioSession.h>
#endif
#include <WebCore/AuthenticationChallenge.h>
#if ENABLE(WEB_AUTHN)
#include <WebCore/AuthenticationExtensionsClientInputs.h>
#endif
#if ENABLE(WEB_AUTHN)
#include <WebCore/AuthenticationExtensionsClientOutputs.h>
#endif
#include <WebCore/AutocapitalizeTypes.h>
#include <WebCore/Autofill.h>
#if ENABLE(SERVICE_WORKER)
#include <WebCore/BackgroundFetchInformation.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/BackgroundFetchOptions.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/BackgroundFetchRecordInformation.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/BackgroundFetchRequest.h>
#endif
#if ENABLE(GPU_PROCESS)
#include <WebCore/BarcodeDetectorOptionsInterface.h>
#endif
#if ENABLE(GPU_PROCESS)
#include <WebCore/BarcodeFormatInterface.h>
#endif
#include <WebCore/BasicShapes.h>
#include <WebCore/BufferSource.h>
#if ENABLE(ENCRYPTED_MEDIA)
#include <WebCore/CDMKeySystemConfiguration.h>
#endif
#if ENABLE(ENCRYPTED_MEDIA)
#include <WebCore/CDMMediaCapability.h>
#endif
#if ENABLE(ENCRYPTED_MEDIA)
#include <WebCore/CDMRestrictions.h>
#endif
#include <WebCore/COEPInheritenceViolationReportBody.h>
#include <WebCore/CORPViolationReportBody.h>
#include <WebCore/CSPViolationReportBody.h>
#include <WebCore/CSSValueKey.h>
#include <WebCore/CacheQueryOptions.h>
#include <WebCore/CanvasActivityRecord.h>
#if ENABLE(MEDIA_STREAM)
#include <WebCore/CaptureDevice.h>
#endif
#if ENABLE(MEDIA_STREAM)
#include <WebCore/CaptureDeviceWithCapabilities.h>
#endif
#if PLATFORM(MAC)
#include <WebCore/CaretAnimator.h>
#endif
#include <WebCore/CertificateInfo.h>
#include <WebCore/CharacterRange.h>
#include <WebCore/ClientOrigin.h>
#include <WebCore/ColorInterpolationMethod.h>
#include <WebCore/CompositionHighlight.h>
#include <WebCore/CompositionUnderline.h>
#include <WebCore/ContactInfo.h>
#include <WebCore/ContactsRequestData.h>
#if ENABLE(CONTENT_EXTENSIONS)
#include <WebCore/ContentRuleListResults.h>
#endif
#include <WebCore/ContentSecurityPolicy.h>
#include <WebCore/ContentType.h>
#include <WebCore/ControlStyle.h>
#include <WebCore/Cookie.h>
#include <WebCore/CookieConsentDecisionResult.h>
#include <WebCore/CookieRequestHeaderFieldProxy.h>
#include <WebCore/CookieStoreGetOptions.h>
#include <WebCore/CrossOriginEmbedderPolicy.h>
#include <WebCore/CrossOriginOpenerPolicy.h>
#include <WebCore/CustomHeaderFields.h>
#include <WebCore/DOMCacheEngine.h>
#include <WebCore/DOMPasteAccess.h>
#if ENABLE(DATA_DETECTION)
#include <WebCore/DataDetectorType.h>
#endif
#if ENABLE(DATALIST_ELEMENT)
#include <WebCore/DataListSuggestionInformation.h>
#endif
#include <WebCore/DatabaseDetails.h>
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
#include <WebCore/DateTimeChooserParameters.h>
#endif
#include <WebCore/DecomposedGlyphs.h>
#include <WebCore/DeprecationReportBody.h>
#include <WebCore/DestinationColorSpace.h>
#if ENABLE(WEB_RTC)
#include <WebCore/DetachedRTCDataChannel.h>
#endif
#if ENABLE(GPU_PROCESS)
#include <WebCore/DetectedBarcodeInterface.h>
#endif
#if ENABLE(GPU_PROCESS)
#include <WebCore/DetectedFaceInterface.h>
#endif
#if ENABLE(GPU_PROCESS)
#include <WebCore/DetectedTextInterface.h>
#endif
#include <WebCore/DeviceOrientationOrMotionPermissionState.h>
#include <WebCore/DiagnosticLoggingDomain.h>
#include <WebCore/DictationAlternative.h>
#include <WebCore/DictionaryPopupInfo.h>
#if HAVE(SCREEN_CAPTURE_KIT)
#include <WebCore/DisplayCapturePromptType.h>
#endif
#include <WebCore/DisplayListItems.h>
#include <WebCore/DistantLightSource.h>
#include <WebCore/DocumentLoader.h>
#if ENABLE(TRACKING_PREVENTION)
#include <WebCore/DocumentStorageAccess.h>
#endif
#include <WebCore/DragData.h>
#if ENABLE(DRAG_SUPPORT)
#include <WebCore/DragData.h>
#endif
#include <WebCore/ElementAnimationContext.h>
#include <WebCore/ElementContext.h>
#include <WebCore/EventInit.h>
#include <WebCore/EventRegion.h>
#include <WebCore/EventTrackingRegions.h>
#include <WebCore/Exception.h>
#include <WebCore/ExceptionData.h>
#include <WebCore/ExceptionDetails.h>
#include <WebCore/FEBlend.h>
#include <WebCore/FEColorMatrix.h>
#include <WebCore/FEComponentTransfer.h>
#include <WebCore/FEComposite.h>
#include <WebCore/FEConvolveMatrix.h>
#include <WebCore/FEDiffuseLighting.h>
#include <WebCore/FEDisplacementMap.h>
#include <WebCore/FEDropShadow.h>
#include <WebCore/FEFlood.h>
#include <WebCore/FEGaussianBlur.h>
#include <WebCore/FEImage.h>
#include <WebCore/FEMerge.h>
#include <WebCore/FEMorphology.h>
#include <WebCore/FEOffset.h>
#include <WebCore/FESpecularLighting.h>
#include <WebCore/FETurbulence.h>
#if ENABLE(GPU_PROCESS)
#include <WebCore/FaceDetectorOptionsInterface.h>
#endif
#include <WebCore/FetchOptions.h>
#include <WebCore/FileChooser.h>
#include <WebCore/FilterEffectGeometry.h>
#include <WebCore/FloatPoint.h>
#include <WebCore/FloatPoint3D.h>
#include <WebCore/FloatQuad.h>
#include <WebCore/FloatRect.h>
#include <WebCore/FloatRoundedRect.h>
#include <WebCore/FloatSize.h>
#include <WebCore/FocusDirection.h>
#include <WebCore/FontAttributeChanges.h>
#include <WebCore/FontAttributes.h>
#include <WebCore/FontShadow.h>
#include <WebCore/FormData.h>
#include <WebCore/FourCC.h>
#include <WebCore/FrameLoaderTypes.h>
#if ENABLE(GAMEPAD)
#include <WebCore/GamepadEffectParameters.h>
#endif
#if ENABLE(GAMEPAD)
#include <WebCore/GamepadHapticEffectType.h>
#endif
#include <WebCore/GeolocationPositionData.h>
#include <WebCore/GlobalFrameIdentifier.h>
#include <WebCore/GlobalWindowIdentifier.h>
#include <WebCore/Gradient.h>
#include <WebCore/GradientColorStop.h>
#include <WebCore/GradientColorStops.h>
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
#include <WebCore/GraphicsContextGLActiveInfo.h>
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
#include <WebCore/GraphicsContextGLAttributes.h>
#endif
#include <WebCore/GraphicsStyle.h>
#include <WebCore/GraphicsTypes.h>
#include <WebCore/HTMLModelElementCamera.h>
#include <WebCore/HTTPCookieAcceptPolicy.h>
#include <WebCore/HTTPHeaderField.h>
#include <WebCore/HTTPHeaderMap.h>
#include <WebCore/IDBCursorInfo.h>
#include <WebCore/IDBCursorRecord.h>
#include <WebCore/IDBDatabaseIdentifier.h>
#include <WebCore/IDBDatabaseInfo.h>
#include <WebCore/IDBDatabaseNameAndVersion.h>
#include <WebCore/IDBError.h>
#include <WebCore/IDBGetAllRecordsData.h>
#include <WebCore/IDBGetAllResult.h>
#include <WebCore/IDBGetRecordData.h>
#include <WebCore/IDBGetResult.h>
#include <WebCore/IDBIndexInfo.h>
#include <WebCore/IDBIterateCursorData.h>
#include <WebCore/IDBKeyData.h>
#include <WebCore/IDBKeyRangeData.h>
#include <WebCore/IDBObjectStoreInfo.h>
#include <WebCore/IDBRequestData.h>
#include <WebCore/IDBResourceIdentifier.h>
#include <WebCore/IDBResultData.h>
#include <WebCore/IDBTransactionInfo.h>
#include <WebCore/IDBValue.h>
#include <WebCore/ISOVTTCue.h>
#include <WebCore/IdentityTransformOperation.h>
#include <WebCore/ImageBufferBackendParameters.h>
#include <WebCore/ImageDecoder.h>
#include <WebCore/ImageOrientation.h>
#include <WebCore/ImagePaintingOptions.h>
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ImageResource.h>
#endif
#if ENABLE(VIDEO)
#include <WebCore/InbandGenericCue.h>
#endif
#include <WebCore/IntPoint.h>
#include <WebCore/IntRect.h>
#include <WebCore/IntSize.h>
#include <WebCore/InteractionRegion.h>
#include <WebCore/KeyboardScroll.h>
#if ENABLE(GPU_PROCESS)
#include <WebCore/LandmarkInterface.h>
#endif
#if ENABLE(GPU_PROCESS)
#include <WebCore/LandmarkTypeInterface.h>
#endif
#include <WebCore/LayoutPoint.h>
#include <WebCore/LayoutRect.h>
#include <WebCore/LayoutSize.h>
#include <WebCore/LayoutUnit.h>
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
#include <WebCore/LengthPoint.h>
#endif
#include <WebCore/LengthSize.h>
#include <WebCore/LinkIcon.h>
#include <WebCore/ListStyleType.h>
#include <WebCore/LoadSchedulingMode.h>
#include <WebCore/Matrix3DTransformOperation.h>
#include <WebCore/MatrixTransformOperation.h>
#include <WebCore/MediaCapabilitiesDecodingInfo.h>
#include <WebCore/MediaCapabilitiesEncodingInfo.h>
#include <WebCore/MediaCapabilitiesInfo.h>
#include <WebCore/MediaConfiguration.h>
#if ENABLE(MEDIA_STREAM)
#include <WebCore/MediaConstraints.h>
#endif
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS) && USE(UICONTEXTMENU)
#include <WebCore/MediaControlsContextMenuItem.h>
#endif
#include <WebCore/MediaDecodingConfiguration.h>
#include <WebCore/MediaDeviceHashSalts.h>
#include <WebCore/MediaEncodingConfiguration.h>
#if ENABLE(VIDEO)
#include <WebCore/MediaPlayer.h>
#endif
#if ENABLE(MEDIA_SESSION)
#include <WebCore/MediaPositionState.h>
#endif
#include <WebCore/MediaProducer.h>
#include <WebCore/MediaSelectionOption.h>
#if ENABLE(MEDIA_SESSION)
#include <WebCore/MediaSessionAction.h>
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
#include <WebCore/MediaSessionCoordinatorState.h>
#endif
#if ENABLE(MEDIA_SESSION)
#include <WebCore/MediaSessionPlaybackState.h>
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
#include <WebCore/MediaSessionReadyState.h>
#endif
#include <WebCore/MediaStreamRequest.h>
#if ! ENABLE(MEDIA_STREAM)
#include <WebCore/MediaStreamRequest.h>
#endif
#if ENABLE(MEDIA_STREAM)
#include <WebCore/MediaStreamRequest.h>
#endif
#include <WebCore/MessagePortIdentifier.h>
#include <WebCore/MessageWithMessagePorts.h>
#include <WebCore/MeterPart.h>
#if ENABLE(CONTENT_FILTERING)
#include <WebCore/MockContentFilterSettings.h>
#endif
#if ENABLE(MEDIA_STREAM)
#include <WebCore/MockMediaDevice.h>
#endif
#if ENABLE(WEB_AUTHN)
#include <WebCore/MockWebAuthenticationConfiguration.h>
#endif
#include <WebCore/ModalContainerTypes.h>
#include <WebCore/Model.h>
#if ENABLE(SERVICE_WORKER)
#include <WebCore/NavigationPreloadState.h>
#endif
#include <WebCore/NavigationRequester.h>
#include <WebCore/NetworkLoadInformation.h>
#include <WebCore/NotificationData.h>
#include <WebCore/NotificationResources.h>
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
#include <WebCore/OffsetRotation.h>
#endif
#include <WebCore/Pasteboard.h>
#include <WebCore/PasteboardCustomData.h>
#include <WebCore/PasteboardItemInfo.h>
#include <WebCore/PathOperation.h>
#include <WebCore/PathSegment.h>
#include <WebCore/PathSegmentData.h>
#include <WebCore/Pattern.h>
#if ENABLE(APPLE_PAY_INSTALLMENTS)
#include <WebCore/PaymentInstallmentConfigurationWebCore.h>
#endif
#include <WebCore/PermissionDescriptor.h>
#include <WebCore/PermissionQuerySource.h>
#include <WebCore/PermissionState.h>
#include <WebCore/PerspectiveTransformOperation.h>
#include <WebCore/PixelBufferFormat.h>
#if ENABLE(VIDEO)
#include <WebCore/PlatformAudioTrackConfiguration.h>
#endif
#if !USE(CG)
#include <WebCore/PlatformColorSpace.h>
#endif
#include <WebCore/PlatformTimeRanges.h>
#if ENABLE(VIDEO)
#include <WebCore/PlatformTrackConfiguration.h>
#endif
#include <WebCore/PlatformVideoColorSpace.h>
#if ENABLE(VIDEO)
#include <WebCore/PlatformVideoTrackConfiguration.h>
#endif
#include <WebCore/PlatformWheelEvent.h>
#include <WebCore/PluginData.h>
#include <WebCore/PointLightSource.h>
#include <WebCore/PolicyContainer.h>
#include <WebCore/PositionedGlyphs.h>
#include <WebCore/PrivateClickMeasurement.h>
#include <WebCore/ProcessIdentity.h>
#include <WebCore/ProgressBarPart.h>
#include <WebCore/PromisedAttachmentInfo.h>
#include <WebCore/ProtectionSpace.h>
#include <WebCore/PublicKeyCredentialCreationOptions.h>
#if ENABLE(WEB_AUTHN)
#include <WebCore/PublicKeyCredentialDescriptor.h>
#endif
#include <WebCore/PublicKeyCredentialRequestOptions.h>
#if ENABLE(SERVICE_WORKER)
#include <WebCore/PushPermissionState.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/PushSubscriptionData.h>
#endif
#if ENABLE(WEB_RTC)
#include <WebCore/RTCDataChannelHandler.h>
#endif
#if ENABLE(WEB_RTC)
#include <WebCore/RTCDataChannelIdentifier.h>
#endif
#include <WebCore/RTCErrorDetailType.h>
#if ENABLE(MEDIA_STREAM)
#include <WebCore/RealtimeMediaSource.h>
#endif
#if ENABLE(MEDIA_STREAM)
#include <WebCore/RealtimeMediaSourceCapabilities.h>
#endif
#if ENABLE(MEDIA_STREAM)
#include <WebCore/RealtimeMediaSourceSettings.h>
#endif
#if ENABLE(MEDIA_STREAM)
#include <WebCore/RealtimeMediaSourceSupportedConstraints.h>
#endif
#include <WebCore/RectEdges.h>
#include <WebCore/Region.h>
#include <WebCore/RegistrableDomain.h>
#include <WebCore/RenderStyleConstants.h>
#include <WebCore/RenderTreeAsText.h>
#include <WebCore/Report.h>
#include <WebCore/ReportBody.h>
#include <WebCore/ResourceLoadStatistics.h>
#include <WebCore/ResourceLoaderOptions.h>
#include <WebCore/ResourceRequest.h>
#if !USE(CURL) && !PLATFORM(COCOA)
#include <WebCore/ResourceRequest.h>
#endif
#if PLATFORM(COCOA)
#include <WebCore/ResourceRequest.h>
#endif
#if USE(CURL)
#include <WebCore/ResourceRequest.h>
#endif
#if USE(SOUP)
#include <WebCore/ResourceRequest.h>
#endif
#include <WebCore/ResourceResponse.h>
#include <WebCore/ResourceResponseBase.h>
#include <WebCore/RetrieveRecordsOptions.h>
#include <WebCore/RotateTransformOperation.h>
#include <WebCore/SVGFilterExpression.h>
#include <WebCore/SVGPathByteStream.h>
#include <WebCore/SVGPreserveAspectRatioValue.h>
#include <WebCore/SameSiteInfo.h>
#include <WebCore/ScaleTransformOperation.h>
#include <WebCore/ScreenOrientationLockType.h>
#include <WebCore/ScreenOrientationType.h>
#include <WebCore/ScreenProperties.h>
#include <WebCore/ScrollTypes.h>
#include <WebCore/ScrollingConstraints.h>
#include <WebCore/ScrollingCoordinatorTypes.h>
#if ENABLE(ASYNC_SCROLLING)
#include <WebCore/ScrollingStateNode.h>
#endif
#include <WebCore/SearchPopupMenu.h>
#include <WebCore/SecurityOrigin.h>
#include <WebCore/SecurityOriginData.h>
#include <WebCore/SecurityPolicyViolationEvent.h>
#include <WebCore/SecurityPolicyViolationEventDisposition.h>
#if PLATFORM(IOS_FAMILY)
#include <WebCore/SelectionGeometry.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ServiceWorkerClientData.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ServiceWorkerClientPendingMessage.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ServiceWorkerClientQueryOptions.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ServiceWorkerContextData.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ServiceWorkerData.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ServiceWorkerImportedScript.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ServiceWorkerJobData.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ServiceWorkerJobDataIdentifier.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ServiceWorkerRegistrationData.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ServiceWorkerRegistrationKey.h>
#endif
#if ENABLE(SERVICE_WORKER)
#include <WebCore/ServiceWorkerRegistrationOptions.h>
#endif
#include <WebCore/ShareData.h>
#include <WebCore/SharedWorkerKey.h>
#include <WebCore/ShouldTreatAsContinuingLoad.h>
#include <WebCore/SkewTransformOperation.h>
#include <WebCore/SliderTrackPart.h>
#include <WebCore/SourceBrush.h>
#include <WebCore/SourceImage.h>
#include <WebCore/SpeechRecognitionError.h>
#include <WebCore/SpeechRecognitionRequestInfo.h>
#include <WebCore/SpeechRecognitionResultData.h>
#include <WebCore/SpeechRecognitionUpdate.h>
#include <WebCore/SpotLightSource.h>
#include <WebCore/StorageEstimate.h>
#include <WebCore/StorageType.h>
#include <WebCore/SubstituteData.h>
#include <WebCore/TestReportBody.h>
#include <WebCore/TextChecking.h>
#include <WebCore/TextGranularity.h>
#include <WebCore/TextIndicator.h>
#include <WebCore/TextManipulationController.h>
#include <WebCore/TextManipulationItem.h>
#include <WebCore/TextManipulationToken.h>
#if ENABLE(IMAGE_ANALYSIS)
#include <WebCore/TextRecognitionResult.h>
#endif
#include <WebCore/TimingFunction.h>
#include <WebCore/TransformOperation.h>
#include <WebCore/TransformOperations.h>
#include <WebCore/TransformationMatrix.h>
#include <WebCore/TranslateTransformOperation.h>
#if HAVE(TRANSLATION_UI_SERVICES) && ENABLE(CONTEXT_MENUS)
#include <WebCore/TranslationContextMenuInfo.h>
#endif
#include <WebCore/UserStyleSheet.h>
#include <WebCore/VP9Utilities.h>
#include <WebCore/VelocityData.h>
#if ENABLE(VIDEO)
#include <WebCore/VideoFrame.h>
#endif
#if ENABLE(VIDEO) && USE(AVFOUNDATION)
#include <WebCore/VideoFrameCV.h>
#endif
#if ENABLE(VIDEO)
#include <WebCore/VideoFrameMetadata.h>
#endif
#include <WebCore/VideoFrameTimeMetadata.h>
#if ENABLE(VIDEO)
#include <WebCore/VideoPlaybackQualityMetrics.h>
#endif
#if ENABLE(MEDIA_STREAM)
#include <WebCore/VideoPreset.h>
#endif
#include <WebCore/ViewportArguments.h>
#include <WebCore/VisibleSelection.h>
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
#include <WebCore/WebAnimationTypes.h>
#endif
#include <WebCore/WebCodecsEncodedVideoChunk.h>
#if ENABLE(WEB_CODECS)
#include <WebCore/WebCodecsEncodedVideoChunkData.h>
#endif
#if ENABLE(GPU_PROCESS)
#include <WebCore/WebGPUExternalTextureDescriptor.h>
#endif
#include <WebCore/WebGPUPredefinedColorSpace.h>
#include <WebCore/WebGPUTextureAspect.h>
#include <WebCore/WebGPUTextureFormat.h>
#include <WebCore/WebLockManagerSnapshot.h>
#include <WebCore/WindowFeatures.h>
#include <WebCore/WorkerFetchResult.h>
#include <WebCore/WorkerInitializationData.h>
#include <WebCore/WorkerOptions.h>
#include <WebCore/WritingDirection.h>
#if ENABLE(WK_WEB_EXTENSIONS)
#include <WebKit/WebExtensionEventListenerType.h>
#endif
#include <wtf/ArgumentCoder.h>
#if OS(DARWIN)
#include <wtf/MachSendRight.h>
#endif
#include <wtf/MediaTime.h>
#include <wtf/MonotonicTime.h>
#include <wtf/RefCounted.h>
#if ENABLE(SERVICE_WORKER)
#include <wtf/RobinHoodHashTable.h>
#endif
#include <wtf/Seconds.h>
#include <wtf/URL.h>
#include <wtf/WallTime.h>
#include <wtf/text/AtomString.h>
#if USE(UNIX_DOMAIN_SOCKETS)
#include <wtf/unix/UnixFileDescriptor.h>
#endif
#if OS(WINDOWS)
#include <wtf/win/Win32Handle.h>
#endif

#if ENABLE(IPC_TESTING_API)

namespace WebKit {

Vector<SerializedTypeInfo> allSerializedTypes()
{
    return {
        { "WebKit::GPUProcessSessionParameters"_s, {
            {
                "String"_s,
                "mediaCacheDirectory"_s
            },
            {
                "WebKit::SandboxExtension::Handle"_s,
                "mediaCacheDirectorySandboxExtensionHandle"_s
            },
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
            {
                "String"_s,
                "mediaKeysStorageDirectory"_s
            },
#endif
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
            {
                "WebKit::SandboxExtension::Handle"_s,
                "mediaKeysStorageDirectorySandboxExtensionHandle"_s
            },
#endif
        } },
        { "WebCore::PathMoveTo"_s, {
            {
                "WebCore::FloatPoint"_s,
                "point"_s
            },
        } },
        { "WebCore::PathLineTo"_s, {
            {
                "WebCore::FloatPoint"_s,
                "point"_s
            },
        } },
        { "WebCore::PathQuadCurveTo"_s, {
            {
                "WebCore::FloatPoint"_s,
                "controlPoint"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "endPoint"_s
            },
        } },
        { "WebCore::PathBezierCurveTo"_s, {
            {
                "WebCore::FloatPoint"_s,
                "controlPoint1"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "controlPoint2"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "endPoint"_s
            },
        } },
        { "WebCore::PathArcTo"_s, {
            {
                "WebCore::FloatPoint"_s,
                "controlPoint1"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "controlPoint2"_s
            },
            {
                "float"_s,
                "radius"_s
            },
        } },
        { "WebCore::PathArc"_s, {
            {
                "WebCore::FloatPoint"_s,
                "center"_s
            },
            {
                "float"_s,
                "radius"_s
            },
            {
                "float"_s,
                "startAngle"_s
            },
            {
                "float"_s,
                "endAngle"_s
            },
            {
                "WebCore::RotationDirection"_s,
                "direction"_s
            },
        } },
        { "WebCore::PathEllipse"_s, {
            {
                "WebCore::FloatPoint"_s,
                "center"_s
            },
            {
                "float"_s,
                "radiusX"_s
            },
            {
                "float"_s,
                "radiusY"_s
            },
            {
                "float"_s,
                "rotation"_s
            },
            {
                "float"_s,
                "startAngle"_s
            },
            {
                "float"_s,
                "endAngle"_s
            },
            {
                "WebCore::RotationDirection"_s,
                "direction"_s
            },
        } },
        { "WebCore::PathEllipseInRect"_s, {
            {
                "WebCore::FloatRect"_s,
                "rect"_s
            },
        } },
        { "WebCore::PathRect"_s, {
            {
                "WebCore::FloatRect"_s,
                "rect"_s
            },
        } },
        { "WebCore::PathRoundedRect"_s, {
            {
                "WebCore::FloatRoundedRect"_s,
                "roundedRect"_s
            },
            {
                "WebCore::PathRoundedRect::Strategy"_s,
                "strategy"_s
            },
        } },
        { "WebCore::PathDataLine"_s, {
            {
                "WebCore::FloatPoint"_s,
                "start"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "end"_s
            },
        } },
        { "WebCore::PathDataQuadCurve"_s, {
            {
                "WebCore::FloatPoint"_s,
                "start"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "controlPoint"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "endPoint"_s
            },
        } },
        { "WebCore::PathDataBezierCurve"_s, {
            {
                "WebCore::FloatPoint"_s,
                "start"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "controlPoint1"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "controlPoint2"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "endPoint"_s
            },
        } },
        { "WebCore::PathDataArc"_s, {
            {
                "WebCore::FloatPoint"_s,
                "start"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "controlPoint1"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "controlPoint2"_s
            },
            {
                "float"_s,
                "radius"_s
            },
        } },
        { "WebCore::PathCloseSubpath"_s, {
        } },
        { "WebCore::PathSegment"_s, {
            {
                "WebCore::PathSegment::Data"_s,
                "data()"_s
            },
        } },
        { "WebKit::RemoteRenderingBackendCreationParameters"_s, {
            {
                "WebKit::RenderingBackendIdentifier"_s,
                "identifier"_s
            },
            {
                "WebKit::WebPageProxyIdentifier"_s,
                "pageProxyID"_s
            },
            {
                "WebCore::PageIdentifier"_s,
                "pageID"_s
            },
        } },
        { "WebKit::RemoteGPURequestAdapterResponse"_s, {
            {
                "String"_s,
                "name"_s
            },
            {
                "WebKit::WebGPU::SupportedFeatures"_s,
                "features"_s
            },
            {
                "WebKit::WebGPU::SupportedLimits"_s,
                "limits"_s
            },
            {
                "bool"_s,
                "isFallbackAdapter"_s
            },
        } },
        { "WebKit::AudioTrackPrivateRemoteConfiguration"_s, {
            {
                "bool"_s,
                "enabled"_s
            },
            {
                "WebCore::AudioTrackPrivate::Kind"_s,
                "kind"_s
            },
            {
                "WebCore::PlatformAudioTrackConfiguration"_s,
                "trackConfiguration"_s
            },
        } },
        { "WebKit::InitializationSegmentInfo"_s, {
            {
                "MediaTime"_s,
                "duration"_s
            },
            {
                "Vector<WebKit::InitializationSegmentInfo::TrackInformation>"_s,
                "audioTracks"_s
            },
            {
                "Vector<WebKit::InitializationSegmentInfo::TrackInformation>"_s,
                "videoTracks"_s
            },
            {
                "Vector<WebKit::InitializationSegmentInfo::TrackInformation>"_s,
                "textTracks"_s
            },
        } },
        { "WebKit::InitializationSegmentInfo::TrackInformation"_s, {
            {
                "WebKit::MediaDescriptionInfo"_s,
                "description"_s
            },
            {
                "WebKit::TrackPrivateRemoteIdentifier"_s,
                "identifier"_s
            },
        } },
        { "WebKit::MediaDescriptionInfo"_s, {
            {
                "AtomString"_s,
                "m_codec"_s
            },
            {
                "bool"_s,
                "m_isVideo"_s
            },
            {
                "bool"_s,
                "m_isAudio"_s
            },
            {
                "bool"_s,
                "m_isText"_s
            },
        } },
        { "WebKit::RemoteMediaPlayerProxyConfiguration"_s, {
            {
                "String"_s,
                "referrer"_s
            },
            {
                "String"_s,
                "userAgent"_s
            },
            {
                "String"_s,
                "sourceApplicationIdentifier"_s
            },
            {
                "String"_s,
                "networkInterfaceName"_s
            },
            {
                "Vector<WebCore::ContentType>"_s,
                "mediaContentTypesRequiringHardwareSupport"_s
            },
            {
                "std::optional<Vector<String>>"_s,
                "allowedMediaContainerTypes"_s
            },
            {
                "std::optional<Vector<String>>"_s,
                "allowedMediaCodecTypes"_s
            },
            {
                "std::optional<Vector<WebCore::FourCC>>"_s,
                "allowedMediaVideoCodecIDs"_s
            },
            {
                "std::optional<Vector<WebCore::FourCC>>"_s,
                "allowedMediaAudioCodecIDs"_s
            },
            {
                "std::optional<Vector<WebCore::FourCC>>"_s,
                "allowedMediaCaptionFormatTypes"_s
            },
            {
                "WebCore::LayoutRect"_s,
                "playerContentBoxRect"_s
            },
            {
                "Vector<String>"_s,
                "preferredAudioCharacteristics"_s
            },
#if ENABLE(AVF_CAPTIONS)
            {
                "Vector<WebCore::PlatformTextTrackData>"_s,
                "outOfBandTrackData"_s
            },
#endif
            {
                "WebCore::SecurityOriginData"_s,
                "documentSecurityOrigin"_s
            },
            {
                "WebCore::IntSize"_s,
                "presentationSize"_s
            },
            {
                "WebCore::FloatSize"_s,
                "videoInlineSize"_s
            },
            {
                "uint64_t"_s,
                "logIdentifier"_s
            },
            {
                "bool"_s,
                "shouldUsePersistentCache"_s
            },
            {
                "bool"_s,
                "isVideo"_s
            },
            {
                "bool"_s,
                "renderingCanBeAccelerated"_s
            },
            {
                "bool"_s,
                "prefersSandboxedParsing"_s
            },
            {
                "bool"_s,
                "shouldDisableHDR"_s
            },
        } },
        { "WebKit::TextTrackPrivateRemoteConfiguration"_s, {
            {
                "AtomString"_s,
                "trackId"_s
            },
            {
                "AtomString"_s,
                "label"_s
            },
            {
                "AtomString"_s,
                "language"_s
            },
            {
                "AtomString"_s,
                "inBandMetadataTrackDispatchType"_s
            },
            {
                "MediaTime"_s,
                "startTimeVariance"_s
            },
            {
                "int"_s,
                "trackIndex"_s
            },
            {
                "WebCore::InbandTextTrackPrivate::CueFormat"_s,
                "cueFormat"_s
            },
            {
                "WebCore::InbandTextTrackPrivate::Kind"_s,
                "kind"_s
            },
            {
                "bool"_s,
                "isClosedCaptions"_s
            },
            {
                "bool"_s,
                "isSDH"_s
            },
            {
                "bool"_s,
                "containsOnlyForcedSubtitles"_s
            },
            {
                "bool"_s,
                "isMainProgramContent"_s
            },
            {
                "bool"_s,
                "isEasyToRead"_s
            },
            {
                "bool"_s,
                "isDefault"_s
            },
        } },
        { "WebKit::TrackPrivateRemoteConfiguration"_s, {
            {
                "AtomString"_s,
                "trackId"_s
            },
            {
                "AtomString"_s,
                "label"_s
            },
            {
                "AtomString"_s,
                "language"_s
            },
            {
                "MediaTime"_s,
                "startTimeVariance"_s
            },
            {
                "int"_s,
                "trackIndex"_s
            },
        } },
        { "WebKit::VideoTrackPrivateRemoteConfiguration"_s, {
            {
                "bool"_s,
                "selected"_s
            },
            {
                "WebCore::VideoTrackPrivate::Kind"_s,
                "kind"_s
            },
            {
                "WebCore::PlatformVideoTrackConfiguration"_s,
                "trackConfiguration"_s
            },
        } },
        { "WebKit::NetworkProcessCreationParameters"_s, {
            {
                "WebKit::AuxiliaryProcessCreationParameters"_s,
                "auxiliaryProcessParameters"_s
            },
            {
                "WebKit::CacheModel"_s,
                "cacheModel"_s
            },
#if PLATFORM(MAC) || PLATFORM(MACCATALYST)
            {
                "Vector<uint8_t>"_s,
                "uiProcessCookieStorageIdentifier"_s
            },
#endif
            {
                "bool"_s,
                "shouldSuppressMemoryPressureHandler"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredForCustomProtocols"_s
            },
#if PLATFORM(COCOA)
            {
                "String"_s,
                "uiProcessBundleIdentifier"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "RetainPtr<CFDataRef>"_s,
                "networkATSContext"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "strictSecureDecodingForAllObjCEnabled"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "isParentProcessFullWebBrowserOrRunningTest"_s
            },
#endif
#if USE(SOUP)
            {
                "WebCore::HTTPCookieAcceptPolicy"_s,
                "cookieAcceptPolicy"_s
            },
#endif
#if USE(SOUP)
            {
                "Vector<String>"_s,
                "languages"_s
            },
#endif
#if USE(SOUP)
            {
                "std::optional<MemoryPressureHandler::Configuration>"_s,
                "memoryPressureHandlerConfiguration"_s
            },
#endif
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsSecure"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsBypassingContentSecurityPolicy"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsLocal"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsNoAccess"_s
            },
            {
                "bool"_s,
                "enablePrivateClickMeasurement"_s
            },
            {
                "bool"_s,
                "ftpEnabled"_s
            },
#if ENABLE(BUILT_IN_NOTIFICATIONS)
            {
                "bool"_s,
                "builtInNotificationsEnabled"_s
            },
#endif
            {
                "Vector<WebKit::WebsiteDataStoreParameters>"_s,
                "websiteDataStoreParameters"_s
            },
            {
                "Vector<std::pair<WebCore::ProcessIdentifier, WebCore::RegistrableDomain>>"_s,
                "allowedFirstPartiesForCookies"_s
            },
            {
                "HashSet<String>"_s,
                "localhostAliasesForTesting"_s
            },
        } },
        { "WebKit::NetworkLoadParameters"_s, {
            {
                "WebKit::WebPageProxyIdentifier"_s,
                "webPageProxyID"_s
            },
            {
                "WebCore::PageIdentifier"_s,
                "webPageID"_s
            },
            {
                "WebCore::FrameIdentifier"_s,
                "webFrameID"_s
            },
            {
                "RefPtr<WebCore::SecurityOrigin>"_s,
                "topOrigin"_s
            },
            {
                "RefPtr<WebCore::SecurityOrigin>"_s,
                "sourceOrigin"_s
            },
            {
                "WTF::ProcessID"_s,
                "parentPID"_s
            },
            {
                "WebCore::ResourceRequest"_s,
                "request"_s
            },
            {
                "WebCore::ContentSniffingPolicy"_s,
                "contentSniffingPolicy"_s
            },
            {
                "WebCore::ContentEncodingSniffingPolicy"_s,
                "contentEncodingSniffingPolicy"_s
            },
            {
                "WebCore::StoredCredentialsPolicy"_s,
                "storedCredentialsPolicy"_s
            },
            {
                "WebCore::ClientCredentialPolicy"_s,
                "clientCredentialPolicy"_s
            },
            {
                "bool"_s,
                "shouldClearReferrerOnHTTPSToHTTPRedirect"_s
            },
            {
                "bool"_s,
                "needsCertificateInfo"_s
            },
            {
                "bool"_s,
                "isMainFrameNavigation"_s
            },
            {
                "bool"_s,
                "isMainResourceNavigationForAnyFrame"_s
            },
            {
                "WebCore::ShouldRelaxThirdPartyCookieBlocking"_s,
                "shouldRelaxThirdPartyCookieBlocking"_s
            },
            {
                "WebKit::PreconnectOnly"_s,
                "shouldPreconnectOnly"_s
            },
            {
                "std::optional<WebKit::NavigatingToAppBoundDomain>"_s,
                "isNavigatingToAppBoundDomain"_s
            },
            {
                "bool"_s,
                "hadMainFrameMainResourcePrivateRelayed"_s
            },
            {
                "bool"_s,
                "allowPrivacyProxy"_s
            },
            {
                "OptionSet<WebCore::AdvancedPrivacyProtections>"_s,
                "advancedPrivacyProtections"_s
            },
        } },
        { "WebKit::NetworkResourceLoadParameters"_s, {
            {
                "WebCore::ResourceLoaderIdentifier"_s,
                "identifier"_s
            },
            {
                "RefPtr<WebCore::FormData>"_s,
                "request.httpBody()"_s
            },
            {
                "std::optional<Vector<WebKit::SandboxExtension::Handle>>"_s,
                "sandboxExtensionsIfHttpBody()"_s
            },
            {
                "std::optional<WebKit::SandboxExtension::Handle>"_s,
                "sandboxExtensionIflocalFile()"_s
            },
            {
                "Seconds"_s,
                "maximumBufferingTime"_s
            },
            {
                "WebCore::FetchOptions"_s,
                "options"_s
            },
            {
                "std::optional<WebCore::ContentSecurityPolicyResponseHeaders>"_s,
                "cspResponseHeaders"_s
            },
            {
                "URL"_s,
                "parentFrameURL"_s
            },
            {
                "URL"_s,
                "frameURL"_s
            },
            {
                "WebCore::CrossOriginEmbedderPolicy"_s,
                "parentCrossOriginEmbedderPolicy"_s
            },
            {
                "WebCore::CrossOriginEmbedderPolicy"_s,
                "crossOriginEmbedderPolicy"_s
            },
            {
                "WebCore::HTTPHeaderMap"_s,
                "originalRequestHeaders"_s
            },
            {
                "bool"_s,
                "shouldRestrictHTTPResponseAccess"_s
            },
            {
                "WebCore::PreflightPolicy"_s,
                "preflightPolicy"_s
            },
            {
                "bool"_s,
                "shouldEnableCrossOriginResourcePolicy"_s
            },
            {
                "Vector<RefPtr<WebCore::SecurityOrigin>>"_s,
                "frameAncestorOrigins"_s
            },
            {
                "bool"_s,
                "pageHasResourceLoadClient"_s
            },
            {
                "std::optional<WebCore::FrameIdentifier>"_s,
                "parentFrameID"_s
            },
            {
                "bool"_s,
                "crossOriginAccessControlCheckEnabled"_s
            },
            {
                "URL"_s,
                "documentURL"_s
            },
            {
                "bool"_s,
                "isCrossOriginOpenerPolicyEnabled"_s
            },
            {
                "bool"_s,
                "isClearSiteDataHeaderEnabled"_s
            },
            {
                "bool"_s,
                "isDisplayingInitialEmptyDocument"_s
            },
            {
                "WebCore::SandboxFlags"_s,
                "effectiveSandboxFlags"_s
            },
            {
                "URL"_s,
                "openerURL"_s
            },
            {
                "WebCore::CrossOriginOpenerPolicy"_s,
                "sourceCrossOriginOpenerPolicy"_s
            },
            {
                "uint64_t"_s,
                "navigationID"_s
            },
            {
                "std::optional<WebCore::NavigationRequester>"_s,
                "navigationRequester"_s
            },
#if ENABLE(SERVICE_WORKER)
            {
                "WebCore::ServiceWorkersMode"_s,
                "serviceWorkersMode"_s
            },
#endif
#if ENABLE(SERVICE_WORKER)
            {
                "std::optional<WebCore::ServiceWorkerRegistrationIdentifier>"_s,
                "serviceWorkerRegistrationIdentifier"_s
            },
#endif
#if ENABLE(SERVICE_WORKER)
            {
                "OptionSet<WebCore::HTTPHeadersToKeepFromCleaning>"_s,
                "httpHeadersToKeep"_s
            },
#endif
#if ENABLE(SERVICE_WORKER)
            {
                "std::optional<WebCore::FetchIdentifier>"_s,
                "navigationPreloadIdentifier"_s
            },
#endif
#if ENABLE(CONTENT_EXTENSIONS)
            {
                "URL"_s,
                "mainDocumentURL"_s
            },
#endif
#if ENABLE(CONTENT_EXTENSIONS)
            {
                "std::optional<WebKit::UserContentControllerIdentifier>"_s,
                "userContentControllerIdentifier"_s
            },
#endif
            {
                "bool"_s,
                "linkPreconnectEarlyHintsEnabled"_s
            },
        } },
        { "WebKit::SharedMemoryHandle"_s, {
#if USE(UNIX_DOMAIN_SOCKETS)
            {
                "UnixFileDescriptor"_s,
                "m_handle"_s
            },
#endif
#if OS(DARWIN)
            {
                "MachSendRight"_s,
                "m_handle"_s
            },
#endif
#if OS(WINDOWS)
            {
                "Win32Handle"_s,
                "m_handle"_s
            },
#endif
            {
                "size_t"_s,
                "m_size"_s
            },
        } },
        { "WebKit::BackgroundFetchState"_s, {
            {
                "WebCore::SecurityOriginData"_s,
                "topOrigin"_s
            },
            {
                "URL"_s,
                "scope"_s
            },
            {
                "String"_s,
                "identifier"_s
            },
            {
                "WebCore::BackgroundFetchOptions"_s,
                "options"_s
            },
            {
                "uint64_t"_s,
                "downloadTotal"_s
            },
            {
                "uint64_t"_s,
                "downloaded"_s
            },
            {
                "uint64_t"_s,
                "uploadTotal"_s
            },
            {
                "uint64_t"_s,
                "uploaded"_s
            },
            {
                "WebCore::BackgroundFetchResult"_s,
                "result"_s
            },
            {
                "WebCore::BackgroundFetchFailureReason"_s,
                "failureReason"_s
            },
            {
                "bool"_s,
                "isPaused"_s
            },
        } },
        { "WebKit::CallbackID"_s, {
            {
                "uint64_t"_s,
                "m_id"_s
            },
        } },
        { "WebCore::DisplayList::SetState"_s, {
            {
                "WebCore::GraphicsContextState"_s,
                "state()"_s
            },
        } },
        { "WebCore::DisplayList::SetLineDash"_s, {
            {
                "WebCore::DashArray"_s,
                "dashArray()"_s
            },
            {
                "float"_s,
                "dashOffset()"_s
            },
        } },
        { "WebCore::DisplayList::ClipOutToPath"_s, {
            {
                "WebCore::Path"_s,
                "path()"_s
            },
        } },
        { "WebCore::DisplayList::ClipPath"_s, {
            {
                "WebCore::Path"_s,
                "path()"_s
            },
            {
                "WebCore::WindRule"_s,
                "windRule()"_s
            },
        } },
        { "WebCore::DisplayList::DrawGlyphs"_s, {
            {
                "WebCore::RenderingResourceIdentifier"_s,
                "fontIdentifier()"_s
            },
            {
                "WebCore::PositionedGlyphs"_s,
                "positionedGlyphs()"_s
            },
        } },
        { "WebCore::DisplayList::DrawSystemImage"_s, {
            {
                "Ref<WebCore::SystemImage>"_s,
                "systemImage()"_s
            },
            {
                "WebCore::FloatRect"_s,
                "destinationRect()"_s
            },
        } },
        { "WebCore::DisplayList::DrawLinesForText"_s, {
            {
                "WebCore::FloatPoint"_s,
                "blockLocation()"_s
            },
            {
                "WebCore::FloatSize"_s,
                "localAnchor()"_s
            },
            {
                "WebCore::DashArray"_s,
                "widths()"_s
            },
            {
                "float"_s,
                "thickness()"_s
            },
            {
                "bool"_s,
                "isPrinting()"_s
            },
            {
                "bool"_s,
                "doubleLines()"_s
            },
            {
                "WebCore::StrokeStyle"_s,
                "style()"_s
            },
        } },
        { "WebCore::DisplayList::DrawPath"_s, {
            {
                "WebCore::Path"_s,
                "path()"_s
            },
        } },
        { "WebCore::DisplayList::DrawFocusRingPath"_s, {
            {
                "WebCore::Path"_s,
                "path()"_s
            },
            {
                "float"_s,
                "outlineWidth()"_s
            },
            {
                "WebCore::Color"_s,
                "color()"_s
            },
        } },
        { "WebCore::DisplayList::DrawFocusRingRects"_s, {
            {
                "Vector<WebCore::FloatRect>"_s,
                "rects()"_s
            },
            {
                "float"_s,
                "outlineOffset()"_s
            },
            {
                "float"_s,
                "outlineWidth()"_s
            },
            {
                "WebCore::Color"_s,
                "color()"_s
            },
        } },
        { "WebCore::DisplayList::FillRectWithColor"_s, {
            {
                "WebCore::FloatRect"_s,
                "rect()"_s
            },
            {
                "WebCore::Color"_s,
                "color()"_s
            },
        } },
        { "WebCore::DisplayList::FillRectWithGradient"_s, {
            {
                "WebCore::FloatRect"_s,
                "rect()"_s
            },
            {
                "Ref<WebCore::Gradient>"_s,
                "gradient()"_s
            },
        } },
        { "WebCore::DisplayList::FillCompositedRect"_s, {
            {
                "WebCore::FloatRect"_s,
                "rect()"_s
            },
            {
                "WebCore::Color"_s,
                "color()"_s
            },
            {
                "WebCore::CompositeOperator"_s,
                "compositeOperator()"_s
            },
            {
                "WebCore::BlendMode"_s,
                "blendMode()"_s
            },
        } },
        { "WebCore::DisplayList::FillRoundedRect"_s, {
            {
                "WebCore::FloatRoundedRect"_s,
                "roundedRect()"_s
            },
            {
                "WebCore::Color"_s,
                "color()"_s
            },
            {
                "WebCore::BlendMode"_s,
                "blendMode()"_s
            },
        } },
        { "WebCore::DisplayList::FillRectWithRoundedHole"_s, {
            {
                "WebCore::FloatRect"_s,
                "rect()"_s
            },
            {
                "WebCore::FloatRoundedRect"_s,
                "roundedHoleRect()"_s
            },
            {
                "WebCore::Color"_s,
                "color()"_s
            },
        } },
        { "WebCore::DisplayList::FillPath"_s, {
            {
                "WebCore::Path"_s,
                "path()"_s
            },
        } },
        { "WebCore::DisplayList::StrokePath"_s, {
            {
                "WebCore::Path"_s,
                "path()"_s
            },
        } },
        { "WebKit::EditorState"_s, {
            {
                "WebKit::EditorStateIdentifier"_s,
                "identifier"_s
            },
            {
                "bool"_s,
                "shouldIgnoreSelectionChanges"_s
            },
            {
                "bool"_s,
                "selectionIsNone"_s
            },
            {
                "bool"_s,
                "selectionIsRange"_s
            },
            {
                "bool"_s,
                "selectionIsRangeInsideImageOverlay"_s
            },
            {
                "bool"_s,
                "selectionIsRangeInAutoFilledAndViewableField"_s
            },
            {
                "bool"_s,
                "isContentEditable"_s
            },
            {
                "bool"_s,
                "isContentRichlyEditable"_s
            },
            {
                "bool"_s,
                "isInPasswordField"_s
            },
            {
                "bool"_s,
                "isInPlugin"_s
            },
            {
                "bool"_s,
                "hasComposition"_s
            },
            {
                "bool"_s,
                "triggeredByAccessibilitySelectionChange"_s
            },
#if PLATFORM(MAC)
            {
                "bool"_s,
                "canEnableAutomaticSpellingCorrection"_s
            },
#endif
            {
                "std::optional<WebKit::EditorState::PostLayoutData>"_s,
                "postLayoutData"_s
            },
            {
                "std::optional<WebKit::EditorState::VisualData>"_s,
                "visualData"_s
            },
        } },
        { "WebKit::EditorState::PostLayoutData"_s, {
            {
                "OptionSet<WebKit::TypingAttribute>"_s,
                "typingAttributes"_s
            },
#if PLATFORM(COCOA)
            {
                "uint64_t"_s,
                "selectedTextLength"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "WebKit::TextAlignment"_s,
                "textAlignment"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "WebCore::Color"_s,
                "textColor"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "WebKit::ListType"_s,
                "enclosingListType"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "WebCore::WritingDirection"_s,
                "baseWritingDirection"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "editableRootIsTransparentOrFullyClipped"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "String"_s,
                "markedText"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "String"_s,
                "wordAtSelection"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "UChar32"_s,
                "characterAfterSelection"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "UChar32"_s,
                "characterBeforeSelection"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "UChar32"_s,
                "twoCharacterBeforeSelection"_s
            },
#endif
#if PLATFORM(IOS_FAMILY) && USE(DICTATION_ALTERNATIVES)
            {
                "Vector<WebCore::DictationContext>"_s,
                "dictationContextsForSelection"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "isReplaceAllowed"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "hasContent"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "isStableStateUpdate"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "insideFixedPosition"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "hasPlainText"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::Color"_s,
                "caretColor"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "atStartOfSentence"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "selectionStartIsAtParagraphBoundary"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "selectionEndIsAtParagraphBoundary"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "hasGrammarDocumentMarkers"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "std::optional<WebCore::ElementContext>"_s,
                "selectedEditableImage"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "WebCore::IntRect"_s,
                "selectionBoundingRect"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "uint64_t"_s,
                "candidateRequestStartPosition"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "String"_s,
                "paragraphContextForCandidateRequest"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "String"_s,
                "stringForCandidateRequest"_s
            },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
            {
                "String"_s,
                "surroundingContext"_s
            },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
            {
                "uint64_t"_s,
                "surroundingContextCursorPosition"_s
            },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
            {
                "uint64_t"_s,
                "surroundingContextSelectionPosition"_s
            },
#endif
            {
                "std::optional<WebCore::FontAttributes>"_s,
                "fontAttributes"_s
            },
            {
                "bool"_s,
                "canCut"_s
            },
            {
                "bool"_s,
                "canCopy"_s
            },
            {
                "bool"_s,
                "canPaste"_s
            },
        } },
        { "WebKit::EditorState::VisualData"_s, {
#if PLATFORM(IOS_FAMILY) || PLATFORM(GTK) || PLATFORM(WPE)
            {
                "WebCore::IntRect"_s,
                "caretRectAtStart"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntRect"_s,
                "selectionClipRect"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntRect"_s,
                "caretRectAtEnd"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "Vector<WebCore::SelectionGeometry>"_s,
                "selectionGeometries"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "Vector<WebCore::SelectionGeometry>"_s,
                "markedTextRects"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntRect"_s,
                "markedTextCaretRectAtStart"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntRect"_s,
                "markedTextCaretRectAtEnd"_s
            },
#endif
        } },
        { "WebKit::FileSystemSyncAccessHandleInfo"_s, {
            {
                "WebCore::FileSystemSyncAccessHandleIdentifier"_s,
                "identifier"_s
            },
            {
                "IPC::SharedFileHandle"_s,
                "handle"_s
            },
            {
                "uint64_t"_s,
                "capacity"_s
            },
        } },
        { "WebKit::OptionItem"_s, {
            {
                "String"_s,
                "text"_s
            },
            {
                "bool"_s,
                "isGroup"_s
            },
            {
                "bool"_s,
                "isSelected"_s
            },
            {
                "bool"_s,
                "disabled"_s
            },
            {
                "int"_s,
                "parentGroupID"_s
            },
        } },
        { "WebKit::FocusedElementInformation"_s, {
            {
                "WebCore::IntRect"_s,
                "interactionRect"_s
            },
            {
                "WebCore::ElementContext"_s,
                "elementContext"_s
            },
            {
                "WebCore::IntPoint"_s,
                "lastInteractionLocation"_s
            },
            {
                "double"_s,
                "minimumScaleFactor"_s
            },
            {
                "double"_s,
                "maximumScaleFactor"_s
            },
            {
                "double"_s,
                "maximumScaleFactorIgnoringAlwaysScalable"_s
            },
            {
                "double"_s,
                "nodeFontSize"_s
            },
            {
                "bool"_s,
                "hasNextNode"_s
            },
            {
                "WebCore::IntRect"_s,
                "nextNodeRect"_s
            },
            {
                "bool"_s,
                "hasPreviousNode"_s
            },
            {
                "WebCore::IntRect"_s,
                "previousNodeRect"_s
            },
            {
                "bool"_s,
                "isAutocorrect"_s
            },
            {
                "bool"_s,
                "isRTL"_s
            },
            {
                "bool"_s,
                "isMultiSelect"_s
            },
            {
                "bool"_s,
                "isReadOnly"_s
            },
            {
                "bool"_s,
                "allowsUserScaling"_s
            },
            {
                "bool"_s,
                "allowsUserScalingIgnoringAlwaysScalable"_s
            },
            {
                "bool"_s,
                "insideFixedPosition"_s
            },
            {
                "WebCore::AutocapitalizeType"_s,
                "autocapitalizeType"_s
            },
            {
                "WebKit::InputType"_s,
                "elementType"_s
            },
            {
                "WebCore::InputMode"_s,
                "inputMode"_s
            },
            {
                "WebCore::EnterKeyHint"_s,
                "enterKeyHint"_s
            },
            {
                "String"_s,
                "formAction"_s
            },
            {
                "Vector<WebKit::OptionItem>"_s,
                "selectOptions"_s
            },
            {
                "int"_s,
                "selectedIndex"_s
            },
            {
                "String"_s,
                "value"_s
            },
            {
                "double"_s,
                "valueAsNumber"_s
            },
            {
                "String"_s,
                "title"_s
            },
            {
                "bool"_s,
                "acceptsAutofilledLoginCredentials"_s
            },
            {
                "bool"_s,
                "isAutofillableUsernameField"_s
            },
            {
                "URL"_s,
                "representingPageURL"_s
            },
            {
                "WebCore::AutofillFieldName"_s,
                "autofillFieldName"_s
            },
            {
                "WebCore::NonAutofillCredentialType"_s,
                "nonAutofillCredentialType"_s
            },
            {
                "String"_s,
                "placeholder"_s
            },
            {
                "String"_s,
                "label"_s
            },
            {
                "String"_s,
                "ariaLabel"_s
            },
#if ENABLE(DATALIST_ELEMENT)
            {
                "bool"_s,
                "hasSuggestions"_s
            },
#endif
#if ENABLE(DATALIST_ELEMENT)
            {
                "bool"_s,
                "isFocusingWithDataListDropdown"_s
            },
#endif
#if ENABLE(INPUT_TYPE_COLOR)
            {
                "WebCore::Color"_s,
                "colorValue"_s
            },
#endif
#if ENABLE(INPUT_TYPE_COLOR)
            {
                "Vector<WebCore::Color>"_s,
                "suggestedColors"_s
            },
#endif
            {
                "bool"_s,
                "hasEverBeenPasswordField"_s
            },
            {
                "bool"_s,
                "shouldSynthesizeKeyEventsForEditing"_s
            },
            {
                "bool"_s,
                "isSpellCheckingEnabled"_s
            },
            {
                "bool"_s,
                "shouldAvoidResizingWhenInputViewBoundsChange"_s
            },
            {
                "bool"_s,
                "shouldAvoidScrollingWhenFocusedContentIsVisible"_s
            },
            {
                "bool"_s,
                "shouldUseLegacySelectPopoverDismissalBehaviorInDataActivation"_s
            },
            {
                "bool"_s,
                "isFocusingWithValidationMessage"_s
            },
            {
                "bool"_s,
                "preventScroll"_s
            },
            {
                "WebKit::FocusedElementInformationIdentifier"_s,
                "identifier"_s
            },
            {
                "WebCore::ScrollingNodeID"_s,
                "containerScrollingNodeID"_s
            },
            {
                "WebCore::FrameIdentifier"_s,
                "frameID"_s
            },
        } },
        { "WebKit::FrameInfoData"_s, {
            {
                "bool"_s,
                "isMainFrame"_s
            },
            {
                "WebKit::FrameType"_s,
                "frameType"_s
            },
            {
                "WebCore::ResourceRequest"_s,
                "request"_s
            },
            {
                "WebCore::SecurityOriginData"_s,
                "securityOrigin"_s
            },
            {
                "String"_s,
                "frameName"_s
            },
            {
                "WebCore::FrameIdentifier"_s,
                "frameID"_s
            },
            {
                "std::optional<WebCore::FrameIdentifier>"_s,
                "parentFrameID"_s
            },
            {
                "WTF::ProcessID"_s,
                "processID"_s
            },
        } },
        { "WebKit::FrameTreeCreationParameters"_s, {
            {
                "WebCore::FrameIdentifier"_s,
                "frameID"_s
            },
            {
                "Vector<WebKit::FrameTreeCreationParameters>"_s,
                "children"_s
            },
        } },
        { "WebKit::FrameTreeNodeData"_s, {
            {
                "WebKit::FrameInfoData"_s,
                "info"_s
            },
            {
                "Vector<WebKit::FrameTreeNodeData>"_s,
                "children"_s
            },
        } },
        { "WebKit::GPUProcessConnectionParameters"_s, {
            {
                "WebCore::ProcessIdentity"_s,
                "webProcessIdentity"_s
            },
            {
                "bool"_s,
                "isDOMRenderingEnabled"_s
            },
            {
                "bool"_s,
                "isLockdownModeEnabled"_s
            },
            {
                "bool"_s,
                "isWebGPUEnabled"_s
            },
#if ENABLE(IPC_TESTING_API)
            {
                "bool"_s,
                "ignoreInvalidMessageForTesting"_s
            },
#endif
            {
                "bool"_s,
                "allowTestOnlyIPC"_s
            },
#if HAVE(AUDIT_TOKEN)
            {
                "std::optional<audit_token_t>"_s,
                "presentingApplicationAuditToken"_s
            },
#endif
#if ENABLE(VP9)
            {
                "std::optional<bool>"_s,
                "hasVP9HardwareDecoder"_s
            },
#endif
#if ENABLE(VP9)
            {
                "std::optional<bool>"_s,
                "hasVP9ExtensionSupport"_s
            },
#endif
        } },
        { "WebKit::LayerTreeContext"_s, {
            {
                "uint64_t"_s,
                "contextID"_s
            },
        } },
        { "WebKit::LocalFrameCreationParameters"_s, {
            {
                "std::optional<WebCore::LayerHostingContextIdentifier>"_s,
                "layerHostingContextIdentifier"_s
            },
        } },
        { "WebKit::ModelIdentifier"_s, {
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
            {
                "String"_s,
                "uuid"_s
            },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_IOS)
            {
                "WebCore::PlatformLayerIdentifier"_s,
                "layerIdentifier"_s
            },
#endif
        } },
        { "WebKit::NavigationActionData"_s, {
            {
                "WebCore::NavigationType"_s,
                "navigationType"_s
            },
            {
                "OptionSet<WebKit::WebEventModifier>"_s,
                "modifiers"_s
            },
            {
                "WebKit::WebMouseEventButton"_s,
                "mouseButton"_s
            },
            {
                "WebKit::WebMouseEventSyntheticClickType"_s,
                "syntheticClickType"_s
            },
            {
                "uint64_t"_s,
                "userGestureTokenIdentifier"_s
            },
            {
                "std::optional<WTF::UUID>"_s,
                "userGestureAuthorizationToken"_s
            },
            {
                "bool"_s,
                "canHandleRequest"_s
            },
            {
                "WebCore::ShouldOpenExternalURLsPolicy"_s,
                "shouldOpenExternalURLsPolicy"_s
            },
            {
                "WTF::String"_s,
                "downloadAttribute"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "clickLocationInRootViewCoordinates"_s
            },
            {
                "WebCore::ResourceResponse"_s,
                "redirectResponse"_s
            },
            {
                "bool"_s,
                "treatAsSameOriginNavigation"_s
            },
            {
                "bool"_s,
                "hasOpenedFrames"_s
            },
            {
                "bool"_s,
                "openedByDOMWithOpener"_s
            },
            {
                "bool"_s,
                "hasOpener"_s
            },
            {
                "WebCore::SecurityOriginData"_s,
                "requesterOrigin"_s
            },
            {
                "std::optional<WebCore::BackForwardItemIdentifier>"_s,
                "targetBackForwardItemIdentifier"_s
            },
            {
                "std::optional<WebCore::BackForwardItemIdentifier>"_s,
                "sourceBackForwardItemIdentifier"_s
            },
            {
                "WebCore::LockHistory"_s,
                "lockHistory"_s
            },
            {
                "WebCore::LockBackForwardList"_s,
                "lockBackForwardList"_s
            },
            {
                "WTF::String"_s,
                "clientRedirectSourceForHistory"_s
            },
            {
                "WebCore::SandboxFlags"_s,
                "effectiveSandboxFlags"_s
            },
            {
                "std::optional<WebCore::PrivateClickMeasurement>"_s,
                "privateClickMeasurement"_s
            },
            {
                "OptionSet<WebCore::AdvancedPrivacyProtections>"_s,
                "advancedPrivacyProtections"_s
            },
            {
                "OptionSet<WebCore::AdvancedPrivacyProtections>"_s,
                "originatorAdvancedPrivacyProtections"_s
            },
#if PLATFORM(MAC) || HAVE(UIKIT_WITH_MOUSE_SUPPORT)
            {
                "std::optional<WebKit::WebHitTestResultData>"_s,
                "webHitTestResultData"_s
            },
#endif
        } },
        { "WebKit::NetworkProcessConnectionParameters"_s, {
            {
                "bool"_s,
                "allowTestOnlyIPC"_s
            },
        } },
        { "WebCore::PasteboardImage"_s, {
            {
                "RefPtr<WebCore::Image>"_s,
                "image"_s
            },
#if PLATFORM(MAC)
            {
                "RefPtr<WebCore::SharedBuffer>"_s,
                "dataInWebArchiveFormat"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "String"_s,
                "dataInHTMLFormat"_s
            },
#endif
#if !PLATFORM(WIN)
            {
                "WebCore::PasteboardURL"_s,
                "url"_s
            },
#endif
#if !(PLATFORM(GTK) || PLATFORM(WIN))
            {
                "RefPtr<WebCore::SharedBuffer>"_s,
                "resourceData"_s
            },
#endif
#if !(PLATFORM(GTK) || PLATFORM(WIN))
            {
                "String"_s,
                "resourceMIMEType"_s
            },
#endif
#if !(PLATFORM(GTK) || PLATFORM(WIN))
            {
                "Vector<String>"_s,
                "clientTypes"_s
            },
#endif
#if !(PLATFORM(GTK) || PLATFORM(WIN))
            {
                "Vector<RefPtr<WebCore::SharedBuffer>>"_s,
                "clientData"_s
            },
#endif
            {
                "String"_s,
                "suggestedName"_s
            },
            {
                "WebCore::FloatSize"_s,
                "imageSize"_s
            },
        } },
        { "WebCore::PasteboardWebContent"_s, {
#if PLATFORM(COCOA)
            {
                "String"_s,
                "contentOrigin"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "canSmartCopyOrDelete"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "RefPtr<WebCore::SharedBuffer>"_s,
                "dataInWebArchiveFormat"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "RefPtr<WebCore::SharedBuffer>"_s,
                "dataInRTFDFormat"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "RefPtr<WebCore::SharedBuffer>"_s,
                "dataInRTFFormat"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "RefPtr<WebCore::SharedBuffer>"_s,
                "dataInAttributedStringFormat"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "String"_s,
                "dataInHTMLFormat"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "String"_s,
                "dataInStringFormat"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "Vector<String>"_s,
                "clientTypes"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "Vector<RefPtr<WebCore::SharedBuffer>>"_s,
                "clientData"_s
            },
#endif
#if PLATFORM(GTK)
            {
                "String"_s,
                "contentOrigin"_s
            },
#endif
#if PLATFORM(GTK)
            {
                "bool"_s,
                "canSmartCopyOrDelete"_s
            },
#endif
#if PLATFORM(GTK)
            {
                "String"_s,
                "text"_s
            },
#endif
#if PLATFORM(GTK)
            {
                "String"_s,
                "markup"_s
            },
#endif
#if USE(LIBWPE)
            {
                "String"_s,
                "text"_s
            },
#endif
#if USE(LIBWPE)
            {
                "String"_s,
                "markup"_s
            },
#endif
        } },
        { "WebCore::PasteboardURL"_s, {
            {
                "URL"_s,
                "url"_s
            },
            {
                "String"_s,
                "title"_s
            },
#if PLATFORM(MAC)
            {
                "String"_s,
                "userVisibleForm"_s
            },
#endif
#if PLATFORM(GTK)
            {
                "String"_s,
                "markup"_s
            },
#endif
        } },
        { "WebCore::PasteboardBuffer"_s, {
#if PLATFORM(COCOA)
            {
                "String"_s,
                "contentOrigin"_s
            },
#endif
            {
                "String"_s,
                "type"_s
            },
            {
                "RefPtr<WebCore::SharedBuffer>"_s,
                "data"_s
            },
        } },
        { "WebKit::PlatformPopupMenuData"_s, {
#if PLATFORM(COCOA)
            {
                "WebKit::FontInfo"_s,
                "fontInfo"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "shouldPopOver"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "hideArrows"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "WebCore::PopupMenuStyle::PopupMenuSize"_s,
                "menuSize"_s
            },
#endif
#if PLATFORM(WIN)
            {
                "int"_s,
                "m_clientPaddingLeft"_s
            },
#endif
#if PLATFORM(WIN)
            {
                "int"_s,
                "m_clientPaddingRight"_s
            },
#endif
#if PLATFORM(WIN)
            {
                "int"_s,
                "m_clientInsetLeft"_s
            },
#endif
#if PLATFORM(WIN)
            {
                "int"_s,
                "m_clientInsetRight"_s
            },
#endif
#if PLATFORM(WIN)
            {
                "int"_s,
                "m_popupWidth"_s
            },
#endif
#if PLATFORM(WIN)
            {
                "int"_s,
                "m_itemHeight"_s
            },
#endif
#if PLATFORM(WIN)
            {
                "RefPtr<WebKit::ShareableBitmap>"_s,
                "m_notSelectedBackingStore"_s
            },
#endif
#if PLATFORM(WIN)
            {
                "RefPtr<WebKit::ShareableBitmap>"_s,
                "m_selectedBackingStore"_s
            },
#endif
        } },
        { "WebKit::PolicyDecision"_s, {
            {
                "std::optional<WebKit::NavigatingToAppBoundDomain>"_s,
                "isNavigatingToAppBoundDomain"_s
            },
            {
                "WebCore::PolicyAction"_s,
                "policyAction"_s
            },
            {
                "uint64_t"_s,
                "navigationID"_s
            },
            {
                "std::optional<WebKit::DownloadID>"_s,
                "downloadID"_s
            },
            {
                "std::optional<WebKit::WebsitePoliciesData>"_s,
                "websitePoliciesData"_s
            },
            {
                "std::optional<WebKit::SandboxExtension::Handle>"_s,
                "sandboxExtensionHandle"_s
            },
        } },
        { "WebKit::HTTPBody"_s, {
            {
                "String"_s,
                "contentType"_s
            },
            {
                "Vector<WebKit::HTTPBody::Element>"_s,
                "elements"_s
            },
        } },
        { "WebKit::HTTPBody::Element"_s, {
            {
                "std::variant<Vector<uint8_t>, WebKit::HTTPBody::Element::FileData, String>"_s,
                "data"_s
            },
        } },
        { "WebKit::HTTPBody::Element::FileData"_s, {
            {
                "String"_s,
                "filePath"_s
            },
            {
                "int64_t"_s,
                "fileStart"_s
            },
            {
                "std::optional<int64_t>"_s,
                "fileLength"_s
            },
            {
                "std::optional<WallTime>"_s,
                "expectedFileModificationTime"_s
            },
        } },
        { "WebKit::FrameState"_s, {
            {
                "String"_s,
                "urlString"_s
            },
            {
                "String"_s,
                "originalURLString"_s
            },
            {
                "String"_s,
                "referrer"_s
            },
            {
                "AtomString"_s,
                "target"_s
            },
            {
                "std::optional<Vector<uint8_t>>"_s,
                "stateObjectData"_s
            },
            {
                "int64_t"_s,
                "documentSequenceNumber"_s
            },
            {
                "int64_t"_s,
                "itemSequenceNumber"_s
            },
            {
                "WebCore::IntPoint"_s,
                "scrollPosition"_s
            },
            {
                "bool"_s,
                "shouldRestoreScrollPosition"_s
            },
            {
                "float"_s,
                "pageScaleFactor"_s
            },
            {
                "std::optional<WebKit::HTTPBody>"_s,
                "httpBody"_s
            },
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::FloatRect"_s,
                "exposedContentRect"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntRect"_s,
                "unobscuredContentRect"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::FloatSize"_s,
                "minimumLayoutSizeInScrollViewCoordinates"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntSize"_s,
                "contentSize"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "scaleIsInitial"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::FloatBoxExtent"_s,
                "obscuredInsets"_s
            },
#endif
            {
                "Vector<WebKit::FrameState>"_s,
                "children"_s
            },
            {
                "Vector<AtomString>"_s,
                "m_documentState"_s
            },
        } },
        { "WebKit::PageState"_s, {
            {
                "String"_s,
                "title"_s
            },
            {
                "WebKit::FrameState"_s,
                "mainFrameState"_s
            },
            {
                "WebCore::ShouldOpenExternalURLsPolicy"_s,
                "shouldOpenExternalURLsPolicy"_s
            },
            {
                "RefPtr<WebCore::SerializedScriptValue>"_s,
                "sessionStateObject"_s
            },
            {
                "bool"_s,
                "wasCreatedByJSWithoutUserInteraction"_s
            },
        } },
        { "WebKit::BackForwardListItemState"_s, {
            {
                "WebCore::BackForwardItemIdentifier"_s,
                "identifier"_s
            },
            {
                "WebKit::PageState"_s,
                "pageState"_s
            },
            {
                "bool"_s,
                "hasCachedPage"_s
            },
        } },
        { "WebKit::BackForwardListState"_s, {
            {
                "Vector<WebKit::BackForwardListItemState>"_s,
                "items"_s
            },
            {
                "std::optional<uint32_t>"_s,
                "currentIndex"_s
            },
        } },
        { "WebKit::ShareableBitmapConfiguration"_s, {
            {
                "WebCore::IntSize"_s,
                "m_size"_s
            },
            {
                "std::optional<WebCore::DestinationColorSpace>"_s,
                "m_colorSpace"_s
            },
            {
                "bool"_s,
                "m_isOpaque"_s
            },
            {
                "unsigned"_s,
                "bytesPerPixel()"_s
            },
            {
                "unsigned"_s,
                "bytesPerRow()"_s
            },
#if USE(CG)
            {
                "CGBitmapInfo"_s,
                "m_bitmapInfo"_s
            },
#endif
        } },
        { "WebKit::ShareableBitmapHandle"_s, {
            {
                "WebKit::SharedMemoryHandle"_s,
                "m_handle"_s
            },
            {
                "WebKit::ShareableBitmapConfiguration"_s,
                "m_configuration"_s
            },
        } },
        { "WebKit::ShareableBitmap"_s, {
            {
                "std::optional<WebKit::ShareableBitmapHandle>"_s,
                "createReadOnlyHandle()"_s
            },
        } },
        { "WebCore::TextRecognitionWordData"_s, {
            {
                "String"_s,
                "text"_s
            },
            {
                "WebCore::FloatQuad"_s,
                "normalizedQuad"_s
            },
            {
                "bool"_s,
                "hasLeadingWhitespace"_s
            },
        } },
        { "WebCore::TextRecognitionLineData"_s, {
            {
                "WebCore::FloatQuad"_s,
                "normalizedQuad"_s
            },
            {
                "Vector<WebCore::TextRecognitionWordData>"_s,
                "children"_s
            },
            {
                "bool"_s,
                "hasTrailingNewline"_s
            },
            {
                "bool"_s,
                "isVertical"_s
            },
        } },
        { "WebCore::TextRecognitionBlockData"_s, {
            {
                "String"_s,
                "text"_s
            },
            {
                "WebCore::FloatQuad"_s,
                "normalizedQuad"_s
            },
        } },
        { "WebCore::TextRecognitionResult"_s, {
            {
                "Vector<WebCore::TextRecognitionLineData>"_s,
                "lines"_s
            },
#if ENABLE(DATA_DETECTION)
            {
                "Vector<WebCore::TextRecognitionDataDetector>"_s,
                "dataDetectors"_s
            },
#endif
            {
                "Vector<WebCore::TextRecognitionBlockData>"_s,
                "blocks"_s
            },
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
            {
                "RetainPtr<VKCImageAnalysis>"_s,
                "platformData"_s
            },
#endif
        } },
        { "WebKit::UpdateInfo"_s, {
            {
                "WebCore::IntSize"_s,
                "viewSize"_s
            },
            {
                "float"_s,
                "deviceScaleFactor"_s
            },
            {
                "WebCore::IntRect"_s,
                "scrollRect"_s
            },
            {
                "WebCore::IntSize"_s,
                "scrollOffset"_s
            },
            {
                "WebCore::IntRect"_s,
                "updateRectBounds"_s
            },
            {
                "Vector<WebCore::IntRect>"_s,
                "updateRects"_s
            },
            {
                "float"_s,
                "updateScaleFactor"_s
            },
            {
                "WebKit::ShareableBitmapHandle"_s,
                "bitmapHandle"_s
            },
            {
                "WebCore::IntPoint"_s,
                "bitmapOffset"_s
            },
        } },
        { "URL"_s, {
            {
                "String"_s,
                "string()"_s
            },
        } },
        { "MediaTime"_s, {
            {
                "int64_t"_s,
                "timeValue()"_s
            },
            {
                "uint32_t"_s,
                "timeScale()"_s
            },
            {
                "uint8_t"_s,
                "timeFlags()"_s
            },
        } },
        { "Seconds"_s, {
            {
                "double"_s,
                "value()"_s
            },
        } },
        { "MonotonicTime"_s, {
            {
                "double"_s,
                "secondsSinceEpoch().seconds()"_s
            },
        } },
        { "WallTime"_s, {
            {
                "double"_s,
                "secondsSinceEpoch().seconds()"_s
            },
        } },
        { "AtomString"_s, {
            {
                "String"_s,
                "string()"_s
            },
        } },
        { "WebCore::DOMCacheEngine::CacheInfo"_s, {
            {
                "WebCore::DOMCacheIdentifier"_s,
                "identifier"_s
            },
            {
                "String"_s,
                "name"_s
            },
        } },
        { "WebCore::DOMCacheEngine::CacheInfos"_s, {
            {
                "Vector<WebCore::DOMCacheEngine::CacheInfo>"_s,
                "infos"_s
            },
            {
                "uint64_t"_s,
                "updateCounter"_s
            },
        } },
        { "WebCore::DOMCacheEngine::CacheIdentifierOperationResult"_s, {
            {
                "WebCore::DOMCacheIdentifier"_s,
                "identifier"_s
            },
            {
                "bool"_s,
                "hadStorageError"_s
            },
        } },
        { "WebCore::TranslationContextMenuInfo"_s, {
            {
                "String"_s,
                "text"_s
            },
            {
                "WebCore::IntRect"_s,
                "selectionBoundsInRootView"_s
            },
            {
                "WebCore::IntPoint"_s,
                "locationInRootView"_s
            },
            {
                "WebCore::TranslationContextMenuMode"_s,
                "mode"_s
            },
            {
                "WebCore::TranslationContextMenuSource"_s,
                "source"_s
            },
        } },
        { "WebCore::DOMCacheEngine::CrossThreadRecord"_s, {
            {
                "uint64_t"_s,
                "identifier"_s
            },
            {
                "uint64_t"_s,
                "updateResponseCounter"_s
            },
            {
                "WebCore::FetchHeadersGuard"_s,
                "requestHeadersGuard"_s
            },
            {
                "WebCore::ResourceRequest"_s,
                "request"_s
            },
            {
                "WebCore::FetchOptions"_s,
                "options"_s
            },
            {
                "String"_s,
                "referrer"_s
            },
            {
                "WebCore::FetchHeadersGuard"_s,
                "responseHeadersGuard"_s
            },
            {
                "WebCore::ResourceResponse::CrossThreadData"_s,
                "response"_s
            },
            {
                "std::variant<std::nullptr_t, Ref<WebCore::FormData>, Ref<WebCore::SharedBuffer>>"_s,
                "responseBody"_s
            },
            {
                "uint64_t"_s,
                "responseBodySize"_s
            },
        } },
        { "WebCore::TransformationMatrix"_s, {
            {
                "double"_s,
                "m11()"_s
            },
            {
                "double"_s,
                "m12()"_s
            },
            {
                "double"_s,
                "m13()"_s
            },
            {
                "double"_s,
                "m14()"_s
            },
            {
                "double"_s,
                "m21()"_s
            },
            {
                "double"_s,
                "m22()"_s
            },
            {
                "double"_s,
                "m23()"_s
            },
            {
                "double"_s,
                "m24()"_s
            },
            {
                "double"_s,
                "m31()"_s
            },
            {
                "double"_s,
                "m32()"_s
            },
            {
                "double"_s,
                "m33()"_s
            },
            {
                "double"_s,
                "m34()"_s
            },
            {
                "double"_s,
                "m41()"_s
            },
            {
                "double"_s,
                "m42()"_s
            },
            {
                "double"_s,
                "m43()"_s
            },
            {
                "double"_s,
                "m44()"_s
            },
        } },
        { "WebCore::CacheQueryOptions"_s, {
            {
                "bool"_s,
                "ignoreSearch"_s
            },
            {
                "bool"_s,
                "ignoreMethod"_s
            },
            {
                "bool"_s,
                "ignoreVary"_s
            },
        } },
        { "WebCore::CharacterRange"_s, {
            {
                "uint64_t"_s,
                "location"_s
            },
            {
                "uint64_t"_s,
                "length"_s
            },
        } },
        { "WebCore::AffineTransform"_s, {
            {
                "double"_s,
                "a()"_s
            },
            {
                "double"_s,
                "b()"_s
            },
            {
                "double"_s,
                "c()"_s
            },
            {
                "double"_s,
                "d()"_s
            },
            {
                "double"_s,
                "e()"_s
            },
            {
                "double"_s,
                "f()"_s
            },
        } },
        { "WebCore::FloatPoint"_s, {
            {
                "float"_s,
                "x()"_s
            },
            {
                "float"_s,
                "y()"_s
            },
        } },
        { "WebCore::FloatPoint3D"_s, {
            {
                "float"_s,
                "x()"_s
            },
            {
                "float"_s,
                "y()"_s
            },
            {
                "float"_s,
                "z()"_s
            },
        } },
        { "WebCore::FloatQuad"_s, {
            {
                "WebCore::FloatPoint"_s,
                "p1()"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "p2()"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "p3()"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "p4()"_s
            },
        } },
        { "WebCore::IDBCursorRecord"_s, {
            {
                "WebCore::IDBKeyData"_s,
                "key"_s
            },
            {
                "WebCore::IDBKeyData"_s,
                "primaryKey"_s
            },
            {
                "WebCore::IDBValue"_s,
                "value"_s
            },
        } },
        { "WebCore::IDBCursorInfo"_s, {
            {
                "WebCore::IDBResourceIdentifier"_s,
                "identifier()"_s
            },
            {
                "WebCore::IDBResourceIdentifier"_s,
                "transactionIdentifier()"_s
            },
            {
                "uint64_t"_s,
                "objectStoreIdentifier()"_s
            },
            {
                "uint64_t"_s,
                "sourceIdentifier()"_s
            },
            {
                "WebCore::IDBKeyRangeData"_s,
                "range()"_s
            },
            {
                "WebCore::IndexedDB::CursorSource"_s,
                "cursorSource()"_s
            },
            {
                "WebCore::IndexedDB::CursorDirection"_s,
                "cursorDirection()"_s
            },
            {
                "WebCore::IndexedDB::CursorType"_s,
                "cursorType()"_s
            },
        } },
        { "WebCore::IDBError"_s, {
            {
                "std::optional<WebCore::ExceptionCode>"_s,
                "code()"_s
            },
            {
                "String"_s,
                "messageForSerialization()"_s
            },
        } },
        { "WebCore::IDBGetAllRecordsData"_s, {
            {
                "WebCore::IDBKeyRangeData"_s,
                "keyRangeData"_s
            },
            {
                "WebCore::IndexedDB::GetAllType"_s,
                "getAllType"_s
            },
            {
                "std::optional<uint32_t>"_s,
                "count"_s
            },
            {
                "uint64_t"_s,
                "objectStoreIdentifier"_s
            },
            {
                "uint64_t"_s,
                "indexIdentifier"_s
            },
        } },
        { "WebCore::IDBGetResult"_s, {
            {
                "WebCore::IDBKeyData"_s,
                "keyData()"_s
            },
            {
                "WebCore::IDBKeyData"_s,
                "primaryKeyData()"_s
            },
            {
                "WebCore::IDBValue"_s,
                "value()"_s
            },
            {
                "std::optional<WebCore::IDBKeyPath>"_s,
                "keyPath()"_s
            },
            {
                "Vector<WebCore::IDBCursorRecord>"_s,
                "prefetchedRecords()"_s
            },
            {
                "bool"_s,
                "isDefined()"_s
            },
        } },
        { "WebCore::IDBGetAllResult"_s, {
            {
                "WebCore::IndexedDB::GetAllType"_s,
                "type()"_s
            },
            {
                "Vector<WebCore::IDBKeyData>"_s,
                "keys()"_s
            },
            {
                "Vector<WebCore::IDBValue>"_s,
                "values()"_s
            },
            {
                "std::optional<WebCore::IDBKeyPath>"_s,
                "keyPath()"_s
            },
        } },
        { "WebCore::IDBDatabaseInfo"_s, {
            {
                "String"_s,
                "m_name"_s
            },
            {
                "uint64_t"_s,
                "m_version"_s
            },
            {
                "uint64_t"_s,
                "m_maxIndexID"_s
            },
            {
                "uint64_t"_s,
                "m_maxObjectStoreID"_s
            },
            {
                "HashMap<uint64_t, WebCore::IDBObjectStoreInfo>"_s,
                "m_objectStoreMap"_s
            },
        } },
        { "WebCore::IDBKeyRangeData"_s, {
            {
                "WebCore::IDBKeyData"_s,
                "lowerKey"_s
            },
            {
                "WebCore::IDBKeyData"_s,
                "upperKey"_s
            },
            {
                "bool"_s,
                "lowerOpen"_s
            },
            {
                "bool"_s,
                "upperOpen"_s
            },
        } },
        { "WebCore::IDBTransactionInfo"_s, {
            {
                "WebCore::IDBResourceIdentifier"_s,
                "identifier()"_s
            },
            {
                "WebCore::IDBTransactionMode"_s,
                "mode()"_s
            },
            {
                "WebCore::IDBTransactionDurability"_s,
                "durability()"_s
            },
            {
                "uint64_t"_s,
                "newVersion()"_s
            },
            {
                "Vector<String>"_s,
                "objectStores()"_s
            },
            {
                "std::unique_ptr<WebCore::IDBDatabaseInfo>"_s,
                "originalDatabaseInfo()"_s
            },
        } },
        { "WebCore::IDBGetRecordData"_s, {
            {
                "WebCore::IDBKeyRangeData"_s,
                "keyRangeData"_s
            },
            {
                "WebCore::IDBGetRecordDataType"_s,
                "type"_s
            },
        } },
        { "WebCore::IDBIndexInfo"_s, {
            {
                "uint64_t"_s,
                "identifier()"_s
            },
            {
                "uint64_t"_s,
                "objectStoreIdentifier()"_s
            },
            {
                "String"_s,
                "name()"_s
            },
            {
                "WebCore::IDBKeyPath"_s,
                "keyPath()"_s
            },
            {
                "bool"_s,
                "unique()"_s
            },
            {
                "bool"_s,
                "multiEntry()"_s
            },
        } },
        { "WebCore::IDBObjectStoreInfo"_s, {
            {
                "uint64_t"_s,
                "identifier()"_s
            },
            {
                "String"_s,
                "name()"_s
            },
            {
                "std::optional<WebCore::IDBKeyPath>"_s,
                "keyPath()"_s
            },
            {
                "bool"_s,
                "autoIncrement()"_s
            },
            {
                "HashMap<uint64_t, WebCore::IDBIndexInfo>"_s,
                "indexMap()"_s
            },
        } },
        { "WebCore::IDBIterateCursorData"_s, {
            {
                "WebCore::IDBKeyData"_s,
                "keyData"_s
            },
            {
                "WebCore::IDBKeyData"_s,
                "primaryKeyData"_s
            },
            {
                "unsigned"_s,
                "count"_s
            },
            {
                "WebCore::IndexedDB::CursorIterateOption"_s,
                "option"_s
            },
        } },
        { "WebCore::IDBResourceIdentifier"_s, {
            {
                "WebCore::IDBConnectionIdentifier"_s,
                "m_idbConnectionIdentifier"_s
            },
            {
                "uint64_t"_s,
                "m_resourceNumber"_s
            },
        } },
        { "WebCore::IDBValue"_s, {
            {
                "WebCore::ThreadSafeDataBuffer"_s,
                "data()"_s
            },
            {
                "Vector<String>"_s,
                "blobURLs()"_s
            },
            {
                "Vector<String>"_s,
                "blobFilePaths()"_s
            },
        } },
        { "WebCore::IDBRequestData"_s, {
            {
                "WebCore::IDBConnectionIdentifier"_s,
                "m_serverConnectionIdentifier"_s
            },
            {
                "WebCore::IDBResourceIdentifier"_s,
                "m_requestIdentifier"_s
            },
            {
                "std::optional<WebCore::IDBResourceIdentifier>"_s,
                "m_transactionIdentifier"_s
            },
            {
                "std::optional<WebCore::IDBResourceIdentifier>"_s,
                "m_cursorIdentifier"_s
            },
            {
                "uint64_t"_s,
                "m_objectStoreIdentifier"_s
            },
            {
                "uint64_t"_s,
                "m_indexIdentifier"_s
            },
            {
                "WebCore::IndexedDB::IndexRecordType"_s,
                "m_indexRecordType"_s
            },
            {
                "std::optional<WebCore::IDBDatabaseIdentifier>"_s,
                "m_databaseIdentifier"_s
            },
            {
                "uint64_t"_s,
                "m_requestedVersion"_s
            },
            {
                "WebCore::IndexedDB::RequestType"_s,
                "m_requestType"_s
            },
        } },
        { "WebCore::IDBDatabaseIdentifier"_s, {
            {
                "String"_s,
                "m_databaseName"_s
            },
            {
                "WebCore::ClientOrigin"_s,
                "m_origin"_s
            },
            {
                "bool"_s,
                "m_isTransient"_s
            },
        } },
        { "WebCore::IDBDatabaseNameAndVersion"_s, {
            {
                "String"_s,
                "name"_s
            },
            {
                "uint64_t"_s,
                "version"_s
            },
        } },
        { "WebCore::IDBResultData"_s, {
            {
                "WebCore::IDBResultType"_s,
                "m_type"_s
            },
            {
                "WebCore::IDBResourceIdentifier"_s,
                "m_requestIdentifier"_s
            },
            {
                "WebCore::IDBError"_s,
                "m_error"_s
            },
            {
                "uint64_t"_s,
                "m_databaseConnectionIdentifier"_s
            },
            {
                "std::unique_ptr<WebCore::IDBDatabaseInfo>"_s,
                "m_databaseInfo"_s
            },
            {
                "std::unique_ptr<WebCore::IDBTransactionInfo>"_s,
                "m_transactionInfo"_s
            },
            {
                "std::unique_ptr<WebCore::IDBKeyData>"_s,
                "m_resultKey"_s
            },
            {
                "std::unique_ptr<WebCore::IDBGetResult>"_s,
                "m_getResult"_s
            },
            {
                "std::unique_ptr<WebCore::IDBGetAllResult>"_s,
                "m_getAllResult"_s
            },
            {
                "uint64_t"_s,
                "m_resultInteger"_s
            },
        } },
        { "WebCore::IDBKeyData"_s, {
            {
                "std::variant<std::nullptr_t, WebCore::IDBKeyData::Invalid, Vector<WebCore::IDBKeyData>, String, double, WebCore::IDBKeyData::Date, WebCore::ThreadSafeDataBuffer, WebCore::IDBKeyData::Min, WebCore::IDBKeyData::Max>"_s,
                "value()"_s
            },
        } },
        { "WebCore::IDBKeyData::Invalid"_s, {
        } },
        { "WebCore::IDBKeyData::Min"_s, {
        } },
        { "WebCore::IDBKeyData::Max"_s, {
        } },
        { "WebCore::IDBKeyData::Date"_s, {
            {
                "double"_s,
                "value"_s
            },
        } },
        { "CGSize"_s, {
            {
                "CGFloat"_s,
                "width"_s
            },
            {
                "CGFloat"_s,
                "height"_s
            },
        } },
        { "CGPoint"_s, {
            {
                "CGFloat"_s,
                "x"_s
            },
            {
                "CGFloat"_s,
                "y"_s
            },
        } },
        { "CGRect"_s, {
            {
                "CGPoint"_s,
                "origin"_s
            },
            {
                "CGSize"_s,
                "size"_s
            },
        } },
        { "CGAffineTransform"_s, {
            {
                "CGFloat"_s,
                "a"_s
            },
            {
                "CGFloat"_s,
                "b"_s
            },
            {
                "CGFloat"_s,
                "c"_s
            },
            {
                "CGFloat"_s,
                "d"_s
            },
            {
                "CGFloat"_s,
                "tx"_s
            },
            {
                "CGFloat"_s,
                "ty"_s
            },
        } },
        { "WebCore::FloatRect"_s, {
            {
                "WebCore::FloatPoint"_s,
                "location()"_s
            },
            {
                "WebCore::FloatSize"_s,
                "size()"_s
            },
        } },
        { "WebCore::LinearTimingFunction::Point"_s, {
            {
                "double"_s,
                "value"_s
            },
            {
                "double"_s,
                "progress"_s
            },
        } },
        { "WebCore::LinearTimingFunction"_s, {
            {
                "Vector<WebCore::LinearTimingFunction::Point>"_s,
                "points()"_s
            },
        } },
        { "WebCore::CubicBezierTimingFunction"_s, {
            {
                "WebCore::CubicBezierTimingFunction::TimingFunctionPreset"_s,
                "timingFunctionPreset()"_s
            },
            {
                "double"_s,
                "x1()"_s
            },
            {
                "double"_s,
                "y1()"_s
            },
            {
                "double"_s,
                "x2()"_s
            },
            {
                "double"_s,
                "y2()"_s
            },
        } },
        { "WebCore::StepsTimingFunction"_s, {
            {
                "int"_s,
                "numberOfSteps()"_s
            },
            {
                "std::optional<WebCore::StepsTimingFunction::StepPosition>"_s,
                "stepPosition()"_s
            },
        } },
        { "WebCore::SpringTimingFunction"_s, {
            {
                "double"_s,
                "mass()"_s
            },
            {
                "double"_s,
                "stiffness()"_s
            },
            {
                "double"_s,
                "damping()"_s
            },
            {
                "double"_s,
                "initialVelocity()"_s
            },
        } },
        { "WebCore::ResourceLoadStatistics"_s, {
            {
                "WebCore::RegistrableDomain"_s,
                "registrableDomain"_s
            },
            {
                "WallTime"_s,
                "lastSeen"_s
            },
            {
                "bool"_s,
                "hadUserInteraction"_s
            },
            {
                "WallTime"_s,
                "mostRecentUserInteractionTime"_s
            },
            {
                "bool"_s,
                "grandfathered"_s
            },
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "storageAccessUnderTopFrameDomains"_s
            },
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "topFrameUniqueRedirectsTo"_s
            },
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "topFrameUniqueRedirectsToSinceSameSiteStrictEnforcement"_s
            },
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "topFrameUniqueRedirectsFrom"_s
            },
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "topFrameLinkDecorationsFrom"_s
            },
            {
                "bool"_s,
                "gotLinkDecorationFromPrevalentResource"_s
            },
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "topFrameLoadedThirdPartyScripts"_s
            },
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "subframeUnderTopFrameDomains"_s
            },
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "subresourceUnderTopFrameDomains"_s
            },
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "subresourceUniqueRedirectsTo"_s
            },
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "subresourceUniqueRedirectsFrom"_s
            },
            {
                "bool"_s,
                "isPrevalentResource"_s
            },
            {
                "bool"_s,
                "isVeryPrevalentResource"_s
            },
            {
                "unsigned"_s,
                "dataRecordsRemoved"_s
            },
            {
                "unsigned"_s,
                "timesAccessedAsFirstPartyDueToUserInteraction"_s
            },
            {
                "unsigned"_s,
                "timesAccessedAsFirstPartyDueToStorageAccessAPI"_s
            },
#if ENABLE(WEB_API_STATISTICS)
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "topFrameRegistrableDomainsWhichAccessedWebAPIs"_s
            },
#endif
#if ENABLE(WEB_API_STATISTICS)
            {
                "HashSet<String>"_s,
                "fontsFailedToLoad"_s
            },
#endif
#if ENABLE(WEB_API_STATISTICS)
            {
                "HashSet<String>"_s,
                "fontsSuccessfullyLoaded"_s
            },
#endif
#if ENABLE(WEB_API_STATISTICS)
            {
                "WebCore::CanvasActivityRecord"_s,
                "canvasActivityRecord"_s
            },
#endif
#if ENABLE(WEB_API_STATISTICS)
            {
                "OptionSet<WebCore::NavigatorAPIsAccessed>"_s,
                "navigatorFunctionsAccessed"_s
            },
#endif
#if ENABLE(WEB_API_STATISTICS)
            {
                "OptionSet<WebCore::ScreenAPIsAccessed>"_s,
                "screenFunctionsAccessed"_s
            },
#endif
        } },
        { "WebCore::GraphicsContextGLActiveInfo"_s, {
            {
                "String"_s,
                "name"_s
            },
            {
                "GCGLenum"_s,
                "type"_s
            },
            {
                "GCGLint"_s,
                "size"_s
            },
        } },
        { "WebCore::ViewportAttributes"_s, {
            {
                "WebCore::FloatSize"_s,
                "layoutSize"_s
            },
            {
                "float"_s,
                "initialScale"_s
            },
            {
                "float"_s,
                "minimumScale"_s
            },
            {
                "float"_s,
                "maximumScale"_s
            },
            {
                "float"_s,
                "userScalable"_s
            },
            {
                "float"_s,
                "orientation"_s
            },
            {
                "float"_s,
                "shrinkToFit"_s
            },
            {
                "WebCore::ViewportFit"_s,
                "viewportFit"_s
            },
        } },
        { "WebCore::ShareDataWithParsedURL"_s, {
            {
                "WebCore::ShareData"_s,
                "shareData"_s
            },
            {
                "std::optional<URL>"_s,
                "url"_s
            },
            {
                "Vector<WebCore::RawFile>"_s,
                "files"_s
            },
            {
                "WebCore::ShareDataOriginator"_s,
                "originator"_s
            },
        } },
        { "WebCore::ShareData"_s, {
            {
                "String"_s,
                "title"_s
            },
            {
                "String"_s,
                "text"_s
            },
            {
                "String"_s,
                "url"_s
            },
        } },
        { "WebCore::RawFile"_s, {
            {
                "String"_s,
                "fileName"_s
            },
            {
                "RefPtr<WebCore::SharedBuffer>"_s,
                "fileData"_s
            },
        } },
        { "WebCore::FloatRoundedRect"_s, {
            {
                "WebCore::FloatRect"_s,
                "rect()"_s
            },
            {
                "WebCore::FloatSize"_s,
                "radii().topLeft()"_s
            },
            {
                "WebCore::FloatSize"_s,
                "radii().topRight()"_s
            },
            {
                "WebCore::FloatSize"_s,
                "radii().bottomLeft()"_s
            },
            {
                "WebCore::FloatSize"_s,
                "radii().bottomRight()"_s
            },
        } },
        { "WebCore::IntRect"_s, {
            {
                "WebCore::IntPoint"_s,
                "location()"_s
            },
            {
                "WebCore::IntSize"_s,
                "size()"_s
            },
        } },
        { "WebCore::IntPoint"_s, {
            {
                "int"_s,
                "x()"_s
            },
            {
                "int"_s,
                "y()"_s
            },
        } },
        { "WebCore::IntSize"_s, {
            {
                "int"_s,
                "width()"_s
            },
            {
                "int"_s,
                "height()"_s
            },
        } },
        { "WebCore::FloatSize"_s, {
            {
                "float"_s,
                "width()"_s
            },
            {
                "float"_s,
                "height()"_s
            },
        } },
        { "WebCore::LayoutUnit"_s, {
            {
                "int"_s,
                "rawValue()"_s
            },
        } },
        { "WebCore::LayoutPoint"_s, {
            {
                "WebCore::LayoutUnit"_s,
                "x()"_s
            },
            {
                "WebCore::LayoutUnit"_s,
                "y()"_s
            },
        } },
        { "WebCore::LayoutSize"_s, {
            {
                "WebCore::LayoutUnit"_s,
                "width()"_s
            },
            {
                "WebCore::LayoutUnit"_s,
                "height()"_s
            },
        } },
        { "WebCore::DictionaryPopupInfo"_s, {
            {
                "WebCore::FloatPoint"_s,
                "origin"_s
            },
            {
                "WebCore::TextIndicatorData"_s,
                "textIndicator"_s
            },
#if PLATFORM(COCOA)
            {
                "WebCore::DictionaryPopupInfoCocoa"_s,
                "platformData"_s
            },
#endif
        } },
        { "WebCore::PrivateClickMeasurement"_s, {
            {
                "uint8_t"_s,
                "sourceID()"_s
            },
            {
                "WebCore::PCM::SourceSite"_s,
                "sourceSite()"_s
            },
            {
                "WebCore::PCM::AttributionDestinationSite"_s,
                "destinationSite()"_s
            },
            {
                "WallTime"_s,
                "timeOfAdClick()"_s
            },
            {
                "WebCore::PCM::AttributionEphemeral"_s,
                "isEphemeral()"_s
            },
            {
                "std::optional<uint64_t>"_s,
                "adamID()"_s
            },
            {
                "std::optional<WebCore::PCM::AttributionTriggerData>"_s,
                "attributionTriggerData()"_s
            },
            {
                "WebCore::PCM::AttributionTimeToSendData"_s,
                "timesToSend()"_s
            },
            {
                "std::optional<WebCore::PCM::EphemeralNonce>"_s,
                "ephemeralSourceNonce()"_s
            },
            {
                "String"_s,
                "sourceApplicationBundleID()"_s
            },
        } },
        { "WebCore::PCM::SourceSite"_s, {
            {
                "WebCore::RegistrableDomain"_s,
                "registrableDomain"_s
            },
        } },
        { "WebCore::PCM::AttributionDestinationSite"_s, {
            {
                "WebCore::RegistrableDomain"_s,
                "registrableDomain"_s
            },
        } },
        { "WebCore::PCM::EphemeralNonce"_s, {
            {
                "String"_s,
                "nonce"_s
            },
        } },
        { "WebCore::PCM::AttributionTriggerData"_s, {
            {
                "uint8_t"_s,
                "data"_s
            },
            {
                "uint8_t"_s,
                "priority"_s
            },
            {
                "WebCore::PCM::WasSent"_s,
                "wasSent"_s
            },
            {
                "std::optional<WebCore::RegistrableDomain>"_s,
                "sourceRegistrableDomain"_s
            },
            {
                "std::optional<WebCore::PCM::EphemeralNonce>"_s,
                "ephemeralDestinationNonce"_s
            },
            {
                "std::optional<WebCore::RegistrableDomain>"_s,
                "destinationSite"_s
            },
        } },
        { "WebCore::PCM::AttributionTimeToSendData"_s, {
            {
                "std::optional<WallTime>"_s,
                "sourceEarliestTimeToSend"_s
            },
            {
                "std::optional<WallTime>"_s,
                "destinationEarliestTimeToSend"_s
            },
        } },
        { "WebCore::ApplePayRecurringPaymentRequest"_s, {
            {
                "String"_s,
                "paymentDescription"_s
            },
            {
                "WebCore::ApplePayLineItem"_s,
                "regularBilling"_s
            },
            {
                "std::optional<WebCore::ApplePayLineItem>"_s,
                "trialBilling"_s
            },
            {
                "String"_s,
                "billingAgreement"_s
            },
            {
                "String"_s,
                "managementURL"_s
            },
            {
                "String"_s,
                "tokenNotificationURL"_s
            },
        } },
        { "WebCore::ApplePayPaymentTokenContext"_s, {
            {
                "String"_s,
                "merchantIdentifier"_s
            },
            {
                "String"_s,
                "externalIdentifier"_s
            },
            {
                "String"_s,
                "merchantName"_s
            },
            {
                "String"_s,
                "merchantDomain"_s
            },
            {
                "String"_s,
                "amount"_s
            },
        } },
        { "WebCore::ApplePayDeferredPaymentRequest"_s, {
            {
                "String"_s,
                "billingAgreement"_s
            },
            {
                "WebCore::ApplePayLineItem"_s,
                "deferredBilling"_s
            },
            {
                "WallTime"_s,
                "freeCancellationDate"_s
            },
            {
                "String"_s,
                "freeCancellationDateTimeZone"_s
            },
            {
                "String"_s,
                "managementURL"_s
            },
            {
                "String"_s,
                "paymentDescription"_s
            },
            {
                "String"_s,
                "tokenNotificationURL"_s
            },
        } },
        { "WebCore::ApplePayPaymentOrderDetails"_s, {
            {
                "String"_s,
                "orderTypeIdentifier"_s
            },
            {
                "String"_s,
                "orderIdentifier"_s
            },
            {
                "String"_s,
                "webServiceURL"_s
            },
            {
                "String"_s,
                "authenticationToken"_s
            },
        } },
        { "WebCore::ApplePayAMSUIRequest"_s, {
            {
                "String"_s,
                "engagementRequest"_s
            },
        } },
        { "WebCore::ApplePayAutomaticReloadPaymentRequest"_s, {
            {
                "String"_s,
                "paymentDescription"_s
            },
            {
                "WebCore::ApplePayLineItem"_s,
                "automaticReloadBilling"_s
            },
            {
                "String"_s,
                "billingAgreement"_s
            },
            {
                "String"_s,
                "managementURL"_s
            },
            {
                "String"_s,
                "tokenNotificationURL"_s
            },
        } },
        { "WebCore::ApplePayDateComponents"_s, {
            {
                "std::optional<unsigned>"_s,
                "years"_s
            },
            {
                "std::optional<unsigned>"_s,
                "months"_s
            },
            {
                "std::optional<unsigned>"_s,
                "days"_s
            },
            {
                "std::optional<unsigned>"_s,
                "hours"_s
            },
        } },
        { "WebCore::ApplePayDateComponentsRange"_s, {
            {
                "WebCore::ApplePayDateComponents"_s,
                "startDateComponents"_s
            },
            {
                "WebCore::ApplePayDateComponents"_s,
                "endDateComponents"_s
            },
        } },
        { "WebCore::ApplePaySetupConfiguration"_s, {
            {
                "String"_s,
                "merchantIdentifier"_s
            },
            {
                "String"_s,
                "referrerIdentifier"_s
            },
            {
                "String"_s,
                "signature"_s
            },
            {
                "Vector<String>"_s,
                "signedFields"_s
            },
        } },
        { "WebCore::ApplePayLineItem"_s, {
            {
                "WebCore::ApplePayLineItem::Type"_s,
                "type"_s
            },
            {
                "String"_s,
                "label"_s
            },
            {
                "String"_s,
                "amount"_s
            },
            {
                "WebCore::ApplePayPaymentTiming"_s,
                "paymentTiming"_s
            },
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
            {
                "WallTime"_s,
                "recurringPaymentStartDate"_s
            },
#endif
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
            {
                "WebCore::ApplePayRecurringPaymentDateUnit"_s,
                "recurringPaymentIntervalUnit"_s
            },
#endif
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
            {
                "unsigned"_s,
                "recurringPaymentIntervalCount"_s
            },
#endif
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
            {
                "WallTime"_s,
                "recurringPaymentEndDate"_s
            },
#endif
#if ENABLE(APPLE_PAY_DEFERRED_LINE_ITEM)
            {
                "WallTime"_s,
                "deferredPaymentDate"_s
            },
#endif
#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_LINE_ITEM)
            {
                "String"_s,
                "automaticReloadPaymentThresholdAmount"_s
            },
#endif
        } },
        { "WebCore::ApplePayShippingMethod"_s, {
            {
                "String"_s,
                "label"_s
            },
            {
                "String"_s,
                "detail"_s
            },
            {
                "String"_s,
                "amount"_s
            },
            {
                "String"_s,
                "identifier"_s
            },
#if ENABLE(APPLE_PAY_SHIPPING_METHOD_DATE_COMPONENTS_RANGE)
            {
                "std::optional<WebCore::ApplePayDateComponentsRange>"_s,
                "dateComponentsRange"_s
            },
#endif
#if ENABLE(APPLE_PAY_SELECTED_SHIPPING_METHOD)
            {
                "bool"_s,
                "selected"_s
            },
#endif
        } },
        { "WebCore::ApplePayError"_s, {
            {
                "WebCore::ApplePayErrorCode"_s,
                "code()"_s
            },
            {
                "std::optional<WebCore::ApplePayErrorContactField>"_s,
                "contactField()"_s
            },
            {
                "String"_s,
                "message()"_s
            },
        } },
        { "WebCore::ApplePayLogoSystemImage"_s, {
            {
                "WebCore::ApplePayLogoStyle"_s,
                "applePayLogoStyle()"_s
            },
        } },
        { "WebCore::ApplePayDetailsUpdateBase"_s, {
            {
                "WebCore::ApplePayLineItem"_s,
                "newTotal"_s
            },
            {
                "Vector<WebCore::ApplePayLineItem>"_s,
                "newLineItems"_s
            },
#if ENABLE(APPLE_PAY_RECURRING_PAYMENTS)
            {
                "std::optional<WebCore::ApplePayRecurringPaymentRequest>"_s,
                "newRecurringPaymentRequest"_s
            },
#endif
#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_PAYMENTS)
            {
                "std::optional<WebCore::ApplePayAutomaticReloadPaymentRequest>"_s,
                "newAutomaticReloadPaymentRequest"_s
            },
#endif
#if ENABLE(APPLE_PAY_MULTI_MERCHANT_PAYMENTS)
            {
                "std::optional<Vector<WebCore::ApplePayPaymentTokenContext>>"_s,
                "newMultiTokenContexts"_s
            },
#endif
#if ENABLE(APPLE_PAY_DEFERRED_PAYMENTS)
            {
                "std::optional<WebCore::ApplePayDeferredPaymentRequest>"_s,
                "newDeferredPaymentRequest"_s
            },
#endif
        } },
        { "WebCore::ApplePayPaymentMethodUpdate"_s, {
#if ENABLE(APPLE_PAY_UPDATE_SHIPPING_METHODS_WHEN_CHANGING_LINE_ITEMS)
            {
                "Vector<RefPtr<WebCore::ApplePayError>>"_s,
                "errors"_s
            },
#endif
#if ENABLE(APPLE_PAY_UPDATE_SHIPPING_METHODS_WHEN_CHANGING_LINE_ITEMS)
            {
                "Vector<WebCore::ApplePayShippingMethod>"_s,
                "newShippingMethods"_s
            },
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
            {
                "String"_s,
                "installmentGroupIdentifier"_s
            },
#endif
        } },
        { "WebCore::ApplePayShippingContactUpdate"_s, {
            {
                "Vector<RefPtr<WebCore::ApplePayError>>"_s,
                "errors"_s
            },
            {
                "Vector<WebCore::ApplePayShippingMethod>"_s,
                "newShippingMethods"_s
            },
        } },
        { "WebCore::ApplePayShippingMethodUpdate"_s, {
#if ENABLE(APPLE_PAY_UPDATE_SHIPPING_METHODS_WHEN_CHANGING_LINE_ITEMS)
            {
                "Vector<WebCore::ApplePayShippingMethod>"_s,
                "newShippingMethods"_s
            },
#endif
        } },
        { "WebCore::ApplePayPaymentAuthorizationResult"_s, {
            {
                "unsigned short"_s,
                "status"_s
            },
            {
                "Vector<RefPtr<WebCore::ApplePayError>>"_s,
                "errors"_s
            },
#if ENABLE(APPLE_PAY_PAYMENT_ORDER_DETAILS)
            {
                "std::optional<WebCore::ApplePayPaymentOrderDetails>"_s,
                "orderDetails"_s
            },
#endif
        } },
        { "WebCore::ApplePayInstallmentConfiguration"_s, {
            {
                "WebCore::ApplePaySetupFeatureType"_s,
                "featureType"_s
            },
            {
                "String"_s,
                "merchandisingImageData"_s
            },
            {
                "String"_s,
                "openToBuyThresholdAmount"_s
            },
            {
                "String"_s,
                "bindingTotalAmount"_s
            },
            {
                "String"_s,
                "currencyCode"_s
            },
            {
                "bool"_s,
                "isInStorePurchase"_s
            },
            {
                "String"_s,
                "merchantIdentifier"_s
            },
            {
                "String"_s,
                "referrerIdentifier"_s
            },
            {
                "Vector<WebCore::ApplePayInstallmentItem>"_s,
                "items"_s
            },
            {
                "String"_s,
                "applicationMetadata"_s
            },
            {
                "WebCore::ApplePayInstallmentRetailChannel"_s,
                "retailChannel"_s
            },
        } },
        { "WebCore::PaymentInstallmentConfiguration"_s, {
            {
                "std::optional<WebCore::ApplePayInstallmentConfiguration>"_s,
                "applePayInstallmentConfiguration()"_s
            },
        } },
        { "WebCore::ApplePayInstallmentItem"_s, {
            {
                "WebCore::ApplePayInstallmentItemType"_s,
                "type"_s
            },
            {
                "String"_s,
                "amount"_s
            },
            {
                "String"_s,
                "currencyCode"_s
            },
            {
                "String"_s,
                "programIdentifier"_s
            },
            {
                "String"_s,
                "apr"_s
            },
            {
                "String"_s,
                "programTerms"_s
            },
        } },
        { "WebCore::ApplePayCouponCodeUpdate"_s, {
            {
                "Vector<RefPtr<WebCore::ApplePayError>>"_s,
                "errors"_s
            },
            {
                "Vector<WebCore::ApplePayShippingMethod>"_s,
                "newShippingMethods"_s
            },
        } },
        { "WebCore::ApplicationManifest::Icon"_s, {
            {
                "URL"_s,
                "src"_s
            },
            {
                "Vector<String>"_s,
                "sizes"_s
            },
            {
                "String"_s,
                "type"_s
            },
            {
                "OptionSet<WebCore::ApplicationManifest::Icon::Purpose>"_s,
                "purposes"_s
            },
        } },
        { "WebCore::ApplicationManifest"_s, {
            {
                "String"_s,
                "name"_s
            },
            {
                "String"_s,
                "shortName"_s
            },
            {
                "String"_s,
                "description"_s
            },
            {
                "URL"_s,
                "scope"_s
            },
            {
                "WebCore::ApplicationManifest::Display"_s,
                "display"_s
            },
            {
                "std::optional<WebCore::ScreenOrientationLockType>"_s,
                "orientation"_s
            },
            {
                "URL"_s,
                "startURL"_s
            },
            {
                "URL"_s,
                "id"_s
            },
            {
                "WebCore::Color"_s,
                "backgroundColor"_s
            },
            {
                "WebCore::Color"_s,
                "themeColor"_s
            },
            {
                "Vector<WebCore::ApplicationManifest::Icon>"_s,
                "icons"_s
            },
        } },
        { "WebCore::RetrieveRecordsOptions"_s, {
            {
                "WebCore::ResourceRequest"_s,
                "request"_s
            },
            {
                "WebCore::CrossOriginEmbedderPolicy"_s,
                "crossOriginEmbedderPolicy"_s
            },
            {
                "Ref<WebCore::SecurityOrigin>"_s,
                "sourceOrigin"_s
            },
            {
                "bool"_s,
                "ignoreSearch"_s
            },
            {
                "bool"_s,
                "ignoreMethod"_s
            },
            {
                "bool"_s,
                "ignoreVary"_s
            },
            {
                "bool"_s,
                "shouldProvideResponse"_s
            },
        } },
        { "WebCore::ContactInfo"_s, {
            {
                "Vector<String>"_s,
                "name"_s
            },
            {
                "Vector<String>"_s,
                "email"_s
            },
            {
                "Vector<String>"_s,
                "tel"_s
            },
        } },
        { "WebCore::ContactsRequestData"_s, {
            {
                "Vector<WebCore::ContactProperty>"_s,
                "properties"_s
            },
            {
                "bool"_s,
                "multiple"_s
            },
            {
                "String"_s,
                "url"_s
            },
        } },
        { "WebCore::MediaPositionState"_s, {
            {
                "double"_s,
                "duration"_s
            },
            {
                "double"_s,
                "playbackRate"_s
            },
            {
                "double"_s,
                "position"_s
            },
        } },
        { "WebCore::DetachedRTCDataChannel"_s, {
            {
                "WebCore::RTCDataChannelIdentifier"_s,
                "identifier"_s
            },
            {
                "String"_s,
                "label"_s
            },
            {
                "WebCore::RTCDataChannelInit"_s,
                "options"_s
            },
            {
                "WebCore::RTCDataChannelState"_s,
                "state"_s
            },
        } },
        { "WebCore::WebCodecsEncodedVideoChunkData"_s, {
            {
                "WebCore::WebCodecsEncodedVideoChunkType"_s,
                "type"_s
            },
            {
                "int64_t"_s,
                "timestamp"_s
            },
            {
                "std::optional<uint64_t>"_s,
                "duration"_s
            },
            {
                "Vector<uint8_t>"_s,
                "buffer"_s
            },
        } },
        { "WebCore::HTMLModelElementCamera"_s, {
            {
                "double"_s,
                "pitch"_s
            },
            {
                "double"_s,
                "yaw"_s
            },
            {
                "double"_s,
                "scale"_s
            },
        } },
        { "WebCore::NotificationData"_s, {
            {
                "String"_s,
                "title"_s
            },
            {
                "String"_s,
                "body"_s
            },
            {
                "String"_s,
                "iconURL"_s
            },
            {
                "String"_s,
                "tag"_s
            },
            {
                "String"_s,
                "language"_s
            },
            {
                "WebCore::NotificationDirection"_s,
                "direction"_s
            },
            {
                "String"_s,
                "originString"_s
            },
            {
                "URL"_s,
                "serviceWorkerRegistrationURL"_s
            },
            {
                "WTF::UUID"_s,
                "notificationID"_s
            },
            {
                "WebCore::ScriptExecutionContextIdentifier"_s,
                "contextIdentifier"_s
            },
            {
                "PAL::SessionID"_s,
                "sourceSession"_s
            },
            {
                "MonotonicTime"_s,
                "creationTime"_s
            },
            {
                "Vector<uint8_t>"_s,
                "data"_s
            },
            {
                "std::optional<bool>"_s,
                "silent"_s
            },
        } },
        { "WebCore::PermissionDescriptor"_s, {
            {
                "WebCore::PermissionName"_s,
                "name"_s
            },
        } },
        { "WebCore::PushSubscriptionData"_s, {
            {
                "WebCore::PushSubscriptionIdentifier"_s,
                "identifier"_s
            },
            {
                "String"_s,
                "endpoint"_s
            },
            {
                "std::optional<WebCore::EpochTimeStamp>"_s,
                "expirationTime"_s
            },
            {
                "Vector<uint8_t>"_s,
                "serverVAPIDPublicKey"_s
            },
            {
                "Vector<uint8_t>"_s,
                "clientECDHPublicKey"_s
            },
            {
                "Vector<uint8_t>"_s,
                "sharedAuthenticationSecret"_s
            },
        } },
        { "WebCore::DeprecationReportBody"_s, {
            {
                "String"_s,
                "id()"_s
            },
            {
                "WallTime"_s,
                "anticipatedRemoval()"_s
            },
            {
                "String"_s,
                "message()"_s
            },
            {
                "String"_s,
                "sourceFile()"_s
            },
            {
                "std::optional<unsigned>"_s,
                "lineNumber()"_s
            },
            {
                "std::optional<unsigned>"_s,
                "columnNumber()"_s
            },
        } },
        { "WebCore::Report"_s, {
            {
                "String"_s,
                "type()"_s
            },
            {
                "String"_s,
                "url()"_s
            },
            {
                "RefPtr<WebCore::ReportBody>"_s,
                "body()"_s
            },
        } },
        { "WebCore::TestReportBody"_s, {
            {
                "String"_s,
                "message()"_s
            },
        } },
        { "WebCore::SpeechRecognitionError"_s, {
            {
                "WebCore::SpeechRecognitionErrorType"_s,
                "type"_s
            },
            {
                "String"_s,
                "message"_s
            },
        } },
        { "WebCore::SpeechRecognitionRequestInfo"_s, {
            {
                "WebCore::SpeechRecognitionConnectionClientIdentifier"_s,
                "clientIdentifier"_s
            },
            {
                "String"_s,
                "lang"_s
            },
            {
                "bool"_s,
                "continuous"_s
            },
            {
                "bool"_s,
                "interimResults"_s
            },
            {
                "uint64_t"_s,
                "maxAlternatives"_s
            },
            {
                "WebCore::ClientOrigin"_s,
                "clientOrigin"_s
            },
            {
                "WebCore::FrameIdentifier"_s,
                "frameIdentifier"_s
            },
        } },
        { "WebCore::SpeechRecognitionAlternativeData"_s, {
            {
                "String"_s,
                "transcript"_s
            },
            {
                "double"_s,
                "confidence"_s
            },
        } },
        { "WebCore::SpeechRecognitionResultData"_s, {
            {
                "Vector<WebCore::SpeechRecognitionAlternativeData>"_s,
                "alternatives"_s
            },
            {
                "bool"_s,
                "isFinal"_s
            },
        } },
        { "WebCore::WebLockManagerSnapshot"_s, {
            {
                "Vector<WebCore::WebLockManagerSnapshot::Info>"_s,
                "held"_s
            },
            {
                "Vector<WebCore::WebLockManagerSnapshot::Info>"_s,
                "pending"_s
            },
        } },
        { "WebCore::WebLockManagerSnapshot::Info"_s, {
            {
                "String"_s,
                "name"_s
            },
            {
                "WebCore::WebLockMode"_s,
                "mode"_s
            },
            {
                "String"_s,
                "clientId"_s
            },
        } },
        { "WebCore::AuthenticationExtensionsClientInputs::LargeBlobInputs"_s, {
            {
                "String"_s,
                "support"_s
            },
            {
                "std::optional<bool>"_s,
                "read"_s
            },
            {
                "std::optional<WebCore::BufferSource>"_s,
                "write"_s
            },
        } },
        { "WebCore::AuthenticationExtensionsClientInputs"_s, {
            {
                "String"_s,
                "appid"_s
            },
            {
                "std::optional<WebCore::AuthenticationExtensionsClientInputs::LargeBlobInputs>"_s,
                "largeBlob"_s
            },
        } },
        { "WebCore::AuthenticationExtensionsClientOutputs::CredentialPropertiesOutput"_s, {
            {
                "bool"_s,
                "rk"_s
            },
        } },
        { "WebCore::AuthenticationExtensionsClientOutputs::LargeBlobOutputs"_s, {
            {
                "std::optional<bool>"_s,
                "supported"_s
            },
            {
                "RefPtr<JSC::ArrayBuffer>"_s,
                "blob"_s
            },
            {
                "std::optional<bool>"_s,
                "written"_s
            },
        } },
        { "WebCore::AuthenticationExtensionsClientOutputs"_s, {
            {
                "std::optional<bool>"_s,
                "appid"_s
            },
            {
                "std::optional<WebCore::AuthenticationExtensionsClientOutputs::CredentialPropertiesOutput>"_s,
                "credProps"_s
            },
            {
                "std::optional<WebCore::AuthenticationExtensionsClientOutputs::LargeBlobOutputs>"_s,
                "largeBlob"_s
            },
        } },
        { "WebCore::PublicKeyCredentialCreationOptions::Parameters"_s, {
            {
                "WebCore::PublicKeyCredentialType"_s,
                "type"_s
            },
            {
                "int64_t"_s,
                "alg"_s
            },
        } },
        { "WebCore::PublicKeyCredentialCreationOptions::AuthenticatorSelectionCriteria"_s, {
            {
                "std::optional<WebCore::AuthenticatorAttachment>"_s,
                "authenticatorAttachment"_s
            },
            {
                "std::optional<WebCore::ResidentKeyRequirement>"_s,
                "residentKey"_s
            },
            {
                "bool"_s,
                "requireResidentKey"_s
            },
            {
                "WebCore::UserVerificationRequirement"_s,
                "userVerification"_s
            },
        } },
        { "WebCore::PublicKeyCredentialCreationOptions::Entity"_s, {
            {
                "String"_s,
                "name"_s
            },
            {
                "String"_s,
                "icon"_s
            },
        } },
        { "WebCore::PublicKeyCredentialCreationOptions::RpEntity"_s, {
            {
                "std::optional<String>"_s,
                "id"_s
            },
        } },
        { "WebCore::PublicKeyCredentialCreationOptions::UserEntity"_s, {
            {
                "WebCore::BufferSource"_s,
                "id"_s
            },
            {
                "String"_s,
                "displayName"_s
            },
        } },
        { "WebCore::PublicKeyCredentialDescriptor"_s, {
            {
                "WebCore::PublicKeyCredentialType"_s,
                "type"_s
            },
            {
                "WebCore::BufferSource"_s,
                "id"_s
            },
            {
                "Vector<WebCore::AuthenticatorTransport>"_s,
                "transports"_s
            },
        } },
        { "WebCore::PublicKeyCredentialCreationOptions"_s, {
#if ENABLE(WEB_AUTHN)
            {
                "WebCore::PublicKeyCredentialCreationOptions::RpEntity"_s,
                "rp"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "WebCore::PublicKeyCredentialCreationOptions::UserEntity"_s,
                "user"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "WebCore::BufferSource"_s,
                "challenge"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "Vector<WebCore::PublicKeyCredentialCreationOptions::Parameters>"_s,
                "pubKeyCredParams"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "std::optional<unsigned>"_s,
                "timeout"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "Vector<WebCore::PublicKeyCredentialDescriptor>"_s,
                "excludeCredentials"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "std::optional<WebCore::PublicKeyCredentialCreationOptions::AuthenticatorSelectionCriteria>"_s,
                "authenticatorSelection"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "WebCore::AttestationConveyancePreference"_s,
                "attestation"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "std::optional<WebCore::AuthenticationExtensionsClientInputs>"_s,
                "extensions"_s
            },
#endif
        } },
        { "WebCore::PublicKeyCredentialRequestOptions"_s, {
#if ENABLE(WEB_AUTHN)
            {
                "WebCore::BufferSource"_s,
                "challenge"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "std::optional<unsigned>"_s,
                "timeout"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "String"_s,
                "rpId"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "Vector<WebCore::PublicKeyCredentialDescriptor>"_s,
                "allowCredentials"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "WebCore::UserVerificationRequirement"_s,
                "userVerification"_s
            },
#endif
#if ENABLE(WEB_AUTHN)
            {
                "std::optional<WebCore::AuthenticationExtensionsClientInputs>"_s,
                "extensions"_s
            },
#endif
        } },
        { "WebCore::RegistrableDomain"_s, {
            {
                "String"_s,
                "string()"_s
            },
        } },
        { "WebCore::AudioConfiguration"_s, {
            {
                "String"_s,
                "contentType"_s
            },
            {
                "String"_s,
                "channels"_s
            },
            {
                "std::optional<uint64_t>"_s,
                "bitrate"_s
            },
            {
                "std::optional<uint32_t>"_s,
                "samplerate"_s
            },
            {
                "std::optional<bool>"_s,
                "spatialRendering"_s
            },
        } },
        { "WebCore::Cookie"_s, {
            {
                "String"_s,
                "name"_s
            },
            {
                "String"_s,
                "value"_s
            },
            {
                "String"_s,
                "domain"_s
            },
            {
                "String"_s,
                "path"_s
            },
            {
                "double"_s,
                "created"_s
            },
            {
                "std::optional<double>"_s,
                "expires"_s
            },
            {
                "bool"_s,
                "httpOnly"_s
            },
            {
                "bool"_s,
                "secure"_s
            },
            {
                "bool"_s,
                "session"_s
            },
            {
                "String"_s,
                "comment"_s
            },
            {
                "URL"_s,
                "commentURL"_s
            },
            {
                "Vector<uint16_t>"_s,
                "ports"_s
            },
            {
                "WebCore::Cookie::SameSitePolicy"_s,
                "sameSite"_s
            },
        } },
        { "WebCore::VideoFrameMetadata"_s, {
            {
                "double"_s,
                "presentationTime"_s
            },
            {
                "double"_s,
                "expectedDisplayTime"_s
            },
            {
                "unsigned"_s,
                "width"_s
            },
            {
                "unsigned"_s,
                "height"_s
            },
            {
                "double"_s,
                "mediaTime"_s
            },
            {
                "unsigned"_s,
                "presentedFrames"_s
            },
            {
                "std::optional<double>"_s,
                "processingDuration"_s
            },
            {
                "std::optional<double>"_s,
                "captureTime"_s
            },
            {
                "std::optional<double>"_s,
                "receiveTime"_s
            },
            {
                "std::optional<unsigned>"_s,
                "rtpTimestamp"_s
            },
        } },
        { "WebCore::NavigationPreloadState"_s, {
            {
                "bool"_s,
                "enabled"_s
            },
            {
                "String"_s,
                "headerValue"_s
            },
        } },
        { "WebCore::MockContentFilterSettings"_s, {
            {
                "bool"_s,
                "m_enabled"_s
            },
            {
                "WebCore::MockContentFilterSettings::DecisionPoint"_s,
                "m_decisionPoint"_s
            },
            {
                "WebCore::MockContentFilterSettings::Decision"_s,
                "m_decision"_s
            },
            {
                "WebCore::MockContentFilterSettings::Decision"_s,
                "m_unblockRequestDecision"_s
            },
            {
                "String"_s,
                "m_blockedString"_s
            },
            {
                "String"_s,
                "m_modifiedRequestURL"_s
            },
        } },
        { "WebCore::ExceptionDetails"_s, {
            {
                "String"_s,
                "message"_s
            },
            {
                "int"_s,
                "lineNumber"_s
            },
            {
                "int"_s,
                "columnNumber"_s
            },
            {
                "WebCore::ExceptionDetails::Type"_s,
                "type"_s
            },
            {
                "String"_s,
                "sourceURL"_s
            },
        } },
        { "WebCore::FloatBoxExtent"_s, {
            {
                "float"_s,
                "top()"_s
            },
            {
                "float"_s,
                "right()"_s
            },
            {
                "float"_s,
                "bottom()"_s
            },
            {
                "float"_s,
                "left()"_s
            },
        } },
        { "WebCore::DisplayList::SetInlineFillColor"_s, {
            {
                "uint8_t"_s,
                "colorData().resolved().red"_s
            },
            {
                "uint8_t"_s,
                "colorData().resolved().green"_s
            },
            {
                "uint8_t"_s,
                "colorData().resolved().blue"_s
            },
            {
                "uint8_t"_s,
                "colorData().resolved().alpha"_s
            },
        } },
        { "WebCore::DisplayList::SetInlineStrokeColor"_s, {
            {
                "uint8_t"_s,
                "colorData().resolved().red"_s
            },
            {
                "uint8_t"_s,
                "colorData().resolved().green"_s
            },
            {
                "uint8_t"_s,
                "colorData().resolved().blue"_s
            },
            {
                "uint8_t"_s,
                "colorData().resolved().alpha"_s
            },
        } },
        { "WebCore::HTTPHeaderMap::CommonHeader"_s, {
            {
                "WebCore::HTTPHeaderName"_s,
                "key"_s
            },
            {
                "String"_s,
                "value"_s
            },
        } },
        { "WebCore::HTTPHeaderMap::UncommonHeader"_s, {
            {
                "String"_s,
                "key"_s
            },
            {
                "String"_s,
                "value"_s
            },
        } },
        { "WebCore::HTTPHeaderMap"_s, {
            {
                "Vector<WebCore::HTTPHeaderMap::CommonHeader, 0, CrashOnOverflow, 6>"_s,
                "commonHeaders()"_s
            },
            {
                "Vector<WebCore::HTTPHeaderMap::UncommonHeader, 0, CrashOnOverflow, 0>"_s,
                "uncommonHeaders()"_s
            },
        } },
        { "WebCore::ElementContext"_s, {
            {
                "WebCore::FloatRect"_s,
                "boundingRect"_s
            },
            {
                "WebCore::PageIdentifier"_s,
                "webPageIdentifier"_s
            },
            {
                "WebCore::ScriptExecutionContextIdentifier"_s,
                "documentIdentifier"_s
            },
            {
                "WebCore::ElementIdentifier"_s,
                "elementIdentifier"_s
            },
        } },
        { "WebCore::ElementAnimationContext"_s, {
            {
                "WebCore::ElementContext"_s,
                "element"_s
            },
            {
                "bool"_s,
                "isAnimating"_s
            },
        } },
        { "WebCore::SystemPreviewInfo"_s, {
            {
                "WebCore::ElementContext"_s,
                "element"_s
            },
            {
                "WebCore::IntRect"_s,
                "previewRect"_s
            },
            {
                "bool"_s,
                "isPreview"_s
            },
        } },
        { "WebCore::ResourceRequest::RequestData"_s, {
            {
                "URL"_s,
                "m_url"_s
            },
            {
                "URL"_s,
                "m_firstPartyForCookies"_s
            },
            {
                "double"_s,
                "m_timeoutInterval"_s
            },
            {
                "String"_s,
                "m_httpMethod"_s
            },
            {
                "WebCore::HTTPHeaderMap"_s,
                "m_httpHeaderFields"_s
            },
            {
                "Vector<String>"_s,
                "m_responseContentDispositionEncodingFallbackArray"_s
            },
            {
                "WebCore::ResourceRequestCachePolicy"_s,
                "m_cachePolicy"_s
            },
            {
                "WebCore::ResourceRequestBase::SameSiteDisposition"_s,
                "m_sameSiteDisposition"_s
            },
            {
                "WebCore::ResourceLoadPriority"_s,
                "m_priority"_s
            },
            {
                "WebCore::ResourceRequestRequester"_s,
                "m_requester"_s
            },
            {
                "bool"_s,
                "m_allowCookies"_s
            },
            {
                "bool"_s,
                "m_isTopSite"_s
            },
            {
                "bool"_s,
                "m_isAppInitiated"_s
            },
            {
                "bool"_s,
                "m_privacyProxyFailClosedForUnreachableNonMainHosts"_s
            },
            {
                "bool"_s,
                "m_useAdvancedPrivacyProtections"_s
            },
        } },
        { "WebCore::ResourceRequestPlatformData"_s, {
            {
                "WebCore::ResourceRequest::RequestData"_s,
                "requestData"_s
            },
            {
                "bool"_s,
                "acceptEncoding"_s
            },
            {
                "uint16_t"_s,
                "redirectCount"_s
            },
        } },
        { "WebCore::ResourceRequest"_s, {
            {
                "std::variant<WebCore::ResourceRequest::RequestData, WebCore::ResourceRequestPlatformData>"_s,
                "getRequestDataToSerialize()"_s
            },
            {
                "String"_s,
                "cachePartition()"_s
            },
            {
                "bool"_s,
                "hiddenFromInspector()"_s
            },
        } },
        { "WebCore::ResourceRequest"_s, {
            {
                "WebCore::ResourceRequest::RequestData"_s,
                "getRequestDataToSerialize()"_s
            },
        } },
        { "WebCore::ResourceRequest"_s, {
            {
                "std::variant<WebCore::ResourceRequest::RequestData, WebCore::ResourceRequestPlatformData>"_s,
                "getRequestDataToSerialize()"_s
            },
        } },
        { "WebCore::PlatformColorSpace"_s, {
            {
                "WebCore::PlatformColorSpace::Name"_s,
                "get()"_s
            },
        } },
        { "WebCore::DestinationColorSpace"_s, {
            {
                "WebCore::PlatformColorSpace"_s,
                "serializableColorSpace()"_s
            },
        } },
        { "WebCore::WindowFeatures"_s, {
            {
                "std::optional<float>"_s,
                "x"_s
            },
            {
                "std::optional<float>"_s,
                "y"_s
            },
            {
                "std::optional<float>"_s,
                "width"_s
            },
            {
                "std::optional<float>"_s,
                "height"_s
            },
            {
                "bool"_s,
                "menuBarVisible"_s
            },
            {
                "bool"_s,
                "statusBarVisible"_s
            },
            {
                "bool"_s,
                "toolBarVisible"_s
            },
            {
                "bool"_s,
                "locationBarVisible"_s
            },
            {
                "bool"_s,
                "scrollbarsVisible"_s
            },
            {
                "bool"_s,
                "resizable"_s
            },
            {
                "bool"_s,
                "fullscreen"_s
            },
            {
                "bool"_s,
                "dialog"_s
            },
        } },
        { "WebCore::CompositionUnderline"_s, {
            {
                "unsigned"_s,
                "startOffset"_s
            },
            {
                "unsigned"_s,
                "endOffset"_s
            },
            {
                "WebCore::CompositionUnderlineColor"_s,
                "compositionUnderlineColor"_s
            },
            {
                "WebCore::Color"_s,
                "color"_s
            },
            {
                "bool"_s,
                "thick"_s
            },
        } },
        { "WebCore::FileChooserSettings"_s, {
            {
                "bool"_s,
                "allowsDirectories"_s
            },
            {
                "bool"_s,
                "allowsMultipleFiles"_s
            },
            {
                "Vector<String>"_s,
                "acceptMIMETypes"_s
            },
            {
                "Vector<String>"_s,
                "acceptFileExtensions"_s
            },
            {
                "Vector<String>"_s,
                "selectedFiles"_s
            },
#if ENABLE(MEDIA_CAPTURE)
            {
                "WebCore::MediaCaptureType"_s,
                "mediaCaptureType"_s
            },
#endif
        } },
        { "WebCore::GrammarDetail"_s, {
            {
                "WebCore::CharacterRange"_s,
                "range"_s
            },
            {
                "Vector<String>"_s,
                "guesses"_s
            },
            {
                "String"_s,
                "userDescription"_s
            },
        } },
        { "WebCore::TextCheckingResult"_s, {
            {
                "OptionSet<WebCore::TextCheckingType>"_s,
                "type"_s
            },
            {
                "WebCore::CharacterRange"_s,
                "range"_s
            },
            {
                "Vector<WebCore::GrammarDetail>"_s,
                "details"_s
            },
            {
                "String"_s,
                "replacement"_s
            },
        } },
        { "WebCore::TextCheckingRequestData"_s, {
            {
                "std::optional<WebCore::TextCheckingRequestIdentifier>"_s,
                "identifier()"_s
            },
            {
                "String"_s,
                "text()"_s
            },
            {
                "OptionSet<WebCore::TextCheckingType>"_s,
                "checkingTypes()"_s
            },
            {
                "WebCore::TextCheckingProcessType"_s,
                "processType()"_s
            },
        } },
        { "WebCore::LayoutRect"_s, {
            {
                "WebCore::LayoutPoint"_s,
                "m_location"_s
            },
            {
                "WebCore::LayoutSize"_s,
                "m_size"_s
            },
        } },
        { "WebCore::ScreenDataOverrides"_s, {
            {
                "double"_s,
                "width"_s
            },
            {
                "double"_s,
                "height"_s
            },
            {
                "double"_s,
                "scale"_s
            },
        } },
        { "WebCore::MediaCapabilitiesInfo"_s, {
            {
                "bool"_s,
                "supported"_s
            },
            {
                "bool"_s,
                "smooth"_s
            },
            {
                "bool"_s,
                "powerEfficient"_s
            },
        } },
        { "WebCore::MediaStreamRequest"_s, {
            {
                "WebCore::MediaStreamRequest::Type"_s,
                "type"_s
            },
            {
                "WebCore::MediaConstraints"_s,
                "audioConstraints"_s
            },
            {
                "WebCore::MediaConstraints"_s,
                "videoConstraints"_s
            },
            {
                "bool"_s,
                "isUserGesturePriviledged"_s
            },
            {
                "WebCore::PageIdentifier"_s,
                "pageIdentifier"_s
            },
        } },
        { "WebCore::MediaTrackConstraintSetMap"_s, {
            {
                "std::optional<WebCore::IntConstraint>"_s,
                "m_width"_s
            },
            {
                "std::optional<WebCore::IntConstraint>"_s,
                "m_height"_s
            },
            {
                "std::optional<WebCore::IntConstraint>"_s,
                "m_sampleRate"_s
            },
            {
                "std::optional<WebCore::IntConstraint>"_s,
                "m_sampleSize"_s
            },
            {
                "std::optional<WebCore::DoubleConstraint>"_s,
                "m_aspectRatio"_s
            },
            {
                "std::optional<WebCore::DoubleConstraint>"_s,
                "m_zoom"_s
            },
            {
                "std::optional<WebCore::DoubleConstraint>"_s,
                "m_frameRate"_s
            },
            {
                "std::optional<WebCore::DoubleConstraint>"_s,
                "m_volume"_s
            },
            {
                "std::optional<WebCore::BooleanConstraint>"_s,
                "m_echoCancellation"_s
            },
            {
                "std::optional<WebCore::BooleanConstraint>"_s,
                "m_displaySurface"_s
            },
            {
                "std::optional<WebCore::BooleanConstraint>"_s,
                "m_logicalSurface"_s
            },
            {
                "std::optional<WebCore::StringConstraint>"_s,
                "m_facingMode"_s
            },
            {
                "std::optional<WebCore::StringConstraint>"_s,
                "m_deviceId"_s
            },
            {
                "std::optional<WebCore::StringConstraint>"_s,
                "m_groupId"_s
            },
        } },
        { "WebCore::MediaStreamRequest"_s, {
            {
                "WebCore::MediaStreamRequest::Type"_s,
                "type"_s
            },
        } },
        { "WebCore::MediaCapabilitiesDecodingInfo"_s, {
            {
                "WebCore::MediaDecodingConfiguration"_s,
                "supportedConfiguration"_s
            },
        } },
        { "WebCore::MediaCapabilitiesEncodingInfo"_s, {
            {
                "WebCore::MediaEncodingConfiguration"_s,
                "supportedConfiguration"_s
            },
        } },
        { "WebCore::FormDataElement"_s, {
            {
                "std::variant<Vector<uint8_t>, WebCore::FormDataElement::EncodedFileData, WebCore::FormDataElement::EncodedBlobData>"_s,
                "data"_s
            },
        } },
        { "WebCore::FormDataElement::EncodedFileData"_s, {
            {
                "String"_s,
                "filename"_s
            },
            {
                "int64_t"_s,
                "fileStart"_s
            },
            {
                "int64_t"_s,
                "fileLength"_s
            },
            {
                "std::optional<WallTime>"_s,
                "expectedFileModificationTime"_s
            },
        } },
        { "WebCore::FormDataElement::EncodedBlobData"_s, {
            {
                "URL"_s,
                "url"_s
            },
        } },
        { "WebCore::NetworkTransactionInformation"_s, {
            {
                "WebCore::NetworkTransactionInformation::Type"_s,
                "type"_s
            },
            {
                "WebCore::ResourceRequest"_s,
                "request"_s
            },
            {
                "WebCore::ResourceResponse"_s,
                "response"_s
            },
            {
                "WebCore::NetworkLoadMetrics"_s,
                "metrics"_s
            },
        } },
        { "WebCore::ContentType"_s, {
            {
                "String"_s,
                "raw()"_s
            },
        } },
        { "WebCore::DateTimeChooserParameters"_s, {
            {
                "AtomString"_s,
                "type"_s
            },
            {
                "WebCore::IntRect"_s,
                "anchorRectInRootView"_s
            },
            {
                "AtomString"_s,
                "locale"_s
            },
            {
                "String"_s,
                "currentValue"_s
            },
            {
                "Vector<String>"_s,
                "suggestionValues"_s
            },
            {
                "Vector<String>"_s,
                "localizedSuggestionValues"_s
            },
            {
                "Vector<String>"_s,
                "suggestionLabels"_s
            },
            {
                "double"_s,
                "minimum"_s
            },
            {
                "double"_s,
                "maximum"_s
            },
            {
                "double"_s,
                "step"_s
            },
            {
                "double"_s,
                "stepBase"_s
            },
            {
                "bool"_s,
                "required"_s
            },
            {
                "bool"_s,
                "isAnchorElementRTL"_s
            },
            {
                "bool"_s,
                "useDarkAppearance"_s
            },
            {
                "bool"_s,
                "hasSecondField"_s
            },
            {
                "bool"_s,
                "hasMillisecondField"_s
            },
        } },
        { "WebCore::ScreenData"_s, {
            {
                "WebCore::FloatRect"_s,
                "screenAvailableRect"_s
            },
            {
                "WebCore::FloatRect"_s,
                "screenRect"_s
            },
            {
                "WebCore::DestinationColorSpace"_s,
                "colorSpace"_s
            },
            {
                "int"_s,
                "screenDepth"_s
            },
            {
                "int"_s,
                "screenDepthPerComponent"_s
            },
            {
                "bool"_s,
                "screenSupportsExtendedColor"_s
            },
            {
                "bool"_s,
                "screenHasInvertedColors"_s
            },
            {
                "bool"_s,
                "screenSupportsHighDynamicRange"_s
            },
#if PLATFORM(MAC)
            {
                "bool"_s,
                "screenIsMonochrome"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "uint32_t"_s,
                "displayMask"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "WebCore::PlatformGPUID"_s,
                "gpuID"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "WebCore::DynamicRangeMode"_s,
                "preferredDynamicRangeMode"_s
            },
#endif
#if PLATFORM(MAC) || PLATFORM(IOS_FAMILY)
            {
                "float"_s,
                "scaleFactor"_s
            },
#endif
        } },
        { "WebCore::ScreenProperties"_s, {
            {
                "WebCore::PlatformDisplayID"_s,
                "primaryDisplayID"_s
            },
            {
                "HashMap<WebCore::PlatformDisplayID, WebCore::ScreenData>"_s,
                "screenDataMap"_s
            },
        } },
        { "WebCore::PlatformTimeRanges"_s, {
            {
                "Vector<WebCore::PlatformTimeRanges::Range>"_s,
                "m_ranges"_s
            },
        } },
        { "WebCore::PlatformTimeRanges::Range"_s, {
            {
                "MediaTime"_s,
                "start"_s
            },
            {
                "MediaTime"_s,
                "end"_s
            },
        } },
        { "WebCore::VideoPlaybackQualityMetrics"_s, {
            {
                "uint32_t"_s,
                "totalVideoFrames"_s
            },
            {
                "uint32_t"_s,
                "droppedVideoFrames"_s
            },
            {
                "uint32_t"_s,
                "corruptedVideoFrames"_s
            },
            {
                "double"_s,
                "totalFrameDelay"_s
            },
            {
                "uint32_t"_s,
                "displayCompositedVideoFrames"_s
            },
        } },
        { "WebCore::SelectionGeometry"_s, {
            {
                "WebCore::FloatQuad"_s,
                "quad()"_s
            },
            {
                "WebCore::SelectionRenderingBehavior"_s,
                "behavior()"_s
            },
            {
                "WebCore::TextDirection"_s,
                "direction()"_s
            },
            {
                "int"_s,
                "minX()"_s
            },
            {
                "int"_s,
                "maxX()"_s
            },
            {
                "int"_s,
                "maxY()"_s
            },
            {
                "int"_s,
                "lineNumber()"_s
            },
            {
                "bool"_s,
                "isLineBreak()"_s
            },
            {
                "bool"_s,
                "isFirstOnLine()"_s
            },
            {
                "bool"_s,
                "isLastOnLine()"_s
            },
            {
                "bool"_s,
                "containsStart()"_s
            },
            {
                "bool"_s,
                "containsEnd()"_s
            },
            {
                "bool"_s,
                "isHorizontal()"_s
            },
        } },
        { "WebCore::DataListSuggestion"_s, {
            {
                "String"_s,
                "value"_s
            },
            {
                "String"_s,
                "label"_s
            },
        } },
        { "WebCore::DataListSuggestionInformation"_s, {
            {
                "WebCore::DataListSuggestionActivationType"_s,
                "activationType"_s
            },
            {
                "Vector<WebCore::DataListSuggestion>"_s,
                "suggestions"_s
            },
            {
                "WebCore::IntRect"_s,
                "elementRect"_s
            },
        } },
        { "WebCore::ClientOrigin"_s, {
            {
                "WebCore::SecurityOriginData"_s,
                "topOrigin"_s
            },
            {
                "WebCore::SecurityOriginData"_s,
                "clientOrigin"_s
            },
        } },
        { "WebCore::PixelBufferFormat"_s, {
            {
                "WebCore::AlphaPremultiplication"_s,
                "alphaFormat"_s
            },
            {
                "WebCore::PixelFormat"_s,
                "pixelFormat"_s
            },
            {
                "WebCore::DestinationColorSpace"_s,
                "colorSpace"_s
            },
        } },
        { "WebCore::TextIndicator"_s, {
            {
                "WebCore::TextIndicatorData"_s,
                "data()"_s
            },
        } },
        { "WebCore::CertificateInfo"_s, {
#if PLATFORM(COCOA)
            {
                "RetainPtr<SecTrustRef>"_s,
                "trust()"_s
            },
#endif
#if USE(CURL)
            {
                "int"_s,
                "verificationError()"_s
            },
#endif
#if USE(CURL)
            {
                "Vector<Vector<uint8_t>>"_s,
                "certificateChain()"_s
            },
#endif
#if USE(SOUP)
            {
                "GRefPtr<GTlsCertificate>"_s,
                "certificate()"_s
            },
#endif
#if USE(SOUP)
            {
                "GTlsCertificateFlags"_s,
                "tlsErrors()"_s
            },
#endif
        } },
        { "WebCore::PasteboardCustomData::Entry"_s, {
            {
                "String"_s,
                "type"_s
            },
            {
                "String"_s,
                "customData"_s
            },
            {
                "std::variant<String, Ref<WebCore::SharedBuffer>>"_s,
                "platformData"_s
            },
        } },
        { "WebCore::PasteboardCustomData"_s, {
            {
                "String"_s,
                "origin()"_s
            },
            {
                "Vector<WebCore::PasteboardCustomData::Entry>"_s,
                "data()"_s
            },
        } },
        { "WebCore::DatabaseDetails"_s, {
            {
                "String"_s,
                "name()"_s
            },
            {
                "String"_s,
                "displayName()"_s
            },
            {
                "uint64_t"_s,
                "expectedUsage()"_s
            },
            {
                "uint64_t"_s,
                "currentUsage()"_s
            },
            {
                "std::optional<WallTime>"_s,
                "creationTime()"_s
            },
            {
                "std::optional<WallTime>"_s,
                "modificationTime()"_s
            },
        } },
        { "WebCore::DecomposedGlyphs"_s, {
            {
                "WebCore::PositionedGlyphs"_s,
                "positionedGlyphs()"_s
            },
            {
                "WebCore::RenderingResourceIdentifier"_s,
                "renderingResourceIdentifier()"_s
            },
        } },
        { "WebCore::TextIndicatorData"_s, {
            {
                "WebCore::FloatRect"_s,
                "selectionRectInRootViewCoordinates"_s
            },
            {
                "WebCore::FloatRect"_s,
                "textBoundingRectInRootViewCoordinates"_s
            },
            {
                "WebCore::FloatRect"_s,
                "contentImageWithoutSelectionRectInRootViewCoordinates"_s
            },
            {
                "Vector<WebCore::FloatRect>"_s,
                "textRectsInBoundingRectCoordinates"_s
            },
            {
                "float"_s,
                "contentImageScaleFactor"_s
            },
            {
                "RefPtr<WebCore::Image>"_s,
                "contentImageWithHighlight"_s
            },
            {
                "RefPtr<WebCore::Image>"_s,
                "contentImageWithoutSelection"_s
            },
            {
                "RefPtr<WebCore::Image>"_s,
                "contentImage"_s
            },
            {
                "WebCore::Color"_s,
                "estimatedBackgroundColor"_s
            },
            {
                "WebCore::TextIndicatorPresentationTransition"_s,
                "presentationTransition"_s
            },
            {
                "OptionSet<WebCore::TextIndicatorOption>"_s,
                "options"_s
            },
        } },
        { "WebCore::MediaConstraints"_s, {
            {
                "WebCore::MediaTrackConstraintSetMap"_s,
                "mandatoryConstraints"_s
            },
            {
                "Vector<WebCore::MediaTrackConstraintSetMap>"_s,
                "advancedConstraints"_s
            },
            {
                "bool"_s,
                "isValid"_s
            },
        } },
        { "WebCore::PromisedAttachmentInfo"_s, {
#if ENABLE(ATTACHMENT_ELEMENT)
            {
                "String"_s,
                "attachmentIdentifier"_s
            },
#endif
            {
                "Vector<String>"_s,
                "additionalTypes"_s
            },
            {
                "Vector<RefPtr<WebCore::SharedBuffer>>"_s,
                "additionalData"_s
            },
        } },
        { "WebCore::RecentSearch"_s, {
            {
                "String"_s,
                "string"_s
            },
            {
                "WallTime"_s,
                "time"_s
            },
        } },
        { "WebCore::EventTrackingRegions"_s, {
            {
                "WebCore::Region"_s,
                "asynchronousDispatchRegion"_s
            },
            {
                "HashMap<WebCore::EventTrackingRegions::EventType, WebCore::Region, WTF::IntHash<WebCore::EventTrackingRegions::EventType>, WTF::StrongEnumHashTraits<WebCore::EventTrackingRegions::EventType>>"_s,
                "eventSpecificSynchronousDispatchRegions"_s
            },
        } },
        { "WebCore::TextManipulationItem"_s, {
            {
                "WebCore::FrameIdentifier"_s,
                "frameID"_s
            },
            {
                "bool"_s,
                "isSubframe"_s
            },
            {
                "bool"_s,
                "isCrossSiteSubframe"_s
            },
            {
                "WebCore::TextManipulationItemIdentifier"_s,
                "identifier"_s
            },
            {
                "Vector<WebCore::TextManipulationToken>"_s,
                "tokens"_s
            },
        } },
        { "WebCore::TextManipulationToken"_s, {
            {
                "WebCore::TextManipulationTokenIdentifier"_s,
                "identifier"_s
            },
            {
                "String"_s,
                "content"_s
            },
            {
                "std::optional<WebCore::TextManipulationTokenInfo>"_s,
                "info"_s
            },
            {
                "bool"_s,
                "isExcluded"_s
            },
        } },
        { "WebCore::TextManipulationTokenInfo"_s, {
            {
                "String"_s,
                "tagName"_s
            },
            {
                "String"_s,
                "roleAttribute"_s
            },
            {
                "URL"_s,
                "documentURL"_s
            },
            {
                "bool"_s,
                "isVisible"_s
            },
        } },
        { "WebCore::VelocityData"_s, {
            {
                "float"_s,
                "horizontalVelocity"_s
            },
            {
                "float"_s,
                "verticalVelocity"_s
            },
            {
                "float"_s,
                "scaleChangeRate"_s
            },
            {
                "MonotonicTime"_s,
                "lastUpdateTime"_s
            },
        } },
        { "WebCore::MimeClassInfo"_s, {
            {
                "AtomString"_s,
                "type"_s
            },
            {
                "String"_s,
                "desc"_s
            },
            {
                "Vector<String>"_s,
                "extensions"_s
            },
        } },
        { "WebCore::AuthenticationChallenge"_s, {
            {
                "WebCore::ProtectionSpace"_s,
                "protectionSpace()"_s
            },
            {
                "WebCore::Credential"_s,
                "proposedCredential()"_s
            },
            {
                "unsigned"_s,
                "previousFailureCount()"_s
            },
            {
                "WebCore::ResourceResponse"_s,
                "failureResponse()"_s
            },
            {
                "WebCore::ResourceError"_s,
                "error()"_s
            },
#if USE(SOUP)
            {
                "uint32_t"_s,
                "tlsPasswordFlags()"_s
            },
#endif
        } },
        { "WebCore::DragData"_s, {
#if PLATFORM(COCOA)
            {
                "String"_s,
                "pasteboardName()"_s
            },
#endif
            {
                "WebCore::IntPoint"_s,
                "clientPosition()"_s
            },
            {
                "WebCore::IntPoint"_s,
                "globalPosition()"_s
            },
#if PLATFORM(COCOA)
            {
                "Vector<String>"_s,
                "fileNames()"_s
            },
#endif
            {
                "OptionSet<WebCore::DragOperation>"_s,
                "draggingSourceOperationMask()"_s
            },
            {
                "OptionSet<WebCore::DragApplicationFlags>"_s,
                "flags()"_s
            },
            {
                "OptionSet<WebCore::DragDestinationAction>"_s,
                "dragDestinationActionMask()"_s
            },
            {
                "std::optional<WebCore::PageIdentifier>"_s,
                "pageID()"_s
            },
        } },
        { "WebCore::DictationAlternative"_s, {
            {
                "WebCore::CharacterRange"_s,
                "range"_s
            },
            {
                "WebCore::DictationContext"_s,
                "context"_s
            },
        } },
        { "WebCore::UserStyleSheet"_s, {
            {
                "String"_s,
                "source()"_s
            },
            {
                "URL"_s,
                "url()"_s
            },
            {
                "Vector<String>"_s,
                "allowlist()"_s
            },
            {
                "Vector<String>"_s,
                "blocklist()"_s
            },
            {
                "WebCore::UserContentInjectedFrames"_s,
                "injectedFrames()"_s
            },
            {
                "WebCore::UserStyleLevel"_s,
                "level()"_s
            },
            {
                "std::optional<WebCore::PageIdentifier>"_s,
                "pageID()"_s
            },
        } },
        { "WebCore::ScrollableAreaParameters"_s, {
            {
                "WebCore::ScrollElasticity"_s,
                "horizontalScrollElasticity"_s
            },
            {
                "WebCore::ScrollElasticity"_s,
                "verticalScrollElasticity"_s
            },
            {
                "WebCore::ScrollbarMode"_s,
                "horizontalScrollbarMode"_s
            },
            {
                "WebCore::ScrollbarMode"_s,
                "verticalScrollbarMode"_s
            },
            {
                "WebCore::OverscrollBehavior"_s,
                "horizontalOverscrollBehavior"_s
            },
            {
                "WebCore::OverscrollBehavior"_s,
                "verticalOverscrollBehavior"_s
            },
            {
                "bool"_s,
                "allowsHorizontalScrolling"_s
            },
            {
                "bool"_s,
                "allowsVerticalScrolling"_s
            },
            {
                "WebCore::NativeScrollbarVisibility"_s,
                "horizontalNativeScrollbarVisibility"_s
            },
            {
                "WebCore::NativeScrollbarVisibility"_s,
                "verticalNativeScrollbarVisibility"_s
            },
            {
                "bool"_s,
                "useDarkAppearanceForScrollbars"_s
            },
            {
                "WebCore::ScrollbarWidth"_s,
                "scrollbarWidthStyle"_s
            },
        } },
        { "WebCore::RequestedKeyboardScrollData"_s, {
            {
                "WebCore::KeyboardScrollAction"_s,
                "action"_s
            },
            {
                "std::optional<WebCore::KeyboardScroll>"_s,
                "keyboardScroll"_s
            },
        } },
        { "WebCore::AbsolutePositionConstraints"_s, {
            {
                "WebCore::FloatSize"_s,
                "alignmentOffset()"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "layerPositionAtLastLayout()"_s
            },
        } },
        { "WebCore::KeyboardScroll"_s, {
            {
                "WebCore::FloatSize"_s,
                "offset"_s
            },
            {
                "WebCore::FloatSize"_s,
                "maximumVelocity"_s
            },
            {
                "WebCore::FloatSize"_s,
                "force"_s
            },
            {
                "WebCore::ScrollGranularity"_s,
                "granularity"_s
            },
            {
                "WebCore::ScrollDirection"_s,
                "direction"_s
            },
        } },
        { "WebCore::NotificationResources"_s, {
            {
                "RefPtr<WebCore::Image>"_s,
                "icon()"_s
            },
        } },
        { "WebCore::IdentityTransformOperation"_s, {
        } },
        { "WebCore::TranslateTransformOperation"_s, {
            {
                "WebCore::Length"_s,
                "x()"_s
            },
            {
                "WebCore::Length"_s,
                "y()"_s
            },
            {
                "WebCore::Length"_s,
                "z()"_s
            },
            {
                "WebCore::TransformOperation::Type"_s,
                "type()"_s
            },
        } },
        { "WebCore::RotateTransformOperation"_s, {
            {
                "double"_s,
                "x()"_s
            },
            {
                "double"_s,
                "y()"_s
            },
            {
                "double"_s,
                "z()"_s
            },
            {
                "double"_s,
                "angle()"_s
            },
            {
                "WebCore::TransformOperation::Type"_s,
                "type()"_s
            },
        } },
        { "WebCore::ScaleTransformOperation"_s, {
            {
                "double"_s,
                "x()"_s
            },
            {
                "double"_s,
                "y()"_s
            },
            {
                "double"_s,
                "z()"_s
            },
            {
                "WebCore::TransformOperation::Type"_s,
                "type()"_s
            },
        } },
        { "WebCore::SkewTransformOperation"_s, {
            {
                "double"_s,
                "angleX()"_s
            },
            {
                "double"_s,
                "angleY()"_s
            },
            {
                "WebCore::TransformOperation::Type"_s,
                "type()"_s
            },
        } },
        { "WebCore::PerspectiveTransformOperation"_s, {
            {
                "std::optional<WebCore::Length>"_s,
                "perspective()"_s
            },
        } },
        { "WebCore::MatrixTransformOperation"_s, {
            {
                "WebCore::TransformationMatrix"_s,
                "matrix()"_s
            },
        } },
        { "WebCore::Matrix3DTransformOperation"_s, {
            {
                "WebCore::TransformationMatrix"_s,
                "matrix()"_s
            },
        } },
        { "WebCore::TransformOperations"_s, {
            {
                "Vector<RefPtr<WebCore::TransformOperation>>"_s,
                "operations()"_s
            },
        } },
        { "WebCore::Gradient::LinearData"_s, {
            {
                "WebCore::FloatPoint"_s,
                "point0"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "point1"_s
            },
        } },
        { "WebCore::Gradient::RadialData"_s, {
            {
                "WebCore::FloatPoint"_s,
                "point0"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "point1"_s
            },
            {
                "float"_s,
                "startRadius"_s
            },
            {
                "float"_s,
                "endRadius"_s
            },
            {
                "float"_s,
                "aspectRatio"_s
            },
        } },
        { "WebCore::Gradient::ConicData"_s, {
            {
                "WebCore::FloatPoint"_s,
                "point0"_s
            },
            {
                "float"_s,
                "angleRadians"_s
            },
        } },
        { "WebCore::Gradient"_s, {
            {
                "std::variant<WebCore::Gradient::LinearData, WebCore::Gradient::RadialData, WebCore::Gradient::ConicData>"_s,
                "data()"_s
            },
            {
                "WebCore::ColorInterpolationMethod"_s,
                "colorInterpolationMethod()"_s
            },
            {
                "WebCore::GradientSpreadMethod"_s,
                "spreadMethod()"_s
            },
            {
                "WebCore::GradientColorStops"_s,
                "stops()"_s
            },
        } },
        { "WebCore::Pattern::Parameters"_s, {
            {
                "bool"_s,
                "repeatX"_s
            },
            {
                "bool"_s,
                "repeatY"_s
            },
            {
                "WebCore::AffineTransform"_s,
                "patternSpaceTransform"_s
            },
        } },
        { "WebCore::Pattern"_s, {
            {
                "WebCore::SourceImage"_s,
                "tileImage()"_s
            },
            {
                "WebCore::Pattern::Parameters"_s,
                "parameters()"_s
            },
        } },
        { "WebCore::SourceBrush::Brush"_s, {
            {
                "std::variant<WebCore::SourceBrush::Brush::LogicalGradient, Ref<WebCore::Pattern>>"_s,
                "brush"_s
            },
        } },
        { "WebCore::SourceBrush"_s, {
            {
                "WebCore::Color"_s,
                "color()"_s
            },
            {
                "std::optional<WebCore::SourceBrush::Brush>"_s,
                "brush()"_s
            },
        } },
        { "WebCore::GraphicsContextGLAttributes"_s, {
            {
                "bool"_s,
                "alpha"_s
            },
            {
                "bool"_s,
                "depth"_s
            },
            {
                "bool"_s,
                "stencil"_s
            },
            {
                "bool"_s,
                "antialias"_s
            },
            {
                "bool"_s,
                "premultipliedAlpha"_s
            },
            {
                "bool"_s,
                "preserveDrawingBuffer"_s
            },
            {
                "bool"_s,
                "failIfMajorPerformanceCaveat"_s
            },
            {
                "WebCore::GraphicsContextGLPowerPreference"_s,
                "powerPreference"_s
            },
            {
                "bool"_s,
                "shareResources"_s
            },
            {
                "bool"_s,
                "noExtensions"_s
            },
            {
                "float"_s,
                "devicePixelRatio"_s
            },
            {
                "WebCore::GraphicsContextGLPowerPreference"_s,
                "initialPowerPreference"_s
            },
            {
                "WebCore::GraphicsContextGLWebGLVersion"_s,
                "webGLVersion"_s
            },
            {
                "bool"_s,
                "forceRequestForHighPerformanceGPU"_s
            },
#if PLATFORM(MAC) || PLATFORM(MACCATALYST)
            {
                "uint64_t"_s,
                "windowGPUID"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "useMetal"_s
            },
#endif
#if ENABLE(WEBXR)
            {
                "bool"_s,
                "xrCompatible"_s
            },
#endif
            {
                "bool"_s,
                "failPlatformContextCreationForTesting"_s
            },
        } },
        { "WebCore::TimingFunction"_s, {
            { "std::variant<WebCore::LinearTimingFunction, WebCore::CubicBezierTimingFunction, WebCore::StepsTimingFunction, WebCore::SpringTimingFunction>"_s, "subclasses"_s }
        } },
        { "WebCore::TransformOperation"_s, {
            { "std::variant<WebCore::TranslateTransformOperation, WebCore::ScaleTransformOperation, WebCore::RotateTransformOperation, WebCore::SkewTransformOperation, WebCore::MatrixTransformOperation, WebCore::Matrix3DTransformOperation, WebCore::PerspectiveTransformOperation, WebCore::IdentityTransformOperation>"_s, "subclasses"_s }
        } },
        { "WebCore::LengthSize"_s, {
            {
                "WebCore::Length"_s,
                "width"_s
            },
            {
                "WebCore::Length"_s,
                "height"_s
            },
        } },
        { "WebCore::SVGPathByteStream"_s, {
            {
                "Vector<unsigned char>"_s,
                "data()"_s
            },
        } },
        { "WebCore::BasicShapeCenterCoordinate"_s, {
            {
                "WebCore::BasicShapeCenterCoordinate::Direction"_s,
                "direction()"_s
            },
            {
                "WebCore::Length"_s,
                "length()"_s
            },
        } },
        { "WebCore::BasicShapeRadius"_s, {
            {
                "WebCore::Length"_s,
                "value()"_s
            },
            {
                "WebCore::BasicShapeRadius::Type"_s,
                "type()"_s
            },
        } },
        { "WebCore::BasicShapeCircle"_s, {
            {
                "WebCore::BasicShapeCenterCoordinate"_s,
                "centerX()"_s
            },
            {
                "WebCore::BasicShapeCenterCoordinate"_s,
                "centerY()"_s
            },
            {
                "WebCore::BasicShapeRadius"_s,
                "radius()"_s
            },
        } },
        { "WebCore::BasicShapeEllipse"_s, {
            {
                "WebCore::BasicShapeCenterCoordinate"_s,
                "centerX()"_s
            },
            {
                "WebCore::BasicShapeCenterCoordinate"_s,
                "centerY()"_s
            },
            {
                "WebCore::BasicShapeRadius"_s,
                "radiusX()"_s
            },
            {
                "WebCore::BasicShapeRadius"_s,
                "radiusY()"_s
            },
        } },
        { "WebCore::BasicShapePolygon"_s, {
            {
                "WebCore::WindRule"_s,
                "windRule()"_s
            },
            {
                "Vector<WebCore::Length>"_s,
                "values()"_s
            },
        } },
        { "WebCore::BasicShapePath"_s, {
            {
                "std::unique_ptr<WebCore::SVGPathByteStream>"_s,
                "byteStream()"_s
            },
            {
                "float"_s,
                "zoom()"_s
            },
            {
                "WebCore::WindRule"_s,
                "windRule()"_s
            },
        } },
        { "WebCore::BasicShapeInset"_s, {
            {
                "WebCore::Length"_s,
                "right()"_s
            },
            {
                "WebCore::Length"_s,
                "top()"_s
            },
            {
                "WebCore::Length"_s,
                "bottom()"_s
            },
            {
                "WebCore::Length"_s,
                "left()"_s
            },
            {
                "WebCore::LengthSize"_s,
                "topLeftRadius()"_s
            },
            {
                "WebCore::LengthSize"_s,
                "topRightRadius()"_s
            },
            {
                "WebCore::LengthSize"_s,
                "bottomRightRadius()"_s
            },
            {
                "WebCore::LengthSize"_s,
                "bottomLeftRadius()"_s
            },
        } },
        { "WebCore::BasicShape"_s, {
            { "std::variant<WebCore::BasicShapeCircle, WebCore::BasicShapeEllipse, WebCore::BasicShapePolygon, WebCore::BasicShapePath, WebCore::BasicShapeInset>"_s, "subclasses"_s }
        } },
        { "WebCore::ReferencePathOperation"_s, {
            {
                "std::optional<WebCore::Path>"_s,
                "path()"_s
            },
        } },
        { "WebCore::ShapePathOperation"_s, {
            {
                "Ref<WebCore::BasicShape>"_s,
                "shape()"_s
            },
            {
                "WebCore::CSSBoxType"_s,
                "referenceBox()"_s
            },
        } },
        { "WebCore::BoxPathOperation"_s, {
            {
                "WebCore::Path"_s,
                "path()"_s
            },
            {
                "WebCore::CSSBoxType"_s,
                "referenceBox()"_s
            },
        } },
        { "WebCore::RayPathOperation"_s, {
            {
                "float"_s,
                "angle()"_s
            },
            {
                "WebCore::RayPathOperation::Size"_s,
                "size()"_s
            },
            {
                "bool"_s,
                "isContaining()"_s
            },
            {
                "WebCore::FloatRect"_s,
                "containingBlockBoundingRect()"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "position()"_s
            },
        } },
        { "WebCore::PathOperation"_s, {
            { "std::variant<WebCore::ReferencePathOperation, WebCore::ShapePathOperation, WebCore::BoxPathOperation, WebCore::RayPathOperation>"_s, "subclasses"_s }
        } },
        { "WebCore::CDMKeySystemConfiguration"_s, {
            {
                "String"_s,
                "label"_s
            },
            {
                "Vector<AtomString>"_s,
                "initDataTypes"_s
            },
            {
                "Vector<WebCore::CDMMediaCapability>"_s,
                "audioCapabilities"_s
            },
            {
                "Vector<WebCore::CDMMediaCapability>"_s,
                "videoCapabilities"_s
            },
            {
                "WebCore::CDMRequirement"_s,
                "distinctiveIdentifier"_s
            },
            {
                "WebCore::CDMRequirement"_s,
                "persistentState"_s
            },
            {
                "Vector<WebCore::CDMSessionType>"_s,
                "sessionTypes"_s
            },
        } },
        { "WebCore::MediaConfiguration"_s, {
            {
                "std::optional<WebCore::VideoConfiguration>"_s,
                "video"_s
            },
            {
                "std::optional<WebCore::AudioConfiguration>"_s,
                "audio"_s
            },
            {
                "std::optional<Vector<String>>"_s,
                "allowedMediaContainerTypes"_s
            },
            {
                "std::optional<Vector<String>>"_s,
                "allowedMediaCodecTypes"_s
            },
        } },
        { "WebCore::MediaEncodingConfiguration"_s, {
            {
                "WebCore::MediaEncodingType"_s,
                "type"_s
            },
        } },
        { "WebCore::MediaDecodingConfiguration"_s, {
            {
                "WebCore::MediaDecodingType"_s,
                "type"_s
            },
            {
                "bool"_s,
                "canExposeVP9"_s
            },
        } },
        { "WebCore::ResourceResponseBase::ResponseData"_s, {
            {
                "URL"_s,
                "m_url"_s
            },
            {
                "AtomString"_s,
                "m_mimeType"_s
            },
            {
                "long long"_s,
                "m_expectedContentLength"_s
            },
            {
                "AtomString"_s,
                "m_textEncodingName"_s
            },
            {
                "AtomString"_s,
                "m_httpStatusText"_s
            },
            {
                "AtomString"_s,
                "m_httpVersion"_s
            },
            {
                "WebCore::HTTPHeaderMap"_s,
                "m_httpHeaderFields"_s
            },
            {
                "Box<WebCore::NetworkLoadMetrics>"_s,
                "m_networkLoadMetrics"_s
            },
            {
                "short"_s,
                "m_httpStatusCode"_s
            },
            {
                "std::optional<WebCore::CertificateInfo>"_s,
                "m_certificateInfo"_s
            },
            {
                "WebCore::ResourceResponseBase::Source"_s,
                "m_source"_s
            },
            {
                "WebCore::ResourceResponseBase::Type"_s,
                "m_type"_s
            },
            {
                "WebCore::ResourceResponseBase::Tainting"_s,
                "m_tainting"_s
            },
            {
                "bool"_s,
                "m_isRedirected"_s
            },
            {
                "WebCore::UsedLegacyTLS"_s,
                "m_usedLegacyTLS"_s
            },
            {
                "WebCore::WasPrivateRelayed"_s,
                "m_wasPrivateRelayed"_s
            },
            {
                "bool"_s,
                "m_isRangeRequested"_s
            },
        } },
        { "WebCore::ResourceResponseBase"_s, {
            {
                "std::optional<WebCore::ResourceResponseBase::ResponseData>"_s,
                "getResponseData()"_s
            },
        } },
        { "WebCore::ResourceResponse"_s, {
        } },
        { "WebCore::ResourceResponseBase::CrossThreadData"_s, {
            {
                "URL"_s,
                "url"_s
            },
            {
                "String"_s,
                "mimeType"_s
            },
            {
                "long long"_s,
                "expectedContentLength"_s
            },
            {
                "String"_s,
                "textEncodingName"_s
            },
            {
                "short"_s,
                "httpStatusCode"_s
            },
            {
                "String"_s,
                "httpStatusText"_s
            },
            {
                "String"_s,
                "httpVersion"_s
            },
            {
                "WebCore::HTTPHeaderMap"_s,
                "httpHeaderFields"_s
            },
            {
                "std::optional<WebCore::NetworkLoadMetrics>"_s,
                "networkLoadMetrics"_s
            },
            {
                "WebCore::ResourceResponseBase::Source"_s,
                "source"_s
            },
            {
                "WebCore::ResourceResponseBase::Type"_s,
                "type"_s
            },
            {
                "WebCore::ResourceResponseBase::Tainting"_s,
                "tainting"_s
            },
            {
                "bool"_s,
                "isRedirected"_s
            },
            {
                "WebCore::UsedLegacyTLS"_s,
                "usedLegacyTLS"_s
            },
            {
                "WebCore::WasPrivateRelayed"_s,
                "wasPrivateRelayed"_s
            },
            {
                "bool"_s,
                "isRangeRequested"_s
            },
            {
                "std::optional<WebCore::CertificateInfo>"_s,
                "certificateInfo"_s
            },
        } },
        { "WebCore::FetchOptions"_s, {
            {
                "WebCore::FetchOptionsDestination"_s,
                "destination"_s
            },
            {
                "WebCore::FetchOptionsMode"_s,
                "mode"_s
            },
            {
                "WebCore::FetchOptionsCredentials"_s,
                "credentials"_s
            },
            {
                "WebCore::FetchOptionsCache"_s,
                "cache"_s
            },
            {
                "WebCore::FetchOptionsRedirect"_s,
                "redirect"_s
            },
            {
                "WebCore::ReferrerPolicy"_s,
                "referrerPolicy"_s
            },
            {
                "bool"_s,
                "keepAlive"_s
            },
            {
                "String"_s,
                "integrity"_s
            },
            {
                "Markable<WTF::UUID>"_s,
                "clientIdentifier"_s
            },
            {
                "Markable<WTF::UUID>"_s,
                "resultingClientIdentifier"_s
            },
        } },
        { "WebCore::ControlStyle"_s, {
            {
                "OptionSet<WebCore::ControlStyle::State>"_s,
                "states"_s
            },
            {
                "float"_s,
                "fontSize"_s
            },
            {
                "float"_s,
                "zoomFactor"_s
            },
            {
                "WebCore::Color"_s,
                "accentColor"_s
            },
            {
                "WebCore::Color"_s,
                "textColor"_s
            },
            {
                "WebCore::FloatBoxExtent"_s,
                "borderWidth"_s
            },
        } },
        { "WebCore::ApplePayButtonPart"_s, {
            {
                "WebCore::ApplePayButtonType"_s,
                "buttonType()"_s
            },
            {
                "WebCore::ApplePayButtonStyle"_s,
                "buttonStyle()"_s
            },
            {
                "String"_s,
                "locale()"_s
            },
        } },
        { "WebCore::MeterPart"_s, {
            {
                "WebCore::MeterPart::GaugeRegion"_s,
                "gaugeRegion()"_s
            },
            {
                "double"_s,
                "value()"_s
            },
            {
                "double"_s,
                "minimum()"_s
            },
            {
                "double"_s,
                "maximum()"_s
            },
        } },
        { "WebCore::ProgressBarPart"_s, {
            {
                "double"_s,
                "position()"_s
            },
            {
                "Seconds"_s,
                "animationStartTime()"_s
            },
        } },
        { "WebCore::SliderTrackPart"_s, {
            {
                "WebCore::StyleAppearance"_s,
                "type()"_s
            },
            {
                "WebCore::IntSize"_s,
                "thumbSize()"_s
            },
            {
                "WebCore::IntRect"_s,
                "trackBounds()"_s
            },
            {
                "Vector<double>"_s,
                "tickRatios()"_s
            },
        } },
        { "WebCore::DistantLightSource"_s, {
            {
                "float"_s,
                "azimuth()"_s
            },
            {
                "float"_s,
                "elevation()"_s
            },
        } },
        { "WebCore::PointLightSource"_s, {
            {
                "WebCore::FloatPoint3D"_s,
                "position()"_s
            },
        } },
        { "WebCore::SpotLightSource"_s, {
            {
                "WebCore::FloatPoint3D"_s,
                "position()"_s
            },
            {
                "WebCore::FloatPoint3D"_s,
                "direction()"_s
            },
            {
                "float"_s,
                "specularExponent()"_s
            },
            {
                "float"_s,
                "limitingConeAngle()"_s
            },
        } },
        { "WebCore::FEBlend"_s, {
            {
                "WebCore::BlendMode"_s,
                "blendMode()"_s
            },
        } },
        { "WebCore::FEColorMatrix"_s, {
            {
                "WebCore::ColorMatrixType"_s,
                "type()"_s
            },
            {
                "Vector<float>"_s,
                "values()"_s
            },
        } },
        { "WebCore::ComponentTransferFunction"_s, {
            {
                "WebCore::ComponentTransferType"_s,
                "type"_s
            },
            {
                "float"_s,
                "slope"_s
            },
            {
                "float"_s,
                "intercept"_s
            },
            {
                "float"_s,
                "amplitude"_s
            },
            {
                "float"_s,
                "exponent"_s
            },
            {
                "float"_s,
                "offset"_s
            },
            {
                "Vector<float>"_s,
                "tableValues"_s
            },
        } },
        { "WebCore::FEComponentTransfer"_s, {
            {
                "WebCore::ComponentTransferFunction"_s,
                "redFunction()"_s
            },
            {
                "WebCore::ComponentTransferFunction"_s,
                "greenFunction()"_s
            },
            {
                "WebCore::ComponentTransferFunction"_s,
                "blueFunction()"_s
            },
            {
                "WebCore::ComponentTransferFunction"_s,
                "alphaFunction()"_s
            },
        } },
        { "WebCore::FEComposite"_s, {
            {
                "WebCore::CompositeOperationType"_s,
                "operation()"_s
            },
            {
                "float"_s,
                "k1()"_s
            },
            {
                "float"_s,
                "k2()"_s
            },
            {
                "float"_s,
                "k3()"_s
            },
            {
                "float"_s,
                "k4()"_s
            },
        } },
        { "WebCore::FEConvolveMatrix"_s, {
            {
                "WebCore::IntSize"_s,
                "kernelSize()"_s
            },
            {
                "float"_s,
                "divisor()"_s
            },
            {
                "float"_s,
                "bias()"_s
            },
            {
                "WebCore::IntPoint"_s,
                "targetOffset()"_s
            },
            {
                "WebCore::EdgeModeType"_s,
                "edgeMode()"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "kernelUnitLength()"_s
            },
            {
                "bool"_s,
                "preserveAlpha()"_s
            },
            {
                "Vector<float>"_s,
                "kernel()"_s
            },
        } },
        { "WebCore::FEDiffuseLighting"_s, {
            {
                "WebCore::Color"_s,
                "lightingColor()"_s
            },
            {
                "float"_s,
                "surfaceScale()"_s
            },
            {
                "float"_s,
                "diffuseConstant()"_s
            },
            {
                "float"_s,
                "kernelUnitLengthX()"_s
            },
            {
                "float"_s,
                "kernelUnitLengthY()"_s
            },
            {
                "Ref<WebCore::LightSource>"_s,
                "lightSource()"_s
            },
        } },
        { "WebCore::FEDisplacementMap"_s, {
            {
                "WebCore::ChannelSelectorType"_s,
                "xChannelSelector()"_s
            },
            {
                "WebCore::ChannelSelectorType"_s,
                "yChannelSelector()"_s
            },
            {
                "float"_s,
                "scale()"_s
            },
        } },
        { "WebCore::FEDropShadow"_s, {
            {
                "float"_s,
                "stdDeviationX()"_s
            },
            {
                "float"_s,
                "stdDeviationY()"_s
            },
            {
                "float"_s,
                "dx()"_s
            },
            {
                "float"_s,
                "dy()"_s
            },
            {
                "WebCore::Color"_s,
                "shadowColor()"_s
            },
            {
                "float"_s,
                "shadowOpacity()"_s
            },
        } },
        { "WebCore::FEFlood"_s, {
            {
                "WebCore::Color"_s,
                "floodColor()"_s
            },
            {
                "float"_s,
                "floodOpacity()"_s
            },
        } },
        { "WebCore::FEGaussianBlur"_s, {
            {
                "float"_s,
                "stdDeviationX()"_s
            },
            {
                "float"_s,
                "stdDeviationY()"_s
            },
            {
                "WebCore::EdgeModeType"_s,
                "edgeMode()"_s
            },
        } },
        { "WebCore::FEImage"_s, {
            {
                "WebCore::SourceImage"_s,
                "sourceImage()"_s
            },
            {
                "WebCore::FloatRect"_s,
                "sourceImageRect()"_s
            },
            {
                "WebCore::SVGPreserveAspectRatioValue"_s,
                "preserveAspectRatio()"_s
            },
        } },
        { "WebCore::FEMerge"_s, {
            {
                "unsigned"_s,
                "numberOfEffectInputs()"_s
            },
        } },
        { "WebCore::FEMorphology"_s, {
            {
                "WebCore::MorphologyOperatorType"_s,
                "morphologyOperator()"_s
            },
            {
                "float"_s,
                "radiusX()"_s
            },
            {
                "float"_s,
                "radiusY()"_s
            },
        } },
        { "WebCore::FEOffset"_s, {
            {
                "float"_s,
                "dx()"_s
            },
            {
                "float"_s,
                "dy()"_s
            },
        } },
        { "WebCore::FESpecularLighting"_s, {
            {
                "WebCore::Color"_s,
                "lightingColor()"_s
            },
            {
                "float"_s,
                "surfaceScale()"_s
            },
            {
                "float"_s,
                "specularConstant()"_s
            },
            {
                "float"_s,
                "specularExponent()"_s
            },
            {
                "float"_s,
                "kernelUnitLengthX()"_s
            },
            {
                "float"_s,
                "kernelUnitLengthY()"_s
            },
            {
                "Ref<WebCore::LightSource>"_s,
                "lightSource()"_s
            },
        } },
        { "WebCore::FETurbulence"_s, {
            {
                "WebCore::TurbulenceType"_s,
                "type()"_s
            },
            {
                "float"_s,
                "baseFrequencyX()"_s
            },
            {
                "float"_s,
                "baseFrequencyY()"_s
            },
            {
                "int"_s,
                "numOctaves()"_s
            },
            {
                "float"_s,
                "seed()"_s
            },
            {
                "bool"_s,
                "stitchTiles()"_s
            },
        } },
        { "WebCore::FilterEffectGeometry"_s, {
            {
                "WebCore::FloatRect"_s,
                "m_boundaries"_s
            },
            {
                "OptionSet<WebCore::FilterEffectGeometry::Flags>"_s,
                "m_flags"_s
            },
        } },
        { "WebCore::SVGFilterExpressionTerm"_s, {
            {
                "unsigned"_s,
                "index"_s
            },
            {
                "unsigned"_s,
                "level"_s
            },
            {
                "std::optional<WebCore::FilterEffectGeometry>"_s,
                "geometry"_s
            },
        } },
        { "WebCore::SVGPreserveAspectRatioValue"_s, {
            {
                "WebCore::SVGPreserveAspectRatioValue::SVGPreserveAspectRatioType"_s,
                "m_align"_s
            },
            {
                "WebCore::SVGPreserveAspectRatioValue::SVGMeetOrSliceType"_s,
                "m_meetOrSlice"_s
            },
        } },
        { "WebCore::GamepadEffectParameters"_s, {
            {
                "double"_s,
                "duration"_s
            },
            {
                "double"_s,
                "startDelay"_s
            },
            {
                "double"_s,
                "strongMagnitude"_s
            },
            {
                "double"_s,
                "weakMagnitude"_s
            },
            {
                "double"_s,
                "leftTrigger"_s
            },
            {
                "double"_s,
                "rightTrigger"_s
            },
        } },
        { "WebCore::StorageEstimate"_s, {
            {
                "uint64_t"_s,
                "usage"_s
            },
            {
                "uint64_t"_s,
                "quota"_s
            },
        } },
        { "WebCore::ListStyleType"_s, {
            {
                "WebCore::ListStyleType::Type"_s,
                "type"_s
            },
            {
                "AtomString"_s,
                "identifier"_s
            },
        } },
        { "WebCore::TextList"_s, {
            {
                "WebCore::ListStyleType"_s,
                "styleType"_s
            },
            {
                "int"_s,
                "startingItemNumber"_s
            },
            {
                "bool"_s,
                "ordered"_s
            },
        } },
        { "WebCore::FontAttributes"_s, {
            {
                "RefPtr<WebCore::Font>"_s,
                "font"_s
            },
            {
                "WebCore::Color"_s,
                "backgroundColor"_s
            },
            {
                "WebCore::Color"_s,
                "foregroundColor"_s
            },
            {
                "WebCore::FontShadow"_s,
                "fontShadow"_s
            },
            {
                "WebCore::FontAttributes::SubscriptOrSuperscript"_s,
                "subscriptOrSuperscript"_s
            },
            {
                "WebCore::FontAttributes::HorizontalAlignment"_s,
                "horizontalAlignment"_s
            },
            {
                "Vector<WebCore::TextList>"_s,
                "textLists"_s
            },
            {
                "bool"_s,
                "hasUnderline"_s
            },
            {
                "bool"_s,
                "hasStrikeThrough"_s
            },
            {
                "bool"_s,
                "hasMultipleFonts"_s
            },
        } },
        { "WebCore::CrossOriginEmbedderPolicy"_s, {
            {
                "WebCore::CrossOriginEmbedderPolicyValue"_s,
                "value"_s
            },
            {
                "WebCore::CrossOriginEmbedderPolicyValue"_s,
                "reportOnlyValue"_s
            },
            {
                "String"_s,
                "reportingEndpoint"_s
            },
            {
                "String"_s,
                "reportOnlyReportingEndpoint"_s
            },
        } },
        { "WebCore::SameSiteInfo"_s, {
            {
                "bool"_s,
                "isSameSite"_s
            },
            {
                "bool"_s,
                "isTopSite"_s
            },
            {
                "bool"_s,
                "isSafeHTTPMethod"_s
            },
        } },
        { "WebCore::SecurityOrigin"_s, {
            {
                "WebCore::SecurityOriginData"_s,
                "m_data"_s
            },
            {
                "String"_s,
                "m_domain"_s
            },
            {
                "String"_s,
                "m_filePath"_s
            },
            {
                "bool"_s,
                "m_universalAccess"_s
            },
            {
                "bool"_s,
                "m_domainWasSetInDOM"_s
            },
            {
                "bool"_s,
                "m_canLoadLocalResources"_s
            },
            {
                "bool"_s,
                "m_enforcesFilePathSeparation"_s
            },
            {
                "bool"_s,
                "m_needsStorageAccessFromFileURLsQuirk"_s
            },
            {
                "std::optional<bool>"_s,
                "m_isPotentiallyTrustworthy"_s
            },
            {
                "bool"_s,
                "m_isLocal"_s
            },
        } },
        { "WebCore::CookieRequestHeaderFieldProxy"_s, {
            {
                "URL"_s,
                "firstParty"_s
            },
            {
                "WebCore::SameSiteInfo"_s,
                "sameSiteInfo"_s
            },
            {
                "URL"_s,
                "url"_s
            },
            {
                "std::optional<WebCore::FrameIdentifier>"_s,
                "frameID"_s
            },
            {
                "std::optional<WebCore::PageIdentifier>"_s,
                "pageID"_s
            },
            {
                "WebCore::IncludeSecureCookies"_s,
                "includeSecureCookies"_s
            },
        } },
        { "WebCore::FormData"_s, {
            {
                "Vector<WebCore::FormDataElement>"_s,
                "m_elements"_s
            },
            {
                "int64_t"_s,
                "m_identifier"_s
            },
            {
                "bool"_s,
                "m_alwaysStream"_s
            },
            {
                "Vector<char>"_s,
                "m_boundary"_s
            },
        } },
        { "WebCore::RequestedScrollData"_s, {
            {
                "WebCore::ScrollRequestType"_s,
                "requestType"_s
            },
            {
                "std::variant<WebCore::FloatPoint, WebCore::FloatSize>"_s,
                "scrollPositionOrDelta"_s
            },
            {
                "WebCore::ScrollType"_s,
                "scrollType"_s
            },
            {
                "WebCore::ScrollClamping"_s,
                "clamping"_s
            },
            {
                "WebCore::ScrollIsAnimated"_s,
                "animated"_s
            },
            {
                "std::optional<std::tuple<WebCore::ScrollRequestType, std::variant<WebCore::FloatPoint, WebCore::FloatSize>, WebCore::ScrollType, WebCore::ScrollClamping>>"_s,
                "requestedDataBeforeAnimatedScroll"_s
            },
        } },
        { "WebCore::FloatScrollSnapOffsetsInfo"_s, {
            {
                "WebCore::ScrollSnapStrictness"_s,
                "strictness"_s
            },
            {
                "Vector<WebCore::FloatSnapOffset>"_s,
                "horizontalSnapOffsets"_s
            },
            {
                "Vector<WebCore::FloatSnapOffset>"_s,
                "verticalSnapOffsets"_s
            },
            {
                "Vector<WebCore::FloatRect>"_s,
                "snapAreas"_s
            },
            {
                "Vector<WebCore::ElementIdentifier>"_s,
                "snapAreasIDs"_s
            },
        } },
        { "WebCore::FloatSnapOffset"_s, {
            {
                "float"_s,
                "offset"_s
            },
            {
                "WebCore::ScrollSnapStop"_s,
                "stop"_s
            },
            {
                "bool"_s,
                "hasSnapAreaLargerThanViewport"_s
            },
            {
                "WebCore::ElementIdentifier"_s,
                "snapTargetID"_s
            },
            {
                "bool"_s,
                "isFocused"_s
            },
            {
                "Vector<size_t>"_s,
                "snapAreaIndices"_s
            },
        } },
        { "WebCore::CDMMediaCapability"_s, {
            {
                "String"_s,
                "contentType"_s
            },
            {
                "String"_s,
                "robustness"_s
            },
            {
                "std::optional<WebCore::CDMEncryptionScheme>"_s,
                "encryptionScheme"_s
            },
        } },
        { "WebCore::CDMRestrictions"_s, {
            {
                "bool"_s,
                "distinctiveIdentifierDenied"_s
            },
            {
                "bool"_s,
                "persistentStateDenied"_s
            },
            {
                "HashSet<WebCore::CDMSessionType, IntHash<WebCore::CDMSessionType>, WTF::StrongEnumHashTraits<WebCore::CDMSessionType>>"_s,
                "deniedSessionTypes"_s
            },
        } },
        { "WebCore::MediaSelectionOption"_s, {
            {
                "WebCore::MediaSelectionOption::MediaType"_s,
                "mediaType"_s
            },
            {
                "String"_s,
                "displayName"_s
            },
            {
                "WebCore::MediaSelectionOption::LegibleType"_s,
                "legibleType"_s
            },
        } },
        { "WebCore::BufferSource"_s, {
            {
                "std::span<const uint8_t>"_s,
                "span()"_s
            },
        } },
        { "WebCore::FontShadow"_s, {
            {
                "WebCore::Color"_s,
                "color"_s
            },
            {
                "WebCore::FloatSize"_s,
                "offset"_s
            },
            {
                "double"_s,
                "blurRadius"_s
            },
        } },
        { "WebCore::CompositionHighlight"_s, {
            {
                "unsigned"_s,
                "startOffset"_s
            },
            {
                "unsigned"_s,
                "endOffset"_s
            },
            {
                "std::optional<WebCore::Color>"_s,
                "backgroundColor"_s
            },
            {
                "std::optional<WebCore::Color>"_s,
                "foregroundColor"_s
            },
        } },
        { "WebCore::FontChanges"_s, {
            {
                "String"_s,
                "m_fontName"_s
            },
            {
                "String"_s,
                "m_fontFamily"_s
            },
            {
                "std::optional<double>"_s,
                "m_fontSize"_s
            },
            {
                "std::optional<double>"_s,
                "m_fontSizeDelta"_s
            },
            {
                "std::optional<bool>"_s,
                "m_bold"_s
            },
            {
                "std::optional<bool>"_s,
                "m_italic"_s
            },
        } },
        { "WebCore::FontAttributeChanges"_s, {
            {
                "std::optional<WebCore::VerticalAlignChange>"_s,
                "m_verticalAlign"_s
            },
            {
                "std::optional<WebCore::Color>"_s,
                "m_backgroundColor"_s
            },
            {
                "std::optional<WebCore::Color>"_s,
                "m_foregroundColor"_s
            },
            {
                "std::optional<WebCore::FontShadow>"_s,
                "m_shadow"_s
            },
            {
                "std::optional<bool>"_s,
                "m_strikeThrough"_s
            },
            {
                "std::optional<bool>"_s,
                "m_underline"_s
            },
            {
                "WebCore::FontChanges"_s,
                "m_fontChanges"_s
            },
        } },
        { "WebCore::TextManipulationControllerExclusionRule::ElementRule"_s, {
            {
                "AtomString"_s,
                "localName"_s
            },
        } },
        { "WebCore::TextManipulationControllerExclusionRule::AttributeRule"_s, {
            {
                "AtomString"_s,
                "name"_s
            },
            {
                "String"_s,
                "value"_s
            },
        } },
        { "WebCore::TextManipulationControllerExclusionRule::ClassRule"_s, {
            {
                "AtomString"_s,
                "className"_s
            },
        } },
        { "WebCore::TextManipulationControllerExclusionRule"_s, {
            {
                "WebCore::TextManipulationControllerExclusionRule::Type"_s,
                "type"_s
            },
            {
                "std::variant<WebCore::TextManipulationControllerExclusionRule::ElementRule, WebCore::TextManipulationControllerExclusionRule::AttributeRule, WebCore::TextManipulationControllerExclusionRule::ClassRule>"_s,
                "rule"_s
            },
        } },
        { "WebCore::TextManipulationControllerManipulationFailure"_s, {
            {
                "WebCore::FrameIdentifier"_s,
                "frameID"_s
            },
            {
                "WebCore::TextManipulationItemIdentifier"_s,
                "identifier"_s
            },
            {
                "uint64_t"_s,
                "index"_s
            },
            {
                "WebCore::TextManipulationControllerManipulationFailure::Type"_s,
                "type"_s
            },
        } },
        { "WebCore::BackgroundFetchInformation"_s, {
            {
                "WebCore::ServiceWorkerRegistrationIdentifier"_s,
                "registrationIdentifier"_s
            },
            {
                "String"_s,
                "identifier"_s
            },
            {
                "uint64_t"_s,
                "uploadTotal"_s
            },
            {
                "uint64_t"_s,
                "uploaded"_s
            },
            {
                "uint64_t"_s,
                "downloadTotal"_s
            },
            {
                "uint64_t"_s,
                "downloaded"_s
            },
            {
                "WebCore::BackgroundFetchResult"_s,
                "result"_s
            },
            {
                "WebCore::BackgroundFetchFailureReason"_s,
                "failureReason"_s
            },
            {
                "bool"_s,
                "recordsAvailable"_s
            },
        } },
        { "WebCore::BackgroundFetchRequest"_s, {
            {
                "WebCore::ResourceRequest"_s,
                "internalRequest"_s
            },
            {
                "WebCore::FetchOptions"_s,
                "options"_s
            },
            {
                "WebCore::FetchHeadersGuard"_s,
                "guard"_s
            },
            {
                "WebCore::HTTPHeaderMap"_s,
                "httpHeaders"_s
            },
            {
                "String"_s,
                "referrer"_s
            },
            {
                "Markable<WebCore::ContentSecurityPolicyResponseHeaders, WebCore::ContentSecurityPolicyResponseHeaders::MarkableTraits>"_s,
                "cspResponseHeaders"_s
            },
        } },
        { "WebCore::BackgroundFetchRecordInformation"_s, {
            {
                "WebCore::BackgroundFetchRecordIdentifier"_s,
                "identifier"_s
            },
            {
                "WebCore::ResourceRequest"_s,
                "internalRequest"_s
            },
            {
                "WebCore::FetchOptions"_s,
                "options"_s
            },
            {
                "WebCore::FetchHeadersGuard"_s,
                "guard"_s
            },
            {
                "WebCore::HTTPHeaderMap"_s,
                "httpHeaders"_s
            },
            {
                "String"_s,
                "referrer"_s
            },
        } },
        { "WebCore::BackgroundFetchOptions"_s, {
            {
                "Vector<WebCore::ImageResource>"_s,
                "icons"_s
            },
            {
                "String"_s,
                "title"_s
            },
            {
                "uint64_t"_s,
                "downloadTotal"_s
            },
        } },
        { "WebCore::ImageResource"_s, {
            {
                "String"_s,
                "src"_s
            },
            {
                "String"_s,
                "sizes"_s
            },
            {
                "String"_s,
                "type"_s
            },
            {
                "String"_s,
                "label"_s
            },
        } },
        { "WebCore::FourCC"_s, {
            {
                "uint32_t"_s,
                "value"_s
            },
        } },
        { "WebCore::MediaEngineSupportParameters"_s, {
            {
                "WebCore::ContentType"_s,
                "type"_s
            },
            {
                "URL"_s,
                "url"_s
            },
            {
                "bool"_s,
                "isMediaSource"_s
            },
            {
                "bool"_s,
                "isMediaStream"_s
            },
            {
                "bool"_s,
                "requiresRemotePlayback"_s
            },
            {
                "Vector<WebCore::ContentType>"_s,
                "contentTypesRequiringHardwareSupport"_s
            },
            {
                "std::optional<Vector<String>>"_s,
                "allowedMediaContainerTypes"_s
            },
            {
                "std::optional<Vector<String>>"_s,
                "allowedMediaCodecTypes"_s
            },
            {
                "std::optional<Vector<WebCore::FourCC>>"_s,
                "allowedMediaVideoCodecIDs"_s
            },
            {
                "std::optional<Vector<WebCore::FourCC>>"_s,
                "allowedMediaAudioCodecIDs"_s
            },
            {
                "std::optional<Vector<WebCore::FourCC>>"_s,
                "allowedMediaCaptionFormatTypes"_s
            },
        } },
        { "WebCore::GeolocationPositionData"_s, {
            {
                "double"_s,
                "timestamp"_s
            },
            {
                "double"_s,
                "latitude"_s
            },
            {
                "double"_s,
                "longitude"_s
            },
            {
                "double"_s,
                "accuracy"_s
            },
            {
                "std::optional<double>"_s,
                "altitude"_s
            },
            {
                "std::optional<double>"_s,
                "altitudeAccuracy"_s
            },
            {
                "std::optional<double>"_s,
                "heading"_s
            },
            {
                "std::optional<double>"_s,
                "speed"_s
            },
            {
                "std::optional<double>"_s,
                "floorLevel"_s
            },
        } },
        { "WebCore::AppHighlight"_s, {
            {
                "Ref<WebCore::FragmentedSharedBuffer>"_s,
                "highlight"_s
            },
            {
                "std::optional<String>"_s,
                "text"_s
            },
            {
                "WebCore::CreateNewGroupForHighlight"_s,
                "isNewGroup"_s
            },
            {
                "WebCore::HighlightRequestOriginatedInApp"_s,
                "requestOriginatedInApp"_s
            },
        } },
        { "WebCore::MediaDeviceHashSalts"_s, {
            {
                "String"_s,
                "persistentDeviceSalt"_s
            },
            {
                "String"_s,
                "ephemeralDeviceSalt"_s
            },
        } },
        { "WebCore::SpeechRecognitionUpdate"_s, {
            {
                "WebCore::SpeechRecognitionConnectionClientIdentifier"_s,
                "m_clientIdentifier"_s
            },
            {
                "WebCore::SpeechRecognitionUpdateType"_s,
                "m_type"_s
            },
            {
                "std::variant<std::monostate, WebCore::SpeechRecognitionError, Vector<WebCore::SpeechRecognitionResultData>>"_s,
                "m_content"_s
            },
        } },
        { "WebCore::ARKitBadgeSystemImage"_s, {
            {
                "WebCore::RenderingResourceIdentifier"_s,
                "imageIdentifier()"_s
            },
            {
                "WebCore::FloatSize"_s,
                "m_imageSize"_s
            },
        } },
        { "WebCore::AudioIOPosition"_s, {
            {
                "Seconds"_s,
                "position"_s
            },
            {
                "MonotonicTime"_s,
                "timestamp"_s
            },
        } },
        { "WebCore::VideoFrameCV"_s, {
            {
                "MediaTime"_s,
                "presentationTime()"_s
            },
            {
                "bool"_s,
                "isMirrored()"_s
            },
            {
                "WebCore::VideoFrameRotation"_s,
                "rotation()"_s
            },
            {
                "RetainPtr<CVPixelBufferRef>"_s,
                "m_pixelBuffer"_s
            },
            {
                "WebCore::PlatformVideoColorSpace"_s,
                "colorSpace()"_s
            },
        } },
        { "WebCore::GradientColorStop"_s, {
            {
                "float"_s,
                "offset"_s
            },
            {
                "WebCore::Color"_s,
                "color"_s
            },
        } },
        { "WebCore::GradientColorStops"_s, {
            {
                "Vector<WebCore::GradientColorStop, 2>"_s,
                "stops()"_s
            },
        } },
        { "WebCore::ImageBufferBackendParameters"_s, {
            {
                "WebCore::FloatSize"_s,
                "logicalSize"_s
            },
            {
                "float"_s,
                "resolutionScale"_s
            },
            {
                "WebCore::DestinationColorSpace"_s,
                "colorSpace"_s
            },
            {
                "WebCore::PixelFormat"_s,
                "pixelFormat"_s
            },
            {
                "WebCore::RenderingPurpose"_s,
                "purpose"_s
            },
        } },
        { "WebCore::ProcessIdentity"_s, {
#if HAVE(TASK_IDENTITY_TOKEN)
            {
                "MachSendRight"_s,
                "m_taskIdToken"_s
            },
#endif
        } },
        { "WebCore::ColorInterpolationMethod::HSL"_s, {
            {
                "WebCore::HueInterpolationMethod"_s,
                "hueInterpolationMethod"_s
            },
        } },
        { "WebCore::ColorInterpolationMethod::HWB"_s, {
            {
                "WebCore::HueInterpolationMethod"_s,
                "hueInterpolationMethod"_s
            },
        } },
        { "WebCore::ColorInterpolationMethod::LCH"_s, {
            {
                "WebCore::HueInterpolationMethod"_s,
                "hueInterpolationMethod"_s
            },
        } },
        { "WebCore::ColorInterpolationMethod::Lab"_s, {
        } },
        { "WebCore::ColorInterpolationMethod::OKLCH"_s, {
            {
                "WebCore::HueInterpolationMethod"_s,
                "hueInterpolationMethod"_s
            },
        } },
        { "WebCore::ColorInterpolationMethod::OKLab"_s, {
        } },
        { "WebCore::ColorInterpolationMethod::SRGB"_s, {
        } },
        { "WebCore::ColorInterpolationMethod::SRGBLinear"_s, {
        } },
        { "WebCore::ColorInterpolationMethod::XYZD50"_s, {
        } },
        { "WebCore::ColorInterpolationMethod::XYZD65"_s, {
        } },
        { "WebCore::ColorInterpolationMethod"_s, {
            {
                "std::variant<WebCore::ColorInterpolationMethod::HSL, WebCore::ColorInterpolationMethod::HWB, WebCore::ColorInterpolationMethod::LCH, WebCore::ColorInterpolationMethod::Lab, WebCore::ColorInterpolationMethod::OKLCH, WebCore::ColorInterpolationMethod::OKLab, WebCore::ColorInterpolationMethod::SRGB, WebCore::ColorInterpolationMethod::SRGBLinear, WebCore::ColorInterpolationMethod::XYZD50, WebCore::ColorInterpolationMethod::XYZD65>"_s,
                "colorSpace"_s
            },
            {
                "WebCore::AlphaPremultiplication"_s,
                "alphaPremultiplication"_s
            },
        } },
        { "WebCore::CompositeMode"_s, {
            {
                "WebCore::CompositeOperator"_s,
                "operation"_s
            },
            {
                "WebCore::BlendMode"_s,
                "blendMode"_s
            },
        } },
        { "WebCore::DocumentMarkerLineStyle"_s, {
            {
                "WebCore::DocumentMarkerLineStyleMode"_s,
                "mode"_s
            },
            {
                "WebCore::Color"_s,
                "color"_s
            },
        } },
        { "WebCore::GraphicsDropShadow"_s, {
            {
                "WebCore::FloatSize"_s,
                "offset"_s
            },
            {
                "float"_s,
                "radius"_s
            },
            {
                "WebCore::Color"_s,
                "color"_s
            },
            {
                "WebCore::ShadowRadiusMode"_s,
                "radiusMode"_s
            },
        } },
        { "WebCore::GenericCueData"_s, {
            {
                "WebCore::InbandGenericCueIdentifier"_s,
                "m_uniqueId"_s
            },
            {
                "MediaTime"_s,
                "m_startTime"_s
            },
            {
                "MediaTime"_s,
                "m_endTime"_s
            },
            {
                "AtomString"_s,
                "m_id"_s
            },
            {
                "String"_s,
                "m_content"_s
            },
            {
                "String"_s,
                "m_fontName"_s
            },
            {
                "double"_s,
                "m_line"_s
            },
            {
                "double"_s,
                "m_position"_s
            },
            {
                "double"_s,
                "m_size"_s
            },
            {
                "double"_s,
                "m_baseFontSize"_s
            },
            {
                "double"_s,
                "m_relativeFontSize"_s
            },
            {
                "WebCore::Color"_s,
                "m_foregroundColor"_s
            },
            {
                "WebCore::Color"_s,
                "m_backgroundColor"_s
            },
            {
                "WebCore::Color"_s,
                "m_highlightColor"_s
            },
            {
                "WebCore::GenericCueData::Alignment"_s,
                "m_align"_s
            },
            {
                "WebCore::GenericCueData::Status"_s,
                "m_status"_s
            },
        } },
        { "WebCore::ImageDecoderFrameInfo"_s, {
            {
                "bool"_s,
                "hasAlpha"_s
            },
            {
                "Seconds"_s,
                "duration"_s
            },
        } },
        { "WebCore::DisplayList::DrawDotsForDocumentMarker"_s, {
            {
                "WebCore::FloatRect"_s,
                "rect()"_s
            },
            {
                "WebCore::DocumentMarkerLineStyle"_s,
                "style()"_s
            },
        } },
        { "WebCore::ImageOrientation"_s, {
            {
                "WebCore::ImageOrientation::Orientation"_s,
                "orientation()"_s
            },
        } },
        { "WebCore::ImagePaintingOptions"_s, {
            {
                "WebCore::CompositeOperator"_s,
                "m_compositeOperator"_s
            },
            {
                "WebCore::BlendMode"_s,
                "m_blendMode"_s
            },
            {
                "WebCore::DecodingMode"_s,
                "m_decodingMode"_s
            },
            {
                "WebCore::ImageOrientation"_s,
                "m_orientation"_s
            },
            {
                "WebCore::InterpolationQuality"_s,
                "m_interpolationQuality"_s
            },
        } },
        { "WebCore::CanvasActivityRecord"_s, {
            {
                "HashSet<String>"_s,
                "textWritten"_s
            },
            {
                "bool"_s,
                "wasDataRead"_s
            },
        } },
        { "WebCore::PCM::AttributionSecondsUntilSendData"_s, {
            {
                "std::optional<Seconds>"_s,
                "sourceSeconds"_s
            },
            {
                "std::optional<Seconds>"_s,
                "destinationSeconds"_s
            },
        } },
        { "WebCore::CrossOriginOpenerPolicy"_s, {
            {
                "WebCore::CrossOriginOpenerPolicyValue"_s,
                "value"_s
            },
            {
                "WebCore::CrossOriginOpenerPolicyValue"_s,
                "reportOnlyValue"_s
            },
            {
                "String"_s,
                "reportingEndpoint"_s
            },
            {
                "String"_s,
                "reportOnlyReportingEndpoint"_s
            },
        } },
        { "WebCore::CustomHeaderFields"_s, {
            {
                "Vector<WebCore::HTTPHeaderField>"_s,
                "fields"_s
            },
            {
                "Vector<String>"_s,
                "thirdPartyDomains"_s
            },
        } },
        { "WebCore::HTTPHeaderField"_s, {
            {
                "String"_s,
                "name()"_s
            },
            {
                "String"_s,
                "value()"_s
            },
        } },
        { "WebCore::NavigationRequester"_s, {
            {
                "URL"_s,
                "url"_s
            },
            {
                "Ref<WebCore::SecurityOrigin>"_s,
                "securityOrigin"_s
            },
            {
                "Ref<WebCore::SecurityOrigin>"_s,
                "topOrigin"_s
            },
            {
                "WebCore::PolicyContainer"_s,
                "policyContainer"_s
            },
            {
                "std::optional<WebCore::FrameIdentifier>"_s,
                "frameID"_s
            },
            {
                "std::optional<WebCore::PageIdentifier>"_s,
                "pageID"_s
            },
            {
                "WebCore::ScriptExecutionContextIdentifier"_s,
                "documentIdentifier"_s
            },
            {
                "WebCore::SandboxFlags"_s,
                "sandboxFlags"_s
            },
        } },
        { "WebCore::PolicyContainer"_s, {
            {
                "WebCore::ContentSecurityPolicyResponseHeaders"_s,
                "contentSecurityPolicyResponseHeaders"_s
            },
            {
                "WebCore::CrossOriginEmbedderPolicy"_s,
                "crossOriginEmbedderPolicy"_s
            },
            {
                "WebCore::CrossOriginOpenerPolicy"_s,
                "crossOriginOpenerPolicy"_s
            },
            {
                "WebCore::ReferrerPolicy"_s,
                "referrerPolicy"_s
            },
        } },
        { "WebCore::SubstituteData"_s, {
            {
                "RefPtr<WebCore::FragmentedSharedBuffer>"_s,
                "content()"_s
            },
            {
                "URL"_s,
                "failingURL()"_s
            },
            {
                "WebCore::ResourceResponse"_s,
                "response()"_s
            },
            {
                "WebCore::SubstituteData::SessionHistoryVisibility"_s,
                "shouldRevealToSessionHistory()"_s
            },
        } },
        { "WebCore::ServiceWorkerClientData"_s, {
            {
                "WebCore::ScriptExecutionContextIdentifier"_s,
                "identifier"_s
            },
            {
                "WebCore::ServiceWorkerClientType"_s,
                "type"_s
            },
            {
                "WebCore::ServiceWorkerClientFrameType"_s,
                "frameType"_s
            },
            {
                "URL"_s,
                "url"_s
            },
            {
                "URL"_s,
                "ownerURL"_s
            },
            {
                "std::optional<WebCore::PageIdentifier>"_s,
                "pageIdentifier"_s
            },
            {
                "std::optional<WebCore::FrameIdentifier>"_s,
                "frameIdentifier"_s
            },
            {
                "WebCore::LastNavigationWasAppInitiated"_s,
                "lastNavigationWasAppInitiated"_s
            },
            {
                "bool"_s,
                "isVisible"_s
            },
            {
                "bool"_s,
                "isFocused"_s
            },
            {
                "uint64_t"_s,
                "focusOrder"_s
            },
            {
                "Vector<String>"_s,
                "ancestorOrigins"_s
            },
        } },
        { "WebCore::ServiceWorkerClientPendingMessage"_s, {
            {
                "WebCore::MessageWithMessagePorts"_s,
                "message"_s
            },
            {
                "WebCore::ServiceWorkerData"_s,
                "sourceData"_s
            },
            {
                "String"_s,
                "sourceOrigin"_s
            },
        } },
        { "WebCore::ServiceWorkerClientQueryOptions"_s, {
            {
                "bool"_s,
                "includeUncontrolled"_s
            },
            {
                "WebCore::ServiceWorkerClientType"_s,
                "type"_s
            },
        } },
        { "WebCore::ServiceWorkerData"_s, {
            {
                "WebCore::ServiceWorkerIdentifier"_s,
                "identifier"_s
            },
            {
                "WebCore::ServiceWorkerRegistrationIdentifier"_s,
                "registrationIdentifier"_s
            },
            {
                "URL"_s,
                "scriptURL"_s
            },
            {
                "WebCore::ServiceWorkerState"_s,
                "state"_s
            },
            {
                "WebCore::WorkerType"_s,
                "type"_s
            },
        } },
        { "WebCore::ServiceWorkerJobData"_s, {
            {
                "WebCore::ServiceWorkerJobDataIdentifier"_s,
                "identifier()"_s
            },
            {
                "URL"_s,
                "scriptURL"_s
            },
            {
                "URL"_s,
                "clientCreationURL"_s
            },
            {
                "WebCore::SecurityOriginData"_s,
                "topOrigin"_s
            },
            {
                "URL"_s,
                "scopeURL"_s
            },
            {
                "WebCore::ServiceWorkerOrClientIdentifier"_s,
                "sourceContext"_s
            },
            {
                "WebCore::WorkerType"_s,
                "workerType"_s
            },
            {
                "WebCore::ServiceWorkerJobType"_s,
                "type"_s
            },
            {
                "String"_s,
                "domainForCachePartition"_s
            },
            {
                "bool"_s,
                "isFromServiceWorkerPage"_s
            },
            {
                "std::optional<WebCore::ServiceWorkerRegistrationOptions>"_s,
                "registrationOptions"_s
            },
        } },
        { "WebCore::EventInit"_s, {
            {
                "bool"_s,
                "bubbles"_s
            },
            {
                "bool"_s,
                "cancelable"_s
            },
            {
                "bool"_s,
                "composed"_s
            },
        } },
        { "WebCore::MessageWithMessagePorts"_s, {
            {
                "RefPtr<WebCore::SerializedScriptValue>"_s,
                "message"_s
            },
            {
                "Vector<WebCore::TransferredMessagePort>"_s,
                "transferredPorts"_s
            },
        } },
        { "WebCore::RequestStorageAccessResult"_s, {
            {
                "WebCore::StorageAccessWasGranted"_s,
                "wasGranted"_s
            },
            {
                "WebCore::StorageAccessPromptWasShown"_s,
                "promptWasShown"_s
            },
            {
                "WebCore::StorageAccessScope"_s,
                "scope"_s
            },
            {
                "WebCore::RegistrableDomain"_s,
                "topFrameDomain"_s
            },
            {
                "WebCore::RegistrableDomain"_s,
                "subFrameDomain"_s
            },
        } },
        { "WebCore::Exception"_s, {
            {
                "WebCore::ExceptionCode"_s,
                "code()"_s
            },
            {
                "String"_s,
                "message()"_s
            },
        } },
        { "WebCore::ExceptionData"_s, {
            {
                "WebCore::ExceptionCode"_s,
                "code"_s
            },
            {
                "String"_s,
                "message"_s
            },
        } },
        { "WebCore::MessagePortIdentifier"_s, {
            {
                "WebCore::ProcessIdentifier"_s,
                "processIdentifier"_s
            },
            {
                "WebCore::PortIdentifier"_s,
                "portIdentifier"_s
            },
        } },
        { "WebCore::SecurityPolicyViolationEventInit"_s, {
            {
                "String"_s,
                "documentURI"_s
            },
            {
                "String"_s,
                "referrer"_s
            },
            {
                "String"_s,
                "blockedURI"_s
            },
            {
                "String"_s,
                "violatedDirective"_s
            },
            {
                "String"_s,
                "effectiveDirective"_s
            },
            {
                "String"_s,
                "originalPolicy"_s
            },
            {
                "String"_s,
                "sourceFile"_s
            },
            {
                "String"_s,
                "sample"_s
            },
            {
                "WebCore::SecurityPolicyViolationEventDisposition"_s,
                "disposition"_s
            },
            {
                "unsigned short"_s,
                "statusCode"_s
            },
            {
                "unsigned"_s,
                "lineNumber"_s
            },
            {
                "unsigned"_s,
                "columnNumber"_s
            },
        } },
        { "WebCore::CSPViolationReportBody"_s, {
            {
                "String"_s,
                "documentURL()"_s
            },
            {
                "String"_s,
                "referrer()"_s
            },
            {
                "String"_s,
                "blockedURL()"_s
            },
            {
                "String"_s,
                "effectiveDirective()"_s
            },
            {
                "String"_s,
                "originalPolicy()"_s
            },
            {
                "String"_s,
                "sourceFile()"_s
            },
            {
                "String"_s,
                "sample()"_s
            },
            {
                "WebCore::SecurityPolicyViolationEventDisposition"_s,
                "disposition()"_s
            },
            {
                "unsigned short"_s,
                "statusCode()"_s
            },
            {
                "unsigned long"_s,
                "lineNumber()"_s
            },
            {
                "unsigned long"_s,
                "columnNumber()"_s
            },
        } },
        { "WebCore::SecurityOriginData"_s, {
            {
                "std::variant<WebCore::SecurityOriginData::Tuple, WebCore::ProcessQualified<WebCore::OpaqueOriginIdentifier>>"_s,
                "data()"_s
            },
        } },
        { "WebCore::SecurityOriginData::Tuple"_s, {
            {
                "String"_s,
                "protocol"_s
            },
            {
                "String"_s,
                "host"_s
            },
            {
                "std::optional<uint16_t>"_s,
                "port"_s
            },
        } },
        { "WebCore::MediaConstraint"_s, {
            {
                "String"_s,
                "name()"_s
            },
            {
                "WebCore::MediaConstraintType"_s,
                "constraintType()"_s
            },
            {
                "WebCore::MediaConstraint::DataType"_s,
                "dataType()"_s
            },
        } },
        { "WebCore::IntConstraint"_s, {
            {
                "std::optional<int>"_s,
                "m_min"_s
            },
            {
                "std::optional<int>"_s,
                "m_max"_s
            },
            {
                "std::optional<int>"_s,
                "m_exact"_s
            },
            {
                "std::optional<int>"_s,
                "m_ideal"_s
            },
        } },
        { "WebCore::DoubleConstraint"_s, {
            {
                "std::optional<double>"_s,
                "m_min"_s
            },
            {
                "std::optional<double>"_s,
                "m_max"_s
            },
            {
                "std::optional<double>"_s,
                "m_exact"_s
            },
            {
                "std::optional<double>"_s,
                "m_ideal"_s
            },
        } },
        { "WebCore::BooleanConstraint"_s, {
            {
                "std::optional<bool>"_s,
                "m_exact"_s
            },
            {
                "std::optional<bool>"_s,
                "m_ideal"_s
            },
        } },
        { "WebCore::StringConstraint"_s, {
            {
                "Vector<String>"_s,
                "m_exact"_s
            },
            {
                "Vector<String>"_s,
                "m_ideal"_s
            },
        } },
        { "WebCore::FrameRateRange"_s, {
            {
                "double"_s,
                "minimum"_s
            },
            {
                "double"_s,
                "maximum"_s
            },
        } },
        { "WebCore::VideoPresetData"_s, {
            {
                "WebCore::IntSize"_s,
                "size"_s
            },
            {
                "Vector<WebCore::FrameRateRange>"_s,
                "frameRateRanges"_s
            },
            {
                "double"_s,
                "minZoom"_s
            },
            {
                "double"_s,
                "maxZoom"_s
            },
        } },
        { "WebCore::RealtimeMediaSourceSupportedConstraints"_s, {
            {
                "bool"_s,
                "supportsWidth()"_s
            },
            {
                "bool"_s,
                "supportsHeight()"_s
            },
            {
                "bool"_s,
                "supportsAspectRatio()"_s
            },
            {
                "bool"_s,
                "supportsFrameRate()"_s
            },
            {
                "bool"_s,
                "supportsFacingMode()"_s
            },
            {
                "bool"_s,
                "supportsVolume()"_s
            },
            {
                "bool"_s,
                "supportsSampleRate()"_s
            },
            {
                "bool"_s,
                "supportsSampleSize()"_s
            },
            {
                "bool"_s,
                "supportsEchoCancellation()"_s
            },
            {
                "bool"_s,
                "supportsDeviceId()"_s
            },
            {
                "bool"_s,
                "supportsGroupId()"_s
            },
            {
                "bool"_s,
                "supportsDisplaySurface()"_s
            },
            {
                "bool"_s,
                "supportsLogicalSurface()"_s
            },
            {
                "bool"_s,
                "supportsFocusDistance()"_s
            },
            {
                "bool"_s,
                "supportsZoom()"_s
            },
        } },
        { "WebCore::RealtimeMediaSourceSettings"_s, {
            {
                "uint32_t"_s,
                "width()"_s
            },
            {
                "uint32_t"_s,
                "height()"_s
            },
            {
                "float"_s,
                "frameRate()"_s
            },
            {
                "WebCore::VideoFacingMode"_s,
                "facingMode()"_s
            },
            {
                "double"_s,
                "volume()"_s
            },
            {
                "uint32_t"_s,
                "sampleRate()"_s
            },
            {
                "uint32_t"_s,
                "sampleSize()"_s
            },
            {
                "bool"_s,
                "echoCancellation()"_s
            },
            {
                "AtomString"_s,
                "deviceId()"_s
            },
            {
                "String"_s,
                "groupId()"_s
            },
            {
                "AtomString"_s,
                "label()"_s
            },
            {
                "WebCore::DisplaySurfaceType"_s,
                "displaySurface()"_s
            },
            {
                "bool"_s,
                "logicalSurface()"_s
            },
            {
                "double"_s,
                "zoom()"_s
            },
            {
                "WebCore::RealtimeMediaSourceSupportedConstraints"_s,
                "supportedConstraints()"_s
            },
        } },
        { "WebCore::CaptureDevice"_s, {
            {
                "String"_s,
                "persistentId()"_s
            },
            {
                "WebCore::CaptureDevice::DeviceType"_s,
                "type()"_s
            },
            {
                "String"_s,
                "label()"_s
            },
            {
                "String"_s,
                "groupId()"_s
            },
            {
                "bool"_s,
                "enabled()"_s
            },
            {
                "bool"_s,
                "isDefault()"_s
            },
            {
                "bool"_s,
                "isMockDevice()"_s
            },
            {
                "bool"_s,
                "isEphemeral()"_s
            },
        } },
        { "WebCore::CaptureDeviceWithCapabilities"_s, {
            {
                "WebCore::CaptureDevice"_s,
                "device"_s
            },
            {
                "WebCore::RealtimeMediaSourceCapabilities"_s,
                "capabilities"_s
            },
        } },
        { "WebCore::RealtimeMediaSourceCapabilities"_s, {
            {
                "WebCore::CapabilityValueOrRange"_s,
                "width()"_s
            },
            {
                "WebCore::CapabilityValueOrRange"_s,
                "height()"_s
            },
            {
                "WebCore::CapabilityValueOrRange"_s,
                "aspectRatio()"_s
            },
            {
                "WebCore::CapabilityValueOrRange"_s,
                "frameRate()"_s
            },
            {
                "Vector<WebCore::VideoFacingMode>"_s,
                "facingMode()"_s
            },
            {
                "WebCore::CapabilityValueOrRange"_s,
                "volume()"_s
            },
            {
                "WebCore::CapabilityValueOrRange"_s,
                "sampleRate()"_s
            },
            {
                "WebCore::CapabilityValueOrRange"_s,
                "sampleSize()"_s
            },
            {
                "WebCore::RealtimeMediaSourceCapabilities::EchoCancellation"_s,
                "echoCancellation()"_s
            },
            {
                "AtomString"_s,
                "deviceId()"_s
            },
            {
                "AtomString"_s,
                "groupId()"_s
            },
            {
                "WebCore::CapabilityValueOrRange"_s,
                "focusDistance()"_s
            },
            {
                "WebCore::CapabilityValueOrRange"_s,
                "zoom()"_s
            },
            {
                "WebCore::RealtimeMediaSourceSupportedConstraints"_s,
                "supportedConstraints()"_s
            },
        } },
        { "WebCore::PlatformVideoColorSpace"_s, {
            {
                "std::optional<WebCore::PlatformVideoColorPrimaries>"_s,
                "primaries"_s
            },
            {
                "std::optional<WebCore::PlatformVideoTransferCharacteristics>"_s,
                "transfer"_s
            },
            {
                "std::optional<WebCore::PlatformVideoMatrixCoefficients>"_s,
                "matrix"_s
            },
            {
                "std::optional<bool>"_s,
                "fullRange"_s
            },
        } },
        { "WebCore::PlatformTrackConfiguration"_s, {
            {
                "String"_s,
                "codec"_s
            },
        } },
        { "WebCore::PlatformAudioTrackConfiguration"_s, {
            {
                "uint32_t"_s,
                "sampleRate"_s
            },
            {
                "uint32_t"_s,
                "numberOfChannels"_s
            },
            {
                "uint64_t"_s,
                "bitrate"_s
            },
        } },
        { "WebCore::PlatformVideoTrackConfiguration"_s, {
            {
                "uint32_t"_s,
                "width"_s
            },
            {
                "uint32_t"_s,
                "height"_s
            },
            {
                "WebCore::PlatformVideoColorSpace"_s,
                "colorSpace"_s
            },
            {
                "double"_s,
                "framerate"_s
            },
            {
                "uint64_t"_s,
                "bitrate"_s
            },
        } },
        { "WebCore::RTCDataChannelInit"_s, {
            {
                "std::optional<bool>"_s,
                "ordered"_s
            },
            {
                "std::optional<unsigned short>"_s,
                "maxPacketLifeTime"_s
            },
            {
                "std::optional<unsigned short>"_s,
                "maxRetransmits"_s
            },
            {
                "String"_s,
                "protocol"_s
            },
            {
                "std::optional<bool>"_s,
                "negotiated"_s
            },
            {
                "std::optional<unsigned short>"_s,
                "id"_s
            },
            {
                "WebCore::RTCPriorityType"_s,
                "priority"_s
            },
        } },
        { "WebCore::RTCDataChannelIdentifier"_s, {
            {
                "WebCore::ProcessIdentifier"_s,
                "processIdentifier"_s
            },
            {
                "WebCore::RTCDataChannelLocalIdentifier"_s,
                "channelIdentifier"_s
            },
        } },
        { "WebCore::ContentRuleListResults::Result"_s, {
            {
                "bool"_s,
                "blockedLoad"_s
            },
            {
                "bool"_s,
                "madeHTTPS"_s
            },
            {
                "bool"_s,
                "blockedCookies"_s
            },
            {
                "bool"_s,
                "modifiedHeaders"_s
            },
            {
                "bool"_s,
                "redirected"_s
            },
            {
                "Vector<String>"_s,
                "notifications"_s
            },
        } },
        { "WebCore::ContentRuleListResults::Summary"_s, {
            {
                "bool"_s,
                "blockedLoad"_s
            },
            {
                "bool"_s,
                "madeHTTPS"_s
            },
            {
                "bool"_s,
                "blockedCookies"_s
            },
            {
                "bool"_s,
                "hasNotifications"_s
            },
        } },
        { "WebCore::ContentRuleListResults"_s, {
            {
                "WebCore::ContentRuleListResults::Summary"_s,
                "summary"_s
            },
            {
                "Vector<std::pair<String, WebCore::ContentRuleListResults::Result>>"_s,
                "results"_s
            },
        } },
        { "WebCore::COEPInheritenceViolationReportBody"_s, {
            {
                "WebCore::COEPDisposition"_s,
                "m_disposition"_s
            },
            {
                "URL"_s,
                "m_blockedURL"_s
            },
            {
                "String"_s,
                "m_type"_s
            },
        } },
        { "WebCore::CORPViolationReportBody"_s, {
            {
                "WebCore::COEPDisposition"_s,
                "m_disposition"_s
            },
            {
                "URL"_s,
                "m_blockedURL"_s
            },
            {
                "WebCore::FetchOptionsDestination"_s,
                "m_destination"_s
            },
        } },
        { "WebCore::ReportBody"_s, {
            { "std::variant<WebCore::CSPViolationReportBody, WebCore::COEPInheritenceViolationReportBody, WebCore::CORPViolationReportBody, WebCore::DeprecationReportBody, WebCore::TestReportBody>"_s, "subclasses"_s }
        } },
        { "WebCore::SourceImage"_s, {
            {
                "WebCore::RenderingResourceIdentifier"_s,
                "imageIdentifier()"_s
            },
        } },
        { "WebCore::LinkIcon"_s, {
            {
                "URL"_s,
                "url"_s
            },
            {
                "WebCore::LinkIconType"_s,
                "type"_s
            },
            {
                "String"_s,
                "mimeType"_s
            },
            {
                "std::optional<unsigned>"_s,
                "size"_s
            },
            {
                "Vector<std::pair<String, String>>"_s,
                "attributes"_s
            },
        } },
        { "WebCore::SupportedPluginIdentifier"_s, {
            {
                "String"_s,
                "matchingDomain"_s
            },
            {
                "String"_s,
                "pluginIdentifier"_s
            },
        } },
        { "WebCore::CSSValueKey"_s, {
            {
                "unsigned"_s,
                "cssValueID"_s
            },
            {
                "bool"_s,
                "useDarkAppearance"_s
            },
            {
                "bool"_s,
                "useElevatedUserInterfaceLevel"_s
            },
        } },
        { "WebCore::VideoFrameTimeMetadata"_s, {
            {
                "std::optional<double>"_s,
                "processingDuration"_s
            },
            {
                "std::optional<Seconds>"_s,
                "captureTime"_s
            },
            {
                "std::optional<Seconds>"_s,
                "receiveTime"_s
            },
            {
                "std::optional<unsigned>"_s,
                "rtpTimestamp"_s
            },
        } },
        { "WebCore::PositionedGlyphs"_s, {
            {
                "Vector<WebCore::GlyphBufferGlyph>"_s,
                "glyphs"_s
            },
            {
                "Vector<WebCore::GlyphBufferAdvance>"_s,
                "advances"_s
            },
            {
                "WebCore::FloatPoint"_s,
                "localAnchor"_s
            },
            {
                "WebCore::FontSmoothingMode"_s,
                "smoothingMode"_s
            },
        } },
        { "WebCore::EventRegion"_s, {
            {
                "WebCore::Region"_s,
                "m_region"_s
            },
#if ENABLE(TOUCH_ACTION_REGIONS)
            {
                "Vector<WebCore::Region>"_s,
                "m_touchActionRegions"_s
            },
#endif
#if ENABLE(WHEEL_EVENT_REGIONS)
            {
                "WebCore::Region"_s,
                "m_wheelEventListenerRegion"_s
            },
#endif
#if ENABLE(WHEEL_EVENT_REGIONS)
            {
                "WebCore::Region"_s,
                "m_nonPassiveWheelEventListenerRegion"_s
            },
#endif
#if ENABLE(EDITABLE_REGION)
            {
                "std::optional<WebCore::Region>"_s,
                "m_editableRegion"_s
            },
#endif
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
            {
                "Vector<WebCore::InteractionRegion>"_s,
                "m_interactionRegions"_s
            },
#endif
        } },
        { "WebCore::PresentationSize"_s, {
            {
                "std::optional<double>"_s,
                "width"_s
            },
            {
                "std::optional<double>"_s,
                "height"_s
            },
        } },
        { "WebCore::PasteboardItemInfo"_s, {
            {
                "Vector<String>"_s,
                "pathsForFileUpload"_s
            },
            {
                "Vector<String>"_s,
                "platformTypesForFileUpload"_s
            },
            {
                "Vector<String>"_s,
                "platformTypesByFidelity"_s
            },
            {
                "String"_s,
                "suggestedFileName"_s
            },
            {
                "WebCore::PresentationSize"_s,
                "preferredPresentationSize"_s
            },
            {
                "bool"_s,
                "isNonTextType"_s
            },
            {
                "bool"_s,
                "containsFileURLAndFileUploadContent"_s
            },
            {
                "Vector<String>"_s,
                "webSafeTypesByFidelity"_s
            },
            {
                "WebCore::PasteboardItemPresentationStyle"_s,
                "preferredPresentationStyle"_s
            },
        } },
        { "WebCore::MediaControlsContextMenuItem"_s, {
            {
                "uint64_t"_s,
                "id"_s
            },
            {
                "String"_s,
                "title"_s
            },
            {
                "String"_s,
                "icon"_s
            },
            {
                "bool"_s,
                "checked"_s
            },
            {
                "Vector<WebCore::MediaControlsContextMenuItem>"_s,
                "children"_s
            },
        } },
        { "WebCore::WorkerOptions"_s, {
            {
                "WebCore::WorkerType"_s,
                "type"_s
            },
            {
                "WebCore::FetchRequestCredentials"_s,
                "credentials"_s
            },
            {
                "String"_s,
                "name"_s
            },
        } },
        { "WebCore::WorkerInitializationData"_s, {
#if ENABLE(SERVICE_WORKER)
            {
                "std::optional<WebCore::ServiceWorkerData>"_s,
                "serviceWorkerData"_s
            },
#endif
            {
                "std::optional<WebCore::ScriptExecutionContextIdentifier>"_s,
                "clientIdentifier"_s
            },
            {
                "String"_s,
                "userAgent"_s
            },
        } },
        { "WebCore::WorkerFetchResult"_s, {
            {
                "WebCore::ScriptBuffer"_s,
                "script"_s
            },
            {
                "URL"_s,
                "responseURL"_s
            },
            {
                "WebCore::CertificateInfo"_s,
                "certificateInfo"_s
            },
            {
                "WebCore::ContentSecurityPolicyResponseHeaders"_s,
                "contentSecurityPolicy"_s
            },
            {
                "WebCore::CrossOriginEmbedderPolicy"_s,
                "crossOriginEmbedderPolicy"_s
            },
            {
                "String"_s,
                "referrerPolicy"_s
            },
            {
                "WebCore::ResourceError"_s,
                "error"_s
            },
        } },
        { "WebCore::SharedWorkerKey"_s, {
            {
                "WebCore::ClientOrigin"_s,
                "origin"_s
            },
            {
                "URL"_s,
                "url"_s
            },
            {
                "String"_s,
                "name"_s
            },
        } },
        { "WebCore::ServiceWorkerRegistrationOptions"_s, {
            {
                "String"_s,
                "scope"_s
            },
            {
                "WebCore::WorkerType"_s,
                "type"_s
            },
            {
                "WebCore::ServiceWorkerUpdateViaCache"_s,
                "updateViaCache"_s
            },
        } },
        { "WebCore::ServiceWorkerRegistrationKey"_s, {
            {
                "WebCore::SecurityOriginData"_s,
                "topOrigin()"_s
            },
            {
                "URL"_s,
                "scope()"_s
            },
        } },
        { "WebCore::ServiceWorkerRegistrationData"_s, {
            {
                "WebCore::ServiceWorkerRegistrationKey"_s,
                "key"_s
            },
            {
                "WebCore::ServiceWorkerRegistrationIdentifier"_s,
                "identifier"_s
            },
            {
                "URL"_s,
                "scopeURL"_s
            },
            {
                "WebCore::ServiceWorkerUpdateViaCache"_s,
                "updateViaCache"_s
            },
            {
                "WallTime"_s,
                "lastUpdateTime"_s
            },
            {
                "std::optional<WebCore::ServiceWorkerData>"_s,
                "installingWorker"_s
            },
            {
                "std::optional<WebCore::ServiceWorkerData>"_s,
                "waitingWorker"_s
            },
            {
                "std::optional<WebCore::ServiceWorkerData>"_s,
                "activeWorker"_s
            },
        } },
        { "WebCore::ServiceWorkerJobDataIdentifier"_s, {
            {
                "WebCore::SWServerConnectionIdentifier"_s,
                "connectionIdentifier"_s
            },
            {
                "WebCore::ServiceWorkerJobIdentifier"_s,
                "jobIdentifier"_s
            },
        } },
        { "WebCore::ServiceWorkerImportedScript"_s, {
            {
                "WebCore::ScriptBuffer"_s,
                "script"_s
            },
            {
                "URL"_s,
                "responseURL"_s
            },
            {
                "String"_s,
                "mimeType"_s
            },
        } },
        { "WebCore::ServiceWorkerContextData"_s, {
            {
                "std::optional<WebCore::ServiceWorkerJobDataIdentifier>"_s,
                "jobDataIdentifier"_s
            },
            {
                "WebCore::ServiceWorkerRegistrationData"_s,
                "registration"_s
            },
            {
                "WebCore::ServiceWorkerIdentifier"_s,
                "serviceWorkerIdentifier"_s
            },
            {
                "WebCore::ScriptBuffer"_s,
                "script"_s
            },
            {
                "WebCore::CertificateInfo"_s,
                "certificateInfo"_s
            },
            {
                "WebCore::ContentSecurityPolicyResponseHeaders"_s,
                "contentSecurityPolicy"_s
            },
            {
                "WebCore::CrossOriginEmbedderPolicy"_s,
                "crossOriginEmbedderPolicy"_s
            },
            {
                "String"_s,
                "referrerPolicy"_s
            },
            {
                "URL"_s,
                "scriptURL"_s
            },
            {
                "WebCore::WorkerType"_s,
                "workerType"_s
            },
            {
                "bool"_s,
                "loadedFromDisk"_s
            },
            {
                "std::optional<WebCore::LastNavigationWasAppInitiated>"_s,
                "lastNavigationWasAppInitiated"_s
            },
            {
                "MemoryCompactRobinHoodHashMap<URL, WebCore::ServiceWorkerImportedScript>"_s,
                "scriptResourceMap"_s
            },
            {
                "std::optional<WebCore::ScriptExecutionContextIdentifier>"_s,
                "serviceWorkerPageIdentifier"_s
            },
            {
                "WebCore::NavigationPreloadState"_s,
                "navigationPreloadState"_s
            },
        } },
        { "JSC::ArrayBuffer"_s, {
            {
                "Vector<uint8_t>"_s,
                "toVector()"_s
            },
        } },
        { "WebCore::GlobalFrameIdentifier"_s, {
            {
                "WebCore::PageIdentifier"_s,
                "pageID"_s
            },
            {
                "WebCore::FrameIdentifier"_s,
                "frameID"_s
            },
        } },
        { "WebCore::GlobalWindowIdentifier"_s, {
            {
                "WebCore::ProcessIdentifier"_s,
                "processIdentifier"_s
            },
            {
                "WebCore::WindowIdentifier"_s,
                "windowIdentifier"_s
            },
        } },
        { "WebCore::InteractionRegion"_s, {
            {
                "WebCore::InteractionRegion::Type"_s,
                "type"_s
            },
            {
                "WebCore::ElementIdentifier"_s,
                "elementIdentifier"_s
            },
            {
                "WebCore::IntRect"_s,
                "rectInLayerCoordinates"_s
            },
            {
                "float"_s,
                "borderRadius"_s
            },
            {
                "OptionSet<WebCore::InteractionRegion::CornerMask>"_s,
                "maskedCorners"_s
            },
        } },
        { "WebCore::Region::Span"_s, {
            {
                "int"_s,
                "y"_s
            },
            {
                "size_t"_s,
                "segmentIndex"_s
            },
        } },
        { "WebCore::Region::Shape"_s, {
            {
                "Vector<int, 32>"_s,
                "m_segments"_s
            },
            {
                "Vector<WebCore::Region::Span, 16>"_s,
                "m_spans"_s
            },
        } },
        { "WebCore::Region"_s, {
            {
                "WebCore::IntRect"_s,
                "bounds()"_s
            },
            {
                "std::unique_ptr<WebCore::Region::Shape>"_s,
                "copyShape()"_s
            },
        } },
        { "WebCore::ISOWebVTTCue"_s, {
            {
                "MediaTime"_s,
                "presentationTime()"_s
            },
            {
                "MediaTime"_s,
                "duration()"_s
            },
            {
                "AtomString"_s,
                "id()"_s
            },
            {
                "String"_s,
                "cueText()"_s
            },
            {
                "String"_s,
                "settings()"_s
            },
            {
                "String"_s,
                "sourceID()"_s
            },
            {
                "String"_s,
                "originalStartTime()"_s
            },
        } },
        { "WebCore::MockWebAuthenticationConfiguration::LocalConfiguration"_s, {
            {
                "WebCore::MockWebAuthenticationConfiguration::UserVerification"_s,
                "userVerification"_s
            },
            {
                "bool"_s,
                "acceptAttestation"_s
            },
            {
                "String"_s,
                "privateKeyBase64"_s
            },
            {
                "String"_s,
                "userCertificateBase64"_s
            },
            {
                "String"_s,
                "intermediateCACertificateBase64"_s
            },
            {
                "String"_s,
                "preferredCredentialIdBase64"_s
            },
        } },
        { "WebCore::MockWebAuthenticationConfiguration::HidConfiguration"_s, {
            {
                "Vector<String>"_s,
                "payloadBase64"_s
            },
            {
                "WebCore::MockWebAuthenticationConfiguration::HidStage"_s,
                "stage"_s
            },
            {
                "WebCore::MockWebAuthenticationConfiguration::HidSubStage"_s,
                "subStage"_s
            },
            {
                "WebCore::MockWebAuthenticationConfiguration::HidError"_s,
                "error"_s
            },
            {
                "bool"_s,
                "isU2f"_s
            },
            {
                "bool"_s,
                "keepAlive"_s
            },
            {
                "bool"_s,
                "fastDataArrival"_s
            },
            {
                "bool"_s,
                "continueAfterErrorData"_s
            },
            {
                "bool"_s,
                "canDowngrade"_s
            },
            {
                "bool"_s,
                "expectCancel"_s
            },
            {
                "bool"_s,
                "supportClientPin"_s
            },
            {
                "bool"_s,
                "supportInternalUV"_s
            },
        } },
        { "WebCore::MockWebAuthenticationConfiguration::NfcConfiguration"_s, {
            {
                "WebCore::MockWebAuthenticationConfiguration::NfcError"_s,
                "error"_s
            },
            {
                "Vector<String>"_s,
                "payloadBase64"_s
            },
            {
                "bool"_s,
                "multipleTags"_s
            },
            {
                "bool"_s,
                "multiplePhysicalTags"_s
            },
        } },
        { "WebCore::MockWebAuthenticationConfiguration::CcidConfiguration"_s, {
            {
                "Vector<String>"_s,
                "payloadBase64"_s
            },
        } },
        { "WebCore::MockWebAuthenticationConfiguration"_s, {
            {
                "bool"_s,
                "silentFailure"_s
            },
            {
                "std::optional<WebCore::MockWebAuthenticationConfiguration::LocalConfiguration>"_s,
                "local"_s
            },
            {
                "std::optional<WebCore::MockWebAuthenticationConfiguration::HidConfiguration>"_s,
                "hid"_s
            },
            {
                "std::optional<WebCore::MockWebAuthenticationConfiguration::NfcConfiguration>"_s,
                "nfc"_s
            },
            {
                "std::optional<WebCore::MockWebAuthenticationConfiguration::CcidConfiguration>"_s,
                "ccid"_s
            },
        } },
        { "WebCore::LengthPoint"_s, {
            {
                "WebCore::Length"_s,
                "x()"_s
            },
            {
                "WebCore::Length"_s,
                "y()"_s
            },
        } },
        { "WebCore::OffsetRotation"_s, {
            {
                "bool"_s,
                "hasAuto()"_s
            },
            {
                "float"_s,
                "angle()"_s
            },
        } },
        { "WebCore::AcceleratedEffectValues"_s, {
            {
                "float"_s,
                "opacity"_s
            },
            {
                "WebCore::LengthPoint"_s,
                "transformOrigin"_s
            },
            {
                "WebCore::TransformOperations"_s,
                "transform"_s
            },
            {
                "RefPtr<WebCore::TransformOperation>"_s,
                "translate"_s
            },
            {
                "RefPtr<WebCore::TransformOperation>"_s,
                "scale"_s
            },
            {
                "RefPtr<WebCore::TransformOperation>"_s,
                "rotate"_s
            },
            {
                "RefPtr<WebCore::PathOperation>"_s,
                "offsetPath"_s
            },
            {
                "WebCore::Length"_s,
                "offsetDistance"_s
            },
            {
                "WebCore::LengthPoint"_s,
                "offsetPosition"_s
            },
            {
                "WebCore::LengthPoint"_s,
                "offsetAnchor"_s
            },
            {
                "WebCore::OffsetRotation"_s,
                "offsetRotate"_s
            },
            {
                "WebCore::FilterOperations"_s,
                "filter"_s
            },
#if ENABLE(FILTERS_LEVEL_2)
            {
                "WebCore::FilterOperations"_s,
                "backdropFilter"_s
            },
#endif
        } },
        { "WebCore::AcceleratedEffectKeyframe"_s, {
            {
                "double"_s,
                "offset"_s
            },
            {
                "WebCore::AcceleratedEffectValues"_s,
                "values"_s
            },
            {
                "RefPtr<WebCore::TimingFunction>"_s,
                "timingFunction"_s
            },
            {
                "std::optional<WebCore::CompositeOperation>"_s,
                "compositeOperation"_s
            },
            {
                "OptionSet<WebCore::AcceleratedEffectProperty>"_s,
                "animatedProperties"_s
            },
        } },
        { "WebCore::AcceleratedEffect"_s, {
            {
                "Vector<WebCore::AcceleratedEffectKeyframe>"_s,
                "keyframes()"_s
            },
            {
                "WebCore::WebAnimationType"_s,
                "animationType()"_s
            },
            {
                "WebCore::FillMode"_s,
                "fill()"_s
            },
            {
                "WebCore::PlaybackDirection"_s,
                "direction()"_s
            },
            {
                "WebCore::CompositeOperation"_s,
                "compositeOperation()"_s
            },
            {
                "RefPtr<WebCore::TimingFunction>"_s,
                "timingFunction()"_s
            },
            {
                "RefPtr<WebCore::TimingFunction>"_s,
                "defaultKeyframeTimingFunction()"_s
            },
            {
                "OptionSet<WebCore::AcceleratedEffectProperty>"_s,
                "animatedProperties()"_s
            },
            {
                "bool"_s,
                "paused()"_s
            },
            {
                "double"_s,
                "iterationStart()"_s
            },
            {
                "double"_s,
                "iterations()"_s
            },
            {
                "double"_s,
                "playbackRate()"_s
            },
            {
                "WTF::Seconds"_s,
                "delay()"_s
            },
            {
                "WTF::Seconds"_s,
                "endDelay()"_s
            },
            {
                "WTF::Seconds"_s,
                "iterationDuration()"_s
            },
            {
                "WTF::Seconds"_s,
                "activeDuration()"_s
            },
            {
                "WTF::Seconds"_s,
                "endTime()"_s
            },
            {
                "std::optional<WTF::Seconds>"_s,
                "startTime()"_s
            },
            {
                "std::optional<WTF::Seconds>"_s,
                "holdTime()"_s
            },
        } },
        { "WebCore::ProtectionSpace"_s, {
            {
                "String"_s,
                "host()"_s
            },
            {
                "int"_s,
                "port()"_s
            },
            {
                "WebCore::ProtectionSpace::ServerType"_s,
                "serverType()"_s
            },
            {
                "String"_s,
                "realm()"_s
            },
            {
                "WebCore::ProtectionSpace::AuthenticationScheme"_s,
                "authenticationScheme()"_s
            },
#if USE(CURL)
            {
                "WebCore::CertificateInfo"_s,
                "certificateInfo()"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "std::optional<WebCore::ProtectionSpace::PlatformData>"_s,
                "getPlatformDataToSerialize()"_s
            },
#endif
        } },
        { "WebCore::ShapeDetection::BarcodeDetectorOptions"_s, {
            {
                "Vector<WebCore::ShapeDetection::BarcodeFormat>"_s,
                "formats"_s
            },
        } },
        { "WebCore::ShapeDetection::DetectedBarcode"_s, {
            {
                "WebCore::FloatRect"_s,
                "boundingBox"_s
            },
            {
                "String"_s,
                "rawValue"_s
            },
            {
                "WebCore::ShapeDetection::BarcodeFormat"_s,
                "format"_s
            },
            {
                "Vector<WebCore::FloatPoint>"_s,
                "cornerPoints"_s
            },
        } },
        { "WebCore::ShapeDetection::DetectedFace"_s, {
            {
                "WebCore::FloatRect"_s,
                "boundingBox"_s
            },
            {
                "std::optional<Vector<WebCore::ShapeDetection::Landmark>>"_s,
                "landmarks"_s
            },
        } },
        { "WebCore::ShapeDetection::DetectedText"_s, {
            {
                "WebCore::FloatRect"_s,
                "boundingBox"_s
            },
            {
                "String"_s,
                "rawValue"_s
            },
            {
                "Vector<WebCore::FloatPoint>"_s,
                "cornerPoints"_s
            },
        } },
        { "WebCore::ShapeDetection::FaceDetectorOptions"_s, {
            {
                "uint16_t"_s,
                "maxDetectedFaces"_s
            },
            {
                "bool"_s,
                "fastMode"_s
            },
        } },
        { "WebCore::ShapeDetection::Landmark"_s, {
            {
                "Vector<WebCore::FloatPoint>"_s,
                "locations"_s
            },
            {
                "WebCore::ShapeDetection::LandmarkType"_s,
                "type"_s
            },
        } },
        { "WebCore::CaptureSourceError"_s, {
            {
                "String"_s,
                "errorMessage"_s
            },
            {
                "WebCore::MediaAccessDenialReason"_s,
                "denialReason"_s
            },
        } },
        { "WebCore::CookieStoreGetOptions"_s, {
            {
                "String"_s,
                "name"_s
            },
            {
                "String"_s,
                "url"_s
            },
        } },
        { "WebCore::Model"_s, {
            {
                "Ref<WebCore::SharedBuffer>"_s,
                "data()"_s
            },
            {
                "String"_s,
                "mimeType()"_s
            },
            {
                "URL"_s,
                "url()"_s
            },
        } },
        { "WebKit::WebEvent"_s, {
            {
                "WebKit::WebEventType"_s,
                "type()"_s
            },
            {
                "OptionSet<WebKit::WebEventModifier>"_s,
                "modifiers()"_s
            },
            {
                "WallTime"_s,
                "timestamp()"_s
            },
            {
                "WTF::UUID"_s,
                "authorizationToken()"_s
            },
        } },
        { "WebKit::WebKeyboardEvent"_s, {
            {
                "String"_s,
                "text()"_s
            },
#if !PLATFORM(GTK) && !USE(LIBWPE)
            {
                "String"_s,
                "unmodifiedText()"_s
            },
#endif
            {
                "String"_s,
                "key()"_s
            },
            {
                "String"_s,
                "code()"_s
            },
            {
                "String"_s,
                "keyIdentifier()"_s
            },
            {
                "int32_t"_s,
                "windowsVirtualKeyCode()"_s
            },
            {
                "int32_t"_s,
                "nativeVirtualKeyCode()"_s
            },
#if !PLATFORM(GTK) && !USE(LIBWPE)
            {
                "int32_t"_s,
                "macCharCode()"_s
            },
#endif
#if USE(APPKIT) || PLATFORM(IOS_FAMILY) || PLATFORM(GTK) || USE(LIBWPE)
            {
                "bool"_s,
                "handledByInputMethod()"_s
            },
#endif
#if PLATFORM(GTK) || USE(LIBWPE)
            {
                "std::optional<Vector<WebCore::CompositionUnderline>>"_s,
                "preeditUnderlines()"_s
            },
#endif
#if PLATFORM(GTK) || USE(LIBWPE)
            {
                "std::optional<WebKit::EditingRange>"_s,
                "preeditSelectionRange()"_s
            },
#endif
#if USE(APPKIT)
            {
                "Vector<WebCore::KeypressCommand>"_s,
                "commands()"_s
            },
#endif
#if !USE(APPKIT) && PLATFORM(GTK)
            {
                "Vector<String>"_s,
                "commands()"_s
            },
#endif
            {
                "bool"_s,
                "isAutoRepeat()"_s
            },
            {
                "bool"_s,
                "isKeypad()"_s
            },
#if !PLATFORM(GTK) && !USE(LIBWPE)
            {
                "bool"_s,
                "isSystemKey()"_s
            },
#endif
        } },
        { "WebKit::WebTouchEvent"_s, {
            {
                "Vector<WebKit::WebPlatformTouchPoint>"_s,
                "touchPoints()"_s
            },
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntPoint"_s,
                "position()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "isPotentialTap()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "isGesture()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "float"_s,
                "gestureScale()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "float"_s,
                "gestureRotation()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "canPreventNativeGestures()"_s
            },
#endif
        } },
        { "WebKit::WebPlatformTouchPoint"_s, {
#if PLATFORM(IOS_FAMILY)
            {
                "unsigned"_s,
                "identifier()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntPoint"_s,
                "location()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebKit::WebPlatformTouchPoint::State"_s,
                "phase()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(IOS_TOUCH_EVENTS)
            {
                "double"_s,
                "radiusX()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(IOS_TOUCH_EVENTS)
            {
                "double"_s,
                "radiusY()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(IOS_TOUCH_EVENTS)
            {
                "double"_s,
                "rotationAngle()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(IOS_TOUCH_EVENTS)
            {
                "double"_s,
                "force()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(IOS_TOUCH_EVENTS)
            {
                "double"_s,
                "altitudeAngle()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(IOS_TOUCH_EVENTS)
            {
                "double"_s,
                "azimuthAngle()"_s
            },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(IOS_TOUCH_EVENTS)
            {
                "WebKit::WebPlatformTouchPoint::TouchType"_s,
                "touchType()"_s
            },
#endif
#if !PLATFORM(IOS_FAMILY)
            {
                "uint32_t"_s,
                "id()"_s
            },
#endif
#if !PLATFORM(IOS_FAMILY)
            {
                "WebKit::WebPlatformTouchPoint::State"_s,
                "state()"_s
            },
#endif
#if !PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntPoint"_s,
                "screenPosition()"_s
            },
#endif
#if !PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntPoint"_s,
                "position()"_s
            },
#endif
#if !PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntSize"_s,
                "radius()"_s
            },
#endif
#if !PLATFORM(IOS_FAMILY)
            {
                "float"_s,
                "rotationAngle()"_s
            },
#endif
#if !PLATFORM(IOS_FAMILY)
            {
                "float"_s,
                "force()"_s
            },
#endif
        } },
        { "WebKit::WebMouseEvent"_s, {
            {
                "WebKit::WebMouseEventButton"_s,
                "button()"_s
            },
            {
                "unsigned short"_s,
                "buttons()"_s
            },
            {
                "WebCore::IntPoint"_s,
                "position()"_s
            },
            {
                "WebCore::IntPoint"_s,
                "globalPosition()"_s
            },
            {
                "float"_s,
                "deltaX()"_s
            },
            {
                "float"_s,
                "deltaY()"_s
            },
            {
                "float"_s,
                "deltaZ()"_s
            },
            {
                "int32_t"_s,
                "clickCount()"_s
            },
            {
                "double"_s,
                "force()"_s
            },
            {
                "WebKit::WebMouseEventSyntheticClickType"_s,
                "syntheticClickType()"_s
            },
#if PLATFORM(MAC)
            {
                "int32_t"_s,
                "eventNumber()"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "int32_t"_s,
                "menuTypeForEvent()"_s
            },
#endif
#if !PLATFORM(MAC) && PLATFORM(GTK)
            {
                "WebCore::PlatformMouseEvent::IsTouch"_s,
                "isTouchEvent()"_s
            },
#endif
#if !PLATFORM(MAC)
            {
                "WebCore::PointerID"_s,
                "pointerId()"_s
            },
#endif
#if !PLATFORM(MAC)
            {
                "String"_s,
                "pointerType()"_s
            },
#endif
            {
                "WebKit::GestureWasCancelled"_s,
                "gestureWasCancelled()"_s
            },
        } },
        { "WebKit::WebGestureEvent"_s, {
            {
                "WebCore::IntPoint"_s,
                "position()"_s
            },
            {
                "float"_s,
                "gestureScale()"_s
            },
            {
                "float"_s,
                "gestureRotation()"_s
            },
        } },
        { "WebKit::WebWheelEvent"_s, {
            {
                "WebCore::IntPoint"_s,
                "position()"_s
            },
            {
                "WebCore::IntPoint"_s,
                "globalPosition()"_s
            },
            {
                "WebCore::FloatSize"_s,
                "delta()"_s
            },
            {
                "WebCore::FloatSize"_s,
                "wheelTicks()"_s
            },
            {
                "WebKit::WebWheelEvent::Granularity"_s,
                "granularity()"_s
            },
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "directionInvertedFromDevice()"_s
            },
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK) || USE(LIBWPE)
            {
                "WebKit::WebWheelEvent::Phase"_s,
                "phase()"_s
            },
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK) || USE(LIBWPE)
            {
                "WebKit::WebWheelEvent::Phase"_s,
                "momentumPhase()"_s
            },
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK) || USE(LIBWPE)
            {
                "bool"_s,
                "hasPreciseScrollingDeltas()"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "uint32_t"_s,
                "scrollCount()"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "WebCore::FloatSize"_s,
                "unacceleratedScrollingDelta()"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "WallTime"_s,
                "ioHIDEventTimestamp()"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "std::optional<WebCore::FloatSize>"_s,
                "rawPlatformDelta()"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "WebKit::WebWheelEvent::MomentumEndType"_s,
                "momentumEndType()"_s
            },
#endif
        } },
        { "WebKit::WebHitTestResultData"_s, {
            {
                "String"_s,
                "absoluteImageURL"_s
            },
            {
                "String"_s,
                "absolutePDFURL"_s
            },
            {
                "String"_s,
                "absoluteLinkURL"_s
            },
            {
                "String"_s,
                "absoluteMediaURL"_s
            },
            {
                "String"_s,
                "linkLabel"_s
            },
            {
                "String"_s,
                "linkTitle"_s
            },
            {
                "String"_s,
                "linkSuggestedFilename"_s
            },
            {
                "bool"_s,
                "isContentEditable"_s
            },
            {
                "WebCore::IntRect"_s,
                "elementBoundingBox"_s
            },
            {
                "WebKit::WebHitTestResultData::IsScrollbar"_s,
                "isScrollbar"_s
            },
            {
                "bool"_s,
                "isSelected"_s
            },
            {
                "bool"_s,
                "isTextNode"_s
            },
            {
                "bool"_s,
                "isOverTextInsideFormControlElement"_s
            },
            {
                "bool"_s,
                "isDownloadableMedia"_s
            },
            {
                "String"_s,
                "lookupText"_s
            },
            {
                "String"_s,
                "toolTipText"_s
            },
            {
                "String"_s,
                "imageText"_s
            },
            {
                "std::optional<WebKit::SharedMemoryHandle>"_s,
                "getImageSharedMemoryHandle()"_s
            },
            {
                "RefPtr<WebKit::ShareableBitmap>"_s,
                "imageBitmap"_s
            },
            {
                "String"_s,
                "sourceImageMIMEType"_s
            },
#if PLATFORM(MAC)
            {
                "WebKit::WebHitTestResultPlatformData"_s,
                "platformData"_s
            },
#endif
            {
                "WebCore::DictionaryPopupInfo"_s,
                "dictionaryPopupInfo"_s
            },
            {
                "RefPtr<WebCore::TextIndicator>"_s,
                "linkTextIndicator"_s
            },
        } },
        { "WebKit::WebPageCreationParameters"_s, {
            {
                "WebCore::IntSize"_s,
                "viewSize"_s
            },
            {
                "OptionSet<WebCore::ActivityState>"_s,
                "activityState"_s
            },
            {
                "WebKit::WebPreferencesStore"_s,
                "store"_s
            },
            {
                "WebKit::DrawingAreaType"_s,
                "drawingAreaType"_s
            },
            {
                "WebKit::DrawingAreaIdentifier"_s,
                "drawingAreaIdentifier"_s
            },
            {
                "WebKit::WebPageProxyIdentifier"_s,
                "webPageProxyIdentifier"_s
            },
            {
                "WebKit::WebPageGroupData"_s,
                "pageGroupData"_s
            },
            {
                "bool"_s,
                "isEditable"_s
            },
            {
                "WebCore::Color"_s,
                "underlayColor"_s
            },
            {
                "bool"_s,
                "useFixedLayout"_s
            },
            {
                "WebCore::IntSize"_s,
                "fixedLayoutSize"_s
            },
            {
                "WebCore::FloatSize"_s,
                "defaultUnobscuredSize"_s
            },
            {
                "WebCore::FloatSize"_s,
                "minimumUnobscuredSize"_s
            },
            {
                "WebCore::FloatSize"_s,
                "maximumUnobscuredSize"_s
            },
            {
                "std::optional<WebCore::FloatRect>"_s,
                "viewExposedRect"_s
            },
            {
                "bool"_s,
                "alwaysShowsHorizontalScroller"_s
            },
            {
                "bool"_s,
                "alwaysShowsVerticalScroller"_s
            },
            {
                "bool"_s,
                "suppressScrollbarAnimations"_s
            },
            {
                "WebCore::Pagination::Mode"_s,
                "paginationMode"_s
            },
            {
                "bool"_s,
                "paginationBehavesLikeColumns"_s
            },
            {
                "double"_s,
                "pageLength"_s
            },
            {
                "double"_s,
                "gapBetweenPages"_s
            },
            {
                "String"_s,
                "userAgent"_s
            },
            {
                "bool"_s,
                "itemStatesWereRestoredByAPIRequest"_s
            },
            {
                "Vector<WebKit::BackForwardListItemState>"_s,
                "itemStates"_s
            },
            {
                "uint64_t"_s,
                "visitedLinkTableID"_s
            },
            {
                "bool"_s,
                "canRunBeforeUnloadConfirmPanel"_s
            },
            {
                "bool"_s,
                "canRunModal"_s
            },
            {
                "float"_s,
                "deviceScaleFactor"_s
            },
            {
                "float"_s,
                "viewScaleFactor"_s
            },
            {
                "double"_s,
                "textZoomFactor"_s
            },
            {
                "double"_s,
                "pageZoomFactor"_s
            },
            {
                "float"_s,
                "topContentInset"_s
            },
            {
                "float"_s,
                "mediaVolume"_s
            },
            {
                "WebCore::MediaProducerMutedStateFlags"_s,
                "muted"_s
            },
            {
                "bool"_s,
                "openedByDOM"_s
            },
            {
                "bool"_s,
                "mayStartMediaWhenInWindow"_s
            },
            {
                "bool"_s,
                "mediaPlaybackIsSuspended"_s
            },
            {
                "WebCore::IntSize"_s,
                "minimumSizeForAutoLayout"_s
            },
            {
                "WebCore::IntSize"_s,
                "sizeToContentAutoSizeMaximumSize"_s
            },
            {
                "bool"_s,
                "autoSizingShouldExpandToViewHeight"_s
            },
            {
                "std::optional<WebCore::FloatSize>"_s,
                "viewportSizeForCSSViewportUnits"_s
            },
            {
                "WebCore::ScrollPinningBehavior"_s,
                "scrollPinningBehavior"_s
            },
            {
                "std::optional<uint32_t>"_s,
                "scrollbarOverlayStyle"_s
            },
            {
                "bool"_s,
                "backgroundExtendsBeyondPage"_s
            },
            {
                "WebKit::LayerHostingMode"_s,
                "layerHostingMode"_s
            },
            {
                "bool"_s,
                "hasResourceLoadClient"_s
            },
            {
                "Vector<String>"_s,
                "mimeTypesWithCustomContentProviders"_s
            },
            {
                "bool"_s,
                "controlledByAutomation"_s
            },
            {
                "bool"_s,
                "isProcessSwap"_s
            },
            {
                "bool"_s,
                "useDarkAppearance"_s
            },
            {
                "bool"_s,
                "useElevatedUserInterfaceLevel"_s
            },
#if PLATFORM(MAC)
            {
                "std::optional<WebCore::DestinationColorSpace>"_s,
                "colorSpace"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "bool"_s,
                "useSystemAppearance"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "bool"_s,
                "useFormSemanticContext"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "int"_s,
                "headerBannerHeight"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "int"_s,
                "footerBannerHeight"_s
            },
#endif
#if ENABLE(META_VIEWPORT)
            {
                "bool"_s,
                "ignoresViewportScaleLimits"_s
            },
#endif
#if ENABLE(META_VIEWPORT)
            {
                "WebCore::FloatSize"_s,
                "viewportConfigurationViewLayoutSize"_s
            },
#endif
#if ENABLE(META_VIEWPORT)
            {
                "double"_s,
                "viewportConfigurationLayoutSizeScaleFactor"_s
            },
#endif
#if ENABLE(META_VIEWPORT)
            {
                "double"_s,
                "viewportConfigurationMinimumEffectiveDeviceWidth"_s
            },
#endif
#if ENABLE(META_VIEWPORT)
            {
                "WebCore::FloatSize"_s,
                "viewportConfigurationViewSize"_s
            },
#endif
#if ENABLE(META_VIEWPORT)
            {
                "std::optional<WebCore::ViewportArguments>"_s,
                "overrideViewportArguments"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::FloatSize"_s,
                "screenSize"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::FloatSize"_s,
                "availableScreenSize"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::FloatSize"_s,
                "overrideScreenSize"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "float"_s,
                "textAutosizingWidth"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::IntDegrees"_s,
                "deviceOrientation"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "keyboardIsAttached"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "canShowWhileLocked"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "isCapturingScreen"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::Color"_s,
                "insertionPointColor"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "smartInsertDeleteEnabled"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "Vector<String>"_s,
                "additionalSupportedImageTypes"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "Vector<WebKit::SandboxExtension::Handle>"_s,
                "gpuIOKitExtensionHandles"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "Vector<WebKit::SandboxExtension::Handle>"_s,
                "gpuMachExtensionHandles"_s
            },
#endif
#if HAVE(STATIC_FONT_REGISTRY)
            {
                "Vector<WebKit::SandboxExtension::Handle>"_s,
                "fontMachExtensionHandles"_s
            },
#endif
#if HAVE(APP_ACCENT_COLORS)
            {
                "WebCore::Color"_s,
                "accentColor"_s
            },
#endif
#if USE(WPE_RENDERER)
            {
                "UnixFileDescriptor"_s,
                "hostFileDescriptor"_s
            },
#endif
#if USE(GRAPHICS_LAYER_TEXTURE_MAPPER) || USE(GRAPHICS_LAYER_WC)
            {
                "uint64_t"_s,
                "nativeWindowHandle"_s
            },
#endif
#if USE(GRAPHICS_LAYER_WC)
            {
                "bool"_s,
                "usesOffscreenRendering"_s
            },
#endif
            {
                "bool"_s,
                "shouldScaleViewToFitDocument"_s
            },
            {
                "WebCore::UserInterfaceLayoutDirection"_s,
                "userInterfaceLayoutDirection"_s
            },
            {
                "OptionSet<WebCore::LayoutMilestone>"_s,
                "observedLayoutMilestones"_s
            },
            {
                "String"_s,
                "overrideContentSecurityPolicy"_s
            },
            {
                "std::optional<double>"_s,
                "cpuLimit"_s
            },
            {
                "HashMap<String, WebKit::WebURLSchemeHandlerIdentifier>"_s,
                "urlSchemeHandlers"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesWithLegacyCustomProtocolHandlers"_s
            },
#if ENABLE(APPLICATION_MANIFEST)
            {
                "std::optional<WebCore::ApplicationManifest>"_s,
                "applicationManifest"_s
            },
#endif
            {
                "bool"_s,
                "needsFontAttributes"_s
            },
            {
                "bool"_s,
                "iceCandidateFilteringEnabled"_s
            },
            {
                "bool"_s,
                "enumeratingAllNetworkInterfacesEnabled"_s
            },
            {
                "WebKit::UserContentControllerParameters"_s,
                "userContentControllerParameters"_s
            },
#if ENABLE(WK_WEB_EXTENSIONS)
            {
                "std::optional<WebKit::WebExtensionControllerParameters>"_s,
                "webExtensionControllerParameters"_s
            },
#endif
            {
                "std::optional<WebCore::Color>"_s,
                "backgroundColor"_s
            },
            {
                "std::optional<WebCore::PageIdentifier>"_s,
                "oldPageID"_s
            },
            {
                "String"_s,
                "overriddenMediaType"_s
            },
            {
                "Vector<String>"_s,
                "corsDisablingPatterns"_s
            },
            {
                "HashSet<String>"_s,
                "maskedURLSchemes"_s
            },
            {
                "bool"_s,
                "userScriptsShouldWaitUntilNotification"_s
            },
            {
                "bool"_s,
                "loadsSubresources"_s
            },
            {
                "std::optional<MemoryCompactLookupOnlyRobinHoodHashSet<String>>"_s,
                "allowedNetworkHosts"_s
            },
            {
                "bool"_s,
                "crossOriginAccessControlCheckEnabled"_s
            },
            {
                "String"_s,
                "processDisplayName"_s
            },
            {
                "bool"_s,
                "shouldCaptureAudioInUIProcess"_s
            },
            {
                "bool"_s,
                "shouldCaptureAudioInGPUProcess"_s
            },
            {
                "bool"_s,
                "shouldCaptureVideoInUIProcess"_s
            },
            {
                "bool"_s,
                "shouldCaptureVideoInGPUProcess"_s
            },
            {
                "bool"_s,
                "shouldCaptureDisplayInUIProcess"_s
            },
            {
                "bool"_s,
                "shouldCaptureDisplayInGPUProcess"_s
            },
            {
                "bool"_s,
                "shouldRenderCanvasInGPUProcess"_s
            },
            {
                "bool"_s,
                "shouldRenderDOMInGPUProcess"_s
            },
            {
                "bool"_s,
                "shouldPlayMediaInGPUProcess"_s
            },
#if ENABLE(WEBGL)
            {
                "bool"_s,
                "shouldRenderWebGLInGPUProcess"_s
            },
#endif
            {
                "bool"_s,
                "shouldEnableVP8Decoder"_s
            },
            {
                "bool"_s,
                "shouldEnableVP9Decoder"_s
            },
            {
                "bool"_s,
                "shouldEnableVP9SWDecoder"_s
            },
#if ENABLE(APP_BOUND_DOMAINS)
            {
                "bool"_s,
                "limitsNavigationsToAppBoundDomains"_s
            },
#endif
            {
                "bool"_s,
                "lastNavigationWasAppInitiated"_s
            },
            {
                "bool"_s,
                "canUseCredentialStorage"_s
            },
            {
                "WebCore::ShouldRelaxThirdPartyCookieBlocking"_s,
                "shouldRelaxThirdPartyCookieBlocking"_s
            },
            {
                "bool"_s,
                "httpsUpgradeEnabled"_s
            },
#if PLATFORM(IOS) || PLATFORM(VISION)
            {
                "bool"_s,
                "allowsDeprecatedSynchronousXMLHttpRequestDuringUnload"_s
            },
#endif
#if ENABLE(APP_HIGHLIGHTS)
            {
                "WebCore::HighlightVisibility"_s,
                "appHighlightsVisible"_s
            },
#endif
#if HAVE(TOUCH_BAR)
            {
                "bool"_s,
                "requiresUserActionForEditingControlsManager"_s
            },
#endif
            {
                "bool"_s,
                "hasResizableWindows"_s
            },
            {
                "WebCore::ContentSecurityPolicyModeForExtension"_s,
                "contentSecurityPolicyModeForExtension"_s
            },
            {
                "std::optional<WebKit::FrameTreeCreationParameters>"_s,
                "subframeProcessFrameTreeCreationParameters"_s
            },
            {
                "std::optional<WebCore::FrameIdentifier>"_s,
                "openerFrameIdentifier"_s
            },
            {
                "std::optional<WebCore::FrameIdentifier>"_s,
                "mainFrameIdentifier"_s
            },
#if ENABLE(ADVANCED_PRIVACY_PROTECTIONS)
            {
                "Vector<WebCore::LinkDecorationFilteringData>"_s,
                "linkDecorationFilteringData"_s
            },
#endif
#if ENABLE(ADVANCED_PRIVACY_PROTECTIONS)
            {
                "Vector<WebCore::LinkDecorationFilteringData>"_s,
                "allowedQueryParametersForAdvancedPrivacyProtections"_s
            },
#endif
#if HAVE(MACH_BOOTSTRAP_EXTENSION)
            {
                "WebKit::SandboxExtension::Handle"_s,
                "machBootstrapHandle"_s
            },
#endif
        } },
        { "WebKit::WebPopupItem"_s, {
            {
                "WebKit::WebPopupItem::Type"_s,
                "m_type"_s
            },
            {
                "String"_s,
                "m_text"_s
            },
            {
                "WebCore::TextDirection"_s,
                "m_textDirection"_s
            },
            {
                "bool"_s,
                "m_hasTextDirectionOverride"_s
            },
            {
                "String"_s,
                "m_toolTip"_s
            },
            {
                "String"_s,
                "m_accessibilityText"_s
            },
            {
                "bool"_s,
                "m_isEnabled"_s
            },
            {
                "bool"_s,
                "m_isLabel"_s
            },
            {
                "bool"_s,
                "m_isSelected"_s
            },
        } },
        { "WebKit::WebProcessCreationParameters"_s, {
            {
                "WebKit::AuxiliaryProcessCreationParameters"_s,
                "auxiliaryProcessParameters"_s
            },
            {
                "String"_s,
                "injectedBundlePath"_s
            },
            {
                "WebKit::SandboxExtension::Handle"_s,
                "injectedBundlePathExtensionHandle"_s
            },
            {
                "Vector<WebKit::SandboxExtension::Handle>"_s,
                "additionalSandboxExtensionHandles"_s
            },
            {
                "WebKit::UserData"_s,
                "initializationUserData"_s
            },
#if PLATFORM(COCOA) && ENABLE(REMOTE_INSPECTOR)
            {
                "Vector<WebKit::SandboxExtension::Handle>"_s,
                "enableRemoteWebInspectorExtensionHandles"_s
            },
#endif
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsEmptyDocument"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsSecure"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsBypassingContentSecurityPolicy"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesForWhichDomainRelaxationIsForbidden"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsLocal"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsNoAccess"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsDisplayIsolated"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsCORSEnabled"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsAlwaysRevalidated"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsCachePartitioned"_s
            },
            {
                "Vector<String>"_s,
                "urlSchemesRegisteredAsCanDisplayOnlyIfCanRequest"_s
            },
            {
                "Vector<String>"_s,
                "fontAllowList"_s
            },
            {
                "Vector<String>"_s,
                "overrideLanguages"_s
            },
#if USE(GSTREAMER)
            {
                "Vector<String>"_s,
                "gstreamerOptions"_s
            },
#endif
            {
                "WebKit::CacheModel"_s,
                "cacheModel"_s
            },
            {
                "double"_s,
                "defaultRequestTimeoutInterval"_s
            },
            {
                "unsigned"_s,
                "backForwardCacheCapacity"_s
            },
            {
                "bool"_s,
                "shouldAlwaysUseComplexTextCodePath"_s
            },
            {
                "bool"_s,
                "shouldEnableMemoryPressureReliefLogging"_s
            },
            {
                "bool"_s,
                "shouldSuppressMemoryPressureHandler"_s
            },
            {
                "bool"_s,
                "disableFontSubpixelAntialiasingForTesting"_s
            },
            {
                "bool"_s,
                "fullKeyboardAccessEnabled"_s
            },
#if HAVE(MOUSE_DEVICE_OBSERVATION)
            {
                "bool"_s,
                "hasMouseDevice"_s
            },
#endif
#if HAVE(STYLUS_DEVICE_OBSERVATION)
            {
                "bool"_s,
                "hasStylusDevice"_s
            },
#endif
            {
                "bool"_s,
                "memoryCacheDisabled"_s
            },
            {
                "bool"_s,
                "attrStyleEnabled"_s
            },
            {
                "bool"_s,
                "shouldThrowExceptionForGlobalConstantRedeclaration"_s
            },
            {
                "WebCore::CrossOriginMode"_s,
                "crossOriginMode"_s
            },
            {
                "bool"_s,
                "isLockdownModeEnabled"_s
            },
#if ENABLE(SERVICE_CONTROLS)
            {
                "bool"_s,
                "hasImageServices"_s
            },
#endif
#if ENABLE(SERVICE_CONTROLS)
            {
                "bool"_s,
                "hasSelectionServices"_s
            },
#endif
#if ENABLE(SERVICE_CONTROLS)
            {
                "bool"_s,
                "hasRichContentServices"_s
            },
#endif
            {
                "WebKit::TextCheckerState"_s,
                "textCheckerState"_s
            },
#if PLATFORM(COCOA)
            {
                "String"_s,
                "uiProcessBundleIdentifier"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "int"_s,
                "latencyQOS"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "int"_s,
                "throughputQOS"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "String"_s,
                "presentingApplicationBundleIdentifier"_s
            },
#endif
            {
                "ProcessID"_s,
                "presentingApplicationPID"_s
            },
#if PLATFORM(COCOA)
            {
                "WTF::MachSendRight"_s,
                "acceleratedCompositingPort"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "String"_s,
                "uiProcessBundleResourcePath"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "WebKit::SandboxExtension::Handle"_s,
                "uiProcessBundleResourcePathExtensionHandle"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "shouldEnableJIT"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "shouldEnableFTLJIT"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "accessibilityEnhancedUserInterfaceEnabled"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "RefPtr<API::Data>"_s,
                "bundleParameterData"_s
            },
#endif
#if ENABLE(NOTIFICATIONS)
            {
                "HashMap<String, bool>"_s,
                "notificationPermissions"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "RetainPtr<CFDataRef>"_s,
                "networkATSContext"_s
            },
#endif
#if PLATFORM(WAYLAND)
            {
                "String"_s,
                "waylandCompositorDisplayName"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "Vector<String>"_s,
                "mediaMIMETypes"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "WebCore::ScreenProperties"_s,
                "screenProperties"_s
            },
#endif
#if ENABLE(TRACKING_PREVENTION) && !RELEASE_LOG_DISABLED
            {
                "bool"_s,
                "shouldLogUserInteraction"_s
            },
#endif
#if PLATFORM(MAC)
            {
                "bool"_s,
                "useOverlayScrollbars"_s
            },
#endif
#if USE(WPE_RENDERER)
            {
                "bool"_s,
                "isServiceWorkerProcess"_s
            },
#endif
#if USE(WPE_RENDERER)
            {
                "UnixFileDescriptor"_s,
                "hostClientFileDescriptor"_s
            },
#endif
#if USE(WPE_RENDERER)
            {
                "CString"_s,
                "implementationLibraryName"_s
            },
#endif
            {
                "std::optional<WebKit::WebProcessDataStoreParameters>"_s,
                "websiteDataStoreParameters"_s
            },
#if PLATFORM(IOS) || PLATFORM(VISION)
            {
                "Vector<WebKit::SandboxExtension::Handle>"_s,
                "compilerServiceExtensionHandles"_s
            },
#endif
            {
                "std::optional<WebKit::SandboxExtension::Handle>"_s,
                "mobileGestaltExtensionHandle"_s
            },
            {
                "std::optional<WebKit::SandboxExtension::Handle>"_s,
                "launchServicesExtensionHandle"_s
            },
#if PLATFORM(MAC) && HAVE(VIDEO_RESTRICTED_DECODING)
            {
                "WebKit::SandboxExtension::Handle"_s,
                "trustdExtensionHandle"_s
            },
#endif
#if HAVE(VIDEO_RESTRICTED_DECODING)
            {
                "bool"_s,
                "enableDecodingHEIC"_s
            },
#endif
#if HAVE(VIDEO_RESTRICTED_DECODING)
            {
                "bool"_s,
                "enableDecodingAVIF"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "Vector<WebKit::SandboxExtension::Handle>"_s,
                "dynamicIOKitExtensionHandles"_s
            },
#endif
#if PLATFORM(VISION)
            {
                "Vector<WebKit::SandboxExtension::Handle>"_s,
                "metalCacheDirectoryExtensionHandles"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "systemHasBattery"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "systemHasAC"_s
            },
#endif
#if PLATFORM(COCOA)
            {
                "bool"_s,
                "strictSecureDecodingForAllObjCEnabled"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "PAL::UserInterfaceIdiom"_s,
                "currentUserInterfaceIdiom"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "supportsPictureInPicture"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::RenderThemeIOS::CSSValueToSystemColorMap"_s,
                "cssValueToSystemColorMap"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "WebCore::Color"_s,
                "focusRingColor"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "String"_s,
                "localizedDeviceModel"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "String"_s,
                "contentSizeCategory"_s
            },
#endif
#if USE(GBM)
            {
                "String"_s,
                "renderDeviceFile"_s
            },
#endif
#if PLATFORM(GTK)
            {
                "OptionSet<WebKit::DMABufRendererBufferMode>"_s,
                "dmaBufRendererBufferMode"_s
            },
#endif
#if PLATFORM(GTK)
            {
                "bool"_s,
                "useSystemAppearanceForScrollbars"_s
            },
#endif
#if PLATFORM(GTK)
            {
                "WebKit::GtkSettingsState"_s,
                "gtkSettings"_s
            },
#endif
#if HAVE(CATALYST_USER_INTERFACE_IDIOM_AND_SCALE_FACTOR)
            {
                "std::pair<int64_t, double>"_s,
                "overrideUserInterfaceIdiomAndScale"_s
            },
#endif
#if HAVE(IOSURFACE)
            {
                "WebCore::IntSize"_s,
                "maximumIOSurfaceSize"_s
            },
#endif
#if HAVE(IOSURFACE)
            {
                "size_t"_s,
                "bytesPerRowIOSurfaceAlignment"_s
            },
#endif
            {
                "WebKit::AccessibilityPreferences"_s,
                "accessibilityPreferences"_s
            },
#if PLATFORM(IOS_FAMILY)
            {
                "bool"_s,
                "applicationAccessibilityEnabled"_s
            },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
            {
                "std::optional<WTF::MemoryPressureHandler::Configuration>"_s,
                "memoryPressureHandlerConfiguration"_s
            },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
            {
                "bool"_s,
                "disableFontHintingForTesting"_s
            },
#endif
#if USE(GLIB)
            {
                "String"_s,
                "applicationID"_s
            },
#endif
#if USE(GLIB)
            {
                "String"_s,
                "applicationName"_s
            },
#endif
#if USE(GLIB) && ENABLE(REMOTE_INSPECTOR)
            {
                "CString"_s,
                "inspectorServerAddress"_s
            },
#endif
#if USE(ATSPI)
            {
                "String"_s,
                "accessibilityBusAddress"_s
            },
#endif
            {
                "String"_s,
                "timeZoneOverride"_s
            },
        } },
        { "WebKit::WebProcessDataStoreParameters"_s, {
            {
                "PAL::SessionID"_s,
                "sessionID"_s
            },
            {
                "String"_s,
                "applicationCacheDirectory"_s
            },
            {
                "WebKit::SandboxExtension::Handle"_s,
                "applicationCacheDirectoryExtensionHandle"_s
            },
            {
                "String"_s,
                "applicationCacheFlatFileSubdirectoryName"_s
            },
            {
                "String"_s,
                "mediaCacheDirectory"_s
            },
            {
                "WebKit::SandboxExtension::Handle"_s,
                "mediaCacheDirectoryExtensionHandle"_s
            },
            {
                "String"_s,
                "mediaKeyStorageDirectory"_s
            },
            {
                "WebKit::SandboxExtension::Handle"_s,
                "mediaKeyStorageDirectoryExtensionHandle"_s
            },
            {
                "String"_s,
                "javaScriptConfigurationDirectory"_s
            },
            {
                "WebKit::SandboxExtension::Handle"_s,
                "javaScriptConfigurationDirectoryExtensionHandle"_s
            },
#if ENABLE(TRACKING_PREVENTION)
            {
                "WebCore::ThirdPartyCookieBlockingMode"_s,
                "thirdPartyCookieBlockingMode"_s
            },
#endif
#if ENABLE(TRACKING_PREVENTION)
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "domainsWithUserInteraction"_s
            },
#endif
#if ENABLE(TRACKING_PREVENTION)
            {
                "HashMap<WebCore::RegistrableDomain, WebCore::RegistrableDomain>"_s,
                "domainsWithStorageAccessQuirk"_s
            },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
            {
                "String"_s,
                "modelElementCacheDirectory"_s
            },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
            {
                "WebKit::SandboxExtension::Handle"_s,
                "modelElementCacheDirectoryExtensionHandle"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "std::optional<WebKit::SandboxExtension::Handle>"_s,
                "cookieStorageDirectoryExtensionHandle"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "std::optional<WebKit::SandboxExtension::Handle>"_s,
                "containerCachesDirectoryExtensionHandle"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "std::optional<WebKit::SandboxExtension::Handle>"_s,
                "containerTemporaryDirectoryExtensionHandle"_s
            },
#endif
            {
                "bool"_s,
                "trackingPreventionEnabled"_s
            },
        } },
        { "WebKit::WebPushD::WebPushDaemonConnectionConfiguration"_s, {
            {
                "bool"_s,
                "useMockBundlesForTesting"_s
            },
            {
                "std::optional<Vector<uint8_t>>"_s,
                "hostAppAuditTokenData"_s
            },
            {
                "String"_s,
                "pushPartitionString"_s
            },
            {
                "std::optional<WTF::UUID>"_s,
                "dataStoreIdentifier"_s
            },
        } },
        { "WebKit::WebPushMessage"_s, {
            {
                "std::optional<Vector<uint8_t>>"_s,
                "pushData"_s
            },
            {
                "String"_s,
                "pushPartitionString"_s
            },
            {
                "URL"_s,
                "registrationURL"_s
            },
        } },
        { "WebKit::WebsiteDataStoreParameters"_s, {
            {
                "Vector<uint8_t>"_s,
                "uiProcessCookieStorageIdentifier"_s
            },
            {
                "WebKit::SandboxExtension::Handle"_s,
                "cookieStoragePathExtensionHandle"_s
            },
            {
                "WebKit::NetworkSessionCreationParameters"_s,
                "networkSessionParameters"_s
            },
#if PLATFORM(IOS_FAMILY)
            {
                "std::optional<WebKit::SandboxExtension::Handle>"_s,
                "cookieStorageDirectoryExtensionHandle"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "std::optional<WebKit::SandboxExtension::Handle>"_s,
                "containerCachesDirectoryExtensionHandle"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "std::optional<WebKit::SandboxExtension::Handle>"_s,
                "parentBundleDirectoryExtensionHandle"_s
            },
#endif
#if PLATFORM(IOS_FAMILY)
            {
                "std::optional<WebKit::SandboxExtension::Handle>"_s,
                "tempDirectoryExtensionHandle"_s
            },
#endif
        } },
        { "WebKit::WebsitePoliciesData"_s, {
            {
                "WebCore::ContentExtensionEnablement"_s,
                "contentExtensionEnablement"_s
            },
            {
                "HashMap<WTF::String, Vector<WTF::String>>"_s,
                "activeContentRuleListActionPatterns"_s
            },
            {
                "OptionSet<WebKit::WebsiteAutoplayQuirk>"_s,
                "allowedAutoplayQuirks"_s
            },
            {
                "WebKit::WebsiteAutoplayPolicy"_s,
                "autoplayPolicy"_s
            },
#if ENABLE(DEVICE_ORIENTATION)
            {
                "WebCore::DeviceOrientationOrMotionPermissionState"_s,
                "deviceOrientationAndMotionAccessState"_s
            },
#endif
            {
                "Vector<WebCore::CustomHeaderFields>"_s,
                "customHeaderFields"_s
            },
            {
                "WebKit::WebsitePopUpPolicy"_s,
                "popUpPolicy"_s
            },
            {
                "String"_s,
                "customUserAgent"_s
            },
            {
                "String"_s,
                "customUserAgentAsSiteSpecificQuirks"_s
            },
            {
                "String"_s,
                "customNavigatorPlatform"_s
            },
            {
                "WebKit::WebsiteMetaViewportPolicy"_s,
                "metaViewportPolicy"_s
            },
            {
                "WebKit::WebsiteMediaSourcePolicy"_s,
                "mediaSourcePolicy"_s
            },
            {
                "WebKit::WebsiteSimulatedMouseEventsDispatchPolicy"_s,
                "simulatedMouseEventsDispatchPolicy"_s
            },
            {
                "WebKit::WebsiteLegacyOverflowScrollingTouchPolicy"_s,
                "legacyOverflowScrollingTouchPolicy"_s
            },
            {
                "bool"_s,
                "allowContentChangeObserverQuirk"_s
            },
            {
                "WebCore::AllowsContentJavaScript"_s,
                "allowsContentJavaScript"_s
            },
            {
                "WebCore::MouseEventPolicy"_s,
                "mouseEventPolicy"_s
            },
            {
                "WebCore::ModalContainerObservationPolicy"_s,
                "modalContainerObservationPolicy"_s
            },
            {
                "WebCore::ColorSchemePreference"_s,
                "colorSchemePreference"_s
            },
            {
                "OptionSet<WebCore::AdvancedPrivacyProtections>"_s,
                "advancedPrivacyProtections"_s
            },
            {
                "bool"_s,
                "idempotentModeAutosizingOnlyHonorsPercentages"_s
            },
            {
                "bool"_s,
                "allowPrivacyProxy"_s
            },
        } },
        { "API::Data"_s, {
            {
                "IPC::DataReference"_s,
                "dataReference()"_s
            },
        } },
        { "API::Error"_s, {
            {
                "WebCore::ResourceError"_s,
                "platformError()"_s
            },
        } },
        { "API::FrameHandle"_s, {
            {
                "WebCore::FrameIdentifier"_s,
                "frameID()"_s
            },
            {
                "bool"_s,
                "isAutoconverting()"_s
            },
        } },
        { "API::Size"_s, {
            {
                "double"_s,
                "size().width"_s
            },
            {
                "double"_s,
                "size().height"_s
            },
        } },
        { "API::Point"_s, {
            {
                "double"_s,
                "point().x"_s
            },
            {
                "double"_s,
                "point().y"_s
            },
        } },
        { "API::Rect"_s, {
            {
                "double"_s,
                "rect().origin.x"_s
            },
            {
                "double"_s,
                "rect().origin.y"_s
            },
            {
                "double"_s,
                "rect().size.width"_s
            },
            {
                "double"_s,
                "rect().size.height"_s
            },
        } },
        { "API::PageHandle"_s, {
            {
                "WebKit::WebPageProxyIdentifier"_s,
                "pageProxyID()"_s
            },
            {
                "WebCore::PageIdentifier"_s,
                "webPageID()"_s
            },
            {
                "bool"_s,
                "isAutoconverting()"_s
            },
        } },
        { "API::URL"_s, {
            {
                "WTF::String"_s,
                "string()"_s
            },
        } },
        { "API::URLRequest"_s, {
            {
                "WebCore::ResourceRequest"_s,
                "resourceRequest()"_s
            },
        } },
        { "API::URLResponse"_s, {
            {
                "WebCore::ResourceResponse"_s,
                "resourceResponse()"_s
            },
        } },
        { "WebKit::WebIDBResult"_s, {
            {
                "WebCore::IDBResultData"_s,
                "m_resultData"_s
            },
            {
                "Vector<WebKit::SandboxExtension::Handle>"_s,
                "m_handles"_s
            },
        } },
        { "WebKit::GamepadData"_s, {
            {
                "unsigned"_s,
                "index()"_s
            },
            {
                "String"_s,
                "id()"_s
            },
            {
                "String"_s,
                "mapping()"_s
            },
            {
                "Vector<double>"_s,
                "axisValues()"_s
            },
            {
                "Vector<double>"_s,
                "buttonValues()"_s
            },
            {
                "MonotonicTime"_s,
                "lastUpdateTime()"_s
            },
            {
                "HashSet<WebCore::GamepadHapticEffectType, IntHash<WebCore::GamepadHapticEffectType>, WTF::StrongEnumHashTraits<WebCore::GamepadHapticEffectType>>"_s,
                "supportedEffectTypes()"_s
            },
        } },
        { "WebKit::WebGPU::BindGroupDescriptor"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "bindGroupLayout"_s
            },
            {
                "Vector<WebKit::WebGPU::BindGroupEntry>"_s,
                "entries"_s
            },
        } },
        { "WebKit::WebGPU::BindGroupEntry"_s, {
            {
                "WebCore::WebGPU::Index32"_s,
                "binding"_s
            },
            {
                "WebKit::WebGPU::BufferBinding"_s,
                "bufferBinding"_s
            },
            {
                "WebKit::WebGPUIdentifier"_s,
                "identifier"_s
            },
            {
                "WebKit::WebGPU::BindingResourceType"_s,
                "type"_s
            },
        } },
        { "WebKit::WebGPU::BindGroupLayoutDescriptor"_s, {
            {
                "Vector<WebKit::WebGPU::BindGroupLayoutEntry>"_s,
                "entries"_s
            },
        } },
        { "WebKit::WebGPU::BindGroupLayoutEntry"_s, {
            {
                "WebCore::WebGPU::Index32"_s,
                "binding"_s
            },
            {
                "WebCore::WebGPU::ShaderStageFlags"_s,
                "visibility"_s
            },
            {
                "std::optional<WebKit::WebGPU::BufferBindingLayout>"_s,
                "buffer"_s
            },
            {
                "std::optional<WebKit::WebGPU::SamplerBindingLayout>"_s,
                "sampler"_s
            },
            {
                "std::optional<WebKit::WebGPU::TextureBindingLayout>"_s,
                "texture"_s
            },
            {
                "std::optional<WebKit::WebGPU::StorageTextureBindingLayout>"_s,
                "storageTexture"_s
            },
            {
                "std::optional<WebKit::WebGPU::ExternalTextureBindingLayout>"_s,
                "externalTexture"_s
            },
        } },
        { "WebKit::WebGPU::BlendComponent"_s, {
            {
                "WebCore::WebGPU::BlendOperation"_s,
                "operation"_s
            },
            {
                "WebCore::WebGPU::BlendFactor"_s,
                "srcFactor"_s
            },
            {
                "WebCore::WebGPU::BlendFactor"_s,
                "dstFactor"_s
            },
        } },
        { "WebKit::WebGPU::BlendState"_s, {
            {
                "WebKit::WebGPU::BlendComponent"_s,
                "color"_s
            },
            {
                "WebKit::WebGPU::BlendComponent"_s,
                "alpha"_s
            },
        } },
        { "WebKit::WebGPU::BufferBinding"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "buffer"_s
            },
            {
                "WebCore::WebGPU::Size64"_s,
                "offset"_s
            },
            {
                "std::optional<WebCore::WebGPU::Size64>"_s,
                "size"_s
            },
        } },
        { "WebKit::WebGPU::BufferBindingLayout"_s, {
            {
                "WebCore::WebGPU::BufferBindingType"_s,
                "type"_s
            },
            {
                "bool"_s,
                "hasDynamicOffset"_s
            },
            {
                "WebCore::WebGPU::Size64"_s,
                "minBindingSize"_s
            },
        } },
        { "WebKit::WebGPU::BufferDescriptor"_s, {
            {
                "WebCore::WebGPU::Size64"_s,
                "size"_s
            },
            {
                "WebCore::WebGPU::BufferUsageFlags"_s,
                "usage"_s
            },
            {
                "bool"_s,
                "mappedAtCreation"_s
            },
        } },
        { "WebKit::WebGPU::CanvasConfiguration"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "device"_s
            },
            {
                "WebCore::WebGPU::TextureFormat"_s,
                "format"_s
            },
            {
                "WebCore::WebGPU::TextureUsageFlags"_s,
                "usage"_s
            },
            {
                "Vector<WebCore::WebGPU::TextureFormat>"_s,
                "viewFormats"_s
            },
            {
                "WebCore::WebGPU::PredefinedColorSpace"_s,
                "colorSpace"_s
            },
            {
                "WebCore::WebGPU::CanvasCompositingAlphaMode"_s,
                "compositingAlphaMode"_s
            },
        } },
        { "WebKit::WebGPU::ColorDict"_s, {
            {
                "double"_s,
                "r"_s
            },
            {
                "double"_s,
                "g"_s
            },
            {
                "double"_s,
                "b"_s
            },
            {
                "double"_s,
                "a"_s
            },
        } },
        { "WebKit::WebGPU::ColorTargetState"_s, {
            {
                "WebCore::WebGPU::TextureFormat"_s,
                "format"_s
            },
            {
                "std::optional<WebKit::WebGPU::BlendState>"_s,
                "blend"_s
            },
            {
                "WebCore::WebGPU::ColorWriteFlags"_s,
                "writeMask"_s
            },
        } },
        { "WebKit::WebGPU::CommandBufferDescriptor"_s, {
        } },
        { "WebKit::WebGPU::CommandEncoderDescriptor"_s, {
        } },
        { "WebKit::WebGPU::CompilationMessage"_s, {
            {
                "String"_s,
                "message"_s
            },
            {
                "WebCore::WebGPU::CompilationMessageType"_s,
                "type"_s
            },
            {
                "uint64_t"_s,
                "lineNum"_s
            },
            {
                "uint64_t"_s,
                "linePos"_s
            },
            {
                "uint64_t"_s,
                "offset"_s
            },
            {
                "uint64_t"_s,
                "length"_s
            },
        } },
        { "WebKit::WebGPU::ComputePassDescriptor"_s, {
            {
                "WebKit::WebGPU::ComputePassTimestampWrites"_s,
                "timestampWrites"_s
            },
        } },
        { "WebKit::WebGPU::ComputePassTimestampWrite"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "querySet"_s
            },
            {
                "WebCore::WebGPU::Size32"_s,
                "queryIndex"_s
            },
            {
                "WebCore::WebGPU::ComputePassTimestampLocation"_s,
                "location"_s
            },
        } },
        { "WebKit::WebGPU::ComputePipelineDescriptor"_s, {
            {
                "WebKit::WebGPU::ProgrammableStage"_s,
                "compute"_s
            },
        } },
        { "WebKit::WebGPU::DepthStencilState"_s, {
            {
                "WebCore::WebGPU::TextureFormat"_s,
                "format"_s
            },
            {
                "bool"_s,
                "depthWriteEnabled"_s
            },
            {
                "WebCore::WebGPU::CompareFunction"_s,
                "depthCompare"_s
            },
            {
                "WebKit::WebGPU::StencilFaceState"_s,
                "stencilFront"_s
            },
            {
                "WebKit::WebGPU::StencilFaceState"_s,
                "stencilBack"_s
            },
            {
                "std::optional<WebCore::WebGPU::StencilValue>"_s,
                "stencilReadMask"_s
            },
            {
                "std::optional<WebCore::WebGPU::StencilValue>"_s,
                "stencilWriteMask"_s
            },
            {
                "WebCore::WebGPU::DepthBias"_s,
                "depthBias"_s
            },
            {
                "float"_s,
                "depthBiasSlopeScale"_s
            },
            {
                "float"_s,
                "depthBiasClamp"_s
            },
        } },
        { "WebKit::WebGPU::DeviceDescriptor"_s, {
            {
                "Vector<WebCore::WebGPU::FeatureName>"_s,
                "requiredFeatures"_s
            },
            {
                "Vector<KeyValuePair<String, uint64_t>>"_s,
                "requiredLimits"_s
            },
        } },
        { "WebKit::WebGPU::Extent3DDict"_s, {
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "width"_s
            },
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "height"_s
            },
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "depthOrArrayLayers"_s
            },
        } },
        { "WebKit::WebGPU::ExternalTextureBindingLayout"_s, {
        } },
        { "WebCore::WebGPU::HTMLVideoElementIdentifier"_s, {
            {
                "uint64_t"_s,
                "identifier"_s
            },
        } },
        { "WebCore::WebGPU::WebCodecsVideoFrameIdentifier"_s, {
            {
                "std::pair<uint64_t, uint64_t>"_s,
                "identifier"_s
            },
        } },
        { "WebKit::WebGPU::ExternalTextureDescriptor"_s, {
            {
                "WebCore::WebGPU::VideoSourceIdentifier"_s,
                "mediaIdentifier"_s
            },
            {
                "WebCore::WebGPU::PredefinedColorSpace"_s,
                "colorSpace"_s
            },
        } },
        { "WebKit::WebGPU::FragmentState"_s, {
            {
                "Vector<std::optional<WebKit::WebGPU::ColorTargetState>>"_s,
                "targets"_s
            },
        } },
        { "WebKit::WebGPU::ImageCopyBuffer"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "buffer"_s
            },
        } },
        { "WebKit::WebGPU::ImageCopyExternalImage"_s, {
            {
                "std::optional<WebKit::WebGPU::Origin2D>"_s,
                "origin"_s
            },
            {
                "bool"_s,
                "flipY"_s
            },
        } },
        { "WebKit::WebGPU::ImageCopyTexture"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "texture"_s
            },
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "mipLevel"_s
            },
            {
                "std::optional<WebKit::WebGPU::Origin3D>"_s,
                "origin"_s
            },
            {
                "WebCore::WebGPU::TextureAspect"_s,
                "aspect"_s
            },
        } },
        { "WebKit::WebGPU::ImageCopyTextureTagged"_s, {
            {
                "WebCore::WebGPU::PredefinedColorSpace"_s,
                "colorSpace"_s
            },
            {
                "bool"_s,
                "premultipliedAlpha"_s
            },
        } },
        { "WebKit::WebGPU::ImageDataLayout"_s, {
            {
                "WebCore::WebGPU::Size64"_s,
                "offset"_s
            },
            {
                "std::optional<WebCore::WebGPU::Size32>"_s,
                "bytesPerRow"_s
            },
            {
                "std::optional<WebCore::WebGPU::Size32>"_s,
                "rowsPerImage"_s
            },
        } },
        { "WebKit::WebGPU::MultisampleState"_s, {
            {
                "WebCore::WebGPU::Size32"_s,
                "count"_s
            },
            {
                "WebCore::WebGPU::SampleMask"_s,
                "mask"_s
            },
            {
                "bool"_s,
                "alphaToCoverageEnabled"_s
            },
        } },
        { "WebKit::WebGPU::ObjectDescriptorBase"_s, {
            {
                "String"_s,
                "label"_s
            },
        } },
        { "WebKit::WebGPU::Origin2DDict"_s, {
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "x"_s
            },
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "y"_s
            },
        } },
        { "WebKit::WebGPU::Origin3DDict"_s, {
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "x"_s
            },
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "y"_s
            },
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "z"_s
            },
        } },
        { "WebKit::WebGPU::OutOfMemoryError"_s, {
        } },
        { "WebKit::WebGPU::PipelineDescriptorBase"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "layout"_s
            },
        } },
        { "WebKit::WebGPU::PipelineLayoutDescriptor"_s, {
            {
                "std::optional<Vector<WebKit::WebGPUIdentifier>>"_s,
                "bindGroupLayouts"_s
            },
        } },
        { "WebKit::WebGPU::PresentationContextDescriptor"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "compositorIntegration"_s
            },
        } },
        { "WebKit::WebGPU::PrimitiveState"_s, {
            {
                "WebCore::WebGPU::PrimitiveTopology"_s,
                "topology"_s
            },
            {
                "std::optional<WebCore::WebGPU::IndexFormat>"_s,
                "stripIndexFormat"_s
            },
            {
                "WebCore::WebGPU::FrontFace"_s,
                "frontFace"_s
            },
            {
                "WebCore::WebGPU::CullMode"_s,
                "cullMode"_s
            },
            {
                "bool"_s,
                "unclippedDepth"_s
            },
        } },
        { "WebKit::WebGPU::ProgrammableStage"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "module"_s
            },
            {
                "String"_s,
                "entryPoint"_s
            },
            {
                "Vector<KeyValuePair<String, double>>"_s,
                "constants"_s
            },
        } },
        { "WebKit::WebGPU::QuerySetDescriptor"_s, {
            {
                "WebCore::WebGPU::QueryType"_s,
                "type"_s
            },
            {
                "WebCore::WebGPU::Size32"_s,
                "count"_s
            },
        } },
        { "WebKit::WebGPU::RenderBundleDescriptor"_s, {
        } },
        { "WebKit::WebGPU::RenderBundleEncoderDescriptor"_s, {
            {
                "bool"_s,
                "depthReadOnly"_s
            },
            {
                "bool"_s,
                "stencilReadOnly"_s
            },
        } },
        { "WebKit::WebGPU::RenderPassColorAttachment"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "view"_s
            },
            {
                "std::optional<WebKit::WebGPUIdentifier>"_s,
                "resolveTarget"_s
            },
            {
                "std::optional<WebKit::WebGPU::Color>"_s,
                "clearValue"_s
            },
            {
                "WebCore::WebGPU::LoadOp"_s,
                "loadOp"_s
            },
            {
                "WebCore::WebGPU::StoreOp"_s,
                "storeOp"_s
            },
        } },
        { "WebKit::WebGPU::RenderPassDepthStencilAttachment"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "view"_s
            },
            {
                "float"_s,
                "depthClearValue"_s
            },
            {
                "std::optional<WebCore::WebGPU::LoadOp>"_s,
                "depthLoadOp"_s
            },
            {
                "std::optional<WebCore::WebGPU::StoreOp>"_s,
                "depthStoreOp"_s
            },
            {
                "bool"_s,
                "depthReadOnly"_s
            },
            {
                "WebCore::WebGPU::StencilValue"_s,
                "stencilClearValue"_s
            },
            {
                "std::optional<WebCore::WebGPU::LoadOp>"_s,
                "stencilLoadOp"_s
            },
            {
                "std::optional<WebCore::WebGPU::StoreOp>"_s,
                "stencilStoreOp"_s
            },
            {
                "bool"_s,
                "stencilReadOnly"_s
            },
        } },
        { "WebKit::WebGPU::RenderPassDescriptor"_s, {
            {
                "Vector<std::optional<WebKit::WebGPU::RenderPassColorAttachment>>"_s,
                "colorAttachments"_s
            },
            {
                "std::optional<WebKit::WebGPU::RenderPassDepthStencilAttachment>"_s,
                "depthStencilAttachment"_s
            },
            {
                "std::optional<WebKit::WebGPUIdentifier>"_s,
                "occlusionQuerySet"_s
            },
            {
                "WebKit::WebGPU::RenderPassTimestampWrites"_s,
                "timestampWrites"_s
            },
        } },
        { "WebKit::WebGPU::RenderPassLayout"_s, {
            {
                "Vector<std::optional<WebCore::WebGPU::TextureFormat>>"_s,
                "colorFormats"_s
            },
            {
                "std::optional<WebCore::WebGPU::TextureFormat>"_s,
                "depthStencilFormat"_s
            },
            {
                "WebCore::WebGPU::Size32"_s,
                "sampleCount"_s
            },
        } },
        { "WebKit::WebGPU::RenderPassTimestampWrite"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "querySet"_s
            },
            {
                "WebCore::WebGPU::Size32"_s,
                "queryIndex"_s
            },
            {
                "WebCore::WebGPU::RenderPassTimestampLocation"_s,
                "location"_s
            },
        } },
        { "WebKit::WebGPU::RenderPipelineDescriptor"_s, {
            {
                "WebKit::WebGPU::VertexState"_s,
                "vertex"_s
            },
            {
                "std::optional<WebKit::WebGPU::PrimitiveState>"_s,
                "primitive"_s
            },
            {
                "std::optional<WebKit::WebGPU::DepthStencilState>"_s,
                "depthStencil"_s
            },
            {
                "std::optional<WebKit::WebGPU::MultisampleState>"_s,
                "multisample"_s
            },
            {
                "std::optional<WebKit::WebGPU::FragmentState>"_s,
                "fragment"_s
            },
        } },
        { "WebKit::WebGPU::RequestAdapterOptions"_s, {
            {
                "std::optional<WebCore::WebGPU::PowerPreference>"_s,
                "powerPreference"_s
            },
            {
                "bool"_s,
                "forceFallbackAdapter"_s
            },
        } },
        { "WebKit::WebGPU::SamplerBindingLayout"_s, {
            {
                "WebCore::WebGPU::SamplerBindingType"_s,
                "type"_s
            },
        } },
        { "WebKit::WebGPU::SamplerDescriptor"_s, {
            {
                "WebCore::WebGPU::AddressMode"_s,
                "addressModeU"_s
            },
            {
                "WebCore::WebGPU::AddressMode"_s,
                "addressModeV"_s
            },
            {
                "WebCore::WebGPU::AddressMode"_s,
                "addressModeW"_s
            },
            {
                "WebCore::WebGPU::FilterMode"_s,
                "magFilter"_s
            },
            {
                "WebCore::WebGPU::FilterMode"_s,
                "minFilter"_s
            },
            {
                "WebCore::WebGPU::MipmapFilterMode"_s,
                "mipmapFilter"_s
            },
            {
                "float"_s,
                "lodMinClamp"_s
            },
            {
                "float"_s,
                "lodMaxClamp"_s
            },
            {
                "std::optional<WebCore::WebGPU::CompareFunction>"_s,
                "compare"_s
            },
            {
                "uint16_t"_s,
                "maxAnisotropy"_s
            },
        } },
        { "WebKit::WebGPU::ShaderModuleCompilationHint"_s, {
            {
                "WebKit::WebGPUIdentifier"_s,
                "pipelineLayout"_s
            },
        } },
        { "WebKit::WebGPU::ShaderModuleDescriptor"_s, {
            {
                "String"_s,
                "code"_s
            },
            {
                "Vector<KeyValuePair<String, WebKit::WebGPU::ShaderModuleCompilationHint>>"_s,
                "hints"_s
            },
        } },
        { "WebKit::WebGPU::StencilFaceState"_s, {
            {
                "WebCore::WebGPU::CompareFunction"_s,
                "compare"_s
            },
            {
                "WebCore::WebGPU::StencilOperation"_s,
                "failOp"_s
            },
            {
                "WebCore::WebGPU::StencilOperation"_s,
                "depthFailOp"_s
            },
            {
                "WebCore::WebGPU::StencilOperation"_s,
                "passOp"_s
            },
        } },
        { "WebKit::WebGPU::StorageTextureBindingLayout"_s, {
            {
                "WebCore::WebGPU::StorageTextureAccess"_s,
                "access"_s
            },
            {
                "WebCore::WebGPU::TextureFormat"_s,
                "format"_s
            },
            {
                "WebCore::WebGPU::TextureViewDimension"_s,
                "viewDimension"_s
            },
        } },
        { "WebKit::WebGPU::SupportedFeatures"_s, {
            {
                "Vector<String>"_s,
                "features"_s
            },
        } },
        { "WebKit::WebGPU::SupportedLimits"_s, {
            {
                "uint32_t"_s,
                "maxTextureDimension1D"_s
            },
            {
                "uint32_t"_s,
                "maxTextureDimension2D"_s
            },
            {
                "uint32_t"_s,
                "maxTextureDimension3D"_s
            },
            {
                "uint32_t"_s,
                "maxTextureArrayLayers"_s
            },
            {
                "uint32_t"_s,
                "maxBindGroups"_s
            },
            {
                "uint32_t"_s,
                "maxBindingsPerBindGroup"_s
            },
            {
                "uint32_t"_s,
                "maxDynamicUniformBuffersPerPipelineLayout"_s
            },
            {
                "uint32_t"_s,
                "maxDynamicStorageBuffersPerPipelineLayout"_s
            },
            {
                "uint32_t"_s,
                "maxSampledTexturesPerShaderStage"_s
            },
            {
                "uint32_t"_s,
                "maxSamplersPerShaderStage"_s
            },
            {
                "uint32_t"_s,
                "maxStorageBuffersPerShaderStage"_s
            },
            {
                "uint32_t"_s,
                "maxStorageTexturesPerShaderStage"_s
            },
            {
                "uint32_t"_s,
                "maxUniformBuffersPerShaderStage"_s
            },
            {
                "uint64_t"_s,
                "maxUniformBufferBindingSize"_s
            },
            {
                "uint64_t"_s,
                "maxStorageBufferBindingSize"_s
            },
            {
                "uint32_t"_s,
                "minUniformBufferOffsetAlignment"_s
            },
            {
                "uint32_t"_s,
                "minStorageBufferOffsetAlignment"_s
            },
            {
                "uint32_t"_s,
                "maxVertexBuffers"_s
            },
            {
                "uint64_t"_s,
                "maxBufferSize"_s
            },
            {
                "uint32_t"_s,
                "maxVertexAttributes"_s
            },
            {
                "uint32_t"_s,
                "maxVertexBufferArrayStride"_s
            },
            {
                "uint32_t"_s,
                "maxInterStageShaderComponents"_s
            },
            {
                "uint32_t"_s,
                "maxInterStageShaderVariables"_s
            },
            {
                "uint32_t"_s,
                "maxColorAttachments"_s
            },
            {
                "uint32_t"_s,
                "maxColorAttachmentBytesPerSample"_s
            },
            {
                "uint32_t"_s,
                "maxComputeWorkgroupStorageSize"_s
            },
            {
                "uint32_t"_s,
                "maxComputeInvocationsPerWorkgroup"_s
            },
            {
                "uint32_t"_s,
                "maxComputeWorkgroupSizeX"_s
            },
            {
                "uint32_t"_s,
                "maxComputeWorkgroupSizeY"_s
            },
            {
                "uint32_t"_s,
                "maxComputeWorkgroupSizeZ"_s
            },
            {
                "uint32_t"_s,
                "maxComputeWorkgroupsPerDimension"_s
            },
        } },
        { "WebKit::WebGPU::TextureBindingLayout"_s, {
            {
                "WebCore::WebGPU::TextureSampleType"_s,
                "sampleType"_s
            },
            {
                "WebCore::WebGPU::TextureViewDimension"_s,
                "viewDimension"_s
            },
            {
                "bool"_s,
                "multisampled"_s
            },
        } },
        { "WebKit::WebGPU::TextureDescriptor"_s, {
            {
                "WebKit::WebGPU::Extent3D"_s,
                "size"_s
            },
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "mipLevelCount"_s
            },
            {
                "WebCore::WebGPU::Size32"_s,
                "sampleCount"_s
            },
            {
                "WebCore::WebGPU::TextureDimension"_s,
                "dimension"_s
            },
            {
                "WebCore::WebGPU::TextureFormat"_s,
                "format"_s
            },
            {
                "WebCore::WebGPU::TextureUsageFlags"_s,
                "usage"_s
            },
            {
                "Vector<WebCore::WebGPU::TextureFormat>"_s,
                "viewFormats"_s
            },
        } },
        { "WebKit::WebGPU::TextureViewDescriptor"_s, {
            {
                "std::optional<WebCore::WebGPU::TextureFormat>"_s,
                "format"_s
            },
            {
                "std::optional<WebCore::WebGPU::TextureViewDimension>"_s,
                "dimension"_s
            },
            {
                "WebCore::WebGPU::TextureAspect"_s,
                "aspect"_s
            },
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "baseMipLevel"_s
            },
            {
                "std::optional<WebCore::WebGPU::IntegerCoordinate>"_s,
                "mipLevelCount"_s
            },
            {
                "WebCore::WebGPU::IntegerCoordinate"_s,
                "baseArrayLayer"_s
            },
            {
                "std::optional<WebCore::WebGPU::IntegerCoordinate>"_s,
                "arrayLayerCount"_s
            },
        } },
        { "WebKit::WebGPU::ValidationError"_s, {
            {
                "String"_s,
                "message"_s
            },
        } },
        { "WebKit::WebGPU::VertexAttribute"_s, {
            {
                "WebCore::WebGPU::VertexFormat"_s,
                "format"_s
            },
            {
                "WebCore::WebGPU::Size64"_s,
                "offset"_s
            },
            {
                "WebCore::WebGPU::Index32"_s,
                "shaderLocation"_s
            },
        } },
        { "WebKit::WebGPU::VertexBufferLayout"_s, {
            {
                "WebCore::WebGPU::Size64"_s,
                "arrayStride"_s
            },
            {
                "WebCore::WebGPU::VertexStepMode"_s,
                "stepMode"_s
            },
            {
                "Vector<WebKit::WebGPU::VertexAttribute>"_s,
                "attributes"_s
            },
        } },
        { "WebKit::WebGPU::VertexState"_s, {
            {
                "Vector<std::optional<WebKit::WebGPU::VertexBufferLayout>>"_s,
                "buffers"_s
            },
        } },
        { "WebKit::WebsiteData::Entry"_s, {
            {
                "WebCore::SecurityOriginData"_s,
                "origin"_s
            },
            {
                "OptionSet<WebKit::WebsiteDataType>"_s,
                "typeAsOptionSet()"_s
            },
            {
                "uint64_t"_s,
                "size"_s
            },
        } },
        { "WebKit::WebsiteData"_s, {
            {
                "Vector<WebKit::WebsiteData::Entry>"_s,
                "entries"_s
            },
            {
                "HashSet<String>"_s,
                "hostNamesWithCookies"_s
            },
            {
                "HashSet<String>"_s,
                "hostNamesWithHSTSCache"_s
            },
#if ENABLE(TRACKING_PREVENTION)
            {
                "HashSet<WebCore::RegistrableDomain>"_s,
                "registrableDomainsWithResourceLoadStatistics"_s
            },
#endif
        } },
        { "WebKit::BufferIdentifierSet"_s, {
            {
                "std::optional<WebCore::RenderingResourceIdentifier>"_s,
                "front"_s
            },
            {
                "std::optional<WebCore::RenderingResourceIdentifier>"_s,
                "back"_s
            },
            {
                "std::optional<WebCore::RenderingResourceIdentifier>"_s,
                "secondaryBack"_s
            },
        } },
        { "WebKit::PrepareBackingStoreBuffersInputData"_s, {
            {
                "WebKit::BufferIdentifierSet"_s,
                "bufferSet"_s
            },
            {
                "bool"_s,
                "supportsPartialRepaint"_s
            },
            {
                "bool"_s,
                "hasEmptyDirtyRegion"_s
            },
        } },
        { "WebKit::PrepareBackingStoreBuffersOutputData"_s, {
            {
                "WebKit::BufferIdentifierSet"_s,
                "bufferSet"_s
            },
            {
                "std::optional<WebKit::ImageBufferBackendHandle>"_s,
                "frontBufferHandle"_s
            },
            {
                "WebKit::SwapBuffersDisplayRequirement"_s,
                "displayRequirement"_s
            },
        } },
        { "WebKit::RemoteAudioSessionConfiguration"_s, {
            {
                "String"_s,
                "routingContextUID"_s
            },
            {
                "float"_s,
                "sampleRate"_s
            },
            {
                "size_t"_s,
                "bufferSize"_s
            },
            {
                "size_t"_s,
                "numberOfOutputChannels"_s
            },
            {
                "size_t"_s,
                "maximumNumberOfOutputChannels"_s
            },
            {
                "size_t"_s,
                "preferredBufferSize"_s
            },
            {
                "bool"_s,
                "isMuted"_s
            },
            {
                "bool"_s,
                "isActive"_s
            },
        } },
        { "WebKit::RemoteCDMConfiguration"_s, {
            {
                "Vector<AtomString>"_s,
                "supportedInitDataTypes"_s
            },
            {
                "Vector<AtomString>"_s,
                "supportedRobustnesses"_s
            },
            {
                "bool"_s,
                "supportsServerCertificates"_s
            },
            {
                "bool"_s,
                "supportsSessions"_s
            },
            {
                "uint64_t"_s,
                "logIdentifier"_s
            },
        } },
        { "WebKit::RemoteMediaPlayerConfiguration"_s, {
            {
                "String"_s,
                "engineDescription"_s
            },
            {
                "double"_s,
                "maximumDurationToCacheMediaTime"_s
            },
            {
                "bool"_s,
                "supportsScanning"_s
            },
            {
                "bool"_s,
                "supportsFullscreen"_s
            },
            {
                "bool"_s,
                "supportsPictureInPicture"_s
            },
            {
                "bool"_s,
                "supportsAcceleratedRendering"_s
            },
            {
                "bool"_s,
                "supportsPlayAtHostTime"_s
            },
            {
                "bool"_s,
                "supportsPauseAtHostTime"_s
            },
            {
                "bool"_s,
                "canPlayToWirelessPlaybackTarget"_s
            },
            {
                "bool"_s,
                "shouldIgnoreIntrinsicSize"_s
            },
        } },
        { "WebKit::RemoteMediaPlayerState"_s, {
            {
                "MediaTime"_s,
                "duration"_s
            },
            {
                "MediaTime"_s,
                "minTimeSeekable"_s
            },
            {
                "MediaTime"_s,
                "maxTimeSeekable"_s
            },
            {
                "MediaTime"_s,
                "startDate"_s
            },
            {
                "MediaTime"_s,
                "startTime"_s
            },
            {
                "String"_s,
                "languageOfPrimaryAudioTrack"_s
            },
            {
                "String"_s,
                "wirelessPlaybackTargetName"_s
            },
            {
                "std::optional<WebCore::PlatformTimeRanges>"_s,
                "bufferedRanges"_s
            },
            {
                "WebCore::MediaPlayerEnums::NetworkState"_s,
                "networkState"_s
            },
            {
                "WebCore::MediaPlayerEnums::ReadyState"_s,
                "readyState"_s
            },
            {
                "WebCore::MediaPlayerEnums::MovieLoadType"_s,
                "movieLoadType"_s
            },
            {
                "WebCore::MediaPlayerEnums::WirelessPlaybackTargetType"_s,
                "wirelessPlaybackTargetType"_s
            },
            {
                "WebCore::FloatSize"_s,
                "naturalSize"_s
            },
            {
                "double"_s,
                "maxFastForwardRate"_s
            },
            {
                "double"_s,
                "minFastReverseRate"_s
            },
            {
                "double"_s,
                "seekableTimeRangesLastModifiedTime"_s
            },
            {
                "double"_s,
                "liveUpdateInterval"_s
            },
            {
                "uint64_t"_s,
                "totalBytes"_s
            },
            {
                "std::optional<WebCore::VideoPlaybackQualityMetrics>"_s,
                "videoMetrics"_s
            },
            {
                "std::optional<bool>"_s,
                "documentIsCrossOrigin"_s
            },
            {
                "bool"_s,
                "paused"_s
            },
            {
                "bool"_s,
                "canSaveMediaData"_s
            },
            {
                "bool"_s,
                "hasAudio"_s
            },
            {
                "bool"_s,
                "hasVideo"_s
            },
            {
                "bool"_s,
                "hasClosedCaptions"_s
            },
            {
                "bool"_s,
                "hasAvailableVideoFrame"_s
            },
            {
                "bool"_s,
                "wirelessVideoPlaybackDisabled"_s
            },
            {
                "bool"_s,
                "didPassCORSAccessCheck"_s
            },
        } },
        { "WebKit::WebSpeechSynthesisVoice"_s, {
            {
                "String"_s,
                "voiceURI"_s
            },
            {
                "String"_s,
                "name"_s
            },
            {
                "String"_s,
                "lang"_s
            },
            {
                "bool"_s,
                "localService"_s
            },
            {
                "bool"_s,
                "defaultLang"_s
            },
        } },
        { "WebCore::PlatformDisplayID"_s, {
            { "uint32_t;"_s, "alias"_s }
        } },
        { "WebCore::SharedStringHash"_s, {
            { "uint32_t"_s, "alias"_s }
        } },
        { "WebCore::IDBConnectionIdentifier"_s, {
            { "WebCore::ProcessIdentifier;"_s, "alias"_s }
        } },
        { "WebCore::TransferredMessagePort"_s, {
            { "std::pair<WebCore::MessagePortIdentifier, WebCore::MessagePortIdentifier>;"_s, "alias"_s }
        } },
    };
}

Vector<SerializedEnumInfo> allSerializedEnums()
{
    return {
        { "WebCore::PathRoundedRect::Strategy"_s, sizeof(WebCore::PathRoundedRect::Strategy), false, {
            static_cast<uint64_t>(WebCore::PathRoundedRect::Strategy::PreferNative),
            static_cast<uint64_t>(WebCore::PathRoundedRect::Strategy::PreferBezier),
        } },
        { "WebKit::PreconnectOnly"_s, sizeof(WebKit::PreconnectOnly), false, {
            0, 1
        } },
        { "WebKit::ListType"_s, sizeof(WebKit::ListType), false, {
            static_cast<uint64_t>(WebKit::ListType::None),
            static_cast<uint64_t>(WebKit::ListType::OrderedList),
            static_cast<uint64_t>(WebKit::ListType::UnorderedList),
        } },
        { "WebKit::TextAlignment"_s, sizeof(WebKit::TextAlignment), false, {
            static_cast<uint64_t>(WebKit::TextAlignment::Natural),
            static_cast<uint64_t>(WebKit::TextAlignment::Left),
            static_cast<uint64_t>(WebKit::TextAlignment::Right),
            static_cast<uint64_t>(WebKit::TextAlignment::Center),
            static_cast<uint64_t>(WebKit::TextAlignment::Justified),
        } },
        { "WebKit::TypingAttribute"_s, sizeof(WebKit::TypingAttribute), true, {
            static_cast<uint64_t>(WebKit::TypingAttribute::Bold),
            static_cast<uint64_t>(WebKit::TypingAttribute::Italics),
            static_cast<uint64_t>(WebKit::TypingAttribute::Underline),
            static_cast<uint64_t>(WebKit::TypingAttribute::StrikeThrough),
        } },
        { "WebKit::FrameType"_s, sizeof(WebKit::FrameType), false, {
            0, 1
        } },
        { "WebKit::RemoteWorkerType"_s, sizeof(WebKit::RemoteWorkerType), false, {
            static_cast<uint64_t>(WebKit::RemoteWorkerType::ServiceWorker),
            static_cast<uint64_t>(WebKit::RemoteWorkerType::SharedWorker),
        } },
        { "WebKit::SameDocumentNavigationType"_s, sizeof(WebKit::SameDocumentNavigationType), false, {
            static_cast<uint64_t>(WebKit::SameDocumentNavigationType::AnchorNavigation),
            static_cast<uint64_t>(WebKit::SameDocumentNavigationType::SessionStatePush),
            static_cast<uint64_t>(WebKit::SameDocumentNavigationType::SessionStateReplace),
            static_cast<uint64_t>(WebKit::SameDocumentNavigationType::SessionStatePop),
        } },
        { "WebCore::FontWidthVariant"_s, sizeof(WebCore::FontWidthVariant), false, {
            static_cast<uint64_t>(WebCore::FontWidthVariant::RegularWidth),
            static_cast<uint64_t>(WebCore::FontWidthVariant::HalfWidth),
            static_cast<uint64_t>(WebCore::FontWidthVariant::ThirdWidth),
            static_cast<uint64_t>(WebCore::FontWidthVariant::QuarterWidth),
        } },
        { "WebCore::Kerning"_s, sizeof(WebCore::Kerning), false, {
            static_cast<uint64_t>(WebCore::Kerning::Auto),
            static_cast<uint64_t>(WebCore::Kerning::Normal),
            static_cast<uint64_t>(WebCore::Kerning::NoShift),
        } },
        { "WebCore::FontOpticalSizing"_s, sizeof(WebCore::FontOpticalSizing), false, {
            static_cast<uint64_t>(WebCore::FontOpticalSizing::Enabled),
            static_cast<uint64_t>(WebCore::FontOpticalSizing::Disabled),
        } },
        { "WebCore::FontStyleAxis"_s, sizeof(WebCore::FontStyleAxis), false, {
            static_cast<uint64_t>(WebCore::FontStyleAxis::slnt),
            static_cast<uint64_t>(WebCore::FontStyleAxis::ital),
        } },
        { "WebCore::AllowUserInstalledFonts"_s, sizeof(WebCore::AllowUserInstalledFonts), false, {
            0, 1
        } },
        { "WebCore::FontVariantEastAsianVariant"_s, sizeof(WebCore::FontVariantEastAsianVariant), false, {
            static_cast<uint64_t>(WebCore::FontVariantEastAsianVariant::Normal),
            static_cast<uint64_t>(WebCore::FontVariantEastAsianVariant::Jis78),
            static_cast<uint64_t>(WebCore::FontVariantEastAsianVariant::Jis83),
            static_cast<uint64_t>(WebCore::FontVariantEastAsianVariant::Jis90),
            static_cast<uint64_t>(WebCore::FontVariantEastAsianVariant::Jis04),
            static_cast<uint64_t>(WebCore::FontVariantEastAsianVariant::Simplified),
            static_cast<uint64_t>(WebCore::FontVariantEastAsianVariant::Traditional),
        } },
        { "WebCore::FontVariantEastAsianWidth"_s, sizeof(WebCore::FontVariantEastAsianWidth), false, {
            static_cast<uint64_t>(WebCore::FontVariantEastAsianWidth::Normal),
            static_cast<uint64_t>(WebCore::FontVariantEastAsianWidth::Full),
            static_cast<uint64_t>(WebCore::FontVariantEastAsianWidth::Proportional),
        } },
        { "WebCore::FontVariantEastAsianRuby"_s, sizeof(WebCore::FontVariantEastAsianRuby), false, {
            static_cast<uint64_t>(WebCore::FontVariantEastAsianRuby::Normal),
            static_cast<uint64_t>(WebCore::FontVariantEastAsianRuby::Yes),
        } },
        { "WebCore::FontVariantLigatures"_s, sizeof(WebCore::FontVariantLigatures), false, {
            static_cast<uint64_t>(WebCore::FontVariantLigatures::Normal),
            static_cast<uint64_t>(WebCore::FontVariantLigatures::Yes),
            static_cast<uint64_t>(WebCore::FontVariantLigatures::No),
        } },
        { "WebCore::FontVariantPosition"_s, sizeof(WebCore::FontVariantPosition), false, {
            static_cast<uint64_t>(WebCore::FontVariantPosition::Normal),
            static_cast<uint64_t>(WebCore::FontVariantPosition::Subscript),
            static_cast<uint64_t>(WebCore::FontVariantPosition::Superscript),
        } },
        { "WebCore::FontVariantCaps"_s, sizeof(WebCore::FontVariantCaps), false, {
            static_cast<uint64_t>(WebCore::FontVariantCaps::Normal),
            static_cast<uint64_t>(WebCore::FontVariantCaps::Small),
            static_cast<uint64_t>(WebCore::FontVariantCaps::AllSmall),
            static_cast<uint64_t>(WebCore::FontVariantCaps::Petite),
            static_cast<uint64_t>(WebCore::FontVariantCaps::AllPetite),
            static_cast<uint64_t>(WebCore::FontVariantCaps::Unicase),
            static_cast<uint64_t>(WebCore::FontVariantCaps::Titling),
        } },
        { "WebCore::FontVariantNumericFigure"_s, sizeof(WebCore::FontVariantNumericFigure), false, {
            static_cast<uint64_t>(WebCore::FontVariantNumericFigure::Normal),
            static_cast<uint64_t>(WebCore::FontVariantNumericFigure::LiningNumbers),
            static_cast<uint64_t>(WebCore::FontVariantNumericFigure::OldStyleNumbers),
        } },
        { "WebCore::FontVariantNumericSpacing"_s, sizeof(WebCore::FontVariantNumericSpacing), false, {
            static_cast<uint64_t>(WebCore::FontVariantNumericSpacing::Normal),
            static_cast<uint64_t>(WebCore::FontVariantNumericSpacing::ProportionalNumbers),
            static_cast<uint64_t>(WebCore::FontVariantNumericSpacing::TabularNumbers),
        } },
        { "WebCore::FontVariantNumericFraction"_s, sizeof(WebCore::FontVariantNumericFraction), false, {
            static_cast<uint64_t>(WebCore::FontVariantNumericFraction::Normal),
            static_cast<uint64_t>(WebCore::FontVariantNumericFraction::DiagonalFractions),
            static_cast<uint64_t>(WebCore::FontVariantNumericFraction::StackedFractions),
        } },
        { "WebCore::TextRenderingMode"_s, sizeof(WebCore::TextRenderingMode), false, {
            static_cast<uint64_t>(WebCore::TextRenderingMode::AutoTextRendering),
            static_cast<uint64_t>(WebCore::TextRenderingMode::OptimizeSpeed),
            static_cast<uint64_t>(WebCore::TextRenderingMode::OptimizeLegibility),
            static_cast<uint64_t>(WebCore::TextRenderingMode::GeometricPrecision),
        } },
        { "WebCore::FontSmoothingMode"_s, sizeof(WebCore::FontSmoothingMode), false, {
            static_cast<uint64_t>(WebCore::FontSmoothingMode::AutoSmoothing),
            static_cast<uint64_t>(WebCore::FontSmoothingMode::NoSmoothing),
            static_cast<uint64_t>(WebCore::FontSmoothingMode::Antialiased),
            static_cast<uint64_t>(WebCore::FontSmoothingMode::SubpixelAntialiased),
        } },
        { "WebCore::FontOrientation"_s, sizeof(WebCore::FontOrientation), false, {
            0, 1
        } },
        { "WebCore::NonCJKGlyphOrientation"_s, sizeof(WebCore::NonCJKGlyphOrientation), false, {
            0, 1
        } },
        { "WebCore::FontSynthesisLonghandValue"_s, sizeof(WebCore::FontSynthesisLonghandValue), false, {
            0, 1
        } },
        { "WebCore::FontSmallCaps"_s, sizeof(WebCore::FontSmallCaps), false, {
            0, 1
        } },
#if ENABLE(APPLE_PAY)
        { "WebCore::ApplePayFeature"_s, sizeof(WebCore::ApplePayFeature), false, {
#if ENABLE(APPLE_PAY_LATER)
            static_cast<uint64_t>(WebCore::ApplePayFeature::ApplePayLater),
#endif
#if ENABLE(APPLE_PAY_LATER_AVAILABILITY)
            static_cast<uint64_t>(WebCore::ApplePayFeature::ApplePayLaterAvailability),
#endif
#if ENABLE(APPLE_PAY_PAYMENT_ORDER_DETAILS)
            static_cast<uint64_t>(WebCore::ApplePayFeature::AuthorizationResultOrderDetails),
#endif
            static_cast<uint64_t>(WebCore::ApplePayFeature::LineItemPaymentTiming),
#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_PAYMENTS)
            static_cast<uint64_t>(WebCore::ApplePayFeature::PaymentRequestAutomaticReload),
#endif
#if ENABLE(APPLE_PAY_COUPON_CODE)
            static_cast<uint64_t>(WebCore::ApplePayFeature::PaymentRequestCouponCode),
#endif
#if ENABLE(APPLE_PAY_MULTI_MERCHANT_PAYMENTS)
            static_cast<uint64_t>(WebCore::ApplePayFeature::PaymentRequestMultiTokenContexts),
#endif
#if ENABLE(APPLE_PAY_RECURRING_PAYMENTS)
            static_cast<uint64_t>(WebCore::ApplePayFeature::PaymentRequestRecurring),
#endif
#if ENABLE(APPLE_PAY_SHIPPING_CONTACT_EDITING_MODE)
            static_cast<uint64_t>(WebCore::ApplePayFeature::PaymentRequestShippingContactEditingMode),
#endif
#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_LINE_ITEM)
            static_cast<uint64_t>(WebCore::ApplePayFeature::PaymentTimingAutomaticReload),
#endif
#if ENABLE(APPLE_PAY_DEFERRED_PAYMENTS)
            static_cast<uint64_t>(WebCore::ApplePayFeature::PaymentRequestDeferred),
#endif
#if ENABLE(APPLE_PAY_DEFERRED_LINE_ITEM)
            static_cast<uint64_t>(WebCore::ApplePayFeature::PaymentTimingDeferred),
#endif
            static_cast<uint64_t>(WebCore::ApplePayFeature::PaymentTimingImmediate),
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
            static_cast<uint64_t>(WebCore::ApplePayFeature::PaymentTimingRecurring),
#endif
#if ENABLE(APPLE_PAY_SHIPPING_CONTACT_EDITING_MODE)
            static_cast<uint64_t>(WebCore::ApplePayFeature::ShippingContactEditingModeEnabled),
#endif
#if ENABLE(APPLE_PAY_SHIPPING_CONTACT_EDITING_MODE)
            static_cast<uint64_t>(WebCore::ApplePayFeature::ShippingContactEditingModeStorePickup),
#endif
#if ENABLE(APPLE_PAY_SHIPPING_METHOD_DATE_COMPONENTS_RANGE)
            static_cast<uint64_t>(WebCore::ApplePayFeature::ShippingMethodDateComponentsRange),
#endif
        } },
#endif
#if ENABLE(APPLE_PAY)
        { "WebCore::ApplePayPaymentTiming"_s, sizeof(WebCore::ApplePayPaymentTiming), false, {
            static_cast<uint64_t>(WebCore::ApplePayPaymentTiming::Immediate),
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
            static_cast<uint64_t>(WebCore::ApplePayPaymentTiming::Recurring),
#endif
#if ENABLE(APPLE_PAY_DEFERRED_LINE_ITEM)
            static_cast<uint64_t>(WebCore::ApplePayPaymentTiming::Deferred),
#endif
#if ENABLE(APPLE_PAY_AUTOMATIC_RELOAD_LINE_ITEM)
            static_cast<uint64_t>(WebCore::ApplePayPaymentTiming::AutomaticReload),
#endif
        } },
#endif
#if ENABLE(APPLE_PAY_RECURRING_LINE_ITEM)
        { "WebCore::ApplePayRecurringPaymentDateUnit"_s, sizeof(WebCore::ApplePayRecurringPaymentDateUnit), false, {
            static_cast<uint64_t>(WebCore::ApplePayRecurringPaymentDateUnit::Year),
            static_cast<uint64_t>(WebCore::ApplePayRecurringPaymentDateUnit::Month),
            static_cast<uint64_t>(WebCore::ApplePayRecurringPaymentDateUnit::Day),
            static_cast<uint64_t>(WebCore::ApplePayRecurringPaymentDateUnit::Hour),
            static_cast<uint64_t>(WebCore::ApplePayRecurringPaymentDateUnit::Minute),
        } },
#endif
        { "WebCore::ContactProperty"_s, sizeof(WebCore::ContactProperty), false, {
            static_cast<uint64_t>(WebCore::ContactProperty::Email),
            static_cast<uint64_t>(WebCore::ContactProperty::Name),
            static_cast<uint64_t>(WebCore::ContactProperty::Tel),
        } },
        { "WebCore::CookieConsentDecisionResult"_s, sizeof(WebCore::CookieConsentDecisionResult), false, {
            static_cast<uint64_t>(WebCore::CookieConsentDecisionResult::NotSupported),
            static_cast<uint64_t>(WebCore::CookieConsentDecisionResult::Consent),
            static_cast<uint64_t>(WebCore::CookieConsentDecisionResult::Dissent),
        } },
        { "WebCore::IDBResultType"_s, sizeof(WebCore::IDBResultType), false, {
            static_cast<uint64_t>(WebCore::IDBResultType::Error),
            static_cast<uint64_t>(WebCore::IDBResultType::OpenDatabaseSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::OpenDatabaseUpgradeNeeded),
            static_cast<uint64_t>(WebCore::IDBResultType::DeleteDatabaseSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::CreateObjectStoreSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::DeleteObjectStoreSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::ClearObjectStoreSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::PutOrAddSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::GetRecordSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::GetAllRecordsSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::GetCountSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::DeleteRecordSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::CreateIndexSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::DeleteIndexSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::OpenCursorSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::IterateCursorSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::RenameObjectStoreSuccess),
            static_cast<uint64_t>(WebCore::IDBResultType::RenameIndexSuccess),
        } },
        { "WebCore::IDBTransactionDurability"_s, sizeof(WebCore::IDBTransactionDurability), false, {
            static_cast<uint64_t>(WebCore::IDBTransactionDurability::Strict),
            static_cast<uint64_t>(WebCore::IDBTransactionDurability::Relaxed),
            static_cast<uint64_t>(WebCore::IDBTransactionDurability::Default),
        } },
        { "WebCore::IDBTransactionMode"_s, sizeof(WebCore::IDBTransactionMode), false, {
            static_cast<uint64_t>(WebCore::IDBTransactionMode::Readonly),
            static_cast<uint64_t>(WebCore::IDBTransactionMode::Readwrite),
            static_cast<uint64_t>(WebCore::IDBTransactionMode::Versionchange),
        } },
#if ENABLE(MEDIA_SESSION)
        { "WebCore::MediaSessionAction"_s, sizeof(WebCore::MediaSessionAction), false, {
            static_cast<uint64_t>(WebCore::MediaSessionAction::Play),
            static_cast<uint64_t>(WebCore::MediaSessionAction::Pause),
            static_cast<uint64_t>(WebCore::MediaSessionAction::Seekbackward),
            static_cast<uint64_t>(WebCore::MediaSessionAction::Seekforward),
            static_cast<uint64_t>(WebCore::MediaSessionAction::Previoustrack),
            static_cast<uint64_t>(WebCore::MediaSessionAction::Nexttrack),
            static_cast<uint64_t>(WebCore::MediaSessionAction::Skipad),
            static_cast<uint64_t>(WebCore::MediaSessionAction::Stop),
            static_cast<uint64_t>(WebCore::MediaSessionAction::Seekto),
            static_cast<uint64_t>(WebCore::MediaSessionAction::Settrack),
        } },
#endif
#if ENABLE(MEDIA_SESSION)
        { "WebCore::MediaSessionPlaybackState"_s, sizeof(WebCore::MediaSessionPlaybackState), false, {
            static_cast<uint64_t>(WebCore::MediaSessionPlaybackState::None),
            static_cast<uint64_t>(WebCore::MediaSessionPlaybackState::Paused),
            static_cast<uint64_t>(WebCore::MediaSessionPlaybackState::Playing),
        } },
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
        { "WebCore::MediaSessionCoordinatorState"_s, sizeof(WebCore::MediaSessionCoordinatorState), false, {
            static_cast<uint64_t>(WebCore::MediaSessionCoordinatorState::Waiting),
            static_cast<uint64_t>(WebCore::MediaSessionCoordinatorState::Joined),
            static_cast<uint64_t>(WebCore::MediaSessionCoordinatorState::Closed),
        } },
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
        { "WebCore::MediaSessionReadyState"_s, sizeof(WebCore::MediaSessionReadyState), false, {
            static_cast<uint64_t>(WebCore::MediaSessionReadyState::Havenothing),
            static_cast<uint64_t>(WebCore::MediaSessionReadyState::Havemetadata),
            static_cast<uint64_t>(WebCore::MediaSessionReadyState::Havecurrentdata),
            static_cast<uint64_t>(WebCore::MediaSessionReadyState::Havefuturedata),
            static_cast<uint64_t>(WebCore::MediaSessionReadyState::Haveenoughdata),
        } },
#endif
        { "WebCore::RTCErrorDetailType"_s, sizeof(WebCore::RTCErrorDetailType), false, {
            static_cast<uint64_t>(WebCore::RTCErrorDetailType::DataChannelFailure),
            static_cast<uint64_t>(WebCore::RTCErrorDetailType::DtlsFailure),
            static_cast<uint64_t>(WebCore::RTCErrorDetailType::FingerprintFailure),
            static_cast<uint64_t>(WebCore::RTCErrorDetailType::SctpFailure),
            static_cast<uint64_t>(WebCore::RTCErrorDetailType::SdpSyntaxError),
        } },
        { "WebCore::NotificationEventType"_s, sizeof(WebCore::NotificationEventType), false, {
            0, 1
        } },
        { "WebCore::PermissionName"_s, sizeof(WebCore::PermissionName), false, {
            static_cast<uint64_t>(WebCore::PermissionName::Accelerometer),
            static_cast<uint64_t>(WebCore::PermissionName::BackgroundFetch),
            static_cast<uint64_t>(WebCore::PermissionName::Bluetooth),
            static_cast<uint64_t>(WebCore::PermissionName::Camera),
            static_cast<uint64_t>(WebCore::PermissionName::DisplayCapture),
            static_cast<uint64_t>(WebCore::PermissionName::Geolocation),
            static_cast<uint64_t>(WebCore::PermissionName::Gyroscope),
            static_cast<uint64_t>(WebCore::PermissionName::Magnetometer),
            static_cast<uint64_t>(WebCore::PermissionName::Microphone),
            static_cast<uint64_t>(WebCore::PermissionName::Midi),
            static_cast<uint64_t>(WebCore::PermissionName::Nfc),
            static_cast<uint64_t>(WebCore::PermissionName::Notifications),
            static_cast<uint64_t>(WebCore::PermissionName::Push),
            static_cast<uint64_t>(WebCore::PermissionName::ScreenWakeLock),
            static_cast<uint64_t>(WebCore::PermissionName::SpeakerSelection),
        } },
        { "WebCore::PermissionQuerySource"_s, sizeof(WebCore::PermissionQuerySource), false, {
            static_cast<uint64_t>(WebCore::PermissionQuerySource::Window),
            static_cast<uint64_t>(WebCore::PermissionQuerySource::DedicatedWorker),
            static_cast<uint64_t>(WebCore::PermissionQuerySource::SharedWorker),
            static_cast<uint64_t>(WebCore::PermissionQuerySource::ServiceWorker),
        } },
        { "WebCore::PermissionState"_s, sizeof(WebCore::PermissionState), false, {
            static_cast<uint64_t>(WebCore::PermissionState::Granted),
            static_cast<uint64_t>(WebCore::PermissionState::Denied),
            static_cast<uint64_t>(WebCore::PermissionState::Prompt),
        } },
#if ENABLE(SERVICE_WORKER)
        { "WebCore::PushPermissionState"_s, sizeof(WebCore::PushPermissionState), false, {
            static_cast<uint64_t>(WebCore::PushPermissionState::Denied),
            static_cast<uint64_t>(WebCore::PushPermissionState::Granted),
            static_cast<uint64_t>(WebCore::PushPermissionState::Prompt),
        } },
#endif
        { "WebCore::AutofillFieldName"_s, sizeof(WebCore::AutofillFieldName), false, {
            static_cast<uint64_t>(WebCore::AutofillFieldName::None),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Name),
            static_cast<uint64_t>(WebCore::AutofillFieldName::HonorificPrefix),
            static_cast<uint64_t>(WebCore::AutofillFieldName::GivenName),
            static_cast<uint64_t>(WebCore::AutofillFieldName::AdditionalName),
            static_cast<uint64_t>(WebCore::AutofillFieldName::FamilyName),
            static_cast<uint64_t>(WebCore::AutofillFieldName::HonorificSuffix),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Nickname),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Username),
            static_cast<uint64_t>(WebCore::AutofillFieldName::NewPassword),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CurrentPassword),
            static_cast<uint64_t>(WebCore::AutofillFieldName::OrganizationTitle),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Organization),
            static_cast<uint64_t>(WebCore::AutofillFieldName::StreetAddress),
            static_cast<uint64_t>(WebCore::AutofillFieldName::AddressLine1),
            static_cast<uint64_t>(WebCore::AutofillFieldName::AddressLine2),
            static_cast<uint64_t>(WebCore::AutofillFieldName::AddressLine3),
            static_cast<uint64_t>(WebCore::AutofillFieldName::AddressLevel4),
            static_cast<uint64_t>(WebCore::AutofillFieldName::AddressLevel3),
            static_cast<uint64_t>(WebCore::AutofillFieldName::AddressLevel2),
            static_cast<uint64_t>(WebCore::AutofillFieldName::AddressLevel1),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Country),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CountryName),
            static_cast<uint64_t>(WebCore::AutofillFieldName::PostalCode),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CcName),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CcGivenName),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CcAdditionalName),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CcFamilyName),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CcNumber),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CcExp),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CcExpMonth),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CcExpYear),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CcCsc),
            static_cast<uint64_t>(WebCore::AutofillFieldName::CcType),
            static_cast<uint64_t>(WebCore::AutofillFieldName::TransactionCurrency),
            static_cast<uint64_t>(WebCore::AutofillFieldName::TransactionAmount),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Language),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Bday),
            static_cast<uint64_t>(WebCore::AutofillFieldName::BdayDay),
            static_cast<uint64_t>(WebCore::AutofillFieldName::BdayMonth),
            static_cast<uint64_t>(WebCore::AutofillFieldName::BdayYear),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Sex),
            static_cast<uint64_t>(WebCore::AutofillFieldName::URL),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Photo),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Tel),
            static_cast<uint64_t>(WebCore::AutofillFieldName::TelCountryCode),
            static_cast<uint64_t>(WebCore::AutofillFieldName::TelNational),
            static_cast<uint64_t>(WebCore::AutofillFieldName::TelAreaCode),
            static_cast<uint64_t>(WebCore::AutofillFieldName::TelLocal),
            static_cast<uint64_t>(WebCore::AutofillFieldName::TelLocalPrefix),
            static_cast<uint64_t>(WebCore::AutofillFieldName::TelLocalSuffix),
            static_cast<uint64_t>(WebCore::AutofillFieldName::TelExtension),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Email),
            static_cast<uint64_t>(WebCore::AutofillFieldName::Impp),
            static_cast<uint64_t>(WebCore::AutofillFieldName::WebAuthn),
        } },
        { "WebCore::NonAutofillCredentialType"_s, sizeof(WebCore::NonAutofillCredentialType), false, {
            0, 1
        } },
        { "WebCore::EnterKeyHint"_s, sizeof(WebCore::EnterKeyHint), false, {
            static_cast<uint64_t>(WebCore::EnterKeyHint::Unspecified),
            static_cast<uint64_t>(WebCore::EnterKeyHint::Enter),
            static_cast<uint64_t>(WebCore::EnterKeyHint::Done),
            static_cast<uint64_t>(WebCore::EnterKeyHint::Go),
            static_cast<uint64_t>(WebCore::EnterKeyHint::Next),
            static_cast<uint64_t>(WebCore::EnterKeyHint::Previous),
            static_cast<uint64_t>(WebCore::EnterKeyHint::Search),
            static_cast<uint64_t>(WebCore::EnterKeyHint::Send),
        } },
        { "WebCore::DownloadableBinaryFontAllowedTypes"_s, sizeof(WebCore::DownloadableBinaryFontAllowedTypes), false, {
            static_cast<uint64_t>(WebCore::DownloadableBinaryFontAllowedTypes::Any),
            static_cast<uint64_t>(WebCore::DownloadableBinaryFontAllowedTypes::Restricted),
            static_cast<uint64_t>(WebCore::DownloadableBinaryFontAllowedTypes::None),
        } },
        { "WebCore::LoadSchedulingMode"_s, sizeof(WebCore::LoadSchedulingMode), false, {
            static_cast<uint64_t>(WebCore::LoadSchedulingMode::Direct),
            static_cast<uint64_t>(WebCore::LoadSchedulingMode::Prioritized),
        } },
        { "WebCore::ServiceWorkersMode"_s, sizeof(WebCore::ServiceWorkersMode), false, {
            static_cast<uint64_t>(WebCore::ServiceWorkersMode::All),
            static_cast<uint64_t>(WebCore::ServiceWorkersMode::None),
            static_cast<uint64_t>(WebCore::ServiceWorkersMode::Only),
        } },
        { "WebCore::ShouldTreatAsContinuingLoad"_s, sizeof(WebCore::ShouldTreatAsContinuingLoad), false, {
            static_cast<uint64_t>(WebCore::ShouldTreatAsContinuingLoad::No),
            static_cast<uint64_t>(WebCore::ShouldTreatAsContinuingLoad::YesAfterNavigationPolicyDecision),
            static_cast<uint64_t>(WebCore::ShouldTreatAsContinuingLoad::YesAfterProvisionalLoadStarted),
        } },
        { "WebCore::ContentSecurityPolicyModeForExtension"_s, sizeof(WebCore::ContentSecurityPolicyModeForExtension), false, {
            static_cast<uint64_t>(WebCore::ContentSecurityPolicyModeForExtension::None),
            static_cast<uint64_t>(WebCore::ContentSecurityPolicyModeForExtension::ManifestV2),
            static_cast<uint64_t>(WebCore::ContentSecurityPolicyModeForExtension::ManifestV3),
        } },
        { "WebCore::MediaProducerMediaCaptureKind"_s, sizeof(WebCore::MediaProducerMediaCaptureKind), false, {
            static_cast<uint64_t>(WebCore::MediaProducerMediaCaptureKind::Microphone),
            static_cast<uint64_t>(WebCore::MediaProducerMediaCaptureKind::Camera),
            static_cast<uint64_t>(WebCore::MediaProducerMediaCaptureKind::Display),
            static_cast<uint64_t>(WebCore::MediaProducerMediaCaptureKind::SystemAudio),
            static_cast<uint64_t>(WebCore::MediaProducerMediaCaptureKind::EveryKind),
        } },
        { "WebCore::ScreenOrientationType"_s, sizeof(WebCore::ScreenOrientationType), false, {
            static_cast<uint64_t>(WebCore::ScreenOrientationType::PortraitPrimary),
            static_cast<uint64_t>(WebCore::ScreenOrientationType::PortraitSecondary),
            static_cast<uint64_t>(WebCore::ScreenOrientationType::LandscapePrimary),
            static_cast<uint64_t>(WebCore::ScreenOrientationType::LandscapeSecondary),
        } },
        { "WebCore::StorageBlockingPolicy"_s, sizeof(WebCore::StorageBlockingPolicy), false, {
            static_cast<uint64_t>(WebCore::StorageBlockingPolicy::AllowAll),
            static_cast<uint64_t>(WebCore::StorageBlockingPolicy::BlockThirdParty),
            static_cast<uint64_t>(WebCore::StorageBlockingPolicy::BlockAll),
        } },
#if HAVE(TRANSLATION_UI_SERVICES) && ENABLE(CONTEXT_MENUS)
        { "WebCore::TranslationContextMenuMode"_s, sizeof(WebCore::TranslationContextMenuMode), false, {
            0, 1
        } },
#endif
#if HAVE(TRANSLATION_UI_SERVICES) && ENABLE(CONTEXT_MENUS)
        { "WebCore::TranslationContextMenuSource"_s, sizeof(WebCore::TranslationContextMenuSource), false, {
            0, 1
        } },
#endif
#if USE(APPKIT)
        { "WebCore::AppKitControlSystemImageType"_s, sizeof(WebCore::AppKitControlSystemImageType), false, {
            static_cast<uint64_t>(WebCore::AppKitControlSystemImageType::ScrollbarTrackCorner),
        } },
#endif
        { "WebCore::ListStyleType::Type"_s, sizeof(WebCore::ListStyleType::Type), false, {
            static_cast<uint64_t>(WebCore::ListStyleType::Type::CounterStyle),
            static_cast<uint64_t>(WebCore::ListStyleType::Type::String),
            static_cast<uint64_t>(WebCore::ListStyleType::Type::None),
        } },
        { "WebCore::ScrollIsAnimated"_s, sizeof(WebCore::ScrollIsAnimated), false, {
            0, 1
        } },
        { "WebCore::ScrollGranularity"_s, sizeof(WebCore::ScrollGranularity), false, {
            static_cast<uint64_t>(WebCore::ScrollGranularity::Line),
            static_cast<uint64_t>(WebCore::ScrollGranularity::Page),
            static_cast<uint64_t>(WebCore::ScrollGranularity::Document),
            static_cast<uint64_t>(WebCore::ScrollGranularity::Pixel),
        } },
        { "WebCore::IndexedDB::KeyType"_s, sizeof(WebCore::IndexedDB::KeyType), false, {
            static_cast<uint64_t>(WebCore::IndexedDB::KeyType::Max),
            static_cast<uint64_t>(WebCore::IndexedDB::KeyType::Invalid),
            static_cast<uint64_t>(WebCore::IndexedDB::KeyType::Array),
            static_cast<uint64_t>(WebCore::IndexedDB::KeyType::Binary),
            static_cast<uint64_t>(WebCore::IndexedDB::KeyType::String),
            static_cast<uint64_t>(WebCore::IndexedDB::KeyType::Date),
            static_cast<uint64_t>(WebCore::IndexedDB::KeyType::Number),
            static_cast<uint64_t>(WebCore::IndexedDB::KeyType::Min),
        } },
        { "WebCore::IndexedDB::CursorDirection"_s, sizeof(WebCore::IndexedDB::CursorDirection), false, {
            static_cast<uint64_t>(WebCore::IndexedDB::CursorDirection::Next),
            static_cast<uint64_t>(WebCore::IndexedDB::CursorDirection::Nextunique),
            static_cast<uint64_t>(WebCore::IndexedDB::CursorDirection::Prev),
            static_cast<uint64_t>(WebCore::IndexedDB::CursorDirection::Prevunique),
        } },
        { "WebCore::IndexedDB::ObjectStoreOverwriteMode"_s, sizeof(WebCore::IndexedDB::ObjectStoreOverwriteMode), false, {
            static_cast<uint64_t>(WebCore::IndexedDB::ObjectStoreOverwriteMode::Overwrite),
            static_cast<uint64_t>(WebCore::IndexedDB::ObjectStoreOverwriteMode::OverwriteForCursor),
            static_cast<uint64_t>(WebCore::IndexedDB::ObjectStoreOverwriteMode::NoOverwrite),
        } },
        { "WebCore::IndexedDB::RequestType"_s, sizeof(WebCore::IndexedDB::RequestType), false, {
            static_cast<uint64_t>(WebCore::IndexedDB::RequestType::Open),
            static_cast<uint64_t>(WebCore::IndexedDB::RequestType::Delete),
            static_cast<uint64_t>(WebCore::IndexedDB::RequestType::Other),
        } },
        { "WebCore::CubicBezierTimingFunction::TimingFunctionPreset"_s, sizeof(WebCore::CubicBezierTimingFunction::TimingFunctionPreset), false, {
            static_cast<uint64_t>(WebCore::CubicBezierTimingFunction::TimingFunctionPreset::Ease),
            static_cast<uint64_t>(WebCore::CubicBezierTimingFunction::TimingFunctionPreset::EaseIn),
            static_cast<uint64_t>(WebCore::CubicBezierTimingFunction::TimingFunctionPreset::EaseOut),
            static_cast<uint64_t>(WebCore::CubicBezierTimingFunction::TimingFunctionPreset::EaseInOut),
            static_cast<uint64_t>(WebCore::CubicBezierTimingFunction::TimingFunctionPreset::Custom),
        } },
        { "WebCore::StepsTimingFunction::StepPosition"_s, sizeof(WebCore::StepsTimingFunction::StepPosition), false, {
            static_cast<uint64_t>(WebCore::StepsTimingFunction::StepPosition::JumpStart),
            static_cast<uint64_t>(WebCore::StepsTimingFunction::StepPosition::JumpEnd),
            static_cast<uint64_t>(WebCore::StepsTimingFunction::StepPosition::JumpNone),
            static_cast<uint64_t>(WebCore::StepsTimingFunction::StepPosition::JumpBoth),
            static_cast<uint64_t>(WebCore::StepsTimingFunction::StepPosition::Start),
            static_cast<uint64_t>(WebCore::StepsTimingFunction::StepPosition::End),
        } },
        { "WebCore::NavigatorAPIsAccessed"_s, sizeof(WebCore::NavigatorAPIsAccessed), true, {
            static_cast<uint64_t>(WebCore::NavigatorAPIsAccessed::AppVersion),
            static_cast<uint64_t>(WebCore::NavigatorAPIsAccessed::UserAgent),
            static_cast<uint64_t>(WebCore::NavigatorAPIsAccessed::Plugins),
            static_cast<uint64_t>(WebCore::NavigatorAPIsAccessed::MimeTypes),
            static_cast<uint64_t>(WebCore::NavigatorAPIsAccessed::CookieEnabled),
        } },
        { "WebCore::ScreenAPIsAccessed"_s, sizeof(WebCore::ScreenAPIsAccessed), true, {
            static_cast<uint64_t>(WebCore::ScreenAPIsAccessed::Height),
            static_cast<uint64_t>(WebCore::ScreenAPIsAccessed::Width),
            static_cast<uint64_t>(WebCore::ScreenAPIsAccessed::ColorDepth),
            static_cast<uint64_t>(WebCore::ScreenAPIsAccessed::AvailLeft),
            static_cast<uint64_t>(WebCore::ScreenAPIsAccessed::AvailTop),
            static_cast<uint64_t>(WebCore::ScreenAPIsAccessed::AvailHeight),
            static_cast<uint64_t>(WebCore::ScreenAPIsAccessed::AvailWidth),
        } },
        { "WebCore::ViewportFit"_s, sizeof(WebCore::ViewportFit), false, {
            static_cast<uint64_t>(WebCore::ViewportFit::Auto),
            static_cast<uint64_t>(WebCore::ViewportFit::Contain),
            static_cast<uint64_t>(WebCore::ViewportFit::Cover),
        } },
        { "WebCore::ShareDataOriginator"_s, sizeof(WebCore::ShareDataOriginator), false, {
            0, 1
        } },
        { "WebCore::PCM::AttributionEphemeral"_s, sizeof(WebCore::PCM::AttributionEphemeral), false, {
            0, 1
        } },
        { "WebCore::PCM::WasSent"_s, sizeof(WebCore::PCM::WasSent), false, {
            0, 1
        } },
#if ENABLE(APPLE_PAY)
        { "WebCore::ApplePayLineItem::Type"_s, sizeof(WebCore::ApplePayLineItem::Type), false, {
            0, 1
        } },
#endif
#if ENABLE(APPLE_PAY)
        { "WebCore::ApplePayLogoStyle"_s, sizeof(WebCore::ApplePayLogoStyle), false, {
            0, 1
        } },
#endif
#if ENABLE(APPLE_PAY)
        { "WebCore::ApplePayErrorContactField"_s, sizeof(WebCore::ApplePayErrorContactField), false, {
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::PhoneNumber),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::EmailAddress),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::Name),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::PhoneticName),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::PostalAddress),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::AddressLines),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::SubLocality),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::Locality),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::PostalCode),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::SubAdministrativeArea),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::AdministrativeArea),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::Country),
            static_cast<uint64_t>(WebCore::ApplePayErrorContactField::CountryCode),
        } },
#endif
#if ENABLE(APPLE_PAY)
        { "WebCore::ApplePayErrorCode"_s, sizeof(WebCore::ApplePayErrorCode), false, {
            static_cast<uint64_t>(WebCore::ApplePayErrorCode::Unknown),
            static_cast<uint64_t>(WebCore::ApplePayErrorCode::ShippingContactInvalid),
            static_cast<uint64_t>(WebCore::ApplePayErrorCode::BillingContactInvalid),
            static_cast<uint64_t>(WebCore::ApplePayErrorCode::AddressUnserviceable),
#if ENABLE(APPLE_PAY_COUPON_CODE)
            static_cast<uint64_t>(WebCore::ApplePayErrorCode::CouponCodeInvalid),
#endif
#if ENABLE(APPLE_PAY_COUPON_CODE)
            static_cast<uint64_t>(WebCore::ApplePayErrorCode::CouponCodeExpired),
#endif
        } },
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
        { "WebCore::ApplePaySetupFeatureType"_s, sizeof(WebCore::ApplePaySetupFeatureType), false, {
            0, 1
        } },
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
        { "WebCore::ApplePayInstallmentItemType"_s, sizeof(WebCore::ApplePayInstallmentItemType), false, {
            static_cast<uint64_t>(WebCore::ApplePayInstallmentItemType::Generic),
            static_cast<uint64_t>(WebCore::ApplePayInstallmentItemType::Phone),
            static_cast<uint64_t>(WebCore::ApplePayInstallmentItemType::Pad),
            static_cast<uint64_t>(WebCore::ApplePayInstallmentItemType::Watch),
            static_cast<uint64_t>(WebCore::ApplePayInstallmentItemType::Mac),
        } },
#endif
#if ENABLE(APPLE_PAY_INSTALLMENTS)
        { "WebCore::ApplePayInstallmentRetailChannel"_s, sizeof(WebCore::ApplePayInstallmentRetailChannel), false, {
            static_cast<uint64_t>(WebCore::ApplePayInstallmentRetailChannel::Unknown),
            static_cast<uint64_t>(WebCore::ApplePayInstallmentRetailChannel::App),
            static_cast<uint64_t>(WebCore::ApplePayInstallmentRetailChannel::Web),
            static_cast<uint64_t>(WebCore::ApplePayInstallmentRetailChannel::InStore),
        } },
#endif
        { "WebCore::ScreenOrientationLockType"_s, sizeof(WebCore::ScreenOrientationLockType), false, {
            static_cast<uint64_t>(WebCore::ScreenOrientationLockType::Any),
            static_cast<uint64_t>(WebCore::ScreenOrientationLockType::Natural),
            static_cast<uint64_t>(WebCore::ScreenOrientationLockType::Landscape),
            static_cast<uint64_t>(WebCore::ScreenOrientationLockType::Portrait),
            static_cast<uint64_t>(WebCore::ScreenOrientationLockType::PortraitPrimary),
            static_cast<uint64_t>(WebCore::ScreenOrientationLockType::PortraitSecondary),
            static_cast<uint64_t>(WebCore::ScreenOrientationLockType::LandscapePrimary),
            static_cast<uint64_t>(WebCore::ScreenOrientationLockType::LandscapeSecondary),
        } },
#if ENABLE(APPLICATION_MANIFEST)
        { "WebCore::ApplicationManifest::Display"_s, sizeof(WebCore::ApplicationManifest::Display), false, {
            static_cast<uint64_t>(WebCore::ApplicationManifest::Display::Browser),
            static_cast<uint64_t>(WebCore::ApplicationManifest::Display::MinimalUI),
            static_cast<uint64_t>(WebCore::ApplicationManifest::Display::Standalone),
            static_cast<uint64_t>(WebCore::ApplicationManifest::Display::Fullscreen),
        } },
#endif
#if ENABLE(APPLICATION_MANIFEST)
        { "WebCore::ApplicationManifest::Icon::Purpose"_s, sizeof(WebCore::ApplicationManifest::Icon::Purpose), true, {
            static_cast<uint64_t>(WebCore::ApplicationManifest::Icon::Purpose::Any),
            static_cast<uint64_t>(WebCore::ApplicationManifest::Icon::Purpose::Monochrome),
            static_cast<uint64_t>(WebCore::ApplicationManifest::Icon::Purpose::Maskable),
        } },
#endif
        { "WebCore::DOMCacheEngine::Error"_s, sizeof(WebCore::DOMCacheEngine::Error), false, {
            static_cast<uint64_t>(WebCore::DOMCacheEngine::Error::NotImplemented),
            static_cast<uint64_t>(WebCore::DOMCacheEngine::Error::ReadDisk),
            static_cast<uint64_t>(WebCore::DOMCacheEngine::Error::WriteDisk),
            static_cast<uint64_t>(WebCore::DOMCacheEngine::Error::QuotaExceeded),
            static_cast<uint64_t>(WebCore::DOMCacheEngine::Error::Internal),
            static_cast<uint64_t>(WebCore::DOMCacheEngine::Error::Stopped),
            static_cast<uint64_t>(WebCore::DOMCacheEngine::Error::CORP),
        } },
#if ENABLE(WEB_CODECS)
        { "WebCore::WebCodecsEncodedVideoChunkType"_s, sizeof(WebCore::WebCodecsEncodedVideoChunkType), false, {
            0, 1
        } },
#endif
        { "WebCore::SpeechRecognitionErrorType"_s, sizeof(WebCore::SpeechRecognitionErrorType), false, {
            static_cast<uint64_t>(WebCore::SpeechRecognitionErrorType::NoSpeech),
            static_cast<uint64_t>(WebCore::SpeechRecognitionErrorType::Aborted),
            static_cast<uint64_t>(WebCore::SpeechRecognitionErrorType::AudioCapture),
            static_cast<uint64_t>(WebCore::SpeechRecognitionErrorType::Network),
            static_cast<uint64_t>(WebCore::SpeechRecognitionErrorType::NotAllowed),
            static_cast<uint64_t>(WebCore::SpeechRecognitionErrorType::ServiceNotAllowed),
            static_cast<uint64_t>(WebCore::SpeechRecognitionErrorType::BadGrammar),
            static_cast<uint64_t>(WebCore::SpeechRecognitionErrorType::LanguageNotSupported),
        } },
#if ENABLE(WEB_AUTHN)
        { "WebCore::AttestationConveyancePreference"_s, sizeof(WebCore::AttestationConveyancePreference), false, {
            static_cast<uint64_t>(WebCore::AttestationConveyancePreference::None),
            static_cast<uint64_t>(WebCore::AttestationConveyancePreference::Indirect),
            static_cast<uint64_t>(WebCore::AttestationConveyancePreference::Direct),
            static_cast<uint64_t>(WebCore::AttestationConveyancePreference::Enterprise),
        } },
#endif
        { "WebCore::Cookie::SameSitePolicy"_s, sizeof(WebCore::Cookie::SameSitePolicy), false, {
            static_cast<uint64_t>(WebCore::Cookie::SameSitePolicy::None),
            static_cast<uint64_t>(WebCore::Cookie::SameSitePolicy::Lax),
            static_cast<uint64_t>(WebCore::Cookie::SameSitePolicy::Strict),
        } },
        { "WebCore::RenderingMode"_s, sizeof(WebCore::RenderingMode), false, {
            0, 1
        } },
        { "WebCore::RenderingPurpose"_s, sizeof(WebCore::RenderingPurpose), false, {
            static_cast<uint64_t>(WebCore::RenderingPurpose::Unspecified),
            static_cast<uint64_t>(WebCore::RenderingPurpose::Canvas),
            static_cast<uint64_t>(WebCore::RenderingPurpose::DOM),
            static_cast<uint64_t>(WebCore::RenderingPurpose::LayerBacking),
            static_cast<uint64_t>(WebCore::RenderingPurpose::Snapshot),
            static_cast<uint64_t>(WebCore::RenderingPurpose::ShareableSnapshot),
            static_cast<uint64_t>(WebCore::RenderingPurpose::ShareableLocalSnapshot),
            static_cast<uint64_t>(WebCore::RenderingPurpose::MediaPainting),
        } },
        { "WebCore::RotationDirection"_s, sizeof(WebCore::RotationDirection), false, {
            0, 1
        } },
#if ENABLE(CONTENT_FILTERING)
        { "WebCore::MockContentFilterSettings::DecisionPoint"_s, sizeof(WebCore::MockContentFilterSettings::DecisionPoint), false, {
            static_cast<uint64_t>(WebCore::MockContentFilterSettings::DecisionPoint::AfterWillSendRequest),
            static_cast<uint64_t>(WebCore::MockContentFilterSettings::DecisionPoint::AfterRedirect),
            static_cast<uint64_t>(WebCore::MockContentFilterSettings::DecisionPoint::AfterResponse),
            static_cast<uint64_t>(WebCore::MockContentFilterSettings::DecisionPoint::AfterAddData),
            static_cast<uint64_t>(WebCore::MockContentFilterSettings::DecisionPoint::AfterFinishedAddingData),
            static_cast<uint64_t>(WebCore::MockContentFilterSettings::DecisionPoint::Never),
        } },
#endif
#if ENABLE(CONTENT_FILTERING)
        { "WebCore::MockContentFilterSettings::Decision"_s, sizeof(WebCore::MockContentFilterSettings::Decision), false, {
            0, 1
        } },
#endif
        { "WebCore::AutoplayEvent"_s, sizeof(WebCore::AutoplayEvent), false, {
            static_cast<uint64_t>(WebCore::AutoplayEvent::DidPreventMediaFromPlaying),
            static_cast<uint64_t>(WebCore::AutoplayEvent::DidPlayMediaWithUserGesture),
            static_cast<uint64_t>(WebCore::AutoplayEvent::DidAutoplayMediaPastThresholdWithoutUserInterference),
            static_cast<uint64_t>(WebCore::AutoplayEvent::UserDidInterfereWithPlayback),
        } },
        { "WebCore::InputMode"_s, sizeof(WebCore::InputMode), false, {
            static_cast<uint64_t>(WebCore::InputMode::Unspecified),
            static_cast<uint64_t>(WebCore::InputMode::None),
            static_cast<uint64_t>(WebCore::InputMode::Text),
            static_cast<uint64_t>(WebCore::InputMode::Telephone),
            static_cast<uint64_t>(WebCore::InputMode::Url),
            static_cast<uint64_t>(WebCore::InputMode::Email),
            static_cast<uint64_t>(WebCore::InputMode::Numeric),
            static_cast<uint64_t>(WebCore::InputMode::Decimal),
            static_cast<uint64_t>(WebCore::InputMode::Search),
        } },
        { "WebCore::NotificationDirection"_s, sizeof(WebCore::NotificationDirection), false, {
            static_cast<uint64_t>(WebCore::NotificationDirection::Auto),
            static_cast<uint64_t>(WebCore::NotificationDirection::Ltr),
            static_cast<uint64_t>(WebCore::NotificationDirection::Rtl),
        } },
        { "WebCore::IndexedDB::GetAllType"_s, sizeof(WebCore::IndexedDB::GetAllType), false, {
            0, 1
        } },
        { "WebCore::WorkerType"_s, sizeof(WebCore::WorkerType), false, {
            0, 1
        } },
        { "WebCore::StoredCredentialsPolicy"_s, sizeof(WebCore::StoredCredentialsPolicy), false, {
            static_cast<uint64_t>(WebCore::StoredCredentialsPolicy::DoNotUse),
            static_cast<uint64_t>(WebCore::StoredCredentialsPolicy::Use),
            static_cast<uint64_t>(WebCore::StoredCredentialsPolicy::EphemeralStateless),
        } },
        { "WebCore::ContentSniffingPolicy"_s, sizeof(WebCore::ContentSniffingPolicy), false, {
            0, 1
        } },
        { "WebCore::ContentEncodingSniffingPolicy"_s, sizeof(WebCore::ContentEncodingSniffingPolicy), false, {
            0, 1
        } },
        { "WebCore::ClientCredentialPolicy"_s, sizeof(WebCore::ClientCredentialPolicy), false, {
            0, 1
        } },
        { "WebCore::ShouldRelaxThirdPartyCookieBlocking"_s, sizeof(WebCore::ShouldRelaxThirdPartyCookieBlocking), false, {
            0, 1
        } },
        { "WebCore::PreflightPolicy"_s, sizeof(WebCore::PreflightPolicy), false, {
            static_cast<uint64_t>(WebCore::PreflightPolicy::Consider),
            static_cast<uint64_t>(WebCore::PreflightPolicy::Force),
            static_cast<uint64_t>(WebCore::PreflightPolicy::Prevent),
        } },
        { "WTFLogChannelState"_s, sizeof(WTFLogChannelState), false, {
            static_cast<uint64_t>(WTFLogChannelState::Off),
            static_cast<uint64_t>(WTFLogChannelState::On),
            static_cast<uint64_t>(WTFLogChannelState::OnWithAccumulation),
        } },
        { "WebCore::ScrollSnapStrictness"_s, sizeof(WebCore::ScrollSnapStrictness), false, {
            static_cast<uint64_t>(WebCore::ScrollSnapStrictness::None),
            static_cast<uint64_t>(WebCore::ScrollSnapStrictness::Proximity),
            static_cast<uint64_t>(WebCore::ScrollSnapStrictness::Mandatory),
        } },
        { "WebCore::LengthType"_s, sizeof(WebCore::LengthType), false, {
            static_cast<uint64_t>(WebCore::LengthType::Auto),
            static_cast<uint64_t>(WebCore::LengthType::Relative),
            static_cast<uint64_t>(WebCore::LengthType::Percent),
            static_cast<uint64_t>(WebCore::LengthType::Fixed),
            static_cast<uint64_t>(WebCore::LengthType::Intrinsic),
            static_cast<uint64_t>(WebCore::LengthType::MinIntrinsic),
            static_cast<uint64_t>(WebCore::LengthType::MinContent),
            static_cast<uint64_t>(WebCore::LengthType::MaxContent),
            static_cast<uint64_t>(WebCore::LengthType::FillAvailable),
            static_cast<uint64_t>(WebCore::LengthType::FitContent),
            static_cast<uint64_t>(WebCore::LengthType::Calculated),
            static_cast<uint64_t>(WebCore::LengthType::Undefined),
        } },
        { "WebCore::OverscrollBehavior"_s, sizeof(WebCore::OverscrollBehavior), false, {
            static_cast<uint64_t>(WebCore::OverscrollBehavior::Auto),
            static_cast<uint64_t>(WebCore::OverscrollBehavior::Contain),
            static_cast<uint64_t>(WebCore::OverscrollBehavior::None),
        } },
        { "WebCore::ScrollPinningBehavior"_s, sizeof(WebCore::ScrollPinningBehavior), false, {
            static_cast<uint64_t>(WebCore::ScrollPinningBehavior::DoNotPin),
            static_cast<uint64_t>(WebCore::ScrollPinningBehavior::PinToTop),
            static_cast<uint64_t>(WebCore::ScrollPinningBehavior::PinToBottom),
        } },
        { "WebCore::WheelScrollGestureState"_s, sizeof(WebCore::WheelScrollGestureState), false, {
            static_cast<uint64_t>(WebCore::WheelScrollGestureState::Blocking),
            static_cast<uint64_t>(WebCore::WheelScrollGestureState::NonBlocking),
        } },
        { "WebCore::DiagnosticLoggingDomain"_s, sizeof(WebCore::DiagnosticLoggingDomain), false, {
            static_cast<uint64_t>(WebCore::DiagnosticLoggingDomain::Media),
        } },
#if !USE(CG)
        { "WebCore::PlatformColorSpace::Name"_s, sizeof(WebCore::PlatformColorSpace::Name), false, {
            static_cast<uint64_t>(WebCore::PlatformColorSpace::Name::SRGB),
#if ENABLE(DESTINATION_COLOR_SPACE_LINEAR_SRGB)
            static_cast<uint64_t>(WebCore::PlatformColorSpace::Name::LinearSRGB),
#endif
#if ENABLE(DESTINATION_COLOR_SPACE_DISPLAY_P3)
            static_cast<uint64_t>(WebCore::PlatformColorSpace::Name::DisplayP3),
#endif
        } },
#endif
        { "WebCore::CompositionUnderlineColor"_s, sizeof(WebCore::CompositionUnderlineColor), false, {
            0, 1
        } },
        { "WebCore::MediaCaptureType"_s, sizeof(WebCore::MediaCaptureType), false, {
            static_cast<uint64_t>(WebCore::MediaCaptureType::MediaCaptureTypeNone),
            static_cast<uint64_t>(WebCore::MediaCaptureType::MediaCaptureTypeUser),
            static_cast<uint64_t>(WebCore::MediaCaptureType::MediaCaptureTypeEnvironment),
        } },
        { "WebCore::TextCheckingProcessType"_s, sizeof(WebCore::TextCheckingProcessType), false, {
            0, 1
        } },
        { "WebCore::MediaStreamRequest::Type"_s, sizeof(WebCore::MediaStreamRequest::Type), false, {
            static_cast<uint64_t>(WebCore::MediaStreamRequest::Type::UserMedia),
            static_cast<uint64_t>(WebCore::MediaStreamRequest::Type::DisplayMedia),
            static_cast<uint64_t>(WebCore::MediaStreamRequest::Type::DisplayMediaWithAudio),
        } },
        { "WebCore::NetworkTransactionInformation::Type"_s, sizeof(WebCore::NetworkTransactionInformation::Type), false, {
            0, 1
        } },
#if ENABLE(WEB_AUTHN)
        { "WebCore::AuthenticatorTransport"_s, sizeof(WebCore::AuthenticatorTransport), false, {
            static_cast<uint64_t>(WebCore::AuthenticatorTransport::Usb),
            static_cast<uint64_t>(WebCore::AuthenticatorTransport::Nfc),
            static_cast<uint64_t>(WebCore::AuthenticatorTransport::Ble),
            static_cast<uint64_t>(WebCore::AuthenticatorTransport::Internal),
            static_cast<uint64_t>(WebCore::AuthenticatorTransport::Cable),
            static_cast<uint64_t>(WebCore::AuthenticatorTransport::Hybrid),
            static_cast<uint64_t>(WebCore::AuthenticatorTransport::SmartCard),
        } },
#endif
#if ENABLE(WEB_AUTHN)
        { "WebCore::PublicKeyCredentialType"_s, sizeof(WebCore::PublicKeyCredentialType), false, {
            0, 1
        } },
#endif
#if ENABLE(DATALIST_ELEMENT)
        { "WebCore::DataListSuggestionActivationType"_s, sizeof(WebCore::DataListSuggestionActivationType), false, {
            static_cast<uint64_t>(WebCore::DataListSuggestionActivationType::ControlClicked),
            static_cast<uint64_t>(WebCore::DataListSuggestionActivationType::IndicatorClicked),
            static_cast<uint64_t>(WebCore::DataListSuggestionActivationType::TextChanged),
        } },
#endif
        { "WebCore::AlphaPremultiplication"_s, sizeof(WebCore::AlphaPremultiplication), false, {
            static_cast<uint64_t>(WebCore::AlphaPremultiplication::Premultiplied),
            static_cast<uint64_t>(WebCore::AlphaPremultiplication::Unpremultiplied),
        } },
        { "WebCore::PixelFormat"_s, sizeof(WebCore::PixelFormat), false, {
            static_cast<uint64_t>(WebCore::PixelFormat::RGBA8),
            static_cast<uint64_t>(WebCore::PixelFormat::BGRX8),
            static_cast<uint64_t>(WebCore::PixelFormat::BGRA8),
            static_cast<uint64_t>(WebCore::PixelFormat::RGB10),
            static_cast<uint64_t>(WebCore::PixelFormat::RGB10A8),
        } },
        { "WebCore::EventTrackingRegions::EventType"_s, sizeof(WebCore::EventTrackingRegions::EventType), false, {
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Mousedown),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Mousemove),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Mouseup),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Mousewheel),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Pointerdown),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Pointerenter),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Pointerleave),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Pointermove),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Pointerout),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Pointerover),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Pointerup),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Touchend),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Touchforcechange),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Touchmove),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Touchstart),
            static_cast<uint64_t>(WebCore::EventTrackingRegions::EventType::Wheel),
        } },
        { "WebCore::HasInsecureContent"_s, sizeof(WebCore::HasInsecureContent), false, {
            0, 1
        } },
        { "WebCore::ScrollElasticity"_s, sizeof(WebCore::ScrollElasticity), false, {
            static_cast<uint64_t>(WebCore::ScrollElasticity::Automatic),
            static_cast<uint64_t>(WebCore::ScrollElasticity::None),
            static_cast<uint64_t>(WebCore::ScrollElasticity::Allowed),
        } },
        { "WebCore::ScrollbarMode"_s, sizeof(WebCore::ScrollbarMode), false, {
            static_cast<uint64_t>(WebCore::ScrollbarMode::Auto),
            static_cast<uint64_t>(WebCore::ScrollbarMode::AlwaysOff),
            static_cast<uint64_t>(WebCore::ScrollbarMode::AlwaysOn),
        } },
        { "WebCore::NativeScrollbarVisibility"_s, sizeof(WebCore::NativeScrollbarVisibility), false, {
            static_cast<uint64_t>(WebCore::NativeScrollbarVisibility::Visible),
            static_cast<uint64_t>(WebCore::NativeScrollbarVisibility::HiddenByStyle),
            static_cast<uint64_t>(WebCore::NativeScrollbarVisibility::ReplacedByCustomScrollbar),
        } },
        { "WebCore::ScrollbarWidth"_s, sizeof(WebCore::ScrollbarWidth), false, {
            static_cast<uint64_t>(WebCore::ScrollbarWidth::Auto),
            static_cast<uint64_t>(WebCore::ScrollbarWidth::Thin),
            static_cast<uint64_t>(WebCore::ScrollbarWidth::None),
        } },
        { "WebCore::WheelEventProcessingSteps"_s, sizeof(WebCore::WheelEventProcessingSteps), true, {
            static_cast<uint64_t>(WebCore::WheelEventProcessingSteps::AsyncScrolling),
            static_cast<uint64_t>(WebCore::WheelEventProcessingSteps::SynchronousScrolling),
            static_cast<uint64_t>(WebCore::WheelEventProcessingSteps::NonBlockingDOMEventDispatch),
            static_cast<uint64_t>(WebCore::WheelEventProcessingSteps::BlockingDOMEventDispatch),
        } },
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
        { "WebCore::GraphicsContextGLPowerPreference"_s, sizeof(WebCore::GraphicsContextGLPowerPreference), false, {
            static_cast<uint64_t>(WebCore::GraphicsContextGLPowerPreference::Default),
            static_cast<uint64_t>(WebCore::GraphicsContextGLPowerPreference::LowPower),
            static_cast<uint64_t>(WebCore::GraphicsContextGLPowerPreference::HighPerformance),
        } },
#endif
#if ENABLE(GPU_PROCESS) && ENABLE(WEBGL)
        { "WebCore::GraphicsContextGLWebGLVersion"_s, sizeof(WebCore::GraphicsContextGLWebGLVersion), false, {
            static_cast<uint64_t>(WebCore::GraphicsContextGLWebGLVersion::WebGL1),
            static_cast<uint64_t>(WebCore::GraphicsContextGLWebGLVersion::WebGL2),
        } },
#endif
        { "WebCore::BasicShapeCenterCoordinate::Direction"_s, sizeof(WebCore::BasicShapeCenterCoordinate::Direction), false, {
            0, 1
        } },
        { "WebCore::BasicShapeRadius::Type"_s, sizeof(WebCore::BasicShapeRadius::Type), false, {
            static_cast<uint64_t>(WebCore::BasicShapeRadius::Type::Value),
            static_cast<uint64_t>(WebCore::BasicShapeRadius::Type::ClosestSide),
            static_cast<uint64_t>(WebCore::BasicShapeRadius::Type::FarthestSide),
        } },
        { "WebCore::CSSBoxType"_s, sizeof(WebCore::CSSBoxType), false, {
            static_cast<uint64_t>(WebCore::CSSBoxType::BoxMissing),
            static_cast<uint64_t>(WebCore::CSSBoxType::MarginBox),
            static_cast<uint64_t>(WebCore::CSSBoxType::BorderBox),
            static_cast<uint64_t>(WebCore::CSSBoxType::PaddingBox),
            static_cast<uint64_t>(WebCore::CSSBoxType::ContentBox),
            static_cast<uint64_t>(WebCore::CSSBoxType::FillBox),
            static_cast<uint64_t>(WebCore::CSSBoxType::StrokeBox),
            static_cast<uint64_t>(WebCore::CSSBoxType::ViewBox),
        } },
        { "WebCore::RayPathOperation::Size"_s, sizeof(WebCore::RayPathOperation::Size), false, {
            static_cast<uint64_t>(WebCore::RayPathOperation::Size::ClosestSide),
            static_cast<uint64_t>(WebCore::RayPathOperation::Size::ClosestCorner),
            static_cast<uint64_t>(WebCore::RayPathOperation::Size::FarthestSide),
            static_cast<uint64_t>(WebCore::RayPathOperation::Size::FarthestCorner),
            static_cast<uint64_t>(WebCore::RayPathOperation::Size::Sides),
        } },
#if PLATFORM(IOS_FAMILY)
        { "WebCore::SelectionRenderingBehavior"_s, sizeof(WebCore::SelectionRenderingBehavior), false, {
            0, 1
        } },
#endif
#if ENABLE(WEB_AUTHN)
        { "WebCore::UserVerificationRequirement"_s, sizeof(WebCore::UserVerificationRequirement), false, {
            static_cast<uint64_t>(WebCore::UserVerificationRequirement::Required),
            static_cast<uint64_t>(WebCore::UserVerificationRequirement::Preferred),
            static_cast<uint64_t>(WebCore::UserVerificationRequirement::Discouraged),
        } },
#endif
#if ENABLE(WEB_AUTHN)
        { "WebCore::ResidentKeyRequirement"_s, sizeof(WebCore::ResidentKeyRequirement), false, {
            static_cast<uint64_t>(WebCore::ResidentKeyRequirement::Required),
            static_cast<uint64_t>(WebCore::ResidentKeyRequirement::Preferred),
            static_cast<uint64_t>(WebCore::ResidentKeyRequirement::Discouraged),
        } },
#endif
#if ENABLE(WEB_AUTHN)
        { "WebCore::AuthenticatorAttachment"_s, sizeof(WebCore::AuthenticatorAttachment), false, {
            static_cast<uint64_t>(WebCore::AuthenticatorAttachment::Platform),
            static_cast<uint64_t>(WebCore::AuthenticatorAttachment::CrossPlatform),
        } },
#endif
        { "WebCore::ResourceRequestCachePolicy"_s, sizeof(WebCore::ResourceRequestCachePolicy), false, {
            static_cast<uint64_t>(WebCore::ResourceRequestCachePolicy::UseProtocolCachePolicy),
            static_cast<uint64_t>(WebCore::ResourceRequestCachePolicy::ReloadIgnoringCacheData),
            static_cast<uint64_t>(WebCore::ResourceRequestCachePolicy::ReturnCacheDataElseLoad),
            static_cast<uint64_t>(WebCore::ResourceRequestCachePolicy::ReturnCacheDataDontLoad),
            static_cast<uint64_t>(WebCore::ResourceRequestCachePolicy::DoNotUseAnyCache),
            static_cast<uint64_t>(WebCore::ResourceRequestCachePolicy::RefreshAnyCacheData),
        } },
        { "WebCore::ResourceRequestBase::SameSiteDisposition"_s, sizeof(WebCore::ResourceRequestBase::SameSiteDisposition), false, {
            static_cast<uint64_t>(WebCore::ResourceRequestBase::SameSiteDisposition::Unspecified),
            static_cast<uint64_t>(WebCore::ResourceRequestBase::SameSiteDisposition::SameSite),
            static_cast<uint64_t>(WebCore::ResourceRequestBase::SameSiteDisposition::CrossSite),
        } },
        { "WebCore::ResourceRequestRequester"_s, sizeof(WebCore::ResourceRequestRequester), false, {
            static_cast<uint64_t>(WebCore::ResourceRequestRequester::Unspecified),
            static_cast<uint64_t>(WebCore::ResourceRequestRequester::Main),
            static_cast<uint64_t>(WebCore::ResourceRequestRequester::XHR),
            static_cast<uint64_t>(WebCore::ResourceRequestRequester::Fetch),
            static_cast<uint64_t>(WebCore::ResourceRequestRequester::Media),
            static_cast<uint64_t>(WebCore::ResourceRequestRequester::Model),
            static_cast<uint64_t>(WebCore::ResourceRequestRequester::ImportScripts),
            static_cast<uint64_t>(WebCore::ResourceRequestRequester::Ping),
            static_cast<uint64_t>(WebCore::ResourceRequestRequester::Beacon),
            static_cast<uint64_t>(WebCore::ResourceRequestRequester::EventSource),
        } },
        { "WebCore::ResourceLoadPriority"_s, sizeof(WebCore::ResourceLoadPriority), false, {
            static_cast<uint64_t>(WebCore::ResourceLoadPriority::VeryLow),
            static_cast<uint64_t>(WebCore::ResourceLoadPriority::Low),
            static_cast<uint64_t>(WebCore::ResourceLoadPriority::Medium),
            static_cast<uint64_t>(WebCore::ResourceLoadPriority::High),
            static_cast<uint64_t>(WebCore::ResourceLoadPriority::VeryHigh),
        } },
        { "WebCore::ResourceResponseBase::Type"_s, sizeof(WebCore::ResourceResponseBase::Type), false, {
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Type::Basic),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Type::Cors),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Type::Default),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Type::Error),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Type::Opaque),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Type::Opaqueredirect),
        } },
        { "WebCore::ResourceResponseBase::Tainting"_s, sizeof(WebCore::ResourceResponseBase::Tainting), false, {
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Tainting::Basic),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Tainting::Cors),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Tainting::Opaque),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Tainting::Opaqueredirect),
        } },
        { "WebCore::ResourceResponseBase::Source"_s, sizeof(WebCore::ResourceResponseBase::Source), false, {
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Source::Unknown),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Source::Network),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Source::DiskCache),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Source::DiskCacheAfterValidation),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Source::MemoryCache),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Source::MemoryCacheAfterValidation),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Source::ServiceWorker),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Source::ApplicationCache),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Source::DOMCache),
            static_cast<uint64_t>(WebCore::ResourceResponseBase::Source::InspectorOverride),
        } },
        { "WebCore::ReferrerPolicy"_s, sizeof(WebCore::ReferrerPolicy), false, {
            static_cast<uint64_t>(WebCore::ReferrerPolicy::EmptyString),
            static_cast<uint64_t>(WebCore::ReferrerPolicy::NoReferrer),
            static_cast<uint64_t>(WebCore::ReferrerPolicy::NoReferrerWhenDowngrade),
            static_cast<uint64_t>(WebCore::ReferrerPolicy::SameOrigin),
            static_cast<uint64_t>(WebCore::ReferrerPolicy::Origin),
            static_cast<uint64_t>(WebCore::ReferrerPolicy::StrictOrigin),
            static_cast<uint64_t>(WebCore::ReferrerPolicy::OriginWhenCrossOrigin),
            static_cast<uint64_t>(WebCore::ReferrerPolicy::StrictOriginWhenCrossOrigin),
            static_cast<uint64_t>(WebCore::ReferrerPolicy::UnsafeUrl),
        } },
        { "WebCore::FetchOptionsDestination"_s, sizeof(WebCore::FetchOptionsDestination), false, {
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::EmptyString),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Audio),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Audioworklet),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Document),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Embed),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Font),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Image),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Iframe),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Manifest),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Model),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Object),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Paintworklet),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Report),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Script),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Serviceworker),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Sharedworker),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Style),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Track),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Video),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Worker),
            static_cast<uint64_t>(WebCore::FetchOptionsDestination::Xslt),
        } },
        { "WebCore::FetchOptionsMode"_s, sizeof(WebCore::FetchOptionsMode), false, {
            static_cast<uint64_t>(WebCore::FetchOptionsMode::Navigate),
            static_cast<uint64_t>(WebCore::FetchOptionsMode::SameOrigin),
            static_cast<uint64_t>(WebCore::FetchOptionsMode::NoCors),
            static_cast<uint64_t>(WebCore::FetchOptionsMode::Cors),
        } },
        { "WebCore::FetchOptionsCredentials"_s, sizeof(WebCore::FetchOptionsCredentials), false, {
            static_cast<uint64_t>(WebCore::FetchOptionsCredentials::Omit),
            static_cast<uint64_t>(WebCore::FetchOptionsCredentials::SameOrigin),
            static_cast<uint64_t>(WebCore::FetchOptionsCredentials::Include),
        } },
        { "WebCore::FetchOptionsCache"_s, sizeof(WebCore::FetchOptionsCache), false, {
            static_cast<uint64_t>(WebCore::FetchOptionsCache::Default),
            static_cast<uint64_t>(WebCore::FetchOptionsCache::NoStore),
            static_cast<uint64_t>(WebCore::FetchOptionsCache::Reload),
            static_cast<uint64_t>(WebCore::FetchOptionsCache::NoCache),
            static_cast<uint64_t>(WebCore::FetchOptionsCache::ForceCache),
            static_cast<uint64_t>(WebCore::FetchOptionsCache::OnlyIfCached),
        } },
        { "WebCore::FetchOptionsRedirect"_s, sizeof(WebCore::FetchOptionsRedirect), false, {
            static_cast<uint64_t>(WebCore::FetchOptionsRedirect::Follow),
            static_cast<uint64_t>(WebCore::FetchOptionsRedirect::Error),
            static_cast<uint64_t>(WebCore::FetchOptionsRedirect::Manual),
        } },
        { "WebCore::FetchHeadersGuard"_s, sizeof(WebCore::FetchHeadersGuard), false, {
            static_cast<uint64_t>(WebCore::FetchHeadersGuard::None),
            static_cast<uint64_t>(WebCore::FetchHeadersGuard::Immutable),
            static_cast<uint64_t>(WebCore::FetchHeadersGuard::Request),
            static_cast<uint64_t>(WebCore::FetchHeadersGuard::RequestNoCors),
            static_cast<uint64_t>(WebCore::FetchHeadersGuard::Response),
        } },
        { "WebCore::ControlStyle::State"_s, sizeof(WebCore::ControlStyle::State), true, {
            static_cast<uint64_t>(WebCore::ControlStyle::State::Hovered),
            static_cast<uint64_t>(WebCore::ControlStyle::State::Pressed),
            static_cast<uint64_t>(WebCore::ControlStyle::State::Focused),
            static_cast<uint64_t>(WebCore::ControlStyle::State::Enabled),
            static_cast<uint64_t>(WebCore::ControlStyle::State::Checked),
            static_cast<uint64_t>(WebCore::ControlStyle::State::Default),
            static_cast<uint64_t>(WebCore::ControlStyle::State::WindowActive),
            static_cast<uint64_t>(WebCore::ControlStyle::State::Indeterminate),
            static_cast<uint64_t>(WebCore::ControlStyle::State::SpinUp),
            static_cast<uint64_t>(WebCore::ControlStyle::State::Presenting),
            static_cast<uint64_t>(WebCore::ControlStyle::State::FormSemanticContext),
            static_cast<uint64_t>(WebCore::ControlStyle::State::DarkAppearance),
            static_cast<uint64_t>(WebCore::ControlStyle::State::RightToLeft),
            static_cast<uint64_t>(WebCore::ControlStyle::State::LargeControls),
            static_cast<uint64_t>(WebCore::ControlStyle::State::ReadOnly),
            static_cast<uint64_t>(WebCore::ControlStyle::State::ListButton),
            static_cast<uint64_t>(WebCore::ControlStyle::State::ListButtonPressed),
            static_cast<uint64_t>(WebCore::ControlStyle::State::VerticalWritingMode),
        } },
        { "WebCore::StyleAppearance"_s, sizeof(WebCore::StyleAppearance), false, {
            static_cast<uint64_t>(WebCore::StyleAppearance::None),
            static_cast<uint64_t>(WebCore::StyleAppearance::Auto),
            static_cast<uint64_t>(WebCore::StyleAppearance::Checkbox),
            static_cast<uint64_t>(WebCore::StyleAppearance::Radio),
            static_cast<uint64_t>(WebCore::StyleAppearance::PushButton),
            static_cast<uint64_t>(WebCore::StyleAppearance::SquareButton),
            static_cast<uint64_t>(WebCore::StyleAppearance::Button),
            static_cast<uint64_t>(WebCore::StyleAppearance::DefaultButton),
            static_cast<uint64_t>(WebCore::StyleAppearance::Listbox),
            static_cast<uint64_t>(WebCore::StyleAppearance::Menulist),
            static_cast<uint64_t>(WebCore::StyleAppearance::MenulistButton),
            static_cast<uint64_t>(WebCore::StyleAppearance::Meter),
            static_cast<uint64_t>(WebCore::StyleAppearance::ProgressBar),
            static_cast<uint64_t>(WebCore::StyleAppearance::SliderHorizontal),
            static_cast<uint64_t>(WebCore::StyleAppearance::SliderVertical),
            static_cast<uint64_t>(WebCore::StyleAppearance::SearchField),
#if ENABLE(APPLE_PAY)
            static_cast<uint64_t>(WebCore::StyleAppearance::ApplePayButton),
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
            static_cast<uint64_t>(WebCore::StyleAppearance::Attachment),
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
            static_cast<uint64_t>(WebCore::StyleAppearance::BorderlessAttachment),
#endif
            static_cast<uint64_t>(WebCore::StyleAppearance::TextArea),
            static_cast<uint64_t>(WebCore::StyleAppearance::TextField),
            static_cast<uint64_t>(WebCore::StyleAppearance::CapsLockIndicator),
#if ENABLE(INPUT_TYPE_COLOR)
            static_cast<uint64_t>(WebCore::StyleAppearance::ColorWell),
#endif
#if ENABLE(SERVICE_CONTROLS)
            static_cast<uint64_t>(WebCore::StyleAppearance::ImageControlsButton),
#endif
            static_cast<uint64_t>(WebCore::StyleAppearance::InnerSpinButton),
#if ENABLE(DATALIST_ELEMENT)
            static_cast<uint64_t>(WebCore::StyleAppearance::ListButton),
#endif
            static_cast<uint64_t>(WebCore::StyleAppearance::SearchFieldDecoration),
            static_cast<uint64_t>(WebCore::StyleAppearance::SearchFieldResultsDecoration),
            static_cast<uint64_t>(WebCore::StyleAppearance::SearchFieldResultsButton),
            static_cast<uint64_t>(WebCore::StyleAppearance::SearchFieldCancelButton),
            static_cast<uint64_t>(WebCore::StyleAppearance::SliderThumbHorizontal),
            static_cast<uint64_t>(WebCore::StyleAppearance::SliderThumbVertical),
        } },
#if ENABLE(APPLE_PAY)
        { "WebCore::ApplePayButtonType"_s, sizeof(WebCore::ApplePayButtonType), false, {
            static_cast<uint64_t>(WebCore::ApplePayButtonType::Plain),
            static_cast<uint64_t>(WebCore::ApplePayButtonType::Buy),
            static_cast<uint64_t>(WebCore::ApplePayButtonType::SetUp),
            static_cast<uint64_t>(WebCore::ApplePayButtonType::Donate),
            static_cast<uint64_t>(WebCore::ApplePayButtonType::CheckOut),
            static_cast<uint64_t>(WebCore::ApplePayButtonType::Book),
            static_cast<uint64_t>(WebCore::ApplePayButtonType::Subscribe),
#if ENABLE(APPLE_PAY_NEW_BUTTON_TYPES)
            static_cast<uint64_t>(WebCore::ApplePayButtonType::Reload),
#endif
#if ENABLE(APPLE_PAY_NEW_BUTTON_TYPES)
            static_cast<uint64_t>(WebCore::ApplePayButtonType::AddMoney),
#endif
#if ENABLE(APPLE_PAY_NEW_BUTTON_TYPES)
            static_cast<uint64_t>(WebCore::ApplePayButtonType::TopUp),
#endif
#if ENABLE(APPLE_PAY_NEW_BUTTON_TYPES)
            static_cast<uint64_t>(WebCore::ApplePayButtonType::Order),
#endif
#if ENABLE(APPLE_PAY_NEW_BUTTON_TYPES)
            static_cast<uint64_t>(WebCore::ApplePayButtonType::Rent),
#endif
#if ENABLE(APPLE_PAY_NEW_BUTTON_TYPES)
            static_cast<uint64_t>(WebCore::ApplePayButtonType::Support),
#endif
#if ENABLE(APPLE_PAY_NEW_BUTTON_TYPES)
            static_cast<uint64_t>(WebCore::ApplePayButtonType::Contribute),
#endif
#if ENABLE(APPLE_PAY_NEW_BUTTON_TYPES)
            static_cast<uint64_t>(WebCore::ApplePayButtonType::Tip),
#endif
        } },
#endif
#if ENABLE(APPLE_PAY)
        { "WebCore::ApplePayButtonStyle"_s, sizeof(WebCore::ApplePayButtonStyle), false, {
            static_cast<uint64_t>(WebCore::ApplePayButtonStyle::White),
            static_cast<uint64_t>(WebCore::ApplePayButtonStyle::WhiteOutline),
            static_cast<uint64_t>(WebCore::ApplePayButtonStyle::Black),
        } },
#endif
        { "WebCore::MeterPart::GaugeRegion"_s, sizeof(WebCore::MeterPart::GaugeRegion), false, {
            static_cast<uint64_t>(WebCore::MeterPart::GaugeRegion::Optimum),
            static_cast<uint64_t>(WebCore::MeterPart::GaugeRegion::Suboptimal),
            static_cast<uint64_t>(WebCore::MeterPart::GaugeRegion::EvenLessGood),
        } },
        { "WebCore::FilterEffectGeometry::Flags"_s, sizeof(WebCore::FilterEffectGeometry::Flags), true, {
            static_cast<uint64_t>(WebCore::FilterEffectGeometry::Flags::HasX),
            static_cast<uint64_t>(WebCore::FilterEffectGeometry::Flags::HasY),
            static_cast<uint64_t>(WebCore::FilterEffectGeometry::Flags::HasWidth),
            static_cast<uint64_t>(WebCore::FilterEffectGeometry::Flags::HasHeight),
        } },
        { "WebCore::HasInsecureContent"_s, sizeof(WebCore::HasInsecureContent), false, {
            0, 1
        } },
        { "WebCore::ModalContainerDecision"_s, sizeof(WebCore::ModalContainerDecision), false, {
            static_cast<uint64_t>(WebCore::ModalContainerDecision::Show),
            static_cast<uint64_t>(WebCore::ModalContainerDecision::HideAndIgnore),
            static_cast<uint64_t>(WebCore::ModalContainerDecision::HideAndAllow),
            static_cast<uint64_t>(WebCore::ModalContainerDecision::HideAndDisallow),
        } },
        { "WebCore::AutoplayEventFlags"_s, sizeof(WebCore::AutoplayEventFlags), true, {
            static_cast<uint64_t>(WebCore::AutoplayEventFlags::HasAudio),
            static_cast<uint64_t>(WebCore::AutoplayEventFlags::PlaybackWasPrevented),
            static_cast<uint64_t>(WebCore::AutoplayEventFlags::MediaIsMainContent),
        } },
        { "WebCore::FocusDirection"_s, sizeof(WebCore::FocusDirection), false, {
            static_cast<uint64_t>(WebCore::FocusDirection::None),
            static_cast<uint64_t>(WebCore::FocusDirection::Forward),
            static_cast<uint64_t>(WebCore::FocusDirection::Backward),
            static_cast<uint64_t>(WebCore::FocusDirection::Up),
            static_cast<uint64_t>(WebCore::FocusDirection::Down),
            static_cast<uint64_t>(WebCore::FocusDirection::Left),
            static_cast<uint64_t>(WebCore::FocusDirection::Right),
        } },
#if ENABLE(GAMEPAD)
        { "WebCore::GamepadHapticEffectType"_s, sizeof(WebCore::GamepadHapticEffectType), false, {
            static_cast<uint64_t>(WebCore::GamepadHapticEffectType::DualRumble),
            static_cast<uint64_t>(WebCore::GamepadHapticEffectType::TriggerRumble),
        } },
#endif
        { "WebCore::DOMPasteAccessCategory"_s, sizeof(WebCore::DOMPasteAccessCategory), false, {
            static_cast<uint64_t>(WebCore::DOMPasteAccessCategory::General),
            static_cast<uint64_t>(WebCore::DOMPasteAccessCategory::Fonts),
        } },
        { "WebCore::DOMPasteAccessPolicy"_s, sizeof(WebCore::DOMPasteAccessPolicy), false, {
            static_cast<uint64_t>(WebCore::DOMPasteAccessPolicy::NotRequestedYet),
            static_cast<uint64_t>(WebCore::DOMPasteAccessPolicy::Denied),
            static_cast<uint64_t>(WebCore::DOMPasteAccessPolicy::Granted),
        } },
        { "WebCore::DOMPasteAccessResponse"_s, sizeof(WebCore::DOMPasteAccessResponse), false, {
            static_cast<uint64_t>(WebCore::DOMPasteAccessResponse::DeniedForGesture),
            static_cast<uint64_t>(WebCore::DOMPasteAccessResponse::GrantedForCommand),
            static_cast<uint64_t>(WebCore::DOMPasteAccessResponse::GrantedForGesture),
        } },
        { "WebCore::DeviceOrientationOrMotionPermissionState"_s, sizeof(WebCore::DeviceOrientationOrMotionPermissionState), false, {
            static_cast<uint64_t>(WebCore::DeviceOrientationOrMotionPermissionState::Granted),
            static_cast<uint64_t>(WebCore::DeviceOrientationOrMotionPermissionState::Denied),
            static_cast<uint64_t>(WebCore::DeviceOrientationOrMotionPermissionState::Prompt),
        } },
        { "WebCore::ExceptionDetails::Type"_s, sizeof(WebCore::ExceptionDetails::Type), false, {
            static_cast<uint64_t>(WebCore::ExceptionDetails::Type::Script),
            static_cast<uint64_t>(WebCore::ExceptionDetails::Type::InvalidTargetFrame),
            static_cast<uint64_t>(WebCore::ExceptionDetails::Type::AppBoundDomain),
        } },
        { "WebCore::SecurityPolicyViolationEventDisposition"_s, sizeof(WebCore::SecurityPolicyViolationEventDisposition), false, {
            0, 1
        } },
        { "WebCore::VerticalAlignChange"_s, sizeof(WebCore::VerticalAlignChange), false, {
            static_cast<uint64_t>(WebCore::VerticalAlignChange::Superscript),
            static_cast<uint64_t>(WebCore::VerticalAlignChange::Baseline),
            static_cast<uint64_t>(WebCore::VerticalAlignChange::Subscript),
        } },
        { "WebCore::TextGranularity"_s, sizeof(WebCore::TextGranularity), false, {
            static_cast<uint64_t>(WebCore::TextGranularity::CharacterGranularity),
            static_cast<uint64_t>(WebCore::TextGranularity::WordGranularity),
            static_cast<uint64_t>(WebCore::TextGranularity::SentenceGranularity),
            static_cast<uint64_t>(WebCore::TextGranularity::LineGranularity),
            static_cast<uint64_t>(WebCore::TextGranularity::ParagraphGranularity),
            static_cast<uint64_t>(WebCore::TextGranularity::DocumentGranularity),
            static_cast<uint64_t>(WebCore::TextGranularity::SentenceBoundary),
            static_cast<uint64_t>(WebCore::TextGranularity::LineBoundary),
            static_cast<uint64_t>(WebCore::TextGranularity::ParagraphBoundary),
            static_cast<uint64_t>(WebCore::TextGranularity::DocumentBoundary),
        } },
        { "WebCore::FontAttributes::SubscriptOrSuperscript"_s, sizeof(WebCore::FontAttributes::SubscriptOrSuperscript), false, {
            static_cast<uint64_t>(WebCore::FontAttributes::SubscriptOrSuperscript::None),
            static_cast<uint64_t>(WebCore::FontAttributes::SubscriptOrSuperscript::Subscript),
            static_cast<uint64_t>(WebCore::FontAttributes::SubscriptOrSuperscript::Superscript),
        } },
        { "WebCore::FontAttributes::HorizontalAlignment"_s, sizeof(WebCore::FontAttributes::HorizontalAlignment), false, {
            static_cast<uint64_t>(WebCore::FontAttributes::HorizontalAlignment::Left),
            static_cast<uint64_t>(WebCore::FontAttributes::HorizontalAlignment::Center),
            static_cast<uint64_t>(WebCore::FontAttributes::HorizontalAlignment::Right),
            static_cast<uint64_t>(WebCore::FontAttributes::HorizontalAlignment::Justify),
            static_cast<uint64_t>(WebCore::FontAttributes::HorizontalAlignment::Natural),
        } },
        { "WebCore::WritingDirection"_s, sizeof(WebCore::WritingDirection), false, {
            static_cast<uint64_t>(WebCore::WritingDirection::Natural),
            static_cast<uint64_t>(WebCore::WritingDirection::LeftToRight),
            static_cast<uint64_t>(WebCore::WritingDirection::RightToLeft),
        } },
        { "WebCore::SelectionDirection"_s, sizeof(WebCore::SelectionDirection), false, {
            static_cast<uint64_t>(WebCore::SelectionDirection::Forward),
            static_cast<uint64_t>(WebCore::SelectionDirection::Backward),
            static_cast<uint64_t>(WebCore::SelectionDirection::Right),
            static_cast<uint64_t>(WebCore::SelectionDirection::Left),
        } },
#if ENABLE(DATA_DETECTION)
        { "WebCore::DataDetectorType"_s, sizeof(WebCore::DataDetectorType), true, {
            static_cast<uint64_t>(WebCore::DataDetectorType::PhoneNumber),
            static_cast<uint64_t>(WebCore::DataDetectorType::Link),
            static_cast<uint64_t>(WebCore::DataDetectorType::Address),
            static_cast<uint64_t>(WebCore::DataDetectorType::CalendarEvent),
            static_cast<uint64_t>(WebCore::DataDetectorType::TrackingNumber),
            static_cast<uint64_t>(WebCore::DataDetectorType::FlightNumber),
            static_cast<uint64_t>(WebCore::DataDetectorType::LookupSuggestion),
        } },
#endif
        { "WebCore::AutocapitalizeType"_s, sizeof(WebCore::AutocapitalizeType), false, {
            static_cast<uint64_t>(WebCore::AutocapitalizeType::Default),
            static_cast<uint64_t>(WebCore::AutocapitalizeType::None),
            static_cast<uint64_t>(WebCore::AutocapitalizeType::Words),
            static_cast<uint64_t>(WebCore::AutocapitalizeType::Sentences),
            static_cast<uint64_t>(WebCore::AutocapitalizeType::AllCharacters),
        } },
        { "WebCore::CrossOriginEmbedderPolicyValue"_s, sizeof(WebCore::CrossOriginEmbedderPolicyValue), false, {
            0, 1
        } },
        { "WebCore::IncludeSecureCookies"_s, sizeof(WebCore::IncludeSecureCookies), false, {
            0, 1
        } },
#if ENABLE(ASYNC_SCROLLING)
        { "WebCore::ScrollingStateNodeProperty"_s, sizeof(WebCore::ScrollingStateNodeProperty), true, {
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::Layer),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ChildNodes),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ScrollableAreaSize),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::TotalContentsSize),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ReachableContentsSize),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ScrollPosition),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ScrollOrigin),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ScrollableAreaParams),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ReasonsForSynchronousScrolling),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::RequestedScrollPosition),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::SnapOffsetsInfo),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::CurrentHorizontalSnapOffsetIndex),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::CurrentVerticalSnapOffsetIndex),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::IsMonitoringWheelEvents),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ScrollContainerLayer),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ScrolledContentsLayer),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::HorizontalScrollbarLayer),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::VerticalScrollbarLayer),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::PainterForScrollbar),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ContentAreaHoverState),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::MouseActivityState),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ScrollbarHoverState),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ScrollbarEnabledState),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::FrameScaleFactor),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::EventTrackingRegion),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::RootContentsLayer),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::CounterScrollingLayer),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::InsetClipLayer),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ContentShadowLayer),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::HeaderHeight),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::FooterHeight),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::HeaderLayer),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::FooterLayer),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::BehaviorForFixedElements),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::TopContentInset),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::FixedElementsLayoutRelativeToFrame),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::VisualViewportIsSmallerThanLayoutViewport),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::AsyncFrameOrOverflowScrollingEnabled),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::WheelEventGesturesBecomeNonBlocking),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ScrollingPerformanceTestingEnabled),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::LayoutViewport),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::MinLayoutViewportOrigin),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::MaxLayoutViewportOrigin),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::OverrideVisualViewportSize),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::RelatedOverflowScrollingNodes),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::LayoutConstraintData),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::ViewportConstraints),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::OverflowScrollingNode),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::KeyboardScrollData),
            static_cast<uint64_t>(WebCore::ScrollingStateNodeProperty::OverlayScrollbarsEnabled),
        } },
#endif
#if ENABLE(ENCRYPTED_MEDIA)
        { "WebCore::CDMEncryptionScheme"_s, sizeof(WebCore::CDMEncryptionScheme), false, {
            0, 1
        } },
#endif
#if ENABLE(ENCRYPTED_MEDIA)
        { "WebCore::CDMSessionType"_s, sizeof(WebCore::CDMSessionType), false, {
            static_cast<uint64_t>(WebCore::CDMSessionType::Temporary),
            static_cast<uint64_t>(WebCore::CDMSessionType::PersistentUsageRecord),
            static_cast<uint64_t>(WebCore::CDMSessionType::PersistentLicense),
        } },
#endif
        { "WebCore::MediaSelectionOption::MediaType"_s, sizeof(WebCore::MediaSelectionOption::MediaType), false, {
            static_cast<uint64_t>(WebCore::MediaSelectionOption::MediaType::Unknown),
            static_cast<uint64_t>(WebCore::MediaSelectionOption::MediaType::Audio),
            static_cast<uint64_t>(WebCore::MediaSelectionOption::MediaType::Subtitles),
            static_cast<uint64_t>(WebCore::MediaSelectionOption::MediaType::Captions),
            static_cast<uint64_t>(WebCore::MediaSelectionOption::MediaType::Metadata),
        } },
        { "WebCore::MediaSelectionOption::LegibleType"_s, sizeof(WebCore::MediaSelectionOption::LegibleType), false, {
            static_cast<uint64_t>(WebCore::MediaSelectionOption::LegibleType::Regular),
            static_cast<uint64_t>(WebCore::MediaSelectionOption::LegibleType::LegibleOff),
            static_cast<uint64_t>(WebCore::MediaSelectionOption::LegibleType::LegibleAuto),
        } },
        { "WebCore::MediaDecodingType"_s, sizeof(WebCore::MediaDecodingType), false, {
            static_cast<uint64_t>(WebCore::MediaDecodingType::File),
            static_cast<uint64_t>(WebCore::MediaDecodingType::MediaSource),
            static_cast<uint64_t>(WebCore::MediaDecodingType::WebRTC),
        } },
        { "WebCore::MediaEncodingType"_s, sizeof(WebCore::MediaEncodingType), false, {
            0, 1
        } },
        { "WebCore::TextManipulationControllerExclusionRule::Type"_s, sizeof(WebCore::TextManipulationControllerExclusionRule::Type), false, {
            static_cast<uint64_t>(WebCore::TextManipulationControllerExclusionRule::Type::Exclude),
            static_cast<uint64_t>(WebCore::TextManipulationControllerExclusionRule::Type::Include),
        } },
        { "WebCore::TextManipulationControllerManipulationFailure::Type"_s, sizeof(WebCore::TextManipulationControllerManipulationFailure::Type), false, {
            static_cast<uint64_t>(WebCore::TextManipulationControllerManipulationFailure::Type::NotAvailable),
            static_cast<uint64_t>(WebCore::TextManipulationControllerManipulationFailure::Type::ContentChanged),
            static_cast<uint64_t>(WebCore::TextManipulationControllerManipulationFailure::Type::InvalidItem),
            static_cast<uint64_t>(WebCore::TextManipulationControllerManipulationFailure::Type::InvalidToken),
            static_cast<uint64_t>(WebCore::TextManipulationControllerManipulationFailure::Type::ExclusionViolation),
        } },
        { "WebCore::MediaPlayerNetworkState"_s, sizeof(WebCore::MediaPlayerNetworkState), false, {
            static_cast<uint64_t>(WebCore::MediaPlayerNetworkState::Empty),
            static_cast<uint64_t>(WebCore::MediaPlayerNetworkState::Idle),
            static_cast<uint64_t>(WebCore::MediaPlayerNetworkState::Loading),
            static_cast<uint64_t>(WebCore::MediaPlayerNetworkState::Loaded),
            static_cast<uint64_t>(WebCore::MediaPlayerNetworkState::FormatError),
            static_cast<uint64_t>(WebCore::MediaPlayerNetworkState::NetworkError),
            static_cast<uint64_t>(WebCore::MediaPlayerNetworkState::DecodeError),
        } },
        { "WebCore::MediaPlayerReadyState"_s, sizeof(WebCore::MediaPlayerReadyState), false, {
            static_cast<uint64_t>(WebCore::MediaPlayerReadyState::HaveNothing),
            static_cast<uint64_t>(WebCore::MediaPlayerReadyState::HaveMetadata),
            static_cast<uint64_t>(WebCore::MediaPlayerReadyState::HaveCurrentData),
            static_cast<uint64_t>(WebCore::MediaPlayerReadyState::HaveFutureData),
            static_cast<uint64_t>(WebCore::MediaPlayerReadyState::HaveEnoughData),
        } },
        { "WebCore::MediaPlayerMovieLoadType"_s, sizeof(WebCore::MediaPlayerMovieLoadType), false, {
            static_cast<uint64_t>(WebCore::MediaPlayerMovieLoadType::Unknown),
            static_cast<uint64_t>(WebCore::MediaPlayerMovieLoadType::Download),
            static_cast<uint64_t>(WebCore::MediaPlayerMovieLoadType::StoredStream),
            static_cast<uint64_t>(WebCore::MediaPlayerMovieLoadType::LiveStream),
            static_cast<uint64_t>(WebCore::MediaPlayerMovieLoadType::HttpLiveStream),
        } },
        { "WebCore::MediaPlayerPreload"_s, sizeof(WebCore::MediaPlayerPreload), false, {
            static_cast<uint64_t>(WebCore::MediaPlayerPreload::None),
            static_cast<uint64_t>(WebCore::MediaPlayerPreload::MetaData),
            static_cast<uint64_t>(WebCore::MediaPlayerPreload::Auto),
        } },
        { "WebCore::MediaPlayerVideoGravity"_s, sizeof(WebCore::MediaPlayerVideoGravity), false, {
            static_cast<uint64_t>(WebCore::MediaPlayerVideoGravity::Resize),
            static_cast<uint64_t>(WebCore::MediaPlayerVideoGravity::ResizeAspect),
            static_cast<uint64_t>(WebCore::MediaPlayerVideoGravity::ResizeAspectFill),
        } },
        { "WebCore::MediaPlayerSupportsType"_s, sizeof(WebCore::MediaPlayerSupportsType), false, {
            static_cast<uint64_t>(WebCore::MediaPlayerSupportsType::IsNotSupported),
            static_cast<uint64_t>(WebCore::MediaPlayerSupportsType::IsSupported),
            static_cast<uint64_t>(WebCore::MediaPlayerSupportsType::MayBeSupported),
        } },
        { "WebCore::MediaPlayerBufferingPolicy"_s, sizeof(WebCore::MediaPlayerBufferingPolicy), false, {
            static_cast<uint64_t>(WebCore::MediaPlayerBufferingPolicy::Default),
            static_cast<uint64_t>(WebCore::MediaPlayerBufferingPolicy::LimitReadAhead),
            static_cast<uint64_t>(WebCore::MediaPlayerBufferingPolicy::MakeResourcesPurgeable),
            static_cast<uint64_t>(WebCore::MediaPlayerBufferingPolicy::PurgeResources),
        } },
        { "WebCore::MediaPlayerMediaEngineIdentifier"_s, sizeof(WebCore::MediaPlayerMediaEngineIdentifier), false, {
            static_cast<uint64_t>(WebCore::MediaPlayerMediaEngineIdentifier::AVFoundation),
            static_cast<uint64_t>(WebCore::MediaPlayerMediaEngineIdentifier::AVFoundationMSE),
            static_cast<uint64_t>(WebCore::MediaPlayerMediaEngineIdentifier::AVFoundationMediaStream),
            static_cast<uint64_t>(WebCore::MediaPlayerMediaEngineIdentifier::AVFoundationCF),
            static_cast<uint64_t>(WebCore::MediaPlayerMediaEngineIdentifier::GStreamer),
            static_cast<uint64_t>(WebCore::MediaPlayerMediaEngineIdentifier::GStreamerMSE),
            static_cast<uint64_t>(WebCore::MediaPlayerMediaEngineIdentifier::HolePunch),
            static_cast<uint64_t>(WebCore::MediaPlayerMediaEngineIdentifier::MediaFoundation),
            static_cast<uint64_t>(WebCore::MediaPlayerMediaEngineIdentifier::MockMSE),
            static_cast<uint64_t>(WebCore::MediaPlayerMediaEngineIdentifier::CocoaWebM),
        } },
        { "WebCore::MediaPlayerWirelessPlaybackTargetType"_s, sizeof(WebCore::MediaPlayerWirelessPlaybackTargetType), false, {
            static_cast<uint64_t>(WebCore::MediaPlayerWirelessPlaybackTargetType::TargetTypeNone),
            static_cast<uint64_t>(WebCore::MediaPlayerWirelessPlaybackTargetType::TargetTypeAirPlay),
            static_cast<uint64_t>(WebCore::MediaPlayerWirelessPlaybackTargetType::TargetTypeTVOut),
        } },
        { "WebCore::MediaPlayerPitchCorrectionAlgorithm"_s, sizeof(WebCore::MediaPlayerPitchCorrectionAlgorithm), false, {
            static_cast<uint64_t>(WebCore::MediaPlayerPitchCorrectionAlgorithm::BestAllAround),
            static_cast<uint64_t>(WebCore::MediaPlayerPitchCorrectionAlgorithm::BestForMusic),
            static_cast<uint64_t>(WebCore::MediaPlayerPitchCorrectionAlgorithm::BestForSpeech),
        } },
#if ENABLE(APP_HIGHLIGHTS)
        { "WebCore::CreateNewGroupForHighlight"_s, sizeof(WebCore::CreateNewGroupForHighlight), false, {
            0, 1
        } },
#endif
#if ENABLE(APP_HIGHLIGHTS)
        { "WebCore::HighlightRequestOriginatedInApp"_s, sizeof(WebCore::HighlightRequestOriginatedInApp), false, {
            0, 1
        } },
#endif
        { "WebCore::SpeechRecognitionUpdateType"_s, sizeof(WebCore::SpeechRecognitionUpdateType), false, {
            static_cast<uint64_t>(WebCore::SpeechRecognitionUpdateType::Start),
            static_cast<uint64_t>(WebCore::SpeechRecognitionUpdateType::AudioStart),
            static_cast<uint64_t>(WebCore::SpeechRecognitionUpdateType::SoundStart),
            static_cast<uint64_t>(WebCore::SpeechRecognitionUpdateType::SpeechStart),
            static_cast<uint64_t>(WebCore::SpeechRecognitionUpdateType::SpeechEnd),
            static_cast<uint64_t>(WebCore::SpeechRecognitionUpdateType::SoundEnd),
            static_cast<uint64_t>(WebCore::SpeechRecognitionUpdateType::AudioEnd),
            static_cast<uint64_t>(WebCore::SpeechRecognitionUpdateType::Result),
            static_cast<uint64_t>(WebCore::SpeechRecognitionUpdateType::NoMatch),
            static_cast<uint64_t>(WebCore::SpeechRecognitionUpdateType::Error),
            static_cast<uint64_t>(WebCore::SpeechRecognitionUpdateType::End),
        } },
        { "WebCore::CompositeOperator"_s, sizeof(WebCore::CompositeOperator), false, {
            static_cast<uint64_t>(WebCore::CompositeOperator::Clear),
            static_cast<uint64_t>(WebCore::CompositeOperator::Copy),
            static_cast<uint64_t>(WebCore::CompositeOperator::SourceOver),
            static_cast<uint64_t>(WebCore::CompositeOperator::SourceIn),
            static_cast<uint64_t>(WebCore::CompositeOperator::SourceOut),
            static_cast<uint64_t>(WebCore::CompositeOperator::SourceAtop),
            static_cast<uint64_t>(WebCore::CompositeOperator::DestinationOver),
            static_cast<uint64_t>(WebCore::CompositeOperator::DestinationIn),
            static_cast<uint64_t>(WebCore::CompositeOperator::DestinationOut),
            static_cast<uint64_t>(WebCore::CompositeOperator::DestinationAtop),
            static_cast<uint64_t>(WebCore::CompositeOperator::XOR),
            static_cast<uint64_t>(WebCore::CompositeOperator::PlusDarker),
            static_cast<uint64_t>(WebCore::CompositeOperator::PlusLighter),
            static_cast<uint64_t>(WebCore::CompositeOperator::Difference),
        } },
        { "WebCore::BlendMode"_s, sizeof(WebCore::BlendMode), false, {
            static_cast<uint64_t>(WebCore::BlendMode::Normal),
            static_cast<uint64_t>(WebCore::BlendMode::Multiply),
            static_cast<uint64_t>(WebCore::BlendMode::Screen),
            static_cast<uint64_t>(WebCore::BlendMode::Darken),
            static_cast<uint64_t>(WebCore::BlendMode::Lighten),
            static_cast<uint64_t>(WebCore::BlendMode::Overlay),
            static_cast<uint64_t>(WebCore::BlendMode::ColorDodge),
            static_cast<uint64_t>(WebCore::BlendMode::ColorBurn),
            static_cast<uint64_t>(WebCore::BlendMode::HardLight),
            static_cast<uint64_t>(WebCore::BlendMode::SoftLight),
            static_cast<uint64_t>(WebCore::BlendMode::Difference),
            static_cast<uint64_t>(WebCore::BlendMode::Exclusion),
            static_cast<uint64_t>(WebCore::BlendMode::Hue),
            static_cast<uint64_t>(WebCore::BlendMode::Saturation),
            static_cast<uint64_t>(WebCore::BlendMode::Color),
            static_cast<uint64_t>(WebCore::BlendMode::Luminosity),
            static_cast<uint64_t>(WebCore::BlendMode::PlusDarker),
            static_cast<uint64_t>(WebCore::BlendMode::PlusLighter),
        } },
        { "WebCore::GradientSpreadMethod"_s, sizeof(WebCore::GradientSpreadMethod), false, {
            static_cast<uint64_t>(WebCore::GradientSpreadMethod::Pad),
            static_cast<uint64_t>(WebCore::GradientSpreadMethod::Reflect),
            static_cast<uint64_t>(WebCore::GradientSpreadMethod::Repeat),
        } },
        { "WebCore::InterpolationQuality"_s, sizeof(WebCore::InterpolationQuality), false, {
            static_cast<uint64_t>(WebCore::InterpolationQuality::Default),
            static_cast<uint64_t>(WebCore::InterpolationQuality::DoNotInterpolate),
            static_cast<uint64_t>(WebCore::InterpolationQuality::Low),
            static_cast<uint64_t>(WebCore::InterpolationQuality::Medium),
            static_cast<uint64_t>(WebCore::InterpolationQuality::High),
        } },
#if ENABLE(VIDEO)
        { "WebCore::VideoFrameRotation"_s, sizeof(WebCore::VideoFrameRotation), false, {
            static_cast<uint64_t>(WebCore::VideoFrameRotation::None),
            static_cast<uint64_t>(WebCore::VideoFrameRotation::UpsideDown),
            static_cast<uint64_t>(WebCore::VideoFrameRotation::Right),
            static_cast<uint64_t>(WebCore::VideoFrameRotation::Left),
        } },
#endif
        { "WebCore::PreserveResolution"_s, sizeof(WebCore::PreserveResolution), false, {
            0, 1
        } },
        { "WebCore::ColorInterpolationColorSpace"_s, sizeof(WebCore::ColorInterpolationColorSpace), false, {
            static_cast<uint64_t>(WebCore::ColorInterpolationColorSpace::HSL),
            static_cast<uint64_t>(WebCore::ColorInterpolationColorSpace::HWB),
            static_cast<uint64_t>(WebCore::ColorInterpolationColorSpace::LCH),
            static_cast<uint64_t>(WebCore::ColorInterpolationColorSpace::Lab),
            static_cast<uint64_t>(WebCore::ColorInterpolationColorSpace::OKLCH),
            static_cast<uint64_t>(WebCore::ColorInterpolationColorSpace::OKLab),
            static_cast<uint64_t>(WebCore::ColorInterpolationColorSpace::SRGB),
            static_cast<uint64_t>(WebCore::ColorInterpolationColorSpace::SRGBLinear),
            static_cast<uint64_t>(WebCore::ColorInterpolationColorSpace::XYZD50),
            static_cast<uint64_t>(WebCore::ColorInterpolationColorSpace::XYZD65),
        } },
        { "WebCore::HueInterpolationMethod"_s, sizeof(WebCore::HueInterpolationMethod), false, {
            static_cast<uint64_t>(WebCore::HueInterpolationMethod::Shorter),
            static_cast<uint64_t>(WebCore::HueInterpolationMethod::Longer),
            static_cast<uint64_t>(WebCore::HueInterpolationMethod::Increasing),
            static_cast<uint64_t>(WebCore::HueInterpolationMethod::Decreasing),
        } },
#if USE(AUDIO_SESSION)
        { "WebCore::RouteSharingPolicy"_s, sizeof(WebCore::RouteSharingPolicy), false, {
            static_cast<uint64_t>(WebCore::RouteSharingPolicy::Default),
            static_cast<uint64_t>(WebCore::RouteSharingPolicy::LongFormAudio),
            static_cast<uint64_t>(WebCore::RouteSharingPolicy::Independent),
            static_cast<uint64_t>(WebCore::RouteSharingPolicy::LongFormVideo),
        } },
#endif
#if USE(AUDIO_SESSION)
        { "WebCore::AudioSessionCategory"_s, sizeof(WebCore::AudioSessionCategory), false, {
            static_cast<uint64_t>(WebCore::AudioSessionCategory::None),
            static_cast<uint64_t>(WebCore::AudioSessionCategory::AmbientSound),
            static_cast<uint64_t>(WebCore::AudioSessionCategory::SoloAmbientSound),
            static_cast<uint64_t>(WebCore::AudioSessionCategory::MediaPlayback),
            static_cast<uint64_t>(WebCore::AudioSessionCategory::RecordAudio),
            static_cast<uint64_t>(WebCore::AudioSessionCategory::PlayAndRecord),
            static_cast<uint64_t>(WebCore::AudioSessionCategory::AudioProcessing),
        } },
#endif
#if USE(AUDIO_SESSION)
        { "WebCore::AudioSessionMode"_s, sizeof(WebCore::AudioSessionMode), false, {
            static_cast<uint64_t>(WebCore::AudioSessionMode::Default),
            static_cast<uint64_t>(WebCore::AudioSessionMode::VideoChat),
            static_cast<uint64_t>(WebCore::AudioSessionMode::MoviePlayback),
        } },
#endif
#if USE(AUDIO_SESSION)
        { "WebCore::AudioSession::MayResume"_s, sizeof(WebCore::AudioSession::MayResume), false, {
            0, 1
        } },
#endif
#if USE(AUDIO_SESSION)
        { "WebCore::AudioSessionRoutingArbitrationError"_s, sizeof(WebCore::AudioSessionRoutingArbitrationError), false, {
            static_cast<uint64_t>(WebCore::AudioSessionRoutingArbitrationError::None),
            static_cast<uint64_t>(WebCore::AudioSessionRoutingArbitrationError::Failed),
            static_cast<uint64_t>(WebCore::AudioSessionRoutingArbitrationError::Cancelled),
        } },
#endif
#if USE(AUDIO_SESSION)
        { "WebCore::AudioSessionRoutingArbitrationClient::DefaultRouteChanged"_s, sizeof(WebCore::AudioSessionRoutingArbitrationClient::DefaultRouteChanged), false, {
            0, 1
        } },
#endif
#if ENABLE(ENCRYPTED_MEDIA)
        { "WebCore::CDMKeyStatus"_s, sizeof(WebCore::CDMKeyStatus), false, {
            static_cast<uint64_t>(WebCore::CDMKeyStatus::Usable),
            static_cast<uint64_t>(WebCore::CDMKeyStatus::Expired),
            static_cast<uint64_t>(WebCore::CDMKeyStatus::Released),
            static_cast<uint64_t>(WebCore::CDMKeyStatus::OutputRestricted),
            static_cast<uint64_t>(WebCore::CDMKeyStatus::OutputDownscaled),
            static_cast<uint64_t>(WebCore::CDMKeyStatus::StatusPending),
            static_cast<uint64_t>(WebCore::CDMKeyStatus::InternalError),
        } },
#endif
#if ENABLE(ENCRYPTED_MEDIA)
        { "WebCore::CDMMessageType"_s, sizeof(WebCore::CDMMessageType), false, {
            static_cast<uint64_t>(WebCore::CDMMessageType::LicenseRequest),
            static_cast<uint64_t>(WebCore::CDMMessageType::LicenseRenewal),
            static_cast<uint64_t>(WebCore::CDMMessageType::LicenseRelease),
            static_cast<uint64_t>(WebCore::CDMMessageType::IndividualizationRequest),
        } },
#endif
#if ENABLE(ENCRYPTED_MEDIA)
        { "WebCore::CDMRequirement"_s, sizeof(WebCore::CDMRequirement), false, {
            static_cast<uint64_t>(WebCore::CDMRequirement::Required),
            static_cast<uint64_t>(WebCore::CDMRequirement::Optional),
            static_cast<uint64_t>(WebCore::CDMRequirement::NotAllowed),
        } },
#endif
#if ENABLE(WEB_RTC)
        { "WebCore::RTCDataChannelState"_s, sizeof(WebCore::RTCDataChannelState), false, {
            static_cast<uint64_t>(WebCore::RTCDataChannelState::Connecting),
            static_cast<uint64_t>(WebCore::RTCDataChannelState::Open),
            static_cast<uint64_t>(WebCore::RTCDataChannelState::Closing),
            static_cast<uint64_t>(WebCore::RTCDataChannelState::Closed),
        } },
#endif
#if ENABLE(WEB_RTC)
        { "WebCore::RTCPriorityType"_s, sizeof(WebCore::RTCPriorityType), false, {
            static_cast<uint64_t>(WebCore::RTCPriorityType::VeryLow),
            static_cast<uint64_t>(WebCore::RTCPriorityType::Low),
            static_cast<uint64_t>(WebCore::RTCPriorityType::Medium),
            static_cast<uint64_t>(WebCore::RTCPriorityType::High),
        } },
#endif
        { "WebCore::LineCap"_s, sizeof(WebCore::LineCap), false, {
            static_cast<uint64_t>(WebCore::LineCap::Butt),
            static_cast<uint64_t>(WebCore::LineCap::Round),
            static_cast<uint64_t>(WebCore::LineCap::Square),
        } },
        { "WebCore::LineJoin"_s, sizeof(WebCore::LineJoin), false, {
            static_cast<uint64_t>(WebCore::LineJoin::Miter),
            static_cast<uint64_t>(WebCore::LineJoin::Round),
            static_cast<uint64_t>(WebCore::LineJoin::Bevel),
        } },
        { "WebCore::StrokeStyle"_s, sizeof(WebCore::StrokeStyle), false, {
            static_cast<uint64_t>(WebCore::StrokeStyle::NoStroke),
            static_cast<uint64_t>(WebCore::StrokeStyle::SolidStroke),
            static_cast<uint64_t>(WebCore::StrokeStyle::DottedStroke),
            static_cast<uint64_t>(WebCore::StrokeStyle::DashedStroke),
            static_cast<uint64_t>(WebCore::StrokeStyle::DoubleStroke),
            static_cast<uint64_t>(WebCore::StrokeStyle::WavyStroke),
        } },
        { "WebCore::TextDrawingMode"_s, sizeof(WebCore::TextDrawingMode), true, {
            static_cast<uint64_t>(WebCore::TextDrawingMode::Fill),
            static_cast<uint64_t>(WebCore::TextDrawingMode::Stroke),
        } },
        { "WebCore::DecodingMode"_s, sizeof(WebCore::DecodingMode), false, {
            static_cast<uint64_t>(WebCore::DecodingMode::Auto),
            static_cast<uint64_t>(WebCore::DecodingMode::Synchronous),
            static_cast<uint64_t>(WebCore::DecodingMode::Asynchronous),
        } },
        { "WebCore::DocumentMarkerLineStyleMode"_s, sizeof(WebCore::DocumentMarkerLineStyleMode), false, {
            static_cast<uint64_t>(WebCore::DocumentMarkerLineStyleMode::TextCheckingDictationPhraseWithAlternatives),
            static_cast<uint64_t>(WebCore::DocumentMarkerLineStyleMode::Spelling),
            static_cast<uint64_t>(WebCore::DocumentMarkerLineStyleMode::Grammar),
            static_cast<uint64_t>(WebCore::DocumentMarkerLineStyleMode::AutocorrectionReplacement),
            static_cast<uint64_t>(WebCore::DocumentMarkerLineStyleMode::DictationAlternatives),
        } },
        { "WebCore::ShadowRadiusMode"_s, sizeof(WebCore::ShadowRadiusMode), false, {
            0, 1
        } },
#if ENABLE(VIDEO)
        { "WebCore::GenericCueData::Alignment"_s, sizeof(WebCore::GenericCueData::Alignment), false, {
            static_cast<uint64_t>(WebCore::GenericCueData::Alignment::None),
            static_cast<uint64_t>(WebCore::GenericCueData::Alignment::Start),
            static_cast<uint64_t>(WebCore::GenericCueData::Alignment::Middle),
            static_cast<uint64_t>(WebCore::GenericCueData::Alignment::End),
        } },
#endif
#if ENABLE(VIDEO)
        { "WebCore::GenericCueData::Status"_s, sizeof(WebCore::GenericCueData::Status), false, {
            static_cast<uint64_t>(WebCore::GenericCueData::Status::Uninitialized),
            static_cast<uint64_t>(WebCore::GenericCueData::Status::Partial),
            static_cast<uint64_t>(WebCore::GenericCueData::Status::Complete),
        } },
#endif
        { "WebCore::ImageOrientation::Orientation"_s, sizeof(WebCore::ImageOrientation::Orientation), false, {
            static_cast<uint64_t>(WebCore::ImageOrientation::Orientation::FromImage),
            static_cast<uint64_t>(WebCore::ImageOrientation::Orientation::OriginTopLeft),
            static_cast<uint64_t>(WebCore::ImageOrientation::Orientation::OriginTopRight),
            static_cast<uint64_t>(WebCore::ImageOrientation::Orientation::OriginBottomRight),
            static_cast<uint64_t>(WebCore::ImageOrientation::Orientation::OriginBottomLeft),
            static_cast<uint64_t>(WebCore::ImageOrientation::Orientation::OriginLeftTop),
            static_cast<uint64_t>(WebCore::ImageOrientation::Orientation::OriginRightTop),
            static_cast<uint64_t>(WebCore::ImageOrientation::Orientation::OriginRightBottom),
            static_cast<uint64_t>(WebCore::ImageOrientation::Orientation::OriginLeftBottom),
        } },
        { "WebCore::CrossOriginOpenerPolicyValue"_s, sizeof(WebCore::CrossOriginOpenerPolicyValue), false, {
            static_cast<uint64_t>(WebCore::CrossOriginOpenerPolicyValue::UnsafeNone),
            static_cast<uint64_t>(WebCore::CrossOriginOpenerPolicyValue::SameOrigin),
            static_cast<uint64_t>(WebCore::CrossOriginOpenerPolicyValue::SameOriginPlusCOEP),
            static_cast<uint64_t>(WebCore::CrossOriginOpenerPolicyValue::SameOriginAllowPopups),
        } },
        { "WebCore::SubstituteData::SessionHistoryVisibility"_s, sizeof(WebCore::SubstituteData::SessionHistoryVisibility), false, {
            0, 1
        } },
        { "WebCore::HTTPCookieAcceptPolicy"_s, sizeof(WebCore::HTTPCookieAcceptPolicy), false, {
            static_cast<uint64_t>(WebCore::HTTPCookieAcceptPolicy::AlwaysAccept),
            static_cast<uint64_t>(WebCore::HTTPCookieAcceptPolicy::Never),
            static_cast<uint64_t>(WebCore::HTTPCookieAcceptPolicy::OnlyFromMainDocumentDomain),
            static_cast<uint64_t>(WebCore::HTTPCookieAcceptPolicy::ExclusivelyFromMainDocumentDomain),
        } },
        { "WebCore::NetworkLoadPriority"_s, sizeof(WebCore::NetworkLoadPriority), false, {
            static_cast<uint64_t>(WebCore::NetworkLoadPriority::Low),
            static_cast<uint64_t>(WebCore::NetworkLoadPriority::Medium),
            static_cast<uint64_t>(WebCore::NetworkLoadPriority::High),
            static_cast<uint64_t>(WebCore::NetworkLoadPriority::Unknown),
        } },
        { "WebCore::PrivacyStance"_s, sizeof(WebCore::PrivacyStance), false, {
            static_cast<uint64_t>(WebCore::PrivacyStance::Unknown),
            static_cast<uint64_t>(WebCore::PrivacyStance::NotEligible),
            static_cast<uint64_t>(WebCore::PrivacyStance::Proxied),
            static_cast<uint64_t>(WebCore::PrivacyStance::Failed),
            static_cast<uint64_t>(WebCore::PrivacyStance::Direct),
            static_cast<uint64_t>(WebCore::PrivacyStance::FailedUnreachable),
        } },
        { "WebCore::ThirdPartyCookieBlockingMode"_s, sizeof(WebCore::ThirdPartyCookieBlockingMode), false, {
            static_cast<uint64_t>(WebCore::ThirdPartyCookieBlockingMode::All),
            static_cast<uint64_t>(WebCore::ThirdPartyCookieBlockingMode::AllExceptBetweenAppBoundDomains),
            static_cast<uint64_t>(WebCore::ThirdPartyCookieBlockingMode::AllExceptManagedDomains),
            static_cast<uint64_t>(WebCore::ThirdPartyCookieBlockingMode::AllOnSitesWithoutUserInteraction),
            static_cast<uint64_t>(WebCore::ThirdPartyCookieBlockingMode::OnlyAccordingToPerDomainPolicy),
        } },
        { "WebCore::FirstPartyWebsiteDataRemovalMode"_s, sizeof(WebCore::FirstPartyWebsiteDataRemovalMode), false, {
            static_cast<uint64_t>(WebCore::FirstPartyWebsiteDataRemovalMode::AllButCookies),
            static_cast<uint64_t>(WebCore::FirstPartyWebsiteDataRemovalMode::None),
            static_cast<uint64_t>(WebCore::FirstPartyWebsiteDataRemovalMode::AllButCookiesLiveOnTestingTimeout),
            static_cast<uint64_t>(WebCore::FirstPartyWebsiteDataRemovalMode::AllButCookiesReproTestingTimeout),
        } },
        { "WebCore::DragApplicationFlags"_s, sizeof(WebCore::DragApplicationFlags), true, {
            static_cast<uint64_t>(WebCore::DragApplicationFlags::IsModal),
            static_cast<uint64_t>(WebCore::DragApplicationFlags::IsSource),
            static_cast<uint64_t>(WebCore::DragApplicationFlags::HasAttachedSheet),
            static_cast<uint64_t>(WebCore::DragApplicationFlags::IsCopyKeyDown),
        } },
        { "WebCore::TextCheckingType"_s, sizeof(WebCore::TextCheckingType), true, {
            static_cast<uint64_t>(WebCore::TextCheckingType::None),
            static_cast<uint64_t>(WebCore::TextCheckingType::Spelling),
            static_cast<uint64_t>(WebCore::TextCheckingType::Grammar),
            static_cast<uint64_t>(WebCore::TextCheckingType::Link),
            static_cast<uint64_t>(WebCore::TextCheckingType::Quote),
            static_cast<uint64_t>(WebCore::TextCheckingType::Dash),
            static_cast<uint64_t>(WebCore::TextCheckingType::Replacement),
            static_cast<uint64_t>(WebCore::TextCheckingType::Correction),
            static_cast<uint64_t>(WebCore::TextCheckingType::ShowCorrectionPanel),
        } },
#if ENABLE(SERVICE_WORKER)
        { "WebCore::ServiceWorkerClientType"_s, sizeof(WebCore::ServiceWorkerClientType), false, {
            static_cast<uint64_t>(WebCore::ServiceWorkerClientType::Window),
            static_cast<uint64_t>(WebCore::ServiceWorkerClientType::Worker),
            static_cast<uint64_t>(WebCore::ServiceWorkerClientType::Sharedworker),
            static_cast<uint64_t>(WebCore::ServiceWorkerClientType::All),
        } },
#endif
#if ENABLE(SERVICE_WORKER)
        { "WebCore::ServiceWorkerJobType"_s, sizeof(WebCore::ServiceWorkerJobType), false, {
            static_cast<uint64_t>(WebCore::ServiceWorkerJobType::Register),
            static_cast<uint64_t>(WebCore::ServiceWorkerJobType::Unregister),
            static_cast<uint64_t>(WebCore::ServiceWorkerJobType::Update),
        } },
#endif
#if ENABLE(SERVICE_WORKER)
        { "WebCore::ServiceWorkerRegistrationState"_s, sizeof(WebCore::ServiceWorkerRegistrationState), false, {
            static_cast<uint64_t>(WebCore::ServiceWorkerRegistrationState::Installing),
            static_cast<uint64_t>(WebCore::ServiceWorkerRegistrationState::Waiting),
            static_cast<uint64_t>(WebCore::ServiceWorkerRegistrationState::Active),
        } },
#endif
#if ENABLE(SERVICE_WORKER)
        { "WebCore::ServiceWorkerState"_s, sizeof(WebCore::ServiceWorkerState), false, {
            static_cast<uint64_t>(WebCore::ServiceWorkerState::Parsed),
            static_cast<uint64_t>(WebCore::ServiceWorkerState::Installing),
            static_cast<uint64_t>(WebCore::ServiceWorkerState::Installed),
            static_cast<uint64_t>(WebCore::ServiceWorkerState::Activating),
            static_cast<uint64_t>(WebCore::ServiceWorkerState::Activated),
            static_cast<uint64_t>(WebCore::ServiceWorkerState::Redundant),
        } },
#endif
#if ENABLE(SERVICE_WORKER)
        { "WebCore::ServiceWorkerClientFrameType"_s, sizeof(WebCore::ServiceWorkerClientFrameType), false, {
            static_cast<uint64_t>(WebCore::ServiceWorkerClientFrameType::Auxiliary),
            static_cast<uint64_t>(WebCore::ServiceWorkerClientFrameType::TopLevel),
            static_cast<uint64_t>(WebCore::ServiceWorkerClientFrameType::Nested),
            static_cast<uint64_t>(WebCore::ServiceWorkerClientFrameType::None),
        } },
#endif
#if ENABLE(SERVICE_WORKER)
        { "WebCore::ShouldNotifyWhenResolved"_s, sizeof(WebCore::ShouldNotifyWhenResolved), false, {
            0, 1
        } },
#endif
#if ENABLE(SERVICE_WORKER)
        { "WebCore::ServiceWorkerUpdateViaCache"_s, sizeof(WebCore::ServiceWorkerUpdateViaCache), false, {
            static_cast<uint64_t>(WebCore::ServiceWorkerUpdateViaCache::Imports),
            static_cast<uint64_t>(WebCore::ServiceWorkerUpdateViaCache::All),
            static_cast<uint64_t>(WebCore::ServiceWorkerUpdateViaCache::None),
        } },
#endif
#if ENABLE(TRACKING_PREVENTION)
        { "WebCore::StorageAccessWasGranted"_s, sizeof(WebCore::StorageAccessWasGranted), false, {
            0, 1
        } },
#endif
#if ENABLE(TRACKING_PREVENTION)
        { "WebCore::StorageAccessPromptWasShown"_s, sizeof(WebCore::StorageAccessPromptWasShown), false, {
            0, 1
        } },
#endif
#if ENABLE(TRACKING_PREVENTION)
        { "WebCore::StorageAccessScope"_s, sizeof(WebCore::StorageAccessScope), false, {
            0, 1
        } },
#endif
#if ENABLE(TRACKING_PREVENTION)
        { "WebCore::StorageAccessQuickResult"_s, sizeof(WebCore::StorageAccessQuickResult), false, {
            0, 1
        } },
#endif
#if ENABLE(MEDIA_STREAM)
        { "WebCore::MediaConstraint::DataType"_s, sizeof(WebCore::MediaConstraint::DataType), false, {
            static_cast<uint64_t>(WebCore::MediaConstraint::DataType::None),
            static_cast<uint64_t>(WebCore::MediaConstraint::DataType::Integer),
            static_cast<uint64_t>(WebCore::MediaConstraint::DataType::Double),
            static_cast<uint64_t>(WebCore::MediaConstraint::DataType::Boolean),
            static_cast<uint64_t>(WebCore::MediaConstraint::DataType::String),
        } },
#endif
#if ENABLE(MEDIA_STREAM)
        { "WebCore::MediaConstraintType"_s, sizeof(WebCore::MediaConstraintType), false, {
            static_cast<uint64_t>(WebCore::MediaConstraintType::Unknown),
            static_cast<uint64_t>(WebCore::MediaConstraintType::Width),
            static_cast<uint64_t>(WebCore::MediaConstraintType::Height),
            static_cast<uint64_t>(WebCore::MediaConstraintType::AspectRatio),
            static_cast<uint64_t>(WebCore::MediaConstraintType::FrameRate),
            static_cast<uint64_t>(WebCore::MediaConstraintType::FacingMode),
            static_cast<uint64_t>(WebCore::MediaConstraintType::Volume),
            static_cast<uint64_t>(WebCore::MediaConstraintType::SampleRate),
            static_cast<uint64_t>(WebCore::MediaConstraintType::SampleSize),
            static_cast<uint64_t>(WebCore::MediaConstraintType::EchoCancellation),
            static_cast<uint64_t>(WebCore::MediaConstraintType::DeviceId),
            static_cast<uint64_t>(WebCore::MediaConstraintType::GroupId),
            static_cast<uint64_t>(WebCore::MediaConstraintType::DisplaySurface),
            static_cast<uint64_t>(WebCore::MediaConstraintType::LogicalSurface),
            static_cast<uint64_t>(WebCore::MediaConstraintType::Zoom),
        } },
#endif
#if ENABLE(MEDIA_STREAM)
        { "WebCore::VideoFacingMode"_s, sizeof(WebCore::VideoFacingMode), false, {
            static_cast<uint64_t>(WebCore::VideoFacingMode::Unknown),
            static_cast<uint64_t>(WebCore::VideoFacingMode::User),
            static_cast<uint64_t>(WebCore::VideoFacingMode::Environment),
            static_cast<uint64_t>(WebCore::VideoFacingMode::Left),
            static_cast<uint64_t>(WebCore::VideoFacingMode::Right),
        } },
#endif
#if ENABLE(MEDIA_STREAM)
        { "WebCore::DisplaySurfaceType"_s, sizeof(WebCore::DisplaySurfaceType), false, {
            static_cast<uint64_t>(WebCore::DisplaySurfaceType::Monitor),
            static_cast<uint64_t>(WebCore::DisplaySurfaceType::Window),
            static_cast<uint64_t>(WebCore::DisplaySurfaceType::Application),
            static_cast<uint64_t>(WebCore::DisplaySurfaceType::Browser),
            static_cast<uint64_t>(WebCore::DisplaySurfaceType::Invalid),
        } },
#endif
#if ENABLE(MEDIA_STREAM)
        { "WebCore::CaptureDevice::DeviceType"_s, sizeof(WebCore::CaptureDevice::DeviceType), false, {
            static_cast<uint64_t>(WebCore::CaptureDevice::DeviceType::Unknown),
            static_cast<uint64_t>(WebCore::CaptureDevice::DeviceType::Microphone),
            static_cast<uint64_t>(WebCore::CaptureDevice::DeviceType::Speaker),
            static_cast<uint64_t>(WebCore::CaptureDevice::DeviceType::Camera),
            static_cast<uint64_t>(WebCore::CaptureDevice::DeviceType::Screen),
            static_cast<uint64_t>(WebCore::CaptureDevice::DeviceType::Window),
            static_cast<uint64_t>(WebCore::CaptureDevice::DeviceType::SystemAudio),
        } },
#endif
#if ENABLE(MEDIA_STREAM)
        { "WebCore::RealtimeMediaSourceCapabilities::EchoCancellation"_s, sizeof(WebCore::RealtimeMediaSourceCapabilities::EchoCancellation), false, {
            0, 1
        } },
#endif
#if ENABLE(MEDIA_STREAM)
        { "WebCore::MockMediaDevice::Flag"_s, sizeof(WebCore::MockMediaDevice::Flag), true, {
            static_cast<uint64_t>(WebCore::MockMediaDevice::Flag::Ephemeral),
            static_cast<uint64_t>(WebCore::MockMediaDevice::Flag::Invalid),
        } },
#endif
        { "WebCore::PlatformVideoColorPrimaries"_s, sizeof(WebCore::PlatformVideoColorPrimaries), false, {
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::Bt709),
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::Bt470bg),
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::Smpte170m),
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::Bt470m),
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::Smpte240m),
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::Film),
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::Bt2020),
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::SmpteSt4281),
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::SmpteRp431),
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::SmpteEg432),
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::JedecP22Phosphors),
            static_cast<uint64_t>(WebCore::PlatformVideoColorPrimaries::Unspecified),
        } },
        { "WebCore::PlatformVideoTransferCharacteristics"_s, sizeof(WebCore::PlatformVideoTransferCharacteristics), false, {
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Bt709),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Smpte170m),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Iec6196621),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Gamma22curve),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Gamma28curve),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Smpte240m),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Linear),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Log),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::LogSqrt),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Iec6196624),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Bt1361ExtendedColourGamut),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Bt2020_10bit),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Bt2020_12bit),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::SmpteSt2084),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::SmpteSt4281),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::AribStdB67Hlg),
            static_cast<uint64_t>(WebCore::PlatformVideoTransferCharacteristics::Unspecified),
        } },
        { "WebCore::PlatformVideoMatrixCoefficients"_s, sizeof(WebCore::PlatformVideoMatrixCoefficients), false, {
            static_cast<uint64_t>(WebCore::PlatformVideoMatrixCoefficients::Rgb),
            static_cast<uint64_t>(WebCore::PlatformVideoMatrixCoefficients::Bt709),
            static_cast<uint64_t>(WebCore::PlatformVideoMatrixCoefficients::Bt470bg),
            static_cast<uint64_t>(WebCore::PlatformVideoMatrixCoefficients::Smpte170m),
            static_cast<uint64_t>(WebCore::PlatformVideoMatrixCoefficients::Smpte240m),
            static_cast<uint64_t>(WebCore::PlatformVideoMatrixCoefficients::Fcc),
            static_cast<uint64_t>(WebCore::PlatformVideoMatrixCoefficients::YCgCo),
            static_cast<uint64_t>(WebCore::PlatformVideoMatrixCoefficients::Bt2020NonconstantLuminance),
            static_cast<uint64_t>(WebCore::PlatformVideoMatrixCoefficients::Bt2020ConstantLuminance),
            static_cast<uint64_t>(WebCore::PlatformVideoMatrixCoefficients::Unspecified),
        } },
        { "WebCore::PolicyAction"_s, sizeof(WebCore::PolicyAction), false, {
            static_cast<uint64_t>(WebCore::PolicyAction::Use),
            static_cast<uint64_t>(WebCore::PolicyAction::Download),
            static_cast<uint64_t>(WebCore::PolicyAction::Ignore),
            static_cast<uint64_t>(WebCore::PolicyAction::LoadWillContinueInAnotherProcess),
        } },
        { "WebCore::ReloadOption"_s, sizeof(WebCore::ReloadOption), true, {
            static_cast<uint64_t>(WebCore::ReloadOption::ExpiredOnly),
            static_cast<uint64_t>(WebCore::ReloadOption::FromOrigin),
            static_cast<uint64_t>(WebCore::ReloadOption::DisableContentBlockers),
        } },
        { "WebCore::FrameLoadType"_s, sizeof(WebCore::FrameLoadType), false, {
            static_cast<uint64_t>(WebCore::FrameLoadType::Standard),
            static_cast<uint64_t>(WebCore::FrameLoadType::Back),
            static_cast<uint64_t>(WebCore::FrameLoadType::Forward),
            static_cast<uint64_t>(WebCore::FrameLoadType::IndexedBackForward),
            static_cast<uint64_t>(WebCore::FrameLoadType::Reload),
            static_cast<uint64_t>(WebCore::FrameLoadType::Same),
            static_cast<uint64_t>(WebCore::FrameLoadType::RedirectWithLockedBackForwardList),
            static_cast<uint64_t>(WebCore::FrameLoadType::Replace),
            static_cast<uint64_t>(WebCore::FrameLoadType::ReloadFromOrigin),
            static_cast<uint64_t>(WebCore::FrameLoadType::ReloadExpiredOnly),
        } },
        { "WebCore::NavigationType"_s, sizeof(WebCore::NavigationType), false, {
            static_cast<uint64_t>(WebCore::NavigationType::LinkClicked),
            static_cast<uint64_t>(WebCore::NavigationType::FormSubmitted),
            static_cast<uint64_t>(WebCore::NavigationType::BackForward),
            static_cast<uint64_t>(WebCore::NavigationType::Reload),
            static_cast<uint64_t>(WebCore::NavigationType::FormResubmitted),
            static_cast<uint64_t>(WebCore::NavigationType::Other),
        } },
        { "WebCore::BrowsingContextGroupSwitchDecision"_s, sizeof(WebCore::BrowsingContextGroupSwitchDecision), false, {
            static_cast<uint64_t>(WebCore::BrowsingContextGroupSwitchDecision::StayInGroup),
            static_cast<uint64_t>(WebCore::BrowsingContextGroupSwitchDecision::NewSharedGroup),
            static_cast<uint64_t>(WebCore::BrowsingContextGroupSwitchDecision::NewIsolatedGroup),
        } },
        { "WebCore::ShouldOpenExternalURLsPolicy"_s, sizeof(WebCore::ShouldOpenExternalURLsPolicy), false, {
            static_cast<uint64_t>(WebCore::ShouldOpenExternalURLsPolicy::ShouldNotAllow),
            static_cast<uint64_t>(WebCore::ShouldOpenExternalURLsPolicy::ShouldAllowExternalSchemesButNotAppLinks),
            static_cast<uint64_t>(WebCore::ShouldOpenExternalURLsPolicy::ShouldAllow),
        } },
        { "WebCore::MouseEventPolicy"_s, sizeof(WebCore::MouseEventPolicy), false, {
            static_cast<uint64_t>(WebCore::MouseEventPolicy::Default),
#if ENABLE(IOS_TOUCH_EVENTS)
            static_cast<uint64_t>(WebCore::MouseEventPolicy::SynthesizeTouchEvents),
#endif
        } },
        { "WebCore::ColorSchemePreference"_s, sizeof(WebCore::ColorSchemePreference), false, {
            static_cast<uint64_t>(WebCore::ColorSchemePreference::NoPreference),
            static_cast<uint64_t>(WebCore::ColorSchemePreference::Light),
            static_cast<uint64_t>(WebCore::ColorSchemePreference::Dark),
        } },
        { "WebCore::ModalContainerObservationPolicy"_s, sizeof(WebCore::ModalContainerObservationPolicy), false, {
            0, 1
        } },
        { "WebCore::AllowsContentJavaScript"_s, sizeof(WebCore::AllowsContentJavaScript), false, {
            0, 1
        } },
        { "WebCore::AdvancedPrivacyProtections"_s, sizeof(WebCore::AdvancedPrivacyProtections), true, {
            static_cast<uint64_t>(WebCore::AdvancedPrivacyProtections::BaselineProtections),
            static_cast<uint64_t>(WebCore::AdvancedPrivacyProtections::HTTPSFirst),
            static_cast<uint64_t>(WebCore::AdvancedPrivacyProtections::HTTPSOnly),
            static_cast<uint64_t>(WebCore::AdvancedPrivacyProtections::HTTPSOnlyExplicitlyBypassedForDomain),
            static_cast<uint64_t>(WebCore::AdvancedPrivacyProtections::FailClosed),
            static_cast<uint64_t>(WebCore::AdvancedPrivacyProtections::WebSearchContent),
            static_cast<uint64_t>(WebCore::AdvancedPrivacyProtections::FingerprintingProtections),
            static_cast<uint64_t>(WebCore::AdvancedPrivacyProtections::EnhancedNetworkPrivacy),
            static_cast<uint64_t>(WebCore::AdvancedPrivacyProtections::LinkDecorationFiltering),
        } },
        { "WebCore::ViolationReportType"_s, sizeof(WebCore::ViolationReportType), false, {
            static_cast<uint64_t>(WebCore::ViolationReportType::COEPInheritenceViolation),
            static_cast<uint64_t>(WebCore::ViolationReportType::CORPViolation),
            static_cast<uint64_t>(WebCore::ViolationReportType::ContentSecurityPolicy),
            static_cast<uint64_t>(WebCore::ViolationReportType::CrossOriginOpenerPolicy),
            static_cast<uint64_t>(WebCore::ViolationReportType::Deprecation),
            static_cast<uint64_t>(WebCore::ViolationReportType::StandardReportingAPIViolation),
            static_cast<uint64_t>(WebCore::ViolationReportType::Test),
        } },
        { "WebCore::COEPDisposition"_s, sizeof(WebCore::COEPDisposition), false, {
            0, 1
        } },
        { "WebCore::LinkIconType"_s, sizeof(WebCore::LinkIconType), false, {
            static_cast<uint64_t>(WebCore::LinkIconType::Favicon),
            static_cast<uint64_t>(WebCore::LinkIconType::TouchIcon),
            static_cast<uint64_t>(WebCore::LinkIconType::TouchPrecomposedIcon),
        } },
        { "WebCore::PluginLoadClientPolicy"_s, sizeof(WebCore::PluginLoadClientPolicy), false, {
            static_cast<uint64_t>(WebCore::PluginLoadClientPolicy::Undefined),
            static_cast<uint64_t>(WebCore::PluginLoadClientPolicy::Block),
            static_cast<uint64_t>(WebCore::PluginLoadClientPolicy::Ask),
            static_cast<uint64_t>(WebCore::PluginLoadClientPolicy::Allow),
            static_cast<uint64_t>(WebCore::PluginLoadClientPolicy::AllowAlways),
        } },
        { "WebCore::PasteboardItemPresentationStyle"_s, sizeof(WebCore::PasteboardItemPresentationStyle), false, {
            static_cast<uint64_t>(WebCore::PasteboardItemPresentationStyle::Unspecified),
            static_cast<uint64_t>(WebCore::PasteboardItemPresentationStyle::Inline),
            static_cast<uint64_t>(WebCore::PasteboardItemPresentationStyle::Attachment),
        } },
#if HAVE(SCREEN_CAPTURE_KIT)
        { "WebCore::DisplayCapturePromptType"_s, sizeof(WebCore::DisplayCapturePromptType), false, {
            static_cast<uint64_t>(WebCore::DisplayCapturePromptType::Window),
            static_cast<uint64_t>(WebCore::DisplayCapturePromptType::Screen),
            static_cast<uint64_t>(WebCore::DisplayCapturePromptType::UserChoose),
        } },
#endif
        { "WebCore::TextIndicatorPresentationTransition"_s, sizeof(WebCore::TextIndicatorPresentationTransition), false, {
            static_cast<uint64_t>(WebCore::TextIndicatorPresentationTransition::None),
            static_cast<uint64_t>(WebCore::TextIndicatorPresentationTransition::Bounce),
            static_cast<uint64_t>(WebCore::TextIndicatorPresentationTransition::BounceAndCrossfade),
            static_cast<uint64_t>(WebCore::TextIndicatorPresentationTransition::FadeIn),
        } },
        { "WebCore::TextIndicatorOption"_s, sizeof(WebCore::TextIndicatorOption), true, {
            static_cast<uint64_t>(WebCore::TextIndicatorOption::RespectTextColor),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::PaintBackgrounds),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::PaintAllContent),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::IncludeSnapshotWithSelectionHighlight),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::TightlyFitContent),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::UseBoundingRectAndPaintAllContentForComplexRanges),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::IncludeMarginIfRangeMatchesSelection),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::ExpandClipBeyondVisibleRect),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::DoNotClipToVisibleRect),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::IncludeSnapshotOfAllVisibleContentWithoutSelection),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::UseSelectionRectForSizing),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::ComputeEstimatedBackgroundColor),
            static_cast<uint64_t>(WebCore::TextIndicatorOption::UseUserSelectAllCommonAncestor),
        } },
        { "WebCore::InteractionRegion::Type"_s, sizeof(WebCore::InteractionRegion::Type), false, {
            static_cast<uint64_t>(WebCore::InteractionRegion::Type::Interaction),
            static_cast<uint64_t>(WebCore::InteractionRegion::Type::Occlusion),
            static_cast<uint64_t>(WebCore::InteractionRegion::Type::Guard),
        } },
        { "WebCore::InteractionRegion::CornerMask"_s, sizeof(WebCore::InteractionRegion::CornerMask), true, {
            static_cast<uint64_t>(WebCore::InteractionRegion::CornerMask::MinXMinYCorner),
            static_cast<uint64_t>(WebCore::InteractionRegion::CornerMask::MaxXMinYCorner),
            static_cast<uint64_t>(WebCore::InteractionRegion::CornerMask::MinXMaxYCorner),
            static_cast<uint64_t>(WebCore::InteractionRegion::CornerMask::MaxXMaxYCorner),
        } },
#if ENABLE(WEB_AUTHN)
        { "WebCore::MockWebAuthenticationConfiguration::UserVerification"_s, sizeof(WebCore::MockWebAuthenticationConfiguration::UserVerification), false, {
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::UserVerification::No),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::UserVerification::Yes),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::UserVerification::Cancel),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::UserVerification::Presence),
        } },
#endif
#if ENABLE(WEB_AUTHN)
        { "WebCore::MockWebAuthenticationConfiguration::HidStage"_s, sizeof(WebCore::MockWebAuthenticationConfiguration::HidStage), false, {
            0, 1
        } },
#endif
#if ENABLE(WEB_AUTHN)
        { "WebCore::MockWebAuthenticationConfiguration::HidSubStage"_s, sizeof(WebCore::MockWebAuthenticationConfiguration::HidSubStage), false, {
            0, 1
        } },
#endif
#if ENABLE(WEB_AUTHN)
        { "WebCore::MockWebAuthenticationConfiguration::HidError"_s, sizeof(WebCore::MockWebAuthenticationConfiguration::HidError), false, {
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::HidError::Success),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::HidError::DataNotSent),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::HidError::EmptyReport),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::HidError::WrongChannelId),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::HidError::MaliciousPayload),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::HidError::UnsupportedOptions),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::HidError::WrongNonce),
        } },
#endif
#if ENABLE(WEB_AUTHN)
        { "WebCore::MockWebAuthenticationConfiguration::NfcError"_s, sizeof(WebCore::MockWebAuthenticationConfiguration::NfcError), false, {
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::NfcError::Success),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::NfcError::NoTags),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::NfcError::WrongTagType),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::NfcError::NoConnections),
            static_cast<uint64_t>(WebCore::MockWebAuthenticationConfiguration::NfcError::MaliciousPayload),
        } },
#endif
        { "WebCore::StorageType"_s, sizeof(WebCore::StorageType), false, {
            static_cast<uint64_t>(WebCore::StorageType::Session),
            static_cast<uint64_t>(WebCore::StorageType::Local),
            static_cast<uint64_t>(WebCore::StorageType::TransientLocal),
        } },
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
        { "WebCore::AcceleratedEffectProperty"_s, sizeof(WebCore::AcceleratedEffectProperty), true, {
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::Opacity),
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::Transform),
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::Translate),
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::Rotate),
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::Scale),
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::OffsetPath),
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::OffsetDistance),
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::OffsetPosition),
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::OffsetAnchor),
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::OffsetRotate),
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::Filter),
#if ENABLE(FILTERS_LEVEL_2)
            static_cast<uint64_t>(WebCore::AcceleratedEffectProperty::BackdropFilter),
#endif
        } },
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
        { "WebCore::WebAnimationType"_s, sizeof(WebCore::WebAnimationType), false, {
            static_cast<uint64_t>(WebCore::WebAnimationType::CSSAnimation),
            static_cast<uint64_t>(WebCore::WebAnimationType::CSSTransition),
            static_cast<uint64_t>(WebCore::WebAnimationType::WebAnimation),
        } },
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
        { "WebCore::FillMode"_s, sizeof(WebCore::FillMode), false, {
            static_cast<uint64_t>(WebCore::FillMode::None),
            static_cast<uint64_t>(WebCore::FillMode::Forwards),
            static_cast<uint64_t>(WebCore::FillMode::Backwards),
            static_cast<uint64_t>(WebCore::FillMode::Both),
            static_cast<uint64_t>(WebCore::FillMode::Auto),
        } },
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
        { "WebCore::PlaybackDirection"_s, sizeof(WebCore::PlaybackDirection), false, {
            static_cast<uint64_t>(WebCore::PlaybackDirection::Normal),
            static_cast<uint64_t>(WebCore::PlaybackDirection::Reverse),
            static_cast<uint64_t>(WebCore::PlaybackDirection::Alternate),
            static_cast<uint64_t>(WebCore::PlaybackDirection::AlternateReverse),
        } },
#endif
#if ENABLE(THREADED_ANIMATION_RESOLUTION)
        { "WebCore::CompositeOperation"_s, sizeof(WebCore::CompositeOperation), false, {
            static_cast<uint64_t>(WebCore::CompositeOperation::Replace),
            static_cast<uint64_t>(WebCore::CompositeOperation::Add),
            static_cast<uint64_t>(WebCore::CompositeOperation::Accumulate),
        } },
#endif
#if PLATFORM(MAC)
        { "WebCore::CaretAnimatorType"_s, sizeof(WebCore::CaretAnimatorType), false, {
            static_cast<uint64_t>(WebCore::CaretAnimatorType::Default),
            static_cast<uint64_t>(WebCore::CaretAnimatorType::Dictation),
        } },
#endif
        { "WebCore::ProtectionSpace::ServerType"_s, sizeof(WebCore::ProtectionSpace::ServerType), false, {
            static_cast<uint64_t>(WebCore::ProtectionSpace::ServerType::HTTP),
            static_cast<uint64_t>(WebCore::ProtectionSpace::ServerType::HTTPS),
            static_cast<uint64_t>(WebCore::ProtectionSpace::ServerType::FTP),
            static_cast<uint64_t>(WebCore::ProtectionSpace::ServerType::FTPS),
            static_cast<uint64_t>(WebCore::ProtectionSpace::ServerType::ProxyHTTP),
            static_cast<uint64_t>(WebCore::ProtectionSpace::ServerType::ProxyHTTPS),
            static_cast<uint64_t>(WebCore::ProtectionSpace::ServerType::ProxyFTP),
            static_cast<uint64_t>(WebCore::ProtectionSpace::ServerType::ProxySOCKS),
        } },
        { "WebCore::ProtectionSpace::AuthenticationScheme"_s, sizeof(WebCore::ProtectionSpace::AuthenticationScheme), false, {
            static_cast<uint64_t>(WebCore::ProtectionSpace::AuthenticationScheme::Default),
            static_cast<uint64_t>(WebCore::ProtectionSpace::AuthenticationScheme::HTTPBasic),
            static_cast<uint64_t>(WebCore::ProtectionSpace::AuthenticationScheme::HTTPDigest),
            static_cast<uint64_t>(WebCore::ProtectionSpace::AuthenticationScheme::HTMLForm),
            static_cast<uint64_t>(WebCore::ProtectionSpace::AuthenticationScheme::NTLM),
            static_cast<uint64_t>(WebCore::ProtectionSpace::AuthenticationScheme::Negotiate),
            static_cast<uint64_t>(WebCore::ProtectionSpace::AuthenticationScheme::ClientCertificateRequested),
            static_cast<uint64_t>(WebCore::ProtectionSpace::AuthenticationScheme::ServerTrustEvaluationRequested),
            static_cast<uint64_t>(WebCore::ProtectionSpace::AuthenticationScheme::OAuth),
#if USE(GLIB)
            static_cast<uint64_t>(WebCore::ProtectionSpace::AuthenticationScheme::ClientCertificatePINRequested),
#endif
            static_cast<uint64_t>(WebCore::ProtectionSpace::AuthenticationScheme::Unknown),
        } },
#if ENABLE(GPU_PROCESS)
        { "WebCore::ShapeDetection::BarcodeFormat"_s, sizeof(WebCore::ShapeDetection::BarcodeFormat), false, {
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Aztec),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Code_128),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Code_39),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Code_93),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Codabar),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Data_matrix),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Ean_13),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Ean_8),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Itf),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Pdf417),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Qr_code),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Unknown),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Upc_a),
            static_cast<uint64_t>(WebCore::ShapeDetection::BarcodeFormat::Upc_e),
        } },
#endif
#if ENABLE(GPU_PROCESS)
        { "WebCore::ShapeDetection::LandmarkType"_s, sizeof(WebCore::ShapeDetection::LandmarkType), false, {
            static_cast<uint64_t>(WebCore::ShapeDetection::LandmarkType::Mouth),
            static_cast<uint64_t>(WebCore::ShapeDetection::LandmarkType::Eye),
            static_cast<uint64_t>(WebCore::ShapeDetection::LandmarkType::Nose),
        } },
#endif
        { "WebCore::RenderAsTextFlag"_s, sizeof(WebCore::RenderAsTextFlag), true, {
            static_cast<uint64_t>(WebCore::RenderAsTextFlag::ShowAllLayers),
            static_cast<uint64_t>(WebCore::RenderAsTextFlag::ShowLayerNesting),
            static_cast<uint64_t>(WebCore::RenderAsTextFlag::ShowCompositedLayers),
            static_cast<uint64_t>(WebCore::RenderAsTextFlag::ShowOverflow),
            static_cast<uint64_t>(WebCore::RenderAsTextFlag::ShowSVGGeometry),
            static_cast<uint64_t>(WebCore::RenderAsTextFlag::ShowLayerFragments),
            static_cast<uint64_t>(WebCore::RenderAsTextFlag::ShowAddresses),
            static_cast<uint64_t>(WebCore::RenderAsTextFlag::ShowIDAndClass),
            static_cast<uint64_t>(WebCore::RenderAsTextFlag::PrintingMode),
            static_cast<uint64_t>(WebCore::RenderAsTextFlag::DontUpdateLayout),
            static_cast<uint64_t>(WebCore::RenderAsTextFlag::ShowLayoutState),
        } },
        { "WebCore::WebGPU::TextureFormat"_s, sizeof(WebCore::WebGPU::TextureFormat), false, {
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::R8unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::R8snorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::R8uint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::R8sint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::R16uint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::R16sint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::R16float),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rg8unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rg8snorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rg8uint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rg8sint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::R32uint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::R32sint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::R32float),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rg16uint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rg16sint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rg16float),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgba8unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgba8unormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgba8snorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgba8uint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgba8sint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bgra8unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bgra8unormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgb9e5ufloat),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgb10a2unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rg11b10ufloat),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rg32uint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rg32sint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rg32float),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgba16uint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgba16sint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgba16float),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgba32uint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgba32sint),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Rgba32float),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Stencil8),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Depth16unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Depth24plus),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Depth24plusStencil8),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Depth32float),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Depth32floatStencil8),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc1RgbaUnorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc1RgbaUnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc2RgbaUnorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc2RgbaUnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc3RgbaUnorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc3RgbaUnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc4RUnorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc4RSnorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc5RgUnorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc5RgSnorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc6hRgbUfloat),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc6hRgbFloat),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc7RgbaUnorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Bc7RgbaUnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Etc2Rgb8unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Etc2Rgb8unormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Etc2Rgb8a1unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Etc2Rgb8a1unormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Etc2Rgba8unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Etc2Rgba8unormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::EacR11unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::EacR11snorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::EacRg11unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::EacRg11snorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc4x4Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc4x4UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc5x4Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc5x4UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc5x5Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc5x5UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc6x5Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc6x5UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc6x6Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc6x6UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc8x5Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc8x5UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc8x6Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc8x6UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc8x8Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc8x8UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc10x5Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc10x5UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc10x6Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc10x6UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc10x8Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc10x8UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc10x10Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc10x10UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc12x10Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc12x10UnormSRGB),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc12x12Unorm),
            static_cast<uint64_t>(WebCore::WebGPU::TextureFormat::Astc12x12UnormSRGB),
        } },
#if ENABLE(MEDIA_STREAM)
        { "WebCore::MediaAccessDenialReason"_s, sizeof(WebCore::MediaAccessDenialReason), false, {
            static_cast<uint64_t>(WebCore::MediaAccessDenialReason::NoReason),
            static_cast<uint64_t>(WebCore::MediaAccessDenialReason::NoConstraints),
            static_cast<uint64_t>(WebCore::MediaAccessDenialReason::UserMediaDisabled),
            static_cast<uint64_t>(WebCore::MediaAccessDenialReason::NoCaptureDevices),
            static_cast<uint64_t>(WebCore::MediaAccessDenialReason::InvalidConstraint),
            static_cast<uint64_t>(WebCore::MediaAccessDenialReason::HardwareError),
            static_cast<uint64_t>(WebCore::MediaAccessDenialReason::PermissionDenied),
            static_cast<uint64_t>(WebCore::MediaAccessDenialReason::InvalidAccess),
            static_cast<uint64_t>(WebCore::MediaAccessDenialReason::OtherFailure),
        } },
#endif
        { "WebCore::WebGPU::TextureAspect"_s, sizeof(WebCore::WebGPU::TextureAspect), false, {
            static_cast<uint64_t>(WebCore::WebGPU::TextureAspect::All),
            static_cast<uint64_t>(WebCore::WebGPU::TextureAspect::StencilOnly),
            static_cast<uint64_t>(WebCore::WebGPU::TextureAspect::DepthOnly),
        } },
        { "WebCore::WebGPU::PowerPreference"_s, sizeof(WebCore::WebGPU::PowerPreference), false, {
            0, 1
        } },
        { "WebCore::WebGPU::PredefinedColorSpace"_s, sizeof(WebCore::WebGPU::PredefinedColorSpace), false, {
            static_cast<uint64_t>(WebCore::WebGPU::PredefinedColorSpace::SRGB),
        } },
        { "WebKit::WebEventModifier"_s, sizeof(WebKit::WebEventModifier), true, {
            static_cast<uint64_t>(WebKit::WebEventModifier::ShiftKey),
            static_cast<uint64_t>(WebKit::WebEventModifier::ControlKey),
            static_cast<uint64_t>(WebKit::WebEventModifier::AltKey),
            static_cast<uint64_t>(WebKit::WebEventModifier::MetaKey),
            static_cast<uint64_t>(WebKit::WebEventModifier::CapsLockKey),
        } },
        { "WebKit::WebEventType"_s, sizeof(WebKit::WebEventType), false, {
            static_cast<uint64_t>(WebKit::WebEventType::NoType),
            static_cast<uint64_t>(WebKit::WebEventType::MouseDown),
            static_cast<uint64_t>(WebKit::WebEventType::MouseUp),
            static_cast<uint64_t>(WebKit::WebEventType::MouseMove),
            static_cast<uint64_t>(WebKit::WebEventType::MouseForceChanged),
            static_cast<uint64_t>(WebKit::WebEventType::MouseForceDown),
            static_cast<uint64_t>(WebKit::WebEventType::MouseForceUp),
            static_cast<uint64_t>(WebKit::WebEventType::Wheel),
            static_cast<uint64_t>(WebKit::WebEventType::KeyDown),
            static_cast<uint64_t>(WebKit::WebEventType::KeyUp),
            static_cast<uint64_t>(WebKit::WebEventType::RawKeyDown),
            static_cast<uint64_t>(WebKit::WebEventType::Char),
#if ENABLE(TOUCH_EVENTS)
            static_cast<uint64_t>(WebKit::WebEventType::TouchStart),
#endif
#if ENABLE(TOUCH_EVENTS)
            static_cast<uint64_t>(WebKit::WebEventType::TouchMove),
#endif
#if ENABLE(TOUCH_EVENTS)
            static_cast<uint64_t>(WebKit::WebEventType::TouchEnd),
#endif
#if ENABLE(TOUCH_EVENTS)
            static_cast<uint64_t>(WebKit::WebEventType::TouchCancel),
#endif
#if ENABLE(MAC_GESTURE_EVENTS)
            static_cast<uint64_t>(WebKit::WebEventType::GestureStart),
#endif
#if ENABLE(MAC_GESTURE_EVENTS)
            static_cast<uint64_t>(WebKit::WebEventType::GestureChange),
#endif
#if ENABLE(MAC_GESTURE_EVENTS)
            static_cast<uint64_t>(WebKit::WebEventType::GestureEnd),
#endif
        } },
#if PLATFORM(IOS_FAMILY) && ENABLE(IOS_TOUCH_EVENTS)
        { "WebKit::WebPlatformTouchPoint::TouchType"_s, sizeof(WebKit::WebPlatformTouchPoint::TouchType), false, {
            0, 1
        } },
#endif
#if ENABLE(TOUCH_EVENTS)
        { "WebKit::WebPlatformTouchPoint::State"_s, sizeof(WebKit::WebPlatformTouchPoint::State), false, {
            static_cast<uint64_t>(WebKit::WebPlatformTouchPoint::State::Released),
            static_cast<uint64_t>(WebKit::WebPlatformTouchPoint::State::Pressed),
            static_cast<uint64_t>(WebKit::WebPlatformTouchPoint::State::Moved),
            static_cast<uint64_t>(WebKit::WebPlatformTouchPoint::State::Stationary),
            static_cast<uint64_t>(WebKit::WebPlatformTouchPoint::State::Cancelled),
        } },
#endif
        { "WebKit::WebMouseEventButton"_s, sizeof(WebKit::WebMouseEventButton), false, {
            static_cast<uint64_t>(WebKit::WebMouseEventButton::LeftButton),
            static_cast<uint64_t>(WebKit::WebMouseEventButton::MiddleButton),
            static_cast<uint64_t>(WebKit::WebMouseEventButton::RightButton),
            static_cast<uint64_t>(WebKit::WebMouseEventButton::NoButton),
        } },
        { "WebKit::WebMouseEventSyntheticClickType"_s, sizeof(WebKit::WebMouseEventSyntheticClickType), false, {
            static_cast<uint64_t>(WebKit::WebMouseEventSyntheticClickType::NoTap),
            static_cast<uint64_t>(WebKit::WebMouseEventSyntheticClickType::OneFingerTap),
            static_cast<uint64_t>(WebKit::WebMouseEventSyntheticClickType::TwoFingerTap),
        } },
        { "WebKit::WebWheelEvent::Granularity"_s, sizeof(WebKit::WebWheelEvent::Granularity), false, {
            static_cast<uint64_t>(WebKit::WebWheelEvent::Granularity::ScrollByPageWheelEvent),
            static_cast<uint64_t>(WebKit::WebWheelEvent::Granularity::ScrollByPixelWheelEvent),
        } },
        { "WebKit::WebWheelEvent::Phase"_s, sizeof(WebKit::WebWheelEvent::Phase), false, {
            static_cast<uint64_t>(WebKit::WebWheelEvent::Phase::PhaseNone),
            static_cast<uint64_t>(WebKit::WebWheelEvent::Phase::PhaseBegan),
            static_cast<uint64_t>(WebKit::WebWheelEvent::Phase::PhaseStationary),
            static_cast<uint64_t>(WebKit::WebWheelEvent::Phase::PhaseChanged),
            static_cast<uint64_t>(WebKit::WebWheelEvent::Phase::PhaseEnded),
            static_cast<uint64_t>(WebKit::WebWheelEvent::Phase::PhaseCancelled),
            static_cast<uint64_t>(WebKit::WebWheelEvent::Phase::PhaseMayBegin),
        } },
        { "WebKit::WebWheelEvent::MomentumEndType"_s, sizeof(WebKit::WebWheelEvent::MomentumEndType), false, {
            static_cast<uint64_t>(WebKit::WebWheelEvent::MomentumEndType::Unknown),
            static_cast<uint64_t>(WebKit::WebWheelEvent::MomentumEndType::Interrupted),
            static_cast<uint64_t>(WebKit::WebWheelEvent::MomentumEndType::Natural),
        } },
        { "WebKit::WebHitTestResultData::IsScrollbar"_s, sizeof(WebKit::WebHitTestResultData::IsScrollbar), false, {
            static_cast<uint64_t>(WebKit::WebHitTestResultData::IsScrollbar::No),
            static_cast<uint64_t>(WebKit::WebHitTestResultData::IsScrollbar::Vertical),
            static_cast<uint64_t>(WebKit::WebHitTestResultData::IsScrollbar::Horizontal),
        } },
        { "WebKit::WebPopupItem::Type"_s, sizeof(WebKit::WebPopupItem::Type), false, {
            0, 1
        } },
        { "WebKit::WebsiteMetaViewportPolicy"_s, sizeof(WebKit::WebsiteMetaViewportPolicy), false, {
            static_cast<uint64_t>(WebKit::WebsiteMetaViewportPolicy::Default),
            static_cast<uint64_t>(WebKit::WebsiteMetaViewportPolicy::Respect),
            static_cast<uint64_t>(WebKit::WebsiteMetaViewportPolicy::Ignore),
        } },
        { "WebKit::WebsiteMediaSourcePolicy"_s, sizeof(WebKit::WebsiteMediaSourcePolicy), false, {
            static_cast<uint64_t>(WebKit::WebsiteMediaSourcePolicy::Default),
            static_cast<uint64_t>(WebKit::WebsiteMediaSourcePolicy::Disable),
            static_cast<uint64_t>(WebKit::WebsiteMediaSourcePolicy::Enable),
        } },
        { "WebKit::WebsiteSimulatedMouseEventsDispatchPolicy"_s, sizeof(WebKit::WebsiteSimulatedMouseEventsDispatchPolicy), false, {
            static_cast<uint64_t>(WebKit::WebsiteSimulatedMouseEventsDispatchPolicy::Default),
            static_cast<uint64_t>(WebKit::WebsiteSimulatedMouseEventsDispatchPolicy::Allow),
            static_cast<uint64_t>(WebKit::WebsiteSimulatedMouseEventsDispatchPolicy::Deny),
        } },
        { "WebKit::WebsiteLegacyOverflowScrollingTouchPolicy"_s, sizeof(WebKit::WebsiteLegacyOverflowScrollingTouchPolicy), false, {
            static_cast<uint64_t>(WebKit::WebsiteLegacyOverflowScrollingTouchPolicy::Default),
            static_cast<uint64_t>(WebKit::WebsiteLegacyOverflowScrollingTouchPolicy::Disable),
            static_cast<uint64_t>(WebKit::WebsiteLegacyOverflowScrollingTouchPolicy::Enable),
        } },
#if ENABLE(WK_WEB_EXTENSIONS)
        { "WebKit::WebExtensionEventListenerType"_s, sizeof(WebKit::WebExtensionEventListenerType), false, {
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::Unknown),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::ActionOnClicked),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::AlarmsOnAlarm),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::CommandsOnCommand),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::ContextMenusOnClicked),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::CookiesOnChanged),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DevToolsElementsPanelOnSelectionChanged),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DevToolsExtensionPanelOnShown),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DevToolsExtensionPanelOnHidden),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DevToolsExtensionSidebarPaneOnShown),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DevToolsExtensionSidebarPaneOnHidden),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DevToolsExtensionPanelOnSearch),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DevToolsNetworkOnNavigated),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DevToolsNetworkOnRequestFinished),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DevToolsPanelsOnThemeChanged),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::NotificationsOnButtonClicked),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::NotificationsOnClicked),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::PermissionsOnAdded),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::PermissionsOnRemoved),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::PortOnDisconnect),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::PortOnMessage),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::RuntimeOnConnect),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::RuntimeOnConnectExternal),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::RuntimeOnInstalled),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::RuntimeOnMessage),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::RuntimeOnMessageExternal),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::RuntimeOnStartup),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::StorageOnChanged),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::TabsOnActivated),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::TabsOnAttached),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::TabsOnCreated),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::TabsOnDetached),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::TabsOnHighlighted),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::TabsOnMoved),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::TabsOnRemoved),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::TabsOnReplaced),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::TabsOnUpdated),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebNavigationOnBeforeNavigate),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebNavigationOnCommitted),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebNavigationOnCompleted),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebNavigationOnDOMContentLoaded),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebNavigationOnErrorOccurred),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebRequestOnAuthRequired),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebRequestOnBeforeRedirect),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebRequestOnBeforeRequest),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebRequestOnBeforeSendHeaders),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebRequestOnCompleted),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebRequestOnErrorOccurred),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebRequestOnHeadersReceived),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebRequestOnResponseStarted),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WebRequestOnSendHeaders),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WindowsOnCreated),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WindowsOnFocusChanged),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::WindowsOnRemoved),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DevToolsInspectedWindowOnResourceAdded),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DownloadsOnCreated),
            static_cast<uint64_t>(WebKit::WebExtensionEventListenerType::DownloadsOnChanged),
        } },
#endif
#if ENABLE(GPU_PROCESS)
        { "WebCore::WebGPU::FeatureName"_s, sizeof(WebCore::WebGPU::FeatureName), false, {
            static_cast<uint64_t>(WebCore::WebGPU::FeatureName::DepthClipControl),
            static_cast<uint64_t>(WebCore::WebGPU::FeatureName::Depth32floatStencil8),
            static_cast<uint64_t>(WebCore::WebGPU::FeatureName::TextureCompressionBc),
            static_cast<uint64_t>(WebCore::WebGPU::FeatureName::TextureCompressionEtc2),
            static_cast<uint64_t>(WebCore::WebGPU::FeatureName::TextureCompressionAstc),
            static_cast<uint64_t>(WebCore::WebGPU::FeatureName::TimestampQuery),
            static_cast<uint64_t>(WebCore::WebGPU::FeatureName::IndirectFirstInstance),
            static_cast<uint64_t>(WebCore::WebGPU::FeatureName::ShaderF16),
            static_cast<uint64_t>(WebCore::WebGPU::FeatureName::Rg11b10ufloatRenderable),
            static_cast<uint64_t>(WebCore::WebGPU::FeatureName::Bgra8unormStorage),
        } },
#endif
        { "WebKit::WebsiteDataFetchOption"_s, sizeof(WebKit::WebsiteDataFetchOption), true, {
            static_cast<uint64_t>(WebKit::WebsiteDataFetchOption::ComputeSizes),
            static_cast<uint64_t>(WebKit::WebsiteDataFetchOption::DoNotCreateProcesses),
        } },
        { "WebKit::WebsiteDataType"_s, sizeof(WebKit::WebsiteDataType), true, {
            static_cast<uint64_t>(WebKit::WebsiteDataType::Cookies),
            static_cast<uint64_t>(WebKit::WebsiteDataType::DiskCache),
            static_cast<uint64_t>(WebKit::WebsiteDataType::MemoryCache),
            static_cast<uint64_t>(WebKit::WebsiteDataType::OfflineWebApplicationCache),
            static_cast<uint64_t>(WebKit::WebsiteDataType::SessionStorage),
            static_cast<uint64_t>(WebKit::WebsiteDataType::LocalStorage),
            static_cast<uint64_t>(WebKit::WebsiteDataType::WebSQLDatabases),
            static_cast<uint64_t>(WebKit::WebsiteDataType::IndexedDBDatabases),
            static_cast<uint64_t>(WebKit::WebsiteDataType::MediaKeys),
            static_cast<uint64_t>(WebKit::WebsiteDataType::HSTSCache),
            static_cast<uint64_t>(WebKit::WebsiteDataType::SearchFieldRecentSearches),
            static_cast<uint64_t>(WebKit::WebsiteDataType::ResourceLoadStatistics),
            static_cast<uint64_t>(WebKit::WebsiteDataType::Credentials),
#if ENABLE(SERVICE_WORKER)
            static_cast<uint64_t>(WebKit::WebsiteDataType::ServiceWorkerRegistrations),
#endif
            static_cast<uint64_t>(WebKit::WebsiteDataType::DOMCache),
            static_cast<uint64_t>(WebKit::WebsiteDataType::DeviceIdHashSalt),
            static_cast<uint64_t>(WebKit::WebsiteDataType::PrivateClickMeasurements),
#if HAVE(ALTERNATIVE_SERVICE)
            static_cast<uint64_t>(WebKit::WebsiteDataType::AlternativeServices),
#endif
            static_cast<uint64_t>(WebKit::WebsiteDataType::FileSystem),
#if ENABLE(SERVICE_WORKER)
            static_cast<uint64_t>(WebKit::WebsiteDataType::BackgroundFetchStorage),
#endif
        } },
#if ENABLE(WEBXR)
        { "PlatformXR::SessionFeature"_s, sizeof(PlatformXR::SessionFeature), false, {
            static_cast<uint64_t>(PlatformXR::SessionFeature::ReferenceSpaceTypeViewer),
            static_cast<uint64_t>(PlatformXR::SessionFeature::ReferenceSpaceTypeLocal),
            static_cast<uint64_t>(PlatformXR::SessionFeature::ReferenceSpaceTypeLocalFloor),
            static_cast<uint64_t>(PlatformXR::SessionFeature::ReferenceSpaceTypeBoundedFloor),
            static_cast<uint64_t>(PlatformXR::SessionFeature::ReferenceSpaceTypeUnbounded),
#if ENABLE(WEBXR_HANDS)
            static_cast<uint64_t>(PlatformXR::SessionFeature::HandTracking),
#endif
        } },
#endif
    };
}

} // namespace WebKit

#endif // ENABLE(IPC_TESTING_API)
