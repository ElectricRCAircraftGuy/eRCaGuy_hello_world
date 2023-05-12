#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 12 May 2023
#
# This is a **floating point** math library to allow basic floating point math, easily, in Bash.
# Import it with `. path/to/floating_point_math.sh`
#
# STATUS: Done and works perfectly!

# keywords to easily grep or ripgrep in this repo for this program and what it teaches
#
# KEYWORDS:

# Check this script with:
#
##      shellcheck bash/floating_point_math.sh
#
# Run command:
#
#       bash/floating_point_math.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/floating_point_math.sh

# References:
# 1. The outline of this file -
#    https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/hello_world_best.sh
# 1. ***** [my answer] How to do floating point calculations in bash -
#    https://stackoverflow.com/a/58479867/4561887
# 1. [my answer] Math in bash: how to use all bash operators (`+`, `-`, `/`, `*`, `**`, `&`, `&&`,
#    `<<`, etc.), and arithmetic expansion, in bash - https://stackoverflow.com/a/71567705/4561887
# 1. [my answer] More array slicing examples in bash -
#    https://unix.stackexchange.com/a/664956/114401
# 1. How to show zero before decimal point in bc? - https://unix.stackexchange.com/a/197902/114401


RETURN_CODE_SUCCESS=0
RETURN_CODE_ERROR=1

SCALE=10  # decimal digit precision to use in `bc`

# Add all arguments and output the result
# Ex:
#       # result is 1.1 + 2.1 + 3.1 + 4.1 = 10.4
#       add 1.1 2.1 3.1 4.1
add() {
    result="$1"
    for number in "${@:2}"; do
        result="$(echo "scale=$SCALE; $result+$number" | bc -l)"
    done

    echo "$result"
}

# Subtract all numbers from the number in the **first argument**
# Ex:
#       # result is 1.1 - 2.1 - 3.1 - 4.1 = -8.2
#       subtract 1.1 2.1 3.1 4.1
subtract() {
    result="$1"
    for number in "${@:2}"; do
        result="$(echo "scale=$SCALE; $result-$number" | bc -l)"
    done

    echo "$result"
}

# Multiply all numbers together, using floating point math
# Ex:
#       # result is 1.1*2.1*3.1*4.1 = 29.3601
#       multiply 1.1 2.1 3.1 4.1
multiply() {
    result="$1"
    for number in "${@:2}"; do
        result="$(echo "scale=$SCALE; $result*$number" | bc -l)"
    done

    echo "$result"
}

# Divide all numbers, using floating point math
# Ex:
#       # result is 1.1/2.1/3.1/4.1 = approx. 0.041212394
#       divide 1.1 2.1 3.1 4.1
divide() {
    result="$1"
    for number in "${@:2}"; do
        result="$(echo "scale=$SCALE; $result/$number" | bc -l)"
    done

    echo "$result"
}

# Aliases to make 3-letter versions of all of the functions above

sub() {
    subtract "$@"
}

mul() {
    multiply "$@"
}

div() {
    divide "$@"
}

# Assert that the two input argument strings are equal, and exit if they are not
assert_eq() {
    if [ "$1" != "$2" ]; then
        echo "Error: assertion failed. Arguments not equal! arg1 = $1; arg2 = $2"
        echo "Exiting."
        exit $RETURN_CODE_ERROR
    fi
}

# Run some unit tests of the functions found herein
_test() {
    printf "%s\n\n" "Running tests."

    # add

    printf "%s\n" "Running 'add 1.1 2.1 3.1 4.1'"
    result="$(add 1.1 2.1 3.1 4.1)"
    printf "%s\n\n" "result = $result"
    assert_eq "$result" "10.4"

    printf "%s\n" "Running 'add 100.2 923.2334'"
    result="$(add 100.2 923.2334)"
    printf "%s\n\n" "result = $result"
    assert_eq "$result" "1023.4334"

    # subtract

    printf "%s\n" "Running 'subtract 1.1 2.1 3.1 4.1'"
    result="$(subtract 1.1 2.1 3.1 4.1)"
    printf "%s\n\n" "result = $result"
    assert_eq "$result" "-8.2"

    printf "%s\n" "Running 'sub 1.1 2.1 3.1 4.1'"
    result="$(sub 1.1 2.1 3.1 4.1)"
    printf "%s\n\n" "result = $result"
    assert_eq "$result" "-8.2"

    # multiply

    printf "%s\n" "Running 'multiply 1.1 2.1 3.1 4.1'"
    result="$(multiply 1.1 2.1 3.1 4.1)"
    printf "%s\n\n" "result = $result"
    assert_eq "$result" "29.3601"

    printf "%s\n" "Running 'mul 1.1 2.1 3.1 4.1'"
    result="$(mul 1.1 2.1 3.1 4.1)"
    printf "%s\n\n" "result = $result"
    assert_eq "$result" "29.3601"

    # divide

    printf "%s\n" "Running 'divide 1.1 2.1 3.1 4.1'"
    result="$(divide 1.1 2.1 3.1 4.1)"
    printf "%s\n\n" "result = $result"
    assert_eq "$result" ".0412123936"

    printf "%s\n" "Running 'div 1.1 2.1 3.1 4.1'"
    result="$(div 1.1 2.1 3.1 4.1)"
    printf "%s\n\n" "result = $result"
    assert_eq "$result" ".0412123936"


    echo "All tests passed!"
}

main() {
    _test
}

# Determine if the script is being sourced or executed (run).
# See:
# 1. "eRCaGuy_hello_world/bash/if__name__==__main___check_if_sourced_or_executed_best.sh"
# 1. My answer: https://stackoverflow.com/a/70662116/4561887
if [ "${BASH_SOURCE[0]}" = "$0" ]; then
    # This script is being run.
    __name__="__main__"
else
    # This script is being sourced.
    __name__="__source__"
fi

# Only run `main` if this script is being **run**, NOT sourced (imported).
# - See my answer: https://stackoverflow.com/a/70662116/4561887
if [ "$__name__" = "__main__" ]; then
    main "$@"
fi


# SAMPLE OUTPUT:
#
# 1) WHEN RUN (it prints "Running main.")
#
#       eRCaGuy_hello_world$ time bash/floating_point_math.sh
#       Running tests.
#
#       Running 'add 1.1 2.1 3.1 4.1'
#       result = 10.4
#
#       Running 'add 100.2 923.2334'
#       result = 1023.4334
#
#       Running 'subtract 1.1 2.1 3.1 4.1'
#       result = -8.2
#
#       Running 'sub 1.1 2.1 3.1 4.1'
#       result = -8.2
#
#       Running 'multiply 1.1 2.1 3.1 4.1'
#       result = 29.3601
#
#       Running 'mul 1.1 2.1 3.1 4.1'
#       result = 29.3601
#
#       Running 'divide 1.1 2.1 3.1 4.1'
#       result = .0412123936
#
#       Running 'div 1.1 2.1 3.1 4.1'
#       result = .0412123936
#
#       All tests passed!
#
#       real    0m0.057s
#       user    0m0.058s
#       sys 0m0.011s
#
#
# 2) WHEN SOURCED (no output, but it brings in all functions herein so you can use them!)
#
#       eRCaGuy_hello_world$ . bash/floating_point_math.sh
#       eRCaGuy_hello_world$ div 13.1838 10.110832
#       1.3039283018
#       eRCaGuy_hello_world$ mul 1.2 3 2
#       7.2
