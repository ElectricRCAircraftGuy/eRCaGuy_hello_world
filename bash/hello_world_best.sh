#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# (description)
#
# Status: (status)

# keywords: (keywords to easily grep or ripgrep in this repo for this program and what it teaches)

# Check this script with:
#
##      shellcheck bash/hello_world_best.sh
#
# Run command:
#
#       bash/hello_world_best.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/hello_world_best.sh

# References:
# 1. "eRCaGuy_hello_world/bash/if__name__==__main___check_if_sourced_or_executed_best.sh"
# 1. ***** [my answer] What is the bash equivalent to Python's `if __name__ == '__main__'`?:
#    https://stackoverflow.com/a/70662116/4561887
# 1. This answer here where I first learned about `"${BASH_SOURCE[0]}" = "$0"`:
#    https://stackoverflow.com/a/29967433/4561887
# 1.


main() {
    echo "Running main."
    # Add your main function code here
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
