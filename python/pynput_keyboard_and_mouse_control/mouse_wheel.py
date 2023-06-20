#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
3 June 2023

Learn to detect mouse scroll wheel events, and create them, using the `pynput`
library.

Status: detecting mouse scroll wheel events is done!
Creating them is not.
When detecting them, in Wayland, there are problems. It detects the mouse scroll wheel events in
Chrome, but not in programs like the terminal or Sublime Text.
In X11, it all works fine.
See my comment here:
https://github.com/albertz/mouse-scroll-wheel-acceleration-userspace/issues/8#issuecomment-1575389079


keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint pynput_mouse_wheel.py
```

Run command:
```bash
./pynput_mouse_wheel.py
# OR
python3 pynput_mouse_wheel.py
```

References:
1. ***** pynput:
    1. https://pypi.org/project/pynput/
    1. https://github.com/moses-palmer/pynput
    1. https://pynput.readthedocs.io/en/latest/
1. https://github.com/albertz/mouse-scroll-wheel-acceleration-userspace


"""

# DETECT MOUSE SCROLL WHEEL EVENTS.
# modified from here: https://pypi.org/project/pynput/

# See my notes on my below code, here:
# https://github.com/albertz/mouse-scroll-wheel-acceleration-userspace/issues/8#issuecomment-1575389079

from pynput import mouse

def on_scroll(x, y, dx, dy):
    print('Scrolled {}; (x, y)=({:4d}, {:4d}); (dx, dy)={}'.format(
        'down' if dy < 0 else 'up  ',
        x, y,
        (dx, dy),
    ))

# block the main thread, listening
# Collect events until released
with mouse.Listener(
        on_scroll=on_scroll) as listener:
    listener.join()



# def main():
#     """
#     The main function of this program.
#     """
#     print("Hello world!")


# # Only run `main()` if this script is **run**, NOT imported
# if __name__ == '__main__':
#     main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python/pynput_keyboard_and_mouse_control/pynput_mouse_wheel.py
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled up  ; (x, y)=(2948, 1508); (dx, dy)=(0, 1)
    Scrolled up  ; (x, y)=(2948, 1508); (dx, dy)=(0, 1)
    Scrolled up  ; (x, y)=(2948, 1508); (dx, dy)=(0, 1)
    Scrolled up  ; (x, y)=(2948, 1508); (dx, dy)=(0, 1)
    Scrolled up  ; (x, y)=(2948, 1508); (dx, dy)=(0, 1)
    Scrolled up  ; (x, y)=(2948, 1508); (dx, dy)=(0, 1)
    Scrolled up  ; (x, y)=(2948, 1508); (dx, dy)=(0, 1)
    Scrolled up  ; (x, y)=(2948, 1508); (dx, dy)=(0, 1)
    Scrolled up  ; (x, y)=(2948, 1508); (dx, dy)=(0, 1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2948, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2947, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2947, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2947, 1508); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2946, 1509); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2946, 1509); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(2946, 1509); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(4775, 1458); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(4775, 1458); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(4775, 1458); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(4775, 1458); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(4775, 1458); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(4775, 1458); (dx, dy)=(0, -1)
    Scrolled up  ; (x, y)=(4775, 1458); (dx, dy)=(0, 1)
    Scrolled up  ; (x, y)=(4775, 1458); (dx, dy)=(0, 1)
    Scrolled up  ; (x, y)=(4775, 1458); (dx, dy)=(0, 1)
    Scrolled down; (x, y)=(4775, 1458); (dx, dy)=(0, -1)
    Scrolled down; (x, y)=(4775, 1458); (dx, dy)=(0, -1)


"""
