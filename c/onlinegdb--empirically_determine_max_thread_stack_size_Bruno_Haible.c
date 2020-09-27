/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

Gabriel Staples
www.ElectricRCAircraftGuy.com
26 Sept. 2020

empirically_determine_max_thread_stack_size

You can run this as a C OR C++ program!

References:
1. https://stackoverflow.com/questions/1825964/c-c-maximum-stack-size-of-program/1826072#1826072
1. https://lists.gnu.org/archive/html/bug-coreutils/2009-10/msg00262.html
    Originally by Bruno Haible, here, 24 Oct. 2009

I've added some minor changes to it for readability, clarity, and efficiency.

Build and run command:

    mkdir -p bin && \
    gcc -Wall -Werror -g3 -O3 -std=c11 -pthread -o bin/tmp \
    onlinegdb--empirically_determine_max_thread_stack_size_Bruno_Haible.c && \
    time bin/tmp

*******************************************************************************/

// By Bruno Haible
// 24 Oct. 2009
// Source: https://lists.gnu.org/archive/html/bug-coreutils/2009-10/msg00262.html

// =============== Program for determining the default thread stack size =========

#include <alloca.h>
#include <pthread.h>
#include <stdio.h>
void* threadfunc (void*p) {
  int n = 0;
  for (;;) {
    printf("Allocated %d bytes\n", n);
    fflush(stdout);
    n += 128;
    *((volatile char *) alloca(128)) = 0;
  }
}

int main()
{
  pthread_t thread;
  pthread_create(&thread, NULL, threadfunc, NULL);
  for (;;) {}
}



