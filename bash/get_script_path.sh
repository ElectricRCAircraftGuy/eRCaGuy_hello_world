#!/usr/bin/env bash

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

# A. Obtain the full path, and expand (walk down) symbolic links
FULL_PATH_TO_SCRIPT="$(realpath "$0")"
# Get the full path to the directory, and the base filename
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"

# OR: B. Obtain the full path, but do NOT expand (walk down) symbolic links; in
# other words: **keep** the symlinks as part of the path!
FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS="$(realpath -s "$0")"
# Get the full path to the directory, and the base filename
SCRIPT_DIRECTORY_KEEP_SYMLINKS="$(dirname "$FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS")"
SCRIPT_FILENAME_KEEP_SYMLINKS="$(basename "$FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS")"


# Now print it all out

echo "FULL_PATH_TO_SCRIPT               = \"$FULL_PATH_TO_SCRIPT\""
echo "SCRIPT_DIRECTORY                  = \"$SCRIPT_DIRECTORY\""
echo "SCRIPT_FILENAME                   = \"$SCRIPT_FILENAME\""
echo "==="
echo "FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS = \"$FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS\""
echo "SCRIPT_DIRECTORY_KEEP_SYMLINKS    = \"$SCRIPT_DIRECTORY_KEEP_SYMLINKS\""
echo "SCRIPT_FILENAME_KEEP_SYMLINKS     = \"$SCRIPT_FILENAME_KEEP_SYMLINKS\""


# SAMPLE OUTPUT:


# 1: Run the script with NO symlinks in the path to the script. Output
#    is the same for both the regular and the `_KEEP_SYMLINKS` case:
#
# ~/GS/dev/eRCaGuy_hello_world/bash$ ./get_script_path.sh
# FULL_PATH_TO_SCRIPT               = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
# SCRIPT_DIRECTORY                  = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
# SCRIPT_FILENAME                   = "get_script_path.sh"
# ===
# FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
# SCRIPT_DIRECTORY_KEEP_SYMLINKS    = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
# SCRIPT_FILENAME_KEEP_SYMLINKS     = "get_script_path.sh"


# 2: Run the script through a **symlink to the script** (ie: WITH symlinks in the path to this
#    script):
# - Notice that, when run via a symlink to the script, `FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS` contains
#   the full path **to the symlinked script** (WITH "test_dir_for_symlinks/get_script_path.sh" in
#   the path) rather than **to the target script**, but `FULL_PATH_TO_SCRIPT` does NOT contain that
#   path to the symlink since it expands (walks down) that symlink to find the real path!
#
# ~/GS/dev/eRCaGuy_hello_world/bash$ ./test_dir_for_symlinks/get_script_path.sh
# FULL_PATH_TO_SCRIPT               = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
# SCRIPT_DIRECTORY                  = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
# SCRIPT_FILENAME                   = "get_script_path.sh"
# ===
# FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/test_dir_for_symlinks/get_script_path.sh"
# SCRIPT_DIRECTORY_KEEP_SYMLINKS    = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/test_dir_for_symlinks"
# SCRIPT_FILENAME_KEEP_SYMLINKS     = "get_script_path.sh"
