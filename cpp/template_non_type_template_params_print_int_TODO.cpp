/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
28 Sept. 2022

Practice using "non-type" template parameters.

Ex:

start with

```
template <int I>
printInt();
```

and see how that differs from

```
printInt(int i);
```

If you template `int I` and call it with 1000 versions of `I` you'll actually get 1000 different
functions at compile-time, I think. Prove it.

```
for (size_t i = 0; i < 1000; i++)
{
    printInt<i>(); // causes 1000 different versions of this func to be generated at compile-time
}
```

See references below as a start to my research on this.


(description)
STATUS: (status)

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a
```

References:
1. Google search for "template <int>" -
https://www.google.com/search?q=template+%3Cint%3E&oq=template+%3Cint%3E&aqs=chrome..69i57j69i65l3.2371j0j7&sourceid=chrome&ie=UTF-8
1. https://stackoverflow.com/questions/499106/what-does-template-unsigned-int-n-mean
1. Google search for "c++ template specialization" -
https://www.google.com/search?q=c%2B%2B+template+specialization&oq=c%2B%2B+template+specialization&aqs=chrome..69i57j69i65l2.8116j0j7&sourceid=chrome&ie=UTF-8
    1. https://www.geeksforgeeks.org/template-specialization-c/
    1. https://en.cppreference.com/w/cpp/language/template_specialization
1. Google search for "non type template parameters" -
https://www.google.com/search?q=non+type+template+parameters&oq=non+type+template+parameters&aqs=chrome..69i57.3319j0j7&sourceid=chrome&ie=UTF-8
    1. What does template <unsigned int N> mean? - https://stackoverflow.com/q/499106/4561887
    1. ***** [need to study and read more] https://stackoverflow.com/questions/5687540/non-type-template-parameters/5687553#5687553



*/

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a

    real    0m2.079s
    user    0m0.775s
    sys 0m0.087s
    Hello world!

*/
