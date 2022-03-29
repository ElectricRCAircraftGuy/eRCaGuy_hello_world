/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Learn to do basic UDP packet sending
STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 socket__ethernet__udp_basic.c -o bin/a -lm && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__ethernet__udp_basic.c -o bin/a && bin/a
```

References:
1. See also: Oracle: "Advanced Topics": "Broadcasting and Determining Network Configuration":
   https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2o/index.html


1. [my answer] What is SOCK_DGRAM and SOCK_STREAM?: https://stackoverflow.com/a/71417876/4561887
1. ***** Google search for "Ethernet sockets demo in c":
   https://www.google.com/search?q=Ethernet+sockets+demo+in+c&oq=Ethernet+sockets+demo+in+c&aqs=chrome..69i57.156j0j9&sourceid=chrome&ie=UTF-8
    1. *****+ LOOKS LIKE THE BEST DEMO!: https://people.cs.rutgers.edu/~pxk/rutgers/notes/sockets/
    1. LOOKS LIKE A GREAT DEMO!:
       https://www.codeproject.com/Articles/586000/Networking-and-Socket-Programming-Tutorial-in-C
    1. https://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf
    1. Looks very useful!: https://www.geeksforgeeks.org/socket-programming-cc/
------
1. How to Code Raw Sockets in C on Linux: https://www.binarytides.com/raw-sockets-c-code-linux/
1. Google search for "linux socket ethernet packet example":
   https://www.google.com/search?q=linux+socket+ethernet+packet+example&oq=linux+socket+ethernet+packet+example&aqs=chrome..69i57.8472j0j4&sourceid=chrome&ie=UTF-8
    1. sendRawEth.c: Send a raw Ethernet frame in Linux:
       https://gist.github.com/austinmarton/1922600
------
1. https://linux.die.net/man/7/ip
1. https://linux.die.net/man/7/socket
1. https://linux.die.net/man/7/udp
1. https://www.ibm.com/docs/en/aix/7.1?topic=s-socket-subroutine
1. https://www.ibm.com/docs/en/aix/7.1?topic=domains-address-families
1. https://www.ibm.com/docs/en/aix/7.1?topic=protocols-socket-types
1. https://www.ibm.com/docs/en/aix/7.1?topic=s-send-subroutine

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// See: https://linux.die.net/man/7/ip
#define SOCKET_TYPE_TCP              AF_INET, SOCK_STREAM, 0
#define SOCKET_TYPE_UDP              AF_INET, SOCK_DGRAM, 0
#define SOCKET_TYPE_RAW(protocol)    AF_INET, SOCK_RAW, (protocol)

// // Usage examples:
// int socket_tcp = socket(SOCKET_TYPE_TCP);
// int socket_udp = socket(SOCKET_TYPE_UDP);
// // See also: https://www.binarytides.com/raw-sockets-c-code-linux/
// int socket_raw = socket(SOCKET_TYPE_RAW(IPPROTO_RAW));



// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 socket__ethernet__udp_basic.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 socket__ethernet__udp_basic.c -o bin/a && bin/a
    Hello World.


*/
