/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Run the GeeksforGeeks UDP Server-Client code exactly as-is, from here:
https://www.geeksforgeeks.org/udp-server-client-implementation-c/.
This is the UDP **server** code.

STATUS: works, but could use some clean-up in my own edited version.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
# Removed -Werror to compile; put it back!
gcc -Wall -Wextra -O3 -std=c17 socket__geeksforgeeks_udp_server.c -o bin/server -lm && bin/server
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__geeksforgeeks_udp_server.c -o bin/server && bin/server
```

References:
1. UDP server/client: https://www.geeksforgeeks.org/udp-server-client-implementation-c/
1. TCP server/client: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

*/

// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE 1024

// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr); //len is value/resuslt

    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sockfd, (const char *)hello, strlen(hello),
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    printf("Hello message sent.\n");

    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -O3 -std=c17 socket__geeksforgeeks_udp_server.c -o bin/server -lm && bin/server
    socket__geeksforgeeks_udp_server.c: In function ‘main’:
    socket__geeksforgeeks_udp_server.c:73:17: warning: pointer targets in passing argument 6 of ‘recvfrom’ differ in signedness [-Wpointer-sign]
                     &len);
                     ^~~~
    In file included from /usr/include/x86_64-linux-gnu/sys/socket.h:269,
                     from socket__geeksforgeeks_udp_server.c:31:
    /usr/include/x86_64-linux-gnu/bits/socket2.h:64:1: note: expected ‘socklen_t * restrict’ {aka ‘unsigned int * restrict’} but argument is of type ‘int *’
     recvfrom (int __fd, void *__restrict __buf, size_t __n, int __flags,
     ^~~~~~~~

    Client : Hello from client
    Hello message sent.



OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__geeksforgeeks_udp_server.c -o bin/a && bin/a
    Hello World.


*/
