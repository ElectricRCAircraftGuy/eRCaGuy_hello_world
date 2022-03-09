#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Mar. 2022
# (description)

# Run command:
#       ./hello_world_basic.sh

# References:
# 1. https://stackoverflow.com/questions/71117953/how-to-write-bash-function-to-print-and-run-command-when-the-command-has-argumen/71118445?noredirect=1#comment125716247_71118015

print_and_run_cmd() {
    echo "Running cmd:  $1"
    # echo "$1" > cmd.txt
    # cmd_expanded="$(cat "cmd.txt")"

    echo "printing cmd_array"
    cmd_array=($1)
    cmd_array_fixed=()
    str_cat_on="false"  # set to "true" to turn on string concatenation
    joined_element=""
    for element in "${cmd_array[@]}"; do
        num_chars="${#element}"
        first_char="${element:0:1}"
        last_char="${element:$num_chars-1:1}"

        # echo "  $element; $first_char; $last_char"

        if [ "$first_char" = '"' ] && [ "$last_char" != '"' ]; then
            # echo "ON"
            str_cat_on="true"
        elif [ "$first_char" != '"' ] && [ "$last_char" = '"' ]; then
            # echo "OFF"
            str_cat_on="false"
        fi

        if [ "$str_cat_on" = "true" ]; then
            joined_element
        fi

    done

    # cmd_expanded=
    # echo "   expanded:  $cmd_expanded"

    # # cmd="$(printf "%s" $(eval "$1"))"
    # # echo "$cmd"

    # # cmd_expanded_array=($(eval "$(echo "$1")"))
    # # echo "   expanded:  ${cmd_expanded_array[@]}"
    # eval "$cmd"
}


# WORKS!
print_and_run_cmd2() {
    echo "Running cmd:  $1"
    cmd_expanded="$(eval echo $cmd)"
    echo "   expanded:  $cmd_expanded"

    eval "$cmd"
}




main() {

    cmd='ls -1 "$HOME/temp/some folder with spaces"' # | grep --color=always "ew"'
    print_and_run_cmd2 "$cmd"
    # eval "$cmd"
}

# echo "$@"
main "$@"


# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./hello_world_basic.sh a b c d e f g
#       a b c d e f g
