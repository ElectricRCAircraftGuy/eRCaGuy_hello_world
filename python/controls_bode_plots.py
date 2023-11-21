#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Nov. 2023

Learn to plot Bode plots (frequency response plots) of transfer functions in Python.
---
See my Controls slides, Lecture_12, slides 11-12, here (private):
https://drive.google.com/drive/u/0/folders/1yvrecZpbRJPrPw-PPG6iscDiTRMwS0sU

IF YOU'RE LOOKING FOR THE SIMPLEST, QUICK EXAMPLE, look at 3. first, below.

Status: done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint controls_bode_plots.py
```

Run command:
```bash
./controls_bode_plots.py
# OR
python3 controls_bode_plots.py
```

References:
1. Controls notes; see above.
1. GitHub Copilot: I asked it to convert some code from MATLAB to Python for me, and it got me
   started.
1. Python `control` library documentation: https://python-control.readthedocs.io/en/0.9.4/
    1. https://python-control.readthedocs.io/en/latest/generated/control.bode_plot.html
    1.

"""

import control
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import os

# See my answer: https://stackoverflow.com/a/74800814/4561887
FULL_PATH_TO_SCRIPT = os.path.abspath(__file__)
SCRIPT_DIRECTORY = str(os.path.dirname(FULL_PATH_TO_SCRIPT))
SCRIPT_PARENT_DIRECTORY = str(os.path.dirname(SCRIPT_DIRECTORY))
FILENAME = str(os.path.basename(FULL_PATH_TO_SCRIPT))
FILENAME_NO_EXTENSION = os.path.splitext(FILENAME)[0]
FILENAME_EXTENSION = os.path.splitext(FILENAME)[1]

def save_figure(savename):
    plt.savefig(f'{SCRIPT_DIRECTORY}/{FILENAME_NO_EXTENSION}_{savename}.svg')
    # plt.savefig(f'{SCRIPT_DIRECTORY}/{FILENAME_NO_EXTENSION}_{savename}.png')
    # plt.savefig(f'{SCRIPT_DIRECTORY}/{FILENAME_NO_EXTENSION}_{savename}.jpg')


"""
=========================================================
1. Bode plot for G(s) = (s + a)/1
From Lecture_12 slide 11:
=========================================================

Matlab code:
```matlab
num = [1,1];
den = 1;
bode(num,den);
grid on
```
"""

f1 = plt.figure()

# Bode plot for G(s) = (s + a)/1
num = [1, 1]
den = [1]
G = control.TransferFunction(num, den)

# Notes:
# 1. use `dB=True` to plot in dB, and `Hz=False` to plot in rad/s.
# 1. `wrap_phase=True` is necessary to wrap the phase from -180 to +180 degrees. Otherwise, it may
# be -360 to +360 deg.
# 1. Unless you pass `plot=False`, the plot will be generated via `matplotlib` automatically.
# 1. `omega` = frequency (x-axis), in rad/s since `Hz=False`.
mag, phase, omega = control.bode(G, dB=True, Hz=False, omega_limits=(10e-3, 10e2), wrap_phase=True)
save_figure("bode_plot_1")


"""
=========================================================
2. Same as above, except *manually* create the plot.
=========================================================
"""

f2 = plt.figure()

# Bode plot for G(s) = (s + a)/1
num = [1, 1]
den = [1]
G = control.TransferFunction(num, den)

mag, phase, omega = control.bode(G, dB=True, Hz=False, omega_limits=(10e-3, 10e2), wrap_phase=True,
                                 plot=False)

# **Manually** create the plots

plt.subplot(2, 1, 1)  # row 1, col 1, plot 1
plt.semilogx(omega, 20*np.log10(mag))  # Bode magnitude plot
# plt.xlabel('Frequency (rad/sec)')  # no label needed here--just put on the bottom plot
plt.ylabel('Magnitude (dB)')
plt.grid(True, which="both")  # "both" means major and minor grid lines

plt.subplot(2, 1, 2)
plt.semilogx(omega, np.degrees(phase))  # Bode phase plot
plt.xlabel('Frequency (rad/sec)')
plt.ylabel('Phase (deg)')
plt.grid(True, which="both")  # "both" means major and minor grid lines
# Set major gridlines at multiples of 45 degrees
ax = plt.gca()
ax.yaxis.set_major_locator(matplotlib.ticker.MultipleLocator(45))

save_figure("bode_plot_2")


"""
=========================================================
3. Bode plot for G(s) = 1/(s + a)
From Lecture_12 slide 12:
=========================================================

Matlab code:
```matlab
num = 1;
den = [1,1]
bode(num,den);
grid on
```
"""

f1 = plt.figure()

# Bode plot for G(s) = 1/(s + a)
num = [1]
den = [1, 1]
G = control.TransferFunction(num, den)
control.bode(G, dB=True, Hz=False, omega_limits=(10e-3, 10e2), wrap_phase=True)
save_figure("bode_plot_3")


# =========================================================
# Display the plots
# =========================================================

plt.show() # show all plots



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

(You'll see several plot windows open).

    eRCaGuy_hello_world/python$ ./controls_bode_plots.py


"""
