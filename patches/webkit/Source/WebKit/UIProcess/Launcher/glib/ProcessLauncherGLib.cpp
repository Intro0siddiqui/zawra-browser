/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 * Portions Copyright (c) 2010 Motorola Mobility, Inc.  All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY MOTOROLA INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MOTOROLA INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "ProcessLauncher.h"

#include "BubblewrapLauncher.h"
#include "Connection.h"
#include "FlatpakLauncher.h"
#include "IPCUtilities.h"
#include "ProcessExecutablePath.h"
#include <errno.h>
#include <fcntl.h>
#include <glib.h>
#include <wtf/FileSystem.h>
#include <wtf/RunLoop.h>
#include <wtf/UniStdExtras.h>
#include <wtf/glib/GUniquePtr.h>
#include <wtf/glib/Sandbox.h>
#include <wtf/text/CString.h>
#include <wtf/text/WTFString.h>

#if USE(LIBWPE)
#include "ProcessProviderLibWPE.h"
#endif

#if !USE(SYSTEM_MALLOC) && OS(LINUX)
#include <bmalloc/valgrind.h>
#endif

extern "C" int Zawra_Hajr_SpawnProcess(const char* path, const char** argv, int* out_socket);
extern "C" uint64_t Zawra_Hajr_CreateBootstrapRing(size_t size);

