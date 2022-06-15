/*
This file is part of eRCaGuy_hello_world:
https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
June 2022

In Arduino/AVR microcontroller programming, a PROGMEM utility exists to store **constant** data into
Flash memory ONLY, instead of into Flash memory AND into RAM. Normally, withOUT the PROGMEM
utility, non-zero-initialized variables, including constants, are initialized via a startup routine
which copies them to RAM from Flash upon startup, thereby unnecessarily taking up RAM space when
the variable is constant.

(FYI: unlike AVR/Arduino, STM32 mcus, on the other hand, automatically store all `const` or
`constexpr` data ONLY into Flash withOUT any special type of PROGMEM utility like AVR has.)

So, this program is a quick Arduino/AVR mcu program to practice storing a 1D PROGMEM array of
multiple 2D PROGMEM arrays, since it has complicated syntax.


Status: done and works! It compiles in the Arduino IDE **and** has been fully
tested and run on an Arduino Nano with ATMega328 mcu!


CONCLUSIONS:

The way that the `pgm_read_*()` functions work, such as `pgm_read_byte()`,
`pgm_read_word()`, etc., is that they map regular RAM addresses into PROGMEM
(Flash) addresses, then read the contents of those Flash addresses! In this
way, the regular C and C++ language and compiler constructs work like normal,
producing RAM addresses and offsets from pointers and array starts and things,
withOUT any customization or modifications to the compiler from AVR-libc. BUT,
those RAM addresses do NOT actually contain any of the useful PROGMEM data we
are after! Rather, AVR-libc must then **map** those RAM addresses to the real
Flash addresses and read the Flash data. If we read the contents of those RAM
address, they'd contain garbage or random data, NOT the data we are after. So,
the `pgm_read_*()` functions do the mapping from RAM to Flash memory and then
give us the Flash data we need.

Example and explantion of this:
    // Works! [GREAT]
    byte my_data = pgm_read_byte(&((ALL_DATA[2])[5][1])); // 248

When you do something more complicated, like `&((ALL_DATA[2])[5][1])`, it all
still works! The value at `ALL_DATA[2]` is an address to a 2D sub-array, such
as `DATA1`, `DATA2`, or `DATA3`. Indexing into that sub-array then takes place
via `[5][1]`. The **value** at that location in RAM is pure garbage! We don't
know **what** might actually be there! BUT, we don't care! We take
the **address** at that indexed location via `&` in order to obtain a RAM
address. We then pass that RAM address to `pgm_read_byte()` to do the mapping
from the RAM address to a Flash memory address, and it then reads the contents
at that mapped Flash address. We never find out what that mapped Flash address
is, but that's ok. So long as we keep the RAM address we always have a way to
read the Flash value again via those `pgm_read_*()` functions.


References:
1. ***** My Question: How to make PROGMEM array of 2D PROGMEM arrays:
   https://stackoverflow.com/q/37903758/4561887
    1. *****+ My answer with this code here: https://stackoverflow.com/a/72624681/4561887
1. ***** AVR-libc reference page:
   https://www.nongnu.org/avr-libc/user-manual/group__avr__pgmspace.html
1. *****+ AVR-libc Tutorial: https://www.nongnu.org/avr-libc/user-manual/pgmspace.html
1. https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
1. [my answer] 1D arrays: https://stackoverflow.com/a/51527502/4561887
1. [my answer] 2d arrays and automatic array "decay" or "adjusting" to ptrs:
   https://stackoverflow.com/a/67814330/4561887


*/



// Get the number of elements in any C array
// - from my repo here:
//   https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/utilities.h#L42
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

/// Definitions: `rows` = "rows"; `cols` = "columns"

/// Get number of rows in a 2D array
#define NUM_ROWS(array_2d) ARRAY_LEN(array_2d)

/// Get number of columns in a 2D array
#define NUM_COLS(array_2d) ARRAY_LEN(array_2d[0])


