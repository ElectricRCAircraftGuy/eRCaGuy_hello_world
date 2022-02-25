/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
24 Feb. 2022

Practice passing structs in C to functions as parameters as both R-values and as L-values, passing
both **by value** and **by reference**.
Reminder:
    L values are data attached to a variable.
    R values are data NOT attached to a variable.

STATUS: complete and works great! I show a couple integer examples too.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 struct_pass_R_values_and_L_values_by_value_and_reference.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 struct_pass_R_values_and_L_values_by_value_and_reference.c -o bin/a && bin/a
```

References:
1. string_literals_test.c
1. https://en.cppreference.com/w/c/language/struct_initialization
    - Demonstrates "designator" initialization syntax (`.member1 = whatever`)
1. [my answer]
   [Use of 'const' for function parameters](https://stackoverflow.com/a/60823004/4561887)
1. SEE ALSO: eRCaGuy_hello_world/cpp/struct_pass_R_values_by_cpp_reference_and_ptr.c

*/

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`


/// data struct
typedef struct data_s
{
    // NB: if you remove `const` just below, the code will fail to compile as C++ with a bunch of
    // these errors:
    // `error: ISO C++ forbids converting a string constant to ‘char*’ [-Werror=write-strings]`
    // This is because we are doing things like `data1.name = "data1 struct L-value";` below, which
    // implies the "data1 struct L-value" R-value string literal **should be** `const` since it's
    // not explicitly tied to a modifiable L-value C-string array of `chars`.
    const char * name;
    uint16_t u1;
    uint16_t u2;
    uint16_t u3;
    float f1;
} data_t;

/// Print all members of a struct which is passed by value (full copy).
/// - NB: I recommend you do NOT use `const` when passing by value. See my answer here:
/// https://stackoverflow.com/a/60823004/4561887
/// - When passing by value, changing the input parameter inside the function does NOT
/// affect the external variable which was passed in, since it was passed by copy.
void print_struct_passed_by_value(data_t data)
{
    printf("number of bytes just passed by value (full copy) = `sizeof(data)` = %zu\n",
            sizeof(data));
    printf("name = %s\n"
           "u1   = %u\n"
           "u2   = %u\n"
           "u3   = %u\n"
           "f1   = %.6f\n\n",
           data.name,
           data.u1,
           data.u2,
           data.u3,
           data.f1);
}

/// Print all members of a struct which is passed by reference (ptr).
/// - NB: I recommend you DO use `const` whenever applicable on ptr parameters! See my answer here:
/// https://stackoverflow.com/a/60823004/4561887
/// - When passing by reference, changing the object the input parameter points to inside the
/// function DOES also affect the external variable which was passed in, since it was passed by
/// reference (ptr).
void print_struct_passed_by_reference(const data_t *data)
{
    printf("number of bytes just passed by reference (ptr) = `sizeof(data)` = %zu\n",
            sizeof(data));
    printf("name = %s\n"
           "u1   = %u\n"
           "u2   = %u\n"
           "u3   = %u\n"
           "f1   = %.6f\n\n",
           data->name,
           data->u1,
           data->u2,
           data->u3,
           data->f1);
}

/// Print an int passed by value
void print_int(int i)
{
    printf("int i pased by value = %i\n\n", i);
}

/// Print an int passed by reference. DON'T DO THIS! See the explanation above
/// `print_and_modify_int()` just below. A ptr to an int is generally MORE BYTES than just the
/// int itself!
void print_int_passed_by_reference(const int *i)
{
    printf("int i passed by reference = %i\n\n", *i);
}

