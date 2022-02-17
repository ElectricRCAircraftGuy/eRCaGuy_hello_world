#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 17 Feb. 2022

# Demonstrate some better ways to print and run commands!

# keywords: print and run arrays, array cmds, array commands; print and run bash commands cmds

# Check this script with: `shellcheck print_and_run.sh`

# Run command:
#       ./print_and_run.sh

# References:
# 1. *****+ THIS IS THE ANSWER THIS CODE IS BASED ON!:
#    https://stackoverflow.com/a/71151669/4561887
# 1. See also: eRCaGuy_hello_world/bash/sandbox/print_and_run2.sh


# Print and run the passed-in command, which is passed in as an array **by reference**
# See here for a full explanation: https://stackoverflow.com/a/71151669/4561887
# USAGE:
#       cmd_array=(ls -a -l -F /)
#       print_and_run1 cmd_array
print_and_run1() {
    local -n array_reference="$1"
    local PS4='Running cmd:  '
    local -
    set -o xtrace
    # Call the cmd
    "${array_reference[@]}"
}

# Print and run the passed-in command, which is passed in as members of an array **by value**
# See here for a full explanation: https://stackoverflow.com/a/71151669/4561887
# USAGE:
#       cmd_array=(ls -a -l -F /)
#       print_and_run2 "${cmd_array[@]}"
print_and_run2() {
    local PS4='Running cmd:  '
    local -
    set -o xtrace
    # Call the cmd
    "$@"
}

cmd_array=(ls -1 "$HOME/temp/some folder with spaces")

print_and_run1 cmd_array
echo ""
print_and_run2 "${cmd_array[@]}"
echo ""






# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./print_and_run.sh
#       Running cmd:  ls -1 '/home/gabriel/temp/some folder with spaces'
#       file1.md
#       file2.md
#
#       Running cmd:  ls -1 '/home/gabriel/temp/some folder with spaces'
#       file1.md
#       file2.md
#
