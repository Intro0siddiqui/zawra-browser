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

#if ENABLE(GPU_PROCESS)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "GPUProcessConnectionParameters.h"
#include "MessageNames.h"
#include "SandboxExtension.h"
#include "ShareableBitmap.h"
#include <WebCore/CaptureDevice.h>
#include <WebCore/IntDegrees.h>
#include <WebCore/MediaPlayerIdentifier.h>
#include <WebCore/ProcessIdentifier.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace IPC {
class SharedBufferReference;
}

namespace PAL {
class SessionID;
}

namespace WebCore {
class SecurityOriginData;
enum class DisplayCapturePromptType : uint8_t;
struct MockMediaDevice;
struct ScreenProperties;
}

namespace WebKit {
struct GPUProcessCreationParameters;
struct GPUProcessPreferences;
struct GPUProcessSessionParameters;
}

namespace Messages {
namespace GPUProcess {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::GPUProcess;
}

class InitializeGPUProcess {
public:
    using Arguments = std::tuple<WebKit::GPUProcessCreationParameters>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_InitializeGPUProcess; }
    static constexpr bool isSync = false;

    explicit InitializeGPUProcess(const WebKit::GPUProcessCreationParameters& processCreationParameters)
        : m_arguments(processCreationParameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::GPUProcessCreationParameters&> m_arguments;
};

class CreateGPUConnectionToWebProcess {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier, PAL::SessionID, IPC::Connection::Handle, WebKit::GPUProcessConnectionParameters>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_CreateGPUConnectionToWebProcess; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::GPUProcess_CreateGPUConnectionToWebProcessReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    CreateGPUConnectionToWebProcess(const WebCore::ProcessIdentifier& processIdentifier, const PAL::SessionID& sessionID, IPC::Connection::Handle&& connectionHandle, WebKit::GPUProcessConnectionParameters&& parameters)
        : m_arguments(processIdentifier, sessionID, WTFMove(connectionHandle), WTFMove(parameters))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&, const PAL::SessionID&, IPC::Connection::Handle&&, WebKit::GPUProcessConnectionParameters&&> m_arguments;
};

class UpdateWebGPUEnabled {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_UpdateWebGPUEnabled; }
    static constexpr bool isSync = false;

    UpdateWebGPUEnabled(const WebCore::ProcessIdentifier& processIdentifier, bool webGPUEnabled)
        : m_arguments(processIdentifier, webGPUEnabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&, bool> m_arguments;
};

class UpdateDOMRenderingEnabled {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_UpdateDOMRenderingEnabled; }
    static constexpr bool isSync = false;

    UpdateDOMRenderingEnabled(const WebCore::ProcessIdentifier& processIdentifier, bool isDOMRenderingEnabled)
        : m_arguments(processIdentifier, isDOMRenderingEnabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&, bool> m_arguments;
};

class UpdateGPUProcessPreferences {
public:
    using Arguments = std::tuple<WebKit::GPUProcessPreferences>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_UpdateGPUProcessPreferences; }
    static constexpr bool isSync = false;

    explicit UpdateGPUProcessPreferences(const WebKit::GPUProcessPreferences& preferences)
        : m_arguments(preferences)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::GPUProcessPreferences&> m_arguments;
};

class UpdateSandboxAccess {
public:
    using Arguments = std::tuple<Vector<WebKit::SandboxExtension::Handle>>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_UpdateSandboxAccess; }
    static constexpr bool isSync = false;

    explicit UpdateSandboxAccess(const Vector<WebKit::SandboxExtension::Handle>& extensions)
        : m_arguments(extensions)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::SandboxExtension::Handle>&> m_arguments;
};

class PrepareToSuspend {
public:
    using Arguments = std::tuple<bool, MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_PrepareToSuspend; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::GPUProcess_PrepareToSuspendReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    PrepareToSuspend(bool isSuspensionImminent, const MonotonicTime& estimatedSuspendTime)
        : m_arguments(isSuspensionImminent, estimatedSuspendTime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, const MonotonicTime&> m_arguments;
};

class ProcessDidResume {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_ProcessDidResume; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class AddSession {
public:
    using Arguments = std::tuple<PAL::SessionID, WebKit::GPUProcessSessionParameters>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_AddSession; }
    static constexpr bool isSync = false;

