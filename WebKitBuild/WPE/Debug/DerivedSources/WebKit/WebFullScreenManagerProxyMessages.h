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

#if ENABLE(FULLSCREEN_API)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace WebCore {
class FloatSize;
class IntRect;
}

namespace Messages {
namespace WebFullScreenManagerProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebFullScreenManagerProxy;
}

class SupportsFullScreen {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebFullScreenManagerProxy_SupportsFullScreen; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit SupportsFullScreen(bool withKeyboard)
        : m_arguments(withKeyboard)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class EnterFullScreen {
public:
    using Arguments = std::tuple<bool, bool, WebCore::FloatSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebFullScreenManagerProxy_EnterFullScreen; }
    static constexpr bool isSync = false;

    EnterFullScreen(bool blocksReturnToFullscreenFromPictureInPicture, bool isVideoElement, const WebCore::FloatSize& videoDimensions)
        : m_arguments(blocksReturnToFullscreenFromPictureInPicture, isVideoElement, videoDimensions)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool, const WebCore::FloatSize&> m_arguments;
};

class ExitFullScreen {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebFullScreenManagerProxy_ExitFullScreen; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class BeganEnterFullScreen {
public:
    using Arguments = std::tuple<WebCore::IntRect, WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebFullScreenManagerProxy_BeganEnterFullScreen; }
    static constexpr bool isSync = false;

    BeganEnterFullScreen(const WebCore::IntRect& initialRect, const WebCore::IntRect& finalRect)
        : m_arguments(initialRect, finalRect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&, const WebCore::IntRect&> m_arguments;
};

class BeganExitFullScreen {
public:
    using Arguments = std::tuple<WebCore::IntRect, WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebFullScreenManagerProxy_BeganExitFullScreen; }
    static constexpr bool isSync = false;

    BeganExitFullScreen(const WebCore::IntRect& initialRect, const WebCore::IntRect& finalRect)
        : m_arguments(initialRect, finalRect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&, const WebCore::IntRect&> m_arguments;
};

class Close {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebFullScreenManagerProxy_Close; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

} // namespace WebFullScreenManagerProxy
} // namespace Messages

#endif // ENABLE(FULLSCREEN_API)
