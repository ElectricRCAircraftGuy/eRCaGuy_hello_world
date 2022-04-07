This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


1. For an *excellent* and thorough demo on how to activate and use the Linux `SCHED_RR` soft-realtime round-robin scheduler, as well as how to set the process or thread priority, see:
    1. Function `set_scheduler()` in [sleep_nanosleep_minimum_time_interval.c](sleep_nanosleep_minimum_time_interval.c).
1. High-resolution, high-precision, high-accuracy 10 KHz periodic task loop, with `SCHED_RR` soft real-time round-robin scheduler, and nanosecond sleep: [timinglib_pthread_periodic_loop.c](timinglib_pthread_periodic_loop.c)
