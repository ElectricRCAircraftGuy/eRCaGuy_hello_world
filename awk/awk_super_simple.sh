#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# By: Gabriel Staples
# awk_super_simple.sh

# Run It:
#   echo -e "hey1\nhello\nhey2" | ./awk_super_simple.sh

# # 1. FAILS!
# #   $ echo -e "hey1\nhello\nhey2" | ./awk_super_simple.sh
# #   gawk: cmd. line:3: BEGIN blocks must have an action part
# gawk \
# '
# BEGIN
# {
#     print "START OF AWK PROGRAM"
# }
# '

# # 2. PASSES!
# #   $ echo -e "hey1\nhello\nhey2" | ./awk_super_simple.sh
# #   START OF AWK PROGRAM
# gawk \
# '
# BEGIN {
#     print "START OF AWK PROGRAM"
# }
# '

# # 3. FAILS TO PROVIDE EXPECTED OUTPUT!
# #   $ echo -e "hey1\nhello\nhey2" | ./awk_super_simple.sh
# #   hey1
# #   hey1
# #   hello
# #   hey2
# #   hey2
# gawk \
# '
# /hey/ 
# {
#     print $0
# }
# '

# # 4. WORKS AS EXPECTED!
# #   $ echo -e "hey1\nhello\nhey2" | ./awk_super_simple.sh
# #   hey1
# #   hey2
# gawk \
# '
# /hey/ {
#     print $0
# }
# '

# # 5. Also works the same as 4! (is more explicit than 4.)
# gawk \
# '
# $0 ~ /hey/ {
#     print $0
# }
# '

# 6. Also works the same as 4 and 5! (is more explicit still than 5. or 4.)
# See this Q here for where I got it: 
# https://stackoverflow.com/questions/27776583/begin-blocks-must-have-an-action-part-error-in-awk-script
gawk \
'
if ( $0 ~ /hey/ ) {
    print $0
}
'





# name = "Gabriel"

# /hey/ {
#     name = "Gabriel"
#     print $0, name
# }

# # END
# # {
# #     print "END OF AWK PROGRAM"
# # }
# '
