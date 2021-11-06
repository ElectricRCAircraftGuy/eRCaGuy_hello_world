/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2021

Practice using pthreads (POSIX threads). COPY-PASTED FROM WIKIPEDIA, then edited by myself.
Also print the thread number.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:

    mkdir -p bin && gcc -Wall -Wextra -Werror -Wno-error=pointer-to-int-cast \
    -Wno-error=int-to-pointer-cast -O3 -std=c11 -save-temps=obj -pthread pthreads_wikipedia_demo2.c \
    -o bin/pthreads_wikipedia_demo2 && bin/pthreads_wikipedia_demo2

2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -Wno-error=pointer-to-int-cast \
    -Wno-error=int-to-pointer-cast -O3 -std=c++17 -save-temps=obj -pthread pthreads_wikipedia_demo2.c \
    -o bin/pthreads_wikipedia_demo2 && bin/pthreads_wikipedia_demo2

References:
1. https://en.wikipedia.org/wiki/Pthreads

*/

// This is required in order for `syscall()` to be defined. See the example at the bottom of this
// documentation here: https://man7.org/linux/man-pages/man2/syscall.2.html
// and my comment here: https://stackoverflow.com/questions/21091000/how-to-get-thread-id-of-a-pthread-in-linux-c-program/21206357#comment122500554_32211287
#ifndef __cplusplus
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

// Definition of SYS_* constants; see: https://man7.org/linux/man-pages/man2/syscall.2.html
#include <sys/syscall.h>

// See: https://stackoverflow.com/a/63827823/4561887
#ifndef SYS_gettid
#error "SYS_gettid unavailable on this system"
#endif
#define GET_THREAD_ID() ((pid_t)syscall(SYS_gettid))

#define NUM_THREADS 5

void *perform_work(void *arguments)
{
    pid_t tid = GET_THREAD_ID();

    int index = *((int *)arguments);
    int sleep_time = 1 + rand() % NUM_THREADS;
    printf("THREAD %d: Started (tid = %i).\n", index, tid); // print tid too!
    printf("THREAD %d: Will be sleeping for %d seconds.\n", index, sleep_time);
    sleep(sleep_time);
    printf("THREAD %d: Ended.\n", index);

    // this is a bit of a hack to store an integer as though it was a pointer, but it works; to
    // avoid the error of: `error: cast to pointer from integer of different size
    // [-Werror=int-to-pointer-cast]`, however, I first cast to an `int64_t` which is the same size
    // as a ptr. I then do this in reverse later on, below, when reading this value back out.
    return (void*)(int64_t)tid;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
    int result_code;

    //create all threads one by one
    for (i = 0; i < NUM_THREADS; i++)
    {
        printf("IN MAIN: Creating thread %d.\n", i);
        thread_args[i] = i;
        result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
        assert(!result_code);
    }

    printf("IN MAIN: All threads are created.\n");

    //wait for each thread to complete
    for (i = 0; i < NUM_THREADS; i++)
    {
        void * retval;
        result_code = pthread_join(threads[i], &retval);
        assert(!result_code);
        printf("IN MAIN: Thread %d (tid = %i) has ended.\n", i, (int)(int64_t)retval);
    }

    printf("MAIN program has ended.\n");
    return 0;
}

/*
SAMPLE OUTPUT:

In C:



OR, in C++:



*/
