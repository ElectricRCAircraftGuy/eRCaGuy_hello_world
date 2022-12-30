/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
13 Mar. 2022

My goal is to answer this question: How to play sound in C from scratch
(Linux): https://stackoverflow.com/q/71445060/4561887. I think I can do this by writing an
Arduino-like `tonAC()`-type function and passing the output to the `aplay` Linux system call.

STATUS: wip
Note 30 Dec. 2022: I made some misc. changes to this file but don't remember why. So, take a look
at this file's history next time I look at it so I can see what changes I last made:
```bash
# See: https://stackoverflow.com/a/5493663/4561887
git log --follow -p -- c/alsa_aplay__play_tone_sound_WIP.c
```

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 alsa_aplay__play_tone_sound.c -o bin/a -lm && time bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 alsa_aplay__play_tone_sound.c -o bin/a && time bin/a
```

References:
1. [Q I'd like to answer] How to play sound in C from scratch (Linux):
   https://stackoverflow.com/q/71445060/4561887
1. ALSA (Advanced Linux Sound Architecture):
   https://en.wikipedia.org/wiki/Advanced_Linux_Sound_Architecture
1. See `man aplay`
1. My comment here:
   https://unix.stackexchange.com/questions/103746/why-wont-linux-let-me-play-with-dev-dsp/147147#comment1312330_147147
1. Arduino `toneAC()` library
    1. https://www.arduino.cc/reference/en/libraries/toneac/
    1. https://github.com/teckel12/arduino-toneac
1. https://en.cppreference.com/w/c/string/byte/strncat
1. *****More on pipes to pipes in C: see my comment here and the gist link in my comment:
   https://stackoverflow.com/questions/12032323/piping-the-output-of-one-command-as-input-to-another-command#comment126352138_12032323
    1. https://gist.github.com/mplewis/5279108

MINIMUM AMOUNT OF RAW DATA THAT PLAYS!:
```bash
# Unsigned 8-bit:
echo -n "0x00 0xff 0x00 0xff 0x00 0xff" | aplay
# OR
printf "%s" "0x00 0xff 0x00 0xff 0x00 0xff" | aplay

printf "\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff" | aplay

# Signed 16-bit Big-endian:
echo -n "0x0000 0xffff 0x0000 0xffff 0x0000 0xffff" | aplay -f S16_BE

TODO:
1. [ ] Write the data to a file instead of just to RAM. Play it from a file OR from RAM, but if
   from RAM, you'll have to use binary 1 in place of all binary 0s, because bash can't handle
   binary zeros. Read up on pipes too. See the "more on pipes to pipes in C" reference above.
1. [ ]

