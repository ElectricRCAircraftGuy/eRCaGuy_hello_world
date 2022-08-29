#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
28 Aug. 2022

Practice using the built-in Python `struct` module to pack (serialize) and unpack (deserialize) data
into C-like structs.
See: https://docs.python.org/3/library/struct.html

Status: done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint struct_packed.py
```

Run command:
```bash
./struct_packed.py
# OR
python3 struct_packed.py
```

References:
1. ***** https://docs.python.org/3/library/struct.html

"""


import struct


def main():
    """
    The main function of this program.
    """
    print("Struct packing (serializing) and unpacking (deserializing) demo.\n")

    # See the official documentation: https://docs.python.org/3/library/struct.html

    # ----------------------------------------------------------------------------------------------
    print("== Option 1. pack a struct using the global functions. ==\n")
    # ----------------------------------------------------------------------------------------------

    print("A: native byte order with padding.")
    # Alignment and padding:
    #   @ = native endianness and native alignment and padding
    # Data types:
    #   B = uint8_t
    #   I = uint32_t
    # Explanation:
    # 16 bytes: 4 bytes for the uint8_t (1 byte + 3 bytes padding) + 3 uint32_ts at 4 bytes each.
    # Little-endian (think: "little beginnian": least-significant byte FIRST), since that's the
    # native byte order on my x86-64 Linux architecture.
    format_string = "@BIII"
    data_a = struct.pack(format_string, 255, 1, 2, 3)  # a `bytes` object
    num_bytes = struct.calcsize(format_string)
    print(f"Num bytes = {num_bytes}")
    print(f"data = {data_a}\n")

    print("B: native byte order withOUT padding.")
    format_string = "=BIII"
    data_b = struct.pack(format_string, 255, 1, 2, 3)  # a `bytes` object
    num_bytes = struct.calcsize(format_string)
    print(f"Num bytes = {num_bytes}")
    print(f"data = {data_b}\n")

    print("C: network (big-endian) byte order withOUT padding.")
    format_string = "!BIII"
    data_c = struct.pack(format_string, 255, 1, 2, 3)  # a `bytes` object
    num_bytes = struct.calcsize(format_string)
    print(f"Num bytes = {num_bytes}")
    print(f"data = {data_c}\n")

    print("Unpacking the last struct.")
    (byte_1, uint32_1, uint32_2, uint32_3) = struct.unpack(format_string, data_c)
    print("(byte_1, uint32_1, uint32_2, uint32_3) = " +
         f"({byte_1}, {uint32_1}, {uint32_2}, {uint32_3})\n\n")

    # ----------------------------------------------------------------------------------------------
    print("== Option 2. pack a struct using a `struct.Struct` class. ==\n" +
          "Note: the only thing extra this technique really does is store the `format` string\n" +
          "internally, so you don't have to manually pass it to every function call!\n")
    # ----------------------------------------------------------------------------------------------
    # This technique is more efficient because it requires converting the format string into an
    # underlying C-struct only **once*. See: https://docs.python.org/3/library/struct.html#classes:
    #
    # > Creating a Struct object once and calling its methods is more efficient than calling the
    #   struct functions with the same format since the format string only needs to be compiled
    #   once.

    print("C: network (big-endian) byte order withOUT padding.")
    format_string = "!BIII"
    struct_class_object = struct.Struct(format_string)
    data_2c = struct_class_object.pack(255, 1, 2, 3)
    print(f"Num bytes = {struct_class_object.size}")
    # Note: "Changed in version 3.7: The format string type is now str instead of bytes."
    print(f"Format string = {struct_class_object.format}")
    print(f"data = {data_2c}\n")

    print("Unpacking the first option's last struct (data_c), and the last struct (data_2c)\n" +
          "using the struct_class_object.")
    # data_c
    (byte_1, uint32_1, uint32_2, uint32_3) = struct_class_object.unpack(data_c)
    print("(byte_1, uint32_1, uint32_2, uint32_3) = " +
         f"({byte_1}, {uint32_1}, {uint32_2}, {uint32_3})")
    # data_2c
    (byte_1, uint32_1, uint32_2, uint32_3) = struct_class_object.unpack(data_2c)
    print("(byte_1, uint32_1, uint32_2, uint32_3) = " +
         f"({byte_1}, {uint32_1}, {uint32_2}, {uint32_3})\n\n")

    # prove that the data object packed by the global functions is the same as the one packed by the
    # class
    print(data_c == data_2c)  # True
    # and these also are the same
    print(struct.pack("!BIII", 255, 1, 2, 3) == struct.pack(">BIII", 255, 1, 2, 3))  # True
    # but these are different **for my system**, since data_b is "native" byte order
    # (little-endian for x86-64 Linux architecture), whereas data_c is network (big-endian) byte
    # order
    print(data_b == data_c)  # False for my system


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./struct_packed.py
    Struct packing (serializing) and unpacking (deserializing) demo.

    == Option 1. pack a struct using the global functions. ==

    A: native byte order with padding.
    Num bytes = 16
    data = b'\xff\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00'

    B: native byte order withOUT padding.
    Num bytes = 13
    data = b'\xff\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00'

    C: network (big-endian) byte order withOUT padding.
    Num bytes = 13
    data = b'\xff\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03'

    Unpacking the last struct.
    (byte_1, uint32_1, uint32_2, uint32_3) = (255, 1, 2, 3)


    == Option 2. pack a struct using a `struct.Struct` class. ==
    Note: the only thing extra this technique really does is store the `format` string
    internally, so you don't have to manually pass it to every function call!

    C: network (big-endian) byte order withOUT padding.
    Num bytes = 13
    Format string = b'!BIII'
    data = b'\xff\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03'

    Unpacking the first option's last struct (data_c), and the last struct (data_2c)
    using the struct_class_object.
    (byte_1, uint32_1, uint32_2, uint32_3) = (255, 1, 2, 3)
    (byte_1, uint32_1, uint32_2, uint32_3) = (255, 1, 2, 3)


    True
    True
    False

"""
