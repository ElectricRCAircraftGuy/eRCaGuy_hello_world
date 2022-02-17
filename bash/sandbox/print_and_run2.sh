#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 17 Feb. 2022

# Trying out this answer here: https://stackoverflow.com/a/71151669/4561887
# IT WORKS! GREAT ANSWER!

# keywords:

# Run command:
#       ./hello_world_basic.sh

# References:
# 1.


print_and_run_cmd() {
    local PS4='Running cmd:  '
    local -
    # set -v
    # set -v
    set -o xtrace

    "$@"
}

print_and_run_cmd2()
{
    local -n array_reference="$1"
    local PS4='Running cmd:  '
    local -
    set -o xtrace

    "${array_reference[@]}"
}

print_and_run_cmd echo 'Hello World!'
echo ""

cmd_array=(echo 'Hello World!')
print_and_run_cmd "${cmd_array[@]}"
echo ""

cmd_array=(ls -1 "$HOME/temp/some folder with spaces")
print_and_run_cmd "${cmd_array[@]}"
echo ""

print_and_run_cmd ls -1 "$HOME/temp/some folder with spaces"
echo ""

# DOESN'T WORK! Pipe operator not allowed inside the array:
#       syntax error near unexpected token `|'
cmd_array=(ls -1 "$HOME/temp/some folder with spaces" | grep a)
print_and_run_cmd "${cmd_array[@]}"
echo ""

cmd_array=(ls -1 "$HOME/temp/some folder with spaces")
print_and_run_cmd2 cmd_array
echo ""



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./hello_world_basic.sh a b c d e f g
#       a b c d e f g
