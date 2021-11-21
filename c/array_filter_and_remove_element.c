/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Gabriel Staples
19 Nov. 2021

Demonstrate how to "remove an element" from an array in C. You might also call this "filtering an
array" in C. I demonstrate 2 approaches:
1. [better] copy the array into a new array (the clean and easy approach), but takes 2x array memory
2. filter the array in-pace (the hard and copy-intensive approach), but takes no extra array memory

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj array_filter_and_remove_element.c \
    -o bin/array_filter_and_remove_element && bin/array_filter_and_remove_element
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj array_filter_and_remove_element.c \
    -o bin/array_filter_and_remove_element && bin/array_filter_and_remove_element

References:
1. [posted as my answer here] https://stackoverflow.com/a/70043744/4561887
1. OnlineGDB Share link: [my project called "filter_array_in_c"] https://onlinegdb.com/7zjgh56OB

*/

#include <stdbool.h>
#include <stdio.h>

/// Get the number of elements in an array
#define ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))

/// Return false for -1, 0, or +1, and return true otherwise.
bool is_it_right(int i)
{
    if (i/2 == 0)
    {
        return false;
    }

    return true;
}

void print_array(const int arr[], size_t len)
{
    printf("[");
    for (size_t i = 0; i < len; i++)
    {
        printf("%i", arr[i]);
        if (i < len - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

int main()
{
    /////////////////// THIS ANSWER IS A BIT OF A WORK-IN-PROGRESS STILL, BUT IT IS CORRECT AND
    ////////// DOES WORK AS-IS. I JUST NEED TO CLEAN IT UP A BIT IS ALL.

    printf("\n====================================\n"
           "APPROACH 0: MODIFY ARRAY IN-PLACE IN O(1) TIME\n"
           "====================================\n");
    {
        int arr[] = {-3, -2, -1, 0, 1, 2, 3};
        print_array(arr, ARRAY_LEN(arr));
        size_t arr_len; // this will store the array's new length after modifications to it

        // Remove values -1, 0, and +1 from the array
        size_t i_write = 0;
        for (size_t i_read = 0; i_read < ARRAY_LEN(arr); i_read++)
        {
            if (is_it_right(arr[i_read]))
            {
                arr[i_write] = arr[i_read];
                i_write++;
            }
        }
        arr_len = i_write;

        print_array(arr, arr_len);
    }

    printf("\n====================================\n"
           "APPROACH 1 [BETTER APPROACH]: FILTER AN ARRAY INTO ANOTHER ARRAY\n"
           "====================================\n");
    int arr[] = {-3, -2, -1, 0, 1, 2, 3};
    int arr_filtered[ARRAY_LEN(arr)];
    size_t arr_filtered_len;

    // Remove values -1, 0, and +1 from the array
    int j = 0;
    for (size_t i = 0; i < ARRAY_LEN(arr); i++)
    {
        if (is_it_right(arr[i]))
        {
            arr_filtered[j] = arr[i];
            j++;
        }
    }
    arr_filtered_len = j;

    print_array(arr, ARRAY_LEN(arr));
    print_array(arr_filtered, arr_filtered_len);


    printf("\n====================================\n"
           "APPROACH 2: FILTER AN ARRAY IN-PLACE\n"
           "====================================\n");

    // Remove values -1, 0, and +1 from the array **in place**
    size_t arr_len = ARRAY_LEN(arr);
    printf("Starting array:\n");
    print_array(arr, arr_len);
    size_t i = 0;
    while (i < arr_len)
    {
        if (is_it_right(arr[i]) == false)
        {
            // We don't want to keep this value at `arr[i]`, so overwrite it
            // by shifting all values from `i + 1` to the end of the array to
            // the left by 1 place.
            printf("Removing value `%i` from the array\n", arr[i]);
            size_t i_write = i;
            for (size_t i_read = i_write + 1; i_read < arr_len; i_read++)
            {
                arr[i_write] = arr[i_read];
                i_write++;
                print_array(arr, arr_len);
            }
            arr_len--;
            printf("One element has just been removed. Here is the new array:\n");
            print_array(arr, arr_len);
        }
        else // is_it_right(arr[i]) == true
        {
            // only increment `i` if we did NOT just left-shift a bunch of
            // elements by one index place
            i++;
        }
    }
    printf("Here is the final, filtered-in-place array:\n");
    print_array(arr, arr_len);


    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj array_filter_and_remove_element.c \
    >     -o bin/array_filter_and_remove_element && bin/array_filter_and_remove_element

    ====================================
    APPROACH 1 [BETTER APPROACH]: FILTER AN ARRAY INTO ANOTHER ARRAY
    ====================================
    [-3, -2, -1, 0, 1, 2, 3]
    [-3, -2, 2, 3]

    ====================================
    APPROACH 2: FILTER AN ARRAY IN-PLACE
    ====================================
    Starting array:
    [-3, -2, -1, 0, 1, 2, 3]
    Removing value `-1` from the array
    [-3, -2, 0, 0, 1, 2, 3]
    [-3, -2, 0, 1, 1, 2, 3]
    [-3, -2, 0, 1, 2, 2, 3]
    [-3, -2, 0, 1, 2, 3, 3]
    One element has just been removed. Here is the new array:
    [-3, -2, 0, 1, 2, 3]
    Removing value `0` from the array
    [-3, -2, 1, 1, 2, 3]
    [-3, -2, 1, 2, 2, 3]
    [-3, -2, 1, 2, 3, 3]
    One element has just been removed. Here is the new array:
    [-3, -2, 1, 2, 3]
    Removing value `1` from the array
    [-3, -2, 2, 2, 3]
    [-3, -2, 2, 3, 3]
    One element has just been removed. Here is the new array:
    [-3, -2, 2, 3]
    Here is the final, filtered-in-place array:
    [-3, -2, 2, 3]


OR, in C++:

    SAME AS ABOVE

*/
