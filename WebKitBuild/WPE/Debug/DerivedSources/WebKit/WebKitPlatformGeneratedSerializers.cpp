/*
 * Copyright (C) 2022 Apple Inc. All rights reserved.
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
#include "GeneratedSerializers.h"

#if OS(DARWIN)
#include "ArgumentCodersDarwin.h"
#endif
#if USE(UNIX_DOMAIN_SOCKETS)
#include "ArgumentCodersUnix.h"
#endif
#if OS(WINDOWS)
#include "ArgumentCodersWin.h"
#endif
#include "Decoder.h"
#include "Encoder.h"
#include "SharedMemory.h"
#include <wtf/ArgumentCoder.h>
#if OS(DARWIN)
#include <wtf/MachSendRight.h>
#endif
#include <wtf/RefCounted.h>
#if USE(UNIX_DOMAIN_SOCKETS)
#include <wtf/unix/UnixFileDescriptor.h>
#endif
#if OS(WINDOWS)
#include <wtf/win/Win32Handle.h>
#endif

template<size_t...> struct MembersInCorrectOrder;
template<size_t onlyOffset> struct MembersInCorrectOrder<onlyOffset> {
    static constexpr bool value = true;
};
template<size_t firstOffset, size_t secondOffset, size_t... remainingOffsets> struct MembersInCorrectOrder<firstOffset, secondOffset, remainingOffsets...> {
    static constexpr bool value = firstOffset > secondOffset ? false : MembersInCorrectOrder<secondOffset, remainingOffsets...>::value;
};

template<uint64_t...> struct BitsInIncreasingOrder;
template<uint64_t onlyBit> struct BitsInIncreasingOrder<onlyBit> {
    static constexpr bool value = true;
};
template<uint64_t firstBit, uint64_t secondBit, uint64_t... remainingBits> struct BitsInIncreasingOrder<firstBit, secondBit, remainingBits...> {
    static constexpr bool value = firstBit == secondBit >> 1 && BitsInIncreasingOrder<secondBit, remainingBits...>::value;
};

template<bool, bool> struct VirtualTableAndRefCountOverhead;
template<> struct VirtualTableAndRefCountOverhead<true, true> {
    virtual ~VirtualTableAndRefCountOverhead() { }
    unsigned refCount;
#if ASSERT_ENABLED
    bool m_isOwnedByMainThread;
    bool m_areThreadingChecksEnabled;
#endif
#if CHECK_REF_COUNTED_LIFECYCLE
    bool m_deletionHasBegun;
    bool m_adoptionIsRequired;
#endif
};
template<> struct VirtualTableAndRefCountOverhead<false, true> {
    unsigned refCount;
#if ASSERT_ENABLED
    bool m_isOwnedByMainThread;
    bool m_areThreadingChecksEnabled;
#endif
#if CHECK_REF_COUNTED_LIFECYCLE
    bool m_deletionHasBegun;
    bool m_adoptionIsRequired;
#endif
};
template<> struct VirtualTableAndRefCountOverhead<true, false> {
    virtual ~VirtualTableAndRefCountOverhead() { }
};
template<> struct VirtualTableAndRefCountOverhead<false, false> { };

#if COMPILER(GCC)
IGNORE_WARNINGS_BEGIN("invalid-offsetof")
#endif

namespace IPC {

void ArgumentCoder<WebKit::SharedMemoryHandle>::encode(Encoder& encoder, WebKit::SharedMemoryHandle&& instance)
{
#if USE(UNIX_DOMAIN_SOCKETS)
    static_assert(std::is_same_v<std::remove_cvref_t<decltype(instance.m_handle)>, UnixFileDescriptor>);
#endif
#if OS(DARWIN)
    static_assert(std::is_same_v<std::remove_cvref_t<decltype(instance.m_handle)>, MachSendRight>);
#endif
#if OS(WINDOWS)
    static_assert(std::is_same_v<std::remove_cvref_t<decltype(instance.m_handle)>, Win32Handle>);
#endif
    static_assert(std::is_same_v<std::remove_cvref_t<decltype(instance.m_size)>, size_t>);
    struct ShouldBeSameSizeAsSharedMemoryHandle : public VirtualTableAndRefCountOverhead<std::is_polymorphic_v<WebKit::SharedMemoryHandle>, false> {
#if USE(UNIX_DOMAIN_SOCKETS)
        UnixFileDescriptor m_handle;
#endif
#if OS(DARWIN)
        MachSendRight m_handle;
#endif
#if OS(WINDOWS)
        Win32Handle m_handle;
#endif
        size_t m_size;
    };
    static_assert(sizeof(ShouldBeSameSizeAsSharedMemoryHandle) == sizeof(WebKit::SharedMemoryHandle));
    static_assert(MembersInCorrectOrder < 0
#if USE(UNIX_DOMAIN_SOCKETS)
        , offsetof(WebKit::SharedMemoryHandle, m_handle)
#endif
#if OS(DARWIN)
        , offsetof(WebKit::SharedMemoryHandle, m_handle)
#endif
#if OS(WINDOWS)
        , offsetof(WebKit::SharedMemoryHandle, m_handle)
#endif
        , offsetof(WebKit::SharedMemoryHandle, m_size)
    >::value);
#if USE(UNIX_DOMAIN_SOCKETS)
    encoder << WTFMove(instance.m_handle);
#endif
#if OS(DARWIN)
    encoder << WTFMove(instance.m_handle);
#endif
#if OS(WINDOWS)
    encoder << WTFMove(instance.m_handle);
#endif
    encoder << WTFMove(instance.m_size);
}

std::optional<WebKit::SharedMemoryHandle> ArgumentCoder<WebKit::SharedMemoryHandle>::decode(Decoder& decoder)
{
#if USE(UNIX_DOMAIN_SOCKETS)
    auto m_handle = decoder.decode<UnixFileDescriptor>();
#endif
#if OS(DARWIN)
    auto m_handle = decoder.decode<MachSendRight>();
#endif
#if OS(WINDOWS)
    auto m_handle = decoder.decode<Win32Handle>();
#endif
    auto m_size = decoder.decode<size_t>();
    if (UNLIKELY(!decoder.isValid()))
        return std::nullopt;
    return {
        WebKit::SharedMemoryHandle {
#if USE(UNIX_DOMAIN_SOCKETS)
            WTFMove(*m_handle),
#endif
#if OS(DARWIN)
            WTFMove(*m_handle),
#endif
#if OS(WINDOWS)
            WTFMove(*m_handle),
#endif
            WTFMove(*m_size)
        }
    };
}

} // namespace IPC

namespace WTF {

} // namespace WTF

#if COMPILER(GCC)
IGNORE_WARNINGS_END
#endif
