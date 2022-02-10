#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Feb. 2022

# Learn to securely send text to your phone via the phone's camera through a QR code (same as
# how 2-factor-authentication pre-shared keys are sent to a phone via QR codes)

# Run command:
#       sudo apt update
#       sudo apt install qrencode feh
#
#       ./qrencode_send_text_to_phone.sh

# References:
# 1. Google search for "linux qr code generator"
#    https://www.google.com/search?q=linux+qr+code+generator&oq=linux+qr+code+generator&aqs=chrome..69i57.20404j0j4&client=ms-android-google&sourceid=chrome-mobile&ie=UTF-8
#   1. https://www.linux-magazine.com/Online/Features/Generating-QR-Codes-in-Linux
# 1. https://stackoverflow.com/a/59521674/4561887
# 1. [my answer about this] https://stackoverflow.com/a/70934014/4561887
# 1. How to get path to the running script [my answer]: https://stackoverflow.com/a/60157372/4561887
# 1. Max input file size for QR codes:
#    https://github.com/fukuchi/libqrencode/issues/31#issuecomment-1034603750

# See my answer: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_THIS_SCRIPT="$(realpath "$0")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_THIS_SCRIPT")"
filename_to_encode="${SCRIPT_DIRECTORY}/qrcode_input.txt"

# Option 1: save as an image and open in Ubuntu's default `eog` (Eye of Gnome) image viewer.
echo "Running Option 1 (close the open windows to get the next option to run)"
cat "$filename_to_encode" | qrencode -m 4 -o "${SCRIPT_DIRECTORY}/qrcode.png"
eog "${SCRIPT_DIRECTORY}/qrcode.png"

# Option 2: pipe directly to the `feh` image viewer (this uses temporary files anyway, under the
# hood).
# See:
#   1. https://stackoverflow.com/a/59521674/4561887
#   1. [my answer]
echo "Running Option 2 (close the open windows to get the next option to run)"
cat "$filename_to_encode" | qrencode -m 4 -o "-" | feh -

# Option 3 [BEST]: create your own temporary files and use eog anyway:
echo "Running Option 3"
cat "$filename_to_encode" | qrencode -m 4 -o "/tmp/qrcode.png"
# Use `&` to run in background so that the `rm` cmd next runs **immediately!**
eog "/tmp/qrcode.png" &
sleep 1
rm "/tmp/qrcode.png"

## [BEST 1-LINE ANSWER FOR A FILE]
echo "1-line Demo 4: See my answer here: https://stackoverflow.com/a/70934014/4561887"
cat "$filename_to_encode" | qrencode -m 4 -o /tmp/qr.png \
&& ((eog /tmp/qr.png &); sleep 1; rm /tmp/qr.png)

sleep 2

## [BEST 1-LINE ANSWER FOR A URL]
echo "1-line Demo 5: See my answer here: https://stackoverflow.com/a/70934014/4561887"
qrencode -o /tmp/qr2.png "www.google.com" \
&& ((eog /tmp/qr2.png &); sleep 1; rm /tmp/qr2.png)


# SAMPLE OUTPUT:
#
# (run it yourself to see the images)
# Here is the text output:
#
#       eRCaGuy_hello_world$ bash/qrencode_send_text_to_phone.sh
#       Running Option 1 (close the open windows to get the next option to run)
#       Running Option 2 (close the open windows to get the next option to run)
#       Running Option 3
#       1-line Demo 4: See my answer here: https://stackoverflow.com/a/70934014/4561887
#       1-line Demo 5: See my answer here: https://stackoverflow.com/a/70934014/4561887