/// \brief      Print a 2D array which has a VARIABLE number of rows but
///             FIXED number of columns.
///     This code is from Example 2 here:
///     https://stackoverflow.com/a/67814330/4561887
///     For PROGMEM help, see:
///     1. ***** [main AVR tutorial]
///        https://www.nongnu.org/avr-libc/user-manual/pgmspace.html
///     1. [Arduino reference]
///        https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
///     1. [AVR reference pg]
///        https://www.nongnu.org/avr-libc/user-manual/group__avr__pgmspace.html
/// \param[in]  array_2d    a 2D array; is of type `int [][2]` (n x 2 (2D) array
///                         of ints), which naturally decays to type
///                         `int (*)[2]` (ptr to (1D) array of 2 ints)
/// \param[in]  num_rows    The number of rows in the array
/// \return     None
void print_2d_progmem_array(const byte array_2d[][2], size_t num_rows)
{
    Serial.println(F("print_2d_progmem_array:"));

    for (size_t row = 0; row < num_rows; row++)
    {
        for (size_t col = 0; col < NUM_COLS(array_2d); col++)
        {
            // This works!:
            // byte val = pgm_read_byte(&array_2d[row][col]);

            // But, let's print out the address too, for learning
            uint16_t address = (uint16_t)(&array_2d[row][col]);
            byte val = pgm_read_byte(address);

            Serial.print(F("array_2d["));
            Serial.print(row);
            Serial.print("]");
            Serial.print("[");
            Serial.print(col);
            Serial.print(F("]=address:"));
            Serial.print(address);
            Serial.print(F("=val:"));
            Serial.print(val);
            Serial.print("  ");
        }
        Serial.println();
    }
    Serial.println();
}


