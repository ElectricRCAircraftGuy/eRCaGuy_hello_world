
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
