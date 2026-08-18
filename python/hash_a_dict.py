#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Aug. 2026

Hash a dictionary in Python.

Status: (status)

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
1. [this code]

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



# pylint: disable-next=pointless-string-statement
"""
SAMPLE OUTPUT:



"""
