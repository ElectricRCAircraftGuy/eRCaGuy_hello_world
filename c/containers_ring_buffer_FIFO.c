///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm -latomic && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
9 May 2023
Based on skills learned from 2012 to 2023.

Demonstrate a basic, efficient ring buffer FIFO in C (that also runs in C++).

- NB: This code assumes that your hardware and compiler supports modern C11 (see here:
  https://en.cppreference.com/w/c/thread#Atomic_operations) or C++11 (see here:
  https://en.cppreference.com/w/cpp/atomic/atomic) atomic types, so that the ring buffer array
  data (stored in `array`), and the indices (`i_write` and `i_read`) have at least **atomic
  copies**. This means that they MUST be able to be written to or read from withOUT being
  interrupted in the middle of reading or writing bytes from or to those variables. If this is NOT
  the case for your compiler or architecture, you have two options to fix this code:

    1. Use naturally-atomic read-and-write types for those 3 variables.

        1. For 8-bit Arduino AVR microcontrollers, that means they must be **8-bit** variable types!
            Ex:
            ```cpp
            uint8_t* array;  // for the data in the ring buffer
            uint8_t i_write; // ring buffer write index
            uint8_t i_read;  // ring buffer read index
            ```
            See my detailed Q&A here: https://stackoverflow.com/a/39693278/4561887

        1. For 32-bit STM32 microcontrollers, that means they must be **32-bit or smaller** variable
        types! See my answer here: https://stackoverflow.com/a/52785864/4561887

    2. Use atomic access guards. See some of my very-detailed Q&As on this here:
        1. my Q&A on STM32 mcus: https://stackoverflow.com/q/71626597/4561887
        1. my Q&A on Arduino AVR mcus: https://stackoverflow.com/a/39693278/4561887
        1. my ans. on spin locks: https://stackoverflow.com/a/73819087/4561887

- Note: I have written many ring buffers, and studied a variety of different techniques, and this
  implementation is the **best of all of them!** It is the best I have ever written or seen, for the
  following reasons:
  <============== REASONS WHY THIS IMPLEMENTATION IS THE BEST WAY TO DO IT ===============

    1. Benefit 1: first and foremost: this implementation is **lock free** so long as the following
    conditions are met:

        1. There is only **single-direction** usage (ex: where only the ISR ever writes and adds
        elements, and only the main loop ever reads and removes elements) **and**:

        1. The hardware & compiler supports the `atomic_*` types to guarantee atomic reads, **or**:

            1. the variable types are small enough to have **naturally atomic** reads and writes
            (see above), or

            1. atomic access guards are used for all reads and writes on the 3 variables of
            interest (data and indices x 2) (see above).

    2. Benefit 2: it does NOT have the "reduced by one" problem, where the usable space in the array
    has to be reduced by 1 element in order to see when the buffer is full.

    3. Benefit 3: it does NOT have to store an additional `size_t count` variable to count the
    number of elements in the array.

        - Rather, this implementation works by **never** writing the "modulus"ed value into the
          `i_write` and `i_read` indices. This way, the buffer is empty if `i_write == i_read`, and
          it is full if `i_write - i_read == len`. This works because for a buffer of length 2, for
          instance, `i_read` might be 0, for instance, while `i_write` is 2 (where `2 % len` is 0).
          If you performed the modulus and *then* stored that "modulus"ed value into `i_read` and
          `i_write` instead, then `i_write` would be 0 instead of 2, and you'd have a situation
          where `i_write - i_read` would equal 0 *both* when it is empty *and* when it is full!

          This is problematic, as you would have no way to identify when the buffer is full vs.
          empty without violating one of my other two bullets just above. That's the ingenuity of
          this approach! I came up with it on my own during a live interview years ago. I had never
          seen nor heard of this approach before, but when it occurred to me, I knew it was the
          best approach I had ever seen, and I have since decided to make it my standard way of
          doing ring buffers. The only reason I might change and use a different technique is if
          this approach of performing the modulus operation **during indexing usage** turns out to
          be slower. In that case, I might make the tiny sacrifice in **space efficiency** to get a
          gain in **time efficiency**, but I haven't yet done any speed profiling to see if that is
          a time gain that can be achieved.

STATUS: done and works!

TODO:
1. [ ] Break this out into its own library module, and write unit tests (using gtest in C++) for it
   too! New files that will be created:

    1. containers_ring_buffer_FIFO_lib.h
    1. containers_ring_buffer_FIFO_lib.c
    1. containers_ring_buffer_FIFO_lib_unittest.cpp

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS: interview prep

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./containers_ring_buffer_FIFO.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 containers_ring_buffer_FIFO.c -o bin/a -lm -latomic && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 containers_ring_buffer_FIFO.c -o bin/a -latomic && bin/a
```

References:

1. ***** [my answer] Here are all techniques I am aware of to force atomicity in Atmel
   AVR microcontrollers, such as Arduino - https://stackoverflow.com/a/39693278/4561887
1. Ring buffer - https://en.m.wikipedia.org/wiki/Circular_buffer
1. [my answer] Efficiently rotating a 2D array up by treating it as a "ring
   buffer" or "circular buffer" - https://stackoverflow.com/a/76210820/4561887
1. [my answer] Error codes and error handling in C - https://stackoverflow.com/a/59221452/4561887
1. Atomic variable types:
    1. In C:    https://en.cppreference.com/w/c/thread#Atomic_operations
    1. In C++:  https://en.cppreference.com/w/cpp/atomic/atomic
    1.          https://en.cppreference.com/w/cpp/header/atomic
    1. ---
    1.          https://en.cppreference.com/w/cpp/header/stdatomic.h
1. eRCaGuy_hello_world/c/atomic_types.c
    1. My answer with some of this code: https://stackoverflow.com/a/76223047/4561887

*/

#ifdef __cplusplus
    #include <atomic> // for `atomic_*` types in C++
    // This is required for C++ since all `atomic_*` type aliases are in namespace `std`, as in
    // `std::atomic_bool`, for instance, instead of just `atomic_bool`!
    using namespace std;
#else
    #include <stdatomic.h> // for `atomic_*` types in C
#endif

#include <assert.h>  // For `static_assert()` in C. See my answer:
                     // https://stackoverflow.com/a/54993033/4561887
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`


/// Get the number of elements in any C array
/// - Usage example: [my own answer]:
///   https://arduino.stackexchange.com/a/80289/7727
#define ARRAY_LEN(array) (sizeof(array) / sizeof((array)[0]))

/// The ring buffer object.
typedef struct ring_buffer_s
{
    /// Ptr to an array of the data you want to store.
    /// - Choose the correct type here for your data. I'll use `int`.
    volatile atomic_int* array;

    // Note: you can replace the `size_t` type in all 3 places below with any **unsigned** integer
    // type, such as `uint8_t`, `uint16_t`, `uint32_t`, etc., if desired, for space efficiency, so
    // long as it is big enough to store your desired max number of elements in the buffer.

    /// Length, or number of elements, the array above can store.
    /// - NB to the user of this API: choosing a power-of-2 length (ex: 2, 4, 8, 16, 32, 64, ...,
    ///   2048, 4096, etc.) makes this ring buffer waaaay more efficient, because the modulus
    ///   operator on a power-of-2 number gets reduced to a simple instruction.
    size_t len;

    // NB: for efficiency and simplicity, **and especially** for the ability to see when the buffer
    // is full! [this is ingenious!], for the following two indices, we will **not** store
    // the "modulus"ed value into the index variables. Instead, we will perform the modulus
    // operation only at usage time when we *use* this index!
    //
    // This way, we can always tell when the ring buffer is **empty** because `i_write == i_read`,
    // and we can tell when the ring buffer is **full* because `i_write - i_read == len`. See more
    // on this in my discussion notes at the top of this file.

    /// The write index where you will write new data.
    volatile atomic_size_t i_write;

    /// The read index where you will read out the oldest data.
    volatile atomic_size_t i_read;
} ring_buffer_t;


// "Unsafe" versions


/// \brief          Initialize a ring buffer object.
/// \param[in]      ring_buffer     Ptr to the ring buffer object to be initialized
/// \param[in]      array           The array where the data will be written.
/// \param[in]      len             The length of (# of elements in) the array.
/// \return         None
void ring_buffer_init(ring_buffer_t* ring_buffer, atomic_int* array, size_t len)
{
    // Watch out: we are *not* checking for NULL input ptrs here, to make this safer.

    ring_buffer->array = array;
    ring_buffer->len = len;
    ring_buffer->i_write = 0;
    ring_buffer->i_read = 0;
}

/// An *un*safe write function to add an element into the buffer. It does NOT check for overwrite
/// when the buffer is full.
void ring_buffer_write(ring_buffer_t* ring_buffer, int data)
{
    ring_buffer->array[ring_buffer->i_write % ring_buffer->len] = data;
    (ring_buffer->i_write)++;
}

/// An *un*safe read function to read an element from the buffer. It does NOT check to ensure
/// valid, previously-written data is being read.
int ring_buffer_read(ring_buffer_t* ring_buffer)
{
    int data = ring_buffer->array[ring_buffer->i_read % ring_buffer->len];
    (ring_buffer->i_read)++;
    return data;
}


// "Safe" versions, with error-checking code


/// Ring buffer library error codes
typedef enum ring_buffer_error_e
{
    /// No error
    RING_BUFFER_ERROR_OK = 0,

    /// Invalid arguments (ex: NULL pointer where a valid pointer is required)
    RING_BUFFER_ERROR_INVARG,

    /// Buffer is full
    RING_BUFFER_ERROR_FULL,

    /// Buffer is empty
    RING_BUFFER_ERROR_EMPTY,

    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value 0 and you let it
    /// naturally increment from there, as is done above, without explicitly altering any error
    /// values above
    RING_BUFFER_ERROR_COUNT,
} ring_buffer_error_t;

/// Array of strings to map enum error types to printable strings
const char* const RING_BUFFER_ERROR_STRS[] =
{
    "RING_BUFFER_ERROR_OK",
    "RING_BUFFER_ERROR_INVARG",
    "RING_BUFFER_ERROR_FULL",
    "RING_BUFFER_ERROR_EMPTY",
};
static_assert(ARRAY_LEN(RING_BUFFER_ERROR_STRS) == RING_BUFFER_ERROR_COUNT,
    "You must keep your `ring_buffer_error_t` enum and your "
    "`RING_BUFFER_ERROR_STRS` array in-sync!");

/// \brief      Function to get a printable string from an enum error type
/// \param[in]  err     a valid error code for this module
/// \return     A printable C string corresponding to the error code input above, or NULL if an
///             invalid error code was passed in
const char* ring_buffer_error_str(ring_buffer_error_t err)
{
    const char* err_str = NULL;

    // Ensure error codes are within the valid array index range
    if (err >= RING_BUFFER_ERROR_COUNT)
    {
        return err_str;
    }

    err_str = RING_BUFFER_ERROR_STRS[err];

    return err_str;
}

/// Get the number of elements currently stored inside the ring buffer
size_t ring_buffer_get_count(const ring_buffer_t* ring_buffer)
{
    // NB: this implementation is **lock-free** for **single-direction** usage! See notes at the top
    // of this file for details. Therefore, no atomic access guards nor concurrency primitives are
    // needed here, so long as `i_write` and `i_read` both have at least **atomic read** capability!
    size_t num_elements_in_buffer = ring_buffer->i_write - ring_buffer->i_read;
    return num_elements_in_buffer;
}

/// See if the buffer is full. Returns true if full, or false otherwise.
bool ring_buffer_get_is_full(const ring_buffer_t* ring_buffer)
{
    bool buffer_is_full = ring_buffer_get_count(ring_buffer) == ring_buffer->len;
    return buffer_is_full;
}

/// See if the buffer is empty. Returns true if empty, or false otherwise.
bool ring_buffer_get_is_empty(const ring_buffer_t* ring_buffer)
{
    bool buffer_is_empty = ring_buffer_get_count(ring_buffer) == 0;
    return buffer_is_empty;
}

/// A safe version of writing into the ring buffer, which returns proper errors if you pass in a
/// null ptr or if the buffer is full.
ring_buffer_error_t ring_buffer_write_safe(ring_buffer_t* ring_buffer, int data)
{
    if (ring_buffer == NULL)
    {
        return RING_BUFFER_ERROR_INVARG;
    }

    // Check if the ring buffer is full
    if (ring_buffer_get_is_full(ring_buffer))
    {
        return RING_BUFFER_ERROR_FULL;
    }

    ring_buffer_write(ring_buffer, data);

    return RING_BUFFER_ERROR_OK;
}

/// A safe version of reading from the ring buffer, which returns proper errors if you pass in a
/// null ptr or if the buffer is empty.
/// The read value is passed out via the output ptr `data`.
ring_buffer_error_t ring_buffer_read_safe(ring_buffer_t* ring_buffer, int* data)
{
    if (ring_buffer == NULL)
    {
        return RING_BUFFER_ERROR_INVARG;
    }

    // Check if the ring buffer is empty
    if (ring_buffer_get_is_empty(ring_buffer))
    {
        return RING_BUFFER_ERROR_EMPTY;
    }

    int data_ = ring_buffer_read(ring_buffer);
    *data = data_;

    return RING_BUFFER_ERROR_OK;
}


// Make the ring buffer global (and with `volatile` members) so that it can be shared between an ISR
// and your main loop. This way the ISR can write to it, for instance, while the main loop reads
// from it.
#define NUM_ELEMENTS 8
ring_buffer_t ring_buffer;
atomic_int array[NUM_ELEMENTS];

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Highly-efficient ring buffer demo.\n\n");

    ring_buffer_init(&ring_buffer, array, ARRAY_LEN(array));
    printf("Ring buffer size is %zu.\n\n", ring_buffer.len);

    ring_buffer_error_t ring_buffer_error;
    int data;

    // try to read; it should fail
    printf("Attempting to read.\n");
    ring_buffer_error = ring_buffer_read_safe(&ring_buffer, &data);
    if (ring_buffer_error != RING_BUFFER_ERROR_OK)
    {
        printf("Error: %s.\n\n", ring_buffer_error_str(ring_buffer_error));
    }

    // Now write until it is full.
    //
    // NB: an ISR could be doing this writing, and it is still perfectly safe with my
    // implementation, again, so long as the data is only moving **one context direction**-ex: from
    // the ISR to the main loop, and NOT also from the main loop to the ISR.
    ring_buffer_error = RING_BUFFER_ERROR_OK;
    int fake_data = 0;
    while (ring_buffer_error == RING_BUFFER_ERROR_OK)
    {
        printf("Attempting to write %i. ", fake_data);
        ring_buffer_error = ring_buffer_write_safe(&ring_buffer, fake_data);
        if (ring_buffer_error != RING_BUFFER_ERROR_OK)
        {
            printf("Error: %s.\n\n", ring_buffer_error_str(ring_buffer_error));
            continue;
        }
        else
        {
            printf("Done.\n");
        }

        fake_data++;
    }

    // Now read until it is empty
    printf("Reading out data until the buffer is empty.\n");
    ring_buffer_error = RING_BUFFER_ERROR_OK;
    size_t i = 0;
    while (ring_buffer_error == RING_BUFFER_ERROR_OK)
    {
        ring_buffer_error = ring_buffer_read_safe(&ring_buffer, &data);
        if (ring_buffer_error != RING_BUFFER_ERROR_OK)
        {
            printf("Error: %s.\n", ring_buffer_error_str(ring_buffer_error));
            continue;
        }

        printf("%3zu: %3i\n", i, data);
        i++;
    }


    return 0;
}


/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ ./containers_ring_buffer_FIFO.c
    Highly-efficient ring buffer demo.

    Ring buffer size is 8.

    Attempting to read.
    Error: RING_BUFFER_ERROR_EMPTY.

    Attempting to write 0. Done.
    Attempting to write 1. Done.
    Attempting to write 2. Done.
    Attempting to write 3. Done.
    Attempting to write 4. Done.
    Attempting to write 5. Done.
    Attempting to write 6. Done.
    Attempting to write 7. Done.
    Attempting to write 8. Error: RING_BUFFER_ERROR_FULL.

    Reading out data until the buffer is empty.
      0:   0
      1:   1
      2:   2
      3:   3
      4:   4
      5:   5
      6:   6
      7:   7
    Error: RING_BUFFER_ERROR_EMPTY.



OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 containers_ring_buffer_FIFO.c -o bin/a && bin/a

    [same output as in C, above]

*/
