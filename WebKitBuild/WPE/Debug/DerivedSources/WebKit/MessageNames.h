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

#pragma once

#include <algorithm>
#include <wtf/EnumTraits.h>

namespace IPC {

enum class ReceiverName : uint8_t {
    AuthenticationManager = 1
    , AuxiliaryProcess = 2
    , CacheStorageEngineConnection = 3
    , DownloadProxy = 4
    , DrawingArea = 5
    , DrawingAreaProxy = 6
    , EventDispatcher = 7
    , GPUConnectionToWebProcess = 8
    , GPUProcess = 9
    , GPUProcessConnection = 10
    , GPUProcessProxy = 11
    , IPCConnectionTester = 12
    , IPCStreamTester = 13
    , IPCStreamTesterProxy = 14
    , IPCTester = 15
    , IPCTesterReceiver = 16
    , LibWebRTCCodecs = 17
    , LibWebRTCCodecsProxy = 18
    , LibWebRTCNetwork = 19
    , MediaPlayerPrivateRemote = 20
    , MediaSourcePrivateRemote = 21
    , NetworkBroadcastChannelRegistry = 22
    , NetworkConnectionToWebProcess = 23
    , NetworkContentRuleListManager = 24
    , NetworkMDNSRegister = 25
    , NetworkProcess = 26
    , NetworkProcessConnection = 27
    , NetworkProcessProxy = 28
    , NetworkRTCMonitor = 29
    , NetworkRTCProvider = 30
    , NetworkResourceLoader = 31
    , NetworkSocketChannel = 32
    , NetworkStorageManager = 33
    , NotificationManagerMessageHandler = 34
    , PlatformXRSystem = 35
    , PlatformXRSystemProxy = 36
    , RTCDataChannelRemoteManager = 37
    , RTCDataChannelRemoteManagerProxy = 38
    , RemoteAdapter = 39
    , RemoteAudioDestinationManager = 40
    , RemoteAudioHardwareListener = 41
    , RemoteAudioMediaStreamTrackRendererInternalUnitManager = 42
    , RemoteAudioSession = 43
    , RemoteAudioSessionProxy = 44
    , RemoteAudioSourceProviderManager = 45
    , RemoteBarcodeDetector = 46
    , RemoteBindGroup = 47
    , RemoteBindGroupLayout = 48
    , RemoteBuffer = 49
    , RemoteCDMFactoryProxy = 50
    , RemoteCDMInstance = 51
    , RemoteCDMInstanceProxy = 52
    , RemoteCDMInstanceSession = 53
    , RemoteCDMInstanceSessionProxy = 54
    , RemoteCDMProxy = 55
    , RemoteCommandBuffer = 56
    , RemoteCommandEncoder = 57
    , RemoteCompositorIntegration = 58
    , RemoteComputePassEncoder = 59
    , RemoteComputePipeline = 60
    , RemoteDevice = 61
    , RemoteDisplayListRecorder = 62
    , RemoteExternalTexture = 63
    , RemoteFaceDetector = 64
    , RemoteGPU = 65
    , RemoteGPUProxy = 66
    , RemoteGraphicsContextGL = 67
    , RemoteGraphicsContextGLProxy = 68
    , RemoteImageBufferProxy = 69
    , RemoteLegacyCDMFactoryProxy = 70
    , RemoteLegacyCDMProxy = 71
    , RemoteLegacyCDMSession = 72
    , RemoteLegacyCDMSessionProxy = 73
    , RemoteMediaEngineConfigurationFactoryProxy = 74
    , RemoteMediaPlayerManagerProxy = 75
    , RemoteMediaPlayerProxy = 76
    , RemoteMediaRecorder = 77
    , RemoteMediaRecorderManager = 78
    , RemoteMediaResourceManager = 79
    , RemoteMediaSessionCoordinator = 80
    , RemoteMediaSessionCoordinatorProxy = 81
    , RemoteMediaSourceProxy = 82
    , RemotePipelineLayout = 83
    , RemotePresentationContext = 84
    , RemoteQuerySet = 85
    , RemoteQueue = 86
    , RemoteRemoteCommandListener = 87
    , RemoteRemoteCommandListenerProxy = 88
    , RemoteRenderBundle = 89
    , RemoteRenderBundleEncoder = 90
    , RemoteRenderPassEncoder = 91
    , RemoteRenderPipeline = 92
    , RemoteRenderingBackend = 93
    , RemoteRenderingBackendProxy = 94
    , RemoteSampleBufferDisplayLayer = 95
    , RemoteSampleBufferDisplayLayerManager = 96
    , RemoteSampler = 97
    , RemoteShaderModule = 98
    , RemoteSourceBufferProxy = 99
    , RemoteTextDetector = 100
    , RemoteTexture = 101
    , RemoteTextureView = 102
    , RemoteVideoFrameObjectHeap = 103
    , RemoteVideoFrameObjectHeapProxyProcessor = 104
    , RemoteWebInspectorUI = 105
    , RemoteWebInspectorUIProxy = 106
    , RemoteWebLockRegistry = 107
    , SampleBufferDisplayLayer = 108
    , ServiceWorkerDownloadTask = 109
    , ServiceWorkerFetchTask = 110
    , SourceBufferPrivateRemote = 111
    , SpeechRecognitionRealtimeMediaSourceManager = 112
    , SpeechRecognitionRemoteRealtimeMediaSourceManager = 113
    , SpeechRecognitionServer = 114
    , StorageAreaMap = 115
    , VisitedLinkStore = 116
    , VisitedLinkTableController = 117
    , WebAutomationSession = 118
    , WebAutomationSessionProxy = 119
    , WebBroadcastChannelRegistry = 120
    , WebConnection = 121
    , WebCookieManager = 122
    , WebFileSystemStorageConnection = 123
    , WebFullScreenManager = 124
    , WebFullScreenManagerProxy = 125
    , WebGeolocationManager = 126
    , WebGeolocationManagerProxy = 127
    , WebIDBConnectionToServer = 128
    , WebInspector = 129
    , WebInspectorInterruptDispatcher = 130
    , WebInspectorUI = 131
    , WebInspectorUIProxy = 132
    , WebLockRegistryProxy = 133
    , WebNotificationManager = 134
    , WebPage = 135
    , WebPageProxy = 136
    , WebPasteboardProxy = 137
    , WebPermissionController = 138
    , WebPermissionControllerProxy = 139
    , WebProcess = 140
    , WebProcessPool = 141
    , WebProcessProxy = 142
    , WebRTCMonitor = 143
    , WebRTCResolver = 144
    , WebResourceLoader = 145
    , WebSWClientConnection = 146
    , WebSWContextManagerConnection = 147
    , WebSWServerConnection = 148
    , WebSWServerToContextConnection = 149
    , WebScreenOrientationManager = 150
    , WebScreenOrientationManagerProxy = 151
    , WebSharedWorkerContextManagerConnection = 152
    , WebSharedWorkerObjectConnection = 153
    , WebSharedWorkerServerConnection = 154
    , WebSharedWorkerServerToContextConnection = 155
    , WebSocketChannel = 156
    , WebSpeechRecognitionConnection = 157
    , WebUserContentController = 158
    , WebUserContentControllerProxy = 159
    , IPC = 160
    , AsyncReply = 161
    , Invalid = 162
};

enum class MessageName : uint16_t {
    AuthenticationManager_CompleteAuthenticationChallenge,
#if OS(LINUX)
    AuxiliaryProcess_DidReceiveMemoryPressureEvent,
#endif
    AuxiliaryProcess_MainThreadPing,
    AuxiliaryProcess_SetProcessSuppressionEnabled,
    AuxiliaryProcess_ShutDown,
    CacheStorageEngineConnection_Caches,
    CacheStorageEngineConnection_ClearMemoryRepresentation,
    CacheStorageEngineConnection_DeleteMatchingRecords,
    CacheStorageEngineConnection_Dereference,
    CacheStorageEngineConnection_EngineRepresentation,
    CacheStorageEngineConnection_Open,
    CacheStorageEngineConnection_PutRecords,
    CacheStorageEngineConnection_Reference,
    CacheStorageEngineConnection_Remove,
    CacheStorageEngineConnection_RetrieveRecords,
    DownloadProxy_DecideDestinationWithSuggestedFilename,
    DownloadProxy_DidCreateDestination,
    DownloadProxy_DidFail,
    DownloadProxy_DidFinish,
    DownloadProxy_DidReceiveAuthenticationChallenge,
    DownloadProxy_DidReceiveData,
    DownloadProxy_DidStart,
    DownloadProxy_WillSendRequest,
    DrawingAreaProxy_DidFirstLayerFlush,
    DrawingAreaProxy_DispatchPresentationCallbacksAfterFlushingLayers,
    DrawingAreaProxy_EnterAcceleratedCompositingMode,
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
    DrawingAreaProxy_ExitAcceleratedCompositingMode,
    DrawingAreaProxy_Update,
#endif
    DrawingAreaProxy_UpdateAcceleratedCompositingMode,
#if PLATFORM(COCOA)
    DrawingArea_AcceleratedAnimationDidEnd,
    DrawingArea_AcceleratedAnimationDidStart,
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK)
    DrawingArea_AdjustTransientZoom,
    DrawingArea_CommitTransientZoom,
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
    DrawingArea_DidDiscardBackingStore,
#endif
#if PLATFORM(COCOA)
    DrawingArea_DispatchAfterEnsuringDrawing,
#endif
    DrawingArea_DisplayDidRefresh,
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
    DrawingArea_ForceUpdate,
#endif
#if PLATFORM(COCOA)
    DrawingArea_SetColorSpace,
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER) || PLATFORM(COCOA)
    DrawingArea_SetDeviceScaleFactor,
#endif
#if PLATFORM(COCOA)
    DrawingArea_SetViewExposedRect,
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER)
    DrawingArea_TargetRefreshRateDidChange,
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER) || PLATFORM(COCOA)
    DrawingArea_UpdateGeometry,
#endif
#if USE(GRAPHICS_LAYER_WC)
    DrawingArea_UpdateGeometryWC,
#endif
#if HAVE(CVDISPLAYLINK)
    EventDispatcher_DisplayDidRefresh,
#endif
#if ENABLE(MAC_GESTURE_EVENTS)
    EventDispatcher_GestureEvent,
#endif
    EventDispatcher_PageScreenDidChange,
#if ENABLE(MOMENTUM_EVENT_DISPATCHER)
    EventDispatcher_SetScrollingAccelerationCurve,
#endif
#if ENABLE(IOS_TOUCH_EVENTS)
    EventDispatcher_TouchEvent,
    EventDispatcher_TouchEventWithoutCallback,
#endif
    EventDispatcher_WheelEvent,
    GPUConnectionToWebProcess_ClearNowPlayingInfo,
    GPUConnectionToWebProcess_ConfigureLoggingChannel,
    GPUConnectionToWebProcess_CreateAudioHardwareListener,
#if ENABLE(WEBGL)
    GPUConnectionToWebProcess_CreateGraphicsContextGL,
#endif
    GPUConnectionToWebProcess_CreateRemoteCommandListener,
    GPUConnectionToWebProcess_CreateRemoteGPU,
    GPUConnectionToWebProcess_CreateRenderingBackend,
#if HAVE(VISIBILITY_PROPAGATION_VIEW)
    GPUConnectionToWebProcess_CreateVisibilityPropagationContextForPage,
#endif
#if USE(GRAPHICS_LAYER_WC)
    GPUConnectionToWebProcess_CreateWCLayerTreeHost,
#endif
#if HAVE(VISIBILITY_PROPAGATION_VIEW)
    GPUConnectionToWebProcess_DestroyVisibilityPropagationContextForPage,
#endif
#if ENABLE(MEDIA_SOURCE)
    GPUConnectionToWebProcess_EnableMockMediaSource,
#endif
#if ENABLE(VP9)
    GPUConnectionToWebProcess_EnableVP9Decoders,
#endif
#if PLATFORM(IOS_FAMILY)
    GPUConnectionToWebProcess_EnsureMediaSessionHelper,
#endif
    GPUConnectionToWebProcess_ReleaseAudioHardwareListener,
#if ENABLE(WEBGL)
    GPUConnectionToWebProcess_ReleaseGraphicsContextGL,
#endif
    GPUConnectionToWebProcess_ReleaseRemoteCommandListener,
    GPUConnectionToWebProcess_ReleaseRemoteGPU,
    GPUConnectionToWebProcess_ReleaseRenderingBackend,
    GPUConnectionToWebProcess_ReleaseSerializedImageBuffer,
#if USE(GRAPHICS_LAYER_WC)
    GPUConnectionToWebProcess_ReleaseWCLayerTreeHost,
#endif
    GPUConnectionToWebProcess_SetMediaOverridesForTesting,
    GPUConnectionToWebProcess_SetNowPlayingInfo,
#if ENABLE(ROUTING_ARBITRATION)
    GPUProcessConnection_BeginRoutingArbitrationWithCategory,
#endif
    GPUProcessConnection_DidInitialize,
    GPUProcessConnection_DidReceiveRemoteCommand,
#if ENABLE(ROUTING_ARBITRATION)
    GPUProcessConnection_EndRoutingArbitration,
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(COCOA)
    GPUProcessConnection_ResetAudioMediaStreamTrackRendererInternalUnit,
#endif
#if HAVE(VISIBILITY_PROPAGATION_VIEW)
    GPUProcessProxy_DidCreateContextForVisibilityPropagation,
#endif
    GPUProcessProxy_ProcessIsReadyToExit,
#if ENABLE(VP9)
    GPUProcessProxy_SetHasVP9ExtensionSupport,
    GPUProcessProxy_SetHasVP9HardwareDecoder,
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
    GPUProcessProxy_StatusBarWasTapped,
#endif
    GPUProcessProxy_TerminateWebProcess,
#if ENABLE(MEDIA_STREAM)
    GPUProcess_AddMockMediaDevice,
#endif
    GPUProcess_AddSession,
#if ENABLE(MEDIA_STREAM)
    GPUProcess_ClearMockMediaDevices,
#endif
#if HAVE(AUDIO_COMPONENT_SERVER_REGISTRATIONS)
    GPUProcess_ConsumeAudioComponentRegistrations,
#endif
    GPUProcess_CreateGPUConnectionToWebProcess,
#if PLATFORM(MAC)
    GPUProcess_DisplayConfigurationChanged,
#endif
#if HAVE(POWERLOG_TASK_MODE_QUERY)
    GPUProcess_EnablePowerLogging,
#endif
    GPUProcess_InitializeGPUProcess,
#if ENABLE(CFPREFS_DIRECT_MODE)
    GPUProcess_NotifyPreferencesChanged,
#endif
#if PLATFORM(MAC)
    GPUProcess_OpenDirectoryCacheInvalidated,
#endif
    GPUProcess_PrepareToSuspend,
    GPUProcess_ProcessDidResume,
#if HAVE(SCREEN_CAPTURE_KIT)
    GPUProcess_PromptForGetDisplayMedia,
#endif
#if ENABLE(MEDIA_STREAM)
    GPUProcess_RemoveMockMediaDevice,
#endif
    GPUProcess_RemoveSession,
#if ENABLE(VIDEO)
    GPUProcess_RequestBitmapImageForCurrentTime,
#endif
#if ENABLE(MEDIA_STREAM)
    GPUProcess_ResetMockMediaDevices,
    GPUProcess_SetMockCaptureDevicesEnabled,
    GPUProcess_SetMockCaptureDevicesInterrupted,
    GPUProcess_SetMockMediaDeviceIsEphemeral,
    GPUProcess_SetOrientationForMediaCapture,
#endif
#if PLATFORM(MAC)
    GPUProcess_SetScreenProperties,
#endif
#if HAVE(SC_CONTENT_SHARING_PICKER)
    GPUProcess_SetUseSCContentSharingPicker,
#endif
#if ENABLE(MEDIA_STREAM)
    GPUProcess_TriggerMockMicrophoneConfigurationChange,
    GPUProcess_UpdateCaptureAccess,
    GPUProcess_UpdateCaptureOrigin,
#endif
    GPUProcess_UpdateDOMRenderingEnabled,
    GPUProcess_UpdateGPUProcessPreferences,
    GPUProcess_UpdateSandboxAccess,
    GPUProcess_UpdateWebGPUEnabled,
    GPUProcess_UserPreferredLanguagesChanged,
    GPUProcess_WebProcessConnectionCountForTesting,
    IPCConnectionTester_AsyncMessage,
    IPCStreamTesterProxy_WasCreated,
    IPCStreamTester_AsyncMessage,
    IPCTesterReceiver_AsyncMessage,
    IPCTester_CreateConnectionTester,
    IPCTester_CreateConnectionTesterAndSendAsyncMessages,
    IPCTester_CreateStreamTester,
    IPCTester_SendAsyncMessageToReceiver,
    IPCTester_SendSameSemaphoreBack,
    IPCTester_SendSemaphoreBackAndSignalProtocol,
    IPCTester_StartMessageTesting,
    LibWebRTCCodecsProxy_CreateDecoder,
    LibWebRTCCodecsProxy_CreateEncoder,
    LibWebRTCCodecsProxy_DecodeFrame,
    LibWebRTCCodecsProxy_EncodeFrame,
    LibWebRTCCodecsProxy_FlushDecoder,
    LibWebRTCCodecsProxy_FlushEncoder,
    LibWebRTCCodecsProxy_InitializeEncoder,
    LibWebRTCCodecsProxy_ReleaseDecoder,
    LibWebRTCCodecsProxy_ReleaseEncoder,
    LibWebRTCCodecsProxy_SetDecoderFormatDescription,
    LibWebRTCCodecsProxy_SetEncodeRates,
    LibWebRTCCodecsProxy_SetFrameSize,
    LibWebRTCCodecsProxy_SetRTCLoggingLevel,
    LibWebRTCCodecsProxy_SetSharedVideoFrameMemory,
    LibWebRTCCodecsProxy_SetSharedVideoFrameSemaphore,
    LibWebRTCCodecs_CompletedDecoding,
    LibWebRTCCodecs_CompletedDecodingCV,
    LibWebRTCCodecs_CompletedEncoding,
    LibWebRTCCodecs_FailedDecoding,
    LibWebRTCCodecs_FlushDecoderCompleted,
    LibWebRTCCodecs_FlushEncoderCompleted,
    LibWebRTCCodecs_SetEncodingConfiguration,
    LibWebRTCNetwork_SignalAddressReady,
    LibWebRTCNetwork_SignalClose,
    LibWebRTCNetwork_SignalConnect,
    LibWebRTCNetwork_SignalReadPacket,
    LibWebRTCNetwork_SignalSentPacket,
    LibWebRTCNetwork_SignalUsedInterface,
    MediaPlayerPrivateRemote_ActiveSourceBuffersChanged,
    MediaPlayerPrivateRemote_AddDataCue,
#if ENABLE(DATACUE_VALUE)
    MediaPlayerPrivateRemote_AddDataCueWithType,
#endif
    MediaPlayerPrivateRemote_AddGenericCue,
    MediaPlayerPrivateRemote_AddRemoteAudioTrack,
    MediaPlayerPrivateRemote_AddRemoteTextTrack,
    MediaPlayerPrivateRemote_AddRemoteVideoTrack,
    MediaPlayerPrivateRemote_CharacteristicChanged,
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    MediaPlayerPrivateRemote_CurrentPlaybackTargetIsWirelessChanged,
#endif
    MediaPlayerPrivateRemote_CurrentTimeChanged,
    MediaPlayerPrivateRemote_DurationChanged,
    MediaPlayerPrivateRemote_EngineFailedToLoad,
    MediaPlayerPrivateRemote_FirstVideoFrameAvailable,
#if PLATFORM(IOS_FAMILY)
    MediaPlayerPrivateRemote_GetRawCookies,
#endif
#if ENABLE(ENCRYPTED_MEDIA)
    MediaPlayerPrivateRemote_InitializationDataEncountered,
#endif
#if PLATFORM(COCOA)
    MediaPlayerPrivateRemote_LayerHostingContextIdChanged,
#endif
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    MediaPlayerPrivateRemote_MediaPlayerKeyNeeded,
#endif
    MediaPlayerPrivateRemote_MuteChanged,
    MediaPlayerPrivateRemote_NetworkStateChanged,
    MediaPlayerPrivateRemote_ParseWebVTTCueData,
    MediaPlayerPrivateRemote_ParseWebVTTCueDataStruct,
    MediaPlayerPrivateRemote_ParseWebVTTFileHeader,
    MediaPlayerPrivateRemote_PlaybackStateChanged,
#if PLATFORM(COCOA)
    MediaPlayerPrivateRemote_PushVideoFrameMetadata,
#endif
    MediaPlayerPrivateRemote_RateChanged,
    MediaPlayerPrivateRemote_ReadyStateChanged,
    MediaPlayerPrivateRemote_RemoteAudioTrackConfigurationChanged,
    MediaPlayerPrivateRemote_RemoteTextTrackConfigurationChanged,
    MediaPlayerPrivateRemote_RemoteVideoTrackConfigurationChanged,
#if ENABLE(DATACUE_VALUE)
    MediaPlayerPrivateRemote_RemoveDataCue,
#endif
    MediaPlayerPrivateRemote_RemoveGenericCue,
    MediaPlayerPrivateRemote_RemoveRemoteAudioTrack,
    MediaPlayerPrivateRemote_RemoveRemoteTextTrack,
    MediaPlayerPrivateRemote_RemoveRemoteVideoTrack,
    MediaPlayerPrivateRemote_RemoveResource,
    MediaPlayerPrivateRemote_RenderingModeChanged,
    MediaPlayerPrivateRemote_RequestResource,
    MediaPlayerPrivateRemote_ResourceNotSupported,
    MediaPlayerPrivateRemote_SendH2Ping,
    MediaPlayerPrivateRemote_SizeChanged,
    MediaPlayerPrivateRemote_TimeChanged,
    MediaPlayerPrivateRemote_UpdateCachedState,
#if ENABLE(DATACUE_VALUE)
    MediaPlayerPrivateRemote_UpdateDataCue,
#endif
    MediaPlayerPrivateRemote_UpdateGenericCue,
    MediaPlayerPrivateRemote_VolumeChanged,
#if ENABLE(ENCRYPTED_MEDIA)
    MediaPlayerPrivateRemote_WaitingForKeyChanged,
#endif
    MediaSourcePrivateRemote_MediaSourcePrivateShuttingDown,
    MediaSourcePrivateRemote_SeekToTime,
    NetworkBroadcastChannelRegistry_PostMessage,
    NetworkBroadcastChannelRegistry_RegisterChannel,
    NetworkBroadcastChannelRegistry_UnregisterChannel,
    NetworkConnectionToWebProcess_AddAllowedFirstPartyForCookies,
    NetworkConnectionToWebProcess_AddOriginAccessAllowListEntry,
    NetworkConnectionToWebProcess_BrowsingContextRemoved,
    NetworkConnectionToWebProcess_ClearPageSpecificData,
#if ENABLE(SERVICE_WORKER)
    NetworkConnectionToWebProcess_CloseSWContextConnection,
#endif
    NetworkConnectionToWebProcess_CloseSharedWorkerContextConnection,
#if ENABLE(WEB_RTC)
    NetworkConnectionToWebProcess_ConnectToRTCDataChannelRemoteSource,
#endif
    NetworkConnectionToWebProcess_ConvertMainResourceLoadToDownload,
    NetworkConnectionToWebProcess_CookiesForDOMAsync,
    NetworkConnectionToWebProcess_CreateNewMessagePortChannel,
    NetworkConnectionToWebProcess_CreateRTCProvider,
    NetworkConnectionToWebProcess_CreateSocketChannel,
    NetworkConnectionToWebProcess_DeleteCookie,
    NetworkConnectionToWebProcess_DidDeliverMessagePortMessages,
    NetworkConnectionToWebProcess_EntangleLocalPortInThisProcessToRemote,
#if ENABLE(SERVICE_WORKER)
    NetworkConnectionToWebProcess_EstablishSWContextConnection,
#endif
    NetworkConnectionToWebProcess_EstablishSharedWorkerContextConnection,
#if PLATFORM(MAC)
    NetworkConnectionToWebProcess_GetProcessDisplayName,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkConnectionToWebProcess_HasStorageAccess,
#endif
#if ENABLE(CONTENT_FILTERING)
    NetworkConnectionToWebProcess_InstallMockContentFilter,
#endif
    NetworkConnectionToWebProcess_IsResourceLoadFinished,
    NetworkConnectionToWebProcess_LoadPing,
#if ENABLE(LOGD_BLOCKING_IN_WEBCONTENT)
    NetworkConnectionToWebProcess_LogOnBehalfOfWebContent,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkConnectionToWebProcess_LogUserInteraction,
#endif
    NetworkConnectionToWebProcess_MessagePortClosed,
    NetworkConnectionToWebProcess_MessagePortDisentangled,
    NetworkConnectionToWebProcess_PageLoadCompleted,
    NetworkConnectionToWebProcess_PostMessageToRemote,
    NetworkConnectionToWebProcess_PreconnectTo,
    NetworkConnectionToWebProcess_PrefetchDNS,
    NetworkConnectionToWebProcess_PrioritizeResourceLoads,
    NetworkConnectionToWebProcess_RegisterBlobURL,
    NetworkConnectionToWebProcess_RegisterBlobURLHandle,
    NetworkConnectionToWebProcess_RegisterInternalBlobURL,
    NetworkConnectionToWebProcess_RegisterInternalBlobURLForSlice,
    NetworkConnectionToWebProcess_RegisterInternalBlobURLOptionallyFileBacked,
    NetworkConnectionToWebProcess_RegisterInternalFileBlobURL,
    NetworkConnectionToWebProcess_RegisterURLSchemesAsCORSEnabled,
    NetworkConnectionToWebProcess_RemoveLoadIdentifier,
    NetworkConnectionToWebProcess_RemoveOriginAccessAllowListEntry,
#if ENABLE(TRACKING_PREVENTION)
    NetworkConnectionToWebProcess_RemoveStorageAccessForFrame,
    NetworkConnectionToWebProcess_RequestStorageAccess,
    NetworkConnectionToWebProcess_RequestStorageAccessUnderOpener,
#endif
    NetworkConnectionToWebProcess_ResetOriginAccessAllowLists,
#if ENABLE(TRACKING_PREVENTION)
    NetworkConnectionToWebProcess_ResourceLoadStatisticsUpdated,
#endif
    NetworkConnectionToWebProcess_ScheduleResourceLoad,
    NetworkConnectionToWebProcess_SendH2Ping,
    NetworkConnectionToWebProcess_SetCORSDisablingPatterns,
    NetworkConnectionToWebProcess_SetCaptureExtraNetworkLoadMetricsEnabled,
    NetworkConnectionToWebProcess_SetCookieFromDOMAsync,
    NetworkConnectionToWebProcess_SetCookiesFromDOM,
    NetworkConnectionToWebProcess_SetRawCookie,
    NetworkConnectionToWebProcess_SetResourceLoadSchedulingMode,
    NetworkConnectionToWebProcess_StartDownload,
#if HAVE(COOKIE_CHANGE_LISTENER_API)
    NetworkConnectionToWebProcess_SubscribeToCookieChangeNotifications,
#endif
    NetworkConnectionToWebProcess_TakeAllMessagesForPort,
    NetworkConnectionToWebProcess_UnregisterBlobURL,
    NetworkConnectionToWebProcess_UnregisterBlobURLHandle,
#if HAVE(COOKIE_CHANGE_LISTENER_API)
    NetworkConnectionToWebProcess_UnsubscribeFromCookieChangeNotifications,
#endif
#if PLATFORM(MAC)
    NetworkConnectionToWebProcess_UpdateActivePages,
#endif
    NetworkConnectionToWebProcess_UpdateQuotaBasedOnSpaceUsageForTesting,
    NetworkConnectionToWebProcess_UseRedirectionForCurrentNavigation,
    NetworkConnectionToWebProcess_WriteBlobsToTemporaryFilesForIndexedDB,
    NetworkContentRuleListManager_AddContentRuleLists,
    NetworkContentRuleListManager_Remove,
    NetworkContentRuleListManager_RemoveAllContentRuleLists,
    NetworkContentRuleListManager_RemoveContentRuleList,
    NetworkMDNSRegister_RegisterMDNSName,
    NetworkMDNSRegister_UnregisterMDNSNames,
    NetworkProcessConnection_AddAllowedFirstPartyForCookies,
#if HAVE(COOKIE_CHANGE_LISTENER_API)
    NetworkProcessConnection_AllCookiesDeleted,
#endif
    NetworkProcessConnection_BroadcastConsoleMessage,
#if ENABLE(WEB_RTC)
    NetworkProcessConnection_ConnectToRTCDataChannelRemoteSource,
#endif
    NetworkProcessConnection_CookieAcceptPolicyChanged,
#if HAVE(COOKIE_CHANGE_LISTENER_API)
    NetworkProcessConnection_CookiesAdded,
    NetworkProcessConnection_CookiesDeleted,
#endif
#if ENABLE(SHAREABLE_RESOURCE)
    NetworkProcessConnection_DidCacheResource,
