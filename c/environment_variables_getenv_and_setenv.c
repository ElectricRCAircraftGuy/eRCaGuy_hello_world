///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Aug. 2023

Practice getting and setting environment variables in C, as well as reading their values via the
`environ` (https://man7.org/linux/man-pages/man7/environ.7.html) array of environment variable
strings.
- I'll use GDB and my `print_environ` custom GDB function to check things in the GDB debugger, as
  explained in my answer here: https://stackoverflow.com/a/76903706/4561887.

STATUS: done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./environment_variables_getenv_and_setenv.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 environment_variables_getenv_and_setenv.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 environment_variables_getenv_and_setenv.c -o bin/a && bin/a
```

References:
1. My answer about GDB and `environ`: https://stackoverflow.com/a/76903706/4561887
1. https://man7.org/linux/man-pages/man7/environ.7.html
1. https://man7.org/linux/man-pages/man3/getenv.3.html
1. https://man7.org/linux/man-pages/man3/setenv.3.html
1. https://man7.org/linux/man-pages/man3/sleep.3.html

*/


#include <errno.h>
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <stdlib.h>  // For `setenv()` and `getenv()`
#include <string.h>  // For `strerror()`
#include <unistd.h>  // For `sleep()`

void sleep_seconds(unsigned int sec)
{
    unsigned int retcode = sleep(sec);
    if (retcode != 0)
    {
        printf("Error: failed to fully sleep. Remaining sleep time = %u sec.\n", retcode);
    }
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    uint32_t i = 0;
    while (true)
    {
        const char* ENV_VARIABLE_NAME = "FOO";

        // Set environment variable with the counter in it. Ex: `FOO="bar_1".
        char env_var_value[100];
        sprintf(env_var_value, "bar_%u", i);
        int retcode = setenv(ENV_VARIABLE_NAME, env_var_value, true);
        if (retcode == -1)
        {
            printf("Error: failed to set the environment variable. errno = %i: %s\n",
                errno, strerror(errno));
        }

        // Get the environment variable now, to see if it was set correctly above
        char* env_variable_value = getenv(ENV_VARIABLE_NAME);
        if (env_variable_value == NULL)
        {
            printf("Error: environment variable '%s' not found!\n", ENV_VARIABLE_NAME);
        }
        else
        {
            printf("%s = %s\n", ENV_VARIABLE_NAME, env_variable_value);
        }

        i++;
        sleep_seconds(1);
    }

    return 0;
}


/*
SAMPLE OUTPUT:

In C (note: use Ctrl + C to kill it):

    eRCaGuy_hello_world$ c/environment_variables_getenv_and_setenv.c
    Hello World.

    FOO = bar_0
    FOO = bar_1
    FOO = bar_2
    FOO = bar_3
    FOO = bar_4
    FOO = bar_5
    FOO = bar_6
    FOO = bar_7
    FOO = bar_8
    FOO = bar_9
    FOO = bar_10
    FOO = bar_11
    FOO = bar_12


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 environment_variables_getenv_and_setenv.c -o bin/a && bin/a

    [same output as in C]

*/
