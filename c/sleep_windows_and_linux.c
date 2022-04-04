/*
sleep_windows_and_linux

Gabriel Staples
www.ElectricRCAircraftGuy.com
25 Apr. 2019 

Examples of how to compile & run:
- NB: c90 requires C-style comments (slash star, star slash) and does NOT work with modern
      C++-style // comments!
  C:
    gcc -Wall -g3 -o bin/sleep_windows_and_linux sleep_windows_and_linux.c && time bin/sleep_windows_and_linux
    gcc -Wall -g3 -std=c90 -o bin/sleep_windows_and_linux sleep_windows_and_linux.c && time bin/sleep_windows_and_linux
    gcc -Wall -g3 -std=c99 -o bin/sleep_windows_and_linux sleep_windows_and_linux.c && time bin/sleep_windows_and_linux
    # I'M BUILDING WITH THIS ONE!:
    gcc -Wall -g3 -std=c11 -o bin/sleep_windows_and_linux sleep_windows_and_linux.c && time bin/sleep_windows_and_linux
  C++:
    g++ -Wall -g3 -o bin/sleep_windows_and_linux sleep_windows_and_linux.c && time bin/sleep_windows_and_linux
    g++ -Wall -g3 -std=c++98 -o bin/sleep_windows_and_linux sleep_windows_and_linux.c && time bin/sleep_windows_and_linux
    g++ -Wall -g3 -std=c++03 -o bin/sleep_windows_and_linux sleep_windows_and_linux.c && time bin/sleep_windows_and_linux
    g++ -Wall -g3 -std=c++11 -o bin/sleep_windows_and_linux sleep_windows_and_linux.c && time bin/sleep_windows_and_linux

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

/// cross-platform sleep function
void sleep_ms(int milliseconds)
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

    for (int i = 0; i < 40; i++)
    {
        printf("%i: Hello sleep\n", i + 1);
        // sleep(1);
        sleep_ms(50);
    }

    return 0;
}

/*

Sample Output:

(with 50ms sleep between each line printed)

    eRCaGuy_hello_world/c$ gcc -Wall -g3 -std=c11 -o bin/sleep_windows_and_linux sleep_windows_and_linux.c && time bin/sleep_windows_and_linux

    1: Hello sleep
    2: Hello sleep
    3: Hello sleep
    4: Hello sleep
    5: Hello sleep
    6: Hello sleep
    7: Hello sleep
    8: Hello sleep
    9: Hello sleep
    10: Hello sleep
    11: Hello sleep
    12: Hello sleep
    13: Hello sleep
    14: Hello sleep
    15: Hello sleep
    16: Hello sleep
    17: Hello sleep
    18: Hello sleep
    19: Hello sleep
    20: Hello sleep
    21: Hello sleep
    22: Hello sleep
    23: Hello sleep
    24: Hello sleep
    25: Hello sleep
    26: Hello sleep
    27: Hello sleep
    28: Hello sleep
    29: Hello sleep
    30: Hello sleep
    31: Hello sleep
    32: Hello sleep
    33: Hello sleep
    34: Hello sleep
    35: Hello sleep
    36: Hello sleep
    37: Hello sleep
    38: Hello sleep
    39: Hello sleep
    40: Hello sleep

    real    0m2.007s
    user    0m0.003s
    sys 0m0.000s


*/

