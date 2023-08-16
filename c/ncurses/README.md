This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# About

[`ncurses`](https://en.wikipedia.org/wiki/Ncurses) is a [TUI](https://en.wikipedia.org/wiki/Text-based_user_interface) GUI-like library for writing GUI-like programs in the command-line terminal. Apparently it's the modern, open-source re-implementation (as a library and API) of the "System V" (system five) Unix operating system look and feel from the 1980's. See: https://en.wikipedia.org/wiki/Ncurses.

Programs written with it include `gpsmon` (I'm guessing), `htop` (I'm guessing), and `ncdu` (I'm guessing, based on its initials: 'n''c'urses 'd'isk 'u'sage). 


# Getting started

1. https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html
    1. Hello world: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html


# Build and install the latest version of `ncurses` from source code

_Tested on Ubuntu 22.04.2._

References:
1. Official source code: https://invisible-island.net/ncurses/announce.html
1. GitHub mirror of the official source code: https://github.com/mirror/ncurses

```bash
# download
git clone https://github.com/mirror/ncurses.git
cd ncurses

# build and install
time ./configure    # takes ~8 sec
time make           # takes ~45 sec
sudo make install   # installs libraries into /usr/include and other places

# See all installed header files authored by Thomas E. Dickey, the author of ncurses
rg -il 'Thomas.{0,30}Dickey' /usr/include
```


# Build a program with it

The simplest build command is listed right here: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html:

```bash
# build
gcc myfile.c -lncurses
# run
./a.out
```

But here are some better build commands in C and C++, from [ncurses_hello_world.c](ncurses_hello_world.c):
```bash
# 1. In C:
./ncurses_hello_world.c
# or:
gcc -Wall -Wextra -Werror -O3 -std=gnu17 ncurses_hello_world.c -o bin/a -lm -lncurses && bin/a

# 2. In C++
g++ -Wall -Wextra -Werror -O3 -std=gnu++17 ncurses_hello_world.c -o bin/a -lncurses && bin/a
```
