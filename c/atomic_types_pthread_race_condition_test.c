/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Apr. 2022

Demonstrate how to force types in the C language to have atomic reads, atomic writes, atomic
increment, atomic decrement, and atomic compound assignment. See the extensive links and details on
this in my **question** here: https://stackoverflow.com/q/71866535/4561887.

The only guarantees for atomicity by the language standards are to use `_Atomic` types in C11 or
later or `std::atomic<>` types in C++11 or later.

STATUS & RESULTS: Done! Works great! Comment out `#define USE_ATOMIC_TYPES` below, and run it. Then
uncomment it and run it again, to compare results! You'll see that when using atomic variables, you
get the expected `10000000` (10 million) value for each counter, but when NOT using atomic
variables, you'll only get each counter up to about half that, or `4274108` (4.3 million), for
instance!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 atomic_types_pthread_race_condition_test.c -o bin/a -lm -pthread && time bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 atomic_types_pthread_race_condition_test.c -o bin/a -pthread && time bin/a
```

References:
1. [my Q] *****Which types on a 64-bit computer are naturally atomic in gnu C and gnu C++?--meaning
they have atomic reads, and atomic writes - https://stackoverflow.com/q/71866535/4561887
1. *****`_Atomic` types in C11:
    1. *****https://en.cppreference.com/w/c/thread
    1. *****https://en.cppreference.com/w/c/language/atomic
    1. https://en.cppreference.com/w/c/types/integer - explains meaning of `uint_fast32_t`,
       `uint_least32_t`, etc.
1. *****`std::atomic<>` types in C++11:
    1. https://en.cppreference.com/w/cpp/atomic/atomic
1. "pthreads_wikipedia_demo2.c"
1. https://man7.org/linux/man-pages/man3/pthread_create.3.html
1. https://man7.org/linux/man-pages/man3/pthread_join.3.html
1. How can I print value of std::atomic<unsigned int>? - Ans: use the `load()` method!:
   https://stackoverflow.com/a/51770507/4561887

1. GCC & linux atomic stuff

    1. *****gcc documentation on forced atomic memory access intrinsics - from @Raymond.Chen
    (https://stackoverflow.com/questions/71866535/which-types-on-a-64-bit-computer-are-naturally-atomic-in-gnu-c-and-gnu-c-mea#comment127012929_71866535):
    "6.55 Built-in Functions for Memory Model Aware Atomic Operations":
    https://gcc.gnu.org/onlinedocs/gcc-11.2.0/gcc/_005f_005fatomic-Builtins.html#g_t_005f_005fatomic-Builtins

    1. "/usr/include/x86_64-linux-gnu/c++/8/bits/atomic_word.h"
    1. https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_concurrency.html
    1. https://gcc.gnu.org/onlinedocs/gcc-4.6.2/libstdc++/api/a00760_source.html - atomicity.h


*/

// Linux includes
#include <pthread.h>

// C++ includes
#ifdef __cplusplus
  // `std::atomic<>` types for C++!
  #include <atomic> // See: https://en.cppreference.com/w/cpp/atomic/atomic
#endif

// C includes
#include <assert.h>
#include <inttypes.h>  // `PRIu32`, `PRIuLEAST32`, etc.
#ifndef __cplusplus
  // `atomic_uint_least32_t`-type types for C
  #include <stdatomic.h> // For `atomic_uint_least32_t`: https://en.cppreference.com/w/c/thread#Atomic_operations
#endif
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <string.h>  // `strerror()`

#define NUM_THREADS 10
#define NUM_INCREMENTS_PER_THREAD 1000000UL

/// Get the number of elements in any C array
/// - Usage example: [my own answer]:
///   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

// Variables shared between threads.
//
// Notes:
// 1. For standard multi-threading, the `volatile` keyword is NOT required! See:
// https://stackoverflow.com/q/4557979/4561887
//      - However, I use it below anyway in order to match the NOT atomic declarations further below
//        where `volatile` **is** required to prevent the increment operators from being optimized
//        out!
// 1. `volatile` **is**, however, required if sharing global variables between interrupt contexts
// and the main context, OR to map addresses to hardware registers or memory directly. See:
// https://electronics.stackexchange.com/a/409570/26234

#define USE_ATOMIC_TYPES // comment this out to use regular types!  <=========

#ifdef USE_ATOMIC_TYPES
  // `volatile` NOT required here, but I use it to match the non-atomic declarations below; see my
  // note above as well.

  #ifndef __cplusplus // For C
    volatile _Atomic uint32_t counter1; // in C
    // alternative way to do the above!--with the **smallest** type that is 32-bits or larger.
    volatile atomic_uint_least32_t counter2;
    // alternative way to do the above!--with the **fastest** type that is 32-bits or larger
    // (this type could be larger than the "least"-sized type, but is guaranteed to be the fastest
    // type with at least 32 bits).
    volatile atomic_uint_fast32_t counter3;
    // atomic_uint32_t counter4; // INVALID IN C!

  #else  // For C++
    // volatile _Atomic uint32_t counter1; // in C
    volatile std::atomic<uint32_t> counter1; // in C++
    // alternative way to do the above!--with the **smallest** type that is 32-bits or larger.
    volatile std::atomic_uint_least32_t counter2; // also in C++
    // alternative way to do the above!--with the **fastest** type that is 32-bits or larger
    // (this type could be larger than the "least"-sized type, but is guaranteed to be the fastest
    // type with at least 32 bits).
    volatile std::atomic_uint_fast32_t counter3; // also in C++
    std::atomic_uint32_t counter4; // OK in C++!

  #endif

#else // NOT using atomic types!
  // Make volatile or else these variables get optimized out and the code takes 0.001 sec to run
  // instead of much longer than that!
  volatile uint32_t counter1;
  volatile uint32_t counter2;
  volatile uint32_t counter3;
#endif

// Increment all of the atomic variables withOUT using mutexes, to prove that no race conditions are
// happening!
void * pthread_task(void * argument)
{
    (void)argument;

    for (size_t i = 0; i < NUM_INCREMENTS_PER_THREAD; i++)
    {
        // These increments are atomic for C11 `_Atomic` types, so no mutex is needed to protect
        // these variables!
        counter1++;
        counter2++;
        counter3++;
    }

    return NULL;
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("`_Atomic` types test in C.\n\n");
#ifdef USE_ATOMIC_TYPES
    printf("Using atomic types.\n");
#else
    printf("NOT using atomic types.\n");
#endif

    pthread_t threads[NUM_THREADS];
    int retcode; // return code

    // create all threads
    for (size_t i = 0; i < ARRAY_LEN(threads); i++)
    {
        printf("Creating thread %zu.\n", i);
        retcode = pthread_create(&threads[i], NULL, pthread_task, NULL);
        if (retcode != 0)
        {
            printf("Failed to create pthread. retcode = %i: %s\n", retcode, strerror(retcode));
        }
    }

    // wait for all threads to finish
    for (size_t i = 0; i < ARRAY_LEN(threads); i++)
    {
        printf("Joining (waiting for it to complete) thread %zu.\n", i);
        retcode = pthread_join(threads[i], NULL);
        if (retcode != 0)
        {
            printf("Failed to join (wait for it to complete) pthread. retcode = %i: %s\n",
                retcode, strerror(retcode));
        }
    }

    // check the atomic variables to ensure they are all the expected value now

#ifdef USE_ATOMIC_TYPES
  #ifndef __cplusplus // For C
    printf("counter1 = %" PRIu32 "\n",      counter1);
    printf("counter2 = %" PRIuLEAST32 "\n", counter2);
    printf("counter3 = %" PRIuFAST32 "\n",  counter3);
  #else // For C++
    // Use the `loac()` method to atomically read the underlying type; see:
    printf("counter1 = %" PRIu32 "\n",      counter1.load());
    printf("counter2 = %" PRIuLEAST32 "\n", counter2.load());
    printf("counter3 = %" PRIuFAST32 "\n",  counter3.load());
  #endif
#else // non-atomic types
    printf("counter1 = %" PRIu32 "\n", counter1);
    printf("counter2 = %" PRIu32 "\n", counter2);
    printf("counter3 = %" PRIu32 "\n", counter3);
#endif


    assert(counter1 == NUM_INCREMENTS_PER_THREAD*NUM_THREADS);
    assert(counter2 == NUM_INCREMENTS_PER_THREAD*NUM_THREADS);
    assert(counter3 == NUM_INCREMENTS_PER_THREAD*NUM_THREADS);

    printf("\nPASSED!\n");

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

 WITH `#define USE_ATOMIC_TYPES`

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 atomic_types_pthread_race_condition_test.c -o bin/a -lm -pthread && time bin/a
    `_Atomic` types test in C.

    Using atomic types.
    Creating thread 0.
    Creating thread 1.
    Creating thread 2.
    Creating thread 3.
    Creating thread 4.
    Creating thread 5.
    Creating thread 6.
    Creating thread 7.
    Creating thread 8.
    Creating thread 9.
    Joining (waiting for it to complete) thread 0.
    Joining (waiting for it to complete) thread 1.
    Joining (waiting for it to complete) thread 2.
    Joining (waiting for it to complete) thread 3.
    Joining (waiting for it to complete) thread 4.
    Joining (waiting for it to complete) thread 5.
    Joining (waiting for it to complete) thread 6.
    Joining (waiting for it to complete) thread 7.
    Joining (waiting for it to complete) thread 8.
    Joining (waiting for it to complete) thread 9.
    counter1 = 10000000
    counter2 = 10000000
    counter3 = 10000000

    PASSED!

    real    0m0.557s
    user    0m3.601s
    sys 0m0.000s


 With `#define USE_ATOMIC_TYPES` **commented out**:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 atomic_types_pthread_race_condition_test.c -o bin/a -lm -pthread && time bin/a
    `_Atomic` types test in C.

    NOT using atomic types.
    Creating thread 0.
    Creating thread 1.
    Creating thread 2.
    Creating thread 3.
    Creating thread 4.
    Creating thread 5.
    Creating thread 6.
    Creating thread 7.
    Creating thread 8.
    Creating thread 9.
    Joining (waiting for it to complete) thread 0.
    Joining (waiting for it to complete) thread 1.
    Joining (waiting for it to complete) thread 2.
    Joining (waiting for it to complete) thread 3.
    Joining (waiting for it to complete) thread 4.
    Joining (waiting for it to complete) thread 5.
    Joining (waiting for it to complete) thread 6.
    Joining (waiting for it to complete) thread 7.
    Joining (waiting for it to complete) thread 8.
    Joining (waiting for it to complete) thread 9.
    counter1 = 4197514
    counter2 = 5243898
    counter3 = 4612180
    a: atomic_types_pthread_race_condition_test.c:169: main: Assertion `counter1 == NUM_INCREMENTS_PER_THREAD*NUM_THREADS' failed.
    Aborted (core dumped)

    real    0m0.192s
    user    0m0.091s
    sys 0m0.009s




OR, in C++:

Same output as in C!--except for when the `#define USE_ATOMIC_TYPES` part is **commented out**, the
failed run-time assertion error is every-so-slightly different in C++ than in C:

    counter1 = 4437387
    counter2 = 4431987
    counter3 = 4424032
    a: atomic_types_pthread_race_condition_test.c:214: int main(): Assertion `counter1 == NUM_INCREMENTS_PER_THREAD*NUM_THREADS' failed.
    Aborted (core dumped)


*/
