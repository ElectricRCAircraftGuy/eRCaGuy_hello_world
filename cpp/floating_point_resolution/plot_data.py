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

Install Python dependencies:

    pip3 install matplotlib
    pip3 install pandas

Run command:

    ./plot_data.py

"""

import matplotlib.pyplot as pyplot
import numpy

x, y = numpy.loadtxt('data/temp/double_resolution_test_3.csv',
                     delimiter=',', unpack=True)
pyplot.plot(x,y, label='Loaded from file!')

pyplot.xlabel('x')
pyplot.ylabel('y')
pyplot.title('Interesting Graph\nCheck it out')
pyplot.legend()
pyplot.show()

