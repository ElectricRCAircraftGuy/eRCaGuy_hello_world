#!/usr/bin/env python3

"""
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
14 Aug. 2026

Demo how to use filelock.FileLock inter-process file locking to safely increment a counter in a file
from multiple processes.

Status: done and works!

keywords: (keywords)

Check this script with `pylint` v2.0.0 or later. See "eRCaGuy_hello_world/python/README.md" for
installation instructions to install the latest version from GitHub.
For a list of all error codes, such as `C0301`, `C0116`, `W0105`, etc., see here:
https://pylint.pycqa.org/en/latest/messages/messages_list.html
```bash
pylint filelock_counter_incrementing_demo.py
```

Run command:
```bash
./filelock_counter_incrementing_demo.py
# OR
python3 filelock_counter_incrementing_demo.py
```

References:
1. https://py-filelock.readthedocs.io/en/latest/
    1. https://py-filelock.readthedocs.io/en/latest/api.html:
        > FileLock and AsyncFileLock are platform aliases: at import time they resolve to
        UnixFileLock or WindowsFileLock (and their async peers), or to the soft backends on a build
        without fcntl.

What it does:
- counter.txt holds the shared data.
- counter.txt.lock is the lock file used only for coordination.
- `with lock`: ensures only one process at a time enters the critical section.
- `timeout=5` means another process will wait up to 5 seconds trying to acquire the lock before
  raising Timeout.

How to test it:
1. Save it as filelock_demo.py.
1. Run it in one terminal.
1. Quickly run it again in a second terminal.
1. You should see one process acquire the lock first, while the other waits. That prevents both
   processes from reading the same old value and writing conflicting updates.

"""


from filelock import FileLock, Timeout
from pathlib import Path
import time

# NB: `FileLock()` automatically creates the parent dir if it doesn't exist.
data_file = Path("temp/counter.txt")
lock_file = Path("temp/counter.txt.lock")

lock = FileLock(lock_file, timeout=5)

try:
    with lock:
        print("Lock acquired.")

        if data_file.exists():
            count = int(data_file.read_text(encoding="utf-8").strip())
        else:
            count = 0

        print(f"Current count: {count}. Incrementing by one...")

        # Simulate work while holding the lock.
        time.sleep(3)

        count += 1
        data_file.write_text(f"{count}\n", encoding="utf-8")
        print(f"New count written: {count}")

except Timeout:
    print("Could not acquire the lock within 5 seconds.")

