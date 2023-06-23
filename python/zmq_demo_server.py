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

"""
GS notes: which socket type should I use? See: https://zeromq.org/socket-api/
"ZeroMQ patterns are implemented by pairs of sockets with matching types." Here are some of those
types:

ZMQ socket types/patterns:
- https://zeromq.org/socket-api/


Built-in core ZeroMQ patterns:

1. Request-reply (synchronous: REQ-REP; and asynchronous: DEALER-ROUTER, DEALER-DEALER,
   ROUTER-ROUTER, etc.) - a "remote procedure call [RPC] and task distribution pattern"
    - For the official specification, see: https://rfc.zeromq.org/spec/28/

    - REQ socket type: "If no services are available, then any send operation on the socket will block until at least
      one service becomes available. The REQ socket will not discard any messages."

    - REP socket type: "If the original requester does not exist any more the reply is silently
      discarded.

    - ROUTER socket type:
        - "works as an asynchronous replacement for REP, and is often used as the basis for servers
          that talk to DEALER clients."


2. Pub-sub (PUB-SUB) - a data distribution pattern.
    - "The publish-subscribe pattern is used for one-to-many distribution of data from a single
      publisher to multiple subscribers in a fan out fashion."
    - Official spec: https://rfc.zeromq.org/spec/29/
    - GS: this sounds like it could be a total replacement for ROS topics and ROS pub/sub.
    - Topics are hierarchical. Subscribe to "topic", for instance, to receive "topic/1", "topic/2",
      as well as "topic" or "topical" messages.
    - "A consequence of this prefix matching behaviour is that you can receive all published messages by subscribing with an empty topic string."

    - PUB socket type:
        - "When a PUB socket enters the mute state due to having reached the high water mark for a
          subscriber, then any messages that would be sent to the subscriber in question shall
          instead be dropped until the mute state ends. The send function does never block for this
          socket type."

3. Pipeline (PUSH-PULL) - a "parallel task distribution and collection pattern"

4. Exclusive pair (PAIR) - "connects two sockets exclusively"; "a pattern for connecting two threads
   in a process, not to be confused with 'normal' pairs of sockets"


Draft state patterns:

5. Client-Server (CLIENT-SERVER) - one ZMQ server talks to multiple ZMQ clients

6. Radio-Dish (RADIO-DISH) - for a "one-to-many distribution of data from a single publisher to
   multiple subscribers in a fan out fashion"
"""

import time
import zmq

context = zmq.Context()
# Use a "Reply" **syncrhonous** socket type; see: https://zeromq.org/socket-api/: "ZeroMQ patterns
# are implemented by pairs of sockets with matching types."
socket = context.socket(zmq.REP)
# GS: use `bind()` instead of `connect()` on what you might consider "the more stable" side, ie: the
# server. "As a general rule use bind from the most stable points in your architecture, and use
# connect from dynamic components with volatile endpoints."
# - See: https://zeromq.org/socket-api/
#   - "Bind vs Connect" and its sub-section, "When should I use bind and when connect?"
# - See official `zmq.Socket.bind()` documentation here:
#   https://pyzmq.readthedocs.io/en/latest/api/zmq.html#zmq.Socket.bind
#   - "This causes the socket to listen on a network port. Sockets on the other side of this
#     connection will use `Socket.connect(addr)`` to connect to this socket."
#   - "addr (str) – The address string. This has the form ‘protocol://interface:port’, for example
#     ‘tcp://127.0.0.1:5555’. Protocols supported include tcp, udp, pgm, epgm, inproc and ipc. If
#     the address is unicode, it is encoded to utf-8 first."
socket.bind("tcp://*:5555")

print("Starting ZMQ server. Waiting for client.")

while True:
    #  Wait for next request from client
    # GS: a REP socket type MUST receive first. It cannot send until it receives first.
    # - See: https://zeromq.org/socket-api/: "Send/receive pattern: Receive, Send, Receive, Send …"
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
