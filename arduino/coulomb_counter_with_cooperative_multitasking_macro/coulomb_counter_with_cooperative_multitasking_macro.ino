/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Written:                                    28 May 2020
Published to my eRCaGuy_hello_world repo:    1 May 2022
Based on timestamp-based, cooperative multi-tasking techniques I developed primarily from 2012 to
2018, and then refined by 2020.

Demonstrate advanced, bare-metal, timestamp-based cooperative multi-tasking techniques using my
`CREATE_TASK_TIMER()` macro to implement a fully-functional energy measurement device, or "coulomb
counter".

STATUS: done and works! You just need to implement `get_current()`, `get_volage()`, and
`do_time_correction()`, is all, for your particular hardware.

References:
1. *****+++[my full answer with this code!] https://arduino.stackexchange.com/a/75937/7727
1. *****++[How to do high-resolution, timestamp-based, non-blocking, single-threaded cooperative
   multi-tasking] https://stackoverflow.com/a/50032992/4561887
1.

*/



/// Coulomb counter example
/// By Gabriel Staples
/// See: https://arduino.stackexchange.com/questions/75932/calculating-amp-hrs-of-a-solar-panel/75937#75937

// TODO: improve this `CREATE_TASK_TIMER()` macro to be easier to use! See: TODO.md: 20230406.

/// @brief      A function-like macro to get a certain set of events to run at a desired, fixed
///             interval period or frequency.
/// @details    This is a timestamp-based time polling technique frequently used in bare-metal
///             programming as a basic means of achieving cooperative multi-tasking. Note
///             that getting the timing details right is difficult, hence one reason this macro
///             is so useful. The other reason is that this maro significantly reduces the number of
///             lines of code you need to write to introduce a new timestamp-based cooperative
///             task. The technique used herein achieves a perfect desired period (or freq)
///             on average, as it centers the jitter inherent in any polling technique around
///             the desired time delta set-point, rather than always lagging as many other
///             approaches do.
///
///             USAGE EX:
///             ```
///             // Create a task timer to run at 500 Hz (every 2000 us, or 2 ms; 1/0.002 sec = 500 Hz)
///             const uint32_t PERIOD_US = 2000; // 2000 us pd --> 500 Hz freq
///             bool time_to_run;
///             uint32_t actual_period_us;
///             CREATE_TASK_TIMER(PERIOD_US, time_to_run, actual_period_us);
///             if (time_to_run)
///             {
///                 run_task_2();
///
///                 // OR, if `run_task_2()` needs the actual period that just occurred, for
///                 // whatever reason, you may pass it in to your `run_task_2()` function:
///                 run_task_2(actual_period_us);
///
///                 // OR, just do all your code right here instead of in `run_task_2()`
///             }
///             ```
///
///             Source: Gabriel Staples
///             https://stackoverflow.com/questions/50028821/best-way-to-read-from-a-sensors-that-doesnt-have-interrupt-pin-and-require-some/50032992#50032992
/// @param[in]  period_desired_us  (uint32_t) The desired delta time period, in microseconds;
///                             note: pd = 1/freq; the type must be `uint32_t`.
/// @param[out] time_to_run     (bool) A `bool` whose scope will enter *into* the brace-based scope block
///                             below; used as an *output* flag to the caller: this variable will
///                             be set to true if it is time to run your code, according to the
///                             timestamps, and will be set to false otherwise.
/// @param[out] actual_period_us  (uint32_t) The actual period, in us, since the last time it was
///                             time to run--ie: since the last time `time_to_run` was set to true.
/// @return     NA--this is not a true function
#define CREATE_TASK_TIMER(period_desired_us, time_to_run, actual_period_us)                                            \
{ /* Use scoping braces to allow multiple calls of this macro all in one outer scope while */                          \
  /* allowing each variable created below to be treated as unique to its own scope */                                  \
    time_to_run = false;                                                                                               \
                                                                                                                       \
    /* set the desired run pd / freq */                                                                                \
    const uint32_t PERIOD_DESIRED_US = period_desired_us;                                                              \
    static uint32_t t_start_us = micros();                                                                             \
    uint32_t t_now_us = micros();                                                                                      \
    uint32_t period_us = t_now_us - t_start_us;                                                                        \
    actual_period_us = period_us;                                                                                      \
                                                                                                                       \
    /* See if it's time to run this Task */                                                                            \
    if (period_us >= PERIOD_DESIRED_US)                                                                                \
    {                                                                                                                  \
        /* 1. Add PERIOD_DESIRED_US to t_start_us rather than setting t_start_us to t_now_us (which many */            \
        /* people do) in order to ***avoid introducing artificial jitter into the timing!*** */                        \
        t_start_us += PERIOD_DESIRED_US;                                                                               \
        /* 2. Handle edge case where it's already time to run again because just completing one of the main */         \
        /* "scheduler" loops in the main() function takes longer than PERIOD_DESIRED_US; in other words, here */       \
        /* we are seeing that t_start_us is lagging too far behind (more than one PERIOD_DESIRED_US time width */      \
        /* from t_now_us), so we are "fast-forwarding" t_start_us up to the point where it is exactly */               \
        /* 1 PERIOD_DESIRED_US time width back now, thereby causing this task to instantly run again the */            \
        /* next time it is called (trying as hard as we can to run at the specified frequency) while */                \
        /* at the same time protecting t_start_us from lagging farther and farther behind, as that would */            \
        /* eventually cause buggy and incorrect behavior when the (unsigned) timestamps start to roll over */          \
        /* back to zero. */                                                                                            \
        period_us = t_now_us - t_start_us; /* calculate new time delta with newly-updated t_start_us */                \
        if (period_us >= PERIOD_DESIRED_US)                                                                            \
        {                                                                                                              \
            t_start_us = t_now_us - PERIOD_DESIRED_US;                                                                 \
        }                                                                                                              \
                                                                                                                       \
        time_to_run = true;                                                                                            \
    }                                                                                                                  \
}

