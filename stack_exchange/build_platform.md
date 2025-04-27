<!--
My answer: https://stackoverflow.com/a/79228659/4561887

GS  
Apr. 2025
-->


## Detecting your build platform/environment in C and C++ at compile-time in Linux, Windows, GCC, MSYS2, Cygwin, etc.

#### Defines provided for you

Here are some possible defines which are automatically defined for a given compiler, OS, or platform:

```c
unix
__unix
__unix__
linux
__linux__
__gnu_linux__
_WIN32
_WIN64
__WIN32__
__CYGWIN__
__MINGW32__
__MINGW64__
__MSYS__
__GNUC__
```

Which ones are defined depends on the compiler, the build environment (ex: the MSYS2 terminal in Windows), and the OS. The results can vary and be somewhat mish-mashed (mixed and overlapping) due to this. 

#### MSYS2 defines you can manually add to your build system

If you are building in MSYS on Windows, see my instructions here for a full GCC or clang setup: [Installing & setting up MSYS2 from scratch, including adding all 7 profiles to Windows Terminal...so you can build native Windows applications with gcc on Windows.](https://stackoverflow.com/a/77407282/4561887)

Detecting which MSYS2 terminal you are building in can be manually done by inspecting the `MSYSTEM` environment variable. See my answer here: [How to specify in which of the 7 MSYS2 terminals to run a command in Windows from Bash, Command Prompt, & PowerShell](https://stackoverflow.com/a/79201770/4561887). 

Possible values for the `MSYSTEM` environment variable are:
```
MSYS
MINGW32
MINGW64
UCRT64
CLANG64
CLANG32
CLANGARM64
```

In your build system, you can then manually define the following C or C++ preprocessor defines, depending on which terminal you are running in: 
```c
#define MSYSTEM_MSYS
#define MSYSTEM_MINGW32
#define MSYSTEM_MINGW64
#define MSYSTEM_UCRT64
#define MSYSTEM_CLANG64
#define MSYSTEM_CLANG32
#define MSYSTEM_CLANGARM64

// and if the `MSYSTEM` environment variable is not set:
#define MSYSTEM_NOTSET
```

This can be done in CMake by adding the following near the top of your main `CMakeLists.txt` file. See a real example in my [eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2](https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2) repo: 

From [`CMakeLists.txt`](https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/blob/main/CMakeLists.txt):
```bash
# Get MSYSTEM environment variable and define it for C and C++ code. 
# - Example `MSYSTEM` values in MSYS2 on Windows are as follows. 
#   See my answer here: https://stackoverflow.com/a/79201770/4561887
#   1. MSYS
#   2. MINGW32
#   3. MINGW64
#   4. UCRT64
#   5. CLANG64
#   6. CLANG32
#   7. CLANGARM64
# - See what `MSYSTEM` is set to by searching 
#   "build/Release/compile_commands.json", for instance, for `-DMSYSTEM` 
#   after building.
set(MSYSTEM_VALUE $ENV{MSYSTEM})
if(MSYSTEM_VALUE)
    add_compile_definitions("MSYSTEM_${MSYSTEM_VALUE}")
else()
    add_compile_definitions("MSYSTEM_NOTSET")
endif()
```


## `platform.h` detection header file

Include this header file anywhere in your project to print out, at compile time, which of the above defines are defined, including your manual `MSYSTEM_*` defines:

[`platform.h`](https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/blob/main/src/platform.h):

```c
// platform.h
// By Gabriel Staples
// Apr. 2025
// 
// From: 
// 1. https://stackoverflow.com/a/79228659/4561887
// 2. https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/blob/main/src/platform.h
// 
// Print out some messages at compile time to show which platform we are 
// compiling on.
// - This helps us debug so we can get the correct static asserts on sizes 
//   for the various platforms on which we compile. 
// - See also: 
//   1. https://sourceforge.net/p/predef/wiki/OperatingSystems/
// 
// Note that on my 64-bit x86-64 computer, the sizes of types are the same on 
// `__CYGWIN__` (using the base MSYS2 terminal) on Windows as they are on
// `__gnu_linux__` on Linux. 

#pragma once

#pragma message(">>> Detecting your platform... <<<")

// Automatically defined by your compiler/OS/platform

#ifdef unix
    #pragma message("Compiling on unix")
#endif
#ifdef __unix
    #pragma message("Compiling on __unix")
#endif
#ifdef __unix__
    #pragma message("Compiling on __unix__")
#endif
#ifdef linux
    #pragma message("Compiling on linux")
#endif
#ifdef __linux__
    #pragma message("Compiling on __linux__")
#endif
#ifdef __gnu_linux__
    #pragma message("Compiling on __gnu_linux__")
#endif
#ifdef _WIN32
    #pragma message("Compiling on _WIN32")
#endif
#ifdef _WIN64
    #pragma message("Compiling on _WIN64")
#endif
#ifdef __WIN32__
    #pragma message("Compiling on __WIN32__")
#endif
#ifdef __CYGWIN__
    #pragma message("Compiling on __CYGWIN__")
#endif
#ifdef __MINGW32__
    #pragma message("Compiling on __MINGW32__")
#endif
#ifdef __MINGW64__
    #pragma message("Compiling on __MINGW64__")
#endif
#ifdef __MSYS__
    #pragma message("Compiling on __MSYS__")
#endif
#ifdef __GNUC__
    #pragma message("Compiling on __GNUC__")
#endif

// Custom `MSYSTEM_*` definitions added by me directly via CMakeLists.txt.
// - This is based on the fact that possible `MSYSTEM` environment variable 
//   values set by the MSYS2 terminal environment on Windows include:
//  
//   1. MSYS
//   2. MINGW32
//   3. MINGW64
//   4. UCRT64
//   5. CLANG64
//   6. CLANG32
//   7. CLANGARM64
// 
// - See my answer here: https://stackoverflow.com/a/79201770/4561887

#ifdef MSYSTEM_MSYS
    #pragma message("Compiling on MSYSTEM_MSYS")
#endif
#ifdef MSYSTEM_MINGW32
    #pragma message("Compiling on MSYSTEM_MINGW32")
#endif
#ifdef MSYSTEM_MINGW64
    #pragma message("Compiling on MSYSTEM_MINGW64")
#endif
#ifdef MSYSTEM_UCRT64
    #pragma message("Compiling on MSYSTEM_UCRT64")
#endif
#ifdef MSYSTEM_CLANG64
    #pragma message("Compiling on MSYSTEM_CLANG64")
#endif
#ifdef MSYSTEM_CLANG32
    #pragma message("Compiling on MSYSTEM_CLANG32")
#endif
#ifdef MSYSTEM_CLANGARM64
    #pragma message("Compiling on MSYSTEM_CLANGARM64")
#endif
#ifdef MSYSTEM_NOTSET
    #pragma message("Compiling on MSYSTEM_NOTSET (ie: probably Linux)")
#endif
```


## My test results (building the exact same code on different platforms)

Let's build my Linux/Unix sockets and cmake demo on both Linux and Windows. Here is my project: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2

For each test, whether on Linux or on Windows in one of the 7 MSYS2 terminals, I build the exact same code using the exact same build tools and commands: 
```bash
make clean
make
```

If a particular macro from `platform.h` above is defined, such as `__gnu_linux__`, it shows up in the build output in a message like this:

> `note: ‘#pragma message: Compiling on __gnu_linux__’`

Here are my full results:

#### 1. Linux Ubuntu 22.04

Compile-time define results after running `make clean && make`:
```
unix
__unix
__unix__
linux
__linux__
__gnu_linux__   <== main automatically-defined one I use
__GNUC__
MSYSTEM_NOTSET  <== custom one I defined in CMakeLists.txt
```

#### 2. Windows 11 in the [7 MSYS2 terminals](https://stackoverflow.com/a/77407282/4561887)
    
**Important:** for each of the 7 MSYS2 terminals, if you don't run the "build setup" commands to install that terminal's terminal-specific version of `gcc`, `cmake`, and `make`, then it appears to default back to using the base MSYS2 terminal's version of `gcc`, `cmake`, and `make`, assuming you previously installed it with: 
```bash
pacman -Suy
pacman -S gcc   # Install gcc
pacman -S cmake # Install CMake
pacman -S make  # Install make
```

However, once you install a given terminal's specific version of those tools into that terminal, such as by running `pacman -S mingw-w64-clang-x86_64-clang` in the `clang64` terminal, then running `make` in my project will use that version of those tools instead, which in the `clang64` terminal will cause CMake to configure and use `Clang 20.1.3`, for example, instead of the base terminal's GCC `GNU 13.3.0`.

Here are my MSYS2 Windows build results:

1. Base `msys` / `msys2` terminal:
    1. Build setup:
        ```bash
        # Update the package database and core system packages; run 
        # repeatedly until no more updates are available
        pacman -Suy  

        pacman -S gcc   # Install gcc
        pacman -S cmake # Install CMake
        pacman -S make  # Install make
        ```
    1. Compile-time define results after running `make clean && make`:
        ```
        unix
        __unix
        __unix__
        __CYGWIN__    <== main automatically-defined one I use
        __MSYS__
        __GNUC__
        MSYSTEM_MSYS  <== custom one I defined in CMakeLists.txt
        ```
    1. Unix/Linux sockets build in this environment on Windows? 
        Yes

1. `mingw32` terminal:
    1. Build setup:
        ```bash
        pacman -Syu  # run repeatedly until there are no more updates
        pacman -S mingw-w64-i686-gcc    # Install gcc
        pacman -S mingw-w64-i686-cmake  # Install CMake
        pacman -S mingw-w64-i686-make   # Install make
        ```
    1. Compile-time define results after running `make clean && make`:
        ```
        _WIN32
        __WIN32__
        __MINGW32__      <== main automatically-defined one I use
        __GNUC__
        MSYSTEM_MINGW32  <== custom one I defined in CMakeLists.txt
        ```
    1. Unix/Linux sockets build in this environment on Windows? 
        No! 
        
        Error: 
        ```bash
        eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2/src/main_server.cpp:83:10: fatal error: arpa/inet.h: No such file or directory
        83 | #include <arpa/inet.h>
            |          ^~~~~~~~~~~~~
        ```

        I commented out almost all of the file in `main_client.cpp` just to get it to build far enough for me to see the compile-time macro define results above. 
        
        Here is what I left in `main_client.cpp` to get it to compile:
        ```c
        #include "platform.h"

        int main()
        {
            return 0;
        }
        ```

1. `mingw64` terminal:
    1. Build setup:
        ```bash
        pacman -Syu  # run repeatedly until there are no more updates
        pacman -S mingw-w64-x86_64-gcc      # Install gcc
        pacman -S mingw-w64-x86_64-cmake    # Install CMake
        pacman -S mingw-w64-x86_64-make     # Install make
        ```
    1. Compile-time define results after running `make clean && make`:
        ```
        _WIN32
        _WIN64
        __WIN32__
        __MINGW32__
        __MINGW64__      <== main automatically-defined one I use
        __GNUC__
        MSYSTEM_MINGW64  <== custom one I defined in CMakeLists.txt
        ```
    1. Unix/Linux sockets build in this environment on Windows?
        No! Same error as `mingw32` above. 

1. `ucrt64` terminal:
    1. Build setup:
        ```bash
        pacman -Syu  # run repeatedly until there are no more updates
        pacman -S mingw-w64-ucrt-x86_64-gcc     # Install gcc
        pacman -S mingw-w64-ucrt-x86_64-cmake   # Install CMake
        pacman -S mingw-w64-ucrt-x86_64-make    # Install make
        ```
    1. Compile-time define results after running `make clean && make` (same as `mingw64`, except for my custom definition):
        ```
        _WIN32
        _WIN64
        __WIN32__
        __MINGW32__
        __MINGW64__     <== main automatically-defined one I use
        __GNUC__
        MSYSTEM_UCRT64  <== custom one I defined in CMakeLists.txt
        ```
    1. Unix/Linux sockets build in this environment on Windows?
        No! Same error as `mingw32` above.

1. `clang64` terminal:
    1. Build setup: 
        ```bash
        pacman -Syu  # run repeatedly until there are no more updates
        pacman -S mingw-w64-clang-x86_64-clang  # Install clang
        pacman -S mingw-w64-clang-x86_64-cmake  # Install CMake
        pacman -S mingw-w64-clang-x86_64-make   # Install make
        ```
    1. Compile-time define results after running `make clean && make` (same as `mingw64`, except for my custom definition):
        ```
        _WIN32
        _WIN64
        __WIN32__
        __MINGW32__
        __MINGW64__      <== main automatically-defined one I use
        __GNUC__
        MSYSTEM_CLANG64  <== custom one I defined in CMakeLists.txt
        ```
    1. Unix/Linux sockets build in this environment on Windows?
        No! Same error as `mingw32` above. Except the colored output is prettier because clang generally does a better job at beautification and compile-time messages than gcc does. 

1. `clang32` terminal:
    [deprecated; no longer opens after running `pacman -Syu` repeatedly, to completion]

1. `clangarm64` terminal:
    1. Build setup:
        ```bash
        pacman -Syu  # run repeatedly until there are no more updates
        pacman -S mingw-w64-clang-aarch64-clang  # Install clang
        pacman -S mingw-w64-clang-aarch64-cmake  # Install CMake
        pacman -S mingw-w64-clang-aarch64-make   # Install make
        ```
    1. Compile-time define results after running `make clean && make`:
    
        NA. Cannot run `cmake`, probably because I'm on an x86-64 computer and the `clangarm64` terminal is for ARM64-based CPUs. 
        
        ```bash
        $ make clean && make
        rm -rf build/
        ./cmake_configure_and_build.sh "debug"
        ===================================================================
        Configuring and building debug...
        ./cmake_configure_and_build.sh: line 14: /clangarm64/bin/cmake: cannot execute binary file: Exec format error
        ./cmake_configure_and_build.sh: line 15: /clangarm64/bin/cmake: cannot execute binary file: Exec format error
        make: *** [Makefile:16: debug] Error 126
        ```


## References

1. [The main answer](https://stackoverflow.com/a/8249232/4561887)
1. The main answer's primary reference: **Pre-defined Compiler Macros Wiki:** https://sourceforge.net/p/predef/wiki/OperatingSystems/
1. [How can I detect g++ and MinGW in C++ preprocessor?](https://stackoverflow.com/a/17493838/4561887)
1. My answer: [Installing & setting up MSYS2 from scratch, including adding all 7 profiles to Windows Terminal...so you can build native Windows applications with gcc on Windows.](https://stackoverflow.com/a/77407282/4561887)
1. My repo: full demo of building and running Unix sockets in the MSYS terminl on Windows: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2
1. My answer: [How to specify in which of the 7 MSYS2 terminals to run a command in Windows from Bash, Command Prompt, & PowerShell](https://stackoverflow.com/a/79201770/4561887)
