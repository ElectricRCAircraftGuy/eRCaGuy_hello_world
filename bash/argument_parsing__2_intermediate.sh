#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# WIP: NOT YET FUNCTIONAL

# TODO!: build upon the beginner parsing demo, except also check to see if certain arguments
# mean certain things by using if statements like this:
#
#       if [ "$1" = "--some_option" ]; then
#           echo "doing some option"
#           some_var="$2"
#       fi
#
# etc.

# Run command:
#       ./argument_parsing__2_intermediate.sh

# References:
# 1. See some of my previous `if` statements for reference here:
#    https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/rg_replace.sh


echo "$@"



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./argument_parsing__2_intermediate.sh a b c d e f g
#       a b c d e f g
