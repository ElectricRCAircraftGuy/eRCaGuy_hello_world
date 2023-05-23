#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
22 May 2023

Demonstrate setting a supertitle with `fig.suptitle()`, and a subtitle or footer
title with `fig.text()`!
Update: while I'm at it, just make this the main "hello world" of how to plot!

Status: wip

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
1. myself; and API documenttation at https://matplotlib.org/. Ex:
   https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.subplots_adjust.html

"""


import matplotlib.pyplot as plt

# ----------------------------------
# 1. Create a new figure
# - Can be done multiple times to create multiple GUI windows of figures.
# ----------------------------------

# Create a new figure. Now, all calls to `plt.whatever()` will apply to this
# figure.
# - When done adding subplots below, you can create more figures using this call
#   if you want to create multiple separate GUI windows of figures.
fig = plt.figure()

# ----------------------------------
# 2. Add a plot or subplot to it.
# - You can use the `fig.add_subplot()` call below multiple times to add
#   multiple subplots to your figure.
# ----------------------------------
# Optional: make this plot a subplot in a grid of plots in your figure
# fig.add_subplot(2, 2, 1) # `1` row x `1` column of plots, this is subplot `1`

# List of x values
x_vals = [1, 2, 3, 4, 5, 6, 7]
# Use a "list comprehension" to make some y values
y_vals = [val**2 for val in x_vals]

# Plot your x, y values: red (`r`) line (`-`) with circles (`o`) for points
plt.plot(x_vals, y_vals, 'r-o', label="Drag curve for Vehicle 1")
plt.legend()
plt.xlabel("x-axis label")
plt.ylabel("y-axis label")
plt.title("Plot title")

# display (x, y) values next to each point in your plot or subplot
for i, x in enumerate(x_vals):
    y = y_vals[i]
    # for your last 2 points only
    if i >= len(x_vals) - 2:
        plt.text(x-.2, y-1, f"({x} m/s, {y:.2f} N drag)",
                 horizontalalignment="right", rotation=0)
    # for all other points
    else:
        plt.text(x+.2, y-1, f"({x} m/s, {y:.2f} N drag)",
                 horizontalalignment="left", rotation=0)

# ----------------------------------
# 3. When all done adding as many subplots as you want to for your figure,
#    configure your figure title, subtitle, and footer.
# ----------------------------------

fig.suptitle("Figure title", fontsize=16)
# Figure subtitle
fig.text(0.5, 0.9, "Figure subtitle", horizontalalignment="center")
# Figure footer title
fig.text(0.5, 0.015, "Figure footer: see my website at www.whatever.com.",
         horizontalalignment="center")
# Important!:
# 1. Use `top=0.8` to bring the top of the plot down to leave some space above
# the plot for the figure subtitle to go above the plot title!
# 2. Use `bottom=0.2` to bring the bottom of the plot up to leave space for the
# figure footer.
plt.subplots_adjust(top=0.8, bottom=0.2)

# ----------------------------------
# 4. Finally, when done adding all of the figures you want to, each with as many
#    subplots as you want, call this to show all figures!
# ----------------------------------

plt.show()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

A single figure is displayed in its own GUI window.

"""
