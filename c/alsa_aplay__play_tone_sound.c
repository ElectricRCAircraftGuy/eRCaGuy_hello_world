/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
13 Mar. 2022

My goal is to answer this question: How to play sound in C from scratch
(Linux): https://stackoverflow.com/q/71445060/4561887. I think I can do this by writing an
Arduino-like `tonAC()`-type function and passing the output to the `aplay` Linux system call.

STATUS: wip

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 alsa_aplay__play_tone_sound.c -o bin/a -lm && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 alsa_aplay__play_tone_sound.c -o bin/a && bin/a
```

References:
1. How to play sound in C from scratch (Linux): https://stackoverflow.com/q/71445060/4561887
1. ALSA (Advanced Linux Sound Architecture):
   https://en.wikipedia.org/wiki/Advanced_Linux_Sound_Architecture
1. See `man aplay`
1. My comment here:
   https://unix.stackexchange.com/questions/103746/why-wont-linux-let-me-play-with-dev-dsp/147147#comment1312330_147147
1. Arduino `toneAC()` library
    1. https://www.arduino.cc/reference/en/libraries/toneac/
    1. https://github.com/teckel12/arduino-toneac

MINIMUM AMOUNT OF RAW DATA THAT PLAYS!:

    echo -n "0x00 0xff 0x00 0xff 0x00 0xff" | aplay
    # OR
    printf "%s" "0x00 0xff 0x00 0xff 0x00 0xff" | aplay

*/

#include <math.h>
#include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
#include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`
#include <stdlib.h>  // `system()`
#include <string.h>

/// Get the number of elements in any C array
/// - Usage example: [my own answer]:
///   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

// See: https://docs.microsoft.com/en-us/cpp/c-runtime-library/math-constants?view=msvc-170
#define PI 3.14159265358979323846

#define SAMPLES_PER_SEC 8000

/// From utilities.h.
/// Perform linear interpolation on x to scale it from an input range between in_min and in_max
/// to an output range between out_min and out_max. This is similar to Arduino's `map`
/// function found in Arduino's WMath.cpp.
#define SCALE(x, in_min, in_max, out_min, out_max)  \
    (((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min))
///////// ^^ for volume control!

/////// doxygen
/// Make a **single period***
// void make_period_sinewave(uint16_t* audio_samples, size_t audio_samples_len, uint16_t freq_hz)
// {
//     if (freq > SAMPLES_PER_SEC/2)
//     {
//         /////////
//         // printf("WARNING: freq (max frequency limitPer Nyquist, the highest frequency that can be generated ")
//     }
// }

void make_period_squarewave(uint16_t* audio_samples, size_t audio_samples_len, uint16_t freq_hz)
{

}

void make_period_sawtoothwave(uint16_t* audio_samples, size_t audio_samples_len, uint16_t freq_hz)
{

}

void make_period_trianglewave(uint16_t* audio_samples, size_t audio_samples_len, uint16_t freq_hz)
{

}


//////// doxygen
void make_cmd(uint16_t* audio_samples, size_t audio_samples_len, char* cmd, size_t cmd_len)
{

}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    // uint16_t audio_samples[SAMPLES_PER_SEC];
    uint8_t audio_samples[SAMPLES_PER_SEC];
    // 1 sample (2 bytes) becomes a string like "0xabcd ", which is 7 chars, so just make it 8 to
    // be safe
    char cmd[SAMPLES_PER_SEC*8];


    // for (size_t i = 0; i < ARRAY_LEN(audio_samples); i++)
    size_t i = 0;
    while (i < ARRAY_LEN(cmd) - 50)
    {
        const char str[] = "0x00 0xff ";
        strcpy(&cmd[i], str);
        i += sizeof(str) - 1;
    }
    strcpy(&cmd[i], " | aplay")
    printf("cmd: %s\n", cmd);

    // for (size_t i = 0; i < ARRAY_LEN(cmd); i++)
    // {
    //     printf("%u\n", cmd[i]);
    // }

    // make_tone(audio_samples, ARRAY_LEN(audio_samples));
    // make_cmd(audio_samples, ARRAY_LEN(audio_samples), cmd, ARRAY_LEN(cmd));
    // system(cmd);



    // printf("Hello World.\n\n");
    // double num = sin(PI/2); // 1
    // printf("num = %f\n", num);
    // num = asin(1); // PI/2 = ~1.57
    // printf("num = %f\n", num);


    // for (size_t t = 0; t < 8000; t++)
    // {
    //     double freq_hz = 1000;
    //     double voltage = asin(PI*freq_hz*t);

    //     printf("%f\n", voltage);
    //     // printf("0x%0X\n", (uint8_t)(voltage*255));

    //     // uint8_t buf[10] =
    //     // snprintf()

    // }

    return 0;
}



/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 alsa_aplay__play_tone_sound.c -o bin/a && bin/a
    Hello World.


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 alsa_aplay__play_tone_sound.c -o bin/a && bin/a
    Hello World.


*/
