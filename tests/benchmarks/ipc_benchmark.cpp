// ipc_benchmark.cpp — Hajr Ring Buffer vs Unix Domain Socket IPC Benchmark
//
// Measures round-trip latency of two IPC mechanisms:
//   1. Hajr lock-free ring buffer (shared memory, minimal syscalls)
//   2. Unix domain socket send/recv (one syscall per message)
//
// Build: make -C tests/benchmarks
// Run:   ./tests/benchmarks/ipc_benchmark

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
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

// ---------------------------------------------------------------------------
// Hajr FFI — opaque handle + extern "C" functions
// ---------------------------------------------------------------------------

struct HajrRing;  // opaque C_HardenedRingBuffer

extern "C" {
    HajrRing* hajr_ring_init(uint8_t* buffer, size_t buffer_len, size_t size,
                             uint32_t key_value, uint8_t tier_value);
    HajrRing* hajr_ring_map(uint8_t* buffer, size_t buffer_len, size_t size,
                            uint32_t key_value, uint8_t tier_value);
    int32_t hajr_ring_write(HajrRing* ring, const uint8_t* data, size_t length);
    int32_t hajr_ring_read(HajrRing* ring, uint8_t* buf, size_t length, size_t* bytes_read);
    void hajr_ring_free(HajrRing* ring);
}

// ---------------------------------------------------------------------------
// Constants
// ---------------------------------------------------------------------------

static constexpr size_t RING_DATA_SIZE  = 65536;
static constexpr size_t RING_META_SIZE  = 192;
static constexpr size_t RING_TOTAL_SIZE = RING_META_SIZE + RING_DATA_SIZE;
static constexpr size_t PAYLOAD_SIZE    = 1024;
static constexpr int    WARMUP_ITERS    = 1000;
static constexpr int    BENCH_ITERS     = 50000;

// ---------------------------------------------------------------------------
// Timing
// ---------------------------------------------------------------------------

static inline uint64_t now_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL + ts.tv_nsec;
}

// ---------------------------------------------------------------------------
// Stats
// ---------------------------------------------------------------------------

struct Stats {
    double avg; uint64_t median, p99, p999, min_l, max_l;
};

static Stats compute(std::vector<uint64_t>& lat) {
    std::sort(lat.begin(), lat.end());
    uint64_t total = 0;
    for (auto l : lat) total += l;
    size_t n = lat.size();
    return { double(total)/n, lat[n/2], lat[n*99/100], lat[n*999/1000], lat.front(), lat.back() };
}

static void print_stats(const char* label, const Stats& s) {
    printf("  %s\n", label);
    printf("    Average:  %8.0f ns  (%6.2f us)\n", s.avg, s.avg / 1000.0);
    printf("    Median:   %8lu ns  (%6.2f us)\n", s.median, s.median / 1000.0);
    printf("    P99:      %8lu ns  (%6.2f us)\n", s.p99, s.p99 / 1000.0);
    printf("    P99.9:    %8lu ns  (%6.2f us)\n", s.p999, s.p999 / 1000.0);
    printf("    Min:      %8lu ns  (%6.2f us)\n", s.min_l, s.min_l / 1000.0);
    printf("    Max:      %8lu ns  (%6.2f us)\n", s.max_l, s.max_l / 1000.0);
}

// ---------------------------------------------------------------------------
// Phase 1: Socket echo benchmark
// ---------------------------------------------------------------------------
// Each iteration: main sends 1KB, worker echoes, main receives 1KB.
// Uses SOCK_DGRAM (message boundary, no MSG_WAITALL issues).

static void socket_worker(int fd, std::atomic<bool>& ready, std::atomic<bool>& done) {
    ready.store(true, std::memory_order_release);
    uint8_t buf[PAYLOAD_SIZE];
    while (!done.load(std::memory_order_acquire)) {
        ssize_t n = recv(fd, buf, PAYLOAD_SIZE, 0);
        if (n <= 0) continue;
        send(fd, buf, n, 0);
    }
}

static Stats bench_socket(int fd) {
    uint8_t snd[PAYLOAD_SIZE], rcv[PAYLOAD_SIZE];
    memset(snd, 0xAB, PAYLOAD_SIZE);

    for (int i = 0; i < WARMUP_ITERS; i++) {
        send(fd, snd, PAYLOAD_SIZE, 0);
        recv(fd, rcv, PAYLOAD_SIZE, 0);
    }

    std::vector<uint64_t> lat(BENCH_ITERS);
    for (int i = 0; i < BENCH_ITERS; i++) {
        uint64_t t0 = now_ns();
        send(fd, snd, PAYLOAD_SIZE, 0);
        recv(fd, rcv, PAYLOAD_SIZE, 0);
        lat[i] = now_ns() - t0;
    }
    return compute(lat);
}

// ---------------------------------------------------------------------------
// Phase 2: Hajr ring echo benchmark
// ---------------------------------------------------------------------------
// Main writes to ring, sends 1-byte kick. Worker reads ring, writes response ring, sends 1-byte ack.

static void hajr_worker(int fd, HajrRing* rd, HajrRing* wr,
                         std::atomic<bool>& ready, std::atomic<bool>& done) {
    ready.store(true, std::memory_order_release);
    uint8_t buf[PAYLOAD_SIZE], kick;
    size_t br;
    while (!done.load(std::memory_order_acquire)) {
        ssize_t n = recv(fd, &kick, 1, 0);
        if (n <= 0) continue;
        if (hajr_ring_read(rd, buf, PAYLOAD_SIZE, &br) != 1 || br == 0) continue;
        hajr_ring_write(wr, buf, br);
        uint8_t ack = 1;
        send(fd, &ack, 1, 0);
    }
}

