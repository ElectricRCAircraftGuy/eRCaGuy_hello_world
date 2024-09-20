#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Tee all stdout output to a log file, to capture all prints in the program. 

GS
Sep. 2024

Status: TODO


PROMPT TO GITHUB COPILOT:
python: tee all stdout output to a file

ANSWER:

To tee all stdout output to a file in Python, you can use the tee functionality provided by the sys module along with a custom class to duplicate the output to both the console and a file.

Example
Here is an example demonstrating how to achieve this:

```python
# SEE BELOW
```

Explanation
1. Custom Tee Class: The Tee class takes multiple file-like objects and writes to all of them.
1. write Method: The write method writes the output to all file-like objects and flushes them to ensure immediate output.
1. flush Method: The flush method flushes all file-like objects.
1. Open Log File: Open the log file in write mode.
1. Create Tee Object: Create a Tee object that writes to both sys.stdout and the log file.
1. Replace sys.stdout: Replace sys.stdout with the Tee object.
1. Example Usage: Use print() to write output to both the console and the file.
1. Close Log File: Close the log file when done.


keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint hello_world.py
```

Run command:
```bash
./hello_world.py
# OR
python3 hello_world.py
```

References:
1.

"""


import sys

class Tee:
    def __init__(self, *files):
        self.files = files

    def write(self, obj):
        for f in self.files:
            f.write(obj)
            f.flush()  # Ensure the output is written immediately

    def flush(self):
        for f in self.files:
            f.flush()

# Open the file in write mode
logfile = open("output.log", "w")

# Create a Tee object that writes to both stdout and the logfile
tee = Tee(sys.stdout, logfile)

# Replace sys.stdout with the Tee object
sys.stdout = tee

# Example usage
print("This will be printed to the console and written to the file.")
print("Another line of output.")

# Close the logfile when done
logfile.close()


# Only run `main()` if this script is **run**, NOT imported
if __name__ == '__main__':
    pass # TODO



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

    eRCaGuy_hello_world/python$ ./hello_world.py
    Hello world!

"""
