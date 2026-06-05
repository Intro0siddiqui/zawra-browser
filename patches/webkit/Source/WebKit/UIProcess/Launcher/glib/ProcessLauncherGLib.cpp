#include "config.h"
#include "ProcessLauncher.h"

#include "Connection.h"
#include "IPCUtilities.h"
#include "ProcessProviderLibWPE.h"
#include <glib.h>
#include <wtf/FileSystem.h>
#include <wtf/RunLoop.h>
#include <wtf/UniStdExtras.h>
#include <wtf/glib/GUniquePtr.h>
#include <wtf/glib/Sandbox.h>
#include <wtf/text/CString.h>
#include <wtf/text/WTFString.h>

#if !USE(SYSTEM_MALLOC) && OS(LINUX)
#include <bmalloc/valgrind.h>
#endif

struct Zawra_Hajr_RingPair {
    uint64_t ring1_id;
    uint64_t ring2_id;
    int signal1_fd;
    int signal2_fd;
};

extern "C" int Zawra_Hajr_SpawnProcess(const char* path, const char** argv, int* out_socket);
extern "C" Zawra_Hajr_RingPair Zawra_Hajr_CreateRingPair(size_t size);

namespace WebKit {

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
    return launchOptions.extraInitializationData.get<HashTranslatorASCIILiteral>("enable-sandbox"_s) == "true"_s;
}

#include <sys/syscall.h>

#ifndef __NR_pidfd_open
#define __NR_pidfd_open 434
#endif

void ProcessLauncher::launchProcess()
{
    Zawra_Hajr_RingPair ringPair = Zawra_Hajr_CreateRingPair(1024 * 1024);

    gchar* ring1Str = g_strdup_printf("%" PRIu64, ringPair.ring1_id);
    gchar* ring2Str = g_strdup_printf("%" PRIu64, ringPair.ring2_id);
    
    // Open a pidfd for the current (UI) process to pass to the child
    int parentPidFD = syscall(__NR_pidfd_open, getpid(), 0);
    
    g_setenv("ZAWRA_HAJR_RING1", ring1Str, TRUE);
    g_setenv("ZAWRA_HAJR_RING2", ring2Str, TRUE);
    g_setenv("ZAWRA_HAJR_SIGNAL1", g_strdup_printf("%d", ringPair.signal1_fd), TRUE);
    g_setenv("ZAWRA_HAJR_SIGNAL2", g_strdup_printf("%d", ringPair.signal2_fd), TRUE);
    g_setenv("ZAWRA_HAJR_PARENT_PIDFD", g_strdup_printf("%d", parentPidFD), TRUE);
    
    int webkitSocketFD = ringPair.signal1_fd;

    g_free(ring1Str);
    g_free(ring2Str);

    GUniquePtr<gchar> processIdentifier(g_strdup_printf("%" PRIu64, m_launchOptions.processIdentifier.toUInt64()));
    GUniquePtr<gchar> webkitSocket(g_strdup_printf("%d", webkitSocketFD));

    String executablePath;
    switch (m_launchOptions.processType) {
    case ProcessType::Web:
        executablePath = executablePathOfWebProcess();
        break;
    case ProcessType::Network:
        executablePath = executablePathOfNetworkProcess();
        break;
#if ENABLE(GPU_PROCESS)
    case ProcessType::GPU:
        executablePath = executablePathOfGPUProcess();
        break;
#endif
    default:
        ASSERT_NOT_REACHED();
        return;
    }

    CString realExecutablePath = FileSystem::fileSystemRepresentation(executablePath);
    
    char* argv[4];
    argv[0] = const_cast<char*>(realExecutablePath.data());
    argv[1] = processIdentifier.get();
    argv[2] = webkitSocket.get();
    argv[3] = nullptr;

    m_processID = Zawra_Hajr_SpawnProcess(realExecutablePath.data(), const_cast<const char**>(argv), &webkitSocketFD);

    if (m_processID <= -1)
        g_error("Unable to spawn a new child process via Hajr");

    // UIProcess connection handle is signal2_fd
    int serverSocket = ringPair.signal2_fd;

    RunLoop::main().dispatch([protectedThis = Ref { *this }, this, serverSocket] {
        didFinishLaunchingProcess(m_processID, serverSocket);
    });
}

} // namespace WebKit
