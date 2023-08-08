This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Socket examples & study

1. \*\*\*\*\*+ EXCELLENT example code, UDP sending and receiving examples, multicast, etc: https://wiki.python.org/moin/UdpCommunication
1. TCP example code: https://wiki.python.org/moin/TcpCommunication
1. https://docs.python.org/3/library/select.html#poll-objects - select — Waiting for I/O completion — Python 3.11.4 documentation [GS notes: how to do Ethernet polling in Python: create a socket, call `poll.register(fd)` to pass in the socket fd file descriptor, then call `poll.poll([timeout_ms])` to get back an iterable tuple of `(fd, event)` 2-tuples telling me which socket file descriptors are ready to be read and have data right now!; how to do ethernet socket polling in Python--see my notes to the left!]


# Examples


From: https://wiki.python.org/moin/UdpCommunication

1. UDP sender ("client"):
    ```bash
    import socket

    UDP_IP = "127.0.0.1"
    UDP_PORT = 5005
    MESSAGE = b"Hello, World!"

    print("UDP target IP: %s" % UDP_IP)
    print("UDP target port: %s" % UDP_PORT)
    print("message: %s" % MESSAGE)

    sock = socket.socket(socket.AF_INET, # Internet
                         socket.SOCK_DGRAM) # UDP
    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
    ```

1. UDP receiver ("server")
    ```bash
    import socket

    UDP_IP = "127.0.0.1"
    UDP_PORT = 5005

    sock = socket.socket(socket.AF_INET, # Internet
                         socket.SOCK_DGRAM) # UDP
    sock.bind((UDP_IP, UDP_PORT))

    while True:
        data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
        print("received message: %s" % data)
    ```

From: https://wiki.python.org/moin/TcpCommunication

1. TCP sender ("client"): see link above.
1. TCP receiver ("server"): see link above.
