This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Table of contents

<!-- MarkdownTOC autolink="true" autoanchor="true" style="ordered" -->

1. [General best practices](#general-best-practices)
1. [For C and C++ programming](#for-c-and-c-programming)
    1. [Notes:](#notes)
    1. [Best practices:](#best-practices)
1. [For FreeRTOS \(also applies to many bare metal or other robotics systems\)](#for-freertos-also-applies-to-many-bare-metal-or-other-robotics-systems)

<!-- /MarkdownTOC -->


<a id="general-best-practices"></a>
# General best practices

These could also be part of a "style guide" or "coding standards" document.


<a id="for-c-and-c-programming"></a>
# For C and C++ programming

<a id="notes"></a>
#### Notes:

1. [SAFETY-CRITICAL] refers to safety-critical, deterministic, memory-constrained embedded system environments, such as microcontrollers embedded in robotic systems, cars, aircraft, medical devices, etc. Where this marking is present, you must do this to be considered "safety critical" and safe code. 
1. [BUG_WARNING] means that if you _don't_ do this, you will have a definite bug in your code.

<a id="best-practices"></a>
#### Best practices:

1. Turn on `-Wall -Wextra -Werror` and fix all resulting build errors.
1. Remove all `default` cases from all switch cases in the entire code base. 
    1. This is safer, as it will cause a **compile-time error** if all enum values are not covered in a switch statement, thereby ensuring that you keep enum definitions and switch statements in-sync.
1. [SAFETY-CRITICAL] Remove all run-time instances of `malloc()` after initialization. 
    1. `malloc()` is not safety-critical, non-deterministic, and can lead to memory fragmentation if `malloc`ing and `free`ing at run-time.
1. Add the git commit hash to to every code build as part of the version number information. This leads to a truly unique version git hash even when the software version number is not otherwise changed. 
    1. Use my `git_get_short_hash` function here: [How do I get the hash for the current commit in Git?](https://stackoverflow.com/a/76856090/4561887).
1. Implement CI/automatic builds. 
    1. If using Atlassian's Bitbucket, start by watching this video: [Intro to CICD with Bitbucket Pipelines](https://www.youtube.com/watch?v=wJv3ZGwxQPQ)
1. Implement CI/automatic unit tests. 
1. Implement CI/automatic `clang-format` checks. 
    1. Block merging if `clang-format`'s results would cause a change from what the author is trying to merge.
    1. My last companies did it this way too.
    1. See my repo for clang-format help: https://github.com/ElectricRCAircraftGuy/eRCaGuy_CodeFormatter
1. Implement CI/automatic static analysis checks. 
    1. The LLVM/Clang static analyzer is a good one to use. It includes ASAN, UBSAN, etc. Search this page for "sanitizer": https://clang.llvm.org/docs/index.html. 
1. Use the safer `n` versions of all C `string.h` functions:
    1. They are safer and prevent buffer overflows.
    1. Have the CI build system block PRs that use the wrong versions, or at least warn the user and make a recommendation.
    1. I have seen this at my past companies. 
    1. https://cplusplus.com/reference/cstring/
    1. `strncpy()` - very useful to prevent buffer overflows
    1. `strncat()` (maybe--`strcat` is already walking a string to find the `NULL` terminator, to maybe `strncat` adds little value; I need to think about this one some more)
    1. `strncmp()` - very useful
1. Add `__FILE__`, `__func__`, and `__LINE__` macro prints, as well as precise timestamps, into every debug statement where we print an error. We need to instantly know where to look in the code to fix a bug, and what the timestamp is for each error in case errors end up out-of-order in the print log. 
    1. https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html
1. [SAFETY-CRITICAL] Replace `printf()` to use a non-`malloc`ing safe implementation we write. Redirect `stdout` to our debugging framework over serial or to a file or whatever. 
1. Use GCC's `__attribute__ ((format (printf, x, y)))` to enforce proper format string and arguments in all custom `printf()` or similar functions where there is a format string followed by variadic arguments.
1. Use `vprintf()`, variadic args, etc., where needed.
1. Use only `stdint.h` types: `intN_t` and `uintN_t` types (such as `int8_t`, `uint8_t`, `int32_t`, `uint32_t`, etc.), _not_ `int`, `unsigned int`, `unsigned long`, etc. Always knowing the bit-width is more portable and safe. 
    1. https://cplusplus.com/reference/cstdint/
    1. Note: `bool` and `char` are good to use in their respective roles, too, namely: for boolean true/false types, and for characters and strings (arrays of characters), respectively.
1. Always use `bool` and `true`/`false` for boolean types, rather than `unsigned int`, `int`, etc. Avoid `1`/`0` to signify `true`/`false`. 
    1. The `bool` and `true`/`false` types are self-documenting and make your intent clear.
1. Prefer `size_t` as the type for any index variable which indexes into an array, since it is the portable type specified to always be big enough to index to any possible element in any array on any given system. 
    1. https://cplusplus.com/reference/cstddef/size_t/

        > It is a type able to represent the size of any object in bytes.

    1. Possible exceptions are on very memory-constrained devices, such as 8-bit microcontrollers, where you might prefer to save stack (RAM) and flash usage by using the smallest type necessary, such as `uint8_t`, `uint16_t`, or `uint32_t`, instead.
1. Upgrade the compiler every 2 to 3 years to keep it up-to-date. 
1. Use `-std=gnu17` or later for C, and `-std=gnu++17` or later for C++. 
    1. Try to keep up to be using a standard 5 years old or newer.   
    1. Don't let yourself get more than 10 years behind the standard. 
    1. C/C++ 17 (from 2017) is 6 years old now, which is okay, but C/C++20 (from 2020) would be even better. 
    1. I also recommend the `gnu` languages over the `c` languages. Ex: `-stde=gnu17` instead of `-std=c17`. The GNU languages provide useful compiler extensions and better POSIX compatibility.
1. Use `#pragma once` instead of `#ifndef` include guards.
    1. `#pragma once` is easier to maintain, faster to compile, and less error-prone. 
    1. See my answer here: https://stackoverflow.com/a/77719024/4561887
1. [SAFETY-CRITICAL] Take care with how you implement run-time asserts and watchdogs. You want to keep these implemented during run-time, but change the behavior as appropriate, to AVOID AUTO-CRASHING A VEHICLE. 
    1. In bench-testing, perhaps you allow the assert to crash the system. But, in **flight testing** you should have it trigger a critical fail-safe condition to have the vehicle land immediately (or pull over and "safe stop" if a car) rather than just crash. 
    1. Same with watchdogs. In bench-testing, perhaps you allow the watchdog to reset the system. But, in **flight testing** you should have the watchdog interrupt fire (ie: enable a watchdog ISR) when the watchdog expires, and if `is_flying` is `true`, log a critical error and reset (pet) the watchdog instead of allowing the system to power cycle.
    1. In other words, NEVER FORCE A VEHICLE CRASH when you can instead try to gracefully recover it and prevent harm to people and property.
1. [SAFETY-CRITICAL] The same as just above also goes for "brown-out resets". 
    1. For bench-testing, using the highest brown-out reset voltage of perhaps 3.0V on a 5.0V system is fine. But, in **flight testing**, if the system can actually run down to 2.5V at room temperature / flight temperatures, then use a brown-out register/fuse setting of 2.0V or whatever, then trigger a critical fault and fail-safe "land now" situation instead of just resetting the power and force-crashing the vehicle. 
    1. Again, the mantra should be "try to fly and fail safely / land now, rather than force an auto-crash."


<a id="for-freertos-also-applies-to-many-bare-metal-or-other-robotics-systems"></a>
# For FreeRTOS (also applies to many bare metal or other robotics systems)

1. Don't create new tasks after initialization.
1. Break out and don't run the main code if initialization fails. 

1. Replace `vTaskDelay()` with `vTaskDelayUntil()` in all tasks which need less jitter and more consistent timing. 
    1. See here: https://www.freertos.org/a00127.html:

        > `vTaskDelay()` does not therefore provide a good method of controlling the frequency of a periodic task as the path taken through the code, as well as other task and interrupt activity, will effect the frequency at which `vTaskDelay()` gets called and therefore the time at which the task next executes. See `vTaskDelayUntil()` for an alternative API function designed to facilitate fixed frequency execution. It does this by specifying an absolute time (rather than a relative time) at which the calling task should unblock.

    1. But, handle the edge case where a bunch of time elapses due to tasks being blocked, and then the task wants to run every tick until it "catches up". You may need to skip the start epoch forward periodically to counter this. I do this concept in my `CREATE_TASK_TIMER()` macro here, for instance: https://stackoverflow.com/a/50032992/4561887

1. Use the largest delay period (run period) practical for all tasks. 
    1. ie: don't run them unnecessarily faster than needed, as that takes up CPU resources and decreases the efficiency of the system by adding additional unnecessary context switches.
1. In most cases, sensor data should not be gathered significantly faster than the control loop. 
    1. If performing filtering, sensor data should be gathered only as fast as necessary. 
    1. One filtered result per control loop is all that is needed.
    1. Even when performing significant filtering, you can still carry a circular buffer of data to process and only add and remove one element per sensor loop, thereby running the sensor loop at the exact same speed as the control loop. 
        1. Arduino has an excellent example of this, performing a windowed moving average FIR filter on sensor data here: https://docs.arduino.cc/built-in-examples/analog/Smoothing. Their ring buffer solution is highly efficient and a great model to follow. 
1. Use event-based tasks and programming whenever possible, rather than "fixed-interval" timestamp-based programming. 
    1. Ex: use `xQueueSend()` and `xQueueReceive()` to send and receive data between tasks, rather than using a fixed-interval timer to trigger a task to run, and then having that task poll for data. See: https://www.freertos.org/a00018.html. 
    1. Sensor data might be gathered at 100Hz, for instance, and then placed into a queue. 
    1. The control loop might then read from the queue, blocking on the queue until data arrives, rather than running at a fixed rate with `vTaskDelayUntil()`, or (worse) `vTaskDelay()`.
1. (Repeat of the bullet above) Use queues to pass data between tasks. The task that writes to a queue might be at the top of the hierarchy and use a time-based delay. But, all tasks consuming this data should block on the queue and _not_ use any time-based delays. Event-based programming will significantly improve the efficiency of the system. 
1. Use `vTaskDelay(ms/portTICK_PERIOD_MS)` (okay), or `vTaskDelay(pdMS_TO_TICKS(ms))` (better!) instead of `vTaskDelay(ms)`, because the latter only works if your tick rate is 1kHz, or 1ms period, which according to FreeRTOS themselves is probably too high as it is (see next bullet).
    1. The [`vTaskDelay()`](https://www.freertos.org/a00127.html) and `vTaskDelayUntil()` functions expect ticks as their argument, _not_ ms!

1. Prefer lower FreeRTOS tick rates to higher ones, whenever possible. 
    1. Ex: I recommend a tick rate of perhaps 500 Hz for applications performing inner-loop stabilization and control, such as self-balancing vehicles and quadcopters, and 100 Hz otherwise. Even 10 Hz \~ 50 Hz is sufficient for outer-loop control and guidance in most systems. 
    1. See this answer: https://stackoverflow.com/a/75249983/4561887
    1. And from FreeRTOS directly: https://www.freertos.org/a00110.html#configTICK_RATE_HZ: 

        (emphasis added):

        > ...a high tick frequency also means that the RTOS kernel will use more CPU time so be less efficient. The RTOS demo applications all use a tick rate of 1000Hz. This is used to test the RTOS kernel and **is higher than would normally be required.**
        
        And:

        > The RTOS scheduler will share processor time between tasks of the same priority by switching between the tasks during each RTOS tick. **A high tick rate frequency will therefore also have the effect of reducing the 'time slice' given to each task.**

1. Prefer fewer tasks to more tasks. One sensor-reading task that reads all sensors at once, for instance, is strongly preferred to one task per sensor, which adds a lot of inefficiency and overhead. 
    1. If sensors need to be read at different rates (ex: 100 Hz, 50 Hz, and 10 Hz), but all use the same serial, I2C, or SPI bus, rather than having multiple tasks, and semaphores to manage the bus, you could have just one task that uses [my cooperative multitasking technique shown here](https://stackoverflow.com/a/50032992/4561887) to read each sensor at the appropriate rate, but all inside the same 100 Hz task. 
1. Appropriately choose between binary semaphores and mutexes. 
    1. See: https://www.freertos.org/xSemaphoreCreateBinary.html: 

        > Binary semaphores and [mutexes](https://www.freertos.org/CreateMutex.html) are very similar but have some subtle differences: Mutexes include a priority inheritance mechanism, binary semaphores do not. This makes binary semaphores the better choice for implementing synchronisation (between tasks or between tasks and an interrupt), and mutexes the better choice for implementing simple mutual exclusion.
        > 
        > A binary semaphore need not be given back once obtained, so task synchronisation can be implemented by one task/interrupt continuously 'giving' the semaphore while another continuously 'takes' the semaphore. This is demonstrated by the sample code on the [`xSemaphoreGiveFromISR()`](https://www.freertos.org/a00124.html) documentation page. Note the same functionality can often be achieved in a more efficient way using a [direct to task notification](https://www.freertos.org/RTOS_Task_Notification_As_Binary_Semaphore.html).

1. Watch out for _priority inheritance_ when using mutexes! This can unexpectedly cause a lower-priority task to run at a higher priority when it holds a mutex that a higher-priority task needs it to release. Here is how priority inheritance works:
    1. If a higher-priority task is blocking on trying to take a mutex held by the lower-priority task, the scheduler will raise the priority of that lower-priority task to the priority of that higher-priority task. The higher priority task is now blocked, so it will yield, and that once-lower-priority task which holds the mutex will now run at the higher priority until it releases the mutex, at which point that higher-priority task will run again and take the mutex. 
    1. This is how, why, and when the lower-priority task will "inherit" the higher priority of the task trying to take the mutex until that previously-lower-priority task releases the mutex.
    1. See: https://www.freertos.org/Real-time-embedded-RTOS-mutexes.html

        > Mutexes are [binary semaphores](https://www.freertos.org/Embedded-RTOS-Binary-Semaphores.html) that include a priority inheritance mechanism. Whereas binary semaphores are the better choice for implementing synchronisation (between tasks or between tasks and an interrupt), mutexes are the better choice for implementing simple mutual exclusion (hence 'MUT'ual 'EX'clusion).

1. When using one task to "notify" or unblock another task, use a direct-to-task notification, such as [`xTaskNotifyGive()`](https://www.freertos.org/xTaskNotifyGive.html), instead of a binary semaphore. 
    1. Quote from the FreeRTOS documentation on how to wake one task from another task: https://www.freertos.org/RTOS_Task_Notification_As_Binary_Semaphore.html:        

        > Unblocking an RTOS task with a direct notification is **45% faster** and **uses less RAM** than unblocking a task with a binary semaphore. This page demonstrates how this is done.

    1. The FreeRTOS task notification system is similar to using `std::condition_variable`s in C++11 and later. See my notes on `std::condition_variable`s here:
        1. https://gabrielstaples.com/cpp-mutexes-and-locks/#5-stdcondition_variable-c11
        1. https://stackoverflow.com/a/74024531/4561887

    1. See also: https://www.freertos.org/RTOS_Task_Notification_As_Counting_Semaphore.html

1. When passing data between tasks (threads), use [FreeRTOS queues](https://www.freertos.org/Embedded-RTOS-Queues.html), rather than semaphores and shared variables. FreeRTOS queues are automatically thread-safe and efficient, and they avoid the unnecessary use of global variables for data sharing. 
    1. See also the "event-based tasks and programming" bullet above. 
    1. https://www.freertos.org/Embedded-RTOS-Queues.html
1. [BUG_WARNING] FreeRTOS mutexes: watch out for cases where recursive mutexes should be used instead of regular mutexes.
    1. When using FreeRTOS semaphores and mutexes, use the appropriate type. If a single task has code or an API that is structured in such a way that the same mutex gets taken twice in a row, then it must get released twice before actually releasing the mutex. In such a case, a _recursive_ mutex must be used! This is a common pattern seen when `mymodule_func1()` calls `mymodule_func2()`, for instance, and each of those takes the same mutex. See:
    1. https://www.freertos.org/Real-time-embedded-RTOS-mutexes.html
    1. https://www.freertos.org/RTOS-Recursive-Mutexes.html: 

        > A mutex used recursively can be 'taken' repeatedly by the owner. The mutex doesn't become available again until the owner has called xSemaphoreGiveRecursive() for each successful xSemaphoreTakeRecursive() request. For example, if a task successfully 'takes' the same mutex 5 times then the mutex will not be available to any other task until it has also 'given' the mutex back exactly five times.
        >
        > This type of semaphore uses a priority inheritance mechanism so a task 'taking' a semaphore MUST ALWAYS 'give' the semaphore back once the semaphore it is no longer required.
        > 
        > Mutex type semaphores cannot be used from within interrupt service routines.

1. [BUG_WARNING] Use the `...FromISR()` function calls within ISRs. Ex: [`xSemaphoreTakeFromISR()`](https://www.freertos.org/xSemaphoreTakeFromISR.html).

