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
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class GeolocationPositionData;
class RegistrableDomain;
}

namespace Messages {
namespace WebGeolocationManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebGeolocationManager;
}

class DidChangePosition {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain, WebCore::GeolocationPositionData>;

    static IPC::MessageName name() { return IPC::MessageName::WebGeolocationManager_DidChangePosition; }
    static constexpr bool isSync = false;

    DidChangePosition(const WebCore::RegistrableDomain& registrableDomain, const WebCore::GeolocationPositionData& position)
        : m_arguments(registrableDomain, position)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&, const WebCore::GeolocationPositionData&> m_arguments;
};

class DidFailToDeterminePosition {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebGeolocationManager_DidFailToDeterminePosition; }
    static constexpr bool isSync = false;

    DidFailToDeterminePosition(const WebCore::RegistrableDomain& registrableDomain, const String& errorMessage)
        : m_arguments(registrableDomain, errorMessage)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&, const String&> m_arguments;
};

#if PLATFORM(IOS_FAMILY)
class ResetPermissions {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::WebGeolocationManager_ResetPermissions; }
    static constexpr bool isSync = false;

    explicit ResetPermissions(const WebCore::RegistrableDomain& registrableDomain)
        : m_arguments(registrableDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&> m_arguments;
};
#endif

} // namespace WebGeolocationManager
} // namespace Messages
