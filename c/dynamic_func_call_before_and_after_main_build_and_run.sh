#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


FULL_PATH_TO_SCRIPT="$(realpath "$0")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"
cd "$SCRIPT_DIRECTORY"


# 1. Build the other program (hello_world_basic.c) that has `main()` in it which we want to use
mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj hello_world_basic.c \
-o bin/hello_world_basic
# 2. Create a .o object file of this program, compiling with Position Independent Code (PIC); see
# here: https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
gcc -Wall -Wextra -Werror -O3 -std=c11 -fpic -c dynamic_func_call_before_and_after_main.c \
-o bin/dynamic_func_call_before_and_after_main.o
# 3. Link the above PIC object file into a dynamic shared library (`lib*.so` file); link above shows
# we must use `-shared`
gcc -shared bin/dynamic_func_call_before_and_after_main.o -o \
bin/libdynamic_func_call_before_and_after_main.so
# 4. Call the other program with `main()` in it, dynamically injecting this code into that other
# program via this code's .so shared object file, and via Linux's `LD_PRELOAD` trick
LD_PRELOAD='bin/libdynamic_func_call_before_and_after_main.so' bin/hello_world_basic
