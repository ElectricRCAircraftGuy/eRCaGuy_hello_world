/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
May 2022

Googletest (gtest) unit tests for systemcall_lib.h/.cpp.

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. FIRST, follow the detailed clone and build steps in "eRCaGuy_hello_world/cpp/README.md" in
# order to prepare to use the following libraries:
#   1. gtest
#   1. fmt - use `-lfmt` AND `-DFMT_ENFORCE_COMPILE_STRING` below. See "fmt_lib_demo.cpp"

# 2. THEN, build and run this unit test with this command!:
time ( \
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
    -I"googletest/googletest/include" -I"googletest/googlemock/include" \
    bin/libgtest.a bin/libgtest_main.a \
    -DFMT_ENFORCE_COMPILE_STRING \
    systemcall_lib_unittest.cpp \
    systemcall_lib.cpp \
    -o bin/a \
    -lfmt \
    && time bin/a \
)
```

References:
1. https://github.com/google/googletest
    1. https://github.com/google/googletest/blob/main/docs/reference/assertions.md - for
       `EXPECT_EQ()`, `EXPECT_STREQ()`--for C-strings only, etc.!
1. [my answer on how to build gtest with gcc] https://stackoverflow.com/a/72108315/4561887

*/


// Local includes
#include "systemcall_lib.h"

// 3rd-party library includes
// #include "gmock/gmock.h"
#include "gtest/gtest.h"

// Linux includes
// NA

// C and C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.


// anonymous namespace
namespace
{

/// Test a simple `ls` system call
TEST(SystemCallTest, ListFile)
{
    std::string response_str;
    int cmd_return_code;
    std::string error = systemcall::system_call("ls hello_world.cpp", &response_str,
        &cmd_return_code);

    EXPECT_EQ(error, systemcall::ERROR_OK);
    EXPECT_EQ(response_str, std::string("hello_world"));
    EXPECT_EQ(cmd_return_code, 0);
}

} // anonymous namespace



/*
SAMPLE OUTPUT:



*/
