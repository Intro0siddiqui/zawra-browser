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

#if ENABLE(WEBXR)

#include "ArgumentCoders.h"
#include "Connection.h"
#include "MessageNames.h"
#include "XRDeviceInfo.h"
#include <WebCore/PlatformXR.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>

namespace WebCore {
class SecurityOriginData;
}

namespace Messages {
namespace PlatformXRSystem {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::PlatformXRSystem;
}

class EnumerateImmersiveXRDevices {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::PlatformXRSystem_EnumerateImmersiveXRDevices; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::PlatformXRSystem_EnumerateImmersiveXRDevicesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebKit::XRDeviceInfo>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RequestPermissionOnSessionFeatures {
public:
    using Arguments = std::tuple<WebCore::SecurityOriginData, PlatformXR::SessionMode, Vector<PlatformXR::SessionFeature>, Vector<PlatformXR::SessionFeature>, Vector<PlatformXR::SessionFeature>, Vector<PlatformXR::SessionFeature>, Vector<PlatformXR::SessionFeature>>;

    static IPC::MessageName name() { return IPC::MessageName::PlatformXRSystem_RequestPermissionOnSessionFeatures; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::PlatformXRSystem_RequestPermissionOnSessionFeaturesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<Vector<PlatformXR::SessionFeature>>>;
    RequestPermissionOnSessionFeatures(const WebCore::SecurityOriginData& origin, const PlatformXR::SessionMode& mode, const Vector<PlatformXR::SessionFeature>& granted, const Vector<PlatformXR::SessionFeature>& consentRequired, const Vector<PlatformXR::SessionFeature>& consentOptional, const Vector<PlatformXR::SessionFeature>& requiredFeaturesRequested, const Vector<PlatformXR::SessionFeature>& optionalFeaturesRequested)
        : m_arguments(origin, mode, granted, consentRequired, consentOptional, requiredFeaturesRequested, optionalFeaturesRequested)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SecurityOriginData&, const PlatformXR::SessionMode&, const Vector<PlatformXR::SessionFeature>&, const Vector<PlatformXR::SessionFeature>&, const Vector<PlatformXR::SessionFeature>&, const Vector<PlatformXR::SessionFeature>&, const Vector<PlatformXR::SessionFeature>&> m_arguments;
};

class InitializeTrackingAndRendering {
public:
    using Arguments = std::tuple<WebCore::SecurityOriginData, PlatformXR::SessionMode, Vector<PlatformXR::SessionFeature>>;

    static IPC::MessageName name() { return IPC::MessageName::PlatformXRSystem_InitializeTrackingAndRendering; }
    static constexpr bool isSync = false;

    InitializeTrackingAndRendering(const WebCore::SecurityOriginData& origin, const PlatformXR::SessionMode& mode, const Vector<PlatformXR::SessionFeature>& requestedFeatures)
        : m_arguments(origin, mode, requestedFeatures)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SecurityOriginData&, const PlatformXR::SessionMode&, const Vector<PlatformXR::SessionFeature>&> m_arguments;
};

class ShutDownTrackingAndRendering {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::PlatformXRSystem_ShutDownTrackingAndRendering; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RequestFrame {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::PlatformXRSystem_RequestFrame; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::PlatformXRSystem_RequestFrameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<PlatformXR::Device::FrameData>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SubmitFrame {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::PlatformXRSystem_SubmitFrame; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

} // namespace PlatformXRSystem
} // namespace Messages

#endif // ENABLE(WEBXR)
