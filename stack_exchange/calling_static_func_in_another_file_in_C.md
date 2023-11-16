<!--
GS
Nov. 2023

https://stackoverflow.com/q/35425790/4561887
-->

> How to call a static function in one C source code file from another C source code file?

First of all, you shouldn't do this. If you have a function that is used in other source files, it should be _non_`static`, and forward-declared inside a header file. Then, you include the header file in each source file that uses the function. If you have a function that is only used in one file, it should be declared `static` so that it is _not visible outside that file_, period. The `static` keyword gives a function or variable _internal linkage_, or "file scope" in layman's terms, which means that it is only visible inside the file it is declared in.

These answers here say that as well:
1. [@Anbu.Sankar](https://stackoverflow.com/a/35425964/4561887)
1. [@vivek thantho](https://stackoverflow.com/a/35426822/4561887)
1. [@Umamahesh P](https://stackoverflow.com/a/35425898/4561887)
1. [@Frodo](https://stackoverflow.com/a/35427118/4561887)
1. [@Teodorico Levoff](https://stackoverflow.com/a/35425948/4561887)

But, there are two cases I can think of where you may need to include a `static` function in another file:
1. You are trying to unit test private `static` functions inside a `.c` source file. 
1. You are trying to enhance some 3rd-party library code while making no or minimal changes to that code. Making zero or minimal changes to 3rd-party library code is especially desired when that code is under active development, and you want to be able to easily upgrade to future versions of that code with*out* having to unweave your changes from it to do so. Take my case, for example, from [my comment here](https://stackoverflow.com/questions/35425790/how-to-call-a-static-function-in-one-c-source-code-file-from-another-c-source-co#comment136602396_35425790):

    > I'm in this situation now. The situation is that I need to enhance some of the FreeRTOS kernel code to inject some extra debugging features. To keep my code modular and outside of the FreeRTOS kernel, however, so that I can easily upgrade FreeRTOS versions, I need to access a private `static` C function in the FreeRTOS kernel, _from outside the file_ in which the `static` C function is defined. So, I think this situation comes up most often when trying to enhance 3rd-party libraries by tapping into their code, but without touching (modifying) their source code. 
    > 
    > Unit testing private `static` functions defined in a `.c` file is another legitimate use-case.

So, if you *really* need to call a `static` function in another file, here are some ways. 


## Background knowledge: `extern` vs `static`

First off, some basic knowledge: the keywords `exern` and `static` are opposites to each other. `extern` means "this variable or function is defined in another file", and `static` means "this variable or function is only visible in this file".

_Functions_ without `static` are `extern` by default, so you don't need to explicitly write `extern` in front of them. But, you can if you want to:
```c
// explicitly `extern`
extern void foo(void);

// same thing, but implicitly `extern`
void foo(void);
```

So, in a header file, when you write a function declaration, you don't need to write `extern` in front of it, because it is `extern` by default. 

_Variables_, on the other hand, are *not* `extern` by default, so you do need to explicitly write `extern` in front of them if you want them to be `extern`.
```c
uint32_t u32;  // this statically allocates a new variable named `u32`

extern uint32_t u32;  // this tells the compiler that `u32` is allocated and 
                      // defined in another file, but needs to be accessible 
                      // inside this file
```



