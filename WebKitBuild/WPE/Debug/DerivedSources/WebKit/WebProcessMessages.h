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
#include "DataReference.h"
#include "GamepadData.h"
#include "IdentifierTypes.h"
#include "MessageNames.h"
#include "SandboxExtension.h"
#include "WebPageProxyIdentifier.h"
#include "WebProcessCreationParameters.h"
#include "WebsiteDataType.h"
#include <WebCore/BackForwardItemIdentifier.h>
#include <WebCore/CaptionUserPreferences.h>
#include <WebCore/FrameIdentifier.h>
#include <WebCore/PageIdentifier.h>
#include <WebCore/ProcessQualified.h>
#include <WebCore/RegistrableDomain.h>
#include <WebCore/RenderTreeAsText.h>
#include <WebCore/ScriptExecutionContextIdentifier.h>
#include <WebCore/SecurityOriginData.h>
#include <optional>
#include <wtf/Forward.h>
#include <wtf/HashMap.h>
#include <wtf/HashSet.h>
#include <wtf/ObjectIdentifier.h>
#include <wtf/OptionSet.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace IPC {
class SharedBufferReference;
}

namespace PAL {
enum class UserInterfaceIdiom : uint8_t;
}

namespace WebCore {
class RegistrableDomain;
enum class EventMakesGamepadsVisible : bool;
enum class ThirdPartyCookieBlockingMode : uint8_t;
struct ClientOrigin;
struct DisplayUpdate;
struct MessageWithMessagePorts;
struct MockMediaDevice;
struct PrewarmInformation;
struct ScreenProperties;
}

namespace WebKit {
class GamepadData;
class MediaDeviceSandboxExtensions;
class UserData;
enum class CacheModel : uint8_t;
enum class RemoteWorkerType : uint8_t;
struct AccessibilityPreferences;
struct RemoteWorkerInitializationData;
struct TextCheckerState;
struct UserMessage;
struct WebPageCreationParameters;
struct WebPreferencesStore;
struct WebProcessDataStoreParameters;
struct WebsiteData;
}

namespace Messages {
namespace WebProcess {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebProcess;
}

class InitializeWebProcess {
public:
    using Arguments = std::tuple<WebKit::WebProcessCreationParameters>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_InitializeWebProcess; }
    static constexpr bool isSync = false;

    explicit InitializeWebProcess(WebKit::WebProcessCreationParameters&& processCreationParameters)
        : m_arguments(WTFMove(processCreationParameters))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::WebProcessCreationParameters&&> m_arguments;
};

class SetWebsiteDataStoreParameters {
public:
    using Arguments = std::tuple<WebKit::WebProcessDataStoreParameters>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetWebsiteDataStoreParameters; }
    static constexpr bool isSync = false;

    explicit SetWebsiteDataStoreParameters(const WebKit::WebProcessDataStoreParameters& parameters)
        : m_arguments(parameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebProcessDataStoreParameters&> m_arguments;
};

class CreateWebPage {
public:
    using Arguments = std::tuple<WebCore::PageIdentifier, WebKit::WebPageCreationParameters>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_CreateWebPage; }
    static constexpr bool isSync = false;

    CreateWebPage(const WebCore::PageIdentifier& newPageID, const WebKit::WebPageCreationParameters& pageCreationParameters)
        : m_arguments(newPageID, pageCreationParameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageIdentifier&, const WebKit::WebPageCreationParameters&> m_arguments;
};

class PrewarmWithDomainInformation {
public:
    using Arguments = std::tuple<WebCore::PrewarmInformation>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_PrewarmWithDomainInformation; }
    static constexpr bool isSync = false;

    explicit PrewarmWithDomainInformation(const WebCore::PrewarmInformation& prewarmInformation)
        : m_arguments(prewarmInformation)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PrewarmInformation&> m_arguments;
};

class SetCacheModel {
public:
    using Arguments = std::tuple<WebKit::CacheModel>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetCacheModel; }
    static constexpr bool isSync = false;

    explicit SetCacheModel(WebKit::CacheModel cacheModel)
        : m_arguments(cacheModel)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::CacheModel> m_arguments;
};

