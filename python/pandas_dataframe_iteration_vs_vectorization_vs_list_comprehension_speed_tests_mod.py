#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Same as "pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py", except
modify (hence the name "_mod") the first 4 techniques which iterate to NOT have the following `if`
statement check in them which may slow them down substantially:

            if i < 2 or i > len(df)-2:
                continue

I want to see how much faster those `for` loop techniques are withOUT having 2 million extra `if`
statement checks in them.
- So, this file now has **17** instead of 13 techniques in it.
- Search this file for the word "mod:" (case-INsensitive) to see the changes. OR, use `meld` to
  compare the two files:
  ```bash
  meld pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py \
      pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests_mod.py
  ```

Status: Done and works!

RESULT: it doesn't have much of an effect. It has only a minor improvement. See the plot:
"python/pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests_mod.svg".

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
    fig.subplots_adjust(left=0.05, right=0.95, top=0.95, bottom=0.25)
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
    # NUM_ROWS = 2_000_000  # default for final tests
    # NUM_ROWS = 1_000_000
    NUM_ROWS = 500_000  # long enough for fast but "good" tests
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
    # MOD: using the pre-shifted rows
    technique_num += 1
    print(f"\n=== Technique {technique_num}: raw Python `for` loop using regular df indexing "
          f"and the pre-shifted rows ===")
    # ==============================================================================================
    name = f"{technique_num}_MOD_raw_for_loop_using_regular_df_indexing_and_the_preshifted_rows"
    def technique_to_run_and_time(df):

        val = [np.NAN]*len(df)
        for i in range(len(df)):
            val[i] = calculate_val(
                df["A_i_minus_2"][i],
                df["A_i_minus_1"][i],
                df["A"][i],
                df["A_i_plus_1"][i],
                df["B"][i],
                df["C"][i],
                df["D"][i],
            )
        df["val"] = val  # put this column back into the dataframe

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    # MOD: using the pre-shifted rows
    technique_num += 1
    print(f"\n=== Technique {technique_num}: raw Python `for` loop using `df.loc[]` " +
           "label-based indexing and the pre-shifted rows ===")
    # ==============================================================================================
    name = f"{technique_num}_MOD_raw_for_loop_using_df.loc[]_indexing_and_the_preshifted_rows"
    def technique_to_run_and_time(df):

        val = [np.NAN]*len(df)
        for i in range(len(df)):
            val[i] = calculate_val(
                df.loc[i, "A_i_minus_2"],
                df.loc[i, "A_i_minus_1"],
                df.loc[i, "A"],
                df.loc[i, "A_i_plus_1"],
                df.loc[i, "B"],
                df.loc[i, "C"],
                df.loc[i, "D"],
            )

        df["val"] = val  # put this column back into the dataframe

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    # MOD: using the pre-shifted rows
    technique_num += 1
    print(f"\n=== Technique {technique_num}: raw Python `for` loop using `df.iloc[]` " +
           "index-based indexing and the pre-shifted rows ===")
    # ==============================================================================================
    name = f"{technique_num}_MOD_raw_for_loop_using_df.iloc[]_indexing_and_the_preshifted_rows"
    def technique_to_run_and_time(df):

        # column indices
        i_A = 0
        i_B = 1
        i_C = 2
        i_D = 3

        # These columns were added last, so these indices are the last 3 columns
        i_A_minus_2 = -3
        i_A_minus_1 = -2
        i_A_plus_1 = -1

        val = [np.NAN]*len(df)
        for i in range(len(df)):
            val[i] = calculate_val(
                df.iloc[i, i_A_minus_2],
                df.iloc[i, i_A_minus_1],
                df.iloc[i, i_A],
                df.iloc[i, i_A_plus_1],
                df.iloc[i, i_B],
                df.iloc[i, i_C],
                df.iloc[i, i_D],
            )

        df["val"] = val  # put this column back into the dataframe

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

    # ==============================================================================================
    # MOD: using the pre-shifted rows
    technique_num += 1
    print(f"\n=== Technique {technique_num} [BAD-**NEVER** USE!]: use `iterrows()` in a Python "
          f"`for` loop, and the pre-shifted rows ===")
    # ==============================================================================================
    name = f"{technique_num}_MOD_iterrows_in_for_loop_and_the_preshifted_rows"
    def technique_to_run_and_time(df):

        val = [np.NAN]*len(df)
        for index, row in df.iterrows():
            val[index] = calculate_val(
                row["A_i_minus_2"],
                row["A_i_minus_1"],
                row["A"],
                row["A_i_plus_1"],
                row["B"],
                row["C"],
                row["D"],
            )

        df["val"] = val  # put this column back into the dataframe

    run_and_time_this_technique(name, technique_to_run_and_time, df_original, dt_sec, df_dict)

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
            # Note: you *could* do the calculations directly here instead of using a
            # function call, so long as you don't have indented code blocks such as
            # sub-routines or multi-line if statements.
            #
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
            # Note: you *could* do the calculations directly here instead of using a
            # function call, so long as you don't have indented code blocks such as
            # sub-routines or multi-line if statements.
            #
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
            # Note: this `[[...]]` double-bracket indexing is used to select a subset of columns
            # from the dataframe. The inner `[]` brackets create a list from the column names within
            # them, and the outer `[]` brackets accept this list to index into the dataframe and
            # select just this list of columns, in that order.
            # - See the official documentation on it here:
            #   https://pandas.pydata.org/docs/user_guide/indexing.html#basics
            #   - Search for the phrase "You can pass a list of columns to [] to select columns in
            #     that order."
            #   - I learned this from this comment here:
            #     https://stackoverflow.com/questions/16476924/how-to-iterate-over-rows-in-a-dataframe-in-pandas/55557758#comment136020567_55557758
            # - One of the **list comprehension** examples in this answer here uses `.to_numpy()`
            #   like this: https://stackoverflow.com/a/55557758/4561887
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
        lambda s: add_newlines_every_n_chars(s, 9))

    # Now plot the results in a bar chart
    plot_data(results_df, NUM_ROWS, NUM_COLS)

    plt.show()  # show all figures


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

