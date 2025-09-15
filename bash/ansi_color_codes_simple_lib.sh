#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# July 2022 - Sep. 2025

# A simple library for printing colored text to the terminal using ANSI color codes.
# You can source this file in your bash scripts to use the color printing functions.

# Status: done and works!

# See also: 
# 1. "eRCaGuy_hello_world/bash/ansi_color_codes.sh": 
#    https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/ansi_color_codes.sh

COLOR_GRN="\e[;32m"  # ANSI color green
COLOR_RED="\e[;91m"  # ANSI color bright red
COLOR_YLW="\e[;93m"  # ANSI color bright yellow
COLOR_BLU="\e[;94m"  # ANSI color bright blue
COLOR_OFF="\e[m"     # ANSI color reset

echo_blue() {
    local text="$*"
    echo -e "${COLOR_BLU}${text}${COLOR_OFF}"
}

echo_green() {
    local text="$*"
    echo -e "${COLOR_GRN}${text}${COLOR_OFF}"
}

echo_yellow() {
    local text="$*"
    echo -e "${COLOR_YLW}${text}${COLOR_OFF}"
}

echo_red() {
    local text="$*"
    echo -e "${COLOR_RED}${text}${COLOR_OFF}"
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
