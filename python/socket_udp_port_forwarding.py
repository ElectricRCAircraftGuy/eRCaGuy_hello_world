#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

In some cases, such as when trying to forward UDP packets from your Windows computer to WSL running
on it, it may be useful to set up port forwarding. I'm sure there's a "proper" way to do it, but
here's a quick and dirty way to brute force it using a simple Python script instead.

Status: ("done", but not fully tested yet)

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint socket_udp_port_forwarding.py
```

Run command:
```bash
./socket_udp_port_forwarding.py
# OR
python3 socket_udp_port_forwarding.py
```

References:
1. Bing AI
1. ChatGPT

Prompts I gave to Bing AI:
1. Write me a python program to forward UDP packets from any interface to a specific port, to
   another IP and port.
1. Now add exception handling to gracefully handle the user pressing Ctrl + C to quit.
1. Use a try except instead.


"""

import socket
import sys

INADDR_ANY = "0.0.0.0"  # IP address used to specify to listen on all available network interfaces

# Source IP (host) and port to bind to and listen for incoming UDP packets on.
src_ip = INADDR_ANY
src_port = 1234

# Destination IP (host) and port to forward UDP packets to.
dst_ip = "192.168.1.100"
dst_port = 5678

# Create a socket for receiving UDP packets
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
print(f"Listening for UDP packets on host IP:port {src_ip}:{src_port}...")
sock.bind((src_ip, src_port))

# NOT NECESSARY I THINK; try just re-using the same socket for sending and receiving.
# - TODO: test this to see if using a separate socket for sending might be faster! It's possible
#   that we can operate faster with two separate sockets for receiving and sending.
#   Or, maybe just one socket for both is fine.
# Create a socket for sending UDP packets
# dst_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Loop forever
while True:
    try:
        # Receive a UDP packet from the source (on any interface)
        data, addr = sock.recvfrom(2048)
        print(f"Received {len(data)} bytes from addr {addr}.")

        # Forward the UDP packet to the destination IP and port
        print(f"Forwarding {len(data)} bytes to endpoint {(dst_ip, dst_port)}.")
        sock.sendto(data, (dst_ip, dst_port))
    except KeyboardInterrupt:
        # Handle the user pressing Ctrl + C
        print("\nYou pressed Ctrl + C. Exiting...")
        sock.close()
        # dst_sock.close()
        break

sys.exit(0)


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:
[I still need to fully test this!]

    eRCaGuy_hello_world$ python/socket_udp_port_forwarding.py
    Listening for UDP packets on host IP:port 0.0.0.0:1234...
    ^C
    You pressed Ctrl + C. Exiting...

"""
