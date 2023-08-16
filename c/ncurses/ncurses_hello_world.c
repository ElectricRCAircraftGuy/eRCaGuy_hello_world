///usr/bin/env ccache gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm -lncurses && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
15 Aug. 2023

Ncurses hello world demo from here: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
- See my `ncurses` build and install instructions here: "eRCaGuy_hello_world/c/ncurses/README.md".

STATUS: done and works!

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# Why `-std=gnu17` vs `-std=c17`, and `-std=gnu++17` vs `-std=c++17`?
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# [run once ever] install ccache
sudo apt update && sudo apt install ccache

# 1. In C:
./ncurses_hello_world.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 ncurses_hello_world.c -o bin/a -lm -lncurses && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 ncurses_hello_world.c -o bin/a -lncurses && bin/a
```

References:
1. Modified from here: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
1.

*/


#include <ncurses.h>

int main()
{
    initscr();          /* Start curses mode          */
    printw("Hello World !!!");  /* Print Hello World          */
    refresh();          /* Print it on to the real screen */
    getch();            /* Wait for user input */
    endwin();           /* End curses mode        */

    return 0;
}

/*
SAMPLE OUTPUT:

In C:

    eRCaGuy_hello_world/c$ gcc -Wall -Wextra -Werror -O3 -std=gnu17 ncurses_hello_world.c -o bin/a -lm -lncurses && bin/a
    Hello World !!!


OR, in C++:

    eRCaGuy_hello_world/c$ g++ -Wall -Wextra -Werror -O3 -std=gnu++17 ncurses_hello_world.c -o bin/a -lncurses && bin/a
    [same as in C]

*/
