#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# (description)
#
# Status: (status)

# keywords: (keywords to easily grep or ripgrep in this repo for this program and what it teaches)

# Check this script with: `shellcheck hello_world_best.sh`

# Run command:
#
#       bash/hello_world_best.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/hello_world_best.sh

# References:
# 1. "eRCaGuy_hello_world/bash/if__name__==__main___check_if_sourced_or_executed_basic.sh"
# 1. [my answer] What is the bash equivalent to Python's `if __name__ == '__main__'`?:
#    https://stackoverflow.com/a/70662116/4561887


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
    main
fi


# SAMPLE OUTPUT:
#
# 1) WHEN RUN (it prints "Running main.")
#
#       eRCaGuy_hello_world$ bash/hello_world_best.sh
#       Running main.
#
#
# 2) WHEN SOURCED (no output)
#
#       eRCaGuy_hello_world$ . bash/hello_world_best.sh
