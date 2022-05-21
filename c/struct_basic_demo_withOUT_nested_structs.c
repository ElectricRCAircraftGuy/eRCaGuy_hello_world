/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
21 May 2022

Demonstrate the usefulness of structures within structures. This file is with
only 1 layer of structures, and no structures within structures.

STATUS: Done!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 struct_basic_demo_withOUT_nested_structs.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 struct_basic_demo_withOUT_nested_structs.c -o bin/a && bin/a
```

References:
1. The question: https://stackoverflow.com/q/72330971/4561887

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <string.h>  // `strncpy()`


/// A function-like macro to write string `string` into destination char array
/// `destination`.
#define SET_STRING(destination, string) \
    strncpy((destination), (string), sizeof(destination))


typedef struct addresses_s
{
    char home_street[40];
    char home_city[30];
    char home_zipcode[10];
    char home_state[30];
    char home_country[30];

    char work_street[40];
    char work_city[30];
    char work_zipcode[10];
    char work_state[30];
    char work_country[30];

    char other_street[40];
    char other_city[30];
    char other_zipcode[10];
    char other_state[30];
    char other_country[30];
} addresses_t;

void print_addresses(addresses_t addresses)
{
    printf(
        "home_street:   %s\n"
        "home_city:     %s\n"
        "home_zipcode:  %s\n"
        "home_state:    %s\n"
        "home_country:  %s\n"
        "\n"
        "work_street:   %s\n"
        "work_city:     %s\n"
        "work_zipcode:  %s\n"
        "work_state:    %s\n"
        "work_country:  %s\n"
        "\n"
        "other_street:  %s\n"
        "other_city:    %s\n"
        "other_zipcode: %s\n"
        "other_state:   %s\n"
        "other_country: %s\n"
        "\n",

        addresses.home_street,
        addresses.home_city,
        addresses.home_zipcode,
        addresses.home_state,
        addresses.home_country,

        addresses.work_street,
        addresses.work_city,
        addresses.work_zipcode,
        addresses.work_state,
        addresses.work_country,

        addresses.other_street,
        addresses.other_city,
        addresses.other_zipcode,
        addresses.other_state,
        addresses.other_country);
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("struct basic demo withOUT nested structs.\n\n");

    addresses_t addresses;

    SET_STRING(addresses.home_street,   "street 1");
    SET_STRING(addresses.home_city,     "city 1");
    SET_STRING(addresses.home_zipcode,  "12345");
    SET_STRING(addresses.home_state,    "Florida");
    SET_STRING(addresses.home_country,  "USA");

    SET_STRING(addresses.work_street,   "street 2");
    SET_STRING(addresses.work_city,     "city 2");
    SET_STRING(addresses.work_zipcode,  "67890");
    SET_STRING(addresses.work_state,    "Florida");
    SET_STRING(addresses.work_country,  "USA");

    SET_STRING(addresses.other_street,  "street 3");
    SET_STRING(addresses.other_city,    "city 3");
    SET_STRING(addresses.other_zipcode, "54321");
    SET_STRING(addresses.other_state,   "Florida");
    SET_STRING(addresses.other_country, "USA");

    print_addresses(addresses);

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 struct_basic_demo_withOUT_nested_structs.c -o bin/a -lm && bin/a
    struct basic demo withOUT nested structs.

    home_street:   street 1
    home_city:     city 1
    home_zipcode:  12345
    home_state:    Florida
    home_country:  USA

    work_street:   street 2
    work_city:     city 2
    work_zipcode:  67890
    work_state:    Florida
    work_country:  USA

    other_street:  street 3
    other_city:    city 3
    other_zipcode: 54321
    other_state:   Florida
    other_country: USA



OR, in C++:

(Same as in C)


*/
