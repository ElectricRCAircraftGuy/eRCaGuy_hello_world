#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Jan. 2024
# 
# Create a timer/alarm **library** I can easily call! Ex:
# ```bash
# . alarm_lib.sh  # source (import) it
# alarm_timer 600 "Feed the cat!" # set a 10 minute alarm to remind you to feed the cat
# ```
# 
# STATUS: Done and works!

# keywords to easily grep or ripgrep in this repo for this program and what it teaches
#
# KEYWORDS: bash bell alarm clock countdown timer stop watch zenity popup window
# beep

# Check this script with:
#
##      shellcheck bash/alarm.sh
#
# Run command:
#
#       bash/alarm.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/alarm.sh

# References:
# 1. MY ANSWER WITH THIS CODE: //////
# 1. My answer: math in Bash: https://stackoverflow.com/a/71567705/4561887

kill_beep() {
    if [[ -n "$beep_pid" ]]; then
        kill "$beep_pid"
    fi
}

min() {
    if (( "$1" <= "$2" )); then
        echo "$1"
    else
        echo "$2"
    fi
}

# Set a timer to go off in a certain number of minutes, and then play a sound
# and pop up a notification when the timer goes off.
#
# Example usage:
#
#       # set a 10 minute alarm to remind you to feed the cat
#       alarm_timer 600 "Feed the cat!" 
#       # OR (same thing)
#       alarm_timer 600 Feed the cat!
alarm_timer() {
    total_whole_sec_to_sleep="$1"
    # store all remaining args into a single string
    text="${@:2}"

    echo "Sleeping for $total_whole_sec_to_sleep sec."
    SLEEP_INTERVAL_SEC=10
    elapsed_seconds=0
    while (( "$elapsed_seconds" < "$total_whole_sec_to_sleep" )); do
        seconds_remaining="$(( total_whole_sec_to_sleep - elapsed_seconds ))"
        sec_to_sleep_this_iteration="$(min "$SLEEP_INTERVAL_SEC" "$seconds_remaining")"
        # echo "sec_to_sleep_this_iteration=$sec_to_sleep_this_iteration" # debugging
        
        sleep "$sec_to_sleep_this_iteration"
        if [[ "$?" -ne 0 ]]; then
            echo "ERROR: sleep command failed! Exiting."
            echo "Proper usage: 'alarm_timer <total_whole_sec_to_sleep> <text>'"
            return 1
        fi

        elapsed_seconds="$(( elapsed_seconds + sec_to_sleep_this_iteration ))"
        echo -n "$elapsed_seconds..."
    done

    echo "Sounding alarm!"

    # trap Ctrl + C
    beep_pid=""
    trap "
        echo -e '\n\nCaught Ctrl + C! Exiting...'; 
        kill_beep;
        " SIGINT

    # Run the beep command in the background, and save its PID in a variable
    while true; do
        echo -en "\a"
        sleep 0.15
    done & beep_pid="$!"

    echo -e "\n>>> Reminder: $text <<<\n"
    echo "Press OK (or press Enter) in the popup window to stop the alarm,"
    echo "or click back into this terminal and press Ctrl + C."

    # Open a popup window with the reminder title and text
    zenity --info --title "Reminder" --text "$text"

    # Kill the beep command once the user has closed the popup window above
    kill "$beep_pid"
}

run_tests() {
    echo "Running unit tests."

    # Test 1
    alarm_timer 1 "Feed the cat!"
}

main() {
    echo "Running main."
    run_tests "$@"
}

# Determine if the script is being sourced or executed (run).
# See:
# 1. "eRCaGuy_hello_world/bash/if__name__==__main___check_if_sourced_or_executed_best.sh"
# 1. My answer: https://stackoverflow.com/a/70662116/4561887
if [ "${BASH_SOURCE[0]}" = "$0" ]; then
    # This script is being run.
    __name__="__main__"
else
    # This script is being sourced.
    __name__="__source__"
fi

# Only run `main` if this script is being **run**, NOT sourced (imported).
# - See my answer: https://stackoverflow.com/a/70662116/4561887
if [ "$__name__" = "__main__" ]; then
    main "$@"
fi


# SAMPLE OUTPUT:
#
# 1) WHEN RUN
#
#       eRCaGuy_hello_world$ $ bash/alarm_lib.sh 
#       Running main.
#       Running unit tests.
#       Sleeping for 1 sec.
#       1...Sounding alarm!
#       
#       >>> Reminder: Feed the cat! <<<
#       
#       Press OK (or press Enter) in the popup window to stop the alarm,
#       or click back into this terminal and press Ctrl + C.
#
#
# 2) WHEN SOURCED
#
#       eRCaGuy_hello_world$ . bash/alarm_lib.sh
#       eRCaGuy_hello_world$ alarm_timer 1 Check the mail!
#       Sleeping for 1 sec.
#       1...Sounding alarm!
#       [1] 129413
#       
#       >>> Reminder: Check the mail! <<<
#       
#       Press OK (or press Enter) in the popup window to stop the alarm,
#       or click back into this terminal and press Ctrl + C.
#       [1]+  Terminated              while true; do
#           echo -en "\a"; sleep 0.15;
#       done

