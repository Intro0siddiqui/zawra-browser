# Makefile for Zawra IPC Benchmarks
#
# Usage:
#   make              # build single-message benchmark
#   make batch        # build batched-message benchmark
#   make all          # build both
#   make run          # run single-message benchmark
#   make run-batch    # run batched-message benchmark
#   make clean        # remove build artifacts

CXX      ?= g++
CXXFLAGS  = -std=c++17 -O2 -Wall -Wextra -march=native
LDFLAGS   = -lpthread

# Hajr library path (from zig build)
HAJR_DIR  = ../../subsystems/hajr
HAJR_LIB  = $(HAJR_DIR)/zig-out/lib

# Link against the Hajr FFI shared library
LIBS      = -L$(HAJR_LIB) -lhajr_ffi -Wl,-rpath,$(abspath $(HAJR_LIB))

TARGETS   = ipc_benchmark ipc_batch_benchmark

.PHONY: all run run-batch clean

all: $(TARGETS)

ipc_benchmark: ipc_benchmark.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS) $(LDFLAGS)

ipc_batch_benchmark: ipc_batch_benchmark.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS) $(LDFLAGS)

run: ipc_benchmark
	LD_LIBRARY_PATH=$(HAJR_LIB) ./ipc_benchmark

run-batch: ipc_batch_benchmark
	LD_LIBRARY_PATH=$(HAJR_LIB) ./ipc_batch_benchmark

clean:
	rm -f $(TARGETS)
