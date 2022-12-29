#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

27 Aug. 2022

Practice packing a binary struct and sending it out over an Ethernet UDP socket!
- Start by learning how the `struct` modules works in Python, to pack and unpack C-like structs.
  See:
  1. eRCaGuy_hello_world/python/struct_packed.py
  1. https://docs.python.org/3/library/struct.html

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


import socket
import struct


def udp_send():
    print("Sending a packed struct over UDP.")

    # 1. Open a UDP socket to send UDP Ethernet packets

    # A UDP socket is a "Datagram" type (SOCK_DGRAM) over "Address Family: Internet" (AF_INET)
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    UDP_TARGET = ("192.168.0.2", 10000)  # IP and PORT that we will send a packed struct to

    # 2. Create a packed struct of data to send

    # 3. send the packed struct


def udp_listen():
    pass


def main():
    """
    The main function of this program.
    """


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_socket_udp_send_packed_struct_TODO/python$ ./socket_udp_send_packed_struct_TODO.py
    Hello world!

"""