#endif
    NetworkProcessConnection_DidFinishPingLoad,
    NetworkProcessConnection_DidFinishPreconnection,
    NetworkProcessConnection_MessagesAvailableForPort,
    NetworkProcessConnection_SetOnLineState,
#if ENABLE(CONTENT_EXTENSIONS)
    NetworkProcessProxy_ContentExtensionRules,
#endif
    NetworkProcessProxy_CookiesDidChange,
    NetworkProcessProxy_DataTaskDidCompleteWithError,
    NetworkProcessProxy_DataTaskDidReceiveData,
    NetworkProcessProxy_DataTaskDidReceiveResponse,
    NetworkProcessProxy_DataTaskReceivedChallenge,
    NetworkProcessProxy_DataTaskWillPerformHTTPRedirection,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcessProxy_DeleteWebsiteDataInUIProcessForRegistrableDomains,
#endif
    NetworkProcessProxy_DeleteWebsiteDataInWebProcessesForOrigin,
    NetworkProcessProxy_DidBlockLoadToKnownTracker,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcessProxy_DidCommitCrossSiteLoadWithDataTransferFromPrevalentResource,
#endif
#if USE(SOUP)
    NetworkProcessProxy_DidExceedMemoryLimit,
#endif
    NetworkProcessProxy_DidNegotiateModernTLS,
    NetworkProcessProxy_DidReceiveAuthenticationChallenge,
#if ENABLE(SERVICE_WORKER)
    NetworkProcessProxy_EndServiceWorkerBackgroundProcessing,
#endif
    NetworkProcessProxy_EstablishRemoteWorkerContextConnectionToNetworkProcess,
#if ENABLE(APP_BOUND_DOMAINS)
    NetworkProcessProxy_GetAppBoundDomains,
#endif
#if ENABLE(APPLE_PAY_REMOTE_UI_USES_SCENE)
    NetworkProcessProxy_GetWindowSceneIdentifierForPaymentPresentation,
#endif
    NetworkProcessProxy_IncreaseQuota,
    NetworkProcessProxy_LogDiagnosticMessage,
    NetworkProcessProxy_LogDiagnosticMessageWithResult,
    NetworkProcessProxy_LogDiagnosticMessageWithValue,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcessProxy_LogTestingEvent,
#endif
    NetworkProcessProxy_NavigateServiceWorkerClient,
    NetworkProcessProxy_NegotiatedLegacyTLS,
#if ENABLE(SERVICE_WORKER)
    NetworkProcessProxy_NotifyBackgroundFetchChange,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcessProxy_NotifyResourceLoadStatisticsProcessed,
    NetworkProcessProxy_NotifyWebsiteDataDeletionForRegistrableDomainsFinished,
    NetworkProcessProxy_NotifyWebsiteDataScanForRegistrableDomainsFinished,
#endif
    NetworkProcessProxy_OpenWindowFromServiceWorker,
    NetworkProcessProxy_RegisterRemoteWorkerClientProcess,
    NetworkProcessProxy_ReloadExecutionContextsForOrigin,
    NetworkProcessProxy_RemoteWorkerContextConnectionNoLongerNeeded,
    NetworkProcessProxy_ReportConsoleMessage,
#if ENABLE(NETWORK_ISSUE_REPORTING)
    NetworkProcessProxy_ReportNetworkIssue,
#endif
#if ENABLE(SERVICE_WORKER)
    NetworkProcessProxy_RequestBackgroundFetchPermission,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcessProxy_RequestStorageAccessConfirm,
#endif
    NetworkProcessProxy_RequestStorageSpace,
    NetworkProcessProxy_ResourceLoadDidCompleteWithError,
    NetworkProcessProxy_ResourceLoadDidPerformHTTPRedirection,
    NetworkProcessProxy_ResourceLoadDidReceiveChallenge,
    NetworkProcessProxy_ResourceLoadDidReceiveResponse,
    NetworkProcessProxy_ResourceLoadDidSendRequest,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcessProxy_SetDomainsWithCrossPageStorageAccess,
    NetworkProcessProxy_SetDomainsWithUserInteraction,
#endif
    NetworkProcessProxy_SetWebProcessHasUploads,
#if ENABLE(SERVICE_WORKER)
    NetworkProcessProxy_StartServiceWorkerBackgroundProcessing,
#endif
    NetworkProcessProxy_TerminateUnresponsiveServiceWorkerProcesses,
    NetworkProcessProxy_TerminateWebProcess,
    NetworkProcessProxy_TriggerBrowsingContextGroupSwitchForNavigation,
    NetworkProcessProxy_UnregisterRemoteWorkerClientProcess,
#if USE(RUNNINGBOARD)
    NetworkProcessProxy_WakeUpWebProcessForIPC,
#endif
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_AbortBackgroundFetch,
#endif
    NetworkProcess_AddAllowedFirstPartyForCookies,
    NetworkProcess_AddWebPageNetworkParameters,
    NetworkProcess_AddWebsiteDataStore,
    NetworkProcess_AllowSpecificHTTPSCertificateForHost,
    NetworkProcess_AllowTLSCertificateChainForLocalPCMTesting,
#if PLATFORM(COCOA)
    NetworkProcess_AppPrivacyReportTestingData,
#endif
    NetworkProcess_ApplicationDidEnterBackground,
    NetworkProcess_ApplicationWillEnterForeground,
    NetworkProcess_CancelDataTask,
    NetworkProcess_CancelDownload,
#if ENABLE(APP_BOUND_DOMAINS)
    NetworkProcess_ClearAppBoundSession,
#endif
#if PLATFORM(COCOA)
    NetworkProcess_ClearAppPrivacyReportTestingData,
#endif
    NetworkProcess_ClearBundleIdentifier,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_ClearPrevalentResource,
#endif
    NetworkProcess_ClearPrivateClickMeasurement,
#if HAVE(NW_PROXY_CONFIG)
    NetworkProcess_ClearProxyConfigData,
#endif
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
    NetworkProcess_ClearServiceWorkerEntitlementOverride,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_ClearUserInteraction,
#endif
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_ClickBackgroundFetch,
#endif
    NetworkProcess_CloneSessionStorageForWebPage,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_CloseITPDatabase,
#endif
    NetworkProcess_ClosePCMDatabase,
    NetworkProcess_CountNonDefaultSessionSets,
    NetworkProcess_CreateNetworkConnectionToWebProcess,
    NetworkProcess_DataTaskWithRequest,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_DeleteCookiesForTesting,
#endif
    NetworkProcess_DeletePushAndNotificationRegistration,
    NetworkProcess_DeleteWebsiteData,
    NetworkProcess_DeleteWebsiteDataForOrigins,
    NetworkProcess_DestroySession,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_DidCommitCrossSiteLoadWithDataTransfer,
#endif
    NetworkProcess_DidIncreaseQuota,
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
    NetworkProcess_DisableServiceWorkerEntitlement,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_DomainIDExistsInDatabase,
#endif
    NetworkProcess_DownloadRequest,
    NetworkProcess_DumpPrivateClickMeasurement,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_DumpResourceLoadStatistics,
#endif
    NetworkProcess_FetchWebsiteData,
    NetworkProcess_FlushCookies,
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_GetAllBackgroundFetchIdentifiers,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_GetAllStorageAccessEntries,
#endif
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_GetBackgroundFetchState,
#endif
    NetworkProcess_GetOriginsWithPushAndNotificationPermissions,
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_GetPendingPushMessages,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_GetResourceLoadStatisticsDataSummary,
    NetworkProcess_HadUserInteraction,
#endif
#if ENABLE(APP_BOUND_DOMAINS)
    NetworkProcess_HasAppBoundSession,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_HasIsolatedSession,
    NetworkProcess_HasLocalStorage,
#endif
    NetworkProcess_HasPushSubscriptionForTesting,
    NetworkProcess_InitializeNetworkProcess,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_InsertExpiredStatisticForTesting,
    NetworkProcess_IsGrandfathered,
    NetworkProcess_IsPrevalentResource,
    NetworkProcess_IsRegisteredAsRedirectingTo,
    NetworkProcess_IsRegisteredAsSubFrameUnder,
    NetworkProcess_IsRegisteredAsSubresourceUnder,
    NetworkProcess_IsRelationshipOnlyInDatabaseOnce,
    NetworkProcess_IsResourceLoadStatisticsEphemeral,
    NetworkProcess_IsVeryPrevalentResource,
    NetworkProcess_LogFrameNavigation,
    NetworkProcess_LogUserInteraction,
#endif
    NetworkProcess_MarkAttributedPrivateClickMeasurementsAsExpiredForTesting,
    NetworkProcess_MarkPrivateClickMeasurementsAsExpiredForTesting,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_MergeStatisticForTesting,
#endif
    NetworkProcess_NotifyMediaStreamingActivity,
#if ENABLE(CFPREFS_DIRECT_MODE)
    NetworkProcess_NotifyPreferencesChanged,
#endif
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_PauseBackgroundFetch,
#endif
    NetworkProcess_PreconnectTo,
#if USE(SOUP)
    NetworkProcess_PrefetchDNS,
#endif
    NetworkProcess_PrepareToSuspend,
    NetworkProcess_ProcessDidResume,
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_ProcessNotificationEvent,
    NetworkProcess_ProcessPushMessage,
#endif
#if PLATFORM(COCOA)
    NetworkProcess_PublishDownloadProgress,
#endif
    NetworkProcess_RegisterURLSchemeAsBypassingContentSecurityPolicy,
    NetworkProcess_RegisterURLSchemeAsLocal,
    NetworkProcess_RegisterURLSchemeAsNoAccess,
    NetworkProcess_RegisterURLSchemeAsSecure,
    NetworkProcess_RemoveWebPageNetworkParameters,
    NetworkProcess_RenameOriginInWebsiteData,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_ResetCacheMaxAgeCapForPrevalentResources,
    NetworkProcess_ResetCrossSiteLoadsWithLinkDecorationForTesting,
    NetworkProcess_ResetParametersToDefaultValues,
#endif
    NetworkProcess_ResetQuota,
    NetworkProcess_ResetStoragePersistedState,
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_ResumeBackgroundFetch,
#endif
    NetworkProcess_ResumeDownload,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_ScheduleClearInMemoryAndPersistent,
    NetworkProcess_ScheduleCookieBlockingUpdate,
    NetworkProcess_ScheduleStatisticsAndDataRecordsProcessing,
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(APP_BOUND_DOMAINS))
    NetworkProcess_SetAppBoundDomainsForResourceLoadStatistics,
#endif
#if PLATFORM(IOS_FAMILY)
    NetworkProcess_SetBackupExclusionPeriodForTesting,
#endif
    NetworkProcess_SetBlobRegistryTopOriginPartitioningEnabled,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetCacheMaxAgeCapForPrevalentResources,
#endif
    NetworkProcess_SetCacheModel,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetCrossSiteLoadWithLinkDecorationForTesting,
#endif
#if ENABLE(INSPECTOR_NETWORK_THROTTLING)
    NetworkProcess_SetEmulatedConditions,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetFirstPartyHostCNAMEDomainForTesting,
    NetworkProcess_SetFirstPartyWebsiteDataRemovalModeForTesting,
    NetworkProcess_SetGrandfathered,
    NetworkProcess_SetGrandfatheringTime,
#endif
#if USE(SOUP)
    NetworkProcess_SetIgnoreTLSErrors,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetIsRunningResourceLoadStatisticsTest,
    NetworkProcess_SetLastSeen,
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(MANAGED_DOMAINS))
    NetworkProcess_SetManagedDomainsForResourceLoadStatistics,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetMaxStatisticsEntries,
    NetworkProcess_SetMinimumTimeBetweenDataRecordsRemoval,
#endif
#if USE(SOUP) || USE(CURL)
    NetworkProcess_SetNetworkProxySettings,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetNotifyPagesWhenDataRecordsWereScanned,
#endif
    NetworkProcess_SetPCMFraudPreventionValuesForTesting,
#if USE(SOUP)
    NetworkProcess_SetPersistentCredentialStorageEnabled,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetPrevalentResource,
    NetworkProcess_SetPrevalentResourceForDebugMode,
#endif
    NetworkProcess_SetPrivateClickMeasurementAppBundleIDForTesting,
    NetworkProcess_SetPrivateClickMeasurementAttributionReportURLsForTesting,
    NetworkProcess_SetPrivateClickMeasurementDebugMode,
    NetworkProcess_SetPrivateClickMeasurementEphemeralMeasurementForTesting,
    NetworkProcess_SetPrivateClickMeasurementOverrideTimerForTesting,
    NetworkProcess_SetPrivateClickMeasurementTokenPublicKeyURLForTesting,
    NetworkProcess_SetPrivateClickMeasurementTokenSignatureURLForTesting,
#if HAVE(NW_PROXY_CONFIG)
    NetworkProcess_SetProxyConfigData,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetPruneEntriesDownTo,
#endif
    NetworkProcess_SetPushAndNotificationsEnabledForOrigin,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetResourceLoadStatisticsDebugMode,
    NetworkProcess_SetResourceLoadStatisticsLogTestingEvent,
    NetworkProcess_SetResourceLoadStatisticsTimeAdvanceForTesting,
#endif
    NetworkProcess_SetSessionIsControlledByAutomation,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetShouldClassifyResourcesBeforeDataRecordsRemoval,
    NetworkProcess_SetShouldDowngradeReferrerForTesting,
    NetworkProcess_SetShouldEnbleSameSiteStrictEnforcementForTesting,
    NetworkProcess_SetSubframeUnderTopFrameDomain,
    NetworkProcess_SetSubresourceUnderTopFrameDomain,
    NetworkProcess_SetSubresourceUniqueRedirectFrom,
    NetworkProcess_SetSubresourceUniqueRedirectTo,
    NetworkProcess_SetThirdPartyCNAMEDomainForTesting,
    NetworkProcess_SetThirdPartyCookieBlockingMode,
    NetworkProcess_SetTimeToLiveUserInteraction,
    NetworkProcess_SetToSameSiteStrictCookiesForTesting,
    NetworkProcess_SetTopFrameUniqueRedirectFrom,
    NetworkProcess_SetTopFrameUniqueRedirectTo,
    NetworkProcess_SetTrackingPreventionEnabled,
    NetworkProcess_SetVeryPrevalentResource,
#endif
    NetworkProcess_SimulatePrivateClickMeasurementSessionRestart,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_StatisticsDatabaseHasAllTables,
#endif
    NetworkProcess_StorePrivateClickMeasurement,
    NetworkProcess_StoreServiceWorkerRegistrations,
    NetworkProcess_SyncLocalStorage,
    NetworkProcess_TerminateRemoteWorkerContextConnectionWhenPossible,
    NetworkProcess_UpdateBundleIdentifier,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_UpdatePrevalentDomainsToBlockCookiesFor,
#endif
#if USE(SOUP)
    NetworkProcess_UserPreferredLanguagesChanged,
#endif
    NetworkProcess_WebsiteDataOriginDirectoryForTesting,
    NetworkRTCMonitor_StartUpdatingIfNeeded,
    NetworkRTCMonitor_StopUpdating,
    NetworkRTCProvider_CloseSocket,
    NetworkRTCProvider_CreateClientTCPSocket,
    NetworkRTCProvider_CreateResolver,
    NetworkRTCProvider_CreateUDPSocket,
    NetworkRTCProvider_SendToSocket,
    NetworkRTCProvider_SetPlatformTCPSocketsEnabled,
    NetworkRTCProvider_SetPlatformUDPSocketsEnabled,
    NetworkRTCProvider_SetSocketOption,
    NetworkRTCProvider_StopResolver,
    NetworkRTCProvider_WrapNewTCPConnection,
    NetworkResourceLoader_ContinueDidReceiveResponse,
    NetworkSocketChannel_Close,
    NetworkSocketChannel_SendData,
    NetworkSocketChannel_SendString,
    NetworkStorageManager_AbortOpenAndUpgradeNeeded,
    NetworkStorageManager_AbortTransaction,
    NetworkStorageManager_CacheStorageAllCaches,
    NetworkStorageManager_CacheStorageClearMemoryRepresentation,
    NetworkStorageManager_CacheStorageDereference,
    NetworkStorageManager_CacheStorageOpenCache,
    NetworkStorageManager_CacheStoragePutRecords,
    NetworkStorageManager_CacheStorageReference,
    NetworkStorageManager_CacheStorageRemoveCache,
    NetworkStorageManager_CacheStorageRemoveRecords,
    NetworkStorageManager_CacheStorageRepresentation,
    NetworkStorageManager_CacheStorageRetrieveRecords,
    NetworkStorageManager_CancelConnectToStorageArea,
    NetworkStorageManager_Clear,
    NetworkStorageManager_ClearObjectStore,
    NetworkStorageManager_CloneSessionStorageNamespace,
    NetworkStorageManager_CloseHandle,
    NetworkStorageManager_CloseSyncAccessHandle,
    NetworkStorageManager_CommitTransaction,
    NetworkStorageManager_ConnectToStorageArea,
    NetworkStorageManager_CreateIndex,
    NetworkStorageManager_CreateObjectStore,
    NetworkStorageManager_CreateSyncAccessHandle,
    NetworkStorageManager_DatabaseConnectionClosed,
    NetworkStorageManager_DatabaseConnectionPendingClose,
    NetworkStorageManager_DeleteDatabase,
    NetworkStorageManager_DeleteIndex,
    NetworkStorageManager_DeleteObjectStore,
    NetworkStorageManager_DeleteRecord,
    NetworkStorageManager_DidFinishHandlingVersionChangeTransaction,
    NetworkStorageManager_DidFireVersionChangeEvent,
    NetworkStorageManager_DisconnectFromStorageArea,
    NetworkStorageManager_EstablishTransaction,
    NetworkStorageManager_Estimate,
    NetworkStorageManager_FileSystemGetDirectory,
    NetworkStorageManager_GetAllDatabaseNamesAndVersions,
    NetworkStorageManager_GetAllRecords,
    NetworkStorageManager_GetCount,
    NetworkStorageManager_GetDirectoryHandle,
    NetworkStorageManager_GetFile,
    NetworkStorageManager_GetFileHandle,
    NetworkStorageManager_GetHandle,
    NetworkStorageManager_GetHandleNames,
    NetworkStorageManager_GetRecord,
    NetworkStorageManager_IsSameEntry,
    NetworkStorageManager_IterateCursor,
    NetworkStorageManager_Move,
    NetworkStorageManager_OpenCursor,
    NetworkStorageManager_OpenDBRequestCancelled,
    NetworkStorageManager_OpenDatabase,
    NetworkStorageManager_Persist,
    NetworkStorageManager_Persisted,
    NetworkStorageManager_PutOrAdd,
    NetworkStorageManager_RemoveEntry,
    NetworkStorageManager_RemoveItem,
    NetworkStorageManager_RenameIndex,
    NetworkStorageManager_RenameObjectStore,
    NetworkStorageManager_RequestNewCapacityForSyncAccessHandle,
    NetworkStorageManager_Resolve,
    NetworkStorageManager_SetItem,
    NotificationManagerMessageHandler_CancelNotification,
    NotificationManagerMessageHandler_ClearNotifications,
    NotificationManagerMessageHandler_DidDestroyNotification,
    NotificationManagerMessageHandler_PageWasNotifiedOfNotificationPermission,
    NotificationManagerMessageHandler_RequestSystemNotificationPermission,
    NotificationManagerMessageHandler_ShowNotification,
    PlatformXRSystemProxy_SessionDidEnd,
    PlatformXRSystemProxy_SessionDidUpdateVisibilityState,
    PlatformXRSystem_EnumerateImmersiveXRDevices,
    PlatformXRSystem_InitializeTrackingAndRendering,
    PlatformXRSystem_RequestFrame,
    PlatformXRSystem_RequestPermissionOnSessionFeatures,
    PlatformXRSystem_ShutDownTrackingAndRendering,
    PlatformXRSystem_SubmitFrame,
    RTCDataChannelRemoteManagerProxy_BufferedAmountIsDecreasing,
    RTCDataChannelRemoteManagerProxy_ChangeReadyState,
    RTCDataChannelRemoteManagerProxy_Close,
    RTCDataChannelRemoteManagerProxy_DetectError,
    RTCDataChannelRemoteManagerProxy_ReceiveData,
    RTCDataChannelRemoteManagerProxy_SendData,
    RTCDataChannelRemoteManager_BufferedAmountIsDecreasing,
    RTCDataChannelRemoteManager_ChangeReadyState,
    RTCDataChannelRemoteManager_Close,
    RTCDataChannelRemoteManager_DetectError,
    RTCDataChannelRemoteManager_ReceiveData,
    RTCDataChannelRemoteManager_SendData,
    RemoteAdapter_Destruct,
#if PLATFORM(COCOA)
    RemoteAudioDestinationManager_AudioSamplesStorageChanged,
#endif
    RemoteAudioDestinationManager_CreateAudioDestination,
    RemoteAudioDestinationManager_DeleteAudioDestination,
    RemoteAudioDestinationManager_StartAudioDestination,
    RemoteAudioDestinationManager_StopAudioDestination,
    RemoteAudioHardwareListener_AudioHardwareDidBecomeActive,
    RemoteAudioHardwareListener_AudioHardwareDidBecomeInactive,
    RemoteAudioHardwareListener_AudioOutputDeviceChanged,
    RemoteAudioMediaStreamTrackRendererInternalUnitManager_CreateUnit,
    RemoteAudioMediaStreamTrackRendererInternalUnitManager_DeleteUnit,
    RemoteAudioMediaStreamTrackRendererInternalUnitManager_SetAudioOutputDevice,
    RemoteAudioMediaStreamTrackRendererInternalUnitManager_StartUnit,
    RemoteAudioMediaStreamTrackRendererInternalUnitManager_StopUnit,
    RemoteAudioSessionProxy_BeginInterruptionRemote,
    RemoteAudioSessionProxy_EndInterruptionRemote,
    RemoteAudioSessionProxy_SetCategory,
    RemoteAudioSessionProxy_SetIsPlayingToBluetoothOverride,
    RemoteAudioSessionProxy_SetPreferredBufferSize,
    RemoteAudioSessionProxy_TriggerBeginInterruptionForTesting,
    RemoteAudioSessionProxy_TriggerEndInterruptionForTesting,
    RemoteAudioSession_BeginInterruptionRemote,
    RemoteAudioSession_ConfigurationChanged,
    RemoteAudioSession_EndInterruptionRemote,
    RemoteAudioSourceProviderManager_AudioSamplesAvailable,
    RemoteAudioSourceProviderManager_AudioStorageChanged,
    RemoteBarcodeDetector_Detect,
    RemoteBindGroupLayout_Destruct,
    RemoteBindGroupLayout_SetLabel,
    RemoteBindGroup_Destruct,
    RemoteBindGroup_SetLabel,
    RemoteBuffer_Destroy,
    RemoteBuffer_Destruct,
    RemoteBuffer_MapAsync,
    RemoteBuffer_SetLabel,
    RemoteBuffer_Unmap,
    RemoteCDMFactoryProxy_RemoveInstance,
    RemoteCDMFactoryProxy_RemoveSession,
    RemoteCDMInstanceProxy_InitializeWithConfiguration,
    RemoteCDMInstanceProxy_SetServerCertificate,
    RemoteCDMInstanceProxy_SetStorageDirectory,
    RemoteCDMInstanceSessionProxy_CloseSession,
    RemoteCDMInstanceSessionProxy_LoadSession,
    RemoteCDMInstanceSessionProxy_RemoveSessionData,
    RemoteCDMInstanceSessionProxy_RequestLicense,
    RemoteCDMInstanceSessionProxy_SetLogIdentifier,
    RemoteCDMInstanceSessionProxy_StoreRecordOfKeyUsage,
    RemoteCDMInstanceSessionProxy_UpdateLicense,
    RemoteCDMInstanceSession_SendMessage,
    RemoteCDMInstanceSession_SessionIdChanged,
    RemoteCDMInstanceSession_UpdateKeyStatuses,
    RemoteCDMInstance_UnrequestedInitializationDataReceived,
    RemoteCDMProxy_GetSupportedConfiguration,
    RemoteCDMProxy_LoadAndInitialize,
    RemoteCDMProxy_SetLogIdentifier,
    RemoteCommandBuffer_Destruct,
    RemoteCommandBuffer_SetLabel,
    RemoteCommandEncoder_BeginComputePass,
    RemoteCommandEncoder_BeginRenderPass,
    RemoteCommandEncoder_ClearBuffer,
    RemoteCommandEncoder_CopyBufferToBuffer,
    RemoteCommandEncoder_CopyBufferToTexture,
    RemoteCommandEncoder_CopyTextureToBuffer,
    RemoteCommandEncoder_CopyTextureToTexture,
    RemoteCommandEncoder_Destruct,
    RemoteCommandEncoder_Finish,
    RemoteCommandEncoder_InsertDebugMarker,
    RemoteCommandEncoder_PopDebugGroup,
    RemoteCommandEncoder_PushDebugGroup,
    RemoteCommandEncoder_ResolveQuerySet,
    RemoteCommandEncoder_SetLabel,
    RemoteCommandEncoder_WriteTimestamp,
    RemoteCompositorIntegration_Destruct,
    RemoteComputePassEncoder_Destruct,
    RemoteComputePassEncoder_Dispatch,
    RemoteComputePassEncoder_DispatchIndirect,
    RemoteComputePassEncoder_End,
    RemoteComputePassEncoder_InsertDebugMarker,
    RemoteComputePassEncoder_PopDebugGroup,
    RemoteComputePassEncoder_PushDebugGroup,
    RemoteComputePassEncoder_SetBindGroup,
    RemoteComputePassEncoder_SetLabel,
    RemoteComputePassEncoder_SetPipeline,
    RemoteComputePipeline_Destruct,
    RemoteComputePipeline_GetBindGroupLayout,
    RemoteComputePipeline_SetLabel,
    RemoteDevice_CreateBindGroup,
    RemoteDevice_CreateBindGroupLayout,
    RemoteDevice_CreateBuffer,
    RemoteDevice_CreateCommandEncoder,
    RemoteDevice_CreateComputePipeline,
    RemoteDevice_CreateComputePipelineAsync,
    RemoteDevice_CreatePipelineLayout,
    RemoteDevice_CreateQuerySet,
    RemoteDevice_CreateRenderBundleEncoder,
    RemoteDevice_CreateRenderPipeline,
    RemoteDevice_CreateRenderPipelineAsync,
    RemoteDevice_CreateSampler,
    RemoteDevice_CreateShaderModule,
    RemoteDevice_CreateTexture,
    RemoteDevice_Destroy,
    RemoteDevice_Destruct,
    RemoteDevice_ImportExternalTexture,
#if PLATFORM(COCOA) && ENABLE(VIDEO)
    RemoteDevice_ImportExternalTextureFromPixelBuffer,
#endif
    RemoteDevice_PopErrorScope,
    RemoteDevice_PushErrorScope,
    RemoteDevice_SetLabel,
#if PLATFORM(COCOA) && ENABLE(VIDEO)
    RemoteDevice_SetSharedVideoFrameMemory,
    RemoteDevice_SetSharedVideoFrameSemaphore,
#endif
    RemoteDisplayListRecorder_ApplyDeviceScaleFactor,
#if USE(CG)
    RemoteDisplayListRecorder_ApplyFillPattern,
    RemoteDisplayListRecorder_ApplyStrokePattern,
#endif
    RemoteDisplayListRecorder_BeginTransparencyLayer,
    RemoteDisplayListRecorder_ClearRect,
    RemoteDisplayListRecorder_ClearShadow,
    RemoteDisplayListRecorder_Clip,
    RemoteDisplayListRecorder_ClipOut,
    RemoteDisplayListRecorder_ClipOutRoundedRect,
    RemoteDisplayListRecorder_ClipOutToPath,
    RemoteDisplayListRecorder_ClipPath,
    RemoteDisplayListRecorder_ClipRoundedRect,
    RemoteDisplayListRecorder_ClipToImageBuffer,
    RemoteDisplayListRecorder_ConcatenateCTM,
    RemoteDisplayListRecorder_ConvertToLuminanceMask,
    RemoteDisplayListRecorder_DrawControlPart,
    RemoteDisplayListRecorder_DrawDecomposedGlyphs,
    RemoteDisplayListRecorder_DrawDotsForDocumentMarker,
    RemoteDisplayListRecorder_DrawEllipse,
    RemoteDisplayListRecorder_DrawFilteredImageBuffer,
    RemoteDisplayListRecorder_DrawFocusRingPath,
    RemoteDisplayListRecorder_DrawFocusRingRects,
    RemoteDisplayListRecorder_DrawGlyphs,
    RemoteDisplayListRecorder_DrawImageBuffer,
    RemoteDisplayListRecorder_DrawLine,
    RemoteDisplayListRecorder_DrawLinesForText,
    RemoteDisplayListRecorder_DrawNativeImage,
    RemoteDisplayListRecorder_DrawPath,
    RemoteDisplayListRecorder_DrawPattern,
    RemoteDisplayListRecorder_DrawRect,
    RemoteDisplayListRecorder_DrawSystemImage,
    RemoteDisplayListRecorder_EndTransparencyLayer,
#if ENABLE(INLINE_PATH_DATA)
    RemoteDisplayListRecorder_FillArc,
    RemoteDisplayListRecorder_FillBezierCurve,
