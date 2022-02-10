#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Basic "hello world" demo in Linux/Unix Bash scripting.

# Run command:
#       ./hello_world.sh

# References:
# 1. None


i=0

((i++))
echo "${i}: Hello World"

((i++))
printf "%s\n" "${i}: Hello World"



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./hello_world.sh
#       1: Hello World
#       2: Hello World
