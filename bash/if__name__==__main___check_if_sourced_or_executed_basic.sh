#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 1 Feb. 2023

# A basic demo to do the equivalent of `if __name__ == '__main__'` in Python.
#
# Status: done and works!

# keywords:

# Check this script with: `shellcheck if__name__==__main___check_if_sourced_or_executed_basic.sh`

# Run command:
#
#       ./if__name__==__main___check_if_sourced_or_executed_basic.sh
#
# Source (import) command to get access to these functions:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . ./if__name__==__main___check_if_sourced_or_executed_basic.sh

# References:
# 1. See: "eRCaGuy_hello_world/bash/print_FUNCNAME_and_BASH_SOURCE_builtin_bash_arrays.sh"
# 1. *****+ [my answer with this code] https://stackoverflow.com/a/70662116/4561887
# 1. Where I first learned about the `${FUNCNAME[-1]}` trick:
#    @mr.spuratic: https://stackoverflow.com/a/14706745/4561887
#    - he learned it from Dennis Williamson apparently.


main() {
    echo "Running main."
}

__name__() {
    # Get the last element in this bash built-in array to see if this script
    # is being sourced or executed. See `man bash` and search for "FUNCNAME".
    # This prints either "__main__" or "__source__".
    printf "%s" "__${FUNCNAME[-1]}__"
}

# Only run `main` if this script is being **run**, NOT sourced (imported)
if [ "$(__name__)" = "__main__" ]; then
    echo "This script is being run."
    main
else
    echo "This script is being sourced."
fi


# SAMPLE OUTPUT:
#
# 1) WHEN RUN
#
#       eRCaGuy_hello_world$ bash/if__name__==__main___check_if_sourced_or_executed_basic.sh
#       This script is being run.
#       Running main.
#
# 2) WHEN SOURCED
#
#       eRCaGuy_hello_world$ . bash/if__name__==__main___check_if_sourced_or_executed_basic.sh
#       This script is being sourced.
