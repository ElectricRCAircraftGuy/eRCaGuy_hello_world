#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Learn to manually type in and plot bar charts using Matplotlib and possibly Pandas. I'm making plots
to go with this answer that I helped edit: https://stackoverflow.com/a/59413206/4561887. See the
bottom of that answer for the results I am using herein.

Status: done and works!
- This is an EXCELLENT plotting demo, and auto-text-labeling demo, for bar charts!
- It also demonstrates the use of **list comprehension** to add text labels to each bar in a bar.
See also "pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py".

keywords: bar charts, bar chart, bar plot, bar plots, plot, plots, matplotlib, pandas, python,
automatically add text labels to plots charts add text labels to bars

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint pandas_plot_bar_chart_better_GREAT_AUTOLABEL_DATA
```

Run command:
```bash
./pandas_plot_bar_chart_better_GREAT_AUTOLABEL_DATA
# OR
python3 pandas_plot_bar_chart_better_GREAT_AUTOLABEL_DATA
```

References:
1. "eRCaGuy_hello_world/python/pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py"
1. GitHub CoPilot
1. Online resources, such as this answer: https://stackoverflow.com/a/55557758/4561887
1.

"""

import matplotlib.pyplot as plt
import pandas as pd

results_dict = {
    "Method": ["iterrows", "default_named_itertuples", "nameless_itertuples", "polyvalent_itertuples"],
    "Time_sec": [104.96, 1.26, 0.94, 2.94],
}

results_df = pd.DataFrame(results_dict) # columns are "Method" and "Time_sec"
results_df = results_df.sort_values(by="Time_sec", axis='rows', ascending=False)
# Be sure to reset the indices after sorting, or else the indices will be sorted out of their
# original order now too!
# - Note: this defaults to `drop=False`, which means the old indices will be kept in a new column
#   called "index" now. If you want to drop the old indices instead of putting them into a new
#   column, pass argument `drop=True`.
results_df = results_df.reset_index()

# create a bar chart
fig = plt.figure(figsize=(10, 7))  # default is `(6.4, 4.8)` inches
plt.bar(results_df["Method"], results_df["Time_sec"])
plt.title('Time vs iteration method (*Lower* is better)', fontsize=14)
plt.xlabel('Iteration method', labelpad=15, fontsize=12) # use labelpad to lower the label
plt.ylabel('Time (sec)', fontsize=12)

# Prepare to add text labels to each bar
results_df["text_x"] = results_df.index # use the indices as the x-positions
results_df["text_y"] = results_df["Time_sec"] + 5
results_df["time_multiplier"] = results_df["Time_sec"] / results_df["Time_sec"].min()
results_df["text_label"] = (results_df["Time_sec"].round(3).astype(str) + " sec\n" +
                            results_df["time_multiplier"].round(1).astype(str) + "x")

# Use a list comprehension to actually call `plot.text()` to add a label for each row in the
# dataframe
[
    plt.text(
        text_x,
        text_y,
        text_label,
        horizontalalignment='center',
        verticalalignment='center'
    ) for text_x, text_y, text_label
    # Note: this `[[...]]` syntax is called "double-bracket indexing" and is used to select a subset
    # of columns from the dataframe, kind of like boolean indexing. The inner `[]` brackets create a
    # list from the column names within them, and the outer `[]` brackets accept this list to index
    # into the dataframe and select just this list of columns.
    # - One of the **list comprehension** examples in this answer here uses `.to_numpy()` like this:
    #   https://stackoverflow.com/a/55557758/4561887
    in results_df[[
        "text_x",
        "text_y",
        "text_label"
    ]].to_numpy()  # NB: `.values` works here too, but is deprecated. See:
                   # https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.values.html
]

print(f"results_df =\n{results_df}")

ymin, ymax = plt.ylim()
plt.ylim(ymin, ymax*1.1)  # add 10% to the top of the y-axis

plt.show()


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

eRCaGuy_hello_world$ python/pandas_plot_bar_chart_better_GREAT_AUTOLABEL_DATA
results_df =
   index                 Method  Time_sec  text_x  text_y  time_multiplier          text_label
0      0               iterrows    104.96       0  109.96       111.659574  104.96 sec\n111.7x
1      3  polyvalent_itertuples      2.94       1    7.94         3.127660      2.94 sec\n3.1x
2      1       named_itertuples      1.26       2    6.26         1.340426      1.26 sec\n1.3x
3      2    nameless_itertuples      0.94       3    5.94         1.000000      0.94 sec\n1.0x

[then a plot appears in a new window]

"""
