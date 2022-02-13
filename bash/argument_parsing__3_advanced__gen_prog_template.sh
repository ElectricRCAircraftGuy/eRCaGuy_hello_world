#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Gabriel Staples
# Feb. 2022

# STATUS: It works! Done and ready for use!

# - Demonstrate advanced argument parsing in bash.
# - Use this program as a general program template for most bash programs I write, especially for
#   large and sophisticated bash programs.

# Basic run command:
#       ./argument_parsing__3_advanced__gen_prog_template.sh
# Test commands:
#       ./argument_parsing__3_advanced__gen_prog_template.sh -h
#   Then run the "EXAMPLE USAGES" commands shown in the help menu! Ex:
#       ./argument_parsing__3_advanced__gen_prog_template.sh -h
#       ./argument_parsing__3_advanced__gen_prog_template.sh --help
#       ./argument_parsing__3_advanced__gen_prog_template.sh -a 'hello world'
#       ./argument_parsing__3_advanced__gen_prog_template.sh --arga 'hello world' --argb 'Nice to meet you!' --argc 789
#       ./argument_parsing__3_advanced__gen_prog_template.sh -a 'hello world' -b 'Nice to meet you!' -c 789
#       ./argument_parsing__3_advanced__gen_prog_template.sh --argc 789 one two
#       ./argument_parsing__3_advanced__gen_prog_template.sh one --argc 789 two
#       ./argument_parsing__3_advanced__gen_prog_template.sh one two --argc 789

# INSTALLATION INSTRUCTIONS:
# 1. Create a symlink in ~/bin to this script so you can run it from anywhere.
#       cd /path/to/here
#       mkdir -p ~/bin
#       ln -si "${PWD}/argument_parsing__3_advanced__gen_prog_template.sh" ~/bin/arg_parse_demo     # required
#       ln -si "${PWD}/argument_parsing__3_advanced__gen_prog_template.sh" ~/bin/gs_arg_parse_demo  # optional; replace "gs" with your initials
# 2. Log out and log back in if using Ubuntu with a default ~/.profile file which automatically
#    adds ~/bin to your PATH. This will cause ~/bin to be automatically added to your path.
#    Otherwise, manually add it to your path with this command. You can add it to your
#    ~/.bashrc file as well:
#       PATH="$HOME/bin:$PATH"
# 3. Now you can use this command directly anywhere you like in any of these ways:
#   1. `arg_parse_demo`
#   2. `gs_arg_parse_demo`

# References:
# 1. *****++ For advanced argument parsing help and demo, see: https://stackoverflow.com/a/14203146/4561887
# 1. Examples of real programs where I've done this myself before:
#   1. *****+ https://github.com/ElectricRCAircraftGuy/PDF2SearchablePDF/blob/master/pdf2searchablepdf.sh#L150-L223
#   1. *****+ https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/rg_replace.sh#L175-L356
#      NB: I used this "rg_replace.sh" program as a starting point for this program below!
# 1. [my answer] How to detect if a script is being sourced or executed:
#    https://stackoverflow.com/a/70662049/4561887
#   1. check_if_sourced_or_executed.sh

# TODO:
# 1.


RETURN_CODE_SUCCESS=0
RETURN_CODE_ERROR=1

VERSION="0.1.0"
AUTHOR="Gabriel Staples"

DEBUG_PRINTS_ON="true"  # "true" or "false"; can also be passed in as an option: `-d` or `--debug`

SCRIPT_NAME="$(basename "$0")"
VERSION_SHORT_STR="'$SCRIPT_NAME' version $VERSION"
VERSION_LONG_STR="\
$VERSION_SHORT_STR
Author = $AUTHOR
See '$SCRIPT_NAME -h' for more info.
"

HELP_STR="\
$VERSION_SHORT_STR

