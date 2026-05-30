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

#if ENABLE(WEB_RTC)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include <WebCore/MDNSRegisterError.h>
#include <WebCore/ProcessQualified.h>
#include <WebCore/ScriptExecutionContextIdentifier.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ObjectIdentifier.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace NetworkMDNSRegister {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::NetworkMDNSRegister;
}

class UnregisterMDNSNames {
public:
    using Arguments = std::tuple<WebCore::ScriptExecutionContextIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkMDNSRegister_UnregisterMDNSNames; }
    static constexpr bool isSync = false;

    explicit UnregisterMDNSNames(const WebCore::ScriptExecutionContextIdentifier& documentIdentifier)
        : m_arguments(documentIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScriptExecutionContextIdentifier&> m_arguments;
};

class RegisterMDNSName {
public:
    using Arguments = std::tuple<WebCore::ScriptExecutionContextIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkMDNSRegister_RegisterMDNSName; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NetworkMDNSRegister_RegisterMDNSNameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String, std::optional<WebCore::MDNSRegisterError>>;
    RegisterMDNSName(const WebCore::ScriptExecutionContextIdentifier& documentIdentifier, const String& ipAddress)
        : m_arguments(documentIdentifier, ipAddress)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScriptExecutionContextIdentifier&, const String&> m_arguments;
};

} // namespace NetworkMDNSRegister
} // namespace Messages

#endif // ENABLE(WEB_RTC)
