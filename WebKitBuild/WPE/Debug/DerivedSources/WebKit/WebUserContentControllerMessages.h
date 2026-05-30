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
#include "ContentWorldShared.h"
#include "MessageNames.h"
#include "WebCompiledContentRuleListData.h"
#include "WebUserContentControllerDataTypes.h"
#include <utility>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/URLHash.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebKit {
enum class InjectUserScriptImmediately : bool;
}

namespace Messages {
namespace WebUserContentController {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebUserContentController;
}

class AddContentWorlds {
public:
    using Arguments = std::tuple<Vector<std::pair<WebKit::ContentWorldIdentifier, String>>>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_AddContentWorlds; }
    static constexpr bool isSync = false;

    explicit AddContentWorlds(const Vector<std::pair<WebKit::ContentWorldIdentifier, String>>& worlds)
        : m_arguments(worlds)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<std::pair<WebKit::ContentWorldIdentifier, String>>&> m_arguments;
};

class RemoveContentWorlds {
public:
    using Arguments = std::tuple<Vector<WebKit::ContentWorldIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_RemoveContentWorlds; }
    static constexpr bool isSync = false;

    explicit RemoveContentWorlds(const Vector<WebKit::ContentWorldIdentifier>& worldIdentifiers)
        : m_arguments(worldIdentifiers)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::ContentWorldIdentifier>&> m_arguments;
};

class AddUserScripts {
public:
    using Arguments = std::tuple<Vector<WebKit::WebUserScriptData>, WebKit::InjectUserScriptImmediately>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_AddUserScripts; }
    static constexpr bool isSync = false;

    AddUserScripts(const Vector<WebKit::WebUserScriptData>& userScripts, WebKit::InjectUserScriptImmediately immediately)
        : m_arguments(userScripts, immediately)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::WebUserScriptData>&, WebKit::InjectUserScriptImmediately> m_arguments;
};

class RemoveUserScript {
public:
    using Arguments = std::tuple<WebKit::ContentWorldIdentifier, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_RemoveUserScript; }
    static constexpr bool isSync = false;

    RemoveUserScript(const WebKit::ContentWorldIdentifier& worldIdentifier, uint64_t identifier)
        : m_arguments(worldIdentifier, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ContentWorldIdentifier&, uint64_t> m_arguments;
};

class RemoveAllUserScripts {
public:
    using Arguments = std::tuple<Vector<WebKit::ContentWorldIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_RemoveAllUserScripts; }
    static constexpr bool isSync = false;

    explicit RemoveAllUserScripts(const Vector<WebKit::ContentWorldIdentifier>& worldIdentifiers)
        : m_arguments(worldIdentifiers)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::ContentWorldIdentifier>&> m_arguments;
};

class AddUserStyleSheets {
public:
    using Arguments = std::tuple<Vector<WebKit::WebUserStyleSheetData>>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_AddUserStyleSheets; }
    static constexpr bool isSync = false;

    explicit AddUserStyleSheets(const Vector<WebKit::WebUserStyleSheetData>& userStyleSheets)
        : m_arguments(userStyleSheets)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::WebUserStyleSheetData>&> m_arguments;
};

class RemoveUserStyleSheet {
public:
    using Arguments = std::tuple<WebKit::ContentWorldIdentifier, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_RemoveUserStyleSheet; }
    static constexpr bool isSync = false;

    RemoveUserStyleSheet(const WebKit::ContentWorldIdentifier& worldIdentifier, uint64_t identifier)
        : m_arguments(worldIdentifier, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ContentWorldIdentifier&, uint64_t> m_arguments;
};

class RemoveAllUserStyleSheets {
public:
    using Arguments = std::tuple<Vector<WebKit::ContentWorldIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_RemoveAllUserStyleSheets; }
    static constexpr bool isSync = false;

    explicit RemoveAllUserStyleSheets(const Vector<WebKit::ContentWorldIdentifier>& worldIdentifiers)
        : m_arguments(worldIdentifiers)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::ContentWorldIdentifier>&> m_arguments;
};

class AddUserScriptMessageHandlers {
public:
    using Arguments = std::tuple<Vector<WebKit::WebScriptMessageHandlerData>>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_AddUserScriptMessageHandlers; }
    static constexpr bool isSync = false;

    explicit AddUserScriptMessageHandlers(const Vector<WebKit::WebScriptMessageHandlerData>& scriptMessageHandlers)
        : m_arguments(scriptMessageHandlers)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::WebScriptMessageHandlerData>&> m_arguments;
};

class RemoveUserScriptMessageHandler {
public:
    using Arguments = std::tuple<WebKit::ContentWorldIdentifier, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_RemoveUserScriptMessageHandler; }
    static constexpr bool isSync = false;

    RemoveUserScriptMessageHandler(const WebKit::ContentWorldIdentifier& worldIdentifier, uint64_t identifier)
        : m_arguments(worldIdentifier, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ContentWorldIdentifier&, uint64_t> m_arguments;
};

class RemoveAllUserScriptMessageHandlersForWorlds {
public:
    using Arguments = std::tuple<Vector<WebKit::ContentWorldIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_RemoveAllUserScriptMessageHandlersForWorlds; }
    static constexpr bool isSync = false;

    explicit RemoveAllUserScriptMessageHandlersForWorlds(const Vector<WebKit::ContentWorldIdentifier>& worldIdentifiers)
        : m_arguments(worldIdentifiers)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::ContentWorldIdentifier>&> m_arguments;
};

class RemoveAllUserScriptMessageHandlers {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_RemoveAllUserScriptMessageHandlers; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if ENABLE(CONTENT_EXTENSIONS)
class AddContentRuleLists {
public:
    using Arguments = std::tuple<Vector<std::pair<WebKit::WebCompiledContentRuleListData, URL>>>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_AddContentRuleLists; }
    static constexpr bool isSync = false;

    explicit AddContentRuleLists(const Vector<std::pair<WebKit::WebCompiledContentRuleListData, URL>>& contentFilters)
        : m_arguments(contentFilters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<std::pair<WebKit::WebCompiledContentRuleListData, URL>>&> m_arguments;
};
#endif

#if ENABLE(CONTENT_EXTENSIONS)
class RemoveContentRuleList {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_RemoveContentRuleList; }
    static constexpr bool isSync = false;

    explicit RemoveContentRuleList(const String& name)
        : m_arguments(name)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};
#endif

#if ENABLE(CONTENT_EXTENSIONS)
class RemoveAllContentRuleLists {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebUserContentController_RemoveAllContentRuleLists; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

} // namespace WebUserContentController
} // namespace Messages
