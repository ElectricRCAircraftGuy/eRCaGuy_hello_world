/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
May 2022

This is a basic Linux C++ library to wrap the command-line `curl` call into a C++ function, using a
system call via a pipe (with `popen()`) so I can read back the response.

NB: an alternative would be to write a C++ wrapper around the C library, `libcurl`, but I'll do that
in another file and example instead, so I can compare the two options, including speed!

TODO:
1.

STATUS: wip

To compile and run:
- See a file which includes this header file, as an example.

References:
1. "eRCaGuy_hello_world/cpp/curl_rest_api_http_post_and_get.c" - great example of the
   libcurl C library
1. "eRCaGuy_hello_world/c/read_system_call_via_pipe__arrow_keypresses.c" - example of using a pipe
   with `popen()` to read back the response from a system call in C or C++
1. *****+ "eRCaGuy_hello_world/c/read_system_call_via_pipe__keypress.c"

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


namespace curl_systemcall
{

/// error code indicating no error
constexpr char ERROR_OK[] = "ok";

/// \brief          Send an HTTP REST API POST command.
/// \details        This is essentially equivalent to the following command-line command:
///     `curl --data "post_str" -X POST "url"`. Ex:
///     `curl --data "name=Gabe&project=curl" -X POST "https://example.com"`.
/// \param[in]      url             A null-terminated URL to send the POST command to.
/// \param[in]      post_str        A null-terminated string containing the data to post, or send
///     to the URL.
/// \param[out]     response_str    (Optional) A string to receive the response in, if desired.
/// \return         An error string to describe the error if there is an error, or
///                 `ERROR_OK` otherwise.
std::string http_post(const char* url, const char* post_str, std::string* response_str = nullptr);

/// Same as above, but withOUT using `goto` in the implementation.
std::string http_post2(const char* url, const char* post_str, std::string* response_str = nullptr);

} // namespace curl_systemcall

