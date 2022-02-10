#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Learn to pass bash arrays as a parameter to a function which requires multiple parameters

# Run command:
#       ./array_pass_as_bash_parameter_1_indexed.sh

# References:
# 1. [MY ANSWER ON THIS] https://stackoverflow.com/a/70855715/4561887
# 1. array_practice.sh
# 1. arrays_join_and_print.sh
# 1. How to pass array as an argument to a function in Bash:
#    https://stackoverflow.com/q/16461656/4561887
# 1. ***** Passing arrays as parameters in bash:
#    https://stackoverflow.com/q/1063347/4561887
# 1. [my answer on bash array slicing] https://unix.stackexchange.com/a/664956/114401


# EXAMPLE 1: pass a single array only, with NO OTHER PARAMETERS, to a bash function.
#
# Function to print all elements of an array.
# Example usage, where `my_array` is a bash array:
#       my_array=()
#       my_array+=("one")
#       my_array+=("two")
#       my_array+=("three")
#       print_array "${my_array[@]}"
print_one_array() {
    # echo "print_one_array:"

    for element in "$@"; do
        printf "    %s\n" "$element"
    done
}

# EXAMPLE 2: pass two arrays to a single bash function
#
# Usage:
#       # General usage (notice length MUST come first to be able to parse the args!)
#       print_two_arrays array1_len array1 array2_len array2
#       # Example
#       print_two_arrays "${#array1[@]}" "${array1[@]}" "${#array2[@]}" "${array2[@]}"
print_two_arrays() {
    # echo "print_two_arrays:"

    # Array slicing demos:
    # See my answer: https://unix.stackexchange.com/a/664956/114401

    # # Print all input args
    # echo "All args to 'print_two_arrays':"
    # for element in "$@"; do
    #     printf "    %s\n" "$element"
    # done
    # echo ""

    # Print all input args
    echo "All args to 'print_two_arrays':"
    print_one_array "$@"

    # Slice some input args to select a subset
    # for element in "${@:3:5}"; do
    #     printf "    %s\n" "$element"
    # done
    # echo ""

    # Slice with variables as the slice parameters
    # num1=3
    # num2=5
    # for element in "${@:$num1:$num2}"; do
    #     printf "    %s\n" "$element"
    # done
    # echo ""

    i=1

    # Read array1_len
    array1_len="${@:$i:1}"
    # echo "$array1_len"  # debugging
    ((i++))

    # Read array1 (note that the parenthesis around the content to the right of
    # the equals sign below turn the sliced array output into a new bash array)
    array1=("${@:$i:$array1_len}")
    ((i += $array1_len))

    # Read array2_len
    array2_len="${@:$i:1}"
    # echo "$array2_len"  # debugging
    ((i++))

    # Read array2
    array2=("${@:$i:$array2_len}")
    ((i += $array2_len))

    # Print the two arrays
    echo "array1:"
    print_one_array "${array1[@]}"
    echo "array2:"
    print_one_array "${array2[@]}"
}

# EXAMPLE 3: pass two arrays plus some extra args after that to a single bash function
#
# Usage:
#       # General usage (notice length MUST come first to be able to parse the args!)
#       print_two_arrays_plus_extra_args array1_len array1 array2_len array2 extra_arg1 extra_arg2
#       # Example
#       print_two_arrays_plus_extra_args "${#array1[@]}" "${array1[@]}" "${#array2[@]}" "${array2[@]}" "hello" "world"
print_two_arrays_plus_extra_args() {
    # echo "print_two_arrays_plus_extra_args:"

    i=1

    # Read array1_len
    array1_len="${@:$i:1}"
    ((i++))

    # Read array1
    array1=("${@:$i:$array1_len}")
    ((i += $array1_len))

    # Read array2_len
    array2_len="${@:$i:1}"
    ((i++))

    # Read array2
    array2=("${@:$i:$array2_len}")
    ((i += $array2_len))

    # You can now read the extra arguments all at once and gather them into a
    # new array like this:
    extra_args_array=("${@:$i}")

    # OR you can read the extra arguments individually into their own variables
    # one-by-one like this
    extra_arg1="${@:$i:1}"
    ((i++))
    extra_arg2="${@:$i:1}"
    ((i++))

    # Print the output
    echo "array1:"
    print_one_array "${array1[@]}"
    echo "array2:"
    print_one_array "${array2[@]}"
    echo "extra_arg1 = $extra_arg1"
    echo "extra_arg2 = $extra_arg2"
    echo "extra_args_array:"
    print_one_array "${extra_args_array[@]}"
}


# Build and print a few arrays

array1=()
array1+=("one")
array1+=("two")
array1+=("three")

array2=("four" "five" "six" "seven" "eight")


echo "Printing array1"
print_one_array "${array1[@]}"
echo ""

echo "Printing array1 and array2"
print_two_arrays "${#array1[@]}" "${array1[@]}" "${#array2[@]}" "${array2[@]}"
echo ""

echo "Printing array1 and array2 plus some extra args"
print_two_arrays_plus_extra_args "${#array1[@]}" "${array1[@]}" "${#array2[@]}" "${array2[@]}" "hello" "world"
echo ""



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./array_pass_as_bash_parameter_1_indexed.sh
#       Printing array1
#           one
#           two
#           three
#
#       Printing array1 and array2
#       All args to 'print_two_arrays':
#           3
#           one
#           two
#           three
#           5
#           four
#           five
#           six
#           seven
#           eight
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
#
#       Printing array1 and array2 plus some extra args
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
#       extra_arg1 = hello
#       extra_arg2 = world
#       extra_args_array:
#           hello
#           world
#
