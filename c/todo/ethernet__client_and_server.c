/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Started: 8 Mar. 2022

(description)
TODO: write a demo client/server program which exchanges some data between two running processes.
Both processes will be run on the same executable. Just run it like this:
        prog_name --server
        // vs
        prog_name --client

Once they are both up, they will begin exchanging data. Just have the client send a counter over or
something, and have the server respond with what it received.

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 hello_world_extra_basic.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.c -o bin/a && bin/a
```

References:
1. Google search for "linux socket ethernet packet example":
   https://www.google.com/search?q=linux+socket+ethernet+packet+example&oq=linux+socket+ethernet+packet+example&aqs=chrome..69i57.8472j0j4&sourceid=chrome&ie=UTF-8
    1. sendRawEth.c: Send a raw Ethernet frame in Linux:
       https://gist.github.com/austinmarton/1922600
1. ***** Google search for "Ethernet sockets demo in c":
   https://www.google.com/search?q=Ethernet+sockets+demo+in+c&oq=Ethernet+sockets+demo+in+c&aqs=chrome..69i57.156j0j9&sourceid=chrome&ie=UTF-8
    1. LOOKS LIKE A GREAT DEMO!:
       https://www.codeproject.com/Articles/586000/Networking-and-Socket-Programming-Tutorial-in-C
    1. https://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf
    1. Looks very useful!: https://www.geeksforgeeks.org/socket-programming-cc/


*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 hello_world_extra_basic.c -o bin/a && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.c -o bin/a && bin/a
    Hello World.


*/
