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

#include "config.h"
#include "WebProcessProxy.h"

#include "ArgumentCoders.h" // NOLINT
#if ENABLE(GPU_PROCESS)
#include "Connection.h" // NOLINT
#endif
#include "Decoder.h" // NOLINT
#if HAVE(CVDISPLAYLINK)
#include "DisplayLinkObserverID.h" // NOLINT
#endif
#if ENABLE(GPU_PROCESS)
#include "GPUProcessConnectionParameters.h" // NOLINT
#endif
#include "HandleMessage.h" // NOLINT
#include "NetworkProcessConnectionInfo.h" // NOLINT
#include "SessionState.h" // NOLINT
#if PLATFORM(GTK) || PLATFORM(WPE)
#include "UserMessage.h" // NOLINT
#endif
#include "WebCoreArgumentCoders.h" // NOLINT
#include "WebPageProxyIdentifier.h" // NOLINT
#include "WebProcessProxyMessages.h" // NOLINT
#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
#include <WebCore/CaptionUserPreferences.h> // NOLINT
#endif
#include <WebCore/FrameIdentifier.h> // NOLINT
#include <WebCore/MessageWithMessagePorts.h> // NOLINT
#include <WebCore/NotificationData.h> // NOLINT
#include <WebCore/PageIdentifier.h> // NOLINT
#include <WebCore/PrewarmInformation.h> // NOLINT
#include <WebCore/RegistrableDomain.h> // NOLINT
#include <WebCore/RenderTreeAsText.h> // NOLINT
#include <WebCore/SecurityOriginData.h> // NOLINT
#include <optional> // NOLINT
#include <wtf/OptionSet.h> // NOLINT
#include <wtf/URLHash.h> // NOLINT
#include <wtf/Vector.h> // NOLINT
#include <wtf/text/WTFString.h> // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void WebProcessProxy::didReceiveWebProcessProxyMessage(IPC::Connection& connection, IPC::Decoder& decoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::WebProcessProxy::UpdateBackForwardItem::name())
        return IPC::handleMessage<Messages::WebProcessProxy::UpdateBackForwardItem>(connection, decoder, this, &WebProcessProxy::updateBackForwardItem);
    if (decoder.messageName() == Messages::WebProcessProxy::DidDestroyFrame::name())
        return IPC::handleMessage<Messages::WebProcessProxy::DidDestroyFrame>(connection, decoder, this, &WebProcessProxy::didDestroyFrame);
    if (decoder.messageName() == Messages::WebProcessProxy::DidDestroyUserGestureToken::name())
        return IPC::handleMessage<Messages::WebProcessProxy::DidDestroyUserGestureToken>(connection, decoder, this, &WebProcessProxy::didDestroyUserGestureToken);
    if (decoder.messageName() == Messages::WebProcessProxy::EnableSuddenTermination::name())
        return IPC::handleMessage<Messages::WebProcessProxy::EnableSuddenTermination>(connection, decoder, this, &WebProcessProxy::enableSuddenTermination);
    if (decoder.messageName() == Messages::WebProcessProxy::DisableSuddenTermination::name())
        return IPC::handleMessage<Messages::WebProcessProxy::DisableSuddenTermination>(connection, decoder, this, &WebProcessProxy::disableSuddenTermination);
#if ENABLE(GPU_PROCESS)
    if (decoder.messageName() == Messages::WebProcessProxy::CreateGPUProcessConnection::name())
        return IPC::handleMessage<Messages::WebProcessProxy::CreateGPUProcessConnection>(connection, decoder, this, &WebProcessProxy::createGPUProcessConnection);
