#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Obtain path to this script.
# See my own ans here: 
# https://stackoverflow.com/questions/59895/how-to-get-the-source-directory-of-a-bash-script-from-within-the-script-itself/60157372#60157372
THIS_PATH="$(realpath $0)"
THIS_DIR="$(dirname "$THIS_PATH")"
# echo "THIS_DIR = \"$THIS_DIR\"" # for debugging 

g++ -Wall -Werror -g3 -std=c++17 -o "$THIS_DIR/bin/explicit_template_specialization" \
"$THIS_DIR/explicit_template_specialization.cpp" && \
"$THIS_DIR/bin/explicit_template_specialization"


