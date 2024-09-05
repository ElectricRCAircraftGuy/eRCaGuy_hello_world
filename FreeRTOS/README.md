This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# See also 

1. [../NOTES_architecture_and_best_practices.md](../NOTES_architecture_and_best_practices.md).
1. \*\*\*\*\*See a list of all my FreeRTOS links in my `FreeRTOS/README.md` readme here: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Engineering/tree/main/FreeRTOS


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
1. [Run-time crashes in FreeRTOS](#run-time-crashes-in-freertos)
    1. [Getting stuck inside the `vListInsert()` function in `FreeRTOS/Source/list.c`](#getting-stuck-inside-the-vlistinsert-function-in-freertossourcelistc)
    1. [Immediately after calling `xSemaphoreCreateBinary()` or `xSemaphoreCreateBinaryStatic()`, you must call `xSemaphoreGive()` before calling `xSemaphoreTake()`](#immediately-after-calling-xsemaphorecreatebinary-or-xsemaphorecreatebinarystatic-you-must-call-xsemaphoregive-before-calling-xsemaphoretake)

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


<a id="run-time-crashes-in-freertos"></a>
# Run-time crashes in FreeRTOS

See also:
1. [../pic32/README.md](../pic32/README.md)


<a id="getting-stuck-inside-the-vlistinsert-function-in-freertossourcelistc"></a>
## Getting stuck inside the `vListInsert()` function in `FreeRTOS/Source/list.c`

If you find yourself with a debugger stuck in this code (as shown by `HERE` below): 

File: `FreeRTOS/Source/list.c`, function: `vListInsert()`:

```c
        /* *** NOTE ***********************************************************
        *  If you find your application is crashing here then likely causes are
        *  listed below.  In addition see https://www.FreeRTOS.org/FAQHelp.html for
        *  more tips, and ensure configASSERT() is defined!
        *  https://www.FreeRTOS.org/a00110.html#configASSERT
        *
        *   1) Stack overflow -
        *      see https://www.FreeRTOS.org/Stacks-and-stack-overflow-checking.html
        *   2) Incorrect interrupt priority assignment, especially on Cortex-M
        *      parts where numerically high priority values denote low actual
        *      interrupt priorities, which can seem counter intuitive.  See
        *      https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html and the definition
        *      of configMAX_SYSCALL_INTERRUPT_PRIORITY on
        *      https://www.FreeRTOS.org/a00110.html
        *   3) Calling an API function from within a critical section or when
        *      the scheduler is suspended, or calling an API function that does
        *      not end in "FromISR" from an interrupt.
        *   4) Using a queue or semaphore before it has been initialised or
        *      before the scheduler has been started (are interrupts firing
        *      before vTaskStartScheduler() has been called?).
        *   5) If the FreeRTOS port supports interrupt nesting then ensure that
        *      the priority of the tick interrupt is at or below
        *      configMAX_SYSCALL_INTERRUPT_PRIORITY.
        **********************************************************************/

        for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd ); pxIterator->pxNext->xItemValue <= xValueOfInsertion; pxIterator = pxIterator->pxNext ) /*lint !e826 !e740 !e9087 The mini list structure is used as the list end to save RAM.  This is checked and valid. *//*lint !e440 The iterator moves to a different value, not xValueOfInsertion. */
        {
            /* There is nothing to do here, just iterating to the wanted  <========== HERE ========
             * insertion position. */
        }
```

...then read the comments above that for some possible reasons why. 

In addition to the reasons above, another possible reason is that (since semaphores are based on queues, and queues are mentioned in bullet 4 in the comments above) you may have called something like `xSemaphoreCreateBinary()` or `xSemaphoreCreateBinaryStatic()` and then *not* immediately called `xSemaphoreGive()` on it before calling `xSemaphoreTake()` on it. 

The official documentation on it (https://freertos.org/xSemaphoreCreateBinaryStatic.html) says: 

> The semaphore is created in the 'empty' state, meaning the semaphore must first be given using the `xSemaphoreGive()` API function before it can subsequently be taken (obtained) using the `xSemaphoreTake()` function.

See also my answer here: [FreeRTOS stuck in `vListInsert()`](https://stackoverflow.com/a/78452464/4561887).


<a id="immediately-after-calling-xsemaphorecreatebinary-or-xsemaphorecreatebinarystatic-you-must-call-xsemaphoregive-before-calling-xsemaphoretake"></a>
## Immediately after calling `xSemaphoreCreateBinary()` or `xSemaphoreCreateBinaryStatic()`, you must call `xSemaphoreGive()` before calling `xSemaphoreTake()`

...or else you get stuck inside the `vListInsert()` function in `FreeRTOS/Source/list.c` as shown above.

Pull request I opened for this: https://github.com/FreeRTOS/FreeRTOS-Kernel/pull/1051. 