This is a general program template intended to be used for medium to large-sized bash programs. Just
copy-paste it as a starting point for your program. Be sure to cite me and any other sources you
use to write your program. Please provide a URL in your program to link back to this file in my
eRCaGuy_hello_world repo.

USAGE
    $SCRIPT_NAME [options] [positional_arg1] [positional_arg2]

OPTIONS
    -h, -?, --help
        Print help menu
    -v, --version
        Print version information.
    --run_tests
        Run unit tests.
    -d, --debug
        Turn on debug prints.

    -a <arg>, --arga <arg>
        Pass in custom argument a.
    -b <arg>, --argb <arg>
        Pass in custom argument b.
    -c <arg>, --argc <arg>
        Pass in custom argument c.

EXAMPLE USAGES:

    $SCRIPT_NAME -h
        Print help menu.
    $SCRIPT_NAME --help
        Print help menu.
    $SCRIPT_NAME -a 'hello world'
        Pass in 'hello world' for custom argument a.
    $SCRIPT_NAME --arga 'hello world' --argb 'Nice to meet you!' --argc 789
        Pass in custom arguments a, b, and c.
    $SCRIPT_NAME -a 'hello world' -b 'Nice to meet you!' -c 789
        Same as above.
    $SCRIPT_NAME --argc 789 one two
        Pass in '789' as custom argument c, 'one' as posiitonal_arg1, and 'two' as positional_arg2
    $SCRIPT_NAME one --argc 789 two
        Same as above, just in a different order.
    $SCRIPT_NAME one two --argc 789
        Same as above, just in a different order again.
    $SCRIPT_NAME -a 'hello world' one two -b 'Nice to meet you!' -c 789 three
        Pass in custom arguments a, b, and c, as well as 'one' for 'posiitonal_arg1', 'two' for
        'positional_arg2', and 'three' as a 3rd positional argument which is unused but will also
        get captured into the 'POSITIONAL_ARGS_ARRAY'.
    $SCRIPT_NAME -a 'some invalid argument' one two -b 'Nice to meet you!' -c 789 three
        Same as above, except make argument a be invalid so the code will exit early and print an
        error about it.

This program is part of eRCaGuy_dotfiles: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles
by Gabriel Staples.
"

# A function to do echo-style debug prints only if `DEBUG_PRINTS_ON` is set to "true".
echo_debug() {
    if [ "$DEBUG_PRINTS_ON" = "true" ]; then
        printf "%s" "DEBUG: "
        echo "$@"
    fi
}

echo_error() {
    printf "%s" "ERROR: "
    echo "$@"
}

# A function to do printf-style debug prints only if `DEBUG_PRINTS_ON` is set to "true".
printf_debug() {
    if [ "$DEBUG_PRINTS_ON" = "true" ]; then
        printf "%s" "DEBUG: "
        printf "$@"
    fi
}

print_help() {
    echo "$HELP_STR" | less -RFX
}

print_version() {
    echo "$VERSION_LONG_STR"
}

# Unit Tests
# Cmd: `<this_script_name> --run_tests`
run_tests() {
    echo "Running unit tests"
    # Fill this in. Ex: call `my_unit_tests.sh`
}

# Print a regular bash "indexed" array
# See:
# 1. my answer: https://stackoverflow.com/a/71060036/4561887 and
# 1. my answer: https://stackoverflow.com/a/71060913/4561887
print_array() {
    local -n array_reference="$1"
    for element in "${array_reference[@]}"; do
        echo "  $element"
    done
}

# Print a regular bash "indexed" array only if `DEBUG_PRINTS_ON` is set to "true".
print_array_debug() {
    local -n array_reference="$1"
    for element in "${array_reference[@]}"; do
        echo_debug "  $element"
    done
}

parse_args() {
    # For advanced argument parsing help and demo, see:
    # https://stackoverflow.com/a/14203146/4561887

    if [ $# -eq 0 ]; then
        echo "No arguments supplied"
        print_help
        exit $RETURN_CODE_ERROR
    fi

    # All possible input arguments we expect to see.

    # Note: pre-declaring these variables like this is NOT required in bash. This is optional, and
    # is only done for human-readability and "aesthetic" purposes, to remind us that all of these
    # variables 1) **exist**, and 2) **are empty by default** if not written to below.
    ARGA=""
    ARGB=""
    ARGC=""
    POSITIONAL_ARG1=""
    POSITIONAL_ARG2=""

    ALL_ARGS_ARRAY=("$@")  # See: https://stackoverflow.com/a/70572787/4561887
    POSITIONAL_ARGS_ARRAY=()
    while [ $# -gt 0 ]; do
        arg="$1"
        # get first letter of `arg`; see: https://stackoverflow.com/a/10218528/4561887
        # This is a form of bash "array slicing", treating the string like an array of chars,
        # so see also my answer about array slicing here:
        # https://unix.stackexchange.com/a/664956/114401
        first_letter="${arg:0:1}"

        case $arg in
            # Help menu
            "-h"|"-?"|"--help")
                print_help
                exit $RETURN_CODE_SUCCESS
                ;;
            # Version
            "-v"|"--version")
                print_version
                exit $RETURN_CODE_SUCCESS
                ;;
            # Unit tests
            "--run_tests")
                run_tests
                exit $RETURN_CODE_SUCCESS
                ;;
            # Debug prints on
            "-d"|"--debug")
                echo_debug "Debug on."
                DEBUG_PRINTS_ON="true"
                shift # past argument
                ;;
            # Custom argument a
            "-a"|"--arga")
                echo_debug "arga passed in"
                ARGA="$2"
                shift # past argument (`$1`)
                shift # past value (`$2`)
                ;;
            # Custom argument b
            "-b"|"--argb")
                echo_debug "argb passed in"
                ARGB="$2"
                shift # past argument (`$1`)
                shift # past value (`$2`)
                ;;
            # Custom argument c
            "-c"|"--argc")
                echo_debug "argc passed in"
                ARGC="$2"
                shift # past argument (`$1`)
                shift # past value (`$2`)
                ;;
            # All positional args (ie: unmatched in the switch cases above)
            *)
                # error out for any unexpected options passed in
                if [ "$first_letter" = "-" ]; then
                    echo_error "Invalid optional argument ('$1'). See help menu for valid options."
                    exit $RETURN_CODE_ERROR
                fi

                POSITIONAL_ARGS_ARRAY+=("$1")  # save positional arg into array
                shift # past argument (`$1`)
                ;;
        esac
    done

    POSITIONAL_ARG1="${POSITIONAL_ARGS_ARRAY[0]}"
    POSITIONAL_ARG2="${POSITIONAL_ARGS_ARRAY[1]}"

    # Do debug prints of all argument stats

    all_args_array_len="${#ALL_ARGS_ARRAY[@]}"
    echo_debug "Total number of args = $all_args_array_len"
    echo_debug "ALL_ARGS_ARRAY contains:"
    print_array_debug ALL_ARGS_ARRAY
    echo_debug ""

    positional_args_array_len="${#POSITIONAL_ARGS_ARRAY[@]}"
    echo_debug "Number of positional args = $positional_args_array_len"
    echo_debug "POSITIONAL_ARGS_ARRAY contains:"
    print_array_debug POSITIONAL_ARGS_ARRAY
    echo_debug ""
    echo_debug "POSITIONAL_ARG1 = '$POSITIONAL_ARG1'"
    echo_debug "POSITIONAL_ARG2 = '$POSITIONAL_ARG2'"
    echo_debug ""
} # parse_args

