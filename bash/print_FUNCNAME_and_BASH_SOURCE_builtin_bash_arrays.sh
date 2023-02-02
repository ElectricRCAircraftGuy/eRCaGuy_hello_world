#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# See what the bash built-in array variable `FUNCNAME` contains when it is inside vs outside a
# function.
#
# Status: done and works!

# keywords: (keywords to easily grep or ripgrep in this repo for this program and what it teaches)

# Check this script with: `shellcheck print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh`

# Run command:
#
#       ./print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#
# Source (import) command to get access to these functions:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . ./print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh

# References:
# 1. What is the bash equivalent to Python's `if __name__ == '__main__'`? -
#    https://stackoverflow.com/q/29966449/4561887
#   1. [my answer] https://stackoverflow.com/a/70662116/4561887
#   1. [my answer] https://stackoverflow.com/a/70662049/4561887
# 1. `man bash`, then search for "FUNCNAME", "main", and "BASH_SOURCE".
# 1. Where I first learned about the `${FUNCNAME[-1]}` trick:
#    @mr.spuratic: https://stackoverflow.com/a/14706745/4561887
#    - he learned it from Dennis Williamson apparently.


echo "==========="
echo '$0 = '"$0"
echo "==========="
echo ""

echo "==========="
echo "FUNCNAME"
echo "==========="

echo "Outside a function:"
echo "  ${FUNCNAME[@]}"
i=0
for element in "${FUNCNAME[@]}"; do
    echo "  $i: $element"
    ((i++))
done

print_FUNCNAME() {
    echo "Inside a function:"
    echo "${FUNCNAME[@]}"
    i=0
    for element in "${FUNCNAME[@]}"; do
        echo "  $i: $element"
        ((i++))
    done
}

print_FUNCNAME
echo ""


echo "==========="
echo "BASH_SOURCE"
echo "==========="

echo "Outside a function:"
echo "  ${BASH_SOURCE[@]}"
i=0
for element in "${BASH_SOURCE[@]}"; do
    echo "  $i: $element"
    ((i++))
done

print_BASH_SOURCE() {
    echo "Inside a function:"
    echo "${BASH_SOURCE[@]}"
    i=0
    for element in "${BASH_SOURCE[@]}"; do
        echo "  $i: $element"
        ((i++))
    done
}

print_BASH_SOURCE
echo ""


# ===============================

get_name() {
    # Get the last element in this bash built-in array to see if this script
    # is being sourced or executed. See `man bash` and search for "FUNCNAME".
    printf "%s" "${FUNCNAME[-1]}"
}

main() {
    echo "Running main."
}

if [ "$(get_name)" = "main" ]; then
    main
fi


# SAMPLE OUTPUT:
#
# 1) WHEN RUN:
#
#       eRCaGuy_hello_world$ bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#       ===========
#       $0 = bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#       ===========
#
#       ===========
#       FUNCNAME
#       ===========
#       Outside a function:
#
#       Inside a function:
#       print_FUNCNAME main
#         0: print_FUNCNAME
#         1: main                   <======= KEY PART TO NOTICE ========
#
#       ===========
#       BASH_SOURCE
#       ===========
#       Outside a function:
#         bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#         0: bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#       Inside a function:
#       bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#         0: bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#         1: bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#
#       Running main.               <======= KEY PART TO NOTICE ========
#
#
# 2) WHEN SOURCED:
#
#       eRCaGuy_hello_world$ . bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#       ===========
#       $0 = /bin/bash
#       ===========
#
#       ===========
#       FUNCNAME
#       ===========
#       Outside a function:
#
#       Inside a function:
#       print_FUNCNAME source
#         0: print_FUNCNAME
#         1: source                 <======= KEY PART TO NOTICE ========
#
#       ===========
#       BASH_SOURCE
#       ===========
#       Outside a function:
#         bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#         0: bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#       Inside a function:
#       bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#         0: bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh
#         1: bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh


