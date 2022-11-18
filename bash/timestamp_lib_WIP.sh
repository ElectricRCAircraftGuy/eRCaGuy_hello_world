#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 12 July 2022

# A library to easily obtain high-resolution absolute timestamps in bash.
#
# Take what I learned from "timestamps_with_rounding_truncating_and_math.sh" and
# make some importable (`source`able) functions out of it!
#
# If you source this library via `. timestamp_lib.sh`, it will NOT run `main`
# below, but if you run this library with `./timestamp_lib.sh` it WILL run
# the `main` function below, just like in Python!

# Status: wip

# Check this script with: `shellcheck timestamp_lib.sh`

# Run command:
#       ./timestamp_lib.sh

# References:
# 1. "eRCaGuy_hello_world/bash/timestamps_with_rounding_truncating_and_math.sh"
#    for timestamps
# 1. "eRCaGuy_hello_world/bash/argument_parsing__3_advanced__gen_prog_template.sh"
#    for layout, including the program entry point and handling sourcing
#    vs running this script
# 1. [my answer] difference between `source` and `export` in bash:
#    https://stackoverflow.com/a/62626515/4561887
# 1. "eRCaGuy_hello_world/c/timinglib.h" and .c - a great demo timing lib
#    to look at in C. I got a lot of my ideas for this script there.



# ------------------------------ Library START ---------------------------------

MS_PER_SEC="1000"
US_PER_SEC="1000000"
NS_PER_SEC="1000000000"

NS_PER_MS="1000000"
NS_PER_US="1000"


# Floating point timestamps

# Get an absolute timestamp in floating point seconds.
seconds_float() {
    time_sec="$(date +"%s.%N")"
    echo "$time_sec"
}

# Get an absolute timestamp in floating point milliseconds.
millis_float() {
    time_ms="$(bc <<< "$(seconds_float)*$MS_PER_SEC")"
    echo "$time_ms"
}

# Get an absolute timestamp in floating point microseconds.
micros_float() {
    time_us="$(bc <<< "$(seconds_float)*$US_PER_SEC")"
    echo "$time_us"
}

# Get an absolute timestamp in floating point nanoseconds.
nanos_float() {
    time_ns="$(bc <<< "$(seconds_float)*$NS_PER_SEC")"
    echo "$time_ns"
}


# Integer timestamps
# All of these timestamps will be **truncated** (floored), NOT
# rounded-to-nearest, integers.

# Get an absolute timestamp in integer seconds.
seconds_int() {
    time_sec="$(bc <<< "$(seconds_float)/1")"
    echo "$time_sec"
}

# Get an absolute timestamp in integer milliseconds.
millis_int() {
    time_ms="$(bc <<< "$(seconds_float)*$MS_PER_SEC/1")"
    echo "$time_ms"
}

# Get an absolute timestamp in integer microseconds.
micros_int() {
    time_us="$(bc <<< "$(seconds_float)*$US_PER_SEC/1")"
    echo "$time_us"
}

# Get an absolute timestamp in integer nanoseconds.
nanos_int() {
    time_ns="$(bc <<< "$(seconds_float)*$NS_PER_SEC/1")"
    echo "$time_ns"
}


# Default to integer timestamps so that you can easily do math with the values
# using bash "arithmetic expansion", rather than having to rely on the
# confusing `bc` utility to do floating point math.
# See my answer:
# https://stackoverflow.com/a/71567705/4561887

# Get an absolute timestamp in integer seconds.
seconds() {
    seconds_int
}

# Get an absolute timestamp in integer milliseconds.
millis() {
    millis_int
}

# Get an absolute timestamp in integer microseconds.
micros() {
    micros_int
}

# Get an absolute timestamp in integer nanoseconds.
nanos() {
    nanos_int
}


# special sleep functions for loop timing
sleep_until() {
    #########
}

# ------------------------------- Library END ----------------------------------

RETURN_CODE_SUCCESS=0
RETURN_CODE_ERROR=1

parse_args() {
    # nothing to do
    return "$RETURN_CODE_SUCCESS"
}

# run some basic tests if this program is run rather than sourced!
main() {
    # 1st, just print all timestamps to ensure they work

    seconds_float
    millis_float
    micros_float
    nanos_float
    echo ""
    seconds_int
    millis_int
    micros_int
    nanos_int
    echo ""
    seconds
    millis
    micros
    nanos
    echo ""

    # 2nd, store some timestamps into variables and do some basic integer math

    time_start_ms="$(millis)"
    sleep 1
    time_end_ms="$(millis)"

    time_delta_ms=$((time_end_ms - time_start_ms))

    echo "time_start_ms = $time_start_ms"
    echo "time_end_ms   = $time_end_ms"
    echo "time_delta_ms = $time_delta_ms"
    echo ""

    # 3rd, store some timestamps into variables and do some basic floating
    # point math via `bc`

    time_start_float_sec="$(seconds_float)"
    sleep 1
    time_end_float_sec="$(seconds_float)"

    time_delta_float_sec="$(bc <<< "scale=20; \
        $time_end_float_sec - $time_start_float_sec")"

    echo "time_start_float_sec = $time_start_float_sec"
    echo "time_end_float_sec   = $time_end_float_sec"
    echo "time_delta_float_sec = $time_delta_float_sec"
    echo ""
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
    # Explicitly exit after `main` to prevent any code from running afterwards
    # in case someone modifies this script and adds more code below.
    # See: https://unix.stackexchange.com/a/449508/114401
    exit $RETURN_CODE_SUCCESS
fi


# SAMPLE OUTPUT:
#
# 1. running the script
#
#       eRCaGuy_hello_world/bash$ ./timestamp_lib.sh
#       1657695420.916846195
#       1657695420922.458811000
#       1657695420931420.694000000
#       1657695420940175000.000000000
#
#       1657695420
#       1657695420959
#       1657695420968040
#       1657695420979077351
#
#       1657695420
#       1657695420999
#       1657695421005969
#       1657695421013023665
#
#       time_start_ms = 1657695421019
#       time_end_ms   = 1657695422030
#       time_delta_ms = 1011
#
#       time_start_float_sec = 1657695422.038250473
#       time_end_float_sec   = 1657695423.046251106
#       time_delta_float_sec = 1.008000633
#
#
#       real    0m2.138s
#       user    0m0.083s
#       sys 0m0.062s
#
#
# 2. sourcing the script and then calling the functions directly
#
#       eRCaGuy_hello_world/bash$ . timestamp_lib.sh
#       eRCaGuy_hello_world/bash$ seconds
#       1657695643
#       eRCaGuy_hello_world/bash$ millis
#       1657695644925
#       eRCaGuy_hello_world/bash$ micros
#       1657695645854138
#       eRCaGuy_hello_world/bash$ nanos
#       1657695646715097304


