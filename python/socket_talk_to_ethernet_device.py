#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Nov. 2021

Demonstrate how to use the built-in Ethernet `socket` module to communicate with an
Ethernet-controlled device (UDP or TCP can be used; this example shows TCP). This is very useful
for controlling and talking to laboratory equipment, for instance, such as digital power supplies,
multimeters, etc.

References:
1. [Official Python3 documentation] https://docs.python.org/3/library/socket.html
    1. Examples: https://docs.python.org/3/library/socket.html#example

Run command:

        ./socket_talk_to_ethernet_device.py

  OR:

        python3 socket_talk_to_ethernet_device.py

"""

import socket


# Note: `socket.SOCK_STREAM` is usually used with TCP and `socket.SOCK_DGRAM` is usually used with
# UDP. See: https://stackoverflow.com/a/10810040/4561887
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

HOST = '192.168.0.1'
PORT = 9999
s.connect((HOST, PORT))
s.settimeout(1)

# 1. Send a text command to the device you are controlling
s.sendall("my command to send".encode())
# OR (same thing--specify the command as a byte array object directly)
s.sendall(b"my command to send")
# OR (same thing)
cmd = "my command to send"
s.sendall(cmd.encode())

# 2. Read the response back from the device, up to this many bytes from the receive buffer
s.recv(4096)

# Close the connection when done. Leaving a TCP connection open in an infinite loop, for instance,
# will block other users on the computer from opening a socket to communicate with the same device.
s.close()


"""
SAMPLE OUTPUT:



"""
