#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Use the Pandas library to import CSV file data into a Pandas DataFrame object. Then, use Pandas to
manipulate the data, and plot it using Matplotlib.

Status: done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint pandas_read_and_plot_csv_GREAT.py
```

Run command:
```bash
./pandas_read_and_plot_csv_GREAT.py
# OR
python3 pandas_read_and_plot_csv_GREAT.py
```

References:
1. https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.read_csv.html
1. GitHub CoPilot
1. My answer on adding titles to matplotlib plots: https://stackoverflow.com/a/76311048/4561887


"""

import matplotlib.pyplot as plt
import os
import pandas as pd

# See: "eRCaGuy_hello_world/python/import_helper.py"
FULL_PATH_TO_SCRIPT = os.path.abspath(__file__)
SCRIPT_DIRECTORY = str(os.path.dirname(FULL_PATH_TO_SCRIPT))


def mkdir(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)


def save_figure(filename):
    plt.savefig(f'{SCRIPT_DIRECTORY}/../fake_data/figures/{filename}.svg')
    plt.savefig(f'{SCRIPT_DIRECTORY}/../fake_data/figures/{filename}.png')


def read_csv_file(filename):
    """
    Read a CSV file into a Pandas DataFrame object, and return it.
    """
    filepath = f"{SCRIPT_DIRECTORY}/../fake_data/{filename}"
    print(f"Reading file: \"{filepath}\"")

    dataframe = pd.read_csv(
        filepath,
        sep=r"[,\t]+", # allow any number of either commas or tabs as the separator
        header=0,  # the first non-blank row is the header
        engine="python",
        skip_blank_lines=True,
    )

    # for debugging
    print(f"Dataframe: = \n{dataframe}")
    print()
    print(f"dataframe.dtypes = \n{dataframe.dtypes}")
    print()

    # convert dollars to a printable number; ie: remove the $ symbol and convert to numeric values
    # See:
    # 1. GitHub CoPilot
    # 1. https://pandas.pydata.org/docs/reference/api/pandas.Series.str.html
    # 1. https://pandas.pydata.org/docs/reference/api/pandas.Series.astype.html
    dataframe['dollar'] = dataframe['dollar'].str.replace('$', '').astype(float)

    # for debugging
    print(f"Dataframe: = \n{dataframe}")
    print()
    print(f"dataframe.dtypes = \n{dataframe.dtypes}")
    print()

    return dataframe


def plot_data(dataframe):
    """
    Plot the data in the given Pandas DataFrame object.
    """
    print("Plotting data...")

    # Note: `.dropna()` removes missing or "NaN" values from the dataframe. See:
    # https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.dropna.html
    dataframe_sorted = dataframe.sort_values(by=["age"]).dropna()

    # ==============================================================================================
    # Figure: whatever it can automatically plot
    # ==============================================================================================

    # This just attempts to plot all numerical columns in the dataframe, with the x-axis being the
    # dataframe index (row number).
    dataframe.plot()
    plt.xlabel("points (-)")

    # For the whole figure
    plt.suptitle("Person data, automatically plotted")
    plt.subplots_adjust(hspace=0.4)  # adjust the height space between subplots
    plt.subplots_adjust(wspace=0.3)  # adjust the width space between subplots
    save_figure("Figure_1_automatically_plotted")


    # Let's do some more advanced **manual** plotting now.

    # ==============================================================================================
    # Figure: person data
    # ==============================================================================================
    fig = plt.figure(figsize=(18, 10.8))  # default is `(6.4, 4.8)` inches

    # Ages
    fig.add_subplot(2, 3, 1)  # nrows, ncols, index
    plt.title("Ages", y=1.05)
    plt.plot(
        dataframe['age'],
        'b-o',
        linewidth=1,
        markersize=2,
        label="age (yrs)"
    )
    plt.legend()
    plt.xlabel("points (-)")
    plt.ylabel("age (years)")

    # Dollars
    fig.add_subplot(2, 3, 2)  # nrows, ncols, index
    plt.title("Dollars", y=1.05)
    plt.plot(
        dataframe['dollar'],
        'b-o',
        linewidth=1,
        markersize=2,
        label="Dollars ($)"
    )
    plt.legend()
    plt.xlabel("points (-)")
    plt.ylabel("dollars ($)")

    # Dollars vs age
    fig.add_subplot(2, 3, 3)  # nrows, ncols, index
    plt.title("Dollars vs age", y=1.05)
    plt.plot(
        dataframe['age'].to_numpy(),
        dataframe['dollar'].to_numpy(),
        'b-o',
        linewidth=1,
        markersize=2,
        label="Dollars ($)"
    )
    plt.legend()
    plt.xlabel("age (years)")
    plt.ylabel("dollars ($)")

    # Dollars vs age (sorted by age)
    fig.add_subplot(2, 3, 4)  # nrows, ncols, index
    plt.title("Dollars vs age (sorted by age)", y=1.05)
    plt.plot(
        dataframe_sorted['age'].to_numpy(),
        dataframe_sorted['dollar'].to_numpy(),
        'b-o',
        linewidth=1,
        markersize=2,
        label="Dollars ($)"
    )
    plt.legend()
    plt.xlabel("age (years)")
    plt.ylabel("dollars ($)")

    # Dollars vs age (sorted by dollars)
    dataframe_sorted_by_dollars = dataframe.sort_values(by=["dollar"]).dropna()
    fig.add_subplot(2, 3, 5)  # nrows, ncols, index
    plt.title("Dollars vs age (sorted by dollars)", y=1.05)
    plt.plot(
        dataframe_sorted_by_dollars['age'].to_numpy(),
        dataframe_sorted_by_dollars['dollar'].to_numpy(),
        'b-o',
        linewidth=1,
        markersize=2,
        label="Dollars ($)"
    )
    plt.legend()
    plt.xlabel("age (years)")
    plt.ylabel("dollars ($)")

    # Dollars vs age (scatter plot--no line)
    fig.add_subplot(2, 3, 6)  # nrows, ncols, index
    plt.title("Dollars vs age (scatter plot--no line)", y=1.05)
    plt.plot(
        dataframe['age'].to_numpy(),
        dataframe['dollar'].to_numpy(),
        'bo',  # just remove the `-` is all to not have a line!
        linewidth=1,
        markersize=2,
        label="Dollars ($)"
    )
    # plt.legend()  # no need for a legend either
    plt.xlabel("age (years)")
    plt.ylabel("dollars ($)")

    # For the whole figure
    plt.suptitle("Person data, manually plotted")
    plt.subplots_adjust(hspace=0.4)  # adjust the height space between subplots
    plt.subplots_adjust(wspace=0.3)  # adjust the width space between subplots
    save_figure("Figure_2_manually_plotted")


def main():
    """
    The main function of this program.
    """

    mkdir(f"{SCRIPT_DIRECTORY}/../fake_data/figures")
    dataframe = read_csv_file("fake_person_data.csv")
    plot_data(dataframe)
    # Show all figures
    plt.show()


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    Run it and see the output in "eRCaGuy_hello_world/fake_data/figures"

"""
