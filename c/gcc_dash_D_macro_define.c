/*
gcc_dash_D_macro_define.c

///// TODO: RENAME TO: gcc_define_macro_in_build_param__and_stringify_macro; also:
symlink this file into cpp/macro_practice folder.

Pass `-DMY_NUMBER=1234`, or similar, as a build option, and prove it got passed in.

Run cmd:

    1. MY_NUMBER=999
            gcc -std=c11 -Wall -Wextra -Werror -o bin/D_define -DMY_NUMBER=999 \
            -DMY_THRESHOLD=1000 -DGREETING='"Hello World!"' gcc_dash_D_macro_define.c && \
            bin/D_define
    2. MY_NUMBER=1000
            gcc -std=c11 -Wall -Wextra -Werror -o bin/D_define -DMY_NUMBER=1000 \
            -DMY_THRESHOLD=1000 -DGREETING='"Hello World!"' gcc_dash_D_macro_define.c && \
            bin/D_define
    3. MY_NUMBER=1001
            gcc -std=c11 -Wall -Wextra -Werror -o bin/D_define -DMY_NUMBER=1001 \
            -DMY_THRESHOLD=1000 -DGREETING='"Hello World!"' gcc_dash_D_macro_define.c && \
            bin/D_define

References:
1. [my code] https://github.com/ElectricRCAircraftGuy/eRCaGuy_PPM_Writer/blob/master/src/eRCaGuy_PPM_Writer.h#L77
1. [my answer] https://stackoverflow.com/a/66094447/4561887
1. ***** https://medium.com/@hauyang/convert-int-into-string-with-c-macro-125eeaa71600

*/


#include <stdbool.h> // for `true` and `false`
#include <stdint.h>
#include <stdio.h>   // for printf

/// Stringify any macro or words; ie: convert any macro input `macro`, or any input words,
/// to a string!
/// - Stringizing; see: https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html and
///   https://medium.com/@hauyang/convert-int-into-string-with-c-macro-125eeaa71600
#define STR(macro) STR_INDIRECTION(macro)  // macro input param can be any macro or words
// Can be used to stringify an **already-expanded** macro! WithOUT this indirection, stringification
// of the macro wouldn't work, as it would stringify the macro name itself, rather than
// stringifying the **contents** of the macro (ie: the **expanded** macro)!
#define STR_INDIRECTION(any_words) #any_words // input param can be any words, but not a macro
                                              // directly since the macro won't get expanded first
                                              // if passed directly to this macro.


#if MY_NUMBER >= MY_THRESHOLD
// stringify the int `MY_THRESHOLD`
static const char * const STATEMENT = "MY_NUMBER is >= " STR(MY_THRESHOLD);
#else
// stringify the int `MY_THRESHOLD`
static const char * const STATEMENT = "MY_NUMBER is < " STR(MY_THRESHOLD);
#endif

int main(void)
{
    printf(GREETING "\n");
    printf("%s\n", STATEMENT);
    // Print these `int`s as `int`s! Note: I could stringify them here instead, if I wanted,
    // but since I already demonstrated that above, let's just print them as `int`s
    // to demonstrate that technique this time instead.
    printf("MY_NUMBER = %i, MY_THRESHOLD = %i\n", MY_NUMBER, MY_THRESHOLD);
    printf("GREETING = \"" GREETING "\"\n");
    // OR, here's another way to print this!:
    printf("GREETING = \"%s\"\n", GREETING);
    printf("another greeting = \"%s\"\n", STR(Hey you! How are you doing?));

    return 0;
}

/*
Sample Output:

1.

    $ gcc -std=c11 -Wall -Wextra -Werror -o bin/D_define -DMY_NUMBER=999 \
    >             -DMY_THRESHOLD=1000 -DGREETING='"Hello World!"' gcc_dash_D_macro_define.c && \
    >             bin/D_define
    Hello World!
    MY_NUMBER is < 1000
    MY_NUMBER = 999, MY_THRESHOLD = 1000
    GREETING = "Hello World!"
    GREETING = "Hello World!"
    another greeting = "Hey you! How are you doing?"

2.

    $ gcc -std=c11 -Wall -Wextra -Werror -o bin/D_define -DMY_NUMBER=1000 \
    >             -DMY_THRESHOLD=1000 -DGREETING='"Hello World!"' gcc_dash_D_macro_define.c && \
    >             bin/D_define
    Hello World!
    MY_NUMBER is >= 1000
    MY_NUMBER = 1000, MY_THRESHOLD = 1000
    GREETING = "Hello World!"
    GREETING = "Hello World!"
    another greeting = "Hey you! How are you doing?"

3.

    $ gcc -std=c11 -Wall -Wextra -Werror -o bin/D_define -DMY_NUMBER=1001 \
    >             -DMY_THRESHOLD=1000 -DGREETING='"Hello World!"' gcc_dash_D_macro_define.c && \
    >             bin/D_define
    Hello World!
    MY_NUMBER is >= 1000
    MY_NUMBER = 1001, MY_THRESHOLD = 1000
    GREETING = "Hello World!"
    GREETING = "Hello World!"
    another greeting = "Hey you! How are you doing?"

*/

