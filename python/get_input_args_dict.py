#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sep. 2026

Get and print all desired input args passed into a class at construction time.
Status: Done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint get_input_args_dict.py
```

Run command:
```bash
./get_input_args_dict.py
# OR
python3 get_input_args_dict.py
```

References:
1. https://stackoverflow.com/q/44412617/4561887 - see my answer there too

"""


class MyClass:
    def __init__(self, arg1, arg2, arg3, arg_I_dont_care_about, **kwargs):
        # Optional: do any forced conversions that you may need first
        arg1 = float(arg1)
        arg2 = str(arg2)

        # Then, use `locals()` to grab all desired input args
        self.input_args_dict = {
            name: value
            for name, value in locals().items()
            # Exclude any arguments that we don't care about explicitly
            if name not in ["self", "arg_I_dont_care_about", "kwargs"]
        }
        # Now grab just the kwargs and merge them into the input_args_dict
        self.input_args_dict.update(kwargs)

    def get_input_args_dict(self):
        # Return a copy to prevent external modifications to the
        # internal dict
        return self.input_args_dict.copy()


# Example usage

import pprint

myClass = MyClass(
    1, "two", 3, "ignore_this",
    extra1="extra_value", extra2="another_extra_value"
)

input_args_dict = myClass.get_input_args_dict()

print("input_args_dict:")
pprint.pprint(input_args_dict)



# pylint: disable-next=pointless-string-statement
"""
SAMPLE RUN AND OUTPUT:

eRCaGuy_hello_world$ python/get_input_args_dict.py
input_args_dict:
{'arg1': 1.0,
 'arg2': 'two',
 'arg3': 3,
 'extra1': 'extra_value',
 'extra2': 'another_extra_value'}

"""
