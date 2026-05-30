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
#include "MessageNames.h"
#include <WebCore/Color.h>
#include <WebCore/InspectorClient.h>
#include <WebCore/InspectorFrontendClient.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class CertificateInfo;
class FloatRect;
}

namespace Messages {
namespace WebInspectorUIProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebInspectorUIProxy;
}

class OpenLocalInspectorFrontend {
public:
    using Arguments = std::tuple<bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_OpenLocalInspectorFrontend; }
    static constexpr bool isSync = false;

    OpenLocalInspectorFrontend(bool canAttach, bool underTest)
        : m_arguments(canAttach, underTest)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool> m_arguments;
};

class SetFrontendConnection {
public:
    using Arguments = std::tuple<IPC::Connection::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_SetFrontendConnection; }
    static constexpr bool isSync = false;

    explicit SetFrontendConnection(IPC::Connection::Handle&& connectionHandle)
        : m_arguments(WTFMove(connectionHandle))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<IPC::Connection::Handle&&> m_arguments;
};

class SendMessageToBackend {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_SendMessageToBackend; }
    static constexpr bool isSync = false;

    explicit SendMessageToBackend(const String& message)
        : m_arguments(message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class FrontendLoaded {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_FrontendLoaded; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidClose {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_DidClose; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class BringToFront {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_BringToFront; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Reopen {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_Reopen; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ResetState {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_ResetState; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetForcedAppearance {
public:
    using Arguments = std::tuple<WebCore::InspectorFrontendClient::Appearance>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_SetForcedAppearance; }
    static constexpr bool isSync = false;

    explicit SetForcedAppearance(const WebCore::InspectorFrontendClient::Appearance& appearance)
        : m_arguments(appearance)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::InspectorFrontendClient::Appearance&> m_arguments;
};

class OpenURLExternally {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_OpenURLExternally; }
    static constexpr bool isSync = false;

    explicit OpenURLExternally(const String& url)
        : m_arguments(url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RevealFileExternally {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_RevealFileExternally; }
    static constexpr bool isSync = false;

    explicit RevealFileExternally(const String& path)
        : m_arguments(path)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class InspectedURLChanged {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_InspectedURLChanged; }
    static constexpr bool isSync = false;

    explicit InspectedURLChanged(const String& urlString)
        : m_arguments(urlString)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class ShowCertificate {
public:
    using Arguments = std::tuple<WebCore::CertificateInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_ShowCertificate; }
    static constexpr bool isSync = false;

    explicit ShowCertificate(const WebCore::CertificateInfo& certificateInfo)
        : m_arguments(certificateInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::CertificateInfo&> m_arguments;
};

class ElementSelectionChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_ElementSelectionChanged; }
    static constexpr bool isSync = false;

    explicit ElementSelectionChanged(bool active)
        : m_arguments(active)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class TimelineRecordingChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_TimelineRecordingChanged; }
    static constexpr bool isSync = false;

    explicit TimelineRecordingChanged(bool active)
        : m_arguments(active)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetDeveloperPreferenceOverride {
public:
    using Arguments = std::tuple<WebCore::InspectorClient::DeveloperPreference, std::optional<bool>>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_SetDeveloperPreferenceOverride; }
    static constexpr bool isSync = false;

    SetDeveloperPreferenceOverride(const WebCore::InspectorClient::DeveloperPreference& developerPreference, const std::optional<bool>& overrideValue)
        : m_arguments(developerPreference, overrideValue)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::InspectorClient::DeveloperPreference&, const std::optional<bool>&> m_arguments;
};

#if ENABLE(INSPECTOR_NETWORK_THROTTLING)
class SetEmulatedConditions {
public:
    using Arguments = std::tuple<std::optional<int64_t>>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_SetEmulatedConditions; }
    static constexpr bool isSync = false;

    explicit SetEmulatedConditions(const std::optional<int64_t>& bytesPerSecondLimit)
        : m_arguments(bytesPerSecondLimit)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<int64_t>&> m_arguments;
};
#endif

class Save {
public:
    using Arguments = std::tuple<Vector<WebCore::InspectorFrontendClient::SaveData>, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_Save; }
    static constexpr bool isSync = false;

    Save(const Vector<WebCore::InspectorFrontendClient::SaveData>& saveDatas, bool forceSaveAs)
        : m_arguments(saveDatas, forceSaveAs)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::InspectorFrontendClient::SaveData>&, bool> m_arguments;
};

class Load {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_Load; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebInspectorUIProxy_LoadReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit Load(const String& path)
        : m_arguments(path)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class PickColorFromScreen {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_PickColorFromScreen; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebInspectorUIProxy_PickColorFromScreenReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::Color>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class AttachBottom {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_AttachBottom; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class AttachRight {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_AttachRight; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class AttachLeft {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_AttachLeft; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Detach {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_Detach; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class AttachAvailabilityChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_AttachAvailabilityChanged; }
    static constexpr bool isSync = false;

    explicit AttachAvailabilityChanged(bool available)
        : m_arguments(available)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetAttachedWindowHeight {
public:
    using Arguments = std::tuple<unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_SetAttachedWindowHeight; }
    static constexpr bool isSync = false;

    explicit SetAttachedWindowHeight(const unsigned& height)
        : m_arguments(height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const unsigned&> m_arguments;
};

class SetAttachedWindowWidth {
public:
    using Arguments = std::tuple<unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_SetAttachedWindowWidth; }
    static constexpr bool isSync = false;

    explicit SetAttachedWindowWidth(const unsigned& width)
        : m_arguments(width)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const unsigned&> m_arguments;
};

class SetSheetRect {
public:
    using Arguments = std::tuple<WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_SetSheetRect; }
    static constexpr bool isSync = false;

    explicit SetSheetRect(const WebCore::FloatRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&> m_arguments;
};

class StartWindowDrag {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_StartWindowDrag; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetInspectorPageDeveloperExtrasEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebInspectorUIProxy_SetInspectorPageDeveloperExtrasEnabled; }
    static constexpr bool isSync = false;

    explicit SetInspectorPageDeveloperExtrasEnabled(bool enabled)
        : m_arguments(enabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

} // namespace WebInspectorUIProxy
} // namespace Messages
