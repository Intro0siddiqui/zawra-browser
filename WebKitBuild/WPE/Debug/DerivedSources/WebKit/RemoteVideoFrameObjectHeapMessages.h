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

#if ENABLE(GPU_PROCESS) && ENABLE(VIDEO)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "IPCSemaphore.h"
#include "MessageNames.h"
#include "RemoteVideoFrameIdentifier.h"
#include "SharedMemory.h"
#include "SharedVideoFrame.h"
#if PLATFORM(COCOA)
#include <WebCore/CVUtilities.h>
#endif
#include <WebCore/DestinationColorSpace.h>
#include <wtf/Forward.h>
#include <wtf/RetainPtr.h>
#include <wtf/ThreadSafeRefCounted.h>


namespace Messages {
namespace RemoteVideoFrameObjectHeap {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteVideoFrameObjectHeap;
}

#if PLATFORM(COCOA)
class GetVideoFrameBuffer {
public:
    using Arguments = std::tuple<WebKit::RemoteVideoFrameReadReference, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteVideoFrameObjectHeap_GetVideoFrameBuffer; }
    static constexpr bool isSync = false;

    GetVideoFrameBuffer(const WebKit::RemoteVideoFrameReadReference& read, bool canSendIOSurface)
        : m_arguments(read, canSendIOSurface)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteVideoFrameReadReference&, bool> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class PixelBuffer {
public:
    using Arguments = std::tuple<WebKit::RemoteVideoFrameReadReference>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteVideoFrameObjectHeap_PixelBuffer; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<RetainPtr<CVPixelBufferRef>>;
    explicit PixelBuffer(const WebKit::RemoteVideoFrameReadReference& read)
        : m_arguments(read)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteVideoFrameReadReference&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetSharedVideoFrameSemaphore {
public:
    using Arguments = std::tuple<IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteVideoFrameObjectHeap_SetSharedVideoFrameSemaphore; }
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
#endif

#if PLATFORM(COCOA)
class SetSharedVideoFrameMemory {
public:
    using Arguments = std::tuple<WebKit::SharedMemory::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteVideoFrameObjectHeap_SetSharedVideoFrameMemory; }
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
#endif

#if PLATFORM(COCOA)
class ConvertFrameBuffer {
public:
    using Arguments = std::tuple<WebKit::SharedVideoFrame>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteVideoFrameObjectHeap_ConvertFrameBuffer; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DestinationColorSpace>;
    explicit ConvertFrameBuffer(WebKit::SharedVideoFrame&& frame)
        : m_arguments(WTFMove(frame))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::SharedVideoFrame&&> m_arguments;
};
#endif

class ReleaseVideoFrame {
public:
    using Arguments = std::tuple<WebKit::RemoteVideoFrameWriteReference>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteVideoFrameObjectHeap_ReleaseVideoFrame; }
    static constexpr bool isSync = false;

    explicit ReleaseVideoFrame(const WebKit::RemoteVideoFrameWriteReference& write)
        : m_arguments(write)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::RemoteVideoFrameWriteReference&> m_arguments;
};

} // namespace RemoteVideoFrameObjectHeap
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
