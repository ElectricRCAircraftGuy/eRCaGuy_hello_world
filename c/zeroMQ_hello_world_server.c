/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
9 Apr. 2022

This is the basic ZeroMQ getting started **server** demo in C from
https://zeromq.org/get-started/?language=c#

STATUS: works! See Linux installation instructions for libzmq in the References below.

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 zeroMQ_hello_world_server.c -o bin/zmqserver -lm -lzmq && bin/zmqserver

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 zeroMQ_hello_world_server.c -o bin/zmqserver -lzmq && bin/zmqserver
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

//  Hello World server
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);

    while (1) {
        char buffer [10];
        zmq_recv (responder, buffer, 10, 0);
        printf ("Received Hello\n");
        sleep (1);          //  Do some 'work'
        zmq_send (responder, "World", 5, 0);
    }
    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c/TODO$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 zeroMQ_hello_world_server.c -o bin/zmqserver -lm -lzmq && bin/zmqserver
    Received Hello
    Received Hello
    Received Hello
    Received Hello
    Received Hello
    Received Hello
    Received Hello
    Received Hello
    Received Hello
    Received Hello
    ^C



OR, in C++:




*/
