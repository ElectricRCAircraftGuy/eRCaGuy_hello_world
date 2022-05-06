/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
May 2022

Write some basic functions to do REST API POST and GET calls using libcurl in C.

Note: using a manual, static response buffer in C (see `buffer_t` below) was a pain in the butt!
BUT, it _is_ real-time and safe for safety-critical systems! If using C++ in the future, on NON
real-time and NON safety-critical systems in the future, use a `std::string` (or `std::vector` if
using `uint8_t` types) as that would allow automatic dynamic memory allocation and growth
under-the-hood and be **much** easier to implement! Anyway though, what I have done here is correct
and works well, albeit it took a little extra effort.

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
# THEN, build & run it like this: <=========
# In C:
time ( \
    time gcc -Wall -Wextra -Werror -O3 -std=c17 \
    curl_rest_api_http_post_and_get.c \
    -lcurl \
    -o bin/a \
) && time bin/a

# Note, to run the "simple GET" example (instead of this code), do the following.
# Here is that example: https://curl.se/libcurl/c/simple.html
time ( \
    time gcc -Wall -Wextra -Werror -O3 -std=c17 \
    curl/docs/examples/simple.c \
    -lcurl \
    -o bin/a \
) && time bin/a
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
#include <stdint.h>  // `uint8_t`, etc.
#include <stdio.h>
#include <string.h>


// See "utilities.h"
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

// --------------- buffer struct and functions start ---------------

typedef struct buffer_s
{
    /// ptr to a buffer
    char * buf;
    /// total number of bytes in the buffer
    size_t len_total;
    /// the next write location (index) to write to in the buffer; set to zero to "reset" or clear"
    /// the buffer of all data
    size_t i_write;
} buffer_t;

/// Reset/clear the buffer in preparation for another operation on it. Any data already in the
/// buffer will now be lost.
void buffer_reset(buffer_t* buffer)
{
    buffer->i_write = 0;
}

/// Get the number of remaining (unused) bytes in the buffer.
size_t buffer_get_num_bytes_remaining(const buffer_t* buffer)
{
    size_t num_bytes_remaining = buffer->len_total - buffer->i_write;
    return num_bytes_remaining;
}

/// Write `num_bytes` bytes from `from_buffer` into `to_buffer`, returning the number of bytes
/// actually written, since it could be less than `num_bytes` if the `to_buffer` is too small.
size_t buffer_write_bytes(buffer_t* to_buffer, const char* from_buffer, size_t num_bytes)
{
    size_t num_bytes_remaining = buffer_get_num_bytes_remaining(to_buffer);
    // do `- 1` to save room for a null terminator at the very end of the string
    size_t num_bytes_to_write = MIN(num_bytes_remaining - 1, num_bytes);
    if (num_bytes_to_write < num_bytes)
    {
        printf("WARNING: destination buffer is too small to hold all of the data. "
               "num_bytes_remaining = %zu; to_buffer->len_total = %zu; "
               "num_bytes_to_write = %zu; num_bytes desired to be written = %zu.\n",
               num_bytes_remaining, to_buffer->len_total, num_bytes_to_write, num_bytes);
    }

    memcpy(&to_buffer->buf[to_buffer->i_write], from_buffer, num_bytes_to_write);
    to_buffer->i_write += num_bytes_to_write;
    size_t num_bytes_written = num_bytes_to_write;

    return num_bytes_written;
}

// --------------- buffer struct and functions end -----------------

typedef struct curl_data_s
{
    /// curl_easy handle; NB: this handle can only be used by **one thread at a time!** That means
    /// that if you want to have a multi-threaded program with multiple `curl_easy_perform()`
    /// operations going on at the same time, you need to re-architect this code to have
    /// **one curl easy handle** per thread!
    /// See: https://curl.se/libcurl/c/curl_easy_perform.html
    /// > If you want parallel transfers, you must use several curl easy_handles.
    CURL* curl_easy;
} curl_data_t;

// global variables
curl_data_t g_curl_data =
{
    .curl_easy = NULL,
};

/// A set-up function to be run once by the main thread at the start of `main()` BEFORE any other
/// threads have been started! This function is NOT thread-safe because it calls
/// `curl_global_init()`, which is NOT thread-safe! See:
/// https://curl.se/libcurl/c/curl_global_init.html
/// - Also, you must have **one curl easy handle** per parallel call to `curl_easy_perform()`.
///   Since I only have one curl easy handle, I can only have one thread using it at a time.
///   See: https://curl.se/libcurl/c/curl_easy_perform.html
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

