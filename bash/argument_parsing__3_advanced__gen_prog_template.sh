#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# STATUS: work-in-progress; not yet ready for use.

# - Demonstrate advanced argument parsing in bash.
# - Use this program as a general program template for most bash programs I write, especially for
#   large and sophisticated bash programs.

# Basic run command:
#       ./argument_parsing__3_advanced__gen_prog_template.sh

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

# Test commands:
#       arg_parse_demo -h

# TODO:
# 1.


RETURN_CODE_SUCCESS=0
RETURN_CODE_ERROR=1

VERSION="0.1.0"
AUTHOR="Gabriel Staples"

DEBUG_PRINTS_ON="false"  # "true" or "false"; can also be passed in as an option: `-d` or `--debug`

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
    $SCRIPT_NAME [options]

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

parse_args() {
    # For advanced argument parsing help and demo, see:
    # https://stackoverflow.com/a/14203146/4561887

    num_args="$#"
    if [ "$num_args" -eq 0 ]; then
        echo "No arguments supplied"
        print_help
        exit $RETURN_CODE_ERROR
    fi

    all_args_array=("$@")  # See: https://stackoverflow.com/a/70572787/4561887
    regex=""  # regular expression search pattern to look for
    replacement_text=""
    overwrite_file="false"
    paths_array=()  # array of paths to search in for the `regex` pattern
    ripgrep_args_array=()  # arguments to always be passed to ripgrep
    stats_on="false"

    while [ $# -gt 0 ]; do
        arg="$1"
        # first letter of `arg`; see: https://stackoverflow.com/a/10218528/4561887
        first_letter="${arg:0:1}"

        case $arg in
            # --------------------------------------------------------------------------------------
            # 1. Parse options handled by this rgr wrapper
            # --------------------------------------------------------------------------------------

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
                DEBUG_PRINTS_ON="true"
                ripgrep_args_array+=("--debug")  # also forward this arg to ripgrep
                shift # past argument
                ;;
            # Replacement text; perform in-place to overwrite file
            "-R"|"--Replace")
                overwrite_file="true"
                echo "ACTUAL CONTENT WILL BE REPLACED IN YOUR FILESYSTEM."
                echo "If you'd like to do a dry-run instead, cancel the program and run with '-r' instead of '-R'."

                # See: https://stackoverflow.com/a/226724/4561887
                read -p "Are you sure you'd like to continue? (Y or y to continue; any other key or just Enter to exit) " \
                    yes_or_no
                case "$yes_or_no" in
                    [Yy]* )
                        # nothing to do
                        ;;
                    *)
                        exit $RETURN_CODE_SUCCESS
                        ;;
                esac

                if [ $# -gt 1 ]; then
                    replacement_text="$2"
                    ripgrep_args_array+=("-r" "$replacement_text")
                    shift # past argument
                    shift # past value
                else
                    echo "ERROR: Missing value for argument '-R' or '--Replace'."
                    exit $RETURN_CODE_ERROR
                fi
                ;;
            # Ripgrep Statistics on
            "--stats")
                stats_on="true"
                shift # past argument
                ;;

            # --------------------------------------------------------------------------------------
            # 2. Parse Ripgrep options
            # --------------------------------------------------------------------------------------

            # All ripgrep arguments which require a value after the option (see `rg -h`)
            "-A"|"--after-context"| \
            "-B"|"--before-context"| \
            "--color"| \
            "--colors"| \
            "-C"|"--context"| \
            "--context-separator"| \
            "--dfa-size-limit"| \
            "-E"|"--encoding"| \
            "--engine"| \
            "-f"|"--file"| \
            "-g"|"--glob"| \
            "--iglob"| \
            "--ignore-file"| \
            "-M"|"--max-columns"| \
            "-m"|"--max-count"| \
            "--max-depth"| \
            "--max-filesize"| \
            "--path-separator"| \
            "--pre"| \
            "--pre-glob"| \
            "--regex-size-limit"| \
            "-e"|"--regexp"| \
            "-r"|"--replace"| \
            "--sort"| \
            "--sortr"| \
            "-j"|"--threads"| \
            "-t"|"--type"| \
            "--type-add"| \
            "--type-clear"| \
            "-T"|"--type-not")
                if [ $# -gt 1 ]; then
                    ripgrep_args_array+=("$1")
                    ripgrep_args_array+=("$2")
                    shift # past argument
                    shift # past value
                else
                    echo "ERROR: Missing value for Ripgrep argument."
                    exit $RETURN_CODE_ERROR
                fi
                ;;


            # All other '-' or '--' options (ie: unmatched in the switch cases above)
            -*|--*)
                ripgrep_args_array+=("$1")
                shift # past argument
                ;;

            # --------------------------------------------------------------------------------------
            # 3. Parse positional arguments (regex_search_pattern, and paths)
            # --------------------------------------------------------------------------------------

            # All positional args (ie: unmatched in the switch cases above)
            *)
                # The first positional arg is the regex search pattern
                if [ -z "$regex" ]; then
                    regex="$1"
                # All other positional args are paths to search in
                else
                    paths_array+=("$1")
                fi

                shift # past argument
                ;;
        esac
    done

    # Print argument stats

    all_args_array_len=${#all_args_array[@]}
    echo_debug "Total number of args = $all_args_array_len"
    echo_debug "all_args_array contains:"
    for path in "${all_args_array[@]}"; do
        echo_debug "    $path"
    done

    echo_debug "regex = '$regex'"
    echo_debug "replacement_text = '$replacement_text'"
    echo_debug "overwrite_file = '$overwrite_file'"

    paths_array_len=${#paths_array[@]}
    echo_debug "Number of paths = $paths_array_len"
    echo_debug "paths_array contains:"
    for path in "${paths_array[@]}"; do
        echo_debug "    $path"
    done

    ripgrep_args_array_len=${#ripgrep_args_array[@]}
    echo_debug "Number of general ripgrep args = $ripgrep_args_array_len"
    echo_debug "ripgrep_args_array contains:"
    for arg in "${ripgrep_args_array[@]}"; do
        echo_debug "    $arg"
    done
} # parse_args

main() {
    echo_debug "Running 'main'."

    if [ "$overwrite_file" == "false" ]; then
        # There are no special things this wrapper program needs to do, so just run regular ripgrep!
        rg "${all_args_array[@]}"
        exit $RETURN_CODE_SUCCESS
    fi


    # otherwise, run the special find-and-replace in place

    NUM_STATS_LINES=9  # number of extra lines printed at the end by the ripgrep `--stats` option

    args_array=("${ripgrep_args_array[@]}" "--stats" "-l" "$regex" "${paths_array[@]}")

    filenames_list_and_stats="$(rg "${args_array[@]}")"
    filenames_list="$(printf "%s" "$filenames_list_and_stats" | head -n -$NUM_STATS_LINES)"
    filenames_stats="$(printf "%s" "$filenames_list_and_stats" | tail -n $NUM_STATS_LINES)"

    echo ""
    # echo "TOTAL SUMMARY:"
    # printf "${COLOR_MGN}%s${COLOR_OFF}" "${filenames_list}"
    # echo "$filenames_stats"
    # echo ""

    # Convert list of files to array of files.
    # See:
    # 1. "eRCaGuy_dotfiles/useful_scripts/find_and_replace.sh" for an example of this
    # 1. ***** https://stackoverflow.com/a/24628676/4561887
    SAVEIFS=$IFS   # Save current IFS (Internal Field Separator)
    IFS=$'\n'      # Change IFS (Internal Field Separator) to newline char
    filenames_array=($filenames_list) # split long string into array, separating by IFS (newline chars)
    IFS=$SAVEIFS   # Restore IFS

    # Now do the replacement one file at a time, using `rg` only! (no need for `sed`)

    args_array_base=("${ripgrep_args_array[@]}" "--passthru" "$regex")
    args_array_base_with_color=("${ripgrep_args_array[@]}" "--stats" "--color" "always" \
        "-n" "$regex")

    for filename in "${filenames_array[@]}"; do
        echo -e "${COLOR_MGN}${filename}${COLOR_OFF}"

        args_array_final=("${args_array_base[@]}" "$filename")
        args_array_final_with_color=("${args_array_base_with_color[@]}" "$filename")

        file_changes_and_stats_in_color="$(rg "${args_array_final_with_color[@]}")"
        file_changes_in_color="$(printf "%s" "$file_changes_and_stats_in_color" | head -n -$NUM_STATS_LINES)"

        file_contents="$(rg "${args_array_final[@]}")"

        if [ "$stats_on" == "true" ]; then
            printf "%s\n\n" "$file_changes_and_stats_in_color"
        else
            printf "%s\n\n" "$file_changes_in_color"
        fi

        # WARNING WARNING WARNING! This is the line that makes the actual changes to your
        # file system!
        printf "%s" "$file_contents" > "$filename"
    done

    # print the summary output one more time so that if the output is really long the user doesn't
    # have to scroll up forever to see it
    filenames_array_len=${#filenames_array[@]}
    if [ "$filenames_array_len" -gt 1 ] && [ "$stats_on" == "true" ]; then
        echo ""
        printf "${COLOR_MGN}%s${COLOR_OFF}" "${filenames_list}"
        echo "$filenames_stats"
    fi
} # main

# ----------------------------------------------------------------------------------------------------------------------
# Main program entry point
# ----------------------------------------------------------------------------------------------------------------------

parse_args "$@"
time main
# main
