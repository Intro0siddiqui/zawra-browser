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
#include "LayerHostingContext.h"
#include "MessageNames.h"
#include "WebPageProxyIdentifier.h"
#include <WebCore/PageIdentifier.h>
#include <WebCore/ProcessIdentifier.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>


namespace Messages {
namespace GPUProcessProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::GPUProcessProxy;
}

#if HAVE(VISIBILITY_PROPAGATION_VIEW)
class DidCreateContextForVisibilityPropagation {
public:
    using Arguments = std::tuple<WebKit::WebPageProxyIdentifier, WebCore::PageIdentifier, WebKit::LayerHostingContextID>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcessProxy_DidCreateContextForVisibilityPropagation; }
    static constexpr bool isSync = false;

    DidCreateContextForVisibilityPropagation(const WebKit::WebPageProxyIdentifier& pageProxyID, const WebCore::PageIdentifier& pageID, const WebKit::LayerHostingContextID& contextID)
        : m_arguments(pageProxyID, pageID, contextID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPageProxyIdentifier&, const WebCore::PageIdentifier&, const WebKit::LayerHostingContextID&> m_arguments;
};
#endif

#if ENABLE(VP9)
class SetHasVP9HardwareDecoder {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcessProxy_SetHasVP9HardwareDecoder; }
    static constexpr bool isSync = false;

    explicit SetHasVP9HardwareDecoder(bool hasVP9HardwareDecoder)
        : m_arguments(hasVP9HardwareDecoder)
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

#if ENABLE(VP9)
class SetHasVP9ExtensionSupport {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcessProxy_SetHasVP9ExtensionSupport; }
    static constexpr bool isSync = false;

    explicit SetHasVP9ExtensionSupport(bool hasVP9ExtensionSupport)
        : m_arguments(hasVP9ExtensionSupport)
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

#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)
class StatusBarWasTapped {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcessProxy_StatusBarWasTapped; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::GPUProcessProxy_StatusBarWasTappedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class ProcessIsReadyToExit {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcessProxy_ProcessIsReadyToExit; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class TerminateWebProcess {
public:
    using Arguments = std::tuple<WebCore::ProcessIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::GPUProcessProxy_TerminateWebProcess; }
    static constexpr bool isSync = false;

    explicit TerminateWebProcess(const WebCore::ProcessIdentifier& webProcessIdentifier)
        : m_arguments(webProcessIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ProcessIdentifier&> m_arguments;
};

} // namespace GPUProcessProxy
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
