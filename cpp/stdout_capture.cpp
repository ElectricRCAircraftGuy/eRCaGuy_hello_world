///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
July 2025

Capture stdout into a string buffer, and then print it to the console.
- This is useful for some debugging or unit testing where you need to ensure a certain thing
  was printed. 
STATUS: (status)

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=gnu++17 stdout_capture.cpp -o bin/a && bin/a

# OR (just call this file as an exectuable directly)
time ./stdout_capture.cpp
```

References:
1. Grok AI: 
    1. Private link: https://grok.com/chat/356d87ac-b4c4-4bae-b13f-ffef0c75b9d9
    1. Public link: https://grok.com/share/bGVnYWN5_da25d90e-acf0-41f7-a128-feeb18e514a2

*/

// C++ (incl. C) includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <sstream>
#include <string>

std::string captureStdout() {
    // Save original stdout buffer
    static std::streambuf* oldCout = std::cout.rdbuf();
    
    // Create string stream to capture output
    std::ostringstream capture;
    
    // Redirect stdout to our string stream
    std::cout.rdbuf(capture.rdbuf());
    
    // Your code that writes to stdout goes here
    // For example:
    std::cout << "This will be captured" << std::endl;
    
    // Restore original stdout
    std::cout.rdbuf(oldCout);
    
    // Return captured output
    return capture.str();
}

int main() {
    // Before capturing
    std::cout << "This goes to console" << std::endl;
    
    // Capture output
    std::string captured = captureStdout();
    
    // After capturing
    std::cout << "Back to console" << std::endl;
    std::cout << "Captured: " << captured << std::endl;
    
    return 0;
}



/*
SAMPLE OUTPUT:

eRCaGuy_hello_world$ cpp/stdout_capture.cpp 
This goes to console
Back to console
Captured: This will be captured


*/
