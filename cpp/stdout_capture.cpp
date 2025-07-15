///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" "stdout_capture_lib.cpp" -o /tmp/a && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
July 2025

Capture stdout into a string buffer, and then print it to the console.
- This is useful for some debugging or unit testing where you need to ensure a certain thing
  was printed. 
- NB: The file descriptor redirection at the OS level (`dup2()`) is more fundamental than C++ stream
  buffer redirection. When you redirect the file descriptor, you're redirecting at the system call
  level, which affects all code in this same process that writes to that file descriptor - whether
  it's C++ streams, C stdio, or even other languages such as Bash or Python. 

STATUS: Done and works!

See the *_lib.h file for details. 
*/



// Local includes
#include "stdout_capture_lib.hpp"

// 3rd-party includes
// NA

// Linux/Unix includes
// NA

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>

// C includes 
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`


int main()
{
    // Before capturing
    std::cout << "1. This goes to console." << std::endl;
    printf("2. This goes to console.\n");
    
    // Capture output

    StdoutCapture capture;
    capture.start();                            // start capturing stdout

    std::cout << "1. Captured." << std::endl;
    printf("2. Captured.\n");

    std::string captured = capture.stop();      // stop capturing stdout

    // Print captured output to console
    printf("Captured output:\n%s", captured.c_str());
    

    return 0;
}



/*
SAMPLE OUTPUT:


eRCaGuy_hello_world$ cpp/stdout_capture.cpp 
1. This goes to console.
2. This goes to console.
Captured output:
1. Captured.
2. Captured.


*/
