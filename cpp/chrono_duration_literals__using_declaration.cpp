/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
12 Apr. 2022

Practice using `std::chrono::duration<>` literals (since C++14).

STATUS: done!

vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
Key takeaways:
To use `std::chrono::duration<>` literals like `30s` for "30 seconds", ex: in this statement here:

    std::chrono::seconds halfmin = 30s;

...you must use the appropriate `using namespace` declaration, such as:

    // Choose at least **one** of these!:
    using namespace std::literals;
    using namespace std::chrono_literals;  // [my preference]
    using namespace std::literals::chrono_literals;
    using namespace std::chrono;

...OR you can leave out those `using namespace` declarations, but then you must explicitly cast the
   integer to a `std::chrono::duration<>` type, like this, for example, to `std::chrono::seconds`,
   which is a typedef of `std::chrono::duration<int64_t, ratio<1, 1>>`:

    std::chrono::seconds halfmin = std::chrono::seconds(30);

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Notes:
- I think `std::chrono` is pretty complicated and hard to understand, and makes working with time
  much **more complicated** and **obfuscated** in order to obtain a **perceived benefit** of type
  safety. In other words, I do **not** really recommend using it. However, I still need to learn
  how to use it for the cases when I must interact with C++ APIs which require it, or when I must
  interact with code which uses it, from peers and coworkers, for example.
- I think `uint64_t` makes a better timestamp type. See my answer and notes on `std::chrono` here:
  https://stackoverflow.com/a/49066369/4561887


