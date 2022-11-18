
# Todo list

By Gabriel Staples  
Started: 12 Feb. 2022


[Place newest on TOP]


## 202210xx:
1. [ ] Write a thread-safe FIFO queue library in both C and in C++. In both cases, allow it to handle **any** data type. In C++, use templates for this. See also, for background research:
    1. FreeRTOS Queues (which are naturally thread-safe, and written in C): https://www.freertos.org/Embedded-RTOS-Queues.html
        1. `xQueueCreate()`: https://www.freertos.org/a00116.html
        1. FreeRTOS Binary Semaphores: https://www.freertos.org/Embedded-RTOS-Binary-Semaphores.html
    1. My own writeup on smart locks, task notifications, and condition variables and things in C++: [cpp/std_mutex_vs_std_lock_guard_vs_std_unique_lock_vs_std_scoped_lock_README.md](cpp/std_mutex_vs_std_lock_guard_vs_std_unique_lock_vs_std_scoped_lock_README.md)


## 20220817:
1. [ ] Write a cooperative multi-tasking library usable in Linux or Arduino. Base it on the `CREATE_TASK_TIMER()` macro in "eRCaGuy_hello_world/arduino/coulomb_counter_with_cooperative_multitasking_macro/coulomb_counter_with_cooperative_multitasking_macro.ino". See also:
    1. My Arduino answer: https://arduino.stackexchange.com/a/75937/7727
    1. My answer: How to auto-generate unique variable names with the line number in them by using macros: https://stackoverflow.com/a/71899854/4561887
        1. "eRCaGuy_hello_world/c/macro_make_unique_variable_name_with_line_number.c"
        1. This trick could be useful potentially to auto-generate certain variable names I need, as necessary, such as the time start variable, maybe? Not sure. Will need to think it through.
    1. Be sure to test it on both Linux and Arduino, proving it works! Consider making it a standalone repo (added to this hello world repo as a subrepo) for better visibility.


## 20220428:
1. [ ] As both C and C++ code: test packing and alignment of `__attribute__((__packed__))` vs `#pragma packed(1)`. I'm pretty sure the former sets only packing to 1 but leaves the struct alignment as a whole to be naturally-aligned, which is good. The latter sets packing to 1 but _also_ sets the whole struct alignment to 1, which is _bad_. See: 
    1. [Microsoft DevBlogs: Anybody who writes #pragma pack(1) may as well just wear a sign on their forehead that says “I hate RISC”, by Raymond C](https://devblogs.microsoft.com/oldnewthing/20200103-00/?p=103290)
1. [x] finish adding gtest & gmock build instructions & initial examples to cpp dir.
1. [x] finish adding cpp/swap_bytes_lib.h/.cpp library and unit tests.
1. [x] finish adding fmt library and cpp/fmt_lib_demo.cpp with `{:20.9f}` type float formatting examples.


## 20220212:

Write C/C++ macros to:
1. count number of arguments:
    ```cpp
    COUNT_ARGS(a, b, c)     --> 3
    COUNT_ARGS(a, b, c, d)  --> 4
    ```
    etc.  
    handle 1 to 128 args.  
2. call the correct function based on the number of arguments
    ```cpp
    FOO(a)          --> FOO1(a)
    FOO(a, b)       --> FOO2(a, b)
    FOOD(a, b, c)   --> FOO3(a, b, c)
    ```
    etc.

### References to begin solving this problem:
1. ***** https://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments/26408195#26408195
1. https://stackoverflow.com/questions/5172435/overload-c-c-preprocessor-macro-on-structure-of-its-argument
1. https://stackoverflow.com/questions/3046889/optional-parameters-with-c-macros
1. https://stackoverflow.com/questions/5085533/is-a-c-preprocessor-identical-to-a-c-preprocessor
1. *****+ https://stackoverflow.com/questions/11317474/macro-to-count-number-of-arguments
1. C++ preprocessor __VA_ARGS__ number of arguments:
    1. *****++ [1st most-upvoted answer] https://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments/2124433#2124433
    1. *****+++ [2nd most-upvoted answer] https://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments/2124385#2124385
