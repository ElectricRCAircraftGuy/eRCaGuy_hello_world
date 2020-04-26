# Rounding Integer Division

AKA: performing rounding of the result of division during integer division.

Integer division in C or C++ usually just truncates the part after the decimal in order to store the result into an integer. However, using a little bit of trickery, it's actually possible to **round up**, **round down**, or **round to the nearest integer** during integer division. This project shows how!

Note that doing this for positive-only integer inputs is far easier to understand conceptually than handling negative inputs too, but this project handles both by making use of the ternary operator (`test ? do_if_true : do_if_false`). 

Read more here: https://stackoverflow.com/questions/2422712/rounding-integer-division-instead-of-truncating/58568736#58568736

# Run command:

    ./run_tests.sh

# Description of Files:

1. **rounding_integer_division.cpp** = the main file, to be compiled and run as C code OR as C++ code
1. **rounding_integer_division.c** = a symbolic link to the main file so that it can be compiled and run in C too, since C expects files to end in .c.
1. **rounding_integer_division.md** = the answer/description I'm drafting for [my Stack Overflow answer here](https://stackoverflow.com/questions/2422712/rounding-integer-division-instead-of-truncating/58568736#58568736), too.
1. **run_tests.sh** = the Bash shell script to run to test all of this code. Run it with `./run_tests.sh` while in this directory.
1. **run_tests_sample_output.txt** = copy/pasted sample output from running the test script above
