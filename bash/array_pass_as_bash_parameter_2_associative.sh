#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Learn to pass **associative** bash arrays as a parameter to a function which requires multiple
# parameters. Note: a better way is to pass the arrays by reference! See the other example in the
# references below. This example, however, will intentionally serialize and deserialize the
# associative bash array just to show how we can, for learning and demonstration purposes.

# Run command:
#       ./array_pass_as_bash_parameter.sh

# References:
# 1. *****+ For a BETTER technique, pass them by reference! See:
#    "array_pass_as_bash_parameter_by_reference.sh"  <============ BETTER WAY: PASS BY REFERENCE ==========
# 1. *****+ [my answer with this code!] https://stackoverflow.com/a/71060913/4561887



# Let's create and load up an associative array and print it
declare -A array1
array1["a"]="cat"
array1["b"]="dog"
array1["c"]="mouse"

# --------------------------------------------------------------------------------------------------
# Manually serialize/deserialize the array
# --------------------------------------------------------------------------------------------------

# Print an associative array using manual serialization/deserialization
# Usage:
#       # General form:
#       print_associative_array1 array_length array_keys array_values
#       # Example
#       print_associative_array1 "${#array1[@]}" "${!array1[@]}" "${array1[@]}"
print_associative_array1() {
    i=1

    # read 1st argument, the array length
    array_len="${@:$i:1}"
    ((i++))

    # read all key:value pairs into a new associative array
    declare -A array
    for (( i_key="$i"; i_key<$(($i + "$array_len")); i_key++ )); do
        i_value=$(($i_key + $array_len))
        key="${@:$i_key:1}"
        value="${@:$i_value:1}"
        array["$key"]="$value"
        # debug prints
        # echo "i_key = $i_key"
        # echo "i_value = $i_value"
        # echo "key = $key"
        # echo "value = $value"
    done

    # print the array by iterating through all of the keys now
    for key in "${!array[@]}"; do
        value="${array["$key"]}"
        echo "  $key: $value"
    done
}

echo 'print_associative_array1 "${#array1[@]}" "${!array1[@]}" "${array1[@]}"'
#                         length         indices (keys)    values
print_associative_array1 "${#array1[@]}" "${!array1[@]}" "${array1[@]}"
echo ""


# --------------------------------------------------------------------------------------------------
# [BETTER] Pass the array by reference!
# --------------------------------------------------------------------------------------------------

# Print an associative array by passing the array by reference
# Usage:
#       # General form:
#       print_associative_array2 array
#       # Example
#       print_associative_array2 array1
print_associative_array2() {
    # declare a local **reference variable** (hence `-n`) named `array_reference`
    # which is a reference to the value stored in the first parameter
    # passed in
    local -n array_reference="$1"

    # print the array by iterating through all of the keys now
    for key in "${!array_reference[@]}"; do
        value="${array_reference["$key"]}"
        echo "  $key: $value"
    done
}

echo 'print_associative_array2 array1'
print_associative_array2 array1
echo ""
echo "OR (same thing--quotes don't matter in this case):"
echo 'print_associative_array2 "array1"'
print_associative_array2 "array1"


# --------------------------------------------------------------------------------------------------
# SAMPLE OUTPUT:
# --------------------------------------------------------------------------------------------------
#
#       eRCaGuy_hello_world$ bash/array_pass_as_bash_parameter_2_associative.sh
#       print_associative_array1 "${#array1[@]}" "${!array1[@]}" "${array1[@]}"
#         a: cat
#         b: dog
#         c: mouse
#
#       print_associative_array2 array1
#         a: cat
#         b: dog
#         c: mouse
#
#       OR (same thing--quotes don't matter in this case):
#       print_associative_array2 "array1"
#         a: cat
#         b: dog
#         c: mouse
