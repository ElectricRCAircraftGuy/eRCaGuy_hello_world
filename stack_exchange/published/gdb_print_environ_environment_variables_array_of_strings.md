<!--
GS
14 Aug. 2023
https://stackoverflow.com/q/32917033/4561887

My answer: https://stackoverflow.com/a/76903706/4561887
-->


This also answers the question: **"in GDB, how do you print all C-strings in an array of C-strings (ie: all `char*` C-strings in a `char**` variable), stopping once you reach a terminating NULL ptr value in the array."**


## How to print the entire `environ` variable, containing strings of all of your C or C++ program's environment variables, in GDB


## Quick summary

From the bottom of Option 2 below, this is probably the easiest and fastest, while still producing nice output:

```bash
set $i = 0
printf "environ[%i]: \e[;94m%p\e[m: \"%s\"\n", $i, environ[$i], environ[$i++]
```
Now, press and hold down <kbd>Enter</kbd> until it outputs the full array and you get passed the `(nil): "(null)"` output at the end. 

Or, go look at Option 4 below, and add my `print_environ` function to your `~/.gdbinit` file, and then run this, which is by far the best:
```bash
# print all environment variables as they are currently defined in your 
# C or C++ program
print_environ
```

_If you're just looking for the best answers, first read the note just below, then jump down to Options 2 and 4 below and be done._


## A note about the `environ` variable and when it is updated

