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
#include "IdentifierTypes.h"
#include "MessageNames.h"
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace WebCore {
class Credential;
}

namespace WebKit {
enum class AuthenticationChallengeDisposition : uint8_t;
}

namespace Messages {
namespace AuthenticationManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::AuthenticationManager;
}

class CompleteAuthenticationChallenge {
public:
    using Arguments = std::tuple<WebKit::AuthenticationChallengeIdentifier, WebKit::AuthenticationChallengeDisposition, WebCore::Credential>;

    static IPC::MessageName name() { return IPC::MessageName::AuthenticationManager_CompleteAuthenticationChallenge; }
    static constexpr bool isSync = false;

    CompleteAuthenticationChallenge(const WebKit::AuthenticationChallengeIdentifier& challengeID, WebKit::AuthenticationChallengeDisposition disposition, const WebCore::Credential& credential)
        : m_arguments(challengeID, disposition, credential)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::AuthenticationChallengeIdentifier&, WebKit::AuthenticationChallengeDisposition, const WebCore::Credential&> m_arguments;
};

} // namespace AuthenticationManager
} // namespace Messages
