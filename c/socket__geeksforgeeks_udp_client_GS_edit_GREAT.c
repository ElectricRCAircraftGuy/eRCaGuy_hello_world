///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Edit and learn the GeeksforGeeks UDP Server-Client code, from here:
https://www.geeksforgeeks.org/udp-server-client-implementation-c/.
This is the UDP **client** code.

STATUS: DONE AND WORKS! THIS IS A GREAT DEMO!

Instructions:
1. Run the **server** code first in one terminal. It will wait for the client to send it a message.
2. Run the **client** code second in a second terminal. It will send the server a message then wait
   for a response, which the server sends immediately.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 socket__geeksforgeeks_udp_client_GS_edit_GREAT.c -o bin/client -lm && bin/client
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__geeksforgeeks_udp_client_GS_edit_GREAT.c -o bin/client && bin/client
```

------------------------------
Steps to make a UDP Client:
------------------------------
1. Create a socket with `socket()`.
2. Call `sendto()` to send a message to the server to begin communication.
3. Call `recvfrom()` to block until a message is received back from the server.
4. Process the received message and print out the sender's address info, as well as the message.

References:
1. UDP server/client: https://www.geeksforgeeks.org/udp-server-client-implementation-c/
1. TCP server/client: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

*/

// Client-side implementation of UDP server-client model

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
#define SOCKET_TYPE_TCP              AF_INET, SOCK_STREAM, 0
#define SOCKET_TYPE_UDP              AF_INET, SOCK_DGRAM, 0
#define SOCKET_TYPE_RAW(protocol)    AF_INET, SOCK_RAW, (protocol)
// Usage examples:
// ```c
// int socket_tcp = socket(SOCKET_TYPE_TCP);
// int socket_udp = socket(SOCKET_TYPE_UDP);
// // See also: https://www.binarytides.com/raw-sockets-c-code-linux/
// int socket_raw = socket(SOCKET_TYPE_RAW(IPPROTO_RAW));
// ```c

#define MAX_RECEIVE_BUFFER_SIZE 4096  // in bytes

static const uint16_t PORT = 20000;
_Static_assert(sizeof(uint16_t) == sizeof(unsigned short),
    "`htons()` expects an unsigned short, and the PORT is uint16_t, so let's ensure they match "
    "for this system or else you'll have to replace `htons()` with a different function "
    "call.\n");


