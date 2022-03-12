#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 12 Mar. 2022

# Learn to play one or more .wav files with the ALSA (Advanced Linux Sound Architecture) `aplay`
# Linux audio utility.

# Status:  wip

# keywords:

# Check this script with: `shellcheck alsa_aplay_wav_file.sh`

# Run command:
#       ./alsa_aplay_wav_file.sh

# References:
# 1. ALSA (Advanced Linux Sound Architecture):
#    https://en.wikipedia.org/wiki/Advanced_Linux_Sound_Architecture
# 1. See `man aplay`
# 1. My comment here:
#    https://unix.stackexchange.com/questions/103746/why-wont-linux-let-me-play-with-dev-dsp/147147#comment1312330_147147


echo "1. Play one file by **piping it** to the 'stdin' of aplay'."
cat /usr/share/sounds/alsa/Front_Center.wav | aplay
echo ""

echo "2. Play one file by **passing it as a parameter** to 'aplay'."
aplay /usr/share/sounds/alsa/Front_Center.wav
echo ""

echo "3. Play the same file 2x by passing it to 'aplay' twice."
aplay /usr/share/sounds/alsa/Front_Center.wav /usr/share/sounds/alsa/Front_Center.wav

echo "4. Play the same file 3x by passing it to 'aplay' thrice."
aplay \
    /usr/share/sounds/alsa/Front_Center.wav \
    /usr/share/sounds/alsa/Front_Center.wav \
    /usr/share/sounds/alsa/Front_Center.wav
echo ""



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./alsa_aplay_wav_file.sh
#       1. Play one file by **piping it** to the 'stdin' of aplay'.
#       Playing WAVE 'stdin' : Signed 16 bit Little Endian, Rate 48000 Hz, Mono
#
#       2. Play one file by **passing it as a parameter** to 'aplay'.
#       Playing WAVE '/usr/share/sounds/alsa/Front_Center.wav' : Signed 16 bit Little Endian, Rate 48000 Hz, Mono
#
#       3. Play the same file 2x by passing it to 'aplay' twice.
#       Playing WAVE '/usr/share/sounds/alsa/Front_Center.wav' : Signed 16 bit Little Endian, Rate 48000 Hz, Mono
#       Playing WAVE '/usr/share/sounds/alsa/Front_Center.wav' : Signed 16 bit Little Endian, Rate 48000 Hz, Mono
#       4. Play the same file 3x by passing it to 'aplay' thrice.
#       Playing WAVE '/usr/share/sounds/alsa/Front_Center.wav' : Signed 16 bit Little Endian, Rate 48000 Hz, Mono
#       Playing WAVE '/usr/share/sounds/alsa/Front_Center.wav' : Signed 16 bit Little Endian, Rate 48000 Hz, Mono
#       Playing WAVE '/usr/share/sounds/alsa/Front_Center.wav' : Signed 16 bit Little Endian, Rate 48000 Hz, Mono
#

