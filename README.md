[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2FElectricRCAircraftGuy%2FeRCaGuy_hello_world&count_bg=%2379C83D&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=views+%28today+%2F+total%29&edge_flat=false)](https://hits.seeyoufarm.com)

# eRCaGuy_hello_world
"hello world" demos &amp; templates for various languages, incl. `gcc` build commands for C &amp; C++ 

See also my [eRCaGuy_hello_world_data](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world_data) project. 

By Gabriel Staples  
www.ElectricRCAircraftGuy.com


# Table of Contents
<details>
<summary><b>(click to expand)</b></summary>
<!-- MarkdownTOC -->

1. [Status:](#status)
1. [For beginners and experts alike: not your average "hello world" examples](#for-beginners-and-experts-alike-not-your-average-hello-world-examples)
1. [Examples of more advanced principles taught herein:](#examples-of-more-advanced-principles-taught-herein)
    1. [1. C and C++:](#1-c-and-c)
        1. [Additional C and C++ build notes \(ex: w/`gcc` or `clang` compilers\):](#additional-c-and-c-build-notes-ex-wgcc-or-clang-compilers)
    1. [2. Python:](#2-python)
    1. [3. markdown:](#3-markdown)
    1. [4. bash:](#4-bash)
1. [File Structure:](#file-structure)
1. [Changelog](#changelog)
    1. [\[v0.3.0\] - 2020-05-23](#v030---2020-05-23)
    1. [\[v0.2.0\] - 2020-04-18](#v020---2020-04-18)
    1. [\[v0.1.0\] - 2020-04-14](#v010---2020-04-14)

<!-- /MarkdownTOC -->
</details>


<a id="status"></a>
# Status:
1. Many solid C & C++ demos are done and work! 
1. A Python demo also is in place to show how to parse a YAML file. 

See the `tree` output below to see the file/folder structure.


<a id="for-beginners-and-experts-alike-not-your-average-hello-world-examples"></a>
# For beginners and experts alike: not your average "hello world" examples

Note that these are NOT just your standard "simple" hello world demos for absolute beginners. Rather, they are simple enough for beginners but also contain some advanced techniques and tips & tricks to act as good reminders or teaching for more expert programmers too. I, myself, regularly reference my own examples here to remind myself of some of these details which are easy to forget. There's no sense stressing about trying to remember everything. _Instead of trying to remember everything, just remember where to look (here in this case)_. 


<a id="examples-of-more-advanced-principles-taught-herein"></a>
# Examples of more advanced principles taught herein:

<a id="1-c-and-c"></a>
## 1. C and C++:
1. How to generate intermediate build files, including .ii, .s, and .o.
    1. See ["cpp/hello_world.cpp"](cpp/hello_world.cpp)
1. How to make a single file compile in both C and C++ by using the `#ifdef __cplusplus` `extern "C" {` brace trick
    1. See ["c/hello_world.c"](c/hello_world.c)
1. How to use a forward declaration of `printf` rather than including `stdio.h` to make it link
    1. See ["c/hello_world.c"](c/hello_world.c)
1. How to do cross-platform sleep in Windows or Linux
    1. See ["c/hello_world_sleep.c"](c/hello_world_sleep.c)
1. A reminder to use `-Wall -Werror` for better code safety and quality
    1. See ["c/hello_world.c"](c/hello_world.c)
1. How to use `g3` for full debugging info
    1. See ["c/hello_world.c"](c/hello_world.c) and
    1. ["c/hello_world_sleep.c"](c/hello_world_sleep.c)
1. How to specify the C or C++ version you are compiling for, such as `c90`, `c99`, or `c11` (C 2011), or `c++98`, `c++03` (C++ 2003), or `c++11` (C++ 2011)
    1. See ["c/hello_world.c"](c/hello_world.c) and
    1. ["c/hello_world_sleep.c"](c/hello_world_sleep.c)
1. How to pass entire functions or curly-brace-scoped `{ }` code blocks, as though they were a single parameter, into a macro to be evaluated
    1. See ["cpp/macro_practice/advanced_macro_usage_pass_in_entire_func.cpp"](cpp/macro_practice/advanced_macro_usage_pass_in_entire_func.cpp)
1. How to do integer rounding UP, DOWN, and to NEAREST whole integer during division using 3 different techniques: 1) macros, 2) gcc/clang statement expressions, and 3) C++ function templates. This also is a great unit test example using simple hand-written unit tests.
    1. See ["c/rounding_integer_division/"](c/rounding_integer_division/) directory
    1. If you'd like to see how to use googletest (gtest) and googlemock (gmock) instead of writing custom unit tests, see my other project here instead: https://github.com/ElectricRCAircraftGuy/eRCaGuy_gtest_practice. It also acts as a good demo of how to get up and running quickly with Google's Bazel build system.
1. Witness that the C++ `std::unordered_map<T_key, T_value>` unordered map (hash table) class automatically implicitly creates a new key/value pair each time you attempt to read OR write to a value (or any members of a complex value, such as a `struct` or `class`) which belongs to a **non-existing key**! In other words, reading or writing any key/value which does NOT yet exists causes `std::unordered_map<>` to automatically, dynamically, generate it right on the spot for you to access it! This is confusing behavior at first, as it happens implicitly behind the scenes, so it needs to be understood. _Once understood, it is a powerful feature to use, but a one or two-line comment to exlain that you intend dynamic allocation to happen, above any lines in production code where you use this, would be wise._
    1. See ["cpp/unordered_map_practice/unordered_map_hash_table_implicit_key_construction_test.cpp"](cpp/unordered_map_practice/unordered_map_hash_table_implicit_key_construction_test.cpp)
1. Case-insensitive `strncmp()` function, with unit tests.
    1. See ["c/onlinegdb--strncmpci.c"](c/onlinegdb--strncmpci.c)
1. Example of how to manually write unit tests.
    1. See ["c/onlinegdb--strncmpci.c"](c/onlinegdb--strncmpci.c)
    1. Note: for Google Test (gtest/gmock) examples, including how to use the [Bazel](https://bazel.build/) build system, see my repo here instead: https://github.com/ElectricRCAircraftGuy/eRCaGuy_gtest_practice.
1. How to use a `const` reference to a vector, with a default parameter, as an input param to a function!
    1. See ["cpp/onlinegdb--const_reference_to_vector__default_func_parameter.cpp"](cpp/onlinegdb--const_reference_to_vector__default_func_parameter.cpp)
1. How to call command-line system calls in C and C++, read piped input from `stdin`, and read command-line output from called process from its `stdout`:
    1. [StackOverflow.com: how to read from stdout in C](https://stackoverflow.com/q/24214038/4561887)
    1. [StackOverflow.com: C: Run a System Command and Get Output?](https://stackoverflow.com/q/646241/4561887)
    1. [StackOverflow.com: How can I run an external program from C and parse its output?](https://stackoverflow.com/q/43116/4561887)
    1. [StackOverflow.com: Capturing stdout from a system() command optimally](https://stackoverflow.com/q/125828/4561887)
    1. [the most-thorough C++ answer I think] [StackOverflow.com: How do I execute a command and get the output of the command within C++ using POSIX?](https://stackoverflow.com/q/478898/4561887)
1. Advanced bit-masks and bit-shifting. 
    1. See ["cpp/process_10_bit_video_data.cpp"](cpp/process_10_bit_video_data.cpp)
    1. See also the problem statement and my answer, with other references, on Stack Overflow here: [Stack Overflow: Add bit padding (bit shifting?) to 10bit values stored in a byte array](https://stackoverflow.com/a/66678338/4561887).
1. Weak functions (functions with attribute `weak`): prove to myself that weak functions which are declared but not defined really do have addresses equal to nil (ie: zero, or `0`), as this is how the Arduino `serialEvent()` function works and is implemented.
    1. See ["cpp/check_addr_of_weak_undefined_funcs.cpp"](cpp/check_addr_of_weak_undefined_funcs.cpp). 
    1. See also my Stack Overflow answer here: [Arduino “SerialEvent” example code doesn't work on my Arduino Nano. I can't receive serial data. Why?](https://stackoverflow.com/questions/67013619/arduino-serialevent-example-code-doesnt-work-on-my-arduino-nano-i-cant-rece/67016917#67016917).
    1. gcc `weak` function attribute: https://gcc.gnu.org/onlinedocs/gcc-3.2/gcc/Function-Attributes.html
        > weak
        > 
        > The `weak` attribute causes the declaration to be emitted as a weak symbol rather than a global. This is primarily useful in defining library functions which can be overridden in user code, though it can also be used with non-function declarations. Weak symbols are supported for ELF targets, and also for a.out targets when using the GNU assembler and linker.
1. Empirically measure the max _thread stack size_ permitted on your architecture, in C OR C++. See:
    1. My answer on Stack Overflow here: [Stack Overflow: C/C++ maximum stack size of program](https://stackoverflow.com/a/64085509/4561887)
    1. [c/onlinegdb--empirically_determine_max_thread_stack_size.md](c/onlinegdb--empirically_determine_max_thread_stack_size.md)
    1. [c/onlinegdb--empirically_determine_max_thread_stack_size_Bruno_Haible.c](c/onlinegdb--empirically_determine_max_thread_stack_size_Bruno_Haible.c)
    1. [c/onlinegdb--empirically_determine_max_thread_stack_size_GS_version.c](c/onlinegdb--empirically_determine_max_thread_stack_size_GS_version.c)
1. Practice using `void *` function arguments to pass in ANY data type, such as a regular `uint32_t`, to a function. 
    1. `void *` is also the _required_ input parameter `arg` type, passed by [`pthread_create()`][pthread_create] to the `start_routine` function, so that `arg` can be ANY type! This allows the [Linux `pthread_create()` function][pthread_create] to be a _generic function prototype_ which allows _generic callback functions_, to be called by the thread, and which shall receive _generic input parameters._ GOING FURTHER: The cool thing about this is that a `void *` input parameter can literally be A POINTER TO ANY DATA TYPE, so it could even be to a struct containing more function pointers, or a struct containing a bunch of parameters, etc. In this way, a _generic function prototype_ containing a _single_ `void *` input param can actually "wrap", or contain, a ton of input params. There are no limits to what you can pass with this--it's all up to your imagination and ingenuity and desires.
        1. My example usage of this, passing a simple `uint32_t` type via a `void *` input parameter: [c/onlinegdb--empirically_determine_max_thread_stack_size_GS_version.c](c/onlinegdb--empirically_determine_max_thread_stack_size_GS_version.c)
        1. See also my answer on Stack Overflow here: [Stack Overflow: C/C++ maximum stack size of program](https://stackoverflow.com/a/64085509/4561887)
1. Learn 3 techniques to read individual bytes out of variables of any type in gcc C and C++. 
    1. You can use 1) unions and "type punning", 2) raw pointers, or 3) bit-masks and bit shifting!
    1. See ["c/type_punning.c"](c/type_punning.c)
    1. See also my detailed answer and explanations here: [Stack Overflow: Portability of using union for conversion - my answer: "Using Unions for "type punning" is fine in C, and fine in gcc's C++ as well (as a gcc [g++] extension). But, "type punning" via unions has hardware architecture endianness considerations."](https://stackoverflow.com/questions/67206482/portability-of-using-union-for-conversion/67206563#67206563).


<a id="build-notes"></a>
<a id="additional-c-and-c-build-notes-ex-wgcc-or-clang-compilers"></a>
### Additional C and C++ build notes (ex: w/`gcc` or `clang` compilers):

1. Use `-Wwarning-name` to turn ON build warning "warning-name", and `-Wno-warning-name` to turn OFF build warning "warning-name". `-W` turns a warning ON, and `-Wno-` turns a warning OFF. Here's what gcc has to say about it (source: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html; emphasis added):

    > You can request many specific warnings with options beginning with `-W`, for example `-Wimplicit` to request warnings on implicit declarations. Each of these specific warning options also has a _negative form_ beginning `-Wno-` to turn off warnings; for example, `-Wno-implicit`. This manual lists only one of the two forms, whichever is _not_ the default.

1. Instead of `-g3`, use `-ggdb` to build debug information specifically for the GNU gdb debugger. If using the clang (LLVM) compiler instead of gcc, you may also use `-glldb` to build debug information specifically for the clang LLDB debugger. Note that if you use `-glldb`, it usually builds debug symbols and information which works just fine with gdb too, so you can generally use either debugger with the same built symbols in that case. 
1. Use `-Wall -Wextra -Werror` (which is a good idea) to see all warnings and to convert all warnings to errors, to make you write better code. Some people may leave off `-Wextra`, and just use `-Wall -Werror`. Others may also like to add `-Wpedantic` to that list (now it's `-Wall -Wextra -Wpedantic -Werror`) to enforce ISO C and ISO C++ standards, but other people or code-bases will explicitly turn OFF pedantic with `-Wno-pedantic` to explicitly DISABLE pedantic (ISO standards) checks and ALLOW compiler extensions. Personally, I prefer to leave compiler extensions ENABLED (meaning: do NOT use `-Wpedantic`), as compiler extensions are very frequently used and very useful, especially in small, embedded, low-level and hardware-centric systems such as microcontrollers. 
    - In other words, I recommend that you DO use `-Wall -Wextra -Werror` but that you NOT use `-Wpedantic`, but if you'd like to use `-Wpedantic` as well, you may. See just below for additional details.
    - For details on which warning flags `-Wall` and `-Wextra` each turn on, refer to the gcc user manual here (https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html), and search the page for these warnings, or just scroll partway down. There's a nice list detailing what individual warning flags are under each (`-Wall`, and `-Wextra`).
1. Add the `-Wpedantic` or `-pedantic` (same thing) build flag to enforce strict ISO C or ISO C++ standards and "reject all programs that use forbidden extensions". Or, conversely, add `-Wno-pedantic` to ENABLE extensions and turn a previously-set `-Wpedantic` back OFF. `-Wpedantic` NOT being on is the default. See gcc's user manual section on Warning Options, for example, as well as the bullet just above, for details: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html. 
    - Some people want strict ISO C and C++ functionality only. They use `-Wpedantic`. 
    - Some libraries REQUIRE compiler extensions and explicitly have `-Wno-pedantic` set for the library to *enable* compiler extensions and *disable* any previously-set `-Wpedantic` flags. Sometimes this is just for certain files which require exceptions to use certain compiler extensions. 
    - Others rely on compiler extensions and do NOT use `-Wpedantic`. I am in this latter category and prefer NOT to use `-Wpedantic`, so that I CAN use gcc (or clang) compiler extensions. They are good. They are safe. They are helpful. They just may not be quite as portable across compilers is all, though from gcc to clang and back again, you are usually ok to use them, since clang strives to be gcc-compatible _by design_ (see http://clang.llvm.org/: clang strives to be gcc compatible: "End-User Features" they advertise include: "GCC compatibility"). 
    - See also my notes about `-Wpedantic` in the previous higher-level bullet just above this one. 
1. clang, but NOT gcc, also has a `-Weverything` option which _appears_ to include things such as `-Wpedantic`. You can test it here: https://godbolt.org/z/qcYKd1. Notice the `-Wvla-extension` warning we get since we are relying on a C99 extension in C++ in this case, and we have `-Weverything` set. We get the same warning if we just use `-Wpedantic`, as shown here: https://godbolt.org/z/M9ahE4, indicating that `-Weverything` does in fact include `-Wpedantic`. We get _no warning_ if we have neither of those flags set: https://godbolt.org/z/j8sfsY. <s>Despite `-Weverything` existing and working in clang, however, I can find no documentation whatsoever on its existence, neither in the clang man pages nor in the online manual here: https://clang.llvm.org/docs/DiagnosticsReference.html.</s>
    - Note there is also a clang (at least) option for `-Wc99-extensions` to allow them, or `-Wno-c99-extensions` to disallow them. Source: https://clang.llvm.org/docs/DiagnosticsReference.html#wc99-extensions.
    - UPDATE: the bottom of the main clang documentation index page: https://clang.llvm.org/docs/index.html, under the "Indices and tables" section at the very bottom, has a "Search Page" link. Using that link, here is my search for "-Weverything": https://clang.llvm.org/docs/search.html?q=-Weverything, which brings me to the official documentation here!: https://clang.llvm.org/docs/UsersManual.html?highlight=weverything#cmdoption-weverything. Done! There it is! 
        - **See my answer here:** https://stackoverflow.com/questions/64147706/what-does-the-clang-compilers-weverything-option-include-and-where-is-it-doc/64147755#64147755. Clang does NOT recommend using `-Weverything`! They say it's better to use just `-Wall -Wextra` instead. See their quote here (emphasis added): 

            > Since `-Weverything` enables every diagnostic, we generally **don’t recommend using it.** **`-Wall -Wextra` are a better choice for most projects.** Using `-Weverything` means that updating your compiler is more difficult because you’re exposed to experimental diagnostics which might be of lower quality than the default ones. If you do use `-Weverything` then we advise that you address all new compiler diagnostics as they get added to Clang, either by fixing everything they find or explicitly disabling that diagnostic with its corresponding `Wno-` option.

<a id="2-python"></a>
## 2. Python:
1. How to use the special Python `__slots__` list inside a class to reduce RAM usage during run-time. 
    1. Also, learn about and use _class variables_ vs. _instance variables_, _private variables_ vs _public variables_, and _internal Python variables_ surrounded by double underscores (`__some_var__`). Also practice passing and using _list args_ to a function (ex: as `*args`), and _keyword key:value dict args_ to a function as well (ex: as `**kwargs`).
    1. See ["python/slots_practice/slots_practice.py"](python/slots_practice/slots_practice.py).
1. How to create, parse, and print YAML files. How to find the directory path a called Python file is in.
    1. See ["python/yaml_import/import_yaml_test.py"](python/yaml_import/import_yaml_test.py) and other files in that directory.
1. How to autogenerate C or C++ headers or code using Python. 
    1. See ["python/autogenerate_c_or_cpp_code.py"](python/autogenerate_c_or_cpp_code.py) and the C or C++ header file it auto-generates: ["python/autogenerated/myheader.h"](python/autogenerated/myheader.h).
1. File [python/raw_bytes_practice.py](python/raw_bytes_practice.py) contains:
    1. How to convert a list of integers to bytes.
    1. How to convert bytes back to a list of integers.
    1. Decoding a bytes buffer into a UTF-8 string.
    1. Decoding a bytes buffer into an ASCII string.
    1. Decoding a bytes buffer into a UTF-8 or ASCII string while replacing invalid chars with the 4 char string sequence `"\xhh"` where `hh` is the valid hex char sequence, as a string (via the `errors='backslashreplace'` argument to the bytes `decode()` method).
    1. Converting a bytes buffer into a full hex string.
    1. Converting a full hex string back into a bytes buffer.
    1. Also demonstrated in this file:
        1. `textwrap.dedent()`
        1. New Python "f" format strings. See: https://realpython.com/python-f-strings/.
        1. `time.sleep()`
        1. Exception handling with `try` `except` `else`.
1. Image manipulation:
    1. How to essentially get the equivalent of GIMP's `Colors --> Auto --> White Balance` feature:
        1. [python/auto_white_balance_img.py](python/auto_white_balance_img.py)
        1. See also my answer on Stack Overflow here for a demonstration and more details: [How do I do the equivalent of Gimp's Colors, Auto, White Balance in Python-Fu?](https://stackoverflow.com/questions/48268068/how-do-i-do-the-equivalent-of-gimps-colors-auto-white-balance-in-python-fu/67343271#67343271).

<a id="3-markdown"></a>
## 3. markdown:
1. [github_readme_center_and_align_images.md](markdown/github_readme_center_and_align_images.md): show how to insert and center, align left, align right, etc. images in GitHub readmes in markdown. Ex: resize this image to 15% auto-resizing width, and:

**Align left:**
<p align="left" width="100%">
    <img width="15%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

**Align center:**
<p align="center" width="100%">
    <img width="15%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

**Align right:**
<p align="right" width="100%">
    <img width="15%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

**6 images in a row:**
<p align="center" width="100%">
    <img width="15%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="15%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="15%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="15%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="15%" src="https://i.stack.imgur.com/RJj4x.png"> 
    <img width="15%" src="https://i.stack.imgur.com/RJj4x.png"> 
</p>

<a id="4-bash"></a>
## 4. bash:
1. How to obtain the full file path, full directory, and base filename of any script being run itself.
    1. See: ["bash/get_script_path.sh"](bash/get_script_path.sh)
    1. See also [my answer online on Stack Overflow, here](https://stackoverflow.com/questions/59895/how-to-get-the-source-directory-of-a-bash-script-from-within-the-script-itself/60157372#60157372).


<a id="file-structure"></a>
# File Structure:
(Output of `tree`)

```
$ tree
.
├── arduino
│   └── todo.txt
├── awk
│   ├── awk_hello_world_SAMPLE_OUTPUT.txt
│   ├── awk_hello_world.sh
│   ├── awk_syntax_tests.sh
│   └── input_file_1.txt
├── bash
│   ├── get_script_path.sh
│   ├── Link to ElectricRCAircraftGuy--PDF2SearchablePDF [THIS IS A SOLID BASH EXAMPLE!].desktop
│   ├── Link to PDF2SearchablePDF--pdf2searchablepdf.sh at master · ElectricRCAircraftGuy--PDF2SearchablePDF.desktop
│   ├── practice
│   │   ├── read_arrays.sh
│   │   └── README.md
│   ├── README.md
│   └── source_and_export
│       └── source_and_export.sh
├── c
│   ├── c - Where do we use .i files and how do we generate them? - Stack Overflow.desktop
│   ├── hello_world
│   ├── hello_world.c
│   ├── hello_world_sleep
│   ├── hello_world_sleep.c
│   ├── Link to c - Prototype of printf and implementation - Stack Overflow%%%%%+ [MY OWN ANS!].desktop
│   ├── Link to c - Where do we use .i files and how do we generate them - Stack Overflow%%%%% [MY OWN ANS!].desktop
│   ├── Link to Using the GNU Compiler Collection (GCC): Warning Options%%%%% [always use `-Wall -Werror`!].desktop
│   ├── onlinegdb--atomic_block_in_c_WORKS.c
│   ├── onlinegdb--empirically_determine_max_thread_stack_size_Bruno_Haible.c
│   ├── onlinegdb--empirically_determine_max_thread_stack_size_GS_version.c
│   ├── onlinegdb--empirically_determine_max_thread_stack_size.md
│   ├── rounding_integer_division
│   │   ├── c - Rounding integer division (instead of truncating) - Stack Overflow.desktop
│   │   ├── readme.md
│   │   ├── rounding_integer_division.c -> rounding_integer_division.cpp
│   │   ├── rounding_integer_division.cpp
│   │   ├── rounding_integer_division.md
│   │   ├── run_tests_sample_output.txt
│   │   └── run_tests.sh
│   ├── strncmpci.c
│   ├── Using the GNU Compiler Collection (GCC): Warning Options-1.desktop
│   ├── utilities.c
│   └── utilities.h
├── cpp
│   ├── bin
│   │   └── tmp
│   ├── bin_hello_world
│   │   ├── hello_world
│   │   ├── hello_world.ii
│   │   ├── hello_world.o
│   │   └── hello_world.s
│   ├── copy_constructor_and_assignment_operator
│   │   ├── 170_Copy_Constructor_Assignment_Operator_[Stanford.edu]_GS_edit.pdf
│   │   ├── 170_Copy_Constructor_Assignment_Operator_[Stanford.edu].pdf
│   │   ├── Copy assignment operator - cppreference.com.desktop
│   │   ├── copy_constructor_and_assignment_operator [AKA--the ''Rule of Three'' and the ''Rule of Five'' demo!].txt
│   │   ├── copy_constructor_and_assignment_operator.cpp
│   │   ├── Copy constructors, assignment operators, - C++ Articles-1.desktop
│   │   ├── Copy constructors, assignment operators, - C++ Articles.desktop
│   │   ├── Copy constructor vs assignment operator in C++ - GeeksforGeeks.desktop
│   │   ├── c++ - What is The Rule of Three? - Stack Overflow.desktop
│   │   ├── c++ - What's the difference between assignment operator and copy constructor? - Stack Overflow.desktop
│   │   ├── Link to 170_Copy_Constructor_Assignment_Operator_[Stanford.edu].pdf.desktop
│   │   ├── Link to c++ Assignment operator and copy constructor - Google Search%%%%%.desktop
│   │   ├── Link to Copy constructor vs assignment operator in C++ - GeeksforGeeks%%%%% [see `t2 = t1;  -- calls assignment operator, same as "t2.operator=(t1);" `].desktop
│   │   ├── Link to c++ - What is The Rule of Three? - Stack Overflow%%%%%.desktop
│   │   └── Link to When should we write our own assignment operator in C++? - GeeksforGeeks%%%%% [use this code here!].desktop
│   ├── floating_point_resolution
│   │   ├── bin
│   │   │   └── tmp
│   │   ├── data -> ../../../eRCaGuy_hello_world_data/cpp/floating_point_resolution/data/
│   │   ├── double_resolution_test_1.cpp
│   │   ├── double_resolution_test_2.cpp
│   │   ├── double_resolution_test_3.cpp
│   │   ├── double_resolution_test_3--Figure_1a.png
│   │   ├── double_resolution_test_3--Figure_1b_zoomed_in.png
│   │   ├── double_resolution_test_3--Figure_1c_zoomed_in_really_small_to_very_beginning.png
│   │   ├── double_resolution_test_4.cpp
│   │   ├── plot_data.py
│   │   ├── readme.md
│   │   └── todo_(what_to_work_on_next).txt
│   ├── hello_world.cpp
│   ├── Link to c - Where do we use .i files and how do we generate them - Stack Overflow%%%%% [MY OWN ANS!].desktop
│   ├── Link to How to initialize a struct to 0 in C++ - Stack Overflow%%%%%+ [my own Q & A].desktop
│   ├── Link to Why doesn't initializing a C++ struct to `= {0}` set all of its members to 0? - Stack Overflow%%%%%++ [my own Q; very good answers here!].desktop
│   ├── macro_practice
│   │   ├── advanced_macro_usage_pass_in_entire_func.cpp
│   │   └── bin_adv_macro
│   │       ├── advanced_macro_usage_pass_in_entire_func
│   │       ├── advanced_macro_usage_pass_in_entire_func.ii
│   │       ├── advanced_macro_usage_pass_in_entire_func.o
│   │       └── advanced_macro_usage_pass_in_entire_func.s
│   ├── onlinegdb--atomic_block_in_cpp_1_WORKS.cpp
│   ├── onlinegdb--atomic_block_in_cpp_2_FAILS.cpp
│   ├── onlinegdb--atomic_block_in_cpp_3_WORKS.cpp
│   ├── onlinegdb--const_reference_to_vector__default_func_parameter.cpp
│   ├── run_hello_world.sh
│   ├── run_struct_initialization.sh
│   ├── struct_initialization.c -> struct_initialization.cpp
│   ├── struct_initialization.cpp
│   ├── template_function_sized_array_param
│   │   ├── print_array_calls_by_array_size.ods
│   │   ├── readme.md
│   │   ├── regular_func
│   │   ├── regular_func.cpp
│   │   ├── template_func
│   │   └── template_func.cpp
│   ├── template_practice
│   │   ├── explicit_template_specialization.cpp
│   │   ├── research
│   │   │   ├── (7) Template Specialization In C++ - YouTube.desktop
│   │   │   ├── Buckys C++ Programming Tutorials - 61 - Template Specializations - YouTube.desktop
│   │   │   ├── Link to explicit (full) template specialization - cppreference.com%%%%%+.desktop
│   │   │   ├── Link to template c++ - Google Search%%%%%.desktop
│   │   │   ├── Link to template specialization - Google Search%%%%%.desktop
│   │   │   ├── Link to template specialization - Google Search [videos]%%%%%.desktop
│   │   │   ├── partial template specialization - cppreference.com.desktop
│   │   │   ├── Template (C++) - Wikipedia.desktop
│   │   │   ├── Template (C++) - Wikipedia_GS_edit.pdf
│   │   │   └── Template (C++) - Wikipedia.pdf
│   │   └── run_explicit_template_specialization.sh
│   └── unordered_map_practice
│       ├── Link to GDB online Debugger - Code, Compile, Run, Debug online C, C++ [unordered_map practice].desktop
│       ├── unordered_map_hash_table_implicit_key_construction_test
│       └── unordered_map_hash_table_implicit_key_construction_test.cpp
├── eRCaGuy_hello_world--what to work on next--Gabriel.odt
├── java
│   └── todo.txt
├── LICENSE
├── markdown
│   ├── github_readme_center_and_align_images.md
│   └── photos
│       ├── LICENSE.txt
│       ├── pranksta1.jpg
│       ├── pranksta2.jpg
│       ├── pranksta3.jpg
│       ├── pranksta4.jpg
│       ├── pranksta5.jpg
│       ├── pranksta6.jpg
│       └── pranksta7.jpg
├── python
│   ├── textwrap_practice_1.py
│   └── yaml_import
│       ├── import_yaml_test.py
│       ├── my_config1.yaml
│       └── my_config2.yaml
├── README.md
└── tree.txt

25 directories, 122 files
```


<a id="changelog"></a>
# Changelog
- Newest on top
- Follows Semantic Versioning: MAJOR.MINOR.PATCH; see: https://semver.org/ for rules & FAQ.
- The 6 most common recommended types of changes are (see here: https://keepachangelog.com/en/1.0.0/): Added, Changed, Deprecated, Removed, Fixed, Security

INITIAL DEVELOPMENT PHASE:
- Use version numbers 0.MINOR.PATCH for the initial development phase; ex: 0.1.0, 0.2.0, etc.
- Increment just the MINOR version number for each new 0.y.z development phase enhancement, until the project is mature enough that you choose to move to a 1.0.0 release
- You may increment the PATCH number for bug fixes to your development code, or just increment the MINOR version number if there are also enhancements

MORE MATURE PHASE:
- As the project matures, release a 1.0.0 version
- Once you release a 1.0.0 version, do the following (copied from semver.org):
- Given a version number MAJOR.MINOR.PATCH, increment the:  
1. MAJOR version when you make incompatible API changes,  
2. MINOR version when you add functionality in a backwards compatible manner, and  
3. PATCH version when you make backwards compatible bug fixes.  

**UPDATE 27 DEC 2020: CHANGELOG AND RELEASES NOT REALLY UP-TO-DATE ANYMORE. JUST USE THE LATEST MASTER BRANCH!**

<a id="v030---2020-05-23"></a>
## [v0.3.0] - 2020-05-23
- Added "awk" folder with two sample programs: "awk_hello_world.sh" and "awk_syntax_tests.sh"

<a id="v020---2020-04-18"></a>
## [v0.2.0] - 2020-04-18
- Added "cpp/unordered_map_practice/unordered_map_hash_table_implicit_key_construction_test.cpp"

<a id="v010---2020-04-14"></a>
## [v0.1.0] - 2020-04-14
- Added changelog and started tracking a "version" number via the changelog
- Added "python/yaml_import/import_yaml_test.py" and related .yaml configuration files to demonstrate importing and using YAML configuration files in Python
- A bunch of really good C and C++ examples were already in place at this time, as I had been doing this project for quite some time without a Changelog 


  [pthread_create]: https://www.man7.org/linux/man-pages/man3/pthread_create.3.html
