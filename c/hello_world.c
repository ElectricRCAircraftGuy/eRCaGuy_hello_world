/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

hello_world

Gabriel Staples
www.ElectricRCAircraftGuy.com
27 Mar. 2019 

Examples of how to compile & run:
- NB: c90 requires C-style comments (slash star, star slash) and does NOT work with modern
      C++-style // comments!
- UPDATE: DON'T JUST DO -Wall (which includes -Wformat and -Wswitch and other things), also add in -Werror! 
  The -Wall enables ALL WARNINGS, and the -Werror converts all warnings into build errors so it will not 
  compile! Therefore, compile only with `-Wall -Werror` to have safer code! 
  - See all warning options in the gcc user manual here on the "Warning Options" page: 
    https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
  C:
    gcc -Wall -Werror -g3 -o hello_world hello_world.c && ./hello_world
    gcc -Wall -Werror -g3 -std=c90 -o hello_world hello_world.c -lm && ./hello_world
    gcc -Wall -Werror -g3 -std=c99 -o hello_world hello_world.c -lm && ./hello_world
    gcc -Wall -Werror -g3 -std=c11 -o hello_world hello_world.c -lm && ./hello_world
  C++:
    g++ -Wall -Werror -g3 -o hello_world hello_world.c && ./hello_world
    g++ -Wall -Werror -g3 -std=c++98 -o hello_world hello_world.c && ./hello_world
    g++ -Wall -Werror -g3 -std=c++03 -o hello_world hello_world.c && ./hello_world
    g++ -Wall -Werror -g3 -std=c++11 -o hello_world hello_world.c && ./hello_world

Note: `-g3` adds full debugging info! See the `-g` and `-glevel` options here: 
      https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html

References:
- this code posted as my answer here! https://stackoverflow.com/a/55384270/4561887 


*/

// #include <stdio.h>   // for printf
#include <stdbool.h> // for `true` and `false`

#ifdef __cplusplus
extern "C" {
#endif
// A hacky alternative to including stdio.h above! Writing the prototype, or declaration, to a
// function like this in order to declare its existence and be able to use it is called a
// "forward declaration", and it allows you to use this function withOUT including its header file
// so long as the forward-declared function **definition** is also found by the linker as a symbol
// within the compiled gcc GNU LibC object/binary file, which library the linker links to during
// the `gcc` compilation process.
int printf ( const char * format, ... ); // a hacky alternative to including stdio.h above! 
#ifdef __cplusplus
}
#endif

int main(void)
{
    printf("Hello World\n");
    printf("`true == 1`? = %i, `true == 1`? = %s\n", true, (true == 1 ? "true" : "false"));

    return 0;
}

/*
Sample Output:

C11:

    $ gcc -Wall -Werror -g3 -std=c11 -o hello_world hello_world.c && ./hello_world
    Hello World
    `true == 1`? = 1, `true == 1`? = true

C++11:

    $ g++ -Wall -Werror -g3 -std=c++11 -o hello_world hello_world.c && ./hello_world
    Hello World
    `true == 1`? = 1, `true == 1`? = true



*/