namespace WebKit {

#if OS(LINUX)
static bool isFlatpakSpawnUsable()
{
    static std::optional<bool> ret;
    if (ret)
        return *ret;

    // For our usage to work we need flatpak >= 1.5.2 on the host and flatpak-xdg-utils > 1.0.1 in the sandbox
    GRefPtr<GSubprocess> process = adoptGRef(g_subprocess_new(static_cast<GSubprocessFlags>(G_SUBPROCESS_FLAGS_STDOUT_SILENCE | G_SUBPROCESS_FLAGS_STDERR_SILENCE),
        nullptr, "flatpak-spawn", "--sandbox", "--sandbox-expose-path-ro-try=/this_path_doesnt_exist", "echo", nullptr));

    if (!process.get())
        ret = false;
    else
        ret = g_subprocess_wait_check(process.get(), nullptr, nullptr);

    return *ret;
}
#endif

static int connectionOptions()
{
#if USE(LIBWPE) && !ENABLE(BUBBLEWRAP_SANDBOX)
    // When using the WPE process launcher API, we cannot use CLOEXEC for the client socket because
    // we need to leak it to the child process.
    if (ProcessProviderLibWPE::singleton().isEnabled())
        return IPC::PlatformConnectionOptions::SetCloexecOnServer;
#endif

    // We use CLOEXEC for the client socket here even though we need to leak it to the child,
    // because we don't want it leaking to xdg-dbus-proxy. If the IPC socket is unexpectedly open in
    // an extra subprocess, WebKit won't notice when its child process crashes. We can ensure it
    // gets leaked into only the correct subprocess by using g_subprocess_launcher_take_fd() later.
    return IPC::PlatformConnectionOptions::SetCloexecOnClient | IPC::PlatformConnectionOptions::SetCloexecOnServer;
}

static bool isSandboxEnabled(const ProcessLauncher::LaunchOptions& launchOptions)
{
#if !USE(SYSTEM_MALLOC)
    if (RUNNING_ON_VALGRIND)
        return false;
#endif

    if (const char* sandboxEnv = g_getenv("WEBKIT_DISABLE_SANDBOX_THIS_IS_DANGEROUS")) {
        if (!strcmp(sandboxEnv, "1"))
            return false;
    }

#if !ENABLE(2022_GLIB_API)
    if (const char* sandboxEnv = g_getenv("WEBKIT_FORCE_SANDBOX")) {
        if (!strcmp(sandboxEnv, "1"))
            return true;

        static bool once = false;
        if (!once) {
            g_warning("WEBKIT_FORCE_SANDBOX no longer allows disabling the sandbox. Use WEBKIT_DISABLE_SANDBOX_THIS_IS_DANGEROUS=1 instead.");
            once = true;
        }
    }
#endif

    return launchOptions.extraInitializationData.get<HashTranslatorASCIILiteral>("enable-sandbox"_s) == "true"_s;
}

void ProcessLauncher::launchProcess()
{
    uint64_t ringID = Zawra_Hajr_CreateBootstrapRing(1024 * 1024);
    IPC::SocketPair socketPair = IPC::createPlatformConnection(connectionOptions());

    gchar* ringStr = g_strdup_printf("%" PRIu64, ringID);
    gchar* envClient = g_strdup_printf("ZAWRA_HAJR_RING_%d", socketPair.client);
    g_setenv(envClient, ringStr, TRUE);
    g_free(envClient);

    gchar* envServer = g_strdup_printf("ZAWRA_HAJR_RING_%d", socketPair.server);
    g_setenv(envServer, ringStr, TRUE);
    g_free(envServer);
    g_free(ringStr);

    GUniquePtr<gchar> processIdentifier(g_strdup_printf("%" PRIu64, m_launchOptions.processIdentifier.toUInt64()));
    GUniquePtr<gchar> webkitSocket(g_strdup_printf("%d", socketPair.client));

#if USE(LIBWPE) && !ENABLE(BUBBLEWRAP_SANDBOX)
    if (ProcessProviderLibWPE::singleton().isEnabled()) {
        unsigned nargs = 3;
        char** argv = g_newa(char*, nargs);
        unsigned i = 0;
        argv[i++] = processIdentifier.get();
        argv[i++] = webkitSocket.get();
        argv[i++] = nullptr;

        m_processID = ProcessProviderLibWPE::singleton().launchProcess(m_launchOptions, argv, socketPair.client);
        if (m_processID <= -1)
            g_error("Unable to spawn a new child process");

        // We've finished launching the process, message back to the main run loop.
        RunLoop::main().dispatch([protectedThis = Ref { *this }, this, serverSocket = socketPair.server] {
            didFinishLaunchingProcess(m_processID, IPC::Connection::Identifier { serverSocket });
        });

        return;
    }
#endif

    String executablePath;
    CString realExecutablePath;
    switch (m_launchOptions.processType) {
    case ProcessLauncher::ProcessType::Web:
        executablePath = executablePathOfWebProcess();
        break;
    case ProcessLauncher::ProcessType::Network:
        executablePath = executablePathOfNetworkProcess();
        break;
#if ENABLE(GPU_PROCESS)
    case ProcessLauncher::ProcessType::GPU:
        executablePath = executablePathOfGPUProcess();
        break;
#endif
    default:
        ASSERT_NOT_REACHED();
        return;
    }

    realExecutablePath = FileSystem::fileSystemRepresentation(executablePath);
    unsigned nargs = 4; // size of the argv array for g_spawn_async()

#if ENABLE(DEVELOPER_MODE)
    Vector<CString> prefixArgs;
    if (!m_launchOptions.processCmdPrefix.isNull()) {
        for (auto& arg : m_launchOptions.processCmdPrefix.split(' '))
            prefixArgs.append(arg.utf8());
        nargs += prefixArgs.size();
    }

    bool configureJSCForTesting = false;
    if (m_launchOptions.processType == ProcessLauncher::ProcessType::Web && m_client && m_client->shouldConfigureJSCForTesting()) {
        configureJSCForTesting = true;
        nargs++;
    }
#endif

    char** argv = g_newa(char*, nargs);
    unsigned i = 0;
#if ENABLE(DEVELOPER_MODE)
    // If there's a prefix command, put it before the rest of the args.
    for (auto& arg : prefixArgs)
        argv[i++] = const_cast<char*>(arg.data());
#endif
    argv[i++] = const_cast<char*>(realExecutablePath.data());
    argv[i++] = processIdentifier.get();
    argv[i++] = webkitSocket.get();
#if ENABLE(DEVELOPER_MODE)
    if (configureJSCForTesting)
        argv[i++] = const_cast<char*>("--configure-jsc-for-testing");
#endif
    argv[i++] = nullptr;

    m_processID = Zawra_Hajr_SpawnProcess(realExecutablePath.data(), const_cast<const char**>(argv), &socketPair.client);
    if (m_processID <= 0)
        g_error("Unable to spawn a new child process via Hajr");

    // We've finished launching the process, message back to the main run loop.
    RunLoop::main().dispatch([protectedThis = Ref { *this }, this, serverSocket = socketPair.server] {
        didFinishLaunchingProcess(m_processID, IPC::Connection::Identifier(static_cast<uint64_t>(serverSocket)));
    });
}

void ProcessLauncher::terminateProcess()
{
    if (m_isLaunching) {
        invalidate();
        return;
    }

    if (!m_processID)
        return;

#if USE(LIBWPE) && !ENABLE(BUBBLEWRAP_SANDBOX)
    if (ProcessProviderLibWPE::singleton().isEnabled())
        ProcessProviderLibWPE::singleton().kill(m_processID);
    else
        kill(m_processID, SIGKILL);
#else
    kill(m_processID, SIGKILL);
#endif

    m_processID = 0;
}

void ProcessLauncher::platformInvalidate()
{
}

} // namespace WebKit
