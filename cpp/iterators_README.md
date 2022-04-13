
- Started: approx. Jan. 2022
- Updated: Apr. 2022

_This file is a wip (work-in-progress), and needs to be cleaned up and checked and gone through by me again. I should probably move all of the examples below into their own runnable example files too!_


# C++ container iterators

Think of an iterator, `iter`, as a class object which acts like a pointer to a container's `value_type`. You can increment it (`iter++`), decrement it (`iter--`), use the arrow operator on it (ex: `iter->first` for iterators where `value_type` is a `std::pair<>`), and dereference it (use `*iter` to obtain the `value_type` directly, from the iterator)--all things which you can do with pointers too! As a matter of fact, a raw C pointer satisfies the C++ requirements to be appropriately classified as a valid type of "random access iterator" (LegacyRandomAccessIterator).


## References

1. [generally much easier-to-understand] https://www.cplusplus.com/reference/iterator/
1. [generally more thorough] https://en.cppreference.com/w/cpp/iterator


## Code examples I wrote or helped write [most of which have now been undone by others since it's a wiki]:

TODO: 
1. MOVE ALL THIS CODE TO MY REPO HERE INSTEAD SINCE IT'S NOT BEING WELL-RECEIVED ON THE WIKI, AND I REALLY NEED TO CONTINUE REFERENCING IT, AND I'M SURE OTHERS DO TOO!
1. This page too: https://en.cppreference.com/w/cpp/language/using_declaration  <--- the polymorphism and inheritance comments I had there are absolutely essential in my opinion in order to gain proper understanding. ///////////////////////// <==========  
    1. See @Cubbi's response to me here: https://en.cppreference.com/w/Talk:cpp/language/using_declaration :
    > This is not the place for a tutorial on the use of the language feature or on virtual functions. 
1. So, I think I need to keep such "tutorials" and detailed information like this confined to my personal website, my own person github repos, and, to some extent, on Stack Overflow and other Stack Exchange sites.
1. \*\*\*\*\*Analyze these pages and look at my old code samples in the "history" of these pages:
    1. https://en.cppreference.com/w/cpp/container/map
        1. https://en.cppreference.com/w/cpp/container/map/erase
    1. https://en.cppreference.com/w/cpp/container/unordered_map
        1. https://en.cppreference.com/w/cpp/container/unordered_map/erase


## Code samples I had written/edited and put on cppreference.com, but which most-likely are no longer there: 

### https://en.cppreference.com/w/cpp/container/map  
My version: https://en.cppreference.com/mwiki/index.php?title=cpp/container/map&oldid=137507 
```cpp
#include <iostream>
#include <map>
#include <string>
#include <string_view>
 
void print_map(std::string_view comment, const std::map<std::string, int>& m)
{
    std::cout << comment << "\n";

    // Demonstrate multiple ways to iterate over the `std::map`

    // ----------------------------
    // Legacy iterators
    // ----------------------------
 
    // 1. Use explicit iterator
    for (std::map<std::string, int>::const_iterator it = m.begin(); it != m.end(); it++) {
        std::cout << it->first << " = " << it->second << "; ";
    }
    std::cout << "\n";

    // 2. Use `auto` for the iterator; notice we use `cbegin()` and `cend()` 
    // here to force `auto` to be a `const_iterator`
    for (auto it = m.cbegin(); it != m.cend(); it++) {
        std::cout << it->first << " = " << it->second << "; ";
    }
    std::cout << "\n";

    // ----------------------------
    // Range-based for loops
    // ----------------------------

    // 1. Explicitly specify the `std::pair` iterator 
    for (const std::pair<const std::string, int>& n : m) {
        std::cout << n.first << " = " << n.second << "; ";
    }
    std::cout << "\n";
 
    // 2. Use `auto` for the `std::pair` iterator 
    for (const auto& n : m) {
        std::cout << n.first << " = " << n.second << "; ";
    }
    std::cout << "\n";
 
    // 3. Iterate using automatic "structured binding" to `key`, `value` variables
    //    (**since C++17**)
    for (const auto& [key, value] : m) {
        std::cout << key << " = " << value << "; ";
    }
    std::cout << "\n";
}
 
int main()
{
    // Create a map of three (strings, int) pairs
    std::map<std::string, int> m { {"CPU", 10}, {"GPU", 15}, {"RAM", 20}, };
 
    print_map("Initial map: ", m);
    std::cout << "\n";
 
    m["CPU"] = 25;  // update an existing value
    m["SSD"] = 30;  // insert a new value
    print_map("Updated map: ", m);
    std::cout << "\n";
 
    // using operator[] with non-existent key always performs an insert
    std::cout << "m[new_key] = " << m["new_key"] << "\n";
    print_map("Updated map: ", m);
}
```

