
# Todo list

By Gabriel Staples  
Started: 12 Feb. 2022


[Place newest on TOP]


## 20230406:
1. [ ] fix my `CREATE_TASK_TIMER()` cooperative multi-tasking macro!

    Here: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/arduino/coulomb_counter_with_cooperative_multitasking_macro/coulomb_counter_with_cooperative_multitasking_macro.ino#L73-L108

    Change usage from this type of usage:
    ```c
    #import <ercaguy/task.h>
    
    void loop()
    {
        // Create a task timer to run at 500 Hz (every 2000 us, or 2 ms; 1/0.002 sec = 500 Hz)
        const uint32_t PERIOD_US = 2000; // 2000 us pd --> 500 Hz freq
        bool time_to_run;
        uint32_t actual_period_us;
        CREATE_TASK_TIMER(PERIOD_US, time_to_run, actual_period_us);
        if (time_to_run)
        {
            run_task_2();

            // OR, if `run_task_2()` needs the actual period that just occurred, for
            // whatever reason, you may pass it in to your `run_task_2()` function:
            run_task_2(actual_period_us);

            // OR, just do all your code right here instead of in `run_task_2()`
        }
    }
    ```

    ...to this type of usage (removing `time_to_run` and `if (time_to_run)` from the visibility of the user!:
    ```c
    #import <ercaguy/task.h>

    void loop()
    {
        uint32_t actual_period_us; // shared by all task timers

        // Create a task timer to run at 500 Hz (every 2000 us, or 2 ms; 1/0.002 sec = 500 Hz)
        const uint32_t TASK_2_PERIOD_US = 2000; // 2000 us pd --> 500 Hz freq
        CREATE_TASK_TIMER(TASK_2_PERIOD_US, actual_period_us)
        {
            // `actual_period_us` is available here

            run_task_2();

            // OR, if `run_task_2()` needs the actual period that just occurred, for
            // whatever reason, you may pass it in to your `run_task_2()` function:
            run_task_2(actual_period_us);

            // OR, just do all your code right here instead of in `run_task_2()`
        }
    }
    ```

    Also try a few different other approaches to play with them and see which is easiest to use!  
    
    - [ ] Prove them in C by having them just print different things to the screen at different intervals, such as "Task 1", "Task 2", etc.

    Possible other approaches could mimic `pthread_create()`, for instance: https://man7.org/linux/man-pages/man3/pthread_create.3.html:

    ```c
    // max number of tasks that can be created [stored into a statically-allocated array]
    // #define TASK_MAX_NUM 10
    // ^^^ Update: nah; use dynamic memory allocation instead!

    #import <gabrielstaples/task.h>

    // Move this macro into the library as well!
    // TODO
    // #define TASK_CHECK_CREATE_ERRORS(task_error, task_name) \

    void task_2(void * args)
    {
        // Do whatever you need to for your task here. 
        // - Note that global variable `g_actual_period_us` is magically available here!
        //   Update: actually, make it hidden. Obtain it through `task_get_actual_period_us()` 
        //   instead!
        //   This task will just automatically run at the prescribed interval.

        printf("Task 2\n");
    }

    void setup()
    {
        task_error_t task_error;

        // dynamically allocate the array of scheduled tasks
        // TODO: add error checking! (`malloc()` could fail under the hood due to out of memory)
        task_set_max_num_tasks(10); 

        // Create a task timer to run at 500 Hz (every 2000 us, or 2 ms; 1/0.002 sec = 500 Hz)
        
        // `task_create()` will place the `task_2` function into an internal task array to run at
        // the prescribed period.
        // - Note: this is loosely modeled after `pthread_create()`: 
        //   https://man7.org/linux/man-pages/man3/pthread_create.3.html
        const uint32_t TASK_2_PERIOD_US = 2000; // 2000 us pd --> 500 Hz freq
        task_error = task_create(task_2, TASK_2_PERIOD_US, NULL);
        if (task_error != TASK_ERROR_OK)
        {
            printf("Error: failed to create task 2 (err = %s).\n", task_error_str(task_error));
        }

        // etc etc:
        task_error = task_create(task_1, TASK_1_PERIOD_US, NULL);
        task_error = task_create(task_3, TASK_3_PERIOD_US, NULL);
        my_struct_t my_struct = 
        {
            .val1 = 7,
            .val2 = 8,
            .val3 = 9,
        };
        task_error = task_create(task_4, TASK_4_PERIOD_US, &my_struct);
        // etc etc:
    }

    void loop()
    {
        task_run_all(); // everything contained herein!
    }
    ```


## 20230310:
1. Add demos!:
    1. [ ] aligned fixed size memory pool in C
    1. [ ] aligned fixed size memory pool in C++


## 20221207:
1. [ ]  Analyze [this sample data](https://github.com/Atores1/exampleData) and write an algorithm to do automatic peak detection on it! Add an answer to the question: [Finding realtime reliable and precise peak detection algorithm for noisy signals](https://stackoverflow.com/q/74679201/4561887). Ensure your code is capable of running on even the weakest of 8-bit AVR-based Arduinos. Have a signal generator/simulator send the Arduino this data over serial, live, from your computer, so your algorithm can do live peak detection on the Arduino.


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
