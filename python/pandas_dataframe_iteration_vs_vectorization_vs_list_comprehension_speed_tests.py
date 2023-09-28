#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Use the Pandas library to manipulate a DataFrame using iteration vs vectorization vs list
comprehension, and compare the speed tests results.

The question I'm trying to answer is:
What are the various ways to do iteration-like things over a Pandas DataFrame with*out* actually
doing Python iteration, which is slow, and how do they compare in speed?

Status: Done and works!

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
import re
import time

# See: "eRCaGuy_hello_world/python/import_helper.py"
FULL_PATH_TO_SCRIPT = os.path.abspath(__file__)
SCRIPT_DIRECTORY = str(os.path.dirname(FULL_PATH_TO_SCRIPT))
FILENAME = os.path.basename(FULL_PATH_TO_SCRIPT)
FILENAME_NO_EXTENSION = os.path.splitext(FILENAME)[0]

# For text formatting and colorization in the terminal.
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


DEBUG_ON = False  # set to False to disable debug prints

def debug_print(*args, **kwargs):
    if DEBUG_ON:
        print("DEBUG: ", *args, **kwargs)


def save_figure(filename):
    plt.savefig(f'{SCRIPT_DIRECTORY}/{filename}.svg')
    plt.savefig(f'{SCRIPT_DIRECTORY}/{filename}.png')


