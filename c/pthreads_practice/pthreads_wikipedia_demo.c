/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Sept. 2021

Practice using pthreads (POSIX threads). ESSENTIALLY COPY-PASTED FROM WIKIPEDIA (see link below)!

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj -pthread pthreads_wikipedia_demo.c \
    -o bin/pthreads_wikipedia_demo && bin/pthreads_wikipedia_demo
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj -pthread pthreads_wikipedia_demo.c \
    -o bin/pthreads_wikipedia_demo && bin/pthreads_wikipedia_demo

References:
1. [the code below] https://en.wikipedia.org/wiki/Pthreads
1. [how to build pthread in Linux; ie: with `gcc -pthread`]
   https://stackoverflow.com/questions/1662909/undefined-reference-to-pthread-create-in-linux/1665110#1665110

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

void *perform_work(void *arguments)
{
    int index = *((int *)arguments);
    int sleep_time = 1 + rand() % NUM_THREADS;
    printf("THREAD %d: Started.\n", index);
    printf("THREAD %d: Will be sleeping for %d seconds.\n", index, sleep_time);
    sleep(sleep_time);
    printf("THREAD %d: Ended.\n", index);

    return NULL;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
    int result_code;

    //create all threads one by one
    for (i = 0; i < NUM_THREADS; i++) {
        printf("IN MAIN: Creating thread %d.\n", i);
        thread_args[i] = i;
        result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
        assert(!result_code);
    }

    printf("IN MAIN: All threads are created.\n");

    //wait for each thread to complete
    for (i = 0; i < NUM_THREADS; i++) {
        result_code = pthread_join(threads[i], NULL);
        assert(!result_code);
        printf("IN MAIN: Thread %d has ended.\n", i);
    }

    printf("MAIN program has ended.\n");
    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c/pthreads_practice$ mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj -pthread pthreads_wikipedia_demo.c \
    >     -o bin/pthreads_wikipedia_demo && bin/pthreads_wikipedia_demo
    IN MAIN: Creating thread 0.
    IN MAIN: Creating thread 1.
    THREAD 0: Started.
    THREAD 0: Will be sleeping for 4 seconds.
    THREAD 1: Started.
    THREAD 1: Will be sleeping for 2 seconds.
    IN MAIN: Creating thread 2.
    IN MAIN: Creating thread 3.
    THREAD 2: Started.
    THREAD 2: Will be sleeping for 3 seconds.
    IN MAIN: Creating thread 4.
    THREAD 3: Started.
    THREAD 3: Will be sleeping for 1 seconds.
    IN MAIN: All threads are created.
    THREAD 4: Started.
    THREAD 4: Will be sleeping for 4 seconds.
    THREAD 3: Ended.
    THREAD 1: Ended.
    THREAD 2: Ended.
    THREAD 0: Ended.
    THREAD 4: Ended.
    IN MAIN: Thread 0 has ended.
    IN MAIN: Thread 1 has ended.
    IN MAIN: Thread 2 has ended.
    IN MAIN: Thread 3 has ended.
    IN MAIN: Thread 4 has ended.
    MAIN program has ended.

OR, in C++ (same type of output as above); ex:

    eRCaGuy_hello_world/c/pthreads_practice$ mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj -pthread pthreads_wikipedia_demo.c \
    >     -o bin/pthreads_wikipedia_demo && bin/pthreads_wikipedia_demo
    IN MAIN: Creating thread 0.
    IN MAIN: Creating thread 1.
    IN MAIN: Creating thread 2.
    THREAD 0: Started.
    THREAD 0: Will be sleeping for 4 seconds.
    IN MAIN: Creating thread 3.
    IN MAIN: Creating thread 4.
    THREAD 1: Started.
    THREAD 1: Will be sleeping for 2 seconds.
    IN MAIN: All threads are created.
    THREAD 2: Started.
    THREAD 2: Will be sleeping for 1 seconds.
    THREAD 3: Started.
    THREAD 3: Will be sleeping for 3 seconds.
    THREAD 4: Started.
    THREAD 4: Will be sleeping for 4 seconds.
    THREAD 2: Ended.
    THREAD 1: Ended.
    THREAD 3: Ended.
    THREAD 0: Ended.
    THREAD 4: Ended.
    IN MAIN: Thread 0 has ended.
    IN MAIN: Thread 1 has ended.
    IN MAIN: Thread 2 has ended.
    IN MAIN: Thread 3 has ended.
    IN MAIN: Thread 4 has ended.
    MAIN program has ended.

*/