class RegisterURLSchemeAsEmptyDocument {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RegisterURLSchemeAsEmptyDocument; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsEmptyDocument(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RegisterURLSchemeAsSecure {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RegisterURLSchemeAsSecure; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsSecure(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RegisterURLSchemeAsBypassingContentSecurityPolicy {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RegisterURLSchemeAsBypassingContentSecurityPolicy; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsBypassingContentSecurityPolicy(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class SetDomainRelaxationForbiddenForURLScheme {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetDomainRelaxationForbiddenForURLScheme; }
    static constexpr bool isSync = false;

    explicit SetDomainRelaxationForbiddenForURLScheme(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RegisterURLSchemeAsLocal {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RegisterURLSchemeAsLocal; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsLocal(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RegisterURLSchemeAsNoAccess {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RegisterURLSchemeAsNoAccess; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsNoAccess(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RegisterURLSchemeAsDisplayIsolated {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RegisterURLSchemeAsDisplayIsolated; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsDisplayIsolated(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RegisterURLSchemeAsCORSEnabled {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RegisterURLSchemeAsCORSEnabled; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsCORSEnabled(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RegisterURLSchemeAsCachePartitioned {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RegisterURLSchemeAsCachePartitioned; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsCachePartitioned(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RegisterURLSchemeAsCanDisplayOnlyIfCanRequest {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RegisterURLSchemeAsCanDisplayOnlyIfCanRequest; }
    static constexpr bool isSync = false;

    explicit RegisterURLSchemeAsCanDisplayOnlyIfCanRequest(const String& scheme)
        : m_arguments(scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class SetDefaultRequestTimeoutInterval {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetDefaultRequestTimeoutInterval; }
    static constexpr bool isSync = false;

    explicit SetDefaultRequestTimeoutInterval(double timeoutInterval)
        : m_arguments(timeoutInterval)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class SetAlwaysUsesComplexTextCodePath {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetAlwaysUsesComplexTextCodePath; }
    static constexpr bool isSync = false;

    explicit SetAlwaysUsesComplexTextCodePath(bool alwaysUseComplexText)
        : m_arguments(alwaysUseComplexText)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetDisableFontSubpixelAntialiasingForTesting {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetDisableFontSubpixelAntialiasingForTesting; }
    static constexpr bool isSync = false;

    explicit SetDisableFontSubpixelAntialiasingForTesting(bool disable)
        : m_arguments(disable)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetTrackingPreventionEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetTrackingPreventionEnabled; }
    static constexpr bool isSync = false;

    explicit SetTrackingPreventionEnabled(bool enabled)
        : m_arguments(enabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class ClearResourceLoadStatistics {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_ClearResourceLoadStatistics; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class UserPreferredLanguagesChanged {
public:
    using Arguments = std::tuple<Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_UserPreferredLanguagesChanged; }
    static constexpr bool isSync = false;

    explicit UserPreferredLanguagesChanged(const Vector<String>& languages)
        : m_arguments(languages)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&> m_arguments;
};

class FullKeyboardAccessModeChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_FullKeyboardAccessModeChanged; }
    static constexpr bool isSync = false;

    explicit FullKeyboardAccessModeChanged(bool fullKeyboardAccessEnabled)
        : m_arguments(fullKeyboardAccessEnabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

#if HAVE(MOUSE_DEVICE_OBSERVATION)
class SetHasMouseDevice {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetHasMouseDevice; }
    static constexpr bool isSync = false;

    explicit SetHasMouseDevice(bool hasMouseDevice)
        : m_arguments(hasMouseDevice)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};
#endif

#if HAVE(STYLUS_DEVICE_OBSERVATION)
class SetHasStylusDevice {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetHasStylusDevice; }
    static constexpr bool isSync = false;

    explicit SetHasStylusDevice(bool hasStylusDevice)
        : m_arguments(hasStylusDevice)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};
#endif

class StartMemorySampler {
public:
    using Arguments = std::tuple<WebKit::SandboxExtension::Handle, String, double>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_StartMemorySampler; }
    static constexpr bool isSync = false;

    StartMemorySampler(const WebKit::SandboxExtension::Handle& sampleLogFileHandle, const String& sampleLogFilePath, double interval)
        : m_arguments(sampleLogFileHandle, sampleLogFilePath, interval)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::SandboxExtension::Handle&, const String&, double> m_arguments;
};

class StopMemorySampler {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_StopMemorySampler; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetTextCheckerState {
public:
    using Arguments = std::tuple<WebKit::TextCheckerState>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetTextCheckerState; }
    static constexpr bool isSync = false;

    explicit SetTextCheckerState(const WebKit::TextCheckerState& textCheckerState)
        : m_arguments(textCheckerState)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TextCheckerState&> m_arguments;
};

class SetEnhancedAccessibility {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetEnhancedAccessibility; }
    static constexpr bool isSync = false;

    explicit SetEnhancedAccessibility(bool flag)
        : m_arguments(flag)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class GarbageCollectJavaScriptObjects {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_GarbageCollectJavaScriptObjects; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetJavaScriptGarbageCollectorTimerEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetJavaScriptGarbageCollectorTimerEnabled; }
    static constexpr bool isSync = false;

    explicit SetJavaScriptGarbageCollectorTimerEnabled(bool enable)
        : m_arguments(enable)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetInjectedBundleParameter {
public:
    using Arguments = std::tuple<String, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetInjectedBundleParameter; }
    static constexpr bool isSync = false;

    SetInjectedBundleParameter(const String& parameter, const IPC::DataReference& value)
        : m_arguments(parameter, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const IPC::DataReference&> m_arguments;
};

class SetInjectedBundleParameters {
public:
    using Arguments = std::tuple<IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetInjectedBundleParameters; }
    static constexpr bool isSync = false;

    explicit SetInjectedBundleParameters(const IPC::DataReference& parameters)
        : m_arguments(parameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::DataReference&> m_arguments;
};

class HandleInjectedBundleMessage {
public:
    using Arguments = std::tuple<String, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_HandleInjectedBundleMessage; }
    static constexpr bool isSync = false;

    HandleInjectedBundleMessage(const String& messageName, const WebKit::UserData& messageBody)
        : m_arguments(messageName, messageBody)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebKit::UserData&> m_arguments;
};

class FetchWebsiteData {
public:
    using Arguments = std::tuple<OptionSet<WebKit::WebsiteDataType>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_FetchWebsiteData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_FetchWebsiteDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::WebsiteData>;
    explicit FetchWebsiteData(const OptionSet<WebKit::WebsiteDataType>& websiteDataTypes)
        : m_arguments(websiteDataTypes)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebKit::WebsiteDataType>&> m_arguments;
};

class DeleteWebsiteData {
public:
    using Arguments = std::tuple<OptionSet<WebKit::WebsiteDataType>, WallTime>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_DeleteWebsiteData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_DeleteWebsiteDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    DeleteWebsiteData(const OptionSet<WebKit::WebsiteDataType>& websiteDataTypes, const WallTime& modifiedSince)
        : m_arguments(websiteDataTypes, modifiedSince)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebKit::WebsiteDataType>&, const WallTime&> m_arguments;
};

class DeleteWebsiteDataForOrigins {
public:
    using Arguments = std::tuple<OptionSet<WebKit::WebsiteDataType>, Vector<WebCore::SecurityOriginData>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_DeleteWebsiteDataForOrigins; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_DeleteWebsiteDataForOriginsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    DeleteWebsiteDataForOrigins(const OptionSet<WebKit::WebsiteDataType>& websiteDataTypes, const Vector<WebCore::SecurityOriginData>& origins)
        : m_arguments(websiteDataTypes, origins)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebKit::WebsiteDataType>&, const Vector<WebCore::SecurityOriginData>&> m_arguments;
};

class DeleteWebsiteDataForOrigin {
public:
    using Arguments = std::tuple<OptionSet<WebKit::WebsiteDataType>, WebCore::ClientOrigin>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_DeleteWebsiteDataForOrigin; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_DeleteWebsiteDataForOriginReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    DeleteWebsiteDataForOrigin(const OptionSet<WebKit::WebsiteDataType>& websiteDataTypes, const WebCore::ClientOrigin& origin)
        : m_arguments(websiteDataTypes, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebKit::WebsiteDataType>&, const WebCore::ClientOrigin&> m_arguments;
};

class ReloadExecutionContextsForOrigin {
public:
    using Arguments = std::tuple<WebCore::ClientOrigin, std::optional<WebCore::FrameIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_ReloadExecutionContextsForOrigin; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_ReloadExecutionContextsForOriginReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    ReloadExecutionContextsForOrigin(const WebCore::ClientOrigin& origin, const std::optional<WebCore::FrameIdentifier>& triggeringFrame)
        : m_arguments(origin, triggeringFrame)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ClientOrigin&, const std::optional<WebCore::FrameIdentifier>&> m_arguments;
};

class DeleteAllCookies {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_DeleteAllCookies; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_DeleteAllCookiesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetHiddenPageDOMTimerThrottlingIncreaseLimit {
public:
    using Arguments = std::tuple<int>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetHiddenPageDOMTimerThrottlingIncreaseLimit; }
    static constexpr bool isSync = false;

    explicit SetHiddenPageDOMTimerThrottlingIncreaseLimit(const int& milliseconds)
        : m_arguments(milliseconds)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const int&> m_arguments;
};

class SetMemoryCacheDisabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetMemoryCacheDisabled; }
    static constexpr bool isSync = false;

    explicit SetMemoryCacheDisabled(bool disabled)
        : m_arguments(disabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

#if ENABLE(SERVICE_CONTROLS)
class SetEnabledServices {
public:
    using Arguments = std::tuple<bool, bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetEnabledServices; }
    static constexpr bool isSync = false;

    SetEnabledServices(bool hasImageServices, bool hasSelectionServices, bool hasRichContentServices)
        : m_arguments(hasImageServices, hasSelectionServices, hasRichContentServices)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool, bool> m_arguments;
};
#endif

class EnsureAutomationSessionProxy {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_EnsureAutomationSessionProxy; }
    static constexpr bool isSync = false;

    explicit EnsureAutomationSessionProxy(const String& sessionIdentifier)
        : m_arguments(sessionIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class DestroyAutomationSessionProxy {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_DestroyAutomationSessionProxy; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class PrepareToSuspend {
public:
    using Arguments = std::tuple<bool, MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_PrepareToSuspend; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_PrepareToSuspendReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    PrepareToSuspend(bool isSuspensionImminent, const MonotonicTime& estimatedSuspendTime)
        : m_arguments(isSuspensionImminent, estimatedSuspendTime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, const MonotonicTime&> m_arguments;
};

class ProcessDidResume {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_ProcessDidResume; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class BackgroundResponsivenessPing {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_BackgroundResponsivenessPing; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if ENABLE(GAMEPAD)
class SetInitialGamepads {
public:
    using Arguments = std::tuple<Vector<std::optional<WebKit::GamepadData>>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetInitialGamepads; }
    static constexpr bool isSync = false;

    explicit SetInitialGamepads(const Vector<std::optional<WebKit::GamepadData>>& gamepadDatas)
        : m_arguments(gamepadDatas)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<std::optional<WebKit::GamepadData>>&> m_arguments;
};
#endif

#if ENABLE(GAMEPAD)
class GamepadConnected {
public:
    using Arguments = std::tuple<WebKit::GamepadData, WebCore::EventMakesGamepadsVisible>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_GamepadConnected; }
    static constexpr bool isSync = false;

    GamepadConnected(const WebKit::GamepadData& gamepadData, WebCore::EventMakesGamepadsVisible eventVisibility)
        : m_arguments(gamepadData, eventVisibility)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::GamepadData&, WebCore::EventMakesGamepadsVisible> m_arguments;
};
#endif

#if ENABLE(GAMEPAD)
class GamepadDisconnected {
public:
    using Arguments = std::tuple<unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_GamepadDisconnected; }
    static constexpr bool isSync = false;

    explicit GamepadDisconnected(const unsigned& index)
        : m_arguments(index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const unsigned&> m_arguments;
};
#endif

class EstablishRemoteWorkerContextConnectionToNetworkProcess {
public:
    using Arguments = std::tuple<WebKit::RemoteWorkerType, WebKit::PageGroupIdentifier, WebKit::WebPageProxyIdentifier, WebCore::PageIdentifier, WebKit::WebPreferencesStore, WebCore::RegistrableDomain, std::optional<WebCore::ScriptExecutionContextIdentifier>, WebKit::RemoteWorkerInitializationData>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_EstablishRemoteWorkerContextConnectionToNetworkProcess; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_EstablishRemoteWorkerContextConnectionToNetworkProcessReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    EstablishRemoteWorkerContextConnectionToNetworkProcess(WebKit::RemoteWorkerType workerType, const WebKit::PageGroupIdentifier& pageGroupID, const WebKit::WebPageProxyIdentifier& webPageProxyID, const WebCore::PageIdentifier& pageID, const WebKit::WebPreferencesStore& store, const WebCore::RegistrableDomain& domain, const std::optional<WebCore::ScriptExecutionContextIdentifier>& serviceWorkerPageIdentifier, const WebKit::RemoteWorkerInitializationData& initializationData)
        : m_arguments(workerType, pageGroupID, webPageProxyID, pageID, store, domain, serviceWorkerPageIdentifier, initializationData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::RemoteWorkerType, const WebKit::PageGroupIdentifier&, const WebKit::WebPageProxyIdentifier&, const WebCore::PageIdentifier&, const WebKit::WebPreferencesStore&, const WebCore::RegistrableDomain&, const std::optional<WebCore::ScriptExecutionContextIdentifier>&, const WebKit::RemoteWorkerInitializationData&> m_arguments;
};

class SetHasSuspendedPageProxy {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetHasSuspendedPageProxy; }
    static constexpr bool isSync = false;

    explicit SetHasSuspendedPageProxy(bool hasSuspendedPageProxy)
        : m_arguments(hasSuspendedPageProxy)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetIsInProcessCache {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetIsInProcessCache; }
    static constexpr bool isSync = false;

    explicit SetIsInProcessCache(bool isInProcessCache)
        : m_arguments(isInProcessCache)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class MarkIsNoLongerPrewarmed {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_MarkIsNoLongerPrewarmed; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class GetActivePagesOriginsForTesting {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_GetActivePagesOriginsForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_GetActivePagesOriginsForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if PLATFORM(COCOA)
class SetScreenProperties {
public:
    using Arguments = std::tuple<WebCore::ScreenProperties>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetScreenProperties; }
    static constexpr bool isSync = false;

    explicit SetScreenProperties(const WebCore::ScreenProperties& screenProperties)
        : m_arguments(screenProperties)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScreenProperties&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class ScrollerStylePreferenceChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_ScrollerStylePreferenceChanged; }
    static constexpr bool isSync = false;

    explicit ScrollerStylePreferenceChanged(bool useOvelayScrollbars)
        : m_arguments(useOvelayScrollbars)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};
#endif

#if PLATFORM(MAC)
class DisplayConfigurationChanged {
public:
    using Arguments = std::tuple<CGDirectDisplayID, CGDisplayChangeSummaryFlags>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_DisplayConfigurationChanged; }
    static constexpr bool isSync = false;

    DisplayConfigurationChanged(const CGDirectDisplayID& displayID, const CGDisplayChangeSummaryFlags& flags)
        : m_arguments(displayID, flags)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const CGDirectDisplayID&, const CGDisplayChangeSummaryFlags&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class UserInterfaceIdiomDidChange {
public:
    using Arguments = std::tuple<PAL::UserInterfaceIdiom>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_UserInterfaceIdiomDidChange; }
    static constexpr bool isSync = false;

    explicit UserInterfaceIdiomDidChange(PAL::UserInterfaceIdiom idiom)
        : m_arguments(idiom)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<PAL::UserInterfaceIdiom> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
class BacklightLevelDidChange {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_BacklightLevelDidChange; }
    static constexpr bool isSync = false;

    explicit BacklightLevelDidChange(float backlightLevel)
        : m_arguments(backlightLevel)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};
#endif

#if PLATFORM(MAC) || PLATFORM(MACCATALYST)
class ColorPreferencesDidChange {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_ColorPreferencesDidChange; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class IsJITEnabled {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_IsJITEnabled; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_IsJITEnabledReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if PLATFORM(COCOA)
class SetMediaMIMETypes {
public:
    using Arguments = std::tuple<Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetMediaMIMETypes; }
    static constexpr bool isSync = false;

    explicit SetMediaMIMETypes(const Vector<String>& types)
        : m_arguments(types)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&> m_arguments;
};
#endif

#if (PLATFORM(COCOA) && ENABLE(REMOTE_INSPECTOR))
class EnableRemoteWebInspector {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_EnableRemoteWebInspector; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class AddMockMediaDevice {
public:
    using Arguments = std::tuple<WebCore::MockMediaDevice>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_AddMockMediaDevice; }
    static constexpr bool isSync = false;

    explicit AddMockMediaDevice(const WebCore::MockMediaDevice& device)
        : m_arguments(device)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MockMediaDevice&> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class ClearMockMediaDevices {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_ClearMockMediaDevices; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class RemoveMockMediaDevice {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RemoveMockMediaDevice; }
    static constexpr bool isSync = false;

    explicit RemoveMockMediaDevice(const String& persistentId)
        : m_arguments(persistentId)
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

#if ENABLE(MEDIA_STREAM)
class SetMockMediaDeviceIsEphemeral {
public:
    using Arguments = std::tuple<String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetMockMediaDeviceIsEphemeral; }
    static constexpr bool isSync = false;

    SetMockMediaDeviceIsEphemeral(const String& persistentId, bool isEphemeral)
        : m_arguments(persistentId, isEphemeral)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, bool> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class ResetMockMediaDevices {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_ResetMockMediaDevices; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if (ENABLE(MEDIA_STREAM) && ENABLE(SANDBOX_EXTENSIONS))
class GrantUserMediaDeviceSandboxExtensions {
public:
    using Arguments = std::tuple<WebKit::MediaDeviceSandboxExtensions>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_GrantUserMediaDeviceSandboxExtensions; }
    static constexpr bool isSync = false;

    explicit GrantUserMediaDeviceSandboxExtensions(const WebKit::MediaDeviceSandboxExtensions& sandboxExtensions)
        : m_arguments(sandboxExtensions)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::MediaDeviceSandboxExtensions&> m_arguments;
};
#endif

#if (ENABLE(MEDIA_STREAM) && ENABLE(SANDBOX_EXTENSIONS))
class RevokeUserMediaDeviceSandboxExtensions {
public:
    using Arguments = std::tuple<Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RevokeUserMediaDeviceSandboxExtensions; }
    static constexpr bool isSync = false;

    explicit RevokeUserMediaDeviceSandboxExtensions(const Vector<String>& sandboxExtensionIDs)
        : m_arguments(sandboxExtensionIDs)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&> m_arguments;
};
#endif

class ClearCurrentModifierStateForTesting {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_ClearCurrentModifierStateForTesting; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetBackForwardCacheCapacity {
public:
    using Arguments = std::tuple<unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetBackForwardCacheCapacity; }
    static constexpr bool isSync = false;

    explicit SetBackForwardCacheCapacity(const unsigned& capacity)
        : m_arguments(capacity)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const unsigned&> m_arguments;
};

class ClearCachedPage {
public:
    using Arguments = std::tuple<WebCore::BackForwardItemIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_ClearCachedPage; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_ClearCachedPageReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ClearCachedPage(const WebCore::BackForwardItemIdentifier& backForwardItemID)
        : m_arguments(backForwardItemID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::BackForwardItemIdentifier&> m_arguments;
};

#if PLATFORM(GTK) || PLATFORM(WPE)
class SendMessageToWebProcessExtension {
public:
    using Arguments = std::tuple<WebKit::UserMessage>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SendMessageToWebProcessExtension; }
    static constexpr bool isSync = false;

    explicit SendMessageToWebProcessExtension(const WebKit::UserMessage& userMessage)
        : m_arguments(userMessage)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::UserMessage&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SeedResourceLoadStatisticsForTesting {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain, WebCore::RegistrableDomain, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SeedResourceLoadStatisticsForTesting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_SeedResourceLoadStatisticsForTestingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SeedResourceLoadStatisticsForTesting(const WebCore::RegistrableDomain& firstPartyDomain, const WebCore::RegistrableDomain& thirdPartyDomain, bool shouldScheduleNotification)
        : m_arguments(firstPartyDomain, thirdPartyDomain, shouldScheduleNotification)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&, const WebCore::RegistrableDomain&, bool> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetThirdPartyCookieBlockingMode {
public:
    using Arguments = std::tuple<WebCore::ThirdPartyCookieBlockingMode>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetThirdPartyCookieBlockingMode; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_SetThirdPartyCookieBlockingModeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit SetThirdPartyCookieBlockingMode(WebCore::ThirdPartyCookieBlockingMode blockingMode)
        : m_arguments(blockingMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::ThirdPartyCookieBlockingMode> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetDomainsWithUserInteraction {
public:
    using Arguments = std::tuple<HashSet<WebCore::RegistrableDomain>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetDomainsWithUserInteraction; }
    static constexpr bool isSync = false;

    explicit SetDomainsWithUserInteraction(const HashSet<WebCore::RegistrableDomain>& domains)
        : m_arguments(domains)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const HashSet<WebCore::RegistrableDomain>&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SetDomainsWithCrossPageStorageAccess {
public:
    using Arguments = std::tuple<HashMap<WebCore::RegistrableDomain, WebCore::RegistrableDomain>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetDomainsWithCrossPageStorageAccess; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_SetDomainsWithCrossPageStorageAccessReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit SetDomainsWithCrossPageStorageAccess(const HashMap<WebCore::RegistrableDomain, WebCore::RegistrableDomain>& domains)
        : m_arguments(domains)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const HashMap<WebCore::RegistrableDomain, WebCore::RegistrableDomain>&> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class SendResourceLoadStatisticsDataImmediately {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SendResourceLoadStatisticsDataImmediately; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_SendResourceLoadStatisticsDataImmediatelyReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class GrantAccessToAssetServices {
public:
    using Arguments = std::tuple<Vector<WebKit::SandboxExtension::Handle>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_GrantAccessToAssetServices; }
    static constexpr bool isSync = false;

    explicit GrantAccessToAssetServices(const Vector<WebKit::SandboxExtension::Handle>& assetServicesHandles)
        : m_arguments(assetServicesHandles)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::SandboxExtension::Handle>&> m_arguments;
};

class RevokeAccessToAssetServices {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RevokeAccessToAssetServices; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SwitchFromStaticFontRegistryToUserFontRegistry {
public:
    using Arguments = std::tuple<Vector<WebKit::SandboxExtension::Handle>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SwitchFromStaticFontRegistryToUserFontRegistry; }
    static constexpr bool isSync = false;

    explicit SwitchFromStaticFontRegistryToUserFontRegistry(const Vector<WebKit::SandboxExtension::Handle>& fontMachExtensionHandles)
        : m_arguments(fontMachExtensionHandles)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::SandboxExtension::Handle>&> m_arguments;
};

#if PLATFORM(COCOA)
class DisableURLSchemeCheckInDataDetectors {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_DisableURLSchemeCheckInDataDetectors; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class UnblockServicesRequiredByAccessibility {
public:
    using Arguments = std::tuple<Vector<WebKit::SandboxExtension::Handle>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_UnblockServicesRequiredByAccessibility; }
    static constexpr bool isSync = false;

    explicit UnblockServicesRequiredByAccessibility(const Vector<WebKit::SandboxExtension::Handle>& handleArray)
        : m_arguments(handleArray)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::SandboxExtension::Handle>&> m_arguments;
};
#endif

#if (PLATFORM(COCOA) && ENABLE(CFPREFS_DIRECT_MODE))
class NotifyPreferencesChanged {
public:
    using Arguments = std::tuple<String, String, std::optional<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_NotifyPreferencesChanged; }
    static constexpr bool isSync = false;

    NotifyPreferencesChanged(const String& domain, const String& key, const std::optional<String>& encodedValue)
        : m_arguments(domain, key, encodedValue)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const std::optional<String>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class PowerSourceDidChange {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_PowerSourceDidChange; }
    static constexpr bool isSync = false;

    explicit PowerSourceDidChange(bool hasAC)
        : m_arguments(hasAC)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};
#endif

#if PLATFORM(GTK) && !USE(GTK4)
class SetUseSystemAppearanceForScrollbars {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetUseSystemAppearanceForScrollbars; }
    static constexpr bool isSync = false;

    explicit SetUseSystemAppearanceForScrollbars(bool useSystemAppearanceForScrollbars)
        : m_arguments(useSystemAppearanceForScrollbars)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class DidWriteToPasteboardAsynchronously {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_DidWriteToPasteboardAsynchronously; }
    static constexpr bool isSync = false;

    explicit DidWriteToPasteboardAsynchronously(const String& pasteboardName)
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

#if HAVE(CVDISPLAYLINK)
class DisplayDidRefresh {
public:
    using Arguments = std::tuple<uint32_t, WebCore::DisplayUpdate>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_DisplayDidRefresh; }
    static constexpr bool isSync = false;

    DisplayDidRefresh(uint32_t displayID, const WebCore::DisplayUpdate& update)
        : m_arguments(displayID, update)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const WebCore::DisplayUpdate&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class SystemWillPowerOn {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SystemWillPowerOn; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(MAC)
class SystemWillSleep {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SystemWillSleep; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(MAC)
class SystemDidWake {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SystemDidWake; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if HAVE(AUDIO_COMPONENT_SERVER_REGISTRATIONS)
class ConsumeAudioComponentRegistrations {
public:
    using Arguments = std::tuple<IPC::SharedBufferReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_ConsumeAudioComponentRegistrations; }
    static constexpr bool isSync = false;

    explicit ConsumeAudioComponentRegistrations(const IPC::SharedBufferReference& registrationData)
        : m_arguments(registrationData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::SharedBufferReference&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class AccessibilityPreferencesDidChange {
public:
    using Arguments = std::tuple<WebKit::AccessibilityPreferences>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_AccessibilityPreferencesDidChange; }
    static constexpr bool isSync = false;

    explicit AccessibilityPreferencesDidChange(const WebKit::AccessibilityPreferences& accessibilityPreferences)
        : m_arguments(accessibilityPreferences)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::AccessibilityPreferences&> m_arguments;
};
#endif

#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
class SetMediaAccessibilityPreferences {
public:
    using Arguments = std::tuple<WebCore::CaptionUserPreferences::CaptionDisplayMode, Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_SetMediaAccessibilityPreferences; }
    static constexpr bool isSync = false;

    SetMediaAccessibilityPreferences(const WebCore::CaptionUserPreferences::CaptionDisplayMode& displayMode, const Vector<String>& languages)
        : m_arguments(displayMode, languages)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::CaptionUserPreferences::CaptionDisplayMode&, const Vector<String>&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class OpenDirectoryCacheInvalidated {
public:
    using Arguments = std::tuple<WebKit::SandboxExtension::Handle, WebKit::SandboxExtension::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_OpenDirectoryCacheInvalidated; }
    static constexpr bool isSync = false;

    OpenDirectoryCacheInvalidated(const WebKit::SandboxExtension::Handle& handle, const WebKit::SandboxExtension::Handle& machBootstrapHandle)
        : m_arguments(handle, machBootstrapHandle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::SandboxExtension::Handle&, const WebKit::SandboxExtension::Handle&> m_arguments;
};
#endif

class ReleaseMemory {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_ReleaseMemory; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebProcess_ReleaseMemoryReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RemotePostMessage {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, std::optional<WebCore::SecurityOriginData>, WebCore::MessageWithMessagePorts>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RemotePostMessage; }
    static constexpr bool isSync = false;

    RemotePostMessage(const WebCore::FrameIdentifier& frameIdentifier, const std::optional<WebCore::SecurityOriginData>& target, const WebCore::MessageWithMessagePorts& message)
        : m_arguments(frameIdentifier, target, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const std::optional<WebCore::SecurityOriginData>&, const WebCore::MessageWithMessagePorts&> m_arguments;
};

class RenderTreeAsText {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, size_t, OptionSet<WebCore::RenderAsTextFlag>>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_RenderTreeAsText; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    RenderTreeAsText(const WebCore::FrameIdentifier& frameIdentifier, size_t baseIndent, const OptionSet<WebCore::RenderAsTextFlag>& behavior)
        : m_arguments(frameIdentifier, baseIndent, behavior)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, size_t, const OptionSet<WebCore::RenderAsTextFlag>&> m_arguments;
};

class AddAllowedFirstPartyForCookies {
public:
    using Arguments = std::tuple<WebCore::RegistrableDomain>;

    static IPC::MessageName name() { return IPC::MessageName::WebProcess_AddAllowedFirstPartyForCookies; }
    static constexpr bool isSync = false;

    explicit AddAllowedFirstPartyForCookies(const WebCore::RegistrableDomain& firstPartyDomain)
        : m_arguments(firstPartyDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RegistrableDomain&> m_arguments;
};

} // namespace WebProcess
} // namespace Messages
