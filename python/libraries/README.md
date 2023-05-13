This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Python libraries

This folder contains my Python libraries which I consider good enough to use repeatedly across my projects, so I want to be able to import them easily.

Someday I'll figure out how to add them to `pip` so you can install them with `pip3 install my_library_name` or whatever, but for now you and I can install them manually by following the simple steps below.


# Installation 

These steps are similar to those found in [../../bash/libraries/README.md](../../bash/libraries/README.md#installation).

```bash
# make a "libs_python" dir in your home dir
mkdir -p ~/libs_python

# symlink this entire "eRCaGuy_hello_world/python/libraries" dir into it
cd path/to/eRCaGuy_hello_world/python
ln -si "$(pwd)/libraries" ~/libs_python/

# Now run this whole block at once, one time, to add the following chunk of code
# to the bottom of your ~/.bashrc file. This adds the new directory above to
# your `PYTHONPATH` environment variable, which is how Python knows where to
# look for packages and modules you import in your Python programs.
# START OF BLOCK TO RUN ALL AT ONCE
cat << "EOF" >> ~/.bashrc

# Added by eRCaGuy_hello_world for importing Python libraries: 
# https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
if [ -d "$HOME/libs_python/libraries" ] ; then
    export PYTHONPATH="$HOME/libs_python/libraries:$PYTHONPATH"
fi
EOF
# END OF BLOCK TO RUN ALL AT ONCE

# check your `PYTHONPATH` variable; you should *not* see your new `libs_python`
# dir in it yet
echo "$PYTHONPATH"

# re-source your terminal to receive the updates above which are now inside
# your ~/.bashrc file
. ~/.profile

# check your new variable again; you should see the equivalent of this at the
# start of its output, but for your username: 
# `/home/gabriel/libs_python/libraries:`
echo "$PYTHONPATH"
```

Done!

If you take a look at the bottom of your `~/.bashrc` file, you will now see this:
```bash
# Added by eRCaGuy_hello_world for importing Python libraries: 
# https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world
if [ -d "$HOME/libs_python/libraries" ] ; then
    export PYTHONPATH="$HOME/libs_python/libraries:$PYTHONPATH"
fi
```


# Usage

When importing _packages_ (groups of .py files within a folder, including subfolders) or _modules_ (standalone .py files) into your Python program so long as they reside in this `~/libs_python/libraries` directory, which is a symlink to the `eRCaGuy_hello_world/python/libraries` directory. This is because that directory is now in your `PYTHONPATH` environment variable, which is one of the places where Python will look for such things.

Example:

```bash
# Import my `import_helper.py` module
import import_helper
```
