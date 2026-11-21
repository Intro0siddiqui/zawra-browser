/*
 * Copyright (C) 2014 Igalia S.L.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "NetworkProcessMain.h"

#include "AuxiliaryProcessMain.h"
#include "NetworkProcess.h"
#include "NetworkSession.h"
#include <WebCore/NetworkStorageSession.h>
#include <sys/syscall.h>
#include <unistd.h>

#if USE(GCRYPT)
#include <pal/crypto/gcrypt/Initialization.h>
#endif

namespace WebKit {

class NetworkProcessMainSoup final : public AuxiliaryProcessMainBaseNoSingleton<NetworkProcess> {
public:
    bool platformInitialize() override
    {
#if USE(GCRYPT)
        PAL::GCrypt::initialize();
#endif
        return true;
    }

    void platformFinalize() override
    {
        Vector<PAL::SessionID> sessionIDs;
        process().forEachNetworkSession([&sessionIDs](auto& session) {
            sessionIDs.append(session.sessionID());
        });
        for (auto& sessionID : sessionIDs)
            process().destroySession(sessionID);
    }
};

extern "C" int Z_Init_Subsystems(const char* profile_path);
extern "C" int Z_Register_Protocols();
extern "C" void hajr_trace_set_process_kind(uint8_t);

int NetworkProcessMain(int argc, char** argv)
{
    hajr_trace_set_process_kind(3);
    fprintf(stderr, "[NETCONN-MAIN] NetworkProcessMain ENTER argc=%d pid=%d tid=%d\n", argc, (int)getpid(), (int)syscall(SYS_gettid));
    Z_Init_Subsystems("/tmp/zawra-profile");
    fprintf(stderr, "[NETCONN-MAIN] NetworkProcessMain Zawra_Init_Subsystems done pid=%d tid=%d\n", (int)getpid(), (int)syscall(SYS_gettid));
    Z_Register_Protocols();
    fprintf(stderr, "[NETCONN-MAIN] NetworkProcessMain Zawra_Register_Protocols done pid=%d tid=%d\n", (int)getpid(), (int)syscall(SYS_gettid));
    int result = AuxiliaryProcessMain<NetworkProcessMainSoup>(argc, argv);
    fprintf(stderr, "[NETCONN-MAIN] NetworkProcessMain AuxiliaryProcessMain returned result=%d pid=%d tid=%d\n", result, (int)getpid(), (int)syscall(SYS_gettid));
    return result;
}

} // namespace WebKit
