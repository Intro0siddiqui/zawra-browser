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

#if PLATFORM(COCOA) && ENABLE(GPU_PROCESS) && ENABLE(MEDIA_STREAM)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "LayerHostingContext.h"
#include "MessageNames.h"
#include "SampleBufferDisplayLayerIdentifier.h"
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace WebCore {
class IntSize;
}

namespace Messages {
namespace RemoteSampleBufferDisplayLayerManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteSampleBufferDisplayLayerManager;
}

class CreateLayer {
public:
    using Arguments = std::tuple<WebKit::SampleBufferDisplayLayerIdentifier, bool, WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayerManager_CreateLayer; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteSampleBufferDisplayLayerManager_CreateLayerReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::LayerHostingContextID>>;
    CreateLayer(const WebKit::SampleBufferDisplayLayerIdentifier& id, bool hideRootLayer, const WebCore::IntSize& size)
        : m_arguments(id, hideRootLayer, size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::SampleBufferDisplayLayerIdentifier&, bool, const WebCore::IntSize&> m_arguments;
};

class ReleaseLayer {
public:
    using Arguments = std::tuple<WebKit::SampleBufferDisplayLayerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayerManager_ReleaseLayer; }
    static constexpr bool isSync = false;

    explicit ReleaseLayer(const WebKit::SampleBufferDisplayLayerIdentifier& id)
        : m_arguments(id)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::SampleBufferDisplayLayerIdentifier&> m_arguments;
};

} // namespace RemoteSampleBufferDisplayLayerManager
} // namespace Messages

#endif // PLATFORM(COCOA) && ENABLE(GPU_PROCESS) && ENABLE(MEDIA_STREAM)
