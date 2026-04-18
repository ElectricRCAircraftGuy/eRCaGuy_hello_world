# This is also a wrapper-style Makefile instead of just a normal Makefile.
# - Inspired by: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/blob/main/Makefile
#
#
# Q: How does ccache help here, beyond the normal Makefile's built-in timestamp-based incremental
# build system?
#
# A: Short answer: both help, but at different layers.
#
# * Make gives incremental builds in the current build tree via timestamps: if *.o is newer than
#   source/headers, it skips recompiling.
# * ccache gives compiler result reuse across builds (including after make clean, across
#   directories/branches, and across repeated invocations with same effective compile inputs).
# * In this current one-file setup, Make already avoids most recompiles, so ccache may show little
#   benefit unless you force recompilation.
# * ccache helps most when rebuilds are frequent but logically identical (clean builds, CI, branch
#   switching, many similar files).
# * ccache does not speed linking; it only helps compile commands (-c ...).
#
# So: keep both. Make avoids unnecessary work; ccache accelerates the recompiles that still happen.
#
#
# Dry run:
# ```bash
# make -n
# # OR
# make -n all
# ```
#
# References
# 1. GNU make manual [one webpage]: https://www.gnu.org/software/make/manual/make.html
#

BUILD_DIR := build
BUILD_FLAGS := -Wall -Wextra -Werror -O3 -std=gnu++20
CCACHE_BIN := $(shell command -v ccache 2>/dev/null)
# Use ccache if available, otherwise set to empty string to just call the compiler directly.
CCACHE := $(if $(CCACHE_BIN),ccache,)
INSIDE_DOCKER := $(shell if [ -f /.dockerenv ] || grep -qaE '(docker|containerd|kubepods)' /proc/1/cgroup 2>/dev/null; then echo true; else echo false; fi)
DOCKER_RUN := $(abspath ../docker/docker_run.sh)

# If inside Docker, run the build targets directly, so make the wrapper empty. Otherwise, forward
# all targets into Docker.
ifeq ($(INSIDE_DOCKER),true)
$(info Already inside Docker container, so no need to forward targets into Docker.)
$(info )
DOCKER_RUN_WRAPPER :=
else
$(info Not inside Docker container, so forwarding targets into Docker.)
$(info )
DOCKER_RUN_WRAPPER := $(DOCKER_RUN) --quiet --
endif

# NB: if you don't have this line, then the first target runs by default when you just run "make"
# with no args.
.DEFAULT_GOAL := all

# Mark all targets as PHONY (not real files)
.PHONY: \
	help \
	all \
	clean \
	build_prep \
	print_vars

help:
	@echo "Primary targets:"
	@echo "  help:          Show this help message"
	@echo "  all:           Build all targets (default)"
	@echo "  clean:         Remove build artifacts from dir \"$(BUILD_DIR)\""
	@echo "  print_vars:    Print variable values for debugging"
	@echo "  build_prep:    Prepare build directory"
	@echo ""
	@echo "Project-specific targets:"
	@echo "  timing__timing_and_precision_Windows_and_Linux_tests.cpp:"
	@echo "    timing__timing_and_precision_Windows_and_Linux_tests:          Build both Linux and Windows binaries"
	@echo "    timing__timing_and_precision_Windows_and_Linux_tests-linux:    Build Linux binary only"
	@echo "    timing__timing_and_precision_Windows_and_Linux_tests-windows:  Build Windows binary only"
	@echo "    timing__timing_and_precision_Windows_and_Linux_tests-run:      Run the built binary based on the current OS"

clean:
	rm -rf "$(BUILD_DIR)"

build_prep:
	mkdir -p $(BUILD_DIR)

# NB: use double colon `::` to allow multiple rules with the same name, so we can have a separate
# `print_vars` rule for each section of the Makefile. Running `make print_vars` will then run all of
# them sequentially.
print_vars::
	@echo "== print_vars =="
	@echo ""
	@echo "BUILD_DIR:           ${BUILD_DIR}"
	@echo "BUILD_FLAGS:         ${BUILD_FLAGS}"
	@echo "CCACHE_BIN:          ${CCACHE_BIN}"
	@echo "CCACHE:              ${CCACHE}"
	@echo "INSIDE_DOCKER:       ${INSIDE_DOCKER}"
	@echo "DOCKER_RUN:          ${DOCKER_RUN}"
	@echo "DOCKER_RUN_WRAPPER:  ${DOCKER_RUN_WRAPPER}"
	@echo ""

