#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
#
# Written:
# July 2022 - Sep. 2025
#
# Updated:
# 2026: modified to more closely match file "bash/ansi_color_codes.sh".

# A simple library for printing colored text to the terminal using ANSI color codes.
# You can source this file in your bash scripts to use the color printing functions.

# Status: done and works!
# Test me:
# ```bash
# cd path/to/here
# ./ansi_color_codes_simple_lib.sh
# # and
# ./ansi_color_codes_simple_lib_demo.sh
# ```

# See also:
# 1. "eRCaGuy_hello_world/bash/ansi_color_codes.sh":
#    https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/ansi_color_codes.sh
# 1. For Python, see my repo here: https://github.com/ElectricRCAircraftGuy/eRCaGuy_PyColors

# --------------------------------------------------------------------------------------------------

# ANSI color codes.
# See:
# 1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/ansi_color_codes_simple_lib.sh
# 2. https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/ansi_color_codes.sh
# 3. https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit

ANSI_START="\e["
ANSI_END="m"
# the combination of ANSI_START + ANSI_END with no numeric codes in between
ANSI_OFF="${ANSI_START}${ANSI_END}"

ANSI_FG_RED=";31"      # foreground color red
ANSI_FG_BR_RED=";91"   # foreground color bright red
ANSI_FG_GRE=";32"      # foreground color green
ANSI_FG_BLU=";34"      # foreground color blue
ANSI_FG_BR_BLU=";94"   # foreground color bright blue
ANSI_FG_BR_YLW=";93"   # foreground color bright yellow

echo_blue() {
    local text="$*"
    echo -e "${ANSI_START}${ANSI_FG_BR_BLU}${ANSI_END}${text}${ANSI_OFF}"
}

echo_green() {
    local text="$*"
    echo -e "${ANSI_START}${ANSI_FG_GRE}${ANSI_END}${text}${ANSI_OFF}"
}

echo_yellow() {
    local text="$*"
    echo -e "${ANSI_START}${ANSI_FG_BR_YLW}${ANSI_END}${text}${ANSI_OFF}"
}

echo_red() {
    local text="$*"
    echo -e "${ANSI_START}${ANSI_FG_BR_RED}${ANSI_END}${text}${ANSI_OFF}"
}


demo() {
    echo "Running demo."

    echo_green "This is green text"
    echo_yellow "This is yellow text"
    echo_red "This is red text"
    echo_blue "This is blue text"
}

main() {
    echo "Running main."
    demo
}

# Determine if the script is being sourced or executed (run).
# See:
# 1. "eRCaGuy_hello_world/bash/if__name__==__main___check_if_sourced_or_executed_best.sh"
# 1. My answer: https://stackoverflow.com/a/70662116/4561887
if [ "${BASH_SOURCE[0]}" = "$0" ]; then
    # This script is being run.
    __name__="__main__"
else
    # This script is being sourced.
    __name__="__source__"
fi

# Only run `main` if this script is being **run**, NOT sourced (imported).
# - See my answer: https://stackoverflow.com/a/70662116/4561887
if [ "$__name__" = "__main__" ]; then
    main "$@"
fi
