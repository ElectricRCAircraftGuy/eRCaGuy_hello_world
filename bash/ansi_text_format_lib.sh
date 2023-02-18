#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# A general purpose ANSI text formatting library in Bash. Easily make your terminal text bold, red,
# blue, blinking, inverted colors (highlighted), etc.
# - See all the possible codes on Wikipedia, starting here:
#   https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
#
# Status: wip

# keywords: (keywords to easily grep or ripgrep in this repo for this program and what it teaches)

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
# 1. NB: WHEN USING `echo`, DON'T FORGET THE `-e` to escape the color codes! Ex:
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
# Foreground (FG) colors: 30-97  (not continuous); TODO: FILL THE REST IN!
# - See: https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit
ANSI_FG_BLK=";30"       # foreground color black
ANSI_FG_RED=";31"       # foreground color red
ANSI_FG_BLU=";34"       # foreground color blue
ANSI_FG_BR_BLU=";94"    # foreground color bright blue
ANSI_FG_BR_YLW=";93"    # foreground color bright yellow
# Background (BG) colors: 40-107 (not continuous); TODO: FILL THE REST IN!
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
# Usage:
#       set_f ANSI_BOLD ANSI_UNDERLINE ANSI_SLOW_BLINK ANSI_FG_BR_BLU
#       echo -e "${f}This string is bold, underlined, blinking, bright blue.${F} This is not."
set_f() {
    format_str='${ANSI_START}'
    for format_arg in "$@"; do
        format_str="$(printf "%s\${%s}" "$format_str" "$format_arg")"
    done
    format_str="$format_str"'${ANSI_END}'

    # now do variable substitution in that string to replace all `${variable_name}` parts with the
    # value of those variables
    format_str="$(eval echo "$format_str")"
    # echo "$format_str"  # debugging

    f="$format_str"
}

make_format_str() {
    echo ""
}


main() {
    echo "Running main."

    set_f ANSI_BOLD ANSI_UNDERLINE ANSI_SLOW_BLINK ANSI_FG_BR_BLU
    echo -e "${f}This string is bold, underlined, blinking, bright blue.${F} This is not."

    # branch_info="${F}${git_branch}${f} ${F}${git_short_hash}${f}"
    # echo -e "$branch_info"  # NB: DON'T FORGET THE `-e` here to escape the color codes!

    # set_format "$ANSI_INV"
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
# 1) WHEN RUN (it prints "Running main.")
#
#       eRCaGuy_hello_world$ bash/ansi_text_format_lib.sh
#       Running main.
#
#
# 2) WHEN SOURCED (no output)
#
#       eRCaGuy_hello_world$ . bash/ansi_text_format_lib.sh
