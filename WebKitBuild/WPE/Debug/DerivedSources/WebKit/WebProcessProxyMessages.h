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

#include "ArgumentCoders.h"
#include "Connection.h"
#include "DisplayLinkObserverID.h"
#include "GPUProcessConnectionParameters.h"
#include "MessageNames.h"
#include "WebPageProxyIdentifier.h"
#include <WebCore/CaptionUserPreferences.h>
#include <WebCore/FrameIdentifier.h>
#include <WebCore/NotificationData.h>
#include <WebCore/PageIdentifier.h>
#include <WebCore/RenderTreeAsText.h>
#include <WebCore/SecurityOriginData.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/OptionSet.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class RegistrableDomain;
class SecurityOriginData;
struct MessageWithMessagePorts;
struct PrewarmInformation;
}

namespace WebKit {
struct BackForwardListItemState;
struct NetworkProcessConnectionInfo;
struct UserMessage;
}

namespace Messages {
namespace WebProcessProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebProcessProxy;
}

class UpdateBackForwardItem {
public:
    using Arguments = std::tuple<WebKit::BackForwardListItemState>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_UpdateBackForwardItem; }
    static constexpr bool isSync = false;

    explicit UpdateBackForwardItem(const WebKit::BackForwardListItemState& backForwardListItemState)
        : m_arguments(backForwardListItemState)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::BackForwardListItemState&> m_arguments;
};

class DidDestroyFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::WebPageProxyIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_DidDestroyFrame; }
    static constexpr bool isSync = false;

    DidDestroyFrame(const WebCore::FrameIdentifier& frameID, const WebKit::WebPageProxyIdentifier& pageID)
        : m_arguments(frameID, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::WebPageProxyIdentifier&> m_arguments;
};

