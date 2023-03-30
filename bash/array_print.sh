#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 30 Mar. 2023
#
# Print a bash array by passing the array elements by value, and by passing the array name by
# reference.
#
# STATUS: done and works!

# keywords to easily grep or ripgrep in this repo for this program and what it teaches
#
# KEYWORDS: print bash arrays; bash arrays print; print array print arrays print printArrays
# arrayPrint

# Check this script with:
#
##      shellcheck bash/array_print.sh
#
# Run command:
#
#       bash/array_print.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/array_print.sh

# References:
# 1. [my answer with this code] https://stackoverflow.com/a/75891597/4561887
# 1.

# Function to print all elements of an array, **by value.**
# Example usage, where `my_array` is a bash array:
#       my_array=()
#       my_array+=("one")
#       my_array+=("two")
#       my_array+=("three")
#       print_array "${my_array[@]}"
print_array() {
    for element in "$@"; do
        printf "    %s\n" "$element"
    done
}

# Print an array **by reference** instead of by value.
# Example usage, where `my_array` is a bash array:
#       my_array=()
#       my_array+=("one")
#       my_array+=("two")
#       my_array+=("three")
#       print_array "my_array"
print_array2() {
    # declare a local **reference variable** (hence `-n`) named `array_ref`
    # which is a reference to the first parameter passed in
    local -n array_ref="$1"

    for element in "${array_ref[@]}"; do
        printf "    %s\n" "$element"
    done
}

main() {
    echo "Running main."

    array1=()
    array1+=("one")
    array1+=("two")
    array1+=("three")

    echo "array1:"
    print_array "${array1[@]}"
    echo ""
    print_array2 "array1"
    echo ""
    print_array2 array1  # same as above
    echo ""

    array2=(-n -e -E)
    print_array "${array2[@]}"
    echo ""
    print_array2 "array2"
    echo ""

    array3=(8 9 10)
    print_array "${array3[@]}"
    echo ""
    print_array2 "array3"
    echo ""

    array4=(11 12 13)
    print_array "${array4[@]}"
    echo ""
    print_array2 "array4"
    echo ""
    # Print out the attributes and values in array `array4`.
    # See `help declare`.
    declare -p array4
}

# Determine if the script is being sourced or executed (run).
# See:
# 1. "eRCaGuy_hello_world/bash/if__name__==__main___check_if_sourced_or_executed_best.sh"
# 1. My answer: https://stackoverflow.com/a/70662116/4561887
if [ "${BASH_SOURCE[0]}" = "$0" ]; then
    # This script is being run.
    __name__="__main__"
else
    # This script is being sourced.
    __name__="__source__"
fi

# Only run `main` if this script is being **run**, NOT sourced (imported).
# - See my answer: https://stackoverflow.com/a/70662116/4561887
if [ "$__name__" = "__main__" ]; then
    main "$@"
fi


# SAMPLE OUTPUT:
#
# 1) WHEN RUN (it prints "Running main.")
#
#       eRCaGuy_hello_world/bash$ ./array_print.sh
#       Running main.
#       array1:
#           one
#           two
#           three
#
#           one
#           two
#           three
#
#           one
#           two
#           three
#
#           -n
#           -e
#           -E
#
#           -n
#           -e
#           -E
#
#           8
#           9
#           10
#
#           8
#           9
#           10
#
#           11
#           12
#           13
#
#           11
#           12
#           13
#
#       declare -a array4=([0]="11" [1]="12" [2]="13")
#
#
#
# 2) WHEN SOURCED (no output)
#
#       eRCaGuy_hello_world$ . bash/array_print.sh
