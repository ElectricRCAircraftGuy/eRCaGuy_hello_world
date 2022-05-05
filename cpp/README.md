This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Table of Contents
<details>
<summary><b>(click to expand)</b></summary>
<!-- MarkdownTOC -->

1. [Googletest setup: how to build googletest \(gtest and gmock\) with the gcc/g++ compiler](#googletest-setup-how-to-build-googletest-gtest-and-gmock-with-the-gccg-compiler)
    1. [References:](#references)
    1. [First, clone the googletest source code and symlink it into your repo](#first-clone-the-googletest-source-code-and-symlink-it-into-your-repo)
    1. [Build all of gtest and gmock as static library archive `*.a` files](#build-all-of-gtest-and-gmock-as-static-library-archive-a-files)
        1. [Option 1 \[recommended/my preference\]: _manually_ build the `*.a` static library files with g++:](#option-1-recommendedmy-preference-manually-build-the-a-static-library-files-with-g)
        1. [Option 2: build with the Cmake files which come with the source code](#option-2-build-with-the-cmake-files-which-come-with-the-source-code)
    1. [Build your unit tests using gtest and/or gmock](#build-your-unit-tests-using-gtest-andor-gmock)
        1. [Option 1 \[my preference/recommended!\] build your unit test using the pre-built `*.a` static library files from above:](#option-1-my-preferencerecommended-build-your-unit-test-using-the-pre-built-a-static-library-files-from-above)
        1. [Option 2: rebuild your unit test _and_ the entire gtest/gmock library all at once](#option-2-rebuild-your-unit-test-and-the-entire-gtestgmock-library-all-at-once)
        1. [More examples just to show building and running the samples which come with googletest](#more-examples-just-to-show-building-and-running-the-samples-which-come-with-googletest)
1. [`fmt` library installation & setup](#fmt-library-installation--setup)
    1. [References:](#references-1)
    1. [1. Build & install the `fmt` library](#1-build--install-the-fmt-library)
    1. [2. How to use and link against the `fmt` library in your own code](#2-how-to-use-and-link-against-the-fmt-library-in-your-own-code)
1. [`curl` library installation & setup](#curl-library-installation--setup)
    1. [References:](#references-2)
    1. [1. Build & install the `curl` library](#1-build--install-the-curl-library)
    1. [2. How to use and link against the `curl` library in your own code](#2-how-to-use-and-link-against-the-curl-library-in-your-own-code)

<!-- /MarkdownTOC -->
</details>


<a id="googletest-setup-how-to-build-googletest-gtest-and-gmock-with-the-gccg-compiler"></a>
# Googletest setup: how to build googletest (gtest and gmock) with the gcc/g++ compiler


<a id="references"></a>
## References: 
1. https://github.com/google/googletest
    1. https://github.com/google/googletest/tree/main/googletest
1. \*\*\*\*\*+ https://ethz-adrl.github.io/ct/ct_core/doc/html/md__home_adrl_code_src_control-toolbox_ct_core_build_test_googletest-src_googletest_README.html - this is the main source for all of the examples below because it is the _only_ source I could find which showed me how to use g++ to build googletest from scratch. It is where I learned how to build `gtest` and the associated static library files (including the `libgtest.a` and `libgtest_main.a` static library .a archive files, for instance) with g++. 
1. I have now posted some of these instructions below here on Stack Overflow as well: [How do I build and use googletest (gtest) and googlemock (gmock) with gcc/g++ or clang?](https://stackoverflow.com/a/72108315/4561887)


<a id="first-clone-the-googletest-source-code-and-symlink-it-into-your-repo"></a>
## First, clone the googletest source code and symlink it into your repo

_These steps are required before any of the build options below will work._

```bash
# cd into your repo of interest (for me: `eRCaGuy_hello_world`)
cd path/to/eRCaGuy_hello_world
# go up one level to be at the same level as `eRCaGuy_hello_world`
cd ..

# clone the googletest repo
time git clone https://github.com/google/googletest.git
# you now have the folder "googletest" at the same level as "eRCaGuy_hello_world"; ex:
#   some/dir/eRCaGuy_hello_world
#   some/dir/googletest

# cd into the folder where you want the symlink to googletest be located
cd eRCaGuy_hello_world/cpp
# create a relative symlink to googletest here
ln -si ../../googletest .
# You now have the symlink dir "eRCaGuy_hello_world/cpp/googletest", which contains the full 
# "googletest" repo source code
```


<a id="build-all-of-gtest-and-gmock-as-static-library-archive-a-files"></a>
## Build all of gtest and gmock as static library archive `*.a` files

See: https://ethz-adrl.github.io/ct/ct_core/doc/html/md__home_adrl_code_src_control-toolbox_ct_core_build_test_googletest-src_googletest_README.html

Note: to build *all* of the `gtest` and `gmock` library files, all you need to build are the following. The next steps show how to do that.
```bash
# Files to build for gtest and gmock

# gtest
googletest/googletest/src/gtest-all.cc
googletest/googletest/src/gtest_main.cc
# gmock
googletest/googlemock/src/gmock-all.cc
googletest/googlemock/src/gmock_main.cc
```

<a id="option-1-recommendedmy-preference-manually-build-the-a-static-library-files-with-g"></a>
### Option 1 [recommended/my preference]: _manually_ build the `*.a` static library files with g++:

Be sure to build (just below) the object files with the same exact build options you plan to use for your unit tests. If you use different build options for your unit tests, you may also need to rebuild gtest and gmock.

```bash
cd path/to/eRCaGuy_hello_world/cpp

# [takes ~15 sec] build the 4 gtest and gmock *.o object files; note that `-c` means: "Compile or
# assemble the source files, but do not link."; optionally add `--verbose` for verbose output
time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread -c \
    -I"googletest/googletest/include" -I"googletest/googletest" \
    -I"googletest/googlemock/include" -I"googletest/googlemock" \
    googletest/googletest/src/gtest-all.cc googletest/googletest/src/gtest_main.cc \
    googletest/googlemock/src/gmock-all.cc googletest/googlemock/src/gmock_main.cc

# move all of the object files just created to the "bin" dir
mv -t bin gtest-all.o gtest_main.o gmock-all.o gmock_main.o

# Use the `ar` "archive" utility to create the *.a static library archive files from the 4 object
# files above
time ar -rv bin/libgtest.a bin/gtest-all.o
time ar -rv bin/libgtest_main.a bin/gtest_main.o
time ar -rv bin/libgmock.a bin/gmock-all.o
time ar -rv bin/libgmock_main.a bin/gmock_main.o
```

You now have:
```bash
bin/libgtest.a
bin/libgtest_main.a
bin/libgmock.a
bin/libgmock_main.a
```

<a id="option-2-build-with-the-cmake-files-which-come-with-the-source-code"></a>
### Option 2: build with the Cmake files which come with the source code

Source: https://github.com/google/googletest/tree/main/googletest#generic-build-instructions 

```bash
time git clone https://github.com/google/googletest.git
cd googletest        # Main directory of the cloned repository.
mkdir build          # Create a directory to hold the build output.
cd build
time cmake ..        # Generate native make build scripts for GoogleTest.

time make            # Run those makefiles just autogenerated by cmake above.
```

You'll now have the following 4 library files built with whatever build settings were pre-specified for you in the cmake files:

```bash
googletest/build/lib/libgmock.a
googletest/build/lib/libgmock_main.a
googletest/build/lib/libgtest.a
googletest/build/lib/libgtest_main.a
```

To more-fully control the build settings, I therefore recommend you just use the _manual_ g++ build steps above, instead.

**Sample output from the steps above:**

1. Sample output from `time cmake`:
    ```bash
    eRCaGuy_hello_world/cpp/googletest/build$ time cmake ..
    -- The C compiler identification is GNU 8.4.0
    -- The CXX compiler identification is GNU 8.4.0
    -- Check for working C compiler: /usr/bin/cc
    -- Check for working C compiler: /usr/bin/cc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Found PythonInterp: /usr/bin/python (found version "2.7.17") 
    -- Looking for pthread.h
    -- Looking for pthread.h - found
    -- Looking for pthread_create
    -- Looking for pthread_create - not found
    -- Looking for pthread_create in pthreads
    -- Looking for pthread_create in pthreads - not found
    -- Looking for pthread_create in pthread
    -- Looking for pthread_create in pthread - found
    -- Found Threads: TRUE  
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /home/gabriel/GS/dev/eRCaGuy_hello_world/cpp/googletest/build

    real    0m1.202s
    user    0m0.879s
    sys 0m0.245s
    ```
1. Sample output from `time make`:
    ```bash
    eRCaGuy_hello_world/cpp/googletest/build$ time make
    Scanning dependencies of target gtest
    [ 12%] Building CXX object googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
    [ 25%] Linking CXX static library ../lib/libgtest.a
    [ 25%] Built target gtest
    Scanning dependencies of target gmock
    [ 37%] Building CXX object googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
    [ 50%] Linking CXX static library ../lib/libgmock.a
    [ 50%] Built target gmock
    Scanning dependencies of target gmock_main
    [ 62%] Building CXX object googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
    [ 75%] Linking CXX static library ../lib/libgmock_main.a
    [ 75%] Built target gmock_main
    Scanning dependencies of target gtest_main
    [ 87%] Building CXX object googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
    [100%] Linking CXX static library ../lib/libgtest_main.a
    [100%] Built target gtest_main

    real    0m5.482s
    user    0m5.125s
    sys 0m0.346s
    ```


<a id="build-your-unit-tests-using-gtest-andor-gmock"></a>
## Build your unit tests using gtest and/or gmock

<a id="option-1-my-preferencerecommended-build-your-unit-test-using-the-pre-built-a-static-library-files-from-above"></a>
### Option 1 [my preference/recommended!] build your unit test using the pre-built `*.a` static library files from above:

This is the easiest technique in my opinion, and it also builds the _fastest_ since it is using prebuilt static library `*.a` files rather than rebuilding gtest and gmock from scratch.

I learned this technique here: https://ethz-adrl.github.io/ct/ct_core/doc/html/md__home_adrl_code_src_control-toolbox_ct_core_build_test_googletest-src_googletest_README.html

```bash
cd path/to/eRCaGuy_hello_world/cpp

# [takes ~2 sec] build & run your unit tests
# Optionally add `--verbose` for verbose output.
#
# Notes:
# 1. Include whatever libraries you want; add "bin/libgmock.a" too, if gmock is needed.
# 1. Remove "bin/libgtest_main.a" if you'd like to write your own `main()` function!
# 1. NB: If you use different build options here than you used to build the *.a static libraries 
#    above, you may need to rebuild the *.a files above with those new options.
time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
    -I"googletest/googletest/include" -I"googletest/googlemock/include" \
    gtest_demo__sample1_factorial_and_is_prime_unittest.cc \
    gtest_demo__sample1_factorial_and_is_prime.cc \
    bin/libgtest.a bin/libgtest_main.a \
    -o bin/a && time bin/a
```

I like to wrap it up in an outer `time` call too, however, to time the duration of the entire thing. See my answer here for details on the `time` cmd: https://unix.stackexchange.com/a/699728/114401:

```bash
# MY FAVORITE COMMAND/TECHNIQUE <===========
time ( \
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
    -I"googletest/googletest/include" -I"googletest/googlemock/include" \
    gtest_demo__sample1_factorial_and_is_prime_unittest.cc \
    gtest_demo__sample1_factorial_and_is_prime.cc \
    bin/libgtest.a bin/libgtest_main.a \
    -o bin/a \
    && time bin/a \
)
```

<a id="option-2-rebuild-your-unit-test-and-the-entire-gtestgmock-library-all-at-once"></a>
### Option 2: rebuild your unit test _and_ the entire gtest/gmock library all at once

Use this option if you really want to be sure you build gtest/gmock with the _exact same build options_ as your unit test files! This technique is slower, however, because it rebuilds the entire gtest/gmock library every time you build your unit test files.

```bash
cd path/to/eRCaGuy_hello_world/cpp

# [takes ~11 sec (since it's only building gtest, not gmock)] build & run gtest & your unit 
# tests all at once
# Optionally add `--verbose` for verbose output.
# 
# Notes:
# 1. Optionally add `googletest/googlemock/src/gmock-all.cc` and/or
#    `googletest/googlemock/src/gmock_main.cc` too, if needed.
time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
    -I"googletest/googletest/include" -I"googletest/googletest" \
    -I"googletest/googlemock/include" -I"googletest/googlemock" \
    googletest/googletest/src/gtest-all.cc googletest/googletest/src/gtest_main.cc \
    gtest_demo__sample1_factorial_and_is_prime_unittest.cc \
    gtest_demo__sample1_factorial_and_is_prime.cc \
    -o bin/a && time bin/a
```

<a id="more-examples-just-to-show-building-and-running-the-samples-which-come-with-googletest"></a>
### More examples just to show building and running the samples which come with googletest

Using Option 1 from above (pre-building the `*.a` static library files for gtest and gmock):

1. `googletest/googletest/samples/sample1_unittest.cc`
    ```bash
    time ( \
        time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
        -I"googletest/googletest/include" -I"googletest/googlemock/include" \
        googletest/googletest/samples/sample1_unittest.cc \
        googletest/googletest/samples/sample1.cc \
        bin/libgtest.a bin/libgtest_main.a \
        -o bin/a \
        && time bin/a \
    )
    ```
1. `googletest/googletest/samples/sample2_unittest.cc`
    ```bash
    time ( \
        time g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread \
        -I"googletest/googletest/include" -I"googletest/googlemock/include" \
        googletest/googletest/samples/sample2_unittest.cc \
        googletest/googletest/samples/sample2.cc \
        bin/libgtest.a bin/libgtest_main.a \
        -o bin/a \
        && time bin/a \
    )
    ```

etc. 


<a id="fmt-library-installation--setup"></a>
# `fmt` library installation & setup


<a id="references-1"></a>
## References:
1. Source code: https://github.com/fmtlib/fmt
1. https://fmt.dev/latest/syntax.html
1. https://fmt.dev/latest/usage.html#building-the-library
1. https://fmt.dev/latest/api.html
    1. https://fmt.dev/latest/api.html#compile-time-format-string-checks
1. My own notes & instructions: https://github.com/fmtlib/fmt/issues/2157#issuecomment-1117930229


<a id="1-build--install-the-fmt-library"></a>
## 1. Build & install the `fmt` library

Get the source code and place it at the same level as the main `eRCaGuy_hello_world` folder, then symlink the fmt lib into the `eRCaGuy_hello_world/cpp` folder.

```bash
# cd into your repo of interest (for me: `eRCaGuy_hello_world`)
cd path/to/eRCaGuy_hello_world
# go up one level to be at the same level as `eRCaGuy_hello_world`
cd ..

# clone the repo
time git clone https://github.com/fmtlib/fmt.git
# you now have the folder "fmt" at the same level as "eRCaGuy_hello_world"; ex:
#   some/dir/eRCaGuy_hello_world
#   some/dir/fmt

# cd into the folder where you want the symlink to googletest be located
cd eRCaGuy_hello_world/cpp
# create a relative symlink to the other repo here
ln -si ../../fmt .
```

Now build & install the library! See: https://fmt.dev/latest/usage.html#building-the-library

```bash
cd eRCaGuy_hello_world/cpp

cd fmt
mkdir -p build 
cd build
time cmake ..  # takes ~2 sec
time make      # takes ~3~5 minutes
time sudo make install  # takes ~7 sec
```

Done!

Here is the output of `time sudo make install`, so you can see what it's really doing:

```bash
eRCaGuy_hello_world/cpp/fmt/build$ time sudo make install
[sudo] password for gabriel: 
[  4%] Built target fmt
[  7%] Built target gtest
[ 16%] Built target posix-mock-test
[ 23%] Built target test-main
[ 26%] Built target xchar-test
[ 29%] Built target color-test
[ 32%] Built target chrono-test
[ 35%] Built target os-test
[ 38%] Built target args-test
[ 41%] Built target enforce-checks-test
[ 44%] Built target gtest-extra-test
[ 47%] Built target printf-test
[ 50%] Built target scan-test
[ 53%] Built target format-test
[ 64%] Built target format-impl-test
[ 67%] Built target ostream-test
[ 72%] Built target ranges-test
[ 81%] Built target compile-fp-test
[ 84%] Built target assert-test
[ 87%] Built target core-test
[ 90%] Built target compile-test
[100%] Built target unicode-test
Install the project...
-- Install configuration: "Release"
-- Installing: /usr/local/lib/libfmt.a
-- Installing: /usr/local/include/fmt/args.h
-- Installing: /usr/local/include/fmt/chrono.h
-- Installing: /usr/local/include/fmt/color.h
-- Installing: /usr/local/include/fmt/compile.h
-- Installing: /usr/local/include/fmt/core.h
-- Installing: /usr/local/include/fmt/format.h
-- Installing: /usr/local/include/fmt/format-inl.h
-- Installing: /usr/local/include/fmt/locale.h
-- Installing: /usr/local/include/fmt/os.h
-- Installing: /usr/local/include/fmt/ostream.h
-- Installing: /usr/local/include/fmt/printf.h
-- Installing: /usr/local/include/fmt/ranges.h
-- Installing: /usr/local/include/fmt/xchar.h
-- Installing: /usr/local/lib/cmake/fmt/fmt-config.cmake
-- Installing: /usr/local/lib/cmake/fmt/fmt-config-version.cmake
-- Installing: /usr/local/lib/cmake/fmt/fmt-targets.cmake
-- Installing: /usr/local/lib/cmake/fmt/fmt-targets-release.cmake
-- Installing: /usr/local/lib/pkgconfig/fmt.pc

real    0m7.034s
user    0m0.413s
sys 0m0.217s
```


<a id="2-how-to-use-and-link-against-the-fmt-library-in-your-own-code"></a>
## 2. How to use and link against the `fmt` library in your own code

As you can see from the `time sudo make install` output above, `time sudo make install` installs both the _library_ into `/usr/local/lib/libfmt.a` **and** all of the header files to include into `/usr/local/include/fmt`! Having the header files there now means that I can just include the `fmt` library files like this in my projects now!:

```cpp
// You can do this now that the `fmt` library is installed!
#include <fmt/format.h>
```

...instead of having to do relative includes like this:

```cpp
#include "fmt/include/fmt/format.h"
```

OR having to add the `-I` flag to g++ like this: `-I"fmt/include"` and then including like this:

```cpp
#include "fmt/format.h"
```

Two options:

See my instructions here: https://github.com/fmtlib/fmt/issues/2157#issuecomment-1117930229

1. Option 1: add `#define FMT_HEADER_ONLY` to your build options or above your `#include <fmt/format.h>` line:
    Ex:
    ```bash
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 -DFMT_HEADER_ONLY fmt_lib_demo.cpp \
        -o bin/a -lfmt && bin/a
    ```
    Then in my source code:
    ```cpp
    #include <fmt/format.h>
    ```
    OR, just in my source code:
    ```cpp
    #define FMT_HEADER_ONLY
    #include <fmt/format.h>
    ```
1. Option 2 [my preference]: add `-lfmt` OR `"/usr/local/lib/libfmt.a"` to your build command to link against the make-installed static .a library at that location. 
    See my notes: https://github.com/fmtlib/fmt/issues/2157#issuecomment-1117930229:
    ```bash
    # Option 1 [my preference]: add `-lfmt`
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 fmt_lib_demo.cpp -o bin/a -lfmt && bin/a

    # OR: Option 2: add `"/usr/local/lib/libfmt.a"`
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 fmt_lib_demo.cpp "/usr/local/lib/libfmt.a" \
        -o bin/a && bin/a
    ```

**My final build command:**

I like to build with _static, compile-time format string checks ON_ by defining the `FMT_ENFORCE_COMPILE_STRING` macro and using the `FMT_STRING()` macro around all format strings so that I don't get unexpected run-time errors which throw exceptions and crash my code! See: 
1. https://fmt.dev/latest/api.html#compile-time-format-string-checks
1. https://github.com/fmtlib/fmt/issues/2157#issuecomment-1117930229

So, here is my final build command:
```bash
# my final `fmt` library build command style:

time g++ -Wall -Wextra -Werror -O3 -std=c++17 -DFMT_ENFORCE_COMPILE_STRING fmt_lib_demo.cpp \
    -o bin/a -lfmt && bin/a
```

Then, in your code, you must use `FMT_STRING()` around all format strings, like this, for example:

```cpp
#include <fmt/format.h>


std::string timestamps_str = fmt::format(FMT_STRING(
        "Timestamps:\n"
        "  time_ns_1 = {:20.9f}\n"
        "  time_ns_2 = {:20.9f}\n"
        "  time_ns_3 = {:20.9f}\n"),
        NS_TO_SEC((double)time_ns_1),
        NS_TO_SEC((double)time_ns_2),
        NS_TO_SEC((double)time_ns_3));
std::cout << timestamps_str;

fmt::print(FMT_STRING("\n"
        "  time_ns_1 = {:20.9f}\n"),
        NS_TO_SEC((double)time_ns_1));
```

**See [eRCaGuy_hello_world/cpp/fmt_lib_demo.cpp](fmt_lib_demo.cpp) for a full demo!**


<a id="curl-library-installation--setup"></a>
# `curl` library installation & setup


<a id="references-2"></a>
## References:
1. Source code: https://github.com/curl/curl
1. Installation instructions: https://curl.se/docs/install.html
1. \*\*\*\*\*+ [my answer] [How to build curl from scratch using cmake, including building libcurl, and then how to use it to build and run the C examples](https://unix.stackexchange.com/a/701472/114401) 


<a id="1-build--install-the-curl-library"></a>
## 1. Build & install the `curl` library

Get the source code and place it at the same level as the main `eRCaGuy_hello_world` folder, then symlink the lib into the `eRCaGuy_hello_world/cpp` folder.

```bash
# cd into your repo of interest (for me: `eRCaGuy_hello_world`)
cd path/to/eRCaGuy_hello_world
# go up one level to be at the same level as `eRCaGuy_hello_world`
cd ..

time git clone https://github.com/curl/curl.git

# cd into the folder where you want the symlink to be located
cd eRCaGuy_hello_world/cpp
# create a relative symlink to the other repo here
ln -si ../../curl .
```

Now build & install the library!  
See: https://curl.se/docs/install.html

```bash
cd eRCaGuy_hello_world/cpp

cd curl
mkdir -p build 
cd build
time cmake ..  # takes ~20 sec
time make      # takes ~11 sec

time sudo make install  # takes < 1 sec
```

Note that `make` above produces the dynamic, shared-object .so library file at `curl/build/lib/libcurl.so`. You need to link to this library at compile time, and load it directly at run-time. See: https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html.

Sample output of `sudo make install`, so you can know what it did. Note that it only took 10 sec because I had to type in my password too:

```bash
eRCaGuy_hello_world/cpp/curl/build$ time sudo make install
[sudo] password for gabriel: 
[ 73%] Built target libcurl
[100%] Built target curl
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/bin/curl-config
-- Installing: /usr/local/lib/pkgconfig/libcurl.pc
-- Installing: /usr/local/include/curl
-- Installing: /usr/local/include/curl/curl.h
-- Installing: /usr/local/include/curl/curlver.h
-- Installing: /usr/local/include/curl/header.h
-- Installing: /usr/local/include/curl/options.h
-- Installing: /usr/local/include/curl/easy.h
-- Installing: /usr/local/include/curl/typecheck-gcc.h
-- Installing: /usr/local/include/curl/stdcheaders.h
-- Installing: /usr/local/include/curl/mprintf.h
-- Installing: /usr/local/include/curl/multi.h
-- Installing: /usr/local/include/curl/system.h
-- Installing: /usr/local/include/curl/urlapi.h
-- Installing: /usr/local/lib/cmake/CURL/CURLTargets.cmake
-- Installing: /usr/local/lib/cmake/CURL/CURLTargets-noconfig.cmake
-- Installing: /usr/local/lib/cmake/CURL/CURLConfigVersion.cmake
-- Installing: /usr/local/lib/cmake/CURL/CURLConfig.cmake
-- Installing: /usr/local/lib/libcurl.so
-- Installing: /usr/local/bin/curl
-- Set runtime path of "/usr/local/bin/curl" to ""

real    0m10.549s
user    0m0.152s
sys 0m0.088s
```


<a id="2-how-to-use-and-link-against-the-curl-library-in-your-own-code"></a>
## 2. How to use and link against the `curl` library in your own code

Let's build one of the example files as a demo of this. This file: `curl/docs/examples/10-at-a-time.c`.

See the examples online here: https://curl.se/libcurl/c/example.html.

For shared, dynamic library .so file help, see: https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html

```bash
# This works even if you stopped after `time make` and did NOT run 
# `sudo make install` above!
time ( \
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 \
    -I"curl/include" \
    curl/docs/examples/10-at-a-time.c \
    -L"curl/build/lib" \
    -lcurl \
    -o bin/a \
    && time LD_LIBRARY_PATH="$(pwd)/curl/build/lib:$LD_LIBRARY_PATH" bin/a \
)

# OR, if you DID run `sudo make install` above, you can simplify the above
# cmd slightly to this:
time ( \
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 \
    curl/docs/examples/10-at-a-time.c \
    -lcurl \
    -o bin/a \
    && time LD_LIBRARY_PATH="$(pwd)/curl/build/lib:$LD_LIBRARY_PATH" bin/a \
)

# OR (best): add this new library path permanently: <===== BEST ======
# Run this _once_ to add it to your ~/.bashrc file. 
# See: https://stackoverflow.com/a/37558191/4561887.
echo "export LD_LIBRARY_PATH=\"$(pwd)/curl/build/lib:\$LD_LIBRARY_PATH\"" >> ~/.bashrc   # <========
. ~/.bashrc  # re-source it
# Then run:
time ( \
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 \
    curl/docs/examples/10-at-a-time.c \
    -lcurl \
    -o bin/a \
    && time bin/a \
)

# <============
# Correction though: we should build the examples as C with `gcc`, rather than as C++ with `g++`
# (even though the first one at least does build and run as C++ too). 
# **Final answer:**
time ( \
    time gcc -Wall -Wextra -Werror -O3 -std=c17 \
    curl/docs/examples/10-at-a-time.c \
    -lcurl \
    -o bin/a \
    && time bin/a \
)
```

See my answer here: [How to build curl from scratch, including libcurl, and use it to build and run the C examples](https://unix.stackexchange.com/a/701472/114401).


Sample run and output of the first command shown above:

```bash
eRCaGuy_hello_world/cpp$ time ( \
>     time g++ -Wall -Wextra -Werror -O3 -std=c++17 \
>     -I"curl/include" \
>     curl/docs/examples/10-at-a-time.c \
>     -L"curl/build/lib" \
>     -lcurl \
>     -o bin/a \
>     && time LD_LIBRARY_PATH="$(pwd)/curl/build/lib:$LD_LIBRARY_PATH" bin/a \
> )

real    0m0.125s
user    0m0.107s
sys 0m0.019s
R: 0 - No error <https://www.iana.org>
R: 0 - No error <https://www.ibm.com>
R: 0 - No error <https://www.google.com>
R: 0 - No error <https://www.amazon.com>
R: 0 - No error <https://www.oracle.com>
R: 0 - No error <https://www.mysql.com>
R: 0 - No error <https://www.ripe.net>
R: 0 - No error <https://opensource.org>
R: 0 - No error <https://www.yahoo.com>
R: 0 - No error <https://www.mozilla.org>
R: 0 - No error <https://www.netcraft.com>
R: 0 - No error <https://www.ca.com>
R: 0 - No error <https://www.dell.com>
R: 0 - No error <https://www.wikipedia.org>
R: 0 - No error <https://www.hp.com>
R: 0 - No error <https://www.cnet.com>
R: 0 - No error <https://www.cert.org>
R: 0 - No error <https://www.mit.edu>
R: 0 - No error <https://www.chip.de>
R: 0 - No error <https://www.playstation.com>
R: 0 - No error <https://www.symantec.com>
R: 0 - No error <https://www.apple.com>
R: 0 - No error <https://www.ebay.com>
R: 0 - No error <https://www.nist.gov>
R: 0 - No error <https://www.uefa.com>
R: 0 - No error <https://www.cnn.com>
R: 0 - No error <https://www.supermicro.com>
R: 0 - No error <https://www.zdnet.com>
R: 0 - No error <https://www.ietf.org>
R: 0 - No error <https://news.google.com>
R: 0 - No error <https://www.ieee.org>
R: 0 - No error <https://www.hotmail.com>
R: 0 - No error <https://www.fujitsu.com/global/>
R: 0 - No error <https://www.bbc.co.uk>
R: 0 - No error <https://www.usatoday.com>
R: 0 - No error <https://www.foxnews.com>
R: 0 - No error <https://www.msn.com>
R: 0 - No error <https://www.cbs.com>
R: 0 - No error <https://www.sky.com>
R: 0 - No error <https://slashdot.org>
R: 0 - No error <https://www.wired.com>
R: 0 - No error <https://www.heise.de>
R: 0 - No error <https://apache.org>
R: 0 - No error <https://www.nbc.com/>
R: 0 - No error <https://www.un.org>
R: 0 - No error <https://www.informationweek.com>
R: 0 - No error <https://www.microsoft.com>

real    0m10.444s
user    0m0.911s
sys 0m0.169s

real    0m10.570s
user    0m1.018s
sys 0m0.188s
```

