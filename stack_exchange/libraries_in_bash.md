<!--
GS
12 May 2023

I'm going to post this in a new Q&A on Stack Overflow.
-->

I'm familiar with Python. It has packages and modules you can `import`. I also know that C and C++ have libraries you can `#include`. 

So, how do you write, import, and use libraries in Bash? 

---

<sub>This is a [Q&A-style question](https://stackoverflow.blog/2011/07/01/its-ok-to-ask-and-answer-your-own-questions/) where I'll also propose an answer to my own question. I don't see any really good Q&As on this topic yet.</sub>

--------

Here's a really beautiful, almost Pythonic style I've come with over the years for writing and using Bash libraries. 

You can also see a general starting point I use for all of my bash scripts in my [hello_world_best.sh](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/hello_world_best.sh) file in my [eRCaGuy_hello_world](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world) repo. You can see a full library example in [floating_point_math.sh](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/floating_point_math.sh).

**[bash/library_basic_example.sh](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/library_basic_example.sh):**

```bash
#!/usr/bin/env bash

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

# Only run `main` if this script is being **run**, NOT sourced (imported).
# - See my answer: https://stackoverflow.com/a/70662116/4561887
if [ "$__name__" = "__main__" ]; then
    main "$@"
fi
```

Now, make the file executable. Running it will run its internal unit tests:
```bash
# make it executable
chmod +x library_basic_example.sh

# run it
./my
```
