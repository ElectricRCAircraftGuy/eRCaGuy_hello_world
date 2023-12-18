#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 17 Dec. 2023
#
# Practice doing 2D, 3D, etc. multidimensional arrays in Bash. Bash doesn't support this natively,
# and has no concept of "arrays of arrays", but that doesn't matter. As can be done in any language,
# including C (see Example 3 in my answer here: https://stackoverflow.com/a/67814330/4561887), you
# can just use a 1D array for an ND array. 
#
# STATUS: wip

# keywords to easily grep or ripgrep in this repo for this program and what it teaches
#
# KEYWORDS:

# Check this script with:
#
##      shellcheck bash/hello_world_best.sh
#
# Run command:
#
#       bash/hello_world_best.sh
#
# Source (import) command to get access to any functions herein:
# [my answer] https://stackoverflow.com/a/62626515/4561887):
#
#       . bash/hello_world_best.sh

# References:
# 1. Example 3 in my answer here: https://stackoverflow.com/a/67814330/4561887
# 1.

# 2D array of 4 rows and 3 columns
ARRAY2D_NUM_COLS="3"
array2d=(
    "0,0" "0,1" "0,2"
    "1,0" "1,1" "1,2"
    "2,0" "2,1" "2,2"
    "3,0" "3,1" "3,2"
)

# 3D array of 3 pages of 4 rows and 3 columns each
ARRAY3D_NUM_COLS="3"
ARRAY3D_NUM_ROWS="4"
array3d=(
    # page 0
    "0,0,0" "0,0,1" "0,0,2"
    "0,1,0" "0,1,1" "0,1,2"
    "0,2,0" "0,2,1" "0,2,2"
    "0,3,0" "0,3,1" "0,3,2"

    # page 1
    "1,0,0" "1,0,1" "1,0,2"
    "1,1,0" "1,1,1" "1,1,2"
    "1,2,0" "1,2,1" "1,2,2"
    "1,3,0" "1,3,1" "1,3,2"
    
    # page 2
    "2,0,0" "2,0,1" "2,0,2"
    "2,1,0" "2,1,1" "2,1,2"
    "2,2,0" "2,2,1" "2,2,2"
    "2,3,0" "2,3,1" "2,3,2"
)

array2d_get_num_cols() {
    echo "$ARRAY2D_NUM_COLS"
}

array2d_get_num_rows() {
    array2d=("$@")
    num_elements="${#array2d[@]}"
    # echo "num_elements = $num_elements"  # debugging
    num_rows=$(( $num_elements / $(array2d_get_num_cols) ))
    echo "$num_rows"
}

array3d_get_num_cols() {
    echo "$ARRAY3D_NUM_COLS"
}

array3d_get_num_rows() {
    echo "$ARRAY3D_NUM_ROWS"
}

array3d_get_num_pages() {
    array3d=("$@")
    num_elements="${#array3d[@]}"
    num_rows="$(array3d_get_num_rows)"
    num_cols="$(array3d_get_num_cols)"
    num_pages=$(( $num_elements / ($num_rows * $num_cols) ))
    echo "$num_pages"
}

array2d_print() {
    array2d=("$@")
    num_rows="$(array2d_get_num_rows "${array2d[@]}")"
    num_cols="$(array2d_get_num_cols)"

    for ((row=0; row<num_rows; row++)); do
        for ((col=0; col<num_cols; col++)); do
            i=$(( $row*$num_cols + $col ))
            echo -n "${array2d[$i]} "
        done
        echo "" # new line after each row
    done
}

array3d_print() {
    array3d=("$@")
    num_rows="$(array3d_get_num_rows)"
    num_cols="$(array3d_get_num_cols)"
    num_pages="$(array3d_get_num_pages "${array3d[@]}")"
    
    for ((page=0; page<num_pages; page++)); do
        echo "Page $page:"

        for ((row=0; row<num_rows; row++)); do
            for ((col=0; col<num_cols; col++)); do
                i=$(( $page*$num_rows*$num_cols + $row*$num_cols + $col ))
                echo -n "${array3d[$i]} "
            done
            echo "" # new line after each row
        done
        echo "" # extra new line after each page
    done
}

# Obtain an element from a 2D array given its row and column.
# Call format:
#   array2d_get_element <row> <col> <array2d>
# Example:
#   array2d_get_element 2 1 "${array2d[@]}"
array2d_get_element() {
    row="$1"
    col="$2"
    # slice off the first 2 args and store the rest as the array
    shift 2
    array2d=("$@")
    
    num_cols="$(array2d_get_num_cols)"
    i=$(( $row*$num_cols + $col ))
    echo "${array2d[$i]}"
}

# Obtain an element from a 3D array given its page, row, and column.
# Call format:
#   array3d_get_element <page> <row> <col> <array3d>
# Example:
#   array3d_get_element 1 2 1 "${array3d[@]}"
array3d_get_element() {
    page="$1"
    row="$2"
    col="$3"
    # slice off the first 3 args and store the rest as the array
    shift 3
    array3d=("$@")
    
    num_rows="$(array3d_get_num_rows)"
    num_cols="$(array3d_get_num_cols)"
    i=$(( $page*$num_rows*$num_cols + $row*$num_cols + $col ))
    echo "${array3d[$i]}"
}

# =========================
# Test code
# =========================

echo ""

echo "array2d has:"
echo "  ${#array2d[@]} elements"
echo "  $(array2d_get_num_rows "${array2d[@]}") rows"
echo "  $(array2d_get_num_cols) columns"
echo ""
echo "array2d_print:"
array2d_print "${array2d[@]}"
echo ""

echo "array3d has:"
echo "  ${#array3d[@]} elements"
echo "  $(array3d_get_num_rows) rows"
echo "  $(array3d_get_num_cols) columns"
echo "  $(array3d_get_num_pages "${array3d[@]}") pages"
echo ""
echo "array3d_print:"
array3d_print "${array3d[@]}"
echo ""



# SAMPLE OUTPUT:
#
# 1) WHEN RUN
#
#       eRCaGuy_hello_world$ bash/hello_world_best.sh
#       Running main.
#
#
# 2) WHEN SOURCED (no output, but it brings in all functions herein so you can use them!)
#
#       eRCaGuy_hello_world$ . bash/hello_world_best.sh
