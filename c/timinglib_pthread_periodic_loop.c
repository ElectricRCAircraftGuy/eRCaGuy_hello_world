/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Show how to use the timinglib "sleep until" functions in a pthread (POSIX thread) thread. Let's run
the loop really fast (ex: 100 Hz ~ 1000 Hz), and analyze the time errors!

STATUS: works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# 1. In C:
gcc -Wall -Wextra -Werror -O3 -std=c17 timinglib_pthread_periodic_loop.c timinglib.c -o bin/a -pthread && time sudo bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 timinglib_pthread_periodic_loop.c timinglib.c -o bin/a -pthread && time sudo bin/a
```

References:
1. https://linux.die.net/man/3/pthread_create
1. https://man7.org/linux/man-pages/man3/pthread_create.3.html
1. https://linux.die.net/man/3/pthread_join

*/


// Local includes
#include "timinglib.h"

// Linux includes
#include <pthread.h>

// C includes
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

#define NUM_ITERATIONS 200

// TODO: consider passing in the period to the `pthread_task()` function, and spawning multiple
// threads at once.

// Perform an action at the period specified below.
// - Start `pthread_task` as its own thread, using a library such as
//   `pthread` (POSIX threads).
void * pthread_task(void * argument)
{
    const char* thread_name = (const char*)argument;

    // =============================================================================================
    // SET LOOP PERIOD (FREQUENCY) HERE!
    //    10 us ( 0.01 ms) --> 100 KHz
    //   100 us ( 0.10 ms) -->  10 KHz
    //  1000 us ( 1.00 ms) -->   1 KHz
    // 10000 us (10.00 ms) --> 100 Hz
    const uint64_t PERIOD_US = 100;
    // =============================================================================================
    // Seed the last wake time with the current time.
    uint64_t last_wake_time_us = micros();

    printf("thread_name = %s\n", thread_name);
    printf("loop period = %lu us; freq = %.1f Hz\n", PERIOD_US, 1.0/US_TO_SEC((double)PERIOD_US));

    // while (true)
    uint64_t t_start_ns = nanos();
    int64_t time_error_sum_ns = 0;
    int64_t time_error_min_ns = INT64_MAX;
    int64_t time_error_max_ns = INT64_MIN;
    for (size_t i = 0; i < NUM_ITERATIONS; i++)
    {
        // Wait for the next cycle.
        sleep_until_us(&last_wake_time_us, PERIOD_US);

        // -----------------------------------------------------------------------------------------
        // Perform whatever action you want here at this fixed interval.
        // -----------------------------------------------------------------------------------------

        uint64_t t_end_ns = nanos();
        uint64_t dt_ns = t_end_ns - t_start_ns;
        t_start_ns = t_end_ns;

        int64_t time_period_error_ns = US_TO_NS((int64_t)PERIOD_US) - (int64_t)dt_ns;
        // percent error
        double time_period_error_pct = NS_TO_US((double)time_period_error_ns)/PERIOD_US*100;
        printf("%4zu: dt_ns = %9lu ns;  error = %6li **ns** (%7.3f%%)\n",
            i, dt_ns, time_period_error_ns, time_period_error_pct);

        // gather statistics on the time interval error;

        // // reject the first iteration from the stats, however, since it has extra error!
        // if (i == 0)
        // {
        //     continue;
        // }

        time_error_sum_ns += time_period_error_ns;

        if (time_period_error_ns > time_error_max_ns)
        {
            time_error_max_ns = time_period_error_ns;
        }

        if (time_period_error_ns < time_error_min_ns)
        {
            time_error_min_ns = time_period_error_ns;
        }
    }

    printf("\n");
    double time_error_avg_ns = (double)time_error_sum_ns/(NUM_ITERATIONS);
    double time_error_avg_pct = NS_TO_US((double)time_error_avg_ns)/PERIOD_US*100;
    double time_error_min_pct = NS_TO_US((double)time_error_min_ns)/PERIOD_US*100;
    double time_error_max_pct = NS_TO_US((double)time_error_max_ns)/PERIOD_US*100;
    printf("average time error per iteration = %12.3f ns (%7.3f%%)\n",
        time_error_avg_ns, time_error_avg_pct);
    printf("minimum time error per iteration = %8li     ns (%7.3f%%)\n",
        time_error_min_ns, time_error_min_pct);
    printf("maximum time error per iteration = %8li     ns (%7.3f%%)\n",
        time_error_max_ns, time_error_max_pct);

    return (void*)"Done!";
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Activating realtime scheduler.\n");
    use_realtime_scheduler();

    printf("Starting pthread at fixed interval using `sleep_until_us()`.\n\n");

    pthread_t thread;
    const char thread_name[] = "some thread name"; // this can really be ANY argument
    int retcode = pthread_create(&thread, NULL, pthread_task, (void*)thread_name);
    if (retcode != 0)
    {
        printf("Failed to create pthread. retcode = %i\n", retcode);
    }

    const char * return_message;
    retcode = pthread_join(thread, (void**)&return_message);
    if (retcode != 0)
    {
        printf("Failed to join (terminate) pthread. retcode = %i\n", retcode);
    }

    printf("\nFinal message from thread = %s\n", return_message);

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

NEW: using the realtime scheduler!--via a call to `use_realtime_scheduler()`:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 timinglib_pthread_periodic_loop.c timinglib.c -o bin/a -pthread && time sudo bin/a
    Activating realtime scheduler.
    Starting pthread at fixed interval using `sleep_until_us()`.

    thread_name = some thread name
    loop period = 100 us; freq = 10000.0 Hz
       0: dt_ns =     85717 ns;  error =  14283 **ns** ( 14.283%)
       1: dt_ns =     98792 ns;  error =   1208 **ns** (  1.208%)
       2: dt_ns =     99712 ns;  error =    288 **ns** (  0.288%)
       3: dt_ns =    100196 ns;  error =   -196 **ns** ( -0.196%)
       4: dt_ns =     99679 ns;  error =    321 **ns** (  0.321%)
       5: dt_ns =    100680 ns;  error =   -680 **ns** ( -0.680%)
       6: dt_ns =     99396 ns;  error =    604 **ns** (  0.604%)
       7: dt_ns =    100265 ns;  error =   -265 **ns** ( -0.265%)
       8: dt_ns =     99716 ns;  error =    284 **ns** (  0.284%)
       9: dt_ns =    100183 ns;  error =   -183 **ns** ( -0.183%)
      10: dt_ns =     99864 ns;  error =    136 **ns** (  0.136%)
      11: dt_ns =    100031 ns;  error =    -31 **ns** ( -0.031%)
      12: dt_ns =    100001 ns;  error =     -1 **ns** ( -0.001%)
      13: dt_ns =     99970 ns;  error =     30 **ns** (  0.030%)
      14: dt_ns =     99984 ns;  error =     16 **ns** (  0.016%)
      15: dt_ns =    100047 ns;  error =    -47 **ns** ( -0.047%)
      16: dt_ns =     99861 ns;  error =    139 **ns** (  0.139%)
      17: dt_ns =    100281 ns;  error =   -281 **ns** ( -0.281%)
      18: dt_ns =     99909 ns;  error =     91 **ns** (  0.091%)
      19: dt_ns =     99985 ns;  error =     15 **ns** (  0.015%)
      20: dt_ns =     99736 ns;  error =    264 **ns** (  0.264%)
      21: dt_ns =    100312 ns;  error =   -312 **ns** ( -0.312%)
      22: dt_ns =    100013 ns;  error =    -13 **ns** ( -0.013%)
      23: dt_ns =    100014 ns;  error =    -14 **ns** ( -0.014%)
      24: dt_ns =     99834 ns;  error =    166 **ns** (  0.166%)
      25: dt_ns =     99951 ns;  error =     49 **ns** (  0.049%)
      26: dt_ns =    100267 ns;  error =   -267 **ns** ( -0.267%)
      27: dt_ns =     99735 ns;  error =    265 **ns** (  0.265%)
      28: dt_ns =    100174 ns;  error =   -174 **ns** ( -0.174%)
      29: dt_ns =    100028 ns;  error =    -28 **ns** ( -0.028%)
      30: dt_ns =     99942 ns;  error =     58 **ns** (  0.058%)
      31: dt_ns =     99747 ns;  error =    253 **ns** (  0.253%)
      32: dt_ns =    100226 ns;  error =   -226 **ns** ( -0.226%)
      33: dt_ns =     99994 ns;  error =      6 **ns** (  0.006%)
      34: dt_ns =     99969 ns;  error =     31 **ns** (  0.031%)
      35: dt_ns =     99857 ns;  error =    143 **ns** (  0.143%)
      36: dt_ns =    100386 ns;  error =   -386 **ns** ( -0.386%)
      37: dt_ns =     99813 ns;  error =    187 **ns** (  0.187%)
      38: dt_ns =    100042 ns;  error =    -42 **ns** ( -0.042%)
      39: dt_ns =     99706 ns;  error =    294 **ns** (  0.294%)
      40: dt_ns =    100238 ns;  error =   -238 **ns** ( -0.238%)
      41: dt_ns =     99886 ns;  error =    114 **ns** (  0.114%)
      42: dt_ns =    100160 ns;  error =   -160 **ns** ( -0.160%)
      43: dt_ns =     99867 ns;  error =    133 **ns** (  0.133%)
      44: dt_ns =    100092 ns;  error =    -92 **ns** ( -0.092%)
      45: dt_ns =     99878 ns;  error =    122 **ns** (  0.122%)
      46: dt_ns =    100085 ns;  error =    -85 **ns** ( -0.085%)
      47: dt_ns =    100112 ns;  error =   -112 **ns** ( -0.112%)
      48: dt_ns =     99764 ns;  error =    236 **ns** (  0.236%)
      49: dt_ns =    100212 ns;  error =   -212 **ns** ( -0.212%)
      50: dt_ns =     99989 ns;  error =     11 **ns** (  0.011%)
      51: dt_ns =    100010 ns;  error =    -10 **ns** ( -0.010%)
      52: dt_ns =     99759 ns;  error =    241 **ns** (  0.241%)
      53: dt_ns =    100206 ns;  error =   -206 **ns** ( -0.206%)
      54: dt_ns =    100002 ns;  error =     -2 **ns** ( -0.002%)
      55: dt_ns =     99938 ns;  error =     62 **ns** (  0.062%)
      56: dt_ns =     99746 ns;  error =    254 **ns** (  0.254%)
      57: dt_ns =    100569 ns;  error =   -569 **ns** ( -0.569%)
      58: dt_ns =     99724 ns;  error =    276 **ns** (  0.276%)
      59: dt_ns =    100101 ns;  error =   -101 **ns** ( -0.101%)
      60: dt_ns =     99650 ns;  error =    350 **ns** (  0.350%)
      61: dt_ns =    100250 ns;  error =   -250 **ns** ( -0.250%)
      62: dt_ns =    100001 ns;  error =     -1 **ns** ( -0.001%)
      63: dt_ns =    100052 ns;  error =    -52 **ns** ( -0.052%)
      64: dt_ns =     99853 ns;  error =    147 **ns** (  0.147%)
      65: dt_ns =     99832 ns;  error =    168 **ns** (  0.168%)
      66: dt_ns =    100017 ns;  error =    -17 **ns** ( -0.017%)
      67: dt_ns =    100001 ns;  error =     -1 **ns** ( -0.001%)
      68: dt_ns =    100227 ns;  error =   -227 **ns** ( -0.227%)
      69: dt_ns =     99840 ns;  error =    160 **ns** (  0.160%)
      70: dt_ns =     99876 ns;  error =    124 **ns** (  0.124%)
      71: dt_ns =     99938 ns;  error =     62 **ns** (  0.062%)
      72: dt_ns =    100469 ns;  error =   -469 **ns** ( -0.469%)
      73: dt_ns =    100162 ns;  error =   -162 **ns** ( -0.162%)
      74: dt_ns =    100724 ns;  error =   -724 **ns** ( -0.724%)
      75: dt_ns =    106371 ns;  error =  -6371 **ns** ( -6.371%)
      76: dt_ns =     93393 ns;  error =   6607 **ns** (  6.607%)
      77: dt_ns =    100476 ns;  error =   -476 **ns** ( -0.476%)
      78: dt_ns =     99400 ns;  error =    600 **ns** (  0.600%)
      79: dt_ns =     99948 ns;  error =     52 **ns** (  0.052%)
      80: dt_ns =     99938 ns;  error =     62 **ns** (  0.062%)
      81: dt_ns =    100204 ns;  error =   -204 **ns** ( -0.204%)
      82: dt_ns =    100026 ns;  error =    -26 **ns** ( -0.026%)
      83: dt_ns =    100236 ns;  error =   -236 **ns** ( -0.236%)
      84: dt_ns =     99252 ns;  error =    748 **ns** (  0.748%)
      85: dt_ns =    100272 ns;  error =   -272 **ns** ( -0.272%)
      86: dt_ns =     99745 ns;  error =    255 **ns** (  0.255%)
      87: dt_ns =    101421 ns;  error =  -1421 **ns** ( -1.421%)
      88: dt_ns =     99283 ns;  error =    717 **ns** (  0.717%)
      89: dt_ns =    100878 ns;  error =   -878 **ns** ( -0.878%)
      90: dt_ns =     99288 ns;  error =    712 **ns** (  0.712%)
      91: dt_ns =     99430 ns;  error =    570 **ns** (  0.570%)
      92: dt_ns =     99673 ns;  error =    327 **ns** (  0.327%)
      93: dt_ns =    100080 ns;  error =    -80 **ns** ( -0.080%)
      94: dt_ns =     99945 ns;  error =     55 **ns** (  0.055%)
      95: dt_ns =     99950 ns;  error =     50 **ns** (  0.050%)
      96: dt_ns =     99985 ns;  error =     15 **ns** (  0.015%)
      97: dt_ns =    100418 ns;  error =   -418 **ns** ( -0.418%)
      98: dt_ns =    100050 ns;  error =    -50 **ns** ( -0.050%)
      99: dt_ns =     99361 ns;  error =    639 **ns** (  0.639%)
     100: dt_ns =     99627 ns;  error =    373 **ns** (  0.373%)
     101: dt_ns =     99641 ns;  error =    359 **ns** (  0.359%)
     102: dt_ns =    100025 ns;  error =    -25 **ns** ( -0.025%)
     103: dt_ns =    100820 ns;  error =   -820 **ns** ( -0.820%)
     104: dt_ns =    100723 ns;  error =   -723 **ns** ( -0.723%)
     105: dt_ns =     98815 ns;  error =   1185 **ns** (  1.185%)
     106: dt_ns =    100250 ns;  error =   -250 **ns** ( -0.250%)
     107: dt_ns =    100216 ns;  error =   -216 **ns** ( -0.216%)
     108: dt_ns =     99683 ns;  error =    317 **ns** (  0.317%)
     109: dt_ns =    100966 ns;  error =   -966 **ns** ( -0.966%)
     110: dt_ns =    100357 ns;  error =   -357 **ns** ( -0.357%)
     111: dt_ns =    100022 ns;  error =    -22 **ns** ( -0.022%)
     112: dt_ns =     98966 ns;  error =   1034 **ns** (  1.034%)
     113: dt_ns =     99517 ns;  error =    483 **ns** (  0.483%)
     114: dt_ns =     99973 ns;  error =     27 **ns** (  0.027%)
     115: dt_ns =     99841 ns;  error =    159 **ns** (  0.159%)
     116: dt_ns =    101627 ns;  error =  -1627 **ns** ( -1.627%)
     117: dt_ns =    100344 ns;  error =   -344 **ns** ( -0.344%)
     118: dt_ns =     99767 ns;  error =    233 **ns** (  0.233%)
     119: dt_ns =    100106 ns;  error =   -106 **ns** ( -0.106%)
     120: dt_ns =    101530 ns;  error =  -1530 **ns** ( -1.530%)
     121: dt_ns =     99844 ns;  error =    156 **ns** (  0.156%)
     122: dt_ns =     98751 ns;  error =   1249 **ns** (  1.249%)
     123: dt_ns =    100082 ns;  error =    -82 **ns** ( -0.082%)
     124: dt_ns =     99979 ns;  error =     21 **ns** (  0.021%)
     125: dt_ns =    101888 ns;  error =  -1888 **ns** ( -1.888%)
     126: dt_ns =     99798 ns;  error =    202 **ns** (  0.202%)
     127: dt_ns =     98897 ns;  error =   1103 **ns** (  1.103%)
     128: dt_ns =    100091 ns;  error =    -91 **ns** ( -0.091%)
     129: dt_ns =     99992 ns;  error =      8 **ns** (  0.008%)
     130: dt_ns =    100077 ns;  error =    -77 **ns** ( -0.077%)
     131: dt_ns =     99306 ns;  error =    694 **ns** (  0.694%)
     132: dt_ns =    100008 ns;  error =     -8 **ns** ( -0.008%)
     133: dt_ns =    100690 ns;  error =   -690 **ns** ( -0.690%)
     134: dt_ns =    100179 ns;  error =   -179 **ns** ( -0.179%)
     135: dt_ns =     97880 ns;  error =   2120 **ns** (  2.120%)
     136: dt_ns =     99795 ns;  error =    205 **ns** (  0.205%)
     137: dt_ns =    100787 ns;  error =   -787 **ns** ( -0.787%)
     138: dt_ns =    102552 ns;  error =  -2552 **ns** ( -2.552%)
     139: dt_ns =     99397 ns;  error =    603 **ns** (  0.603%)
     140: dt_ns =     99718 ns;  error =    282 **ns** (  0.282%)
     141: dt_ns =     99864 ns;  error =    136 **ns** (  0.136%)
     142: dt_ns =    101029 ns;  error =  -1029 **ns** ( -1.029%)
     143: dt_ns =    104776 ns;  error =  -4776 **ns** ( -4.776%)
     144: dt_ns =     94933 ns;  error =   5067 **ns** (  5.067%)
     145: dt_ns =     99679 ns;  error =    321 **ns** (  0.321%)
     146: dt_ns =     99559 ns;  error =    441 **ns** (  0.441%)
     147: dt_ns =    100669 ns;  error =   -669 **ns** ( -0.669%)
     148: dt_ns =    100517 ns;  error =   -517 **ns** ( -0.517%)
     149: dt_ns =     98934 ns;  error =   1066 **ns** (  1.066%)
     150: dt_ns =     98797 ns;  error =   1203 **ns** (  1.203%)
     151: dt_ns =     99370 ns;  error =    630 **ns** (  0.630%)
     152: dt_ns =     99447 ns;  error =    553 **ns** (  0.553%)
     153: dt_ns =     99903 ns;  error =     97 **ns** (  0.097%)
     154: dt_ns =    101088 ns;  error =  -1088 **ns** ( -1.088%)
     155: dt_ns =     99971 ns;  error =     29 **ns** (  0.029%)
     156: dt_ns =     99980 ns;  error =     20 **ns** (  0.020%)
     157: dt_ns =     99390 ns;  error =    610 **ns** (  0.610%)
     158: dt_ns =    102007 ns;  error =  -2007 **ns** ( -2.007%)
     159: dt_ns =     99097 ns;  error =    903 **ns** (  0.903%)
     160: dt_ns =     98546 ns;  error =   1454 **ns** (  1.454%)
     161: dt_ns =     99841 ns;  error =    159 **ns** (  0.159%)
     162: dt_ns =    100830 ns;  error =   -830 **ns** ( -0.830%)
     163: dt_ns =    100135 ns;  error =   -135 **ns** ( -0.135%)
     164: dt_ns =    101267 ns;  error =  -1267 **ns** ( -1.267%)
     165: dt_ns =    103445 ns;  error =  -3445 **ns** ( -3.445%)
     166: dt_ns =     99046 ns;  error =    954 **ns** (  0.954%)
     167: dt_ns =     99528 ns;  error =    472 **ns** (  0.472%)
     168: dt_ns =    100012 ns;  error =    -12 **ns** ( -0.012%)
     169: dt_ns =    100580 ns;  error =   -580 **ns** ( -0.580%)
     170: dt_ns =     97971 ns;  error =   2029 **ns** (  2.029%)
     171: dt_ns =     99363 ns;  error =    637 **ns** (  0.637%)
     172: dt_ns =    100817 ns;  error =   -817 **ns** ( -0.817%)
     173: dt_ns =    101567 ns;  error =  -1567 **ns** ( -1.567%)
     174: dt_ns =    100112 ns;  error =   -112 **ns** ( -0.112%)
     175: dt_ns =     99775 ns;  error =    225 **ns** (  0.225%)
     176: dt_ns =    100885 ns;  error =   -885 **ns** ( -0.885%)
     177: dt_ns =     99555 ns;  error =    445 **ns** (  0.445%)
     178: dt_ns =    101252 ns;  error =  -1252 **ns** ( -1.252%)
     179: dt_ns =     99116 ns;  error =    884 **ns** (  0.884%)
     180: dt_ns =     99471 ns;  error =    529 **ns** (  0.529%)
     181: dt_ns =     98410 ns;  error =   1590 **ns** (  1.590%)
     182: dt_ns =    100764 ns;  error =   -764 **ns** ( -0.764%)
     183: dt_ns =     99709 ns;  error =    291 **ns** (  0.291%)
     184: dt_ns =     99505 ns;  error =    495 **ns** (  0.495%)
     185: dt_ns =    101294 ns;  error =  -1294 **ns** ( -1.294%)
     186: dt_ns =     98697 ns;  error =   1303 **ns** (  1.303%)
     187: dt_ns =    101129 ns;  error =  -1129 **ns** ( -1.129%)
     188: dt_ns =     99346 ns;  error =    654 **ns** (  0.654%)
     189: dt_ns =    100789 ns;  error =   -789 **ns** ( -0.789%)
     190: dt_ns =     97991 ns;  error =   2009 **ns** (  2.009%)
     191: dt_ns =    101046 ns;  error =  -1046 **ns** ( -1.046%)
     192: dt_ns =     98505 ns;  error =   1495 **ns** (  1.495%)
     193: dt_ns =     99308 ns;  error =    692 **ns** (  0.692%)
     194: dt_ns =     99995 ns;  error =      5 **ns** (  0.005%)
     195: dt_ns =    100440 ns;  error =   -440 **ns** ( -0.440%)
     196: dt_ns =    100826 ns;  error =   -826 **ns** ( -0.826%)
     197: dt_ns =    102797 ns;  error =  -2797 **ns** ( -2.797%)
     198: dt_ns =     97970 ns;  error =   2030 **ns** (  2.030%)
     199: dt_ns =     98622 ns;  error =   1378 **ns** (  1.378%)

    average time error per iteration =       69.690 ns (  0.070%)
    minimum time error per iteration =    -6371     ns ( -6.371%)
    maximum time error per iteration =    14283     ns ( 14.283%)

    Final message from thread = Done!

    real    0m0.049s
    user    0m0.004s
    sys 0m0.015s




OLD, NON real-time scheduler:


    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 timinglib_pthread_periodic_loop.c timinglib.c -o bin/a -pthread && time bin/a
    Starting pthread at fixed interval using `sleep_until_ms()`.

    thread_name = some thread name
       0: dt_ns =   9735178 ns;  error =    264 **us**
       1: dt_ns =   9998204 ns;  error =      1 **us**
       2: dt_ns =   9992340 ns;  error =      7 **us**
       3: dt_ns =  10021152 ns;  error =    -21 **us**
       4: dt_ns =   9991807 ns;  error =      8 **us**
       5: dt_ns =   9971915 ns;  error =     28 **us**
       6: dt_ns =  10002417 ns;  error =     -2 **us**
       7: dt_ns =  10039566 ns;  error =    -39 **us**
       8: dt_ns =   9984627 ns;  error =     15 **us**
       9: dt_ns =   9960032 ns;  error =     39 **us**
      10: dt_ns =  10010844 ns;  error =    -10 **us**
      11: dt_ns =  10046415 ns;  error =    -46 **us**
      12: dt_ns =   9994367 ns;  error =      5 **us**
      13: dt_ns =   9954111 ns;  error =     45 **us**
      14: dt_ns =  10193405 ns;  error =   -193 **us**
      15: dt_ns =   9827192 ns;  error =    172 **us**
      16: dt_ns =  10054913 ns;  error =    -54 **us**
      17: dt_ns =   9989492 ns;  error =     10 **us**
      18: dt_ns =   9978018 ns;  error =     21 **us**
      19: dt_ns =   9975802 ns;  error =     24 **us**
      20: dt_ns =   9985199 ns;  error =     14 **us**
      21: dt_ns =  10026753 ns;  error =    -26 **us**
      22: dt_ns =  10011507 ns;  error =    -11 **us**
      23: dt_ns =   9941954 ns;  error =     58 **us**
      24: dt_ns =  10054677 ns;  error =    -54 **us**
      25: dt_ns =   9987750 ns;  error =     12 **us**
      26: dt_ns =   9981280 ns;  error =     18 **us**
      27: dt_ns =   9959769 ns;  error =     40 **us**
      28: dt_ns =  10085370 ns;  error =    -85 **us**
      29: dt_ns =   9941678 ns;  error =     58 **us**
      30: dt_ns =  10018696 ns;  error =    -18 **us**
      31: dt_ns =  10050913 ns;  error =    -50 **us**
      32: dt_ns =   9963577 ns;  error =     36 **us**
      33: dt_ns =   9947881 ns;  error =     52 **us**
      34: dt_ns =  10026641 ns;  error =    -26 **us**
      35: dt_ns =  10015025 ns;  error =    -15 **us**
      36: dt_ns =   9979387 ns;  error =     20 **us**
      37: dt_ns =  10003888 ns;  error =     -3 **us**
      38: dt_ns =  10062648 ns;  error =    -62 **us**
      39: dt_ns =   9937151 ns;  error =     62 **us**
      40: dt_ns =  10003258 ns;  error =     -3 **us**
      41: dt_ns =   9998200 ns;  error =      1 **us**
      42: dt_ns =  10028013 ns;  error =    -28 **us**
      43: dt_ns =  10015356 ns;  error =    -15 **us**
      44: dt_ns =   9951117 ns;  error =     48 **us**
      45: dt_ns =  10004421 ns;  error =     -4 **us**
      46: dt_ns =  10004699 ns;  error =     -4 **us**
      47: dt_ns =  10048501 ns;  error =    -48 **us**
      48: dt_ns =   9996144 ns;  error =      3 **us**
      49: dt_ns =   9971288 ns;  error =     28 **us**
      50: dt_ns =  10046959 ns;  error =    -46 **us**
      51: dt_ns =   9966386 ns;  error =     33 **us**
      52: dt_ns =  10021927 ns;  error =    -21 **us**
      53: dt_ns =   9990311 ns;  error =      9 **us**
      54: dt_ns =  10019170 ns;  error =    -19 **us**
      55: dt_ns =   9967757 ns;  error =     32 **us**
      56: dt_ns =  10019455 ns;  error =    -19 **us**
      57: dt_ns =   9995387 ns;  error =      4 **us**
      58: dt_ns =  10006630 ns;  error =     -6 **us**
      59: dt_ns =   9959851 ns;  error =     40 **us**
      60: dt_ns =  10018525 ns;  error =    -18 **us**
      61: dt_ns =  10014423 ns;  error =    -14 **us**
      62: dt_ns =   9960740 ns;  error =     39 **us**
      63: dt_ns =  10069151 ns;  error =    -69 **us**
      64: dt_ns =   9981962 ns;  error =     18 **us**
      65: dt_ns =  10009861 ns;  error =     -9 **us**
      66: dt_ns =   9981098 ns;  error =     18 **us**
      67: dt_ns =   9973102 ns;  error =     26 **us**
      68: dt_ns =  10026926 ns;  error =    -26 **us**
      69: dt_ns =   9967373 ns;  error =     32 **us**
      70: dt_ns =  10029630 ns;  error =    -29 **us**
      71: dt_ns =  10014935 ns;  error =    -14 **us**
      72: dt_ns =  10001636 ns;  error =     -1 **us**
      73: dt_ns =  10013978 ns;  error =    -13 **us**
      74: dt_ns =   9935977 ns;  error =     64 **us**
      75: dt_ns =  10049426 ns;  error =    -49 **us**
      76: dt_ns =   9973107 ns;  error =     26 **us**
      77: dt_ns =   9996319 ns;  error =      3 **us**
      78: dt_ns =  10002237 ns;  error =     -2 **us**
      79: dt_ns =   9988132 ns;  error =     11 **us**
      80: dt_ns =   9980812 ns;  error =     19 **us**
      81: dt_ns =   9986003 ns;  error =     13 **us**
      82: dt_ns =  10069309 ns;  error =    -69 **us**
      83: dt_ns =   9967841 ns;  error =     32 **us**
      84: dt_ns =   9994342 ns;  error =      5 **us**
      85: dt_ns =  10019304 ns;  error =    -19 **us**
      86: dt_ns =   9996140 ns;  error =      3 **us**
      87: dt_ns =   9992928 ns;  error =      7 **us**
      88: dt_ns =  10068364 ns;  error =    -68 **us**
      89: dt_ns =   9896354 ns;  error =    103 **us**
      90: dt_ns =  10086264 ns;  error =    -86 **us**
      91: dt_ns =   9925043 ns;  error =     74 **us**
      92: dt_ns =  10031766 ns;  error =    -31 **us**
      93: dt_ns =  10006041 ns;  error =     -6 **us**
      94: dt_ns =  10005128 ns;  error =     -5 **us**
      95: dt_ns =   9965488 ns;  error =     34 **us**
      96: dt_ns =  10028760 ns;  error =    -28 **us**
      97: dt_ns =   9964485 ns;  error =     35 **us**
      98: dt_ns =  10040938 ns;  error =    -40 **us**
      99: dt_ns =  10015181 ns;  error =    -15 **us**

    average time error per iteration =    2.300 us
    minimum time error per iteration = -193 us
    maximum time error per iteration =  264 us

    Final message from thread = Done!

    real    0m1.001s
    user    0m0.000s
    sys 0m0.007s


OR, in C++:

(same as in C)


*/
