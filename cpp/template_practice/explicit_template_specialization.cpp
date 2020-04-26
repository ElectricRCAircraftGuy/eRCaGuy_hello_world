/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
25 Apr. 2020

Let's play with some explicit template specialization to learn about it.

References:
1. https://en.wikipedia.org/wiki/Template_(C%2B%2B)#Template_specialization

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
        return 0;
    }

    return numer/denom;
}

// Template specialization; see: https://en.wikipedia.org/wiki/Template_(C%2B%2B)#Explicit_template_specialization
template <>
double divide1(double numer, double denom)
{
    printf("divide1 double type: just returning -0.1419\n");
    return -0.1419;
}


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
        return 0;
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
        return 0;
    }

    return numer/denom;
}

// // 3. A function template based on static/compile-time **template inputs**, with numer & denom
// // passed in as **template parameter inputs**, and having their types specified by the **first
// // template parameter type, T**
// template <typename T, T numer, T denom>
// T divide3()
// {
//     // WORKS--compile-time check!
//     // This works because numer and denom are both **template parameters**, so they get inserted
//     // into their own versions of this function **at compile time**!
//     // static_assert(denom != 0, "dividing by zero not allowed");
    
//     // WORKS--run-time check!
//     if (denom == 0)
//     {
//         printf("divide3: cannot divide by zero\n");
//         return 0;
//     }

//     return numer/denom;
// }




int main()
{
    printf("Hello World\n");

    int i1;
    int i2;

    // 1. 
    printf("\ndivide1\n============\n");

    i1 = divide1<int>(25, 2);
    printf("i1 = %i\n", i1); // 12

    i2 = divide1<int>(25, 0);
    printf("i2 = %i\n", i2); 

    printf("divide1(25.0, 0.0) = %f\n", divide1(25.0, 0.0));

    // for (int i = 10; i >= 0; i--)
    // {
    //     int ans = divide(100, i);
    //     printf("  ans = %i\n", ans);
    // }

    // 2. 
    printf("\ndivide2\n============\n");

    i1 = divide2<25, 2>();
    printf("i1 = %i\n", i1); // 12

    i2 = divide2<25, 0>();
    printf("i2 = %i\n", i2); 

    // 3. 
    printf("\ndivide3\n============\n");

    i1 = divide3<int, 31, 2>();
    printf("i1 = %i\n", i1); // 12

    i2 = divide3<int, 31, 0>();
    printf("i2 = %i\n", i2); 


    return 0;
}







