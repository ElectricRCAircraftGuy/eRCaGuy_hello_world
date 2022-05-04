#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Demonstrate a basic system call via the `subprocess` module which allows you to call system calls
via _subprocesses_ while opening _pipes_ as an IPC (Inter-Process Communication) mechanism in order
to read the stdout output back from the subprocess! For this demo let's just read back the stdout
output from `ls -alF`, which is the common Ubuntu alias for `ll`!

Status: wip

keywords: system call pipe IPC subprocess in Python

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint system_call_subprocess_pipe.py
```

Run command:
```bash
./system_call_subprocess_pipe.py
# OR
python3 system_call_subprocess_pipe.py
```

References:
1. *****+ [my answer with this code] https://stackoverflow.com/a/72105927/4561887
1. *****+ The main Q&A for sub-processes and pipes in Python:
   https://stackoverflow.com/a/4760517/4561887
1. https://docs.python.org/3/library/subprocess.html#subprocess.run - official documentation

"""

import subprocess

cmd = ["ls", "-alF"]
result = subprocess.run(cmd, stdout=subprocess.PIPE, check=True)
print(result)

print()
# print the stdout from the result in a pretty format
print(result.stdout.decode("utf-8"))



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

The end of the output is the same as `ls -alF`.


"""
