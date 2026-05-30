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
#include "SandboxExtension.h"
#include "SharedMemory.h"
#include <WebCore/PageIdentifier.h>
#include <WebCore/Pasteboard.h>
#include <WebCore/PasteboardItemInfo.h>
#include <WebCore/SharedBuffer.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/RefCounted.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class Color;
class SelectionData;
struct PasteboardBuffer;
struct PasteboardImage;
struct PasteboardURL;
struct PasteboardWebContent;
}

namespace Messages {
namespace WebPasteboardProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebPasteboardProxy;
}

#if PLATFORM(IOS_FAMILY)
class WriteURLToPasteboard {
public:
    using Arguments = std::tuple<WebCore::PasteboardURL, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_WriteURLToPasteboard; }
    static constexpr bool isSync = false;

    WriteURLToPasteboard(const WebCore::PasteboardURL& url, const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(url, pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PasteboardURL&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class WriteWebContentToPasteboard {
public:
    using Arguments = std::tuple<WebCore::PasteboardWebContent, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_WriteWebContentToPasteboard; }
    static constexpr bool isSync = false;

    WriteWebContentToPasteboard(const WebCore::PasteboardWebContent& content, const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(content, pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PasteboardWebContent&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class WriteImageToPasteboard {
public:
    using Arguments = std::tuple<WebCore::PasteboardImage, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_WriteImageToPasteboard; }
    static constexpr bool isSync = false;

    WriteImageToPasteboard(const WebCore::PasteboardImage& pasteboardImage, const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardImage, pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PasteboardImage&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class WriteStringToPasteboard {
public:
    using Arguments = std::tuple<String, String, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_WriteStringToPasteboard; }
    static constexpr bool isSync = false;

    WriteStringToPasteboard(const String& pasteboardType, const String& text, const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardType, text, pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class UpdateSupportedTypeIdentifiers {
public:
    using Arguments = std::tuple<Vector<String>, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_UpdateSupportedTypeIdentifiers; }
    static constexpr bool isSync = false;

    UpdateSupportedTypeIdentifiers(const Vector<String>& identifiers, const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(identifiers, pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

class WriteCustomData {
public:
    using Arguments = std::tuple<Vector<WebCore::PasteboardCustomData>, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_WriteCustomData; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    WriteCustomData(const Vector<WebCore::PasteboardCustomData>& data, const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(data, pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::PasteboardCustomData>&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};

class TypesSafeForDOMToReadAndWrite {
public:
    using Arguments = std::tuple<String, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_TypesSafeForDOMToReadAndWrite; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    TypesSafeForDOMToReadAndWrite(const String& pasteboardName, const String& origin, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, origin, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};

class AllPasteboardItemInfo {
public:
    using Arguments = std::tuple<String, int64_t, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_AllPasteboardItemInfo; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<Vector<WebCore::PasteboardItemInfo>>>;
    AllPasteboardItemInfo(const String& pasteboardName, int64_t changeCount, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, changeCount, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, int64_t, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};

class InformationForItemAtIndex {
public:
    using Arguments = std::tuple<size_t, String, int64_t, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_InformationForItemAtIndex; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::PasteboardItemInfo>>;
    InformationForItemAtIndex(size_t index, const String& pasteboardName, int64_t changeCount, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(index, pasteboardName, changeCount, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<size_t, const String&, int64_t, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};

class GetPasteboardItemsCount {
public:
    using Arguments = std::tuple<String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetPasteboardItemsCount; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    GetPasteboardItemsCount(const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};

class ReadStringFromPasteboard {
public:
    using Arguments = std::tuple<size_t, String, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_ReadStringFromPasteboard; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    ReadStringFromPasteboard(size_t index, const String& pasteboardType, const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(index, pasteboardType, pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<size_t, const String&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};

class ReadURLFromPasteboard {
public:
    using Arguments = std::tuple<size_t, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_ReadURLFromPasteboard; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String, String>;
    ReadURLFromPasteboard(size_t index, const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(index, pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<size_t, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};

class ReadBufferFromPasteboard {
public:
    using Arguments = std::tuple<std::optional<size_t>, String, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_ReadBufferFromPasteboard; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<RefPtr<WebCore::SharedBuffer>>;
    ReadBufferFromPasteboard(const std::optional<size_t>& index, const String& pasteboardType, const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(index, pasteboardType, pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<size_t>&, const String&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};

class ContainsStringSafeForDOMToReadForType {
public:
    using Arguments = std::tuple<String, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_ContainsStringSafeForDOMToReadForType; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    ContainsStringSafeForDOMToReadForType(const String& type, const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(type, pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};

#if PLATFORM(COCOA)
class GetNumberOfFiles {
public:
    using Arguments = std::tuple<String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetNumberOfFiles; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    GetNumberOfFiles(const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetPasteboardTypes {
public:
    using Arguments = std::tuple<String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetPasteboardTypes; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    GetPasteboardTypes(const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetPasteboardPathnamesForType {
public:
    using Arguments = std::tuple<String, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetPasteboardPathnamesForType; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>, Vector<WebKit::SandboxExtension::Handle>>;
    GetPasteboardPathnamesForType(const String& pasteboardName, const String& pasteboardType, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pasteboardType, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetPasteboardStringForType {
public:
    using Arguments = std::tuple<String, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetPasteboardStringForType; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    GetPasteboardStringForType(const String& pasteboardName, const String& pasteboardType, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pasteboardType, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetPasteboardStringsForType {
public:
    using Arguments = std::tuple<String, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetPasteboardStringsForType; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    GetPasteboardStringsForType(const String& pasteboardName, const String& pasteboardType, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pasteboardType, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetPasteboardBufferForType {
public:
    using Arguments = std::tuple<String, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetPasteboardBufferForType; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::PasteboardBuffer>;
    GetPasteboardBufferForType(const String& pasteboardName, const String& pasteboardType, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pasteboardType, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetPasteboardChangeCount {
public:
    using Arguments = std::tuple<String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetPasteboardChangeCount; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    GetPasteboardChangeCount(const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetPasteboardColor {
public:
    using Arguments = std::tuple<String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetPasteboardColor; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::Color>;
    GetPasteboardColor(const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetPasteboardURL {
public:
    using Arguments = std::tuple<String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetPasteboardURL; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    GetPasteboardURL(const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class AddPasteboardTypes {
public:
    using Arguments = std::tuple<String, Vector<String>, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_AddPasteboardTypes; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    AddPasteboardTypes(const String& pasteboardName, const Vector<String>& pasteboardTypes, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pasteboardTypes, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const Vector<String>&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetPasteboardTypes {
public:
    using Arguments = std::tuple<String, Vector<String>, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_SetPasteboardTypes; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    SetPasteboardTypes(const String& pasteboardName, const Vector<String>& pasteboardTypes, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pasteboardTypes, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const Vector<String>&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetPasteboardURL {
public:
    using Arguments = std::tuple<WebCore::PasteboardURL, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_SetPasteboardURL; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    SetPasteboardURL(const WebCore::PasteboardURL& pasteboardURL, const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardURL, pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PasteboardURL&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetPasteboardColor {
public:
    using Arguments = std::tuple<String, WebCore::Color, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_SetPasteboardColor; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    SetPasteboardColor(const String& pasteboardName, const WebCore::Color& color, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, color, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::Color&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetPasteboardStringForType {
public:
    using Arguments = std::tuple<String, String, String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_SetPasteboardStringForType; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    SetPasteboardStringForType(const String& pasteboardName, const String& pasteboardType, const String& string, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pasteboardType, string, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetPasteboardBufferForType {
public:
    using Arguments = std::tuple<String, String, RefPtr<WebCore::SharedBuffer>, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_SetPasteboardBufferForType; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    SetPasteboardBufferForType(const String& pasteboardName, const String& pasteboardType, const RefPtr<WebCore::SharedBuffer>& buffer, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pasteboardType, buffer, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const RefPtr<WebCore::SharedBuffer>&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class ContainsURLStringSuitableForLoading {
public:
    using Arguments = std::tuple<String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_ContainsURLStringSuitableForLoading; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    ContainsURLStringSuitableForLoading(const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class URLStringSuitableForLoading {
public:
    using Arguments = std::tuple<String, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_URLStringSuitableForLoading; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String, String>;
    URLStringSuitableForLoading(const String& pasteboardName, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if (PLATFORM(COCOA) && ENABLE(IPC_TESTING_API))
class TestIPCSharedMemory {
public:
    using Arguments = std::tuple<String, String, WebKit::SharedMemory::Handle, std::optional<WebCore::PageIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_TestIPCSharedMemory; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t, String>;
    TestIPCSharedMemory(const String& pasteboardName, const String& pasteboardType, WebKit::SharedMemory::Handle&& handle, const std::optional<WebCore::PageIdentifier>& pageID)
        : m_arguments(pasteboardName, pasteboardType, WTFMove(handle), pageID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, WebKit::SharedMemory::Handle&&, const std::optional<WebCore::PageIdentifier>&> m_arguments;
};
#endif

#if PLATFORM(GTK)
class GetTypes {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetTypes; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    explicit GetTypes(const String& pasteboardName)
        : m_arguments(pasteboardName)
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

#if PLATFORM(GTK)
class ReadText {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_ReadText; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit ReadText(const String& pasteboardName)
        : m_arguments(pasteboardName)
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

#if PLATFORM(GTK)
class ReadFilePaths {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_ReadFilePaths; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    explicit ReadFilePaths(const String& pasteboardName)
        : m_arguments(pasteboardName)
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

#if PLATFORM(GTK)
class ReadBuffer {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_ReadBuffer; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<RefPtr<WebCore::SharedBuffer>>;
    ReadBuffer(const String& pasteboardName, const String& pasteboardType)
        : m_arguments(pasteboardName, pasteboardType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&> m_arguments;
};
#endif

#if PLATFORM(GTK)
class WriteToClipboard {
public:
    using Arguments = std::tuple<String, WebCore::SelectionData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_WriteToClipboard; }
    static constexpr bool isSync = false;

    WriteToClipboard(const String& pasteboardName, const WebCore::SelectionData& pasteboardContent)
        : m_arguments(pasteboardName, pasteboardContent)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::SelectionData&> m_arguments;
};
#endif

#if PLATFORM(GTK)
class ClearClipboard {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_ClearClipboard; }
    static constexpr bool isSync = false;

    explicit ClearClipboard(const String& pasteboardName)
        : m_arguments(pasteboardName)
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

#if PLATFORM(GTK)
class GetPasteboardChangeCount {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetPasteboardChangeCount; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int64_t>;
    explicit GetPasteboardChangeCount(const String& pasteboardName)
        : m_arguments(pasteboardName)
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

#if USE(LIBWPE)
class GetPasteboardTypes {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_GetPasteboardTypes; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(LIBWPE)
class WriteWebContentToPasteboard {
public:
    using Arguments = std::tuple<WebCore::PasteboardWebContent>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_WriteWebContentToPasteboard; }
    static constexpr bool isSync = false;

    explicit WriteWebContentToPasteboard(const WebCore::PasteboardWebContent& content)
        : m_arguments(content)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PasteboardWebContent&> m_arguments;
};
#endif

#if USE(LIBWPE)
class WriteStringToPasteboard {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPasteboardProxy_WriteStringToPasteboard; }
    static constexpr bool isSync = false;

    WriteStringToPasteboard(const String& pasteboardType, const String& text)
        : m_arguments(pasteboardType, text)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&> m_arguments;
};
#endif

} // namespace WebPasteboardProxy
} // namespace Messages
