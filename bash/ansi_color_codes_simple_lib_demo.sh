#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Sep. 2025

# Demonstrate sourcing and using the `ansi_color_codes_simple_lib.sh` library. 

# Status: done and works!

# Ensure we are in the correct directory to start so that all relative paths work.
# See: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"
cd "$SCRIPT_DIRECTORY"

# Source the library.
. ./ansi_color_codes_simple_lib.sh

# Now use it
echo_green  "${SCRIPT_FILENAME}: This is green text"
echo_yellow "${SCRIPT_FILENAME}: This is yellow text"
echo_red    "${SCRIPT_FILENAME}: This is red text"
echo_blue   "${SCRIPT_FILENAME}: This is blue text"

