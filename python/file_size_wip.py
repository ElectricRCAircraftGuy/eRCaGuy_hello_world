    import os

    with open('file.txt', 'w') as f:
        f.write('hello')
        
        size_bytes1 = f.tell()
        size_bytes2 = os.fstat(f.fileno()).st_size
        size_bytes3 = os.path.getsize(f.name)
        
        print(f"size_bytes1 = {size_bytes1}"
              f"size_bytes2 = {size_bytes2}"
              f"size_bytes3 = {size_bytes3}"
        )

        f.flush()

        size_bytes1 = f.tell()
        size_bytes2 = os.fstat(f.fileno()).st_size
        size_bytes3 = os.path.getsize(f.name)

        print(f"size_bytes1 = {size_bytes1}"
              f"size_bytes2 = {size_bytes2}"
              f"size_bytes3 = {size_bytes3}"
        )
