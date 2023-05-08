This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Package and module practice

See:
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


# Example runs

```bash
```
