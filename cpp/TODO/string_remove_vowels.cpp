/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
14 Jan. 2022

See: https://stackoverflow.com/questions/70712858/removing-all-the-vowels-in-a-string-in-c

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj remove_vowels_in_string.cpp \
    -o bin/remove_vowels_in_string && bin/remove_vowels_in_string

References:
1.

*/

// C++ includes
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <string>

//////////// APPROACH 1: COPY TO NEW STRING
// int main()
// {
//     std::string input_str = "zjuotps";
//     std::string vowels = "aeiouyAEIOUY";

//     std::string output_str;
//     for (const char c : input_str)
//     {
//         if (vowels.find(c) == std::string::npos)
//         {
//             // char `c` is NOT in the `vowels` string, so append it to the
//             // output string
//             output_str.push_back(c);
//         }
//     }

//     std::cout << "input_str  = " << input_str << std::endl;
//     std::cout << "output_str = " << output_str << std::endl;
// }

// ///////////// APPROACH 2: modify input string in-place in a slow C++ way
// int main()
// {
//     std::string input_str = "zjuotps";
//     std::string vowels = "aeiouyAEIOUY";

//     std::cout << "BEFORE: input_str = " << input_str << std::endl;

//     size_t i = 0;
//     while (i < input_str.length())
//     {
//         char c = input_str[i];
//         if (vowels.find(c) != std::string::npos)
//         {
//             // char `c` IS in the `vowels` string, so remove it from the
//             // `input_str`
//             input_str.erase(input_str.begin() + i);
//             // do NOT increment `i` here since erasing the vowel char above just
//             // left-shifted the remaining chars in the string, meaning that we
//             // need to check the *same* index location again the next
//             // iteration!
//             continue;
//         }
//         i++;
//     }

//     std::cout << "AFTER:  input_str = " << input_str << std::endl;
// }

///////////// APPROACH 3: fast C-style array way

/// Get the number of elements in an array
#define ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))

int main()
{
    char input_str[] = "zjuotps";
    char vowels[] = "aeiouyAEIOUY";

    std::cout << "BEFORE: input_str = " << input_str << std::endl;

    // Iterate over all chars in the input string
    size_t i_write = 0;
    for (size_t i_read = 0; i_read < ARRAY_LEN(input_str); i_read++)
    {
        // Iterate over all chars in the vowels string. Only retain in the input
        // string (copying chars into the left side of the input string) all
        // chars which are NOT vowels!
        bool char_is_a_vowel = false;
        for (size_t j = 0; j < ARRAY_LEN(input_str); j++)
        {
            if (input_str[i_read] == vowels[j])
            {
                char_is_a_vowel = true;
                break;
            }
        }
        if (!char_is_a_vowel)
        {
            input_str[i_write] = input_str[i_read];
            i_write++;
        }
    }
    // null-terminate the input string at its new end location; the number of
    // chars in it (its new length) is now equal to `i_write`!
    input_str[i_write] = '\n';

    std::cout << "AFTER:  input_str = " << input_str << std::endl;
    // Just in case you need it back in this form now:
    std::string str(input_str);
    std::cout << "          C++ str = " << str << std::endl;
}

/*
SAMPLE OUTPUT:

In C++:



*/
