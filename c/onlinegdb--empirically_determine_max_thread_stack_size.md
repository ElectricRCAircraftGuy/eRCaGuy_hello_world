
## Object file (compiled binary executable file) size notes

To compare object file (executable file) sizes:

    size bin/stack_size_bruno_c
    size bin/stack_size_bruno_cpp
    size bin/stack_size_gs_c
    size bin/stack_size_gs_cpp

Or, for more details:

    objdump -h bin/stack_size_bruno_c
    objdump -h bin/stack_size_bruno_cpp
    objdump -h bin/stack_size_gs_c
    objdump -h bin/stack_size_gs_cpp

Sample `size` output:

    $ size bin/stack_size_bruno_c
       text    data     bss     dec     hex filename
       1969     632      16    2617     a39 bin/stack_size_bruno_c

    $ size bin/stack_size_bruno_cpp
       text    data     bss     dec     hex filename
       1969     632      16    2617     a39 bin/stack_size_bruno_cpp

    $ size bin/stack_size_gs_c
       text    data     bss     dec     hex filename
       2091     640      16    2747     abb bin/stack_size_gs_c

    $ size bin/stack_size_gs_cpp
       text    data     bss     dec     hex filename
       2091     640      16    2747     abb bin/stack_size_gs_cpp


## TODO

1. Study the various comments by @Peter Cordes under [my answer](https://stackoverflow.com/a/64085509/4561887), starting [here](https://stackoverflow.com/questions/1825964/c-c-maximum-stack-size-of-program-on-mainstream-oses/64085509?noredirect=1#comment126662172_64085509), and implement any changes necessary to my code (`onlinegdb--empirically_determine_max_thread_stack_size_GS_version.c`) to incorporate the concepts he is talking about. `man ulimit`, under the "DESCRIPTION" section, says: "For the shell command `ulimit()`, see `bash(1)`." `man bash`, and then searching for the `ulimit` bash built-in function, says that `ulimit [-HSabcdefiklmnpqrstuvxPT [limit]]` "Provides control over the resources available to the shell and to processes started by it, on systems that allow such control." The `-s` option is to set or get `The maximum stack size`. So, running `ulimit -s` shows the "maximum stack size" to be `8192`, which apparently is in units of KiB, because that's equal to 8192/1024 = **8 MiB**, which is just a little more than my measured `7.4 MB` on Linux. So, where did the remaining 2/3 of a MiB or so go (meaning: the difference between these two numbers)? Peter explains in his comments that it probably went to the `printf()` stack and to environment setup variables for the C runtime environment or something. So, I should expand my empirical stack size checker program above to check the `ulimit -s` setting 

    says that the `ulimit` tool is to `allows  shows the stack size:
   ```bash
   ulimit --help`Run `ulimit -s` and you'll see the 
