
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


