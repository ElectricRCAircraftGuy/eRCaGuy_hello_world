<!--
GS
12 May 2023

I'm going to post this in a new Q&A on Stack Overflow.

"How do you write, import, and use libraries in Bash?"
My Q&A: https://stackoverflow.com/a/76241159/4561887

Update: My Q&A was almost instantly downvoted and closed. I moved my answer to
here instead, where it fits better:
https://stackoverflow.com/a/76241268/4561887
-->

I'm familiar with Python. It has packages and modules you can `import`. I also know that C and C++ have libraries you can `#include`. 

So, how do you write, import, and use libraries in Bash? 

---

<sub>This is a [Q&A-style question](https://stackoverflow.blog/2011/07/01/its-ok-to-ask-and-answer-your-own-questions/) where I'll also propose an answer to my own question. I don't see any really good Q&As on this topic yet.</sub>

--------

Here's a really beautiful, almost Python-like style I've come with over the years for writing and using Bash libraries. Bash is a beautiful "glue"-type language which allows you to easily tie together executables from many languages. Considering how long Bash has been around, I'm not sure why the below style isn't more popular, but perhaps it hasn't been thought of or used this way before. So, here goes. I think you'll find it really useful.

You can also see a general starting point I use for all of my bash scripts in my [hello_world_best.sh](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/hello_world_best.sh) file in my [eRCaGuy_hello_world](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world) repo. 

You can see a full library example in [floating_point_math.sh](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/floating_point_math.sh).

**[library_basic_example.sh](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/library_basic_example.sh):**

```bash
#!/usr/bin/env bash

RETURN_CODE_SUCCESS=0
RETURN_CODE_ERROR=1

# Add your library functions here. Ex:

my_func1() {
    echo "100.1"
}

my_func2() {
    echo "200"
}

my_func3() {
    echo "hello world"
}

# Note: make "private" functions begin with an underscore `_`, like in Python,
# so that users know they are not intended for use outside this library.

# Assert that the two input argument strings are equal, and exit if they are not
_assert_eq() {
    if [ "$1" != "$2" ]; then
        echo "Error: assertion failed. Arguments not equal!"
        echo "  arg1 = $1; arg2 = $2"
        echo "Exiting."
        exit $RETURN_CODE_ERROR
    fi
}

# Run some unit tests of the functions found herein
_test() {
    printf "%s\n\n" "Running tests."

    printf "%s\n" "Running 'my_func1'"
    result="$(my_func1)"
    printf "%s\n\n" "result = $result"
    _assert_eq "$result" "100.1"

    printf "%s\n" "Running 'my_func2'"
    result="$(my_func2)"
    printf "%s\n\n" "result = $result"
    _assert_eq "$result" "200"

    printf "%s\n" "Running 'my_func3'"
    result="$(my_func3)"
    printf "%s\n\n" "result = $result"
    _assert_eq "$result" "hello world"

    echo "All tests passed!"
}

main() {
    _test
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

# Code entry point. Only run `main` if this script is being **run**, NOT
# sourced (imported).
# - See my answer: https://stackoverflow.com/a/70662116/4561887
if [ "$__name__" = "__main__" ]; then
    main "$@"
fi
```


## Run the library to run its unit tests

Now, make the file executable. Running it will run its internal unit tests:
```bash
# make it executable
chmod +x library_basic_example.sh

# run it
./library_basic_example.sh
```

Example run command and output:
```bash
eRCaGuy_hello_world$ bash/library_basic_example.sh 
Running tests.

Running 'my_func1'
result = 100.1

Running 'my_func2'
result = 200

Running 'my_func3'
result = hello world

All tests passed!
```


## Import (source) the library

To import a Bash library, you "source" it with the `source` or `.` (better) command. Read more about that in my answer here: [`source` (`.`) vs `export` (and also some file lock [`flock`] stuff at the end)](https://stackoverflow.com/a/62626515/4561887).

#### 1. Use a manually-set import path

You can do this either in a bash terminal directly, or in your own bash script. Try it right now inside your own terminal!:
```bash
source "path/to/library_basic_example.sh"

# Or (better, since it's Posix-compliant)
. "path/to/library_basic_example.sh"
```

Once you source (import) the Bash library, you get access to call its functions directly. Here's a full example run and output, showing that I can do function calls like `my_func1`, `my_func2`, etc, right inside my terminal once I've sourced (imported) this Bash library!:
```bash
eRCaGuy_hello_world$ . bash/library_basic_example.sh
eRCaGuy_hello_world$ my_func1
100.1
eRCaGuy_hello_world$ my_func2
200
eRCaGuy_hello_world$ my_func3
hello world
eRCaGuy_hello_world$ _test
Running tests.

Running 'my_func1'
result = 100.1

Running 'my_func2'
result = 200

Running 'my_func3'
result = hello world

All tests passed!
```

#### 2. Use a `BASHLIBS` environment variable to make importing your Bash libraries easier

You can source your bash libraries from _any path_. But, an environment variable, such as `BASHLIBS`, makes it easier. Add this to the bottom of your `~/.bashrc` file:
```bash
if [ -d "$HOME/libs_bash/libraries" ] ; then
    export BASHLIBS="$HOME/libs_bash/libraries"
fi
```

Now, you can symlink your Bash libraries into that directory, like this:

```bash
# symlink my `library_basic_example.sh` file into the `~/libs_bash/libraries`
# dir
mkdir -p ~/libs_bash/libraries
cd path/to/dir_where_my_library_file_of_interest_is_stored
# make the symlink
ln -si "$(pwd)/library_basic_example.sh" ~/libs_bash/libraries/
```

Now that a symlink to my `library_basic_example.sh` file is stored inside `~/libs_bash/libraries/`, and the `BASHLIBS` environment variable has been set and `export`ted to my environment, I can import my library into any Bash terminal or script I run within the terminal, like this:
```bash
. "$BASHLIBS/library_basic_example.sh"
```

#### 3. Using relative import paths

This is really beautiful and powerful. Check this out!

Let's say you have the following directory layout:
```
dir1/
    my_lib_1.sh

    dir2/
        my_lib_2.sh
        my_script.sh
    
        dir3/
            my_lib_3.sh
```

The above representation could easily exist in a large program or tool-chain you have set up with a scattered assortment of runnable scripts and libraries, especially when sharing (sourcing/importing) code between your various bash scripts, no matter where they lie. 

Imagine you have these constraints/requirements:
1. The entire directory structure above is all stored inside a single GitHub repo.
1. You need anyone to be able to `git clone` this repo and just have all scripts and imports and things _magically work_ for everybody!
    1. This means you need to use _relative imports_ when importing your bash scripts into each other.
1. You are going to run `my_script.sh`, for example.
1. You must be able to call `my_script.sh` _from anywhere_, meaning: you should be able to be `cd`ed into _any_ directory in your entire file system at the time you call this script to run.
1. `my_script.sh` must use relative imports to import `my_lib_1.sh`, `my_lib_2.sh`, and `my_lib_3.sh`. 

Here's how! Basically, we are going to find the path _to the script being run_, and then use that path as a relative starting point to the other scripts around this script!

Read my full answer on this for more details: [How to obtain the _full file path_, _full directory_, and _base filename_ of any script being _run_ OR _sourced_...even when the called script is called from within another bash function or script, or when nested sourcing is being used!](https://stackoverflow.com/a/60157372/4561887). 


Full example:

my_script.sh:

```bash
#!/usr/bin/env bash

# Get the path to the directory this script is in.
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[-1]}")"
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"

# Now, source the 3 Bash libraries of interests, using relative paths to this
# script!
. "$SCRIPT_DIRECTORY/../my_lib_1.sh"
. "$SCRIPT_DIRECTORY/my_lib_2.sh"
. "$SCRIPT_DIRECTORY/dir3/my_lib_3.sh"

# Now you've sourced (imported) all 3 of those scripts!
```

That's it! Super easy if you know the commands! 

Can Python do this? No, not natively at least. Bash is _much easier_ than Python in this regard! Python doesn't use filesystem paths directly when `import`ing. It's [much more complicated and convoluted than that](https://stackoverflow.com/q/16981921/4561887). But, I'm working on an `import_helper.py` Python module to make this type of thing easy in Python too. I'll publish it shortly as well.


## Going further

1. See my full and really-useful Bash floating point library in my [eRCaGuy_hello_world](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world) repo here: [floating_point_math.sh](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/floating_point_math.sh).
1. See some alternative notes of mine on Bash library installation and usage in my readme here: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/tree/master/bash/libraries
