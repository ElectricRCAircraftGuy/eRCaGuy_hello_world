#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# check_if_sourced_or_executed.sh

# By Gabriel Staples
# First written: 10 Jan. 2022

# Test if this bash script is being sourced or executed. This could be useful, for instance, to only
# run certain things if the file is being executed, but to NOT run them if this file is being
# sourced, since sourcing this script might be just to pull in some functions from it which the
# script doing the sourcing might want to use from this script!
#
# This would be akin to using the `if __name__ == "__main__":` check in Python.

# References:
# 1. Python's `if __name__ == "__main__":` check -
#    https://stackoverflow.com/questions/419163/what-does-if-name-main-do
# 1. [my own answer on what it means to "source" a file]
#    https://stackoverflow.com/questions/15474650/unix-what-is-the-difference-between-source-and-export/62626515#62626515
# 1. detect if script is being sourced:
#    https://stackoverflow.com/questions/2683279/how-to-detect-if-a-script-is-being-sourced
# 1. How to define a shell script to be sourced not run:
#    https://unix.stackexchange.com/questions/424492/how-to-define-a-shell-script-to-be-sourced-not-run
# 1. What is the bash equivalent to Python's `if __name__ == '__main__'`?:
#    https://stackoverflow.com/questions/29966449/what-is-the-bash-equivalent-to-pythons-if-name-main
#
# My own answers where I've posted all or some of this code:
# 1. *****+ How to detect if a script is being sourced: https://stackoverflow.com/a/70662049/4561887
# 1. https://stackoverflow.com/a/70662116/4561887
# 1. https://unix.stackexchange.com/a/685857/114401

# Test run:
# For all cases, first do:
#           cd path/to/eRCaGuy_hello_world
# 1. Execute the script in 2 ways:
#   A. As an executable script
#           ./bash/check_if_sourced_or_executed.sh
#   B. By calling the bash interpreter
#           bash ./bash/check_if_sourced_or_executed.sh
# 2. Source the script in 2 ways:
#   A. Bash source call
#           source ./bash/check_if_sourced_or_executed.sh
#   B. (Recommended) POSIX-compliant source call
#           . ./bash/check_if_sourced_or_executed.sh


main() {
    echo "Running main function."

    # put your code here

    echo -e "\nTOTAL TIME TO RUN main func:"
}

# Set the global variable `run` to "true" if the script is being executed and `main` should run, and
# set `run` to "false" otherwise--ex: if the script is being sourced in order to import functions
# from the script, but `main` should NOT run.
run_check() {
    # DEMONSTRATE A FEW DIFFERENT TECHNIQUES

    echo "Technique 1 (can be placed anywhere):"
    echo "  See: https://unix.stackexchange.com/a/424495/114401"
    if [ "${BASH_SOURCE[0]}" -ef "$0" ]; then
        echo "  This script is being EXECUTED."
        run="true"
    else
        echo "  This script is being SOURCED."
    fi


    echo "Technique 2 [MY 2ND FAVORITE] (can be placed anywhere):"
    echo "  Modified from: https://stackoverflow.com/a/29967433/4561887"
    if [ "${BASH_SOURCE[0]}" == "$0" ]; then
        echo "  This script is being EXECUTED."
        run="true"
    else
        echo "  This script is being SOURCED."
    fi

    echo "Technique 3 (requires another line which MUST be **outside** all functions):"
    echo "  Modified from: https://stackoverflow.com/a/28776166/4561887"
    if [ "$script_is_being_executed" == "true" ]; then
        echo "  This script is being EXECUTED."
        run="true"
    else
        echo "  This script is being SOURCED."
    fi


    echo "Technique 4 [MY 1ST FAVORITE] (MUST be **inside** a function):"
    echo "  Modified from: https://stackoverflow.com/a/14706745/4561887"
    echo "  and https://unix.stackexchange.com/a/424552/114401"
    if [ "${FUNCNAME[-1]}" == "main" ]; then
        echo "  This script is being EXECUTED."
        run="true"
    elif [ "${FUNCNAME[-1]}" == "source" ]; then
        echo "  This script is being SOURCED."
    else
        echo "  ERROR: THIS TECHNIQUE IS BROKEN"
    fi

}

# ==================================================================================================
# Main program entry point
# ==================================================================================================

# Only run main function if this file is being executed, NOT sourced.

