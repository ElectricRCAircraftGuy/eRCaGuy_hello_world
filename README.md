# eRCaGuy_hello_world
"hello world" demos &amp; templates for various languages, incl. `gcc` build commands for C &amp; C++ 

By Gabriel Staples  
www.ElectricRCAircraftGuy.com


## Status:
1. Many solid C & C++ demos are done and work! 
1. A Python demo also is in place to show how to parse a YAML file. 

See the `tree` output below to see the file/folder structure.


# For beginners and experts alike: not your average "hello world" examples

Note that these are NOT just your standard "simple" hello world demos for absolute beginners. Rather, they are simple enough for beginners but also contain some advanced techniques and tips & tricks to act as good reminders or teaching for more expert programmers too. I, myself, regularly reference my own examples here to remind myself of some of these details which are easy to forget. There's no sense stressing about trying to remember everything. _Instead of trying to remember everything, just remember where to look (here in this case)_. 


# Examples of more advanced principles taught herein:

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

## 2. Python:
1. How to create, parse, and print YAML files. How to find the directory path a called Python file is in.
    1. See ["python/yaml_import/import_yaml_test.py"](python/yaml_import/import_yaml_test.py) and other files in that directory.

## 3. markdown:
1. [github_readme_center_and_align_images.md](markdown/github_readme_center_and_align_images.md): show how to insert and center, align left, align right, etc. images in GitHub readmes in markdown.


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
│   ├── Link to ElectricRCAircraftGuy--PDF2SearchablePDF [THIS IS A SOLID BASH EXAMPLE!].desktop
│   ├── Link to PDF2SearchablePDF--pdf2searchablepdf.sh at master · ElectricRCAircraftGuy--PDF2SearchablePDF.desktop
│   └── todo.txt
├── c
│   ├── c - Where do we use .i files and how do we generate them? - Stack Overflow.desktop
│   ├── hello_world
│   ├── hello_world.c
│   ├── hello_world_sleep
│   ├── hello_world_sleep.c
│   ├── Link to c - Prototype of printf and implementation - Stack Overflow%%%%%+ [MY OWN ANS!].desktop
│   ├── Link to c - Where do we use .i files and how do we generate them - Stack Overflow%%%%% [MY OWN ANS!].desktop
│   ├── Link to Using the GNU Compiler Collection (GCC): Warning Options%%%%% [always use `-Wall -Werror`!].desktop
│   ├── rounding_integer_division
│   │   ├── c - Rounding integer division (instead of truncating) - Stack Overflow.desktop
│   │   ├── readme.md
│   │   ├── rounding_integer_division.c -> rounding_integer_division.cpp
│   │   ├── rounding_integer_division.cpp
│   │   ├── rounding_integer_division.md
│   │   ├── run_tests_sample_output.txt
│   │   └── run_tests.sh
│   └── Using the GNU Compiler Collection (GCC): Warning Options-1.desktop
├── cpp
│   ├── bin
│   │   ├── struct_initialization
│   │   ├── struct_initialization.i
│   │   ├── struct_initialization.ii
│   │   ├── struct_initialization.o
│   │   └── struct_initialization.s
│   ├── bin_hello_world
│   │   ├── hello_world
│   │   ├── hello_world.ii
│   │   ├── hello_world.o
│   │   └── hello_world.s
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
│   ├── run_hello_world.sh
│   ├── run_struct_initialization.sh
│   ├── struct_initialization.c -> struct_initialization.cpp
│   ├── struct_initialization.cpp
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
├── python
│   └── yaml_import
│       ├── import_yaml_test.py
│       ├── my_config1.yaml
│       └── my_config2.yaml
└── README.md

16 directories, 68 files

```


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

## [v0.3.0] - 2020-05-23
- Added "awk" folder with two sample programs: "awk_hello_world.sh" and "awk_syntax_tests.sh"

## [v0.2.0] - 2020-04-18
- Added "cpp/unordered_map_practice/unordered_map_hash_table_implicit_key_construction_test.cpp"

## [v0.1.0] - 2020-04-14
- Added changelog and started tracking a "version" number via the changelog
- Added "python/yaml_import/import_yaml_test.py" and related .yaml configuration files to demonstrate importing and using YAML configuration files in Python
- A bunch of really good C and C++ examples were already in place at this time, as I had been doing this project for quite some time without a Changelog 
