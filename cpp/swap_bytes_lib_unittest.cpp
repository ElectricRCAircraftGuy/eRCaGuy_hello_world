/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Googletest (gtest) unit tests for swap_bytes_lib.h/.cpp.

STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. FIRST, follow the detailed clone and build steps here to clone the googletest repo and manually
# build the necessary *.a static library files for gtest and gmock:
# "eRCaGuy_hello_world/cpp/README.md"

# 2. THEN, build and run this unit test with this command!:
time ( \
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
    -I"googletest/googletest/include" -I"googletest/googlemock/include" \
    swap_bytes_lib_unittest.cpp \
    swap_bytes_lib.cpp \
    bin/libgtest.a bin/libgtest_main.a \
    -o bin/a \
    && time bin/a \
)
```

References:
1. https://github.com/google/googletest
    1. https://github.com/google/googletest/blob/main/docs/reference/assertions.md - for
       `EXPECT_EQ()`, `EXPECT_STREQ()`--for C-strings only, etc.!

*/


// Local includes
#include "swap_bytes_lib.h"

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

/// Ensure that swapping bytes in various data types through the template function works as expected
TEST(SwapBytesTest, SwapBytes)
{
    uint8_t   u8 = 0x12;
    uint16_t u16 = 0x0011;
    uint32_t u32 = 0x00112233;
    uint64_t u64 = 0x0011223344556677;
    uint8_t byte_array[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                              0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

    swap_bytes(&u8);
    swap_bytes(&u16);
    swap_bytes(&u32);
    swap_bytes(&u64);
    swap_bytes(byte_array, sizeof(byte_array));

    EXPECT_EQ(u8,  0x12U); // nothing to swap, so the byte should be the same as before
    EXPECT_EQ(u16, 0x1100U);
    EXPECT_EQ(u32, 0x33221100U);
    EXPECT_EQ(u64, 0x7766554433221100UL);
    uint8_t byte_array_manually_swapped[16] = {
        0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
    };
    EXPECT_EQ(memcmp(byte_array, byte_array_manually_swapped, sizeof(byte_array)), 0);
}

/// Test the endianness functions.
TEST(EndiannessTest, EngiannessGetAndGetName)
{
    endianness_t endianness = endianness_get();

    EXPECT_EQ(endianness, ENDIANNESS_LITTLE_ENDIAN) << "Just update this test if your system's "
        "endianness is different from this. For x86-64, your system should be Little-Endian.";
    EXPECT_STREQ(endianness_get_name(endianness),
        "LITTLE_ENDIAN (least-significant byte first in memory)");
}

} // anonymous namespace



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time (     time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread     -I"googletest/googletest/include" -I"googletest/googlemock/include"     swap_bytes_lib_unittest.cpp     swap_bytes_lib.cpp     bin/libgtest.a bin/libgtest_main.a     -o bin/a     && time bin/a )

    real    0m1.644s
    user    0m1.543s
    sys 0m0.101s
    Running main() from googletest/googletest/src/gtest_main.cc
    [==========] Running 2 tests from 2 test suites.
    [----------] Global test environment set-up.
    [----------] 1 test from SwapBytesTest
    [ RUN      ] SwapBytesTest.SwapBytes
    [       OK ] SwapBytesTest.SwapBytes (0 ms)
    [----------] 1 test from SwapBytesTest (0 ms total)

    [----------] 1 test from EndiannessTest
    [ RUN      ] EndiannessTest.EngiannessGetAndGetName
    [       OK ] EndiannessTest.EngiannessGetAndGetName (0 ms)
    [----------] 1 test from EndiannessTest (0 ms total)

    [----------] Global test environment tear-down
    [==========] 2 tests from 2 test suites ran. (0 ms total)
    [  PASSED  ] 2 tests.

    real    0m0.002s
    user    0m0.002s
    sys 0m0.000s

    real    0m1.647s
    user    0m1.545s
    sys 0m0.101s


*/
