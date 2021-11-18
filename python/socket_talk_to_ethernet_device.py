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
    1. See other examples here: https://docs.python.org/3/library/socket.html#example  <========
1. Netcat timeout in floating point < 1 second: https://unix.stackexchange.com/a/492796/114401
1. [my Q&A on using `printf` instead of `echo` with netcat (`nc`)]
   https://stackoverflow.com/q/70001189/4561887

Run command:
        ./socket_talk_to_ethernet_device.py
  OR:
        python3 socket_talk_to_ethernet_device.py

Note:
1. `netcat` (`nc`) can be used at the command-line to do essentially the same thing as the code
below over TCP like this.

        printf '%s' "my command to send" | timeout 0.2 nc 192.168.0.1 9999

- Note: do NOT use `echo` in place of `printf` above, as `echo` appends a trailing newline character
  (`\n`) which can mess up parsing. `echo` is also not very portable and has other limitations such
  as being unable to send a string which begins with `-`.
  - [See my detailed answer here]: https://stackoverflow.com/a/70001270/4561887

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
#   s.sendall(b"my command to send")
# OR (same thing)
#   cmd = "my command to send"
#   s.sendall(cmd.encode())

# 2. Read the response back from the device, up to this many bytes from the receive buffer
data = s.recv(4096)

print('Received', repr(data))
# alternative way to print
print('Received ', end='')
print(data)

# Close the connection when done. Leaving a TCP connection open in an infinite loop, for instance,
# will block other users on the computer from opening a socket to communicate with the same device.
s.close()



"""
SAMPLE OUTPUT:

Received b'some response string from the device here\n'
Received b'some response string from the device here\n'

"""