static Stats bench_hajr(int fd, HajrRing* wr, HajrRing* rr) {
    uint8_t snd[PAYLOAD_SIZE], rcv[PAYLOAD_SIZE];
    uint8_t kick = 1, ack;
    size_t br;
    memset(snd, 0xAB, PAYLOAD_SIZE);

    for (int i = 0; i < WARMUP_ITERS; i++) {
        hajr_ring_write(wr, snd, PAYLOAD_SIZE);
        send(fd, &kick, 1, 0);
        recv(fd, &ack, 1, 0);
        hajr_ring_read(rr, rcv, PAYLOAD_SIZE, &br);
    }

    std::vector<uint64_t> lat(BENCH_ITERS);
    for (int i = 0; i < BENCH_ITERS; i++) {
        uint64_t t0 = now_ns();
        hajr_ring_write(wr, snd, PAYLOAD_SIZE);
        send(fd, &kick, 1, 0);
        recv(fd, &ack, 1, 0);
        hajr_ring_read(rr, rcv, PAYLOAD_SIZE, &br);
        lat[i] = now_ns() - t0;
    }
    return compute(lat);
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main() {
    printf("IPC Benchmark: Hajr Ring Buffer vs Unix Domain Socket\n");
    printf("======================================================\n");
    printf("Payload: %zu bytes | Iterations: %d (+ %d warm-up)\n\n",
           PAYLOAD_SIZE, BENCH_ITERS, WARMUP_ITERS);

    // Timer overhead
    uint64_t tov = 0;
    for (int i = 0; i < 10000; i++) { uint64_t a = now_ns(), b = now_ns(); tov += b - a; }
    printf("Timer overhead: %.1f ns\n\n", double(tov) / 10000);

    // --- Phase 1: Socket (SOCK_DGRAM for clean message boundaries) ---
    printf("[Phase 1] Socket baseline...\n"); fflush(stdout);
    int sv[2];
    if (socketpair(AF_LOCAL, SOCK_DGRAM, 0, sv) < 0) { perror("socketpair"); return 1; }

    std::atomic<bool> s_ready{false}, s_done{false};
    std::thread sworker(socket_worker, sv[1], std::ref(s_ready), std::ref(s_done));
    while (!s_ready.load(std::memory_order_acquire)) std::this_thread::yield();

    Stats s_stat = bench_socket(sv[0]);

    s_done.store(true, std::memory_order_release);
    uint8_t w = 0; send(sv[0], &w, 1, 0);
    sworker.join();
    close(sv[0]); close(sv[1]);

    // --- Phase 2: Hajr ring ---
    printf("[Phase 2] Hajr ring buffer...\n"); fflush(stdout);

    int out_fd = syscall(SYS_memfd_create, "hajr-out", MFD_CLOEXEC);
    int in_fd  = syscall(SYS_memfd_create, "hajr-in",  MFD_CLOEXEC);
    ftruncate(out_fd, RING_TOTAL_SIZE);
    ftruncate(in_fd,  RING_TOTAL_SIZE);

    auto* out_mem = static_cast<uint8_t*>(
        mmap(nullptr, RING_TOTAL_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, out_fd, 0));
    auto* in_mem = static_cast<uint8_t*>(
        mmap(nullptr, RING_TOTAL_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, in_fd, 0));

    HajrRing* s_wr = hajr_ring_init(out_mem, RING_TOTAL_SIZE, RING_DATA_SIZE, 0, 0);
    HajrRing* s_rr = hajr_ring_init(in_mem,  RING_TOTAL_SIZE, RING_DATA_SIZE, 0, 0);
    HajrRing* c_rr = hajr_ring_map(out_mem, RING_TOTAL_SIZE, RING_DATA_SIZE, 0, 0);
    HajrRing* c_wr = hajr_ring_map(in_mem,  RING_TOTAL_SIZE, RING_DATA_SIZE, 0, 0);

    if (!s_wr || !s_rr || !c_rr || !c_wr) {
        fprintf(stderr, "hajr_ring_init/map failed\n"); return 1;
    }

    int hsv[2];
    if (socketpair(AF_LOCAL, SOCK_DGRAM, 0, hsv) < 0) { perror("socketpair hajr"); return 1; }

    std::atomic<bool> h_ready{false}, h_done{false};
    std::thread hworker(hajr_worker, hsv[1], c_rr, c_wr, std::ref(h_ready), std::ref(h_done));
    while (!h_ready.load(std::memory_order_acquire)) std::this_thread::yield();

    Stats h_stat = bench_hajr(hsv[0], s_wr, s_rr);

    h_done.store(true, std::memory_order_release);
    uint8_t w2 = 0; send(hsv[0], &w2, 1, 0);
    hworker.join();

    hajr_ring_free(s_wr); hajr_ring_free(s_rr);
    hajr_ring_free(c_rr); hajr_ring_free(c_wr);
    munmap(out_mem, RING_TOTAL_SIZE); munmap(in_mem, RING_TOTAL_SIZE);
    close(out_fd); close(in_fd);
    close(hsv[0]); close(hsv[1]);

    // --- Results ---
    printf("\n");
    print_stats("Unix Domain Socket (SOCK_DGRAM send/recv)", s_stat);
    printf("\n");
    print_stats("Hajr Ring Buffer (lock-free + 2 syscalls for kick)", h_stat);
    printf("\n");

    double speedup = s_stat.avg / h_stat.avg;
    printf("Speedup: %.1fx\n", speedup);
    if (speedup > 1.0)
        printf("  Hajr saves ~%.0f ns per round-trip\n", s_stat.avg - h_stat.avg);
    else
        printf("  Socket is %.1fx faster (check alignment/optimization)\n", 1.0/speedup);

    return 0;
}
