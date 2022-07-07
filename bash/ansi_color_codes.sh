#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 6 July 2022

# Practice printing with various formatting using ANSI color and formatting codes.
# Status: done and works!

# keywords: print ansi color codes; print ansi colors; print colors; print color codes; shell
# formatting and print formatting

# Check this script with: `shellcheck ansi_color_codes.sh`

# Run command:
#       ./ansi_color_codes.sh

# References:
# 1. "eRCaGuy_hello_world/c/strncmpci.c"
# 1. "eRCaGuy_hello_world/c/printf_bold_and_colors.c"
# 1. *****+ ANSI colors and color codes on Wikipedia
#   1. https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
#   1. https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit


# From "eRCaGuy_hello_world/c/printf_bold_and_colors.c":
#
# SOME ANSI COLOR CODES--VERY INCOMPLETE LIST--consider how to refactor this (or just complete it
# as-is) to make it more-usable.
# See a full table of colors here:
# 1. https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
# 1. https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit
ANSI_OFF="\e[m"
ANSI_START="\e["
ANSI_END="m"
ANSI_BOLD=";1"
ANSI_SLOW_BLINK=";5"
ANSI_FAST_BLINK=";6"   # (not widely supported--does NOT work in a Linux Ubuntu bash shell)
ANSI_FG_BLK=";30"       # foreground color black
ANSI_BG_BLK=";40"       # background color black
ANSI_FG_RED=";31"       # foreground color red
ANSI_BG_RED=";41"       # background color red
ANSI_FG_BLU=";34"      # foreground color blue
ANSI_BG_BLU=";44"      # background color blue
ANSI_FG_BR_BLU=";94"   # foreground color bright blue
ANSI_BG_BR_BLU=";104"  # background color bright blue
ANSI_FG_BR_YLW=";93"    # foreground color bright yellow
ANSI_BG_BR_YLW=";103"   # background color bright yellow

# From "eRCaGuy_hello_world/c/printf_bold_and_colors.c":
#
# 1 = bold; 5 = slow blink; 31 = foreground color red
# 34 = foreground color blue
# See: https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
COLOR_OFF="\e[m"
COLOR_BOLD_SLOW_BLINKING="\e[1;5m"
COLOR_BOLD_SLOW_BLINKING_RED="\e[1;5;31m"
COLOR_BOLD_BLUE="\e[1;34m"


echo "bold \"Hello\":"
echo -e "${ANSI_START}${ANSI_BOLD}${ANSI_END}Hello${ANSI_OFF} World."
# OR:
printf "%b\n\n" "${ANSI_START}${ANSI_BOLD}${ANSI_END}Hello${ANSI_OFF} World."

echo "bold foreground blue:"
printf "%b\n" "${ANSI_START}${ANSI_BOLD}${ANSI_FG_BLU}${ANSI_END}Hello${ANSI_OFF} World."
echo ""

printf "%b%b\n" \
    "${ANSI_START}${ANSI_BOLD}${ANSI_FG_BLU}${ANSI_END}Hello${ANSI_OFF} "\
    "World."
printf "%b%b%b\n" \
    "${ANSI_START}${ANSI_BOLD}${ANSI_FG_BLU}${ANSI_END}He${ANSI_OFF}"\
    "${ANSI_START}${ANSI_FG_BLU}${ANSI_END}llo${ANSI_OFF} "\
    "World."
printf "%b%b\n" \
    "${ANSI_START}${ANSI_FG_BLU}${ANSI_END}Hello${ANSI_OFF} "\
    "${ANSI_START}${ANSI_BOLD}${ANSI_FG_BLU}${ANSI_END}Hello${ANSI_OFF}"
printf "%b%b\n" \
    "${ANSI_START}${ANSI_BOLD}${ANSI_FG_BLU}${ANSI_END}Hello${ANSI_OFF} "\
    "${ANSI_START}${ANSI_BG_BLU}${ANSI_END}World${ANSI_OFF}."
printf "%b%b\n" \
    "${ANSI_START}${ANSI_BOLD}${ANSI_FG_BR_BLU}${ANSI_END}Hello${ANSI_OFF} "\
    "${ANSI_START}${ANSI_BG_BR_BLU}${ANSI_END}World${ANSI_OFF}."
printf "%b%b\n" \
    "${ANSI_START}${ANSI_BOLD}${ANSI_FG_BLU}${ANSI_SLOW_BLINK}${ANSI_END}Hello${ANSI_OFF} "\
    "${ANSI_START}${ANSI_BG_BLU}${ANSI_SLOW_BLINK}${ANSI_END}World${ANSI_OFF}."
printf "%b%b\n" \
    "${ANSI_START}${ANSI_BOLD}${ANSI_FG_BLU}${ANSI_FAST_BLINK}${ANSI_END}Hello${ANSI_OFF} "\
    "${ANSI_START}${ANSI_BG_BLU}${ANSI_FAST_BLINK}${ANSI_END}World${ANSI_OFF}."
printf "%b%b\n" \
    "${ANSI_START}${ANSI_BOLD}${ANSI_FG_RED}${ANSI_SLOW_BLINK}${ANSI_END}Hello${ANSI_OFF} "\
    "${ANSI_START}${ANSI_BG_RED}${ANSI_SLOW_BLINK}${ANSI_END}World${ANSI_OFF}."
printf "%b%b\n" \
    "${ANSI_START}${ANSI_BOLD}${ANSI_FG_BR_YLW}${ANSI_SLOW_BLINK}${ANSI_END}Hello${ANSI_OFF} "\
    "${ANSI_START}${ANSI_BG_BR_YLW}${ANSI_SLOW_BLINK}${ANSI_END}World${ANSI_OFF}."
printf "%b%b\n" \
    "${ANSI_START}${ANSI_BOLD}${ANSI_FG_BR_YLW}${ANSI_SLOW_BLINK}${ANSI_END}Hello${ANSI_OFF} "\
    "${ANSI_START}${ANSI_BG_BR_YLW}${ANSI_SLOW_BLINK}${ANSI_FG_BLK}${ANSI_END}World${ANSI_OFF}."


# SAMPLE OUTPUT:
# NB: RUN THIS YOURSELF TO SEE THE ACTUAL COLORS, FORMATTING, AND BLINKING!
#
#       eRCaGuy_hello_world/bash$ ./ansi_color_codes.sh
#       bold "Hello":
#       Hello World.
#       Hello World.
#
#       bold foreground blue:
#       Hello World.
#
#       Hello World.
#       Hello World.
#       Hello Hello
#       Hello World.
#       Hello World.
#       Hello World.
#       Hello World.
#       Hello World.
#       Hello World.
#       Hello World.

