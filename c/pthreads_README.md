This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


## `pthread` resources

For pthreads demos, see:

1. All files named `pthreads*`. 
1. [timinglib_pthread_periodic_loop.c](timinglib_pthread_periodic_loop.c)
1. https://en.wikipedia.org/wiki/POSIX_Threads
    1. NEW LINK: the above link is now: https://en.wikipedia.org/wiki/Pthreads
1. Search this repo for any file which contains `pthread`-related words or content:
    ```bash
    # 1. `#include <pthread.h>`
    #
    rg '#include <pthread.h>' "path/to/eRCaGuy_hello_world"
    # Ex: if already cd'ed into this "eRCaGuy_hello_world/c" dir:
    rg '#include <pthread.h>' ..

    # 2. `pthread`
    #
    # Ah, interesting! The output shows a **ton** of matches
    # inside "eRCaGuy_hello_worldcpp/bin_hello_world/hello_world.ii", which
    # must mean that pthreads are used naturally even for basic,
    # single-threaded "hello world" programs compiled by gcc on Linux!
    rg pthread
    
    # 3. `pthread_create`
    rg pthread_create
    ```
