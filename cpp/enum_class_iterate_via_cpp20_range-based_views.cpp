///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++23 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sep. 2024

Iterate over a C++ enum class via C++20 "views", which are lightweight,
non-owning views of a sequence of elements that can be used in range-based
iteration.

This code is for my answer here: https://stackoverflow.com/a/69762682/4561887

STATUS: Done & works! It compiles and runs in ALL versions of C++, but only
C++11 or later actually has `enum class`es (scoped enums)!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=gnu++23 enum_class_iterate_via_cpp20_range-based_views.cpp -o bin/a && bin/a
time g++ -Wall -Wextra -Werror -O3 -std=gnu++20 enum_class_iterate_via_cpp20_range-based_views.cpp -o bin/a && bin/a
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 enum_class_iterate_via_cpp20_range-based_views.cpp -o bin/a && bin/a
time g++ -Wall -Wextra -Werror -O3 -std=gnu++14 enum_class_iterate_via_cpp20_range-based_views.cpp -o bin/a && bin/a
time g++ -Wall -Wextra -Werror -O3 -std=gnu++11 enum_class_iterate_via_cpp20_range-based_views.cpp -o bin/a && bin/a
time g++ -Wall -Wextra -Werror -O3 -std=gnu++03 enum_class_iterate_via_cpp20_range-based_views.cpp -o bin/a && bin/a
time g++ -Wall -Wextra -Werror -O3 -std=gnu++98 enum_class_iterate_via_cpp20_range-based_views.cpp -o bin/a && bin/a

