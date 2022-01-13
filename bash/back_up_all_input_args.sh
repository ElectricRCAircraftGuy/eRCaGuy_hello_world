#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Jan. 2022
#
# Demonstrate how to back up and use the input arguments array, which is normally accessed as
# `"$@"`.
#
# ===> SEE ALSO "array_practice.sh" for other examples of how to pass an array to a command as
#      arguments to the command! Ex:
#           ls "${my_args_array[@]}"
#
# Run cmd:
#       ./back_up_all_input_args.sh arg1 "arg 2" "arg 3"
#
# References:
# 1. [my Q]
# https://stackoverflow.com/questions/70572744/how-can-i-create-and-use-a-backup-copy-of-all-input-args-in-bash
#   1. See my References I mention in my question here too!

all_args1="$@"                     # Does NOT work
all_args2="$(printf "%q " "$@")"   # Does NOT work
all_args3=("${@[@]}")              # Does NOT work: "bad substitution"
all_args4=("$@")                   # WORKS! See: https://stackoverflow.com/a/70572787/4561887

shift # remove 1st arg
shift # remove 2nd arg

# Test out each of the approaches now; this is where we see if they work or don't work
echo   '$@        = '"$@"                       # Does NOT work
echo   "all_args1 = $all_args1"                 # Does NOT work
echo   "all_args2 = $all_args2"                 # Does NOT work
echo   "all_args3 = $all_args3"                 # Does NOT work (string-style print)
printf 'all_args3 = [%s]\n' "${all_args3[@]}"   # Does NOT work (array-style print)
echo   "all_args4 = $all_args4"                 # Does NOT work (string-style print)

# THIS WORKS!
printf "\n"
printf "%s" "all_args4 = "
printf '"%s" ' "${all_args4[@]}"
printf "\n"
printf "\n"

# THIS WORKS TOO!
# First, prove that `"$@"` still isn't restored.
echo '$@ = '"$@"
echo '$1 = '"$1"
echo '$2 = '"$2"
echo '$3 = '"$3"
# Now, restore it
set -- "${all_args4[@]}"  # THIS WORKS!
# And prove it is restored
echo '$@ = '"$@"
echo '$1 = '"$1"
echo '$2 = '"$2"
echo '$3 = '"$3"



# SAMPLE OUTPUT:
#
#       eRCaGuy_dotfiles$ ../eRCaGuy_hello_world/bash/back_up_all_input_args.sh arg1 "arg 2" "arg 3"
#       ../eRCaGuy_hello_world/bash/back_up_all_input_args.sh: line 21: ${@[@]}: bad substitution
#       $@        = arg 3
#       all_args1 = arg1 arg 2 arg 3
#       all_args2 = arg1 arg\ 2 arg\ 3
#       all_args3 =
#       all_args3 = []
#       all_args4 = arg1
#
#       all_args4 = "arg1" "arg 2" "arg 3"
#
#       $@ = arg 3
#       $1 = arg 3
#       $2 =
#       $3 =
#       $@ = arg1 arg 2 arg 3
#       $1 = arg1
#       $2 = arg 2
#       $3 = arg 3

