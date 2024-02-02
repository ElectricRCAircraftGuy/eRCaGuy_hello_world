This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# See also 

1. [../NOTES_architecture_and_best_practices.md](../NOTES_architecture_and_best_practices.md).
1. ---
1. FreeRTOS Kernel Developer Docs: https://www.freertos.org/features.html
1. API Reference: https://www.freertos.org/a00106.html


# Table of Contents
<details>
<summary><b>(click to expand)</b></summary>
<!-- MarkdownTOC autolink="true" autoanchor="true" style="ordered" -->

1. [Regexes \(regular expressions\) to convert dynamic memory calls to static memory calls](#regexes-regular-expressions-to-convert-dynamic-memory-calls-to-static-memory-calls)
    1. [1. Mass `xTaskCreate()` to `xTaskCreateStatic()` conversions](#1-mass-xtaskcreate-to-xtaskcreatestatic-conversions)
    1. [2. General fixes](#2-general-fixes)
1. [Tracing your FreeRTOS programs to identify what's going on during crashes](#tracing-your-freertos-programs-to-identify-whats-going-on-during-crashes)
    1. [Tools from FreeRTOS](#tools-from-freertos)
    1. [Manual trace data or "crash pages"](#manual-trace-data-or-crash-pages)

<!-- /MarkdownTOC -->
</details>


<a id="regexes-regular-expressions-to-convert-dynamic-memory-calls-to-static-memory-calls"></a>
# Regexes (regular expressions) to convert dynamic memory calls to static memory calls

These replacements can be done either programmatically at the command line, or manually in MS VSCode, for instance, using the global "Find and Replace" feature with regexes enabled.


<a id="1-mass-xtaskcreate-to-xtaskcreatestatic-conversions"></a>
## 1. Mass `xTaskCreate()` to `xTaskCreateStatic()` conversions

1. Find and replace all instances of `xTaskCreate()` with `xTaskCreateStatic()`
    1. Example 1:

        Find:
        ```
        ^(.*)(xTaskCreate\()(.*),(.*),( )?(.*),(.*),(.*),(.*)(\));(.*)
        ```
        Replace with:
        ```
        $1static StackType_t taskStack[$6];\n$1static StaticTask_t taskControlBlock;\n$1xTaskCreateStatic($3,$4, $6,$7,$8, taskStack, &taskControlBlock);
        ```

        Example result: 
        
        This:
        ```c
        xTaskCreate(myTask, "My Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
        ```

        Becomes this:
        ```c
        static StackType_t taskStack[configMINIMAL_STACK_SIZE];
        static StaticTask_t taskControlBlock;
        xTaskCreateStatic(myTask, "My Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, taskStack, &taskControlBlock);
        ```

    1. Example 2 (BETTER--USE THIS ONE):

        1. [ ] TODO: Add a `#define myTask_STACK_SIZE (configMINIMAL_STACK_SIZE)` type line above the `static StackType_t myTaskStack[configMINIMAL_STACK_SIZE];` line!

        1. Step 1: replace all instances of `xTaskCreate()` with `xTaskCreateStatic()`
        
            Find:
            ```
            ^(.*)(xTaskCreate\()(.*),(.*),( )*(.*),(.*),(.*),( )*(&)?(.*)(\));(.*)
            ```
            Replace with:
            ```
            $1static StackType_t $3Stack[$6];\n$1static StaticTask_t $3ControlBlock;\n$1$11 = xTaskCreateStatic($3,$4, $6,$7,$8, $3Stack, &$3ControlBlock);
            ```

        1. Step 2: replace all instances of `NULL = xTaskCreateStatic(` (which happened in Step 1 cases where the last parameter passed to `xTaskCreate()` was `NULL`) with just `xTaskCreateStatic(`

            Find: 
            ```
            ^(.*)(NULL = xTaskCreateStatic\()
            ```
            Replace with:
            ```
            $1xTaskCreateStatic(
            ```

        1. Example result: 
            
            This:
            ```c
            TaskHandle_t myTaskHandle = NULL;

            xTaskCreate(myTask, "My Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &myTaskHandle);
            ```

            Becomes this:
            ```c
            TaskHandle_t myTaskHandle = NULL;
            
            static StackType_t myTaskStack[configMINIMAL_STACK_SIZE];
            static StaticTask_t myTaskControlBlock;
            myTaskHandle = xTaskCreateStatic(myTask, "My Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, myTaskStack, &myTaskControlBlock);
            ```


<a id="2-general-fixes"></a>
## 2. General fixes

To convert this: 

```c
static StackType_t taskStack[configMINIMAL_STACK_SIZE];
static StaticTask_t taskControlBlock;
myTaskHandle = xTaskCreateStatic(myTask, "My Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, taskStack, &taskControlBlock);
```

to this:
```c
#define myTask_STACK_SIZE (configMINIMAL_STACK_SIZE)
static StackType_t taskStack[myTask_STACK_SIZE];
static StaticTask_t taskControlBlock;
myTaskHandle = xTaskCreateStatic(myTask, "My Task", myTask_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, taskStack, &taskControlBlock);
```

WORK-IN-PROGRESS:

Find: 
```
^(.*)(static StackType_t )(.*)\[(.*)\];(.*)\n^(.*)(static StaticTask_t )(.*);(.*)\n

TODO: finish this regex
^(.*)(xTaskCreate\()(.*),(.*),( )*(.*),(.*),(.*),( )*(&)?(.*)(\));(.*)


^(.*)(xTaskCreate\()(.*),(.*),( )*(.*),(.*),(.*),( )*(&)?(.*)(\));(.*)
```
Replace with:
```
TODO: finish this regex
$1static StackType_t $3Stack[$6];\n$1static StaticTask_t $3ControlBlock;\n$1$11 = xTaskCreateStatic($3,$4, $6,$7,$8, $3Stack, &$3ControlBlock);
```


<a id="tracing-your-freertos-programs-to-identify-whats-going-on-during-crashes"></a>
# Tracing your FreeRTOS programs to identify what's going on during crashes


<a id="tools-from-freertos"></a>
## Tools from FreeRTOS

I don't know much about these yet, but here are some tools from FreeRTOS:

1. https://www.freertos.org/rtos-trace-macros.html
1. https://www.freertos.org/a00021.html#vTaskStartTrace


<a id="manual-trace-data-or-crash-pages"></a>
## Manual trace data or "crash pages"

And here are some techniques to do it yourself:

Scatter `TRACE_LOG()` calls all throughout your code, logging trace data to persistent RAM. You might define `TRACE_LOG()` like this:

```c
#define TRACE_LOG() \
{ \
    /* For the FreeRTOS functions, see here: https://www.freertos.org/a00021.html */ \
    /* NB: NOT FOR USE IN ISRS! Ex: we'd need to use `xTaskGetTickCountFromISR()` instead. */ \
    TickType_t tickCount = xTaskGetTickCount(); \
    const char* taskName = pcTaskGetName(NULL); \
    TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle(); \
    UBaseType_t taskNumber = taskGetNumber(taskHandle); \
    /* NB: for __FILE__, __LINE__, __func__ macros, see GCC's documentation here: */ \
    /* https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html */ \
    traceLog(tickCount, taskName, taskNumber, __FILE__, __LINE__, __func__); \
}
```

...where `taskGetNumber()` is a custom function you write and store inside `freertos_task_c_additions_include.h`. See my answer here: [FreeRTOS: obtain the stack size (`usStackDepth`) value in words or bytes after calling `xTaskCreate()`](https://stackoverflow.com/a/77568267/4561887). 

You'd set `#define configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H 1` in your `FreeRTOSConfig.h` file to get your custom `freertos_task_c_additions_include.h` to be included in the bottom of FreeRTOS's `tasks.c`. 

The definition for `taskGetNumber()` inside `freertos_task_c_additions_include.h` would look something like this:

```c
#pragma once

#include "FreeRTOS.h"

#if (configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H == 1)

UBaseType_t taskGetNumber(TaskHandle_t taskHandle)
{
    TCB_t * tcb = prvGetTCBFromHandle(taskHandle);

    // no critical section needed to copy out this single `UBaseType_t` value
    UBaseType_t taskNumber = tcb->uxTaskNumber;

    return taskNumber;
}

#endif // (configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H == 1)
```

You'd also have to write the `traceLog()` function, which would log trace data. It might simply log continually to a large circular array in persistent RAM, for instance, and then if the system crashes (ie: resets due to the watchdog), then after reboot, the persistent array is printed out over serial debug or Ethernet telnet, or logged to an SD card, for review by the developer. If you scatter `TRACE_LOG()` calls all throughout your code, you might be able to get a good idea of what was happening when the system crashed.

Persistent RAM can be set up using GCC attributes, as follows. See the `persistent` attribute here: https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html. Ex: 

```c
Trace_data trace_data[1024] __attribute__((__persistent__));
```

Note that persistent RAM is not a special type of RAM. It's just regular, volatile RAM. It only "persists" so long as the system does not lose power, such as is the case when the system restarts due to a watchdog reset.

The outline of the `traceLog()` function might look something like this:

```c
void traceLog(
    TickType_t tickCount,
    const char* taskName,
    UBaseType_t taskNumber,
    const char* file,
    int lineNumber,
    const char* funcName)
{
    // Log to the persistent RAM circular buffer, which is a circular array
    // of `Trace_data` structs.
    // ...

    // Be sure to use a critical section, as needed, to prevent broken data 
    // from being logged into the circular buffer.
    
    // See my answer here: https://stackoverflow.com/a/71626598/4561887
    taskENTER_CRITICAL();

    // critical section where we store all of the inputs into the circular buffer
    
    taskEXIT_CRITICAL();
}
```

That's the gist of it.
