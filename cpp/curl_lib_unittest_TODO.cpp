/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
May 2022

Googletest (gtest) unit tests for curl_systemcall_lib.h/.cpp.

STATUS: wip/todo: THIS FILE IS A DIRECT COPY OF "curl_systemcall_lib_unittest.cpp" AND NEEDS TO BE
UPDATED TO TEST curl_lib.h/.cpp! <=============
Run `meld curl_systemcall_lib_unittest.cpp curl_lib_unittest.cpp` to compare the two files.

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
    curl_systemcall_lib_unittest.cpp \
    curl_systemcall_lib.cpp \
    systemcall_lib.cpp \
    bin/libgtest.a bin/libgtest_main.a \
    -o bin/a \
    -lfmt \
    && time bin/a \
)
```

References:
1. gtest:
    1. https://github.com/google/googletest
        1. https://github.com/google/googletest/blob/main/docs/reference/assertions.md - for
           `EXPECT_EQ()`, `EXPECT_STREQ()`--for C-strings only, etc.!
    1. [my answer on how to build gtest with gcc] https://stackoverflow.com/a/72108315/4561887
1. "cpp/curl_rest_api_http_post_and_get.c"

*/


// Local includes
#include "curl_systemcall_lib.h"

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
TEST(CurlSystemCallTest, PostToPublicRestApiServer)
{
    std::string response_str;
    // Obtain this expected response string at the command-line, as a sanity check, with:
    //      curl --data "" -X POST "https://gorest.co.in/public/v2/users"
    const std::string EXPECTED_RESPONSE_STR = "{\"message\":\"Authentication failed\"}";

    std::string error = curl_systemcall::http_post("https://gorest.co.in/public/v2/users",
        "", &response_str);
    EXPECT_EQ(error, curl_systemcall::ERROR_OK);
    EXPECT_EQ(response_str, EXPECTED_RESPONSE_STR);
}

} // anonymous namespace



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time ( \
    >     time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
    >     -I"googletest/googletest/include" -I"googletest/googlemock/include" \
    >     -DFMT_ENFORCE_COMPILE_STRING \
    >     curl_systemcall_lib_unittest.cpp \
    >     curl_systemcall_lib.cpp \
    >     systemcall_lib.cpp \
    >     bin/libgtest.a bin/libgtest_main.a \
    >     -o bin/a \
    >     -lfmt \
    >     && time bin/a \
    > )

    real    0m2.104s
    user    0m1.895s
    sys 0m0.161s
    Running main() from googletest/googletest/src/gtest_main.cc
    [==========] Running 1 test from 1 test suite.
    [----------] Global test environment set-up.
    [----------] 1 test from CurlSystemCallTest
    [ RUN      ] CurlSystemCallTest.PostToPublicRestApiServer
      % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                     Dload  Upload   Total   Spent    Left  Speed
    100    35    0    35    0     0     34      0 --:--:--  0:00:01 --:--:--    34
    [       OK ] CurlSystemCallTest.PostToPublicRestApiServer (1038 ms)
    [----------] 1 test from CurlSystemCallTest (1038 ms total)

    [----------] Global test environment tear-down
    [==========] 1 test from 1 test suite ran. (1038 ms total)
    [  PASSED  ] 1 test.

    real    0m1.041s
    user    0m0.023s
    sys 0m0.007s

    real    0m3.145s
    user    0m1.919s
    sys 0m0.168s



*/
