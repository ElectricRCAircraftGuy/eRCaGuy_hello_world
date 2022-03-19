#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Mar. 2022

# Read the keyboard, and output live to the user which key was pressed.
# Status: works!

# keywords: read keyboard; read key

# Check this script with: `shellcheck read_keypress.sh`

# Run command:
#       ./read_keypress.sh

# References:
# 1. [MY ANSwer] https://stackoverflow.com/a/70979348/4561887


echo "Press any key. Press Ctrl + C to exit."
while true; do
    read -s -n1 c && printf "You Pressed: %s\n" "$c"
done



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./read_keypress.sh
#       Press any key. Press Ctrl + C to exit.
#       You Pressed: a
#       You Pressed: d
#       You Pressed: b
#       You Pressed: e
#       You Pressed: 
#       You Pressed: [
#       You Pressed: A
#       You Pressed: 
#       You Pressed: [
#       You Pressed: D
#       You Pressed: 
#       You Pressed: [
#       You Pressed: C
#       You Pressed: 
#       You Pressed: [
#       You Pressed: A
#       You Pressed: 
#       You Pressed: [
#       You Pressed: B
#       You Pressed: 9
#       You Pressed: A
#       You Pressed: a
#       You Pressed: B
#       You Pressed: b
#       You Pressed: 1
#       You Pressed: 2
#       You Pressed: 3
#       You Pressed: 4
#       You Pressed: 4
#       You Pressed: 8
#       You Pressed: q
#       You Pressed: p
#       You Pressed: k
#       You Pressed: l
#       You Pressed: j
#       You Pressed: e
#       You Pressed: 1
#       You Pressed: 2
#       You Pressed: 3
#       You Pressed: $
#       You Pressed: 3
#       You Pressed: `
#       You Pressed: ~
#       You Pressed:
#       You Pressed:
#
