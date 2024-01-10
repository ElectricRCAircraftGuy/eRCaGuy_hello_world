This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

See: 

1. [../NOTES_architecture_and_best_practices.md](../NOTES_architecture_and_best_practices.md).
1. ---
1. FreeRTOS Kernel Developer Docs: https://www.freertos.org/features.html
1. API Reference: https://www.freertos.org/a00106.html


# Regexes (regular expressions) to convert dynamic memory calls to static memory calls

These replacements can be done either programmatically at the command line, or manually in MS VSCode, for instance, using the global "Find and Replace" feature with regexes enabled.

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

        1. Step 1: replace all instances of `xTaskCreate()` with `xTaskCreateStatic()`
            Find:
            ```
            ^(.*)(xTaskCreate\()(.*),(.*),( )*(.*),(.*),(.*),( )*(&)?(.*)(\));(.*)
            ```
            Replace with:
            ```
            $1static StackType_t taskStack[$6];\n$1static StaticTask_t taskControlBlock;\n$1$11 = xTaskCreateStatic($3,$4, $6,$7,$8, taskStack, &taskControlBlock);
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
            
            static StackType_t taskStack[configMINIMAL_STACK_SIZE];
            static StaticTask_t taskControlBlock;
            myTaskHandle = xTaskCreateStatic(myTask, "My Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, taskStack, &taskControlBlock);
            ```
