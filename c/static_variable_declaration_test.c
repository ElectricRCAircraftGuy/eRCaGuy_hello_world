///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Mar. 2025

Demonstrate how `static` variable declarations only set the assigned value once, and then
keep their previous value for the rest of the program.

STATUS: Done and works. 

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./static_variable_declaration_test.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 static_variable_declaration_test.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 static_variable_declaration_test.c -o bin/a && bin/a
```

References:
1. For help with this funky bash script 1-liner at the very top, to make this C
   program directly executable:
    1. Shebang starting with `//`? - https://unix.stackexchange.com/a/162535/114401
    1. *****+ Run C or C++ file as a script - [my answer] https://stackoverflow.com/a/75491834/4561887
    1. ***** What's the appropriate Go shebang line? - [my answer] https://stackoverflow.com/a/75491727/4561887
1.

*/


#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    while (true)
    {
        // If you use this line, the program works correctly and exits after 10 iterations. 
        static int i = 0;
        // If you use this line, the program runs forever in its sins, repeatedly printing `i = 1`.
        // - Press Ctrl + C to exit. 
        // int i = 0;

        i++; 
        printf("i = %d\n", i);

        if (i >= 10)
        {
            break;
        }
    }

    return 0;
}


/*
SAMPLE OUTPUT:

In C, using `static int i = 0;`:

    eRCaGuy_hello_world/c$ ./static_variable_declaration_test.c
    Hello World.

    i = 1
    i = 2
    i = 3
    i = 4
    i = 5
    i = 6
    i = 7
    i = 8
    i = 9
    i = 10


In C, using `int i = 0;`:

    eRCaGuy_hello_world/c$ ./hello_world_extra_basic.c 
    Hello World.

    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    i = 1
    ...
    [continuing forever, with no end; use Ctrl + C to kill it]


*/
