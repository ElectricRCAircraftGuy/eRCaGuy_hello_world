///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 -DUNIT_TEST -pthread "$0" "stringslib.c" -lgtest -lgtest_main -o "/tmp/test_$(basename "$0")" && "/tmp/test_$(basename "$0")" "$@"; exit
// For the line just above, see: 
// 1. My answer here: https://stackoverflow.com/a/75491834/4561887
// 2. https://stackoverflow.com/a/61709728/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
July 2024

Googletest (gtest) unit tests for stringslib.h/.c.

STATUS: done & works!

To compile and run (assuming you've already `cd`ed into this dir):

1. First, install Gtest by following my instructions here: 
   https://stackoverflow.com/a/75719098/4561887

2. Then, run this file as a Bash script:
    ```bash
    cd path/to/this/dir
    ./stringslib_unittest.cpp
    ```
*/


// Local includes
#include "stringslib.h"

// 3rd-party library includes
// #include "gmock/gmock.h"
#include "gtest/gtest.h"

// Linux includes
#include <strings.h> // for `strcasecmp()`, `strncasecmp()`

// C and C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <limits.h> // for `INT_MIN`
#include <string.h> // for `strncmp()`


// anonymous namespace
namespace
{

TEST(stringslib, strncasecmp)
{
    // Copied and modified from strncmpci.c:
    // https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/strncmpci.c

    const char * str1;
    const char * str2;
    size_t n;

    // NULL ptr checks
    EXPECT_EQ(my_strncasecmp(NULL, "", 0), INT_MIN);
    EXPECT_EQ(my_strncasecmp("", NULL, 0), INT_MIN);
    EXPECT_EQ(my_strncasecmp(NULL, NULL, 0), INT_MIN);
    EXPECT_EQ(my_strncasecmp(NULL, "", 10), INT_MIN);
    EXPECT_EQ(my_strncasecmp("", NULL, 10), INT_MIN);
    EXPECT_EQ(my_strncasecmp(NULL, NULL, 10), INT_MIN);

    EXPECT_EQ(my_strncasecmp("", "", 0), 0);
    EXPECT_EQ(my_strncasecmp("", "", 0), strncasecmp("", "", 0));
    EXPECT_EQ(strncmp("", "", 0), 0);

    str1 = "";
    str2 = "";
    n = 0;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), 0);
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 0);

    str1 = "hey";
    str2 = "HEY";
    n = 0;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), 0);
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 0);

    str1 = "hey";
    str2 = "HEY";
    n = 3;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), 0);
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 'h' - 'H');

    str1 = "heY";
    str2 = "HeY";
    n = 3;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), 0);
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 'h' - 'H');

    str1 = "hey";
    str2 = "HEdY";
    n = 3;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), 'y' - 'd');
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 'h' - 'H');

    str1 = "heY";
    str2 = "hEYd";
    n = 3;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), 0);
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 'e' - 'E');

    str1 = "heY";
    str2 = "heyd";
    n = 6;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), -'d');
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 'Y' - 'y');

    str1 = "hey";
    str2 = "hey";
    n = 6;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), 0);
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 0);

    str1 = "hey";
    str2 = "heyd";
    n = 6;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), -'d');
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), -'d');

    str1 = "hey";
    str2 = "heyd";
    n = 3;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), 0);
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 0);

    str1 = "hEY";
    str2 = "heyYOU";
    n = 3;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), 0);
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 'E' - 'e');

    str1 = "hEY";
    str2 = "heyYOU";
    n = 10;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), -'y');
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 'E' - 'e');

    str1 = "hEYHowAre";
    str2 = "heyYOU";
    n = 10;
    EXPECT_EQ(my_strncasecmp(str1, str2, n), 'h' - 'y');
    EXPECT_EQ(my_strncasecmp(str1, str2, n), strncasecmp(str1, str2, n));
    EXPECT_EQ(strncmp(str1, str2, n), 'E' - 'e');

    EXPECT_EQ(my_strncasecmp("nice to meet you.,;", "NICE TO MEET YOU.,;", 100), 0);
    EXPECT_EQ(strncasecmp(   "nice to meet you.,;", "NICE TO MEET YOU.,;", 100), 0);
    EXPECT_EQ(strncmp(  "nice to meet you.,;", "NICE TO MEET YOU.,;", 100), 'n' - 'N');
    EXPECT_EQ(strncmp(  "nice to meet you.,;", "nice to meet you.,;", 100), 0);

    EXPECT_EQ(my_strncasecmp("nice to meet you.,;", "NICE TO UEET YOU.,;", 100), 'm' - 'u');
    EXPECT_EQ(strncasecmp(   "nice to meet you.,;", "NICE TO UEET YOU.,;", 100), 'm' - 'u');
    EXPECT_EQ(strncmp(  "nice to meet you.,;", "nice to uEET YOU.,;", 100), 'm' - 'u');
    EXPECT_EQ(strncmp(  "nice to meet you.,;", "nice to UEET YOU.,;", 100), 'm' - 'U');

    EXPECT_EQ(my_strncasecmp("nice to meet you.,;", "NICE TO MEET YOU.,;", 5), 0);
    EXPECT_EQ(strncasecmp(   "nice to meet you.,;", "NICE TO MEET YOU.,;", 5), 0);
    EXPECT_EQ(strncmp(  "nice to meet you.,;", "NICE TO MEET YOU.,;", 5), 'n' - 'N');

    EXPECT_EQ(my_strncasecmp("nice to meet you.,;", "NICE eo UEET YOU.,;", 5), 0);
    EXPECT_EQ(strncasecmp(   "nice to meet you.,;", "NICE eo UEET YOU.,;", 5), 0);
    EXPECT_EQ(strncmp(  "nice to meet you.,;", "nice eo uEET YOU.,;", 5), 0);

    EXPECT_EQ(my_strncasecmp("nice to meet you.,;", "NICE eo UEET YOU.,;", 100), 't' - 'e');
    EXPECT_EQ(strncasecmp(   "nice to meet you.,;", "NICE eo UEET YOU.,;", 100), 't' - 'e');
    EXPECT_EQ(strncmp(  "nice to meet you.,;", "nice eo uEET YOU.,;", 100), 't' - 'e');

    EXPECT_EQ(my_strncasecmp("nice to meet you.,;", "nice-eo UEET YOU.,;", 5), ' ' - '-');
    EXPECT_EQ(strncasecmp   ("nice to meet you.,;", "nice-eo UEET YOU.,;", 5), ' ' - '-');
    EXPECT_EQ(strncmp(  "nice to meet you.,;", "nice-eo UEET YOU.,;", 5), ' ' - '-');
}

