#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Run command:
#       ./array_practice.sh

# References:
# 1. *****[VERY IMPORTANT AND USEFUL ANSWER!] https://stackoverflow.com/a/70572787/4561887
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


# Now use an array as the input arguments to another command! For this demo, let the command be
# `ls`. Here is an array of arguments to this command:

my_args_array=("-a" "-l" "-F" "some path")

echo "========================================================================"
echo 'OPTION 1: pass the contents of the array as arguments to our command \
via the input array, "$@", which we set from our custom array'
echo "========================================================================"
# See: https://stackoverflow.com/a/70572787/4561887

# First, show what is in the magic input args array, `"$@"`:
echo '$@ = '"$@"
echo '$1 = '"$1"
echo '$2 = '"$2"
echo '$3 = '"$3"
echo '$4 = '"$4"
# Now, set it to what's in `my_args_array`
set -- "${my_args_array[@]}"
# And prove it is set to this
echo '$@ = '"$@"
echo '$1 = '"$1"
echo '$2 = '"$2"
echo '$3 = '"$3"
echo '$4 = '"$4"

# Now call the cmd with these arguments!
ls "$@"

echo "========================================================================"
echo 'OPTION 2: pass the contents of the array as arguments to our command \
via our custom array directly, "${my_args_array[@]}"'
echo "========================================================================"

ls "${my_args_array[@]}"



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world$ bash/array_practice.sh
#
#       Number of elements = 3
#       my_array contains:
#           element 1
#           element 2
#           element 3
#
#       Number of elements = 3
#       my_array2 contains:
#           element 1
#           element 2
#           element 3
#       ========================================================================
#       OPTION 1: pass the contents of the array as arguments to our command \
#       via the input array, "$@", which we set from our custom array
#       ========================================================================
#       $@ =
#       $1 =
#       $2 =
#       $3 =
#       $4 =
#       $@ = -a -l -F some path
#       $1 = -a
#       $2 = -l
#       $3 = -F
#       $4 = some path
#       ls: cannot access 'some path': No such file or directory
#       ========================================================================
#       OPTION 2: pass the contents of the array as arguments to our command \
#       via our custom array directly, "${my_args_array[@]}"
#       ========================================================================
#       ls: cannot access 'some path': No such file or directory