int main()
{
    // FOR MORE COMMENTS AND REFERENCE LINKS IN THE CODE, SEE THE SERVER CODE! Not all reference
    // links and comments have been copied from the server code to this client code.

    printf("STARTING UDP CLIENT:\n");

    // =============================================================================================
    printf("1. Create a socket object and obtain a file descriptor to it.\n");
    // =============================================================================================
    // See:
    // 1. https://linux.die.net/man/2/socket
    // 1. https://man7.org/linux/man-pages/man2/socket.2.html
    int socket_fd = socket(SOCKET_TYPE_UDP);
    if (socket_fd == -1)
    {
        printf("Failed to create socket. errno = %i: %s\n", errno, strerror(errno));
        goto cleanup;
    }

    struct sockaddr_in addr_server;
    memset(&addr_server, 0, sizeof(addr_server));

    // Fill in the server address information.
    addr_server.sin_family = AF_INET;  // IPv4
    addr_server.sin_port = htons(PORT);
    addr_server.sin_addr.s_addr = INADDR_ANY;

    // =============================================================================================
    printf("2. Send a message to the server.\n");
    // =============================================================================================

    const char msg_to_send[] = "Hello from client.";

    ssize_t num_bytes_sent = sendto(socket_fd, msg_to_send, sizeof(msg_to_send), 0,
        (const struct sockaddr *)&addr_server, sizeof(addr_server));
    if (num_bytes_sent == -1)
    {
        printf("Failed to send to server. errno = %i: %s\n", errno, strerror(errno));
        goto cleanup;
    }

    printf("Done! This msg was just sent to the server:\n"
           "  %s\n", msg_to_send);

    // =============================================================================================
    printf("3. Block until a message is received.\n");
    // =============================================================================================

    char receive_buf[MAX_RECEIVE_BUFFER_SIZE];
    // This is an input/output ("value-result") argument to the `recvfrom()` call below. See the
    // documentation links. That means we must first set it to the length of the address,
    // but then we must read it after the call to check for address length errors as well, because
    // the function will write to it!
    socklen_t addr_len = sizeof(addr_server);
    ssize_t num_bytes_received = recvfrom(socket_fd, receive_buf, sizeof(receive_buf), MSG_WAITALL,
        (struct sockaddr *)&addr_server, &addr_len);
    if (num_bytes_received == -1)
    {
        printf("Failed to receive data. errno = %i: %s\n", errno, strerror(errno));
        goto cleanup;
    }
    else if (num_bytes_received == 0)
    {
        printf("No bytes received. The sender has performed an orderly shutdown.\n");
    }

    if (addr_len > sizeof(addr_server))
    {
        printf("Error: the `addr_server` address buffer provided to the receive call was too "
               "small, and therefore the address written into it was truncated. Actual address "
               "size provided to the function was %zu bytes, but %u bytes were needed.\n",
               sizeof(addr_server), addr_len);
    }
    else if (addr_len < sizeof(addr_server))
    {
        printf("Note: the `addr_server` address buffer provided to the receive call was bigger "
               "than necessary. Actual address size provided to the function was %zu bytes, "
               "but only %u bytes were needed.\n", sizeof(addr_server), addr_len);
    }

    // =============================================================================================
    printf("4. Process the received message, & print out address info. of the sender, followed by "
           "the message!\n");
    // =============================================================================================

    // A. get and print sender address information

    // Socket internet namespace name
    const char* sender_sin_family_name = "unknown";
    switch (addr_server.sin_family)
    {
    case AF_INET:
        sender_sin_family_name = "AF_INET (IPv4 address)";
        break;
    case AF_INET6:
        sender_sin_family_name = "AF_INET6 (IPv6 address)";
    }
    // Use `ntohs()` ("network to host for short type") to convert the port number from network
    // (Big-endian) to host (Little-endian) byte order.
    uint16_t sender_port = ntohs(addr_server.sin_port);
    // See:
    // 1. https://linux.die.net/man/3/inet_aton
    // 1. https://linux.die.net/man/7/ip - for the `struct sockaddr_in` and `struct in_addr` struct
    //    definitions.
    const char* sender_ip_addr = inet_ntoa(addr_server.sin_addr);

    printf("Sender (server) address information:\n"
           "  socket internet namespace (sin) family name = %s\n"
           "  port                                        = %u\n"
           "  IP address                                  = %s\n",
           sender_sin_family_name, sender_port, sender_ip_addr);

    // B. print the message received from the sender

    printf("Msg received from sender (server) (%zi bytes):\n  %s\n",
        num_bytes_received, receive_buf);


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

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -O3 -std=c17 socket__geeksforgeeks_udp_client_GS_edit_GREAT.c -o bin/client -lm && bin/client
    socket__geeksforgeeks_udp_client_GS_edit_GREAT.c: In function ‘main’:
    socket__geeksforgeeks_udp_client_GS_edit_GREAT.c:67:17: warning: pointer targets in passing argument 6 of ‘recvfrom’ differ in signedness [-Wpointer-sign]
                     &len);
                     ^~~~
    In file included from /usr/include/x86_64-linux-gnu/sys/socket.h:269,
                     from socket__geeksforgeeks_udp_client_GS_edit_GREAT.c:31:
    /usr/include/x86_64-linux-gnu/bits/socket2.h:64:1: note: expected ‘socklen_t * restrict’ {aka ‘unsigned int * restrict’} but argument is of type ‘int *’
     recvfrom (int __fd, void *__restrict __buf, size_t __n, int __flags,
     ^~~~~~~~
    Hello message sent.
    Server : Hello from server



OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__geeksforgeeks_udp_client_GS_edit_GREAT.c -o bin/a && bin/a
    Hello World.


*/
