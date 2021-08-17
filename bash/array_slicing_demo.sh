#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Run command:
#       ./array_slicing_demo.sh a b c d e f g h i j k

# References:
# 1. [my own answer] https://unix.stackexchange.com/a/664956/114401


# array slicing basic format 1: grab a certain length starting at a certain
# index
echo "${@:2:5}"
#         │ │
#         │ └────> slice length
#         └──────> slice starting index

# array slicing basic format 2: grab all remaining array elements starting at a
# certain index through to the end
echo "${@:2}"
#         │
#         │
#         └──────> slice starting index

# store a slice from an array into a new array
new_array=("${@:4}")

# print the entire array
echo "new_array = ${new_array[@]}"


a=(one two three four five six)   # define a new array, `a`, with 6 elements
echo "$a"           # print first element of array a
echo "${a}"         # print first element of array a
echo "${a[0]}"      # print first element of array a
echo "${a[1]}"      # print *second* element of array a
echo "${#a[@]}"     # print number of elements in array a
echo "${a[@]:1:3}"  # print 2nd through 4th elements (`two three four`)
echo "${a[@]:1}"    # print 2nd element onward



# SAMPLE OUTPUT:

# eRCaGuy_hello_world/bash$ ./array_slicing_demo.sh a b c d e f g h i j k
# b c d e f
# b c d e f g h i j k
# new_array = d e f g h i j k
# one
# one
# one
# two
# 6
# two three four
# two three four five six

