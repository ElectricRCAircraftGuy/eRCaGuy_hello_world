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
1. https://en.cppreference.com/w/cpp/io/cout.html
1. https://en.cppreference.com/w/cpp/io/basic_ios/rdbuf.html
1. https://en.cppreference.com/w/cpp/io/basic_ostream.htm

*/

// C++ (incl. C) includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <sstream>
#include <string>
// #include <unistd.h>  // For `dup()`, `dup2()`, `close()`, `pipe()`

class StdoutCapture 
{
public: 
    // Start capturing stdout into a string stream.
    // - This will redirect all `std::cout` output to the string stream instead of to the console.
    void start() 
    {
        // Save original stdout buffer, and redirect stdout to our string stream
        cout_bak_ = std::cout.rdbuf(capture_buf_.rdbuf());
    }

    // Stop capturing stdout and restore original stdout.
    // - This will restore `std::cout` to its original state, so that future `std::cout` output goes to the console again.
    // - Returns the captured output as a string.
    std::string stop()
    {
        // Restore original stdout buffer
        std::cout.rdbuf(cout_bak_);

        return capture_buf_.str();
    }

private:
    // Original stdout buffer
    std::streambuf* cout_bak_ = nullptr;
    // String stream to capture output
    std::ostringstream capture_buf_;
};

int main() 
{
    // Before capturing
    std::cout << "1. This goes to console." << std::endl;
    printf("2. This goes to console.\n");
    
    // Capture output

    StdoutCapture capture;
    capture.start();

    std::cout << "1. This will be captured." << std::endl;
    printf("2. This will be captured.\n");

    std::string captured = capture.stop();

    // Print captured output to console
    printf("Captured output:\n%s", captured.c_str());
    

    return 0;
}



/*
SAMPLE OUTPUT:

Does NOT work correctly yet!: 

eRCaGuy_hello_world$ cpp/stdout_capture.cpp 
1. This goes to console.
2. This goes to console.
2. This will be captured.
Captured output:
1. This will be captured.


*/
