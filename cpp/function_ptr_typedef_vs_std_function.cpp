/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
4 Feb. 2022

Passing a function ptr as a parameter or argument to another function!:
Remind myself how to use C-style function pointers, vs `typdedef`ed function pointers, vs C++
`std::function<>` objects.

STATUS: EXCELLENT! IT WORKS!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 function_ptr_typedef_vs_std_function.cpp -o bin/a && bin/a
```

References:
1. `std::function<>`: https://en.cppreference.com/w/cpp/utility/functional/function
1. *****+ How to typedef a function pointer in C or C++: https://stackoverflow.com/q/4295432/4561887
1. ***** [my question] https://stackoverflow.com/questions/31869026/c-function-call-via-an-object-with-public-member-pointer-to-function-without

*/


// C++ includes
#include <functional> // `std::function<>`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

typedef void (*voidvoidfunc_t)(void);
using voidvoidfunc2_t = std::function<void(void)>;

// -------------------------------------------------------------------------------
// BASIC `void(void)` PRINT FUNCTIONS TO BE PASSED AS ARGUMENTS TO OTHER FUNCTIONS
// -------------------------------------------------------------------------------

void print1()
{
    printf("print1\n");
}

void print2()
{
    printf("print2\n");
}

void print3()
{
    printf("print3\n");
}

// -------------------------------------------------------------------------------
// FUNCTIONS WHICH ACCEPT OTHER `void(void)` FUNCTIONS
// -------------------------------------------------------------------------------

// -------------------
// C-STYLE TECHNIQUES:
// -------------------

// [commonly-used in C, but hard to read] Using a raw function pointer
void printWithFunc1(void (*f)(void))
{
    f();
}

// [my favorite usage in C!] Using the typedef `voidvoidfunc_t` to a fuction pointer
// (much easier to read than above!)
void printWithFunc2(voidvoidfunc_t f)
{
    f();
}

// -------------------
// C++ TECHNIQUES:
// -------------------

// [easy-to-read in C++] Using a `std::function<>` directly
void printWithFunc3(std::function<void(void)> f)
{
    f();
}

// [very similar to the C typedef usage above] Using the `using`-style "typdedef" to a
// `std::function<>`
void printWithFunc4(voidvoidfunc2_t f)
{
    f();
}

// -------------------
// fancy function **call* practice; see my Q here: https://stackoverflow.com/q/31869026/4561887
// -------------------

void printWithFunc5(voidvoidfunc_t f)
{
    // see my Q and the answers here!: https://stackoverflow.com/q/31869026/4561887
    f();
    (*f)();
    (**f)();
    (***f)();
    // etc.
    (**********************************f)();

    printf("- - -\n");
}


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    printf("printWithFunc1\n");
    printWithFunc1(print1);
    printWithFunc1(print2);
    printWithFunc1(print3);
    printf("\n");

    printf("printWithFunc2\n");
    printWithFunc2(print1);
    printWithFunc2(print2);
    printWithFunc2(print3);
    printf("\n");

    printf("printWithFunc3\n");
    printWithFunc3(print1);
    printWithFunc3(print2);
    printWithFunc3(print3);
    printf("\n");

    printf("printWithFunc4\n");
    printWithFunc4(print1);
    printWithFunc4(print2);
    printWithFunc4(print3);
    printf("\n");

    printf("---------------\n"
           "Let's do a few more tests for kicks.\n"
           "Notice how passing the **address** to a function makes no difference.\n"
           "See my Q here: https://stackoverflow.com/q/31869026/4561887\n");
    printWithFunc1(&print1);
    printWithFunc1(&print2);
    printWithFunc1(&print3);
    printf("\n");

    printf("Fancy function calls:\n");
    printWithFunc5(print1);
    printWithFunc5(&print2); // intentional & in front--makes no difference
    printWithFunc5(print3);

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 function_ptr_typedef_vs_std_function.cpp -o bin/a && bin/a
    Hello world!

    printWithFunc1
    print1
    print2
    print3

    printWithFunc2
    print1
    print2
    print3

    printWithFunc3
    print1
    print2
    print3

    printWithFunc4
    print1
    print2
    print3

    ---------------
    Let's do a few more tests for kicks.
    Notice how passing the **address** to a function makes no difference.
    See my Q here: https://stackoverflow.com/q/31869026/4561887
    print1
    print2
    print3

    Fancy function calls:
    print1
    print1
    print1
    print1
    print1
    - - -
    print2
    print2
    print2
    print2
    print2
    - - -
    print3
    print3
    print3
    print3
    print3
    - - -


*/
