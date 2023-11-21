<!--
GS
Nov. 2023

https://stackoverflow.com/q/35425790/4561887
-->


> How to call a static function in one C source code file from another C source code file?


## Summary

1. You shouldn't call a `static` function from another source file. `static` means "I'm not supposed to be used anywhere else." So, if you really need to use that function or variable from another source file, remove `static` from its declaration. 
    1. See the top of the "Details" section below.
1. But if you really must (ex: for unit testing or modifying a 3rd-party library while making minimal changes to it), see the techniques in the section titled **"Techniques to forcefully include a `static` function or variable in another file"**, below.

This answer also answers the question: "When to use `extern` in C?"


## Details

First of all, you shouldn't do this. If you have a function that is used in other source files, it should be _non_`static`, and declared inside a header file, and that header file should be included in the source file where you need it. This is the proper design pattern. You include the header file in each source file that uses the function. 

If you have a function that is only used in _one_ file, it should be declared `static` so that it is _not visible outside that file_, period. The `static` keyword gives a function or variable _internal linkage_, or "file scope" in layman's terms, which means that it is only visible inside the file it is declared in.

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
#include "foo.h"      // most-often used

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

_Tested with `gcc --version` `gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0`._

This is helpful to help you understand when you are having this problem in your own code:

This is an **example build (linker, `ld`) error** if you try to forward declare a `static` function from another file:

```
undefined reference to `counter'
undefined reference to `print_incrementing_number'
```

The linking step is the last step of the build process, and where it tries to find and match function declarations to their compiled definitions in the compiled object `.o` files. If a function was built as `static`, it is not visible outside the file it was defined in, so the linker cannot find it, and you get this error.

**Full build error in C:** the linker (`ld` program) fails to find my `print_incrementing_number()` function because it is `static` and in another source file, so the linker excludes its definition and cannot find it at link time:
```bash
eRCaGuy_hello_world$ c/static_extern_function_include__main.c 
/usr/bin/ld: /tmp/cckelXCL.o: in function `main':
static_extern_function_include__main.c:(.text.startup+0x17): undefined reference to `print_incrementing_number'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x1e): undefined reference to `print_incrementing_number'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x25): undefined reference to `print_incrementing_number'
collect2: error: ld returned 1 exit status
```

**Full build error in C++:**

```bash
eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 static_extern_function_include__main.c static_extern_function_include__module.c -o bin/a && bin/a
/usr/bin/ld: /tmp/cc7tV6Pq.o: in function `main':
static_extern_function_include__main.c:(.text.startup+0x15): undefined reference to `print_incrementing_number()'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x1a): undefined reference to `print_incrementing_number()'
/usr/bin/ld: static_extern_function_include__main.c:(.text.startup+0x1f): undefined reference to `print_incrementing_number()'
collect2: error: ld returned 1 exit status
```

Here is the source code that produces that error: 

`static_extern_function_include__module.c`:
```c
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// Aaaah! Static!
static void print_incrementing_number()
{
    static uint32_t i = 0;
    printf("i = %u\n", i);
    i++;
}

void foo()
{
    print_incrementing_number();
}
```

`static_extern_function_include__main.c`:
```c
void print_incrementing_number(); // forward declaration

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n");

    print_incrementing_number();
    print_incrementing_number();
    print_incrementing_number();

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
1. remove the `static` keyword from their .c file
1. [my preferred choice for enhancing a 3rd-party library] write a non-static wrapper function in the bottom of their .c file for access to static _functions_, and setter and getter functions for access to static _variables_
1. #include your .c file in the bottom of their .c file
1. [my preference for unit testing private `static` C code] #include their .c file in the top of your .c file
1. add a non-static function pointer to the bottom of their .c file

### 2. Alternatives:
1. duplicate their code into your own function in your own file
1. submit a pull request to their library to make the function non-static
1. write a Bash or Python script which automatically removes the `static` keyword from their .c file at compile-time, thereby applying a compile-time patch
