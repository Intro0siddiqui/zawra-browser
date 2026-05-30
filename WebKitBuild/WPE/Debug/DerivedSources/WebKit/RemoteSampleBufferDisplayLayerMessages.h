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
#include "IPCSemaphore.h"
#include "MessageNames.h"
#include "SharedMemory.h"
#include "SharedVideoFrame.h"
#include <optional>
#include <wtf/Forward.h>
#include <wtf/MachSendRight.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace RemoteSampleBufferDisplayLayer {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteSampleBufferDisplayLayer;
}

#if !RELEASE_LOG_DISABLED
class SetLogIdentifier {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayer_SetLogIdentifier; }
    static constexpr bool isSync = false;

    explicit SetLogIdentifier(const String& logIdentifier)
        : m_arguments(logIdentifier)
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

class UpdateDisplayMode {
public:
    using Arguments = std::tuple<bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayer_UpdateDisplayMode; }
    static constexpr bool isSync = false;

    UpdateDisplayMode(bool hideDisplayLayer, bool hideRootLayer)
        : m_arguments(hideDisplayLayer, hideRootLayer)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool> m_arguments;
};

class UpdateBoundsAndPosition {
public:
    using Arguments = std::tuple<CGRect, std::optional<MachSendRight>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayer_UpdateBoundsAndPosition; }
    static constexpr bool isSync = false;

    UpdateBoundsAndPosition(const CGRect& bounds, std::optional<MachSendRight>&& fence)
        : m_arguments(bounds, WTFMove(fence))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const CGRect&, std::optional<MachSendRight>&&> m_arguments;
};

class Flush {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayer_Flush; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class FlushAndRemoveImage {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayer_FlushAndRemoveImage; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class EnqueueVideoFrame {
public:
    using Arguments = std::tuple<WebKit::SharedVideoFrame>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayer_EnqueueVideoFrame; }
    static constexpr bool isSync = false;

    explicit EnqueueVideoFrame(WebKit::SharedVideoFrame&& frame)
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

class ClearVideoFrames {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayer_ClearVideoFrames; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Play {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayer_Play; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Pause {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayer_Pause; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetSharedVideoFrameSemaphore {
public:
    using Arguments = std::tuple<IPC::Semaphore>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayer_SetSharedVideoFrameSemaphore; }
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

    static IPC::MessageName name() { return IPC::MessageName::RemoteSampleBufferDisplayLayer_SetSharedVideoFrameMemory; }
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

} // namespace RemoteSampleBufferDisplayLayer
} // namespace Messages

#endif // PLATFORM(COCOA) && ENABLE(GPU_PROCESS) && ENABLE(MEDIA_STREAM)
