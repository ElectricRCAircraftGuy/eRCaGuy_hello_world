#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2023

Practice monitoring the keyboard.
Modified from the official example here:
https://pynput.readthedocs.io/en/latest/keyboard.html#monitoring-the-keyboard

Status: done and works to monitor and detect key presses.

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint pynput_monitor_keyboard.py
```

Run command:
```bash
./pynput_monitor_keyboard.py
# OR
python3 pynput_monitor_keyboard.py
```

References:
1. ***** https://pynput.readthedocs.io/en/latest/keyboard.html#monitoring-the-keyboard
1. [my Q] pynput library not working as expected in Python to press Windows + D key

"""

from pynput import keyboard

print("Keyboard monitor demo program. Press Esc to exit.")

def on_press(key):
    try:
        print('alphanumeric key {0} pressed'.format(
            key.char))
    except AttributeError:
        print('special key {0} pressed'.format(
            key))

def on_release(key):
    print('{0} released'.format(
        key))
    if key == keyboard.Key.esc:
        # Stop listener
        print("Exiting the program.")
        return False

# Collect events until released
with keyboard.Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()

# # ...or, in a non-blocking fashion:
# listener = keyboard.Listener(
#     on_press=on_press,
#     on_release=on_release)
# listener.start()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

Notice that ask keys are pressed, the key I pressed is printed to the terminal
(because I pressed the key!)--and the program also detects the key press and
mentions it. That's why you see double output, like `u'u' released`.

    eRCaGuy_hello_world$ python/pynput_keyboard_and_mouse_control/monitor_keyboard.py
    Keyboard monitor demo program. Press Esc to exit.
    Key.enter released
    special key Key.enter pressed

    Key.enter released
    alphanumeric key u pressed
    u'u' released
    alphanumeric key i pressed
    i'i' released
    special key Key.shift pressed
    alphanumeric key O pressed
    O'O' released
    Key.shift released
    special key Key.shift_r pressed
    alphanumeric key T pressed
    T'T' released
    Key.shift_r released
    special key Key.cmd pressed
    Key.cmd released
    special key Key.cmd pressed
    Key.cmd released
    special key Key.cmd pressed
    alphanumeric key d pressed
    'd' released
    alphanumeric key d pressed
    'd' released
    Key.cmd released
    special key Key.esc pressed
    ^[Key.esc released
    Exiting the program.


"""