#endif
    RemoteDisplayListRecorder_FillCompositedRect,
    RemoteDisplayListRecorder_FillEllipse,
#if ENABLE(INLINE_PATH_DATA)
    RemoteDisplayListRecorder_FillLine,
#endif
    RemoteDisplayListRecorder_FillPath,
    RemoteDisplayListRecorder_FillPathSegment,
#if ENABLE(INLINE_PATH_DATA)
    RemoteDisplayListRecorder_FillQuadCurve,
#endif
    RemoteDisplayListRecorder_FillRect,
    RemoteDisplayListRecorder_FillRectWithColor,
    RemoteDisplayListRecorder_FillRectWithGradient,
    RemoteDisplayListRecorder_FillRectWithRoundedHole,
    RemoteDisplayListRecorder_FillRoundedRect,
    RemoteDisplayListRecorder_FlushContext,
#if ENABLE(VIDEO)
    RemoteDisplayListRecorder_PaintFrameForMedia,
#endif
#if PLATFORM(COCOA) && ENABLE(VIDEO)
    RemoteDisplayListRecorder_PaintVideoFrame,
#endif
    RemoteDisplayListRecorder_ResetClip,
    RemoteDisplayListRecorder_Restore,
    RemoteDisplayListRecorder_Rotate,
    RemoteDisplayListRecorder_Save,
    RemoteDisplayListRecorder_Scale,
    RemoteDisplayListRecorder_SetCTM,
    RemoteDisplayListRecorder_SetInlineFillColor,
    RemoteDisplayListRecorder_SetInlineStrokeColor,
    RemoteDisplayListRecorder_SetLineCap,
    RemoteDisplayListRecorder_SetLineDash,
    RemoteDisplayListRecorder_SetLineJoin,
    RemoteDisplayListRecorder_SetMiterLimit,
#if PLATFORM(COCOA) && ENABLE(VIDEO)
    RemoteDisplayListRecorder_SetSharedVideoFrameMemory,
    RemoteDisplayListRecorder_SetSharedVideoFrameSemaphore,
#endif
    RemoteDisplayListRecorder_SetState,
    RemoteDisplayListRecorder_SetStrokeThickness,
#if ENABLE(INLINE_PATH_DATA)
    RemoteDisplayListRecorder_StrokeArc,
    RemoteDisplayListRecorder_StrokeBezierCurve,
#endif
    RemoteDisplayListRecorder_StrokeEllipse,
#if ENABLE(INLINE_PATH_DATA)
    RemoteDisplayListRecorder_StrokeLine,
    RemoteDisplayListRecorder_StrokeLineWithColorAndThickness,
#endif
    RemoteDisplayListRecorder_StrokePath,
    RemoteDisplayListRecorder_StrokePathSegment,
#if ENABLE(INLINE_PATH_DATA)
    RemoteDisplayListRecorder_StrokeQuadCurve,
#endif
    RemoteDisplayListRecorder_StrokeRect,
    RemoteDisplayListRecorder_TransformToColorSpace,
    RemoteDisplayListRecorder_Translate,
    RemoteExternalTexture_Destruct,
    RemoteExternalTexture_SetLabel,
    RemoteFaceDetector_Detect,
    RemoteGPUProxy_WasCreated,
    RemoteGPU_CreateCompositorIntegration,
    RemoteGPU_CreatePresentationContext,
    RemoteGraphicsContextGLProxy_WasChanged,
    RemoteGraphicsContextGLProxy_WasCreated,
    RemoteGraphicsContextGLProxy_WasLost,
    RemoteGraphicsContextGL_ActiveTexture,
    RemoteGraphicsContextGL_AttachShader,
    RemoteGraphicsContextGL_BeginQuery,
    RemoteGraphicsContextGL_BeginQueryEXT,
    RemoteGraphicsContextGL_BeginTransformFeedback,
    RemoteGraphicsContextGL_BindAttribLocation,
    RemoteGraphicsContextGL_BindBuffer,
    RemoteGraphicsContextGL_BindBufferBase,
    RemoteGraphicsContextGL_BindBufferRange,
    RemoteGraphicsContextGL_BindFramebuffer,
    RemoteGraphicsContextGL_BindRenderbuffer,
    RemoteGraphicsContextGL_BindSampler,
    RemoteGraphicsContextGL_BindTexture,
    RemoteGraphicsContextGL_BindTransformFeedback,
    RemoteGraphicsContextGL_BindVertexArray,
    RemoteGraphicsContextGL_BlendColor,
    RemoteGraphicsContextGL_BlendEquation,
    RemoteGraphicsContextGL_BlendEquationSeparate,
    RemoteGraphicsContextGL_BlendEquationSeparateiOES,
    RemoteGraphicsContextGL_BlendEquationiOES,
    RemoteGraphicsContextGL_BlendFunc,
    RemoteGraphicsContextGL_BlendFuncSeparate,
    RemoteGraphicsContextGL_BlendFuncSeparateiOES,
    RemoteGraphicsContextGL_BlendFunciOES,
    RemoteGraphicsContextGL_BlitFramebuffer,
    RemoteGraphicsContextGL_BlitFramebufferANGLE,
    RemoteGraphicsContextGL_BufferData0,
    RemoteGraphicsContextGL_BufferData1,
    RemoteGraphicsContextGL_BufferSubData,
    RemoteGraphicsContextGL_Clear,
    RemoteGraphicsContextGL_ClearBufferfi,
    RemoteGraphicsContextGL_ClearBufferfv,
    RemoteGraphicsContextGL_ClearBufferiv,
    RemoteGraphicsContextGL_ClearBufferuiv,
    RemoteGraphicsContextGL_ClearColor,
    RemoteGraphicsContextGL_ClearDepth,
    RemoteGraphicsContextGL_ClearStencil,
    RemoteGraphicsContextGL_ClientWaitEGLSyncWithFlush,
    RemoteGraphicsContextGL_ClipControlEXT,
    RemoteGraphicsContextGL_ColorMask,
    RemoteGraphicsContextGL_ColorMaskiOES,
    RemoteGraphicsContextGL_CompileShader,
    RemoteGraphicsContextGL_CompressedTexImage2D0,
    RemoteGraphicsContextGL_CompressedTexImage2D1,
    RemoteGraphicsContextGL_CompressedTexImage3D0,
    RemoteGraphicsContextGL_CompressedTexImage3D1,
    RemoteGraphicsContextGL_CompressedTexSubImage2D0,
    RemoteGraphicsContextGL_CompressedTexSubImage2D1,
    RemoteGraphicsContextGL_CompressedTexSubImage3D0,
    RemoteGraphicsContextGL_CompressedTexSubImage3D1,
    RemoteGraphicsContextGL_CopyBufferSubData,
    RemoteGraphicsContextGL_CopyTexImage2D,
    RemoteGraphicsContextGL_CopyTexSubImage2D,
    RemoteGraphicsContextGL_CopyTexSubImage3D,
    RemoteGraphicsContextGL_CullFace,
    RemoteGraphicsContextGL_DeleteBuffer,
    RemoteGraphicsContextGL_DeleteFramebuffer,
    RemoteGraphicsContextGL_DeleteProgram,
    RemoteGraphicsContextGL_DeleteQuery,
    RemoteGraphicsContextGL_DeleteQueryEXT,
    RemoteGraphicsContextGL_DeleteRenderbuffer,
    RemoteGraphicsContextGL_DeleteSampler,
    RemoteGraphicsContextGL_DeleteShader,
    RemoteGraphicsContextGL_DeleteSync,
    RemoteGraphicsContextGL_DeleteTexture,
    RemoteGraphicsContextGL_DeleteTransformFeedback,
    RemoteGraphicsContextGL_DeleteVertexArray,
    RemoteGraphicsContextGL_DepthFunc,
    RemoteGraphicsContextGL_DepthMask,
    RemoteGraphicsContextGL_DepthRange,
    RemoteGraphicsContextGL_DestroyEGLImage,
    RemoteGraphicsContextGL_DetachShader,
    RemoteGraphicsContextGL_Disable,
    RemoteGraphicsContextGL_DisableVertexAttribArray,
    RemoteGraphicsContextGL_DisableiOES,
    RemoteGraphicsContextGL_DrawArrays,
    RemoteGraphicsContextGL_DrawArraysInstanced,
    RemoteGraphicsContextGL_DrawArraysInstancedBaseInstanceANGLE,
    RemoteGraphicsContextGL_DrawBuffers,
    RemoteGraphicsContextGL_DrawBuffersEXT,
    RemoteGraphicsContextGL_DrawElements,
    RemoteGraphicsContextGL_DrawElementsInstanced,
    RemoteGraphicsContextGL_DrawElementsInstancedBaseVertexBaseInstanceANGLE,
    RemoteGraphicsContextGL_DrawRangeElements,
    RemoteGraphicsContextGL_Enable,
    RemoteGraphicsContextGL_EnableVertexAttribArray,
    RemoteGraphicsContextGL_EnableiOES,
    RemoteGraphicsContextGL_EndQuery,
    RemoteGraphicsContextGL_EndQueryEXT,
    RemoteGraphicsContextGL_EndTransformFeedback,
    RemoteGraphicsContextGL_EnsureExtensionEnabled,
    RemoteGraphicsContextGL_Finish,
    RemoteGraphicsContextGL_Flush,
    RemoteGraphicsContextGL_FramebufferRenderbuffer,
    RemoteGraphicsContextGL_FramebufferTexture2D,
    RemoteGraphicsContextGL_FramebufferTextureLayer,
    RemoteGraphicsContextGL_FrontFace,
    RemoteGraphicsContextGL_GenerateMipmap,
    RemoteGraphicsContextGL_Hint,
    RemoteGraphicsContextGL_InvalidateFramebuffer,
    RemoteGraphicsContextGL_InvalidateSubFramebuffer,
    RemoteGraphicsContextGL_LineWidth,
    RemoteGraphicsContextGL_LinkProgram,
    RemoteGraphicsContextGL_MarkContextChanged,
    RemoteGraphicsContextGL_MultiDrawArraysANGLE,
    RemoteGraphicsContextGL_MultiDrawArraysInstancedANGLE,
    RemoteGraphicsContextGL_MultiDrawArraysInstancedBaseInstanceANGLE,
    RemoteGraphicsContextGL_MultiDrawElementsANGLE,
    RemoteGraphicsContextGL_MultiDrawElementsInstancedANGLE,
    RemoteGraphicsContextGL_MultiDrawElementsInstancedBaseVertexBaseInstanceANGLE,
    RemoteGraphicsContextGL_PauseTransformFeedback,
    RemoteGraphicsContextGL_PixelStorei,
    RemoteGraphicsContextGL_PolygonModeANGLE,
    RemoteGraphicsContextGL_PolygonOffset,
    RemoteGraphicsContextGL_PolygonOffsetClampEXT,
    RemoteGraphicsContextGL_ProvokingVertexANGLE,
    RemoteGraphicsContextGL_QueryCounterEXT,
    RemoteGraphicsContextGL_ReadBuffer,
    RemoteGraphicsContextGL_ReadPixelsBufferObject,
    RemoteGraphicsContextGL_RenderbufferStorage,
    RemoteGraphicsContextGL_RenderbufferStorageMultisample,
    RemoteGraphicsContextGL_RenderbufferStorageMultisampleANGLE,
    RemoteGraphicsContextGL_Reshape,
    RemoteGraphicsContextGL_ResumeTransformFeedback,
    RemoteGraphicsContextGL_SampleCoverage,
    RemoteGraphicsContextGL_SamplerParameterf,
    RemoteGraphicsContextGL_SamplerParameteri,
    RemoteGraphicsContextGL_Scissor,
    RemoteGraphicsContextGL_SetDrawingBufferColorSpace,
#if ENABLE(VIDEO) && PLATFORM(COCOA)
    RemoteGraphicsContextGL_SetSharedVideoFrameMemory,
    RemoteGraphicsContextGL_SetSharedVideoFrameSemaphore,
#endif
    RemoteGraphicsContextGL_ShaderSource,
    RemoteGraphicsContextGL_SimulateEventForTesting,
    RemoteGraphicsContextGL_StencilFunc,
    RemoteGraphicsContextGL_StencilFuncSeparate,
    RemoteGraphicsContextGL_StencilMask,
    RemoteGraphicsContextGL_StencilMaskSeparate,
    RemoteGraphicsContextGL_StencilOp,
    RemoteGraphicsContextGL_StencilOpSeparate,
    RemoteGraphicsContextGL_TexImage2D0,
    RemoteGraphicsContextGL_TexImage2D1,
    RemoteGraphicsContextGL_TexImage3D0,
    RemoteGraphicsContextGL_TexImage3D1,
    RemoteGraphicsContextGL_TexParameterf,
    RemoteGraphicsContextGL_TexParameteri,
    RemoteGraphicsContextGL_TexStorage2D,
    RemoteGraphicsContextGL_TexStorage3D,
    RemoteGraphicsContextGL_TexSubImage2D0,
    RemoteGraphicsContextGL_TexSubImage2D1,
    RemoteGraphicsContextGL_TexSubImage3D0,
    RemoteGraphicsContextGL_TexSubImage3D1,
    RemoteGraphicsContextGL_TransformFeedbackVaryings,
    RemoteGraphicsContextGL_Uniform1f,
    RemoteGraphicsContextGL_Uniform1fv,
    RemoteGraphicsContextGL_Uniform1i,
    RemoteGraphicsContextGL_Uniform1iv,
    RemoteGraphicsContextGL_Uniform1ui,
    RemoteGraphicsContextGL_Uniform1uiv,
    RemoteGraphicsContextGL_Uniform2f,
    RemoteGraphicsContextGL_Uniform2fv,
    RemoteGraphicsContextGL_Uniform2i,
    RemoteGraphicsContextGL_Uniform2iv,
    RemoteGraphicsContextGL_Uniform2ui,
    RemoteGraphicsContextGL_Uniform2uiv,
    RemoteGraphicsContextGL_Uniform3f,
    RemoteGraphicsContextGL_Uniform3fv,
    RemoteGraphicsContextGL_Uniform3i,
    RemoteGraphicsContextGL_Uniform3iv,
    RemoteGraphicsContextGL_Uniform3ui,
    RemoteGraphicsContextGL_Uniform3uiv,
    RemoteGraphicsContextGL_Uniform4f,
    RemoteGraphicsContextGL_Uniform4fv,
    RemoteGraphicsContextGL_Uniform4i,
    RemoteGraphicsContextGL_Uniform4iv,
    RemoteGraphicsContextGL_Uniform4ui,
    RemoteGraphicsContextGL_Uniform4uiv,
    RemoteGraphicsContextGL_UniformBlockBinding,
    RemoteGraphicsContextGL_UniformMatrix2fv,
    RemoteGraphicsContextGL_UniformMatrix2x3fv,
    RemoteGraphicsContextGL_UniformMatrix2x4fv,
    RemoteGraphicsContextGL_UniformMatrix3fv,
    RemoteGraphicsContextGL_UniformMatrix3x2fv,
    RemoteGraphicsContextGL_UniformMatrix3x4fv,
    RemoteGraphicsContextGL_UniformMatrix4fv,
    RemoteGraphicsContextGL_UniformMatrix4x2fv,
    RemoteGraphicsContextGL_UniformMatrix4x3fv,
    RemoteGraphicsContextGL_UseProgram,
    RemoteGraphicsContextGL_ValidateProgram,
    RemoteGraphicsContextGL_VertexAttrib1f,
    RemoteGraphicsContextGL_VertexAttrib1fv,
    RemoteGraphicsContextGL_VertexAttrib2f,
    RemoteGraphicsContextGL_VertexAttrib2fv,
    RemoteGraphicsContextGL_VertexAttrib3f,
    RemoteGraphicsContextGL_VertexAttrib3fv,
    RemoteGraphicsContextGL_VertexAttrib4f,
    RemoteGraphicsContextGL_VertexAttrib4fv,
    RemoteGraphicsContextGL_VertexAttribDivisor,
    RemoteGraphicsContextGL_VertexAttribI4i,
    RemoteGraphicsContextGL_VertexAttribI4iv,
    RemoteGraphicsContextGL_VertexAttribI4ui,
    RemoteGraphicsContextGL_VertexAttribI4uiv,
    RemoteGraphicsContextGL_VertexAttribIPointer,
    RemoteGraphicsContextGL_VertexAttribPointer,
    RemoteGraphicsContextGL_Viewport,
    RemoteGraphicsContextGL_WaitSync,
    RemoteImageBufferProxy_DidCreateBackend,
    RemoteLegacyCDMFactoryProxy_RemoveSession,
    RemoteLegacyCDMProxy_SetPlayerId,
    RemoteLegacyCDMSessionProxy_ReleaseKeys,
    RemoteLegacyCDMSession_SendError,
    RemoteLegacyCDMSession_SendMessage,
    RemoteMediaEngineConfigurationFactoryProxy_CreateDecodingConfiguration,
    RemoteMediaEngineConfigurationFactoryProxy_CreateEncodingConfiguration,
    RemoteMediaPlayerManagerProxy_CreateMediaPlayer,
    RemoteMediaPlayerManagerProxy_DeleteMediaPlayer,
    RemoteMediaPlayerProxy_AcceleratedRenderingStateChanged,
    RemoteMediaPlayerProxy_ApplicationDidBecomeActive,
    RemoteMediaPlayerProxy_ApplicationWillResignActive,
#if ENABLE(ENCRYPTED_MEDIA)
    RemoteMediaPlayerProxy_AttemptToDecryptWithInstance,
#endif
    RemoteMediaPlayerProxy_AudioTrackSetEnabled,
    RemoteMediaPlayerProxy_BeginSimulatedHDCPError,
    RemoteMediaPlayerProxy_CancelLoad,
#if ENABLE(ENCRYPTED_MEDIA)
    RemoteMediaPlayerProxy_CdmInstanceAttached,
    RemoteMediaPlayerProxy_CdmInstanceDetached,
#endif
#if ENABLE(WEB_AUDIO)
    RemoteMediaPlayerProxy_CreateAudioSourceProvider,
#endif
    RemoteMediaPlayerProxy_DidLoadingProgress,
    RemoteMediaPlayerProxy_EndSimulatedHDCPError,
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    RemoteMediaPlayerProxy_KeyAdded,
#endif
    RemoteMediaPlayerProxy_Load,
#if ENABLE(MEDIA_SOURCE)
    RemoteMediaPlayerProxy_LoadMediaSource,
#endif
    RemoteMediaPlayerProxy_NotifyActiveSourceBuffersChanged,
    RemoteMediaPlayerProxy_NotifyTrackModeChanged,
    RemoteMediaPlayerProxy_Pause,
    RemoteMediaPlayerProxy_PauseAtHostTime,
    RemoteMediaPlayerProxy_PerformTaskAtMediaTime,
    RemoteMediaPlayerProxy_Play,
    RemoteMediaPlayerProxy_PlayAtHostTime,
    RemoteMediaPlayerProxy_PlayerContentBoxRectChanged,
    RemoteMediaPlayerProxy_PrepareForPlayback,
    RemoteMediaPlayerProxy_PrepareForRendering,
    RemoteMediaPlayerProxy_PrepareToPlay,
    RemoteMediaPlayerProxy_RequestHostingContextID,
    RemoteMediaPlayerProxy_Seek,
    RemoteMediaPlayerProxy_SeekWithTolerance,
    RemoteMediaPlayerProxy_SetBufferingPolicy,
#if ENABLE(LEGACY_ENCRYPTED_MEDIA)
    RemoteMediaPlayerProxy_SetLegacyCDMSession,
#endif
    RemoteMediaPlayerProxy_SetMuted,
    RemoteMediaPlayerProxy_SetPageIsVisible,
    RemoteMediaPlayerProxy_SetPitchCorrectionAlgorithm,
    RemoteMediaPlayerProxy_SetPreferredDynamicRangeMode,
    RemoteMediaPlayerProxy_SetPreload,
    RemoteMediaPlayerProxy_SetPresentationSize,
    RemoteMediaPlayerProxy_SetPreservesPitch,
    RemoteMediaPlayerProxy_SetPrivateBrowsingMode,
    RemoteMediaPlayerProxy_SetRate,
#if ENABLE(LEGACY_ENCRYPTED_MEDIA) && ENABLE(ENCRYPTED_MEDIA)
    RemoteMediaPlayerProxy_SetShouldContinueAfterKeyNeeded,
#endif
    RemoteMediaPlayerProxy_SetShouldDisableHDR,
    RemoteMediaPlayerProxy_SetShouldDisableSleep,
#if ENABLE(WEB_AUDIO)
    RemoteMediaPlayerProxy_SetShouldEnableAudioSourceProvider,
#endif
    RemoteMediaPlayerProxy_SetShouldMaintainAspectRatio,
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    RemoteMediaPlayerProxy_SetShouldPlayToPlaybackTarget,
#endif
#if ENABLE(VIDEO_PRESENTATION_MODE)
    RemoteMediaPlayerProxy_SetVideoFullscreenGravity,
    RemoteMediaPlayerProxy_SetVideoFullscreenMode,
#endif
#if PLATFORM(COCOA)
    RemoteMediaPlayerProxy_SetVideoInlineSizeFenced,
#endif
    RemoteMediaPlayerProxy_SetVideoPlaybackMetricsUpdateInterval,
    RemoteMediaPlayerProxy_SetVolume,
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
    RemoteMediaPlayerProxy_SetWirelessPlaybackTarget,
    RemoteMediaPlayerProxy_SetWirelessVideoPlaybackDisabled,
#endif
    RemoteMediaPlayerProxy_StartVideoFrameMetadataGathering,
    RemoteMediaPlayerProxy_StopVideoFrameMetadataGathering,
    RemoteMediaPlayerProxy_TextTrackSetMode,
    RemoteMediaPlayerProxy_TracksChanged,
#if ENABLE(VIDEO_PRESENTATION_MODE)
    RemoteMediaPlayerProxy_UpdateVideoFullscreenInlineImage,
    RemoteMediaPlayerProxy_VideoFullscreenStandbyChanged,
#endif
    RemoteMediaPlayerProxy_VideoTrackSetSelected,
#if (PLATFORM(COCOA) && !HAVE(AVSAMPLEBUFFERDISPLAYLAYER_COPYDISPLAYEDPIXELBUFFER))
    RemoteMediaPlayerProxy_WillBeAskedToPaintGL,
#endif
    RemoteMediaRecorderManager_CreateRecorder,
    RemoteMediaRecorderManager_ReleaseRecorder,
    RemoteMediaRecorder_AudioSamplesAvailable,
    RemoteMediaRecorder_AudioSamplesStorageChanged,
    RemoteMediaRecorder_FetchData,
    RemoteMediaRecorder_Pause,
    RemoteMediaRecorder_Resume,
    RemoteMediaRecorder_SetSharedVideoFrameMemory,
    RemoteMediaRecorder_SetSharedVideoFrameSemaphore,
    RemoteMediaRecorder_StopRecording,
    RemoteMediaRecorder_VideoFrameAvailable,
    RemoteMediaResourceManager_AccessControlCheckFailed,
    RemoteMediaResourceManager_DataReceived,
    RemoteMediaResourceManager_DataSent,
    RemoteMediaResourceManager_LoadFailed,
    RemoteMediaResourceManager_LoadFinished,
    RemoteMediaResourceManager_RedirectReceived,
    RemoteMediaResourceManager_ResponseReceived,
    RemoteMediaSessionCoordinatorProxy_CoordinatePause,
    RemoteMediaSessionCoordinatorProxy_CoordinatePlay,
    RemoteMediaSessionCoordinatorProxy_CoordinateSeekTo,
    RemoteMediaSessionCoordinatorProxy_CoordinateSetTrack,
    RemoteMediaSessionCoordinatorProxy_Join,
    RemoteMediaSessionCoordinatorProxy_Leave,
    RemoteMediaSessionCoordinatorProxy_PlaybackStateChanged,
    RemoteMediaSessionCoordinatorProxy_PositionStateChanged,
    RemoteMediaSessionCoordinatorProxy_ReadyStateChanged,
    RemoteMediaSessionCoordinatorProxy_TrackIdentifierChanged,
    RemoteMediaSessionCoordinator_CoordinatorStateChanged,
    RemoteMediaSessionCoordinator_PauseSession,
    RemoteMediaSessionCoordinator_PlaySession,
    RemoteMediaSessionCoordinator_SeekSessionToTime,
    RemoteMediaSessionCoordinator_SetSessionTrack,
    RemoteMediaSourceProxy_BufferedChanged,
    RemoteMediaSourceProxy_DurationChanged,
    RemoteMediaSourceProxy_MarkEndOfStream,
    RemoteMediaSourceProxy_SeekCompleted,
    RemoteMediaSourceProxy_SetIsSeeking,
    RemoteMediaSourceProxy_SetReadyState,
    RemoteMediaSourceProxy_SetTimeFudgeFactor,
    RemoteMediaSourceProxy_UnmarkEndOfStream,
    RemoteMediaSourceProxy_WaitForSeekCompleted,
    RemotePipelineLayout_Destruct,
    RemotePipelineLayout_SetLabel,
    RemotePresentationContext_Configure,
    RemotePresentationContext_GetCurrentTexture,
    RemotePresentationContext_Unconfigure,
    RemoteQuerySet_Destroy,
    RemoteQuerySet_Destruct,
    RemoteQuerySet_SetLabel,
    RemoteQueue_CopyExternalImageToTexture,
    RemoteQueue_Destruct,
    RemoteQueue_SetLabel,
    RemoteQueue_Submit,
    RemoteQueue_WriteBuffer,
    RemoteQueue_WriteTexture,
    RemoteRemoteCommandListenerProxy_UpdateSupportedCommands,
    RemoteRemoteCommandListener_DidReceiveRemoteControlCommand,
    RemoteRenderBundleEncoder_Destruct,
    RemoteRenderBundleEncoder_Draw,
    RemoteRenderBundleEncoder_DrawIndexed,
    RemoteRenderBundleEncoder_DrawIndexedIndirect,
    RemoteRenderBundleEncoder_DrawIndirect,
    RemoteRenderBundleEncoder_Finish,
    RemoteRenderBundleEncoder_InsertDebugMarker,
    RemoteRenderBundleEncoder_PopDebugGroup,
    RemoteRenderBundleEncoder_PushDebugGroup,
    RemoteRenderBundleEncoder_SetBindGroup,
    RemoteRenderBundleEncoder_SetIndexBuffer,
    RemoteRenderBundleEncoder_SetLabel,
    RemoteRenderBundleEncoder_SetPipeline,
    RemoteRenderBundleEncoder_SetVertexBuffer,
    RemoteRenderBundle_Destruct,
    RemoteRenderBundle_SetLabel,
    RemoteRenderPassEncoder_BeginOcclusionQuery,
    RemoteRenderPassEncoder_Destruct,
    RemoteRenderPassEncoder_Draw,
    RemoteRenderPassEncoder_DrawIndexed,
    RemoteRenderPassEncoder_DrawIndexedIndirect,
    RemoteRenderPassEncoder_DrawIndirect,
    RemoteRenderPassEncoder_End,
    RemoteRenderPassEncoder_EndOcclusionQuery,
    RemoteRenderPassEncoder_ExecuteBundles,
    RemoteRenderPassEncoder_InsertDebugMarker,
    RemoteRenderPassEncoder_PopDebugGroup,
    RemoteRenderPassEncoder_PushDebugGroup,
    RemoteRenderPassEncoder_SetBindGroup,
    RemoteRenderPassEncoder_SetBlendConstant,
    RemoteRenderPassEncoder_SetIndexBuffer,
    RemoteRenderPassEncoder_SetLabel,
    RemoteRenderPassEncoder_SetPipeline,
    RemoteRenderPassEncoder_SetScissorRect,
    RemoteRenderPassEncoder_SetStencilReference,
    RemoteRenderPassEncoder_SetVertexBuffer,
    RemoteRenderPassEncoder_SetViewport,
    RemoteRenderPipeline_Destruct,
    RemoteRenderPipeline_GetBindGroupLayout,
    RemoteRenderPipeline_SetLabel,
    RemoteRenderingBackendProxy_DidFinalizeRenderingUpdate,
    RemoteRenderingBackendProxy_DidInitialize,
    RemoteRenderingBackendProxy_DidMarkLayersAsVolatile,
    RemoteRenderingBackend_CacheDecomposedGlyphs,
    RemoteRenderingBackend_CacheFilter,
    RemoteRenderingBackend_CacheFont,
    RemoteRenderingBackend_CacheFontCustomPlatformData,
    RemoteRenderingBackend_CacheGradient,
    RemoteRenderingBackend_CacheNativeImage,
    RemoteRenderingBackend_CreateImageBuffer,
    RemoteRenderingBackend_CreateRemoteBarcodeDetector,
    RemoteRenderingBackend_CreateRemoteFaceDetector,
    RemoteRenderingBackend_CreateRemoteTextDetector,
    RemoteRenderingBackend_DestroyGetPixelBufferSharedMemory,
    RemoteRenderingBackend_FinalizeRenderingUpdate,
    RemoteRenderingBackend_GetRemoteBarcodeDetectorSupportedFormats,
    RemoteRenderingBackend_MarkSurfacesVolatile,
    RemoteRenderingBackend_MoveToImageBuffer,
    RemoteRenderingBackend_MoveToSerializedBuffer,
    RemoteRenderingBackend_PutPixelBufferForImageBuffer,
    RemoteRenderingBackend_ReleaseAllImageResources,
    RemoteRenderingBackend_ReleaseAllResources,
    RemoteRenderingBackend_ReleaseRemoteBarcodeDetector,
    RemoteRenderingBackend_ReleaseRemoteFaceDetector,
    RemoteRenderingBackend_ReleaseRemoteTextDetector,
    RemoteRenderingBackend_ReleaseRenderingResource,
    RemoteSampleBufferDisplayLayerManager_CreateLayer,
    RemoteSampleBufferDisplayLayerManager_ReleaseLayer,
    RemoteSampleBufferDisplayLayer_ClearVideoFrames,
    RemoteSampleBufferDisplayLayer_EnqueueVideoFrame,
    RemoteSampleBufferDisplayLayer_Flush,
    RemoteSampleBufferDisplayLayer_FlushAndRemoveImage,
    RemoteSampleBufferDisplayLayer_Pause,
    RemoteSampleBufferDisplayLayer_Play,
