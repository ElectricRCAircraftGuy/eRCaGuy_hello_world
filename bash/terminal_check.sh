#!/usr/bin/env bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Gabriel Staples
# Sep. 2025
# 
# Published here too: https://stackoverflow.com/a/78480875/4561887


# Linux terminal
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OPERATING_SYSTEM="Linux: $(lsb_release -d | cut -f2-)"
# MSYS2: Git Bash terminal
elif [[ "$OSTYPE" == "msys" ]]; then 
    OPERATING_SYSTEM="Windows: MSYS2: Git Bash terminal $MSYSTEM: $(uname -a)"
# MSYS2: Normal MSYS2 terminal
elif [[ "$OSTYPE" == "cygwin" ]]; then 
    OPERATING_SYSTEM="Windows: MSYS2: Cygwin terminal $MSYSTEM: $(uname -a)"
fi

echo "OPERATING_SYSTEM = $OPERATING_SYSTEM"
