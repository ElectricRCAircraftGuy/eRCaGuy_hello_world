#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Learning about how to store some data in bash
# June 2020
#
# Run cmd: 
#       ./read_arrays.sh


echo "1) gawk:"
# See a little more on awk here: https://en.wikipedia.org/wiki/AWK

item1="
line 2
line 3
line 4
"

echo "$item1" | gawk '

{
    printf "%u: %s\n", FNR, $0
}

'
echo ""


echo "2) bash array:"
# See: https://stackoverflow.com/questions/8880603/loop-through-an-array-of-strings-in-bash/8880633#8880633

declare -a myarray=(
"element 1"
"element 2"
"element 3" "element 4"
)

for element in "${myarray[@]}"
do
    echo "$element"
done

