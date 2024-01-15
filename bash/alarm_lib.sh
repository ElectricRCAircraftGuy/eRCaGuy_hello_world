#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Jan. 2024
# 
# Create a timer/alarm. Ex:
# 
# Sleep 600 seconds (10 minutes), then beep forever until you click "OK" in
# the popup window
#
# STATUS: wip

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


sleep 1  # sleep 1 second; set this to the alarm duration that you want!

# Run the beep command in the background, and save its PID in a variable
while true; do
    echo -en "\a"
    sleep 0.15
done & beep_pid="$!"

# Open a popup window with the reminder title and text
zenity --info --title "Reminder" --text "Feed the cat!"

# Kill the beep command once the user has closed the popup window above
kill "$beep_pid"


main() {
    echo "Running main."
    # Add your main function code here
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


# SAMPLE RUN AND OUTPUT:
# 
#       eRCaGuy_hello_world$ bash/alarm.sh
# 
# [No output; a popup window appears with the title "Reminder" and the text
# "Feed the cat!", and it beeps forever until you click "OK" in the popup
# window]. 
# 
