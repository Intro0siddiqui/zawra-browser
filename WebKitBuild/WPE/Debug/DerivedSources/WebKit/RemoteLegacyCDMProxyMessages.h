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

#if ENABLE(GPU_PROCESS) && ENABLE(LEGACY_ENCRYPTED_MEDIA)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#if ENABLE(GPU_PROCESS) && ENABLE(LEGACY_ENCRYPTED_MEDIA)
#include "RemoteLegacyCDMSessionIdentifier.h"
#endif
#include <WebCore/MediaPlayerIdentifier.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace RemoteLegacyCDMProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteLegacyCDMProxy;
}

class SupportsMIMEType {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteLegacyCDMProxy_SupportsMIMEType; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit SupportsMIMEType(const String& mimeType)
        : m_arguments(mimeType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class CreateSession {
public:
    using Arguments = std::tuple<String, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteLegacyCDMProxy_CreateSession; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::RemoteLegacyCDMSessionIdentifier>;
    CreateSession(const String& mediaKeysStorageDirectory, uint64_t logIdentifier)
        : m_arguments(mediaKeysStorageDirectory, logIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, uint64_t> m_arguments;
};

class SetPlayerId {
public:
    using Arguments = std::tuple<std::optional<WebCore::MediaPlayerIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteLegacyCDMProxy_SetPlayerId; }
    static constexpr bool isSync = false;

    explicit SetPlayerId(const std::optional<WebCore::MediaPlayerIdentifier>& playerId)
        : m_arguments(playerId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::MediaPlayerIdentifier>&> m_arguments;
};

} // namespace RemoteLegacyCDMProxy
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(LEGACY_ENCRYPTED_MEDIA)