    AddSession(const PAL::SessionID& sessionID, const WebKit::GPUProcessSessionParameters& parameters)
        : m_arguments(sessionID, parameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&, const WebKit::GPUProcessSessionParameters&> m_arguments;
};

class RemoveSession {
public:
    using Arguments = std::tuple<PAL::SessionID>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_RemoveSession; }
    static constexpr bool isSync = false;

    explicit RemoveSession(const PAL::SessionID& sessionID)
        : m_arguments(sessionID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const PAL::SessionID&> m_arguments;
};

#if ENABLE(MEDIA_STREAM)
class SetMockCaptureDevicesEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_SetMockCaptureDevicesEnabled; }
    static constexpr bool isSync = false;

    explicit SetMockCaptureDevicesEnabled(bool isEnabled)
        : m_arguments(isEnabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class SetOrientationForMediaCapture {
public:
    using Arguments = std::tuple<WebCore::IntDegrees>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_SetOrientationForMediaCapture; }
    static constexpr bool isSync = false;

    explicit SetOrientationForMediaCapture(const WebCore::IntDegrees& orientation)
        : m_arguments(orientation)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntDegrees&> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class UpdateCaptureAccess {
public:
    using Arguments = std::tuple<bool, bool, bool, WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_UpdateCaptureAccess; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::GPUProcess_UpdateCaptureAccessReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    UpdateCaptureAccess(bool allowAudioCapture, bool allowVideoCapture, bool allowDisplayCapture, const WebCore::ProcessIdentifier& processID)
        : m_arguments(allowAudioCapture, allowVideoCapture, allowDisplayCapture, processID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool, bool, const WebCore::ProcessIdentifier&> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class UpdateCaptureOrigin {
public:
    using Arguments = std::tuple<WebCore::SecurityOriginData, WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_UpdateCaptureOrigin; }
    static constexpr bool isSync = false;

    UpdateCaptureOrigin(const WebCore::SecurityOriginData& originData, const WebCore::ProcessIdentifier& processID)
        : m_arguments(originData, processID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SecurityOriginData&, const WebCore::ProcessIdentifier&> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class AddMockMediaDevice {
public:
    using Arguments = std::tuple<WebCore::MockMediaDevice>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_AddMockMediaDevice; }
    static constexpr bool isSync = false;

    explicit AddMockMediaDevice(const WebCore::MockMediaDevice& device)
        : m_arguments(device)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MockMediaDevice&> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class ClearMockMediaDevices {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_ClearMockMediaDevices; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class RemoveMockMediaDevice {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_RemoveMockMediaDevice; }
    static constexpr bool isSync = false;

    explicit RemoveMockMediaDevice(const String& persistentId)
        : m_arguments(persistentId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class SetMockMediaDeviceIsEphemeral {
public:
    using Arguments = std::tuple<String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_SetMockMediaDeviceIsEphemeral; }
    static constexpr bool isSync = false;

    SetMockMediaDeviceIsEphemeral(const String& persistentId, bool isEphemeral)
        : m_arguments(persistentId, isEphemeral)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, bool> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class ResetMockMediaDevices {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_ResetMockMediaDevices; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class SetMockCaptureDevicesInterrupted {
public:
    using Arguments = std::tuple<bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_SetMockCaptureDevicesInterrupted; }
    static constexpr bool isSync = false;

    SetMockCaptureDevicesInterrupted(bool isCameraInterrupted, bool isMicrophoneInterrupted)
        : m_arguments(isCameraInterrupted, isMicrophoneInterrupted)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class TriggerMockMicrophoneConfigurationChange {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_TriggerMockMicrophoneConfigurationChange; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if HAVE(SC_CONTENT_SHARING_PICKER)
class SetUseSCContentSharingPicker {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_SetUseSCContentSharingPicker; }
    static constexpr bool isSync = false;

    explicit SetUseSCContentSharingPicker(bool use)
        : m_arguments(use)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};
#endif

#if PLATFORM(MAC)
class DisplayConfigurationChanged {
public:
    using Arguments = std::tuple<CGDirectDisplayID, CGDisplayChangeSummaryFlags>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_DisplayConfigurationChanged; }
    static constexpr bool isSync = false;

    DisplayConfigurationChanged(const CGDirectDisplayID& displayID, const CGDisplayChangeSummaryFlags& flags)
        : m_arguments(displayID, flags)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const CGDirectDisplayID&, const CGDisplayChangeSummaryFlags&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class SetScreenProperties {
public:
    using Arguments = std::tuple<WebCore::ScreenProperties>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_SetScreenProperties; }
    static constexpr bool isSync = false;

    explicit SetScreenProperties(const WebCore::ScreenProperties& screenProperties)
        : m_arguments(screenProperties)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScreenProperties&> m_arguments;
};
#endif

#if HAVE(SCREEN_CAPTURE_KIT)
class PromptForGetDisplayMedia {
public:
    using Arguments = std::tuple<WebCore::DisplayCapturePromptType>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_PromptForGetDisplayMedia; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::GPUProcess_PromptForGetDisplayMediaReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::CaptureDevice>>;
    explicit PromptForGetDisplayMedia(WebCore::DisplayCapturePromptType type)
        : m_arguments(type)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::DisplayCapturePromptType> m_arguments;
};
#endif

#if ENABLE(VIDEO)
class RequestBitmapImageForCurrentTime {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier, WebCore::MediaPlayerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_RequestBitmapImageForCurrentTime; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::GPUProcess_RequestBitmapImageForCurrentTimeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::ShareableBitmap::Handle>;
    RequestBitmapImageForCurrentTime(const WebCore::ProcessIdentifier& processIdentifier, const WebCore::MediaPlayerIdentifier& playerIdentifier)
        : m_arguments(processIdentifier, playerIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&, const WebCore::MediaPlayerIdentifier&> m_arguments;
};
#endif

#if ENABLE(CFPREFS_DIRECT_MODE)
class NotifyPreferencesChanged {
public:
    using Arguments = std::tuple<String, String, std::optional<String>>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_NotifyPreferencesChanged; }
    static constexpr bool isSync = false;

    NotifyPreferencesChanged(const String& domain, const String& key, const std::optional<String>& encodedValue)
        : m_arguments(domain, key, encodedValue)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const std::optional<String>&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class OpenDirectoryCacheInvalidated {
public:
    using Arguments = std::tuple<WebKit::SandboxExtension::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_OpenDirectoryCacheInvalidated; }
    static constexpr bool isSync = false;

    explicit OpenDirectoryCacheInvalidated(const WebKit::SandboxExtension::Handle& handle)
        : m_arguments(handle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::SandboxExtension::Handle&> m_arguments;
};
#endif

#if HAVE(AUDIO_COMPONENT_SERVER_REGISTRATIONS)
class ConsumeAudioComponentRegistrations {
public:
    using Arguments = std::tuple<IPC::SharedBufferReference>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_ConsumeAudioComponentRegistrations; }
    static constexpr bool isSync = false;

    explicit ConsumeAudioComponentRegistrations(const IPC::SharedBufferReference& registrationData)
        : m_arguments(registrationData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::SharedBufferReference&> m_arguments;
};
#endif

#if HAVE(POWERLOG_TASK_MODE_QUERY)
class EnablePowerLogging {
public:
    using Arguments = std::tuple<WebKit::SandboxExtension::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_EnablePowerLogging; }
    static constexpr bool isSync = false;

    explicit EnablePowerLogging(const WebKit::SandboxExtension::Handle& handle)
        : m_arguments(handle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::SandboxExtension::Handle&> m_arguments;
};
#endif

class UserPreferredLanguagesChanged {
public:
    using Arguments = std::tuple<Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_UserPreferredLanguagesChanged; }
    static constexpr bool isSync = false;

    explicit UserPreferredLanguagesChanged(const Vector<String>& languages)
        : m_arguments(languages)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&> m_arguments;
};

class WebProcessConnectionCountForTesting {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcess_WebProcessConnectionCountForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::GPUProcess_WebProcessConnectionCountForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

} // namespace GPUProcess
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
