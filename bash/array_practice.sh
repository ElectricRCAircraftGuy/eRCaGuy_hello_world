#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Run command:
#       ./array_practice.sh

# References:
# 1. https://stackoverflow.com/a/70572787/4561887
# 1. my own memory
# 1. https://github.com/ElectricRCAircraftGuy/PDF2SearchablePDF/blob/master/pdf2searchablepdf.sh
# 1. back_up_all_input_args.sh


# 1. Build up one element at-a-time

my_array=()
my_array+=("element 1")
my_array+=("element 2")
my_array+=("element 3")

my_array_len=${#my_array[@]}
echo ""
echo "Number of elements = $my_array_len"
echo "my_array contains:"
for i in "${my_array[@]}"; do
    echo "    $i"
done

# 2. Build up all at once

my_array2=("element 1" "element 2" "element 3")

my_array2_len=${#my_array2[@]}
echo ""
echo "Number of elements = $my_array2_len"
echo "my_array2 contains:"
for i in "${my_array2[@]}"; do
    echo "    $i"
done


# Now use an array as the input arguments to another command!

my_array=("-a" "-l" "-F" "some path")

echo "==================================================="
echo 'OPTION 1: via "$@"'
echo "==================================================="
# See: https://stackoverflow.com/a/70572787/4561887

# First, show what is in the magic input args array, `"$@"`:
echo '$@ = '"$@"
echo '$1 = '"$1"
echo '$2 = '"$2"
echo '$3 = '"$3"
echo '$4 = '"$4"
# Now, set it to what's in `my_array`
set -- "${my_array[@]}"
# And prove it is set to this
echo '$@ = '"$@"
echo '$1 = '"$1"
echo '$2 = '"$2"
echo '$3 = '"$3"
echo '$4 = '"$4"

# Now call the cmd with these arguments!
ls "$@"

echo "==================================================="
echo 'OPTION 2: via a manually-built-up command string'
echo "==================================================="

ls "${my_array[@]}"

# args=""
# for i in "${my_array[@]}"; do
#     args="$args \"$i\""
# done
# cmd="ls $args"   # create the full command
# echo "cmd = '$cmd'"  # print the full command
# $cmd               # call the command
# echo "---"
# ls $args





# SAMPLE OUTPUT:

