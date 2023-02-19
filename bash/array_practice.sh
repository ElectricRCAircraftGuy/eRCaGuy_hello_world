#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Run command:
#       ./array_practice.sh

# References:
# 1. *****[VERY IMPORTANT AND USEFUL ANSWER!] https://stackoverflow.com/a/70572787/4561887
# 1. my own memory
# 1. https://github.com/ElectricRCAircraftGuy/PDF2SearchablePDF/blob/master/pdf2searchablepdf.sh
# 1. back_up_all_input_args.sh
# 1. combining (merging) arrays in bash: https://stackoverflow.com/a/38579195/4561887
# 1. *****EXCELLENT BASH ARRAYS TUTORIAL!
#    https://opensource.com/article/18/5/you-dont-know-bash-intro-bash-arrays
# 1. [my own answer] bash slicing and array indexing demo:
#    https://unix.stackexchange.com/a/664956/114401


# Test multiple ways to build and print regular bash "indexed" arrays

# ----------------------------------------
# -1. See if you can have empty arrays (arrays of size 0 elements)
# Answer: yes! Run this example.
# ----------------------------------------
a1=("")  # array of size 1 element, which is an empty string
a2=(a b "${a1[@]}" c)
echo "${a2[@]}"
echo "number of elements = ${#a2[@]}"  # 4

a1=()  # array of size 0 elements
a2=(a b "${a1[@]}" c)
echo "${a2[@]}"
echo "number of elements = ${#a2[@]}"  # 3; there you have it! You CAN have arrays of zero elements!

echo ""

# ----------------------------------------
# 0. Array splicing (AKA: joining, combining, merging, etc.)
# NB: Bash does *not* have nested nor multidimensional arrays, so this is simply *combining* arrays!
# See: https://stackoverflow.com/a/12317983/4561887
# ----------------------------------------

a1=(a b c d)
a2=(d e f g)
a3=(1 2 3 "${a1[@]}" 4 5 "${a2[@]}" 6 7)
echo "${a1[@]}"  # output: a b c d
echo "${a2[@]}"  # output: d e f g
echo "${a3[@]}"  # output: 1 2 3 a b c d 4 5 d e f g 6 7
echo ""

# ----------------------------------------
# 1. Build up one element at-a-time
# ----------------------------------------

my_array=()
my_array+=("element 1")
my_array+=("element 2")
my_array+=("element 3")

