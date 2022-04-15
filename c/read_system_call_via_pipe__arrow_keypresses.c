/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Write a program to read and ignore ALL key presses *except* arrow keys! It does this via a system
call through a pipe to the bash `read` cmd, with a timeout such that it operates in a polling loop
fashion at 10 Hz.
- This could prove useful for having arrow keys control a character in a simple game or
  something?--so long as the terminal is always in scope in order to receive the keypresses.
  There's probably a better way. :)

STATUS: done; works!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=gnu17 read_system_call_via_pipe__arrow_keypresses.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 read_system_call_via_pipe__arrow_keypresses.c -o bin/a && bin/a
```

References:
1. https://stackoverflow.com/q/1798511/4561887
1. https://stackoverflow.com/q/12709256/4561887
1. https://stackoverflow.com/questions/24016046/shell-script-respond-to-keypress
1. https://en.cppreference.com/w/c/program/system
1. https://stackoverflow.com/questions/448944/c-non-blocking-keyboard-input
1. https://en.cppreference.com/w/c/io/fgets
1. https://linux.die.net/man/3/popen
1. https://linux.die.net/man/3/pclose
1. *****+ https://stackoverflow.com/a/28971647/4561887 - popen example!
1. [MY ANSWER WITH THIS]: Read Key presses in C; ex.: Arrow keys, Enter key:
   https://stackoverflow.com/a/70980046/4561887

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <stdlib.h>

#define BUFSIZE 32

typedef enum arrowKey_e
{
    ARROWKEY_UNKNOWN = 0,
    ARROWKEY_UP,
    ARROWKEY_DOWN,
    ARROWKEY_LEFT,
    ARROWKEY_RIGHT,
} arrowKey_t;

// Modeled after my answer here: https://stackoverflow.com/a/54728664/4561887
const char* arrowKeyGetName(arrowKey_t arrowKey)
{
    const char* arrowKeyName = "TBD";

    switch (arrowKey)
    {
        case ARROWKEY_UNKNOWN:
            arrowKeyName = "ARROWKEY_UNKNOWN";
            break;
        case ARROWKEY_UP:
            arrowKeyName = "ARROWKEY_UP";
            break;
        case ARROWKEY_DOWN:
            arrowKeyName = "ARROWKEY_DOWN";
            break;
        case ARROWKEY_LEFT:
            arrowKeyName = "ARROWKEY_LEFT";
            break;
        case ARROWKEY_RIGHT:
            arrowKeyName = "ARROWKEY_RIGHT";
            break;
    }

    return arrowKeyName;
}

// Read a keyboard key press and return the character pressed, or a negative
// number in the event of an error.
// NB: for help reading output from system calls, see here:
//  1. https://stackoverflow.com/a/28971647/4561887
//  2. https://stackoverflow.com/a/18297075/4561887
arrowKey_t readArrowKeyPress()
{
    arrowKey_t arrowKeyPressed = ARROWKEY_UNKNOWN;

    // This bash cmd is from my answer here:
    // https://stackoverflow.com/a/70979348/4561887
    // `-n3` here means to read 3 chars at once, since an arrow key press
    // comes in as 3 chars.
    // The `-t .1` forces a timeout of that many seconds, which means the loop
    // interval will be this fast.
    const char* cmd = "bash -c 'read -s -t .1 -n3 c && printf \"%s\" \"$c\"'";
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        printf("\nError opening pipe!\n");
        return arrowKeyPressed;
    }

    char buf[BUFSIZE] = {0};
    char* retval1 = fgets(buf, BUFSIZE, fp);
    if (retval1 == NULL)
    {
        // printf("\nFailed to read cmd response.\n");
        // Timeout occured; just exit.
        return arrowKeyPressed;
    }

    // See meaning of this return value here:
    // https://stackoverflow.com/questions/43116/how-can-i-run-an-external-program-from-c-and-parse-its-output/28971647#comment60311936_28971647
    int retval2 = pclose(fp);
    if (retval2 == -1)
    {
        printf("\nError obtaining the cmd's exit status code.\n");
        return arrowKeyPressed;
    }
    else if (retval2 != 0)
    {
        printf("\nCommand exited with exit status code %i.\n", retval2);
        return arrowKeyPressed;
    }

    // Map the readings to arrow keys
    if ((buf[0] == 27) && (buf[1] == 91) && (buf[2] == 65))
    {
        arrowKeyPressed = ARROWKEY_UP;
    }
    else if ((buf[0] == 27) && (buf[1] == 91) && (buf[2] == 66))
    {
        arrowKeyPressed = ARROWKEY_DOWN;
    }
    else if ((buf[0] == 27) && (buf[1] == 91) && (buf[2] == 67))
    {
        arrowKeyPressed = ARROWKEY_RIGHT;
    }
    else if ((buf[0] == 27) && (buf[1] == 91) && (buf[2] == 68))
    {
        arrowKeyPressed = ARROWKEY_LEFT;
    }

    return arrowKeyPressed;
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Press any arrow key. Press Ctrl + C to quit.\n");
    fflush(stdout);

    while (true)
    {
        arrowKey_t arrowKeyPressed = readArrowKeyPress();
        if (arrowKeyPressed == ARROWKEY_UNKNOWN)
        {
            continue;
        }
        printf("Key pressed = %s\n", arrowKeyGetName(arrowKeyPressed));
    }

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 read_system_call_via_pipe__arrow_keypresses.c -o bin/a && bin/a
    Press any arrow key. Press Ctrl + C to quit.
    Key pressed = ARROWKEY_DOWN
    Key pressed = ARROWKEY_UP
    Key pressed = ARROWKEY_LEFT
    Key pressed = ARROWKEY_RIGHT
    Key pressed = ARROWKEY_UP
    Key pressed = ARROWKEY_DOWN
    Key pressed = ARROWKEY_LEFT
    Key pressed = ARROWKEY_RIGHT
    Key pressed = ARROWKEY_UP
    Key pressed = ARROWKEY_DOWN
    Key pressed = ARROWKEY_LEFT
    Key pressed = ARROWKEY_RIGHT



OR, in C++ [SAME]:

*/
