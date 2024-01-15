#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Jan. 2024
# 
# Sleep 600 seconds (10 minutes), then beep forever until you click "OK" in
# the popup window
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


# SAMPLE RUN AND OUTPUT:
# 
#       eRCaGuy_hello_world$ bash/alarm.sh
# 
# [No output; a popup window appears with the title "Reminder" and the text
# "Feed the cat!", and it beeps forever until you click "OK" in the popup
# window]. 
# 
