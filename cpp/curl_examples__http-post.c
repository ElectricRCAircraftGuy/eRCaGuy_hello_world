/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
May 2022

Test the libcurl example "http-post.c". See references below for links to it.
This C code is essentially the equivalent of this command-line curl command!:

    curl -d "name=daniel&project=curl" -X POST "http://postit.example.com/moo.cgi"

See: https://www.educative.io/edpresso/how-to-perform-a-post-request-using-curl

STATUS: done & works!

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
    curl_examples__http-post.c \
    -lcurl \
    -o bin/a \
) && time bin/a
```

References:
1. libcurl example "http-post.c":
    1. Local: "eRCaGuy_hello_world/cpp/curl/docs/examples/http-post.c"
    1. Online: https://curl.se/libcurl/c/http-post.html
1. How to perform a POST request using Curl:
   https://www.educative.io/edpresso/how-to-perform-a-post-request-using-curl

*/

/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2020, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * simple HTTP POST using the easy interface
 * </DESC>
 */
#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
  CURL *curl;
  CURLcode res;

  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
    curl_easy_setopt(curl, CURLOPT_URL, "http://postit.example.com/moo.cgi");
    /* Now specify the POST data */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}




/*
SAMPLE OUTPUT:
Not a valid post URL, so this error is expected.


    eRCaGuy_hello_world/cpp$ time ( \
    >     time gcc -Wall -Wextra -Werror -O3 -std=c17 \
    >     curl_examples__http-post.c \
    >     -lcurl \
    >     -o bin/a \
    >     && time bin/a \
    > )

    real    0m0.098s
    user    0m0.044s
    sys 0m0.032s
    curl_easy_perform() failed: Couldn't resolve host name

    real    0m0.283s
    user    0m0.000s
    sys 0m0.005s

    real    0m0.381s
    user    0m0.044s
    sys 0m0.037s


Command-line equivalent command and output:

    eRCaGuy_hello_world/c$ curl -d "name=daniel&project=curl" -X POST "http://postit.example.com/moo.cgi"
    curl: (6) Could not resolve host: postit.example.com

*/