#endif
    if (decoder.messageName() == Messages::WebProcessProxy::SetIsHoldingLockedFiles::name())
        return IPC::handleMessage<Messages::WebProcessProxy::SetIsHoldingLockedFiles>(connection, decoder, this, &WebProcessProxy::setIsHoldingLockedFiles);
    if (decoder.messageName() == Messages::WebProcessProxy::DidExceedActiveMemoryLimit::name())
        return IPC::handleMessage<Messages::WebProcessProxy::DidExceedActiveMemoryLimit>(connection, decoder, this, &WebProcessProxy::didExceedActiveMemoryLimit);
    if (decoder.messageName() == Messages::WebProcessProxy::DidExceedInactiveMemoryLimit::name())
        return IPC::handleMessage<Messages::WebProcessProxy::DidExceedInactiveMemoryLimit>(connection, decoder, this, &WebProcessProxy::didExceedInactiveMemoryLimit);
    if (decoder.messageName() == Messages::WebProcessProxy::DidExceedCPULimit::name())
        return IPC::handleMessage<Messages::WebProcessProxy::DidExceedCPULimit>(connection, decoder, this, &WebProcessProxy::didExceedCPULimit);
    if (decoder.messageName() == Messages::WebProcessProxy::StopResponsivenessTimer::name())
        return IPC::handleMessage<Messages::WebProcessProxy::StopResponsivenessTimer>(connection, decoder, this, &WebProcessProxy::stopResponsivenessTimer);
    if (decoder.messageName() == Messages::WebProcessProxy::DidReceiveBackgroundResponsivenessPing::name())
        return IPC::handleMessage<Messages::WebProcessProxy::DidReceiveBackgroundResponsivenessPing>(connection, decoder, this, &WebProcessProxy::didReceiveBackgroundResponsivenessPing);
    if (decoder.messageName() == Messages::WebProcessProxy::MemoryPressureStatusChanged::name())
        return IPC::handleMessage<Messages::WebProcessProxy::MemoryPressureStatusChanged>(connection, decoder, this, &WebProcessProxy::memoryPressureStatusChanged);
    if (decoder.messageName() == Messages::WebProcessProxy::DidCollectPrewarmInformation::name())
        return IPC::handleMessage<Messages::WebProcessProxy::DidCollectPrewarmInformation>(connection, decoder, this, &WebProcessProxy::didCollectPrewarmInformation);
#if PLATFORM(COCOA)
    if (decoder.messageName() == Messages::WebProcessProxy::CacheMediaMIMETypes::name())
        return IPC::handleMessage<Messages::WebProcessProxy::CacheMediaMIMETypes>(connection, decoder, this, &WebProcessProxy::cacheMediaMIMETypes);
#endif
#if PLATFORM(MAC)
    if (decoder.messageName() == Messages::WebProcessProxy::RequestHighPerformanceGPU::name())
        return IPC::handleMessage<Messages::WebProcessProxy::RequestHighPerformanceGPU>(connection, decoder, this, &WebProcessProxy::requestHighPerformanceGPU);
    if (decoder.messageName() == Messages::WebProcessProxy::ReleaseHighPerformanceGPU::name())
        return IPC::handleMessage<Messages::WebProcessProxy::ReleaseHighPerformanceGPU>(connection, decoder, this, &WebProcessProxy::releaseHighPerformanceGPU);
#endif
#if HAVE(CVDISPLAYLINK)
    if (decoder.messageName() == Messages::WebProcessProxy::StartDisplayLink::name())
        return IPC::handleMessage<Messages::WebProcessProxy::StartDisplayLink>(connection, decoder, this, &WebProcessProxy::startDisplayLink);
    if (decoder.messageName() == Messages::WebProcessProxy::StopDisplayLink::name())
        return IPC::handleMessage<Messages::WebProcessProxy::StopDisplayLink>(connection, decoder, this, &WebProcessProxy::stopDisplayLink);
    if (decoder.messageName() == Messages::WebProcessProxy::SetDisplayLinkPreferredFramesPerSecond::name())
        return IPC::handleMessage<Messages::WebProcessProxy::SetDisplayLinkPreferredFramesPerSecond>(connection, decoder, this, &WebProcessProxy::setDisplayLinkPreferredFramesPerSecond);
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
    if (decoder.messageName() == Messages::WebProcessProxy::SendMessageToWebContext::name())
        return IPC::handleMessage<Messages::WebProcessProxy::SendMessageToWebContext>(connection, decoder, this, &WebProcessProxy::sendMessageToWebContext);
    if (decoder.messageName() == Messages::WebProcessProxy::SendMessageToWebContextWithReply::name())
        return IPC::handleMessageAsync<Messages::WebProcessProxy::SendMessageToWebContextWithReply>(connection, decoder, this, &WebProcessProxy::sendMessageToWebContextWithReply);
