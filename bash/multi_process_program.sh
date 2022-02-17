#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# multi_process_program.sh

# By Gabriel Staples
# First written: 11 Jan. 2022

# Create a "multi-threaded" (multi-process, actually) bash program, and learn how to start the
# processes and determine when each is done!
#
# keywords: multi-process bash program; delete or remove elements from standard
# bash "indexed" array; iterate across bash array indices or indexes

# References:
# 1. [my own answer where I posted this code!] https://stackoverflow.com/a/70670852/4561887
# 1. how I first learned the basics of this approach: https://stackoverflow.com/a/356154/4561887
# 1. [Remove an element from a Bash array](https://stackoverflow.com/q/16860877/4561887)

# Run it
#       time ./multi_process_program.sh

# Create an array of whatever commands you want to run as subprocesses
procs=()  # bash array
procs+=("sleep 5")
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

# # OPTION 1 (comment this option out if using Option 2 below): wait for all pids
# for pid in "${pids[@]}"; do
#     wait "$pid"
# done
# echo "All $num_procs processes have ended."

# OR OPTION 2 (comment out Option 1 above if using Option 2): poll to detect
# when each process terminates, and print out when each process finishes!
while true; do
    for i in "${!pids[@]}"; do
        pid="${pids[$i]}"
        # echo "pid = $pid"  # debugging

        # See if PID is still running; see my answer here:
        # https://stackoverflow.com/a/71134379/4561887
        ps --pid "$pid" > /dev/null
        if [ "$?" -ne 0 ]; then
            # PID doesn't exist anymore, meaning it terminated
            # remove it from the `pids` array by `unset`ting the element at this
            # index; NB: due to how bash arrays work, this does NOT actually
            # remove this element from the array. Rather, it removes this index
            # from the `"${!pids[@]}"` list of indices, adjusts the array count
            # (`"${#pids[@]}"`) accordingly, and it sets the value at this
            # index to either a null value of some sort, or an empty string
            # (I'm not exactly sure).
            unset "pids[$i]"

            num_pids="${#pids[@]}"
            echo "PID $pid is done. $num_pids PIDs remaining."
        fi
    done

    # exit the while loop if the `pids` array is empty
    if [ "${#pids[@]}" -eq 0 ]; then
        break
    fi

    # Do some small sleep here to keep your polling loop from sucking up
    # 100% of one of your CPUs unnecessarily. Sleeping allows other processes
    # to run during this time.
    sleep 0.1
done


# SAMPLE OUTPUT:
#
# OPTION 1 (with Option 2 commented out)
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
#
# OPTION 2 (with Option 1 commented out)
#
#       eRCaGuy_hello_world/bash$ ./multi_process_program.sh
#       num_procs = 4
#       cmd = sleep 5
#           pid = 14736
#       cmd = sleep 2
#           pid = 14737
#       cmd = sleep 3
#           pid = 14738
#       cmd = sleep 4
#           pid = 14739
#       PID 14737 is done. 3 PIDs remaining.
#       PID 14738 is done. 2 PIDs remaining.
#       PID 14739 is done. 1 PIDs remaining.
#       PID 14736 is done. 0 PIDs remaining.


