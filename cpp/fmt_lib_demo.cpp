/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
3 May 2022

Learn how to set up, build/link-to, and use the `fmt` library
(https://github.com/fmtlib/fmt/issues/2157), _including_ enforcing static, compile-time checks of
all format strings so I don't get exceptions thrown during critical error prints at run-time!

STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
[see the "BEST" option below for my final answer for this code]
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
# With `-DFMT_HEADER_ONLY` in it:
# time g++ -Wall -Wextra -Werror -O3 -std=c++17 -DFMT_HEADER_ONLY fmt_lib_demo.cpp ../c/timinglib.c -o bin/a && bin/a

# Use this one since I have defined the macros manually below, just above `#include <fmt/format.h>`;
# has `-lfmt`:
time g++ -Wall -Wextra -Werror -O3 -std=c++17 fmt_lib_demo.cpp ../c/timinglib.c -o bin/a -lfmt && bin/a

# OR: has "/usr/local/lib/libfmt.a":
time g++ -Wall -Wextra -Werror -O3 -std=c++17 fmt_lib_demo.cpp ../c/timinglib.c "/usr/local/lib/libfmt.a" -o bin/a && bin/a

# **BEST:** with `-lfmt` AND `-DFMT_ENFORCE_COMPILE_STRING` in it to enforce static, compile-time format
# string checking. See:
# 1. *****+ [my notes] https://github.com/fmtlib/fmt/issues/2157#issuecomment-1117930229
# 1. ***** https://fmt.dev/latest/api.html#compile-time-format-string-checks
# 1. https://fmt.dev/latest/usage.html
#
# 1st: FIRST, follow the fmt library setup and installation instructions here:
# "eRCaGuy_hello_world/cpp/README.md"
# 2nd: THEN, run this build & run command:
time g++ -Wall -Wextra -Werror -O3 -std=c++17 -DFMT_ENFORCE_COMPILE_STRING fmt_lib_demo.cpp ../c/timinglib.c -o bin/a -lfmt && bin/a
```

References:
1. https://github.com/fmtlib/fmt
1. https://fmt.dev/latest/usage.html#building-the-library
1. *****+ https://fmt.dev/latest/api.html - full API reference and description of the
   various header files!
1. *****+ my own build and run notes:
   https://github.com/fmtlib/fmt/issues/2157#issuecomment-1117930229


*/



// Local includes
#include "../c/timinglib.h"


// 3rd-party library includes

// This macro FORCES you to use `FMT_STRING()` everywhere for static, compile-time format string
// checks! See: https://fmt.dev/latest/api.html#compile-time-format-string-checks
// If you don't, you'll see this compile-time error:
//
//      /usr/local/include/fmt/core.h:587:17: error: static assertion failed: FMT_ENFORCE_COMPILE_STRING requires all format strings to use FMT_STRING.
//
// If you use this macro, do NOT also define `FMT_HEADER_ONLY`! Instead, build g++ also with the
// `-lfmt` library option to pull in the .a static library file from "/usr/local/lib/libfmt.a".
// #define FMT_ENFORCE_COMPILE_STRING

// This define is _required_ for the `fmt` library! See:
// 1. https://github.com/fmtlib/fmt/issues/2157#issuecomment-805529473
// 1. The last bullet in the "Features" section of the main readme:
//    https://github.com/fmtlib/fmt#features
//    > Optional header-only configuration enabled with the `FMT_HEADER_ONLY` macro
// #define FMT_HEADER_ONLY  // <-- even better, define this in the g++ build cmd!

#include <fmt/format.h>  // This include is OK now that I have fully installed the `fmt` library
                         // with `sudo make install`, I believe.
// #include "fmt/include/fmt/format.h"


// Linux includes
// NA

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    uint64_t time_ns_1 = nanos();
    uint64_t time_ns_2 = nanos();
    uint64_t time_ns_3 = nanos();

    // -----------------
    // Printf
    // -----------------

    printf("Timestamps:\n"
           "  time_ns_1 = %20.9f\n"
           "  time_ns_2 = %20.9f\n"
           "  time_ns_3 = %20.9f\n",
           NS_TO_SEC((double)time_ns_1),
           NS_TO_SEC((double)time_ns_2),
           NS_TO_SEC((double)time_ns_3));

    // -----------------
    // `fmt` library
    // -----------------

#ifndef FMT_ENFORCE_COMPILE_STRING  // compile-time checks are NOT enforced, so you'll get really
                                    // irritating **run-time** C++ exceptions thrown instead, if
                                    // format strings are wrong

    // fmt-string style; stored into C++ `std::string` first
    std::string timestamps_str = fmt::format(
            "Timestamps:\n"
            "  time_ns_1 = {:20.9f}\n"
            "  time_ns_2 = {:20.9f}\n"
            "  time_ns_3 = {:20.9f}\n",
            NS_TO_SEC((double)time_ns_1),
            NS_TO_SEC((double)time_ns_2),
            NS_TO_SEC((double)time_ns_3));
    std::cout << timestamps_str;

    // OR, print directly; see: https://fmt.dev/latest/api.html
    fmt::print(
            "Timestamps:\n"
            "  time_ns_1 = {:20.9f}\n"
            "  time_ns_2 = {:20.9f}\n"
            "  time_ns_3 = {:20.9f}\n",
            NS_TO_SEC((double)time_ns_1),
            NS_TO_SEC((double)time_ns_2),
            NS_TO_SEC((double)time_ns_3));

    // This is an invalid format string and produces a **run-time** error and throws a C++
    // exception!:
    //
    //      terminate called after throwing an instance of 'fmt::v8::format_error'
    //        what():  invalid format string
    //      Aborted (core dumped)
    //
    fmt::print("\n"
            "time_ns_1 = {20.9f}\n",
            NS_TO_SEC((double)time_ns_1));

#else  // `FMT_ENFORCE_COMPILE_STRING` **is** defined, so we MUST use the `FMT_STRING()` macro
       // to enforce static compile-time checks of the format string!

    // fmt-string style; stored into C++ `std::string` first
    std::string timestamps_str = fmt::format(FMT_STRING(
            "Timestamps:\n"
            "  time_ns_1 = {:20.9f}\n"
            "  time_ns_2 = {:20.9f}\n"
            "  time_ns_3 = {:20.9f}\n"),
            NS_TO_SEC((double)time_ns_1),
            NS_TO_SEC((double)time_ns_2),
            NS_TO_SEC((double)time_ns_3));
    std::cout << timestamps_str;

    // OR, print directly; see: https://fmt.dev/latest/api.html
    fmt::print(FMT_STRING(
            "Timestamps:\n"
            "  time_ns_1 = {:20.9f}\n"
            "  time_ns_2 = {:20.9f}\n"
            "  time_ns_3 = {:20.9f}\n"),
            NS_TO_SEC((double)time_ns_1),
            NS_TO_SEC((double)time_ns_2),
            NS_TO_SEC((double)time_ns_3));

    fmt::print(FMT_STRING("\n"
            "  time_ns_1 = {:20.9f}\n"), // <=== I corrected this to pass static, compile-time checks
            NS_TO_SEC((double)time_ns_1));

#endif

    // To make it a static **compile-time** error instead, use the `FMT_STRING()` macro, like this!
    // The static compile-time error becomes **really** long and cryptic, however. Here is what it
    // looks like. The line which states **`fmt_lib_demo.cpp:142:41:   required from here`** is
    // what actually indicates the erroneous line. I have marked it with `<========` below:
    //
    //      eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 -DFMT_HEADER_ONLY fmt_lib_demo.cpp ../c/timinglib.c -o bin/a && bin/a
    //      In file included from /usr/local/include/fmt/format.h:48,
    //                       from fmt_lib_demo.cpp:38:
    //      /usr/local/include/fmt/core.h: In instantiation of ‘void fmt::v8::detail::check_format_string(S) [with <template-parameter-1-1> = {double}; S = main()::<lambda()>::FMT_COMPILE_STRING; typename std::enable_if<fmt::v8::is_compile_string<S>::value, int>::type <anonymous> = 0]’:
    //      /usr/local/include/fmt/core.h:3120:41:   required from ‘fmt::v8::basic_format_string<Char, Args>::basic_format_string(const S&) [with S = main()::<lambda()>::FMT_COMPILE_STRING; typename std::enable_if<std::is_convertible<const S&, fmt::v8::basic_string_view<Char> >::value, int>::type <anonymous> = 0; Char = char; Args = {double}]’
    //      fmt_lib_demo.cpp:142:41:   required from here  <========:
    //      /usr/local/include/fmt/core.h:2975:33:   in ‘constexpr’ expansion of ‘fmt::v8::detail::parse_format_string<true, char, fmt::v8::detail::format_string_checker<char, fmt::v8::detail::error_handler, double> >(s, fmt::v8::detail::format_string_checker<char, fmt::v8::detail::error_handler, double>(s, (fmt::v8::detail::error_handler(), fmt::v8::detail::error_handler())))’
    //      /usr/local/include/fmt/core.h:2642:44:   in ‘constexpr’ expansion of ‘fmt::v8::detail::parse_replacement_field<char, fmt::v8::detail::format_string_checker<char, fmt::v8::detail::error_handler, double>&>((p + 18446744073709551615), end, ((fmt::v8::detail::format_string_checker<char, fmt::v8::detail::error_handler, double>&)handler))’
    //      /usr/local/include/fmt/core.h:2612:25:   in ‘constexpr’ expansion of ‘fmt::v8::detail::parse_arg_id<char, fmt::v8::detail::parse_replacement_field(const Char*, const Char*, Handler&&) [with Char = char; Handler = fmt::v8::detail::format_string_checker<char, fmt::v8::detail::error_handler, double>&]::id_adapter&>(begin, end, adapter)’
    //      /usr/local/include/fmt/core.h:2391:51:   in ‘constexpr’ expansion of ‘fmt::v8::detail::do_parse_arg_id<char, fmt::v8::detail::parse_replacement_field(const Char*, const Char*, Handler&&) [with Char = char; Handler = fmt::v8::detail::format_string_checker<char, fmt::v8::detail::error_handler, double>&]::id_adapter&>(begin, end, handler)’
    //      /usr/local/include/fmt/core.h:2370:7:   in ‘constexpr’ expansion of ‘(& handler)->fmt::v8::detail::parse_replacement_field(const Char*, const Char*, Handler&&) [with Char = char; Handler = fmt::v8::detail::format_string_checker<char, fmt::v8::detail::error_handler, double>&]::id_adapter::on_error(((const char*)"invalid format string"))’
    //      /usr/local/include/fmt/core.h:2600:20:   in ‘constexpr’ expansion of ‘(&((fmt::v8::detail::parse_replacement_field(const Char*, const Char*, Handler&&) [with Char = char; Handler = fmt::v8::detail::format_string_checker<char, fmt::v8::detail::error_handler, double>&]::id_adapter*)this)->fmt::v8::detail::parse_replacement_field(const Char*, const Char*, Handler&&) [with Char = char; Handler = fmt::v8::detail::format_string_checker<char, fmt::v8::detail::error_handler, double>&]::id_adapter::handler)->fmt::v8::detail::format_string_checker<char, fmt::v8::detail::error_handler, double>::on_error(message)’
    //      /usr/local/include/fmt/core.h:2964:5: error: ‘constexpr void fmt::v8::basic_format_parse_context<Char, ErrorHandler>::on_error(const char*) [with Char = char; ErrorHandler = fmt::v8::detail::error_handler]’ called in a constant expression
    //           context_.on_error(message);
    //           ^~~~~~~~
    //      /usr/local/include/fmt/core.h:674:22: note: ‘constexpr void fmt::v8::basic_format_parse_context<Char, ErrorHandler>::on_error(const char*) [with Char = char; ErrorHandler = fmt::v8::detail::error_handler]’ is not usable as a ‘constexpr’ function because:
    //         FMT_CONSTEXPR void on_error(const char* message) {
    //                            ^~~~~~~~
    //      /usr/local/include/fmt/core.h:675:27: error: call to non-‘constexpr’ function ‘void fmt::v8::detail::error_handler::on_error(const char*)’
    //           ErrorHandler::on_error(message);
    //           ~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~
    //

    // Uncomment these few lines to see the static, compile-time error:
    // fmt::print(FMT_STRING("\n"
    //         "time_ns_1 = {20.9f}\n"),
    //         NS_TO_SEC((double)time_ns_1));


    return 0;
}



/*
SAMPLE OUTPUT:

If you have NOT yet built and installed the `fmt` library to your system, you'll
see this `undefined reference to `fmt::v8::vformat` error!: UPDATE: actually,
it *could* be because I forgot `#include <string>`, OR it could be because I
forgot `#define FMT_HEADER_ONLY` before `#include <fmt/format.h>`. Honestly,
I'm not sure if it was because I added those things OR because I built and
installed the library with `sudo make install` that caused it to now work!
BROKEN OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 fmt_lib_demo.cpp ../c/timinglib.c -o bin/a && bin/a
    /tmp/ccbmysAm.o: In function `main':
    fmt_lib_demo.cpp:(.text.startup+0x113): undefined reference to `fmt::v8::vformat[abi:cxx11](fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<fmt::v8::appender, char> >)'
    collect2: error: ld returned 1 exit status


WORKING OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 fmt_lib_demo.cpp ../c/timinglib.c -o bin/a && bin/a

    real    0m2.908s
    user    0m2.499s
    sys 0m0.187s
    Hello world!

    Timestamps:
      time_ns_1 =     660748.510879601
      time_ns_2 =     660748.510879753
      time_ns_3 =     660748.510879833
    Timestamps:
      time_ns_1 =     660748.510879601
      time_ns_2 =     660748.510879753
      time_ns_3 =     660748.510879833


FINAL OUTPUT in present-state and with the build command labelled "BEST" above:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 -DFMT_ENFORCE_COMPILE_STRING fmt_lib_demo.cpp ../c/timinglib.c -o bin/a -lfmt && bin/a

    real    0m0.700s
    user    0m0.623s
    sys 0m0.076s
    Hello world!

    Timestamps:
      time_ns_1 =     708856.723843497
      time_ns_2 =     708856.723843599
      time_ns_3 =     708856.723843641
    Timestamps:
      time_ns_1 =     708856.723843497
      time_ns_2 =     708856.723843599
      time_ns_3 =     708856.723843641
    Timestamps:
      time_ns_1 =     708856.723843497
      time_ns_2 =     708856.723843599
      time_ns_3 =     708856.723843641

      time_ns_1 =     708856.723843497


*/
