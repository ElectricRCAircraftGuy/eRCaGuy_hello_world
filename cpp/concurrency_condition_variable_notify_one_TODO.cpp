/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
30 Aug. 2022

Practice using condition variables for a single producer multiple consumers type example!
See: https://en.cppreference.com/w/cpp/thread/condition_variable/notify_one

As part of this demo, or experiment, try sending a binary file > 100 MiB over UDP via the loopback
interface from one process to another, as a form of IPC, seeing how fast a single worker thread can
read and re-assemble the chunked file (of ~1400 bytes per chunk) vs how fast multiple worker
threads take via a call to `condition_var.notify_one()`. I'd like to know if re-assembling can be
made to be super fast via one thread or if that takes enough time that multiple threads should be
used.
- attempt to see if you can measure the internal UDP buffer's high water mark during this, and see
  how the high water-mark compares for the one worker thread vs multiple-worker-thread case of the
  threads re-assembling the chunked file.
- To check the UDP watermark, see `man udp` and search for "udp_mem". You can read this value, for
  instance, via `cat /proc/sys/net/ipv4/udp_mem`, and you can manually change the internal UDP
  socket read buffer via a call to `setsockopt()`
  (https://man7.org/linux/man-pages/man2/setsockopt.2.html), I think, with the `SO_RCVBUF` option,
  I think. Look more into this!


STATUS: todo

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a
```

References:
1. https://en.cppreference.com/w/cpp/thread - Concurrency support library
1. https://en.cppreference.com/w/cpp/thread/condition_variable/notify_one

*/

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 hello_world_extra_basic.cpp -o bin/a && bin/a

    real    0m2.079s
    user    0m0.775s
    sys 0m0.087s
    Hello world!

*/
