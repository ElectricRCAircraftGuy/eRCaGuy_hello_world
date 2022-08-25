/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Aug. 2022

Learn how to link to and use the `yaml-cpp` library (https://github.com/jbeder/yaml-cpp).
See full installation instructions to use this library, in "eRCaGuy_hello_world/cpp/README.md".

STATUS: done and works!


Build commands:
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1st: FIRST, follow the yaml-cpp library setup and installation instructions here:
# "eRCaGuy_hello_world/cpp/README.md"
# THEN, use one of the two options below to build and run this code:

# [my preference]
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
#include <cassert>
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.


int main()
{
    printf("Practice ");
    std::cout << "reading from a YAML file!\n\n";

    YAML::Node root_node;
    const char* filename;
    constexpr char YAML_FILE_PATH_WRONG[] = "yaml-cpp_lib_demooo.yaml";
    constexpr char YAML_FILE_PATH_EMPTY[] = "yaml-cpp_lib_demo_empty.yaml";
    constexpr char YAML_FILE_PATH[] = "yaml-cpp_lib_demo.yaml";

    // Show how to catch a thrown exception by intentionally typing the file path wrong so that
    // `LoadFile()` will throw an exception. Refer to the yaml-cpp source code--it throws
    // exceptions in **a lot** of places, rather than using explicit error handling! Ex: search for
    // "throw" in the source files here:
    // 1. eRCaGuy_hello_world/cpp/yaml-cpp/include/yaml-cpp/node/parse.h
    // 1. eRCaGuy_hello_world/cpp/yaml-cpp/src/parse.cpp
    try
    {
        root_node = YAML::LoadFile(YAML_FILE_PATH_WRONG);
    }
    catch (const std::exception& e)
    {
        std::cout << "Unable to load file \"" << YAML_FILE_PATH_WRONG << "\".\n"
                  << "  Exception caught: e.what() = " << e.what() << "\n";
    }
    std::cout << "Trying again...\n";

    // Now show what happens if you do NOT catch the exception! It crashes the program with:
    //      terminate called after throwing an instance of 'YAML::BadFile'
    //        what():  bad file: yaml-cpp_lib_demooo.yaml
    //      Aborted (core dumped)
    // root_node = YAML::LoadFile(YAML_FILE_PATH_WRONG);

    // Now load a file which *does* exist, but is empty.
    filename = YAML_FILE_PATH_EMPTY;
    root_node = YAML::LoadFile(filename);
    if (root_node.IsNull())
    {
        std::cout << "Error: YAML::Node is Null, indicating the yaml file was empty or invalid.\n"
                     "  Filename = \"" << filename << "\".\n";
    }
    else
    {
        std::cout << "YAML file successfully loaded.\n";
    }

    // Finally, load a good and valid file!
    filename = YAML_FILE_PATH;
    root_node = YAML::LoadFile(filename);
    if (root_node.IsNull())
    {
        std::cout << "Error: YAML::Node is Null, indicating the yaml file was empty or invalid.\n"
                     "  Filename = \"" << filename << "\".\n";
    }
    else
    {
        std::cout << "YAML file \"" << filename << "\" successfully loaded.\n";
    }

    // Print out the whole thing!
    std::cout << "\nWHOLE FILE:\n" << root_node << "\n\n";

    // Extract just some parts I care about. See the tutorial:
    // https://github.com/jbeder/yaml-cpp/wiki/Tutorial

    assert(root_node.IsMap());
    assert(root_node["data"].IsSequence());

    // Iterate over the "data" sequence (list) in this yaml file, printing select data
    YAML::Node data_node = root_node["data"];
    assert(data_node.IsSequence());
    for (size_t i = 0; i < data_node.size(); i++)
    {
        std::cout << data_node[i]["name"] << ", " << data_node[i]["value"] << "\n";
    }

    // Iterate over the "data" sequence (list) in this yaml file, printing each map in the list
    std::cout << "\n";
    for (size_t i = 0; i < data_node.size(); i++)
    {
        std::cout << "data_node[" << i << "] = \n" << data_node[i] << "\n\n";
    }

    // Iterate over a map in the data
    YAML::Node data_phi = root_node["data"][6];
    assert(data_phi.IsMap());
    std::cout << "data_phi = \n" << data_phi << "\n\n";
    std::cout << "data_phi.size() = " << data_phi.size() << "\n";
    // NB: this does NOT work! See the output. This is how you iterate over a sequence, NOT a map!
    for (size_t i = 0; i < data_phi.size(); i++)
    {
        // Does not work right. That's the point: to show you what NOT to do. :)
        std::cout << "data_phi[" << i << "] = " << data_phi[i] << "\n";
    }
    std::cout << "\n";
    // This is correct to iterate over a map!
    // See the `YAML::Node lineup` example here:
    // https://github.com/jbeder/yaml-cpp/wiki/Tutorial#basic-parsing-and-node-editing
    for (YAML::const_iterator it = data_phi.begin(); it != data_phi.end(); it++)
    {
        std::string key = it->first.as<std::string>();
        std::string value = it->second.as<std::string>();
        printf("key = %-15s value = %-15s\n", key.c_str(), value.c_str());
    }
    std::cout << "\n";

    // Do some math on a value from a map node
    double value = data_phi["value"].as<double>();
    printf("phi value = %f; phi value*2.1 = %f\n", value, value*2.1);


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 yaml-cpp_lib_demo.cpp -o bin/a -lyaml-cpp && bin/a

    real    0m2.449s
    user    0m2.240s
    sys 0m0.130s
    Practice reading from a YAML file!

    Unable to load file "yaml-cpp_lib_demooo.yaml".
      Exception caught: e.what() = bad file: yaml-cpp_lib_demooo.yaml
    Trying again...
    Error: YAML::Node is Null, indicating the yaml file was empty or invalid.
      Filename = "yaml-cpp_lib_demo_empty.yaml".
    YAML file "yaml-cpp_lib_demo.yaml" successfully loaded.

    WHOLE FILE:
    name: yaml-cpp_demo.yaml
    description: This is a demo yaml file that can be imported, for example, by the yaml-cpp library.
    author: Gabriel Staples
    date: Aug. 2022
    data:
      - name: x
        description: x position
        units: mm
        type: int64_t
        value: 100
      - name: y
        description: y position
        units: mm
        type: int64_t
        value: 200
      - name: z
        description: z position
        units: mm
        type: int64_t
        value: 300
      - name: u
        description: velocity in the x direction
        units: mm/s
        type: int64_t
        value: 10
      - name: v
        description: velocity in the y direction
        units: mm/s
        type: int64_t
        value: 11
      - name: w
        description: velocity in the z direction
        units: mm/s
        type: int64_t
        value: 12
      - &1
        name: phi
        description: roll angle
        units: deg
        type: double
        value: 0.10
      - name: theta
        description: pitch angle
        units: deg
        type: double
        value: -0.20
      - name: psi
        description: yaw angle (heading)
        units: deg
        type: double
        value: 45.1234
      - *1

    x, 100
    y, 200
    z, 300
    u, 10
    v, 11
    w, 12
    phi, 0.10
    theta, -0.20
    psi, 45.1234
    phi, 0.10

    data_node[0] =
    name: x
    description: x position
    units: mm
    type: int64_t
    value: 100

    data_node[1] =
    name: y
    description: y position
    units: mm
    type: int64_t
    value: 200

    data_node[2] =
    name: z
    description: z position
    units: mm
    type: int64_t
    value: 300

    data_node[3] =
    name: u
    description: velocity in the x direction
    units: mm/s
    type: int64_t
    value: 10

    data_node[4] =
    name: v
    description: velocity in the y direction
    units: mm/s
    type: int64_t
    value: 11

    data_node[5] =
    name: w
    description: velocity in the z direction
    units: mm/s
    type: int64_t
    value: 12

    data_node[6] =
    name: phi
    description: roll angle
    units: deg
    type: double
    value: 0.10

    data_node[7] =
    name: theta
    description: pitch angle
    units: deg
    type: double
    value: -0.20

    data_node[8] =
    name: psi
    description: yaw angle (heading)
    units: deg
    type: double
    value: 45.1234

    data_node[9] =
    name: phi
    description: roll angle
    units: deg
    type: double
    value: 0.10

    data_phi =
    name: phi
    description: roll angle
    units: deg
    type: double
    value: 0.10

    data_phi.size() = 5
    data_phi[0] =
    data_phi[1] =
    data_phi[2] =
    data_phi[3] =
    data_phi[4] =

    key = name            value = phi
    key = description     value = roll angle
    key = units           value = deg
    key = type            value = double
    key = value           value = 0.10

    phi value = 0.100000; phi value*2.1 = 0.210000


*/
