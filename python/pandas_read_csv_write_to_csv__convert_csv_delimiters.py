#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2023

Use the Pandas library to import a CSV file that could have commas or tabs or both as delimiters.
Then, convert it to a plain CSV file with commas as the delimiter. This allows you to import it
faster next time by using the `c` engine instead of the `python` engine.

Status: Done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint pandas_read_csv_write_to_csv__convert_csv_delimiters.py
```

Run command:
```bash
./pandas_read_csv_write_to_csv__convert_csv_delimiters.py
# OR
python3 pandas_read_csv_write_to_csv__convert_csv_delimiters.py
```

References:
1. "eRCaGuy_hello_world/python/pandas_read_and_plot_csv_GREAT.py"


"""

import os
import pandas as pd

# See: "eRCaGuy_hello_world/python/import_helper.py"
FULL_PATH_TO_SCRIPT = os.path.abspath(__file__)
SCRIPT_DIRECTORY = str(os.path.dirname(FULL_PATH_TO_SCRIPT))

def mkdir(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

mkdir(f"{SCRIPT_DIRECTORY}/../fake_data/figures")

filename = "fake_person_data.csv"
filepath = f"{SCRIPT_DIRECTORY}/../fake_data/{filename}"
print(f"Reading file: \"{filepath}\"")

dataframe = pd.read_csv(
    filepath,
    sep=r"[,\t]+", # allow any number of either commas or tabs as the separator
    header=0,  # the first non-blank row is the header
    # NB: using the "python" engine instead of the default "c" engine is much slower, but allows
    # us to have a regex `sep` separator value above, instead of just specifying a single
    # character. When logging files, just use a plain, single comma (`,`) as the separator in
    # order to avoid this problem.
    engine="python",
    skip_blank_lines=True,
    # Force the zipcode column to be treated as a string so that leading zeros are not stripped.
    # COMMENT THIS OUT TO SEE THE DIFFERENCE!
    dtype={"zip": str},
)
#
# Alternatively, just do this for a plain and simple CSV file. This uses the default `c` parsing
# engine instead of the `python` engine, and is much faster.
# dataframe = pd.read_csv(filepath)

# write it back to a plain CSV file with commas as the delimiter
filepath_out = os.path.splitext(filepath)[0] + "_converted.csv"
print(f"Writing file: \"{filepath_out}\"")
# Note: for tab-delimited, use `sep="\t"` instead of `sep=","`
dataframe.to_csv(filepath_out, sep=",", index=False)



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world$ python/pandas_read_csv_write_to_csv__convert_csv_delimiters.py
    Reading file: "/home/gabriel/GS/dev/eRCaGuy_hello_world/python/../fake_data/fake_person_data.csv"
    Writing file: "/home/gabriel/GS/dev/eRCaGuy_hello_world/python/../fake_data/fake_person_data_converted.csv"

"""
