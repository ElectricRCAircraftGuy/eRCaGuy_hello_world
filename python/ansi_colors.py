#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
Sept. 2024

Add ANSI color codes to strings for terminal output.
Status: WORKS!

vvvvvvvvvvvvvvvvvvvvvvv
SEE ALSO: 
https://github.com/ElectricRCAircraftGuy/eRCaGuy_PathShortener/blob/main/ansi_colors.py
^^^^^^^^^^^^^^^^^^^^^^^

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint ansi_colors.py
```

Run command:
```bash
./ansi_colors.py
# OR
python3 ansi_colors.py
```

Example usage in your own Python code:
```python
import ansi_colors as colors

print(f"{colors.FGR}This text is green.{colors.END}")
print(f"{colors.FBB}This text is bright blue.{colors.END}")
```

References:
1. ORIGINAL COPIED FROM MY OTHER WORK HERE: 
   https://github.com/ElectricRCAircraftGuy/eRCaGuy_PathShortener/blob/main/ansi_colors.py
1. ...Which borrowed from my file here: 
   https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/python/pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py
1. *****+ https://github.com/ElectricRCAircraftGuy/eRCaGuy_PathShortener/blob/main/ansi_colors.py
1. 

"""


# For text formatting and colorization in the terminal.
# See:
# 1. My ANSI format library here:
#    https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/ansi_text_format_lib.sh
# 1. https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit

ANSI_START = "\033["    # start of an ANSI formatting sequence

ANSI_FG_GRE = ";32"     # foreground color green
ANSI_FG_BLU = ";34"     # foreground color blue
ANSI_FG_BR_BLU = ";94"  # foreground color bright blue
ANSI_FG_RED = ";31"     # foreground color red
ANSI_FG_BR_RED = ";91"  # foreground color bright red

ANSI_END = "m"          # end of an ANSI formatting sequence

ANSI_OFF = f"{ANSI_START}{ANSI_END}"
F = ANSI_OFF    # alias
END = ANSI_OFF  # alias

FGR = f"{ANSI_START}{ANSI_FG_GRE}{ANSI_END}"     # green text
FBL = f"{ANSI_START}{ANSI_FG_BLU}{ANSI_END}"     # blue text
FBB = f"{ANSI_START}{ANSI_FG_BR_BLU}{ANSI_END}"  # bright blue text
FRE = f"{ANSI_START}{ANSI_FG_RED}{ANSI_END}"     # red text
FBR = f"{ANSI_START}{ANSI_FG_BR_RED}{ANSI_END}"  # bright red text


def print_red(*args, **kwargs):
    """
    Print the arguments in bright red text.
    - Accepts all the same arguments as the built-in `print()` function.
    """
    
    # NOT QUITE RIGHT
    # print(f"{colors.FRE}", *args, f"{colors.END}", **kwargs)
    
    # ALSO NOT QUITE RIGHT
    # print(f"{colors.FRE}" + args[0], args[1:], f"{colors.END}", **kwargs)

    # Works!
    # Concatenate the red color code with each argument
    colored_args = [f"{FBR}{arg}{END}" for arg in args]
    # Print the colored arguments
    print(*colored_args, **kwargs)


def run_tests():
    # Test the colors
    
    print(f"{FGR}This text is green.{END}")
    print(f"{FBB}This text is bright blue.{END}")
    
    print_red("This text is bright red.")
    print_red("This text", "is bright red.")
    print_red("This text", "is", "bright", "red.")
    
    print_red("This text", "is", end=" ")  # end with a space instead of a newline
    print_red("bright", "red.")

    print_red("This text", "is")
    print_red("  bright", "red.")


if __name__ == "__main__":
    run_tests()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

eRCaGuy_hello_world/python$ ./ansi_colors.py 
This text is green.
This text is bright blue.
This text is bright red.
This text is bright red.
This text is bright red.
This text is bright red.
This text is
  bright red.


"""
