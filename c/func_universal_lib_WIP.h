///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
June 2024

A "universal function" and "universal function call" library for C, which allows passing a function
plus its arguments in a struct to a universal function which can call the function with the
arguments, regardless of the function's type signature.

This can be very useful to create a worker task, for instance, in a FreeRTOS, embedded, or
multi-threaded application. 

STATUS: wip

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./hello_world_extra_basic.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 hello_world_extra_basic.c -o bin/a -lm && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 hello_world_extra_basic.c -o bin/a && bin/a
```

References:
1. 
1.

*/


#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// An enum to represent the type/signature of the function
typedef enum Func_type_e
{
    FUNC_TYPE_VOID_VOID = 0,    // `void func(void)`
    FUNC_TYPE_VOID_INT,         // `void func(int)`
    FUNC_TYPE_INT_INT,          // `int func(int)`
    // etc: add more types here as needed
} Func_type;

// An enum to represent the argument type
typedef enum Func_arg_type_e
{
    FUNC_ARG_TYPE_PTR = 0,
    FUNC_ARG_TYPE_INT,
    FUNC_ARG_TYPE_FLOAT,
    // etc: add more types here as needed; they must match the types in `Func_arg`
} Func_arg_type;

// A struct to represent a single argument to the function
typedef struct Func_arg_s
{
    union
    {
        void* ptr;
        int i;
        float f;
        // etc: add more types here as needed; they must match the types in `Func_arg_type`
    } arg;

    Func_arg_type arg_type;
} Func_arg;

#define MAX_FUNC_ARGS 3
// A struct to represent a "job" of work to do, meaning: a function and its arguments
typedef struct Func_job_s
{
    /// The function type/signature
    Func_type type;

    /// The pointer to the function to call
    void* func;

    /// The number of arguments to pass to the function at call time
    size_t num_args;

    /// The arguments to pass to the function at call time
    Func_arg args[MAX_FUNC_ARGS];  // up to this many arguments
} Func_job;


// Call the passed-in "job", or function with its given arguments
void func_call(const Func_job * job);


///////// move the next two functions to their own library module?
/*
typedef enum Func_worker_error_e
{
    // No error
    FUNC_WORKER_ERROR_NONE = 0,

    // The worker task is already running
    FUNC_WORKER_ERROR_ALREADY_RUNNING,

    // The worker task is not running
    FUNC_WORKER_ERROR_NOT_RUNNING,

    // The queue is full and the job could not be enqueued
    FUNC_WORKER_ERROR_QUEUE_FULL,
} Func_worker_error;

// Initialize the worker task which will begin running in the background whenever work arrives
Func_worker_error func_worker_init();

// Enqueue a job (function + args) to be executed by the background worker task.
Func_worker_error func_worker_enqueue_job(const Func_job * job);
*/


////////////////// TODO NEXT: IMPLEMENT THESE FUNCTIONS in the .c file! //////////////////


#ifdef __cplusplus
}
#endif
