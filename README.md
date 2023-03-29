[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2FElectricRCAircraftGuy%2FeRCaGuy_hello_world&count_bg=%2379C83D&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=views+%28today+%2F+total%29&edge_flat=false)](https://hits.seeyoufarm.com)

[>> Sponsor Me on GitHub <<](https://github.com/sponsors/ElectricRCAircraftGuy)


# eRCaGuy_hello_world
"hello world" demos &amp; templates for various languages, incl. `gcc` build commands for C &amp; C++ 

See also my [eRCaGuy_hello_world_data](https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world_data) project. 

By Gabriel Staples  
www.ElectricRCAircraftGuy.com  

- Disclaimer: any content herein is my own or otherwise has proper notice of licensing and attribution. This repo contains my own beliefs, opinions, words and works. They are _not_ endorsed by any of my past nor present employers.


## Other, very-useful repos:
1. My [eRCaGuy_dotfiles](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles) repo.


## Popular online interactive tools & resources
1. Free:
    1. https://www.onlinegdb.com/ - compile, run, save, share, and debug with `gdb`, your code online
    1. https://godbolt.org/ - Compiler Explorer: view the compiled assembler output of your code
    1. \*\*\*\*\* [My favorite for C++!] https://cppinsights.io/ - a tool for understanding and expanding cryptic C++ so that it goes from implicit to explicit! See how `auto` expands, what explicit types implicit types are, how range-based `for` loop expand, how arrays, structs, classes, etc., are initialized, etc.
        1. My answer here references it: [Coderpad's new C++ example is cryptic: meaning of `auto` and `const char* const&`](https://stackoverflow.com/a/75656629/4561887)
    1. https://cdecl.org/ - convert C and C++ pointers and complex types to plain English
    1. https://regex101.com/ - expand, test, and understand regular expressions
    1. https://asciiflow.com/#/ - draw ASCII diagrams and documentation, for text-based readmes, online.
1. Paid:
    1. https://coderpad.io/ - for sharing code when giving or taking online interviews; practice in the sandbox before an interview here: https://app.coderpad.io/sandbox
    1. https://www.lucidchart.com/pages/ - a popular diagramming tool used by many top tech companies


## Also very useful:
1. **Learn X in Y minutes**: for _most-excellent_ software tutorials written in code in the language itself which you are learning!
    1. Main Website: https://learnxinyminutes.com/
    1. GitHub: https://github.com/adambard/learnxinyminutes-docs
    1. Example tutorials:
        1. Ones I'd like to study next are marked with a star: ⭐. Ones I have fully studied are marked with a check (none so far): ✅.
        1. Languages:
            1. C - https://learnxinyminutes.com/docs/c/
            1. C++ - https://learnxinyminutes.com/docs/c++/
            1. Python - https://learnxinyminutes.com/docs/python/
            1. Go - https://learnxinyminutes.com/docs/go/
        1. Tools [I know I know!...I consider some of these programming languages too!--like `bash` and `awk`]:
            1. Bash - https://learnxinyminutes.com/docs/bash/
            1. awk - https://learnxinyminutes.com/docs/awk/
            1. cmake⭐ - https://learnxinyminutes.com/docs/cmake/
            1. ansible - https://learnxinyminutes.com/docs/ansible/
            1. git - https://learnxinyminutes.com/docs/git/
            1. make⭐ - https://learnxinyminutes.com/docs/make/
            1. linker scripts (Russian only--use Google Translate) - https://learnxinyminutes.com/docs/linker/
            1. vim - https://learnxinyminutes.com/docs/vim/
1. https://www.learncpp.com/


# Table of Contents
<details>
<summary><b>(click to expand)</b></summary>
<!-- MarkdownTOC -->

1. [Status:](#status)
1. [Description: _for beginners and experts alike!_--not your average "hello world" examples](#description-_for-beginners-and-experts-alike_--not-your-average-hello-world-examples)
1. [How to clone this repo and all git submodules and git lfs files \(including tracked binary files, such as PDFs\)](#how-to-clone-this-repo-and-all-git-submodules-and-git-lfs-files-including-tracked-binary-files-such-as-pdfs)
        1. [To clone this repo plus all sub-repos \(git submodules\) and all `git lfs` Large File Storage files](#to-clone-this-repo-plus-all-sub-repos-git-submodules-and-all-git-lfs-large-file-storage-files)
        1. [To update this repo as a _user_ of it, to match it exactly as I have made it as the developer of it](#to-update-this-repo-as-a-user-of-it-to-match-it-exactly-as-i-have-made-it-as-the-developer-of-it)
1. [A Few Folder & File Notes](#a-few-folder--file-notes)
1. [Examples of more advanced principles taught herein:](#examples-of-more-advanced-principles-taught-herein)
    1. [1. C and C++:](#1-c-and-c)
            1. [Online community wiki reference pages](#online-community-wiki-reference-pages)
            1. [Code examples:](#code-examples)
        1. [Additional C and C++ build notes \(ex: w/`gcc` or `clang` compilers\):](#additional-c-and-c-build-notes-ex-wgcc-or-clang-compilers)
    1. [2. Python:](#2-python)
    1. [3. markdown:](#3-markdown)
    1. [4. bash:](#4-bash)
    1. [5. awk:](#5-awk)
    1. [6. Arduino:](#6-arduino)
1. [Useful tips and tricks:](#useful-tips-and-tricks)
    1. [Running a C file as an executable Bash script](#running-a-c-file-as-an-executable-bash-script)
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
1. [bash/argument_parsing__3_advanced__gen_prog_template.sh](bash/argument_parsing__3_advanced__gen_prog_template.sh) is a _really good_ advanced bash demo of a full program with advanced features, help menu, full argument parsing, etc. See the [bash](#4-bash) section below.

See the `tree` output below to see the file/folder structure.


<a id="description-_for-beginners-and-experts-alike_--not-your-average-hello-world-examples"></a>
# Description: _for beginners and experts alike!_--not your average "hello world" examples

Note that these are NOT just your standard "simple" hello world demos for absolute beginners. Rather, they are simple enough for beginners but also contain some advanced techniques and tips & tricks to act as good reminders or teaching for more expert programmers too. I, myself, regularly reference my own examples here to remind myself of some of these details which are easy to forget. There's no sense stressing about trying to remember everything. _Instead of trying to remember everything, just remember where to look (here in this case)_. 


<a id="how-to-clone-whole-repo"></a>
<a id="how-to-clone-this-repo-and-all-git-submodules-and-git-lfs-files-including-tracked-binary-files-such-as-pdfs"></a>
# How to clone this repo and all git submodules and git lfs files (including tracked binary files, such as PDFs)

This repo contains [Git Submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules), which simply means that this is a git repo which contains other git repos. It also uses [`git lfs` (Large File Storage)](https://git-lfs.com/) to more-efficiently store certain binary files, such as PDFs. 

- **For details on how to use `git submodule` and `git lfs`, see my notes in my [eRCaGuy_dotfiles](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles) repo here: [how-to-clone-whole-repo](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles#how-to-clone-whole-repo).** 
- See also the `= git submodules: =` section of my "git & Linux cmds doc" notes in my [eRCaGuy_dotfiles](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles) repo here: [eRCaGuy_dotfiles/git & Linux cmds, help, tips & tricks - Gabriel.txt](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/git%20%26%20Linux%20cmds%2C%20help%2C%20tips%20%26%20tricks%20-%20Gabriel.txt).

In short:

<a id="to-clone-this-repo-plus-all-sub-repos-git-submodules-and-all-git-lfs-large-file-storage-files"></a>
### To clone this repo plus all sub-repos (git submodules) and all `git lfs` Large File Storage files

```bash
# Clone this repo
git clone https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world.git
# Pull all Git LFS files (large binary files, such as PDFs, tracked with `git lfs`)
git lfs pull
# Recursively clone and update all subrepos (git submodules) it may contain
git submodule update --init --recursive
```

<a id="to-update-this-repo-as-a-user-of-it-to-match-it-exactly-as-i-have-made-it-as-the-developer-of-it"></a>
### To update this repo as a _user_ of it, to match it exactly as I have made it as the developer of it

```bash
git pull
git lfs pull
git submodule update --init --recursive
```


<a id="a-few-folder--file-notes"></a>
# A Few Folder & File Notes

1. Find some sample interview preparation code and notes by running `./find_interview_prep.sh` at the root of the repo. Example:
    ```bash
    eRCaGuy_hello_world$ ./find_interview_prep.sh 
    Finding all "interview prep" files in directory "/home/gabriel/GS/dev/eRCaGuy_hello_world" and lower.
    find_interview_prep.sh
    cpp/string_concatenate.cpp
    Done. 2 file(s) found.
    ```
1. You can add this as an **Eclipse project**--for source code navigation _only_, NOT for building! The Eclipse project files/folders are:
    1. `.cproject` file
    1. `.project` file
    1. `.settings` dir
1. `.clang-format` is the format definition file for auto-formatting C and C++ files with `clang-format`. 
    1. For full installation and usage instructions for `clang-format`, see the readme in my other repo here: https://github.com/ElectricRCAircraftGuy/eRCaGuy_CodeFormatter.
    1. Quick usage example: 
        ```bash
        # Format this file in-place (`-i`)
        clang-format --verbose -i --style=file "path/to/file.c"
        ```
    1. See the other repo here (https://github.com/ElectricRCAircraftGuy/eRCaGuy_CodeFormatter#usage) for more info on what `--style=file` means and how you can place the `.clang-format` configuration file at different levels.


<a id="examples-of-more-advanced-principles-taught-herein"></a>
# Examples of more advanced principles taught herein:


<a id="1-c-and-c"></a>
## 1. C and C++:


<a id="online-community-wiki-reference-pages"></a>
#### Online community wiki reference pages
1. https://en.cppreference.com/ - most popular; hard to understand; cryptic; pedantic; most-thorough and complete; written like it's for a programming language lawyer; covers up to C++17 and is working on C++20
1. https://cplusplus.com/reference/ - much easier to understand; better examples and explanations; written like it's for normal humans and programmers; but less complete and less-thorough; maybe only covers up to C++11


<a id="code-examples"></a>
#### Code examples:

1. How to generate intermediate build files, including .ii, .s, and .o.
    1. See ["cpp/hello_world.cpp"](cpp/hello_world.cpp)
1. How to make a single file compile in both C and C++ by using the `#ifdef __cplusplus` `extern "C" {` brace trick
    1. See ["c/hello_world.c"](c/hello_world.c)
    1. Note: there is also such a thing as `extern "C++"`. Search the GNU gcc documentation here for that search string: https://gcc.gnu.org/onlinedocs/gcc.pdf. Ex: the top of p489, under the paragraph titled "_Language-linkage module attachment_", mentions `(extern "C" or extern "C++")`.
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
    1. See ["c/strncmpci.c"](c/strncmpci.c)
1. Example of how to manually write unit tests.
    1. See ["c/strncmpci.c"](c/strncmpci.c)
    1. Note: for Google Test (gtest/gmock) examples, including how to use the [Bazel](https://bazel.build/) build system, see my repo here instead: https://github.com/ElectricRCAircraftGuy/eRCaGuy_gtest_practice.
1. Example of how to use ANSI color codes (ex: red and green) in terminal output. 
    1. It is possible to colorize and stylize/format your text you print to `stdout` or `stderr`, in any programming language, by surrounding the text with special ANSI color codes. This works for _all programming languages_ and _all forms of printing_ to `stdout` or `stderr`, whether via `printf("some text\n");` in C or C++, `std::cout << "some text\n";` in C++, `print("some text")` in Python, `echo "some text"` in bash, etc.
    1. See these defines in C in ["c/strncmpci.c"](c/strncmpci.c):
        ```c
        #define ANSI_COLOR_OFF "\033[m"
        #define ANSI_COLOR_GRN "\033[32m"
        #define ANSI_COLOR_RED "\033[31m"
        ```
        ...and how I used them to colorize text in `printf()` calls there.
    1. See also my other repo here: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/git-diffn.sh#L126
1. How to use a `const` reference to a vector, with a default parameter, as an input param to a function!
    1. See ["cpp/onlinegdb--const_reference_to_vector__default_func_parameter.cpp"](cpp/onlinegdb--const_reference_to_vector__default_func_parameter.cpp)
1. How to call command-line system calls in C and C++, read piped input from `stdin`, and read command-line output from called process from its `stdout`:
    1. [c/system_call_list_files.c](c/system_call_list_files.c): basic example to call `ls -l` in C, but _not_ read back the output. Rather, it just prints to stdout instead. 
    1. See also:
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
    1. More of my answers:
        1. [Answer 1/3: use a union and a packed struct](https://stackoverflow.com/a/69984037/4561887). Code:
            1. [c/struct_to_array_via_type_punning_union.c](c/struct_to_array_via_type_punning_union.c)
            1. [c/struct_to_array_via_type_punning_union_more_efficient.c](c/struct_to_array_via_type_punning_union_more_efficient.c)
        1. [Answer 2/3: convert a struct to an array of bytes via manual bit-shifting](https://stackoverflow.com/a/69984464/4561887). Code:
            1. [c/struct_to_array_via_bit_shifting.c](c/struct_to_array_via_bit_shifting.c)
        1. [Answer 3/3: use a packed struct and a raw uint8_t pointer to it](https://stackoverflow.com/a/69984614/4561887). Code:
            1. [c/struct_to_array_via_type_punning_raw_pointer.c](c/struct_to_array_via_type_punning_raw_pointer.c)
1. (Multidimensional arrays) 2D array practice in C and C++. 
    1. See [c/2d_array_practice.c](c/2d_array_practice.c); it runs in both C and C++; see build commands in the comments at the top
        1. See my full answer on this on Stack Overflow here: [How to pass a multidimensional array to a function in C and C++](https://stackoverflow.com/a/67814330/4561887)
1. Asserts in C:
    1. [c/assert_practice.c](c/assert_practice.c) - practice using the `assert()` and `static_assert()` macro wrappers in C11, as well as a custom `ASSERT_TRUE()` macro I wrote which also prints the filename, function name, and line number using built-in _macros_ `__FILE__` and `__LINE__`, and the special built-in static C-string (char array) _variable_ `__func__`.   
1. Pre-main() and post-main() function call injection:
    1. [VERY interesting and neat concept!] Dynamically inject function calls before and after another executable's `main()` function.
        1. AKA: program "constructors" and "destructors" in C.
        1. AKA: how to use gcc function attributes `constructor` and `destructor`, and C function `atexit()`. 
    1. See [c/dynamic_func_call_before_and_after_main.c](c/dynamic_func_call_before_and_after_main.c). 
1. Dynamic library (shared object `lib*.so`) creation and use, including with the Linux `LD_PRELOAD` preloader trick at call time. 
    1. See [c/dynamic_func_call_before_and_after_main_build_and_run.sh](c/dynamic_func_call_before_and_after_main_build_and_run.sh)
1. How to use [`std::initializer_list<>`](https://en.cppreference.com/w/cpp/utility/initializer_list) as an input arg to a function, like [`std::max()`](https://en.cppreference.com/w/cpp/algorithm/max) does, so you can easily pass in a variable number of input arguments inside curly braces in order to perform operations on them. In this case, I concatenate any number of input argument strings with `/` chars between them in order to build a file path from multiple directory names and the filename at the end. 
    1. See [cpp/make_path_to_file.cpp](cpp/make_path_to_file.cpp)
        1. Sample usage:
            ```cpp
            // output: `"/dir1/dir2/dir3"`
            std::string file_path = make_path({"/dir1", "dir2", "dir3"}); 
            ```
1. Demonstrate how to "remove an element" from an array in C. You might also call this "filtering an array" in C. 
    1. See: [c/array_filter_and_remove_element.c](c/array_filter_and_remove_element.c). I demonstrate 2 approaches:
        1. [better] copy the array into a new array (the clean and easy approach), but takes 2x array memory
        1. filter the array in-pace (the hard and copy-intensive approach), but takes no extra array memory
        1. See also my answer on this here: [Stack Overflow: Removing elements from array in C](https://stackoverflow.com/a/70043744/4561887).
1. Demonstrate prefix (`++i` and `--i`) vs postfix (`i--` and `i++`) operators and how they differ. 
    1. See: [c/preincrement_and_postincrement_demo.c](c/preincrement_and_postincrement_demo.c)
    1. In short: 
        * `++i` increments the value first, and THEN reads the value.
        * `i++` reads the value first, and THEN increments it!
        - The same order goes for prefix and postfix decrements (`--i`, and `i--`, respectively).
        - That's it!
1. [c/system_call_python.c](c/system_call_python.c) - this program is pretty cool! It has C write and call a Python program using `system()` calls. 
    1. In short, it's a C program which uses system calls to write and call a Python script which then uses a system call to ping. Pretty neat. I posted the code also in my answer here: https://stackoverflow.com/a/70285228/4561887.
1. Iterate over C `enum` and C++ `enum class`: [Stack Overflow: How can I iterate over an enum?](https://stackoverflow.com/a/69774217/4561887)
1. 4 ways to do function pointers in C++ (2 of which work also in C) - [cpp/function_ptr_typedef_vs_std_function.cpp](cpp/function_ptr_typedef_vs_std_function.cpp)
1. Libcurl usage (`#include <curl/curl.h>`) and advanced error handling--ex: `enum class Error_code`, `struct Error`, `return Error::Ok()`, etc.
    1. See the `cpp/curl_lib*` `.h`, `.cpp`, and `unittest.cpp` files.


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
<a id="-lm"></a>
1. **If you include the C math library with `#include <math.h>`,** you must add `-lm` to the very end of your gcc build command to link to the math library! _Technically_, you only need `-lm` after any .o object file or .c source file which needs it, but it's a good idea to _just put all libraries to link against at the very end of the gcc build command._ 
    1. So, do this:
        ```bash
        # DO THIS (has `-lm` at end):
        # Note: add the math lib last via `-lm` so that any object file or source file before 
        # this point which includes <math.h> will link properly against that library's symbols.
        gcc -Wall -Wextra -Werror -O3 -std=c17 hello_world_extra_basic.c -o bin/a -lm && bin/a
        ```
    1. NOT this:
        ```bash
        # NOT THIS (is missing `-lm`):
        gcc -Wall -Wextra -Werror -O3 -std=c17 hello_world_extra_basic.c -o bin/a && bin/a
        ```
    1. See:
        1. This answer: [Undefined reference to `sin`](https://stackoverflow.com/a/12165016/4561887)
        1. This comment discussion and links between @paxdiablo and myself [from this point down](https://stackoverflow.com/questions/5248919/undefined-reference-to-sqrt-or-other-mathematical-functions#comment126310413_5248951). 
            1. In short, you _technically_ only need to link to a library `my_library` with `-lmy_library` _directly after_ any .o object file or .c source file which needs it, but _practically_ (meaning: it's a good, practical, rule of thumb to do so) you should just put all libraries to link to at the very end of the gcc build command: 
                ```bash
                gcc -Wall -Wextra -Werror -O3 -std=c17 hello_world_extra_basic.c \
                    -o bin/a -lm -lmyliba -lmylibb -lmylibc -lmylibd
                ```


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
1. File [python/enum_practice.py](python/enum_practice.py) contains:
    1. How to use the hash-bang (ex: `#!/usr/bin/python3`) at the top of a Python script to make it a callable file. Note: you must still make the file executable in addition to this too.
    1. How to use [enums](https://docs.python.org/3/library/enum.html) (ie: "`Enum` classes") in Python.
    1. Demonstrates that Python enums can have values which are either integers or strings (or other types I think too).
    1. Shows how to _left-align prints_ in Python using the `%` operator, as well as specify their _width_. This is like the [`printf()`-style prints in C and C++](http://www.cplusplus.com/reference/cstdio/printf/). _Keywords: python print alignment, python print width, python left or right align prints, python C or C++-like prints, python %s prints._
    1. How to inspect and print _all members of any class in Python_ using the `.__dict__` member accessor; ex: `my_obj.__dict__`. 
    1. How to access the full, scoped name of an enum with just `my_enum`, or its name with `my_enum.name`, or its value with `my_enum.value`.
    1. How to access an enum _via a variable_ (ex: `fruit`, where previously fruit was set like this: `fruit = Fruit.APPLE`) OR _directly via its scoped class name_ (ex: `Fruit.APPLE` directly).
    1. How to create an enum class which contains ONLY strings, for instance, by inheriting from BOTH the `str` class _and_ the `Enum` class. 
        1. Pay attention!: if you try to store an integer into such an Enum class the integer value gets automatically converted into a string! This is demonstrated.
    1. How to iterate over Enums in Python (meaning: over all enum members in an Enum class).
    1. Introduce 3 types of enums:
        1. regular enums
        1. string enums
        1. integer enums
    1. Compare and contrast three types of enums (1. _regular enums_ vs. 2. _string enums_ vs. 3. _integer enums_), and show and compare how each works and how each treats the `=` operator.
    1. etc.
1. Controlling and communicating with Ethernet devices via UDP and TCP communication packets over `socket`s.
    1. These examples demonstrate how to use the built-in Ethernet `socket` module, for instance, to communicate with an Ethernet-controlled device via UDP or TCP. This is very useful for controlling and talking to laboratory equipment, for instance, such as digital power supplies, multimeters, etc.
    1. [python/socket_talk_to_ethernet_device.py](python/socket_talk_to_ethernet_device.py)
        1. Note: `netcat` (`nc`) can be used at the command-line to send commands over TCP and UDP as well. To do essentially the same thing (also over TCP) in the shell command-line as the code does via Python in the file above, do this:
            ```bash
            printf '%s' "my command to send" | timeout 0.2 nc 192.168.0.1 9999
            ```
            1. Do NOT use `echo` in place of `printf` above, as `echo` appends a trailing newline character (`\n`) which can prevent the device from parsing the message properly. `echo` is also not very portable and has other limitations such as being unable to send a string which begins with `-`.
            1. See my detailed answer here: [Stack Overflow: Piping echo to netcat fails while piping printf passes](https://stackoverflow.com/a/70001270/4561887)
            1. See also the many example `netcat` commands in my ["git & Linux cmds" doc](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/git%20%26%20Linux%20cmds%2C%20help%2C%20tips%20%26%20tricks%20-%20Gabriel.txt) in my [eRCaGuy_dotfiles][dotfiles] repo below. Search the document for "netcat". Search also for this section: "_Example of power supply control via string commands over Ethernet TCP using netcat_". It will be in the document somewhere around here: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/git%20%26%20Linux%20cmds%2C%20help%2C%20tips%20%26%20tricks%20-%20Gabriel.txt#L3192-L3219.
1. [c/system_call_python.py](c/system_call_python.py) - this Python program is autogenerated by and called by the C or C++ program [c/system_call_python.c](c/system_call_python.c). See additional information about it up above in the "C and C++" section.
1. [math/sympy_integral_and_printing.py](math/sympy_integral_and_printing.py) contains symbolic math and integrals in Python.


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
1. See the [bash](bash) folder.
1. See also various \*.sh bash scripts I've written in my [eRCaGuy_dotfiles][dotfiles] repo here: [eRCaGuy_dotfiles/useful_scripts](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/tree/master/useful_scripts).
1. How to obtain the full file path, full directory, and base filename of any script being run itself.
    1. See: ["bash/get_script_path.sh"](bash/get_script_path.sh)
    1. See also [my answer online on Stack Overflow, here](https://stackoverflow.com/questions/59895/how-to-get-the-source-directory-of-a-bash-script-from-within-the-script-itself/60157372#60157372).
1. Learn how to use the `source` (AKA `.`) command to "import" variables, and the `export` command to "export" them. 
    1. See my answer: [`source` (`.`) vs `export` (and also some file lock [`flock`] stuff at the end)](https://stackoverflow.com/a/62626515/4561887).
    1. [bash/source_and_export.sh](bash/source_and_export.sh)
1. How to escape `$` and `'`: [bash/character_escaping_demo.sh](bash/character_escaping_demo.sh)
1. How to do "array slicing" (like in Python) in bash, meaning: how to grab _an element_ or a desired _range of elements_ from within a bash array. This also covers the bare basics of printing arrays, creating arrays, etc.
    1. [bash/array_slicing_demo.sh](bash/array_slicing_demo.sh)
1. Bash array demo, as well as building and passing arguments to new commands via arrays. See:
    1. [bash/back_up_all_input_args.sh](bash/back_up_all_input_args.sh)
    1. [bash/array_practice.sh](bash/array_practice.sh) - also shows using negative index numbers to index from the right/end, like in Python.
1. [bash/check_if_sourced_or_executed.sh](bash/check_if_sourced_or_executed.sh)
    1. Identify if a bash script is being _executed_ or [_sourced_](https://stackoverflow.com/questions/15474650/unix-what-is-the-difference-between-source-and-export/62626515#62626515) (like importing in Python--ex: to get access to its functions), and act accordingly.
    1. This is the bash-equivalent to [Python's `if __name__ == "__main__":` check](https://stackoverflow.com/questions/419163/what-does-if-name-main-do).
1. [bash/multi_process_program.sh](bash/multi_process_program.sh)
    1. Create a "multi-threaded" (multi-process, actually) bash program, and learn how to start the processes and determine when each is done!
    1. See also my answer on this here: [Stack Overflow: How to wait in bash for several subprocesses to finish, and return exit code !=0 when any subprocess ends with code !=0?](https://stackoverflow.com/a/70670852/4561887)
1. [bash/array_pass_as_bash_parameter.sh](bash/array_pass_as_bash_parameter.sh)
    1. How to pass arrays as bash parameters to functions or bash scripts in bash. 
    1. This also extensively uses bash _array slicing_.
    1. See also my answer here: [Stack Overflow: Passing arrays as parameters in bash](https://stackoverflow.com/a/70855715/4561887)
1. **[VERY USEFUL]** [bash/argument_parsing__3_advanced__gen_prog_template.sh](bash/argument_parsing__3_advanced__gen_prog_template.sh) - very complete full program demo. Copy/paste this as a template for all medium to large bash programs! Features:
    1. Advanced optional and positional argument parsing.
    1. Full help menu. 
    1. Option to print version info.
    1. Debug prints which can be turned on/off.
    1. Function to print arrays.
    1. `main` function.
    1. Automatic run vs source detection: if the program detects it is being _executed_, it will parse arguments and run `main`, but if it detects it is being _sourced_ it will NOT! This way, you can source the program with `. path/to/program` or `source path/to/program` to "import" functions and variables you may want from it, but withOUT running it. This is akin to `if __name__ == "__main__":` in Python.


<a id="5-awk"></a>
## 5. awk:
1. See the [awk](awk) folder.
1. See also: [git-diffn.sh](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/git-diffn.sh) in another repo of mine, my [readme here](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/README_git-diffn.md), and [my answer to how to do "Git diff with line numbers (Git log with line numbers)" here](https://stackoverflow.com/questions/24455377/git-diff-with-line-numbers-git-log-with-line-numbers/61997003#61997003).


<a id="6-arduino"></a>
## 6. Arduino:
1. [arduino/Blink/Blink.ino](arduino/Blink/Blink.ino) - see how to blink built-in LED 13, how to manually "bit-bang" PWM it to dim it, and how to plot a couple opposing sawtooth waves you can view in the Arduino Serial Plotter. Pretty cool!


<a id="useful-tips-and-tricks"></a>
# Useful tips and tricks:


<a id="running-a-c-file-as-an-executable-bash-script"></a>
## Running a C file as an executable Bash script

Put this one-line bash script at the top of your C file: `//usr/bin/env gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit`

**hello_world.c:**
```c
//usr/bin/env gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit

#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello World.\n\n");

    return 0;
}
```

Now run your C file as an executable:
```bash
chmod +x hello_world.c
./hello_world.c
```

It turns out you can do this with **almost any** compiled language program to make it "feel" like a scripted program.

Pretty awesome. I first learned about it for Go, then just applied the concept to C.

See: [Unix & Linux: Shebang starting with `//`?](https://unix.stackexchange.com/a/162535/114401)

**Explanation:**

In this particular case above, it works because `//` is a comment in C, so that line is ignored in C, and multiple slashes are ignored in Bash, making `//usr/bin/env gcc` act like `/usr/bin/env gcc` in Bash, which simply calls the gcc compiler. That Bash line then calls the compiled C program with all args passed to it, as `/tmp/a "$@";`, then it calls `exit` afterwards to exit before trying to execute any more lines from this file, since trying to execute the C lines in Bash would of course result in errors.


<a id="file-structure"></a>
# File Structure:
(Output of `tree`. Run this cmd yourself to make sure what you see is up-to-date! I don't update the output below very often.)

```
eRCaGuy_hello_world$ tree
.
├── arduino
│   └── Leonardo_type_once_per_second
│       └── Leonardo_type_once_per_second.ino
├── avr
│   └── avr_ATmega328_blink--UNTESTED.c
├── awk
│   ├── awk_hello_world_SAMPLE_OUTPUT.txt
│   ├── awk_hello_world.sh
│   ├── awk_syntax_tests.sh
│   └── input_file_1.txt
├── bash
│   ├── array_slicing_demo.sh
│   ├── character_escaping_demo.sh
│   ├── get_script_path.sh
│   ├── Link to ElectricRCAircraftGuy--PDF2SearchablePDF [THIS IS A SOLID BASH EXAMPLE!].desktop
│   ├── Link to PDF2SearchablePDF--pdf2searchablepdf.sh at master · ElectricRCAircraftGuy--PDF2SearchablePDF.desktop
│   ├── practice
│   │   ├── read_arrays.sh
│   │   └── README.md
│   ├── README.md
│   └── source_and_export.sh
├── bin
├── c
│   ├── 2d_array_practice.c
│   ├── assert_practice.c
│   ├── bin
│   │   ├── D_define
│   │   ├── stack_size_bruno_c
│   │   ├── stack_size_bruno_cpp
│   │   ├── stack_size_gs_c
│   │   ├── stack_size_gs_cpp
│   │   └── tmp
│   ├── c - Where do we use .i files and how do we generate them? - Stack Overflow.desktop
│   ├── dynamic_func_call_before_and_after_main_build_and_run.sh
│   ├── dynamic_func_call_before_and_after_main.c
│   ├── gcc_dash_D_macro_define.c
│   ├── hello_world
│   ├── hello_world_basic.c
│   ├── hello_world.c
│   ├── hello_world_sleep
│   ├── hello_world_sleep.c
│   ├── Link to c - Prototype of printf and implementation - Stack Overflow%%%%%+ [MY OWN ANS!].desktop
│   ├── Link to c - Where do we use .i files and how do we generate them - Stack Overflow%%%%% [MY OWN ANS!].desktop
│   ├── Link to Using the GNU Compiler Collection (GCC): Warning Options%%%%% [always use `-Wall -Werror`!].desktop
│   ├── malloc_override_test.c
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
│   ├── type_punning.c
│   ├── Using the GNU Compiler Collection (GCC): Warning Options-1.desktop
│   ├── utilities.c
│   └── utilities.h
├── cpp
│   ├── bin
│   │   ├── integer_literals
│   │   ├── onlinegdb--cpp_default_args_practice
│   │   ├── onlinegdb--process_10_bit_video_data
│   │   ├── process_10_bit_video_data
│   │   ├── struct_initialization
│   │   ├── struct_initialization.i
│   │   ├── struct_initialization.ii
│   │   ├── struct_initialization.o
│   │   ├── struct_initialization.s
│   │   └── tmp
│   ├── bin_hello_world
│   │   ├── hello_world
│   │   ├── hello_world.ii
│   │   ├── hello_world.o
│   │   └── hello_world.s
│   ├── check_addr_of_weak_undefined_funcs.cpp
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
│   ├── integer_literals.cpp
│   ├── Link to c - Where do we use .i files and how do we generate them - Stack Overflow%%%%% [MY OWN ANS!].desktop
│   ├── Link to How to initialize a struct to 0 in C++ - Stack Overflow%%%%%+ [my own Q & A].desktop
│   ├── Link to Why doesn't initializing a C++ struct to `= {0}` set all of its members to 0? - Stack Overflow%%%%%++ [my own Q; very good answers here!].desktop
│   ├── macro_practice
│   │   ├── advanced_macro_usage_pass_in_entire_func.cpp
│   │   ├── bin_adv_macro
│   │   │   ├── advanced_macro_usage_pass_in_entire_func
│   │   │   ├── advanced_macro_usage_pass_in_entire_func.ii
│   │   │   ├── advanced_macro_usage_pass_in_entire_func.o
│   │   │   └── advanced_macro_usage_pass_in_entire_func.s
│   │   └── gcc_dash_D_macro_define.c -> ../../c/gcc_dash_D_macro_define.c
│   ├── onlinegdb--atomic_block_in_cpp_1_WORKS.cpp
│   ├── onlinegdb--atomic_block_in_cpp_2_FAILS.cpp
│   ├── onlinegdb--atomic_block_in_cpp_3_WORKS.cpp
│   ├── onlinegdb--const_reference_to_vector__default_func_parameter.cpp
│   ├── onlinegdb--cpp_default_args_practice.cpp
│   ├── process_10_bit_video_data.cpp
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
├── git_branch_hash_backups
│   └── eRCaGuy_hello_world_git_branch_bak--20200628-1856hrs-45sec.txt
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
│   ├── autogenerate_c_or_cpp_code.py
│   ├── autogenerated
│   │   └── myheader.h
│   ├── auto_white_balance_img.py
│   ├── raw_bytes_practice.py
│   ├── slots_practice
│   │   ├── Class and Instance Attributes – Real Python.desktop
│   │   ├── Link to 10. __slots__ Magic — Python Tips 0.1 documentation%%%%%+.desktop
│   │   └── slots_practice.py
│   ├── textwrap_practice_1.py
│   └── yaml_import
│       ├── import_yaml_test.py
│       ├── my_config1.yaml
│       └── my_config2.yaml
├── README.md
├── test_photos
│   ├── README.md
│   └── test1.jpg
└── tree.txt

30 directories, 163 files
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
  [dotfiles]: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles
