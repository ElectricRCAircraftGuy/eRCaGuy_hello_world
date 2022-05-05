/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
May 2022

Write some basic functions to do REST API POST and GET calls using libcurl in C.

Example command-line alternatives to this C program:

    # GET

    curl "https://example.com"
    # OR_ (same thing):
    curl -X GET "https://example.com"

    # POST

    curl --data "moo mooo moo moo" -X POST "https://example.com"

From `man curl`:

       -d, --data <data>
              (HTTP)  Sends  the specified data in a POST request to the HTTP server, in the same
              way that a browser does when a user has filled in an HTML form and presses the submit
              button. This will cause curl to pass the data to the server  using  the  con‐
              tent-type application/x-www-form-urlencoded.  Compare to -F, --form.

See also: https://www.educative.io/edpresso/how-to-perform-a-post-request-using-curl


STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# FIRST, follow the curl installation & setup instructions here: "eRCaGuy_hello_world/cpp/README.md"
# THEN, build & run it like this:
# In C:
time ( \
    time gcc -Wall -Wextra -Werror -O3 -std=c17 \
    curl_rest_api_http_post_and_get.c \
    -lcurl \
    -o bin/a \
    && time bin/a \
)
```

References:
1. libcurl example "simplepost.c":
    1. Local: "eRCaGuy_hello_world/cpp/curl/docs/examples/simplepost.c"
    1. Online: https://curl.se/libcurl/c/simplepost.html
1. How to perform a POST request using Curl:
   https://www.educative.io/edpresso/how-to-perform-a-post-request-using-curl
1. ***** Basic HTTP GET example: https://curl.se/libcurl/c/simple.html
1. ***** Basic HTTP POST example: https://curl.se/libcurl/c/simplepost.html
1. https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
1. https://curl.se/libcurl/c/curl_easy_strerror.html
1. A good example with a write function example:
  `curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);`:
  https://curl.se/libcurl/c/ftpget.html

*/



// Local includes
// NA

// 3rd-party library includes
#include <curl/curl.h>

// C and C++ includes
#include <assert.h>
#include <stdio.h>
#include <string.h>


// See "utilities.h"
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct buffer_s
{
    // fixed values
    char * buf;  /// ptr to a buffer
    size_t len_total;  /// total number of bytes in the buffer

    // values which change as the buffer is written to
    // size_t len_remaining; /// number of unused bytes in the buffer ////////
    size_t i_write; /// the next write location in the buffer
} buffer_t;

typedef struct curl_data_s
{
    CURL* curl_easy; // curl_easy handle
} curl_data_t;

// global variables
curl_data_t g_curl_data =
{
    .curl_easy = NULL,
};

/// Reset/clear the buffer in preparation for another operation on it. Any data already in the
/// buffer will now be lost.
void reset_buffer(buffer_t* buffer)
{
    // buffer->len_remaining = buffer->len_total;////////
    buffer->i_write = 0;
}

/// A set-up function to be run once by the main thread at the start of `main()` BEFORE any other
/// threads have been started! This function is NOT thread-safe because it calls
/// `curl_global_init()`, which is NOT thread-safe! See:
/// https://curl.se/libcurl/c/curl_global_init.html
CURLcode set_up()
{
    CURLcode curl_code = CURLE_OK;

    // global init (must be called once in the whole program)
    curl_code = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (curl_code != CURLE_OK)
    {
        printf("ERROR: curl_global_init() failed. curl_code = %i: %s\n",
                curl_code, curl_easy_strerror(curl_code));
        return curl_code;
    }

    // easy init (must be called to obtain a handle for all other curl easy calls)
    g_curl_data.curl_easy = curl_easy_init();
    if (g_curl_data.curl_easy == NULL)
    {
        printf("ERROR: curl_easy_init() failed.\n");
        return CURLE_FAILED_INIT;
    }

    return curl_code;
}

/// A tear-down, or "un-set-up" function to be run by the main thread once at the end of `main()`
/// as part of the global cleanup, AFTER all other threads have been terminated and joined
/// back to the main thread. It is NOT thread-safe because it calls `curl_global_cleanup()`,
/// which is NOT thread-safe! See: https://curl.se/libcurl/c/curl_global_cleanup.html
void tear_down()
{
    curl_easy_cleanup(g_curl_data.curl_easy);
    curl_global_cleanup();
}

/// \brief          The callback function which writes data received from curl.
/// \details        This is the `curl_easy_setopt()` `CURLOPT_WRITEFUNCTION` function callback which
///     gets calls to write data received from the curl operation during `curl_easy_perform()`.
///                 See: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
///                 This callback signature is essentially created by curl to be modeled after the
///                 `fwrite()` function. See:
///                 1. https://www.cplusplus.com/reference/cstdio/fwrite/
///                 1. https://en.cppreference.com/w/c/io/fwrite
/// \param[in]      received_data        The buffer of data arriving from the curl operation, which
///                     this function must handle.
/// \param[in]      size                 The size of a byte--will always be 1. This oddity of
///                     having this even be an input parameter at all seems to be that this
///                     function is modeled after the `fwrite()` function in C which writes to
///                     a file: https://en.cppreference.com/w/c/io/fwrite.
///                     The 4 parameters to this write callback function could be made to
///                     **exactly mimic** the 4 parameters to `fwrite()` if desired.
/// \param[in]      count                The number of bytes in the `received_data` buffer which
///                     are ready to be processed.
/// \param[in,out]  user_data            Any special data you'd like to pass in to the function.
///                     This data is passed in via a call to
///                     `curl_easy_setopt(handle, CURLOPT_WRITEDATA, ptr)`.
///                     See: https://curl.se/libcurl/c/CURLOPT_WRITEDATA.html
///                     In this case, it is the destination buffer of type `buffer_t*` to
///                     write into.
/// \return         The number of bytes from `received_data` actually handled or processed.
size_t write_callback(const char *received_data, size_t size, size_t count, void *user_data)
{
    assert(size == 1); // the curl documentation states that `size` is always 1, so let's prove it

    buffer_t* write_buffer = (buffer_t*)user_data;
    size_t num_bytes_to_write = MIN(write_buffer->len, count);
    if (num_bytes_to_write < count)
    {
        printf("WARNING: output buffer is too small to hold all of the data. "
               "write_buffer->len = %zu; num_bytes_to_write = %zu; count of bytes desired "
               "to be written = %zu.\n",
               write_buffer->len, num_bytes_to_write, count);
        // do not return; we will write as many bytes as we can anyway
    }

    memcpy(write_buffer->buf, received_data, num_bytes_to_write); /////////// add bytes_used and i_write to the struct!

    return num_bytes_to_write;
}

/// \brief          Call an HTTP GET REST API command.
/// \details        This is roughly the equivalent of: `curl -X GET "https://example.com"`,
///                 where `url` is "https://example.com".
/// \param[in]      url             The URL to communicate with.
/// \param[out]     response_buf    (Optional) the buffer to write the response string into. Pass
///                     in NULL to not use this parameter, in which case the output will be
///                     written to `stdout` instead of into the `response_buf`.
/// \param[in]      response_len    The length of the response buffer. It is recommended to use
///                     a response buffer of size `CURL_MAX_WRITE_SIZE`, since that is the maximum
///                     size `curl` will try to write into the buffer. That curl macro is usually
///                     ~16 KiB.
/// \return         A curl error code:
///                 - #ENUM_VALUE_1////////
///                 - #ENUM_VALUE_2
///                 - #ENUM_VALUE_3
CURLcode http_get(const char* url, char* response_buf, size_t response_len)
{
    CURLcode curl_code;

    curl_code = curl_easy_setopt(g_curl_data.curl_easy, CURLOPT_URL, url);
    if (curl_code != CURLE_OK)
    {
        printf("ERROR: curl_easy_setopt() failed on `CURLOPT_URL`. curl_code = %i: %s\n",
                curl_code, curl_easy_strerror(curl_code));
        return curl_code;
    }

    // Only write the data into the response buffer if the user desires it and has passed in a
    // buffer. Otherwise, let curl write to `stdout`, which is the default.
    if (response_buf != NULL && response_len > 0)
    {
        curl_code = curl_easy_setopt(g_curl_data.curl_easy, CURLOPT_WRITEFUNCTION, write_callback);
        /////// error handling


        buffer_t write_buffer =
        {
            .buf = response_buf,
            .len = response_len
        };
        curl_code = curl_easy_setopt(g_curl_data.curl_easy, CURLOPT_WRITEDATA, &write_buffer);
        //// error handling
    }

    // Perform the curl request/operation. NB: this call is NOT thread-safe if using one
    // curl easy handle! You must use a separate easy handle per thread if you desire to do
    // multiple calls to `curl_easy_perform()` in parallel! See:
    // https://curl.se/libcurl/c/curl_easy_perform.html
    // > If you want parallel transfers, you must use several curl easy_handles.
    curl_code = curl_easy_perform(g_curl_data.curl_easy);
    if (curl_code != CURLE_OK)
    {
        printf("ERROR: curl_easy_perform() failed. curl_code = %i: %s\n",
                curl_code, curl_easy_strerror(curl_code));
        return curl_code;
    }

    return curl_code;
}

int main(void)
{
    CURLcode curl_code;

    curl_code = set_up();
    if (curl_code != CURLE_OK)
    {
        printf("ERROR: set_up() failed. curl_code = %i: %s\n",
                curl_code, curl_easy_strerror(curl_code));
        return curl_code;
    }

    static char response_buffer[CURL_MAX_WRITE_SIZE];
    // buffer_t response_buffer =
    // {
    //     .buf = buffer,
    //     .len = sizeof(buffer),
    // };
    static_assert(sizeof(response_buffer) == CURL_MAX_WRITE_SIZE, "sanity check");

    printf("Calling http_get() WITH a response buffer.\n");
    curl_code = http_get("www.example.com", response_buffer, sizeof(response_buffer));



    tear_down();

    return 0;
}




/*
SAMPLE OUTPUT:





Command-line equivalent command and output:




*/
