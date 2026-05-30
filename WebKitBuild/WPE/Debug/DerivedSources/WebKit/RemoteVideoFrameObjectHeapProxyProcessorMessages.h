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

#if PLATFORM(COCOA) && ENABLE(GPU_PROCESS) && ENABLE(VIDEO)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "IPCSemaphore.h"
#include "MessageNames.h"
#include "RemoteVideoFrameIdentifier.h"
#include "SharedMemory.h"
#include "SharedVideoFrame.h"
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>


namespace Messages {
namespace RemoteVideoFrameObjectHeapProxyProcessor {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteVideoFrameObjectHeapProxyProcessor;
}

class SetSharedVideoFrameSemaphore {
public:
    using Arguments = std::tuple<IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteVideoFrameObjectHeapProxyProcessor_SetSharedVideoFrameSemaphore; }
    static constexpr bool isSync = false;

    explicit SetSharedVideoFrameSemaphore(const IPC::Semaphore& semaphore)
        : m_arguments(semaphore)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::Semaphore&> m_arguments;
};

class SetSharedVideoFrameMemory {
public:
    using Arguments = std::tuple<WebKit::SharedMemory::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteVideoFrameObjectHeapProxyProcessor_SetSharedVideoFrameMemory; }
    static constexpr bool isSync = false;

    explicit SetSharedVideoFrameMemory(WebKit::SharedMemory::Handle&& storageHandle)
        : m_arguments(WTFMove(storageHandle))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::SharedMemory::Handle&&> m_arguments;
};

class NewVideoFrameBuffer {
public:
    using Arguments = std::tuple<WebKit::RemoteVideoFrameIdentifier, std::optional<WebKit::SharedVideoFrame::Buffer>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteVideoFrameObjectHeapProxyProcessor_NewVideoFrameBuffer; }
    static constexpr bool isSync = false;

    NewVideoFrameBuffer(const WebKit::RemoteVideoFrameIdentifier& identifier, std::optional<WebKit::SharedVideoFrame::Buffer>&& frame)
        : m_arguments(identifier, WTFMove(frame))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteVideoFrameIdentifier&, std::optional<WebKit::SharedVideoFrame::Buffer>&&> m_arguments;
};

class NewConvertedVideoFrameBuffer {
public:
    using Arguments = std::tuple<std::optional<WebKit::SharedVideoFrame::Buffer>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteVideoFrameObjectHeapProxyProcessor_NewConvertedVideoFrameBuffer; }
    static constexpr bool isSync = false;

    explicit NewConvertedVideoFrameBuffer(std::optional<WebKit::SharedVideoFrame::Buffer>&& frame)
        : m_arguments(WTFMove(frame))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<std::optional<WebKit::SharedVideoFrame::Buffer>&&> m_arguments;
};

} // namespace RemoteVideoFrameObjectHeapProxyProcessor
} // namespace Messages

#endif // PLATFORM(COCOA) && ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