# For Technique 3. This `return` statement MUST be called at a top-level scope, outside of all
# functions, in order to work! See their detailed explanation here for how it works:
# https://stackoverflow.com/a/28776166/4561887
(return 0 2>/dev/null) && script_is_being_executed="false" || script_is_being_executed="true"

run="false"
run_check
if [ "$run" == "true" ]; then
    time main "$@"
fi



# SAMPLE OUTPUT:
#
#       ----------------------------------------------------------------------------------
#
#       eRCaGuy_hello_world$ ./bash/check_if_sourced_or_executed.sh
#       Technique 1 (can be placed anywhere):
#         See: https://unix.stackexchange.com/a/424495/114401
#         This script is being EXECUTED.
#       Technique 2 [MY 2ND FAVORITE] (can be placed anywhere):
#         Modified from: https://stackoverflow.com/a/29967433/4561887
#         This script is being EXECUTED.
#       Technique 3 (requires another line which MUST be **outside** all functions):
#         Modified from: https://stackoverflow.com/a/28776166/4561887
#         This script is being EXECUTED.
#       Technique 4 [MY 1ST FAVORITE] (MUST be **inside** a function):
#         Modified from: https://stackoverflow.com/a/14706745/4561887
#         and https://unix.stackexchange.com/a/424552/114401
#         This script is being EXECUTED.
#       Running main function.
#
#       TOTAL TIME TO RUN main func:
#
#       real    0m0.000s
#       user    0m0.000s
#       sys 0m0.000s
#
#       ----------------------------------------------------------------------------------
#
#       eRCaGuy_hello_world$ bash ./bash/check_if_sourced_or_executed.sh
#       Technique 1 (can be placed anywhere):
#         See: https://unix.stackexchange.com/a/424495/114401
#         This script is being EXECUTED.
#       Technique 2 [MY 2ND FAVORITE] (can be placed anywhere):
#         Modified from: https://stackoverflow.com/a/29967433/4561887
#         This script is being EXECUTED.
#       Technique 3 (requires another line which MUST be **outside** all functions):
#         Modified from: https://stackoverflow.com/a/28776166/4561887
#         This script is being EXECUTED.
#       Technique 4 [MY 1ST FAVORITE] (MUST be **inside** a function):
#         Modified from: https://stackoverflow.com/a/14706745/4561887
#         and https://unix.stackexchange.com/a/424552/114401
#         This script is being EXECUTED.
#       Running main function.
#
#       TOTAL TIME TO RUN main func:
#
#       real    0m0.000s
#       user    0m0.000s
#       sys 0m0.000s
#
#       ----------------------------------------------------------------------------------
#
#       eRCaGuy_hello_world$ source ./bash/check_if_sourced_or_executed.sh
#       Technique 1 (can be placed anywhere):
#         See: https://unix.stackexchange.com/a/424495/114401
#         This script is being SOURCED.
#       Technique 2 [MY 2ND FAVORITE] (can be placed anywhere):
#         Modified from: https://stackoverflow.com/a/29967433/4561887
#         This script is being SOURCED.
#       Technique 3 (requires another line which MUST be **outside** all functions):
#         Modified from: https://stackoverflow.com/a/28776166/4561887
#         This script is being SOURCED.
#       Technique 4 [MY 1ST FAVORITE] (MUST be **inside** a function):
#         Modified from: https://stackoverflow.com/a/14706745/4561887
#         and https://unix.stackexchange.com/a/424552/114401
#         This script is being SOURCED.
#
#       ----------------------------------------------------------------------------------
#
#       eRCaGuy_hello_world$ . ./bash/check_if_sourced_or_executed.sh
#       Technique 1 (can be placed anywhere):
#         See: https://unix.stackexchange.com/a/424495/114401
#         This script is being SOURCED.
#       Technique 2 [MY 2ND FAVORITE] (can be placed anywhere):
#         Modified from: https://stackoverflow.com/a/29967433/4561887
#         This script is being SOURCED.
#       Technique 3 (requires another line which MUST be **outside** all functions):
#         Modified from: https://stackoverflow.com/a/28776166/4561887
#         This script is being SOURCED.
#       Technique 4 [MY 1ST FAVORITE] (MUST be **inside** a function):
#         Modified from: https://stackoverflow.com/a/14706745/4561887
#         and https://unix.stackexchange.com/a/424552/114401
#         This script is being SOURCED.
