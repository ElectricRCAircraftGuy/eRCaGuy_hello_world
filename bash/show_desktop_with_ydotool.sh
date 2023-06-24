#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 23 June 2023
#
# Use `ydotool` to press Windows + D to toggle showing the desktop.
# See my answer here: https://askubuntu.com/a/1473061/327339
#
# NB: this tool works in the X11 OR Wayland window manager. It is newer than `xdotool`, and more
# modern. It is meant to help us deal with the problems the new Wayland window manager has caused.
#
# Dependencies:
# 1. `ydotool` - follow my detailed installation instructions here:
#   1. https://askubuntu.com/a/1473061/327339
#   1. https://gabrielstaples.com/ydotool-tutorial/
#
# STATUS: done and works!
#
# Works in Ubuntu 22.04.2?:
# 1. [yes] with the X11 window manager - result: WORKS, but requires `sudo` for the daemon.
# 2. [yes] with the Wayland window manager - result: WORKS, but requires `sudo` for the daemon.

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


# 0. Kill the `ydotoold` background running processes
sudo pkill ydotoold

# 1. start the `ydotoold` background daemon (`sudo -b` runs it in the
# background; see `sudo -h`).
# - It takes a couple seconds to fully start up and print "READY". Once it does
#   that, hit Enter a couple times to clear out the command line.
sudo -b ydotoold --socket-path="$HOME/.ydotool_socket" --socket-own="$(id -u):$(id -g)"
sleep 2  # give it a chance to start up fully


press_windows_plus_d() {
    YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 125:1 32:1 32:0 125:0
}

echo "Pressing Windows + D once to hide all windows."
press_windows_plus_d

sleep 1

echo "Pressing Windows + D again to show all windows."
press_windows_plus_d



# SAMPLE OUTPUT:
#
# 1) WHEN RUN in the X11 window manager:
#
#       eRCaGuy_hello_world$ bash/show_desktop_with_ydotool.sh
#       Socket path: /home/gabriel/.ydotool_socket
#       Removing old stale socket
#       Socket permission: 0600
#       Socket ownership: UID=1000, GID=1000
#       READY
#       Pressing Windows + D once to hide all windows.
#       Pressing Windows + D again to show all windows.
#
#
# 2) WHEN RUN in the Wayland window manager:
#
#       eRCaGuy_hello_world/bash$ ./show_desktop_with_ydotool.sh
#       Socket path: /home/gabriel/.ydotool_socket
#       Removing old stale socket
#       Socket permission: 0600
#       Socket ownership: UID=1000, GID=1000
#       READY
#       WARNING: running xinput against an Xwayland server. See the xinput man page for details.
#       unable to find device pointer:ydotoold virtual device
#       Pressing Windows + D once to hide all windows.
#       Pressing Windows + D again to show all windows.
