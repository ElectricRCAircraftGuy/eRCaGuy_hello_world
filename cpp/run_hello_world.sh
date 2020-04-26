#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Obtain path to this script.
# See my own ans here: 
# https://stackoverflow.com/questions/59895/how-to-get-the-source-directory-of-a-bash-script-from-within-the-script-itself/60157372#60157372
THIS_PATH="$(realpath $0)"
THIS_DIR="$(dirname "$THIS_PATH")"
# echo "THIS_DIR = \"$THIS_DIR\"" # for debugging 

# Build and run this program

PROGRAM_NAME="hello_world"
SOURCE_FILES="hello_world.cpp"
# BIN_DIR="bin"
BIN_DIR="bin_hello_world"

mkdir -p "${THIS_DIR}/${BIN_DIR}"

# - See all warning options in the gcc user manual here on the "Warning Options" page: 
#   https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
# - Note: `-g3` adds full debugging info! See the `-g` and `-glevel` options here: 
#   https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html
# - For meaning of -save-temps=obj, see: https://stackoverflow.com/a/46256372/4561887
#   Basically, it tells the temp objects to go to the same location as the -o setting!
g++ -Wall -Werror -g3 -std=c++17 -save-temps=obj -o "${THIS_DIR}/${BIN_DIR}/${PROGRAM_NAME}" \
"${THIS_DIR}/${SOURCE_FILES}" && \
"${THIS_DIR}/${BIN_DIR}/${PROGRAM_NAME}"