# OR (just call this file as an exectuable directly)
time ./enum_class_iterate_via_cpp20_range-based_views.cpp
```

References:
1. *****+ This really helpful answer by 康桓瑋 (Kang Huanwei) here:
   https://stackoverflow.com/a/69762782/4561887
1. ***** [WHERE I PRESENT THIS CODE] My answer here: 
   https://stackoverflow.com/a/69762682/4561887
1. C++20 views and ranges: https://en.cppreference.com/w/cpp/ranges
    1. https://en.cppreference.com/w/cpp/ranges/iota_view
1. Algorithm: https://en.cppreference.com/w/cpp/algorithm/transform
1. Utility: https://en.cppreference.com/w/cpp/utility/to_underlying
1. https://en.cppreference.com/w/cpp/language/decltype
1. Abbreviated Function Templates and Constrained Auto - 
   https://devblogs.microsoft.com/cppblog/abbreviated-function-templates-and-constrained-auto/

1. GitHub Copilot: 

    Prompt: 
    
    > In `std::views::iota`, what does iota stand for?

    Answer: 
    
    > In std::views::iota, the term "iota" is derived from the Greek letter "ι"
    (iota), which is often used in mathematics and computer science to represent
    a small increment or a sequence of consecutive values. In the context of
    C++20 ranges, std::views::iota generates an infinite sequence of values
    starting from a given initial value.

*/

// C++ (incl. C) includes
// #include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <ranges>
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

#if __cplusplus >= 201103L

// Option 1: adds no new values to the enum class, but rather, just adds 
// aliased names:
// - Note: everything works just fine for non-scoped `enum MyErrorType` too. 
enum class MyErrorType  
{
    SOMETHING_1 = 0,
    SOMETHING_2,
    SOMETHING_3,
    SOMETHING_4,
    SOMETHING_5,
    // Helpers for iterating over the enum:
    // - Note: adding these helpers adds no new enum values, since `begin`
    //   already has the same value as `SOMETHING_1`, and `end` already has the
    //   same value as `SOMETHING_5`. These are just aliased names is all. 
    begin = 0,
    end = SOMETHING_5,
};

// Option 2 [MY PREFERENCE]: also add a new `count` value to the enum class. 
//
// I prefer this style for two reasons: 
// 1. The `MyErrorType2::count` member is really useful to see how many valid
//    members are in your enum class.
// 2. The last portion of the enum class definition, starting with `count,` is
//    always the exact same for all enum classes, so you can easily copy-paste
//    this code and recognize it throughout your code base. In the example
//    above, the `= SOMETHING_5` part of `end = SOMETHING_5` must be manually 
//    updated for each enum class definition, which is a pain. 
enum class MyErrorType2 
{
    SOMETHING_1 = 0,
    SOMETHING_2,
    SOMETHING_3,
    SOMETHING_4,
    SOMETHING_5,
    
    // Helpers
    count,
    begin = 0,
    end = count - 1,
};

#endif

#if __cplusplus >= 202100L
// C++23 or later: using `std::to_underlying()`, a C++23 feature:

// Generate a C++20 "range" iterating from the enum value `first` to `last`,
// inclusive, to be used in modern C++ range-based for loops.
// - This is also using the C++20 feature of "abbreviated function templates",
//   or "template argument deduction for functions", where `auto` can be used
//   for all input parameter types and for the return type in place of making
//   this a function template. 
//   - Previous to C++20, this would have to be a function template or lambda
//     function. See here: 
//     https://devblogs.microsoft.com/cppblog/abbreviated-function-templates-and-constrained-auto/
//     >  C++14 allowed you to make lambdas which can be called with arguments
//     >  of any type by using the auto keyword...Now you can pass any types as
//     >  the arguments. C++20’s abbreviated function templates allows you to
//     >  apply this kind of syntax to function templates.
constexpr inline auto enum_range(auto first, auto last) 
{
    // Note that "ranges" exist only in C++20 or later
    auto enum_range = 
        // `std::views::iota` is a C++20 range generator that auto-generates a
        // sequence of values from (param1) to (param2 - 1).
        // - See: https://en.cppreference.com/w/cpp/ranges/iota_view
        // - The word "iota" refers to the Greek letter "iota" which apparently
        //   is often used in math and computer science to represent a small
        //   increment or a sequence of consecutive values.
        // - In range factories, `|` is apparently the "pipe" operator, which is
        //   used to chain together range operations.
        std::views::iota(
            std::to_underlying(first), 
            std::to_underlying(last) + 1
        ) 
        | std::views::transform([](auto enum_val) 
            { 
                return (decltype(first))enum_val; 
            }
        ); 

    return enum_range; 
};

#elif __cplusplus >= 202000L
// For C++20 range-based views:

// Generate a C++20 "range" iterating from the enum value `first` to `last`,
// inclusive, to be used in modern C++ range-based for loops.
// - This is also using the C++20 feature of "abbreviated function templates",
//   or "template argument deduction for functions", where `auto` can be used
//   for all input parameter types and for the return type in place of making
//   this a function template. 
//   - Previous to C++20, this would have to be a function template or lambda
//     function. See here: 
//     https://devblogs.microsoft.com/cppblog/abbreviated-function-templates-and-constrained-auto/
//     >  C++14 allowed you to make lambdas which can be called with arguments
//     >  of any type by using the auto keyword...Now you can pass any types as
//     >  the arguments. C++20’s abbreviated function templates allows you to
//     >  apply this kind of syntax to function templates.
constexpr inline auto enum_range(auto first, auto last) 
{
    // Note that "ranges" exist only in C++20 or later
    auto enum_range = 
        // `std::views::iota` is a C++20 range generator that auto-generates a
        // sequence of values from (param1) to (param2 - 1).
        // - See: https://en.cppreference.com/w/cpp/ranges/iota_view
        // - The word "iota" refers to the Greek letter "iota" which apparently
        //   is often used in math and computer science to represent a small
        //   increment or a sequence of consecutive values.
        // - In range factories, `|` is apparently the "pipe" operator, which is
        //   used to chain together range operations.
        std::views::iota(
            static_cast<std::underlying_type_t<decltype(first)>>(first), 
            static_cast<std::underlying_type_t<decltype(last)>>(last) + 1
        ) 
        | std::views::transform([](auto enum_val) 
            {
                return (decltype(first))enum_val; 
            }
        ); 

    return enum_range; 
};

#endif


int main()
{
    printf("__cplusplus = %ld\n", __cplusplus);

    #if __cplusplus >= 202300L
        std::cout << "Compiled with C++23 or later.\n";
    #elif __cplusplus >= 202100L
        std::cout << "Compiled with a pre-release version of C++23.\n";
    #elif __cplusplus >= 202002L
        std::cout << "Compiled with C++20.\n";
    #elif __cplusplus >= 201703L
        std::cout << "Compiled with C++17.\n";
    #elif __cplusplus >= 201402L
        std::cout << "Compiled with C++14.\n";
    #elif __cplusplus >= 201103L
        std::cout << "Compiled with C++11.\n";
    #elif __cplusplus >= 199711L
        std::cout << "Compiled with C++98 or C++03.\n";
    #else
        std::cout << "Compiled with an unknown version of C++.\n";
    #endif

    printf("\nC++ enum class iteration demo.\n\n");

    // ---------------------------------------------------------
    // Iterate over the enum classes
    // ---------------------------------------------------------

#if __cplusplus >= 202000L
    // Option 0: C++20 range-based views

    for (const MyErrorType e : enum_range(MyErrorType::begin, MyErrorType::end))
    {
        switch (e)
        {
            case MyErrorType::SOMETHING_1:
                printf("MyErrorType::SOMETHING_1\n");
                break;
            case MyErrorType::SOMETHING_2:
                printf("MyErrorType::SOMETHING_2\n");
                break;
            case MyErrorType::SOMETHING_3:
                printf("MyErrorType::SOMETHING_3\n");
                break;
            case MyErrorType::SOMETHING_4:
                printf("MyErrorType::SOMETHING_4\n");
                break;
            case MyErrorType::SOMETHING_5:
                printf("MyErrorType::SOMETHING_5\n");
                break;
        }
    }

    printf("\n");

    for (const MyErrorType2 e : 
        enum_range(MyErrorType2::begin, MyErrorType2::end))
    {
        switch (e)
        {
            case MyErrorType2::SOMETHING_1:
                printf("MyErrorType2::SOMETHING_1\n");
                break;
            case MyErrorType2::SOMETHING_2:
                printf("MyErrorType2::SOMETHING_2\n");
                break;
            case MyErrorType2::SOMETHING_3:
                printf("MyErrorType2::SOMETHING_3\n");
                break;
            case MyErrorType2::SOMETHING_4:
                printf("MyErrorType2::SOMETHING_4\n");
                break;
            case MyErrorType2::SOMETHING_5:
                printf("MyErrorType2::SOMETHING_5\n");
                break;
            case MyErrorType2::count:
                // Nothing to do
                break;
        }
    }

    printf("\n");
#endif

#if __cplusplus >= 201103L
    // Option 1
    for (MyErrorType myErrorType = MyErrorType::begin;
        myErrorType <= MyErrorType::end;
        myErrorType = static_cast<MyErrorType>(
            static_cast<size_t>(myErrorType) + 1))
    {
        switch (myErrorType)
        {
            case MyErrorType::SOMETHING_1:
                printf("MyErrorType::SOMETHING_1\n");
                break;
            case MyErrorType::SOMETHING_2:
                printf("MyErrorType::SOMETHING_2\n");
                break;
            case MyErrorType::SOMETHING_3:
                printf("MyErrorType::SOMETHING_3\n");
                break;
            case MyErrorType::SOMETHING_4:
                printf("MyErrorType::SOMETHING_4\n");
                break;
            case MyErrorType::SOMETHING_5:
                printf("MyErrorType::SOMETHING_5\n");
                break;
        }
    }

    printf("\n");

    // Option 2: same as above, except we must also include the `count` value
    // as a switch case. 
    for (MyErrorType2 myErrorType2 = MyErrorType2::begin;
        myErrorType2 <= MyErrorType2::end;
        myErrorType2 = static_cast<MyErrorType2>(
            static_cast<size_t>(myErrorType2) + 1))
    {
        switch (myErrorType2)
        {
            case MyErrorType2::SOMETHING_1:
                printf("MyErrorType2::SOMETHING_1\n");
                break;
            case MyErrorType2::SOMETHING_2:
                printf("MyErrorType2::SOMETHING_2\n");
                break;
            case MyErrorType2::SOMETHING_3:
                printf("MyErrorType2::SOMETHING_3\n");
                break;
            case MyErrorType2::SOMETHING_4:
                printf("MyErrorType2::SOMETHING_4\n");
                break;
            case MyErrorType2::SOMETHING_5:
                printf("MyErrorType2::SOMETHING_5\n");
                break;
            case MyErrorType2::count:
                // Nothing to do
                break;
        }
    }
#endif
}



/*
SAMPLE OUTPUT:

eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=gnu++23 enum_class_iterate_via_cpp20_range-based_views.cpp -o bin/a && bin/a

real	0m0.405s
user	0m0.354s
sys	0m0.051s
__cplusplus = 202100
Compiled with a pre-release version of C++23.

C++ enum class iteration demo.

MyErrorType::SOMETHING_1
MyErrorType::SOMETHING_2
MyErrorType::SOMETHING_3
MyErrorType::SOMETHING_4
MyErrorType::SOMETHING_5

MyErrorType2::SOMETHING_1
MyErrorType2::SOMETHING_2
MyErrorType2::SOMETHING_3
MyErrorType2::SOMETHING_4
MyErrorType2::SOMETHING_5

MyErrorType::SOMETHING_1
MyErrorType::SOMETHING_2
MyErrorType::SOMETHING_3
MyErrorType::SOMETHING_4
MyErrorType::SOMETHING_5

MyErrorType2::SOMETHING_1
MyErrorType2::SOMETHING_2
MyErrorType2::SOMETHING_3
MyErrorType2::SOMETHING_4
MyErrorType2::SOMETHING_5

*/
