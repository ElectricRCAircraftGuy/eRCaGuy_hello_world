#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 12 July 2022

# Get high-resolution timestamps in bash, learn how to both **truncate**
# and **round** to a whole number, and show how to do both **floating
# point** math **and** **integer** math on them!

# Status: done and works!

# keywords: timestamps, high-resolution timestamps, truncating, rounding,
# floating point math, integer math

# Check this script with: `shellcheck timestamps_with_rounding_truncating_and_math.sh`

# Run command:
#       ./timestamps_with_rounding_truncating_and_math.sh

# References:
# 1. *****+ MY ANSWER WITH THIS CODE: **TODO**:
#   1. TODO: add an answer somewhere with this code below and/or with my code
#   from "bash/timestamp_lib_WIP.sh", which would be really useful for people I think!
#   1. Potential places to post this as an answer:
#       1. Google search for "bash high resolution timestamps"
#          https://www.google.com/search?q=bash+high+resolution+timestamps&oq=bash+high+resolution+timestamps&aqs=chrome..69i57.4432j0j7&sourceid=chrome&ie=UTF-8
#           1. https://unix.stackexchange.com/q/204796/114401
#           1. https://serverfault.com/q/151109/357116
#           1. https://stackoverflow.com/q/16548528/4561887
# 1. How to do floating point calculations in bash
#   1. main answer: https://stackoverflow.com/a/12723330/4561887
#   1. [my answer]: https://stackoverflow.com/a/58479867/4561887
# 1. tcpdump - how to check rate of packets?:
#    https://serverfault.com/q/521043/357116
# 1. [my answer]: How to use all bash operators, and arithmetic expansion, in
#    bash: https://stackoverflow.com/a/71567705/4561887
# 1. `bc` truncate floating point number:
#    https://stackoverflow.com/a/20558725/4561887


# ------------------------------------------------------------------------------
# 1. Floating point timestamps
# Notes: `<<<` is called a "here string". `bc` is a floating point math program.
# ------------------------------------------------------------------------------

# get floating point timestamps
time_sec="$(date +"%s.%N")"
time_ms="$(bc <<< "$time_sec*1000")"
time_us="$(bc <<< "$time_sec*1000000")"
time_ns="$(bc <<< "$time_sec*1000000000")"

# print them as-is
echo "== Printed as-is =="
echo "time_sec = $time_sec"
echo "time_ms  = $time_ms"
echo "time_us  = $time_us"
echo "time_ns  = $time_ns"
echo ""

# pretty-print them, aligning the decimals and rounding to the appropriate
# number of decimal places
echo "== Pretty-printed with aligned decimals and appropriate number of"\
     "decimals =="
printf "time_sec = %30.9f\n" "$time_sec"
printf "time_ms  = %27.6f\n" "$time_ms"
printf "time_us  = %24.3f\n" "$time_us"
printf "time_ns  = %20.0f\n" "$time_ns"
printf "\n"


# ------------------------------------------------------------------------------
# 2. Whole-number timestamps
# ------------------------------------------------------------------------------

# A. **rounded** to the nearest whole number

# convert the floating point timestamps into whole, rounded integer numbers
time_sec_rounded="$(printf "%.0f" "$time_sec")"
time_ms_rounded="$(printf "%.0f" "$time_ms")"
time_us_rounded="$(printf "%.0f" "$time_us")"
time_ns_rounded="$(printf "%.0f" "$time_ns")"
# print them as-is
echo "time_sec_rounded = $time_sec_rounded"
echo "time_ms_rounded  = $time_ms_rounded"
echo "time_us_rounded  = $time_us_rounded"
echo "time_ns_rounded  = $time_ns_rounded"
echo ""

# B. **truncated** to an integer

# Truncate the floating point timestamps into integers using integer division
# via `scale=0` (the default in `bc`) and `/1` to then force integer division
# by dividing according to that scale setting.
# See:
# 1. How to use `/1`:
#    https://stackoverflow.com/a/20558725/4561887 and
# 1. How to use the `bc` `scale` setting to set decimal precision:
#    https://stackoverflow.com/a/12723330/4561887
# Note: `bc` has a default `scale` of 0, which means that if you do `/1` it will
# divide by 1, truncating via integer division.
time_sec_truncated="$(bc <<< "$time_sec/1")"
time_ms_truncated="$(bc <<< "$time_sec*1000/1")"
time_us_truncated="$(bc <<< "$time_sec*1000000/1")"
time_ns_truncated="$(bc <<< "$time_sec*1000000000/1")"
# print them as-is
echo "time_sec_truncated = $time_sec_truncated"
echo "time_ms_truncated  = $time_ms_truncated"
echo "time_us_truncated  = $time_us_truncated"
echo "time_ns_truncated  = $time_ns_truncated"
echo ""

# ------------------------------------------------------------------------------
# Do some math just to show how
# - both floating point math **and** integer math!
# ------------------------------------------------------------------------------

# 1. With the floating-point numbers using the `bc` program.
# See: https://stackoverflow.com/a/12723330/4561887 and my answer too:
# https://stackoverflow.com/a/58479867/4561887
echo "Floating point math demos:"
echo "$(bc <<< "${time_sec}/2")"                    # scale=0 (the default)
echo "$(bc <<< "${time_sec}/2.5 + 1.7")"            # scale=0 (the default)
echo "$(bc <<< "scale=0; ${time_sec}/2")"           # scale=0
echo "$(bc <<< "scale=0; ${time_sec}/2.5 + 1.7")"   # scale=0
echo "$(bc <<< "scale=20; ${time_sec}/2")"          # scale=20
echo "$(bc <<< "scale=20; ${time_sec}/2.5 + 1.7")"  # scale=20
echo ""

# 2. With whole integer numbers via bash "arithmetic expansion".
# See my answer: https://stackoverflow.com/a/71567705/4561887
echo "Integer math demos:"
echo $((time_sec_rounded/2))
echo $((time_sec_rounded/2 + 5))
echo $((time_sec_rounded - time_ms_rounded))
echo ""




# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./timestamps_with_rounding_truncating_and_math.sh
#       == Printed as-is ==
#       time_sec = 1657683163.093838727
#       time_ms  = 1657683163093.838727000
#       time_us  = 1657683163093838.727000000
#       time_ns  = 1657683163093838727.000000000
#
#       == Pretty-printed with aligned decimals and appropriate number of decimals ==
#       time_sec =           1657683163.093838727
#       time_ms  =        1657683163093.838727
#       time_us  =     1657683163093838.727
#       time_ns  =  1657683163093838727
#
#       time_sec_rounded = 1657683163
#       time_ms_rounded  = 1657683163094
#       time_us_rounded  = 1657683163093839
#       time_ns_rounded  = 1657683163093838727
#
#       time_sec_truncated = 1657683163
#       time_ms_truncated  = 1657683163093
#       time_us_truncated  = 1657683163093838
#       time_ns_truncated  = 1657683163093838727
#
#       Floating point math demos:
#       828841581
#       663073266.7
#       828841581
#       663073266.7
#       828841581.54691936350000000000
#       663073266.93753549080000000000
#
#       Integer math demos:
#       828841581
#       828841586
#       -1656025479931


