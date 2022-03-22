/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Feb. 2022

Use a bash system call to read in keypresses live withOUT forcing the user to press Enter at the
end, unlike `getc()`, which won't return until you press Enter. See "read_in_any_key.c" for a
`getc()` example instead, if pressing Enter at the end is ok.

STATUS: works! Done!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=gnu17 read_keypress_system_call.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 read_keypress_system_call.c -o bin/a && bin/a
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
1. *****More on pipes to pipes in C: see my comment here and the gist link in my comment:
   https://stackoverflow.com/questions/12032323/piping-the-output-of-one-command-as-input-to-another-command#comment126352138_12032323
    1. https://gist.github.com/mplewis/5279108
1. [MY ANSWER WITH THIS]

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <stdlib.h>

#define BUFSIZE 32

// Read a keyboard key press and return the character pressed, or a negative
// number in the event of an error.
// NB: for help reading output from system calls, see here:
//  1. https://stackoverflow.com/a/28971647/4561887
//  2. https://stackoverflow.com/a/18297075/4561887
char getKeypress()
{
    // This bash cmd is from my answer here:
    // https://stackoverflow.com/a/70979348/4561887
    const char* cmd = "bash -c 'read -s -n1 c && printf \"%s\" \"$c\"'";
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        printf("\nError opening pipe!\n");
        return -1;
    }

    char buf[BUFSIZE] = {0};
    char* retval1 = fgets(buf, BUFSIZE, fp);
    if (retval1 == NULL)
    {
        printf("\nFailed to read cmd response.\n");
        return -2;
    }

    // See meaning of this return value here:
    // https://stackoverflow.com/questions/43116/how-can-i-run-an-external-program-from-c-and-parse-its-output/28971647#comment60311936_28971647
    int retval2 = pclose(fp);
    if (retval2 == -1)
    {
        printf("\nError obtaining the cmd's exit status code.\n");
        return -3;
    }
    else if (retval2 != 0)
    {
        printf("\nCommand exited with exit status code %i.\n", retval2);
        return -4;
    }

    char keyPressed = buf[0];
    return keyPressed;
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Press any key to continue: ");
    fflush(stdout);
    char keyPressed = getKeypress();
    if (keyPressed > 0)
    {
        printf("\nKey pressed = %c\n", keyPressed);
    }

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 read_keypress_system_call.c -o bin/a && bin/a
    Press any key to continue:
    Key pressed = P


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 read_keypress_system_call.c -o bin/a && bin/a
    Press any key to continue:
    Key pressed = u

*/
