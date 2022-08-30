#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# ~Apr.~Aug. 2022

# Try to play a constant tone using the ALSA `aplay` executable.

# Status: wip; does NOT work yet! It just makes a couple ticking noises, but doesn't play a tone
# yet! :(

# keywords: (keywords to easily grep or ripgrep in this repo for this program and what it teaches)

# Check this script with: `shellcheck alsa_aplay_try_to_play_via_for_loop_WIP.sh`

# Run command:
#       ./alsa_aplay_try_to_play_via_for_loop_WIP.sh

# References:
# 1.


for t in $(seq 0 8000); do echo $((t%4)); done | aplay




# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./alsa_aplay_try_to_play_via_for_loop_WIP.sh a b c d e f g
#       a b c d e f g
