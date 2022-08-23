This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Table of Contents
<details>
<summary><b>(click to expand)</b></summary>
<!-- MarkdownTOC -->

1. [`ccache` - "a fast C/C++ compiler cache"](#ccache---a-fast-cc-compiler-cache)
1. [Library setup & installation](#library-setup--installation)
1. [C++ Googletest setup: how to build googletest \(gtest and gmock\) with the gcc/g++ compiler](#c-googletest-setup-how-to-build-googletest-gtest-and-gmock-with-the-gccg-compiler)
    1. [References:](#references)
    1. [First, clone the googletest source code and symlink it into your repo](#first-clone-the-googletest-source-code-and-symlink-it-into-your-repo)
    1. [Build all of gtest and gmock as static library archive `*.a` files](#build-all-of-gtest-and-gmock-as-static-library-archive-a-files)
        1. [Option 1 \[recommended/my preference\]: _manually_ build the `*.a` static library files with g++:](#option-1-recommendedmy-preference-manually-build-the-a-static-library-files-with-g)
        1. [Option 2: build with the Cmake files which come with the source code](#option-2-build-with-the-cmake-files-which-come-with-the-source-code)
    1. [Build your unit tests using gtest and/or gmock](#build-your-unit-tests-using-gtest-andor-gmock)
        1. [Option 1 \[my preference/recommended!\] build your unit test using the pre-built `*.a` static library files from above:](#option-1-my-preferencerecommended-build-your-unit-test-using-the-pre-built-a-static-library-files-from-above)
        1. [Option 2: rebuild your unit test _and_ the entire gtest/gmock library all at once](#option-2-rebuild-your-unit-test-and-the-entire-gtestgmock-library-all-at-once)
        1. [More examples just to show building and running the samples which come with googletest](#more-examples-just-to-show-building-and-running-the-samples-which-come-with-googletest)
1. [C++ `fmt` library installation & setup](#c-fmt-library-installation--setup)
    1. [References:](#references-1)
    1. [1. Build & install the `fmt` library](#1-build--install-the-fmt-library)
    1. [2. How to use and link against the `fmt` library in your own code](#2-how-to-use-and-link-against-the-fmt-library-in-your-own-code)
1. [C `curl` library installation & setup](#c-curl-library-installation--setup)
    1. [References:](#references-2)
    1. [1. Build & install the `curl` library](#1-build--install-the-curl-library)
    1. [2. How to use and link against the `curl` library in your own code](#2-how-to-use-and-link-against-the-curl-library-in-your-own-code)
1. [C++ `nlohmann/json` "JSON for Modern C++" library installation & setup](#c-nlohmannjson-json-for-modern-c-library-installation--setup)
    1. [Option 1: to download just that one single < 1 MB header file into your project, do this:](#option-1-to-download-just-that-one-single--1-mb-header-file-into-your-project-do-this)
    1. [Option 2 \[my preference\]: clone the _entire_ nlohmann json library](#option-2-my-preference-clone-the-entire-nlohmann-json-library)
    1. [Include the header in your builds](#include-the-header-in-your-builds)
1. [C++ `yaml-cpp` library installation & setup](#c-yaml-cpp-library-installation--setup)
    1. [1. Build & install the `yaml-cpp` library](#1-build--install-the-yaml-cpp-library)
    1. [2. How to use and link against the `yaml-cpp` library in your own code](#2-how-to-use-and-link-against-the-yaml-cpp-library-in-your-own-code)

<!-- /MarkdownTOC -->
</details>


<a id="ccache---a-fast-cc-compiler-cache"></a>
# `ccache` - ["a fast C/C++ compiler cache"](https://ccache.dev/manual/4.6.1.html)

You may optionally speed up your builds by using the `ccache` compiler cacher. 

References:
1. \*\*\*\*\*+ Quick instructions: https://ccache.dev/manual/4.6.1.html#_run_modes
1. https://github.com/ccache/ccache/blob/master/doc/INSTALL.md
1. https://ccache.dev/documentation.html
1. Main website: https://ccache.dev/

For Linux:
```bash
# Install it
sudo apt update 
sudo apt install ccache

ccache -h         # help menu
ccache --version  # print version info

# show stats
ccache -s
# OR (same thing)
ccache --show-stats

# (OPTIONAL) Create local symlinks to override your compiler and call ccache instead, whenever
# you try to call your compiler directly.
# See: https://ccache.dev/manual/4.6.1.html#_run_modes
cp ccache /usr/local/bin/
ln -s ccache /usr/local/bin/gcc
ln -s ccache /usr/local/bin/g++
ln -s ccache /usr/local/bin/cc
ln -s ccache /usr/local/bin/c++

# Basic, direct usage (without symlinks to replace your compiler)
ccache compiler compiler_options
# ex: 
time ccache g++ -Wall -Wextra -Werror -O3 -std=c++17 -I"json/single_include" json_nlohmann_demo.cpp -o bin/a && bin/a
```


<a id="library-setup--installation"></a>
# Library setup & installation

See the major headings below for instructions to install and set up various libraries.


<a id="c-googletest-setup-how-to-build-googletest-gtest-and-gmock-with-the-gccg-compiler"></a>
# C++ Googletest setup: how to build googletest (gtest and gmock) with the gcc/g++ compiler


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


<a id="c-fmt-library-installation--setup"></a>
# C++ `fmt` library installation & setup


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

# cd into the folder where you want a symlink to this repo to be located
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


<a id="c-curl-library-installation--setup"></a>
# C `curl` library installation & setup


<a id="references-2"></a>
## References:
1. Source code: https://github.com/curl/curl
1. Installation instructions: https://curl.se/docs/install.html
1. \*\*\*\*\*+ [my answer] [How to build curl from scratch using cmake, including building libcurl, and then how to use it to build and run the C examples](https://unix.stackexchange.com/a/701472/114401) 
1. \*\*\*\*\*+ libcurl usage & help:
    1. \*\*\*\*\* The libcurl API: https://curl.se/libcurl/c/
    1. libcurl - small example snippets: https://curl.se/libcurl/c/example.html
    1. libcurl programming tutorial: https://curl.se/libcurl/c/libcurl-tutorial.html; here are some of the _key sections_ I care about in this tutorial: 
        1. "Compiling the Program"
            Get the linking options for gcc:
            ```bash
            $ curl-config --libs
            -L/usr/local/lib -lcurl
            ```
        1. "Two interfaces"
        1. "Handle the easy libcurl"
        1. "Http posting" - for REST API `curl -X POST http://192.168.0.1/my_api/my_command` type POST commands!
        1. "Showing progress"
        1. "Libcurl with c++"
        1. "Persistence is the way to happiness"
        1. "The multi interface": 
        > The multi interface, on the other hand, allows your program to transfer multiple files in both directions at the same time, without forcing you to use multiple threads. The name might make it seem that the multi interface is for multi-threaded programs, but the truth is almost the reverse. The multi interface allows a single-threaded application to perform the same kinds of multiple, simultaneous transfers that multi-threaded programs can perform. It allows many of the benefits of multi-threaded transfers without the complexity of managing and synchronizing many threads.
    1. Easy interface overview: https://curl.se/libcurl/c/libcurl-easy.html
    1. multi interface overview: https://curl.se/libcurl/c/libcurl-multi.html
        1. curl_easy_setopt - set options for a curl easy handle [ex: `CURLOPT_URL`--the only option you really _must_ set]: https://curl.se/libcurl/c/curl_easy_setopt.html
    1. libcurl error codes [ex: `CURLE_OK` = "Curl Error Ok" = no error]: https://curl.se/libcurl/c/libcurl-errors.html


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

cd ../..  # go back up to the same level as where the `curl` dir is

# See:
# 1. https://stackoverflow.com/a/37558191/4561887
# 1. [my answer] https://unix.stackexchange.com/a/701472/114401
# <==== DO THIS! ====
# (recommended, since the `libcurl.so` file has been installed by `sudo make install` here now too):
echo "export LD_LIBRARY_PATH=\"/usr/local/lib:\$LD_LIBRARY_PATH\"" >> ~/.bashrc
# OR (also ok, since this is where the library got built):
echo "export LD_LIBRARY_PATH=\"$(pwd)/curl/build/lib:\$LD_LIBRARY_PATH\"" >> ~/.bashrc
. ~/.bashrc  # re-source it
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
# (recommended, since the `libcurl.so` file has been installed by `sudo make install` here now too):
echo "export LD_LIBRARY_PATH=\"/usr/local/lib:\$LD_LIBRARY_PATH\"" >> ~/.bashrc  # <========
# OR (also ok, since this is where the library got built):
echo "export LD_LIBRARY_PATH=\"$(pwd)/curl/build/lib:\$LD_LIBRARY_PATH\"" >> ~/.bashrc
. ~/.bashrc  # re-source it
# Then run:
time ( \
    time g++ -Wall -Wextra -Werror -O3 -std=c++17 \
    curl/docs/examples/10-at-a-time.c \
    -lcurl \
    -o bin/a \
    && time bin/a \
)

# <============ FINAL ANSWER ===========
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


<a id="c-nlohmannjson-json-for-modern-c-library-installation--setup"></a>
# C++ `nlohmann/json` "JSON for Modern C++" library installation & setup

References: 
1. main source code: https://github.com/nlohmann/json
    1. Basic usage for serialization/deserialization and dumping the output for humans to read: https://github.com/nlohmann/json#serialization--deserialization
1. main webpage: https://json.nlohmann.me/

This library can be used and installed as a "singled header file". The file stored at `single_include/nlohmann/json.hpp` is the one single header file to rule them all! Just copy it to your project, include it, and you're done! It just works.


<a id="option-1-to-download-just-that-one-single--1-mb-header-file-into-your-project-do-this"></a>
## Option 1: to download just that one single < 1 MB header file into your project, do this:

```bash
cd path/to/your_project
mkdir -p json/single_include/nlohmann
cd json/single_include/nlohmann

# download the one single < 1 MB header file
time wget https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp

# cd back up to your project
```


<a id="option-2-my-preference-clone-the-entire-nlohmann-json-library"></a>
## Option 2 [my preference]: clone the _entire_ nlohmann json library

Here is the general "installation" process I like to use for this json library repo. Note, however, that cloning the repo may take 10\~15 minutes or so, downloading \~300 MiB of data, so if you have a slow internet connection or limited data just do the option above instead.

```bash
# cd into your repo of interest (for me: `eRCaGuy_hello_world`)
cd path/to/eRCaGuy_hello_world
# go up one level to be at the same level as `eRCaGuy_hello_world`
cd ..

# clone the repo; this downloads ~300 MiB of data and takes 10~15 minutes
time git clone https://github.com/nlohmann/json.git
# you now have the folder "json" at the same level as "eRCaGuy_hello_world"; ex:
#   some/dir/eRCaGuy_hello_world
#   some/dir/json

# cd into the folder where you want a symlink to this repo to be located
cd eRCaGuy_hello_world/cpp
# create a relative symlink to the other repo here
ln -si ../../json .
```


<a id="include-the-header-in-your-builds"></a>
## Include the header in your builds

Now, to build and use that header file in your projects, add this include option to your gcc build options:
```bash
-I"path/to/json/single_include"
```

Then, you can include that file in a source file with:
```cpp
#include <nlohmann/json.hpp>
```

See [json_nlohmann_demo.cpp](json_nlohmann_demo.cpp) as an example I wrote.


<a id="c-yaml-cpp-library-installation--setup"></a>
# C++ `yaml-cpp` library installation & setup

**References:**
1. https://github.com/jbeder/yaml-cpp
1. Tutorials:
    1. https://github.com/jbeder/yaml-cpp/wiki/Tutorial
    1. https://github.com/jbeder/yaml-cpp/wiki/How-To-Emit-YAML


<a id="1-build--install-the-yaml-cpp-library"></a>
## 1. Build & install the `yaml-cpp` library

```bash
# cd into your repo of interest (for me: `eRCaGuy_hello_world`)
cd path/to/eRCaGuy_hello_world
# go up one level to be at the same level as `eRCaGuy_hello_world`
cd ..

# clone the repo
time git clone https://github.com/jbeder/yaml-cpp.git
# you now have the folder "yaml-cpp" at the same level as "eRCaGuy_hello_world"; ex:
#   some/dir/eRCaGuy_hello_world
#   some/dir/yaml-cpp

# cd into the folder where you want a symlink to this repo to be located
cd eRCaGuy_hello_world/cpp
# create a relative symlink to the other repo here
ln -si ../../yaml-cpp .
```

Now build the library! See: https://github.com/jbeder/yaml-cpp#how-to-build

```bash
cd eRCaGuy_hello_world/cpp

cd yaml-cpp
mkdir -p build 
cd build
time cmake ..  # takes ~1 sec
time make      # takes ~15 sec
time sudo make install  # takes ~7 sec
```

Done!

Here is the output of `time sudo make install`, so you can see what it's really doing. As you can see, it installed the static library .a file into `/usr/local/lib/libyaml-cpp.a`, and it installed all of the relevant header files you can include into the `/usr/local/include/yaml-cpp` dir, such as the main header, which is `/usr/local/include/yaml-cpp/yaml.h`.

```
eRCaGuy_hello_world/cpp/yaml-cpp/build$ time sudo make install  # takes ~7 sec
[sudo] password for gabriel: 
[ 84%] Built target yaml-cpp
[ 89%] Built target yaml-cpp-parse
[ 94%] Built target yaml-cpp-read
[100%] Built target yaml-cpp-sandbox
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/lib/libyaml-cpp.a
-- Up-to-date: /usr/local/include
-- Installing: /usr/local/include/yaml-cpp
-- Installing: /usr/local/include/yaml-cpp/mark.h
-- Installing: /usr/local/include/yaml-cpp/noexcept.h
-- Installing: /usr/local/include/yaml-cpp/emitterdef.h
-- Installing: /usr/local/include/yaml-cpp/binary.h
-- Installing: /usr/local/include/yaml-cpp/emitterstyle.h
-- Installing: /usr/local/include/yaml-cpp/emittermanip.h
-- Installing: /usr/local/include/yaml-cpp/emitfromevents.h
-- Installing: /usr/local/include/yaml-cpp/null.h
-- Installing: /usr/local/include/yaml-cpp/eventhandler.h
-- Installing: /usr/local/include/yaml-cpp/ostream_wrapper.h
-- Installing: /usr/local/include/yaml-cpp/yaml.h
-- Installing: /usr/local/include/yaml-cpp/anchor.h
-- Installing: /usr/local/include/yaml-cpp/node
-- Installing: /usr/local/include/yaml-cpp/node/type.h
-- Installing: /usr/local/include/yaml-cpp/node/iterator.h
-- Installing: /usr/local/include/yaml-cpp/node/parse.h
-- Installing: /usr/local/include/yaml-cpp/node/detail
-- Installing: /usr/local/include/yaml-cpp/node/detail/iterator_fwd.h
-- Installing: /usr/local/include/yaml-cpp/node/detail/iterator.h
-- Installing: /usr/local/include/yaml-cpp/node/detail/node_iterator.h
-- Installing: /usr/local/include/yaml-cpp/node/detail/impl.h
-- Installing: /usr/local/include/yaml-cpp/node/detail/node_ref.h
-- Installing: /usr/local/include/yaml-cpp/node/detail/node.h
-- Installing: /usr/local/include/yaml-cpp/node/detail/memory.h
-- Installing: /usr/local/include/yaml-cpp/node/detail/node_data.h
-- Installing: /usr/local/include/yaml-cpp/node/ptr.h
-- Installing: /usr/local/include/yaml-cpp/node/impl.h
-- Installing: /usr/local/include/yaml-cpp/node/emit.h
-- Installing: /usr/local/include/yaml-cpp/node/node.h
-- Installing: /usr/local/include/yaml-cpp/node/convert.h
-- Installing: /usr/local/include/yaml-cpp/depthguard.h
-- Installing: /usr/local/include/yaml-cpp/dll.h
-- Installing: /usr/local/include/yaml-cpp/stlemitter.h
-- Installing: /usr/local/include/yaml-cpp/parser.h
-- Installing: /usr/local/include/yaml-cpp/traits.h
-- Installing: /usr/local/include/yaml-cpp/emitter.h
-- Installing: /usr/local/include/yaml-cpp/contrib
-- Installing: /usr/local/include/yaml-cpp/contrib/anchordict.h
-- Installing: /usr/local/include/yaml-cpp/contrib/graphbuilder.h
-- Installing: /usr/local/include/yaml-cpp/exceptions.h
-- Installing: /usr/local/share/cmake/yaml-cpp/yaml-cpp-targets.cmake
-- Installing: /usr/local/share/cmake/yaml-cpp/yaml-cpp-targets-noconfig.cmake
-- Installing: /usr/local/share/cmake/yaml-cpp/yaml-cpp-config.cmake
-- Installing: /usr/local/share/cmake/yaml-cpp/yaml-cpp-config-version.cmake
-- Installing: /usr/local/share/pkgconfig/yaml-cpp.pc

real    0m6.552s
user    0m0.138s
sys 0m0.051s
```


<a id="2-how-to-use-and-link-against-the-yaml-cpp-library-in-your-own-code"></a>
## 2. How to use and link against the `yaml-cpp` library in your own code

See the section in this readme titled _"2. How to use and link against the fmt library in your own code"_ for more details and info. and alternative options.

**Option 1: link in the _installed_ static .a file library**

In your header or source file:

```cpp
#include <yaml-cpp/yaml.h>
```

In your build command, add `-lyaml-cpp` to link in the library. Ex:

```bash
time g++ -Wall -Wextra -Werror -O3 -std=c++17 yaml-cpp_lib_demo.cpp -o bin/a -lyaml-cpp && bin/a
```

**Option 2: _manually_ link in the .a file**

TODO
