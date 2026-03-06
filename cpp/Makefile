# This is a wrapper Makefile instead of just a normal Makefile.
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

BUILD_DIR := build
BUILD_FLAGS := -Wall -Wextra -Werror -O3 -std=gnu++20
CCACHE_BIN := $(shell command -v ccache 2>/dev/null)
# Use ccache if available, otherwise set to empty string to just call the compiler directly.
CCACHE := $(if $(CCACHE_BIN),ccache,)

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
LINUX_OBJ := $(BUILD_DIR)/$(TARGET).linux.o
WINDOWS_OBJ := $(BUILD_DIR)/$(TARGET).windows.o

.PHONY: $(TARGET) $(TARGET_LINUX) $(TARGET_WINDOWS)

all: $(TARGET)  # append this `$(TARGET)` dependency to target `all`

print_vars:
	@echo "== print_vars =="
	@echo "FILE:             ${FILE}"
	@echo "TARGET:           ${TARGET}"
	@echo "TARGET_LINUX:     ${TARGET_LINUX}"
	@echo "TARGET_WINDOWS:   ${TARGET_WINDOWS}"
	@echo "LINUX_BIN:        ${LINUX_BIN}"
	@echo "WINDOWS_BIN:      ${WINDOWS_BIN}"
	@echo "LINUX_OBJ:        ${LINUX_OBJ}"
	@echo "WINDOWS_OBJ:      ${WINDOWS_OBJ}"
	@echo "CCACHE:           ${CCACHE}"

$(TARGET): $(TARGET_LINUX) $(TARGET_WINDOWS)
	@echo "✅ All targets built successfully: $(TARGET_LINUX) and $(TARGET_WINDOWS)."

$(TARGET_LINUX): $(LINUX_BIN)
	@echo "✅ Linux build completed successfully: $(TARGET_LINUX)."

$(TARGET_WINDOWS): $(WINDOWS_BIN)
	@echo "✅ Windows build completed successfully: $(TARGET_WINDOWS)."

# Note: prerequisites to the left of `|` are normal prerequisites that get rebuilt if their
# timestamps change, and those to the right are order-only prerequisites that must be done first.
$(LINUX_OBJ): $(FILE) | build_prep
	@echo ""
	@echo "= Compiling Linux object ="
	$(CCACHE) g++ $(BUILD_FLAGS) -c "$(FILE)" -o "$(LINUX_OBJ)"

$(WINDOWS_OBJ): $(FILE) | build_prep
	@echo ""
	@echo "= Compiling Windows object ="
	$(CCACHE) x86_64-w64-mingw32-g++ $(BUILD_FLAGS) -c "$(FILE)" -o "$(WINDOWS_OBJ)"

$(LINUX_BIN): $(LINUX_OBJ)
	@echo "= Linking Linux binary ="
	g++ "$(LINUX_OBJ)" -o "$(LINUX_BIN)"

$(WINDOWS_BIN): $(WINDOWS_OBJ)
	@echo "= Linking Windows binary ="
	x86_64-w64-mingw32-g++ "$(WINDOWS_OBJ)" -o "$(WINDOWS_BIN)" -lwinmm

