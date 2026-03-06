# This is a simple wrapper Makefile instead of a normal Makefile.
# - Inspired by: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/blob/main/Makefile

BUILD_DIR := build
BUILD_FLAGS := -Wall -Wextra -Werror -O3 -std=gnu++20

TIMING_TARGET := timing__timing_and_precision_Windows_and_Linux_tests
TIMING_TARGET_LINUX := $(TIMING_TARGET)-linux
TIMING_TARGET_WINDOWS := $(TIMING_TARGET)-windows
TIMING_TARGET_BASE := $(basename $(TIMING_TARGET))
LINUX_BIN := $(BUILD_DIR)/$(TIMING_TARGET_BASE)
WINDOWS_BIN := $(BUILD_DIR)/$(TIMING_TARGET_BASE).exe

# Mark all targets as PHONY (not real files)
.PHONY:
	all \
	build_prep \
	clean \
	print_vars \
	$(TIMING_TARGET) \
	$(TIMING_TARGET_LINUX) \
	$(TIMING_TARGET_WINDOWS)

# NB: this is the first target, so it runs by default when you just run "make" with no args.
all: \
	$(TIMING_TARGET)

build_prep:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf "$(BUILD_DIR)"



print_vars:
	@echo "TIMING_TARGET:           ${TIMING_TARGET}"
	@echo "TIMING_TARGET_LINUX:     ${TIMING_TARGET_LINUX}"
	@echo "TIMING_TARGET_WINDOWS:   ${TIMING_TARGET_WINDOWS}"
	@echo "TIMING_TARGET_BASE:      ${TIMING_TARGET_BASE}"
	@echo "LINUX_BIN:               ${LINUX_BIN}"
	@echo "WINDOWS_BIN:             ${WINDOWS_BIN}"

$(TIMING_TARGET): \
	$(TIMING_TARGET_LINUX) \
	$(TIMING_TARGET_WINDOWS)

$(TIMING_TARGET_LINUX): build_prep
	# Build
	time g++ $(BUILD_FLAGS) "$(TIMING_TARGET)" -o "$(LINUX_BIN)"

	# Run
	@echo "Running the Linux binary..."
	"$(LINUX_BIN)"

$(TIMING_TARGET_WINDOWS): build_prep
	# Build
	time x86_64-w64-mingw32-g++ $(BUILD_FLAGS) "$(TIMING_TARGET)" -o "$(WINDOWS_BIN)" -lwinmm

	@echo "Not running the Windows binary in Linux."
