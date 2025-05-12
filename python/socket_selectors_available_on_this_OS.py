#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
May 2025

Goal: use introspection to see which underlying socket selectors (low-level OS-supported socket
utilities, such as on Linux: select, `poll()`, or `epoll()`) are available on a given OS, such as
Linux or Windows. 
- See the references below. 

My prompt to GitHub Copilot: 

> Write me some Python with the selectors module to see what underlying selector I get. I'll run it
on different OSs to see what each OS provides.

Status: Done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint socket_selectors_available_on_this_OS.py
```

Run command:
```bash
./socket_selectors_available_on_this_OS.py
# OR
python3 socket_selectors_available_on_this_OS.py
```

References:
1. https://docs.python.org/3/library/selectors.html [highest level]
1. https://docs.python.org/3/library/select.html    [mid-level]
1. https://docs.python.org/3/library/socket.html    [lowest level]
1. 

"""

import selectors
import sys

def check_and_print_selector():
    """
    Check and print the default selector for the current platform.
    
    This function creates a default selector using the selectors module and prints
    information about the selector, including its class name, module, and available
    selector implementations.
    """

    # Create default selector for this platform. 
    # See: https://docs.python.org/3/library/selectors.html#selectors.DefaultSelector
    default_selector = selectors.DefaultSelector()
    
    # Get information about the selector
    selector_class = default_selector.__class__
    selector_class_name = selector_class.__name__
    selector_class_module = selector_class.__module__
    
    print(f"Python version:                {sys.version}")
    print(f"Platform (OS):                 {sys.platform}")
    print()

    print(f"Default selector class:        {selector_class}")
    print(f"Default selector class module: {selector_class_module}")
    print(f"Default selector class name:   {selector_class_name}")
    
    # Show all available selector implementations
    print("\nAvailable selector implementations on this OS:")
    i = 0
    for name in dir(selectors):
        if name.endswith('Selector'):
            i += 1
            print(f"  {i}. {name}")

    print()

if __name__ == "__main__":
    check_and_print_selector()

"""
Example run and output on Linux Ubuntu 22.04:

    eRCaGuy_hello_world/python$ ./socket_selectors_available_on_this_OS.py 
    Python version:                3.10.12 (main, Feb  4 2025, 14:57:36) [GCC 11.4.0]
    Platform (OS):                 linux

    Default selector class:        <class 'selectors.EpollSelector'>
    Default selector class module: selectors
    Default selector class name:   EpollSelector

    Available selector implementations on this OS:
      1. BaseSelector
      2. DefaultSelector
      3. EpollSelector
      4. PollSelector
      5. SelectSelector
      6. _PollLikeSelector

      
Example run and output on Windows 11:

    eRCaGuy_hello_world/python$ ./socket_selectors_available_on_this_OS.py 
    Python version:                3.12.1 (tags/v3.12.1:2305ca5, Dec  7 2023, 22:03:25) [MSC v.1937 64 bit (AMD64)]
    Platform (OS):                 win32

    Default selector class:        <class 'selectors.SelectSelector'>
    Default selector class module: selectors
    Default selector class name:   SelectSelector

    Available selector implementations on this OS:
      1. BaseSelector
      2. DefaultSelector
      3. SelectSelector
      4. _PollLikeSelector

"""
