/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
25 Apr. 2020

Let's play with some explicit template specialization to learn about it.

References:
1. https://en.wikipedia.org/wiki/Template_(C%2B%2B)#Template_specialization


Other References:
1. http://www.cplusplus.com/doc/tutorial/program_structure/
1. C++ standards available in gcc/g++: http://gcc.gnu.org/onlinedocs/gcc/Standards.html
1. Basic C compiling & running: http://www.network-theory.co.uk/docs/gccintro/gccintro_9.html 
1. Basic C++ compiling & running: http://www.network-theory.co.uk/docs/gccintro/gccintro_54.html

To compile and run:
    g++ -Wall -Werror -g3 -std=c++17 -o explicit_template_specialization \
    explicit_template_specialization.cpp && ./explicit_template_specialization

Examples of how to compile & run:
- NB: c90 requires C-style comments (slash star, star slash) and does NOT work with modern
      C++-style // comments!
- UPDATE: DON'T JUST DO -Wall (which includes -Wformat and -Wswitch and other things), also add in -Werror! 
  The -Wall enables ALL WARNINGS, and the -Werror converts all warnings into build errors so it will not 
  compile! Therefore, compile only with `-Wall -Werror` to have safer code! 
  - See all warning options in the gcc user manual here on the "Warning Options" page: 
    https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
- Note: `-g3` adds full debugging info! See the `-g` and `-glevel` options here: 
  https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html
  C:
    gcc -Wall -Werror -g3 -o hello_world hello_world.c && ./hello_world
    gcc -Wall -Werror -g3 -std=c90 -o hello_world hello_world.c && ./hello_world
    gcc -Wall -Werror -g3 -std=c99 -o hello_world hello_world.c && ./hello_world
    gcc -Wall -Werror -g3 -std=c11 -o hello_world hello_world.c && ./hello_world
  C++:
    g++ -Wall -Werror -g3 -o hello_world hello_world.c && ./hello_world
    g++ -Wall -Werror -g3 -std=c++98 -o hello_world hello_world.c && ./hello_world
    g++ -Wall -Werror -g3 -std=c++03 -o hello_world hello_world.c && ./hello_world
    g++ -Wall -Werror -g3 -std=c++11 -o hello_world hello_world.c && ./hello_world
    g++ -Wall -Werror -g3 -std=c++14 -o hello_world hello_world.c && ./hello_world
    g++ -Wall -Werror -g3 -std=c++17 -o hello_world hello_world.c && ./hello_world

To get the intermediate files along with the executable:
(Source: https://www.geeksforgeeks.org/compiling-a-c-program-behind-the-scenes/)
ie: 1) .hh, .cpp C++ files --[preprocessing]--> 
    2) .ii preprocessed C++ files --[compiling]--> 
    3) .s assembly language files --[assembly]-->
    4) .o object (machine code) files --[linking]-->
    #) executable (machine code) file [Done!]
  `g++ -Wall -std=c++11 -save-temps hello_world.cpp -o hello_world`

COMPILE AND RUN ALL IN ONE! <========== EASIEST
    g++ -Wall -std=c++11 -save-temps hello_world.cpp -o hello_world && ./hello_world
COMPILE AND RUN ALL IN ONE, OUTPUTTING EVERYTHING TO ./bin/ <========== MY FAVORITE
    mkdir -p bin && g++ -Wall -std=c++11 -save-temps=obj hello_world.cpp -o ./bin/hello_world && ./bin/hello_world
    - For meaning of -save-temps=obj, see: https://stackoverflow.com/a/46256372/4561887
    - basically, it tells the temp objects to go to the same location as the -o setting!

For multiple files:
  `g++ -Wall -std=c++11 hello_world.cpp file2.cpp file3.cpp -o hello_world`
  `./hello_world`

*/

#include <stdio.h>

#include <iostream>


int main()
{
    printf("Hello World\n");

    return 0;
}







