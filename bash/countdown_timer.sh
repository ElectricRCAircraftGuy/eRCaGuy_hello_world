#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Dec. 2021
#
# Make a countdown timer.
#
# Run cmd:
#       ./countdown_timer.sh
#   OR
#       time ./countdown_timer.sh
#
#
# References:
# 1. https://linuxize.com/post/bash-for-loop/
# 1. https://www.cyberciti.biz/faq/how-to-display-countdown-timer-in-bash-shell-script-running-on-linuxunix/


# -----------------------
# Countdown 10 seconds
# -----------------------

for i in {10..1}; do
    printf "%s" "$i"
    sleep 1
    if [ "$i" -gt "0" ]; then
        printf "%s" " "
    fi
done
printf "\n"

# -----------------------
# Now make it a function and try it again!
# -----------------------

# Count down `n` whole seconds.
# Usage: `countdown_timer n`
# Ex:    `countdown_timer 20`
countdown_timer() {
    n_sec="$1"

    # C-style Bash "for loop"
    # See: https://linuxize.com/post/bash-for-loop/
    for ((i = n_sec; i > 0; i--)); do
        printf "%s" "$i"
        sleep 1
        if [ "$i" -gt "0" ]; then
            printf "%s" " "
        fi
    done
    printf "\n"
}

printf "\n"
countdown_timer 20


# -----------------------
# SAMPLE OUTPUT (this takes 30 seconds to print out):
# -----------------------

#    eRCaGuy_hello_world/bash$ time ./countdown_timer.sh
#    10 9 8 7 6 5 4 3 2 1
#
#    20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
#
#    real    0m30.083s
#    user    0m0.045s
#    sys 0m0.037s


