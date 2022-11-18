#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Gabriel Staples
# 12 Jan. 2021

# References:
# 1. None; all in my head from prior learning.

print_double_quoted_multiline_examples() {
    # ----------------------------
    # 3 examples that DO work
    # ----------------------------

    # DO IT LIKE THIS!   <======== GOOD =========
    # NB: each separate string argument to the `echo` command is parsed as a separate argument, and
    # `echo` automatically adds a space between each printed argument output, so that is why we do
    # NOT need to add a space inside the quotes after the word "code" inside the first string arg
    # in order to cause a space to appear there in the output. Rather, as separate arguments, the
    # space is added there automatically by `echo`!
    echo "GOOD: This is a multi-line string in the code" \
         "that will print properly on one line in the output."

    # Or this (but it looks awkward in the code!):
    printf "%s\n" "GOOD: This is a multi-line string in the code \
that will print properly on one line in the output."

    # Or this; NOTICE the space required after the word "code"! This format is the most C-like and
    # makes the most sense!  <========== BEST =========
    # - The 2nd string after the format string is read into the 2nd "%s" location in the format
    #   string. Bash `printf` acts a lot like C and C++'s `printf()` function, and neither spaces
    #   nor trailing newline chars are automatically added by `printf`, so you must control and
    #   add all of that manually instead!
    printf "%s%s\n" "GOOD: This is a multi-line string in the code " \
        "that will print properly on one line in the output."

    echo ""

    # ----------------------------
    # 2 examples that do NOT work
    # ----------------------------

    # Not like this.
    echo "BAD: The spacing in this is wrong! It will print with a big \
          gap in it!"

    # And not like this.
    echo "BAD: The spacing in this is wrong too. It will have one space " \
         "too many right before the word \"too\"."

    echo ""
}

print_single_quoted_multiline_examples() {
    echo 'test \'
}


echo -e \
    "--------------------------------------\n"\
   "print_double_quoted_multiline_examples\n" \
    "--------------------------------------"
print_double_quoted_multiline_examples

echo "--------------------------------------" \
     "print_single_quoted_multiline_examples" \
     "--------------------------------------"
print_single_quoted_multiline_examples


# Example output:
#
#       eRCaGuy_hello_world/bash$ ./multiline_string.sh
#       GOOD: This is a multi-line string in the code that will print properly on one line in the output.
#       GOOD: This is a multi-line string in the code that will print properly on one line in the output.
#       GOOD: This is a multi-line string in the code that will print properly on one line in the output.
#
#       BAD: The spacing in this is wrong! It will print with a big           gap in it!
#       BAD: The spacing in this is wrong too. It will have one space  too many right before the word "too".
#

