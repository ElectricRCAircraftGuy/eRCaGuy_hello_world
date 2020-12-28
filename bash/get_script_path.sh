#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# get_script_path.sh
# - Obtain the full file path, full directory, and base filename of this script being run itself.
# - Note that `realpath` also successfully walks down symbolic links to determine and point to their
#   targets rather than pointing to the symbolic link.
#
# References:
# 1. *****+[see my own answer here!]:
#    https://stackoverflow.com/questions/59895/how-to-get-the-source-directory-of-a-bash-script-from-within-the-script-itself/60157372#60157372
# 2. https://stackoverflow.com/questions/4175264/how-to-retrieve-absolute-path-given-relative/14892459#14892459

FULL_PATH_TO_SCRIPT="$(realpath $0)"

# You can then also get the full path to the directory, and the base
# filename, like this:
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"

# Now print it all out
echo "FULL_PATH_TO_SCRIPT = \"$FULL_PATH_TO_SCRIPT\""
echo "SCRIPT_DIRECTORY    = \"$SCRIPT_DIRECTORY\""
echo "SCRIPT_FILENAME     = \"$SCRIPT_FILENAME\""



# SAMPLE OUTPUT:

# ~/GS/dev/eRCaGuy_hello_world/bash$ ./get_script_path.sh
# FULL_PATH_TO_SCRIPT = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
# SCRIPT_DIRECTORY    = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
# SCRIPT_FILENAME     = "get_script_path.sh"
