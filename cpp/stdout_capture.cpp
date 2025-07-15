///usr/bin/env ccache g++ -Wall -Wextra -Werror -O3 -std=gnu++17 "$0" -o /tmp/a && /tmp/a "$@"; exit
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


From GitHub Copilot; cleaned up by me:
DETAILED EXPLANATION OF dup() and dup2():

1. Initial state:
   fd 0 (stdin)  → keyboard
   fd 1 (stdout) → terminal
   fd 2 (stderr) → terminal

2. After: `stdout_fd_backup_ = dup(STDOUT_FILENO);`
   fd 0 (stdin)  → keyboard  
   fd 1 (stdout) → terminal
   fd 2 (stderr) → terminal
   fd 3 (backup) → terminal  ← NEW fd pointing to same terminal

3. After: `dup2(fileno(temp_file_), STDOUT_FILENO);` [format: from fd, to fd]
   fd 0 (stdin)  → keyboard
   fd 1 (stdout) → temp_file  ← REDIRECTED to temp file
   fd 2 (stderr) → terminal
   fd 3 (backup) → terminal   ← Still points to original terminal!

4. After: `dup2(stdout_fd_backup_, STDOUT_FILENO);` [format: from fd, to fd]
   fd 0 (stdin)  → keyboard
   fd 1 (stdout) → terminal   ← RESTORED to terminal
   fd 2 (stderr) → terminal
   fd 3 (backup) → terminal

5. After: `close(stdout_fd_backup_);`
   fd 0 (stdin)  → keyboard
   fd 1 (stdout) → terminal
   fd 2 (stderr) → terminal
   fd 3 (backup) → [closed]   ← Backup fd is closed, but the underlying terminal connection 
                                remains open since another fd (fd 1) still points to it.
                                See: https://linux.die.net/man/2/close: 
                                > If fd is the last file descriptor referring to the underlying 
                                  open file description (see open(2)), the resources associated 
                                  with the open file description are freed

Why this works:
- dup() creates a NEW file descriptor that refers to the same file.
- `dup2(oldfd, newfd)` atomically redirects an existing file descriptor (`newfd`) to a new file
  (`oldfd`) by copying the underlying file descriptor data structure from `oldfd` to `newfd`.
- The backup fd preserves the original terminal connection.
- We can restore stdout by copying the backup back to fd 1 via `dup2(fileno(stdout_backup_),
  STDOUT_FILENO)`.



References:
1. Grok AI: 
    1. Private link: https://grok.com/chat/356d87ac-b4c4-4bae-b13f-ffef0c75b9d9
    1. Public link: https://grok.com/share/bGVnYWN5_da25d90e-acf0-41f7-a128-feeb18e514a2
1. https://en.cppreference.com/w/cpp/io/cout.html
1. https://en.cppreference.com/w/cpp/io/basic_ios/rdbuf.html
1. https://en.cppreference.com/w/cpp/io/basic_ostream.htm

1. https://man7.org/linux/man-pages/man2/dup.2.html
1. https://linux.die.net/man/2/dup2
1. https://man7.org/linux/man-pages/man3/fflush.3.html
1. https://linux.die.net/man/2/close
1. https://en.cppreference.com/w/c/io/fseek
1. https://en.cppreference.com/w/c/io/ftell
1. https://en.cppreference.com/w/c/io/fgetc

*/



// Local includes/
// NA

// 3rd-party includes
// NA

// Linux/Unix includes
#include <unistd.h>  // For `dup()`, `dup2()`, `close()`

// C++ includes
#include <fstream>
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <sstream>
#include <string>

// C includes 
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <cstring>  // For `strerror()`


// Error code / invalid fd for file descriptor operations
constexpr int FILE_DESCRIPTOR_INVALID = -1; 

class StdoutCapture 
{
public: 
    // Start capturing stdout into a string stream.
    // - This will redirect all `std::cout` AND `printf()` output to a temporary file.
    void start() 
    {
        // Flush any pending output
        fflush(stdout);
        
        // Save original stdout file descriptor. 
        // - This does NOT just copy the file descriptor number, but rather duplicates the
        //   underlying file descriptor data structure containing the information about the file,
        //   so that now we have two unique file descriptor objects pointing to the same location
        //   in the file system.
        stdout_fd_backup_ = dup(STDOUT_FILENO);
        
        // Create a temporary file
        temp_file_ = tmpfile();
        if (!temp_file_) 
        {
            perror("tmpfile"); // GS: not required since the next line does nearly the same thing.
            printf("tmpfile() failed: %s\n", strerror(errno));
            return;
        }
        
        // Redirect stdout to the temporary file.
        // - Format: `dup2(old_fd [from fd], new_fd [to fd])`. 
        // - This will duplicate the underlying data structure of the file descriptor to the temp
        //   file, copying it into the file descriptor data structure for the `STDOUT_FILENO` file
        //   descriptor, thereby making the `STDOUT_FILENO` file descriptor now point to the
        //   temporary file instead of to the terminal.
        // - This automatically redirects BOTH `std::cout` AND `printf()` since they both 
        //   ultimately write to file descriptor `1` (`STDOUT_FILENO`).
        // - This doesn't just affect this program, but also any other programming running at this
        //   time in the same process, so that if you run `printf()` in another thread or process,
        //   even if in another language entirely, it will also write to the temporary file instead
        //   of to the terminal.
        dup2(fileno(temp_file_), STDOUT_FILENO);
    }

    // Stop capturing stdout and restore original stdout.
    // - This will restore both `std::cout` and `printf()` to their original state.
    // - Returns the captured output as a string.
    std::string stop()
    {
        // Flush any remaining output
        fflush(stdout);
        
        // Restore original stdout file descriptor
        dup2(stdout_fd_backup_, STDOUT_FILENO);  // copy the underlying data structure from, to
        close(stdout_fd_backup_);  // close the backup file descriptor while keeping the original
                                   // terminal connection open, since another fd (fd 1) still points
                                   // to it.
        
        // Read from the temporary file
        if (temp_file_) 
        {
            rewind(temp_file_);
            
            // Clear the read buffer for reuse
            read_buffer_.clear();
            
            // Get file size for efficient allocation
            // - Seek to 0 chars offset from the end of the file (`SEEK_END`)
            fseek(temp_file_, 0, SEEK_END);
            long file_size = ftell(temp_file_);
            rewind(temp_file_);
            
            // Read all chars from the file into the read buffer
            if (file_size > 0) 
            {
                // Reserve space for the entire file content
                read_buffer_.reserve(static_cast<size_t>(file_size));
                
                // Read the entire file into the string buffer
                char c;
                while ((c = fgetc(temp_file_)) != EOF) 
                {
                    read_buffer_.push_back(c);
                }
            }
            
            fclose(temp_file_);
            temp_file_ = nullptr;
        }
        
        return read_buffer_;
    }

private:
    // Original stdout file descriptor backup
    int stdout_fd_backup_ = FILE_DESCRIPTOR_INVALID;
    // Temporary file for capturing output
    FILE* temp_file_ = nullptr;
    // Read buffer - dynamically grows as needed, safer than fixed-size buffers
    std::string read_buffer_;
};

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
