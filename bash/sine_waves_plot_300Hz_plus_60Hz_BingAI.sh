#!/bin/bash

# GS
# 9 Sept. 2023
# Bing AI: Plotting sine waves in Python (open in Edge browser only):
# https://sl.bing.net/iaa7CFoBq2e
#
# Requirements:
#
#     sudo apt update
#     sudo apt install gnuplot-qt
#


# Define the frequency and amplitude of the sine waves
f1=300 # Frequency of the first sine wave in Hz
a1=1 # Amplitude of the first sine wave
f2=60 # Frequency of the second sine wave in Hz
a2=0.5 # Amplitude of the second sine wave

# Define the time range and sampling rate
tmin=0 # Minimum time value in seconds
tmax=0.1 # Maximum time value in seconds
fs=10000 # Sampling rate in Hz
n=$(echo "($tmax - $tmin) * $fs" | bc) # Number of samples

# Create a temporary file to store the data
tmpfile=$(mktemp)

# Loop through the samples and calculate the sine waves
for i in $(seq 0 $n); do
  t=$(echo "scale=4; $tmin + $i / $fs" | bc) # Time value for each sample
  y1=$(echo "scale=4; $a1 * s($f1 * $t * 2 * 4*a(1))" | bc -l) # First sine wave
  y2=$(echo "scale=4; $a2 * s($f2 * $t * 2 * 4*a(1))" | bc -l) # Second sine wave
  y=$(echo "scale=4; $y1 + $y2" | bc) # Superimposed sine wave
  echo "$t $y1 $y2 $y" >> $tmpfile # Append the data to the file
done

# Plot the data using gnuplot
gnuplot -persist <<EOF
set xlabel "Time (s)"
set ylabel "Amplitude"
set title "Sine Waves"
plot "$tmpfile" using 1:2 with lines title "300Hz", \
     "$tmpfile" using 1:3 with lines title "60Hz", \
     "$tmpfile" using 1:4 with lines title "Superimposed"
EOF

# Remove the temporary file
rm $tmpfile
