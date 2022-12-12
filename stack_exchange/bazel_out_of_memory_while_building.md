<!--
https://stackoverflow.com/a/60572662/4561887
-->

## Summary

If bazel runs out of memory while building, and you see this error:

>     java.lang.OutOfMemoryError: Java heap space

...then do this:

1. Increase your RAM _or_ your virtual memory swap file size, to emulate having more RAM (details on how to do this are below).
1. From now on, build with this bazel command, for example, to give Bazel more heap space (RAM) while building. In this case I am giving it **32GB maximum** RAM:
    ```bash
    # Do this to give Bazel up to 32GB of RAM wile building
    time bazel --host_jvm_args=-Xmx32g build //...

    # ...instead of doing this
    time bazel build //...
    ```


## Details

If Bazel fails with any versions of the following error, it's because it ran out of heap space while trying to build. 

Example error:

>     java.lang.OutOfMemoryError: Java heap space

I see that error in your output you pasted. Although very much not well-known, some monster-sized projects and mono-repos can require a heap of **16GB or more**, so I recommend you just create a massive 32GB\~64GB swap file (virtual memory) on your Linux build machine and let it run with it! Give it the whole thing to build!

**CAUTION**: if you have a standard HDD (spinning Hard Disk Drive), this may cause the build to run **dozens or even _hundreds_ of times slower** than using physical RAM to build! This is because HDDs are HORRIBLY HORRIBLY HORRIBLY SLOW! 

**BUUUUT**: If you have a 2.5" or 3.5" SSD (Solid State Drive), then it works _ok_, or 100x BETTER STILL IF YOU HAVE AN _m.2_ form-factor SSD! This is because an m.2 form-factor SSD is INCREDIBLY FAST, so you can get away with HUGE swap files being used in place of RAM all the time because these disks operate so fast!

_If using a top-of-the-line internal m.2 form-factor SSD, I expect the following build with virtual memory to be only \~2x slower than using physical RAM only (of the same size) to build. If you have a super slow spinning HDD, however, the same build which takes 2 hrs using a swap file on the internal m.2 SSD might take up to *multiple days* or more using a swap file on a spinning HDD._ 

_Your results may vary, of course, but favor a smaller JVM bazel heap (to use less of your virtual memory), the slower you expect your virtual memory (swap file) to be._

1. Increase your system’s swap file (virtual memory) to at least 32\~64 GB. To add or remove a swapfile, follow the detailed instructions here: https://linuxize.com/post/how-to-add-swap-space-on-ubuntu-18-04/. UPDATE: use my own instructions here instead: [How do I increase the size of swapfile without removing it in the terminal?](https://askubuntu.com/a/1177620/327339). My instructions avoid the pitfalls of `fallocate` by using `dd` instead, as I explain in my answer there. 

    In short, here is **how to add a swapfile**:
    ```bash
    sudo dd if=/dev/zero of=/swapfile count=64 bs=1G # Create a 64 GiB file
    sudo mkswap /swapfile           # turn this new file into swap space
    sudo chmod 0600 /swapfile       # only let root read from/write to it, 
                                    # for security
    sudo swapon /swapfile           # enable it
    swapon --show                   # verify this new 64GB swap file is 
                                    # now active
    sudo gedit /etc/fstab           # edit the /etc/fstab file to make these 
                                    # changes persistent (load them each boot)
    # ADD this line to bottom (w/out the # comment symbol):
    # /swapfile none swap sw 0 0
    cat /proc/sys/vm/swappiness     # not required: verify your systems 
                                    # "swappiness" value is 60 or so (range 
                                    # is 0 to 100)
    ```
1. **To resize or delete your swapfile:** if you ever need to resize your swap file you just made above, you can delete it like this:
    ```bash
    sudo swapoff -v /swapfile # turn swap file off
    sudo swapon --show  # verify the swap file is off
    free -h             # you can also look at this as an
                        # indication the swap file is off
    sudo rm /swapfile   # remove the swap file
    ```
    Then, you can either follow the instructions above again to recreate it at a new size, or if you are permanently deleting it you'll need to edit your **/etc/fstab** file to remove the `/swapfile none swap sw 0 0` line you previously added to the bottom of it.

1. Add `--host_jvm_args=-Xmx32g` to any `bazel` command, right after the word `bazel`. This sets the *max* Java Virtual Memory, or bazel build heap in this case, to **32GB**, which goes into your swap file once your physical RAM is full. _If you have a high-speed SSD drive, which will operate surprisingly well with swap, expect to wait a few hrs max for your build to complete, depending on the repo size._ If you have an old spinning HDD, expect a repo that takes 2 hrs to buld with a swap file on an internal m.2 SSD to take maybe up to _several days perhaps_ to build with a swap file on a slow spinning HDD--especially if it's an external instead of internal HDD.

    Here is a sample full bazel command with this bazel startup option added, to build an entire repo:
    ```bash
    time bazel --host_jvm_args=-Xmx32g build //...
    ```
    ...instead of this:
    ```bash
    time bazel build //...
    ```
    
    The `time` addition there just prints out a more readable printout of how long the build took is all (I like it). Just be sure to set your max Java Virtual Memory allotted to bazel for any bazel build command by putting `--host_jvm_args=-Xmx32g` (or similar) after the word `bazel` any time you need it. 

    Note that setting the *max* heap like we are doing here with `-Xmx` is NOT the same thing as setting the default heap like others might do with `-Xms`. Setting the max heap still starts with the default heap but lets it grow if needed. [The other answer](https://stackoverflow.com/a/55200662/4561887) shows setting both via an environment variable.

Done!


## References:
1. \*\*\*\*\*[my own answer] [Ask Ubuntu: How do I increase the size of swapfile without removing it in the terminal?](https://askubuntu.com/a/1177620/327339)
1. https://linuxize.com/post/how-to-add-swap-space-on-ubuntu-18-04/
1. https://serverfault.com/questions/684771/best-way-to-disable-swap-in-linux/684792#684792


## See also:
1. https://github.com/bazelbuild/bazel/issues/1308



