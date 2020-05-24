#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# By: Gabriel Staples
# awk_hello_world.sh
# Started: 23 May 2020 
# - just a basic demo to show some of the features of awk

# STATUS: IT WORKS! All examples in here are correct, have been tested, make valid points,
#         and have correct comments.

# Run It:
#   ./awk_hello_world.sh input_file_1.txt
# Command to generate "awk_hello_world_SAMPLE_OUTPUT.txt":
#   ./awk_hello_world.sh input_file_1.txt > awk_hello_world_SAMPLE_OUTPUT.txt

# Awk-language-specific References:
# 1. Great awk intro, description, & examples to get started!: https://en.wikipedia.org/wiki/AWK
# 1. awk cheatsheet: https://www.shortcutfoo.com/app/dojos/awk/cheatsheet
# 1. *****"The Essential Syntax of AWK": https://www.grymoire.com/Unix/Awk.html#uh-5
# 1. https://www.gnu.org/software/gawk/manual/html_node/Using-Shell-Variables.html
# 1. Dynamic Regexps: https://www.gnu.org/software/gawk/manual/html_node/Computed-Regexps.html
# 1. https://www.gnu.org/software/gawk/manual/html_node/Quoting.html
# 1. awk print: https://www.gnu.org/software/gawk/manual/html_node/Print.html 
# 1. awk printf: https://www.gnu.org/software/gawk/manual/html_node/Basic-Printf.html
# 1. awk printf examples: https://www.gnu.org/software/gawk/manual/html_node/Printf-Examples.html
#   1. Sample data files for all awk examples: https://www.gnu.org/software/gawk/manual/html_node/Sample-Data-Files.html#Sample-Data-Files
# 1. awk next: https://www.gnu.org/software/gawk/manual/html_node/Next-Statement.html
# 1. awk String Functions: https://www.gnu.org/software/gawk/manual/html_node/String-Functions.html; Including:
#   1. gsub()
#   1. match()
#   1. gensub()
#   1. etc. 
# 1. awk `next` statement: https://www.gnu.org/software/gawk/manual/html_node/Next-Statement.html
# 1. awk variable and shell variable usage
#   1. see the last example here:
#      https://www.gnu.org/software/gawk/manual/html_node/Printf-Examples.html
#   1. and also this info here: 
#      https://www.gnu.org/software/gawk/manual/html_node/Using-Shell-Variables.html
# 1. See also my Q & the answers & comments here: 
#    https://stackoverflow.com/questions/61932427/git-diff-with-line-numbers-and-proper-code-alignment-indentation

# Awk-language Notes:
# The gist of awk: pattern {action}
#  - See here: https://en.wikipedia.org/wiki/AWK
# Meaning of tidle (~): "matches a regular expression against a string" (https://en.wikipedia.org/wiki/AWK)
#  - Can be read as: "check the operands on either side to see if they match" (http://billconner.com/techie/awk.html)
#  - See also here: https://www.grymoire.com/Unix/Awk.html#uh-11
#  - Ex:  `my_var ~ /regex/ { action }` means: "if the contents of my_var match the regular 
#       expression "regex", then do `action`".


# Create some bash shell script variables
MY_STR="Hello World!"
DATE="$(date)"

# IMPORTANT: SINCE I'M USING SINGLE QUOTES (' ') AROUND THE WHOLE AWK PROGRAM BELOW, ***NO***
# UNESCAPED SINGLE QUOTES ARE ALLOWED IN THE CODE BELOW, ***INCLUDING IN AWK COMMENTS!*** Since 
# this comment says "I'm" in it, if you move it down into the awk code below, it will make the awk
# code fail to run too!

# Call GNU awk (gawk), inputting the above bash variables into the gawk program as awk variables,
# then passing all input arguments to this script ("$@") to `gawk` after specifying the awk 
# program.
gawk \
-v my_str="$MY_STR" \
-v date="$DATE" \
'
# START OF THE AWK PROGRAM

