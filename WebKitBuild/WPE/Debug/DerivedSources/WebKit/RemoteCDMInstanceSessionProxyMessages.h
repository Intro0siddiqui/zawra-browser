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
#include <WebCore/CDMInstanceSession.h>
#include <WebCore/SharedBuffer.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/RefCounted.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace RemoteCDMInstanceSessionProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteCDMInstanceSessionProxy;
}

class SetLogIdentifier {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_SetLogIdentifier; }
    static constexpr bool isSync = false;

    explicit SetLogIdentifier(uint64_t logIdentifier)
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

class RequestLicense {
public:
    using Arguments = std::tuple<WebCore::CDMInstanceSession::LicenseType, AtomString, RefPtr<WebCore::SharedBuffer>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_RequestLicense; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_RequestLicenseReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<RefPtr<WebCore::SharedBuffer>, String, bool, bool>;
    RequestLicense(const WebCore::CDMInstanceSession::LicenseType& type, const AtomString& initDataType, const RefPtr<WebCore::SharedBuffer>& initData)
        : m_arguments(type, initDataType, initData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::CDMInstanceSession::LicenseType&, const AtomString&, const RefPtr<WebCore::SharedBuffer>&> m_arguments;
};

class UpdateLicense {
public:
    using Arguments = std::tuple<String, WebCore::CDMInstanceSession::LicenseType, RefPtr<WebCore::SharedBuffer>>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_UpdateLicense; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_UpdateLicenseReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool, std::optional<WebCore::CDMInstanceSession::KeyStatusVector>, std::optional<double>, std::optional<WebCore::CDMInstanceSession::Message>, bool>;
    UpdateLicense(const String& sessionId, const WebCore::CDMInstanceSession::LicenseType& type, const RefPtr<WebCore::SharedBuffer>& response)
        : m_arguments(sessionId, type, response)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::CDMInstanceSession::LicenseType&, const RefPtr<WebCore::SharedBuffer>&> m_arguments;
};

class LoadSession {
public:
    using Arguments = std::tuple<WebCore::CDMInstanceSession::LicenseType, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_LoadSession; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_LoadSessionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::CDMInstanceSession::KeyStatusVector>, std::optional<double>, std::optional<WebCore::CDMInstanceSession::Message>, bool, WebCore::CDMInstanceSession::SessionLoadFailure>;
    LoadSession(const WebCore::CDMInstanceSession::LicenseType& type, const String& sessionId, const String& origin)
        : m_arguments(type, sessionId, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::CDMInstanceSession::LicenseType&, const String&, const String&> m_arguments;
};

class CloseSession {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_CloseSession; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_CloseSessionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit CloseSession(const String& sessionId)
        : m_arguments(sessionId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RemoveSessionData {
public:
    using Arguments = std::tuple<String, WebCore::CDMInstanceSession::LicenseType>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_RemoveSessionData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_RemoveSessionDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::CDMInstanceSession::KeyStatusVector, RefPtr<WebCore::SharedBuffer>, bool>;
    RemoveSessionData(const String& sessionId, const WebCore::CDMInstanceSession::LicenseType& type)
        : m_arguments(sessionId, type)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::CDMInstanceSession::LicenseType&> m_arguments;
};

class StoreRecordOfKeyUsage {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteCDMInstanceSessionProxy_StoreRecordOfKeyUsage; }
    static constexpr bool isSync = false;

    explicit StoreRecordOfKeyUsage(const String& sessionId)
        : m_arguments(sessionId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

} // namespace RemoteCDMInstanceSessionProxy
} // namespace Messages

#endif // ENABLE(GPU_PROCESS) && ENABLE(ENCRYPTED_MEDIA)
