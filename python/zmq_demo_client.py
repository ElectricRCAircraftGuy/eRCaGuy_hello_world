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
pylint zmq_demo_client.py
```

Run command:
```bash
# First, install zmq
pip install pyzmq

./zmq_demo_client.py
# OR
python3 zmq_demo_client.py
```

References:
1. This code has been modified from here: https://zeromq.org/languages/python/

"""


#   https://zeromq.org/languages/python/
#
#   Hello World client in Python
#   Connects REQ socket to tcp://localhost:5555
#   Sends "Hello" to server, expects "World" back
#

import zmq

context = zmq.Context()

#  Socket to talk to server
print("Connecting to hello world server…")
# Use a "Request" **synchronous** socket type; see: https://zeromq.org/socket-api/: "ZeroMQ patterns
# are implemented by pairs of sockets with matching types."
socket = context.socket(zmq.REQ)
# GS: use `connect()` instead of `bind()` on what you might consider the more "dynamic component",
# ie: the client. "As a general rule use bind from the most stable points in your architecture, and
# use connect from dynamic components with volatile endpoints."
# - See: https://zeromq.org/socket-api/
#   - "Bind vs Connect" and its sub-section, "When should I use bind and when connect?"
# - See documentation for `zmq.Socket.connect()` here:
#   https://pyzmq.readthedocs.io/en/latest/api/zmq.html#zmq.Socket.connect
#   - format: `protocol://interface:port`.
#       - Supported protocols are `tcp`, `udp`, `pgm`, `inproc`, and `ipc`.
#       - Note that `localhost` is equivalent to interface `127.0.0.1`.
socket.connect("tcp://localhost:5555")

#  Do 10 requests, waiting each time for a response
for request_num in range(10):
    print("Sending request_num %s …" % request_num)
    # GS: a REQ socket type MUST send first. It cannot go into receive mode until it sends first.
    # - See: https://zeromq.org/socket-api/: "Send/receive pattern: Send, Receive, Send, Receive, …"
    socket.send(b"Hello")

    #  Get the reply.
    message = socket.recv()
    print("Received reply %s [ %s ]" % (request_num, message))



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/zmq_demo_client.py
    Connecting to hello world server…
    Sending request 0 …
    Received reply 0 [ b'World' ]
    Sending request 1 …
    Received reply 1 [ b'World' ]
    Sending request 2 …
    Received reply 2 [ b'World' ]
    Sending request 3 …
    Received reply 3 [ b'World' ]
    Sending request 4 …
    Received reply 4 [ b'World' ]
    Sending request 5 …
    Received reply 5 [ b'World' ]
    Sending request 6 …
    Received reply 6 [ b'World' ]
    Sending request 7 …
    Received reply 7 [ b'World' ]
    Sending request 8 …
    Received reply 8 [ b'World' ]
    Sending request 9 …
    Received reply 9 [ b'World' ]


"""
