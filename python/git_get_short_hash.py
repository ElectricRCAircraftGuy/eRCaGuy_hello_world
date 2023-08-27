#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
2023

Get a short git hash that also indicates if a repo has a "dirty" git status,
for use in software versioning systems to track software versions.
- To do this, I'll call my `eRCaGuy_hello_world/bash/git_get_short_hash.sh`
  script.
- I'll also write a pure Python + system call version, for ease-of-use, that doesn't require that
  bash executable.

Status: done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint git_get_short_hash.py
```

Run command:
```bash
./git_get_short_hash.py
# OR
python3 git_get_short_hash.py
```

References:
1. Bing AI chat helped me.
1. My `eRCaGuy_hello_world/bash/git_get_short_hash.sh` script.
1. My answer: https://stackoverflow.com/a/76856090/4561887

"""


import os
import subprocess

# Get the present working directory of the Python file
SCRIPT_DIRECTORY = os.path.dirname(os.path.abspath(__file__))


def git_get_short_hash():
    """
    Call my Bash script and return the result.
    """

    # Get path to "../bash/git_get_short_hash.sh"
    executable_path = os.path.join(SCRIPT_DIRECTORY, "..", "bash", "git_get_short_hash.sh")

    # Run the executable and capture its output
    result = subprocess.run([executable_path], capture_output=True, text=True)

    git_short_hash = result.stdout
    # strip off the trailing newline char
    if git_short_hash[-1] == "\n":
        git_short_hash = git_short_hash[:-1]

    return git_short_hash


# (Preferred version)
def git_get_short_hash2():
    """
    Returns the git short hash, also indicating if the git status is "clean" or "dirty."
    - Calls some git commands directly from Python. No Bash script required.
    - This is the preferred version in Python since it doesn't require calling a separate bash
      script.
    - See my Bash script for git cmd help: `eRCaGuy_hello_world/bash/git_get_short_hash.sh`.

    Returns:
        - a string of the form "1f6413d" if `git status` is clean, or
        - a string of the form "1f6413d-dirty" if `git status` is dirty (meaning it has pending
          uncommitted changes), or
        - `None` if you are not in a git repo.
    """

    result = subprocess.run(['git', 'rev-parse', '--is-inside-work-tree'],
        capture_output=True, text=True)
    if result.stdout != "true\n":
        # We are not in a git repo
        return None

    # At this point we know we are in a git repo, so get the short hash

    git_short_hash = subprocess.run(['git', 'rev-parse', '--short', 'HEAD'],
        capture_output=True, text=True).stdout
    # strip off the trailing newline char
    if git_short_hash[-1] == "\n":
        git_short_hash = git_short_hash[:-1]

    # See if the `git status` is clean or dirty

    result = subprocess.run(['test', '-z', '"$(git status --porcelain)"'],
        capture_output=True, text=True)
    if result.returncode != 0:
        # git status is dirty
        git_short_hash += "-dirty"

    return git_short_hash


# (Best for most cases, if I copy this file into another project)
def git_get_short_hash3():
    '''
    Same as `git_get_short_hash2()`, but first `cd`s into the directory **where this script is
    located**.

    Example usage:
    - Use this function in another program of yours like this, for instance:

    ```python
    import git_get_short_hash
    import textwrap

    # Alias the function to a shorter name
    git_get_short_hash = git_get_short_hash.git_get_short_hash3

    git_short_hash = git_get_short_hash()
    program_info_str = textwrap.dedent(f"""\
        My other program details here...
        Program version: {git_short_hash}
    """)
    print(program_info_str)
    mylogfile.write(program_info_str)
    ```
    '''

    # See: https://stackoverflow.com/a/431715/4561887
    os.chdir(SCRIPT_DIRECTORY)
    git_short_hash = git_get_short_hash2()
    return git_short_hash


def main():
    """
    The main function of this program.
    """
    git_short_hash = git_get_short_hash()
    print(git_short_hash)

    git_short_hash = git_get_short_hash2()
    print(git_short_hash)

    git_short_hash = git_get_short_hash3()
    print(git_short_hash)


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    main()


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:
(while in this git repo):

    eRCaGuy_hello_world$ python/git_get_short_hash.py
    c628ba7-dirty
    c628ba7-dirty
    c628ba7-dirty

(while NOT in a git repo):

    $ eRCaGuy_hello_world/python/git_get_short_hash.py
    (not a git repo)
    None
    c628ba7-dirty

"""
