#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 1 Feb. 2023

# Source (import) the corresponding bash library, and call some functions it
# contains.
#
# Status: wip

# keywords: bell sound; play sounds in bash

# Check this script with:
#
##      shellcheck -x bash/sound_bell_lib_unittest.sh
#
# Run command:
#
#       bash/sound_bell_lib_unittest.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/sound_bell_lib_unittest.sh

# References:
# 1.

# See my answer: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[-1]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
# shellcheck disable=SC2034
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"

# Source (import) the bash library to test
# See also my answer here: https://stackoverflow.com/a/75341911/4561887
# shellcheck source=bash/sound_bell_lib.sh
. "$SCRIPT_DIRECTORY/sound_bell_lib.sh"


# Now test some of its functions

echo "sound_bell 3 .3";      sleep 1
sound_bell 3 .3

echo "sound_bell 7 .2";      sleep 1
sound_bell 7 .2


echo "run_unit_tests"
run_unit_tests

echo "Done!"



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world$ bash/sound_bell_lib_unittest.sh
#       sound_bell 3 .3
#       sound_bell 7 .2
#       run_unit_tests
#       sound_bell
#       sound_bell 2
#       sound_bell 2 .2
#       sound_bell 3 .5
#       sound_bell 1
#       Done!


