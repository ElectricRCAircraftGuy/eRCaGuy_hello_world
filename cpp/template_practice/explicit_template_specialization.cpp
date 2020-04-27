/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
25 Apr. 2020

Let's play with some explicit template specialization to learn about it.

References:
1. *****https://en.wikipedia.org/wiki/Template_(C%2B%2B)#Template_specialization
1. *****+https://en.cppreference.com/w/cpp/language/template_specialization
1. https://en.cppreference.com/w/cpp/language/partial_specialization

To compile and run:
    ./run_explicit_template_specialization.sh
  OR:
    g++ -Wall -Werror -g3 -std=c++17 -o explicit_template_specialization \
    explicit_template_specialization.cpp && ./explicit_template_specialization

See the following files for additional general info. on building and running:
1. eRCaGuy_hello_world/cpp/hello_world.cpp
2. eRCaGuy_hello_world/cpp/run_hello_world.sh

*/

// C includes
#include <stdio.h>

// C++ includes
#include <iostream>

// 1. A normal function template based on type, with numer & denom passed in as 
// **function parameter inputs** **of a given template type, T**
template <typename T>
T divide1(T numer, T denom)
{
    // Does NOT work, because `denom` cannot be evaluated at compile time since it is an input
    // parameter **to the function** NOT a static/compile-time **template parameter**!
    //      explicit_template_specialization.cpp:38:5: error: non-constant condition for static assertion
    //      explicit_template_specialization.cpp:38:5: error: ‘denom’ is not a constant expression
    // static_assert(denom != 0, "dividing by zero not allowed");

    // WORKS--run-time check!
    if (denom == 0)
    {
        printf("divide1: cannot divide by zero\n");
        return -1;
    }

    return numer/denom;
}

// Template specialization; see: https://en.wikipedia.org/wiki/Template_(C%2B%2B)#Explicit_template_specialization
// Specialized for whenever type T is **double**!
template <>
// double divide1(double numer, double denom)       // WORKS!
// Can also be written more explicitly by adding in the explicit template type, `<double>`, like this instead!
double divide1<double>(double numer, double denom)  // WORKS!
{
    printf("divide1 template specialization #1: double type: just returning -0.1419\n");
    return -0.1419;
}

// Template specialization #2; see: https://en.cppreference.com/w/cpp/language/partial_specialization
// and *****https://en.cppreference.com/w/cpp/language/template_specialization
// I learned from the link above that a template specialization can have ANY template parameters!
// What has to match is simply the function **name** (`divide1` in this case)!
template<int numer, int denom>
int divide1()
{
    printf("divide1 template specialization #2\n");
    return numer/denom;
}

// Template specialization #3
template<int numer>
int divide1(int denom)
{
    printf("divide1 template specialization #3\n");
    return numer/denom;
}

// Template specialization #3 AGAIN, this time FUNCTION OVERLOADED on parameters
template<int anything>
int divide1(int numer, int denom)
{
    printf("divide1 template specialization #3 AGAIN (function overloaded)\n");
    return numer/denom;
}

// Template specialization #4
template<typename T = int, T numer = 18, T denom = 3>
T divide1()
{
    printf("divide1 template specialization #4\n");
    return numer/denom;
}

// Template specialization #5 (based on "#3 AGAIN")
template<>
int divide1<7>(int numer, int denom)
{
    printf("divide1 template specialization #5 (based on \"#3 AGAIN\"); your template parameter is 7!\n");
    return numer/denom;
}

// // Template specialization #6 (based on #4); DOESN'T WORK!
// //      explicit_template_specialization.cpp:110:25: error: non-class, non-variable partial 
// //      specialization ‘divide1<T, numer, 17>’ is not allowed
// template<typename T = int, T numer = 18, T denom = 3>
// T divide1<T, numer, 17>()
// {
//     printf("divide1 template specialization #6 (based on #4, but denom is 17!)\n");
//     return numer/denom;
// }

// // PARTIAL template specialization #1
// // See: https://en.cppreference.com/w/cpp/language/partial_specialization
// // OOPS! I WAS WRONG! I think partial template specialization ONLY works for class templates, and
// // does NOT work for function templates!
// template<typename T>
// T divide1<int, 17, 18>()
// {
//     printf("divide1 PARTIAL template specialization #1\n");
//     return 2983.7; // 2983
// }


