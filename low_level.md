This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# What does "low level" mean? Do you want that? It depends. 

Consider the following examples. Which would you use? Why? What are the trade-offs of each?

Task: concatenate two strings: turn "hello" and "world" into "hello world", and print it.


## Python

```py
str1 = "hello"
str2 = "world"
str_combined = str1 + " " + str2
print(str_combined)
```


## Bash

```bash
str1="hello"
str2="world"
str_combined="$str1 $str2"
echo "$str_combined"
```


## C

```c
#include <string.h>
#include <stdio.h>

const char str1[] = "hello";
const char str2[] = "world";

int main()
{
    // the null terminator in str1 will become a space, and the null terminator
    // in str2 will still be there, so this is long enough for str1 + space +
    // str2
    char str_combined[sizeof(str1) + sizeof(str2)];
    
    // Write str1 into the new buffer
    strncpy(str_combined, str1, sizeof(str1));

    // Write the space after str1
    char* write_loc = str_combined + sizeof(str1) - 1;
    *write_loc = ' ';

    // Write str2 after the space
    write_loc++;
    strncpy(write_loc, str2, sizeof(str2));

    // print str_combined
    printf("%s\n", str_combined);

    return 0;
}
```


## C++

```cpp
#include <cstdio>
#include <iostream>
#include <string>

int main()
{
    std::string str1 = "hello";
    std::string str2 = "world";
    std::string str_combined = str1 + " " + str2;

    std::cout << str_combined;
    // OR
    printf("%s\n", str_combined.c_str());
}
```
