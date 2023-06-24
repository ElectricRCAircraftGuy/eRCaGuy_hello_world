#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2023

Get pynput to press Super (Windows) + D to show the desktop.

Status: Done, but does NOT work on Linux Ubuntu 22.04.2, even in the X11 window manager, due to a
bug in pynput.
See:
1. My bug report: https://github.com/moses-palmer/pynput/issues/556
1. My answer here: todo

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint pynput_press_Windows+D_to_show_the_desktop.py
```

Run command:
```bash
./pynput_press_Windows+D_to_show_the_desktop.py
# OR
python3 pynput_press_Windows+D_to_show_the_desktop.py
```

References:
1. My answer: https://askubuntu.com/a/1109490/327339
1. ***** https://pynput.readthedocs.io/en/latest/keyboard.html
1. https://stackoverflow.com/q/63489008/4561887 - How to press the windows key with pynput?
1. my bug report: https://github.com/moses-palmer/pynput/issues/556
1. my Q: https://stackoverflow.com/q/76399361/4561887

"""


import time

from pynput.keyboard import Key, Controller


# ========== technique 1 ===========
# From: https://pynput.readthedocs.io/en/latest/keyboard.html
print("Trying technique 1")

keyboard = Controller()
SUPER_KEY = Key.cmd
with keyboard.pressed(SUPER_KEY):
    keyboard.press('d')
    keyboard.release('d')


time.sleep(1.0)


# ========== technique 2 ===========
print("Trying technique 2")

keyboard = Controller()
SUPER_KEY = Key.cmd

keyboard.press(SUPER_KEY)
keyboard.press('d')
keyboard.release('d')
keyboard.release(SUPER_KEY)


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

Does NOT work right due to a bug, but here's my output nonetheless

    eRCaGuy_hello_world$ python/pynput_keyboard_and_mouse_control/press_Windows+D_to_show_the_desktop.py
    Trying technique 1
    dTrying technique 2


"""
