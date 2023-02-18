#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Feb. 18 2023
# https://gabrielstaples.com/
# https://www.electricrcaircraftguy.com/

# A general purpose ANSI text formatting library in Bash. Easily make your terminal text bold, red,
# blue, blinking, inverted colors (highlighted), etc.
# - See all the possible codes on Wikipedia, starting here:
#   https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
#
# Status: done and works!
# I need to add more ANSI codes, but this is a very-well-done and functional library now! I am
# very pleased with it.

# keywords: text formatting in your terminal in Bash (or any language for that matter, C, C++,
# Python, Go, etc.)

# Check this script with:
#
##      shellcheck bash/ansi_text_format_lib.sh
#
# Run command:
#
#       bash/ansi_text_format_lib.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/ansi_text_format_lib.sh

# References:
# 1. ANSI color codes, formatting, or highlighting
#   1. ***** https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/ansi_color_codes.sh
#   2. *****+ "ANSI escape code" on Wikipedia:
#     1. https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit
#     2. https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
#   1. *****+ https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/home/.bash_aliases
#      - The area at and above my `gs_git_show_branch_and_hash` func
# 1.

# Notes:
# 1. NB: WHEN USING `echo`, DON'T FORGET THE `-e` to escape the color codes! Ex:   <======== REQUIRED TO GET THE FORMATTING WHEN USING `echo` ===========
#       echo -e "some string with color codes in it"

# TODO (newest on bottom):
# 1. [ ] Take a whole day sometime and go through the Wikipedia article carefully
# (https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters),
# adding **all** formatting codes and possibilities to the list below.


ANSI_START="\e["    # start of an ANSI formatting sequence
#
# --------- ANSI numeric codes start ----------
#         - these codes go **between** `ANSI_START` and `ANSI_END`
#
ANSI_BOLD=";1"
ANSI_FAINT=";2"
ANSI_ITALIC=";3"
ANSI_UNDERLINE=";4"
ANSI_SLOW_BLINK=";5"
ANSI_FAST_BLINK=";6"    # (not widely supported--does NOT work in a Linux Ubuntu bash shell)
ANSI_INVERTED=";7"      # inverted colors (ie: the text looks **highlighted**); see code 7 here:
                        # https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
                        # This swaps foreground and background colors; "inconsistent emulation".
ANSI_HIGHLIGHTED="$ANSI_INVERTED" # alias
ANSI_CROSSED_OUT=";9"
ANSI_NORMAL_INTENSITY=";22" # neither bold nor faint
# Foreground (FG) colors: 30-97  (not continuous); TODO: ADD THE REST OF THE CODES!
# - See: https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit
ANSI_FG_BLK=";30"       # foreground color black
ANSI_FG_RED=";31"       # foreground color red
ANSI_FG_BLU=";34"       # foreground color blue
ANSI_FG_BR_BLU=";94"    # foreground color bright blue
ANSI_FG_BR_YLW=";93"    # foreground color bright yellow
# Background (BG) colors: 40-107 (not continuous); TODO: ADD THE REST OF THE CODES!
# - See: https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit
ANSI_BG_BLK=";40"       # background color black
ANSI_BG_RED=";41"       # background color red
ANSI_BG_BLU=";44"       # background color blue
ANSI_BG_BR_BLU=";104"   # background color bright blue
ANSI_BG_BR_YLW=";103"   # background color bright yellow
#
# --------- ANSI numeric codes end ------------
#
ANSI_END="m"        # end of an ANSI formatting sequence
#
# turn OFF ANSI formatting; ie: disable all formatting by specifying `ANSI_START` and
# `ANSI_END` withOUT any formatting codes in between!
ANSI_OFF="${ANSI_START}${ANSI_END}"

# Let's use `f` for "format on" and `F` for "format off".
# Ex:
# format on; set whatever format codes you want between `ANSI_START` and `ANSI_END`
f="${ANSI_START}${ANSI_INVERTED}${ANSI_END}"
# format off; will always be this
F="${ANSI_OFF}"

