#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# By: Gabriel Staples
# awk_hello_world.sh
# - just a basic demo

# Run It:
#   ./awk_hello_world.sh input_file_1.txt

# Create some bash shell script variables
MY_STR="Hello World!"
DATE="$(date)"

# Call GNU awk (gawk), inputting the above bash variables into the gawk program as awk variables,
# then passing all input arguments to this script ("$@") to `gawk` after specifying the awk 
# program.
gawk \
-v my_str="$MY_STR" \
-v date="$DATE" \
'
# START OF THE AWK PROGRAM

BEGIN {
    print "START OF AWK PROGRAM"
}

# `$0` is a "record", which is by default a line since the default record separator is a
# newline (\n) char
line = $0
# Fields are be default separated by whitepace, such as spaces and tabs, so `$1`, `$2`, `$3`, etc.
# will, by default, obtain word 1, 2, and 3 in each record (line). You can also think of these
# as "columns" 1, 2, and 3, in the event your textual input data is columnated. 
field1 = $1
field2 = 

# Match all lines
{
    print ">>> " $

}

# END OF THE AWK PROGRAM
' \
"$@"
