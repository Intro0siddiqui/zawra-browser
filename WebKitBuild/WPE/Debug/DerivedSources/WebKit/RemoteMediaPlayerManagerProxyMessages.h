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
#include "MessageNames.h"
#include <WebCore/MediaPlayerEnums.h>
#include <WebCore/MediaPlayerIdentifier.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
struct MediaEngineSupportParameters;
}

namespace WebKit {
struct RemoteMediaPlayerProxyConfiguration;
}

namespace Messages {
namespace RemoteMediaPlayerManagerProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteMediaPlayerManagerProxy;
}

class CreateMediaPlayer {
public:
    using Arguments = std::tuple<WebCore::MediaPlayerIdentifier, WebCore::MediaPlayerEnums::MediaEngineIdentifier, WebKit::RemoteMediaPlayerProxyConfiguration>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerManagerProxy_CreateMediaPlayer; }
    static constexpr bool isSync = false;

    CreateMediaPlayer(const WebCore::MediaPlayerIdentifier& identifier, WebCore::MediaPlayerEnums::MediaEngineIdentifier remoteEngineIdentifier, const WebKit::RemoteMediaPlayerProxyConfiguration& proxyConfiguration)
        : m_arguments(identifier, remoteEngineIdentifier, proxyConfiguration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaPlayerIdentifier&, WebCore::MediaPlayerEnums::MediaEngineIdentifier, const WebKit::RemoteMediaPlayerProxyConfiguration&> m_arguments;
};

class DeleteMediaPlayer {
public:
    using Arguments = std::tuple<WebCore::MediaPlayerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerManagerProxy_DeleteMediaPlayer; }
    static constexpr bool isSync = false;

    explicit DeleteMediaPlayer(const WebCore::MediaPlayerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaPlayerIdentifier&> m_arguments;
};

class GetSupportedTypes {
public:
    using Arguments = std::tuple<WebCore::MediaPlayerEnums::MediaEngineIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerManagerProxy_GetSupportedTypes; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    explicit GetSupportedTypes(WebCore::MediaPlayerEnums::MediaEngineIdentifier remoteEngineIdentifier)
        : m_arguments(remoteEngineIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::MediaPlayerEnums::MediaEngineIdentifier> m_arguments;
};

class SupportsTypeAndCodecs {
public:
    using Arguments = std::tuple<WebCore::MediaPlayerEnums::MediaEngineIdentifier, WebCore::MediaEngineSupportParameters>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerManagerProxy_SupportsTypeAndCodecs; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::MediaPlayerEnums::SupportsType>;
    SupportsTypeAndCodecs(WebCore::MediaPlayerEnums::MediaEngineIdentifier remoteEngineIdentifier, const WebCore::MediaEngineSupportParameters& type)
        : m_arguments(remoteEngineIdentifier, type)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::MediaPlayerEnums::MediaEngineIdentifier, const WebCore::MediaEngineSupportParameters&> m_arguments;
};

class SupportsKeySystem {
public:
    using Arguments = std::tuple<WebCore::MediaPlayerEnums::MediaEngineIdentifier, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteMediaPlayerManagerProxy_SupportsKeySystem; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    SupportsKeySystem(WebCore::MediaPlayerEnums::MediaEngineIdentifier remoteEngineIdentifier, const String& keySystem, const String& mimeType)
        : m_arguments(remoteEngineIdentifier, keySystem, mimeType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::MediaPlayerEnums::MediaEngineIdentifier, const String&, const String&> m_arguments;
};

} // namespace RemoteMediaPlayerManagerProxy
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(VIDEO)
