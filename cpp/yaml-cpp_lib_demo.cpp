/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Aug. 2022

Learn how to link to and use the `yaml-cpp` library (https://github.com/jbeder/yaml-cpp).
See full installation instructions to use this library, in "eRCaGuy_hello_world/cpp/README.md".

STATUS: wip


Build commands:
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1st: FIRST, follow the yaml-cpp library setup and installation instructions here:
# "eRCaGuy_hello_world/cpp/README.md"
# THEN, use one of the two options below to build and run this code:

# Option 1: build from the static library which is **installed to the system** by specifying
# `-lyaml-cpp`
time g++ -Wall -Wextra -Werror -O3 -std=c++17 yaml-cpp_lib_demo.cpp -o bin/a -lyaml-cpp && bin/a

# OR: Option 2: manually specify the include dir location with `-I` **and** static library .a file
# (include the .a file **last**!)
time g++ -Wall -Wextra -Werror -O3 -std=c++17 -I"yaml-cpp/include" yaml-cpp_lib_demo.cpp yaml-cpp/build/libyaml-cpp.a -o bin/a && bin/a
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
