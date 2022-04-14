/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
24 Feb. 2022

Investigate some tools and tricks I'll need for
eRCaGuy_hash_table library I'm working on.

STATUS: wip; it runs as-is though

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 string_literals_test_for_eRCaGuy_hash_table.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 string_literals_test_for_eRCaGuy_hash_table.c -o bin/a && bin/a
```

References:
1.

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <string.h>  // `strlen()`

void foo(const char* str, size_t len, const char** str_p)
{
    printf("str = %s\n"
           "len = %zu\n", str, len);

    (void)str_p;
}

typedef struct my_struct_s
{
    int i1;
    int i2;
} my_struct_t;

void print_struct(my_struct_t my_struct)
{
    printf("i1 = %i; i2 = %i\n", my_struct.i1, my_struct.i2);
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    size_t size = sizeof("test");
    printf("size = %zu\n\n", size);

    char* p = NULL;

    foo(p = "test", sizeof("test"), NULL);//&"test");
    printf("p = %s\n", p);
    printf("\n");

    foo(p = "supdude", sizeof("supdude"), NULL);//&"test");
    printf("p = %s\n", p);
    printf("\n");

    // foo(char str2[] = "supdude", sizeof("supdude"), NULL);//&"test");
    // printf("p = %s\n", p);
    // printf("\n");

    // // undefined operation on p
    // foo(p = "yellow", strlen(p), NULL);
    // printf("p = %s\n", p);
    // printf("\n");

    p = "yellow";
    foo(p, strlen(p), NULL); // NB: strlen() does NOT count the null terminator at end, but sizeof() **does**!
    printf("p = %s\n", p);
    printf("\n");

    // print_struct({.i1 = 2, .i2 = 3});
    print_struct((my_struct_t){2, 3}); // works!

    // also works, of course, but the one above is what is really impressive!
    my_struct_t my_struct =
    {
        11,
        22,
    };
    print_struct(my_struct);
    printf("\n");


#define FOO(str) foo((str), sizeof(str), NULL);

    // WORKS!
    FOO("orange");
    printf("\n");

#define STR_TO_ARGS(str) (str), sizeof(str), NULL

    // WORKS!
    foo(STR_TO_ARGS("blue"));
    printf("\n");


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 string_literals_test_for_eRCaGuy_hash_table.c -o bin/a && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 string_literals_test_for_eRCaGuy_hash_table.c -o bin/a && bin/a
    Hello World.


*/
