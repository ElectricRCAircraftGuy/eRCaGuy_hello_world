#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 2023
#
# Get a short git hash that also indicates if a repo has a "dirty" git status,
# for use in software versioning systems to track software versions.
# - See my answer here: https://stackoverflow.com/a/76856090/4561887
#
# STATUS: done and works!

# keywords to easily grep or ripgrep in this repo for this program and what it teaches
#
# KEYWORDS:

# Check this script with:
#
##      shellcheck bash/git_get_short_hash.sh
#
# Run command:
#
#       bash/git_get_short_hash.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/git_get_short_hash.sh

# References:
# 1. My answer: https://stackoverflow.com/a/76856090/4561887
# 1.


RETURN_CODE_SUCCESS=0
RETURN_CODE_ERROR=1

# Get a short commit hash, and see whether `git status` is clean or dirty.
# Example outputs:
# 1. Not in a git repo: `(not a git repo)`
# 2. In a repo which has a "dirty" `git status`: `72361c8-dirty`
#   - Note that "dirty" means there are pending uncommitted changes.
# 3. In a repo which has a "clean" `git status`: `72361c8`
git_get_short_hash() {
    # See: https://stackoverflow.com/a/16925062/4561887
    is_git_repo="$(git rev-parse --is-inside-work-tree)"

    if [ "$is_git_repo" != "true" ]; then
        echo "(not a git repo)"
        return $RETURN_CODE_SUCCESS
    fi

    # See my answer here: https://stackoverflow.com/a/76856090/4561887
    test -z "$(git status --porcelain)" \
        && echo "$(git rev-parse --short HEAD)" \
        || echo "$(git rev-parse --short HEAD)-dirty"
}

main() {
    git_get_short_hash
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
#       eRCaGuy_hello_world$ bash/git_get_short_hash.sh
#       fddb4ef-dirty
#
#
# 2) WHEN SOURCED
#
#       eRCaGuy_hello_world$ . bash/git_get_short_hash.sh
#       eRCaGuy_hello_world$ main
#       fddb4ef-dirty
#       eRCaGuy_hello_world$ git_get_short_hash
#       fddb4ef-dirty

