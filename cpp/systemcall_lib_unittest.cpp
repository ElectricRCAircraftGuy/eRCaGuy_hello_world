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
# NB: the libgtest*.a files MUST come at the end like this!
time ( \
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
    -I"googletest/googletest/include" -I"googletest/googlemock/include" \
    -DFMT_ENFORCE_COMPILE_STRING \
    systemcall_lib_unittest.cpp \
    systemcall_lib.cpp \
    bin/libgtest.a bin/libgtest_main.a \
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
    const std::string EXPECTED_RESPONSE_STR = "hello_world.cpp\n";
    std::string error;

    // Test `system_call()`
    error = systemcall::system_call("ls hello_world.cpp", &response_str, &cmd_return_code);
    EXPECT_EQ(error, systemcall::ERROR_OK);
    EXPECT_EQ(response_str, EXPECTED_RESPONSE_STR);
    EXPECT_EQ(cmd_return_code, 0);

    // Test `system_call2()`
    error = systemcall::system_call2("ls hello_world.cpp", &response_str, &cmd_return_code);
    EXPECT_EQ(error, systemcall::ERROR_OK);
    EXPECT_EQ(response_str, EXPECTED_RESPONSE_STR);
    EXPECT_EQ(cmd_return_code, 0);

    // Test `system_call()` again, to ensure the `response_str` is cleared and not just appended
    error = systemcall::system_call("ls hello_world.cpp", &response_str, &cmd_return_code);
    EXPECT_EQ(error, systemcall::ERROR_OK);
    EXPECT_EQ(response_str, EXPECTED_RESPONSE_STR);
    EXPECT_EQ(cmd_return_code, 0);
}

} // anonymous namespace



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time ( \
    >     time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
    >     -I"googletest/googletest/include" -I"googletest/googlemock/include" \
    >     -DFMT_ENFORCE_COMPILE_STRING \
    >     systemcall_lib_unittest.cpp \
    >     systemcall_lib.cpp \
    >     bin/libgtest.a bin/libgtest_main.a \
    >     -o bin/a \
    >     -lfmt \
    >     && time bin/a \
    > )

    real    0m1.646s
    user    0m1.481s
    sys 0m0.107s
    Running main() from googletest/googletest/src/gtest_main.cc
    [==========] Running 1 test from 1 test suite.
    [----------] Global test environment set-up.
    [----------] 1 test from SystemCallTest
    [ RUN      ] SystemCallTest.ListFile
    [       OK ] SystemCallTest.ListFile (3 ms)
    [----------] 1 test from SystemCallTest (3 ms total)

    [----------] Global test environment tear-down
    [==========] 1 test from 1 test suite ran. (3 ms total)
    [  PASSED  ] 1 test.

    real    0m0.005s
    user    0m0.005s
    sys 0m0.000s

    real    0m1.651s
    user    0m1.485s
    sys 0m0.107s


*/
