
GS  
21 Mar. 2022

To do this in a non-blocking way in C, it may be best to use a separate thread which can block on reading stdin, like I do in Python here: [How to read keyboard-input?](https://stackoverflow.com/a/53344690/4561887). I could use pthreads. One key difference I'll have to account for in C, however, is concurrency. I'll need to use a mutex or notification variable or something for the shared memory. In Python, queues are already thread-safe, but no so in C or C++.
