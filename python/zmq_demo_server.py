#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
22 June 2023

Run the basic Zero MQ demo for Python, here: https://zeromq.org/languages/python/
GS note: whether you start the client first or the server first makes no difference. It works the
same either way.

Status: done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint zmq_demo_server.py
```

Run command:
```bash
# First, install zmq
pip install pyzmq

./zmq_demo_server.py
# OR
python3 zmq_demo_server.py
```

References:
1. This code has been modified from here: https://zeromq.org/languages/python/

"""


#   https://zeromq.org/languages/python/
#
#   Hello World server in Python
#   Binds REP socket to tcp://*:5555
#   Expects b"Hello" from client, replies with b"World"
#

import time
import zmq

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

print("Starting ZMQ server. Waiting for client.")

while True:
    #  Wait for next request from client
    message = socket.recv()
    print("Received request: %s" % message)

    #  Do some 'work'
    time.sleep(1)

    #  Send reply back to client
    socket.send(b"World")



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

Note: I hit Ctrl + C at the end to kill it.

    eRCaGuy_hello_world$ python/zmq_demo_server.py
    Starting ZMQ server. Waiting for client.
    Received request: b'Hello'
    Received request: b'Hello'
    Received request: b'Hello'
    Received request: b'Hello'
    Received request: b'Hello'
    Received request: b'Hello'
    Received request: b'Hello'
    Received request: b'Hello'
    Received request: b'Hello'
    Received request: b'Hello'
    ^CTraceback (most recent call last):
    File "/home/gabriel/GS/dev/eRCaGuy_hello_world/python/zmq_demo_server.py", line 60, in <module>
        message = socket.recv()
    File "zmq/backend/cython/socket.pyx", line 805, in zmq.backend.cython.socket.Socket.recv
    File "zmq/backend/cython/socket.pyx", line 841, in zmq.backend.cython.socket.Socket.recv
    File "zmq/backend/cython/socket.pyx", line 194, in zmq.backend.cython.socket._recv_copy
    File "zmq/backend/cython/checkrc.pxd", line 13, in zmq.backend.cython.checkrc._check_rc
    KeyboardInterrupt


"""
