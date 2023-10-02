#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Oct. 2023

Assuming you have two Pandas DataFrames of different lengths, interpolate the shorter one to
match the length of the longer one, so that you can do math on them, such as taking the difference
between them, etc.

Status: done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint pandas_dataframe_interpolation_via_scipy_interpolate.py
```

Run command:
```bash
./pandas_dataframe_interpolation_via_scipy_interpolate.py
# OR
python3 pandas_dataframe_interpolation_via_scipy_interpolate.py
```

References:
1. GitHub Copilot
1. https://docs.scipy.org/doc/scipy/reference/generated/scipy.interpolate.interp1d.html#scipy.interpolate.interp1d
1. https://numpy.org/doc/stable/reference/generated/numpy.arange.html
1. https://numpy.org/doc/stable/reference/generated/numpy.interp.html
1.


============================
GitHub Copilot conversation:
- EXCELLENT results!
============================

Me:
> I have x and y values in two different dataframes of different lengths. How can I subtract one
y from the other, to get the difference between the two dataframes, interpolating for x and y
values?

Me again later:
> Error: A value in x_new is below the interpolation range.

GitHub Copilot: The error message suggests that one or more of the `x` values in `df1` are outside
the range of `x` values in `df2`. This can happen if the `x` values in `df1` are not a subset of the
`x` values in `df2`. To fix this error, you can either adjust the `x` values in `df1` to be within
the range of `x` values in `df2`, or you can adjust the `x` values in `df2` to be within the range
of `x` values in `df1`. Alternatively, you can use a different interpolation method that allows
extrapolation, such as `kind='linear', fill_value='extrapolate'`. Here's an example code snippet
that demonstrates how to use this method:

```python
import pandas as pd
from scipy.interpolate import interp1d

# assume df1 is the longer dataframe and df2 is the shorter dataframe
df1 = pd.DataFrame({'x': [1, 2, 3, 4, 5], 'y': [2, 4, 6, 8, 10]})
df2 = pd.DataFrame({'x': [1.5, 2.5, 3.5], 'y': [3, 5, 7]})

# interpolate the y values of df2 to the x values of df1
f = interp1d(df2['x'], df2['y'], kind='linear', fill_value='extrapolate')
df2_interpolated = pd.DataFrame({'x': df1['x'], 'y': f(df1['x'])})

# subtract the interpolated y values from the y values of df1
df_diff = pd.DataFrame({'x': df1['x'], 'y': df1['y'] - df2_interpolated['y']})
```

In this example, the `kind` argument is set to `'linear'` and the `fill_value` argument is set to
`'extrapolate'`. This allows the interpolation function to extrapolate beyond the range of `x`
values in `df2`.

== NEW CONVERSATION: how I obtained Method 4 below: ==

Me:
> Write an interpolation example using `np.interp()`.

GitHub Copilot: Sure! Here's an example of how to use `np.interp()` to interpolate a set of `x` and
`y` values to a new set of `x` values:

```python
import numpy as np

# create some example data
x = np.array([1, 2, 3, 4, 5])
y = np.array([2, 4, 6, 8, 10])

# create a new set of x values to interpolate to
x_new = np.array([1.5, 2.5, 3.5])

# interpolate the y values to the new x values
y_new = np.interp(x_new, x, y)

