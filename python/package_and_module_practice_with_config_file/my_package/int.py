#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

By Gabriel Staples
7 May 2023

Modified from @Aya's excellent answer here: https://stackoverflow.com/a/16985066/4561887
"""

# Exported function
def to_int(a):
    return int(a)

# Test function for module
def _test():
    assert to_int('1') == 1

if __name__ == '__main__':
    _test()