#if !RELEASE_LOG_DISABLED
    RemoteSampleBufferDisplayLayer_SetLogIdentifier,
#endif
    RemoteSampleBufferDisplayLayer_SetSharedVideoFrameMemory,
    RemoteSampleBufferDisplayLayer_SetSharedVideoFrameSemaphore,
    RemoteSampleBufferDisplayLayer_UpdateBoundsAndPosition,
    RemoteSampleBufferDisplayLayer_UpdateDisplayMode,
    RemoteSampler_Destruct,
    RemoteSampler_SetLabel,
    RemoteShaderModule_CompilationInfo,
    RemoteShaderModule_Destruct,
    RemoteShaderModule_SetLabel,
    RemoteSourceBufferProxy_Abort,
    RemoteSourceBufferProxy_AddTrackBuffer,
    RemoteSourceBufferProxy_Append,
    RemoteSourceBufferProxy_BufferedSamplesForTrackId,
    RemoteSourceBufferProxy_ClearTrackBuffers,
    RemoteSourceBufferProxy_ClientReadyStateChanged,
    RemoteSourceBufferProxy_EnqueuedSamplesForTrackID,
    RemoteSourceBufferProxy_MemoryPressure,
    RemoteSourceBufferProxy_ReenqueueMediaIfNeeded,
    RemoteSourceBufferProxy_RemoveCodedFrames,
    RemoteSourceBufferProxy_RemovedFromMediaSource,
    RemoteSourceBufferProxy_ResetParserState,
    RemoteSourceBufferProxy_ResetTimestampOffsetInTrackBuffers,
    RemoteSourceBufferProxy_ResetTrackBuffers,
    RemoteSourceBufferProxy_SeekToTime,
    RemoteSourceBufferProxy_SetActive,
    RemoteSourceBufferProxy_SetAllTrackBuffersNeedRandomAccess,
    RemoteSourceBufferProxy_SetAppendWindowEnd,
    RemoteSourceBufferProxy_SetAppendWindowStart,
    RemoteSourceBufferProxy_SetGroupStartTimestamp,
    RemoteSourceBufferProxy_SetGroupStartTimestampToEndTimestamp,
    RemoteSourceBufferProxy_SetMaximumQueueDepthForTrackID,
    RemoteSourceBufferProxy_SetMediaSourceEnded,
    RemoteSourceBufferProxy_SetMode,
    RemoteSourceBufferProxy_SetReadyState,
    RemoteSourceBufferProxy_SetShouldGenerateTimestamps,
    RemoteSourceBufferProxy_SetTimestampOffset,
    RemoteSourceBufferProxy_StartChangingType,
    RemoteSourceBufferProxy_UpdateTrackIds,
    RemoteTextDetector_Detect,
    RemoteTextureView_Destruct,
    RemoteTextureView_SetLabel,
    RemoteTexture_CreateView,
    RemoteTexture_Destroy,
    RemoteTexture_Destruct,
    RemoteTexture_SetLabel,
    RemoteVideoFrameObjectHeapProxyProcessor_NewConvertedVideoFrameBuffer,
    RemoteVideoFrameObjectHeapProxyProcessor_NewVideoFrameBuffer,
    RemoteVideoFrameObjectHeapProxyProcessor_SetSharedVideoFrameMemory,
    RemoteVideoFrameObjectHeapProxyProcessor_SetSharedVideoFrameSemaphore,
#if PLATFORM(COCOA)
    RemoteVideoFrameObjectHeap_GetVideoFrameBuffer,
#endif
    RemoteVideoFrameObjectHeap_ReleaseVideoFrame,
#if PLATFORM(COCOA)
    RemoteVideoFrameObjectHeap_SetSharedVideoFrameMemory,
    RemoteVideoFrameObjectHeap_SetSharedVideoFrameSemaphore,
#endif
    RemoteWebInspectorUIProxy_BringToFront,
    RemoteWebInspectorUIProxy_FrontendDidClose,
    RemoteWebInspectorUIProxy_FrontendLoaded,
    RemoteWebInspectorUIProxy_Load,
    RemoteWebInspectorUIProxy_OpenURLExternally,
    RemoteWebInspectorUIProxy_PickColorFromScreen,
    RemoteWebInspectorUIProxy_Reopen,
    RemoteWebInspectorUIProxy_ResetState,
    RemoteWebInspectorUIProxy_RevealFileExternally,
    RemoteWebInspectorUIProxy_Save,
    RemoteWebInspectorUIProxy_SendMessageToBackend,
    RemoteWebInspectorUIProxy_SetForcedAppearance,
    RemoteWebInspectorUIProxy_SetInspectorPageDeveloperExtrasEnabled,
    RemoteWebInspectorUIProxy_SetSheetRect,
    RemoteWebInspectorUIProxy_ShowCertificate,
    RemoteWebInspectorUIProxy_StartWindowDrag,
    RemoteWebInspectorUI_Initialize,
    RemoteWebInspectorUI_SendMessageToFrontend,
#if ENABLE(INSPECTOR_TELEMETRY)
    RemoteWebInspectorUI_SetDiagnosticLoggingAvailable,
#endif
    RemoteWebInspectorUI_ShowConsole,
    RemoteWebInspectorUI_ShowResources,
    RemoteWebInspectorUI_UpdateFindString,
    RemoteWebLockRegistry_DidCompleteLockRequest,
    RemoteWebLockRegistry_DidStealLock,
    SampleBufferDisplayLayer_SetDidFail,
    ServiceWorkerDownloadTask_DidFail,
    ServiceWorkerDownloadTask_DidFinish,
    ServiceWorkerDownloadTask_DidReceiveData,
    ServiceWorkerDownloadTask_DidReceiveFormData,
    ServiceWorkerFetchTask_DidFail,
    ServiceWorkerFetchTask_DidFinish,
    ServiceWorkerFetchTask_DidNotHandle,
    ServiceWorkerFetchTask_DidReceiveData,
    ServiceWorkerFetchTask_DidReceiveFormData,
    ServiceWorkerFetchTask_DidReceiveRedirectResponse,
    ServiceWorkerFetchTask_DidReceiveResponse,
    ServiceWorkerFetchTask_UsePreload,
    SourceBufferPrivateRemote_SourceBufferPrivateAppendComplete,
    SourceBufferPrivateRemote_SourceBufferPrivateBufferedChanged,
    SourceBufferPrivateRemote_SourceBufferPrivateDidDropSample,
    SourceBufferPrivateRemote_SourceBufferPrivateDidParseSample,
    SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveInitializationSegment,
    SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveRenderingError,
    SourceBufferPrivateRemote_SourceBufferPrivateDurationChanged,
    SourceBufferPrivateRemote_SourceBufferPrivateHighestPresentationTimestampChanged,
    SourceBufferPrivateRemote_SourceBufferPrivateReportExtraMemoryCost,
    SourceBufferPrivateRemote_SourceBufferPrivateStreamEndedWithDecodeError,
    SourceBufferPrivateRemote_SourceBufferPrivateTrackBuffersChanged,
    SpeechRecognitionRealtimeMediaSourceManager_CreateSource,
    SpeechRecognitionRealtimeMediaSourceManager_DeleteSource,
#if ENABLE(SANDBOX_EXTENSIONS)
    SpeechRecognitionRealtimeMediaSourceManager_GrantSandboxExtensions,
    SpeechRecognitionRealtimeMediaSourceManager_RevokeSandboxExtensions,
#endif
    SpeechRecognitionRealtimeMediaSourceManager_Start,
    SpeechRecognitionRealtimeMediaSourceManager_Stop,
    SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteAudioSamplesAvailable,
    SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteCaptureFailed,
    SpeechRecognitionRemoteRealtimeMediaSourceManager_RemoteSourceStopped,
#if PLATFORM(COCOA)
    SpeechRecognitionRemoteRealtimeMediaSourceManager_SetStorage,
#endif
    SpeechRecognitionServer_Abort,
    SpeechRecognitionServer_Invalidate,
    SpeechRecognitionServer_Start,
    SpeechRecognitionServer_Stop,
    StorageAreaMap_ClearCache,
    StorageAreaMap_DispatchStorageEvent,
    VisitedLinkStore_AddVisitedLinkHashFromPage,
    VisitedLinkTableController_AllVisitedLinkStateChanged,
    VisitedLinkTableController_RemoveAllVisitedLinks,
    VisitedLinkTableController_SetVisitedLinkTable,
    VisitedLinkTableController_VisitedLinkStateChanged,
    WebAutomationSessionProxy_ComputeElementLayout,
    WebAutomationSessionProxy_DeleteCookie,
    WebAutomationSessionProxy_EvaluateJavaScriptFunction,
    WebAutomationSessionProxy_GetComputedLabel,
    WebAutomationSessionProxy_GetComputedRole,
    WebAutomationSessionProxy_GetCookiesForFrame,
    WebAutomationSessionProxy_ResolveChildFrameWithName,
    WebAutomationSessionProxy_ResolveChildFrameWithNodeHandle,
    WebAutomationSessionProxy_ResolveChildFrameWithOrdinal,
    WebAutomationSessionProxy_ResolveParentFrame,
    WebAutomationSessionProxy_SelectOptionElement,
    WebAutomationSessionProxy_SetFilesForInputFileUpload,
    WebAutomationSessionProxy_SnapshotRectForScreenshot,
    WebAutomationSessionProxy_TakeScreenshot,
    WebAutomationSession_DidEvaluateJavaScriptFunction,
    WebAutomationSession_DidTakeScreenshot,
    WebBroadcastChannelRegistry_PostMessageToRemote,
    WebConnection_HandleMessage,
    WebCookieManager_DeleteAllCookies,
    WebCookieManager_DeleteAllCookiesModifiedSince,
    WebCookieManager_DeleteCookie,
    WebCookieManager_DeleteCookiesForHostnames,
    WebCookieManager_GetAllCookies,
    WebCookieManager_GetCookies,
    WebCookieManager_GetHTTPCookieAcceptPolicy,
    WebCookieManager_GetHostnamesWithCookies,
#if USE(SOUP)
    WebCookieManager_ReplaceCookies,
#endif
    WebCookieManager_SetCookie,
#if USE(SOUP)
    WebCookieManager_SetCookiePersistentStorage,
#endif
    WebCookieManager_SetCookies,
    WebCookieManager_SetHTTPCookieAcceptPolicy,
    WebCookieManager_StartObservingCookieChanges,
    WebCookieManager_StopObservingCookieChanges,
    WebFileSystemStorageConnection_InvalidateAccessHandle,
    WebFullScreenManagerProxy_BeganEnterFullScreen,
    WebFullScreenManagerProxy_BeganExitFullScreen,
    WebFullScreenManagerProxy_Close,
    WebFullScreenManagerProxy_EnterFullScreen,
    WebFullScreenManagerProxy_ExitFullScreen,
    WebFullScreenManager_DidEnterFullScreen,
    WebFullScreenManager_DidExitFullScreen,
    WebFullScreenManager_RequestExitFullScreen,
    WebFullScreenManager_RequestRestoreFullScreen,
    WebFullScreenManager_RestoreScrollPosition,
    WebFullScreenManager_SaveScrollPosition,
    WebFullScreenManager_SetAnimatingFullScreen,
    WebFullScreenManager_SetFullscreenAutoHideDuration,
    WebFullScreenManager_SetFullscreenControlsHidden,
    WebFullScreenManager_SetFullscreenInsets,
    WebFullScreenManager_WillEnterFullScreen,
    WebFullScreenManager_WillExitFullScreen,
    WebGeolocationManagerProxy_SetEnableHighAccuracy,
    WebGeolocationManagerProxy_StartUpdating,
    WebGeolocationManagerProxy_StopUpdating,
    WebGeolocationManager_DidChangePosition,
    WebGeolocationManager_DidFailToDeterminePosition,
#if PLATFORM(IOS_FAMILY)
    WebGeolocationManager_ResetPermissions,
#endif
    WebIDBConnectionToServer_DidAbortTransaction,
    WebIDBConnectionToServer_DidClearObjectStore,
    WebIDBConnectionToServer_DidCloseFromServer,
    WebIDBConnectionToServer_DidCommitTransaction,
    WebIDBConnectionToServer_DidCreateIndex,
    WebIDBConnectionToServer_DidCreateObjectStore,
    WebIDBConnectionToServer_DidDeleteDatabase,
    WebIDBConnectionToServer_DidDeleteIndex,
    WebIDBConnectionToServer_DidDeleteObjectStore,
    WebIDBConnectionToServer_DidDeleteRecord,
    WebIDBConnectionToServer_DidGetAllDatabaseNamesAndVersions,
    WebIDBConnectionToServer_DidGetAllRecords,
    WebIDBConnectionToServer_DidGetCount,
    WebIDBConnectionToServer_DidGetRecord,
    WebIDBConnectionToServer_DidIterateCursor,
    WebIDBConnectionToServer_DidOpenCursor,
    WebIDBConnectionToServer_DidOpenDatabase,
    WebIDBConnectionToServer_DidPutOrAdd,
    WebIDBConnectionToServer_DidRenameIndex,
    WebIDBConnectionToServer_DidRenameObjectStore,
    WebIDBConnectionToServer_DidStartTransaction,
    WebIDBConnectionToServer_FireVersionChangeEvent,
    WebIDBConnectionToServer_NotifyOpenDBRequestBlocked,
    WebInspectorInterruptDispatcher_NotifyNeedDebuggerBreak,
    WebInspectorUIProxy_AttachAvailabilityChanged,
    WebInspectorUIProxy_AttachBottom,
    WebInspectorUIProxy_AttachLeft,
    WebInspectorUIProxy_AttachRight,
    WebInspectorUIProxy_BringToFront,
    WebInspectorUIProxy_Detach,
    WebInspectorUIProxy_DidClose,
    WebInspectorUIProxy_ElementSelectionChanged,
    WebInspectorUIProxy_FrontendLoaded,
    WebInspectorUIProxy_InspectedURLChanged,
    WebInspectorUIProxy_Load,
    WebInspectorUIProxy_OpenLocalInspectorFrontend,
    WebInspectorUIProxy_OpenURLExternally,
    WebInspectorUIProxy_PickColorFromScreen,
    WebInspectorUIProxy_Reopen,
    WebInspectorUIProxy_ResetState,
    WebInspectorUIProxy_RevealFileExternally,
    WebInspectorUIProxy_Save,
    WebInspectorUIProxy_SendMessageToBackend,
    WebInspectorUIProxy_SetAttachedWindowHeight,
    WebInspectorUIProxy_SetAttachedWindowWidth,
    WebInspectorUIProxy_SetDeveloperPreferenceOverride,
#if ENABLE(INSPECTOR_NETWORK_THROTTLING)
    WebInspectorUIProxy_SetEmulatedConditions,
#endif
    WebInspectorUIProxy_SetForcedAppearance,
    WebInspectorUIProxy_SetFrontendConnection,
    WebInspectorUIProxy_SetInspectorPageDeveloperExtrasEnabled,
    WebInspectorUIProxy_SetSheetRect,
    WebInspectorUIProxy_ShowCertificate,
    WebInspectorUIProxy_StartWindowDrag,
    WebInspectorUIProxy_TimelineRecordingChanged,
    WebInspectorUI_AttachedBottom,
    WebInspectorUI_AttachedLeft,
    WebInspectorUI_AttachedRight,
    WebInspectorUI_Detached,
    WebInspectorUI_EstablishConnection,
    WebInspectorUI_EvaluateInFrontendForTesting,
    WebInspectorUI_SendMessageToFrontend,
#if ENABLE(INSPECTOR_TELEMETRY)
    WebInspectorUI_SetDiagnosticLoggingAvailable,
#endif
    WebInspectorUI_SetDockingUnavailable,
    WebInspectorUI_SetIsVisible,
    WebInspectorUI_ShowConsole,
    WebInspectorUI_ShowMainResourceForFrame,
    WebInspectorUI_ShowResources,
    WebInspectorUI_StartElementSelection,
    WebInspectorUI_StartPageProfiling,
    WebInspectorUI_StopElementSelection,
    WebInspectorUI_StopPageProfiling,
    WebInspectorUI_UpdateConnection,
    WebInspectorUI_UpdateFindString,
    WebInspector_Close,
    WebInspector_SetAttached,
    WebInspector_SetFrontendConnection,
    WebInspector_Show,
    WebInspector_ShowConsole,
    WebInspector_ShowMainResourceForFrame,
    WebInspector_ShowResources,
    WebInspector_StartElementSelection,
    WebInspector_StartPageProfiling,
    WebInspector_StopElementSelection,
    WebInspector_StopPageProfiling,
    WebLockRegistryProxy_AbortLockRequest,
    WebLockRegistryProxy_ClientIsGoingAway,
    WebLockRegistryProxy_ReleaseLock,
    WebLockRegistryProxy_RequestLock,
    WebLockRegistryProxy_Snapshot,
    WebNotificationManager_DidClickNotification,
    WebNotificationManager_DidCloseNotifications,
    WebNotificationManager_DidRemoveNotificationDecisions,
    WebNotificationManager_DidShowNotification,
    WebNotificationManager_DidUpdateNotificationDecision,
#if ENABLE(APPLE_PAY_AMS_UI)
    WebPageProxy_AbortApplePayAMSUISession,
#endif
#if ENABLE(MEDIA_USAGE)
    WebPageProxy_AddMediaUsageManagerSession,
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    WebPageProxy_AddPlaybackTargetPickerClient,
#endif
#if PLATFORM(COCOA)
    WebPageProxy_AssistiveTechnologyMakeFirstResponder,
#endif
    WebPageProxy_BackForwardAddItem,
    WebPageProxy_BackForwardClear,
#if ENABLE(MEDIA_STREAM)
    WebPageProxy_BeginMonitoringCaptureDevices,
#endif
#if USE(SYSTEM_PREVIEW)
    WebPageProxy_BeginSystemPreview,
#endif
#if ENABLE(VIDEO)
    WebPageProxy_BeginTextRecognitionForVideoInElementFullScreen,
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPageProxy_BindAccessibilityTree,
#endif
    WebPageProxy_BroadcastFrameRemovalToOtherProcesses,
#if ENABLE(VIDEO)
    WebPageProxy_CancelTextRecognitionForVideoInElementFullScreen,
#endif
#if PLATFORM(MAC)
    WebPageProxy_ChangeUniversalAccessZoomFocus,
#endif
    WebPageProxy_ClearAllEditCommands,
    WebPageProxy_ClearTextIndicator,
#if ENABLE(ATTACHMENT_ELEMENT)
    WebPageProxy_CloneAttachmentData,
#endif
    WebPageProxy_ClosePage,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_CommitPotentialTapFailed,
#endif
    WebPageProxy_CompositionWasCanceled,
    WebPageProxy_ConfigureLoggingChannel,
#if ENABLE(CONTENT_FILTERING)
    WebPageProxy_ContentFilterDidBlockLoadForFrame,
#endif
#if ENABLE(CONTENT_EXTENSIONS)
    WebPageProxy_ContentRuleListNotification,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_CouldNotRestorePageState,
#endif
    WebPageProxy_CreateInspectorTarget,
#if ENABLE(PDFKIT_PLUGIN)
    WebPageProxy_CreatePDFHUD,
#endif
    WebPageProxy_DecidePolicyForNavigationActionAsync,
    WebPageProxy_DecidePolicyForNewWindowAction,
    WebPageProxy_DecidePolicyForResponse,
    WebPageProxy_DestroyInspectorTarget,
    WebPageProxy_DidApplyLinkDecorationFiltering,
    WebPageProxy_DidCancelClientRedirectForFrame,
    WebPageProxy_DidChangeContentSize,
    WebPageProxy_DidChangeInspectorFrontendCount,
    WebPageProxy_DidChangeIntrinsicContentSize,
    WebPageProxy_DidChangeMainDocument,
    WebPageProxy_DidChangePageCount,
    WebPageProxy_DidChangeProgress,
    WebPageProxy_DidChangeProvisionalURLForFrame,
    WebPageProxy_DidChangeScrollOffsetPinningForMainFrame,
    WebPageProxy_DidChangeScrollbarsForMainFrame,
    WebPageProxy_DidChangeViewportProperties,
    WebPageProxy_DidCommitLoadForFrame,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_DidCompleteSyntheticClick,
#endif
    WebPageProxy_DidCountStringMatches,
#if HAVE(VISIBILITY_PROPAGATION_VIEW)
    WebPageProxy_DidCreateContextInWebProcessForVisibilityPropagation,
#endif
    WebPageProxy_DidCreateMainFrame,
    WebPageProxy_DidCreateSleepDisabler,
    WebPageProxy_DidCreateSubframe,
    WebPageProxy_DidDestroyNavigation,
    WebPageProxy_DidDestroySleepDisabler,
    WebPageProxy_DidDisplayInsecureContentForFrame,
#if ENABLE(DRAG_SUPPORT)
    WebPageProxy_DidEndDragging,
#endif
    WebPageProxy_DidExplicitOpenForFrame,
    WebPageProxy_DidFailLoadForFrame,
    WebPageProxy_DidFailProvisionalLoadForFrame,
    WebPageProxy_DidFailToFindString,
    WebPageProxy_DidFailToSuspendAfterProcessSwap,
    WebPageProxy_DidFindString,
    WebPageProxy_DidFindStringMatches,
    WebPageProxy_DidFindTextManipulationItems,
    WebPageProxy_DidFinishDocumentLoadForFrame,
    WebPageProxy_DidFinishLoadForFrame,
#if USE(QUICK_LOOK)
    WebPageProxy_DidFinishLoadForQuickLookDocumentInMainFrame,
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPageProxy_DidFinishLoadForResource,
#endif
    WebPageProxy_DidFinishLoadingDataForCustomContentProvider,
    WebPageProxy_DidFinishProgress,
#if ENABLE(SERVICE_WORKER)
    WebPageProxy_DidFinishServiceWorkerPageRegistration,
#endif
    WebPageProxy_DidFirstLayoutForFrame,
    WebPageProxy_DidFirstVisuallyNonEmptyLayoutForFrame,
    WebPageProxy_DidGetImageForFindMatch,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_DidGetTapHighlightGeometries,
#endif
#if PLATFORM(MAC)
    WebPageProxy_DidHandleAcceptedCandidate,
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    WebPageProxy_DidHandleAdditionalDragItemsRequest,
    WebPageProxy_DidHandleDragStartRequest,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_DidHandleTapAsHover,
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPageProxy_DidInitiateLoadForResource,
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
    WebPageProxy_DidInsertAttachmentWithIdentifier,
#endif
    WebPageProxy_DidNavigateWithNavigationData,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_DidNotHandleTapAsClick,
#endif
    WebPageProxy_DidPerformClientRedirect,
#if PLATFORM(COCOA)
    WebPageProxy_DidPerformDictionaryLookup,
#endif
#if ENABLE(DRAG_SUPPORT)
    WebPageProxy_DidPerformDragControllerAction,
    WebPageProxy_DidPerformDragOperation,
#endif
#if PLATFORM(MAC)
    WebPageProxy_DidPerformImmediateActionHitTest,
#endif
    WebPageProxy_DidPerformServerRedirect,
    WebPageProxy_DidReachLayoutMilestone,
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    WebPageProxy_DidReceiveEditDragSnapshot,
#endif
    WebPageProxy_DidReceiveEvent,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_DidReceivePositionInformation,
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPageProxy_DidReceiveResponseForResource,
#endif
    WebPageProxy_DidReceiveServerRedirectForProvisionalLoadForFrame,
    WebPageProxy_DidReceiveTitleForFrame,
#if ENABLE(ATTACHMENT_ELEMENT)
    WebPageProxy_DidRemoveAttachmentWithIdentifier,
#endif
    WebPageProxy_DidResignInputElementStrongPasswordAppearance,
    WebPageProxy_DidRestoreScrollPosition,
    WebPageProxy_DidRunInsecureContentForFrame,
    WebPageProxy_DidSameDocumentNavigationForFrame,
    WebPageProxy_DidSameDocumentNavigationForFrameViaJSHistoryAPI,
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPageProxy_DidSendRequestForResource,
#endif
#if USE(QUICK_LOOK)
    WebPageProxy_DidStartLoadForQuickLookDocumentInMainFrame,
#endif
    WebPageProxy_DidStartProgress,
    WebPageProxy_DidStartProvisionalLoadForFrame,
    WebPageProxy_DidSuspendAfterProcessSwap,
    WebPageProxy_DidUpdateActivityState,
    WebPageProxy_DidUpdateHistoryTitle,
    WebPageProxy_DidUpdateRenderingAfterCommittingLoad,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_DisableDoubleTapGesturesDuringTapIfNecessary,
    WebPageProxy_DisableInspectorNodeSearch,
#endif
#if PLATFORM(MAC)
    WebPageProxy_DismissCorrectionPanel,
#endif
    WebPageProxy_EditorStateChanged,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_ElementDidBlur,
    WebPageProxy_ElementDidFocus,
    WebPageProxy_EnableInspectorNodeSearch,
#endif
#if ENABLE(INPUT_TYPE_COLOR)
    WebPageProxy_EndColorPicker,
#endif
#if ENABLE(DATALIST_ELEMENT)
    WebPageProxy_EndDataListSuggestions,
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    WebPageProxy_EndDateTimePicker,
#endif
#if ENABLE(MEDIA_STREAM)
    WebPageProxy_EnumerateMediaDevicesForFrame,
#endif
    WebPageProxy_FixedLayoutSizeDidChange,
    WebPageProxy_FocusFromServiceWorker,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_FocusedElementDidChangeInputMode,
#endif
    WebPageProxy_FocusedFrameChanged,
    WebPageProxy_GetLoadDecisionForIcon,
#if PLATFORM(MAC)
    WebPageProxy_HandleAcceptsFirstMouse,
#endif
    WebPageProxy_HandleAutoFillButtonClick,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_HandleAutocorrectionContext,
#endif
    WebPageProxy_HandleAutoplayEvent,
#if ENABLE(DATA_DETECTION)
    WebPageProxy_HandleClickForDataDetectionResult,
#endif
#if HAVE(TRANSLATION_UI_SERVICES) && ENABLE(CONTEXT_MENUS)
    WebPageProxy_HandleContextMenuTranslation,
#endif
#if ENABLE(DATALIST_ELEMENT)
    WebPageProxy_HandleKeydownInDataList,
#endif
    WebPageProxy_HandleMessage,
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    WebPageProxy_HandleMouseDownForModelElement,
    WebPageProxy_HandleMouseMoveForModelElement,
    WebPageProxy_HandleMouseUpForModelElement,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_HandleSmartMagnificationInformationForPotentialTap,
    WebPageProxy_HideInspectorHighlight,
    WebPageProxy_HideInspectorIndication,
#endif
    WebPageProxy_HidePopupMenu,
#if PLATFORM(COCOA) || PLATFORM(GTK)
    WebPageProxy_HideValidationMessage,
#endif
    WebPageProxy_IgnoreWord,
    WebPageProxy_ImageOrMediaDocumentSizeChanged,
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    WebPageProxy_IsAnyAnimationAllowedToPlayDidChange,
#endif
    WebPageProxy_IsPlayingMediaDidChange,
    WebPageProxy_LearnWord,
    WebPageProxy_LogDiagnosticMessageFromWebProcess,
    WebPageProxy_LogDiagnosticMessageWithDomainFromWebProcess,
    WebPageProxy_LogDiagnosticMessageWithEnhancedPrivacyFromWebProcess,
    WebPageProxy_LogDiagnosticMessageWithResultFromWebProcess,
    WebPageProxy_LogDiagnosticMessageWithValueDictionaryFromWebProcess,
    WebPageProxy_LogDiagnosticMessageWithValueFromWebProcess,
    WebPageProxy_LogScrollingEvent,
    WebPageProxy_MainFramePluginHandlesPageScaleGestureDidChange,
