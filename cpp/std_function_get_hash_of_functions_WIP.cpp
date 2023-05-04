///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
26-27 Apr. 2023

Try to get a function address, and/or a unique hash of a function, which is wrapped by a
`std::function<>` wrapper object.
See this Q here: https://stackoverflow.com/q/76114714/4561887
EXPLANATION:
TODO

STATUS: wip

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
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 hello_world_extra_basic.cpp -o bin/a && bin/a
```

References:
1. The question: https://stackoverflow.com/q/76114714/4561887
1. Answer by @KamilCuk: https://stackoverflow.com/a/76114883/4561887
1. ---
1. https://en.cppreference.com/w/cpp/utility/functional/function
1. https://en.cppreference.com/w/cpp/utility/functional/function/target
1. https://en.cppreference.com/w/cpp/utility/functional/function/target_type
1. https://en.cppreference.com/w/cpp/language/typeid
1. https://en.cppreference.com/w/cpp/types/type_info
1. https://en.cppreference.com/w/cpp/types/type_info/name
1. https://en.cppreference.com/w/cpp/types/type_info/hash_code
1. https://stackoverflow.com/q/28746744/4561887 -
   Passing capturing lambda as function pointer
1. "eRCaGuy_hello_world/c/func_ptr_typedef.c" - C-style function pointers and
   typedefs
1. https://www.nextptr.com/tutorial/ta1188594113/passing-cplusplus-captureless-lambda-as-function-pointer-to-c-api
   "The stand-alone function and static member function choices require us to
    write a separate function, which is tedious and hinders the readability
    [GS: I STRONGLY DISAGREE!]. Besides, the stand-alone function solution is
    an anti-OOP pattern [GS: THIS IS AN EXAMPLE OF C++-MINDSET DEVELOPERS
    OVERCOMPLICATING THINGS AGAIN]. That brings us to the implementation of
    Worker::start using capture-less lambda expression"

    - GS notes: This is a really good pattern to know, however, since C++
      developers will consider it "beautiful" and "perfect" and I would be very
      wise to learn it! I will *certainly* see it again, and maybe even use it
      myself to appease my peers in these situations! There *is* a certain sense
      of beauty once you understand this complicated mess, after-all.

1. https://stackoverflow.com/questions/9186510/how-can-i-store-a-lambda-expression-as-a-field-of-a-class-in-c11#comment11559871_9186510
    Comment by @bames53: "Every lambda expression creates it's own unique type.
    In `auto A = [](){}; auto B = [](){};`, `A` and `B` are
    **not** the same type."!

*/

#include <cassert>
#include <functional>
#include <iostream>
#include <vector>


int f(int a)
{
    return -a;
}

int f2(int a)
{
    return a;
}

// typedef to a basic function pointer that returns `int` and accepts `int`
typedef int (*func_t)(int); // valid in C and C++
// using func_t = int (*)(int);  // same as above; C++ only

int main()
{
    // auto lambda1 = [](int a) {return -a;};
    func_t* lambda1 = [](int a) {return -a;};

    std::vector<std::function<int(int)>> functions
    {
        f,
        f,
        f2,
        f2,
        // NB: Comment by @bames53: "Every lambda expression creates it's own
        // unique type. In `auto A = [](){}; auto B = [](){};`, `A` and `B` are
        // **not** the same type."
        // Source:
        // https://stackoverflow.com/questions/9186510/how-can-i-store-a-lambda-expression-as-a-field-of-a-class-in-c11#comment11559871_9186510
        lambda1,
        [](int a) {return -a;},
        [](int a) {return -a;},
    };

    // 1. Print addresses to `f` and `f2`

    printf("addr of f  = %zu\n", (size_t)f);
    // printf("%zu\n", (size_t)&f); // same as above since functions
                                    // automatically adjust to ptrs

    printf("addr of f2 = %zu\n", (size_t)f2);
    // printf("%zu\n", (size_t)&f2); // same as above since functions
                                     // automatically adjust to ptrs

    printf("\n");

    // 2. proof of concept: try to cast a `std::function<>` function wrapper
    // to a basic function pointer

    printf("Proof of concept: address of an (R-value) lambda function: %zu\n",
        (size_t)(func_t)([](int a) {return -a;}));
    printf("\n");

    // 3. Try to take the address of a `std::function` to see if it differs from
    // the function address (it *should* differ, since a `std::function` is its
    // own type of class wrapper object around a function pointer)

    std::function<int(int)> fn = f;
    printf("addr of fn = %zu\n", (size_t)&fn);
    // Same end result as above, except that if we tried to use(dereference) the
    // intermediate result of the cast to `(func_t)` it would be **undefined
    // behavior**! So, this intermediate cast is really useless.
    printf("addr of fn = %zu\n", (size_t)(func_t)&fn);

    // Q: Can we cast a `std::function<>` to a function ptr?
    // A: No! We can't! Error:
    //
    //      cpp/std_function_get_hash_of_functions.cpp: In function ‘int main()’:
    //      cpp/std_function_get_hash_of_functions.cpp:111:27: error: invalid cast from type ‘std::function<int(int)>’ to type ‘func_t’ {aka ‘int (*)(int)’}
    //        111 |     func_t func = (func_t)fn;
    //            |                           ^~
    //
    // func_t func = (func_t)fn;

    func_t* func_wrapped_by_fn = fn.target<func_t>();
    // Good
    printf("addr of the wrapped func = %zu\n", (size_t)*func_wrapped_by_fn);
    assert((size_t)*func_wrapped_by_fn == (size_t)f);

    // func_t* func_wrapped_by_fn_2 = fn.target<fn.target_type()>(); // FAILS
    // func_t* func_wrapped_by_fn_2 = fn.target<main()::<lambda(int)>>(); // FAILS
    // func_t* func_wrapped_by_fn_2 = fn.target<lambda(int)>(); // FAILS


    printf("\n");


    // 2. Now try to obtain the addresses to functions wrapped by
    // `std::function<>` objects in the `functions` vector

    for (const std::function<int(int)>& func : functions)
    {
        // int (* const * func_ptr)(int) = func.target<int(*)(int)>();
        const func_t* func_ptr = func.target<func_t>(); // same as above, but
                                                        // waaaay cleaner and
                                                        // easier to read!

        if (func_ptr == nullptr)
        {
            printf("Error: nullptr! (Probably pointing to a lambda "
                   "function).\n");
        }
        else
        {
            printf("%zu\n", (size_t)(*func_ptr));
            // printf("%zu\n", (size_t)(func_ptr)); // same as above
        }

        /////////
        std::cout << "typeid = " << func.target_type().name() << "\n";
        std::cout << "typeid = " << func.target_type().hash_code() << "\n";
        std::cout << "\n";


        // Now print the mangled function **names** too just for fun!

    }
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
