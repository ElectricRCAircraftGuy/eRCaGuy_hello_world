/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
May 2022

Examine how to use a C++ `std::string` as a C-style `char*` buffer. Demonstrate 3 viable techniques.
This code also clearly demonstrates the differences between `.resize()` and `.size()`, and
`.reserve()` and `.capacity()`.

Consider also my question here:
https://en.cppreference.com/w/Talk:cpp/string/basic_string/operator_at
> `.size()` (expanded via `resize()`) vs `.capacity()` (expanded via `reserve()`):

RESULTS:

1. To use a C++ `std::string` as a C-style _writable_`char*` buffer, you MUST first pre-allocate the
string's internal buffer to change its `.size()` by using `.resize()` (using `.reserve()` to
increase only the `.capacity()` is NOT sufficient!). Then, you can access the underlying buffer as
a `char*` in at least 3 ways:
    1. Technique 1: array indexing using `operator[]`. Ex: `&str[0]`, `&str[5]`, etc.
    1. Technique 2: use the `.data()` method to obtain a `char*`; Ex: `str.data()`,
    `str.data() + 5`, etc.
    1. Technique 3: use the `.begin()` method to obtain an iterator to the first char, and then use
    the iterator's `operator*()` dereference method to obtain the iterator's `char` `value_type`,
    and then take the address of that to obtain a `char*`. Ex: `&(*str.begin())`,
    `&(*str.begin()) + 5`, etc.
2. To obtain a _readable_ null-terminated `const char*` from a `std::string`, use the
`.c_str()` method. It returns a C-style string that is _guaranteed to be null-terminated_.
Note that the `.data()` method is NOT the same thing, as it is NOT guaranteed to be null-terminated!


STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 string__use_std_string_as_a_c_str_buffer.cpp -o bin/a && bin/a
```

References:
1. How to convert a std::string to const char* or char*:
   https://stackoverflow.com/q/347949/4561887
1. Directly write into char* buffer of std::string:
   https://stackoverflow.com/q/39200665/4561887
1. Is there a way to get std:string's buffer:
   https://stackoverflow.com/q/7836863/4561887

(my content)
1. [my Q] See the "Adjacently related" section at the bottom of my question here:
   https://stackoverflow.com/q/72367123/4561887
1. *****+ [my comments about pre-allocating a buffer in the std::string]:
   https://stackoverflow.com/questions/39200665/directly-write-into-char-buffer-of-stdstring#comment127844941_39200666
1. *****+ [my comment on how to pre-allocate storage in a std::string, to be used as a char* buffer]
   https://stackoverflow.com/questions/7836863/is-there-a-way-to-get-stdstrings-buffer#comment127847227_15863513

(from the cppreference.com community wiki)
1. https://en.cppreference.com/w/cpp/string/basic_string:
   """
   The elements of a basic_string are stored contiguously, that is, for a basic_string s, &*(s.begin
   () + n) == &*s.begin() + n for any n in [0, s.size()), or, equivalently, a pointer to s[0] can
   be passed to functions that expect a pointer to the first element of a null-terminated
   (since C++11)CharT[] array.
   """
1. https://en.cppreference.com/w/cpp/string/basic_string/operator_at
   """
   Returns a reference to the character at specified location pos. No bounds checking is performed.
   If pos > size(), the behavior is undefined.
   """
1. https://en.cppreference.com/w/cpp/string/basic_string/resize
1. https://en.cppreference.com/w/cpp/string/basic_string/reserve
1. https://en.cppreference.com/w/cpp/string/basic_string/data
1. https://en.cppreference.com/w/cpp/string/basic_string/c_str
1. https://en.cppreference.com/w/cpp/string/basic_string/clear


*/


// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <cstring>  // `strcpy()`

void print_string_stats(const std::string& str)
{
    std::cout << "contents of str         = " << str << "\n";
    std::cout << "contents of str.c_str() = " << str.c_str() << "\n";
    std::cout << "str.capacity()          = " << str.capacity() << "\n";
    std::cout << "str.size()              = " << str.size() << "\n";
    std::cout << "strlen(str.c_str())     = " << strlen(str.c_str()) << "\n";
}

/// Clear and resize the string to prepare to try the next technique.
///
/// NB: pass `str` by ptr, NOT by reference, as a best practice to make it obvious that the
/// parameter being passed in may be changed and have side effects. Ie: when a reader/programmer
///  sees a `&` at the call site in front of the parameter being passed-in, it says to them:
/// "Hey! this may get changed!"
void clear_and_resize_str(std::string* str)
{
    printf("clearing & resizing string\n");
    str->clear();
    print_string_stats(*str);
    str->resize(100);
    print_string_stats(*str);
    std::cout << "\n";
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    // Here is how to pre-allocate space in a `std::string` so you can use it like a `char*`
    // C-string:

    std::string str;
    print_string_stats(str);
    // pre-allocate space for 100 chars, filling in every one of those bytes with a '\0' null
    // terminator.
    str.resize(100);
    print_string_stats(str);
    std::cout << "\n";

    // Now write into the `std::string` like you would a C-string.

    constexpr char cstr1[] = "abcde ";
    constexpr char cstr2[] = "fghijk";

    // ---------------------------------------------------------------------------------------------
    // Technique 1: use array indexing via `operator[]`; ex: `&str[0]`
    // ---------------------------------------------------------------------------------------------
    std::cout << "== Technique 1: array indexing ==\n";

    strcpy(&str[0], cstr1);
    print_string_stats(str);
    strcpy(&str[sizeof(cstr1) - 1], cstr2); // `- 1` to overwrite the first null terminator
    print_string_stats(str);
    std::cout << "\n";

    clear_and_resize_str(&str);

    // ---------------------------------------------------------------------------------------------
    // Technique 2: use the `.data()` method
    // ---------------------------------------------------------------------------------------------
    std::cout << "== Technique 2: `.data()` method to obtain a `char*` \n"
                 "   (has the **exact same** results as Technique 1 above!): ==\n";

    strcpy(str.data(), cstr1);
    print_string_stats(str);
    strcpy(str.data() + (sizeof(cstr1) - 1), cstr2); // `- 1` to overwrite the first null terminator
    print_string_stats(str);
    std::cout << "\n";

    clear_and_resize_str(&str);

    // ---------------------------------------------------------------------------------------------
    // Technique 3: use the `.begin()` method to obtain an iterator to the first char.
    // See:
    // 1. https://en.cppreference.com/w/cpp/string/basic_string
    // 1. https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
    //
    // NB: calling the `operator*()` dereference method on the iterator object is how you obtain
    // its `value_type`, which is `char` in this case. You can then take the address of that with
    // `&` to obtain a `char*` C-string beginning at that location in the `std::string`.
    // Ex: `&(*str.begin())`
    // ---------------------------------------------------------------------------------------------
    std::cout << "== Technique 3: `.begin()` method to obtain an iterator to `value_type` `char`\n"
                 "   (has the **exact same** results as Techniques 1 & 2 above!): ==\n";

    strcpy(&(*str.begin()), cstr1);
    print_string_stats(str);
    strcpy(&(*str.begin()) + (sizeof(cstr1) - 1), cstr2); // `- 1` to overwrite the first null terminator
    print_string_stats(str);
    std::cout << "\n";

    clear_and_resize_str(&str);

    // ---------------------------------------------------------------------------------------------
    // Technique 4: use the `.c_str()` method
    // Will NOT work for writing since it returns const references only! You can only **read** from
    // the string as a `const char*` using this method!
    // NB:
    // 1. `.data()` returns a C-string you can **write into** OR read from. It is NOT required to
    // be null-terminated!
    // See: https://en.cppreference.com/w/cpp/string/basic_string/data
    // 2. `.c_str()` returns a C-string you can only **read from**. It IS guaranteed to be
    // null-terminated!
    // See: https://en.cppreference.com/w/cpp/string/basic_string/c_str
    // ---------------------------------------------------------------------------------------------
    std::cout << "== Technique 4: `.c_str()` method (is read-only; so it is expected to fail \n"
                 "   if you try to write to it!) ==" << "\n";
    // ERROR! `.c_str()` only returns a `const char*` null-terminated C-string which can be
    // **read from** only!--unlike `.data()` which returns a not-necessarily-null-terminated
    // C-string which can be **read from** OR **written to**!
    // Here is the compilation error:
    //
    //      string__use_std_string_as_a_c_str_buffer.cpp:181:21: error: invalid conversion from ‘const char*’ to ‘char*’ [-fpermissive]
    //           strcpy(str.c_str(), cstr1);
    // strcpy(str.c_str(), cstr1); // COMMENTED OUT TO ALLOW CODE TO COMPILE
    std::cout << "\n";


    // =============================================================================================
    // One more thing to try now!
    // See if `.reserve()` is sufficient to pre-allocate a C-style string buffer by increasing its
    // `.capacity()`, or if one **must** use `.resize()` to increase its `.size()`! The
    // cppreference.com community wiki documentation seems to indicate that the `size()` is what
    // matters for this, NOT the `.capacity()`. See the `operator[]` documentation here
    // (https://en.cppreference.com/w/cpp/string/basic_string/operator_at), where it states:
    // > If `pos > size()`, the behavior is undefined.
    // =============================================================================================

    std::cout << "Reserving 100 bytes to make `.capacity()` 100 while making `.size()` 0.\n";
    str.reserve(100);
    str.clear();
    print_string_stats(str);
    std::cout << "\n";

    // RESULTS OF THIS BLOCK: it does NOT work properly! We can manually read out the C-string    <============ RESULTS ===========
    // via `str.c_str()`, which works fine, but we can NOT print out the `std::string`
    // properly via `std::cout << str`. That means that calling `.reserve(100)` is NOT sufficient!
    // Rather, one MUST call `.resize(100)` instead! Using `.reserve(100)` only, and then manually
    // writing into the buffer, definitely shows aberrant behavior, and is PROBABLY "UNDEFINED"
    // BEHAVIOR!
    std::cout << "Now try to use this \"reserved\" (not \"resized\") buffer, using Technique 1!\n";
    strcpy(&str[0], "12345 ");
    print_string_stats(str);
    strcpy(&str[sizeof(cstr1) - 1], "6789"); // `- 1` to overwrite the first null terminator
    print_string_stats(str);
    std::cout << "\n";

    std::cout << "Notice that simply resizing and then printing again does NOT fix this!\n";
    str.resize(100);
    print_string_stats(str);
    std::cout << "\n";

    // This works just fine though!--(simply by calling `.resize(100)` first!)
    str.resize(100);
    std::cout << "Now try to use this \"resized\" (not just \"reserved\") buffer, using "
                 "Technique 1 (it works fine)!\n";
    strcpy(&str[0], "programming is ");
    print_string_stats(str);
    strcpy(&str[sizeof("programming is ") - 1], "hard"); // `- 1` to overwrite the first null terminator
    print_string_stats(str);
    std::cout << "\n";

    // =============================================================================================

    // shrink to fit (just to see if this does anything here)
    // RESULTS: Nope! No change!
    std::cout << "shrinking to fit (no change; is the same capacity and size as before,\n"
                 "just above)" << "\n";
    str.shrink_to_fit();
    print_string_stats(str);
    std::cout << "\n";


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 string__use_std_string_as_a_c_str_buffer.cpp -o bin/a && bin/a

    real    0m0.342s
    user    0m0.299s
    sys 0m0.043s
    Hello world!

    contents of str         =
    contents of str.c_str() =
    str.capacity()          = 15
    str.size()              = 0
    strlen(str.c_str())     = 0
    contents of str         =
    contents of str.c_str() =
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 0

    == Technique 1: array indexing ==
    contents of str         = abcde
    contents of str.c_str() = abcde
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 6
    contents of str         = abcde fghijk
    contents of str.c_str() = abcde fghijk
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 12

    clearing & resizing string
    contents of str         =
    contents of str.c_str() =
    str.capacity()          = 100
    str.size()              = 0
    strlen(str.c_str())     = 0
    contents of str         =
    contents of str.c_str() =
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 0

    == Technique 2: `.data()` method to obtain a `char*`
       (has the **exact same** results as Technique 1 above!): ==
    contents of str         = abcde
    contents of str.c_str() = abcde
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 6
    contents of str         = abcde fghijk
    contents of str.c_str() = abcde fghijk
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 12

    clearing & resizing string
    contents of str         =
    contents of str.c_str() =
    str.capacity()          = 100
    str.size()              = 0
    strlen(str.c_str())     = 0
    contents of str         =
    contents of str.c_str() =
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 0

    == Technique 3: `.begin()` method to obtain an iterator to `value_type` `char`
       (has the **exact same** results as Techniques 1 & 2 above!): ==
    contents of str         = abcde
    contents of str.c_str() = abcde
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 6
    contents of str         = abcde fghijk
    contents of str.c_str() = abcde fghijk
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 12

    clearing & resizing string
    contents of str         =
    contents of str.c_str() =
    str.capacity()          = 100
    str.size()              = 0
    strlen(str.c_str())     = 0
    contents of str         =
    contents of str.c_str() =
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 0

    == Technique 4: `.c_str()` method (is read-only; so it is expected to fail
       if you try to write to it!) ==

    Reserving 100 bytes to make `.capacity()` 100 while making `.size()` 0.
    contents of str         =
    contents of str.c_str() =
    str.capacity()          = 100
    str.size()              = 0
    strlen(str.c_str())     = 0

    Now try to use this "reserved" (not "resized") buffer, using Technique 1!
    contents of str         =
    contents of str.c_str() = 12345
    str.capacity()          = 100
    str.size()              = 0
    strlen(str.c_str())     = 6
    contents of str         =
    contents of str.c_str() = 12345 6789
    str.capacity()          = 100
    str.size()              = 0
    strlen(str.c_str())     = 10

    Notice that simply resizing and then printing again does NOT fix this!
    contents of str         =
    contents of str.c_str() =
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 0

    Now try to use this "resized" (not just "reserved") buffer, using Technique 1 (it works fine)!
    contents of str         = programming is
    contents of str.c_str() = programming is
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 15
    contents of str         = programming is hard
    contents of str.c_str() = programming is hard
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 19

    shrinking to fit (no change; is the same capacity and size as before,
    just above)
    contents of str         = programming is hard
    contents of str.c_str() = programming is hard
    str.capacity()          = 100
    str.size()              = 100
    strlen(str.c_str())     = 19


*/
