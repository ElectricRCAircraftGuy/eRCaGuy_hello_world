#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# Jan. 2026
#
# Resize an svg file to a given width in pixels, maintaining aspect ratio.
# The new file name will have the suffix "_resized.svg".
#
# STATUS: Done and works!
#
# Install:
# ```bash
# cd path/to/eRCaGuy_hello_world
# chmod +x bash/resize_svg.sh
# mkdir -p ~/bin
# ln -sir $(pwd)/bash/resize_svg.sh ~/bin/resize_svg
# ```
#
# USAGE:
# `resize_svg <svg_file> <width>`
#
# Example:
# `resize_svg "diagram.svg" 600`


# Function to resize SVG to specified width in-place
# Usage:   `resize_svg <svg_file> <width>`
# Example: `resize_svg "diagram.svg" 600`
resize_svg() {
    # Read input arguments
    local svg_file="$1"
    local width="$2"

    echo "Resizing $svg_file to ${width}px width"
    # Set width attribute
    sed -i "s|width=\"[^\"]*\"|width=\"$width\"|" "$svg_file"
    # Remove height attribute to maintain aspect ratio
    sed -i "s|height=\"[^\"]*\"||" "$svg_file"
}

main() {
    local svg_file="$1"
    local width="$2"

    if [[ -z "$svg_file" || -z "$width" ]]; then
        echo "Usage: $0 <svg_file> <width>"
        exit 1
    fi

    # Create a copy of the original SVG file with "_resized" suffix
    local resized_svg_file="${svg_file%.svg}_resized.svg"
    cp "$svg_file" "$resized_svg_file"

    # Resize the copied SVG file
    # - Note: this calls the function defined above, NOT a script or executable by this name that
    #   may be in your PATH.
    resize_svg "$resized_svg_file" "$width"
}

# Determine if the script is being sourced or executed (run).
# See:
# 1. "eRCaGuy_hello_world/bash/if__name__==__main___check_if_sourced_or_executed_best.sh"
# 1. My answer: https://stackoverflow.com/a/70662116/4561887
if [ "${BASH_SOURCE[0]}" = "$0" ]; then
    # This script is being run.
    __name__="__main__"
else
    # This script is being sourced.
    __name__="__source__"
fi

# Only run `main` if this script is being **run**, NOT sourced (imported).
# - See my answer: https://stackoverflow.com/a/70662116/4561887
if [ "$__name__" = "__main__" ]; then
    main "$@"
fi
