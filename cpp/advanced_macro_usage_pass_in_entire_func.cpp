/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

GS 
19 Mar. 2020 
- Let's practice some more advanced usages of macros where I pass in entire function calls as parameters, like this!

    MY_MACRO(my_int1, my_int2, mynamespace1::mynamespace2::my_func(my_int1, my_int2));

Build and run:
- `-std=` options: https://gcc.gnu.org/projects/cxx-status.html
- `c++98`, `c++11`, `c++14`, `c++17`, `c++2a`

    mkdir -p bin_adv_macro && g++ -Wall -Werror -g3 -std=c++17 -save-temps=obj \
    advanced_macro_usage_pass_in_entire_func.cpp \
    -o ./bin_adv_macro/advanced_macro_usage_pass_in_entire_func \
    && ./bin_adv_macro/advanced_macro_usage_pass_in_entire_func

*******************************************************************************/

#include <stdio.h>

#define MY_MACRO(int1, int2, func_call_or_code_block) \
    do                                \
    {                                 \
        (int1) += 7;                  \
        (int2) += 5;                  \
        (func_call_or_code_block);    \
    } while (0)
    

namespace ns1 
{
    namespace ns2 
    {
        int my_func(int i1, int i2)
        {
            return i1 + i2;
        }
    } // namespace ns2 
    
} // namespace ns1 

int main()
{
    printf("Hello World\n");

    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    
    // WORKS!
    printf("i1 = %i; i2 = %i; i3 = %i\n", i1, i2, i3);
    MY_MACRO(i1, 
             i2, 
             // Pass in a *single function* here; works!
             i3 = ns1::ns2::my_func(i1, i2)
    );
    printf("i1 = %i; i2 = %i; i3 = %i\n", i1, i2, i3);
    
    // ALSO WORKS!
    int i4 = i1 + 1;
    int i5 = i2 + 1;
    int i6 = i3 + 1;
    printf("\n");
    printf("i1 = %i; i2 = %i; i3 = %i\n", i1, i2, i3);
    printf("i4 = %i; i5 = %i; i6 = %i\n", i4, i5, i6);
    MY_MACRO(i1, 
             i2, 
             {
                 // Pass in an *entire code block* here! Also works!
                 // - this is REALLY cool! You can pass in ANYTHING to the macro via this textual code block!
                 
                 printf("hey, I'm a code block being passed into the macro!\n");
                 i3 = ns1::ns2::my_func(i1, i2);
                 i6 = ns1::ns2::my_func(i4, i5);
             }
    );
    printf("i1 = %i; i2 = %i; i3 = %i\n", i1, i2, i3);
    printf("i4 = %i; i5 = %i; i6 = %i\n", i4, i5, i6);
    

    return 0;
}

/*

Output:
- works in at least C++17 and also just "C++"

    Hello World
    i1 = 0; i2 = 0; i3 = 0
    i1 = 7; i2 = 5; i3 = 12

    i1 = 7; i2 = 5; i3 = 12
    i4 = 8; i5 = 6; i6 = 13
    hey, I'm a code block being passed into the macro!
    i1 = 14; i2 = 10; i3 = 24
    i4 = 8; i5 = 6; i6 = 14


Here's what the pre-processed .ii file `main()` func looks like, showing the code
*after* macro substitution has already taken place!
- See: "cpp/bin_adv_macro/advanced_macro_usage_pass_in_entire_func.ii"

    int main()
    {
        printf("Hello World\n");

        int i1 = 0;
        int i2 = 0;
        int i3 = 0;


        printf("i1 = %i; i2 = %i; i3 = %i\n", i1, i2, i3);
        do { (i1) += 7; (i2) += 5; (i3 = ns1::ns2::my_func(i1, i2)); } while (0)



         ;
        printf("i1 = %i; i2 = %i; i3 = %i\n", i1, i2, i3);


        int i4 = i1 + 1;
        int i5 = i2 + 1;
        int i6 = i3 + 1;
        printf("\n");
        printf("i1 = %i; i2 = %i; i3 = %i\n", i1, i2, i3);
        printf("i4 = %i; i5 = %i; i6 = %i\n", i4, i5, i6);
        do { (i1) += 7; (i2) += 5; ({ printf("hey, I'm a code block being passed into the macro!\n"); i3 = ns1::ns2::my_func(i1, i2); i6 = ns1::ns2::my_func(i4, i5); }); } while (0)
    # 82 "advanced_macro_usage_pass_in_entire_func.cpp"
         ;
        printf("i1 = %i; i2 = %i; i3 = %i\n", i1, i2, i3);
        printf("i4 = %i; i5 = %i; i6 = %i\n", i4, i5, i6);


        return 0;
    }


*/