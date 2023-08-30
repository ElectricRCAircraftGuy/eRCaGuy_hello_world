This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# About

[`ncurses`](https://en.wikipedia.org/wiki/Ncurses) is a [TUI](https://en.wikipedia.org/wiki/Text-based_user_interface) GUI-like library for writing GUI-like programs in the command-line terminal. Apparently it's the modern, open-source re-implementation (as a library and API) of the "System V" (system five) Unix operating system look and feel from the 1980's. See: https://en.wikipedia.org/wiki/Ncurses.

Programs written with it include `gpsmon` (I'm guessing), `htop` (I'm guessing), and `ncdu` (I'm guessing, based on its initials: 'n''c'urses 'd'isk 'u'sage). 


# Getting started / References

1. \*\*\*\*\*+ https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html
    1. Hello world: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
1. Examples from others:
    1. Logan Wright: 
        1. https://github.com/loganwrightAI/LinuxCMDProjects
            1. https://github.com/loganwrightAI/LinuxCMDProjects/issues/1


# Build and install the latest version of `ncurses` from source code

_Tested on Ubuntu 22.04.2._

References:
1. Official source code: https://invisible-island.net/ncurses/announce.html
    1. Official source code download archives page: https://invisible-island.net/archives/ncurses/

        The latest version at the time of this writing is `6.4-20230812`, from 12 Aug. 2023.

1. GitHub mirror of the official source code: https://github.com/mirror/ncurses

```bash
# 1. Download
# - NB: the absolute latest version will be found here instead, on the official archives download
#   page: https://invisible-island.net/archives/ncurses/

# Option 1.1 (easiest, by far, so do this): clone from the Github mirror
git clone https://github.com/mirror/ncurses.git
cd ncurses

# Option 1.2 (best only if you need the absolute latest version): find the latest version on the
# archives page, and download and extract it. 
# TODO: if I ever need the absolute latest version, figure this out.

# 2. Build and install
time ./configure    # takes ~8 sec
time make           # takes ~45 sec
sudo make install   # installs libraries into /usr/include and other places

# 3. (Optional) See all installed header files authored by Thomas E. Dickey, the author of ncurses
rg -il 'Thomas.{0,30}Dickey' /usr/include
```

# TODO

1. Write Option 1.2 above, to get the latest source code. Here are the start of my notes on it so far:
    ```bash
    # Option 1.2 (best only if you need the absolute latest version): find the latest version on the
    # archives page, and download and extract it. 
    # - this guarantees you will get the absolute latest version straight from where the author puts
    #   it first. 
    # - Archives page: https://invisible-island.net/archives/ncurses/
    # - Ex: the latest version at this moment is 6.4-20230812, so here is that download URL.
    #   https://invisible-island.net/archives/ncurses/6.4/ncurses-6.4-20230812.patch.gz
    # Download (replace this URL with the latest version at the time you look)
    wget https://invisible-island.net/archives/ncurses/6.4/ncurses-6.4-20230812.patch.gz
    ...
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
