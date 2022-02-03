/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Iterate over a C-style enum in C++. I need to know if a postfix increment (`my_enum++`) is allowed.
See my answer: https://stackoverflow.com/a/69774217/4561887

GS
2 Feb. 2022

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 enum_c_style_iterate.cpp -o bin/a && bin/a
```

References:
1. [my answer] https://stackoverflow.com/a/69774217/4561887

*/


// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

enum my_error_type_t
{
    MY_ERROR_TYPE_SOMETHING_1 = 0,
    MY_ERROR_TYPE_SOMETHING_2,
    MY_ERROR_TYPE_SOMETHING_3,
    MY_ERROR_TYPE_SOMETHING_4,
    MY_ERROR_TYPE_SOMETHING_5,
    /// Not a valid value; this is the number of members in this enum
    MY_ERROR_TYPE_count,
    // helpers for iterating over the enum
    MY_ERROR_TYPE_begin = 0,
    MY_ERROR_TYPE_end = MY_ERROR_TYPE_count,
};

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    // NB: postfix increment (`my_error_type++`) not allowed! `operator+=()` also NOT allowed on enums!
    // Example error if I try to do `my_error_type++`:
    //
    //      enum_c_style_iterate.cpp:48:26: error: no ‘operator++(int)’ declared for postfix ‘++’ [-fpermissive]
    //                   my_error_type++)
    //                   ~~~~~~~~~~~~~^~
    for (my_error_type_t my_error_type = MY_ERROR_TYPE_begin;
            my_error_type < MY_ERROR_TYPE_end;
            my_error_type = (my_error_type_t)(my_error_type + 1))
    {
        switch (my_error_type)
        {
            case MY_ERROR_TYPE_SOMETHING_1:
                printf("MY_ERROR_TYPE_SOMETHING_1\n");
                break;
            case MY_ERROR_TYPE_SOMETHING_2:
                printf("MY_ERROR_TYPE_SOMETHING_2\n");
                break;
            case MY_ERROR_TYPE_SOMETHING_3:
                printf("MY_ERROR_TYPE_SOMETHING_3\n");
                break;
            case MY_ERROR_TYPE_SOMETHING_4:
                printf("MY_ERROR_TYPE_SOMETHING_4\n");
                break;
            case MY_ERROR_TYPE_SOMETHING_5:
                printf("MY_ERROR_TYPE_SOMETHING_5\n");
                break;
            case MY_ERROR_TYPE_count:
                // This case will never be reached.
                break;
        }
    }

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 enum_c_style_iterate.cpp -o bin/a && bin/a
    Hello world!

    MY_ERROR_TYPE_SOMETHING_1
    MY_ERROR_TYPE_SOMETHING_2
    MY_ERROR_TYPE_SOMETHING_3
    MY_ERROR_TYPE_SOMETHING_4
    MY_ERROR_TYPE_SOMETHING_5

*/
