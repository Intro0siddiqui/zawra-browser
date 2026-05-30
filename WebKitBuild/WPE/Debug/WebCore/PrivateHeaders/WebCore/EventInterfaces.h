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

enum EventInterface {
#if ENABLE(APPLE_PAY)
    ApplePayCancelEventInterfaceType = 1,
    ApplePayPaymentAuthorizedEventInterfaceType = 2,
    ApplePayPaymentMethodSelectedEventInterfaceType = 3,
    ApplePayShippingContactSelectedEventInterfaceType = 4,
    ApplePayShippingMethodSelectedEventInterfaceType = 5,
    ApplePayValidateMerchantEventInterfaceType = 6,
#endif
#if ENABLE(APPLE_PAY_COUPON_CODE)
    ApplePayCouponCodeChangedEventInterfaceType = 7,
#endif
#if ENABLE(DEVICE_ORIENTATION)
    DeviceMotionEventInterfaceType = 8,
    DeviceOrientationEventInterfaceType = 9,
#endif
#if ENABLE(ENCRYPTED_MEDIA)
    MediaEncryptedEventInterfaceType = 10,
    MediaKeyMessageEventInterfaceType = 11,
#endif
#if ENABLE(GAMEPAD)
    GamepadEventInterfaceType = 12,
#endif
#if ENABLE(IOS_GESTURE_EVENTS) || ENABLE(MAC_GESTURE_EVENTS)
    GestureEventInterfaceType = 13,
#endif
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    WebKitMediaKeyMessageEventInterfaceType = 14,
    WebKitMediaKeyNeededEventInterfaceType = 15,
#endif
#if ENABLE(MANAGED_MEDIA_SOURCE)
    BufferedChangeEventInterfaceType = 16,
#endif
#if ENABLE(MEDIA_RECORDER)
    BlobEventInterfaceType = 17,
    MediaRecorderErrorEventInterfaceType = 18,
#endif
#if ENABLE(MEDIA_STREAM)
    MediaStreamTrackEventInterfaceType = 19,
    OverconstrainedErrorEventInterfaceType = 20,
#endif
#if ENABLE(NOTIFICATION_EVENT)
    NotificationEventInterfaceType = 21,
#endif
#if ENABLE(ORIENTATION_EVENTS)
#endif
#if ENABLE(PAYMENT_REQUEST)
    MerchantValidationEventInterfaceType = 22,
    PaymentMethodChangeEventInterfaceType = 23,
    PaymentRequestUpdateEventInterfaceType = 24,
#endif
#if ENABLE(PICTURE_IN_PICTURE_API)
    PictureInPictureEventInterfaceType = 25,
#endif
#if ENABLE(SERVICE_WORKER)
    BackgroundFetchEventInterfaceType = 26,
    BackgroundFetchUpdateUIEventInterfaceType = 27,
    ExtendableEventInterfaceType = 28,
    ExtendableMessageEventInterfaceType = 29,
    FetchEventInterfaceType = 30,
    PushEventInterfaceType = 31,
    PushSubscriptionChangeEventInterfaceType = 32,
#endif
#if ENABLE(SPEECH_SYNTHESIS)
    SpeechSynthesisErrorEventInterfaceType = 33,
    SpeechSynthesisEventInterfaceType = 34,
#endif
#if ENABLE(TOUCH_EVENTS)
    TouchEventInterfaceType = 35,
#endif
#if ENABLE(VIDEO)
    TrackEventInterfaceType = 36,
#endif
#if ENABLE(WEBGL)
    WebGLContextEventInterfaceType = 37,
#endif
#if ENABLE(WEBXR)
    XRInputSourceEventInterfaceType = 38,
    XRInputSourcesChangeEventInterfaceType = 39,
    XRReferenceSpaceEventInterfaceType = 40,
    XRSessionEventInterfaceType = 41,
#endif
#if ENABLE(WEB_AUDIO)
    AudioProcessingEventInterfaceType = 42,
    OfflineAudioCompletionEventInterfaceType = 43,
#endif
#if ENABLE(WEB_RTC)
    RTCDTMFToneChangeEventInterfaceType = 44,
    RTCDataChannelEventInterfaceType = 45,
    RTCErrorEventInterfaceType = 46,
    RTCPeerConnectionIceErrorEventInterfaceType = 47,
    RTCPeerConnectionIceEventInterfaceType = 48,
    RTCRtpSFrameTransformErrorEventInterfaceType = 49,
    RTCTrackEventInterfaceType = 50,
    RTCTransformEventInterfaceType = 51,
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET_AVAILABILITY_API)
    WebKitPlaybackTargetAvailabilityEventInterfaceType = 52,
#endif
    AnimationPlaybackEventInterfaceType = 53,
    BeforeUnloadEventInterfaceType = 54,
    CSSAnimationEventInterfaceType = 55,
    CSSTransitionEventInterfaceType = 56,
    ClipboardEventInterfaceType = 57,
    CloseEventInterfaceType = 58,
    CompositionEventInterfaceType = 59,
    CustomEventInterfaceType = 60,
    DragEventInterfaceType = 61,
    ErrorEventInterfaceType = 62,
    EventInterfaceType = 63,
    FocusEventInterfaceType = 64,
    FormDataEventInterfaceType = 65,
    HashChangeEventInterfaceType = 66,
    IDBVersionChangeEventInterfaceType = 67,
    InputEventInterfaceType = 68,
    KeyboardEventInterfaceType = 69,
    MediaQueryListEventInterfaceType = 70,
    MessageEventInterfaceType = 71,
    MouseEventInterfaceType = 72,
    MutationEventInterfaceType = 73,
    OverflowEventInterfaceType = 74,
    PageTransitionEventInterfaceType = 75,
    PointerEventInterfaceType = 76,
    PopStateEventInterfaceType = 77,
    ProgressEventInterfaceType = 78,
    PromiseRejectionEventInterfaceType = 79,
    SecurityPolicyViolationEventInterfaceType = 80,
    SpeechRecognitionErrorEventInterfaceType = 81,
    SpeechRecognitionEventInterfaceType = 82,
    StorageEventInterfaceType = 83,
    SubmitEventInterfaceType = 84,
    TextEventInterfaceType = 85,
    ToggleEventInterfaceType = 86,
    UIEventInterfaceType = 87,
    WheelEventInterfaceType = 88,
    XMLHttpRequestProgressEventInterfaceType = 89,
};

} // namespace WebCore
