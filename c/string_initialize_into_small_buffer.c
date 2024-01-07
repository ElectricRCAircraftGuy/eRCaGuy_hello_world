///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Jan. 2024

Question: What happens if you initialize a string into a buffer that is too small?--perhaps just
by the 1 character required to put the null terminator? 
I _think_ it will just write the string with*out* the null terminator. Let's check!

Answer: see the output at the very bottom. See also this really important comment in the code
below:

    > // NB: even if you compile with `-Werror` in C, so long as you don't
    > // *intentionally* read outside the buffer, this "string-isn't-
    > // null-terminated" bug will **silently** make it through and you'll
    > // never know about it, so watch out for it!

STATUS: Done and works! See results at the bottom.

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./string_initialize_into_small_buffer.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 string_initialize_into_small_buffer.c -o bin/a -lm && bin/a
# REMOVE -Werror TO GET THIS TO COMPILE IN THIS CASE SINCE I'M INTENTIONALLY WRITING OUT OF BOUNDS!
# <======
gcc -Wall -Wextra -O3 -std=gnu17 string_initialize_into_small_buffer.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 string_initialize_into_small_buffer.c -o bin/a && bin/a
# REMOVE -Werror TO GET THIS TO COMPILE IN THIS CASE SINCE I'M INTENTIONALLY WRITING OUT OF BOUNDS!
# <======
g++ -Wall -Wextra -O3 -std=gnu++17 string_initialize_into_small_buffer.c -o bin/a && bin/a
```

References:
1. For help with this funky bash script 1-liner at the very top, to make this C
   program directly executable:
    1. Shebang starting with `//`? - https://unix.stackexchange.com/a/162535/114401
    1. *****+ Run C or C++ file as a script - [my answer] https://stackoverflow.com/a/75491834/4561887
    1. ***** What's the appropriate Go shebang line? - [my answer] https://stackoverflow.com/a/75491727/4561887
1.

*/


#include <assert.h>
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{

    // char str[4] = "Hello"; // Compiles in C when `-Werror` is removed, but also has the bug.
    //
    char str[5] = "Hello"; // BUG: works WITH UNDEFINED BEHAVIOR SINCE IT'S NOT NULL-TERMINATED.
                           // NB: even if you compile with `-Werror` in C, so long as you don't
                           // *intentionally* read outside the buffer, this "string-isn't-
                           // null-terminated" bug will **silently** make it through and you'll
                           // never know about it, so watch out for it!
    // char str[6] = "Hello"; // No bug: **would** work perfectly: "Hello World."
    char str2[10];

    // force some undefined behavior here; first: ensure my undefined behavior is well-behaved
    
    printf("&str[5] = %zu\n", (size_t)&str[5]);
    printf("&str2[0] = %zu\n", (size_t)&str2[0]);

    // I expect str2 to be stored right after str1, even though it doesn't have to be, technically,
    // per the C standard. Note: `((size_t)&str[4] + 1)` is `str[5]` which is out of bounds!
    assert(((size_t)&str[4] + 1) == (size_t)&str2[0]); 

    str[5] = 'X'; // UNDEFINED BEHAVIOR (technically), but it works fine because it just writes into
                  // element 1 of `str2`. 


    printf("sizeof(str) = %zu\n", sizeof(str));
    printf("%s World.\n", str);

    return 0;
}


/*
SAMPLE OUTPUT:

MANUALLY CALL THE COMPILE COMMANDS WITH*OUT* `-Werror`!

In C:

Answer: UNDEFINED BEHAVIOR, AND THE BUG I EXPECTED! NOT HAVING THE STRING NULL-TERMINATED IS 
PROBLEMATIC! The 'X' following the `str` buffer is also printed, and it's not until the 0 after
the 'X' that the string is finally terminated.

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -O3 -std=gnu17 string_initialize_into_small_buffer.c -o bin/a -lm && bin/a
    string_initialize_into_small_buffer.c: In function ‘main’:
    string_initialize_into_small_buffer.c:73:8: warning: array subscript 5 is above array bounds of ‘char[5]’ [-Warray-bounds]
       73 |     str[5] = 'X'; // UNDEFINED BEHAVIOR (technically), but it works fine because it just writes into
          |     ~~~^~~
    string_initialize_into_small_buffer.c:61:10: note: while referencing ‘str’
       61 |     char str[5] = "Hello"; // works fine: "Hello World."
          |          ^~~
    &str[5] = 140729063910126
    &str2[0] = 140729063910126
    sizeof(str) = 5
    HelloX World.


In C++:

Answer: IT JUST WON'T COMPILE! C++ REQUIRES THAT THE char BUFFER BE BIG ENOUGH TO HOLD THE STRING
PLUS THE NULL TERMINATOR!

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -O3 -std=gnu++17 string_initialize_into_small_buffer.c -o bin/a && bin/a
    string_initialize_into_small_buffer.c: In function ‘int main()’:
    string_initialize_into_small_buffer.c:61:19: error: initializer-string for ‘char [5]’ is too long [-fpermissive]
       61 |     char str[5] = "Hello"; // works fine: "Hello World."
          |                   ^~~~~~~

*/
