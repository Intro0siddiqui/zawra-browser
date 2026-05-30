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
#include "GeolocationIdentifier.h"
#include "IdentifierTypes.h"
#if PLATFORM(GTK) || PLATFORM(WPE)
#include "InputMethodState.h"
#endif
#include "LayerHostingContext.h"
#include "MessageNames.h"
#include "PDFPluginIdentifier.h"
#include "ShareableBitmap.h"
#include "ShareableResource.h"
#include "SharedMemory.h"
#include "WebEventModifier.h"
#include "WebPageCreationParameters.h"
#include "WebPageProxyIdentifier.h"
#include "WebPopupItem.h"
#include "WebSpeechSynthesisVoice.h"
#include "WebURLSchemeHandlerIdentifier.h"
#include <WebCore/ActivityState.h>
#include <WebCore/AutoplayEvent.h>
#include <WebCore/BackForwardItemIdentifier.h>
#include <WebCore/CaptureDeviceWithCapabilities.h>
#include <WebCore/Color.h>
#include <WebCore/ContactInfo.h>
#include <WebCore/DiagnosticLoggingClient.h>
#include <WebCore/DiagnosticLoggingDomain.h>
#include <WebCore/DictationContext.h>
#include <WebCore/DragActions.h>
#include <WebCore/FloatPoint.h>
#include <WebCore/FloatQuad.h>
#include <WebCore/FrameIdentifier.h>
#include <WebCore/HTMLModelElementCamera.h>
#include <WebCore/InspectorOverlay.h>
#include <WebCore/IntRect.h>
#include <WebCore/LayoutMilestone.h>
#include <WebCore/MediaControlsContextMenuItem.h>
#include <WebCore/MediaKeySystemRequestIdentifier.h>
#if ENABLE(WIRELESS_PLAYBACK_TARGET)
#include <WebCore/MediaPlaybackTargetContext.h>
#endif
#include <WebCore/MediaPlayerIdentifier.h>
#include <WebCore/MediaProducer.h>
#include <WebCore/MediaSessionIdentifier.h>
#include <WebCore/PageIdentifier.h>
#include <WebCore/PlaybackTargetClientContextIdentifier.h>
#include <WebCore/ProcessQualified.h>
#include <WebCore/RectEdges.h>
#include <WebCore/ResourceError.h>
#include <WebCore/ResourceLoaderIdentifier.h>
#include <WebCore/SearchPopupMenu.h>
#include <WebCore/SerializedAttachmentData.h>
#include <WebCore/SleepDisablerIdentifier.h>
#include <WebCore/TextCheckerClient.h>
#include <WebCore/TextChecking.h>
#include <WebCore/TextIndicator.h>
#include <WebCore/TextManipulationItem.h>
#include <WebCore/UserMediaRequestIdentifier.h>
#include <optional>
#include <utility>
#include <wtf/Expected.h>
#include <wtf/Forward.h>
#include <wtf/MachSendRight.h>
#include <wtf/ObjectIdentifier.h>
#include <wtf/OptionSet.h>
#include <wtf/Seconds.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace IPC {
class FormDataReference;
class SharedBufferReference;
}

namespace Inspector {
enum class InspectorTargetType : uint8_t;
}

namespace WebCore {
class CertificateInfo;
class Color;
class ContentFilterUnblockHandler;
class Cursor;
class FloatPoint;
class FloatRect;
class FloatSize;
class IntPoint;
class IntRect;
class IntSize;
class LayoutPoint;
class ResourceError;
class ResourceRequest;
class ResourceResponse;
class SecurityOriginData;
class SelectionData;
class TextCheckingRequestData;
enum class HasInsecureContent : bool;
enum class LockBackForwardList : bool;
enum class ShouldSample : bool;
enum class WillContinueLoading : bool;
enum class WillInternallyHandleFailure : bool;
enum class AlternativeTextType : uint8_t;
enum class AutocorrectionResponse : uint8_t;
enum class AutoplayEvent : uint8_t;
enum class CookieConsentDecisionResult : uint8_t;
enum class DOMPasteAccessCategory : uint8_t;
enum class DOMPasteAccessResponse : uint8_t;
enum class DeviceOrientationOrMotionPermissionState : uint8_t;
enum class DragHandlingMethod : uint8_t;
enum class FocusDirection : uint8_t;
enum class FrameLoadType : uint8_t;
enum class InputMode : uint8_t;
enum class MouseEventPolicy : uint8_t;
enum class ReasonForDismissingAlternativeText : uint8_t;
enum class RouteSharingPolicy : uint8_t;
struct AppHighlight;
struct ApplePayAMSUIRequest;
struct ContactsRequestData;
struct ContentRuleListResults;
struct DataDetectorElementInfo;
struct DataListSuggestionInformation;
struct DateTimeChooserParameters;
struct DictionaryPopupInfo;
struct DragItem;
struct FileChooserSettings;
struct GrammarDetail;
struct HTMLModelElementCamera;
struct ImageBufferBackendParameters;
struct LinkIcon;
struct MediaDeviceHashSalts;
struct MediaStreamRequest;
struct MediaUsageInfo;
struct MockWebAuthenticationConfiguration;
struct PromisedAttachmentInfo;
struct ShareDataWithParsedURL;
struct SystemPreviewInfo;
struct TextIndicatorData;
struct TextRecognitionResult;
struct TranslationContextMenuInfo;
struct ViewportAttributes;
struct WindowFeatures;
}

namespace WebKit {
class CallbackID;
class ContextMenuContextData;
class TouchBarMenuData;
class UserData;
enum class UndoOrRedo : bool;
enum class WebEventType : int8_t;
enum class SameDocumentNavigationType : uint8_t;
struct BackForwardListItemState;
struct DataDetectionResult;
struct EditorState;
struct FocusedElementInformation;
struct FrameInfoData;
struct InteractionInformationAtPosition;
struct ModelIdentifier;
struct NavigationActionData;
struct PDFContextMenu;
struct PlatformPopupMenuData;
struct PolicyDecision;
struct TouchBarMenuItemData;
struct URLSchemeTaskParameters;
struct UserMessage;
struct WebAutocorrectionContext;
struct WebBackForwardListCounts;
struct WebHitTestResultData;
struct WebNavigationDataStore;
}

namespace Messages {
namespace WebPageProxy {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebPageProxy;
}

class CreateNewPage {
public:
    using Arguments = std::tuple<WebKit::FrameInfoData, WebKit::WebPageProxyIdentifier, WebCore::ResourceRequest, WebCore::WindowFeatures, WebKit::NavigationActionData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CreateNewPage; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::PageIdentifier>, std::optional<WebKit::WebPageCreationParameters>>;
    CreateNewPage(const WebKit::FrameInfoData& originatingFrameInfoData, const WebKit::WebPageProxyIdentifier& originatingPageID, const WebCore::ResourceRequest& request, const WebCore::WindowFeatures& windowFeatures, const WebKit::NavigationActionData& navigationActionData)
        : m_arguments(originatingFrameInfoData, originatingPageID, request, windowFeatures, navigationActionData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::FrameInfoData&, const WebKit::WebPageProxyIdentifier&, const WebCore::ResourceRequest&, const WebCore::WindowFeatures&, const WebKit::NavigationActionData&> m_arguments;
};

class ShowPage {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowPage; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ClosePage {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ClosePage; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RunJavaScriptAlert {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::FrameInfoData, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RunJavaScriptAlert; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    RunJavaScriptAlert(const WebCore::FrameIdentifier& frameID, const WebKit::FrameInfoData& frameInfo, const String& message)
        : m_arguments(frameID, frameInfo, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::FrameInfoData&, const String&> m_arguments;
};

class RunJavaScriptConfirm {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::FrameInfoData, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RunJavaScriptConfirm; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    RunJavaScriptConfirm(const WebCore::FrameIdentifier& frameID, const WebKit::FrameInfoData& frameInfo, const String& message)
        : m_arguments(frameID, frameInfo, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::FrameInfoData&, const String&> m_arguments;
};

class RunJavaScriptPrompt {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::FrameInfoData, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RunJavaScriptPrompt; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    RunJavaScriptPrompt(const WebCore::FrameIdentifier& frameID, const WebKit::FrameInfoData& frameInfo, const String& message, const String& defaultValue)
        : m_arguments(frameID, frameInfo, message, defaultValue)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::FrameInfoData&, const String&, const String&> m_arguments;
};

class MouseDidMoveOverElement {
public:
    using Arguments = std::tuple<WebKit::WebHitTestResultData, OptionSet<WebKit::WebEventModifier>, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_MouseDidMoveOverElement; }
    static constexpr bool isSync = false;

    MouseDidMoveOverElement(const WebKit::WebHitTestResultData& hitTestResultData, const OptionSet<WebKit::WebEventModifier>& modifiers, const WebKit::UserData& userData)
        : m_arguments(hitTestResultData, modifiers, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebHitTestResultData&, const OptionSet<WebKit::WebEventModifier>&, const WebKit::UserData&> m_arguments;
};

class DidChangeViewportProperties {
public:
    using Arguments = std::tuple<WebCore::ViewportAttributes>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidChangeViewportProperties; }
    static constexpr bool isSync = false;

    explicit DidChangeViewportProperties(const WebCore::ViewportAttributes& attributes)
        : m_arguments(attributes)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ViewportAttributes&> m_arguments;
};

class DidReceiveEvent {
public:
    using Arguments = std::tuple<WebKit::WebEventType, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidReceiveEvent; }
    static constexpr bool isSync = false;

    DidReceiveEvent(WebKit::WebEventType eventType, bool handled)
        : m_arguments(eventType, handled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::WebEventType, bool> m_arguments;
};

class SetCursor {
public:
    using Arguments = std::tuple<WebCore::Cursor>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetCursor; }
    static constexpr bool isSync = false;

    explicit SetCursor(const WebCore::Cursor& cursor)
        : m_arguments(cursor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Cursor&> m_arguments;
};

class SetCursorHiddenUntilMouseMoves {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetCursorHiddenUntilMouseMoves; }
    static constexpr bool isSync = false;

    explicit SetCursorHiddenUntilMouseMoves(bool hiddenUntilMouseMoves)
        : m_arguments(hiddenUntilMouseMoves)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetStatusText {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetStatusText; }
    static constexpr bool isSync = false;

    explicit SetStatusText(const String& statusText)
        : m_arguments(statusText)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class SetFocus {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetFocus; }
    static constexpr bool isSync = false;

    explicit SetFocus(bool focused)
        : m_arguments(focused)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class TakeFocus {
public:
    using Arguments = std::tuple<WebCore::FocusDirection>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_TakeFocus; }
    static constexpr bool isSync = false;

    explicit TakeFocus(WebCore::FocusDirection direction)
        : m_arguments(direction)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::FocusDirection> m_arguments;
};

class FocusFromServiceWorker {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_FocusFromServiceWorker; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_FocusFromServiceWorkerReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class FocusedFrameChanged {
public:
    using Arguments = std::tuple<std::optional<WebCore::FrameIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_FocusedFrameChanged; }
    static constexpr bool isSync = false;

    explicit FocusedFrameChanged(const std::optional<WebCore::FrameIdentifier>& frameID)
        : m_arguments(frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::FrameIdentifier>&> m_arguments;
};

class SetRenderTreeSize {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetRenderTreeSize; }
    static constexpr bool isSync = false;

