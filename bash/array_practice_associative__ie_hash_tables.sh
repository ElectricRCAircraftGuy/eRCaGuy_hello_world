#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 9 Feb. 2022

# Demonstrate how to use "associative arrays" in bash. These are also known generically as "hash
# tables". In C++, they are `std::unordered_map<>` templated container objects. In Python they
# are "dictionaries", or "dicts", for short.

# Run command:
#       ./array_practice_associative__ie_hash_tables.sh

# References:
# 1. *****+ EXCELLENT "Bash associative array examples" and tutorial:
#    https://www.artificialworlds.net/blog/2012/10/17/bash-associative-array-examples/   <========= MAIN SOURCE! =========
# 1. My previous usage of associative arrays approximately here:
#   1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/sync_git_repo_from_pc1_to_pc2.sh#L301-L367
#   1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/home/.sync_git_repo_private#L74-L84
# 1. ***** https://stackoverflow.com/questions/1494178/how-to-define-hash-tables-in-bash
# 1. https://stackoverflow.com/questions/688849/associative-arrays-in-shell-scripts

# See also:
# Regular bash arrays:
#   1. array_practice.sh
#   1. array_pass_as_bash_parameter.sh
#   1. arrays_join_and_print.sh
#   1. array_slicing_demo.sh

echo "Main source for this tutorial: https://www.artificialworlds.net/blog/2012/10/17/bash-associative-array-examples/"
echo ""
echo "Using associative arrays (AKA: hash tables / dictionaries / unordered maps) in bash requires version 4+."
echo "Your bash version is:"
echo "-------------"
echo "$(bash --version)"
echo "-------------"
echo ""


# # this will take some effort to get right; figure it out later
# # See my normal array answer as a start: https://stackoverflow.com/a/70855715/4561887
# printAssociativeArray() {
#     array="$1"
#     for key in "${!array[@]}"; do
#         echo "  $key = ${array["$key"]}"
#     done
# }


echo "EXAMPLE 1: explicitly create an associative array"
# See bash associative array tutorial here!:
# https://www.artificialworlds.net/blog/2012/10/17/bash-associative-array-examples/
# See also `help declare`. NB: `-g` makes these variables global; otherwise they would be
# local to this function only!
# - Note: use `unset` to delete a variable. Ex: `unset array1`.
declare -gA array1
array1["A"]="A is for apple"
array1["B"]="B is for booger"
array1["C"]="C is for candy"

# print the number of elements in the associative array
array1_len="${#array1[@]}"
echo "array1_len = $array1_len"
echo ""

# loop through all keys (in order to also obtain the values)
echo "array1 key:value pairs"
for key in "${!array1[@]}"; do
    value="${array1["$key"]}"
    echo "$key: $value"
done
echo ""

# loop through just values
echo "array1 values only"
for value in "${array1[@]}"; do
    echo "$value"
done
echo ""


echo "EXAMPLE 2: implicitly create an associative array in global scope (apparently bash 4.2+" \
     "only), per the tutorial above."

echo "Uhhh...implicit declaration actually does NOT seem to work! Comment out the 'declare'" \
     "statement below and this fails to run!"
declare -gA array2
array2["statement 1"]="how are you?"
echo "array2 key:value pairs"
for key in "${!array2[@]}"; do
    value="${array2["$key"]}"
    echo "$key: $value"
done
echo ""


echo "======================="

# delete (unset) a key:value pair from the array
unset array1["B"]

# print the number of elements in the associative array
array1_len="${#array1[@]}"
echo "array1_len = $array1_len"
echo ""

# loop through all keys (in order to also obtain the values)
echo "array1 key:value pairs"
for key in "${!array1[@]}"; do
    value="${array1["$key"]}"
    echo "$key: $value"
done
echo ""


echo "======================="

# delete/clear (unset) the whole associative array!
unset array1

# print the number of elements in the associative array
array1_len="${#array1[@]}"
echo "array1_len = $array1_len"
echo ""

# loop through all keys (in order to also obtain the values)
echo "array1 key:value pairs"
for key in "${!array1[@]}"; do
    value="${array1["$key"]}"
    echo "$key: $value"
done
echo ""


echo "======================="

# fill an array all at once




# SAMPLE OUTPUT:
#

