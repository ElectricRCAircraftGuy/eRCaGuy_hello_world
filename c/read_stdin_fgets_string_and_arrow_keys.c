/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
3 Feb. 2022

Read in a string OR ARROW KEY PRESSES! This uses `fgets()`, which, like `getc()`, requires you press
Enter to end it and return.

See here:
It says: https://en.cppreference.com/w/c/io/fgets
> Parsing stops if a newline character is found, in which case str will contain that newline
  character, or if end-of-file occurs.

STATUS: WORKS

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 read_string_and_arrow_keys.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 read_string_and_arrow_keys.c -o bin/a && bin/a
```

References:
1. https://stackoverflow.com/questions/70975906/how-do-i-take-in-the-enter-key-as-an-input-in-c

*/

// #include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
// #include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <string.h> // `strlen()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Press any key followed by Enter, or just Enter alone, to continue: ");
    char buf[1024];
    char* retval = fgets(buf, sizeof(buf), stdin);
    if (retval == NULL)
    {
        printf("fgets() failed!\n");
    }
    else
    {
        // Strip off the trailing newline char
        size_t len = strlen(buf);
        buf[len - 1] = '\0';
        len -= 1;

        // Print decimal bytes
        printf("You entered these decimal bytes: [");
        for (size_t i = 0; i < len; i++)
        {
            printf("%u", buf[i]);
            if (i < len - 1)
            {
                printf(", ");
            }
        }
        printf("]\n");

        // Check for arrow keys, which show up as a sequence of 3 chars
        if (len >= 3)
        {
            // Note: do `- 2` so I can read this char plus the next 2 to check for arrow keys
            for (size_t i = 0; i < len - 2; i++)
            {
                if ((buf[i] == 27) && (buf[i + 1] == 91) && (buf[i + 2] == 65))
                {
                    printf("UP ARROW\n");
                    // Replace this arrow key sequence with something else
                    buf[i] = '[';
                    buf[i + 1] = 'U';
                    buf[i + 2] = ']';
                    i += 2;
                }
                else if ((buf[i] == 27) && (buf[i + 1] == 91) && (buf[i + 2] == 66))
                {
                    printf("DOWN ARROW\n");
                    // Replace this arrow key sequence with something else
                    buf[i] = '[';
                    buf[i + 1] = 'D';
                    buf[i + 2] = ']';
                    i += 2;
                }
                else if ((buf[i] == 27) && (buf[i + 1] == 91) && (buf[i + 2] == 67))
                {
                    printf("RIGHT ARROW\n");
                    // Replace this arrow key sequence with something else
                    buf[i] = '[';
                    buf[i + 1] = 'R';
                    buf[i + 2] = ']';
                    i += 2;
                }
                else if ((buf[i] == 27) && (buf[i + 1] == 91) && (buf[i + 2] == 68))
                {
                    printf("LEFT ARROW\n");
                    // Replace this arrow key sequence with something else
                    buf[i] = '[';
                    buf[i + 1] = 'L';
                    buf[i + 2] = ']';
                    i += 2;
                }
            }
        }

        // Print string as chars
        printf("You entered this string: \"%s\".\n", buf);
    }

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

I pressed "abc" then Right Left Up Down arrow keys:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 read_string_and_arrow_keys.c -o bin/a && bin/a
    Press any key followed by Enter, or just Enter alone, to continue: abc^[[C^[[D^[[A^[[B
    You entered these decimal bytes: [97, 98, 99, 27, 91, 67, 27, 91, 68, 27, 91, 65, 27, 91, 66]
    RIGHT ARROW
    LEFT ARROW
    UP ARROW
    DOWN ARROW
    You entered this string: "abc[R][L][U][D]".


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 read_string_and_arrow_keys.c -o bin/a && bin/a
    Hello World.


*/
