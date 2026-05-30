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
#include <WebCore/NotificationResources.h>
#include <wtf/Forward.h>
#include <wtf/RefCounted.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/UUID.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WTF {
class UUID;
}

namespace WebCore {
struct NotificationData;
}

namespace Messages {
namespace NotificationManagerMessageHandler {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::NotificationManagerMessageHandler;
}

class RequestSystemNotificationPermission {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::NotificationManagerMessageHandler_RequestSystemNotificationPermission; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NotificationManagerMessageHandler_RequestSystemNotificationPermissionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit RequestSystemNotificationPermission(const String& originIdentifier)
        : m_arguments(originIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class ShowNotification {
public:
    using Arguments = std::tuple<WebCore::NotificationData, RefPtr<WebCore::NotificationResources>>;

    static IPC::MessageName name() { return IPC::MessageName::NotificationManagerMessageHandler_ShowNotification; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::NotificationManagerMessageHandler_ShowNotificationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    ShowNotification(const WebCore::NotificationData& notificationData, const RefPtr<WebCore::NotificationResources>& notificationResources)
        : m_arguments(notificationData, notificationResources)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::NotificationData&, const RefPtr<WebCore::NotificationResources>&> m_arguments;
};

class CancelNotification {
public:
    using Arguments = std::tuple<WTF::UUID>;

    static IPC::MessageName name() { return IPC::MessageName::NotificationManagerMessageHandler_CancelNotification; }
    static constexpr bool isSync = false;

    explicit CancelNotification(const WTF::UUID& notificationID)
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

class ClearNotifications {
public:
    using Arguments = std::tuple<Vector<WTF::UUID>>;

    static IPC::MessageName name() { return IPC::MessageName::NotificationManagerMessageHandler_ClearNotifications; }
    static constexpr bool isSync = false;

    explicit ClearNotifications(const Vector<WTF::UUID>& notificationIDs)
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

class DidDestroyNotification {
public:
    using Arguments = std::tuple<WTF::UUID>;

    static IPC::MessageName name() { return IPC::MessageName::NotificationManagerMessageHandler_DidDestroyNotification; }
    static constexpr bool isSync = false;

    explicit DidDestroyNotification(const WTF::UUID& notificationID)
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

class PageWasNotifiedOfNotificationPermission {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::NotificationManagerMessageHandler_PageWasNotifiedOfNotificationPermission; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

} // namespace NotificationManagerMessageHandler
} // namespace Messages
