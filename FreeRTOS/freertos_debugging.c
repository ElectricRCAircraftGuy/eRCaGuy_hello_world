// This file is part of eRCaGuy_hello_world: 
// https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

// Local includes
#include "freertos_debugging.h"

// 3rd-party includes
// For the `_nop()` macro. 
// See: 
// 1. <https://github.com/ElectricRCAircraftGuy/eRCaGuy_Engineering/blob/main/Datasheets/Microchip/MPLAB%20XC32%20C%20Compiler%20for%20PIC32M%20MCU%20UG%2050002799B%20%5Bcompiler%20User's%20Guide%20PIC32M%5D%20%5Bqpdf%20--decrypt%5D_GS_edit.pdf> 
//    pg. 218: Table 21-5. "Predefined Macros in XC.H"
#include <xc.h>

// C includes
// NA


// This custom function gets called whenever a FreeRTOS `configASSERT()` assertion fails. 
// See: https://www.freertos.org/a00110.html#configASSERT
void vAssertCalled(volatile const char* file, volatile int line, volatile const char* func)
{
	(void)file;
	(void)line;
	(void)func;

	taskDISABLE_INTERRUPTS();

	volatile bool exit_loop = false;
	while (exit_loop == false)
	{
		// If you get stuck here, it means a FreeRTOS `configASSERT()` failed. Inspect the values of
		// `file`, `line`, and `func` in a debugger to see where the assertion failed. 
		// 
		// Be sure to use `-O0` optimization level zero when debugging, for best results. 
		// See my answer: https://stackoverflow.com/a/63386263/4561887
		// 
		// You can also optionally set `exit_loop` to true with the debugger and then step out
		// to see the code location just after the failure site, as another technique to find 
		// where the assertion occurred. 
		_nop();
	}
}
