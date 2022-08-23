/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Aug. 2022

Learn how to link to and use the `yaml-cpp` library (https://github.com/jbeder/yaml-cpp).
See full installation instructions to use this library, in "eRCaGuy_hello_world/cpp/README.md".

STATUS: wip

time g++ -Wall -Wextra -Werror -O3 -std=c++17 yaml-cpp_lib_demo.cpp -o bin/a -lyaml-cpp && bin/a



To compile and run (assuming you've already `cd`ed into this dir):
[see the "BEST" option below for my final answer for this code]
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
# With `-DFMT_HEADER_ONLY` in it:
# time g++ -Wall -Wextra -Werror -O3 -std=c++17 -DFMT_HEADER_ONLY fmt_lib_demo.cpp ../c/timinglib.c -o bin/a && bin/a

# Use this one since I have defined the macros manually below, just above `#include <fmt/format.h>`;
# has `-lfmt`:
time g++ -Wall -Wextra -Werror -O3 -std=c++17 fmt_lib_demo.cpp ../c/timinglib.c -o bin/a -lfmt && bin/a

# OR: has "/usr/local/lib/libfmt.a":
time g++ -Wall -Wextra -Werror -O3 -std=c++17 fmt_lib_demo.cpp ../c/timinglib.c "/usr/local/lib/libfmt.a" -o bin/a && bin/a

# **BEST:** with `-lfmt` AND `-DFMT_ENFORCE_COMPILE_STRING` in it to enforce static, compile-time format
# string checking. See:
# 1. *****+ [my notes] https://github.com/fmtlib/fmt/issues/2157#issuecomment-1117930229
# 1. ***** https://fmt.dev/latest/api.html#compile-time-format-string-checks
# 1. https://fmt.dev/latest/usage.html
#
# 1st: FIRST, follow the fmt library setup and installation instructions here:
# "eRCaGuy_hello_world/cpp/README.md"
# 2nd: THEN, run this build & run command:
time g++ -Wall -Wextra -Werror -O3 -std=c++17 -DFMT_ENFORCE_COMPILE_STRING fmt_lib_demo.cpp ../c/timinglib.c -o bin/a -lfmt && bin/a
```

References:
1. See full installation instructions to use this `yaml-cpp` library, in:
   "eRCaGuy_hello_world/cpp/README.md".
1. https://github.com/jbeder/yaml-cpp
1. ***** https://github.com/jbeder/yaml-cpp/wiki/Tutorial
1. https://github.com/jbeder/yaml-cpp/wiki/How-To-Emit-YAML


*/



// Local includes
// NA

// 3rd-party library includes
#include <yaml-cpp/yaml.h>

// Linux includes
// NA

// C & C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.


int main()
{
    printf("Practice ");
    std::cout << "reading from a YAML file!\n\n";

    YAML::Node yaml_config;
    constexpr char YAML_FILE_PATH_WRONG[] = "yaml-cpp_lib_demooo.yaml";
    constexpr char YAML_FILE_PATH[] = "yaml-cpp_lib_demo.yaml";

    // Show how to catch a thrown exception by intentionally typing the file path wrong so that
    // `LoadFile()` will throw an exception. Refer to the yaml-cpp source code--it throws
    // exceptions in **a lot** of places, rather than using explicit error handling! Ex: search for
    // "throw" in the source files here:
    // 1. eRCaGuy_hello_world/cpp/yaml-cpp/include/yaml-cpp/node/parse.h
    // 1. eRCaGuy_hello_world/cpp/yaml-cpp/src/parse.cpp
    try
    {
        yaml_config = YAML::LoadFile(YAML_FILE_PATH_WRONG);
    }
    catch (const std::exception& e)
    {
        printf("Unable to load file \"%s\".\n"
               "  Exception caught: e.what() = ", YAML_FILE_PATH_WRONG);
        std::cout << e.what() << "\n";
    }
    std::cout << "Trying again...\n";

    // Now show what happens if you do NOT catch the exception! It crashes the program with:
    //      terminate called after throwing an instance of 'YAML::BadFile'
    //        what():  bad file: yaml-cpp_lib_demooo.yaml
    //      Aborted (core dumped)
    // yaml_config = YAML::LoadFile(YAML_FILE_PATH_WRONG);

    // Now do it correctly
    YAML::Node config = YAML::LoadFile(YAML_FILE_PATH);






    return 0;
}



/*
SAMPLE OUTPUT:



*/
