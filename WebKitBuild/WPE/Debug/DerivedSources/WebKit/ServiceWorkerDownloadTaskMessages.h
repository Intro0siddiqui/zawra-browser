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

#if ENABLE(SERVICE_WORKER)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>

namespace IPC {
class FormDataReference;
class SharedBufferReference;
}

namespace WebCore {
class ResourceError;
}

namespace Messages {
namespace ServiceWorkerDownloadTask {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::ServiceWorkerDownloadTask;
}

class DidFail {
public:
    using Arguments = std::tuple<WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::ServiceWorkerDownloadTask_DidFail; }
    static constexpr bool isSync = false;

    explicit DidFail(const WebCore::ResourceError& error)
        : m_arguments(error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceError&> m_arguments;
};

class DidReceiveData {
public:
    using Arguments = std::tuple<IPC::SharedBufferReference, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::ServiceWorkerDownloadTask_DidReceiveData; }
    static constexpr bool isSync = false;

    DidReceiveData(const IPC::SharedBufferReference& data, uint64_t encodedDataLength)
        : m_arguments(data, encodedDataLength)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::SharedBufferReference&, uint64_t> m_arguments;
};

class DidReceiveFormData {
public:
    using Arguments = std::tuple<IPC::FormDataReference>;

    static IPC::MessageName name() { return IPC::MessageName::ServiceWorkerDownloadTask_DidReceiveFormData; }
    static constexpr bool isSync = false;

    explicit DidReceiveFormData(const IPC::FormDataReference& data)
        : m_arguments(data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::FormDataReference&> m_arguments;
};

class DidFinish {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::ServiceWorkerDownloadTask_DidFinish; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

} // namespace ServiceWorkerDownloadTask
} // namespace Messages

#endif // ENABLE(SERVICE_WORKER)
