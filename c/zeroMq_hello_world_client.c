/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
9 Apr. 2022

This is the basic ZeroMQ getting started **client** demo in C from
https://zeromq.org/get-started/?language=c#

STATUS: works! See Linux installation instructions for libzmq in the References below.

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 zeroMQ_hello_world_client.c -o bin/zmqclient -lm -lzmq && bin/zmqclient

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 zeroMQ_hello_world_client.c -o bin/zmqclient -lzmq && bin/zmqclient
```

References:
1. ZeroMQ getting started, in C: https://zeromq.org/get-started/?language=c#
1. Install ZeroMQ: https://zeromq.org/download/
    ```bash
    sudo apt update
    sudo apt install libzmq3-dev
    ```
1. Include the library when building, via `-lzmq`; see: https://stackoverflow.com/a/15312060/4561887

*/

//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char buffer [10];
        printf ("Sending Hello %d…\n", request_nbr);
        zmq_send (requester, "Hello", 5, 0);
        zmq_recv (requester, buffer, 10, 0);
        printf ("Received World %d\n", request_nbr);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c/TODO$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 zeroMQ_hello_world_client.c -o bin/zmqclient -lm -lzmq && bin/zmqclient
    Connecting to hello world server…
    Sending Hello 0…
    Received World 0
    Sending Hello 1…
    Received World 1
    Sending Hello 2…
    Received World 2
    Sending Hello 3…
    Received World 3
    Sending Hello 4…
    Received World 4
    Sending Hello 5…
    Received World 5
    Sending Hello 6…
    Received World 6
    Sending Hello 7…
    Received World 7
    Sending Hello 8…
    Received World 8
    Sending Hello 9…
    Received World 9



OR, in C++:




*/
