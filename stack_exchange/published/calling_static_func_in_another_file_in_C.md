<!--
GS
Nov. 2023

https://stackoverflow.com/q/35425790/4561887

My answer: https://stackoverflow.com/a/77527374/4561887
-->


> How to call a static function in one C source code file from another C source code file?


## Summary

1. You shouldn't call a `static` function from another source file. `static` means "I'm not supposed to be used anywhere else." So, if you really need to use that function or variable from another source file, remove `static` from its declaration. 
    1. See the top of the "Details" section below.
1. But if you really must (ex: for unit testing, or modifying a 3rd-party library while making minimal changes to it), see the techniques in the section titled **"Techniques to forcefully include a `static` function or variable in another file"**, below.

This answer also answers the question: "When to use `extern` in C or C++?"


## Details

First of all, you generally shouldn't use a `static` function or variable in another file. If you have a function that is used in other source files, it should be _non_`static`, and declared inside a header file, and that header file should be included in the source file where you need it. This is the proper design pattern. You then include the header file in each source file that uses the function. See the "`#include` vs forward declarations" section below for examples of this. 

If you have a function or variable that is only used in _one_ file, it should be declared `static` so that it is _not visible outside that file_, period. The `static` keyword gives a function or variable _internal linkage_, or "file scope" in layman's terms, which means that it is only visible inside the file it is declared in.

