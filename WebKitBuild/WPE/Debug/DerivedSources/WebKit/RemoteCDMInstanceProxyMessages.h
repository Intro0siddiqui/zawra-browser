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

#if ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#if ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)
#include "RemoteCDMInstanceSessionIdentifier.h"
#endif
#include <WebCore/CDMInstance.h>
#include <WebCore/SharedBuffer.h>
#include <wtf/Forward.h>
#include <wtf/Ref.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
struct CDMKeySystemConfiguration;
}

namespace Messages {
namespace RemoteCDMInstanceProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteCDMInstanceProxy;
}

class CreateSession {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceProxy_CreateSession; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::RemoteCDMInstanceSessionIdentifier>;
    explicit CreateSession(uint64_t logIdentifier)
        : m_arguments(logIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class InitializeWithConfiguration {
public:
    using Arguments = std::tuple<WebCore::CDMKeySystemConfiguration, WebCore::CDMInstance::AllowDistinctiveIdentifiers, WebCore::CDMInstance::AllowPersistentState>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceProxy_InitializeWithConfiguration; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteCDMInstanceProxy_InitializeWithConfigurationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::CDMInstance::SuccessValue>;
    InitializeWithConfiguration(const WebCore::CDMKeySystemConfiguration& configuration, WebCore::CDMInstance::AllowDistinctiveIdentifiers distinctiveIdentifiersAllowed, WebCore::CDMInstance::AllowPersistentState persistentStateAllowed)
        : m_arguments(configuration, distinctiveIdentifiersAllowed, persistentStateAllowed)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::CDMKeySystemConfiguration&, WebCore::CDMInstance::AllowDistinctiveIdentifiers, WebCore::CDMInstance::AllowPersistentState> m_arguments;
};

class SetServerCertificate {
public:
    using Arguments = std::tuple<Ref<WebCore::SharedBuffer>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceProxy_SetServerCertificate; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteCDMInstanceProxy_SetServerCertificateReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::CDMInstance::SuccessValue>;
    explicit SetServerCertificate(const Ref<WebCore::SharedBuffer>& certificate)
        : m_arguments(certificate)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Ref<WebCore::SharedBuffer>&> m_arguments;
};

class SetStorageDirectory {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceProxy_SetStorageDirectory; }
    static constexpr bool isSync = false;

    explicit SetStorageDirectory(const String& directory)
        : m_arguments(directory)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

} // namespace RemoteCDMInstanceProxy
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)
