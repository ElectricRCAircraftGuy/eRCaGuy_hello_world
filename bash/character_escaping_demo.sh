#!/bin/bash

# This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# GS
# 2 Aug. 2021
# See my ans. here: https://stackoverflow.com/a/65878993/4561887

CMD="gs_set_title"

# 1. 1st technique: escape the $ symbol with a backslash (\) so it doesn't
# run and expand the command following it
echo "$CMD '\$(basename \"\$(pwd)\")'"

# 2. 2nd technique (does the same thing in a different way): escape the
# $ symbol using single quotes around it, and the single quote (') symbol
# using double quotes around it
echo "$CMD ""'"'$(basename "$(pwd)")'"'"



# SAMPLE OUTPUT:

# eRCaGuy_hello_world/bash$ ./character_escaping_demo.sh
# gs_set_title '$(basename "$(pwd)")'
# gs_set_title '$(basename "$(pwd)")'
