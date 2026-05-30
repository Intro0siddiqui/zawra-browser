/*
 * THIS FILE WAS AUTOMATICALLY GENERATED, DO NOT EDIT.
 *
 * Copyright (C) 2011 Google Inc.  All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY GOOGLE, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

namespace WebCore {

enum EventTargetInterface {
#if ENABLE(APPLE_PAY)
    ApplePaySessionEventTargetInterfaceType = 1,
#endif
#if ENABLE(DOM_AUDIO_SESSION)
    DOMAudioSessionEventTargetInterfaceType = 2,
#endif
#if ENABLE(ENCRYPTED_MEDIA)
    MediaKeySessionEventTargetInterfaceType = 3,
#endif
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    WebKitMediaKeySessionEventTargetInterfaceType = 4,
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    ManagedMediaSourceEventTargetInterfaceType = 5,
    ManagedSourceBufferEventTargetInterfaceType = 6,
#endif
#if ENABLE(MEDIA_RECORDER)
    MediaRecorderEventTargetInterfaceType = 7,
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
    MediaSessionCoordinatorEventTargetInterfaceType = 8,
#endif
#if ENABLE(MEDIA_SOURCE)
    MediaSourceEventTargetInterfaceType = 9,
    SourceBufferEventTargetInterfaceType = 10,
    SourceBufferListEventTargetInterfaceType = 11,
#endif
#if ENABLE(MEDIA_STREAM)
    MediaDevicesEventTargetInterfaceType = 12,
    MediaStreamEventTargetInterfaceType = 13,
    MediaStreamTrackEventTargetInterfaceType = 14,
#endif
#if ENABLE(NOTIFICATIONS)
    NotificationEventTargetInterfaceType = 15,
#endif
#if ENABLE(OFFSCREEN_CANVAS)
    OffscreenCanvasEventTargetInterfaceType = 16,
#endif
#if ENABLE(PAYMENT_REQUEST)
    PaymentRequestEventTargetInterfaceType = 17,
    PaymentResponseEventTargetInterfaceType = 18,
#endif
#if ENABLE(PICTURE_IN_PICTURE_API)
    PictureInPictureWindowEventTargetInterfaceType = 19,
#endif
#if ENABLE(SERVICE_WORKER)
    BackgroundFetchRegistrationEventTargetInterfaceType = 20,
    ServiceWorkerEventTargetInterfaceType = 21,
    ServiceWorkerContainerEventTargetInterfaceType = 22,
    ServiceWorkerGlobalScopeEventTargetInterfaceType = 23,
    ServiceWorkerRegistrationEventTargetInterfaceType = 24,
#endif
#if ENABLE(SPEECH_SYNTHESIS)
    SpeechSynthesisEventTargetInterfaceType = 25,
    SpeechSynthesisUtteranceEventTargetInterfaceType = 26,
#endif
#if ENABLE(VIDEO)
    AudioTrackListEventTargetInterfaceType = 27,
    MediaControllerEventTargetInterfaceType = 28,
    TextTrackEventTargetInterfaceType = 29,
    TextTrackCueEventTargetInterfaceType = 30,
    TextTrackCueGenericEventTargetInterfaceType = 31,
    TextTrackListEventTargetInterfaceType = 32,
    VideoTrackListEventTargetInterfaceType = 33,
#endif
#if ENABLE(WEBXR)
    WebXRLayerEventTargetInterfaceType = 34,
    WebXRSessionEventTargetInterfaceType = 35,
    WebXRSpaceEventTargetInterfaceType = 36,
    WebXRSystemEventTargetInterfaceType = 37,
#endif
#if ENABLE(WEB_AUDIO)
    AudioNodeEventTargetInterfaceType = 38,
    BaseAudioContextEventTargetInterfaceType = 39,
#endif
#if ENABLE(WEB_CODECS)
    WebCodecsVideoDecoderEventTargetInterfaceType = 40,
    WebCodecsVideoEncoderEventTargetInterfaceType = 41,
#endif
#if ENABLE(WEB_RTC)
    RTCDTMFSenderEventTargetInterfaceType = 42,
    RTCDataChannelEventTargetInterfaceType = 43,
    RTCDtlsTransportEventTargetInterfaceType = 44,
    RTCIceTransportEventTargetInterfaceType = 45,
    RTCPeerConnectionEventTargetInterfaceType = 46,
    RTCRtpSFrameTransformEventTargetInterfaceType = 47,
    RTCRtpScriptTransformEventTargetInterfaceType = 48,
    RTCSctpTransportEventTargetInterfaceType = 49,
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    RemotePlaybackEventTargetInterfaceType = 50,
#endif
    EventTargetInterfaceType = 51,
    AbortSignalEventTargetInterfaceType = 52,
    BroadcastChannelEventTargetInterfaceType = 53,
    ClipboardEventTargetInterfaceType = 54,
    CookieStoreEventTargetInterfaceType = 55,
    DOMApplicationCacheEventTargetInterfaceType = 56,
    DedicatedWorkerGlobalScopeEventTargetInterfaceType = 57,
    EventSourceEventTargetInterfaceType = 58,
    FileReaderEventTargetInterfaceType = 59,
    FontFaceSetEventTargetInterfaceType = 60,
    GPUDeviceEventTargetInterfaceType = 61,
    IDBDatabaseEventTargetInterfaceType = 62,
    IDBOpenDBRequestEventTargetInterfaceType = 63,
    IDBRequestEventTargetInterfaceType = 64,
    IDBTransactionEventTargetInterfaceType = 65,
    LocalDOMWindowEventTargetInterfaceType = 66,
    MediaQueryListEventTargetInterfaceType = 67,
    MessagePortEventTargetInterfaceType = 68,
    NodeEventTargetInterfaceType = 69,
    PerformanceEventTargetInterfaceType = 70,
    PermissionStatusEventTargetInterfaceType = 71,
    ScreenOrientationEventTargetInterfaceType = 72,
    SharedWorkerEventTargetInterfaceType = 73,
    SharedWorkerGlobalScopeEventTargetInterfaceType = 74,
    SpeechRecognitionEventTargetInterfaceType = 75,
    VisualViewportEventTargetInterfaceType = 76,
    WakeLockSentinelEventTargetInterfaceType = 77,
    WebAnimationEventTargetInterfaceType = 78,
    WebSocketEventTargetInterfaceType = 79,
    WorkerEventTargetInterfaceType = 80,
    WorkletGlobalScopeEventTargetInterfaceType = 81,
    XMLHttpRequestEventTargetInterfaceType = 82,
    XMLHttpRequestUploadEventTargetInterfaceType = 83,
};

} // namespace WebCore