eRCaGuy_hello_world$ python/pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests_mod.py
dataframe =
          A    B    C    D
0      -951 -955  -70 -428
1      -226 -574 -389  602
2      -218 -955  661   82
3      -646 -617 -652  625
4      -443 -471  -19 -870
...     ...  ...  ...  ...
499995 -494   21 -710 -215
499996 -379  237  495 -381
499997  496  632  132  976
499998  -51 -114  279 -337
499999   78 -326  701  198

[500000 rows x 4 columns]

=== Technique 1: raw Python `for` loop using regular df indexing ===
len(val) = 500000
dt_sec[1_raw_for_loop_using_regular_df_indexing] = 8.824408 sec
df_dict[1_raw_for_loop_using_regular_df_indexing]:
------
          A    B    C    D      val
0      -951 -955  -70 -428      NaN
1      -226 -574 -389  602      NaN
2      -218 -955  661   82 -60011.0
3      -646 -617 -652  625 -52489.0
4      -443 -471  -19 -870 -22884.0
...     ...  ...  ...  ...      ...
499995 -494   21 -710 -215  -4013.0
499996 -379  237  495 -381   9217.0
499997  496  632  132  976  -3488.0
499998  -51 -114  279 -337  -1275.0
499999   78 -326  701  198      NaN

[500000 rows x 5 columns]

=== Technique 2: raw Python `for` loop using `df.loc[]` label-based indexing ===
len(val) = 500000
dt_sec[2_raw_for_loop_using_df.loc[]_indexing] = 14.355397 sec
df_dict[2_raw_for_loop_using_df.loc[]_indexing]:
------
          A    B    C    D      val
0      -951 -955  -70 -428      NaN
1      -226 -574 -389  602      NaN
2      -218 -955  661   82 -60011.0
3      -646 -617 -652  625 -52489.0
4      -443 -471  -19 -870 -22884.0
...     ...  ...  ...  ...      ...
499995 -494   21 -710 -215  -4013.0
499996 -379  237  495 -381   9217.0
499997  496  632  132  976  -3488.0
499998  -51 -114  279 -337  -1275.0
499999   78 -326  701  198      NaN

[500000 rows x 5 columns]

=== Technique 3: raw Python `for` loop using `df.iloc[]` index-based indexing ===
len(val) = 500000
dt_sec[3_raw_for_loop_using_df.iloc[]_indexing] = 35.398073 sec
df_dict[3_raw_for_loop_using_df.iloc[]_indexing]:
------
          A    B    C    D      val
0      -951 -955  -70 -428      NaN
1      -226 -574 -389  602      NaN
2      -218 -955  661   82 -60011.0
3      -646 -617 -652  625 -52489.0
4      -443 -471  -19 -870 -22884.0
...     ...  ...  ...  ...      ...
499995 -494   21 -710 -215  -4013.0
499996 -379  237  495 -381   9217.0
499997  496  632  132  976  -3488.0
499998  -51 -114  279 -337  -1275.0
499999   78 -326  701  198      NaN

