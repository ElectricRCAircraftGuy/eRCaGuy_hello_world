#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 23 June 2023
#
# Try to use `wmctrl` to press Windows + D to toggle showing the desktop.
# See this answer: https://askubuntu.com/a/905480/327339
#
# Dependencies:
#
#       sudo apt update
#       sudo apt install wmctrl
#
# STATUS: done and works!:
#
# Works in Ubuntu 22.04.2?:
# 1. [yes] with the X11 window manager - result: WORKS.
# 2. [yes] with the Wayland window manager - result: WORKS.

# keywords to easily grep or ripgrep in this repo for this program and what it teaches
#
# KEYWORDS:

# Check this script with:
#
##      shellcheck bash/show_desktop_with_wmctrl.sh
#
# Run command:
#
#       bash/show_desktop_with_wmctrl.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/show_desktop_with_wmctrl.sh

# References:
# 1. See link above.
# 1.

toggle_windows() {
    # This code was originally copied from this answer by @AndAC here:
    # https://askubuntu.com/a/905480/327339

    status="$(wmctrl -m | grep "showing the desktop" | sed -r 's/(.*)(ON|OFF)/\2/g')"
    if [ $status == "ON" ]; then
        wmctrl -k off
    else
        wmctrl -k on
    fi
}

# My own version
toggle_windows2() {
    status="$(wmctrl -m | grep "showing the desktop" | grep -Eo "ON|OFF")"
    if [ $status == "ON" ]; then
        wmctrl -k off
    else
        wmctrl -k on
    fi
}

echo "Toggling windows once to hide all windows."
# toggle_windows
toggle_windows2

sleep 1

echo "Toggling windows again to show all windows."
# toggle_windows
toggle_windows2


# SAMPLE OUTPUT:
#
# 1) WHEN RUN
#
#       eRCaGuy_hello_world$ time bash/show_desktop_with_wmctrl.sh
#       Toggling windows once to hide all windows.
#       Toggling windows again to show all windows.
#
#       real    0m1.024s
#       user    0m0.019s
#       sys 0m0.013s
#
#
