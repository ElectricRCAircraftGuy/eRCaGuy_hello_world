
// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

/*

double_resolution_test_3.cpp

- Find out when float += 1 ns (in decimal form, assuming the whole units are seconds) no longer
equals uint64_t += 1 ns, and so on, printing each time another ns of resolution is lost!
- Do the same for += 1.0 sec!

GS
30 Oct. 2020

References:
1. Optimization levels: https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
2. https://stackoverflow.com/questions/213907/stdendl-vs-n

Build and run command:
Note: use optimization level `-O3` for normal use, and `-O0` for debugging with gdb.

    Normal:

        mkdir -p bin && g++ -Wall -Wextra -Werror -ggdb -O3 -std=c++17 -o ./bin/tmp \
        double_resolution_test_3.cpp && time ./bin/tmp

    Debugging:

        mkdir -p bin && g++ -Wall -Wextra -Werror -ggdb -O0 -std=c++17 -o ./bin/tmp \
        double_resolution_test_3.cpp && time ./bin/tmp

*/

#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    printf("Hello World\n\n");

    constexpr double NS_PER_SEC = 1e9;
    constexpr double SEC_PER_NS = 1.0/NS_PER_SEC;

    printf("NS_PER_SEC = %f\n"
           "SEC_PER_NS = %3.12f\n",
           NS_PER_SEC,
           SEC_PER_NS);


    // Open file and create CSV file header
    std::string FILENAME = "double_resolution_test_3.csv";
    std::ofstream file;
    file.open(FILENAME, std::fstream::out);
    if (!file.good())
    {
        printf("FAILED TO OPEN FILE; state = %i\n", file.rdstate());
        return file.rdstate();
    }
    // file << "loop_cnt, u64_time_ns, accumulated_error_ns" << std::endl;
    file << "u64_time_ns (also acts as a loop counter), accumulated_error_ns" << std::endl;

    double double_time_sec = 0.0;
    // NB: since `u64_time_ns` will be incremented by 1 ns each loop iteration, it is also **exactly
    // equivalent** to an integer loop counter!
    uint64_t u64_time_ns = 0;
    while (true)
    {
        // static uint64_t loop_cnt = 0;

        // Display progress
        constexpr uint64_t NUM_INCREMENTS = 1e9;
        if (u64_time_ns % (UINT64_MAX/NUM_INCREMENTS) == 0)
        {
            static uint64_t progress_counter = 0;
            progress_counter++;

            printf("%3.9f%% complete (%lu/%lu)\n",
                  (double)progress_counter/NUM_INCREMENTS*100, progress_counter, NUM_INCREMENTS);
            file << std::flush; // flush file to ensure data thus far is written
        }

        // calculate and check accumulated floating point error
        double accumulated_error_ns = double_time_sec*NS_PER_SEC - u64_time_ns;
        static double accumulated_error_ns_old = 0;
        double accumulated_error_ns_change = accumulated_error_ns - accumulated_error_ns_old;
        static int64_t error_bound_ns = 0;
        double accumulated_error_ns_change_magnitude = std::abs(accumulated_error_ns_change);
        bool print_now = false;
        if (accumulated_error_ns_change_magnitude >= error_bound_ns + 1)
        {
            print_now = true;
            error_bound_ns += 1;

            if (error_bound_ns == INT64_MAX)
            {
                printf("OUT OF BOUNDS: error_bound_ns == INT64_MAX\n");
                break;
            }
        }
        else if (accumulated_error_ns_change_magnitude <= error_bound_ns - 1)
        {
            print_now = true;
            error_bound_ns -= 1;

            if (error_bound_ns == INT64_MIN)
            {
                printf("OUT OF BOUNDS: error_bound_ns == INT64_MIN\n");
                break;
            }
        }

        if (print_now)
        {
            file << u64_time_ns << ", " << accumulated_error_ns << "\n";
        }

        // loop_cnt++;

        // Add 1 ns to each
        double_time_sec += SEC_PER_NS;
        u64_time_ns += 1;
    }

    file.close();

    return 0;
}


