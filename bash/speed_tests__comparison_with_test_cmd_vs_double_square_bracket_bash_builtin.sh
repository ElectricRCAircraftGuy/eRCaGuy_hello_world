#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 13 Oct. 2023
#
# Let's speed test the `test` command (`[`) vs the `[[` bash builtin.
# ie: `[]` vs `[[]]` speed tests.
# See my answer: https://stackoverflow.com/a/77291070/4561887
#
# STATUS: done and works!

# keywords to easily grep or ripgrep in this repo for this program and what it teaches
#
# KEYWORDS:

# Check this script with:
#
##      shellcheck bash/speed_tests__comparison_with_test_cmd_vs_double_square_bracket_bash_builtin.sh
#
# Run command:
#
#       bash/speed_tests__comparison_with_test_cmd_vs_double_square_bracket_bash_builtin.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/speed_tests__comparison_with_test_cmd_vs_double_square_bracket_bash_builtin.sh

# References:
# 1. My answer: https://stackoverflow.com/a/77291070/4561887
# 1.


NUM_ITERATIONS="1000000" # 1 million
word1="true"
word2="false"

single_bracket() {
    echo -e "\nsingle_bracket() start..."
    for i in $(seq 1 "$NUM_ITERATIONS"); do
        if [ "$word1" = "$word2" ]; then
            echo "true"
        fi
    done
    echo "single_bracket() done."
}

double_bracket() {
    echo -e "\ndouble_bracket() start..."
    for i in $(seq 1 "$NUM_ITERATIONS"); do
        if [[ "$word1" == "$word2" ]]; then
            echo "true"
        fi
    done
    echo "double_bracket() done."
}

main() {
    echo "Running speed tests."
    time single_bracket
    echo "====================="
    time double_bracket
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
# 1) WHEN RUN
#
#       eRCaGuy_hello_world$ bash/speed_tests__comparison_with_test_cmd_vs_double_square_bracket_bash_builtin.sh
#       Running speed tests.
#
#       single_bracket() start...
#       single_bracket() done.
#
#       real	0m2.334s
#       user	0m2.291s
#       sys	0m0.055s
#       =====================
#
#       double_bracket() start...
#       double_bracket() done.
#
#       real	0m1.604s
#       user	0m1.597s
#       sys	0m0.020s
#
#
#
# 2) WHEN SOURCED (no output, but it brings in all functions herein so you can use them!)
#
#       eRCaGuy_hello_world$ . bash/speed_tests__comparison_with_test_cmd_vs_double_square_bracket_bash_builtin.sh
