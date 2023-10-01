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
pylint pandas_dataframe_interpolation_via_scipy_interpolate_Copilot.py
```

Run command:
```bash
./pandas_dataframe_interpolation_via_scipy_interpolate_Copilot.py
# OR
python3 pandas_dataframe_interpolation_via_scipy_interpolate_Copilot.py
```

References:
1. GitHub Copilot
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


"""


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

# print the results
print(f"df1:\n{df1}\n")
print(f"df2:\n{df2}\n")
print(f"df2_interpolated:\n{df2_interpolated}\n")
print(f"df_diff:\n{df_diff}\n")


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

eRCaGuy_hello_world$ python/pandas_dataframe_interpolation_via_scipy_interpolate_Copilot.py
/usr/lib/python3/dist-packages/scipy/__init__.py:146: UserWarning: A NumPy version >=1.17.3 and <1.25.0 is required for this version of SciPy (detected version 1.25.2
  warnings.warn(f"A NumPy version >={np_minversion} and <{np_maxversion}"
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

"""