#if PLATFORM(COCOA)
    WebPageProxy_MakeFirstResponder,
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    WebPageProxy_MockMediaPlaybackTargetPickerDismissPopup,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    WebPageProxy_ModelElementAnimationCurrentTime,
    WebPageProxy_ModelElementAnimationDuration,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    WebPageProxy_ModelElementCreateRemotePreview,
    WebPageProxy_ModelElementDestroyRemotePreview,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    WebPageProxy_ModelElementGetCamera,
    WebPageProxy_ModelElementHasAudio,
    WebPageProxy_ModelElementIsLoopingAnimation,
    WebPageProxy_ModelElementIsMuted,
    WebPageProxy_ModelElementIsPlayingAnimation,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    WebPageProxy_ModelElementLoadRemotePreview,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    WebPageProxy_ModelElementSetAnimationCurrentTime,
    WebPageProxy_ModelElementSetAnimationIsPlaying,
    WebPageProxy_ModelElementSetCamera,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_IOS)
    WebPageProxy_ModelElementSetInteractionEnabled,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    WebPageProxy_ModelElementSetIsLoopingAnimation,
    WebPageProxy_ModelElementSetIsMuted,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    WebPageProxy_ModelElementSizeDidChange,
    WebPageProxy_ModelInlinePreviewUUIDs,
#endif
    WebPageProxy_MouseDidMoveOverElement,
    WebPageProxy_NotifyScrollerThumbIsVisibleInRect,
    WebPageProxy_PageDidScroll,
    WebPageProxy_PageExtendedBackgroundColorDidChange,
    WebPageProxy_PageScaleFactorDidChange,
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    WebPageProxy_PlaybackTargetPickerClientStateDidChange,
#endif
    WebPageProxy_PluginScaleFactorDidChange,
    WebPageProxy_PluginZoomFactorDidChange,
    WebPageProxy_RecommendedScrollbarStyleDidChange,
#if PLATFORM(MAC)
    WebPageProxy_RecordAutocorrectionResponse,
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
    WebPageProxy_RegisterAttachmentIdentifier,
    WebPageProxy_RegisterAttachmentIdentifierFromData,
    WebPageProxy_RegisterAttachmentIdentifierFromFilePath,
    WebPageProxy_RegisterAttachmentsFromSerializedData,
#endif
    WebPageProxy_RegisterEditCommandForUndo,
    WebPageProxy_RegisterInsertionUndoGrouping,
#if PLATFORM(COCOA)
    WebPageProxy_RegisterWebProcessAccessibilityToken,
#endif
#if USE(DICTATION_ALTERNATIVES)
    WebPageProxy_RemoveDictationAlternatives,
#endif
#if ENABLE(MEDIA_USAGE)
    WebPageProxy_RemoveMediaUsageManagerSession,
#endif
#if ENABLE(PDFKIT_PLUGIN)
    WebPageProxy_RemovePDFHUD,
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    WebPageProxy_RemovePlaybackTargetPickerClient,
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
    WebPageProxy_RequestAttachmentIcon,
#endif
    WebPageProxy_RequestCheckingOfString,
    WebPageProxy_RequestCookieConsent,
    WebPageProxy_RequestGeolocationPermissionForFrame,
#if ENABLE(ENCRYPTED_MEDIA)
    WebPageProxy_RequestMediaKeySystemPermissionForFrame,
#endif
    WebPageProxy_RequestNotificationPermission,
#if USE(QUICK_LOOK)
    WebPageProxy_RequestPasswordForQuickLookDocumentInMainFrame,
#endif
#if ENABLE(POINTER_LOCK)
    WebPageProxy_RequestPointerLock,
    WebPageProxy_RequestPointerUnlock,
#endif
    WebPageProxy_RequestScrollToRect,
#if ENABLE(IMAGE_ANALYSIS)
    WebPageProxy_RequestTextRecognition,
#endif
#if ENABLE(MEDIA_STREAM)
    WebPageProxy_RequestUserMediaPermissionForFrame,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_RestorePageCenterAndScale,
    WebPageProxy_RestorePageState,
#endif
    WebPageProxy_RevokeGeolocationAuthorizationToken,
    WebPageProxy_RunModal,
    WebPageProxy_RunOpenPanel,
    WebPageProxy_SampledPageTopColorChanged,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_SaveImageToLibrary,
#endif
    WebPageProxy_SaveRecentSearches,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_ScrollingNodeScrollDidEndScroll,
    WebPageProxy_ScrollingNodeScrollWillStartScroll,
#endif
#if PLATFORM(COCOA)
    WebPageProxy_SearchTheWeb,
    WebPageProxy_SearchWithSpotlight,
#endif
    WebPageProxy_SendMessageToInspectorFrontend,
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPageProxy_SendMessageToWebView,
    WebPageProxy_SendMessageToWebViewWithReply,
#endif
    WebPageProxy_SetCanShortCircuitHorizontalWheelEvents,
#if ENABLE(INPUT_TYPE_COLOR)
    WebPageProxy_SetColorPickerColor,
#endif
    WebPageProxy_SetCursor,
    WebPageProxy_SetCursorHiddenUntilMouseMoves,
#if ENABLE(DATA_DETECTION)
    WebPageProxy_SetDataDetectionResult,
#endif
#if PLATFORM(MAC)
    WebPageProxy_SetEditableElementIsFocused,
#endif
    WebPageProxy_SetFocus,
    WebPageProxy_SetHasActiveAnimatedScrolls,
    WebPageProxy_SetHasExecutedAppBoundBehaviorBeforeNavigation,
    WebPageProxy_SetHasHadSelectionChangesFromUserInteraction,
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPageProxy_SetInputMethodState,
#endif
#if HAVE(TOUCH_BAR)
    WebPageProxy_SetIsNeverRichlyEditableForTouchBar,
#endif
    WebPageProxy_SetIsResizable,
#if HAVE(TOUCH_BAR)
    WebPageProxy_SetIsTouchBarUpdateSupressedForHiddenContentEditable,
#endif
    WebPageProxy_SetIsUsingHighPerformanceWebGL,
    WebPageProxy_SetMenuBarIsVisible,
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    WebPageProxy_SetMockMediaPlaybackTargetPickerEnabled,
    WebPageProxy_SetMockMediaPlaybackTargetPickerState,
#endif
#if ENABLE(VIDEO_PRESENTATION_MODE)
    WebPageProxy_SetMockVideoPresentationModeEnabled,
#endif
#if ENABLE(WEB_AUTHN)
    WebPageProxy_SetMockWebAuthenticationConfiguration,
#endif
    WebPageProxy_SetNetworkRequestsInProgress,
#if PLATFORM(COCOA) && ENABLE(DRAG_SUPPORT)
    WebPageProxy_SetPromisedDataForImage,
#endif
    WebPageProxy_SetRenderTreeSize,
    WebPageProxy_SetStatusBarIsVisible,
    WebPageProxy_SetStatusText,
    WebPageProxy_SetTextIndicator,
    WebPageProxy_SetToolbarsAreVisible,
    WebPageProxy_SetWindowFrame,
#if ENABLE(DEVICE_ORIENTATION)
    WebPageProxy_ShouldAllowDeviceOrientationAndMotionAccess,
#endif
#if ENABLE(INPUT_TYPE_COLOR)
    WebPageProxy_ShowColorPicker,
#endif
    WebPageProxy_ShowContactPicker,
#if ENABLE(CONTEXT_MENUS)
    WebPageProxy_ShowContextMenu,
#endif
#if PLATFORM(MAC)
    WebPageProxy_ShowCorrectionPanel,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_ShowDataDetectorsUIForPositionInformation,
#endif
#if ENABLE(DATALIST_ELEMENT)
    WebPageProxy_ShowDataListSuggestions,
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    WebPageProxy_ShowDateTimePicker,
#endif
#if USE(DICTATION_ALTERNATIVES)
    WebPageProxy_ShowDictationAlternativeUI,
#endif
#if PLATFORM(GTK)
    WebPageProxy_ShowEmojiPicker,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_ShowInspectorHighlight,
    WebPageProxy_ShowInspectorIndication,
#endif
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS) && USE(UICONTEXTMENU)
    WebPageProxy_ShowMediaControlsContextMenu,
#endif
    WebPageProxy_ShowPage,
#if PLATFORM(IOS_FAMILY) || ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    WebPageProxy_ShowPlaybackTargetPicker,
#endif
    WebPageProxy_ShowPopupMenu,
    WebPageProxy_ShowShareSheet,
#if (ENABLE(TELEPHONE_NUMBER_DETECTION) && PLATFORM(MAC))
    WebPageProxy_ShowTelephoneNumberMenu,
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK)
    WebPageProxy_ShowValidationMessage,
#endif
#if PLATFORM(COCOA)
    WebPageProxy_Speak,
#endif
#if ENABLE(SPEECH_SYNTHESIS)
    WebPageProxy_SpeechSynthesisCancel,
    WebPageProxy_SpeechSynthesisPause,
    WebPageProxy_SpeechSynthesisResetState,
    WebPageProxy_SpeechSynthesisResume,
    WebPageProxy_SpeechSynthesisSetFinishedCallback,
    WebPageProxy_SpeechSynthesisSpeak,
#endif
#if ENABLE(APPLE_PAY_AMS_UI)
    WebPageProxy_StartApplePayAMSUISession,
#endif
#if PLATFORM(COCOA) && ENABLE(DRAG_SUPPORT) || PLATFORM(GTK) && ENABLE(DRAG_SUPPORT)
    WebPageProxy_StartDrag,
#endif
    WebPageProxy_StartURLSchemeTask,
#if PLATFORM(COCOA)
    WebPageProxy_StopSpeaking,
#endif
    WebPageProxy_StopURLSchemeTask,
#if ENABLE(APP_HIGHLIGHTS)
    WebPageProxy_StoreAppHighlight,
#endif
    WebPageProxy_TakeFocus,
#if ENABLE(ARKIT_INLINE_PREVIEW_IOS)
    WebPageProxy_TakeModelElementFullscreen,
#endif
    WebPageProxy_ThemeColorChanged,
#if HAVE(TOUCH_BAR)
    WebPageProxy_TouchBarMenuDataChanged,
    WebPageProxy_TouchBarMenuItemDataAdded,
    WebPageProxy_TouchBarMenuItemDataRemoved,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_UpdateInputContextAfterBlurringAndRefocusingElement,
#endif
#if ENABLE(MEDIA_USAGE)
    WebPageProxy_UpdateMediaUsageManagerSessionState,
#endif
#if ENABLE(PDFKIT_PLUGIN)
    WebPageProxy_UpdatePDFHUDLocation,
#endif
    WebPageProxy_UpdateRemoteFrameSize,
    WebPageProxy_UpdateSpellingUIWithGrammarString,
    WebPageProxy_UpdateSpellingUIWithMisspelledWord,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_UpdateStringForFind,
#endif
    WebPageProxy_UseFixedLayoutDidChange,
    WebPageProxy_WillGoToBackForwardListItem,
    WebPageProxy_WillPerformClientRedirectForFrame,
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    WebPageProxy_WillReceiveEditDragSnapshot,
#endif
    WebPageProxy_WillSubmitForm,
#if (ENABLE(ATTACHMENT_ELEMENT) && PLATFORM(IOS_FAMILY))
    WebPageProxy_WritePromisedAttachmentToPasteboard,
#endif
#if USE(AUTOMATIC_TEXT_REPLACEMENT)
    WebPageProxy_toggleAutomaticDashSubstitution,
    WebPageProxy_toggleAutomaticLinkDetection,
    WebPageProxy_toggleAutomaticQuoteSubstitution,
    WebPageProxy_toggleAutomaticTextReplacement,
    WebPageProxy_toggleSmartInsertDelete,
#endif
    WebPage_AccessibilitySettingsDidChange,
    WebPage_AddConsoleMessage,
#if PLATFORM(COCOA)
    WebPage_AddDictationAlternative,
#endif
    WebPage_AddLayerForFindOverlay,
    WebPage_AddMIMETypeWithCustomContentProvider,
    WebPage_AdvanceToNextMisspelling,
#if PLATFORM(IOS_FAMILY)
    WebPage_ApplicationDidBecomeActive,
    WebPage_ApplicationDidEnterBackground,
    WebPage_ApplicationDidEnterBackgroundForMedia,
    WebPage_ApplicationDidFinishSnapshottingAfterEnteringBackground,
    WebPage_ApplicationWillEnterForeground,
    WebPage_ApplicationWillEnterForegroundForMedia,
    WebPage_ApplicationWillResignActive,
    WebPage_ApplyAutocorrection,
    WebPage_AttemptSyntheticClick,
#endif
#if PLATFORM(MAC)
    WebPage_AttributedSubstringForCharacterRangeAsync,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_AutofillLoginCredentials,
#endif
    WebPage_BeginPrinting,
    WebPage_BeginPrintingDuringDOMPrintOperation,
#if PLATFORM(IOS_FAMILY)
    WebPage_BeginSelectionInDirection,
    WebPage_BlurFocusedElement,
#endif
#if ENABLE(SPEECH_SYNTHESIS)
    WebPage_BoundaryEventOccurred,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_CancelAutoscroll,
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPage_CancelComposition,
#endif
    WebPage_CancelPointer,
#if PLATFORM(IOS_FAMILY)
    WebPage_CancelPotentialTap,
#endif
#if USE(APPKIT)
    WebPage_CapitalizeWord,
#endif
#if ENABLE(MEDIA_STREAM)
    WebPage_CaptureDevicesChanged,
#endif
    WebPage_CenterSelectionInVisibleArea,
    WebPage_ChangeFont,
    WebPage_ChangeFontAttributes,
    WebPage_ChangeListType,
    WebPage_ChangeSpellingToWord,
#if PLATFORM(COCOA)
    WebPage_CharacterIndexForPointAsync,
#endif
    WebPage_ClearAllDecoratedFoundText,
#if PLATFORM(COCOA)
    WebPage_ClearDictationAlternatives,
#endif
#if ENABLE(TRACKING_PREVENTION)
    WebPage_ClearLoadedSubresourceDomains,
#endif
#if ENABLE(NOTIFICATIONS)
    WebPage_ClearNotificationPermissionState,
#endif
    WebPage_ClearSelection,
#if PLATFORM(IOS_FAMILY)
    WebPage_ClearServiceWorkerEntitlementOverride,
#endif
    WebPage_ClearWheelEventTestMonitor,
    WebPage_Close,
#if PLATFORM(GTK)
    WebPage_CollapseSelectionInFrame,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_CommitPotentialTap,
#endif
    WebPage_CompleteTextManipulation,
    WebPage_ComputePagesForPrinting,
    WebPage_ComputePagesForPrintingDuringDOMPrintOperation,
#if PLATFORM(COCOA)
    WebPage_ConfirmCompositionAsync,
#endif
    WebPage_ConnectInspector,
#if PLATFORM(IOS_FAMILY)
    WebPage_ContentSizeCategoryDidChange,
#endif
#if ENABLE(CONTEXT_MENUS)
    WebPage_ContextMenuForKeyEvent,
#endif
    WebPage_CountStringMatches,
#if ENABLE(APP_HIGHLIGHTS)
    WebPage_CreateAppHighlightInSelectedRange,
#endif
#if ENABLE(MEDIA_SESSION_COORDINATOR)
    WebPage_CreateMediaSessionCoordinator,
#endif
    WebPage_CreateRemoteSubframe,
#if PLATFORM(MAC)
    WebPage_DataDetectorsDidChangeUI,
    WebPage_DataDetectorsDidHideUI,
    WebPage_DataDetectorsDidPresentUI,
#endif
    WebPage_DecorateTextRangeWithStyle,
    WebPage_DecreaseListLevel,
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPage_DeleteSurrounding,
#endif
#if ENABLE(DATA_DETECTION)
    WebPage_DetectDataInAllFrames,
#endif
#if PLATFORM(COCOA)
    WebPage_DictationAlternativesAtSelection,
#endif
#if ENABLE(POINTER_LOCK)
    WebPage_DidAcquirePointerLock,
#endif
    WebPage_DidBeginTextSearchOperation,
    WebPage_DidCancelCheckingText,
    WebPage_DidCancelForOpenPanel,
    WebPage_DidChangeSelectedIndexForActivePopupMenu,
#if ENABLE(INPUT_TYPE_COLOR)
    WebPage_DidChooseColor,
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    WebPage_DidChooseDate,
#endif
    WebPage_DidChooseFilesForOpenPanel,
#if PLATFORM(IOS_FAMILY)
    WebPage_DidChooseFilesForOpenPanelWithDisplayStringAndIcon,
#endif
#if ENABLE(DATALIST_ELEMENT)
    WebPage_DidCloseSuggestions,
#endif
    WebPage_DidCommitLoadInAnotherProcess,
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    WebPage_DidConcludeDrop,
#endif
#if ENABLE(CONTEXT_MENUS)
    WebPage_DidDismissContextMenu,
#endif
#if ENABLE(INPUT_TYPE_COLOR)
    WebPage_DidEndColorPicker,
#endif
#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
    WebPage_DidEndDateTimePicker,
#endif
#if PLATFORM(MAC)
    WebPage_DidEndMagnificationGesture,
#endif
    WebPage_DidEndTextSearchOperation,
    WebPage_DidFinishCheckingText,
    WebPage_DidFinishLoadInAnotherProcess,
    WebPage_DidGetLoadDecisionForIcon,
#if PLATFORM(IOS_FAMILY)
    WebPage_DidInsertFinalDictationResult,
#endif
#if ENABLE(POINTER_LOCK)
    WebPage_DidLosePointerLock,
    WebPage_DidNotAcquirePointerLock,
#endif
#if ENABLE(GEOLOCATION)
    WebPage_DidReceiveGeolocationPermissionDecision,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_DidRecognizeLongPress,
#endif
    WebPage_DidRemoveBackForwardItem,
    WebPage_DidRemoveEditCommand,
#if ENABLE(DATALIST_ELEMENT)
    WebPage_DidSelectDataListOption,
#endif
#if ENABLE(CONTEXT_MENUS)
    WebPage_DidSelectItemFromActiveContextMenu,
    WebPage_DidShowContextMenu,
#endif
#if ENABLE(DRAG_SUPPORT)
    WebPage_DidStartDrag,
#endif
    WebPage_DisconnectInspector,
#if PLATFORM(IOS_FAMILY)
    WebPage_DispatchWheelEventWithoutScrolling,
#endif
#if ENABLE(DRAG_SUPPORT)
    WebPage_DragCancelled,
    WebPage_DragEnded,
#endif
#if PLATFORM(GTK)
    WebPage_DrawPagesForPrinting,
    WebPage_DrawPagesForPrintingDuringDOMPrintOperation,
#endif
#if PLATFORM(COCOA)
    WebPage_DrawPagesToPDF,
    WebPage_DrawPagesToPDFDuringDOMPrintOperation,
    WebPage_DrawRectToImage,
    WebPage_DrawRectToImageDuringDOMPrintOperation,
#endif
#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
    WebPage_DrawToImage,
#endif
#if PLATFORM(COCOA)
    WebPage_DrawToPDF,
#endif
#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
    WebPage_DrawToPDFiOS,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_DynamicViewportSizeUpdate,
#endif
    WebPage_EffectiveAppearanceDidChange,
    WebPage_EndPrinting,
    WebPage_EndPrintingDuringDOMPrintOperation,
    WebPage_EnqueueSecurityPolicyViolationEvent,
    WebPage_ExecuteEditCommand,
    WebPage_ExecuteEditCommandWithCallback,
#if ENABLE(SANDBOX_EXTENSIONS)
    WebPage_ExtendSandboxForFilesFromOpenPanel,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_ExtendSelection,
    WebPage_ExtendSelectionForReplacement,
#endif
#if PLATFORM(GTK)
    WebPage_FailedToShowPopupMenu,
#endif
    WebPage_FindRectsForStringMatches,
    WebPage_FindString,
    WebPage_FindStringMatches,
    WebPage_FindTextRangesForStringMatches,
#if PLATFORM(COCOA)
    WebPage_FirstRectForCharacterRangeAsync,
#endif
    WebPage_FlushDeferredDidReceiveMouseEvent,
#if PLATFORM(IOS_FAMILY)
    WebPage_FocusNextFocusedElement,
    WebPage_FocusTextInputContextAndPlaceCaret,
#endif
    WebPage_ForceRepaint,
    WebPage_FrameWasRemovedInAnotherProcess,
    WebPage_FreezeLayerTreeDueToSwipeAnimation,
#if ENABLE(GAMEPAD)
    WebPage_GamepadActivity,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_GenerateSyntheticEditingCommand,
#endif
    WebPage_GenerateTestReport,
    WebPage_GetAccessibilityTreeData,
#if ENABLE(APPLICATION_MANIFEST)
    WebPage_GetApplicationManifest,
#endif
    WebPage_GetBytecodeProfile,
#if PLATFORM(COCOA)
    WebPage_GetContentsAsAttributedString,
#endif
#if ENABLE(MHTML)
    WebPage_GetContentsAsMHTMLData,
#endif
    WebPage_GetContentsAsString,
    WebPage_GetFrameInfo,
    WebPage_GetFrameTree,
    WebPage_GetImageForFindMatch,
#if ENABLE(TRACKING_PREVENTION)
    WebPage_GetLoadedSubresourceDomains,
#endif
    WebPage_GetMainResourceDataOfFrame,
#if PLATFORM(COCOA)
    WebPage_GetMarkedRangeAsync,
#endif
    WebPage_GetPDFFirstPageSize,
    WebPage_GetProcessDisplayName,
#if PLATFORM(IOS_FAMILY)
    WebPage_GetRectsAtSelectionOffsetWithText,
    WebPage_GetRectsForGranularityWithSelectionOffset,
#endif
    WebPage_GetRenderTreeExternalRepresentation,
    WebPage_GetResourceDataFromFrame,
    WebPage_GetSamplingProfilerOutput,
#if PLATFORM(COCOA)
    WebPage_GetSelectedRangeAsync,
#endif
    WebPage_GetSelectionAsWebArchiveData,
#if PLATFORM(IOS_FAMILY)
    WebPage_GetSelectionContext,
#endif
    WebPage_GetSelectionOrContentsAsString,
    WebPage_GetSourceForFrame,
    WebPage_GetTextFragmentMatch,
    WebPage_GetWebArchiveOfFrame,
    WebPage_GoToBackForwardItem,
#if PLATFORM(MAC)
    WebPage_HandleAcceptedCandidate,
#endif
#if PLATFORM(COCOA)
    WebPage_HandleAlternativeTextUIResult,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_HandleAutocorrectionContextRequest,
    WebPage_HandleDoubleTapForDoubleClickAtPoint,
    WebPage_HandleTwoFingerTapAtPoint,
#endif
    WebPage_HandleWheelEvent,
#if PLATFORM(IOS_FAMILY)
    WebPage_HardwareKeyboardAvailabilityChanged,
#endif
#if PLATFORM(COCOA)
    WebPage_HasMarkedText,
#endif
    WebPage_HideFindIndicator,
    WebPage_HideFindUI,
#if PLATFORM(MAC)
    WebPage_ImmediateActionDidCancel,
    WebPage_ImmediateActionDidComplete,
    WebPage_ImmediateActionDidUpdate,
#endif
    WebPage_IncreaseListLevel,
    WebPage_IndicateFindMatch,
#if ENABLE(ATTACHMENT_ELEMENT)
    WebPage_InsertAttachment,
#endif
#if PLATFORM(COCOA)
    WebPage_InsertDictatedTextAsync,
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    WebPage_InsertDroppedImagePlaceholders,
#endif
#if PLATFORM(COCOA)
    WebPage_InsertTextAsync,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_InsertTextPlaceholder,
    WebPage_InspectorNodeSearchEndedAtPosition,
    WebPage_InspectorNodeSearchMovedToPosition,
#endif
    WebPage_IsLayerTreeFrozen,
    WebPage_KeyEvent,
    WebPage_LastNavigationWasAppInitiated,
    WebPage_ListenForLayoutMilestones,
    WebPage_LoadAlternateHTML,
    WebPage_LoadData,
    WebPage_LoadDataInFrame,
    WebPage_LoadRequest,
    WebPage_LoadRequestWaitingForProcessLaunch,
    WebPage_LoadSimulatedRequestAndResponse,
    WebPage_LoadURLInFrame,
#if USE(APPKIT)
    WebPage_LowercaseWord,
#endif
#if ENABLE(ENCRYPTED_MEDIA)
    WebPage_MediaKeySystemWasDenied,
    WebPage_MediaKeySystemWasGranted,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_IOS)
    WebPage_ModelInlinePreviewDidFailToLoad,
    WebPage_ModelInlinePreviewDidLoad,
#endif
    WebPage_MouseEvent,
#if PLATFORM(IOS_FAMILY)
    WebPage_MoveSelectionAtBoundaryWithDirection,
    WebPage_MoveSelectionByOffset,
#endif
    WebPage_NavigateServiceWorkerClient,
    WebPage_NavigateToPDFLinkWithSimulatedClick,
    WebPage_NotifyReportObservers,
    WebPage_NotifyUserScripts,
#if ENABLE(PDFKIT_PLUGIN)
    WebPage_OpenPDFWithPreview,
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    WebPage_PauseAllAnimations,
#endif
    WebPage_PauseAllMediaPlayback,
#if PLATFORM(IOS_FAMILY)
    WebPage_PerformActionOnElement,
    WebPage_PerformActionOnElements,
#endif
#if PLATFORM(COCOA)
    WebPage_PerformDictionaryLookupAtLocation,
    WebPage_PerformDictionaryLookupOfCurrentSelection,
#endif
#if PLATFORM(GTK) && ENABLE(DRAG_SUPPORT) || !PLATFORM(GTK) && ENABLE(DRAG_SUPPORT)
    WebPage_PerformDragControllerAction,
#endif
    WebPage_PerformHitTestForMouseEvent,
#if PLATFORM(MAC)
    WebPage_PerformImmediateActionHitTestAtLocation,
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    WebPage_PlayAllAnimations,
#endif
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    WebPage_PlaybackTargetAvailabilityDidChange,
    WebPage_PlaybackTargetPickerWasDismissed,
    WebPage_PlaybackTargetSelected,
#endif
    WebPage_PostInjectedBundleMessage,
#if PLATFORM(IOS_FAMILY)
    WebPage_PotentialTapAtPosition,
#endif
    WebPage_PreferencesDidChange,
    WebPage_PreferencesDidChangeDuringDOMPrintOperation,
#if (PLATFORM(IOS_FAMILY) && ENABLE(REVEAL))
    WebPage_PrepareSelectionForContextMenuWithLocationInView,
#endif
    WebPage_ReapplyEditCommand,
#if PLATFORM(COCOA)
    WebPage_RegisterUIProcessAccessibilityTokens,
#endif
    WebPage_RegisterURLSchemeHandler,
    WebPage_Reload,
#if ENABLE(DATA_DETECTION)
    WebPage_RemoveDataDetectedLinks,
#endif
    WebPage_RemoveLayerForFindOverlay,
#if PLATFORM(IOS_FAMILY)
    WebPage_RemoveTextPlaceholder,
    WebPage_ReplaceDictatedText,
#endif
    WebPage_ReplaceFoundTextRangeWithString,
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    WebPage_ReplaceImageForRemoveBackground,
#endif
    WebPage_ReplaceMatches,
#if PLATFORM(IOS_FAMILY)
    WebPage_ReplaceSelectedText,
#endif
#if PLATFORM(COCOA)
    WebPage_ReplaceSelectionWithPasteboardData,
#endif
#if PLATFORM(MAC)
    WebPage_RequestAcceptsFirstMouse,
#endif
#if PLATFORM(COCOA)
    WebPage_RequestActiveNowPlayingSessionInfo,
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    WebPage_RequestAdditionalItemsForDragSession,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_RequestAutocorrectionData,
    WebPage_RequestDictationContext,
    WebPage_RequestDocumentEditingContext,
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    WebPage_RequestDragStart,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_RequestEvasionRectsAboveSelection,
    WebPage_RequestFocusedElementInformation,
#endif
    WebPage_RequestFontAttributesAtSelectionStart,
    WebPage_RequestImageBitmap,
    WebPage_RequestMediaPlaybackState,
#if PLATFORM(IOS_FAMILY)
    WebPage_RequestPositionInformation,
#endif
#if (PLATFORM(IOS_FAMILY) && ENABLE(REVEAL))
    WebPage_RequestRVItemInCurrentSelectedRange,
#endif
    WebPage_RequestRectForFoundTextRange,
#if ENABLE(IOS_TOUCH_EVENTS)
    WebPage_ResetPotentialTapSecurityOrigin,
#endif
#if ENABLE(APP_HIGHLIGHTS)
    WebPage_RestoreAppHighlightsAndScrollToIndex,
#endif
    WebPage_RestoreSelectionInFocusedEditableElement,
    WebPage_RestoreSession,
    WebPage_Resume,
    WebPage_ResumeActiveDOMObjectsAndAnimations,
    WebPage_ResumeAllMediaPlayback,
    WebPage_RunJavaScriptInFrameInScriptWorld,
#if ENABLE(PDFKIT_PLUGIN)
    WebPage_SavePDF,