    explicit SetRenderTreeSize(uint64_t treeSize)
        : m_arguments(treeSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class SetToolbarsAreVisible {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetToolbarsAreVisible; }
    static constexpr bool isSync = false;

    explicit SetToolbarsAreVisible(bool toolbarsAreVisible)
        : m_arguments(toolbarsAreVisible)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class GetToolbarsAreVisible {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_GetToolbarsAreVisible; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetMenuBarIsVisible {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetMenuBarIsVisible; }
    static constexpr bool isSync = false;

    explicit SetMenuBarIsVisible(bool menuBarIsVisible)
        : m_arguments(menuBarIsVisible)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class GetMenuBarIsVisible {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_GetMenuBarIsVisible; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetStatusBarIsVisible {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetStatusBarIsVisible; }
    static constexpr bool isSync = false;

    explicit SetStatusBarIsVisible(bool statusBarIsVisible)
        : m_arguments(statusBarIsVisible)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class GetStatusBarIsVisible {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_GetStatusBarIsVisible; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetIsResizable {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetIsResizable; }
    static constexpr bool isSync = false;

    explicit SetIsResizable(bool isResizable)
        : m_arguments(isResizable)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetWindowFrame {
public:
    using Arguments = std::tuple<WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetWindowFrame; }
    static constexpr bool isSync = false;

    explicit SetWindowFrame(const WebCore::FloatRect& windowFrame)
        : m_arguments(windowFrame)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&> m_arguments;
};

class GetWindowFrame {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_GetWindowFrame; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::FloatRect>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ScreenToRootView {
public:
    using Arguments = std::tuple<WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ScreenToRootView; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::IntPoint>;
    explicit ScreenToRootView(const WebCore::IntPoint& screenPoint)
        : m_arguments(screenPoint)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&> m_arguments;
};

class RootViewToScreen {
public:
    using Arguments = std::tuple<WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RootViewToScreen; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::IntRect>;
    explicit RootViewToScreen(const WebCore::IntRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&> m_arguments;
};

class AccessibilityScreenToRootView {
public:
    using Arguments = std::tuple<WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_AccessibilityScreenToRootView; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::IntPoint>;
    explicit AccessibilityScreenToRootView(const WebCore::IntPoint& screenPoint)
        : m_arguments(screenPoint)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&> m_arguments;
};

class RootViewToAccessibilityScreen {
public:
    using Arguments = std::tuple<WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RootViewToAccessibilityScreen; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::IntRect>;
    explicit RootViewToAccessibilityScreen(const WebCore::IntRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&> m_arguments;
};

#if PLATFORM(COCOA) || PLATFORM(GTK)
class ShowValidationMessage {
public:
    using Arguments = std::tuple<WebCore::IntRect, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowValidationMessage; }
    static constexpr bool isSync = false;

    ShowValidationMessage(const WebCore::IntRect& anchorRect, const String& message)
        : m_arguments(anchorRect, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&, const String&> m_arguments;
};
#endif

#if PLATFORM(COCOA) || PLATFORM(GTK)
class HideValidationMessage {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HideValidationMessage; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class RunBeforeUnloadConfirmPanel {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::FrameInfoData, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RunBeforeUnloadConfirmPanel; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    RunBeforeUnloadConfirmPanel(const WebCore::FrameIdentifier& frameID, const WebKit::FrameInfoData& frameInfo, const String& message)
        : m_arguments(frameID, frameInfo, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::FrameInfoData&, const String&> m_arguments;
};

class PageDidScroll {
public:
    using Arguments = std::tuple<WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_PageDidScroll; }
    static constexpr bool isSync = false;

    explicit PageDidScroll(const WebCore::IntPoint& scrollPosition)
        : m_arguments(scrollPosition)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&> m_arguments;
};

class SetHasActiveAnimatedScrolls {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetHasActiveAnimatedScrolls; }
    static constexpr bool isSync = false;

    explicit SetHasActiveAnimatedScrolls(bool hasActiveAnimatedScrolls)
        : m_arguments(hasActiveAnimatedScrolls)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class RunOpenPanel {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::FrameInfoData, WebCore::FileChooserSettings>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RunOpenPanel; }
    static constexpr bool isSync = false;

    RunOpenPanel(const WebCore::FrameIdentifier& frameID, const WebKit::FrameInfoData& frameInfo, const WebCore::FileChooserSettings& parameters)
        : m_arguments(frameID, frameInfo, parameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::FrameInfoData&, const WebCore::FileChooserSettings&> m_arguments;
};

class ShowShareSheet {
public:
    using Arguments = std::tuple<WebCore::ShareDataWithParsedURL>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowShareSheet; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ShowShareSheetReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit ShowShareSheet(const WebCore::ShareDataWithParsedURL& shareData)
        : m_arguments(shareData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ShareDataWithParsedURL&> m_arguments;
};

class ShowContactPicker {
public:
    using Arguments = std::tuple<WebCore::ContactsRequestData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowContactPicker; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ShowContactPickerReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<Vector<WebCore::ContactInfo>>>;
    explicit ShowContactPicker(const WebCore::ContactsRequestData& requestData)
        : m_arguments(requestData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ContactsRequestData&> m_arguments;
};

class PrintFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, String, WebCore::FloatSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_PrintFrame; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    PrintFrame(const WebCore::FrameIdentifier& frameID, const String& title, const WebCore::FloatSize& pdfFirstPageSize)
        : m_arguments(frameID, title, pdfFirstPageSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const String&, const WebCore::FloatSize&> m_arguments;
};

class RunModal {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RunModal; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class NotifyScrollerThumbIsVisibleInRect {
public:
    using Arguments = std::tuple<WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_NotifyScrollerThumbIsVisibleInRect; }
    static constexpr bool isSync = false;

    explicit NotifyScrollerThumbIsVisibleInRect(const WebCore::IntRect& scrollerThumb)
        : m_arguments(scrollerThumb)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&> m_arguments;
};

class RecommendedScrollbarStyleDidChange {
public:
    using Arguments = std::tuple<int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RecommendedScrollbarStyleDidChange; }
    static constexpr bool isSync = false;

    explicit RecommendedScrollbarStyleDidChange(int32_t newStyle)
        : m_arguments(newStyle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t> m_arguments;
};

class DidChangeScrollbarsForMainFrame {
public:
    using Arguments = std::tuple<bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidChangeScrollbarsForMainFrame; }
    static constexpr bool isSync = false;

    DidChangeScrollbarsForMainFrame(bool hasHorizontalScrollbar, bool hasVerticalScrollbar)
        : m_arguments(hasHorizontalScrollbar, hasVerticalScrollbar)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool> m_arguments;
};

class DidChangeScrollOffsetPinningForMainFrame {
public:
    using Arguments = std::tuple<WebCore::RectEdges<bool>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidChangeScrollOffsetPinningForMainFrame; }
    static constexpr bool isSync = false;

    explicit DidChangeScrollOffsetPinningForMainFrame(const WebCore::RectEdges<bool>& pinnedState)
        : m_arguments(pinnedState)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RectEdges<bool>&> m_arguments;
};

class DidChangePageCount {
public:
    using Arguments = std::tuple<unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidChangePageCount; }
    static constexpr bool isSync = false;

    explicit DidChangePageCount(const unsigned& pageCount)
        : m_arguments(pageCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const unsigned&> m_arguments;
};

class ThemeColorChanged {
public:
    using Arguments = std::tuple<WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ThemeColorChanged; }
    static constexpr bool isSync = false;

    explicit ThemeColorChanged(const WebCore::Color& themeColor)
        : m_arguments(themeColor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Color&> m_arguments;
};

class PageExtendedBackgroundColorDidChange {
public:
    using Arguments = std::tuple<WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_PageExtendedBackgroundColorDidChange; }
    static constexpr bool isSync = false;

    explicit PageExtendedBackgroundColorDidChange(const WebCore::Color& backgroundColor)
        : m_arguments(backgroundColor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Color&> m_arguments;
};

class SampledPageTopColorChanged {
public:
    using Arguments = std::tuple<WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SampledPageTopColorChanged; }
    static constexpr bool isSync = false;

    explicit SampledPageTopColorChanged(const WebCore::Color& sampledPageTopColor)
        : m_arguments(sampledPageTopColor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Color&> m_arguments;
};

class SetCanShortCircuitHorizontalWheelEvents {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetCanShortCircuitHorizontalWheelEvents; }
    static constexpr bool isSync = false;

    explicit SetCanShortCircuitHorizontalWheelEvents(bool canShortCircuitHorizontalWheelEvents)
        : m_arguments(canShortCircuitHorizontalWheelEvents)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class DidChangeContentSize {
public:
    using Arguments = std::tuple<WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidChangeContentSize; }
    static constexpr bool isSync = false;

    explicit DidChangeContentSize(const WebCore::IntSize& newSize)
        : m_arguments(newSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntSize&> m_arguments;
};

class DidChangeIntrinsicContentSize {
public:
    using Arguments = std::tuple<WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidChangeIntrinsicContentSize; }
    static constexpr bool isSync = false;

    explicit DidChangeIntrinsicContentSize(const WebCore::IntSize& newIntrinsicContentSize)
        : m_arguments(newIntrinsicContentSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntSize&> m_arguments;
};

#if ENABLE(INPUT_TYPE_COLOR)
class ShowColorPicker {
public:
    using Arguments = std::tuple<WebCore::Color, WebCore::IntRect, Vector<WebCore::Color>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowColorPicker; }
    static constexpr bool isSync = false;

    ShowColorPicker(const WebCore::Color& initialColor, const WebCore::IntRect& elementRect, const Vector<WebCore::Color>& suggestions)
        : m_arguments(initialColor, elementRect, suggestions)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Color&, const WebCore::IntRect&, const Vector<WebCore::Color>&> m_arguments;
};
#endif

#if ENABLE(INPUT_TYPE_COLOR)
class SetColorPickerColor {
public:
    using Arguments = std::tuple<WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetColorPickerColor; }
    static constexpr bool isSync = false;

    explicit SetColorPickerColor(const WebCore::Color& color)
        : m_arguments(color)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Color&> m_arguments;
};
#endif

#if ENABLE(INPUT_TYPE_COLOR)
class EndColorPicker {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_EndColorPicker; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(DATALIST_ELEMENT)
class ShowDataListSuggestions {
public:
    using Arguments = std::tuple<WebCore::DataListSuggestionInformation>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowDataListSuggestions; }
    static constexpr bool isSync = false;

    explicit ShowDataListSuggestions(const WebCore::DataListSuggestionInformation& suggestionInformation)
        : m_arguments(suggestionInformation)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DataListSuggestionInformation&> m_arguments;
};
#endif

#if ENABLE(DATALIST_ELEMENT)
class HandleKeydownInDataList {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleKeydownInDataList; }
    static constexpr bool isSync = false;

    explicit HandleKeydownInDataList(const String& key)
        : m_arguments(key)
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

#if ENABLE(DATALIST_ELEMENT)
class EndDataListSuggestions {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_EndDataListSuggestions; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
class ShowDateTimePicker {
public:
    using Arguments = std::tuple<WebCore::DateTimeChooserParameters>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowDateTimePicker; }
    static constexpr bool isSync = false;

    explicit ShowDateTimePicker(const WebCore::DateTimeChooserParameters& params)
        : m_arguments(params)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DateTimeChooserParameters&> m_arguments;
};
#endif

#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
class EndDateTimePicker {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_EndDateTimePicker; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class DecidePolicyForResponse {
public:
    using Arguments = std::tuple<WebKit::FrameInfoData, uint64_t, WebCore::ResourceResponse, WebCore::ResourceRequest, bool, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DecidePolicyForResponse; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_DecidePolicyForResponseReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::PolicyDecision>;
    DecidePolicyForResponse(const WebKit::FrameInfoData& frameInfo, uint64_t navigationID, const WebCore::ResourceResponse& response, const WebCore::ResourceRequest& request, bool canShowMIMEType, const String& downloadAttribute)
        : m_arguments(frameInfo, navigationID, response, request, canShowMIMEType, downloadAttribute)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::FrameInfoData&, uint64_t, const WebCore::ResourceResponse&, const WebCore::ResourceRequest&, bool, const String&> m_arguments;
};

class DecidePolicyForNavigationActionAsync {
public:
    using Arguments = std::tuple<WebKit::FrameInfoData, uint64_t, WebKit::NavigationActionData, WebKit::FrameInfoData, std::optional<WebKit::WebPageProxyIdentifier>, WebCore::ResourceRequest, WebCore::ResourceRequest, IPC::FormDataReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DecidePolicyForNavigationActionAsync; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_DecidePolicyForNavigationActionAsyncReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::PolicyDecision>;
    DecidePolicyForNavigationActionAsync(const WebKit::FrameInfoData& frameInfo, uint64_t navigationID, const WebKit::NavigationActionData& navigationActionData, const WebKit::FrameInfoData& originatingFrameInfoData, const std::optional<WebKit::WebPageProxyIdentifier>& originatingPageID, const WebCore::ResourceRequest& originalRequest, const WebCore::ResourceRequest& request, const IPC::FormDataReference& requestBody)
        : m_arguments(frameInfo, navigationID, navigationActionData, originatingFrameInfoData, originatingPageID, originalRequest, request, requestBody)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::FrameInfoData&, uint64_t, const WebKit::NavigationActionData&, const WebKit::FrameInfoData&, const std::optional<WebKit::WebPageProxyIdentifier>&, const WebCore::ResourceRequest&, const WebCore::ResourceRequest&, const IPC::FormDataReference&> m_arguments;
};

class DecidePolicyForNavigationActionSync {
public:
    using Arguments = std::tuple<WebKit::FrameInfoData, uint64_t, WebKit::NavigationActionData, WebKit::FrameInfoData, std::optional<WebKit::WebPageProxyIdentifier>, WebCore::ResourceRequest, WebCore::ResourceRequest, IPC::FormDataReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DecidePolicyForNavigationActionSync; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::PolicyDecision>;
    DecidePolicyForNavigationActionSync(const WebKit::FrameInfoData& frameInfo, uint64_t navigationID, const WebKit::NavigationActionData& navigationActionData, const WebKit::FrameInfoData& originatingFrameInfoData, const std::optional<WebKit::WebPageProxyIdentifier>& originatingPageID, const WebCore::ResourceRequest& originalRequest, const WebCore::ResourceRequest& request, const IPC::FormDataReference& requestBody)
        : m_arguments(frameInfo, navigationID, navigationActionData, originatingFrameInfoData, originatingPageID, originalRequest, request, requestBody)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::FrameInfoData&, uint64_t, const WebKit::NavigationActionData&, const WebKit::FrameInfoData&, const std::optional<WebKit::WebPageProxyIdentifier>&, const WebCore::ResourceRequest&, const WebCore::ResourceRequest&, const IPC::FormDataReference&> m_arguments;
};

class DecidePolicyForNewWindowAction {
public:
    using Arguments = std::tuple<WebKit::FrameInfoData, WebKit::NavigationActionData, WebCore::ResourceRequest, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DecidePolicyForNewWindowAction; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_DecidePolicyForNewWindowActionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::PolicyDecision>;
    DecidePolicyForNewWindowAction(const WebKit::FrameInfoData& frameInfo, const WebKit::NavigationActionData& navigationActionData, const WebCore::ResourceRequest& request, const String& frameName)
        : m_arguments(frameInfo, navigationActionData, request, frameName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::FrameInfoData&, const WebKit::NavigationActionData&, const WebCore::ResourceRequest&, const String&> m_arguments;
};

class DidChangeProgress {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidChangeProgress; }
    static constexpr bool isSync = false;

    explicit DidChangeProgress(double value)
        : m_arguments(value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class DidFinishProgress {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFinishProgress; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidStartProgress {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidStartProgress; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetNetworkRequestsInProgress {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetNetworkRequestsInProgress; }
    static constexpr bool isSync = false;

    explicit SetNetworkRequestsInProgress(bool networkRequestsInProgress)
        : m_arguments(networkRequestsInProgress)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class DidCreateMainFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidCreateMainFrame; }
    static constexpr bool isSync = false;

    explicit DidCreateMainFrame(const WebCore::FrameIdentifier& frameID)
        : m_arguments(frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&> m_arguments;
};

class DidCreateSubframe {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidCreateSubframe; }
    static constexpr bool isSync = false;

    DidCreateSubframe(const WebCore::FrameIdentifier& parent, const WebCore::FrameIdentifier& newFrameID)
        : m_arguments(parent, newFrameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebCore::FrameIdentifier&> m_arguments;
};

class DidStartProvisionalLoadForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::FrameInfoData, WebCore::ResourceRequest, uint64_t, URL, URL, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidStartProvisionalLoadForFrame; }
    static constexpr bool isSync = false;

    DidStartProvisionalLoadForFrame(const WebCore::FrameIdentifier& frameID, const WebKit::FrameInfoData& frameInfo, const WebCore::ResourceRequest& request, uint64_t navigationID, const URL& url, const URL& unreachableURL, const WebKit::UserData& userData)
        : m_arguments(frameID, frameInfo, request, navigationID, url, unreachableURL, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::FrameInfoData&, const WebCore::ResourceRequest&, uint64_t, const URL&, const URL&, const WebKit::UserData&> m_arguments;
};

class DidReceiveServerRedirectForProvisionalLoadForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, uint64_t, WebCore::ResourceRequest, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidReceiveServerRedirectForProvisionalLoadForFrame; }
    static constexpr bool isSync = false;

    DidReceiveServerRedirectForProvisionalLoadForFrame(const WebCore::FrameIdentifier& frameID, uint64_t navigationID, const WebCore::ResourceRequest& request, const WebKit::UserData& userData)
        : m_arguments(frameID, navigationID, request, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, uint64_t, const WebCore::ResourceRequest&, const WebKit::UserData&> m_arguments;
};

class WillPerformClientRedirectForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, String, double, WebCore::LockBackForwardList>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_WillPerformClientRedirectForFrame; }
    static constexpr bool isSync = false;

    WillPerformClientRedirectForFrame(const WebCore::FrameIdentifier& frameID, const String& url, double delay, WebCore::LockBackForwardList lockBackForwardList)
        : m_arguments(frameID, url, delay, lockBackForwardList)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const String&, double, WebCore::LockBackForwardList> m_arguments;
};

class DidCancelClientRedirectForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidCancelClientRedirectForFrame; }
    static constexpr bool isSync = false;

    explicit DidCancelClientRedirectForFrame(const WebCore::FrameIdentifier& frameID)
        : m_arguments(frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&> m_arguments;
};

class DidChangeProvisionalURLForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, uint64_t, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidChangeProvisionalURLForFrame; }
    static constexpr bool isSync = false;

    DidChangeProvisionalURLForFrame(const WebCore::FrameIdentifier& frameID, uint64_t navigationID, const URL& url)
        : m_arguments(frameID, navigationID, url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, uint64_t, const URL&> m_arguments;
};

class DidFailProvisionalLoadForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::FrameInfoData, WebCore::ResourceRequest, uint64_t, String, WebCore::ResourceError, WebCore::WillContinueLoading, WebKit::UserData, WebCore::WillInternallyHandleFailure>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFailProvisionalLoadForFrame; }
    static constexpr bool isSync = false;

    DidFailProvisionalLoadForFrame(const WebCore::FrameIdentifier& frameID, const WebKit::FrameInfoData& frameInfo, const WebCore::ResourceRequest& request, uint64_t navigationID, const String& provisionalURL, const WebCore::ResourceError& error, WebCore::WillContinueLoading willContinueLoading, const WebKit::UserData& userData, WebCore::WillInternallyHandleFailure willInternallyHandleFailure)
        : m_arguments(frameID, frameInfo, request, navigationID, provisionalURL, error, willContinueLoading, userData, willInternallyHandleFailure)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::FrameInfoData&, const WebCore::ResourceRequest&, uint64_t, const String&, const WebCore::ResourceError&, WebCore::WillContinueLoading, const WebKit::UserData&, WebCore::WillInternallyHandleFailure> m_arguments;
};

class DidCommitLoadForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::FrameInfoData, WebCore::ResourceRequest, uint64_t, String, bool, WebCore::FrameLoadType, WebCore::CertificateInfo, bool, bool, bool, WebCore::HasInsecureContent, WebCore::MouseEventPolicy, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidCommitLoadForFrame; }
    static constexpr bool isSync = false;

