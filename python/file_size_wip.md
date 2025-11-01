What a pain in the butt. As is usually the case, programming is nuanced. 


## Getting the size of an open file object

Assuming your open file object is called `f`, here are some techniques: 

1. If actively writing to the end of the file, do this

    ```python
    # [BEST, because it does not require flushing the file first]
    size_bytes = f.tell()  


    # Not as good, because both of these require **flushing** the file first, 
    # which means forcing the data to be written from an OS or hardware-layer
    # cache to the nonvolatile memory of your disk. Flushing frequently 
    # can be slow and will wear out your SSD faster.
    import os

    f.flush()
    # option 1
    size_bytes = os.fstat(f.fileno()).st_size
    # option 2
    size_bytes = os.path.getsize(f.name)
    ```

    Full example: 
    
    [file_size.py]() from my [eRCaGuy_hello_world]() repo: 
    ```python
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
    ```

    Output: 
    ```
    ```
