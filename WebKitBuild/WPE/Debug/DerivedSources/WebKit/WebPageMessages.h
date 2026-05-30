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
#include "DataReference.h"
#include "DrawingAreaInfo.h"
#include "EditorState.h"
#include "FocusedElementInformation.h"
#include "GamepadData.h"
#include "GeolocationIdentifier.h"
#if PLATFORM(IOS_FAMILY)
#include "GestureTypes.h"
#endif
#include "IdentifierTypes.h"
#include "MessageNames.h"
#include "NetworkResourceLoadIdentifier.h"
#include "PDFPluginIdentifier.h"
#include "SandboxExtension.h"
#include "SessionState.h"
#include "ShareableBitmap.h"
#include "SharedBufferReference.h"
#include "SharedMemory.h"
#include "TransactionID.h"
#include "WebEventModifier.h"
#include "WebFindOptions.h"
#include "WebFoundTextRange.h"
#include "WebPageProxyIdentifier.h"
#include "WebURLSchemeHandlerIdentifier.h"
#include "WebsitePoliciesData.h"
#include <JavaScriptCore/InspectorFrontendChannel.h>
#include <WebCore/ActivityState.h>
#include <WebCore/ApplicationManifest.h>
#include <WebCore/BackForwardItemIdentifier.h>
#include <WebCore/CharacterRange.h>
#include <WebCore/Color.h>
#include <WebCore/CompositionHighlight.h>
#include <WebCore/CompositionUnderline.h>
#if ENABLE(DATA_DETECTION)
#include <WebCore/DataDetectorType.h>
#endif
#include <WebCore/DictationAlternative.h>
#include <WebCore/DictationContext.h>
#include <WebCore/DragActions.h>
#include <WebCore/DragData.h>
#include <WebCore/ElementContext.h>
#include <WebCore/FloatRect.h>
#include <WebCore/FloatSize.h>
#include <WebCore/FrameIdentifier.h>
#include <WebCore/FrameLoaderTypes.h>
#include <WebCore/IntDegrees.h>
#include <WebCore/IntRect.h>
#include <WebCore/IntSize.h>
#include <WebCore/JSDOMExceptionHandling.h>
#include <WebCore/LayerHostingContextIdentifier.h>
#include <WebCore/LayoutMilestone.h>
#include <WebCore/LinkDecorationFilteringData.h>
#include <WebCore/MediaKeySystemRequestIdentifier.h>
#include <WebCore/MediaProducer.h>
#include <WebCore/PageOverlay.h>
#include <WebCore/PlatformEvent.h>
#include <WebCore/PlatformLayerIdentifier.h>
#include <WebCore/PlatformWheelEvent.h>
#include <WebCore/PlaybackTargetClientContextIdentifier.h>
#include <WebCore/PointerID.h>
#include <WebCore/ProcessQualified.h>
#include <WebCore/RectEdges.h>
#include <WebCore/RegistrableDomain.h>
#include <WebCore/Report.h>
#include <WebCore/ResourceLoaderIdentifier.h>
#include <WebCore/ScriptExecutionContextIdentifier.h>
#include <WebCore/ScrollingCoordinatorTypes.h>
#include <WebCore/SharedBuffer.h>
#include <WebCore/TextCheckerClient.h>
#include <WebCore/TextIndicator.h>
#include <WebCore/TextManipulationController.h>
#include <WebCore/TextManipulationItem.h>
#include <WebCore/UserMediaRequestIdentifier.h>
#include <WebCore/ViewportArguments.h>
#include <optional>
#include <utility>
#include <wtf/Forward.h>
#include <wtf/HashMap.h>
#include <wtf/MachSendRight.h>
#include <wtf/ObjectIdentifier.h>
#include <wtf/OptionSet.h>
#include <wtf/Ref.h>
#include <wtf/RefCounted.h>
#include <wtf/ThreadSafeRefCounted.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace IPC {
class FormDataReference;
class SharedBufferReference;
}

namespace JSC {
enum class MessageLevel : uint8_t;
enum class MessageSource : uint8_t;
}

namespace WebCore {
class CaptureDevice;
class Color;
class DragData;
class FloatPoint;
class FloatRect;
class FloatSize;
class FontAttributeChanges;
class FontChanges;
class IntPoint;
class IntRect;
class IntSize;
class MediaPlaybackTargetContext;
class ResourceError;
class ResourceRequest;
class ResourceResponse;
class SelectionData;
enum class CreateNewGroupForHighlight : bool;
enum class EventMakesGamepadsVisible : bool;
enum class HighlightRequestOriginatedInApp : bool;
enum class HighlightVisibility : bool;
enum class CaretAnimatorType : uint8_t;
enum class FrameLoadType : uint8_t;
enum class MediaProducerMediaCaptureKind : uint8_t;
enum class ScrollGranularity : uint8_t;
enum class ScrollPinningBehavior : uint8_t;
enum class SelectionDirection : uint8_t;
enum class ShouldTreatAsContinuingLoad : uint8_t;
enum class TextGranularity : uint8_t;
enum class ViolationReportType : uint8_t;
enum class WritingDirection : uint8_t;
struct AttributedString;
struct ElementContext;
struct FontAttributes;
struct MediaDeviceHashSalts;
struct RunJavaScriptParameters;
struct SecurityPolicyViolationEventInit;
struct SystemPreviewInfo;
struct TextCheckingResult;
struct TextRecognitionResult;
}

namespace WebKit {
class CallbackID;
class RevealItem;
class UserData;
class WebContextMenuItemData;
class WebKeyboardEvent;
class WebMouseEvent;
class WebTouchEvent;
class WebWheelEvent;
enum class ContentAsStringIncludesChildFrames : bool;
enum class RespectSelectionAnchor : bool;
enum class DragControllerAction : uint8_t;
enum class FindDecorationStyle : uint8_t;
enum class GestureRecognizerState : uint8_t;
enum class GestureType : uint8_t;
enum class LayerHostingMode : uint8_t;
enum class MediaPlaybackState : uint8_t;
enum class SelectionTouch : uint8_t;
enum class SyntheticEditingCommandType : uint8_t;
enum class TextRecognitionUpdateResult : uint8_t;
struct BackForwardListItemState;
struct DataDetectionResult;
struct DocumentEditingContext;
struct DocumentEditingContextRequest;
struct DynamicViewportSizeUpdate;
struct EditingRange;
struct FrameInfoData;
struct FrameTreeNodeData;
struct InsertTextOptions;
struct InteractionInformationRequest;
struct LoadParameters;
struct LocalFrameCreationParameters;
struct PrintInfo;
struct UserMessage;
struct WebAutocorrectionData;
struct WebFoundTextRange;
struct WebHitTestResultData;
struct WebPreferencesStore;
struct WebsitePoliciesData;
}

namespace Messages {
namespace WebPage {

static inline IPC::ReceiverName messageReceiverName()
{
    return IPC::ReceiverName::WebPage;
}

class SetInitialFocus {
public:
    using Arguments = std::tuple<bool, bool, WebKit::WebKeyboardEvent>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetInitialFocus; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SetInitialFocusReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetInitialFocus(bool forward, bool isKeyboardEventValid, const WebKit::WebKeyboardEvent& event)
        : m_arguments(forward, isKeyboardEventValid, event)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool, const WebKit::WebKeyboardEvent&> m_arguments;
};

class SetActivityState {
public:
    using Arguments = std::tuple<OptionSet<WebCore::ActivityState>, WebKit::ActivityStateChangeID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetActivityState; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SetActivityStateReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SetActivityState(const OptionSet<WebCore::ActivityState>& activityState, const WebKit::ActivityStateChangeID& activityStateChangeID)
        : m_arguments(activityState, activityStateChangeID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebCore::ActivityState>&, const WebKit::ActivityStateChangeID&> m_arguments;
};

class SetLayerHostingMode {
public:
    using Arguments = std::tuple<WebKit::LayerHostingMode>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetLayerHostingMode; }
    static constexpr bool isSync = false;

    explicit SetLayerHostingMode(WebKit::LayerHostingMode layerHostingMode)
        : m_arguments(layerHostingMode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::LayerHostingMode> m_arguments;
};

class SetBackgroundColor {
public:
    using Arguments = std::tuple<std::optional<WebCore::Color>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetBackgroundColor; }
    static constexpr bool isSync = false;

    explicit SetBackgroundColor(const std::optional<WebCore::Color>& color)
        : m_arguments(color)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::Color>&> m_arguments;
};

class AddConsoleMessage {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, JSC::MessageSource, JSC::MessageLevel, String, std::optional<WebCore::ResourceLoaderIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_AddConsoleMessage; }
    static constexpr bool isSync = false;

    AddConsoleMessage(const WebCore::FrameIdentifier& frameID, JSC::MessageSource messageSource, JSC::MessageLevel messageLevel, const String& message, const std::optional<WebCore::ResourceLoaderIdentifier>& requestID)
        : m_arguments(frameID, messageSource, messageLevel, message, requestID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, JSC::MessageSource, JSC::MessageLevel, const String&, const std::optional<WebCore::ResourceLoaderIdentifier>&> m_arguments;
};

class EnqueueSecurityPolicyViolationEvent {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebCore::SecurityPolicyViolationEventInit>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_EnqueueSecurityPolicyViolationEvent; }
    static constexpr bool isSync = false;

    EnqueueSecurityPolicyViolationEvent(const WebCore::FrameIdentifier& frameID, const WebCore::SecurityPolicyViolationEventInit& eventInit)
        : m_arguments(frameID, eventInit)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebCore::SecurityPolicyViolationEventInit&> m_arguments;
};

class SendReportToEndpoints {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, URL, Vector<String>, Vector<String>, IPC::FormDataReference, WebCore::ViolationReportType>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SendReportToEndpoints; }
    static constexpr bool isSync = false;

    SendReportToEndpoints(const WebCore::FrameIdentifier& frameID, const URL& baseURL, const Vector<String>& endpointURIs, const Vector<String>& endpointTokens, const IPC::FormDataReference& reportData, WebCore::ViolationReportType reportType)
        : m_arguments(frameID, baseURL, endpointURIs, endpointTokens, reportData, reportType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const URL&, const Vector<String>&, const Vector<String>&, const IPC::FormDataReference&, WebCore::ViolationReportType> m_arguments;
};

class NotifyReportObservers {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, Ref<WebCore::Report>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_NotifyReportObservers; }
    static constexpr bool isSync = false;

    NotifyReportObservers(const WebCore::FrameIdentifier& frameID, const Ref<WebCore::Report>& report)
        : m_arguments(frameID, report)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const Ref<WebCore::Report>&> m_arguments;
};

class TestProcessIncomingSyncMessagesWhenWaitingForSyncReply {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_TestProcessIncomingSyncMessagesWhenWaitingForSyncReply; }
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

#if PLATFORM(COCOA)
class SetTopContentInsetFenced {
public:
    using Arguments = std::tuple<float, MachSendRight>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetTopContentInsetFenced; }
    static constexpr bool isSync = false;

    SetTopContentInsetFenced(float contentInset, MachSendRight&& machSendRight)
        : m_arguments(contentInset, WTFMove(machSendRight))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float, MachSendRight&&> m_arguments;
};
#endif

class SetTopContentInset {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetTopContentInset; }
    static constexpr bool isSync = false;

    explicit SetTopContentInset(float contentInset)
        : m_arguments(contentInset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};

class SetUnderlayColor {
public:
    using Arguments = std::tuple<WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetUnderlayColor; }
    static constexpr bool isSync = false;

    explicit SetUnderlayColor(const WebCore::Color& color)
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

class SetUnderPageBackgroundColorOverride {
public:
    using Arguments = std::tuple<WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetUnderPageBackgroundColorOverride; }
    static constexpr bool isSync = false;

    explicit SetUnderPageBackgroundColorOverride(const WebCore::Color& underPageBackgroundColorOverride)
        : m_arguments(underPageBackgroundColorOverride)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::Color&> m_arguments;
};

class ViewWillStartLiveResize {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ViewWillStartLiveResize; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ViewWillEndLiveResize {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ViewWillEndLiveResize; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ExecuteEditCommandWithCallback {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ExecuteEditCommandWithCallback; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ExecuteEditCommandWithCallbackReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    ExecuteEditCommandWithCallback(const String& name, const String& argument)
        : m_arguments(name, argument)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&> m_arguments;
};

class KeyEvent {
public:
    using Arguments = std::tuple<WebKit::WebKeyboardEvent>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_KeyEvent; }
    static constexpr bool isSync = false;

    explicit KeyEvent(const WebKit::WebKeyboardEvent& event)
        : m_arguments(event)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebKeyboardEvent&> m_arguments;
};

class MouseEvent {
public:
    using Arguments = std::tuple<WebKit::WebMouseEvent, std::optional<Vector<WebKit::SandboxExtension::Handle>>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_MouseEvent; }
    static constexpr bool isSync = false;

    MouseEvent(const WebKit::WebMouseEvent& event, const std::optional<Vector<WebKit::SandboxExtension::Handle>>& sandboxExtensions)
        : m_arguments(event, sandboxExtensions)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebMouseEvent&, const std::optional<Vector<WebKit::SandboxExtension::Handle>>&> m_arguments;
};

#if ENABLE(NOTIFICATIONS)
class ClearNotificationPermissionState {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ClearNotificationPermissionState; }
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
class SetViewportConfigurationViewLayoutSize {
public:
    using Arguments = std::tuple<WebCore::FloatSize, double, double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetViewportConfigurationViewLayoutSize; }
    static constexpr bool isSync = false;

    SetViewportConfigurationViewLayoutSize(const WebCore::FloatSize& size, double scaleFactor, double minimumEffectiveDeviceWidth)
        : m_arguments(size, scaleFactor, minimumEffectiveDeviceWidth)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatSize&, double, double> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SetDeviceOrientation {
public:
    using Arguments = std::tuple<WebCore::IntDegrees>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetDeviceOrientation; }
    static constexpr bool isSync = false;

    explicit SetDeviceOrientation(const WebCore::IntDegrees& deviceOrientation)
        : m_arguments(deviceOrientation)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntDegrees&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SetOverrideViewportArguments {
public:
    using Arguments = std::tuple<std::optional<WebCore::ViewportArguments>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetOverrideViewportArguments; }
    static constexpr bool isSync = false;

    explicit SetOverrideViewportArguments(const std::optional<WebCore::ViewportArguments>& arguments)
        : m_arguments(arguments)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::ViewportArguments>&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class DynamicViewportSizeUpdate {
public:
    using Arguments = std::tuple<WebKit::DynamicViewportSizeUpdate>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DynamicViewportSizeUpdate; }
    static constexpr bool isSync = false;

    explicit DynamicViewportSizeUpdate(const WebKit::DynamicViewportSizeUpdate& target)
        : m_arguments(target)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DynamicViewportSizeUpdate&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SetScreenIsBeingCaptured {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetScreenIsBeingCaptured; }
    static constexpr bool isSync = false;

    explicit SetScreenIsBeingCaptured(bool captured)
        : m_arguments(captured)
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

#if PLATFORM(IOS_FAMILY)
class SetInsertionPointColor {
public:
    using Arguments = std::tuple<WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetInsertionPointColor; }
    static constexpr bool isSync = false;

    explicit SetInsertionPointColor(const WebCore::Color& color)
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

