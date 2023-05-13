This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Python libraries

This folder contains my Python libraries (both _packages_ and _modules_--see more on both of these below) which I consider good enough to use repeatedly across my projects, so I want to be able to import them easily.

Someday I'll figure out how to add them to `pip` so you can install them with `pip3 install my_library_name` or whatever, but for now you and I can install them manually by following the simple steps below.


## References

1. \*\*\*\*\* [Stack Overflow: Relative imports in Python 3](https://stackoverflow.com/a/16985066/4561887) - my `my_package` code herein is largely modified from @Aya's excellent answer here!
1. https://docs.python.org/3/reference/import.html
1. https://docs.python.org/3/reference/import.html#namespace-packages
1. [Stack Overflow: What is `__init__.py` for?](https://stackoverflow.com/q/448271/4561887)
1. What are the automatically-created `__pycache__` directories in Python?
    
    Answer from Bing's GPT-4, via the Microsoft Edge browser:

    > `__pycache__` is a directory that is created by the Python interpreter when it imports a module. It contains the compiled bytecode of the module, which can be used to speed up subsequent imports of the same module¹. 
    > 
    > The bytecode is platform-independent and is generated from the source code of the module. When you import a module, Python checks if there is a corresponding `.pyc` file in the `__pycache__` directory. If there is, and the timestamp on the `.pyc` file is newer than that on the corresponding `.py` file, Python loads the bytecode from the `.pyc` file instead of recompiling the source code².
    > 
    > I hope this helps! Let me know if you have any other questions.
    > 
    > Source: Conversation with Bing, 5/7/2023  
    > (1) What is __pycache__? - w3docs.com. https://www.w3docs.com/snippets/python/what-is-pycache.html.
    > (2) Where is my _pycache_ folder and .pyc byte code files?. https://stackoverflow.com/questions/24291779/where-is-my-pycache-folder-and-pyc-byte-code-files.
    > (3) PEP 3147 – PYC Repository Directories | peps.python.org. https://peps.python.org/pep-3147/.
    > (4) python - What is __pycache__? - Stack Overflow. https://stackoverflow.com/questions/16869024/what-is-pycache.
    > (5) python - Python3 project remove __pycache__ folders and .pyc files .... https://stackoverflow.com/questions/28991015/python3-project-remove-pycache-folders-and-pyc-files.

    See also my comment under this answer, and this answer, here: https://stackoverflow.com/questions/16869024/what-is-pycache/48143622#comment134373559_48143622


## Packages and modules

1. What are _packages_ and _modules_ in Python?
    
    A _module_ is a _single Python file_ intended to be imported into another Python file in order to use its functions, variables, or other objects inside of it. 

    Both packages and modules must either be stored in a directory within your [`PYTHONPATH` environment variable](https://docs.python.org/3/using/cmdline.html#envvar-PYTHONPATH), _or_ in the same directory as your Python script importing it (notice how `my_package/`, below, is in the same directory as `main.py`). If your module is named `my_module.py`, you would import it with `import my_module`. 

    A _package_ is a _filesystem folder_ containing a conglomeration of Python files and modules, usually working together as a single "packaged library" program. If you have this file and folder layout in your Python package:

    ```
    my_dir/
        main.py
        
        my_package/
            my_module_1.py

            my_subpackage_1/
                my_module_2.py
        
            my_subpackage_2/
                my_module_3.py
    ```

    ...then you can say that `my_dir/main.py` is your main program, and everything within `my_package/` is package `my_package`. Inside `main.py`, for instance, you could have the following `import`s:
    ```py
    import my_package.my_module_1
    import my_package.my_subpackage_1.my_module_2
    import my_package.my_subpackage_2.my_module_3
    ```

    And, inside file `my_package/my_module_1.py`, you could have these imports:
    ```py
    import my_package.my_subpackage_1.my_module_2
    import my_package.my_subpackage_2.my_module_3
    ```

    The above imports inside `my_package/my_module_1.py` expect that your main program is up higher at `main.py`, however, and that _you will never call `my_package/my_module_1.py` as a runnable program directly, itslef._ There are ways to work around this however, as I discuss in my answer below:

    **TODO: [A detailed and practical look at the limitations of Python `import`s, and how to overcome them with filepath absolute and relative imports](TODO)**


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
