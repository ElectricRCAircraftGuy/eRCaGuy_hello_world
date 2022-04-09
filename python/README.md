This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Notes

`wip` means "work-in-progress".


# Pylint linter and static code analyzer for Python

[![linting: pylint](https://img.shields.io/badge/linting-pylint-yellowgreen)](https://github.com/PyCQA/pylint)

1. Source code on GitHub: https://github.com/PyCQA/pylint
1. Pylint User Manual: https://pylint.pycqa.org/en/latest/

Use this linter to check your Python code for errors. 


## Installation instructions

See my answer here: [Ask Ubuntu: Installing Pylint for Python3 on Ubuntu](https://askubuntu.com/a/1397185/327339)

`pylint` versions before 2.0.0 or so had separate executables for Python2 vs Python3 code. In the old versions, `pylint` was for Python2 and `pylint3` was for Python3. As of version 2.0.0 or so, we are back to _one_ executable named `pylint`, and it handles _only_ Python3 code. To get this latest version from the GitHub releases page, do this:

1. Go to the ["Releases" page for `pylint` on GitHub](https://github.com/PyCQA/pylint/releases), and download the source code for the latest release (ex: v2.12.2).
1. In your file manager, right-click on the downloaded file and go to "Extract Here". This will produce a directory named `pylint-2.12.2`, for instance.
1. `cd` into the extracted directory and run the `setup.py` script; ex:
    ```bash
    cd path/to/pylint-2.12.2
    sudo python3 setup.py install
    ```
    See also: https://github.com/PyCQA/pylint#install
1. Check your version and ensure it now says `pylint 2.12.2`
    ```bash
    pylint --version
    ```
1. Lint some code:
    ```bash
    pylint path/to/my_python3_file.py
    ```

**Sample usage command and output**. Notice it _does_ show the `C`onvention and `W`arning codes (ex: `C0301` and `W0105`), which is great!:

>     eRCaGuy_hello_world/python$ pylint hello_world.py  
>     ************* Module hello_world  
>     hello_world.py:4:0: C0301: Line too long (102/100) (line-too-long)
>     hello_world.py:33:0: C0116: Missing function or method docstring (missing-function-docstring)
>     hello_world.py:49:-1: W0105: String statement has no effect (pointless-string-statement)
>     
>     -----------------------------------
>     Your code has been rated at 4.00/10


## List of all error codes

`pylint` output shows these **5 types of messages** (emphasis added):  
Source: Tutorial: https://pylint.pycqa.org/en/latest/tutorial.html. 

> Output:  
>    Using the default text output, the message format is :  
>   MESSAGE_TYPE: LINE_NUM:[OBJECT:] MESSAGE  
>   There are **5 kind of message types** :  
>   * **(C) convention**, for programming standard violation
>   * **(R) refactor**, for bad code smell
>   * **(W) warning**, for python specific problems
>   * **(E) error**, for probable bugs in the code
>   * **(F) fatal**, if an error occurred which prevented pylint from doing
>   further processing.

**>> For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here: https://pylint.pycqa.org/en/latest/messages/messages_list.html <<**


## Disable `pylint` errors

See here: https://pylint.pycqa.org/en/latest/user_guide/message-control.html

### Examples:

1. Disable a violation _on the given line_ using `# pylint: disable=whatever` at the _end of_ the offending line:
    From `hello_world.py`:
    ```python
    """
    SAMPLE OUTPUT:

        eRCaGuy_hello_world/python$ ./hello_world.py
        Hello world!

    """ # pylint: disable=pointless-string-statement
    ```
1. [MY PREFERENCE] Disable a violation _on the next line_ using `# pylint: disable-next=whatever` just _before_ the offending line:
    From `hello_world.py`:
    ```python
    # pylint: disable-next=pointless-string-statement
    """
    SAMPLE OUTPUT:

        eRCaGuy_hello_world/python$ ./hello_world.py
        Hello world!

    """
    ```
