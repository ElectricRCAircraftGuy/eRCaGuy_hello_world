/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

See the .h file for details.

References:
1. NA

*/


// Local includes
#include "curl_lib.h"

// 3rd-party library includes
#include <fmt/format.h>

// Linux includes
// NA

// C and C++ includes
// NA


namespace curl {

Error::Error(Error_code error_code_in, const std::string& error_msg_in)
{
    error_code = error_code_in;
    error_msg = error_msg_in;
}

Error::Ok()
{
    // Note: the default constructor defaults to `Error_code::OK` and an empty `error_msg` string.
    Error error_ok = Error();
    return error_ok;
}

Curl::Curl() {}

Curl::~Curl() {}

Error Curl::global_set_up() {
    CURLcode curl_code = CURLE_OK;

    curl_code = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (curl_code != CURLE_OK) {
        return Error(Error_code::GENERIC, fmt::format(
                FMT_STRING("curl_global_init() failed. curl_code = {}: {}"),
                curl_code,
                curl_easy_strerror(curl_code)));
    }

    return Error::Ok();
}

void Curl::global_tear_down() {
    curl_global_cleanup();
}

Error Curl::local_set_up() {
    curl_easy_handle_ = curl_easy_init();
    if (curl_easy_handle_ == nullptr) {
        return Error(Error_code::GENERIC,
                fmt::format(FMT_STRING("curl_easy_init() failed.")));
    }

    return Error::Ok();
}

void Curl::local_tear_down() {
    curl_easy_cleanup(curl_easy_handle_);
}

/// \brief          The callback function which writes data received from the curl operation.
/// \details        This is the `curl_easy_setopt()` `CURLOPT_WRITEFUNCTION` function callback
///     which gets calls to write data received from the curl operation during
///     `curl_easy_perform()`. See: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
///     This callback signature is modeled after `fwrite()`:
///     1. https://www.cplusplus.com/reference/cstdio/fwrite/
///     2. https://en.cppreference.com/w/c/io/fwrite
/// \param[in]      received_data         The buffer of data arriving from the curl operation,
///                     which this function must handle.
/// \param[in]      size                 The size of a byte--will always be 1.
/// \param[in]      count                The number of bytes in the `received_data` buffer which
///                     are ready to be processed.
/// \param[in,out]  user_data            Any special data you'd like to pass in to the function.
///                     This data is passed in via a call to
///                     `curl_easy_setopt(handle, CURLOPT_WRITEDATA, ptr)`.
///                     See: https://curl.se/libcurl/c/CURLOPT_WRITEDATA.html
///                     In this case, it is the destination `std::string*` response string to
///                     write data into.
/// \return         The number of bytes from `received_data` actually written.
static size_t write_callback(const char* received_data, size_t size, size_t count, void* user_data) {
    // curl documentation says `size` is always 1; prove it; see:
    // https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
    assert(size == 1);

    std::string* response_str = reinterpret_cast<std::string*>(user_data);

    response_str->append(received_data, count);
    size_t num_bytes_written = count;

    return num_bytes_written;
}

Error Curl::http_get(const char* url, std::string* response_str) {
    CURLcode curl_code;

    curl_code = curl_easy_setopt(curl_easy_handle_, CURLOPT_URL, url);
    if (curl_code != CURLE_OK) {
        curl_easy_reset(curl_easy_handle_);  // Note: no return code to check
        return Error(Error_code::GENERIC, fmt::format(
                FMT_STRING("curl_easy_setopt() failed on `CURLOPT_URL`. curl_code = {}: {}"),
                curl_code,
                curl_easy_strerror(curl_code)));
    }

    // Only write the data into the response string if the user desires it and has passed in a
    // response string. Otherwise, let curl write to `stdout`, which is the default.
    if (response_str != nullptr) {
        // For efficiency, we pre-reserve the maximum number of bytes which might be written into
        // the string, since otherwise dynamic memory allocation will repeatedly occur as the
        // string grows. `CURL_MAX_WRITE_SIZE` is the maximum size `curl` will try to write. That
        // curl macro is usually ~16 KiB.
        response_str->reserve(CURL_MAX_WRITE_SIZE);

        // This call always succeeds and returns `CURLE_OK`.
        // See: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
        curl_easy_setopt(curl_easy_handle_, CURLOPT_WRITEFUNCTION, write_callback);

        // This call always succeeds and returns `CURLE_OK`.
        // See: https://curl.se/libcurl/c/CURLOPT_WRITEDATA.html
        curl_easy_setopt(curl_easy_handle_, CURLOPT_WRITEDATA, response_str);
    }

    // Perform the curl request/operation. See:
    // https://curl.se/libcurl/c/curl_easy_perform.html
    curl_code = curl_easy_perform(curl_easy_handle_);
    if (curl_code != CURLE_OK) {
        curl_easy_reset(curl_easy_handle_);  // Note: no return code to check
        return Error(Error_code::GENERIC, fmt::format(
                FMT_STRING("curl_easy_perform() failed. curl_code = {}: {}"),
                curl_code,
                curl_easy_strerror(curl_code)));
    }

    return Error::Ok();
}

Error
Curl::http_post(const char* url, const std::string& post_str, std::string* response_str) {
    CURLcode curl_code;

    // This call always succeeds and returns `CURLE_OK`.
    // See: https://curl.se/libcurl/c/CURLOPT_POSTFIELDS.html
    curl_easy_setopt(curl_easy_handle_, CURLOPT_POSTFIELDS, post_str.c_str());

    curl_code = curl_easy_setopt(curl_easy_handle_, CURLOPT_POSTFIELDSIZE, (long)post_str.size());
    if (curl_code != CURLE_OK) {
        curl_easy_reset(curl_easy_handle_);  // Note: no return code to check
        return Error(Error_code::GENERIC, fmt::format(
                FMT_STRING(
                        "curl_easy_setopt() failed on `CURLOPT_POSTFIELDSIZE`. curl_code = {}: {}"),
                curl_code,
                curl_easy_strerror(curl_code)));
    }

    Error status = http_get(url, response_str);
    if (!status.isOk()) {
        return status;
    }

    return Error::Ok();
}

}  // namespace curl
