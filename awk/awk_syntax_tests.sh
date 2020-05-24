#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# By: Gabriel Staples
# awk_syntax_tests.sh
# Started: 23 May 2020 

# STATUS: IT WORKS! All examples in here are correct, have been tested, make valid points,
#         and have correct comments.

# Run It:
#   echo -e "hey1\nhello\nhey2" | ./awk_syntax_tests.sh

# # 1. FAILS!
# # See reason why here:
# # https://stackoverflow.com/questions/27776583/begin-blocks-must-have-an-action-part-error-in-awk-script
# #   $ echo -e "hey1\nhello\nhey2" | ./awk_syntax_tests.sh
# #   gawk: cmd. line:3: BEGIN blocks must have an action part
# gawk \
# '
# BEGIN
# {
#     print "START OF AWK PROGRAM"
# }
# '

# ========= USE THIS! ========
# # 2. PASSES! 
# #   $ echo -e "hey1\nhello\nhey2" | ./awk_syntax_tests.sh
# #   START OF AWK PROGRAM
# gawk \
# '
# BEGIN {
#     print "START OF AWK PROGRAM"
# }
# '

# # 3. FAILS TO PROVIDE EXPECTED OUTPUT!
# # Why? See this answer to my Q here, and my comments underneath it!
# # https://stackoverflow.com/questions/61979177/can-the-regex-matching-pattern-for-awk-be-placed-above-the-opening-brace-of-the/61979402#61979402
# # Essentially, `/hey/` acts as a stand-alone matcher with not action, so the default action of 
# # printing $0 takes place, followed by a second rule which is to print, but has no matcher, so
# # the default of matching *everything* takes place! Hence, whatever matches /hey/ is printed, and
# # then *each line* is printed too! This results in duplication of the hey1 and hey2 prints!
# # Test results:
# #   $ echo -e "hey1\nhello\nhey2" | ./awk_syntax_tests.sh
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

# ========= USE THIS! ========
# # 4. WORKS AS EXPECTED!
# #   $ echo -e "hey1\nhello\nhey2" | ./awk_syntax_tests.sh
# #   hey1
# #   hey2
# gawk \
# '
# /hey/ {
#     print $0
# }
# '

# ========= USE THIS! ========
# # 5. Also WORKS the same as 4! (is more explicit than 4.)
# # See, among other places, the example in the question here:
# # https://stackoverflow.com/questions/27776583/begin-blocks-must-have-an-action-part-error-in-awk-script
# gawk \
# '
# $0 ~ /hey/ {
#     print $0
# }
# '

# # 6. Does NOT work! It's a syntax error because the `if()` statement needs an extra set of curly 
# #    braces around the *whole thing!*
# #       $ echo -e "hey1\nhello\nhey2" | ./awk_syntax_tests.sh 
# #       gawk: cmd. line:2: if ($0 ~ /hey/) {
# #       gawk: cmd. line:2: ^ syntax error
# gawk \
# '
# if ($0 ~ /hey/) {
#     print $0
# }
# '

# # 7. Also DOES work, the same as 4 and 5! (is more explicit still than 5. or 4.)
# # See this Q here for where I got the idea: 
# # https://stackoverflow.com/questions/27776583/begin-blocks-must-have-an-action-part-error-in-awk-script
# # And here too: https://stackoverflow.com/questions/10739613/awk-if-else-issues
# #       $ echo -e "hey1\nhello\nhey2" | ./awk_syntax_tests.sh 
# #       hey1
# #       hey2
# gawk \
# '
# {
#     if ($0 ~ /hey/) 
#     {
#         print $0
#     }
# }
# '

# ========= USE THIS only *sometimes*!--when you really need an if/if-else type statement or 
# really need to be extra explicit! ========
# # 8. Also DOES work, the same as 4 and 5 and 7! (is more explicit still than 5. or 4., and uses
# # more-consistent/"better" syntax than 7. because it keeps the opening brace `{` of the if statement
# # on the same line as the if statement, more-consistent with the pattern { action } syntax 
# # *required* elsewhere!
# #       $ echo -e "hey1\nhello\nhey2" | ./awk_syntax_tests.sh 
# #       hey1
# #       hey2
# gawk \
# '
# {
#     if ($0 ~ /hey/) {
#         print $0
#     }
# }
# '

# 9. This works too!
# Sample output:
#       $ echo -e "hey1\nhello\nhey2" | ./awk_syntax_tests.sh 
#       START OF AWK PROGRAM
#       hey1 Gabriel
#       hey2 Gabriel
#       END OF AWK PROGRAM
gawk \
'
# ========= USE THIS! ========
BEGIN {
    print "START OF AWK PROGRAM"
}

# Does NOT do what I expect it to! Rather, this assigns "Gabriel" to variable `name`, then it 
# treats the result as a boolean expression, confirming in essence that name is in fact 
# not zero/empty, so it considers it "true", and then runs the action for it,
# which is empty, so it uses the default action of `print $0`. Therefore, this one variable 
# assignment line also prints the current record (line), which is not the intended behavior 
# of the programmer!
# name = "Gabriel" 

# To solve the above problem, either give it an empty action:
# (This works, but I prefer the next approach below more I think).
name = "Gabriel" {}

# ========= USE THIS! ========
# OR, make this variable assignment *part of* an action which gets applied to ALL records!
# (I prefer this approach to the above approach, and if you need to assign a bunch of variables
# at once, recommend you just do them all in a single rule like this at the beginning of your
# program, OR just do them individually wherever they are needed, as you see fit).
{
    name = "Gabriel"
}

# ========= USE THIS! ========
/hey/ {
    print $0, name
}

# ========= USE THIS! ========
END {
    print "END OF AWK PROGRAM"
}
'


