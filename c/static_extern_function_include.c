///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Practice force-including `static` functions from other .c source files in C.

`static` functions are internal to the file they are defined in, and are not visible to other
files. However, if you want to force-include them in another file, there are a few hacky ways.
Let's try them out.
See: https://stackoverflow.com/q/35425790/4561887

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
./static_extern_function.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 static_extern_function.c static_extern_function__helper.c -o bin/a && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 static_extern_function.c static_extern_function__helper.c -o bin/a && bin/a
```

References:
1. https://stackoverflow.com/q/35425790/4561887
1.

*/

#include "static_extern_function__helper.h"

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n");

    print_incrementing_number();
    print_incrementing_number();
    print_incrementing_number();

    return 0;
}


/*
SAMPLE OUTPUT:

In C:




OR, in C++:



*/
