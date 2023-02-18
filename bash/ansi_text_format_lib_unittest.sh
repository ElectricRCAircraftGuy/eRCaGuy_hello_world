#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Feb. 18 2023
# https://gabrielstaples.com/
# https://www.electricrcaircraftguy.com/

# Source (import) the corresponding bash library, and call some functions it
# contains.
#
# Status: done and works

# Check this script with:
#
##      shellcheck -x bash/ansi_text_format_lib_unittest.sh
#
# Run command:
#
#       bash/ansi_text_format_lib_unittest.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/ansi_text_format_lib_unittest.sh

# References:
# 1.

# See my answer: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[-1]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
# shellcheck disable=SC2034
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"

# Source (import) the bash library to test
# See also my answer here: https://stackoverflow.com/a/75341911/4561887
# shellcheck source=bash/sound_bell_lib.sh
. "$SCRIPT_DIRECTORY/ansi_text_format_lib.sh"


# Now test some of its functions

# Set your format string
set_f ANSI_BOLD ANSI_UNDERLINE ANSI_SLOW_BLINK ANSI_FG_BR_BLU
# view the current format string
echo "$f"
# Now print something in that format
ansi_echo "This library works very well! I am very pleased with its usage and format! :)"
f_echo "This library works very well! I am very pleased with its usage and format! :)"


# SAMPLE OUTPUT (run it yourself to see the blinking formatted output):
#
#       eRCaGuy_hello_world/bash$ ./ansi_text_format_lib_unittest.sh
#       \e[;1;4;5;94m
#       This library works very well! I am very pleased with its usage and format! :)
#       This library works very well! I am very pleased with its usage and format! :)


