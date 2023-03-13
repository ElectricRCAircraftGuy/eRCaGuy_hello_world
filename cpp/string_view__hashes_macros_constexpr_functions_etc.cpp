///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
12 Mar. 2023

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
See my long answer here: Use a char[4] or char[8] as a constant int?:
*****+ https://stackoverflow.com/a/75714049/4561887
1. Solution 1/4: use a macro to hack together a `uint32_t` by manually calculating it from 4 bytes
2. Solution 2/4 (better): use a constant expression function hack instead of the macro hack above
3. Solution 3/4: (best so far) `constexpr` function hack using a `std::string_view` as input, instead of the `std::array` just above
4. Solution 4/4: don't convert 4 bytes to integers; just hash the string directly, as a string view, using built-in C++ hash functions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


STATUS: eh; good enough. It runs. :) See my answer above for the full picture


To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 hello_world_extra_basic.cpp -o bin/a && bin/a
```

References:
1.

*/

// // C++ includes
// #include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// // C includes
// #include <cstdint>  // For `uint8_t`, `int8_t`, etc.
// #include <cstdio>   // For `printf()`

// #define CONST_INT32(bytes) (*((const int32_t*)(bytes)))

// #define HASH4(x) (*((const int*)x))
// #define HASH8(x) (*((const long long*)x))

// // int main(int argc, char *argv[])  // alternative prototype
// int main()
// {
//     printf("Hello ");
//     std::cout << "world!\n\n";

//     const int something = HASH4("FOOD");

//     switch(something)
//     {
//     case HASH4("FOOD"):
//         printf("FOOD!");
//         break;
//     case HASH8("SEXYCOOL"):
//         printf("SEXYCOOL!");
//         break;
//     }

//     return 0;
// }


// #include <iostream>

// #define HASH4(s) ((((s)[0]*256+(s)[1])*256+(s)[2])*256+(s)[3])

// void check_int(int i)
// {
//     switch(i)
//     {
//     case HASH4("FOOD"):
//         printf("FOOD\n");
//         break;
//     case HASH4("TREE"):
//         printf("TREE\n");
//         break;
//     }
// }

// int main()
// {
//     std::cout << "Test\n";

//     int something = HASH4("FOOD");
//     printf("something = %i\n", something); // something = 1179602756
//     check_int(something);

//     something = 1179602756;
//     check_int(something);


//     // withOUT using a #define now

//     something = ((('F'*256+'O')*256+'O')*256+'D');

//     switch(something)
//     {
//         case ((('F'*256+'O')*256+'O')*256+'D'):
//             printf("FOOD\n");
//             break;
//     }


//     return 0;
// }


// ///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// // For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

// #include <array>
// #include <iostream>

// constexpr uint32_t hash4chars(const std::array<char, 4>& chars)
// {
//     // For big-endian byte ordering
//     // uint32_t num = ((chars[0]*256 + chars[1])*256 + chars[2])*256 + chars[3];

//     // Update: reverse the order for correct endianness:
//     // For little-endian byte ordering
//     uint32_t num = ((chars[3]*256 + chars[2])*256 + chars[1])*256 + chars[0];
//     return num;
// }

// void check_int(int i)
// {
//     switch(i)
//     {
//     case hash4chars({'F', 'O', 'O', 'D'}):
//         printf("FOOD\n");
//         break;
//     case hash4chars({'T', 'R', 'E', 'E'}):
//         printf("TREE\n");
//         break;
//     }
// }

// int main()
// {
//     std::cout << "Test\n";

//     uint32_t num = hash4chars({'F', 'O', 'O', 'D'});
//     printf("num = %u\n", num);

//     // convert the num back to a char array to check that it was converted
//     // correctly
//     const char* str = (const char*)(&num);
//     printf("%c%c%c%c\n", str[0], str[1], str[2], str[3]);

//     return 0;
// }




// #include <array>


// ///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// // For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

// #include <cstdint>
// #include <iostream>
// #include <string_view>

// constexpr uint32_t hash4chars(const std::string_view& sv)
// {
//     // Error checking: ensure all inputs have only 4 chars.
//     // Note: as really crude error checking, we'll just return the sentinel
//     // value of `UINT32_MAX` if this error occurs. Better techniques exist
//     if (sv.size() != 4)
//     {
//         printf("Error: the string view should be 4 chars long!\n");
//         return UINT32_MAX;
//     }

//     // static_assert(sv.size() == 4); // doesn't work

//     // For big-endian byte ordering
//     // uint32_t num = ((sv[0]*256 + sv[1])*256 + sv[2])*256 + sv[3];

//     // Update: reverse the order for correct endianness:
//     // For little-endian byte ordering
//     uint32_t num = ((sv[3]*256 + sv[2])*256 + sv[1])*256 + sv[0];
//     return num;
// }

// void check_int(int i)
// {
//     switch(i)
//     {
//     case hash4chars("FOOD"):
//         printf("FOOD\n");
//         break;
//     case hash4chars("TREE"):
//         printf("TREE\n");
//         break;
//     }
// }

// int main()
// {
//     std::cout << "Test\n";

//     uint32_t num = hash4chars("FOOD");
//     printf("num = %u\n", num);

//     // convert the num back to a char array to check that it was converted
//     // correctly
//     const char* str = (const char*)(&num);
//     printf("%c%c%c%c\n", str[0], str[1], str[2], str[3]);

//     return 0;
// }



#include <iostream>
#include <string_view>

void check_hash(std::size_t hash)
{
    if (hash == std::hash<std::string_view>{}(std::string_view{"FOOD", 4}))
    {
        printf("FOOD\n");
    }
    else if (hash == std::hash<std::string_view>{}(std::string_view{"TREE", 4}))
    {
        printf("TREE\n");
    }
}

int main()
{
    std::cout << "Test\n";

    std::size_t num
        = std::hash<std::string_view>{}(std::string_view{"FOOD", 4});
    printf("num = %lu\n", num);
    check_hash(num);

    return 0;
}


/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a

    real    0m2.079s
    user    0m0.775s
    sys 0m0.087s
    Hello world!


You can also run this file as an executable directly!:

    eRCaGuy_hello_world/cpp$ ./hello_world_extra_basic.cpp
    Hello world!


*/

