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
#include <fstream>
#include <unistd.h>  // For `dup()`, `dup2()`, `close()`

class StdoutCapture 
{
public: 
    // Start capturing stdout into a string stream.
    // - This will redirect all `std::cout` AND `printf()` output to a temporary file.
    void start() 
    {
        // Flush any pending output
        fflush(stdout);
        
        // Save original stdout file descriptor
        stdout_fd_backup_ = dup(STDOUT_FILENO);
        
        // Create a temporary file
        temp_file_ = tmpfile();
        if (!temp_file_) {
            perror("tmpfile");
            return;
        }
        
        // Redirect stdout to the temporary file
        dup2(fileno(temp_file_), STDOUT_FILENO);
        
        // Also redirect C++ cout to the same file
        cout_bak_ = std::cout.rdbuf();
        std::cout.rdbuf(std::cout.rdbuf());  // This keeps cout synced with stdout
    }

    // Stop capturing stdout and restore original stdout.
    // - This will restore both `std::cout` and `printf()` to their original state.
    // - Returns the captured output as a string.
    std::string stop()
    {
        // Flush any remaining output
        fflush(stdout);
        
        // Restore original stdout file descriptor
        dup2(stdout_fd_backup_, STDOUT_FILENO);
        close(stdout_fd_backup_);
        
        // Read from the temporary file
        std::string result;
        if (temp_file_) {
            rewind(temp_file_);
            
            char buffer[4096];
            while (fgets(buffer, sizeof(buffer), temp_file_)) {
                result += buffer;
            }
            
            fclose(temp_file_);
            temp_file_ = nullptr;
        }
        
        return result;
    }

private:
    // Original stdout file descriptor backup
    int stdout_fd_backup_ = -1;
    // Temporary file for capturing output
    FILE* temp_file_ = nullptr;
    // Original cout buffer (not used in this approach, but kept for completeness)
    std::streambuf* cout_bak_ = nullptr;
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
