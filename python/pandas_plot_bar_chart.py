#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Learn to manually type in and plot bar charts using Matplotlib and possibly Pandas. I'm making plots
to go with this answer that I helped edit: https://stackoverflow.com/a/59413206/4561887. See the
bottom of that answer for the results I am using herein.

Status: (status)

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint pandas_plot_bar_chart.py
```

Run command:
```bash
./pandas_plot_bar_chart.py
# OR
python3 pandas_plot_bar_chart.py
```

References:
1. GitHub CoPilot
1.

"""


import matplotlib.pyplot as plt
import pandas as pd

# GS: it turns out this is NOT the best way to store bar chart data! See a better way to do it in
# "pandas_plot_bar_chart_better.py".
# - This is, however, a good way to store line chart data, since it allows storing a list of values
#   for each column (method type).
results_dict = {
    # columns are method types
    # rows are lists of times for each method type
    "iterrows": [104.96],
    "named_itertuples": [1.26],
    "nameless_itertuples": [0.94],
    "polyvalent_itertuples": [2.94],
}

results_df = pd.DataFrame(results_dict)
# sort all columns by their values in the first row at index 0 (`by=0`)
results_df = results_df.sort_values(by=0, axis='columns', ascending=False)

# create a bar chart
fig = plt.figure(figsize=(10, 7))  # default is `(6.4, 4.8)` inches
values = results_df.values.flatten()
plt.bar(results_df.columns, values)
plt.title('Time vs iteration method', fontsize=14)
plt.xlabel('Iteration method', labelpad=15, fontsize=12) # use labelpad to lower the label
plt.ylabel('Time (sec)', fontsize=12)

# show the plot
plt.show()


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./pandas_plot_bar_chart.py
    [plot appears in a new window]

"""
