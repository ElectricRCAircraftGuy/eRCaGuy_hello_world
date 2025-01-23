This file is part of eRCaGuy_dotfiles: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles


# See also

1. [coulomb_counter_with_cooperative_multitasking_macro/coulomb_counter_with_cooperative_multitasking_macro.ino](coulomb_counter_with_cooperative_multitasking_macro/coulomb_counter_with_cooperative_multitasking_macro.ino)


# Bare-metal, or "polling" style timing example

```cpp
uint32_t millis();

void loop()
{
    uint32_t t_now_ms = millis();
    static uint32_t t_start_ms = t_now_ms;
    uint32_t dt_ms = t_now_ms - t_start_ms;
    if (dt_ms >= DESIRED_PD)
    {
        // Option 1: for jittering around dt error of zero
        // t_start_ms += DESIRED_PD; 
        //
        // dt_ms = t_now_ms - t_start_ms;
        // if (dt_ms >= DESIRED_PD)
        // {
        //     t_start_ms = t_now_ms - DESIRED_PD;
        // }

        // OR: Option 2: for simpler math but always having a non-zero, 
        // positive error in your actual dt
        t_start_ms = t_now_ms;

        // run your periodic event
        // ...
    }
}
```