void setup()
{
    Serial.begin(115200);
    Serial.print(F("\n\nBEGIN:\n\n"));

    static const byte DATA1[3][2] PROGMEM =
    {
        (byte)-1, 6, // Note: -1 underflows to 255
        (byte)-3, 7, // Note: -3 underflows to 253
        (byte)-5, 8, // Note: -5 underflows to 251
    };

    static const byte DATA2[3][2] PROGMEM =
    {
        10,  13,
        11,  14,
        12,  15,
    };

    // static const byte DATA3[6][2] PROGMEM =
    // {
    //     0,  100,
    //     1,  101,
    //     2,  102,
    //     3,  103,
    //     4,  104,
    //     5,  (byte)-8, // Note: -8 underflows to 248
    // };

    // alternative, better and clearer way to define the array just above:
    static const byte DATA3[][2] PROGMEM =
    {
        {0,         100},
        {1,         101},
        {2,         102},
        {3,         103},
        {4,         104},
        {5,  (byte)-8}, // Note: -8 underflows to 248
    };

    // First, prove we can read some values from the above 2D PROGMEM arrays.
    print_2d_progmem_array(DATA1, NUM_ROWS(DATA1));
    print_2d_progmem_array(DATA2, NUM_ROWS(DATA2));
    print_2d_progmem_array(DATA3, NUM_ROWS(DATA3));


    // -------------------------------------------------------------------------
    // Now let's store the above 2D PROGMEM arrays all into a 1D PROGEMEM array
    // -------------------------------------------------------------------------


    // Technique 1 [best]: use a typedef for the `array2d_t` type to make the
    // definition of the `ALL_DATA` array easier to understand and read
    {
        Serial.println(F("\n===== Technique 1: ====="));

        typedef byte (*array2d_t)[2];
        // Note: the left-most `const` here makes the `byte`s being pointed-to
        // `const`, whereas the right-most `const` makes the actual ptr itself
        // `const`, NOT what it points to.
        typedef const byte (* const array2d_const_t)[2];

        static const array2d_const_t ALL_DATA[] PROGMEM =
        {
            DATA1,
            DATA2,
            DATA3,
        };

        // now print out all 2D PROGMEM arrays within the `ALL_DATA` 1D PROGMEM
        // array

        // This does NOT work quite right!
        // Broken: it will only print the 1st row.
        //
        // `NUM_ROWS(array2d)` always returns 1, since the `typedef`ed
        // `array2d_t` type is actually a ptr (it represents a 2D array by
        // being a ptr to a 1D array), so this only prints the first row of
        // each data array since the ptr length is always 1. We will have to do
        // this explicitly instead.
        Serial.println(F("\n--- 1.A: ---\n"));
        for (size_t i = 0; i < ARRAY_LEN(ALL_DATA); i++)
        {
            // Attempt to print the entire data array
            array2d_t array2d = pgm_read_ptr(&ALL_DATA[i]);

            // broken! `NUM_ROWS(array2d)` always returns 1 below!
            // prove that `NUM_ROWS(array2d)` always returns 1
            size_t num_rows = NUM_ROWS(array2d);
            Serial.print(F("NUM_ROWS(array2d)="));
            Serial.println(num_rows);

            print_2d_progmem_array(array2d, NUM_ROWS(array2d));
        }


        // This works! Be **explicit** in manually specifying the number of rows
        // for each 2D array! See the comment just above!
        Serial.println(F("\n--- 1.B: ---\n"));
        array2d_t array2d;
        size_t i_data;
        // DATA1
        i_data = 0;
        array2d = pgm_read_ptr(&ALL_DATA[i_data]);
        print_2d_progmem_array(array2d, NUM_ROWS(DATA1));
        // DATA2
        i_data = 1;
        array2d = pgm_read_ptr(&ALL_DATA[i_data]);
        print_2d_progmem_array(array2d, NUM_ROWS(DATA2));
        // DATA3
        i_data = 2;
        array2d = pgm_read_ptr(&ALL_DATA[i_data]);
        print_2d_progmem_array(array2d, NUM_ROWS(DATA3));

        // print the addresses just above, for understanding, too
        uint16_t address;
        // DATA1
        address = (uint16_t)(&ALL_DATA[0]);
        Serial.print(F("address (`&ALL_DATA[0]`)="));
        Serial.println(address);
        // DATA2
        address = (uint16_t)(&ALL_DATA[1]);
        Serial.print(F("address (`&ALL_DATA[1]`)="));
        Serial.println(address);
        // DATA3
        address = (uint16_t)(&ALL_DATA[2]);
        Serial.print(F("address (`&ALL_DATA[2]`)="));
        Serial.println(address);

        // print the values in the 1D outer-most array too, for understanding,
        // as these **values** should be the **addresses** of the `DATA1`,
        // `DATA2`, and `DATA3` sub-arrays!
        //
        // NB: the **value** of the outer array = the **address** of the inner
        // array, so it is still acceptable to call this value an "address"!
        // DATA1
        address = (uint16_t)(ALL_DATA[0]);
        Serial.print(F("value of outer array / address of inner array "
                       "(`ALL_DATA[0]`)="));
        Serial.println(address);
        // DATA2
        address = (uint16_t)(ALL_DATA[1]);
        Serial.print(F("value of outer array / address of inner array "
                       "(`ALL_DATA[1]`)="));
        Serial.println(address);
        // DATA3
        address = (uint16_t)(ALL_DATA[2]);
        Serial.print(F("value of outer array / address of inner array "
                       "(`ALL_DATA[2]`)="));
        Serial.println(address);


        Serial.println(F("\n--- general indexing: ---\n"));

        // Works! [GREAT]
        byte my_data = pgm_read_byte(&((ALL_DATA[2])[5][1])); // 248  <============ WORKS GREAT! Great general indexing example ===========
        Serial.print(F("my_data="));
        Serial.print(my_data);
        // print the address too, for understanding
        address = (uint16_t)(&((ALL_DATA[2])[5][1]));
        Serial.print(F("; address="));
        Serial.print(address);
        Serial.println(F(" <=== this is the sum of the value or address just "
            "above, + 11, which is the offset to this member of that array!\n"
            "That's how this works! That RAM address is then mapped by the "
            "`pgm_read_*()` functions into a PROGMEM (Flash) address, which\n"
            "gets read by those functions!"));

        // Also works, but is perhaps unnecessarily verbose when just trying to
        // obtain one number. So, I'd prefer to use the style shown just above
        // instead.
        array2d = pgm_read_ptr(&ALL_DATA[2]);    // DATA3
        my_data = pgm_read_byte(&array2d[5][1]); // 248
        Serial.print(F("my_data="));
        Serial.print(my_data);
        // print the addresses too, for understanding
        address = (uint16_t)(&ALL_DATA[2]);
        Serial.print(F("; address (`&ALL_DATA[2]`)="));
        Serial.print(address);
        address = (uint16_t)(&array2d[5][1]);
        Serial.print(F("; address (`&array2d[5][1]`)="));
        Serial.println(address);
    }


    // Technique 2: withOUT a typedef (very hard to read)
    // See https://cdecl.org/ for help.
    {
        Serial.println(F("\n===== Technique 2: ====="));

        // defined withOUT the typedef; notice the extra `const` here after
        // the asterisk (`*`). That's ok. It makes the ptr itself `const`,
        // whereas the `const` to the far left makes the stuff being pointed-to
        // `const`.
        static const byte (* const ALL_DATA2[])[2] PROGMEM =
        {
            DATA1,
            DATA2,
            DATA3,
        };

        // now print out all 2D PROGMEM arrays within the `ALL_DATA2` 1D PROGMEM
        // array

        // skip attempt A since we already tested it above, and just go straight
        // to attempt B, which we know works

        Serial.println(F("\n--- 2.B: ---\n"));

        // defined withOUT the typedef;
        // Notice I _removed_ the `const` after the asterisk so that this ptr
        // itself is NOT `const`, so that it can be re-assigned 3 separate
        // times--once per DATA array.
        byte (* array2d)[2];
        size_t i_data;
        // DATA1
        i_data = 0;
        array2d = pgm_read_ptr(&ALL_DATA2[i_data]);
        print_2d_progmem_array(array2d, NUM_ROWS(DATA1));
        // DATA2
        i_data = 1;
        array2d = pgm_read_ptr(&ALL_DATA2[i_data]);
        print_2d_progmem_array(array2d, NUM_ROWS(DATA2));
        // DATA3
        i_data = 2;
        array2d = pgm_read_ptr(&ALL_DATA2[i_data]);
        print_2d_progmem_array(array2d, NUM_ROWS(DATA3));
    }
}

