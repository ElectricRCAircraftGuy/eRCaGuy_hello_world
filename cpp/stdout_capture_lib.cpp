/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
*/

// Primary include
#include "stdout_capture_lib.hpp"

// Local includes
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


// Start capturing stdout into a string stream.
// - This will redirect all `std::cout` AND `printf()` output to a temporary file.
void StdoutCapture::start() 
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
std::string StdoutCapture::stop()
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