These answers here say that as well:
1. [@Anbu.Sankar](https://stackoverflow.com/a/35425964/4561887)
1. [@vivek thantho](https://stackoverflow.com/a/35426822/4561887)
1. [@Umamahesh P](https://stackoverflow.com/a/35425898/4561887)
1. [@Frodo](https://stackoverflow.com/a/35427118/4561887)
1. [@Teodorico Levoff](https://stackoverflow.com/a/35425948/4561887)

But, there are **two cases I can think of where you may need to include a `static` function in another file:**
1. You are trying to unit test private `static` functions inside a `.c` source file. 
1. You are trying to enhance some 3rd-party library code while making no or minimal changes to that code. Making zero or minimal changes to 3rd-party library code is especially desired when that code is under active development, and you want to be able to easily upgrade to future versions of that code with*out* having to unweave your changes from your copy of it to do so. Take my case, for example, from [my comment here](https://stackoverflow.com/questions/35425790/how-to-call-a-static-function-in-one-c-source-code-file-from-another-c-source-co#comment136602396_35425790):

    > I'm in this situation now. The situation is that I need to enhance some of the FreeRTOS kernel code to inject some extra debugging features. To keep my code modular and outside of the FreeRTOS kernel, however, so that I can easily upgrade FreeRTOS versions, I need to access a private `static` C function in the FreeRTOS [`tasks.c` kernel file], _from outside the file_ in which the `static` C function is defined. So, I think this situation comes up most often when trying to enhance 3rd-party libraries by tapping into their code, but without touching (modifying) their source code. 
    > 
    > Unit testing private `static` functions defined in a `.c` file is another legitimate use-case.

So, if you *really* need to call a `static` function in another file, here are some ways. 


## Background knowledge: 

First off, some basic knowledge: 

### 1. `extern` vs `static`

The keywords `exern` and `static` are opposites of each other. `extern` means "this variable or function is defined in another file", and `static` means "this variable or function is only visible within this scope." Typically, the scope of a `static` variable is within the curly braces `{ }` it is in (typically a function), but if the `static` variable is defined _outside_ of all functions, then it is a `static` _global_ variable, and its scope is _the entire file._ If a function or variable is _non_-`static`, then its scope is _all files in the entire program_, so long as they either: 
1. include the header file where each is declared, or 
1. forward declare the function or variable in the file where they want to use it.

**_Functions_ without `static` are `extern` by default**, so you don't need to explicitly write `extern` in front of them. But, you can if you want to:
```c
// explicitly `extern`
extern void foo(void);

// same thing, but implicitly `extern`
void foo(void);
```

So, in a header file, when you write a function declaration, you don't need to write `extern` in front of it, because it is `extern` by default. 

**_Variables_, on the other hand, are *not* `extern` by default**, so you do need to explicitly write `extern` in front of them if you want them to be `extern`.
```c
uint32_t u32;  // this statically allocates a new variable named `u32`, because
               // `extern` is NOT implied by default

extern uint32_t u32;  // this tells the compiler that `u32` is allocated and 
                      // defined in another file, but needs to be accessible 
                      // inside this file
```

Static global functions or variables in `foo.c`:
```c
// this function is only visible inside this file since it is `static`
static void foo(void) {
    // your code here
}

// this global variable is only visible inside this file since it is `static`
static uint32_t u32;
```


### 2. `#include` vs forward declarations

Assume you have the following source file. You'd like to use function `foo()` and variable `u32` outside this file:

`foo.c`:
```c
// this function can be used **outside** this file, if forward declared in 
// the file where it will be used, before it is used, since it is NOT `static`
void foo(void) {
    // your code here
}

// this global variable can be used and shared **outside** this file, if 
// forward declared in the file where it will be used, before it is used, 
// since it is NOT `static`
uint32_t u32;
```

To get access to a _non-`static`_ function or variable defined in another file, you have two options:

1. [Ok] Forward declare its existence like this in the file where you want to use it:

    `main.c`:

    ```c
    // Forward declaration of the function `foo`, so you can use it in this 
    // file. 
    // - Remember: `extern` is automatically implicitly implied for functions!
    void foo();
    // same thing, but explicitly `extern`
    extern void foo();

    // Forward declaration of the variable `u32`, which is defined in another 
    // file, so you can use it in this file.
    // - Remember: `extern` is NOT automatically implicitly implied for 
    //   variables, so you must **explicitly** write `extern` here.
    extern uint32_t u32;

    // Now you can call foo() in this file, and also use variable `u32` from the 
    // other file.
    int main()
    {
        foo();
        printf("u32 = %u\n", u32);
        u32 = 123;

        return 0;
    }
    ```

1. [Better] Use an `#include "foo.h"` statement:

    A **more conventional and recommended approach,** however, is to put the forward declarations into a `.h` header file, and then include the header file where you want access to these functions and variables. 
    
    Here is an example `foo.h` header file to do this:

    `foo.h`:
    ```c
    #pragma once

    // Forward declare the `foo()` function defined in foo.c; `extern` is 
    // automatically implied here for functions, so you don't have to write it.
    void foo();  

    // Forward declare the existence of the `uint32_t u32` variable allocated 
    // and defined in `foo.c`.
    extern uint32_t u32;
    ```

    Then, you can just include the header file and those forward declarations get copied into your file at compile-time by the preprocessor:

    `main.c`:
    ```c
    #include "foo.h"

    // Now you can call foo() in this file, and also use variable `u32` from the 
    // other file, just like before when we manually wrote the forward 
    // declarations here!
    int main()
    {
        foo();
        printf("u32 = %u\n", u32);
        u32 = 123;

        return 0;
    }
    ```

#### Review/summary

So, any of these will work: 

`main.c`:
```c
// For both functions and variables
#include "foo.h"      // most-often used / most-recommended

// or, for functions:
void foo();           // forward declaration with implicit `extern`
// or
extern void foo();    // forward declaration with optional explicit `extern`

// or, for variables:
extern uint32_t u32;  // forward declaration with **required** explicit `extern`


// Now you can call foo() in this file, and also use variable `u32` from the 
// other file.
int main()
{
    foo();
    printf("u32 = %u\n", u32);
    u32 = 123;

    return 0;
}
```


## Example error if you try to call a `static` function or variable from another file

_Tested with `gcc --version` `gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0`._ To run these `gcc` build commands on Windows, use the MSYS2 terminal. See my full setup instructions here: [Installing & setting up MSYS2 from scratch, including adding all 7 profiles to Windows Terminal](https://stackoverflow.com/a/77407282/4561887).

This is helpful to help you understand when you are having this problem in your own code:

This is an **example build (linker, `ld`) error** if you try to forward declare or include a `static` function or variable from another file:

```
undefined reference to `counter'
undefined reference to `print_incrementing_number'
```

The linking step is the last step of the build process, and where it tries to find and match function declarations to their compiled definitions in the compiled object `.o` files. If a function or variable was built as `static`, it has "static linkage", which means that is not visible outside the file it was defined in, so the linker cannot find it, and you get this error. 

The linker (`ld` program) fails to find my `print_incrementing_number()` function and `uint32_t counter` variable. If you want to try running the commands, this is at commit `11430a3cb3b298f26d3763e4a7224a7d610751c1` in my [eRCaGuy_hello_world](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world) repo.

**Full build error in C:** 

```bash
eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 static_extern_function_include__main.c static_extern_function_include__module.c -o bin/a && bin/a
/usr/bin/ld: /tmp/ccKPOHqx.o: warning: relocation against `counter' in read-only section `.text.startup'
/usr/bin/ld: /tmp/ccKPOHqx.o: in function `main':
static_extern_function_include__main.c:(.text.startup+0x1b): undefined reference to `print_incrementing_number'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x21): undefined reference to `counter'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x37): undefined reference to `print_incrementing_number'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x3d): undefined reference to `counter'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x53): undefined reference to `print_incrementing_number'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x59): undefined reference to `counter'
/usr/bin/ld: warning: creating DT_TEXTREL in a PIE
collect2: error: ld returned 1 exit status
```

**Full build error in C++:**

```bash
eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 static_extern_function_include__main.c static_extern_function_include__module.c -o bin/a && bin/a
/usr/bin/ld: /tmp/ccAn3aKq.o: warning: relocation against `counter' in read-only section `.text.startup'
/usr/bin/ld: /tmp/ccAn3aKq.o: in function `main':
static_extern_function_include__main.c:(.text.startup+0x19): undefined reference to `print_incrementing_number()'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x1f): undefined reference to `counter'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x33): undefined reference to `print_incrementing_number()'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x39): undefined reference to `counter'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x4d): undefined reference to `print_incrementing_number()'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x53): undefined reference to `counter'
/usr/bin/ld: warning: creating DT_TEXTREL in a PIE
collect2: error: ld returned 1 exit status
```

Here is the source code that produces that error: 

`static_extern_function_include__module.c`:
```c
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

static uint32_t counter = 0;

static void print_incrementing_number()
{
    printf("counter = %u\n", counter);
    counter++;
}

void foo()
{
    print_incrementing_number();
}
```

`static_extern_function_include__main.c`:
```c
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

void print_incrementing_number(); // forward function declaration
extern uint32_t counter;          // forward variable declaration

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n");

    print_incrementing_number();
    printf("  counter = %u\n", counter);
    print_incrementing_number();
    printf("  counter = %u\n", counter);
    print_incrementing_number();
    printf("  counter = %u\n", counter);

    return 0;
}
```

Build command:
```bash
# in C
gcc -Wall -Wextra -Werror -O3 -std=gnu17 static_extern_function_include__main.c static_extern_function_include__module.c -o bin/a && bin/a

# in C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 static_extern_function_include__main.c static_extern_function_include__module.c -o bin/a && bin/a
```


## The fixes: techniques to forcefully include a `static` function or variable in another file


### 1. Possible solutions:

1. [Preferred choice if you intend the function and variable to be used elsewhere] **remove the `static` keyword** from the `.c` file:

    Go to `static_extern_function_include__module.c` and remove the `static` keyword from the function and variable declarations, so you have this:
    ```c
    uint32_t counter = 0;

    void print_incrementing_number()
    {
        printf("counter = %u\n", counter);
        counter++;
    }
    ```

    Now it builds and runs. Here is my command and output:
    ```bash
    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 static_extern_function_include__main.c static_extern_function_include__module.c -o bin/a && bin/a
    Hello World.
    counter = 0
      counter = 1
    counter = 1
      counter = 2
    counter = 2
      counter = 3
    ```

    The build commands for all other techniques below are exactly the same as just above unless stated otherwise.

1. [My preferred choice for enhancing a 3rd-party library] **write a non-static wrapper function in the bottom of their `.c`** file for access to static _functions_, and setter and getter functions for access to their static _variables_:

    At the bottom of their `.c` file, add your custom wrappers and setters/getters, like this:

    `static_extern_function_include__module.c`:
    ```c
    // ------- their original code left as-is -------
 
    static uint32_t counter = 0;

    static void print_incrementing_number()
    {
        printf("counter = %u\n", counter);
        counter++;
    }

    void foo()
    {
        print_incrementing_number();
        // a bunch of other library code here
    }

    // ------- your custom wrappers and setters/getters -------

    void print_incrementing_number_wrapper()
    {
        print_incrementing_number();
    }

    void set_counter(uint32_t new_counter)
    {
        counter = new_counter;
    }

    uint32_t get_counter()
    {
        return counter;
    }
    ```

    In your `.c` file, you can now forward declare and use these custom wrappers and setters/getters. 
    
    Even better, make a wrapper `.h` file too: 

    `static_extern_function_include__module_wrapper.h`:
    ```c
    #pragma once

    #include <stdint.h>  // For `uint8_t`, `int8_t`, etc.

    void print_incrementing_number_wrapper();
    void set_counter(uint32_t new_counter);
    uint32_t get_counter();
    ``` 

    And in your `.c` file, include and use the wrapper header:

    ```c
    #include "static_extern_function_include__module_wrapper.h"
    
    #include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
    #include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
    #include <stdio.h>   // For `printf()`

    // Using the wrapper
    int main()
    {
        printf("Hello World.\n");

        print_incrementing_number_wrapper();
        printf("  counter = %u\n", get_counter());
        print_incrementing_number_wrapper();
        printf("  counter = %u\n", get_counter());
        print_incrementing_number_wrapper();
        printf("  counter = %u\n", get_counter());

        return 0;
    }
    ```

1. **Add non-`static` pointers** to their functions and variables in the bottom of their `.c` file:

    Instead of adding wrapper functions and setters/getters, you can use non-static pointer variables instead: 

    `static_extern_function_include__module.c`:
    ```c
    // ------- their original code left as-is -------
 
    static uint32_t counter = 0;

    static void print_incrementing_number()
    {
        printf("counter = %u\n", counter);
        counter++;
    }

    void foo()
    {
        print_incrementing_number();
        // a bunch of other library code here
    }

    // ------- your custom, non-static pointer variables -------

    typedef void (*void_void_func_ptr_t)(void);
    
    void_void_func_ptr_t print_incrementing_number_ptr = 
        print_incrementing_number;

    uint32_t *counter_ptr = &counter;
    ```

    Now, forward declare these `extern` pointer variables in your `.c` file, or make a header file like this:

    `static_extern_function_include__module_ptrs.h`:
    ```c
    #pragma once

    #include <stdint.h>  // For `uint8_t`, `int8_t`, etc.

    typedef void (*void_void_func_ptr_t)(void);

    // forward pointer variable declarations
    extern void_void_func_ptr_t print_incrementing_number_ptr;
    extern uint32_t *counter_ptr;
    ```

    And in your `.c` file, include and use the pointer header:

    ```c
    #include "static_extern_function_include__module_ptrs.h"

    #include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
    #include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
    #include <stdio.h>   // For `printf()`

    // Using the pointers
    int main()
    {
        printf("Hello World.\n");

        print_incrementing_number_ptr();
        printf("  counter = %u\n", *counter_ptr);
        print_incrementing_number_ptr();
        printf("  counter = %u\n", *counter_ptr);
        print_incrementing_number_ptr();
        printf("  counter = %u\n", *counter_ptr);

        return 0;
    }
    ```

1. [Least intrusive / best to minimize changes to someone else's library files] **`#include` your custom `.h` or `.c` file in the bottom of their `.c` file**

    If you want to keep the bottom of their `.c` file as clean as possible, then you can do that by adding a **single `#include` statement at the bottom of their `.c` file**, like this. Note that the extension doesn't really matter. You can use any extension you want. Here, I use `_extension.c` to indicate I am extending this module with my own customizations:

    ```c
    // ------- their original code left as-is -------
    // ...

    // ------- your custom include line at the very bottom -------
    // Including a `.c` file is a bit unconventional, but it works just fine.
    // You can think of the pre-processor as a type of code generator since
    // it just copies and pastes stuff around.
    #include "static_extern_function_include__module_extensions.c"
    ```

    Now, put the necessary wrappers or pointers from the examples above into this extension file included above. Here, I'll use the wrapper functions and setters/getters from the 2nd example above:

    `static_extern_function_include__module_extensions.c`:
    ```c
    void print_incrementing_number_wrapper()
    {
        print_incrementing_number();
    }

    void set_counter(uint32_t new_counter)
    {
        counter = new_counter;
    }

    uint32_t get_counter()
    {
        return counter;
    }
    ```

    Now in your `.c` file, just do what you did for the 2nd example above, and include and use the wrapper header again, like normal:

    ```c
    #include "static_extern_function_include__module_wrapper.h"
    
    #include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
    #include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
    #include <stdio.h>   // For `printf()`

    // Using the wrapper
    int main()
    {
        printf("Hello World.\n");

        print_incrementing_number_wrapper();
        printf("  counter = %u\n", get_counter());
        print_incrementing_number_wrapper();
        printf("  counter = %u\n", get_counter());
        print_incrementing_number_wrapper();
        printf("  counter = %u\n", get_counter());

        return 0;
    }
    ```

    Note: as of later versions of FreeRTOS, this is now possible! They have even provided "hooks" to do this right inside their main library code! See here for example, in V10.6.1 in the bottom of `tasks.c`: https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/V10.6.1/tasks.c#L5514-L5534: 

    ```c
    /* Code below here allows additional code to be inserted into this source file,
    * especially where access to file scope functions and data is needed (for example
    * when performing module tests). */

    #ifdef FREERTOS_MODULE_TEST
        #include "tasks_test_access_functions.h"
    #endif


    #if ( configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H == 1 )

        #include "freertos_tasks_c_additions.h"

        #ifdef FREERTOS_TASKS_C_ADDITIONS_INIT
            static void freertos_tasks_c_additions_init( void )
            {
                FREERTOS_TASKS_C_ADDITIONS_INIT();
            }
        #endif

    #endif /* if ( configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H == 1 ) */
    ```

    I'll be using that now. Older versions of FreeRTOS did _not_ have this. 

1. [My preference for unit testing private `static` C code] **`#include` the entire `.c` file of interest in the _top_ of your `.c` file:**

    To unit test or get access to a ton of private `static` functions and variables from a `.c` file, just include the `.c` file near the _top_ of your `.c` file. 

    The pre-processor will then copy/paste that entire included file into the top of your file. Imagine that has happened, and write your code from there. 

    You can access all of the private `static` data in your `.c` file because it _is in_ your `.c` file now. 

    I won't show an explicit example, for brevity, but you get the point. 


### 2. Alternatives:

Here are some other alternatives to consider:

1. Duplicate the `static` code into your own function in your own file.

    ie: just copy-paste it. I generally recommend against this, however, as maintaining duplicate code is a horrible waste of time, and it gets out-of-sync easy.

    If the function is 3 lines and it's only 1 function, sure, do this. But if it's 4 lines or 2 functions, choose one of the other options above instead, to avoid duplicate code.

1. Submit a pull request to their library to make the functions or variables of interest non-`static`.

    While this is a great idea, just beware it can take weeks to months to years, or never, to get an upstream developer to accept your pull request. So, with that in mind, do this, yes, but meanwhile also just choose one of the options above to get your own work done meanwhile. 

1. Write a Bash or Python script which automatically removes the `static` keyword from their `.c` file at compile-time, thereby applying a compile-time patch. 

    This is actually a really effective solution, and sometimes the best. You can, for example:

    1. manually make the necessary changes, then produce a `git diff` type `.patch` file which you apply at build-time, _or_ 
    1. write a custom find-and-replace type script which does some simple changes for you, such as removing `static` from the variables and functions you need access to. 

    If you choose the latter option, I recommend having your build system copy the file first and have your build script modify this untracked copy. This way your original file is not modified, and `git status` and `git diff` don't become "dirty" (having uncommitted changes) each time you build.
