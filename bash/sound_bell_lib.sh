#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 1 Feb. 2023

# A library you can source (import) or run to get access to a `sound_bell`
# function which plays a "ding" type bell sound from the terminal.
#
# Status: done and works!

# keywords: bell sound; play sounds in bash

# Check this script with:
#
##      shellcheck bash/sound_bell_lib.sh
#
# Run command:
#
#       bash/sound_bell_lib.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/sound_bell_lib.sh

# References:
# 1. Differences between source and export: [my answer]:
#    https://stackoverflow.com/a/62626515/4561887
# 1. https://stackoverflow.com/a/70662116/4561887
# 1. ***** https://stackoverflow.com/a/70662049/4561887
# 1. eRCaGuy_hello_world/bash/argument_parsing__3_advanced__gen_prog_template.sh


RETURN_CODE_SUCCESS=0
# shellcheck disable=SC2034
RETURN_CODE_ERROR=1

# ------------------------------ Library START ---------------------------------

# Play the bell sound "ding" to alert the user of something.
#
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
    delay_sec="0.12"

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

run_unit_tests() {
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

main() {
    run_unit_tests
}

# Check if this script is being sourced or executed.
# See:
# 1. This answer here where I first learned about `"${BASH_SOURCE[0]}" = "$0"`:
#    https://stackoverflow.com/a/29967433/4561887
# 1. My answer here: https://stackoverflow.com/a/70662116/4561887
if [ "${BASH_SOURCE[0]}" = "$0" ]; then
    # This script is being run.
    __name__="__main__"
else
    # This script is being sourced.
    __name__="__source__"
fi

# ------------------------------------------------------------------------------
# Main program entry point
# ------------------------------------------------------------------------------

# Only run `main` if this script is being **run**, NOT sourced (imported)
# - See my answer: https://stackoverflow.com/a/70662116/4561887
if [ "$__name__" = "__main__" ]; then
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
#
#       real    0m6.340s
#       user    0m0.011s
#       sys 0m0.009s