/// \brief          The callback function which writes data received from the curl operation.
/// \details        This is the `curl_easy_setopt()` `CURLOPT_WRITEFUNCTION` function callback which
///     gets calls to write data received from the curl operation during `curl_easy_perform()`.
///     See: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
///     This callback signature is essentially created by curl to be modeled after the
///     `fwrite()` function. See:
///     1. https://www.cplusplus.com/reference/cstdio/fwrite/
///     1. https://en.cppreference.com/w/c/io/fwrite
/// \param[in]      received_data        The buffer of data arriving from the curl operation, which
///                     this function must handle.
/// \param[in]      size                 The size of a byte--will always be 1. This oddity of
///                     having this even be an input parameter at all seems to be that this callback
///                     function prototype is modeled after the `fwrite()` function in C which
///                     writes to a file: https://en.cppreference.com/w/c/io/fwrite.
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
    size_t num_bytes_written = buffer_write_bytes(write_buffer, received_data, count);

    return num_bytes_written;
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
CURLcode http_get(const char* url, char* response_buf, size_t response_len)
{
    CURLcode curl_code;
    buffer_t response_buffer; // buffer in which the response will be stored

    // Reset all previously-set options for this handle so that subsequent calls to this function
    // will start fresh. Otherwise, if you pass in `response_buf` once, then options
    // `CURLOPT_WRITEFUNCTION` and `CURLOPT_WRITEDATA` will get set below, and will remain set
    // even during subsequent calls when you pass in `NULL` for `response_buf`! That is NOT the
    // desired behavior, so we must reset the options and start fresh on this handle each time
    // we begin this function.
    // See info. about `curl_easy_reset()` here:
    // 1. https://curl.se/libcurl/c/libcurl-easy.html
    // 1. https://curl.se/libcurl/c/curl_easy_reset.html
    curl_easy_reset(g_curl_data.curl_easy); // Note: no return code to check

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
        // This call always succeeds and returns `CURLE_OK`.
        // See: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
        curl_easy_setopt(g_curl_data.curl_easy, CURLOPT_WRITEFUNCTION, write_callback);

        response_buffer.buf = response_buf;
        response_buffer.len_total = response_len;
        response_buffer.i_write = 0; // reset
        // This call always succeeds and returns `CURLE_OK`.
        // See: https://curl.se/libcurl/c/CURLOPT_WRITEDATA.html
        curl_easy_setopt(g_curl_data.curl_easy, CURLOPT_WRITEDATA, &response_buffer);
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

    // ensure null termination of the entire string
    if (response_buf != NULL && response_len > 0)
    {
        response_buffer.buf[response_buffer.i_write] = '\0';
    }

    // // debug prints
    // printf("==== LAST 3 BYTES: %u %u %u %u %u ====\n",
    //     (uint8_t)response_buffer.buf[response_buffer.i_write - 2],
    //     (uint8_t)response_buffer.buf[response_buffer.i_write - 1],
    //     (uint8_t)response_buffer.buf[response_buffer.i_write - 0],
    //     (uint8_t)response_buffer.buf[response_buffer.i_write + 1],
    //     (uint8_t)response_buffer.buf[response_buffer.i_write + 2]);
    // printf("==== LAST several chars: `%s` ====\n",
    //     &response_buffer.buf[response_buffer.i_write - 5]);

    return curl_code;
}

int main(void)
{
    CURLcode curl_code;

    // 1. set_up()
    curl_code = set_up();
    if (curl_code != CURLE_OK)
    {
        printf("ERROR: set_up() failed. curl_code = %i: %s\n",
                curl_code, curl_easy_strerror(curl_code));
        return curl_code;
    }

    static char response_buffer[CURL_MAX_WRITE_SIZE];
    static_assert(sizeof(response_buffer) == CURL_MAX_WRITE_SIZE, "just for a sanity check");

    // 2. http_get(), collecting the response
    printf("==== 1. ==== Calling http_get() WITH a response buffer to manually "
           "collect the response.\n");
    curl_code = http_get("www.example.com", response_buffer, sizeof(response_buffer));
    if (curl_code != CURLE_OK)
    {
        printf("ERROR: http_get() failed. curl_code = %i: %s\n",
                curl_code, curl_easy_strerror(curl_code));
    }
    else
    {
        printf("--- SUCESS! ---\n");
        printf("=== response_buffer START ===\n"
               "%s\n"
               "=== response_buffer END ===\n\n",
               response_buffer);
    }

    // 3. http_get(), NOT collecting the response
    printf("==== 2. ==== Calling http_get() withOUT a response buffer to manually "
           "collect the response. Therefore, the output will be **automatically written** "
           "to `stdout`!\n");
    curl_code = http_get("www.example.com", NULL, 0);
    if (curl_code != CURLE_OK)
    {
        printf("ERROR: http_get() failed. curl_code = %i: %s\n",
                curl_code, curl_easy_strerror(curl_code));
        return curl_code;
    }
    else
    {
        printf("--- SUCESS! ---\n");
    }

    // 4. http_post()

    // 5. tear_down()
    tear_down();

    return 0;
}




/*
SAMPLE OUTPUT:





Command-line equivalent command and output:




*/
