/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2022

Learn how to list files and directories both at a given level, and recursively. Also learn to sort
their output!

STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
time g++ -Wall -Wextra -Werror -O3 -std=c++17 std_experimental_filesystem__list_files_and_dirs.cpp -o bin/a -lstdc++fs && bin/a
```

IMPORTANT: if you see this linker error:
    ```
    /tmp/ccfHRXrJ.o: In function `main':
    std_experimental_filesystem__list_files_and_dirs.cpp:(.text.startup+0x9c): undefined reference to `std::experimental::filesystem::v1::__cxx11::path::_M_split_cmpts()'
    collect2: error: ld returned 1 exit status
    ```
...it's because you forgot to link to the library with `-lstdc++fs` above! Add that to your build
   flags! See: https://stackoverflow.com/a/33159746/4561887

References:
1. https://en.cppreference.com/w/cpp/experimental/fs
    1. ***** https://en.cppreference.com/w/cpp/experimental/fs/directory_iterator
    1. ***** https://en.cppreference.com/w/cpp/experimental/fs/recursive_directory_iterator
    1. *****+ https://en.cppreference.com/w/cpp/experimental/fs/directory_entry
    1. https://en.cppreference.com/w/cpp/experimental/fs/path/path
1. *****+ https://stackoverflow.com/a/612176/4561887
1. *****+ https://stackoverflow.com/a/37494654/4561887
1. https://stackoverflow.com/a/33159746/4561887 - use `-lstdc++fs` in your build arguments to link


*/

// C & C++ includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.
#include <cstdio>   // For `printf()`
#include <experimental/filesystem>
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <set>


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    std::experimental::filesystem::path path = "json/include/nlohmann";

    // See:
    // 1. https://en.cppreference.com/w/cpp/experimental/fs/directory_iterator
    // 1. https://stackoverflow.com/a/612176/4561887
    std::cout << "Printing all files and folders in path \"" << path << "\":\n";
    for (const std::experimental::filesystem::directory_entry& entry :
        std::experimental::filesystem::directory_iterator(path))
    {
        std::cout << entry.path() << "\n";
    }
    std::cout << "\n";

    // See:
    // 1. https://en.cppreference.com/w/cpp/experimental/fs/recursive_directory_iterator
    // 1. https://stackoverflow.com/a/612176/4561887
    std::cout << "**Resursively** printing all files and folders in path \"" << path << "\":\n";
    for (const std::experimental::filesystem::directory_entry& entry :
        std::experimental::filesystem::recursive_directory_iterator(path))
    {
        std::cout << entry.path() << "\n";
    }
    std::cout << "\n";


    // Notice the output above is NOT sorted. That's normal. Let's try to sort it now!:

    std::cout << "Printing all files and folders in path \"" << path <<
        "\" **SORTED**:\n";
    // To auto-sort the files alphabetically, we can place them into a `std::set<>`!
    std::set<std::experimental::filesystem::path> files_sorted;
    for (const std::experimental::filesystem::directory_entry& entry :
        std::experimental::filesystem::directory_iterator(path))
    {
        files_sorted.insert(entry.path());
    }
    // Now print them all
    for (const std::experimental::filesystem::path& path : files_sorted)
    {
        std::cout << path << "\n";
    }
    std::cout << "\n";

    std::cout << "**Recursively** printing all files and folders in path \"" << path <<
        "\" **SORTED**:\n";
    // To auto-sort the files alphabetically, we can place them into a `std::set<>`!
    std::set<std::experimental::filesystem::path> files_recursive_sorted;
    for (const std::experimental::filesystem::directory_entry& entry :
        std::experimental::filesystem::recursive_directory_iterator(path))
    {
        files_recursive_sorted.insert(entry.path());
    }
    // Now print them all
    for (const std::experimental::filesystem::path& path : files_recursive_sorted)
    {
        std::cout << path << "\n";
    }
    std::cout << "\n";


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ time g++ -Wall -Wextra -Werror -O3 -std=c++17 std_experimental_filesystem__list_files_and_dirs.cpp -o bin/a -lstdc++fs && bin/a

    real    0m0.794s
    user    0m0.724s
    sys 0m0.070s
    Hello world!

    Printing all files and folders in path ""json/include/nlohmann"":
    "json/include/nlohmann/thirdparty"
    "json/include/nlohmann/adl_serializer.hpp"
    "json/include/nlohmann/detail"
    "json/include/nlohmann/ordered_map.hpp"
    "json/include/nlohmann/json_fwd.hpp"
    "json/include/nlohmann/byte_container_with_subtype.hpp"
    "json/include/nlohmann/json.hpp"

    **Resursively** printing all files and folders in path ""json/include/nlohmann"":
    "json/include/nlohmann/thirdparty"
    "json/include/nlohmann/thirdparty/hedley"
    "json/include/nlohmann/thirdparty/hedley/hedley.hpp"
    "json/include/nlohmann/thirdparty/hedley/hedley_undef.hpp"
    "json/include/nlohmann/adl_serializer.hpp"
    "json/include/nlohmann/detail"
    "json/include/nlohmann/detail/macro_scope.hpp"
    "json/include/nlohmann/detail/exceptions.hpp"
    "json/include/nlohmann/detail/iterators"
    "json/include/nlohmann/detail/iterators/json_reverse_iterator.hpp"
    "json/include/nlohmann/detail/iterators/primitive_iterator.hpp"
    "json/include/nlohmann/detail/iterators/iteration_proxy.hpp"
    "json/include/nlohmann/detail/iterators/iter_impl.hpp"
    "json/include/nlohmann/detail/iterators/iterator_traits.hpp"
    "json/include/nlohmann/detail/iterators/internal_iterator.hpp"
    "json/include/nlohmann/detail/json_pointer.hpp"
    "json/include/nlohmann/detail/conversions"
    "json/include/nlohmann/detail/conversions/from_json.hpp"
    "json/include/nlohmann/detail/conversions/to_chars.hpp"
    "json/include/nlohmann/detail/conversions/to_json.hpp"
    "json/include/nlohmann/detail/output"
    "json/include/nlohmann/detail/output/serializer.hpp"
    "json/include/nlohmann/detail/output/binary_writer.hpp"
    "json/include/nlohmann/detail/output/output_adapters.hpp"
    "json/include/nlohmann/detail/value_t.hpp"
    "json/include/nlohmann/detail/hash.hpp"
    "json/include/nlohmann/detail/meta"
    "json/include/nlohmann/detail/meta/void_t.hpp"
    "json/include/nlohmann/detail/meta/type_traits.hpp"
    "json/include/nlohmann/detail/meta/cpp_future.hpp"
    "json/include/nlohmann/detail/meta/detected.hpp"
    "json/include/nlohmann/detail/meta/is_sax.hpp"
    "json/include/nlohmann/detail/meta/call_std"
    "json/include/nlohmann/detail/meta/call_std/begin.hpp"
    "json/include/nlohmann/detail/meta/call_std/end.hpp"
    "json/include/nlohmann/detail/meta/identity_tag.hpp"
    "json/include/nlohmann/detail/string_escape.hpp"
    "json/include/nlohmann/detail/string_concat.hpp"
    "json/include/nlohmann/detail/input"
    "json/include/nlohmann/detail/input/position_t.hpp"
    "json/include/nlohmann/detail/input/binary_reader.hpp"
    "json/include/nlohmann/detail/input/parser.hpp"
    "json/include/nlohmann/detail/input/json_sax.hpp"
    "json/include/nlohmann/detail/input/input_adapters.hpp"
    "json/include/nlohmann/detail/input/lexer.hpp"
    "json/include/nlohmann/detail/json_ref.hpp"
    "json/include/nlohmann/detail/macro_unscope.hpp"
    "json/include/nlohmann/ordered_map.hpp"
    "json/include/nlohmann/json_fwd.hpp"
    "json/include/nlohmann/byte_container_with_subtype.hpp"
    "json/include/nlohmann/json.hpp"

    Printing all files and folders in path ""json/include/nlohmann"" **SORTED**:
    "json/include/nlohmann/adl_serializer.hpp"
    "json/include/nlohmann/byte_container_with_subtype.hpp"
    "json/include/nlohmann/detail"
    "json/include/nlohmann/json.hpp"
    "json/include/nlohmann/json_fwd.hpp"
    "json/include/nlohmann/ordered_map.hpp"
    "json/include/nlohmann/thirdparty"

    **Recursively** printing all files and folders in path ""json/include/nlohmann"" **SORTED**:
    "json/include/nlohmann/adl_serializer.hpp"
    "json/include/nlohmann/byte_container_with_subtype.hpp"
    "json/include/nlohmann/detail"
    "json/include/nlohmann/detail/conversions"
    "json/include/nlohmann/detail/conversions/from_json.hpp"
    "json/include/nlohmann/detail/conversions/to_chars.hpp"
    "json/include/nlohmann/detail/conversions/to_json.hpp"
    "json/include/nlohmann/detail/exceptions.hpp"
    "json/include/nlohmann/detail/hash.hpp"
    "json/include/nlohmann/detail/input"
    "json/include/nlohmann/detail/input/binary_reader.hpp"
    "json/include/nlohmann/detail/input/input_adapters.hpp"
    "json/include/nlohmann/detail/input/json_sax.hpp"
    "json/include/nlohmann/detail/input/lexer.hpp"
    "json/include/nlohmann/detail/input/parser.hpp"
    "json/include/nlohmann/detail/input/position_t.hpp"
    "json/include/nlohmann/detail/iterators"
    "json/include/nlohmann/detail/iterators/internal_iterator.hpp"
    "json/include/nlohmann/detail/iterators/iter_impl.hpp"
    "json/include/nlohmann/detail/iterators/iteration_proxy.hpp"
    "json/include/nlohmann/detail/iterators/iterator_traits.hpp"
    "json/include/nlohmann/detail/iterators/json_reverse_iterator.hpp"
    "json/include/nlohmann/detail/iterators/primitive_iterator.hpp"
    "json/include/nlohmann/detail/json_pointer.hpp"
    "json/include/nlohmann/detail/json_ref.hpp"
    "json/include/nlohmann/detail/macro_scope.hpp"
    "json/include/nlohmann/detail/macro_unscope.hpp"
    "json/include/nlohmann/detail/meta"
    "json/include/nlohmann/detail/meta/call_std"
    "json/include/nlohmann/detail/meta/call_std/begin.hpp"
    "json/include/nlohmann/detail/meta/call_std/end.hpp"
    "json/include/nlohmann/detail/meta/cpp_future.hpp"
    "json/include/nlohmann/detail/meta/detected.hpp"
    "json/include/nlohmann/detail/meta/identity_tag.hpp"
    "json/include/nlohmann/detail/meta/is_sax.hpp"
    "json/include/nlohmann/detail/meta/type_traits.hpp"
    "json/include/nlohmann/detail/meta/void_t.hpp"
    "json/include/nlohmann/detail/output"
    "json/include/nlohmann/detail/output/binary_writer.hpp"
    "json/include/nlohmann/detail/output/output_adapters.hpp"
    "json/include/nlohmann/detail/output/serializer.hpp"
    "json/include/nlohmann/detail/string_concat.hpp"
    "json/include/nlohmann/detail/string_escape.hpp"
    "json/include/nlohmann/detail/value_t.hpp"
    "json/include/nlohmann/json.hpp"
    "json/include/nlohmann/json_fwd.hpp"
    "json/include/nlohmann/ordered_map.hpp"
    "json/include/nlohmann/thirdparty"
    "json/include/nlohmann/thirdparty/hedley"
    "json/include/nlohmann/thirdparty/hedley/hedley.hpp"
    "json/include/nlohmann/thirdparty/hedley/hedley_undef.hpp"



*/