#endif
    WebPage_ScalePage,
    WebPage_ScalePageInViewCoordinates,
    WebPage_ScaleView,
    WebPage_ScheduleFullEditorStateUpdate,
    WebPage_ScrollBy,
    WebPage_ScrollTextRangeToVisible,
    WebPage_ScrollToRect,
    WebPage_SelectAll,
    WebPage_SelectFindMatch,
#if PLATFORM(IOS_FAMILY)
    WebPage_SelectPositionAtBoundaryWithDirection,
    WebPage_SelectPositionAtPoint,
    WebPage_SelectTextWithGranularityAtPoint,
    WebPage_SelectWithGesture,
    WebPage_SelectWithTwoTouches,
    WebPage_SelectWordBackward,
#endif
#if PLATFORM(MAC)
    WebPage_SemanticContextDidChange,
#endif
    WebPage_SendMessageToTargetBackend,
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPage_SendMessageToWebProcessExtension,
    WebPage_SendMessageToWebProcessExtensionWithReply,
#endif
    WebPage_SendReportToEndpoints,
#if HAVE(APP_ACCENT_COLORS)
    WebPage_SetAccentColor,
#endif
    WebPage_SetActivityState,
#if ENABLE(ADVANCED_PRIVACY_PROTECTIONS)
    WebPage_SetAllowedQueryParametersForAdvancedPrivacyProtections,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_SetAllowsMediaDocumentInlinePlayback,
#endif
    WebPage_SetAlwaysShowsHorizontalScroller,
    WebPage_SetAlwaysShowsVerticalScroller,
#if ENABLE(APP_HIGHLIGHTS)
    WebPage_SetAppHighlightsVisibility,
#endif
    WebPage_SetAutoSizingShouldExpandToViewHeight,
    WebPage_SetBackgroundColor,
    WebPage_SetBackgroundExtendsBeyondPage,
    WebPage_SetBaseWritingDirection,
    WebPage_SetCanRunBeforeUnloadConfirmPanel,
    WebPage_SetCanRunModal,
    WebPage_SetCanShowPlaceholder,
    WebPage_SetCanUseCredentialStorage,
#if PLATFORM(MAC)
    WebPage_SetCaretAnimatorType,
    WebPage_SetCaretBlinkingSuspended,
#endif
#if PLATFORM(COCOA)
    WebPage_SetCompositionAsync,
#endif
    WebPage_SetControlledByAutomation,
    WebPage_SetCurrentHistoryItemForReattach,
    WebPage_SetCustomTextEncodingName,
    WebPage_SetDefaultUnobscuredSize,
    WebPage_SetDefersLoading,
#if PLATFORM(IOS_FAMILY)
    WebPage_SetDeviceOrientation,
#endif
    WebPage_SetEditable,
    WebPage_SetEnableHorizontalRubberBanding,
    WebPage_SetEnableVerticalRubberBanding,
    WebPage_SetFixedLayoutSize,
#if PLATFORM(IOS_FAMILY)
    WebPage_SetFocusedElementSelectedIndex,
    WebPage_SetFocusedElementValue,
#endif
#if PLATFORM(MAC)
    WebPage_SetFooterBannerHeight,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_SetForceAlwaysUserScalable,
#endif
    WebPage_SetGapBetweenPages,
    WebPage_SetHasResourceLoadClient,
#if PLATFORM(MAC)
    WebPage_SetHeaderBannerHeight,
#endif
#if ENABLE(REMOTE_INSPECTOR)
    WebPage_SetIndicating,
#endif
    WebPage_SetInitialFocus,
#if PLATFORM(IOS_FAMILY)
    WebPage_SetInsertionPointColor,
#endif
#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
    WebPage_SetInteractionRegionsEnabled,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_SetIsShowingInputViewForFocusedElement,
#endif
    WebPage_SetIsSuspended,
    WebPage_SetIsTakingSnapshotsForApplicationSuspension,
#if HAVE(UIKIT_RESIZABLE_WINDOWS)
    WebPage_SetIsWindowResizingEnabled,
#endif
    WebPage_SetLayerHostingMode,
#if ENABLE(ADVANCED_PRIVACY_PROTECTIONS)
    WebPage_SetLinkDecorationFilteringData,
#endif
#if PLATFORM(COCOA)
    WebPage_SetMainFrameIsScrollable,
#endif
    WebPage_SetMaximumUnobscuredSize,
    WebPage_SetMayStartMediaWhenInWindow,
    WebPage_SetMediaVolume,
    WebPage_SetMinimumSizeForAutoLayout,
    WebPage_SetMinimumUnobscuredSize,
#if (ENABLE(MEDIA_STREAM) && USE(GSTREAMER))
    WebPage_SetMockCaptureDevicesInterrupted,
#endif
    WebPage_SetMuted,
    WebPage_SetNeedsDOMWindowResizeEvent,
    WebPage_SetNeedsFontAttributes,
#if (ENABLE(MEDIA_STREAM) && USE(GSTREAMER))
    WebPage_SetOrientationForMediaCapture,
#endif
    WebPage_SetOverriddenMediaType,
#if PLATFORM(IOS_FAMILY)
    WebPage_SetOverrideViewportArguments,
#endif
    WebPage_SetPageAndTextZoomFactors,
    WebPage_SetPageLength,
    WebPage_SetPageZoomFactor,
    WebPage_SetPaginationBehavesLikeColumns,
    WebPage_SetPaginationMode,
#if PLATFORM(IOS_FAMILY)
    WebPage_SetScreenIsBeingCaptured,
#endif
    WebPage_SetScrollPinningBehavior,
    WebPage_SetScrollbarOverlayStyle,
    WebPage_SetShouldDispatchFakeMouseMoveEvents,
#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
    WebPage_SetShouldPlayToPlaybackTarget,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_SetShouldRevealCurrentSelectionAfterInsertion,
#endif
    WebPage_SetShouldScaleViewToFitDocument,
    WebPage_SetSizeToContentAutoSizeMaximumSize,
#if PLATFORM(COCOA)
    WebPage_SetSmartInsertDeleteEnabled,
#endif
    WebPage_SetSuppressScrollbarAnimations,
#if PLATFORM(COCOA)
    WebPage_SetTextAsync,
#endif
    WebPage_SetTextForActivePopupMenu,
    WebPage_SetTextZoomFactor,
    WebPage_SetTopContentInset,
#if PLATFORM(COCOA)
    WebPage_SetTopContentInsetFenced,
#endif
    WebPage_SetUnderPageBackgroundColorOverride,
    WebPage_SetUnderlayColor,
    WebPage_SetUseFixedLayout,
    WebPage_SetUseIconLoadingClient,
#if PLATFORM(MAC)
    WebPage_SetUseSystemAppearance,
#endif
    WebPage_SetUserAgent,
    WebPage_SetUserInterfaceLayoutDirection,
#if PLATFORM(IOS_FAMILY)
    WebPage_SetViewportConfigurationViewLayoutSize,
#endif
    WebPage_SetViewportSizeForCSSViewportUnits,
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    WebPage_ShouldAllowRemoveBackground,
#endif
    WebPage_SimulateDeviceOrientationChange,
#if ENABLE(SPEECH_SYNTHESIS)
    WebPage_SpeakingErrorOccurred,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_StartAutoscrollAtPosition,
    WebPage_StartInteractionWithElementContextOrPosition,
#endif
    WebPage_StartTextManipulations,
#if ENABLE(IMAGE_ANALYSIS)
    WebPage_StartVisualTranslation,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_StopInteraction,
#endif
    WebPage_StopLoading,
    WebPage_StopLoadingDueToProcessSwap,
    WebPage_StopMediaCapture,
#if PLATFORM(IOS_FAMILY)
    WebPage_StoreSelectionForAccessibility,
#endif
    WebPage_Suspend,
    WebPage_SuspendActiveDOMObjectsAndAnimations,
    WebPage_SuspendAllMediaPlayback,
#if USE(SYSTEM_PREVIEW)
    WebPage_SystemPreviewActionTriggered,
#endif
    WebPage_TakeSnapshot,
#if PLATFORM(IOS_FAMILY)
    WebPage_TapHighlightAtPosition,
    WebPage_TextInputContextsInRect,
#endif
#if !ENABLE(IOS_TOUCH_EVENTS) && ENABLE(TOUCH_EVENTS)
    WebPage_TouchEvent,
#endif
    WebPage_TouchWithIdentifierWasRemoved,
    WebPage_TransitionFrameToLocal,
    WebPage_TryClose,
    WebPage_TryRestoreScrollPosition,
    WebPage_URLSchemeTaskDidComplete,
    WebPage_URLSchemeTaskDidPerformRedirection,
    WebPage_URLSchemeTaskDidReceiveData,
    WebPage_URLSchemeTaskDidReceiveResponse,
    WebPage_URLSchemeTaskWillPerformRedirection,
    WebPage_UnapplyEditCommand,
    WebPage_UnfreezeLayerTreeDueToSwipeAnimation,
#if ENABLE(ATTACHMENT_ELEMENT)
    WebPage_UpdateAttachmentAttributes,
    WebPage_UpdateAttachmentIcon,
    WebPage_UpdateAttachmentThumbnail,
#endif
    WebPage_UpdateBackForwardListForReattach,
    WebPage_UpdateCORSDisablingPatterns,
    WebPage_UpdateCurrentModifierState,
    WebPage_UpdateFrameSize,
#if PLATFORM(IOS_FAMILY)
    WebPage_UpdateSelectionWithDelta,
    WebPage_UpdateSelectionWithExtentPoint,
    WebPage_UpdateSelectionWithExtentPointAndBoundary,
    WebPage_UpdateSelectionWithTouches,
#endif
    WebPage_UpdateWebsitePolicies,
#if ENABLE(IMAGE_ANALYSIS)
    WebPage_UpdateWithTextRecognitionResult,
#endif
#if USE(APPKIT)
    WebPage_UppercaseWord,
#endif
    WebPage_UseRedirectionForCurrentNavigation,
#if ENABLE(MEDIA_STREAM)
    WebPage_UserMediaAccessWasDenied,
    WebPage_UserMediaAccessWasGranted,
#endif
    WebPage_ValidateCommand,
    WebPage_ViewWillEndLiveResize,
    WebPage_ViewWillStartLiveResize,
#if ENABLE(SPEECH_SYNTHESIS)
    WebPage_VoicesDidChange,
#endif
#if ENABLE(TRACKING_PREVENTION)
    WebPage_WasLoadedWithDataTransferFromPrevalentResource,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_WillInsertFinalDictationResult,
    WebPage_WillStartUserTriggeredZooming,
#endif
#if PLATFORM(COCOA)
    WebPage_WindowAndViewFramesChanged,
#endif
    WebPage_WindowScreenDidChange,
#if ENABLE(PDFKIT_PLUGIN)
    WebPage_ZoomPDFIn,
    WebPage_ZoomPDFOut,
#endif
#if PLATFORM(GTK)
    WebPasteboardProxy_ClearClipboard,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPasteboardProxy_UpdateSupportedTypeIdentifiers,
    WebPasteboardProxy_WriteImageToPasteboard,
#endif
#if PLATFORM(IOS_FAMILY) || USE(LIBWPE)
    WebPasteboardProxy_WriteStringToPasteboard,
#endif
#if PLATFORM(GTK)
    WebPasteboardProxy_WriteToClipboard,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPasteboardProxy_WriteURLToPasteboard,
#endif
#if PLATFORM(IOS_FAMILY) || USE(LIBWPE)
    WebPasteboardProxy_WriteWebContentToPasteboard,
#endif
    WebPermissionControllerProxy_Query,
    WebPermissionController_permissionChanged,
    WebProcessPool_HandleMessage,
#if ENABLE(GAMEPAD)
    WebProcessPool_PlayGamepadEffect,
#endif
    WebProcessPool_ReportWebContentCPUTime,
#if ENABLE(GAMEPAD)
    WebProcessPool_StartedUsingGamepads,
    WebProcessPool_StopGamepadEffects,
    WebProcessPool_StoppedUsingGamepads,
#endif
#if PLATFORM(COCOA)
    WebProcessProxy_CacheMediaMIMETypes,
#endif
#if ENABLE(GPU_PROCESS)
    WebProcessProxy_CreateGPUProcessConnection,
#endif
    WebProcessProxy_CreateSpeechRecognitionServer,
    WebProcessProxy_DestroySpeechRecognitionServer,
    WebProcessProxy_DidCollectPrewarmInformation,
    WebProcessProxy_DidDestroyFrame,
    WebProcessProxy_DidDestroyUserGestureToken,
    WebProcessProxy_DidExceedActiveMemoryLimit,
    WebProcessProxy_DidExceedCPULimit,
    WebProcessProxy_DidExceedInactiveMemoryLimit,
    WebProcessProxy_DidReceiveBackgroundResponsivenessPing,
    WebProcessProxy_DisableSuddenTermination,
    WebProcessProxy_EnableSuddenTermination,
    WebProcessProxy_GetNotifications,
    WebProcessProxy_MemoryPressureStatusChanged,
    WebProcessProxy_PostMessageToRemote,
#if PLATFORM(MAC)
    WebProcessProxy_ReleaseHighPerformanceGPU,
    WebProcessProxy_RequestHighPerformanceGPU,
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebProcessProxy_SendMessageToWebContext,
    WebProcessProxy_SendMessageToWebContextWithReply,
#endif
    WebProcessProxy_SetAppBadge,
#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
    WebProcessProxy_SetCaptionDisplayMode,
    WebProcessProxy_SetCaptionLanguage,
#endif
    WebProcessProxy_SetClientBadge,
#if HAVE(CVDISPLAYLINK)
    WebProcessProxy_SetDisplayLinkPreferredFramesPerSecond,
#endif
    WebProcessProxy_SetIsHoldingLockedFiles,
#if HAVE(CVDISPLAYLINK)
    WebProcessProxy_StartDisplayLink,
    WebProcessProxy_StopDisplayLink,
#endif
    WebProcessProxy_StopResponsivenessTimer,
    WebProcessProxy_SystemBeep,
    WebProcessProxy_UpdateBackForwardItem,
#if PLATFORM(COCOA)
    WebProcess_AccessibilityPreferencesDidChange,
#endif
    WebProcess_AddAllowedFirstPartyForCookies,
#if ENABLE(MEDIA_STREAM)
    WebProcess_AddMockMediaDevice,
#endif
    WebProcess_BackgroundResponsivenessPing,
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
    WebProcess_BacklightLevelDidChange,
#endif
    WebProcess_ClearCachedPage,
    WebProcess_ClearCurrentModifierStateForTesting,
#if ENABLE(MEDIA_STREAM)
    WebProcess_ClearMockMediaDevices,
#endif
    WebProcess_ClearResourceLoadStatistics,
#if PLATFORM(MAC) || PLATFORM(MACCATALYST)
    WebProcess_ColorPreferencesDidChange,
#endif
#if HAVE(AUDIO_COMPONENT_SERVER_REGISTRATIONS)
    WebProcess_ConsumeAudioComponentRegistrations,
#endif
    WebProcess_CreateWebPage,
    WebProcess_DeleteAllCookies,
    WebProcess_DeleteWebsiteData,
    WebProcess_DeleteWebsiteDataForOrigin,
    WebProcess_DeleteWebsiteDataForOrigins,
    WebProcess_DestroyAutomationSessionProxy,
#if PLATFORM(COCOA)
    WebProcess_DidWriteToPasteboardAsynchronously,
    WebProcess_DisableURLSchemeCheckInDataDetectors,
#endif
#if PLATFORM(MAC)
    WebProcess_DisplayConfigurationChanged,
#endif
#if HAVE(CVDISPLAYLINK)
    WebProcess_DisplayDidRefresh,
#endif
#if (PLATFORM(COCOA) && ENABLE(REMOTE_INSPECTOR))
    WebProcess_EnableRemoteWebInspector,
#endif
    WebProcess_EnsureAutomationSessionProxy,
    WebProcess_EstablishRemoteWorkerContextConnectionToNetworkProcess,
    WebProcess_FetchWebsiteData,
    WebProcess_FullKeyboardAccessModeChanged,
#if ENABLE(GAMEPAD)
    WebProcess_GamepadConnected,
    WebProcess_GamepadDisconnected,
#endif
    WebProcess_GarbageCollectJavaScriptObjects,
    WebProcess_GetActivePagesOriginsForTesting,
    WebProcess_GrantAccessToAssetServices,
#if (ENABLE(MEDIA_STREAM) && ENABLE(SANDBOX_EXTENSIONS))
    WebProcess_GrantUserMediaDeviceSandboxExtensions,
#endif
    WebProcess_HandleInjectedBundleMessage,
    WebProcess_InitializeWebProcess,
    WebProcess_IsJITEnabled,
    WebProcess_MarkIsNoLongerPrewarmed,
#if (PLATFORM(COCOA) && ENABLE(CFPREFS_DIRECT_MODE))
    WebProcess_NotifyPreferencesChanged,
#endif
#if PLATFORM(MAC)
    WebProcess_OpenDirectoryCacheInvalidated,
#endif
#if PLATFORM(COCOA)
    WebProcess_PowerSourceDidChange,
#endif
    WebProcess_PrepareToSuspend,
    WebProcess_PrewarmWithDomainInformation,
    WebProcess_ProcessDidResume,
    WebProcess_RegisterURLSchemeAsBypassingContentSecurityPolicy,
    WebProcess_RegisterURLSchemeAsCORSEnabled,
    WebProcess_RegisterURLSchemeAsCachePartitioned,
    WebProcess_RegisterURLSchemeAsCanDisplayOnlyIfCanRequest,
    WebProcess_RegisterURLSchemeAsDisplayIsolated,
    WebProcess_RegisterURLSchemeAsEmptyDocument,
    WebProcess_RegisterURLSchemeAsLocal,
    WebProcess_RegisterURLSchemeAsNoAccess,
    WebProcess_RegisterURLSchemeAsSecure,
    WebProcess_ReleaseMemory,
    WebProcess_ReloadExecutionContextsForOrigin,
    WebProcess_RemotePostMessage,
#if ENABLE(MEDIA_STREAM)
    WebProcess_RemoveMockMediaDevice,
    WebProcess_ResetMockMediaDevices,
#endif
    WebProcess_RevokeAccessToAssetServices,
#if (ENABLE(MEDIA_STREAM) && ENABLE(SANDBOX_EXTENSIONS))
    WebProcess_RevokeUserMediaDeviceSandboxExtensions,
#endif
#if PLATFORM(MAC)
    WebProcess_ScrollerStylePreferenceChanged,
#endif
#if ENABLE(TRACKING_PREVENTION)
    WebProcess_SeedResourceLoadStatisticsForTesting,
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebProcess_SendMessageToWebProcessExtension,
#endif
#if ENABLE(TRACKING_PREVENTION)
    WebProcess_SendResourceLoadStatisticsDataImmediately,
#endif
    WebProcess_SetAlwaysUsesComplexTextCodePath,
    WebProcess_SetBackForwardCacheCapacity,
    WebProcess_SetCacheModel,
    WebProcess_SetDefaultRequestTimeoutInterval,
    WebProcess_SetDisableFontSubpixelAntialiasingForTesting,
    WebProcess_SetDomainRelaxationForbiddenForURLScheme,
#if ENABLE(TRACKING_PREVENTION)
    WebProcess_SetDomainsWithCrossPageStorageAccess,
    WebProcess_SetDomainsWithUserInteraction,
#endif
#if ENABLE(SERVICE_CONTROLS)
    WebProcess_SetEnabledServices,
#endif
    WebProcess_SetEnhancedAccessibility,
#if HAVE(MOUSE_DEVICE_OBSERVATION)
    WebProcess_SetHasMouseDevice,
#endif
#if HAVE(STYLUS_DEVICE_OBSERVATION)
    WebProcess_SetHasStylusDevice,
#endif
    WebProcess_SetHasSuspendedPageProxy,
    WebProcess_SetHiddenPageDOMTimerThrottlingIncreaseLimit,
#if ENABLE(GAMEPAD)
    WebProcess_SetInitialGamepads,
#endif
    WebProcess_SetInjectedBundleParameter,
    WebProcess_SetInjectedBundleParameters,
    WebProcess_SetIsInProcessCache,
    WebProcess_SetJavaScriptGarbageCollectorTimerEnabled,
#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
    WebProcess_SetMediaAccessibilityPreferences,
#endif
#if PLATFORM(COCOA)
    WebProcess_SetMediaMIMETypes,
#endif
    WebProcess_SetMemoryCacheDisabled,
#if ENABLE(MEDIA_STREAM)
    WebProcess_SetMockMediaDeviceIsEphemeral,
#endif
#if PLATFORM(COCOA)
    WebProcess_SetScreenProperties,
#endif
    WebProcess_SetTextCheckerState,
#if ENABLE(TRACKING_PREVENTION)
    WebProcess_SetThirdPartyCookieBlockingMode,
#endif
    WebProcess_SetTrackingPreventionEnabled,
#if PLATFORM(GTK) && !USE(GTK4)
    WebProcess_SetUseSystemAppearanceForScrollbars,
#endif
    WebProcess_SetWebsiteDataStoreParameters,
    WebProcess_StartMemorySampler,
    WebProcess_StopMemorySampler,
    WebProcess_SwitchFromStaticFontRegistryToUserFontRegistry,
#if PLATFORM(MAC)
    WebProcess_SystemDidWake,
    WebProcess_SystemWillPowerOn,
    WebProcess_SystemWillSleep,
#endif
#if PLATFORM(COCOA)
    WebProcess_UnblockServicesRequiredByAccessibility,
#endif
#if PLATFORM(IOS_FAMILY)
    WebProcess_UserInterfaceIdiomDidChange,
#endif
    WebProcess_UserPreferredLanguagesChanged,
    WebRTCMonitor_NetworksChanged,
    WebRTCResolver_ResolvedAddressError,
    WebRTCResolver_SetResolvedAddress,
#if ENABLE(CONTENT_FILTERING)
    WebResourceLoader_ContentFilterDidBlockLoad,
#endif
    WebResourceLoader_DidBlockAuthenticationChallenge,
    WebResourceLoader_DidFailResourceLoad,
    WebResourceLoader_DidFailServiceWorkerLoad,
    WebResourceLoader_DidFinishResourceLoad,
    WebResourceLoader_DidReceiveData,
#if ENABLE(SHAREABLE_RESOURCE)
    WebResourceLoader_DidReceiveResource,
#endif
    WebResourceLoader_DidReceiveResponse,
    WebResourceLoader_DidSendData,
    WebResourceLoader_ServiceWorkerDidNotHandle,
    WebResourceLoader_SetWorkerStart,
    WebResourceLoader_StopLoadingAfterXFrameOptionsOrContentSecurityPolicyDenied,
    WebResourceLoader_WillSendRequest,
    WebSWClientConnection_FireUpdateFoundEvent,
    WebSWClientConnection_FocusServiceWorkerClient,
    WebSWClientConnection_JobRejectedInServer,
    WebSWClientConnection_NotifyClientsOfControllerChange,
    WebSWClientConnection_NotifyRecordResponseBodyChunk,
    WebSWClientConnection_NotifyRecordResponseBodyEnd,
    WebSWClientConnection_PostMessageToServiceWorkerClient,
    WebSWClientConnection_RegistrationJobResolvedInServer,
    WebSWClientConnection_SetRegistrationLastUpdateTime,
    WebSWClientConnection_SetRegistrationUpdateViaCache,
    WebSWClientConnection_SetSWOriginTableIsImported,
    WebSWClientConnection_SetSWOriginTableSharedMemory,
    WebSWClientConnection_SetServiceWorkerClientIsControlled,
    WebSWClientConnection_StartScriptFetchForServer,
    WebSWClientConnection_UpdateBackgroundFetchRegistration,
    WebSWClientConnection_UpdateRegistrationState,
    WebSWClientConnection_UpdateWorkerState,
    WebSWContextManagerConnection_CancelFetch,
    WebSWContextManagerConnection_Close,
    WebSWContextManagerConnection_ContinueDidReceiveFetchResponse,
    WebSWContextManagerConnection_ConvertFetchToDownload,
#if ENABLE(SHAREABLE_RESOURCE) && PLATFORM(COCOA)
    WebSWContextManagerConnection_DidSaveScriptsToDisk,
#endif
    WebSWContextManagerConnection_FireActivateEvent,
    WebSWContextManagerConnection_FireBackgroundFetchClickEvent,
    WebSWContextManagerConnection_FireBackgroundFetchEvent,
    WebSWContextManagerConnection_FireInstallEvent,
    WebSWContextManagerConnection_FireNotificationEvent,
    WebSWContextManagerConnection_FirePushEvent,
    WebSWContextManagerConnection_InstallServiceWorker,
    WebSWContextManagerConnection_MatchAllCompleted,
    WebSWContextManagerConnection_NavigationPreloadFailed,
    WebSWContextManagerConnection_NavigationPreloadIsReady,
    WebSWContextManagerConnection_PostMessageToServiceWorker,
    WebSWContextManagerConnection_SetThrottleState,
    WebSWContextManagerConnection_SetUserAgent,
    WebSWContextManagerConnection_SkipWaitingCompleted,
    WebSWContextManagerConnection_StartFetch,
    WebSWContextManagerConnection_TerminateWorker,
    WebSWContextManagerConnection_UpdateAppInitiatedValue,
    WebSWContextManagerConnection_UpdatePreferencesStore,
    WebSWServerConnection_AbortBackgroundFetch,
    WebSWServerConnection_AddServiceWorkerRegistrationInServer,
    WebSWServerConnection_BackgroundFetchIdentifiers,
    WebSWServerConnection_BackgroundFetchInformation,
    WebSWServerConnection_DidResolveRegistrationPromise,
    WebSWServerConnection_DisableNavigationPreload,
    WebSWServerConnection_EnableNavigationPreload,
    WebSWServerConnection_FinishFetchingScriptInServer,
    WebSWServerConnection_GetNavigationPreloadState,
    WebSWServerConnection_GetPushPermissionState,
    WebSWServerConnection_GetPushSubscription,
    WebSWServerConnection_GetRegistrations,
    WebSWServerConnection_MatchBackgroundFetch,
    WebSWServerConnection_MatchRegistration,
    WebSWServerConnection_PostMessageToServiceWorker,
    WebSWServerConnection_RegisterServiceWorkerClient,
    WebSWServerConnection_RemoveServiceWorkerRegistrationInServer,
    WebSWServerConnection_RetrieveRecordResponse,
    WebSWServerConnection_RetrieveRecordResponseBody,
    WebSWServerConnection_ScheduleJobInServer,
    WebSWServerConnection_ScheduleUnregisterJobInServer,
    WebSWServerConnection_SetNavigationPreloadHeaderValue,
    WebSWServerConnection_SetThrottleState,
    WebSWServerConnection_StartBackgroundFetch,
    WebSWServerConnection_StoreRegistrationsOnDisk,
    WebSWServerConnection_SubscribeToPushService,
    WebSWServerConnection_TerminateWorkerFromClient,
    WebSWServerConnection_UnregisterServiceWorkerClient,
    WebSWServerConnection_UnsubscribeFromPushService,
    WebSWServerConnection_WhenRegistrationReady,
    WebSWServerConnection_WhenServiceWorkerIsTerminatedForTesting,
    WebSWServerToContextConnection_Claim,
    WebSWServerToContextConnection_DidFailHeartBeatCheck,
    WebSWServerToContextConnection_DidFinishActivation,
    WebSWServerToContextConnection_DidFinishInstall,
    WebSWServerToContextConnection_FindClientByVisibleIdentifier,
    WebSWServerToContextConnection_Focus,
    WebSWServerToContextConnection_MatchAll,
    WebSWServerToContextConnection_Navigate,
    WebSWServerToContextConnection_OpenWindow,
    WebSWServerToContextConnection_PostMessageToServiceWorkerClient,
    WebSWServerToContextConnection_ReportConsoleMessage,
    WebSWServerToContextConnection_ScriptContextFailedToStart,
    WebSWServerToContextConnection_ScriptContextStarted,
    WebSWServerToContextConnection_SetAsInspected,
    WebSWServerToContextConnection_SetScriptResource,
    WebSWServerToContextConnection_SetServiceWorkerHasPendingEvents,
    WebSWServerToContextConnection_SkipWaiting,
    WebSWServerToContextConnection_WorkerTerminated,
    WebScreenOrientationManagerProxy_Lock,
    WebScreenOrientationManagerProxy_SetShouldSendChangeNotification,
    WebScreenOrientationManagerProxy_Unlock,
    WebScreenOrientationManager_OrientationDidChange,
    WebSharedWorkerContextManagerConnection_Close,
    WebSharedWorkerContextManagerConnection_LaunchSharedWorker,
    WebSharedWorkerContextManagerConnection_PostConnectEvent,
    WebSharedWorkerContextManagerConnection_ResumeSharedWorker,
    WebSharedWorkerContextManagerConnection_SetUserAgent,
    WebSharedWorkerContextManagerConnection_SuspendSharedWorker,
    WebSharedWorkerContextManagerConnection_TerminateSharedWorker,
    WebSharedWorkerContextManagerConnection_UpdatePreferencesStore,
    WebSharedWorkerObjectConnection_FetchScriptInClient,
    WebSharedWorkerObjectConnection_NotifyWorkerObjectOfLoadCompletion,
    WebSharedWorkerObjectConnection_PostExceptionToWorkerObject,
    WebSharedWorkerServerConnection_RequestSharedWorker,
    WebSharedWorkerServerConnection_ResumeForBackForwardCache,
    WebSharedWorkerServerConnection_SharedWorkerObjectIsGoingAway,
    WebSharedWorkerServerConnection_SuspendForBackForwardCache,
    WebSharedWorkerServerToContextConnection_PostExceptionToWorkerObject,
    WebSharedWorkerServerToContextConnection_SharedWorkerTerminated,
    WebSocketChannel_DidClose,
    WebSocketChannel_DidConnect,
    WebSocketChannel_DidReceiveBinaryData,
    WebSocketChannel_DidReceiveHandshakeResponse,
    WebSocketChannel_DidReceiveMessageError,
    WebSocketChannel_DidReceiveText,
    WebSocketChannel_DidSendHandshakeRequest,
    WebSpeechRecognitionConnection_DidReceiveUpdate,
    WebUserContentControllerProxy_DidPostMessage,
