/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
May 2022

This is a basic C++ library to wrap the `libcurl` C library (https://curl.se/libcurl/c/) in a C++
class for easier usage in C++. It uses libcurl to implement the HTTP REST API GET and POST commands.

TODO:
1. NA

STATUS: wip; pretty much done--just need to finalize it and write "curl_lib_unittest.cpp" and fully
test this!

To compile and run:
- See a file which includes this header file, as an example. Ex: "cpp/curl_lib_unittest.cpp"

References:
1. *****libcurl official pages: The libcurl API: https://curl.se/libcurl/c/
1. "eRCaGuy_hello_world/cpp/curl_rest_api_http_post_and_get.c" - great example of the
   libcurl C library
1. "curl_systemcall_lib.h/.cpp"
1. "systemcall_lib.h/.cpp"


*/


#pragma once

// Local includes
// NA

// 3rd-party library includes
#include <curl/curl.h>

// Linux includes
// NA

// C and C++ includes
#include <string>


namespace curl
{

/// Generic error codes that may be encountered
enum class Error_code
{
    /// No error
    OK = 0,

    /// Generic error: any type of error not covered by the codes below.
    GENERIC,

    /// Invalid argument
    INVALID_ARG,

    /// Out of dynamic memory (heap)
    NO_MEMORY,

    /// Any type of input/output error, such as from files, pseudo-files (pipes, sysfs
    /// filesystem, GPIO pin pseudo-files, etc.)
    IO,

    /// Operation timed out
    TIMEOUT,
}

struct Error
{
    /// constructor: creates an `Error` object from an error code and error message.
    Error(Error_code error_code_in, const std::string& error_msg_in);

    /// default constructor
    Error();

    /// destructor
    ~Error();

    /// Construct and return an "OK" `Error` status struct.
    static Error Ok();

    Error_code error_code = Error_code::OK;
    std::string error_msg;
}

/// This is a class to wrap the C libcurl library and perform curl operations such as GET and
/// POST in C++.
///
/// NB: each instance of this class owns its own `CURL*` curl easy handle. You need to
/// construct one instance of this class per thread which desires to perform parallel libcurl
/// operations, since a "curl easy handle" can only be in-use by a single thread at any one time.
/// See: https://curl.se/libcurl/c/curl_easy_perform.html
/// > If you want parallel transfers, you must use several curl easy_handles.
///
///     The general usage of an instance of this class would look like this (plus you need to add
///     error handling).
///
///     NB: If you want to have simultaneous curl operations in multiple threads, use one `Curl`
///     object per thread. The global setup and global teardown functions still need to be
///     called only *once* for the whole program, however, regardless of how many threads and
///     `Curl` class objects you have.
///
///     ```cpp
///     main() {
///         // once at start of main
///         curl::Curl::global_set_up();
///
///         // ------- anywhere start ----------
///         curl::Curl curl;
///         curl.local_set_up();
///
///         // call as often as you need
///         curl.http_get(...);
///         curl.http_post(...);
///
///         curl.local_tear_down();
///         // ------- anywhere end ------------
///
///         // once at end of main
///         curl::Curl::global_tear_down();
///     }
///     ```
class Curl {
public:
    /// constructor
    Curl();

    /// destructor
    ~Curl();

    /// A global set-up function which must be called once **per program** at the start of
    /// `main()` **before** any other threads have been started. This function is NOT
    /// thread-safe since it calls `curl_global_init()`, which is NOT thread-safe! See:
    /// https://curl.se/libcurl/c/curl_global_init.html
    static Error global_set_up();

    /// A global teardown function to be called once **per program** at the end of `main()`,
    /// as part of the global cleanup, **after** all other threads have been terminated and
    /// joined back to the main thread. This function is NOT thread-safe because it
    /// calls `curl_global_cleanup()`, which is NOT thread-safe! See:
    /// https://curl.se/libcurl/c/curl_global_cleanup.html
    static void global_tear_down();

    /// Set up just this object. Call this once before any call to `http_get()` or `http_post()`
    /// on this object.
    Error local_set_up();

    /// Release curl resources for this object. Call this once when totally done with the object
    /// in order to prevent memory leaks. Once it has been called, you must no longer call
    /// `http_get()` or `http_post()` on this object.
    void local_tear_down();

    /// \brief          Call an HTTP GET REST API command. This is roughly equivalent to:
    ///     `curl -X GET "https://example.com"`, where the `url` is "https://example.com".
    /// \param[in]      url            A null-terminated C-string to the URL to communicate with.
    /// \param[out]     response_str    (Optional) the string to write the HTTP GET response into.
    ///                     Pass in nullptr to not use this parameter, in which case the output
    ///                     will be written to `stdout` instead.
    /// \return         The `Error` status.
    Error http_get(const char* url, std::string* response_str = nullptr);

    /// \brief          Call an HTTP POST REST API command. This is roughly equivalent to:
    ///     `curl --data "var1=foo&var2=bar" -X POST "https://example.com"`, where the `url` is
    ///     "https://example.com" and the `post_str` is the data: `"var1=foo&var2=bar"`.
    /// \param[in]      url            A null-terminated C-string to the URL to communicate with.
    /// \param[in]      post_str       The data string to post--ie: send to the URL. Use an empty
    ///                                string if there is no data to post.
    /// \param[out]     response_str    (Optional) the string to write the response into.
    ///                     Pass in nullptr to not use this parameter, in which case the output
    ///                     will be written to `stdout` instead.
    /// \return         The `Error` status.
    Error http_post(const char* url, const std::string& post_str,
        std::string* response_str = nullptr);

private:
    /// A "curl easy handle" object required to use the easy interface to libcurl.
    CURL* curl_easy_handle_;
};

} // namespace curl

