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
namespace RemoteWebInspectorUIProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteWebInspectorUIProxy;
}

class FrontendLoaded {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_FrontendLoaded; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class FrontendDidClose {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_FrontendDidClose; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_Reopen; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_ResetState; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_BringToFront; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Save {
public:
    using Arguments = std::tuple<Vector<WebCore::InspectorFrontendClient::SaveData>, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_Save; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_Load; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteWebInspectorUIProxy_LoadReply; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_PickColorFromScreen; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteWebInspectorUIProxy_PickColorFromScreenReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::Color>>;
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_SetForcedAppearance; }
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

class SetSheetRect {
public:
    using Arguments = std::tuple<WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_SetSheetRect; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_StartWindowDrag; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class OpenURLExternally {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_OpenURLExternally; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_RevealFileExternally; }
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

class ShowCertificate {
public:
    using Arguments = std::tuple<WebCore::CertificateInfo>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_ShowCertificate; }
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

class SendMessageToBackend {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_SendMessageToBackend; }
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

class SetInspectorPageDeveloperExtrasEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebInspectorUIProxy_SetInspectorPageDeveloperExtrasEnabled; }
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

} // namespace RemoteWebInspectorUIProxy
} // namespace Messages