#if ENABLE(CONTENT_EXTENSIONS)
    WebUserContentController_AddContentRuleLists,
#endif
    WebUserContentController_AddContentWorlds,
    WebUserContentController_AddUserScriptMessageHandlers,
    WebUserContentController_AddUserScripts,
    WebUserContentController_AddUserStyleSheets,
#if ENABLE(CONTENT_EXTENSIONS)
    WebUserContentController_RemoveAllContentRuleLists,
#endif
    WebUserContentController_RemoveAllUserScriptMessageHandlers,
    WebUserContentController_RemoveAllUserScriptMessageHandlersForWorlds,
    WebUserContentController_RemoveAllUserScripts,
    WebUserContentController_RemoveAllUserStyleSheets,
#if ENABLE(CONTENT_EXTENSIONS)
    WebUserContentController_RemoveContentRuleList,
#endif
    WebUserContentController_RemoveContentWorlds,
    WebUserContentController_RemoveUserScript,
    WebUserContentController_RemoveUserScriptMessageHandler,
    WebUserContentController_RemoveUserStyleSheet,
#if PLATFORM(COCOA)
    InitializeConnection,
#endif
    LegacySessionState,
    ProcessOutOfStreamMessage,
    SetStreamDestinationID,
    SyncMessageReply,
    AuxiliaryProcess_MainThreadPingReply,
    CacheStorageEngineConnection_CachesReply,
    CacheStorageEngineConnection_ClearMemoryRepresentationReply,
    CacheStorageEngineConnection_DeleteMatchingRecordsReply,
    CacheStorageEngineConnection_EngineRepresentationReply,
    CacheStorageEngineConnection_OpenReply,
    CacheStorageEngineConnection_PutRecordsReply,
    CacheStorageEngineConnection_RemoveReply,
    CacheStorageEngineConnection_RetrieveRecordsReply,
    DownloadProxy_DecideDestinationWithSuggestedFilenameReply,
    DownloadProxy_WillSendRequestReply,
#if PLATFORM(COCOA)
    DrawingArea_DispatchAfterEnsuringDrawingReply,
#endif
#if USE(COORDINATED_GRAPHICS) || USE(TEXTURE_MAPPER) || PLATFORM(COCOA)
    DrawingArea_UpdateGeometryReply,
#endif
#if ENABLE(IOS_TOUCH_EVENTS)
    EventDispatcher_TouchEventReply,
#endif
#if ENABLE(ROUTING_ARBITRATION)
    GPUProcessConnection_BeginRoutingArbitrationWithCategoryReply,
#endif
#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
    GPUProcessProxy_StatusBarWasTappedReply,
#endif
    GPUProcess_CreateGPUConnectionToWebProcessReply,
    GPUProcess_PrepareToSuspendReply,
#if HAVE(SCREEN_CAPTURE_KIT)
    GPUProcess_PromptForGetDisplayMediaReply,
#endif
#if ENABLE(VIDEO)
    GPUProcess_RequestBitmapImageForCurrentTimeReply,
#endif
#if ENABLE(MEDIA_STREAM)
    GPUProcess_UpdateCaptureAccessReply,
#endif
    GPUProcess_WebProcessConnectionCountForTestingReply,
    IPCStreamTester_AsyncMessageReply,
    IPCTesterReceiver_AsyncMessageReply,
#if PLATFORM(IOS_FAMILY)
    MediaPlayerPrivateRemote_GetRawCookiesReply,
#endif
    MediaPlayerPrivateRemote_SendH2PingReply,
    MediaSourcePrivateRemote_MediaSourcePrivateShuttingDownReply,
    NetworkBroadcastChannelRegistry_PostMessageReply,
#if ENABLE(WEB_RTC)
    NetworkConnectionToWebProcess_ConnectToRTCDataChannelRemoteSourceReply,
#endif
    NetworkConnectionToWebProcess_CookiesForDOMAsyncReply,
    NetworkConnectionToWebProcess_CreateRTCProviderReply,
    NetworkConnectionToWebProcess_DeleteCookieReply,
#if ENABLE(SERVICE_WORKER)
    NetworkConnectionToWebProcess_EstablishSWContextConnectionReply,
#endif
    NetworkConnectionToWebProcess_EstablishSharedWorkerContextConnectionReply,
#if PLATFORM(MAC)
    NetworkConnectionToWebProcess_GetProcessDisplayNameReply,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkConnectionToWebProcess_HasStorageAccessReply,
#endif
    NetworkConnectionToWebProcess_IsResourceLoadFinishedReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkConnectionToWebProcess_RequestStorageAccessReply,
    NetworkConnectionToWebProcess_ResourceLoadStatisticsUpdatedReply,
#endif
    NetworkConnectionToWebProcess_SendH2PingReply,
    NetworkConnectionToWebProcess_SetCookieFromDOMAsyncReply,
    NetworkConnectionToWebProcess_TakeAllMessagesForPortReply,
    NetworkConnectionToWebProcess_WriteBlobsToTemporaryFilesForIndexedDBReply,
    NetworkMDNSRegister_RegisterMDNSNameReply,
#if ENABLE(WEB_RTC)
    NetworkProcessConnection_ConnectToRTCDataChannelRemoteSourceReply,
#endif
    NetworkProcessProxy_DataTaskDidReceiveResponseReply,
    NetworkProcessProxy_DataTaskReceivedChallengeReply,
    NetworkProcessProxy_DataTaskWillPerformHTTPRedirectionReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcessProxy_DeleteWebsiteDataInUIProcessForRegistrableDomainsReply,
#endif
    NetworkProcessProxy_DeleteWebsiteDataInWebProcessesForOriginReply,
    NetworkProcessProxy_EstablishRemoteWorkerContextConnectionToNetworkProcessReply,
#if ENABLE(APP_BOUND_DOMAINS)
    NetworkProcessProxy_GetAppBoundDomainsReply,
#endif
#if ENABLE(APPLE_PAY_REMOTE_UI_USES_SCENE)
    NetworkProcessProxy_GetWindowSceneIdentifierForPaymentPresentationReply,
#endif
    NetworkProcessProxy_NavigateServiceWorkerClientReply,
    NetworkProcessProxy_OpenWindowFromServiceWorkerReply,
    NetworkProcessProxy_ReloadExecutionContextsForOriginReply,
#if ENABLE(SERVICE_WORKER)
    NetworkProcessProxy_RequestBackgroundFetchPermissionReply,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcessProxy_RequestStorageAccessConfirmReply,
#endif
    NetworkProcessProxy_RequestStorageSpaceReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcessProxy_SetDomainsWithCrossPageStorageAccessReply,
#endif
    NetworkProcessProxy_TriggerBrowsingContextGroupSwitchForNavigationReply,
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_AbortBackgroundFetchReply,
#endif
    NetworkProcess_AddAllowedFirstPartyForCookiesReply,
#if PLATFORM(COCOA)
    NetworkProcess_AppPrivacyReportTestingDataReply,
#endif
    NetworkProcess_CancelDownloadReply,
#if ENABLE(APP_BOUND_DOMAINS)
    NetworkProcess_ClearAppBoundSessionReply,
#endif
#if PLATFORM(COCOA)
    NetworkProcess_ClearAppPrivacyReportTestingDataReply,
#endif
    NetworkProcess_ClearBundleIdentifierReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_ClearPrevalentResourceReply,
#endif
    NetworkProcess_ClearPrivateClickMeasurementReply,
#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
    NetworkProcess_ClearServiceWorkerEntitlementOverrideReply,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_ClearUserInteractionReply,
#endif
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_ClickBackgroundFetchReply,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_CloseITPDatabaseReply,
#endif
    NetworkProcess_ClosePCMDatabaseReply,
    NetworkProcess_CountNonDefaultSessionSetsReply,
    NetworkProcess_CreateNetworkConnectionToWebProcessReply,
    NetworkProcess_DataTaskWithRequestReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_DeleteCookiesForTestingReply,
#endif
    NetworkProcess_DeletePushAndNotificationRegistrationReply,
    NetworkProcess_DeleteWebsiteDataForOriginsReply,
    NetworkProcess_DeleteWebsiteDataReply,
    NetworkProcess_DestroySessionReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_DomainIDExistsInDatabaseReply,
#endif
    NetworkProcess_DumpPrivateClickMeasurementReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_DumpResourceLoadStatisticsReply,
#endif
    NetworkProcess_FetchWebsiteDataReply,
    NetworkProcess_FlushCookiesReply,
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_GetAllBackgroundFetchIdentifiersReply,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_GetAllStorageAccessEntriesReply,
#endif
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_GetBackgroundFetchStateReply,
#endif
    NetworkProcess_GetOriginsWithPushAndNotificationPermissionsReply,
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_GetPendingPushMessagesReply,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_GetResourceLoadStatisticsDataSummaryReply,
    NetworkProcess_HadUserInteractionReply,
#endif
#if ENABLE(APP_BOUND_DOMAINS)
    NetworkProcess_HasAppBoundSessionReply,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_HasIsolatedSessionReply,
    NetworkProcess_HasLocalStorageReply,
#endif
    NetworkProcess_HasPushSubscriptionForTestingReply,
    NetworkProcess_InitializeNetworkProcessReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_InsertExpiredStatisticForTestingReply,
    NetworkProcess_IsGrandfatheredReply,
    NetworkProcess_IsPrevalentResourceReply,
    NetworkProcess_IsRegisteredAsRedirectingToReply,
    NetworkProcess_IsRegisteredAsSubFrameUnderReply,
    NetworkProcess_IsRegisteredAsSubresourceUnderReply,
    NetworkProcess_IsRelationshipOnlyInDatabaseOnceReply,
    NetworkProcess_IsResourceLoadStatisticsEphemeralReply,
    NetworkProcess_IsVeryPrevalentResourceReply,
    NetworkProcess_LogUserInteractionReply,
#endif
    NetworkProcess_MarkAttributedPrivateClickMeasurementsAsExpiredForTestingReply,
    NetworkProcess_MarkPrivateClickMeasurementsAsExpiredForTestingReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_MergeStatisticForTestingReply,
#endif
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_PauseBackgroundFetchReply,
#endif
    NetworkProcess_PrepareToSuspendReply,
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_ProcessNotificationEventReply,
    NetworkProcess_ProcessPushMessageReply,
#endif
    NetworkProcess_RenameOriginInWebsiteDataReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_ResetCacheMaxAgeCapForPrevalentResourcesReply,
    NetworkProcess_ResetCrossSiteLoadsWithLinkDecorationForTestingReply,
    NetworkProcess_ResetParametersToDefaultValuesReply,
#endif
    NetworkProcess_ResetQuotaReply,
    NetworkProcess_ResetStoragePersistedStateReply,
#if ENABLE(SERVICE_WORKER)
    NetworkProcess_ResumeBackgroundFetchReply,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_ScheduleClearInMemoryAndPersistentReply,
    NetworkProcess_ScheduleCookieBlockingUpdateReply,
    NetworkProcess_ScheduleStatisticsAndDataRecordsProcessingReply,
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(APP_BOUND_DOMAINS))
    NetworkProcess_SetAppBoundDomainsForResourceLoadStatisticsReply,
#endif
#if PLATFORM(IOS_FAMILY)
    NetworkProcess_SetBackupExclusionPeriodForTestingReply,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetCacheMaxAgeCapForPrevalentResourcesReply,
    NetworkProcess_SetCrossSiteLoadWithLinkDecorationForTestingReply,
    NetworkProcess_SetFirstPartyHostCNAMEDomainForTestingReply,
    NetworkProcess_SetFirstPartyWebsiteDataRemovalModeForTestingReply,
    NetworkProcess_SetGrandfatheredReply,
    NetworkProcess_SetGrandfatheringTimeReply,
    NetworkProcess_SetIsRunningResourceLoadStatisticsTestReply,
    NetworkProcess_SetLastSeenReply,
#endif
#if (ENABLE(TRACKING_PREVENTION) && ENABLE(MANAGED_DOMAINS))
    NetworkProcess_SetManagedDomainsForResourceLoadStatisticsReply,
#endif
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetMaxStatisticsEntriesReply,
    NetworkProcess_SetMinimumTimeBetweenDataRecordsRemovalReply,
    NetworkProcess_SetNotifyPagesWhenDataRecordsWereScannedReply,
#endif
    NetworkProcess_SetPCMFraudPreventionValuesForTestingReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetPrevalentResourceForDebugModeReply,
    NetworkProcess_SetPrevalentResourceReply,
#endif
    NetworkProcess_SetPrivateClickMeasurementAppBundleIDForTestingReply,
    NetworkProcess_SetPrivateClickMeasurementAttributionReportURLsForTestingReply,
    NetworkProcess_SetPrivateClickMeasurementEphemeralMeasurementForTestingReply,
    NetworkProcess_SetPrivateClickMeasurementOverrideTimerForTestingReply,
    NetworkProcess_SetPrivateClickMeasurementTokenPublicKeyURLForTestingReply,
    NetworkProcess_SetPrivateClickMeasurementTokenSignatureURLForTestingReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetPruneEntriesDownToReply,
#endif
    NetworkProcess_SetPushAndNotificationsEnabledForOriginReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_SetResourceLoadStatisticsDebugModeReply,
    NetworkProcess_SetResourceLoadStatisticsTimeAdvanceForTestingReply,
    NetworkProcess_SetShouldClassifyResourcesBeforeDataRecordsRemovalReply,
    NetworkProcess_SetShouldDowngradeReferrerForTestingReply,
    NetworkProcess_SetShouldEnbleSameSiteStrictEnforcementForTestingReply,
    NetworkProcess_SetSubframeUnderTopFrameDomainReply,
    NetworkProcess_SetSubresourceUnderTopFrameDomainReply,
    NetworkProcess_SetSubresourceUniqueRedirectFromReply,
    NetworkProcess_SetSubresourceUniqueRedirectToReply,
    NetworkProcess_SetThirdPartyCNAMEDomainForTestingReply,
    NetworkProcess_SetThirdPartyCookieBlockingModeReply,
    NetworkProcess_SetTimeToLiveUserInteractionReply,
    NetworkProcess_SetToSameSiteStrictCookiesForTestingReply,
    NetworkProcess_SetTopFrameUniqueRedirectFromReply,
    NetworkProcess_SetTopFrameUniqueRedirectToReply,
    NetworkProcess_SetVeryPrevalentResourceReply,
#endif
    NetworkProcess_SimulatePrivateClickMeasurementSessionRestartReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_StatisticsDatabaseHasAllTablesReply,
#endif
    NetworkProcess_StoreServiceWorkerRegistrationsReply,
    NetworkProcess_SyncLocalStorageReply,
    NetworkProcess_UpdateBundleIdentifierReply,
#if ENABLE(TRACKING_PREVENTION)
    NetworkProcess_UpdatePrevalentDomainsToBlockCookiesForReply,
#endif
    NetworkProcess_WebsiteDataOriginDirectoryForTestingReply,
    NetworkSocketChannel_SendDataReply,
    NetworkSocketChannel_SendStringReply,
    NetworkStorageManager_CacheStorageAllCachesReply,
    NetworkStorageManager_CacheStorageClearMemoryRepresentationReply,
    NetworkStorageManager_CacheStorageOpenCacheReply,
    NetworkStorageManager_CacheStoragePutRecordsReply,
    NetworkStorageManager_CacheStorageRemoveCacheReply,
    NetworkStorageManager_CacheStorageRemoveRecordsReply,
    NetworkStorageManager_CacheStorageRepresentationReply,
    NetworkStorageManager_CacheStorageRetrieveRecordsReply,
    NetworkStorageManager_ClearReply,
    NetworkStorageManager_CloseSyncAccessHandleReply,
    NetworkStorageManager_ConnectToStorageAreaReply,
    NetworkStorageManager_CreateSyncAccessHandleReply,
    NetworkStorageManager_EstimateReply,
    NetworkStorageManager_FileSystemGetDirectoryReply,
    NetworkStorageManager_GetDirectoryHandleReply,
    NetworkStorageManager_GetFileHandleReply,
    NetworkStorageManager_GetFileReply,
    NetworkStorageManager_GetHandleNamesReply,
    NetworkStorageManager_GetHandleReply,
    NetworkStorageManager_IsSameEntryReply,
    NetworkStorageManager_MoveReply,
    NetworkStorageManager_PersistReply,
    NetworkStorageManager_PersistedReply,
    NetworkStorageManager_RemoveEntryReply,
    NetworkStorageManager_RemoveItemReply,
    NetworkStorageManager_RequestNewCapacityForSyncAccessHandleReply,
    NetworkStorageManager_ResolveReply,
    NetworkStorageManager_SetItemReply,
    NotificationManagerMessageHandler_RequestSystemNotificationPermissionReply,
    NotificationManagerMessageHandler_ShowNotificationReply,
    PlatformXRSystem_EnumerateImmersiveXRDevicesReply,
    PlatformXRSystem_RequestFrameReply,
    PlatformXRSystem_RequestPermissionOnSessionFeaturesReply,
    RemoteAudioDestinationManager_StartAudioDestinationReply,
    RemoteAudioDestinationManager_StopAudioDestinationReply,
    RemoteAudioMediaStreamTrackRendererInternalUnitManager_CreateUnitReply,
    RemoteBarcodeDetector_DetectReply,
    RemoteBuffer_MapAsyncReply,
    RemoteCDMInstanceProxy_InitializeWithConfigurationReply,
    RemoteCDMInstanceProxy_SetServerCertificateReply,
    RemoteCDMInstanceSessionProxy_CloseSessionReply,
    RemoteCDMInstanceSessionProxy_LoadSessionReply,
    RemoteCDMInstanceSessionProxy_RemoveSessionDataReply,
    RemoteCDMInstanceSessionProxy_RequestLicenseReply,
    RemoteCDMInstanceSessionProxy_UpdateLicenseReply,
    RemoteCDMProxy_GetSupportedConfigurationReply,
    RemoteDevice_CreateComputePipelineAsyncReply,
    RemoteDevice_CreateRenderPipelineAsyncReply,
    RemoteDevice_PopErrorScopeReply,
    RemoteFaceDetector_DetectReply,
    RemoteMediaEngineConfigurationFactoryProxy_CreateDecodingConfigurationReply,
    RemoteMediaEngineConfigurationFactoryProxy_CreateEncodingConfigurationReply,
    RemoteMediaPlayerProxy_DidLoadingProgressReply,
#if ENABLE(MEDIA_SOURCE)
    RemoteMediaPlayerProxy_LoadMediaSourceReply,
#endif
    RemoteMediaPlayerProxy_LoadReply,
    RemoteMediaPlayerProxy_PerformTaskAtMediaTimeReply,
    RemoteMediaPlayerProxy_RequestHostingContextIDReply,
    RemoteMediaRecorderManager_CreateRecorderReply,
    RemoteMediaRecorder_FetchDataReply,
    RemoteMediaRecorder_PauseReply,
    RemoteMediaRecorder_ResumeReply,
    RemoteMediaRecorder_StopRecordingReply,
    RemoteMediaResourceManager_DataReceivedReply,
    RemoteMediaResourceManager_RedirectReceivedReply,
    RemoteMediaResourceManager_ResponseReceivedReply,
    RemoteMediaSessionCoordinatorProxy_CoordinatePauseReply,
    RemoteMediaSessionCoordinatorProxy_CoordinatePlayReply,
    RemoteMediaSessionCoordinatorProxy_CoordinateSeekToReply,
    RemoteMediaSessionCoordinatorProxy_CoordinateSetTrackReply,
    RemoteMediaSessionCoordinatorProxy_JoinReply,
    RemoteMediaSessionCoordinator_PauseSessionReply,
    RemoteMediaSessionCoordinator_PlaySessionReply,
    RemoteMediaSessionCoordinator_SeekSessionToTimeReply,
    RemoteMediaSessionCoordinator_SetSessionTrackReply,
    RemoteRenderingBackend_GetRemoteBarcodeDetectorSupportedFormatsReply,
    RemoteSampleBufferDisplayLayerManager_CreateLayerReply,
    RemoteShaderModule_CompilationInfoReply,
    RemoteSourceBufferProxy_AppendReply,
    RemoteSourceBufferProxy_BufferedSamplesForTrackIdReply,
    RemoteSourceBufferProxy_EnqueuedSamplesForTrackIDReply,
    RemoteSourceBufferProxy_MemoryPressureReply,
    RemoteSourceBufferProxy_RemoveCodedFramesReply,
    RemoteTextDetector_DetectReply,
    RemoteWebInspectorUIProxy_LoadReply,
    RemoteWebInspectorUIProxy_PickColorFromScreenReply,
    SourceBufferPrivateRemote_SourceBufferPrivateBufferedChangedReply,
    SourceBufferPrivateRemote_SourceBufferPrivateDidReceiveInitializationSegmentReply,
    SourceBufferPrivateRemote_SourceBufferPrivateDurationChangedReply,
    WebAutomationSessionProxy_ComputeElementLayoutReply,
    WebAutomationSessionProxy_DeleteCookieReply,
    WebAutomationSessionProxy_GetComputedLabelReply,
    WebAutomationSessionProxy_GetComputedRoleReply,
    WebAutomationSessionProxy_GetCookiesForFrameReply,
    WebAutomationSessionProxy_ResolveChildFrameWithNameReply,
    WebAutomationSessionProxy_ResolveChildFrameWithNodeHandleReply,
    WebAutomationSessionProxy_ResolveChildFrameWithOrdinalReply,
    WebAutomationSessionProxy_ResolveParentFrameReply,
    WebAutomationSessionProxy_SelectOptionElementReply,
    WebAutomationSessionProxy_SetFilesForInputFileUploadReply,
    WebAutomationSessionProxy_SnapshotRectForScreenshotReply,
    WebBroadcastChannelRegistry_PostMessageToRemoteReply,
    WebCookieManager_DeleteAllCookiesModifiedSinceReply,
    WebCookieManager_DeleteAllCookiesReply,
    WebCookieManager_DeleteCookieReply,
    WebCookieManager_DeleteCookiesForHostnamesReply,
    WebCookieManager_GetAllCookiesReply,
    WebCookieManager_GetCookiesReply,
    WebCookieManager_GetHTTPCookieAcceptPolicyReply,
    WebCookieManager_GetHostnamesWithCookiesReply,
#if USE(SOUP)
    WebCookieManager_ReplaceCookiesReply,
#endif
    WebCookieManager_SetCookieReply,
    WebCookieManager_SetCookiesReply,
    WebCookieManager_SetHTTPCookieAcceptPolicyReply,
    WebInspectorUIProxy_LoadReply,
    WebInspectorUIProxy_PickColorFromScreenReply,
    WebLockRegistryProxy_AbortLockRequestReply,
    WebLockRegistryProxy_SnapshotReply,
#if USE(SYSTEM_PREVIEW)
    WebPageProxy_BeginSystemPreviewReply,
#endif
    WebPageProxy_DecidePolicyForNavigationActionAsyncReply,
    WebPageProxy_DecidePolicyForNewWindowActionReply,
    WebPageProxy_DecidePolicyForResponseReply,
#if ENABLE(MEDIA_STREAM)
    WebPageProxy_EnumerateMediaDevicesForFrameReply,
#endif
    WebPageProxy_FocusFromServiceWorkerReply,
#if ENABLE(ARKIT_INLINE_PREVIEW)
    WebPageProxy_ModelElementAnimationCurrentTimeReply,
    WebPageProxy_ModelElementAnimationDurationReply,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    WebPageProxy_ModelElementCreateRemotePreviewReply,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    WebPageProxy_ModelElementGetCameraReply,
    WebPageProxy_ModelElementHasAudioReply,
    WebPageProxy_ModelElementIsLoopingAnimationReply,
    WebPageProxy_ModelElementIsMutedReply,
    WebPageProxy_ModelElementIsPlayingAnimationReply,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    WebPageProxy_ModelElementLoadRemotePreviewReply,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW)
    WebPageProxy_ModelElementSetAnimationCurrentTimeReply,
    WebPageProxy_ModelElementSetAnimationIsPlayingReply,
    WebPageProxy_ModelElementSetCameraReply,
    WebPageProxy_ModelElementSetIsLoopingAnimationReply,
    WebPageProxy_ModelElementSetIsMutedReply,
#endif
#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
    WebPageProxy_ModelElementSizeDidChangeReply,
    WebPageProxy_ModelInlinePreviewUUIDsReply,
#endif
    WebPageProxy_RequestCookieConsentReply,
    WebPageProxy_RequestNotificationPermissionReply,
#if USE(QUICK_LOOK)
    WebPageProxy_RequestPasswordForQuickLookDocumentInMainFrameReply,
#endif
#if ENABLE(IMAGE_ANALYSIS)
    WebPageProxy_RequestTextRecognitionReply,
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPageProxy_SendMessageToWebViewWithReplyReply,
#endif
#if ENABLE(DEVICE_ORIENTATION)
    WebPageProxy_ShouldAllowDeviceOrientationAndMotionAccessReply,
#endif
    WebPageProxy_ShowContactPickerReply,
#if PLATFORM(GTK)
    WebPageProxy_ShowEmojiPickerReply,
#endif
#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS) && USE(UICONTEXTMENU)
    WebPageProxy_ShowMediaControlsContextMenuReply,
#endif
    WebPageProxy_ShowShareSheetReply,
#if ENABLE(SPEECH_SYNTHESIS)
    WebPageProxy_SpeechSynthesisPauseReply,
    WebPageProxy_SpeechSynthesisResumeReply,
    WebPageProxy_SpeechSynthesisSetFinishedCallbackReply,
    WebPageProxy_SpeechSynthesisSpeakReply,
#endif
#if ENABLE(APPLE_PAY_AMS_UI)
    WebPageProxy_StartApplePayAMSUISessionReply,
#endif
    WebPageProxy_WillSubmitFormReply,
#if PLATFORM(COCOA)
    WebPage_AddDictationAlternativeReply,
#endif
    WebPage_AddLayerForFindOverlayReply,
#if PLATFORM(IOS_FAMILY)
    WebPage_ApplyAutocorrectionReply,
#endif
#if PLATFORM(MAC)
    WebPage_AttributedSubstringForCharacterRangeAsyncReply,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_BeginSelectionInDirectionReply,
#endif
#if PLATFORM(COCOA)
    WebPage_CharacterIndexForPointAsyncReply,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_ClearServiceWorkerEntitlementOverrideReply,
#endif
    WebPage_CompleteTextManipulationReply,
    WebPage_ComputePagesForPrintingDuringDOMPrintOperationReply,
    WebPage_ComputePagesForPrintingReply,
#if ENABLE(MEDIA_SESSION_COORDINATOR)
    WebPage_CreateMediaSessionCoordinatorReply,
#endif
#if ENABLE(DATA_DETECTION)
    WebPage_DetectDataInAllFramesReply,
#endif
#if PLATFORM(COCOA)
    WebPage_DictationAlternativesAtSelectionReply,
#endif
    WebPage_DidGetLoadDecisionForIconReply,
#if PLATFORM(IOS_FAMILY)
    WebPage_DispatchWheelEventWithoutScrollingReply,
#endif
#if PLATFORM(GTK)
    WebPage_DrawPagesForPrintingDuringDOMPrintOperationReply,
    WebPage_DrawPagesForPrintingReply,
#endif
#if PLATFORM(COCOA)
    WebPage_DrawPagesToPDFDuringDOMPrintOperationReply,
    WebPage_DrawPagesToPDFReply,
    WebPage_DrawRectToImageDuringDOMPrintOperationReply,
    WebPage_DrawRectToImageReply,
#endif
#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
    WebPage_DrawToImageReply,
#endif
#if PLATFORM(COCOA)
    WebPage_DrawToPDFReply,
#endif
#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
    WebPage_DrawToPDFiOSReply,
#endif
    WebPage_EndPrintingDuringDOMPrintOperationReply,
    WebPage_EndPrintingReply,
    WebPage_ExecuteEditCommandWithCallbackReply,
#if PLATFORM(IOS_FAMILY)
    WebPage_ExtendSelectionForReplacementReply,
    WebPage_ExtendSelectionReply,
#endif
    WebPage_FindRectsForStringMatchesReply,
    WebPage_FindStringReply,
    WebPage_FindTextRangesForStringMatchesReply,
