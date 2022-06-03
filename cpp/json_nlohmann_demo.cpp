/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2022

This is a quick demo to practice using the nlohmann "JSON for Modern C++" header-only library for
parsing (deserializing) and printing (serializing) JSON data. This is particularly useful for
parsing HTTP REST API responses received from command-line `curl` or the C `libcurl`!

STATUS: done and works perfectly! EXCELLENT demo! It show how to print JSON objects using both
C-style `printf()`-based *and* C++-style prints!

To compile and run (assuming you've already `cd`ed into this dir):
[see the "BEST" option below for my final answer for this code]
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1st: FIRST, follow the C++ `nlohmann/json` library setup and installation instructions here:
# "eRCaGuy_hello_world/cpp/README.md"
# 2nd: THEN, run this build & run command:
#
time g++ -Wall -Wextra -Werror -O3 -std=c++17 -I"json/single_include" json_nlohmann_demo.cpp -o bin/a && bin/a
# Or, WITH ccache compiler caching to speed up builds!:
time ccache g++ -Wall -Wextra -Werror -O3 -std=c++17 -I"json/single_include" json_nlohmann_demo.cpp -o bin/a && bin/a
```

References:
1. nlohmann/json:
    1. https://github.com/nlohmann/json#serialization--deserialization
    1. https://json.nlohmann.me/
        1. API documentation: https://json.nlohmann.me/api/basic_json/
        1. See `get<>()` examples at the bottom of this page here!:
           https://json.nlohmann.me/api/basic_json/get/
        1. See `get_ptr<>()` examples at the bottom of
           here: https://json.nlohmann.me/api/basic_json/get_ptr/
        1. https://json.nlohmann.me/api/basic_json/get_ref/
1. https://en.cppreference.com/w/cpp/language/string_literal


*/



// Local includes
// NA

// 3rd-party library includes
#include <nlohmann/json.hpp>  // a header-only library

// Linux includes
// NA

// C and C++ includes
#include <cstdint>   // For `uint8_t`, `int8_t`, etc.
#include <cstdio>    // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    // See a bunch of examples here:
    // https://github.com/nlohmann/json#serialization--deserialization

    // Create a json object from a raw (`R`) C++ string literal.
    // NB: the `parse()` method can throw C++ run-time exceptions if parsing fails!
    // Ex: change `true` below to `True` and it will throw a run-time exception and core dump since
    // that is not a valid literal! Example error:
    //
    //      terminate called after throwing an instance of 'nlohmann::detail::parse_error'
    //        what():  [json.exception.parse_error.101] parse error at line 4, column 23: syntax error while parsing value - invalid literal; last read: '"status": T'
    //      Aborted (core dumped)
    //
    nlohmann::json j1 = nlohmann::json::parse(R"(
        {
            "name": "John",
            "status": true,
            "pi": 3.141
        }
    )");

    // C++ prints using `std::cout`
    std::cout << "name:   " << j1["name"] << "\n";
    std::cout << "status: " << j1["status"] << "\n";
    std::cout << "pi:     " << j1["pi"] << "\n";
    std::cout << "\n";

    // C-style prints using `printf()`
    //
    // See also the examples at the bottom of the documentation for `.get<>()`, `.get_ref<>()`, and
    // `.get_ptr<>()` here:
    // 1. https://json.nlohmann.me/api/basic_json/get/
    // 1. https://json.nlohmann.me/api/basic_json/get_ref/
    // 1. https://json.nlohmann.me/api/basic_json/get_ptr/
    printf("name:   %s\n", j1["name"].get_ref<const std::string&>().c_str());
    printf("status: %u\n", j1["status"].get<bool>());
    printf("pi:     %f\n", j1["pi"].get<double>());
    printf("\n");

    // Print the whole object at once as a json string blob
    std::cout << j1.dump() << "\n";     // C++-style
    printf("%s\n", j1.dump().c_str());  // C-style
    printf("\n");

    // Store into a string first, then print
    std::string j1str = j1.dump();
    std::cout << j1str << "\n";     // C++-style
    printf("%s\n", j1str.c_str());  // C-style
    printf("\n");

    // Pretty print; pass in the number of spaces to indent
    std::cout << j1.dump(4) << "\n";     // C++-style
    printf("%s\n", j1.dump(4).c_str());  // C-style
    printf("\n");

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time ccache g++ -Wall -Wextra -Werror -O3 -std=c++17 -I"json/single_include" json_nlohmann_demo.cpp -o bin/a && bin/a

    real    0m2.971s
    user    0m2.856s
    sys 0m0.115s
    Hello world!

    name:   "John"
    status: true
    pi:     3.141

    name:   John
    status: 1
    pi:     3.141000

    {"name":"John","pi":3.141,"status":true}
    {"name":"John","pi":3.141,"status":true}

    {"name":"John","pi":3.141,"status":true}
    {"name":"John","pi":3.141,"status":true}

    {
        "name": "John",
        "pi": 3.141,
        "status": true
    }
    {
        "name": "John",
        "pi": 3.141,
        "status": true
    }


*/
