#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# multi_process_program.sh

# By Gabriel Staples
# First written: 11 Jan. 2022

# Create a "multi-threaded" (multi-process, actually) bash program, and learn how to start the
# processes and determine when each is done!

# References:
# 1. [my own answer where I posted this code!] https://stackoverflow.com/a/70670852/4561887
# 1. how I first learned the basics of this approach: https://stackoverflow.com/a/356154/4561887

# Run it
#       time ./multi_process_program.sh

# Create an array of whatever commands you want to run as subprocesses
procs=()  # bash array
procs+=("sleep 1")
procs+=("sleep 2")
procs+=("sleep 3")
procs+=("sleep 4")

num_procs=${#procs[@]}  # number of processes
echo "num_procs = $num_procs"

# run commands as subprocesses and store pids in an array
pids=()  # bash array
for (( i=0; i<"$num_procs"; i++ )); do
    echo "cmd = ${procs[$i]}"
    ${procs[$i]} &  # run the cmd as a subprocess
    # store pid of last subprocess started; see:
    # https://unix.stackexchange.com/a/30371/114401
    pids+=("$!")
    echo "    pid = ${pids[$i]}"
done

# wait for all pids
for pid in "${pids[@]}"; do
    wait "$pid"
done



# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ time ./multi_process_program.sh
#       num_procs = 4
#       cmd = sleep 1
#           pid = 26573
#       cmd = sleep 2
#           pid = 26574
#       cmd = sleep 3
#           pid = 26575
#       cmd = sleep 4
#           pid = 26576
#
#       real    0m4.013s
#       user    0m0.015s
#       sys 0m0.010s

