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
# 1.

kill_beep() {
    if [[ -n "$beep_pid" ]]; then
        kill "$beep_pid"
    fi
}

alarm_timer() {
    seconds="$1"
    text="$2"

    echo "Sleeping for $seconds sec."
    sleep "$seconds"

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

    echo ">>> Reminder: $text <<<"
    echo "Press OK in the popup window to stop the alarm (or press Ctrl + C)."

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
#       eRCaGuy_hello_world$ bash/alarm_lib.sh 
#       Running main.
#       Running unit tests.
#       Sleeping for 1 sec.
#       Sounding alarm!
#       >>> Reminder: Feed the cat! <<<
#       Press OK in the popup window to stop the alarm (or press Ctrl + C).
#
#
# 2) WHEN SOURCED
#
#       eRCaGuy_hello_world$ . bash/alarm_lib.sh
#       eRCaGuy_hello_world$ alarm_timer 1 "Check the mail"
#       Sleeping for 1 sec.
#       Sounding alarm!
#       [1] 123568
#       >>> Reminder: Check the mail <<<
#       Press OK in the popup window to stop the alarm (or press Ctrl + C).
#       ^C
#       [1]+  Terminated              while true; do
#           echo -en "\a"; sleep 0.15;
#       done
