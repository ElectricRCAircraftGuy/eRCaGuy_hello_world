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
# 1. *****+ [my answer with this code!] TBD

# Print an associative array using
# Usage:
#       # General form:
#       print_associative_array array_length array_keys array_values
#       # Example
#       print_associative_array "${#array1[@]}" "${!array1[@]}" "${array1[@]}"
print_associative_array() {
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

# Let's create and load up an associative array and print it
declare -A array1
array1["a"]="cat"
array1["b"]="dog"
array1["c"]="mouse"

#                         length         indices (keys)    values
print_associative_array "${#array1[@]}" "${!array1[@]}" "${array1[@]}"



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world$ bash/array_pass_as_bash_parameter_2_associative.sh
#         a: cat
#         b: dog
#         c: mouse
