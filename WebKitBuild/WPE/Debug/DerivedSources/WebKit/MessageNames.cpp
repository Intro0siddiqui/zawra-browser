/*
 * Copyright (C) 2021-2023 Apple Inc. All rights reserved.
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
#include "MessageNames.h"

namespace IPC::Detail {

const MessageDescription messageDescriptions[static_cast<size_t>(MessageName::Count) + 1] = {
    { "AuthenticationManager_CompleteAuthenticationChallenge", ReceiverName::AuthenticationManager, false, false },
#if OS(LINUX)
    { "AuxiliaryProcess_DidReceiveMemoryPressureEvent", ReceiverName::AuxiliaryProcess, false, false },
#endif
    { "AuxiliaryProcess_MainThreadPing", ReceiverName::AuxiliaryProcess, false, false },
    { "AuxiliaryProcess_SetProcessSuppressionEnabled", ReceiverName::AuxiliaryProcess, false, false },
    { "AuxiliaryProcess_ShutDown", ReceiverName::AuxiliaryProcess, false, false },
    { "CacheStorageEngineConnection_Caches", ReceiverName::CacheStorageEngineConnection, false, false },
    { "CacheStorageEngineConnection_ClearMemoryRepresentation", ReceiverName::CacheStorageEngineConnection, false, false },
    { "CacheStorageEngineConnection_DeleteMatchingRecords", ReceiverName::CacheStorageEngineConnection, false, false },
    { "CacheStorageEngineConnection_Dereference", ReceiverName::CacheStorageEngineConnection, false, false },
    { "CacheStorageEngineConnection_EngineRepresentation", ReceiverName::CacheStorageEngineConnection, false, false },
    { "CacheStorageEngineConnection_Open", ReceiverName::CacheStorageEngineConnection, false, false },
    { "CacheStorageEngineConnection_PutRecords", ReceiverName::CacheStorageEngineConnection, false, false },
    { "CacheStorageEngineConnection_Reference", ReceiverName::CacheStorageEngineConnection, false, false },
    { "CacheStorageEngineConnection_Remove", ReceiverName::CacheStorageEngineConnection, false, false },
    { "CacheStorageEngineConnection_RetrieveRecords", ReceiverName::CacheStorageEngineConnection, false, false },
    { "DownloadProxy_DecideDestinationWithSuggestedFilename", ReceiverName::DownloadProxy, false, false },
    { "DownloadProxy_DidCreateDestination", ReceiverName::DownloadProxy, false, false },
    { "DownloadProxy_DidFail", ReceiverName::DownloadProxy, false, false },
    { "DownloadProxy_DidFinish", ReceiverName::DownloadProxy, false, false },
    { "DownloadProxy_DidReceiveAuthenticationChallenge", ReceiverName::DownloadProxy, false, false },
    { "DownloadProxy_DidReceiveData", ReceiverName::DownloadProxy, false, false },
    { "DownloadProxy_DidStart", ReceiverName::DownloadProxy, false, false },
    { "DownloadProxy_WillSendRequest", ReceiverName::DownloadProxy, false, false },
    { "DrawingAreaProxy_DidFirstLayerFlush", ReceiverName::DrawingAreaProxy, false, false },
    { "DrawingAreaProxy_DispatchPresentationCallbacksAfterFlushingLayers", ReceiverName::DrawingAreaProxy, false, false },
    { "DrawingAreaProxy_EnterAcceleratedCompositingMode", ReceiverName::DrawingAreaProxy, false, false },
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
    { "DrawingAreaProxy_ExitAcceleratedCompositingMode", ReceiverName::DrawingAreaProxy, false, false },
    { "DrawingAreaProxy_Update", ReceiverName::DrawingAreaProxy, false, false },
#endif
    { "DrawingAreaProxy_UpdateAcceleratedCompositingMode", ReceiverName::DrawingAreaProxy, false, false },
#if PLATFORM(COCOA)
    { "DrawingArea_AcceleratedAnimationDidEnd", ReceiverName::DrawingArea, false, false },
    { "DrawingArea_AcceleratedAnimationDidStart", ReceiverName::DrawingArea, false, false },
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK)
    { "DrawingArea_AdjustTransientZoom", ReceiverName::DrawingArea, false, false },
    { "DrawingArea_CommitTransientZoom", ReceiverName::DrawingArea, false, false },
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
    { "DrawingArea_DidDiscardBackingStore", ReceiverName::DrawingArea, false, false },
#endif
#if PLATFORM(COCOA)
    { "DrawingArea_DispatchAfterEnsuringDrawing", ReceiverName::DrawingArea, false, false },
#endif
    { "DrawingArea_DisplayDidRefresh", ReceiverName::DrawingArea, false, false },
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
    { "DrawingArea_ForceUpdate", ReceiverName::DrawingArea, false, false },
#endif
#if PLATFORM(COCOA)
    { "DrawingArea_SetColorSpace", ReceiverName::DrawingArea, false, false },
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER) || PLATFORM(COCOA)
    { "DrawingArea_SetDeviceScaleFactor", ReceiverName::DrawingArea, false, false },
#endif
#if PLATFORM(COCOA)
    { "DrawingArea_SetViewExposedRect", ReceiverName::DrawingArea, false, false },
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
    { "DrawingArea_TargetRefreshRateDidChange", ReceiverName::DrawingArea, false, false },
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER) || PLATFORM(COCOA)
    { "DrawingArea_UpdateGeometry", ReceiverName::DrawingArea, false, false },
#endif
#if USE(GRAPHICS_LAYER_WC)
    { "DrawingArea_UpdateGeometryWC", ReceiverName::DrawingArea, false, false },
#endif
#if HAVE(CVDISPLAYLINK)
    { "EventDispatcher_DisplayDidRefresh", ReceiverName::EventDispatcher, false, false },
#endif
#if ENABLE(MAC_GESTURE_EVENTS)
    { "EventDispatcher_GestureEvent", ReceiverName::EventDispatcher, false, false },
#endif
    { "EventDispatcher_PageScreenDidChange", ReceiverName::EventDispatcher, false, false },
#if ENABLE(MOMENTUM_EVENT_DISPATCHER)
    { "EventDispatcher_SetScrollingAccelerationCurve", ReceiverName::EventDispatcher, false, false },
#endif
#if ENABLE(IOS_TOUCH_EVENTS)
    { "EventDispatcher_TouchEvent", ReceiverName::EventDispatcher, false, false },
    { "EventDispatcher_TouchEventWithoutCallback", ReceiverName::EventDispatcher, false, false },
#endif
    { "EventDispatcher_WheelEvent", ReceiverName::EventDispatcher, false, false },
    { "GPUConnectionToWebProcess_ClearNowPlayingInfo", ReceiverName::GPUConnectionToWebProcess, false, false },
    { "GPUConnectionToWebProcess_ConfigureLoggingChannel", ReceiverName::GPUConnectionToWebProcess, false, false },
    { "GPUConnectionToWebProcess_CreateAudioHardwareListener", ReceiverName::GPUConnectionToWebProcess, false, false },
#if ENABLE(WEBGL)
    { "GPUConnectionToWebProcess_CreateGraphicsContextGL", ReceiverName::GPUConnectionToWebProcess, true, false },
#endif
    { "GPUConnectionToWebProcess_CreateRemoteCommandListener", ReceiverName::GPUConnectionToWebProcess, false, false },
    { "GPUConnectionToWebProcess_CreateRemoteGPU", ReceiverName::GPUConnectionToWebProcess, true, false },
    { "GPUConnectionToWebProcess_CreateRenderingBackend", ReceiverName::GPUConnectionToWebProcess, true, false },
#if HAVE(VISIBILITY_PROPAGATION_VIEW)
    { "GPUConnectionToWebProcess_CreateVisibilityPropagationContextForPage", ReceiverName::GPUConnectionToWebProcess, false, false },
#endif
#if USE(GRAPHICS_LAYER_WC)
    { "GPUConnectionToWebProcess_CreateWCLayerTreeHost", ReceiverName::GPUConnectionToWebProcess, true, false },
#endif
#if HAVE(VISIBILITY_PROPAGATION_VIEW)
    { "GPUConnectionToWebProcess_DestroyVisibilityPropagationContextForPage", ReceiverName::GPUConnectionToWebProcess, false, false },
#endif
#if ENABLE(MEDIA_SOURCE)
    { "GPUConnectionToWebProcess_EnableMockMediaSource", ReceiverName::GPUConnectionToWebProcess, false, false },
#endif
#if ENABLE(VP9)
    { "GPUConnectionToWebProcess_EnableVP9Decoders", ReceiverName::GPUConnectionToWebProcess, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "GPUConnectionToWebProcess_EnsureMediaSessionHelper", ReceiverName::GPUConnectionToWebProcess, false, false },
#endif
    { "GPUConnectionToWebProcess_ReleaseAudioHardwareListener", ReceiverName::GPUConnectionToWebProcess, false, false },
#if ENABLE(WEBGL)
    { "GPUConnectionToWebProcess_ReleaseGraphicsContextGL", ReceiverName::GPUConnectionToWebProcess, true, false },
#endif
    { "GPUConnectionToWebProcess_ReleaseRemoteCommandListener", ReceiverName::GPUConnectionToWebProcess, false, false },
    { "GPUConnectionToWebProcess_ReleaseRemoteGPU", ReceiverName::GPUConnectionToWebProcess, true, false },
    { "GPUConnectionToWebProcess_ReleaseRenderingBackend", ReceiverName::GPUConnectionToWebProcess, true, false },
    { "GPUConnectionToWebProcess_ReleaseSerializedImageBuffer", ReceiverName::GPUConnectionToWebProcess, false, false },
#if USE(GRAPHICS_LAYER_WC)
    { "GPUConnectionToWebProcess_ReleaseWCLayerTreeHost", ReceiverName::GPUConnectionToWebProcess, true, false },
#endif
    { "GPUConnectionToWebProcess_SetMediaOverridesForTesting", ReceiverName::GPUConnectionToWebProcess, false, false },
    { "GPUConnectionToWebProcess_SetNowPlayingInfo", ReceiverName::GPUConnectionToWebProcess, false, false },
#if ENABLE(ROUTING_ARBITRATION)
    { "GPUProcessConnection_BeginRoutingArbitrationWithCategory", ReceiverName::GPUProcessConnection, false, false },
#endif
    { "GPUProcessConnection_DidInitialize", ReceiverName::GPUProcessConnection, false, false },
    { "GPUProcessConnection_DidReceiveRemoteCommand", ReceiverName::GPUProcessConnection, false, false },
#if ENABLE(ROUTING_ARBITRATION)
    { "GPUProcessConnection_EndRoutingArbitration", ReceiverName::GPUProcessConnection, false, false },
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(COCOA)
    { "GPUProcessConnection_ResetAudioMediaStreamTrackRendererInternalUnit", ReceiverName::GPUProcessConnection, false, false },
#endif
#if HAVE(VISIBILITY_PROPAGATION_VIEW)
    { "GPUProcessProxy_DidCreateContextForVisibilityPropagation", ReceiverName::GPUProcessProxy, false, false },
#endif
    { "GPUProcessProxy_ProcessIsReadyToExit", ReceiverName::GPUProcessProxy, false, false },
#if ENABLE(VP9)
    { "GPUProcessProxy_SetHasVP9ExtensionSupport", ReceiverName::GPUProcessProxy, false, false },
    { "GPUProcessProxy_SetHasVP9HardwareDecoder", ReceiverName::GPUProcessProxy, false, false },
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
    { "GPUProcessProxy_StatusBarWasTapped", ReceiverName::GPUProcessProxy, false, false },
#endif
    { "GPUProcessProxy_TerminateWebProcess", ReceiverName::GPUProcessProxy, false, false },
#if ENABLE(MEDIA_STREAM)
    { "GPUProcess_AddMockMediaDevice", ReceiverName::GPUProcess, false, false },
#endif
    { "GPUProcess_AddSession", ReceiverName::GPUProcess, false, false },
#if ENABLE(MEDIA_STREAM)
    { "GPUProcess_ClearMockMediaDevices", ReceiverName::GPUProcess, false, false },
#endif
#if HAVE(AUDIO_COMPONENT_SERVER_REGISTRATIONS)
    { "GPUProcess_ConsumeAudioComponentRegistrations", ReceiverName::GPUProcess, false, false },
#endif
    { "GPUProcess_CreateGPUConnectionToWebProcess", ReceiverName::GPUProcess, true, false },
#if PLATFORM(MAC)
    { "GPUProcess_DisplayConfigurationChanged", ReceiverName::GPUProcess, false, false },
#endif
#if HAVE(POWERLOG_TASK_MODE_QUERY)
    { "GPUProcess_EnablePowerLogging", ReceiverName::GPUProcess, false, false },
#endif
    { "GPUProcess_InitializeGPUProcess", ReceiverName::GPUProcess, false, false },
#if ENABLE(CFPREFS_DIRECT_MODE)
    { "GPUProcess_NotifyPreferencesChanged", ReceiverName::GPUProcess, false, false },
#endif
#if PLATFORM(MAC)
    { "GPUProcess_OpenDirectoryCacheInvalidated", ReceiverName::GPUProcess, false, false },
#endif
    { "GPUProcess_PrepareToSuspend", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_ProcessDidResume", ReceiverName::GPUProcess, false, false },
#if HAVE(SCREEN_CAPTURE_KIT)
    { "GPUProcess_PromptForGetDisplayMedia", ReceiverName::GPUProcess, false, false },
#endif
#if ENABLE(MEDIA_STREAM)
    { "GPUProcess_RemoveMockMediaDevice", ReceiverName::GPUProcess, false, false },
#endif
    { "GPUProcess_RemoveSession", ReceiverName::GPUProcess, false, false },
#if ENABLE(VIDEO)
    { "GPUProcess_RequestBitmapImageForCurrentTime", ReceiverName::GPUProcess, false, false },
#endif
#if ENABLE(MEDIA_STREAM)
    { "GPUProcess_ResetMockMediaDevices", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_SetMockCaptureDevicesEnabled", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_SetMockCaptureDevicesInterrupted", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_SetMockMediaDeviceIsEphemeral", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_SetOrientationForMediaCapture", ReceiverName::GPUProcess, false, false },
#endif
#if PLATFORM(MAC)
    { "GPUProcess_SetScreenProperties", ReceiverName::GPUProcess, false, false },
#endif
#if HAVE(SC_CONTENT_SHARING_PICKER)
    { "GPUProcess_SetUseSCContentSharingPicker", ReceiverName::GPUProcess, false, false },
#endif
#if ENABLE(MEDIA_STREAM)
    { "GPUProcess_TriggerMockMicrophoneConfigurationChange", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_UpdateCaptureAccess", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_UpdateCaptureOrigin", ReceiverName::GPUProcess, false, false },
#endif
    { "GPUProcess_UpdateDOMRenderingEnabled", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_UpdateGPUProcessPreferences", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_UpdateSandboxAccess", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_UpdateWebGPUEnabled", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_UserPreferredLanguagesChanged", ReceiverName::GPUProcess, false, false },
    { "GPUProcess_WebProcessConnectionCountForTesting", ReceiverName::GPUProcess, false, false },
    { "IPCConnectionTester_AsyncMessage", ReceiverName::IPCConnectionTester, false, false },
    { "IPCStreamTesterProxy_WasCreated", ReceiverName::IPCStreamTesterProxy, false, false },
    { "IPCStreamTester_AsyncMessage", ReceiverName::IPCStreamTester, true, false },
    { "IPCTesterReceiver_AsyncMessage", ReceiverName::IPCTesterReceiver, false, false },
    { "IPCTester_CreateConnectionTester", ReceiverName::IPCTester, false, false },
    { "IPCTester_CreateConnectionTesterAndSendAsyncMessages", ReceiverName::IPCTester, false, false },
    { "IPCTester_CreateStreamTester", ReceiverName::IPCTester, false, false },
    { "IPCTester_SendAsyncMessageToReceiver", ReceiverName::IPCTester, false, false },
    { "IPCTester_SendSameSemaphoreBack", ReceiverName::IPCTester, false, false },
    { "IPCTester_SendSemaphoreBackAndSignalProtocol", ReceiverName::IPCTester, false, false },
    { "IPCTester_StartMessageTesting", ReceiverName::IPCTester, false, false },
    { "LibWebRTCCodecsProxy_CreateDecoder", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_CreateEncoder", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_DecodeFrame", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_EncodeFrame", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_FlushDecoder", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_FlushEncoder", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_InitializeEncoder", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_ReleaseDecoder", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_ReleaseEncoder", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_SetDecoderFormatDescription", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_SetEncodeRates", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_SetFrameSize", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_SetRTCLoggingLevel", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_SetSharedVideoFrameMemory", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecsProxy_SetSharedVideoFrameSemaphore", ReceiverName::LibWebRTCCodecsProxy, false, false },
    { "LibWebRTCCodecs_CompletedDecoding", ReceiverName::LibWebRTCCodecs, false, false },
    { "LibWebRTCCodecs_CompletedDecodingCV", ReceiverName::LibWebRTCCodecs, false, false },
    { "LibWebRTCCodecs_CompletedEncoding", ReceiverName::LibWebRTCCodecs, false, false },
    { "LibWebRTCCodecs_FailedDecoding", ReceiverName::LibWebRTCCodecs, false, false },
    { "LibWebRTCCodecs_FlushDecoderCompleted", ReceiverName::LibWebRTCCodecs, false, false },
    { "LibWebRTCCodecs_FlushEncoderCompleted", ReceiverName::LibWebRTCCodecs, false, false },
    { "LibWebRTCCodecs_SetEncodingConfiguration", ReceiverName::LibWebRTCCodecs, false, false },
    { "LibWebRTCNetwork_SignalAddressReady", ReceiverName::LibWebRTCNetwork, false, false },
    { "LibWebRTCNetwork_SignalClose", ReceiverName::LibWebRTCNetwork, false, false },
    { "LibWebRTCNetwork_SignalConnect", ReceiverName::LibWebRTCNetwork, false, false },
    { "LibWebRTCNetwork_SignalReadPacket", ReceiverName::LibWebRTCNetwork, false, false },
    { "LibWebRTCNetwork_SignalSentPacket", ReceiverName::LibWebRTCNetwork, false, false },
    { "LibWebRTCNetwork_SignalUsedInterface", ReceiverName::LibWebRTCNetwork, false, false },
    { "MediaPlayerPrivateRemote_ActiveSourceBuffersChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_AddDataCue", ReceiverName::MediaPlayerPrivateRemote, false, false },
#if ENABLE(DATACUE_VALUE)
    { "MediaPlayerPrivateRemote_AddDataCueWithType", ReceiverName::MediaPlayerPrivateRemote, false, false },
#endif
    { "MediaPlayerPrivateRemote_AddGenericCue", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_AddRemoteAudioTrack", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_AddRemoteTextTrack", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_AddRemoteVideoTrack", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_CharacteristicChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    { "MediaPlayerPrivateRemote_CurrentPlaybackTargetIsWirelessChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
#endif
    { "MediaPlayerPrivateRemote_CurrentTimeChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_DurationChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_EngineFailedToLoad", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_FirstVideoFrameAvailable", ReceiverName::MediaPlayerPrivateRemote, false, false },
#if PLATFORM(IOS_FAMILY)
    { "MediaPlayerPrivateRemote_GetRawCookies", ReceiverName::MediaPlayerPrivateRemote, false, false },
#endif
#if ENABLE(ENCRYPTED_MEDIA)
    { "MediaPlayerPrivateRemote_InitializationDataEncountered", ReceiverName::MediaPlayerPrivateRemote, false, false },
#endif
#if PLATFORM(COCOA)
    { "MediaPlayerPrivateRemote_LayerHostingContextIdChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
#endif
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    { "MediaPlayerPrivateRemote_MediaPlayerKeyNeeded", ReceiverName::MediaPlayerPrivateRemote, false, false },
#endif
    { "MediaPlayerPrivateRemote_MuteChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_NetworkStateChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_ParseWebVTTCueData", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_ParseWebVTTCueDataStruct", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_ParseWebVTTFileHeader", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_PlaybackStateChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
#if PLATFORM(COCOA)
    { "MediaPlayerPrivateRemote_PushVideoFrameMetadata", ReceiverName::MediaPlayerPrivateRemote, false, false },
#endif
    { "MediaPlayerPrivateRemote_RateChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_ReadyStateChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_RemoteAudioTrackConfigurationChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_RemoteTextTrackConfigurationChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_RemoteVideoTrackConfigurationChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
#if ENABLE(DATACUE_VALUE)
    { "MediaPlayerPrivateRemote_RemoveDataCue", ReceiverName::MediaPlayerPrivateRemote, false, false },
#endif
    { "MediaPlayerPrivateRemote_RemoveGenericCue", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_RemoveRemoteAudioTrack", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_RemoveRemoteTextTrack", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_RemoveRemoteVideoTrack", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_RemoveResource", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_RenderingModeChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_RequestResource", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_ResourceNotSupported", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_SendH2Ping", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_SizeChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_TimeChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_UpdateCachedState", ReceiverName::MediaPlayerPrivateRemote, false, false },
#if ENABLE(DATACUE_VALUE)
    { "MediaPlayerPrivateRemote_UpdateDataCue", ReceiverName::MediaPlayerPrivateRemote, false, false },
#endif
    { "MediaPlayerPrivateRemote_UpdateGenericCue", ReceiverName::MediaPlayerPrivateRemote, false, false },
    { "MediaPlayerPrivateRemote_VolumeChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
#if ENABLE(ENCRYPTED_MEDIA)
    { "MediaPlayerPrivateRemote_WaitingForKeyChanged", ReceiverName::MediaPlayerPrivateRemote, false, false },
#endif
    { "MediaSourcePrivateRemote_MediaSourcePrivateShuttingDown", ReceiverName::MediaSourcePrivateRemote, false, false },
    { "MediaSourcePrivateRemote_SeekToTime", ReceiverName::MediaSourcePrivateRemote, false, false },
    { "NetworkBroadcastChannelRegistry_PostMessage", ReceiverName::NetworkBroadcastChannelRegistry, false, false },
    { "NetworkBroadcastChannelRegistry_RegisterChannel", ReceiverName::NetworkBroadcastChannelRegistry, false, false },
    { "NetworkBroadcastChannelRegistry_UnregisterChannel", ReceiverName::NetworkBroadcastChannelRegistry, false, false },
    { "NetworkConnectionToWebProcess_AddAllowedFirstPartyForCookies", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_AddOriginAccessAllowListEntry", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_BrowsingContextRemoved", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_ClearPageSpecificData", ReceiverName::NetworkConnectionToWebProcess, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkConnectionToWebProcess_CloseSWContextConnection", ReceiverName::NetworkConnectionToWebProcess, false, false },
#endif
    { "NetworkConnectionToWebProcess_CloseSharedWorkerContextConnection", ReceiverName::NetworkConnectionToWebProcess, false, false },
#if ENABLE(WEB_RTC)
    { "NetworkConnectionToWebProcess_ConnectToRTCDataChannelRemoteSource", ReceiverName::NetworkConnectionToWebProcess, false, false },
#endif
    { "NetworkConnectionToWebProcess_ConvertMainResourceLoadToDownload", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_CookiesForDOMAsync", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_CreateNewMessagePortChannel", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_CreateRTCProvider", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_CreateSocketChannel", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_DeleteCookie", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_DidDeliverMessagePortMessages", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_EntangleLocalPortInThisProcessToRemote", ReceiverName::NetworkConnectionToWebProcess, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkConnectionToWebProcess_EstablishSWContextConnection", ReceiverName::NetworkConnectionToWebProcess, false, false },
#endif
    { "NetworkConnectionToWebProcess_EstablishSharedWorkerContextConnection", ReceiverName::NetworkConnectionToWebProcess, false, false },
#if PLATFORM(MAC)
    { "NetworkConnectionToWebProcess_GetProcessDisplayName", ReceiverName::NetworkConnectionToWebProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkConnectionToWebProcess_HasStorageAccess", ReceiverName::NetworkConnectionToWebProcess, false, false },
#endif
#if ENABLE(CONTENT_FILTERING)
    { "NetworkConnectionToWebProcess_InstallMockContentFilter", ReceiverName::NetworkConnectionToWebProcess, false, false },
#endif
    { "NetworkConnectionToWebProcess_IsResourceLoadFinished", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_LoadPing", ReceiverName::NetworkConnectionToWebProcess, false, false },
#if ENABLE(LOGD_BLOCKING_IN_WEBCONTENT)
    { "NetworkConnectionToWebProcess_LogOnBehalfOfWebContent", ReceiverName::NetworkConnectionToWebProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkConnectionToWebProcess_LogUserInteraction", ReceiverName::NetworkConnectionToWebProcess, false, false },
#endif
    { "NetworkConnectionToWebProcess_MessagePortClosed", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_MessagePortDisentangled", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_PageLoadCompleted", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_PostMessageToRemote", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_PreconnectTo", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_PrefetchDNS", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_PrioritizeResourceLoads", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_RegisterBlobURL", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_RegisterBlobURLHandle", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_RegisterInternalBlobURL", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_RegisterInternalBlobURLForSlice", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_RegisterInternalBlobURLOptionallyFileBacked", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_RegisterInternalFileBlobURL", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_RegisterURLSchemesAsCORSEnabled", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_RemoveLoadIdentifier", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_RemoveOriginAccessAllowListEntry", ReceiverName::NetworkConnectionToWebProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkConnectionToWebProcess_RemoveStorageAccessForFrame", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_RequestStorageAccess", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_RequestStorageAccessUnderOpener", ReceiverName::NetworkConnectionToWebProcess, false, false },
#endif
    { "NetworkConnectionToWebProcess_ResetOriginAccessAllowLists", ReceiverName::NetworkConnectionToWebProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkConnectionToWebProcess_ResourceLoadStatisticsUpdated", ReceiverName::NetworkConnectionToWebProcess, false, false },
#endif
    { "NetworkConnectionToWebProcess_ScheduleResourceLoad", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_SendH2Ping", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_SetCORSDisablingPatterns", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_SetCaptureExtraNetworkLoadMetricsEnabled", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_SetCookieFromDOMAsync", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_SetCookiesFromDOM", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_SetRawCookie", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_SetResourceLoadSchedulingMode", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_StartDownload", ReceiverName::NetworkConnectionToWebProcess, false, false },
#if HAVE(COOKIE_CHANGE_LISTENER_API)
    { "NetworkConnectionToWebProcess_SubscribeToCookieChangeNotifications", ReceiverName::NetworkConnectionToWebProcess, true, false },
#endif
    { "NetworkConnectionToWebProcess_TakeAllMessagesForPort", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_UnregisterBlobURL", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_UnregisterBlobURLHandle", ReceiverName::NetworkConnectionToWebProcess, false, false },
#if HAVE(COOKIE_CHANGE_LISTENER_API)
    { "NetworkConnectionToWebProcess_UnsubscribeFromCookieChangeNotifications", ReceiverName::NetworkConnectionToWebProcess, true, false },
#endif
#if PLATFORM(MAC)
    { "NetworkConnectionToWebProcess_UpdateActivePages", ReceiverName::NetworkConnectionToWebProcess, false, false },
#endif
    { "NetworkConnectionToWebProcess_UpdateQuotaBasedOnSpaceUsageForTesting", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_UseRedirectionForCurrentNavigation", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkConnectionToWebProcess_WriteBlobsToTemporaryFilesForIndexedDB", ReceiverName::NetworkConnectionToWebProcess, false, false },
    { "NetworkContentRuleListManager_AddContentRuleLists", ReceiverName::NetworkContentRuleListManager, false, false },
    { "NetworkContentRuleListManager_Remove", ReceiverName::NetworkContentRuleListManager, false, false },
    { "NetworkContentRuleListManager_RemoveAllContentRuleLists", ReceiverName::NetworkContentRuleListManager, false, false },
    { "NetworkContentRuleListManager_RemoveContentRuleList", ReceiverName::NetworkContentRuleListManager, false, false },
    { "NetworkMDNSRegister_RegisterMDNSName", ReceiverName::NetworkMDNSRegister, false, false },
    { "NetworkMDNSRegister_UnregisterMDNSNames", ReceiverName::NetworkMDNSRegister, false, false },
    { "NetworkProcessConnection_AddAllowedFirstPartyForCookies", ReceiverName::NetworkProcessConnection, false, false },
#if HAVE(COOKIE_CHANGE_LISTENER_API)
    { "NetworkProcessConnection_AllCookiesDeleted", ReceiverName::NetworkProcessConnection, false, false },
#endif
    { "NetworkProcessConnection_BroadcastConsoleMessage", ReceiverName::NetworkProcessConnection, false, false },
#if ENABLE(WEB_RTC)
    { "NetworkProcessConnection_ConnectToRTCDataChannelRemoteSource", ReceiverName::NetworkProcessConnection, false, false },
#endif
    { "NetworkProcessConnection_CookieAcceptPolicyChanged", ReceiverName::NetworkProcessConnection, false, false },
#if HAVE(COOKIE_CHANGE_LISTENER_API)
    { "NetworkProcessConnection_CookiesAdded", ReceiverName::NetworkProcessConnection, false, false },
    { "NetworkProcessConnection_CookiesDeleted", ReceiverName::NetworkProcessConnection, false, false },
#endif
#if ENABLE(SHAREABLE_RESOURCE)
    { "NetworkProcessConnection_DidCacheResource", ReceiverName::NetworkProcessConnection, false, false },
#endif
    { "NetworkProcessConnection_DidFinishPingLoad", ReceiverName::NetworkProcessConnection, false, false },
    { "NetworkProcessConnection_DidFinishPreconnection", ReceiverName::NetworkProcessConnection, false, false },
    { "NetworkProcessConnection_MessagesAvailableForPort", ReceiverName::NetworkProcessConnection, false, false },
    { "NetworkProcessConnection_SetOnLineState", ReceiverName::NetworkProcessConnection, false, false },
#if ENABLE(CONTENT_EXTENSIONS)
    { "NetworkProcessProxy_ContentExtensionRules", ReceiverName::NetworkProcessProxy, false, false },
#endif
    { "NetworkProcessProxy_CookiesDidChange", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_DataTaskDidCompleteWithError", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_DataTaskDidReceiveData", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_DataTaskDidReceiveResponse", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_DataTaskReceivedChallenge", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_DataTaskWillPerformHTTPRedirection", ReceiverName::NetworkProcessProxy, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcessProxy_DeleteWebsiteDataInUIProcessForRegistrableDomains", ReceiverName::NetworkProcessProxy, false, false },
#endif
    { "NetworkProcessProxy_DeleteWebsiteDataInWebProcessesForOrigin", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_DidBlockLoadToKnownTracker", ReceiverName::NetworkProcessProxy, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcessProxy_DidCommitCrossSiteLoadWithDataTransferFromPrevalentResource", ReceiverName::NetworkProcessProxy, false, false },
#endif
#if USE(SOUP)
    { "NetworkProcessProxy_DidExceedMemoryLimit", ReceiverName::NetworkProcessProxy, false, false },
#endif
    { "NetworkProcessProxy_DidNegotiateModernTLS", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_DidReceiveAuthenticationChallenge", ReceiverName::NetworkProcessProxy, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcessProxy_EndServiceWorkerBackgroundProcessing", ReceiverName::NetworkProcessProxy, false, false },
#endif
    { "NetworkProcessProxy_EstablishRemoteWorkerContextConnectionToNetworkProcess", ReceiverName::NetworkProcessProxy, false, false },
#if ENABLE(APP_BOUND_DOMAINS)
    { "NetworkProcessProxy_GetAppBoundDomains", ReceiverName::NetworkProcessProxy, false, false },
#endif
#if ENABLE(APPLE_PAY_REMOTE_UI_USES_SCENE)
    { "NetworkProcessProxy_GetWindowSceneIdentifierForPaymentPresentation", ReceiverName::NetworkProcessProxy, false, false },
#endif
    { "NetworkProcessProxy_IncreaseQuota", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_LogDiagnosticMessage", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_LogDiagnosticMessageWithResult", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_LogDiagnosticMessageWithValue", ReceiverName::NetworkProcessProxy, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcessProxy_LogTestingEvent", ReceiverName::NetworkProcessProxy, false, false },
#endif
    { "NetworkProcessProxy_NavigateServiceWorkerClient", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_NegotiatedLegacyTLS", ReceiverName::NetworkProcessProxy, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcessProxy_NotifyBackgroundFetchChange", ReceiverName::NetworkProcessProxy, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcessProxy_NotifyResourceLoadStatisticsProcessed", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_NotifyWebsiteDataDeletionForRegistrableDomainsFinished", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_NotifyWebsiteDataScanForRegistrableDomainsFinished", ReceiverName::NetworkProcessProxy, false, false },
#endif
    { "NetworkProcessProxy_OpenWindowFromServiceWorker", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_RegisterRemoteWorkerClientProcess", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_ReloadExecutionContextsForOrigin", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_RemoteWorkerContextConnectionNoLongerNeeded", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_ReportConsoleMessage", ReceiverName::NetworkProcessProxy, false, false },
#if ENABLE(NETWORK_ISSUE_REPORTING)
    { "NetworkProcessProxy_ReportNetworkIssue", ReceiverName::NetworkProcessProxy, false, false },
#endif
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcessProxy_RequestBackgroundFetchPermission", ReceiverName::NetworkProcessProxy, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcessProxy_RequestStorageAccessConfirm", ReceiverName::NetworkProcessProxy, false, false },
#endif
    { "NetworkProcessProxy_RequestStorageSpace", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_ResourceLoadDidCompleteWithError", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_ResourceLoadDidPerformHTTPRedirection", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_ResourceLoadDidReceiveChallenge", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_ResourceLoadDidReceiveResponse", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_ResourceLoadDidSendRequest", ReceiverName::NetworkProcessProxy, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcessProxy_SetDomainsWithCrossPageStorageAccess", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_SetDomainsWithUserInteraction", ReceiverName::NetworkProcessProxy, false, false },
#endif
    { "NetworkProcessProxy_SetWebProcessHasUploads", ReceiverName::NetworkProcessProxy, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcessProxy_StartServiceWorkerBackgroundProcessing", ReceiverName::NetworkProcessProxy, false, false },
#endif
    { "NetworkProcessProxy_TerminateUnresponsiveServiceWorkerProcesses", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_TerminateWebProcess", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_TriggerBrowsingContextGroupSwitchForNavigation", ReceiverName::NetworkProcessProxy, false, false },
    { "NetworkProcessProxy_UnregisterRemoteWorkerClientProcess", ReceiverName::NetworkProcessProxy, false, false },
#if USE(RUNNINGBOARD)
    { "NetworkProcessProxy_WakeUpWebProcessForIPC", ReceiverName::NetworkProcessProxy, false, false },
#endif
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_AbortBackgroundFetch", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_AddAllowedFirstPartyForCookies", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_AddWebPageNetworkParameters", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_AddWebsiteDataStore", ReceiverName::NetworkProcess, true, false },
    { "NetworkProcess_AllowSpecificHTTPSCertificateForHost", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_AllowTLSCertificateChainForLocalPCMTesting", ReceiverName::NetworkProcess, false, false },
#if PLATFORM(COCOA)
    { "NetworkProcess_AppPrivacyReportTestingData", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_ApplicationDidEnterBackground", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_ApplicationWillEnterForeground", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_CancelDataTask", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_CancelDownload", ReceiverName::NetworkProcess, false, false },
#if ENABLE(APP_BOUND_DOMAINS)
    { "NetworkProcess_ClearAppBoundSession", ReceiverName::NetworkProcess, false, false },
#endif
#if PLATFORM(COCOA)
    { "NetworkProcess_ClearAppPrivacyReportTestingData", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_ClearBundleIdentifier", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_ClearPrevalentResource", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_ClearPrivateClickMeasurement", ReceiverName::NetworkProcess, false, false },
#if HAVE(NW_PROXY_CONFIG)
    { "NetworkProcess_ClearProxyConfigData", ReceiverName::NetworkProcess, false, false },
#endif
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
    { "NetworkProcess_ClearServiceWorkerEntitlementOverride", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_ClearUserInteraction", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_ClickBackgroundFetch", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_CloneSessionStorageForWebPage", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_CloseITPDatabase", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_ClosePCMDatabase", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_CountNonDefaultSessionSets", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_CreateNetworkConnectionToWebProcess", ReceiverName::NetworkProcess, true, false },
    { "NetworkProcess_DataTaskWithRequest", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_DeleteCookiesForTesting", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_DeletePushAndNotificationRegistration", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_DeleteWebsiteData", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_DeleteWebsiteDataForOrigins", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_DestroySession", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_DidCommitCrossSiteLoadWithDataTransfer", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_DidIncreaseQuota", ReceiverName::NetworkProcess, false, false },
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
    { "NetworkProcess_DisableServiceWorkerEntitlement", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_DomainIDExistsInDatabase", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_DownloadRequest", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_DumpPrivateClickMeasurement", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_DumpResourceLoadStatistics", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_FetchWebsiteData", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_FlushCookies", ReceiverName::NetworkProcess, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_GetAllBackgroundFetchIdentifiers", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_GetAllStorageAccessEntries", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_GetBackgroundFetchState", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_GetOriginsWithPushAndNotificationPermissions", ReceiverName::NetworkProcess, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_GetPendingPushMessages", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_GetResourceLoadStatisticsDataSummary", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_HadUserInteraction", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(APP_BOUND_DOMAINS)
    { "NetworkProcess_HasAppBoundSession", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_HasIsolatedSession", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_HasLocalStorage", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_HasPushSubscriptionForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_InitializeNetworkProcess", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_InsertExpiredStatisticForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_IsGrandfathered", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_IsPrevalentResource", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_IsRegisteredAsRedirectingTo", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_IsRegisteredAsSubFrameUnder", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_IsRegisteredAsSubresourceUnder", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_IsRelationshipOnlyInDatabaseOnce", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_IsResourceLoadStatisticsEphemeral", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_IsVeryPrevalentResource", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_LogFrameNavigation", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_LogUserInteraction", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_MarkAttributedPrivateClickMeasurementsAsExpiredForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_MarkPrivateClickMeasurementsAsExpiredForTesting", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_MergeStatisticForTesting", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_NotifyMediaStreamingActivity", ReceiverName::NetworkProcess, false, false },
#if ENABLE(CFPREFS_DIRECT_MODE)
    { "NetworkProcess_NotifyPreferencesChanged", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_PauseBackgroundFetch", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_PreconnectTo", ReceiverName::NetworkProcess, false, false },
#if USE(SOUP)
    { "NetworkProcess_PrefetchDNS", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_PrepareToSuspend", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_ProcessDidResume", ReceiverName::NetworkProcess, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_ProcessNotificationEvent", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_ProcessPushMessage", ReceiverName::NetworkProcess, false, false },
#endif
#if PLATFORM(COCOA)
    { "NetworkProcess_PublishDownloadProgress", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_RegisterURLSchemeAsBypassingContentSecurityPolicy", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_RegisterURLSchemeAsLocal", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_RegisterURLSchemeAsNoAccess", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_RegisterURLSchemeAsSecure", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_RemoveWebPageNetworkParameters", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_RenameOriginInWebsiteData", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_ResetCacheMaxAgeCapForPrevalentResources", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_ResetCrossSiteLoadsWithLinkDecorationForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_ResetParametersToDefaultValues", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_ResetQuota", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_ResetStoragePersistedState", ReceiverName::NetworkProcess, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_ResumeBackgroundFetch", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_ResumeDownload", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_ScheduleClearInMemoryAndPersistent", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_ScheduleCookieBlockingUpdate", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_ScheduleStatisticsAndDataRecordsProcessing", ReceiverName::NetworkProcess, false, false },
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(APP_BOUND_DOMAINS))
    { "NetworkProcess_SetAppBoundDomainsForResourceLoadStatistics", ReceiverName::NetworkProcess, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "NetworkProcess_SetBackupExclusionPeriodForTesting", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_SetBlobRegistryTopOriginPartitioningEnabled", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetCacheMaxAgeCapForPrevalentResources", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_SetCacheModel", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetCrossSiteLoadWithLinkDecorationForTesting", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(INSPECTOR_NETWORK_THROTTLING)
    { "NetworkProcess_SetEmulatedConditions", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetFirstPartyHostCNAMEDomainForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetFirstPartyWebsiteDataRemovalModeForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetGrandfathered", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetGrandfatheringTime", ReceiverName::NetworkProcess, false, false },
#endif
#if USE(SOUP)
    { "NetworkProcess_SetIgnoreTLSErrors", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetIsRunningResourceLoadStatisticsTest", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetLastSeen", ReceiverName::NetworkProcess, false, false },
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(MANAGED_DOMAINS))
    { "NetworkProcess_SetManagedDomainsForResourceLoadStatistics", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetMaxStatisticsEntries", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetMinimumTimeBetweenDataRecordsRemoval", ReceiverName::NetworkProcess, false, false },
#endif
#if USE(SOUP) || USE(CURL)
    { "NetworkProcess_SetNetworkProxySettings", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetNotifyPagesWhenDataRecordsWereScanned", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_SetPCMFraudPreventionValuesForTesting", ReceiverName::NetworkProcess, false, false },
#if USE(SOUP)
    { "NetworkProcess_SetPersistentCredentialStorageEnabled", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetPrevalentResource", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetPrevalentResourceForDebugMode", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_SetPrivateClickMeasurementAppBundleIDForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetPrivateClickMeasurementAttributionReportURLsForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetPrivateClickMeasurementDebugMode", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetPrivateClickMeasurementEphemeralMeasurementForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetPrivateClickMeasurementOverrideTimerForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetPrivateClickMeasurementTokenPublicKeyURLForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetPrivateClickMeasurementTokenSignatureURLForTesting", ReceiverName::NetworkProcess, false, false },
#if HAVE(NW_PROXY_CONFIG)
    { "NetworkProcess_SetProxyConfigData", ReceiverName::NetworkProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetPruneEntriesDownTo", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_SetPushAndNotificationsEnabledForOrigin", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetResourceLoadStatisticsDebugMode", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetResourceLoadStatisticsLogTestingEvent", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetResourceLoadStatisticsTimeAdvanceForTesting", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_SetSessionIsControlledByAutomation", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetShouldClassifyResourcesBeforeDataRecordsRemoval", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetShouldDowngradeReferrerForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetShouldEnbleSameSiteStrictEnforcementForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetSubframeUnderTopFrameDomain", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetSubresourceUnderTopFrameDomain", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetSubresourceUniqueRedirectFrom", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetSubresourceUniqueRedirectTo", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetThirdPartyCNAMEDomainForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetThirdPartyCookieBlockingMode", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetTimeToLiveUserInteraction", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetToSameSiteStrictCookiesForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetTopFrameUniqueRedirectFrom", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetTopFrameUniqueRedirectTo", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetTrackingPreventionEnabled", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SetVeryPrevalentResource", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_SimulatePrivateClickMeasurementSessionRestart", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_StatisticsDatabaseHasAllTables", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_StorePrivateClickMeasurement", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_StoreServiceWorkerRegistrations", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_SyncLocalStorage", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_TerminateRemoteWorkerContextConnectionWhenPossible", ReceiverName::NetworkProcess, false, false },
    { "NetworkProcess_UpdateBundleIdentifier", ReceiverName::NetworkProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_UpdatePrevalentDomainsToBlockCookiesFor", ReceiverName::NetworkProcess, false, false },
#endif
#if USE(SOUP)
    { "NetworkProcess_UserPreferredLanguagesChanged", ReceiverName::NetworkProcess, false, false },
#endif
    { "NetworkProcess_WebsiteDataOriginDirectoryForTesting", ReceiverName::NetworkProcess, false, false },
    { "NetworkRTCMonitor_StartUpdatingIfNeeded", ReceiverName::NetworkRTCMonitor, false, false },
    { "NetworkRTCMonitor_StopUpdating", ReceiverName::NetworkRTCMonitor, false, false },
    { "NetworkRTCProvider_CloseSocket", ReceiverName::NetworkRTCProvider, false, false },
    { "NetworkRTCProvider_CreateClientTCPSocket", ReceiverName::NetworkRTCProvider, false, false },
    { "NetworkRTCProvider_CreateResolver", ReceiverName::NetworkRTCProvider, false, false },
    { "NetworkRTCProvider_CreateUDPSocket", ReceiverName::NetworkRTCProvider, false, false },
    { "NetworkRTCProvider_SendToSocket", ReceiverName::NetworkRTCProvider, false, false },
    { "NetworkRTCProvider_SetPlatformTCPSocketsEnabled", ReceiverName::NetworkRTCProvider, false, false },
    { "NetworkRTCProvider_SetPlatformUDPSocketsEnabled", ReceiverName::NetworkRTCProvider, false, false },
    { "NetworkRTCProvider_SetSocketOption", ReceiverName::NetworkRTCProvider, false, false },
    { "NetworkRTCProvider_StopResolver", ReceiverName::NetworkRTCProvider, false, false },
    { "NetworkRTCProvider_WrapNewTCPConnection", ReceiverName::NetworkRTCProvider, false, false },
    { "NetworkResourceLoader_ContinueDidReceiveResponse", ReceiverName::NetworkResourceLoader, false, false },
    { "NetworkSocketChannel_Close", ReceiverName::NetworkSocketChannel, false, false },
    { "NetworkSocketChannel_SendData", ReceiverName::NetworkSocketChannel, false, false },
    { "NetworkSocketChannel_SendString", ReceiverName::NetworkSocketChannel, false, false },
    { "NetworkStorageManager_AbortOpenAndUpgradeNeeded", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_AbortTransaction", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CacheStorageAllCaches", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CacheStorageClearMemoryRepresentation", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CacheStorageDereference", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CacheStorageOpenCache", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CacheStoragePutRecords", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CacheStorageReference", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CacheStorageRemoveCache", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CacheStorageRemoveRecords", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CacheStorageRepresentation", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CacheStorageRetrieveRecords", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CancelConnectToStorageArea", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_Clear", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_ClearObjectStore", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CloneSessionStorageNamespace", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CloseHandle", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CloseSyncAccessHandle", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CommitTransaction", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_ConnectToStorageArea", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CreateIndex", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CreateObjectStore", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_CreateSyncAccessHandle", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_DatabaseConnectionClosed", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_DatabaseConnectionPendingClose", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_DeleteDatabase", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_DeleteIndex", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_DeleteObjectStore", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_DeleteRecord", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_DidFinishHandlingVersionChangeTransaction", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_DidFireVersionChangeEvent", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_DisconnectFromStorageArea", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_EstablishTransaction", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_Estimate", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_FileSystemGetDirectory", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_GetAllDatabaseNamesAndVersions", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_GetAllRecords", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_GetCount", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_GetDirectoryHandle", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_GetFile", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_GetFileHandle", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_GetHandle", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_GetHandleNames", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_GetRecord", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_IsSameEntry", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_IterateCursor", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_Move", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_OpenCursor", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_OpenDBRequestCancelled", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_OpenDatabase", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_Persist", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_Persisted", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_PutOrAdd", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_RemoveEntry", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_RemoveItem", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_RenameIndex", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_RenameObjectStore", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_RequestNewCapacityForSyncAccessHandle", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_Resolve", ReceiverName::NetworkStorageManager, false, false },
    { "NetworkStorageManager_SetItem", ReceiverName::NetworkStorageManager, false, false },
    { "NotificationManagerMessageHandler_CancelNotification", ReceiverName::NotificationManagerMessageHandler, false, false },
    { "NotificationManagerMessageHandler_ClearNotifications", ReceiverName::NotificationManagerMessageHandler, false, false },
    { "NotificationManagerMessageHandler_DidDestroyNotification", ReceiverName::NotificationManagerMessageHandler, false, false },
    { "NotificationManagerMessageHandler_PageWasNotifiedOfNotificationPermission", ReceiverName::NotificationManagerMessageHandler, false, false },
    { "NotificationManagerMessageHandler_RequestSystemNotificationPermission", ReceiverName::NotificationManagerMessageHandler, false, false },
    { "NotificationManagerMessageHandler_ShowNotification", ReceiverName::NotificationManagerMessageHandler, false, false },
    { "PlatformXRSystemProxy_SessionDidEnd", ReceiverName::PlatformXRSystemProxy, false, false },
    { "PlatformXRSystemProxy_SessionDidUpdateVisibilityState", ReceiverName::PlatformXRSystemProxy, false, false },
    { "PlatformXRSystem_EnumerateImmersiveXRDevices", ReceiverName::PlatformXRSystem, false, false },
    { "PlatformXRSystem_InitializeTrackingAndRendering", ReceiverName::PlatformXRSystem, false, false },
    { "PlatformXRSystem_RequestFrame", ReceiverName::PlatformXRSystem, false, false },
    { "PlatformXRSystem_RequestPermissionOnSessionFeatures", ReceiverName::PlatformXRSystem, false, false },
    { "PlatformXRSystem_ShutDownTrackingAndRendering", ReceiverName::PlatformXRSystem, false, false },
    { "PlatformXRSystem_SubmitFrame", ReceiverName::PlatformXRSystem, false, false },
    { "RTCDataChannelRemoteManagerProxy_BufferedAmountIsDecreasing", ReceiverName::RTCDataChannelRemoteManagerProxy, false, false },
    { "RTCDataChannelRemoteManagerProxy_ChangeReadyState", ReceiverName::RTCDataChannelRemoteManagerProxy, false, false },
    { "RTCDataChannelRemoteManagerProxy_Close", ReceiverName::RTCDataChannelRemoteManagerProxy, false, false },
    { "RTCDataChannelRemoteManagerProxy_DetectError", ReceiverName::RTCDataChannelRemoteManagerProxy, false, false },
    { "RTCDataChannelRemoteManagerProxy_ReceiveData", ReceiverName::RTCDataChannelRemoteManagerProxy, false, false },
    { "RTCDataChannelRemoteManagerProxy_SendData", ReceiverName::RTCDataChannelRemoteManagerProxy, false, false },
    { "RTCDataChannelRemoteManager_BufferedAmountIsDecreasing", ReceiverName::RTCDataChannelRemoteManager, false, false },
    { "RTCDataChannelRemoteManager_ChangeReadyState", ReceiverName::RTCDataChannelRemoteManager, false, false },
    { "RTCDataChannelRemoteManager_Close", ReceiverName::RTCDataChannelRemoteManager, false, false },
    { "RTCDataChannelRemoteManager_DetectError", ReceiverName::RTCDataChannelRemoteManager, false, false },
    { "RTCDataChannelRemoteManager_ReceiveData", ReceiverName::RTCDataChannelRemoteManager, false, false },
    { "RTCDataChannelRemoteManager_SendData", ReceiverName::RTCDataChannelRemoteManager, false, false },
    { "RemoteAdapter_Destruct", ReceiverName::RemoteAdapter, true, false },
#if PLATFORM(COCOA)
    { "RemoteAudioDestinationManager_AudioSamplesStorageChanged", ReceiverName::RemoteAudioDestinationManager, false, false },
#endif
    { "RemoteAudioDestinationManager_CreateAudioDestination", ReceiverName::RemoteAudioDestinationManager, false, false },
    { "RemoteAudioDestinationManager_DeleteAudioDestination", ReceiverName::RemoteAudioDestinationManager, false, false },
    { "RemoteAudioDestinationManager_StartAudioDestination", ReceiverName::RemoteAudioDestinationManager, false, false },
    { "RemoteAudioDestinationManager_StopAudioDestination", ReceiverName::RemoteAudioDestinationManager, false, false },
    { "RemoteAudioHardwareListener_AudioHardwareDidBecomeActive", ReceiverName::RemoteAudioHardwareListener, false, false },
    { "RemoteAudioHardwareListener_AudioHardwareDidBecomeInactive", ReceiverName::RemoteAudioHardwareListener, false, false },
    { "RemoteAudioHardwareListener_AudioOutputDeviceChanged", ReceiverName::RemoteAudioHardwareListener, false, false },
    { "RemoteAudioMediaStreamTrackRendererInternalUnitManager_CreateUnit", ReceiverName::RemoteAudioMediaStreamTrackRendererInternalUnitManager, false, false },
    { "RemoteAudioMediaStreamTrackRendererInternalUnitManager_DeleteUnit", ReceiverName::RemoteAudioMediaStreamTrackRendererInternalUnitManager, false, false },
    { "RemoteAudioMediaStreamTrackRendererInternalUnitManager_SetAudioOutputDevice", ReceiverName::RemoteAudioMediaStreamTrackRendererInternalUnitManager, false, false },
    { "RemoteAudioMediaStreamTrackRendererInternalUnitManager_StartUnit", ReceiverName::RemoteAudioMediaStreamTrackRendererInternalUnitManager, false, false },
    { "RemoteAudioMediaStreamTrackRendererInternalUnitManager_StopUnit", ReceiverName::RemoteAudioMediaStreamTrackRendererInternalUnitManager, false, false },
    { "RemoteAudioSessionProxy_BeginInterruptionRemote", ReceiverName::RemoteAudioSessionProxy, false, false },
    { "RemoteAudioSessionProxy_EndInterruptionRemote", ReceiverName::RemoteAudioSessionProxy, false, false },
    { "RemoteAudioSessionProxy_SetCategory", ReceiverName::RemoteAudioSessionProxy, false, false },
    { "RemoteAudioSessionProxy_SetIsPlayingToBluetoothOverride", ReceiverName::RemoteAudioSessionProxy, false, false },
    { "RemoteAudioSessionProxy_SetPreferredBufferSize", ReceiverName::RemoteAudioSessionProxy, false, false },
    { "RemoteAudioSessionProxy_TriggerBeginInterruptionForTesting", ReceiverName::RemoteAudioSessionProxy, false, false },
    { "RemoteAudioSessionProxy_TriggerEndInterruptionForTesting", ReceiverName::RemoteAudioSessionProxy, false, false },
    { "RemoteAudioSession_BeginInterruptionRemote", ReceiverName::RemoteAudioSession, false, false },
    { "RemoteAudioSession_ConfigurationChanged", ReceiverName::RemoteAudioSession, false, false },
    { "RemoteAudioSession_EndInterruptionRemote", ReceiverName::RemoteAudioSession, false, false },
    { "RemoteAudioSourceProviderManager_AudioSamplesAvailable", ReceiverName::RemoteAudioSourceProviderManager, false, false },
    { "RemoteAudioSourceProviderManager_AudioStorageChanged", ReceiverName::RemoteAudioSourceProviderManager, false, false },
    { "RemoteBarcodeDetector_Detect", ReceiverName::RemoteBarcodeDetector, true, false },
    { "RemoteBindGroupLayout_Destruct", ReceiverName::RemoteBindGroupLayout, true, false },
    { "RemoteBindGroupLayout_SetLabel", ReceiverName::RemoteBindGroupLayout, true, false },
    { "RemoteBindGroup_Destruct", ReceiverName::RemoteBindGroup, true, false },
    { "RemoteBindGroup_SetLabel", ReceiverName::RemoteBindGroup, true, false },
    { "RemoteBuffer_Destroy", ReceiverName::RemoteBuffer, true, false },
    { "RemoteBuffer_Destruct", ReceiverName::RemoteBuffer, true, false },
    { "RemoteBuffer_MapAsync", ReceiverName::RemoteBuffer, true, false },
    { "RemoteBuffer_SetLabel", ReceiverName::RemoteBuffer, true, false },
    { "RemoteBuffer_Unmap", ReceiverName::RemoteBuffer, true, false },
    { "RemoteCDMFactoryProxy_RemoveInstance", ReceiverName::RemoteCDMFactoryProxy, false, false },
    { "RemoteCDMFactoryProxy_RemoveSession", ReceiverName::RemoteCDMFactoryProxy, false, false },
    { "RemoteCDMInstanceProxy_InitializeWithConfiguration", ReceiverName::RemoteCDMInstanceProxy, false, false },
    { "RemoteCDMInstanceProxy_SetServerCertificate", ReceiverName::RemoteCDMInstanceProxy, false, false },
    { "RemoteCDMInstanceProxy_SetStorageDirectory", ReceiverName::RemoteCDMInstanceProxy, false, false },
    { "RemoteCDMInstanceSessionProxy_CloseSession", ReceiverName::RemoteCDMInstanceSessionProxy, false, false },
    { "RemoteCDMInstanceSessionProxy_LoadSession", ReceiverName::RemoteCDMInstanceSessionProxy, false, false },
    { "RemoteCDMInstanceSessionProxy_RemoveSessionData", ReceiverName::RemoteCDMInstanceSessionProxy, false, false },
    { "RemoteCDMInstanceSessionProxy_RequestLicense", ReceiverName::RemoteCDMInstanceSessionProxy, false, false },
    { "RemoteCDMInstanceSessionProxy_SetLogIdentifier", ReceiverName::RemoteCDMInstanceSessionProxy, false, false },
    { "RemoteCDMInstanceSessionProxy_StoreRecordOfKeyUsage", ReceiverName::RemoteCDMInstanceSessionProxy, false, false },
    { "RemoteCDMInstanceSessionProxy_UpdateLicense", ReceiverName::RemoteCDMInstanceSessionProxy, false, false },
    { "RemoteCDMInstanceSession_SendMessage", ReceiverName::RemoteCDMInstanceSession, false, false },
    { "RemoteCDMInstanceSession_SessionIdChanged", ReceiverName::RemoteCDMInstanceSession, false, false },
    { "RemoteCDMInstanceSession_UpdateKeyStatuses", ReceiverName::RemoteCDMInstanceSession, false, false },
    { "RemoteCDMInstance_UnrequestedInitializationDataReceived", ReceiverName::RemoteCDMInstance, false, false },
    { "RemoteCDMProxy_GetSupportedConfiguration", ReceiverName::RemoteCDMProxy, false, false },
    { "RemoteCDMProxy_LoadAndInitialize", ReceiverName::RemoteCDMProxy, false, false },
    { "RemoteCDMProxy_SetLogIdentifier", ReceiverName::RemoteCDMProxy, false, false },
    { "RemoteCommandBuffer_Destruct", ReceiverName::RemoteCommandBuffer, true, false },
    { "RemoteCommandBuffer_SetLabel", ReceiverName::RemoteCommandBuffer, true, false },
    { "RemoteCommandEncoder_BeginComputePass", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_BeginRenderPass", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_ClearBuffer", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_CopyBufferToBuffer", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_CopyBufferToTexture", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_CopyTextureToBuffer", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_CopyTextureToTexture", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_Destruct", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_Finish", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_InsertDebugMarker", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_PopDebugGroup", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_PushDebugGroup", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_ResolveQuerySet", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_SetLabel", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCommandEncoder_WriteTimestamp", ReceiverName::RemoteCommandEncoder, true, false },
    { "RemoteCompositorIntegration_Destruct", ReceiverName::RemoteCompositorIntegration, true, false },
    { "RemoteComputePassEncoder_Destruct", ReceiverName::RemoteComputePassEncoder, true, false },
    { "RemoteComputePassEncoder_Dispatch", ReceiverName::RemoteComputePassEncoder, true, false },
    { "RemoteComputePassEncoder_DispatchIndirect", ReceiverName::RemoteComputePassEncoder, true, false },
    { "RemoteComputePassEncoder_End", ReceiverName::RemoteComputePassEncoder, true, false },
    { "RemoteComputePassEncoder_InsertDebugMarker", ReceiverName::RemoteComputePassEncoder, true, false },
    { "RemoteComputePassEncoder_PopDebugGroup", ReceiverName::RemoteComputePassEncoder, true, false },
    { "RemoteComputePassEncoder_PushDebugGroup", ReceiverName::RemoteComputePassEncoder, true, false },
    { "RemoteComputePassEncoder_SetBindGroup", ReceiverName::RemoteComputePassEncoder, true, false },
    { "RemoteComputePassEncoder_SetLabel", ReceiverName::RemoteComputePassEncoder, true, false },
    { "RemoteComputePassEncoder_SetPipeline", ReceiverName::RemoteComputePassEncoder, true, false },
    { "RemoteComputePipeline_Destruct", ReceiverName::RemoteComputePipeline, true, false },
    { "RemoteComputePipeline_GetBindGroupLayout", ReceiverName::RemoteComputePipeline, true, false },
    { "RemoteComputePipeline_SetLabel", ReceiverName::RemoteComputePipeline, true, false },
    { "RemoteDevice_CreateBindGroup", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateBindGroupLayout", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateBuffer", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateCommandEncoder", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateComputePipeline", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateComputePipelineAsync", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreatePipelineLayout", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateQuerySet", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateRenderBundleEncoder", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateRenderPipeline", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateRenderPipelineAsync", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateSampler", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateShaderModule", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_CreateTexture", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_Destroy", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_Destruct", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_ImportExternalTexture", ReceiverName::RemoteDevice, true, false },
#if PLATFORM(COCOA) && ENABLE(VIDEO)
    { "RemoteDevice_ImportExternalTextureFromPixelBuffer", ReceiverName::RemoteDevice, true, false },
#endif
    { "RemoteDevice_PopErrorScope", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_PushErrorScope", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_SetLabel", ReceiverName::RemoteDevice, true, false },
#if PLATFORM(COCOA) && ENABLE(VIDEO)
    { "RemoteDevice_SetSharedVideoFrameMemory", ReceiverName::RemoteDevice, true, false },
    { "RemoteDevice_SetSharedVideoFrameSemaphore", ReceiverName::RemoteDevice, true, false },
#endif
    { "RemoteDisplayListRecorder_ApplyDeviceScaleFactor", ReceiverName::RemoteDisplayListRecorder, true, false },
#if USE(CG)
    { "RemoteDisplayListRecorder_ApplyFillPattern", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_ApplyStrokePattern", ReceiverName::RemoteDisplayListRecorder, true, false },
#endif
    { "RemoteDisplayListRecorder_BeginTransparencyLayer", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_ClearRect", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_ClearShadow", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_Clip", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_ClipOut", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_ClipOutRoundedRect", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_ClipOutToPath", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_ClipPath", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_ClipRoundedRect", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_ClipToImageBuffer", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_ConcatenateCTM", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_ConvertToLuminanceMask", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawControlPart", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawDecomposedGlyphs", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawDotsForDocumentMarker", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawEllipse", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawFilteredImageBuffer", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawFocusRingPath", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawFocusRingRects", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawGlyphs", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawImageBuffer", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawLine", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawLinesForText", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawNativeImage", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawPath", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawPattern", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawRect", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_DrawSystemImage", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_EndTransparencyLayer", ReceiverName::RemoteDisplayListRecorder, true, false },
#if ENABLE(INLINE_PATH_DATA)
    { "RemoteDisplayListRecorder_FillArc", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_FillBezierCurve", ReceiverName::RemoteDisplayListRecorder, true, false },
#endif
    { "RemoteDisplayListRecorder_FillCompositedRect", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_FillEllipse", ReceiverName::RemoteDisplayListRecorder, true, false },
#if ENABLE(INLINE_PATH_DATA)
    { "RemoteDisplayListRecorder_FillLine", ReceiverName::RemoteDisplayListRecorder, true, false },
#endif
    { "RemoteDisplayListRecorder_FillPath", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_FillPathSegment", ReceiverName::RemoteDisplayListRecorder, true, false },
#if ENABLE(INLINE_PATH_DATA)
    { "RemoteDisplayListRecorder_FillQuadCurve", ReceiverName::RemoteDisplayListRecorder, true, false },
#endif
    { "RemoteDisplayListRecorder_FillRect", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_FillRectWithColor", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_FillRectWithGradient", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_FillRectWithRoundedHole", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_FillRoundedRect", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_FlushContext", ReceiverName::RemoteDisplayListRecorder, true, false },
#if ENABLE(VIDEO)
    { "RemoteDisplayListRecorder_PaintFrameForMedia", ReceiverName::RemoteDisplayListRecorder, true, false },
#endif
#if PLATFORM(COCOA) && ENABLE(VIDEO)
    { "RemoteDisplayListRecorder_PaintVideoFrame", ReceiverName::RemoteDisplayListRecorder, true, false },
#endif
    { "RemoteDisplayListRecorder_ResetClip", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_Restore", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_Rotate", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_Save", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_Scale", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_SetCTM", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_SetInlineFillColor", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_SetInlineStrokeColor", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_SetLineCap", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_SetLineDash", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_SetLineJoin", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_SetMiterLimit", ReceiverName::RemoteDisplayListRecorder, true, false },
#if PLATFORM(COCOA) && ENABLE(VIDEO)
    { "RemoteDisplayListRecorder_SetSharedVideoFrameMemory", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_SetSharedVideoFrameSemaphore", ReceiverName::RemoteDisplayListRecorder, true, false },
#endif
    { "RemoteDisplayListRecorder_SetState", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_SetStrokeThickness", ReceiverName::RemoteDisplayListRecorder, true, false },
#if ENABLE(INLINE_PATH_DATA)
    { "RemoteDisplayListRecorder_StrokeArc", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_StrokeBezierCurve", ReceiverName::RemoteDisplayListRecorder, true, false },
#endif
    { "RemoteDisplayListRecorder_StrokeEllipse", ReceiverName::RemoteDisplayListRecorder, true, false },
#if ENABLE(INLINE_PATH_DATA)
    { "RemoteDisplayListRecorder_StrokeLine", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_StrokeLineWithColorAndThickness", ReceiverName::RemoteDisplayListRecorder, true, false },
#endif
    { "RemoteDisplayListRecorder_StrokePath", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_StrokePathSegment", ReceiverName::RemoteDisplayListRecorder, true, false },
#if ENABLE(INLINE_PATH_DATA)
    { "RemoteDisplayListRecorder_StrokeQuadCurve", ReceiverName::RemoteDisplayListRecorder, true, false },
#endif
    { "RemoteDisplayListRecorder_StrokeRect", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_TransformToColorSpace", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteDisplayListRecorder_Translate", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteExternalTexture_Destruct", ReceiverName::RemoteExternalTexture, true, false },
    { "RemoteExternalTexture_SetLabel", ReceiverName::RemoteExternalTexture, true, false },
    { "RemoteFaceDetector_Detect", ReceiverName::RemoteFaceDetector, true, false },
    { "RemoteGPUProxy_WasCreated", ReceiverName::RemoteGPUProxy, false, false },
    { "RemoteGPU_CreateCompositorIntegration", ReceiverName::RemoteGPU, true, false },
    { "RemoteGPU_CreatePresentationContext", ReceiverName::RemoteGPU, true, false },
    { "RemoteGraphicsContextGLProxy_WasChanged", ReceiverName::RemoteGraphicsContextGLProxy, false, false },
    { "RemoteGraphicsContextGLProxy_WasCreated", ReceiverName::RemoteGraphicsContextGLProxy, false, false },
    { "RemoteGraphicsContextGLProxy_WasLost", ReceiverName::RemoteGraphicsContextGLProxy, false, false },
    { "RemoteGraphicsContextGL_ActiveTexture", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_AttachShader", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BeginQuery", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BeginQueryEXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BeginTransformFeedback", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BindAttribLocation", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BindBuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BindBufferBase", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BindBufferRange", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BindFramebuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BindRenderbuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BindSampler", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BindTexture", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BindTransformFeedback", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BindVertexArray", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BlendColor", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BlendEquation", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BlendEquationSeparate", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BlendEquationSeparateiOES", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BlendEquationiOES", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BlendFunc", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BlendFuncSeparate", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BlendFuncSeparateiOES", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BlendFunciOES", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BlitFramebuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BlitFramebufferANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BufferData0", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BufferData1", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_BufferSubData", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Clear", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ClearBufferfi", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ClearBufferfv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ClearBufferiv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ClearBufferuiv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ClearColor", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ClearDepth", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ClearStencil", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ClientWaitEGLSyncWithFlush", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ClipControlEXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ColorMask", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ColorMaskiOES", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CompileShader", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CompressedTexImage2D0", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CompressedTexImage2D1", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CompressedTexImage3D0", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CompressedTexImage3D1", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CompressedTexSubImage2D0", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CompressedTexSubImage2D1", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CompressedTexSubImage3D0", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CompressedTexSubImage3D1", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CopyBufferSubData", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CopyTexImage2D", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CopyTexSubImage2D", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CopyTexSubImage3D", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CullFace", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteBuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteFramebuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteProgram", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteQuery", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteQueryEXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteRenderbuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteSampler", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteShader", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteSync", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteTexture", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteTransformFeedback", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DeleteVertexArray", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DepthFunc", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DepthMask", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DepthRange", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DestroyEGLImage", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DetachShader", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Disable", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DisableVertexAttribArray", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DisableiOES", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DrawArrays", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DrawArraysInstanced", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DrawArraysInstancedBaseInstanceANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DrawBuffers", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DrawBuffersEXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DrawElements", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DrawElementsInstanced", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DrawElementsInstancedBaseVertexBaseInstanceANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DrawRangeElements", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Enable", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_EnableVertexAttribArray", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_EnableiOES", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_EndQuery", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_EndQueryEXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_EndTransformFeedback", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_EnsureExtensionEnabled", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Finish", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Flush", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_FramebufferRenderbuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_FramebufferTexture2D", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_FramebufferTextureLayer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_FrontFace", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GenerateMipmap", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Hint", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_InvalidateFramebuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_InvalidateSubFramebuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_LineWidth", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_LinkProgram", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_MarkContextChanged", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_MultiDrawArraysANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_MultiDrawArraysInstancedANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_MultiDrawArraysInstancedBaseInstanceANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_MultiDrawElementsANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_MultiDrawElementsInstancedANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_MultiDrawElementsInstancedBaseVertexBaseInstanceANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_PauseTransformFeedback", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_PixelStorei", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_PolygonModeANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_PolygonOffset", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_PolygonOffsetClampEXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ProvokingVertexANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_QueryCounterEXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ReadBuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ReadPixelsBufferObject", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_RenderbufferStorage", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_RenderbufferStorageMultisample", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_RenderbufferStorageMultisampleANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Reshape", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ResumeTransformFeedback", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_SampleCoverage", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_SamplerParameterf", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_SamplerParameteri", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Scissor", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_SetDrawingBufferColorSpace", ReceiverName::RemoteGraphicsContextGL, true, false },
#if ENABLE(VIDEO) && PLATFORM(COCOA)
    { "RemoteGraphicsContextGL_SetSharedVideoFrameMemory", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_SetSharedVideoFrameSemaphore", ReceiverName::RemoteGraphicsContextGL, true, false },
#endif
    { "RemoteGraphicsContextGL_ShaderSource", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_SimulateEventForTesting", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_StencilFunc", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_StencilFuncSeparate", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_StencilMask", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_StencilMaskSeparate", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_StencilOp", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_StencilOpSeparate", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexImage2D0", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexImage2D1", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexImage3D0", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexImage3D1", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexParameterf", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexParameteri", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexStorage2D", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexStorage3D", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexSubImage2D0", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexSubImage2D1", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexSubImage3D0", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TexSubImage3D1", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_TransformFeedbackVaryings", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform1f", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform1fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform1i", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform1iv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform1ui", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform1uiv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform2f", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform2fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform2i", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform2iv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform2ui", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform2uiv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform3f", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform3fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform3i", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform3iv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform3ui", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform3uiv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform4f", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform4fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform4i", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform4iv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform4ui", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Uniform4uiv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_UniformBlockBinding", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_UniformMatrix2fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_UniformMatrix2x3fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_UniformMatrix2x4fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_UniformMatrix3fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_UniformMatrix3x2fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_UniformMatrix3x4fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_UniformMatrix4fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_UniformMatrix4x2fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_UniformMatrix4x3fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_UseProgram", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ValidateProgram", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttrib1f", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttrib1fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttrib2f", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttrib2fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttrib3f", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttrib3fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttrib4f", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttrib4fv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttribDivisor", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttribI4i", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttribI4iv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttribI4ui", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttribI4uiv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttribIPointer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_VertexAttribPointer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_Viewport", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_WaitSync", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteImageBufferProxy_DidCreateBackend", ReceiverName::RemoteImageBufferProxy, false, false },
    { "RemoteLegacyCDMFactoryProxy_RemoveSession", ReceiverName::RemoteLegacyCDMFactoryProxy, false, false },
    { "RemoteLegacyCDMProxy_SetPlayerId", ReceiverName::RemoteLegacyCDMProxy, false, false },
    { "RemoteLegacyCDMSessionProxy_ReleaseKeys", ReceiverName::RemoteLegacyCDMSessionProxy, false, false },
    { "RemoteLegacyCDMSession_SendError", ReceiverName::RemoteLegacyCDMSession, false, false },
    { "RemoteLegacyCDMSession_SendMessage", ReceiverName::RemoteLegacyCDMSession, false, false },
    { "RemoteMediaEngineConfigurationFactoryProxy_CreateDecodingConfiguration", ReceiverName::RemoteMediaEngineConfigurationFactoryProxy, false, false },
    { "RemoteMediaEngineConfigurationFactoryProxy_CreateEncodingConfiguration", ReceiverName::RemoteMediaEngineConfigurationFactoryProxy, false, false },
    { "RemoteMediaPlayerManagerProxy_CreateMediaPlayer", ReceiverName::RemoteMediaPlayerManagerProxy, false, false },
    { "RemoteMediaPlayerManagerProxy_DeleteMediaPlayer", ReceiverName::RemoteMediaPlayerManagerProxy, false, false },
    { "RemoteMediaPlayerProxy_AcceleratedRenderingStateChanged", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_ApplicationDidBecomeActive", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_ApplicationWillResignActive", ReceiverName::RemoteMediaPlayerProxy, false, false },
#if ENABLE(ENCRYPTED_MEDIA)
    { "RemoteMediaPlayerProxy_AttemptToDecryptWithInstance", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
    { "RemoteMediaPlayerProxy_AudioTrackSetEnabled", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_BeginSimulatedHDCPError", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_CancelLoad", ReceiverName::RemoteMediaPlayerProxy, false, false },
#if ENABLE(ENCRYPTED_MEDIA)
    { "RemoteMediaPlayerProxy_CdmInstanceAttached", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_CdmInstanceDetached", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
#if ENABLE(WEB_AUDIO)
    { "RemoteMediaPlayerProxy_CreateAudioSourceProvider", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
    { "RemoteMediaPlayerProxy_DidLoadingProgress", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_EndSimulatedHDCPError", ReceiverName::RemoteMediaPlayerProxy, false, false },
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    { "RemoteMediaPlayerProxy_KeyAdded", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
    { "RemoteMediaPlayerProxy_Load", ReceiverName::RemoteMediaPlayerProxy, false, false },
#if ENABLE(MEDIA_SOURCE)
    { "RemoteMediaPlayerProxy_LoadMediaSource", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
    { "RemoteMediaPlayerProxy_NotifyActiveSourceBuffersChanged", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_NotifyTrackModeChanged", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_Pause", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_PauseAtHostTime", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_PerformTaskAtMediaTime", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_Play", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_PlayAtHostTime", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_PlayerContentBoxRectChanged", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_PrepareForPlayback", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_PrepareForRendering", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_PrepareToPlay", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_RequestHostingContextID", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_Seek", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SeekWithTolerance", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetBufferingPolicy", ReceiverName::RemoteMediaPlayerProxy, false, false },
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    { "RemoteMediaPlayerProxy_SetLegacyCDMSession", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
    { "RemoteMediaPlayerProxy_SetMuted", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetPageIsVisible", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetPitchCorrectionAlgorithm", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetPreferredDynamicRangeMode", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetPreload", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetPresentationSize", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetPreservesPitch", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetPrivateBrowsingMode", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetRate", ReceiverName::RemoteMediaPlayerProxy, false, false },
#if ENABLE(LEGACY_ENCRYPTED_MEDIA) && ENABLE(ENCRYPTED_MEDIA)
    { "RemoteMediaPlayerProxy_SetShouldContinueAfterKeyNeeded", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
    { "RemoteMediaPlayerProxy_SetShouldDisableHDR", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetShouldDisableSleep", ReceiverName::RemoteMediaPlayerProxy, false, false },
#if ENABLE(WEB_AUDIO)
    { "RemoteMediaPlayerProxy_SetShouldEnableAudioSourceProvider", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
    { "RemoteMediaPlayerProxy_SetShouldMaintainAspectRatio", ReceiverName::RemoteMediaPlayerProxy, false, false },
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    { "RemoteMediaPlayerProxy_SetShouldPlayToPlaybackTarget", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
#if ENABLE(VIDEO_PRESENTATION_MODE)
    { "RemoteMediaPlayerProxy_SetVideoFullscreenGravity", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetVideoFullscreenMode", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
#if PLATFORM(COCOA)
    { "RemoteMediaPlayerProxy_SetVideoInlineSizeFenced", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
    { "RemoteMediaPlayerProxy_SetVideoPlaybackMetricsUpdateInterval", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetVolume", ReceiverName::RemoteMediaPlayerProxy, false, false },
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    { "RemoteMediaPlayerProxy_SetWirelessPlaybackTarget", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_SetWirelessVideoPlaybackDisabled", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
    { "RemoteMediaPlayerProxy_StartVideoFrameMetadataGathering", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_StopVideoFrameMetadataGathering", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_TextTrackSetMode", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_TracksChanged", ReceiverName::RemoteMediaPlayerProxy, false, false },
#if ENABLE(VIDEO_PRESENTATION_MODE)
    { "RemoteMediaPlayerProxy_UpdateVideoFullscreenInlineImage", ReceiverName::RemoteMediaPlayerProxy, false, false },
    { "RemoteMediaPlayerProxy_VideoFullscreenStandbyChanged", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
    { "RemoteMediaPlayerProxy_VideoTrackSetSelected", ReceiverName::RemoteMediaPlayerProxy, false, false },
#if (PLATFORM(COCOA) && !HAVE(AVSAMPLEBUFFERDISPLAYLAYER_COPYDISPLAYEDPIXELBUFFER))
    { "RemoteMediaPlayerProxy_WillBeAskedToPaintGL", ReceiverName::RemoteMediaPlayerProxy, false, false },
#endif
    { "RemoteMediaRecorderManager_CreateRecorder", ReceiverName::RemoteMediaRecorderManager, false, false },
    { "RemoteMediaRecorderManager_ReleaseRecorder", ReceiverName::RemoteMediaRecorderManager, false, false },
    { "RemoteMediaRecorder_AudioSamplesAvailable", ReceiverName::RemoteMediaRecorder, false, false },
    { "RemoteMediaRecorder_AudioSamplesStorageChanged", ReceiverName::RemoteMediaRecorder, false, false },
    { "RemoteMediaRecorder_FetchData", ReceiverName::RemoteMediaRecorder, false, false },
    { "RemoteMediaRecorder_Pause", ReceiverName::RemoteMediaRecorder, false, false },
    { "RemoteMediaRecorder_Resume", ReceiverName::RemoteMediaRecorder, false, false },
    { "RemoteMediaRecorder_SetSharedVideoFrameMemory", ReceiverName::RemoteMediaRecorder, false, false },
    { "RemoteMediaRecorder_SetSharedVideoFrameSemaphore", ReceiverName::RemoteMediaRecorder, false, false },
    { "RemoteMediaRecorder_StopRecording", ReceiverName::RemoteMediaRecorder, false, false },
    { "RemoteMediaRecorder_VideoFrameAvailable", ReceiverName::RemoteMediaRecorder, false, false },
    { "RemoteMediaResourceManager_AccessControlCheckFailed", ReceiverName::RemoteMediaResourceManager, false, false },
    { "RemoteMediaResourceManager_DataReceived", ReceiverName::RemoteMediaResourceManager, false, false },
    { "RemoteMediaResourceManager_DataSent", ReceiverName::RemoteMediaResourceManager, false, false },
    { "RemoteMediaResourceManager_LoadFailed", ReceiverName::RemoteMediaResourceManager, false, false },
    { "RemoteMediaResourceManager_LoadFinished", ReceiverName::RemoteMediaResourceManager, false, false },
    { "RemoteMediaResourceManager_RedirectReceived", ReceiverName::RemoteMediaResourceManager, false, false },
    { "RemoteMediaResourceManager_ResponseReceived", ReceiverName::RemoteMediaResourceManager, false, false },
    { "RemoteMediaSessionCoordinatorProxy_CoordinatePause", ReceiverName::RemoteMediaSessionCoordinatorProxy, false, false },
    { "RemoteMediaSessionCoordinatorProxy_CoordinatePlay", ReceiverName::RemoteMediaSessionCoordinatorProxy, false, false },
    { "RemoteMediaSessionCoordinatorProxy_CoordinateSeekTo", ReceiverName::RemoteMediaSessionCoordinatorProxy, false, false },
    { "RemoteMediaSessionCoordinatorProxy_CoordinateSetTrack", ReceiverName::RemoteMediaSessionCoordinatorProxy, false, false },
    { "RemoteMediaSessionCoordinatorProxy_Join", ReceiverName::RemoteMediaSessionCoordinatorProxy, false, false },
    { "RemoteMediaSessionCoordinatorProxy_Leave", ReceiverName::RemoteMediaSessionCoordinatorProxy, false, false },
    { "RemoteMediaSessionCoordinatorProxy_PlaybackStateChanged", ReceiverName::RemoteMediaSessionCoordinatorProxy, false, false },
    { "RemoteMediaSessionCoordinatorProxy_PositionStateChanged", ReceiverName::RemoteMediaSessionCoordinatorProxy, false, false },
    { "RemoteMediaSessionCoordinatorProxy_ReadyStateChanged", ReceiverName::RemoteMediaSessionCoordinatorProxy, false, false },
    { "RemoteMediaSessionCoordinatorProxy_TrackIdentifierChanged", ReceiverName::RemoteMediaSessionCoordinatorProxy, false, false },
    { "RemoteMediaSessionCoordinator_CoordinatorStateChanged", ReceiverName::RemoteMediaSessionCoordinator, false, false },
    { "RemoteMediaSessionCoordinator_PauseSession", ReceiverName::RemoteMediaSessionCoordinator, false, false },
    { "RemoteMediaSessionCoordinator_PlaySession", ReceiverName::RemoteMediaSessionCoordinator, false, false },
    { "RemoteMediaSessionCoordinator_SeekSessionToTime", ReceiverName::RemoteMediaSessionCoordinator, false, false },
    { "RemoteMediaSessionCoordinator_SetSessionTrack", ReceiverName::RemoteMediaSessionCoordinator, false, false },
    { "RemoteMediaSourceProxy_BufferedChanged", ReceiverName::RemoteMediaSourceProxy, false, false },
    { "RemoteMediaSourceProxy_DurationChanged", ReceiverName::RemoteMediaSourceProxy, false, false },
    { "RemoteMediaSourceProxy_MarkEndOfStream", ReceiverName::RemoteMediaSourceProxy, false, false },
    { "RemoteMediaSourceProxy_SeekCompleted", ReceiverName::RemoteMediaSourceProxy, false, false },
    { "RemoteMediaSourceProxy_SetIsSeeking", ReceiverName::RemoteMediaSourceProxy, false, false },
    { "RemoteMediaSourceProxy_SetReadyState", ReceiverName::RemoteMediaSourceProxy, false, false },
    { "RemoteMediaSourceProxy_SetTimeFudgeFactor", ReceiverName::RemoteMediaSourceProxy, false, false },
    { "RemoteMediaSourceProxy_UnmarkEndOfStream", ReceiverName::RemoteMediaSourceProxy, false, false },
    { "RemoteMediaSourceProxy_WaitForSeekCompleted", ReceiverName::RemoteMediaSourceProxy, false, false },
    { "RemotePipelineLayout_Destruct", ReceiverName::RemotePipelineLayout, true, false },
    { "RemotePipelineLayout_SetLabel", ReceiverName::RemotePipelineLayout, true, false },
    { "RemotePresentationContext_Configure", ReceiverName::RemotePresentationContext, true, false },
    { "RemotePresentationContext_GetCurrentTexture", ReceiverName::RemotePresentationContext, true, false },
    { "RemotePresentationContext_Unconfigure", ReceiverName::RemotePresentationContext, true, false },
    { "RemoteQuerySet_Destroy", ReceiverName::RemoteQuerySet, true, false },
    { "RemoteQuerySet_Destruct", ReceiverName::RemoteQuerySet, true, false },
    { "RemoteQuerySet_SetLabel", ReceiverName::RemoteQuerySet, true, false },
    { "RemoteQueue_CopyExternalImageToTexture", ReceiverName::RemoteQueue, true, false },
    { "RemoteQueue_Destruct", ReceiverName::RemoteQueue, true, false },
    { "RemoteQueue_SetLabel", ReceiverName::RemoteQueue, true, false },
    { "RemoteQueue_Submit", ReceiverName::RemoteQueue, true, false },
    { "RemoteQueue_WriteBuffer", ReceiverName::RemoteQueue, true, false },
    { "RemoteQueue_WriteTexture", ReceiverName::RemoteQueue, true, false },
    { "RemoteRemoteCommandListenerProxy_UpdateSupportedCommands", ReceiverName::RemoteRemoteCommandListenerProxy, false, false },
    { "RemoteRemoteCommandListener_DidReceiveRemoteControlCommand", ReceiverName::RemoteRemoteCommandListener, false, false },
    { "RemoteRenderBundleEncoder_Destruct", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_Draw", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_DrawIndexed", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_DrawIndexedIndirect", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_DrawIndirect", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_Finish", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_InsertDebugMarker", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_PopDebugGroup", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_PushDebugGroup", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_SetBindGroup", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_SetIndexBuffer", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_SetLabel", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_SetPipeline", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundleEncoder_SetVertexBuffer", ReceiverName::RemoteRenderBundleEncoder, true, false },
    { "RemoteRenderBundle_Destruct", ReceiverName::RemoteRenderBundle, true, false },
    { "RemoteRenderBundle_SetLabel", ReceiverName::RemoteRenderBundle, true, false },
    { "RemoteRenderPassEncoder_BeginOcclusionQuery", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_Destruct", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_Draw", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_DrawIndexed", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_DrawIndexedIndirect", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_DrawIndirect", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_End", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_EndOcclusionQuery", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_ExecuteBundles", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_InsertDebugMarker", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_PopDebugGroup", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_PushDebugGroup", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_SetBindGroup", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_SetBlendConstant", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_SetIndexBuffer", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_SetLabel", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_SetPipeline", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_SetScissorRect", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_SetStencilReference", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_SetVertexBuffer", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPassEncoder_SetViewport", ReceiverName::RemoteRenderPassEncoder, true, false },
    { "RemoteRenderPipeline_Destruct", ReceiverName::RemoteRenderPipeline, true, false },
    { "RemoteRenderPipeline_GetBindGroupLayout", ReceiverName::RemoteRenderPipeline, true, false },
    { "RemoteRenderPipeline_SetLabel", ReceiverName::RemoteRenderPipeline, true, false },
    { "RemoteRenderingBackendProxy_DidFinalizeRenderingUpdate", ReceiverName::RemoteRenderingBackendProxy, false, false },
    { "RemoteRenderingBackendProxy_DidInitialize", ReceiverName::RemoteRenderingBackendProxy, false, false },
    { "RemoteRenderingBackendProxy_DidMarkLayersAsVolatile", ReceiverName::RemoteRenderingBackendProxy, false, false },
    { "RemoteRenderingBackend_CacheDecomposedGlyphs", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_CacheFilter", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_CacheFont", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_CacheFontCustomPlatformData", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_CacheGradient", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_CacheNativeImage", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_CreateImageBuffer", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_CreateRemoteBarcodeDetector", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_CreateRemoteFaceDetector", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_CreateRemoteTextDetector", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_DestroyGetPixelBufferSharedMemory", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_FinalizeRenderingUpdate", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_GetRemoteBarcodeDetectorSupportedFormats", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_MarkSurfacesVolatile", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_MoveToImageBuffer", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_MoveToSerializedBuffer", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_PutPixelBufferForImageBuffer", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_ReleaseAllImageResources", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_ReleaseAllResources", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_ReleaseRemoteBarcodeDetector", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_ReleaseRemoteFaceDetector", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_ReleaseRemoteTextDetector", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_ReleaseRenderingResource", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteSampleBufferDisplayLayerManager_CreateLayer", ReceiverName::RemoteSampleBufferDisplayLayerManager, false, false },
    { "RemoteSampleBufferDisplayLayerManager_ReleaseLayer", ReceiverName::RemoteSampleBufferDisplayLayerManager, false, false },
    { "RemoteSampleBufferDisplayLayer_ClearVideoFrames", ReceiverName::RemoteSampleBufferDisplayLayer, false, false },
    { "RemoteSampleBufferDisplayLayer_EnqueueVideoFrame", ReceiverName::RemoteSampleBufferDisplayLayer, false, false },
    { "RemoteSampleBufferDisplayLayer_Flush", ReceiverName::RemoteSampleBufferDisplayLayer, false, false },
    { "RemoteSampleBufferDisplayLayer_FlushAndRemoveImage", ReceiverName::RemoteSampleBufferDisplayLayer, false, false },
    { "RemoteSampleBufferDisplayLayer_Pause", ReceiverName::RemoteSampleBufferDisplayLayer, false, false },
    { "RemoteSampleBufferDisplayLayer_Play", ReceiverName::RemoteSampleBufferDisplayLayer, false, false },
#if !RELEASE_LOG_DISABLED
    { "RemoteSampleBufferDisplayLayer_SetLogIdentifier", ReceiverName::RemoteSampleBufferDisplayLayer, false, false },
#endif
    { "RemoteSampleBufferDisplayLayer_SetSharedVideoFrameMemory", ReceiverName::RemoteSampleBufferDisplayLayer, false, false },
    { "RemoteSampleBufferDisplayLayer_SetSharedVideoFrameSemaphore", ReceiverName::RemoteSampleBufferDisplayLayer, false, false },
    { "RemoteSampleBufferDisplayLayer_UpdateBoundsAndPosition", ReceiverName::RemoteSampleBufferDisplayLayer, false, false },
    { "RemoteSampleBufferDisplayLayer_UpdateDisplayMode", ReceiverName::RemoteSampleBufferDisplayLayer, false, false },
    { "RemoteSampler_Destruct", ReceiverName::RemoteSampler, true, false },
    { "RemoteSampler_SetLabel", ReceiverName::RemoteSampler, true, false },
    { "RemoteShaderModule_CompilationInfo", ReceiverName::RemoteShaderModule, true, false },
    { "RemoteShaderModule_Destruct", ReceiverName::RemoteShaderModule, true, false },
    { "RemoteShaderModule_SetLabel", ReceiverName::RemoteShaderModule, true, false },
    { "RemoteSourceBufferProxy_Abort", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_AddTrackBuffer", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_Append", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_BufferedSamplesForTrackId", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_ClearTrackBuffers", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_ClientReadyStateChanged", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_EnqueuedSamplesForTrackID", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_MemoryPressure", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_ReenqueueMediaIfNeeded", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_RemoveCodedFrames", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_RemovedFromMediaSource", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_ResetParserState", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_ResetTimestampOffsetInTrackBuffers", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_ResetTrackBuffers", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SeekToTime", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetActive", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetAllTrackBuffersNeedRandomAccess", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetAppendWindowEnd", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetAppendWindowStart", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetGroupStartTimestamp", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetGroupStartTimestampToEndTimestamp", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetMaximumQueueDepthForTrackID", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetMediaSourceEnded", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetMode", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetReadyState", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetShouldGenerateTimestamps", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_SetTimestampOffset", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_StartChangingType", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteSourceBufferProxy_UpdateTrackIds", ReceiverName::RemoteSourceBufferProxy, false, false },
    { "RemoteTextDetector_Detect", ReceiverName::RemoteTextDetector, true, false },
    { "RemoteTextureView_Destruct", ReceiverName::RemoteTextureView, true, false },
    { "RemoteTextureView_SetLabel", ReceiverName::RemoteTextureView, true, false },
    { "RemoteTexture_CreateView", ReceiverName::RemoteTexture, true, false },
    { "RemoteTexture_Destroy", ReceiverName::RemoteTexture, true, false },
    { "RemoteTexture_Destruct", ReceiverName::RemoteTexture, true, false },
    { "RemoteTexture_SetLabel", ReceiverName::RemoteTexture, true, false },
    { "RemoteVideoFrameObjectHeapProxyProcessor_NewConvertedVideoFrameBuffer", ReceiverName::RemoteVideoFrameObjectHeapProxyProcessor, false, false },
    { "RemoteVideoFrameObjectHeapProxyProcessor_NewVideoFrameBuffer", ReceiverName::RemoteVideoFrameObjectHeapProxyProcessor, false, false },
    { "RemoteVideoFrameObjectHeapProxyProcessor_SetSharedVideoFrameMemory", ReceiverName::RemoteVideoFrameObjectHeapProxyProcessor, false, false },
    { "RemoteVideoFrameObjectHeapProxyProcessor_SetSharedVideoFrameSemaphore", ReceiverName::RemoteVideoFrameObjectHeapProxyProcessor, false, false },
#if PLATFORM(COCOA)
    { "RemoteVideoFrameObjectHeap_GetVideoFrameBuffer", ReceiverName::RemoteVideoFrameObjectHeap, true, false },
#endif
    { "RemoteVideoFrameObjectHeap_ReleaseVideoFrame", ReceiverName::RemoteVideoFrameObjectHeap, true, false },
#if PLATFORM(COCOA)
    { "RemoteVideoFrameObjectHeap_SetSharedVideoFrameMemory", ReceiverName::RemoteVideoFrameObjectHeap, false, false },
    { "RemoteVideoFrameObjectHeap_SetSharedVideoFrameSemaphore", ReceiverName::RemoteVideoFrameObjectHeap, false, false },
#endif
    { "RemoteWebInspectorUIProxy_BringToFront", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_FrontendDidClose", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_FrontendLoaded", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_Load", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_OpenURLExternally", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_PickColorFromScreen", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_Reopen", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_ResetState", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_RevealFileExternally", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_Save", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_SendMessageToBackend", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_SetForcedAppearance", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_SetInspectorPageDeveloperExtrasEnabled", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_SetSheetRect", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_ShowCertificate", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUIProxy_StartWindowDrag", ReceiverName::RemoteWebInspectorUIProxy, false, false },
    { "RemoteWebInspectorUI_Initialize", ReceiverName::RemoteWebInspectorUI, false, false },
    { "RemoteWebInspectorUI_SendMessageToFrontend", ReceiverName::RemoteWebInspectorUI, false, false },
#if ENABLE(INSPECTOR_TELEMETRY)
    { "RemoteWebInspectorUI_SetDiagnosticLoggingAvailable", ReceiverName::RemoteWebInspectorUI, false, false },
#endif
    { "RemoteWebInspectorUI_ShowConsole", ReceiverName::RemoteWebInspectorUI, false, false },
    { "RemoteWebInspectorUI_ShowResources", ReceiverName::RemoteWebInspectorUI, false, false },
    { "RemoteWebInspectorUI_UpdateFindString", ReceiverName::RemoteWebInspectorUI, false, false },
    { "RemoteWebLockRegistry_DidCompleteLockRequest", ReceiverName::RemoteWebLockRegistry, false, false },
    { "RemoteWebLockRegistry_DidStealLock", ReceiverName::RemoteWebLockRegistry, false, false },
    { "SampleBufferDisplayLayer_SetDidFail", ReceiverName::SampleBufferDisplayLayer, false, false },
    { "ServiceWorkerDownloadTask_DidFail", ReceiverName::ServiceWorkerDownloadTask, false, false },
    { "ServiceWorkerDownloadTask_DidFinish", ReceiverName::ServiceWorkerDownloadTask, false, false },
    { "ServiceWorkerDownloadTask_DidReceiveData", ReceiverName::ServiceWorkerDownloadTask, false, false },
    { "ServiceWorkerDownloadTask_DidReceiveFormData", ReceiverName::ServiceWorkerDownloadTask, false, false },
    { "ServiceWorkerFetchTask_DidFail", ReceiverName::ServiceWorkerFetchTask, false, false },
    { "ServiceWorkerFetchTask_DidFinish", ReceiverName::ServiceWorkerFetchTask, false, false },
    { "ServiceWorkerFetchTask_DidNotHandle", ReceiverName::ServiceWorkerFetchTask, false, false },
    { "ServiceWorkerFetchTask_DidReceiveData", ReceiverName::ServiceWorkerFetchTask, false, false },
    { "ServiceWorkerFetchTask_DidReceiveFormData", ReceiverName::ServiceWorkerFetchTask, false, false },
    { "ServiceWorkerFetchTask_DidReceiveRedirectResponse", ReceiverName::ServiceWorkerFetchTask, false, false },
    { "ServiceWorkerFetchTask_DidReceiveResponse", ReceiverName::ServiceWorkerFetchTask, false, false },
    { "ServiceWorkerFetchTask_UsePreload", ReceiverName::ServiceWorkerFetchTask, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateAppendComplete", ReceiverName::SourceBufferPrivateRemote, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateBufferedChanged", ReceiverName::SourceBufferPrivateRemote, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateDidDropSample", ReceiverName::SourceBufferPrivateRemote, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateDidParseSample", ReceiverName::SourceBufferPrivateRemote, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveInitializationSegment", ReceiverName::SourceBufferPrivateRemote, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveRenderingError", ReceiverName::SourceBufferPrivateRemote, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateDurationChanged", ReceiverName::SourceBufferPrivateRemote, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateHighestPresentationTimestampChanged", ReceiverName::SourceBufferPrivateRemote, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateReportExtraMemoryCost", ReceiverName::SourceBufferPrivateRemote, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateStreamEndedWithDecodeError", ReceiverName::SourceBufferPrivateRemote, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateTrackBuffersChanged", ReceiverName::SourceBufferPrivateRemote, false, false },
    { "SpeechRecognitionRealtimeMediaSourceManager_CreateSource", ReceiverName::SpeechRecognitionRealtimeMediaSourceManager, false, false },
    { "SpeechRecognitionRealtimeMediaSourceManager_DeleteSource", ReceiverName::SpeechRecognitionRealtimeMediaSourceManager, false, false },
#if ENABLE(SANDBOX_EXTENSIONS)
    { "SpeechRecognitionRealtimeMediaSourceManager_GrantSandboxExtensions", ReceiverName::SpeechRecognitionRealtimeMediaSourceManager, false, false },
    { "SpeechRecognitionRealtimeMediaSourceManager_RevokeSandboxExtensions", ReceiverName::SpeechRecognitionRealtimeMediaSourceManager, false, false },
#endif
    { "SpeechRecognitionRealtimeMediaSourceManager_Start", ReceiverName::SpeechRecognitionRealtimeMediaSourceManager, false, false },
    { "SpeechRecognitionRealtimeMediaSourceManager_Stop", ReceiverName::SpeechRecognitionRealtimeMediaSourceManager, false, false },
    { "SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteAudioSamplesAvailable", ReceiverName::SpeechRecognitionRemoteRealtimeMediaSourceManager, false, false },
    { "SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteCaptureFailed", ReceiverName::SpeechRecognitionRemoteRealtimeMediaSourceManager, false, false },
    { "SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteSourceStopped", ReceiverName::SpeechRecognitionRemoteRealtimeMediaSourceManager, false, false },
#if PLATFORM(COCOA)
    { "SpeechRecognitionRemoteRealtimeMediaSourceManager_SetStorage", ReceiverName::SpeechRecognitionRemoteRealtimeMediaSourceManager, false, false },
#endif
    { "SpeechRecognitionServer_Abort", ReceiverName::SpeechRecognitionServer, false, false },
    { "SpeechRecognitionServer_Invalidate", ReceiverName::SpeechRecognitionServer, false, false },
    { "SpeechRecognitionServer_Start", ReceiverName::SpeechRecognitionServer, false, false },
    { "SpeechRecognitionServer_Stop", ReceiverName::SpeechRecognitionServer, false, false },
    { "StorageAreaMap_ClearCache", ReceiverName::StorageAreaMap, false, false },
    { "StorageAreaMap_DispatchStorageEvent", ReceiverName::StorageAreaMap, false, false },
    { "VisitedLinkStore_AddVisitedLinkHashFromPage", ReceiverName::VisitedLinkStore, false, false },
    { "VisitedLinkTableController_AllVisitedLinkStateChanged", ReceiverName::VisitedLinkTableController, false, false },
    { "VisitedLinkTableController_RemoveAllVisitedLinks", ReceiverName::VisitedLinkTableController, false, false },
    { "VisitedLinkTableController_SetVisitedLinkTable", ReceiverName::VisitedLinkTableController, false, false },
    { "VisitedLinkTableController_VisitedLinkStateChanged", ReceiverName::VisitedLinkTableController, false, false },
    { "WebAutomationSessionProxy_ComputeElementLayout", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_DeleteCookie", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_EvaluateJavaScriptFunction", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_GetComputedLabel", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_GetComputedRole", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_GetCookiesForFrame", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_ResolveChildFrameWithName", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_ResolveChildFrameWithNodeHandle", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_ResolveChildFrameWithOrdinal", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_ResolveParentFrame", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_SelectOptionElement", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_SetFilesForInputFileUpload", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_SnapshotRectForScreenshot", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSessionProxy_TakeScreenshot", ReceiverName::WebAutomationSessionProxy, false, false },
    { "WebAutomationSession_DidEvaluateJavaScriptFunction", ReceiverName::WebAutomationSession, false, false },
    { "WebAutomationSession_DidTakeScreenshot", ReceiverName::WebAutomationSession, false, false },
    { "WebBroadcastChannelRegistry_PostMessageToRemote", ReceiverName::WebBroadcastChannelRegistry, false, false },
    { "WebConnection_HandleMessage", ReceiverName::WebConnection, false, false },
    { "WebCookieManager_DeleteAllCookies", ReceiverName::WebCookieManager, false, false },
    { "WebCookieManager_DeleteAllCookiesModifiedSince", ReceiverName::WebCookieManager, false, false },
    { "WebCookieManager_DeleteCookie", ReceiverName::WebCookieManager, false, false },
    { "WebCookieManager_DeleteCookiesForHostnames", ReceiverName::WebCookieManager, false, false },
    { "WebCookieManager_GetAllCookies", ReceiverName::WebCookieManager, false, false },
    { "WebCookieManager_GetCookies", ReceiverName::WebCookieManager, false, false },
    { "WebCookieManager_GetHTTPCookieAcceptPolicy", ReceiverName::WebCookieManager, false, false },
    { "WebCookieManager_GetHostnamesWithCookies", ReceiverName::WebCookieManager, false, false },
#if USE(SOUP)
    { "WebCookieManager_ReplaceCookies", ReceiverName::WebCookieManager, false, false },
#endif
    { "WebCookieManager_SetCookie", ReceiverName::WebCookieManager, false, false },
#if USE(SOUP)
    { "WebCookieManager_SetCookiePersistentStorage", ReceiverName::WebCookieManager, false, false },
#endif
    { "WebCookieManager_SetCookies", ReceiverName::WebCookieManager, false, false },
    { "WebCookieManager_SetHTTPCookieAcceptPolicy", ReceiverName::WebCookieManager, false, false },
    { "WebCookieManager_StartObservingCookieChanges", ReceiverName::WebCookieManager, false, false },
    { "WebCookieManager_StopObservingCookieChanges", ReceiverName::WebCookieManager, false, false },
    { "WebFileSystemStorageConnection_InvalidateAccessHandle", ReceiverName::WebFileSystemStorageConnection, false, false },
    { "WebFullScreenManagerProxy_BeganEnterFullScreen", ReceiverName::WebFullScreenManagerProxy, false, false },
    { "WebFullScreenManagerProxy_BeganExitFullScreen", ReceiverName::WebFullScreenManagerProxy, false, false },
    { "WebFullScreenManagerProxy_Close", ReceiverName::WebFullScreenManagerProxy, false, false },
    { "WebFullScreenManagerProxy_EnterFullScreen", ReceiverName::WebFullScreenManagerProxy, false, false },
    { "WebFullScreenManagerProxy_ExitFullScreen", ReceiverName::WebFullScreenManagerProxy, false, false },
    { "WebFullScreenManager_DidEnterFullScreen", ReceiverName::WebFullScreenManager, false, false },
    { "WebFullScreenManager_DidExitFullScreen", ReceiverName::WebFullScreenManager, false, false },
    { "WebFullScreenManager_RequestExitFullScreen", ReceiverName::WebFullScreenManager, false, false },
    { "WebFullScreenManager_RequestRestoreFullScreen", ReceiverName::WebFullScreenManager, false, false },
    { "WebFullScreenManager_RestoreScrollPosition", ReceiverName::WebFullScreenManager, false, false },
    { "WebFullScreenManager_SaveScrollPosition", ReceiverName::WebFullScreenManager, false, false },
    { "WebFullScreenManager_SetAnimatingFullScreen", ReceiverName::WebFullScreenManager, false, false },
    { "WebFullScreenManager_SetFullscreenAutoHideDuration", ReceiverName::WebFullScreenManager, false, false },
    { "WebFullScreenManager_SetFullscreenControlsHidden", ReceiverName::WebFullScreenManager, false, false },
    { "WebFullScreenManager_SetFullscreenInsets", ReceiverName::WebFullScreenManager, false, false },
    { "WebFullScreenManager_WillEnterFullScreen", ReceiverName::WebFullScreenManager, false, false },
    { "WebFullScreenManager_WillExitFullScreen", ReceiverName::WebFullScreenManager, false, false },
    { "WebGeolocationManagerProxy_SetEnableHighAccuracy", ReceiverName::WebGeolocationManagerProxy, false, false },
    { "WebGeolocationManagerProxy_StartUpdating", ReceiverName::WebGeolocationManagerProxy, false, false },
    { "WebGeolocationManagerProxy_StopUpdating", ReceiverName::WebGeolocationManagerProxy, false, false },
    { "WebGeolocationManager_DidChangePosition", ReceiverName::WebGeolocationManager, false, false },
    { "WebGeolocationManager_DidFailToDeterminePosition", ReceiverName::WebGeolocationManager, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebGeolocationManager_ResetPermissions", ReceiverName::WebGeolocationManager, false, false },
#endif
    { "WebIDBConnectionToServer_DidAbortTransaction", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidClearObjectStore", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidCloseFromServer", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidCommitTransaction", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidCreateIndex", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidCreateObjectStore", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidDeleteDatabase", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidDeleteIndex", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidDeleteObjectStore", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidDeleteRecord", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidGetAllDatabaseNamesAndVersions", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidGetAllRecords", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidGetCount", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidGetRecord", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidIterateCursor", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidOpenCursor", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidOpenDatabase", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidPutOrAdd", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidRenameIndex", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidRenameObjectStore", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_DidStartTransaction", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_FireVersionChangeEvent", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebIDBConnectionToServer_NotifyOpenDBRequestBlocked", ReceiverName::WebIDBConnectionToServer, false, false },
    { "WebInspectorInterruptDispatcher_NotifyNeedDebuggerBreak", ReceiverName::WebInspectorInterruptDispatcher, false, false },
    { "WebInspectorUIProxy_AttachAvailabilityChanged", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_AttachBottom", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_AttachLeft", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_AttachRight", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_BringToFront", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_Detach", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_DidClose", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_ElementSelectionChanged", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_FrontendLoaded", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_InspectedURLChanged", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_Load", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_OpenLocalInspectorFrontend", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_OpenURLExternally", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_PickColorFromScreen", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_Reopen", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_ResetState", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_RevealFileExternally", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_Save", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_SendMessageToBackend", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_SetAttachedWindowHeight", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_SetAttachedWindowWidth", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_SetDeveloperPreferenceOverride", ReceiverName::WebInspectorUIProxy, false, false },
#if ENABLE(INSPECTOR_NETWORK_THROTTLING)
    { "WebInspectorUIProxy_SetEmulatedConditions", ReceiverName::WebInspectorUIProxy, false, false },
#endif
    { "WebInspectorUIProxy_SetForcedAppearance", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_SetFrontendConnection", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_SetInspectorPageDeveloperExtrasEnabled", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_SetSheetRect", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_ShowCertificate", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_StartWindowDrag", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUIProxy_TimelineRecordingChanged", ReceiverName::WebInspectorUIProxy, false, false },
    { "WebInspectorUI_AttachedBottom", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_AttachedLeft", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_AttachedRight", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_Detached", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_EstablishConnection", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_EvaluateInFrontendForTesting", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_SendMessageToFrontend", ReceiverName::WebInspectorUI, false, false },
#if ENABLE(INSPECTOR_TELEMETRY)
    { "WebInspectorUI_SetDiagnosticLoggingAvailable", ReceiverName::WebInspectorUI, false, false },
#endif
    { "WebInspectorUI_SetDockingUnavailable", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_SetIsVisible", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_ShowConsole", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_ShowMainResourceForFrame", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_ShowResources", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_StartElementSelection", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_StartPageProfiling", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_StopElementSelection", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_StopPageProfiling", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_UpdateConnection", ReceiverName::WebInspectorUI, false, false },
    { "WebInspectorUI_UpdateFindString", ReceiverName::WebInspectorUI, false, false },
    { "WebInspector_Close", ReceiverName::WebInspector, false, false },
    { "WebInspector_SetAttached", ReceiverName::WebInspector, false, false },
    { "WebInspector_SetFrontendConnection", ReceiverName::WebInspector, false, false },
    { "WebInspector_Show", ReceiverName::WebInspector, false, false },
    { "WebInspector_ShowConsole", ReceiverName::WebInspector, false, false },
    { "WebInspector_ShowMainResourceForFrame", ReceiverName::WebInspector, false, false },
    { "WebInspector_ShowResources", ReceiverName::WebInspector, false, false },
    { "WebInspector_StartElementSelection", ReceiverName::WebInspector, false, false },
    { "WebInspector_StartPageProfiling", ReceiverName::WebInspector, false, false },
    { "WebInspector_StopElementSelection", ReceiverName::WebInspector, false, false },
    { "WebInspector_StopPageProfiling", ReceiverName::WebInspector, false, false },
    { "WebLockRegistryProxy_AbortLockRequest", ReceiverName::WebLockRegistryProxy, false, false },
    { "WebLockRegistryProxy_ClientIsGoingAway", ReceiverName::WebLockRegistryProxy, false, false },
    { "WebLockRegistryProxy_ReleaseLock", ReceiverName::WebLockRegistryProxy, false, false },
    { "WebLockRegistryProxy_RequestLock", ReceiverName::WebLockRegistryProxy, false, false },
    { "WebLockRegistryProxy_Snapshot", ReceiverName::WebLockRegistryProxy, false, false },
    { "WebNotificationManager_DidClickNotification", ReceiverName::WebNotificationManager, false, false },
    { "WebNotificationManager_DidCloseNotifications", ReceiverName::WebNotificationManager, false, false },
    { "WebNotificationManager_DidRemoveNotificationDecisions", ReceiverName::WebNotificationManager, false, false },
    { "WebNotificationManager_DidShowNotification", ReceiverName::WebNotificationManager, false, false },
    { "WebNotificationManager_DidUpdateNotificationDecision", ReceiverName::WebNotificationManager, false, false },
#if ENABLE(APPLE_PAY_AMS_UI)
    { "WebPageProxy_AbortApplePayAMSUISession", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(MEDIA_USAGE)
    { "WebPageProxy_AddMediaUsageManagerSession", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    { "WebPageProxy_AddPlaybackTargetPickerClient", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPageProxy_AssistiveTechnologyMakeFirstResponder", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_BackForwardAddItem", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_BackForwardClear", ReceiverName::WebPageProxy, false, false },
#if ENABLE(MEDIA_STREAM)
    { "WebPageProxy_BeginMonitoringCaptureDevices", ReceiverName::WebPageProxy, false, false },
#endif
#if USE(SYSTEM_PREVIEW)
    { "WebPageProxy_BeginSystemPreview", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(VIDEO)
    { "WebPageProxy_BeginTextRecognitionForVideoInElementFullScreen", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPageProxy_BindAccessibilityTree", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_BroadcastFrameRemovalToOtherProcesses", ReceiverName::WebPageProxy, false, false },
#if ENABLE(VIDEO)
    { "WebPageProxy_CancelTextRecognitionForVideoInElementFullScreen", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPageProxy_ChangeUniversalAccessZoomFocus", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_ClearAllEditCommands", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ClearTextIndicator", ReceiverName::WebPageProxy, false, false },
#if ENABLE(ATTACHMENT_ELEMENT)
    { "WebPageProxy_CloneAttachmentData", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_ClosePage", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_CommitPotentialTapFailed", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_CompositionWasCanceled", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ConfigureLoggingChannel", ReceiverName::WebPageProxy, false, false },
#if ENABLE(CONTENT_FILTERING)
    { "WebPageProxy_ContentFilterDidBlockLoadForFrame", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(CONTENT_EXTENSIONS)
    { "WebPageProxy_ContentRuleListNotification", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_CouldNotRestorePageState", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_CreateInspectorTarget", ReceiverName::WebPageProxy, false, false },
#if ENABLE(PDFKIT_PLUGIN)
    { "WebPageProxy_CreatePDFHUD", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DecidePolicyForNavigationActionAsync", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DecidePolicyForNewWindowAction", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DecidePolicyForResponse", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DestroyInspectorTarget", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidApplyLinkDecorationFiltering", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidCancelClientRedirectForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidChangeContentSize", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidChangeInspectorFrontendCount", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidChangeIntrinsicContentSize", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidChangeMainDocument", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidChangePageCount", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidChangeProgress", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidChangeProvisionalURLForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidChangeScrollOffsetPinningForMainFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidChangeScrollbarsForMainFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidChangeViewportProperties", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidCommitLoadForFrame", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_DidCompleteSyntheticClick", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidCountStringMatches", ReceiverName::WebPageProxy, false, false },
#if HAVE(VISIBILITY_PROPAGATION_VIEW)
    { "WebPageProxy_DidCreateContextInWebProcessForVisibilityPropagation", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidCreateMainFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidCreateSleepDisabler", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidCreateSubframe", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidDestroyNavigation", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidDestroySleepDisabler", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidDisplayInsecureContentForFrame", ReceiverName::WebPageProxy, false, false },
#if ENABLE(DRAG_SUPPORT)
    { "WebPageProxy_DidEndDragging", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidExplicitOpenForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidFailLoadForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidFailProvisionalLoadForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidFailToFindString", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidFailToSuspendAfterProcessSwap", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidFindString", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidFindStringMatches", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidFindTextManipulationItems", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidFinishDocumentLoadForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidFinishLoadForFrame", ReceiverName::WebPageProxy, false, false },
#if USE(QUICK_LOOK)
    { "WebPageProxy_DidFinishLoadForQuickLookDocumentInMainFrame", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPageProxy_DidFinishLoadForResource", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidFinishLoadingDataForCustomContentProvider", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidFinishProgress", ReceiverName::WebPageProxy, false, false },
#if ENABLE(SERVICE_WORKER)
    { "WebPageProxy_DidFinishServiceWorkerPageRegistration", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidFirstLayoutForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidFirstVisuallyNonEmptyLayoutForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidGetImageForFindMatch", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_DidGetTapHighlightGeometries", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPageProxy_DidHandleAcceptedCandidate", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    { "WebPageProxy_DidHandleAdditionalDragItemsRequest", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidHandleDragStartRequest", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_DidHandleTapAsHover", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPageProxy_DidInitiateLoadForResource", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
    { "WebPageProxy_DidInsertAttachmentWithIdentifier", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidNavigateWithNavigationData", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_DidNotHandleTapAsClick", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidPerformClientRedirect", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(COCOA)
    { "WebPageProxy_DidPerformDictionaryLookup", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(DRAG_SUPPORT)
    { "WebPageProxy_DidPerformDragControllerAction", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidPerformDragOperation", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPageProxy_DidPerformImmediateActionHitTest", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidPerformServerRedirect", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidReachLayoutMilestone", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    { "WebPageProxy_DidReceiveEditDragSnapshot", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidReceiveEvent", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_DidReceivePositionInformation", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPageProxy_DidReceiveResponseForResource", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidReceiveServerRedirectForProvisionalLoadForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidReceiveTitleForFrame", ReceiverName::WebPageProxy, false, false },
#if ENABLE(ATTACHMENT_ELEMENT)
    { "WebPageProxy_DidRemoveAttachmentWithIdentifier", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidResignInputElementStrongPasswordAppearance", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidRestoreScrollPosition", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidRunInsecureContentForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidSameDocumentNavigationForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidSameDocumentNavigationForFrameViaJSHistoryAPI", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPageProxy_DidSendRequestForResource", ReceiverName::WebPageProxy, false, false },
#endif
#if USE(QUICK_LOOK)
    { "WebPageProxy_DidStartLoadForQuickLookDocumentInMainFrame", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_DidStartProgress", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidStartProvisionalLoadForFrame", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidSuspendAfterProcessSwap", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidUpdateActivityState", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidUpdateHistoryTitle", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DidUpdateRenderingAfterCommittingLoad", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_DisableDoubleTapGesturesDuringTapIfNecessary", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_DisableInspectorNodeSearch", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPageProxy_DismissCorrectionPanel", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_EditorStateChanged", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_ElementDidBlur", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ElementDidFocus", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_EnableInspectorNodeSearch", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(INPUT_TYPE_COLOR)
    { "WebPageProxy_EndColorPicker", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(DATALIST_ELEMENT)
    { "WebPageProxy_EndDataListSuggestions", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    { "WebPageProxy_EndDateTimePicker", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(MEDIA_STREAM)
    { "WebPageProxy_EnumerateMediaDevicesForFrame", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_FixedLayoutSizeDidChange", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_FocusFromServiceWorker", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_FocusedElementDidChangeInputMode", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_FocusedFrameChanged", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_GetLoadDecisionForIcon", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(MAC)
    { "WebPageProxy_HandleAcceptsFirstMouse", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_HandleAutoFillButtonClick", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_HandleAutocorrectionContext", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_HandleAutoplayEvent", ReceiverName::WebPageProxy, false, false },
#if ENABLE(DATA_DETECTION)
    { "WebPageProxy_HandleClickForDataDetectionResult", ReceiverName::WebPageProxy, false, false },
#endif
#if HAVE(TRANSLATION_UI_SERVICES) && ENABLE(CONTEXT_MENUS)
    { "WebPageProxy_HandleContextMenuTranslation", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(DATALIST_ELEMENT)
    { "WebPageProxy_HandleKeydownInDataList", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_HandleMessage", ReceiverName::WebPageProxy, false, false },
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    { "WebPageProxy_HandleMouseDownForModelElement", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_HandleMouseMoveForModelElement", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_HandleMouseUpForModelElement", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_HandleSmartMagnificationInformationForPotentialTap", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_HideInspectorHighlight", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_HideInspectorIndication", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_HidePopupMenu", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(COCOA) || PLATFORM(GTK)
    { "WebPageProxy_HideValidationMessage", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_IgnoreWord", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ImageOrMediaDocumentSizeChanged", ReceiverName::WebPageProxy, false, false },
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    { "WebPageProxy_IsAnyAnimationAllowedToPlayDidChange", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_IsPlayingMediaDidChange", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_LearnWord", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_LogDiagnosticMessageFromWebProcess", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_LogDiagnosticMessageWithDomainFromWebProcess", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_LogDiagnosticMessageWithEnhancedPrivacyFromWebProcess", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_LogDiagnosticMessageWithResultFromWebProcess", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_LogDiagnosticMessageWithValueDictionaryFromWebProcess", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_LogDiagnosticMessageWithValueFromWebProcess", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_LogScrollingEvent", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_MainFramePluginHandlesPageScaleGestureDidChange", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(COCOA)
    { "WebPageProxy_MakeFirstResponder", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    { "WebPageProxy_MockMediaPlaybackTargetPickerDismissPopup", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    { "WebPageProxy_ModelElementAnimationCurrentTime", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ModelElementAnimationDuration", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    { "WebPageProxy_ModelElementCreateRemotePreview", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ModelElementDestroyRemotePreview", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    { "WebPageProxy_ModelElementGetCamera", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ModelElementHasAudio", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ModelElementIsLoopingAnimation", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ModelElementIsMuted", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ModelElementIsPlayingAnimation", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    { "WebPageProxy_ModelElementLoadRemotePreview", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    { "WebPageProxy_ModelElementSetAnimationCurrentTime", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ModelElementSetAnimationIsPlaying", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ModelElementSetCamera", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_IOS)
    { "WebPageProxy_ModelElementSetInteractionEnabled", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    { "WebPageProxy_ModelElementSetIsLoopingAnimation", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ModelElementSetIsMuted", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    { "WebPageProxy_ModelElementSizeDidChange", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ModelInlinePreviewUUIDs", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_MouseDidMoveOverElement", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_NotifyScrollerThumbIsVisibleInRect", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_PageDidScroll", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_PageExtendedBackgroundColorDidChange", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_PageScaleFactorDidChange", ReceiverName::WebPageProxy, false, false },
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    { "WebPageProxy_PlaybackTargetPickerClientStateDidChange", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_PluginScaleFactorDidChange", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_PluginZoomFactorDidChange", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_RecommendedScrollbarStyleDidChange", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(MAC)
    { "WebPageProxy_RecordAutocorrectionResponse", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
    { "WebPageProxy_RegisterAttachmentIdentifier", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_RegisterAttachmentIdentifierFromData", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_RegisterAttachmentIdentifierFromFilePath", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_RegisterAttachmentsFromSerializedData", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_RegisterEditCommandForUndo", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_RegisterInsertionUndoGrouping", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(COCOA)
    { "WebPageProxy_RegisterWebProcessAccessibilityToken", ReceiverName::WebPageProxy, false, false },
#endif
#if USE(DICTATION_ALTERNATIVES)
    { "WebPageProxy_RemoveDictationAlternatives", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(MEDIA_USAGE)
    { "WebPageProxy_RemoveMediaUsageManagerSession", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(PDFKIT_PLUGIN)
    { "WebPageProxy_RemovePDFHUD", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    { "WebPageProxy_RemovePlaybackTargetPickerClient", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
    { "WebPageProxy_RequestAttachmentIcon", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_RequestCheckingOfString", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_RequestCookieConsent", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_RequestGeolocationPermissionForFrame", ReceiverName::WebPageProxy, false, false },
#if ENABLE(ENCRYPTED_MEDIA)
    { "WebPageProxy_RequestMediaKeySystemPermissionForFrame", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_RequestNotificationPermission", ReceiverName::WebPageProxy, false, false },
#if USE(QUICK_LOOK)
    { "WebPageProxy_RequestPasswordForQuickLookDocumentInMainFrame", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(POINTER_LOCK)
    { "WebPageProxy_RequestPointerLock", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_RequestPointerUnlock", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_RequestScrollToRect", ReceiverName::WebPageProxy, false, false },
#if ENABLE(IMAGE_ANALYSIS)
    { "WebPageProxy_RequestTextRecognition", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(MEDIA_STREAM)
    { "WebPageProxy_RequestUserMediaPermissionForFrame", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_RestorePageCenterAndScale", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_RestorePageState", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_RevokeGeolocationAuthorizationToken", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_RunModal", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_RunOpenPanel", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SampledPageTopColorChanged", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_SaveImageToLibrary", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_SaveRecentSearches", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_ScrollingNodeScrollDidEndScroll", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ScrollingNodeScrollWillStartScroll", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPageProxy_SearchTheWeb", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SearchWithSpotlight", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_SendMessageToInspectorFrontend", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPageProxy_SendMessageToWebView", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SendMessageToWebViewWithReply", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_SetCanShortCircuitHorizontalWheelEvents", ReceiverName::WebPageProxy, false, false },
#if ENABLE(INPUT_TYPE_COLOR)
    { "WebPageProxy_SetColorPickerColor", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_SetCursor", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SetCursorHiddenUntilMouseMoves", ReceiverName::WebPageProxy, false, false },
#if ENABLE(DATA_DETECTION)
    { "WebPageProxy_SetDataDetectionResult", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPageProxy_SetEditableElementIsFocused", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_SetFocus", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SetHasActiveAnimatedScrolls", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SetHasExecutedAppBoundBehaviorBeforeNavigation", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SetHasHadSelectionChangesFromUserInteraction", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPageProxy_SetInputMethodState", ReceiverName::WebPageProxy, false, false },
#endif
#if HAVE(TOUCH_BAR)
    { "WebPageProxy_SetIsNeverRichlyEditableForTouchBar", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_SetIsResizable", ReceiverName::WebPageProxy, false, false },
#if HAVE(TOUCH_BAR)
    { "WebPageProxy_SetIsTouchBarUpdateSupressedForHiddenContentEditable", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_SetIsUsingHighPerformanceWebGL", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SetMenuBarIsVisible", ReceiverName::WebPageProxy, false, false },
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    { "WebPageProxy_SetMockMediaPlaybackTargetPickerEnabled", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SetMockMediaPlaybackTargetPickerState", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(VIDEO_PRESENTATION_MODE)
    { "WebPageProxy_SetMockVideoPresentationModeEnabled", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(WEB_AUTHN)
    { "WebPageProxy_SetMockWebAuthenticationConfiguration", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_SetNetworkRequestsInProgress", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(COCOA) && ENABLE(DRAG_SUPPORT)
    { "WebPageProxy_SetPromisedDataForImage", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_SetRenderTreeSize", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SetStatusBarIsVisible", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SetStatusText", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SetTextIndicator", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SetToolbarsAreVisible", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SetWindowFrame", ReceiverName::WebPageProxy, false, false },
#if ENABLE(DEVICE_ORIENTATION)
    { "WebPageProxy_ShouldAllowDeviceOrientationAndMotionAccess", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(INPUT_TYPE_COLOR)
    { "WebPageProxy_ShowColorPicker", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_ShowContactPicker", ReceiverName::WebPageProxy, false, false },
#if ENABLE(CONTEXT_MENUS)
    { "WebPageProxy_ShowContextMenu", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPageProxy_ShowCorrectionPanel", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_ShowDataDetectorsUIForPositionInformation", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(DATALIST_ELEMENT)
    { "WebPageProxy_ShowDataListSuggestions", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    { "WebPageProxy_ShowDateTimePicker", ReceiverName::WebPageProxy, false, false },
#endif
#if USE(DICTATION_ALTERNATIVES)
    { "WebPageProxy_ShowDictationAlternativeUI", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(GTK)
    { "WebPageProxy_ShowEmojiPicker", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_ShowInspectorHighlight", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ShowInspectorIndication", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS) && USE(UICONTEXTMENU)
    { "WebPageProxy_ShowMediaControlsContextMenu", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_ShowPage", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY) || ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    { "WebPageProxy_ShowPlaybackTargetPicker", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_ShowPopupMenu", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_ShowShareSheet", ReceiverName::WebPageProxy, false, false },
#if (ENABLE(TELEPHONE_NUMBER_DETECTION) && PLATFORM(MAC))
    { "WebPageProxy_ShowTelephoneNumberMenu", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK)
    { "WebPageProxy_ShowValidationMessage", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPageProxy_Speak", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(SPEECH_SYNTHESIS)
    { "WebPageProxy_SpeechSynthesisCancel", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SpeechSynthesisPause", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SpeechSynthesisResetState", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SpeechSynthesisResume", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SpeechSynthesisSetFinishedCallback", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_SpeechSynthesisSpeak", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(APPLE_PAY_AMS_UI)
    { "WebPageProxy_StartApplePayAMSUISession", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(COCOA) && ENABLE(DRAG_SUPPORT) || PLATFORM(GTK) && ENABLE(DRAG_SUPPORT)
    { "WebPageProxy_StartDrag", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_StartURLSchemeTask", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(COCOA)
    { "WebPageProxy_StopSpeaking", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_StopURLSchemeTask", ReceiverName::WebPageProxy, false, false },
#if ENABLE(APP_HIGHLIGHTS)
    { "WebPageProxy_StoreAppHighlight", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_TakeFocus", ReceiverName::WebPageProxy, false, false },
#if ENABLE(ARKIT_INLINE_PREVIEW_IOS)
    { "WebPageProxy_TakeModelElementFullscreen", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_ThemeColorChanged", ReceiverName::WebPageProxy, false, false },
#if HAVE(TOUCH_BAR)
    { "WebPageProxy_TouchBarMenuDataChanged", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_TouchBarMenuItemDataAdded", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_TouchBarMenuItemDataRemoved", ReceiverName::WebPageProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_UpdateInputContextAfterBlurringAndRefocusingElement", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(MEDIA_USAGE)
    { "WebPageProxy_UpdateMediaUsageManagerSessionState", ReceiverName::WebPageProxy, false, false },
#endif
#if ENABLE(PDFKIT_PLUGIN)
    { "WebPageProxy_UpdatePDFHUDLocation", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_UpdateRemoteFrameSize", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_UpdateSpellingUIWithGrammarString", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_UpdateSpellingUIWithMisspelledWord", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_UpdateStringForFind", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_UseFixedLayoutDidChange", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_WillGoToBackForwardListItem", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_WillPerformClientRedirectForFrame", ReceiverName::WebPageProxy, false, false },
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    { "WebPageProxy_WillReceiveEditDragSnapshot", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPageProxy_WillSubmitForm", ReceiverName::WebPageProxy, false, false },
#if (ENABLE(ATTACHMENT_ELEMENT) && PLATFORM(IOS_FAMILY))
    { "WebPageProxy_WritePromisedAttachmentToPasteboard", ReceiverName::WebPageProxy, false, false },
#endif
#if USE(AUTOMATIC_TEXT_REPLACEMENT)
    { "WebPageProxy_toggleAutomaticDashSubstitution", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_toggleAutomaticLinkDetection", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_toggleAutomaticQuoteSubstitution", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_toggleAutomaticTextReplacement", ReceiverName::WebPageProxy, false, false },
    { "WebPageProxy_toggleSmartInsertDelete", ReceiverName::WebPageProxy, false, false },
#endif
    { "WebPage_AccessibilitySettingsDidChange", ReceiverName::WebPage, false, false },
    { "WebPage_AddConsoleMessage", ReceiverName::WebPage, false, false },
#if PLATFORM(COCOA)
    { "WebPage_AddDictationAlternative", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_AddLayerForFindOverlay", ReceiverName::WebPage, false, false },
    { "WebPage_AddMIMETypeWithCustomContentProvider", ReceiverName::WebPage, false, false },
    { "WebPage_AdvanceToNextMisspelling", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_ApplicationDidBecomeActive", ReceiverName::WebPage, false, false },
    { "WebPage_ApplicationDidEnterBackground", ReceiverName::WebPage, false, false },
    { "WebPage_ApplicationDidEnterBackgroundForMedia", ReceiverName::WebPage, false, false },
    { "WebPage_ApplicationDidFinishSnapshottingAfterEnteringBackground", ReceiverName::WebPage, false, false },
    { "WebPage_ApplicationWillEnterForeground", ReceiverName::WebPage, false, false },
    { "WebPage_ApplicationWillEnterForegroundForMedia", ReceiverName::WebPage, false, false },
    { "WebPage_ApplicationWillResignActive", ReceiverName::WebPage, false, false },
    { "WebPage_ApplyAutocorrection", ReceiverName::WebPage, false, false },
    { "WebPage_AttemptSyntheticClick", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPage_AttributedSubstringForCharacterRangeAsync", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_AutofillLoginCredentials", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_BeginPrinting", ReceiverName::WebPage, false, false },
    { "WebPage_BeginPrintingDuringDOMPrintOperation", ReceiverName::WebPage, false, true },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_BeginSelectionInDirection", ReceiverName::WebPage, false, false },
    { "WebPage_BlurFocusedElement", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(SPEECH_SYNTHESIS)
    { "WebPage_BoundaryEventOccurred", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_CancelAutoscroll", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPage_CancelComposition", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_CancelPointer", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_CancelPotentialTap", ReceiverName::WebPage, false, false },
#endif
#if USE(APPKIT)
    { "WebPage_CapitalizeWord", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(MEDIA_STREAM)
    { "WebPage_CaptureDevicesChanged", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_CenterSelectionInVisibleArea", ReceiverName::WebPage, false, false },
    { "WebPage_ChangeFont", ReceiverName::WebPage, false, false },
    { "WebPage_ChangeFontAttributes", ReceiverName::WebPage, false, false },
    { "WebPage_ChangeListType", ReceiverName::WebPage, false, false },
    { "WebPage_ChangeSpellingToWord", ReceiverName::WebPage, false, false },
#if PLATFORM(COCOA)
    { "WebPage_CharacterIndexForPointAsync", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_ClearAllDecoratedFoundText", ReceiverName::WebPage, false, false },
#if PLATFORM(COCOA)
    { "WebPage_ClearDictationAlternatives", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "WebPage_ClearLoadedSubresourceDomains", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(NOTIFICATIONS)
    { "WebPage_ClearNotificationPermissionState", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_ClearSelection", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_ClearServiceWorkerEntitlementOverride", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_ClearWheelEventTestMonitor", ReceiverName::WebPage, false, false },
    { "WebPage_Close", ReceiverName::WebPage, false, false },
#if PLATFORM(GTK)
    { "WebPage_CollapseSelectionInFrame", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_CommitPotentialTap", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_CompleteTextManipulation", ReceiverName::WebPage, false, false },
    { "WebPage_ComputePagesForPrinting", ReceiverName::WebPage, false, false },
    { "WebPage_ComputePagesForPrintingDuringDOMPrintOperation", ReceiverName::WebPage, false, true },
#if PLATFORM(COCOA)
    { "WebPage_ConfirmCompositionAsync", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_ConnectInspector", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_ContentSizeCategoryDidChange", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(CONTEXT_MENUS)
    { "WebPage_ContextMenuForKeyEvent", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_CountStringMatches", ReceiverName::WebPage, false, false },
#if ENABLE(APP_HIGHLIGHTS)
    { "WebPage_CreateAppHighlightInSelectedRange", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
    { "WebPage_CreateMediaSessionCoordinator", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_CreateRemoteSubframe", ReceiverName::WebPage, false, false },
#if PLATFORM(MAC)
    { "WebPage_DataDetectorsDidChangeUI", ReceiverName::WebPage, false, false },
    { "WebPage_DataDetectorsDidHideUI", ReceiverName::WebPage, false, false },
    { "WebPage_DataDetectorsDidPresentUI", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_DecorateTextRangeWithStyle", ReceiverName::WebPage, false, false },
    { "WebPage_DecreaseListLevel", ReceiverName::WebPage, false, false },
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPage_DeleteSurrounding", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(DATA_DETECTION)
    { "WebPage_DetectDataInAllFrames", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_DictationAlternativesAtSelection", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(POINTER_LOCK)
    { "WebPage_DidAcquirePointerLock", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_DidBeginTextSearchOperation", ReceiverName::WebPage, false, false },
    { "WebPage_DidCancelCheckingText", ReceiverName::WebPage, false, false },
    { "WebPage_DidCancelForOpenPanel", ReceiverName::WebPage, false, false },
    { "WebPage_DidChangeSelectedIndexForActivePopupMenu", ReceiverName::WebPage, false, false },
#if ENABLE(INPUT_TYPE_COLOR)
    { "WebPage_DidChooseColor", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    { "WebPage_DidChooseDate", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_DidChooseFilesForOpenPanel", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_DidChooseFilesForOpenPanelWithDisplayStringAndIcon", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(DATALIST_ELEMENT)
    { "WebPage_DidCloseSuggestions", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_DidCommitLoadInAnotherProcess", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    { "WebPage_DidConcludeDrop", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(CONTEXT_MENUS)
    { "WebPage_DidDismissContextMenu", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(INPUT_TYPE_COLOR)
    { "WebPage_DidEndColorPicker", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    { "WebPage_DidEndDateTimePicker", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPage_DidEndMagnificationGesture", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_DidEndTextSearchOperation", ReceiverName::WebPage, false, false },
    { "WebPage_DidFinishCheckingText", ReceiverName::WebPage, false, false },
    { "WebPage_DidFinishLoadInAnotherProcess", ReceiverName::WebPage, false, false },
    { "WebPage_DidGetLoadDecisionForIcon", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_DidInsertFinalDictationResult", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(POINTER_LOCK)
    { "WebPage_DidLosePointerLock", ReceiverName::WebPage, false, false },
    { "WebPage_DidNotAcquirePointerLock", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(GEOLOCATION)
    { "WebPage_DidReceiveGeolocationPermissionDecision", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_DidRecognizeLongPress", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_DidRemoveBackForwardItem", ReceiverName::WebPage, false, false },
    { "WebPage_DidRemoveEditCommand", ReceiverName::WebPage, false, false },
#if ENABLE(DATALIST_ELEMENT)
    { "WebPage_DidSelectDataListOption", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(CONTEXT_MENUS)
    { "WebPage_DidSelectItemFromActiveContextMenu", ReceiverName::WebPage, false, false },
    { "WebPage_DidShowContextMenu", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(DRAG_SUPPORT)
    { "WebPage_DidStartDrag", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_DisconnectInspector", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_DispatchWheelEventWithoutScrolling", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(DRAG_SUPPORT)
    { "WebPage_DragCancelled", ReceiverName::WebPage, false, false },
    { "WebPage_DragEnded", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(GTK)
    { "WebPage_DrawPagesForPrinting", ReceiverName::WebPage, false, false },
    { "WebPage_DrawPagesForPrintingDuringDOMPrintOperation", ReceiverName::WebPage, false, true },
#endif
#if PLATFORM(COCOA)
    { "WebPage_DrawPagesToPDF", ReceiverName::WebPage, false, false },
    { "WebPage_DrawPagesToPDFDuringDOMPrintOperation", ReceiverName::WebPage, false, true },
    { "WebPage_DrawRectToImage", ReceiverName::WebPage, false, false },
    { "WebPage_DrawRectToImageDuringDOMPrintOperation", ReceiverName::WebPage, false, true },
#endif
#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
    { "WebPage_DrawToImage", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_DrawToPDF", ReceiverName::WebPage, false, false },
#endif
#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
    { "WebPage_DrawToPDFiOS", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_DynamicViewportSizeUpdate", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_EffectiveAppearanceDidChange", ReceiverName::WebPage, false, false },
    { "WebPage_EndPrinting", ReceiverName::WebPage, false, false },
    { "WebPage_EndPrintingDuringDOMPrintOperation", ReceiverName::WebPage, false, true },
    { "WebPage_EnqueueSecurityPolicyViolationEvent", ReceiverName::WebPage, false, false },
    { "WebPage_ExecuteEditCommand", ReceiverName::WebPage, false, false },
    { "WebPage_ExecuteEditCommandWithCallback", ReceiverName::WebPage, false, false },
#if ENABLE(SANDBOX_EXTENSIONS)
    { "WebPage_ExtendSandboxForFilesFromOpenPanel", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_ExtendSelection", ReceiverName::WebPage, false, false },
    { "WebPage_ExtendSelectionForReplacement", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(GTK)
    { "WebPage_FailedToShowPopupMenu", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_FindRectsForStringMatches", ReceiverName::WebPage, false, false },
    { "WebPage_FindString", ReceiverName::WebPage, false, false },
    { "WebPage_FindStringMatches", ReceiverName::WebPage, false, false },
    { "WebPage_FindTextRangesForStringMatches", ReceiverName::WebPage, false, false },
#if PLATFORM(COCOA)
    { "WebPage_FirstRectForCharacterRangeAsync", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_FlushDeferredDidReceiveMouseEvent", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_FocusNextFocusedElement", ReceiverName::WebPage, false, false },
    { "WebPage_FocusTextInputContextAndPlaceCaret", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_ForceRepaint", ReceiverName::WebPage, false, false },
    { "WebPage_FrameWasRemovedInAnotherProcess", ReceiverName::WebPage, false, false },
    { "WebPage_FreezeLayerTreeDueToSwipeAnimation", ReceiverName::WebPage, false, false },
#if ENABLE(GAMEPAD)
    { "WebPage_GamepadActivity", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_GenerateSyntheticEditingCommand", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_GenerateTestReport", ReceiverName::WebPage, false, false },
    { "WebPage_GetAccessibilityTreeData", ReceiverName::WebPage, false, false },
#if ENABLE(APPLICATION_MANIFEST)
    { "WebPage_GetApplicationManifest", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_GetBytecodeProfile", ReceiverName::WebPage, false, false },
#if PLATFORM(COCOA)
    { "WebPage_GetContentsAsAttributedString", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(MHTML)
    { "WebPage_GetContentsAsMHTMLData", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_GetContentsAsString", ReceiverName::WebPage, false, false },
    { "WebPage_GetFrameInfo", ReceiverName::WebPage, false, false },
    { "WebPage_GetFrameTree", ReceiverName::WebPage, false, false },
    { "WebPage_GetImageForFindMatch", ReceiverName::WebPage, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "WebPage_GetLoadedSubresourceDomains", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_GetMainResourceDataOfFrame", ReceiverName::WebPage, false, false },
#if PLATFORM(COCOA)
    { "WebPage_GetMarkedRangeAsync", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_GetPDFFirstPageSize", ReceiverName::WebPage, false, false },
    { "WebPage_GetProcessDisplayName", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_GetRectsAtSelectionOffsetWithText", ReceiverName::WebPage, false, false },
    { "WebPage_GetRectsForGranularityWithSelectionOffset", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_GetRenderTreeExternalRepresentation", ReceiverName::WebPage, false, false },
    { "WebPage_GetResourceDataFromFrame", ReceiverName::WebPage, false, false },
    { "WebPage_GetSamplingProfilerOutput", ReceiverName::WebPage, false, false },
#if PLATFORM(COCOA)
    { "WebPage_GetSelectedRangeAsync", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_GetSelectionAsWebArchiveData", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_GetSelectionContext", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_GetSelectionOrContentsAsString", ReceiverName::WebPage, false, false },
    { "WebPage_GetSourceForFrame", ReceiverName::WebPage, false, false },
    { "WebPage_GetTextFragmentMatch", ReceiverName::WebPage, false, false },
    { "WebPage_GetWebArchiveOfFrame", ReceiverName::WebPage, false, false },
    { "WebPage_GoToBackForwardItem", ReceiverName::WebPage, false, false },
#if PLATFORM(MAC)
    { "WebPage_HandleAcceptedCandidate", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_HandleAlternativeTextUIResult", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_HandleAutocorrectionContextRequest", ReceiverName::WebPage, false, false },
    { "WebPage_HandleDoubleTapForDoubleClickAtPoint", ReceiverName::WebPage, false, false },
    { "WebPage_HandleTwoFingerTapAtPoint", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_HandleWheelEvent", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_HardwareKeyboardAvailabilityChanged", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_HasMarkedText", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_HideFindIndicator", ReceiverName::WebPage, false, false },
    { "WebPage_HideFindUI", ReceiverName::WebPage, false, false },
#if PLATFORM(MAC)
    { "WebPage_ImmediateActionDidCancel", ReceiverName::WebPage, false, false },
    { "WebPage_ImmediateActionDidComplete", ReceiverName::WebPage, false, false },
    { "WebPage_ImmediateActionDidUpdate", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_IncreaseListLevel", ReceiverName::WebPage, false, false },
    { "WebPage_IndicateFindMatch", ReceiverName::WebPage, false, false },
#if ENABLE(ATTACHMENT_ELEMENT)
    { "WebPage_InsertAttachment", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_InsertDictatedTextAsync", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    { "WebPage_InsertDroppedImagePlaceholders", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_InsertTextAsync", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_InsertTextPlaceholder", ReceiverName::WebPage, false, false },
    { "WebPage_InspectorNodeSearchEndedAtPosition", ReceiverName::WebPage, false, false },
    { "WebPage_InspectorNodeSearchMovedToPosition", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_IsLayerTreeFrozen", ReceiverName::WebPage, false, false },
    { "WebPage_KeyEvent", ReceiverName::WebPage, false, false },
    { "WebPage_LastNavigationWasAppInitiated", ReceiverName::WebPage, false, false },
    { "WebPage_ListenForLayoutMilestones", ReceiverName::WebPage, false, false },
    { "WebPage_LoadAlternateHTML", ReceiverName::WebPage, false, false },
    { "WebPage_LoadData", ReceiverName::WebPage, false, false },
    { "WebPage_LoadDataInFrame", ReceiverName::WebPage, false, false },
    { "WebPage_LoadRequest", ReceiverName::WebPage, false, false },
    { "WebPage_LoadRequestWaitingForProcessLaunch", ReceiverName::WebPage, false, false },
    { "WebPage_LoadSimulatedRequestAndResponse", ReceiverName::WebPage, false, false },
    { "WebPage_LoadURLInFrame", ReceiverName::WebPage, false, false },
#if USE(APPKIT)
    { "WebPage_LowercaseWord", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(ENCRYPTED_MEDIA)
    { "WebPage_MediaKeySystemWasDenied", ReceiverName::WebPage, false, false },
    { "WebPage_MediaKeySystemWasGranted", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_IOS)
    { "WebPage_ModelInlinePreviewDidFailToLoad", ReceiverName::WebPage, false, false },
    { "WebPage_ModelInlinePreviewDidLoad", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_MouseEvent", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_MoveSelectionAtBoundaryWithDirection", ReceiverName::WebPage, false, false },
    { "WebPage_MoveSelectionByOffset", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_NavigateServiceWorkerClient", ReceiverName::WebPage, false, false },
    { "WebPage_NavigateToPDFLinkWithSimulatedClick", ReceiverName::WebPage, false, false },
    { "WebPage_NotifyReportObservers", ReceiverName::WebPage, false, false },
    { "WebPage_NotifyUserScripts", ReceiverName::WebPage, false, false },
#if ENABLE(PDFKIT_PLUGIN)
    { "WebPage_OpenPDFWithPreview", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    { "WebPage_PauseAllAnimations", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_PauseAllMediaPlayback", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_PerformActionOnElement", ReceiverName::WebPage, false, false },
    { "WebPage_PerformActionOnElements", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_PerformDictionaryLookupAtLocation", ReceiverName::WebPage, false, false },
    { "WebPage_PerformDictionaryLookupOfCurrentSelection", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(GTK) && ENABLE(DRAG_SUPPORT) || !PLATFORM(GTK) && ENABLE(DRAG_SUPPORT)
    { "WebPage_PerformDragControllerAction", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_PerformHitTestForMouseEvent", ReceiverName::WebPage, false, false },
#if PLATFORM(MAC)
    { "WebPage_PerformImmediateActionHitTestAtLocation", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    { "WebPage_PlayAllAnimations", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    { "WebPage_PlaybackTargetAvailabilityDidChange", ReceiverName::WebPage, false, false },
    { "WebPage_PlaybackTargetPickerWasDismissed", ReceiverName::WebPage, false, false },
    { "WebPage_PlaybackTargetSelected", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_PostInjectedBundleMessage", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_PotentialTapAtPosition", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_PreferencesDidChange", ReceiverName::WebPage, false, false },
    { "WebPage_PreferencesDidChangeDuringDOMPrintOperation", ReceiverName::WebPage, false, true },
#if (PLATFORM(IOS_FAMILY) && ENABLE(REVEAL))
    { "WebPage_PrepareSelectionForContextMenuWithLocationInView", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_ReapplyEditCommand", ReceiverName::WebPage, true, false },
#if PLATFORM(COCOA)
    { "WebPage_RegisterUIProcessAccessibilityTokens", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_RegisterURLSchemeHandler", ReceiverName::WebPage, false, false },
    { "WebPage_Reload", ReceiverName::WebPage, false, false },
#if ENABLE(DATA_DETECTION)
    { "WebPage_RemoveDataDetectedLinks", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_RemoveLayerForFindOverlay", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_RemoveTextPlaceholder", ReceiverName::WebPage, false, false },
    { "WebPage_ReplaceDictatedText", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_ReplaceFoundTextRangeWithString", ReceiverName::WebPage, false, false },
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    { "WebPage_ReplaceImageForRemoveBackground", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_ReplaceMatches", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_ReplaceSelectedText", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_ReplaceSelectionWithPasteboardData", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPage_RequestAcceptsFirstMouse", ReceiverName::WebPage, false, true },
#endif
#if PLATFORM(COCOA)
    { "WebPage_RequestActiveNowPlayingSessionInfo", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    { "WebPage_RequestAdditionalItemsForDragSession", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_RequestAutocorrectionData", ReceiverName::WebPage, false, false },
    { "WebPage_RequestDictationContext", ReceiverName::WebPage, false, false },
    { "WebPage_RequestDocumentEditingContext", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    { "WebPage_RequestDragStart", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_RequestEvasionRectsAboveSelection", ReceiverName::WebPage, false, false },
    { "WebPage_RequestFocusedElementInformation", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_RequestFontAttributesAtSelectionStart", ReceiverName::WebPage, false, false },
    { "WebPage_RequestImageBitmap", ReceiverName::WebPage, false, false },
    { "WebPage_RequestMediaPlaybackState", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_RequestPositionInformation", ReceiverName::WebPage, false, false },
#endif
#if (PLATFORM(IOS_FAMILY) && ENABLE(REVEAL))
    { "WebPage_RequestRVItemInCurrentSelectedRange", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_RequestRectForFoundTextRange", ReceiverName::WebPage, false, false },
#if ENABLE(IOS_TOUCH_EVENTS)
    { "WebPage_ResetPotentialTapSecurityOrigin", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(APP_HIGHLIGHTS)
    { "WebPage_RestoreAppHighlightsAndScrollToIndex", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_RestoreSelectionInFocusedEditableElement", ReceiverName::WebPage, false, false },
    { "WebPage_RestoreSession", ReceiverName::WebPage, false, false },
    { "WebPage_Resume", ReceiverName::WebPage, false, false },
    { "WebPage_ResumeActiveDOMObjectsAndAnimations", ReceiverName::WebPage, false, false },
    { "WebPage_ResumeAllMediaPlayback", ReceiverName::WebPage, false, false },
    { "WebPage_RunJavaScriptInFrameInScriptWorld", ReceiverName::WebPage, false, false },
#if ENABLE(PDFKIT_PLUGIN)
    { "WebPage_SavePDF", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_ScalePage", ReceiverName::WebPage, false, false },
    { "WebPage_ScalePageInViewCoordinates", ReceiverName::WebPage, false, false },
    { "WebPage_ScaleView", ReceiverName::WebPage, false, false },
    { "WebPage_ScheduleFullEditorStateUpdate", ReceiverName::WebPage, false, false },
    { "WebPage_ScrollBy", ReceiverName::WebPage, false, false },
    { "WebPage_ScrollTextRangeToVisible", ReceiverName::WebPage, false, false },
    { "WebPage_ScrollToRect", ReceiverName::WebPage, false, false },
    { "WebPage_SelectAll", ReceiverName::WebPage, false, false },
    { "WebPage_SelectFindMatch", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SelectPositionAtBoundaryWithDirection", ReceiverName::WebPage, false, false },
    { "WebPage_SelectPositionAtPoint", ReceiverName::WebPage, false, false },
    { "WebPage_SelectTextWithGranularityAtPoint", ReceiverName::WebPage, false, false },
    { "WebPage_SelectWithGesture", ReceiverName::WebPage, false, false },
    { "WebPage_SelectWithTwoTouches", ReceiverName::WebPage, false, false },
    { "WebPage_SelectWordBackward", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPage_SemanticContextDidChange", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SendMessageToTargetBackend", ReceiverName::WebPage, false, false },
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPage_SendMessageToWebProcessExtension", ReceiverName::WebPage, false, false },
    { "WebPage_SendMessageToWebProcessExtensionWithReply", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SendReportToEndpoints", ReceiverName::WebPage, false, false },
#if HAVE(APP_ACCENT_COLORS)
    { "WebPage_SetAccentColor", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetActivityState", ReceiverName::WebPage, false, false },
#if ENABLE(ADVANCED_PRIVACY_PROTECTIONS)
    { "WebPage_SetAllowedQueryParametersForAdvancedPrivacyProtections", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SetAllowsMediaDocumentInlinePlayback", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetAlwaysShowsHorizontalScroller", ReceiverName::WebPage, false, false },
    { "WebPage_SetAlwaysShowsVerticalScroller", ReceiverName::WebPage, false, false },
#if ENABLE(APP_HIGHLIGHTS)
    { "WebPage_SetAppHighlightsVisibility", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetAutoSizingShouldExpandToViewHeight", ReceiverName::WebPage, false, false },
    { "WebPage_SetBackgroundColor", ReceiverName::WebPage, false, false },
    { "WebPage_SetBackgroundExtendsBeyondPage", ReceiverName::WebPage, false, false },
    { "WebPage_SetBaseWritingDirection", ReceiverName::WebPage, false, false },
    { "WebPage_SetCanRunBeforeUnloadConfirmPanel", ReceiverName::WebPage, false, false },
    { "WebPage_SetCanRunModal", ReceiverName::WebPage, false, false },
    { "WebPage_SetCanShowPlaceholder", ReceiverName::WebPage, false, false },
    { "WebPage_SetCanUseCredentialStorage", ReceiverName::WebPage, false, false },
#if PLATFORM(MAC)
    { "WebPage_SetCaretAnimatorType", ReceiverName::WebPage, false, false },
    { "WebPage_SetCaretBlinkingSuspended", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_SetCompositionAsync", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetControlledByAutomation", ReceiverName::WebPage, false, false },
    { "WebPage_SetCurrentHistoryItemForReattach", ReceiverName::WebPage, false, false },
    { "WebPage_SetCustomTextEncodingName", ReceiverName::WebPage, false, false },
    { "WebPage_SetDefaultUnobscuredSize", ReceiverName::WebPage, false, false },
    { "WebPage_SetDefersLoading", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SetDeviceOrientation", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetEditable", ReceiverName::WebPage, false, false },
    { "WebPage_SetEnableHorizontalRubberBanding", ReceiverName::WebPage, false, false },
    { "WebPage_SetEnableVerticalRubberBanding", ReceiverName::WebPage, false, false },
    { "WebPage_SetFixedLayoutSize", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SetFocusedElementSelectedIndex", ReceiverName::WebPage, false, false },
    { "WebPage_SetFocusedElementValue", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPage_SetFooterBannerHeight", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SetForceAlwaysUserScalable", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetGapBetweenPages", ReceiverName::WebPage, false, false },
    { "WebPage_SetHasResourceLoadClient", ReceiverName::WebPage, false, false },
#if PLATFORM(MAC)
    { "WebPage_SetHeaderBannerHeight", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(REMOTE_INSPECTOR)
    { "WebPage_SetIndicating", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetInitialFocus", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SetInsertionPointColor", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
    { "WebPage_SetInteractionRegionsEnabled", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SetIsShowingInputViewForFocusedElement", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetIsSuspended", ReceiverName::WebPage, false, false },
    { "WebPage_SetIsTakingSnapshotsForApplicationSuspension", ReceiverName::WebPage, false, false },
#if HAVE(UIKIT_RESIZABLE_WINDOWS)
    { "WebPage_SetIsWindowResizingEnabled", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetLayerHostingMode", ReceiverName::WebPage, false, false },
#if ENABLE(ADVANCED_PRIVACY_PROTECTIONS)
    { "WebPage_SetLinkDecorationFilteringData", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_SetMainFrameIsScrollable", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetMaximumUnobscuredSize", ReceiverName::WebPage, false, false },
    { "WebPage_SetMayStartMediaWhenInWindow", ReceiverName::WebPage, false, false },
    { "WebPage_SetMediaVolume", ReceiverName::WebPage, false, false },
    { "WebPage_SetMinimumSizeForAutoLayout", ReceiverName::WebPage, false, false },
    { "WebPage_SetMinimumUnobscuredSize", ReceiverName::WebPage, false, false },
#if (ENABLE(MEDIA_STREAM) && USE(GSTREAMER))
    { "WebPage_SetMockCaptureDevicesInterrupted", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetMuted", ReceiverName::WebPage, false, false },
    { "WebPage_SetNeedsDOMWindowResizeEvent", ReceiverName::WebPage, false, false },
    { "WebPage_SetNeedsFontAttributes", ReceiverName::WebPage, false, false },
#if (ENABLE(MEDIA_STREAM) && USE(GSTREAMER))
    { "WebPage_SetOrientationForMediaCapture", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetOverriddenMediaType", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SetOverrideViewportArguments", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetPageAndTextZoomFactors", ReceiverName::WebPage, false, false },
    { "WebPage_SetPageLength", ReceiverName::WebPage, false, false },
    { "WebPage_SetPageZoomFactor", ReceiverName::WebPage, false, false },
    { "WebPage_SetPaginationBehavesLikeColumns", ReceiverName::WebPage, false, false },
    { "WebPage_SetPaginationMode", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SetScreenIsBeingCaptured", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetScrollPinningBehavior", ReceiverName::WebPage, false, false },
    { "WebPage_SetScrollbarOverlayStyle", ReceiverName::WebPage, false, false },
    { "WebPage_SetShouldDispatchFakeMouseMoveEvents", ReceiverName::WebPage, false, false },
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    { "WebPage_SetShouldPlayToPlaybackTarget", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SetShouldRevealCurrentSelectionAfterInsertion", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetShouldScaleViewToFitDocument", ReceiverName::WebPage, false, false },
    { "WebPage_SetSizeToContentAutoSizeMaximumSize", ReceiverName::WebPage, false, false },
#if PLATFORM(COCOA)
    { "WebPage_SetSmartInsertDeleteEnabled", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetSuppressScrollbarAnimations", ReceiverName::WebPage, false, false },
#if PLATFORM(COCOA)
    { "WebPage_SetTextAsync", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetTextForActivePopupMenu", ReceiverName::WebPage, false, false },
    { "WebPage_SetTextZoomFactor", ReceiverName::WebPage, false, false },
    { "WebPage_SetTopContentInset", ReceiverName::WebPage, false, false },
#if PLATFORM(COCOA)
    { "WebPage_SetTopContentInsetFenced", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetUnderPageBackgroundColorOverride", ReceiverName::WebPage, false, false },
    { "WebPage_SetUnderlayColor", ReceiverName::WebPage, false, false },
    { "WebPage_SetUseFixedLayout", ReceiverName::WebPage, false, false },
    { "WebPage_SetUseIconLoadingClient", ReceiverName::WebPage, false, false },
#if PLATFORM(MAC)
    { "WebPage_SetUseSystemAppearance", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetUserAgent", ReceiverName::WebPage, false, false },
    { "WebPage_SetUserInterfaceLayoutDirection", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SetViewportConfigurationViewLayoutSize", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SetViewportSizeForCSSViewportUnits", ReceiverName::WebPage, false, false },
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    { "WebPage_ShouldAllowRemoveBackground", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_SimulateDeviceOrientationChange", ReceiverName::WebPage, false, false },
#if ENABLE(SPEECH_SYNTHESIS)
    { "WebPage_SpeakingErrorOccurred", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_StartAutoscrollAtPosition", ReceiverName::WebPage, false, false },
    { "WebPage_StartInteractionWithElementContextOrPosition", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_StartTextManipulations", ReceiverName::WebPage, false, false },
#if ENABLE(IMAGE_ANALYSIS)
    { "WebPage_StartVisualTranslation", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_StopInteraction", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_StopLoading", ReceiverName::WebPage, false, false },
    { "WebPage_StopLoadingDueToProcessSwap", ReceiverName::WebPage, false, false },
    { "WebPage_StopMediaCapture", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_StoreSelectionForAccessibility", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_Suspend", ReceiverName::WebPage, false, false },
    { "WebPage_SuspendActiveDOMObjectsAndAnimations", ReceiverName::WebPage, false, false },
    { "WebPage_SuspendAllMediaPlayback", ReceiverName::WebPage, false, false },
#if USE(SYSTEM_PREVIEW)
    { "WebPage_SystemPreviewActionTriggered", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_TakeSnapshot", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_TapHighlightAtPosition", ReceiverName::WebPage, false, false },
    { "WebPage_TextInputContextsInRect", ReceiverName::WebPage, false, false },
#endif
#if !ENABLE(IOS_TOUCH_EVENTS) && ENABLE(TOUCH_EVENTS)
    { "WebPage_TouchEvent", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_TouchWithIdentifierWasRemoved", ReceiverName::WebPage, false, false },
    { "WebPage_TransitionFrameToLocal", ReceiverName::WebPage, false, false },
    { "WebPage_TryClose", ReceiverName::WebPage, false, false },
    { "WebPage_TryRestoreScrollPosition", ReceiverName::WebPage, false, false },
    { "WebPage_URLSchemeTaskDidComplete", ReceiverName::WebPage, false, false },
    { "WebPage_URLSchemeTaskDidPerformRedirection", ReceiverName::WebPage, false, false },
    { "WebPage_URLSchemeTaskDidReceiveData", ReceiverName::WebPage, false, false },
    { "WebPage_URLSchemeTaskDidReceiveResponse", ReceiverName::WebPage, false, false },
    { "WebPage_URLSchemeTaskWillPerformRedirection", ReceiverName::WebPage, false, false },
    { "WebPage_UnapplyEditCommand", ReceiverName::WebPage, true, false },
    { "WebPage_UnfreezeLayerTreeDueToSwipeAnimation", ReceiverName::WebPage, false, false },
#if ENABLE(ATTACHMENT_ELEMENT)
    { "WebPage_UpdateAttachmentAttributes", ReceiverName::WebPage, false, false },
    { "WebPage_UpdateAttachmentIcon", ReceiverName::WebPage, false, false },
    { "WebPage_UpdateAttachmentThumbnail", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_UpdateBackForwardListForReattach", ReceiverName::WebPage, false, false },
    { "WebPage_UpdateCORSDisablingPatterns", ReceiverName::WebPage, false, false },
    { "WebPage_UpdateCurrentModifierState", ReceiverName::WebPage, false, false },
    { "WebPage_UpdateFrameSize", ReceiverName::WebPage, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_UpdateSelectionWithDelta", ReceiverName::WebPage, false, false },
    { "WebPage_UpdateSelectionWithExtentPoint", ReceiverName::WebPage, false, false },
    { "WebPage_UpdateSelectionWithExtentPointAndBoundary", ReceiverName::WebPage, false, false },
    { "WebPage_UpdateSelectionWithTouches", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_UpdateWebsitePolicies", ReceiverName::WebPage, false, false },
#if ENABLE(IMAGE_ANALYSIS)
    { "WebPage_UpdateWithTextRecognitionResult", ReceiverName::WebPage, false, false },
#endif
#if USE(APPKIT)
    { "WebPage_UppercaseWord", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_UseRedirectionForCurrentNavigation", ReceiverName::WebPage, false, false },
#if ENABLE(MEDIA_STREAM)
    { "WebPage_UserMediaAccessWasDenied", ReceiverName::WebPage, false, false },
    { "WebPage_UserMediaAccessWasGranted", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_ValidateCommand", ReceiverName::WebPage, false, false },
    { "WebPage_ViewWillEndLiveResize", ReceiverName::WebPage, false, false },
    { "WebPage_ViewWillStartLiveResize", ReceiverName::WebPage, false, false },
#if ENABLE(SPEECH_SYNTHESIS)
    { "WebPage_VoicesDidChange", ReceiverName::WebPage, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "WebPage_WasLoadedWithDataTransferFromPrevalentResource", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_WillInsertFinalDictationResult", ReceiverName::WebPage, false, false },
    { "WebPage_WillStartUserTriggeredZooming", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_WindowAndViewFramesChanged", ReceiverName::WebPage, false, false },
#endif
    { "WebPage_WindowScreenDidChange", ReceiverName::WebPage, false, false },
#if ENABLE(PDFKIT_PLUGIN)
    { "WebPage_ZoomPDFIn", ReceiverName::WebPage, false, false },
    { "WebPage_ZoomPDFOut", ReceiverName::WebPage, false, false },
#endif
#if PLATFORM(GTK)
    { "WebPasteboardProxy_ClearClipboard", ReceiverName::WebPasteboardProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPasteboardProxy_UpdateSupportedTypeIdentifiers", ReceiverName::WebPasteboardProxy, false, false },
    { "WebPasteboardProxy_WriteImageToPasteboard", ReceiverName::WebPasteboardProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY) || USE(LIBWPE)
    { "WebPasteboardProxy_WriteStringToPasteboard", ReceiverName::WebPasteboardProxy, false, false },
#endif
#if PLATFORM(GTK)
    { "WebPasteboardProxy_WriteToClipboard", ReceiverName::WebPasteboardProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPasteboardProxy_WriteURLToPasteboard", ReceiverName::WebPasteboardProxy, false, false },
#endif
#if PLATFORM(IOS_FAMILY) || USE(LIBWPE)
    { "WebPasteboardProxy_WriteWebContentToPasteboard", ReceiverName::WebPasteboardProxy, false, false },
#endif
    { "WebPermissionControllerProxy_Query", ReceiverName::WebPermissionControllerProxy, false, false },
    { "WebPermissionController_permissionChanged", ReceiverName::WebPermissionController, false, false },
    { "WebProcessPool_HandleMessage", ReceiverName::WebProcessPool, false, false },
#if ENABLE(GAMEPAD)
    { "WebProcessPool_PlayGamepadEffect", ReceiverName::WebProcessPool, false, false },
#endif
    { "WebProcessPool_ReportWebContentCPUTime", ReceiverName::WebProcessPool, false, false },
#if ENABLE(GAMEPAD)
    { "WebProcessPool_StartedUsingGamepads", ReceiverName::WebProcessPool, false, false },
    { "WebProcessPool_StopGamepadEffects", ReceiverName::WebProcessPool, false, false },
    { "WebProcessPool_StoppedUsingGamepads", ReceiverName::WebProcessPool, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebProcessProxy_CacheMediaMIMETypes", ReceiverName::WebProcessProxy, false, false },
#endif
#if ENABLE(GPU_PROCESS)
    { "WebProcessProxy_CreateGPUProcessConnection", ReceiverName::WebProcessProxy, true, false },
#endif
    { "WebProcessProxy_CreateSpeechRecognitionServer", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_DestroySpeechRecognitionServer", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_DidCollectPrewarmInformation", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_DidDestroyFrame", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_DidDestroyUserGestureToken", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_DidExceedActiveMemoryLimit", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_DidExceedCPULimit", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_DidExceedInactiveMemoryLimit", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_DidReceiveBackgroundResponsivenessPing", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_DisableSuddenTermination", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_EnableSuddenTermination", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_GetNotifications", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_MemoryPressureStatusChanged", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_PostMessageToRemote", ReceiverName::WebProcessProxy, false, false },
#if PLATFORM(MAC)
    { "WebProcessProxy_ReleaseHighPerformanceGPU", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_RequestHighPerformanceGPU", ReceiverName::WebProcessProxy, false, false },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebProcessProxy_SendMessageToWebContext", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_SendMessageToWebContextWithReply", ReceiverName::WebProcessProxy, false, false },
#endif
    { "WebProcessProxy_SetAppBadge", ReceiverName::WebProcessProxy, false, false },
#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
    { "WebProcessProxy_SetCaptionDisplayMode", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_SetCaptionLanguage", ReceiverName::WebProcessProxy, false, false },
#endif
    { "WebProcessProxy_SetClientBadge", ReceiverName::WebProcessProxy, false, false },
#if HAVE(CVDISPLAYLINK)
    { "WebProcessProxy_SetDisplayLinkPreferredFramesPerSecond", ReceiverName::WebProcessProxy, false, false },
#endif
    { "WebProcessProxy_SetIsHoldingLockedFiles", ReceiverName::WebProcessProxy, false, false },
#if HAVE(CVDISPLAYLINK)
    { "WebProcessProxy_StartDisplayLink", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_StopDisplayLink", ReceiverName::WebProcessProxy, false, false },
#endif
    { "WebProcessProxy_StopResponsivenessTimer", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_SystemBeep", ReceiverName::WebProcessProxy, false, false },
    { "WebProcessProxy_UpdateBackForwardItem", ReceiverName::WebProcessProxy, false, false },
#if PLATFORM(COCOA)
    { "WebProcess_AccessibilityPreferencesDidChange", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_AddAllowedFirstPartyForCookies", ReceiverName::WebProcess, false, false },
#if ENABLE(MEDIA_STREAM)
    { "WebProcess_AddMockMediaDevice", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_BackgroundResponsivenessPing", ReceiverName::WebProcess, false, false },
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
    { "WebProcess_BacklightLevelDidChange", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_ClearCachedPage", ReceiverName::WebProcess, false, false },
    { "WebProcess_ClearCurrentModifierStateForTesting", ReceiverName::WebProcess, false, false },
#if ENABLE(MEDIA_STREAM)
    { "WebProcess_ClearMockMediaDevices", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_ClearResourceLoadStatistics", ReceiverName::WebProcess, false, false },
#if PLATFORM(MAC) || PLATFORM(MACCATALYST)
    { "WebProcess_ColorPreferencesDidChange", ReceiverName::WebProcess, false, false },
#endif
#if HAVE(AUDIO_COMPONENT_SERVER_REGISTRATIONS)
    { "WebProcess_ConsumeAudioComponentRegistrations", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_CreateWebPage", ReceiverName::WebProcess, false, false },
    { "WebProcess_DeleteAllCookies", ReceiverName::WebProcess, false, false },
    { "WebProcess_DeleteWebsiteData", ReceiverName::WebProcess, false, false },
    { "WebProcess_DeleteWebsiteDataForOrigin", ReceiverName::WebProcess, false, false },
    { "WebProcess_DeleteWebsiteDataForOrigins", ReceiverName::WebProcess, false, false },
    { "WebProcess_DestroyAutomationSessionProxy", ReceiverName::WebProcess, false, false },
#if PLATFORM(COCOA)
    { "WebProcess_DidWriteToPasteboardAsynchronously", ReceiverName::WebProcess, false, false },
    { "WebProcess_DisableURLSchemeCheckInDataDetectors", ReceiverName::WebProcess, false, false },
#endif
#if PLATFORM(MAC)
    { "WebProcess_DisplayConfigurationChanged", ReceiverName::WebProcess, false, false },
#endif
#if HAVE(CVDISPLAYLINK)
    { "WebProcess_DisplayDidRefresh", ReceiverName::WebProcess, false, false },
#endif
#if (PLATFORM(COCOA) && ENABLE(REMOTE_INSPECTOR))
    { "WebProcess_EnableRemoteWebInspector", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_EnsureAutomationSessionProxy", ReceiverName::WebProcess, false, false },
    { "WebProcess_EstablishRemoteWorkerContextConnectionToNetworkProcess", ReceiverName::WebProcess, false, false },
    { "WebProcess_FetchWebsiteData", ReceiverName::WebProcess, false, false },
    { "WebProcess_FullKeyboardAccessModeChanged", ReceiverName::WebProcess, false, false },
#if ENABLE(GAMEPAD)
    { "WebProcess_GamepadConnected", ReceiverName::WebProcess, false, false },
    { "WebProcess_GamepadDisconnected", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_GarbageCollectJavaScriptObjects", ReceiverName::WebProcess, false, false },
    { "WebProcess_GetActivePagesOriginsForTesting", ReceiverName::WebProcess, false, false },
    { "WebProcess_GrantAccessToAssetServices", ReceiverName::WebProcess, false, false },
#if (ENABLE(MEDIA_STREAM) && ENABLE(SANDBOX_EXTENSIONS))
    { "WebProcess_GrantUserMediaDeviceSandboxExtensions", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_HandleInjectedBundleMessage", ReceiverName::WebProcess, false, false },
    { "WebProcess_InitializeWebProcess", ReceiverName::WebProcess, false, false },
    { "WebProcess_IsJITEnabled", ReceiverName::WebProcess, false, false },
    { "WebProcess_MarkIsNoLongerPrewarmed", ReceiverName::WebProcess, false, false },
#if (PLATFORM(COCOA) && ENABLE(CFPREFS_DIRECT_MODE))
    { "WebProcess_NotifyPreferencesChanged", ReceiverName::WebProcess, false, false },
#endif
#if PLATFORM(MAC)
    { "WebProcess_OpenDirectoryCacheInvalidated", ReceiverName::WebProcess, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebProcess_PowerSourceDidChange", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_PrepareToSuspend", ReceiverName::WebProcess, false, false },
    { "WebProcess_PrewarmWithDomainInformation", ReceiverName::WebProcess, false, false },
    { "WebProcess_ProcessDidResume", ReceiverName::WebProcess, false, false },
    { "WebProcess_RegisterURLSchemeAsBypassingContentSecurityPolicy", ReceiverName::WebProcess, false, false },
    { "WebProcess_RegisterURLSchemeAsCORSEnabled", ReceiverName::WebProcess, false, false },
    { "WebProcess_RegisterURLSchemeAsCachePartitioned", ReceiverName::WebProcess, false, false },
    { "WebProcess_RegisterURLSchemeAsCanDisplayOnlyIfCanRequest", ReceiverName::WebProcess, false, false },
    { "WebProcess_RegisterURLSchemeAsDisplayIsolated", ReceiverName::WebProcess, false, false },
    { "WebProcess_RegisterURLSchemeAsEmptyDocument", ReceiverName::WebProcess, false, false },
    { "WebProcess_RegisterURLSchemeAsLocal", ReceiverName::WebProcess, false, false },
    { "WebProcess_RegisterURLSchemeAsNoAccess", ReceiverName::WebProcess, false, false },
    { "WebProcess_RegisterURLSchemeAsSecure", ReceiverName::WebProcess, false, false },
    { "WebProcess_ReleaseMemory", ReceiverName::WebProcess, false, false },
    { "WebProcess_ReloadExecutionContextsForOrigin", ReceiverName::WebProcess, false, false },
    { "WebProcess_RemotePostMessage", ReceiverName::WebProcess, false, false },
#if ENABLE(MEDIA_STREAM)
    { "WebProcess_RemoveMockMediaDevice", ReceiverName::WebProcess, false, false },
    { "WebProcess_ResetMockMediaDevices", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_RevokeAccessToAssetServices", ReceiverName::WebProcess, false, false },
#if (ENABLE(MEDIA_STREAM) && ENABLE(SANDBOX_EXTENSIONS))
    { "WebProcess_RevokeUserMediaDeviceSandboxExtensions", ReceiverName::WebProcess, false, false },
#endif
#if PLATFORM(MAC)
    { "WebProcess_ScrollerStylePreferenceChanged", ReceiverName::WebProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "WebProcess_SeedResourceLoadStatisticsForTesting", ReceiverName::WebProcess, false, false },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebProcess_SendMessageToWebProcessExtension", ReceiverName::WebProcess, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "WebProcess_SendResourceLoadStatisticsDataImmediately", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_SetAlwaysUsesComplexTextCodePath", ReceiverName::WebProcess, false, false },
    { "WebProcess_SetBackForwardCacheCapacity", ReceiverName::WebProcess, false, false },
    { "WebProcess_SetCacheModel", ReceiverName::WebProcess, false, false },
    { "WebProcess_SetDefaultRequestTimeoutInterval", ReceiverName::WebProcess, false, false },
    { "WebProcess_SetDisableFontSubpixelAntialiasingForTesting", ReceiverName::WebProcess, false, false },
    { "WebProcess_SetDomainRelaxationForbiddenForURLScheme", ReceiverName::WebProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "WebProcess_SetDomainsWithCrossPageStorageAccess", ReceiverName::WebProcess, false, false },
    { "WebProcess_SetDomainsWithUserInteraction", ReceiverName::WebProcess, false, false },
#endif
#if ENABLE(SERVICE_CONTROLS)
    { "WebProcess_SetEnabledServices", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_SetEnhancedAccessibility", ReceiverName::WebProcess, false, false },
#if HAVE(MOUSE_DEVICE_OBSERVATION)
    { "WebProcess_SetHasMouseDevice", ReceiverName::WebProcess, false, false },
#endif
#if HAVE(STYLUS_DEVICE_OBSERVATION)
    { "WebProcess_SetHasStylusDevice", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_SetHasSuspendedPageProxy", ReceiverName::WebProcess, false, false },
    { "WebProcess_SetHiddenPageDOMTimerThrottlingIncreaseLimit", ReceiverName::WebProcess, false, false },
#if ENABLE(GAMEPAD)
    { "WebProcess_SetInitialGamepads", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_SetInjectedBundleParameter", ReceiverName::WebProcess, false, false },
    { "WebProcess_SetInjectedBundleParameters", ReceiverName::WebProcess, false, false },
    { "WebProcess_SetIsInProcessCache", ReceiverName::WebProcess, false, false },
    { "WebProcess_SetJavaScriptGarbageCollectorTimerEnabled", ReceiverName::WebProcess, false, false },
#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
    { "WebProcess_SetMediaAccessibilityPreferences", ReceiverName::WebProcess, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebProcess_SetMediaMIMETypes", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_SetMemoryCacheDisabled", ReceiverName::WebProcess, false, false },
#if ENABLE(MEDIA_STREAM)
    { "WebProcess_SetMockMediaDeviceIsEphemeral", ReceiverName::WebProcess, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebProcess_SetScreenProperties", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_SetTextCheckerState", ReceiverName::WebProcess, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "WebProcess_SetThirdPartyCookieBlockingMode", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_SetTrackingPreventionEnabled", ReceiverName::WebProcess, false, false },
#if PLATFORM(GTK) && !USE(GTK4)
    { "WebProcess_SetUseSystemAppearanceForScrollbars", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_SetWebsiteDataStoreParameters", ReceiverName::WebProcess, false, false },
    { "WebProcess_StartMemorySampler", ReceiverName::WebProcess, false, false },
    { "WebProcess_StopMemorySampler", ReceiverName::WebProcess, false, false },
    { "WebProcess_SwitchFromStaticFontRegistryToUserFontRegistry", ReceiverName::WebProcess, false, false },
#if PLATFORM(MAC)
    { "WebProcess_SystemDidWake", ReceiverName::WebProcess, false, false },
    { "WebProcess_SystemWillPowerOn", ReceiverName::WebProcess, false, false },
    { "WebProcess_SystemWillSleep", ReceiverName::WebProcess, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebProcess_UnblockServicesRequiredByAccessibility", ReceiverName::WebProcess, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebProcess_UserInterfaceIdiomDidChange", ReceiverName::WebProcess, false, false },
#endif
    { "WebProcess_UserPreferredLanguagesChanged", ReceiverName::WebProcess, false, false },
    { "WebRTCMonitor_NetworksChanged", ReceiverName::WebRTCMonitor, false, false },
    { "WebRTCResolver_ResolvedAddressError", ReceiverName::WebRTCResolver, false, false },
    { "WebRTCResolver_SetResolvedAddress", ReceiverName::WebRTCResolver, false, false },
#if ENABLE(CONTENT_FILTERING)
    { "WebResourceLoader_ContentFilterDidBlockLoad", ReceiverName::WebResourceLoader, false, false },
#endif
    { "WebResourceLoader_DidBlockAuthenticationChallenge", ReceiverName::WebResourceLoader, false, false },
    { "WebResourceLoader_DidFailResourceLoad", ReceiverName::WebResourceLoader, false, false },
    { "WebResourceLoader_DidFailServiceWorkerLoad", ReceiverName::WebResourceLoader, false, false },
    { "WebResourceLoader_DidFinishResourceLoad", ReceiverName::WebResourceLoader, false, false },
    { "WebResourceLoader_DidReceiveData", ReceiverName::WebResourceLoader, false, false },
#if ENABLE(SHAREABLE_RESOURCE)
    { "WebResourceLoader_DidReceiveResource", ReceiverName::WebResourceLoader, false, false },
#endif
    { "WebResourceLoader_DidReceiveResponse", ReceiverName::WebResourceLoader, false, false },
    { "WebResourceLoader_DidSendData", ReceiverName::WebResourceLoader, false, false },
    { "WebResourceLoader_ServiceWorkerDidNotHandle", ReceiverName::WebResourceLoader, false, false },
    { "WebResourceLoader_SetWorkerStart", ReceiverName::WebResourceLoader, false, false },
    { "WebResourceLoader_StopLoadingAfterXFrameOptionsOrContentSecurityPolicyDenied", ReceiverName::WebResourceLoader, false, false },
    { "WebResourceLoader_WillSendRequest", ReceiverName::WebResourceLoader, false, false },
    { "WebSWClientConnection_FireUpdateFoundEvent", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_FocusServiceWorkerClient", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_JobRejectedInServer", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_NotifyClientsOfControllerChange", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_NotifyRecordResponseBodyChunk", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_NotifyRecordResponseBodyEnd", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_PostMessageToServiceWorkerClient", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_RegistrationJobResolvedInServer", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_SetRegistrationLastUpdateTime", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_SetRegistrationUpdateViaCache", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_SetSWOriginTableIsImported", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_SetSWOriginTableSharedMemory", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_SetServiceWorkerClientIsControlled", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_StartScriptFetchForServer", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_UpdateBackgroundFetchRegistration", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_UpdateRegistrationState", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWClientConnection_UpdateWorkerState", ReceiverName::WebSWClientConnection, false, false },
    { "WebSWContextManagerConnection_CancelFetch", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_Close", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_ContinueDidReceiveFetchResponse", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_ConvertFetchToDownload", ReceiverName::WebSWContextManagerConnection, false, false },
#if ENABLE(SHAREABLE_RESOURCE) && PLATFORM(COCOA)
    { "WebSWContextManagerConnection_DidSaveScriptsToDisk", ReceiverName::WebSWContextManagerConnection, false, false },
#endif
    { "WebSWContextManagerConnection_FireActivateEvent", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_FireBackgroundFetchClickEvent", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_FireBackgroundFetchEvent", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_FireInstallEvent", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_FireNotificationEvent", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_FirePushEvent", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_InstallServiceWorker", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_MatchAllCompleted", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_NavigationPreloadFailed", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_NavigationPreloadIsReady", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_PostMessageToServiceWorker", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_SetThrottleState", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_SetUserAgent", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_SkipWaitingCompleted", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_StartFetch", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_TerminateWorker", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_UpdateAppInitiatedValue", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWContextManagerConnection_UpdatePreferencesStore", ReceiverName::WebSWContextManagerConnection, false, false },
    { "WebSWServerConnection_AbortBackgroundFetch", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_AddServiceWorkerRegistrationInServer", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_BackgroundFetchIdentifiers", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_BackgroundFetchInformation", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_DidResolveRegistrationPromise", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_DisableNavigationPreload", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_EnableNavigationPreload", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_FinishFetchingScriptInServer", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_GetNavigationPreloadState", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_GetPushPermissionState", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_GetPushSubscription", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_GetRegistrations", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_MatchBackgroundFetch", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_MatchRegistration", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_PostMessageToServiceWorker", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_RegisterServiceWorkerClient", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_RemoveServiceWorkerRegistrationInServer", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_RetrieveRecordResponse", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_RetrieveRecordResponseBody", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_ScheduleJobInServer", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_ScheduleUnregisterJobInServer", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_SetNavigationPreloadHeaderValue", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_SetThrottleState", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_StartBackgroundFetch", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_StoreRegistrationsOnDisk", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_SubscribeToPushService", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_TerminateWorkerFromClient", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_UnregisterServiceWorkerClient", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_UnsubscribeFromPushService", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_WhenRegistrationReady", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerConnection_WhenServiceWorkerIsTerminatedForTesting", ReceiverName::WebSWServerConnection, false, false },
    { "WebSWServerToContextConnection_Claim", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_DidFailHeartBeatCheck", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_DidFinishActivation", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_DidFinishInstall", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_FindClientByVisibleIdentifier", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_Focus", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_MatchAll", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_Navigate", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_OpenWindow", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_PostMessageToServiceWorkerClient", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_ReportConsoleMessage", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_ScriptContextFailedToStart", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_ScriptContextStarted", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_SetAsInspected", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_SetScriptResource", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_SetServiceWorkerHasPendingEvents", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_SkipWaiting", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebSWServerToContextConnection_WorkerTerminated", ReceiverName::WebSWServerToContextConnection, false, false },
    { "WebScreenOrientationManagerProxy_Lock", ReceiverName::WebScreenOrientationManagerProxy, false, false },
    { "WebScreenOrientationManagerProxy_SetShouldSendChangeNotification", ReceiverName::WebScreenOrientationManagerProxy, false, false },
    { "WebScreenOrientationManagerProxy_Unlock", ReceiverName::WebScreenOrientationManagerProxy, false, false },
    { "WebScreenOrientationManager_OrientationDidChange", ReceiverName::WebScreenOrientationManager, false, false },
    { "WebSharedWorkerContextManagerConnection_Close", ReceiverName::WebSharedWorkerContextManagerConnection, false, false },
    { "WebSharedWorkerContextManagerConnection_LaunchSharedWorker", ReceiverName::WebSharedWorkerContextManagerConnection, false, false },
    { "WebSharedWorkerContextManagerConnection_PostConnectEvent", ReceiverName::WebSharedWorkerContextManagerConnection, false, false },
    { "WebSharedWorkerContextManagerConnection_ResumeSharedWorker", ReceiverName::WebSharedWorkerContextManagerConnection, false, false },
    { "WebSharedWorkerContextManagerConnection_SetUserAgent", ReceiverName::WebSharedWorkerContextManagerConnection, false, false },
    { "WebSharedWorkerContextManagerConnection_SuspendSharedWorker", ReceiverName::WebSharedWorkerContextManagerConnection, false, false },
    { "WebSharedWorkerContextManagerConnection_TerminateSharedWorker", ReceiverName::WebSharedWorkerContextManagerConnection, false, false },
    { "WebSharedWorkerContextManagerConnection_UpdatePreferencesStore", ReceiverName::WebSharedWorkerContextManagerConnection, false, false },
    { "WebSharedWorkerObjectConnection_FetchScriptInClient", ReceiverName::WebSharedWorkerObjectConnection, false, false },
    { "WebSharedWorkerObjectConnection_NotifyWorkerObjectOfLoadCompletion", ReceiverName::WebSharedWorkerObjectConnection, false, false },
    { "WebSharedWorkerObjectConnection_PostExceptionToWorkerObject", ReceiverName::WebSharedWorkerObjectConnection, false, false },
    { "WebSharedWorkerServerConnection_RequestSharedWorker", ReceiverName::WebSharedWorkerServerConnection, false, false },
    { "WebSharedWorkerServerConnection_ResumeForBackForwardCache", ReceiverName::WebSharedWorkerServerConnection, false, false },
    { "WebSharedWorkerServerConnection_SharedWorkerObjectIsGoingAway", ReceiverName::WebSharedWorkerServerConnection, false, false },
    { "WebSharedWorkerServerConnection_SuspendForBackForwardCache", ReceiverName::WebSharedWorkerServerConnection, false, false },
    { "WebSharedWorkerServerToContextConnection_PostExceptionToWorkerObject", ReceiverName::WebSharedWorkerServerToContextConnection, false, false },
    { "WebSharedWorkerServerToContextConnection_SharedWorkerTerminated", ReceiverName::WebSharedWorkerServerToContextConnection, false, false },
    { "WebSocketChannel_DidClose", ReceiverName::WebSocketChannel, false, false },
    { "WebSocketChannel_DidConnect", ReceiverName::WebSocketChannel, false, false },
    { "WebSocketChannel_DidReceiveBinaryData", ReceiverName::WebSocketChannel, false, false },
    { "WebSocketChannel_DidReceiveHandshakeResponse", ReceiverName::WebSocketChannel, false, false },
    { "WebSocketChannel_DidReceiveMessageError", ReceiverName::WebSocketChannel, false, false },
    { "WebSocketChannel_DidReceiveText", ReceiverName::WebSocketChannel, false, false },
    { "WebSocketChannel_DidSendHandshakeRequest", ReceiverName::WebSocketChannel, false, false },
    { "WebSpeechRecognitionConnection_DidReceiveUpdate", ReceiverName::WebSpeechRecognitionConnection, false, false },
    { "WebUserContentControllerProxy_DidPostMessage", ReceiverName::WebUserContentControllerProxy, false, false },
#if ENABLE(CONTENT_EXTENSIONS)
    { "WebUserContentController_AddContentRuleLists", ReceiverName::WebUserContentController, false, false },
#endif
    { "WebUserContentController_AddContentWorlds", ReceiverName::WebUserContentController, false, false },
    { "WebUserContentController_AddUserScriptMessageHandlers", ReceiverName::WebUserContentController, false, false },
    { "WebUserContentController_AddUserScripts", ReceiverName::WebUserContentController, false, false },
    { "WebUserContentController_AddUserStyleSheets", ReceiverName::WebUserContentController, false, false },
#if ENABLE(CONTENT_EXTENSIONS)
    { "WebUserContentController_RemoveAllContentRuleLists", ReceiverName::WebUserContentController, false, false },
#endif
    { "WebUserContentController_RemoveAllUserScriptMessageHandlers", ReceiverName::WebUserContentController, false, false },
    { "WebUserContentController_RemoveAllUserScriptMessageHandlersForWorlds", ReceiverName::WebUserContentController, false, false },
    { "WebUserContentController_RemoveAllUserScripts", ReceiverName::WebUserContentController, false, false },
    { "WebUserContentController_RemoveAllUserStyleSheets", ReceiverName::WebUserContentController, false, false },
#if ENABLE(CONTENT_EXTENSIONS)
    { "WebUserContentController_RemoveContentRuleList", ReceiverName::WebUserContentController, false, false },
#endif
    { "WebUserContentController_RemoveContentWorlds", ReceiverName::WebUserContentController, false, false },
    { "WebUserContentController_RemoveUserScript", ReceiverName::WebUserContentController, false, false },
    { "WebUserContentController_RemoveUserScriptMessageHandler", ReceiverName::WebUserContentController, false, false },
    { "WebUserContentController_RemoveUserStyleSheet", ReceiverName::WebUserContentController, false, false },
#if PLATFORM(COCOA)
    { "InitializeConnection", ReceiverName::IPC, false, false },
#endif
    { "LegacySessionState", ReceiverName::IPC, false, false },
    { "ProcessOutOfStreamMessage", ReceiverName::IPC, false, false },
    { "SetStreamDestinationID", ReceiverName::IPC, false, false },
    { "SyncMessageReply", ReceiverName::IPC, false, false },
    { "AuxiliaryProcess_MainThreadPingReply", ReceiverName::AsyncReply, false, false },
    { "CacheStorageEngineConnection_CachesReply", ReceiverName::AsyncReply, false, false },
    { "CacheStorageEngineConnection_ClearMemoryRepresentationReply", ReceiverName::AsyncReply, false, false },
    { "CacheStorageEngineConnection_DeleteMatchingRecordsReply", ReceiverName::AsyncReply, false, false },
    { "CacheStorageEngineConnection_EngineRepresentationReply", ReceiverName::AsyncReply, false, false },
    { "CacheStorageEngineConnection_OpenReply", ReceiverName::AsyncReply, false, false },
    { "CacheStorageEngineConnection_PutRecordsReply", ReceiverName::AsyncReply, false, false },
    { "CacheStorageEngineConnection_RemoveReply", ReceiverName::AsyncReply, false, false },
    { "CacheStorageEngineConnection_RetrieveRecordsReply", ReceiverName::AsyncReply, false, false },
    { "DownloadProxy_DecideDestinationWithSuggestedFilenameReply", ReceiverName::AsyncReply, false, false },
    { "DownloadProxy_WillSendRequestReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(COCOA)
    { "DrawingArea_DispatchAfterEnsuringDrawingReply", ReceiverName::AsyncReply, false, false },
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER) || PLATFORM(COCOA)
    { "DrawingArea_UpdateGeometryReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(IOS_TOUCH_EVENTS)
    { "EventDispatcher_TouchEventReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(ROUTING_ARBITRATION)
    { "GPUProcessConnection_BeginRoutingArbitrationWithCategoryReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
    { "GPUProcessProxy_StatusBarWasTappedReply", ReceiverName::AsyncReply, false, false },
#endif
    { "GPUProcess_CreateGPUConnectionToWebProcessReply", ReceiverName::AsyncReply, false, false },
    { "GPUProcess_PrepareToSuspendReply", ReceiverName::AsyncReply, false, false },
#if HAVE(SCREEN_CAPTURE_KIT)
    { "GPUProcess_PromptForGetDisplayMediaReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(VIDEO)
    { "GPUProcess_RequestBitmapImageForCurrentTimeReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(MEDIA_STREAM)
    { "GPUProcess_UpdateCaptureAccessReply", ReceiverName::AsyncReply, false, false },
#endif
    { "GPUProcess_WebProcessConnectionCountForTestingReply", ReceiverName::AsyncReply, false, false },
    { "IPCStreamTester_AsyncMessageReply", ReceiverName::AsyncReply, false, false },
    { "IPCTesterReceiver_AsyncMessageReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(IOS_FAMILY)
    { "MediaPlayerPrivateRemote_GetRawCookiesReply", ReceiverName::AsyncReply, false, false },
#endif
    { "MediaPlayerPrivateRemote_SendH2PingReply", ReceiverName::AsyncReply, false, false },
    { "MediaSourcePrivateRemote_MediaSourcePrivateShuttingDownReply", ReceiverName::AsyncReply, false, false },
    { "NetworkBroadcastChannelRegistry_PostMessageReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(WEB_RTC)
    { "NetworkConnectionToWebProcess_ConnectToRTCDataChannelRemoteSourceReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkConnectionToWebProcess_CookiesForDOMAsyncReply", ReceiverName::AsyncReply, false, false },
    { "NetworkConnectionToWebProcess_CreateRTCProviderReply", ReceiverName::AsyncReply, false, false },
    { "NetworkConnectionToWebProcess_DeleteCookieReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkConnectionToWebProcess_EstablishSWContextConnectionReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkConnectionToWebProcess_EstablishSharedWorkerContextConnectionReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(MAC)
    { "NetworkConnectionToWebProcess_GetProcessDisplayNameReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkConnectionToWebProcess_HasStorageAccessReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkConnectionToWebProcess_IsResourceLoadFinishedReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkConnectionToWebProcess_RequestStorageAccessReply", ReceiverName::AsyncReply, false, false },
    { "NetworkConnectionToWebProcess_ResourceLoadStatisticsUpdatedReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkConnectionToWebProcess_SendH2PingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkConnectionToWebProcess_SetCookieFromDOMAsyncReply", ReceiverName::AsyncReply, false, false },
    { "NetworkConnectionToWebProcess_TakeAllMessagesForPortReply", ReceiverName::AsyncReply, false, false },
    { "NetworkConnectionToWebProcess_WriteBlobsToTemporaryFilesForIndexedDBReply", ReceiverName::AsyncReply, false, false },
    { "NetworkMDNSRegister_RegisterMDNSNameReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(WEB_RTC)
    { "NetworkProcessConnection_ConnectToRTCDataChannelRemoteSourceReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcessProxy_DataTaskDidReceiveResponseReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcessProxy_DataTaskReceivedChallengeReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcessProxy_DataTaskWillPerformHTTPRedirectionReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcessProxy_DeleteWebsiteDataInUIProcessForRegistrableDomainsReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcessProxy_DeleteWebsiteDataInWebProcessesForOriginReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcessProxy_EstablishRemoteWorkerContextConnectionToNetworkProcessReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(APP_BOUND_DOMAINS)
    { "NetworkProcessProxy_GetAppBoundDomainsReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(APPLE_PAY_REMOTE_UI_USES_SCENE)
    { "NetworkProcessProxy_GetWindowSceneIdentifierForPaymentPresentationReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcessProxy_NavigateServiceWorkerClientReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcessProxy_OpenWindowFromServiceWorkerReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcessProxy_ReloadExecutionContextsForOriginReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcessProxy_RequestBackgroundFetchPermissionReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcessProxy_RequestStorageAccessConfirmReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcessProxy_RequestStorageSpaceReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcessProxy_SetDomainsWithCrossPageStorageAccessReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcessProxy_TriggerBrowsingContextGroupSwitchForNavigationReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_AbortBackgroundFetchReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_AddAllowedFirstPartyForCookiesReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(COCOA)
    { "NetworkProcess_AppPrivacyReportTestingDataReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_CancelDownloadReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(APP_BOUND_DOMAINS)
    { "NetworkProcess_ClearAppBoundSessionReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(COCOA)
    { "NetworkProcess_ClearAppPrivacyReportTestingDataReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_ClearBundleIdentifierReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_ClearPrevalentResourceReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_ClearPrivateClickMeasurementReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
    { "NetworkProcess_ClearServiceWorkerEntitlementOverrideReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_ClearUserInteractionReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_ClickBackgroundFetchReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_CloseITPDatabaseReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_ClosePCMDatabaseReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_CountNonDefaultSessionSetsReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_CreateNetworkConnectionToWebProcessReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_DataTaskWithRequestReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_DeleteCookiesForTestingReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_DeletePushAndNotificationRegistrationReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_DeleteWebsiteDataForOriginsReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_DeleteWebsiteDataReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_DestroySessionReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_DomainIDExistsInDatabaseReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_DumpPrivateClickMeasurementReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_DumpResourceLoadStatisticsReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_FetchWebsiteDataReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_FlushCookiesReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_GetAllBackgroundFetchIdentifiersReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_GetAllStorageAccessEntriesReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_GetBackgroundFetchStateReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_GetOriginsWithPushAndNotificationPermissionsReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_GetPendingPushMessagesReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_GetResourceLoadStatisticsDataSummaryReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_HadUserInteractionReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(APP_BOUND_DOMAINS)
    { "NetworkProcess_HasAppBoundSessionReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_HasIsolatedSessionReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_HasLocalStorageReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_HasPushSubscriptionForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_InitializeNetworkProcessReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_InsertExpiredStatisticForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_IsGrandfatheredReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_IsPrevalentResourceReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_IsRegisteredAsRedirectingToReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_IsRegisteredAsSubFrameUnderReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_IsRegisteredAsSubresourceUnderReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_IsRelationshipOnlyInDatabaseOnceReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_IsResourceLoadStatisticsEphemeralReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_IsVeryPrevalentResourceReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_LogUserInteractionReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_MarkAttributedPrivateClickMeasurementsAsExpiredForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_MarkPrivateClickMeasurementsAsExpiredForTestingReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_MergeStatisticForTestingReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_PauseBackgroundFetchReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_PrepareToSuspendReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_ProcessNotificationEventReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_ProcessPushMessageReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_RenameOriginInWebsiteDataReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_ResetCacheMaxAgeCapForPrevalentResourcesReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_ResetCrossSiteLoadsWithLinkDecorationForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_ResetParametersToDefaultValuesReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_ResetQuotaReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_ResetStoragePersistedStateReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(SERVICE_WORKER)
    { "NetworkProcess_ResumeBackgroundFetchReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_ScheduleClearInMemoryAndPersistentReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_ScheduleCookieBlockingUpdateReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_ScheduleStatisticsAndDataRecordsProcessingReply", ReceiverName::AsyncReply, false, false },
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(APP_BOUND_DOMAINS))
    { "NetworkProcess_SetAppBoundDomainsForResourceLoadStatisticsReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "NetworkProcess_SetBackupExclusionPeriodForTestingReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetCacheMaxAgeCapForPrevalentResourcesReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetCrossSiteLoadWithLinkDecorationForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetFirstPartyHostCNAMEDomainForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetFirstPartyWebsiteDataRemovalModeForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetGrandfatheredReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetGrandfatheringTimeReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetIsRunningResourceLoadStatisticsTestReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetLastSeenReply", ReceiverName::AsyncReply, false, false },
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(MANAGED_DOMAINS))
    { "NetworkProcess_SetManagedDomainsForResourceLoadStatisticsReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetMaxStatisticsEntriesReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetMinimumTimeBetweenDataRecordsRemovalReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetNotifyPagesWhenDataRecordsWereScannedReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_SetPCMFraudPreventionValuesForTestingReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetPrevalentResourceForDebugModeReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetPrevalentResourceReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_SetPrivateClickMeasurementAppBundleIDForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetPrivateClickMeasurementAttributionReportURLsForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetPrivateClickMeasurementEphemeralMeasurementForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetPrivateClickMeasurementOverrideTimerForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetPrivateClickMeasurementTokenPublicKeyURLForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetPrivateClickMeasurementTokenSignatureURLForTestingReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetPruneEntriesDownToReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_SetPushAndNotificationsEnabledForOriginReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_SetResourceLoadStatisticsDebugModeReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetResourceLoadStatisticsTimeAdvanceForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetShouldClassifyResourcesBeforeDataRecordsRemovalReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetShouldDowngradeReferrerForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetShouldEnbleSameSiteStrictEnforcementForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetSubframeUnderTopFrameDomainReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetSubresourceUnderTopFrameDomainReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetSubresourceUniqueRedirectFromReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetSubresourceUniqueRedirectToReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetThirdPartyCNAMEDomainForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetThirdPartyCookieBlockingModeReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetTimeToLiveUserInteractionReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetToSameSiteStrictCookiesForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetTopFrameUniqueRedirectFromReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetTopFrameUniqueRedirectToReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SetVeryPrevalentResourceReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_SimulatePrivateClickMeasurementSessionRestartReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_StatisticsDatabaseHasAllTablesReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_StoreServiceWorkerRegistrationsReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_SyncLocalStorageReply", ReceiverName::AsyncReply, false, false },
    { "NetworkProcess_UpdateBundleIdentifierReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "NetworkProcess_UpdatePrevalentDomainsToBlockCookiesForReply", ReceiverName::AsyncReply, false, false },
#endif
    { "NetworkProcess_WebsiteDataOriginDirectoryForTestingReply", ReceiverName::AsyncReply, false, false },
    { "NetworkSocketChannel_SendDataReply", ReceiverName::AsyncReply, false, false },
    { "NetworkSocketChannel_SendStringReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_CacheStorageAllCachesReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_CacheStorageClearMemoryRepresentationReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_CacheStorageOpenCacheReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_CacheStoragePutRecordsReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_CacheStorageRemoveCacheReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_CacheStorageRemoveRecordsReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_CacheStorageRepresentationReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_CacheStorageRetrieveRecordsReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_ClearReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_CloseSyncAccessHandleReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_ConnectToStorageAreaReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_CreateSyncAccessHandleReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_EstimateReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_FileSystemGetDirectoryReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_GetDirectoryHandleReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_GetFileHandleReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_GetFileReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_GetHandleNamesReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_GetHandleReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_IsSameEntryReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_MoveReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_PersistReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_PersistedReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_RemoveEntryReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_RemoveItemReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_RequestNewCapacityForSyncAccessHandleReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_ResolveReply", ReceiverName::AsyncReply, false, false },
    { "NetworkStorageManager_SetItemReply", ReceiverName::AsyncReply, false, false },
    { "NotificationManagerMessageHandler_RequestSystemNotificationPermissionReply", ReceiverName::AsyncReply, false, false },
    { "NotificationManagerMessageHandler_ShowNotificationReply", ReceiverName::AsyncReply, false, false },
    { "PlatformXRSystem_EnumerateImmersiveXRDevicesReply", ReceiverName::AsyncReply, false, false },
    { "PlatformXRSystem_RequestFrameReply", ReceiverName::AsyncReply, false, false },
    { "PlatformXRSystem_RequestPermissionOnSessionFeaturesReply", ReceiverName::AsyncReply, false, false },
    { "RemoteAudioDestinationManager_StartAudioDestinationReply", ReceiverName::AsyncReply, false, false },
    { "RemoteAudioDestinationManager_StopAudioDestinationReply", ReceiverName::AsyncReply, false, false },
    { "RemoteAudioMediaStreamTrackRendererInternalUnitManager_CreateUnitReply", ReceiverName::AsyncReply, false, false },
    { "RemoteBarcodeDetector_DetectReply", ReceiverName::AsyncReply, false, false },
    { "RemoteBuffer_MapAsyncReply", ReceiverName::AsyncReply, false, false },
    { "RemoteCDMInstanceProxy_InitializeWithConfigurationReply", ReceiverName::AsyncReply, false, false },
    { "RemoteCDMInstanceProxy_SetServerCertificateReply", ReceiverName::AsyncReply, false, false },
    { "RemoteCDMInstanceSessionProxy_CloseSessionReply", ReceiverName::AsyncReply, false, false },
    { "RemoteCDMInstanceSessionProxy_LoadSessionReply", ReceiverName::AsyncReply, false, false },
    { "RemoteCDMInstanceSessionProxy_RemoveSessionDataReply", ReceiverName::AsyncReply, false, false },
    { "RemoteCDMInstanceSessionProxy_RequestLicenseReply", ReceiverName::AsyncReply, false, false },
    { "RemoteCDMInstanceSessionProxy_UpdateLicenseReply", ReceiverName::AsyncReply, false, false },
    { "RemoteCDMProxy_GetSupportedConfigurationReply", ReceiverName::AsyncReply, false, false },
    { "RemoteDevice_CreateComputePipelineAsyncReply", ReceiverName::AsyncReply, false, false },
    { "RemoteDevice_CreateRenderPipelineAsyncReply", ReceiverName::AsyncReply, false, false },
    { "RemoteDevice_PopErrorScopeReply", ReceiverName::AsyncReply, false, false },
    { "RemoteFaceDetector_DetectReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaEngineConfigurationFactoryProxy_CreateDecodingConfigurationReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaEngineConfigurationFactoryProxy_CreateEncodingConfigurationReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaPlayerProxy_DidLoadingProgressReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(MEDIA_SOURCE)
    { "RemoteMediaPlayerProxy_LoadMediaSourceReply", ReceiverName::AsyncReply, false, false },
#endif
    { "RemoteMediaPlayerProxy_LoadReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaPlayerProxy_PerformTaskAtMediaTimeReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaPlayerProxy_RequestHostingContextIDReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaRecorderManager_CreateRecorderReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaRecorder_FetchDataReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaRecorder_PauseReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaRecorder_ResumeReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaRecorder_StopRecordingReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaResourceManager_DataReceivedReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaResourceManager_RedirectReceivedReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaResourceManager_ResponseReceivedReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaSessionCoordinatorProxy_CoordinatePauseReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaSessionCoordinatorProxy_CoordinatePlayReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaSessionCoordinatorProxy_CoordinateSeekToReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaSessionCoordinatorProxy_CoordinateSetTrackReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaSessionCoordinatorProxy_JoinReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaSessionCoordinator_PauseSessionReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaSessionCoordinator_PlaySessionReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaSessionCoordinator_SeekSessionToTimeReply", ReceiverName::AsyncReply, false, false },
    { "RemoteMediaSessionCoordinator_SetSessionTrackReply", ReceiverName::AsyncReply, false, false },
    { "RemoteRenderingBackend_GetRemoteBarcodeDetectorSupportedFormatsReply", ReceiverName::AsyncReply, false, false },
    { "RemoteSampleBufferDisplayLayerManager_CreateLayerReply", ReceiverName::AsyncReply, false, false },
    { "RemoteShaderModule_CompilationInfoReply", ReceiverName::AsyncReply, false, false },
    { "RemoteSourceBufferProxy_AppendReply", ReceiverName::AsyncReply, false, false },
    { "RemoteSourceBufferProxy_BufferedSamplesForTrackIdReply", ReceiverName::AsyncReply, false, false },
    { "RemoteSourceBufferProxy_EnqueuedSamplesForTrackIDReply", ReceiverName::AsyncReply, false, false },
    { "RemoteSourceBufferProxy_MemoryPressureReply", ReceiverName::AsyncReply, false, false },
    { "RemoteSourceBufferProxy_RemoveCodedFramesReply", ReceiverName::AsyncReply, false, false },
    { "RemoteTextDetector_DetectReply", ReceiverName::AsyncReply, false, false },
    { "RemoteWebInspectorUIProxy_LoadReply", ReceiverName::AsyncReply, false, false },
    { "RemoteWebInspectorUIProxy_PickColorFromScreenReply", ReceiverName::AsyncReply, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateBufferedChangedReply", ReceiverName::AsyncReply, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveInitializationSegmentReply", ReceiverName::AsyncReply, false, false },
    { "SourceBufferPrivateRemote_SourceBufferPrivateDurationChangedReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_ComputeElementLayoutReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_DeleteCookieReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_GetComputedLabelReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_GetComputedRoleReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_GetCookiesForFrameReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_ResolveChildFrameWithNameReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_ResolveChildFrameWithNodeHandleReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_ResolveChildFrameWithOrdinalReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_ResolveParentFrameReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_SelectOptionElementReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_SetFilesForInputFileUploadReply", ReceiverName::AsyncReply, false, false },
    { "WebAutomationSessionProxy_SnapshotRectForScreenshotReply", ReceiverName::AsyncReply, false, false },
    { "WebBroadcastChannelRegistry_PostMessageToRemoteReply", ReceiverName::AsyncReply, false, false },
    { "WebCookieManager_DeleteAllCookiesModifiedSinceReply", ReceiverName::AsyncReply, false, false },
    { "WebCookieManager_DeleteAllCookiesReply", ReceiverName::AsyncReply, false, false },
    { "WebCookieManager_DeleteCookieReply", ReceiverName::AsyncReply, false, false },
    { "WebCookieManager_DeleteCookiesForHostnamesReply", ReceiverName::AsyncReply, false, false },
    { "WebCookieManager_GetAllCookiesReply", ReceiverName::AsyncReply, false, false },
    { "WebCookieManager_GetCookiesReply", ReceiverName::AsyncReply, false, false },
    { "WebCookieManager_GetHTTPCookieAcceptPolicyReply", ReceiverName::AsyncReply, false, false },
    { "WebCookieManager_GetHostnamesWithCookiesReply", ReceiverName::AsyncReply, false, false },
#if USE(SOUP)
    { "WebCookieManager_ReplaceCookiesReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebCookieManager_SetCookieReply", ReceiverName::AsyncReply, false, false },
    { "WebCookieManager_SetCookiesReply", ReceiverName::AsyncReply, false, false },
    { "WebCookieManager_SetHTTPCookieAcceptPolicyReply", ReceiverName::AsyncReply, false, false },
    { "WebInspectorUIProxy_LoadReply", ReceiverName::AsyncReply, false, false },
    { "WebInspectorUIProxy_PickColorFromScreenReply", ReceiverName::AsyncReply, false, false },
    { "WebLockRegistryProxy_AbortLockRequestReply", ReceiverName::AsyncReply, false, false },
    { "WebLockRegistryProxy_SnapshotReply", ReceiverName::AsyncReply, false, false },
#if USE(SYSTEM_PREVIEW)
    { "WebPageProxy_BeginSystemPreviewReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPageProxy_DecidePolicyForNavigationActionAsyncReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_DecidePolicyForNewWindowActionReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_DecidePolicyForResponseReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(MEDIA_STREAM)
    { "WebPageProxy_EnumerateMediaDevicesForFrameReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPageProxy_FocusFromServiceWorkerReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(ARKIT_INLINE_PREVIEW)
    { "WebPageProxy_ModelElementAnimationCurrentTimeReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_ModelElementAnimationDurationReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    { "WebPageProxy_ModelElementCreateRemotePreviewReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    { "WebPageProxy_ModelElementGetCameraReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_ModelElementHasAudioReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_ModelElementIsLoopingAnimationReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_ModelElementIsMutedReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_ModelElementIsPlayingAnimationReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    { "WebPageProxy_ModelElementLoadRemotePreviewReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    { "WebPageProxy_ModelElementSetAnimationCurrentTimeReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_ModelElementSetAnimationIsPlayingReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_ModelElementSetCameraReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_ModelElementSetIsLoopingAnimationReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_ModelElementSetIsMutedReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    { "WebPageProxy_ModelElementSizeDidChangeReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_ModelInlinePreviewUUIDsReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPageProxy_RequestCookieConsentReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_RequestNotificationPermissionReply", ReceiverName::AsyncReply, false, false },
#if USE(QUICK_LOOK)
    { "WebPageProxy_RequestPasswordForQuickLookDocumentInMainFrameReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(IMAGE_ANALYSIS)
    { "WebPageProxy_RequestTextRecognitionReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPageProxy_SendMessageToWebViewWithReplyReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(DEVICE_ORIENTATION)
    { "WebPageProxy_ShouldAllowDeviceOrientationAndMotionAccessReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPageProxy_ShowContactPickerReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(GTK)
    { "WebPageProxy_ShowEmojiPickerReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS) && USE(UICONTEXTMENU)
    { "WebPageProxy_ShowMediaControlsContextMenuReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPageProxy_ShowShareSheetReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(SPEECH_SYNTHESIS)
    { "WebPageProxy_SpeechSynthesisPauseReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_SpeechSynthesisResumeReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_SpeechSynthesisSetFinishedCallbackReply", ReceiverName::AsyncReply, false, false },
    { "WebPageProxy_SpeechSynthesisSpeakReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(APPLE_PAY_AMS_UI)
    { "WebPageProxy_StartApplePayAMSUISessionReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPageProxy_WillSubmitFormReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(COCOA)
    { "WebPage_AddDictationAlternativeReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_AddLayerForFindOverlayReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_ApplyAutocorrectionReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(MAC)
    { "WebPage_AttributedSubstringForCharacterRangeAsyncReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_BeginSelectionInDirectionReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_CharacterIndexForPointAsyncReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_ClearServiceWorkerEntitlementOverrideReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_CompleteTextManipulationReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_ComputePagesForPrintingDuringDOMPrintOperationReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_ComputePagesForPrintingReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(MEDIA_SESSION_COORDINATOR)
    { "WebPage_CreateMediaSessionCoordinatorReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(DATA_DETECTION)
    { "WebPage_DetectDataInAllFramesReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_DictationAlternativesAtSelectionReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_DidGetLoadDecisionForIconReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_DispatchWheelEventWithoutScrollingReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(GTK)
    { "WebPage_DrawPagesForPrintingDuringDOMPrintOperationReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_DrawPagesForPrintingReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_DrawPagesToPDFDuringDOMPrintOperationReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_DrawPagesToPDFReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_DrawRectToImageDuringDOMPrintOperationReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_DrawRectToImageReply", ReceiverName::AsyncReply, false, false },
#endif
#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
    { "WebPage_DrawToImageReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_DrawToPDFReply", ReceiverName::AsyncReply, false, false },
#endif
#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
    { "WebPage_DrawToPDFiOSReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_EndPrintingDuringDOMPrintOperationReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_EndPrintingReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_ExecuteEditCommandWithCallbackReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_ExtendSelectionForReplacementReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_ExtendSelectionReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_FindRectsForStringMatchesReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_FindStringReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_FindTextRangesForStringMatchesReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(COCOA)
    { "WebPage_FirstRectForCharacterRangeAsyncReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_FocusNextFocusedElementReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_FocusTextInputContextAndPlaceCaretReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_ForceRepaintReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_GetAccessibilityTreeDataReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(APPLICATION_MANIFEST)
    { "WebPage_GetApplicationManifestReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_GetBytecodeProfileReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(COCOA)
    { "WebPage_GetContentsAsAttributedStringReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(MHTML)
    { "WebPage_GetContentsAsMHTMLDataReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_GetContentsAsStringReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_GetFrameInfoReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_GetFrameTreeReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "WebPage_GetLoadedSubresourceDomainsReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_GetMainResourceDataOfFrameReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(COCOA)
    { "WebPage_GetMarkedRangeAsyncReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_GetPDFFirstPageSizeReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_GetProcessDisplayNameReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_GetRectsAtSelectionOffsetWithTextReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_GetRectsForGranularityWithSelectionOffsetReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_GetRenderTreeExternalRepresentationReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_GetResourceDataFromFrameReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_GetSamplingProfilerOutputReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(COCOA)
    { "WebPage_GetSelectedRangeAsyncReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_GetSelectionAsWebArchiveDataReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_GetSelectionContextReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_GetSelectionOrContentsAsStringReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_GetSourceForFrameReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_GetTextFragmentMatchReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_GetWebArchiveOfFrameReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_HandleWheelEventReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(COCOA)
    { "WebPage_HasMarkedTextReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
    { "WebPage_InsertAttachmentReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    { "WebPage_InsertDroppedImagePlaceholdersReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_InsertTextPlaceholderReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_IsLayerTreeFrozenReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_LastNavigationWasAppInitiatedReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_MoveSelectionAtBoundaryWithDirectionReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_MoveSelectionByOffsetReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_NavigateServiceWorkerClientReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(PDFKIT_PLUGIN)
    { "WebPage_OpenPDFWithPreviewReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    { "WebPage_PauseAllAnimationsReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_PauseAllMediaPlaybackReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_PerformActionOnElementReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_PerformHitTestForMouseEventReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    { "WebPage_PlayAllAnimationsReply", ReceiverName::AsyncReply, false, false },
#endif
#if (PLATFORM(IOS_FAMILY) && ENABLE(REVEAL))
    { "WebPage_PrepareSelectionForContextMenuWithLocationInViewReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(DATA_DETECTION)
    { "WebPage_RemoveDataDetectedLinksReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_RemoveLayerForFindOverlayReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_RemoveTextPlaceholderReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_ReplaceMatchesReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(COCOA)
    { "WebPage_RequestActiveNowPlayingSessionInfoReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_RequestAutocorrectionDataReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_RequestDictationContextReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_RequestDocumentEditingContextReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_RequestEvasionRectsAboveSelectionReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_RequestFocusedElementInformationReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_RequestFontAttributesAtSelectionStartReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_RequestImageBitmapReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_RequestMediaPlaybackStateReply", ReceiverName::AsyncReply, false, false },
#if (PLATFORM(IOS_FAMILY) && ENABLE(REVEAL))
    { "WebPage_RequestRVItemInCurrentSelectedRangeReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_RequestRectForFoundTextRangeReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_ResumeAllMediaPlaybackReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_ResumeReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_RunJavaScriptInFrameInScriptWorldReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(PDFKIT_PLUGIN)
    { "WebPage_SavePDFReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SelectPositionAtBoundaryWithDirectionReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_SelectPositionAtPointReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_SelectTextWithGranularityAtPointReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_SelectWithGestureReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_SelectWithTwoTouchesReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebPage_SendMessageToWebProcessExtensionWithReplyReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_SetActivityStateReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_SetInitialFocusReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_SetMutedReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    { "WebPage_ShouldAllowRemoveBackgroundReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_StartTextManipulationsReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_StopMediaCaptureReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_SuspendAllMediaPlaybackReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_SuspendReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_TakeSnapshotReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPage_TextInputContextsInRectReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_TryCloseReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_URLSchemeTaskWillPerformRedirectionReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(ATTACHMENT_ELEMENT)
    { "WebPage_UpdateAttachmentAttributesReply", ReceiverName::AsyncReply, false, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_UpdateSelectionWithDeltaReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_UpdateSelectionWithExtentPointAndBoundaryReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_UpdateSelectionWithExtentPointReply", ReceiverName::AsyncReply, false, false },
    { "WebPage_UpdateSelectionWithTouchesReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(IMAGE_ANALYSIS)
    { "WebPage_UpdateWithTextRecognitionResultReply", ReceiverName::AsyncReply, false, false },
#endif
#if ENABLE(MEDIA_STREAM)
    { "WebPage_UserMediaAccessWasGrantedReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebPage_ValidateCommandReply", ReceiverName::AsyncReply, false, false },
    { "WebPermissionControllerProxy_QueryReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(GAMEPAD)
    { "WebProcessPool_PlayGamepadEffectReply", ReceiverName::AsyncReply, false, false },
    { "WebProcessPool_StopGamepadEffectsReply", ReceiverName::AsyncReply, false, false },
    { "WebProcessPool_StoppedUsingGamepadsReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebProcessProxy_GetNotificationsReply", ReceiverName::AsyncReply, false, false },
#if PLATFORM(GTK) || PLATFORM(WPE)
    { "WebProcessProxy_SendMessageToWebContextWithReplyReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebProcess_ClearCachedPageReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_DeleteAllCookiesReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_DeleteWebsiteDataForOriginReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_DeleteWebsiteDataForOriginsReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_DeleteWebsiteDataReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_EstablishRemoteWorkerContextConnectionToNetworkProcessReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_FetchWebsiteDataReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_GetActivePagesOriginsForTestingReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_IsJITEnabledReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_PrepareToSuspendReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_ReleaseMemoryReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_ReloadExecutionContextsForOriginReply", ReceiverName::AsyncReply, false, false },
#if ENABLE(TRACKING_PREVENTION)
    { "WebProcess_SeedResourceLoadStatisticsForTestingReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_SendResourceLoadStatisticsDataImmediatelyReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_SetDomainsWithCrossPageStorageAccessReply", ReceiverName::AsyncReply, false, false },
    { "WebProcess_SetThirdPartyCookieBlockingModeReply", ReceiverName::AsyncReply, false, false },
#endif
    { "WebResourceLoader_WillSendRequestReply", ReceiverName::AsyncReply, false, false },
    { "WebSWClientConnection_FocusServiceWorkerClientReply", ReceiverName::AsyncReply, false, false },
    { "WebSWClientConnection_SetServiceWorkerClientIsControlledReply", ReceiverName::AsyncReply, false, false },
    { "WebSWContextManagerConnection_FireBackgroundFetchClickEventReply", ReceiverName::AsyncReply, false, false },
    { "WebSWContextManagerConnection_FireBackgroundFetchEventReply", ReceiverName::AsyncReply, false, false },
    { "WebSWContextManagerConnection_FireNotificationEventReply", ReceiverName::AsyncReply, false, false },
    { "WebSWContextManagerConnection_FirePushEventReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_AbortBackgroundFetchReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_BackgroundFetchIdentifiersReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_BackgroundFetchInformationReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_DisableNavigationPreloadReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_EnableNavigationPreloadReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_GetNavigationPreloadStateReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_GetPushPermissionStateReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_GetPushSubscriptionReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_GetRegistrationsReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_MatchBackgroundFetchReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_MatchRegistrationReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_RetrieveRecordResponseReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_ScheduleUnregisterJobInServerReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_SetNavigationPreloadHeaderValueReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_StartBackgroundFetchReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_StoreRegistrationsOnDiskReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_SubscribeToPushServiceReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_TerminateWorkerFromClientReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_UnsubscribeFromPushServiceReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_WhenRegistrationReadyReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerConnection_WhenServiceWorkerIsTerminatedForTestingReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerToContextConnection_ClaimReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerToContextConnection_FindClientByVisibleIdentifierReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerToContextConnection_FocusReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerToContextConnection_NavigateReply", ReceiverName::AsyncReply, false, false },
    { "WebSWServerToContextConnection_OpenWindowReply", ReceiverName::AsyncReply, false, false },
    { "WebScreenOrientationManagerProxy_LockReply", ReceiverName::AsyncReply, false, false },
    { "WebSharedWorkerContextManagerConnection_PostConnectEventReply", ReceiverName::AsyncReply, false, false },
    { "WebSharedWorkerObjectConnection_FetchScriptInClientReply", ReceiverName::AsyncReply, false, false },
    { "WebUserContentControllerProxy_DidPostMessageReply", ReceiverName::AsyncReply, false, false },
#if USE(AUDIO_SESSION)
    { "GPUConnectionToWebProcess_EnsureAudioSession", ReceiverName::GPUConnectionToWebProcess, true, false },
#endif
    { "IPCConnectionTester_SyncMessage", ReceiverName::IPCConnectionTester, true, false },
    { "IPCStreamTester_CheckAutoreleasePool", ReceiverName::IPCStreamTester, true, false },
    { "IPCStreamTester_SyncCrashOnZero", ReceiverName::IPCStreamTester, true, false },
    { "IPCStreamTester_SyncMessageReturningSharedMemory1", ReceiverName::IPCStreamTester, true, false },
    { "IPCTester_ReleaseConnectionTester", ReceiverName::IPCTester, true, false },
    { "IPCTester_ReleaseStreamTester", ReceiverName::IPCTester, true, false },
    { "IPCTester_StopMessageTesting", ReceiverName::IPCTester, true, false },
    { "NetworkConnectionToWebProcess_BlobSize", ReceiverName::NetworkConnectionToWebProcess, true, false },
    { "NetworkConnectionToWebProcess_CookieRequestHeaderFieldValue", ReceiverName::NetworkConnectionToWebProcess, true, false },
    { "NetworkConnectionToWebProcess_CookiesForDOM", ReceiverName::NetworkConnectionToWebProcess, true, false },
    { "NetworkConnectionToWebProcess_DomCookiesForHost", ReceiverName::NetworkConnectionToWebProcess, true, false },
    { "NetworkConnectionToWebProcess_GetNetworkLoadInformationResponse", ReceiverName::NetworkConnectionToWebProcess, true, false },
    { "NetworkConnectionToWebProcess_GetNetworkLoadIntermediateInformation", ReceiverName::NetworkConnectionToWebProcess, true, false },
    { "NetworkConnectionToWebProcess_GetRawCookies", ReceiverName::NetworkConnectionToWebProcess, true, false },
    { "NetworkConnectionToWebProcess_PerformSynchronousLoad", ReceiverName::NetworkConnectionToWebProcess, true, false },
    { "NetworkConnectionToWebProcess_TakeNetworkLoadInformationMetrics", ReceiverName::NetworkConnectionToWebProcess, true, false },
    { "NetworkConnectionToWebProcess_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply", ReceiverName::NetworkConnectionToWebProcess, true, false },
    { "NetworkProcessProxy_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply", ReceiverName::NetworkProcessProxy, true, false },
    { "NetworkProcess_ProcessWillSuspendImminentlyForTestingSync", ReceiverName::NetworkProcess, true, false },
    { "NetworkProcess_ResetServiceWorkerFetchTimeoutForTesting", ReceiverName::NetworkProcess, true, false },
    { "NetworkProcess_SetAllowsAnySSLCertificateForWebSocket", ReceiverName::NetworkProcess, true, false },
    { "NetworkProcess_SetCacheModelSynchronouslyForTesting", ReceiverName::NetworkProcess, true, false },
    { "NetworkProcess_SetServiceWorkerFetchTimeoutForTesting", ReceiverName::NetworkProcess, true, false },
    { "NetworkStorageManager_ConnectToStorageAreaSync", ReceiverName::NetworkStorageManager, true, false },
    { "RemoteAdapter_RequestDevice", ReceiverName::RemoteAdapter, true, false },
    { "RemoteAudioSessionProxy_TryToSetActive", ReceiverName::RemoteAudioSessionProxy, true, false },
    { "RemoteBuffer_GetMappedRange", ReceiverName::RemoteBuffer, true, false },
    { "RemoteCDMFactoryProxy_CreateCDM", ReceiverName::RemoteCDMFactoryProxy, true, false },
    { "RemoteCDMFactoryProxy_SupportsKeySystem", ReceiverName::RemoteCDMFactoryProxy, true, false },
    { "RemoteCDMInstanceProxy_CreateSession", ReceiverName::RemoteCDMInstanceProxy, true, false },
    { "RemoteCDMProxy_CreateInstance", ReceiverName::RemoteCDMProxy, true, false },
    { "RemoteCompositorIntegration_PrepareForDisplay", ReceiverName::RemoteCompositorIntegration, true, false },
#if PLATFORM(COCOA)
    { "RemoteCompositorIntegration_RecreateRenderBuffers", ReceiverName::RemoteCompositorIntegration, true, false },
#endif
    { "RemoteDisplayListRecorder_FlushContextSync", ReceiverName::RemoteDisplayListRecorder, true, false },
    { "RemoteGPU_RequestAdapter", ReceiverName::RemoteGPU, true, false },
    { "RemoteGraphicsContextGL_CheckFramebufferStatus", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ClientWaitSync", ReceiverName::RemoteGraphicsContextGL, true, false },
#if ENABLE(VIDEO) && PLATFORM(COCOA)
    { "RemoteGraphicsContextGL_CopyTextureFromVideoFrame", ReceiverName::RemoteGraphicsContextGL, true, false },
#endif
#if PLATFORM(COCOA)
    { "RemoteGraphicsContextGL_CreateAndBindEGLImage", ReceiverName::RemoteGraphicsContextGL, true, false },
#endif
    { "RemoteGraphicsContextGL_CreateBuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
#if PLATFORM(COCOA)
    { "RemoteGraphicsContextGL_CreateEGLSync", ReceiverName::RemoteGraphicsContextGL, true, false },
#endif
    { "RemoteGraphicsContextGL_CreateFramebuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CreateProgram", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CreateQuery", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CreateQueryEXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CreateRenderbuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CreateSampler", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CreateShader", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CreateTexture", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CreateTransformFeedback", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_CreateVertexArray", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_DestroyEGLSync", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_EnableRequiredWebXRExtensions", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_FenceSync", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetActiveAttrib", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetActiveUniform", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetActiveUniformBlockName", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetActiveUniformBlockiv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetActiveUniforms", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetAttribLocation", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetBooleanv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetBufferParameteri", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetBufferSubData", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetErrors", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetFloatv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetFragDataLocation", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetFramebufferAttachmentParameteri", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetInteger64", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetInteger64EXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetInteger64i", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetIntegeri_v", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetIntegerv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetInternalformativ", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetProgramInfoLog", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetProgrami", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetQuery", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetQueryObjectiEXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetQueryObjectui", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetQueryObjectui64EXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetQueryiEXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetRenderbufferParameteri", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetSamplerParameterf", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetSamplerParameteri", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetShaderInfoLog", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetShaderPrecisionFormat", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetShaderSource", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetShaderi", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetString", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetSynci", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetTexParameterf", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetTexParameteri", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetTransformFeedbackVarying", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetTranslatedShaderSourceANGLE", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetUniformBlockIndex", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetUniformIndices", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetUniformLocation", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetUniformfv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetUniformiv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetUniformuiv", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_GetVertexAttribOffset", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsBuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsEnabled", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsFramebuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsProgram", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsQuery", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsQueryEXT", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsRenderbuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsSampler", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsShader", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsSync", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsTexture", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsTransformFeedback", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_IsVertexArray", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_PaintCompositedResultsToCanvas", ReceiverName::RemoteGraphicsContextGL, true, false },
#if ENABLE(MEDIA_STREAM) || ENABLE(WEB_CODECS)
    { "RemoteGraphicsContextGL_PaintCompositedResultsToVideoFrame", ReceiverName::RemoteGraphicsContextGL, true, false },
#endif
    { "RemoteGraphicsContextGL_PaintRenderingResultsToCanvas", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_PaintRenderingResultsToPixelBuffer", ReceiverName::RemoteGraphicsContextGL, true, false },
#if PLATFORM(COCOA) || USE(GRAPHICS_LAYER_WC) || USE(GBM) || !PLATFORM(COCOA) && !USE(GRAPHICS_LAYER_WC) && !USE(GBM)
    { "RemoteGraphicsContextGL_PrepareForDisplay", ReceiverName::RemoteGraphicsContextGL, true, false },
#endif
    { "RemoteGraphicsContextGL_ReadPixelsInline", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteGraphicsContextGL_ReadPixelsSharedMemory", ReceiverName::RemoteGraphicsContextGL, true, false },
    { "RemoteLegacyCDMFactoryProxy_CreateCDM", ReceiverName::RemoteLegacyCDMFactoryProxy, true, false },
    { "RemoteLegacyCDMFactoryProxy_SupportsKeySystem", ReceiverName::RemoteLegacyCDMFactoryProxy, true, false },
    { "RemoteLegacyCDMProxy_CreateSession", ReceiverName::RemoteLegacyCDMProxy, true, false },
    { "RemoteLegacyCDMProxy_SupportsMIMEType", ReceiverName::RemoteLegacyCDMProxy, true, false },
    { "RemoteLegacyCDMSessionProxy_CachedKeyForKeyID", ReceiverName::RemoteLegacyCDMSessionProxy, true, false },
    { "RemoteLegacyCDMSessionProxy_GenerateKeyRequest", ReceiverName::RemoteLegacyCDMSessionProxy, true, false },
    { "RemoteLegacyCDMSessionProxy_Update", ReceiverName::RemoteLegacyCDMSessionProxy, true, false },
    { "RemoteMediaPlayerManagerProxy_GetSupportedTypes", ReceiverName::RemoteMediaPlayerManagerProxy, true, false },
    { "RemoteMediaPlayerManagerProxy_SupportsKeySystem", ReceiverName::RemoteMediaPlayerManagerProxy, true, false },
    { "RemoteMediaPlayerManagerProxy_SupportsTypeAndCodecs", ReceiverName::RemoteMediaPlayerManagerProxy, true, false },
#if PLATFORM(IOS_FAMILY)
    { "RemoteMediaPlayerProxy_AccessLog", ReceiverName::RemoteMediaPlayerProxy, true, false },
#endif
#if PLATFORM(COCOA)
    { "RemoteMediaPlayerProxy_ColorSpace", ReceiverName::RemoteMediaPlayerProxy, true, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "RemoteMediaPlayerProxy_ErrorLog", ReceiverName::RemoteMediaPlayerProxy, true, false },
#endif
    { "RemoteMediaPlayerProxy_IsCrossOrigin", ReceiverName::RemoteMediaPlayerProxy, true, false },
#if PLATFORM(COCOA)
    { "RemoteMediaPlayerProxy_NativeImageForCurrentTime", ReceiverName::RemoteMediaPlayerProxy, true, false },
#endif
    { "RemoteMediaPlayerProxy_VideoFrameForCurrentTimeIfChanged", ReceiverName::RemoteMediaPlayerProxy, true, false },
    { "RemoteMediaSourceProxy_AddSourceBuffer", ReceiverName::RemoteMediaSourceProxy, true, false },
    { "RemoteQueue_OnSubmittedWorkDone", ReceiverName::RemoteQueue, true, false },
    { "RemoteRenderingBackend_GetFilteredImageForImageBuffer", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_GetPixelBufferForImageBuffer", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_GetPixelBufferForImageBufferWithNewMemory", ReceiverName::RemoteRenderingBackend, true, false },
    { "RemoteRenderingBackend_GetShareableBitmapForImageBuffer", ReceiverName::RemoteRenderingBackend, true, false },
#if PLATFORM(COCOA)
    { "RemoteRenderingBackend_PrepareBuffersForDisplay", ReceiverName::RemoteRenderingBackend, true, false },
#endif
    { "RemoteSourceBufferProxy_CanSwitchToType", ReceiverName::RemoteSourceBufferProxy, true, false },
    { "RemoteSourceBufferProxy_EvictCodedFrames", ReceiverName::RemoteSourceBufferProxy, true, false },
    { "RemoteSourceBufferProxy_MinimumUpcomingPresentationTimeForTrackID", ReceiverName::RemoteSourceBufferProxy, true, false },
#if PLATFORM(COCOA)
    { "RemoteVideoFrameObjectHeap_ConvertFrameBuffer", ReceiverName::RemoteVideoFrameObjectHeap, true, false },
    { "RemoteVideoFrameObjectHeap_PixelBuffer", ReceiverName::RemoteVideoFrameObjectHeap, true, false },
#endif
    { "WebFullScreenManagerProxy_SupportsFullScreen", ReceiverName::WebFullScreenManagerProxy, true, false },
    { "WebPageProxy_AccessibilityScreenToRootView", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_BackForwardGoToItem", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_BackForwardItemAtIndex", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_BackForwardListContainsItem", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_BackForwardListCounts", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_CanUndoRedo", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_CheckGrammarOfString", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_CheckSpellingOfString", ReceiverName::WebPageProxy, true, false },
#if USE(UNIFIED_TEXT_CHECKING)
    { "WebPageProxy_CheckTextOfParagraph", ReceiverName::WebPageProxy, true, false },
#endif
    { "WebPageProxy_CreateNewPage", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_DecidePolicyForNavigationActionSync", ReceiverName::WebPageProxy, true, false },
#if USE(DICTATION_ALTERNATIVES)
    { "WebPageProxy_DictationAlternatives", ReceiverName::WebPageProxy, true, false },
#endif
#if PLATFORM(MAC)
    { "WebPageProxy_DismissCorrectionPanelSoon", ReceiverName::WebPageProxy, true, false },
#endif
    { "WebPageProxy_ExceededDatabaseQuota", ReceiverName::WebPageProxy, true, false },
#if PLATFORM(COCOA)
    { "WebPageProxy_ExecuteSavedCommandBySelector", ReceiverName::WebPageProxy, true, false },
#endif
    { "WebPageProxy_ExecuteUndoRedo", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_GetGuessesForWord", ReceiverName::WebPageProxy, true, false },
#if PLATFORM(COCOA)
    { "WebPageProxy_GetIsSpeaking", ReceiverName::WebPageProxy, true, false },
#endif
    { "WebPageProxy_GetMenuBarIsVisible", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_GetStatusBarIsVisible", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_GetToolbarsAreVisible", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_GetWindowFrame", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_HandleSynchronousMessage", ReceiverName::WebPageProxy, true, false },
#if PLATFORM(IOS_FAMILY)
    { "WebPageProxy_InterpretKeyEvent", ReceiverName::WebPageProxy, true, false },
#endif
    { "WebPageProxy_LoadRecentSearches", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_LoadSynchronousURLSchemeTask", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_PrintFrame", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_ReachedApplicationCacheOriginQuota", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_RequestDOMPasteAccess", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_RootViewToAccessibilityScreen", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_RootViewToScreen", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_RunBeforeUnloadConfirmPanel", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_RunJavaScriptAlert", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_RunJavaScriptConfirm", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_RunJavaScriptPrompt", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_ScreenToRootView", ReceiverName::WebPageProxy, true, false },
#if ENABLE(ATTACHMENT_ELEMENT)
    { "WebPageProxy_SerializedAttachmentDataForIdentifiers", ReceiverName::WebPageProxy, true, false },
#endif
#if ENABLE(PDFKIT_PLUGIN)
    { "WebPageProxy_ShowPDFContextMenu", ReceiverName::WebPageProxy, true, false },
#endif
#if ENABLE(SPEECH_SYNTHESIS)
    { "WebPageProxy_SpeechSynthesisVoiceList", ReceiverName::WebPageProxy, true, false },
#endif
    { "WebPageProxy_SpellingUIIsShowing", ReceiverName::WebPageProxy, true, false },
#if USE(APPKIT)
    { "WebPageProxy_SubstitutionsPanelIsShowing", ReceiverName::WebPageProxy, true, false },
#endif
#if ENABLE(WEB_CRYPTO)
    { "WebPageProxy_UnwrapCryptoKey", ReceiverName::WebPageProxy, true, false },
    { "WebPageProxy_WrapCryptoKey", ReceiverName::WebPageProxy, true, false },
#endif
#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
    { "WebPage_ComputePagesForPrintingiOS", ReceiverName::WebPage, true, false },
#endif
#if PLATFORM(COCOA)
    { "WebPage_GetDataSelectionForPasteboard", ReceiverName::WebPage, true, false },
    { "WebPage_GetStringSelectionForPasteboard", ReceiverName::WebPage, true, false },
    { "WebPage_ReadSelectionFromPasteboard", ReceiverName::WebPage, true, false },
    { "WebPage_ShouldDelayWindowOrderingEvent", ReceiverName::WebPage, true, false },
#endif
#if PLATFORM(IOS_FAMILY)
    { "WebPage_SyncApplyAutocorrection", ReceiverName::WebPage, true, false },
#endif
    { "WebPage_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply", ReceiverName::WebPage, true, true },
#if PLATFORM(COCOA)
    { "WebPasteboardProxy_AddPasteboardTypes", ReceiverName::WebPasteboardProxy, true, false },
#endif
    { "WebPasteboardProxy_AllPasteboardItemInfo", ReceiverName::WebPasteboardProxy, true, false },
    { "WebPasteboardProxy_ContainsStringSafeForDOMToReadForType", ReceiverName::WebPasteboardProxy, true, false },
#if PLATFORM(COCOA)
    { "WebPasteboardProxy_ContainsURLStringSuitableForLoading", ReceiverName::WebPasteboardProxy, true, false },
    { "WebPasteboardProxy_GetNumberOfFiles", ReceiverName::WebPasteboardProxy, true, false },
    { "WebPasteboardProxy_GetPasteboardBufferForType", ReceiverName::WebPasteboardProxy, true, false },
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK)
    { "WebPasteboardProxy_GetPasteboardChangeCount", ReceiverName::WebPasteboardProxy, true, false },
#endif
#if PLATFORM(COCOA)
    { "WebPasteboardProxy_GetPasteboardColor", ReceiverName::WebPasteboardProxy, true, false },
#endif
    { "WebPasteboardProxy_GetPasteboardItemsCount", ReceiverName::WebPasteboardProxy, true, false },
#if PLATFORM(COCOA)
    { "WebPasteboardProxy_GetPasteboardPathnamesForType", ReceiverName::WebPasteboardProxy, true, false },
    { "WebPasteboardProxy_GetPasteboardStringForType", ReceiverName::WebPasteboardProxy, true, false },
    { "WebPasteboardProxy_GetPasteboardStringsForType", ReceiverName::WebPasteboardProxy, true, false },
#endif
#if PLATFORM(COCOA) || USE(LIBWPE)
    { "WebPasteboardProxy_GetPasteboardTypes", ReceiverName::WebPasteboardProxy, true, false },
#endif
#if PLATFORM(COCOA)
    { "WebPasteboardProxy_GetPasteboardURL", ReceiverName::WebPasteboardProxy, true, false },
#endif
#if PLATFORM(GTK)
    { "WebPasteboardProxy_GetTypes", ReceiverName::WebPasteboardProxy, true, false },
#endif
    { "WebPasteboardProxy_InformationForItemAtIndex", ReceiverName::WebPasteboardProxy, true, false },
#if PLATFORM(GTK)
    { "WebPasteboardProxy_ReadBuffer", ReceiverName::WebPasteboardProxy, true, false },
#endif
    { "WebPasteboardProxy_ReadBufferFromPasteboard", ReceiverName::WebPasteboardProxy, true, false },
#if PLATFORM(GTK)
    { "WebPasteboardProxy_ReadFilePaths", ReceiverName::WebPasteboardProxy, true, false },
#endif
    { "WebPasteboardProxy_ReadStringFromPasteboard", ReceiverName::WebPasteboardProxy, true, false },
#if PLATFORM(GTK)
    { "WebPasteboardProxy_ReadText", ReceiverName::WebPasteboardProxy, true, false },
#endif
    { "WebPasteboardProxy_ReadURLFromPasteboard", ReceiverName::WebPasteboardProxy, true, false },
#if PLATFORM(COCOA)
    { "WebPasteboardProxy_SetPasteboardBufferForType", ReceiverName::WebPasteboardProxy, true, false },
    { "WebPasteboardProxy_SetPasteboardColor", ReceiverName::WebPasteboardProxy, true, false },
    { "WebPasteboardProxy_SetPasteboardStringForType", ReceiverName::WebPasteboardProxy, true, false },
    { "WebPasteboardProxy_SetPasteboardTypes", ReceiverName::WebPasteboardProxy, true, false },
    { "WebPasteboardProxy_SetPasteboardURL", ReceiverName::WebPasteboardProxy, true, false },
#endif
#if (PLATFORM(COCOA) && ENABLE(IPC_TESTING_API))
    { "WebPasteboardProxy_TestIPCSharedMemory", ReceiverName::WebPasteboardProxy, true, false },
#endif
    { "WebPasteboardProxy_TypesSafeForDOMToReadAndWrite", ReceiverName::WebPasteboardProxy, true, false },
#if PLATFORM(COCOA)
    { "WebPasteboardProxy_URLStringSuitableForLoading", ReceiverName::WebPasteboardProxy, true, false },
#endif
    { "WebPasteboardProxy_WriteCustomData", ReceiverName::WebPasteboardProxy, true, false },
    { "WebProcessPool_HandleSynchronousMessage", ReceiverName::WebProcessPool, true, false },
    { "WebProcessProxy_GetNetworkProcessConnection", ReceiverName::WebProcessProxy, true, false },
#if PLATFORM(MAC)
    { "WebProcessProxy_IsAXAuthenticated", ReceiverName::WebProcessProxy, true, false },
#endif
    { "WebProcessProxy_RenderTreeAsText", ReceiverName::WebProcessProxy, true, false },
    { "WebProcessProxy_ShouldTerminate", ReceiverName::WebProcessProxy, true, false },
    { "WebProcess_RenderTreeAsText", ReceiverName::WebProcess, true, false },
    { "WebScreenOrientationManagerProxy_CurrentOrientation", ReceiverName::WebScreenOrientationManagerProxy, true, false },
    { "WrappedAsyncMessageForTesting", ReceiverName::IPC, true, false },
    { "<invalid message name>", ReceiverName::Invalid, false, false }
};

} // namespace IPC::Detail