// Convert microseconds to seconds
#define US_TO_SEC(us) ((us)/1000000UL)
// Convert Joules to KWh (Kilowatt*hours)
#define JOULES_TO_KWHRS(joules) ((joules)/3600/1000)

/// @brief      Obtain a corrected time measurement from a raw time measurement.
/// @details    Assuming you have done experiments to determine your microcontroller (mcu)
///             clock's error, you can correct for it with this function. Pass in a time
///             measurement the mcu has timed directly, and get back a corrected value.
/// @param[in]  raw_sec     A raw time measurement, in seconds
/// @return     A corrected time measurement, in seconds
float do_time_correction(float raw_sec)
{
    // You determine the correct calibration constant. Perhaps it is 0.9813, or perhaps it is
    // 1.19.... You will need to determine this for each individual mcu.
    constexpr float TIME_CORRECTION_CONST = 1.0; // default: 1.0
    float corrected_sec = raw_sec*TIME_CORRECTION_CONST;
    return corrected_sec;
}

/// @brief      Obtain a new instantaneous (at this moment) current reading, in Amps
/// @param      None
/// @return     Current, in Amps
float get_current()
{
    // you implement this
}

/// @brief      Obtain a new instantaneous (at this moment) voltage reading, in Volts
/// @param      None
/// @return     Voltage, in Volts
float get_voltage()
{
    // you implement this
}

/// @brief      Run the coulomb counter task to sum the total energy received from the solar panels
/// @param[out] total_energy_joules_p  (optional) A pointer to a float to receive back the total
///                         energy value acquired, in Joules (Watts*sec). Pass in `nullptr` to not
///                         receive back this value. Note that the previously-cached value is
///                         passed out in the event it's not time to calculate a new value.
///                         The return value of this function will indicate whether a new value
///                         or cached value is passed out here.
/// @param[in]  reset_sum   (optional) pass in true to reset the internally-stored "total energy
///                         acquired" value during this call (prior to performing the latest
///                         power_watts_avg calculation, if it is time for that).
/// @return     true if a new total_energy_joules value was just calculated and passed back via the
///             pointer above, or false if an old, cached value was passed out instead since it
///             wasn't time to obtain and calculate a new value.
bool run_coulomb_counter(float* total_energy_joules_p = nullptr, bool reset_sum = false)
{
    // Set this task to run at 100 Hz
    constexpr uint32_t PERIOD_DESIRED_US = 10000; // 10000us = 10ms, or 100Hz run freq

    static float total_energy_joules = 0;

    if (reset_sum)
    {
        total_energy_joules = 0;
    }

    bool time_to_run = false;
    uint32_t actual_period_us;
    CREATE_TASK_TIMER(PERIOD_DESIRED_US, time_to_run, actual_period_us);
    if (time_to_run)
    {
        // Time to obtain new samples and perform some numerical integration to obtain the total
        // energy received.

        // the previous power calculation, in watts; required for trapezoidal integration
        static float power_watts_old = 0;

        // take new samples, & calculate power from those samples
        float current_amps = get_current();
        float voltage = get_voltage();
        float power_watts = current_amps*voltage;

        float actual_period_sec = US_TO_SEC((float)actual_period_us);
        actual_period_sec = do_time_correction(actual_period_sec);

        // Perform trapezoidal integration to obtain the "area under the curve", which is equal to
        // the energy in joules. Imagine a plot where the y-axis is power and the x-axis is time. If
        // you split the x-axis up into segments of width PERIOD_DESIRED_US, then the trapezoidal
        // area under the curve, within each of those time segments, is equal to time_delta x
        // (power_old + power)/2. This is the energy (Joules) obtained during that time period.
        float power_watts_avg = (power_watts + power_watts_old)/2;
        power_watts_old = power_watts; // prepare for next iteration
        float energy_joules = actual_period_sec*power_watts_avg;

        total_energy_joules += energy_joules;
    }

    if (total_energy_joules_p != nullptr)
    {
        // output this value back to the user
        *total_energy_joules_p = total_energy_joules;
    }

    return time_to_run;
}

void setup()
{
    // do whatever you need to here
    Serial.begin(115200);
}

void loop()
{
    // Energy, in Joules, or Watt*seconds. To convert to Watt*hours, simply divide by 3600 [sec/hr]
    float total_energy_joules;
    bool new_measurements_made = run_coulomb_counter(&total_energy_joules);

    // Let's do an event-based print where we print the latest total_energy_joules value at a rate
    // of 2 Hz, which is typical for digital displays showing information expected to be read by
    // us slow humans. Since the run_coulomb_counter() task is running at 100 Hz, that means we
    // need to print the latest value every 50 runs.
    if (new_measurements_made)
    {
        static uint16_t run_count = 0;
        run_count++;
        if (run_count % 50 == 0)
        {
            float total_energy_kwh = JOULES_TO_KWHRS(total_energy_joules);
            Serial.print("total energy received (J) = ");
            Serial.print(total_energy_joules);
            Serial.print("; (kWh) = ");
            Serial.println(total_energy_kwh);
        }
    }
}



/*
Compilation Output:


Arduino IDE: 1.8.13
Board: Arduino Nano with ATmega328p mcu:

    Sketch uses 3750 bytes (12%) of program storage space. Maximum is 30720 bytes.
    Global variables use 262 bytes (12%) of dynamic memory, leaving 1786 bytes for local variables. Maximum is 2048 bytes.


*/
