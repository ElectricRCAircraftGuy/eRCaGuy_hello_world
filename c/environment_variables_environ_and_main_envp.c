/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
17 Aug. 2022

Practice reading shell environment variables in C using the 3rd and optional parameter to
`main()` **and** by using the POSIX `environ` variable. Search for `environ` here, for ex:
https://en.cppreference.com/w/c/program/getenv

Note: if you ever want to **set** an environment variable, use `setenv()`
(https://man7.org/linux/man-pages/man3/setenv.3.html)!


STATUS: done and works! **Excellent** example!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 environment_variables_environ_and_main_envp.c -o bin/a -lm \
&& export MY_EXPORTED_VAR="12345 I am exported" && MY_CUSTOM_VAR="hey you!" bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 environment_variables_environ_and_main_envp.c -o bin/a \
&& export MY_EXPORTED_VAR="12345 I am exported" && MY_CUSTOM_VAR="hey you!" bin/a
```

References:
1. `getenv()` std C function
    1. *****https://en.cppreference.com/w/c/program/getenv
    1. https://man7.org/linux/man-pages/man3/getenv.3.html
1. `main()` function with `envp` environment pointer in it:
    1. C reference: https://en.cppreference.com/w/c/language/main_function
    1. *****gcc manual:  https://www.gnu.org/software/libc/manual/html_mono/libc.html#Program-Arguments
        > The first two arguments are just the same. The third argument envp gives the program’s
          environment; it is the same as the value of environ. See Environment Variables. **POSIX.1
          does not allow this three-argument form, so to be portable it is best to write main to
          take two arguments, and use the value of `environ`**.
1. https://man7.org/linux/man-pages/man7/environ.7.html
1. https://man7.org/linux/man-pages/man3/setenv.3.html
1. [my answer] "source (.) vs export (and also some file lock [flock] stuff at the end)":
   https://stackoverflow.com/a/62626515/4561887
1. ***** meaning of argv, argc, and envp in `main()`: https://stackoverflow.com/a/54723654/4561887
1. Print the environment variables using `environ`: https://stackoverflow.com/q/4291080/4561887

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <stdlib.h>  // `getenv()`

/// `environ` is a global POSIX variable containing all environment variable names and their values
///  in it.
/// See:
///     https://man7.org/linux/man-pages/man7/environ.7.html and
///     https://en.cppreference.com/w/c/program/getenv
/// There are **two ways** to get access to the `environ` variable:
/// 1. Declare it `extern`, like this: `extern char **environ;`
extern char **environ;
/// OR 2. Define `__USE_GNU` and then include `<unistd.h>` like this:
// #define __USE_GNU
// #include <unistd.h>


// int main(int argc, char *argv[])  // alternative prototype
// See: https://en.cppreference.com/w/c/language/main_function

/// \brief          The `main()` function, which is the entry point for all C and C++ programs.
/// \param[in]      argc        The argument count, or number of arguments passed to the executable
///                             at run-time.
/// \param[in]      argv        An array of strings containing all of the arguments passed to the
///                             executable at run-time.
/// \param[in]      envp        "environment pointer": an array of strings containing all
///                             "key=value" environment variables set prior to running this
///                             executable.
///                             See: https://stackoverflow.com/a/54723654/4561887 and
///                             https://en.cppreference.com/w/c/language/main_function and see:
/// *****gcc manual:  https://www.gnu.org/software/libc/manual/html_mono/libc.html#Program-Arguments
/// > The first two arguments are just the same. The third argument envp gives the program’s
///   environment; it is the same as the value of environ. See Environment Variables. **POSIX.1
///   does not allow this three-argument form, so to be portable it is best to write main to
///   take two arguments, and use the value of `environ`.**
/// \return         0 for no error, or any other integer value for error.
int main(int argc, const char* argv[], const char* envp[])
{
    printf("\n");

    printf("============================================================================\n");
    printf("1. Printing input arguments from C `argv` input to main (`argc` count = %i).\n", argc);
    printf("============================================================================\n");
    // Read through the vector `argc` times.
    for (int i = 0; i < argc; i++)
    {
        printf("%4i: %s\n", i, argv[i]);
    }
    printf("\n");

    printf("============================================================================\n");
    printf("2. Printing environment variables from (gcc/POSIX?) `envp` input to main.\n");
    printf("============================================================================\n");
    // This vector is null-terminated, so read through it until you hit a NULL char*.
    for (size_t i = 0; envp[i] != NULL; i++)
    {
        printf("%4zu: %s\n", i, envp[i]);
    }
    printf("\n");

    printf("============================================================================\n");
    printf("3. Printing environment variables from POSIX `environ` extern global var.\n");
    printf("============================================================================\n");
    // This vector is null-terminated, so read through it until you hit a NULL char*.
    for (size_t i = 0; environ[i] != NULL; i++)
    {
        printf("%4zu: %s\n", i, environ[i]);
    }
    printf("\n");


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 environment_variables_environ_and_main_envp.c -o bin/a -lm && export MY_EXPORTED_VAR="12345 I am exported" && MY_CUSTOM_VAR="hey you!" bin/a

    ============================================================================
    1. Printing input arguments from C `argv` input to main (`argc` count = 1).
    ============================================================================
       0: bin/a

    ============================================================================
    2. Printing environment variables from (gcc/POSIX?) `envp` input to main.
    ============================================================================
       0: MY_CUSTOM_VAR=hey you!
       1: LS_COLORS=rs=0:di=01;34:l
...[RUN THIS CODE YOURSELF FOR FULL OUTPUT!]

    ============================================================================
    3. Printing environment variables from POSIX `environ` extern global var.
    ============================================================================
       0: MY_CUSTOM_VAR=hey you!
       1: LS_COLORS=rs=0:di=01;34:l
...[RUN THIS CODE YOURSELF FOR FULL OUTPUT!]


OR, in C++:
(same result as in C)


*/
