#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 17 Feb. 2022

# Investigate the mysterious extra space on each newline after using `echo -e`

# keywords: (keywords to easily grep or ripgrep in this repo for this program and what it teaches)

# Check this script with: `shellcheck print_and_run.sh`

# Run command:
#       ./hello_world_basic.sh

# References:
# 1. See: https://stackoverflow.com/q/23929235/4561887

echo "OUTSIDE A FUNCTION"

text="this is line one\n
this is line two\n
this is line three"
echo -e $text
echo "-----------"
echo -e "$text"
printf "======================\n\n"

text="this is line one\n \
this is line two\n \
this is line three"
echo -e $text
echo "-----------"
echo -e "$text"
printf "======================\n\n"

text="this is line one\n\
this is line two\n\
this is line three"
echo -e $text
echo "-----------"
echo -e "$text"
printf "======================\n\n"

text=("this is line one\n"\
"this is line two\n"\
"this is line three")
echo -e ${text[@]}
echo "-----------"
echo -e "${text[@]}"
printf "======================\n\n"

print_stuff() {
    echo "INDENTED IN A FUNCTION"

    text="this is line one\n
    this is line two\n
    this is line three"
    echo -e $text
    echo "-----------"
    echo -e "$text"
    printf "======================\n\n"

    text="this is line one\n \
    this is line two\n \
    this is line three"
    echo -e $text
    echo "-----------"
    echo -e "$text"
    printf "======================\n\n"

    text="this is line one\n\
        this is line two\n\
        this is line three"
    echo -e $text
    echo "-----------"
    echo -e "$text"
    printf "======================\n\n"

    text=("this is line one\n"\
    "this is line two\n"\
    "this is line three")
    echo -e ${text[@]}
    echo "-----------"
    echo -e "${text[@]}"
    printf "======================\n\n"

    # THIS IS IT! IT'S LIKE PYTHON'S text.dedent() func
    # https://stackoverflow.com/questions/37888872/equivalent-of-pythons-textwrap-dedent-in-bash
    text=("this is line one"
          "this is line two"
          "this is line three")
    printf "%s\n" ${text[@]}
    echo "-----------"
    printf "%s\n" "${text[@]}"
    printf "======================\n\n"

    text=("this is line one\n"\
          "this is line two\n\n"\
          "this is line three\n")
    printf ${text[*]}
    echo "-----------"
    printf "${text[*]}"
    printf "======================\n\n"

    text=("this is line one
           this is line two
           this is line three\n")
    printf ${text[*]}
    echo "-----------"
    printf "${text[*]}"
    # `text` gets passed in by reference as a regular bash "indexed" array
    dedent text
    # `text` has now become a regular string
    printf "$text"
    # printf "======================\n\n"
}

# # works!
# dedent() {
#     echo "dedent:"
#     local -n text_array_reference="$1"
#     local t="$(echo "${text_array_reference[*]}" | sed 's/^[[:space:]]*//')"
#     printf "$t"
# }

# works!
dedent() {
    echo "dedent:"
    local -n reference="$1"
    reference="$(echo "${reference[*]}" | sed 's/^[[:space:]]*//')"
    printf "$reference"
}

print_stuff


# FINAL DEMO

# BEGIN

dedent_and_stringify() {
    echo "dedent_and_stringify:"
    local -n reference="$1"
    reference="$(echo "${reference[*]}" | sed 's/^[[:space:]]*//')"
}

text=("this is line one
       this is line two
       this is line three\n")
# `text` gets passed in by reference as a regular bash "indexed" array
dedent_and_stringify text
# `text` has now become a regular string
printf "$text"

# END



# FINAL DEMO

# BEGIN

dedent_and_stringify2() {
    echo "dedent_and_stringify2:"
    local -n reference="$1"
    reference="$(echo "$reference" | sed 's/^[[:space:]]*//')"
}

text="this is line one
      this is line two
      this is line three\n"
# `text` gets passed in by reference as a regular bash "indexed" array
dedent_and_stringify2 text
# `text` has now become a regular string
printf "$text"

# END


###### WIP: DON'T ECHO IT NOR PRINT IT TO pipe it to sed! Rather, "herestring" it over to `sed`
# using the `<<<` operator! See:
# 1. https://github.com/koalaman/shellcheck/wiki/SC2206
# 2. https://stackoverflow.com/questions/7950268/what-does-the-bash-operator-i-e-triple-less-than-sign-mean
# 3. Add an answer here!: https://stackoverflow.com/questions/24628076/convert-multiline-string-to-array <==========********************
#    1. this works but is long and not as recommended (the existing main answer) since it's long and since it doesn't use quotes (per shellcheck)
#    1. this works and is shorter (set IFS on same line) and is not recommended by shellcheck since it doesn't use quotes
#    1. this works (mapfile) and is recommended
#    1. this works (read -r -a) and is recommended
dedent() {
    local -n reference="$1"
    reference="$(printf "$reference" | sed 's/^[ ]*//g')"
}

# do this
text="this is line one
      this is line two
      this is line three\n"
# OR this (same thing)-------nope
text="this is line one
      this is line two
      this is line three


      "


echo "BEFORE DEDENT:"
printf "$text"
echo ""

dedent text  # `text` is passed by reference

echo "AFTER DEDENT:"
printf "$text"
echo ""


text="this is line one\n\
this is line two\n\
this is line three"

echo -e "$text"


# SAMPLE OUTPUT:
#
#       eRCaGuy_hello_world/bash$ ./hello_world_basic.sh a b c d e f g
#       a b c d e f g
