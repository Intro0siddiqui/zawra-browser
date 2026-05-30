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
#include <WebCore/ProcessQualified.h>
#include <WebCore/ScriptExecutionContextIdentifier.h>
#include <WebCore/WebLockIdentifier.h>
#include <wtf/Forward.h>
#include <wtf/ObjectIdentifier.h>
#include <wtf/ThreadSafeRefCounted.h>


namespace Messages {
namespace RemoteWebLockRegistry {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::RemoteWebLockRegistry;
}

class DidCompleteLockRequest {
public:
    using Arguments = std::tuple<WebCore::WebLockIdentifier, WebCore::ScriptExecutionContextIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebLockRegistry_DidCompleteLockRequest; }
    static constexpr bool isSync = false;

    DidCompleteLockRequest(const WebCore::WebLockIdentifier& lockIdentifier, const WebCore::ScriptExecutionContextIdentifier& clientID, bool success)
        : m_arguments(lockIdentifier, clientID, success)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::WebLockIdentifier&, const WebCore::ScriptExecutionContextIdentifier&, bool> m_arguments;
};

class DidStealLock {
public:
    using Arguments = std::tuple<WebCore::WebLockIdentifier, WebCore::ScriptExecutionContextIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::RemoteWebLockRegistry_DidStealLock; }
    static constexpr bool isSync = false;

    DidStealLock(const WebCore::WebLockIdentifier& lockIdentifier, const WebCore::ScriptExecutionContextIdentifier& clientID)
        : m_arguments(lockIdentifier, clientID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::WebLockIdentifier&, const WebCore::ScriptExecutionContextIdentifier&> m_arguments;
};

} // namespace RemoteWebLockRegistry
} // namespace Messages
