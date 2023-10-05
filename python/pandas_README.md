This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# What is Pandas?

Me: 
> What is Pandas?

GitHub Copilot:
> **Pandas** is a popular open-source Python library for data manipulation and analysis. It provides data structures for efficiently storing and manipulating large datasets, as well as tools for data cleaning, merging, reshaping, and visualization.
> 
> The two primary data structures in Pandas are the `Series` and `DataFrame` objects. A `Series` is a one-dimensional array-like object that can hold any data type, while a `DataFrame` is a two-dimensional table-like object that can hold multiple `Series` objects. Pandas also provides many functions for working with these data structures, including functions for filtering, grouping, and aggregating data.
> 
> Pandas is widely used in data science, finance, and other fields where large datasets need to be analyzed and manipulated. It is often used in conjunction with other Python libraries such as **NumPy**, **Matplotlib**, and **Scikit-learn** to create powerful data analysis and visualization tools.

From Wikipedia: https://en.wikipedia.org/wiki/Pandas_(software):

>  The name is derived from the term "panel data", an econometrics term for data sets that include observations over multiple time periods for the same individuals.


# Learning resources

_Rough list order: most useful first:_

1. Talk to GitHub Copilot, Bing AI, and ChatGPT for help to use it.
1. Official Pandas User Guide: 10 minutes to pandas: https://pandas.pydata.org/pandas-docs/stable/user_guide/10min.html
1. https://github.com/Coldsp33d/stackoverflow-pandas-canonicals - a collection of resources by this avid Pandas user and high-reputation Stack Overflow user, [@cs95](https://stackoverflow.com/users/4909087/cs95).
    1. [How to iterate over rows in a DataFrame in Pandas? Answer: DON'T\*!](https://stackoverflow.com/a/55557758/4561887)
    1. [NEVER grow a DataFrame row-wise!](https://stackoverflow.com/a/56746204/4561887)
    1. [What is "vectorization"?](https://stackoverflow.com/q/1422149/4561887)
1. Official Pandas reference documentation: https://pandas.pydata.org/docs/reference/frame.html
1. https://docs.python.org/3/tutorial/datastructures.html#list-comprehensions


# Pandas `DataFrame`s & misc. notes

This is too big of a topic to cover here, so let me just put down a few reminders and notes to myself regarding some "gotchas".

## _Special keywords or values_ that Pandas will recognize and treat special when parsing a CSV file

When calling `pd.read_csv()`, the parser will interpret your CSV file based on heuristics. Ex: `1.0` is a float, `1` is an int, `True` is a boolean, `NaN`, or `None` are `np.nan` NaN values, multiple commas in a row with nothing between them (or perhaps only whitespace), are also NaNs, `Noon` or any other non-keyword strings are just strings, etc. Here is what GitHub Copilot told me: 

**Me**: Give me a list of special keywords or values that Pandas will recognize and treat special in a CSV file.

**GitHub Copilot:**

> Pandas recognizes the following special keywords or values in a CSV file:
> 
> - `NaN`: This is a special value that represents a missing or undefined value. Pandas will interpret any cell in a CSV file that contains the string "NaN" as a missing or NaN value.
> - `None`: This is another special value that represents a missing or undefined value. Pandas will interpret any cell in a CSV file that is empty or contains the string "None" as a missing or NaN value.
> - `Inf` and `-Inf`: These are special values that represent positive and negative infinity, respectively. Pandas will interpret any cell in a CSV file that contains the string "Inf" or "-Inf" as the corresponding infinity value.
> - `True` and `False`: These are special values that represent boolean values. Pandas will interpret any cell in a CSV file that contains the string "True" or "False" as the corresponding boolean value.
> - Dates and times: Pandas can recognize and parse a variety of date and time formats in a CSV file, including ISO 8601 format, Excel serial date format, and many others. Pandas will automatically convert these values to the appropriate datetime data type.
> 
> Note that Pandas can also recognize and parse other special values and formats in a CSV file, depending on the data type of the column and the parsing options specified. However, the above list includes some of the most common special values and formats that Pandas users may encounter in a CSV file.

ElectricRCAircraftGuy: Give me some online links to the documentation that lists these special keywords or values.

GitHub Copilot: 

> Sure, here are some links to the Pandas documentation that describe the special keywords or values recognized by Pandas in a CSV file:
> 
> - `NaN`: https://pandas.pydata.org/pandas-docs/stable/user_guide/missing_data.html#missing-data [GS: see below for a "Full list of `NaN` values in Pandas"]
> - `None`: https://pandas.pydata.org/pandas-docs/stable/user_guide/missing_data.html#missing-data
> - `Inf` and `-Inf`: https://pandas.pydata.org/pandas-docs/stable/user_guide/io.html#na-values
> - `True` and `False`: https://pandas.pydata.org/pandas-docs/stable/user_guide/io.html#na-values
> - Dates and times: https://pandas.pydata.org/pandas-docs/stable/user_guide/io.html#datetime-handling

## You can*not* detect `NaN` values with `==` or `!=`! `np.nan == np.nan` is `False`!

I also learned here (https://pandas.pydata.org/pandas-docs/stable/user_guide/missing_data.html#missing-data) to watch out for this gotcha!: 

You can*not* detect `NaN` values with `==` or `!=`! You must use `pd.isna()` or `pd.notna()` instead!

> **Warning**
> 
> One has to be mindful that in Python (and NumPy), the `nan`'s don’t compare equal, but `None`'s do. Note that pandas/NumPy uses the fact that `np.nan != np.nan`, and treats `None` like `np.nan`.
> 
> ```py
> None == None  # noqa: E711
> Out[11]: True
> 
> np.nan == np.nan
> Out[12]: False
> ```
> 
> So as compared to above, a scalar equality comparison versus a `None`/`np.nan` doesn’t provide useful information.

In other words, again, you can*not* use `== np.nan` or `!= np.nan` to detect `NaN` values! You must use `pd.isna()` or `pd.notna()` instead!

Ex:
```py
import pandas as pd

# Example DataFrame with NaN values
df = pd.DataFrame({'col1': [1, 2, None, 4], 'col2': ['a', 'b', 'c', None]})

# Use pd.isna() to detect NaN values (None being one of those)
nan_mask = pd.isna(df)

# Print the mask
print(nan_mask)
```

Output:
```
    col1   col2
0  False  False
1  False  False
2   True  False
3  False   True
```

## Full list of `NaN` values in Pandas:

And this source tells me the full list of strings in a CSV file that will be interpreted as `NaN` values: https://pandas.pydata.org/pandas-docs/stable/user_guide/io.html#na-values :

> The default `NaN` recognized values are `['-1.#IND', '1.#QNAN', '1.#IND', '-1.#QNAN', '#N/A N/A', '#N/A', 'N/A', 'n/a', 'NA', '<NA>', '#NA', 'NULL', 'null', 'NaN', '-NaN', 'nan', '-nan', 'None', '']`.

Full list of `NaN` values in Pandas:

- `NaN` (`pd.nan`) values are recognized by default in Pandas from the following strings when reading a CSV file: 
    - `'-1.#IND'`
    - `'1.#QNAN'`
    - `'1.#IND'`
    - `'-1.#QNAN'`
    - `'#N/A N/A'`
    - `'#N/A'`
    - `'N/A'`
    - `'n/a'`
    - `'NA'`
    - `'<NA>'`
    - `'#NA'`
    - `'NULL'`
    - `'null'`
    - `'NaN'`
    - `'-NaN'`
    - `'nan'`
    - `'-nan'`
    - `'None'`
    - `''` - empty string, ex: signified by two commas in a row with nothing between them (`,,`), or a comma at the beginning of a line with nothing in front of it (`,`), or perhaps only whitespace in front of a comma [I have not tested the whitespace one, but I know the comma thing to be true]
