/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Demonstrate a UDP server and client in the same program.
STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Compile as C
gcc -Wall -Wextra -Werror -O3 -std=c17 hello_world_extra_basic.c -o bin/server_client -lm
# Compile as C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.c -o bin/server_client

# Run server
bin/server_client --server
# Run client
bin/server_client --client
```

References:
1. This code is based on these two files:
    1. socket__geeksforgeeks_udp_server_GS_edit_GREAT.c
    1. socket__geeksforgeeks_udp_client_GS_edit_GREAT.c
1.

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

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 hello_world_extra_basic.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.c -o bin/a && bin/a
    Hello World.


*/
