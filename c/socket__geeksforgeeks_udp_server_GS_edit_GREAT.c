/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Edit and learn the GeeksforGeeks UDP Server-Client code, from here:
https://www.geeksforgeeks.org/udp-server-client-implementation-c/.
This is the UDP **server** code.

STATUS: DONE AND WORKS! THIS IS A GREAT DEMO!

TODO: make a super simple version of this that ignores ALL error checking, just to show how simple
and short these 5 steps are if you don't do any error checking!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
# NB: Use `-std=gnu17`, NOT `-std=c17`, per my answer here:
# https://stackoverflow.com/a/71801111/4561887. This allows me to use `inet_aton()`, for instance,
# much more easily!
gcc -Wall -Wextra -Werror -O3 -std=gnu17 socket__geeksforgeeks_udp_server_GS_edit_GREAT.c -o bin/server -lm && bin/server
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 socket__geeksforgeeks_udp_server_GS_edit_GREAT.c -o bin/server && bin/server
```

------------------------------
Steps to make a UDP Server:
------------------------------
1. Create a socket with `socket()`.
2. Bind the socket object to a socket internet namespace (sin) address (which consists of a socket
internet namespace A) family, B) port, and C) IP address) via `bind()`.
3. Call `recvfrom()` to block until a message is received.
4. Process the received message and print out the sender's address info, as well as the message.
5. Call `sendto()` to send a message reply back to the sender of the message we just received.

References:

1. *****+UDP server/client: https://www.geeksforgeeks.org/udp-server-client-implementation-c/
1. *****+TCP server/client: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

1. https://www.binarytides.com/programming-udp-sockets-c-linux/

1. https://man7.org/linux/man-pages/man7/ip.7.html
1. *****https://man7.org/linux/man-pages/man3/recvfrom.3p.html [POSIX Programmer's Manual]
    > DESCRIPTION: The recvfrom() function shall receive a message from a connection-mode [TCP] or
      connectionless-mode [UDP] socket. It is normally used with connectionless-mode [UDP] sockets
      **because it permits the application to retrieve the source address of received data.**
1. https://linux.die.net/man/7/socket
1. https://linux.die.net/man/2/socket
1. https://linux.die.net/man/2/recvfrom
1. https://linux.die.net/man/7/ip
1.


What happens if you try to use **unbound sockets**!?
Ans: https://linux.die.net/man/7/ip
> When a process wants to receive new incoming packets or connections, it should bind a socket to a
  local interface address using bind(2). In this case, only one IP socket may be bound to any given
  local (address, port) pair. When INADDR_ANY is specified in the bind call, the socket will be
  bound to all local interfaces. When listen(2) is called on an unbound socket, the socket is
  automatically bound to a random free port with the local address set to INADDR_ANY. When connect
  (2) is called on an unbound socket, the socket is automatically bound to a random free port or to
  a usable shared port with the local address set to INADDR_ANY.


*/

// Server-side implementation of UDP server-client model

// local includes
// None

// Linux Includes
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// C includes
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // `strerror()`


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
//
// Usage examples:
// ```c
// int socket_tcp = socket(SOCKET_TYPE_TCP_IPV4);
// int socket_udp = socket(SOCKET_TYPE_UDP_IPV4);
// // See also: https://www.binarytides.com/raw-sockets-c-code-linux/
// int socket_raw = socket(SOCKET_TYPE_RAW_IPV4(IPPROTO_RAW));
// ```c

#define MAX_RECEIVE_BUFFER_SIZE 4096  // in bytes

static const uint16_t PORT = 20000;
_Static_assert(sizeof(uint16_t) == sizeof(unsigned short),
    "`htons()` expects an unsigned short, and the PORT is uint16_t, so let's ensure they match "
    "for this system or else you'll have to replace `htons()` with a different function "
    "call.\n");


