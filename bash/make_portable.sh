#!/usr/bin/env bash

# By Gabriel Staples
# - See: https://stackoverflow.com/a/79569000/4561887
# - COPIED MAY 2025 FROM: 
#   https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/blob/main/make_portable.sh

# Make a "build/Portable/" dir which can be copied to a Windows machine and
# contains the required DLLs packaged right next to it. 
# 
# For Windows, this allows you to run the program in a non-MSYS terminal, or 
# in a different MSYS-based terminal than the one in which it was built. 
# This means you can now run your program in Git Bash, Command Prompt, 
# PowerShell, or by double-clicking the executable in File Explorer.
# You can also copy the entire `Portable` dir to a new Windows computer, even
# if it doesn't have MSYS2 installed, and run the program there.
# 
# For Linux, to use the packaged .so shared object files in the same way, you
# need to set the `LD_LIBRARY_PATH` environment variable to the directory
# containing the .so files, at call time, like this: 
# ```bash
# cd build/Portable
# LD_LIBRARY_PATH=. ./your_program
# ```

EXECUTABLE_NAME="$1"

# See here: https://stackoverflow.com/a/60157372/4561887
# NB: `-s` means do NOT expand symlinks, which is what I want in my case. 
FULL_PATH_TO_SCRIPT="$(realpath -s "${BASH_SOURCE[0]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
echo "SCRIPT_DIRECTORY: ${SCRIPT_DIRECTORY}"  # debugging

PORTABLE_DIR="build/Portable"
# Note that `.exe` on Windows is optional. "build/Release/your_program" and
# "build/Release/your_program.exe" are equivalent.
PATH_TO_RELEASE_PROGRAM="build/Release/${EXECUTABLE_NAME}"

cd "$SCRIPT_DIRECTORY"
mkdir -p "${PORTABLE_DIR}"

if [ ! -f "${PATH_TO_RELEASE_PROGRAM}" ]; then
    echo \
        "Error: Release program not found at \"${PATH_TO_RELEASE_PROGRAM}\"." \
        "Please build the program first."
    exit 1
fi

readarray -t required_dynamic_libs < <(ldd "${PATH_TO_RELEASE_PROGRAM}" \
    | grep '=>' | awk '{print $3}')
for lib in "${required_dynamic_libs[@]}"; do
    # Copy the library to the "Portable" directory
    cp "$lib" "${PORTABLE_DIR}/"
done

# Also copy the executable over
cp "${PATH_TO_RELEASE_PROGRAM}" "${PORTABLE_DIR}"

echo "  Portable directory created at \"${PORTABLE_DIR}/\"."

echo ""
echo \
    "  To run the program in Windows, navigate to \"${PORTABLE_DIR}/\" and" \
    "run it in any terminal including Git Bash, Command Prompt, PowerShell," \
    "or by double-clicking the executable in File Explorer."
echo ""
echo \
    "  To run the program in Linux with those shared object files, cd to" \
    "\"${PORTABLE_DIR}/\" and run it, like this:"
echo "    cd \"${PORTABLE_DIR}/\""
echo "    LD_LIBRARY_PATH=. ./your_program"
echo ""
