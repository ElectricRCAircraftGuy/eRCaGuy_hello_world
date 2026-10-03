# Makefile wrapper

# Specify the default target to run when you just run `make`
.DEFAULT_GOAL := help

help:
	@{ \
	echo "Makefile Help"; \
	echo "Usage: make <target>"; \
	echo ""; \
	echo "Targets:"; \
	echo "  help             - Show this help message"; \
	echo "  check [files...] - Run code checks (linting, formatting, etc.). If no files are specified, all files will be checked."; \
	echo "  fix [files...]   - Automatically fix code issues (linting, formatting, etc.). If no files are specified, all files will be fixed."; \
	echo "  test             - Run unit tests"; \
	echo "  clean            - Remove generated build and test artifacts"; \
	echo ""; \
	echo "Examples:"; \
	echo "  make check"; \
	echo "  make check some_path/some_file.py"; \
	echo "  make fix some_path/some_file.py"; \
	} | less -RFX

# ------------- ANSI color codes START -------------
# ANSI color/format codes for colored terminal output from make recipes.
ANSI_START := \e[
ANSI_END := m
ANSI_OFF := $(ANSI_START)$(ANSI_END)

ANSI_BOLD := ;1
ANSI_SLOW_BLINK := ;5
ANSI_FAST_BLINK := ;6
ANSI_FG_BLK := ;30
ANSI_BG_BLK := ;40
ANSI_FG_RED := ;31
ANSI_FG_BR_RED := ;91
ANSI_BG_RED := ;41
ANSI_FG_GRE := ;32
ANSI_BG_GRE := ;42
ANSI_FG_BLU := ;34
ANSI_FG_BR_BLU := ;94
ANSI_BG_BLU := ;44
ANSI_BG_BR_BLU := ;104
ANSI_FG_BR_YLW := ;93
ANSI_BG_BR_YLW := ;103

ANSI_BLUE := $(ANSI_START)$(ANSI_FG_BR_BLU)$(ANSI_END)
ANSI_GREEN := $(ANSI_START)$(ANSI_FG_GRE)$(ANSI_END)
ANSI_YELLOW := $(ANSI_START)$(ANSI_FG_BR_YLW)$(ANSI_END)
ANSI_RED := $(ANSI_START)$(ANSI_FG_BR_RED)$(ANSI_END)
# ------------- ANSI color codes END -------------

CHECK_OR_FIX_PATHS := $(filter-out check fix,$(MAKECMDGOALS))

# Is `check` or `fix` one of the make cmd goals?
ifneq ($(filter check fix,$(MAKECMDGOALS)),)
# Yes, so define a dummy target for each path in `CHECK_OR_FIX_PATHS` to avoid make errors.
$(foreach path,$(CHECK_OR_FIX_PATHS),$(eval $(path):;@:))
endif

# Mark targets as PHONY (not real files)
.PHONY: \
	help \
	check \
	fix \
	test \
	clean

# Check code formatting for the list of files specified in CHECK_OR_FIX_PATHS. If no files are
# specified, check all files.
check:
	@echo "Running code checks..."
	black --check --config pyproject.toml $(if $(CHECK_OR_FIX_PATHS),$(CHECK_OR_FIX_PATHS),.)

# 	@isort --check-only some_path
# 	@flake8 some_path
# 	@pylint some_path

# Fix formatting on the specified files. If no files are specified, fix all files.
fix:
	@echo "Fixing code issues..."
	black --config pyproject.toml $(if $(CHECK_OR_FIX_PATHS),$(CHECK_OR_FIX_PATHS),.)

# Run unit tests
test:
	@echo "Running unit tests..."
	python3 -m pytest

# Remove generated, gitignored build and test artifacts. `find` does not follow symlinks by
# default, so it safely avoids the math <-> python directory-link loop.
# - Keep `.venv/` dirs intact because they hold user-managed virtual environments and are
#   expensive to rebuild.
clean:
	@echo "Removing generated build and test artifacts..."
	@find . -type d -name __pycache__ -prune -exec rm -rf {} +
	@find . -type f \( -name '*.pyc' -o -name '*.pyo' \) -delete
	@rm -rf .pytest_cache bin build temp
