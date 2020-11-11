#!/usr/bin/python3

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

"""
GS
1 Nov. 2020

References:
1. Google search for "plot csv in python":
https://www.google.com/search?q=plot+csv+in+python&oq=plot+csv+in+python&aqs=chrome..69i57.8976j0j4&client=ms-android-google&sourceid=chrome-mobile&ie=UTF-8
2. https://pythonprogramming.net/loading-file-data-matplotlib-tutorial/
3. https://stackoverflow.com/a/46220898/4561887
4. https://stackoverflow.com/questions/46219792/how-to-get-labels-by-numpy-loadtext
    1. *****https://stackoverflow.com/questions/46219792/how-to-get-labels-by-numpy-loadtext/46220898#46220898

Install Python dependencies:

    pip3 install matplotlib
    pip3 install pandas

Run command:

    ./plot_data.py

"""

import matplotlib.pyplot as pyplot
# import numpy
import pandas
import time

# filename = "data/temp/double_resolution_test_3.csv"
# filename = "data/temp/double_resolution_test_3_20201031#2.csv"
# filename = "data/temp/double_resolution_test_3_20201031#3_recombined.csv"
filename = "data/temp/double_resolution_test_4.csv"

print("Reading file.")
t_start_sec = time.time()
data = pandas.read_csv(filename)
print("read time (sec) = {}".format(time.time() - t_start_sec))
u64_time_ns_label = data.columns[0]
error_ns_label = data.columns[1]
# print(u64_time_ns_label)
# print(error_ns_label)

u64_time_ns = data[u64_time_ns_label]
error_ns = data[error_ns_label]

pyplot.figure()
pyplot.plot(u64_time_ns, error_ns)
pyplot.xlabel(u64_time_ns_label.strip())
pyplot.ylabel(error_ns_label.strip())
pyplot.title("Floating Point Error")
# pyplot.get_legend_handles_labels()
# pyplot.legend()
print("Showing plot.")
pyplot.show()