[500000 rows x 5 columns]

=== Technique 4 [BAD-**NEVER** USE!]: use `iterrows()` in a Python `for` loop ===
len(val) = 500000
dt_sec[4_iterrows_in_for_loop] = 14.720045 sec
df_dict[4_iterrows_in_for_loop]:
------
          A    B    C    D      val
0      -951 -955  -70 -428      NaN
1      -226 -574 -389  602      NaN
2      -218 -955  661   82 -60011.0
3      -646 -617 -652  625 -52489.0
4      -443 -471  -19 -870 -22884.0
...     ...  ...  ...  ...      ...
499995 -494   21 -710 -215  -4013.0
499996 -379  237  495 -381   9217.0
499997  496  632  132  976  -3488.0
499998  -51 -114  279 -337  -1275.0
499999   78 -326  701  198      NaN

[500000 rows x 5 columns]

=== For all of the next examples, we must first prepare the dataframe by adding
columns with previous and next values: A_(i-2), A_(i-1), and A_(i+1). ===
dt_sec[adding_shifted_data] = 0.014089 sec

=== Technique 5: raw Python `for` loop using regular df indexing and the pre-shifted rows ===
len(val) = 500000
dt_sec[5_MOD_raw_for_loop_using_regular_df_indexing_and_the_preshifted_rows] = 8.548541 sec
df_dict[5_MOD_raw_for_loop_using_regular_df_indexing_and_the_preshifted_rows]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[500000 rows x 8 columns]

=== Technique 6: raw Python `for` loop using `df.loc[]` label-based indexing and the pre-shifted rows ===
len(val) = 500000
dt_sec[6_MOD_raw_for_loop_using_df.loc[]_indexing_and_the_preshifted_rows] = 13.844656 sec
df_dict[6_MOD_raw_for_loop_using_df.loc[]_indexing_and_the_preshifted_rows]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[500000 rows x 8 columns]

=== Technique 7: raw Python `for` loop using `df.iloc[]` index-based indexing and the pre-shifted rows ===
len(val) = 500000
dt_sec[7_MOD_raw_for_loop_using_df.iloc[]_indexing_and_the_preshifted_rows] = 34.186218 sec
df_dict[7_MOD_raw_for_loop_using_df.iloc[]_indexing_and_the_preshifted_rows]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[500000 rows x 8 columns]

=== Technique 8 [BAD-**NEVER** USE!]: use `iterrows()` in a Python `for` loop, and the pre-shifted rows ===
len(val) = 500000
dt_sec[8_MOD_iterrows_in_for_loop_and_the_preshifted_rows] = 10.847548 sec
df_dict[8_MOD_iterrows_in_for_loop_and_the_preshifted_rows]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[500000 rows x 8 columns]

=== Technique 9: named `itertuples()` in a Python `for` loop ===
len(val) = 500000
dt_sec[9_itertuples_in_for_loop] = 0.383379 sec
df_dict[9_itertuples_in_for_loop]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[500000 rows x 8 columns]

=== Technique 10: vectorization, w/`apply()` for if statement corner-case ===
len(val) = 500000
dt_sec[10_vectorization__with_apply_for_if_statement_corner_case] = 0.065442 sec
df_dict[10_vectorization__with_apply_for_if_statement_corner_case]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1    B_new      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -57300.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -37020.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -28260.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0    126.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   1422.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0   3792.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -6840.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN

[500000 rows x 9 columns]

=== Technique 11: vectorization, w/list comprehension for if statement corner-case ===
len(val) = 500000
dt_sec[11_vectorization__with_list_comprehension_for_if_statment_corner_case] = 0.079371 sec
df_dict[11_vectorization__with_list_comprehension_for_if_statment_corner_case]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1    B_new      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -57300.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -37020.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -28260.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0    126.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   1422.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0   3792.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -6840.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN

[500000 rows x 9 columns]

=== Technique 12: pure vectorization: w/`df.loc[]` boolean array indexing for if statement corner-case ===
len(val) = 500000
dt_sec[12_pure_vectorization__with_df.loc[]_boolean_array_indexing_for_if_statment_corner_case] = 0.028573 sec
df_dict[12_pure_vectorization__with_df.loc[]_boolean_array_indexing_for_if_statment_corner_case]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1    B_new      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -57300.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -37020.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -28260.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0    126.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   1422.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0   3792.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -6840.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN      NaN

[500000 rows x 9 columns]

=== Technique 13: using the `apply()` function with a lambda ===
len(val) = 500000
dt_sec[13_apply_function_with_lambda] = 4.713148 sec
df_dict[13_apply_function_with_lambda]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[500000 rows x 8 columns]