def add_newlines_every_n_chars(s, n):
    """
    ********** NOTE **********
    ORIGINALLY COPIED from my own code in "pandas_plot_bar_chart_better_GREAT_AUTOLABEL_DATA.py",
    but this here is now the most-up-to-date version of it.
    **************************

    Add a newline character to a string at the nearest underscore (`_`), space (` `), or dash (`-`)
    to the nth character. This is useful for making long labels fit on a plot.

    - Aided by GitHub CoPilot

    TODO:
    1. [ ] add unit tests. Example test cases/strings:
        name = "8_list_comprehension_w__to_numpy__and_direct_variable_assignment"
        name = "8_list comprehension_w__to_numpy--and_direct-variable assignment"
        name = "8listcomprehensionwtonumpyanddirectvariableassignment"
    1. [x] think through this really deeply and make sure it's correct. I'm not sure it's right, and
       it could easily have some "off by one" type problems in the logic and indexing!
       DONE!: the logic is correct; tested by carefully studying the debugging prints!
    """
    # return '\n'.join(s[i:i+n] for i in range(0, len(s), n))

    regex_pattern = r"[ _-]"

    remaining_chars = len(s)
    i_start = 0

    while remaining_chars > n:
        # If there is no underscore in the range, split at the nth character from the start, so make
        # this the default
        split_index = i_start + n
        if split_index >= len(s):
            break

        debug_print(f"len(s) = {len(s)}; n = {n}; n//2 = {n//2}")
        debug_print(f"bytes object (s.encode()) = {s.encode()}")
        debug_print(f"remaining_chars = {remaining_chars}")
        debug_print(f"i_start = {i_start}")
        debug_print(f"split_index = {split_index}")

        # Find the char of interest which is nearest to the nth character
        # See: https://docs.python.org/3/library/re.html#re.search
        match = re.search(regex_pattern, s[i_start + n//2:i_start + n + n//2])
        if match:
            debug_print(f"match.start() (offset by (i_start + n//2) = "
                      + f"{i_start + n//2}) = {match.start()}")

            # If there is a match, split one char to the right of the match, just after the matching
            # char we found
            split_index = i_start + n//2 + match.start() + 1
            debug_print(f"split_index = i_start + n//2 + match.start() + 1 = "
                      + f"{i_start} + {n//2} + {match.start()} + 1 = {split_index}")
            if split_index >= len(s):
                break

        # Split the string
        s = s[:split_index] + '\n' + s[split_index:]

        remaining_chars = len(s) - split_index - 1  # subtract the 1 we added above
        i_start = split_index + 1  # + 1 to go to the right of the newline char we just inserted

        debug_print(f"len(s) = {len(s)}; n = {n}; n//2 = {n//2}")
        debug_print(f"bytes object (s.encode()) = {s.encode()}")
        debug_print(f"remaining_chars = {remaining_chars}")
        debug_print(f"i_start = {i_start}")
        debug_print()

    return s


def plot_data(results_df, num_data_rows, num_data_cols):
    """
    Plot **and automatically label** the data in the given dataframe.

    ********** NOTE **********
    - This code was copied from:
      "eRCaGuy_hello_world/python/pandas_plot_bar_chart_better_GREAT_AUTOLABEL_DATA.py", but
      this here is now the most-up-to-date version of it.
    **************************
    """

    # create a bar chart
    fig = plt.figure(figsize=(19, 13))  # default is `(6.4, 4.8)` inches
    plt.bar(results_df["Method_short_names"], results_df["Time_sec"])
    plt.title(f'Computation time vs Pandas iteration technique over {num_data_rows:,} rows ' +
              f'x {num_data_cols} columns\n' +
              f'in a DataFrame (*Lower* is better; {len(results_df)} techniques tested).',
              fontsize=14)
    plt.xlabel('Iteration technique', labelpad=15, fontsize=12) # use labelpad to lower the label
    plt.ylabel('Computation time (sec)', fontsize=12)

    # Prepare to add text labels to each bar
    results_df["text_x"] = results_df.index # use the indices as the x-positions
    results_df["text_y"] = results_df["Time_sec"] + 0.05*results_df["Time_sec"].max()
    results_df["time_multiplier"] = results_df["Time_sec"] / results_df["Time_sec"].min()
    results_df["text_label"] = (results_df["Time_sec"].map("{:.4f} sec\n".format) +
                                results_df["time_multiplier"].map("{:.2f}x".format))

    # Use a list comprehension to actually call `plot.text()` to **automatically add a plot label**
    # for each row in the dataframe
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
    # increase the whitespace under the figure to leave space for long, wrapping labels; decrease
    # the whitespace on all other sides
    fig.subplots_adjust(left=0.05, right=0.95, top=0.95, bottom=0.15)
    save_figure(FILENAME_NO_EXTENSION)


def calculate_new_column_b_value(b_value):
    b_value_new = (6 * b_value) if b_value > 0 else (60 * b_value)  # Python ternary operator
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
          + ((6 * B_i) if B > 0 else (60 * B_i))  # don't forget parenthesis around the whole line!
          + 7 * C_i
          - 8 * D_i
    """
    val = (
        2 * A_i_minus_2
        + 3 * A_i_minus_1
        + 4 * A
        + 5 * A_i_plus_1
        # Python ternary operator; don't forget parentheses around the entire ternary expression!
        + ((6 * B) if B > 0 else (60 * B))
        + 7 * C
        - 8 * D
    )
    return val


def assert_all_results_are_equal(df_dict):
    """
    Assert that all val series objects from each calculation technique are the same.
    """
    print()
    # Get the first technique's val series as the "golden" one to compare against
    df_first = df_dict[list(df_dict.keys())[0]]
    series_first = df_first["val"]
    for name, df in df_dict.items():
        print(f"Checking stats for technique \"{name}\"")

        debug_print(df)
        debug_print(f"\ndf.dtypes =\n{df.dtypes}\n\n")

        assert_series_equal(df["val"], series_first)

    print(f"{FGR}Tests passed: the results of all techniques are equal!{F}\n")
    print(f"df_first =\n{df_first}\n\n")
    print(f"Summary statistics:\n{series_first.describe()}")


def run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict):
    """
    Run and time a DataFrame iteration technique.

    Args:
    - technique_to_run_and_time: a function to run and time; this must be a closure which has access to
        the variables in `main()'s scope.
    """
    df = df_original.copy()  # make a copy of the original dataframe to work with

    time_start_sec = time.monotonic()
    technique_to_run_and_time(df)
    time_end_sec = time.monotonic()

    val = df["val"]
    print(f"len(val) = {len(val)}") # debugging
    # print(f"val[:10] = {val[:10]}") # debugging
    # print(f"val[-10:] = {val[-10:]}") # debugging

    dt_sec[name] = time_end_sec - time_start_sec
    # Note: no need to `.copy()` this again, since we created `df` from a copy above already
    df_dict[name] = df

    print(f"{FBL}dt_sec[{name}] = {dt_sec[name]:.6f} sec{F}")
    print(f'df_dict[{name}]:\n------\n{df_dict[name]}')


def main():
    """
    The main function of this program.
    """

    mkdir(f"{SCRIPT_DIRECTORY}/../fake_data/figures")

    # Create an array (numpy list of lists) of fake data
    MIN_VAL = -1000
    MAX_VAL = 1000
    # NUM_ROWS = 10_000_000
    NUM_ROWS = 2_000_000  # default for final tests
    # NUM_ROWS = 1_000_000
    # NUM_ROWS = 100_000
    # NUM_ROWS = 10_000  # default for rapid development & initial tests
    NUM_COLS = 4
    data = np.random.randint(MIN_VAL, MAX_VAL, size=(NUM_ROWS, NUM_COLS))

    # Now convert it to a Pandas DataFrame with columns named "A", "B", "C", and "D"
    df_original = pd.DataFrame(data, columns=["A", "B", "C", "D"])
    print(f"dataframe = \n{df_original}")

    # Now calculate a new column, "val", using a variety of techniques, by following the formula
    # inside `calculate_val()`

    dt_sec = {}  # dictionary of time deltas in seconds
    df_dict = {}   # dictionary mapping string names to Pandas DataFrame objects
    technique_num = 0

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num}: raw Python `for` loop using regular df indexing ===")
    # ==============================================================================================
    name = f"{technique_num}_raw_for_loop_using_regular_df_indexing"
    def technique_to_run_and_time(df):

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

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num}: raw Python `for` loop using `df.loc[]` " +
           "label-based indexing ===")
    # ==============================================================================================
    name = f"{technique_num}_raw_for_loop_using_df.loc[]_indexing"
    def technique_to_run_and_time(df):

        val = [np.NAN]*len(df)
        for i in range(len(df)):
            if i < 2 or i > len(df)-2:
                continue

            val[i] = calculate_val(
                df.loc[i-2, "A"],
                df.loc[i-1, "A"],
                df.loc[i,   "A"],
                df.loc[i+1, "A"],
                df.loc[i,   "B"],
                df.loc[i,   "C"],
                df.loc[i,   "D"],
            )

        df["val"] = val  # put this column back into the dataframe

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num}: raw Python `for` loop using `df.iloc[]` " +
           "index-based indexing ===")
    # ==============================================================================================
    name = f"{technique_num}_raw_for_loop_using_df.iloc[]_indexing"
    def technique_to_run_and_time(df):

        # column indices
        i_A = 0
        i_B = 1
        i_C = 2
        i_D = 3

        val = [np.NAN]*len(df)
        for i in range(len(df)):
            if i < 2 or i > len(df)-2:
                continue

            val[i] = calculate_val(
                df.iloc[i-2, i_A],
                df.iloc[i-1, i_A],
                df.iloc[i,   i_A],
                df.iloc[i+1, i_A],
                df.iloc[i,   i_B],
                df.iloc[i,   i_C],
                df.iloc[i,   i_D],
            )

        df["val"] = val  # put this column back into the dataframe

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num} [BAD-**NEVER** USE!]: use `iterrows()` in a Python `for` loop ===")
    # ==============================================================================================
    name = f"{technique_num}_iterrows_in_for_loop"
    def technique_to_run_and_time(df):

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

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

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
    technique_num += 1
    print(f"\n=== Technique {technique_num}: named `itertuples()` in a Python `for` loop ===")
    # See here for this and other `itertuples()`-based techniques:
    # https://stackoverflow.com/a/59413206/4561887
    # ==============================================================================================
    name = f"{technique_num}_itertuples_in_for_loop"
    def technique_to_run_and_time(df):

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

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num}: vectorization, w/`apply()` for " +
           "if statement corner-case ===")
    # ==============================================================================================
    name = f"{technique_num}_vectorization__with_apply_for_if_statement_corner_case"
    def technique_to_run_and_time(df):

        # In this particular example, since we have an embedded `if-else` statement for the `B` column,
        # pure vectorization is less intuitive. So, first we'll calculate a new `B` column using
        # **`apply()`**, then we'll use vectorization for the rest.
        df["B_new"] = df["B"].apply(calculate_new_column_b_value)
        # OR (same thing, but with a lambda function instead)
        # df["B_new"] = df["B"].apply(lambda x: (6 * x) if x > 0 else (60 * x))

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

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num}: vectorization, w/list comprehension for " +
           "if statement corner-case ===")
    # ==============================================================================================
    name = f"{technique_num}_vectorization__with_list_comprehension_for_if_statment_corner_case"
    def technique_to_run_and_time(df):

        # In this particular example, since we have an embedded `if-else` statement for the `B` column,
        # pure vectorization is less intuitive. So, first we'll calculate a new `B` column using **list
        # comprehension**, then we'll use vectorization for the rest.
        df["B_new"] = [
            calculate_new_column_b_value(b_value) for b_value in df["B"]
        ]

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

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num}: pure vectorization: w/`df.loc[]` " +
           "boolean array indexing for if statement corner-case ===")
    # ==============================================================================================
    name = f"{technique_num}_pure_vectorization__with_df.loc[]_boolean_array_indexing_for_if_statment_corner_case"
    def technique_to_run_and_time(df):

        # If statement to evaluate:
        #
        #     if B > 0:
        #         B_new = 6 * B
        #     else:
        #         B_new = 60 * B
        #
        # In this particular example, since we have an embedded `if-else` statement for the `B` column,
        # we can use some boolean array indexing through `df.loc[]` for some pure vectorization magic.
        #
        # Explanation:
        #
        # Long:
        # The format is: `df.loc[rows, columns]`, except in this case, the rows are specified by a
        # "boolean array" (AKA: a boolean expression, list of booleans, or "boolean mask"), specifying
        # all rows where `B` is
        # > 0. Then, only in that `B` column for those rows, set the value accordingly. After we do this
        # for where `B` is > 0, we do the same thing for where `B` is <= 0, except with the other
        # equation.
        #
        # Short:
        # For all rows where the boolean expression applies, set the column value accordingly.
        #
        # GitHub CoPilot first showed me this `.loc[]` technique.
        # See also the official documentation:
        # https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.loc.html
        #
        # 1st: handle the > 0 case
        df["B_new"] = df.loc[df["B"] > 0, "B"] * 6
        # 2nd: handle the <= 0 case, merging the results into the previously-created "B_new" column
        # - NB: this doesn't work; it overwrites and replaces the whole "B_new" column instead:
        #
        #       df["B_new"] = df.loc[df["B"] <= 0, "B"] * 60
        #
        df.loc[df["B"] <= 0, "B_new"] = df.loc[df["B"] <= 0, "B"] * 60

        # Now use normal vectorization for the rest.
        df["val"] = (
            2 * df["A_i_minus_2"]
            + 3 * df["A_i_minus_1"]
            + 4 * df["A"]
            + 5 * df["A_i_plus_1"]
            + df["B_new"]
            + 7 * df["C"]
            - 8 * df["D"]
        )

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num}: using the `apply()` function with a lambda ===")
    # See:
    # 1. How to use `apply()` with multiple columns in a given row!:
    # https://stackoverflow.com/a/30566899/4561887
    # 1. https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.apply.html
    # ==============================================================================================
    name = f"{technique_num}_apply_function_with_lambda"
    def technique_to_run_and_time(df):

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

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num} [EASIEST/VERY GOOD]: using a list comprehension " +
           "with `zip()` and direct variable assignment passed to func ===")
    # For more styles and ways to use list comprehensions, see:
    # https://stackoverflow.com/a/55557758/4561887
    # ==============================================================================================
    name = f"{technique_num}_list_comprehension_w_zip_and_direct_variable_assignment_passed_to_func"
    def technique_to_run_and_time(df):

        df["val"] = [
            # Note: you *could* do the calculations directly here instead of using a function call, so
            # long as you don't have indented code blocks such as sub-routines or multi-line if
            # statements.
            # I'm using a function call.
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

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num} [EASIEST/VERY GOOD]: using a list comprehension " +
           "with `zip()` and direct variable assignment calculated in place ===")
    # For more styles and ways to use list comprehensions, see:
    # https://stackoverflow.com/a/55557758/4561887
    # ==============================================================================================
    name = f"{technique_num}_list_comprehension_w_zip_and_direct_variable_assignment_calculated_in_place"
    def technique_to_run_and_time(df):

        df["val"] = [
            2 * A_i_minus_2
            + 3 * A_i_minus_1
            + 4 * A
            + 5 * A_i_plus_1
            # Python ternary operator; don't forget parentheses around the entire ternary expression!
            + ((6 * B) if B > 0 else (60 * B))
            + 7 * C
            - 8 * D
            for A_i_minus_2, A_i_minus_1, A, A_i_plus_1, B, C, D
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

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num}: using a list comprehension with `zip()` and `row` " +
          "tuple passed to func ===")
    # For more styles and ways to use list comprehensions, see:
    # https://stackoverflow.com/a/55557758/4561887
    # ==============================================================================================
    name = f"{technique_num}_list_comprehension_w_zip_and_row_tuple_passed_to_func"
    def technique_to_run_and_time(df):

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

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    technique_num += 1
    print(f"\n=== Technique {technique_num}: using a list comprehension with `.to_numpy()` " +
          "and direct variable assignment passed to func ===")
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
    name = f"{technique_num}_list_comprehension_w__to_numpy__and_direct_variable_assignment_passed_to_func"
    def technique_to_run_and_time(df):

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

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # =================================== END OF TECHNIQUES ========================================
    # Collect and prepare data for plotting
    # ==============================================================================================
    assert_all_results_are_equal(df_dict)
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

    # Now plot the results in a bar chart
    plot_data(results_df, NUM_ROWS, NUM_COLS)

    plt.show()  # show all figures


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

eRCaGuy_hello_world$ time python/pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py
dataframe =
           A    B    C    D
0       -365  842  284 -942
1        532  416 -102  888
2        397  321 -296 -616
3       -215  879  557  895
4        857  701 -157  480
...      ...  ...  ...  ...
1999995 -101 -233 -377 -939
1999996 -989  380  917  145
1999997 -879  333 -372 -970
1999998  738  982 -743  312
1999999 -306 -103  459  745

[2000000 rows x 4 columns]

=== Technique 1: raw Python `for` loop using regular df indexing ===
len(val) = 2000000
dt_sec[1_raw_for_loop_using_regular_df_indexing] = 33.603625 sec
df_dict[1_raw_for_loop_using_regular_df_indexing]:
------
           A    B    C    D      val
0       -365  842  284 -942      NaN
1        532  416 -102  888      NaN
2        397  321 -296 -616   6161.0
3       -215  879  557  895   7693.0
4        857  701 -157  480   5864.0
...      ...  ...  ...  ...      ...
1999995 -101 -233 -377 -939 -12195.0
1999996 -989  380  917  145    243.0
1999997 -879  333 -372 -970   4159.0
1999998  738  982 -743  312  -4998.0
1999999 -306 -103  459  745      NaN

[2000000 rows x 5 columns]

=== Technique 2: raw Python `for` loop using `df.loc[]` label-based indexing ===
len(val) = 2000000
dt_sec[2_raw_for_loop_using_df.loc[]_indexing] = 54.561268 sec
df_dict[2_raw_for_loop_using_df.loc[]_indexing]:
------
           A    B    C    D      val
0       -365  842  284 -942      NaN
1        532  416 -102  888      NaN
2        397  321 -296 -616   6161.0
3       -215  879  557  895   7693.0
4        857  701 -157  480   5864.0
...      ...  ...  ...  ...      ...
1999995 -101 -233 -377 -939 -12195.0
1999996 -989  380  917  145    243.0
1999997 -879  333 -372 -970   4159.0
1999998  738  982 -743  312  -4998.0
1999999 -306 -103  459  745      NaN

[2000000 rows x 5 columns]

=== Technique 3: raw Python `for` loop using `df.iloc[]` index-based indexing ===
len(val) = 2000000
dt_sec[3_raw_for_loop_using_df.iloc[]_indexing] = 135.124845 sec
df_dict[3_raw_for_loop_using_df.iloc[]_indexing]:
------
           A    B    C    D      val
0       -365  842  284 -942      NaN
1        532  416 -102  888      NaN
2        397  321 -296 -616   6161.0
3       -215  879  557  895   7693.0
4        857  701 -157  480   5864.0
...      ...  ...  ...  ...      ...
1999995 -101 -233 -377 -939 -12195.0
1999996 -989  380  917  145    243.0
1999997 -879  333 -372 -970   4159.0
1999998  738  982 -743  312  -4998.0
1999999 -306 -103  459  745      NaN

[2000000 rows x 5 columns]

=== Technique 4 [BAD-**NEVER** USE!]: use `iterrows()` in a Python `for` loop ===
len(val) = 2000000
dt_sec[4_iterrows_in_for_loop] = 57.582548 sec
df_dict[4_iterrows_in_for_loop]:
------
           A    B    C    D      val
0       -365  842  284 -942      NaN
1        532  416 -102  888      NaN
2        397  321 -296 -616   6161.0
3       -215  879  557  895   7693.0
4        857  701 -157  480   5864.0
...      ...  ...  ...  ...      ...
1999995 -101 -233 -377 -939 -12195.0
1999996 -989  380  917  145    243.0
1999997 -879  333 -372 -970   4159.0
1999998  738  982 -743  312  -4998.0
1999999 -306 -103  459  745      NaN

[2000000 rows x 5 columns]

=== For all of the next examples, we must first prepare the dataframe by adding
columns with previous and next values: A_(i-2), A_(i-1), and A_(i+1). ===
dt_sec[adding_shifted_data] = 0.044961 sec

=== Technique 5: named `itertuples()` in a Python `for` loop ===
len(val) = 2000000
dt_sec[5_itertuples_in_for_loop] = 1.519371 sec
df_dict[5_itertuples_in_for_loop]:
------
             A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2        397.0  321.0 -296.0 -616.0       -365.0        532.0      -215.0   6161.0
3       -215.0  879.0  557.0  895.0        532.0        397.0       857.0   7693.0
4        857.0  701.0 -157.0  480.0        397.0       -215.0       604.0   5864.0
...        ...    ...    ...    ...          ...          ...         ...      ...
1999995 -101.0 -233.0 -377.0 -939.0        112.0        679.0      -989.0 -12195.0
1999996 -989.0  380.0  917.0  145.0        679.0       -101.0      -879.0    243.0
1999997 -879.0  333.0 -372.0 -970.0       -101.0       -989.0       738.0   4159.0
1999998  738.0  982.0 -743.0  312.0       -989.0       -879.0      -306.0  -4998.0
1999999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[2000000 rows x 8 columns]

=== Technique 6: vectorization, w/`apply()` for if statement corner-case ===
len(val) = 2000000
dt_sec[6_vectorization__with_apply_for_if_statement_corner_case] = 0.251125 sec
df_dict[6_vectorization__with_apply_for_if_statement_corner_case]:
------
             A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1    B_new      val
0          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
1          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
2        397.0  321.0 -296.0 -616.0       -365.0        532.0      -215.0   1926.0   6161.0
3       -215.0  879.0  557.0  895.0        532.0        397.0       857.0   5274.0   7693.0
4        857.0  701.0 -157.0  480.0        397.0       -215.0       604.0   4206.0   5864.0
...        ...    ...    ...    ...          ...          ...         ...      ...      ...
1999995 -101.0 -233.0 -377.0 -939.0        112.0        679.0      -989.0 -13980.0 -12195.0
1999996 -989.0  380.0  917.0  145.0        679.0       -101.0      -879.0   2280.0    243.0
1999997 -879.0  333.0 -372.0 -970.0       -101.0       -989.0       738.0   1998.0   4159.0
1999998  738.0  982.0 -743.0  312.0       -989.0       -879.0      -306.0   5892.0  -4998.0
1999999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN

[2000000 rows x 9 columns]

=== Technique 7: vectorization, w/list comprehension for if statement corner-case ===
len(val) = 2000000
dt_sec[7_vectorization__with_list_comprehension_for_if_statment_corner_case] = 0.305493 sec
df_dict[7_vectorization__with_list_comprehension_for_if_statment_corner_case]:
------
             A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1    B_new      val
0          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
1          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
2        397.0  321.0 -296.0 -616.0       -365.0        532.0      -215.0   1926.0   6161.0
3       -215.0  879.0  557.0  895.0        532.0        397.0       857.0   5274.0   7693.0
4        857.0  701.0 -157.0  480.0        397.0       -215.0       604.0   4206.0   5864.0
...        ...    ...    ...    ...          ...          ...         ...      ...      ...
1999995 -101.0 -233.0 -377.0 -939.0        112.0        679.0      -989.0 -13980.0 -12195.0
1999996 -989.0  380.0  917.0  145.0        679.0       -101.0      -879.0   2280.0    243.0
1999997 -879.0  333.0 -372.0 -970.0       -101.0       -989.0       738.0   1998.0   4159.0
1999998  738.0  982.0 -743.0  312.0       -989.0       -879.0      -306.0   5892.0  -4998.0
1999999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN

[2000000 rows x 9 columns]

=== Technique 8: pure vectorization: w/`df.loc[]` boolean array indexing for if statement corner-case ===
len(val) = 2000000
dt_sec[8_pure_vectorization__with_df.loc[]_boolean_array_indexing_for_if_statment_corner_case] = 0.099171 sec
df_dict[8_pure_vectorization__with_df.loc[]_boolean_array_indexing_for_if_statment_corner_case]:
------
             A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1    B_new      val
0          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
1          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
2        397.0  321.0 -296.0 -616.0       -365.0        532.0      -215.0   1926.0   6161.0
3       -215.0  879.0  557.0  895.0        532.0        397.0       857.0   5274.0   7693.0
4        857.0  701.0 -157.0  480.0        397.0       -215.0       604.0   4206.0   5864.0
...        ...    ...    ...    ...          ...          ...         ...      ...      ...
1999995 -101.0 -233.0 -377.0 -939.0        112.0        679.0      -989.0 -13980.0 -12195.0
1999996 -989.0  380.0  917.0  145.0        679.0       -101.0      -879.0   2280.0    243.0
1999997 -879.0  333.0 -372.0 -970.0       -101.0       -989.0       738.0   1998.0   4159.0
1999998  738.0  982.0 -743.0  312.0       -989.0       -879.0      -306.0   5892.0  -4998.0
1999999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN

[2000000 rows x 9 columns]

=== Technique 9: using the `apply()` function with a lambda ===
len(val) = 2000000
dt_sec[9_apply_function_with_lambda] = 18.518937 sec
df_dict[9_apply_function_with_lambda]:
------
             A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2        397.0  321.0 -296.0 -616.0       -365.0        532.0      -215.0   6161.0
3       -215.0  879.0  557.0  895.0        532.0        397.0       857.0   7693.0
4        857.0  701.0 -157.0  480.0        397.0       -215.0       604.0   5864.0
...        ...    ...    ...    ...          ...          ...         ...      ...
1999995 -101.0 -233.0 -377.0 -939.0        112.0        679.0      -989.0 -12195.0
1999996 -989.0  380.0  917.0  145.0        679.0       -101.0      -879.0    243.0
1999997 -879.0  333.0 -372.0 -970.0       -101.0       -989.0       738.0   4159.0
1999998  738.0  982.0 -743.0  312.0       -989.0       -879.0      -306.0  -4998.0
1999999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[2000000 rows x 8 columns]

=== Technique 10 [EASIEST/VERY GOOD]: using a list comprehension with `zip()` and direct variable assignment passed to func ===
len(val) = 2000000
dt_sec[10_list_comprehension_w_zip_and_direct_variable_assignment_passed_to_func] = 0.999363 sec
df_dict[10_list_comprehension_w_zip_and_direct_variable_assignment_passed_to_func]:
------
             A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2        397.0  321.0 -296.0 -616.0       -365.0        532.0      -215.0   6161.0
3       -215.0  879.0  557.0  895.0        532.0        397.0       857.0   7693.0
4        857.0  701.0 -157.0  480.0        397.0       -215.0       604.0   5864.0
...        ...    ...    ...    ...          ...          ...         ...      ...
1999995 -101.0 -233.0 -377.0 -939.0        112.0        679.0      -989.0 -12195.0
1999996 -989.0  380.0  917.0  145.0        679.0       -101.0      -879.0    243.0
1999997 -879.0  333.0 -372.0 -970.0       -101.0       -989.0       738.0   4159.0
1999998  738.0  982.0 -743.0  312.0       -989.0       -879.0      -306.0  -4998.0
1999999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[2000000 rows x 8 columns]

=== Technique 11 [EASIEST/VERY GOOD]: using a list comprehension with `zip()` and direct variable assignment calculated in place ===
len(val) = 2000000
dt_sec[11_list_comprehension_w_zip_and_direct_variable_assignment_calculated_in_place] = 0.853953 sec
df_dict[11_list_comprehension_w_zip_and_direct_variable_assignment_calculated_in_place]:
------
             A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2        397.0  321.0 -296.0 -616.0       -365.0        532.0      -215.0   6161.0
3       -215.0  879.0  557.0  895.0        532.0        397.0       857.0   7693.0
4        857.0  701.0 -157.0  480.0        397.0       -215.0       604.0   5864.0
...        ...    ...    ...    ...          ...          ...         ...      ...
1999995 -101.0 -233.0 -377.0 -939.0        112.0        679.0      -989.0 -12195.0
1999996 -989.0  380.0  917.0  145.0        679.0       -101.0      -879.0    243.0
1999997 -879.0  333.0 -372.0 -970.0       -101.0       -989.0       738.0   4159.0
1999998  738.0  982.0 -743.0  312.0       -989.0       -879.0      -306.0  -4998.0
1999999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[2000000 rows x 8 columns]

=== Technique 12: using a list comprehension with `zip()` and `row` tuple passed to func ===
len(val) = 2000000
dt_sec[12_list_comprehension_w_zip_and_row_tuple_passed_to_func] = 1.019849 sec
df_dict[12_list_comprehension_w_zip_and_row_tuple_passed_to_func]:
------
             A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2        397.0  321.0 -296.0 -616.0       -365.0        532.0      -215.0   6161.0
3       -215.0  879.0  557.0  895.0        532.0        397.0       857.0   7693.0
4        857.0  701.0 -157.0  480.0        397.0       -215.0       604.0   5864.0
...        ...    ...    ...    ...          ...          ...         ...      ...
1999995 -101.0 -233.0 -377.0 -939.0        112.0        679.0      -989.0 -12195.0
1999996 -989.0  380.0  917.0  145.0        679.0       -101.0      -879.0    243.0
1999997 -879.0  333.0 -372.0 -970.0       -101.0       -989.0       738.0   4159.0
1999998  738.0  982.0 -743.0  312.0       -989.0       -879.0      -306.0  -4998.0
1999999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[2000000 rows x 8 columns]

=== Technique 13: using a list comprehension with `.to_numpy()` and direct variable assignment passed to func ===
len(val) = 2000000
dt_sec[13_list_comprehension_w__to_numpy__and_direct_variable_assignment_passed_to_func] = 2.342621 sec
df_dict[13_list_comprehension_w__to_numpy__and_direct_variable_assignment_passed_to_func]:
------
             A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1          NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2        397.0  321.0 -296.0 -616.0       -365.0        532.0      -215.0   6161.0
3       -215.0  879.0  557.0  895.0        532.0        397.0       857.0   7693.0
4        857.0  701.0 -157.0  480.0        397.0       -215.0       604.0   5864.0
...        ...    ...    ...    ...          ...          ...         ...      ...
1999995 -101.0 -233.0 -377.0 -939.0        112.0        679.0      -989.0 -12195.0
1999996 -989.0  380.0  917.0  145.0        679.0       -101.0      -879.0    243.0
1999997 -879.0  333.0 -372.0 -970.0       -101.0       -989.0       738.0   4159.0
1999998  738.0  982.0 -743.0  312.0       -989.0       -879.0      -306.0  -4998.0
1999999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[2000000 rows x 8 columns]

Checking stats for technique "1_raw_for_loop_using_regular_df_indexing"
Checking stats for technique "2_raw_for_loop_using_df.loc[]_indexing"
Checking stats for technique "3_raw_for_loop_using_df.iloc[]_indexing"
Checking stats for technique "4_iterrows_in_for_loop"
Checking stats for technique "5_itertuples_in_for_loop"
Checking stats for technique "6_vectorization__with_apply_for_if_statement_corner_case"
Checking stats for technique "7_vectorization__with_list_comprehension_for_if_statment_corner_case"
Checking stats for technique "8_pure_vectorization__with_df.loc[]_boolean_array_indexing_for_if_statment_corner_case"
Checking stats for technique "9_apply_function_with_lambda"
Checking stats for technique "10_list_comprehension_w_zip_and_direct_variable_assignment_passed_to_func"
Checking stats for technique "11_list_comprehension_w_zip_and_direct_variable_assignment_calculated_in_place"
Checking stats for technique "12_list_comprehension_w_zip_and_row_tuple_passed_to_func"
Checking stats for technique "13_list_comprehension_w__to_numpy__and_direct_variable_assignment_passed_to_func"
Tests passed: the results of all techniques are equal!

df_first =
           A    B    C    D      val
0       -365  842  284 -942      NaN
1        532  416 -102  888      NaN
2        397  321 -296 -616   6161.0
3       -215  879  557  895   7693.0
4        857  701 -157  480   5864.0
...      ...  ...  ...  ...      ...
1999995 -101 -233 -377 -939 -12195.0
1999996 -989  380  917  145    243.0
1999997 -879  333 -372 -970   4159.0
1999998  738  982 -743  312  -4998.0
1999999 -306 -103  459  745      NaN

[2000000 rows x 5 columns]


Summary statistics:
count    1.999997e+06
mean    -1.354112e+04
std      2.190405e+04
min     -8.288600e+04
25%     -3.007800e+04
50%     -6.301000e+03
75%      3.505000e+03
max      3.122600e+04
Name: val, dtype: float64

results_df =
    index                                             Method    Time_sec                                 Method_short_names  text_x      text_y  time_multiplier              text_label
0       2            3_raw_for_loop_using_df.iloc[]_indexing  135.124845      3_raw_for_\nloop_using_\ndf.iloc[]_\nindexing       0  141.881087      1362.541659  135.1248 sec\n1362.54x
1       3                             4_iterrows_in_for_loop   57.582548                           4_iterrows_\nin_for_loop       1   64.338791       580.638010    57.5825 sec\n580.64x
2       1             2_raw_for_loop_using_df.loc[]_indexing   54.561268       2_raw_for_\nloop_using_\ndf.loc[]_\nindexing       2   61.317511       550.172703    54.5613 sec\n550.17x
3       0           1_raw_for_loop_using_regular_df_indexing   33.603625     1_raw_for_\nloop_using_\nregular_\ndf_indexing       3   40.359867       338.844711    33.6036 sec\n338.84x
4       8                       9_apply_function_with_lambda   18.518937                   9_apply_\nfunction_\nwith_lambda       4   25.275179       186.737113    18.5189 sec\n186.74x
5      12  13_list_comprehension_w__to_numpy__and_direct_...    2.342621  13_list_\ncomprehension_\nw__to_numpy_\n_and_d...       5    9.098863        23.621996      2.3426 sec\n23.62x
6       4                           5_itertuples_in_for_loop    1.519371                         5_itertuples_\nin_for_loop       6    8.275613        15.320689      1.5194 sec\n15.32x
7      11  12_list_comprehension_w_zip_and_row_tuple_pass...    1.019849  12_list_\ncomprehension_\nw_zip_and_\nrow_tupl...       7    7.776091        10.283723      1.0198 sec\n10.28x
8       9  10_list_comprehension_w_zip_and_direct_variabl...    0.999363  10_list_\ncomprehension_\nw_zip_and_\ndirect_\...       8    7.755605        10.077149      0.9994 sec\n10.08x
9      10  11_list_comprehension_w_zip_and_direct_variabl...    0.853953  11_list_\ncomprehension_\nw_zip_and_\ndirect_\...       9    7.610195         8.610896       0.8540 sec\n8.61x
10      6  7_vectorization__with_list_comprehension_for_i...    0.305493  7_vectorization_\n_with_list_\ncomprehension_\...      10    7.061735         3.080463       0.3055 sec\n3.08x
11      5  6_vectorization__with_apply_for_if_statement_c...    0.251125  6_vectorization_\n_with_apply_\nfor_if_\nstate...      11    7.007367         2.532234       0.2511 sec\n2.53x
12      7  8_pure_vectorization__with_df.loc[]_boolean_ar...    0.099171  8_pure_\nvectorization_\n_with_df.loc[]_\nbool...      12    6.855413         1.000000       0.0992 sec\n1.00x


"""
