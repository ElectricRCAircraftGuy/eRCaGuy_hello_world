#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Use the Pandas library to manipulate a DataFrame using iteration vs vectorization vs list
comprehension, and compare the speed tests results.

The question I'm trying to answer is:
What are the various ways to do iteration-like things over a Pandas dataframe with*out* actually
doing Python iteration, which is slow, and how do they compare in speed?

Status: WIP

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py
```

Run command:
```bash
./pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py
# OR
python3 pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py
```

References:
1. "pandas_read_and_plot_csv.py"
1. How to iterate over rows in a DataFrame in Pandas
    1. https://stackoverflow.com/a/55557758/4561887
    1. https://stackoverflow.com/a/59413206/4561887
1. My answer on Python timestamps: https://stackoverflow.com/a/73482099/4561887


"""

import matplotlib.pyplot as plt
import numpy as np
import os
import pandas as pd
from pandas.testing import assert_series_equal
import time

# See: "eRCaGuy_hello_world/python/import_helper.py"
FULL_PATH_TO_SCRIPT = os.path.abspath(__file__)
SCRIPT_DIRECTORY = str(os.path.dirname(FULL_PATH_TO_SCRIPT))

# Text formatting.
# - See my ANSI format library here:
#   https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/ansi_text_format_lib.sh
ANSI_START = "\033["    # start of an ANSI formatting sequence
ANSI_FG_GRE = ";32"     # foreground color green
ANSI_FG_BLU = ";34"     # foreground color blue
ANSI_FG_BR_BLU = ";94"  # foreground color bright blue
ANSI_END = "m"          # end of an ANSI formatting sequence
ANSI_OFF = f"{ANSI_START}{ANSI_END}"
FGR = f"{ANSI_START}{ANSI_FG_GRE}{ANSI_END}"     # green text
FBL = f"{ANSI_START}{ANSI_FG_BLU}{ANSI_END}"     # blue text
FBB = f"{ANSI_START}{ANSI_FG_BR_BLU}{ANSI_END}"  # bright blue text
F = ANSI_OFF

def mkdir(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)


def add_newlines_every_n_chars(s, n):
    """
    Copied from my own code in "pandas_plot_bar_chart_better_GREAT_AUTOLABEL_DATA.py"

    Add a newline character to a string at the nearest underscore to the nth character. This is
    useful for making long labels fit on a plot.
    - Aided by GitHub CoPilot

    TODO:
    1. [ ] add unit tests
    1. [ ] think through this really deeply and make sure it's correct. I'm not sure it's right, and
       it could easily have some "off by one" type problems in the logic and indexing!
    """
    # return '\n'.join(s[i:i+n] for i in range(0, len(s), n))

    remaining_chars = len(s)
    i_start = 0

    while remaining_chars > n:
        # Find the nearest underscore to the nth character
        split_index = s.find('_', i_start + n//2, i_start + n + n//2)

        if split_index == -1:
            # If there is no underscore in the range, split at the nth character
            split_index = n - 1

        split_index += 1  # go to the right of the underscore we just found
        # Split the string
        s = s[:split_index] + '\n' + s[split_index:]

        remaining_chars = len(s) - split_index
        i_start = split_index

    return s


def plot_data(results_df):
    """
    Plot the data in the given dataframe.
    - This code was copied from:
      "eRCaGuy_hello_world/python/pandas_plot_bar_chart_better_GREAT_AUTOLABEL_DATA.py"
    """

    # create a bar chart
    fig = plt.figure(figsize=(12, 7))  # default is `(6.4, 4.8)` inches
    plt.bar(results_df["Method_short_names"], results_df["Time_sec"])
    plt.title('Time vs iteration method (*Lower* is better)', fontsize=14)
    plt.xlabel('Iteration method', labelpad=15, fontsize=12) # use labelpad to lower the label
    plt.ylabel('Time (sec)', fontsize=12)

    # Prepare to add text labels to each bar
    results_df["text_x"] = results_df.index # use the indices as the x-positions
    results_df["text_y"] = results_df["Time_sec"] + 0.05*results_df["Time_sec"].max()
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
        in zip(
            results_df["text_x"],
            results_df["text_y"],
            results_df["text_label"]
        )
    ]

    print(f"results_df =\n{results_df}")

    ymin, ymax = plt.ylim()
    plt.ylim(ymin, ymax*1.1)  # add 10% to the top of the y-axis
    # increase the whitespace under the figure to leave space for long, wrapping labels
    fig.subplots_adjust(bottom=0.2)


def calculate_new_column_b_value(b_value):
    b_value_new = (6 * b_value) if b_value > 0 else (-6 * b_value)  # Python ternary operator
    return b_value_new


def calculate_val(
        A_i_minus_2,
        A_i_minus_1,
        A,
        A_i_plus_1,
        B,
        C,
        D):
    """
    Calculate and return a new value, `val`, by performing the following equation:
    val_i = 2 * A_(i-2)
          + 3 * A_(i-1)
          + 4 * A_i
          + 5 * A_(i+1)
          + 6 * B_i
          + 7 * C_i
          - 8 * D_i
    """
    val = (
        2 * A_i_minus_2
        + 3 * A_i_minus_1
        + 4 * A
        + 5 * A_i_plus_1
        + (6 * B) if B > 0 else (-6 * B)  # Python ternary operator
        + 7 * C
        - 8 * D
    )
    return val


def assert_all_stats_are_equal(stats_dict):
    """
    Assert that all summary statistics are equal across all techniques.
    """
    print()
    # Get the first technique's stats as the "golden" stats to compare against
    stats_series_first = stats_dict[list(stats_dict.keys())[0]]
    for name, stats_series in stats_dict.items():
        print(f"Checking stats for technique \"{name}\"")
        assert_series_equal(stats_series, stats_series_first)

    print(f"{FGR}Tests passed: the results of all techniques are equal!{F}")


def main():
    """
    The main function of this program.
    """

    mkdir(f"{SCRIPT_DIRECTORY}/../fake_data/figures")

    # Create an array (numpy list of lists) of fake data
    MIN_VAL = -1000
    MAX_VAL = 1000
    # NUM_ROWS = 1_000_000
    NUM_ROWS = 100_000
    NUM_COLS = 4
    data = np.random.randint(MIN_VAL, MAX_VAL, size=(NUM_ROWS, NUM_COLS))

    # Now convert it to a Pandas DataFrame with columns named "A", "B", "C", and "D"
    df_original = pd.DataFrame(data, columns=["A", "B", "C", "D"])
    print(f"dataframe = \n{df_original}")

    # Now calculate a new column, "val", using a variety of techniques, by following the formula
    # inside `calculate_val()`

    dt_sec = {}  # dictionary of time deltas in seconds
    val_stats = {}   # dictionary of summary statistics

    # ==============================================================================================
    print("\n=== Technique 1: raw Python `for` loop ===")
    # ==============================================================================================

    name = "raw_for_loop"
    df = df_original.copy()  # make a copy of the original dataframe to work with
    time_start_sec = time.monotonic()

    val = [np.NAN]*len(df)
    for i in range(len(df)):
        if i < 2 or i > len(df)-2:
            continue

        val[i] = calculate_val(
            df["A"][i-2],
            df["A"][i-1],
            df["A"][i],
            df["A"][i+1],
            df["B"][i],
            df["C"][i],
            df["D"][i],
        )

    df["val"] = val  # put this column back into the dataframe
    time_end_sec = time.monotonic()
    print(f"len(val) = {len(val)}") # debugging
    # print(f"val[:10] = {val[:10]}") # debugging
    # print(f"val[-10:] = {val[-10:]}") # debugging

    dt_sec[name] = time_end_sec - time_start_sec
    val_stats[name] = df["val"].describe()  # summary statistics

    print(f"{FBL}dt_sec[{name}] = {dt_sec[name]:.6f} sec{F}")
    print(f'val_stats[{name}]:\n------\n{val_stats[name]}')

    # ==============================================================================================
    print("\n=== Technique 2 [WORST-**NEVER** USE!]: use `iterrows()` in a Python `for` loop ===")
    # ==============================================================================================

    name = "iterrows_in_for_loop"
    df = df_original.copy()  # make a copy of the original dataframe to work with
    time_start_sec = time.monotonic()

    val = [np.NAN]*len(df)
    for index, row in df.iterrows():
        if index < 2 or index > len(df)-2:
            continue

        val[index] = calculate_val(
            df["A"][index-2],
            df["A"][index-1],
            row["A"],
            df["A"][index+1],
            row["B"],
            row["C"],
            row["D"],
        )

    df["val"] = val  # put this column back into the dataframe
    time_end_sec = time.monotonic()
    print(f"len(val) = {len(val)}") # debugging
    # print(f"val[:10] = {val[:10]}") # debugging
    # print(f"val[-10:] = {val[-10:]}") # debugging

    dt_sec[name] = time_end_sec - time_start_sec
    val_stats[name] = df["val"].describe()  # summary statistics

    print(f"{FBL}dt_sec[{name}] = {dt_sec[name]:.6f} sec{F}")
    print(f'val_stats[{name}]:\n------\n{val_stats[name]}')

    # ==============================================================================================
    print("\n=== For all of the next examples, we must first prepare the dataframe by adding\n" +
          "columns with previous and next values: A_(i-2), A_(i-1), and A_(i+1). ===")
    # ==============================================================================================

    name = "adding_shifted_data"
    time_start_sec = time.monotonic()

    df_original["A_i_minus_2"] = df_original["A"].shift(2)  # val at index i-2
    df_original["A_i_minus_1"] = df_original["A"].shift(1)  # val at index i-1
    df_original["A_i_plus_1"] = df_original["A"].shift(-1)  # val at index i+1

    # Note: to ensure that no partial calculations are ever done with rows which have NaN values due
    # to the shifting, we can either drop such rows with `.dropna()`, or set all values in these
    # rows to NaN. I'll choose the latter so that the stats that will be generated with the
    # techniques below will end up matching the stats which were produced by the prior techniques
    # above.
    # df_original = df_original.dropna()
    df_original.iloc[:2, :] = np.NAN   # slicing operators: first two rows, all columns
    df_original.iloc[-1:, :] = np.NAN  # slicing operators: last row, all columns

    time_end_sec = time.monotonic()
    dt_sec[name] = time_end_sec - time_start_sec
    print(f"{FBL}dt_sec[{name}] = {dt_sec[name]:.6f} sec{F}")

    # ==============================================================================================
    print("\n=== Technique 3: named `itertuples()` in a Python `for` loop ===")
    # See here for this and other `itertuples()`-based techniques:
    # https://stackoverflow.com/a/59413206/4561887
    # ==============================================================================================

    name = "itertuples_in_for_loop"
    df = df_original.copy()  # make a copy of the original dataframe to work with
    time_start_sec = time.monotonic()

    val = [np.NAN]*len(df)
    for row in df.itertuples():
        val[row.Index] = calculate_val(
            row.A_i_minus_2,
            row.A_i_minus_1,
            row.A,
            row.A_i_plus_1,
            row.B,
            row.C,
            row.D,
        )

    df["val"] = val  # put this column back into the dataframe
    time_end_sec = time.monotonic()
    print(f"len(val) = {len(val)}") # debugging
    # print(f"val[:10] = {val[:10]}") # debugging
    # print(f"val[-10:] = {val[-10:]}") # debugging

    dt_sec[name] = time_end_sec - time_start_sec
    val_stats[name] = df["val"].describe()  # summary statistics

    print(f"{FBL}dt_sec[{name}] = {dt_sec[name]:.6f} sec{F}")
    print(f'val_stats[{name}]:\n------\n{val_stats[name]}')

    # ==============================================================================================
    print("\n=== Technique 4 [FASTEST]: vectorization, w/`apply()` for one corner-case ===")
    # ==============================================================================================

    name = "vectorization__with_apply_for_corner_case"
    df = df_original.copy()  # make a copy of the original dataframe to work with
    time_start_sec = time.monotonic()

    # In this particular example, since we have an embedded `if-else` statement for the `B` column,
    # we can't use pure vectorization. So, first we'll calculate a new `B` column using `apply()`,
    # then we'll use vectorization for the rest.
    df["B_new"] = df["B"].apply(calculate_new_column_b_value)
    # OR (same thing, but with a lambda function instead)
    # df["B_new"] = df["B"].apply(lambda x: (6 * x) if x > 0 else (-6 * x))

    # Now we can use vectorization for the rest. "Vectorization" in this case means to simply use
    # the column series variables in equations directly, without manually iterating over them.
    # Pandas DataFrames will handle the underlying iteration automatically for you. You just focus
    # on the math.
    df["val"] = (
        2 * df["A_i_minus_2"]
        + 3 * df["A_i_minus_1"]
        + 4 * df["A"]
        + 5 * df["A_i_plus_1"]
        + df["B_new"]
        + 7 * df["C"]
        - 8 * df["D"]
    )

    df["val"] = val  # put this column back into the dataframe
    time_end_sec = time.monotonic()
    print(f"len(val) = {len(val)}") # debugging
    # print(f"val[:10] = {val[:10]}") # debugging
    # print(f"val[-10:] = {val[-10:]}") # debugging

    dt_sec[name] = time_end_sec - time_start_sec
    val_stats[name] = df["val"].describe()  # summary statistics

    print(f"{FBL}dt_sec[{name}] = {dt_sec[name]:.6f} sec{F}")
    print(f'val_stats[{name}]:\n------\n{val_stats[name]}')

    # ==============================================================================================
    print("\n=== Technique 5: using the `apply()` function with a lambda ===")
    # See:
    # 1. How to use `apply()` with multiple columns in a given row!:
    # https://stackoverflow.com/a/30566899/4561887
    # 1. https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.apply.html
    # ==============================================================================================

    name = "apply_function_with_lambda"
    df = df_original.copy()  # make a copy of the original dataframe to work with
    time_start_sec = time.monotonic()

    df["val"] = df.apply(
        lambda row: calculate_val(
            row["A_i_minus_2"],
            row["A_i_minus_1"],
            row["A"],
            row["A_i_plus_1"],
            row["B"],
            row["C"],
            row["D"]
        ),
        axis='columns' # same as `axis=1`: "apply function to each row", rather than to each column
    )

    df["val"] = val  # put this column back into the dataframe
    time_end_sec = time.monotonic()
    print(f"len(val) = {len(val)}") # debugging
    # print(f"val[:10] = {val[:10]}") # debugging
    # print(f"val[-10:] = {val[-10:]}") # debugging

    dt_sec[name] = time_end_sec - time_start_sec
    val_stats[name] = df["val"].describe()  # summary statistics

    print(f"{FBL}dt_sec[{name}] = {dt_sec[name]:.6f} sec{F}")
    print(f'val_stats[{name}]:\n------\n{val_stats[name]}')

    # ==============================================================================================
    print("\n=== Technique 6 [EASIEST/BEST]: using a list comprehension with `zip()` and direct " +
          "variable assignment ===")
    # For more styles and ways to use list comprehensions, see:
    # https://stackoverflow.com/a/55557758/4561887
    # ==============================================================================================

    name = "list_comprehension_w_zip_and_direct_variable_assignment"
    df = df_original.copy()  # make a copy of the original dataframe to work with
    time_start_sec = time.monotonic()

    df["val"] = [
        # Note: this *could* be a lambda here instead of a function call. I'm using a function call.
        calculate_val(
            A_i_minus_2,
            A_i_minus_1,
            A,
            A_i_plus_1,
            B,
            C,
            D
        ) for A_i_minus_2, A_i_minus_1, A, A_i_plus_1, B, C, D
        in zip(
            df["A_i_minus_2"],
            df["A_i_minus_1"],
            df["A"],
            df["A_i_plus_1"],
            df["B"],
            df["C"],
            df["D"]
        )
    ]

    df["val"] = val  # put this column back into the dataframe
    time_end_sec = time.monotonic()
    print(f"len(val) = {len(val)}") # debugging
    # print(f"val[:10] = {val[:10]}") # debugging
    # print(f"val[-10:] = {val[-10:]}") # debugging

    dt_sec[name] = time_end_sec - time_start_sec
    val_stats[name] = df["val"].describe()  # summary statistics

    print(f"{FBL}dt_sec[{name}] = {dt_sec[name]:.6f} sec{F}")
    print(f'val_stats[{name}]:\n------\n{val_stats[name]}')

    # ==============================================================================================
    print("\n=== Technique 7: using a list comprehension with `zip()` and `row` tuple ===")
    # For more styles and ways to use list comprehensions, see:
    # https://stackoverflow.com/a/55557758/4561887
    # ==============================================================================================

    name = "list_comprehension_w_zip_and_row_tuple"
    df = df_original.copy()  # make a copy of the original dataframe to work with
    time_start_sec = time.monotonic()

    df["val"] = [
        calculate_val(
            row[0],
            row[1],
            row[2],
            row[3],
            row[4],
            row[5],
            row[6],
        ) for row
        in zip(
            df["A_i_minus_2"],
            df["A_i_minus_1"],
            df["A"],
            df["A_i_plus_1"],
            df["B"],
            df["C"],
            df["D"]
        )
    ]

    df["val"] = val  # put this column back into the dataframe
    time_end_sec = time.monotonic()
    print(f"len(val) = {len(val)}") # debugging
    # print(f"val[:10] = {val[:10]}") # debugging
    # print(f"val[-10:] = {val[-10:]}") # debugging

    dt_sec[name] = time_end_sec - time_start_sec
    val_stats[name] = df["val"].describe()  # summary statistics

    print(f"{FBL}dt_sec[{name}] = {dt_sec[name]:.6f} sec{F}")
    print(f'val_stats[{name}]:\n------\n{val_stats[name]}')

    # ==============================================================================================
    print("\n=== Technique 8: using a list comprehension with `.to_numpy()` and direct " +
          "variable assignment ===")
    # Notes:
    # 1. This could be done with a `row` tuple, as just above, too, but I won't show that minor
    # variation.
    # 1. For more styles and ways to use list comprehensions, see:
    # https://stackoverflow.com/a/55557758/4561887. This answer also states:
    #   > When dealing with mixed data types you should iterate over `zip(df['A'], df['B'], ...)`
    #   > instead of `df[['A', 'B']].to_numpy()` as the latter implicitly upcasts data to the most
    #   > common type. As an example, if `A` is numeric and `B` is string, `to_numpy()` will cast
    #   > the entire array to string, which may not be what you want. Fortunately, zipping your
    #   > columns together is the most straightforward workaround to this.
    # ==============================================================================================

    name = "list_comprehension_w__to_numpy__and_direct_variable_assignment"
    df = df_original.copy()  # make a copy of the original dataframe to work with
    time_start_sec = time.monotonic()

    df["val"] = [
        # Note: this *could* be a lambda here instead of a function call. I'm using a function call.
        calculate_val(
            A_i_minus_2,
            A_i_minus_1,
            A,
            A_i_plus_1,
            B,
            C,
            D
        ) for A_i_minus_2, A_i_minus_1, A, A_i_plus_1, B, C, D
        # Note: this `[[...]]` syntax is called "double-bracket indexing" and is used to select a
        # subset of columns from the dataframe, kind of like boolean indexing. The inner `[]`
        # brackets create a list from the column names within them, and the outer `[]` brackets
        # accept this list to index into the dataframe and select just this list of columns.
        # - One of the **list comprehension** examples in this answer here uses `.to_numpy()` like
        #   this: https://stackoverflow.com/a/55557758/4561887
        in df[[
            "A_i_minus_2",
            "A_i_minus_1",
            "A",
            "A_i_plus_1",
            "B",
            "C",
            "D"
        ]].to_numpy()  # NB: `.values` works here too, but is deprecated. See:
                       # https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.values.html
    ]

    df["val"] = val  # put this column back into the dataframe
    time_end_sec = time.monotonic()
    print(f"len(val) = {len(val)}") # debugging
    # print(f"val[:10] = {val[:10]}") # debugging
    # print(f"val[-10:] = {val[-10:]}") # debugging

    dt_sec[name] = time_end_sec - time_start_sec
    val_stats[name] = df["val"].describe()  # summary statistics

    print(f"{FBL}dt_sec[{name}] = {dt_sec[name]:.6f} sec{F}")
    print(f'val_stats[{name}]:\n------\n{val_stats[name]}')

    # =================================== END OF TECHNIQUES ========================================
    # Collect and prepare data for plotting
    # ==============================================================================================
    assert_all_stats_are_equal(val_stats)
    print()

    # delete this key/value pair since it is not needed for plotting
    del dt_sec["adding_shifted_data"]

    results_dict = {
        "Method": list(dt_sec.keys()),
        "Time_sec": list(dt_sec.values()),
    }
    results_df = pd.DataFrame(results_dict) # columns are "Method" and "Time_sec"
    results_df = results_df.sort_values(by="Time_sec", axis='rows', ascending=False)
    # Be sure to reset the indices after sorting, or else the indices will be sorted out of their
    # original order now too!
    # - Note: this defaults to `drop=False`, which means the old indices will be kept in a new column
    #   called "index" now. If you want to drop the old indices instead of putting them into a new
    #   column, pass argument `drop=True`.
    results_df = results_df.reset_index()
    results_df["Method_short_names"] = results_df["Method"].apply(
        lambda s: add_newlines_every_n_chars(s, 12))

    #########
    # Now plot the results in a bar chart
    plot_data(results_df) ##### TODO: add plotting code per the example in the file above; increase the number of samples to get longer calculation times

    plt.show()  # show all figures


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    Run it and see the output in "eRCaGuy_hello_world/fake_data/figures"

"""
