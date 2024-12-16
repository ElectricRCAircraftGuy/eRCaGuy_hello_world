#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Dec. 2024

Test the minimum time precision possible on your system using `time.monotonic_ns()`. 

Status: DONE AND WORKS!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint time_monotonic_ns__get_precision.py
```

Run command:
```bash
./time_monotonic_ns__get_precision.py
# OR
python3 time_monotonic_ns__get_precision.py
```

References:
1. *****+See my answer with this code, here: 
   https://stackoverflow.com/a/73482099/4561887

"""


import statistics
import time

# preallocated list, so that no dynamic memory allocation will happen in 
# the loop below
ARRAY_SIZE = 20
timestamps_ns = [None]*ARRAY_SIZE

# Gather timestamps with zero delays between them
for i in range(len(timestamps_ns)):
    timestamps_ns[i] = time.monotonic_ns()

# Now calculate the time differences between the timestamps.
delta_times_us = [None]*(len(timestamps_ns) - 1)
t_start_ns = timestamps_ns[0]
for i in range(1, len(timestamps_ns)):
    t_now_ns = timestamps_ns[i]
    dt_ns = t_now_ns - t_start_ns
    delta_times_us[i - 1] = dt_ns / 1e3
    t_start_ns = t_now_ns
    print(f"{i - 1}: dt_ns = {dt_ns}")

# Output statistics
mean = statistics.mean(delta_times_us)
median = statistics.median(delta_times_us)
mode = statistics.mode(delta_times_us)
stdev = statistics.stdev(delta_times_us)
print(f"Mean:   {mean:.3f} us")
print(f"Median: {median:.3f} us")
print(f"Mode:   {mode:.3f} us")
print(f"Stdev:  {stdev:.3f} us")
print(f"\nFINAL ANSWER: time precision on this system: "
    + f"{median:.3f} +/- {stdev:.3f} us\n")



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

eRCaGuy_hello_world$ python/time_monotonic_ns__get_precision.py 
0: dt_ns = 333
1: dt_ns = 153
2: dt_ns = 80
3: dt_ns = 78
4: dt_ns = 72
5: dt_ns = 71
6: dt_ns = 72
7: dt_ns = 71
8: dt_ns = 64
9: dt_ns = 65
10: dt_ns = 62
11: dt_ns = 63
12: dt_ns = 61
13: dt_ns = 130
14: dt_ns = 66
15: dt_ns = 63
16: dt_ns = 61
17: dt_ns = 62
18: dt_ns = 62
Mean:   0.089 us
Median: 0.066 us
Mode:   0.062 us
Stdev:  0.064 us

FINAL ANSWER: time precision on this system: 0.066 +/- 0.064 us

"""
