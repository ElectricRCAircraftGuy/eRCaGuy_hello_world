#!/usr/bin/python3

"""
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
Mar. 2021

Demonstrate how to do basic bytes manipulation and conversion to human-readable strings in Python.
In C and C++, this is common-place for me, and is my "bread and butter". In Python, it's like magic
sauce. I need to document it so I don't forget how it works.

To run this script:
    ./raw_bytes_practice.py
    # OR
    python3 raw_bytes_practice.py

References:
1. bytes
    1. https://docs.python.org/3/library/functions.html
    1. https://docs.python.org/3/library/functions.html#func-bytes
    1. https://docs.python.org/3/library/functions.html#func-bytearray
    1. https://docs.python.org/3/library/stdtypes.html#bytes
    1. https://docs.python.org/3/library/stdtypes.html#bytearray
    1. https://docs.python.org/3/library/stdtypes.html#bytes-methods
    1. https://docs.python.org/3/library/stdtypes.html#bytes.decode
    1. `errors='replace'` error handler: https://docs.python.org/3/library/codecs.html#error-handlers
1. new, format "f" strings: https://realpython.com/python-f-strings/
1. textwrap [my answer] https://stackoverflow.com/questions/10985603/multi-line-string-with-arguments-how-to-declare/64437283#64437283

"""

import textwrap
import time


print()

full_uint8_t_range = list(range(0, 256))
print(f"full_uint8_t_range = \n{full_uint8_t_range}\n")

bytes_buffer = bytes(full_uint8_t_range)
print(f"bytes_buffer = \n{bytes_buffer}\n")

# The following will produce a decoding error, so catch and print it
try:
    # See: https://docs.python.org/3/library/stdtypes.html#bytes.decode
    # Default args to `decode()` are: `encoding="utf-8", errors="strict"`.
    bytes_buffer_str = bytes_buffer.decode()
except UnicodeDecodeError as e:
    print(f"{e}")
    char128 = bytes_buffer[128]
    print(textwrap.dedent(f"""\
        This error means that position 128 in the `bytes_buffer` contains an invalid unicode 'utf-8'
        character and cannot be decoded. That character is decimal {char128} ({hex(char128)}).\
        \n"""))
else:
    # this will NOT be reached
    print("No exceptions occurred.")

# This will work just fine though! Note, one of these chars is the ASCII "bell" char (`\a'), so it
# will make that sound when the below code prints.
# See here for the meaning of 'replace':
# https://docs.python.org/3/library/codecs.html#error-handlers
# - 'replace' will replace all non-utf-8 chars with this replacement question mark char to indicate
# the char is non-printable and not a valid utf-8 char!: `�`
bytes_buffer_str1 = bytes_buffer.decode(encoding='utf-8', errors='replace')
print(f"bytes_buffer_str1 = \n{bytes_buffer_str1}\n")

print("About to make the bell char ('\\a') sound again.")
time.sleep(0.5)
print("Printing '\\a' here. \a")
print("Did it!")
print("Ok, printing the above bytes_buffer_str again as ASCII now:\n")
time.sleep(0.5)

# Do it again, as ASCII this time. ASCII is a valid subset of utf-8, so you'll see no difference,
# in this case, to the above print). Note that utf-8 is always preferred, in case non-ASCII
# utf-8 chars exist in any buffer too.
bytes_buffer_str2 = bytes_buffer.decode(encoding='ascii', errors='replace')
print(f"bytes_buffer_str2 = \n{bytes_buffer_str2}\n")

print("bytes_buffer_str1 == bytes_buffer_str2 ?: {}\n".format(bytes_buffer_str1 == bytes_buffer_str2))

# Ok, this time get the bytes buffer string again but use the 'backslashreplace' error handler
# to replace all invalid chars with their backslashed hex number!
# See: https://docs.python.org/3/library/codecs.html#error-handlers
bytes_buffer_str3 = bytes_buffer.decode(encoding='utf-8', errors='backslashreplace')
print(f"[BEST PRINTING OPTION I THINK!] bytes_buffer_str3 = \n{bytes_buffer_str3}\n")

### WORK IN PROGRESS FROM HERE ON ######
# Ok, now turn a bytes buffer string back into a bytes buffer!
bytes_buffer3 = bytes(bytes_buffer_str3, encoding='utf-8', errors='namereplace')
print(f"bytes_buffer3 = \n{bytes_buffer3}\n")
print(bytes_buffer_str3.encode())
print(bytes_buffer_str3.encode(errors='backslashreplace'))
print(bytes_buffer_str3.encode())


# print(encode(bytes_buffer_str3))
from codecs import encode
print(encode(bytes_buffer_str3, "raw_unicode_escape"))
