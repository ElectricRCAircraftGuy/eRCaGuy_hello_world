# eRCaGuy_hello_world
"hello world" demos &amp; templates for various languages, incl. gcc build commands for C &amp; C++ 

By Gabriel Staples  
www.ElectricRCAircraftGuy.com

**Status:** C & C++ demos are done and work! 

## For beginners and experts alike: not your average "hello world" examples

Note that these are NOT just your standard "simple" hello world demos for absolute beginners. Rather, they are simple enough for beginners but also contain some advanced techniques and tips & tricks to act as good reminders or teaching for more expert programmers too. I, myself, regularly reference my own examples here to remind myself of some of these details which are easy to forget. There's no sense stressing about trying to remember everything. _Instead of trying to remember everything, just remember where to look (here in this case)_. 

**Examples of more advanced principles taught herein:** 

1. How to generate intermediate build files, including .ii, .s, and .o.
    1. See "cpp/hello_world.cpp"
1. How to make a single file compile in both C and C++ by using the `#ifdef __cplusplus` `extern "C" {` brace trick
    1. See "c/hello_world.c"
1. How to use a forward declaration of `printf` rather than including `stdio.h` to make it link
    1. See "c/hello_world.c"
1. How to do cross-platform sleep in Windows or Linux
    1. See "c/hello_world_sleep.c"
1. A reminder to use `-Wall -Werror` for better code safety and quality
    1. See "c/hello_world.c"
1. How to use `g3` for full debugging info
    1. See "c/hello_world.c" and
    1. "c/hello_world_sleep.c"
1. How to specify the C or C++ version you are compiling for, such as `c90`, `c99`, or `c11` (C 2011), or `c++98`, `c++03` (C++ 2003), or `c++11` (C++ 2011)
    1. See "c/hello_world.c" and
    1. "c/hello_world_sleep.c"
1. How to pass entire functions or curly-brace-scoped `{ }` code blocks, as though they were a single parameter, into a macro to be evaluated
    1. See "advanced_macro_usage_pass_in_entire_func.cpp"
1. How to do integer rounding UP, DOWN, and to NEAREST whole integer during division using 3 different techniques: 1) macros, 2) gcc/clang statement expressions, and 3) C++ function templates. This also is a great unit test example using simple hand-written unit tests.
    1. See "c/rounding_integer_division/" directory
    1. If you'd like to see how to use googletest (gtest) and googlemock (gmock) instead of writing custom unit tests, see my other project here instead: https://github.com/ElectricRCAircraftGuy/eRCaGuy_gtest_practice. It also acts as a good demo of how to get up and running quickly with Google's Bazel build system.

