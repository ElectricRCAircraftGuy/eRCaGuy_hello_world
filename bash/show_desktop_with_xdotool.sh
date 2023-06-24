#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 23 June 2023
#
# Use `xdotool` to press Windows + D to toggle showing the desktop.
# See my answer here: https://askubuntu.com/a/1109490/327339
# NB: this tool ONLY works in the **X11** window manager, NOT Wayland. See my answer above for
# details and how to switch to X11.
#
# Dependencies:
#
#       sudo apt install xdotool
#
# STATUS: done and works!

# keywords to easily grep or ripgrep in this repo for this program and what it teaches
#
# KEYWORDS:

# Check this script with:
#
##      shellcheck bash/show_desktop_with_xdotool.sh
#
# Run command:
#
#       bash/show_desktop_with_xdotool.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/show_desktop_with_xdotool.sh

# References:
# 1. See link above.
# 1.

SEC=5

echo "Running command in $SEC seconds."
echo "Press Windows + D to come back."

sleep "$SEC"

xdotool key --clearmodifiers Super+d


# SAMPLE OUTPUT:
#
# 1) WHEN RUN
#
#       eRCaGuy_hello_world$ time bash/show_desktop_with_xdotool.sh
#       Running command in 5 seconds.
#       Press Windows + D to come back.
#
#       real    0m5.084s
#       user    0m0.008s
#       sys 0m0.004s
#
