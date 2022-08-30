#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 10 Mar. 2022 ~ 29 Aug. 2022

# Play some music in bash!

# Status: wip; works, but needs some cleanup and a ton of study to understand it! Copied from the
# link below.

# keywords: (keywords to easily grep or ripgrep in this repo for this program and what it teaches)

# Check this script with: `shellcheck alsa_aplay_play_music.sh`

# Run command:
#       ./alsa_aplay_play_music.sh

# References:
# 1. *****+ https://tldp.org/LDP/abs/html/devref1.html --> Example 29-2. Playing music



# From: https://tldp.org/LDP/abs/html/devref1.html --> Example 29-2. Playing music:
# Advanced Bash-Scripting Guide:
# Chapter 29. /dev and /proc

#!/bin/bash
# music.sh

# Music without external files

# Author: Antonio Macchi
# Used in ABS Guide with permission.


#  /dev/dsp default = 8000 frames per second, 8 bits per frame (1 byte),
#+ 1 channel (mono)

duration=2000       # If 8000 bytes = 1 second, then 2000 = 1/4 second.
volume=$'\xc0'      # Max volume = \xff (or \x00).
mute=$'\x80'        # No volume = \x80 (the middle).

function mknote ()  # $1=Note Hz in bytes (e.g. A = 440Hz ::
{                   #+ 8000 fps / 440 = 16 :: A = 16 bytes per second)
  # GS: 8000 samples/sec / 440 periods/sec = 18 samples per period.
  for t in `seq 0 $duration`
  do
    test $(( $t % $1 )) = 0 && echo -n $volume || echo -n $mute
  done
}

e=`mknote 49`
g=`mknote 41`
a=`mknote 36`
b=`mknote 32`
c=`mknote 30`
cis=`mknote 29`
d=`mknote 27`
e2=`mknote 24`
n=`mknote 32767`
# European notation.

######### https://unix.stackexchange.com/a/147147/114401

# echo -n "$g$e2$d$c$d$c$a$g$n$g$e$n$g$e2$d$c$c$b$c$cis$n$cis$d \
# $n$g$e2$d$c$d$c$a$g$n$g$e$n$g$a$d$c$b$a$b$c" > /dev/dsp

echo -n "$g$e2$d$c$d$c$a$g$n$g$e$n$g$e2$d$c$c$b$c$cis$n$cis$d \
$n$g$e2$d$c$d$c$a$g$n$g$e$n$g$a$d$c$b$a$b$c" | aplay
# dsp = Digital Signal Processor

exit      # A "bonny" example of an elegant shell script!



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./alsa_aplay_play_music.sh a b c d e f g
#       a b c d e f g
