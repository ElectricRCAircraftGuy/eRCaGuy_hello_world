#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
22 May 2023

Do some plotting; learn to use matplotlib subplots a bit.
- This code below is modified from @Sheldore's answer here:
  https://stackoverflow.com/a/52244724/4561887

Status: (status)

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint hello_world.py
```

Run command:
```bash
./hello_world.py
# OR
python3 hello_world.py
```

References:
1. This code below is modified from @Sheldore's answer here:
   https://stackoverflow.com/a/52244724/4561887
1. ...and from my own answer here: https://stackoverflow.com/a/76309590/4561887

"""


import matplotlib.pyplot as plt

from statistics import mean

# cluster size (KiB) vs speed (MB/s)
x_cluster_size = [0.5, 4, 8, 32, 128, 32768]
y_speed = [
    mean([87.36, 96.84]),
    mean([285.36, 352.37, 309.35]),
    mean([333.19, 320.87, 360.62]),
    mean([360.59, 329.26, 387.60]),
    mean([392.01, 363.88, 413.63]),
    mean([437.09, 409.12, 436.98]),
]

# -----------
# Figure 1
# -----------
f1 = plt.figure()
plt.plot(x_cluster_size, y_speed, 'b-o', label='When writing a 5.3 GB file')
plt.legend(loc='lower right')
plt.xscale('log', base=2)
plt.ylabel('Speed (MB/sec)')
plt.xlabel('exFAT cluster size (KiB)')
plt.title("exFAT cluster size vs speed")
# display (x, y) values next to each point
for i, x in enumerate(x_cluster_size):
    y = y_speed[i]
    # first element
    if i == 0:
        plt.text(x+.2, y, f"({x} KiB, {y:.0f} MB/sec)", horizontalalignment="left")
    # last element
    elif i == len(x_cluster_size) - 1:
        plt.text(x-10000, y, f"({x} KiB, {y:.0f} MB/sec)", horizontalalignment="right")
    else:
        plt.text(x, y-20, f"({x} KiB, {y:.0f} MB/sec)", horizontalalignment="left")

# -----------
# Figure 2
# -----------
f2 = plt.figure()
values = [7, 57, 121, 192, 123, 240, 546]
labels = ['1950s', '1960s', '1970s', '1980s', '1990s', '2000s', '2010s']

plt.plot(range(len(labels)), values, 'bo') # Plotting data
plt.xticks(range(len(labels)), labels) # Redefining x-axis labels

for i, v in enumerate(values):
    # GS note: using `plt.text()` here works just fine too!
    # plt.text(i, v+25, "%d" %v, ha="center")
    plt.text(i, v+25, "%d" %v, ha="center")
plt.ylim(-10, 595)

# -----------
# Show all figures
# -----------
plt.show()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./hello_world.py
    Hello world!

"""
