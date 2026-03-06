# This is a simple wrapper Makefile instead of a normal Makefile.
# - Inspired by: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/blob/main/Makefile

BUILD_DIR := build
BUILD_FLAGS := -Wall -Wextra -Werror -O3 -std=gnu++20
TIMING_TEST_FILE := timing__timing_and_precision_Windows_and_Linux_tests.cpp
LINUX_BIN := $(BUILD_DIR)/timing__timing_and_precision_Windows_and_Linux_tests
WINDOWS_BIN := $(BUILD_DIR)/timing__timing_and_precision_Windows_and_Linux_tests.exe

# Mark all targets as PHONY (not real files)
.PHONY:
	all \
	build_prep \
	clean \
	timing__timing_and_precision_Windows_and_Linux_tests.cpp \
	timing__timing_and_precision_Windows_and_Linux_tests.cpp-linux \
	timing__timing_and_precision_Windows_and_Linux_tests.cpp-windows

# NB: this is the first target, so it runs by default when you just run "make" with no args.
all: \
	timing__timing_and_precision_Windows_and_Linux_tests.cpp

build_prep:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf "$(BUILD_DIR)"

timing__timing_and_precision_Windows_and_Linux_tests.cpp: \
	timing__timing_and_precision_Windows_and_Linux_tests.cpp-linux \
	timing__timing_and_precision_Windows_and_Linux_tests.cpp-windows

timing__timing_and_precision_Windows_and_Linux_tests.cpp-linux: build_prep
	# Build
	time g++ $(BUILD_FLAGS) "$(TIMING_TEST_FILE)" -o "$(LINUX_BIN)"

	# Run
	@echo "Running the Linux binary..."
	"$(LINUX_BIN)"

timing__timing_and_precision_Windows_and_Linux_tests.cpp-windows: build_prep
	# Build
	time x86_64-w64-mingw32-g++ $(BUILD_FLAGS) "$(TIMING_TEST_FILE)" -o "$(WINDOWS_BIN)" -lwinmm

	@echo "Not running the Windows binary in Linux."
