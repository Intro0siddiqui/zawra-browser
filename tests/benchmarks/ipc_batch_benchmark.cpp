// ipc_batch_benchmark.cpp — Batched IPC: Hajr Ring vs Unix Socket
//
// Measures how each IPC mechanism scales with batch size.
// Socket: N messages = N send/recv pairs = 2N syscalls
// Ring:   N messages = 1 write loop + 1 kick + 1 drain = 2 syscalls total
//
// Build: make batch
// Run:   ./ipc_batch_benchmark

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <vector>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <linux/memfd.h>
#include <fcntl.h>
#include <stdint.h>

// ---------------------------------------------------------------------------
// Hajr FFI (opaque)
// ---------------------------------------------------------------------------

struct HajrRing;
extern "C" {
    HajrRing* hajr_ring_init(uint8_t* buf, size_t buf_len, size_t size,
                             uint32_t key, uint8_t tier);
    HajrRing* hajr_ring_map(uint8_t* buf, size_t buf_len, size_t size,
                            uint32_t key, uint8_t tier);
    int32_t hajr_ring_write(HajrRing* ring, const uint8_t* data, size_t len);
    int32_t hajr_ring_read(HajrRing* ring, uint8_t* buf, size_t len, size_t* br);
    void hajr_ring_free(HajrRing* ring);
}

// ---------------------------------------------------------------------------
// Constants
// ---------------------------------------------------------------------------

static constexpr size_t RING_DATA   = 65536;
static constexpr size_t RING_META   = 192;
static constexpr size_t RING_TOTAL  = RING_META + RING_DATA;
static constexpr size_t MSG_SIZE    = 256;       // small IPC message
static constexpr int    WARMUP      = 500;
static constexpr int    ITERS       = 5000;

// Batch sizes to test
static constexpr int BATCH_SIZES[] = { 1, 4, 16, 64, 256 };
static constexpr int NUM_BATCHES   = sizeof(BATCH_SIZES) / sizeof(BATCH_SIZES[0]);

// ---------------------------------------------------------------------------
// Timing
// ---------------------------------------------------------------------------

static inline uint64_t ns() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (uint64_t)t.tv_sec * 1000000000ULL + t.tv_nsec;
}

// ---------------------------------------------------------------------------
// Socket worker — receives BATCH_SIZE messages, echoes each back
// ---------------------------------------------------------------------------

struct SockWorker {
    int fd;
    std::atomic<bool> ready{false};
    std::atomic<bool> done{false};
};

static void sock_worker_fn(SockWorker* w) {
    w->ready.store(true, std::memory_order_release);
    uint8_t buf[MSG_SIZE];
    while (!w->done.load(std::memory_order_acquire)) {
        ssize_t n = recv(w->fd, buf, MSG_SIZE, 0);
        if (n <= 0) continue;
        send(w->fd, buf, n, 0);
    }
}

// ---------------------------------------------------------------------------
// Hajr worker — receives kick, drains ring, writes responses, sends ack
// ---------------------------------------------------------------------------

struct HajrWorker {
    int       kick_fd;
    HajrRing* rd_ring;
    HajrRing* wr_ring;
    int       batch_size;
    std::atomic<bool> ready{false};
    std::atomic<bool> done{false};
};

static void hajr_worker_fn(HajrWorker* w) {
    w->ready.store(true, std::memory_order_release);
    uint8_t buf[MSG_SIZE], kick;
    size_t br;

    while (!w->done.load(std::memory_order_acquire)) {
        // Wait for kick
        if (recv(w->kick_fd, &kick, 1, 0) <= 0) continue;

        // Drain all available messages from ring
        int drained = 0;
        while (drained < w->batch_size) {
            int32_t res = hajr_ring_read(w->rd_ring, buf, MSG_SIZE, &br);
            if (res != 1 || br == 0) break;
            // Echo back
            hajr_ring_write(w->wr_ring, buf, br);
            drained++;
        }

        // Send ack
        uint8_t ack = 1;
        send(w->kick_fd, &ack, 1, 0);
    }
}

// ---------------------------------------------------------------------------
// Benchmark: Socket (N messages, each with send/recv)
// ---------------------------------------------------------------------------

static double bench_socket_batch(int fd, int batch) {
    uint8_t snd[MSG_SIZE], rcv[MSG_SIZE];
    memset(snd, 0xAB, MSG_SIZE);

    // Warm up
    for (int w = 0; w < WARMUP; w++) {
        for (int i = 0; i < batch; i++) {
            send(fd, snd, MSG_SIZE, 0);
            recv(fd, rcv, MSG_SIZE, 0);
        }
    }

    // Benchmark
    uint64_t total = 0;
    for (int iter = 0; iter < ITERS; iter++) {
        uint64_t t0 = ns();
        for (int i = 0; i < batch; i++) {
            send(fd, snd, MSG_SIZE, 0);
            recv(fd, rcv, MSG_SIZE, 0);
        }
        total += ns() - t0;
    }
    return double(total) / ITERS;  // avg ns per batch
}

// ---------------------------------------------------------------------------
// Benchmark: Hajr ring (N messages in ring, 1 kick, 1 drain)
// ---------------------------------------------------------------------------