    DidCommitLoadForFrame(const WebCore::FrameIdentifier& frameID, const WebKit::FrameInfoData& frameInfo, const WebCore::ResourceRequest& request, uint64_t navigationID, const String& mimeType, bool hasCustomContentProvider, WebCore::FrameLoadType loadType, const WebCore::CertificateInfo& certificateInfo, bool usedLegacyTLS, bool wasPrivateRelayed, bool containsPluginDocument, WebCore::HasInsecureContent hasInsecureContent, WebCore::MouseEventPolicy mouseEventPolicy, const WebKit::UserData& userData)
        : m_arguments(frameID, frameInfo, request, navigationID, mimeType, hasCustomContentProvider, loadType, certificateInfo, usedLegacyTLS, wasPrivateRelayed, containsPluginDocument, hasInsecureContent, mouseEventPolicy, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::FrameInfoData&, const WebCore::ResourceRequest&, uint64_t, const String&, bool, WebCore::FrameLoadType, const WebCore::CertificateInfo&, bool, bool, bool, WebCore::HasInsecureContent, WebCore::MouseEventPolicy, const WebKit::UserData&> m_arguments;
};

class DidFailLoadForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::FrameInfoData, WebCore::ResourceRequest, uint64_t, WebCore::ResourceError, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFailLoadForFrame; }
    static constexpr bool isSync = false;

    DidFailLoadForFrame(const WebCore::FrameIdentifier& frameID, const WebKit::FrameInfoData& frameInfo, const WebCore::ResourceRequest& request, uint64_t navigationID, const WebCore::ResourceError& error, const WebKit::UserData& userData)
        : m_arguments(frameID, frameInfo, request, navigationID, error, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::FrameInfoData&, const WebCore::ResourceRequest&, uint64_t, const WebCore::ResourceError&, const WebKit::UserData&> m_arguments;
};

class DidFinishDocumentLoadForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, uint64_t, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFinishDocumentLoadForFrame; }
    static constexpr bool isSync = false;

    DidFinishDocumentLoadForFrame(const WebCore::FrameIdentifier& frameID, uint64_t navigationID, const WebKit::UserData& userData)
        : m_arguments(frameID, navigationID, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, uint64_t, const WebKit::UserData&> m_arguments;
};

class DidFinishLoadForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::FrameInfoData, WebCore::ResourceRequest, uint64_t, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFinishLoadForFrame; }
    static constexpr bool isSync = false;

    DidFinishLoadForFrame(const WebCore::FrameIdentifier& frameID, const WebKit::FrameInfoData& frameInfo, const WebCore::ResourceRequest& request, uint64_t navigationID, const WebKit::UserData& userData)
        : m_arguments(frameID, frameInfo, request, navigationID, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::FrameInfoData&, const WebCore::ResourceRequest&, uint64_t, const WebKit::UserData&> m_arguments;
};

class DidFirstLayoutForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFirstLayoutForFrame; }
    static constexpr bool isSync = false;

    DidFirstLayoutForFrame(const WebCore::FrameIdentifier& frameID, const WebKit::UserData& userData)
        : m_arguments(frameID, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::UserData&> m_arguments;
};

class DidFirstVisuallyNonEmptyLayoutForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFirstVisuallyNonEmptyLayoutForFrame; }
    static constexpr bool isSync = false;

    DidFirstVisuallyNonEmptyLayoutForFrame(const WebCore::FrameIdentifier& frameID, const WebKit::UserData& userData)
        : m_arguments(frameID, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::UserData&> m_arguments;
};

class DidReachLayoutMilestone {
public:
    using Arguments = std::tuple<OptionSet<WebCore::LayoutMilestone>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidReachLayoutMilestone; }
    static constexpr bool isSync = false;

    explicit DidReachLayoutMilestone(const OptionSet<WebCore::LayoutMilestone>& layoutMilestones)
        : m_arguments(layoutMilestones)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebCore::LayoutMilestone>&> m_arguments;
};

class DidReceiveTitleForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, String, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidReceiveTitleForFrame; }
    static constexpr bool isSync = false;

    DidReceiveTitleForFrame(const WebCore::FrameIdentifier& frameID, const String& title, const WebKit::UserData& userData)
        : m_arguments(frameID, title, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const String&, const WebKit::UserData&> m_arguments;
};

class DidDisplayInsecureContentForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidDisplayInsecureContentForFrame; }
    static constexpr bool isSync = false;

    DidDisplayInsecureContentForFrame(const WebCore::FrameIdentifier& frameID, const WebKit::UserData& userData)
        : m_arguments(frameID, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::UserData&> m_arguments;
};

class DidRunInsecureContentForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidRunInsecureContentForFrame; }
    static constexpr bool isSync = false;

    DidRunInsecureContentForFrame(const WebCore::FrameIdentifier& frameID, const WebKit::UserData& userData)
        : m_arguments(frameID, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::UserData&> m_arguments;
};

class DidSameDocumentNavigationForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, uint64_t, WebKit::SameDocumentNavigationType, URL, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidSameDocumentNavigationForFrame; }
    static constexpr bool isSync = false;

    DidSameDocumentNavigationForFrame(const WebCore::FrameIdentifier& frameID, uint64_t navigationID, WebKit::SameDocumentNavigationType type, const URL& url, const WebKit::UserData& userData)
        : m_arguments(frameID, navigationID, type, url, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, uint64_t, WebKit::SameDocumentNavigationType, const URL&, const WebKit::UserData&> m_arguments;
};

class DidSameDocumentNavigationForFrameViaJSHistoryAPI {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::SameDocumentNavigationType, URL, WebKit::NavigationActionData, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidSameDocumentNavigationForFrameViaJSHistoryAPI; }
    static constexpr bool isSync = false;

    DidSameDocumentNavigationForFrameViaJSHistoryAPI(const WebCore::FrameIdentifier& frameID, WebKit::SameDocumentNavigationType type, const URL& url, const WebKit::NavigationActionData& navigationActionData, const WebKit::UserData& userData)
        : m_arguments(frameID, type, url, navigationActionData, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, WebKit::SameDocumentNavigationType, const URL&, const WebKit::NavigationActionData&, const WebKit::UserData&> m_arguments;
};

class DidChangeMainDocument {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidChangeMainDocument; }
    static constexpr bool isSync = false;

    explicit DidChangeMainDocument(const WebCore::FrameIdentifier& frameID)
        : m_arguments(frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&> m_arguments;
};

class DidExplicitOpenForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, URL, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidExplicitOpenForFrame; }
    static constexpr bool isSync = false;

    DidExplicitOpenForFrame(const WebCore::FrameIdentifier& frameID, const URL& url, const String& mimeType)
        : m_arguments(frameID, url, mimeType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const URL&, const String&> m_arguments;
};

class DidDestroyNavigation {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidDestroyNavigation; }
    static constexpr bool isSync = false;

    explicit DidDestroyNavigation(uint64_t navigationID)
        : m_arguments(navigationID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class UpdateRemoteFrameSize {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_UpdateRemoteFrameSize; }
    static constexpr bool isSync = false;

    UpdateRemoteFrameSize(const WebCore::FrameIdentifier& frameID, const WebCore::IntSize& size)
        : m_arguments(frameID, size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebCore::IntSize&> m_arguments;
};

class MainFramePluginHandlesPageScaleGestureDidChange {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_MainFramePluginHandlesPageScaleGestureDidChange; }
    static constexpr bool isSync = false;

    explicit MainFramePluginHandlesPageScaleGestureDidChange(bool mainFramePluginHandlesPageScaleGesture)
        : m_arguments(mainFramePluginHandlesPageScaleGesture)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

#if PLATFORM(GTK) || PLATFORM(WPE)
class DidInitiateLoadForResource {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier, WebCore::FrameIdentifier, WebCore::ResourceRequest>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidInitiateLoadForResource; }
    static constexpr bool isSync = false;

    DidInitiateLoadForResource(const WebCore::ResourceLoaderIdentifier& resourceID, const WebCore::FrameIdentifier& frameID, const WebCore::ResourceRequest& request)
        : m_arguments(resourceID, frameID, request)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&, const WebCore::FrameIdentifier&, const WebCore::ResourceRequest&> m_arguments;
};
#endif

#if PLATFORM(GTK) || PLATFORM(WPE)
class DidSendRequestForResource {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier, WebCore::FrameIdentifier, WebCore::ResourceRequest, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidSendRequestForResource; }
    static constexpr bool isSync = false;

    DidSendRequestForResource(const WebCore::ResourceLoaderIdentifier& resourceID, const WebCore::FrameIdentifier& frameID, const WebCore::ResourceRequest& request, const WebCore::ResourceResponse& redirectResponse)
        : m_arguments(resourceID, frameID, request, redirectResponse)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&, const WebCore::FrameIdentifier&, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&> m_arguments;
};
#endif

#if PLATFORM(GTK) || PLATFORM(WPE)
class DidReceiveResponseForResource {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier, WebCore::FrameIdentifier, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidReceiveResponseForResource; }
    static constexpr bool isSync = false;

    DidReceiveResponseForResource(const WebCore::ResourceLoaderIdentifier& resourceID, const WebCore::FrameIdentifier& frameID, const WebCore::ResourceResponse& response)
        : m_arguments(resourceID, frameID, response)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&, const WebCore::FrameIdentifier&, const WebCore::ResourceResponse&> m_arguments;
};
#endif

#if PLATFORM(GTK) || PLATFORM(WPE)
class DidFinishLoadForResource {
public:
    using Arguments = std::tuple<WebCore::ResourceLoaderIdentifier, WebCore::FrameIdentifier, WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFinishLoadForResource; }
    static constexpr bool isSync = false;

    DidFinishLoadForResource(const WebCore::ResourceLoaderIdentifier& resourceID, const WebCore::FrameIdentifier& frameID, const WebCore::ResourceError& error)
        : m_arguments(resourceID, frameID, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceLoaderIdentifier&, const WebCore::FrameIdentifier&, const WebCore::ResourceError&> m_arguments;
};
#endif

class DidNavigateWithNavigationData {
public:
    using Arguments = std::tuple<WebKit::WebNavigationDataStore, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidNavigateWithNavigationData; }
    static constexpr bool isSync = false;

    DidNavigateWithNavigationData(const WebKit::WebNavigationDataStore& store, const WebCore::FrameIdentifier& frameID)
        : m_arguments(store, frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebNavigationDataStore&, const WebCore::FrameIdentifier&> m_arguments;
};

class DidPerformClientRedirect {
public:
    using Arguments = std::tuple<String, String, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidPerformClientRedirect; }
    static constexpr bool isSync = false;

    DidPerformClientRedirect(const String& sourceURLString, const String& destinationURLString, const WebCore::FrameIdentifier& frameID)
        : m_arguments(sourceURLString, destinationURLString, frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const WebCore::FrameIdentifier&> m_arguments;
};

class DidPerformServerRedirect {
public:
    using Arguments = std::tuple<String, String, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidPerformServerRedirect; }
    static constexpr bool isSync = false;

    DidPerformServerRedirect(const String& sourceURLString, const String& destinationURLString, const WebCore::FrameIdentifier& frameID)
        : m_arguments(sourceURLString, destinationURLString, frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const WebCore::FrameIdentifier&> m_arguments;
};

class DidUpdateHistoryTitle {
public:
    using Arguments = std::tuple<String, String, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidUpdateHistoryTitle; }
    static constexpr bool isSync = false;

    DidUpdateHistoryTitle(const String& title, const String& url, const WebCore::FrameIdentifier& frameID)
        : m_arguments(title, url, frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const WebCore::FrameIdentifier&> m_arguments;
};

class DidFinishLoadingDataForCustomContentProvider {
public:
    using Arguments = std::tuple<String, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFinishLoadingDataForCustomContentProvider; }
    static constexpr bool isSync = false;

    DidFinishLoadingDataForCustomContentProvider(const String& suggestedFilename, const IPC::DataReference& data)
        : m_arguments(suggestedFilename, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const IPC::DataReference&> m_arguments;
};

class WillSubmitForm {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebCore::FrameIdentifier, Vector<std::pair<String, String>>, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_WillSubmitForm; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_WillSubmitFormReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    WillSubmitForm(const WebCore::FrameIdentifier& frameID, const WebCore::FrameIdentifier& sourceFrameID, const Vector<std::pair<String, String>>& textFieldValues, const WebKit::UserData& userData)
        : m_arguments(frameID, sourceFrameID, textFieldValues, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebCore::FrameIdentifier&, const Vector<std::pair<String, String>>&, const WebKit::UserData&> m_arguments;
};

#if PLATFORM(IOS_FAMILY)
class InterpretKeyEvent {
public:
    using Arguments = std::tuple<WebKit::EditorState, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_InterpretKeyEvent; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    InterpretKeyEvent(const WebKit::EditorState& state, bool isCharEvent)
        : m_arguments(state, isCharEvent)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::EditorState&, bool> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class DidReceivePositionInformation {
public:
    using Arguments = std::tuple<WebKit::InteractionInformationAtPosition>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidReceivePositionInformation; }
    static constexpr bool isSync = false;

    explicit DidReceivePositionInformation(const WebKit::InteractionInformationAtPosition& information)
        : m_arguments(information)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::InteractionInformationAtPosition&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SaveImageToLibrary {
public:
    using Arguments = std::tuple<WebKit::SharedMemory::Handle, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SaveImageToLibrary; }
    static constexpr bool isSync = false;

    SaveImageToLibrary(WebKit::SharedMemory::Handle&& handle, const String& authorizationToken)
        : m_arguments(WTFMove(handle), authorizationToken)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::SharedMemory::Handle&&, const String&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class ShowPlaybackTargetPicker {
public:
    using Arguments = std::tuple<bool, WebCore::IntRect, WebCore::RouteSharingPolicy, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowPlaybackTargetPicker; }
    static constexpr bool isSync = false;

