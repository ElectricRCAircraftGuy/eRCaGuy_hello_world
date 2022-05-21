/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

See the .h file for details.

References:
1. ***** Great `popen()` demos!:
    1. *****https://stackoverflow.com/a/28971647/4561887
    1. *****https://stackoverflow.com/a/18297075/4561887
1. https://man7.org/linux/man-pages/man3/popen.3.html
1. https://linux.die.net/man/3/popen
1. https://en.cppreference.com/w/c/io/fread
1. ***** fread and ferror don't set errno: https://stackoverflow.com/a/40215174/4561887
1. https://en.cppreference.com/w/cpp/string/basic_string/reserve
1. https://en.cppreference.com/w/cpp/string/basic_string/append
1. https://en.cppreference.com/w/c/io/fgets - alternative to `fread()`, for char/C-string data
1. "read_stdin_fgets_basic_input_from_user.c"
1. "eRCaGuy_hello_world/c/read_system_call_via_pipe__arrow_keypresses.c" - example of using a pipe
   with `popen()` to read back the response from a system call in C or C++
1. *****+ "eRCaGuy_hello_world/c/read_system_call_via_pipe__keypress.c"

*/


// Local includes
#include "curl_syscall_lib.h"

// 3rd-party library includes
#include <fmt/format.h>

// Linux includes
// NA

// C and C++ includes
#include <cstdint>
#include <cstdio> // `popen()`


namespace curl_syscall
{

std::string http_post(const char* url, const char* post_str, std::string* response_str = nullptr)
{
    std::string error = ERROR_OK;

    std::string cmd = fmt::format(FMT_STRING("curl --data \"{}\" -X POST \"{}\""), post_str, url);

    FILE *pipe = popen(cmd.c_str(), "r");
    if (pipe == nullptr)
    {
        error = fmt::format(FMT_STRING("Failed to open pipe. errno = {}: {}"),
            errno, strerror(errno));
        goto done;
    }

    if (responseStr == nullptr)
    {
        // skip reading the response back from the system call
        goto close;
    }

    constexpr size_t BUFSIZE = 4096;
    uint8_t buf[BUFSIZE];

    // pre-reserve some space to avoid having the string dynamically allocate memory
    // under-the-hood for response strings <= BUFSIZE in length; this improves speed; see:
    // https://github.com/facontidavide/CPP_Optimizations_Diary/blob/master/docs/reserve.md
    response_str->reserve(BUFSIZE);

    size_t num_bytes_read = sizeof(buf); // initialize as necessary to enter the while loop
    while (num_bytes_read == sizeof(buf))
    {
        size_t num_bytes_read = fread(buf, 1, sizeof(buf), pipe);
        response_str->append(buf, num_bytes_read);
    }
    // check for errors
    // NB: `fread()` and `ferror()` do NOT set `errno`! You don't get that level of granularity.
    // See:
    // 1. *****fread and ferror don't set errno: https://stackoverflow.com/a/40215174/4561887
    // 1. https://man7.org/linux/man-pages/man3/fread.3.html
    // 1. https://man7.org/linux/man-pages/man3/ferror.3.html
    if (ferror(pipe))
    {
        error = "Error indicator set. IO error occurred when reading from pipe.";
        goto close;
    }
    if (feof(pipe))
    {
        // end of file reached successfully; nothing to do
    }

close:
    int retval = pclose(pipe);
    if (retval == -1)
    {
        error = fmt::format(FMT_STRING("Failed to close pipe. Therefore: could not obtain the "
            "system call's exit status code. errno = {}: {}"), errno, strerror(errno));
        goto done;
    }
    else if (retval != 0)
    {
        error = fmt::format(FMT_STRING("Command exited with error status exit code {}."), retval);
        // no need to `goto done`; the pipe functioned correctly; the cmd failed, is all
    }

done:
    return error;
}

} // namespace curl_syscall
