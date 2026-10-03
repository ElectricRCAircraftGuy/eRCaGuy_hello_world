import os

with open("file.txt", "w") as f:
    f.write("hello")

    size_bytes1 = f.tell()
    size_bytes2 = os.fstat(f.fileno()).st_size
    size_bytes3 = os.path.getsize(f.name)

    # fmt: off
    print(f"size_bytes1 = {size_bytes1}\n"
          f"size_bytes2 = {size_bytes2}\n"
          f"size_bytes3 = {size_bytes3}"
    )
    # fmt: on

    f.flush()

    size_bytes1 = f.tell()
    size_bytes2 = os.fstat(f.fileno()).st_size
    size_bytes3 = os.path.getsize(f.name)

    # fmt: off
    print(f"size_bytes1 = {size_bytes1}\n"
          f"size_bytes2 = {size_bytes2}\n"
          f"size_bytes3 = {size_bytes3}"
    )
    # fmt: on