# print the interpolated y values
print(y_new)
```

In this example, `np.interp()` is used to interpolate the `y` values of the `x` and `y` arrays to a
new set of `x` values specified by the `x_new` array. The resulting interpolated `y` values are
stored in the `y_new` array. The output of this example code should be:

```
[3. 5. 7.]
```

This means that the interpolated `y` values for the `x` values `[1.5, 2.5, 3.5]` are `[3, 5, 7]`,
respectively.

Me:
> np.interp() produces erroneous results when extrapolating beyond the input x values.

GitHub Copilot: You're correct. np.interp() can produce erroneous results when extrapolating beyond
the input x values...
[It then told me to use SciPy's `interp1d()` instead, which I already was using
in Method 3, per its previous advice above.]


"""

import numpy as np
import pandas as pd
from scipy.interpolate import interp1d


# =================================
# [GOOD] Super simple, more-manual way to interpolate
# - mostly written by GitHub Copilot
print("==== [GOOD] METHOD 1: manual, using the x-values of the longer dataframe ====\n")
# =================================

# assume df1 is the longer dataframe and df2 is the shorter dataframe
df1 = pd.DataFrame({'x': [1, 2, 3, 4, 5], 'y': [2, 4, 6, 8, 10]})
df2 = pd.DataFrame({'x': [1.5, 2.5, 3.5], 'y': [3, 5, 7]})

# interpolate the y values of df2 (the shorter dataframe) to the x values of df1 (the longer
# dataframe)
f = interp1d(df2['x'], df2['y'], kind='linear', fill_value='extrapolate')
df2_interpolated = pd.DataFrame({'x': df1['x'], 'y': f(df1['x'])})

# subtract the interpolated y values of df2 from the original y values of df1
df_diff = pd.DataFrame({'x': df1['x'], 'y': df1['y'] - df2_interpolated['y']})

# print the results
print(f"df1:\n{df1}\n")
print(f"df2:\n{df2}\n")
print(f"df2_interpolated:\n{df2_interpolated}\n")
print(f"df_diff:\n{df_diff}\n")

# =================================
# [BETTER] Alternative, generic way to do this at the x-values of the longer dataframe
# - By me
print("==== [BETTER] METHOD 2: generic, function-based, using the x-values of the longer dataframe ====\n")
# =================================

def interpolate_df(x1, y1, x2, y2):
    """
    Interpolate dataframes at whatever x values the longer dataframe has.:

    Interpolate the two dataframes to end up with a single set of x values, and two sets of y
    values, with the longer one being original, and the shorter one being interpolated to match the
    length of the longer one.
    """
    if (len(x1) >= len(x2)):
        x_long = x1
        y_long = y1
        x_short = x2
        y_short = y2
    else:
        x_long = x2
        y_long = y2
        x_short = x1
        y_short = y1

    x_from = x_short
    y_from = y_short
    x_to = x_long

    # interpolate the y values of the shorter dataframe to the x values of the longer dataframe
    func = interp1d(x_from, y_from, kind='linear', fill_value='extrapolate')
    y_interpolated = func(x_to)  # the interpolated "to" y_to values

    # Return a new dataframe with the "to" x values, and the two sets of y values
    df_interpolated = pd.DataFrame({
        x_to.name: x_to,        # the longer set of x-values
        y_long.name: y_long,    # the one set of y-values which was already longer
        y_short.name + "_interpolated": y_interpolated,  # the other set of y-values,
                                                         # now interpolated
    })

    # Do some math on the values; ex: calculate the difference between the two sets of y-values
    df_interpolated["y_diff"] = df_interpolated[y_long.name] - df_interpolated[
        y_short.name + "_interpolated"]

    return df_interpolated  # Contains x_long, y_long, y_short_interpolated, and y_diff


df1 = pd.DataFrame({'x1': [1, 2, 3, 4, 5], 'y1': [2, 4, 6, 8, 10]})
df2 = pd.DataFrame({'x2': [1.5, 2.5, 3.5], 'y2': [3, 5, 7]})

df_new_interpolated = interpolate_df(df1['x1'], df1['y1'], df2['x2'], df2['y2'])

print(f"df1:\n{df1}\n")
print(f"df2:\n{df2}\n")
print(f"df_new_interpolated:\n{df_new_interpolated}\n")

# =================================
# [BEST!!!] Alternative, generic way to do this at fixed x-value intervals
# - By me, with CoPilot's assistance
print("==== [BEST] METHOD 3: generic, function-based, at fixed x-value intervals; uses\n"
      "`scipy.interpolate.interp1d()` ====\n")
# =================================

def interpolate_df_at_fixed_x_intervals(x1, y1, x2, y2, x_interval):
    """
    Interpolate dataframes at fixed x intervals.
    """

    x_min = min(x1.min(), x2.min())
    x_max = max(x1.max(), x2.max())

    # Create a new set of x values at fixed intervals
    # - The new x-values are produced as a floating point numpy `arange` array range of values.
    #   See: https://numpy.org/doc/stable/reference/generated/numpy.arange.html
    x_new = np.arange(x_min, x_max + x_interval, x_interval)  # <========= HOW TO CREATE A NEW NUMPY
                                                              # FLOATING POINT RANGE ARRAY (array
                                                              # range)
    x_new = pd.Series(x_new)  # convert to a Pandas Series

    # Create interpolated y values for each set of data at the new x values
    interpolation_func1 = interp1d(x1, y1, kind='linear', fill_value='extrapolate')
    interpolation_func2 = interp1d(x2, y2, kind='linear', fill_value='extrapolate')
    y1_new = interpolation_func1(x_new)
    y2_new = interpolation_func2(x_new)
    y_diff = y1_new - y2_new  # better way than doing it later, below

    # Return a new dataframe with the new x values, and the two sets of y values
    df_interpolated = pd.DataFrame({
        x1.name + "_new": x_new,     # the new set of x-values; arbitrarily use `x1`'s name
        y1.name + "_new": y1_new,    # the new, interpolated y1 values
        y2.name + "_new": y2_new,    # the new, interpolated y2 values
        # Better way than doing this later, below
        "y_diff": y_diff
    })

    # Do some math on the values; ex: calculate the difference between the two sets of y-values
    # - TODO/NB: if you know you need this calculation, it's cleaner to just do it *before* creating
    #   the `df_interpolated` dataframe above. See `interpolate_df_at_fixed_x_intervals_numpy()` in
    #   the method below, and instead just inject `"y_diff"` directly into `df_interpolated`
    #   DataFrame as you create it above.
    #
    # df_interpolated["y_diff"] = (
    #     df_interpolated[y1.name + "_new"] - df_interpolated[y2.name + "_new"])

    return df_interpolated  # Contains x_new, y1_new, y2_new, and y_diff

# NB: NOT ALLOWED!
#       ValueError: All arrays must be of the same length
# df = pd.DataFrame({
#     'x1': [1, 2, 3, 4, 5], 'y1': [2, 4, 6, 8, 10],
#     'x2': [1.5, 2.5, 3.5], 'y2': [3, 5, 7],
# })

df_new_interpolated_at_fixed_x_intervals = interpolate_df_at_fixed_x_intervals(
    df1['x1'], df1['y1'], df2['x2'], df2['y2'], x_interval=0.25)

print(f"df1:\n{df1}\n")
print(f"df2:\n{df2}\n")
print(f"df_new_interpolated_at_fixed_x_intervals:\n{df_new_interpolated_at_fixed_x_intervals}\n")

# =================================
# Method 3B to insert NaNs instead of allowing extrapolation outside of the input x-bounds.
print("==== [BEST, if you want NO extrapolation] Method 3B: same as Method 3, except don't allow\n"
      "extrapolation ====\n")
# =================================

def interpolate_df_at_fixed_x_intervals_no_extrapolation(x1, y1, x2, y2, x_interval):
    """
    Interpolate dataframes at fixed x intervals.
    """
    x_min = min(x1.min(), x2.min())
    x_max = max(x1.max(), x2.max())

    x_new = np.arange(x_min, x_max + x_interval, x_interval)
    x_new = pd.Series(x_new)

    # To prevent extrapolation outside of the range of `x1` and `x2`, and to thereby force
    # those values to be `NaN` instead, set `bounds_error=False`.
    interpolation_func1 = interp1d(x1, y1, kind='linear', bounds_error=False)
    interpolation_func2 = interp1d(x2, y2, kind='linear', bounds_error=False)
    y1_new = interpolation_func1(x_new)
    y2_new = interpolation_func2(x_new)
    y_diff = y1_new - y2_new

    df_interpolated = pd.DataFrame({
        "x_new": x_new,      # the new set of x-values; arbitrarily use `x1`'s name
        "y1_new": y1_new,    # the new, interpolated y1 values
        "y2_new": y2_new,    # the new, interpolated y2 values
        "y_diff": y_diff
    })

    return df_interpolated

df_new_interpolated_at_fixed_x_intervals_no_extrapolation = \
    interpolate_df_at_fixed_x_intervals_no_extrapolation(
        df1['x1'], df1['y1'], df2['x2'], df2['y2'], x_interval=0.25)

print(f"df1:\n{df1}\n")
print(f"df2:\n{df2}\n")
print(f"df_new_interpolated_at_fixed_x_intervals_no_extrapolation [NOTICE THE NAN values!]:\n"
      f"{df_new_interpolated_at_fixed_x_intervals_no_extrapolation}\n")

# =================================
# [less-robust (and erroneous: CANNOT EXTRAPOLATE) alternative to using SciPy's `interp1d()`]
print("==== [DO NOT USE! PRODUCES ERRONEOUS RESULTS WHEN EXTRAPOLATING OUTSIDE OF THE INPUT\n"
      "X VALUES; all y_diff values should be zeros, but are not here!] METHOD 4: using\n"
      "`np.interp()` at fixed x-value intervals ====")
# =================================

def interpolate_df_at_fixed_x_intervals_numpy(x1, y1, x2, y2, x_interval):
    """
    Interpolate dataframes at fixed x intervals, but this time using `np.interp()` instead of
    `scipy.interpolate.interp1d()`.
    """
    x_min = min(x1.min(), x2.min())
    x_max = max(x1.max(), x2.max())

    x_new = np.arange(x_min, x_max + x_interval, x_interval)
    y1_new = np.interp(x_new, x1, y1)
    y2_new = np.interp(x_new, x2, y2)
    y_diff = y1_new - y2_new

    df_interpolated = pd.DataFrame({
        x1.name + "_new": x_new,     # the new set of x-values; arbitrarily use `x1`'s name
        y1.name + "_new": y1_new,    # the new, interpolated y1 values
        y2.name + "_new": y2_new,    # the new, interpolated y2 values
        "y_diff": y_diff,
    })

    return df_interpolated  # Contains x_new, y1_new, y2_new, and y_diff

df_new_interpolated_at_fixed_x_intervals_numpy = interpolate_df_at_fixed_x_intervals_numpy(
    df1['x1'], df1['y1'], df2['x2'], df2['y2'], x_interval=0.25)

print(f"df1:\n{df1}\n")
print(f"df2:\n{df2}\n")
print(f"df_new_interpolated_at_fixed_x_intervals_numpy:\n"
      f"{df_new_interpolated_at_fixed_x_intervals_numpy}\n")



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

eRCaGuy_hello_world$ python/pandas_dataframe_interpolation_via_scipy_interpolate.py
/usr/lib/python3/dist-packages/scipy/__init__.py:146: UserWarning: A NumPy version >=1.17.3 and <1.25.0 is required for this version of SciPy (detected version 1.25.2
  warnings.warn(f"A NumPy version >={np_minversion} and <{np_maxversion}"
==== [GOOD] METHOD 1: manual, using the x-values of the longer dataframe ====

df1:
   x   y
0  1   2
1  2   4
2  3   6
3  4   8
4  5  10

df2:
     x  y
0  1.5  3
1  2.5  5
2  3.5  7

df2_interpolated:
   x     y
0  1   2.0
1  2   4.0
2  3   6.0
3  4   8.0
4  5  10.0

df_diff:
   x    y
0  1  0.0
1  2  0.0
2  3  0.0
3  4  0.0
4  5  0.0

==== [BETTER] METHOD 2: generic, function-based, using the x-values of the longer dataframe ====

df1:
   x1  y1
0   1   2
1   2   4
2   3   6
3   4   8
4   5  10

df2:
    x2  y2
0  1.5   3
1  2.5   5
2  3.5   7

df_new_interpolated:
   x1  y1  y2_interpolated  y_diff
0   1   2              2.0     0.0
1   2   4              4.0     0.0
2   3   6              6.0     0.0
3   4   8              8.0     0.0
4   5  10             10.0     0.0

==== [BEST] METHOD 3: generic, function-based, at fixed x-value intervals; uses
`scipy.interpolate.interp1d()` ====

df1:
   x1  y1
0   1   2
1   2   4
2   3   6
3   4   8
4   5  10

df2:
    x2  y2
0  1.5   3
1  2.5   5
2  3.5   7

df_new_interpolated_at_fixed_x_intervals:
    x1_new  y1_new  y2_new  y_diff
0     1.00     2.0     2.0     0.0
1     1.25     2.5     2.5     0.0
2     1.50     3.0     3.0     0.0
3     1.75     3.5     3.5     0.0
4     2.00     4.0     4.0     0.0
5     2.25     4.5     4.5     0.0
6     2.50     5.0     5.0     0.0
7     2.75     5.5     5.5     0.0
8     3.00     6.0     6.0     0.0
9     3.25     6.5     6.5     0.0
10    3.50     7.0     7.0     0.0
11    3.75     7.5     7.5     0.0
12    4.00     8.0     8.0     0.0
13    4.25     8.5     8.5     0.0
14    4.50     9.0     9.0     0.0
15    4.75     9.5     9.5     0.0
16    5.00    10.0    10.0     0.0

==== [BEST, if you want NO extrapolation] Method 3B: same as Method 3, except don't allow
extrapolation ====

df1:
   x1  y1
0   1   2
1   2   4
2   3   6
3   4   8
4   5  10

df2:
    x2  y2
0  1.5   3
1  2.5   5
2  3.5   7

df_new_interpolated_at_fixed_x_intervals_no_extrapolation [NOTICE THE NAN values!]:
    x_new  y1_new  y2_new  y_diff
0    1.00     2.0     NaN     NaN
1    1.25     2.5     NaN     NaN
2    1.50     3.0     3.0     0.0
3    1.75     3.5     3.5     0.0
4    2.00     4.0     4.0     0.0
5    2.25     4.5     4.5     0.0
6    2.50     5.0     5.0     0.0
7    2.75     5.5     5.5     0.0
8    3.00     6.0     6.0     0.0
9    3.25     6.5     6.5     0.0
10   3.50     7.0     7.0     0.0
11   3.75     7.5     NaN     NaN
12   4.00     8.0     NaN     NaN
13   4.25     8.5     NaN     NaN
14   4.50     9.0     NaN     NaN
15   4.75     9.5     NaN     NaN
16   5.00    10.0     NaN     NaN

==== [DO NOT USE! PRODUCES ERRONEOUS RESULTS WHEN EXTRAPOLATING OUTSIDE OF THE INPUT
X VALUES; all y_diff values should be zeros, but are not here!] METHOD 4: using
`np.interp()` at fixed x-value intervals ====
df1:
   x1  y1
0   1   2
1   2   4
2   3   6
3   4   8
4   5  10

df2:
    x2  y2
0  1.5   3
1  2.5   5
2  3.5   7

df_new_interpolated_at_fixed_x_intervals_numpy:
    x1_new  y1_new  y2_new  y_diff
0     1.00     2.0     3.0    -1.0
1     1.25     2.5     3.0    -0.5
2     1.50     3.0     3.0     0.0
3     1.75     3.5     3.5     0.0
4     2.00     4.0     4.0     0.0
5     2.25     4.5     4.5     0.0
6     2.50     5.0     5.0     0.0
7     2.75     5.5     5.5     0.0
8     3.00     6.0     6.0     0.0
9     3.25     6.5     6.5     0.0
10    3.50     7.0     7.0     0.0
11    3.75     7.5     7.0     0.5
12    4.00     8.0     7.0     1.0
13    4.25     8.5     7.0     1.5
14    4.50     9.0     7.0     2.0
15    4.75     9.5     7.0     2.5
16    5.00    10.0     7.0     3.0

"""