#if PLATFORM(IOS_FAMILY)
class AttemptSyntheticClick {
public:
    using Arguments = std::tuple<WebCore::IntPoint, OptionSet<WebKit::WebEventModifier>, WebKit::TransactionID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_AttemptSyntheticClick; }
    static constexpr bool isSync = false;

    AttemptSyntheticClick(const WebCore::IntPoint& point, const OptionSet<WebKit::WebEventModifier>& modifiers, const WebKit::TransactionID& lastLayerTreeTransactionId)
        : m_arguments(point, modifiers, lastLayerTreeTransactionId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, const OptionSet<WebKit::WebEventModifier>&, const WebKit::TransactionID&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class PotentialTapAtPosition {
public:
    using Arguments = std::tuple<WebKit::TapIdentifier, WebCore::FloatPoint, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PotentialTapAtPosition; }
    static constexpr bool isSync = false;

    PotentialTapAtPosition(const WebKit::TapIdentifier& requestID, const WebCore::FloatPoint& point, bool shouldRequestMagnificationInformation)
        : m_arguments(requestID, point, shouldRequestMagnificationInformation)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TapIdentifier&, const WebCore::FloatPoint&, bool> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class CommitPotentialTap {
public:
    using Arguments = std::tuple<OptionSet<WebKit::WebEventModifier>, WebKit::TransactionID, WebCore::PointerID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CommitPotentialTap; }
    static constexpr bool isSync = false;

    CommitPotentialTap(const OptionSet<WebKit::WebEventModifier>& modifiers, const WebKit::TransactionID& lastLayerTreeTransactionId, const WebCore::PointerID& pointerId)
        : m_arguments(modifiers, lastLayerTreeTransactionId, pointerId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebKit::WebEventModifier>&, const WebKit::TransactionID&, const WebCore::PointerID&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class CancelPotentialTap {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CancelPotentialTap; }
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
class TapHighlightAtPosition {
public:
    using Arguments = std::tuple<WebKit::TapIdentifier, WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_TapHighlightAtPosition; }
    static constexpr bool isSync = false;

    TapHighlightAtPosition(const WebKit::TapIdentifier& requestID, const WebCore::FloatPoint& point)
        : m_arguments(requestID, point)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TapIdentifier&, const WebCore::FloatPoint&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class DidRecognizeLongPress {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidRecognizeLongPress; }
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
class HandleDoubleTapForDoubleClickAtPoint {
public:
    using Arguments = std::tuple<WebCore::IntPoint, OptionSet<WebKit::WebEventModifier>, WebKit::TransactionID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_HandleDoubleTapForDoubleClickAtPoint; }
    static constexpr bool isSync = false;

    HandleDoubleTapForDoubleClickAtPoint(const WebCore::IntPoint& point, const OptionSet<WebKit::WebEventModifier>& modifiers, const WebKit::TransactionID& lastLayerTreeTransactionId)
        : m_arguments(point, modifiers, lastLayerTreeTransactionId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, const OptionSet<WebKit::WebEventModifier>&, const WebKit::TransactionID&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class InspectorNodeSearchMovedToPosition {
public:
    using Arguments = std::tuple<WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_InspectorNodeSearchMovedToPosition; }
    static constexpr bool isSync = false;

    explicit InspectorNodeSearchMovedToPosition(const WebCore::FloatPoint& point)
        : m_arguments(point)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatPoint&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class InspectorNodeSearchEndedAtPosition {
public:
    using Arguments = std::tuple<WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_InspectorNodeSearchEndedAtPosition; }
    static constexpr bool isSync = false;

    explicit InspectorNodeSearchEndedAtPosition(const WebCore::FloatPoint& point)
        : m_arguments(point)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatPoint&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class BlurFocusedElement {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_BlurFocusedElement; }
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
class SelectWithGesture {
public:
    using Arguments = std::tuple<WebCore::IntPoint, WebKit::GestureType, WebKit::GestureRecognizerState, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SelectWithGesture; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SelectWithGestureReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::IntPoint, WebKit::GestureType, WebKit::GestureRecognizerState, OptionSet<WebKit::SelectionFlags>>;
    SelectWithGesture(const WebCore::IntPoint& point, WebKit::GestureType gestureType, WebKit::GestureRecognizerState gestureState, bool isInteractingWithFocusedElement)
        : m_arguments(point, gestureType, gestureState, isInteractingWithFocusedElement)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, WebKit::GestureType, WebKit::GestureRecognizerState, bool> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class UpdateSelectionWithTouches {
public:
    using Arguments = std::tuple<WebCore::IntPoint, WebKit::SelectionTouch, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateSelectionWithTouches; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_UpdateSelectionWithTouchesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::IntPoint, WebKit::SelectionTouch, OptionSet<WebKit::SelectionFlags>>;
    UpdateSelectionWithTouches(const WebCore::IntPoint& point, WebKit::SelectionTouch touches, bool baseIsStart)
        : m_arguments(point, touches, baseIsStart)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, WebKit::SelectionTouch, bool> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SelectWithTwoTouches {
public:
    using Arguments = std::tuple<WebCore::IntPoint, WebCore::IntPoint, WebKit::GestureType, WebKit::GestureRecognizerState>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SelectWithTwoTouches; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SelectWithTwoTouchesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::IntPoint, WebKit::GestureType, WebKit::GestureRecognizerState, OptionSet<WebKit::SelectionFlags>>;
    SelectWithTwoTouches(const WebCore::IntPoint& from, const WebCore::IntPoint& to, WebKit::GestureType gestureType, WebKit::GestureRecognizerState gestureState)
        : m_arguments(from, to, gestureType, gestureState)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, const WebCore::IntPoint&, WebKit::GestureType, WebKit::GestureRecognizerState> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class ExtendSelection {
public:
    using Arguments = std::tuple<WebCore::TextGranularity>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ExtendSelection; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ExtendSelectionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit ExtendSelection(WebCore::TextGranularity granularity)
        : m_arguments(granularity)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::TextGranularity> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SelectWordBackward {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SelectWordBackward; }
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
class ExtendSelectionForReplacement {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ExtendSelectionForReplacement; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ExtendSelectionForReplacementReply; }
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

#if PLATFORM(IOS_FAMILY)
class MoveSelectionByOffset {
public:
    using Arguments = std::tuple<int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_MoveSelectionByOffset; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_MoveSelectionByOffsetReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit MoveSelectionByOffset(int32_t offset)
        : m_arguments(offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SelectTextWithGranularityAtPoint {
public:
    using Arguments = std::tuple<WebCore::IntPoint, WebCore::TextGranularity, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SelectTextWithGranularityAtPoint; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SelectTextWithGranularityAtPointReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SelectTextWithGranularityAtPoint(const WebCore::IntPoint& point, WebCore::TextGranularity granularity, bool isInteractingWithFocusedElement)
        : m_arguments(point, granularity, isInteractingWithFocusedElement)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, WebCore::TextGranularity, bool> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SelectPositionAtBoundaryWithDirection {
public:
    using Arguments = std::tuple<WebCore::IntPoint, WebCore::TextGranularity, WebCore::SelectionDirection, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SelectPositionAtBoundaryWithDirection; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SelectPositionAtBoundaryWithDirectionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SelectPositionAtBoundaryWithDirection(const WebCore::IntPoint& point, WebCore::TextGranularity granularity, WebCore::SelectionDirection direction, bool isInteractingWithFocusedElement)
        : m_arguments(point, granularity, direction, isInteractingWithFocusedElement)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, WebCore::TextGranularity, WebCore::SelectionDirection, bool> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class MoveSelectionAtBoundaryWithDirection {
public:
    using Arguments = std::tuple<WebCore::TextGranularity, WebCore::SelectionDirection>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_MoveSelectionAtBoundaryWithDirection; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_MoveSelectionAtBoundaryWithDirectionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    MoveSelectionAtBoundaryWithDirection(WebCore::TextGranularity granularity, WebCore::SelectionDirection direction)
        : m_arguments(granularity, direction)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::TextGranularity, WebCore::SelectionDirection> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SelectPositionAtPoint {
public:
    using Arguments = std::tuple<WebCore::IntPoint, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SelectPositionAtPoint; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SelectPositionAtPointReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    SelectPositionAtPoint(const WebCore::IntPoint& point, bool isInteractingWithFocusedElement)
        : m_arguments(point, isInteractingWithFocusedElement)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, bool> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class BeginSelectionInDirection {
public:
    using Arguments = std::tuple<WebCore::SelectionDirection>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_BeginSelectionInDirection; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_BeginSelectionInDirectionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit BeginSelectionInDirection(WebCore::SelectionDirection direction)
        : m_arguments(direction)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::SelectionDirection> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class UpdateSelectionWithExtentPoint {
public:
    using Arguments = std::tuple<WebCore::IntPoint, bool, WebKit::RespectSelectionAnchor>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateSelectionWithExtentPoint; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_UpdateSelectionWithExtentPointReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    UpdateSelectionWithExtentPoint(const WebCore::IntPoint& point, bool isInteractingWithFocusedElement, WebKit::RespectSelectionAnchor respectSelectionAnchor)
        : m_arguments(point, isInteractingWithFocusedElement, respectSelectionAnchor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, bool, WebKit::RespectSelectionAnchor> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class UpdateSelectionWithExtentPointAndBoundary {
public:
    using Arguments = std::tuple<WebCore::IntPoint, WebCore::TextGranularity, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateSelectionWithExtentPointAndBoundary; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_UpdateSelectionWithExtentPointAndBoundaryReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    UpdateSelectionWithExtentPointAndBoundary(const WebCore::IntPoint& point, WebCore::TextGranularity granularity, bool isInteractingWithFocusedElement)
        : m_arguments(point, granularity, isInteractingWithFocusedElement)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, WebCore::TextGranularity, bool> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class RequestDictationContext {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestDictationContext; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RequestDictationContextReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String, String, String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if (PLATFORM(IOS_FAMILY) && ENABLE(REVEAL))
class RequestRVItemInCurrentSelectedRange {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestRVItemInCurrentSelectedRange; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RequestRVItemInCurrentSelectedRangeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::RevealItem>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if (PLATFORM(IOS_FAMILY) && ENABLE(REVEAL))
class PrepareSelectionForContextMenuWithLocationInView {
public:
    using Arguments = std::tuple<WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PrepareSelectionForContextMenuWithLocationInView; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_PrepareSelectionForContextMenuWithLocationInViewReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool, WebKit::RevealItem>;
    explicit PrepareSelectionForContextMenuWithLocationInView(const WebCore::IntPoint& point)
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
class WillInsertFinalDictationResult {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_WillInsertFinalDictationResult; }
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
class DidInsertFinalDictationResult {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidInsertFinalDictationResult; }
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
class ReplaceDictatedText {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ReplaceDictatedText; }
    static constexpr bool isSync = false;

    ReplaceDictatedText(const String& oldText, const String& newText)
        : m_arguments(oldText, newText)
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

#if PLATFORM(IOS_FAMILY)
class ReplaceSelectedText {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ReplaceSelectedText; }
    static constexpr bool isSync = false;

    ReplaceSelectedText(const String& oldText, const String& newText)
        : m_arguments(oldText, newText)
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

#if PLATFORM(IOS_FAMILY)
class RequestAutocorrectionData {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestAutocorrectionData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RequestAutocorrectionDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::WebAutocorrectionData>;
    explicit RequestAutocorrectionData(const String& textForAutocorrection)
        : m_arguments(textForAutocorrection)
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
class ApplyAutocorrection {
public:
    using Arguments = std::tuple<String, String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ApplyAutocorrection; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ApplyAutocorrectionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    ApplyAutocorrection(const String& correction, const String& originalText, bool isCandidate)
        : m_arguments(correction, originalText, isCandidate)
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

#if PLATFORM(IOS_FAMILY)
class SyncApplyAutocorrection {
public:
    using Arguments = std::tuple<String, String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SyncApplyAutocorrection; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    SyncApplyAutocorrection(const String& correction, const String& originalText, bool isCandidate)
        : m_arguments(correction, originalText, isCandidate)
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

#if PLATFORM(IOS_FAMILY)
class HandleAutocorrectionContextRequest {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_HandleAutocorrectionContextRequest; }
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
class RequestEvasionRectsAboveSelection {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestEvasionRectsAboveSelection; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RequestEvasionRectsAboveSelectionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::FloatRect>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class RequestPositionInformation {
public:
    using Arguments = std::tuple<WebKit::InteractionInformationRequest>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestPositionInformation; }
    static constexpr bool isSync = false;

    explicit RequestPositionInformation(const WebKit::InteractionInformationRequest& request)
        : m_arguments(request)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::InteractionInformationRequest&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class StartInteractionWithElementContextOrPosition {
public:
    using Arguments = std::tuple<std::optional<WebCore::ElementContext>, WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_StartInteractionWithElementContextOrPosition; }
    static constexpr bool isSync = false;

    StartInteractionWithElementContextOrPosition(const std::optional<WebCore::ElementContext>& elementContext, const WebCore::IntPoint& point)
        : m_arguments(elementContext, point)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::ElementContext>&, const WebCore::IntPoint&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class StopInteraction {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_StopInteraction; }
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
class PerformActionOnElement {
public:
    using Arguments = std::tuple<uint32_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PerformActionOnElement; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_PerformActionOnElementReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    PerformActionOnElement(uint32_t action, const String& authenticationToken)
        : m_arguments(action, authenticationToken)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const String&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class PerformActionOnElements {
public:
    using Arguments = std::tuple<uint32_t, Vector<WebCore::ElementContext>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PerformActionOnElements; }
    static constexpr bool isSync = false;

    PerformActionOnElements(uint32_t action, const Vector<WebCore::ElementContext>& elements)
        : m_arguments(action, elements)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const Vector<WebCore::ElementContext>&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class FocusNextFocusedElement {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_FocusNextFocusedElement; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_FocusNextFocusedElementReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit FocusNextFocusedElement(bool isForward)
        : m_arguments(isForward)
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

#if PLATFORM(IOS_FAMILY)
class AutofillLoginCredentials {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_AutofillLoginCredentials; }
    static constexpr bool isSync = false;

    AutofillLoginCredentials(const String& username, const String& password)
        : m_arguments(username, password)
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

#if PLATFORM(IOS_FAMILY)
class SetFocusedElementValue {
public:
    using Arguments = std::tuple<WebCore::ElementContext, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetFocusedElementValue; }
    static constexpr bool isSync = false;

    SetFocusedElementValue(const WebCore::ElementContext& context, const String& value)
        : m_arguments(context, value)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ElementContext&, const String&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SetFocusedElementSelectedIndex {
public:
    using Arguments = std::tuple<WebCore::ElementContext, uint32_t, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetFocusedElementSelectedIndex; }
    static constexpr bool isSync = false;

    SetFocusedElementSelectedIndex(const WebCore::ElementContext& context, uint32_t index, bool allowMultipleSelection)
        : m_arguments(context, index, allowMultipleSelection)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ElementContext&, uint32_t, bool> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class ApplicationWillResignActive {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ApplicationWillResignActive; }
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
class ApplicationDidEnterBackground {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ApplicationDidEnterBackground; }
    static constexpr bool isSync = false;

    explicit ApplicationDidEnterBackground(bool isSuspendedUnderLock)
        : m_arguments(isSuspendedUnderLock)
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

#if PLATFORM(IOS_FAMILY)
class ApplicationDidFinishSnapshottingAfterEnteringBackground {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ApplicationDidFinishSnapshottingAfterEnteringBackground; }
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
class ApplicationWillEnterForeground {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ApplicationWillEnterForeground; }
    static constexpr bool isSync = false;

    explicit ApplicationWillEnterForeground(bool isSuspendedUnderLock)
        : m_arguments(isSuspendedUnderLock)
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

#if PLATFORM(IOS_FAMILY)
class ApplicationDidBecomeActive {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ApplicationDidBecomeActive; }
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
class ApplicationDidEnterBackgroundForMedia {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ApplicationDidEnterBackgroundForMedia; }
    static constexpr bool isSync = false;

    explicit ApplicationDidEnterBackgroundForMedia(bool isSuspendedUnderLock)
        : m_arguments(isSuspendedUnderLock)
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

#if PLATFORM(IOS_FAMILY)
class ApplicationWillEnterForegroundForMedia {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ApplicationWillEnterForegroundForMedia; }
    static constexpr bool isSync = false;

    explicit ApplicationWillEnterForegroundForMedia(bool isSuspendedUnderLock)
        : m_arguments(isSuspendedUnderLock)
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

#if PLATFORM(IOS_FAMILY)
class ContentSizeCategoryDidChange {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ContentSizeCategoryDidChange; }
    static constexpr bool isSync = false;

    explicit ContentSizeCategoryDidChange(const String& contentSizeCategory)
        : m_arguments(contentSizeCategory)
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
class GetSelectionContext {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetSelectionContext; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetSelectionContextReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String, String, String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SetAllowsMediaDocumentInlinePlayback {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetAllowsMediaDocumentInlinePlayback; }
    static constexpr bool isSync = false;

    explicit SetAllowsMediaDocumentInlinePlayback(bool allows)
        : m_arguments(allows)
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

#if PLATFORM(IOS_FAMILY)
class HandleTwoFingerTapAtPoint {
public:
    using Arguments = std::tuple<WebCore::IntPoint, OptionSet<WebKit::WebEventModifier>, WebKit::TapIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_HandleTwoFingerTapAtPoint; }
    static constexpr bool isSync = false;

    HandleTwoFingerTapAtPoint(const WebCore::IntPoint& point, const OptionSet<WebKit::WebEventModifier>& modifiers, const WebKit::TapIdentifier& requestID)
        : m_arguments(point, modifiers, requestID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, const OptionSet<WebKit::WebEventModifier>&, const WebKit::TapIdentifier&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SetForceAlwaysUserScalable {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetForceAlwaysUserScalable; }
    static constexpr bool isSync = false;

    explicit SetForceAlwaysUserScalable(bool userScalable)
        : m_arguments(userScalable)
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

#if PLATFORM(IOS_FAMILY)
class GetRectsForGranularityWithSelectionOffset {
public:
    using Arguments = std::tuple<WebCore::TextGranularity, int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetRectsForGranularityWithSelectionOffset; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetRectsForGranularityWithSelectionOffsetReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::SelectionGeometry>>;
    GetRectsForGranularityWithSelectionOffset(WebCore::TextGranularity granularity, int32_t offset)
        : m_arguments(granularity, offset)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::TextGranularity, int32_t> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class GetRectsAtSelectionOffsetWithText {
public:
    using Arguments = std::tuple<int32_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetRectsAtSelectionOffsetWithText; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetRectsAtSelectionOffsetWithTextReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::SelectionGeometry>>;
    GetRectsAtSelectionOffsetWithText(int32_t offset, const String& text)
        : m_arguments(offset, text)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t, const String&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class StoreSelectionForAccessibility {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_StoreSelectionForAccessibility; }
    static constexpr bool isSync = false;

    explicit StoreSelectionForAccessibility(bool shouldStore)
        : m_arguments(shouldStore)
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

#if PLATFORM(IOS_FAMILY)
class StartAutoscrollAtPosition {
public:
    using Arguments = std::tuple<WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_StartAutoscrollAtPosition; }
    static constexpr bool isSync = false;

    explicit StartAutoscrollAtPosition(const WebCore::FloatPoint& positionInWindow)
        : m_arguments(positionInWindow)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatPoint&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class CancelAutoscroll {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CancelAutoscroll; }
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
class RequestFocusedElementInformation {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestFocusedElementInformation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RequestFocusedElementInformationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::FocusedElementInformation>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class HardwareKeyboardAvailabilityChanged {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_HardwareKeyboardAvailabilityChanged; }
    static constexpr bool isSync = false;

    explicit HardwareKeyboardAvailabilityChanged(bool keyboardIsAttached)
        : m_arguments(keyboardIsAttached)
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

#if PLATFORM(IOS_FAMILY)
class SetIsShowingInputViewForFocusedElement {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetIsShowingInputViewForFocusedElement; }
    static constexpr bool isSync = false;

    explicit SetIsShowingInputViewForFocusedElement(bool showingInputView)
        : m_arguments(showingInputView)
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

#if PLATFORM(IOS_FAMILY)
class UpdateSelectionWithDelta {
public:
    using Arguments = std::tuple<int64_t, int64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateSelectionWithDelta; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_UpdateSelectionWithDeltaReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    UpdateSelectionWithDelta(int64_t locationDelta, int64_t lengthDelta)
        : m_arguments(locationDelta, lengthDelta)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int64_t, int64_t> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class RequestDocumentEditingContext {
public:
    using Arguments = std::tuple<WebKit::DocumentEditingContextRequest>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestDocumentEditingContext; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RequestDocumentEditingContextReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::DocumentEditingContext>;
    explicit RequestDocumentEditingContext(const WebKit::DocumentEditingContextRequest& request)
        : m_arguments(request)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::DocumentEditingContextRequest&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class GenerateSyntheticEditingCommand {
public:
    using Arguments = std::tuple<WebKit::SyntheticEditingCommandType>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GenerateSyntheticEditingCommand; }
    static constexpr bool isSync = false;

    explicit GenerateSyntheticEditingCommand(WebKit::SyntheticEditingCommandType command)
        : m_arguments(command)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::SyntheticEditingCommandType> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class SetShouldRevealCurrentSelectionAfterInsertion {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetShouldRevealCurrentSelectionAfterInsertion; }
    static constexpr bool isSync = false;

    explicit SetShouldRevealCurrentSelectionAfterInsertion(bool shouldRevealCurrentSelectionAfterInsertion)
        : m_arguments(shouldRevealCurrentSelectionAfterInsertion)
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

#if PLATFORM(IOS_FAMILY)
class InsertTextPlaceholder {
public:
    using Arguments = std::tuple<WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_InsertTextPlaceholder; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_InsertTextPlaceholderReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ElementContext>>;
    explicit InsertTextPlaceholder(const WebCore::IntSize& size)
        : m_arguments(size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntSize&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class RemoveTextPlaceholder {
public:
    using Arguments = std::tuple<WebCore::ElementContext>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RemoveTextPlaceholder; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RemoveTextPlaceholderReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit RemoveTextPlaceholder(const WebCore::ElementContext& placeholder)
        : m_arguments(placeholder)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ElementContext&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class TextInputContextsInRect {
public:
    using Arguments = std::tuple<WebCore::FloatRect>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_TextInputContextsInRect; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_TextInputContextsInRectReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::ElementContext>>;
    explicit TextInputContextsInRect(const WebCore::FloatRect& rect)
        : m_arguments(rect)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class FocusTextInputContextAndPlaceCaret {
public:
    using Arguments = std::tuple<WebCore::ElementContext, WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_FocusTextInputContextAndPlaceCaret; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_FocusTextInputContextAndPlaceCaretReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    FocusTextInputContextAndPlaceCaret(const WebCore::ElementContext& context, const WebCore::IntPoint& point)
        : m_arguments(context, point)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ElementContext&, const WebCore::IntPoint&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY)
class ClearServiceWorkerEntitlementOverride {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ClearServiceWorkerEntitlementOverride; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ClearServiceWorkerEntitlementOverrideReply; }
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

class RequestImageBitmap {
public:
    using Arguments = std::tuple<WebCore::ElementContext>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestImageBitmap; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RequestImageBitmapReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::ShareableBitmap::Handle, String>;
    explicit RequestImageBitmap(const WebCore::ElementContext& elementContext)
        : m_arguments(elementContext)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ElementContext&> m_arguments;
};

class SetControlledByAutomation {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetControlledByAutomation; }
    static constexpr bool isSync = false;

    explicit SetControlledByAutomation(bool controlled)
        : m_arguments(controlled)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class ConnectInspector {
public:
    using Arguments = std::tuple<String, Inspector::FrontendChannel::ConnectionType>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ConnectInspector; }
    static constexpr bool isSync = false;

    ConnectInspector(const String& targetId, const Inspector::FrontendChannel::ConnectionType& connectionType)
        : m_arguments(targetId, connectionType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const Inspector::FrontendChannel::ConnectionType&> m_arguments;
};

class DisconnectInspector {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DisconnectInspector; }
    static constexpr bool isSync = false;

    explicit DisconnectInspector(const String& targetId)
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

class SendMessageToTargetBackend {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SendMessageToTargetBackend; }
    static constexpr bool isSync = false;

    SendMessageToTargetBackend(const String& targetId, const String& message)
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

#if ENABLE(REMOTE_INSPECTOR)
class SetIndicating {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetIndicating; }
    static constexpr bool isSync = false;

    explicit SetIndicating(bool indicating)
        : m_arguments(indicating)
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

#if ENABLE(IOS_TOUCH_EVENTS)
class ResetPotentialTapSecurityOrigin {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ResetPotentialTapSecurityOrigin; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if !ENABLE(IOS_TOUCH_EVENTS) && ENABLE(TOUCH_EVENTS)
class TouchEvent {
public:
    using Arguments = std::tuple<WebKit::WebTouchEvent>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_TouchEvent; }
    static constexpr bool isSync = false;

    explicit TouchEvent(const WebKit::WebTouchEvent& event)
        : m_arguments(event)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebTouchEvent&> m_arguments;
};
#endif

class CancelPointer {
public:
    using Arguments = std::tuple<WebCore::PointerID, WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CancelPointer; }
    static constexpr bool isSync = false;

    CancelPointer(const WebCore::PointerID& pointerId, const WebCore::IntPoint& documentPoint)
        : m_arguments(pointerId, documentPoint)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PointerID&, const WebCore::IntPoint&> m_arguments;
};

class TouchWithIdentifierWasRemoved {
public:
    using Arguments = std::tuple<WebCore::PointerID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_TouchWithIdentifierWasRemoved; }
    static constexpr bool isSync = false;

    explicit TouchWithIdentifierWasRemoved(const WebCore::PointerID& pointerId)
        : m_arguments(pointerId)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PointerID&> m_arguments;
};

#if ENABLE(INPUT_TYPE_COLOR)
class DidEndColorPicker {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidEndColorPicker; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(INPUT_TYPE_COLOR)
class DidChooseColor {
public:
    using Arguments = std::tuple<WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidChooseColor; }
    static constexpr bool isSync = false;

    explicit DidChooseColor(const WebCore::Color& color)
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

#if ENABLE(DATALIST_ELEMENT)
class DidSelectDataListOption {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidSelectDataListOption; }
    static constexpr bool isSync = false;

    explicit DidSelectDataListOption(const String& selectedOption)
        : m_arguments(selectedOption)
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
class DidCloseSuggestions {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidCloseSuggestions; }
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
class DidChooseDate {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidChooseDate; }
    static constexpr bool isSync = false;

    explicit DidChooseDate(const String& date)
        : m_arguments(date)
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

#if ENABLE(DATE_AND_TIME_INPUT_TYPES)
class DidEndDateTimePicker {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidEndDateTimePicker; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class ScrollBy {
public:
    using Arguments = std::tuple<uint32_t, WebCore::ScrollGranularity>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ScrollBy; }
    static constexpr bool isSync = false;

    ScrollBy(uint32_t scrollDirection, WebCore::ScrollGranularity scrollGranularity)
        : m_arguments(scrollDirection, scrollGranularity)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, WebCore::ScrollGranularity> m_arguments;
};

class CenterSelectionInVisibleArea {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CenterSelectionInVisibleArea; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class GoToBackForwardItem {
public:
    using Arguments = std::tuple<uint64_t, WebCore::BackForwardItemIdentifier, WebCore::FrameLoadType, WebCore::ShouldTreatAsContinuingLoad, std::optional<WebKit::WebsitePoliciesData>, bool, std::optional<WebKit::NetworkResourceLoadIdentifier>, std::optional<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GoToBackForwardItem; }
    static constexpr bool isSync = false;

    GoToBackForwardItem(uint64_t navigationID, const WebCore::BackForwardItemIdentifier& backForwardItemID, WebCore::FrameLoadType backForwardType, WebCore::ShouldTreatAsContinuingLoad shouldTreatAsContinuingLoad, const std::optional<WebKit::WebsitePoliciesData>& websitePolicies, bool lastNavigationWasAppInitiated, const std::optional<WebKit::NetworkResourceLoadIdentifier>& existingNetworkResourceLoadIdentifierToResume, const std::optional<String>& topPrivatelyControlledDomain)
        : m_arguments(navigationID, backForwardItemID, backForwardType, shouldTreatAsContinuingLoad, websitePolicies, lastNavigationWasAppInitiated, existingNetworkResourceLoadIdentifierToResume, topPrivatelyControlledDomain)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const WebCore::BackForwardItemIdentifier&, WebCore::FrameLoadType, WebCore::ShouldTreatAsContinuingLoad, const std::optional<WebKit::WebsitePoliciesData>&, bool, const std::optional<WebKit::NetworkResourceLoadIdentifier>&, const std::optional<String>&> m_arguments;
};

class TryRestoreScrollPosition {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_TryRestoreScrollPosition; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class LoadURLInFrame {
public:
    using Arguments = std::tuple<URL, String, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_LoadURLInFrame; }
    static constexpr bool isSync = false;

    LoadURLInFrame(const URL& url, const String& referrer, const WebCore::FrameIdentifier& frameID)
        : m_arguments(url, referrer, frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const URL&, const String&, const WebCore::FrameIdentifier&> m_arguments;
};

class LoadDataInFrame {
public:
    using Arguments = std::tuple<IPC::DataReference, String, String, URL, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_LoadDataInFrame; }
    static constexpr bool isSync = false;

    LoadDataInFrame(const IPC::DataReference& data, const String& MIMEType, const String& encodingName, const URL& baseURL, const WebCore::FrameIdentifier& frameID)
        : m_arguments(data, MIMEType, encodingName, baseURL, frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::DataReference&, const String&, const String&, const URL&, const WebCore::FrameIdentifier&> m_arguments;
};

class LoadRequest {
public:
    using Arguments = std::tuple<WebKit::LoadParameters>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_LoadRequest; }
    static constexpr bool isSync = false;

    explicit LoadRequest(const WebKit::LoadParameters& loadParameters)
        : m_arguments(loadParameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::LoadParameters&> m_arguments;
};

class TransitionFrameToLocal {
public:
    using Arguments = std::tuple<WebKit::LocalFrameCreationParameters, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_TransitionFrameToLocal; }
    static constexpr bool isSync = false;

    TransitionFrameToLocal(const WebKit::LocalFrameCreationParameters& creationParameters, const WebCore::FrameIdentifier& frameID)
        : m_arguments(creationParameters, frameID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::LocalFrameCreationParameters&, const WebCore::FrameIdentifier&> m_arguments;
};

class LoadRequestWaitingForProcessLaunch {
public:
    using Arguments = std::tuple<WebKit::LoadParameters, URL, WebKit::WebPageProxyIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_LoadRequestWaitingForProcessLaunch; }
    static constexpr bool isSync = false;

    LoadRequestWaitingForProcessLaunch(const WebKit::LoadParameters& loadParameters, const URL& resourceDirectoryURL, const WebKit::WebPageProxyIdentifier& pageID, bool checkAssumedReadAccessToResourceURL)
        : m_arguments(loadParameters, resourceDirectoryURL, pageID, checkAssumedReadAccessToResourceURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::LoadParameters&, const URL&, const WebKit::WebPageProxyIdentifier&, bool> m_arguments;
};

class LoadData {
public:
    using Arguments = std::tuple<WebKit::LoadParameters>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_LoadData; }
    static constexpr bool isSync = false;

    explicit LoadData(const WebKit::LoadParameters& loadParameters)
        : m_arguments(loadParameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::LoadParameters&> m_arguments;
};

class LoadSimulatedRequestAndResponse {
public:
    using Arguments = std::tuple<WebKit::LoadParameters, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_LoadSimulatedRequestAndResponse; }
    static constexpr bool isSync = false;

    LoadSimulatedRequestAndResponse(const WebKit::LoadParameters& loadParameters, const WebCore::ResourceResponse& simulatedResponse)
        : m_arguments(loadParameters, simulatedResponse)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::LoadParameters&, const WebCore::ResourceResponse&> m_arguments;
};

class LoadAlternateHTML {
public:
    using Arguments = std::tuple<WebKit::LoadParameters>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_LoadAlternateHTML; }
    static constexpr bool isSync = false;

    explicit LoadAlternateHTML(const WebKit::LoadParameters& loadParameters)
        : m_arguments(loadParameters)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::LoadParameters&> m_arguments;
};

class CreateRemoteSubframe {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CreateRemoteSubframe; }
    static constexpr bool isSync = false;

    CreateRemoteSubframe(const WebCore::FrameIdentifier& parentID, const WebCore::FrameIdentifier& newChildID)
        : m_arguments(parentID, newChildID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebCore::FrameIdentifier&> m_arguments;
};

class GetFrameInfo {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetFrameInfo; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetFrameInfoReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::FrameInfoData>;
    explicit GetFrameInfo(const WebCore::FrameIdentifier& frameID)
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

class GetFrameTree {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetFrameTree; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetFrameTreeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::FrameTreeNodeData>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidCommitLoadInAnotherProcess {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, std::optional<WebCore::LayerHostingContextIdentifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidCommitLoadInAnotherProcess; }
    static constexpr bool isSync = false;

    DidCommitLoadInAnotherProcess(const WebCore::FrameIdentifier& frameID, const std::optional<WebCore::LayerHostingContextIdentifier>& layerHostingContextIdentifier)
        : m_arguments(frameID, layerHostingContextIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const std::optional<WebCore::LayerHostingContextIdentifier>&> m_arguments;
};

class DidFinishLoadInAnotherProcess {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidFinishLoadInAnotherProcess; }
    static constexpr bool isSync = false;

    explicit DidFinishLoadInAnotherProcess(const WebCore::FrameIdentifier& frameID)
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

class FrameWasRemovedInAnotherProcess {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_FrameWasRemovedInAnotherProcess; }
    static constexpr bool isSync = false;

    explicit FrameWasRemovedInAnotherProcess(const WebCore::FrameIdentifier& frameID)
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

class NavigateToPDFLinkWithSimulatedClick {
public:
    using Arguments = std::tuple<String, WebCore::IntPoint, WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_NavigateToPDFLinkWithSimulatedClick; }
    static constexpr bool isSync = false;

    NavigateToPDFLinkWithSimulatedClick(const String& url, const WebCore::IntPoint& documentPoint, const WebCore::IntPoint& screenPoint)
        : m_arguments(url, documentPoint, screenPoint)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::IntPoint&, const WebCore::IntPoint&> m_arguments;
};

class GetPDFFirstPageSize {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetPDFFirstPageSize; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetPDFFirstPageSizeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::FloatSize>;
    explicit GetPDFFirstPageSize(const WebCore::FrameIdentifier& frameID)
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

class Reload {
public:
    using Arguments = std::tuple<uint64_t, OptionSet<WebCore::ReloadOption>, WebKit::SandboxExtension::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_Reload; }
    static constexpr bool isSync = false;

    Reload(uint64_t navigationID, const OptionSet<WebCore::ReloadOption>& reloadOptions, const WebKit::SandboxExtension::Handle& sandboxExtensionHandle)
        : m_arguments(navigationID, reloadOptions, sandboxExtensionHandle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t, const OptionSet<WebCore::ReloadOption>&, const WebKit::SandboxExtension::Handle&> m_arguments;
};

class StopLoading {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_StopLoading; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class StopLoadingDueToProcessSwap {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_StopLoadingDueToProcessSwap; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RestoreSession {
public:
    using Arguments = std::tuple<Vector<WebKit::BackForwardListItemState>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RestoreSession; }
    static constexpr bool isSync = false;

    explicit RestoreSession(const Vector<WebKit::BackForwardListItemState>& itemStates)
        : m_arguments(itemStates)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::BackForwardListItemState>&> m_arguments;
};

class UpdateBackForwardListForReattach {
public:
    using Arguments = std::tuple<Vector<WebKit::BackForwardListItemState>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateBackForwardListForReattach; }
    static constexpr bool isSync = false;

    explicit UpdateBackForwardListForReattach(const Vector<WebKit::BackForwardListItemState>& itemStates)
        : m_arguments(itemStates)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebKit::BackForwardListItemState>&> m_arguments;
};

class SetCurrentHistoryItemForReattach {
public:
    using Arguments = std::tuple<WebKit::BackForwardListItemState>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetCurrentHistoryItemForReattach; }
    static constexpr bool isSync = false;

    explicit SetCurrentHistoryItemForReattach(const WebKit::BackForwardListItemState& itemState)
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

class DidRemoveBackForwardItem {
public:
    using Arguments = std::tuple<WebCore::BackForwardItemIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidRemoveBackForwardItem; }
    static constexpr bool isSync = false;

    explicit DidRemoveBackForwardItem(const WebCore::BackForwardItemIdentifier& backForwardItemID)
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

class UpdateWebsitePolicies {
public:
    using Arguments = std::tuple<WebKit::WebsitePoliciesData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateWebsitePolicies; }
    static constexpr bool isSync = false;

    explicit UpdateWebsitePolicies(const WebKit::WebsitePoliciesData& websitePolicies)
        : m_arguments(websitePolicies)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebsitePoliciesData&> m_arguments;
};

class NotifyUserScripts {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_NotifyUserScripts; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ClearSelection {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ClearSelection; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RestoreSelectionInFocusedEditableElement {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RestoreSelectionInFocusedEditableElement; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class GetContentsAsString {
public:
    using Arguments = std::tuple<WebKit::ContentAsStringIncludesChildFrames>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetContentsAsString; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetContentsAsStringReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit GetContentsAsString(WebKit::ContentAsStringIncludesChildFrames inChildFrames)
        : m_arguments(inChildFrames)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::ContentAsStringIncludesChildFrames> m_arguments;
};

#if PLATFORM(COCOA)
class GetContentsAsAttributedString {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetContentsAsAttributedString; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetContentsAsAttributedStringReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::AttributedString>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(MHTML)
class GetContentsAsMHTMLData {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetContentsAsMHTMLData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetContentsAsMHTMLDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::SharedBufferReference>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class GetMainResourceDataOfFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetMainResourceDataOfFrame; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetMainResourceDataOfFrameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<IPC::SharedBufferReference>>;
    explicit GetMainResourceDataOfFrame(const WebCore::FrameIdentifier& frameID)
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

class GetResourceDataFromFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetResourceDataFromFrame; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetResourceDataFromFrameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<IPC::SharedBufferReference>>;
    GetResourceDataFromFrame(const WebCore::FrameIdentifier& frameID, const String& resourceURL)
        : m_arguments(frameID, resourceURL)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const String&> m_arguments;
};

class GetRenderTreeExternalRepresentation {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetRenderTreeExternalRepresentation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetRenderTreeExternalRepresentationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class GetSelectionOrContentsAsString {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetSelectionOrContentsAsString; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetSelectionOrContentsAsStringReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class GetSelectionAsWebArchiveData {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetSelectionAsWebArchiveData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetSelectionAsWebArchiveDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<IPC::SharedBufferReference>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class GetSourceForFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetSourceForFrame; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetSourceForFrameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    explicit GetSourceForFrame(const WebCore::FrameIdentifier& frameID)
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

class GetWebArchiveOfFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetWebArchiveOfFrame; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetWebArchiveOfFrameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<IPC::SharedBufferReference>>;
    explicit GetWebArchiveOfFrame(const WebCore::FrameIdentifier& frameID)
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

class RunJavaScriptInFrameInScriptWorld {
public:
    using Arguments = std::tuple<WebCore::RunJavaScriptParameters, std::optional<WebCore::FrameIdentifier>, std::pair<WebKit::ContentWorldIdentifier, String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RunJavaScriptInFrameInScriptWorld; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RunJavaScriptInFrameInScriptWorldReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::DataReference, std::optional<WebCore::ExceptionDetails>>;
    RunJavaScriptInFrameInScriptWorld(const WebCore::RunJavaScriptParameters& parameters, const std::optional<WebCore::FrameIdentifier>& frameID, const std::pair<WebKit::ContentWorldIdentifier, String>& world)
        : m_arguments(parameters, frameID, world)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::RunJavaScriptParameters&, const std::optional<WebCore::FrameIdentifier>&, const std::pair<WebKit::ContentWorldIdentifier, String>&> m_arguments;
};

class GetAccessibilityTreeData {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetAccessibilityTreeData; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetAccessibilityTreeDataReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<IPC::SharedBufferReference>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ForceRepaint {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ForceRepaint; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ForceRepaintReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SelectAll {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SelectAll; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ScheduleFullEditorStateUpdate {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ScheduleFullEditorStateUpdate; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if PLATFORM(COCOA)
class PerformDictionaryLookupOfCurrentSelection {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PerformDictionaryLookupOfCurrentSelection; }
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
class PerformDictionaryLookupAtLocation {
public:
    using Arguments = std::tuple<WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PerformDictionaryLookupAtLocation; }
    static constexpr bool isSync = false;

    explicit PerformDictionaryLookupAtLocation(const WebCore::FloatPoint& point)
        : m_arguments(point)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatPoint&> m_arguments;
};
#endif

#if ENABLE(DATA_DETECTION)
class DetectDataInAllFrames {
public:
    using Arguments = std::tuple<OptionSet<WebCore::DataDetectorType>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DetectDataInAllFrames; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DetectDataInAllFramesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::DataDetectionResult>;
    explicit DetectDataInAllFrames(const OptionSet<WebCore::DataDetectorType>& types)
        : m_arguments(types)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebCore::DataDetectorType>&> m_arguments;
};
#endif

#if ENABLE(DATA_DETECTION)
class RemoveDataDetectedLinks {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RemoveDataDetectedLinks; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RemoveDataDetectedLinksReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::DataDetectionResult>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class ChangeFont {
public:
    using Arguments = std::tuple<WebCore::FontChanges>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ChangeFont; }
    static constexpr bool isSync = false;

    explicit ChangeFont(const WebCore::FontChanges& changes)
        : m_arguments(changes)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FontChanges&> m_arguments;
};

class ChangeFontAttributes {
public:
    using Arguments = std::tuple<WebCore::FontAttributeChanges>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ChangeFontAttributes; }
    static constexpr bool isSync = false;

    explicit ChangeFontAttributes(const WebCore::FontAttributeChanges& changes)
        : m_arguments(changes)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FontAttributeChanges&> m_arguments;
};

class PreferencesDidChange {
public:
    using Arguments = std::tuple<WebKit::WebPreferencesStore>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PreferencesDidChange; }
    static constexpr bool isSync = false;

    explicit PreferencesDidChange(const WebKit::WebPreferencesStore& store)
        : m_arguments(store)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPreferencesStore&> m_arguments;
};

class PreferencesDidChangeDuringDOMPrintOperation {
public:
    using Arguments = std::tuple<WebKit::WebPreferencesStore>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PreferencesDidChangeDuringDOMPrintOperation; }
    static constexpr bool isSync = false;

    explicit PreferencesDidChangeDuringDOMPrintOperation(const WebKit::WebPreferencesStore& store)
        : m_arguments(store)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebPreferencesStore&> m_arguments;
};

class SetUserAgent {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetUserAgent; }
    static constexpr bool isSync = false;

    explicit SetUserAgent(const String& userAgent)
        : m_arguments(userAgent)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class SetCustomTextEncodingName {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetCustomTextEncodingName; }
    static constexpr bool isSync = false;

    explicit SetCustomTextEncodingName(const String& encodingName)
        : m_arguments(encodingName)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class SuspendActiveDOMObjectsAndAnimations {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SuspendActiveDOMObjectsAndAnimations; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ResumeActiveDOMObjectsAndAnimations {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ResumeActiveDOMObjectsAndAnimations; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Suspend {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_Suspend; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SuspendReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Resume {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_Resume; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ResumeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class Close {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_Close; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class TryClose {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_TryClose; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_TryCloseReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetEditable {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetEditable; }
    static constexpr bool isSync = false;

    explicit SetEditable(bool editable)
        : m_arguments(editable)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class ValidateCommand {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ValidateCommand; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ValidateCommandReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool, int32_t>;
    explicit ValidateCommand(const String& name)
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

class ExecuteEditCommand {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ExecuteEditCommand; }
    static constexpr bool isSync = false;

    ExecuteEditCommand(const String& name, const String& argument)
        : m_arguments(name, argument)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&> m_arguments;
};

class IncreaseListLevel {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_IncreaseListLevel; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DecreaseListLevel {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DecreaseListLevel; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ChangeListType {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ChangeListType; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetBaseWritingDirection {
public:
    using Arguments = std::tuple<WebCore::WritingDirection>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetBaseWritingDirection; }
    static constexpr bool isSync = false;

    explicit SetBaseWritingDirection(WebCore::WritingDirection direction)
        : m_arguments(direction)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::WritingDirection> m_arguments;
};

class SetNeedsFontAttributes {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetNeedsFontAttributes; }
    static constexpr bool isSync = false;

    explicit SetNeedsFontAttributes(bool needsFontAttributes)
        : m_arguments(needsFontAttributes)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class RequestFontAttributesAtSelectionStart {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestFontAttributesAtSelectionStart; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RequestFontAttributesAtSelectionStartReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::FontAttributes>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidRemoveEditCommand {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidRemoveEditCommand; }
    static constexpr bool isSync = false;

    explicit DidRemoveEditCommand(uint64_t commandID)
        : m_arguments(commandID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class ReapplyEditCommand {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ReapplyEditCommand; }
    static constexpr bool isSync = false;

    explicit ReapplyEditCommand(uint64_t commandID)
        : m_arguments(commandID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class UnapplyEditCommand {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UnapplyEditCommand; }
    static constexpr bool isSync = false;

    explicit UnapplyEditCommand(uint64_t commandID)
        : m_arguments(commandID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint64_t> m_arguments;
};

class SetPageAndTextZoomFactors {
public:
    using Arguments = std::tuple<double, double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetPageAndTextZoomFactors; }
    static constexpr bool isSync = false;

    SetPageAndTextZoomFactors(double pageZoomFactor, double textZoomFactor)
        : m_arguments(pageZoomFactor, textZoomFactor)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double, double> m_arguments;
};

class SetPageZoomFactor {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetPageZoomFactor; }
    static constexpr bool isSync = false;

    explicit SetPageZoomFactor(double zoomFactor)
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

class SetTextZoomFactor {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetTextZoomFactor; }
    static constexpr bool isSync = false;

    explicit SetTextZoomFactor(double zoomFactor)
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

class WindowScreenDidChange {
public:
    using Arguments = std::tuple<uint32_t, std::optional<unsigned>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_WindowScreenDidChange; }
    static constexpr bool isSync = false;

    WindowScreenDidChange(uint32_t displayID, const std::optional<unsigned>& nominalFramesPerSecond)
        : m_arguments(displayID, nominalFramesPerSecond)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t, const std::optional<unsigned>&> m_arguments;
};

class AccessibilitySettingsDidChange {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_AccessibilitySettingsDidChange; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ScalePage {
public:
    using Arguments = std::tuple<double, WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ScalePage; }
    static constexpr bool isSync = false;

    ScalePage(double scale, const WebCore::IntPoint& origin)
        : m_arguments(scale, origin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double, const WebCore::IntPoint&> m_arguments;
};

class ScalePageInViewCoordinates {
public:
    using Arguments = std::tuple<double, WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ScalePageInViewCoordinates; }
    static constexpr bool isSync = false;

    ScalePageInViewCoordinates(double scale, const WebCore::IntPoint& centerInViewCoordinates)
        : m_arguments(scale, centerInViewCoordinates)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double, const WebCore::IntPoint&> m_arguments;
};

class ScaleView {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ScaleView; }
    static constexpr bool isSync = false;

    explicit ScaleView(double scale)
        : m_arguments(scale)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class SetUseFixedLayout {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetUseFixedLayout; }
    static constexpr bool isSync = false;

    explicit SetUseFixedLayout(bool fixed)
        : m_arguments(fixed)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetFixedLayoutSize {
public:
    using Arguments = std::tuple<WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetFixedLayoutSize; }
    static constexpr bool isSync = false;

    explicit SetFixedLayoutSize(const WebCore::IntSize& size)
        : m_arguments(size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntSize&> m_arguments;
};

class SetDefaultUnobscuredSize {
public:
    using Arguments = std::tuple<WebCore::FloatSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetDefaultUnobscuredSize; }
    static constexpr bool isSync = false;

    explicit SetDefaultUnobscuredSize(const WebCore::FloatSize& size)
        : m_arguments(size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatSize&> m_arguments;
};

class SetMinimumUnobscuredSize {
public:
    using Arguments = std::tuple<WebCore::FloatSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetMinimumUnobscuredSize; }
    static constexpr bool isSync = false;

    explicit SetMinimumUnobscuredSize(const WebCore::FloatSize& size)
        : m_arguments(size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatSize&> m_arguments;
};

class SetMaximumUnobscuredSize {
public:
    using Arguments = std::tuple<WebCore::FloatSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetMaximumUnobscuredSize; }
    static constexpr bool isSync = false;

    explicit SetMaximumUnobscuredSize(const WebCore::FloatSize& size)
        : m_arguments(size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatSize&> m_arguments;
};

class ListenForLayoutMilestones {
public:
    using Arguments = std::tuple<OptionSet<WebCore::LayoutMilestone>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ListenForLayoutMilestones; }
    static constexpr bool isSync = false;

    explicit ListenForLayoutMilestones(const OptionSet<WebCore::LayoutMilestone>& layoutMilestones)
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

class SetSuppressScrollbarAnimations {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetSuppressScrollbarAnimations; }
    static constexpr bool isSync = false;

    explicit SetSuppressScrollbarAnimations(bool suppressAnimations)
        : m_arguments(suppressAnimations)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetEnableVerticalRubberBanding {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetEnableVerticalRubberBanding; }
    static constexpr bool isSync = false;

    explicit SetEnableVerticalRubberBanding(bool enableVerticalRubberBanding)
        : m_arguments(enableVerticalRubberBanding)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetEnableHorizontalRubberBanding {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetEnableHorizontalRubberBanding; }
    static constexpr bool isSync = false;

    explicit SetEnableHorizontalRubberBanding(bool enableHorizontalRubberBanding)
        : m_arguments(enableHorizontalRubberBanding)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetBackgroundExtendsBeyondPage {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetBackgroundExtendsBeyondPage; }
    static constexpr bool isSync = false;

    explicit SetBackgroundExtendsBeyondPage(bool backgroundExtendsBeyondPage)
        : m_arguments(backgroundExtendsBeyondPage)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetPaginationMode {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetPaginationMode; }
    static constexpr bool isSync = false;

    explicit SetPaginationMode(uint32_t mode)
        : m_arguments(mode)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class SetPaginationBehavesLikeColumns {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetPaginationBehavesLikeColumns; }
    static constexpr bool isSync = false;

    explicit SetPaginationBehavesLikeColumns(bool behavesLikeColumns)
        : m_arguments(behavesLikeColumns)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetPageLength {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetPageLength; }
    static constexpr bool isSync = false;

    explicit SetPageLength(double pageLength)
        : m_arguments(pageLength)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class SetGapBetweenPages {
public:
    using Arguments = std::tuple<double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetGapBetweenPages; }
    static constexpr bool isSync = false;

    explicit SetGapBetweenPages(double gap)
        : m_arguments(gap)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double> m_arguments;
};

class PostInjectedBundleMessage {
public:
    using Arguments = std::tuple<String, WebKit::UserData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PostInjectedBundleMessage; }
    static constexpr bool isSync = false;

    PostInjectedBundleMessage(const String& messageName, const WebKit::UserData& messageBody)
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

class FindString {
public:
    using Arguments = std::tuple<String, OptionSet<WebKit::FindOptions>, unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_FindString; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_FindStringReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    FindString(const String& string, const OptionSet<WebKit::FindOptions>& findOptions, const unsigned& maxMatchCount)
        : m_arguments(string, findOptions, maxMatchCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const OptionSet<WebKit::FindOptions>&, const unsigned&> m_arguments;
};

class FindStringMatches {
public:
    using Arguments = std::tuple<String, OptionSet<WebKit::FindOptions>, unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_FindStringMatches; }
    static constexpr bool isSync = false;

    FindStringMatches(const String& string, const OptionSet<WebKit::FindOptions>& findOptions, const unsigned& maxMatchCount)
        : m_arguments(string, findOptions, maxMatchCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const OptionSet<WebKit::FindOptions>&, const unsigned&> m_arguments;
};

class GetImageForFindMatch {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetImageForFindMatch; }
    static constexpr bool isSync = false;

    explicit GetImageForFindMatch(uint32_t matchIndex)
        : m_arguments(matchIndex)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class SelectFindMatch {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SelectFindMatch; }
    static constexpr bool isSync = false;

    explicit SelectFindMatch(uint32_t matchIndex)
        : m_arguments(matchIndex)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class IndicateFindMatch {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_IndicateFindMatch; }
    static constexpr bool isSync = false;

    explicit IndicateFindMatch(uint32_t matchIndex)
        : m_arguments(matchIndex)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class HideFindUI {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_HideFindUI; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class CountStringMatches {
public:
    using Arguments = std::tuple<String, OptionSet<WebKit::FindOptions>, unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CountStringMatches; }
    static constexpr bool isSync = false;

    CountStringMatches(const String& string, const OptionSet<WebKit::FindOptions>& findOptions, const unsigned& maxMatchCount)
        : m_arguments(string, findOptions, maxMatchCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const OptionSet<WebKit::FindOptions>&, const unsigned&> m_arguments;
};

class ReplaceMatches {
public:
    using Arguments = std::tuple<Vector<uint32_t>, String, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ReplaceMatches; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ReplaceMatchesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    ReplaceMatches(const Vector<uint32_t>& matchIndices, const String& replacementText, bool selectionOnly)
        : m_arguments(matchIndices, replacementText, selectionOnly)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<uint32_t>&, const String&, bool> m_arguments;
};

class FindRectsForStringMatches {
public:
    using Arguments = std::tuple<String, OptionSet<WebKit::FindOptions>, unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_FindRectsForStringMatches; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_FindRectsForStringMatchesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::FloatRect>>;
    FindRectsForStringMatches(const String& string, const OptionSet<WebKit::FindOptions>& findOptions, const unsigned& maxMatchCount)
        : m_arguments(string, findOptions, maxMatchCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const OptionSet<WebKit::FindOptions>&, const unsigned&> m_arguments;
};

class HideFindIndicator {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_HideFindIndicator; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class FindTextRangesForStringMatches {
public:
    using Arguments = std::tuple<String, OptionSet<WebKit::FindOptions>, unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_FindTextRangesForStringMatches; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_FindTextRangesForStringMatchesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebKit::WebFoundTextRange>>;
    FindTextRangesForStringMatches(const String& string, const OptionSet<WebKit::FindOptions>& findOptions, const unsigned& maxMatchCount)
        : m_arguments(string, findOptions, maxMatchCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const OptionSet<WebKit::FindOptions>&, const unsigned&> m_arguments;
};

class ReplaceFoundTextRangeWithString {
public:
    using Arguments = std::tuple<WebKit::WebFoundTextRange, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ReplaceFoundTextRangeWithString; }
    static constexpr bool isSync = false;

    ReplaceFoundTextRangeWithString(const WebKit::WebFoundTextRange& range, const String& string)
        : m_arguments(range, string)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebFoundTextRange&, const String&> m_arguments;
};

class DecorateTextRangeWithStyle {
public:
    using Arguments = std::tuple<WebKit::WebFoundTextRange, WebKit::FindDecorationStyle>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DecorateTextRangeWithStyle; }
    static constexpr bool isSync = false;

    DecorateTextRangeWithStyle(const WebKit::WebFoundTextRange& range, WebKit::FindDecorationStyle style)
        : m_arguments(range, style)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebFoundTextRange&, WebKit::FindDecorationStyle> m_arguments;
};

class ScrollTextRangeToVisible {
public:
    using Arguments = std::tuple<WebKit::WebFoundTextRange>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ScrollTextRangeToVisible; }
    static constexpr bool isSync = false;

    explicit ScrollTextRangeToVisible(const WebKit::WebFoundTextRange& range)
        : m_arguments(range)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebFoundTextRange&> m_arguments;
};

class ClearAllDecoratedFoundText {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ClearAllDecoratedFoundText; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidBeginTextSearchOperation {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidBeginTextSearchOperation; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class DidEndTextSearchOperation {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidEndTextSearchOperation; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RequestRectForFoundTextRange {
public:
    using Arguments = std::tuple<WebKit::WebFoundTextRange>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestRectForFoundTextRange; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RequestRectForFoundTextRangeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::FloatRect>;
    explicit RequestRectForFoundTextRange(const WebKit::WebFoundTextRange& range)
        : m_arguments(range)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebFoundTextRange&> m_arguments;
};

class AddLayerForFindOverlay {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_AddLayerForFindOverlay; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_AddLayerForFindOverlayReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::PlatformLayerIdentifier>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class RemoveLayerForFindOverlay {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RemoveLayerForFindOverlay; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RemoveLayerForFindOverlayReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class AddMIMETypeWithCustomContentProvider {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_AddMIMETypeWithCustomContentProvider; }
    static constexpr bool isSync = false;

    explicit AddMIMETypeWithCustomContentProvider(const String& mimeType)
        : m_arguments(mimeType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

#if PLATFORM(GTK) && ENABLE(DRAG_SUPPORT)
class PerformDragControllerAction {
public:
    using Arguments = std::tuple<WebKit::DragControllerAction, WebCore::IntPoint, WebCore::IntPoint, OptionSet<WebCore::DragOperation>, WebCore::SelectionData, OptionSet<WebCore::DragApplicationFlags>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PerformDragControllerAction; }
    static constexpr bool isSync = false;

    PerformDragControllerAction(WebKit::DragControllerAction action, const WebCore::IntPoint& clientPosition, const WebCore::IntPoint& globalPosition, const OptionSet<WebCore::DragOperation>& draggingSourceOperationMask, const WebCore::SelectionData& selection, const OptionSet<WebCore::DragApplicationFlags>& flags)
        : m_arguments(action, clientPosition, globalPosition, draggingSourceOperationMask, selection, flags)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::DragControllerAction, const WebCore::IntPoint&, const WebCore::IntPoint&, const OptionSet<WebCore::DragOperation>&, const WebCore::SelectionData&, const OptionSet<WebCore::DragApplicationFlags>&> m_arguments;
};
#endif

#if !PLATFORM(GTK) && ENABLE(DRAG_SUPPORT)
class PerformDragControllerAction {
public:
    using Arguments = std::tuple<WebKit::DragControllerAction, WebCore::DragData, WebKit::SandboxExtension::Handle, Vector<WebKit::SandboxExtension::Handle>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PerformDragControllerAction; }
    static constexpr bool isSync = false;

    PerformDragControllerAction(WebKit::DragControllerAction action, const WebCore::DragData& dragData, const WebKit::SandboxExtension::Handle& sandboxExtensionHandle, const Vector<WebKit::SandboxExtension::Handle>& sandboxExtensionsForUpload)
        : m_arguments(action, dragData, sandboxExtensionHandle, sandboxExtensionsForUpload)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebKit::DragControllerAction, const WebCore::DragData&, const WebKit::SandboxExtension::Handle&, const Vector<WebKit::SandboxExtension::Handle>&> m_arguments;
};
#endif

#if ENABLE(DRAG_SUPPORT)
class DidStartDrag {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidStartDrag; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(DRAG_SUPPORT)
class DragEnded {
public:
    using Arguments = std::tuple<WebCore::IntPoint, WebCore::IntPoint, OptionSet<WebCore::DragOperation>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DragEnded; }
    static constexpr bool isSync = false;

    DragEnded(const WebCore::IntPoint& clientPosition, const WebCore::IntPoint& globalPosition, const OptionSet<WebCore::DragOperation>& dragOperationMask)
        : m_arguments(clientPosition, globalPosition, dragOperationMask)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, const WebCore::IntPoint&, const OptionSet<WebCore::DragOperation>&> m_arguments;
};
#endif

#if ENABLE(DRAG_SUPPORT)
class DragCancelled {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DragCancelled; }
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
class RequestDragStart {
public:
    using Arguments = std::tuple<WebCore::IntPoint, WebCore::IntPoint, OptionSet<WebCore::DragSourceAction>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestDragStart; }
    static constexpr bool isSync = false;

    RequestDragStart(const WebCore::IntPoint& clientPosition, const WebCore::IntPoint& globalPosition, const OptionSet<WebCore::DragSourceAction>& allowedActionsMask)
        : m_arguments(clientPosition, globalPosition, allowedActionsMask)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, const WebCore::IntPoint&, const OptionSet<WebCore::DragSourceAction>&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
class RequestAdditionalItemsForDragSession {
public:
    using Arguments = std::tuple<WebCore::IntPoint, WebCore::IntPoint, OptionSet<WebCore::DragSourceAction>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestAdditionalItemsForDragSession; }
    static constexpr bool isSync = false;

    RequestAdditionalItemsForDragSession(const WebCore::IntPoint& clientPosition, const WebCore::IntPoint& globalPosition, const OptionSet<WebCore::DragSourceAction>& allowedActionsMask)
        : m_arguments(clientPosition, globalPosition, allowedActionsMask)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntPoint&, const WebCore::IntPoint&, const OptionSet<WebCore::DragSourceAction>&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
class InsertDroppedImagePlaceholders {
public:
    using Arguments = std::tuple<Vector<WebCore::IntSize>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_InsertDroppedImagePlaceholders; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_InsertDroppedImagePlaceholdersReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::IntRect>, std::optional<WebCore::TextIndicatorData>>;
    explicit InsertDroppedImagePlaceholders(const Vector<WebCore::IntSize>& imageSize)
        : m_arguments(imageSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::IntSize>&> m_arguments;
};
#endif

#if PLATFORM(IOS_FAMILY) && ENABLE(DRAG_SUPPORT)
class DidConcludeDrop {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidConcludeDrop; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class DidChangeSelectedIndexForActivePopupMenu {
public:
    using Arguments = std::tuple<int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidChangeSelectedIndexForActivePopupMenu; }
    static constexpr bool isSync = false;

    explicit DidChangeSelectedIndexForActivePopupMenu(int32_t newIndex)
        : m_arguments(newIndex)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t> m_arguments;
};

class SetTextForActivePopupMenu {
public:
    using Arguments = std::tuple<int32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetTextForActivePopupMenu; }
    static constexpr bool isSync = false;

    explicit SetTextForActivePopupMenu(int32_t index)
        : m_arguments(index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int32_t> m_arguments;
};

#if PLATFORM(GTK)
class FailedToShowPopupMenu {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_FailedToShowPopupMenu; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(CONTEXT_MENUS)
class DidShowContextMenu {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidShowContextMenu; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(CONTEXT_MENUS)
class DidDismissContextMenu {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidDismissContextMenu; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(CONTEXT_MENUS)
class DidSelectItemFromActiveContextMenu {
public:
    using Arguments = std::tuple<WebKit::WebContextMenuItemData>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidSelectItemFromActiveContextMenu; }
    static constexpr bool isSync = false;

    explicit DidSelectItemFromActiveContextMenu(const WebKit::WebContextMenuItemData& menuItem)
        : m_arguments(menuItem)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebContextMenuItemData&> m_arguments;
};
#endif

#if ENABLE(CONTEXT_MENUS)
class ContextMenuForKeyEvent {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ContextMenuForKeyEvent; }
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
class DidChooseFilesForOpenPanelWithDisplayStringAndIcon {
public:
    using Arguments = std::tuple<Vector<String>, String, IPC::DataReference, WebKit::SandboxExtension::Handle, WebKit::SandboxExtension::Handle, WebKit::SandboxExtension::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidChooseFilesForOpenPanelWithDisplayStringAndIcon; }
    static constexpr bool isSync = false;

    DidChooseFilesForOpenPanelWithDisplayStringAndIcon(const Vector<String>& fileURLs, const String& displayString, const IPC::DataReference& iconData, const WebKit::SandboxExtension::Handle& machBootstrapHandle, const WebKit::SandboxExtension::Handle& frontboardServicesSandboxExtension, const WebKit::SandboxExtension::Handle& iconServicesSandboxExtension)
        : m_arguments(fileURLs, displayString, iconData, machBootstrapHandle, frontboardServicesSandboxExtension, iconServicesSandboxExtension)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&, const String&, const IPC::DataReference&, const WebKit::SandboxExtension::Handle&, const WebKit::SandboxExtension::Handle&, const WebKit::SandboxExtension::Handle&> m_arguments;
};
#endif

class DidChooseFilesForOpenPanel {
public:
    using Arguments = std::tuple<Vector<String>, Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidChooseFilesForOpenPanel; }
    static constexpr bool isSync = false;

    DidChooseFilesForOpenPanel(const Vector<String>& fileURLs, const Vector<String>& replacementURLs)
        : m_arguments(fileURLs, replacementURLs)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&, const Vector<String>&> m_arguments;
};

class DidCancelForOpenPanel {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidCancelForOpenPanel; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if ENABLE(SANDBOX_EXTENSIONS)
class ExtendSandboxForFilesFromOpenPanel {
public:
    using Arguments = std::tuple<Vector<WebKit::SandboxExtension::Handle>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ExtendSandboxForFilesFromOpenPanel; }
    static constexpr bool isSync = false;

    explicit ExtendSandboxForFilesFromOpenPanel(const Vector<WebKit::SandboxExtension::Handle>& sandboxExtensions)
        : m_arguments(sandboxExtensions)
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

class AdvanceToNextMisspelling {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_AdvanceToNextMisspelling; }
    static constexpr bool isSync = false;

    explicit AdvanceToNextMisspelling(bool startBeforeSelection)
        : m_arguments(startBeforeSelection)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class ChangeSpellingToWord {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ChangeSpellingToWord; }
    static constexpr bool isSync = false;

    explicit ChangeSpellingToWord(const String& word)
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

class DidFinishCheckingText {
public:
    using Arguments = std::tuple<WebKit::TextCheckerRequestID, Vector<WebCore::TextCheckingResult>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidFinishCheckingText; }
    static constexpr bool isSync = false;

    DidFinishCheckingText(const WebKit::TextCheckerRequestID& requestID, const Vector<WebCore::TextCheckingResult>& result)
        : m_arguments(requestID, result)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TextCheckerRequestID&, const Vector<WebCore::TextCheckingResult>&> m_arguments;
};

class DidCancelCheckingText {
public:
    using Arguments = std::tuple<WebKit::TextCheckerRequestID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidCancelCheckingText; }
    static constexpr bool isSync = false;

    explicit DidCancelCheckingText(const WebKit::TextCheckerRequestID& requestID)
        : m_arguments(requestID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::TextCheckerRequestID&> m_arguments;
};

#if USE(APPKIT)
class UppercaseWord {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UppercaseWord; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(APPKIT)
class LowercaseWord {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_LowercaseWord; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(APPKIT)
class CapitalizeWord {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CapitalizeWord; }
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
class SetSmartInsertDeleteEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetSmartInsertDeleteEnabled; }
    static constexpr bool isSync = false;

    explicit SetSmartInsertDeleteEnabled(bool isSmartInsertDeleteEnabled)
        : m_arguments(isSmartInsertDeleteEnabled)
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

#if ENABLE(GEOLOCATION)
class DidReceiveGeolocationPermissionDecision {
public:
    using Arguments = std::tuple<WebKit::GeolocationIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidReceiveGeolocationPermissionDecision; }
    static constexpr bool isSync = false;

    DidReceiveGeolocationPermissionDecision(const WebKit::GeolocationIdentifier& geolocationID, const String& authorizationToken)
        : m_arguments(geolocationID, authorizationToken)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::GeolocationIdentifier&, const String&> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class UserMediaAccessWasGranted {
public:
    using Arguments = std::tuple<WebCore::UserMediaRequestIdentifier, WebCore::CaptureDevice, WebCore::CaptureDevice, WebCore::MediaDeviceHashSalts, Vector<WebKit::SandboxExtension::Handle>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UserMediaAccessWasGranted; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_UserMediaAccessWasGrantedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    UserMediaAccessWasGranted(const WebCore::UserMediaRequestIdentifier& userMediaID, const WebCore::CaptureDevice& audioDevice, const WebCore::CaptureDevice& videoDevice, const WebCore::MediaDeviceHashSalts& mediaDeviceIdentifierHashSalts, const Vector<WebKit::SandboxExtension::Handle>& sandboxExtensionHandles)
        : m_arguments(userMediaID, audioDevice, videoDevice, mediaDeviceIdentifierHashSalts, sandboxExtensionHandles)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::UserMediaRequestIdentifier&, const WebCore::CaptureDevice&, const WebCore::CaptureDevice&, const WebCore::MediaDeviceHashSalts&, const Vector<WebKit::SandboxExtension::Handle>&> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class UserMediaAccessWasDenied {
public:
    using Arguments = std::tuple<WebCore::UserMediaRequestIdentifier, uint64_t, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UserMediaAccessWasDenied; }
    static constexpr bool isSync = false;

    UserMediaAccessWasDenied(const WebCore::UserMediaRequestIdentifier& userMediaID, uint64_t reason, const String& invalidConstraint)
        : m_arguments(userMediaID, reason, invalidConstraint)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::UserMediaRequestIdentifier&, uint64_t, const String&> m_arguments;
};
#endif

#if ENABLE(MEDIA_STREAM)
class CaptureDevicesChanged {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CaptureDevicesChanged; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if (ENABLE(MEDIA_STREAM) && USE(GSTREAMER))
class SetOrientationForMediaCapture {
public:
    using Arguments = std::tuple<uint64_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetOrientationForMediaCapture; }
    static constexpr bool isSync = false;

    explicit SetOrientationForMediaCapture(uint64_t rotation)
        : m_arguments(rotation)
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

#if (ENABLE(MEDIA_STREAM) && USE(GSTREAMER))
class SetMockCaptureDevicesInterrupted {
public:
    using Arguments = std::tuple<bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetMockCaptureDevicesInterrupted; }
    static constexpr bool isSync = false;

    SetMockCaptureDevicesInterrupted(bool isCameraInterrupted, bool isMicrophoneInterrupted)
        : m_arguments(isCameraInterrupted, isMicrophoneInterrupted)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool> m_arguments;
};
#endif

#if ENABLE(ENCRYPTED_MEDIA)
class MediaKeySystemWasGranted {
public:
    using Arguments = std::tuple<WebCore::MediaKeySystemRequestIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_MediaKeySystemWasGranted; }
    static constexpr bool isSync = false;

    explicit MediaKeySystemWasGranted(const WebCore::MediaKeySystemRequestIdentifier& mediaKeySystemID)
        : m_arguments(mediaKeySystemID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaKeySystemRequestIdentifier&> m_arguments;
};
#endif

#if ENABLE(ENCRYPTED_MEDIA)
class MediaKeySystemWasDenied {
public:
    using Arguments = std::tuple<WebCore::MediaKeySystemRequestIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_MediaKeySystemWasDenied; }
    static constexpr bool isSync = false;

    MediaKeySystemWasDenied(const WebCore::MediaKeySystemRequestIdentifier& mediaKeySystemID, const String& message)
        : m_arguments(mediaKeySystemID, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::MediaKeySystemRequestIdentifier&, const String&> m_arguments;
};
#endif

class RequestMediaPlaybackState {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestMediaPlaybackState; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RequestMediaPlaybackStateReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::MediaPlaybackState>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class PauseAllMediaPlayback {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PauseAllMediaPlayback; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_PauseAllMediaPlaybackReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SuspendAllMediaPlayback {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SuspendAllMediaPlayback; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SuspendAllMediaPlaybackReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ResumeAllMediaPlayback {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ResumeAllMediaPlayback; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ResumeAllMediaPlaybackReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class FreezeLayerTreeDueToSwipeAnimation {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_FreezeLayerTreeDueToSwipeAnimation; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class UnfreezeLayerTreeDueToSwipeAnimation {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UnfreezeLayerTreeDueToSwipeAnimation; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class IsLayerTreeFrozen {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_IsLayerTreeFrozen; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_IsLayerTreeFrozenReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class BeginPrinting {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_BeginPrinting; }
    static constexpr bool isSync = false;

    BeginPrinting(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo)
        : m_arguments(frameID, printInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&> m_arguments;
};

class BeginPrintingDuringDOMPrintOperation {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_BeginPrintingDuringDOMPrintOperation; }
    static constexpr bool isSync = false;

    BeginPrintingDuringDOMPrintOperation(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo)
        : m_arguments(frameID, printInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&> m_arguments;
};

class EndPrinting {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_EndPrinting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_EndPrintingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class EndPrintingDuringDOMPrintOperation {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_EndPrintingDuringDOMPrintOperation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_EndPrintingDuringDOMPrintOperationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class ComputePagesForPrinting {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ComputePagesForPrinting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ComputePagesForPrintingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::IntRect>, double, WebCore::RectEdges<float>>;
    ComputePagesForPrinting(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo)
        : m_arguments(frameID, printInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&> m_arguments;
};

class ComputePagesForPrintingDuringDOMPrintOperation {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ComputePagesForPrintingDuringDOMPrintOperation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ComputePagesForPrintingDuringDOMPrintOperationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::IntRect>, double, WebCore::RectEdges<float>>;
    ComputePagesForPrintingDuringDOMPrintOperation(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo)
        : m_arguments(frameID, printInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&> m_arguments;
};

#if PLATFORM(COCOA)
class DrawRectToImage {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo, WebCore::IntRect, WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DrawRectToImage; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DrawRectToImageReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::ShareableBitmap::Handle>;
    DrawRectToImage(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo, const WebCore::IntRect& rect, const WebCore::IntSize& imageSize)
        : m_arguments(frameID, printInfo, rect, imageSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&, const WebCore::IntRect&, const WebCore::IntSize&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class DrawRectToImageDuringDOMPrintOperation {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo, WebCore::IntRect, WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DrawRectToImageDuringDOMPrintOperation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DrawRectToImageDuringDOMPrintOperationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::ShareableBitmap::Handle>;
    DrawRectToImageDuringDOMPrintOperation(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo, const WebCore::IntRect& rect, const WebCore::IntSize& imageSize)
        : m_arguments(frameID, printInfo, rect, imageSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&, const WebCore::IntRect&, const WebCore::IntSize&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class DrawPagesToPDF {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DrawPagesToPDF; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DrawPagesToPDFReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<RefPtr<WebCore::SharedBuffer>>;
    DrawPagesToPDF(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo, uint32_t first, uint32_t count)
        : m_arguments(frameID, printInfo, first, count)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&, uint32_t, uint32_t> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class DrawPagesToPDFDuringDOMPrintOperation {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo, uint32_t, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DrawPagesToPDFDuringDOMPrintOperation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DrawPagesToPDFDuringDOMPrintOperationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<RefPtr<WebCore::SharedBuffer>>;
    DrawPagesToPDFDuringDOMPrintOperation(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo, uint32_t first, uint32_t count)
        : m_arguments(frameID, printInfo, first, count)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&, uint32_t, uint32_t> m_arguments;
};
#endif

#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
class ComputePagesForPrintingiOS {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ComputePagesForPrintingiOS; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<size_t>;
    ComputePagesForPrintingiOS(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo)
        : m_arguments(frameID, printInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&> m_arguments;
};
#endif

#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
class DrawToPDFiOS {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo, size_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DrawToPDFiOS; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DrawToPDFiOSReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<RefPtr<WebCore::SharedBuffer>>;
    DrawToPDFiOS(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo, size_t pageCount)
        : m_arguments(frameID, printInfo, pageCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&, size_t> m_arguments;
};
#endif

#if (PLATFORM(COCOA) && PLATFORM(IOS_FAMILY))
class DrawToImage {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DrawToImage; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DrawToImageReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::ShareableBitmap::Handle>;
    DrawToImage(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo)
        : m_arguments(frameID, printInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class DrawToPDF {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, std::optional<WebCore::FloatRect>, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DrawToPDF; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DrawToPDFReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<RefPtr<WebCore::SharedBuffer>>;
    DrawToPDF(const WebCore::FrameIdentifier& frameID, const std::optional<WebCore::FloatRect>& rect, bool allowTransparentBackground)
        : m_arguments(frameID, rect, allowTransparentBackground)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const std::optional<WebCore::FloatRect>&, bool> m_arguments;
};
#endif

#if PLATFORM(GTK)
class DrawPagesForPrinting {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DrawPagesForPrinting; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DrawPagesForPrintingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::SharedMemory::Handle>, WebCore::ResourceError>;
    DrawPagesForPrinting(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo)
        : m_arguments(frameID, printInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&> m_arguments;
};
#endif

#if PLATFORM(GTK)
class DrawPagesForPrintingDuringDOMPrintOperation {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebKit::PrintInfo>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DrawPagesForPrintingDuringDOMPrintOperation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DrawPagesForPrintingDuringDOMPrintOperationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebKit::SharedMemory::Handle>, WebCore::ResourceError>;
    DrawPagesForPrintingDuringDOMPrintOperation(const WebCore::FrameIdentifier& frameID, const WebKit::PrintInfo& printInfo)
        : m_arguments(frameID, printInfo)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebKit::PrintInfo&> m_arguments;
};
#endif

class SetMediaVolume {
public:
    using Arguments = std::tuple<float>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetMediaVolume; }
    static constexpr bool isSync = false;

    explicit SetMediaVolume(float volume)
        : m_arguments(volume)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<float> m_arguments;
};

class SetMuted {
public:
    using Arguments = std::tuple<OptionSet<WebCore::MediaProducerMutedState>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetMuted; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SetMutedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit SetMuted(const OptionSet<WebCore::MediaProducerMutedState>& muted)
        : m_arguments(muted)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebCore::MediaProducerMutedState>&> m_arguments;
};

class SetMayStartMediaWhenInWindow {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetMayStartMediaWhenInWindow; }
    static constexpr bool isSync = false;

    explicit SetMayStartMediaWhenInWindow(bool mayStartMedia)
        : m_arguments(mayStartMedia)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class StopMediaCapture {
public:
    using Arguments = std::tuple<WebCore::MediaProducerMediaCaptureKind>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_StopMediaCapture; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_StopMediaCaptureReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    explicit StopMediaCapture(WebCore::MediaProducerMediaCaptureKind kind)
        : m_arguments(kind)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::MediaProducerMediaCaptureKind> m_arguments;
};

class SetCanRunBeforeUnloadConfirmPanel {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetCanRunBeforeUnloadConfirmPanel; }
    static constexpr bool isSync = false;

    explicit SetCanRunBeforeUnloadConfirmPanel(bool canRunBeforeUnloadConfirmPanel)
        : m_arguments(canRunBeforeUnloadConfirmPanel)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetCanRunModal {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetCanRunModal; }
    static constexpr bool isSync = false;

    explicit SetCanRunModal(bool canRunModal)
        : m_arguments(canRunModal)
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
class CancelComposition {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CancelComposition; }
    static constexpr bool isSync = false;

    explicit CancelComposition(const String& text)
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
#endif

#if PLATFORM(GTK) || PLATFORM(WPE)
class DeleteSurrounding {
public:
    using Arguments = std::tuple<int64_t, unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DeleteSurrounding; }
    static constexpr bool isSync = false;

    DeleteSurrounding(int64_t offset, const unsigned& characterCount)
        : m_arguments(offset, characterCount)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<int64_t, const unsigned&> m_arguments;
};
#endif

#if PLATFORM(GTK)
class CollapseSelectionInFrame {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CollapseSelectionInFrame; }
    static constexpr bool isSync = false;

    explicit CollapseSelectionInFrame(const WebCore::FrameIdentifier& frameID)
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
#endif

#if PLATFORM(COCOA)
class WindowAndViewFramesChanged {
public:
    using Arguments = std::tuple<WebCore::FloatRect, WebCore::FloatRect, WebCore::FloatRect, WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_WindowAndViewFramesChanged; }
    static constexpr bool isSync = false;

    WindowAndViewFramesChanged(const WebCore::FloatRect& windowFrameInScreenCoordinates, const WebCore::FloatRect& windowFrameInUnflippedScreenCoordinates, const WebCore::FloatRect& viewFrameInWindowCoordinates, const WebCore::FloatPoint& accessibilityViewCoordinates)
        : m_arguments(windowFrameInScreenCoordinates, windowFrameInUnflippedScreenCoordinates, viewFrameInWindowCoordinates, accessibilityViewCoordinates)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatRect&, const WebCore::FloatRect&, const WebCore::FloatRect&, const WebCore::FloatPoint&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetMainFrameIsScrollable {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetMainFrameIsScrollable; }
    static constexpr bool isSync = false;

    explicit SetMainFrameIsScrollable(bool isScrollable)
        : m_arguments(isScrollable)
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
class RegisterUIProcessAccessibilityTokens {
public:
    using Arguments = std::tuple<IPC::DataReference, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RegisterUIProcessAccessibilityTokens; }
    static constexpr bool isSync = false;

    RegisterUIProcessAccessibilityTokens(const IPC::DataReference& elemenToken, const IPC::DataReference& windowToken)
        : m_arguments(elemenToken, windowToken)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const IPC::DataReference&, const IPC::DataReference&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetStringSelectionForPasteboard {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetStringSelectionForPasteboard; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetDataSelectionForPasteboard {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetDataSelectionForPasteboard; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<RefPtr<WebCore::SharedBuffer>>;
    explicit GetDataSelectionForPasteboard(const String& pasteboardType)
        : m_arguments(pasteboardType)
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
class ReadSelectionFromPasteboard {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ReadSelectionFromPasteboard; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit ReadSelectionFromPasteboard(const String& pasteboardName)
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

#if PLATFORM(COCOA)
class ReplaceSelectionWithPasteboardData {
public:
    using Arguments = std::tuple<Vector<String>, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ReplaceSelectionWithPasteboardData; }
    static constexpr bool isSync = false;

    ReplaceSelectionWithPasteboardData(const Vector<String>& types, const IPC::DataReference& data)
        : m_arguments(types, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&, const IPC::DataReference&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class ShouldDelayWindowOrderingEvent {
public:
    using Arguments = std::tuple<WebKit::WebMouseEvent>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ShouldDelayWindowOrderingEvent; }
    static constexpr bool isSync = true;

    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit ShouldDelayWindowOrderingEvent(const WebKit::WebMouseEvent& event)
        : m_arguments(event)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebMouseEvent&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetTextAsync {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetTextAsync; }
    static constexpr bool isSync = false;

    explicit SetTextAsync(const String& text)
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
#endif

#if PLATFORM(COCOA)
class InsertTextAsync {
public:
    using Arguments = std::tuple<String, WebKit::EditingRange, WebKit::InsertTextOptions>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_InsertTextAsync; }
    static constexpr bool isSync = false;

    InsertTextAsync(const String& text, const WebKit::EditingRange& replacementRange, const WebKit::InsertTextOptions& options)
        : m_arguments(text, replacementRange, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebKit::EditingRange&, const WebKit::InsertTextOptions&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class InsertDictatedTextAsync {
public:
    using Arguments = std::tuple<String, WebKit::EditingRange, Vector<WebCore::DictationAlternative>, WebKit::InsertTextOptions>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_InsertDictatedTextAsync; }
    static constexpr bool isSync = false;

    InsertDictatedTextAsync(const String& text, const WebKit::EditingRange& replacementRange, const Vector<WebCore::DictationAlternative>& dictationAlternatives, const WebKit::InsertTextOptions& options)
        : m_arguments(text, replacementRange, dictationAlternatives, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebKit::EditingRange&, const Vector<WebCore::DictationAlternative>&, const WebKit::InsertTextOptions&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class AddDictationAlternative {
public:
    using Arguments = std::tuple<String, WebCore::DictationContext>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_AddDictationAlternative; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_AddDictationAlternativeReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    AddDictationAlternative(const String& text, const WebCore::DictationContext& context)
        : m_arguments(text, context)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const WebCore::DictationContext&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class DictationAlternativesAtSelection {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DictationAlternativesAtSelection; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DictationAlternativesAtSelectionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::DictationContext>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class ClearDictationAlternatives {
public:
    using Arguments = std::tuple<Vector<WebCore::DictationContext>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ClearDictationAlternatives; }
    static constexpr bool isSync = false;

    explicit ClearDictationAlternatives(const Vector<WebCore::DictationContext>& contexts)
        : m_arguments(contexts)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::DictationContext>&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class HasMarkedText {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_HasMarkedText; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_HasMarkedTextReply; }
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
class GetMarkedRangeAsync {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetMarkedRangeAsync; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetMarkedRangeAsyncReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::EditingRange>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class GetSelectedRangeAsync {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetSelectedRangeAsync; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetSelectedRangeAsyncReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::EditingRange>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class CharacterIndexForPointAsync {
public:
    using Arguments = std::tuple<WebCore::IntPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CharacterIndexForPointAsync; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_CharacterIndexForPointAsyncReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t>;
    explicit CharacterIndexForPointAsync(const WebCore::IntPoint& point)
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

#if PLATFORM(COCOA)
class FirstRectForCharacterRangeAsync {
public:
    using Arguments = std::tuple<WebKit::EditingRange>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_FirstRectForCharacterRangeAsync; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_FirstRectForCharacterRangeAsyncReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::IntRect, WebKit::EditingRange>;
    explicit FirstRectForCharacterRangeAsync(const WebKit::EditingRange& range)
        : m_arguments(range)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::EditingRange&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class SetCompositionAsync {
public:
    using Arguments = std::tuple<String, Vector<WebCore::CompositionUnderline>, Vector<WebCore::CompositionHighlight>, HashMap<String, Vector<WebCore::CharacterRange>>, WebKit::EditingRange, WebKit::EditingRange>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetCompositionAsync; }
    static constexpr bool isSync = false;

    SetCompositionAsync(const String& text, const Vector<WebCore::CompositionUnderline>& underlines, const Vector<WebCore::CompositionHighlight>& highlights, const HashMap<String, Vector<WebCore::CharacterRange>>& annotations, const WebKit::EditingRange& selectionRange, const WebKit::EditingRange& replacementRange)
        : m_arguments(text, underlines, highlights, annotations, selectionRange, replacementRange)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const Vector<WebCore::CompositionUnderline>&, const Vector<WebCore::CompositionHighlight>&, const HashMap<String, Vector<WebCore::CharacterRange>>&, const WebKit::EditingRange&, const WebKit::EditingRange&> m_arguments;
};
#endif

#if PLATFORM(COCOA)
class ConfirmCompositionAsync {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ConfirmCompositionAsync; }
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
class AttributedSubstringForCharacterRangeAsync {
public:
    using Arguments = std::tuple<WebKit::EditingRange>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_AttributedSubstringForCharacterRangeAsync; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_AttributedSubstringForCharacterRangeAsyncReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::AttributedString, WebKit::EditingRange>;
    explicit AttributedSubstringForCharacterRangeAsync(const WebKit::EditingRange& range)
        : m_arguments(range)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::EditingRange&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class RequestAcceptsFirstMouse {
public:
    using Arguments = std::tuple<int, WebKit::WebMouseEvent>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestAcceptsFirstMouse; }
    static constexpr bool isSync = false;

    RequestAcceptsFirstMouse(const int& eventNumber, const WebKit::WebMouseEvent& event)
        : m_arguments(eventNumber, event)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const int&, const WebKit::WebMouseEvent&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class SetCaretAnimatorType {
public:
    using Arguments = std::tuple<WebCore::CaretAnimatorType>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetCaretAnimatorType; }
    static constexpr bool isSync = false;

    explicit SetCaretAnimatorType(WebCore::CaretAnimatorType caretType)
        : m_arguments(caretType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::CaretAnimatorType> m_arguments;
};
#endif

#if PLATFORM(MAC)
class SetCaretBlinkingSuspended {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetCaretBlinkingSuspended; }
    static constexpr bool isSync = false;

    explicit SetCaretBlinkingSuspended(bool blinkSuspended)
        : m_arguments(blinkSuspended)
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

#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
class ReplaceImageForRemoveBackground {
public:
    using Arguments = std::tuple<WebCore::ElementContext, Vector<String>, IPC::DataReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ReplaceImageForRemoveBackground; }
    static constexpr bool isSync = false;

    ReplaceImageForRemoveBackground(const WebCore::ElementContext& context, const Vector<String>& types, const IPC::DataReference& data)
        : m_arguments(context, types, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ElementContext&, const Vector<String>&, const IPC::DataReference&> m_arguments;
};
#endif

#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)
class ShouldAllowRemoveBackground {
public:
    using Arguments = std::tuple<WebCore::ElementContext>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ShouldAllowRemoveBackground; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_ShouldAllowRemoveBackgroundReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit ShouldAllowRemoveBackground(const WebCore::ElementContext& context)
        : m_arguments(context)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ElementContext&> m_arguments;
};
#endif

class SetAlwaysShowsHorizontalScroller {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetAlwaysShowsHorizontalScroller; }
    static constexpr bool isSync = false;

    explicit SetAlwaysShowsHorizontalScroller(bool alwaysShowsHorizontalScroller)
        : m_arguments(alwaysShowsHorizontalScroller)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetAlwaysShowsVerticalScroller {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetAlwaysShowsVerticalScroller; }
    static constexpr bool isSync = false;

    explicit SetAlwaysShowsVerticalScroller(bool alwaysShowsVerticalScroller)
        : m_arguments(alwaysShowsVerticalScroller)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetMinimumSizeForAutoLayout {
public:
    using Arguments = std::tuple<WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetMinimumSizeForAutoLayout; }
    static constexpr bool isSync = false;

    explicit SetMinimumSizeForAutoLayout(const WebCore::IntSize& size)
        : m_arguments(size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntSize&> m_arguments;
};

class SetSizeToContentAutoSizeMaximumSize {
public:
    using Arguments = std::tuple<WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetSizeToContentAutoSizeMaximumSize; }
    static constexpr bool isSync = false;

    explicit SetSizeToContentAutoSizeMaximumSize(const WebCore::IntSize& size)
        : m_arguments(size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntSize&> m_arguments;
};

class SetAutoSizingShouldExpandToViewHeight {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetAutoSizingShouldExpandToViewHeight; }
    static constexpr bool isSync = false;

    explicit SetAutoSizingShouldExpandToViewHeight(bool shouldExpand)
        : m_arguments(shouldExpand)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetViewportSizeForCSSViewportUnits {
public:
    using Arguments = std::tuple<std::optional<WebCore::FloatSize>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetViewportSizeForCSSViewportUnits; }
    static constexpr bool isSync = false;

    explicit SetViewportSizeForCSSViewportUnits(const std::optional<WebCore::FloatSize>& viewportSize)
        : m_arguments(viewportSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<WebCore::FloatSize>&> m_arguments;
};

#if PLATFORM(COCOA)
class HandleAlternativeTextUIResult {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_HandleAlternativeTextUIResult; }
    static constexpr bool isSync = false;

    explicit HandleAlternativeTextUIResult(const String& result)
        : m_arguments(result)
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
class WillStartUserTriggeredZooming {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_WillStartUserTriggeredZooming; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class SetScrollPinningBehavior {
public:
    using Arguments = std::tuple<WebCore::ScrollPinningBehavior>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetScrollPinningBehavior; }
    static constexpr bool isSync = false;

    explicit SetScrollPinningBehavior(WebCore::ScrollPinningBehavior pinning)
        : m_arguments(pinning)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::ScrollPinningBehavior> m_arguments;
};

class SetScrollbarOverlayStyle {
public:
    using Arguments = std::tuple<std::optional<uint32_t>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetScrollbarOverlayStyle; }
    static constexpr bool isSync = false;

    explicit SetScrollbarOverlayStyle(const std::optional<uint32_t>& scrollbarStyle)
        : m_arguments(scrollbarStyle)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const std::optional<uint32_t>&> m_arguments;
};

class GetBytecodeProfile {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetBytecodeProfile; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetBytecodeProfileReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class GetSamplingProfilerOutput {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetSamplingProfilerOutput; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetSamplingProfilerOutputReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class TakeSnapshot {
public:
    using Arguments = std::tuple<WebCore::IntRect, WebCore::IntSize, uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_TakeSnapshot; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_TakeSnapshotReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::ShareableBitmap::Handle>;
    TakeSnapshot(const WebCore::IntRect& snapshotRect, const WebCore::IntSize& bitmapSize, uint32_t options)
        : m_arguments(snapshotRect, bitmapSize, options)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::IntRect&, const WebCore::IntSize&, uint32_t> m_arguments;
};

#if PLATFORM(MAC)
class PerformImmediateActionHitTestAtLocation {
public:
    using Arguments = std::tuple<WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PerformImmediateActionHitTestAtLocation; }
    static constexpr bool isSync = false;

    explicit PerformImmediateActionHitTestAtLocation(const WebCore::FloatPoint& location)
        : m_arguments(location)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FloatPoint&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class ImmediateActionDidUpdate {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ImmediateActionDidUpdate; }
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
class ImmediateActionDidCancel {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ImmediateActionDidCancel; }
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
class ImmediateActionDidComplete {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ImmediateActionDidComplete; }
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
class DataDetectorsDidPresentUI {
public:
    using Arguments = std::tuple<WebCore::PageOverlay::PageOverlayID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DataDetectorsDidPresentUI; }
    static constexpr bool isSync = false;

    explicit DataDetectorsDidPresentUI(const WebCore::PageOverlay::PageOverlayID& pageOverlay)
        : m_arguments(pageOverlay)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageOverlay::PageOverlayID&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class DataDetectorsDidChangeUI {
public:
    using Arguments = std::tuple<WebCore::PageOverlay::PageOverlayID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DataDetectorsDidChangeUI; }
    static constexpr bool isSync = false;

    explicit DataDetectorsDidChangeUI(const WebCore::PageOverlay::PageOverlayID& pageOverlay)
        : m_arguments(pageOverlay)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageOverlay::PageOverlayID&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class DataDetectorsDidHideUI {
public:
    using Arguments = std::tuple<WebCore::PageOverlay::PageOverlayID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DataDetectorsDidHideUI; }
    static constexpr bool isSync = false;

    explicit DataDetectorsDidHideUI(const WebCore::PageOverlay::PageOverlayID& pageOverlay)
        : m_arguments(pageOverlay)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PageOverlay::PageOverlayID&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class HandleAcceptedCandidate {
public:
    using Arguments = std::tuple<WebCore::TextCheckingResult>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_HandleAcceptedCandidate; }
    static constexpr bool isSync = false;

    explicit HandleAcceptedCandidate(const WebCore::TextCheckingResult& acceptedCandidate)
        : m_arguments(acceptedCandidate)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::TextCheckingResult&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class SetUseSystemAppearance {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetUseSystemAppearance; }
    static constexpr bool isSync = false;

    explicit SetUseSystemAppearance(bool useSystemAppearance)
        : m_arguments(useSystemAppearance)
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
class SemanticContextDidChange {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SemanticContextDidChange; }
    static constexpr bool isSync = false;

    explicit SemanticContextDidChange(bool useFormSemanticContext)
        : m_arguments(useFormSemanticContext)
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
class SetHeaderBannerHeight {
public:
    using Arguments = std::tuple<int>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetHeaderBannerHeight; }
    static constexpr bool isSync = false;

    explicit SetHeaderBannerHeight(const int& height)
        : m_arguments(height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const int&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class SetFooterBannerHeight {
public:
    using Arguments = std::tuple<int>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetFooterBannerHeight; }
    static constexpr bool isSync = false;

    explicit SetFooterBannerHeight(const int& height)
        : m_arguments(height)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const int&> m_arguments;
};
#endif

#if PLATFORM(MAC)
class DidEndMagnificationGesture {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidEndMagnificationGesture; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class FlushDeferredDidReceiveMouseEvent {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_FlushDeferredDidReceiveMouseEvent; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class PerformHitTestForMouseEvent {
public:
    using Arguments = std::tuple<WebKit::WebMouseEvent>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PerformHitTestForMouseEvent; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_PerformHitTestForMouseEventReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::WebHitTestResultData, OptionSet<WebKit::WebEventModifier>, WebKit::UserData>;
    explicit PerformHitTestForMouseEvent(const WebKit::WebMouseEvent& event)
        : m_arguments(event)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebMouseEvent&> m_arguments;
};

class EffectiveAppearanceDidChange {
public:
    using Arguments = std::tuple<bool, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_EffectiveAppearanceDidChange; }
    static constexpr bool isSync = false;

    EffectiveAppearanceDidChange(bool useDarkAppearance, bool useElevatedUserInterfaceLevel)
        : m_arguments(useDarkAppearance, useElevatedUserInterfaceLevel)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, bool> m_arguments;
};

#if HAVE(APP_ACCENT_COLORS)
class SetAccentColor {
public:
    using Arguments = std::tuple<WebCore::Color>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetAccentColor; }
    static constexpr bool isSync = false;

    explicit SetAccentColor(const WebCore::Color& color)
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

#if PLATFORM(COCOA)
class RequestActiveNowPlayingSessionInfo {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RequestActiveNowPlayingSessionInfo; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_RequestActiveNowPlayingSessionInfoReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool, bool, String, double, double, uint64_t>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class SetShouldDispatchFakeMouseMoveEvents {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetShouldDispatchFakeMouseMoveEvents; }
    static constexpr bool isSync = false;

    explicit SetShouldDispatchFakeMouseMoveEvents(bool shouldDispatchFakeMouseMoveEvents)
        : m_arguments(shouldDispatchFakeMouseMoveEvents)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
class PlaybackTargetSelected {
public:
    using Arguments = std::tuple<WebCore::PlaybackTargetClientContextIdentifier, WebCore::MediaPlaybackTargetContext>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PlaybackTargetSelected; }
    static constexpr bool isSync = false;

    PlaybackTargetSelected(const WebCore::PlaybackTargetClientContextIdentifier& contextId, const WebCore::MediaPlaybackTargetContext& target)
        : m_arguments(contextId, target)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlaybackTargetClientContextIdentifier&, const WebCore::MediaPlaybackTargetContext&> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
class PlaybackTargetAvailabilityDidChange {
public:
    using Arguments = std::tuple<WebCore::PlaybackTargetClientContextIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PlaybackTargetAvailabilityDidChange; }
    static constexpr bool isSync = false;

    PlaybackTargetAvailabilityDidChange(const WebCore::PlaybackTargetClientContextIdentifier& contextId, bool available)
        : m_arguments(contextId, available)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlaybackTargetClientContextIdentifier&, bool> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
class SetShouldPlayToPlaybackTarget {
public:
    using Arguments = std::tuple<WebCore::PlaybackTargetClientContextIdentifier, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetShouldPlayToPlaybackTarget; }
    static constexpr bool isSync = false;

    SetShouldPlayToPlaybackTarget(const WebCore::PlaybackTargetClientContextIdentifier& contextId, bool shouldPlay)
        : m_arguments(contextId, shouldPlay)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlaybackTargetClientContextIdentifier&, bool> m_arguments;
};
#endif

#if ENABLE(WIRELESS_PLAYBACK_TARGET) && !PLATFORM(IOS_FAMILY)
class PlaybackTargetPickerWasDismissed {
public:
    using Arguments = std::tuple<WebCore::PlaybackTargetClientContextIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PlaybackTargetPickerWasDismissed; }
    static constexpr bool isSync = false;

    explicit PlaybackTargetPickerWasDismissed(const WebCore::PlaybackTargetClientContextIdentifier& contextId)
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

#if ENABLE(POINTER_LOCK)
class DidAcquirePointerLock {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidAcquirePointerLock; }
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
class DidNotAcquirePointerLock {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidNotAcquirePointerLock; }
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
class DidLosePointerLock {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidLosePointerLock; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class ClearWheelEventTestMonitor {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ClearWheelEventTestMonitor; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetShouldScaleViewToFitDocument {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetShouldScaleViewToFitDocument; }
    static constexpr bool isSync = false;

    explicit SetShouldScaleViewToFitDocument(bool shouldScaleViewToFitDocument)
        : m_arguments(shouldScaleViewToFitDocument)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetUserInterfaceLayoutDirection {
public:
    using Arguments = std::tuple<uint32_t>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetUserInterfaceLayoutDirection; }
    static constexpr bool isSync = false;

    explicit SetUserInterfaceLayoutDirection(uint32_t direction)
        : m_arguments(direction)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<uint32_t> m_arguments;
};

class DidGetLoadDecisionForIcon {
public:
    using Arguments = std::tuple<bool, WebKit::CallbackID>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DidGetLoadDecisionForIcon; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DidGetLoadDecisionForIconReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<IPC::SharedBufferReference>;
    DidGetLoadDecisionForIcon(bool decision, const WebKit::CallbackID& loadIdentifier)
        : m_arguments(decision, loadIdentifier)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, const WebKit::CallbackID&> m_arguments;
};

class SetUseIconLoadingClient {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetUseIconLoadingClient; }
    static constexpr bool isSync = false;

    explicit SetUseIconLoadingClient(bool useIconLoadingClient)
        : m_arguments(useIconLoadingClient)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

#if ENABLE(GAMEPAD)
class GamepadActivity {
public:
    using Arguments = std::tuple<Vector<std::optional<WebKit::GamepadData>>, WebCore::EventMakesGamepadsVisible>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GamepadActivity; }
    static constexpr bool isSync = false;

    GamepadActivity(const Vector<std::optional<WebKit::GamepadData>>& gamepadDatas, WebCore::EventMakesGamepadsVisible eventVisibility)
        : m_arguments(gamepadDatas, eventVisibility)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<std::optional<WebKit::GamepadData>>&, WebCore::EventMakesGamepadsVisible> m_arguments;
};
#endif

class RegisterURLSchemeHandler {
public:
    using Arguments = std::tuple<WebKit::WebURLSchemeHandlerIdentifier, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RegisterURLSchemeHandler; }
    static constexpr bool isSync = false;

    RegisterURLSchemeHandler(const WebKit::WebURLSchemeHandlerIdentifier& handlerIdentifier, const String& scheme)
        : m_arguments(handlerIdentifier, scheme)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebURLSchemeHandlerIdentifier&, const String&> m_arguments;
};

class URLSchemeTaskWillPerformRedirection {
public:
    using Arguments = std::tuple<WebKit::WebURLSchemeHandlerIdentifier, WebCore::ResourceLoaderIdentifier, WebCore::ResourceResponse, WebCore::ResourceRequest>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_URLSchemeTaskWillPerformRedirection; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_URLSchemeTaskWillPerformRedirectionReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebCore::ResourceRequest>;
    URLSchemeTaskWillPerformRedirection(const WebKit::WebURLSchemeHandlerIdentifier& handlerIdentifier, const WebCore::ResourceLoaderIdentifier& taskIdentifier, const WebCore::ResourceResponse& response, const WebCore::ResourceRequest& proposedRequest)
        : m_arguments(handlerIdentifier, taskIdentifier, response, proposedRequest)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebURLSchemeHandlerIdentifier&, const WebCore::ResourceLoaderIdentifier&, const WebCore::ResourceResponse&, const WebCore::ResourceRequest&> m_arguments;
};

class URLSchemeTaskDidPerformRedirection {
public:
    using Arguments = std::tuple<WebKit::WebURLSchemeHandlerIdentifier, WebCore::ResourceLoaderIdentifier, WebCore::ResourceResponse, WebCore::ResourceRequest>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_URLSchemeTaskDidPerformRedirection; }
    static constexpr bool isSync = false;

    URLSchemeTaskDidPerformRedirection(const WebKit::WebURLSchemeHandlerIdentifier& handlerIdentifier, const WebCore::ResourceLoaderIdentifier& taskIdentifier, const WebCore::ResourceResponse& response, const WebCore::ResourceRequest& proposedRequest)
        : m_arguments(handlerIdentifier, taskIdentifier, response, proposedRequest)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebURLSchemeHandlerIdentifier&, const WebCore::ResourceLoaderIdentifier&, const WebCore::ResourceResponse&, const WebCore::ResourceRequest&> m_arguments;
};

class URLSchemeTaskDidReceiveResponse {
public:
    using Arguments = std::tuple<WebKit::WebURLSchemeHandlerIdentifier, WebCore::ResourceLoaderIdentifier, WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_URLSchemeTaskDidReceiveResponse; }
    static constexpr bool isSync = false;

    URLSchemeTaskDidReceiveResponse(const WebKit::WebURLSchemeHandlerIdentifier& handlerIdentifier, const WebCore::ResourceLoaderIdentifier& taskIdentifier, const WebCore::ResourceResponse& response)
        : m_arguments(handlerIdentifier, taskIdentifier, response)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebURLSchemeHandlerIdentifier&, const WebCore::ResourceLoaderIdentifier&, const WebCore::ResourceResponse&> m_arguments;
};

class URLSchemeTaskDidReceiveData {
public:
    using Arguments = std::tuple<WebKit::WebURLSchemeHandlerIdentifier, WebCore::ResourceLoaderIdentifier, Ref<WebCore::SharedBuffer>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_URLSchemeTaskDidReceiveData; }
    static constexpr bool isSync = false;

    URLSchemeTaskDidReceiveData(const WebKit::WebURLSchemeHandlerIdentifier& handlerIdentifier, const WebCore::ResourceLoaderIdentifier& taskIdentifier, const Ref<WebCore::SharedBuffer>& data)
        : m_arguments(handlerIdentifier, taskIdentifier, data)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebURLSchemeHandlerIdentifier&, const WebCore::ResourceLoaderIdentifier&, const Ref<WebCore::SharedBuffer>&> m_arguments;
};

class URLSchemeTaskDidComplete {
public:
    using Arguments = std::tuple<WebKit::WebURLSchemeHandlerIdentifier, WebCore::ResourceLoaderIdentifier, WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_URLSchemeTaskDidComplete; }
    static constexpr bool isSync = false;

    URLSchemeTaskDidComplete(const WebKit::WebURLSchemeHandlerIdentifier& handlerIdentifier, const WebCore::ResourceLoaderIdentifier& taskIdentifier, const WebCore::ResourceError& error)
        : m_arguments(handlerIdentifier, taskIdentifier, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebURLSchemeHandlerIdentifier&, const WebCore::ResourceLoaderIdentifier&, const WebCore::ResourceError&> m_arguments;
};

class SetIsSuspended {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetIsSuspended; }
    static constexpr bool isSync = false;

    explicit SetIsSuspended(bool suspended)
        : m_arguments(suspended)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

#if ENABLE(ATTACHMENT_ELEMENT)
class InsertAttachment {
public:
    using Arguments = std::tuple<String, std::optional<uint64_t>, String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_InsertAttachment; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_InsertAttachmentReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    InsertAttachment(const String& identifier, const std::optional<uint64_t>& fileSize, const String& fileName, const String& contentType)
        : m_arguments(identifier, fileSize, fileName, contentType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const std::optional<uint64_t>&, const String&, const String&> m_arguments;
};
#endif

#if ENABLE(ATTACHMENT_ELEMENT)
class UpdateAttachmentAttributes {
public:
    using Arguments = std::tuple<String, std::optional<uint64_t>, String, String, IPC::SharedBufferReference>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateAttachmentAttributes; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_UpdateAttachmentAttributesReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    UpdateAttachmentAttributes(const String& identifier, const std::optional<uint64_t>& fileSize, const String& contentType, const String& fileName, const IPC::SharedBufferReference& enclosingImageData)
        : m_arguments(identifier, fileSize, contentType, fileName, enclosingImageData)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const std::optional<uint64_t>&, const String&, const String&, const IPC::SharedBufferReference&> m_arguments;
};
#endif

#if ENABLE(ATTACHMENT_ELEMENT)
class UpdateAttachmentThumbnail {
public:
    using Arguments = std::tuple<String, WebKit::ShareableBitmap::Handle>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateAttachmentThumbnail; }
    static constexpr bool isSync = false;

    UpdateAttachmentThumbnail(const String& identifier, WebKit::ShareableBitmap::Handle&& qlThumbnailHandle)
        : m_arguments(identifier, WTFMove(qlThumbnailHandle))
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, WebKit::ShareableBitmap::Handle&&> m_arguments;
};
#endif

#if ENABLE(ATTACHMENT_ELEMENT)
class UpdateAttachmentIcon {
public:
    using Arguments = std::tuple<String, WebKit::ShareableBitmap::Handle, WebCore::FloatSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateAttachmentIcon; }
    static constexpr bool isSync = false;

    UpdateAttachmentIcon(const String& identifier, WebKit::ShareableBitmap::Handle&& icon, const WebCore::FloatSize& size)
        : m_arguments(identifier, WTFMove(icon), size)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, WebKit::ShareableBitmap::Handle&&, const WebCore::FloatSize&> m_arguments;
};
#endif

#if ENABLE(APPLICATION_MANIFEST)
class GetApplicationManifest {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetApplicationManifest; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetApplicationManifestReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<std::optional<WebCore::ApplicationManifest>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class GetTextFragmentMatch {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetTextFragmentMatch; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetTextFragmentMatchReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetDefersLoading {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetDefersLoading; }
    static constexpr bool isSync = false;

    explicit SetDefersLoading(bool defersLoading)
        : m_arguments(defersLoading)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

#if ENABLE(PDFKIT_PLUGIN)
class ZoomPDFIn {
public:
    using Arguments = std::tuple<WebKit::PDFPluginIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ZoomPDFIn; }
    static constexpr bool isSync = false;

    explicit ZoomPDFIn(const WebKit::PDFPluginIdentifier& identifier)
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

#if ENABLE(PDFKIT_PLUGIN)
class ZoomPDFOut {
public:
    using Arguments = std::tuple<WebKit::PDFPluginIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ZoomPDFOut; }
    static constexpr bool isSync = false;

    explicit ZoomPDFOut(const WebKit::PDFPluginIdentifier& identifier)
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

#if ENABLE(PDFKIT_PLUGIN)
class SavePDF {
public:
    using Arguments = std::tuple<WebKit::PDFPluginIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SavePDF; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SavePDFReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String, URL, IPC::DataReference>;
    explicit SavePDF(const WebKit::PDFPluginIdentifier& identifier)
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

#if ENABLE(PDFKIT_PLUGIN)
class OpenPDFWithPreview {
public:
    using Arguments = std::tuple<WebKit::PDFPluginIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_OpenPDFWithPreview; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_OpenPDFWithPreviewReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String, WebKit::FrameInfoData, IPC::DataReference, String>;
    explicit OpenPDFWithPreview(const WebKit::PDFPluginIdentifier& identifier)
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

class UpdateCurrentModifierState {
public:
    using Arguments = std::tuple<OptionSet<WebCore::PlatformEvent::Modifier>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateCurrentModifierState; }
    static constexpr bool isSync = false;

    explicit UpdateCurrentModifierState(const OptionSet<WebCore::PlatformEvent::Modifier>& modifiers)
        : m_arguments(modifiers)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const OptionSet<WebCore::PlatformEvent::Modifier>&> m_arguments;
};

class SimulateDeviceOrientationChange {
public:
    using Arguments = std::tuple<double, double, double>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SimulateDeviceOrientationChange; }
    static constexpr bool isSync = false;

    SimulateDeviceOrientationChange(double alpha, double beta, double gamma)
        : m_arguments(alpha, beta, gamma)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<double, double, double> m_arguments;
};

#if ENABLE(SPEECH_SYNTHESIS)
class SpeakingErrorOccurred {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SpeakingErrorOccurred; }
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
class BoundaryEventOccurred {
public:
    using Arguments = std::tuple<bool, unsigned, unsigned>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_BoundaryEventOccurred; }
    static constexpr bool isSync = false;

    BoundaryEventOccurred(bool wordBoundary, const unsigned& charIndex, const unsigned& charLength)
        : m_arguments(wordBoundary, charIndex, charLength)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool, const unsigned&, const unsigned&> m_arguments;
};
#endif

#if ENABLE(SPEECH_SYNTHESIS)
class VoicesDidChange {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_VoicesDidChange; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

class SetCanShowPlaceholder {
public:
    using Arguments = std::tuple<WebCore::ElementContext, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetCanShowPlaceholder; }
    static constexpr bool isSync = false;

    SetCanShowPlaceholder(const WebCore::ElementContext& context, bool canShowPlaceholder)
        : m_arguments(context, canShowPlaceholder)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ElementContext&, bool> m_arguments;
};

#if ENABLE(TRACKING_PREVENTION)
class WasLoadedWithDataTransferFromPrevalentResource {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_WasLoadedWithDataTransferFromPrevalentResource; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class ClearLoadedSubresourceDomains {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ClearLoadedSubresourceDomains; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if ENABLE(TRACKING_PREVENTION)
class GetLoadedSubresourceDomains {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetLoadedSubresourceDomains; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetLoadedSubresourceDomainsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<Vector<WebCore::RegistrableDomain>>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};
#endif

#if USE(SYSTEM_PREVIEW)
class SystemPreviewActionTriggered {
public:
    using Arguments = std::tuple<WebCore::SystemPreviewInfo, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SystemPreviewActionTriggered; }
    static constexpr bool isSync = false;

    SystemPreviewActionTriggered(const WebCore::SystemPreviewInfo& previewInfo, const String& message)
        : m_arguments(previewInfo, message)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::SystemPreviewInfo&, const String&> m_arguments;
};
#endif

#if PLATFORM(GTK) || PLATFORM(WPE)
class SendMessageToWebProcessExtension {
public:
    using Arguments = std::tuple<WebKit::UserMessage>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SendMessageToWebProcessExtension; }
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

#if PLATFORM(GTK) || PLATFORM(WPE)
class SendMessageToWebProcessExtensionWithReply {
public:
    using Arguments = std::tuple<WebKit::UserMessage>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SendMessageToWebProcessExtensionWithReply; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_SendMessageToWebProcessExtensionWithReplyReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::UserMessage>;
    explicit SendMessageToWebProcessExtensionWithReply(const WebKit::UserMessage& userMessage)
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

class StartTextManipulations {
public:
    using Arguments = std::tuple<Vector<WebCore::TextManipulationController::ExclusionRule>, bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_StartTextManipulations; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_StartTextManipulationsReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<>;
    StartTextManipulations(const Vector<WebCore::TextManipulationController::ExclusionRule>& exclusionRules, bool includeSubframes)
        : m_arguments(exclusionRules, includeSubframes)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::TextManipulationController::ExclusionRule>&, bool> m_arguments;
};

class CompleteTextManipulation {
public:
    using Arguments = std::tuple<Vector<WebCore::TextManipulationItem>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CompleteTextManipulation; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_CompleteTextManipulationReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool, Vector<WebCore::TextManipulationController::ManipulationFailure>>;
    explicit CompleteTextManipulation(const Vector<WebCore::TextManipulationItem>& items)
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

class SetOverriddenMediaType {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetOverriddenMediaType; }
    static constexpr bool isSync = false;

    explicit SetOverriddenMediaType(const String& mediaType)
        : m_arguments(mediaType)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&> m_arguments;
};

class GetProcessDisplayName {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GetProcessDisplayName; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_GetProcessDisplayNameReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<String>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class UpdateCORSDisablingPatterns {
public:
    using Arguments = std::tuple<Vector<String>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateCORSDisablingPatterns; }
    static constexpr bool isSync = false;

    explicit UpdateCORSDisablingPatterns(const Vector<String>& patterns)
        : m_arguments(patterns)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<String>&> m_arguments;
};

class SetIsTakingSnapshotsForApplicationSuspension {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetIsTakingSnapshotsForApplicationSuspension; }
    static constexpr bool isSync = false;

    explicit SetIsTakingSnapshotsForApplicationSuspension(bool isTakingSnapshotsForApplicationSuspension)
        : m_arguments(isTakingSnapshotsForApplicationSuspension)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetNeedsDOMWindowResizeEvent {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetNeedsDOMWindowResizeEvent; }
    static constexpr bool isSync = false;

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

class SetHasResourceLoadClient {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetHasResourceLoadClient; }
    static constexpr bool isSync = false;

    explicit SetHasResourceLoadClient(bool has)
        : m_arguments(has)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

class SetCanUseCredentialStorage {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetCanUseCredentialStorage; }
    static constexpr bool isSync = false;

    explicit SetCanUseCredentialStorage(bool canUse)
        : m_arguments(canUse)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<bool> m_arguments;
};

#if ENABLE(APP_HIGHLIGHTS)
class CreateAppHighlightInSelectedRange {
public:
    using Arguments = std::tuple<WebCore::CreateNewGroupForHighlight, WebCore::HighlightRequestOriginatedInApp>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CreateAppHighlightInSelectedRange; }
    static constexpr bool isSync = false;

    CreateAppHighlightInSelectedRange(WebCore::CreateNewGroupForHighlight createNewGroup, WebCore::HighlightRequestOriginatedInApp requestOrigin)
        : m_arguments(createNewGroup, requestOrigin)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::CreateNewGroupForHighlight, WebCore::HighlightRequestOriginatedInApp> m_arguments;
};
#endif

#if ENABLE(APP_HIGHLIGHTS)
class RestoreAppHighlightsAndScrollToIndex {
public:
    using Arguments = std::tuple<Vector<WebKit::SharedMemory::Handle>, std::optional<unsigned>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_RestoreAppHighlightsAndScrollToIndex; }
    static constexpr bool isSync = false;

    RestoreAppHighlightsAndScrollToIndex(Vector<WebKit::SharedMemory::Handle>&& memoryHandles, const std::optional<unsigned>& index)
        : m_arguments(WTFMove(memoryHandles), index)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<Vector<WebKit::SharedMemory::Handle>&&, const std::optional<unsigned>&> m_arguments;
};
#endif

#if ENABLE(APP_HIGHLIGHTS)
class SetAppHighlightsVisibility {
public:
    using Arguments = std::tuple<WebCore::HighlightVisibility>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetAppHighlightsVisibility; }
    static constexpr bool isSync = false;

    explicit SetAppHighlightsVisibility(WebCore::HighlightVisibility highlightVisibility)
        : m_arguments(highlightVisibility)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<WebCore::HighlightVisibility> m_arguments;
};
#endif

class HandleWheelEvent {
public:
    using Arguments = std::tuple<WebKit::WebWheelEvent, OptionSet<WebCore::WheelEventProcessingSteps>, std::optional<bool>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_HandleWheelEvent; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_HandleWheelEventReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<uint64_t, std::optional<WebCore::WheelScrollGestureState>, bool>;
    HandleWheelEvent(const WebKit::WebWheelEvent& event, const OptionSet<WebCore::WheelEventProcessingSteps>& processingSteps, const std::optional<bool>& willStartSwipe)
        : m_arguments(event, processingSteps, willStartSwipe)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebWheelEvent&, const OptionSet<WebCore::WheelEventProcessingSteps>&, const std::optional<bool>&> m_arguments;
};

#if PLATFORM(IOS_FAMILY)
class DispatchWheelEventWithoutScrolling {
public:
    using Arguments = std::tuple<WebKit::WebWheelEvent>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_DispatchWheelEventWithoutScrolling; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_DispatchWheelEventWithoutScrollingReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit DispatchWheelEventWithoutScrolling(const WebKit::WebWheelEvent& event)
        : m_arguments(event)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebKit::WebWheelEvent&> m_arguments;
};
#endif

class LastNavigationWasAppInitiated {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_LastNavigationWasAppInitiated; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_LastNavigationWasAppInitiatedReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<> m_arguments;
};

#if ENABLE(MEDIA_SESSION_COORDINATOR)
class CreateMediaSessionCoordinator {
public:
    using Arguments = std::tuple<String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_CreateMediaSessionCoordinator; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_CreateMediaSessionCoordinatorReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    explicit CreateMediaSessionCoordinator(const String& identifier)
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

#if ENABLE(IMAGE_ANALYSIS)
class UpdateWithTextRecognitionResult {
public:
    using Arguments = std::tuple<WebCore::TextRecognitionResult, WebCore::ElementContext, WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateWithTextRecognitionResult; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_UpdateWithTextRecognitionResultReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<WebKit::TextRecognitionUpdateResult>;
    UpdateWithTextRecognitionResult(const WebCore::TextRecognitionResult& result, const WebCore::ElementContext& element, const WebCore::FloatPoint& location)
        : m_arguments(result, element, location)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::TextRecognitionResult&, const WebCore::ElementContext&, const WebCore::FloatPoint&> m_arguments;
};
#endif

#if ENABLE(IMAGE_ANALYSIS)
class StartVisualTranslation {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_StartVisualTranslation; }
    static constexpr bool isSync = false;

    StartVisualTranslation(const String& sourceLanguageIdentifier, const String& targetLanguageIdentifier)
        : m_arguments(sourceLanguageIdentifier, targetLanguageIdentifier)
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

class ScrollToRect {
public:
    using Arguments = std::tuple<WebCore::FloatRect, WebCore::FloatPoint>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ScrollToRect; }
    static constexpr bool isSync = false;

    ScrollToRect(const WebCore::FloatRect& targetRect, const WebCore::FloatPoint& origin)
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

class NavigateServiceWorkerClient {
public:
    using Arguments = std::tuple<WebCore::ScriptExecutionContextIdentifier, URL>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_NavigateServiceWorkerClient; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_NavigateServiceWorkerClientReply; }
    static constexpr auto callbackThread = WTF::CompletionHandlerCallThread::ConstructionThread;
    using ReplyArguments = std::tuple<bool>;
    NavigateServiceWorkerClient(const WebCore::ScriptExecutionContextIdentifier& documentIdentifier, const URL& url)
        : m_arguments(documentIdentifier, url)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ScriptExecutionContextIdentifier&, const URL&> m_arguments;
};

#if ENABLE(ARKIT_INLINE_PREVIEW_IOS)
class ModelInlinePreviewDidLoad {
public:
    using Arguments = std::tuple<WebCore::PlatformLayerIdentifier>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ModelInlinePreviewDidLoad; }
    static constexpr bool isSync = false;

    explicit ModelInlinePreviewDidLoad(const WebCore::PlatformLayerIdentifier& layerID)
        : m_arguments(layerID)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlatformLayerIdentifier&> m_arguments;
};
#endif

#if ENABLE(ARKIT_INLINE_PREVIEW_IOS)
class ModelInlinePreviewDidFailToLoad {
public:
    using Arguments = std::tuple<WebCore::PlatformLayerIdentifier, WebCore::ResourceError>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_ModelInlinePreviewDidFailToLoad; }
    static constexpr bool isSync = false;

    ModelInlinePreviewDidFailToLoad(const WebCore::PlatformLayerIdentifier& layerID, const WebCore::ResourceError& error)
        : m_arguments(layerID, error)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::PlatformLayerIdentifier&, const WebCore::ResourceError&> m_arguments;
};
#endif

#if HAVE(UIKIT_RESIZABLE_WINDOWS)
class SetIsWindowResizingEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetIsWindowResizingEnabled; }
    static constexpr bool isSync = false;

    explicit SetIsWindowResizingEnabled(bool hasResizableWindows)
        : m_arguments(hasResizableWindows)
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

#if ENABLE(INTERACTION_REGIONS_IN_EVENT_REGION)
class SetInteractionRegionsEnabled {
public:
    using Arguments = std::tuple<bool>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetInteractionRegionsEnabled; }
    static constexpr bool isSync = false;

    explicit SetInteractionRegionsEnabled(bool enable)
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
#endif

class GenerateTestReport {
public:
    using Arguments = std::tuple<String, String>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_GenerateTestReport; }
    static constexpr bool isSync = false;

    GenerateTestReport(const String& message, const String& group)
        : m_arguments(message, group)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const String&, const String&> m_arguments;
};

#if ENABLE(ADVANCED_PRIVACY_PROTECTIONS)
class SetLinkDecorationFilteringData {
public:
    using Arguments = std::tuple<Vector<WebCore::LinkDecorationFilteringData>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetLinkDecorationFilteringData; }
    static constexpr bool isSync = false;

    explicit SetLinkDecorationFilteringData(const Vector<WebCore::LinkDecorationFilteringData>& strings)
        : m_arguments(strings)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::LinkDecorationFilteringData>&> m_arguments;
};
#endif

#if ENABLE(ADVANCED_PRIVACY_PROTECTIONS)
class SetAllowedQueryParametersForAdvancedPrivacyProtections {
public:
    using Arguments = std::tuple<Vector<WebCore::LinkDecorationFilteringData>>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_SetAllowedQueryParametersForAdvancedPrivacyProtections; }
    static constexpr bool isSync = false;

    explicit SetAllowedQueryParametersForAdvancedPrivacyProtections(const Vector<WebCore::LinkDecorationFilteringData>& allowedStrings)
        : m_arguments(allowedStrings)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const Vector<WebCore::LinkDecorationFilteringData>&> m_arguments;
};
#endif

#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
class PauseAllAnimations {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PauseAllAnimations; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_PauseAllAnimationsReply; }
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

#if ENABLE(ACCESSIBILITY_ANIMATION_CONTROL)
class PlayAllAnimations {
public:
    using Arguments = std::tuple<>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_PlayAllAnimations; }
    static constexpr bool isSync = false;

    static IPC::MessageName asyncMessageReplyName() { return IPC::MessageName::WebPage_PlayAllAnimationsReply; }
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

class UseRedirectionForCurrentNavigation {
public:
    using Arguments = std::tuple<WebCore::ResourceResponse>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UseRedirectionForCurrentNavigation; }
    static constexpr bool isSync = false;

    explicit UseRedirectionForCurrentNavigation(const WebCore::ResourceResponse& response)
        : m_arguments(response)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::ResourceResponse&> m_arguments;
};

class UpdateFrameSize {
public:
    using Arguments = std::tuple<WebCore::FrameIdentifier, WebCore::IntSize>;

    static IPC::MessageName name() { return IPC::MessageName::WebPage_UpdateFrameSize; }
    static constexpr bool isSync = false;

    UpdateFrameSize(const WebCore::FrameIdentifier& frame, const WebCore::IntSize& newSize)
        : m_arguments(frame, newSize)
    {
    }

    auto&& arguments()
    {
        return WTFMove(m_arguments);
    }

private:
    std::tuple<const WebCore::FrameIdentifier&, const WebCore::IntSize&> m_arguments;
};

} // namespace WebPage
} // namespace Messages
