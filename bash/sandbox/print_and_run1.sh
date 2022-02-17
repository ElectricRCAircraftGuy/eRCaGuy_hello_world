#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 16 Feb. 2022

# (description)

# Run command:
#       ./hello_world_basic.sh

# References:
# 1. [my Q] How to write bash function to print and run command when the command has arguments with spaces or things to be expanded
#    https://stackoverflow.com/a/71118015/4561887
# 1. answer trying to help me: https://stackoverflow.com/a/71151221/4561887
# 1. my answer: https://stackoverflow.com/a/71151092/4561887



RETURN_CODE_SUCCESS=0
RETURN_CODE_ERROR=1

# Exit if the last command failed.
exit_if_last_command_failed() {
    error_code="$?"
    if [ "$error_code" -ne 0 ]; then
        echo_error "Last command failed with error code $error_code."
        exit $RETURN_CODE_ERROR
    fi
}

# Print and run the cmd stored in the passed-in array
print_and_run() {
    # local -n array_reference="$1"

    # WORKS
    # echo "Running cmd:  $*" >&2  # the `>&2` part writes this echo to stderr INSTEAD OF to stdout!
    # WORKS
    echo "Running cmd:  $*"


    # run the command by calling all elements of the command array at once
    "$@"
}

print_and_run2() {
    echo "Running cmd: $1"
    eval "$1"
}


PRINT_CMD_ON() {
    printf "%s" "Running cmd: "
    set -v
}

PRINT_CMD_OFF() {
    set +v
    # doesn't seem to be silent: :( https://stackoverflow.com/questions/71150916/bash-how-to-print-and-run-a-cmd-array-which-has-the-pipe-operator-in-it/71151092?noredirect=1#comment125773130_71150916
    # { set +v; } 2>/dev/null
}

# # this works! BUT, Limitations include:
# # 1. It sends the lines it prints to stderr, not stdout
# # 2. it prints `set +v` at the end, which I don't want.
# printf "%s" "Running cmd: "
# set -v
# ls -a / | grep -C 9999 --color=always "home"
# set +v

PS4='$BASH_SOURCE:$LINENO+'

PRINT_CMD_ON
ls -a $HOME/temp | grep --color=always "ew"
{ set +v; } 2>/dev/null
PRINT_CMD_OFF



# set -T
# trap 'test "$FUNCNAME" = print_and_run_cmd || trap_saved_command="${BASH_COMMAND}"' DEBUG
# print_and_run_cmd(){
#     echo "Running this cmd: ${trap_saved_command#* }"
#     "$@"
# }
# outer(){
#     cmd_array=(ls -1 "$HOME/temp/some folder with spaces")
#     print_and_run_cmd "${cmd_array[@]}"
# }
# outer



# # From: https://stackoverflow.com/a/71118015/4561887
# prun() {
#    # in the style of set -x
#    # print to stderr, so output can be captured
#    # echo "Running cmd: $*"
#    # or echo "+ ${*@Q}" >&2
#    # or echo "+$(printf " %q" "$@")" >&2
#    # or echo "+$(/bin/printf " %q" "$@")" >&2
#    echo "Running cmd:$(/usr/bin/printf " %q" "$@")" >&2
#    "$@"
# }

# cmd_array=(ls -a / \| grep "home")
# print_and_run "${cmd_array[@]}"
# print_and_run "${cmd_array[@]}"
# exit_if_last_command_failed
# echo ""

# # WORKS!
# cmd='ls -a / | grep -C 9999 --color=always "home"'
# print_and_run2 "$cmd"
# exit_if_last_command_failed
# echo ""

# prun "${cmd_array[@]}"
# exit_if_last_command_failed
# echo ""


# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./hello_world_basic.sh a b c d e f g
#       a b c d e f g