    ShowPlaybackTargetPicker(bool hasVideo, const WebCore::IntRect& elementRect, WebCore::RouteSharingPolicy policy, const String& routingContextUID)
        : m_arguments(hasVideo, elementRect, policy, routingContextUID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, const WebCore::IntRect&, WebCore::RouteSharingPolicy, const String&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class CommitPotentialTapFailed {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CommitPotentialTapFailed; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class DidNotHandleTapAsClick {
public:
    using Arguments = std::tuple<WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidNotHandleTapAsClick; }
    static constexpr bool isSync = false;

    explicit DidNotHandleTapAsClick(const WebCore::IntPoint& point)
        : m_arguments(point)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class DidCompleteSyntheticClick {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidCompleteSyntheticClick; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class DidHandleTapAsHover {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidHandleTapAsHover; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class DisableDoubleTapGesturesDuringTapIfNecessary {
public:
    using Arguments = std::tuple<WebKit::TapIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DisableDoubleTapGesturesDuringTapIfNecessary; }
    static constexpr bool isSync = false;

    explicit DisableDoubleTapGesturesDuringTapIfNecessary(const WebKit::TapIdentifier& requestID)
        : m_arguments(requestID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TapIdentifier&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class HandleSmartMagnificationInformationForPotentialTap {
public:
    using Arguments = std::tuple<WebKit::TapIdentifier, WebCore::FloatRect, bool, double, double, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleSmartMagnificationInformationForPotentialTap; }
    static constexpr bool isSync = false;

    HandleSmartMagnificationInformationForPotentialTap(const WebKit::TapIdentifier& requestID, const WebCore::FloatRect& renderRect, bool fitEntireRect, double viewportMinimumScale, double viewportMaximumScale, bool nodeIsRootLevel)
        : m_arguments(requestID, renderRect, fitEntireRect, viewportMinimumScale, viewportMaximumScale, nodeIsRootLevel)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TapIdentifier&, const WebCore::FloatRect&, bool, double, double, bool> m_arguments;
};
#endif

#if ENABLE(DATA_DETECTION)
class SetDataDetectionResult {
public:
    using Arguments = std::tuple<WebKit::DataDetectionResult>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetDataDetectionResult; }
    static constexpr bool isSync = false;

    explicit SetDataDetectionResult(const WebKit::DataDetectionResult& dataDetectionResult)
        : m_arguments(dataDetectionResult)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DataDetectionResult&> m_arguments;
};
#endif

#if ENABLE(DATA_DETECTION)
class HandleClickForDataDetectionResult {
public:
    using Arguments = std::tuple<WebCore::DataDetectorElementInfo, WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleClickForDataDetectionResult; }
    static constexpr bool isSync = false;

    HandleClickForDataDetectionResult(const WebCore::DataDetectorElementInfo& info, const WebCore::IntPoint& location)
        : m_arguments(info, location)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DataDetectorElementInfo&, const WebCore::IntPoint&> m_arguments;
};
#endif

class PageScaleFactorDidChange {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_PageScaleFactorDidChange; }
    static constexpr bool isSync = false;

    explicit PageScaleFactorDidChange(double scaleFactor)
        : m_arguments(scaleFactor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class PluginScaleFactorDidChange {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_PluginScaleFactorDidChange; }
    static constexpr bool isSync = false;

    explicit PluginScaleFactorDidChange(double zoomFactor)
        : m_arguments(zoomFactor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class PluginZoomFactorDidChange {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_PluginZoomFactorDidChange; }
    static constexpr bool isSync = false;

    explicit PluginZoomFactorDidChange(double zoomFactor)
        : m_arguments(zoomFactor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

#if PLATFORM(GTK) || PLATFORM(WPE)
class BindAccessibilityTree {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_BindAccessibilityTree; }
    static constexpr bool isSync = false;

    explicit BindAccessibilityTree(const String& plugID)
        : m_arguments(plugID)
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

#if PLATFORM(GTK) || PLATFORM(WPE)
class SetInputMethodState {
public:
    using Arguments = std::tuple<std::optional<WebKit::InputMethodState>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetInputMethodState; }
    static constexpr bool isSync = false;

    explicit SetInputMethodState(const std::optional<WebKit::InputMethodState>& state)
        : m_arguments(state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebKit::InputMethodState>&> m_arguments;
};
#endif

class BackForwardAddItem {
public:
    using Arguments = std::tuple<WebKit::BackForwardListItemState>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_BackForwardAddItem; }
    static constexpr bool isSync = false;

    explicit BackForwardAddItem(const WebKit::BackForwardListItemState& itemState)
        : m_arguments(itemState)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::BackForwardListItemState&> m_arguments;
};

class BackForwardGoToItem {
public:
    using Arguments = std::tuple<WebCore::BackForwardItemIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_BackForwardGoToItem; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::WebBackForwardListCounts>;
    explicit BackForwardGoToItem(const WebCore::BackForwardItemIdentifier& itemID)
        : m_arguments(itemID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::BackForwardItemIdentifier&> m_arguments;
};

class BackForwardItemAtIndex {
public:
    using Arguments = std::tuple<int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_BackForwardItemAtIndex; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::BackForwardItemIdentifier>>;
    explicit BackForwardItemAtIndex(int32_t itemIndex)
        : m_arguments(itemIndex)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t> m_arguments;
};

class BackForwardListContainsItem {
public:
    using Arguments = std::tuple<WebCore::BackForwardItemIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_BackForwardListContainsItem; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit BackForwardListContainsItem(const WebCore::BackForwardItemIdentifier& itemID)
        : m_arguments(itemID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::BackForwardItemIdentifier&> m_arguments;
};

class BackForwardListCounts {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_BackForwardListCounts; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::WebBackForwardListCounts>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class BackForwardClear {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_BackForwardClear; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class WillGoToBackForwardListItem {
public:
    using Arguments = std::tuple<WebCore::BackForwardItemIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_WillGoToBackForwardListItem; }
    static constexpr bool isSync = false;

    WillGoToBackForwardListItem(const WebCore::BackForwardItemIdentifier& itemID, bool inBackForwardCache)
        : m_arguments(itemID, inBackForwardCache)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::BackForwardItemIdentifier&, bool> m_arguments;
};

class RegisterEditCommandForUndo {
public:
    using Arguments = std::tuple<uint64_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RegisterEditCommandForUndo; }
    static constexpr bool isSync = false;

    RegisterEditCommandForUndo(uint64_t commandID, const String& label)
        : m_arguments(commandID, label)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const String&> m_arguments;
};

class ClearAllEditCommands {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ClearAllEditCommands; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RegisterInsertionUndoGrouping {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RegisterInsertionUndoGrouping; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class CanUndoRedo {
public:
    using Arguments = std::tuple<WebKit::UndoOrRedo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CanUndoRedo; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit CanUndoRedo(WebKit::UndoOrRedo undoOrRedo)
        : m_arguments(undoOrRedo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::UndoOrRedo> m_arguments;
};

class ExecuteUndoRedo {
public:
    using Arguments = std::tuple<WebKit::UndoOrRedo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ExecuteUndoRedo; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ExecuteUndoRedo(WebKit::UndoOrRedo undoOrRedo)
        : m_arguments(undoOrRedo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::UndoOrRedo> m_arguments;
};

class LogDiagnosticMessageFromWebProcess {
public:
    using Arguments = std::tuple<String, String, WebCore::ShouldSample>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_LogDiagnosticMessageFromWebProcess; }
    static constexpr bool isSync = false;

    LogDiagnosticMessageFromWebProcess(const String& message, const String& description, WebCore::ShouldSample shouldSample)
        : m_arguments(message, description, shouldSample)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, WebCore::ShouldSample> m_arguments;
};

class LogDiagnosticMessageWithResultFromWebProcess {
public:
    using Arguments = std::tuple<String, String, uint32_t, WebCore::ShouldSample>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_LogDiagnosticMessageWithResultFromWebProcess; }
    static constexpr bool isSync = false;

    LogDiagnosticMessageWithResultFromWebProcess(const String& message, const String& description, uint32_t result, WebCore::ShouldSample shouldSample)
        : m_arguments(message, description, result, shouldSample)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, uint32_t, WebCore::ShouldSample> m_arguments;
};

class LogDiagnosticMessageWithValueFromWebProcess {
public:
    using Arguments = std::tuple<String, String, double, unsigned, WebCore::ShouldSample>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_LogDiagnosticMessageWithValueFromWebProcess; }
    static constexpr bool isSync = false;

    LogDiagnosticMessageWithValueFromWebProcess(const String& message, const String& description, double value, const unsigned& significantFigures, WebCore::ShouldSample shouldSample)
        : m_arguments(message, description, value, significantFigures, shouldSample)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, double, const unsigned&, WebCore::ShouldSample> m_arguments;
};

class LogDiagnosticMessageWithEnhancedPrivacyFromWebProcess {
public:
    using Arguments = std::tuple<String, String, WebCore::ShouldSample>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_LogDiagnosticMessageWithEnhancedPrivacyFromWebProcess; }
    static constexpr bool isSync = false;

    LogDiagnosticMessageWithEnhancedPrivacyFromWebProcess(const String& message, const String& description, WebCore::ShouldSample shouldSample)
        : m_arguments(message, description, shouldSample)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, WebCore::ShouldSample> m_arguments;
};

class LogDiagnosticMessageWithValueDictionaryFromWebProcess {
public:
    using Arguments = std::tuple<String, String, WebCore::DiagnosticLoggingClient::ValueDictionary, WebCore::ShouldSample>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_LogDiagnosticMessageWithValueDictionaryFromWebProcess; }
    static constexpr bool isSync = false;

    LogDiagnosticMessageWithValueDictionaryFromWebProcess(const String& message, const String& description, const WebCore::DiagnosticLoggingClient::ValueDictionary& value, WebCore::ShouldSample shouldSample)
        : m_arguments(message, description, value, shouldSample)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const WebCore::DiagnosticLoggingClient::ValueDictionary&, WebCore::ShouldSample> m_arguments;
};

class LogDiagnosticMessageWithDomainFromWebProcess {
public:
    using Arguments = std::tuple<String, WebCore::DiagnosticLoggingDomain>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_LogDiagnosticMessageWithDomainFromWebProcess; }
    static constexpr bool isSync = false;

    LogDiagnosticMessageWithDomainFromWebProcess(const String& message, const WebCore::DiagnosticLoggingDomain& domain)
        : m_arguments(message, domain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::DiagnosticLoggingDomain&> m_arguments;
};

class LogScrollingEvent {
public:
    using Arguments = std::tuple<uint32_t, MonotonicTime, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_LogScrollingEvent; }
    static constexpr bool isSync = false;

    LogScrollingEvent(uint32_t eventType, const MonotonicTime& timestamp, uint64_t data)
        : m_arguments(eventType, timestamp, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const MonotonicTime&, uint64_t> m_arguments;
};

class EditorStateChanged {
public:
    using Arguments = std::tuple<WebKit::EditorState>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_EditorStateChanged; }
    static constexpr bool isSync = false;

    explicit EditorStateChanged(const WebKit::EditorState& editorState)
        : m_arguments(editorState)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::EditorState&> m_arguments;
};

class CompositionWasCanceled {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CompositionWasCanceled; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetHasHadSelectionChangesFromUserInteraction {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetHasHadSelectionChangesFromUserInteraction; }
    static constexpr bool isSync = false;

    explicit SetHasHadSelectionChangesFromUserInteraction(bool hasHadUserSelectionChanges)
        : m_arguments(hasHadUserSelectionChanges)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

#if ENABLE(IMAGE_ANALYSIS)
class RequestTextRecognition {
public:
    using Arguments = std::tuple<URL, WebKit::ShareableBitmap::Handle, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestTextRecognition; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_RequestTextRecognitionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::TextRecognitionResult>;
    RequestTextRecognition(const URL& imageURL, WebKit::ShareableBitmap::Handle&& imageData, const String& source, const String& target)
        : m_arguments(imageURL, WTFMove(imageData), source, target)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, WebKit::ShareableBitmap::Handle&&, const String&, const String&> m_arguments;
};
#endif

#if HAVE(TRANSLATION_UI_SERVICES) && ENABLE(CONTEXT_MENUS)
class HandleContextMenuTranslation {
public:
    using Arguments = std::tuple<WebCore::TranslationContextMenuInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleContextMenuTranslation; }
    static constexpr bool isSync = false;

    explicit HandleContextMenuTranslation(const WebCore::TranslationContextMenuInfo& info)
        : m_arguments(info)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::TranslationContextMenuInfo&> m_arguments;
};
#endif

#if ENABLE(MEDIA_CONTROLS_CONTEXT_MENUS) && USE(UICONTEXTMENU)
class ShowMediaControlsContextMenu {
public:
    using Arguments = std::tuple<WebCore::FloatRect, Vector<WebCore::MediaControlsContextMenuItem>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowMediaControlsContextMenu; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ShowMediaControlsContextMenuReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::MediaControlsContextMenuItem::ID>;
    ShowMediaControlsContextMenu(const WebCore::FloatRect& targetFrame, const Vector<WebCore::MediaControlsContextMenuItem>& items)
        : m_arguments(targetFrame, items)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&, const Vector<WebCore::MediaControlsContextMenuItem>&> m_arguments;
};
#endif

#if HAVE(TOUCH_BAR)
class SetIsTouchBarUpdateSupressedForHiddenContentEditable {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetIsTouchBarUpdateSupressedForHiddenContentEditable; }
    static constexpr bool isSync = false;

    explicit SetIsTouchBarUpdateSupressedForHiddenContentEditable(bool isTouchBarUpdateSupressed)
        : m_arguments(isTouchBarUpdateSupressed)
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

#if HAVE(TOUCH_BAR)
class SetIsNeverRichlyEditableForTouchBar {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetIsNeverRichlyEditableForTouchBar; }
    static constexpr bool isSync = false;

    explicit SetIsNeverRichlyEditableForTouchBar(bool isNeverRichlyEditable)
        : m_arguments(isNeverRichlyEditable)
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

class RequestDOMPasteAccess {
public:
    using Arguments = std::tuple<WebCore::DOMPasteAccessCategory, WebCore::IntRect, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestDOMPasteAccess; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DOMPasteAccessResponse>;
    RequestDOMPasteAccess(WebCore::DOMPasteAccessCategory pasteAccessCategory, const WebCore::IntRect& elementRect, const String& originIdentifier)
        : m_arguments(pasteAccessCategory, elementRect, originIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::DOMPasteAccessCategory, const WebCore::IntRect&, const String&> m_arguments;
};

class DidCountStringMatches {
public:
    using Arguments = std::tuple<String, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidCountStringMatches; }
    static constexpr bool isSync = false;

    DidCountStringMatches(const String& string, uint32_t matchCount)
        : m_arguments(string, matchCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, uint32_t> m_arguments;
};

class SetTextIndicator {
public:
    using Arguments = std::tuple<WebCore::TextIndicatorData, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetTextIndicator; }
    static constexpr bool isSync = false;

    SetTextIndicator(const WebCore::TextIndicatorData& indicator, uint64_t lifetime)
        : m_arguments(indicator, lifetime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::TextIndicatorData&, uint64_t> m_arguments;
};

class ClearTextIndicator {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ClearTextIndicator; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidFindString {
public:
    using Arguments = std::tuple<String, Vector<WebCore::IntRect>, uint32_t, int32_t, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFindString; }
    static constexpr bool isSync = false;

    DidFindString(const String& string, const Vector<WebCore::IntRect>& matchRect, uint32_t matchCount, int32_t matchIndex, bool didWrapAround)
        : m_arguments(string, matchRect, matchCount, matchIndex, didWrapAround)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const Vector<WebCore::IntRect>&, uint32_t, int32_t, bool> m_arguments;
};

class DidFailToFindString {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFailToFindString; }
    static constexpr bool isSync = false;

    explicit DidFailToFindString(const String& string)
        : m_arguments(string)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class DidFindStringMatches {
public:
    using Arguments = std::tuple<String, Vector<Vector<WebCore::IntRect>>, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFindStringMatches; }
    static constexpr bool isSync = false;

    DidFindStringMatches(const String& string, const Vector<Vector<WebCore::IntRect>>& matches, int32_t firstIndexAfterSelection)
        : m_arguments(string, matches, firstIndexAfterSelection)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const Vector<Vector<WebCore::IntRect>>&, int32_t> m_arguments;
};

class DidGetImageForFindMatch {
public:
    using Arguments = std::tuple<WebCore::ImageBufferBackendParameters, WebKit::ShareableBitmap::Handle, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidGetImageForFindMatch; }
    static constexpr bool isSync = false;

    DidGetImageForFindMatch(const WebCore::ImageBufferBackendParameters& parameters, WebKit::ShareableBitmap::Handle&& contentImageHandle, uint32_t matchIndex)
        : m_arguments(parameters, WTFMove(contentImageHandle), matchIndex)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ImageBufferBackendParameters&, WebKit::ShareableBitmap::Handle&&, uint32_t> m_arguments;
};

class ShowPopupMenu {
public:
    using Arguments = std::tuple<WebCore::IntRect, uint64_t, Vector<WebKit::WebPopupItem>, int32_t, WebKit::PlatformPopupMenuData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowPopupMenu; }
    static constexpr bool isSync = false;

    ShowPopupMenu(const WebCore::IntRect& rect, uint64_t textDirection, const Vector<WebKit::WebPopupItem>& items, int32_t selectedIndex, const WebKit::PlatformPopupMenuData& data)
        : m_arguments(rect, textDirection, items, selectedIndex, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&, uint64_t, const Vector<WebKit::WebPopupItem>&, int32_t, const WebKit::PlatformPopupMenuData&> m_arguments;
};

class HidePopupMenu {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HidePopupMenu; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if ENABLE(CONTEXT_MENUS)
class ShowContextMenu {
public:
    using Arguments = std::tuple<WebKit::ContextMenuContextData, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowContextMenu; }
    static constexpr bool isSync = false;

    ShowContextMenu(const WebKit::ContextMenuContextData& contextMenuContextData, const WebKit::UserData& userData)
        : m_arguments(contextMenuContextData, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ContextMenuContextData&, const WebKit::UserData&> m_arguments;
};
#endif

#if ENABLE(SERVICE_WORKER)
class DidFinishServiceWorkerPageRegistration {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFinishServiceWorkerPageRegistration; }
    static constexpr bool isSync = false;

    explicit DidFinishServiceWorkerPageRegistration(bool success)
        : m_arguments(success)
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

class ExceededDatabaseQuota {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, String, String, String, uint64_t, uint64_t, uint64_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ExceededDatabaseQuota; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    ExceededDatabaseQuota(const WebCore::FrameIdentifier& frameID, const String& originIdentifier, const String& databaseName, const String& databaseDisplayName, uint64_t currentQuota, uint64_t currentOriginUsage, uint64_t currentDatabaseUsage, uint64_t expectedUsage)
        : m_arguments(frameID, originIdentifier, databaseName, databaseDisplayName, currentQuota, currentOriginUsage, currentDatabaseUsage, expectedUsage)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const String&, const String&, const String&, uint64_t, uint64_t, uint64_t, uint64_t> m_arguments;
};

class ReachedApplicationCacheOriginQuota {
public:
    using Arguments = std::tuple<String, uint64_t, uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ReachedApplicationCacheOriginQuota; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    ReachedApplicationCacheOriginQuota(const String& originIdentifier, uint64_t currentQuota, uint64_t totalBytesNeeded)
        : m_arguments(originIdentifier, currentQuota, totalBytesNeeded)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, uint64_t, uint64_t> m_arguments;
};

class RequestGeolocationPermissionForFrame {
public:
    using Arguments = std::tuple<WebKit::GeolocationIdentifier, WebKit::FrameInfoData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestGeolocationPermissionForFrame; }
    static constexpr bool isSync = false;

    RequestGeolocationPermissionForFrame(const WebKit::GeolocationIdentifier& geolocationID, const WebKit::FrameInfoData& frameInfo)
        : m_arguments(geolocationID, frameInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::GeolocationIdentifier&, const WebKit::FrameInfoData&> m_arguments;
};

class RevokeGeolocationAuthorizationToken {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RevokeGeolocationAuthorizationToken; }
    static constexpr bool isSync = false;

    explicit RevokeGeolocationAuthorizationToken(const String& authorizationToken)
        : m_arguments(authorizationToken)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

#if ENABLE(MEDIA_STREAM)
class RequestUserMediaPermissionForFrame {
public:
    using Arguments = std::tuple<WebCore::UserMediaRequestIdentifier, WebCore::FrameIdentifier, WebCore::SecurityOriginData, WebCore::SecurityOriginData, WebCore::MediaStreamRequest>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestUserMediaPermissionForFrame; }
    static constexpr bool isSync = false;

    RequestUserMediaPermissionForFrame(const WebCore::UserMediaRequestIdentifier& userMediaID, const WebCore::FrameIdentifier& frameID, const WebCore::SecurityOriginData& userMediaDocumentOriginIdentifier, const WebCore::SecurityOriginData& topLevelDocumentOriginIdentifier, const WebCore::MediaStreamRequest& request)
        : m_arguments(userMediaID, frameID, userMediaDocumentOriginIdentifier, topLevelDocumentOriginIdentifier, request)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::UserMediaRequestIdentifier&, const WebCore::FrameIdentifier&, const WebCore::SecurityOriginData&, const WebCore::SecurityOriginData&, const WebCore::MediaStreamRequest&> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class EnumerateMediaDevicesForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebCore::SecurityOriginData, WebCore::SecurityOriginData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_EnumerateMediaDevicesForFrame; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_EnumerateMediaDevicesForFrameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::CaptureDeviceWithCapabilities>, WebCore::MediaDeviceHashSalts>;
    EnumerateMediaDevicesForFrame(const WebCore::FrameIdentifier& frameID, const WebCore::SecurityOriginData& userMediaDocumentOriginIdentifier, const WebCore::SecurityOriginData& topLevelDocumentOriginIdentifier)
        : m_arguments(frameID, userMediaDocumentOriginIdentifier, topLevelDocumentOriginIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebCore::SecurityOriginData&, const WebCore::SecurityOriginData&> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class BeginMonitoringCaptureDevices {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_BeginMonitoringCaptureDevices; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(ENCRYPTED_MEDIA)
class RequestMediaKeySystemPermissionForFrame {
public:
    using Arguments = std::tuple<WebCore::MediaKeySystemRequestIdentifier, WebCore::FrameIdentifier, WebCore::SecurityOriginData, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestMediaKeySystemPermissionForFrame; }
    static constexpr bool isSync = false;

    RequestMediaKeySystemPermissionForFrame(const WebCore::MediaKeySystemRequestIdentifier& mediaKeySystemID, const WebCore::FrameIdentifier& frameID, const WebCore::SecurityOriginData& topLevelDocumentOriginIdentifier, const String& keySystem)
        : m_arguments(mediaKeySystemID, frameID, topLevelDocumentOriginIdentifier, keySystem)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaKeySystemRequestIdentifier&, const WebCore::FrameIdentifier&, const WebCore::SecurityOriginData&, const String&> m_arguments;
};
#endif

class RequestNotificationPermission {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestNotificationPermission; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_RequestNotificationPermissionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit RequestNotificationPermission(const String& originIdentifier)
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

#if USE(UNIFIED_TEXT_CHECKING)
class CheckTextOfParagraph {
public:
    using Arguments = std::tuple<String, OptionSet<WebCore::TextCheckingType>, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CheckTextOfParagraph; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::TextCheckingResult>>;
    CheckTextOfParagraph(const String& text, const OptionSet<WebCore::TextCheckingType>& checkingTypes, int32_t insertionPoint)
        : m_arguments(text, checkingTypes, insertionPoint)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const OptionSet<WebCore::TextCheckingType>&, int32_t> m_arguments;
};
#endif

class CheckSpellingOfString {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CheckSpellingOfString; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<int32_t, int32_t>;
    explicit CheckSpellingOfString(const String& text)
        : m_arguments(text)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class CheckGrammarOfString {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CheckGrammarOfString; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::GrammarDetail>, int32_t, int32_t>;
    explicit CheckGrammarOfString(const String& text)
        : m_arguments(text)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class SpellingUIIsShowing {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SpellingUIIsShowing; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class UpdateSpellingUIWithMisspelledWord {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_UpdateSpellingUIWithMisspelledWord; }
    static constexpr bool isSync = false;

    explicit UpdateSpellingUIWithMisspelledWord(const String& misspelledWord)
        : m_arguments(misspelledWord)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class UpdateSpellingUIWithGrammarString {
public:
    using Arguments = std::tuple<String, WebCore::GrammarDetail>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_UpdateSpellingUIWithGrammarString; }
    static constexpr bool isSync = false;

    UpdateSpellingUIWithGrammarString(const String& badGrammarPhrase, const WebCore::GrammarDetail& grammarDetail)
        : m_arguments(badGrammarPhrase, grammarDetail)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::GrammarDetail&> m_arguments;
};

class GetGuessesForWord {
public:
    using Arguments = std::tuple<String, String, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_GetGuessesForWord; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    GetGuessesForWord(const String& word, const String& context, int32_t insertionPoint)
        : m_arguments(word, context, insertionPoint)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, int32_t> m_arguments;
};

class LearnWord {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_LearnWord; }
    static constexpr bool isSync = false;

    explicit LearnWord(const String& word)
        : m_arguments(word)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class IgnoreWord {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_IgnoreWord; }
    static constexpr bool isSync = false;

    explicit IgnoreWord(const String& word)
        : m_arguments(word)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class RequestCheckingOfString {
public:
    using Arguments = std::tuple<WebKit::TextCheckerRequestID, WebCore::TextCheckingRequestData, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestCheckingOfString; }
    static constexpr bool isSync = false;

    RequestCheckingOfString(const WebKit::TextCheckerRequestID& requestID, const WebCore::TextCheckingRequestData& request, int32_t insertionPoint)
        : m_arguments(requestID, request, insertionPoint)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TextCheckerRequestID&, const WebCore::TextCheckingRequestData&, int32_t> m_arguments;
};

#if ENABLE(DRAG_SUPPORT)
class DidPerformDragControllerAction {
public:
    using Arguments = std::tuple<std::optional<WebCore::DragOperation>, WebCore::DragHandlingMethod, bool, unsigned, WebCore::IntRect, WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidPerformDragControllerAction; }
    static constexpr bool isSync = false;

    DidPerformDragControllerAction(const std::optional<WebCore::DragOperation>& dragOperation, WebCore::DragHandlingMethod dragHandlingMethod, bool mouseIsOverFileInput, const unsigned& numberOfItemsToBeAccepted, const WebCore::IntRect& insertionRect, const WebCore::IntRect& editableElementRect)
        : m_arguments(dragOperation, dragHandlingMethod, mouseIsOverFileInput, numberOfItemsToBeAccepted, insertionRect, editableElementRect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::DragOperation>&, WebCore::DragHandlingMethod, bool, const unsigned&, const WebCore::IntRect&, const WebCore::IntRect&> m_arguments;
};
#endif

#if ENABLE(DRAG_SUPPORT)
class DidEndDragging {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidEndDragging; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(COCOA) && ENABLE(DRAG_SUPPORT)
class StartDrag {
public:
    using Arguments = std::tuple<WebCore::DragItem, WebKit::ShareableBitmap::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_StartDrag; }
    static constexpr bool isSync = false;

    StartDrag(const WebCore::DragItem& dragItem, WebKit::ShareableBitmap::Handle&& dragImage)
        : m_arguments(dragItem, WTFMove(dragImage))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DragItem&, WebKit::ShareableBitmap::Handle&&> m_arguments;
};
#endif

#if PLATFORM(COCOA) && ENABLE(DRAG_SUPPORT)
class SetPromisedDataForImage {
public:
    using Arguments = std::tuple<String, WebKit::SharedMemory::Handle, String, String, String, String, String, WebKit::SharedMemory::Handle, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetPromisedDataForImage; }
    static constexpr bool isSync = false;

    SetPromisedDataForImage(const String& pasteboardName, WebKit::SharedMemory::Handle&& imageHandle, const String& filename, const String& extension, const String& title, const String& url, const String& visibleURL, WebKit::SharedMemory::Handle&& archiveHandle, const String& originIdentifier)
        : m_arguments(pasteboardName, WTFMove(imageHandle), filename, extension, title, url, visibleURL, WTFMove(archiveHandle), originIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, WebKit::SharedMemory::Handle&&, const String&, const String&, const String&, const String&, const String&, WebKit::SharedMemory::Handle&&, const String&> m_arguments;
};
#endif

#if PLATFORM(GTK) && ENABLE(DRAG_SUPPORT)
class StartDrag {
public:
    using Arguments = std::tuple<WebCore::SelectionData, OptionSet<WebCore::DragOperation>, WebKit::ShareableBitmap::Handle, WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_StartDrag; }
    static constexpr bool isSync = false;

    StartDrag(const WebCore::SelectionData& selectionData, const OptionSet<WebCore::DragOperation>& dragOperationMask, WebKit::ShareableBitmap::Handle&& dragImage, const WebCore::IntPoint& dragImageHotspot)
        : m_arguments(selectionData, dragOperationMask, WTFMove(dragImage), dragImageHotspot)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SelectionData&, const OptionSet<WebCore::DragOperation>&, WebKit::ShareableBitmap::Handle&&, const WebCore::IntPoint&> m_arguments;
};
#endif

#if ENABLE(DRAG_SUPPORT)
class DidPerformDragOperation {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidPerformDragOperation; }
    static constexpr bool isSync = false;

    explicit DidPerformDragOperation(bool handled)
        : m_arguments(handled)
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

#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
class DidHandleDragStartRequest {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidHandleDragStartRequest; }
    static constexpr bool isSync = false;

    explicit DidHandleDragStartRequest(bool started)
        : m_arguments(started)
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

#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
class DidHandleAdditionalDragItemsRequest {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidHandleAdditionalDragItemsRequest; }
    static constexpr bool isSync = false;

    explicit DidHandleAdditionalDragItemsRequest(bool added)
        : m_arguments(added)
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

#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
class WillReceiveEditDragSnapshot {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_WillReceiveEditDragSnapshot; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
class DidReceiveEditDragSnapshot {
public:
    using Arguments = std::tuple<std::optional<WebCore::TextIndicatorData>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidReceiveEditDragSnapshot; }
    static constexpr bool isSync = false;

    explicit DidReceiveEditDragSnapshot(const std::optional<WebCore::TextIndicatorData>& textIndicator)
        : m_arguments(textIndicator)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::TextIndicatorData>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class DidPerformDictionaryLookup {
public:
    using Arguments = std::tuple<WebCore::DictionaryPopupInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidPerformDictionaryLookup; }
    static constexpr bool isSync = false;

    explicit DidPerformDictionaryLookup(const WebCore::DictionaryPopupInfo& dictionaryPopupInfo)
        : m_arguments(dictionaryPopupInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DictionaryPopupInfo&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class ExecuteSavedCommandBySelector {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ExecuteSavedCommandBySelector; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit ExecuteSavedCommandBySelector(const String& selector)
        : m_arguments(selector)
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

#if PLATFORM(COCOA)
class RegisterWebProcessAccessibilityToken {
public:
    using Arguments = std::tuple<IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RegisterWebProcessAccessibilityToken; }
    static constexpr bool isSync = false;

    explicit RegisterWebProcessAccessibilityToken(const IPC::DataReference& data)
        : m_arguments(data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::DataReference&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetIsSpeaking {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_GetIsSpeaking; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class Speak {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_Speak; }
    static constexpr bool isSync = false;

    explicit Speak(const String& string)
        : m_arguments(string)
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

#if PLATFORM(COCOA)
class StopSpeaking {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_StopSpeaking; }
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
class MakeFirstResponder {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_MakeFirstResponder; }
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
class AssistiveTechnologyMakeFirstResponder {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_AssistiveTechnologyMakeFirstResponder; }
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
class SearchWithSpotlight {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SearchWithSpotlight; }
    static constexpr bool isSync = false;

    explicit SearchWithSpotlight(const String& string)
        : m_arguments(string)
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

#if PLATFORM(COCOA)
class SearchTheWeb {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SearchTheWeb; }
    static constexpr bool isSync = false;

    explicit SearchTheWeb(const String& string)
        : m_arguments(string)
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

#if HAVE(TOUCH_BAR)
class TouchBarMenuDataChanged {
public:
    using Arguments = std::tuple<WebKit::TouchBarMenuData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_TouchBarMenuDataChanged; }
    static constexpr bool isSync = false;

    explicit TouchBarMenuDataChanged(const WebKit::TouchBarMenuData& touchBarMenuData)
        : m_arguments(touchBarMenuData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TouchBarMenuData&> m_arguments;
};
#endif

#if HAVE(TOUCH_BAR)
class TouchBarMenuItemDataAdded {
public:
    using Arguments = std::tuple<WebKit::TouchBarMenuItemData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_TouchBarMenuItemDataAdded; }
    static constexpr bool isSync = false;

    explicit TouchBarMenuItemDataAdded(const WebKit::TouchBarMenuItemData& touchBarMenuItemData)
        : m_arguments(touchBarMenuItemData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TouchBarMenuItemData&> m_arguments;
};
#endif

#if HAVE(TOUCH_BAR)
class TouchBarMenuItemDataRemoved {
public:
    using Arguments = std::tuple<WebKit::TouchBarMenuItemData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_TouchBarMenuItemDataRemoved; }
    static constexpr bool isSync = false;

    explicit TouchBarMenuItemDataRemoved(const WebKit::TouchBarMenuItemData& touchBarMenuItemData)
        : m_arguments(touchBarMenuItemData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TouchBarMenuItemData&> m_arguments;
};
#endif

#if USE(APPKIT)
class SubstitutionsPanelIsShowing {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SubstitutionsPanelIsShowing; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(AUTOMATIC_TEXT_REPLACEMENT)
class toggleSmartInsertDelete {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_toggleSmartInsertDelete; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(AUTOMATIC_TEXT_REPLACEMENT)
class toggleAutomaticQuoteSubstitution {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_toggleAutomaticQuoteSubstitution; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(AUTOMATIC_TEXT_REPLACEMENT)
class toggleAutomaticLinkDetection {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_toggleAutomaticLinkDetection; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(AUTOMATIC_TEXT_REPLACEMENT)
class toggleAutomaticDashSubstitution {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_toggleAutomaticDashSubstitution; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(AUTOMATIC_TEXT_REPLACEMENT)
class toggleAutomaticTextReplacement {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_toggleAutomaticTextReplacement; }
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
class ShowCorrectionPanel {
public:
    using Arguments = std::tuple<WebCore::AlternativeTextType, WebCore::FloatRect, String, String, Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowCorrectionPanel; }
    static constexpr bool isSync = false;

    ShowCorrectionPanel(WebCore::AlternativeTextType panelType, const WebCore::FloatRect& boundingBoxOfReplacedString, const String& replacedString, const String& replacementString, const Vector<String>& alternativeReplacementStrings)
        : m_arguments(panelType, boundingBoxOfReplacedString, replacedString, replacementString, alternativeReplacementStrings)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::AlternativeTextType, const WebCore::FloatRect&, const String&, const String&, const Vector<String>&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class DismissCorrectionPanel {
public:
    using Arguments = std::tuple<WebCore::ReasonForDismissingAlternativeText>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DismissCorrectionPanel; }
    static constexpr bool isSync = false;

    explicit DismissCorrectionPanel(WebCore::ReasonForDismissingAlternativeText reason)
        : m_arguments(reason)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::ReasonForDismissingAlternativeText> m_arguments;
};
#endif

#if PLATFORM(MAC)
class DismissCorrectionPanelSoon {
public:
    using Arguments = std::tuple<WebCore::ReasonForDismissingAlternativeText>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DismissCorrectionPanelSoon; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit DismissCorrectionPanelSoon(WebCore::ReasonForDismissingAlternativeText reason)
        : m_arguments(reason)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::ReasonForDismissingAlternativeText> m_arguments;
};
#endif

#if PLATFORM(MAC)
class RecordAutocorrectionResponse {
public:
    using Arguments = std::tuple<WebCore::AutocorrectionResponse, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RecordAutocorrectionResponse; }
    static constexpr bool isSync = false;

    RecordAutocorrectionResponse(WebCore::AutocorrectionResponse response, const String& replacedString, const String& replacementString)
        : m_arguments(response, replacedString, replacementString)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::AutocorrectionResponse, const String&, const String&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class SetEditableElementIsFocused {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetEditableElementIsFocused; }
    static constexpr bool isSync = false;

    explicit SetEditableElementIsFocused(bool editableElementIsFocused)
        : m_arguments(editableElementIsFocused)
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
class HandleAcceptsFirstMouse {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleAcceptsFirstMouse; }
    static constexpr bool isSync = false;

    explicit HandleAcceptsFirstMouse(bool acceptsFirstMouse)
        : m_arguments(acceptsFirstMouse)
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

class DidUpdateRenderingAfterCommittingLoad {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidUpdateRenderingAfterCommittingLoad; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if USE(DICTATION_ALTERNATIVES)
class ShowDictationAlternativeUI {
public:
    using Arguments = std::tuple<WebCore::FloatRect, WebCore::DictationContext>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowDictationAlternativeUI; }
    static constexpr bool isSync = false;

    ShowDictationAlternativeUI(const WebCore::FloatRect& boundingBoxOfDictatedText, const WebCore::DictationContext& dictationContext)
        : m_arguments(boundingBoxOfDictatedText, dictationContext)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&, const WebCore::DictationContext&> m_arguments;
};
#endif

#if USE(DICTATION_ALTERNATIVES)
class RemoveDictationAlternatives {
public:
    using Arguments = std::tuple<WebCore::DictationContext>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RemoveDictationAlternatives; }
    static constexpr bool isSync = false;

    explicit RemoveDictationAlternatives(const WebCore::DictationContext& dictationContext)
        : m_arguments(dictationContext)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DictationContext&> m_arguments;
};
#endif

#if USE(DICTATION_ALTERNATIVES)
class DictationAlternatives {
public:
    using Arguments = std::tuple<WebCore::DictationContext>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DictationAlternatives; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<String>>;
    explicit DictationAlternatives(const WebCore::DictationContext& dictationContext)
        : m_arguments(dictationContext)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::DictationContext&> m_arguments;
};
#endif

#if ENABLE(VIDEO)
class BeginTextRecognitionForVideoInElementFullScreen {
public:
    using Arguments = std::tuple<WebCore::MediaPlayerIdentifier, WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_BeginTextRecognitionForVideoInElementFullScreen; }
    static constexpr bool isSync = false;

    BeginTextRecognitionForVideoInElementFullScreen(const WebCore::MediaPlayerIdentifier& identifier, const WebCore::FloatRect& videoBounds)
        : m_arguments(identifier, videoBounds)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaPlayerIdentifier&, const WebCore::FloatRect&> m_arguments;
};
#endif

#if ENABLE(VIDEO)
class CancelTextRecognitionForVideoInElementFullScreen {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CancelTextRecognitionForVideoInElementFullScreen; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class CouldNotRestorePageState {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CouldNotRestorePageState; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class RestorePageState {
public:
    using Arguments = std::tuple<std::optional<WebCore::FloatPoint>, WebCore::FloatPoint, WebCore::RectEdges<float>, double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RestorePageState; }
    static constexpr bool isSync = false;

    RestorePageState(const std::optional<WebCore::FloatPoint>& scrollPosition, const WebCore::FloatPoint& scrollOrigin, const WebCore::RectEdges<float>& obscuredInsetsOnSave, double scale)
        : m_arguments(scrollPosition, scrollOrigin, obscuredInsetsOnSave, scale)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::FloatPoint>&, const WebCore::FloatPoint&, const WebCore::RectEdges<float>&, double> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class RestorePageCenterAndScale {
public:
    using Arguments = std::tuple<std::optional<WebCore::FloatPoint>, double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RestorePageCenterAndScale; }
    static constexpr bool isSync = false;

    RestorePageCenterAndScale(const std::optional<WebCore::FloatPoint>& unobscuredCenter, double scale)
        : m_arguments(unobscuredCenter, scale)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::FloatPoint>&, double> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class DidGetTapHighlightGeometries {
public:
    using Arguments = std::tuple<WebKit::TapIdentifier, WebCore::Color, Vector<WebCore::FloatQuad>, WebCore::IntSize, WebCore::IntSize, WebCore::IntSize, WebCore::IntSize, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidGetTapHighlightGeometries; }
    static constexpr bool isSync = false;

    DidGetTapHighlightGeometries(const WebKit::TapIdentifier& requestID, const WebCore::Color& color, const Vector<WebCore::FloatQuad>& geometries, const WebCore::IntSize& topLeftRadius, const WebCore::IntSize& topRightRadius, const WebCore::IntSize& bottomLeftRadius, const WebCore::IntSize& bottomRightRadius, bool nodeHasBuiltInClickHandling)
        : m_arguments(requestID, color, geometries, topLeftRadius, topRightRadius, bottomLeftRadius, bottomRightRadius, nodeHasBuiltInClickHandling)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TapIdentifier&, const WebCore::Color&, const Vector<WebCore::FloatQuad>&, const WebCore::IntSize&, const WebCore::IntSize&, const WebCore::IntSize&, const WebCore::IntSize&, bool> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class ElementDidFocus {
public:
    using Arguments = std::tuple<WebKit::FocusedElementInformation, bool, bool, OptionSet<WebCore::ActivityState>, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ElementDidFocus; }
    static constexpr bool isSync = false;

    ElementDidFocus(const WebKit::FocusedElementInformation& information, bool userIsInteracting, bool blurPreviousNode, const OptionSet<WebCore::ActivityState>& activityStateChanges, const WebKit::UserData& userData)
        : m_arguments(information, userIsInteracting, blurPreviousNode, activityStateChanges, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::FocusedElementInformation&, bool, bool, const OptionSet<WebCore::ActivityState>&, const WebKit::UserData&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class ElementDidBlur {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ElementDidBlur; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class UpdateInputContextAfterBlurringAndRefocusingElement {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_UpdateInputContextAfterBlurringAndRefocusingElement; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class FocusedElementDidChangeInputMode {
public:
    using Arguments = std::tuple<WebCore::InputMode>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_FocusedElementDidChangeInputMode; }
    static constexpr bool isSync = false;

    explicit FocusedElementDidChangeInputMode(WebCore::InputMode mode)
        : m_arguments(mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::InputMode> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class ScrollingNodeScrollWillStartScroll {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ScrollingNodeScrollWillStartScroll; }
    static constexpr bool isSync = false;

    explicit ScrollingNodeScrollWillStartScroll(uint64_t nodeID)
        : m_arguments(nodeID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class ScrollingNodeScrollDidEndScroll {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ScrollingNodeScrollDidEndScroll; }
    static constexpr bool isSync = false;

    explicit ScrollingNodeScrollDidEndScroll(uint64_t nodeID)
        : m_arguments(nodeID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class ShowInspectorHighlight {
public:
    using Arguments = std::tuple<WebCore::InspectorOverlay::Highlight>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowInspectorHighlight; }
    static constexpr bool isSync = false;

    explicit ShowInspectorHighlight(const WebCore::InspectorOverlay::Highlight& highlight)
        : m_arguments(highlight)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::InspectorOverlay::Highlight&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class HideInspectorHighlight {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HideInspectorHighlight; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class ShowInspectorIndication {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowInspectorIndication; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class HideInspectorIndication {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HideInspectorIndication; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class EnableInspectorNodeSearch {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_EnableInspectorNodeSearch; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class DisableInspectorNodeSearch {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DisableInspectorNodeSearch; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class UpdateStringForFind {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_UpdateStringForFind; }
    static constexpr bool isSync = false;

    explicit UpdateStringForFind(const String& findString)
        : m_arguments(findString)
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

#if PLATFORM(IOS_FAMILY)
class HandleAutocorrectionContext {
public:
    using Arguments = std::tuple<WebKit::WebAutocorrectionContext>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleAutocorrectionContext; }
    static constexpr bool isSync = false;

    explicit HandleAutocorrectionContext(const WebKit::WebAutocorrectionContext& context)
        : m_arguments(context)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebAutocorrectionContext&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class ShowDataDetectorsUIForPositionInformation {
public:
    using Arguments = std::tuple<WebKit::InteractionInformationAtPosition>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowDataDetectorsUIForPositionInformation; }
    static constexpr bool isSync = false;

    explicit ShowDataDetectorsUIForPositionInformation(const WebKit::InteractionInformationAtPosition& information)
        : m_arguments(information)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::InteractionInformationAtPosition&> m_arguments;
};
#endif

class DidChangeInspectorFrontendCount {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidChangeInspectorFrontendCount; }
    static constexpr bool isSync = false;

    explicit DidChangeInspectorFrontendCount(uint32_t count)
        : m_arguments(count)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class CreateInspectorTarget {
public:
    using Arguments = std::tuple<String, Inspector::InspectorTargetType>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CreateInspectorTarget; }
    static constexpr bool isSync = false;

    CreateInspectorTarget(const String& targetId, Inspector::InspectorTargetType type)
        : m_arguments(targetId, type)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, Inspector::InspectorTargetType> m_arguments;
};

class DestroyInspectorTarget {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DestroyInspectorTarget; }
    static constexpr bool isSync = false;

    explicit DestroyInspectorTarget(const String& targetId)
        : m_arguments(targetId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class SendMessageToInspectorFrontend {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SendMessageToInspectorFrontend; }
    static constexpr bool isSync = false;

    SendMessageToInspectorFrontend(const String& targetId, const String& message)
        : m_arguments(targetId, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&> m_arguments;
};

class SaveRecentSearches {
public:
    using Arguments = std::tuple<String, Vector<WebCore::RecentSearch>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SaveRecentSearches; }
    static constexpr bool isSync = false;

    SaveRecentSearches(const String& name, const Vector<WebCore::RecentSearch>& searchItems)
        : m_arguments(name, searchItems)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const Vector<WebCore::RecentSearch>&> m_arguments;
};

class LoadRecentSearches {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_LoadRecentSearches; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::RecentSearch>>;
    explicit LoadRecentSearches(const String& name)
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

#if ENABLE(PDFKIT_PLUGIN)
class ShowPDFContextMenu {
public:
    using Arguments = std::tuple<WebKit::PDFContextMenu, WebKit::PDFPluginIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowPDFContextMenu; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<int32_t>>;
    ShowPDFContextMenu(const WebKit::PDFContextMenu& contextMenu, const WebKit::PDFPluginIdentifier& identifier)
        : m_arguments(contextMenu, identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::PDFContextMenu&, const WebKit::PDFPluginIdentifier&> m_arguments;
};
#endif

class DidUpdateActivityState {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidUpdateActivityState; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if ENABLE(WEB_CRYPTO)
class WrapCryptoKey {
public:
    using Arguments = std::tuple<Vector<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_WrapCryptoKey; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool, Vector<uint8_t>>;
    explicit WrapCryptoKey(const Vector<uint8_t>& key)
        : m_arguments(key)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<uint8_t>&> m_arguments;
};
#endif

#if ENABLE(WEB_CRYPTO)
class UnwrapCryptoKey {
public:
    using Arguments = std::tuple<Vector<uint8_t>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_UnwrapCryptoKey; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool, Vector<uint8_t>>;
    explicit UnwrapCryptoKey(const Vector<uint8_t>& wrappedKey)
        : m_arguments(wrappedKey)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<uint8_t>&> m_arguments;
};
#endif

#if (ENABLE(TELEPHONE_NUMBER_DETECTION) && PLATFORM(MAC))
class ShowTelephoneNumberMenu {
public:
    using Arguments = std::tuple<String, WebCore::IntPoint, WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowTelephoneNumberMenu; }
    static constexpr bool isSync = false;

    ShowTelephoneNumberMenu(const String& telephoneNumber, const WebCore::IntPoint& point, const WebCore::IntRect& rect)
        : m_arguments(telephoneNumber, point, rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::IntPoint&, const WebCore::IntRect&> m_arguments;
};
#endif

#if USE(QUICK_LOOK)
class DidStartLoadForQuickLookDocumentInMainFrame {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidStartLoadForQuickLookDocumentInMainFrame; }
    static constexpr bool isSync = false;

    DidStartLoadForQuickLookDocumentInMainFrame(const String& fileName, const String& uti)
        : m_arguments(fileName, uti)
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

#if USE(QUICK_LOOK)
class DidFinishLoadForQuickLookDocumentInMainFrame {
public:
    using Arguments = std::tuple<WebKit::ShareableResource::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFinishLoadForQuickLookDocumentInMainFrame; }
    static constexpr bool isSync = false;

    explicit DidFinishLoadForQuickLookDocumentInMainFrame(WebKit::ShareableResource::Handle&& resource)
        : m_arguments(WTFMove(resource))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::ShareableResource::Handle&&> m_arguments;
};
#endif

#if USE(QUICK_LOOK)
class RequestPasswordForQuickLookDocumentInMainFrame {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestPasswordForQuickLookDocumentInMainFrame; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_RequestPasswordForQuickLookDocumentInMainFrameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit RequestPasswordForQuickLookDocumentInMainFrame(const String& fileName)
        : m_arguments(fileName)
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

#if ENABLE(CONTENT_FILTERING)
class ContentFilterDidBlockLoadForFrame {
public:
    using Arguments = std::tuple<WebCore::ContentFilterUnblockHandler, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ContentFilterDidBlockLoadForFrame; }
    static constexpr bool isSync = false;

    ContentFilterDidBlockLoadForFrame(const WebCore::ContentFilterUnblockHandler& unblockHandler, const WebCore::FrameIdentifier& frameID)
        : m_arguments(unblockHandler, frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ContentFilterUnblockHandler&, const WebCore::FrameIdentifier&> m_arguments;
};
#endif

#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
class IsAnyAnimationAllowedToPlayDidChange {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_IsAnyAnimationAllowedToPlayDidChange; }
    static constexpr bool isSync = false;

    explicit IsAnyAnimationAllowedToPlayDidChange(bool anyAnimationCanPlay)
        : m_arguments(anyAnimationCanPlay)
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

class IsPlayingMediaDidChange {
public:
    using Arguments = std::tuple<OptionSet<WebCore::MediaProducerMediaState>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_IsPlayingMediaDidChange; }
    static constexpr bool isSync = false;

    explicit IsPlayingMediaDidChange(const OptionSet<WebCore::MediaProducerMediaState>& state)
        : m_arguments(state)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebCore::MediaProducerMediaState>&> m_arguments;
};

class HandleAutoplayEvent {
public:
    using Arguments = std::tuple<WebCore::AutoplayEvent, OptionSet<WebCore::AutoplayEventFlags>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleAutoplayEvent; }
    static constexpr bool isSync = false;

    HandleAutoplayEvent(WebCore::AutoplayEvent event, const OptionSet<WebCore::AutoplayEventFlags>& flags)
        : m_arguments(event, flags)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::AutoplayEvent, const OptionSet<WebCore::AutoplayEventFlags>&> m_arguments;
};

#if PLATFORM(MAC)
class DidPerformImmediateActionHitTest {
public:
    using Arguments = std::tuple<WebKit::WebHitTestResultData, bool, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidPerformImmediateActionHitTest; }
    static constexpr bool isSync = false;

    DidPerformImmediateActionHitTest(const WebKit::WebHitTestResultData& result, bool contentPreventsDefault, const WebKit::UserData& userData)
        : m_arguments(result, contentPreventsDefault, userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebHitTestResultData&, bool, const WebKit::UserData&> m_arguments;
};
#endif

class HandleMessage {
public:
    using Arguments = std::tuple<String, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleMessage; }
    static constexpr bool isSync = false;

    HandleMessage(const String& messageName, const WebKit::UserData& messageBody)
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

class HandleSynchronousMessage {
public:
    using Arguments = std::tuple<String, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleSynchronousMessage; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::UserData>;
    HandleSynchronousMessage(const String& messageName, const WebKit::UserData& messageBody)
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

class HandleAutoFillButtonClick {
public:
    using Arguments = std::tuple<WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleAutoFillButtonClick; }
    static constexpr bool isSync = false;

    explicit HandleAutoFillButtonClick(const WebKit::UserData& userData)
        : m_arguments(userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::UserData&> m_arguments;
};

class DidResignInputElementStrongPasswordAppearance {
public:
    using Arguments = std::tuple<WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidResignInputElementStrongPasswordAppearance; }
    static constexpr bool isSync = false;

    explicit DidResignInputElementStrongPasswordAppearance(const WebKit::UserData& userData)
        : m_arguments(userData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::UserData&> m_arguments;
};

#if ENABLE(CONTENT_EXTENSIONS)
class ContentRuleListNotification {
public:
    using Arguments = std::tuple<URL, WebCore::ContentRuleListResults>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ContentRuleListNotification; }
    static constexpr bool isSync = false;

    ContentRuleListNotification(const URL& url, const WebCore::ContentRuleListResults& results)
        : m_arguments(url, results)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const WebCore::ContentRuleListResults&> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
class AddPlaybackTargetPickerClient {
public:
    using Arguments = std::tuple<WebCore::PlaybackTargetClientContextIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_AddPlaybackTargetPickerClient; }
    static constexpr bool isSync = false;

    explicit AddPlaybackTargetPickerClient(const WebCore::PlaybackTargetClientContextIdentifier& contextId)
        : m_arguments(contextId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlaybackTargetClientContextIdentifier&> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
class RemovePlaybackTargetPickerClient {
public:
    using Arguments = std::tuple<WebCore::PlaybackTargetClientContextIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RemovePlaybackTargetPickerClient; }
    static constexpr bool isSync = false;

    explicit RemovePlaybackTargetPickerClient(const WebCore::PlaybackTargetClientContextIdentifier& contextId)
        : m_arguments(contextId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlaybackTargetClientContextIdentifier&> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
class ShowPlaybackTargetPicker {
public:
    using Arguments = std::tuple<WebCore::PlaybackTargetClientContextIdentifier, WebCore::FloatRect, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowPlaybackTargetPicker; }
    static constexpr bool isSync = false;

    ShowPlaybackTargetPicker(const WebCore::PlaybackTargetClientContextIdentifier& contextId, const WebCore::FloatRect& pickerLocation, bool hasVideo)
        : m_arguments(contextId, pickerLocation, hasVideo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlaybackTargetClientContextIdentifier&, const WebCore::FloatRect&, bool> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
class PlaybackTargetPickerClientStateDidChange {
public:
    using Arguments = std::tuple<WebCore::PlaybackTargetClientContextIdentifier, OptionSet<WebCore::MediaProducerMediaState>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_PlaybackTargetPickerClientStateDidChange; }
    static constexpr bool isSync = false;

    PlaybackTargetPickerClientStateDidChange(const WebCore::PlaybackTargetClientContextIdentifier& contextId, const OptionSet<WebCore::MediaProducerMediaState>& mediaState)
        : m_arguments(contextId, mediaState)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlaybackTargetClientContextIdentifier&, const OptionSet<WebCore::MediaProducerMediaState>&> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
class SetMockMediaPlaybackTargetPickerEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetMockMediaPlaybackTargetPickerEnabled; }
    static constexpr bool isSync = false;

    explicit SetMockMediaPlaybackTargetPickerEnabled(bool enabled)
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
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
class SetMockMediaPlaybackTargetPickerState {
public:
    using Arguments = std::tuple<String, WebCore::MediaPlaybackTargetContext::MockState>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetMockMediaPlaybackTargetPickerState; }
    static constexpr bool isSync = false;

    SetMockMediaPlaybackTargetPickerState(const String& name, WebCore::MediaPlaybackTargetContext::MockState pickerState)
        : m_arguments(name, pickerState)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, WebCore::MediaPlaybackTargetContext::MockState> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
class MockMediaPlaybackTargetPickerDismissPopup {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_MockMediaPlaybackTargetPickerDismissPopup; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(VIDEO_PRESENTATION_MODE)
class SetMockVideoPresentationModeEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetMockVideoPresentationModeEnabled; }
    static constexpr bool isSync = false;

    explicit SetMockVideoPresentationModeEnabled(bool enabled)
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
#endif

#if ENABLE(POINTER_LOCK)
class RequestPointerLock {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestPointerLock; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(POINTER_LOCK)
class RequestPointerUnlock {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestPointerUnlock; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class DidFailToSuspendAfterProcessSwap {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFailToSuspendAfterProcessSwap; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidSuspendAfterProcessSwap {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidSuspendAfterProcessSwap; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ImageOrMediaDocumentSizeChanged {
public:
    using Arguments = std::tuple<WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ImageOrMediaDocumentSizeChanged; }
    static constexpr bool isSync = false;

    explicit ImageOrMediaDocumentSizeChanged(const WebCore::IntSize& newSize)
        : m_arguments(newSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntSize&> m_arguments;
};

class UseFixedLayoutDidChange {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_UseFixedLayoutDidChange; }
    static constexpr bool isSync = false;

    explicit UseFixedLayoutDidChange(bool useFixedLayout)
        : m_arguments(useFixedLayout)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class FixedLayoutSizeDidChange {
public:
    using Arguments = std::tuple<WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_FixedLayoutSizeDidChange; }
    static constexpr bool isSync = false;

    explicit FixedLayoutSizeDidChange(const WebCore::IntSize& fixedLayoutSize)
        : m_arguments(fixedLayoutSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntSize&> m_arguments;
};

class DidRestoreScrollPosition {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidRestoreScrollPosition; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RequestScrollToRect {
public:
    using Arguments = std::tuple<WebCore::FloatRect, WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestScrollToRect; }
    static constexpr bool isSync = false;

    RequestScrollToRect(const WebCore::FloatRect& targetRect, const WebCore::FloatPoint& origin)
        : m_arguments(targetRect, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&, const WebCore::FloatPoint&> m_arguments;
};

class GetLoadDecisionForIcon {
public:
    using Arguments = std::tuple<WebCore::LinkIcon, WebKit::CallbackID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_GetLoadDecisionForIcon; }
    static constexpr bool isSync = false;

    GetLoadDecisionForIcon(const WebCore::LinkIcon& icon, const WebKit::CallbackID& callbackID)
        : m_arguments(icon, callbackID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::LinkIcon&, const WebKit::CallbackID&> m_arguments;
};

#if PLATFORM(MAC)
class DidHandleAcceptedCandidate {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidHandleAcceptedCandidate; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class SetIsUsingHighPerformanceWebGL {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetIsUsingHighPerformanceWebGL; }
    static constexpr bool isSync = false;

    explicit SetIsUsingHighPerformanceWebGL(bool isUsingHighPerformanceWebGL)
        : m_arguments(isUsingHighPerformanceWebGL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class StartURLSchemeTask {
public:
    using Arguments = std::tuple<WebKit::URLSchemeTaskParameters>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_StartURLSchemeTask; }
    static constexpr bool isSync = false;

    explicit StartURLSchemeTask(const WebKit::URLSchemeTaskParameters& parameters)
        : m_arguments(parameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::URLSchemeTaskParameters&> m_arguments;
};

class StopURLSchemeTask {
public:
    using Arguments = std::tuple<WebKit::WebURLSchemeHandlerIdentifier, WebCore::ResourceLoaderIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_StopURLSchemeTask; }
    static constexpr bool isSync = false;

    StopURLSchemeTask(const WebKit::WebURLSchemeHandlerIdentifier& handlerIdentifier, const WebCore::ResourceLoaderIdentifier& taskIdentifier)
        : m_arguments(handlerIdentifier, taskIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebURLSchemeHandlerIdentifier&, const WebCore::ResourceLoaderIdentifier&> m_arguments;
};

class LoadSynchronousURLSchemeTask {
public:
    using Arguments = std::tuple<WebKit::URLSchemeTaskParameters>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_LoadSynchronousURLSchemeTask; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::ResourceResponse, WebCore::ResourceError, Vector<uint8_t>>;
    explicit LoadSynchronousURLSchemeTask(const WebKit::URLSchemeTaskParameters& parameters)
        : m_arguments(parameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::URLSchemeTaskParameters&> m_arguments;
};

#if ENABLE(DEVICE_ORIENTATION)
class ShouldAllowDeviceOrientationAndMotionAccess {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::FrameInfoData, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShouldAllowDeviceOrientationAndMotionAccess; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ShouldAllowDeviceOrientationAndMotionAccessReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::DeviceOrientationOrMotionPermissionState>;
    ShouldAllowDeviceOrientationAndMotionAccess(const WebCore::FrameIdentifier& frameID, const WebKit::FrameInfoData& frameInfo, bool mayPrompt)
        : m_arguments(frameID, frameInfo, mayPrompt)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::FrameInfoData&, bool> m_arguments;
};
#endif

#if ENABLE(ATTACHMENT_ELEMENT)
class RegisterAttachmentIdentifierFromData {
public:
    using Arguments = std::tuple<String, String, String, IPC::SharedBufferReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RegisterAttachmentIdentifierFromData; }
    static constexpr bool isSync = false;

    RegisterAttachmentIdentifierFromData(const String& identifier, const String& contentType, const String& preferredFileName, const IPC::SharedBufferReference& data)
        : m_arguments(identifier, contentType, preferredFileName, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const String&, const IPC::SharedBufferReference&> m_arguments;
};
#endif

#if ENABLE(ATTACHMENT_ELEMENT)
class RegisterAttachmentIdentifierFromFilePath {
public:
    using Arguments = std::tuple<String, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RegisterAttachmentIdentifierFromFilePath; }
    static constexpr bool isSync = false;

    RegisterAttachmentIdentifierFromFilePath(const String& identifier, const String& contentType, const String& filePath)
        : m_arguments(identifier, contentType, filePath)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const String&> m_arguments;
};
#endif

#if ENABLE(ATTACHMENT_ELEMENT)
class RegisterAttachmentIdentifier {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RegisterAttachmentIdentifier; }
    static constexpr bool isSync = false;

    explicit RegisterAttachmentIdentifier(const String& identifier)
        : m_arguments(identifier)
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

#if ENABLE(ATTACHMENT_ELEMENT)
class RegisterAttachmentsFromSerializedData {
public:
    using Arguments = std::tuple<Vector<WebCore::SerializedAttachmentData>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RegisterAttachmentsFromSerializedData; }
    static constexpr bool isSync = false;

    explicit RegisterAttachmentsFromSerializedData(const Vector<WebCore::SerializedAttachmentData>& data)
        : m_arguments(data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::SerializedAttachmentData>&> m_arguments;
};
#endif

#if ENABLE(ATTACHMENT_ELEMENT)
class CloneAttachmentData {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CloneAttachmentData; }
    static constexpr bool isSync = false;

    CloneAttachmentData(const String& fromIdentifier, const String& toIdentifier)
        : m_arguments(fromIdentifier, toIdentifier)
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

#if ENABLE(ATTACHMENT_ELEMENT)
class DidInsertAttachmentWithIdentifier {
public:
    using Arguments = std::tuple<String, String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidInsertAttachmentWithIdentifier; }
    static constexpr bool isSync = false;

    DidInsertAttachmentWithIdentifier(const String& identifier, const String& source, bool hasEnclosingImage)
        : m_arguments(identifier, source, hasEnclosingImage)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, bool> m_arguments;
};
#endif

#if ENABLE(ATTACHMENT_ELEMENT)
class DidRemoveAttachmentWithIdentifier {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidRemoveAttachmentWithIdentifier; }
    static constexpr bool isSync = false;

    explicit DidRemoveAttachmentWithIdentifier(const String& identifier)
        : m_arguments(identifier)
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

#if ENABLE(ATTACHMENT_ELEMENT)
class SerializedAttachmentDataForIdentifiers {
public:
    using Arguments = std::tuple<Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SerializedAttachmentDataForIdentifiers; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::SerializedAttachmentData>>;
    explicit SerializedAttachmentDataForIdentifiers(const Vector<String>& identifiers)
        : m_arguments(identifiers)
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

#if (ENABLE(ATTACHMENT_ELEMENT) && PLATFORM(IOS_FAMILY))
class WritePromisedAttachmentToPasteboard {
public:
    using Arguments = std::tuple<WebCore::PromisedAttachmentInfo, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_WritePromisedAttachmentToPasteboard; }
    static constexpr bool isSync = false;

    WritePromisedAttachmentToPasteboard(const WebCore::PromisedAttachmentInfo& info, const String& authorizationToken)
        : m_arguments(info, authorizationToken)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PromisedAttachmentInfo&, const String&> m_arguments;
};
#endif

#if ENABLE(ATTACHMENT_ELEMENT)
class RequestAttachmentIcon {
public:
    using Arguments = std::tuple<String, String, String, String, WebCore::FloatSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestAttachmentIcon; }
    static constexpr bool isSync = false;

    RequestAttachmentIcon(const String& identifier, const String& contentType, const String& path, const String& title, const WebCore::FloatSize& size)
        : m_arguments(identifier, contentType, path, title, size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, const String&, const String&, const WebCore::FloatSize&> m_arguments;
};
#endif

#if ENABLE(APP_HIGHLIGHTS)
class StoreAppHighlight {
public:
    using Arguments = std::tuple<WebCore::AppHighlight>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_StoreAppHighlight; }
    static constexpr bool isSync = false;

    explicit StoreAppHighlight(const WebCore::AppHighlight& info)
        : m_arguments(info)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::AppHighlight&> m_arguments;
};
#endif

#if ENABLE(SPEECH_SYNTHESIS)
class SpeechSynthesisVoiceList {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SpeechSynthesisVoiceList; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebKit::WebSpeechSynthesisVoice>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(SPEECH_SYNTHESIS)
class SpeechSynthesisSpeak {
public:
    using Arguments = std::tuple<String, String, float, float, float, MonotonicTime, String, String, String, bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SpeechSynthesisSpeak; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_SpeechSynthesisSpeakReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SpeechSynthesisSpeak(const String& text, const String& lang, float volume, float rate, float pitch, const MonotonicTime& startTime, const String& voiceURI, const String& voiceName, const String& voiceLang, bool localService, bool defaultVoice)
        : m_arguments(text, lang, volume, rate, pitch, startTime, voiceURI, voiceName, voiceLang, localService, defaultVoice)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&, float, float, float, const MonotonicTime&, const String&, const String&, const String&, bool, bool> m_arguments;
};
#endif

#if ENABLE(SPEECH_SYNTHESIS)
class SpeechSynthesisSetFinishedCallback {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SpeechSynthesisSetFinishedCallback; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_SpeechSynthesisSetFinishedCallbackReply; }
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

#if ENABLE(SPEECH_SYNTHESIS)
class SpeechSynthesisCancel {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SpeechSynthesisCancel; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(SPEECH_SYNTHESIS)
class SpeechSynthesisPause {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SpeechSynthesisPause; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_SpeechSynthesisPauseReply; }
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

#if ENABLE(SPEECH_SYNTHESIS)
class SpeechSynthesisResume {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SpeechSynthesisResume; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_SpeechSynthesisResumeReply; }
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

#if ENABLE(SPEECH_SYNTHESIS)
class SpeechSynthesisResetState {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SpeechSynthesisResetState; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(PDFKIT_PLUGIN)
class CreatePDFHUD {
public:
    using Arguments = std::tuple<WebKit::PDFPluginIdentifier, WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_CreatePDFHUD; }
    static constexpr bool isSync = false;

    CreatePDFHUD(const WebKit::PDFPluginIdentifier& identifier, const WebCore::IntRect& boundingBox)
        : m_arguments(identifier, boundingBox)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::PDFPluginIdentifier&, const WebCore::IntRect&> m_arguments;
};
#endif

#if ENABLE(PDFKIT_PLUGIN)
class UpdatePDFHUDLocation {
public:
    using Arguments = std::tuple<WebKit::PDFPluginIdentifier, WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_UpdatePDFHUDLocation; }
    static constexpr bool isSync = false;

    UpdatePDFHUDLocation(const WebKit::PDFPluginIdentifier& identifier, const WebCore::IntRect& boundingBox)
        : m_arguments(identifier, boundingBox)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::PDFPluginIdentifier&, const WebCore::IntRect&> m_arguments;
};
#endif

#if ENABLE(PDFKIT_PLUGIN)
class RemovePDFHUD {
public:
    using Arguments = std::tuple<WebKit::PDFPluginIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RemovePDFHUD; }
    static constexpr bool isSync = false;

    explicit RemovePDFHUD(const WebKit::PDFPluginIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::PDFPluginIdentifier&> m_arguments;
};
#endif

class ConfigureLoggingChannel {
public:
    using Arguments = std::tuple<String, WTFLogChannelState, WTFLogLevel>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ConfigureLoggingChannel; }
    static constexpr bool isSync = false;

    ConfigureLoggingChannel(const String& channelName, WTFLogChannelState state, WTFLogLevel level)
        : m_arguments(channelName, state, level)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, WTFLogChannelState, WTFLogLevel> m_arguments;
};

#if PLATFORM(GTK)
class ShowEmojiPicker {
public:
    using Arguments = std::tuple<WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ShowEmojiPicker; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ShowEmojiPickerReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit ShowEmojiPicker(const WebCore::IntRect& caretRect)
        : m_arguments(caretRect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&> m_arguments;
};
#endif

#if HAVE(VISIBILITY_PROPAGATION_VIEW)
class DidCreateContextInWebProcessForVisibilityPropagation {
public:
    using Arguments = std::tuple<WebKit::LayerHostingContextID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidCreateContextInWebProcessForVisibilityPropagation; }
    static constexpr bool isSync = false;

    explicit DidCreateContextInWebProcessForVisibilityPropagation(const WebKit::LayerHostingContextID& contextID)
        : m_arguments(contextID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::LayerHostingContextID&> m_arguments;
};
#endif

#if ENABLE(WEB_AUTHN)
class SetMockWebAuthenticationConfiguration {
public:
    using Arguments = std::tuple<WebCore::MockWebAuthenticationConfiguration>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetMockWebAuthenticationConfiguration; }
    static constexpr bool isSync = false;

    explicit SetMockWebAuthenticationConfiguration(const WebCore::MockWebAuthenticationConfiguration& configuration)
        : m_arguments(configuration)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MockWebAuthenticationConfiguration&> m_arguments;
};
#endif

#if PLATFORM(GTK) || PLATFORM(WPE)
class SendMessageToWebView {
public:
    using Arguments = std::tuple<WebKit::UserMessage>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SendMessageToWebView; }
    static constexpr bool isSync = false;

    explicit SendMessageToWebView(const WebKit::UserMessage& userMessage)
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

#if PLATFORM(GTK) || PLATFORM(WPE)
class SendMessageToWebViewWithReply {
public:
    using Arguments = std::tuple<WebKit::UserMessage>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SendMessageToWebViewWithReply; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_SendMessageToWebViewWithReplyReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::UserMessage>;
    explicit SendMessageToWebViewWithReply(const WebKit::UserMessage& userMessage)
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

class DidFindTextManipulationItems {
public:
    using Arguments = std::tuple<Vector<WebCore::TextManipulationItem>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidFindTextManipulationItems; }
    static constexpr bool isSync = false;

    explicit DidFindTextManipulationItems(const Vector<WebCore::TextManipulationItem>& items)
        : m_arguments(items)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::TextManipulationItem>&> m_arguments;
};

#if ENABLE(MEDIA_USAGE)
class AddMediaUsageManagerSession {
public:
    using Arguments = std::tuple<WebCore::MediaSessionIdentifier, String, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_AddMediaUsageManagerSession; }
    static constexpr bool isSync = false;

    AddMediaUsageManagerSession(const WebCore::MediaSessionIdentifier& identifier, const String& bundleIdentifier, const URL& pageURL)
        : m_arguments(identifier, bundleIdentifier, pageURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaSessionIdentifier&, const String&, const URL&> m_arguments;
};
#endif

#if ENABLE(MEDIA_USAGE)
class UpdateMediaUsageManagerSessionState {
public:
    using Arguments = std::tuple<WebCore::MediaSessionIdentifier, WebCore::MediaUsageInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_UpdateMediaUsageManagerSessionState; }
    static constexpr bool isSync = false;

    UpdateMediaUsageManagerSessionState(const WebCore::MediaSessionIdentifier& identifier, const WebCore::MediaUsageInfo& info)
        : m_arguments(identifier, info)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaSessionIdentifier&, const WebCore::MediaUsageInfo&> m_arguments;
};
#endif

#if ENABLE(MEDIA_USAGE)
class RemoveMediaUsageManagerSession {
public:
    using Arguments = std::tuple<WebCore::MediaSessionIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RemoveMediaUsageManagerSession; }
    static constexpr bool isSync = false;

    explicit RemoveMediaUsageManagerSession(const WebCore::MediaSessionIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaSessionIdentifier&> m_arguments;
};
#endif

class SetHasExecutedAppBoundBehaviorBeforeNavigation {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_SetHasExecutedAppBoundBehaviorBeforeNavigation; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if PLATFORM(MAC)
class ChangeUniversalAccessZoomFocus {
public:
    using Arguments = std::tuple<WebCore::IntRect, WebCore::IntRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ChangeUniversalAccessZoomFocus; }
    static constexpr bool isSync = false;

    ChangeUniversalAccessZoomFocus(const WebCore::IntRect& viewRect, const WebCore::IntRect& caretRect)
        : m_arguments(viewRect, caretRect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&, const WebCore::IntRect&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW_IOS)
class TakeModelElementFullscreen {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_TakeModelElementFullscreen; }
    static constexpr bool isSync = false;

    explicit TakeModelElementFullscreen(const WebKit::ModelIdentifier& modelIdentifier)
        : m_arguments(modelIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW_IOS)
class ModelElementSetInteractionEnabled {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementSetInteractionEnabled; }
    static constexpr bool isSync = false;

    ModelElementSetInteractionEnabled(const WebKit::ModelIdentifier& modelIdentifier, bool isInteractionEnabled)
        : m_arguments(modelIdentifier, isInteractionEnabled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&, bool> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
class ModelElementCreateRemotePreview {
public:
    using Arguments = std::tuple<String, WebCore::FloatSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementCreateRemotePreview; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementCreateRemotePreviewReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<std::pair<String, uint32_t>, WebCore::ResourceError>>;
    ModelElementCreateRemotePreview(const String& uuid, const WebCore::FloatSize& size)
        : m_arguments(uuid, size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::FloatSize&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
class ModelElementLoadRemotePreview {
public:
    using Arguments = std::tuple<String, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementLoadRemotePreview; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementLoadRemotePreviewReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ResourceError>>;
    ModelElementLoadRemotePreview(const String& uuid, const URL& url)
        : m_arguments(uuid, url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const URL&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
class ModelElementDestroyRemotePreview {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementDestroyRemotePreview; }
    static constexpr bool isSync = false;

    explicit ModelElementDestroyRemotePreview(const String& uuid)
        : m_arguments(uuid)
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

#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
class ModelElementSizeDidChange {
public:
    using Arguments = std::tuple<String, WebCore::FloatSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementSizeDidChange; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementSizeDidChangeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<MachSendRight, WebCore::ResourceError>>;
    ModelElementSizeDidChange(const String& uuid, const WebCore::FloatSize& size)
        : m_arguments(uuid, size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::FloatSize&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
class HandleMouseDownForModelElement {
public:
    using Arguments = std::tuple<String, WebCore::LayoutPoint, MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleMouseDownForModelElement; }
    static constexpr bool isSync = false;

    HandleMouseDownForModelElement(const String& uuid, const WebCore::LayoutPoint& flippedLocationInElement, const MonotonicTime& timestamp)
        : m_arguments(uuid, flippedLocationInElement, timestamp)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::LayoutPoint&, const MonotonicTime&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
class HandleMouseMoveForModelElement {
public:
    using Arguments = std::tuple<String, WebCore::LayoutPoint, MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleMouseMoveForModelElement; }
    static constexpr bool isSync = false;

    HandleMouseMoveForModelElement(const String& uuid, const WebCore::LayoutPoint& flippedLocationInElement, const MonotonicTime& timestamp)
        : m_arguments(uuid, flippedLocationInElement, timestamp)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::LayoutPoint&, const MonotonicTime&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
class HandleMouseUpForModelElement {
public:
    using Arguments = std::tuple<String, WebCore::LayoutPoint, MonotonicTime>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_HandleMouseUpForModelElement; }
    static constexpr bool isSync = false;

    HandleMouseUpForModelElement(const String& uuid, const WebCore::LayoutPoint& flippedLocationInElement, const MonotonicTime& timestamp)
        : m_arguments(uuid, flippedLocationInElement, timestamp)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::LayoutPoint&, const MonotonicTime&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW_MAC)
class ModelInlinePreviewUUIDs {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelInlinePreviewUUIDs; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelInlinePreviewUUIDsReply; }
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

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementGetCamera {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementGetCamera; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementGetCameraReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<WebCore::HTMLModelElementCamera, WebCore::ResourceError>>;
    explicit ModelElementGetCamera(const WebKit::ModelIdentifier& modelIdentifier)
        : m_arguments(modelIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementSetCamera {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier, WebCore::HTMLModelElementCamera>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementSetCamera; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementSetCameraReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    ModelElementSetCamera(const WebKit::ModelIdentifier& modelIdentifier, const WebCore::HTMLModelElementCamera& camera)
        : m_arguments(modelIdentifier, camera)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&, const WebCore::HTMLModelElementCamera&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementIsPlayingAnimation {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementIsPlayingAnimation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementIsPlayingAnimationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<bool, WebCore::ResourceError>>;
    explicit ModelElementIsPlayingAnimation(const WebKit::ModelIdentifier& modelIdentifier)
        : m_arguments(modelIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementSetAnimationIsPlaying {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementSetAnimationIsPlaying; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementSetAnimationIsPlayingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    ModelElementSetAnimationIsPlaying(const WebKit::ModelIdentifier& modelIdentifier, bool isPlaying)
        : m_arguments(modelIdentifier, isPlaying)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&, bool> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementIsLoopingAnimation {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementIsLoopingAnimation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementIsLoopingAnimationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<bool, WebCore::ResourceError>>;
    explicit ModelElementIsLoopingAnimation(const WebKit::ModelIdentifier& modelIdentifier)
        : m_arguments(modelIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementSetIsLoopingAnimation {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementSetIsLoopingAnimation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementSetIsLoopingAnimationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    ModelElementSetIsLoopingAnimation(const WebKit::ModelIdentifier& modelIdentifier, bool isLooping)
        : m_arguments(modelIdentifier, isLooping)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&, bool> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementAnimationDuration {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementAnimationDuration; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementAnimationDurationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<Seconds, WebCore::ResourceError>>;
    explicit ModelElementAnimationDuration(const WebKit::ModelIdentifier& modelIdentifier)
        : m_arguments(modelIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementAnimationCurrentTime {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementAnimationCurrentTime; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementAnimationCurrentTimeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<Seconds, WebCore::ResourceError>>;
    explicit ModelElementAnimationCurrentTime(const WebKit::ModelIdentifier& modelIdentifier)
        : m_arguments(modelIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementSetAnimationCurrentTime {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier, Seconds>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementSetAnimationCurrentTime; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementSetAnimationCurrentTimeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    ModelElementSetAnimationCurrentTime(const WebKit::ModelIdentifier& modelIdentifier, const Seconds& currentTime)
        : m_arguments(modelIdentifier, currentTime)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&, const Seconds&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementHasAudio {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementHasAudio; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementHasAudioReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<bool, WebCore::ResourceError>>;
    explicit ModelElementHasAudio(const WebKit::ModelIdentifier& modelIdentifier)
        : m_arguments(modelIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementIsMuted {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementIsMuted; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementIsMutedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Expected<bool, WebCore::ResourceError>>;
    explicit ModelElementIsMuted(const WebKit::ModelIdentifier& modelIdentifier)
        : m_arguments(modelIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW)
class ModelElementSetIsMuted {
public:
    using Arguments = std::tuple<WebKit::ModelIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_ModelElementSetIsMuted; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_ModelElementSetIsMutedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    ModelElementSetIsMuted(const WebKit::ModelIdentifier& modelIdentifier, bool isMuted)
        : m_arguments(modelIdentifier, isMuted)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::ModelIdentifier&, bool> m_arguments;
};
#endif

#if ENABLE(APPLE_PAY_AMS_UI)
class StartApplePayAMSUISession {
public:
    using Arguments = std::tuple<URL, WebCore::ApplePayAMSUIRequest>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_StartApplePayAMSUISession; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_StartApplePayAMSUISessionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<bool>>;
    StartApplePayAMSUISession(const URL& originatingURL, const WebCore::ApplePayAMSUIRequest& request)
        : m_arguments(originatingURL, request)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const WebCore::ApplePayAMSUIRequest&> m_arguments;
};
#endif

#if ENABLE(APPLE_PAY_AMS_UI)
class AbortApplePayAMSUISession {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_AbortApplePayAMSUISession; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(SYSTEM_PREVIEW)
class BeginSystemPreview {
public:
    using Arguments = std::tuple<URL, WebCore::SystemPreviewInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_BeginSystemPreview; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_BeginSystemPreviewReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    BeginSystemPreview(const URL& url, const WebCore::SystemPreviewInfo& systemPreviewInfo)
        : m_arguments(url, systemPreviewInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const WebCore::SystemPreviewInfo&> m_arguments;
};
#endif

class DidCreateSleepDisabler {
public:
    using Arguments = std::tuple<WebCore::SleepDisablerIdentifier, String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidCreateSleepDisabler; }
    static constexpr bool isSync = false;

    DidCreateSleepDisabler(const WebCore::SleepDisablerIdentifier& identifier, const String& reason, bool display)
        : m_arguments(identifier, reason, display)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SleepDisablerIdentifier&, const String&, bool> m_arguments;
};

class DidDestroySleepDisabler {
public:
    using Arguments = std::tuple<WebCore::SleepDisablerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidDestroySleepDisabler; }
    static constexpr bool isSync = false;

    explicit DidDestroySleepDisabler(const WebCore::SleepDisablerIdentifier& identifier)
        : m_arguments(identifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SleepDisablerIdentifier&> m_arguments;
};

class RequestCookieConsent {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_RequestCookieConsent; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPageProxy_RequestCookieConsentReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::CookieConsentDecisionResult>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidApplyLinkDecorationFiltering {
public:
    using Arguments = std::tuple<URL, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_DidApplyLinkDecorationFiltering; }
    static constexpr bool isSync = false;

    DidApplyLinkDecorationFiltering(const URL& originalURL, const URL& adjustedURL)
        : m_arguments(originalURL, adjustedURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const URL&> m_arguments;
};

class BroadcastFrameRemovalToOtherProcesses {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPageProxy_BroadcastFrameRemovalToOtherProcesses; }
    static constexpr bool isSync = false;

    explicit BroadcastFrameRemovalToOtherProcesses(const WebCore::FrameIdentifier& frameID)
        : m_arguments(frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&> m_arguments;
};

} // namespace WebPageProxy
} // namespace Messages
