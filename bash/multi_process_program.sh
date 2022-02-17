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
# 1. *****+ How I learned that you can use `wait` to read back the return code of a completed
#    subprocess even **after** the subprocess has already completed!
#    https://stackoverflow.com/a/1570356/4561887
# 1. how I first learned the basics of this approach: https://stackoverflow.com/a/356154/4561887
# 1. [Remove an element from a Bash array](https://stackoverflow.com/q/16860877/4561887)

# Run it
#       time ./multi_process_program.sh


# This is a special sleep function which returns the number of seconds slept as
# the "error code" or return code" so that we can easily see that we are in
# fact actually obtaining the return code of each process as it finishes.
my_sleep() {
    seconds_to_sleep="$1"
    sleep "$seconds_to_sleep"
    return "$seconds_to_sleep"
}

# Create an array of whatever commands you want to run as subprocesses
procs=()  # bash array
procs+=("my_sleep 5")
procs+=("my_sleep 2")
procs+=("my_sleep 3")
procs+=("my_sleep 4")

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
#     return_code="$?"
#     echo "PID = $pid; return_code = $return_code"
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

            # 1st, read its return code
            wait "$pid"
            return_code="$?"

            # 2nd, remove this PID from the `pids` array by `unset`ting the
            # element at this index; NB: due to how bash arrays work, this does
            # NOT actually remove this element from the array. Rather, it
            # removes its index from the `"${!pids[@]}"` list of indices,
            # adjusts the array count(`"${#pids[@]}"`) accordingly, and it sets
            # the value at this index to either a null value of some sort, or
            # an empty string (I'm not exactly sure).
            unset "pids[$i]"

            num_pids="${#pids[@]}"
            echo "PID $pid is done; return_code = $return_code;" \
                 "$num_pids PIDs remaining."
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
# OPTION 1 (with Option 2 NOT commented out)
#
#       eRCaGuy_hello_world/bash$ time ./multi_process_program.sh
#       num_procs = 4
#       cmd = my_sleep 5
#           pid = 21694
#       cmd = my_sleep 2
#           pid = 21695
#       cmd = my_sleep 3
#           pid = 21697
#       cmd = my_sleep 4
#           pid = 21699
#       PID = 21694; return_code = 5
#       PID = 21695; return_code = 2
#       PID = 21697; return_code = 3
#       PID = 21699; return_code = 4
#       All 4 processes have ended.
#       PID 21694 is done; return_code = 5; 3 PIDs remaining.
#       PID 21695 is done; return_code = 2; 2 PIDs remaining.
#       PID 21697 is done; return_code = 3; 1 PIDs remaining.
#       PID 21699 is done; return_code = 4; 0 PIDs remaining.
#
#       real    0m5.084s
#       user    0m0.025s
#       sys 0m0.061s
#
#
# OPTION 2 (with Option 1 commented out)
#
#       eRCaGuy_hello_world/bash$ ./multi_process_program.sh
#       num_procs = 4
#       cmd = my_sleep 5
#           pid = 22275
#       cmd = my_sleep 2
#           pid = 22276
#       cmd = my_sleep 3
#           pid = 22277
#       cmd = my_sleep 4
#           pid = 22280
#       PID 22276 is done; return_code = 2; 3 PIDs remaining.
#       PID 22277 is done; return_code = 3; 2 PIDs remaining.
#       PID 22280 is done; return_code = 4; 1 PIDs remaining.
#       PID 22275 is done; return_code = 5; 0 PIDs remaining.
#


