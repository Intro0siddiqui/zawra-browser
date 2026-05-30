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
#include <wtf/UUID.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WTF {
class UUID;
}

namespace Messages {
namespace WebNotificationManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebNotificationManager;
}

class DidShowNotification {
public:
    using Arguments = std::tuple<WTF::UUID>;

    static IPC::MessageName name() { return IPC::MessageName::WebNotificationManager_DidShowNotification; }
    static constexpr bool isSync = false;

    explicit DidShowNotification(const WTF::UUID& notificationID)
        : m_arguments(notificationID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WTF::UUID&> m_arguments;
};

class DidClickNotification {
public:
    using Arguments = std::tuple<WTF::UUID>;

    static IPC::MessageName name() { return IPC::MessageName::WebNotificationManager_DidClickNotification; }
    static constexpr bool isSync = false;

    explicit DidClickNotification(const WTF::UUID& notificationID)
        : m_arguments(notificationID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WTF::UUID&> m_arguments;
};

class DidCloseNotifications {
public:
    using Arguments = std::tuple<Vector<WTF::UUID>>;

    static IPC::MessageName name() { return IPC::MessageName::WebNotificationManager_DidCloseNotifications; }
    static constexpr bool isSync = false;

    explicit DidCloseNotifications(const Vector<WTF::UUID>& notificationIDs)
        : m_arguments(notificationIDs)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WTF::UUID>&> m_arguments;
};

class DidUpdateNotificationDecision {
public:
    using Arguments = std::tuple<String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebNotificationManager_DidUpdateNotificationDecision; }
    static constexpr bool isSync = false;

    DidUpdateNotificationDecision(const String& originString, bool allowed)
        : m_arguments(originString, allowed)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, bool> m_arguments;
};

class DidRemoveNotificationDecisions {
public:
    using Arguments = std::tuple<Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebNotificationManager_DidRemoveNotificationDecisions; }
    static constexpr bool isSync = false;

    explicit DidRemoveNotificationDecisions(const Vector<String>& originStrings)
        : m_arguments(originStrings)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&> m_arguments;
};

} // namespace WebNotificationManager
} // namespace Messages