#endif
    if (decoder.messageName() == Messages::WebProcessProxy::CreateSpeechRecognitionServer::name())
        return IPC::handleMessage<Messages::WebProcessProxy::CreateSpeechRecognitionServer>(connection, decoder, this, &WebProcessProxy::createSpeechRecognitionServer);
    if (decoder.messageName() == Messages::WebProcessProxy::DestroySpeechRecognitionServer::name())
        return IPC::handleMessage<Messages::WebProcessProxy::DestroySpeechRecognitionServer>(connection, decoder, this, &WebProcessProxy::destroySpeechRecognitionServer);
    if (decoder.messageName() == Messages::WebProcessProxy::SystemBeep::name())
        return IPC::handleMessage<Messages::WebProcessProxy::SystemBeep>(connection, decoder, this, &WebProcessProxy::systemBeep);
#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
    if (decoder.messageName() == Messages::WebProcessProxy::SetCaptionDisplayMode::name())
        return IPC::handleMessage<Messages::WebProcessProxy::SetCaptionDisplayMode>(connection, decoder, this, &WebProcessProxy::setCaptionDisplayMode);
    if (decoder.messageName() == Messages::WebProcessProxy::SetCaptionLanguage::name())
        return IPC::handleMessage<Messages::WebProcessProxy::SetCaptionLanguage>(connection, decoder, this, &WebProcessProxy::setCaptionLanguage);
#endif
    if (decoder.messageName() == Messages::WebProcessProxy::GetNotifications::name())
        return IPC::handleMessageAsync<Messages::WebProcessProxy::GetNotifications>(connection, decoder, this, &WebProcessProxy::getNotifications);
    if (decoder.messageName() == Messages::WebProcessProxy::SetAppBadge::name())
        return IPC::handleMessage<Messages::WebProcessProxy::SetAppBadge>(connection, decoder, this, &WebProcessProxy::setAppBadge);
    if (decoder.messageName() == Messages::WebProcessProxy::SetClientBadge::name())
        return IPC::handleMessage<Messages::WebProcessProxy::SetClientBadge>(connection, decoder, this, &WebProcessProxy::setClientBadge);
    if (decoder.messageName() == Messages::WebProcessProxy::PostMessageToRemote::name())
        return IPC::handleMessage<Messages::WebProcessProxy::PostMessageToRemote>(connection, decoder, this, &WebProcessProxy::postMessageToRemote);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

bool WebProcessProxy::didReceiveSyncWebProcessProxyMessage(IPC::Connection& connection, IPC::Decoder& decoder, UniqueRef<IPC::Encoder>& replyEncoder)
{
    Ref protectedThis { *this };
    if (decoder.messageName() == Messages::WebProcessProxy::ShouldTerminate::name())
        return IPC::handleMessageSynchronous<Messages::WebProcessProxy::ShouldTerminate>(connection, decoder, replyEncoder, this, &WebProcessProxy::shouldTerminate);
    if (decoder.messageName() == Messages::WebProcessProxy::GetNetworkProcessConnection::name())
        return IPC::handleMessageSynchronous<Messages::WebProcessProxy::GetNetworkProcessConnection>(connection, decoder, replyEncoder, this, &WebProcessProxy::getNetworkProcessConnection);
#if PLATFORM(MAC)
    if (decoder.messageName() == Messages::WebProcessProxy::IsAXAuthenticated::name())
        return IPC::handleMessageSynchronous<Messages::WebProcessProxy::IsAXAuthenticated>(connection, decoder, replyEncoder, this, &WebProcessProxy::isAXAuthenticated);
#endif
    if (decoder.messageName() == Messages::WebProcessProxy::RenderTreeAsText::name())
        return IPC::handleMessageSynchronous<Messages::WebProcessProxy::RenderTreeAsText>(connection, decoder, replyEncoder, this, &WebProcessProxy::renderTreeAsText);
    UNUSED_PARAM(connection);
    UNUSED_PARAM(decoder);
    UNUSED_PARAM(replyEncoder);
#if ENABLE(IPC_TESTING_API)
    if (connection.ignoreInvalidMessageForTesting())
        return false;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled synchronous message %s to %" PRIu64, description(decoder.messageName()), decoder.destinationID());
    return false;
}

} // namespace WebKit

