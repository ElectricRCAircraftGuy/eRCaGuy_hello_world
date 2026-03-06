# This is a simple wrapper Makefile instead of a normal Makefile.
# - Inspired by: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/blob/main/Makefile

BUILD_DIR := build
BUILD_FLAGS := -Wall -Wextra -Werror -O3 -std=gnu++20

# NB: if you don't have this line, then the first target runs by default when you just run "make"
# with no args.
.DEFAULT_GOAL := all

# Mark all targets as PHONY (not real files)
.PHONY: \
	all \
	build_prep \
	clean \
	print_vars

build_prep:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf "$(BUILD_DIR)"

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

.PHONY: $(TARGET) $(TARGET_LINUX) $(TARGET_WINDOWS)

all: $(TARGET)  # append this dependency to target `all`

print_vars:
	@echo "== print_vars =="
	@echo "FILE:             ${FILE}"
	@echo "TARGET:           ${TARGET}"
	@echo "TARGET_LINUX:     ${TARGET_LINUX}"
	@echo "TARGET_WINDOWS:   ${TARGET_WINDOWS}"
	@echo "LINUX_BIN:        ${LINUX_BIN}"
	@echo "WINDOWS_BIN:      ${WINDOWS_BIN}"

$(TARGET): $(TARGET_LINUX) $(TARGET_WINDOWS)

$(TARGET_LINUX): build_prep
	@echo "== Building $(TARGET_LINUX) =="
	# Build
	time g++ $(BUILD_FLAGS) "$(FILE)" -o "$(LINUX_BIN)"

	# Run
	# @echo "Running the Linux binary..."
	# "$(LINUX_BIN)"

$(TARGET_WINDOWS): build_prep
	@echo "== Building $(TARGET_WINDOWS) =="
	# Build
	time x86_64-w64-mingw32-g++ $(BUILD_FLAGS) "$(FILE)" -o "$(WINDOWS_BIN)" -lwinmm

	# @echo "Not running the Windows binary in Linux."

