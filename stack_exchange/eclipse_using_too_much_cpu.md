<!--
GS
Dec. 2022
https://stackoverflow.com/a/74707607/4561887
-->

## Problem: Eclipse and the Eclipse indexer take up all my resources / CPU%

_Tested in Eclipse IDE for C/C++ Developers Version: 2022-09 (4.25.0) on Linux Ubuntu 18.04._


## Quick summary

Solution: decrease the max number of threads Eclipse can use, down to 1/2 as many as your computer has. So, if your computer has 8 physical "cores" (actually: hyperthreads), then decrease the max number of threads that Eclipse can use to 4, or **<= half of your number of cores** for your system, as follows:

In `$HOME/eclipse/cpp-2022-09/eclipse/eclipse.ini` on Linux Ubuntu, or equivalent for your OS, make this change (reducing from 10 threads max, to 4, in my case):

Change _from:_
```bash
-Declipse.p2.max.threads=10
```
_to:_
```bash
-Declipse.p2.max.threads=4
```

Restart Eclipse. 

Now, Eclipse can only take up to 4 of my 8 hyperthreads, and my system runs much better!


## Details and additional improvements to make

I noticed a **huge** improvement in my ability to use my computer while Eclipse was indexing projects once I made this change. Eclipse used to make my computer almost totally unusable for hours or days at a time, before, as it indexes my _huge_ repos--many GiB.

You should also give Eclipse more RAM, if needed. In that same `eclipse.ini` file mentioned above, the `-Xms` setting sets the _starting RAM_ given to Eclipse's Java runtime environment, and the `-Xmx` setting sets the _max RAM_ given to it. For indexing large projects, ensure it has a large enough max RAM to successfully index the project. The defaults, if I remember correctly, are:

```bash
-Xms256m
-Xmx2048m
```

...which means: starting RAM given to the Eclipse Java runtime environment is 256 MiB, and max it is allowed to grow to if needed is 2048 MiB. 

I have 32 GiB of RAM and 64 GiB of swap space, and my indexer was stalling if I gave Eclipse < 12 GiB of max RAM, so I set my settings as follows to start Eclipse with 1 GiB (1024 MiB) of RAM, and allow it up to 12 GiB (12288 MiB) of RAM:

```bash
-Xms1024m
-Xmx12288m
```

So, my total changes were _from:_

```bash
-Declipse.p2.max.threads=10
-Xms256m
-Xmx2048m
```

_...to:_
```bash
-Declipse.p2.max.threads=4
-Xms1024m
-Xmx12288m
```

Here is my final `/home/gabriel/eclipse/cpp-2022-09/eclipse/eclipse.ini` file, with those changes in-place:

```
-startup
plugins/org.eclipse.equinox.launcher_1.6.400.v20210924-0641.jar
--launcher.library
/home/gabriel/.p2/pool/plugins/org.eclipse.equinox.launcher.gtk.linux.x86_64_1.2.600.v20220720-1916
-product
org.eclipse.epp.package.cpp.product
-showsplash
/home/gabriel/.p2/pool/plugins/org.eclipse.epp.package.common_4.25.0.20220908-1200
--launcher.defaultAction
openFile
--launcher.appendVmargs
-vm
/home/gabriel/.p2/pool/plugins/org.eclipse.justj.openjdk.hotspot.jre.full.linux.x86_64_19.0.1.v20221102-1007/jre/bin
-vmargs
--add-opens=java.base/java.io=ALL-UNNAMED
--add-opens=java.base/sun.nio.ch=ALL-UNNAMED
--add-opens=java.base/java.net=ALL-UNNAMED
--add-opens=java.base/sun.security.ssl=ALL-UNNAMED
-Dosgi.requiredJavaVersion=17
-Dosgi.instance.area.default=@user.home/eclipse-workspace
-Dsun.java.command=Eclipse
-XX:+UseG1GC
-XX:+UseStringDeduplication
--add-modules=ALL-SYSTEM
-Dosgi.requiredJavaVersion=11
-Dosgi.dataAreaRequiresExplicitInit=true
-Dorg.eclipse.swt.graphics.Resource.reportNonDisposed=true
-Xms1024m
-Xmx12288m
--add-modules=ALL-SYSTEM
-Declipse.p2.max.threads=4
-Doomph.update.url=https://download.eclipse.org/oomph/updates/milestone/latest
-Doomph.redirection.index.redirection=index:/->http://git.eclipse.org/c/oomph/org.eclipse.oomph.git/plain/setups/
--add-opens=java.base/java.lang=ALL-UNNAMED
-Djava.security.manager=allow
```


## How to see how many "cores" (again, actually: hyperthreads) you have on your hardware

On Linux Ubuntu, simply open the "System Monitor" app. Count the cores. You can see here I have 8: 

[![enter image description here][1]][1]


## How many threads should I give Eclipse?

A good starting point is to give Eclipse *half* of your total cores, to keep it from bogging down your system all the time while indexing and refreshing large projects. So, I have 8 cores (hyperthreads), so I should give Eclipse 4 of them by setting `-Declipse.p2.max.threads=4` in the .ini file. 