# Check arguments and print errors and exit if any critical ones are invalid
check_if_arguments_are_valid() {
    arga_is_ok="false"
    argb_is_ok="false"
    argc_is_ok="false"

    # Here are some made-up examples for demonstration purposes

    # Example 1: exit if args are invalid

    if [ "$ARGA" = "some invalid argument" ]; then
        echo_error "ARGA is invalid. See help menu for valid options."
        exit $RETURN_CODE_ERROR
    fi

    if [ "$ARGB" = "some invalid argument" ]; then
        echo_error "ARGB is invalid. See help menu for valid options."
        exit $RETURN_CODE_ERROR
    fi

    if [ "$ARGC" = "some invalid argument" ]; then
        echo_error "ARGC is invalid. See help menu for valid options."
        exit $RETURN_CODE_ERROR
    fi

    # Example 2: set some flags if args are invalid

    if [ "$ARGA" != "some invalid argument" ]; then
        arga_is_ok="true"
    fi

    if [ "$ARGB" != "some invalid argument" ]; then
        argb_is_ok="true"
    fi

    if [ "$ARGC" != "some invalid argument" ]; then
        argc_is_ok="true"
    fi
}

# Exit if the last command failed.
exit_if_last_command_failed() {
    error_code="$?"
    if [ "$error_code" -ne 0 ]; then
        echo_error "Last command failed with error code $error_code."
        exit $RETURN_CODE_ERROR
    fi
}

# Print and run the passed-in command
# USAGE:
#       cmd_array=(ls -a -l -F /)
#       print_and_run_cmd cmd_array
# See:
# 1. My answer on how to pass regular "indexed" and associative arrays by reference:
#    https://stackoverflow.com/a/71060036/4561887 and
# 1. My answer on how to pass associative arrays: https://stackoverflow.com/a/71060913/4561887
print_and_run_cmd() {
    local -n array_reference="$1"
    echo "Running cmd:  ${cmd_array[@]}"
    # run the command by calling all elements of the command array at once
    ${cmd_array[@]}
}

main() {
    echo_debug "Running 'main'."

    check_if_arguments_are_valid

    # Debug print some arguments to prove that parsed arguments are globally available here
    echo_debug "ARGA = '$ARGA'"
    echo_debug "ARGB = '$ARGB'"
    echo_debug "ARGC = '$ARGC'"

    # Run whatever commands you want to here, to do what your program needs to do. Frequently,
    # we want to also print our command we are running before we run it, so that the user can
    # easily copy/paste it to re-run just that part if they want to after the script runs.
    # It can also be used to more-easily debug the program. Here are some examples of
    # storing a command into an array, and then printing and running it.

    echo "== Example command 1: =="
    cmd_array=(ls -a -l -F /)
    print_and_run_cmd cmd_array
    exit_if_last_command_failed
    echo ""

    echo "== Example command 2: =="
    cmd_array=(df -h)
    print_and_run_cmd cmd_array
    exit_if_last_command_failed
    echo ""

    # echo "== Example command 3: =="
    # # Doesn't work; need to figure out how to make this work with spaces
    # cmd_array=(ls -1 "$HOME/temp/some folder with spaces")
    # print_and_run_cmd cmd_array
    # exit_if_last_command_failed
    # echo ""
} # main

# Set the global variable `run` to "true" if the script is being **executed** (not sourced) and
# `main` should run, and set `run` to "false" otherwise. One might source this script but intend
# NOT to run it if they wanted to import functions from the script.
# See:
# 1. my answer: https://stackoverflow.com/a/70662049/4561887
# 1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/check_if_sourced_or_executed.sh
run_check() {
    # This is akin to `if __name__ == "__main__":` in Python.
    if [ "${FUNCNAME[-1]}" == "main" ]; then
        # This script is being EXECUTED, not sourced
        run="true"
    fi
}

# ----------------------------------------------------------------------------------------------------------------------
# Main program entry point
# ----------------------------------------------------------------------------------------------------------------------

# Only run main function if this file is being executed, NOT sourced.
run="false"
run_check
if [ "$run" == "true" ]; then
    parse_args "$@"
    time main
fi
