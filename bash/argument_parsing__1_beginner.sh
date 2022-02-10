#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Feb. 2022

# Do basic parsing and printing of all input arguments from the input `@` regular "indexed" bash
# array.

# Run command:
#       ./argument_parsing__1_beginner.sh a b c d e f g h i j k l m

# References:
# 1. [my answer] bash array slicing: https://unix.stackexchange.com/a/664956/114401



i=0
echo "${i}: Basic argument parsing demo"
((i++))
printf "%s\n\n" "${i}: Basic argument parsing demo"

# --------------------------------------------------------------------------------------------------
# Technique 1: range-based for loop with manual index tracking; print with `echo`
# --------------------------------------------------------------------------------------------------
i=1  # notice we start at index 0 here, but 1 below. That is because this style of for loop
     # skips the 0 index, which is the name of the command itself, and instead starts with the 1
     # index, which is the first argument.
for arg in "${@}"; do
    echo "  index $i: $arg"
    ((i++))
done
echo ""

# --------------------------------------------------------------------------------------------------
# Technique 2: bash indexed for loop; print with `printf`
# --------------------------------------------------------------------------------------------------
# Since we start with index 0 here, we will see the index 0 of the input argument also get called,
# which is the name of the executable (command) itself!
for (( i=0; i<="$#"; i++ )); do
    # For array slicing, see my answer: https://unix.stackexchange.com/a/664956/114401
    printf "  %s\n"  "index $i: ${@:$i:1}"
done
echo ""

# --------------------------------------------------------------------------------------------------
# Technique 3: manually print all arguments
# --------------------------------------------------------------------------------------------------
printf "  %s\n"  "index  0: $0"
printf "  %s\n"  "index  1: $1"
printf "  %s\n"  "index  2: $2"
printf "  %s\n"  "index  3: $3"
printf "  %s\n"  "index  4: $4"
printf "  %s\n"  "index  5: $5"
printf "  %s\n"  "index  6: $6"
printf "  %s\n"  "index  7: $7"
printf "  %s\n"  "index  8: $8"
printf "  %s\n"  "index  9: $9"
printf "  %s\n"  "index 10: ${10}"
printf "  %s\n"  "index 11: ${11}"
printf "  %s\n"  "index 12: ${12}"
printf "  %s\n"  "index 13: ${13}"
printf "  %s\n"  "index 14: ${14}"
printf "  %s\n"  "index 15: ${15}"
echo ""




# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world$ bash/argument_parsing__1_beginner.sh a b c d e f g h i j k l m
#       0: Basic argument parsing demo
#       1: Basic argument parsing demo
#
#         index 1: a
#         index 2: b
#         index 3: c
#         index 4: d
#         index 5: e
#         index 6: f
#         index 7: g
#         index 8: h
#         index 9: i
#         index 10: j
#         index 11: k
#         index 12: l
#         index 13: m
#
#         index 0: bash/argument_parsing__1_beginner.sh
#         index 1: a
#         index 2: b
#         index 3: c
#         index 4: d
#         index 5: e
#         index 6: f
#         index 7: g
#         index 8: h
#         index 9: i
#         index 10: j
#         index 11: k
#         index 12: l
#         index 13: m
#
#         index  0: bash/argument_parsing__1_beginner.sh
#         index  1: a
#         index  2: b
#         index  3: c
#         index  4: d
#         index  5: e
#         index  6: f
#         index  7: g
#         index  8: h
#         index  9: i
#         index 10: j
#         index 11: k
#         index 12: l
#         index 13: m
#         index 14:
#         index 15:
#