Important! The `environ` variable can be expected to only contain a snapshot of your environment variables as available to your program at program start. [The documentation](https://man7.org/linux/man-pages/man7/environ.7.html) states:

> This array of strings is made available to the process by the [`execve(2)`](https://man7.org/linux/man-pages/man2/execve.2.html) call when a new program is started.

I have also done a lot of manual testing and trial-and-error in GDB while debugging my practice [environment_variables_getenv_and_setenv.c](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/environment_variables_getenv_and_setenv.c) C program in my [eRCaGuy_hello_world](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/tree/master) repo, and have found the following to be true.

Once your program starts running, if it modifies any environment variables via [`setenv()`](https://man7.org/linux/man-pages/man3/setenv.3.html), then the `environ` variable will *not* be correspondingly updated! This is a quirk of how `environ` works. Rather, once you have added new environment variables *or* modified existing environment variables in your program, the *only* reliable way that I am aware of to recall their new values is via the [`getenv()`](https://man7.org/linux/man-pages/man3/getenv.3.html) function. Luckily, GDB can call functions in your program directly via the GDB `call` command. So, as long as you have `#include <stdlib.h>` in your program within the section you are currently debugging in GDB, you can call the C function `getenv()` directly in GDB, like this!:

```bash
# This will NOT reliably show new or updated environment variables that your
# program has manipulated. 
# - In some rare cases, some of the environment variables may seem to show some
#   changes, but I cannot explain when, how, or why. So, once your program has
#   started adding new environment variables or modifying existing ones, don't
#   trust this output to be reliable anymore. Instead, call `getenv()` directly, 
#   as shown below. 
print_environ

# This *will* reliable read new or updated environment variables as manipulated
# by your program! 
# - Ex: read the current value of the "SHELL" environment variable via the
#   `getenv("SHELL")` C call: 
call getenv("SHELL")
```

Example call and output while debugging my [environment_variables_getenv_and_setenv.c](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/environment_variables_getenv_and_setenv.c) program:
```bash
(gdb) call getenv("SHELL")
$15 = 0x555555559c76 "bar_4"
```

You can of course also call `setenv()` inside GDB too, to create or modify an existing environment variable. Here, we will set `MY_NEW_VAR="whatever"`, and then get its value:
```bash
call setenv("MY_NEW_VAR", "whatever", 1)
call getenv("MY_NEW_VAR")
```

Here is my example call and output while debugging my program above:
```bash
(gdb) call setenv("MY_NEW_VAR", "whatever", 1)
$17 = 0
(gdb) call getenv("MY_NEW_VAR")
$18 = 0x555555559fcb "whatever"
```

Again, `print_environ`, which prints the full content of the `environ` array of strings, can _not_ be trusted to contain any new environment variables or updated values for them. Use `call getenv("MY_NEW_VAR")` instead.


## Answer details

All Linux programs have a magical [external `char ** environ` variable](https://man7.org/linux/man-pages/man7/environ.7.html) automatically set. It points to an array of pointers to strings which contain the environment variables in plain text. An example of the string at index `0`, for instance, meaning: `environ[0]` in C or C++, might be: `"SHELL=/bin/bash"`. The end of this array of pointers to strings is marked with a `NULL` (decimal `0`) value to indicate there are no more strings.

So, you can print all environment variables as follows. For `environ` to be available, you must be inside the `main()` function somewhere. 

So, first begin debugging, then set a breakpoint at the start of `main()`, and run to that point. Then, run the following commands inside GDB. 

Note that in all cases below, you can NOT copy and paste a chunk of my GDB commands at once, or else they won't run. GDB is a pain, and doesn't like the end-of-line chars, so you much manually type these commands or be very careful to copy only a single line of text at a time, and _not_ include the end-of-line chars when copying the commands.


## Option 1 [easiest to remember]: set a convenience variable, call `print environ[$i++]`, and press <kbd>Enter</kbd> many times

```bash
# set a Convenience Variable
# (https://sourceware.org/gdb/onlinedocs/gdb/Convenience-Vars.html), i,
# initialized to zero
set $i = 0
# print the first string in the environment variable
print environ[$i++]
```

Now press <kbd>Enter</kbd> repeatedly (dozens of times), or just hold it down for a bit, until you see `= 0x0` (the `NULL` terminating value) at some point, indicating that you have reached the end of the array of strings. Here is what the first few outputs and the last few outputs look like for me:

```bash
(gdb) set $i = 0
(gdb) print environ[$i++]
$78 = 0x7fffffffe160 "SHELL=/bin/bash"
(gdb) 
$79 = 0x7fffffffe170 "SESSION_MANAGER=local/gabriel:@/tmp/.ICE-unix/558952,unix/gabriel:/tmp/.ICE-unix/558952"
(gdb) 
$80 = 0x7fffffffe1f4 "QT_ACCESSIBILITY=1"
(gdb) 
$81 = 0x7fffffffe207 "COLORTERM=truecolor"

.
.
.

$133 = 0x7fffffffeebe "GDMSESSION=ubuntu"
(gdb) 
$134 = 0x7fffffffeed0 "DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus"
(gdb) 
$135 = 0x7fffffffef06 "GIO_LAUNCHED_DESKTOP_FILE_PID=559791"
(gdb) 
$136 = 0x7fffffffef2b "GIO_LAUNCHED_DESKTOP_FILE=/home/gabriel/Desktop/open_programming_tools.desktop"
(gdb) 
$137 = 0x7fffffffef81 "OLDPWD=/home/gabriel/GS/dev/eRCaGuy_hello_world"
(gdb) 
$138 = 0x0
```

Notice again, the `= 0x0` (`NULL`) pointer value at the end to terminate the `environ` array of strings. 


## Option 2 [even better!]: use `printf` in GDB to also print the index in the `environ` array that each string comes from!

I first wrote about this in my other answer here: [How to use `printf` in GDB in order to write a custom description around your variable output](https://stackoverflow.com/a/76903487/4561887). See that answer for more detail.

```bash
# Initialize a Convenience Variable
# (https://sourceware.org/gdb/onlinedocs/gdb/Convenience-Vars.html)
set $i = 0
printf "environ[%i]: %s\n", $i, environ[$i++]
# now keep pressing Enter for an amazing repeat effect!
```

The above output now looks like this instead. Notice that you can now easily see which index in the `environ` array of strings each string comes from! For the end of the array of strings, this time look for `(null)`:
```bash
(gdb) set $i = 0
(gdb) printf "environ[%i]: %s\n", $i, environ[$i++]
environ[0]: SHELL=/bin/bash
(gdb) 
environ[1]: SESSION_MANAGER=local/gabriel:@/tmp/.ICE-unix/558952,unix/gabriel:/tmp/.ICE-unix/558952
(gdb) 
environ[2]: QT_ACCESSIBILITY=1
(gdb) 
environ[3]: COLORTERM=truecolor

.
.
.

environ[55]: GDMSESSION=ubuntu
(gdb) 
environ[56]: DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
(gdb) 
environ[57]: GIO_LAUNCHED_DESKTOP_FILE_PID=559791
(gdb) 
environ[58]: GIO_LAUNCHED_DESKTOP_FILE=/home/gabriel/Desktop/open_programming_tools.desktop
(gdb) 
environ[59]: OLDPWD=/home/gabriel/GS/dev/eRCaGuy_hello_world
(gdb) 
environ[60]: (null)
```

**Better still,** let's make it look more like the `print` output in Option 1 by putting quotes around the string, and printing the pointer address too, meaning the address of each C-string in the array of C-strings:

```bash
set $i = 0
printf "environ[%i]: %p: \"%s\"\n", $i, environ[$i], environ[$i++]
```

Now we get this output:

```bash
(gdb) set $i = 0
(gdb) printf "environ[%i]: %p: \"%s\"\n", $i, environ[$i], environ[$i++]
environ[0]: 0x7fffffffe160: "SHELL=/bin/bash"
(gdb) 
environ[1]: 0x7fffffffe170: "SESSION_MANAGER=local/:@/tmp/.ICE-unix/558952,unix/:/tmp/.ICE-unix/558952"
(gdb) 
environ[2]: 0x7fffffffe1f4: "QT_ACCESSIBILITY=1"
(gdb) 
environ[3]: 0x7fffffffe207: "COLORTERM=truecolor"

.
.
.

environ[55]: 0x7fffffffeebe: "GDMSESSION=ubuntu"
(gdb) 
environ[56]: 0x7fffffffeed0: "DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus"
(gdb) 
environ[57]: 0x7fffffffef06: "GIO_LAUNCHED_DESKTOP_FILE_PID=559791"
(gdb) 
environ[58]: 0x7fffffffef2b: "GIO_LAUNCHED_DESKTOP_FILE=/home//Desktop/open_programming_tools.desktop"
(gdb) 
environ[59]: 0x7fffffffef81: "OLDPWD=/home/GS/dev/eRCaGuy_hello_world"
(gdb) 
environ[60]: (nil): "(null)"
```

And lastly, **best yet**, add in some coloring characters (`\e[;34m` to make the foreground color (text) blue, and `\e[m` to clear the formatting), so that the pointer address is blue, like in GDB naturally when you use the `print` function:

```bash
set $i = 0
# print the pointer address as regular blue, like GDB's `print` function does
printf "environ[%i]: \e[;34m%p\e[m: \"%s\"\n", $i, environ[$i], environ[$i++]
# OR, use bright blue, which I like better because it's easier to see
printf "environ[%i]: \e[;94m%p\e[m: \"%s\"\n", $i, environ[$i], environ[$i++]
```

Now, we get the same output as before, except that all of the pointer addresses to each string, like `0x7fffffffe160`, are blue.


## Option 3 [easiest to do]: call `print *environ@100` with an arbitrary long array size (`100` in this case)

Just print `100` strings in the `environ` array of strings. If that's not enough to get to the end of the string and find the `0x0` (`NULL`) marker, then print `200` instead:

```bash
# print 100 elements; the `0x0` address marks the end; everything else after
# that is undefined behavior
print *environ@100

# Or print 200 elements; the `0x0` address marks the end; everything else after
# that is undefined behavior
print *environ@200
```


## Option 4 [best, but trickiest]: write a GDB `while` loop to print all strings in the `environ` array until you reach the `NULL` ptr at the end of the array

Type the following, or copy and paste it, _one line at a time_, and with*out* newlines accidentally being included in what you copy paste, into GDB:
```bash
set $i = 0
while (environ[$i] != 0x0)
    print environ[$i++]
end
```

Here's my command and output, showing first and last several lines of output only, for brevity:
```bash
(gdb) set $i = 0
(gdb) while (environ[$i] != 0x0)
 >    print environ[$i++]
 >end
$345 = 0x7fffffffe160 "SHELL=/bin/bash"
$346 = 0x7fffffffe170 "SESSION_MANAGER=local/gabriel:@/tmp/.ICE-unix/558952,unix/gabriel:/tmp/.ICE-unix/558952"
$347 = 0x7fffffffe1f4 "QT_ACCESSIBILITY=1"
$348 = 0x7fffffffe207 "COLORTERM=truecolor"

.
.
.

$400 = 0x7fffffffeebe "GDMSESSION=ubuntu"
$401 = 0x7fffffffeed0 "DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus"
$402 = 0x7fffffffef06 "GIO_LAUNCHED_DESKTOP_FILE_PID=559791"
$403 = 0x7fffffffef2b "GIO_LAUNCHED_DESKTOP_FILE=/home/gabriel/Desktop/open_programming_tools.desktop"
$404 = 0x7fffffffef81 "OLDPWD=/home/gabriel/GS/dev/eRCaGuy_hello_world"
```

If you see any errors when trying to run the above, it's probably because you copy-pasted multiple lines, or included newlines accidentally when copying, instead of manually typing line-by-line. Try it again, manually typing it this time. 

**Even better, use the last `printf` command we produced at the end of Option 2 above:**

```bash
set $i = 0
while (environ[$i] != 0x0)
    printf "environ[%i]: \e[;94m%p\e[m: \"%s\"\n", $i, environ[$i], environ[$i++]
end
```

**To automate this though, because typing the above is irritating, create a `.gdbinit` file inside your user's home directory,** and copy and paste the following into it to create a `print_environ` function:

```bash
define print_environ
    set $i = 0
    while (environ[$i] != 0x0)
        printf "environ[%i]: \e[;94m%p\e[m: \"%s\"\n", $i, environ[$i], environ[$i++]
    end
end
```

Now, quit GDB, restart the debugger, set a breakpoint at the start of main, run to that breakpoint, and run your new function!:

```bash
print_environ
```

Now you'll see this as your command and output, except the string addresses will be in bright blue:

```bash
(gdb) print_environ 
environ[0]: 0x7fffffffe160: "SHELL=/bin/bash"
environ[1]: 0x7fffffffe170: "SESSION_MANAGER=local/gabriel-5570:@/tmp/.ICE-unix/558952,unix/gabriel-5570:/tmp/.ICE-unix/558952"
environ[2]: 0x7fffffffe1f4: "QT_ACCESSIBILITY=1"
environ[3]: 0x7fffffffe207: "COLORTERM=truecolor"

.
.
.

environ[55]: 0x7fffffffeebe: "GDMSESSION=ubuntu"
environ[56]: 0x7fffffffeed0: "DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus"
environ[57]: 0x7fffffffef06: "GIO_LAUNCHED_DESKTOP_FILE_PID=559791"
environ[58]: 0x7fffffffef2b: "GIO_LAUNCHED_DESKTOP_FILE=/home/gabriel/Desktop/open_programming_tools.desktop"
environ[59]: 0x7fffffffef81: "OLDPWD=/home/gabriel/GS/dev/eRCaGuy_hello_world"
```

Done!


## Printing an `environ[n]` output above

The nice thing about seeing the `environ[n]` indices above is that it makes it easy to re-call just that one string in case you just want to check that one environment variable whose index you now know. Ex:

```bash
print environ[3]
```

But, as stated above in the section titled "A note about the `environ` variable and when it is updated", this cannot be relied upon to give you any new or updated environment variable information. Rather, you should use this GDB call to call the C function `getenv()` instead:
```bash
call getenv("MY_NEW_VAR")
```


## References

1. [`extern char **environ;`](https://man7.org/linux/man-pages/man7/environ.7.html) variable containing an array of strings of environment variables
1. My answer on [How to view a pointer like an array in GDB?](https://stackoverflow.com/a/64055978/4561887)
1. I first learned about this `set $i = 0` and `print environ[$i++]` technique, which uses [Convenience Variables](https://sourceware.org/gdb/onlinedocs/gdb/Convenience-Vars.html#Convenience-Vars), here: https://sourceware.org/gdb/onlinedocs/gdb/Arrays.html. Note that `RET` means to press <kbd>Return</kbd>: 

    > Sometimes the artificial array mechanism is not quite enough; in moderately complex data structures, the elements of interest may not actually be adjacent—for example, if you are interested in the values of pointers in an array. One useful work-around in this situation is to use a convenience variable (see [Convenience Variables](https://sourceware.org/gdb/onlinedocs/gdb/Convenience-Vars.html#Convenience-Vars)) as a counter in an expression that prints the first interesting value, and then repeat that expression via <kbd>RET</kbd>. For instance, suppose you have an array `dtab` of pointers to structures, and you are interested in the values of a field `fv` in each structure. Here is an example of what you might type:
    > 
    > ```
    > set $i = 0
    > p dtab[$i++]->fv
    > RET
    > RET
    > …
    > ```

1. Where I learned the basics about how to write a `while` loop in GDB: [How do I write a loop in a gdb script?](https://stackoverflow.com/a/49675407/4561887)
1. Where I learned how to use the GDB `define` function to set a custom function of your own, as I do with `print_environ` above: [How to loop in a GDB script till program is finished?](https://stackoverflow.com/a/31678832/4561887)
1. My answer on [How to use `printf` in GDB in order to write a custom description around your variable output](https://stackoverflow.com/a/76903487/4561887)
    1. I tinkered with using `printf` here to customize my `environ[]` output, formatting, and custom descriptions.
1. My ANSI color format library in Bash, where I found the color format codes I needed: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/bash/ansi_text_format_lib.sh
    1. My website article on how to use libraries in Bash: [How do you write, import, use, and test libraries in Bash?](https://gabrielstaples.com/bash-libraries/#gsc.tab=0)
1. More on writing scripts in GDB: https://sdimitro.github.io/post/scripting-gdb/