#if PLATFORM(COCOA)
    WebPage_FirstRectForCharacterRangeAsyncReply,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_FocusNextFocusedElementReply,
    WebPage_FocusTextInputContextAndPlaceCaretReply,
#endif
    WebPage_ForceRepaintReply,
    WebPage_GetAccessibilityTreeDataReply,
#if ENABLE(APPLICATION_MANIFEST)
    WebPage_GetApplicationManifestReply,
#endif
    WebPage_GetBytecodeProfileReply,
#if PLATFORM(COCOA)
    WebPage_GetContentsAsAttributedStringReply,
#endif
#if ENABLE(MHTML)
    WebPage_GetContentsAsMHTMLDataReply,
#endif
    WebPage_GetContentsAsStringReply,
    WebPage_GetFrameInfoReply,
    WebPage_GetFrameTreeReply,
#if ENABLE(TRACKING_PREVENTION)
    WebPage_GetLoadedSubresourceDomainsReply,
#endif
    WebPage_GetMainResourceDataOfFrameReply,
#if PLATFORM(COCOA)
    WebPage_GetMarkedRangeAsyncReply,
#endif
    WebPage_GetPDFFirstPageSizeReply,
    WebPage_GetProcessDisplayNameReply,
#if PLATFORM(IOS_FAMILY)
    WebPage_GetRectsAtSelectionOffsetWithTextReply,
    WebPage_GetRectsForGranularityWithSelectionOffsetReply,
#endif
    WebPage_GetRenderTreeExternalRepresentationReply,
    WebPage_GetResourceDataFromFrameReply,
    WebPage_GetSamplingProfilerOutputReply,
#if PLATFORM(COCOA)
    WebPage_GetSelectedRangeAsyncReply,
#endif
    WebPage_GetSelectionAsWebArchiveDataReply,
#if PLATFORM(IOS_FAMILY)
    WebPage_GetSelectionContextReply,
#endif
    WebPage_GetSelectionOrContentsAsStringReply,
    WebPage_GetSourceForFrameReply,
    WebPage_GetTextFragmentMatchReply,
    WebPage_GetWebArchiveOfFrameReply,
    WebPage_HandleWheelEventReply,
#if PLATFORM(COCOA)
    WebPage_HasMarkedTextReply,
#endif
#if ENABLE(ATTACHMENT_ELEMENT)
    WebPage_InsertAttachmentReply,
#endif
#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
    WebPage_InsertDroppedImagePlaceholdersReply,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_InsertTextPlaceholderReply,
#endif
    WebPage_IsLayerTreeFrozenReply,
    WebPage_LastNavigationWasAppInitiatedReply,
#if PLATFORM(IOS_FAMILY)
    WebPage_MoveSelectionAtBoundaryWithDirectionReply,
    WebPage_MoveSelectionByOffsetReply,
#endif
    WebPage_NavigateServiceWorkerClientReply,
#if ENABLE(PDFKIT_PLUGIN)
    WebPage_OpenPDFWithPreviewReply,
#endif
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    WebPage_PauseAllAnimationsReply,
#endif
    WebPage_PauseAllMediaPlaybackReply,
#if PLATFORM(IOS_FAMILY)
    WebPage_PerformActionOnElementReply,
#endif
    WebPage_PerformHitTestForMouseEventReply,
#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
    WebPage_PlayAllAnimationsReply,
#endif
#if (PLATFORM(IOS_FAMILY) && ENABLE(REVEAL))
    WebPage_PrepareSelectionForContextMenuWithLocationInViewReply,
#endif
#if ENABLE(DATA_DETECTION)
    WebPage_RemoveDataDetectedLinksReply,
#endif
    WebPage_RemoveLayerForFindOverlayReply,
#if PLATFORM(IOS_FAMILY)
    WebPage_RemoveTextPlaceholderReply,
#endif
    WebPage_ReplaceMatchesReply,
#if PLATFORM(COCOA)
    WebPage_RequestActiveNowPlayingSessionInfoReply,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_RequestAutocorrectionDataReply,
    WebPage_RequestDictationContextReply,
    WebPage_RequestDocumentEditingContextReply,
    WebPage_RequestEvasionRectsAboveSelectionReply,
    WebPage_RequestFocusedElementInformationReply,
#endif
    WebPage_RequestFontAttributesAtSelectionStartReply,
    WebPage_RequestImageBitmapReply,
    WebPage_RequestMediaPlaybackStateReply,
#if (PLATFORM(IOS_FAMILY) && ENABLE(REVEAL))
    WebPage_RequestRVItemInCurrentSelectedRangeReply,
#endif
    WebPage_RequestRectForFoundTextRangeReply,
    WebPage_ResumeAllMediaPlaybackReply,
    WebPage_ResumeReply,
    WebPage_RunJavaScriptInFrameInScriptWorldReply,
#if ENABLE(PDFKIT_PLUGIN)
    WebPage_SavePDFReply,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_SelectPositionAtBoundaryWithDirectionReply,
    WebPage_SelectPositionAtPointReply,
    WebPage_SelectTextWithGranularityAtPointReply,
    WebPage_SelectWithGestureReply,
    WebPage_SelectWithTwoTouchesReply,
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebPage_SendMessageToWebProcessExtensionWithReplyReply,
#endif
    WebPage_SetActivityStateReply,
    WebPage_SetInitialFocusReply,
    WebPage_SetMutedReply,
#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
    WebPage_ShouldAllowRemoveBackgroundReply,
#endif
    WebPage_StartTextManipulationsReply,
    WebPage_StopMediaCaptureReply,
    WebPage_SuspendAllMediaPlaybackReply,
    WebPage_SuspendReply,
    WebPage_TakeSnapshotReply,
#if PLATFORM(IOS_FAMILY)
    WebPage_TextInputContextsInRectReply,
#endif
    WebPage_TryCloseReply,
    WebPage_URLSchemeTaskWillPerformRedirectionReply,
#if ENABLE(ATTACHMENT_ELEMENT)
    WebPage_UpdateAttachmentAttributesReply,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_UpdateSelectionWithDeltaReply,
    WebPage_UpdateSelectionWithExtentPointAndBoundaryReply,
    WebPage_UpdateSelectionWithExtentPointReply,
    WebPage_UpdateSelectionWithTouchesReply,
#endif
#if ENABLE(IMAGE_ANALYSIS)
    WebPage_UpdateWithTextRecognitionResultReply,
#endif
#if ENABLE(MEDIA_STREAM)
    WebPage_UserMediaAccessWasGrantedReply,
#endif
    WebPage_ValidateCommandReply,
    WebPermissionControllerProxy_QueryReply,
#if ENABLE(GAMEPAD)
    WebProcessPool_PlayGamepadEffectReply,
    WebProcessPool_StopGamepadEffectsReply,
    WebProcessPool_StoppedUsingGamepadsReply,
#endif
    WebProcessProxy_GetNotificationsReply,
#if PLATFORM(GTK) || PLATFORM(WPE)
    WebProcessProxy_SendMessageToWebContextWithReplyReply,
#endif
    WebProcess_ClearCachedPageReply,
    WebProcess_DeleteAllCookiesReply,
    WebProcess_DeleteWebsiteDataForOriginReply,
    WebProcess_DeleteWebsiteDataForOriginsReply,
    WebProcess_DeleteWebsiteDataReply,
    WebProcess_EstablishRemoteWorkerContextConnectionToNetworkProcessReply,
    WebProcess_FetchWebsiteDataReply,
    WebProcess_GetActivePagesOriginsForTestingReply,
    WebProcess_IsJITEnabledReply,
    WebProcess_PrepareToSuspendReply,
    WebProcess_ReleaseMemoryReply,
    WebProcess_ReloadExecutionContextsForOriginReply,
#if ENABLE(TRACKING_PREVENTION)
    WebProcess_SeedResourceLoadStatisticsForTestingReply,
    WebProcess_SendResourceLoadStatisticsDataImmediatelyReply,
    WebProcess_SetDomainsWithCrossPageStorageAccessReply,
    WebProcess_SetThirdPartyCookieBlockingModeReply,
#endif
    WebResourceLoader_WillSendRequestReply,
    WebSWClientConnection_FocusServiceWorkerClientReply,
    WebSWClientConnection_SetServiceWorkerClientIsControlledReply,
    WebSWContextManagerConnection_FireBackgroundFetchClickEventReply,
    WebSWContextManagerConnection_FireBackgroundFetchEventReply,
    WebSWContextManagerConnection_FireNotificationEventReply,
    WebSWContextManagerConnection_FirePushEventReply,
    WebSWServerConnection_AbortBackgroundFetchReply,
    WebSWServerConnection_BackgroundFetchIdentifiersReply,
    WebSWServerConnection_BackgroundFetchInformationReply,
    WebSWServerConnection_DisableNavigationPreloadReply,
    WebSWServerConnection_EnableNavigationPreloadReply,
    WebSWServerConnection_GetNavigationPreloadStateReply,
    WebSWServerConnection_GetPushPermissionStateReply,
    WebSWServerConnection_GetPushSubscriptionReply,
    WebSWServerConnection_GetRegistrationsReply,
    WebSWServerConnection_MatchBackgroundFetchReply,
    WebSWServerConnection_MatchRegistrationReply,
    WebSWServerConnection_RetrieveRecordResponseReply,
    WebSWServerConnection_ScheduleUnregisterJobInServerReply,
    WebSWServerConnection_SetNavigationPreloadHeaderValueReply,
    WebSWServerConnection_StartBackgroundFetchReply,
    WebSWServerConnection_StoreRegistrationsOnDiskReply,
    WebSWServerConnection_SubscribeToPushServiceReply,
    WebSWServerConnection_TerminateWorkerFromClientReply,
    WebSWServerConnection_UnsubscribeFromPushServiceReply,
    WebSWServerConnection_WhenRegistrationReadyReply,
    WebSWServerConnection_WhenServiceWorkerIsTerminatedForTestingReply,
    WebSWServerToContextConnection_ClaimReply,
    WebSWServerToContextConnection_FindClientByVisibleIdentifierReply,
    WebSWServerToContextConnection_FocusReply,
    WebSWServerToContextConnection_NavigateReply,
    WebSWServerToContextConnection_OpenWindowReply,
    WebScreenOrientationManagerProxy_LockReply,
    WebSharedWorkerContextManagerConnection_PostConnectEventReply,
    WebSharedWorkerObjectConnection_FetchScriptInClientReply,
    WebUserContentControllerProxy_DidPostMessageReply,
    FirstSynchronous,
    LastAsynchronous = FirstSynchronous - 1,
#if USE(AUDIO_SESSION)
    GPUConnectionToWebProcess_EnsureAudioSession,
#endif
    IPCConnectionTester_SyncMessage,
    IPCStreamTester_CheckAutoreleasePool,
    IPCStreamTester_SyncCrashOnZero,
    IPCStreamTester_SyncMessageReturningSharedMemory1,
    IPCTester_ReleaseConnectionTester,
    IPCTester_ReleaseStreamTester,
    IPCTester_StopMessageTesting,
    NetworkConnectionToWebProcess_BlobSize,
    NetworkConnectionToWebProcess_CookieRequestHeaderFieldValue,
    NetworkConnectionToWebProcess_CookiesForDOM,
    NetworkConnectionToWebProcess_DomCookiesForHost,
    NetworkConnectionToWebProcess_GetNetworkLoadInformationResponse,
    NetworkConnectionToWebProcess_GetNetworkLoadIntermediateInformation,
    NetworkConnectionToWebProcess_GetRawCookies,
    NetworkConnectionToWebProcess_PerformSynchronousLoad,
    NetworkConnectionToWebProcess_TakeNetworkLoadInformationMetrics,
    NetworkConnectionToWebProcess_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply,
    NetworkProcessProxy_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply,
    NetworkProcess_ProcessWillSuspendImminentlyForTestingSync,
    NetworkProcess_ResetServiceWorkerFetchTimeoutForTesting,
    NetworkProcess_SetAllowsAnySSLCertificateForWebSocket,
    NetworkProcess_SetCacheModelSynchronouslyForTesting,
    NetworkProcess_SetServiceWorkerFetchTimeoutForTesting,
    NetworkStorageManager_ConnectToStorageAreaSync,
    RemoteAdapter_RequestDevice,
    RemoteAudioSessionProxy_TryToSetActive,
    RemoteBuffer_GetMappedRange,
    RemoteCDMFactoryProxy_CreateCDM,
    RemoteCDMFactoryProxy_SupportsKeySystem,
    RemoteCDMInstanceProxy_CreateSession,
    RemoteCDMProxy_CreateInstance,
    RemoteCompositorIntegration_PrepareForDisplay,
#if PLATFORM(COCOA)
    RemoteCompositorIntegration_RecreateRenderBuffers,
#endif
    RemoteDisplayListRecorder_FlushContextSync,
    RemoteGPU_RequestAdapter,
    RemoteGraphicsContextGL_CheckFramebufferStatus,
    RemoteGraphicsContextGL_ClientWaitSync,
#if ENABLE(VIDEO) && PLATFORM(COCOA)
    RemoteGraphicsContextGL_CopyTextureFromVideoFrame,
#endif
#if PLATFORM(COCOA)
    RemoteGraphicsContextGL_CreateAndBindEGLImage,
#endif
    RemoteGraphicsContextGL_CreateBuffer,
#if PLATFORM(COCOA)
    RemoteGraphicsContextGL_CreateEGLSync,
#endif
    RemoteGraphicsContextGL_CreateFramebuffer,
    RemoteGraphicsContextGL_CreateProgram,
    RemoteGraphicsContextGL_CreateQuery,
    RemoteGraphicsContextGL_CreateQueryEXT,
    RemoteGraphicsContextGL_CreateRenderbuffer,
    RemoteGraphicsContextGL_CreateSampler,
    RemoteGraphicsContextGL_CreateShader,
    RemoteGraphicsContextGL_CreateTexture,
    RemoteGraphicsContextGL_CreateTransformFeedback,
    RemoteGraphicsContextGL_CreateVertexArray,
    RemoteGraphicsContextGL_DestroyEGLSync,
    RemoteGraphicsContextGL_EnableRequiredWebXRExtensions,
    RemoteGraphicsContextGL_FenceSync,
    RemoteGraphicsContextGL_GetActiveAttrib,
    RemoteGraphicsContextGL_GetActiveUniform,
    RemoteGraphicsContextGL_GetActiveUniformBlockName,
    RemoteGraphicsContextGL_GetActiveUniformBlockiv,
    RemoteGraphicsContextGL_GetActiveUniforms,
    RemoteGraphicsContextGL_GetAttribLocation,
    RemoteGraphicsContextGL_GetBooleanv,
    RemoteGraphicsContextGL_GetBufferParameteri,
    RemoteGraphicsContextGL_GetBufferSubData,
    RemoteGraphicsContextGL_GetErrors,
    RemoteGraphicsContextGL_GetFloatv,
    RemoteGraphicsContextGL_GetFragDataLocation,
    RemoteGraphicsContextGL_GetFramebufferAttachmentParameteri,
    RemoteGraphicsContextGL_GetInteger64,
    RemoteGraphicsContextGL_GetInteger64EXT,
    RemoteGraphicsContextGL_GetInteger64i,
    RemoteGraphicsContextGL_GetIntegeri_v,
    RemoteGraphicsContextGL_GetIntegerv,
    RemoteGraphicsContextGL_GetInternalformativ,
    RemoteGraphicsContextGL_GetProgramInfoLog,
    RemoteGraphicsContextGL_GetProgrami,
    RemoteGraphicsContextGL_GetQuery,
    RemoteGraphicsContextGL_GetQueryObjectiEXT,
    RemoteGraphicsContextGL_GetQueryObjectui,
    RemoteGraphicsContextGL_GetQueryObjectui64EXT,
    RemoteGraphicsContextGL_GetQueryiEXT,
    RemoteGraphicsContextGL_GetRenderbufferParameteri,
    RemoteGraphicsContextGL_GetSamplerParameterf,
    RemoteGraphicsContextGL_GetSamplerParameteri,
    RemoteGraphicsContextGL_GetShaderInfoLog,
    RemoteGraphicsContextGL_GetShaderPrecisionFormat,
    RemoteGraphicsContextGL_GetShaderSource,
    RemoteGraphicsContextGL_GetShaderi,
    RemoteGraphicsContextGL_GetString,
    RemoteGraphicsContextGL_GetSynci,
    RemoteGraphicsContextGL_GetTexParameterf,
    RemoteGraphicsContextGL_GetTexParameteri,
    RemoteGraphicsContextGL_GetTransformFeedbackVarying,
    RemoteGraphicsContextGL_GetTranslatedShaderSourceANGLE,
    RemoteGraphicsContextGL_GetUniformBlockIndex,
    RemoteGraphicsContextGL_GetUniformIndices,
    RemoteGraphicsContextGL_GetUniformLocation,
    RemoteGraphicsContextGL_GetUniformfv,
    RemoteGraphicsContextGL_GetUniformiv,
    RemoteGraphicsContextGL_GetUniformuiv,
    RemoteGraphicsContextGL_GetVertexAttribOffset,
    RemoteGraphicsContextGL_IsBuffer,
    RemoteGraphicsContextGL_IsEnabled,
    RemoteGraphicsContextGL_IsFramebuffer,
    RemoteGraphicsContextGL_IsProgram,
    RemoteGraphicsContextGL_IsQuery,
    RemoteGraphicsContextGL_IsQueryEXT,
    RemoteGraphicsContextGL_IsRenderbuffer,
    RemoteGraphicsContextGL_IsSampler,
    RemoteGraphicsContextGL_IsShader,
    RemoteGraphicsContextGL_IsSync,
    RemoteGraphicsContextGL_IsTexture,
    RemoteGraphicsContextGL_IsTransformFeedback,
    RemoteGraphicsContextGL_IsVertexArray,
    RemoteGraphicsContextGL_PaintCompositedResultsToCanvas,
#if ENABLE(MEDIA_STREAM) || ENABLE(WEB_CODECS)
    RemoteGraphicsContextGL_PaintCompositedResultsToVideoFrame,
#endif
    RemoteGraphicsContextGL_PaintRenderingResultsToCanvas,
    RemoteGraphicsContextGL_PaintRenderingResultsToPixelBuffer,
#if PLATFORM(COCOA) || USE(GRAPHICS_LAYER_WC) || USE(GBM) || !PLATFORM(COCOA) && !USE(GRAPHICS_LAYER_WC) && !USE(GBM)
    RemoteGraphicsContextGL_PrepareForDisplay,
#endif
    RemoteGraphicsContextGL_ReadPixelsInline,
    RemoteGraphicsContextGL_ReadPixelsSharedMemory,
    RemoteLegacyCDMFactoryProxy_CreateCDM,
    RemoteLegacyCDMFactoryProxy_SupportsKeySystem,
    RemoteLegacyCDMProxy_CreateSession,
    RemoteLegacyCDMProxy_SupportsMIMEType,
    RemoteLegacyCDMSessionProxy_CachedKeyForKeyID,
    RemoteLegacyCDMSessionProxy_GenerateKeyRequest,
    RemoteLegacyCDMSessionProxy_Update,
    RemoteMediaPlayerManagerProxy_GetSupportedTypes,
    RemoteMediaPlayerManagerProxy_SupportsKeySystem,
    RemoteMediaPlayerManagerProxy_SupportsTypeAndCodecs,
#if PLATFORM(IOS_FAMILY)
    RemoteMediaPlayerProxy_AccessLog,
#endif
#if PLATFORM(COCOA)
    RemoteMediaPlayerProxy_ColorSpace,
#endif
#if PLATFORM(IOS_FAMILY)
    RemoteMediaPlayerProxy_ErrorLog,
#endif
    RemoteMediaPlayerProxy_IsCrossOrigin,
#if PLATFORM(COCOA)
    RemoteMediaPlayerProxy_NativeImageForCurrentTime,
#endif
    RemoteMediaPlayerProxy_VideoFrameForCurrentTimeIfChanged,
    RemoteMediaSourceProxy_AddSourceBuffer,
    RemoteQueue_OnSubmittedWorkDone,
    RemoteRenderingBackend_GetFilteredImageForImageBuffer,
    RemoteRenderingBackend_GetPixelBufferForImageBuffer,
    RemoteRenderingBackend_GetPixelBufferForImageBufferWithNewMemory,
    RemoteRenderingBackend_GetShareableBitmapForImageBuffer,
#if PLATFORM(COCOA)
    RemoteRenderingBackend_PrepareBuffersForDisplay,
#endif
    RemoteSourceBufferProxy_CanSwitchToType,
    RemoteSourceBufferProxy_EvictCodedFrames,
    RemoteSourceBufferProxy_MinimumUpcomingPresentationTimeForTrackID,
#if PLATFORM(COCOA)
    RemoteVideoFrameObjectHeap_ConvertFrameBuffer,
    RemoteVideoFrameObjectHeap_PixelBuffer,
#endif
    WebFullScreenManagerProxy_SupportsFullScreen,
    WebPageProxy_AccessibilityScreenToRootView,
    WebPageProxy_BackForwardGoToItem,
    WebPageProxy_BackForwardItemAtIndex,
    WebPageProxy_BackForwardListContainsItem,
    WebPageProxy_BackForwardListCounts,
    WebPageProxy_CanUndoRedo,
    WebPageProxy_CheckGrammarOfString,
    WebPageProxy_CheckSpellingOfString,
#if USE(UNIFIED_TEXT_CHECKING)
    WebPageProxy_CheckTextOfParagraph,
#endif
    WebPageProxy_CreateNewPage,
    WebPageProxy_DecidePolicyForNavigationActionSync,
#if USE(DICTATION_ALTERNATIVES)
    WebPageProxy_DictationAlternatives,
#endif
#if PLATFORM(MAC)
    WebPageProxy_DismissCorrectionPanelSoon,
#endif
    WebPageProxy_ExceededDatabaseQuota,
#if PLATFORM(COCOA)
    WebPageProxy_ExecuteSavedCommandBySelector,
#endif
    WebPageProxy_ExecuteUndoRedo,
    WebPageProxy_GetGuessesForWord,
#if PLATFORM(COCOA)
    WebPageProxy_GetIsSpeaking,
#endif
    WebPageProxy_GetMenuBarIsVisible,
    WebPageProxy_GetStatusBarIsVisible,
    WebPageProxy_GetToolbarsAreVisible,
    WebPageProxy_GetWindowFrame,
    WebPageProxy_HandleSynchronousMessage,
#if PLATFORM(IOS_FAMILY)
    WebPageProxy_InterpretKeyEvent,
#endif
    WebPageProxy_LoadRecentSearches,
    WebPageProxy_LoadSynchronousURLSchemeTask,
    WebPageProxy_PrintFrame,
    WebPageProxy_ReachedApplicationCacheOriginQuota,
    WebPageProxy_RequestDOMPasteAccess,
    WebPageProxy_RootViewToAccessibilityScreen,
    WebPageProxy_RootViewToScreen,
    WebPageProxy_RunBeforeUnloadConfirmPanel,
    WebPageProxy_RunJavaScriptAlert,
    WebPageProxy_RunJavaScriptConfirm,
    WebPageProxy_RunJavaScriptPrompt,
    WebPageProxy_ScreenToRootView,
#if ENABLE(ATTACHMENT_ELEMENT)
    WebPageProxy_SerializedAttachmentDataForIdentifiers,
#endif
#if ENABLE(PDFKIT_PLUGIN)
    WebPageProxy_ShowPDFContextMenu,
#endif
#if ENABLE(SPEECH_SYNTHESIS)
    WebPageProxy_SpeechSynthesisVoiceList,
#endif
    WebPageProxy_SpellingUIIsShowing,
#if USE(APPKIT)
    WebPageProxy_SubstitutionsPanelIsShowing,
#endif
#if ENABLE(WEB_CRYPTO)
    WebPageProxy_UnwrapCryptoKey,
    WebPageProxy_WrapCryptoKey,
#endif
#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
    WebPage_ComputePagesForPrintingiOS,
#endif
#if PLATFORM(COCOA)
    WebPage_GetDataSelectionForPasteboard,
    WebPage_GetStringSelectionForPasteboard,
    WebPage_ReadSelectionFromPasteboard,
    WebPage_ShouldDelayWindowOrderingEvent,
#endif
#if PLATFORM(IOS_FAMILY)
    WebPage_SyncApplyAutocorrection,
#endif
    WebPage_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply,
#if PLATFORM(COCOA)
    WebPasteboardProxy_AddPasteboardTypes,
#endif
    WebPasteboardProxy_AllPasteboardItemInfo,
    WebPasteboardProxy_ContainsStringSafeForDOMToReadForType,
#if PLATFORM(COCOA)
    WebPasteboardProxy_ContainsURLStringSuitableForLoading,
    WebPasteboardProxy_GetNumberOfFiles,
    WebPasteboardProxy_GetPasteboardBufferForType,
#endif
#if PLATFORM(COCOA) || PLATFORM(GTK)
    WebPasteboardProxy_GetPasteboardChangeCount,
#endif
#if PLATFORM(COCOA)
    WebPasteboardProxy_GetPasteboardColor,
#endif
    WebPasteboardProxy_GetPasteboardItemsCount,
#if PLATFORM(COCOA)
    WebPasteboardProxy_GetPasteboardPathnamesForType,
    WebPasteboardProxy_GetPasteboardStringForType,
    WebPasteboardProxy_GetPasteboardStringsForType,
#endif
#if PLATFORM(COCOA) || USE(LIBWPE)
    WebPasteboardProxy_GetPasteboardTypes,
#endif
#if PLATFORM(COCOA)
    WebPasteboardProxy_GetPasteboardURL,
#endif
#if PLATFORM(GTK)
    WebPasteboardProxy_GetTypes,
#endif
    WebPasteboardProxy_InformationForItemAtIndex,
#if PLATFORM(GTK)
    WebPasteboardProxy_ReadBuffer,
#endif
    WebPasteboardProxy_ReadBufferFromPasteboard,
#if PLATFORM(GTK)
    WebPasteboardProxy_ReadFilePaths,
#endif
    WebPasteboardProxy_ReadStringFromPasteboard,
#if PLATFORM(GTK)
    WebPasteboardProxy_ReadText,
#endif
    WebPasteboardProxy_ReadURLFromPasteboard,
#if PLATFORM(COCOA)
    WebPasteboardProxy_SetPasteboardBufferForType,
    WebPasteboardProxy_SetPasteboardColor,
    WebPasteboardProxy_SetPasteboardStringForType,
    WebPasteboardProxy_SetPasteboardTypes,
    WebPasteboardProxy_SetPasteboardURL,
#endif
#if (PLATFORM(COCOA) && ENABLE(IPC_TESTING_API))
    WebPasteboardProxy_TestIPCSharedMemory,
#endif
    WebPasteboardProxy_TypesSafeForDOMToReadAndWrite,
#if PLATFORM(COCOA)
    WebPasteboardProxy_URLStringSuitableForLoading,
#endif
    WebPasteboardProxy_WriteCustomData,
    WebProcessPool_HandleSynchronousMessage,
    WebProcessProxy_GetNetworkProcessConnection,
#if PLATFORM(MAC)
    WebProcessProxy_IsAXAuthenticated,
#endif
    WebProcessProxy_RenderTreeAsText,
    WebProcessProxy_ShouldTerminate,
    WebProcess_RenderTreeAsText,
    WebScreenOrientationManagerProxy_CurrentOrientation,
    WrappedAsyncMessageForTesting,
    Count,
    Last = Count - 1
};

namespace Detail {
struct MessageDescription {
    const char* const description;
    ReceiverName receiverName;
    bool messageAllowedWhenWaitingForSyncReply : 1;
    bool messageAllowedWhenWaitingForUnboundedSyncReply : 1;
};

extern const MessageDescription messageDescriptions[static_cast<size_t>(MessageName::Count) + 1];
}

inline ReceiverName receiverName(MessageName messageName)
{
    messageName = std::min(messageName, MessageName::Last);
    return Detail::messageDescriptions[static_cast<size_t>(messageName)].receiverName;
}

inline const char* description(MessageName messageName)
{
    messageName = std::min(messageName, MessageName::Last);
    return Detail::messageDescriptions[static_cast<size_t>(messageName)].description;
}

inline bool messageAllowedWhenWaitingForSyncReply(MessageName messageName)
{
    messageName = std::min(messageName, MessageName::Last);
    return Detail::messageDescriptions[static_cast<size_t>(messageName)].messageAllowedWhenWaitingForSyncReply;
}

inline bool messageAllowedWhenWaitingForUnboundedSyncReply(MessageName messageName)
{
    messageName = std::min(messageName, MessageName::Last);
    return Detail::messageDescriptions[static_cast<size_t>(messageName)].messageAllowedWhenWaitingForUnboundedSyncReply;
}

constexpr bool messageIsSync(MessageName name)
{
    return name >= MessageName::FirstSynchronous;
}

} // namespace IPC

namespace WTF {

template<> constexpr bool isValidEnum<IPC::MessageName, void>(std::underlying_type_t<IPC::MessageName> messageName)
{
    return messageName <= WTF::enumToUnderlyingType(IPC::MessageName::Last);
}

} // namespace WTF
