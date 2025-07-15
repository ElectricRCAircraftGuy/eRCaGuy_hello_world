///usr/bin/env ccache g++ -Wall -Wextra -Werror -Wno-error=cpp -O3 -std=gnu++17 -pthread "$0" stdout_capture_lib.cpp debug.cpp -lgtest -lgtest_main -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
July 2025

Unit test this library. 

To build and run: 
1. Follow my instructions: 
    Here: https://stackoverflow.com/a/75718815/4561887
    Or here: https://stackoverflow.com/a/75719098/4561887
2. Build and run this file:
    ```bash
    cd path/to/here
    ./stdout_capture_lib_unittest.cpp
    ```

    OR: 
    ```bash
    # Do NOT cd into the `cpp` dir here: 
    cd path/to/eRCaGuy_hello_world
    
    ccache g++ -Wall -Wextra -Werror -Wno-error=cpp -O3 -std=gnu++17 -pthread cpp/debug_unittest.cpp cpp/stdout_capture_lib.cpp cpp/debug.cpp -lgtest -lgtest_main -o /tmp/a && /tmp/a
    ```
    
*/


// Primary include
#include "debug.h"

// Local includes
#include "stdout_capture_lib.hpp"

// 3rd-party includes
#include <gtest/gtest.h>

// Linux/Unix includes
// NA

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes 
// NA


// anonymous namespace
namespace 
{

TEST(Debug, TodoPrints)
{
    StdoutCapture capture;
    std::string captured;
    std::string expected;
    
    capture.start();
    TODO_PRINTF("Statement 1\n");
    captured = capture.stop();
    printf("Captured output: %s", captured.c_str());
    expected = "TODO: debug_unittest.cpp:TestBody():63: Statement 1\n";
    EXPECT_EQ(captured, expected);

    capture.start();
    TODO_PRINTF("Statement 2: %s, %i, %u\n", "test", 42, 100u);
    captured = capture.stop();
    printf("Captured output: %s", captured.c_str());
    expected = "TODO: debug_unittest.cpp:TestBody():70: Statement 2: test, 42, 100\n";
    EXPECT_EQ(captured, expected);
}

} // namespace


/*
Example run and output:


eRCaGuy_hello_world/cpp$ ./debug_unittest.cpp 
Running main() from /home/gabriel/Downloads/Install_Files/gtest/googletest-1.14.0/googletest/src/gtest_main.cc
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from Debug
[ RUN      ] Debug.TodoPrints
Captured output: TODO: debug_unittest.cpp:TestBody():62: Statement 1
Captured output: TODO: debug_unittest.cpp:TestBody():69: Statement 2: test, 42, 100
[       OK ] Debug.TodoPrints (0 ms)
[----------] 1 test from Debug (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.


*/
