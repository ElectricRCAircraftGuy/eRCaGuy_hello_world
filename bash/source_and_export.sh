#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# References:
# 1. *****[SEE MY OWN ANS & DETAILED EXPLANATIONS HERE!] 
#    https://stackoverflow.com/questions/15474650/unix-what-is-the-difference-between-source-and-export/62626515#62626515

echo "var1 = $var1"
var2="world"

# TEST EXAMPLE, WITH COMMENTS ADDED 
# (SEE ALSO MY STACK OVERFLOW ANSWER ABOVE):
#
#    $ echo "$var1"              # var1 contains nothing locally
# 
#    $ var1="hello"              # set var1 to something in the current process only
#    $ ./source_and_export.sh    # call a sub-process
#    var1 =                      # the sub-process can't see what I just set var1 to
#    $ export var1               # **export** var1 so sub-processes will receive it
#    $ ./source_and_export.sh    # call a sub-process
#    var1 = hello                # now the sub-process sees what I previously set var1 to
#    $ echo "$var1 $var2"        # but I can't see var2 from the subprocess/subscript
#    hello 
#    $ . ./source_and_export.sh  # **source** the sub-script to _import_ its var2 into the current process
#    var1 = hello
#    $ echo "$var1 $var2"        # now I CAN see what the subprocess set var2 to because I **sourced it!**
#    hello world                 # BOTH var1 from the current process and var2 from the sub-process print in the current process!
#    $ unset var1                # unexport (`unset`) var1
#    $ echo "$var1"              # var1 is now NOT set in the current process
#    $ ./source_and_export.sh    # and the sub-process doesn't receive it either
#    var1 = 
#    $ var1="hey"                # set var1 again in the current process
#    $ . ./source_and_export.sh  # if I **source** the script, it runs in the current process, so it CAN see var1 from the current process!
#    var1 = hey                  # notice it prints
#    $ ./source_and_export.sh    # but if I run the script as a sub-process, it can NOT see var1 now because it was `unset` (unexported)
#    var1 =                      #   above and has NOT been `export`ed again since then!
#    $
