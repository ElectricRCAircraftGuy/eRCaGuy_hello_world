#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Find all files which contain the words "interview prep" (case *in*sensitive) in this repo.
#
# Dependencies:
# 1. Install ripgrep (rg) first.
#    See here: https://github.com/BurntSushi/ripgrep#installation
#    In the cmds below, update the version number to the latest release found here:
#    https://github.com/BurntSushi/ripgrep/releases
#
#       rg --version        # check your version beforehand, if upgrading
#       mkdir -p ~/Downloads/Install_Files/ripgrep
#       cd ~/Downloads/Install_Files/ripgrep
#       curl -LO https://github.com/BurntSushi/ripgrep/releases/download/13.0.0/ripgrep_13.0.0_amd64.deb
#       sudo dpkg -i ripgrep_13.0.0_amd64.deb
#       rg --version        # check your version to ensure it was installed or upgraded

# Status: done and works!

# Check this script with:
#
##      shellcheck find_interview_prep.sh
#
# Run command:
#
#       ./find_interview_prep.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . find_interview_prep.sh

# References:
# 1.


# RETURN_CODE_SUCCESS=0
RETURN_CODE_ERROR=1

# See my answer here: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[-1]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
# SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"

main() {
    echo "Finding all \"interview prep\" files in directory"\
         "\"$SCRIPT_DIRECTORY\" and lower."

    cd "$SCRIPT_DIRECTORY" || exit "$RETURN_CODE_ERROR"
    files="$(rg -i --no-ignore --no-hidden -l --color always 'interview prep')"
    files_count="$(echo "$files" | wc -l)"
    echo "$files"

    echo "Done. $files_count file(s) found."
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
#       eRCaGuy_hello_world/bash$ ../find_interview_prep.sh
#       Finding all "interview prep" files in directory "/home/gabriel/GS/dev/eRCaGuy_hello_world" and lower.
#       find_interview_prep.sh
#       Done. 1 file(s) found.
#
#
# 2) WHEN SOURCED (no output)
#
#       eRCaGuy_hello_world$ . find_interview_prep.sh
