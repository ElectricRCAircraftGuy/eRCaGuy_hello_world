This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Bash libraries

These files are bash libraries which are intended to be run directly in order to run their internal unit tests, _or_ imported (sourced) anywhere in order to use them at the command-line or in your own Bash programs!


# Installation 

```bash
# make a "libs_bash" dir in your home dir
mkdir -p ~/libs_bash

# symlink this entire "eRCaGuy_hello_world/bash/libraries" dir into it
cd path/to/eRCaGuy_hello_world/bash
ln -si "$(pwd)/libraries" ~/libs_bash/

# Now run this whole block at once, one time, to add this new `BASHLIBS`
# variable (which I am inventing right now) to the bottom of your ~/.bashrc
# file
cat << "EOF" >> ~/.bashrc

# Added by eRCaGuy_hello_world: 
# https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
if [ -d "$HOME/libs_bash/libraries" ] ; then
    export BASHLIBS="$HOME/libs_bash/libraries"
fi
EOF

# check your new variable; you should see NO OUTPUT YET
echo "$BASHLIBS"

# re-source your terminal to receive the updated above
. ~/.profile

# check your new variable again; you should see this as the output:
#       /home/gabriel/libs_bash/libraries
echo "$BASHLIBS"
```

Done!

If you take a look at the bottom of your `~/.bashrc` file, you will now see this:
```bash
# Added by eRCaGuy_hello_world: 
# https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
if [ -d "$HOME/libs_bash/libraries" ] ; then
    export BASHLIBS="$HOME/libs_bash/libraries"
fi

```


# Usage

To learn what it means to `source` (`.`) or `export` a file or variable in Bash, see my answer here: [`source` (`.`) vs `export` (and also some file lock [`flock`] stuff at the end)](https://stackoverflow.com/a/62626515/4561887).

You can now import (source, via the `.` operator) any of your Bash libraries stored inside `~/libs_bash/libraries`, like this. Run this command either _directly in your terminal_, _or_ in any Bash program in which you'd like to use it!

```bash
# Source (import) the `floating_point_math.sh` Bash library
. ~/libs_bash/libraries/floating_point_math.sh
# OR (better; same thing now)
. "$BASHLIBS/floating_point_math.sh"

# Now use the functions within that library
add 1.2 2.3  # result is 3.5
```
