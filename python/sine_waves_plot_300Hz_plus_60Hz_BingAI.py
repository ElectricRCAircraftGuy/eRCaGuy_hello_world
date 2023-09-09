#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
9 Sept. 2023
Bing AI [open in Edge browser only]: Plotting sine waves in Python:
https://sl.bing.net/i0je9FwGFGe

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint sine_waves_plot_300Hz_plus_60Hz_BingAI.py
```

Run command:
```bash
./sine_waves_plot_300Hz_plus_60Hz_BingAI.py
# OR
python3 sine_waves_plot_300Hz_plus_60Hz_BingAI.py
```

References:
1.

"""
# Import the libraries
import numpy as np
import matplotlib.pyplot as plt

# Define the frequency and amplitude of the sine waves
f1 = 300 # Frequency of the first sine wave in Hz
a1 = 1 # Amplitude of the first sine wave
f2 = 60 # Frequency of the second sine wave in Hz
a2 = 0.5 # Amplitude of the second sine wave

# Define the time range and sampling rate
t = np.linspace(0, 0.1, 1000) # Time range from 0 to 0.1 seconds with 1000 samples
fs = 10000 # Sampling rate in Hz

# Calculate the sine waves
y1 = a1 * np.sin(2 * np.pi * f1 * t) # First sine wave
y2 = a2 * np.sin(2 * np.pi * f2 * t) # Second sine wave
y = y1 + y2 # Superimposed sine wave

# Plot the sine waves
plt.figure(figsize=(10, 6)) # Create a figure with a specified size
plt.plot(t, y1, label='300Hz') # Plot the first sine wave with a label
plt.plot(t, y2, label='60Hz') # Plot the second sine wave with a label
plt.plot(t, y, label='Superimposed') # Plot the superimposed sine wave with a label
plt.xlabel('Time (s)') # Add a label for the x-axis
plt.ylabel('Amplitude') # Add a label for the y-axis
plt.title('Sine Waves') # Add a title for the plot
plt.legend() # Add a legend for the plot
plt.show() # Show the plot