To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 chrono_duration_literals__using_declaration.cpp -o bin/a && bin/a
```

References:
1. [Question I'm going to answer with this code] Using operator ""s for std::chrono with gcc:
   https://stackoverflow.com/q/50503445/4561887
    1. *****+ [MY ANSWER] Don't forget a using namespace declaration to get
       access to std::chrono::duration<> literals:
       https://stackoverflow.com/a/71880699/4561887
1. https://en.cppreference.com/w/cpp/header/chrono
1. *****https://en.cppreference.com/w/cpp/chrono/duration
1. *****+https://en.cppreference.com/w/cpp/chrono/operator%22%22s
1. https://en.cppreference.com/w/cpp/language/using_declaration
1. [my ans] Getting an accurate execution time in C++ (micro seconds):
   https://stackoverflow.com/a/49066369/4561887

This code is copied and modified from: https://en.cppreference.com/w/cpp/chrono/operator%22%22s
- I helped edit that code there on the cppreference.com wiki as well.
See the "Notes" section from that page above too! They are **very** important and helpful!:

Notes

These operators are declared in the namespace std::literals::chrono_literals, where both literals
and chrono_literals are inline namespaces. Access to these operators can be gained with `using
namespace std::literals`, `using namespace std::chrono_literals`, and `using namespace
std::literals::chrono_literals`.

In addition, within the namespace std::chrono, the directive using namespace
literals::chrono_literals; is provided by the standard library, so that if a programmer uses using
namespace std::chrono; to gain access to the classes in the chrono library, the corresponding
literal operators become visible as well.

std::string also defines operator""s, to represent literal objects of type std::string, but it is a
string literal: 10s is ten seconds, but "10"s is a two-character string.


GS notes:

To get access to the special chrono literal types:
     h, min, s, ms, us, ns
...you **must** use one of the `using`-declarations below!:

    using namespace std::literals;
    // the most common and logical one to use since the name makes the most sense
    using namespace std::chrono_literals;
    using namespace std::literals::chrono_literals;
    using namespace std::chrono;

See, for ex: https://en.cppreference.com/w/cpp/chrono/operator%22%22s

*/



#include <chrono>
#include <iostream>
#include <typeinfo> // See: https://stackoverflow.com/a/81886/4561887

// Use all relevant `using namespace` declarations.
void example1()
{
    printf("example1\n");

    using namespace std::literals;
    using namespace std::chrono_literals;  // [my preference]
    using namespace std::literals::chrono_literals;
    using namespace std::chrono;

    std::chrono::seconds halfmin = 30s;
    std::cout << "Half a minute is " << halfmin.count() << " seconds.\n"
              << "A minute and a second is " << (1min + 1s).count() << " seconds.\n";
    std::cout << "\n";
}

// Use just one `using namespace` declaration at-a-time.
void example2()
{
    printf("example2\n");

    // using namespace std::literals;                  // WORKS!
    using namespace std::chrono_literals;              // WORKS! [my preference is to use this one!]
    // using namespace std::literals::chrono_literals; // WORKS!
    // using namespace std::chrono;                    // WORKS!

    std::chrono::seconds halfmin = 30s;
    std::cout << "Half a minute is " << halfmin.count() << " seconds.\n"
              << "A minute and a second is " << (1min + 1s).count() << " seconds.\n";
    std::cout << "\n";
}

// Cast the number to a `std::chrono::duration<>` explicitly.
void example3()
{
    printf("example3\n");

    // NB: the type `std::chrono::duration<int64_t, std::ratio<1>>` is the equivalent of
    // `std::chrono::seconds`, since gcc has these typedefs in `<chrono>`, for instance:
    //
    //      /// nanoseconds
    //      typedef duration<int64_t, nano>         nanoseconds;
    //
    //      /// microseconds
    //      typedef duration<int64_t, micro>        microseconds;
    //
    //      /// milliseconds
    //      typedef duration<int64_t, milli>        milliseconds;
    //
    //      /// seconds
    //      typedef duration<int64_t>           seconds;


    // std::chrono::seconds halfmin = (std::chrono::seconds)30; // WORKS!
    // std::chrono::seconds halfmin = std::chrono::seconds(30); // WORKS! [my preference, if I'm going to cast!] <=========
    // std::chrono::seconds halfmin = std::chrono::seconds{30}; // WORKS!
    // ---
    // std::chrono::seconds halfmin = std::chrono::duration<int64_t, std::ratio<1>>(30); // WORKS!
    // std::chrono::seconds halfmin = std::chrono::duration<int64_t>(30);                // WORKS!
    // ---
    // auto halfmin = std::literals::chrono_literals::operator""s(30);                   // WORKS!
    // std::chrono::duration<long double, std::ratio<1>> halfmin = std::literals::chrono_literals::operator""s(30); // WORKS!

    // These do NOT work!
    // auto halfmin = std::literals::chrono_literals::operator""s((unsigned long long)30ULL);
    // std::chrono::seconds halfmin = 30;//std::literals::chrono_literals::operator""s();//30;
    // std::chrono::seconds halfmin = std::literals::chrono_literals::__check_overflow<std::chrono::seconds, 30>();//30;
    // std::chrono::seconds halfmin = (std::literals::chrono_literals::operator""s())30;//30;
    // std::chrono::seconds halfmin = static_cast<std::literals::chrono_literals::operator""s()>(30);//30;

    // std::chrono::seconds halfmin = static_cast<std::chrono::seconds>(30);                           // WORKS!
    std::chrono::seconds halfmin = static_cast<std::chrono::duration<int64_t, std::ratio<1, 1>>>(30);  // WORKS!

    // Print out some mangled type information, for fun; see: https://stackoverflow.com/a/81886/4561887
    std::cout << "typeid(halfmin).name() = " << typeid(halfmin).name() << "\n";

    std::cout << "Half a minute is " << halfmin.count() << " seconds.\n"
              << "A minute and a second is " << (std::chrono::minutes(1) +
                  std::chrono::seconds(1)).count() << " seconds.\n";
    std::cout << "\n";
}

int main()
{
    example1();
    example2();
    example3();

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 chrono_duration_literals__using_declaration.cpp -o bin/a && bin/a
    example1
    Half a minute is 30 seconds.
    A minute and a second is 61 seconds.

    example2
    Half a minute is 30 seconds.
    A minute and a second is 61 seconds.

    example3
    typeid(halfmin).name() = NSt6chrono8durationIlSt5ratioILl1ELl1EEEE
    Half a minute is 30 seconds.
    A minute and a second is 61 seconds.



*/
