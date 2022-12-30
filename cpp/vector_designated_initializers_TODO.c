/*

Oct. 2022

I forgot what I was going to do here, but start by reading the 2 links just below. Obviously I was
going to do some demos and learning about "Designated Initializers" in C and C++. That's a topic I
need to study up on more in order to solidify in my mind.

See:
1. https://stackoverflow.com/questions/9849719/what-do-square-brackets-mean-in-array-initialization-in-c/9849782#9849782
1. https://gcc.gnu.org/onlinedocs/gcc/Designated-Inits.html

be sure to also do a demo which shows whether uninitialized indices are initialized to zero.
See: https://stackoverflow.com/questions/9849719/what-do-square-brackets-mean-in-array-initialization-in-c/9849782#comment125282837_9849782
/////////////
*/

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

(description)

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_designated_initializers.cpp -o bin/a && bin/a
```

References:
1.

*/


// C++ includes
// #include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
// #include <cstdint>  // For `uint8_t`, `int8_t`, etc.
// #include <cstdio>   // For `printf()`
#include <stdio.h>

int a[6] = { [4] = 29, [2] = 15 };

int int_array[] =
{
    [0] = 1,
    [3] = 3,
};

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello world\n");
    // std::cout << "world!\n";

    for (size_t i = 0; i < sizeof(int_array)/sizeof(int_array[0]); i++)
    {
        printf("%lu: %i\n", i, int_array[i]);
    }

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_designated_initializers.cpp -o bin/a && bin/a
    Hello world!

*/
