/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
1 Mar. 2022

Print bold and colors and learn other ANSI formatting codes.
STATUS: works, but is NOT a complete example of ANSI color codes by any means; this is just a short
demo.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 printf_bold_and_colors.c -o bin/a && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 printf_bold_and_colors.c -o bin/a && bin/a
```

References:
1. *****[my answer on this] https://stackoverflow.com/a/71305350/4561887
1. ANSI escape codes: https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/git-diffn.sh#L126-L138
1. How to bold text in c program: https://stackoverflow.com/q/71274207/4561887
1. *****+ Full table of the ANSI formatting number codes:
   ttps://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters

ANSI Color Code Examples
Git config color code descriptions; see here:
https://stackoverflow.com/questions/26941144/how-do-you-customize-the-color-of-the-diff-header-in-git-diff/61993060#61993060
---------------    ----------------------------------------------------------------
                   Git config color code desription
ANSI Color Code    Order: text_color(x1) background_color(x1) attributes(0 or more)
----------------   ----------------------------------------------------------------
\033[m             # code to turn off or "end" the previous color code
\033[1m            # "bold white"
\033[31m           # "red"
\033[32m           # "green"
\033[33m           # "yellow"
\033[34m           # "blue"
\033[36m           # "cyan"
\033[1;33m         # "yellow bold"
\033[1;36m         # "cyan bold"
\033[3;30;42m      # "black green italic" = black text with green background, italic text
\033[9;30;41m      # "black red strike" = black text with red background, strikethrough line through the text
*/



// #include <stdbool.h> // For `true` (`1`) and `false` (`0`) macros in C
// #include <stdint.h>  // For `uint8_t`, `int8_t`, etc.
#include <stdio.h>   // For `printf()`

// SOME ANSI COLOR CODES--VERY INCOMPLETE LIST--consider how to refactor this (or just complete it
// as-is) to make it more-usable.
#define ANSI_OFF        "\e[m"
#define ANSI_START      "\e["
#define ANSI_END        "m"
#define ANSI_BOLD       ";1"
#define ANSI_FG_RED     ";31"   // foreground color red
#define ANSI_BG_RED     ";41"   // background color red
#define ANSI_FG_BR_YLW  ";93"   // foreground color bright yellow
#define ANSI_BG_BR_YLW  ";103"  // background color bright yellow

// 1 = bold; 5 = slow blink; 31 = foreground color red
// 34 = foreground color blue
// See: https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
#define COLOR_OFF  "\e[m"
#define COLOR_BOLD_SLOW_BLINKING      "\e[1;5m"
#define COLOR_BOLD_SLOW_BLINKING_RED  "\e[1;5;31m"
#define COLOR_BOLD_BLUE               "\e[1;34m"

#define IS_EVEN(num) ((num) % 2 == 0)
#define IS_ODD(num)  (!(IS_EVEN(num)))

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf(ANSI_START ANSI_BOLD ANSI_END "Hello" ANSI_OFF " World.\n\n");

    const char str[] = "Hello World.\n\n";
    const size_t NUM_CHARS_TO_COLORIZE = sizeof(str) - 3; // - 2 newlines and - 1 null terminator
    for (size_t i = 0; i < sizeof(str); i++)
    {
        if (i < NUM_CHARS_TO_COLORIZE)
        {
            if (IS_ODD(i))
            {
                printf(ANSI_START ANSI_BOLD ANSI_FG_RED ANSI_END
                       "%c"
                       ANSI_OFF, str[i]);
            }
            else // is even
            {
                printf(ANSI_START ANSI_BOLD ANSI_BG_RED ANSI_FG_BR_YLW ANSI_END
                       "%c"
                       ANSI_OFF, str[i]);
            }
        }
        else
        {
            printf("%c", str[i]);
        }
    }

    // Make "hello" bold, slow blinking, red, and "world" just bold and blue
    printf(COLOR_BOLD_SLOW_BLINKING_RED "hello " COLOR_OFF
           COLOR_BOLD_BLUE "world\n\n" COLOR_OFF);

    return 0;
}

/*
SAMPLE OUTPUT:

In C:
(run it yourself to view the full effect!)

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=c17 printf_bold_and_colors.c -o bin/a && bin/a
    Hello World.

    Hello World.

    hello world


OR, in C++:
(run it yourself to view the full effect!)

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=c++17 printf_bold_and_colors.c -o bin/a && bin/a
    Hello World.

    Hello World.

    hello world

*/
