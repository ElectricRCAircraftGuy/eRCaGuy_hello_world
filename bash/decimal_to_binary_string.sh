#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 22 Mar. 2022

# Convert a decimal number to a binary string with a certain number of digits in
# it.

# Status: done! It works!

# keywords: bash binary base-2 conversion decimal to binary

# Check this script with: `shellcheck decimal_to_binary_string.sh`

# Run command:
#       ./decimal_to_binary_string.sh

# References:

# 1. [my Q--where I'll post this code below as an answer!] How to make `bc`
#    output a desired number of base-2 binary digits:
#    https://stackoverflow.com/q/71568169/4561887
# 1. [my answer] How to use all bash operators, and arithmetic expansion, in
#    bash: https://stackoverflow.com/a/71567705/4561887


# Convert a decimal number to a binary number with a minimum specified number of
# binary digits
# Usage:
#       decimal_to_binary <number_in> [min_num_binary_digits]
decimal_to_binary() {
    num_in="$1"
    min_digits="$2"
    if [ -z "$min_chars" ]; then
        min_digits=8  # set a default
    fi

    binary_str="$(echo "obase=2; 46" | bc)"

    num_chars="${#binary_str}"
    # echo "num_chars = $num_chars" # debugging
    num_zeros_to_add_as_prefix=$((min_digits - num_chars))
    # echo "num_zeros_to_add_as_prefix = $num_zeros_to_add_as_prefix" # debugging
    zeros=""
    for (( i=0; i<"$num_zeros_to_add_as_prefix"; i++ )); do
        zeros="${zeros}0"  # append another zero
    done

    binary_str="${zeros}${binary_str}"
    echo "$binary_str"
}

# Example usage
num=46
num_in_binary="$(decimal_to_binary "$num" 8)"
echo "$num_in_binary"

# ================= UPDATE: DON'T USE MY FUNCTION ABOVE! ======================
# DO THIS INSTEAD!
# Source: David Rankin: https://stackoverflow.com/a/71568608/4561887
# =============================================================================
printf "%08d\n" $(echo "obase=2; $num" | bc)



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./decimal_to_binary_string.sh
#       00101110
#       00101110

