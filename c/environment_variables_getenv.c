/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
17 Aug. 2022

Practice reading shell environment variables in C using `getenv()`. Also show how to export
variables in the terminal before calling this executable, so we can see that they are readable
herein!

Note: if you ever want to **set** an environment variable, use `setenv()`
(https://man7.org/linux/man-pages/man3/setenv.3.html)!


STATUS: done and works! **Excellent** example!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 environment_variables_getenv.c -o bin/a -lm \
&& export MY_EXPORTED_VAR="12345 I am exported" && MY_CUSTOM_VAR="hey you!" bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 environment_variables_getenv.c -o bin/a \
&& export MY_EXPORTED_VAR="12345 I am exported" && MY_CUSTOM_VAR="hey you!" bin/a
```

References:
1. `getenv()` std C function
    1. *****https://en.cppreference.com/w/c/program/getenv
    1. https://man7.org/linux/man-pages/man3/getenv.3.html
1. https://en.cppreference.com/w/c/language/main_function
1. https://man7.org/linux/man-pages/man7/environ.7.html
1. https://man7.org/linux/man-pages/man3/setenv.3.html
1. [my answer] source (.) vs export (and also some file lock [flock] stuff at the end):
   https://stackoverflow.com/a/62626515/4561887

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <stdlib.h>  // `getenv()`

void print_environment_variable(const char* env_variable_name)
{
    const char* env_variable_value = getenv(env_variable_name);
    if (env_variable_value == NULL)
    {
        printf("Error: environment variable '%s' not found!\n",
            env_variable_name);
    }
    else
    {
        printf("%s = %s\n", env_variable_name, env_variable_value);
    }
    printf("\n");
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Reading environment variables.\n\n");

    print_environment_variable("Path");             // not found
    print_environment_variable("PATH");             // works
    print_environment_variable("PWD");              // works
    print_environment_variable("MY_CUSTOM_VAR");    // works; is set at call time
    print_environment_variable("MY_EXPORTED_VAR");  // works; is exported *before* call-time! For
        // what "exported" means, see my answer here: https://stackoverflow.com/a/62626515/4561887
    print_environment_variable("random_var");       // not found


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 environment_variables_getenv.c -o bin/a -lm && export MY_EXPORTED_VAR="12345 I am exported" && MY_CUSTOM_VAR="hey you!" bin/a
    Reading environment variables.

    Error: environment variable 'Path' not found!

    PATH = /home/gabriel/.local/bin:/home/gabriel/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/gabriel/.local/bin:/home/gabriel/.local/bin:/home/gabriel/.fzf/bin:/usr/local/go/bin

    PWD = /home/gabriel/GS/dev/eRCaGuy_hello_world/c

    MY_CUSTOM_VAR = hey you!

    MY_EXPORTED_VAR = 12345 I am exported

    Error: environment variable 'random_var' not found!



OR, in C++:
(same result as in C)


*/
