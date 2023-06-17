This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Unix `socket` interface: sockets, Ethernet, TCP vs UDP packets, client/server examples, etc.

# Learning Resources and notes

I've done a _lot_ of Googling and looked at a lot of resources now, and none of it seems to be great material so far on the topic of learning sockets and Ethernet packets and seeing good UDP and TCP server/client C examples, except perhaps GeeksForGeeks. We shall see. Study these:

1. GeeksforGeeks
    1. https://www.geeksforgeeks.org/socket-programming-cc/
    1. \*\*\*\*\*[TCP Server-Client implementation in C](https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/)
    1. \*\*\*\*\*[UDP Server-Client implementation in C](https://www.geeksforgeeks.org/udp-server-client-implementation-c/)
    1. https://www.geeksforgeeks.org/differences-between-tcp-and-udp/?ref=lbp
    1. https://www.geeksforgeeks.org/user-datagram-protocol-udp/
    1. https://www.geeksforgeeks.org/why-does-dns-use-udp-and-not-tcp/
1. Google search for ["c socket client server demo"](https://www.google.com/search?q=c+socket+client+server+demo&oq=c+socket+client+server+demo&aqs=chrome..69i57j69i64l3.6367j0j7&sourceid=chrome&ie=UTF-8)
1. TCP **server** example: see the bottom of this man page here: https://linux.die.net/man/2/bind. They cover all of these steps:
    1. Create the socket, bind it, listen, accept an incoming connection.

1. [Stack Overflow: How to open and use a socket in C?](https://stackoverflow.com/q/307692/4561887)
    1. https://stackoverflow.com/a/307704/4561887
        1. https://beej.us/guide/bgnet/html//index.html
        1. https://beej.us/guide/bgnet/html//index.html#client-server-background

1.  https://man7.org/linux/man-pages/man2/socket.2.html

1. My work:
    1. [socket__geeksforgeeks_udp_client_GS_edit_GREAT.c](socket__geeksforgeeks_udp_client_GS_edit_GREAT.c)
    1. [socket__geeksforgeeks_udp_server_GS_edit_GREAT.c](socket__geeksforgeeks_udp_server_GS_edit_GREAT.c)
    1. [Stack Overflow: Is TCP bidirectional or full-duplex?](https://stackoverflow.com/a/73226099/4561887)
    1. [Stack Overflow: Why should I use, or not use, MSG_CONFIRM?](https://stackoverflow.com/a/71712033/4561887)
    1. [Stack Overflow: What is SOCK_DGRAM and SOCK_STREAM?](https://stackoverflow.com/a/71417876/4561887) - has my macros like this, too, from my example code here: [socket__geeksforgeeks_udp_server_GS_edit_GREAT.c](socket__geeksforgeeks_udp_server_GS_edit_GREAT.c):
        ```c
        // See: https://linux.die.net/man/7/ip
        // AF = "Address Family"
        // INET = "Internet"
        // AF_INET = IPv4 internet protocols
        // AF_INET6 = IPv6 internet protocols; see: https://linux.die.net/man/2/socket
        // DGRAM = "Datagram" (UDP)
        //
        // IPv4
        #define SOCKET_TYPE_TCP_IPV4              AF_INET, SOCK_STREAM, 0
        #define SOCKET_TYPE_UDP_IPV4              AF_INET, SOCK_DGRAM, 0
        #define SOCKET_TYPE_RAW_IPV4(protocol)    AF_INET, SOCK_RAW, (protocol)
        // IPv6
        #define SOCKET_TYPE_TCP_IPV6              AF_INET6, SOCK_STREAM, 0
        #define SOCKET_TYPE_UDP_IPV6              AF_INET6, SOCK_DGRAM, 0
        #define SOCKET_TYPE_RAW_IPV6(protocol)    AF_INET6, SOCK_RAW, (protocol)
        ```


## [TCP Server/Client flow:](https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/)

[![](docs/Socket_server-1.png)](docs/Socket_server-1.png)


## [UDP Server/Client flow:](https://www.geeksforgeeks.org/udp-server-client-implementation-c/)

[![](docs/udpfuncdiag.png)](docs/udpfuncdiag.png)

1. Excellent example of this!: 
    1. UDP server: [socket__geeksforgeeks_udp_server_GS_edit_GREAT.c](socket__geeksforgeeks_udp_server_GS_edit_GREAT.c)
    1. UDP client: [socket__geeksforgeeks_udp_client_GS_edit_GREAT.c](socket__geeksforgeeks_udp_client_GS_edit_GREAT.c)
