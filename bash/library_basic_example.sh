#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 12 May 2023
#
# This is a really basic, general Bash library template anyone can use.
#
# STATUS: done and works!

# keywords to easily grep or ripgrep in this repo for this program and what it teaches
#
# KEYWORDS:

# Check this script with:
#
##      shellcheck bash/library_basic_example.sh
#
# Run command:
#
#       bash/library_basic_example.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/library_basic_example.sh

# References:
# 1. todo: add the link to where I've posted this on Stack Overflow
# 1.


RETURN_CODE_SUCCESS=0
RETURN_CODE_ERROR=1

# Add your library functions here. Ex:

my_func1() {
    echo "100.1"
}

my_func2() {
    echo "200"
}

my_func3() {
    echo "hello world"
}

# Note: make "private" functions begin with an underscore `_`, like in Python,
# so that users know they are not intended for use outside this library.

# Assert that the two input argument strings are equal, and exit if they are not
_assert_eq() {
    if [ "$1" != "$2" ]; then
        echo "Error: assertion failed. Arguments not equal!"
        echo "  arg1 = $1; arg2 = $2"
        echo "Exiting."
        exit $RETURN_CODE_ERROR
    fi
}

# Run some unit tests of the functions found herein
_test() {
    printf "%s\n\n" "Running tests."

    printf "%s\n" "Running 'my_func1'"
    result="$(my_func1)"
    printf "%s\n\n" "result = $result"
    _assert_eq "$result" "100.1"

    printf "%s\n" "Running 'my_func2'"
    result="$(my_func2)"
    printf "%s\n\n" "result = $result"
    _assert_eq "$result" "200"

    printf "%s\n" "Running 'my_func3'"
    result="$(my_func3)"
    printf "%s\n\n" "result = $result"
    _assert_eq "$result" "hello world"

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

# Code entry point. Only run `main` if this script is being **run**, NOT
# sourced (imported).
# - See my answer: https://stackoverflow.com/a/70662116/4561887
if [ "$__name__" = "__main__" ]; then
    main "$@"
fi


# SAMPLE OUTPUT:
#
# 1) WHEN RUN
#
#       eRCaGuy_hello_world$ bash/library_basic_example.sh
#       Running tests.
#
#       Running 'my_func1'
#       result = 100.1
#
#       Running 'my_func2'
#       result = 200
#
#       Running 'my_func3'
#       result = hello world
#
#       All tests passed!
#
#
#
# 2) WHEN SOURCED (no output, but it brings in all functions herein so you can use them!)
#
#       eRCaGuy_hello_world$ . bash/library_basic_example.sh
#       eRCaGuy_hello_world$ my_func1
#       100.1
#       eRCaGuy_hello_world$ my_func2
#       200
#       eRCaGuy_hello_world$ my_func3
#       hello world
#       eRCaGuy_hello_world$ _test
#       Running tests.
#
#       Running 'my_func1'
#       result = 100.1
#
#       Running 'my_func2'
#       result = 200
#
#       Running 'my_func3'
#       result = hello world
#
#       All tests passed!

