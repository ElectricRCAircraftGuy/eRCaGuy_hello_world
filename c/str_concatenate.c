///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Concatenate two (or more) C-strings (character arrays) in various ways.

- For a comparison to the simpler usage in C++ (just use the `+` operator),
  see "eRCaGuy_hello_world/cpp/string_concatenate.cpp".

  - C++ is seemingly simpler since it handles the low-level memory management **for you**! However,
    this is at the trade-off of:
    1) syntax and language complexity: you need to know what the non-member template function
    `operator+()` is, and how it works, and
    2) speed, safety, determinism, and control: since C++ controls the low-level memory management
    for you, and automatically dynamically allocates memory at-will in most of the STL containers,
    it may run slower, is non-deterministic when it calls `new` (the C++ equivalent of `malloc())`),
    and may be more-likely to throw run-time errors and have run-time crashes when out of
    memory since it may dynamically allocate memory without your explicit awareness otherwise.

STATUS: wip

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS: interview prep

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./str_concatenate.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 str_concatenate.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 str_concatenate.c -o bin/a && bin/a
```

References:
1.
1.

*/


#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`, `snprintf()`, etc.
#include <string.h>

/// Concatenate

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 str_concatenate.c -o bin/a -lm && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 str_concatenate.c -o bin/a && bin/a
    Hello World.

*/
