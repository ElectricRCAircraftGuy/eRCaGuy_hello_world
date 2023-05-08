#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

By Gabriel Staples
7 May 2023

Modified from @Aya's excellent answer here: https://stackoverflow.com/a/16985066/4561887
"""

from my_package.int import to_int

# Exported function
def add(a, b):
    return to_int(a) + to_int(b)

# Test function for module
def _test():
    assert add('1', '1') == 2

if __name__ == '__main__':
    _test()
