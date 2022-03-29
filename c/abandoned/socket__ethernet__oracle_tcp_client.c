/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

See Oracle: Socket Tutorial: https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2l/index.html
"Example 2-3 Internet Domain Stream Connection (Client)"

STATUS: bunch of build warnings, and I get at runtime:
        Segmentation fault (core dumped)
I think it's missing an `argv[1]` argument, but I don't know what to pass to `gethostbyname()`.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
# NB: I HAD TO REMOVE `-Werror` to make it compile! Put it back!
gcc -Wall -Wextra -O3 -std=c17 socket__ethernet__oracle_tcp_client.c -o bin/client -lm && bin/client 127.0.0.1
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__ethernet__oracle_tcp_client.c -o bin/client && bin/client
```

References:
1. See Oracle: Socket Tutorial: https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2l/index.html
"Example 2-3 Internet Domain Stream Connection (Client)"
1. https://www.gnu.org/software/libc/manual/html_node/Host-Names.html - `h_addr` and `h_addr_list`
1. Full GNU libc C library reference manual: for things like `struct hostent`, `h_addr`, etc.
   https://www.gnu.org/software/libc/manual/html_mono/libc.html
    1. `struct hostent`:
        https://www.gnu.org/software/libc/manual/html_mono/libc.html#index-struct-hostent

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>  // `exit()`

#define DATA "Half a league, half a league . . ."

/*
 * This program creates a socket and initiates a connection with
 * the socket given in the command line. Some data are sent over the
 * connection and then the socket is closed, ending the connection.
 * The form of the command line is: streamwrite hostname portnumber
 * Usage: pgm host port
 */
main(argc, argv)
        int argc;
        char *argv[];
{
        int sock;
            struct sockaddr_in server;
            struct hostent *hp, *gethostbyname();
            char buf[1024];

            /* Create socket. */
            sock = socket( AF_INET, SOCK_STREAM, 0);
            if (sock == -1) {
                perror("opening stream socket");
                exit(1);
            }
            /* Connect socket using name specified by command line. */
            server.sin_family = AF_INET;
            hp = gethostbyname(argv[1] );
/*
 * gethostbyname returns a structure including the network address
 * of the specified host.
 */
        if (hp == (struct hostent *) 0) {
            fprintf(stderr, "%s: unknown host\n", argv[1]);
            exit(2);
        }
        // GS: I replaced `h_addr` with `h_addr_list[0]` to get it to compile. I should maybe
        // print **all** address name strings in that array, instead, however, instead of just the
        // first one. Official GNU libc user manual documentation on this struct and member:
        // https://www.gnu.org/software/libc/manual/html_node/Host-Names.html#index-struct-hostent
        memcpy((char *) &server.sin_addr, (char *) hp->h_addr_list[0],
            hp->h_length);
        server.sin_port = htons(atoi(argv[2]));
        if (connect(sock, (struct sockaddr *) &server, sizeof server)
                == -1) {
            perror("connecting stream socket");
            exit(1);
        }
        if (write( sock, DATA, sizeof DATA) == -1)
            perror("writing on stream socket");
        close(sock);
        exit(0);
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 socket__ethernet__oracle_tcp_client.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__ethernet__oracle_tcp_client.c -o bin/a && bin/a
    Hello World.


*/
