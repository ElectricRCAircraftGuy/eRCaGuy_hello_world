/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
3 Feb. 2022

Lean how to read in an Enter key press, and all preceding keystrokes up to that, in C. The downside
of using `getc()` is that you MUST press Enter at the end in order to make `getc()` return.
If this behavior is NOT desired, and you want to read key-presses live withOUT having to press
Enter at the end, see "read_keypress_system_call.c" and "read_string_and_arrow_keys.c".

STATUS: WORKS

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 read_in_any_key.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 read_in_any_key.c -o bin/a && bin/a
```

References:
1. https://stackoverflow.com/questions/70975906/how-do-i-take-in-the-enter-key-as-an-input-in-c
1. [MY ANSWER] https://stackoverflow.com/a/70978704/4561887

*/

// #include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Press any number of keys followed by Enter, or just Enter alone, to continue: ");
    int c = getc(stdin);
    printf("The first character you entered is decimal %i (\"%c\").\n", c, c);

    // If you entered one or more characters above before pressing Enter, they
    // are still in the stdin input stream's buffer, so let's read those out
    // too, up to the newline char (`'\n'`) created by pressing Enter.
    uint32_t charNum = 2;
    while (c != '\n')
    {
        c = getc(stdin);
        if (c == EOF)
        {
            printf("Failed to get char!\n");
            break;
        }
        printf("char %-2u = decimal %i (\"%c\").\n", charNum, c, c);
        charNum++;
    }

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 read_in_any_key.c -o bin/a && bin/a
    Press any key followed by Enter, or just Enter alone, to continue: abcdefghijklmnop
    The first character you entered is decimal 97 ("a").
    char 2  = decimal 98 ("b").
    char 3  = decimal 99 ("c").
    char 4  = decimal 100 ("d").
    char 5  = decimal 101 ("e").
    char 6  = decimal 102 ("f").
    char 7  = decimal 103 ("g").
    char 8  = decimal 104 ("h").
    char 9  = decimal 105 ("i").
    char 10 = decimal 106 ("j").
    char 11 = decimal 107 ("k").
    char 12 = decimal 108 ("l").
    char 13 = decimal 109 ("m").
    char 14 = decimal 110 ("n").
    char 15 = decimal 111 ("o").
    char 16 = decimal 112 ("p").
    char 17 = decimal 10 ("
    ").



OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 read_in_any_key.c -o bin/a && bin/a
    Hello World.


*/
