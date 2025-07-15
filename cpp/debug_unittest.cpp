///usr/bin/env ccache g++ -Wall -Wextra -Werror -Wno-error=cpp -O3 -std=gnu++17 -pthread "$0" stdout_capture_lib.cpp -lgtest -lgtest_main -o /tmp/a && /tmp/a "$@"; exit
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

// TEST(StdoutCaptureTest, BasicCapture)
// {
//     std::cout << "1. Before capture" << std::endl;
//     printf("2. Before capture\n");

//     StdoutCapture capture;
//     capture.start();

//     std::cout << "1. Captured." << std::endl;
//     printf("2. Captured.\n");

//     std::string captured = capture.stop();

//     std::cout << "1. After capture." << std::endl;
//     printf("2. After capture.\n");

//     // Print captured output to console
//     printf("Captured output:\n%s", captured.c_str());

//     std::string expected_output = "1. Captured.\n2. Captured.\n";
//     EXPECT_EQ(captured, expected_output) << "Captured output does not match expected output.";
// }

TEST(Debug, TodoPrints)
{
    StdoutCapture capture;
    
    capture.start();
    TODO_PRINTF("Statement 1\n");
    std::string captured = capture.stop();
    printf("Captured output: %s", captured.c_str());    
    
    ////////

    TODO_PRINTF("Statement 2: %s, %i, %u\n", "test", 42, 100u);

    

    EXPECT_TRUE(false);
}

} // namespace


/*
Example run and output:




*/
