/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
3 Feb. 2022

Keep reading until ONLY Enter is pressed!
STATUS: works!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 read_until_only_enter_key.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 read_until_only_enter_key.c -o bin/a && bin/a
```

References:
1. https://stackoverflow.com/questions/70975906/how-do-i-take-in-the-enter-key-as-an-input-in-c

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
// #include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

/// Clear the stdin input stream by reading and discarding all incoming chars up
/// to and including the Enter key's newline ('\n') char. Once we hit the
/// newline char, stop calling `getc()`, as calls to `getc()` beyond that will
/// block again, waiting for more user input.
void clearStdin()
{
    // keep reading 1 more char as long as the end of the stream, indicated by
    // `EOF` (end of file), and the end of the line, indicated by the newline
    // char inserted into the stream when you pressed Enter, have NOT been
    // reached
    while (true)
    {
        int c = getc(stdin);
        if (c == EOF || c == '\n')
        {
            break;
        }
    }
}

// Returns true if only Enter was pressed, and false otherwise
bool getOnlyEnterKeypress()
{
    bool onlyEnterPressed = false;
    printf("Press ONLY the Enter key to continue: ");
    int firstChar = getc(stdin);
    if (firstChar == '\n')
    {
        printf("Good! You pressed ONLY the Enter key!\n");
        onlyEnterPressed = true;
    }
    else
    {
        printf("You failed. You pressed another key first.\n");
        clearStdin();
    }
    return onlyEnterPressed;
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    while (!getOnlyEnterKeypress()) {};

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 read_until_only_enter_key.c -o bin/a && bin/a
    Press ONLY the Enter key to continue: a
    You failed. You pressed another key first.
    Press ONLY the Enter key to continue: abc
    You failed. You pressed another key first.
    Press ONLY the Enter key to continue: w
    You failed. You pressed another key first.
    Press ONLY the Enter key to continue:
    Good! You pressed ONLY the Enter key!



OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 read_until_only_enter_key.c -o bin/a && bin/a
    Hello World.


*/