=== Technique 14 [EASIEST/VERY GOOD]: using a list comprehension with `zip()` and direct variable assignment passed to func ===
len(val) = 500000
dt_sec[14_list_comprehension_w_zip_and_direct_variable_assignment_passed_to_func] = 0.256655 sec
df_dict[14_list_comprehension_w_zip_and_direct_variable_assignment_passed_to_func]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[500000 rows x 8 columns]

=== Technique 15 [EASIEST/VERY GOOD]: using a list comprehension with `zip()` and direct variable assignment calculated in place ===
len(val) = 500000
dt_sec[15_list_comprehension_w_zip_and_direct_variable_assignment_calculated_in_place] = 0.227246 sec
df_dict[15_list_comprehension_w_zip_and_direct_variable_assignment_calculated_in_place]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[500000 rows x 8 columns]

=== Technique 16: using a list comprehension with `zip()` and `row` tuple passed to func ===
len(val) = 500000
dt_sec[16_list_comprehension_w_zip_and_row_tuple_passed_to_func] = 0.270629 sec
df_dict[16_list_comprehension_w_zip_and_row_tuple_passed_to_func]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[500000 rows x 8 columns]

=== Technique 17: using a list comprehension with `.to_numpy()` and direct variable assignment passed to func ===
len(val) = 500000
dt_sec[17_list_comprehension_w__to_numpy__and_direct_variable_assignment_passed_to_func] = 0.632865 sec
df_dict[17_list_comprehension_w__to_numpy__and_direct_variable_assignment_passed_to_func]:
------
            A      B      C      D  A_i_minus_2  A_i_minus_1  A_i_plus_1      val
0         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
1         NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN
2      -218.0 -955.0  661.0   82.0       -951.0       -226.0      -646.0 -60011.0
3      -646.0 -617.0 -652.0  625.0       -226.0       -218.0      -443.0 -52489.0
4      -443.0 -471.0  -19.0 -870.0       -218.0       -646.0       539.0 -22884.0
...       ...    ...    ...    ...          ...          ...         ...      ...
499995 -494.0   21.0 -710.0 -215.0        141.0        900.0      -379.0  -4013.0
499996 -379.0  237.0  495.0 -381.0        900.0       -494.0       496.0   9217.0
499997  496.0  632.0  132.0  976.0       -494.0       -379.0       -51.0  -3488.0
499998  -51.0 -114.0  279.0 -337.0       -379.0        496.0        78.0  -1275.0
499999    NaN    NaN    NaN    NaN          NaN          NaN         NaN      NaN

[500000 rows x 8 columns]

Checking stats for technique "1_raw_for_loop_using_regular_df_indexing"
Checking stats for technique "2_raw_for_loop_using_df.loc[]_indexing"
Checking stats for technique "3_raw_for_loop_using_df.iloc[]_indexing"
Checking stats for technique "4_iterrows_in_for_loop"
Checking stats for technique "5_MOD_raw_for_loop_using_regular_df_indexing_and_the_preshifted_rows"
Checking stats for technique "6_MOD_raw_for_loop_using_df.loc[]_indexing_and_the_preshifted_rows"
Checking stats for technique "7_MOD_raw_for_loop_using_df.iloc[]_indexing_and_the_preshifted_rows"
Checking stats for technique "8_MOD_iterrows_in_for_loop_and_the_preshifted_rows"
Checking stats for technique "9_itertuples_in_for_loop"
Checking stats for technique "10_vectorization__with_apply_for_if_statement_corner_case"
Checking stats for technique "11_vectorization__with_list_comprehension_for_if_statment_corner_case"
Checking stats for technique "12_pure_vectorization__with_df.loc[]_boolean_array_indexing_for_if_statment_corner_case"
Checking stats for technique "13_apply_function_with_lambda"
Checking stats for technique "14_list_comprehension_w_zip_and_direct_variable_assignment_passed_to_func"
Checking stats for technique "15_list_comprehension_w_zip_and_direct_variable_assignment_calculated_in_place"
Checking stats for technique "16_list_comprehension_w_zip_and_row_tuple_passed_to_func"
Checking stats for technique "17_list_comprehension_w__to_numpy__and_direct_variable_assignment_passed_to_func"
Tests passed: the results of all techniques are equal!

df_first =
          A    B    C    D      val
