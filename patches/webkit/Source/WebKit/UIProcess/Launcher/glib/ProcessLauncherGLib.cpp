#include "config.h"
#include "ProcessLauncher.h"

#include "Connection.h"
#include "IPCUtilities.h"
#include "ProcessExecutablePath.h"
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

extern "C" int Z_Hajr_SpawnProcess(const char* path, const char** argv, int* out_socket);
extern "C" Zawra_Hajr_RingPair Z_Hajr_CreateRingPair(size_t size);

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
#include <sys/prctl.h>
#include <sys/socket.h>
#include <unistd.h>

#ifndef __NR_pidfd_open
#define __NR_pidfd_open 434
#endif

void ProcessLauncher::launchProcess()
{
    // Create a DGRAM socket pair for FD transfer via SCM_RIGHTS.
    // pidfd_getfd requires CAP_SYS_PTRACE which sandboxed children don't have,
    // so we use SCM_RIGHTS on a side-channel socket instead.
    int fdTransferFds[2] = { -1, -1 };
    if (socketpair(AF_UNIX, SOCK_DGRAM | SOCK_CLOEXEC, 0, fdTransferFds) == -1) {
        fprintf(stderr, "[CRASH-V2] socketpair for FD transfer failed: errno=%d\n", errno);
        fdTransferFds[0] = -1;
        fdTransferFds[1] = -1;
    }

    int parentPidFD = syscall(__NR_pidfd_open, getpid(), 0);

    String executablePath;
    Zawra_Hajr_RingPair ringPair;
    gchar* ring1Str = nullptr;
    gchar* ring2Str = nullptr;
    int webkitSocketFD = -1;
    const char* processTypeName = "Unknown";

    switch (m_launchOptions.processType) {
    case ProcessType::Web: {
        processTypeName = "Web";
        ringPair = Z_Hajr_CreateRingPair(1024 * 1024);
        ring1Str = g_strdup_printf("%" PRIu64, ringPair.ring1_id);
        ring2Str = g_strdup_printf("%" PRIu64, ringPair.ring2_id);
        g_setenv("ZAWRA_HAJR_RING1", ring1Str, TRUE);
        g_setenv("ZAWRA_HAJR_RING2", ring2Str, TRUE);
        g_setenv("ZAWRA_HAJR_SIGNAL1", g_strdup_printf("%d", ringPair.signal1_fd), TRUE);
        g_setenv("ZAWRA_HAJR_SIGNAL2", g_strdup_printf("%d", ringPair.signal2_fd), TRUE);
        g_setenv("ZAWRA_HAJR_PARENT_PIDFD", g_strdup_printf("%d", parentPidFD), TRUE);
        g_setenv("ZAWRA_HAJR_FDTRANSFER", g_strdup_printf("%d", fdTransferFds[1]), TRUE);
        fprintf(stderr, "[HAJR-CONN] launchProcess: processType=%s processIdentifier=%" PRIu64 " ring1=%" PRIu64 " ring2=%" PRIu64 " sig1=%d sig2=%d fdTransfer=%d parentPidFD=%d\n",
            processTypeName, (uint64_t)m_launchOptions.processIdentifier.toUInt64(), ringPair.ring1_id, ringPair.ring2_id,
            ringPair.signal1_fd, ringPair.signal2_fd, fdTransferFds[1], parentPidFD);
        webkitSocketFD = ringPair.signal1_fd;
        executablePath = executablePathOfWebProcess();
        break;
    }
    case ProcessType::Network: {
        processTypeName = "Network";
        ringPair = Z_Hajr_CreateRingPair(1024 * 1024);
        ring1Str = g_strdup_printf("%" PRIu64, ringPair.ring1_id);
        ring2Str = g_strdup_printf("%" PRIu64, ringPair.ring2_id);
        g_setenv("ZAWRA_HAJR_RING1", ring1Str, TRUE);
        g_setenv("ZAWRA_HAJR_RING2", ring2Str, TRUE);
        g_setenv("ZAWRA_HAJR_SIGNAL1", g_strdup_printf("%d", ringPair.signal1_fd), TRUE);
        g_setenv("ZAWRA_HAJR_SIGNAL2", g_strdup_printf("%d", ringPair.signal2_fd), TRUE);
        g_setenv("ZAWRA_HAJR_PARENT_PIDFD", g_strdup_printf("%d", parentPidFD), TRUE);
        g_setenv("ZAWRA_HAJR_FDTRANSFER", g_strdup_printf("%d", fdTransferFds[1]), TRUE);
        fprintf(stderr, "[HAJR-CONN] launchProcess: processType=%s processIdentifier=%" PRIu64 " ring1=%" PRIu64 " ring2=%" PRIu64 " sig1=%d sig2=%d fdTransfer=%d parentPidFD=%d\n",
            processTypeName, (uint64_t)m_launchOptions.processIdentifier.toUInt64(), ringPair.ring1_id, ringPair.ring2_id,
            ringPair.signal1_fd, ringPair.signal2_fd, fdTransferFds[1], parentPidFD);
        webkitSocketFD = ringPair.signal1_fd;
        executablePath = executablePathOfNetworkProcess();
        break;
    }
#if ENABLE(GPU_PROCESS)
    case ProcessType::GPU: {
        processTypeName = "GPU";
        ringPair = Z_Hajr_CreateRingPair(1024 * 1024);
        ring1Str = g_strdup_printf("%" PRIu64, ringPair.ring1_id);
        ring2Str = g_strdup_printf("%" PRIu64, ringPair.ring2_id);
        g_setenv("ZAWRA_HAJR_RING1", ring1Str, TRUE);
        g_setenv("ZAWRA_HAJR_RING2", ring2Str, TRUE);
        g_setenv("ZAWRA_HAJR_SIGNAL1", g_strdup_printf("%d", ringPair.signal1_fd), TRUE);
        g_setenv("ZAWRA_HAJR_SIGNAL2", g_strdup_printf("%d", ringPair.signal2_fd), TRUE);
        g_setenv("ZAWRA_HAJR_PARENT_PIDFD", g_strdup_printf("%d", parentPidFD), TRUE);
        g_setenv("ZAWRA_HAJR_FDTRANSFER", g_strdup_printf("%d", fdTransferFds[1]), TRUE);
        fprintf(stderr, "[HAJR-CONN] launchProcess: processType=%s processIdentifier=%" PRIu64 " ring1=%" PRIu64 " ring2=%" PRIu64 " sig1=%d sig2=%d fdTransfer=%d parentPidFD=%d\n",
            processTypeName, (uint64_t)m_launchOptions.processIdentifier.toUInt64(), ringPair.ring1_id, ringPair.ring2_id,
            ringPair.signal1_fd, ringPair.signal2_fd, fdTransferFds[1], parentPidFD);
        webkitSocketFD = ringPair.signal1_fd;
        executablePath = executablePathOfGPUProcess();
        break;
    }
#endif
    default:
        ASSERT_NOT_REACHED();
        return;
    }

    g_free(ring1Str);
    g_free(ring2Str);

    GUniquePtr<gchar> processIdentifier(g_strdup_printf("%" PRIu64, m_launchOptions.processIdentifier.toUInt64()));
    GUniquePtr<gchar> webkitSocket(g_strdup_printf("%d", webkitSocketFD));

    CString realExecutablePath = FileSystem::fileSystemRepresentation(executablePath);
    
    char* argv[4];
    argv[0] = const_cast<char*>(realExecutablePath.data());
    argv[1] = processIdentifier.get();
    argv[2] = webkitSocket.get();
    argv[3] = nullptr;

    m_processID = Z_Hajr_SpawnProcess(realExecutablePath.data(), const_cast<const char**>(argv), &webkitSocketFD);

    if (parentPidFD != -1)
        close(parentPidFD);
    if (fdTransferFds[1] != -1)
        close(fdTransferFds[1]); // Child inherits this end via env var + CLOEXEC clear

    int childPidFD = -1;
#if OS(LINUX)
#ifndef PR_SET_PTRACER_ANY
#define PR_SET_PTRACER_ANY ((unsigned long)-1)
#endif
    prctl(PR_SET_PTRACER, PR_SET_PTRACER_ANY, 0, 0, 0);
    childPidFD = syscall(__NR_pidfd_open, m_processID, 0);
#endif

    if (m_processID <= -1)
        g_error("Unable to spawn a new child process via Hajr");

    // UIProcess connection handle is signal2_fd
    int serverSocket = ringPair.signal2_fd;
    int fdTransferSendFd = fdTransferFds[0];

    RunLoop::main().dispatch([protectedThis = Ref { *this }, this, serverSocket, ringPair, childPidFD, fdTransferSendFd, processTypeName] {
        IPC::Connection::Identifier identifier(serverSocket);
        // Populate Hajr ring bootstrap info so the parent's platformOpen()
        // uses the correct ring pair per-connection (not global env vars).
        identifier.hasHajrInfo = true;
        identifier.hajrRing1 = ringPair.ring1_id;
        identifier.hajrRing2 = ringPair.ring2_id;
        identifier.hajrSig1 = ringPair.signal1_fd;
        identifier.hajrSig2 = ringPair.signal2_fd;
        identifier.hajrPidfd = childPidFD;
        identifier.hajrFdTransferFd = fdTransferSendFd;
        fprintf(stderr, "[HAJR-CONN] didFinishLaunching: processType=%s pid=%d ring1=%" PRIu64 " ring2=%" PRIu64 " sig1=%d sig2=%d serverSocket=%d fdTransferSendFd=%d\n",
            processTypeName, (int)m_processID, ringPair.ring1_id, ringPair.ring2_id,
            ringPair.signal1_fd, ringPair.signal2_fd, serverSocket, fdTransferSendFd);
        didFinishLaunchingProcess(m_processID, WTFMove(identifier));
    });
    fprintf(stderr, "[CRASH-V2] launchProcess: dispatch complete, returning\n");
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