This may sound counter-intuitive, but **the larger your project and the weaker your computer, the _fewer_ threads you should give Eclipse!** This is because the larger your project and the weaker your computer, the more your computer will get bogged down using things like your Chrome web browser. So, **to keep Eclipse from sucking up all your resources and freezing your computer, limit the number of threads it can have even more.** If I find Eclipse to be bogging down my computer again, I'll reduce its threads to 2 or 3 max instead of 4. I previously gave it 7 of my 8 threads, and it was _horrible!_ My computer ran _so stinking slow_ and I could never use things like Chrome or Slack properly!


## How much max RAM (`-Xmx`) should I give Eclipse?

- The starting setting of `-Xmx2048m` (2048 MiB, or 2 GiB) is fine for most users. It handles most normal projects you'll encounter. 
- Perhaps as few as `-Xmx512m` (512 MiB, or 0.5 GiB) or so can index the entire Arduino AVR (8-bit mcu) source code just fine
- I need at least `-Xmx12288m` (12288 MiB, or 12 GiB) for my large mono-repo.
- You might need a whopping 32 GiB \~ 64 giB (`-Xmx32768m` to `-Xmx65536m`) to index the entire C++ Boost library, which is totally nuts. So, in most cases, exclude the Boost library from your indexer. I mention that in my Google document linked-to below.

The rule-of-thumb is to increase your `-Xmx` setting a bit whenever you see your indexer struggling or stalled, and Eclipse's usage of the available RAM is continually maxed-out. Here is a screenshot at the bottom of my Eclipse window showing that Eclipse is currently using **8456 MiB** of the available **12288 MiB** which it has currently allocated on the heap:

[![enter image description here][2]][2]

Zoomed-in view: [![enter image description here][3]][3]

If it was rapidly increasing to the max often and staying there frequently, I'd need to increase my `-Xmx` setting further, to let Eclipse further grow the heap.

To **turn on showing the heap status at the bottom of the Eclipse window** (if it isn’t already on by default): 
Window → Preferences → General → check the box for "Show heap status" → click "Apply and Close".

NB: When Eclipse first starts, the memory usage indicator will show the right-number in the above heap usage as being equal to your starting heap allocation, which is defined by the `-Xms` number. As Eclipse needs more memory, it will allocate more, growing that right number up to the `-Xmx` value you've defined. Again, if your indexer stalls or freezes because it's out of RAM, increase that `-Xmx` number to allow Eclipse's indexer to use more heap memory (RAM).


## What other options can I pass to Eclipse's underlying Java virtual machine (JVM)?

Eclipse's article, [FAQ How do I increase the heap size available to Eclipse?](https://wiki.eclipse.org/FAQ_How_do_I_increase_the_heap_size_available_to_Eclipse%3F), states (emphasis added): 

> Some JVMs put restrictions on the total amount of memory available on the heap. If you are getting `OutOfMemoryError`s while running Eclipse, the VM can be told to let the heap grow to a larger amount by passing the `-vmargs` command to the Eclipse launcher. For example, the following command would run Eclipse with a heap size of 2048MB:
> 
> ```bash
> eclipse [normal arguments] -vmargs -Xmx2048m [more VM args]
> ```
> 
> The arguments after `-vmargs` are directly passed to the VM. **Run `java -X` for the list of options your VM accepts. Options starting with `-X` are implementation-specific and may not be applicable to all VMs.**
> 
> You can also put the extra options in `eclipse.ini`.

So, as it says, run this:
```bash
java -X
```

...for a list of all possible arguments you can pass to the underlying Java virtual machine (JVM). Here are the descriptions from that output for `-Xms` and `-Xmx`: 

>     -Xms<size>        set initial Java heap size
>     -Xmx<size>        set maximum Java heap size


## References:

1. My Google document: [Eclipse setup instructions on a new Linux (or other OS) computer](https://docs.google.com/document/d/1LbuxOsDHfpMksGdpX5X-7l7o_TIIVFPkH2eD23cXUmA/edit?usp=sharing)
    1. ["Troubleshooting"](https://docs.google.com/document/d/1LbuxOsDHfpMksGdpX5X-7l7o_TIIVFPkH2eD23cXUmA/edit#heading=h.6kego5424sh1) section of that doc
1. [My answer: java.lang.OutOfMemoryError when running bazel build](https://stackoverflow.com/a/60572662/4561887)
1. [My answer: Ask Ubuntu: How do I increase the size of swapfile without removing it in the terminal?](https://askubuntu.com/a/1177620/327339)
1. I cross-linked back to here from my short answer: [Eclipse uses 100 % CPU randomly](https://stackoverflow.com/a/74707645/4561887) and on Super User here: [High CPU usage and very slow performance with Eclipse](https://superuser.com/a/1756500/425838)
1. [How to view memory usage in eclipse (beginner)](https://stackoverflow.com/a/31255323/4561887)
    1. I also put this info. in my Google document linked-to above.
1. https://wiki.eclipse.org/FAQ_How_do_I_increase_the_heap_size_available_to_Eclipse%3F


  [1]: https://i.stack.imgur.com/dimKK.png
  [2]: https://i.stack.imgur.com/vl6pm.png
  [3]: https://i.stack.imgur.com/Zf4Bq.jpg