0      -951 -955  -70 -428      NaN
1      -226 -574 -389  602      NaN
2      -218 -955  661   82 -60011.0
3      -646 -617 -652  625 -52489.0
4      -443 -471  -19 -870 -22884.0
...     ...  ...  ...  ...      ...
499995 -494   21 -710 -215  -4013.0
499996 -379  237  495 -381   9217.0
499997  496  632  132  976  -3488.0
499998  -51 -114  279 -337  -1275.0
499999   78 -326  701  198      NaN

[500000 rows x 5 columns]


Summary statistics:
count    499997.000000
mean     -13545.405784
std       21931.985807
min      -83241.000000
25%      -30120.000000
50%       -6277.000000
75%        3529.000000
max       30617.000000
Name: val, dtype: float64

results_df =
    index                                             Method   Time_sec                                 Method_short_names  text_x     text_y  time_multiplier             text_label
0       2            3_raw_for_loop_using_df.iloc[]_indexing  35.398073    3_raw_\nfor_loop_\nusing_\ndf.iloc[]_\nindexing       0  37.167977      1238.855095  35.3981 sec\n1238.86x
1       6  7_MOD_raw_for_loop_using_df.iloc[]_indexing_an...  34.186218  7_MOD_\nraw_for_\nloop_\nusing_\ndf.iloc[]_\ni...       1  35.956122      1196.442839  34.1862 sec\n1196.44x
2       3                             4_iterrows_in_for_loop  14.720045                         4_iterrows_\nin_for_\nloop       2  16.489949       515.169378   14.7200 sec\n515.17x
3       1             2_raw_for_loop_using_df.loc[]_indexing  14.355397     2_raw_\nfor_loop_\nusing_\ndf.loc[]_\nindexing       3  16.125301       502.407482   14.3554 sec\n502.41x
4       5  6_MOD_raw_for_loop_using_df.loc[]_indexing_and...  13.844656  6_MOD_\nraw_for_\nloop_\nusing_\ndf.loc[]_\nin...       4  15.614560       484.532662   13.8447 sec\n484.53x
5       7  8_MOD_iterrows_in_for_loop_and_the_preshifted_...  10.847548  8_MOD_\niterrows_\nin_for_\nloop_\nand_the_\np...       5  12.617452       379.640452   10.8475 sec\n379.64x
6       0           1_raw_for_loop_using_regular_df_indexing   8.824408  1_raw_\nfor_loop_\nusing_\nregular_\ndf_indexi...       6  10.594311       308.834961    8.8244 sec\n308.83x
7       4  5_MOD_raw_for_loop_using_regular_df_indexing_a...   8.548541  5_MOD_\nraw_for_\nloop_\nusing_\nregular_\ndf_...       7  10.318445       299.180226    8.5485 sec\n299.18x
8      12                      13_apply_function_with_lambda   4.713148                13_apply_\nfunction_\nwith_\nlambda       8   6.483051       164.949854    4.7131 sec\n164.95x
9      16  17_list_comprehension_w__to_numpy__and_direct_...   0.632865  17_list_\ncomprehen\nsion_\nw__to_\nnumpy_\n_a...       9   2.402768        22.148880     0.6329 sec\n22.15x
10      8                           9_itertuples_in_for_loop   0.383379                       9_itertuples_\nin_for_\nloop      10   2.153283        13.417434     0.3834 sec\n13.42x
11     15  16_list_comprehension_w_zip_and_row_tuple_pass...   0.270629  16_list_\ncomprehen\nsion_\nw_zip_\nand_row_\n...      11   2.040533         9.471429      0.2706 sec\n9.47x
12     13  14_list_comprehension_w_zip_and_direct_variabl...   0.256655  14_list_\ncomprehen\nsion_\nw_zip_\nand_direct...      12   2.026558         8.982354      0.2567 sec\n8.98x
13     14  15_list_comprehension_w_zip_and_direct_variabl...   0.227246  15_list_\ncomprehen\nsion_\nw_zip_\nand_direct...      13   1.997150         7.953119      0.2272 sec\n7.95x
14     10  11_vectorization__with_list_comprehension_for_...   0.079371  11_vector\nization_\n_with_\nlist_\ncomprehen\...      14   1.849274         2.777803      0.0794 sec\n2.78x
15      9  10_vectorization__with_apply_for_if_statement_...   0.065442  10_vector\nization_\n_with_\napply_\nfor_if_\n...      15   1.835346         2.290328      0.0654 sec\n2.29x
16     11  12_pure_vectorization__with_df.loc[]_boolean_a...   0.028573  12_pure_\nvectoriza\ntion_\n_with_\ndf.loc[]_\...      16   1.798477         1.000000      0.0286 sec\n1.00x

"""
