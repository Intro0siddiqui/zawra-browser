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
#include <WebCore/FrameIdentifier.h>
#include <WebCore/SpeechRecognitionConnectionClientIdentifier.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
struct ClientOrigin;
}

namespace Messages {
namespace SpeechRecognitionServer {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::SpeechRecognitionServer;
}

class Start {
public:
    using Arguments = std::tuple<WebCore::SpeechRecognitionConnectionClientIdentifier, String, bool, bool, uint64_t, WebCore::ClientOrigin, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionServer_Start; }
    static constexpr bool isSync = false;

    Start(const WebCore::SpeechRecognitionConnectionClientIdentifier& identifier, const String& lang, bool continuous, bool interimResults, uint64_t maxAlternatives, const WebCore::ClientOrigin& origin, const WebCore::FrameIdentifier& frameIdentifier)
        : m_arguments(identifier, lang, continuous, interimResults, maxAlternatives, origin, frameIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SpeechRecognitionConnectionClientIdentifier&, const String&, bool, bool, uint64_t, const WebCore::ClientOrigin&, const WebCore::FrameIdentifier&> m_arguments;
};

class Stop {
public:
    using Arguments = std::tuple<WebCore::SpeechRecognitionConnectionClientIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionServer_Stop; }
    static constexpr bool isSync = false;

    explicit Stop(const WebCore::SpeechRecognitionConnectionClientIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SpeechRecognitionConnectionClientIdentifier&> m_arguments;
};

class Abort {
public:
    using Arguments = std::tuple<WebCore::SpeechRecognitionConnectionClientIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionServer_Abort; }
    static constexpr bool isSync = false;

    explicit Abort(const WebCore::SpeechRecognitionConnectionClientIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SpeechRecognitionConnectionClientIdentifier&> m_arguments;
};

class Invalidate {
public:
    using Arguments = std::tuple<WebCore::SpeechRecognitionConnectionClientIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::SpeechRecognitionServer_Invalidate; }
    static constexpr bool isSync = false;

    explicit Invalidate(const WebCore::SpeechRecognitionConnectionClientIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SpeechRecognitionConnectionClientIdentifier&> m_arguments;
};

} // namespace SpeechRecognitionServer
} // namespace Messages
