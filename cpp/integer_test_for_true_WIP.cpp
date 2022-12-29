/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
11 Sept. 2022

If you have `int i1` and `int i2`, what does `if (a && b)` really mean?
>>>> Under what conditions is an integer considered `true`? <<<<

THE PURPOSE OF THIS TEST CODE was for me to write my answer to this now-deleted question here:
[What does `while (a && b)` do when `a` and `b` are both integers? [duplicate]]
(https://stackoverflow.com/q/73683913/4561887)

MY NEW ANSWER, WHICH USES THE CODE BELOW, IS NOW HERE:
How an 'if (A && B)' statement is evaluated?:
[What does `while (a && b)` do when `a` and `b` are both integers, floating point types, or pointers?]
(https://stackoverflow.com/a/74407605/4561887) <======================== JUST SEE MY ANSWER HERE INSTEAD NOW! <=============================


KEY TAKEAWAY: these are all **exactly equivalent**!:

```cpp
int a = 2;
int b = 3;

// these are all **exactly equivalent**!:
while (a && b);
while ((bool)a && (bool)b);
while ((bool)a == true && (bool)b == true);
while (((bool)a == true) && ((bool)b == true));
while (a != 0 && b != 0);
while ((a != 0) && (b != 0));
```

This, however, is NOT the same, since `true` is defined strictly as `1`, and `false` is defined strictly as `0`:

```cpp
while (a == true && b == true);
while ((a == true) && (b == true));
```

The above two lines are like writing this:
```cpp
while (a == 1 && b == 1);
```

Integer `a` is currently 2 and b currently 3, for instance, so of course that
does NOT equate to the same thing as , since `(bool)a` is indeed currently
`true`(`1`), as is `(bool)b`, since they are both non-zero, and `
(bool)some_int` for ALL non-zero integers is `true` (`1`).

```

So, consider this:
```cpp
std::
```


That is because `a` is currently



STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 integer_test_for_true.cpp -o bin/a && bin/a
```

References:
1. What does (a&&b) in the following code entail?: https://stackoverflow.com/q/73683913/4561887

*/

// C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    int i1 = 2;
    int i2 = 3;

    // activate boolalpha mode so that 0 prints as "false" and 1 as "true"
    std::cout << std::boolalpha;

    std::cout << 0 << "\n";         // 0
    std::cout << false << "\n";     // false
    std::cout << 1 << "\n";         // 1
    std::cout << true << "\n";      // true
    std::cout << "\n";

    std::cout << (false == 0) << "\n";  // true
    std::cout << (true == 1) << "\n";   // true
    // turn OFF boolalpha mode
    std::cout << std::noboolalpha;
    std::cout << false << "\n";         // 0
    std::cout << true << "\n";          // 1
    // and turn it back ON again
    std::cout << std::boolalpha;
    std::cout << "\n";

    // Prove that any non-zero integer is NOT equal to true, but it IS equal to
    // not false! :).
    // BUT, when cast to a `bool`, ALL non-zero integers are `true`!
    std::cout << ((bool)i1 == true) << "\n";                     // true
    std::cout << ((bool)i2 == true) << "\n";                     // true
    std::cout << ((bool)i1 == true && (bool)i2 == true) << "\n"; // true
    std::cout << (i1 == true) << "\n";                           // false
    std::cout << (i2 == true) << "\n";                           // false
    std::cout << (i1 == true && i2 == true) << "\n";             // false
    std::cout << (i1 != false) << "\n";                          // true
    std::cout << (i1 != false) << "\n";                          // true
    std::cout << "\n";

    // This is exactly identical to this!:
    //      `std::cout << ((bool)i1 == true && (bool)i2 == true) << "\n";`
    std::cout << (i1 && i2) << "\n";                             // true
    std::cout << "\n";

    i1 = 1; // 1 means "true"
    i2 = 0; // 0 means "false"
    std::cout << (i1 == true) << "\n";                  // true
    std::cout << (i2 == false) << "\n";                 // true
    std::cout << "\n";

    std::cout << (bool)i1 << "\n";                      // true
    std::cout << (bool)i2 << "\n";                      // false
    std::cout << "\n";

    // Prove that when cast to a `bool` type, ONLY integer `0` (zero) is false,
    // and all other integer types are `true`! See full sample output below.
    std::cout << "(bool)i is:\n";
    for (int i = -10; i <= 10; i++)
    {
        printf("(bool)%-3i is ", i);
        std::cout << (bool)i << "\n";
    }
    std::cout << "\n";


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 integer_test_for_true.cpp -o bin/a && bin/a

    real    0m2.079s
    user    0m0.775s
    sys 0m0.087s
    Hello world!

*/
