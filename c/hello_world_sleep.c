/*
hello_world_sleep

Gabriel Staples
www.ElectricRCAircraftGuy.com
25 Apr. 2019 

Examples of how to compile & run:
- NB: c90 requires C-style comments (slash star, star slash) and does NOT work with modern
      C++-style // comments!
  C:
    gcc -Wall -g3 -o hello_world_sleep hello_world_sleep.c && ./hello_world_sleep
    gcc -Wall -g3 -std=c90 -o hello_world_sleep hello_world_sleep.c && ./hello_world_sleep
    gcc -Wall -g3 -std=c99 -o hello_world_sleep hello_world_sleep.c && ./hello_world_sleep
    gcc -Wall -g3 -std=c11 -o hello_world_sleep hello_world_sleep.c && ./hello_world_sleep   <====== I'M BUILDING WITH THIS ONE!
  C++:
    g++ -Wall -g3 -o hello_world_sleep hello_world_sleep.c && ./hello_world_sleep
    g++ -Wall -g3 -std=c++98 -o hello_world_sleep hello_world_sleep.c && ./hello_world_sleep
    g++ -Wall -g3 -std=c++03 -o hello_world_sleep hello_world_sleep.c && ./hello_world_sleep
    g++ -Wall -g3 -std=c++11 -o hello_world_sleep hello_world_sleep.c && ./hello_world_sleep

Note: `-g3` adds full debugging info! See the `-g` and `-glevel` options here: 
      https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html

References:
- this code posted as my answer here! https://stackoverflow.com/a/55384270/4561887 
- Sleep:
  - https://stackoverflow.com/questions/1157209/is-there-an-alternative-sleep-function-in-c-to-milliseconds/28827188#28827188
  - http://man7.org/linux/man-pages/man2/nanosleep.2.html
  - [MY OWN ANS!] https://stackoverflow.com/questions/10053788/implicit-declaration-of-function-usleep/55860234#55860234

*/

#include <stdio.h>   // for printf
#include <stdbool.h> // for `true` and `false`
#include <unistd.h>

// sleep_ms() function
// See: https://stackoverflow.com/a/28827188/4561887
//      and http://man7.org/linux/man-pages/man2/nanosleep.2.html
#define __USE_POSIX199309
#define _POSIX_C_SOURCE 199309L

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds) // cross-platform sleep function
{
#ifdef WIN32
    // printf("WIN32\n");
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    // printf("_POSIX_C_SOURCE >= 199309L\n");
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    // printf("Others\n");
    usleep(milliseconds * 1000);
#endif
}

int main(void)
{
    printf("\n");

    for (int i = 0; i < 100; i++)
    {
        printf("%i: Hello sleep\n", i + 1);
        // sleep(1);
        sleep_ms(50);
    }

    return 0;
}