/// Print an int passed by reference (ptr).
/// - NB: if using the passed-in parameter as an input only, DON'T PASS AN INTEGER BY REFERENCE! This
///   would be pointless since the integer type is generally smaller than the pointer type! The only
///   time you'd want to do this is if you're using the parameter as an input/output variable or an
///   output variable.
/// - Input/output variables contain some value coming in, and then modify the value in place via the
///   passed-in ptr, affecting the variable outside the function. Output variables pass out values
///   back to the user by modifying the variable outside the function, again, through the passed-in
///   ptr.
void print_and_modify_int(int *i)
{
    // First, handle the NULL ptr error case
    if (i == NULL)
    {
        return;
    }

    printf("int i passed by reference (will be modified next) = %i\n\n", *i);

    // now modify the external variable in-place
    *i = 1234;
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    // =============================================================================================
    // NOTES about passing parameters as L-values or R-values:
    //
    // Summary:
    //   L values are data attached to a variable.
    //   R values are data NOT attached to a variable.
    //
    // As L-values:
    // - In the statement `my_var = 7`, `my_var` is the L-value on the **left** receiving the
    //   assignment of the R-value on the right. It is called an "L-value" because it is on
    //   the **Left** in the assignment above. It is data attached to a variable. To "pass in an
    //   L-value", you pass the data into a function using the **variable name**, since the
    //   variable contains or points to the data.
    // - Example:
    //          some_func(my_var);   // pass in an L-value by value (copy)
    //          some_func(&my_var);  // pass in an L-value by reference (ptr)
    //
    // As R-values:
    // - In the statement `my_var = 7`, `7` is the R-value on the **right** being assigned to the
    //   L-value on the left. It is called an "R-value" because it is on the **Right** in the
    //   assignment above. It is the raw "literal" data accessed directly, NOT via any variable.
    //   To "pass in an R-value", you pass the data into a function **directly**, NOT using any
    //   variable name.
    // - Example:
    //          some_func(7);   // pass in an L-value by value (copy)
    //
    //          // By reference (ptr):
    //          // NOT ALLOWED for integers!: FAILS!: `error: lvalue required as unary ‘&’ operand`
    //          // some_func(&7);  // try to pass in an L-value by reference (ptr)
    //          //
    //          // OK for structs, since passing in R-value structs by reference still has the
    //          // benefit of passing in fewer bytes and therefore is faster and more-efficient
    //          // than passing in R-value structs by value (copy).
    //          some_func(&(struct my_struct_s){  // pass in an R-value struct by reference (ptr)
    //              .element1 = 7,
    //              .element2 = 8,
    //          });
    // =============================================================================================

    printf("===================================================================================\n"
           "passed by **value**\n"
           "===================================================================================\n");

    // use braces to create its own scope so I can re-use these variable names and redo the
    // declarations as a fresh example in the "passed by **reference**" section below.
    {
        printf("------------------------------\n"
               "As L-value\n"
               "------------------------------\n");

        // Example 0: L-value integer passed by value
        int i = 7;
        print_int(i);

        // Example 1: create a struct, then populate its members
        data_t data1;
        data1.name = "data1 struct L-value";
        data1.u1 = 7;
        data1.u2 = 8;
        data1.u3 = 9;
        data1.f1 = 10.123456789;
        print_struct_passed_by_value(data1);

        // Example 2: create a struct and populate its values all at once (populating it **as you create
        // it** allows you to also make the struct `const` if desired, as I do below)
        const data_t data2 = {
            "data2 struct L-value",
            11,
            12,
            13,
            14.987654321,
        };
        print_struct_passed_by_value(data2);

        // Example 3: create and populate at once, but use the ".designator" syntax to make it clear
        // what each member is.
        // See: https://en.cppreference.com/w/c/language/struct_initialization
        const data_t data3 = {
            .name = "data3 struct L-value",
            .u1 = 15,
            .u2 = 16,
            .u3 = 17,
            .f1 = 18.123454321,
        };
        print_struct_passed_by_value(data3);


        printf("------------------------------\n"
               "As R-value\n"
               "------------------------------\n");

        // Example 0: R-value integer passed by value
        print_int(7);

        // Example 1: standard construction
        print_struct_passed_by_value((data_t){
            "data4 struct R-value",
            100,
            101,
            102,
            103.987654321,
        });

        // Example 2: "dot designator" syntax
        print_struct_passed_by_value((data_t){
            .name = "data5 struct R-value",
            .u1 = 104,
            .u2 = 105,
            .u3 = 106,
            .f1 = 107.123456789,
        });
    }


    printf("===================================================================================\n"
           "passed by **C-style reference** (ie: ptr)\n"
           "===================================================================================\n");

    {
        printf("------------------------------\n"
               "As L-value\n"
               "------------------------------\n");

        // Example 0: L-value integer passed by reference
        int i = 7;
        print_and_modify_int(&i);
        print_int_passed_by_reference(&i); // print it again to show it has been modified now!

        // Example 1: create a struct, then populate its members
        data_t data1;
        data1.name = "data1 struct L-value";
        data1.u1 = 7;
        data1.u2 = 8;
        data1.u3 = 9;
        data1.f1 = 10.123456789;
        print_struct_passed_by_reference(&data1);

        // Example 2: create a struct and populate its values all at once (populating it **as you create
        // it** allows you to also make the struct `const` if desired, as I do below)
        const data_t data2 = {
            "data2 struct L-value",
            11,
            12,
            13,
            14.987654321,
        };
        print_struct_passed_by_reference(&data2);

        // Example 3: create and populate at once, but use the ".designator" syntax to make it clear
        // what each member is.
        // See: https://en.cppreference.com/w/c/language/struct_initialization
        const data_t data3 = {
            .name = "data3 struct L-value",
            .u1 = 15,
            .u2 = 16,
            .u3 = 17,
            .f1 = 18.123454321,
        };
        print_struct_passed_by_reference(&data3);


        printf("------------------------------\n"
               "As R-value\n"
               "------------------------------\n");

        // Example 0: R-value integer passed by reference
        // (this doesn't really make sense, and hence DOESN'T WORK!)
        // print_and_modify_int(&7);                //  FAILS!: `error: lvalue required as unary ‘&’ operand`
        // print_and_modify_int(&(int)7);           //  FAILS!: `error: lvalue required as unary ‘&’ operand`
        // print_int_passed_by_reference(&7);       //  FAILS!: `error: lvalue required as unary ‘&’ operand`
        // print_int_passed_by_reference(&(int)7);  //  FAILS!: `error: lvalue required as unary ‘&’ operand`

        // THE FOLLOWING 3 EXAMPLES ARE OK IN C BUT **NOT** IN C++! In C++ you'll see this error:
        // `error: taking address of temporary [-fpermissive]`
        // See also: Error: taking address of temporary [-fpermissive]:
        // https://stackoverflow.com/q/16481490/4561887
        // So, don't run this code if compiling as C++.
        //
        // ======== SEE NB BELOW! =======
        // NB: If passing by **C++ reference** (NOT ptr), the below code IS allowed. It's just not
        // allowed to be passed by C++ ptr is all! That's a subtle difference. Again, see the Stack
        // Overflow answer just above for details. So, something **very similar** to the below code
        // and efficiency IS possible in C++ as well, it's just different is all: you must use a
        // C++ "const reference" for the input struct parameter instead of a ptr.
        #ifdef __cplusplus
        printf("No valid R-value ptr examples for C++ (although passing R-values by C++\n"
               "const reference is fine; see: https://stackoverflow.com/a/16481660/4561887) due\n"
               "to `error: taking address of temporary [-fpermissive]`\n"
               "SEE FULL DEMO HERE: "
               "\"eRCaGuy_hello_world/cpp/struct_pass_R_values_by_cpp_reference_and_ptr.c\"\n"
               "and see MY ANSWER HERE: https://stackoverflow.com/a/71270918/4561887\n");
        #else // For C, run the following:

        // Example 1: standard construction
        print_struct_passed_by_reference(&(data_t){
            "data4 struct R-value",
            100,
            101,
            102,
            103.987654321,
        });

        // Example 2: "dot designator" syntax
        print_struct_passed_by_reference(&(data_t){
            .name = "data5 struct R-value",
            .u1 = 104,
            .u2 = 105,
            .u3 = 106,
            .f1 = 107.123456789,
        });

        // Example 3: exact same things as just above, except use the `struct data_s` name instead
        // of the `data_t` typedef, just to show how to do it withOUT the typedef as well!
        print_struct_passed_by_reference(&(struct data_s){
            .name = "data6 struct R-value",
            .u1 = 108,
            .u2 = 109,
            .u3 = 110,
            .f1 = 111.1,  // will print as 111.099998 due to floating point precision issues
        });

        #endif
    }


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 struct_pass_R_values_and_L_values_by_value_and_reference.c -o bin/a && bin/a
    Hello World.

    ===================================================================================
    passed by **value**
    ===================================================================================
    ------------------------------
    As L-value
    ------------------------------
    int i pased by value = 7

    number of bytes just passed by value (full copy) = `sizeof(data)` = 24
    name = data1 struct L-value
    u1   = 7
    u2   = 8
    u3   = 9
    f1   = 10.123457

    number of bytes just passed by value (full copy) = `sizeof(data)` = 24
    name = data2 struct L-value
    u1   = 11
    u2   = 12
    u3   = 13
    f1   = 14.987655

    number of bytes just passed by value (full copy) = `sizeof(data)` = 24
    name = data3 struct L-value
    u1   = 15
    u2   = 16
    u3   = 17
    f1   = 18.123455

    ------------------------------
    As R-value
    ------------------------------
    int i pased by value = 7

    number of bytes just passed by value (full copy) = `sizeof(data)` = 24
    name = data4 struct R-value
    u1   = 100
    u2   = 101
    u3   = 102
    f1   = 103.987656

    number of bytes just passed by value (full copy) = `sizeof(data)` = 24
    name = data5 struct R-value
    u1   = 104
    u2   = 105
    u3   = 106
    f1   = 107.123459

    ===================================================================================
    passed by **C-style reference** (ie: ptr)
    ===================================================================================
    ------------------------------
    As L-value
    ------------------------------
    int i passed by reference (will be modified next) = 7

    int i passed by reference = 1234

    number of bytes just passed by reference (ptr) = `sizeof(data)` = 8
    name = data1 struct L-value
    u1   = 7
    u2   = 8
    u3   = 9
    f1   = 10.123457

    number of bytes just passed by reference (ptr) = `sizeof(data)` = 8
    name = data2 struct L-value
    u1   = 11
    u2   = 12
    u3   = 13
    f1   = 14.987655

    number of bytes just passed by reference (ptr) = `sizeof(data)` = 8
    name = data3 struct L-value
    u1   = 15
    u2   = 16
    u3   = 17
    f1   = 18.123455

    ------------------------------
    As R-value
    ------------------------------
    number of bytes just passed by reference (ptr) = `sizeof(data)` = 8
    name = data4 struct R-value
    u1   = 100
    u2   = 101
    u3   = 102
    f1   = 103.987656

    number of bytes just passed by reference (ptr) = `sizeof(data)` = 8
    name = data5 struct R-value
    u1   = 104
    u2   = 105
    u3   = 106
    f1   = 107.123459

    number of bytes just passed by reference (ptr) = `sizeof(data)` = 8
    name = data6 struct R-value
    u1   = 108
    u2   = 109
    u3   = 110
    f1   = 111.099998



OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 struct_pass_R_values_and_L_values_by_value_and_reference.c -o bin/a && bin/a
    Hello World.

    ===================================================================================
    passed by **value**
    ===================================================================================
    ------------------------------
    As L-value
    ------------------------------
    int i pased by value = 7

    number of bytes just passed by value (full copy) = `sizeof(data)` = 24
    name = data1 struct L-value
    u1   = 7
    u2   = 8
    u3   = 9
    f1   = 10.123457

    number of bytes just passed by value (full copy) = `sizeof(data)` = 24
    name = data2 struct L-value
    u1   = 11
    u2   = 12
    u3   = 13
    f1   = 14.987655

    number of bytes just passed by value (full copy) = `sizeof(data)` = 24
    name = data3 struct L-value
    u1   = 15
    u2   = 16
    u3   = 17
    f1   = 18.123455

    ------------------------------
    As R-value
    ------------------------------
    int i pased by value = 7

    number of bytes just passed by value (full copy) = `sizeof(data)` = 24
    name = data4 struct R-value
    u1   = 100
    u2   = 101
    u3   = 102
    f1   = 103.987656

    number of bytes just passed by value (full copy) = `sizeof(data)` = 24
    name = data5 struct R-value
    u1   = 104
    u2   = 105
    u3   = 106
    f1   = 107.123459

    ===================================================================================
    passed by **C-style reference** (ie: ptr)
    ===================================================================================
    ------------------------------
    As L-value
    ------------------------------
    int i passed by reference (will be modified next) = 7

    int i passed by reference = 1234

    number of bytes just passed by reference (ptr) = `sizeof(data)` = 8
    name = data1 struct L-value
    u1   = 7
    u2   = 8
    u3   = 9
    f1   = 10.123457

    number of bytes just passed by reference (ptr) = `sizeof(data)` = 8
    name = data2 struct L-value
    u1   = 11
    u2   = 12
    u3   = 13
    f1   = 14.987655

    number of bytes just passed by reference (ptr) = `sizeof(data)` = 8
    name = data3 struct L-value
    u1   = 15
    u2   = 16
    u3   = 17
    f1   = 18.123455

    ------------------------------
    As R-value
    ------------------------------
    No valid R-value ptr examples for C++ (although passing R-values by C++
    const reference is fine; see: https://stackoverflow.com/a/16481660/4561887) due
    to `error: taking address of temporary [-fpermissive]`
    SEE FULL DEMO HERE: "eRCaGuy_hello_world/cpp/struct_pass_R_values_by_cpp_reference_and_ptr.c"
    and see MY ANSWER HERE: https://stackoverflow.com/a/71270918/4561887


*/
