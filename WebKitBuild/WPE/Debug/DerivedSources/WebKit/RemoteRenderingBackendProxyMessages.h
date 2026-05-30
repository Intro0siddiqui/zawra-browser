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
#include "IPCSemaphore.h"
#include "MarkSurfacesAsVolatileRequestIdentifier.h"
#include "MessageNames.h"
#include "RenderingUpdateID.h"
#include <WebCore/RenderingResourceIdentifier.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>


namespace Messages {
namespace RemoteRenderingBackendProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteRenderingBackendProxy;
}

class DidFinalizeRenderingUpdate {
public:
    using Arguments = std::tuple<WebKit::RenderingUpdateID>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackendProxy_DidFinalizeRenderingUpdate; }
    static constexpr bool isSync = false;

    explicit DidFinalizeRenderingUpdate(const WebKit::RenderingUpdateID& didRenderingUpdateID)
        : m_arguments(didRenderingUpdateID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RenderingUpdateID&> m_arguments;
};

class DidInitialize {
public:
    using Arguments = std::tuple<IPC::Semaphore, IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackendProxy_DidInitialize; }
    static constexpr bool isSync = false;

    DidInitialize(const IPC::Semaphore& wakeUpSemaphore, const IPC::Semaphore& clientWaitSemaphore)
        : m_arguments(wakeUpSemaphore, clientWaitSemaphore)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::Semaphore&, const IPC::Semaphore&> m_arguments;
};

class DidMarkLayersAsVolatile {
public:
    using Arguments = std::tuple<WebKit::MarkSurfacesAsVolatileRequestIdentifier, Vector<WebCore::RenderingResourceIdentifier>, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteRenderingBackendProxy_DidMarkLayersAsVolatile; }
    static constexpr bool isSync = false;

    DidMarkLayersAsVolatile(const WebKit::MarkSurfacesAsVolatileRequestIdentifier& requestIdentifier, const Vector<WebCore::RenderingResourceIdentifier>& markedVolatileBufferIdentifiers, bool didMarkAllLayersAsVolatile)
        : m_arguments(requestIdentifier, markedVolatileBufferIdentifiers, didMarkAllLayersAsVolatile)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::MarkSurfacesAsVolatileRequestIdentifier&, const Vector<WebCore::RenderingResourceIdentifier>&, bool> m_arguments;
};

} // namespace RemoteRenderingBackendProxy
} // namespace Messages

#endif // ENABLE(GPU_PROCESS)
