#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Aug. 2026

Hash a dictionary in Python.

Status: Done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint hash_a_dict.py
```

Run command:
```bash
./hash_a_dict.py
# OR
python3 hash_a_dict.py
```

References:
1. https://stackoverflow.com/a/22003440/4561887
1. [this code in my own answer]: https://stackoverflow.com/a/79996618/4561887
1. `json.dumps()` docs: https://docs.python.org/3/library/json.html#json.dumps
1. `json.dump()` docs to explain the args for `json.dumps()`:
   https://docs.python.org/3/library/json.html#json.dump
1. `hashlib.sha256()` docs: https://docs.python.org/3/library/hashlib.html#hashlib.sha256

"""


#!/usr/bin/env python3

import hashlib
import json
import datetime

my_dict = {
    "name": "John Doe",
    "age": 30,
    "balance": 1234.56,  # Decimal or float
    "timestamp": datetime.datetime.now()  # Non-serializable object
}

hash_input_str = json.dumps(my_dict, sort_keys=True, default=str)
hash_hex_str = hashlib.sha256(hash_input_str.encode("utf-8")).hexdigest()

print(f"my_dict:               {my_dict}")
print(f"Hashable input string: {hash_input_str}")
print(f"SHA256 hash:           {hash_hex_str}")
print()

# -------------------------------------------------------------------------------------
# Note: to avoid hashing a certain key, such as the timestamp, filter it out like this:
# -------------------------------------------------------------------------------------
my_dict_filtered = {key: value for key, value in my_dict.items() if key != "timestamp"}
hash_input_str_filtered = json.dumps(my_dict_filtered, sort_keys=True, default=str)
hash_hex_str_filtered = hashlib.sha256(hash_input_str_filtered.encode("utf-8")).hexdigest()

print(f"my_dict_filtered:      {my_dict_filtered}")
print(f"Hashable input string: {hash_input_str_filtered}")
print(f"SHA256 hash:           {hash_hex_str_filtered}")
print()


# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:

eRCaGuy_hello_world$ python/hash_a_dict.py
my_dict:               {'name': 'John Doe', 'age': 30, 'balance': 1234.56, 'timestamp': datetime.datetime(2026, 8, 19, 12, 19, 37, 536437)}
Hashable input string: {"age": 30, "balance": 1234.56, "name": "John Doe", "timestamp": "2026-08-19 12:19:37.536437"}
SHA256 hash:           18c2ac9fe591a87fbd39e91ab8b7e06a83258d13fe59b85ce38caaec89a0fcd8

my_dict_filtered:      {'name': 'John Doe', 'age': 30, 'balance': 1234.56}
Hashable input string: {"age": 30, "balance": 1234.56, "name": "John Doe"}
SHA256 hash:           381437e016e2917a6a8576521fd55ccc8627c775b1d826c4fce63a8f63addac0


"""
