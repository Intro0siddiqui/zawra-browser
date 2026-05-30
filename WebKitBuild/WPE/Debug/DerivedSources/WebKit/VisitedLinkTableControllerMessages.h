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
#include "SharedMemory.h"
#include <WebCore/SharedStringHash.h>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>


namespace Messages {
namespace VisitedLinkTableController {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::VisitedLinkTableController;
}

class SetVisitedLinkTable {
public:
    using Arguments = std::tuple<WebKit::SharedMemory::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::VisitedLinkTableController_SetVisitedLinkTable; }
    static constexpr bool isSync = false;

    explicit SetVisitedLinkTable(WebKit::SharedMemory::Handle&& handle)
        : m_arguments(WTFMove(handle))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::SharedMemory::Handle&&> m_arguments;
};

class VisitedLinkStateChanged {
public:
    using Arguments = std::tuple<Vector<WebCore::SharedStringHash>>;

    static IPC::MessageName name() { return IPC::MessageName::VisitedLinkTableController_VisitedLinkStateChanged; }
    static constexpr bool isSync = false;

    explicit VisitedLinkStateChanged(const Vector<WebCore::SharedStringHash>& linkHashes)
        : m_arguments(linkHashes)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::SharedStringHash>&> m_arguments;
};

class AllVisitedLinkStateChanged {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::VisitedLinkTableController_AllVisitedLinkStateChanged; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RemoveAllVisitedLinks {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::VisitedLinkTableController_RemoveAllVisitedLinks; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

} // namespace VisitedLinkTableController
} // namespace Messages
