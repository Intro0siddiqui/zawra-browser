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
#include <WebCore/Cookie.h>
#include <WebCore/FrameIdentifier.h>
#include <WebCore/IntPoint.h>
#include <WebCore/PageIdentifier.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class FloatRect;
class IntRect;
}

namespace WebKit {
enum class CoordinateSystem : uint8_t;
}

namespace Messages {
namespace WebAutomationSessionProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebAutomationSessionProxy;
}

class EvaluateJavaScriptFunction {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, String, Vector<String>, bool, std::optional<double>, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_EvaluateJavaScriptFunction; }
    static constexpr bool isSync = false;

    EvaluateJavaScriptFunction(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, const String& function, const Vector<String>& arguments, bool expectsImplicitCallbackArgument, const std::optional<double>& callbackTimeout, uint64_t callbackID)
        : m_arguments(pageID, frameID, function, arguments, expectsImplicitCallbackArgument, callbackTimeout, callbackID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const String&, const Vector<String>&, bool, const std::optional<double>&, uint64_t> m_arguments;
};

class ResolveChildFrameWithOrdinal {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_ResolveChildFrameWithOrdinal; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_ResolveChildFrameWithOrdinalReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>, std::optional<WebCore::FrameIdentifier>>;
    ResolveChildFrameWithOrdinal(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, uint32_t ordinal)
        : m_arguments(pageID, frameID, ordinal)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, uint32_t> m_arguments;
};

class ResolveChildFrameWithNodeHandle {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_ResolveChildFrameWithNodeHandle; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_ResolveChildFrameWithNodeHandleReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>, std::optional<WebCore::FrameIdentifier>>;
    ResolveChildFrameWithNodeHandle(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, const String& nodeHandle)
        : m_arguments(pageID, frameID, nodeHandle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const String&> m_arguments;
};

class ResolveChildFrameWithName {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_ResolveChildFrameWithName; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_ResolveChildFrameWithNameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>, std::optional<WebCore::FrameIdentifier>>;
    ResolveChildFrameWithName(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, const String& name)
        : m_arguments(pageID, frameID, name)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const String&> m_arguments;
};

class ResolveParentFrame {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_ResolveParentFrame; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_ResolveParentFrameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>, std::optional<WebCore::FrameIdentifier>>;
    ResolveParentFrame(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID)
        : m_arguments(pageID, frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&> m_arguments;
};

class ComputeElementLayout {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, String, bool, WebKit::CoordinateSystem>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_ComputeElementLayout; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_ComputeElementLayoutReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>, WebCore::FloatRect, std::optional<WebCore::IntPoint>, bool>;
    ComputeElementLayout(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, const String& nodeHandle, bool scrollIntoViewIfNeeded, WebKit::CoordinateSystem coordinateSystem)
        : m_arguments(pageID, frameID, nodeHandle, scrollIntoViewIfNeeded, coordinateSystem)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const String&, bool, WebKit::CoordinateSystem> m_arguments;
};

class GetComputedRole {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_GetComputedRole; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_GetComputedRoleReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>, std::optional<String>>;
    GetComputedRole(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, const String& nodeHandle)
        : m_arguments(pageID, frameID, nodeHandle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const String&> m_arguments;
};

class GetComputedLabel {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_GetComputedLabel; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_GetComputedLabelReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>, std::optional<String>>;
    GetComputedLabel(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, const String& nodeHandle)
        : m_arguments(pageID, frameID, nodeHandle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const String&> m_arguments;
};

class SelectOptionElement {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_SelectOptionElement; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_SelectOptionElementReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>>;
    SelectOptionElement(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, const String& nodeHandle)
        : m_arguments(pageID, frameID, nodeHandle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const String&> m_arguments;
};

class SetFilesForInputFileUpload {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, String, Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_SetFilesForInputFileUpload; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_SetFilesForInputFileUploadReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>>;
    SetFilesForInputFileUpload(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, const String& nodeHandle, const Vector<String>& filenames)
        : m_arguments(pageID, frameID, nodeHandle, filenames)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const String&, const Vector<String>&> m_arguments;
};

class TakeScreenshot {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, String, bool, bool, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_TakeScreenshot; }
    static constexpr bool isSync = false;

    TakeScreenshot(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, const String& nodeHandle, bool scrollIntoViewIfNeeded, bool clipToViewport, uint64_t callbackID)
        : m_arguments(pageID, frameID, nodeHandle, scrollIntoViewIfNeeded, clipToViewport, callbackID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const String&, bool, bool, uint64_t> m_arguments;
};

class SnapshotRectForScreenshot {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, String, bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_SnapshotRectForScreenshot; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_SnapshotRectForScreenshotReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>, WebCore::IntRect>;
    SnapshotRectForScreenshot(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, const String& nodeHandle, bool scrollIntoViewIfNeeded, bool clipToViewport)
        : m_arguments(pageID, frameID, nodeHandle, scrollIntoViewIfNeeded, clipToViewport)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const String&, bool, bool> m_arguments;
};

class GetCookiesForFrame {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_GetCookiesForFrame; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_GetCookiesForFrameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>, Vector<WebCore::Cookie>>;
    GetCookiesForFrame(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID)
        : m_arguments(pageID, frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&> m_arguments;
};

class DeleteCookie {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, std::optional<WebCore::FrameIdentifier>, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebAutomationSessionProxy_DeleteCookie; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebAutomationSessionProxy_DeleteCookieReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<String>>;
    DeleteCookie(const WebCore::PageIdentifier& pageID, const std::optional<WebCore::FrameIdentifier>& frameID, const String& cookieName)
        : m_arguments(pageID, frameID, cookieName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const std::optional<WebCore::FrameIdentifier>&, const String&> m_arguments;
};

} // namespace WebAutomationSessionProxy
} // namespace Messages
