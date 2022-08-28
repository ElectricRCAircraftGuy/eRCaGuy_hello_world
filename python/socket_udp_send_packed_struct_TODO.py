#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

27 Aug. 2022

Practice packing a binary struct and sending it out over an Ethernet UDP socket!

Status: wip

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint socket_udp_send_packed_struct_TODO.py
```

Run command:
```bash
./socket_udp_send_packed_struct_TODO.py
# OR
python3 socket_udp_send_packed_struct_TODO.py
```

References:
1. ***** https://docs.python.org/3/library/struct.html - Built-in `struct` module:
   "struct — Interpret bytes as packed binary data"

"""


def main():
    """
    The main function of this program.
    """
    print("Hello world!")


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_socket_udp_send_packed_struct_TODO/python$ ./socket_udp_send_packed_struct_TODO.py
    Hello world!

"""
