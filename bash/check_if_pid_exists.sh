#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Mar. 2022

# Test if a PID (Process ID) exists (is running).
# To see all running processes on your PC, so you can choose one of their IDs to
# pass to this program for testing, run this:
#       ps aux

# Status: done and works!

# Check this script with: `shellcheck check_if_pid_exists.sh`

# Run command:
#   General form:
#       ./check_if_pid_exists.sh [pid]
#   Examples:
#       ./check_if_pid_exists.sh
#       ./check_if_pid_exists.sh 5678

# References:
# 1. [my answer with this code] https://stackoverflow.com/a/71134379/4561887
# 1. Main answer by @FDS: https://stackoverflow.com/a/15774758/4561887


pid=1234

if [ "$#" -gt 0 ]; then
    # At least 1 argument was passed in, so assume it is the PID
    pid="$1"
fi

# Try to print the process (`ps`) information for this PID. Send it to
# /dev/null, however, so we don't actually have to look at it. We just want
# the return code, `$?`, which will be 0 if the process exists and some other
# number if not.
#
# NB: do NOT put *any* command, not even an `echo` or `print` statement, between
# the `ps` command and checking the `$?` error code, or else checking the error
# code will check the error code from the `echo` or `print` statement instead
# of from the `ps` command!
ps --pid "$pid" >/dev/null
# shellcheck disable=SC2181
if [ "$?" -eq 0 ]; then
    echo "PID $pid exists and is running."
else
    echo "PID $pid does NOT exist."
fi

# UPDATE: `shellcheck` actually says to do it this way to avoid redundancy,
# so maybe I'll adjust to this style as I continue using bash.
# I probably won't though, since I consider it harder to read and understand.
if ps --pid "$pid" >/dev/null; then
    echo "PID $pid exists and is running."
else
    echo "PID $pid does NOT exist."
fi



# SAMPLE OUTPUT:
# Note: to find a running process whose number you can use, manually run
# `ps aux` first to print out all running PIDs. Then, choose one and pass it to
# this script.

#       eRCaGuy_hello_world/bash$ ./check_if_pid_exists.sh 28876
#       PID 28876 exists and is running.
#       PID 28876 exists and is running.

#       eRCaGuy_hello_world/bash$ ./check_if_pid_exists.sh
#       PID 1234 does NOT exist.
#       PID 1234 does NOT exist.

#       eRCaGuy_hello_world/bash$ ./check_if_pid_exists.sh 5678
#       PID 5678 does NOT exist.
#       PID 5678 does NOT exist.

