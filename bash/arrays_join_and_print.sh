#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Feb. 2022

# Learn to join multiple bash arrays into one; ie: append one bash array onto another

# Run command:
#       ./arrays_join_and_print.sh

# References:
# 1. array_practice.sh
# 1. See also: array_pass_as_bash_parameter.sh
# 1. array_slicing_demo.sh
#   1. [my answer on bash array slicing] https://unix.stackexchange.com/a/664956/114401

# Function to print all elements of an array.
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

# Build and print a few arrays

array1=()
array1+=("one")
array1+=("two")
array1+=("three")

array2=("four" "five" "six" "seven" "eight")

array3=("twelve" "thirteen")

echo "array1:"
print_array "${array1[@]}"
echo "array2:"
print_array "${array2[@]}"
echo "array3:"
print_array "${array3[@]}"


# Now join some together to show how

echo "array4 is array1 + array2:"
array4=("${array1[@]}" "${array2[@]}")
print_array "${array4[@]}"

echo "array5 is array1 + array2 + array3:"
array5=("${array1[@]}" "${array2[@]}" "${array3[@]}")
print_array "${array5[@]}"

# Now do some array slicing as well, as you join arrays into a new array
# - For help on array slicing, see:
#   1. array_slicing_demo.sh
#       1. my answer here: https://unix.stackexchange.com/a/664956/114401
#   1. array_pass_as_bash_parameter.sh

echo "array6 is (elements 1-2 [indices 0-1] of array1) + (elements 3-5 [indices 2-4] array2)" \
     "+ (element 2 [index 1] of array3):"
echo '- Remember, slicing format is `${array[@]:starting_index:length}`, and indices are **zero-based**.'
array6=("${array1[@]:0:2}" "${array2[@]:2:3}" "${array3[@]:1:1}")
print_array "${array6[@]}"


# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./arrays_join_and_print.sh
#       array1:
#           one
#           two
#           three
#       array2:
#           four
#           five
#           six
#           seven
#           eight
#       array3:
#           twelve
#           thirteen
#       array4 is array1 + array2:
#           one
#           two
#           three
#           four
#           five
#           six
#           seven
#           eight
#       array5 is array1 + array2 + array3:
#           one
#           two
#           three
#           four
#           five
#           six
#           seven
#           eight
#           twelve
#           thirteen
#       array6 is (elements 1-2 [indices 0-1] of array1) + (elements 3-5 [indices 2-4] array2) + (element 2 [index 1] of array3):
#       - Remember, slicing format is `${array[@]:starting_index:length}`, and indices are **zero-based**.
#           one
#           two
#           six
#           seven
#           eight
#           thirteen
