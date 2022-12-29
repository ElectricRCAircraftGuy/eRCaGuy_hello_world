/*
GS
26 Jan. 2022

Investigate this weird behavior/compiler bug present in GCC 8.4 but fixed by GCC 9.1. See my Q here:
https://stackoverflow.com/q/70873232/4561887, and the answer there.

Compile and run:
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_with_square_brackets_gcc_bug_investigation.cpp -o bin/a && bin/a
```
*/

#include <iostream>
#include <vector>

std::vector<int> v =
{
    1,
    2,
    3,
    [7] = 12, // Why does this "work" here? What is happening?
    [10] = 15,
    4,
};

int main()
{
    for (int i : v)
    {
        std::cout << i << "\n";
    }
    printf("\n");

    return 0;
}

/*
Sample output with gcc 8.4:

    $ gcc --version
    gcc (Ubuntu 8.4.0-1ubuntu1~18.04) 8.4.0
    Copyright (C) 2018 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 vector_with_square_brackets_gcc_bug_investigation.cpp -o bin/a && bin/a
    1
    2
    3
    12
    15
    4


*/
