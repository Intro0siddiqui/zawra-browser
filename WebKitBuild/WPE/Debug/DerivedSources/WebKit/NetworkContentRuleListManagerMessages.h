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

#if ENABLE(CONTENT_EXTENSIONS)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include "UserContentControllerIdentifier.h"
#include "WebCompiledContentRuleListData.h"
#include <utility>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/URLHash.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>


namespace Messages {
namespace NetworkContentRuleListManager {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::NetworkContentRuleListManager;
}

class Remove {
public:
    using Arguments = std::tuple<WebKit::UserContentControllerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkContentRuleListManager_Remove; }
    static constexpr bool isSync = false;

    explicit Remove(const WebKit::UserContentControllerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::UserContentControllerIdentifier&> m_arguments;
};

class AddContentRuleLists {
public:
    using Arguments = std::tuple<WebKit::UserContentControllerIdentifier, Vector<std::pair<WebKit::WebCompiledContentRuleListData, URL>>>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkContentRuleListManager_AddContentRuleLists; }
    static constexpr bool isSync = false;

    AddContentRuleLists(const WebKit::UserContentControllerIdentifier& identifier, const Vector<std::pair<WebKit::WebCompiledContentRuleListData, URL>>& contentFilters)
        : m_arguments(identifier, contentFilters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::UserContentControllerIdentifier&, const Vector<std::pair<WebKit::WebCompiledContentRuleListData, URL>>&> m_arguments;
};

class RemoveContentRuleList {
public:
    using Arguments = std::tuple<WebKit::UserContentControllerIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkContentRuleListManager_RemoveContentRuleList; }
    static constexpr bool isSync = false;

    RemoveContentRuleList(const WebKit::UserContentControllerIdentifier& identifier, const String& name)
        : m_arguments(identifier, name)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::UserContentControllerIdentifier&, const String&> m_arguments;
};

class RemoveAllContentRuleLists {
public:
    using Arguments = std::tuple<WebKit::UserContentControllerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::NetworkContentRuleListManager_RemoveAllContentRuleLists; }
    static constexpr bool isSync = false;

    explicit RemoveAllContentRuleLists(const WebKit::UserContentControllerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::UserContentControllerIdentifier&> m_arguments;
};

} // namespace NetworkContentRuleListManager
} // namespace Messages

#endif // ENABLE(CONTENT_EXTENSIONS)
