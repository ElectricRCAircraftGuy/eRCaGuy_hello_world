#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 13 Oct. 2023
#
# Let's speed test the `test` command (`[`) vs the `[[` bash builtin.
# ie: `[]` vs `[[]]` speed tests.
# See my answer: https://stackoverflow.com/a/77291070/4561887
#
# STATUS: done and works!

# keywords to easily grep or ripgrep in this repo for this program and what it teaches
#
# KEYWORDS: python in bash program python called from bash heredoc plotting
# in python bash; python program embedded in bash; python program in bash
# python program in bash heredoc

# Check this script with:
#
##      shellcheck bash/speed_tests__comparison_with_test_cmd_vs_double_square_bracket_bash_builtin.sh
#
# Run command:
#
#       bash/speed_tests__comparison_with_test_cmd_vs_double_square_bracket_bash_builtin.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/speed_tests__comparison_with_test_cmd_vs_double_square_bracket_bash_builtin.sh

# References:
# 1. My answer: https://stackoverflow.com/a/77291070/4561887
# 1.


# ==============================================================================
# Python plotting program
# - is a Bash heredoc
# References:
# 1. My `plot_data()` function here:
#    https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/python/pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py
# 1. See my answer here: https://stackoverflow.com/a/77270285/4561887
# ==============================================================================
python_plotting_program=$(cat <<'PROGRAM_END'

# 3rd-party imports
import matplotlib.pyplot as plt
import pandas as pd

# standard imports
import sys

assert sys.argv[0] == "-c"
# print(f"sys.argv = {sys.argv}")  # debugging

# Get the command-line arguments
num_iterations = int(sys.argv[1])
single_bracket_sec = float(sys.argv[2])
double_bracket_sec = float(sys.argv[3])

# place into lists
labels = ['`[ ]` `test` func', '`[[ ]]` Bash built-in']
data = [single_bracket_sec, double_bracket_sec]

# place into a Pandas dataframe for easy manipulation and plotting
df = pd.DataFrame({'test_type': labels, 'time_sec': data})
df = df.sort_values(by="time_sec", axis='rows', ascending=False)
df = df.reset_index(drop=True)

# plot the data
fig = plt.figure()
plt.bar(labels, data)
plt.title(f"Speed Test: `[ ]` vs `[[ ]]` over {num_iterations:,} iterations")
plt.xlabel('Test Type', labelpad=8)  # use `labelpad` to lower the label
plt.ylabel('Time (sec)')

# Prepare to add text labels to each bar
df["text_x"] = df.index # use the indices as the x-positions
df["text_y"] = df["time_sec"] + 0.06*df["time_sec"].max()
df["time_multiplier"] = df["time_sec"] / df["time_sec"].min()
df["text_label"] = (df["time_sec"].map("{:.4f} sec\n".format) +
                    df["time_multiplier"].map("{:.2f}x".format))

# Use a list comprehension to actually call `plt.text()` to **automatically add
# a plot label** for each row in the dataframe
[
    plt.text(
        text_x,
        text_y,
        text_label,
        horizontalalignment='center',
        verticalalignment='center'
    ) for text_x, text_y, text_label
    in zip(
        df["text_x"],
        df["text_y"],
        df["text_label"]
    )
]

# add 10% to the top of the y-axis to leave space for labels
ymin, ymax = plt.ylim()
plt.ylim(ymin, ymax*1.1)

plt.show()

PROGRAM_END
)

# ==============================================================================
# Bash speed test program
# ==============================================================================

# NUM_ITERATIONS="1000000" # 1 million
NUM_ITERATIONS="10000" # 10k

word1="true"
word2="false"

# Get an absolute timestamp in floating point seconds.
# From:
# https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/timestamp_lib_WIP.sh
seconds_float() {
    time_sec="$(date +"%s.%N")"
    echo "$time_sec"
}

single_bracket() {
    for i in $(seq 1 "$NUM_ITERATIONS"); do
        if [ "$word1" = "$word2" ]; then
            echo "true"
        fi
    done
}

double_bracket() {
    for i in $(seq 1 "$NUM_ITERATIONS"); do
        if [[ "$word1" == "$word2" ]]; then
            echo "true"
        fi
    done
}

run_and_time_function() {
    # the 1st arg is the function to run
    func_to_time="$1"

    # NB: the "information" type prints will go to stderr so they don't
    # interfere with the actual timing results printed to stdout.

    echo -e "== $func_to_time time test start... ==" >&2  # to stderr
    time_start="$(seconds_float)"

    $func_to_time

    time_end="$(seconds_float)"
    elapsed_time="$(bc <<< "scale=20; $time_end - $time_start")"
    echo "== $func_to_time time test end. ==" >&2  # to stderr
    echo "$elapsed_time"  # to stdout
}

main() {
    echo "Running speed tests over $NUM_ITERATIONS iterations."

    single_bracket_time_sec="$(run_and_time_function "single_bracket")"
    double_bracket_time_sec="$(run_and_time_function "double_bracket")"

    echo "single_bracket_time_sec = $single_bracket_time_sec"
    echo "double_bracket_time_sec = $double_bracket_time_sec"

    # echo "Plotting the results in Python..."
    python3 -c "$python_plotting_program" "$NUM_ITERATIONS" \
        "$single_bracket_time_sec" "$double_bracket_time_sec"
}

# Determine if the script is being sourced or executed (run).
# See:
# 1. "eRCaGuy_hello_world/bash/if__name__==__main___check_if_sourced_or_executed_best.sh"
# 1. My answer: https://stackoverflow.com/a/70662116/4561887
if [ "${BASH_SOURCE[0]}" = "$0" ]; then
    # This script is being run.
    __name__="__main__"
else
    # This script is being sourced.
    __name__="__source__"
fi

# Only run `main` if this script is being **run**, NOT sourced (imported).
# - See my answer: https://stackoverflow.com/a/70662116/4561887
if [ "$__name__" = "__main__" ]; then
    main "$@"
fi


# ==============================================================================
# SAMPLE OUTPUT:
# ==============================================================================
#
# 1) WHEN RUN
#
#       eRCaGuy_hello_world$ bash/speed_tests__comparison_with_test_cmd_vs_double_square_bracket_bash_builtin.sh
#       Running speed tests.
#
#       single_bracket() start...
#       single_bracket() done.
#
#       real	0m2.334s
#       user	0m2.291s
#       sys	0m0.055s
#       =====================
#
#       double_bracket() start...
#       double_bracket() done.
#
#       real	0m1.604s
#       user	0m1.597s
#       sys	0m0.020s
#
#
#
# 2) WHEN SOURCED (no output, but it brings in all functions herein so you can use them!)
#
#       eRCaGuy_hello_world$ . bash/speed_tests__comparison_with_test_cmd_vs_double_square_bracket_bash_builtin.sh