class DidDestroyUserGestureToken {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_DidDestroyUserGestureToken; }
    static constexpr bool isSync = false;

    explicit DidDestroyUserGestureToken(uint64_t userGestureTokenID)
        : m_arguments(userGestureTokenID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class ShouldTerminate {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_ShouldTerminate; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class EnableSuddenTermination {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_EnableSuddenTermination; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DisableSuddenTermination {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_DisableSuddenTermination; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class GetNetworkProcessConnection {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_GetNetworkProcessConnection; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::NetworkProcessConnectionInfo>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if ENABLE(GPU_PROCESS)
class CreateGPUProcessConnection {
public:
    using Arguments = std::tuple<IPC::Connection::Handle, WebKit::GPUProcessConnectionParameters>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_CreateGPUProcessConnection; }
    static constexpr bool isSync = false;

    CreateGPUProcessConnection(IPC::Connection::Handle&& connectionHandle, WebKit::GPUProcessConnectionParameters&& parameters)
        : m_arguments(WTFMove(connectionHandle), WTFMove(parameters))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<IPC::Connection::Handle&&, WebKit::GPUProcessConnectionParameters&&> m_arguments;
};
#endif

class SetIsHoldingLockedFiles {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_SetIsHoldingLockedFiles; }
    static constexpr bool isSync = false;

    explicit SetIsHoldingLockedFiles(bool isHoldingLockedFiles)
        : m_arguments(isHoldingLockedFiles)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class DidExceedActiveMemoryLimit {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_DidExceedActiveMemoryLimit; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidExceedInactiveMemoryLimit {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_DidExceedInactiveMemoryLimit; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidExceedCPULimit {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_DidExceedCPULimit; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class StopResponsivenessTimer {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_StopResponsivenessTimer; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidReceiveBackgroundResponsivenessPing {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_DidReceiveBackgroundResponsivenessPing; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class MemoryPressureStatusChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_MemoryPressureStatusChanged; }
    static constexpr bool isSync = false;

    explicit MemoryPressureStatusChanged(bool isUnderMemoryPressure)
        : m_arguments(isUnderMemoryPressure)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class DidCollectPrewarmInformation {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain, WebCore::PrewarmInformation>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_DidCollectPrewarmInformation; }
    static constexpr bool isSync = false;

    DidCollectPrewarmInformation(const WebCore::RegistrableDomain& domain, const WebCore::PrewarmInformation& prewarmInformation)
        : m_arguments(domain, prewarmInformation)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&, const WebCore::PrewarmInformation&> m_arguments;
};

#if PLATFORM(COCOA)
class CacheMediaMIMETypes {
public:
    using Arguments = std::tuple<Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_CacheMediaMIMETypes; }
    static constexpr bool isSync = false;

    explicit CacheMediaMIMETypes(const Vector<String>& types)
        : m_arguments(types)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class RequestHighPerformanceGPU {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_RequestHighPerformanceGPU; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(MAC)
class ReleaseHighPerformanceGPU {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_ReleaseHighPerformanceGPU; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if HAVE(CVDISPLAYLINK)
class StartDisplayLink {
public:
    using Arguments = std::tuple<WebKit::DisplayLinkObserverID, uint32_t, unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_StartDisplayLink; }
    static constexpr bool isSync = false;

    StartDisplayLink(const WebKit::DisplayLinkObserverID& observerID, uint32_t displayID, const unsigned& preferredFramesPerSecond)
        : m_arguments(observerID, displayID, preferredFramesPerSecond)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DisplayLinkObserverID&, uint32_t, const unsigned&> m_arguments;
};
#endif

#if HAVE(CVDISPLAYLINK)
class StopDisplayLink {
public:
    using Arguments = std::tuple<WebKit::DisplayLinkObserverID, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_StopDisplayLink; }
    static constexpr bool isSync = false;

    StopDisplayLink(const WebKit::DisplayLinkObserverID& observerID, uint32_t displayID)
        : m_arguments(observerID, displayID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DisplayLinkObserverID&, uint32_t> m_arguments;
};
#endif

#if HAVE(CVDISPLAYLINK)
class SetDisplayLinkPreferredFramesPerSecond {
public:
    using Arguments = std::tuple<WebKit::DisplayLinkObserverID, uint32_t, unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_SetDisplayLinkPreferredFramesPerSecond; }
    static constexpr bool isSync = false;

    SetDisplayLinkPreferredFramesPerSecond(const WebKit::DisplayLinkObserverID& observerID, uint32_t displayID, const unsigned& preferredFramesPerSecond)
        : m_arguments(observerID, displayID, preferredFramesPerSecond)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DisplayLinkObserverID&, uint32_t, const unsigned&> m_arguments;
};
#endif

#if PLATFORM(GTK) || PLATFORM(WPE)
class SendMessageToWebContext {
public:
    using Arguments = std::tuple<WebKit::UserMessage>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_SendMessageToWebContext; }
    static constexpr bool isSync = false;

    explicit SendMessageToWebContext(const WebKit::UserMessage& userMessage)
        : m_arguments(userMessage)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::UserMessage&> m_arguments;
};
#endif

#if PLATFORM(GTK) || PLATFORM(WPE)
class SendMessageToWebContextWithReply {
public:
    using Arguments = std::tuple<WebKit::UserMessage>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_SendMessageToWebContextWithReply; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcessProxy_SendMessageToWebContextWithReplyReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::UserMessage>;
    explicit SendMessageToWebContextWithReply(const WebKit::UserMessage& userMessage)
        : m_arguments(userMessage)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::UserMessage&> m_arguments;
};
#endif

class CreateSpeechRecognitionServer {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_CreateSpeechRecognitionServer; }
    static constexpr bool isSync = false;

    explicit CreateSpeechRecognitionServer(const WebCore::PageIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&> m_arguments;
};

class DestroySpeechRecognitionServer {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_DestroySpeechRecognitionServer; }
    static constexpr bool isSync = false;

    explicit DestroySpeechRecognitionServer(const WebCore::PageIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&> m_arguments;
};

class SystemBeep {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_SystemBeep; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if PLATFORM(MAC)
class IsAXAuthenticated {
public:
    using Arguments = std::tuple<audit_token_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_IsAXAuthenticated; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit IsAXAuthenticated(const audit_token_t& auditToken)
        : m_arguments(auditToken)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const audit_token_t&> m_arguments;
};
#endif

#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
class SetCaptionDisplayMode {
public:
    using Arguments = std::tuple<WebCore::CaptionUserPreferences::CaptionDisplayMode>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_SetCaptionDisplayMode; }
    static constexpr bool isSync = false;

    explicit SetCaptionDisplayMode(const WebCore::CaptionUserPreferences::CaptionDisplayMode& mode)
        : m_arguments(mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::CaptionUserPreferences::CaptionDisplayMode&> m_arguments;
};
#endif

#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
class SetCaptionLanguage {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_SetCaptionLanguage; }
    static constexpr bool isSync = false;

    explicit SetCaptionLanguage(const String& language)
        : m_arguments(language)
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

class GetNotifications {
public:
    using Arguments = std::tuple<URL, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_GetNotifications; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcessProxy_GetNotificationsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::NotificationData>>;
    GetNotifications(const URL& registrationURL, const String& tag)
        : m_arguments(registrationURL, tag)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const String&> m_arguments;
};

class SetAppBadge {
public:
    using Arguments = std::tuple<std::optional<WebKit::WebPageProxyIdentifier>, WebCore::SecurityOriginData, std::optional<uint64_t>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_SetAppBadge; }
    static constexpr bool isSync = false;

    SetAppBadge(const std::optional<WebKit::WebPageProxyIdentifier>& pageIdentifier, const WebCore::SecurityOriginData& origin, const std::optional<uint64_t>& badge)
        : m_arguments(pageIdentifier, origin, badge)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebKit::WebPageProxyIdentifier>&, const WebCore::SecurityOriginData&, const std::optional<uint64_t>&> m_arguments;
};

class SetClientBadge {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebCore::SecurityOriginData, std::optional<uint64_t>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_SetClientBadge; }
    static constexpr bool isSync = false;

    SetClientBadge(const WebKit::WebPageProxyIdentifier& pageIdentifier, const WebCore::SecurityOriginData& origin, const std::optional<uint64_t>& badge)
        : m_arguments(pageIdentifier, origin, badge)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebCore::SecurityOriginData&, const std::optional<uint64_t>&> m_arguments;
};

class PostMessageToRemote {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, std::optional<WebCore::SecurityOriginData>, WebCore::MessageWithMessagePorts>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_PostMessageToRemote; }
    static constexpr bool isSync = false;

    PostMessageToRemote(const WebCore::FrameIdentifier& identifier, const std::optional<WebCore::SecurityOriginData>& target, const WebCore::MessageWithMessagePorts& message)
        : m_arguments(identifier, target, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const std::optional<WebCore::SecurityOriginData>&, const WebCore::MessageWithMessagePorts&> m_arguments;
};

class RenderTreeAsText {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, size_t, OptionSet<WebCore::RenderAsTextFlag>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcessProxy_RenderTreeAsText; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    RenderTreeAsText(const WebCore::FrameIdentifier& identifier, size_t baseIndent, const OptionSet<WebCore::RenderAsTextFlag>& behavior)
        : m_arguments(identifier, baseIndent, behavior)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, size_t, const OptionSet<WebCore::RenderAsTextFlag>&> m_arguments;
};

} // namespace WebProcessProxy
} // namespace Messages