#if ENABLE(IPC_TESTING_API)

namespace IPC {

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_UpdateBackForwardItem>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::UpdateBackForwardItem::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_DidDestroyFrame>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::DidDestroyFrame::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_DidDestroyUserGestureToken>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::DidDestroyUserGestureToken::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_ShouldTerminate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::ShouldTerminate::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcessProxy_ShouldTerminate>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::ShouldTerminate::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_EnableSuddenTermination>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::EnableSuddenTermination::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_DisableSuddenTermination>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::DisableSuddenTermination::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_GetNetworkProcessConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::GetNetworkProcessConnection::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcessProxy_GetNetworkProcessConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::GetNetworkProcessConnection::ReplyArguments>(globalObject, decoder);
}
#if ENABLE(GPU_PROCESS)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_CreateGPUProcessConnection>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::CreateGPUProcessConnection::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_SetIsHoldingLockedFiles>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::SetIsHoldingLockedFiles::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_DidExceedActiveMemoryLimit>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::DidExceedActiveMemoryLimit::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_DidExceedInactiveMemoryLimit>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::DidExceedInactiveMemoryLimit::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_DidExceedCPULimit>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::DidExceedCPULimit::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_StopResponsivenessTimer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::StopResponsivenessTimer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_DidReceiveBackgroundResponsivenessPing>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::DidReceiveBackgroundResponsivenessPing::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_MemoryPressureStatusChanged>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::MemoryPressureStatusChanged::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_DidCollectPrewarmInformation>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::DidCollectPrewarmInformation::Arguments>(globalObject, decoder);
}
#if PLATFORM(COCOA)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_CacheMediaMIMETypes>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::CacheMediaMIMETypes::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(MAC)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_RequestHighPerformanceGPU>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::RequestHighPerformanceGPU::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_ReleaseHighPerformanceGPU>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::ReleaseHighPerformanceGPU::Arguments>(globalObject, decoder);
}
#endif
#if HAVE(CVDISPLAYLINK)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_StartDisplayLink>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::StartDisplayLink::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_StopDisplayLink>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::StopDisplayLink::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_SetDisplayLinkPreferredFramesPerSecond>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::SetDisplayLinkPreferredFramesPerSecond::Arguments>(globalObject, decoder);
}
#endif
#if PLATFORM(GTK) || PLATFORM(WPE)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_SendMessageToWebContext>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::SendMessageToWebContext::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_SendMessageToWebContextWithReply>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::SendMessageToWebContextWithReply::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcessProxy_SendMessageToWebContextWithReply>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::SendMessageToWebContextWithReply::ReplyArguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_CreateSpeechRecognitionServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::CreateSpeechRecognitionServer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_DestroySpeechRecognitionServer>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::DestroySpeechRecognitionServer::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_SystemBeep>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::SystemBeep::Arguments>(globalObject, decoder);
}
#if PLATFORM(MAC)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_IsAXAuthenticated>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::IsAXAuthenticated::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcessProxy_IsAXAuthenticated>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::IsAXAuthenticated::ReplyArguments>(globalObject, decoder);
}
#endif
#if HAVE(MEDIA_ACCESSIBILITY_FRAMEWORK)
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_SetCaptionDisplayMode>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::SetCaptionDisplayMode::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_SetCaptionLanguage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::SetCaptionLanguage::Arguments>(globalObject, decoder);
}
#endif
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_GetNotifications>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::GetNotifications::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcessProxy_GetNotifications>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::GetNotifications::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_SetAppBadge>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::SetAppBadge::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_SetClientBadge>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::SetClientBadge::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_PostMessageToRemote>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::PostMessageToRemote::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::WebProcessProxy_RenderTreeAsText>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::RenderTreeAsText::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::WebProcessProxy_RenderTreeAsText>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::WebProcessProxy::RenderTreeAsText::ReplyArguments>(globalObject, decoder);
}

}

#endif

