/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Apr. 2022

Compare the results (compile time and binary executable size) of compiling with vs withOUT the gcc
"include all headers" header file `<bits/stdc++.h>.

STATUS: done!
See my results and answer here: https://stackoverflow.com/a/71863759/4561887

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++

# compile, timing how long it takes
time g++ -Wall -Wextra -Werror -O3 -std=c++17 include_bits_stdc++.cpp -o bin/a

# check binary executable size
size bin/a

# run
bin/a
```

References:
1. SEE THIS CODE IN MY ANSWER HERE: https://stackoverflow.com/a/71863759/4561887
1. https://stackoverflow.com/questions/31816095/why-should-i-not-include-bits-stdc-h
1. https://www.geeksforgeeks.org/bitsstdc-h-c/
    - this article plagiarizes from Stack Overflow, though; see my comment here:
      https://stackoverflow.com/questions/25311011/how-does-include-bits-stdc-h-work-in-c/33764128#comment126990806_33764128

*/

// Comment this out to see how long it takes to compile with vs withOUT this include being used!
#include <bits/stdc++.h>

#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    return 0;
}



/*
SAMPLE OUTPUT:

COMPILING:

WITH `#include <bits/stdc++.h>`:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 include_bits_stdc++.cpp -o bin/a

    real    0m1.928s
    user    0m1.586s
    sys 0m0.120s


WithOUT `#include <bits/stdc++.h>`:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 include_bits_stdc++.cpp -o bin/a

    real    0m0.297s
    user    0m0.271s
    sys 0m0.026s


RUNNING:

    eRCaGuy_hello_world/cpp$ bin/a
    Hello world!



*/
