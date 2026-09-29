<!--
GS
Feb. 2020 to Sep. 2026

https://stackoverflow.com/a/60157372/4561887
-->

For Python, see my other answer here: [How to get the path and name of the Python file that is currently executing?](https://stackoverflow.com/a/74800814/4561887)

For Bash, see below:


## Quick Summary

If in a hurry, jump straight down to the example in this answer which is marked with `[Best and most-versatile "one-size-fits-all" approach]`, and use that. 

---

The simplest answer is to put this at the top of every top-level Bash script: 

```bash
#!/usr/bin/env bash

# See: https://stackoverflow.com/a/60157372/4561887
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
SCRIPT_DIR="$(dirname "$FULL_PATH_TO_SCRIPT")"
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"

# The rest of your script goes here...
```

**...but if your script gets sourced from another script and you want to get the path of that higher-level script to not override and change its global variables like `SCRIPT_DIR`**, it gets complicated. 

`${BASH_SOURCE[0]}` identifies the file containing the code currently executing, whether that file was run or sourced, and you can use it when a script or library needs its own path. Sourced scripts share the caller's shell state, however, so lower-level libraries should take care to avoid overwriting caller globals such as `SCRIPT_DIR`.

Higher indices in the `BASH_SOURCE` array, like `${BASH_SOURCE[1]}` and `${BASH_SOURCE[2]}`, describe caller frames, not just source depth, so use them only when you intentionally need to inspect the caller. Function calls can add or duplicate frames.

Example:
```bash
# Current level: file defining the currently-executing code/function
${BASH_SOURCE[0]}
# Next caller frame: file containing the immediate call/source site
${BASH_SOURCE[1]}
# Next caller frame after that
${BASH_SOURCE[2]}  
# And so on through the active call/source stack
${BASH_SOURCE[3]}

# Etc...
```

You can also use negative indices to look backwards from the end of the `BASH_SOURCE` array, such as `${BASH_SOURCE[-1]}`, `${BASH_SOURCE[-2]}`, etc. 

For example:
```bash
# Oldest active source/call frame. 
# - When a script launches Bash, this is often that outer script. 
# - But in an **interactive shell**, it is not necessarily the top-level script.
${BASH_SOURCE[-1]}
```

Note that negative array indices are unavailable in older Bash releases.

So, to solve the above issues and not override upper-level global `SCRIPT_DIR`-type variables in lower-level, sourced scripts, unintentionally, **I have come up with these canonical scenarios for handling top-level Bash scripts and sourced Bash scripts, both inside and outside git repositories:**


## 1. My best quick summary

_Added 17 Sep. 2026_

This is my answer I reference the most I think. 

Here are some copy-paste blobs I now use all the time at the top of just about every bash script I ever write:

### 1.A. Architectural description

1. Top-level executable scripts own their own global state such as `SCRIPT_DIR` and `PROJECT_ROOT`.
1. Sourced libraries determine their own paths inside a short-lived function using local variables, then remove that helper function when done.
1. Every script uses `${BASH_SOURCE[0]}` to locate itself, independent of how deeply it was sourced.

This gives a clear ownership boundary between top-level scripts and sourced libraries:
1. Top-level script: owns global configuration.
1. Sourced libraries: own temporary path-discovery state only.
1. Variable flow is controlled and predictable:
    1. Global variables are set by top-level scripts (and can flow down to sourced library scripts, though unidirectional variable flow from the sourced library up to the top-level script is encouraged and supported).
    1. Sourcing a lower-level library in a top-level script brings variables into the top-level script. 
        1. It feels compact, modular, traceable, predictable, and unidirectional: like including library headers in C or C++ via `#include <header.h>`, or importing modules in Python via `import module`.
    1. Lower-level sourced libraries can be independently run and verified since they independently determine their own paths. 
    1. Variable flow does not confusingly flow into sourced libraries, get modified, and then flow back up to top-level scripts in a "pass-through"-like manner. 
    1. Instead, this pattern encourages and supports unidirectional and predictable variable flow from the sourced script up to the top-level script.
    1. Variables of top-level scripts are never unintentionally overridden by lower-level sourced libraries.

Here is how the wrapper pattern is implemented for sourced libraries:
```bash
# 1. Define the temporary function
_source_local_libraries_without_changing_global_variables() {
    local _SCRIPT_DIR
    # ...
    # derive paths and source dependencies
}
# 2. Call the temporary function
_source_local_libraries_without_changing_global_variables
# 3. Remove the temporary function
unset -f _source_local_libraries_without_changing_global_variables
```

This prevents the library's path-discovery implementation details from overwriting the caller's `SCRIPT_DIR`-style global variables, while still letting the lower-level library determine its own path, the path to the project root, and then use those paths to source other libraries if it needs to.

I think this is a beautiful architectural pattern for Bash and is about as clean and maintainable as it can get.

### 1.B. Implementation

#### 1.B.1. For _lower-level bash scripts that are sourced_--ex: bash libraries that source other libraries

For Bash scripts that are both sourced by higher-level scripts _and_ which optionally may source lower-level scripts themselves, **use `local` variables that won't override/overwrite the higher-level global ones when the lower-level script is sourced:**

1. If running a Bash script **from within a Git repository:**
    ```bash
    #!/usr/bin/env bash

    # Lower-level bash script to be run inside a Git repo:
    # - Get the full path to this script and its directory, as well as the 
    #   repo root, for Bash libraries that are both sourced and source other 
    #   libraries.
    # - See: https://stackoverflow.com/a/60157372/4561887
    _source_local_libraries_without_changing_global_variables() {
        local _FULL_PATH_TO_SCRIPT
        local _SCRIPT_DIR
        local _REPO_ROOT
        local _BASH_LIBS_DIR
        local _UPPER_REPO_ROOT
        local _UPPER_BASH_LIBS_DIR

        _FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
        _SCRIPT_DIR="$(dirname "$_FULL_PATH_TO_SCRIPT")"
        _REPO_ROOT="$(cd "$_SCRIPT_DIR" && git rev-parse --show-toplevel)"
        _BASH_LIBS_DIR="${_REPO_ROOT}/bash_libs"
        # If this file is inside a submodule and needs the superproject's
        # directories, here's how to obtain the upper repo root dir
        _UPPER_REPO_ROOT="$(cd "$_SCRIPT_DIR" && git rev-parse --show-superproject-working-tree)"
        _UPPER_BASH_LIBS_DIR="${_UPPER_REPO_ROOT}/bash_libs"

        # Now you can do your library imports (sourcing) here...
        # - NB: even though we use local variables for the paths, any sourced 
        #   file here can still define and override global variables, aliases, 
        #   shell options, and functions.
        . "${_BASH_LIBS_DIR}/my_library1.sh"
        . "${_BASH_LIBS_DIR}/my_library2.sh"
        . "${_UPPER_BASH_LIBS_DIR}/my_library3.sh"
        . "${_UPPER_BASH_LIBS_DIR}/my_library4.sh"
    }
    _source_local_libraries_without_changing_global_variables
    unset -f _source_local_libraries_without_changing_global_variables

    # The rest of your script goes here...
    ```

1. If running a Bash script **outside of a Git repository:** 

    **[Best and most-versatile "one-size-fits-all" approach]** If you are looking for a single approach to remember and copy-paste, that works in the most scenarios, this is it, use this one. It works both inside and outside of Git repositories, and inside lower-level Bash scripts or libraries that are sourced, as well as for upper-level bash scripts or libraries that source. 
    
    If you need a particular variable to be global, simply delete its `local` declaration, and as a convention, remove the leading underscore from its name. 
    
    ```bash
    #!/usr/bin/env bash

    # Lower-level bash script that can be run outside a Git repo:
    # - Get the full path to this script and its directory, as well as the 
    #   project root, for Bash libraries that are both sourced and source other 
    #   libraries.
    # - See: https://stackoverflow.com/a/60157372/4561887
    _source_local_libraries_without_changing_global_variables() {
        local _FULL_PATH_TO_SCRIPT
        local _SCRIPT_DIR
        local _PROJECT_ROOT
        local _BASH_LIBS_DIR

        _FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
        _SCRIPT_DIR="$(dirname "$_FULL_PATH_TO_SCRIPT")"
        _PROJECT_ROOT="$(realpath -s "$_SCRIPT_DIR/..")"  # manually set this
        _BASH_LIBS_DIR="${_PROJECT_ROOT}/bash_libs"

        # Now you can do your library imports (sourcing) here...
        # - NB: even though we use local variables for the paths, any sourced 
        #   file here can still define and override global variables, aliases, 
        #   shell options, and functions.
        . "${_BASH_LIBS_DIR}/my_library1.sh"
        . "${_BASH_LIBS_DIR}/my_library2.sh"
    }
    _source_local_libraries_without_changing_global_variables
    unset -f _source_local_libraries_without_changing_global_variables
    
    # The rest of your script goes here...
    ```

#### 1.B.2. For _higher-level bash scripts that are never sourced:_ use global variables

1. If running a Bash script **from within a Git repository:**
    ```bash
    #!/usr/bin/env bash

    # Higher-level bash script to be run inside a Git repo:
    # - Get the full path to this script and its directory, as well as the 
    #   repo root, for higher-level Bash scripts **that are never sourced.**
    # - See: https://stackoverflow.com/a/60157372/4561887
    FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
    SCRIPT_DIR="$(dirname "$FULL_PATH_TO_SCRIPT")"
    REPO_ROOT="$(cd "$SCRIPT_DIR" && git rev-parse --show-toplevel)"
    BASH_LIBS_DIR="${REPO_ROOT}/bash_libs"
    # If this file is inside a submodule and needs the superproject's
    # directories, here's how to obtain the upper repo root dir
    UPPER_REPO_ROOT="$(cd "$SCRIPT_DIR" && git rev-parse --show-superproject-working-tree)"
    UPPER_BASH_LIBS_DIR="${UPPER_REPO_ROOT}/bash_libs"

    # Now you can do your library imports (sourcing) here...
    . "${BASH_LIBS_DIR}/my_library1.sh"
    . "${BASH_LIBS_DIR}/my_library2.sh"
    . "${UPPER_BASH_LIBS_DIR}/my_library3.sh"
    . "${UPPER_BASH_LIBS_DIR}/my_library4.sh"

    # The rest of your script goes here...
    ```

1. If running a Bash script **outside of a Git repository:**
    ```bash
    #!/usr/bin/env bash

    # Higher-level bash script that can be run outside a Git repo:
    # - Get the full path to this script and its directory, as well as the 
    #   project root, for higher-level Bash scripts **that are never sourced.**
    # - See: https://stackoverflow.com/a/60157372/4561887
    FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
    SCRIPT_DIR="$(dirname "$FULL_PATH_TO_SCRIPT")"
    PROJECT_ROOT="$(realpath -s "$SCRIPT_DIR/..")"  # manually set this
    BASH_LIBS_DIR="${PROJECT_ROOT}/bash_libs"

    # Now you can do your library imports (sourcing) here...
    . "${BASH_LIBS_DIR}/my_library1.sh"
    . "${BASH_LIBS_DIR}/my_library2.sh"
    
    # The rest of your script goes here...
    ```

---

In your custom Bash libraries you source above, be sure to use my `if [ "$__name__" = "__main__" ]` Python-like trick I describe [in my answer here](https://stackoverflow.com/a/70662116/4561887) and in the links in the "Going further" section just below. 

#### References
1. `git rev-parse --show-superproject-working-tree`: [Is there a way to get the git root directory in one command?](https://stackoverflow.com/a/958125/4561887) - finds the upper-most root directory of the git repository, even if run from inside a git submodule.

#### Going further, to help you write good Bash libraries to import (source)
1. My personal website: [How do you write, import, use, and test libraries in Bash?](https://gabrielstaples.com/bash-libraries/)
1. My answer: [What is the bash equivalent to Python's `if __name__ == '__main__'`?](https://stackoverflow.com/a/70662116/4561887)
1. My answer: [What is the difference between source and export?](https://stackoverflow.com/a/62626515/4561887)


## 2. My older quick summary

Here is a full program:

**my_script.sh**:

```bash
#!/usr/bin/env bash

# This identifies the oldest active source/call frame, not necessarily this
# file.
# - It also requires a Bash version that supports negative array indices.
# - Using index 0 is generally better. 
# FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[-1]}")"

# OR, if you do NOT need it to work for **sourced** scripts too:
# FULL_PATH_TO_SCRIPT="$(realpath "$0")"

# [Generally prefer this, using index `0`, over the one above using 
# index `-1`]
#
# Use index `0` to identify this file, including when it is sourced or when
# code from this file executes inside one of its functions.
# - NB: this may fix the error `No such file or directory` when sourcing
#   this script from another script, where this script sources another
#   file based on the path to its own `FULL_PATH_TO_SCRIPT`, but so does
#   the other script sourcing this script, based on its own outer 
#   `FULL_PATH_TO_SCRIPT`. 
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"

# OR, add `-s` to NOT expand symlinks in the path:
# FULL_PATH_TO_SCRIPT="$(realpath -s "${BASH_SOURCE[0]}")"

SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"


# Going further: also obtain the filename with and without the extension
SCRIPT_FILENAME_STEM="${SCRIPT_FILENAME%.*}"        # withOUT the extension
SCRIPT_FILENAME_EXTENSION="${SCRIPT_FILENAME##*.}"  # JUST the extension

# debug prints of all of the above
echo "FULL_PATH_TO_SCRIPT:       $FULL_PATH_TO_SCRIPT"
echo "SCRIPT_DIRECTORY:          $SCRIPT_DIRECTORY"
echo "SCRIPT_FILENAME:           $SCRIPT_FILENAME"
echo "SCRIPT_FILENAME_STEM:      $SCRIPT_FILENAME_STEM"
echo "SCRIPT_FILENAME_EXTENSION: $SCRIPT_FILENAME_EXTENSION"
```

Mark your program above as executable:
```bash
chmod +x my_script.sh
```

Run it:
```bash
./my_script.sh
```

Example run command and output:
```
~/GS/dev/eRCaGuy_PathShortener$ ./my_script.sh 
FULL_PATH_TO_SCRIPT:       /home/gabriel/GS/dev/eRCaGuy_PathShortener/my_script.sh
SCRIPT_DIRECTORY:          /home/gabriel/GS/dev/eRCaGuy_PathShortener
SCRIPT_FILENAME:           my_script.sh
SCRIPT_FILENAME_STEM:      my_script
SCRIPT_FILENAME_EXTENSION: sh
```


## Other details


## How to obtain the _full file path_, _full directory_, and _base filename_ of any script being _run_ OR _sourced_...
...even when the called script is called from within another bash function or script, or when nested sourcing is being used!

For many cases, all you need to acquire is the full path to the script you just called. This can be easily accomplished using `realpath`. Note that `realpath` is part of **GNU coreutils**. If you don't have it already installed (it comes default on Ubuntu), you can install it with `sudo apt update && sudo apt install coreutils`.

**get_script_path.sh** (for the latest version of this script, see [get_script_path.sh][1] in my [eRCaGuy_hello_world][2] repo):

```bash
#!/bin/bash

# A. Obtain the full path, and expand (walk down) symbolic links
# A.1. `"$0"` works only if the file is **run**, but NOT if it is **sourced**.
# FULL_PATH_TO_SCRIPT="$(realpath "$0")"
# A.2. `"${BASH_SOURCE[0]}"` identifies this file whether it is sourced or run,
# including when a function defined in this file is executing this.
FULL_PATH_TO_SCRIPT="$(realpath "${BASH_SOURCE[0]}")"
# B.1. `"$0"` works only if the file is **run**, but NOT if it is **sourced**.
# FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS="$(realpath -s "$0")"
# B.2. Use the same current-file lookup while preserving symbolic links.
FULL_PATH_TO_SCRIPT_KEEP_SYMLINKS="$(realpath -s "${BASH_SOURCE[0]}")"

# You can then also get the full path to the directory, and the base
# filename, like this:
SCRIPT_DIRECTORY="$(dirname "$FULL_PATH_TO_SCRIPT")"
SCRIPT_FILENAME="$(basename "$FULL_PATH_TO_SCRIPT")"

# Now print it all out
echo "FULL_PATH_TO_SCRIPT = \"$FULL_PATH_TO_SCRIPT\""
echo "SCRIPT_DIRECTORY    = \"$SCRIPT_DIRECTORY\""
echo "SCRIPT_FILENAME     = \"$SCRIPT_FILENAME\""
```

**IMPORTANT note on _nested `source` calls_:** use `"${BASH_SOURCE[0]}"` when a file needs its own path. In a chain where `~/.bashrc` sources `~/.bash_aliases`, code executing from `~/.bash_aliases` sees `BASH_SOURCE[0]` as `~/.bash_aliases`. `BASH_SOURCE[-1]`, where supported, points toward the oldest active frame instead and can therefore identify `~/.bashrc` rather than the current file.

**Example command and output:**

1. _Running_ the script:
    ```bash
    ~/GS/dev/eRCaGuy_hello_world/bash$ ./get_script_path.sh 
    FULL_PATH_TO_SCRIPT = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
    SCRIPT_DIRECTORY    = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
    SCRIPT_FILENAME     = "get_script_path.sh"
    ```
2. _Sourcing_ the script with `. get_script_path.sh` or `source get_script_path.sh` (the result is the exact same as above because I used `"${BASH_SOURCE[0]}"` in the script instead of `"$0"`):
    ```bash
    ~/GS/dev/eRCaGuy_hello_world/bash$ . get_script_path.sh 
    FULL_PATH_TO_SCRIPT = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash/get_script_path.sh"
    SCRIPT_DIRECTORY    = "/home/gabriel/GS/dev/eRCaGuy_hello_world/bash"
    SCRIPT_FILENAME     = "get_script_path.sh"
    ```

If you use `"$0"` in the script instead of `"${BASH_SOURCE[0]}"`, you'll get the same output as above when _running_ the script, but this _undesired_ output instead when _sourcing_ the script:
```bash
~/GS/dev/eRCaGuy_hello_world/bash$ . get_script_path.sh 
FULL_PATH_TO_SCRIPT               = "/bin/bash"
SCRIPT_DIRECTORY                  = "/bin"
SCRIPT_FILENAME                   = "bash"
```

`"$BASH_SOURCE"` normally expands to the first element of the array, equivalent to `"${BASH_SOURCE[0]}"`. It continues to identify the file defining a currently executing function. Prefer the explicit array form because it makes the intended index clear.

**Difference between `realpath` and `realpath -s`:**

Note that `realpath` also successfully walks down symbolic links to determine and point to their targets rather than pointing to the symbolic link. If you do NOT want this behavior (sometimes I don't), then add `-s` to the `realpath` command above, making that line look like this instead:

```bash
# Obtain the full path, but do NOT expand (walk down) symbolic links; in
# other words: **keep** the symlinks as part of the path!
FULL_PATH_TO_SCRIPT="$(realpath -s "${BASH_SOURCE[0]}")"
```

This way, symbolic links are NOT expanded. Rather, they are left as-is, as symbolic links in the full path.

The code above is now part of my [eRCaGuy_hello_world](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world) repo in this file here: [bash/get_script_path.sh](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/get_script_path.sh). Reference and run this file for full examples both with and withOUT symlinks in the paths. See the bottom of the file for example output in both cases.


## References

1. [How to retrieve absolute path given relative](https://stackoverflow.com/a/14892459/4561887)

1. Taught me about the `BASH_SOURCE` variable: [Unix & Linux: determining path to sourced shell script](https://unix.stackexchange.com/a/4653/114401)

1. Explains that `BASH_SOURCE` is an array and how it relates to `FUNCNAME`. They use `"${BASH_SOURCE[${#BASH_SOURCE[@]} - 1]}
"`, however, which is equivalent to `"${BASH_SOURCE[-1]}"`, whereas I prefer to use `"${BASH_SOURCE[0]}"` in most cases, as described above: [Unix & Linux: determining path to sourced shell script](https://unix.stackexchange.com/a/153061/114401)

    They also state this important point. But, if this ever was the case in older versions of Bash, it is no longer the case:
    
    > Note that the commonly supplied answer `${BASH_SOURCE[0]}` won't work if you try to find the path from within a function.

1. `man bash` --> search for `BASH_SOURCE`:
    > **`BASH_SOURCE`**  
    >
    > An array variable whose members are the source filenames where the corresponding shell function names in the `FUNCNAME` array variable are defined. The shell function `${FUNCNAME[$i]}` is defined in the file `${BASH_SOURCE[$i]}` and called from `${BASH_SOURCE[$i+1]}`.


## See also
1. My answer for Python: [How do I get the path and name of the python file that is currently executing?](https://stackoverflow.com/a/74800814/4561887)
1. [my answer] [Unix & Linux: determining path to sourced shell script](https://unix.stackexchange.com/a/692485/114401)



  [1]: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/get_script_path.sh
  [2]: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world







