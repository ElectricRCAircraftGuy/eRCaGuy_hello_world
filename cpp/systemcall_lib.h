/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
May 2022

A simple Linux C++ system call library to allow you to easily make system calls and read back the
response through a pipe.

TODO:
1.

STATUS: done and works!

To compile and run:
- See a file which includes this header file, as an example.

References:
1. System call and pipe examples:
   1. *****+ "eRCaGuy_hello_world/c/read_system_call_via_pipe__keypress.c"
   1. ***** "eRCaGuy_hello_world/c/read_system_call_via_pipe__arrow_keypresses.c" - example of
      using a pipe with `popen()` to read back the response from a system call in C or C++

*/


#pragma once

// Local includes
// NA

// 3rd-party library includes
// NA

// Linux includes
// NA

// C and C++ includes
#include <string>


namespace systemcall
{

/// error code indicating no error
constexpr char ERROR_OK[] = "OK";

/// \brief          Call system call `cmd`, optionally reading back the response into
///      `response_str`.
/// \details        This is the equivalent of calling `cmd` at the command-line.
/// \param[in]      cmd             A null-terminated command string to call as though at the
///                     command-line.
/// \param[out]     response_str    (Optional) A pointer to a `std::string` to receive the
///                     command's `stdout` response back, if desired.
/// \param[out]     cmd_retcode     (Optional) A pointer to receive the command's return error code
///                     back, if desired.
/// \return         An error string to describe the error if there is an error, or
///                 `ERROR_OK` otherwise.
std::string system_call(const char* cmd, std::string* response_str = nullptr,
   int* cmd_retcode = nullptr);

/// Same as above, but withOUT using `goto` in the implementation, to appease those you may work
/// with who don't understand the virtues and benefits of a properly-used `goto` error-handling
/// pattern. See my arguments and demo here--especially the links at the end of my answer!:
/// https://stackoverflow.com/a/54488289/4561887; and:
/// https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/Research_General/goto_for_error_handling_in_C/readme.md
std::string system_call2(const char* cmd, std::string* response_str = nullptr,
   int* cmd_retcode = nullptr);

} // namespace systemcall

