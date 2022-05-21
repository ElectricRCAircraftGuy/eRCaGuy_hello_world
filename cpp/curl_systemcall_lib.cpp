/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

See the .h file for details.

References:
1. "systemcall_lib.h/.cpp"
1.

*/


// Local includes
#include "curl_systemcall_lib.h"
#include "systemcall_lib.h"

// 3rd-party library includes
#include <fmt/format.h>

// Linux includes
// NA

// C and C++ includes
#include <cstdint>
#include <cstdio> // `popen()`


namespace curl_systemcall
{

std::string http_post(const char* url, const char* post_str, std::string* response_str)
{
    std::string error = ERROR_OK;

    if (url == nullptr || post_str == nullptr)
    {
        error = "INVALID ARGUMENT: nullptr";
        return error;
    }

    int cmd_return_code;
    std::string cmd = fmt::format(FMT_STRING("curl --data \"{}\" -X POST \"{}\""), post_str, url);

    error = systemcall::system_call(cmd.c_str(), response_str, &cmd_return_code);
    if (error != ERROR_OK)
    {
        error = fmt::format(FMT_STRING("Curl system call failed: error msg: \"{}\"; "
            "cmd_return_code: {}."), error, cmd_return_code);
    }

    return error;
}

} // namespace curl_systemcall
