/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Add code for thread-safe queues, deques, vectors, maps, etc. (template it
for *any* type), to safely share data between multiple threads. This will
simply require a basic mutex.

Include mechanisms for basic thread synchronization and notifying too, by waking
up threads to notify them there is data for them to read, via
`std::condition_variable`s and all.

See: https://gabrielstaples.com/cpp-mutexes-and-locks/

TODO: 
- [ ] [May 2025] mpmc_thread_safe_queue library: 
    - [ ] Modularize the library code out of
          "eRCaGuy_hello_world/cpp/mpmc_thread_safe_queue/main.cpp" by putting it into
          `mpmc_thread_safe_queue.hpp` and `mpmc_thread_safe_queue.cpp` files.
    - [ ] Then, include "mpmc_thread_safe_queue.hpp" in this file. 
    - [ ] Be sure it builds and runs correctly still in its main code.
    - [ ] Remove "TODO" from the end of this filename. 

*/
