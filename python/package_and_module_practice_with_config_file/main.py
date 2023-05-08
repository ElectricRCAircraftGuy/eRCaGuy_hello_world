#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

By Gabriel Staples
7 May 2023

Modified from @Aya's excellent answer here: https://stackoverflow.com/a/16985066/4561887
"""

from my_package.add_strings_as_int import add

# works!
import config
config._test()
print("config.MY_CONSTANT2 = {}".format(config.MY_CONSTANT2))
print()

# also works!
from config import MY_CONSTANT1
print("MY_CONSTANT1 = {}".format(MY_CONSTANT1))
# print("MY_CONSTANT2 = {}".format(MY_CONSTANT2))  # not defined
print()


def main():
    sum = add("1", "1")
    print("sum = {}".format(sum))
    assert sum == 2


if __name__ == '__main__':
    main()