// 2. A function template based on static/compile-time **template input**, with numer & denom
// passed in as **template parameter inputs**
template <int numer, int denom>
int divide2()
{
    // WORKS--compile-time check!
    // This works because numer and denom are both **template parameters**, so they get inserted
    // into their own versions of this function **at compile time**!
    // static_assert(denom != 0, "dividing by zero not allowed");
    
    // WORKS--run-time check!
    if (denom == 0)
    {
        printf("divide2: cannot divide by zero\n");
        return -1;
    }

    return numer/denom;
}

// 3. A function template based on static/compile-time **template inputs**, with numer & denom
// passed in as **template parameter inputs**, and having their types specified by the **first
// template parameter type, T**
template <typename T, T numer, T denom>
T divide3()
{
    // WORKS--compile-time check!
    // This works because numer and denom are both **template parameters**, so they get inserted
    // into their own versions of this function **at compile time**!
    // static_assert(denom != 0, "dividing by zero not allowed");
    
    // WORKS--run-time check!
    if (denom == 0)
    {
        printf("divide3: cannot divide by zero\n");
        return -1;
    }

    return numer/denom;
}

// // Template specialization; see: https://en.wikipedia.org/wiki/Template_(C%2B%2B)#Explicit_template_specialization
// // Specialized for whenever **T denom is zero**!
// template <>
// // double divide1(double numer, double denom)       // WORKS!
// // Can also be written more explicitly by adding in the explicit template type, `<double>`, like this instead!
// T divide3<typename T, T numer, 0>()
// {
//     printf("divide3 aint gonna never done did divide by zero! numer = %i; denom = %i\n", numer, denom);
//     return -2;
// }


int main()
{
    printf("Hello World\n\n");

    int i1;
    int i2;

    // 1. 
    printf("============\ndivide1\n============\n");

    i1 = divide1<int>(25, 2);
    printf("i1 = %i\n\n", i1); // 12

    i2 = divide1<int>(25, 0);
    printf("i2 = %i\n\n", i2); 

    // Call Template specialization #1
    printf("divide1(25.0, 0.0) = %f\n\n", divide1(25.0, 0.0));
    printf("divide1<double>(25, 0) = %f\n\n", divide1<double>(25, 0));

    // Call Template specialization #2
    printf("divide1<61, 3>() = %i\n\n", divide1<61, 3>());

    // Call Template specialization #3
    printf("divide1<92>(3) = %i\n\n", divide1<92>(3));

    // Call Template specialization #3 again (function overloaded)
    // Notice the 92 isn't even used by this function template! It's just there to get the correct
    // template specialization to be called, and could be *any* number!
    printf("divide1<92>(16, 3) = %i\n\n", divide1<92>(16, 3)); // 5

    // Call Template specialization #4
    printf("divide1<>() = %i\n\n", divide1<>()); // 6
    printf("divide1() = %i\n\n", divide1()); // 6

    // Call Template specialization #5
    printf("divide1<7>(16, 5) = %i\n\n", divide1<7>(16, 5)); // 3
    printf("divide1<7>(16, 3) = %i\n\n", divide1<7>(16, 3)); // 5
    // Call Template specialization #3 again
    printf("divide1<8>(16, 5) = %i\n\n", divide1<8>(16, 5)); // 3

    for (int i = 10; i >= 0; i--)
    {
        int ans = divide1(100, i);
        printf("ans = %i\n", ans);
    }
    printf("\n");

    // 2. 
    printf("============\ndivide2\n============\n");

    i1 = divide2<25, 2>();
    printf("i1 = %i\n\n", i1); // 12

    i2 = divide2<25, 0>();
    printf("i2 = %i\n\n", i2); 

    // 3. 
    printf("============\ndivide3\n============\n");

    i1 = divide3<int, 31, 2>();
    printf("i1 = %i\n\n", i1); // 12

    i2 = divide3<int, 31, 0>();
    printf("i2 = %i\n\n", i2); 


    return 0;
}