my_array_len=${#my_array[@]}
echo "Number of elements = $my_array_len"
echo "my_array contains:"
for i in "${my_array[@]}"; do
    echo "    $i"
done
echo ""

# ----------------------------------------
# 2. Build up all at once
# ----------------------------------------

my_array2=("element 1" "element 2" "element 3")

my_array2_len=${#my_array2[@]}
echo "Number of elements = $my_array2_len"

echo "my_array2 contains (using loop technique 1: range-based for loop):"
for element in "${my_array2[@]}"; do
    echo "    $element"
done
echo ""

# Alternative `for` loop! Iterate using indices to obtain the array elements, instead of iterating
# over elements directly using the "range-based for loop" as shown above.
echo "my_array2 contains (using loop technique 2: C-style index-based for loop):"
echo "- See: https://stackoverflow.com/a/356154/4561887 and "
echo "  [better] https://www.cyberciti.biz/faq/bash-for-loop-array/"
echo "  and [my answer where I used this] https://stackoverflow.com/a/70670852/4561887"
for (( i=0; i<"$my_array2_len"; i++ )); do
    echo '    ${my_array2['"$i"']} = '"${my_array2[$i]}"
done
echo ""

# ----------------------------------------
# 3. Build the array all at once, but use a different format from above,
# specifying the elements on multiple lines.
# ----------------------------------------

my_array3=(
    "element A"
    "element B"
    "element C"
    "element D"
)

# yet another way to print the array: print using the array's **indices**
echo "Number of elements = ${#my_array3[@]}"
echo "my_array3 contains (by printing via its indices):"
for i in "${!my_array3[@]}"; do
    echo "    ${my_array3["$i"]}"
done
echo ""


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


echo ""
echo "========================================================================"
echo "array summation"
echo "========================================================================"

array1=("1" "2" "3" "4")
array2=("5" "6" "7" "8")
array3=("${array1[@]}" "${array2[@]}")  # see: https://stackoverflow.com/a/38579195/4561887

array3_len=${#array3[@]}
echo ""
echo "Number of elements = $array3_len"
echo "array3 contains:"
for i in "${array3[@]}"; do
    echo "    $i"
done

# slightly more-complicated example with multiple arrays plus some more individual elements added;
# this is very useful for building up an arguments array to pass to a command!
array4=("${array1[@]}" "100" "101" "${array2[@]}" "102")
array4_len=${#array4[@]}
echo ""
echo "Number of elements = $array4_len"
echo "array4 contains:"
for i in "${array4[@]}"; do
    echo "    $i"
done


echo ""
echo "========================================================================"
echo "array indexing (into array4)"
echo "========================================================================"
# - See this tutorial for help:
#   https://opensource.com/article/18/5/you-dont-know-bash-intro-bash-arrays
# - and my own answer on bash array indexing and slicing too:
#   https://unix.stackexchange.com/a/664956/114401

echo "index  0: ${array4[0]}"
echo "index  1: ${array4[1]}"
echo "index  2: ${array4[2]}"
echo "index  3: ${array4[3]}"
echo "index  4: ${array4[4]}"
echo "index  5: ${array4[5]}"
echo "index  6: ${array4[6]}"
echo "index  7: ${array4[7]}"
echo "index  8: ${array4[8]}"
echo "index  9: ${array4[9]}"
echo "index 10: ${array4[10]}"
echo "index 11: ${array4[11]}"  # intentionally out-of-bounds
echo ""
echo "index  -1 ( 1st element from the right): ${array4[-1]}"
echo "index  -2 ( 2nd element from the right): ${array4[-2]}"
echo "index  -3 ( 3rd element from the right): ${array4[-3]}"
echo "index  -4 ( 4th element from the right): ${array4[-4]}"
echo "index  -5 ( 5th element from the right): ${array4[-5]}"
echo "index  -6 ( 6th element from the right): ${array4[-6]}"
echo "index  -7 ( 7th element from the right): ${array4[-7]}"
echo "index  -8 ( 8th element from the right): ${array4[-8]}"
echo "index  -9 ( 9th element from the right): ${array4[-9]}"
echo "index -10 (10th element from the right): ${array4[-10]}"
echo "index -11 (11th element from the right): ${array4[-11]}"
echo "index -12 (12th element from the right): ${array4[-12]}"  # intentionally out-of-bounds
echo ""
echo "all elements: ${array4[@]}"
echo ""
echo "all array indices: ${!array4[@]}"
echo ""
echo "array size (number of elements): ${#array4[@]}"
echo ""
echo "Bash array slicing:"
echo '${array4[@]:3:5} (starting at index 3, retrieve 5 elements): '"${array4[@]:3:5}"
echo ""



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./array_practice.sh
#       Number of elements = 3
#       my_array contains:
#           element 1
#           element 2
#           element 3
#
#       Number of elements = 3
#       my_array2 contains (using loop technique 1: range-based for loop):
#           element 1
#           element 2
#           element 3
#
#       my_array2 contains (using loop technique 2: C-style index-based for loop):
#       - See: https://stackoverflow.com/a/356154/4561887 and
#         [better] https://www.cyberciti.biz/faq/bash-for-loop-array/
#         and [my answer where I used this] https://stackoverflow.com/a/70670852/4561887
#           ${my_array2[0]} = element 1
#           ${my_array2[1]} = element 2
#           ${my_array2[2]} = element 3
#
#       Number of elements = 4
#       my_array3 contains (by printing via its indices):
#           element A
#           element B
#           element C
#           element D
#
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
#
#       ========================================================================
#       array summation
#       ========================================================================
#
#       Number of elements = 8
#       array3 contains:
#           1
#           2
#           3
#           4
#           5
#           6
#           7
#           8
#
#       Number of elements = 11
#       array4 contains:
#           1
#           2
#           3
#           4
#           100
#           101
#           5
#           6
#           7
#           8
#           102
#
#       ========================================================================
#       array indexing (into array4)
#       ========================================================================
#       index  0: 1
#       index  1: 2
#       index  2: 3
#       index  3: 4
#       index  4: 100
#       index  5: 101
#       index  6: 5
#       index  7: 6
#       index  8: 7
#       index  9: 8
#       index 10: 102
#       index 11:
#
#       index  -1 ( 1st element from the right): 102
#       index  -2 ( 2nd element from the right): 8
#       index  -3 ( 3rd element from the right): 7
#       index  -4 ( 4th element from the right): 6
#       index  -5 ( 5th element from the right): 5
#       index  -6 ( 6th element from the right): 101
#       index  -7 ( 7th element from the right): 100
#       index  -8 ( 8th element from the right): 4
#       index  -9 ( 9th element from the right): 3
#       index -10 (10th element from the right): 2
#       index -11 (11th element from the right): 1
#       ./array_practice.sh: line 185: array4: bad array subscript
#       index -12 (12th element from the right):
#
#       all elements: 1 2 3 4 100 101 5 6 7 8 102
#
#       all array indices: 0 1 2 3 4 5 6 7 8 9 10
#
#       array size (number of elements): 11
#
#       Bash array slicing:
#       ${array4[@]:3:5} (starting at index 3, retrieve 5 elements): 4 100 101 5 6
#






