/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


Speed test this implementation by @GaspardP: https://stackoverflow.com/a/71331152/4561887
Compare the results of that to the speed of my own implementation, here:
"read_file_into_c_string_and_array_of_lines.c" and online: https://stackoverflow.com/a/71346853/4561887

Then, either post a new answer, or at least update the above answer and make comments there to
present my results.


STATUS: wip (not yet started)

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 read_file_speedtest1.c utilities.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 read_file_speedtest1.c utilities.c -o bin/a && bin/a
```

References:
1. See: read_file_into_c_string_and_array_of_lines.c

*/

#include "utilities.h"

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

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 read_file_speedtest1.c utilities.c -o bin/a && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 read_file_speedtest1.c utilities.c -o bin/a && bin/a
    Hello World.


*/
