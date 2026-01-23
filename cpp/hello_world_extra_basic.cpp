///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++20 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

(description)
STATUS: (status)

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++20` instead of `-std=c++20` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# In C++

# 1. For Linux, or in MSYS2 ucrt64 bash shell in Windows:
# - For MSYS2 setup, see my answer: https://stackoverflow.com/a/77407282/4561887
# Build and run:
# Takes ~0.33 sec:
time ( g++ -Wall -Wextra -Werror -O3 -std=gnu++20 hello_world_extra_basic.cpp -o bin/a && bin/a )
#
# OR [BEST] (just call this file as an executable directly).
# Build and run:
# Takes ~0.33 sec:
time ./hello_world_extra_basic.cpp
#
# Verify it is a Linux executable relying on dynamic libraries:
file bin/a

# 2. Cross-compiling from Linux for Windows via mingw-w64: https://www.mingw-w64.org/
# Install dependencies
sudo apt update
sudo apt install mingw-w64
sudo apt update
sudo apt install wine wine64
#
# Then build only (don't run):
time x86_64-w64-mingw32-g++ -Wall -Wextra -Werror -O3 -std=gnu++20 hello_world_extra_basic.cpp -o bin/a.exe
#
# OR: to build with statically-linked libraries, bundling the required libraries into the .exe
# and making it a standalone and portable executable, build with `-static`, which also includes
# `-static-libgcc -static-libstdc++` too.
# Build only (don't run):
time x86_64-w64-mingw32-g++ -Wall -Wextra -Werror -O3 -std=gnu++20 -static hello_world_extra_basic.cpp -o bin/a_static.exe
#
# Check the file type to see that it's an x86-64 MS Windows executable:
file bin/a.exe
file bin/a_static.exe
#
# And then run the statically-linked .exe via Wine on Linux, suppressing Wine warnings with
# `WINEDEBUG=-all` and then waiting for the Wine server to finish and not hang with `wineserver -w`.
# IMPORTANT: REMOVE `WINDEDEBUG=-all` if you want to see Wine warnings, which can be helpful for debugging:
# Takes ~11 sec:
time ( WINEDEBUG=-all wine bin/a_static.exe; wineserver -w )
#
# OR: run in wine, immediately killing the wine server when done to prevent it from taking time to
# clean up gracefully. This is only safe if your program doesn't need cleanup, is not closing
# GUIs or writing to files, etc.:
# Takes ~0.6 sec:
time ( WINEDEBUG=-all wine bin/a_static.exe; wineserver -k )
#
# OR [BEST] Cross-compile with static linking from Linux for Windows, then run the Windows .exe
# on Linux via Wine, all in one:
time x86_64-w64-mingw32-g++ -Wall -Wextra -Werror -O3 -std=gnu++20 -static hello_world_extra_basic.cpp -o bin/a_static.exe && WINEDEBUG=-all wine bin/a_static.exe; wineserver -w

# 3. Building and running on Windows for Windows
# - Requires:
#   1. The MSYS2 ucrt64 environment with g++ installed (see my instructions here:
#      https://stackoverflow.com/a/77407282/4561887) and
cd path/to/eRCaGuy_hello_world/cpp
#
# Then:
#
# Option 1: Run from the MSYS2 ucrt64 bash shell in Windows:
time g++ -Wall -Wextra -Werror -O3 -std=gnu++20 hello_world_extra_basic.cpp -o bin/a && bin/a
#
# Option 2: Run from Powershell in Windows, accessing the MSYS2 ucrt64 bash shell automatically:
# - See my answer here under the section titled "When running from a Windows PowerShell":
#   https://stackoverflow.com/a/79201770/4561887
C:\msys64\msys2_shell.cmd -defterm -here -no-start -ucrt64 -shell bash -c 'time g++ -Wall -Wextra -Werror -O3 -std=gnu++20 hello_world_extra_basic.cpp -o bin/a && bin/a'
```

References:
1.

*/

// C++ (incl. C) includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++20 hello_world_extra_basic.cpp -o bin/a && bin/a

    real    0m2.079s
    user    0m0.775s
    sys 0m0.087s
    Hello world!


You can also run this file as an executable directly!:

    eRCaGuy_hello_world/cpp$ ./hello_world_extra_basic.cpp
    Hello world!


*/