TEST(stringslib, strcasecmp)
{
    const char * str1;
    const char * str2;

    EXPECT_EQ(my_strcasecmp(NULL, ""), INT_MIN);
    EXPECT_EQ(my_strcasecmp("", NULL), INT_MIN);
    EXPECT_EQ(my_strcasecmp(NULL, NULL), INT_MIN);
    EXPECT_EQ(my_strcasecmp(NULL, ""), INT_MIN);
    EXPECT_EQ(my_strcasecmp("", NULL), INT_MIN);
    EXPECT_EQ(my_strcasecmp(NULL, NULL), INT_MIN);

    EXPECT_EQ(my_strcasecmp("", ""), 0);
    EXPECT_EQ(my_strcasecmp("", ""), strcasecmp("", ""));
    EXPECT_EQ(strcmp("", ""), 0);

    str1 = "";
    str2 = "";
    EXPECT_EQ(my_strcasecmp(str1, str2), 0);
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), 0);

    str1 = "hey";
    str2 = "HEY";
    EXPECT_EQ(my_strcasecmp(str1, str2), 0);
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), 'h' - 'H' > 0 ? 1 : -1);

    str1 = "heY";
    str2 = "HeY";
    EXPECT_EQ(my_strcasecmp(str1, str2), 0);
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), 'h' - 'H' > 0 ? 1 : -1);

    str1 = "hey";
    str2 = "HEdY";
    EXPECT_EQ(my_strcasecmp(str1, str2), 'y' - 'd');
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), 'h' - 'H' > 0 ? 1 : -1);

    str1 = "heY";
    str2 = "hEYd";
    EXPECT_EQ(my_strcasecmp(str1, str2), -'d');
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), 'e' - 'E' > 0 ? 1 : -1);

    str1 = "heY";
    str2 = "heyd";
    EXPECT_EQ(my_strcasecmp(str1, str2), -'d');
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), 'Y' - 'y' > 0 ? 1 : -1);

    str1 = "hey";
    str2 = "hey";
    EXPECT_EQ(my_strcasecmp(str1, str2), 0);
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), 0);

    str1 = "hey";
    str2 = "heyd";
    EXPECT_EQ(my_strcasecmp(str1, str2), -'d');
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), -'d' > 0 ? 1 : -1);

    str1 = "hey";
    str2 = "heyd";
    EXPECT_EQ(my_strcasecmp(str1, str2), -'d');
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), -'d' > 0 ? 1 : -1);

    str1 = "hEY";
    str2 = "heyYOU";
    EXPECT_EQ(my_strcasecmp(str1, str2), -'y');
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), 'E' - 'e' > 0 ? 1 : -1);

    str1 = "hEY";
    str2 = "heyyOU";
    EXPECT_EQ(my_strcasecmp(str1, str2), -'y');
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), 'E' - 'e' > 0 ? 1 : -1);

    str1 = "hEYHowAre";
    str2 = "heyYOU";
    EXPECT_EQ(my_strcasecmp(str1, str2), 'h' - 'y');
    EXPECT_EQ(my_strcasecmp(str1, str2), strcasecmp(str1, str2));
    EXPECT_EQ(strcmp(str1, str2), 'E' - 'e' > 0 ? 1 : -1);

    EXPECT_EQ(my_strcasecmp("nice to meet you.,;", "NICE TO MEET YOU.,;"), 0);
    EXPECT_EQ(strcasecmp(   "nice to meet you.,;", "NICE TO MEET YOU.,;"), 0);
    EXPECT_EQ(strcmp(  "nice to meet you.,;", "NICE TO MEET YOU.,;"), 'n' - 'N' > 0 ? 1 : -1);
    EXPECT_EQ(strcmp(  "nice to meet you.,;", "nice to meet you.,;"), 0);

    EXPECT_EQ(my_strcasecmp("nice to meet you.,;", "NICE TO UEET YOU.,;"), 'm' - 'u');
    EXPECT_EQ(strcasecmp(   "nice to meet you.,;", "NICE TO UEET YOU.,;"), 'm' - 'u');
    EXPECT_EQ(strcmp(  "nice to meet you.,;", "nice to uEET YOU.,;"), 'm' - 'u' > 0 ? 1 : -1);
    EXPECT_EQ(strcmp(  "nice to meet you.,;", "nice to UEET YOU.,;"), 'm' - 'U' > 0 ? 1 : -1);

    EXPECT_EQ(my_strcasecmp("nice to meet you.,;", "NICE TO MEET YOU.,;"), 0);
    EXPECT_EQ(strcasecmp(   "nice to meet you.,;", "NICE TO MEET YOU.,;"), 0);
    EXPECT_EQ(strcmp(  "nice to meet you.,;", "NICE TO MEET YOU.,;"), 'n' - 'N' > 0 ? 1 : -1);

    EXPECT_EQ(my_strcasecmp("nice to meet you.,;", "NICE eo UEET YOU.,;"), 't' - 'e');
    EXPECT_EQ(strcasecmp(   "nice to meet you.,;", "NICE eo UEET YOU.,;"), 't' - 'e');
    EXPECT_EQ(strcmp(  "nice to meet you.,;", "nice eo uEET YOU.,;"), 't' - 'e' > 0 ? 1 : -1);

    EXPECT_EQ(my_strcasecmp("nice to meet you.,;", "nice-eo UEET YOU.,;"), ' ' - '-');
    EXPECT_EQ(strcasecmp   ("nice to meet you.,;", "nice-eo UEET YOU.,;"), ' ' - '-');
    EXPECT_EQ(strcmp(  "nice to meet you.,;", "nice-eo UEET YOU.,;"), ' ' - '-' > 0 ? 1 : -1);
}

} // anonymous namespace



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/c$ ./stringslib_unittest.cpp 
    Running main() from /home/gabrielstaples/Downloads/Install_Files-p/gtest/googletest-1.14.0/googletest/src/gtest_main.cc
    [==========] Running 2 tests from 1 test suite.
    [----------] Global test environment set-up.
    [----------] 2 tests from stringslib
    [ RUN      ] stringslib.strncasecmp
    [       OK ] stringslib.strncasecmp (0 ms)
    [ RUN      ] stringslib.strcasecmp
    [       OK ] stringslib.strcasecmp (0 ms)
    [----------] 2 tests from stringslib (0 ms total)

    [----------] Global test environment tear-down
    [==========] 2 tests from 1 test suite ran. (0 ms total)
    [  PASSED  ] 2 tests.


*/
