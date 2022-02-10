#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 9 Feb. 2022
# Show how to print out all incoming bash parameters from the input array named `@`.

# Run command:
#       ./print_all_parameters.sh
#   Or
#       ./print_all_parameters.sh a b c d e f g

# References:
# 1. NA


# This prints out all passed-in parameters from the incoming bash array named `@`.
# Ex: run this to see all of these parameters print out:
#       ./print_all_parameters.sh a b c d e f g
echo "$@"



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./print_all_parameters.sh a b c d e f g
#       a b c d e f g