# Set the `f` format variable by writing any and all passed-in ANSI numeric codes in between
# `ANSI_START` and `ANSI_END`.
#
# Usage:
#       set_f ansi_format_codes...
#
# Prints to stdout:
#       NA
#
# Example:
#       set_f ANSI_BOLD ANSI_UNDERLINE ANSI_SLOW_BLINK ANSI_FG_BR_BLU
#       echo -e "${f}This string is bold, underlined, blinking, bright blue.${F} This is not."
#
set_f() {
    f="$(make_f_str "$@")"
}

# Make an ANSI format string. This is really useful when you want to make multiple `f` type format
# strings to be used in the same `echo -e` or print command.
#
# Usage:
#       make_f_str ansi_format_codes...
#
# Prints to stdout:
#       The formatted f string for you to manually store into your own format variable.
#
# Example:
#       f1="$(make_f_str ANSI_ITALIC ANSI_FG_RED)"      # italic red font
#       f2="$(make_f_str ANSI_UNDERLINE ANSI_FG_BLU)"   # underlined blue font
#       echo -e "${f1}I am italic red.${F} ${f2}I am underlined blue.${F} I am normal."
#
make_f_str() {
    format_str='${ANSI_START}'
    for format_arg in "$@"; do
        format_str="$(printf "%s\${%s}" "$format_str" "$format_arg")"
    done
    format_str="$format_str"'${ANSI_END}'

    # now do variable substitution in that string to replace all `${variable_name}` parts with the
    # value of those variables
    format_str="$(eval echo "$format_str")"
    echo "$format_str"
}

# A simple wrapper to wrap your text output you'd like to print with the currently-set `f` format
# string.
#
# Example Usage:
#       # source this file
#       . ./ansi_text_format_lib.sh
#       # Set your format string
#       set_f ANSI_BOLD ANSI_UNDERLINE ANSI_SLOW_BLINK ANSI_FG_BR_BLU
#       # view the current format string
#       echo "$f"
#       # Now print something in that format
#       ansi_echo "This library works very well! I am very pleased with its usage and format! :)"
#
ansi_echo() {
    echo -e "${f}$@${F}"
}

# An alternative to (and probably better-named than) `ansi_echo`.
f_echo() {
    ansi_echo "$@"
}

run_tests() {
    echo "Running tests."

    # Test 4 ways to use this library:

    # 1. Do it manually with the ANSI codes directly.
    echo -e "${ANSI_START}${ANSI_INVERTED}${ANSI_END}I am highlighted.${ANSI_OFF} I am normal."
    # or
    echo -e "${ANSI_START}${ANSI_INVERTED}${ANSI_END}I am highlighted.${F} I am normal."

    # 2. Manually use the ANSI codes to create your own format f variables.
    f="${ANSI_START}${ANSI_INVERTED}${ANSI_END}"
    echo -e "${f}I am highlighted.${F} I am normal."

    # 3. Call `set_f`, then use the `f` format variable.
    set_f ANSI_BOLD ANSI_UNDERLINE ANSI_SLOW_BLINK ANSI_FG_BR_BLU
    echo -e "${f}This string is bold, underlined, blinking, bright blue.${F} This is not."

    # 4. Call `make_f_str` and then write its output to your own format variables.
    f1="$(make_f_str ANSI_ITALIC ANSI_FG_RED)"      # italic red font
    f2="$(make_f_str ANSI_UNDERLINE ANSI_FG_BLU)"   # underlined blue font
    echo -e "${f1}I am italic red.${F} ${f2}I am underlined blue.${F} I am normal."
    # Same as above. Apparently the `${F}` is NOT required between subsequent format settings
    # unless you need to disable certain formatting, such as highlighting, background colors, or
    # underlining, for instance, on the space characters between the formatted strings as well.
    echo -e "${f1}I am italic red. ${f2}I am underlined blue.${F} I am normal."
}

main() {
    echo "Running main."
    run_tests
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
    main
fi


# SAMPLE OUTPUT:
#
# 1) WHEN RUN.
# - NB: run this yourself to see the pretty formatting!
#
#       eRCaGuy_hello_world/bash$ ./ansi_text_format_lib.sh
#       Running main.
#       Running tests.
#       I am highlighted. I am normal.
#       I am highlighted. I am normal.
#       I am highlighted. I am normal.
#       This string is bold, underlined, blinking, bright blue. This is not.
#       I am italic red. I am underlined blue. I am normal.
#       I am italic red. I am underlined blue. I am normal.
#
#
# 2) WHEN SOURCED (no output)