int main()
{
    int flags;
    int retcode;

    printf("STARTING UDP SERVER:\n");

    // =============================================================================================
    printf("1. Create a socket object, obtain a file descriptor to it, and prepare server and "
           "client `struct sockaddr_in` internet namespace (\"in\") socket addresses.\n");
    // =============================================================================================
    // See:
    // 1. https://linux.die.net/man/2/socket
    // 1. https://man7.org/linux/man-pages/man2/socket.2.html
    int socket_fd = socket(SOCKET_TYPE_UDP_IPV4);
    if (socket_fd == -1)
    {
        printf("Failed to create socket. errno = %i: %s\n", errno, strerror(errno));
        goto cleanup; // consider replacing this with `exit(EXIT_FAILURE);` instead, in order to
                      // try to quickly get this code compiling in C++/gnu++
    }

    // Internet namespace socket addresses
    // sockaddr_in = "socket address internet namespace"
    // See:
    // 1. GNU LibC one-page user manual:
    //    https://www.gnu.org/software/libc/manual/html_mono/libc.html#index-struct-sockaddr_005fin
    // 1. https://linux.die.net/man/7/ip
    struct sockaddr_in addr_server;
    struct sockaddr_in addr_client;
    // It's a good idea to memset the addresses to zero, so that all fields, including hidden ones
    // or padding ones, are zero as well. See: https://stackoverflow.com/a/36088131/4561887.
    memset(&addr_server, 0, sizeof(addr_server));
    memset(&addr_client, 0, sizeof(addr_client));

    // Fill in the server address information.

    // sin = "socket internet namespace"
    addr_server.sin_family = AF_INET;  // IPv4
    // NB: `htons()` converts "host to network" byte order for unsigned 's'hort types
    // (usually uint16_t), since `sin_port` must be in **network byte order**! Since the port is
    // always a 2-byte uint16_t number, use `htons()` to convert it.
    // See: https://linux.die.net/man/3/htons
    addr_server.sin_port = htons(PORT);

    // Use 1 of the 3 options below to set the IP address of the server.
    // - (I am leaving all 3 options uncommented for the purposes of this demo, since that's okay,
    //   but only the last one is therefore the one which will "stick", as the IP addresses set by
    //   the options prior to that one get overwritten by the last one).

    // Option 1/3: use a macro constant to set the IP address.
    // `INADDR_ANY` means "accept any incoming address". See:
    // https://www.gnu.org/software/libc/manual/html_mono/libc.html#index-INADDR_005fANY
    // ie it means "any address for binding"; see: https://man7.org/linux/man-pages/man7/ip.7.html.
    // I **think** that means it will bind to **any** available IP address when you call `bind()`
    // below! If you need it to have some particular address, use one of the options just below
    // instead!
    addr_server.sin_addr.s_addr = INADDR_ANY; // <--- Option 1/3 to set the IP address
    //
    // Option 2/3: to make your own address from an IPv4 string such as localhost "127.0.0.1"
    // instead, use the NON-POSIX "internet ascii to network" function, `inet_aton()`. See here:
    // 1. https://linux.die.net/man/3/inet_aton
    // 1. https://man7.org/linux/man-pages/man3/inet.3.html
    // Example: this uses the localhost IPv4 address string "127.0.0.1".
    //
    retcode = inet_aton("127.0.0.1", &addr_server.sin_addr); // <--- Option 2/3 to set the IP address
    if (retcode == 0)
    {
        printf("Failed to generate a network address from an ASCII string address. Input address "
               "ASCII string is invalid.\n");
        goto cleanup;
    }
    //
    // Option 3/3 [RECOMMENDED OVER `inet_aton()` above!]: even better than using the
    // non-POSIX "ascii string to network" address `inet_aton()` function is using the
    // POSIX "presentation string to network" `inet_pton()` function! See:
    // 1. [my answer] https://stackoverflow.com/a/71801111/4561887 - Just use the POSIX-compliant
    //    inet_pton() instead of the non-POSIX inet_aton()
    // 1. https://man7.org/linux/man-pages/man3/inet_pton.3.html - Linux Programmer's Manual
    // 1. https://www.gnu.org/software/libc/manual/html_mono/libc.html#index-inet_005fpton
    //      - `inet_pton()` "function converts an Internet address (either IPv4 or IPv6) from
    //        presentation (textual) to network (binary) format"
    // 1. https://man7.org/linux/man-pages/man3/inet_pton.3p.html - POSIX Programmer's Manual
    //
    retcode = inet_pton(AF_INET, "127.0.0.1", &addr_server.sin_addr); // <--- Option 3/3 to set the IP address
    if (retcode != 1)
    {
        printf("`inet_pton()` failed! ");
        if (retcode == 0)
        {
            printf("The source IP address string does not contain a character string representing "
                   "a valid network address in the specified address family.\n");
        }
        else if (retcode == -1)
        {
            printf("Invalid address family (AF) parameter was passed-in as the 1st argument. "
                   "errno = %i: %s\n", errno, strerror(errno));
        }
    }

    // =============================================================================================
    printf("2. Bind the socket object with the server address specified above so that it "
           "can be used.\n");
    // =============================================================================================
    // See:
    // 1. https://linux.die.net/man/7/ip - this link also explains what happens when you try to use
    //    "unbound" sockets!
    // 1. https://linux.die.net/man/2/bind
    retcode = bind(socket_fd, (const struct sockaddr *)&addr_server, sizeof(addr_server));
    if (retcode == -1)
    {
        printf("Failed to bind socket. errno = %i: %s\n", errno, strerror(errno));
        goto cleanup;
    }

    // =============================================================================================
    printf("3. Block until a message is received.\n");
    // =============================================================================================
    // See:
    // 1. *****https://linux.die.net/man/2/recv - NB: receive calls are all **blocking** by default
    //    but can be made **nonblocking** by passing flag `MSG_DONTWAIT` to the calls!:
    //    "If no messages are available at the socket, the receive calls wait for a message to
    //    arrive".
    // 1. *****https://man7.org/linux/man-pages/man3/recvfrom.3p.html [POSIX Programmer's Manual]
    //      > DESCRIPTION: The recvfrom() function shall receive a message from a connection-mode
    //        [TCP] or connectionless-mode [UDP] socket. It is normally used with
    //        connectionless-mode [UDP] sockets **because it permits the application to retrieve
    //        the source address of received data.**
    // 1. https://man7.org/linux/man-pages/man2/recv.2.html
    // 1. https://www.cs.cmu.edu/~srini/15-441/F01.full/www/assignments/P2/htmlsim_split/node12.html
    char receive_buf[MAX_RECEIVE_BUFFER_SIZE];
    // `addr_len` is an input/output ("value-result") argument to the `recvfrom()` call below. See
    // the documentation links above. That means we must first set it to the length of the address,
    // but then we must read it after the call to check for address length errors as well, because
    // the function will write to it!
    socklen_t addr_len = sizeof(addr_client);
    // Receive **from** **any address**, storing the address of the sender into `addr_client` once
    // you receive a message **from ANYONE!** This "received from" address is then used as the
    // "destination address" in `sendto()` below, which we use to **send back to**, or **reply to**,
    // the sender!
    ssize_t num_bytes_received = recvfrom(socket_fd, receive_buf, sizeof(receive_buf), MSG_WAITALL,
        (struct sockaddr *)&addr_client, &addr_len);
    if (num_bytes_received == -1)
    {
        printf("Failed to receive data. errno = %i: %s\n", errno, strerror(errno));
        goto cleanup;
    }
    else if (num_bytes_received == 0)
    {
        printf("No bytes received. The sender has performed an orderly shutdown.\n");
    }

    if (addr_len > sizeof(addr_client))
    {
        printf("Error: the `addr_client` address buffer provided to the receive call was too "
               "small, and therefore the address written into it was truncated. Actual address "
               "size provided to the function was %zu bytes, but %u bytes were needed.\n",
               sizeof(addr_client), addr_len);
    }
    else if (addr_len < sizeof(addr_client))
    {
        printf("Note: the `addr_client` address buffer provided to the receive call was bigger "
               "than necessary. Actual address size provided to the function was %zu bytes, "
               "but only %u bytes were needed.\n", sizeof(addr_client), addr_len);
    }

    // =============================================================================================
    printf("4. Process the received message, & print out address info. of the sender, followed by "
           "the message!\n");
    // =============================================================================================

    // A. get and print sender address information

    // Socket internet namespace name
    const char* sender_sin_family_name = "unknown";
    switch (addr_client.sin_family)
    {
    case AF_INET:
        sender_sin_family_name = "AF_INET (IPv4 address)";
        break;
    case AF_INET6:
        sender_sin_family_name = "AF_INET6 (IPv6 address)";
    }
    // Use `ntohs()` ("network to host for short type") to convert the port number from network
    // (Big-endian) to host (Little-endian) byte order.
    uint16_t sender_port = ntohs(addr_client.sin_port);
    // See:
    // 1. https://linux.die.net/man/3/inet_aton
    // 1. https://linux.die.net/man/7/ip - for the `struct sockaddr_in` and `struct in_addr` struct
    //    definitions.
    const char* sender_ip_addr = inet_ntoa(addr_client.sin_addr);

    printf("Sender (client) address information:\n"
           "  socket internet namespace (sin) family name = %s\n"
           "  port                                        = %u\n"
           "  IP address                                  = %s\n",
           sender_sin_family_name, sender_port, sender_ip_addr);

    // B. print the message received from the sender

    printf("Msg received from sender (client) (%zi bytes):\n  %s\n",
        num_bytes_received, receive_buf);

    // =============================================================================================
    printf("5. Send a response back to the sender of the message we just received.\n");
    // =============================================================================================
    // See:
    // 1. https://man7.org/linux/man-pages/man3/sendto.3p.html [POSIX Programmer's Manual]

    const char msg_to_send[] = "Hello from server.";
    // See: https://linux.die.net/man/2/sendto
    //
    // If you're wondering about when to use the `MSG_CONFIRM` flag, essentially, all it does is
    // tell the underlying ARP network layer to NOT periodically verify the MAC of the recipient
    // IP, because we are confident the IP we are sending to is the device we think it is, since
    // this message are are sending is in **direct response to** a message we just **received**
    // from them! In other words, if in doubt, leave OUT the `MSG_CONFIRM` flag. Put it in ONLY if
    // the message we are sending is a direct response to a message received, and therefore we want
    // to increase the network efficiency a tiny bit by NOT verifying the MAC again periodically,
    // at the risk that the destination MAC could change and be wrong and no loner match the IP
    // address for the device we think we are sending this message to!
    // - See my answer here: https://stackoverflow.com/a/71712033/4561887

    // flags = MSG_CONFIRM;
    flags = 0;
    // Send **to** the address of `addr_client`, which is the **destination address**. See the
    // POSIX Programmer's manual: https://man7.org/linux/man-pages/man3/sendto.3p.html
    // Use `send()` to send to connection-mode (TCP) connected sockets, and use `sendto()` to send
    // to connection-less (UDP) addresses!
    ssize_t num_bytes_sent = sendto(socket_fd, msg_to_send, sizeof(msg_to_send), flags,
        (const struct sockaddr *)&addr_client, sizeof(addr_client));
    if (num_bytes_sent == -1)
    {
        printf("Failed to send to client. errno = %i: %s\n", errno, strerror(errno));
        goto cleanup;
    }

    printf("Done! This msg was just sent to the client:\n"
           "  %s\n", msg_to_send);


cleanup:
    if (socket_fd != -1)
    {
        close(socket_fd);
    }

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 socket__geeksforgeeks_udp_server_GS_edit_GREAT.c -o bin/server -lm && bin/server
    STARTING UDP SERVER:
    1. Create a socket object and obtain a file descriptor to it.
    2. Bind the socket object with the server address specified above so that it can be used.
    3. Block until a message is received.
    4. Process the received message, & print out address info. of the sender, followed by the message!
    Sender address information:
      socket internet namespace (sin) family name = AF_INET (IPv4 address)
      port                                        = 55862
      IP address                                  = 127.0.0.1
    Msg received from sender (client) (18 bytes):
      Hello from client.
    5. Send a response back to the sender of the message we just received.
    Done! This msg was just sent to the client:
      Hello from server.


OR, in C++:

[doesn't work yet--I need to address a bunch of compile-time errors!]


*/