```

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
#define PLAY_LENGTH_SEC 1//60

/// From utilities.h.
/// Perform linear interpolation on x to scale it from an input range between in_min and in_max
/// to an output range between out_min and out_max. This is similar to Arduino's `map`
/// function found in Arduino's WMath.cpp.
#define SCALE(x, in_min, in_max, out_min, out_max)  \
    (((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min))
///////// ^^ for volume control!

/// Struct to contain all data for a single audio waveform to play.
typedef struct waveform_s
{
    /// One period of the waveform, up to 1 second max length of data. For frequencies > 1 Hz,
    /// only a portion of this array will be used. For a frequency as low as 1 Hz, however, the
    /// whole array will be used.
    uint8_t single_period[SAMPLES_PER_SEC];

    /// Number of samples required to make 1 period of the waveform which is stored in the array
    /// above.
    uint32_t period_num_samples;

    /// Enough audio data to play `PLAY_LENGTH_SEC` seconds.
    uint8_t full_waveform[SAMPLES_PER_SEC*PLAY_LENGTH_SEC];

    /// Bash command string to play the `full_waveform` above.
    /// 1 sample (1 byte) becomes a string like "\xab", which is 4 chars. Add some extra chars as
    /// well to allow for the rest of the command string.
    char cmd[SAMPLES_PER_SEC*PLAY_LENGTH_SEC*4 + 100];
} waveform_t;

/// \brief          Generate a single period of a sine wave at the desired frequency and store it
///                 into the `waveform_t`'s `single_period` array.
/// \param[in]      waveform        The struct to store the data into.
/// \param[in]      freq_hz         The frequency of the waveform to store. Valid values are 1 to
///                                 SAMPLES_PER_SEC/2 Hz.
/// \return         None
void make_period_sinewave(waveform_t *waveform, uint16_t freq_hz)
{
    if (waveform == NULL)
    {
        printf("ERROR: NULL ptr.\n");
        return;
    }

    if (freq_hz < 1)
    {
        printf("WARNING: freq_hz of %u is too low. Setting to 1.\n", freq_hz);
        freq_hz = 1;
        // do NOT return
    }
    else if (freq_hz > SAMPLES_PER_SEC/2)
    {
        printf("WARNING: freq_hz of %u is too high. The maximum frequency possible, per Nyquist, "
               "at a sample rate of %u samples/sec, is %u. Truncating specified frequency to "
               "%u Hz.\n", freq_hz, SAMPLES_PER_SEC, SAMPLES_PER_SEC/2, SAMPLES_PER_SEC/2);
        freq_hz = SAMPLES_PER_SEC/2;
        // do NOT return
    }

    waveform->period_num_samples = SAMPLES_PER_SEC/freq_hz;
    for (size_t i = 0; i < waveform->period_num_samples; i++)
    {
        double val = sin((double)2*PI*i/waveform->period_num_samples);
        waveform->single_period[i] = SCALE(val, -1, 1, 0, 255);
        // debugging
        // printf("%1.3f (%u; 0x%02X)  ", val, waveform->single_period[i], waveform->single_period[i]);
    }
    // printf("\n\n"); // debugging
}

// TODO: make other wave shapes:

// void make_period_squarewave(waveform_t *waveform, uint16_t freq_hz)
// {
// }

// void make_period_sawtoothwave(waveform_t *waveform, uint16_t freq_hz)
// {
// }

// void make_period_trianglewave(waveform_t *waveform, uint16_t freq_hz)
// {
// }

/// Copy the single period waveform repeatedly into the full waveform array until it is full.
void make_full_waveform(waveform_t *waveform)
{
    size_t i_single_period = 0;
    for (size_t i = 0; i < ARRAY_LEN(waveform->full_waveform); i++)
    {
        waveform->full_waveform[i] = waveform->single_period[i_single_period];
        i_single_period++;
        if (i_single_period >= waveform->period_num_samples)
        {
            i_single_period = 0;
        }
    }
}

/// Convert the contents of the full waveform array into a bash command string and load it into the
/// cmd string in the same struct.
void make_cmd(waveform_t *waveform)
{
    size_t i_cmd = 0;
    const size_t I_CMD_MAX = ARRAY_LEN(waveform->cmd) - 1;

    // 1. write the cmd prefix
    const char CMD_PREFIX[] = "bash -c 'time aplay -f U8 -r 8000 <<< \"$(printf \"";
    snprintf(&(waveform->cmd[i_cmd]), I_CMD_MAX - i_cmd, "%s", CMD_PREFIX);
    i_cmd += sizeof(CMD_PREFIX) - 1; // -1 so we will overwrite the null terminator next time

    // 2. write the cmd body (all of the binary audio data)
    for (size_t i = 0; i < ARRAY_LEN(waveform->full_waveform); i++)
    {
        const char FORMAT_STR[] = "\\x%02X";
        snprintf(&(waveform->cmd[i_cmd]), I_CMD_MAX - i_cmd,
            FORMAT_STR, waveform->full_waveform[i]); //////// write 1 instead of 0, since bash can't handle binary zeros!
        i_cmd += 4;
    }

    // 3. write the cmd suffix
    const char CMD_SUFFIX[] = "\")\"'";
    snprintf(&(waveform->cmd[i_cmd]), I_CMD_MAX - i_cmd, "%s", CMD_SUFFIX);
    i_cmd += sizeof(CMD_SUFFIX) - 1; // -1 so we will overwrite the null terminator next time

    printf("cmd = %s\n", waveform->cmd); // debugging
}

void play_sound(const waveform_t *waveform)
{
    int retval = system(waveform->cmd);
    if (retval != 0)
    {
        printf("INFO: retval from `system()` call = %i.\n", retval);
    }
}


// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    static waveform_t waveform;
    make_period_sinewave(&waveform, 200);
    make_full_waveform(&waveform);
    make_cmd(&waveform);
    // write_file(&waveform, "file.wav");
    play_sound(&waveform);

    // // for (size_t i = 0; i < ARRAY_LEN(audio_samples); i++)
    // size_t i = 0;
    // while (i < ARRAY_LEN(cmd) - 50)
    // {
    //     const char str[] = "0x00 0xff ";
    //     strcpy(&cmd[i], str);
    //     i += sizeof(str) - 1;
    // }
    // strcpy(&cmd[i], " | aplay")
    // printf("cmd: %s\n", cmd);

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
