<!--
GS
File created: 25 Sept. 2023
Adding content: Oct. 2023

Add an answer here: https://stackoverflow.com/q/16476924/4561887
-->


## How to iterate over Pandas `DataFrame`s without iterating

After _several weeks_ of working on this answer, here's what I've come up with: 

Here are **13 techniques for iterating over Pandas `DataFrame`s**. As you can see, the time it takes varies *dramatically*. The fastest technique is **\~1363x** faster than the slowest technique! The key takeaway, [as @cs95 says here](https://stackoverflow.com/a/55557758/4561887), is **_don't_ iterate! Use vectorization instead.** All this really means is that you should use the arrays directly in mathematical formulas rather than trying to manually iterate over the arrays. There are many ways to do this, which you can see in the plot and in my example code below. When using the arrays directly, the underlying looping still takes place, but in (I think) very optimized underlying C code rather than through raw Python.


## Results

13 techniques, numbered 1 to 13, were tested. The technique number and name is underneath each bar. The total calculation time is above each bar. Underneath that is the multiplier to show how much longer it took than the fastest technique to the far right:

[![enter image description here][1]][1]

Results table, ordered from longest to shortest time (worst to best). Ie: the best technique is the *last row* in this table:
```
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
```


## Summary

Use **list comprehension** (good) and **vectorization** (best). Pure vectorization I think is _always_ possible, but may take extra work in complicated calculations. 

#### Here are the 13 techniques, listed in order of *fastest first to slowest last*. I recommend _never_ using the last (slowest) 3 to 4 techniques:
1. `8_pure_vectorization__with_df.loc[]_boolean_array_indexing_for_if_statment_corner_case`
1. `6_vectorization__with_apply_for_if_statement_corner_case`
1. `7_vectorization__with_list_comprehension_for_if_statment_corner_case`
1. `11_list_comprehension_w_zip_and_direct_variable_assignment_calculated_in_place`
1. `10_list_comprehension_w_zip_and_direct_variable_assignment_passed_to_func`
1. `12_list_comprehension_w_zip_and_row_tuple_passed_to_func`
1. `5_itertuples_in_for_loop`
1. `13_list_comprehension_w__to_numpy__and_direct_variable_assignment_passed_to_func`
1. `9_apply_function_with_lambda`
1. `1_raw_for_loop_using_regular_df_indexing`
1. `2_raw_for_loop_using_df.loc[]_indexing`
1. `4_iterrows_in_for_loop`
1. `3_raw_for_loop_using_df.iloc[]_indexing`

#### Rules of thumb: 
1. Techniques 3, 4, and 2 should _never_ be used. They are super slow and have no advantages whatsoever.
    1. `3_raw_for_loop_using_df.iloc[]_indexing`
    1. `4_iterrows_in_for_loop`
    1. `2_raw_for_loop_using_df.loc[]_indexing`
1. Technique `1_raw_for_loop_using_regular_df_indexing` should never be used either, but if you're going to use a raw for loop, it's faster than the others.
1. The **`.apply()`** function (`9_apply_function_with_lambda`) is ok, but generally speaking, I'd avoid it too. Technique `6_vectorization__with_apply_for_if_statement_corner_case` did perform better than `7_vectorization__with_list_comprehension_for_if_statment_corner_case`, however, which is interesting.
1. **List comprehension** is great! It's not the fastest, but it is easy to use and very fast! 
    1. The nice thing about it is that it can be used with *any* function that is intended to work on individual values, or array values. And this means you could have really complicated `if` statements and things inside the function. So, the tradeoff here is that it gives you great versatility with really readable and re-usable code by using external calculation functions, while still giving you great speed!
1. **Vectorization** is the fastest and best, and what you should use whenever the equation is simple. You can optionally use something like `.apply()` or **list comprehension** on just the more-complicated portions of the equation, while still easily using vectorization for the rest.
1. **Pure vectorization** is the absolute fastest and best, and what you should use if you _are willing to put in the effort to make it work._ 
    1. For simple cases, it's what you should use. 
    1. For complicated cases, `if` statements, etc., pure vectorization can be made to work too, through **boolean indexing,** but can add extra work and can decrease readability to do so. So, you can optionally use **list comprehension** or **.apply()** for just those edge cases instead, while still using vectorization for the rest of the calculation. Ex: see techniques `7_vectorization__with_list_comprehension_for_if_statment_corner_case` and `6_vectorization__with_apply_for_if_statement_corner_case`.


## The test data

Assume we have the following Pandas DataFrame. It has 2 million rows with 4 columns (`A`, `B`, `C`, and `D`), each with random values from `-1000` to `1000`:

```
df =
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
```

I produced this DataFrame like this:
```py
import numpy as np
import pandas as pd

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
print(f"df = \n{df_original}")
```


## The test equation/calculation

I wanted to demonstrate that all of these techniques are possible on non-trivial functions or equations, so I intentionally made the equation they are calculating require:

1. `if` statements
1. data from multiple columns in the DataFrame
1. data from multiple rows in the DataFrame

The equation we will be calculating for each row is this. I arbitrarily made it up, but I think it contains enough complexity that you will be able to expand on what I've done to perform any equation you want in Pandas with full vectorization:

[![enter image description here][2]][2]

<!-- 
LaTeX format generated by Bing Chat AI (see the references): 

<math xmlns="http://www.w3.org/1998/Math/MathML" display="block"><semantics><mtable rowspacing="0.25em" columnalign="right left" columnspacing="0em"><mtr><mtd><mstyle scriptlevel="0" displaystyle="true"><mrow><mi>v</mi><mi>a</mi><mi>l</mi></mrow></mstyle></mtd><mtd><mstyle scriptlevel="0" displaystyle="true"><mrow><mrow></mrow><mo>=</mo><mn>2</mn><msub><mi>A</mi><mrow><mi>i</mi><mo>−</mo><mn>2</mn></mrow></msub><mo>+</mo><mn>3</mn><msub><mi>A</mi><mrow><mi>i</mi><mo>−</mo><mn>1</mn></mrow></msub><mo>+</mo><mn>4</mn><mi>A</mi><mo>+</mo><mn>5</mn><msub><mi>A</mi><mrow><mi>i</mi><mo>+</mo><mn>1</mn></mrow></msub><mo>+</mo><mrow><mo fence="true">{</mo><mtable rowspacing="0.16em" columnalign="left left" columnspacing="1em"><mtr><mtd><mstyle scriptlevel="0" displaystyle="false"><mrow><mn>6</mn><mi>B</mi></mrow></mstyle></mtd><mtd><mstyle scriptlevel="0" displaystyle="false"><mrow><mtext>if&nbsp;</mtext><mi>B</mi><mo>&gt;</mo><mn>0</mn></mrow></mstyle></mtd></mtr><mtr><mtd><mstyle scriptlevel="0" displaystyle="false"><mrow><mn>60</mn><mi>B</mi></mrow></mstyle></mtd><mtd><mstyle scriptlevel="0" displaystyle="false"><mtext>otherwise</mtext></mstyle></mtd></mtr></mtable><mo fence="true">}</mo></mrow><mo>+</mo><mn>7</mn><mi>C</mi><mo>−</mo><mn>8</mn><mi>D</mi></mrow></mstyle></mtd></mtr></mtable><annotation encoding="application/x-tex">\begin{aligned}
val &amp;= 2A_{i-2} + 3A_{i-1} + 4A + 5A_{i+1} + \left\{\begin{array}{ll}
6B &amp; \text{if } B &gt; 0 \\
60B &amp; \text{otherwise}
\end{array}\right\} + 7C - 8D
\end{aligned}
</annotation></semantics></math>

-->

In Python, the above equation can be written like this:
```py
# Calculate and return a new value, `val`, by performing the following equation:
val = (
    2 * A_i_minus_2
    + 3 * A_i_minus_1
    + 4 * A
    + 5 * A_i_plus_1
    # Python ternary operator; don't forget parentheses around the entire 
    # ternary expression!
    + ((6 * B) if B > 0 else (60 * B))
    + 7 * C
    - 8 * D
)
```

Alternatively, you could write it like this:
```py
# Calculate and return a new value, `val`, by performing the following equation:

if B > 0:
    B_new = 6 * B
else:
    B_new = 60 * B

val = (
    2 * A_i_minus_2
    + 3 * A_i_minus_1
    + 4 * A
    + 5 * A_i_plus_1
    + B_new
    + 7 * C
    - 8 * D
)
```

Either of those can be wrapped into a function. Ex: 
```py
def calculate_val(
        A_i_minus_2,
        A_i_minus_1,
        A,
        A_i_plus_1,
        B,
        C,
        D):
    val = (
        2 * A_i_minus_2
        + 3 * A_i_minus_1
        + 4 * A
        + 5 * A_i_plus_1
        # Python ternary operator; don't forget parentheses around the 
        # entire ternary expression!
        + ((6 * B) if B > 0 else (60 * B))
        + 7 * C
        - 8 * D
    )
    return val
```


## The techniques

The full code is available to download and run in my **[`python/pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py`](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/python/pandas_dataframe_iteration_vs_vectorization_vs_list_comprehension_speed_tests.py)** file in my [eRCaGuy_hello_world](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world) repo.

#### Here is the code for all 13 techniques:

1. `1_raw_for_loop_using_regular_df_indexing`

    ```py
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
    ```

1. `2_raw_for_loop_using_df.loc[]_indexing`

    ```py
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
    ```

1. `3_raw_for_loop_using_df.iloc[]_indexing`

    ```py
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
    ```

1. `4_iterrows_in_for_loop`

    ```py
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
    ```

For all of the next examples, we must first prepare the dataframe by adding columns with previous and next values: `A_(i-2)`, `A_(i-1)`, and `A_(i+1)`. These columns in the DataFrame will be named `A_i_minus_2`, `A_i_minus_1`, and `A_i_plus_1`, respectively:

```py
df_original["A_i_minus_2"] = df_original["A"].shift(2)  # val at index i-2
df_original["A_i_minus_1"] = df_original["A"].shift(1)  # val at index i-1
df_original["A_i_plus_1"] = df_original["A"].shift(-1)  # val at index i+1

# Note: to ensure that no partial calculations are ever done with rows which
# have NaN values due to the shifting, we can either drop such rows with
# `.dropna()`, or set all values in these rows to NaN. I'll choose the latter
# so that the stats that will be generated with the techniques below will end
# up matching the stats which were produced by the prior techniques above. ie:
# the number of rows will be identical to before. 
#
# df_original = df_original.dropna()
df_original.iloc[:2, :] = np.NAN   # slicing operators: first two rows, 
                                   # all columns
df_original.iloc[-1:, :] = np.NAN  # slicing operators: last row, all columns
```

Running the vectorized code just above to produce those 3 new columns took a total of **0.044961 seconds**.

Now on to the rest of the techniques:

1. `5_itertuples_in_for_loop`

    ```py
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
    ```

1. `6_vectorization__with_apply_for_if_statement_corner_case`

    ```py
    def calculate_new_column_b_value(b_value):
        # Python ternary operator
        b_value_new = (6 * b_value) if b_value > 0 else (60 * b_value)  
        return b_value_new

    # In this particular example, since we have an embedded `if-else` statement
    # for the `B` column, pure vectorization is less intuitive. So, first we'll
    # calculate a new `B` column using
    # **`apply()`**, then we'll use vectorization for the rest.
    df["B_new"] = df["B"].apply(calculate_new_column_b_value)
    # OR (same thing, but with a lambda function instead)
    # df["B_new"] = df["B"].apply(lambda x: (6 * x) if x > 0 else (60 * x))

    # Now we can use vectorization for the rest. "Vectorization" in this case
    # means to simply use the column series variables in equations directly,
    # without manually iterating over them. Pandas DataFrames will handle the
    # underlying iteration automatically for you. You just focus on the math.
    df["val"] = (
        2 * df["A_i_minus_2"]
        + 3 * df["A_i_minus_1"]
        + 4 * df["A"]
        + 5 * df["A_i_plus_1"]
        + df["B_new"]
        + 7 * df["C"]
        - 8 * df["D"]
    )
    ```

1. `7_vectorization__with_list_comprehension_for_if_statment_corner_case`

    ```py
    # In this particular example, since we have an embedded `if-else` statement
    # for the `B` column, pure vectorization is less intuitive. So, first we'll
    # calculate a new `B` column using **list comprehension**, then we'll use
    # vectorization for the rest.
    df["B_new"] = [
        calculate_new_column_b_value(b_value) for b_value in df["B"]
    ]

    # Now we can use vectorization for the rest. "Vectorization" in this case
    # means to simply use the column series variables in equations directly,
    # without manually iterating over them. Pandas DataFrames will handle the
    # underlying iteration automatically for you. You just focus on the math.
    df["val"] = (
        2 * df["A_i_minus_2"]
        + 3 * df["A_i_minus_1"]
        + 4 * df["A"]
        + 5 * df["A_i_plus_1"]
        + df["B_new"]
        + 7 * df["C"]
        - 8 * df["D"]
    )
    ```

1. `8_pure_vectorization__with_df.loc[]_boolean_array_indexing_for_if_statment_corner_case`

    ```py
    # If statement to evaluate:
    #
    #     if B > 0:
    #         B_new = 6 * B
    #     else:
    #         B_new = 60 * B
    #
    # In this particular example, since we have an embedded `if-else` statement
    # for the `B` column, we can use some boolean array indexing through
    # `df.loc[]` for some pure vectorization magic.
    #
    # Explanation:
    #
    # Long:
    #
    # The format is: `df.loc[rows, columns]`, except in this case, the rows are
    # specified by a "boolean array" (AKA: a boolean expression, list of
    # booleans, or "boolean mask"), specifying all rows where `B` is > 0. Then,
    # only in that `B` column for those rows, set the value accordingly. After
    # we do this for where `B` is > 0, we do the same thing for where `B` 
    # is <= 0, except with the other equation.
    #
    # Short:
    #
    # For all rows where the boolean expression applies, set the column value
    # accordingly.
    #
    # GitHub CoPilot first showed me this `.loc[]` technique.
    # See also the official documentation:
    # https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.loc.html
    #
    # ===========================
    # 1st: handle the > 0 case
    # ===========================
    df["B_new"] = df.loc[df["B"] > 0, "B"] * 6
    #
    # ===========================
    # 2nd: handle the <= 0 case, merging the results into the
    # previously-created "B_new" column
    # ===========================
    # - NB: this does NOT work; it overwrites and replaces the whole "B_new"
    #   column instead:
    #
    #       df["B_new"] = df.loc[df["B"] <= 0, "B"] * 60
    #
    # This works:
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
    ```

1. `9_apply_function_with_lambda`

    ```py
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
        axis='columns' # same as `axis=1`: "apply function to each row", 
                       # rather than to each column
    )
    ```

1. `10_list_comprehension_w_zip_and_direct_variable_assignment_passed_to_func`

    ```py
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
    ```

1. `11_list_comprehension_w_zip_and_direct_variable_assignment_calculated_in_place`

    ```py
    df["val"] = [
        2 * A_i_minus_2
        + 3 * A_i_minus_1
        + 4 * A
        + 5 * A_i_plus_1
        # Python ternary operator; don't forget parentheses around the entire
        # ternary expression!
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
    ```

1. `12_list_comprehension_w_zip_and_row_tuple_passed_to_func`

    ```py
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
    ```

1. `13_list_comprehension_w__to_numpy__and_direct_variable_assignment_passed_to_func`

    ```py
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
            # Note: this `[[...]]` double-bracket indexing is used to select a
            # subset of columns from the dataframe. The inner `[]` brackets
            # create a list from the column names within them, and the outer 
            # `[]` brackets accept this list to index into the dataframe and
            # select just this list of columns, in that order.
            # - See the official documentation on it here:
            #   https://pandas.pydata.org/docs/user_guide/indexing.html#basics
            #   - Search for the phrase "You can pass a list of columns to [] to
            #     select columns in that order."
            #   - I learned this from this comment here:
            #     https://stackoverflow.com/questions/16476924/how-to-iterate-over-rows-in-a-dataframe-in-pandas/55557758#comment136020567_55557758
            # - One of the **list comprehension** examples in this answer here
            #   uses `.to_numpy()` like this:
            #   https://stackoverflow.com/a/55557758/4561887
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
    ```


## More on `.iterrtuples()`

There are actually more nuances when using `.itertuples()`. To delve into some of those, read [this answer by @Romain Capron](https://stackoverflow.com/a/59413206/4561887). Here is a bar chart plot I made of his results:

[![enter image description here][3]][3]

My plotting code for his results is in **[`python/pandas_plot_bar_chart_better_GREAT_AUTOLABEL_DATA.py`](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/python/pandas_plot_bar_chart_better_GREAT_AUTOLABEL_DATA.py)** in my [eRCaGuy_hello_world](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world) repo.


## Future work

Using Cython (Python compiled into C code), or just raw C functions called by Python, could be faster potentially, but I'm not going to do that for these tests. I'd only look into and speed test those options for big optimizations.

I currently don't know Cython and don't feel the need to learn it. As you can see above, simply using list pure vectorization properly already runs incredibly fast, processing 2 *million* rows in only 0.1 seconds, or 20 million rows per second. 


## References

1. A bunch of the official Pandas documentation, especially the `DataFrame` documentation here: https://pandas.pydata.org/pandas-docs/stable/reference/frame.html. 
1. [This excellent answer by @cs95](https://stackoverflow.com/a/55557758/4561887) - this is where I learned in particular how to use list comprehension to iterate over a DataFrame. 
1. [This answer about `itertuples()`, by @Romain Capron](https://stackoverflow.com/a/59413206/4561887) - I studied it carefully and edited/formatted it.
1. All of this is my own code, but I want to point out that I had dozens of chats with GitHub Copilot (mostly), Bing AI, and ChatGPT in order to figure out many of these techniques and debug my code as I went. 
1. Bing Chat produced the pretty LaTeX equation for me, with the following prompt. Of course, I verified the output: 

    > Convert this Python code to a pretty equation I can paste onto Stack Overflow:
    > ```
    >     val = (
    >         2 * A_i_minus_2
    >         + 3 * A_i_minus_1
    >         + 4 * A
    >         + 5 * A_i_plus_1
    >         # Python ternary operator; don't forget parentheses around the entire ternary expression!
    >         + ((6 * B) if B > 0 else (60 * B))
    >         + 7 * C
    >         - 8 * D
    >     )
    > ```



  [1]: https://i.stack.imgur.com/5biMy.png
  [2]: https://i.stack.imgur.com/W3c12.png
  [3]: https://i.stack.imgur.com/ws9db.png
