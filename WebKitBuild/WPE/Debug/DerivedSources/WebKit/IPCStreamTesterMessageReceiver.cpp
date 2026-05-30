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
#if ENABLE(IPC_TESTING_API)
#include "IPCStreamTester.h"

#include "Decoder.h" // NOLINT
#include "HandleMessage.h" // NOLINT
#include "IPCStreamTesterMessages.h" // NOLINT
#include "SharedMemory.h" // NOLINT

#if ENABLE(IPC_TESTING_API)
#include "JSIPCBinding.h"
#endif

namespace WebKit {

void IPCStreamTester::didReceiveStreamMessage(IPC::StreamServerConnection& connection, IPC::Decoder& decoder)
{
    if (decoder.messageName() == Messages::IPCStreamTester::AsyncMessage::name())
        return IPC::handleMessageAsync<Messages::IPCStreamTester::AsyncMessage>(connection.connection(), decoder, this, &IPCStreamTester::asyncMessage);
    if (decoder.messageName() == Messages::IPCStreamTester::SyncMessageReturningSharedMemory1::name())
        return IPC::handleMessageSynchronous<Messages::IPCStreamTester::SyncMessageReturningSharedMemory1>(connection, decoder, this, &IPCStreamTester::syncMessageReturningSharedMemory1);
    if (decoder.messageName() == Messages::IPCStreamTester::SyncCrashOnZero::name())
        return IPC::handleMessageSynchronous<Messages::IPCStreamTester::SyncCrashOnZero>(connection, decoder, this, &IPCStreamTester::syncCrashOnZero);
    if (decoder.messageName() == Messages::IPCStreamTester::CheckAutoreleasePool::name())
        return IPC::handleMessageSynchronous<Messages::IPCStreamTester::CheckAutoreleasePool>(connection, decoder, this, &IPCStreamTester::checkAutoreleasePool);
    UNUSED_PARAM(decoder);
    UNUSED_PARAM(connection);
#if ENABLE(IPC_TESTING_API)
    if (connection.connection().ignoreInvalidMessageForTesting())
        return;
#endif // ENABLE(IPC_TESTING_API)
    ASSERT_NOT_REACHED_WITH_MESSAGE("Unhandled stream message %s to %" PRIu64, IPC::description(decoder.messageName()), decoder.destinationID());
}

} // namespace WebKit

#if ENABLE(IPC_TESTING_API)

namespace IPC {

template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::IPCStreamTester_SyncMessageReturningSharedMemory1>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::IPCStreamTester::SyncMessageReturningSharedMemory1::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::IPCStreamTester_SyncMessageReturningSharedMemory1>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::IPCStreamTester::SyncMessageReturningSharedMemory1::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::IPCStreamTester_SyncCrashOnZero>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::IPCStreamTester::SyncCrashOnZero::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::IPCStreamTester_SyncCrashOnZero>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::IPCStreamTester::SyncCrashOnZero::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::IPCStreamTester_CheckAutoreleasePool>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::IPCStreamTester::CheckAutoreleasePool::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::IPCStreamTester_CheckAutoreleasePool>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::IPCStreamTester::CheckAutoreleasePool::ReplyArguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessage<MessageName::IPCStreamTester_AsyncMessage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::IPCStreamTester::AsyncMessage::Arguments>(globalObject, decoder);
}
template<> std::optional<JSC::JSValue> jsValueForDecodedMessageReply<MessageName::IPCStreamTester_AsyncMessage>(JSC::JSGlobalObject* globalObject, Decoder& decoder)
{
    return jsValueForDecodedArguments<Messages::IPCStreamTester::AsyncMessage::ReplyArguments>(globalObject, decoder);
}

}

#endif


#endif // ENABLE(IPC_TESTING_API)