static double bench_hajr_batch(int fd, HajrRing* wr, HajrRing* rr, int batch) {
    uint8_t snd[MSG_SIZE], rcv[MSG_SIZE];
    uint8_t kick = 1, ack;
    size_t br;
    memset(snd, 0xAB, MSG_SIZE);

    // Warm up
    for (int w = 0; w < WARMUP; w++) {
        for (int i = 0; i < batch; i++)
            hajr_ring_write(wr, snd, MSG_SIZE);
        send(fd, &kick, 1, 0);
        recv(fd, &ack, 1, 0);
        for (int i = 0; i < batch; i++)
            hajr_ring_read(rr, rcv, MSG_SIZE, &br);
    }

    // Benchmark
    uint64_t total = 0;
    for (int iter = 0; iter < ITERS; iter++) {
        uint64_t t0 = ns();

        // Producer: write batch to ring, send 1 kick
        for (int i = 0; i < batch; i++)
            hajr_ring_write(wr, snd, MSG_SIZE);
        send(fd, &kick, 1, 0);

        // Wait for ack (worker drained ring and wrote responses)
        recv(fd, &ack, 1, 0);

        // Consumer: read batch from ring
        for (int i = 0; i < batch; i++)
            hajr_ring_read(rr, rcv, MSG_SIZE, &br);

        total += ns() - t0;
    }
    return double(total) / ITERS;  // avg ns per batch
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main() {
    printf("Batched IPC Benchmark: Hajr Ring vs Unix Socket\n");
    printf("================================================\n");
    printf("Message size: %zu bytes | Iterations: %d (+ %d warm-up)\n\n",
           MSG_SIZE, ITERS, WARMUP);

    // Timer overhead
    uint64_t tov = 0;
    for (int i = 0; i < 10000; i++) { uint64_t a = ns(), b = ns(); tov += b - a; }
    printf("Timer overhead: %.1f ns\n\n", double(tov) / 10000);

    // Setup Hajr rings
    int out_fd = syscall(SYS_memfd_create, "hajr-out", MFD_CLOEXEC);
    int in_fd  = syscall(SYS_memfd_create, "hajr-in",  MFD_CLOEXEC);
    ftruncate(out_fd, RING_TOTAL);
    ftruncate(in_fd,  RING_TOTAL);

    auto* out_mem = (uint8_t*)mmap(nullptr, RING_TOTAL, PROT_READ|PROT_WRITE, MAP_SHARED, out_fd, 0);
    auto* in_mem  = (uint8_t*)mmap(nullptr, RING_TOTAL, PROT_READ|PROT_WRITE, MAP_SHARED, in_fd, 0);

    HajrRing* s_wr = hajr_ring_init(out_mem, RING_TOTAL, RING_DATA, 0, 0);
    HajrRing* s_rr = hajr_ring_init(in_mem,  RING_TOTAL, RING_DATA, 0, 0);
    HajrRing* c_rr = hajr_ring_map(out_mem, RING_TOTAL, RING_DATA, 0, 0);
    HajrRing* c_wr = hajr_ring_map(in_mem,  RING_TOTAL, RING_DATA, 0, 0);

    // Table header
    printf("%-8s | %-16s | %-16s | %-8s\n",
           "Batch", "Socket (avg ns)", "Hajr (avg ns)", "Speedup");
    printf("---------|------------------|------------------|----------\n");

    for (int b = 0; b < NUM_BATCHES; b++) {
        int batch = BATCH_SIZES[b];

        // Socket path
        int sv[2];
        socketpair(AF_LOCAL, SOCK_DGRAM, 0, sv);
        SockWorker sw; sw.fd = sv[1];
        std::thread s_thread(sock_worker_fn, &sw);
        while (!sw.ready.load()) std::this_thread::yield();

        double socket_ns = bench_socket_batch(sv[0], batch);

        sw.done.store(true);
        uint8_t w = 0; send(sv[0], &w, 1, 0);
        s_thread.join();
        close(sv[0]); close(sv[1]);

        // Hajr path
        int hsv[2];
        socketpair(AF_LOCAL, SOCK_DGRAM, 0, hsv);
        HajrWorker hw;
        hw.kick_fd = hsv[1];
        hw.rd_ring = c_rr;
        hw.wr_ring = c_wr;
        hw.batch_size = batch;
        std::thread h_thread(hajr_worker_fn, &hw);
        while (!hw.ready.load()) std::this_thread::yield();

        double hajr_ns = bench_hajr_batch(hsv[0], s_wr, s_rr, batch);

        hw.done.store(true);
        uint8_t w2 = 0; send(hsv[0], &w2, 1, 0);
        h_thread.join();
        close(hsv[0]); close(hsv[1]);

        double speedup = socket_ns / hajr_ns;

        printf("%-8d | %12.0f ns | %12.0f ns | %5.1fx\n",
               batch, socket_ns, hajr_ns, speedup);
    }

    printf("\n");
    printf("Key insight: At batch=1 both are ~equal (2 syscalls each).\n");
    printf("At batch=N, ring costs ~2 syscalls for N messages vs socket's 2N.\n");
    printf("Theoretical ring advantage at batch=256: ~128x fewer syscalls.\n");

    // Cleanup
    hajr_ring_free(s_wr); hajr_ring_free(s_rr);
    hajr_ring_free(c_rr); hajr_ring_free(c_wr);
    munmap(out_mem, RING_TOTAL); munmap(in_mem, RING_TOTAL);
    close(out_fd); close(in_fd);

    return 0;
}
