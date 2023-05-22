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

"""


import matplotlib.pyplot as plt

fig = plt.figure()
ax = fig.add_subplot(111)
values = [7, 57, 121, 192, 123, 240, 546]
labels = ['1950s', '1960s', '1970s', '1980s', '1990s', '2000s', '2010s']

plt.plot(range(len(labels)), values, 'bo') # Plotting data
plt.xticks(range(len(labels)), labels) # Redefining x-axis labels

for i, v in enumerate(values):
    # GS note: using `plt.text()` here works just fine too!
    # plt.text(i, v+25, "%d" %v, ha="center")
    ax.text(i, v+25, "%d" %v, ha="center")
plt.ylim(-10, 595)
plt.show()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./hello_world.py
    Hello world!

"""