# ========================================================================
# timing__timing_and_precision_Windows_and_Linux_tests.cpp
# ========================================================================

FILE := timing__timing_and_precision_Windows_and_Linux_tests.cpp
# Use `basename` to strip the .cpp extension.
# - See:
#   https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html#index-basename-1
TARGET := $(basename $(FILE))
TARGET_LINUX := $(TARGET)-linux
TARGET_WINDOWS := $(TARGET)-windows
LINUX_BIN := $(BUILD_DIR)/$(TARGET)
WINDOWS_BIN := $(BUILD_DIR)/$(TARGET).exe
LINUX_OBJ := $(BUILD_DIR)/$(TARGET).linux.o
WINDOWS_OBJ := $(BUILD_DIR)/$(TARGET).windows.o

all: $(TARGET)  # append this `$(TARGET)` dependency to target `all`

# For debugging the Makefile
print_vars::
	@echo "FILE:                ${FILE}"
	@echo "TARGET:              ${TARGET}"
	@echo "TARGET_LINUX:        ${TARGET_LINUX}"
	@echo "TARGET_WINDOWS:      ${TARGET_WINDOWS}"
	@echo "LINUX_BIN:           ${LINUX_BIN}"
	@echo "WINDOWS_BIN:         ${WINDOWS_BIN}"
	@echo "LINUX_OBJ:           ${LINUX_OBJ}"
	@echo "WINDOWS_OBJ:         ${WINDOWS_OBJ}"
	@echo ""

# File targets:
# "If any prerequisite is newer than the target (or the target doesn't exist yet), the target is
#  out of date → rebuild it."

# Note: prerequisites to the right of `:` and left of `|` are normal prerequisites that get rebuilt
# if their timestamps change, and those to the right are order-only prerequisites that must be done
# first.
$(LINUX_OBJ): $(FILE) | build_prep
	@echo ""
	@echo "= Compiling Linux object ="
	# Compile only (-c), no linking; ccache wraps the compiler for cache hits
	$(DOCKER_RUN_WRAPPER) $(CCACHE) g++ $(BUILD_FLAGS) -c "$(FILE)" -o "$(LINUX_OBJ)"

$(WINDOWS_OBJ): $(FILE) | build_prep
	@echo ""
	@echo "= Compiling Windows object ="
	# Compile only (-c), no linking; ccache wraps the compiler for cache hits
	$(DOCKER_RUN_WRAPPER) $(CCACHE) x86_64-w64-mingw32-g++ $(BUILD_FLAGS) -c "$(FILE)" -o "$(WINDOWS_OBJ)"

# Note: ccache is not helpful for linking; just compiling, so it's not used here.
$(LINUX_BIN): $(LINUX_OBJ)
	@echo "= Linking Linux binary ="
	$(DOCKER_RUN_WRAPPER) g++ "$(LINUX_OBJ)" -o "$(LINUX_BIN)"

# Note: ccache is not helpful for linking; just compiling, so it's not used here.
$(WINDOWS_BIN): $(WINDOWS_OBJ)
	@echo "= Linking Windows binary ="
	$(DOCKER_RUN_WRAPPER) x86_64-w64-mingw32-g++ "$(WINDOWS_OBJ)" -o "$(WINDOWS_BIN)" -lwinmm

# Phony targets
.PHONY: $(TARGET_LINUX) $(TARGET_WINDOWS) $(TARGET) $(TARGET)-run

$(TARGET_LINUX): $(LINUX_BIN)
	@echo "✅ Linux build completed successfully: $(TARGET_LINUX)."

$(TARGET_WINDOWS): $(WINDOWS_BIN)
	@echo "✅ Windows build completed successfully: $(TARGET_WINDOWS)."

$(TARGET): $(TARGET_LINUX) $(TARGET_WINDOWS)
	@echo "✅ All targets built successfully: $(TARGET_LINUX) and $(TARGET_WINDOWS)."

$(TARGET)-run:
	@echo "Running the built binary for the current OS..."
# See: https://stackoverflow.com/a/12099167/4561887
ifeq ($(OS),Windows_NT)
	@echo "Detected Windows OS. Running Windows binary..."
	$(DOCKER_RUN_WRAPPER) "$(WINDOWS_BIN)"
else
	@echo "Detected non-Windows OS. Running Linux binary..."
	$(DOCKER_RUN_WRAPPER) "$(LINUX_BIN)"
endif
