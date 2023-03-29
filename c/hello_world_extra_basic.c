///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

(description)
STATUS: (status)

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./hello_world_extra_basic.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 hello_world_extra_basic.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 hello_world_extra_basic.c -o bin/a && bin/a
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
