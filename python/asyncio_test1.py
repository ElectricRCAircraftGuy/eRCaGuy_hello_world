#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
10 Jan. 2024

Begin learning how asyncio works in Python.

> asyncio: the Python package that provides a foundation and API for running and managing coroutines
Source: https://realpython.com/async-io-python/

Status: Done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint asyncio_test1.py
```

Run command:
```bash
./asyncio_test1.py
# OR
python3 asyncio_test1.py
```

References:
1. Github Copilot: prompt: `python async def`
1. Official Python documentation: https://docs.python.org/3/library/asyncio.html
1. *****https://realpython.com/async-io-python/ <== [STUDY THIS TO REALLY UNDERSTAND]
    > async/await: two new Python keywords that are used to define coroutines

    > asyncio: the Python package that provides a foundation and API for running and managing
    coroutines



"""

import asyncio

class MyClass:
    async def async_method1(self):
        print("async_method1 start")
        await asyncio.sleep(1)
        print("async_method1 end")

    async def async_method2(self):
        print("async_method2 start")
        await self.async_method1()
        print("async_method2 end")

# Usage
async def main():
    obj = MyClass()
    await obj.async_method2()
    await obj.async_method1()

# Run the main function
asyncio.run(main())



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

eRCaGuy_hello_world$ python/asyncio_test1.py 
async_method2 start
async_method1 start
async_method1 end
async_method2 end
async_method1 start
async_method1 end

"""
