#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# get_script_path.sh
# - Obtain the full file path, full directory, and base filename of a script being
#   **run** OR **sourced**.
# - Note that `realpath` also successfully walks down symbolic links to determine and point to their
#   targets rather than pointing to the symbolic link.
#
# References:
# 1. *****+[see my own answer here!]: https://stackoverflow.com/a/60157372/4561887
# 1. https://stackoverflow.com/a/14892459/4561887
# 1. taught me about the `BASH_SOURCE` variable: [Unix & Linux: determining path to sourced shell
#    script](https://unix.stackexchange.com/a/4653/114401)
# 1. taught me that `BASH_SOURCE` is actually an array, and we want the last element from it for it
#    to work as expected inside a function (hence why I used `"${BASH_SOURCE[-1]}"` in my code
#    here): [Unix & Linux: determining path to sourced shell script]
#    (https://unix.stackexchange.com/a/153061/114401)

# A. Obtain the full path, and expand (walk down) symbolic links.
# A.1. `"$0"` works only if the file is **run**, but NOT if it is **sourced**.
# FULL_PATH_TO_SCRIPT="$(realpath "$0")"
# A.2. `"${BASH_SOURCE[-1]}"` works whether the file is sourced OR run, and even
# if the script is called from within another bash function!
# NB: if `"${BASH_SOURCE[-1]}"` doesn't give you quite what you want, use
# `"${BASH_SOURCE[0]}"` instead in order to get the first element from the array.
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[-1]}")"
# Get the full path to the directory, and the base filename
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"

# OR: B. Obtain the full path, but do NOT expand (walk down) symbolic links; in
# other words: **keep** the symlinks as part of the path!
# B.1. `"$0"` works only if the file is **run**, but NOT if it is **sourced**.
# FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS="$(realpath -s "$0")"
# B.2. `"${BASH_SOURCE[-1]}"` works whether the file is sourced OR run, and even
# if the script is called from within another bash function!
# NB: if `"${BASH_SOURCE[-1]}"` doesn't give you quite what you want, use
# `"${BASH_SOURCE[0]}"` instead in order to get the first element from the array.
FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS="$(realpath -s "${BASH_SOURCE[-1]}")"
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
#       ~/GS/dev/eRCaGuy_hello_world/bash$ ./get_script_path.sh
#       FULL_PATH_TO_SCRIPT               = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
#       SCRIPT_DIRECTORY                  = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
#       SCRIPT_FILENAME                   = "get_script_path.sh"
#       ===
#       FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
#       SCRIPT_DIRECTORY_KEEP_SYMLINKS    = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
#       SCRIPT_FILENAME_KEEP_SYMLINKS     = "get_script_path.sh"
#
#
# 2: Run the script through a **symlink to the script** (ie: WITH symlinks in the path to this
#    script):
# - Notice that, when run via a symlink to the script, `FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS` contains
#   the full path **to the symlinked script** (WITH "test_dir_for_symlinks/get_script_path.sh" in
#   the path) rather than **to the target script**, but `FULL_PATH_TO_SCRIPT` does NOT contain that
#   path to the symlink since it expands (walks down) that symlink to find the real path!
#
#       ~/GS/dev/eRCaGuy_hello_world/bash$ ./test_dir_for_symlinks/get_script_path.sh
#       FULL_PATH_TO_SCRIPT               = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
#       SCRIPT_DIRECTORY                  = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
#       SCRIPT_FILENAME                   = "get_script_path.sh"
#       ===
#       FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/test_dir_for_symlinks/get_script_path.sh"
#       SCRIPT_DIRECTORY_KEEP_SYMLINKS    = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/test_dir_for_symlinks"
#       SCRIPT_FILENAME_KEEP_SYMLINKS     = "get_script_path.sh"
#
#
# 3. Source it directly
#       eRCaGuy_hello_world/bash$ . get_script_path.sh
#       FULL_PATH_TO_SCRIPT               = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
#       SCRIPT_DIRECTORY                  = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
#       SCRIPT_FILENAME                   = "get_script_path.sh"
#       ===
#       FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
#       SCRIPT_DIRECTORY_KEEP_SYMLINKS    = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
#       SCRIPT_FILENAME_KEEP_SYMLINKS     = "get_script_path.sh"
#
#
# 4. Source it from the symlink
#       eRCaGuy_hello_world/bash$ . test_dir_for_symlinks/get_script_path.sh
#       FULL_PATH_TO_SCRIPT               = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
#       SCRIPT_DIRECTORY                  = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
#       SCRIPT_FILENAME                   = "get_script_path.sh"
#       ===
#       FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/test_dir_for_symlinks/get_script_path.sh"
#       SCRIPT_DIRECTORY_KEEP_SYMLINKS    = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/test_dir_for_symlinks"
#       SCRIPT_FILENAME_KEEP_SYMLINKS     = "get_script_path.sh"


# OUTPUT FOR THE SOURCE EXAMPLES IF YOU USE `"$0"` ABOVE INSTEAD OF `"${BASH_SOURCE[-1]}"`:
#
# 3. Source it directly [notice this does NOT work to find the script's path when sourced!]
#
#       eRCaGuy_hello_world/bash$ . get_script_path.sh
#       FULL_PATH_TO_SCRIPT               = "/bin/bash"
#       SCRIPT_DIRECTORY                  = "/bin"
#       SCRIPT_FILENAME                   = "bash"
#       ===
#       FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS = "/bin/bash"
#       SCRIPT_DIRECTORY_KEEP_SYMLINKS    = "/bin"
#       SCRIPT_FILENAME_KEEP_SYMLINKS     = "bash"
#
#
# 4. Source it from the symlink [notice this does NOT work to find the script's path when sourced!]
#
#       eRCaGuy_hello_world/bash$ . test_dir_for_symlinks/get_script_path.sh
#       FULL_PATH_TO_SCRIPT               = "/bin/bash"
#       SCRIPT_DIRECTORY                  = "/bin"
#       SCRIPT_FILENAME                   = "bash"
#       ===
#       FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS = "/bin/bash"
#       SCRIPT_DIRECTORY_KEEP_SYMLINKS    = "/bin"
#       SCRIPT_FILENAME_KEEP_SYMLINKS     = "bash"