void loop()
{
    // nothing to do
}



/*
SAMPLE OUTPUT:

Tested on an Arduino Nano with ATmega328 mcu:

    BEGIN:

    print_2d_progmem_array:
    array_2d[0][0]=address:952=val:255  array_2d[0][1]=address:953=val:6
    array_2d[1][0]=address:954=val:253  array_2d[1][1]=address:955=val:7
    array_2d[2][0]=address:956=val:251  array_2d[2][1]=address:957=val:8

    print_2d_progmem_array:
    array_2d[0][0]=address:946=val:10  array_2d[0][1]=address:947=val:13
    array_2d[1][0]=address:948=val:11  array_2d[1][1]=address:949=val:14
    array_2d[2][0]=address:950=val:12  array_2d[2][1]=address:951=val:15

    print_2d_progmem_array:
    array_2d[0][0]=address:934=val:0  array_2d[0][1]=address:935=val:100
    array_2d[1][0]=address:936=val:1  array_2d[1][1]=address:937=val:101
    array_2d[2][0]=address:938=val:2  array_2d[2][1]=address:939=val:102
    array_2d[3][0]=address:940=val:3  array_2d[3][1]=address:941=val:103
    array_2d[4][0]=address:942=val:4  array_2d[4][1]=address:943=val:104
    array_2d[5][0]=address:944=val:5  array_2d[5][1]=address:945=val:248


    ===== Technique 1: =====

    --- 1.A: ---

    NUM_ROWS(array2d)=1
    print_2d_progmem_array:
    array_2d[0][0]=address:952=val:255  array_2d[0][1]=address:953=val:6

    NUM_ROWS(array2d)=1
    print_2d_progmem_array:
    array_2d[0][0]=address:946=val:10  array_2d[0][1]=address:947=val:13

    NUM_ROWS(array2d)=1
    print_2d_progmem_array:
    array_2d[0][0]=address:934=val:0  array_2d[0][1]=address:935=val:100


    --- 1.B: ---

    print_2d_progmem_array:
    array_2d[0][0]=address:952=val:255  array_2d[0][1]=address:953=val:6
    array_2d[1][0]=address:954=val:253  array_2d[1][1]=address:955=val:7
    array_2d[2][0]=address:956=val:251  array_2d[2][1]=address:957=val:8

    print_2d_progmem_array:
    array_2d[0][0]=address:946=val:10  array_2d[0][1]=address:947=val:13
    array_2d[1][0]=address:948=val:11  array_2d[1][1]=address:949=val:14
    array_2d[2][0]=address:950=val:12  array_2d[2][1]=address:951=val:15

    print_2d_progmem_array:
    array_2d[0][0]=address:934=val:0  array_2d[0][1]=address:935=val:100
    array_2d[1][0]=address:936=val:1  array_2d[1][1]=address:937=val:101
    array_2d[2][0]=address:938=val:2  array_2d[2][1]=address:939=val:102
    array_2d[3][0]=address:940=val:3  array_2d[3][1]=address:941=val:103
    array_2d[4][0]=address:942=val:4  array_2d[4][1]=address:943=val:104
    array_2d[5][0]=address:944=val:5  array_2d[5][1]=address:945=val:248

    address (`&ALL_DATA[0]`)=887
    address (`&ALL_DATA[1]`)=889
    address (`&ALL_DATA[2]`)=891
    value of outer array / address of inner array (`ALL_DATA[0]`)=952
    value of outer array / address of inner array (`ALL_DATA[1]`)=946
    value of outer array / address of inner array (`ALL_DATA[2]`)=934

    --- general indexing: ---

    my_data=248; address=945 <=== this is the sum of the value or address just above, + 11, which is the offset to this member of that array!
    That's how this works! That RAM address is then mapped by the `pgm_read_*()` functions into a PROGMEM (Flash) address, which
    gets read by those functions!
    my_data=248; address (`&ALL_DATA[2]`)=891; address (`&array2d[5][1]`)=945

    ===== Technique 2: =====

    --- 2.B: ---

    print_2d_progmem_array:
    array_2d[0][0]=address:952=val:255  array_2d[0][1]=address:953=val:6
    array_2d[1][0]=address:954=val:253  array_2d[1][1]=address:955=val:7
    array_2d[2][0]=address:956=val:251  array_2d[2][1]=address:957=val:8

    print_2d_progmem_array:
    array_2d[0][0]=address:946=val:10  array_2d[0][1]=address:947=val:13
    array_2d[1][0]=address:948=val:11  array_2d[1][1]=address:949=val:14
    array_2d[2][0]=address:950=val:12  array_2d[2][1]=address:951=val:15

    print_2d_progmem_array:
    array_2d[0][0]=address:934=val:0  array_2d[0][1]=address:935=val:100
    array_2d[1][0]=address:936=val:1  array_2d[1][1]=address:937=val:101
    array_2d[2][0]=address:938=val:2  array_2d[2][1]=address:939=val:102
    array_2d[3][0]=address:940=val:3  array_2d[3][1]=address:941=val:103
    array_2d[4][0]=address:942=val:4  array_2d[4][1]=address:943=val:104
    array_2d[5][0]=address:944=val:5  array_2d[5][1]=address:945=val:248


*/
