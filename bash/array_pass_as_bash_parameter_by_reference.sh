#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 9 Feb. 2022

# Practice passing regular bash "indexed" arrays, as well as bash "associative arrays" (ie:
# "hash tables", "dictionaries", or "unordered maps") _by reference_ as parameters to other bash
# functions.

# Run command:
#       ./array_pass_as_bash_parameter_by_reference.sh

# References:
# 1. BIG THANKS to @Todd Lehman, whose answer I modified to get the code below. See:
#    https://stackoverflow.com/a/55170447/4561887
# 1. [my answer with this code] https://stackoverflow.com/a/71060036/4561887
    # 1. See also the several referenced underneath this answer!


# 1. Regular "indexed" array

function foo1 {
    # declare a local **reference variable** (hence `-n`) named `data_ref`
    # which is a reference to the value stored in the first parameter
    # passed in
    local -n data_ref="$1"
    echo "${data_ref[0]}"
    echo "${data_ref[1]}"
    echo ""
}

# declare a regular bash "indexed" array
declare -a data1
data1+=("Fred Flintstone")
data1+=("Barney Rubble")
foo1 data1


# 2. Associative array

function foo2 {
    # declare a local **reference variable** (hence `-n`) named `data_ref`
    # which is a reference to the value stored in the first parameter
    # passed in
    local -n data_ref="$1"
    echo "${data_ref["a"]}"
    echo "${data_ref["b"]}"
}

# declare a bash associative array
declare -A data2
data2["a"]="Fred Flintstone"
data2["b"]="Barney Rubble"
foo2 data2



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world$ bash/array_pass_as_bash_parameter_by_reference.sh
#       Fred Flintstone
#       Barney Rubble
#
#       Fred Flintstone
#       Barney Rubble
