#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 1 Feb. 2023

# A library you can source (import) or run to get access to a `sound_bell`
# function which plays a "ding" type bell sound from the terminal.
#
# Status: done and works!

# keywords: bell sound; play sounds in bash

# Check this script with: `shellcheck sound_bell_lib.sh`

# Run command:
#       ./sound_bell_lib.sh
# Source (import) command to get access to these functions:
#       . ./sound_bell_lib.sh

# References:
# 1. Differences between source and export: [my answer]:
#    https://stackoverflow.com/a/62626515/4561887
# 1. https://stackoverflow.com/a/70662116/4561887
# 1. ***** https://stackoverflow.com/a/70662049/4561887
# 1. eRCaGuy_hello_world/bash/argument_parsing__3_advanced__gen_prog_template.sh


RETURN_CODE_SUCCESS=0
RETURN_CODE_ERROR=1

# ------------------------------ Library START ---------------------------------

# Play the bell sound "ding" to alert the user of something
# Usage:
#       sound_bell [number_of_times [second_delay_between_sounds]]
# Examples
#       sound_bell          # sound bell once
#       sound_bell 1        # sound bell once
#       sound bell 2        # sound bell 2x with default delay between each
#       sound bell 2 .2     # sound bell 2x with delay of 0.2 sec between each
#       sound bell 3 .5     # sound bell 3x with delay of 0.5 sec between each
sound_bell() {
    # set default values
    num_times="1"
    delay_sec="0.1"

    # set to user-defined values if the user passes them in as args
    if [ -n "$1" ]; then
        num_times="$1"
    fi
    if [ -n "$2" ]; then
        delay_sec="$2"
    fi

    # sound the bell
    for (( i=0; i<"$num_times"; i++ )); do
        printf "%b" "\a"  # bell sound

        # Only sleep the delay time **between** bell sounds, and NOT after the last one
        # - for how to do arithmetic expansion (math in Bash), see my answer here:
        #   https://stackoverflow.com/a/71567705/4561887
        if [ "$i" -lt "$((num_times-1))" ]; then
            sleep "$delay_sec"
        fi
    done
}

# ------------------------------- Library END ----------------------------------

parse_args() {
    # nothing to do
    return "$RETURN_CODE_SUCCESS"
}

# run some basic tests if this program is run rather than sourced!
main() {
    # unit tests

    echo "sound_bell";      sleep 1
    sound_bell

    echo "sound_bell 2";    sleep 1
    sound_bell 2

    echo "sound_bell 2 .2"; sleep 1
    sound_bell 2 .2

    echo "sound_bell 3 .5"; sleep 1
    sound_bell 3 .5

    echo "sound_bell 1";    sleep 1
    sound_bell 1
}

# Set the global variable `run` to "true" if the script is being **executed** (not sourced) and
# `main` should run, and set `run` to "false" otherwise. One might source this script but intend
# NOT to run it if they wanted to import functions from the script.
# See:
# 1. my answer: https://stackoverflow.com/a/70662049/4561887
# 1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/check_if_sourced_or_executed.sh
run_check() {
    # This is akin to `if __name__ == "__main__":` in Python.
    if [ "${FUNCNAME[-1]}" == "main" ]; then
        # This script is being EXECUTED, not sourced
        run="true"
    fi
}

# ------------------------------------------------------------------------------
# Main program entry point
# ------------------------------------------------------------------------------

# Only run main function if this file is being executed, NOT sourced.
run="false"
run_check
if [ "$run" == "true" ]; then
    parse_args "$@"
    time main
    exit $RETURN_CODE_SUCCESS
fi


# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world$ bash/sound_bell_lib.sh
#       sound_bell
#       sound_bell 2
#       sound_bell 2 .2
#       sound_bell 3 .5
#       sound_bell 1

