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
1. My answer: How to iterate over Pandas DataFrames without iterating: 
   https://stackoverflow.com/a/77270285/4561887

"""

import os
import pandas as pd
import time

SAMPLE_SIZE_DEFAULT = 20000
# For cases where Windows may have really crappy 16ms precision, we need a
# significantly larger sample size.
SAMPLE_SIZE_MIN_FOR_WINDOWS = 20000000
DEBUG = False  # Set to True to enable debug prints

def debug_print(*args, **kwargs):
    if DEBUG:
        print(*args, **kwargs)

def print_bar():
    debug_print("="*56, "\n")

def process_timestamps(timestamps_ns, output_stats_header_str):
    """
    Process the timestamps list to determine the time precision of the system.
    """

    # Create a pandas DataFrame for efficient analysis of large datasets
    df = pd.DataFrame({"timestamp_ns": timestamps_ns}, dtype='int64')
    debug_print(f"df original:\n{df}")
    print_bar()

    # Remove duplicate timestamps. On Linux, there won't be any, because it has
    # sub-microsecond precision, but on Windows, the dataset may be mostly
    # duplicates because repeated calls to `time.monotonic_ns()` may return the
    # same value if called in quick succession.
    df.drop_duplicates(inplace=True)
    debug_print(f"df no duplicates:\n{df}")
    print_bar()
    if len(df) < 2:
        print("Error: not enough data to calculate time precision. Try \n"
              "increasing `SAMPLE_SIZE` by a factor of 10, and try again.")
        exit(1)

    # Now calculate the time differences between the timestamps.
    df["previous_timestamp_ns"] = df["timestamp_ns"].shift(1)
    df = df.dropna()  # remove NaN row
    df["previous_timestamp_ns"] = df["previous_timestamp_ns"].astype('int64')
    df["delta_time_us"] = (
        df["timestamp_ns"] - df["previous_timestamp_ns"]) / 1e3
    debug_print(f"df:\n{df}")
    print_bar()

    # Output statistics
    
    mean = df["delta_time_us"].mean()
    median = df["delta_time_us"].median()
    mode = df["delta_time_us"].mode()[0]
    stdev = df["delta_time_us"].std()

    print(f">>>>>>>>>> {output_stats_header_str} <<<<<<<<<<")
    print(f"Mean:   {mean:.3f} us")
    print(f"Median: {median:.3f} us")
    print(f"Mode:   {mode:.3f} us")
    print(f"Stdev:  {stdev:.3f} us")
    print(f"FINAL ANSWER: time precision on this system: "
        + f"{median:.3f} +/- {stdev:.3f} us\n")

# =============================================================================
# 1. Test `time.monotonic_ns()`
# =============================================================================

SAMPLE_SIZE = SAMPLE_SIZE_DEFAULT
if os.name == 'nt':
    # The OS is Windows
    if SAMPLE_SIZE < SAMPLE_SIZE_MIN_FOR_WINDOWS:
        SAMPLE_SIZE = SAMPLE_SIZE_MIN_FOR_WINDOWS
        print(f"Detected: running on Windows. Using a larger SAMPLE_SIZE of "
            f"{SAMPLE_SIZE}.\n")

# Gather timestamps with zero delays between them
# - preallocated list, so that no dynamic memory allocation will happen in the
#   loop below
timestamps_ns = [None]*SAMPLE_SIZE
for i in range(len(timestamps_ns)):
    timestamps_ns[i] = time.monotonic_ns()

process_timestamps(timestamps_ns, "1. time.monotonic_ns()")

# =============================================================================
# 2. Test `time.perf_counter_ns()`
# =============================================================================

SAMPLE_SIZE = SAMPLE_SIZE_DEFAULT

timestamps_ns = [None]*SAMPLE_SIZE
for i in range(len(timestamps_ns)):
    timestamps_ns[i] = time.perf_counter_ns()

process_timestamps(timestamps_ns, "2. time.perf_counter_ns()")

# =============================================================================
# 3. Test `time.time_ns()`
# =============================================================================

SAMPLE_SIZE = SAMPLE_SIZE_DEFAULT
if os.name == 'nt':
    # The OS is Windows
    if SAMPLE_SIZE < SAMPLE_SIZE_MIN_FOR_WINDOWS:
        SAMPLE_SIZE = SAMPLE_SIZE_MIN_FOR_WINDOWS
        print(f"Detected: running on Windows. Using a larger SAMPLE_SIZE of "
            f"{SAMPLE_SIZE}.\n")

timestamps_ns = [None]*SAMPLE_SIZE
for i in range(len(timestamps_ns)):
    timestamps_ns[i] = time.time_ns()

process_timestamps(timestamps_ns, "3. time.time_ns()")


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

-----------
ON LINUX:
-----------

eRCaGuy_hello_world$ time python/time_monotonic_ns__get_precision.py 
>>>>>>>>>> 1. time.monotonic_ns() <<<<<<<<<<
Mean:   0.081 us
Median: 0.070 us
Mode:   0.070 us
Stdev:  0.118 us
FINAL ANSWER: time precision on this system: 0.070 +/- 0.118 us

>>>>>>>>>> 2. time.perf_counter_ns() <<<<<<<<<<
Mean:   0.076 us
Median: 0.069 us
Mode:   0.068 us
Stdev:  0.070 us
FINAL ANSWER: time precision on this system: 0.069 +/- 0.070 us

>>>>>>>>>> 3. time.time_ns() <<<<<<<<<<
Mean:   0.080 us
Median: 0.074 us
Mode:   -0.030 us
Stdev:  0.226 us
FINAL ANSWER: time precision on this system: 0.074 +/- 0.226 us


real	0m0.264s
user	0m0.802s
sys	0m1.124s




-----------
ON WINDOWS:
-----------

eRCaGuy_hello_world$ time python/time_monotonic_ns__get_precision.py
Detected: running on Windows. Using a larger SAMPLE_SIZE of 20000000.

>>>>>>>>>> 1. time.monotonic_ns() <<<<<<<<<<
Mean:   15625.000 us
Median: 16000.000 us
Mode:   16000.000 us
Stdev:  486.897 us
FINAL ANSWER: time precision on this system: 16000.000 +/- 486.897 us

>>>>>>>>>> 2. time.perf_counter_ns() <<<<<<<<<<
Mean:   0.101 us
Median: 0.100 us
Mode:   0.100 us
Stdev:  0.021 us
FINAL ANSWER: time precision on this system: 0.100 +/- 0.021 us

Detected: running on Windows. Using a larger SAMPLE_SIZE of 20000000.

>>>>>>>>>> 3. time.time_ns() <<<<<<<<<<
Mean:   9639.436 us
Median: 10134.354 us
Mode:   610.144 us
Stdev:  5201.053 us
FINAL ANSWER: time precision on this system: 10134.354 +/- 5201.053 us


real    0m8.301s
user    0m0.000s
sys     0m0.000s


"""