# BEGIN is a special matcher that matches only one single time at the very beginning of the 
# program. See here: 
# https://www.gnu.org/software/gawk/manual/html_node/Using-BEGIN_002fEND.html
BEGIN {
    print "START OF AWK PROGRAM"
    # Print the variables that I passed in from the bash shell above like this, for example.
    # More descriptions of `print` and `printf` are provided below, so dont get caught up 
    # on these just yet.
    print my_str
    printf "%s\n\n", date
}

# Assign all variables inside a block, or else assigning a variable will also cause the current
# record (line) to be printed. See details and explanation in test 9 at the end of 
# "awk_syntax_tests.sh". 
{
    # `$0` is a "record", which is by default a line since the default record separator is a
    # newline (\n) char
    current_line = $0
    # Fields are be default separated by whitepace, such as spaces and tabs, so `$1`, `$2`, `$3`, etc.
    # will, by default, obtain word 1, 2, and 3 in each record (line). You can also think of these
    # as "columns" 1, 2, and 3, in the event your textual input data is columnated. 
    field1 = $1
    field2 = $2
    field3 = $3
}

# A plain block such as this one below or the one above matches ALL lines
{
    # Notice that string concatenation is automatic: simply place two strings next to each other
    # and they are automatically concatenated into one string.
    print "field2 = \""field2"\""
}

# A boolean expression can also be used to choose whether or not to perform an action block.
# The number 1 is always true, so this will also be performed on ALL lines
1 {
    print "field2 again = \""field2"\""
} 

# This, however, will NEVER run, since its boolean expression is 0, which is always false
0 {
    print "field2 A THIRD TIME = \""field2"\""
} 

# This only performs the action in braces { } below if it matches the regular expression /Jan/. 
# Note that the opening brace MUST be on the same line as the regular expression! See here:
# https://stackoverflow.com/questions/61979177/can-the-regex-matching-pattern-for-awk-be-placed-above-the-opening-brace-of-the
/Jan/ {
    # FNR is a built-in variable (https://en.wikipedia.org/wiki/AWK#Built-in_variables) which
    # means File Number of Records, or "record number" in this file. Since Im using the default,
    # which is to have records split by newline chars (\n), that means that FNR is equivalent 
    # to "line number in this file".
    line_num = FNR
    number_of_fields = NF # for this one record only
    printf "This line (#%u) matches regex \"/Jan/\": %s\n", line_num, current_line
    printf "The 4th field, or column, in this line is \"%u\".\n", $4
    printf "The last field, or column, in this line is \"%u\".\n", $number_of_fields
    printf "The number of fields in this line is \"%u\".\n", number_of_fields
}

# You can also match variables explicitly like this. Read the tilde (~) as "if the thing on 
# the left contains a match for the regular expression on the right, then perform the action 
# in the curly braces { } below."
current_line ~ /Feb/ {
    print "***Feb***: "current_line
    print "         : "$0 # Just proving that $0 is equal to `current_line` right now
}

{
    # Lets practice some if/else statments. 
    # Remember, `$0` could be used in place of "current_line" below if we wanted, since they are 
    # the same thing. 
    line_num = FNR
    if (line_num % 2 == 0) {
        printf "%-4u: This line is EVEN: %s\n", line_num, current_line
    }
    else if (current_line ~ /^Aug/) {
        # I know that the input file has an "Aug" that begins on line 35, so this should work :)
        printf "%-4u: This line is ODD ***and begins with \"Aug\"***: %s\n", line_num, current_line
    }
    else {
        printf "%-4u: This line is ODD: %s\n", line_num, current_line
    }
}

{
    # Flow control:
    # The "next" keyword is a special keyword that skips the rest of the rules for this record.
    # Since this rule matches ALL records, no rules below here will ever be executed.
    # Read about the `next` statement here:
    # https://www.gnu.org/software/gawk/manual/html_node/Next-Statement.html
    next
}

{
    # This will never run because the `next` statement above skips over it every time
    print "THIS ACTION WILL NEVER BE RUN, SO THIS WILL NEVER BE PRINTED."
}

# END is a special matcher that matches only one single time at the very end of the 
# program. See here: 
# https://www.gnu.org/software/gawk/manual/html_node/Using-BEGIN_002fEND.html
END {
    print "END OF AWK PROGRAM"
}

# END OF THE AWK PROGRAM
' \
"$@"