### https://en.cppreference.com/w/cpp/container/map/erase
```cpp
#include <map>
#include <iostream>
 
#define IS_EVEN(num) ((num) % 2 == 0) 
#define IS_ODD(num) (!IS_EVEN(num)) 
 
int main()
{
    const std::map<int, std::string> INITIAL_MAP = {
        {1, "one" }, {2, "two" }, {3, "three"},
        {4, "four"}, {5, "five"}, {6, "six"  }
    };
    // print initial state by iterating using range-based for loop with explicit iterator
    std::cout << "Initial key:value pairs:\n";
    for (const std::pair<const int, std::string>& element : INITIAL_MAP) {
        std::cout << element.first << ": " << element.second << "\n";
    }
 
    std::cout << "\nRemove even keys using explicit iterator types\n";
    std::map<int, std::string> m = INITIAL_MAP;
    // iterate using an explicit iterator to erase all odd numbers
    for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); it++) {
        if (IS_EVEN(it->first)) {
            m.erase(it);
        }
    }
    // iterate using range-based for loop with explicit iterator to print output 
    for (const std::pair<const int, std::string>& element : m) {
        std::cout << element.first << ": " << element.second << "\n";
    }
 
    std::cout << "\nRemove odd keys using automatic iterator types\n";
    m = INITIAL_MAP;
    // iterate using `auto` iterator to erase all odd numbers
    for (auto it = m.begin(); it != m.end(); it++) {
        if (IS_ODD(it->first)) {
            m.erase(it);
        }
    }
    // iterate using range-based for loop with `auto` iterator to print output 
    for (const auto& element : m) {
        std::cout << element.first << ": " << element.second << "\n";
    }

    std::cout << "\nRemove odd keys using explicit range-based for loop\n";
    m = INITIAL_MAP;
    // iterate using explicit range-based for loop to erase all odd numbers
    for (std::pair<const int, std::string>& element : m) {
        if (IS_ODD(element.first)) {
            m.erase(element.first);
        }
    }
    // iterate using range-based for loop with explicit iterator to print output 
    for (const std::pair<const int, std::string>& element : m) {
        std::cout << element.first << ": " << element.second << "\n";
    }
}
```

### https://en.cppreference.com/w/cpp/container/unordered_map
```cpp
#include <iostream>
#include <string>
#include <unordered_map>
 
int main()
{
    // Create an unordered_map of three strings (that map to strings)
    std::unordered_map<std::string, std::string> u = {
        {"RED","#FF0000"},
        {"GREEN","#00FF00"},
        {"BLUE","#0000FF"}
    };
 
    // Helper lambda function to print key:value pairs
    auto print_key_value = [](std::string const& key, std::string const& value) {
        std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
    };

    // Legacy Iterators

    std::cout << "1. Iterate & print keys and values using explicit legacy iterator:\n";
    for( std::unordered_map<std::string, std::string>::const_iterator it = u.begin();
        it != u.end(); it++ ) {
        print_key_value(it->first, it->second);
    }
    std::cout << "\n";

    std::cout << "2. Iterate & print keys and values using automatic legacy iterator.\n"
                 "Use `cbegin()` and `cend()` here to force `auto` to mean\n"
                 "`const_iterator`.\n";
    for( auto it = u.cbegin(); it != u.cend(); it++ ) {
        print_key_value(it->first, it->second);
    }
    std::cout << "\n";
 
    // Range-based for loops

    std::cout << "1. Iterate & print keys and values of unordered_map, being\n"
                 "explicit with the type of the iterator, n:\n";
    for( const std::pair<const std::string, std::string>& n : u ) {
        print_key_value(n.first, n.second);
    }
    std::cout << "\n";
 
    std::cout << "2. Iterate & print keys and values of unordered_map,\n"
                 "using auto:\n";
    for( const auto& n : u ) {
        print_key_value(n.first, n.second);
    }
    std::cout << "\n";
 
    std::cout << "3. Iterate & print keys and values using structured binding\n"
                 "(since C++17):\n";
    for( const auto& [key, value] : u ) {
        print_key_value(key, value);
    }
    std::cout << "\n";
 
    // Add two new entries to the unordered_map
    u["BLACK"] = "#000000";
    u["WHITE"] = "#FFFFFF";
 
    std::cout << "Output values by key:\n";
    std::cout << "The HEX of color RED is:[" << u["RED"] << "]\n";
    std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "]\n\n";
 
    // Use of operator[] with non-existent key inserts a new value
    print_key_value("new_key", u["new_key"]);
    std::cout << "Iterating over the unordered_map shows `new_key` is now one\n"
                 "of the keys in the map:\n";
    for( const std::pair<const std::string, std::string>& n : u ) {
        print_key_value(n.first, n.second);
    }
}
```


## Other examples

See another example of iterating through a container using `std::for_each()` here:

### https://en.cppreference.com/w/cpp/container/map/clear
```cpp
#include <algorithm>
#include <iostream>
#include <map>
 
int main()
{
    std::map<int, char> container{{1, 'x'}, {2, 'y'}, {3, 'z'}};
 
    auto print = [](std::pair<const int, char>& n) { 
        std::cout << " " << n.first << '(' << n.second << ')'; 
    };
 
    std::cout << "Before clear:";
    std::for_each(container.begin(), container.end(), print);
    std::cout << "\nSize=" << container.size() << '\n';
 
    std::cout << "Clear\n";
    container.clear();
 
    std::cout << "After clear:";
    std::for_each(container.begin(), container.end(), print);
    std::cout << "\nSize=" << container.size() << '\n';
}
```
