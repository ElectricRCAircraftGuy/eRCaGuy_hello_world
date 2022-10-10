#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# https://gabrielstaples.com/
# Oct. 2022

# Learn how to make a FIFO Inter-process Communication (IPC) pipe to send data
# from one program (process) to another.

# Status: done!

# keywords: (keywords to easily grep or ripgrep in this repo for this program and what it teaches)

# Check this script with: `shellcheck hello_world_basic.sh`

# Run command:
# NA
# Do NOT run this file directly. Rather, follow instructions in the comments below.

# References:
# 1. ***** [in the question itself!] https://unix.stackexchange.com/q/96718/114401
#   1. *****+ [my own answer!] https://unix.stackexchange.com/a/720397/114401 -
#      including "Key differences between sending over a serial port and sending
#      over an inter-process-communication (IPC) pipe"


# ----------------
# In terminal 1
# ----------------

# Make a FIFO (a named pipe) to send data from one process to another;
# NB: this pipe actually shows up as a **file** (technically a pseudo-file)
# named "mypipe" and in the current directory you are in when you run this cmd!
mkfifo mypipe

# Option 1: Start listening for incoming data over this pipe, and print it to
# the screen when it comes in.
cat < mypipe
# OR: Option 2: start listening for incoming data over this pipe, and write it
# to file "out.txt" when it comes in.
cat < mypipe > out.txt
# OR: Option 3: start listening for incoming data over this pipe, and write it
# to file "out.txt" AND print it to the screen when it comes in.
cat < mypipe | tee out.txt


# ----------------
# In terminal 2 (manually open this up as a *separate* terminal and **in the
# same directory** as terminal 1 is in!)
# ----------------

# Send some data to terminal 1, over the pipe
echo "Hello world!" > mypipe
# Once done, you can manually delete the pipe file like this:
rm mypipe



# SAMPLE OUTPUT:
#
# When you run `echo "Hello world!" > mypipe` in the 2nd terminal, you'll see
# `Hello world!` magically show up in the 1st terminal!
